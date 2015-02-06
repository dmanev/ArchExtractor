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
// Component:    LAP_TFC
// -----------------------------------------------------------------------------
// $Date:   Jun 18 2010 08:42:12  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_TFC/LAP_TFC.C-arc  $
// $Revision:   1.33  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_TFC/LAP_TFC.C-arc  $
// 
//    Rev 1.33   Jun 18 2010 08:42:12   adzhelp
// Cm009329: Frequency for buzzer I/O Control changed from 4khz to 2.4khz
// 
//    Rev 1.32   Mar 24 2010 17:44:20   adzhelp
// Cm007987: NRC when there is no bootloader
// 
//    Rev 1.31   Mar 24 2010 15:08:02   adzhelp
// Cm007987: $21$91 is partly filled from lastest application logzone.
// 
//    Rev 1.30   Mar 12 2010 13:54:18   adzhelp
// Cm007695: Code review corrections
// 
//    Rev 1.29   Mar 08 2010 14:52:26   adzhelp
// Cm007695: Request for Clearing System+Counter faults
// 
//    Rev 1.28   Mar 01 2010 12:28:06   adzhelp
// Cm006824: Response to 21 91 shortened by 2, request '3B 96 ...' shortened by 2
// 
//    Rev 1.27   Feb 19 2010 10:08:42   adzhelp
// Cm007575: Notify DAT layer for sleep request
// 
//    Rev 1.26   Feb 04 2010 14:25:32   adzhelp
// Cm007297: Implementation of SRBLID 'F0' for EEPROM reprogramming
// 
//    Rev 1.25   Jan 28 2010 12:02:22   adzhelp
// Cm007261: MANU: Request $21$91 should read ECU Reference from Log Zone
// 
//    Rev 1.24   Dec 04 2009 16:57:34   adzhelp
// Cm006719: Change number of RC blocks received to ones with correct CRC
// 
//    Rev 1.23   Nov 23 2009 10:26:38   akodzhh
// Cm005566: AutoTest - set errors on outputs.
// 
//    Rev 1.22   Nov 20 2009 09:52:44   akodzhh
// Cm006705: QAC - warnings resolved and justified.
// 
//    Rev 1.21   Nov 19 2009 12:51:56   akodzhh
// Cm006705: AutoTest: fix check for matrix validity.
// 
//    Rev 1.20   Oct 06 2009 16:27:46   akodzhh
// Cm006406:  EEP_FlaCoeffLTrailer, EEP_FlaCoeffRTrailer fix.
// 
//    Rev 1.19   Oct 06 2009 15:48:22   akodzhh
// Cm006406: EEP_RenaultPartNumber, EEP_BCMHWLevel replaced; EEP_FlaCoeffLTrailer_trailer, EEP_FlaCoeffRTrailer removed.
// 
//    Rev 1.18   Oct 05 2009 16:38:04   akodzhh
// Cm005803: Update SL test ECM - start conditions.
// 
//    Rev 1.17   Oct 01 2009 11:38:26   akodzhh
// Cm006291: RF test updated - status request treatment SPEC: Cm006290.
// 
//    Rev 1.16   Sep 30 2009 13:43:56   akodzhh
// Cm005803: Update SL test for Immobilizer start conditions and ECM - start and status request.
// 
//    Rev 1.15   Sep 23 2009 11:49:08   akodzhh
// Cm006229: SRBID Eeprom Test - Checksum List updated according to Eep Version 02.00.
// 
//    Rev 1.14   Sep 23 2009 10:04:34   adzhelp
// Cm005554: ROM Checksum location updated
// 
//    Rev 1.13   Sep 21 2009 16:06:14   akodzhh
// Cm005756: TFC AutoTest timeouts adjusted.
// 
//    Rev 1.12   Aug 05 2009 14:29:10   akodzhh
// Cm005796: Added '#3 Option byte' for RDBLI_AnalogValues request&response frames.
// 
//    Rev 1.11   Aug 05 2009 10:55:18   akodzhh
// Cm005793: Response length for 'RF_Test Start' is set to be 4 bytes.
// 
//    Rev 1.10   Aug 04 2009 15:01:54   akodzhh
// Cm005802: Treatment of $3B $90 corrected for 'BCM Hardware Level'.
// 
//    Rev 1.9   Aug 04 2009 13:42:56   akodzhh
// Cm005751: Delay reset, when session is closed due to StopComm request. CR issues fixed.
// 
//    Rev 1.8   Apr 29 2009 14:24:58   adzhelp
// Cm003517: MEM_TYPE attribute added to service and static functions
// 
//    Rev 1.7   Apr 17 2009 19:12:20   akodzhh
// Cm003517: Use a reset after the sleep request treatment.
// 
//    Rev 1.6   Apr 17 2009 15:46:20   akodzhh
// Cm003517: TOSIsTimerElapsed() call corrected. AutoTest synchronization timeout - treat as timeout, not a delay.
// 
//    Rev 1.5   15 Apr 2009 19:26:20   akodzhh
// Cm003517: StopAutoTest response - status corrected (OK\NOK inversion). Flasher test request wrong byte read.
// 
//    Rev 1.4   15 Apr 2009 12:03:22   akodzhh
// Cm003517: Added SerialLine Immo and Eeprom Test. Constants for Flasher Test renamed. Checks for BCD formad removed from $38$90 frame. Analog values - read converted data 5s. OPEN_DOOR_LED/Alarm output - ensure diag control.
// 
//    Rev 1.3   31 Mar 2009 11:41:50   akodzhh
// Cm003517:  on init TFC session set diag mask (notify DAT_PWM) for PWM_ROOMLAMP output direct control.
// 
//    Rev 1.2   30 Mar 2009 13:51:34   akodzhh
// Cm003517: Read DI_ENGINE_RPM (replace ENGINE_RPM)
// 
//    Rev 1.1   20 Mar 2009 18:18:32   akodzhh
// Cm003517 - fixes for warnings and some data names, Checksum calculation, sleep timeout measurement - use graph instead of task.
// 
//    Rev 1.0   Mar 17 2009 16:53:32   akodzhh
// Initial revision.
//******************************************************************************
#endif


//------------------------------------------------------------------------------
// Body Identification
//------------------------------------------------------------------------------

#define lap_tfc  "lap_tfc"

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------
#include "lib.h"
#include "dat.h"
#include "tos.h"
#include "lap_kwp.h"
#include "lap_kwpp.h"
#include "lap_tfc.h"
#include "lap_tfc.hgr"

#ifdef BOOTLOADER_IS_SUPPORTED
    #include "LIB_BOO.h"
#endif

//------------------------------------------------------------------------------
// Local constants
//------------------------------------------------------------------------------

/////////////////////////////////////////////////////
// constants for ReadDataByLocalIdentifier (RDBLID)
/////////////////////////////////////////////////////
#define cRDBLIDReq_Lgth                         ((U8)2)
#define cRDBLIDReq_AnalogValueLgth              ((U8)3)

#define cRDBLID_SoftwareAndTFCVersionID         ((U8)0x90)
#define cRDBLIDAns_SoftwareAndTFCVersion_Lgth   ((U8)10)

#define cRDBLID_TFCDataID                       ((U8)0x91)
#define cRDBLIDAns_TFCData_Lgth                 ((U8)28)

#define cRDBLID_AnalogValueID                   ((U8)0x92)
#define cRDBLIDAns_AnalogValue_Lgth             ((U8)17)

#define cRDBLID_DigitalInputsID                 ((U8)0x93)
#define cRDBLIDAns_DigitalInputs_Lgth           ((U8)6)

///////////////////////////////////////////////////////////////
// constants for WriteDataByLocalIdentifier (WDBLID)
///////////////////////////////////////////////////////////////
#define cWDBLIDReq_KilisRatio_Lgth              ((U8)4)
#define cWDBLID_KilisRatioID                    ((U8)0x94)

#define cWDBLIDReq_JCAEData_Lgth                ((U8)20)
#define cWDBLID_JCAEDataID                      ((U8)0x90)

#define cWDBLIDReq_TestCounter_Lgth             ((U8)3)
#define cWDBLIDReq_FlashersCoeff_Lgth           ((U8)4)

#define cWDBLID_InSituTestCounterID            ((U8)0x91)
#define cWDBLID_FunctTestCounterID             ((U8)0x92)
#define cWDBLID_RunningTestCounterID           ((U8)0x93)
#define cWDBLID_RfTestCounterID                ((U8)0x94)
#define cWDBLID_FinalTestCounterID             ((U8)0x95)
#define cWDBLID_FlashersCoeffID                ((U8)0x96)

///////////////////////////////////////////////////////////////
// constants for InputOutputControlByLocalIdentifier (IOCBLID)
///////////////////////////////////////////////////////////////
#define cIOCBLIDReq_Lgth                        ((U8)5)
#define cIOCBLIDAns_Lgth                        ((U8)3)

#define cIOCBLID_StartPermanentCtrl             ((U8)0x20)


#define cIOCBLID_ManualOutputMode               ((U8)0xFA)

///////////////////////////////////////////////////////////////
// constants for StartRoutineByLocalIdentifier (SRBID)
//              and StopRoutineByLocalIdentifier (SPRBID)
///////////////////////////////////////////////////////////////
#define cSRBID_SequentielOutputModeReq_Lgth     ((U8)4)


#define cSRBID_FlasherTestReq_Lgth          ((U8)3)
#define cSRBID_RFTestReq_Lgth               ((U8)3)
#define cSRBID_AutoTestTORReqStatic_Lgth    ((U8)9)
#define cSRBID_SerialLineTestReq_Lgth       ((U8)4)
#define cSRBID_SleepingModeReq_Lgth         ((U8)3)
#define cSRBID_EepromTestReq_Lgth           ((U8)3)
#define cSRBLID_StatusReq_Lgth              ((U8)3)

#define cSRBLID_AutoTestTOR_RepLgth         ((U8)9)
#define cSRBLID_StaticRepLgth               ((U8)3)
#define cSRBLID_RFTestRepLgth               ((U8)4)
#define cSRBID_ClearFaultsAndCountersLgth   ((U8)3)

#define cSRBID_EepromReprogramming              ((U8)0xF0)
#define cSRBID_ClearFaultsAndCounters           ((U8)0xF1)
#define cSRBID_FlasherTest                      ((U8)0xF9)
#define cSRBID_RFTest                           ((U8)0xFB)
#define cSRBID_AutoTestTOR                      ((U8)0xFC) 
#define cSRBID_SerialLineTest                   ((U8)0xFD)
#define cSRBID_SleepingMode                     ((U8)0xFE)
#define cSRBID_EepromTest                       ((U8)0xFF)
                                          
                                                 
#define cRoutineControlNumber                  ((U8)0x07)
#define cRoutineIndexFlasherTest               0
#define cRoutineIndexRFTest                    1
#define cRoutineIndexAutoTestTOR               2
#define cRoutineIndexSerialLineImmoTest        3
#define cRoutineIndexSerialLineVerlogTest      4
#define cRoutineIndexSleepingMode              5
#define cRoutineIndexEepromTest                6


// Routine status (TFC specific) 
#define cRoutineNotActivated      ((U8) 0x00)
#define cRoutineInProgress        ((U8) 0x10)
#define cRoutineTerminatedOK      ((U8) 0x20)
#define cRoutineTerminatedNOK     ((U8) 0x40)
                                                
#define cSRBID_StartRoutineID                   ((U8)0x00)
#define cSRBID_ReadStatusID                     ((U8)0x01)

///////////////////////////////////////////////////////////////
// constants for AutoTestTOR routine 
///////////////////////////////////////////////////////////////
#define cOutputsNumber                    (U8)16
#define cInputsNumber                     (U8)24
#define cPouOutputsNumber                 (U8)cDATPouNumberOfDataDouGeneratorMessage 

#define cOPEN_DOOR_LEDOutputPos           ((U8)10)
#define cTxVerlogOutputPos                ((U8)12)
#define cTxImmobilzerOutputPos            ((U8)13)
#define cPwmRoomLampOutputPos             ((U8)14)
#define cBuzzerOutputPos                  ((U8)15)
#define cDiagBuzzFrequency           (U16)2400U     // 2.4kHZ

#define cInvalidCurrentOutput             ((U8)0xFF)
#define cInvalidSequentialOutput          ((U16)0xFFFF)

#define cModeStopOnError                  (U8)0x00
#define cModeContinueOnError              (U8)0x01
#define cModeStopOnErrorTx                (U8)0x02
#define cModeContinueOnErrorTx            (U8)0x03

#define cSequenceModeBytePos                2  
#define cStartDelayIn10msBytePos            3   // *10ms    
#define cSetupTimeBytePos                   4   // *1ms     
#define cActivationTimeOutBytePos           5   // *1ms     
#define cFilterTimeConstantBytePos          6   // reserved for future use
#define cSynchronizationTimeOutBytePos      7   // *10ms 
#define cOrderingMatrixSizeBytePos          8       
#define cOrderingMatrixBytePos              9

#define cOrderingMatrixMaxSize             48 
#define cMaxQuarterOutput               (U8)3
#define cMaxQuarterInput                (U8)5
#define cQuarter0                       (U8)0
#define cQuarter1                       (U8)1
#define cQuarter2                       (U8)2
#define cQuarter3                       (U8)3
#define cQuarter4                       (U8)4
#define cQuarter5                       (U8)5
#define cMatrixPairLng                     2  // one pair is containing one ouputs mask and one inputs mask
#define cQuarterMask                    (U8)0xF0U 


#define c10MsPerUnit                       10 
   

