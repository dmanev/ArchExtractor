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
// Component:    LAP_DLK
//               Doorlock
// -----------------------------------------------------------------------------
// $Date:   Mar 09 2010 10:01:46  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/DLK/LAP_DLK.c-arc  $
// $Revision:   1.64  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/DLK/LAP_DLK.c-arc  $
// 
//    Rev 1.64   Mar 09 2010 10:01:46   adzhelp
// Cm007644: Code review corrections
// 
//    Rev 1.63   Mar 09 2010 09:54:18   adzhelp
// Cm007644: No HWP in sleep mode for Doorlock LED
// 
//    Rev 1.62   Mar 04 2010 12:29:30   adzhelp
// Cm007632: CDL failure management on rising ignition.
// Button authorization / enabling management updated.
// 
//    Rev 1.61   Mar 02 2010 10:49:10   adzhelp
// Cm006814: TPS_OUVPORTE, TPS_COM_MOTEUR, TIMER_PRECONDA_AUTO, TPS_REF, SEUIL_VIT_CONDAROU, NBCOM_MAX normalized
// 
//    Rev 1.60   Feb 26 2010 10:16:18   adzhelp
// Cm007634, Cm007212: Unit test corrections
// 
//    Rev 1.59   Feb 25 2010 17:33:56   adzhelp
// Cm007212: HWP: Implementation of SC detection of Verlog LED and Doorlock LED in sleep mode
// 
//    Rev 1.58   Feb 25 2010 14:55:46   adzhelp
// Cm007634:  HWP: Problems in detection of VERLOG_LED SC
// 
//    Rev 1.57   Feb 24 2010 10:04:04   adzhelp
// Cm006744:  SDO timeout calculation updated
// 
//    Rev 1.56   Feb 23 2010 11:22:46   adzhelp
// Cm006152: Doorlock LED state after reset depends on EEP flag.
// 
//    Rev 1.55   Feb 12 2010 09:08:24   adzhelp
// Cm007440: Safety unlock: ignore CDL lock after LWS until next IGN
// 
//    Rev 1.54   Feb 10 2010 16:47:10   amanevd
// Cm007075: Volatile Faults and Deprotection cleared at IGN ON
// 
//    Rev 1.53   Feb 10 2010 09:22:30   adzhelp
// Cm006744:  Perform 32-bit math operations only when values are changed
// 
//    Rev 1.52   Feb 08 2010 14:45:44   adzhelp
// Cm006989: Safety unlock performed only after LWS activated
// 
//    Rev 1.51   Feb 08 2010 11:53:24   adzhelp
// Cm007023: Send control for SDO unlock to flashers and roomlamps
// 
//    Rev 1.50   Feb 05 2010 17:41:18   adzhelp
// Cm006761: BCM does not go to Sleep mode after Driver Door unlock (SDO)
// 
//    Rev 1.49   Feb 05 2010 16:58:18   adzhelp
// Cm007005: Management of a Crash counter
// 
//    Rev 1.48   Feb 04 2010 10:49:46   adzhelp
// Cm006968, Cm006760: Limitation for repeated crash unlock
// 
//    Rev 1.47   Jan 22 2010 11:03:16   adzhelp
// Cm007074: CLR#190 - EEP flag for airbag malfunction cleared on rising ignition
// 
//    Rev 1.46   Jan 21 2010 15:09:54   adzhelp
// Cm007074: EEP flag for airbag malfunction replaced by RAM flag
// 
//    Rev 1.45   Dec 15 2009 10:52:28   amanevd
// Cm005566: DOORLOCK_LED is not turned off prior attempt to protect it
// 
//    Rev 1.44   Dec 14 2009 11:02:16   amanevd
// Cm005566: Full Hardware Protection
// 
//    Rev 1.43   Dec 01 2009 15:42:44   adzhelp
// Cm006624: EEP_CrashHazardIsRequested is not set on airbag malfunction
// 
//    Rev 1.42   Nov 04 2009 16:27:34   adzhelp
// Cm005566: Implementation of HW Protection
// 
//    Rev 1.41   Oct 30 2009 10:46:26   amarinm1
// Cm006587: Send new control AutoRelock in case of Auto Relock.
// 
//    Rev 1.40   Oct 19 2009 14:53:54   ailievb
// Cm006402: DLK: 'LOCK Doors' output remain permanently ON when LOCK requested by LWS functionality
// 
//    Rev 1.39   Oct 14 2009 16:17:26   ailievb
// Cm005149: DLK: Unexpected UNLOCK on Front doors opening after reset.
// 
//    Rev 1.38   Oct 14 2009 11:43:26   ailievb
// Cm006277: EEP_CrashHazardIsRequested should not be cleared in LAP_DLK anymore.
// 
//    Rev 1.37   Oct 14 2009 09:47:32   ailievb
// Cm006470: DLK: Fault status not updated correctly (0x61 0x94)
// 
//    Rev 1.36   Oct 06 2009 17:32:24   akodzhh
// Cm006427: DATRfPushMemorized is now updated for UnlockDrDoor, UnlockAll and LockAll trough LAP_DLK(SDO).
// 
//    Rev 1.35   Oct 06 2009 10:19:34   ailievb
// Cm006273: DLK: Update prsFS_DLK-558 according to the IR_A01
// 
//    Rev 1.34   Oct 05 2009 14:28:16   ailievb
// Cm006209: DIAG: In $21$DB diag request, bad managment "DERNIERE_CMD".
// 
//    Rev 1.33   Oct 05 2009 14:01:52   ailievb
// Cm006414: DLK: Unexpected Flashing Crash Indication on Malfunction declared.
// 
//    Rev 1.32   Oct 05 2009 11:53:26   ailievb
// Cm006369: DLK: (IR_AUI01) CAR_SECURE means vehicle locked from outside, therefore not by CPL
// 
//    Rev 1.31   Oct 01 2009 10:18:50   adzhelp
// Cm006155: BCM not activated on LeaveStartingStepState
// 
//    Rev 1.30   Sep 23 2009 17:36:36   adzhelp
// Cm005206, Cm005207: Unlock all doors activates both outputs
// 
//    Rev 1.29   Sep 23 2009 16:37:36   adzhelp
// Cm006191: Control cTOSControlCrashUnlockFinished sent only when EEP_CrashHazardIsRequested
// 
//    Rev 1.28   Sep 23 2009 10:57:08   ailievb
// Cm005137:DIAG: Fault status not updated correctly
// 
//    Rev 1.27   Sep 23 2009 10:04:36   ailievb
// Cm005206: EFX90_SW2_FP06 : Implementation of the Doorlock functionality (SDO part)
// 
//    Rev 1.26   Sep 21 2009 15:54:32   ailievb
// Cm005756: TOS Timers introduce an additional delay of 1 graph/task cycle
// 
//    Rev 1.25   Sep 18 2009 10:10:48   ailievb
// Cm006191: FLA: Need to manage crash memorization after reset.
// 
//    Rev 1.24   Sep 14 2009 15:40:58   ailievb
// Cm005603: DLK: Airbag crash, Flashers triggered too early
// 
//    Rev 1.23   Sep 11 2009 11:07:42   ailievb
// Cm005683: DLK: If ALIM_PLAF = 0 after automatic re-lock the Dorrlok LED do not switch off after 60 seconds
// 
//    Rev 1.22   Sep 10 2009 10:36:32   ailievb
// Cm005116:DLK: Unexpected relock after crash unlock
// 
//    Rev 1.21   Sep 08 2009 14:08:18   ailievb
// Cm006152: DLK: IR_A07 according to Cm006108
// 
//    Rev 1.20   Sep 08 2009 10:59:50   ailievb
// Cm006153: DLK: IR_A43 according to Cm006110.
// 
//    Rev 1.19   Jul 24 2009 09:10:14   adzhelp
// Cm005136: Integration corrections: immediate read access after starting step
// 
//    Rev 1.18   Jul 08 2009 10:54:54   ailievb
// Cm005121: DLK: No 'Unlock All' command LWS conditions not met and door opened
// 
//    Rev 1.17   Jul 07 2009 16:56:04   ailievb
// Cm005602 : DLK: Unexpected driving duration of doorlock motors
// 
//    Rev 1.16   Jul 07 2009 14:18:02   ailievb
// Cm005120: DLK: If the doors are locked by RKE or by Auto-relock the DOORLOCK_LED remains turned on after a door opening.
// 
//    Rev 1.15   Jul 07 2009 11:17:56   ailievb
// Cm005132: DLK: 'Master Front Doors unlocking' function do not operate when last RKE is Unlock and key is authorized
// 
//    Rev 1.14   Jul 07 2009 10:53:34   ailievb
// Cm005095:DLK: The DOORLOCK_LED doesn't turn off after front door opening
// 
//    Rev 1.13   Jul 07 2009 09:35:00   ailievb
// Cm005136: DLK: The BCM does LOCK/UNLOCK the doors at BCM reset if the CDL button is in LOCK/UNLOCK position.
// 
//    Rev 1.12   Jul 07 2009 09:24:42   ailievb
// Cm005135:DLK: BCM does not detect a opposite CDL request spaced out less than TPS_COM_MOTEUR time-out 
// 
//    Rev 1.11   May 27 2009 10:42:50   ailievb
// Cm003264:Implementation of the Doorlock functionality (Without SDO part)
// 
//    Rev 1.10   May 08 2009 16:29:52   ailievb
// Cm004984:DoorLock issue : No systematic Crash Unlock in case of Airbag Malfunction
// 
//    Rev 1.9   May 08 2009 14:36:36   ailievb
// Cm004984:DoorLock issue : No systematic Crash Unlock in case of Airbag Malfunction
// 
//    Rev 1.8   May 08 2009 07:47:30   ailievb
// Cm004927:Wrong interpretation of prsFS_DLK-537 (relocking while the door is still open)
// 
//    Rev 1.7   May 07 2009 11:31:14   ailievb
// Cm004927:Wrong interpretation of prsFS_DLK-537 (relocking while the door is still open)
// Cm004939: LWS diag "VEHICULE_ROULANT" not updated
// Cm004934: Diag: ETAT_VEH_CONDA_DECONDA, DERNIERE_CMD not updated for RKE
// 
//    Rev 1.6   May 04 2009 17:40:32   ailievb
// Cm004912: Led CPE is not set properly when lock command is executed
// 
//    Rev 1.4   Apr 28 2009 09:33:46   ailievb
// Cm003264:Implementation of the Doorlock functionality (Without SDO part)
// 
//    Rev 1.3   Apr 22 2009 10:56:28   ailievb
// Cm003264:Implementation of the Doorlock functionality (Without SDO part)
// LastOpeningPanelControl added for diagnostic purposes.
// 
//    Rev 1.2   Apr 21 2009 11:56:30   ailievb
// Cm003264:Implementation of the Doorlock functionality (Without SDO part)
// DATCmnVehicleIsUnprotected, DATCmnLastCommandOrigin, DATCmnVehicleIsAutoRelocked,
// DATCmnVehicleIsLockedWithSpeed, DATCmnVehiculeHasBeenMoving added for diagnostic purposes
// 
//    Rev 1.1   Apr 16 2009 15:02:18   ailievb
// Added support of 1 Button RKE.
// Issue correction. 
// 
//    Rev 1.0   Mar 24 2009 09:37:56   ailievb
// Initial revision.
//
//******************************************************************************

//--------------------------------------------------------------------------
// Body Identification
//--------------------------------------------------------------------------

#define LAP_DLK  "LAP_DLK"
//--------------------------------------------------------------------------
//  Included files
//
//  #include <system_file_name.h>
//  #include "project_file_name.h"
//--------------------------------------------------------------------------

#include "tos.h"
#include "dat.h"
#include "LAP_DLK.h"
#include "LAP_DLK.hgr"

