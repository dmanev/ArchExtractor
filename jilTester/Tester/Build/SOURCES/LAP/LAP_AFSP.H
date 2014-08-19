#ifndef _QAC_
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
// Component:    LAP_AFSP.H
// -----------------------------------------------------------------------------
// $Date:   Mar 04 2010 16:09:04  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_ASF/LAP_AFSP.H-arc  $
// $Revision:   1.17  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_ASF/LAP_AFSP.H-arc  $
// 
//    Rev 1.17   Mar 04 2010 16:09:04   adzhelp
// Cm006814: QAC corrections
// 
//    Rev 1.16   Mar 02 2010 10:46:00   adzhelp
// Cm006814: TPS_COM_MOTEUR normalized
// 
//    Rev 1.15   Feb 15 2010 16:08:30   adzhelp
// Cm006878: VERLOG_ALGO is byte number #3, bit 0
// 
//    Rev 1.14   Jan 29 2010 15:23:46   amanevd
// Cm006878: In function LAPAfsTreatWriteDataByLocalIdentifierService
// 8-th byte is included as 'nothing to do case'
// 
//    Rev 1.13   Nov 23 2009 17:24:30   akodzhh
// Cm006728: LAP_AFS: Update for QAC warnings removal and justification.
// 
//    Rev 1.12   Oct 27 2009 15:32:04   adzhelp
// Cm006382: Service SecurityAccess implemented
// 
//    Rev 1.11   Oct 05 2009 13:20:20   akodzhh
// Cm006299: DIAG : Start Permanent Authentication - set status 00h when successful.
// 
//    Rev 1.10   Sep 24 2009 17:53:28   akodzhh
// Cm005225: IO control of HORN_RL output is inhibited while cycle alarm is activated.
// 
//    Rev 1.9   Sep 23 2009 12:20:58   adzhelp
// Cm003277: Implementation of read log zone request (ID F0...FF)
// 
//    Rev 1.8   Sep 21 2009 11:04:46   akodzhh
// Cm005207: Add SDO, KEY_BUTTON config params (21 D0, 3B D0).
// 
//    Rev 1.7   Aug 07 2009 18:09:48   amanevd
// Cm005142: Implementation of Confidential Diagnostic
// 
//    Rev 1.6   Jul 24 2009 11:40:18   ailievb
// Cm005122: DLK: Time out TPS_REF not taken into account correctly at decrease of doorlock motor actions counter. 
// 
//    Rev 1.5   17 Jul 2009 11:31:04   akodzhh
// Cm005756: IOBLID timeout adjusted, code review 1.5 issues fixed.
// 
//    Rev 1.4   16 Apr 2009 17:33:18   akodzhh
// Cm003128: Analogic values CLR #78. OPEN_DOOR_LED/Alarm output shared - ensure diag control. 
// Due to Eeprom mapping changes. Erase AFS code treatment.
// 
//    Rev 1.3   Mar 30 2009 16:51:24   akodzhh
// Cm003128: Write Calibr Params($3B$D1)- removed range checks for the values written; TPS_COM_MOTEUR step fixed; Read DI_ENGINE_RPM (replace ENGINE_RPM).
// 
//    Rev 1.2   20 Mar 2009 18:07:56   akodzhh
// Cm003128 - fixes for some data names and $3B$D1 frame
// 
//    Rev 1.1   Mar 13 2009 18:49:04   akodzhh
// Cm003128 - Implementation of the Diagnostic functionality - LAP_AFS - VIN_Lgth fix.
// 
//    Rev 1.0   Feb 18 2009 14:49:26   akodzhh
// Initial revision.
//******************************************************************************
#endif

#ifndef I_LAP_AFSP_H
#define I_LAP_AFSP_H (1)

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Constant data
//------------------------------------------------------------------------------
/////////////////////////////////////////////////////
// constants for ReadDataByLocalIdentifier (RDBLID)
/////////////////////////////////////////////////////
#define cRDBLIDReq_Lgth                         ((U8)2)

