//******************************************************************************
// Company:      Johnson Controls Inc.
// -----------------------------------------------------------------------------
// Copyright:    This software is JCI property.
//               Duplication or disclosure without JCI written authorization
//               is prohibited.
// -----------------------------------------------------------------------------
// Project:      X90_BCM
// Language:     ANSI-C
// -----------------------------------------------------------------------------
// Component:    DAT_PEE
// -----------------------------------------------------------------------------
// $Date:   Mar 05 2010 11:27:20  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_PEE/DAT_PEEP.H-arc  $
// $Revision:   1.3  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_PEE/DAT_PEEP.H-arc    $
// 
//    Rev 1.3   Mar 05 2010 11:27:20   adzhelp
// Cm006814, Cm007684: TPS_IMPUL_MINI is removed
// 
//    Rev 1.2   Mar 05 2010 10:33:06   adzhelp
// Cm006814, Cm007684: Normalization of calibration parameters
// 
//    Rev 1.1   Mar 20 2009 09:25:48   adzhelp
// Cm003278: Define macros to acces Eeprom bank like a table
//
//    Rev 1.0   10 Nov 2008 10:31:18   ailievb
// Initial revision.
//
//******************************************************************************

#ifndef I_DAT_PEEP_H
#define I_DAT_PEEP_H (1)

/*-------------------------------------------------------------------------
  Included files

  #include <system_file_name.h>
  #include "project_file_name.h"
  --------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
  Constant data

  #define cCMPConstantName   ((tType) ConstantValue)
  -------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
  Exported Macros

  #define mCMPMacroName   (MacroDefinition)
  -------------------------------------------------------------------------*/ 
 // Define macros to acces Eeprom bank like a table
#define mDATWriteTableU8BitEEPGeneralParameterBankDefault(Index, ValueToWrite) \
            { \
                mLIBassert(Index < cDATPeeSizeGeneralParameterBank); \
                ((U8*)DATDbkMirrors.GeneralParameterBank)[Index] = (ValueToWrite); \
            }

#define mDATReadTableU8BitEEPGeneralParameterBankDefault(Index) \
                (((U8*)DATDbkMirrors.GeneralParameterBank)[Index])

// Normalization of calibration parameters
// Cm006814: DIAG: Implement consistency checking of calibration parameters according to prsFS_DIAG-766
// Read access macros for N<EEP_PARAMETER> :

