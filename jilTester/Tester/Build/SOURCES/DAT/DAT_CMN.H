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
// Component:    DAT_CMN
// -----------------------------------------------------------------------------
// $Date:   Feb 19 2010 10:13:12  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_CMN/DAT_CMN.H-arc  $
// $Revision:   1.17  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_CMN/DAT_CMN.H-arc  $
// 
//    Rev 1.17   Feb 19 2010 10:13:12   adzhelp
// Cm007575: Management of no-init flag 'BcmSleepRequested'
// 
//    Rev 1.16   Feb 18 2010 15:16:56   adzhelp
// Cm006593, Cm006594: Activation on washer switch rising edge.
// 
//    Rev 1.15   Feb 04 2010 11:51:04   adzhelp
// Cm007297: Control macros for EEPROM reprogramming mode added
// 
//    Rev 1.14   Feb 03 2010 14:01:00   adzhelp
// Cm005245: Refresh callback for LIB_PCF implemented
// 
//    Rev 1.13   Nov 30 2009 15:40:46   adzhelp
// Cm006742: FRW / RRW common data added
// 
//    Rev 1.12   Nov 04 2009 16:20:56   adzhelp
// Cm005566: Implementation of HW Protection
// 
//    Rev 1.11   Sep 25 2009 10:28:46   adzhelp
// Cm005225: Flag HazardAlarmRequested added
// 
//    Rev 1.10   Sep 23 2009 10:25:08   amanevd
// Cm005133: tDATCmnData structure split to tDATCmnData and tDATCmnImmoData
// 
//    Rev 1.9   Sep 03 2009 12:37:04   amanevd
// Cm005133: Diagnostic information is cleared on MERA timeout, VERLOGON included
// 
//    Rev 1.8   Aug 07 2009 18:09:42   amanevd
// Cm005142: Implementation of Confidential Diagnostic
// 
//    Rev 1.7   Jul 30 2009 14:06:48   amarinm1
// CM004936: Some macros for updating flashing frequency were added.
// 
//    Rev 1.6   Jul 16 2009 11:42:54   amanevd
// Cm005193: Macros mDATReadU1BitECMIsProtectedDefault should be removed
// 
//    Rev 1.5   Jul 15 2009 10:08:32   adzhelp
// Cm005586: Code review corrections
// 
//    Rev 1.4   Jul 14 2009 14:29:18   amanevd
// Cm005586: KeyFrequency signal removed
// 
//    Rev 1.3   Apr 28 2009 09:54:26   adzhelp
// Cm003619: Common object updated for immobilizer and RF integration
// 
//    Rev 1.2   Mar 20 2009 18:39:04   adzhelp
// Cm003517: Macros for version number corrected
// 
//    Rev 1.1   Mar 20 2009 17:55:44   adzhelp
// Cm003619, Cm003128, Cm003263: Version number updated and stub interfaces created
// 
//    Rev 1.0   18 Feb 2009 14:18:18   ailievb
// Initial revision.
//******************************************************************************

#ifndef I_DAT_CMN_H
#define I_DAT_CMN_H (1)

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------
#include "tos.h"

//------------------------------------------------------------------------------
// Constant data
//------------------------------------------------------------------------------
#define cDATNoVerlogPattern                 ((U8)0)
#define cDATSwitchOnVerlogPattern           ((U8)1)
#define cDATSwitchOffVerlogPattern          ((U8)3)
#define cDATVehicleProtectedVerlogPattern   ((U8)4)
#define cDATLearningVerlogPattern           ((U8)5)
#define cDATKeyNotRecognizedVerlogPattern   ((U8)6)

#define cDATNoLearningMode                  ((U8)0x00) // Value defined for diag
#define cDATFactoryMode                     ((U8)0x01) // Value defined for diag
#define cDATBcmReplacement                  ((U8)0x02) // Value defined for diag
#define cDATKeyReassignment                 ((U8)0x04) // Value defined for diag

// Flashing frequency   
#define cDATCmnNoFlashing                   ((U8)0)
#define cDATCmnNormalFlashingMode           ((U8)1)
#define cDATCmnDegradedFlashingMode         ((U8)2)

// Flasher lamps test                      
#define cDATCmnFlasherLampsNotTested        ((U8)0)
#define cDATCmnFlasherLampIsBurnedOut       ((U8)1)
#define cDATCmnFlasherLampsAreOK            ((U8)2)