#define cRDBLIDAns_APVCode_Lgth                 ((U8)9)
#define cRDBLIDAns_BCMIdentification_Lgth       ((U8)26)
#define cRDBLIDAns_VIN_Lgth                     ((U8)21)
#define cRDBLIDAns_DefaultData_Lgth             ((U8)19)
#define cRDBLIDAns_GeneralParam_Lgth            ((U8)6)
#define cRDBLIDAns_FactoryConfig_Lgth           ((U8)58)
#define cRDBLIDAns_ImmoData_Lgth                ((U8)26)
#define cRDBLIDAns_InputAndVehicleStateLgth     ((U8)8)
#define cRDBLIDAns_OutputStateLgth              ((U8)8)
#define cRDBLIDAns_CodedValueLgth               ((U8)22)
#define cRDBLIDAns_ECU_LOG_Lgth                 cRDBLIDAns_BCMIdentification_Lgth


// List of LID support with ReadDataByLocalIdentifier service (Spécifique Appli)
#define cRDBLID_APVCodeID                       ((U8)0xA2)
#define cRDBLID_BCMIdentificationID             ((U8)0x80)
#define cRDBLID_VINID                           ((U8)0x81)
#define cRDBLID_DefaultDataID                   ((U8)0x94)
#define cRDBLID_GeneralParamID                  ((U8)0xD0)
#define cRDBLID_FactoryConfigID                 ((U8)0xD1)
#define cRDBLID_ImmoDataID                      ((U8)0xDB)
#define cRDBLID_InputAndVehicleStateID          ((U8)0xDC)
#define cRDBLID_OutputStateID                   ((U8)0xDD)  
#define cRDBLID_CodedValueID                    ((U8)0xDE)
#define cRDBLID_ECU_LOG00_ID                    ((U8)0xF0)

///////////////////////////////////////////////////////////////
// constants for WriteDataByLocalIdentifier (RDBLID)
///////////////////////////////////////////////////////////////
#define cWDBLIDReq_VIN_Lgth                           ((U8)21)
#define cWDBLIDReq_GeneralParamBitToBit_Lgth          ((U8)5)
#define cWDBLIDReq_FactoryConfig_Lgth                 ((U8)4)

// List of LID support with ReadDataByLocalIdentifier service (Spécifique Appli)
#define cWDBLID_VINID                           ((U8)0x81)
#define cWDBLID_FactoryConfigID                 ((U8)0xD1)  
#define cWDBLID_GeneralParamBitToBitID          ((U8)0xD0)


// GeneralParam data
#define cNbGeneralParameters   (U8)32

#define cIndexDEM_SURVIT       (U8)0 
#define cIndexCALALPRI         (U8)1 
#define cIndexCALVERDI         (U8)2 
#define cIndexAUTDEGIVRAGE     (U8)3 
#define cIndexRELAIS_DEM       (U8)4 
#define cIndexRESERVED_1       (U8)5 
#define cIndexRESERVED_2       (U8)6 
#define cIndexDETCHOC          (U8)7 
#define cIndexRESERVED_3       (U8)8 
#define cIndexCONDATMPO        (U8)9 
#define cIndexRESERVED_4       (U8)10
#define cIndexCONDAROU         (U8)11
#define cIndexCARCLIENT        (U8)12
#define cIndexRESERVED_5       (U8)13
#define cIndexALIM_PLAF        (U8)14
#define cIndexPIL_PLAF         (U8)15
#define cIndexVERLOG_ALGO      (U8)16
#define cIndexSDO              (U8)17
#define cIndexCPE_IMPULS       (U8)18
#define cIndexFEU_BROUILLARD   (U8)19
#define cIndexEV_ARR           (U8)20
#define cIndexINFO_REGIME      (U8)21
#define cIndexCLI_REM          (U8)22
#define cIndexCAD_BAGUE_AV     (U8)23
#define cIndexAUTCRASH         (U8)24
#define cIndexAUTVERLOG        (U8)25
#define cIndexAUTPLAF          (U8)26
#define cIndexKEY_BUTTON       (U8)27
#define cIndexCALALARM         (U8)28
#define cIndexCALULKTR         (U8)29
#define cIndexAUTRECRF         (U8)30
#define cIndexOUBLICEINTURE    (U8)31


// FactoryConfig data(Read/Write): Byte Number
#define cFactoryConfigBytesNb       31