// Inputs
#define cIndexDI_ENGINE_RPM          0 
#define cIndexPWR_IGN                1 
#define cIndexRR_WASHER_SW           2 
#define cIndexFR_FOG_SW              3  // HIGH_LOW_BEAM
#define cIndexDI_DATA_IMMOBILIZER    4 
#define cIndexDI_VERLOG              5 
#define cIndexL_FLASHER_SW           6 
#define cIndexFR_DOORS_SW            7 
#define cIndexDOOR_LOCK_SW           8 
#define cIndexFR_WIPER_INT_SW        9 
#define cIndexRR_FOG_SW              10
#define cIndexFR_WASHER_SW           11
#define cIndexAIRBAG_CRASH           12
#define cIndexVEHICLE_SPEED          13
#define cIndexFR_AUTOSTOP_SW         14
#define cIndexRR_AUTOSTOP_SW         15
#define cIndexHAZARD_SW              16
#define cIndexR_FLASHER_SW           17
#define cIndexRR_WIPER_INT_SW        18
#define cIndexPOSITION_LIGHTS        19     // DI_CTC_DIMMERS
#define cIndexRR_DOORS_SW            20
#define cIndexDOOR_UNLOCK_SW         21
#define cIndexDEFROSTER_SW           22
#define cIndexSEATBELT_REMINDER_SW   23

#define cMaskDI_ENGINE_RPM          (U8)0x01
#define cMaskPWR_IGN                (U8)0x02
#define cMaskRR_WASHER_SW           (U8)0x04
#define cMaskFR_FOG_SW              (U8)0x08    // HIGH_LOW_BEAM
#define cMaskDI_DATA_IMMOBILIZER    (U8)0x11
#define cMaskDI_VERLOG              (U8)0x12
#define cMaskL_FLASHER_SW           (U8)0x14
#define cMaskFR_DOORS_SW            (U8)0x18
#define cMaskDOOR_LOCK_SW           (U8)0x21
#define cMaskFR_WIPER_INT_SW        (U8)0x22
#define cMaskRR_FOG_SW              (U8)0x24
#define cMaskFR_WASHER_SW           (U8)0x28
#define cMaskAIRBAG_CRASH           (U8)0x31
#define cMaskVEHICLE_SPEED          (U8)0x32
#define cMaskFR_AUTOSTOP_SW         (U8)0x34
#define cMaskRR_AUTOSTOP_SW         (U8)0x38
#define cMaskHAZARD_SW              (U8)0x41
#define cMaskR_FLASHER_SW           (U8)0x42
#define cMaskRR_WIPER_INT_SW        (U8)0x44
#define cMaskPOSITION_LIGHTS        (U8)0x48    // DI_CTC_DIMMERS    
#define cMaskRR_DOORS_SW            (U8)0x51
#define cMaskDOOR_UNLOCK_SW         (U8)0x52
#define cMaskDEFROSTER_SW           (U8)0x54
#define cMaskSEATBELT_REMINDER_SW   (U8)0x58

// common constants
#define c8Bits  8
#define c7Bits  7
#define c6Bits  6
#define c5Bits  5
#define c4Bits  4
#define c3Bits  3
#define c2Bits  2
#define c1Bits  1
#define c16Bits  16
#define cLSBMask       (U8)0xFFU
#define cu16LSBMask    0x00FF
#define cu16MSBMask    0xFF00

#define cByte0  0
#define cByte1  1
#define cByte2  2
#define cByte3  3
#define cByte4  4


// Pwm Output
#define cPwmRoomLampDiagRatio   (U8)100

// Eeprom data
#define cEEP_ECUReferenceLength     5
#define cEEP_PieNumberLength        5
#define cEEP_PieIndexLength         2
#define cEEP_SerialNumberLength     3
#define cEEP_DateCodeLength         2

#define cECUTypeByte    19
#define cECUTypeMax     (U8)0x07

///////////////////////////////////////////////////////////////
// constants for Checksum calculation
///////////////////////////////////////////////////////////////
#ifndef COMPILATION_NATIVE
//QACJ 3116: akodzhh: X90_BCM project specific checksum calculation
#pragma segment="CHECKSUM"
#define cRomChecksum        (*((U16*)__segment_begin("CHECKSUM")))
#else
#define cRomChecksum        0
#endif

#define cTimeoutBeforeEnterSleepInMs        100UL

///////////////////////////////////////////////////////////////
// constants for EepromTest - Eep Checksum read
///////////////////////////////////////////////////////////////
#define cNbEepBanks              (U8)(cNbDbk + cNbSbk)
#define cDbkOffset         cDATDbkFirstProcessHandle
// Bank Index in mDATEepDeclareBlocList
#define cIndexErrorGroup            cDATSbkHandleErrorGroup          
#define cIndexSupplierBank          cDATSbkHandleSupplierBank
#define cIndexVersionBank           cDATSbkHandleVersionBank 
#define cIndexVINBank               cDATSbkHandleVINBank
#define cIndexSpareBank             cDATSbkHandleSpareBank
#define cIndexDiagBank              (cDbkOffset+cDATDbkHandleDiagBank            )            
#define cIndexGeneralParameterBank  (cDbkOffset+cDATDbkHandleGeneralParameterBank)
#define cIndexFactoryConfigBank     (cDbkOffset+cDATDbkHandleFactoryConfigBank   )
#define cIndexStaticImmoBank        (cDbkOffset+cDATDbkHandleStaticImmoBank      )
#define cIndexDynamicImmoDataBank   (cDbkOffset+cDATDbkHandleDynamicImmoDataBank )     

#define cCksLgth        (U8)2

///////////////////////////////////////////////////////////////
// constants for SerialLineTest
///////////////////////////////////////////////////////////////
#define cSerialLineVerlog       (U8)0x01
#define cSerialLineImmobilizer  (U8)0x02

///////////////////////////////////////////////////////////////
// constants for RDBLID AnalogValue
///////////////////////////////////////////////////////////////
#define cReadingOptionDirect       (U8)0x00
#define cReadingOptionCorrection   (U8)0xFF

///////////////////////////////////////////////////////////////
// constants for RDBLID log zone / TFCData
///////////////////////////////////////////////////////////////
// Response indexes (= specification index - 1)
#define cInSituTestCounterIndex    (U8)21U
#define cDateCodeIndex             (U8)17U
#define cSerialNumberIndex         (U8)14U

#define cLastLogZoneId             (U8)0xFEU
#define cLogZoneSize               24U

// Log zone IDENT indexes
#define cLogZoneSparePartNumberIndex    0U
#define cLogZoneHwNumberIndex           9U
#define cLogZoneCalibrationNumberIndex  18U
#define cLogZoneEcuTypeIndex            20U  // first byte of 'other system features'
#define cLogZoneSerialNumberIndex       21U  // last 3 bytes of log zone
// Log zone REPROG indexes
#define cLogZoneDateIndex               16U

//------------------------------------------------------------------------------
// Local macros
//------------------------------------------------------------------------------
#define mInitTfcTabIdentifierServiceSupported()   \
{                                                 \
  cLAPKwpIdReadDataByLocalIdentifier,                \
  cLAPKwpIdWriteDataByLocalIdentifier,               \
  cLAPKwpIdInputOutputControlByLocalIdentifier,      \
  cLAPKwpIdStartRoutineByLocalIdentifier             \
}

#define mInitTfcTabServiceSupported()                 \
{                                                     \
  LAPTfcTreatReadDataByLocalIdentifierService,           \
  LAPTfcTreatWriteDataByLocalIdentifierService,          \
  LAPTfcTreatInputOutputControlByLocalIdentifierService, \
  LAPTfcTreatStartRoutineByLocalIdentifierService        \
}
//QACJ 3435: akodzhh: There is no side effect
//QACJ 3456: akodzhh: There is no side effect
#define mGetQuarterMask(Index)   (U8)( (U8)( (Index)>>2 ) | (U8)( 1 << (U8)((Index)&3 )))

#define mSetInputError(InputIndex)   (u32ErrorsOnInput |= (U32)((U32)1 << (InputIndex)))
#define mSetOutputError(OutputIndex)   (u16ErrorsOnOutput |= (U16)((U16)1 << (OutputIndex)))

//------------------------------------------------------------------------------
// Local types
//------------------------------------------------------------------------------
typedef struct EepBankCks
{
    U8  u8BankIndex;
    U8  u8BankCksMSB;
    U8  u8BankCksLSB;
}tEepBankCks;

//------------------------------------------------------------------------------
// Local data
//------------------------------------------------------------------------------
// TODO: update order of banks when eeprom mapping is changed 
static tEepBankCks BanksCksTable[cNbEepBanks]= 
{    
    {(U8)cIndexErrorGroup          ,0,0},
    {(U8)cIndexSupplierBank        ,0,0},
    {(U8)cIndexVersionBank         ,0,0},
    {(U8)cIndexVINBank             ,0,0},
    {(U8)cIndexSpareBank           ,0,0},
    {(U8)cIndexDiagBank            ,0,0},
    {(U8)cIndexGeneralParameterBank,0,0},
    {(U8)cIndexFactoryConfigBank   ,0,0},
    {(U8)cIndexStaticImmoBank      ,0,0},
    {(U8)cIndexDynamicImmoDataBank ,0,0}
};

static U8         RoutineRequestInProgress[cRoutineControlNumber];

static U16        u16ErrorsOnOutput;  // 16 Outputs
static U32        u32ErrorsOnInput;   // 24 Inputs 
static U8         u8SequenceMode;

static tTOSTimer  AutoTestTimer;
static tTOSTimer  AutoTestTimeOutValueInTick;
static tTOSTimer  SleepTimer;

static U8  u8EepTestCounter;

static U8  u8AutoTestSetupTimeOut;
static U8  u8AutoTestActivTimeOut;
static U8  u8AutoTestSynchroTimeOutIn10msUnit;
static U8  u8OrderingMatrixSize;
static U8  u8OrderingMatrix[cOrderingMatrixMaxSize];
static U8  u8OrderingMatrixCounter;

static BOOL bOutputsActivated;


//------------------------------------------------------------------------------
// Constant local data
//------------------------------------------------------------------------------
static const U16 u16OutputTab[cOutputsNumber] =
{
    ((U16)cDATPouDI_LEFTByteIndex              | (U16)((U16)cDATPouDI_LEFTBitIndex              << c8Bits)),    //    1    HS    DO_DRIVE_LEFT_FLASHER_CAR
    ((U16)cDATPouDI_RIGHTByteIndex             | (U16)((U16)cDATPouDI_RIGHTBitIndex             << c8Bits)),    //    2    HS    DO_DRIVE_RIGHT_FLASHER_CAR
    ((U16)cDATPouRR_WIPER_RR_FOG_LAMPByteIndex | (U16)((U16)cDATPouRR_WIPER_RR_FOG_LAMPBitIndex << c8Bits)),    //    3    HS    DO_DRIVE_REAR_WIPER_CAR
    ((U16)cDATPouLOCK_DOORSByteIndex           | (U16)((U16)cDATPouLOCK_DOORSBitIndex           << c8Bits)),    //    4    HS    DO_RELAY_DOORS-LOCK_CAR
    ((U16)cDATPouUNLOCK_DOORSByteIndex         | (U16)((U16)cDATPouUNLOCK_DOORSBitIndex         << c8Bits)),    //    5    HS    DO_RELAY_DOORS-UNLOCK_CAR
    ((U16)cDATPouUNLOCK_DRIVER_DOORByteIndex   | (U16)((U16)cDATPouUNLOCK_DRIVER_DOORBitIndex   << c8Bits)),    //    6    HS    DO_RELAY_DRV-DOOR-UNLOCK_CAR
    ((U16)cDATPouFRONT_WIPERByteIndex          | (U16)((U16)cDATPouFRONT_WIPERBitIndex          << c8Bits)),    //    7    HS    DO_RELAY_FRONT_WIPER_CAR
    ((U16)cDATPouBAT_LIGHT_TEMPOByteIndex      | (U16)((U16)cDATPouBAT_LIGHT_TEMPOBitIndex      << c8Bits)),    //    8    HS    DO_RELAY_ALIM_TEMPO_CAR
    ((U16)cDATPouDEFROSTERByteIndex            | (U16)((U16)cDATPouDEFROSTERBitIndex            << c8Bits)),    //    9    LS    DO_DRIVE_DEFROSTER_CAR
    ((U16)cDATPouHORN_RLByteIndex              | (U16)((U16)cDATPouHORN_RLBitIndex              << c8Bits)),    //    0A    LS    DO_DRIVE_KLAXON_CAR
    ((U16)cDATPouOPEN_DOOR_LEDByteIndex        | (U16)((U16)cDATPouOPEN_DOOR_LEDBitIndex        << c8Bits)),    //    0B    LS    DO_DOOR-LOCK_LED_CAR
    ((U16)cDATPouVERLOG_LEDByteIndex           | (U16)((U16)cDATPouVERLOG_LEDBitIndex           << c8Bits)),    //    0C    LS    DO_DRIVE_LED-VERLOG_CAR
    ((U16)cInvalidSequentialOutput                                                                   ),    //    0D    LS    DIO_ECM_CAR
    ((U16)cInvalidSequentialOutput                                                                   ),    //    0E    LS    DIO_IMMOBILIZER_CAR
    ((U16)cInvalidSequentialOutput                                                                   ),    //    0F    LS    DO_DRIVE_CEILING_LIGHT_CAR
    ((U16)cInvalidSequentialOutput                                                                   )     //    10    NA    BUZZER

};

static const tDATEepBloc EepBanksList[cNbEepBanks+1] = {mDATEepDeclareBlocList()}; 
//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Constant exported data
//------------------------------------------------------------------------------
//QACJ 3211: akodzhh: Identifier is exported and used in LAP_KWP to init TFC session
const U8 TabIdentifierServiceSupportedInTfcSession[cNbServicesSupportedInTFC] =
          mInitTfcTabIdentifierServiceSupported();
//QACJ 3211: akodzhh: Identifier is exported and used in LAP_KWP to init TFC session
const tLAPKwpServiceFunction TabServiceSupportedInTfcSession[cNbServicesSupportedInTFC] =
          mInitTfcTabServiceSupported();

