//*****************************************************************************
// Company:      Johnson Controls Inc.
// ----------------------------------------------------------------------------
// Copyright:    This software is JCI property.
//               Duplication or disclosure without JCI written authorization
//               is prohibited.
// ----------------------------------------------------------------------------
// Project:      X90_BCM
// Language:     ANSI-C
// ----------------------------------------------------------------------------
// Component:    LAP_LRN
// ----------------------------------------------------------------------------
// $Date:   Mar 31 2010 11:24:24  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LRN/LAP_LRN.c-arc  $
// $Revision:   1.36  $
// ----------------------------------------------------------------------------  
//
//  $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LRN/LAP_LRN.c-arc  $
// 
//    Rev 1.36   Mar 31 2010 11:24:24   amanevd
// Cm006328: COD_ERR_AP set to 0 in function LRNKeyAlreadyLaerned()
// 
//    Rev 1.35   Mar 09 2010 17:37:42   amanevd
// Cm006814: Code review corrections
// 
//    Rev 1.34   Mar 02 2010 10:40:42   adzhelp
// Cm006814: N_MISE_APC normalized
// 
//    Rev 1.33   Feb 11 2010 17:27:30   amanevd
// Cm006997: Implementation of recent prsFS_IMMO-675 and prsFS_IMMO-676
// 
//    Rev 1.32   Feb 08 2010 09:28:18   amanevd
// Cm006744: Perform 32-bit math operations only when values are changed
// 
//    Rev 1.31   Jan 29 2010 18:06:36   amanevd
// Cm007043 & Cm007116: AfterSaleModeValidationAuthorized is set 1 when entering in AFS Key replacement mode
// 
//    Rev 1.30   Jan 21 2010 10:14:06   amanevd
// Cm006999: On unsuccessful pairing in BCM replacement mode the learning mode should
// not be quit
// 
//    Rev 1.29   Jan 21 2010 08:33:52   amanevd
// Cm006997: prsFS_IMMO-675 and prsFS_IMMO-676 put back to initial condition
// 
//    Rev 1.28   Jan 20 2010 12:23:40   amanevd
// Cm007003: cde_eff_code_recu set to 1 on end of BCM replacement mode
// 
//    Rev 1.27   Jan 20 2010 12:01:50   amanevd
// Cm007078: RA-bancs-BCM-53 implementation
// 
//    Rev 1.26   Jan 19 2010 17:05:42   amanevd
// Cm006886: Update of prsFS_IMMO-938 implemented
// 
//    Rev 1.25   Nov 20 2009 11:47:50   amanevd
// Cm006589: LRNStartLearningInAfterSaleMode updated to enable exiting  BCM replacement mode with parameter "Validate"
// 
//    Rev 1.24   Nov 20 2009 10:02:04   amanevd
// Cm005198: FactoryModeAuthorized conditions changed
// 
//    Rev 1.23   Nov 05 2009 18:42:12   amanevd
// Cm006588: COD_ERR_AP is updated to 0x00 on diag request for entering in learning mode
// 
//    Rev 1.22   Oct 06 2009 16:23:52   adzhelp
// Cm006317: Function moved to banked area
// 
//    Rev 1.21   Oct 01 2009 15:09:08   amanevd
// Cm006317: Even if BCM is not blank, authorize Plant Learning while AFS Code is available
// 
//    Rev 1.20   Oct 01 2009 13:59:50   amanevd
// Cm006298: In LRNUpdateLearningAuthorizationConditions
// setting the signal FactoryModeAuthorized to 0 when PWR_IGN==1 is removed
// 
//    Rev 1.19   Oct 01 2009 11:01:42   amanevd
// Cm005587: In case of AFS key reassignment mode successful pairing COD_ERR_APP is set 1
// 
//    Rev 1.18   Oct 01 2009 10:31:30   amanevd
// Cm006325: Verlog LED now blinks at 2Hz in Plant mode for already learnt key
// 
//    Rev 1.17   Sep 30 2009 18:08:24   amanevd
// Cm006328: 'COD_ERR_AP' set to 00h in Plant mode for already learnt key
// 
//    Rev 1.16   Sep 18 2009 15:33:16   amanevd
// Cm005198: EEP_AppCleNonEffect is managed as required in prsFS_IMMO-678, prsFS_IMMO-938 and prsFS_IMMO-992
// 
//    Rev 1.15   Aug 28 2009 15:17:28   amanevd
// Cm005142: Code review corrections
// 
//    Rev 1.14   Aug 07 2009 18:09:48   amanevd
// Cm005142: Implementation of Confidential Diagnostic
// 
//    Rev 1.13   Jul 28 2009 11:49:38   amanevd
// Cm005565: Check for exit from learning conditions included on PWR_IGN==1
// 
//    Rev 1.12   Jul 27 2009 18:16:40   amanevd
// Cm005186: BCM Replacement time measurement starts on sending successful diagnostic request
// 
//    Rev 1.11   Jul 23 2009 13:41:48   amanevd
// Cm005526: 'LearningModeInProgress' is updated immediately on exiting learning mode
// 
//    Rev 1.10   Jul 22 2009 13:41:22   amanevd
// Cm005191: N_MISE_APC parameter is now taken into account on fly on
// 
//    Rev 1.9   Jul 17 2009 10:53:02   amanevd
// Cm004914: AFS code is either erased on Routine request or after Ignition counting reaches N_MISE_APC
// 
//    Rev 1.8   Jul 14 2009 17:18:36   amanevd
// Cm005586: Updating of signal KeyFrequency removed
// 
//    Rev 1.7   May 21 2009 12:24:18   amanevd
// Cm003272 - CCover justification - NO IMPACT ON REAL CODE
// 
//    Rev 1.6   May 07 2009 10:51:54   amanevd
// Cm003272 - Finishing part 2 - pre-integration
// 
//    Rev 1.5   Apr 29 2009 13:14:20   amanevd
// Cm003272 - Intermediate part 3 
// - PRS compliance
// 
//    Rev 1.4   Apr 22 2009 19:23:50   amanevd
// Cm003272 - Finishing part 1 - pre-integration
// 
//    Rev 1.3   Feb 26 2009 16:33:22   amanevd
// Cm003272 - replace(Booleen to BOOL)
// 
//    Rev 1.2   Feb 13 2009 14:52:12   amanevd
// Cm003272 - Intermediate part 1 - PRS compliance
// 
//    Rev 1.1   Feb 04 2009 13:29:48   amanevd
// Cm003272 - Intermediate part 1
// - PRS compliance
// 
//    Rev 1.0   Jan 09 2009 14:21:00   amanevd
// Initial revision.
//*****************************************************************************

//-----------------------------------------------------------------------------
//  Body Identification
//-----------------------------------------------------------------------------

#define LAP_LRN  "LAP_LRN"

//-----------------------------------------------------------------------------
//  Included files
//
//  #include <system_file_name.h>
//  #include "project_file_name.h"
//-----------------------------------------------------------------------------
#include "tos.h"
#include "lib.h"
#include "lib_rnd.h"
#include "dat.h"
#include "LAP_LRN.h"
#include "LAP_LRN.hgr"


//-----------------------------------------------------------------------------
//  Local constants
//
//  #define cConstantName   ((tType) ConstantValue)
//-----------------------------------------------------------------------------

// definitions of useful masks
#define cValueBitBStoOne        ((U32) 0x08000000UL)
#define cLockRFKey              ((U32) 0xF8000000UL)
#define cLockNonRFKey           ((U32) 0xF8000000UL)
#define cPutBitBStoZero         ((U32) 0xF7FFFFFFUL)
#define cMaskKeep24Bits         ((U32) 0x00FFFFFFUL)

#define cPage0                  ((U8) 0)
#define cPage1                  ((U8) 1)
#define cPage2                  ((U8) 2)
#define cPage3                  ((U8) 3)
#define cPage4                  ((U8) 4)
#define cPage5                  ((U8) 5)
#define cPage6                  ((U8) 6)

#define cCodeError0h            ((U8) 0x00U)
#define cCodeError1h            ((U8) 0x01U)
#define cCodeError2h            ((U8) 0x02U)
#define cCodeError11h           ((U8) 0x11U)
#define cCodeError12h           ((U8) 0x12U)
#define cCodeError13h           ((U8) 0x13U)
#define cCodeError14h           ((U8) 0x14U)
#define cCodeError15h           ((U8) 0x15U)
#define cCodeError16h           ((U8) 0x16U)
#define cCodeError17h           ((U8) 0x17U)
#define cCodeError18h           ((U8) 0x18U)
#define cCodeError19h           ((U8) 0x19U)
#define cCodeErrorA1h           ((U8) 0xA1U)
#define cCodeErrorA2h           ((U8) 0xA2U)
#define cCodeErrorB2h           ((U8) 0xB2U)
#define cCodeErrorB3h           ((U8) 0xB3U)
#define cCodeErrorB4h           ((U8) 0xB4U)
#define cCodeErrorB5h           ((U8) 0xB5U)
#define cCodeErrorB6h           ((U8) 0xB6U)
#define cCodeErrorB7h           ((U8) 0xB7U)

// amanevd: QAC expects 32 bit word, we are using 8 bit word.
// It is useless to define 4 times bigger constants just to
// make QAC to shut up.
#ifndef _QAC_
#define cSKIndex0               ((U8) 0)
#define cSKIndex1               ((U8) 1)
#define cSKIndex2               ((U8) 2)
#define cSKIndex3               ((U8) 3)
#define cSKIndex4               ((U8) 4)
#define cSKIndex5               ((U8) 5)
#define cSKIndex6               ((U8) 6)
#else
#define cSKIndex0               ((U32) 0)
#define cSKIndex1               ((U32) 1)
#define cSKIndex2               ((U32) 2)
#define cSKIndex3               ((U32) 3)
#define cSKIndex4               ((U32) 4)
#define cSKIndex5               ((U32) 5)
#define cSKIndex6               ((U32) 6)
#endif

#define cNoLearning               ((U8) 0)
#define cFactoryMode              ((U8) 1)
#define cBcmReplacement           ((U8) 2)
#define cKeyReassignment          ((U8) 3)

// amanevd: 'Neg' constants make QAC to shut up. Must update them
// every time you update the original constant !!!
#define cExitFactoryMode         ((U8) 0x01U)
#define cNegExitFactoryMode      ((U8) 0xFEU)
#define cGiveUpAfterSaleMode     ((U8) 0x02U)
#define cNegGiveUpAfterSaleMode  ((U8) 0xFDU)
#define cLearningValidation      ((U8) 0x04U)
#define cNegLearningValidation   ((U8) 0xFBU)

#define cFactoryModeMaxKeysToLearn    ((U8) 0x02U)

// amanevd: QAC expects 32 bit word, we are using 8 bit word
#ifndef _QAC_
#define cShiftBy8   ((U8) 8)
#define cShiftBy16  ((U8) 16)
#define cShiftBy24  ((U8) 24)
#else
#define cShiftBy8   ((U32) 8)
#define cShiftBy16  ((U32) 16)
#define cShiftBy24  ((U32) 24)
#endif

#define cKeyNumber1 ((U8)0)
#define cKeyNumber2 ((U8)1)
#define cKeyNumber3 ((U8)2)
#define cKeyNumber4 ((U8)3)

#define cU8Max      ((U8)0xFFU)

//-----------------------------------------------------------------------------
//  Local macros
//
//  #define mMacroName   (MacroDefinition)
//-----------------------------------------------------------------------------
#define mSetExitFactoryModeRequested()    (u8AprFlag |= cExitFactoryMode)
#define mClearExitFactoryModeRequested()  (u8AprFlag &= cNegExitFactoryMode)
#define mExitFactoryModeRequestedIsOn()   ((u8AprFlag & cExitFactoryMode) != 0)
#define mExitFactoryModeRequestedIsOff()  ((u8AprFlag & cExitFactoryMode) == 0)