//------------------------------------------------------------------------------
// Exported type
//------------------------------------------------------------------------------

typedef struct sDATCmnData
{
    // RKE
    U1 PcfRefreshAllowed;

    // Flashers
    U8 FlashingFrequency;                               
    U8 FlasherLampsTestResult;                         
    U1 HazardAlarmRequested;

    // Faults
    U1 DefHornCCBat;
    U1 DefHornCCGnd;
    U1 DefDfrToGnd;                                     
    U1 DefDfrToBat;                                     
    U1 DefVerlogToBat;                                  
    U1 DefVerlogToGnd;
    U1 DefVerlogLedCC;
    U1 DefDoorlockLedCC;
    U1 DefTrpShortCircuitToGnd;                         
    U1 DefTrpShortCircuitToBat;                         
    U1 DefEEPROM;                                       
    U1 DefClignL;
    U1 DefClignR;
    U1 DefAirbag;                                       
    U1 DefAFAR;                                         
    U1 DefAFAV;                                         
    U1 DefKLineCC;
    U1 DefRrwCC;
    // RAM faults
    U1 DefBtonCpeFer;                                   
    U1 DefBtonCpeOuv;                                   
                                                        
    // DoorLock diag                                        
    U1 LastCommandOrigin;                              
    U1 VehicleIsAutoRelocked;                          
    U1 VehicleIsLockedWithSpeed;                       
    U1 VehiculeHasBeenMoving;                          
    U1 LastOpeningPanelControl;

    // Wipers
    U1 FrontWasherButtonBlocked;
    U1 RearWasherButtonBlocked;

} tDATCmnData;

typedef struct sDATCmnImmoData
{
// Immobilizer common data
    U1 FactoryModeAuthorized;
    U1 AfterSaleModeAuthorized;
    U1 ISKSuccessfullyWritten;
    U1 RSKSuccessfullyWritten;
    U1 SynchroSuccessfullyWritten;
    U1 AFSCodeIsOk;
    U1 WritingErrorInEepForKey1InFactoryMode;
    U1 WritingErrorInEepForKey2InFactoryMode;
    U1 WritingErrorInEepInBcmReplacement;
    U1 AfterSaleModeValidationAuthorized;
    U1 WritingErrorInEepInReassignment;
    U1 KeyIsAlreadyLearnt;
    U1 VerlogOn;
    
    U8 NumberOfKeysLearnt;
    U8 NumberOfKeys315MHzLearnt;
    U8 NumberOfKeys315MHzSmallLearnt;
    U8 NumberOfKeys433MHzLearnt;
    U8 LearningModeInProgress;
    U8 LedVerlogPattern;
    U8 AuthentPermanentFailCounter;
    U8 AuthentPermanentResynchroFailCounter;
    U8 AuthentLocalFailureCounter;
    U8 COD_ERR_APP;
    
    U16 AuthentPermanentTotalCounter;
} tDATCmnImmoData;

//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------ 
extern tDATCmnData DATCmnData;
extern tDATCmnImmoData DATCmnImmoData;

// FRW / RRW common data
// No access macros provided for clarity
extern U8 u8DATCmnTPS_ARRET_old;
extern U8 u8DATCmnTPS_MAX_COUPLBLOC_old;
extern U8 u8DATCmnTPS_CAD_FIXE_old;
extern U8 u8DATCmnTPS_APPUILAV_old;
extern U8 u8DATCmnTPS_ESSUIE_MINI_old;
extern U8 u8DATCmnTPS_REPRISE_old;

extern tTOSTimer DATCmnFrRrwDisableTimeout;
extern tTOSTimer DATCmnFrRrwWipingTimeout;
extern tTOSTimer DATCmnFrRrwIntermittentPause;
extern tTOSTimer DATCmnFrRrwMinimumWipingTime;
extern tTOSTimer DATCmnFrwWashPressThreshold;
extern tTOSTimer DATCmnRrwWipingTimeoutReprise;

                                                                          
//------------------------------------------------------------------------------
// Constant exported data
//------------------------------------------------------------------------------
extern const U8 DATCmnVerVersionNum[2];
extern const U8 DATCmnVerRevisionNum[2];
extern const U8 DATCmnTfcVersionNum;
extern const U8 DATCmnTfcRevisionNum;