//------------------------------------------------------------------------------
// Local function prototypes
//------------------------------------------------------------------------------
static MEM_TYPE U16  ROMChecksumCalculation(void);
static MEM_TYPE void SetOutput  (const U8 u8OutputNumberP);
static MEM_TYPE void ClearOutput(const U8 u8OutputNumberP);
static MEM_TYPE BOOL IsOrderingMatrixDataValid(void);
static MEM_TYPE void ClearOutputAndSetResult(const U8 u8OutputNumberP);
static MEM_TYPE void DeactivateOutputs(const BOOL bSetResultsP);
static MEM_TYPE BOOL ReadInputsAndSetResult(void);

static MEM_TYPE U8   StartAutoTestTOR (void);
static MEM_TYPE void StopAutoTestTOR  (void);

#ifdef BOOTLOADER_IS_SUPPORTED
static MEM_TYPE U8   ReadECU_LOG(void);
#endif

#ifdef X90_PROJECT
static MEM_TYPE void ActivateOutputs_Static(void);
static MEM_TYPE BOOL IsAutoTestFinished_Static(void);
static MEM_TYPE void TreatEepromTest_Static(void);
#endif

//==============================================================================
//=========================== LOCAL FUNCTIONS ==================================
//==============================================================================
//==============================================================================
// DESCRIPTION:         ROMChecksumCalculation
//
// PARAMETERS:          none
//
// RETURN VALUE:        U16
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
static MEM_TYPE U16 ROMChecksumCalculation(void)
{
    //QACJ 0306: akodzhh: X90_BCM project specific checksum calculation
    //QACJ 0506: akodzhh: X90_BCM project specific checksum calculation
    //QACJ 1302: akodzhh: X90_BCM project specific checksum calculation
    //QACJ 3335: akodzhh: X90_BCM project specific checksum calculation
    return( cRomChecksum );
}

//==============================================================================
// DESCRIPTION:         SetOutput
//
// PARAMETERS:          U8
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
static MEM_TYPE void SetOutput(const U8 u8OutputNumberP)
{
    mLIBassert(u8OutputNumberP < cOutputsNumber);
    if (u8OutputNumberP == cPwmRoomLampOutputPos)
    {
        mLIBassert(u16OutputTab[cPwmRoomLampOutputPos] == cInvalidSequentialOutput);
        mDATWrite(U8Bit,PWM_ROOMLAMPDiagRatio, cPwmRoomLampDiagRatio, Default);
    }
    else if(u8OutputNumberP == cBuzzerOutputPos)
    {
        mDATWrite(U16Bit,DATBuzDiagBuzz, cDiagBuzzFrequency, Default);
    }
    else if(u8OutputNumberP == cTxVerlogOutputPos)
    {
        mDATWrite(U1Bit,DO_VERLOGDiagEnabled, cTrue, Default);
        mDATWrite(U1Bit,DO_VERLOGDiag, 1, Default);    
    }
    else if(u8OutputNumberP == cTxImmobilzerOutputPos)
    {
        mDATWrite(U1Bit,DO_DATA_IMMOBILIZERDiagEnabled, cTrue, Default);
        mDATWrite(U1Bit,DO_DATA_IMMOBILIZERDiag, 1, Default);
    }
    else    // Set digital output
    {   // output shared with Alarm - stop Alarm
        if((u8OutputNumberP == cOPEN_DOOR_LEDOutputPos)
         &&(mDATRead(U1Bit,IsAlaDiagEnabled, Default ) == cFalse) )
        {            
            TOSSendControl(cTOSControlAlaDiagEnable);
        }
       
        mDATWriteTable(U1Bit,DATPouDiagBuffer,u16OutputTab[u8OutputNumberP],1,Default);
    }

}

//==============================================================================
// DESCRIPTION:         ClearOutput
//
// PARAMETERS:          U8
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
static MEM_TYPE void ClearOutput(const U8 u8OutputNumberP)
{
    mLIBassert(u8OutputNumberP < cOutputsNumber);
    // Clear PwmRoomLamp
    if (u8OutputNumberP == cPwmRoomLampOutputPos)
    {
        mLIBassert(u16OutputTab[cPwmRoomLampOutputPos] == cInvalidSequentialOutput);
        mDATWrite(U8Bit,PWM_ROOMLAMPDiagRatio, 0, Default);
    }
    else if(u8OutputNumberP == cBuzzerOutputPos)
    {
        mDATControl(DATBuzDiagBuzz, Stop);
    }
    else if(u8OutputNumberP == cTxVerlogOutputPos)
    {
        mDATWrite(U1Bit,DO_VERLOGDiag, 0, Default);
        mDATWrite(U1Bit,DO_VERLOGDiagEnabled, cFalse, Default);    
    }
    else if(u8OutputNumberP == cTxImmobilzerOutputPos)
    {
        mDATWrite(U1Bit,DO_DATA_IMMOBILIZERDiag, 0, Default);
        mDATWrite(U1Bit,DO_DATA_IMMOBILIZERDiagEnabled, cFalse, Default);

    }
    else
    {
        mDATWriteTable(U1Bit,DATPouDiagBuffer,u16OutputTab[u8OutputNumberP],0,Default);

        if((u8OutputNumberP == cOPEN_DOOR_LEDOutputPos)
         &&(mDATRead(U1Bit,IsAlaDiagEnabled, Default ) == cTrue) )
        {            
            TOSSendControl(cTOSControlAlaDiagDisable);
        }
    }

}

//==============================================================================
// DESCRIPTION:         ClearOutputAndSetResult
//
// PARAMETERS:          U8
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
static MEM_TYPE void ClearOutputAndSetResult(const U8 u8OutputNumberP)
{
    mLIBassert(u8OutputNumberP < cOutputsNumber);
    // Clear PwmRoomLamp
    if (u8OutputNumberP == cPwmRoomLampOutputPos)
    {
        mLIBassert(u16OutputTab[cPwmRoomLampOutputPos] == cInvalidSequentialOutput);
        // HW protection for this output is not available
        mDATWrite(U8Bit,PWM_ROOMLAMPDiagRatio, 0, Default);
    }
    else if(u8OutputNumberP == cBuzzerOutputPos)
    {
        // TODO: HW protection for this output is not available for now
        mDATControl(DATBuzDiagBuzz, Stop);
    }
    else if(u8OutputNumberP == cTxVerlogOutputPos)
    {
        if(mDATRead(U1Bit,DO_VERLOGProtection ,Default) == 1)
        {
            mSetOutputError(u8OutputNumberP);
        }
        mDATWrite(U1Bit,DO_VERLOGDiag, 0, Default);
        mDATWrite(U1Bit,DO_VERLOGDiagEnabled, cFalse, Default);    
    }
    else if(u8OutputNumberP == cTxImmobilzerOutputPos)
    {
        if(mDATRead(U1Bit,DO_DATA_IMMOBILIZERProtection ,Default) == 1)
        {
            mSetOutputError(u8OutputNumberP);
        }
        mDATWrite(U1Bit,DO_DATA_IMMOBILIZERDiag, 0, Default);
        mDATWrite(U1Bit,DO_DATA_IMMOBILIZERDiagEnabled, cFalse, Default);
    }
    else
    {
        mLIBassert(u8OutputNumberP < cPouOutputsNumber);
        if(mDATReadTable(U1Bit,DATPouHardMaskBuffer,u16OutputTab[u8OutputNumberP],Default) == 1)
        {
            mSetOutputError(u8OutputNumberP);
        }
        mDATWriteTable(U1Bit,DATPouDiagBuffer,u16OutputTab[u8OutputNumberP],0,Default);

        if((u8OutputNumberP == cOPEN_DOOR_LEDOutputPos)
         &&(mDATRead(U1Bit,IsAlaDiagEnabled, Default ) == cTrue) )
        {            
            TOSSendControl(cTOSControlAlaDiagDisable);
        }
    }

}

//==============================================================================
// DESCRIPTION:         IsOrderingMatrixDataValid
//
// PARAMETERS:          none
//
// RETURN VALUE:        BOOL
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
static MEM_TYPE BOOL IsOrderingMatrixDataValid(void)
{
    BOOL  bIsDataValid;
    U8    u8IndexL;

    bIsDataValid = cTrue;
    for( u8IndexL = 0; bIsDataValid && (u8IndexL < LAPKwpReadDiagnosticRequest(cOrderingMatrixSizeBytePos));  )
    {
        if(  ((U8)(LAPKwpReadDiagnosticRequest(cOrderingMatrixBytePos+ u8IndexL   )>>c4Bits) > cMaxQuarterOutput)  // Outputs
           ||((U8)(LAPKwpReadDiagnosticRequest(cOrderingMatrixBytePos+(u8IndexL+1))>>c4Bits) > cMaxQuarterInput )) // Inputs
        {
            bIsDataValid = cFalse;
        }
        //QACJ 2469: akodzhh: keep for readability
        u8IndexL += cMatrixPairLng;
    }
    
    return (bIsDataValid);
}

