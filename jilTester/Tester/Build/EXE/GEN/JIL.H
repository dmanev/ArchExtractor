/**************************************************************************

  Component             JIL.H
  -------------------------------------------------------------------------
  Copyright     This software is JCI property. Duplication or
                disclosure is prohibited without JCI written permission
  -------------------------------------------------------------------------
   
   - This file should only contain data useful to the programmer to use
     this component
   - Component exported macros, constants and types are defined in this file
   - Component exported variables and functions are declared in this file
     with the "extern" keyword
   
  -------------------------------------------------------------------------
    This file was generated by TOS.dll 01.03
	
	Generation date : 15/02/2011 13:28
	Reference File  : ..\SOURCES\LAP\lap_sup.jil
	
***************************************************************************/


/*---------------------------------------------------------------------------
     Definition of the Tasks's IDs
  ---------------------------------------------------------------------------*/
// Number of Tasks Including Idle Task
#define cTOSMaxTaskNumber 14UL

// IDs
#ifndef TOS_PREEMPTIVE
  #define cTOSTaskIdDATEepTask             ((tTOSTaskID)0x00000001UL) // Task DATEepTask                      , Priority 10
  #define cTOSTaskIdDATCpuRefreshWatchDogTask ((tTOSTaskID)0x00000002UL) // Task DATCpuRefreshWatchDogTask       , Priority 20
  #define cTOSTaskIdGraphEngineTaskSleep   ((tTOSTaskID)0x00000004UL) // Task GraphEngineTaskSleep            , Priority 30
  #define cTOSTaskIdDATBuzTask             ((tTOSTaskID)0x00000008UL) // Task DATBuzTask                      , Priority 40
  #define cTOSTaskID_WriteLogical          ((tTOSTaskID)0x00000010UL) // Task DATDouTask                      , Priority 50
  #define cTOSTaskIdGraphEngineTask80Ms    ((tTOSTaskID)0x00000020UL) // Task GraphEngineTask80Ms             , Priority 60
  #define cTOSTaskIdGraphEngineTask20Ms    ((tTOSTaskID)0x00000040UL) // Task GraphEngineTask20Ms             , Priority 62
  #define cTOSTaskIdGraphEngineTask        ((tTOSTaskID)0x00000080UL) // Task GraphEngineTask                 , Priority 64
  #define cTOSTaskID_ControlKwp            ((tTOSTaskID)0x00000100UL) // Task DATKwpTask                      , Priority 70
  #define cTOSTaskIdDATRbgTask             ((tTOSTaskID)0x00000200UL) // Task DATRbgTask                      , Priority 80
  #define cTOSTaskID_ReadLogical           ((tTOSTaskID)0x00000400UL) // Task DATDinTask                      , Priority 90
  #define cTOSTaskID_TacheANA              ((tTOSTaskID)0x00000800UL) // Task DATAnaTask                      , Priority 100
  #define cTOSTaskIdTOSClock               ((tTOSTaskID)0x00001000UL) // Task TOSClock                        , Priority 500
