//******************************************************************************
// Company:      Johnson Controls Inc.
// -----------------------------------------------------------------------------
// Copyright:    This software is JCI property.
//               Duplication or disclosure without JCI written authorization
//               is prohibited.
// -----------------------------------------------------------------------------
// Project:      X90_BCM
// Language:     C
// -----------------------------------------------------------------------------
// Component:    LDB_API
// -----------------------------------------------------------------------------
// $Date:   Feb 09 2010 12:18:00  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_API/LDBPARAM.H-arc  $
// $Revision:   1.27  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_API/LDBPARAM.H-arc            $
// 
//    Rev 1.27   Feb 09 2010 12:18:00   adzhelp
// Cm006501: LDB_EEP functions moved to banked area
// 
//    Rev 1.26   Feb 04 2010 11:48:42   adzhelp
// Cm007297: Controls for LDB_DOU EEPROM reprogramming mode added
// 
//    Rev 1.25   Jan 14 2010 14:28:32   adzhelp
// Cm006828: Control cLDBKwpWaitForStartCom added
// 
//    Rev 1.24   Dec 14 2009 11:05:30   amanevd
// Cm005566: Full Hardware Protection
// 
//    Rev 1.23   Nov 17 2009 11:25:42   adzhelp
// Cm006675: LDB_BUZ control / send macros disabled for CPU trace configuration
// 
//    Rev 1.22   Nov 04 2009 16:34:38   amanevd
// Cm005566: Simplified Protection
// 
//    Rev 1.21   Oct 07 2009 09:05:08   adzhelp
// Cm005497: LDB_DOU parameterization
// 
//    Rev 1.20   Sep 28 2009 12:32:34   adzhelp
// Cm005776, Cm005777: 'Extern' keyword added for ALA function - needed by LDBPC
// 
//    Rev 1.19   Sep 25 2009 09:07:08   adzhelp
// Cm005225, Cm004744, Cm003262: Move functions to banked area.
// 
//    Rev 1.18   Aug 27 2009 18:15:06   amanevd
// Cm005466: LDB_TRP QAC and code review fix - inclusion of 'const' qualifiers on interface functions
// 
//    Rev 1.17   Jul 24 2009 14:07:04   amanevd
// Cm005466: LDB_TRP callbacks and control moved to banked memory
// 
//    Rev 1.16   Jul 16 2009 09:20:32   adzhelp
// Cm005205: PWM channel enabled; code review corrections
// 
//    Rev 1.15   Jul 14 2009 10:20:16   adzhelp
// Cm005188: LDB_ALA function moved to banked area
// 
//    Rev 1.14   Jul 13 2009 16:38:48   adzhelp
// Cm005100: LDB_KWP functions moved to banked area
// 
//    Rev 1.13   Apr 27 2009 16:01:16   adzhelp
// Cm003265, Cm003272: Parameterization of RF and TRP channels
// 
//    Rev 1.12   Apr 22 2009 17:35:24   adzhelp
// Cm003265: RF channel enabled
// 
//    Rev 1.11   Apr 17 2009 11:40:24   ailievb
// Cm003265:Implementation of the Remote Keyless Entry functionality (Without SDO part)
// 
//    Rev 1.10   Apr 16 2009 14:24:20   adzhelp
// Cm003276: LDB sleep tick set to 20 ms; channel SUP added; DIN controls added
// 
//    Rev 1.9   Apr 13 2009 15:45:16   adzhelp
// Cm003271: Integration of LDB_ALA channel
// 
//    Rev 1.8   Apr 10 2009 15:20:06   adzhelp
// Cm003264: SPD channel addded
// 
//    Rev 1.7   Apr 07 2009 17:20:02   adzhelp
// Cm003276: Controls for HW layer of LDB_ANA added
// 
//    Rev 1.6   Mar 23 2009 16:57:30   adzhelp
// Cm003619: Added definitions for QAC analysis
// 
//    Rev 1.5   Mar 23 2009 12:34:34   adzhelp
// Cm003465: Channels MOD (simu only) and TRP defined
// 
//    Rev 1.4   Mar 20 2009 16:28:26   adzhelp
// Cm003619: Added definitions for channels KWP, BUZ, ANA, DOU
// 
//    Rev 1.3   06 Feb 2009 11:36:20   adzhelp
// Cm003619: PWM channel enabled
// 
//    Rev 1.2   02 Dec 2009 16:34:26   ailievb
// Cm003619: EEPROM size updated; PWM channel configured
// 
//    Rev 1.1   Nov 12 2008 15:24:20   ailievb
// Cm003619: ANA channel disabled
// 
//    Rev 1.0   Nov 10 2008 14:56:14   ailievb
// Initial revision.
//
//******************************************************************************

#ifndef I_LDBPARAM_H
#define I_LDBPARAM_H (1)


/*-------------------------------------------------------------------------
  Included files to resolve specific definitions in this file

  #include <system_file_name.h>
  #include "project_file_name.h"

#ifndef COMPILATION_NATIVE	// Target specific file name
  #include <system_file_name.h>
  #include "project_file_name.h"
#endif
  -------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------
  Constant data

  #define cCMPConstantName   ((tType) ConstantValue)
  -------------------------------------------------------------------------*/

#define cLDBChannelNbr 17  // Number of channel


// Channel identifier
//#define cLDBCanalXxx  ((tChannel)0UL)

#define cLDBChannelEep   ((tChannel)0UL)

#define cLDBChannelKwp   ((tChannel)1UL)

#define cLDBChannelBuz   ((tChannel)2UL)

#define cLDBChannelAna   ((tChannel)5UL)

#define cLDBChannelPwm   ((tChannel)6UL)

#define cLDBChannelDin   ((tChannel)7UL)

#define cLDBChannelDou   ((tChannel)8UL)

#ifdef cLIBStkFla_Used
#define cLDBChannelFla   ((tChannel)9UL)
#else
//#define cLDBChannelFla   ((tChannel)9UL)
#endif

#define cLDBChannelAla   ((tChannel)10UL)

#define cLDBChannelSpd   ((tChannel)11UL)

#define cLDBChannelTrp    ((tChannel)12UL)

#define cLDBChannelRf     ((tChannel)13UL)

#define cLDBChannelSup   ((tChannel)14UL)

#ifdef cLIBStkLoc_Used
#define cLDBChannelLoc     ((tChannel)15UL)
#else
//#define cLDBChannelLoc   ((tChannel)15UL)
#endif

#ifdef COMPILATION_NATIVE // MOD channel used only in simulation
#define cLDBChannelMod      ((tChannel)16UL)
#endif

#ifdef _QAC_
// Disable compiler extensions
#define __root
#define __interrupt
#define __no_init
#endif