//==============================================================================
// DESCRIPTION:         
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
void ActivateOutputs(void)
{
#ifdef X90_PROJECT
    ActivateOutputs_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void ActivateOutputs_Static(void)
{
#endif    
    U8      u8BitNumber;
    U8      u8OutputIndex;
    BOOL    bBitIsSet;

    for(u8BitNumber = 0; u8BitNumber < c4Bits; u8BitNumber++)
    {
        bBitIsSet = ((u8OrderingMatrix[u8OrderingMatrixCounter] >> u8BitNumber)&1) == 1;
        if (bBitIsSet == cTrue)
        {
            // quartermask 18 -> 1*4+ bit3 -> index=7
            // quartermask 34 -> 3*4+ bit2 -> index=14
            u8OutputIndex = (U8)(((u8OrderingMatrix[u8OrderingMatrixCounter] & cQuarterMask)>>c2Bits) | u8BitNumber); 
            SetOutput(u8OutputIndex);
        }
    }
    

    AutoTestTimeOutValueInTick = mTOSConvMsInTimerTick((U32)u8AutoTestActivTimeOut);
    if(AutoTestTimeOutValueInTick > 0)
    {
        // -1 tick because of Cm005756:TOS Timers introduce an additional delay of 1 graph/task cycle
        AutoTestTimeOutValueInTick--;
    }

    TOSStartTimer(&AutoTestTimer);

    bOutputsActivated = cTrue;
}

//==============================================================================
// DESCRIPTION:         DeactivateOutputs
//
// PARAMETERS:          BOOL bSetResultsP
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
static MEM_TYPE void DeactivateOutputs(const BOOL bSetResultsP)
{
    U8      u8BitNumber;
    U8      u8OutputIndex;
    BOOL    bBitIsSet;

    for(u8BitNumber = 0; u8BitNumber < c4Bits; u8BitNumber++)
    {
        bBitIsSet = ((u8OrderingMatrix[u8OrderingMatrixCounter] >> u8BitNumber)&1) == 1;
        if (bBitIsSet == cTrue)
        {
            u8OutputIndex = (U8)(((u8OrderingMatrix[u8OrderingMatrixCounter] & cQuarterMask)>>c2Bits)| u8BitNumber);
            if(bSetResultsP == cTrue)
            {
                ClearOutputAndSetResult(u8OutputIndex);
            }
            else
            {
                ClearOutput(u8OutputIndex);
            }
        }
    }

    bOutputsActivated = cFalse;

}

//==============================================================================
// DESCRIPTION:         ReadInputsAndSetResult 
//
// PARAMETERS:          none
//
// RETURN VALUE:        BOOL
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
// akodzhh: Size of this function exceeds 100 lines.Keep for readability.
static MEM_TYPE BOOL ReadInputsAndSetResult(void)
{
    BOOL    bInputIsSet;
    U8      u8QuarterNb;
    BOOL    bAllExpectedInputsAreSet;

    u8QuarterNb = (U8)((u8OrderingMatrix[u8OrderingMatrixCounter+1]&cQuarterMask )>>c4Bits);
    bAllExpectedInputsAreSet = cTrue;
   
   
    switch(u8QuarterNb)
    {
    case cQuarter0:
        if( (U8)(u8OrderingMatrix[u8OrderingMatrixCounter+1] & cMaskDI_ENGINE_RPM) ==  cMaskDI_ENGINE_RPM)  
        {
            bInputIsSet = (BOOL)( mDATRead(U1Bit, DI_ENGINE_RPM , Default)&1 );
            if( bInputIsSet == cFalse )
            {    
                mSetInputError(cIndexDI_ENGINE_RPM);
                bAllExpectedInputsAreSet = cFalse;
            }
        }
        if( (U8)(u8OrderingMatrix[u8OrderingMatrixCounter+1] & cMaskPWR_IGN) ==  cMaskPWR_IGN)  
        {
            bInputIsSet = (BOOL)( mDATRead(U1Bit, PWR_IGN, Default)&1 );
            if( bInputIsSet == cFalse )
            {
                mSetInputError(cIndexPWR_IGN);
                bAllExpectedInputsAreSet = cFalse;
            } 
        }
        if( (U8)(u8OrderingMatrix[u8OrderingMatrixCounter+1] & cMaskRR_WASHER_SW) ==  cMaskRR_WASHER_SW)  
        {
            bInputIsSet = (BOOL)( mDATRead(U1Bit, RR_WASHER_SW, Default)&1 );
            if( bInputIsSet == cFalse )
            {
                mSetInputError(cIndexRR_WASHER_SW);
                bAllExpectedInputsAreSet = cFalse;
            } 
        }
        if( (U8)(u8OrderingMatrix[u8OrderingMatrixCounter+1] & cMaskFR_FOG_SW) ==  cMaskFR_FOG_SW)  
        {
            bInputIsSet = (BOOL)( mDATRead(U1Bit, HIGH_LOW_BEAM, Default)&1 );
            if( bInputIsSet == cFalse )
            {
                mSetInputError(cIndexFR_FOG_SW);
                bAllExpectedInputsAreSet = cFalse;
            } 
        }
        break;
    case cQuarter1:
        if( (U8)(u8OrderingMatrix[u8OrderingMatrixCounter+1] & cMaskDI_DATA_IMMOBILIZER) ==  cMaskDI_DATA_IMMOBILIZER)  
        {
            bInputIsSet = (BOOL)( mDATRead(U1Bit, DI_DATA_IMMOBILIZER, Default)&1 );
            if( bInputIsSet == cFalse )
            {
                mSetInputError(cIndexDI_DATA_IMMOBILIZER);
                bAllExpectedInputsAreSet = cFalse; 
            }
        }
        if( (U8)(u8OrderingMatrix[u8OrderingMatrixCounter+1] & cMaskDI_VERLOG) ==  cMaskDI_VERLOG)  
        {
            bInputIsSet = (BOOL)( mDATRead(U1Bit, DI_VERLOG, Default)&1 );
            if( bInputIsSet == cFalse )
            {
                mSetInputError(cIndexDI_VERLOG);
                bAllExpectedInputsAreSet = cFalse;
            } 
        }
        if( (U8)(u8OrderingMatrix[u8OrderingMatrixCounter+1] & cMaskL_FLASHER_SW) ==  cMaskL_FLASHER_SW)  
        {
            bInputIsSet = (BOOL)( mDATRead(U1Bit, L_FLASHER_SW, Default)&1 );
            if( bInputIsSet == cFalse )
            {
                mSetInputError(cIndexL_FLASHER_SW);
                bAllExpectedInputsAreSet = cFalse;
            } 
        }
        if( (U8)(u8OrderingMatrix[u8OrderingMatrixCounter+1] & cMaskFR_DOORS_SW) ==  cMaskFR_DOORS_SW)  
        {
            bInputIsSet = (BOOL)( mDATRead(U1Bit, FR_DOORS_SW, Default)&1 );
            if( bInputIsSet == cFalse )
            {
                mSetInputError(cIndexFR_DOORS_SW);
                bAllExpectedInputsAreSet = cFalse;
            } 
        }
        break;
    case cQuarter2:
        if( (U8)(u8OrderingMatrix[u8OrderingMatrixCounter+1] & cMaskDOOR_LOCK_SW) ==  cMaskDOOR_LOCK_SW)  
        {
            bInputIsSet = (BOOL)( mDATRead(U1Bit, DOOR_LOCK_SW, Default)&1 );
            if( bInputIsSet == cFalse )
            {
                mSetInputError(cIndexDOOR_LOCK_SW);
                bAllExpectedInputsAreSet = cFalse;
            } 
        }
        if( (U8)(u8OrderingMatrix[u8OrderingMatrixCounter+1] & cMaskFR_WIPER_INT_SW) ==  cMaskFR_WIPER_INT_SW)  
        {
            bInputIsSet = (BOOL)( mDATRead(U1Bit, FR_WIPER_INT_SW, Default)&1 );
            if( bInputIsSet == cFalse )
            {
                mSetInputError(cIndexFR_WIPER_INT_SW);
                bAllExpectedInputsAreSet = cFalse;
            } 
        }
        if( (U8)(u8OrderingMatrix[u8OrderingMatrixCounter+1] & cMaskRR_FOG_SW) ==  cMaskRR_FOG_SW)  
        {
            bInputIsSet = (BOOL)( mDATRead(U1Bit, RR_FOG_SW, Default)&1 );
            if( bInputIsSet == cFalse )
            {
                mSetInputError(cIndexRR_FOG_SW);
                bAllExpectedInputsAreSet = cFalse;
            } 
        }
        if( (U8)(u8OrderingMatrix[u8OrderingMatrixCounter+1] & cMaskFR_WASHER_SW) ==  cMaskFR_WASHER_SW)  
        {
            bInputIsSet = (BOOL)( mDATRead(U1Bit, FR_WASHER_SW, Default)&1 );
            if( bInputIsSet == cFalse )
            {
                mSetInputError(cIndexFR_WASHER_SW);
                bAllExpectedInputsAreSet = cFalse;
            } 
        }
        break;
    case cQuarter3:
        if( (U8)(u8OrderingMatrix[u8OrderingMatrixCounter+1] & cMaskAIRBAG_CRASH) ==  cMaskAIRBAG_CRASH)  
        {
            bInputIsSet = (BOOL)( mDATRead(U1Bit, AIRBAG_CRASH, Default)&1 );
            if( bInputIsSet == cFalse )
            {
                mSetInputError(cIndexAIRBAG_CRASH);
                bAllExpectedInputsAreSet = cFalse;
            } 
        }
        if( (U8)(u8OrderingMatrix[u8OrderingMatrixCounter+1] & cMaskVEHICLE_SPEED) ==  cMaskVEHICLE_SPEED)  
        {
            bInputIsSet = (BOOL)( mDATRead(U1Bit, DI_VEHICLE_SPEED, Default)&1 );
            if( bInputIsSet == cFalse )
            {
                mSetInputError(cIndexVEHICLE_SPEED);
                bAllExpectedInputsAreSet = cFalse;
            } 
        }
        if( (U8)(u8OrderingMatrix[u8OrderingMatrixCounter+1] & cMaskFR_AUTOSTOP_SW) ==  cMaskFR_AUTOSTOP_SW)  
        {
            bInputIsSet = (BOOL)( mDATRead(U1Bit, FR_AUTOSTOP_SW, Default)&1 );
            if( bInputIsSet == cFalse )
            {
                mSetInputError(cIndexFR_AUTOSTOP_SW);
                bAllExpectedInputsAreSet = cFalse;
            } 
        }
        if( (U8)(u8OrderingMatrix[u8OrderingMatrixCounter+1] & cMaskRR_AUTOSTOP_SW) ==  cMaskRR_AUTOSTOP_SW)  
        {
            bInputIsSet = (BOOL)( mDATRead(U1Bit, RR_AUTOSTOP_SW, Default)&1 );
            if( bInputIsSet == cFalse )
            {
                mSetInputError(cIndexRR_AUTOSTOP_SW);
                bAllExpectedInputsAreSet = cFalse;
            } 
        }
        break;
    case cQuarter4:
        if( (U8)(u8OrderingMatrix[u8OrderingMatrixCounter+1] & cMaskHAZARD_SW) ==  cMaskHAZARD_SW)  
        {
            bInputIsSet = (BOOL)( mDATRead(U1Bit, HAZARD_SW, Default)&1 );
            if( bInputIsSet == cFalse )
            {
                mSetInputError(cIndexHAZARD_SW);
                bAllExpectedInputsAreSet = cFalse;
            } 
        }
        if( (U8)(u8OrderingMatrix[u8OrderingMatrixCounter+1] & cMaskR_FLASHER_SW) ==  cMaskR_FLASHER_SW)  
        {
            bInputIsSet = (BOOL)( mDATRead(U1Bit, R_FLASHER_SW, Default)&1 );
            if( bInputIsSet == cFalse )
            {
                mSetInputError(cIndexR_FLASHER_SW);
                bAllExpectedInputsAreSet = cFalse;
            } 
        }
        if( (U8)(u8OrderingMatrix[u8OrderingMatrixCounter+1] & cMaskRR_WIPER_INT_SW) ==  cMaskRR_WIPER_INT_SW)  
        {
            bInputIsSet = (BOOL)( mDATRead(U1Bit, RR_WIPER_INT_SW, Default)&1 );
            if( bInputIsSet == cFalse )
            {
                mSetInputError(cIndexRR_WIPER_INT_SW);
                bAllExpectedInputsAreSet = cFalse;
            } 
        }
        if( (U8)(u8OrderingMatrix[u8OrderingMatrixCounter+1] & cMaskPOSITION_LIGHTS) ==  cMaskPOSITION_LIGHTS)  
        {
            bInputIsSet = (BOOL)( mDATRead(U1Bit, POSITION_LIGHTS, Default)&1 );
            if( bInputIsSet == cFalse )
            {
                mSetInputError(cIndexPOSITION_LIGHTS);
                bAllExpectedInputsAreSet = cFalse;
            }
        }
        break;
    case cQuarter5:
        if( (U8)(u8OrderingMatrix[u8OrderingMatrixCounter+1] & cMaskRR_DOORS_SW) ==  cMaskRR_DOORS_SW)  
        {
            bInputIsSet = (BOOL)( mDATRead(U1Bit, RR_DOORS_SW, Default)&1 ); 
            if( bInputIsSet == cFalse )
            {
                mSetInputError(cIndexRR_DOORS_SW);
                bAllExpectedInputsAreSet = cFalse;
            } 
        }
        if( (U8)(u8OrderingMatrix[u8OrderingMatrixCounter+1] & cMaskDOOR_UNLOCK_SW) ==  cMaskDOOR_UNLOCK_SW)  
        {
            bInputIsSet = (BOOL)( mDATRead(U1Bit, DOOR_UNLOCK_SW, Default)&1 );
            if( bInputIsSet == cFalse )
            {
                mSetInputError(cIndexDOOR_UNLOCK_SW);
                bAllExpectedInputsAreSet = cFalse;
            } 
        }
        if( (U8)(u8OrderingMatrix[u8OrderingMatrixCounter+1] & cMaskDEFROSTER_SW) ==  cMaskDEFROSTER_SW)  
        {
            bInputIsSet = (BOOL)( mDATRead(U1Bit, DEFROSTER_SW, Default)&1 );
            if( bInputIsSet == cFalse )
            {
                mSetInputError(cIndexDEFROSTER_SW);
                bAllExpectedInputsAreSet = cFalse;
            } 
        }
        if( (U8)(u8OrderingMatrix[u8OrderingMatrixCounter+1] & cMaskSEATBELT_REMINDER_SW ) ==  cMaskSEATBELT_REMINDER_SW)
        {
            bInputIsSet = (BOOL)( mDATRead(U1Bit, SEATBELT_REMINDER_SW, Default)&1 );
            if( bInputIsSet == cFalse )
            {
                mSetInputError(cIndexSEATBELT_REMINDER_SW);
                bAllExpectedInputsAreSet = cFalse;
            } 
        }
        break;
    
    default:
        //CCOV: akodzhh: can't be covered, no other Quarter
        mLIBassert(cFalse);
        bAllExpectedInputsAreSet = cFalse;
        break;
    }

    return bAllExpectedInputsAreSet;
   
}

#ifdef BOOTLOADER_IS_SUPPORTED
//==============================================================================
// DESCRIPTION:         ReadECU_LOG
//
// PARAMETERS:          None
//
// RETURN VALUE:        U8 Request Status
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
static MEM_TYPE U8 ReadECU_LOG (void)
{
    U8 u8RequestStatusL;
    BOOL bResult;
    //QACJ 3672: akodzhh: Pointer value is correct
    tpRetreiveLogZoneRecord RetreiveLogZoneRecord;

    U8 IdentRecordL[cLogZoneSize];
    U8 ReprogRecordL[cLogZoneSize];
    U8* pSvcResponseL;
    U8 u8IndexL;

    //QACJ 0305: akodzhh: Cast is intentional and safety
    if ((BOOL)mLAPKwpCheckBootloaderPresent() != cFalse)
    {
        RetreiveLogZoneRecord = 
            ((tBootLinkTable*)cLIBBooBootLinkTableAddress)->pRetreiveLogZoneRecord;

        // call bootloader function to read log zone
        bResult = RetreiveLogZoneRecord(IdentRecordL, cLastLogZoneId); // IDENT

        if (bResult != cFalse)
        {
            bResult = RetreiveLogZoneRecord(ReprogRecordL, (U8)(cLastLogZoneId + (U8)1U)); // REPROG
        }
        
        if( bResult == cFalse )
        {
            u8RequestStatusL = cLAPKwpInvalidFormat;
        }
        else
        {
            u8RequestStatusL = cLAPKwpServiceIsCorrect;

            // Copy data from log zone into response //

            pSvcResponseL = LAPKwpGetPtrDiagnosticResponse(cByte2);
            u8IndexL = 0;

            // Copy ECU reference / part number
            mLIBmemcpy(pSvcResponseL , &IdentRecordL[cLogZoneSparePartNumberIndex], cEEP_ECUReferenceLength);
            u8IndexL += cEEP_ECUReferenceLength;

            // Copy PIE number / HW number
            mLIBmemcpy(&pSvcResponseL[u8IndexL], &IdentRecordL[cLogZoneHwNumberIndex], cEEP_PieNumberLength);
            u8IndexL += cEEP_PieNumberLength;

            // Copy PIE index / calibration number
            pSvcResponseL[u8IndexL] = IdentRecordL[cLogZoneCalibrationNumberIndex];
            u8IndexL++;
            pSvcResponseL[u8IndexL] = IdentRecordL[cLogZoneCalibrationNumberIndex + 1U];
            u8IndexL++;

            // Copy serial number
            mLIBmemcpy(&pSvcResponseL[u8IndexL], &IdentRecordL[cLogZoneSerialNumberIndex], cEEP_SerialNumberLength);
            u8IndexL += cEEP_SerialNumberLength;

            // Copy date code
            mLIBmemcpy(&pSvcResponseL[u8IndexL], &ReprogRecordL[cLogZoneDateIndex], cEEP_DateCodeLength + 1);
            u8IndexL += cEEP_DateCodeLength + 1;

            // Copy ECU Type
            pSvcResponseL[u8IndexL] = IdentRecordL[cLogZoneEcuTypeIndex];
        }        
    }
    else // bootloader not present
    {
        u8RequestStatusL = cLAPKwpInvalidFormat;
    }
    return u8RequestStatusL;
}
#endif // BOOTLOADER_IS_SUPPORTED


//==============================================================================
//=========================== EXPORTED FUNCTIONS ===============================
//==============================================================================
//==============================================================================
// DESCRIPTION:         LAPTfcTreatReadDataByLocalIdentifierService
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
// akodzhh: Size of this function exceeds 100 lines. It is AW1092 reuse, keep for readability.
MEM_TYPE void LAPTfcTreatReadDataByLocalIdentifierService(void)
{  
    U8  u8RequestStatus;
    U8  u8ResponseLength;
    U16 u16Checksum;
    U8  u8Index;
    U8  u8TempVar;
    U8  u8ByteNb;
  
    u8ResponseLength = 0;
    u8RequestStatus = cLAPKwpServiceIsCorrect;
    if(  ((mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cRDBLIDReq_Lgth)
        &&(LAPKwpReadDiagnosticRequest(1) != cRDBLID_AnalogValueID ))
       ||((mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cRDBLIDReq_AnalogValueLgth)
        &&(LAPKwpReadDiagnosticRequest(1) == cRDBLID_AnalogValueID ) ))
    {  
        switch (LAPKwpReadDiagnosticRequest(1))
        {

        case cRDBLID_SoftwareAndTFCVersionID :
            u8ByteNb = cByte2;  // first data byte in response
            // Software version and revision
            LAPKwpWriteDiagnosticResponse(u8ByteNb,mDATRead(U8Bit,TfcVersionNum,Default));
            u8ByteNb++;
            LAPKwpWriteDiagnosticResponse(u8ByteNb,mDATRead(U8Bit,TfcRevisionNum,Default));
            u8ByteNb++;


            // EEP version and revision 
            LAPKwpWriteDiagnosticResponse(u8ByteNb,mDATRead(U8Bit,EEP_VersionEEPROM,Default));
            u8ByteNb++;
            LAPKwpWriteDiagnosticResponse(u8ByteNb,mDATRead(U8Bit,EEP_RevisionEEPROM,Default));
            u8ByteNb++;

            // Checksum  
            u16Checksum = ROMChecksumCalculation();  
            LAPKwpWriteDiagnosticResponse(u8ByteNb,0x00);
            u8ByteNb++;
            LAPKwpWriteDiagnosticResponse(u8ByteNb,0x00);
            u8ByteNb++;
            LAPKwpWriteDiagnosticResponse(u8ByteNb,(((U8)(u16Checksum>>c8Bits ) &cLSBMask)));
            u8ByteNb++;
            LAPKwpWriteDiagnosticResponse(u8ByteNb,(((U8)(u16Checksum    ) &cLSBMask)));


            u8ResponseLength = cRDBLIDAns_SoftwareAndTFCVersion_Lgth;
            break;

        case cRDBLID_TFCDataID :
            // MPR
            u8TempVar = ReadECU_LOG();
            //CCOV adzhelp: Bootloader is not available in unit test framework
            if (u8TempVar == cLAPKwpServiceIsCorrect)
            {
                // if Date is present in EEP substitute log zone content
                if (  (mDATReadTable(U8Bit,EEP_DateCode, 0,Default) != 0)
                    ||(mDATReadTable(U8Bit,EEP_DateCode, 1,Default) != 0) )
                {
                    LAPKwpWriteDiagnosticResponse(((U8)cDateCodeIndex+(U8)cByte0), 0);
                    LAPKwpWriteDiagnosticResponse(((U8)cDateCodeIndex+(U8)cByte1), 
                        mDATReadTable(U8Bit, EEP_DateCode, 0U, Default));
                    LAPKwpWriteDiagnosticResponse(((U8)cDateCodeIndex+(U8)cByte2), 
                        mDATReadTable(U8Bit, EEP_DateCode, 1U, Default));
                }
                // Serial number is obtained from EEP if it exists
                if (   (mDATReadTable(U8Bit, EEP_SerialNumber, cByte0, Default) != 0) 
                     ||(mDATReadTable(U8Bit, EEP_SerialNumber, cByte1, Default) != 0) 
                     ||(mDATReadTable(U8Bit, EEP_SerialNumber, cByte2, Default) != 0) )
                {
                    // Serial number exists in EEP, use it
                    for (u8Index = 0; u8Index < cEEP_SerialNumberLength; u8Index++)
                    {
                        LAPKwpWriteDiagnosticResponse(((U8)cSerialNumberIndex+(U8)u8Index),
                            mDATReadTable(U8Bit, EEP_SerialNumber, u8Index, Default));
                    }
                }
            }
            else
            {
            #if defined(COMPILATION_NATIVE) || defined(UTEST) || defined(DEBUG)
                u8ByteNb = cByte2;

                // ECU reference cannot be obtained from log zone, get it from ROM
                for (u8Index=0; u8Index<cEEP_ECUReferenceLength; u8Index++)
                {
                    LAPKwpWriteDiagnosticResponse(u8ByteNb+u8Index,mDATReadTable(U8Bit,EEP_ECUReference,u8Index,Default));
                }

                u8ByteNb += cEEP_ECUReferenceLength;
                // PIE
                for (u8Index=0; u8Index<cEEP_PieNumberLength; u8Index++)
                {
                    LAPKwpWriteDiagnosticResponse(u8ByteNb+u8Index,mDATReadTable(U8Bit,EEP_PieNumber,u8Index,Default));
                }
                u8ByteNb += cEEP_PieNumberLength;
                // Indice PIE
                for (u8Index=0; u8Index<cEEP_PieIndexLength; u8Index++)
                {
                    LAPKwpWriteDiagnosticResponse(u8ByteNb+u8Index,mDATReadTable(U8Bit,EEP_PieIndex,u8Index,Default));
                }
                u8ByteNb += cEEP_PieIndexLength;
                // Numéro de série
                for (u8Index=0; u8Index<cEEP_SerialNumberLength; u8Index++)
                {
                    LAPKwpWriteDiagnosticResponse(u8ByteNb+u8Index,mDATReadTable(U8Bit,EEP_SerialNumber,u8Index,Default));
                }
                u8ByteNb += cEEP_SerialNumberLength;
                // Code date
                LAPKwpWriteDiagnosticResponse(u8ByteNb, 0);
                u8ByteNb++; // date is placed in LSBs
                for (u8Index=0; u8Index<cEEP_DateCodeLength; u8Index++)
                {
                    LAPKwpWriteDiagnosticResponse(u8ByteNb+u8Index,mDATReadTable(U8Bit,EEP_DateCode,u8Index,Default));
                }
                u8ByteNb += cEEP_DateCodeLength;    
                LAPKwpWriteDiagnosticResponse(u8ByteNb,mDATRead(U8Bit,EEP_ECUType,Default));
                
            #else
                // target with no bootloader
                u8RequestStatus = cLAPKwpConditionNotCorrect;
            #endif
            }

            u8ByteNb = cInSituTestCounterIndex;
            
            // Cmpt passage Test Final
            LAPKwpWriteDiagnosticResponse(u8ByteNb,mDATRead(U8Bit,EEP_InSituTestCounter,Default));
            u8ByteNb++;
            // FunctTestCounter              
            LAPKwpWriteDiagnosticResponse(u8ByteNb,mDATRead(U8Bit,EEP_PassingTestCounter  ,Default));
            u8ByteNb++;
            // RunningTestCounter
            LAPKwpWriteDiagnosticResponse(u8ByteNb,mDATRead(U8Bit,EEP_ReliabilityTestCounter,Default));
            u8ByteNb++;
            LAPKwpWriteDiagnosticResponse(u8ByteNb,mDATRead(U8Bit,EEP_RfTestCounter     ,Default));
            u8ByteNb++;
            LAPKwpWriteDiagnosticResponse(u8ByteNb,mDATRead(U8Bit,EEP_FinalTestCounter  ,Default));
            u8ByteNb++;

            LAPKwpWriteDiagnosticResponse(u8ByteNb,mDATRead(U8Bit,EEP_FlaCoeffLNormal , Default));
            u8ByteNb++;
            LAPKwpWriteDiagnosticResponse(u8ByteNb,mDATRead(U8Bit,EEP_FlaCoeffRNormal , Default));

            u8ResponseLength = cRDBLIDAns_TFCData_Lgth;
            break;

        case cRDBLID_DigitalInputsID :
            u8ByteNb = cByte2;    
            //QACJ 3198: akodzhh: Variable is initialized and then modified bit by bit before being used
            u8TempVar = 0x00; // Byte 1
            u8TempVar =  (mDATRead(U1Bit, DI_ENGINE_RPM ,Default ) << 0)    // DI_ENGINE_RPM (P14.0)
                        |(mDATRead(U1Bit, PWR_IGN       ,Default ) << 1)    // APC / WAKE-UP_BCM (P0.1)
                        // Fixed value
                        |(mDATRead(U1Bit, RR_WASHER_SW        ,Default ) << c3Bits)    // DI_CMD_REAR_WASHER (P0.3)
                        |(mDATRead(U1Bit, HIGH_LOW_BEAM       ,Default ) << c4Bits)    // DI_CTC_FRONT_FOG / DI_CTC_LOW-HIGH_BEAM (P0.4)
                        |(mDATRead(U1Bit, DI_DATA_IMMOBILIZER ,Default ) << c5Bits)    // RX_DIO_IMOBILIZER (P0.5)
                        // Fixed value
                        |(mDATRead(U1Bit, DI_VERLOG     , Default ) << c7Bits);   // RX_DIO_ECM_MOTOR (P1.7)
            LAPKwpWriteDiagnosticResponse(u8ByteNb,u8TempVar);
            u8ByteNb++;

            //QACJ 3198: akodzhh: Variable is initialized and then modified bit by bit before being used
            u8TempVar = 0x00; // Byte 2
            u8TempVar =   (mDATRead(U1Bit, L_FLASHER_SW      , Default ) << 0)    // DI_CMD_LEFT_INDICATOR (P12.0)
                         // Fixed value
                         // Fixed value
                         |(mDATRead(U1Bit, FR_DOORS_SW       , Default ) << c3Bits)    // DI_CTC_FRONT_DOORS (P12.3)
                         |(mDATRead(U1Bit, DOOR_LOCK_SW      , Default ) << c4Bits)    // DI_CMD_DOOR-LOCK (P12.4)
                         |(mDATRead(U1Bit, FR_WIPER_INT_SW   , Default ) << c5Bits)    // DI_CMD_FRONT_WIPER_INT (P2.5)  - !!!Ana
                         |(mDATRead(U1Bit, RR_FOG_SW         , Default ) << c6Bits)    // DI_CTC_REAR_FOG (P2.6)
                         |(mDATRead(U1Bit, FR_WASHER_SW      , Default ) << c7Bits);   // DI_CMD_FRONT_WASHER (P2.7)
            LAPKwpWriteDiagnosticResponse(u8ByteNb,u8TempVar);
            u8ByteNb++;

            //QACJ 3198: akodzhh: Variable is initialized and then modified bit by bit before being used
            u8TempVar = 0x00;// Byte 3
            u8TempVar =   (mDATRead(U1Bit, AIRBAG_CRASH     , Default ) << 0)    // DI_AIRBAG_CRASH (P3.0)
                         |(mDATRead(U1Bit, DI_VEHICLE_SPEED , Default ) << 1)    // DI_VEHICLE_SPEED (P3.1)    - !!!
                         |(mDATRead(U1Bit, FR_AUTOSTOP_SW   , Default ) << c2Bits)    // DI_RELAY_FRONT_WIPER_STOP_CAR (P3.2)  - !!!
                         |(mDATRead(U1Bit, RR_AUTOSTOP_SW   , Default ) << c3Bits)    // DI_CTC_REAR_WIPER_STOP (P3.3) - !!!
                        // Fixed value
                        // Fixed value
                         |(mDATRead(U1Bit, HAZARD_SW        , Default ) << c6Bits)    // DI_CMD_WARNING (P4.2) - !!!
                         |(mDATRead(U1Bit, R_FLASHER_SW     , Default ) << c7Bits);   // DI_CMD_RIGHT_INDICATOR (P4.3)
            LAPKwpWriteDiagnosticResponse(u8ByteNb,u8TempVar);
            u8ByteNb++;

            //QACJ 3198: akodzhh: Variable is initialized and then modified bit by bit before being used
            u8TempVar = 0x00; // Byte 4
            u8TempVar =  (mDATRead(U1Bit, RR_WIPER_INT_SW       , Default ) << 1)    // DI_CMD_REAR_WIPER (P5.1) - ???
                        // Fixed value
                         |(mDATRead(U1Bit, POSITION_LIGHTS      , Default ) << c3Bits)    // DI_CTC_DIMMERS (P5.3)   - !!!
                         |(mDATRead(U1Bit, RR_DOORS_SW          , Default ) << c4Bits)    // DI_CTC_REAR_DOOR (P6.0)
                         |(mDATRead(U1Bit, DOOR_UNLOCK_SW       , Default ) << c5Bits)    // DI_CMD_DOOR-UNLOCK (P6.1)
                         |(mDATRead(U1Bit, DEFROSTER_SW         , Default ) << c6Bits)    // DI_CMD_DEFROSTER (P6.2)
                         |(mDATRead(U1Bit, SEATBELT_REMINDER_SW , Default ) << c7Bits);   // DI_CTC_SEAT-BELT (P6.3)
            LAPKwpWriteDiagnosticResponse(u8ByteNb,u8TempVar);

            u8ResponseLength = cRDBLIDAns_DigitalInputs_Lgth;
            break;

        case cRDBLID_AnalogValueID :
            if(   (LAPKwpReadDiagnosticRequest(cByte2)== cReadingOptionDirect)
                ||(LAPKwpReadDiagnosticRequest(cByte2)== cReadingOptionCorrection))
            {
                u8ByteNb = cByte2;
                LAPKwpWriteDiagnosticResponse(u8ByteNb,  LAPKwpReadDiagnosticRequest(cByte2));  // #3 ReadingOption
                u8ByteNb++;
                LAPKwpWriteDiagnosticResponse(u8ByteNb,  (U8)((mDATRead(U16Bit, BATTERY_VOLTAGE, Immediate) & cu16MSBMask)  >> c8Bits));
                u8ByteNb++;
                LAPKwpWriteDiagnosticResponse(u8ByteNb,  (U8)( mDATRead(U16Bit, BATTERY_VOLTAGE, Immediate) & cu16LSBMask));
                u8ByteNb++;
                LAPKwpWriteDiagnosticResponse(u8ByteNb,  (U8)((mDATRead(U16Bit, ULQCurrentInMilliAmpers, Immediate) & cu16MSBMask)  >> c8Bits));
                u8ByteNb++;
                LAPKwpWriteDiagnosticResponse(u8ByteNb,  (U8)( mDATRead(U16Bit, ULQCurrentInMilliAmpers, Immediate) & cu16LSBMask)); 
                u8ByteNb++;
                LAPKwpWriteDiagnosticResponse(u8ByteNb,  (U8)((mDATRead(U16Bit, KlaxonCurrentInMilliAmpers, Immediate) & cu16MSBMask)  >> c8Bits));
                u8ByteNb++;
                LAPKwpWriteDiagnosticResponse(u8ByteNb,  (U8)( mDATRead(U16Bit, KlaxonCurrentInMilliAmpers, Immediate) & cu16LSBMask)); 
                u8ByteNb++;
                LAPKwpWriteDiagnosticResponse(u8ByteNb,  (U8)((mDATRead(U16Bit, FlashersCurrentInMilliAmpers, Immediate) & cu16MSBMask)  >> c8Bits));
                u8ByteNb++;
                LAPKwpWriteDiagnosticResponse(u8ByteNb, (U8)( mDATRead(U16Bit, FlashersCurrentInMilliAmpers, Immediate) & cu16LSBMask)); 
                u8ByteNb++;
                LAPKwpWriteDiagnosticResponse(u8ByteNb, (U8)((mDATRead(U16Bit, PDOInMilliVolt, Immediate) & cu16MSBMask)  >> c8Bits));
                u8ByteNb++;
                LAPKwpWriteDiagnosticResponse(u8ByteNb, (U8)( mDATRead(U16Bit, PDOInMilliVolt, Immediate) & cu16LSBMask)); 
                u8ByteNb++;
                LAPKwpWriteDiagnosticResponse(u8ByteNb, 0x00);
                u8ByteNb++;
                LAPKwpWriteDiagnosticResponse(u8ByteNb, mDATRead(U8Bit, VEHICLE_SPEED, Default));
                u8ByteNb++;
                LAPKwpWriteDiagnosticResponse(u8ByteNb, 0x00);
                u8ByteNb++;
                LAPKwpWriteDiagnosticResponse(u8ByteNb, (U8)mDATRead(U1Bit,ENGINE_RPM,    Default));

                u8ResponseLength = cRDBLIDAns_AnalogValue_Lgth;
            }
            else
            {
                u8RequestStatus = cLAPKwpInvalidFormat;
            }
            break;

        default :   
            u8RequestStatus = cLAPKwpInvalidFormat;
            break;
        }
              
    }
    else
    {
        u8RequestStatus = cLAPKwpInvalidFormat;
    }

    if(u8RequestStatus == cLAPKwpServiceIsCorrect)
    {
        LAPKwpWriteDiagnosticResponse(1,LAPKwpReadDiagnosticRequest(1));
        LAPKwpPreparePositiveResponse(u8ResponseLength);
    }
    else
    {
        LAPKwpPrepareNegativeResponse(u8RequestStatus);
    }
    LAPKwpSetServiceIsFinished();
}

//==============================================================================
// DESCRIPTION:         LAPTfcTreatWriteDataByLocalIdentifierService
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
// akodzhh: Size of this function exceeds 100 lines. It is AW1092 reuse, keep for readability.
MEM_TYPE void LAPTfcTreatWriteDataByLocalIdentifierService(void)
{ 
    U8  u8RequestStatus;
    U8  u8Index;
    U8  u8ByteNb;

    u8RequestStatus = cLAPKwpServiceIsCorrect;

    if(LAPKwpIsServiceTreated() == cFalse )
    {
        switch (LAPKwpReadDiagnosticRequest(1))
        {

        case cWDBLID_JCAEDataID :
            if(   (mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cWDBLIDReq_JCAEData_Lgth)
                &&(LAPKwpReadDiagnosticRequest(cECUTypeByte) <= cECUTypeMax)) // ECUType 0..7
            {
                u8ByteNb = cByte2;

                // ECU Reference is written by bootloader in log zone 
                u8ByteNb += cEEP_ECUReferenceLength;
                // PIE
                for (u8Index=0; u8Index<cEEP_PieNumberLength; u8Index++)
                {
                    mDATWriteTable(U8Bit, EEP_PieNumber, u8Index, LAPKwpReadDiagnosticRequest(u8ByteNb+u8Index), Default);
                }
                u8ByteNb += cEEP_PieNumberLength;
                // Indice PIE
                for (u8Index=0; u8Index<cEEP_PieIndexLength; u8Index++)
                {
                    mDATWriteTable(U8Bit, EEP_PieIndex, u8Index, LAPKwpReadDiagnosticRequest(u8ByteNb+u8Index), Default);
                }
                u8ByteNb += cEEP_PieIndexLength;
                for (u8Index=0; u8Index<cEEP_SerialNumberLength; u8Index++)
                {
                    mDATWriteTable(U8Bit, EEP_SerialNumber, u8Index, LAPKwpReadDiagnosticRequest(u8ByteNb+u8Index), Default);
                }
                u8ByteNb += cEEP_SerialNumberLength;
                // Code date
                for (u8Index=0; u8Index<cEEP_DateCodeLength; u8Index++)
                {
                    mDATWriteTable(U8Bit, EEP_DateCode, u8Index, LAPKwpReadDiagnosticRequest(u8ByteNb+u8Index), Default);
                }
                
                mDATWrite(U8Bit, EEP_ECUType, LAPKwpReadDiagnosticRequest(cECUTypeByte), Default);

            }
            else
            {
                u8RequestStatus = cLAPKwpInvalidFormat;
            }
            break;

        case cWDBLID_InSituTestCounterID :
            if(mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cWDBLIDReq_TestCounter_Lgth)
            {
                mDATWrite(U8Bit, EEP_InSituTestCounter,LAPKwpReadDiagnosticRequest(cByte2),Default);
            }
            else
            {
                u8RequestStatus = cLAPKwpInvalidFormat;
            }
            break;

        case cWDBLID_FunctTestCounterID :
            if(mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cWDBLIDReq_TestCounter_Lgth)
            {
                mDATWrite(U8Bit, EEP_PassingTestCounter,LAPKwpReadDiagnosticRequest(cByte2),Default);
            }
            else
            {
                u8RequestStatus = cLAPKwpInvalidFormat;
            }
            break;

        case cWDBLID_RunningTestCounterID :
            if(mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cWDBLIDReq_TestCounter_Lgth)
            {
                mDATWrite(U8Bit, EEP_ReliabilityTestCounter,LAPKwpReadDiagnosticRequest(cByte2),Default);
            }
            else
            {
                u8RequestStatus = cLAPKwpInvalidFormat;
            }
            break;

        case cWDBLID_RfTestCounterID :
            if(mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cWDBLIDReq_TestCounter_Lgth)
            {
                mDATWrite(U8Bit, EEP_RfTestCounter,LAPKwpReadDiagnosticRequest(cByte2),Default);
            }
            else
            {
                u8RequestStatus = cLAPKwpInvalidFormat;
            }
            break;

        case cWDBLID_FinalTestCounterID :
            if(mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cWDBLIDReq_TestCounter_Lgth)
            {
                mDATWrite(U8Bit, EEP_FinalTestCounter,LAPKwpReadDiagnosticRequest(cByte2),Default);
            }
            else
            {
                u8RequestStatus = cLAPKwpInvalidFormat;
            }
            break;

        case cWDBLID_FlashersCoeffID :
            if(mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cWDBLIDReq_FlashersCoeff_Lgth)
            {
                mDATWrite(U8Bit, EEP_FlaCoeffLNormal, LAPKwpReadDiagnosticRequest(cByte2),Default);
                mDATWrite(U8Bit, EEP_FlaCoeffRNormal, LAPKwpReadDiagnosticRequest(cByte3),Default);
                // Cm006406: removed FlasherCoeffLeft_trailer, FlasherCoeffRight_trailer (Cm006435:SPEC)
            }
            else
            {
                u8RequestStatus = cLAPKwpInvalidFormat;
            }
            break;

        default :
            u8RequestStatus = cLAPKwpInvalidFormat;
            break;
        }   // Switch SubFunction

        if( u8RequestStatus == cLAPKwpServiceIsCorrect)
        {
            mDATControl(Eep,UpDateEepGroupSupplierBank);
            LAPKwpSetServiceIsTreated();
        }
        else
        {
            LAPKwpSetServiceIsFinished();
        }

    }
    else     // service is already started, waiting write to be finished
    {
        if(mDATRead(U1Bit,IsEepGroupSupplierBankProcessing,Default) == cFalse)
        {
            if(mDATRead(U1Bit,IsEepGroupSupplierBankWriteOk,Default) == cFalse)
            {
                u8RequestStatus = cLAPKwpFaultUponWriting;
            }

            LAPKwpSetServiceIsFinished();
        }

    }

    if( LAPKwpIsServiceTreated() == cFalse )
    {
        if(u8RequestStatus != cLAPKwpServiceIsCorrect)
        {
            LAPKwpPrepareNegativeResponse(u8RequestStatus);
        }
        else
        {
            LAPKwpWriteDiagnosticResponse(1,LAPKwpReadDiagnosticRequest(1));
            LAPKwpPreparePositiveResponse(cByte2);
        }
    }
  

}

//==============================================================================
// DESCRIPTION:         LAPTfcTreatInputOutputControlByLocalIdentifierService
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
MEM_TYPE void LAPTfcTreatInputOutputControlByLocalIdentifierService(void)
{
    U8  u8RequestStatus;
    U8  u8OutputIndex;

    u8RequestStatus = cLAPKwpInvalidFormat;

    if (mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cIOCBLIDReq_Lgth)
    {
        if(   (LAPKwpReadDiagnosticRequest(1) == cIOCBLID_ManualOutputMode)
            &&(LAPKwpReadDiagnosticRequest(cByte2) == cIOCBLID_StartPermanentCtrl)
            &&(LAPKwpReadDiagnosticRequest(cByte3) <= cOutputsNumber)
            &&(LAPKwpReadDiagnosticRequest(cByte3) >= 0x01))
        {
            u8OutputIndex = LAPKwpReadDiagnosticRequest(cByte3) - (U8)1;
            // Control requested parameter
            if (LAPKwpReadDiagnosticRequest(cByte4) == 0x01)   // Output activated
            {
                SetOutput(u8OutputIndex);
                u8RequestStatus = cLAPKwpServiceIsCorrect;

            }
            else if(LAPKwpReadDiagnosticRequest(cByte4) == 0x00)   // Output deactived
            {
                ClearOutput(u8OutputIndex);
                u8RequestStatus = cLAPKwpServiceIsCorrect;
            }
            else
            {
                // invalid format
            }

        }
    }
    // Request treatment is finished or status is not correct
    if(u8RequestStatus != cLAPKwpServiceIsCorrect)
    {
        LAPKwpPrepareNegativeResponse(u8RequestStatus);
    }
    else
    {
        LAPKwpPreparePositiveResponse(cIOCBLIDAns_Lgth);
        LAPKwpWriteDiagnosticResponse(1,LAPKwpReadDiagnosticRequest(1));
        LAPKwpWriteDiagnosticResponse(cByte2,cRoutineInProgress); // prsFS-532
    }
    LAPKwpSetServiceIsFinished();
}

//==============================================================================
// DESCRIPTION:         LAPTfcTreatStartRoutineByLocalIdentifierService
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
// akodzhh: Size of this function exceeds 100 lines. It is AW1092 reuse, keep for readability.
MEM_TYPE void LAPTfcTreatStartRoutineByLocalIdentifierService(void)
{
    U8  u8AnswerStatus;
    U8  u8LenghtAnswer;
    U8  u8Index;
    U8  u8SerialLineTestStatus;
    U8  u8ByteNb;
    
    u8AnswerStatus = cLAPKwpServiceIsCorrect;
    u8LenghtAnswer = cSRBLID_StaticRepLgth;

    switch(LAPKwpReadDiagnosticRequest(1))
    {
    case cSRBID_FlasherTest:
        if( LAPKwpIsServiceTreated() == cFalse )    // prsFS-534 - no routine option byte (command)
        {
            if ( mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == (cSRBID_FlasherTestReq_Lgth)) 
            {
                if (LAPKwpReadDiagnosticRequest(cByte2) == 0x01) // Right flasher
                {

                    TOSSendControl(cTOSControlRightFlashingForTFC);
                    // Stop the output control by diag (the soft component flasher shoud set this output)
                    mDATWriteTable(U1Bit,DATPouDiagMaskBuffer,u16OutputTab[1],0,Default);

                    LAPKwpSetServiceIsTreated();
                }
                else if (LAPKwpReadDiagnosticRequest(cByte2) == 0x00) // Left flasher
                {
                    TOSSendControl(cTOSControlLeftFlashingForTFC);
                    // Stop the output control by diag (the soft component flasher shoud set this output)
                    mDATWriteTable(U1Bit,DATPouDiagMaskBuffer,u16OutputTab[0],0,Default);

                    LAPKwpSetServiceIsTreated();
                }
                else
                {
                    u8AnswerStatus = cLAPKwpInvalidFormat;
                }
            }
            else
            {
                u8AnswerStatus = cLAPKwpInvalidFormat;
            }

        }
        else // service treated - chek results
        {
            if (mDATRead(U8Bit, FlasherLampsTestResult, Default) == cDATCmnFlasherLampsAreOK)
            {

                LAPKwpWriteDiagnosticResponse(cByte2,0x01);    // Lamp OK
                // Restart the output control by diag 
                mDATWriteTable(U1Bit,DATPouDiagMaskBuffer,u16OutputTab[1],1,Default);
                mDATWriteTable(U1Bit,DATPouDiagMaskBuffer,u16OutputTab[0],1,Default);

                LAPKwpSetServiceIsFinished();
            }
            else if (mDATRead(U8Bit, FlasherLampsTestResult, Default) == cDATCmnFlasherLampIsBurnedOut)
            {

                LAPKwpWriteDiagnosticResponse(cByte2,0x00);    // burned out lamp   
                // Restart the output control by diag 
                mDATWriteTable(U1Bit,DATPouDiagMaskBuffer,u16OutputTab[1],1,Default);
                mDATWriteTable(U1Bit,DATPouDiagMaskBuffer,u16OutputTab[0],1,Default);

                LAPKwpSetServiceIsFinished();  
            }
            else
            {
            // in progress - wait next cycle
            }

        }
        break;

    case cSRBID_RFTest:
        if (LAPKwpReadDiagnosticRequest(cByte2) == 0x00) // Launch the routine
        {
            if ( mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cSRBID_RFTestReq_Lgth) 
            {
                // Launch the RF test
                mDATControl(Rf, InitializeRFTest);

                RoutineRequestInProgress[cRoutineIndexRFTest] = cRoutineInProgress;
                u8LenghtAnswer = cSRBLID_RFTestRepLgth;
                LAPKwpWriteDiagnosticResponse(cByte3,mDATRead(U8Bit, DATRfNbRCBlocksReceivedCrcOK, Default));
                LAPKwpWriteDiagnosticResponse(cByte2,cRoutineInProgress);
                
            }
            else
            {
                u8AnswerStatus = cLAPKwpInvalidFormat;
            }
        }
        else if ( (LAPKwpReadDiagnosticRequest(cByte2) == 0x01) // Request status
              &&( mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cSRBLID_StatusReq_Lgth) )
        {
            u8LenghtAnswer = cSRBLID_RFTestRepLgth;
            // Cm006291: update for prsFS-891
            if(RoutineRequestInProgress[cRoutineIndexRFTest] == cRoutineInProgress)
            {
                if( mDATRead(U8Bit, DATRfNbRCBlocksReceivedCrcOK, Default) == (U8)0x00 )
                {
                    LAPKwpWriteDiagnosticResponse(cByte2,cRoutineTerminatedNOK);
                    LAPKwpWriteDiagnosticResponse(cByte3,(U8)0x00);
                }
                else
                {
                    LAPKwpWriteDiagnosticResponse(cByte2,cRoutineTerminatedOK);
                    LAPKwpWriteDiagnosticResponse(cByte3,mDATRead(U8Bit, DATRfNbRCBlocksReceivedCrcOK, Default));
                }
            }
            else
            {
                LAPKwpWriteDiagnosticResponse(cByte2,cRoutineNotActivated);
                LAPKwpWriteDiagnosticResponse(cByte3,(U8)0x00);
            }
            
            RoutineRequestInProgress[cRoutineIndexRFTest] = cRoutineNotActivated;
            
        }
        else
        {
            u8AnswerStatus = cLAPKwpInvalidFormat;
        }
        break;

    case cSRBID_AutoTestTOR:
        if( (mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cSRBLID_StatusReq_Lgth)   // prsFS-583 - stop AutoTest
          &&(LAPKwpReadDiagnosticRequest(cSequenceModeBytePos) == cModeContinueOnErrorTx))
        {
            if(RoutineRequestInProgress[cRoutineIndexAutoTestTOR] == cRoutineInProgress)
            {
                // Exit graph
                StopAutoTestTOR();
                // not finished but terminated
                RoutineRequestInProgress[cRoutineIndexAutoTestTOR] = cRoutineTerminatedNOK;
            }

            // prsFS-579
            u8LenghtAnswer = cSRBLID_AutoTestTOR_RepLgth;

            u8ByteNb = cByte2;
            // Set work status
            LAPKwpWriteDiagnosticResponse(u8ByteNb,RoutineRequestInProgress[cRoutineIndexAutoTestTOR]);
            u8ByteNb++;
            // set response data
            LAPKwpWriteDiagnosticResponse(u8ByteNb,u8OrderingMatrixCounter);
            u8ByteNb++;
            LAPKwpWriteDiagnosticResponse(u8ByteNb,(U8)u16ErrorsOnOutput     );
            u8ByteNb++;
            LAPKwpWriteDiagnosticResponse(u8ByteNb,(U8)(u16ErrorsOnOutput>>c8Bits));
            u8ByteNb++;
            LAPKwpWriteDiagnosticResponse(u8ByteNb,(U8)u32ErrorsOnInput      );
            u8ByteNb++;
            LAPKwpWriteDiagnosticResponse(u8ByteNb,(U8)(u32ErrorsOnInput>>c8Bits) );
            u8ByteNb++;
            LAPKwpWriteDiagnosticResponse(u8ByteNb,(U8)(u32ErrorsOnInput>>c16Bits));

            RoutineRequestInProgress[cRoutineIndexAutoTestTOR]  = cRoutineNotActivated;
            u8OrderingMatrixCounter = 0;
            u16ErrorsOnOutput = 0;
            u32ErrorsOnInput = 0;

        }
        else    // start AutoTest
        {
            u8AnswerStatus = StartAutoTestTOR();
            if(u8AnswerStatus == cLAPKwpServiceIsCorrect)
            {
                RoutineRequestInProgress[cRoutineIndexAutoTestTOR] = cRoutineInProgress;
                LAPKwpWriteDiagnosticResponse(cByte2,cRoutineInProgress);
            }

        }
        break;

    case cSRBID_SerialLineTest:
        if (LAPKwpReadDiagnosticRequest(cByte2) == 0x00) // Launch the routine
        {
            if ( mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cSRBID_SerialLineTestReq_Lgth) 
            {
                if(LAPKwpReadDiagnosticRequest(cByte3) == cSerialLineImmobilizer)
                {
                    if(mDATRead(U8Bit,DATTrpAuthenticationState,Default) != cDATTrpServiceInProgress)
                    {
                        // Launch the  test
                        mDATControl(Trp,  cDATTrpTfcDiag);
                        if(mDATRead(U8Bit,DATTrpAuthenticationState,Default) == cDATTrpServiceInProgress)
                        {
                            RoutineRequestInProgress[cRoutineIndexSerialLineImmoTest] = cRoutineInProgress;
                            LAPKwpWriteDiagnosticResponse(cByte2,cRoutineInProgress);
                        }
                        else
                        {
                            u8AnswerStatus = cLAPKwpConditionNotCorrect;
                        }
                    }
                    else
                    {
                        u8AnswerStatus = cLAPKwpConditionNotCorrect;
                    }
                    
                }
                else if (LAPKwpReadDiagnosticRequest(cByte3) == cSerialLineVerlog)
                {   
                    // start ECM test
                    mDATControl(Vlg, cDATVlgSerialTest);
                    RoutineRequestInProgress[cRoutineIndexSerialLineVerlogTest] = cRoutineInProgress;
                    LAPKwpWriteDiagnosticResponse(cByte2,cRoutineInProgress);
                }
                else
                {   // sub service not suported
                    u8AnswerStatus = cLAPKwpInvalidFormat;
                }
            }
            else
            {
                u8AnswerStatus = cLAPKwpInvalidFormat;
            }
        }
        else if ( (LAPKwpReadDiagnosticRequest(cByte2) == 0x01) // Request status; length 4
              &&( mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cSRBID_SerialLineTestReq_Lgth) ) // prsFS-601
        {
            if(LAPKwpReadDiagnosticRequest(cByte3) == cSerialLineImmobilizer)
            {
                if(RoutineRequestInProgress[cRoutineIndexSerialLineImmoTest] == cRoutineInProgress )
                {
                    u8SerialLineTestStatus = mDATRead(U8Bit,DATTrpAuthenticationState,Default); 
                    if (u8SerialLineTestStatus == cDATTrpServiceSuccessful)
                    {
                        LAPKwpWriteDiagnosticResponse(cByte2,cRoutineTerminatedOK);
                        // Routine is finished - clear status
                        RoutineRequestInProgress[cRoutineIndexSerialLineImmoTest] = cRoutineNotActivated;
                    }
                    else if(u8SerialLineTestStatus == cDATTrpServiceNotSuccessful)
                    {
                        LAPKwpWriteDiagnosticResponse(cByte2,cRoutineTerminatedNOK);
                        // Routine is finished - clear status
                        RoutineRequestInProgress[cRoutineIndexSerialLineImmoTest] = cRoutineNotActivated;
                    }
                    else
                    {   // In progress 
                        LAPKwpWriteDiagnosticResponse(cByte2,cRoutineInProgress);
                    }
                }
                else
                {
                    LAPKwpWriteDiagnosticResponse(cByte2,cRoutineNotActivated);
                }

            }
            else if(LAPKwpReadDiagnosticRequest(cByte3) == cSerialLineVerlog)
            {
                if(RoutineRequestInProgress[cRoutineIndexSerialLineVerlogTest] == cRoutineInProgress )
                {
                    // Chek if send is finished 
                    if (mDATRead(U1Bit,DATVlgSerialTestInProgress,Default) == cFalse)
                    {
                        LAPKwpWriteDiagnosticResponse(cByte2,cRoutineTerminatedOK);
                        // Routine is finished - clear status
                        RoutineRequestInProgress[cRoutineIndexSerialLineVerlogTest] = cRoutineNotActivated;
                    }
                    else
                    {
                        LAPKwpWriteDiagnosticResponse(cByte2,cRoutineInProgress);
                    }

                }
                else
                {
                    LAPKwpWriteDiagnosticResponse(cByte2,cRoutineNotActivated);
                }
            }
            else
            {
                u8AnswerStatus = cLAPKwpInvalidFormat;
            }
        }
        else
        {
            u8AnswerStatus = cLAPKwpInvalidFormat;
        }
        break;

    case cSRBID_SleepingMode:
        if ( (LAPKwpReadDiagnosticRequest(cByte2) == 0x00) // Launch the routine
            &&(mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cSRBID_SleepingModeReq_Lgth))
        {
            TOSStartTimer(&SleepTimer);
            TOSSeqActivateGraph(cTOSSeqLAPTfcGraph);
            mDATWrite(U1Bit, BcmSleepRequested, cTrue, Default); // Cm007575

            LAPKwpWriteDiagnosticResponse(cByte2,cRoutineTerminatedOK);
           
        }
        else
        {
            u8AnswerStatus = cLAPKwpInvalidFormat;
        }
        break;   

    case cSRBID_EepromTest:
        if (LAPKwpReadDiagnosticRequest(cByte2) == 0x00) // Launch the routine
        {
            if ( mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cSRBID_EepromTestReq_Lgth) 
            {
                
                if(RoutineRequestInProgress[cRoutineIndexEepromTest] != cRoutineInProgress)
                {   
                    
                    if(mDATRead(U8Bit,DATDeaActionIsFinished,Default) == cTrue)
                    {   
                        RoutineRequestInProgress[cRoutineIndexEepromTest] = cRoutineInProgress;

                        u8EepTestCounter = 0;
                        // Convert Diag index /u8EepTestCounter/ to EepBanksList index
                        u8Index = BanksCksTable[u8EepTestCounter].u8BankIndex;
                        
                        // Set read request
                        mDATWrite(U8Bit, DATDeaSizeBufferInByte, cCksLgth, Default);
                        mDATWrite(U16Bit, DATDeaAddressInByte, (U16)(EepBanksList[u8Index].Offset<<1), Default);
                        mDATControl(DATDea, StartReadEepromByAddress);

                        TOSSeqActivateGraph(cTOSSeqLAPTfcEepTest);
                    }
                    else
                    {
                        u8AnswerStatus = cLAPKwpConditionNotCorrect;
                        RoutineRequestInProgress[cRoutineIndexEepromTest] = cRoutineNotActivated;
                    }
                    
                }

                LAPKwpWriteDiagnosticResponse(cByte2,cRoutineInProgress);
            }
            else
            {
                u8AnswerStatus = cLAPKwpInvalidFormat;
            }
        }
        else if ( (LAPKwpReadDiagnosticRequest(cByte2) == 0x01) // Request status
               &&( mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cSRBLID_StatusReq_Lgth) )
        {

            if (RoutineRequestInProgress[cRoutineIndexEepromTest] == cRoutineTerminatedOK)
            {
                u8LenghtAnswer = cSRBLID_StaticRepLgth + (U8)(cNbEepBanks<<(U8)1);
                u8Index = 0;
                for (u8EepTestCounter = 0; u8EepTestCounter < cNbEepBanks; u8EepTestCounter++)
                {
                    LAPKwpWriteDiagnosticResponse(cByte3+u8Index, BanksCksTable[u8EepTestCounter].u8BankCksLSB);
                    u8Index++;
                    LAPKwpWriteDiagnosticResponse(cByte3+u8Index, BanksCksTable[u8EepTestCounter].u8BankCksMSB);
                    u8Index++;
                    
                }
              
                LAPKwpWriteDiagnosticResponse(cByte2,cRoutineTerminatedOK);
                // Clear status
                RoutineRequestInProgress[cRoutineIndexEepromTest] = cRoutineNotActivated;
                
            }
            //CCOV: akodzhh: can't be covered. This routine is always OK terminated.
            else if(RoutineRequestInProgress[cRoutineIndexEepromTest] == cRoutineTerminatedNOK)
            {
                LAPKwpWriteDiagnosticResponse(cByte2,cRoutineTerminatedNOK);
                // Clear status
                RoutineRequestInProgress[cRoutineIndexEepromTest] = cRoutineNotActivated;

                                
            }
            else // routine not run or in progress
            {
                LAPKwpWriteDiagnosticResponse(cByte2,RoutineRequestInProgress[cRoutineIndexEepromTest]);
            }
        }
        else
        {
            u8AnswerStatus = cLAPKwpInvalidFormat;
        }

        break;

    case cSRBID_EepromReprogramming:
        // This routine will perform following actions:
        // 1. disable all pins (configure pins as inputs)
        // 2. copy continuosly signal from a given pin to EEPROM CS pin
        // No positive response is returned - exit is by reset

        if (LAPKwpReadDiagnosticRequest(cByte2) == 0x00) // Launch the routine
        {
            if ( mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cSRBID_EepromTestReq_Lgth) 
            {
                // Start routine
                mDATControl(EepromReprogramming, Prepare); // prepare routine
                mDATControl(EepromReprogramming, Start); // no return
            }
        }
        else if ( (LAPKwpReadDiagnosticRequest(cByte2) == 0x01) // Request status
               &&( mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cSRBLID_StatusReq_Lgth) )
        {
            LAPKwpWriteDiagnosticResponse(cByte2,cRoutineNotActivated);
        }
        else
        {
            u8AnswerStatus = cLAPKwpInvalidFormat;
        }
        break;
    
    case cSRBID_ClearFaultsAndCounters:
        if ( (LAPKwpReadDiagnosticRequest(cByte2) == 0x00) // Launch the routine
            &&(mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cSRBID_ClearFaultsAndCountersLgth))
        {
            // Clear fault flags and counters using CDI service by Diagnostics
            TOSSendControl(cTOSControlClearFaultFlagsAndCounters);

            // Reset additional counters
            mDATWrite(U16Bit,   EEP_CDLeftInd,     0, Default); //CDLI
            mDATWrite(U16Bit,   EEP_CDRightInd,    0, Default); //CDRI
            mDATWrite(U16Bit,   EEP_CDRearWiper,   0, Default); //CDRRW
            mDATWrite(U8Bit,    EEP_CDDoorLockLed, 0, Default); //CDDLED
            mDATWrite(U8Bit,    EEP_CDVerlogLed,   0, Default); //CDVLED
            mDATWrite(U8Bit,    EEP_CDVerlog,      0, Default); //CDVER
            mDATWrite(U8Bit,    EEP_CDImmo,        0, Default); //CDIMMO 

            LAPKwpWriteDiagnosticResponse(cByte2,cRoutineTerminatedOK);           
        }
        else
        {
            u8AnswerStatus = cLAPKwpInvalidFormat;
        }
        break;

    default:
        u8AnswerStatus = cLAPKwpInvalidFormat;
        break;
    }


    if(LAPKwpIsServiceTreated() == cFalse)
    {
        if (u8AnswerStatus == cLAPKwpServiceIsCorrect)
        {
            LAPKwpWriteDiagnosticResponse(1,LAPKwpReadDiagnosticRequest(1));

            LAPKwpPreparePositiveResponse(u8LenghtAnswer);
        }
        else
        { // negative response
            LAPKwpPrepareNegativeResponse(u8AnswerStatus);
        }
        LAPKwpSetServiceIsFinished();
    }

}

//==============================================================================
// DESCRIPTION:         LAPTfcInitSession
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
MEM_TYPE void LAPTfcInitSession(void)
{
    U8 u8Index;
    for (u8Index=0; u8Index < cRoutineControlNumber;u8Index++)
    {
        RoutineRequestInProgress[u8Index] = cRoutineNotActivated;
    }

    mDATWrite(U1Bit, PWM_ROOMLAMPDiagMask, (U1)1U,  Default);

    TOSSendControl(cTOSControlActivateFinalTest);
}
//==============================================================================
// DESCRIPTION:         LAPTfcCloseSession
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
MEM_TYPE void LAPTfcCloseSession(void)
{
    tTOSSeqGraphStateType  GraphStateL;

    if( LAPKwpReadDiagnosticRequest(0) == cLAPKwpIdStopCommunication)
    {
        GraphStateL = TOSSeqGraphState(cTOSSeqLAPTfcGraph);

        // start a delay before the reset, in order to send a response first
        if(GraphStateL == cTOSSeqInactiveGraph)
        {
            TOSStartTimer(&SleepTimer);
            TOSSeqActivateGraph(cTOSSeqLAPTfcGraph);
        }
        
    }
    else // expired session
    {
        // Reset the BCM after a TFC diag session expired
        mDATControl(Cpu, Reset);
    }
    
}

//==============================================================================
// DESCRIPTION:         IsAutoTestTimeOutElapsed
//
// PARAMETERS:          none
//
// RETURN VALUE:        BOOL
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
BOOL IsAutoTestTimeOutElapsed(void)
{
    return (BOOL)TOSIsTimerElapsed(&AutoTestTimer, AutoTestTimeOutValueInTick);
}

//==============================================================================
// DESCRIPTION:         StartAutoTestTOR
//
// PARAMETERS:          none
//
// RETURN VALUE:        U8 u8RequestStatus
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
static MEM_TYPE U8 StartAutoTestTOR(void)
{
    U8 u8AnswerStatusL;
    U8 u8ExpectedFrameLgth;
    U8 u8IndexL;

    u8AnswerStatusL = cLAPKwpServiceIsCorrect;

    u8ExpectedFrameLgth = cSRBID_AutoTestTORReqStatic_Lgth + LAPKwpReadDiagnosticRequest(cOrderingMatrixSizeBytePos);
 
    // prsFS-561; check frame
    //QACJ 3416: akodzhh: There is no side effect; first check request length correctness,then matrix
    //QACJ 3415: akodzhh: There is no side effect; first check request length correctness,then matrix
    if( (mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == u8ExpectedFrameLgth )
      &&( LAPKwpReadDiagnosticRequest(cOrderingMatrixSizeBytePos) > 0 )
      &&( LAPKwpReadDiagnosticRequest(cOrderingMatrixSizeBytePos) <= cOrderingMatrixMaxSize )
      &&((LAPKwpReadDiagnosticRequest(cOrderingMatrixSizeBytePos)&1 ) == 0 )  // even number  
      &&( LAPKwpReadDiagnosticRequest(cSequenceModeBytePos) <= cModeContinueOnErrorTx)
      &&( IsOrderingMatrixDataValid() == cTrue) )
    {
        if( RoutineRequestInProgress[cRoutineIndexAutoTestTOR] != cRoutineInProgress)
        {
            u8SequenceMode           = LAPKwpReadDiagnosticRequest(cSequenceModeBytePos);    
            u8AutoTestSetupTimeOut   = LAPKwpReadDiagnosticRequest(cSetupTimeBytePos);
            u8AutoTestActivTimeOut   = LAPKwpReadDiagnosticRequest(cActivationTimeOutBytePos);
            u8AutoTestSynchroTimeOutIn10msUnit = LAPKwpReadDiagnosticRequest(cSynchronizationTimeOutBytePos);
            u8OrderingMatrixSize     = LAPKwpReadDiagnosticRequest(cOrderingMatrixSizeBytePos);

            for( u8IndexL = 0; u8IndexL < LAPKwpReadDiagnosticRequest(cOrderingMatrixSizeBytePos); u8IndexL++)
            {
                u8OrderingMatrix[u8IndexL]   = LAPKwpReadDiagnosticRequest(cOrderingMatrixBytePos+u8IndexL);
            }
 
            // Init and start AutoTestTor procedure
            u8OrderingMatrixCounter = 0;
            u16ErrorsOnOutput = 0;
            u32ErrorsOnInput  = 0;

            AutoTestTimeOutValueInTick = 
                mTOSConvMsInTimerTick((U32)( LAPKwpReadDiagnosticRequest(cStartDelayIn10msBytePos) * c10MsPerUnit ));
            if(AutoTestTimeOutValueInTick > 0)
            {   
                // -1 tick because of Cm005756:TOS Timers introduce an additional delay of 1 graph/task cycle
                AutoTestTimeOutValueInTick--;
            }
                         
            TOSStartTimer(&AutoTestTimer);
            TOSSeqActivateGraph(cTOSSeqLAPTfcAutoTestIO);

        }
        else  // Routine In Progress
        {   
            u8AnswerStatusL = cLAPKwpConditionNotCorrect;   
        }
    }
    else
    {
        u8AnswerStatusL = cLAPKwpInvalidFormat;
    }

    return(u8AnswerStatusL);

}

//==============================================================================
// DESCRIPTION:         StopAutoTestTOR
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
static MEM_TYPE void StopAutoTestTOR(void)
{
    tTOSSeqGraphStateType  GraphStateL;

    GraphStateL = TOSSeqGraphState(cTOSSeqLAPTfcAutoTestIO);
    //CCOV: akodzhh: can't be covered, StopAutoTestTOR is called when routine is in progress.
    if( GraphStateL == cTOSSeqActiveGraph)
    {
        TOSSeqDeactivateGraph(cTOSSeqLAPTfcAutoTestIO);
        if(bOutputsActivated == cTrue)
        {
            DeactivateOutputs(cFalse);
        }
    }
}

//==============================================================================
// DESCRIPTION:         StartSetupTimeOut
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
void StartSetupTimeOut(void)
{
    AutoTestTimeOutValueInTick = mTOSConvMsInTimerTick((U32)u8AutoTestSetupTimeOut);
    if(AutoTestTimeOutValueInTick > 0)
    {
        // -1 tick because of Cm005756:TOS Timers introduce an additional delay of 1 graph/task cycle
        AutoTestTimeOutValueInTick--;
    }

    TOSStartTimer(&AutoTestTimer);
}

    
//==============================================================================
// DESCRIPTION:         StartSynchronizationTimeout
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
void StartSynchronizationTimeout(void)
{
    AutoTestTimeOutValueInTick = 
        mTOSConvMsInTimerTick((U32)(u8AutoTestSynchroTimeOutIn10msUnit * c10MsPerUnit));

    if(AutoTestTimeOutValueInTick > 0)
    {
        // -1 tick because of Cm005756:TOS Timers introduce an additional delay of 1 graph/task cycle
        AutoTestTimeOutValueInTick--;
    }                                
    
    TOSStartTimer(&AutoTestTimer);


}

//==============================================================================
// DESCRIPTION:         IsTimeoutElapsedOrInputsSet
//
// PARAMETERS:          none
//
// RETURN VALUE:        BOOL
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
BOOL IsTimeoutElapsedOrInputsAreSet(void)
{
    BOOL bIsSynchroTimeoutElapsed;
    BOOL bAllExpectedInputsAreSet;

    // read inputs and input errors
    bAllExpectedInputsAreSet = ReadInputsAndSetResult();
    bIsSynchroTimeoutElapsed = TOSIsTimerElapsed(&AutoTestTimer, AutoTestTimeOutValueInTick);

    return ( bAllExpectedInputsAreSet || bIsSynchroTimeoutElapsed );
}

//==============================================================================
// DESCRIPTION:         FinishSequence
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
void FinishSequence(void)
{
    DeactivateOutputs(cTrue);    
    
    u8OrderingMatrixCounter += cMatrixPairLng;
}


//==============================================================================
// DESCRIPTION:         IsAutoTestFinished
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
BOOL IsAutoTestFinished(void)
{
#ifdef X90_PROJECT
    return IsAutoTestFinished_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL IsAutoTestFinished_Static(void)
{
#endif
    BOOL bStopTestConditions;
    
    if(u8OrderingMatrixCounter >= u8OrderingMatrixSize )
    {
        mLIBassert(u8OrderingMatrixCounter == u8OrderingMatrixSize);
        bStopTestConditions = cTrue;
        if(( u32ErrorsOnInput > (U32)0 ) || ( u16ErrorsOnOutput > (U16)0 ))
        {
            RoutineRequestInProgress[cRoutineIndexAutoTestTOR] = cRoutineTerminatedNOK;
        }
        else
        {
            RoutineRequestInProgress[cRoutineIndexAutoTestTOR] = cRoutineTerminatedOK;
        }
        
    }
    else if( (u8SequenceMode == cModeStopOnError  )
           ||(u8SequenceMode == cModeStopOnErrorTx) )
    {
        bStopTestConditions =  (BOOL)(( u32ErrorsOnInput > (U32)0 ) || ( u16ErrorsOnOutput > (U16)0 ));
        if( bStopTestConditions == cTrue)
        {
            // finished, errors detected
            RoutineRequestInProgress[cRoutineIndexAutoTestTOR] = cRoutineTerminatedNOK;
        }
    }
    else
    {
        bStopTestConditions = cFalse;
    }

    return(bStopTestConditions);

}


//==============================================================================
// DESCRIPTION:         IsSleepTimeoutElapsed
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
BOOL IsSleepTimeoutElapsed(void)
{
    return (BOOL)TOSIsTimerElapsed(&SleepTimer, mTOSConvMsInTimerTick(cTimeoutBeforeEnterSleepInMs));
}
//==============================================================================
// DESCRIPTION:         SleepTimeoutElapsed
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
void SleepTimeoutElapsed(void)
{
    mDATControl(Cpu, Reset);
}


//==============================================================================
// DESCRIPTION:         TreatEepromTest
//
// PARAMETERS:          none
//
// RETURN VALUE:        none 
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
void TreatEepromTest(void)
{
#ifdef X90_PROJECT
    TreatEepromTest_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void TreatEepromTest_Static(void)
{
#endif
    BOOL bReadIsFinished;
    U16  u16CksAddress;
    U8   u8EepBanksListIndex;


    bReadIsFinished = (BOOL)mDATRead(U8Bit,DATDeaActionIsFinished,Default);

    if( bReadIsFinished == cTrue )
    {
        BanksCksTable[u8EepTestCounter].u8BankCksLSB = mDATReadBuffer(DATDeaBufferU8Bit,0, Default);
        BanksCksTable[u8EepTestCounter].u8BankCksMSB = mDATReadBuffer(DATDeaBufferU8Bit,1, Default);
        
        u8EepTestCounter++;
        
        if( u8EepTestCounter < cNbEepBanks )
        {
            // Convert Diag index /u8EepTestCounter/ to Eep bank list index
            u8EepBanksListIndex = BanksCksTable[u8EepTestCounter].u8BankIndex;

            u16CksAddress = EepBanksList[u8EepBanksListIndex].Offset<<1;
            // Set read request
            mDATWrite(U8Bit,  DATDeaSizeBufferInByte, cCksLgth, Default);
            mDATWrite(U16Bit, DATDeaAddressInByte, u16CksAddress, Default);
            mDATControl(DATDea, StartReadEepromByAddress);


        }
        else    // Test finished
        {
            RoutineRequestInProgress[cRoutineIndexEepromTest] = cRoutineTerminatedOK;
            TOSSeqDeactivateGraph(cTOSSeqLAPTfcEepTest);

        }
                    
    }
                  
}