//NEEP_TPS_RETARD_DETRESSE
#define mDATReadU8BitNEEP_TPS_RETARD_DETRESSEDefault()  (DATPeeCalibrationData.TPS_RETARD_DETRESSE)
//NEEP_TIMER_DETRESSE
#define mDATReadU8BitNEEP_TIMER_DETRESSEDefault() (DATPeeCalibrationData.TIMER_DETRESSE)
//NEEP_TPS_APC
#define mDATReadU8BitNEEP_TPS_APCDefault() (DATPeeCalibrationData.TPS_APC)
//NEEP_TPS_PLAF;
#define mDATReadU8BitNEEP_TPS_PLAFDefault() (DATPeeCalibrationData.TPS_PLAF)
//NEEP_TPS_ESSUIE_MINI;
#define mDATReadU8BitNEEP_TPS_ESSUIE_MINIDefault() (DATPeeCalibrationData.TPS_ESSUIE_MINI)
//NEEP_TPS_MAX_COUPLBLOC;
#define mDATReadU8BitNEEP_TPS_MAX_COUPLBLOCDefault() (DATPeeCalibrationData.TPS_MAX_COUPLBLOC)
//NEEP_TPS_ARRET;
#define mDATReadU8BitNEEP_TPS_ARRETDefault() (DATPeeCalibrationData.TPS_ARRET)
//NEEP_TPS_REPRISE;
#define mDATReadU8BitNEEP_TPS_REPRISEDefault() (DATPeeCalibrationData.TPS_REPRISE)
//NEEP_PROLONG_APPUI_COURT;
#define mDATReadU8BitNEEP_PROLONG_APPUI_COURTDefault() (DATPeeCalibrationData.PROLONG_APPUI_COURT)
//NEEP_PROLONG_APPUI_LONG;
#define mDATReadU8BitNEEP_PROLONG_APPUI_LONGDefault() (DATPeeCalibrationData.PROLONG_APPUI_LONG)
//NEEP_TPS_APPUILAV;
#define mDATReadU8BitNEEP_TPS_APPUILAVDefault() (DATPeeCalibrationData.TPS_APPUILAV)
//NEEP_PROLONG_APPUI_ARR;
#define mDATReadU8BitNEEP_PROLONG_APPUI_ARRDefault() (DATPeeCalibrationData.PROLONG_APPUI_ARR)
//NEEP_SEUIL_VIT_CONDAROU;
#define mDATReadU8BitNEEP_SEUIL_VIT_CONDAROUDefault() (DATPeeCalibrationData.SEUIL_VIT_CONDAROU)
//NEEP_TPS_COM_MOTEUR;
#define mDATReadU8BitNEEP_TPS_COM_MOTEURDefault() (DATPeeCalibrationData.TPS_COM_MOTEUR)
//NEEP_NBCOM_MAX;
#define mDATReadU8BitNEEP_NBCOM_MAXDefault() (DATPeeCalibrationData.NBCOM_MAX)
//NEEP_TPS_REF;
#define mDATReadU8BitNEEP_TPS_REFDefault() (DATPeeCalibrationData.TPS_REF)
//NEEP_TIMER_RECONDA_AUTO;
#define mDATReadU8BitNEEP_TIMER_RECONDA_AUTODefault() (DATPeeCalibrationData.TIMER_RECONDA_AUTO)
//NEEP_N_MISE_APC;
#define mDATReadU8BitNEEP_N_MISE_APCDefault() (DATPeeCalibrationData.N_MISE_APC)
//NEEP_TPS_OUVPORTE;
#define mDATReadU8BitNEEP_TPS_OUVPORTEDefault() (DATPeeCalibrationData.TPS_OUVPORTE)
//NEEP_TPS_TEMPO_DEG;
#define mDATReadU8BitNEEP_TPS_TEMPO_DEGDefault() (DATPeeCalibrationData.TPS_TEMPO_DEG)
//NEEP_SBR_ACTIVE_SPEED_THRESH_TP;
#define mDATReadU8BitNEEP_SBR_ACTIVE_SPEED_THRESH_TPDefault() (DATPeeCalibrationData.SBR_ACTIVE_SPEED_THRESH_TP)
//NEEP_SBR_TIMEOUT_TM_TP;
#define mDATReadU8BitNEEP_SBR_TIMEOUT_TM_TPDefault() (DATPeeCalibrationData.SBR_TIMEOUT_TM_TP)
//NEEP_MAX_NB_ALERT_SEQUENCES_TP;
#define mDATReadU8BitNEEP_MAX_NB_ALERT_SEQUENCES_TPDefault() (DATPeeCalibrationData.MAX_NB_ALERT_SEQUENCES_TP)
//NEEP_TPS_BUZ_CLI;
#define mDATReadU8BitNEEP_TPS_BUZ_CLIDefault() (DATPeeCalibrationData.TPS_BUZ_CLI)
//NEEP_TPS_CLI;
#define mDATReadU8BitNEEP_TPS_CLIDefault() (DATPeeCalibrationData.TPS_CLI)
//NEEP_TPS_CLIDEGRAD;
#define mDATReadU8BitNEEP_TPS_CLIDEGRADDefault() (DATPeeCalibrationData.TPS_CLIDEGRAD)

/*-------------------------------------------------------------------------
  Exported type

  struct  sCMPStructureName { ... };
  union   uCMPUnionName { ... };
  enum    eCMPEnumerationName { ... };
  typedef Expression tCMPTypeName;

  -------------------------------------------------------------------------*/
typedef struct sDATPeeCalibrationData
{
    U8 TPS_RETARD_DETRESSE;
    U8 TIMER_DETRESSE;
    U8 TPS_APC;
    U8 TPS_PLAF;
    U8 TPS_ESSUIE_MINI;
    U8 TPS_MAX_COUPLBLOC;
    U8 TPS_ARRET;
    U8 TPS_REPRISE;
    U8 PROLONG_APPUI_COURT;
    U8 PROLONG_APPUI_LONG;
    U8 TPS_APPUILAV;
    U8 PROLONG_APPUI_ARR;
    U8 SEUIL_VIT_CONDAROU;
    U8 TPS_COM_MOTEUR;
    U8 NBCOM_MAX;
    U8 TPS_REF;
    U8 TIMER_RECONDA_AUTO;
    U8 N_MISE_APC;
    U8 TPS_OUVPORTE;
    U8 TPS_TEMPO_DEG;
    U8 SBR_ACTIVE_SPEED_THRESH_TP;
    U8 SBR_TIMEOUT_TM_TP;
    U8 MAX_NB_ALERT_SEQUENCES_TP;
    U8 TPS_BUZ_CLI;
    U8 TPS_CLI;
    U8 TPS_CLIDEGRAD;

} tDATPeeCalibrationData;

/*-------------------------------------------------------------------------
  Exported data

  extern  tType   CMPVariableName;
  extern  tType*  pCMPVariableName; 
  -------------------------------------------------------------------------*/ 
extern tDATPeeCalibrationData DATPeeCalibrationData;

/*-------------------------------------------------------------------------
  Constant exported data

  extern const tType  CMPVariableName;
  -------------------------------------------------------------------------*/ 

/*-------------------------------------------------------------------------
  Exported functions

  extern tReturnType CMPFunctionName(tTypeArgument1 ArgumentName1, ... );
  -------------------------------------------------------------------------*/ 

#endif   /* I_DAT_PEEP_H */