#define cNbTPS_RETARD_DETRESSE          (U8)1   // Control delay of the hazard warning lights after an impact
#define cNbTIMER_DETRESSE               (U8)4   // Max activation time of the hazard warning lights
#define cNbTPS_APC                      (U8)5   // APC absence time-delay before opening roof light relay
#define cNbTPS_PLAF                     (U8)6   // Roof light control time (time-delay)
#define cNbTPS_ESSUIE_MINI              (U8)9   // Minimum FR wiping time
#define cNbTPS_MAX_COUPLBLOC            (U8)10  // Max FR blocked torque control time
#define cNbTPS_ARRET                    (U8)11  // Stoppage time after FR blocking
#define cNbTPS_REPRISE                  (U8)12  // Time for control retry after blocking
#define cNbTPS_FILT_AF                  (U8)13  // Time to take account of FR fixed stop
#define cNbTPS_POSIT_BALAIS             (U8)14  // Offset time after FR fixed stop detection
#define cNbPROLONG_APPUI_COURT          (U8)19  // Number of wiper strokes after a short wash
#define cNbPROLONG_APPUI_LONG           (U8)20  // Number of wiper strokes after a long wash
#define cNbTPS_APPUILAV                 (U8)21  // Washer pressing time
#define cNbTPS_POSIT_BALAIS_AR          (U8)36  // Offset time after RR fixed stop detection
#define cNbPROLONG_APPUI_ARR            (U8)37  // Number of wiper strokes after a rear wash extension
#define cNbSEUIL_VIT_CONDAROU           (U8)39  // Speed required for locking when driving
#define cNbTPS_COM_MOTEUR               (U8)40  // Max torque control time
#define cNbNBCOM_MAX                    (U8)41  // Number of max engine locking controls
#define cNbTPS_REF                      (U8)42  // Reference time for number of max engine locking controls
#define cNbTIMER_RECONDA_AUTO           (U8)43  // Timer for anti-intruder device
#define cNbN_MISE_APC                   (U8)44  // Number of times APC is switched on before APV code is deleted
#define cNbTMPMERA                      (U8)45  // Time-delay before vehicle protection is activated
#define cNbTPS_OUVPORTE                 (U8)46  // Recognition time for double press (key with two buttons)
#define cNbTPS_TEMPO_DEG                (U8)47  // Deicing time-delay
#define cNbTPS_IMPUL_MINI               (U8)48  // Min time to take account of deicing control
#define cNbSBR_ACTIVE_SPEED_THRESH_TP   (U8)50  // Buzzer triggering speed if seat belt warning
#define cNbSBR_TIMEOUT_TM_TP            (U8)51  // Buzzer activation time if seat belt warning
#define cNbMAX_NB_ALERT_SEQUENCES_TP    (U8)52  // Maximum buzzer activation number if seat belt warning
#define cNbTPS_BUZ_CLI                  (U8)54  // Indicator/hazard warning sound signal time length
#define cNbTPS_CLI                      (U8)55  // Indicator signal period
#define cNbTPS_CLIDEGRAD                (U8)56  // Indicator signal period in degraded mode


///////////////////////////////////////////////////////////////
// constants for InputOutputControlByLocalIdentifier (IOCBLID)
///////////////////////////////////////////////////////////////
#define cIOCBLIDNormalOutputTimeOut        (mTOSConvMsInTimerTick(3000UL))
#define cStepInMsTPS_COM_MOTEUR            10   // DLK

#define cIOCBLIDCpeTimeOut  \
            /* Max of TPS_COM_MOTEUR * step fits in U16 */\
            mTOSConvMsInTimerTick((U32)((U16)mDATRead(U8Bit,NEEP_TPS_COM_MOTEUR,Default) * (U16)cStepInMsTPS_COM_MOTEUR))
// increase accuracy for the timeouts measured through graph group default  
#define cIOCBLIDCpeTimeOutInTick    \
           ((cIOCBLIDCpeTimeOut > (tTOSTimer)0) ? (cIOCBLIDCpeTimeOut - (tTOSTimer)1U) : (tTOSTimer)0U)

#define cIOCBLIDReq_Lgth                        ((U8)4)
#define cIOCBLIDAns_Lgth                        ((U8)3)

#define cIOCBLID_StartRoutineID                 ((U8)0x00)
#define cIOCBLID_ReadStatusID                   ((U8)0x01)

