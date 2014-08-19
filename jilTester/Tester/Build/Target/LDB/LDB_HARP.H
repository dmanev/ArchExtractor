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
// Component:    LDB_HAR
// -----------------------------------------------------------------------------
// $Date:   Feb 26 2010 10:25:22  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_HAR/LDB_HARP.H-arc  $
// $Revision:   1.9  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_HAR/LDB_HARP.H-arc  $
// 
//    Rev 1.9   Feb 26 2010 10:25:22   adzhelp
// Cm007297: Pin for LDB_DOU EEPROM reprogramming changed to P77
// 
//    Rev 1.8   Feb 04 2010 11:54:32   adzhelp
// Cm007297: Pin for LDB_DOU EEPROM reprogramming added
// 
//    Rev 1.7   Jul 15 2009 18:14:26   adzhelp
// Cm005205: LDB_PWM configuration added; Verlog timer sharing with PWM
// 
//    Rev 1.6   Apr 27 2009 10:13:38   adzhelp
// Cm003272: Immobilizer definitions added
// 
//    Rev 1.5   Apr 17 2009 11:31:58   ailievb
// Cm003265:Implementation of the Remote Keyless Entry functionality (Without SDO part)
// Implementation of RF definitions             
// 
//    Rev 1.4   Apr 16 2009 10:22:40   adzhelp
// Cm003276: Sleep tick configuration for Timer H1
// 
//    Rev 1.3   Apr 10 2009 15:29:36   adzhelp
// Cm003264, Cm003271: Definition for LDB_SPD and LDB_ALA added
// 
//    Rev 1.2   Mar 20 2009 14:40:32   adzhelp
// Cm003619: Added definitiions for immobilizer and diagnostics
// 
//    Rev 1.1   Mar 10 2009 15:48:58   adzhelp
// Cm003619: General HW configurations
// 
//    Rev 1.0   10 Nov 2008 15:22:18   ailievb
// Initial revision.
//******************************************************************************

#ifndef I_LDB_HAR_P_H
#define I_LDB_HAR_P_H (1)

/*-------------------------------------------------------------------------
  Included files to resolve specific definitions in this file

  #include <system_file_name.h>
  #include "project_file_name.h"
  -------------------------------------------------------------------------*/

#include "deftypes.h"

/*-------------------------------------------------------------------------
  Constant data

  #define cCMPConstantName   ((tType) ConstantValue)
  -------------------------------------------------------------------------*/

/***********************************************
*  Definition of the clock Frequency
************************************************/
/* Main Clock frequency */
#define cLDBHarMainClockInHz    ((U32)16000000L) // [16 MHz]

/***********************************************
*  Definition of CPU type
************************************************/
/* Define here the used microcontroller */
#define cLDBHarMicro78K0_F0536

/***********************************************
*  Definition of EEPROM pins
************************************************/
#define cLDBHarEepCS       cLDBHarPort13_0 // pin #57
#define cLDBHarSpiSI       cLDBHarPort0_3  // pin #59  // Serial interface CSI11
#define cLDBHarSpiSO       cLDBHarPort0_2  // pin #60
#define cLDBHarSpiSCK      cLDBHarPort0_4  // pin #58

#define cLDBHarEepCsShadow cLDBHarPort7_7  // Used for manufacturing reprogramming input

/***********************************
*  IO configuration
***********************************/
// Example of usage:
//
// mLDBHarConfig(cLDBHarPort0_0, cLDBHarInput);
// mLDBHarWrite(cLDBHarPort0_0, u8Value);
// u8Val = mLDBHarRead(cLDBHarPort0_1);

