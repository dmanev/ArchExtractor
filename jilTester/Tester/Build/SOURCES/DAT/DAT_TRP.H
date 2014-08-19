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
// Component:    DAT_TRP
// -----------------------------------------------------------------------------
// $Date:   Mar 01 2010 15:05:38  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_TRP/DAT_TRP.H-arc  $
// $Revision:   1.9  $
// -----------------------------------------------------------------------------  
//
//    $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_TRP/DAT_TRP.H-arc  $
// 
//    Rev 1.9   Mar 01 2010 15:05:38   adzhelp
// Cm007334: Code review corrections
// 
//    Rev 1.8   Dec 14 2009 10:52:16   amanevd
// Cm005566: Full Hardware Protection
// 
//    Rev 1.7   Sep 17 2009 09:58:38   adzhelp
// Cm003277: DATTrpControl() defined as CALLT_TYPE
// 
//    Rev 1.6   Aug 07 2009 18:09:44   amanevd
// Cm005142: Implementation of Confidential Diagnostic
// 
//    Rev 1.5   Jul 14 2009 17:14:42   amanevd
// Cm005586: DiagKeyFrequency signal included
// 
//    Rev 1.4   Apr 29 2009 13:12:30   amanevd
// Cm003272 - Intermediate part 3 
// - PRS compliance
// 
//    Rev 1.3   Apr 22 2009 19:23:40   amanevd
// Cm003272 - Finishing part 1 - pre-integration
// 
//    Rev 1.2   Feb 13 2009 14:52:12   amanevd
// Cm003272 - Intermediate part 1 - PRS compliance
// 
//    Rev 1.1   Feb 04 2009 13:29:42   amanevd
// Cm003272 - Intermediate part 1
// - PRS compliance
// 
//    Rev 1.0   Jan 09 2009 14:03:58   amanevd
// Initial revision.
// 
//=============================================================================

#ifndef I_DAT_TRP_H
#define I_DAT_TRP_H (1)

//-----------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//
// #include <system_file_name.h>
// #include "project_file_name.h"
//-----------------------------------------------------------------------------
#include "dat_trpp.h"
#include "ldb.h"

//-----------------------------------------------------------------------------
// Data prefix for constant & data
//
// unsigned int {u8,u16,u32} / signed int {s8,s16,s32} 
// register size unsigned int {r} / float {f32,f64}  / s for struct 
// no prefix for other types.
//
//-----------------------------------------------------------------------------
// Constant data
//
// #define cu16LAYCmpConstantName   ((U16) ConstantValueUL)
//-----------------------------------------------------------------------------

// DAT_TRP Controls
#define cDATTrpWakeUp                   ((tCtrl) 0x00U)
#define cDATTrpSleep                    ((tCtrl) 0x01U)
#define cDATTrpStop                     ((tCtrl) 0x02U)
#define cDATTrpAuthenticate             ((tCtrl) 0x03U)
#define cDATTrpReadPage                 ((tCtrl) 0x04U)
#define cDATTrpWritePage                ((tCtrl) 0x05U)
#define cDATTrpResynchronize            ((tCtrl) 0x06U)
#define cDATTrpInitDiagInfo             ((tCtrl) 0x07U)
#define cDATTrpInitializeBlockPointer   ((tCtrl) 0x08U)
#define cDATTrpIncrementBlockPointer    ((tCtrl) 0x09U)
#define cDATTrpDecrementBlockPointer    ((tCtrl) 0x0AU)
#define cDATTrpStopAuthentService       ((tCtrl) 0x0BU)
#define cDATTrpActivateDiag             ((tCtrl) 0x0CU)
#define cDATTrpDeactivateDiag           ((tCtrl) 0x0DU)
#define cDATTrpTfcDiag                  ((tCtrl) 0x0EU)

// encode key frequencies 
#define cDATTrpKey433Mhz              ((U8) 0x00)
#define cDATTrpKey315Mhz              ((U8) 0x10)
#define cDATTrpKey315MhzSmall         ((U8) 0x30)
#define cDATTrpKey868Mhz              ((U8) 0x20)

// Diag key frequencies
#define cDATKeyInvalidFrequency           ((U8) 0x00) // Value defined for diag
#define cDATKeyFrequency315Mhz            ((U8) 0x07) // Value defined for diag
#define cDATKeyFrequency315MhzSmall       ((U8) 0x05) // Value defined for diag
#define cDATKeyFrequency433Mhz            ((U8) 0x06) // Value defined for diag
#define cDATKeyFrequency868Mhz            ((U8) 0x04) // Value defined for diag

#define cDATTrpISKLengthInBytes       ((U8) 6)

#define cDATTrpResyncReadFailDefaultValue ((U32) 0)

#define cDATTrpInvalidKeyIndex        cDATTrpMaxNumberOfKey