//------------------------------------------------------------------------------
// Exported Macros
//------------------------------------------------------------------------------
// RKE
#define mDATWriteU1BitPcfRefreshAllowedDefault(Val)                 (DATCmnData.PcfRefreshAllowed = (Val))

// Flashers
#define mDATReadU8BitFlashingFrequencyDefault()                     (DATCmnData.FlashingFrequency)
#define mDATWriteU8BitFlashingFrequencyDefault(Val)                 (DATCmnData.FlashingFrequency = (Val))
#define mDATReadU8BitFlasherLampsTestResultDefault()                (DATCmnData.FlasherLampsTestResult)
#define mDATWriteU8BitFlasherLampsTestResultDefault(Val)            (DATCmnData.FlasherLampsTestResult = (Val))
#define mDATReadU1BitHazardAlarmRequestedDefault()                  (DATCmnData.HazardAlarmRequested)
#define mDATWriteU1BitHazardAlarmRequestedDefault(Val)              (DATCmnData.HazardAlarmRequested = (Val))

// Wipers
#define mDATReadU1BitFrontWasherButtonBlockedDefault()              (DATCmnData.FrontWasherButtonBlocked)
#define mDATReadU1BitRearWasherButtonBlockedDefault()               (DATCmnData.RearWasherButtonBlocked)
#define mDATWriteU1BitFrontWasherButtonBlockedDefault(Val)          (DATCmnData.FrontWasherButtonBlocked = (Val))
#define mDATWriteU1BitRearWasherButtonBlockedDefault(Val)           (DATCmnData.RearWasherButtonBlocked = (Val))

// Faults read access
#define mDATReadU1BitDefHornCCBatDefault()              (DATCmnData.DefHornCCBat)
#define mDATReadU1BitDefHornCCGndDefault()              (DATCmnData.DefHornCCGnd)
#define mDATReadU1BitDefDfrToGndDefault()               (DATCmnData.DefDfrToGnd)
#define mDATReadU1BitDefDfrToBatDefault()               (DATCmnData.DefDfrToBat)
#define mDATReadU1BitDefVerlogToBatDefault()            (DATCmnData.DefVerlogToBat)
#define mDATReadU1BitDefVerlogToGndDefault()            (DATCmnData.DefVerlogToGnd)
#define mDATReadU1BitDefVerlogLedCCDefault()            (DATCmnData.DefVerlogLedCC)
#define mDATReadU1BitDefDoorlockLedCCDefault()          (DATCmnData.DefDoorlockLedCC)
#define mDATReadU1BitDefTrpShortCircuitToGndDefault()   (DATCmnData.DefTrpShortCircuitToGnd)
#define mDATReadU1BitDefTrpShortCircuitToBatDefault()   (DATCmnData.DefTrpShortCircuitToBat)
#define mDATReadU1BitDefEEPROMDefault()                 (DATCmnData.DefEEPROM)
#define mDATReadU1BitDefClignLDefault()                 (DATCmnData.DefClignL)
#define mDATReadU1BitDefClignRDefault()                 (DATCmnData.DefClignR)
#define mDATReadU1BitDefAirbagDefault()                 (DATCmnData.DefAirbag)
#define mDATReadU1BitDefAFARDefault()                   (DATCmnData.DefAFAR)
#define mDATReadU1BitDefAFAVDefault()                   (DATCmnData.DefAFAV)
#define mDATReadU1BitDefBtonCpeFerDefault()             (DATCmnData.DefBtonCpeFer)
#define mDATReadU1BitDefBtonCpeOuvDefault()             (DATCmnData.DefBtonCpeOuv)
#define mDATReadU1BitDefKLineCCDefault()                (DATCmnData.DefKLineCC)
#define mDATReadU1BitDefRrwCCDefault()                  (DATCmnData.DefRrwCC)

// Doorlock read access
#define mDATReadU1BitLastCommandOriginDefault()         (DATCmnData.LastCommandOrigin)
#define mDATReadU1BitVehicleIsAutoRelockedDefault()     (DATCmnData.VehicleIsAutoRelocked)
#define mDATReadU1BitVehicleIsLockedWithSpeedDefault()  (DATCmnData.VehicleIsLockedWithSpeed)
#define mDATReadU1BitVehiculeHasBeenMovingDefault()     (DATCmnData.VehiculeHasBeenMoving)
#define mDATReadU1BitLastOpeningPanelControlDefault()   (DATCmnData.LastOpeningPanelControl)