/*-------------------------------------------------------------------------
    LDB Timer Management
  -------------------------------------------------------------------------*/
#ifdef COMPILATION_NATIVE
  #define cLDBTick            ((U32)1000L)       // Duration in nanosecond
  #define cLDBSleepTick       ((U32)1000L)       // Duration in nanosecond
#else
  #define cLDBTick            ((U32) 2500000L)   // Duration in nanosecond                                
  #define cLDBSleepTick       ((U32)20000000L)   // Duration in nanosecond
#endif

#define cLDBTimerNbr        ((U8)5UL)           // Number of timers

// Tempo identifier
#define cLDBTimer1      ((tTimerRef)0x00U)
#define cLDBTimer2      ((tTimerRef)0x01U)
#define cLDBTimer3      ((tTimerRef)0x02U)
#define cLDBTimer4      ((tTimerRef)0x03U)
#define cLDBTimer5      ((tTimerRef)0x04U)


/*-------------------------------------------------------------------------
    Channel Xxx
  -------------------------------------------------------------------------*/
//#ifdef cLDBCanalXxx
// -- LDB or DAT Controls --
//#define cLDBXxxCtrlName	((tCtrl)0x00)
//#endif // cLDBCanalXxx

// --------------------------------------------------------------
//     Channel Fla
// --------------------------------------------------------------
#ifdef cLDBChannelFla

// -- DAT Controls --
// Controls Value for FLASH Locking\Unlocking

// FLASH lock control value
#define cLDBFlaLock   ((tCtrl)0x00U)
// FLASH unlock control value
#define cLDBFlaUnlock ((tCtrl)0x01U)

//FLASH Erase control value
#define cLDBFlaErasePage0 ((tCtrl)0x03U)
#define cLDBFlaErasePage1 ((tCtrl)0x04U)

// FLASH Size
#define cLDBFlaSize       0x0800U

#endif // cLDBChannelFla

// --------------------------------------------------------------
//     Channel Eep
// --------------------------------------------------------------
#ifdef cLDBChannelEep

// LDB status codes for EEP
#define cLDBEepControlInProgress       (cLDBCorrect + 1U)

// -- Controls --
// Controls Value for EEPROM Locking\Unlocking

// EEPROM lock control value
#define cLDBEepLock   ((tCtrl)0x00U)
// EEPROM unlock control value
#define cLDBEepUnLock ((tCtrl)0x01U)
// EEPROM check the completion of the write command
#define cLDBEepCheckWriteCompletion ((tCtrl)0x02U)

// EEPROM Size
#define cLDBEepSize       0x0200U

#endif // cLDBChannelEep

// --------------------------------------------------------------
//     Channel Kwp
// --------------------------------------------------------------
#ifdef cLDBChannelKwp

// -- LDB Controls --
#define cLDBKwpWaitForWakeUp          ((tCtrl)0x00)

// -- DAT Controls --
#define cLDBKwpEnableRx               ((tCtrl)0x01)
#define cLDBKwpDisableRx              ((tCtrl)0x02)
#define cLDBKwpWakeUp                 ((tCtrl)0x03)
#define cLDBKwpWaitForStartCom        ((tCtrl)0x04)

#endif // cLDBChannelKwp


// --------------------------------------------------------------
//     Channel Can
// --------------------------------------------------------------
#ifdef cLDBChannelCan0
    #define CANAL_CAN_EXISTS
#else
  #ifdef cLDBChannelCan1
      #define CANAL_CAN_EXISTS
  #else
    #ifdef cLDBChannelCan
        #define CANAL_CAN_EXISTS
    #endif
  #endif
#endif

#ifdef CANAL_CAN_EXISTS

// -- LDB Controls --
// Bus Off Signal input controller
#define cLDBCanBusOff               ((tCtrl)0x00U)
// Bus On Signal input controller
#define cLDBCanBusOn                ((tCtrl)0x01U)
// passive error
#define cLDBCanPassiveError         ((tCtrl)0x02U)
// Wake up received
#define cLDBCanWakeUp               ((tCtrl)0x03U)
// NERR physical CAN layer defect is not present
#define cLDBCanNerrOff              ((tCtrl)0x04U)
// NERR physical CAN layer defect is present
#define cLDBCanNerrOn               ((tCtrl)0x05U)


// -- DAT Controls --
// Can cell auto diagnostic
#define cLDBCanSelfDiag          ((tCtrl)0x07U)
// Reset the controller
#define cLDBCanInit              ((tCtrl)0x08U)
// Start Hardware Layer
#define cLDBCanStart             ((tCtrl)0x09U)
// Stop Hardware Layer
#define cLDBCanStop              ((tCtrl)0x0AU)

// Wake up authorization control
#define cLDBCanAutoriserCtrlWakeUp  ((tCtrl)0x0BU)

// Cancel Transmission in progress
#define cLDBCanCancelTransmissionInProgress  ((tCtrl)0x0CU)

// Can reception interrupt authorization
#define cLDBCanEnableRxCallBack  ((tCtrl)0x0DU)
// Can reception interrupt banning
#define cLDBCanDisableRxCallBack  ((tCtrl)0x0EU)

#endif // CANAL_CAN_EXISTS

// --------------------------------------------------------------
//     Channel Ana
// --------------------------------------------------------------
#ifdef cLDBChannelAna
#ifdef COMPILATION_NATIVE
//mandatory for ECAR simulation
// Start Hardware Layer
#define cLDBAnaStart             ((tCtrl)0x00U)
// Stop Hardware Layer
#define cLDBAnaStop              ((tCtrl)0x01U)
#else
// Start Hardware Layer
#define cLDBAnaStartHW           ((tCtrl)0x00U)
// Stop Hardware Layer
#define cLDBAnaStopHW            ((tCtrl)0x01U)
#endif

//If the LDB_ANA is synchronous active this compilation option
//i.e LDB_ANA keep the focus during tha analog conversion,
// it doesn't work with interrupts

#define cLDB_ANAIsSynchronous

#endif // cLDBChannelAna

// --------------------------------------------------------------
//     Channel Pwm
// --------------------------------------------------------------
#ifdef cLDBChannelPwm

// Controls
#define  cLDBPwmStart           ((tCtrl)0x00)
#define  cLDBPwmStop            ((tCtrl)0x01)

// Addresses
#define cLDBPwmAddrRoomLamp1    ((tAddress)0x00)

#endif // cLDBChannelPwm

// --------------------------------------------------------------
//     Channel Dou
// --------------------------------------------------------------
#ifdef cLDBChannelDou