#else
  #define cTOSTaskIdDATEepTask             ((tTOSTaskID) 1UL) // Task DATEepTask                      , Priority 10
  #define cTOSTaskIdDATCpuRefreshWatchDogTask ((tTOSTaskID) 2UL) // Task DATCpuRefreshWatchDogTask       , Priority 20
  #define cTOSTaskIdGraphEngineTaskSleep   ((tTOSTaskID) 3UL) // Task GraphEngineTaskSleep            , Priority 30
  #define cTOSTaskIdDATBuzTask             ((tTOSTaskID) 4UL) // Task DATBuzTask                      , Priority 40
  #define cTOSTaskID_WriteLogical          ((tTOSTaskID) 5UL) // Task DATDouTask                      , Priority 50
  #define cTOSTaskIdGraphEngineTask80Ms    ((tTOSTaskID) 6UL) // Task GraphEngineTask80Ms             , Priority 60
  #define cTOSTaskIdGraphEngineTask20Ms    ((tTOSTaskID) 7UL) // Task GraphEngineTask20Ms             , Priority 62
  #define cTOSTaskIdGraphEngineTask        ((tTOSTaskID) 8UL) // Task GraphEngineTask                 , Priority 64
  #define cTOSTaskID_ControlKwp            ((tTOSTaskID) 9UL) // Task DATKwpTask                      , Priority 70
  #define cTOSTaskIdDATRbgTask             ((tTOSTaskID)10UL) // Task DATRbgTask                      , Priority 80
  #define cTOSTaskID_ReadLogical           ((tTOSTaskID)11UL) // Task DATDinTask                      , Priority 90
  #define cTOSTaskID_TacheANA              ((tTOSTaskID)12UL) // Task DATAnaTask                      , Priority 100
  #define cTOSTaskIdTOSClock               ((tTOSTaskID)13UL) // Task TOSClock                        , Priority 500
#endif

/*---------------------------------------------------------------------------
     Definition of Graphs's IDs
  ---------------------------------------------------------------------------*/
// Number of Graphs
#define cTOSSeqMaxGraphNumber 47UL