// Define the state of a transponder service
#define cDATTrpServiceNotStarted      ((U8) 0)
#define cDATTrpServiceInProgress      ((U8) 1)
#define cDATTrpServiceSuccessful      ((U8) 2)
#define cDATTrpServiceNotSuccessful   ((U8) 3)

// LastVerlogStatus states
#define cDATTrpVerlogOff              ((U8) 0)
#define cDATTrpBadEcmChallenge        ((U8) 1)
#define cDATTrpChallengeAnsweredByBCM ((U8) 2)

//-----------------------------------------------------------------------------
// Exported Macros
//
// #define LAYCmpMacroName(...)   (MacroDefinition)
//-----------------------------------------------------------------------------

// DAT Controls
#define mDATControlTrp(Control) DATTrpControl(Control)

// DAT Write
#define mDATWriteTableU8BitDATTrpISKForAuthentDefault(Index, Val) (DatTrpExportData.ISKForAuthent[Index] = (Val))
#define mDATWriteU32BitDATTrpDataToWriteDefault(Val) (DatTrpExportData.DataToWrite = (Val))
#define mDATWriteU8BitDATTrpPageNumberDefault(Val) (DatTrpExportData.PageNumber = (Val))
#define mDATWriteU1BitDATTrpAuthentInLearningModeDefault(Val) (DatTrpExportData.AuthentInLearningMode = (Val))
#define mDATWriteU1BitDATTrpWriteSecretKeyHighDefault(Val) (DatTrpExportData.WriteSecretKeyHigh = (Val))
#define mDATWriteU1BitDATTrpActiveTestModeDefault(Val) (DatTrpExportData.ActiveTestMode = (Val))
// Used by LAP component which manages transponder learning
#define mDATWriteU1BitDATTrpPresentKeyLockedDefault(Val) (DatTrpExportData.PresentKeyLocked = (Val))
#define mDATWriteU8BitDATTrpIndexOfKeyRecognizedDefault(Val) (DatTrpExportData.IndexOfKeyRecognized = (Val))
#define mDATWriteU8BitDATTrpAuthentTryCounterDefault(Val)  (DatTrpExportData.AuthentTryCounter = (Val))
#define mDATWriteU1BitDATTrpIdentifierOfPresentKeyIsReceivedDefault(Val) (DatTrpExportData.IdentifierOfPresentKeyIsReceived = (Val))
#define mDATWriteU1BitDATTrpIdentifierOfPresentKeyIsValidDefault(Val) (DatTrpExportData.IdentifierOfPresentKeyIsValid = (Val))
#define mDATWriteU1BitDATTrpResponseToChallengeIsPresentDefault(Val) (DatTrpExportData.ResponseToChallengeIsPresent = (Val))
#define mDATWriteU1BitDATTrpResponseToChallengeIsValidDefault(Val) (DatTrpExportData.ResponseToChallengeIsValid = (Val))
#define mDATWriteU1BitVirginKeyAuthentOkDefault(Val) (DatTrpExportData.VirginKeyAuthentOk = (Val))  
#define mDATWriteU1BitDATTrpKeyWithRFDefault(Val)	(DatTrpExportData.KeyWithRF = (Val))
#define mDATWriteU1BitDATTrpKeyLearningElapsedDefault(Val)  (DatTrpExportData.KeyLearningElapsed = (Val))


// DAT Read
#define mDATReadU1BitDATTrpIdentifierOfPresentKeyIsReceivedDefault() (DatTrpExportData.IdentifierOfPresentKeyIsReceived)
#define mDATReadU1BitDATTrpIdentifierOfPresentKeyIsValidDefault() (DatTrpExportData.IdentifierOfPresentKeyIsValid)
#define mDATReadU1BitDATTrpResponseToChallengeIsPresentDefault() (DatTrpExportData.ResponseToChallengeIsPresent)
#define mDATReadU1BitDATTrpResponseToChallengeIsValidDefault() (DatTrpExportData.ResponseToChallengeIsValid)
#define mDATReadU1BitDATTrpPresentKeyLockedDefault() (DatTrpExportData.PresentKeyLocked)
#define mDATReadU8BitDATTrpFrequencyOfPresentKeyDefault() (DatTrpExportData.FrequencyOfPresentKey)
#define mDATReadU8BitDATTrpDiagKeyFrequencyDefault() (DatTrpExportData.DiagKeyFrequency)
#define mDATReadU32BitDATTrpIdentifierOfPresentKeyDefault() (DatTrpExportData.IdentifierOfPresentKey)
#define mDATReadU1BitDATTrpKeyWithRFDefault()	(DatTrpExportData.KeyWithRF)
#define mDATReadU32BitDATTrpDataReadDefault() (DatTrpExportData.DataRead)
#define mDATReadU32BitDATTrpResynchronizationValueDefault() (DatTrpExportData.ResynchronizationValue)
#define mDATReadU8BitDATTrpIndexOfKeyRecognizedDefault() (DatTrpExportData.IndexOfKeyRecognized)
#define mDATReadU8BitDATTrpAuthenticationStateDefault() (DatTrpExportData.AuthenticationState)
#define mDATReadU8BitDATTrpSleepControlStateDefault() (DatTrpExportData.SleepControlState)
#define mDATReadU8BitDATTrpWriteAccessStateDefault() (DatTrpExportData.WriteAccessState)
#define mDATReadU8BitDATTrpResynchronizationStateDefault() (DatTrpExportData.ResynchronizationState)
#define mDATReadU8BitDATTrpAuthentTryCounterDefault()  (DatTrpExportData.AuthentTryCounter)
#define mDATReadU1BitVirginKeyAuthentOkDefault() (DatTrpExportData.VirginKeyAuthentOk)  
#define mDATReadU1BitDATTrpActiveTestModeDefault() (DatTrpExportData.ActiveTestMode)
#define mDATReadU1BitDATTrpWriteAccessWritingErrorDefault() (DatTrpExportData.WriteAccessWritingError)
#define mDATReadU1BitDATTrpWriteAccessReadingErrorDefault() (DatTrpExportData.WriteAccessReadingError)
#define mDATReadTableU8BitDATTrpTransportISKDefault(Index) (DATTrpTransportISK[Index])
#define mDATReadU32BitRepToChallengeDefault() (DatTrpExportData.RepToChallange)