//--------------------------------------------------------------------------
// Local constants
//
//  #define cConstantName   ((tType) ConstantValue)
//--------------------------------------------------------------------------

//Constants to define commands, posible values of: CommandRequest
#define cNothingRequested                   ((tCommandRequested)0U)   
#define cRfLockAllDoors                     ((tCommandRequested)1U) //Rf
#define cRfUnlockAllDoors                   ((tCommandRequested)2U) //Rf
#define cRfUnlockDriverDoor                 ((tCommandRequested)3U) //Rf
#define cCDLUnlock                          ((tCommandRequested)4U) //CDL 
#define cCDLLock                            ((tCommandRequested)5U) //CDL
#define cCrashUnlock                        ((tCommandRequested)6U) //Crash
#define cLockWithSpeed                      ((tCommandRequested)7U) //LWS
#define cAutoRelock                         ((tCommandRequested)8U) //AutoRelock

//Constants to define commands, possible values of: LEDCommandRequest
#define cLEDOffRequested                   ((U8)0U)   
#define cLEDOnRequested                    ((U8)1U)   
#define cLEDOneMinOnRequested              ((U8)2U)   


#define cRelayRestPosition                  ((U8)0x00U)
#define cLockAll                            ((U8)0x01U)
#define cUnlockAll                          ((U8)0x02U)
#define cUnlockDriverDoor                   ((U8)0x03U) 

#define cNbLWSOpenCloseDoor                 ((U8)5U) // 5th time door is opened
#define cCDLDebounceTimeOut                 ((tTOSTempo)    40U) // 40ms  prsFS_DLK-474                                        
#define cLWSActivationTimeOut               ((tTOSTempo)  4000U) // 4s      
#define cLockWithSpeedTimeOut               ((tTOSTempo)  1000U) // 1s      
#define cDebounceTimeOut                    ((tTOSTempo)    10) // 10ms

#define cSDOTimeOut \
    ((tTOSTempo)(1000U * \
      (u8EEP_TPS_OUVPORTEOld = mDATRead(U8Bit, NEEP_TPS_OUVPORTE, Default)))) // step 1000ms according to CLR53

#define cMotorActivationTimeOut             \
( (tTOSTempo) (10U*  \
    (u8EEP_TPS_COM_MOTEUROld = mDATRead(U8Bit, NEEP_TPS_COM_MOTEUR, Default))) ) //unit:10ms
#define cAutoRelockTimeOut                  \
( (tTOSTempo) (1000U* \
    (u8EEP_TIMER_RECONDA_AUTOOld = mDATRead(U8Bit, NEEP_TIMER_RECONDA_AUTO, Default))) ) //unit:1sec


#define cLedActivationTimeOut  ((tTOSTempo)  60000U) //1min

#define cSevereAbuseTimeOutShort \
    (tTOSTempo)(500U * (u8EEP_TPS_REFShort = mDATRead(U8Bit, NEEP_TPS_REF, Default)))
#define cSevereAbuseTimeOutLong  \
    (tTOSTempo)(2 * (500U * (u8EEP_TPS_REFLong = mDATRead(U8Bit, NEEP_TPS_REF, Default))))

// Protection constant
#define cMaxU8                      ((U8) 0xFFU)
#define cImmoEcmTemporization       (mTOSConvMsInTimerTick((U32)50UL)) // 50ms
#define cEcmTemporization           (mTOSConvMsInTimerTick((U32)10UL)) // 10ms

//--------------------------------------------------------------------------
// Local macros
//
// #define mMacroName   (MacroDefinition)
//--------------------------------------------------------------------------

