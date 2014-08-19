//******************************************************************************
// Company:      Johnson Controls Inc.
// -----------------------------------------------------------------------------
// Copyright:    This software is JCI property.
//               Duplication or disclosure without JCI written authorization
//               is prohibited.
// -----------------------------------------------------------------------------
// Project:      STK
// Language:     ANSI-C
// -----------------------------------------------------------------------------
// Component:    TOS
//               TOS management
// -----------------------------------------------------------------------------
// $Date:   Sep 17 2009 10:27:12  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/EXT_CMP/CPP_CMP/STK/SOURCES/TOS.H-arc  $
// $Revision:   1.1  $
// -----------------------------------------------------------------------------
/* $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/EXT_CMP/CPP_CMP/STK/SOURCES/TOS.H-arc  $
// 
//    Rev 1.1   Sep 17 2009 10:27:12   adzhelp
// Cm003277: Functions defined as CALLT_TYPE
// 
//    Rev 1.0   04 Feb 2009 17:03:04   adzhelp
// Initial revision.
*/
//******************************************************************************

#ifndef I_TOS_H
#define I_TOS_H

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------
#include "deftypes.h"
#include "tosparam.h"
#include "ldb.h"
#include "tos_seq.h"

//------------------------------------------------------------------------------
// Constant data
//------------------------------------------------------------------------------

// ---- obsolete services and type translation
#ifndef TOS_DO_NOT_USE_OBSOLETE_SERVICES

#define TOSTempoPeriodiqueEcoulee   TOSIsPeriodicTimerElapsed
#define TOSTempoPeriodiqueActive    TOSIsPeriodicTimerStarted
#define TOSTempoEcoulee             TOSIsTimerElapsed
#define TOSTempoActive              TOSIsTimerStarted
#define TOSStopPeriodicTempo        TOSStopPeriodicTimer
#define TOSStopTempo                TOSStopTimer
#define TOSStartPeriodicTempo       TOSStartPeriodicTimer
#define TOSStartTempo               TOSStartTimer
#define TOSIsTempoElapsed           TOSIsTimerElapsed
#define TOSIsTempoActiv             TOSIsTimerStarted
#define TOSIsPeriodicTempoElapsed   TOSIsPeriodicTimerElapsed
#define TOSIsPeriodicTempoActiv     TOSIsPeriodicTimerStarted
#define TOSHorlogeSysteme           TOSClock
#define TOSGetTempoValue            TOSGetTimerElapsedTime
#define TOSDureeEcoulee             TOSGetTimerElapsedTime
#define TOSArreterTempoPeriodique   TOSStopPeriodicTimer
#define TOSArreterTempo             TOSStopTimer
#define TOSArmerTempoPeriodique     TOSStartPeriodicTimer
#define TOSArmerTempo               TOSStartTimer
#define TOSPositionnerSignal        TOSWriteSignal
#define TOSLireSignal               TOSReadSignal

#define tTOSTempo                   tTOSTimer
#define tTOSTempoPeriodique         tTOSPeriodicTimer
#define tTOSHorlogeSysteme          tTOSClock

#define mTOSConvMsEnTickHorloge     mTOSConvMsInTimerTick
#define mTOSConvMsEnTickAlarm       mTOSConvMsInAlarmTick
#define mTOSConvUsEnTickAlarm       mTOSConvUsInAlarmTick

#define cTOSTickHorlogeMs           cTOSTimerTickMs
#define cTOSTempoNonArmee           cTOSTempoNotStarted

#define cTOSTempoLdbUtiliseeParALA  cTOSTimerLdbDesignedForALA

#endif
// ---- end of translation


//----- Tempo management -----
#define cTOSTempoNotStarted     ((tTOSTimer)0UL)

//----- Resources management -----
#ifdef TOS_PREEMPTIVE
  #define cTOSResourceScheduler   ((U8)255UL)
#endif

#if cTOSMaxControlNumber < 0xFFUL
typedef U8 tTOSControl;
#define cTOSControlInvalidValue ((tTOSControl)0xFFUL)
#else
  #if cTOSMaxControlNumber < 0xFFFFUL
typedef U16 tTOSControl;
#define cTOSControlInvalidValue ((tTOSControl)0xFFFFUL)
  #else
    #if cTOSMaxControlNumber < 0xFFFFFFFFUL
typedef U32 tTOSControl;
#define cTOSControlInvalidValue ((tTOSControl)0xFFFFFFFFUL)
    #else
        #error "Unable to manage more than 4294967294 Control"
    #endif
  #endif
#endif

//------------------------------------------------------------------------------
// Exported Macros
//------------------------------------------------------------------------------

// convert a time duration (micro or mili seconds)
// into a number of alarm ticks
#define mTOSConvUsInAlarmTick(x) \
            ((tTOSTickAlarm) ( (x) / cTOSTickAlarmUs) )
#define mTOSConvMsInAlarmTick(x)  \
            ((tTOSTickAlarm) ( ((U32)((U32)1000UL) * (x)) / cTOSTickAlarmUs) )