// Controls
#define cLDBDouEnterNominalMode             ((tCtrl)0x01U)
#define cLDBDouEnterSleepMode               ((tCtrl)0x02U)
#define cLDBControlSetDO_DATA_IMMOBILIZER   ((tCtrl)0x03U)
#define cLDBControlClearDO_DATA_IMMOBILIZER ((tCtrl)0x04U)
#define cLDBControlSetDO_VERLOG             ((tCtrl)0x05U)
#define cLDBControlClearDO_VERLOG           ((tCtrl)0x06U)
#define cLDBDouEnableOPEN_DOOR_LED          ((tCtrl)0x07U)
#define cLDBDouDisableOPEN_DOOR_LED         ((tCtrl)0x08U)
#define cLDBControlSetVERLOG_LED            ((tCtrl)0x09U)
#define cLDBControlClearVERLOG_LED          ((tCtrl)0x0AU)
#define cLDBControlCheckDO_VERLOGSCDetect   ((tCtrl)0x0BU)
#define cLDBControlCheckDO_VERLOGSCGnd      ((tCtrl)0x0CU)
#define cLDBControlCheckDO_VERLOGSCBat      ((tCtrl)0x0DU)
#define cLDBDouPrepareEepromReprog          ((tCtrl)0x0EU)
#define cLDBDouStartEepromReprog            ((tCtrl)0x0FU)
// ECU Type
#define cLDBDouSetEcuType0                  ((tCtrl)0x10U)
#define cLDBDouSetEcuType1                  ((tCtrl)(cLDBDouSetEcuType0 + (tCtrl)1U))
#define cLDBDouSetEcuType2                  ((tCtrl)(cLDBDouSetEcuType0 + (tCtrl)2U))
#define cLDBDouSetEcuType3                  ((tCtrl)(cLDBDouSetEcuType0 + (tCtrl)3U))
#define cLDBDouSetEcuType4                  ((tCtrl)(cLDBDouSetEcuType0 + (tCtrl)4U))
#define cLDBDouSetEcuType5                  ((tCtrl)(cLDBDouSetEcuType0 + (tCtrl)5U))
#define cLDBDouSetEcuType6                  ((tCtrl)(cLDBDouSetEcuType0 + (tCtrl)6U))
#define cLDBDouSetEcuType7                  ((tCtrl)(cLDBDouSetEcuType0 + (tCtrl)7U))

#endif // cLDBChannelDou

// --------------------------------------------------------------
//     Channel Din
// --------------------------------------------------------------
#ifdef cLDBChannelDin

// -- DAT Controls --
#define cLDBDinEnterNominalMode         ((tCtrl)0x01U)
#define cLDBDinEnterSleepMode           ((tCtrl)0x02U)
#define cLDBDinEnableWakeUpInterrupt    ((tCtrl)0x03U)
#define cLDBDinCheckKLineWakeupConditions \
                                        ((tCtrl)0x04U)
#define cLDBDinInitiateKLineWakeupConditions \
                                        ((tCtrl)0x05U)

// DAT_PIN
#define cLDBPinWakeUpRequested          ((tCtrl)0x05U)

// -- LDB Controls --
#define cLDBDinWakeUp                   ((tCtrl)0x04U)

#endif // cLDBChannelDin

// --------------------------------------------------------------
//     Channel LIN Master
// --------------------------------------------------------------
#ifdef cLDBChannelLinM

// Initiated controls
#define cLDBLinMCancelRxWithAddr ((tCtrl)0UL)
// Put the LDB in nominal mode
#define cLDBLinMStop            ((tCtrl)1UL)
// stop the LDB
#define cLDBLinMStart           ((tCtrl)2UL)
// Wake up LIN bus request
#define cLDBLinMWake            ((tCtrl)3UL)

// Non Initiated
// LDB signal the detection of a Wake up pattern with this control
#define cLDBLinMWakeUp          ((tCtrl)4UL)

// Status
#define cLDBLinMOk              (cLDBCorrect)
#define cLDBLinMError           (cLDBError)
#define cLDBLinMHeaderError     ((tStatus)2UL) //Error during master frame header transmission

#endif // cLDBChannelLinM

// --------------------------------------------------------------
//     Channel LIN Slave
// --------------------------------------------------------------
#ifdef cLDBChannelLinS

//Status
#define cLDBLinSOk       (cLDBCorrect)
#define cLDBLinSError    (cLDBError)

// ctrl for ldbcontrol
#define cLDBLinSStop    ((tCtrl)0UL)
#define cLDBLinSStart   ((tCtrl)1UL)
#define cLDBLinSWake    ((tCtrl)2UL)
#define cLDBLinSEnableCommandFrameResponse  ((tCtrl)3UL)

// ctrl for callback
#define cLDBLinSWakeUp  ((tCtrl)4UL)
#define cLDBLinSSynch   ((tCtrl)5UL)

#endif // cLDBChannelLinS

// --------------------------------------------------------------
//     Channel Trp
// --------------------------------------------------------------
#ifdef cLDBChannelTrp

// ctrl for ldbcontrol
#define cLDBTrpWakeUp               ((tCtrl)0UL)
#define cLDBTrpSleep                ((tCtrl)1UL)
#define cLDBTrpStop                 ((tCtrl)2UL)
#define cLDBTrpEnterNominalMode     ((tCtrl)3UL)
#define cLDBTrpEnterSleepMode       ((tCtrl)4UL)
#define cLDBTrpStopVerlog           ((tCtrl)5UL)

// ctrl for hardware defaults detection
#define cLDBTrpLinkError          ((tCtrl)6UL)
#define cLDBTrpDataError          ((tCtrl)7UL)
#define cLDBTrpShortCircuitToBat  ((tCtrl)8UL)
#define cLDBTrpShortCircuitToGnd  ((tCtrl)9UL)
#define cLDBTrpNoError            ((tCtrl)10UL)

// transponder commands
#define cLDBTrpStartAuth ((tAddress) 0x0018U)
#define cLDBTrpRdPage    ((tAddress) 0x0018U)
#define cLDBTrpRdPageInv ((tAddress) 0x0008U)
#define cLDBTrpRdSync    ((tAddress) 0x0117U)
#define cLDBTrpResync    ((tAddress) 0x020FU)
#define cLDBTrpWrPage    ((tAddress) 0x0010U)

#endif // cLDBChannelTrp

// --------------------------------------------------------------
//     Channel RF
// --------------------------------------------------------------
#ifdef cLDBChannelRf