// IDs
#define cTOSSeqGraphIdEepromManager      ((tTOSSeqGraphId)0UL) // Graph EepromManager
#define cTOSSeqGraphIdDATTrpAuthentication ((tTOSSeqGraphId)1UL) // Graph DATTrpAuthentication
#define cTOSSeqGraphIdDATVlgOutputProtection ((tTOSSeqGraphId)2UL) // Graph DATVlgOutputProtection
#define cTOSSeqKWPTreatRequest           ((tTOSSeqGraphId)3UL) // Graph LAPKwpTreatRequest
#define cTOSSeqKWPTreatCommunication     ((tTOSSeqGraphId)4UL) // Graph LAPKwpTreatCommunication
#define cTOSSeqLAPAfsIOControlByLocalID  ((tTOSSeqGraphId)5UL) // Graph LAPAfsIOControlByLocalID
#define cTOSSeqLAPTfcAutoTestIO          ((tTOSSeqGraphId)6UL) // Graph LAPTfcAutoTestIO
#define cTOSSeqLAPTfcGraph               ((tTOSSeqGraphId)7UL) // Graph LAPTfcGraph
#define cTOSSeqLAPTfcEepTest             ((tTOSSeqGraphId)8UL) // Graph LAPTfcEepTest
#define cTOSSeqGraphIdDLKInputData       ((tTOSSeqGraphId)9UL) // Graph DLKInputData
#define cTOSSeqGraphIdDLKOutputData      ((tTOSSeqGraphId)10UL) // Graph DLKOutputData
#define cTOSSeqGraphIdDLKMotorCommand    ((tTOSSeqGraphId)11UL) // Graph DLKMotorCommand
#define cTOSSeqGraphIdDLKAirbagManagement ((tTOSSeqGraphId)12UL) // Graph DLKAirbagManagement
#define cTOSSeqGraphIdLAPBuzMainGraph    ((tTOSSeqGraphId)13UL) // Graph LAPBuzMainGraph
#define cTOSSeqGraphIdLAPFliProtectionManagement ((tTOSSeqGraphId)14UL) // Graph LAPFliProtectionManagement
#define cTOSSeqGraphIdCARManageImmobiliserAndCarAntiTheft ((tTOSSeqGraphId)15UL) // Graph CARManageImmobiliserAndCarAntiTheft
#define cTOSSeqGraphIdRDFRearDefoggerManagement ((tTOSSeqGraphId)16UL) // Graph RDFRearDefoggerManagement
#define cTOSSeqGraphIdRDFProtectionManagement ((tTOSSeqGraphId)17UL) // Graph RDFProtectionManagement
#define cTOSSeqGraphIdLAPAlarms          ((tTOSSeqGraphId)18UL) // Graph LAPAlarms
#define cTOSSeqGraphIdAlarmAfterReset    ((tTOSSeqGraphId)19UL) // Graph AlarmAfterReset
#define cTOSSeqGraphIdLAPFrwEngineProtection ((tTOSSeqGraphId)20UL) // Graph LAPFrwEngineProtection
#define cTOSSeqGraphIdLAPFrwIntermittentWipe ((tTOSSeqGraphId)21UL) // Graph LAPFrwIntermittentWipe
#define cTOSSeqGraphIdLAPFrwWashing      ((tTOSSeqGraphId)22UL) // Graph LAPFrwWashing
#define cTOSSeqGraphIdLAPFrwControl      ((tTOSSeqGraphId)23UL) // Graph LAPFrwControl
#define cTOSSeqGraphIdLAPRrwEngineProtection ((tTOSSeqGraphId)24UL) // Graph LAPRrwEngineProtection
#define cTOSSeqGraphIdLAPRrwIntermittentWipe ((tTOSSeqGraphId)25UL) // Graph LAPRrwIntermittentWipe
#define cTOSSeqGraphIdLAPRrwWashing      ((tTOSSeqGraphId)26UL) // Graph LAPRrwWashing
#define cTOSSeqGraphIdLAPRrwInitialParking ((tTOSSeqGraphId)27UL) // Graph LAPRrwInitialParking
#define cTOSSeqGraphIdLAPRrwControl      ((tTOSSeqGraphId)28UL) // Graph LAPRrwControl
#define cTOSSeqGraphIdPerimeterAlarmManagement ((tTOSSeqGraphId)29UL) // Graph PerimeterAlarmManagement
#define cTOSSeqGraphIdDATTrpWriteAccess  ((tTOSSeqGraphId)30UL) // Graph DATTrpWriteAccess
#define cTOSSeqGraphIdDATTrpResynchronization ((tTOSSeqGraphId)31UL) // Graph DATTrpResynchronization
#define cTOSSeqGraphIdDATTrpTfcDiag      ((tTOSSeqGraphId)32UL) // Graph DATTrpTfcDiag
#define cTOSSeqGraphIdLAPIllInternalLightsManagement ((tTOSSeqGraphId)33UL) // Graph LAPIllInternalLightsManagement
#define cTOSSeqGraphIdLAPIllInternalLightsController ((tTOSSeqGraphId)34UL) // Graph LAPIllInternalLightsController
#define cTOSSeqGraphIdLAPFliInput        ((tTOSSeqGraphId)35UL) // Graph LAPFliInput
#define cTOSSeqGraphIdLAPFliLampsState   ((tTOSSeqGraphId)36UL) // Graph LAPFliLampsState
#define cTOSSeqGraphIdLRNUpdateLearningAuthorization ((tTOSSeqGraphId)37UL) // Graph LRNUpdateLearningAuthorization
#define cTOSSeqGraphIdLRNManageLearningService ((tTOSSeqGraphId)38UL) // Graph LRNManageLearningService
#define cTOSSeqGraphIdLAPExlGraph        ((tTOSSeqGraphId)39UL) // Graph LAPExlGraph
#define cTOSSeqGraphIdEepromNormalization ((tTOSSeqGraphId)40UL) // Graph EepromNormalization
#define cTOSSeqGraphIdDATVlgInput        ((tTOSSeqGraphId)41UL) // Graph DATVlgInput
#define cTOSSeqGraphIdSpeedManagement    ((tTOSSeqGraphId)42UL) // Graph SpeedManagement
#define cTOSSeqGraphIdRPMManagement      ((tTOSSeqGraphId)43UL) // Graph RPMManagement
#define cTOSSeqGraphIdDATRfReceptionManagement ((tTOSSeqGraphId)44UL) // Graph DATRfReceptionManagement
#define cTOSSeqGraphIdLAPVldPatternManagement ((tTOSSeqGraphId)45UL) // Graph LAPVldPatternManagement
#define cTOSSeqGraphIdSupervisor         ((tTOSSeqGraphId)46UL) // Graph Supervisor

