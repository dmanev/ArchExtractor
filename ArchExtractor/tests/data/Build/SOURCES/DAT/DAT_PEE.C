/*============================================================================
  Project ......................... PROJECT_NAME
  Component ....................... DAT_PEE
  File revision.................... :   1.4  $
  Last modification date .......... $Modtime:   Mar 22 2010 17:04:50  $
  -------------------------------------------------------------------------
  Copyright ... This software is JCI property. Duplication or
                disclosure is prohibited without JCI written permission
  ------------------------------------------------------------------------- 

  - Macros, constants and types which are not exported are defined in 
    this file
  - Variables and functions which are not exported are defined in this 
    file with the static key word
  
  -------------------------------------------------------------------------
  Comments about the component (role, algorithm, structure, limitations,
           defined tasks and events...)

  - Role : EEPROM Presentation Software Component (Example of MW1011L2)
  
  -------------------------------------------------------------------------
  DAT_PEE.c file review : 

  :   P:/STANDARD/AEH/STK/PVCS/archives/STK/CMP/SOURCES/DAT/EEP/DAT_PEE/Dat_pee.c-arc  $

  ==========================================================================*/

/*--------------------------------------------------------------------------
  Body Identification
  --------------------------------------------------------------------------*/

#define dat_pee   "dat_pee"


/*-------------------------------------------------------------------------
  Included files

  #include <system_file_name.h>
  #include "project_file_name.h"
  --------------------------------------------------------------------------*/
#include "LIB.h"
#include "TOS.h"
#include "LDB.h"
#include "DAT.h"
#include "DAT_PEE.h"
#include "DAT_PEE.hgr"
/*--------------------------------------------------------------------------
  Local constants

  #define cConstantName   ((tType) ConstantValue)
  --------------------------------------------------------------------------*/

// EEPROMErrorCounter is divided is 3 parts :
//                     7  6  5  4  3  2  1  0
//                     X  X  X  X  X  X  X  X
//       Rebuild flag _|  |  |  |  |  |  |  |_
//                   _____|  |  |  |  |  |____| 
// ReadErrorCounter_|________|  |  |  |_______|-WriteErrorCouter
//                  |___________|  |__________| 
#define cMaxReadCounter   ((U8) 0x07)
#define cMaxWriteCounter  ((U8) 0x0F)

#define cTimerPeeMs   ((tTOSTimer) 5000U) // 5 seconds

// Number of EEP Group 
#define cNumberOfEEPGroup  (cDATEepNumberOfProcess-1)

/*--------------------------------------------------------------------------
  Local macros

  #define mMacroName   (MacroDefinition)
  --------------------------------------------------------------------------*/

// The size of EEP Error Table 
#if (cDATPeeSizeErrorGroup != cNumberOfEEPGroup)

  #error "The size of EEP Error Table is different of the number of EEP Group."

#endif

// Direct Access EEP Errors Table
#define mGetEEPErrorTable(idx) mDATReadTable(U8Bit, EEPErrorTable, idx, Default)
#define mSetEEPErrorTable(idx, Val) mDATWriteTable(U8Bit, EEPErrorTable, idx, Val, Default)

// Direct Access EEP Write Error Counter
#define mGetWriteCounter(idx)        (mGetEEPErrorTable(idx) & 0x0F)

// Direct Access EEP Read Error Counter
#define mGetReadCounter(idx)         ((mGetEEPErrorTable(idx) >> 4) & 0x07)

// Direct Access EEP Rebuild Flag
#define mGetRebuildFlag(idx)        ((mGetEEPErrorTable(idx) >> 7) & 0x01)

// Handle EEP Write Error Counter
#define mSetWriteError(idx)                             \
  mSetEEPDtc();                                         \
  if(mGetWriteCounter(idx) < cMaxWriteCounter)          \
  {                                                     \
      mSetEEPErrorTable(idx, (mGetEEPErrorTable(idx) + (U8)(1<<0))); \
  }