#define    cLDBRfSearchFrame        ((tCtrl)0x00U)
#define    cLDBRfStop               ((tCtrl)0x01U)
#define    cLDBRfWakeUpReceived     ((tCtrl)0x02U)
#define    cLDBRfWakeUpNotReceived  ((tCtrl)0x03U)
#define    cLDBRfActivateStrobe     ((tCtrl)0x04U)
#define    cLDBRfDeactivateStrobe   ((tCtrl)0x05U)
#define    cLDBRfControlSleepTick   ((tCtrl)0x06U)
#define    cLDBRfEnterNominalMode   ((tCtrl)0x07U)
#define    cLDBRfEnterSleepMode     ((tCtrl)0x08U)

#define    cLDBRfDecrementTempoSearchFrame  ((tCtrl)0x09U)

#endif // cLDBChannelRf

// --------------------------------------------------------------
//     Channel Mot
// --------------------------------------------------------------
#ifdef cLDBChannelMot

// -- DAT Controls --
//Keep old control value for compatibility
#define cLDBMotStartCalibration           ((tCtrl)0x02U)

#define cLDBMotStart                      ((tCtrl)0x00U)
#define cLDBMotStop                       ((tCtrl)0x01U)
#define cLDBMotStartLowCalibration        ((tCtrl)0x02U)
#define cLDBMotStartHighCalibration       ((tCtrl)0x03U)
#define cLDBMotStartReturnInMicrosteps    ((tCtrl)0x04U)
#define cLDBMotStopReturnInMicrosteps     ((tCtrl)0x05U)
#define cLDBMotStartMotorsInHZ            ((tCtrl)0x06U)
#define cLDBMotStopMotorsInHZ             ((tCtrl)0x07U)
#define cLDBMotStartWOWSession            ((tCtrl)0x08U)
#define cLDBMotStopWOWSession             ((tCtrl)0x09U)
#define cLDBMotNormalVoltage              ((tCtrl)0x0AU)  
#define cLDBMotAbnormalVoltage            ((tCtrl)0x0BU)


// -- DAT Emission Addresses --         
#define cLDBMotSetPointAddr               ((tAddress)0x00U)
#define cLDBMotSetPointInMicrostepsAddr   ((tAddress)0x01U)
#define cLDBMotJumpInMicrostepsAddr       ((tAddress)0x02U)
#define cLDBMotInitMagOffsetAddr          ((tAddress)0x03U)
#define cLDBMotInitSoftZeroAddr           ((tAddress)0x04U)
#define cLDBMotSetCalibrationValueAddr    ((tAddress)0x05U)                                        
#define cLDBMotTorqueValueAddr            ((tAddress)0x06U)
#define cLDBMotSetWOWSpeed                ((tAddress)0x07U)
#define cLDBMotSetCalibInMicrostepsAddr   ((tAddress)0x08U)
#define cLDBMotPositionsValuesInMicrostepsAddr ((tAddress)0x09U)

// -- DAT Reception Addresses --        
#define cLDBMotPositionsReachedAddr       ((tAddress)0x00U)
#define cLDBMotPositionsValuesAddr        ((tAddress)0x01U)
#define cLDBMotCalibrationProcessingAddr  ((tAddress)0x02U)

// -- LDB Constants --
#define cLDBMotHighCalibrationCode        ((U8) 0xFFU)
#define cLDBMotLowCalibrationCode         ((U8) 0xFEU)

#endif // cLDBChannelMot

// --------------------------------------------------------------
//     Channel Dfa
// --------------------------------------------------------------
#ifdef cLDBChannelDfa

#define	LDB_DFA_USE_INTERNAL_VERIFY
#define	LDB_DFA_USE_BLANK_CHECK_BY_SECTOR

// -- DAT Controls --
#define cLDBDfaStatusCheck		((tCtrl)0x00U)

#ifdef	LDB_DFA_USE_WRITE_ERASE_PROTECTION
// Controls Value for Flash SectorID writing and/or erasing protection.
// cLDBDfaProtectSectorID value is equal to Sector Number + 0x10
#define cLDBDfaProtectSector0		((tCtrl)0x10U)
#define cLDBDfaProtectSector1		((tCtrl)0x11U)
#define cLDBDfaProtectSector2		((tCtrl)0x12U)
#define cLDBDfaProtectSector3		((tCtrl)0x13U)
#define cLDBDfaProtectSector4		((tCtrl)0x14U)
#define cLDBDfaProtectSector5		((tCtrl)0x15U)
#define cLDBDfaProtectSector6		((tCtrl)0x16U)
#define cLDBDfaProtectSector7		((tCtrl)0x17U)
#define cLDBDfaProtectSector8		((tCtrl)0x18U)
#define cLDBDfaProtectSector9		((tCtrl)0x19U)
#define cLDBDfaProtectSector10		((tCtrl)0x1AU)
#define cLDBDfaProtectSector11		((tCtrl)0x1BU)
#define cLDBDfaProtectSector12		((tCtrl)0x1CU)
#define cLDBDfaProtectSector13		((tCtrl)0x1DU)
#define cLDBDfaProtectSector14		((tCtrl)0x1EU)
#define cLDBDfaProtectSector15		((tCtrl)0x1FU)

// Controls Value for Flash SectorID writing and/or erasing unprotection.
// cLDBDfaUnprotectSectorID value is equal to cLDBDfaProtectSectorID max value 	+1
#define cLDBDfaUnprotectSector0		((tCtrl)0x20U)
#define cLDBDfaUnprotectSector1		((tCtrl)0x21U)
#define cLDBDfaUnprotectSector2		((tCtrl)0x22U)
#define cLDBDfaUnprotectSector3		((tCtrl)0x23U)
#define cLDBDfaUnprotectSector4		((tCtrl)0x24U)
#define cLDBDfaUnprotectSector5		((tCtrl)0x25U)
#define cLDBDfaUnprotectSector6		((tCtrl)0x26U)
#define cLDBDfaUnprotectSector7		((tCtrl)0x27U)
#define cLDBDfaUnprotectSector8		((tCtrl)0x28U)
#define cLDBDfaUnprotectSector9		((tCtrl)0x29U)
#define cLDBDfaUnprotectSector10	((tCtrl)0x2AU)
#define cLDBDfaUnprotectSector11	((tCtrl)0x2BU)
#define cLDBDfaUnprotectSector12	((tCtrl)0x2CU)
#define cLDBDfaUnprotectSector13	((tCtrl)0x2DU)
#define cLDBDfaUnprotectSector14	((tCtrl)0x2EU)
#define cLDBDfaUnprotectSector15	((tCtrl)0x2FU)

#endif // LDB_DFA_USE_WRITE_ERASE_PROTECTION


// -- DAT Commands --
#define cLDBDfaIdle			((tCtrl)0x00U)
#define cLDBDfaErase			((tCtrl)0x01U)
#define cLDBDfaRead			((tCtrl)0x02U)
#define cLDBDfaWrite			((tCtrl)0x03U)
#define cLDBDfaCheckBlankFw		((tCtrl)0x04U)