/*---------------------------------------------------------------------------
     Definition of Graphs's Instances
  ---------------------------------------------------------------------------*/
// Number of Graph Instances

#define cTOSSeqEepromManagerNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqDATTrpAuthenticationNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqDATVlgOutputProtectionNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqLAPKwpTreatRequestNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqLAPKwpTreatCommunicationNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqLAPAfsIOControlByLocalIDNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqLAPTfcAutoTestIONumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqLAPTfcGraphNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqLAPTfcEepTestNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqDLKInputDataNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqDLKOutputDataNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqDLKMotorCommandNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqDLKAirbagManagementNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqLAPBuzMainGraphNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqLAPFliProtectionManagementNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqCARManageImmobiliserAndCarAntiTheftNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqRDFRearDefoggerManagementNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqRDFProtectionManagementNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqLAPAlarmsNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqAlarmAfterResetNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqLAPFrwEngineProtectionNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqLAPFrwIntermittentWipeNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqLAPFrwWashingNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqLAPFrwControlNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqLAPRrwEngineProtectionNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqLAPRrwIntermittentWipeNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqLAPRrwWashingNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqLAPRrwInitialParkingNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqLAPRrwControlNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqPerimeterAlarmManagementNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqDATTrpWriteAccessNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqDATTrpResynchronizationNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqDATTrpTfcDiagNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqLAPIllInternalLightsManagementNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqLAPIllInternalLightsControllerNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqLAPFliInputNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqLAPFliLampsStateNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqLRNUpdateLearningAuthorizationNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqLRNManageLearningServiceNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqLAPExlGraphNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqEepromNormalizationNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqDATVlgInputNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqSpeedManagementNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqRPMManagementNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqDATRfReceptionManagementNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqLAPVldPatternManagementNumberOfInstance ((tTOSSeqGraphInstance)1UL)
#define cTOSSeqSupervisorNumberOfInstance ((tTOSSeqGraphInstance)1UL)

/*---------------------------------------------------------------------------
     Definition of the Graph group's Macros
  ---------------------------------------------------------------------------*/
// Number of Graphs groups
#define cTOSSeqMaxGraphGroupsNumber 5UL

// Macros
#define mTOSSeqMotorDefault()            TOSSeqMotor(cTOSSeqGraphIdEepromManager,cTOSSeqGraphIdPerimeterAlarmManagement)
#define mTOSSeqMotorIdleGraphGroup()     TOSSeqMotor(cTOSSeqGraphIdSupervisor,cTOSSeqGraphIdSupervisor)
#define mTOSSeqMotorGraphGroup20Ms()     TOSSeqMotor(cTOSSeqGraphIdDATTrpWriteAccess,cTOSSeqGraphIdLAPExlGraph)
#define mTOSSeqMotorGraphGroupSleep()    TOSSeqMotor(cTOSSeqGraphIdDATRfReceptionManagement,cTOSSeqGraphIdLAPVldPatternManagement)
#define mTOSSeqMotorGraphGroup80Ms()     TOSSeqMotor(cTOSSeqGraphIdEepromNormalization,cTOSSeqGraphIdRPMManagement)

/*---------------------------------------------------------------------------
     Definition of the Signals's IDs
  ---------------------------------------------------------------------------*/
// Number of Signals
#define cTOSSigMaxSignalNumber 42UL