// Definition of I/O ports for 78K0_F0536
// ==== P0 ====
#define cLDBHarPort0_0  mLDBHarPort(0, 0)
#define cLDBHarPort0_1  mLDBHarPort(0, 1)
#define cLDBHarPort0_2  mLDBHarPort(0, 2)
#define cLDBHarPort0_3  mLDBHarPort(0, 3)
#define cLDBHarPort0_4  mLDBHarPort(0, 4)
#define cLDBHarPort0_5  mLDBHarPort(0, 5)
#define cLDBHarPort0_6  mLDBHarPort(0, 6)
// ==== P1 ====
#define cLDBHarPort1_0  mLDBHarPort(1, 0)
#define cLDBHarPort1_1  mLDBHarPort(1, 1)
#define cLDBHarPort1_2  mLDBHarPort(1, 2)
#define cLDBHarPort1_3  mLDBHarPort(1, 3)
#define cLDBHarPort1_4  mLDBHarPort(1, 4)
#define cLDBHarPort1_5  mLDBHarPort(1, 5)
#define cLDBHarPort1_6  mLDBHarPort(1, 6)
#define cLDBHarPort1_7  mLDBHarPort(1, 7)
// ==== P2 ====
#define cLDBHarPort2_0  mLDBHarPort(2, 0)
#define cLDBHarPort2_1  mLDBHarPort(2, 1)
#define cLDBHarPort2_2  mLDBHarPort(2, 2)
#define cLDBHarPort2_3  mLDBHarPort(2, 3)
#define cLDBHarPort2_4  mLDBHarPort(2, 4)
#define cLDBHarPort2_5  mLDBHarPort(2, 5)
#define cLDBHarPort2_6  mLDBHarPort(2, 6)
#define cLDBHarPort2_7  mLDBHarPort(2, 7)
// ==== P3 ====
#define cLDBHarPort3_0  mLDBHarPort(3, 0)
#define cLDBHarPort3_1  mLDBHarPort(3, 1)
#define cLDBHarPort3_2  mLDBHarPort(3, 2)
#define cLDBHarPort3_3  mLDBHarPort(3, 3)
// ==== P4 ====
#define cLDBHarPort4_0  mLDBHarPort(4, 0)
#define cLDBHarPort4_1  mLDBHarPort(4, 1)
#define cLDBHarPort4_2  mLDBHarPort(4, 2)
#define cLDBHarPort4_3  mLDBHarPort(4, 3)
// ==== P5 ====
#define cLDBHarPort5_0  mLDBHarPort(5, 0)
#define cLDBHarPort5_1  mLDBHarPort(5, 1)
#define cLDBHarPort5_2  mLDBHarPort(5, 2)
#define cLDBHarPort5_3  mLDBHarPort(5, 3)
// ==== P6 ====
#define cLDBHarPort6_0  mLDBHarPort(6, 0)
#define cLDBHarPort6_1  mLDBHarPort(6, 1)
#define cLDBHarPort6_2  mLDBHarPort(6, 2)
#define cLDBHarPort6_3  mLDBHarPort(6, 3)
// ==== P7 ====
#define cLDBHarPort7_0  mLDBHarPort(7, 0)
#define cLDBHarPort7_1  mLDBHarPort(7, 1)
#define cLDBHarPort7_2  mLDBHarPort(7, 2)
#define cLDBHarPort7_3  mLDBHarPort(7, 3)
#define cLDBHarPort7_4  mLDBHarPort(7, 4)
#define cLDBHarPort7_5  mLDBHarPort(7, 5)
#define cLDBHarPort7_6  mLDBHarPort(7, 6)
#define cLDBHarPort7_7  mLDBHarPort(7, 7)
// ==== P12 ====
#define cLDBHarPort12_0  mLDBHarPort(12, 0)
#define cLDBHarPort12_1  mLDBHarPort(12, 1)
#define cLDBHarPort12_2  mLDBHarPort(12, 2)
#define cLDBHarPort12_3  mLDBHarPort(12, 3)
#define cLDBHarPort12_4  mLDBHarPort(12, 4)
// ==== P13 ====
#define cLDBHarPort13_0  mLDBHarPort(13, 0)
// ==== P14 ====
#define cLDBHarPort14_0  mLDBHarPort(14, 0)
#define cLDBHarPort14_1  mLDBHarPort(14, 1)

/***********************************
*  Spi configuration
***********************************/
#define cLDBHarSpiUseUart11  // Serial interface CSI11


/***********************************
*  Eep M93Cx6 definition           *
***********************************/
// Choose EEPROM type:
//#define cLDBHarEep93Type_M93C06
//#define cLDBHarEep93Type_M93C46
//#define cLDBHarEep93Type_M93C56
#define cLDBHarEep93Type_M93C66
//#define cLDBHarEep93Type_M93C76
//#define cLDBHarEep93Type_M93C86

// Choose EEPROM organization:
//#define cLDBHarEep93Org_8Bits
#define cLDBHarEep93Org_16Bits


/***************************
* Analog inputs definition *
***************************/

// Enter here the number of Analog inputs used
#define cNumberAnalog   ((U8)8)