#if (defined (LDB_DFA_USE_BLANK_CHECK_BY_SECTOR))
	#define cLDBDfaCheckBlankBw		((tCtrl)0x05U)
#endif

#if (defined (LDB_DFA_USE_INTERNAL_VERIFY))
	#define cLDBDfaIVerify		((tCtrl)0x06U)
#endif

// -- DAT Status --
//		LDBDfaCfgData .Status contains blank check status:
#define cLDBDfaBlank		((tCtrl)0x00U)
							// The address part does not contain valid data.
#define cLDBDfaNotBlank		((tCtrl)0x01U)
							// Buffer[0] - Buffer[3] contain first non blank address.
typedef struct
{
    U32                u32BeginAddress;
    U32                u32EndAddress;
    U8                 u8Command;
    U8                 u8Status;
	U8*                pBuffer; 
} tLDBDfaCfgData;

#define cLDBInProgress     ((tStatus)0x02U)    // the before requested operation
											   // is not finished yet
#define cLDBInvalid        ((tStatus)0xFFU)    // Invalid Control Status

#endif // cLDBChannelDfa

// --------------------------------------------------------------
//     Channel BUZ
// --------------------------------------------------------------
#ifdef cLDBChannelBuz

//buz controls
#define cLDBBuzEnable           ((tCtrl)0x00U)
#define cLDBBuzDisable          ((tCtrl)0x01U)
#define cLDBBuzStartSound       ((tCtrl)0x02U)
#define cLDBBuzCancelSound      ((tCtrl)0x03U)

#endif // cLDBChannelBuz

// --------------------------------------------------------------
//     Channel SPD
// --------------------------------------------------------------
#ifdef cLDBChannelSpd

// SPD controls
#define cLDBSpdControlStart         ((tCtrl)0x01U)
#define cLDBSpdControlStop          ((tCtrl)0x02U)
// SPD addresses
#define cLDBSpdAddrVehicleSpeed     ((tAddress)0x01U)
#define cLDBSpdAddrEngineRpm        ((tAddress)0x02U)

// Values
// Message parameters
#define cLDBSpdMessageLength        2U
#define cLDBSpdVehicleSpeedIndex    0U
#define cLDBSpdEngineRpmIndex       1U
// Engine RPM status
#define cLDBSpdEngineNotRunning     ((U8)0x00U)
#define cLDBSpdEngineRunning        ((U8)0x01U)

#endif // cLDBChannelSpd

// --------------------------------------------------------------
//     Channel SUP
// --------------------------------------------------------------
#ifdef cLDBChannelSup

// SUP controls
#define cLDBSupWakeUpDetectionPinStarted    ((tCtrl)0x01U)
#define cLDBSupSynchronizeSleepTimer        ((tCtrl)0x02U)

// Values
// Message parameters
#define cLDBSupMessageLength                    2U
#define cLDBSupClockForActiveModeSelectedIndex  0U
#define cLDBSupAnalogConversionAllowedIndex     1U

#endif // cLDBChannelSup

/*-------------------------------------------------------------------------
  Exported Macro

  #define mCMPMacroName   (MacroDefinition)
  -------------------------------------------------------------------------*/ 

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
#ifdef COMPILATION_NATIVE

// Simulate the processing time of series of operations
// Dont call directly this function
// a macro is defined to use it
extern void LDBSimulerTempsTraitement(tDelay TempsEnMicroSecondes);
extern void LDBPcTrace(char* Texte);

#endif // COMILATION_NATIVE

//---------------------- Channel Functions Callback ----------------------

// --------------------------------------------------------------
//      Definition of Xxx Callback channel (with address)
// --------------------------------------------------------------
#ifdef cLDBCanalXxx

extern void    DATXxxCallBackEndCtrl    (tCtrl,    tStatus);
extern void    DATXxxCallBackCtrl       (tCtrl);
extern void    DATXxxCallBackTxWithAddr (tAddress, tStatus);
extern void    DATXxxCallBackRxWithAddr (tAddress, tStatus);
extern const   tRxSpontWithAddr          DATXxxRxSpontTable[];
extern const   U16                   DATXxxRxSpontNbr;

#endif // cLDBCanalXxx

// --------------------------------------------------------------
//      Definition of Yyy Callback channel (without address)
// --------------------------------------------------------------
#ifdef cLDBCanalYyy

extern void    DATYyyCallBackRxWithoutAddr(tStatus);
extern void    DATYyyCallBackTxWithoutAddr(tStatus);

#endif // cLDBCanalYyy

// --------------------------------------------------------------
//      Definition of Eep Callback channel (with address)
// --------------------------------------------------------------
#ifdef cLDBChannelEep

extern void    DATEepCallBackEndCtrl   (tCtrl,    tStatus);
extern void    DATEepCallBackTxWithAddr(tAddress, tStatus);
extern void    DATEepCallBackRxWithAddr(tAddress, tStatus);

#endif // cLDBChannelEep

// --------------------------------------------------------------
//      Definition of Kwp Callback channel (with address)
// --------------------------------------------------------------
#ifdef cLDBChannelKwp

extern void    DATKwpCallBackRxSpontWithoutAddr (tStatus,tMsg*);
extern void    DATKwpCallBackCtrl(tCtrl);
extern void    DATKwpCallBackEndCtrl(tCtrl,tStatus);
extern void    DATKwpCallBackTxWithoutAddr(tStatus);

#endif // cLDBChannelKwp

// --------------------------------------------------------------
//      Definition of Can Callback channel (with address)
// --------------------------------------------------------------

#ifdef cLDBChannelCan

extern void    DATCanCallBackEndCtrl   (tCtrl, tStatus);
extern void    DATCanCallBackCtrl      (tCtrl);
extern void    DATCanCallBackTxWithAddr(tAddress, tStatus);
extern const   tRxSpontWithAddr        DATCanRxSpontTable[];
extern const   U16                     DATCanRxSpontNbr;

#endif // cLDBChannelCan

// channel 0
#ifdef cLDBChannelCan0

extern void    DATCan0CallBackEndCtrl   (tCtrl, tStatus);
extern void    DATCan0CallBackCtrl      (tCtrl);
extern void    DATCan0CallBackTxWithAddr(tAddress, tStatus);
extern const   tRxSpontWithAddr         DATCan0RxSpontTable[];
extern const   U16                      DATCan0RxSpontNbr;

#endif // cLDBChannelCan0

// channel 1
#ifdef cLDBChannelCan1

extern void    DATCan1CallBackEndCtrl   (tCtrl, tStatus);
extern void    DATCan1CallBackCtrl      (tCtrl);
extern void    DATCan1CallBackTxWithAddr(tAddress, tStatus);
extern const   tRxSpontWithAddr         DATCan1RxSpontTable[];
extern const   U16                      DATCan1RxSpontNbr;