#define mDATReadU1BitDATTrpOutputActiveDefault() (u8DATTrpOutState)

//-----------------------------------------------------------------------------
// Exported type
//
// typedef Expression tLAYCmpTypeName;
//-----------------------------------------------------------------------------

typedef struct tDATTrpChallengeType
{
    U32 ulSignature;
    U32 ulRandomNumber;
}tDATTrpChallenge;

//QACJ 0635:amanevd:  Bitfields of type U8 are used to optimize RAM usage 
typedef struct tDatTrpExportDataType
{
    tDATTrpChallenge  ExchChallenge;
    // U32 Input Data
    U32 DataToWrite;

    // U32 Output Data
    U32 IdentifierOfPresentKey;
    U32 DataRead;
    U32 ResynchronizationValue;
    U32 RepToChallange;
    U32 RepToChallangeDecrypt;

    // U8 Input Data
    U8  ISKForAuthent[cDATTrpISKLengthInBytes];
    U8  PageNumber;

    // U8 Output Data
    U8  FrequencyOfPresentKey;
    U8  DiagKeyFrequency;
    U8  IndexOfKeyRecognized;
    U8  LastVerlogStatus;
    U8  AuthentTryCounter;

    // U8 Output Data - Service state
    U8  AuthenticationState;
    U8  WakeUpControlState;
    U8  SleepControlState;
    U8  StopControlState;
    U8  WriteAccessState;
    U8  ResynchronizationState;

    // U8 Bitfield Input Data
    U8  AuthentInLearningMode             : 1;
    U8  WriteSecretKeyHigh                : 1;
    U8  ActiveTestMode                    : 1;

    // U8 Bitfield Output Data
    U8  VirginKeyAuthentOk                : 1;
    U8  KeyWithExtendedMemory             : 1;
    U8  IdentifierOfPresentKeyIsReceived  : 1;
    U8  IdentifierOfPresentKeyIsValid     : 1;
    U8  ResponseToChallengeIsPresent      : 1;
    U8  ResponseToChallengeIsValid        : 1;
    U8  PresentKeyLocked                  : 1;
    U8  KeyWithRF                         : 1;
    U8  KeyStandard                       : 1;
    U8  KeyLearningElapsed                : 1;
    U8  WriteAccessWritingError           : 1;
    U8  WriteAccessReadingError           : 1;
} tDatTrpExportData;

//-----------------------------------------------------------------------------
// Exported data
//
// extern  tType   u8LAYCmpVariableName;
// extern  tType*  ps32LAYCmpVariableName; 
//-----------------------------------------------------------------------------

extern tDatTrpExportData DatTrpExportData;

extern U8 u8DATTrpOutState;
//-----------------------------------------------------------------------------
// Constant exported data
//
// extern const tType  s8LAYCmpVariableName;
//-----------------------------------------------------------------------------
extern const U8 DATTrpTransportISK[cDATTrpISKLengthInBytes];

//-----------------------------------------------------------------------------
// Exported functions
//
// extern tReturnType LAYCmpFunctionName(tTypeArgument1 ArgumentName1, ... );
//-----------------------------------------------------------------------------
extern CALLT_TYPE void DATTrpControl(const tCtrl Ctrl);
extern void DATTrpInit(void);
extern void DATTrpMaintainActiveState(void);

#endif   // I_DAT_TRP_H