#define mSetGiveUpAfterSaleModeRequested()   (u8AprFlag |= cGiveUpAfterSaleMode)
#define mClearGiveUpAfterSaleModeRequested() (u8AprFlag &= cNegGiveUpAfterSaleMode)
#define mGiveUpAfterSaleModeRequestedIsOn()  ((u8AprFlag & cGiveUpAfterSaleMode) != 0)
#define mGiveUpAfterSaleModeRequestedIsOff() ((u8AprFlag & cGiveUpAfterSaleMode) == 0)

#define mSetLearningValidation()   (u8AprFlag |= cLearningValidation)
#define mClearLearningValidation() (u8AprFlag &= cNegLearningValidation)
#define mLearningValidationIsOn()  ((u8AprFlag & cLearningValidation) != 0)
#define mLearningValidationIsOff() ((u8AprFlag & cLearningValidation) == 0)

//QACJ 3443:amanevd: Last instance of mDATRead(cTimeOutMERA -> mDATRead -> mDATRead2 -> [mDATRead]) is a concatenation of mDATRead ## DataType## DataName ## TreatmentType()
#define mCalcPlantModeTimeOut() (mTOSConvMsInTimerTick((U32)(u8tmp_app_cle = mDATRead(U8Bit, EEP_tmp_app_cle, Default))*(U32)1000UL))

#define mPlantModeTimeOut()     (CalculatedTmp_app_cle = \
                                    (u8tmp_app_cle == mDATRead(U8Bit, EEP_tmp_app_cle, Default)) \
                                    ? CalculatedTmp_app_cle \
    /*//QACJ 3443:amanevd: Last instance of mDATRead(cTimeOutMERA -> mDATRead -> mDATRead2 -> [mDATRead]) is a concatenation of mDATRead ## DataType## DataName ## TreatmentType()*/ \
                                    : mCalcPlantModeTimeOut())

//QACJ 3443:amanevd: Last instance of mDATRead(cTimeOutMERA -> mDATRead -> mDATRead2 -> [mDATRead]) is a concatenation of mDATRead ## DataType## DataName ## TreatmentType()
#define mCalcAfterSaleTimeOut() (mTOSConvMsInTimerTick((U32)(u8timeout_app_cle = mDATRead(U8Bit, EEP_timeout_app_cle, Default))*(U32)60000UL))

#define mAfterSaleTimeOut() (CalculatedTimeout_app_cle = \
                                (u8timeout_app_cle == mDATRead(U8Bit, EEP_timeout_app_cle, Default)) \
                                ? CalculatedTimeout_app_cle \
    /*//QACJ 3443:amanevd: Last instance of mDATRead(cTimeOutMERA -> mDATRead -> mDATRead2 -> [mDATRead]) is a concatenation of mDATRead ## DataType## DataName ## TreatmentType()*/ \
                                : mCalcAfterSaleTimeOut())

//-----------------------------------------------------------------------------
//  Local types
//
//  struct  sStructureName { ... };
//  union   uUnionName { ... };
//  enum    eEnumerationName { ... };
//  typedef Expression tTypeName;
//-----------------------------------------------------------------------------
typedef struct sLowHighSKType
{
    U32  SKLow;
    U16  SKHigh;
} sLowHighSK;

typedef union uSecretKeyType
//QACJ 0750:amanevd: Union is used to optimize memory and cpu usage
{  
    sLowHighSK  SK;
    U8          SecretKey[cDATTrpISKLengthInBytes];
} uSecretKey;

typedef U8 tKeyType;
//-----------------------------------------------------------------------------
//  Local data
//
//  static  tType   VariableName;
//  static  tType*  pVariableName; 
//-----------------------------------------------------------------------------
// Timer used to manage after sale mode time out
static tTOSTimer    AfterSaleTimer;
static tTOSTimer    PlantModeTimer;
static tTOSTimer    CalculatedTmp_app_cle;
static tTOSTimer    CalculatedTimeout_app_cle;

static U32  u32TrpIdentifierReceived;
static U32  u32TrpConfigAndPassWordTag;

static U8   ImmobilizerSecretKey[cDATTrpISKLengthInBytes];
static U8   RemoteSecretKey[cDATTrpISKLengthInBytes];
static U8   AfterSaleCode[cDATTrpISKLengthInBytes];
static U16  u16SKey;

static U32          TableOfKeyIdentifierReassigned[cDATTrpMaxNumberOfKey];
static U32          TableOfPassWordTagReassigned[cDATTrpMaxNumberOfKey];
static uSecretKey   TableOfRemoteSecretKeyReassigned[cDATTrpMaxNumberOfKey];
static U32          TableOfResynchroValueReassigned[cDATTrpMaxNumberOfKey];

static U8   u8LearningMode;
static U8   u8AprFlag;

static U8   u8tmp_app_cle;
static U8   u8timeout_app_cle;

static BOOL   bKeyAlreadyLearned;

//-----------------------------------------------------------------------------
//  Constant local data
//
//  static const tType  VariableName;
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//  Exported data
//
//  tType   LAYCmpVariableName;   (LAY: 3 characters to identify the layer)
//  tType*  pLAYCmpVariableName;  (Cmp: 3 characters to identify this component)
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//  Constant exported data
//
//              (LAY: 3 characters to identify the layer)
//              (Cmp: 3 characters to identify this component)
// 
//  const tType   LAYCmpVariableName;
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//  Local function prototypes
//  
//  static tTypeRetour FunctionName(tTypeArgument1 ArgumentName1, ... );
//-----------------------------------------------------------------------------
static MEM_TYPE void MemorizeKeyFrequencyCounter(void);
static MEM_TYPE void WriteRSKInEeprom(const tKeyType u8IndexKeyP, const U8* const pu8RSKP);
static MEM_TYPE void CheckExitConditions(void);
           
#ifdef X90_PROJECT
static MEM_TYPE void LRNLearningModeSuccess_Static(void);
static MEM_TYPE void LRNCalculateTranspCodes_Static(void);
static MEM_TYPE void LRNWriteISKHighIntoTransponder_Static(void);
static MEM_TYPE void LRNWriteRSKErrorAction_Static(void);
static MEM_TYPE void LRNWriteISKLowIntoTransponder_Static(void);
static MEM_TYPE void LRNAuthenticationWithCalculateISK_Static(void);
static MEM_TYPE void LRNResynchroErrorAction_Static(void);
static MEM_TYPE void LRNWriteInEepromTransponderCodes_Static(void);
static MEM_TYPE void LRNCalculateCodesInAfterSaleMode_Static(void);
static MEM_TYPE void LRNWriteInEepromFirstTransponderCodes_Static(void);
static MEM_TYPE void LRNMemorizeTranspAlreadyKnown_Static(void);
static MEM_TYPE void LRNMemoriseNewTransp_Static(void);
static MEM_TYPE BOOL LRNIgnitionON_Static(void);
static MEM_TYPE void LRNLearningModeNotSuccess_Static(void);
static MEM_TYPE void LRNStartLearningInAfterSaleMode_Static(void);
static MEM_TYPE void LRNValidateLearningInAfterSaleMode_Static(void);
static MEM_TYPE void LRNUpdateLearningAuthorizationConditions_Static(void);
static MEM_TYPE void LRNStartLearningInFactoryMode_Static(void);
static MEM_TYPE void LRNAuthenticationWithTransportISK_Static(void);
static MEM_TYPE void LRNMemoTransponderType_Static(void);
static MEM_TYPE void LRNSelectRemoteConfigBlockForRFKey_Static(void);
static MEM_TYPE void LRNWriteRSKHighIntoTransponder_Static(void);
static MEM_TYPE void LRNWriteRSKLowIntoTransponder_Static(void);
static MEM_TYPE void LRNFactoryModeAuthentNewISKNOK_Static(void);
static MEM_TYPE void LRNLockingTransponder_Static(void);
static MEM_TYPE BOOL LRNWritingInEepromFinishedNOK_Static(void);
static MEM_TYPE void LRNCalculateISKandAuthenticate_Static(void);
static MEM_TYPE void LRNAuthenticationWithCarISK_Static(void);
static MEM_TYPE BOOL LRNEnterAfterSaleBCMReplacementMode_Static(void);
static MEM_TYPE BOOL LRNEnterAfterSaleKeyReassigmentMode_Static(void);
static MEM_TYPE BOOL LRNEnterFactoryMode_Static(void);
static MEM_TYPE void LRNUpdateDiagData_Static(void);
static MEM_TYPE void LRNAuthenticationWithCalculatedISKHigh_Static(void);
static MEM_TYPE void LRNAuthenticationWithCalculatedISKLow_Static(void);
static MEM_TYPE BOOL LRNKeyAlreadyLearned_Static(void);
static MEM_TYPE BOOL LRNKeyNotAlreadyRelearnt_Static(void);
#endif

//=============================================================================
//=========================== LOCAL FUNCTIONS =================================
//=============================================================================

//=============================================================================
//  DESCRIPTION :
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//=============================================================================
//static type FunctionName(...)

//=============================================================================
//  DESCRIPTION : Memorize the key frequency counter
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//=============================================================================
static MEM_TYPE void MemorizeKeyFrequencyCounter(void)
{
    U8 u8KeyCounterL;

    switch (mDATRead(U8Bit, DATTrpFrequencyOfPresentKey, Default))
    {
        case cDATTrpKey315Mhz:
        u8KeyCounterL = mDATRead(U8Bit, NumberOfKeys315MHzLearnt, Default);
        mDATWrite(U8Bit, NumberOfKeys315MHzLearnt, (u8KeyCounterL + 1), Default);
        break;

        case cDATTrpKey315MhzSmall:
        u8KeyCounterL = mDATRead(U8Bit, NumberOfKeys315MHzSmallLearnt, Default);
        mDATWrite(U8Bit, NumberOfKeys315MHzSmallLearnt, (u8KeyCounterL + 1), Default);
        break;

        case cDATTrpKey433Mhz:
        u8KeyCounterL = mDATRead(U8Bit, NumberOfKeys433MHzLearnt, Default);
        mDATWrite(U8Bit, NumberOfKeys433MHzLearnt, (u8KeyCounterL + 1), Default);
        break;

        //CCOV: amanevd: Cannot be covered because this default case rises explicit assert
        default:
        mLIBassert(cFalse);
        break;
    }
}

//=============================================================================
//  DESCRIPTION : Write RSK in EEPROM
//  
//  PARAMETERS (Type,Name,Min,Max) : U8 u8IndexKeyP
//                                   U8* pu8RSKP
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//=============================================================================
static MEM_TYPE void WriteRSKInEeprom(const tKeyType u8IndexKeyP, const U8* const pu8RSKP)
{
    U8 u8IndexL;

    mLIBassert(NULL != pu8RSKP);

    switch(u8IndexKeyP)
    {
        case cKeyNumber1:
        for (u8IndexL = 0; u8IndexL < cDATTrpISKLengthInBytes; u8IndexL++)
        {
            //QACJ 0506:amanevd: Function is called in two points with static argument in place of pu8RSKP. For any case pointer is checked in debug mode.
            mDATWriteTable(U8Bit, EEP_RemoteSecretKey1, u8IndexL, pu8RSKP[u8IndexL], Default);
        }
        break;

        case cKeyNumber2:
        for (u8IndexL = 0; u8IndexL < cDATTrpISKLengthInBytes; u8IndexL++)
        {
            mDATWriteTable(U8Bit, EEP_RemoteSecretKey2, u8IndexL, pu8RSKP[u8IndexL], Default);
        }
        break;

        case cKeyNumber3:
        for (u8IndexL = 0; u8IndexL < cDATTrpISKLengthInBytes; u8IndexL++)
        {
            mDATWriteTable(U8Bit, EEP_RemoteSecretKey3, u8IndexL, pu8RSKP[u8IndexL], Default);
        }
        break;

        case cKeyNumber4:
        for (u8IndexL = 0; u8IndexL < cDATTrpISKLengthInBytes; u8IndexL++)
        {
            mDATWriteTable(U8Bit, EEP_RemoteSecretKey4, u8IndexL, pu8RSKP[u8IndexL], Default);
        }
        break;

        //CCOV: amanevd: Cannot be covered because this default case rises explicit assert
        default:
        mLIBassert(cFalse);
        break;
    }
}
//=============================================================================
//  DESCRIPTION : Check Exit Conditions
//  
//  PARAMETERS (Type,Name,Min,Max) : 
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//=============================================================================
static MEM_TYPE void CheckExitConditions(void)
{
    BOOL bTimerStatusL;
    tTOSTimer   TempTimer;

    bTimerStatusL = TOSIsTimerStarted(&AfterSaleTimer);
    if(cFalse != bTimerStatusL)
    {
        //QACJ 3226: amanevd: This is intentional and is checked out for problems.
        TempTimer = mAfterSaleTimeOut();
        bTimerStatusL = TOSIsTimerElapsed(&AfterSaleTimer, TempTimer);
    }

    if ((((u8LearningMode == cBcmReplacement) 
        || (u8LearningMode == cKeyReassignment))  
        && (bTimerStatusL != cFalse))
        || mExitFactoryModeRequestedIsOn()
        || mGiveUpAfterSaleModeRequestedIsOn())
    {
        mClearExitFactoryModeRequested();
        mClearGiveUpAfterSaleModeRequested();
        mClearExitFactoryModeRequested();

        u8LearningMode = cNoLearning;
        mDATWrite(U8Bit, LearningModeInProgress, cDATNoLearningMode, Default);
        mDATWrite(U1Bit, DATTrpKeyLearningElapsed, 1, Default);
    }
}