// Handle EEP Read Error Counter
#define mSetReadError(idx)                              \
  mSetEEPDtc();                                         \
  if(mGetReadCounter(idx) < cMaxReadCounter)            \
  {                                                     \
      mSetEEPErrorTable(idx, (mGetEEPErrorTable(idx) + (U8)(1<<4))); \
  } 
                                                    
// Handle EEP Rebuild Flag
#define mSetRebuildFlag(idx)                                            \
                   mSetEEPDtc();                                        \
                   mSetEEPErrorTable(idx, (mGetEEPErrorTable(idx) | 0x80))

#define mSetDbkDefaultValue(BankName)   \
    {                                   \
    static const U8 BankName##DefaultValues[cDATPeeSize##BankName] = mDATPeeResetBuffer##BankName();\
    mLIBmemcpy((U8 *)DATDbkMirrors.##BankName, BankName##DefaultValues, cDATPeeSize##BankName);\
    }
#define mInitDbkBank(BankName,Val)      \
    {                                   \
    mLIBmemset((U8 *)DATDbkMirrors.##BankName, Val, cDATPeeSize##BankName);\
    }

#define mSetSbkDefaultValue(BankName)   \
    {                                   \
    static const U8 BankName##DefaultValues[cDATPeeSize##BankName] = mDATPeeResetBuffer##BankName();\
    mLIBmemcpy((U8 *)DATSbkMirrors.##BankName, BankName##DefaultValues, cDATPeeSize##BankName);\
    }
#define mInitSbkBank(BankName,Val)      \
    {                                   \
    mLIBmemset((U8 *)DATSbkMirrors.##BankName, Val, cDATPeeSize##BankName);\
    }

// Cm006501: Treatment of DEF_EEPROM
#define mSetEEPDtc() \
    mDATWrite(U1Bit, DefEEPROM, cTrue, Default); \
    if (bEepReadFinished != cFalse) \
    { \
        mDATWrite(U1Bit, EEP_DefEeprom, cTrue, Default) \
    }

// Normalization of calibration parameters
// Cm006814: DIAG: Implement consistency checking of calibration parameters according to prsFS_DIAG-766
//Normalization of maximal values
#define mNormalizeMax(PARAM) \
    DATPeeCalibrationData.##PARAM = \
        ((mDATReadU8BitEEP_##PARAM##Default() > MAX_##PARAM) ? \
         MAX_##PARAM : mDATReadU8BitEEP_##PARAM##Default())

//Normalization of minimal values 
//the result from macro mNormalizeMax() is used
#define mNormalizeMin(PARAM) \
    DATPeeCalibrationData.##PARAM = \
        ((mDATReadU8BitEEP_##PARAM##Default() < MIN_##PARAM) ? \
         MIN_##PARAM : DATPeeCalibrationData.##PARAM)

// List of max EEP values
#define MAX_TPS_RETARD_DETRESSE         (U8)6U
#define MAX_TIMER_DETRESSE              (U8)144U
#define MAX_TPS_APC                     (U8)72U
#define MAX_TPS_PLAF                    (U8)75U
#define MAX_TPS_ESSUIE_MINI             (U8)25U
#define MAX_TPS_MAX_COUPLBLOC           (U8)120U
#define MAX_TPS_ARRET                   (U8)30U
#define MAX_TPS_REPRISE                 (U8)10U
#define MAX_PROLONG_APPUI_COURT         (U8)6U
#define MAX_PROLONG_APPUI_LONG          (U8)6U
#define MAX_TPS_APPUILAV                (U8)67U
#define MAX_PROLONG_APPUI_ARR           (U8)6U
#define MAX_SEUIL_VIT_CONDAROU          (U8)50U
#define MAX_TPS_COM_MOTEUR              (U8)100U
#define MAX_NBCOM_MAX                   (U8)40U
#define MAX_TPS_REF                     (U8)4U
#define MAX_TIMER_RECONDA_AUTO          (U8)60U
#define MAX_N_MISE_APC                  (U8)20U
#define MAX_TPS_OUVPORTE                (U8)20U
#define MAX_TPS_TEMPO_DEG               (U8)24U

#define MAX_SBR_ACTIVE_SPEED_THRESH_TP  (U8)30U
#define MAX_SBR_TIMEOUT_TM_TP           (U8)120U
#define MAX_MAX_NB_ALERT_SEQUENCES_TP   (U8)20U
#define MAX_TPS_BUZ_CLI                 (U8)8U
#define MAX_TPS_CLI                     (U8)10U
#define MAX_TPS_CLIDEGRAD               (U8)5U

// List of min EEP values
#define MIN_TPS_ESSUIE_MINI             (U8)1U
#define MIN_TPS_APPUILAV                (U8)1U
#define MIN_TPS_TEMPO_DEG               (U8)1U
#define MIN_TPS_CLI                     (U8)1U
#define MIN_TPS_CLIDEGRAD               (U8)1U

#define MIN_NBCOM_MAX                   (U8)2U
#define MIN_N_MISE_APC                  (U8)1U
#define MIN_TPS_MAX_COUPLBLOC           (U8)1U
#define MIN_TPS_ARRET                   (U8)1U
#define MIN_TIMER_RECONDA_AUTO          (U8)1U
#define MIN_MAX_NB_ALERT_SEQUENCES_TP   (U8)1U

/*--------------------------------------------------------------------------
  Local types

  struct  sStructureName { ... };
  union   uUnionName { ... };
  enum    eEnumerationName { ... };
  typedef Expression tTypeName;
  --------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------
  Local data

  static  tType   VariableName;
  static  tType*  pVariableName; 
  --------------------------------------------------------------------------*/
static tTOSTimer TimerPee;
static BOOL      bEepReadFinished = cFalse;

/*--------------------------------------------------------------------------
  Constant local data

  static const tType  VariableName;
  --------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------
  Exported data

  tType   CMPVariableName;      (CMP: 3 characters to identify this component)
  tType*  pCMPVariableName;     (CMP: 3 characters to identify this component)
  --------------------------------------------------------------------------*/
tDATPeeCalibrationData DATPeeCalibrationData;

/*--------------------------------------------------------------------------
  Constant exported data
 
  const tType   CMPVariableName;(CMP: 3 characters to identify this component)
  --------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------
  Local function prototypes
  
  static tTypeRetour FunctionName(tTypeArgument1 ArgumentName1, ... );
  --------------------------------------------------------------------------*/


/*============================================================================
  =========================== LOCAL FUNCTIONS ================================
  ==========================================================================*/

/*============================================================================
  DESCRIPTION :
  
  PARAMETERS (Type,Name,Min,Max) :   none

  RETURN VALUE :   none
 
  DESIGN INFORMATION :   refer to Detailed Design Document
  ==========================================================================*/
/* static type FunctionName(...) */


/*============================================================================
  =========================== EXPORTED FUNCTIONS =============================
  ==========================================================================*/

/*============================================================================
  DESCRIPTION :
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void DATPeeInit(void)
{
#ifdef cDATSbkHandleErrorGroup

    // The error bank must be the first bank read at startup.
    // If its handle is 0, it will be the case
    
    // if the error bank is not the first bank read.
    // Then, if another bank read previouly set an error,
    // the error bank read will overwrite this error flag.
    
    mLIBassert( cDATSbkHandleErrorGroup==0 );
#endif
}

/*============================================================================
  DESCRIPTION :
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
BOOL DATPeeIsEepromAccessible(void)
{
    return (cTrue);
}

/*============================================================================
  DESCRIPTION : Rebuild indication
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
MEM_TYPE void DATPeeRebuildDoubleBank(tDATDbkDoubleBankHandle DoubleBankHandle)
{
    mLIBassert(DoubleBankHandle < cNbDbk);
    mSetRebuildFlag(cDATDbkFirstProcessHandle + DoubleBankHandle)
    switch(DoubleBankHandle)
    {
    case cDATDbkHandleDiagBank:
         mSetDbkDefaultValue(DiagBank);
    break;

    case cDATDbkHandleGeneralParameterBank:
         mSetDbkDefaultValue(GeneralParameterBank);
      break;

    case cDATDbkHandleFactoryConfigBank:
         mSetDbkDefaultValue(FactoryConfigBank);
      break;

    case cDATDbkHandleStaticImmoBank:
         mSetDbkDefaultValue(StaticImmoBank);
      break;
  
    case cDATDbkHandleDynamicImmoDataBank:
         mSetDbkDefaultValue(DynamicImmoDataBank);
      break;

    default:
      break;
    }
}

/*============================================================================
  DESCRIPTION :
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
MEM_TYPE void DATPeeErrorIndication(tDATDbkDoubleBankHandle DoubleBankHandle
                           , tDATDbkErrorHandle DbkErrorHandle)
{
    mLIBassert(DoubleBankHandle < cNbDbk);

    if (( DbkErrorHandle == cDATDbkErrorReadingBK1) || ( DbkErrorHandle == cDATDbkErrorReadingBK2))
    {
        mSetReadError(cDATDbkFirstProcessHandle + DoubleBankHandle);
    }
    else if (( DbkErrorHandle == cDATDbkErrorWritingBK1) || ( DbkErrorHandle == cDATDbkErrorWritingBK2))
    {
        mSetWriteError(cDATDbkFirstProcessHandle + DoubleBankHandle);
    }
    else
    {
        mLIBassert(0);
    }
}




/*============================================================================
  DESCRIPTION :
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
MEM_TYPE void DATPeeRebuildSingleBank( tDATSbkSingleBankHandle HandleSbk )
{
    mLIBassert(HandleSbk < cNbSbk);
    mSetRebuildFlag(cDATSbkFirstProcessHandle + HandleSbk);
    switch(HandleSbk)
    {
    case cDATSbkHandleErrorGroup:
         mInitSbkBank(ErrorGroup,0);
      break;
  
    case cDATSbkHandleVersionBank:
         mSetSbkDefaultValue(VersionBank);
      break;
  
    case cDATSbkHandleSupplierBank:
         // No Default value;
      break;
  
    case cDATSbkHandleVINBank:
         // No Default value;
      break;
   
    default:
      break;
    }
}

/*============================================================================
  DESCRIPTION :
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
MEM_TYPE void DATPeeSingleBankErrorIndication( tDATSbkSingleBankHandle HandleSbk
                                      , tDATSbkErrorHandle SbkErrorHandle )
{
    mLIBassert(HandleSbk < cNbSbk);
    if (SbkErrorHandle == cDATSbkErrorReading)
    {
        mSetReadError(cDATSbkFirstProcessHandle + HandleSbk);
    }
    else if (SbkErrorHandle == cDATSbkErrorWriting)
    {
        mSetWriteError(cDATSbkFirstProcessHandle + HandleSbk);
    }
    else
    {
        mLIBassert(0);
    }
}


/*============================================================================
  DESCRIPTION : Send a signal to maintain the Starting Step if the Reading 
                of the EEPROM is not finished.
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void DATPeeIsMaintainStartingStepState( void )
{
    if(mDATRead(U1Bit,IsEepProcessing,Default))
    {
        TOSWriteSignal(cTOSSignalSomebodyMaintainStartingStepState);
    }
}

/*============================================================================
  DESCRIPTION : 5 seconds after the starting step, it's recommended 
                to restore the EEP.
  
  PARAMETERS (Type,Name,Min,Max) :   none

  RETURN VALUE :   none
 
  DESIGN INFORMATION :   refer to Detailed Design Document
  ==========================================================================*/
void DATPeeRestoreBanks(void)
{
    mDATControl(Eep, Restore);
}

/*============================================================================
  DESCRIPTION : During the Starting Step, The banks must be read.
  
  PARAMETERS (Type,Name,Min,Max) :   none

  RETURN VALUE :   none
 
  DESIGN INFORMATION :   refer to Detailed Design Document
  ==========================================================================*/
void DATPeeReadAllBanks(void)
{
    mDATControl(Eep, ReadEep);
}

/*============================================================================
  DESCRIPTION : Update the necessary banks before Enter in Sleep State
  
  PARAMETERS (Type,Name,Min,Max) :   none

  RETURN VALUE :   none
 
  DESIGN INFORMATION :   refer to Detailed Design Document
  ==========================================================================*/
void DATPeeUpdateBanks(void)
{
    // This function is called when the system leave the active state.
    // Add here the Update command of the differed EEP groups
    // mDATControl(Eep, UpdateGroupName1);
    // mDATControl(Eep, UpdateGroupName2);
    // ...
    // mDATControl(Eep, UpdateGroupName3);
}


/****************************************************************************
  DESCRIPTION         : Start a 5 seconds timer

  PARAMETERS          : None
  (Type,Name,Min,Max) 

  RETURN VALUE        : None

  DESIGN INFORMATION  : Refer to Detailed Design Document

*****************************************************************************/
void DATPeeStartTimer(void)
{
    TOSStartTimer(&TimerPee);
}

/****************************************************************************
  DESCRIPTION         : Check the end of the 5 seconds timer.

  PARAMETERS          : None
  (Type,Name,Min,Max) 

  RETURN VALUE        : cTrue if the end of the 5 seconds timer is elapsed.

  DESIGN INFORMATION  : Refer to Detailed Design Document

*****************************************************************************/
BOOL DATPeeIsTimerElapsed(void)
{
    return(TOSIsTimerElapsed(&TimerPee, cTimerPeeMs / cTOSTimerTickMs));
}

/****************************************************************************
  DESCRIPTION         : Check the end of the 5 seconds timer.

  PARAMETERS          : None
  (Type,Name,Min,Max) 

  RETURN VALUE        : cTrue if the end of the 5 seconds timer is elapsed.

  DESIGN INFORMATION  : Refer to Detailed Design Document

*****************************************************************************/
void DATPeeCanRestoreBanks(void)
{
    TOSSeqActivateGraph( cTOSSeqGraphIdEepromManager );
    
    // EEPROM content is read: now safe to set defect if present
    bEepReadFinished = cTrue;
    if (mDATRead(U1Bit, DefEEPROM, Default) != cFalse)
    {
        mDATWrite(U1Bit, EEP_DefEeprom, cTrue, Default);
    }
    
    // Leave starting step state: normalize parameters immediately
    DATPeeNormalizeParameters();
    TOSSeqActivateGraph( cTOSSeqGraphIdEepromNormalization );
}

/****************************************************************************
  DESCRIPTION         : Normalize calibration parameters periodically
                        EEP_<PARAM> => NEEP_<PARAM>
                        taking into account maximal / minimal value limits

  PARAMETERS          : None
  (Type,Name,Min,Max) 

  RETURN VALUE        : None

  DESIGN INFORMATION  : Refer to Detailed Design Document

*****************************************************************************/
void DATPeeNormalizeParameters (void)
{
#ifdef X90_PROJECT
    static MEM_TYPE void DATPeeNormalizeParameters_Static(void);
    DATPeeNormalizeParameters_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DATPeeNormalizeParameters_Static(void)
{
#endif

    // MAX: Normalize to specified maximal value
    
    mNormalizeMax(TPS_RETARD_DETRESSE);
    mNormalizeMax(TIMER_DETRESSE);
    mNormalizeMax(TPS_APC);
    mNormalizeMax(TPS_PLAF);
    mNormalizeMax(TPS_ESSUIE_MINI);
    mNormalizeMax(TPS_MAX_COUPLBLOC);
    mNormalizeMax(TPS_ARRET);
    mNormalizeMax(TPS_REPRISE);
    mNormalizeMax(PROLONG_APPUI_COURT);
    mNormalizeMax(PROLONG_APPUI_LONG);
    mNormalizeMax(TPS_APPUILAV);
    mNormalizeMax(PROLONG_APPUI_ARR);
    mNormalizeMax(SEUIL_VIT_CONDAROU);
    mNormalizeMax(TPS_COM_MOTEUR);
    mNormalizeMax(NBCOM_MAX);
    mNormalizeMax(TPS_REF);
    mNormalizeMax(TIMER_RECONDA_AUTO);
    mNormalizeMax(N_MISE_APC);
    mNormalizeMax(TPS_OUVPORTE);
    mNormalizeMax(TPS_TEMPO_DEG);
    mNormalizeMax(SBR_ACTIVE_SPEED_THRESH_TP);
    mNormalizeMax(SBR_TIMEOUT_TM_TP);
    mNormalizeMax(MAX_NB_ALERT_SEQUENCES_TP);
    mNormalizeMax(TPS_BUZ_CLI);
    mNormalizeMax(TPS_CLI);
    mNormalizeMax(TPS_CLIDEGRAD);

    // MIN: Normalize to value 1
    // Note that mNormalizeMin() should be used AFTER mNormalizeMax()!
    
    // Parameters leading to value 255 due to direct subtraction:
    mNormalizeMin(TPS_ESSUIE_MINI);
    mNormalizeMin(TPS_APPUILAV);
    mNormalizeMin(TPS_TEMPO_DEG);
    mNormalizeMin(TPS_CLI);
    mNormalizeMin(TPS_CLIDEGRAD);
    
    // Parameters that are specified to be normalized:
    mNormalizeMin(TPS_MAX_COUPLBLOC);
    mNormalizeMin(TPS_ARRET);
    mNormalizeMin(NBCOM_MAX);
    mNormalizeMin(TIMER_RECONDA_AUTO);
    mNormalizeMin(N_MISE_APC);
    mNormalizeMin(MAX_NB_ALERT_SEQUENCES_TP);

    // Justification of parameters that will not be normalized:

    // TPS_RETARD_DETRESSE - value 0 leads to at least one LAP_FLI graph cycle of 20 ms
    // TPS_TIMER_DETRESSE - value 0 leads to 1 step of duration 25 s
    // TPS_APC - value 0 leads to 1 step of duration 50 s
    // TPS_PLAF - value 0 produces minimal duration
    
    // TPS_REPRISE - value 0 produces minimal duration

    // TPSFILT_AF - value 0 (and 1) lead to duration of 3...8 ms
    // TPS_POSIT_BALAIS - value 0 produces no steps = 0

    // PROLONG_APPUI_COURT - value 0 leads to 1 stroke
    // PROLONG_APPUI_LONG - value 0 leads to 1 stroke

    // TPS_POSIT_BALAIS_AR - value 0 produces minimal duration
    // PROLONG_APPUI_ARR - value 0 leads to 1 stroke

    // SEUIL_VIT_CONDAROU - value 0 is correct limit speed
    // TPS_COM_MOTEUR - value 0 produces minimal duration 20 ms

    // TPS_REF - value 0 produces minimal duration
    // TMPMERA (TimeOutMERA) - value 0 produces minimal duration
    // TPS_OUVPORTE - value 0 produces minimal duration
    
    // TPS_IMPUL_MINI - value 0 produces minimal duration
    // SBR_ACTIVE_SPEED_THRESH_TP - value 0 produces correct limit
    // SBR_TIMEOUT_TM_TP - value 0 produces minimal duration

    // TPS_BUZ_CLI - value 0 produces minimal duration
}