#define mSet(Type,DataName)                                       \
(DLK ## Type ## Status.BitField.## DataName = cTrue)

#define mReset(Type,DataName)                                     \
(DLK ## Type ## Status.BitField.## DataName = cFalse)

#define mRead(Type,DataName)                                      \
(DLK ## Type ## Status.BitField.## DataName)

#define mReadMotorActivationTimeoutTicks() \
    (MotorActivationTimeoutTicks = \
        (u8EEP_TPS_COM_MOTEUROld == mDATRead(U8Bit, NEEP_TPS_COM_MOTEUR, Default)) ? \
           MotorActivationTimeoutTicks \
        :  mTOSConvMsInTimerTick(cMotorActivationTimeOut))

#define mReadAutoRelockTimeOutTicks() \
    (AutoRelockTimeOutTicks = \
        (u8EEP_TIMER_RECONDA_AUTOOld == mDATRead(U8Bit, NEEP_TIMER_RECONDA_AUTO, Default)) ? \
           AutoRelockTimeOutTicks \
        :  mTOSConvMsInTimerTick(cAutoRelockTimeOut))

#define mReadSevereAbuseTimeOutShortTicks() \
    (SevereAbuseTimeOutShortTicks = \
        (u8EEP_TPS_REFShort == mDATRead(U8Bit, NEEP_TPS_REF, Default) ) ? \
           SevereAbuseTimeOutShortTicks \
        :  mTOSConvMsInTimerTick(cSevereAbuseTimeOutShort) )

#define mReadSevereAbuseTimeOutLongTicks() \
    (SevereAbuseTimeOutLongTicks = \
        (u8EEP_TPS_REFLong == mDATRead(U8Bit, NEEP_TPS_REF, Default) ) ? \
           SevereAbuseTimeOutLongTicks \
        :  mTOSConvMsInTimerTick(cSevereAbuseTimeOutLong) )

#define mReadSDOTimeOutTicks() \
    (SDOTimeOutTicks = \
        (u8EEP_TPS_OUVPORTEOld == mDATRead(U8Bit, NEEP_TPS_OUVPORTE, Default)) ? \
          SDOTimeOutTicks \
        : mTOSConvMsInTimerTick(cSDOTimeOut) )

//--------------------------------------------------------------------------
// Local types
//
//  struct  sStructureName { ... };
//  union   uUnionName { ... };
//  enum    eEnumerationName { ... };
//  typedef Expression tTypeName;
//--------------------------------------------------------------------------

typedef union DLKControlUnion
{
    U32 DLKControlFlags;
    struct
    {
        U1 AllDoorsAreClosed                :1;       // 1
        U1 KeyIsAuthenticated               :1;       // 2
        U1 MotorsAreInOperation             :1;       // 3
        U1 LWSNewConfirmationRequested      :1;       // 4 
        U1 CDLButtonIsAuthorized            :1;       // 5 
        U1 NewCommandToBeDone               :1;       // 6 
        U1 CDLDebounceTimerIsLock           :1;       // 7 
        U1 AutoRelockIsEnabled              :1;       // 8 
        U1 CDLButtonIsPressed               :1;       // 9
        U1 CDLButtonIsLock                  :1;       // 10
        U1 Rising_DOOR_UNLOCK_LOCK_SW       :1;       // 11
        U1 Rising_DOOR_LOCK_SW              :1;       // 12
        U1 Falling_FR_DOORS_SW_LAP_DLK      :1;       // 13
        U1 Falling_RR_DOORS_SW_LAP_DLK      :1;       // 14
        U1 LWSMustLockOverThreshold         :1;       // 15
        U1 LWSLockedWithOpenDoor            :1;       // 16
        U1 AirBagMalFunctionDetected        :1;       // 17
        U1 LWSForbiddenByAirBagMalFunction  :1;       // 18
        U1 LWSWithOpenDoorEnabled           :1;       // 19
        U1 Rising_PWR_IGN_LAP_DLK           :1;       // 20
        U1 Changing_FR_DOORS_SW_LAP_DLK     :1;       // 21
        U1 Changing_RR_DOORS_SW_LAP_DLK     :1;       // 22
        U1 Rising_FR_DOORS_SW_LAP_DLK       :1;       // 23
        U1 LWSSpeedConditionsAreMet         :1;       // 24
        U1 WaitLongSevereAbuseTimeOut       :1;       // 25
        U1 LastRFActionIsUnlock             :1;       // 26  
        U1 LWSForbiddenAfterCrash           :1;       // 27  
        U1 CarSecure                        :1;       // 28  
        U1 SafetyUnlockAllowed              :1;       // 29  
        U1 CDLButtonIsEnabled               :1;       // 30
    } BitField;
} structDLKControlFlag;

typedef union DLKTimerControlUnion
{
    U8 DLKTimerControlFlags;
    struct
    {
        U1 AutoRelockTimerIsArmed           :1;       // 1
        U1 VehiculeHasBeenMovingTimerIsArmed:1;       // 2
        U1 CDLDebounceTimerIsStarted        :1;       // 3 
        U1 LWSActivationTimerIsStarted      :1;       // 4 
        U1 LWSDeativationTimerIsStarted     :1;       // 5 
        U1 LockWithSpeedTimerIsArmed        :1;       // 6
        U1 LedActivationTimerIsStarted      :1;       // 7
        U1 AbuseTimerIsStarted              :1;       // 8
        U1 SDOTimerIsStarted                :1;       // 9
    } BitField;

} structDLKTimerControlFlag;


//Same position as constants to define commands, posible values of: CommandRequest
typedef union DLKArbitrationUnion
{
    U8 DLKArbitrationFlags;
    struct
    {
        U1 CDLLock                           :1;        // 1   
        U1 CDLUnlock                         :1;        // 2   
        U1 RfLockAllDoors                    :1;        // 3   
        U1 RfUnlockAllDoors                  :1;        // 4  
        U1 RfUnlockDriverDoor                :1;        // 5   
        U1 CrashUnlock                       :1;        // 6   
        U1 LockWithSpeed                     :1;        // 7   
        U1 AutoRelock                        :1;        // 8    
    } BitField;
} structDLKArbitrationFlag;


typedef enum
{
    cOutputStateDetection,
    cDefectDetection
}tProtectionStateMachine;


typedef U16 tCommandRequested;
typedef U8  tLEDCommandRequested;

//--------------------------------------------------------------------------
// Local data
//
// static  tType   VariableName;
// static  tType*  pVariableName; 
//--------------------------------------------------------------------------
static structDLKControlFlag       DLKControlStatus;
static structDLKArbitrationFlag   DLKArbitrationStatus;
static structDLKTimerControlFlag  DLKTimerControlStatus;

static U8 NbLWSOpenCloseDoor; //counts number of open/close done until next Apc Off
static U8 MotorPattern;
static U8 MotorActionCounter;
static U8 LEDCommandRequested;

static tCommandRequested DLKLastCommandRequested; //Posible values: 0 to 16 (see #define above)
static tCommandRequested CommandRequested;        //Posible values: 0 to 16 (see #define above)

static tTOSTempo LockWithSpeedTime;
static tTOSTempo SevereAbuseTime;
static tTOSTempo SevereAbuseTimeOut;
static tTOSTempo DebounceTime;
static tTOSTempo MotorActivationTime;
static tTOSTempo AutoRelockTime;
static tTOSTempo CDLDebounceTime;
static tTOSTempo LWSActivationTime;
static tTOSTempo LedActivationTime;
static tTOSTempo VehiculeHasBeenMovingTime; //for diagnostic
static tTOSTempo SDOTimeOut;

static tTOSTempo AutoRelockTimeOutTicks;
static U8        u8EEP_TIMER_RECONDA_AUTOOld;
static tTOSTempo MotorActivationTimeoutTicks;
static U8        u8EEP_TPS_COM_MOTEUROld;
static tTOSTempo SevereAbuseTimeOutShortTicks;
static U8        u8EEP_TPS_REFShort;
static tTOSTempo SevereAbuseTimeOutLongTicks;
static U8        u8EEP_TPS_REFLong;
static tTOSTempo SDOTimeOutTicks;
static U8        u8EEP_TPS_OUVPORTEOld;

// HW Protection
static BOOL                     bPWR_IGNOld;
static tProtectionStateMachine  ProtectionState;
static tTOSTimer                ImmoEcmProtection;
static BOOL                     bLED_VERLOGStopped;

//--------------------------------------------------------------------------
// Constant local Data
//
// static const tType  VariableName;
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// Exported data
//
// tType   CMPVariableName;      (CMP: 3 characters to identify this component)
// tType*  pCMPVariableName;     (CMP: 3 characters to identify this component)
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// Constant exported data
//
//  const tType   CMPVariableName;(CMP: 3 characters to identify this component)
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// Local function prototypes
//
//  static tTypeRetour FunctionName(tTypeArgument1 ArgumentName1, ... );
//--------------------------------------------------------------------------
static MEM_TYPE void DLKProtectionTask (void);
static MEM_TYPE void SetVerlogLedDefect (void);
static MEM_TYPE void SetDoorlockLedDefect (void);

#ifdef X90_PROJECT    
static MEM_TYPE void DLKInputDataManagement_Static(void);
static MEM_TYPE void DLKCommandMotorRelays_Static(void);
static MEM_TYPE void DLKOutputDataManagement_Static(void);
static MEM_TYPE BOOL DLKCommandIsPending_Static(void);
static MEM_TYPE void DLKInitialize_Static(void);
static MEM_TYPE void DLKDeCommandMotorRelays_Static(void);
static MEM_TYPE void DLKAirbagInformationManagement_Static(void);
#endif

/****************************************************************************
*...........................................................................*
*............................ LOCAL FUNCTIONS ..............................*
*...........................................................................*
****************************************************************************/
//--------------------------------------------------------------------------
//  DESCRIPTION : DLKProtectionTask
//
//  PARAMETERS (Type,Name,Min,Max) :   none
//  
//  RETURN VALUE :   none
//    
//  DESIGN INFORMATION :   refer to Detailed Design Document
//      
//--------------------------------------------------------------------------
static MEM_TYPE void DLKProtectionTask (void)
{
    BOOL bIsTimerStartedL;
    BOOL bIsTimerElapsedL;

    if(     (cFalse != mDATRead(U1Bit, PWR_IGN, Default))
        &&  (cFalse == bPWR_IGNOld)
      )
    {
        mDATWrite(U1Bit, OPEN_DOOR_LEDProtection, 0, Default);
        mDATWrite(U1Bit, DefDoorlockLedCC, 0, Default);

        mDATWrite(U1Bit, VERLOG_LEDProtection, 0, Default);
        mDATWrite(U1Bit, DefVerlogLedCC, 0, Default);
    }

    switch(ProtectionState)
    {
        case cOutputStateDetection:

        // DO state actions
        bIsTimerStartedL = TOSIsTimerStarted(&ImmoEcmProtection);
        if (cFalse != mDATRead(U1Bit, DIAG_DRIVER_ULQ_SCBat, Default))
        {
            if(cFalse == bIsTimerStartedL)
            {
                if(     (cFalse != mDATRead(U1Bit, DATTrpOutputActive, Default))
                    ||  (cFalse == mDATRead(U1Bit, DI_VERLOG, Immediate))
                  )
                {
                    TOSStartTimer(&ImmoEcmProtection);
                    bLED_VERLOGStopped=0;
                }
            }
        }
        else
        {
            if(cTrue == bIsTimerStartedL)
            {
                TOSStopTimer(&ImmoEcmProtection);
            }
        }

        bIsTimerStartedL = TOSIsTimerStarted(&ImmoEcmProtection);
        
        if (mDATRead(U1Bit, PWR_IGN, Default) != cFalse)
        {
            bIsTimerElapsedL = TOSIsTimerElapsed(&ImmoEcmProtection, cImmoEcmTemporization);
        }
        else
        {
            // only VERLOG line can be active
            bIsTimerElapsedL = TOSIsTimerElapsed(&ImmoEcmProtection, cEcmTemporization);
        }
        
        // Exit state conditions
        if(     ((cFalse != bIsTimerElapsedL) && (cFalse != bIsTimerStartedL))
            ||  (   (cFalse != mDATRead(U1Bit, DIAG_DRIVER_ULQ_SCBat, Default))
                 && ((cFalse == bIsTimerStartedL))
                )
          )
        {
            ProtectionState = cDefectDetection;
        }
        break;

        case cDefectDetection:

        // DO state actions
        if(cFalse != mDATRead(U1Bit, VERLOG_LED, Immediate))
        {
            if(cFalse != mDATRead(U1Bit, DIAG_DRIVER_ULQ_SCBat, Default))
            {
                if (1 == mDATRead(U1Bit, OPEN_DOOR_LED, Immediate))
                {
                    // DOOR_LOCK_LED is active: need to deactivate VERLOG LED
                    mDATWrite(U1Bit, VERLOG_LED, 0, Default);
                    mDATWrite(U1Bit, VERLOG_LEDDirect, 0, Default);
                    bLED_VERLOGStopped=1;
                }
                else
                {
                    // Only verlog LED is active and there is SC:
                    bLED_VERLOGStopped = 0;
                    SetVerlogLedDefect();
                }
            }
            else
            {
                // no SC detected
            }
        }
        else if(    (1 == mDATRead(U1Bit, OPEN_DOOR_LED, Immediate))
                 && (cFalse == mDATRead(U1Bit, AlaCommunicationIsRunning, Default))    
               )
        {
            if (mDATRead(U1Bit, DIAG_DRIVER_ULQ_SCBat, Default) != cFalse)
            {
                bLED_VERLOGStopped = 0;
                SetDoorlockLedDefect();
            }
            else if(1 == bLED_VERLOGStopped)
            {
                bLED_VERLOGStopped = 0;
                SetVerlogLedDefect();
            }
            else
            {
                bLED_VERLOGStopped = 0;
            }

            // Exit state conditions
            if (cFalse == mDATRead(U1Bit, DIAG_DRIVER_ULQ_SCBat, Default))
            {
                ProtectionState = cOutputStateDetection;
            }
        }
        else
        {
            // outputs not activated or already protected
        }

        break;
        
        //CCOV: adzhelp: Cannot be covered in normal operating conditions,
        default:
        
        mLIBassert(cFalse);
        break;
    }

    bPWR_IGNOld = mDATRead(U1Bit, PWR_IGN, Default);
}

//--------------------------------------------------------------------------
//  DESCRIPTION : SetVerlogLedDefect
//
//  PARAMETERS (Type,Name,Min,Max) :   none
//  
//  RETURN VALUE :   none
//    
//  DESIGN INFORMATION :   refer to Detailed Design Document
//--------------------------------------------------------------------------
static MEM_TYPE void SetVerlogLedDefect (void)
{
    U8 u8TempL;

    mDATWrite(U1Bit, DefVerlogLedCC, 1, Default);
    mDATWrite(U1Bit, VERLOG_LEDProtection, 1, Default);                
    mDATWrite(U1Bit, EEP_DefVerlogLedCC, 1, Default);
    
    u8TempL = mDATRead(U8Bit, EEP_CDVerlogLed, Default);
    if(u8TempL < cMaxU8)
    {
        u8TempL ++;
        mDATWrite(U8Bit, EEP_CDVerlogLed, u8TempL, Default);
    }
}

//--------------------------------------------------------------------------
//  DESCRIPTION : SetDoorlockLedDefect
//
//  PARAMETERS (Type,Name,Min,Max) :   none
//  
//  RETURN VALUE :   none
//    
//  DESIGN INFORMATION :   refer to Detailed Design Document
//--------------------------------------------------------------------------
static MEM_TYPE void SetDoorlockLedDefect (void)
{
    U8 u8TempL;
    
    mDATWrite(U1Bit, DefDoorlockLedCC, 1, Default);
    mDATWrite(U1Bit, OPEN_DOOR_LEDProtection, 1, Default);
    mDATWrite(U1Bit, EEP_DefDoorlockLedCC, 1, Default);
    // Enter in IgnOff State
    u8TempL = mDATRead(U8Bit, EEP_CDDoorLockLed, Default);
    if(u8TempL < cMaxU8)
    {
        u8TempL ++;
        mDATWrite(U8Bit, EEP_CDDoorLockLed, u8TempL, Default);
    }
}

/* [LOCAL_FUNCTIONS_END] */


/****************************************************************************
*...........................................................................*
*........................... EXPORTED FUNCTIONS.............................*
*...........................................................................*
****************************************************************************/

//--------------------------------------------------------------------------
//  DESCRIPTION : DRLInputDataManagement
//
//  PARAMETERS (Type,Name,Min,Max) :   none
//  
//  RETURN VALUE :   none
//    
//  DESIGN INFORMATION :   refer to Detailed Design Document
//      
//--------------------------------------------------------------------------
void DLKInputDataManagement(void)
{
#ifdef X90_PROJECT    
    DLKInputDataManagement_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DLKInputDataManagement_Static(void)
{
#endif
    BOOL bTimerElapsedL;
    tTOSTempo TimeoutTicksL;

    if (TOSReadSignal(cTOSSignalRising_PWR_IGN_LAP_DLK))
    {
        mSet(Control, Rising_PWR_IGN_LAP_DLK);
    }
    if (TOSReadSignal(cTOSSignalRising_DOOR_UNLOCK_LOCK_SW_LAP_DLK))
    {
        mSet(Control, Rising_DOOR_UNLOCK_LOCK_SW);
    }
    
    if (TOSReadSignal(cTOSSignalRising_DOOR_LOCK_SW_LAP_DLK))
    {
        mSet(Control, Rising_DOOR_LOCK_SW);
    }         
    
    if (TOSReadSignal(cTOSSignalFalling_FR_DOORS_SW_LAP_DLK))
    {
        mSet(Control, Falling_FR_DOORS_SW_LAP_DLK);
    }

    
    if (TOSReadSignal(cTOSSignalRising_FR_DOORS_SW_LAP_DLK))
    {
        mSet(Control, Rising_FR_DOORS_SW_LAP_DLK);
    }
    
    if (TOSReadSignal(cTOSSignalFalling_RR_DOORS_SW_LAP_DLK))
    {
        mSet(Control, Falling_RR_DOORS_SW_LAP_DLK);
    }
    
    if (TOSReadSignal(cTOSSignalChanging_FR_DOORS_SW_LAP_DLK))
    {
        mSet(Control, Changing_FR_DOORS_SW_LAP_DLK);
    }
    
    if (TOSReadSignal(cTOSSignalChanging_RR_DOORS_SW_LAP_DLK))
    {
        mSet(Control, Changing_RR_DOORS_SW_LAP_DLK);
    }
    
    //Update flag AllDoorsAreClosed
    if (   (mDATRead(U1Bit, FR_DOORS_SW, Default) == cFalse)
        && (mDATRead(U1Bit, RR_DOORS_SW, Default) == cFalse)
        )
    {
        mSet(Control, AllDoorsAreClosed);
    }
    else
    {
        mReset(Control, AllDoorsAreClosed);
    }
    
    //Update flags: KeyIsAuthenticated is reset when the ignition is turned off
    if (mDATRead(U1Bit, PWR_IGN, Default) == cFalse)
    { 
        mReset(Control, KeyIsAuthenticated);
        mDATWrite(U1Bit, VehiculeHasBeenMoving, cFalse, Default);
    }
    else
    {
        //nothing to do
    } 
    
    // prsFS_DLK-467
    if (mRead(Control, Rising_PWR_IGN_LAP_DLK) == cTrue)
    {
        mReset(Control, LWSForbiddenAfterCrash); // prsFS_DLK-549 
        mReset(Control, LWSForbiddenByAirBagMalFunction);  // prsFS_DLK-547
        mReset(Control, SafetyUnlockAllowed); // Cm007440

        //****************************************************************************
        // CDLButton failure management
        //****************************************************************************
        // prsFS_DLK-467, prsFS_DLK-468
        if (mDATRead(U1Bit, EEP_CPE_IMPULS, Default) == cFalse) // CDL button with 3 positions 
        {
            if (mDATRead(U1Bit, DOOR_LOCK_SW, Default) == cTrue)
            {
                mDATWrite(U1Bit, DefBtonCpeFer, cTrue, Default);
            }
            else
            {
                mDATWrite(U1Bit, DefBtonCpeFer, cFalse, Default);
            }

            if (mDATRead(U1Bit, DOOR_UNLOCK_SW, Default) == cTrue)
            {
                mDATWrite(U1Bit, DefBtonCpeOuv, cTrue, Default);
            }
            else
            {
                mDATWrite(U1Bit, DefBtonCpeOuv, cFalse, Default);
            }
        }
        else // CDL button with 2 positions
        {
            mDATWrite(U1Bit, DefBtonCpeOuv, cFalse, Default); // not used

            if (mDATRead(U1Bit, DOOR_UNLOCK_SW, Default) == cTrue)
            {
                // although Unlock input is activated set 'Fer' defect
                mDATWrite(U1Bit, DefBtonCpeFer, cTrue, Default);
            }
            else
            {
                mDATWrite(U1Bit, DefBtonCpeFer, cFalse, Default);
            }
        }

        // CDL button Enable/disable - only on rising ignition

        if (   (mDATRead(U1Bit, DefBtonCpeOuv, Default) == cTrue ) // prsFS_DLK-467          
            || (mDATRead(U1Bit, DefBtonCpeFer, Default) == cTrue ) // prsFS_DLK-467         
            )
        {
            mReset(Control, CDLButtonIsEnabled); //prsFS_DLK-826
        }
        else
        {
            mSet(Control, CDLButtonIsEnabled); // prsFS_DLK-468
        }

        // CLR #190
        mDATWrite(U1Bit, DefAirbag, cFalse, Default); // no requirement yet
    }
    
    //****************************************************************************
    // AutoRelock
    //****************************************************************************
    if (mDATRead(U1Bit, EEP_CONDATMPO, Default) == cTrue) //AutoRelock function is enabled
    {
        //AutoRelock canceled prsFS_DLK-499
        if (   (mRead(Control, Rising_PWR_IGN_LAP_DLK) == cTrue)
            || (DLKLastCommandRequested == cCDLLock)
            || (DLKLastCommandRequested == cCDLUnlock)
            || (DLKLastCommandRequested == cRfLockAllDoors)
            || ( ((DLKLastCommandRequested == cRfUnlockAllDoors) || (DLKLastCommandRequested == cRfUnlockDriverDoor))
            &&(mRead(Control, AllDoorsAreClosed) == cFalse)
            )
            || (mRead(Control, Changing_FR_DOORS_SW_LAP_DLK) == cTrue) 
            || (mRead(Control, Changing_RR_DOORS_SW_LAP_DLK) == cTrue)  
            ) 
        {
            mReset(TimerControl, AutoRelockTimerIsArmed);
        }
        else
        {
            TimeoutTicksL = mReadAutoRelockTimeOutTicks();

            if (  (TOSIsTempoElapsed(&AutoRelockTime, TimeoutTicksL) == cTrue)
                && (mRead(TimerControl, AutoRelockTimerIsArmed) == cTrue)
            ) //AutoRelock demanded
            {
                mSet(Arbitration, AutoRelock);
                mReset(TimerControl, AutoRelockTimerIsArmed);
            }
            else
            {
            } 
            //wait TimeOut or RfUnlock
            //AutoRelock is armed after arbitration if RfUnlock (with all doors closed) occured
        }
    }
    else //AutoRelock function is not enabled
    {
        mReset(Arbitration, AutoRelock);
        mReset(TimerControl, AutoRelockTimerIsArmed);
    } 	
    
    //****************************************************************************
    // CDLButton Is Authorized/Inhibitted
    //****************************************************************************
    //Update flag CDLButtonIsAuthorized (other conditions are in function CommandMotorRelays)
    // prsFS_DLK-455 must be taken into account
    if (   (mRead(Control, Rising_PWR_IGN_LAP_DLK) == cTrue) // prsFS_DLK-455,prsFS_DLK-457
        || (mDATRead(U1Bit, FR_DOORS_SW, Default) == cTrue)  // prsFS_DLK-457, see also CommandMotorRelays
        || (mDATRead(U1Bit, RR_DOORS_SW, Default) == cTrue)  // prsFS_DLK-457, see also CommandMotorRelays
        )
    {
        mSet(Control, CDLButtonIsAuthorized); 
    }
    else {} //nothing to do

    //****************************************************************************
    // CDLButton management
    //****************************************************************************
    if ((mRead(Control, CDLButtonIsEnabled) != cFalse) &&
        (mRead(Control, CDLButtonIsAuthorized) != cFalse) )
    {
        //Update CDL flags 
        if (mDATRead(U1Bit, EEP_CPE_IMPULS, Default) == cTrue) // CDL button with 2 positions 
        { 
            if ((mDATRead(U1Bit, DOOR_UNLOCK_SW, Default) == cTrue) &&
               (mRead(Control, MotorsAreInOperation) == cFalse))
            {
                mSet(Control, CDLButtonIsPressed);
                if(mRead(Control, CarSecure) == cTrue) 
                {
                    mReset(Control, CDLButtonIsLock);
                }
                else
                {
                    mSet(Control, CDLButtonIsLock);
                }
            }
            else
            {
                mReset(Control, CDLButtonIsPressed);
            }
        }
        else // CDL button with 3 positions 
        { 
            if ((mDATRead(U1Bit, DOOR_LOCK_SW, Default) == cTrue) ||
                (mDATRead(U1Bit, DOOR_UNLOCK_SW, Default) == cTrue)
               )
            {
                mSet(Control, CDLButtonIsPressed);
            }
            else
            {
                mReset(Control, CDLButtonIsPressed);
            }
        }
        
        if ( (mRead(Control, Rising_DOOR_LOCK_SW) == cTrue)
            || (mRead(Control, Rising_DOOR_UNLOCK_LOCK_SW) == cTrue)
           )
        {
            if (mRead(Control, Rising_DOOR_LOCK_SW) == cTrue)
            {
                mSet(Control, CDLButtonIsLock);
            }
            else
            {
                mReset(Control, CDLButtonIsLock);
            }
            mSet(TimerControl, CDLDebounceTimerIsStarted);
            TOSStartTempo(&CDLDebounceTime);  // prsFS_DLK-474
        }
    }
    
    if (   (mRead(Control, CDLButtonIsEnabled) == cTrue)  // CDLButton Is Enabled
        && (mRead(Control, CDLButtonIsAuthorized) == cTrue)  // CDLButton Is authorized
        && (TOSIsTempoElapsed(&CDLDebounceTime, mTOSConvMsInTimerTick(cCDLDebounceTimeOut) - (tTOSTimer)1U) == cTrue) // prsFS_DLK-474
        && (mRead(TimerControl, CDLDebounceTimerIsStarted) == cTrue)
        )
    {
        if ((mRead(Control, CDLButtonIsPressed) == cTrue) &&
           (mRead(Control, MotorsAreInOperation) == cFalse))
        {
            mReset(TimerControl, CDLDebounceTimerIsStarted); 
            if (mRead(Control, CDLButtonIsLock) == cTrue)
            {
                mSet(Arbitration, CDLLock); // prsFS_DLK-476
            }
            else
            {
                mSet(Arbitration, CDLUnlock); // prsFS_DLK-476
            }
        }
    }		
    
    //****************************************************************************
    // RF reception
    //****************************************************************************
    if (   (mDATRead(U1Bit, PWR_IGN, Default) == cFalse)     // prsFS_DLK-480
        && (mDATRead(U1Bit, EEP_AUTRECRF, Default) == cTrue) // prsFS_DLK-342, prsFS_DLK-481
        && (mRead(Control, MotorsAreInOperation) == cFalse) 
        )
    {
        if (mDATRead(U1Bit, EEP_KEY_BUTTON, Default) == cTrue)
        {
            // RF Key with 2 buttons
            if (mDATRead(U1Bit, EEP_SDO, Default) == cTrue) // prsFS_DLK-571
            { 
                // SDO is enabled
                TimeoutTicksL = mReadSDOTimeOutTicks();
                
                bTimerElapsedL = (BOOL)
                        (   (mRead(TimerControl, SDOTimerIsStarted) != cFalse)
                         && (TOSIsTempoElapsed(&SDOTimeOut, TimeoutTicksL) != cFalse));

                if (bTimerElapsedL != cFalse)
                {
                    // Allow device to go to sleep - Cm006761
                    mReset(TimerControl, SDOTimerIsStarted);
                }

                if (mDATRead(U1Bit, DATRfUnlockPush, Default) == cTrue)
                {
                    if (mRead(TimerControl, SDOTimerIsStarted) == cTrue) // not elapsed!
                    {
                        mReset(TimerControl, SDOTimerIsStarted); 
                        mSet(Arbitration, RfUnlockAllDoors);
                        DATRfMemorisePush(cDATRfDiagUnlockAll);
                    }
                    else
                    {
                        // SDO
                        TOSStartTempo(&SDOTimeOut); 
                        mSet(Arbitration, RfUnlockDriverDoor); // prsFS_DLK-577
                        mSet(TimerControl, SDOTimerIsStarted); 
                        DATRfMemorisePush(cDATRfDiagUnlockDrDoor);
                    }
                }

                if (mDATRead(U1Bit, DATRfLockPush, Default) == cTrue)
                {
                    mSet(Arbitration, RfLockAllDoors); // prsFS_DLK-486
                    mReset(TimerControl, SDOTimerIsStarted); 
                    DATRfMemorisePush(cDATRfDiagLockAll);
                }
            }
            else
            {
                // SDO is disabled.
                mReset(TimerControl, SDOTimerIsStarted); 
                if (mDATRead(U1Bit, DATRfLockPush, Default) == cTrue)
                {
                    mSet(Arbitration, RfLockAllDoors); // prsFS_DLK-486
                    DATRfMemorisePush(cDATRfDiagLockAll);
                }
                else if (mDATRead(U1Bit, DATRfUnlockPush, Default) == cTrue)
                {
                    mSet(Arbitration, RfUnlockAllDoors); // prsFS_DLK-489
                    DATRfMemorisePush(cDATRfDiagUnlockAll);
                }
            }
        }
        else
        {
            // RF Key with 1 button(Lock push button), 
            // NO SDO
            // NO Unlock push button
            if(mDATRead(U1Bit, DATRfLockPush, Default) == cTrue)
            {
                if(mDATRead(U1Bit, EEP_CAR_SECURE, Default) == cTrue) 
                {
                    mSet(Arbitration, RfUnlockAllDoors);
                    DATRfMemorisePush(cDATRfDiagUnlockAll);
                }
                else
                {
                    mSet(Arbitration, RfLockAllDoors);
                    DATRfMemorisePush(cDATRfDiagLockAll);
                }
            }
            else
            {
                // no unlock button when EEP_KEY_BUTTON = 0
            }
        }
    }
    
    //****************************************************************************
    // Activation and deactivation of Lock With Speed (LWS)
    //****************************************************************************
    if (mDATRead(U1Bit, EEP_CONDAROU, Default) == cTrue) // prsFS_DLK-506
    {
        if ((mDATRead(U1Bit, PWR_IGN, Default) == cTrue) &&
            (mRead(Control, CDLButtonIsEnabled) != cFalse) )
        {
            if(mDATRead(U1Bit, EEP_CPE_IMPULS, Default) == cTrue) // CDL button with 2 positions 
            { 
                if (mRead(Control, Rising_DOOR_UNLOCK_LOCK_SW) == cTrue)
                {
                    if (mDATRead(U1Bit, EEP_CARCLIENT,Default) == cTrue)
                    {
                        TOSStartTempo(&LWSActivationTime); 
                        mReset(TimerControl, LWSActivationTimerIsStarted); 
                        mSet(TimerControl, LWSDeativationTimerIsStarted); 
                    }
                    else
                    {
                        TOSStartTempo(&LWSActivationTime); 
                        mSet(TimerControl, LWSActivationTimerIsStarted); 
                        mReset(TimerControl, LWSDeativationTimerIsStarted); 
                    }
                }
                
                if (   (mRead(TimerControl, LWSActivationTimerIsStarted) == cTrue) 
                    && (TOSIsTempoElapsed(&LWSActivationTime, mTOSConvMsEnTickHorloge(cLWSActivationTimeOut)) == cTrue)
                    && (mDATRead(U1Bit, DOOR_UNLOCK_SW, Default) == cTrue)  
                    )
                {
                    mDATWrite(U1Bit, EEP_CARCLIENT , cTrue, Default); // prsFS_DLK-514, prsFS_DLK-521
                    mDATWriteTable(U1Bit, BUZZER, eBUZZER_LockWithSpeed, cTrue, Default); // prsFS_DLK-522
                    mReset(TimerControl, LWSActivationTimerIsStarted); 
                }
                
                if (   (mRead(TimerControl, LWSDeativationTimerIsStarted) == cTrue) 
                    && (TOSIsTempoElapsed(&LWSActivationTime, mTOSConvMsEnTickHorloge(cLWSActivationTimeOut)) == cTrue)
                    && (mDATRead(U1Bit, DOOR_UNLOCK_SW, Default) == cTrue)  
                    )
                {
                    mDATWrite(U1Bit, EEP_CARCLIENT , cFalse, Default); // prsFS_DLK-520, prsFS_DLK-521
                    mDATWriteTable(U1Bit, BUZZER, eBUZZER_LockWithSpeed, cTrue, Default); // prsFS_DLK-522
                    mReset(TimerControl, LWSDeativationTimerIsStarted); 
                }
            }
            else // CDL button with 3 positions 
            {
                if (mRead(Control, Rising_DOOR_LOCK_SW) == cTrue)
                {
                    TOSStartTempo(&LWSActivationTime); 
                    mSet(TimerControl, LWSActivationTimerIsStarted); 
                    mReset(TimerControl, LWSDeativationTimerIsStarted); 
                }
                if (mRead(Control, Rising_DOOR_UNLOCK_LOCK_SW) == cTrue)
                {
                    TOSStartTempo(&LWSActivationTime); 
                    mReset(TimerControl, LWSActivationTimerIsStarted); 
                    mSet(TimerControl, LWSDeativationTimerIsStarted); 
                }
                
                if (   (mRead(TimerControl, LWSActivationTimerIsStarted) == cTrue) 
                    && (TOSIsTempoElapsed(&LWSActivationTime, mTOSConvMsEnTickHorloge(cLWSActivationTimeOut)) == cTrue)
                    && (mDATRead(U1Bit, DOOR_LOCK_SW, Default) == cTrue)  
                    )
                {
                    mDATWrite(U1Bit, EEP_CARCLIENT , cTrue, Default); // prsFS_DLK-516
                    mDATWriteTable(U1Bit, BUZZER, eBUZZER_LockWithSpeed, cTrue, Default); // prsFS_DLK-522
                    mReset(TimerControl, LWSActivationTimerIsStarted); 
                }
                
                if (   (mRead(TimerControl, LWSDeativationTimerIsStarted) == cTrue) 
                    && (TOSIsTempoElapsed(&LWSActivationTime, mTOSConvMsEnTickHorloge(cLWSActivationTimeOut)) == cTrue)
                    && (mDATRead(U1Bit, DOOR_UNLOCK_SW, Default) == cTrue)  
                    )
                {
                    mDATWrite(U1Bit, EEP_CARCLIENT , cFalse, Default); // prsFS_DLK-516
                    mDATWriteTable(U1Bit, BUZZER, eBUZZER_LockWithSpeed, cTrue, Default); // prsFS_DLK-522
                    mReset(TimerControl, LWSDeativationTimerIsStarted); 
                }
            }
        }
        else
        {
            mReset(TimerControl, LWSActivationTimerIsStarted); 
            mReset(TimerControl, LWSDeativationTimerIsStarted); 
        }
    }
    else
    {
        //nothing to-do: the LWS function can never be activated by the client
    }
    
    //****************************************************************************
    // Lock With Speed (LWS)
    //****************************************************************************
    if (TOSReadSignal(cTOSSignalFalling_PWR_IGN_LAP_DLK) == cTrue)  
    { 
        NbLWSOpenCloseDoor = 0; // prsFS_DLK-541
    }
    else
    {}
    
    //Update counter of open/close doors
    if ( (  //any door (with lock) closes
        (mRead(Control, Falling_FR_DOORS_SW_LAP_DLK) == cTrue)     // prsFS_DLK-539
        || (mRead(Control, Falling_RR_DOORS_SW_LAP_DLK) == cTrue) // prsFS_DLK-539
        )
        && (mDATRead(U8Bit, VEHICLE_SPEED, Default)             // prsFS_DLK-539
        > mDATRead(U8Bit, NEEP_SEUIL_VIT_CONDAROU, Default)) // prsFS_DLK-539
        && (NbLWSOpenCloseDoor <= (cNbLWSOpenCloseDoor)) 
        ) 
    {
        NbLWSOpenCloseDoor++; // prsFS_DLK-540
    }
    else  {} //nothing to do
    
    if (    ( mDATRead(U1Bit, EEP_CARCLIENT, Default) == cTrue )
        && ( mDATRead(U1Bit, EEP_CONDAROU, Default) == cTrue )   //LWS function is enabled
        && ( mRead(Control, LWSForbiddenByAirBagMalFunction) == cFalse ) //prsFS_DLK-547
        && ( mRead(Control, LWSForbiddenAfterCrash) == cFalse ) //prsFS_DLK-549 
       )
    {
        if (   ( mDATRead(U1Bit, PWR_IGN, Default) == cFalse ) // prsFS_DLK-417
            || ( mDATRead(U1Bit, ENGINE_RUNNING, Default) == 0 ) // prsFS_DLK-417
            || ( mRead(Control, KeyIsAuthenticated) == cFalse ) // prsFS_DLK-417
            || ( mDATRead(U8Bit, VEHICLE_SPEED, Default )
            <= mDATRead(U8Bit, NEEP_SEUIL_VIT_CONDAROU, Default)) // prsFS_DLK-526
            || (NbLWSOpenCloseDoor > cNbLWSOpenCloseDoor ) // prsFS_DLK-540
            || (   (mRead(Control, CarSecure) == cTrue)
            && (mRead(Control, LWSLockedWithOpenDoor) == cFalse) 
            ) // prsFS_DLK-417
            ) 
        { 
            //LockWithSpeed to be cancelled
            mReset(TimerControl, LockWithSpeedTimerIsArmed); 
            if(  (mDATRead(U8Bit, VEHICLE_SPEED, Default)
              <= mDATRead(U8Bit, NEEP_SEUIL_VIT_CONDAROU, Default))
               && (mRead(Control, AllDoorsAreClosed) == cFalse)
              )         
            {
                mSet(Control, LWSWithOpenDoorEnabled);
            }
            else //any other LWS cancel condition
            {
                mReset(Control, LWSWithOpenDoorEnabled);
            }
        } 
        //all condition are met
        else if( ( (mRead(TimerControl, LockWithSpeedTimerIsArmed) == cTrue)
                && (TOSIsTempoElapsed(&LockWithSpeedTime, mTOSConvMsEnTickHorloge(cLockWithSpeedTimeOut)) == cTrue)
                )
                || ((mRead(Control, LWSMustLockOverThreshold) == cTrue)
                    && (mRead(Control, AllDoorsAreClosed) == cTrue) 
                   )
               )
        {
            mReset(TimerControl, LockWithSpeedTimerIsArmed);
            mDATWrite(U1Bit, VehiculeHasBeenMoving, cTrue, Default);
            mSet(Control, LWSSpeedConditionsAreMet);
            if((mRead(Control, LWSWithOpenDoorEnabled) == cTrue)
               || (mRead(Control, AllDoorsAreClosed)== cTrue)
              )
            {
               mSet(Arbitration, LockWithSpeed);
               mReset(Control, LWSMustLockOverThreshold);
            }
            if(mRead(Control, AllDoorsAreClosed) == cFalse) //a door is open
            {
                mReset(Control, LWSWithOpenDoorEnabled);
            }
        }
        else if (  (mRead(Control, LWSSpeedConditionsAreMet) == cTrue)
                 &&(mRead(Control, LWSMustLockOverThreshold) == cTrue)
                )
        {
               mSet(Arbitration, LockWithSpeed);
               mReset(Control, LWSMustLockOverThreshold);
        }
        else if ((mRead(TimerControl, LockWithSpeedTimerIsArmed) == cFalse) 
                 && (mRead(Control, LWSNewConfirmationRequested) == cFalse)    
                )
        {       
            mSet(TimerControl, LockWithSpeedTimerIsArmed);
            TOSStartTempo(&LockWithSpeedTime);
        }
        else
        {} //wait for TimeOut
        
        if (   (mRead(Control,Rising_FR_DOORS_SW_LAP_DLK) == cTrue) 
            || (TOSReadSignal(cTOSSignalRising_RR_DOORS_SW_LAP_DLK) == cTrue )
            )
        {
            mSet(Control, LWSLockedWithOpenDoor); 
        }
        
        if (  (mRead(Control, LWSLockedWithOpenDoor) == cTrue )
            &&
            (   ( mRead(Control, Falling_FR_DOORS_SW_LAP_DLK) == cTrue )
            || ( mRead(Control, Falling_RR_DOORS_SW_LAP_DLK) == cTrue )
            )
           )
        {
            // Relock when a door is closed
            mSet(Control, LWSMustLockOverThreshold); 
        }
        
        if (mDATRead(U8Bit, VEHICLE_SPEED, Default)
            <= mDATRead(U8Bit, NEEP_SEUIL_VIT_CONDAROU, Default)) // prsFS_DLK-544
        {
            mReset(Control, LWSSpeedConditionsAreMet); 
            mReset(Control, LWSNewConfirmationRequested);
        }
        
    }
    else //function not authorized, reset all
    {
        mReset(TimerControl, LockWithSpeedTimerIsArmed);
        mReset(Control, LWSSpeedConditionsAreMet); 
    } 

    //****************************************************************************
    // Master Front Doors
    //****************************************************************************
    if (  (mDATRead(U1Bit, EEP_SDO, Default) == cFalse) // prsFS_DLK-570
        &&( (mRead(Control, KeyIsAuthenticated) == cTrue) ||
            (mRead(Control, LastRFActionIsUnlock) == cTrue)
          ) // prsFS_DLK-545
        &&(mRead(Control, Rising_FR_DOORS_SW_LAP_DLK ) == cTrue) // prsFS_DLK-544
        &&(mRead(Control, LWSSpeedConditionsAreMet ) == cFalse )// prsFS_DLK-544
        &&(
             (DLKLastCommandRequested == cCDLLock)        // prsFS_DLK-544 locked with CDL
           ||(DLKLastCommandRequested == cLockWithSpeed)  // prsFS_DLK-544 locked with LWS
          )
       )
    {
        mSet(Arbitration, CDLUnlock);
    }
    else
    {
        // MFD is inhibited
    }
    
    //Update flag VehiculeHasBeenMovingTime created for Diagnostic function:
    if(mDATRead(U1Bit, PWR_IGN, Default) == cFalse)
    { //reset flags
        mDATWrite(U1Bit, VehiculeHasBeenMoving, cFalse, Default);
        mReset(TimerControl, VehiculeHasBeenMovingTimerIsArmed);
    }
    else if(  ( mRead(TimerControl, VehiculeHasBeenMovingTimerIsArmed) == cTrue )
         && ( mDATRead(U8Bit, VEHICLE_SPEED, Default)
               <= mDATRead(U8Bit, NEEP_SEUIL_VIT_CONDAROU, Default) )
         )
    {
        mReset(TimerControl, VehiculeHasBeenMovingTimerIsArmed);
    }
    else if(  (TOSIsTempoElapsed( &VehiculeHasBeenMovingTime,
                               mTOSConvMsEnTickHorloge(cLockWithSpeedTimeOut) ) == cTrue)
         && ( mRead(TimerControl, VehiculeHasBeenMovingTimerIsArmed) == cTrue )
         )
    {
        mDATWrite(U1Bit, VehiculeHasBeenMoving, cTrue, Default);
        mReset(TimerControl, VehiculeHasBeenMovingTimerIsArmed);
    }
    else if(  ( mRead(TimerControl, VehiculeHasBeenMovingTimerIsArmed) == cFalse )
         && ( mDATRead(U8Bit, VEHICLE_SPEED, Default)
               > mDATRead(U8Bit, NEEP_SEUIL_VIT_CONDAROU, Default) )
         )
    {
        mSet(TimerControl, VehiculeHasBeenMovingTimerIsArmed);
        TOSStartTempo(&VehiculeHasBeenMovingTime);
    }
    else 
    {} //wait time out
    //end Diagnostic function

    mReset(Control, Rising_DOOR_UNLOCK_LOCK_SW);
    mReset(Control, Rising_DOOR_LOCK_SW);
    mReset(Control, Falling_FR_DOORS_SW_LAP_DLK);
    mReset(Control, Rising_FR_DOORS_SW_LAP_DLK);
    mReset(Control, Falling_RR_DOORS_SW_LAP_DLK);
    mReset(Control, Rising_PWR_IGN_LAP_DLK);
    mReset(Control, Rising_FR_DOORS_SW_LAP_DLK);
    mReset(Control, Changing_FR_DOORS_SW_LAP_DLK);
    mReset(Control, Changing_RR_DOORS_SW_LAP_DLK);
}

//--------------------------------------------------------------------------
// DESCRIPTION : DLKOutputDataManagement
//
// PARAMETERS (Type,Name,Min,Max) :   none
//  
// RETURN VALUE :   none
//    
// DESIGN INFORMATION :   refer to Detailed Design Document
//      
//--------------------------------------------------------------------------
void DLKOutputDataManagement(void)
{
#ifdef X90_PROJECT
    DLKOutputDataManagement_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DLKOutputDataManagement_Static(void)
{
#endif

    if ( (TOSIsTempoElapsed(&LedActivationTime, mTOSConvMsEnTickHorloge(cLedActivationTimeOut)) == cTrue) 
        && (mRead(TimerControl, LedActivationTimerIsStarted) == cTrue)
        )
    {
        mReset(TimerControl, LedActivationTimerIsStarted);
        LEDCommandRequested = cLEDOffRequested;
    }

    if (   (mDATRead(U1Bit, FR_DOORS_SW, Default) == cTrue)
        || (mDATRead(U1Bit, RR_DOORS_SW, Default) == cTrue)
        )
    {
        mReset(TimerControl, LedActivationTimerIsStarted);
        LEDCommandRequested = cLEDOffRequested;
    }
    
    if (LEDCommandRequested == cLEDOnRequested)
    {
        mDATWrite(U1Bit, OPEN_DOOR_LED, (U1)(cTrue), Default);
        mReset(TimerControl, LedActivationTimerIsStarted);

        mDATWrite(U1Bit, EEP_DoorlockLedActivation, cTrue, Default);
    }
    
    if (   (LEDCommandRequested == cLEDOneMinOnRequested )
        && (mRead(TimerControl, LedActivationTimerIsStarted) == cFalse) )
    {
        mDATWrite(U1Bit, OPEN_DOOR_LED, (U1)(cTrue), Default);
        mSet(TimerControl, LedActivationTimerIsStarted);
        TOSStartTempo(&LedActivationTime); 

        mDATWrite(U1Bit, EEP_DoorlockLedActivation, cTrue, Default);
    }

    
    if (LEDCommandRequested == cLEDOffRequested)
    {
        mDATWrite(U1Bit, OPEN_DOOR_LED, (U1)(cFalse), Default);
        mReset(TimerControl, LedActivationTimerIsStarted);

        mDATWrite(U1Bit, EEP_DoorlockLedActivation, cFalse, Default);
    }
    
    //****************************************************************************
    // For diagnostic purposes
    //****************************************************************************
    if(  (DLKLastCommandRequested == cRfUnlockAllDoors    )
       ||(DLKLastCommandRequested == cRfLockAllDoors     )
       ||(DLKLastCommandRequested == cRfUnlockDriverDoor )
       ||(DLKLastCommandRequested == cAutoRelock         )  
      )
    {
        mDATWrite(U1Bit, LastCommandOrigin, cTrue, Default);
    }
    else if (  (DLKLastCommandRequested == cCDLLock )
             ||(DLKLastCommandRequested == cCDLUnlock )
        )
    {
        mDATWrite(U1Bit, LastCommandOrigin, cFalse, Default);
    }
    else
    {
        // nothing to do
        // cCrashUnlock and cLockWithSpeed 
    }

    //****************************************************************************
    // For diagnostic purposes / Safety unlock control
    //****************************************************************************
    if(DLKLastCommandRequested == cLockWithSpeed)
    {
        mDATWrite(U1Bit, VehicleIsLockedWithSpeed, cTrue, Default);

        mSet(Control, SafetyUnlockAllowed);
    }
    else
    {
        mDATWrite(U1Bit, VehicleIsLockedWithSpeed, cFalse, Default);

        if (  (mRead(Control, SafetyUnlockAllowed) != cFalse)
            &&(DLKLastCommandRequested == cCDLLock))
        {
            // do not clear SafetyUnlockAllowed flag
        }
        else
        {
            mReset(Control, SafetyUnlockAllowed);
        }
    }

    //****************************************************************************
    // For diagnostic purposes
    //****************************************************************************
    if(DLKLastCommandRequested == cAutoRelock)
    {
        mDATWrite(U1Bit, VehicleIsAutoRelocked, cTrue, Default);
    }
    else
    {
        mDATWrite(U1Bit, VehicleIsAutoRelocked, cFalse, Default);
    }

    if ( (DLKLastCommandRequested == cCDLLock )
        || (DLKLastCommandRequested == cRfLockAllDoors )
        || (DLKLastCommandRequested == cLockWithSpeed )
        || (DLKLastCommandRequested == cAutoRelock )
       )
    {
        mDATWrite(U1Bit, LastOpeningPanelControl, cFalse, Default);
    }
    
    if ( (DLKLastCommandRequested == cCDLUnlock )
        || (DLKLastCommandRequested == cRfUnlockAllDoors )
        || (DLKLastCommandRequested == cCrashUnlock)
        || (DLKLastCommandRequested == cRfUnlockDriverDoor)
       )
    {
        mDATWrite(U1Bit, LastOpeningPanelControl, cTrue, Default);
    }

    //****************************************************************************
    // DOORLOCK LED / VERLOG LED HW protection
    //****************************************************************************
    DLKProtectionTask();

}
        
/* [GRAPH_FUNCTIONS_END] */

//=============================================================================
//  DESCRIPTION : Verlog LED Protection Callback for Sleep Mode
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//=============================================================================
void DLKProtectionSleepModeCallBack(void)
{
#ifdef X90_PROJECT
    static MEM_TYPE void DLKProtectionSleepModeCallBack_Static(void);
    DLKProtectionSleepModeCallBack_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DLKProtectionSleepModeCallBack_Static(void)
{
#endif
    
    // This function is called periodically synchronous with analog inputs 
    // reading in sleep mode (on 40 ms)

    // Flag for output turned on and unprotected:
    const BOOL bVerlogLedOn = (BOOL)
        (  (cFalse != mDATRead(U1Bit, VERLOG_LED, Default))
         &&(mDATRead(U1Bit, VERLOG_LEDProtection, Default) == cFalse) );

    if (bVerlogLedOn != cFalse)
    {
        // VERLOG LED active
        if (mDATRead(U1Bit, DIAG_DRIVER_ULQ_SCBat, Default) != cFalse)
        {
            // SC VERLOG LED found
            SetVerlogLedDefect();
        }
        else
        {
            // No SC
        }
    }
    else
    {
        // output not enabled or already protected
    }
}
        
//--------------------------------------------------------------------------
//  DESCRIPTION : DLKInitialize
//        
//  PARAMETERS (Type,Name,Min,Max) :   none
//          
//  RETURN VALUE :   none
//            
//  DESIGN INFORMATION :   refer to Detailed Design Document
//              
//--------------------------------------------------------------------------
void DLKInitialize(void)
{
#ifdef X90_PROJECT
    DLKInitialize_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DLKInitialize_Static(void)
{
#endif
    CommandRequested     = cNothingRequested;
    DLKLastCommandRequested = cNothingRequested;
    
    MotorPattern         = cRelayRestPosition;
    
    NbLWSOpenCloseDoor = 0;    //init for LockWithSpeed
    
    //Reset all flags
    DLKControlStatus.DLKControlFlags         = (U16)0;
    DLKArbitrationStatus.DLKArbitrationFlags = (U16)0;

    bPWR_IGNOld = cFalse;

    //Exceptions, flags to be set to cTrue:
    //for CentralDoorLockButton authorization
    mSet(Control, CDLButtonIsAuthorized);               // prsFS_DLK-455
    
    // after reset button shall be enabled
    mSet(Control, CDLButtonIsEnabled);
    
    TOSStopTempo(&LockWithSpeedTime);
    TOSStopTempo(&SevereAbuseTime);
    SevereAbuseTimeOut = 0;
    TOSStopTempo(&DebounceTime);
    TOSStopTempo(&MotorActivationTime);
    TOSStopTempo(&AutoRelockTime);
    TOSStopTempo(&CDLDebounceTime);
    TOSStopTempo(&LWSActivationTime);
    TOSStopTempo(&LedActivationTime);
    TOSStopTempo(&VehiculeHasBeenMovingTime);//for diagnostic
    TOSStopTempo(&SDOTimeOut);
   
    mReset(TimerControl, AutoRelockTimerIsArmed);
    mReset(TimerControl, VehiculeHasBeenMovingTimerIsArmed);
    mReset(TimerControl, CDLDebounceTimerIsStarted);
    mReset(TimerControl, LWSActivationTimerIsStarted);            
    mReset(TimerControl, LWSDeativationTimerIsStarted);         
    mReset(TimerControl, LockWithSpeedTimerIsArmed);               
    mReset(TimerControl, LedActivationTimerIsStarted);             
    mReset(TimerControl, AbuseTimerIsStarted);                    
    mReset(TimerControl, SDOTimerIsStarted);                    

    MotorActionCounter = 0;
    
    LEDCommandRequested = cLEDOffRequested;
}
        
//--------------------------------------------------------------------------
// DESCRIPTION         : DLKIsAnybodyMaintainActiveState
//        
// PARAMETERS (Type,Name,Min,Max) :   none
//          
// RETURN VALUE        : none
//            
// DESIGN INFORMATION  : Refer to Detailed Design Document
//              
//--------------------------------------------------------------------------
void DLKIsAnybodyMaintainActiveState(void)
{
    if (   ( mRead(TimerControl, AutoRelockTimerIsArmed) == cTrue )
        || ( mRead(Control, MotorsAreInOperation)   == cTrue )
        || ( mRead(TimerControl, LockWithSpeedTimerIsArmed) == cTrue )
        || ( mRead(TimerControl, AbuseTimerIsStarted) == cTrue ) 
        || ( mRead(TimerControl, LedActivationTimerIsStarted) == cTrue)
        || ( mRead(TimerControl, CDLDebounceTimerIsStarted) == cTrue)
        || ( mRead(TimerControl, LWSActivationTimerIsStarted) == cTrue)
        || ( mRead(TimerControl, LWSDeativationTimerIsStarted) == cTrue)
        || ( mRead(TimerControl, SDOTimerIsStarted) == cTrue)
        )
    {
        TOSWriteSignal(cTOSSignalSomebodyMaintainActiveState);
    }  
}

//--------------------------------------------------------------------------
// DESCRIPTION         : DLKEnterActiveState
//        
// PARAMETERS (Type,Name,Min,Max) :   none
//          
// RETURN VALUE        : none
//            
// DESIGN INFORMATION  : control coming from LAP_SUP
//              
//--------------------------------------------------------------------------
void DLKEnterActiveState(void)
{
    TOSSeqActivateGraph(cTOSSeqGraphIdDLKInputData);
    TOSSeqActivateGraph(cTOSSeqGraphIdDLKOutputData);
    TOSSeqActivateGraph(cTOSSeqGraphIdDLKMotorCommand);
    TOSSeqActivateGraph(cTOSSeqGraphIdDLKAirbagManagement);
    bPWR_IGNOld = cFalse;
}

//--------------------------------------------------------------------------
//  DESCRIPTION         : DLKLeaveActiveState
//        
//  PARAMETERS (Type,Name,Min,Max) :   none
//          
//  RETURN VALUE        : none
//            
//  DESIGN INFORMATION  : control coming from LAP_SUP
//              
//--------------------------------------------------------------------------
void DLKLeaveActiveState(void)
{
    TOSSeqDeactivateGraph(cTOSSeqGraphIdDLKInputData);
    TOSSeqDeactivateGraph(cTOSSeqGraphIdDLKOutputData);  
    TOSSeqDeactivateGraph(cTOSSeqGraphIdDLKMotorCommand);  
    TOSSeqDeactivateGraph(cTOSSeqGraphIdDLKAirbagManagement);
}
        
//--------------------------------------------------------------------------
// DESCRIPTION : DLKCommandCPERelay
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//--------------------------------------------------------------------------
void DLKCommandCPERelay(void)
{
    mReset(Control, NewCommandToBeDone); 
    TOSStartTempo(&MotorActivationTime);
}
        
//--------------------------------------------------------------------------
// DESCRIPTION : DLKCommandIsPending
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none 
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//--------------------------------------------------------------------------
BOOL DLKCommandIsPending(void)
{
#ifdef X90_PROJECT
    return DLKCommandIsPending_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL DLKCommandIsPending_Static(void)
{
#endif
    BOOL bReturnValueL;	 
    
    if (DLKArbitrationStatus.DLKArbitrationFlags == 0) 
    {
        bReturnValueL = cFalse;
    }
    else  //Command Is Pending
    {
        if( mRead(Arbitration, CrashUnlock) == cTrue) // CrashUnlock
        {
            CommandRequested = cCrashUnlock; 
        }
        else if (mRead(Arbitration, RfLockAllDoors) == cTrue) // RfLockAllDoors
        {
            CommandRequested = cRfLockAllDoors;
        }
        else if (mRead(Arbitration, RfUnlockAllDoors) == cTrue) // RfUnlockAllDoors
        {
            CommandRequested = cRfUnlockAllDoors;
        }
        else if (mRead(Arbitration, RfUnlockDriverDoor) == cTrue) // RfUnlockDriverDoor
        {
            CommandRequested = cRfUnlockDriverDoor;
        }
        else if (mRead(Arbitration, AutoRelock) == cTrue) //AutoRelock
        {
            CommandRequested = cAutoRelock; 
        }
        else if (mRead(Arbitration, LockWithSpeed) == cTrue) //LockWithSpeed
        {
            CommandRequested = cLockWithSpeed; 
        }
        else if (mRead(Arbitration, CDLUnlock) == cTrue) //CDLUnlock
        {
            CommandRequested = cCDLUnlock; 
        }
        else  //CDLLock
        {
            CommandRequested = cCDLLock; 
            mLIBassert(mRead(Arbitration, CDLLock) == cTrue);
        }
        
        //Update flags
        DLKArbitrationStatus.DLKArbitrationFlags = (U16)0;
        bReturnValueL = cTrue;
    }
    
    //****************************************************************************
    // SevereAbuse function
    //****************************************************************************
    if ( bReturnValueL == cTrue ) //a command is requested
    {
        if (  (MotorActionCounter < mDATRead(U8Bit, NEEP_NBCOM_MAX, Default)) 
            ||(CommandRequested == cCrashUnlock )	// prsFS_DLK-585
            || (   (mRead(Control, CarSecure) == cTrue) // prsFS_DLK-584
               && (   (CommandRequested == cRfUnlockAllDoors) 
                   || (CommandRequested == cRfUnlockDriverDoor) 
                   || (CommandRequested == cCDLUnlock) 
                  )
            )
            ) 
        {
            if (MotorActionCounter < mDATRead(U8Bit, NEEP_NBCOM_MAX, Default))
            {
                MotorActionCounter++;  // prsFS_DLK-581
            }
            else
            {} //nothing to do
            TOSStartTempo(&SevereAbuseTime);
            mSet(TimerControl, AbuseTimerIsStarted);
            mSet(Control, WaitLongSevereAbuseTimeOut);
            mSet(Control, MotorsAreInOperation);
        }
        else // No motor actions are authorized
        {
            // prsFS_DLK-582
            CommandRequested = cNothingRequested; 
            //Restart timer

            TOSStartTempo(&SevereAbuseTime);
            mSet(TimerControl, AbuseTimerIsStarted);
            mSet(Control, WaitLongSevereAbuseTimeOut);
       }
    }

    //Set TimeOut value
    if( mRead(Control, WaitLongSevereAbuseTimeOut) == cFalse )
    {
        SevereAbuseTimeOut = mReadSevereAbuseTimeOutShortTicks();
    }
    else
    {
        SevereAbuseTimeOut = mReadSevereAbuseTimeOutLongTicks();
    }
    
    //Verify TimeOut to decrease counter if need to be
    if (  (mRead(TimerControl, AbuseTimerIsStarted) == cTrue)
        &&(TOSIsTempoElapsed(&SevereAbuseTime, SevereAbuseTimeOut) == cTrue)
       )
    {
        mReset(Control, WaitLongSevereAbuseTimeOut);
        TOSStartTempo(&SevereAbuseTime);
        mSet(TimerControl, AbuseTimerIsStarted);
        if(MotorActionCounter >0)
        {
            MotorActionCounter--;
        }
        else
        {
            mReset(TimerControl, AbuseTimerIsStarted);
        } //nothing to do
    }
    else
    {} 
    
    return bReturnValueL;
}
        
//--------------------------------------------------------------------------
// DESCRIPTION : DLKCommandMotorRelays
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//--------------------------------------------------------------------------
void DLKCommandMotorRelays(void)
{
#ifdef X90_PROJECT
    DLKCommandMotorRelays_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DLKCommandMotorRelays_Static(void)
{
#endif
    //****************************************************************************
    // CDLButton Is Authorized/Inhibitted
    //****************************************************************************
    //Update flag CDLButtonIsAuthorized
    if (   (CommandRequested == cRfUnlockAllDoors )         // prsFS_DLK-457
        || (CommandRequested == cRfUnlockDriverDoor )       // prsFS_DLK-457 
        )
    { 
        // forbidden -> authorized   
        mSet(Control, CDLButtonIsAuthorized); 
    }
    else if (   (CommandRequested == cAutoRelock)      // prsFS_DLK-456
        || (CommandRequested == cRfLockAllDoors)       // prsFS_DLK-456    
        ) 
    {
        // authorized -> forbidden    
        mReset(Control, CDLButtonIsAuthorized); 
    }
    else 
    {} //nothing to do
    
    
    if (CommandRequested != cNothingRequested)
    {
        DLKLastCommandRequested = CommandRequested;
    }
    else
    {} //nothing to do because code is "no request"
    
    
    //****************************************************************************
    // Rearm AutoRelock function
    //****************************************************************************
    if (mDATRead(U1Bit, EEP_CONDATMPO, Default) == cTrue) // AutoRelock function is enabled
    {
        if( (
              (CommandRequested == cRfUnlockAllDoors) ||                 // prsFS_DLK-500
              (CommandRequested == cRfUnlockDriverDoor)
            ) 
            && (mDATRead(U1Bit, FR_DOORS_SW, Default) == cFalse)        // prsFS_DLK-500
            && (mDATRead(U1Bit, RR_DOORS_SW, Default) == cFalse)        // prsFS_DLK-500 
            )  
        {
            //Rearm AutoRelock timer if RfUnlock with all doors closed
            TOSStartTempo(&AutoRelockTime);
            mSet(TimerControl, AutoRelockTimerIsArmed);
        }
    }
    else {} //nothing to do
    
    //MotorPattern = cRelayRestPosition;
    switch(CommandRequested)
    {
        //****************************************************************************
        // Crash Unlock
        //****************************************************************************
    case cCrashUnlock:  //graph must be the last, just before Command graph
        MotorPattern = cUnlockAll;
        CommandRequested = cNothingRequested; 
        LEDCommandRequested = cLEDOffRequested; // prsFS_DLK-562
        break;
        
        //****************************************************************************
        // AutoRelock
        //****************************************************************************
    case cAutoRelock :  //flasher pattern
        // Cm006153:According to IR_A43, when the vehicle is locked following 
        // an auto relock, No flashing feedback requested
        TOSSendControl(cTOSControlAutoRelock); 
        MotorPattern = cLockAll;
        CommandRequested = cNothingRequested; 
        LEDCommandRequested = cLEDOneMinOnRequested; // prsFS_DLK-567
        break;
        
        //****************************************************************************
        // CDLLock
        //****************************************************************************
    case cCDLLock : //no flasher pattern to be requested 
        MotorPattern = cLockAll; // prsFS_DLK-469
        CommandRequested = cNothingRequested;
        if (mRead(Control, AllDoorsAreClosed) == cTrue)
        {
            LEDCommandRequested = cLEDOnRequested; // prsFS_DLK-564
        }
        break;
        
        //****************************************************************************
        // CDLUnlock
        //****************************************************************************
    case cCDLUnlock :   //no flasher pattern to be requested
        MotorPattern = cUnlockAll; // prsFS_DLK-470 
        CommandRequested = cNothingRequested;
        LEDCommandRequested = cLEDOffRequested; // prsFS_DLK-562
        break;
        
        //****************************************************************************
        // LockWithSpeed
        //****************************************************************************
    case cLockWithSpeed : //no flasher pattern to be requested
        MotorPattern = cLockAll; 
        CommandRequested = cNothingRequested;
        if (mRead(Control, AllDoorsAreClosed) == cFalse)
        {  	
            mSet(Control, LWSLockedWithOpenDoor);
        }
        else
        {
            mReset(Control, LWSLockedWithOpenDoor);
        }
        LEDCommandRequested = cLEDOnRequested; // prsFS_DLK-565
        break;
        
        //****************************************************************************
        // RfLockAllDoors
        //****************************************************************************
    case cRfLockAllDoors :
        if (mRead(Control, AllDoorsAreClosed) == cTrue)
        {
            // prsFS_DLK-488
            TOSSendControl(cTOSControlRKE_LOCK_REQUEST); // flashing feedback is requested  
            LEDCommandRequested = cLEDOneMinOnRequested; // prsFS_DLK-566
        }
        else
        {
            // prsFS_DLK-492
            // nothing to do
        }
        MotorPattern = cLockAll;
        CommandRequested   = cNothingRequested;
        mReset(Control, LastRFActionIsUnlock);
        break;
        
        //****************************************************************************
        // RfUnlockAllDoors
        //****************************************************************************
    case cRfUnlockAllDoors :         
        if (mRead(Control, AllDoorsAreClosed) == cTrue)
        {
            // prsFS_DLK-490
            TOSSendControl(cTOSControlRKE_UNLOCK_REQUEST); // flashing feedback is requested 
        }
        else
        {
            // prsFS_DLK-492
            // nothing to do
        }
        MotorPattern = cUnlockAll;
        CommandRequested   = cNothingRequested;
        LEDCommandRequested = cLEDOffRequested; // prsFS_DLK-562
        mSet(Control, LastRFActionIsUnlock);
        break;
        
        //****************************************************************************
        // RfUnlockDriverDoor
        //****************************************************************************
    case cRfUnlockDriverDoor :         
        TOSSendControl(cTOSControlRKE_UNLOCK_REQUEST); // flashing feedback is requested
        MotorPattern = cUnlockDriverDoor;
        CommandRequested   = cNothingRequested;
        LEDCommandRequested = cLEDOffRequested; // prsFS_DLK-562
        mSet(Control, LastRFActionIsUnlock);
        break;
        
    default:
        MotorPattern = cRelayRestPosition;
        break;
    } //end switch (CommandRequested)
    
    //****************************************************************************
    // Motor Commands
    //****************************************************************************
    if (MotorPattern == cLockAll)
    {
        mDATWrite(U1Bit, LOCK_DOORS, (U1)(cTrue), Default);
    }

    if (MotorPattern == cUnlockAll)
    {
        // wrong spec (see TCR Cm004888)
        mDATWrite(U1Bit, UNLOCK_DOORS, (U1)(cTrue), Default);
        mDATWrite(U1Bit, UNLOCK_DRIVER_DOOR, (U1)(cTrue), Default);
    }
    
    if (MotorPattern == cUnlockDriverDoor)
    {
        mDATWrite(U1Bit, UNLOCK_DRIVER_DOOR, (U1)(cTrue), Default);
    }
    
    if(mRead(Control, LWSSpeedConditionsAreMet) == cTrue) //prsFS_DLK-529
    {
       mSet(Control, LWSNewConfirmationRequested);   
    }
    else
    {
       mReset(Control, LWSNewConfirmationRequested);   
    }

    mSet(Control, NewCommandToBeDone); 
    TOSStartTempo(&DebounceTime);
}

//--------------------------------------------------------------------------
// DESCRIPTION : DLKDeCommandMotorRelays
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//--------------------------------------------------------------------------
void DLKDeCommandMotorRelays(void)
{
#ifdef X90_PROJECT
    DLKDeCommandMotorRelays_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DLKDeCommandMotorRelays_Static(void)
{
#endif
    //All relays off
    mDATWrite(U1Bit, LOCK_DOORS, (U1)(0), Default);
    mDATWrite(U1Bit, UNLOCK_DOORS, (U1)(0), Default);
    mDATWrite(U1Bit, UNLOCK_DRIVER_DOOR, (U1)(0), Default);
    
    if (TOSReadSignal(cTOSSignalCrashUnlockStarted) != cFalse)
    {
        TOSSendControl(cTOSControlCrashUnlockFinished);
        // Start flashers crash unlock signalization
        
        mSet(Control, LWSForbiddenAfterCrash);
        // flag is reset after BCM reset with APC on: it is set again for that case
    }

    //****************************************************************************
    // CAR_SECURE
    //****************************************************************************
    if (MotorPattern == cLockAll) // prsFS_DLK-497, prsFS_DLK-487
    {
        mSet(Control, CarSecure);
    }
    else if (MotorPattern == cUnlockAll)  // prsFS_DLK-470, prsFS_DLK-491
    {
        mReset(Control, CarSecure);
    }
    //CCOV: ailievb: Cannot be covered in normal operating conditions,
    else if ( MotorPattern == cUnlockDriverDoor)
    {
        
        mReset(Control, CarSecure);
    }
    else
    {
        mLIBassert(cFalse);
    }

    if (  (DLKLastCommandRequested == cRfLockAllDoors)         // prsFS_DLK-487
        ||(DLKLastCommandRequested == cAutoRelock)             // prsFS_DLK-497  
       )
    {
        mDATWrite(U1Bit, EEP_CAR_SECURE, cTrue, Default);
        TOSSendControl(cTOSControlRfLockAllForAlarm); // Control for Alarm
    }
    else if (  (DLKLastCommandRequested == cRfUnlockAllDoors)    // prsFS_DLK-491  
             ||(DLKLastCommandRequested == cRfUnlockDriverDoor) 
            ) 
    {
        mDATWrite(U1Bit, EEP_CAR_SECURE, cFalse, Default);
        TOSSendControl(cTOSControlRfUnlockAllForAlarm); // Control for Alarm
    }
    mReset(Control, MotorsAreInOperation); //to authorise Sleep
}

//--------------------------------------------------------------------------
// DESCRIPTION : DLKDebounceTimeOut
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none 
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//--------------------------------------------------------------------------
BOOL DLKDebounceTimeOut(void)
{
    //StabilizationTime = 10ms when connecting and 1ms when disconnecting
    //due to hardware restrictions and to avoid sparks
    return( TOSIsTempoElapsed(&DebounceTime,  mTOSConvMsInTimerTick(cDebounceTimeOut) - (tTOSTimer)1U) == cTrue );
}

//--------------------------------------------------------------------------
// DESCRIPTION : DLKMotorActivationTimeOut
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none 
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//--------------------------------------------------------------------------
BOOL DLKMotorActivationTimeOut(void)
{
    tTOSTempo TimeoutTicksL = mReadMotorActivationTimeoutTicks();
    BOOL bResultL = TOSIsTempoElapsed(&MotorActivationTime, TimeoutTicksL);

    return bResultL;
}

//--------------------------------------------------------------------------
// DESCRIPTION : DLKNoRequest
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none 
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//--------------------------------------------------------------------------
BOOL DLKNoRequest(void)
{
    BOOL bReturnValueL;
    
    if (MotorPattern == cRelayRestPosition)
    {
        mReset(Control, MotorsAreInOperation); //to authorise Sleep
        bReturnValueL = cTrue;
    }
    else
    {
        bReturnValueL = cFalse;
    }
    
    return(bReturnValueL);
}

//--------------------------------------------------------------------------
// DESCRIPTION :      DLKUpdateByVerlogOfKeyIsAuthenticated
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none 
//
// DESIGN INFORMATION : control coming from carimmo:KeyIsAuthenticated
//--------------------------------------------------------------------------
void DLKUpdateByVerlogOfKeyIsAuthenticated(void)
{
    mSet(Control, KeyIsAuthenticated);
}

//--------------------------------------------------------------------------
// DESCRIPTION : DLKAirbagInformationManagement
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//--------------------------------------------------------------------------
void DLKAirbagInformationManagement(void)
{
#ifdef X90_PROJECT
    DLKAirbagInformationManagement_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DLKAirbagInformationManagement_Static(void)
{
#endif
    BOOL bCrashByAirbagL;
    U8 u8CrashCountL;
    bCrashByAirbagL =   (BOOL)(TOSReadSignal(cTOSSignalCrashIsDetectedByAirbag) == cTrue); //crash coming from serial line
    
    if ((bCrashByAirbagL == cTrue) && 
        (mRead(Control, LWSForbiddenAfterCrash) == cFalse) ) // prsFS_DLK-757
    {
        // prsFS_DLK-549: Crash
        mSet(Arbitration, CrashUnlock);
        mDATWrite(U1Bit, EEP_CrashHazardIsRequested, cTrue, Immediate);
        mSet(Control, LWSForbiddenAfterCrash);
        TOSWriteSignal(cTOSSignalCrashUnlockStarted); // Cm006968

        // crash counter
        u8CrashCountL = mDATRead(U8Bit, EEP_CrashCount, Default);
        if (u8CrashCountL < cMaxU8)
        {
            mDATWrite(U8Bit, EEP_CrashCount, (u8CrashCountL + (U8)1U), Default);
        }
    }
    else if (mDATRead(U1Bit, DefAirbag, Default) == cTrue) //malfunction serial line
        //airbag malfunction
    {
        if (mRead(Control, AirBagMalFunctionDetected) == cFalse) //to detect a raising edge
        {
            mSet(Control, AirBagMalFunctionDetected);

            if (mRead(Control, SafetyUnlockAllowed) != cFalse) //Cm006989, Cm007440
            {
                mSet(Control, LWSForbiddenByAirBagMalFunction);
                mSet(Arbitration, CrashUnlock); // Safety unlock
            }
            else
            {
                // do not perform safety unlock
            }
        }
        else
        {
            // do nothing
        }
    }
    else
    {
        mReset(Control, AirBagMalFunctionDetected);
    }
}

//--------------------------------------------------------------------------
// DESCRIPTION : DLKIgnitionIsOff
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none 
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//--------------------------------------------------------------------------
BOOL DLKIgnitionIsOff(void)
{
    return( (BOOL)(   (mDATRead(U1Bit, EEP_AUTCRASH, Default) == cFalse) // prsFS_DLK-423
        || (mDATRead(U1Bit, PWR_IGN, Default) == cFalse) // prsFS_DLK-558
        )
        );
}

//--------------------------------------------------------------------------
// DESCRIPTION : DLKStopAirbag
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//--------------------------------------------------------------------------
void DLKStopAirbag(void)
{
    mDATControl(Rbag, Stop);
    mReset(Control, AirBagMalFunctionDetected);
}

//--------------------------------------------------------------------------
// DESCRIPTION : DLKIgnitionIsOnAndKeyWasRecognizedAndLWS
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none 
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//--------------------------------------------------------------------------
BOOL DLKIgnitionIsOnAndKeyWasRecognizedAndLWS(void)
{ 
    return( (BOOL)(   (mDATRead(U1Bit, EEP_AUTCRASH, Default) == cTrue) // prsFS_DLK-423
        && (mDATRead(U1Bit, PWR_IGN, Default) == cTrue) // prsFS_DLK-558
        && (mRead(Control, KeyIsAuthenticated) == cTrue) // prsFS_DLK-558
        )
        );
}

//==============================================================================
// DESCRIPTION : DLKStartAirbag
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
void DLKStartAirbag(void)
{
    mDATControl(Rbag, Start);
    TOSReadSignal(cTOSSignalCrashIsDetectedByAirbag); //crash coming from serial line
}

//==============================================================================
// DESCRIPTION : DLKLeaveStartingStepState
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
void DLKLeaveStartingStepState(void)
{
#ifdef X90_PROJECT
    static MEM_TYPE void DLKLeaveStartingStepState_Static(void);
    DLKLeaveStartingStepState_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DLKLeaveStartingStepState_Static(void)
{
#endif

    if ( mDATRead(U1Bit, EEP_CAR_SECURE, Default) == cTrue)
    {
        mSet(Control, CarSecure);
    }
    else
    {
        mReset(Control, CarSecure);
    }
    
    if ( mDATRead(U1Bit, EEP_CrashHazardIsRequested, Default) == cTrue)
    {
        mSet(Arbitration, CrashUnlock);
        TOSSendControl(cTOSControlWakeUpRequest);
        TOSWriteSignal(cTOSSignalCrashUnlockStarted); // Cm006968
    }

    // Cm006152: DLK: IR_A07 according to Cm006108
    //doorlock LED after power ON reset is set according to EEP flag
    if (mDATRead(U1Bit, EEP_DoorlockLedActivation, Default) != cFalse)
    {
        LEDCommandRequested = cLEDOnRequested;
        mDATWrite(U1Bit, OPEN_DOOR_LED, cTrue, Immediate);
    }
    else
    {
        // Nothing to do: LED is off by default
    }
}

/* [EXPORTED_FUNCTIONS_END] */