// Faults write access
#define mDATWriteU1BitDefHornCCBatDefault(Val)              (DATCmnData.DefHornCCBat=(Val))
#define mDATWriteU1BitDefHornCCGndDefault(Val)              (DATCmnData.DefHornCCGnd=(Val))
#define mDATWriteU1BitDefDfrToGndDefault(Val)               (DATCmnData.DefDfrToGnd=(Val))
#define mDATWriteU1BitDefDfrToBatDefault(Val)               (DATCmnData.DefDfrToBat=(Val))
#define mDATWriteU1BitDefVerlogToBatDefault(Val)            (DATCmnData.DefVerlogToBat=(Val))
#define mDATWriteU1BitDefVerlogToGndDefault(Val)            (DATCmnData.DefVerlogToGnd=(Val))
#define mDATWriteU1BitDefVerlogLedCCDefault(Val)            (DATCmnData.DefVerlogLedCC=(Val))
#define mDATWriteU1BitDefDoorlockLedCCDefault(Val)          (DATCmnData.DefDoorlockLedCC=(Val))
#define mDATWriteU1BitDefTrpShortCircuitToGndDefault(Val)   (DATCmnData.DefTrpShortCircuitToGnd=(Val))
#define mDATWriteU1BitDefTrpShortCircuitToBatDefault(Val)   (DATCmnData.DefTrpShortCircuitToBat=(Val))
#define mDATWriteU1BitDefEEPROMDefault(Val)                 (DATCmnData.DefEEPROM=(Val))
#define mDATWriteU1BitDefClignLDefault(Val)                 (DATCmnData.DefClignL=(Val))
#define mDATWriteU1BitDefClignRDefault(Val)                 (DATCmnData.DefClignR=(Val))
#define mDATWriteU1BitDefAirbagDefault(Val)                 (DATCmnData.DefAirbag=(Val))
#define mDATWriteU1BitDefAFARDefault(Val)                   (DATCmnData.DefAFAR=(Val))
#define mDATWriteU1BitDefAFAVDefault(Val)                   (DATCmnData.DefAFAV=(Val))
#define mDATWriteU1BitDefBtonCpeFerDefault(Val)             (DATCmnData.DefBtonCpeFer=(Val))
#define mDATWriteU1BitDefBtonCpeOuvDefault(Val)             (DATCmnData.DefBtonCpeOuv=(Val))
#define mDATWriteU1BitDefKLineCCDefault(Val)                (DATCmnData.DefKLineCC=(Val))
#define mDATWriteU1BitDefRrwCCDefault(Val)                  (DATCmnData.DefRrwCC=(Val))

// Version identification
#define mDATReadTableU8BitVerVersionNumDefault(Index)       (DATCmnVerVersionNum[Index])
#define mDATReadTableU8BitVerRevisionNumDefault(Index)      (DATCmnVerRevisionNum[Index])
#define mDATReadU8BitTfcVersionNumDefault()                 (DATCmnTfcVersionNum)
#define mDATReadU8BitTfcRevisionNumDefault()                (DATCmnTfcRevisionNum)


// Immobilizer Common Data
#define mDATReadU1BitFactoryModeAuthorizedDefault()    \
    (DATCmnImmoData.FactoryModeAuthorized)
#define mDATWriteU1BitFactoryModeAuthorizedDefault(Value)  \
    (DATCmnImmoData.FactoryModeAuthorized = (Value))

#define mDATReadU1BitAfterSaleModeAuthorizedDefault()    \
    (DATCmnImmoData.AfterSaleModeAuthorized)
#define mDATWriteU1BitAfterSaleModeAuthorizedDefault(Value)  \
    (DATCmnImmoData.AfterSaleModeAuthorized = (Value))

#define mDATReadU1BitISKSuccessfullyWrittenDefault()    \
    (DATCmnImmoData.ISKSuccessfullyWritten)
#define mDATWriteU1BitISKSuccessfullyWrittenDefault(Value)  \
    (DATCmnImmoData.ISKSuccessfullyWritten = (Value))

#define mDATReadU1BitRSKSuccessfullyWrittenDefault()    \
    (DATCmnImmoData.RSKSuccessfullyWritten)