// convert a time duration into a number of clock ticks
#define mTOSConvMsInTimerTick(x)   ((tTOSTimer) ( (x) / cTOSTimerTickMs))


#define TOSSetRelAlarm( pAlarm, Increment, Cycle ) \
  TOSSetRelAlarm_Interne( pAlarm, Cycle )

#define TOSStartPeriodicTimer(pTempo, P, Delay)   \
    (pTempo)->Period = (P);                           \
    TOSStartPeriodicTimer_Internal( (pTempo), (Delay)  )

#define TOSAlaInitialiser()                   TOSAlaInitialize()

//----- TOS management -----
#define TOSInit()               TOSInitialize();
#define TOSInitialize()         TOSSendControl(cTOSControlTOSInitialize);

#define TOSStart(Mode)          TOSInternalStart()
#define TOSGetApplicationMode() cTOSDefaultMode //For OSEK API compatibility

//----- Tasks management -----
#ifdef TOS_PREEMPTIVE
#ifdef DEBUG   /* SOFT_REQ_TOS_ORD_008 */
#define TOSTerminateTask()                              \
    TOSDisableOSInterrupts();                           \
    mLIBassert(TOSInternalForbiddenPreemptLev == TOSForbiddenPreemptLevelList[TOSInternalRunningTaskId]);\
    TOSEnableOSInterrupts();                            \
    return
#else
#define TOSTerminateTask() return
#endif

#define TOSChainTask(TaskId)  TOSActivateTask(TaskId);        \
                              TOSTerminateTask()
#else
#define TOSTerminateTask() return

#define TOSChainTask(TaskId)  TOSActivateTask(TaskId);        \
                              TOSTerminateTask()
#endif

//----- Resources management services -----
#ifdef TOS_PREEMPTIVE
    #define TOSGetSchedulerResource()     TOSGetResource(cTOSResourceScheduler)
    #define TOSReleaseSchedulerResource() TOSReleaseResource(cTOSResourceScheduler)
#endif


//----- Scheduler management -----
#if (cTOSBusInteger == 8UL)
  #define cTOSLogBusInteger     3UL
#elif (cTOSBusInteger == 16UL)
  #define cTOSLogBusInteger     4UL
#elif (cTOSBusInteger == 32UL)
  #define cTOSLogBusInteger     5UL
#else
  #error "cTOSBusInteger not or bad defined"
#endif

#ifdef TOS_PREEMPTIVE
// 1) Assert that resources are released
// 2) Decrease priority for enable scheduling in the group
// 3) Call TOSOrdInternalSchedule
// 4) Increase priority for disable scheduling in the group
  #define  TOSSchedule()                              \
    TOSDisableOSInterrupts();                         \
    mLIBassert(TOSInternalForbiddenPreemptLev == TOSForbiddenPreemptLevelList[TOSInternalRunningTaskId]);\
    TOSInternalForbiddenPreemptLev = TOSInternalRunningTaskId;\
    TOSOrdInternalSchedule();\
    TOSInternalForbiddenPreemptLev = TOSForbiddenPreemptLevelList[TOSInternalRunningTaskId];\
    TOSEnableOSInterrupts()
#endif

#define TOSGetTaskId() ((tTOSTaskID)TOSInternalRunningTaskId)  // Cast used for discard volatile type

//------------------------------------------------------------------------------
// Exported type
//------------------------------------------------------------------------------
//----- Define the IT state type -----
typedef U8 tTOSItState;

//----- Scheduler management -----
#if (cTOSBusInteger == 8UL)
typedef U8 tTOSBusInteger;
#elif (cTOSBusInteger == 16UL)
typedef U16 tTOSBusInteger;
#elif (cTOSBusInteger == 32UL)
typedef U32 tTOSBusInteger;
#else
  #error "cTOSBusInteger not or bad defined"
#endif

//----- Task ident -----
#define cTOSNbTask ((tTOSTaskID)cTOSMaxTaskNumber)
#ifndef TOS_PREEMPTIVE
  #if   (cTOSMaxTaskNumber <= 9U)
typedef U8 tTOSTaskID;
  #elif (cTOSMaxTaskNumber <= 17U)
typedef U16 tTOSTaskID;
  #elif (cTOSMaxTaskNumber <= 33U)
typedef U32 tTOSTaskID;
  #else
    #error "The maximum task number is reached"
  #endif
#endif

typedef void (*tpTOSTaskFct)(void);
typedef tpTOSTaskFct tTOSTask;

#ifdef TOS_PREEMPTIVE
//----- Scheduler management
typedef tTOSBusInteger    tTOSPriorityLevel;
typedef tTOSPriorityLevel tTOSTaskID;

//----- Resources management -----
typedef tTOSPriorityLevel tTOSResourceId;
#endif

//----- Control ident -----
typedef U8 tTOSControlId;

// Tick defined for an alarm object
typedef U8 tTOSTickAlarm;