#define cIOCBLID_DeactivationParam              ((U8)0x00)
#define cIOCBLID_TemporaryActivationParam       ((U8)0x01)
#define cIOCBLID_PermanentActivationParam       ((U8)0xFF)

#define cIOCBLID_RoutineInProgressID            ((U8)0x01)
#define cIOCBLID_RoutineIsFinishedID            ((U8)0x02)

///////////////////////////////////////////////////////////////
// Output control Num
///////////////////////////////////////////////////////////////
#define cNoOutputControl                 (U8)0xFF

#define cNbTorToControl                  (U8)13
#define cOutputLockDoors                 (U8)0x80
#define cOutputUnlockDoors               (U8)0x81
#define cOutputUnlockDrDoor              (U8)0x82
#define cOutputDiRight                   (U8)0x83
#define cOutputDiLeft                    (U8)0x84
#define cOutputFrWiper                   (U8)0x87
#define cOutputRrWiper                   (U8)0x89
#define cOutputBatLightTempo             (U8)0x8A
#define cOutputDoorlockLed               (U8)0x8B
#define cOutputVerlogLed                 (U8)0x8C
#define cOutputDefrosterRl               (U8)0x8E
#define cOutputHornRl                    (U8)0x93
#define cOutputRrFogLamp                 (U8)0x9E

// Serial Line
#define cNbSerialLineToControl           (U8)2
#define cOutputDataImmobilzer            (U8)0x8F
#define cOutputVerlog                    (U8)0x90

// PWM
#define cNbPwmToControl                  (U8)2                         
#define cOutputPwmRoomLamp               (U8)0x85
#define cOutputBuzzer                    (U8)0x9D

#define cNbOutputToControl      (U8)(cNbTorToControl + cNbSerialLineToControl + cNbPwmToControl)
#define cDoorlockLedIndex       (U8)8
#define cHornRlIndex            (U8)11


///////////////////////////////////////////////////////////////
// constants for LearningModeControl (LMC)
///////////////////////////////////////////////////////////////
#define cLMCReq_Factory_Lgth                         ((U8)2)
#define cLMCReq_EnterInAFSLearningMode_Lgth          ((U8)8)
#define cLMCReq_LeaveInAFSLearningMode_Lgth          ((U8)3)
#define cLMCAns_Lgth                                 ((U8)2)

#define cLMC_EnterInFactoryLearningModeID         ((U8)0x02)
#define cLMC_LeaveInFactoryLearningModeID         ((U8)0x82)
#define cLMC_EnterInAFSLearningModeID             ((U8)0x01)
#define cLMC_LeaveInAFSLearningModeID             ((U8)0x81)

#define cLMCL_AFSLearningCancel                   ((U8)0x00)
#define cLMCL_AFSLearningValidation               ((U8)0x01)

///////////////////////////////////////////////////////////////
// constants for StartRoutineByLocalIdentifier (SRBID)
//              and StopRoutineByLocalIdentifier (SPRBID)
///////////////////////////////////////////////////////////////
#define cSRBID_StartPermanentAuthenticationID       ((U8)0xA6)
#define cSRBID_EraseAfterSalesCodeID                ((U8)0xA7)
#define cSRBID_TestVirginKeyID                      ((U8)0xB0)
#define cNoRoutineControl                           ((U8)0x00)

#define cSRBIDReq_Lght                              ((U8)0x03)

#define cSRBID_StartRoutineAccepted   ((U8)0x00)
///////////////////////////////////////////////////////////////
// constants for ClearDiagnosticInformation (CLRDI)
///////////////////////////////////////////////////////////////
#define cCLRDIReq_Lght                              ((U8)0x03)

///////////////////////////////////////////////////////////////
// constants for SecurityAccess (SA)
///////////////////////////////////////////////////////////////
#define cSAReq_Lngth                                ((U8)2U)
#define cLIdReqSecurityAccess1                      ((U8)0x81U)

///////////////////////////////////////////////////////////////
// general constants
///////////////////////////////////////////////////////////////
#define c8BitsShift 8


//------------------------------------------------------------------------------
// Exported type
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Constant exported data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported Macros
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported functions
//------------------------------------------------------------------------------

//QACJ 0882:akodzhh: deftypes.h is forceincluded to resolve definitions in header files
#endif   // I_LAP_AFSP_H