#define mDATWriteU1BitRSKSuccessfullyWrittenDefault(Value)  \
    (DATCmnImmoData.RSKSuccessfullyWritten = (Value))

#define mDATReadU1BitSynchroSuccessfullyWrittenDefault()    \
    (DATCmnImmoData.SynchroSuccessfullyWritten)
#define mDATWriteU1BitSynchroSuccessfullyWrittenDefault(Value)  \
    (DATCmnImmoData.SynchroSuccessfullyWritten = (Value))

#define mDATReadU1BitAFSCodeIsOkDefault()    \
    (DATCmnImmoData.AFSCodeIsOk)
#define mDATWriteU1BitAFSCodeIsOkDefault(Value)  \
    (DATCmnImmoData.AFSCodeIsOk = (Value))

#define mDATReadU1BitWritingErrorInEepForKey1InFactoryModeDefault()    \
    (DATCmnImmoData.WritingErrorInEepForKey1InFactoryMode)
#define mDATWriteU1BitWritingErrorInEepForKey1InFactoryModeDefault(Value)  \
    (DATCmnImmoData.WritingErrorInEepForKey1InFactoryMode = (Value))

#define mDATReadU1BitWritingErrorInEepForKey2InFactoryModeDefault()    \
    (DATCmnImmoData.WritingErrorInEepForKey2InFactoryMode)
#define mDATWriteU1BitWritingErrorInEepForKey2InFactoryModeDefault(Value)  \
    (DATCmnImmoData.WritingErrorInEepForKey2InFactoryMode = (Value))

#define mDATReadU1BitAfterSaleModeValidationAuthorizedDefault()    \
    (DATCmnImmoData.AfterSaleModeValidationAuthorized)
#define mDATWriteU1BitAfterSaleModeValidationAuthorizedDefault(Value)  \
    (DATCmnImmoData.AfterSaleModeValidationAuthorized = (Value))

#define mDATReadU1BitWritingErrorInEepInBcmReplacementDefault()    \
    (DATCmnImmoData.WritingErrorInEepInBcmReplacement)
#define mDATWriteU1BitWritingErrorInEepInBcmReplacementDefault(Value)  \
    (DATCmnImmoData.WritingErrorInEepInBcmReplacement = (Value))

#define mDATReadU1BitWritingErrorInEepInReassignmentDefault()    \
    (DATCmnImmoData.WritingErrorInEepInReassignment)
#define mDATWriteU1BitWritingErrorInEepInReassignmentDefault(Value)  \
    (DATCmnImmoData.WritingErrorInEepInReassignment = (Value))

#define mDATReadU8BitNumberOfKeysLearntDefault()    \
    (DATCmnImmoData.NumberOfKeysLearnt)
#define mDATWriteU8BitNumberOfKeysLearntDefault(Value)  \
    (DATCmnImmoData.NumberOfKeysLearnt = (Value))

#define mDATReadU8BitNumberOfKeys315MHzLearntDefault() \
    (DATCmnImmoData.NumberOfKeys315MHzLearnt)
#define mDATWriteU8BitNumberOfKeys315MHzLearntDefault(Value)  \
    (DATCmnImmoData.NumberOfKeys315MHzLearnt = (Value))

#define mDATReadU8BitNumberOfKeys315MHzSmallLearntDefault() \
    (DATCmnImmoData.NumberOfKeys315MHzSmallLearnt)
#define mDATWriteU8BitNumberOfKeys315MHzSmallLearntDefault(Value)  \
    (DATCmnImmoData.NumberOfKeys315MHzSmallLearnt = (Value))

#define mDATReadU8BitNumberOfKeys433MHzLearntDefault() \
    (DATCmnImmoData.NumberOfKeys433MHzLearnt)
#define mDATWriteU8BitNumberOfKeys433MHzLearntDefault(Value)  \
    (DATCmnImmoData.NumberOfKeys433MHzLearnt = (Value))

#define mDATReadU8BitLearningModeInProgressDefault() \
    (DATCmnImmoData.LearningModeInProgress)
#define mDATWriteU8BitLearningModeInProgressDefault(Value)  \
    (DATCmnImmoData.LearningModeInProgress = (Value))

#define mDATReadU8BitLedVerlogPatternDefault() \
    (DATCmnImmoData.LedVerlogPattern)
#define mDATWriteU8BitLedVerlogPatternDefault(Value)  \
    (DATCmnImmoData.LedVerlogPattern = (Value))