// Definition of the different channels
#define cLDBHarAnaChannel0 ((U8)0)
#define cLDBHarAnaChannel1 ((U8)1)
#define cLDBHarAnaChannel2 ((U8)2)
#define cLDBHarAnaChannel3 ((U8)3)
#define cLDBHarAnaChannel4 ((U8)4)
#define cLDBHarAnaChannel5 ((U8)5)
#define cLDBHarAnaChannel6 ((U8)6)
#define cLDBHarAnaChannel7 ((U8)7)

// Enter in the table the Channel used
#define mListAnalogInputs() \
{ \
    cLDBHarAnaChannel0, \
    cLDBHarAnaChannel1, \
    cLDBHarAnaChannel2, \
    cLDBHarAnaChannel3, \
    cLDBHarAnaChannel4, \
    cLDBHarAnaChannel5, \
    cLDBHarAnaChannel6, \
    cLDBHarAnaChannel7 \
}

/***********************************
*  Tick configuration (LDB_TIM)    *
***********************************/
// System timer (LDB_TIM)
#define cLDBHarRealTimeTimer            TimerH0

// System timer parameters
#define cLDBHarRealTimeTrigger          TriggerH0
#define cLDBHarInterruptRealTimeIt      INTTMH0
// Fh0 = Fprs / 2^10 = 15626 Hz => 64 us tick
#define cLDBHarRealTimeTimerPrescaler   10
#define cLDBHarTickInNsRealTimeTimer    64000UL

// Sleep parameters
#define cLDBHarSleepRealTimeTimer           TimerH1

#define cLDBHarSleepRealTimeTrigger         TriggerH1
#define cLDBHarSleepInterruptRealTimeIt     INTTMH1
// Fh1 = Frl / 2^7 = 1875 Hz => 533.333 us tick
#define cLDBHarSleepRealTimeTimerPrescaler  FRL_7
#define cLDBHarSleepTickInNsRealTimeTimer   533333UL

/***********************************************
*  Definition of BUZZER pins (LDB_BUZ)
************************************************/
#define cLDBHarBuzzerOutput     cLDBHarPort1_7

/***********************************************
*  Definition of IMMOBILIZER pins (LDB_TRP)
************************************************/
// Liaison transpondeur
#define cLDBHarTrpOut           cLDBHarPort0_6
#define cLDBHarTrpIn            cLDBHarPort0_5
// Liaison verlog moteur (ECM)
#define cLDBHarVerlogOut        cLDBHarPort1_5
#define cLDBHarVerlogIn         cLDBHarPort3_0

// Capture timer
#define cLDBHarTrpTimeCaptureTimer                  Timer01
#define cLDBHarSelectClockTrpTimeCaptureTimer       4
#define cLDBHarFreeRunningModeTrpTimeCaptureTimer   CompareAndCapture
#define cLDBHarConfigureTrpTimeCaptureTimer         DisableOutput
#define cLDBHarTickInNsTrpTimeCaptureTimer          ((U32) 1000)

// Timer time out
#define cLDBHarTrpTimeOutTimer                      Timer00
#define cLDBHarSelectClockTrpTimeOutTimer           2
#define cLDBHarTickInNsTrpTimeOutTimer              ((U32)  250)

//PPG output timer
#define cLDBHarTrpTimePPGTimer               Timer01
#define cLDBHarSelectClockTrpPPGTimer        4
#define cLDBHarTrpPPGTimeCompareTimer        CompareAndCompare
#define cLDBHarConfigureTrpTimePPGTimer      EnableOutput
#define cLDBHarTickInNsTrpTimePPGTimer       ((U32) 1000)

// Verlog timer (shared with PWM)
#define cLDBHarTrpVerlogTimer               cLDBHarPwmTimer
#define cLDBHarSelectClockTrpVerlogTimer    cLDBHarPwmTimerPrescaler
#define cLDBHarTickInNsTrpVerlogTimer       cLDBHarTickInNsPwmTimer
#define cLDBHarVerlogTimerPeriodInNs        6150000UL // required by Verlog

// Trigger
#define cLDBHarTrpTimeCaptureTrigger         Trigger01_1
#define cLDBHarTrpTimePPGTriggerM            Trigger01_0
#define cLDBHarTrpTimePPGTriggerN            Trigger01_1
#define cLDBHarTrpTimeOutTrigger             Trigger00_0
#define cLDBHarTrpTimeVerlogTrigger          cLDBHarPwmTimerTrigger