//=============================================================================
//============================ EXPORTED FUNCTIONS =============================
//=============================================================================

//*****************************************************************************
//  DESCRIPTION : Initialize Learning component.
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void LRNInitialize(void)
{
    u8LearningMode = cNoLearning;

    bKeyAlreadyLearned = cFalse;
    mClearExitFactoryModeRequested();
    mClearGiveUpAfterSaleModeRequested();
    mClearLearningValidation();
}
//*****************************************************************************
//  DESCRIPTION : Active learning component.
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void LRNEnterActiveState(void)
{
    TOSSeqActivateGraph(cTOSSeqGraphIdLRNManageLearningService);
    TOSSeqActivateGraph(cTOSSeqGraphIdLRNUpdateLearningAuthorization);
}
//*****************************************************************************
//  DESCRIPTION : Stop learning component.
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void LRNLeaveActiveState(void)
{
    TOSSeqDeactivateGraph(cTOSSeqGraphIdLRNManageLearningService);
    TOSSeqDeactivateGraph(cTOSSeqGraphIdLRNUpdateLearningAuthorization);
}
//*****************************************************************************
//  DESCRIPTION : Start the service learning in factory mode.
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void LRNStartLearningInFactoryMode(void)
{ 
#ifdef X90_PROJECT
    LRNStartLearningInFactoryMode_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LRNStartLearningInFactoryMode_Static(void)
{
#endif

    mDATWrite(U1Bit, FactoryModeAuthorized, 0, Default);
    mDATWrite(U1Bit, AfterSaleModeAuthorized, 0, Default);

    mClearExitFactoryModeRequested();

    u8LearningMode = cFactoryMode;

    mDATWrite(U8Bit, COD_ERR_APP, cCodeError0h, Default);
    mDATWrite(U8Bit, LearningModeInProgress, cDATFactoryMode, Default);
}
//*****************************************************************************
//  DESCRIPTION : Stop factory mode service.
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void LRNExitFromLearningInFactoryMode(void)
{
    mSetExitFactoryModeRequested();
}
//*****************************************************************************
//  DESCRIPTION : Start an authentication with the transport ISK.
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void LRNAuthenticationWithTransportISK(void)
{
#ifdef X90_PROJECT
    LRNAuthenticationWithTransportISK_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LRNAuthenticationWithTransportISK_Static(void)
{
#endif

    U8 u8IndexL;

    for (u8IndexL = 0; u8IndexL < cDATTrpISKLengthInBytes; u8IndexL++)
    {
        mDATWriteTable(U8Bit, DATTrpISKForAuthent, u8IndexL, mDATReadTable(U8Bit, DATTrpTransportISK, u8IndexL, Default), Default);
    }

    mDATWrite(U1Bit, DATTrpAuthentInLearningMode, 1, Default);
    mDATControl(Trp, cDATTrpAuthenticate);
}

//*****************************************************************************
//  DESCRIPTION : Action if key inserted is not blank
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void LRNKeyNotBlank(void)
{
    if (u8LearningMode == cFactoryMode)
    {
        mDATWrite(U8Bit, COD_ERR_APP, cCodeError11h, Default);
    }
    else // if(u8LearningMode == cKeyReassignment)
    {
        mDATWrite(U8Bit, COD_ERR_APP, cCodeErrorB2h, Default);
    }
}

//*****************************************************************************
//  DESCRIPTION : Action if key is already learned
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void LRNKeyAlreadyLaerned(void)
{
    bKeyAlreadyLearned = cTrue;
    mDATWrite(U8Bit, COD_ERR_APP, cCodeError0h, Default);
}

//*****************************************************************************
//  DESCRIPTION : Test if authentication is not successfully finished
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  cFalse or cTrue
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL LRNAuthenticationNOK(void)
{
    return (mDATRead(U8Bit, DATTrpAuthenticationState, Default) == cDATTrpServiceNotSuccessful);
}

//*****************************************************************************
//  DESCRIPTION : Special case for last authent with written ISK in Factory
//                  and AfterSale mode
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  cFalse or cTrue
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL LRNAfterSaleTimeoutElapsed(void)
{
    BOOL bTimerElapsedL = cFalse;
    tTOSTimer   TempTimer;
     
    if(u8LearningMode == cKeyReassignment)
    {
        //QACJ 3226: amanevd: This is intentional and is checked out for problems.
        TempTimer = mAfterSaleTimeOut();
        bTimerElapsedL = TOSIsTimerElapsed(&AfterSaleTimer, TempTimer);
    }

    return (cFalse != bTimerElapsedL);
}

//*****************************************************************************
//  DESCRIPTION : Test if authentication is successfully finished
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  cFalse or cTrue
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL LRNAuthenticationOK(void)
{
    BOOL bResultL = cFalse;
    if (mDATRead(U8Bit, DATTrpAuthenticationState, Default) == cDATTrpServiceSuccessful)
    {
        bResultL = cTrue;
    }

    return bResultL; 
}

//*****************************************************************************
//  DESCRIPTION : Test if key has been learned and IDE is in EEPROM
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  cFalse or cTrue
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL LRNKeyAlreadyLearned(void)
{
#ifdef X90_PROJECT
    return LRNKeyAlreadyLearned_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL LRNKeyAlreadyLearned_Static(void)
{
#endif
    BOOL    bResultL = cFalse;
    U8      u8IndexL;

    if(     (mDATRead(U1Bit, EEP_BCMBlank, Default) == 0)
        &&  (u8LearningMode == cFactoryMode)
      )
    {
        for (u8IndexL = 0; (u8IndexL < mDATRead(U8Bit, NumberOfKeysLearnt, Default)); u8IndexL++)
        {
            if (mDATReadTable(U32Bit, EEP_KeyIdentifier, u8IndexL, Default)
                == mDATRead(U32Bit, DATTrpIdentifierOfPresentKey, Default))
            {
                bResultL = cTrue;
            }
        }
    }

    return bResultL;
}
//*****************************************************************************
//  DESCRIPTION : Store into ram the transponder configuration and its password
//                tag.
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document (REQ: prsFS_IMMO-933)
//*****************************************************************************
void LRNMemoTransponderType(void)
{
#ifdef X90_PROJECT
    LRNMemoTransponderType_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LRNMemoTransponderType_Static(void)
{
#endif

    // Store the identifier of the transponder
    u32TrpIdentifierReceived = mDATRead(U32Bit, DATTrpIdentifierOfPresentKey, Default);

    // Store the content of the page 3 of block 0 of the transponder memory
    u32TrpConfigAndPassWordTag = mDATRead(U32Bit, DATTrpDataRead, Default);
}

//*****************************************************************************
//  DESCRIPTION : Test if current key is locked.
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  cFalse or cTrue
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL LRNKeyIsLocked(void)
{
    return (mDATRead(U1Bit, DATTrpPresentKeyLocked, Default) != 0);
}
//*****************************************************************************
//  DESCRIPTION : Test if current key can be learnt.
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  cFalse or cTrue
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL LRNKeyOKforLearning(void)
{
    return (BOOL)(   (mDATRead(U1Bit, DATTrpKeyWithRF, Default) == 0)
    || ((u32TrpConfigAndPassWordTag & cValueBitBStoOne) == 0UL));
}
//*****************************************************************************
//  DESCRIPTION : Select remote config block in transponder with RF memory.
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void LRNSelectRemoteConfigBlockForRFKey(void)
{
#ifdef X90_PROJECT
    LRNSelectRemoteConfigBlockForRFKey_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LRNSelectRemoteConfigBlockForRFKey_Static(void)
{
#endif

    // Put bit BS to 0
    u32TrpConfigAndPassWordTag &= cPutBitBStoZero;

    mDATWrite(U1Bit, DATTrpWriteSecretKeyHigh, 0, Default);
    mDATWrite(U32Bit, DATTrpDataToWrite, u32TrpConfigAndPassWordTag, Default);
    mDATWrite(U8Bit, DATTrpPageNumber, cPage3, Default);
    mDATControl(Trp, cDATTrpWritePage);
}
//*****************************************************************************
//  DESCRIPTION : Test if ISK writing in transponder memory is finished 
//                successfully.
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  cFalse or cTrue
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL LRNWritingISKFinishedOK(void)
{
    BOOL bResultL = cFalse;

    if (mDATRead(U8Bit, DATTrpWriteAccessState, Default) == cDATTrpServiceSuccessful)
    {
        mDATWrite(U1Bit, ISKSuccessfullyWritten, 1, Default);
        bResultL = cTrue;
    }
    return (bResultL);
}
//*****************************************************************************
//  DESCRIPTION : Test if RSK writing in transponder memory is finished 
//                successfully.
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  cFalse or cTrue
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL LRNWritingRSKFinishedOK(void)
{
    BOOL bResultL = cFalse;

    if (mDATRead(U8Bit, DATTrpWriteAccessState, Default) == cDATTrpServiceSuccessful)
    {
        mDATWrite(U1Bit, RSKSuccessfullyWritten, 1, Default);
        bResultL = cTrue;
    }
    return (bResultL);
}
//*****************************************************************************
//  DESCRIPTION : Test if writing in transponder memory is finished not 
//                successfully.
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  cFalse or cTrue
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL LRNWritingFinishedNOK(void)
{
    return (mDATRead(U8Bit, DATTrpWriteAccessState, Default) == cDATTrpServiceNotSuccessful);
}
//*****************************************************************************
//  DESCRIPTION : Test if writing in transponder memory is finished successfully.
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  cFalse or cTrue
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL LRNWritingFinishedOK(void)
{
    return (mDATRead(U8Bit, DATTrpWriteAccessState, Default) == cDATTrpServiceSuccessful);
}
//*****************************************************************************
//  DESCRIPTION : Calculate codes for the key transponder.
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void LRNCalculateTranspCodes(void)
{
#ifdef X90_PROJECT
    LRNCalculateTranspCodes_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LRNCalculateTranspCodes_Static( void )
{
#endif

    U8  u8IndexL;

    if (   (mDATRead(U8Bit, NumberOfKeysLearnt, Default) == 0)
    && (mDATRead(U1Bit, EEP_BCMBlank, Default) != 0) )
    {
        // For the learning of the first key
        // Generate ISK, After sale code and VERLOG code
        mDATWrite(U32Bit, DATAprIdentifier, u32TrpIdentifierReceived, Default);
        mDATWrite(U32Bit, DATAprPasswordTag, (u32TrpConfigAndPassWordTag & cMaskKeep24Bits), Default);
        mDATControl(Apr, cDATAprComputeISK);
        mDATControl(Apr, cDATAprComputeAfterSaleCode);
        mDATControl(Apr, cDATAprComputeSKey);

        for (u8IndexL = 0; u8IndexL < cDATTrpISKLengthInBytes; u8IndexL++)
        {
            ImmobilizerSecretKey[u8IndexL] = mDATReadTable(U8Bit, DATAprImmobilizerSecretKey, u8IndexL, Default);
            AfterSaleCode[u8IndexL]        = mDATReadTable(U8Bit, DATAprAfterSaleCode, u8IndexL, Default);
        }

        u16SKey = mDATRead(U16Bit, DATAprSKey, Default);
    }

    // Generate RSK for transponder with RF function
    mDATWrite(U32Bit, DATAprIdentifier, u32TrpIdentifierReceived, Default);
    mDATControl(Apr, cDATAprComputeRSK);
    for (u8IndexL = 0; u8IndexL < cDATTrpISKLengthInBytes; u8IndexL++)
    {
        RemoteSecretKey[u8IndexL] = mDATReadTable(U8Bit, DATAprRemoteSecretKey, u8IndexL, Default);    
    }
}
//*****************************************************************************
//  DESCRIPTION : Test if transponder has RF function
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  cFalse or cTrue
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL LRNKeyTypeWithRF(void)
{
    return (mDATRead(U1Bit, DATTrpKeyWithRF, Default) != 0);
}
//*****************************************************************************
//  DESCRIPTION : Start writing of RSK High into transponder memory
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void LRNWriteRSKHighIntoTransponder(void)
{
#ifdef X90_PROJECT
    LRNWriteRSKHighIntoTransponder_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LRNWriteRSKHighIntoTransponder_Static(void)
{
#endif

    U32 u32DataPageToWriteL;

    u32DataPageToWriteL  = ((U32)RemoteSecretKey[cSKIndex5]);
    u32DataPageToWriteL |= ((U32)RemoteSecretKey[cSKIndex4] << cShiftBy8);

    // Start the writing of the RSK High into the transponder memory
    mDATWrite(U1Bit, DATTrpWriteSecretKeyHigh, 1, Default);
    mDATWrite(U32Bit, DATTrpDataToWrite, u32DataPageToWriteL, Default);
    mDATWrite(U8Bit, DATTrpPageNumber, cPage5, Default);
    mDATControl(Trp, cDATTrpWritePage);
}
//*****************************************************************************
//  DESCRIPTION : Start writing of RSK Low into transponder memory
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void LRNWriteRSKLowIntoTransponder(void)
{
#ifdef X90_PROJECT
    LRNWriteRSKLowIntoTransponder_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LRNWriteRSKLowIntoTransponder_Static(void)
{
#endif

    U32 u32DataPageToWriteL;

    u32DataPageToWriteL  = ((U32)RemoteSecretKey[cSKIndex0] << cShiftBy24);
    u32DataPageToWriteL |= ((U32)RemoteSecretKey[cSKIndex1] << cShiftBy16); 
    u32DataPageToWriteL |= ((U32)RemoteSecretKey[cSKIndex2] << cShiftBy8);
    u32DataPageToWriteL |= ((U32)RemoteSecretKey[cSKIndex3]);  

    // Start the writing of the RSK Low into the transponder memory
    mDATWrite(U1Bit, DATTrpWriteSecretKeyHigh, 0, Default);
    mDATWrite(U32Bit, DATTrpDataToWrite, u32DataPageToWriteL, Default);
    mDATWrite(U8Bit, DATTrpPageNumber, cPage4, Default);
    mDATControl(Trp, cDATTrpWritePage);
}
//*****************************************************************************
//  DESCRIPTION : Start writing of ISK High into transponder memory
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void LRNWriteISKHighIntoTransponder(void)
{
#ifdef X90_PROJECT
    LRNWriteISKHighIntoTransponder_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LRNWriteISKHighIntoTransponder_Static(void)
{
#endif

    U32 u32DataPageToWriteL;
    U8  u8IndexL;

    if (mDATRead(U1Bit, EEP_BCMBlank, Default) == 0)
    {
        u32DataPageToWriteL  = ((U32)mDATReadTable(U8Bit, EEP_ImmoSecretKey, cSKIndex5, Default));
        u32DataPageToWriteL |= ((U32)mDATReadTable(U8Bit, EEP_ImmoSecretKey, cSKIndex4, Default) << cShiftBy8);

        for (u8IndexL = 0; u8IndexL < (cDATTrpISKLengthInBytes - cSKIndex2); u8IndexL++)
        {
            mDATWriteTable(U8Bit, DATTrpISKForAuthent, u8IndexL, mDATReadTable(U8Bit, EEP_ImmoSecretKey, u8IndexL, Default), Default);
        }    
    }
    else
    {    
        u32DataPageToWriteL  = ((U32)ImmobilizerSecretKey[cSKIndex5]);
        u32DataPageToWriteL |= ((U32)ImmobilizerSecretKey[cSKIndex4] << cShiftBy8);

        for (u8IndexL = 0; u8IndexL < (cDATTrpISKLengthInBytes - cSKIndex2); u8IndexL++)
        {
            mDATWriteTable(U8Bit, DATTrpISKForAuthent, u8IndexL, ImmobilizerSecretKey[u8IndexL], Default);
        }
    }
    mDATWriteTable(U8Bit, DATTrpISKForAuthent, cSKIndex4, mDATReadTable(U8Bit, DATTrpTransportISK, cSKIndex4, Default), Default);
    mDATWriteTable(U8Bit, DATTrpISKForAuthent, cSKIndex5, mDATReadTable(U8Bit, DATTrpTransportISK, cSKIndex5, Default), Default);

    // Start the writing of the ISK High into the transponder memory
    mDATWrite(U1Bit, DATTrpWriteSecretKeyHigh, 1, Default);
    mDATWrite(U32Bit, DATTrpDataToWrite, u32DataPageToWriteL, Default);
    mDATWrite(U8Bit, DATTrpPageNumber, cPage2, Default);
    mDATControl(Trp, cDATTrpWritePage);
}
//*****************************************************************************
//  DESCRIPTION : Write RSK Error Action
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void LRNWriteRSKErrorAction(void)
{
#ifdef X90_PROJECT
    LRNWriteRSKErrorAction_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LRNWriteRSKErrorAction_Static( void )
{
#endif

    if (u8LearningMode == cFactoryMode)
    {
        if(cFalse != mDATRead(U1Bit, DATTrpWriteAccessWritingError, Default))
        {
            mDATWrite(U8Bit, COD_ERR_APP, cCodeError14h, Default);
        }
        else if(cFalse != mDATRead(U1Bit, DATTrpWriteAccessReadingError, Default))
        {
            mDATWrite(U8Bit, COD_ERR_APP, cCodeError15h, Default);
        }
        else
        {
            //Nothing to do
        }
    }
    else // if(u8LearningMode == cKeyReassignment)
    {
        mDATWrite(U8Bit, COD_ERR_APP, cCodeErrorB5h, Default);
    }
}
//*****************************************************************************
//  DESCRIPTION : Start writing of ISK Low into transponder memory
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void LRNWriteISKLowIntoTransponder(void)
{
#ifdef X90_PROJECT
    LRNWriteISKLowIntoTransponder_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LRNWriteISKLowIntoTransponder_Static( void )
{
#endif

    U32 u32DataPageToWriteL;
    U8  u8IndexL;

    for (u8IndexL = 0; u8IndexL < cDATTrpISKLengthInBytes; u8IndexL++)
    {
        mDATWriteTable(U8Bit, DATTrpISKForAuthent, u8IndexL, mDATReadTable(U8Bit, DATTrpTransportISK, u8IndexL, Default), Default);
    }

    if (mDATRead(U1Bit, EEP_BCMBlank, Default) != 0)
    {
        u32DataPageToWriteL  = ((U32)ImmobilizerSecretKey[cSKIndex0] << cShiftBy24);
        u32DataPageToWriteL |= ((U32)ImmobilizerSecretKey[cSKIndex1] << cShiftBy16);
        u32DataPageToWriteL |= ((U32)ImmobilizerSecretKey[cSKIndex2] << cShiftBy8);
        u32DataPageToWriteL |= ((U32)ImmobilizerSecretKey[cSKIndex3]);
    }
    else
    {
        u32DataPageToWriteL  = ((U32)mDATReadTable(U8Bit, EEP_ImmoSecretKey, cSKIndex0, Default) << cShiftBy24);
        u32DataPageToWriteL |= ((U32)mDATReadTable(U8Bit, EEP_ImmoSecretKey, cSKIndex1, Default) << cShiftBy16);
        u32DataPageToWriteL |= ((U32)mDATReadTable(U8Bit, EEP_ImmoSecretKey, cSKIndex2, Default) << cShiftBy8);
        u32DataPageToWriteL |= ((U32)mDATReadTable(U8Bit, EEP_ImmoSecretKey, cSKIndex3, Default));
    }  

    // Start the writing of the ISK Low into the transponder memory
    mDATWrite(U1Bit, DATTrpWriteSecretKeyHigh, 0, Default);
    mDATWrite(U32Bit, DATTrpDataToWrite, u32DataPageToWriteL, Default);
    mDATWrite(U8Bit, DATTrpPageNumber, cPage1, Default);
    mDATControl(Trp, cDATTrpWritePage);
}

//*****************************************************************************
//  DESCRIPTION : Start immobilizer antenna sleep control
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void LRNPutImmobilizerAntennaInSleepMode(void)
{
    mDATControl(Trp, cDATTrpSleep);
}
//*****************************************************************************
//  DESCRIPTION : Test if sleep control finished not successfully
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  cFalse or cTrue
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL LRNSleepModeNOK(void)
{
    return (mDATRead(U8Bit, DATTrpSleepControlState, Default) == cDATTrpServiceNotSuccessful);
}
//*****************************************************************************
//  DESCRIPTION : Test if sleep control finished successfully
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  cFalse or cTrue
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL LRNSleepModeOK(void)
{
    return (mDATRead(U8Bit, DATTrpSleepControlState, Default) == cDATTrpServiceSuccessful);
}
//*****************************************************************************
//  DESCRIPTION : Start authentication with the last calculated ISK.
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void LRNAuthenticationWithCalculateISK(void)
{
#ifdef X90_PROJECT
    LRNAuthenticationWithCalculateISK_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LRNAuthenticationWithCalculateISK_Static( void )
{
#endif

    U8 u8IndexL;

    if (mDATRead(U1Bit, EEP_BCMBlank, Default) == 0)
    {
        for (u8IndexL = 0; u8IndexL < cDATTrpISKLengthInBytes; u8IndexL++)
        {
            mDATWriteTable(U8Bit, DATTrpISKForAuthent, u8IndexL, mDATReadTable(U8Bit, EEP_ImmoSecretKey, u8IndexL, Default), Default);
        }    
    }
    else
    {
        for (u8IndexL = 0; u8IndexL < cDATTrpISKLengthInBytes; u8IndexL++)
        {
            mDATWriteTable(U8Bit, DATTrpISKForAuthent, u8IndexL, ImmobilizerSecretKey[u8IndexL], Default);
        }
    }

    mDATWrite(U1Bit, DATTrpAuthentInLearningMode, 1, Default);
    mDATControl(Trp, cDATTrpAuthenticate);
}

//*****************************************************************************
//  DESCRIPTION : 
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void LRNFactoryModeAuthentNewISKNOK(void)
{
#ifdef X90_PROJECT
    LRNFactoryModeAuthentNewISKNOK_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LRNFactoryModeAuthentNewISKNOK_Static(void)
{
#endif

    mDATWrite(U1Bit, DATTrpKeyLearningElapsed, 1, Default);

    if (u8LearningMode == cFactoryMode)
    {
        mDATWrite(U8Bit, COD_ERR_APP, cCodeError13h, Default);    
    }
    else // if(u8LearningMode == cKeyReassignment)
    {
        mDATWrite(U8Bit, COD_ERR_APP, cCodeErrorB4h, Default);
    }
}

//*****************************************************************************
//  DESCRIPTION : Test if resynchronization service is finished not successfully.
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  cFalse or cTrue
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL LRNResynchroFinishedNOK(void)
{
    return (mDATRead(U8Bit, DATTrpResynchronizationState, Default) == cDATTrpServiceNotSuccessful);
}
//*****************************************************************************
//  DESCRIPTION : Test if resynchronization service is finished successfully.
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  cFalse or cTrue
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL LRNResynchroFinishedOK(void)
{
    BOOL bResultL = cFalse;

    if (mDATRead(U8Bit, DATTrpResynchronizationState, Default) == cDATTrpServiceSuccessful)
    {
        mDATWrite(U1Bit, SynchroSuccessfullyWritten, 1, Default);
        bResultL = cTrue;
    }
    return (bResultL);
}
//*****************************************************************************
//  DESCRIPTION : Start resynchronization service.
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void LRNResynchronizeTransponder(void)
{
    mDATWrite(U1Bit, DATTrpWriteSecretKeyHigh, 0, Default);
    mDATControl(Trp, cDATTrpResynchronize);
}

//*****************************************************************************
//  DESCRIPTION : Bcm Replacement Resynchronization failure error code
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void LRNBcmReplacementResyncNOK(void)
{
    mDATWrite(U8Bit, COD_ERR_APP, cCodeErrorA2h, Default);
}

//*****************************************************************************
//  DESCRIPTION : Resynchro Error Action.
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void LRNResynchroErrorAction(void)
{
#ifdef X90_PROJECT
    LRNResynchroErrorAction_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LRNResynchroErrorAction_Static( void )
{
#endif

    if (u8LearningMode == cFactoryMode)
    {
        if(cFalse != mDATRead(U1Bit, DATTrpWriteAccessWritingError, Default))
        {
            mDATWrite(U8Bit, COD_ERR_APP, cCodeError16h, Default);
        }
        else if(cFalse != mDATRead(U1Bit, DATTrpWriteAccessReadingError, Default))
        {
            mDATWrite(U8Bit, COD_ERR_APP, cCodeError17h, Default);
        }
        else
        {
            //Nothing to do
        }
    }
    else // if(u8LearningMode == cKeyReassignment)
    {
        mDATWrite(U8Bit, COD_ERR_APP, cCodeErrorB6h, Default);
    }
}

//*****************************************************************************
//  DESCRIPTION : Test if key locking is authorized.
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  cFalse or cTrue
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL LRNLockingTrpIsAuthorized(void)
{
    return (0 == mDATRead(U1Bit, EEP_CALULKTR, Default));
}
//*****************************************************************************
//  DESCRIPTION : Start locking of transponder
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void LRNLockingTransponder(void)
{  
#ifdef X90_PROJECT
    LRNLockingTransponder_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LRNLockingTransponder_Static(void)
{
#endif

    if (mDATRead(U1Bit, DATTrpKeyWithRF, Default) != 0)
    {
        u32TrpConfigAndPassWordTag |= cLockRFKey;
    }
    else
    {
        u32TrpConfigAndPassWordTag |= cLockNonRFKey;
    }

    mDATWrite(U1Bit, DATTrpWriteSecretKeyHigh, 0, Default);
    mDATWrite(U32Bit, DATTrpDataToWrite, u32TrpConfigAndPassWordTag, Default);
    mDATWrite(U8Bit, DATTrpPageNumber, cPage3, Default);
    mDATControl(Trp, cDATTrpWritePage);
}

//*****************************************************************************
//  DESCRIPTION : Locking Transponder Error
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void LRNLockingTransponderError(void)
{  
    if (u8LearningMode == cFactoryMode)
    {
        mDATWrite(U8Bit, COD_ERR_APP, cCodeError18h, Default);
    }
    else // if(u8LearningMode == cKeyReassignment)
    {
        mDATWrite(U8Bit, COD_ERR_APP, cCodeErrorB7h, Default);
    }
}

//*****************************************************************************
//  DESCRIPTION : Indicate that the transponder memory is locked.
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void LRNKeyLockedForEver(void)
{
    mDATWrite(U1Bit, DATTrpPresentKeyLocked, 1, Default);
}
//*****************************************************************************
//  DESCRIPTION : Start writing of all transponder data in BCM EEPROM.
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void LRNWriteInEepromTransponderCodes(void)
{
#ifdef X90_PROJECT
    LRNWriteInEepromTransponderCodes_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LRNWriteInEepromTransponderCodes_Static(void)
{
#endif

    U8 u8IndexL;
    U32 u32RandomValue;
    tKeyType KeyNumberL;

    KeyNumberL = (tKeyType)mDATRead(U8Bit, NumberOfKeysLearnt, Default);

    if (KeyNumberL == cKeyNumber1)
    {   
        // Store in Eeprom the ISK calculated, 
        // the VERLOG code calculated and the encoded After Sale code
        for (u8IndexL = 0; u8IndexL < cDATTrpISKLengthInBytes; u8IndexL++)
        {
            mDATWriteTable(U8Bit, EEP_ImmoSecretKey, u8IndexL, ImmobilizerSecretKey[u8IndexL], Default);
            mDATWriteTable(U8Bit, DATAprAfterSaleCode, u8IndexL, AfterSaleCode[u8IndexL], Default);
        }
        mDATWrite(U16Bit, EEP_VerlogSKey, u16SKey, Default);

        mDATControl(Apr, cDATAprWriteAfterSaleCode);
    }

    // Store the Identifier and Password received after the Authentication sequence
    mDATWriteTable(U32Bit, EEP_KeyIdentifier, KeyNumberL, u32TrpIdentifierReceived, Default);
    mDATWriteTable(U32Bit, EEP_PwdTag, KeyNumberL, (u32TrpConfigAndPassWordTag & cMaskKeep24Bits), Default);

    // If transponder has the RF function
    if (mDATRead(U1Bit, DATTrpKeyWithRF, Default) != 0)
    {
        // Store into Eeprom the random number of Resynchro
        mDATWriteTable(U32Bit, EEP_InitialResynchroValue, KeyNumberL, mDATRead(U32Bit, DATTrpResynchronizationValue, Default), Default);
        mDATWriteTable(U32Bit, EEP_SI28Bits, KeyNumberL, mDATRead(U32Bit, DATTrpResynchronizationValue, Default), Default);

        // Store into Eeprom RSK
        WriteRSKInEeprom(KeyNumberL, RemoteSecretKey);

        MemorizeKeyFrequencyCounter();
    }

    // Fill unused key passwords with random values
    for (u8IndexL = KeyNumberL+1; u8IndexL < cDATTrpMaxNumberOfKey; u8IndexL++)
    {
        u32RandomValue = LIBCalculateRandomNb(TOSClock);
        mDATWriteTable(U32Bit, EEP_PwdTag, u8IndexL, u32RandomValue, Default);
    }
}

//*****************************************************************************
//  DESCRIPTION : Eeprom Writing Error.
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void LRNEepromWritingError(void)
{
    mDATWrite(U8Bit, COD_ERR_APP, cCodeError19h, Default);
}

//*****************************************************************************
//  DESCRIPTION : Test if writing in EEPROM is finished not successfully.
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  cFalse or cTrue
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL LRNWritingInEepromFinishedNOK(void)
{
#ifdef X90_PROJECT
    return LRNWritingInEepromFinishedNOK_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL LRNWritingInEepromFinishedNOK_Static(void)
{
#endif

    BOOL bResultL = cFalse;

    if (   (mDATRead(U1Bit, IsEepGroupStaticImmoBankProcessing, Default) == 0)
    && (mDATRead(U1Bit, IsEepGroupDynamicImmoDataBankProcessing, Default) == 0) )      
    {
        //-----------------------------------------------------------------//
        // Set Eeprom writing error flag according to the mode in progress
        //-----------------------------------------------------------------//

        if (u8LearningMode == cFactoryMode)
        {
            switch ((tKeyType)mDATRead(U8Bit, NumberOfKeysLearnt, Default))
            {
                case cKeyNumber1:
                mDATWrite(U1Bit, WritingErrorInEepForKey1InFactoryMode, 1, Default);
                break;

                case cKeyNumber2:
                mDATWrite(U1Bit, WritingErrorInEepForKey2InFactoryMode, 1, Default);
                break;

                //CCOV: amanevd: Cannot be covered because this default case rises explicit assert
                default:
                mLIBassert(cFalse);
                break;
            }
        }
        else
        {
            mDATWrite(U1Bit, WritingErrorInEepInBcmReplacement, 1, Default);
        }
        bResultL = cTrue;
    }
    return bResultL;
}
//*****************************************************************************
//  DESCRIPTION : Test if writing in EEPROM is finished successfully.
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  cFalse or cTrue
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL LRNWritingInEepromFinishedOK(void)
{ 
    return (   (mDATRead(U1Bit, IsEepGroupStaticImmoBankProcessing, Default) == 0)
    && (mDATRead(U1Bit, IsEepGroupDynamicImmoDataBankProcessing, Default) == 0)
    && (mDATRead(U1Bit, IsEepGroupStaticImmoBankWriteOk, Default) != 0)
    && (mDATRead(U1Bit, IsEepGroupDynamicImmoDataBankWriteOk, Default) != 0) );
}
//*****************************************************************************
//  DESCRIPTION : Test if base-station sleep control is finished successfully.
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  cFalse or cTrue
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL LRNSleepModeFinished(void)
{ 
    return mDATRead(U8Bit, DATTrpSleepControlState, Default) != cDATTrpServiceInProgress;
}
//*****************************************************************************
//  DESCRIPTION : Compute ISK from the After Sale code and start authentication
//                service with the calculate ISK.
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void LRNCalculateISKandAuthenticate(void)
{
#ifdef X90_PROJECT
    LRNCalculateISKandAuthenticate_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LRNCalculateISKandAuthenticate_Static(void)
{
#endif

    U8 u8IndexL;

    mDATControl(Apr, cDATAprComputeISKFromDiagAfterSaleCode);

    for (u8IndexL = 0; u8IndexL < cDATTrpISKLengthInBytes; u8IndexL++)
    {
        ImmobilizerSecretKey[u8IndexL] = mDATReadTable(U8Bit, DATAprImmobilizerSecretKey, u8IndexL, Default);
        mDATWriteTable(U8Bit, DATTrpISKForAuthent, u8IndexL, ImmobilizerSecretKey[u8IndexL], Default);
    }

    mDATWrite(U1Bit, DATTrpAuthentInLearningMode, 1, Default);
    mDATControl(Trp, cDATTrpAuthenticate);
}
//*****************************************************************************
//  DESCRIPTION : Authentication with calculated ISK in BCM Replacement mode failed.
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void LRNBCMReplacementAuthentError(void)
{
    mDATWrite(U8Bit, COD_ERR_APP, cCodeErrorA1h, Default);
}

//*****************************************************************************
//  DESCRIPTION : Calculate transponder codes from the After Sale code
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void LRNCalculateCodesInAfterSaleMode(void)
{
#ifdef X90_PROJECT
    LRNCalculateCodesInAfterSaleMode_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LRNCalculateCodesInAfterSaleMode_Static(void)
{
#endif

    U8  u8IndexL;

    // Diag AFS code is ok
    mDATWrite(U1Bit,AFSCodeIsOk,1,Default);

    // Generate new VERLOG code
    for (u8IndexL = 0; u8IndexL < cDATTrpISKLengthInBytes; u8IndexL++)
    {
        mDATWriteTable(U8Bit, DATAprImmobilizerSecretKey, u8IndexL, ImmobilizerSecretKey[u8IndexL], Default);
    }
    mDATControl(Apr, cDATAprComputeSKey);

    u16SKey = mDATRead(U16Bit, DATAprSKey, Default);

    // Compute the RSK of the current key
    mDATWrite(U32Bit, DATAprIdentifier, u32TrpIdentifierReceived, Default);

    // If transponder has the RF function
    if (mDATRead(U1Bit, DATTrpKeyWithRF, Default) != 0)
    {
        mDATControl(Apr, cDATAprComputeRSK);

        // Store RSK
        for (u8IndexL = 0; u8IndexL < cDATTrpISKLengthInBytes; u8IndexL++)
        {
            RemoteSecretKey[u8IndexL] = mDATReadTable(U8Bit, DATAprRemoteSecretKey, u8IndexL, Default);
        }
    }
}

//*****************************************************************************
//  DESCRIPTION : Authentication with calculated ISK in BCM Replacement mode.
//                In order to prepare for resync.
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void LRNAuthentWithCorrectISK(void)
{
    mDATControl(Trp, cDATTrpAuthenticate);
}

//*****************************************************************************
//  DESCRIPTION : Store in EEPROM the transponder codes of a the key used for 
//                a BCM replacement.
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void LRNWriteInEepromFirstTransponderCodes(void)
{
#ifdef X90_PROJECT
    LRNWriteInEepromFirstTransponderCodes_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LRNWriteInEepromFirstTransponderCodes_Static( void )
{
#endif

    U8  u8IndexL;
    U32 u32RandomValue;

    // Store in Eeprom the ISK calculated and the VERLOG code calculated
    for (u8IndexL = 0; u8IndexL < cDATTrpISKLengthInBytes; u8IndexL++)
    {
        mDATWriteTable(U8Bit, EEP_ImmoSecretKey, u8IndexL, ImmobilizerSecretKey[u8IndexL], Default);
        mDATWriteTable(U8Bit, EEP_AfterSalesCode, u8IndexL, 0, Default);
    }
    mDATWrite(U16Bit, EEP_VerlogSKey, u16SKey, Default);

    // Store the Identifier and Password received after the Authentication sequence
    mDATWriteTable(U32Bit, EEP_KeyIdentifier, 0, u32TrpIdentifierReceived, Default);
    mDATWriteTable(U32Bit, EEP_PwdTag, 0, (u32TrpConfigAndPassWordTag & cMaskKeep24Bits), Default);

    // If transponder has the RF function
    if (mDATRead(U1Bit, DATTrpKeyWithRF, Default) != 0)
    {
        // Store the random number of Resynchro in Eeprom 
        mDATWriteTable(U32Bit, EEP_InitialResynchroValue, 0, mDATRead(U32Bit, DATTrpResynchronizationValue, Default), Default);
        mDATWriteTable(U32Bit, EEP_SI28Bits, 0, mDATRead(U32Bit, DATTrpResynchronizationValue, Default), Default);

        // Store RSK in Eeprom 
        WriteRSKInEeprom(cKeyNumber1, RemoteSecretKey);

        MemorizeKeyFrequencyCounter();
    }

    // Fill unused key passwords with random values
    for (u8IndexL = 1; u8IndexL < cDATTrpMaxNumberOfKey; u8IndexL++)
    {
        u32RandomValue = LIBCalculateRandomNb(TOSClock);
        mDATWriteTable(U32Bit, EEP_PwdTag, u8IndexL, u32RandomValue, Default);
    }
}
//*****************************************************************************
//  DESCRIPTION : Start Authentication service with ISK from BCM EEPROM
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void LRNAuthenticationWithCarISK(void)
{
#ifdef X90_PROJECT
    LRNAuthenticationWithCarISK_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LRNAuthenticationWithCarISK_Static(void)
{
#endif

    U8 u8IndexL;

    for (u8IndexL = 0; u8IndexL < cDATTrpISKLengthInBytes; u8IndexL++)
    {
        mDATWriteTable(U8Bit, DATTrpISKForAuthent, u8IndexL, mDATReadTable(U8Bit, EEP_ImmoSecretKey, u8IndexL, Default), Default);
    }

    mDATWrite(U1Bit, DATTrpAuthentInLearningMode, 1, Default);
    mDATControl(Trp, cDATTrpAuthenticate);
}
//*****************************************************************************
//  DESCRIPTION : Test if the current transponder is not already learnt
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  cFalse or cTrue
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL LRNKeyNotAlreadyRelearnt(void)
{
#ifdef X90_PROJECT
    return LRNKeyNotAlreadyRelearnt_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL LRNKeyNotAlreadyRelearnt_Static(void)
{
#endif

    U8   u8IndexL;
    BOOL bKeyUnknownL = cTrue;

    for (u8IndexL = 0; (u8IndexL < mDATRead(U8Bit, NumberOfKeysLearnt, Default)) && (bKeyUnknownL != cFalse); u8IndexL++)
    {
        if (TableOfKeyIdentifierReassigned[u8IndexL] == mDATRead(U32Bit, DATTrpIdentifierOfPresentKey, Default))
        {
            bKeyUnknownL = cFalse;
        }
    }
    return (bKeyUnknownL);
}
//*****************************************************************************
//  DESCRIPTION : Test if the current transponder is known by the BCM
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  cFalse or cTrue
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL LRNKeyKnownByBCM(void)
{
    return (mDATRead(U8Bit, DATTrpIndexOfKeyRecognized, Default) != cDATTrpInvalidKeyIndex);
}
//*****************************************************************************
//  DESCRIPTION : Store codes of a already known transponder
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void LRNMemorizeTranspAlreadyKnown(void)
{
#ifdef X90_PROJECT
    LRNMemorizeTranspAlreadyKnown_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LRNMemorizeTranspAlreadyKnown_Static( void )
{
#endif

    U8 u8IndexL;
    U8 u8IndexOfKeyRecognizedL;
    U8 u8KeyNumberL;  

    u8IndexOfKeyRecognizedL = mDATRead(U8Bit, DATTrpIndexOfKeyRecognized, Default);
    u8KeyNumberL            = mDATRead(U8Bit, NumberOfKeysLearnt, Default);

    // Store identifier and pwdtag
    TableOfKeyIdentifierReassigned[u8KeyNumberL] = mDATReadTable(U32Bit, EEP_KeyIdentifier, u8IndexOfKeyRecognizedL, Default);
    TableOfPassWordTagReassigned[u8KeyNumberL]   = mDATReadTable(U32Bit, EEP_PwdTag, u8IndexOfKeyRecognizedL, Default);

    if (mDATRead(U1Bit, DATTrpKeyWithRF, Default) != 0)
    {
        MemorizeKeyFrequencyCounter();

        switch ((tKeyType)u8IndexOfKeyRecognizedL)
        {
            case cKeyNumber1:
            for (u8IndexL = 0; u8IndexL < cDATTrpISKLengthInBytes; u8IndexL++)
            {
                TableOfRemoteSecretKeyReassigned[u8KeyNumberL].SecretKey[u8IndexL] = mDATReadTable(U8Bit, EEP_RemoteSecretKey1, u8IndexL, Default);
            }
            break;

            case cKeyNumber2:
            for (u8IndexL = 0; u8IndexL < cDATTrpISKLengthInBytes; u8IndexL++)
            {
                TableOfRemoteSecretKeyReassigned[u8KeyNumberL].SecretKey[u8IndexL] = mDATReadTable(U8Bit, EEP_RemoteSecretKey2, u8IndexL, Default);
            }
            break;

            case cKeyNumber3:
            for (u8IndexL = 0; u8IndexL < cDATTrpISKLengthInBytes; u8IndexL++)
            {
                TableOfRemoteSecretKeyReassigned[u8KeyNumberL].SecretKey[u8IndexL] = mDATReadTable(U8Bit, EEP_RemoteSecretKey3, u8IndexL, Default);
            }
            break;

            case cKeyNumber4:
            for (u8IndexL = 0; u8IndexL < cDATTrpISKLengthInBytes; u8IndexL++)
            {
                TableOfRemoteSecretKeyReassigned[u8KeyNumberL].SecretKey[u8IndexL] = mDATReadTable(U8Bit, EEP_RemoteSecretKey4, u8IndexL, Default);
            }
            break;

            //CCOV: amanevd: Cannot be covered because this default case rises explicit assert
            default:
            mLIBassert(cFalse);
            break;
        }

        TableOfResynchroValueReassigned[u8KeyNumberL] = mDATRead(U32Bit, DATTrpResynchronizationValue, Default);
    }
}  
//*****************************************************************************
//  DESCRIPTION : Store codes of a new transponder
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void LRNMemoriseNewTransp(void)
{
#ifdef X90_PROJECT
    LRNMemoriseNewTransp_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LRNMemoriseNewTransp_Static(void)
{
#endif

    U8 u8IndexL;
    U8 u8KeyNumberL;  

    u8KeyNumberL = mDATRead(U8Bit, NumberOfKeysLearnt, Default);

    TableOfKeyIdentifierReassigned[u8KeyNumberL] = u32TrpIdentifierReceived;
    TableOfPassWordTagReassigned[u8KeyNumberL]   = (u32TrpConfigAndPassWordTag & cMaskKeep24Bits);  

    if (mDATRead(U1Bit, DATTrpKeyWithRF, Default) != 0)
    {
        MemorizeKeyFrequencyCounter();

        for (u8IndexL = 0; u8IndexL < cDATTrpISKLengthInBytes; u8IndexL++)
        {
            TableOfRemoteSecretKeyReassigned[u8KeyNumberL].SecretKey[u8IndexL] = RemoteSecretKey[u8IndexL];
        }

        TableOfResynchroValueReassigned[u8KeyNumberL] = mDATRead(U32Bit, DATTrpResynchronizationValue, Default);
    }
}
//*****************************************************************************
//  DESCRIPTION         : Test if a BCM replacement is requested
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : cFalse or cTrue
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//*****************************************************************************
BOOL LRNEnterAfterSaleBCMReplacementMode(void)
{
#ifdef X90_PROJECT
    return LRNEnterAfterSaleBCMReplacementMode_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL LRNEnterAfterSaleBCMReplacementMode_Static(void)
{
#endif

    BOOL bResultL = cFalse;

    if (u8LearningMode == cBcmReplacement)
    {
        // Start after sale timer
        TOSStartTimer(&AfterSaleTimer);
        mDATWrite(U1Bit, DATTrpKeyLearningElapsed, 0, Default);
        mDATWrite(U8Bit, LedVerlogPattern, cDATLearningVerlogPattern, Default);
        
        bResultL = cTrue;
    }
    return bResultL;
}
//*****************************************************************************
//  DESCRIPTION         : Test if key reassignment is requested
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : cFalse or cTrue
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//*****************************************************************************
BOOL LRNEnterAfterSaleKeyReassigmentMode(void)
{
#ifdef X90_PROJECT
    return LRNEnterAfterSaleKeyReassigmentMode_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL LRNEnterAfterSaleKeyReassigmentMode_Static(void)
{
#endif

    BOOL bResultL = cFalse;

    if (u8LearningMode == cKeyReassignment)
    {
        mDATWrite(U8Bit, LedVerlogPattern, cDATLearningVerlogPattern, Default);
        bResultL = cTrue;
    }
    return bResultL;
}
//*****************************************************************************
//  DESCRIPTION         : Test if factory mode is requested
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : cFalse or cTrue
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//*****************************************************************************
BOOL LRNEnterFactoryMode(void)
{
#ifdef X90_PROJECT
    return LRNEnterFactoryMode_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL LRNEnterFactoryMode_Static(void)
{
#endif

    BOOL bResultL = cFalse;

    if (u8LearningMode == cFactoryMode)
    {
        mDATWrite(U1Bit, WritingErrorInEepForKey1InFactoryMode, 0, Default);
        mDATWrite(U1Bit, WritingErrorInEepForKey2InFactoryMode, 0, Default);
        mDATWrite(U1Bit, ISKSuccessfullyWritten, 0, Default);
        mDATWrite(U1Bit, RSKSuccessfullyWritten, 0, Default);
        mDATWrite(U1Bit, SynchroSuccessfullyWritten, 0, Default);
        TOSStartTimer(&PlantModeTimer);
        mDATWrite(U1Bit, DATTrpKeyLearningElapsed, 0, Default);

        mDATWrite(U8Bit, NumberOfKeysLearnt, mDATRead(U8Bit, EEP_NbKeysLearnt, Default), Default);
        mDATWrite(U8Bit, NumberOfKeys315MHzLearnt, mDATRead(U8Bit, EEP_NbKeysStd315MhzLearnt, Default), Default);
        mDATWrite(U8Bit, NumberOfKeys315MHzSmallLearnt, mDATRead(U8Bit, EEP_NbKeysStd315MhzLowPowerLearnt, Default), Default);
        mDATWrite(U8Bit, NumberOfKeys433MHzLearnt, mDATRead(U8Bit, EEP_NbKeysStd433MhzLearnt, Default), Default);

        mDATWrite(U8Bit, LedVerlogPattern, cDATLearningVerlogPattern, Default);
        bKeyAlreadyLearned = cFalse;
        bResultL = cTrue;
    }
    return bResultL;
}
//*****************************************************************************
//  DESCRIPTION         : Test if ignition state is OFF
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : cFalse or cTrue
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//*****************************************************************************
BOOL LRNIgnitionOFF(void)
{
    BOOL bApcOffL;

    CheckExitConditions();

    if (u8LearningMode == cNoLearning)
    {
        mDATWrite(U8Bit, LearningModeInProgress, cDATNoLearningMode, Default);
        mDATWrite(U1Bit, AFSCodeIsOk,0,Default);
        TOSStopTimer(&AfterSaleTimer);
    }

    if (mDATRead(U1Bit, PWR_IGN, Default) == 0)
    {
        // Activate RF
        TOSSendControl(cTOSControlReleaseAprTrpResource);
        bApcOffL = cTrue;
    }
    else
    {
        bApcOffL = cFalse;
    }
    return bApcOffL;
}

//*****************************************************************************
//  DESCRIPTION         : Test if ignition state is ON
//                        Manage the erasing of the after sale code when it is 
//                        enabled.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : cFalse or cTrue
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//*****************************************************************************
BOOL LRNIgnitionON(void)
{
#ifdef X90_PROJECT
    return LRNIgnitionON_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL LRNIgnitionON_Static(void)
{
#endif

    BOOL bResultL = cFalse;
    U8   u8CounterL;
    U8   u8IndexL;

    if (mDATRead(U1Bit, PWR_IGN, Default) != 0)
    {
        // Deactivate RF
        TOSSendControl(cTOSControlGetAprTrpResource);

        ///////////////////////////////////
        // Manage After sale code erasing
        ///////////////////////////////////
        if(     (cTrue == mDATRead(U1Bit, EEP_CodeAFSAvailable, Default))
            &&  (cTrue == mDATRead(U1Bit, EEP_EraseAFSCodeRequest, Default))
          )
        {
            u8CounterL = mDATRead(U8Bit, EEP_AfsEraseIgnitionCnt, Default);
            if(u8CounterL < cU8Max)
            {
                mDATWrite(U8Bit, EEP_AfsEraseIgnitionCnt, (u8CounterL + 1), Default);
            }

            if (    mDATRead(U8Bit, EEP_AfsEraseIgnitionCnt, Default) 
                   >= mDATRead(U8Bit, NEEP_N_MISE_APC, Default))
            {
                mDATWrite(U1Bit, EEP_CodeAFSAvailable, 0, Default);
                mDATWrite(U8Bit, EEP_AfsEraseIgnitionCnt, 0, Default);

                for (u8IndexL = 0; u8IndexL < cDATTrpISKLengthInBytes; u8IndexL++)
                {
                    mDATWriteTable(U8Bit, EEP_AfterSalesCode, u8IndexL, 0, Default);
                }
            }
            else
            {
                //Nothing to do
            }
        }
        bResultL = cTrue;
    }
    else
    {
        CheckExitConditions();
    }
    return bResultL;
}
//*****************************************************************************
//  DESCRIPTION         : The learning of the current key is not successful
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//*****************************************************************************
void LRNLearningModeNotSuccess(void)
{
#ifdef X90_PROJECT
    LRNLearningModeNotSuccess_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LRNLearningModeNotSuccess_Static(void)
{
#endif

    if (u8LearningMode == cFactoryMode)
    {

        //------------------------------------------------
        // Key learning in Factory mode is not successful
        //------------------------------------------------
        if (mExitFactoryModeRequestedIsOn())
        {
            mClearExitFactoryModeRequested();
            u8LearningMode = cNoLearning;
        }

        if(cFalse == bKeyAlreadyLearned)
        {
            mDATWrite(U8Bit, LedVerlogPattern, cDATSwitchOnVerlogPattern, Default);
        }
        else
        {
            mDATWrite(U8Bit, LedVerlogPattern, cDATLearningVerlogPattern, Default);
        }
    }
    else if (u8LearningMode == cBcmReplacement)
    {
        //--------------------------------------------
        // Key learning in After Sale mode with BCM
        // replacement is not successful
        //--------------------------------------------
        mDATWrite(U8Bit, LedVerlogPattern, cDATSwitchOnVerlogPattern, Default);
    }
    else
    {
        //--------------------------------------------
        // Key learning in After Sale mode with key
        // reassignment is not successful
        //--------------------------------------------
        if (mGiveUpAfterSaleModeRequestedIsOff())
        {      
            TOSStartTimer(&AfterSaleTimer);
        }
        else
        {
            u8LearningMode = cNoLearning;    
        }    
        mDATWrite(U8Bit, LedVerlogPattern, cDATSwitchOnVerlogPattern, Default);
    }
}
//*****************************************************************************
//  DESCRIPTION         : The learning of the current key is successful
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//*****************************************************************************
void LRNLearningModeSuccess(void)
{
#ifdef X90_PROJECT
    LRNLearningModeSuccess_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LRNLearningModeSuccess_Static(void)
{
#endif
    U8 u8NumberOfKeyL;

    if (u8LearningMode == cFactoryMode)
    {
        //--------------------------------------------
        // Key learning in Factory mode is successful
        //--------------------------------------------    
        if (mDATRead(U1Bit, EEP_BCMBlank, Default) != 0)
        {
            mDATWrite(U1Bit, EEP_BCMBlank, 0, Default);

            // Inform the learning Tool that the After Sale code is now available
            // and initialize after sale code erasing counter
            mDATWrite(U1Bit, EEP_CodeAFSAvailable, 1, Default);
            mDATWrite(U1Bit, EEP_EraseAFSCodeRequest, 0, Default);
            mDATWrite(U8Bit, EEP_AfsEraseIgnitionCnt, 0, Default);
        }

        if(cKeyNumber1 == mDATRead(U8Bit, NumberOfKeysLearnt, Default))
        {
            mDATWrite(U8Bit, COD_ERR_APP, cCodeError1h, Default);
        }

        // Store the number of keys learnt
        u8NumberOfKeyL = (mDATRead(U8Bit, NumberOfKeysLearnt, Default) + 1);
        mDATWrite(U8Bit, NumberOfKeysLearnt, u8NumberOfKeyL, Default);
        mDATWrite(U8Bit, EEP_NbKeysLearnt, u8NumberOfKeyL, Default);
        mDATWrite(U8Bit, EEP_NbKeysStd433MhzLearnt, mDATRead(U8Bit, NumberOfKeys433MHzLearnt, Default), Default);
        mDATWrite(U8Bit, EEP_NbKeysStd315MhzLearnt, mDATRead(U8Bit, NumberOfKeys315MHzLearnt, Default), Default);
        mDATWrite(U8Bit, EEP_NbKeysStd315MhzLowPowerLearnt, mDATRead(U8Bit, NumberOfKeys315MHzSmallLearnt, Default), Default);
        TOSStopTimer(&PlantModeTimer);
        mDATWrite(U1Bit, DATTrpKeyLearningElapsed, 0, Default);

        if(mDATRead(U8Bit, NumberOfKeysLearnt, Default) >= cFactoryModeMaxKeysToLearn)
        {
            mDATWrite(U1Bit, EEP_AppCleNonEffect, 0, Default);
            mSetExitFactoryModeRequested();
        }

        if (mExitFactoryModeRequestedIsOn())
        {
            mDATWrite(U8Bit, COD_ERR_APP, cCodeError2h, Default);
            mClearExitFactoryModeRequested();
            u8LearningMode = cNoLearning;
        }
    }
    else if (u8LearningMode == cBcmReplacement)
    {
        //--------------------------------------------
        // Key learning in After Sale mode with BCM
        // replacement is successful
        //--------------------------------------------
        mDATControl(Apr,cDATAprTestDiagAfterSaleCode);  // Update AFS with new Key

        mDATWrite(U1Bit, EEP_BCMBlank, 0, Default);
        mDATWrite(U8Bit, COD_ERR_APP, cCodeError1h, Default);
        mDATWrite(U1Bit, EEP_EraseAFSCodeRequest, 1, Default); // cde_eff_code_recu

        mDATWrite(U8Bit, EEP_NbKeysLearnt, 1, Default);
        mDATWrite(U8Bit, EEP_NbKeysStd433MhzLearnt, mDATRead(U8Bit, NumberOfKeys433MHzLearnt, Default), Default);
        mDATWrite(U8Bit, EEP_NbKeysStd315MhzLearnt, mDATRead(U8Bit, NumberOfKeys315MHzLearnt, Default), Default);
        mDATWrite(U8Bit, EEP_NbKeysStd315MhzLowPowerLearnt, mDATRead(U8Bit, NumberOfKeys315MHzSmallLearnt, Default), Default);

        u8LearningMode = cNoLearning;
    }
    else
    {
        //--------------------------------------------
        // Key learning in After Sale mode with key
        // reassignment is successful
        //--------------------------------------------
        if (mGiveUpAfterSaleModeRequestedIsOff())
        {
            mDATWrite(U1Bit, AfterSaleModeValidationAuthorized, 1, Default);
            u8NumberOfKeyL = mDATRead(U8Bit, NumberOfKeysLearnt, Default);
            mDATWrite(U8Bit, NumberOfKeysLearnt, (u8NumberOfKeyL + 1), Default);
            TOSStartTimer(&AfterSaleTimer);
        }
        else
        {
            mClearGiveUpAfterSaleModeRequested();
            u8LearningMode = cNoLearning;
        }
        mDATWrite(U8Bit, COD_ERR_APP, cCodeError1h, Default);
    }
    mDATWrite(U8Bit, LedVerlogPattern, cDATSwitchOffVerlogPattern, Default);
}

//*****************************************************************************
//  DESCRIPTION         : Update diagnostic data
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//*****************************************************************************
void LRNUpdateDiagData(void)
{
#ifdef X90_PROJECT
    LRNUpdateDiagData_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LRNUpdateDiagData_Static(void)
{
#endif

    mDATWrite(U1Bit, ISKSuccessfullyWritten,      0, Default);
    mDATWrite(U1Bit, RSKSuccessfullyWritten,      0, Default);
    mDATWrite(U1Bit, SynchroSuccessfullyWritten,  0, Default);
    if (u8LearningMode != cNoLearning)
    {
        mDATControl(Trp,cDATTrpInitDiagInfo);
    }
}

//*****************************************************************************
//  DESCRIPTION         : Control used to start learning in after sale mode
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//*****************************************************************************
void LRNStartLearningInAfterSaleMode(void)
{
#ifdef X90_PROJECT
    LRNStartLearningInAfterSaleMode_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LRNStartLearningInAfterSaleMode_Static(void)
{
#endif

    U8 u8IndexL;

    for (u8IndexL = 0; u8IndexL < cDATTrpMaxNumberOfKey; u8IndexL++)
    {
        TableOfKeyIdentifierReassigned[u8IndexL]             = 0;
        TableOfPassWordTagReassigned[u8IndexL]               = LIBCalculateRandomNb(TOSClock);
        TableOfRemoteSecretKeyReassigned[u8IndexL].SK.SKLow  = 0;
        TableOfRemoteSecretKeyReassigned[u8IndexL].SK.SKHigh = 0;
        TableOfResynchroValueReassigned[u8IndexL]            = 0;
    }    

    mDATWrite(U8Bit, NumberOfKeysLearnt, 0, Default);
    mDATWrite(U8Bit, NumberOfKeys315MHzLearnt, 0, Default);
    mDATWrite(U8Bit, NumberOfKeys315MHzSmallLearnt, 0, Default);
    mDATWrite(U8Bit, NumberOfKeys433MHzLearnt, 0, Default);

    mDATWrite(U1Bit, ISKSuccessfullyWritten, 0, Default);
    mDATWrite(U1Bit, RSKSuccessfullyWritten, 0, Default);
    mDATWrite(U1Bit, SynchroSuccessfullyWritten, 0, Default);

    // Start after sale timer
    TOSStartTimer(&AfterSaleTimer);

    if (mDATRead(U1Bit, EEP_BCMBlank, Default) == 0)
    {
        mDATWrite(U1Bit, WritingErrorInEepInReassignment, 0, Default);
        u8LearningMode = cKeyReassignment;
        mDATWrite(U8Bit, LearningModeInProgress, cDATKeyReassignment, Default);
        mDATWrite(U1Bit, AfterSaleModeValidationAuthorized, 1, Default);
    }
    else
    {
        mDATWrite(U1Bit, WritingErrorInEepInBcmReplacement, 0, Default);
        u8LearningMode = cBcmReplacement;
        mDATWrite(U8Bit, LearningModeInProgress, cDATBcmReplacement, Default);
        mDATWrite(U1Bit, AfterSaleModeValidationAuthorized, 1, Default);
    }

    mClearGiveUpAfterSaleModeRequested();

    mDATWrite(U8Bit, COD_ERR_APP, cCodeError0h, Default);
    mDATWrite(U1Bit, FactoryModeAuthorized, 0, Default);
    mDATWrite(U1Bit, AfterSaleModeAuthorized, 0, Default);
}
//*****************************************************************************
//  DESCRIPTION         : Control used to validate the keys learnt in after sale
//                        mode.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//*****************************************************************************
void LRNValidateLearningInAfterSaleMode(void)
{
#ifdef X90_PROJECT
    LRNValidateLearningInAfterSaleMode_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LRNValidateLearningInAfterSaleMode_Static(void)
{
#endif

    tKeyType u8IndexL;

    if(cKeyReassignment == u8LearningMode)
    {
        for (u8IndexL = cKeyNumber1; u8IndexL < cDATTrpMaxNumberOfKey; u8IndexL++)
        {
            // Store the Identifier and Password received after the Authentication sequence
            mDATWriteTable(U32Bit, EEP_KeyIdentifier, u8IndexL, 
                TableOfKeyIdentifierReassigned[u8IndexL], Default);
            mDATWriteTable(U32Bit, EEP_PwdTag, u8IndexL, 
                TableOfPassWordTagReassigned[u8IndexL], Default);

            // Store RSK and resynchronization value
            WriteRSKInEeprom(u8IndexL, TableOfRemoteSecretKeyReassigned[u8IndexL].SecretKey);
            mDATWriteTable(U32Bit, EEP_SI28Bits, u8IndexL, 
                TableOfResynchroValueReassigned[u8IndexL], Default);
            mDATWriteTable(U32Bit, EEP_InitialResynchroValue, u8IndexL, 
                TableOfResynchroValueReassigned[u8IndexL], Default);
        }
    }
    if (mDATRead(U1Bit, PWR_IGN, Default) == 0)
    {
        mDATWrite(U1Bit, AFSCodeIsOk,0,Default);
    }
    mDATWrite(U8Bit, COD_ERR_APP, cCodeError1h, Default);
    TOSStopTimer(&AfterSaleTimer);

    mSetLearningValidation();
}
//*****************************************************************************
//  DESCRIPTION         : Manage the update of the learning services 
//                        authorization and the state of the EEPROM writing of 
//                        the after sale mode validation.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//*****************************************************************************
void LRNUpdateLearningAuthorizationConditions(void)
{
#ifdef X90_PROJECT
    LRNUpdateLearningAuthorizationConditions_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LRNUpdateLearningAuthorizationConditions_Static(void)
{
#endif

    BOOL bTimerStartedL;
    BOOL bTimerElapsedL;
    tTOSTimer   TempTimer;

    if (mDATRead(U1Bit, PWR_IGN, Default) == 0)
    {
        if (u8LearningMode == cNoLearning)
        {
            mDATWrite(U1Bit, FactoryModeAuthorized, 
                    (   mDATRead(U1Bit, EEP_BCMBlank, Default)
                     || mDATRead(U1Bit, EEP_CodeAFSAvailable, Default))
                     && mDATRead(U1Bit, EEP_AppCleNonEffect, Default), 
                Default);
            mDATWrite(U1Bit, AfterSaleModeAuthorized, 1, Default);      
        }
    }
    else
    {
        mDATWrite(U1Bit, AfterSaleModeAuthorized, 0, Default);
        if(cFactoryMode == u8LearningMode)
        {
            bTimerStartedL = TOSIsTimerStarted(&PlantModeTimer);
            //QACJ 3226: amanevd: This is intentional and is checked out for problems.
            TempTimer      = mPlantModeTimeOut();
            bTimerElapsedL = TOSIsTimerElapsed(&PlantModeTimer, TempTimer);
            if((cFalse != bTimerStartedL) && (cFalse != bTimerElapsedL))
            {
                mDATWrite(U1Bit, DATTrpKeyLearningElapsed, 1, Default);
            }
        }
        else
        {
            //Nothing to do
        }
    }

    if (   mLearningValidationIsOn()
        && (mDATRead(U1Bit, IsEepGroupStaticImmoBankProcessing, Default) == 0)
        && (mDATRead(U1Bit, IsEepGroupDynamicImmoDataBankProcessing, Default) == 0) )
    {
        if (   (mDATRead(U1Bit, IsEepGroupStaticImmoBankWriteOk, Default) == 0)
        || (mDATRead(U1Bit, IsEepGroupDynamicImmoDataBankWriteOk, Default) == 0) )
        {
            mDATWrite(U1Bit, WritingErrorInEepInReassignment, 1, Default);

            mDATWrite(U1Bit, EEP_BCMBlank, 1, Default);
            mDATWrite(U8Bit, EEP_NbKeysLearnt, 0, Default);
            mDATWrite(U8Bit, EEP_NbKeysStd315MhzLearnt, 0, Default);
            mDATWrite(U8Bit, EEP_NbKeysStd315MhzLowPowerLearnt, 0, Default);
            mDATWrite(U8Bit, EEP_NbKeysStd433MhzLearnt, 0, Default);
        }
        else
        {
            mDATWrite(U8Bit, EEP_NbKeysLearnt, mDATRead(U8Bit, NumberOfKeysLearnt, Default), Default);
            mDATWrite(U8Bit, EEP_NbKeysStd315MhzLearnt, mDATRead(U8Bit, NumberOfKeys315MHzLearnt, Default), Default);
            mDATWrite(U8Bit, EEP_NbKeysStd315MhzLowPowerLearnt, mDATRead(U8Bit, NumberOfKeys315MHzSmallLearnt, Default), Default);
            mDATWrite(U8Bit, EEP_NbKeysStd433MhzLearnt, mDATRead(U8Bit, NumberOfKeys433MHzLearnt, Default), Default);

            mDATWrite(U1Bit, EEP_AppCleNonEffect, 0, Default);
        }
        mClearLearningValidation();
        mDATWrite(U1Bit, AfterSaleModeValidationAuthorized, 0, Default);

        u8LearningMode = cNoLearning;
        mDATWrite(U8Bit, LearningModeInProgress, cDATNoLearningMode, Default);
    }
}

//*****************************************************************************
//  DESCRIPTION         : Backup authentication with transport ISK High when
//                        the ISK High writing has failed.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//*****************************************************************************
void LRNAuthenticationWithCalculatedISKHigh(void)
{
#ifdef X90_PROJECT
    LRNAuthenticationWithCalculatedISKHigh_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LRNAuthenticationWithCalculatedISKHigh_Static(void)
{
#endif

    U8 u8IndexL;

    if (mDATRead(U1Bit, EEP_BCMBlank, Default) == 0)
    {
        for (u8IndexL = 0; u8IndexL < cDATTrpISKLengthInBytes; u8IndexL++)
        {
            mDATWriteTable(U8Bit, DATTrpISKForAuthent, u8IndexL, mDATReadTable(U8Bit, EEP_ImmoSecretKey, u8IndexL, Default), Default);
        }    
    }
    else
    {
        for (u8IndexL = 0; u8IndexL < cDATTrpISKLengthInBytes; u8IndexL++)
        {
            mDATWriteTable(U8Bit, DATTrpISKForAuthent, u8IndexL, ImmobilizerSecretKey[u8IndexL], Default);
        }
    }
    mDATWrite(U1Bit, DATTrpAuthentInLearningMode, 1, Default);
    mDATControl(Trp, cDATTrpAuthenticate);
}
//*****************************************************************************
//  DESCRIPTION         : Test if a key could be learnt in key reassignment
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : cFalse or cTrue
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//*****************************************************************************
BOOL LRNReassignmentCannotBeDone(void)
{
    return (mDATRead(U8Bit, NumberOfKeysLearnt, Default) >= cDATTrpMaxNumberOfKey);
}
//*****************************************************************************
//  DESCRIPTION         : Control use to give up the learning in after sale
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//*****************************************************************************
void LRNGiveUpLearningInAfterSaleMode(void)
{
    if (mDATRead(U1Bit, PWR_IGN, Default) == 0)
    {
        mDATWrite(U1Bit, AFSCodeIsOk,0,Default);
    }
    mSetGiveUpAfterSaleModeRequested();
}

//*****************************************************************************
//  DESCRIPTION         : ISK Writing Error
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//*****************************************************************************
void LRNISKWritingError(void)
{
    if (u8LearningMode == cFactoryMode)
    {
        mDATWrite(U8Bit, COD_ERR_APP, cCodeError12h, Default);
    }
    else // if(u8LearningMode == cKeyReassignment)
    {
        mDATWrite(U8Bit, COD_ERR_APP, cCodeErrorB3h, Default);
    }
}

//*****************************************************************************
//  DESCRIPTION         : Backup authentication with transport ISK when
//                        the ISK Low writing has failed.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//*****************************************************************************
void LRNAuthenticationWithCalculatedISKLow(void)
{
#ifdef X90_PROJECT
    LRNAuthenticationWithCalculatedISKLow_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LRNAuthenticationWithCalculatedISKLow_Static(void)
{
#endif

    U8 u8IndexL;

    if (mDATRead(U1Bit, EEP_BCMBlank, Default) == 0)
    {
        for (u8IndexL = 0; u8IndexL < (cDATTrpISKLengthInBytes - cSKIndex2); u8IndexL++)
        {
            mDATWriteTable(U8Bit, DATTrpISKForAuthent, u8IndexL, mDATReadTable(U8Bit, EEP_ImmoSecretKey, u8IndexL, Default), Default);
        }
    }
    else
    {
        for (u8IndexL = 0; u8IndexL < (cDATTrpISKLengthInBytes - cSKIndex2); u8IndexL++)
        {
            mDATWriteTable(U8Bit, DATTrpISKForAuthent, u8IndexL, ImmobilizerSecretKey[u8IndexL], Default);
        }
    }
    mDATWriteTable(U8Bit, DATTrpISKForAuthent, cSKIndex4, mDATReadTable(U8Bit, DATTrpTransportISK, cSKIndex4, Default), Default);
    mDATWriteTable(U8Bit, DATTrpISKForAuthent, cSKIndex5, mDATReadTable(U8Bit, DATTrpTransportISK, cSKIndex5, Default), Default);

    mDATWrite(U1Bit, DATTrpAuthentInLearningMode, 1, Default);
    mDATControl(Trp, cDATTrpAuthenticate);
}
//*****************************************************************************
//  DESCRIPTION         : Test if the factory mode is in progress
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : cFalse or cTrue
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//*****************************************************************************
BOOL LRNFactoryModeInProgress(void)
{
    return (u8LearningMode == cDATFactoryMode);
}