#define mDATReadU8BitAuthentPermanentFailCounterDefault() \
    (DATCmnImmoData.AuthentPermanentFailCounter)
#define mDATWriteU8BitAuthentPermanentFailCounterDefault(Value)  \
    (DATCmnImmoData.AuthentPermanentFailCounter = (Value))

#define mDATReadU8BitAuthentPermanentResynchroFailCounterDefault() \
    (DATCmnImmoData.AuthentPermanentResynchroFailCounter)
#define mDATWriteU8BitAuthentPermanentResynchroFailCounterDefault(Value)  \
    (DATCmnImmoData.AuthentPermanentResynchroFailCounter = (Value))

#define mDATReadU8BitAuthentLocalFailureCounterDefault() \
    (DATCmnImmoData.AuthentLocalFailureCounter)
#define mDATWriteU8BitAuthentLocalFailureCounterDefault(Value)  \
    (DATCmnImmoData.AuthentLocalFailureCounter = (Value))

#define mDATReadU8BitCOD_ERR_APPDefault() \
    (DATCmnImmoData.COD_ERR_APP)
#define mDATWriteU8BitCOD_ERR_APPDefault(Value)  \
    (DATCmnImmoData.COD_ERR_APP = (Value))

#define mDATReadU16BitAuthentPermanentTotalCounterDefault() \
    (DATCmnImmoData.AuthentPermanentTotalCounter)
#define mDATWriteU16BitAuthentPermanentTotalCounterDefault(Value)  \
    (DATCmnImmoData.AuthentPermanentTotalCounter = (Value))

#define mDATReadU1BitDATKeyIsAlreadyLearntDefault() \
    (DATCmnImmoData.KeyIsAlreadyLearnt)
#define mDATWriteU1BitDATKeyIsAlreadyLearntDefault(Value)   \
    (DATCmnImmoData.KeyIsAlreadyLearnt = (Value))

#define mDATReadU1BitVERLOGONDefault() \
    (DATCmnImmoData.VerlogOn)
#define mDATWriteU1BitVERLOGONDefault(Value)   \
    (DATCmnImmoData.VerlogOn = (Value))

// Doorlock write access
#define mDATWriteU1BitLastCommandOriginDefault(Val)         (DATCmnData.LastCommandOrigin=(Val))
#define mDATWriteU1BitVehicleIsAutoRelockedDefault(Val)     (DATCmnData.VehicleIsAutoRelocked=(Val))
#define mDATWriteU1BitVehicleIsLockedWithSpeedDefault(Val)  (DATCmnData.VehicleIsLockedWithSpeed=(Val))
#define mDATWriteU1BitVehiculeHasBeenMovingDefault(Val)     (DATCmnData.VehiculeHasBeenMoving=(Val))
#define mDATWriteU1BitLastOpeningPanelControlDefault(Val)   (DATCmnData.LastOpeningPanelControl=(Val))

#define mDATReadU1BitBcmSleepRequestedDefault()             (DATCmnGetBcmSleepRequested() != cFalse)
#define mDATWriteU1BitBcmSleepRequestedDefault(Val)         (DATCmnSetBcmSleepRequested(Val))

// Control macros
//------------------------------------------------------------------------------

#define mDATControlEepromReprogramming(Control) \
    mDATControlEepromReprogramming##Control()

#define mDATControlEepromReprogrammingPrepare() \
    LDBControl(cLDBChannelDou, cLDBDouPrepareEepromReprog)
#define mDATControlEepromReprogrammingStart() \
    LDBControl(cLDBChannelDou, cLDBDouStartEepromReprog)
    

//------------------------------------------------------------------------------
// Exported functions
//------------------------------------------------------------------------------
extern void DATCmnInitialize(void);
extern void DATCmnLeaveStartingStepState(void);
extern void DATCmnGetAprTrpResource(void);
extern void DATCmnReleaseAprTrpResource(void);
extern void DATCmnGetCarTrpResource(void);
extern void DATCmnReleaseCarTrpResource(void);
extern void DATCmnPcfRefresh(void);
extern MEM_TYPE BOOL DATCmnGetBcmSleepRequested(void);
extern MEM_TYPE void DATCmnSetBcmSleepRequested(BOOL bSleepRequestedP);

#endif   //  I_DAT_CMN_H 