// IDs
#define cTOSSignalFrontWiperStopIsAllowed_LAP_FRW ((tTOSSignalID)0UL)
#define cTOSSignalRearWiperStopIsAllowed_LAP_RRW ((tTOSSignalID)1UL)
#define cTOSSignalFR_AUTOSTOP_SWFalling_LAP_FRW ((tTOSSignalID)2UL)
#define cTOSSignalRR_AUTOSTOP_SWFalling_LAP_RRW ((tTOSSignalID)3UL)
#define cTOSSignalChanging_RR_DOORS_SW_LAP_ILL ((tTOSSignalID)4UL)
#define cTOSSignalFalling_RR_DOORS_SW_LAP_ILL ((tTOSSignalID)5UL)
#define cTOSSignalRising_RR_DOORS_SW_LAP_ILL ((tTOSSignalID)6UL)
#define cTOSSignalChanging_FR_DOORS_SW_LAP_ILL ((tTOSSignalID)7UL)
#define cTOSSignalFalling_FR_DOORS_SW_LAP_ILL ((tTOSSignalID)8UL)
#define cTOSSignalRising_FR_DOORS_SW_LAP_ILL ((tTOSSignalID)9UL)
#define cTOSSignalFalling_PWR_IGN_LAP_ILL ((tTOSSignalID)10UL)
#define cTOSSignalRising_PWR_IGN_LAP_ILL ((tTOSSignalID)11UL)
#define cTOSSignalFalling_PWR_IGN_LAP_BUZ ((tTOSSignalID)12UL)
#define cTOSSignalRising_PWR_IGN_LAP_FLI ((tTOSSignalID)13UL)
#define cTOSSignalFalling_HAZARD_SW_LAP_FLI ((tTOSSignalID)14UL)
#define cTOSSignalFrontStopPositionDetected_LAP_FRW1 ((tTOSSignalID)15UL)
#define cTOSSignalFrontStopPositionDetected_LAP_FRW2 ((tTOSSignalID)16UL)
#define cTOSSignalRearStopPositionDetected_LAP_RRW1 ((tTOSSignalID)17UL)
#define cTOSSignalRearStopPositionDetected_LAP_RRW2 ((tTOSSignalID)18UL)
#define cTOSSignalRising_PWR_IGN_LAP_DLK ((tTOSSignalID)19UL)
#define cTOSSignalFalling_PWR_IGN_LAP_DLK ((tTOSSignalID)20UL)
#define cTOSSignalRising_FR_DOORS_SW_LAP_DLK ((tTOSSignalID)21UL)
#define cTOSSignalFalling_FR_DOORS_SW_LAP_DLK ((tTOSSignalID)22UL)
#define cTOSSignalChanging_FR_DOORS_SW_LAP_DLK ((tTOSSignalID)23UL)
#define cTOSSignalRising_RR_DOORS_SW_LAP_DLK ((tTOSSignalID)24UL)
#define cTOSSignalFalling_RR_DOORS_SW_LAP_DLK ((tTOSSignalID)25UL)
#define cTOSSignalChanging_RR_DOORS_SW_LAP_DLK ((tTOSSignalID)26UL)
#define cTOSSignalRising_DOOR_LOCK_SW_LAP_DLK ((tTOSSignalID)27UL)
#define cTOSSignalRising_DOOR_UNLOCK_LOCK_SW_LAP_DLK ((tTOSSignalID)28UL)
#define cTOSSignalRising_RF_UNLOCK_DRIVER_DOOR_LAP_DLK ((tTOSSignalID)29UL)
#define cTOSSignalEventIntKwpWakeUp      ((tTOSSignalID)30UL)
#define cTOSSignalDiagnosticMessageIsReceived ((tTOSSignalID)31UL)
#define cTOSSignalCrashIsDetectedByAirbag ((tTOSSignalID)32UL)
#define cTOSSignalCrashUnlockStarted     ((tTOSSignalID)33UL)
#define cTOSSignalLAPFliCrashUnlockFinished ((tTOSSignalID)34UL)
#define cTOSSignalLAPFliEventRfLockAll   ((tTOSSignalID)35UL)
#define cTOSSignalLAPFliEventRfUnlockAll ((tTOSSignalID)36UL)
#define cTOSSignalActiveSleepRequested   ((tTOSSignalID)37UL)
#define cTOSSignalWakeUpRequested        ((tTOSSignalID)38UL)
#define cTOSSignalSomebodyMaintainStartingStepState ((tTOSSignalID)39UL)
#define cTOSSignalSomebodyMaintainActiveSleepState ((tTOSSignalID)40UL)
#define cTOSSignalSomebodyMaintainActiveState ((tTOSSignalID)41UL)