#endif // cLDBChannelCan1



// --------------------------------------------------------------
//      Definition of Ana Callback channel (without address)
// --------------------------------------------------------------
#ifdef cLDBChannelAna

extern void    DATAnaCallBackRxWithoutAddr(tStatus);
extern void    DATAnaCallBackEndCtrl      (tCtrl,tStatus);

#endif // cLDBChannelAna

// --------------------------------------------------------------
//      Definition of Pwm Callback channel (without address)
// --------------------------------------------------------------
#ifdef cLDBChannelPwm

extern void    DATPwmCallBackTxWithAddr(const tAddress, const tStatus);


#endif // cLDBChannelPwm

// --------------------------------------------------------------
//      Definition of Ent Callback channel (without address)
// --------------------------------------------------------------
#ifdef cLDBChannelDin

extern void    DATDinCallBackRxWithoutAddr(tStatus);
extern void    DATDinCallBackEndCtrl      (tCtrl,tStatus);
extern void    DATDinCallBackCtrl         (tCtrl);

extern void    DATPinCallBackCtrl         (const tCtrl);

#endif // cLDBChannelDin

// --------------------------------------------------------------
//		Definition of Sor Callback channel (without address)
// --------------------------------------------------------------
#ifdef cLDBChannelDou

extern void    DATDouCallBackTxWithoutAddr(tStatus);
extern void    DATDouCallBackEndCtrl	  (tCtrl,tStatus);

#endif // cLDBChannelDou

// --------------------------------------------------------------
//		Definition of Fla Callback channel (without address)
// --------------------------------------------------------------
#ifdef cLDBChannelFla

extern void DATFlaCallBackEndCtrl   (tCtrl Unused, tStatus Status);
extern void DATFlaCallBackTxWithAddr(tAddress Unused, tStatus Status);

#endif // cLDBChannelFla

// --------------------------------------------------------------
//      Definition of Lin Master Callback channel (with address)
// --------------------------------------------------------------
#ifdef cLDBChannelLinM

extern void DATLinMCallBackRxWithAddr(tAddress Address,tStatus Status);
extern void DATLinMCallBackTxWithAddr(tAddress Address,tStatus Status);
extern void DATLinMCallBackEndCtrl   (tCtrl Ctrl,tStatus Status);
extern void DATLinMCallBackCtrl      (tCtrl Ctrl);

#endif

// --------------------------------------------------------------
//      Definition of Lin Slave Callback channel (with address)
// --------------------------------------------------------------
#ifdef cLDBChannelLinS

extern void DATLinSCallBackRxSpontWithIdx(U8 Index,tStatus Status,tMsg * pMsg);
extern void DATLinSCallBackEndCtrl       (tCtrl Ctrl,tStatus Status);
extern void DATLinSCallBackTxSpontWithIdx(U8 Index,tStatus Status);
extern void DATLinSCallBackCtrl          (tCtrl Ctrl);

extern const tTxSpontWithIdx DATLinSTxSpontTableWithIdx [];
extern const tRxSpontWithIdx DATLinSRxSpontTableWithIdx [];
extern const U8          DATLinSNumberOfRxFrame;
extern const U8          DATLinSNumberOfTxFrame;

#endif

// --------------------------------------------------------------
//      Definition of Trp Callback channel
// --------------------------------------------------------------
#ifdef cLDBChannelTrp

extern MEM_TYPE void DATTrpCallBackCtrl         (tCtrl);
extern MEM_TYPE void DATTrpCallBackEndCtrl      (tCtrl,    tStatus);
extern MEM_TYPE void DATTrpCallBackTxWithAddr   (tAddress, tStatus);
extern MEM_TYPE void DATTrpCallBackRxWithAddr   (tAddress, tStatus);
extern MEM_TYPE void DATTrpCallBackRxSpontWithoutAddr   (tStatus,  tMsg*);
extern void DATVlgCallBackCtrl                  (void);
extern MEM_TYPE void DATVlgCallBackEndCtrl      (const tCtrl, const tStatus);
#endif // cLDBChannelTrp

// --------------------------------------------------------------
//      Definition of Rf Callback channel
// --------------------------------------------------------------
#ifdef cLDBChannelRf

extern void DATRfCallBackEndCtrl(tCtrl, tStatus);
extern void DATRfCallBackCtrl   (tCtrl);
extern const tRxSpontWithAddr DATRfRxSpontTable[];

#endif // cLDBChannelRf

// --------------------------------------------------------------
//		Definition of Loc Callback channel (without address)
// --------------------------------------------------------------
#ifdef cLDBChannelLoc
extern void   DATLocCallBackRxWithoutAddr (tStatus);
extern void   DATLocCallBackTxWithoutAddr (tStatus);
#endif // cLDBChannelLoc

// --------------------------------------------------------------
//      Definition of Dfa Callback channel (without address)
// --------------------------------------------------------------
#ifdef cLDBChannelDfa

extern void   DATFrlCallBackEndCtrl   (const tCtrl, const tStatus);
extern void   DATFrlCallBackRxWithoutAddr (const tStatus Status);
extern void   DATFrlCallBackTxWithoutAddr (const tStatus Status);

#endif // cLDBChannelDfa

// --------------------------------------------------------------
//      Definition of ALA Callback channel (without address)
// --------------------------------------------------------------
#ifdef cLDBChannelAla 

extern void DATAlaCallBackTxWithoutAddr(tStatus Status);

#endif // cLDBChannelAla 

// --------------------------------------------------------------
//      Definition of LDB Macro Services
// --------------------------------------------------------------

#ifdef LDB_MACRO_SERVICES

// --------------------------------------------------------------
//      Definition of cLDBChannelEep Macro Services
// --------------------------------------------------------------

#ifdef cLDBChannelEep

extern MEM_TYPE void LDBEepSendWithAddr  (tAddress Ad, tMsg* Msg );
extern MEM_TYPE void LDBEepReceiveWithAddr(tAddress Ad, tMsg* Msg );
extern MEM_TYPE void LDBEepControl       (tCtrl    Ctrl);

#define mLDBSendWithAddrcLDBChannelEep(Ad,Msg)   LDBEepSendWithAddr  (Ad,Msg)
#define mLDBReceiveWithAddrcLDBChannelEep(Ad,Msg) LDBEepReceiveWithAddr(Ad,Msg)
#define mLDBControlcLDBChannelEep( Ctrl)         LDBEepControl       (Ctrl)

#endif

// --------------------------------------------------------------
//      Definition of cLDBChannelKwp Macro Services
// --------------------------------------------------------------
#ifdef cLDBChannelKwp