// It
#define cLDBHarInterruptTrpTimeCaptureIt    INTTM011
#define cLDBHarInterruptTrpTimeOutIt        INTTM000
#define cLDBHarInterruptTrpPPGIt            INTTM001 // Shared with LDBRf
#define cLDBHarInterruptTrpVerlogTimerIt    cLDBHarPwmTimerIt // Shared with LDBPwm

#define cLDBHarVerlogLed        cLDBHarPort1_2

/***********************************************
*  DIAGNOSTIC definitions (LDB_KWP)
************************************************/
#define cLDBHarTxKwp            cLDBHarPort1_0
#define cLDBHarRxKwp            cLDBHarPort1_1

// UART
#define cLDBHarUARTKwp          0 // 0 or 6
#define cLDBHarInterruptKwpRx   INTSR0
#define cLDBHarInterruptKwpTx   INTST0 

/***********************************************
*  ALARM definitions (LDB_ALA)
************************************************/
#define cLDBHarAlarmOut     cLDBHarPort1_3
#define cLDBHarAlarmTimer   TimerWTI

#define cLDBHarInterruptAlarmUartTx         INTST6
#define cLDBHarInterruptAlarmTimer          INTWTI

/***********************************************
*  DOORLOCK definitions
************************************************/
// Vehicle speed / engine RPM measurement (LDB_SPD)
// Pins definitions
#define cLDBHarEngineRpmInput               cLDBHarPort14_0

/***********************************************
*  RF definitions             
************************************************/
#define cLDBHarRfStrobe                           cLDBHarPort14_1
#define cLDBHarRfInput                            cLDBHarPort0_0
                                                  
// Timer InputCapture                             
#define cLDBHarRfTimerIC                          Timer00
#define cLDBHarSelectClockRfTimeCaptureTimer      0
#define cLDBHarModeRfTimeCaptureTimer             Capture
#define cLDBHarModeRfTimeDoubleInterval           DoubleInterval
#define cLDBHarTickInNsRfTimerIC                  ((U32)62)   
#define cLDBHarRfTriggerIC                        Trigger00_1
#define cLDBHarRfTriggerIC2                       Trigger00_0
                                                  
// Timer OutputCapture                            
#define cLDBHarRfTimerOC                          Timer01
#define cLDBHarCounterSourceRfTimerOC             0
#define cLDBHarTickInNsRfTimerOC                  ((U32)62)
#define cLDBHarRfTriggerOC                        Trigger01_0
                                                  
// It
#define cLDBHarInterruptRfOCIt                    INTTM001 // Shared with LDBTrp
#define cLDBHarInterruptRfICIt                    INTTM010 // Shared with LDBTrp INTTM010


/***********************************************
*  Interior Lights Configuration (LDB_PWM)
************************************************/
#define cLDBHarILLOutput                cLDBHarPort1_6

// Timer configuration (shared with Verlog)
#define cLDBHarPwmTimer                 TimerH1
#define cLDBHarPwmTimerTrigger          TriggerH1
#define cLDBHarPwmTimerIt               INTTMH1
#define cLDBHarPwmTimerPrescaler        12        // Fh1 = Fprs / 2^12 = 3906.25 Hz => 256 us tick
#define cLDBHarTickInNsPwmTimer         256000UL

#define cLDBHarPwmTimerPeriodInNs       (cLDBHarVerlogTimerPeriodInNs) // To achieve PWM frequency ~162 Hz


/*-------------------------------------------------------------------------
  Exported Macros

  #define mCMPMacroName   (MacroDefinition)
  -------------------------------------------------------------------------*/ 
#define mLDBHarPort(PortNumber, BitNumber)  PortNumber##_bit.no##BitNumber

/*-------------------------------------------------------------------------
  Exported type

  struct  sCMPStructureName { ... };
  union   uCMPUnionName { ... };
  enum    eCMPEnumerationName { ... };
  typedef Expression tCMPTypeName;

  -------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
  Exported data

  extern  tType   CMPVariableName;
  extern  tType*  pCMPVariableName; 
  -------------------------------------------------------------------------*/ 

/*-------------------------------------------------------------------------
  Constant exported data

  extern const tType  CMPVariableName;
  -------------------------------------------------------------------------*/ 

/*-------------------------------------------------------------------------
  Exported functions

  extern tReturnType CMPFunctionName(tTypeArgument1 ArgumentName1, ... );
  -------------------------------------------------------------------------*/ 


#endif   /* I_LDB_HAR_P_H */