/*---------------------------------------------------------------------------
     Definition of Controls's IDs
  ---------------------------------------------------------------------------*/
// Number of controls
#define cTOSMaxControlNumber 56UL

// IDs
#define cTOSControlTOSInitialize        ((tTOSControlId)0UL) // Control TOSInitialize
#define cTOSControlActiveSleepRequest   ((tTOSControlId)1UL) // Control ActiveSleepRequest
#define cTOSControlWakeUpRequest        ((tTOSControlId)2UL) // Control WakeUpRequest
#define cTOSControlChanging_RR_DOORS_SW ((tTOSControlId)3UL) // Control Changing_RR_DOORS_SW
#define cTOSControlChanging_FR_DOORS_SW ((tTOSControlId)4UL) // Control Changing_FR_DOORS_SW
#define cTOSControlFalling_HAZARD_SW    ((tTOSControlId)5UL) // Control Falling_HAZARD_SW
#define cTOSControlFalling_PWR_IGN      ((tTOSControlId)6UL) // Control Falling_PWR_IGN
#define cTOSControlRising_PWR_IGN       ((tTOSControlId)7UL) // Control Rising_PWR_IGN
#define cTOSControlFrontStopPositionDetected ((tTOSControlId)8UL) // Control FrontStopPositionDetected
#define cTOSControlRearStopPositionDetected ((tTOSControlId)9UL) // Control RearStopPositionDetected
#define cTOSControlRising_DOOR_LOCK_SW  ((tTOSControlId)10UL) // Control Rising_DOOR_LOCK_SW
#define cTOSControlRising_DOOR_UNLOCK_SW ((tTOSControlId)11UL) // Control Rising_DOOR_UNLOCK_SW
#define cTOSControlFalling_FR_DOORS_SW  ((tTOSControlId)12UL) // Control Falling_FR_DOORS_SW
#define cTOSControlRising_FR_DOORS_SW   ((tTOSControlId)13UL) // Control Rising_FR_DOORS_SW
#define cTOSControlFalling_RR_DOORS_SW  ((tTOSControlId)14UL) // Control Falling_RR_DOORS_SW
#define cTOSControlRising_RR_DOORS_SW   ((tTOSControlId)15UL) // Control Rising_RR_DOORS_SW
#define cTOSControlInputsReadAfterStartingStepState ((tTOSControlId)16UL) // Control InputsReadAfterStartingStepState
#define cTOSControlProtectionLedVerlogSleepMode ((tTOSControlId)17UL) // Control ProtectionLedVerlogSleepMode
#define cTOSControlAirbagUnlock         ((tTOSControlId)18UL) // Control AirbagUnlock
#define cTOSControlStartLearningInFactoryMode ((tTOSControlId)19UL) // Control StartLearningInFactoryMode
#define cTOSControlExitFromLearningInFactoryMode ((tTOSControlId)20UL) // Control ExitFromLearningInFactoryMode
#define cTOSControlStartLearningInAfterSaleMode ((tTOSControlId)21UL) // Control StartLearningInAfterSaleMode
#define cTOSControlValidateLearningInAfterSaleMode ((tTOSControlId)22UL) // Control ValidateLearningInAfterSaleMode
#define cTOSControlGiveUpLearningInAfterSaleMode ((tTOSControlId)23UL) // Control GiveUpLearningInAfterSaleMode
#define cTOSControlStartPermanentAuthentication ((tTOSControlId)24UL) // Control StartPermanentAuthentication
#define cTOSControlStopPermanentAuthentication ((tTOSControlId)25UL) // Control StopPermanentAuthentication
#define cTOSControlStartTestVirginKey   ((tTOSControlId)26UL) // Control StartTestVirginKey
#define cTOSControlAlaDiagEnable        ((tTOSControlId)27UL) // Control AlaDiagEnable
#define cTOSControlAlaDiagDisable       ((tTOSControlId)28UL) // Control AlaDiagDisable
#define cTOSControlRightFlashingForTFC  ((tTOSControlId)29UL) // Control RightFlashingForTFC
#define cTOSControlLeftFlashingForTFC   ((tTOSControlId)30UL) // Control LeftFlashingForTFC
#define cTOSControlActivateFinalTest    ((tTOSControlId)31UL) // Control ActivateFinalTest
#define cTOSControlClearFaultFlagsAndCounters ((tTOSControlId)32UL) // Control ClearFaultFlagsAndCounters
#define cTOSControlRKE_LOCK_REQUEST     ((tTOSControlId)33UL) // Control RKE_LOCK_REQUEST
#define cTOSControlRKE_UNLOCK_REQUEST   ((tTOSControlId)34UL) // Control RKE_UNLOCK_REQUEST
#define cTOSControlRfLockAllForAlarm    ((tTOSControlId)35UL) // Control RfLockAllForAlarm
#define cTOSControlRfUnlockAllForAlarm  ((tTOSControlId)36UL) // Control RfUnlockAllForAlarm
#define cTOSControlAutoRelock           ((tTOSControlId)37UL) // Control AutoRelock
#define cTOSControlCrashUnlockFinished  ((tTOSControlId)38UL) // Control CrashUnlockFinished
#define cTOSControlGetAprTrpResource    ((tTOSControlId)39UL) // Control GetAprTrpResource
#define cTOSControlReleaseAprTrpResource ((tTOSControlId)40UL) // Control ReleaseAprTrpResource
#define cTOSControlGetCarTrpResource    ((tTOSControlId)41UL) // Control GetCarTrpResource
#define cTOSControlKeyIsAuthenticated   ((tTOSControlId)42UL) // Control KeyIsAuthenticated
#define cTOSControlKeyIsNotAuthenticated ((tTOSControlId)43UL) // Control KeyIsNotAuthenticated
#define cTOSControlReleaseCarTrpResource ((tTOSControlId)44UL) // Control ReleaseCarTrpResource
#define cTOSControlDATInitialize        ((tTOSControlId)45UL) // Control DATInitialize
#define cTOSControlLAPInitialize        ((tTOSControlId)46UL) // Control LAPInitialize
#define cTOSControlEnterStartingStepState ((tTOSControlId)47UL) // Control EnterStartingStepState
#define cTOSControlLeaveStartingStepState ((tTOSControlId)48UL) // Control LeaveStartingStepState
#define cTOSControlDATEnterActiveState  ((tTOSControlId)49UL) // Control DATEnterActiveState
#define cTOSControlLAPEnterActiveState  ((tTOSControlId)50UL) // Control LAPEnterActiveState
#define cTOSControlLAPLeaveActiveState  ((tTOSControlId)51UL) // Control LAPLeaveActiveState
#define cTOSControlDATLeaveActiveState  ((tTOSControlId)52UL) // Control DATLeaveActiveState
#define cTOSControlIsAnybodyMaintainStartingStepState ((tTOSControlId)53UL) // Control IsAnybodyMaintainStartingStepState
#define cTOSControlIsAnybodyMaintainActiveSleepState ((tTOSControlId)54UL) // Control IsAnybodyMaintainActiveSleepState
#define cTOSControlIsAnybodyMaintainActiveState ((tTOSControlId)55UL) // Control IsAnybodyMaintainActiveState