extern MEM_TYPE void LDBKwpSendWithoutAddr(tMsg* Msg );
extern MEM_TYPE void LDBKwpControl       (tCtrl    Ctrl);
extern MEM_TYPE void LDBKwpEnableCallBack(BOOL CallBackEnabled );

#define mLDBSendWithoutAddrcLDBChannelKwp(Msg)            LDBKwpSendWithoutAddr  ( Msg )
#define mLDBControlcLDBChannelKwp(Ctrl)                   LDBKwpControl       ( Ctrl )
#define mLDBEnableCallBackcLDBChannelKwp(CallBackEnabled) LDBKwpEnableCallBack( CallBackEnabled )

#endif

// --------------------------------------------------------------
//      Definition of cLDBChannelCan Macro Services
// --------------------------------------------------------------
#ifdef cLDBChannelCan

extern void LDBCanSendWithAddr        (tAddress Ad, tMsg* Msg );
extern void LDBCanControl             (tCtrl    Ctrl);
extern void LDBCanEnableCallBack      (BOOL CallBackEnabled );

#define mLDBSendWithAddrcLDBChannelCan(Ad, Msg )           LDBCanSendWithAddr   (Ad, Msg )      
#define mLDBControlcLDBChannelCan(Ctrl)                    LDBCanControl        (Ctrl)          

#else
#ifdef cLDBChannelCan0

extern void LDBCanSendWithAddr         (tChannel Canal,tAddress Ad, tMsg* Msg );
extern void LDBCanControl              (tChannel Canal,tCtrl    Ctrl);
extern void LDBCanEnableCallBack       (tChannel Canal,BOOL CallBackEnabled );

#define mLDBSendWithAddrcLDBChannelCan0(Ad, Msg )           LDBCanSendWithAddr   (cLDBChannelCan0,Ad, Msg )      
#define mLDBControlcLDBChannelCan0(Ctrl)                    LDBCanControl        (cLDBChannelCan0,Ctrl)          

#define mLDBSendWithAddrcLDBChannelCan1(Ad, Msg )           LDBCanSendWithAddr   (cLDBChannelCan1,Ad, Msg )      
#define mLDBControlcLDBChannelCan1(Ctrl)                    LDBCanControl        (cLDBChannelCan1,Ctrl)          

#endif
#endif

// --------------------------------------------------------------
//      Definition of cLDBChannelAna Macro Services
// --------------------------------------------------------------
#ifdef cLDBChannelAna

extern MEM_TYPE void LDBAnaReceiveWithoutAddr    (tMsg* Msg );
extern MEM_TYPE void LDBAnaControl              (tCtrl    Ctrl);

#define mLDBReceiveWithoutAddrcLDBChannelAna(Msg)  LDBAnaReceiveWithoutAddr(Msg)  
#define mLDBControlcLDBChannelAna(Ctrl)           LDBAnaControl      (Ctrl) 

#endif

// --------------------------------------------------------------
//      Definition of cLDBChannelPwm Macro Services
// --------------------------------------------------------------
#ifdef cLDBChannelPwm

extern MEM_TYPE void LDBPwmSendWithAddr         (const tAddress Ad, const tMsg* const Msg );
extern MEM_TYPE void LDBPwmSendWithoutAddr      (const tMsg* const Msg );
extern MEM_TYPE void LDBPwmControl              (const tCtrl    Ctrl);

#define mLDBSendWithAddrcLDBChannelPwm(Ad,Msg) LDBPwmSendWithAddr(Ad,Msg)
#define mLDBSendWithoutAddrcLDBChannelPwm(Msg) LDBPwmSendWithoutAddr(Msg)
#define mLDBControlcLDBChannelPwm(Ctrl)        LDBPwmControl(Ctrl)

#endif

// --------------------------------------------------------------
//      Definition of cLDBChannelDin Macro Services
// --------------------------------------------------------------
#ifdef cLDBChannelDin

extern void LDBDinReceiveWithoutAddr    (tMsg* Msg );
extern MEM_TYPE void LDBDinControl      (tCtrl    Ctrl);

#define mLDBReceiveWithoutAddrcLDBChannelDin(Msg ) LDBDinReceiveWithoutAddr(Msg )
#define mLDBControlcLDBChannelDin(Ctrl)           LDBDinControl(Ctrl)

#endif

// --------------------------------------------------------------
//      Definition of cLDBChannelDou Macro Services
// --------------------------------------------------------------
#ifdef cLDBChannelDou

extern void LDBDouSendWithoutAddr  (const tMsg* const Msg );
extern MEM_TYPE void LDBDouControl          (const tCtrl    Ctrl);

#define mLDBSendWithoutAddrcLDBChannelDou(Msg )  LDBDouSendWithoutAddr(Msg )
#define mLDBControlcLDBChannelDou(Ctrl)          LDBDouControl      (Ctrl)

#endif

// --------------------------------------------------------------
//      Definition of cLDBChannelFla Macro Services
// --------------------------------------------------------------
#ifdef cLDBChannelFla

extern void LDBFlaSendWithAddr         (tAddress Ad, tMsg* Msg );
extern void LDBFlaControl              (tCtrl    Ctrl);

#define mLDBSendWithAddrcLDBChannelFla(Ad,Msg) LDBFlaSendWithAddr(Ad,Msg)
#define mLDBControlcLDBChannelFla(Ctrl)        LDBFlaControl     (Ctrl)

#endif

// --------------------------------------------------------------
//      Definition of cLDBChannelLinM Macro Services
// --------------------------------------------------------------
#ifdef cLDBChannelLinM

extern void LDBLinMSendWithAddr          (tAddress Ad, tMsg* Msg );
extern void LDBLinMReceiveWithAddr        (tAddress Ad, tMsg* Msg );
extern void LDBLinMControl               (tCtrl    Ctrl);

#define mLDBSendWithAddrcLDBChannelLinM(Ad,Msg)   LDBLinMSendWithAddr (Ad,Msg)
#define mLDBReceiveWithAddrcLDBChannelLinM(Ad,Msg) LDBLinMReceiveWithAddr(Ad,Msg)
#define mLDBControlcLDBChannelLinM(Ctrl)          LDBLinMControl      (Ctrl)

#endif

// --------------------------------------------------------------
//      Definition of cLDBChannelLinS Macro Services
// --------------------------------------------------------------
#ifdef cLDBChannelLinS

extern void LDBLinSPrepareSendWithAddr(tAddress Ad, tMsg* Msg );
extern void LDBLinSControl(tCtrl Ctrl);