// Alarm type
typedef struct
{
    tTOSTaskID     TaskID;
    tTOSTickAlarm  Period;
} tTOSAlarm;

typedef tTOSAlarm* tTOSAlarmType;
typedef tTOSClock tTOSTimer;

// Periodic tempo type
typedef struct
{
    tTOSTimer StartDate;
    tTOSTimer Period;
} tTOSPeriodicTimer;

//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------
// System clock
extern tTOSClock TOSClock;

//----- Scheduler management -----
#ifdef TOS_PREEMPTIVE
extern volatile tTOSPriorityLevel    TOSInternalForbiddenPreemptLev;
extern volatile tTOSTaskID           TOSInternalRunningTaskId;
#endif

//------------------------------------------------------------------------------
// Constant exported data
//------------------------------------------------------------------------------
extern const tTOSTask           TOSTaskList[cTOSNbTask];
#ifdef TOS_PREEMPTIVE
extern const tTOSPriorityLevel  TOSForbiddenPreemptLevelList[cTOSNbTask];
#endif

//------------------------------------------------------------------------------
// Exported functions
//------------------------------------------------------------------------------
//----- Interrupt management services -----
#ifdef TOS_PREEMPTIVE
extern void       TOSEnterISR(void);
extern void       TOSLeaveISR(void);
#endif

#ifdef USE_DISABLE_ALL_INTERRUPTS
extern void       TOSResumeAllInterrupts(void);
extern void       TOSSuspendAllInterrupts(void);
#endif

extern void       TOSSuspendOSInterrupts(void);
extern void       TOSResumeOSInterrupts(void);

//----- Tasks management services -----
#ifdef TOS_PREEMPTIVE
extern void       TOSOrdInternalSchedule(void); // Don't use this function,
#else
extern void       TOSSchedule(void);
#endif
// you must use TOSSchedule()
extern void       TOSActivateTask(const tTOSTaskID TaskId);

//Idle mode
extern void       TOSHalt(void);

//----- Resources management services -----
#ifdef TOS_PREEMPTIVE
extern void       TOSGetResource(const tTOSResourceId ResourceId);
extern void       TOSReleaseResource(const tTOSResourceId ResourceId);
#endif

//----- TOS management services -----
extern void       TOSShutdown(const U16 u16ErrorCode);
extern void       TOSInternalStart(void);

extern  void      LAPStartupHook(void);
extern  void      LAPShutdownHook(U16 u16ErrorCode);

//----- Alarm management services -----
extern void       TOSStartAlarm(void);
extern void       TOSStopAlarm(void);
extern void       TOSStartSlowestAlarms(const tTOSTickAlarm MinimumCycle);
extern void       TOSCancelAlarm(const tTOSAlarm* const pAlarm);

// This function is obsolete and must not be used. Use instead the macro
// TOSSetRelAlarm( pAlarm, Increment, Cycle ) with increment parameter equal to zero
extern void       TOSSetRelAlarm_Interne(tTOSAlarmType const pAlarm, const tTOSTickAlarm Cycle);


// "Timer" management services
extern CALLT_TYPE void       TOSStartTimer(tTOSTimer* const pTimer);
extern CALLT_TYPE void       TOSStopTimer(tTOSTimer* const pTimer);
extern BOOL       TOSIsTimerStarted(const tTOSTimer* const pTimer);
extern CALLT_TYPE BOOL       TOSIsTimerElapsed(tTOSTimer* const pTimer, const tTOSTimer Timeout);
extern tTOSTimer  TOSGetTimerElapsedTime(const tTOSTimer* const pTimer);
extern void       TOSClockTask(void);

// This function is obsolete and must not be used. Use instead the macro TOSStartPeriodicTimer
extern void       TOSStartPeriodicTimer_Internal(
                                                 tTOSPeriodicTimer* const pTimer,
                                                 const tTOSTimer Delay
                                                );

extern void       TOSStopPeriodicTimer(tTOSPeriodicTimer* const pTimer);
extern BOOL       TOSIsPeriodicTimerStarted(const tTOSPeriodicTimer* const pTimer);
extern BOOL       TOSIsPeriodicTimerElapsed(tTOSPeriodicTimer* const pTimer);

#ifdef USE_DISABLE_TOSTIMER
extern void       TOSEnableTimer(const U8 u8Period);
extern void       TOSDisableTimer(void);
#endif

// "Signal" management services (TOS_SIG services)
// A signal is an object used to signal the occurance of one event
// See english translation of those services in macro declaration
#ifdef USE_TOS_SIG
extern CALLT_TYPE void       TOSWriteSignal(const tTOSSignalID SignalId);
extern CALLT_TYPE BOOL       TOSReadSignal(const tTOSSignalID SignalId);
#endif

// "Control flow" service (JIL tool)
//==============================================================================
// DESCRIPTION:         Sets a signal
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  This service is used from one component to send a control
//                      to an other one
//                      Refer to Detailed Design Document
//==============================================================================
CALLT_TYPE void TOSSendControl(const U8 u8ControlId );

#endif   // I_TOS_H