#define mLDBPrepareSendWithAddrcLDBChannelLinS(Ad,Msg) LDBLinSPrepareSendWithAddr(Ad,Msg)
#define mLDBControlcLDBChannelLinS(Ctrl)              LDBLinSControl(Ctrl)

#endif

// --------------------------------------------------------------
//      Definition of cLDBChannelTrp Macro Services 
// --------------------------------------------------------------
#ifdef cLDBChannelTrp

extern MEM_TYPE void LDBTrpSendWithAddr(tAddress Ad, const tMsg* const Msg );
extern MEM_TYPE void LDBTrpReceiveWithAddr(tAddress Ad, const tMsg* const Msg );
extern MEM_TYPE void LDBTrpControl(const tCtrl Ctrl);

#define mLDBSendWithAddrcLDBChannelTrp(Ad,Msg)   LDBTrpSendWithAddr(Ad,Msg)
#define mLDBReceiveWithAddrcLDBChannelTrp(Ad,Msg) LDBTrpReceiveWithAddr(Ad,Msg)
#define mLDBControlcLDBChannelTrp(Ctrl)          LDBTrpControl(Ctrl)

#endif // cLDBChannelTrp

// --------------------------------------------------------------
//      Definition of cLDBChannelRf Macro Services 
// --------------------------------------------------------------
#ifdef cLDBChannelRf

extern MEM_TYPE void LDBRfControl(tCtrl Ctrl);

#define mLDBControlcLDBChannelRf(Ctrl)         LDBRfControl(Ctrl)

#endif // cLDBChannelRf

// --------------------------------------------------------------
//      Definition of cLDBChannelMot Macro Services
// --------------------------------------------------------------

#ifdef cLDBChannelMot

extern void LDBMotSendWithAddr(tAddress Ad, const tMsg* const Msg);
extern void LDBMotReceiveWithAddr       (tAddress Ad, tMsg* Msg );
extern void LDBMotControl              (tCtrl    Ctrl);

#define mLDBSendWithAddrcLDBChannelMot(  Ad, Msg )  LDBMotSendWithAddr ( Ad, Msg )
#define mLDBReceiveWithAddrcLDBChannelMot( Ad, Msg ) LDBMotReceiveWithAddr( Ad, Msg )
#define mLDBControlcLDBChannelMot( Ctrl)            LDBMotControl      ( Ctrl)

#endif // cLDBChannelMot

// --------------------------------------------------------------
//      Definition of cLDBChannelLoc Macro Services 
// --------------------------------------------------------------
#ifdef cLDBChannelLoc

extern void LDBLocSendWithoutAddr(tMsg* Msg );
extern void LDBLocReceiveWithoutAddr(tMsg* Msg );
extern void LDBLocControl(tCtrl Ctrl);

#define mLDBSendWithoutAddrcLDBChannelLoc(Msg)   LDBLocSendWithoutAddr(Msg)
#define mLDBReceiveWithoutAddrcLDBChannelLoc(Msg)LDBLocRecevoitAvecAdr(Ad,Msg)
#define mLDBControlcLDBChannelLoc(Ctrl)          LDBLocControl(Ctrl)

#endif // cLDBChannelLoc

// --------------------------------------------------------------
//      Definition of cLDBChannelDfa Macro Services
// --------------------------------------------------------------

#ifdef cLDBChannelDfa

extern void LDBControlDfa       (const tCtrl    Ctrl);
extern void LDBDfaSendWithoutAddr  (const tMsg* const pMsg );
extern void LDBDfaReceiveWithoutAddr(const tMsg* const pMsg );

#define mLDBControlcLDBChannelDfa( Ctrl)          LDBControlDfa       (Ctrl)
#define mLDBSendWithoutAddrcLDBChannelDfa(Msg)    LDBDfaSendWithoutAddr  (Msg)
#define mLDBReceiveWithoutAddrcLDBChannelDfa(Msg) LDBDfaReceiveWithoutAddr(Msg)

#endif	// cLDBChannelDfa

// --------------------------------------------------------------
//      Definition of cLDBChannelBuz Macro Services 
// --------------------------------------------------------------
#ifdef cLDBChannelBuz

extern MEM_TYPE void LDBBuzInit( void );
extern MEM_TYPE void LDBBuzControl( const tCtrl Ctrl );
extern MEM_TYPE void LDBBuzSendWithoutAddr( const tMsg * const Msg );

#ifndef TRACE_CPU_ACTIVE
#define mLDBControlcLDBChannelBuz(Ctrl)         LDBBuzControl(Ctrl)
#define mLDBSendWithoutAddrcLDBChannelBuz(Msg)  LDBBuzSendWithoutAddr(Msg)

#else // buzzer channel is not used for CPU trace
#define mLDBControlcLDBChannelBuz(Ctrl)
#define mLDBSendWithoutAddrcLDBChannelBuz(Msg)
#endif

#endif // cLDBChannelBuz

// --------------------------------------------------------------
// Definition of cLDBChannelAla Macro Services
// --------------------------------------------------------------
#ifdef cLDBChannelAla

extern MEM_TYPE void LDBAlaSendWithoutAddr(const tMsg * const Msg);

#define mLDBSendWithoutAddrcLDBChannelAla(Msg)  LDBAlaSendWithoutAddr(Msg)

#endif // cLDBChannelAla 

// --------------------------------------------------------------
// Definition of cLDBChannelSpd Macro Services
// --------------------------------------------------------------
#ifdef cLDBChannelSpd

extern void LDBSpdInit(void);
extern MEM_TYPE void LDBSpdReceiveWithAddr(const tAddress Address, tMsg * const Msg);
extern MEM_TYPE void LDBSpdControl(const tCtrl Ctrl);

#define mLDBReceiveWithAddrcLDBChannelSpd(Address, Msg) \
                                                LDBSpdReceiveWithAddr(Address, Msg)
#define mLDBControlcLDBChannelSpd(Ctrl)         LDBSpdControl(Ctrl)

#endif // cLDBChannelSpd

// --------------------------------------------------------------
//      Definition of cLDBChannelSup Macro Services 
// --------------------------------------------------------------
#ifdef cLDBChannelSup

extern void LDBSupReceiveWithoutAddr(tMsg * const Msg);
extern void LDBSupControl(const tCtrl Ctrl);

#define mLDBReceiveWithoutAddrcLDBChannelSup( Msg ) LDBSupReceiveWithoutAddr( Msg )
#define mLDBControlcLDBChannelSup( Ctrl)            LDBSupControl           ( Ctrl)

#endif // cLDBChannelSup


#endif

#if defined(__cplusplus)
#undef extern
#endif


/*-------------------------------------------------------------------------
  End of includes non re entry
  -------------------------------------------------------------------------*/
#endif   /* I_LDBPARAM_H */
