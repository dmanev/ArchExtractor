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
// Component:    TOS_CONFIG
// -----------------------------------------------------------------------------
// $Date:   Jul 24 2009 14:40:38  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/TOS/TOS_CONFIG/TOSPARAM.H-arc  $
// $Revision:   1.2  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/TOS/TOS_CONFIG/TOSPARAM.H-$
// 
//    Rev 1.2   Jul 24 2009 14:40:38   amanevd
// Cm005466: NO_DYNAMIC_DATA should is now undefined
// 
//    Rev 1.1   Mar 12 2009 08:49:56   adzhelp
// Cm003619: Paramaterization for NEC K0 / IAR compiler
// 
//    Rev 1.0   04 Feb 2009 17:03:04   adzhelp
// Initial revision.
//******************************************************************************

#ifndef I_TOSPARAM_H
#define I_TOSPARAM_H


// This definition determine the TOS_ORD component used
//#define TOS_PREEMPTIVE

// This definition enable the using of TOS_SIG component
#define USE_TOS_SIG

// This definition enable the using of EnableAllInterrupt services.
// In majority of case, this functions may not be used.
// You must define it only if there are interrupts of OSEK category 1.
// #define USE_DISABLE_ALL_INTERRUPTS

// This definition indicate that micro treat only a static datas
//#define NO_DYNAMIC_DATA

// This definition active services to set the timer tick and disable TOS timer
// (always disable TOS timer before set the timer tick value)
// Usefull when in sleep mode the CPU clock frequency is reduced but TOS timer
// are still active
#define USE_DISABLE_TOSTIMER

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------
#include "deftypes.h"
#include "lib.h"
#include "jil.h"

//------------------------------------------------------------------------------
// Constant data
//------------------------------------------------------------------------------

//----- Scheduler management -----
// This definition determine the number of mode used for OSEK compatibility.
// It must be always equal 1
  #define cTOSNbMode                            1
  #define cTOSDefaultMode                       1

#if ( defined (NO_DYNAMIC_DATA) || defined(TOS_PREEMPTIVE) )
// If a scheduler stack is used, This definition adjust it.
  #define cTOSOffsetSchedulerStackSize          0UL
#endif

//----- Alarm definition -----
//This constant parameter is used to define the designed for Alarm management LDB Timer 
  #define cTOSTimerLdbDesignedForALA            cLDBTimer1

//----- Tick definition -----
  #define cTOSTickAlarmUs                       5000UL
  #define cTOSTimerTickMs                       10UL

//----  Graph scheduler parameters ----
  #define cTOSSeqMaxRuleNumber                  255   // 255 or 65535
  #define cTOSSeqDureeTourGrapheSimulationNs    3000000UL

  // -- Use for CPU Trace to avoid to trace the idle task
  //    (permit to let the trace points to others events)
  //#define TOS_NO_IDLE_TASK_TRACE

  // -- Use for CPU Trace to avoid to trace the idle mode (halt mode)
  //    (permit to let the trace points to others events)
  //#define TOS_NO_IDLE_MODE_TRACE

//------------------------------------------------------------------------------
// Exported Macros
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//                                QAC
//------------------------------------------------------------------------------
#if defined(_QAC_)
// This definition determine the size of micro bus
  #define cTOSBusInteger                        8UL      // 8UL,16UL or 32UL bits

//----- Interrupt management services -----
extern void NOP(void);
  #ifdef USE_DISABLE_ALL_INTERRUPTS
    #define TOSEnableAllInterrupts()    NOP()
    #define TOSDisableAllInterrupts()   NOP()

    #define TOSInternalGetAndDisableAllInterrupts(ITState)  ITState = 0;\
                                                            ITState = ITState
    #define TOSInternalSetAllInterruptsState(ITState)       ITState = 0;\
                                                            ITState = ITState
  #endif
  #define TOSEnableOSInterrupts()     NOP()
  #define TOSDisableOSInterrupts()    NOP()

  #define TOSInternalGetAndDisableOSInterrupts(ITState)   ITState = 0;\
                                                          ITState = ITState

  #define TOSInternalSetOSInterruptsState(ITState)        ITState = 0;\
                                                          ITState = ITState

  #define TOSToggleOSInterrupts()     TOSEnableOSInterrupts();    \
                                      NOP();                      \
                                      TOSDisableOSInterrupts()

  #ifdef TOS_PREEMPTIVE
    #define mTOSEnterISR()              NOP()
    #define mTOSLeaveISR()              NOP()
  #endif

//------------------------------------------------------------------------------
//                          COMPILATION NATIVE
//------------------------------------------------------------------------------
#elif defined(COMPILATION_NATIVE)
// This definition determine the size of micro bus
  #define cTOSBusInteger                        8UL      // 8UL,16UL or 32UL bits
  #define NOP()
//----- Interrupt management services -----
  #ifdef USE_DISABLE_ALL_INTERRUPTS
    #define TOSEnableAllInterrupts()
    #define TOSDisableAllInterrupts()

    #define TOSInternalGetAndDisableAllInterrupts(ITState)    ITState = 0
    #define TOSInternalSetAllInterruptsState(ITState)         ITState = 0
  #endif

  #define TOSEnableOSInterrupts()
  #define TOSDisableOSInterrupts()

  #define TOSInternalGetAndDisableOSInterrupts(ITState)     ITState = 0
  #define TOSInternalSetOSInterruptsState(ITState)          ITState = 0

  #define TOSToggleOSInterrupts()   TOSEnableOSInterrupts();    \
                                    NOP();                      \
                                    TOSDisableOSInterrupts()

  #ifdef TOS_PREEMPTIVE
    #define mTOSEnterISR()
    #define mTOSLeaveISR()
  #endif
#else 
//------------------------------------------------------------------------------
//                            MICRO H8S
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//                            MICRO NEC K0
//------------------------------------------------------------------------------

  #define NOP() _ASM("nop")

// This definition indicate that micro treat only a static datas
//  #define NO_DYNAMIC_DATA
  #define cTOSOffsetSchedulerStackSize          0UL

// This definition determine the size of micro bus
  #define cTOSBusInteger                        8UL      // 8UL,16UL or 32UL bits

//----- Interrupt management services -----
// This services are optional

  #include "io78f0536_64.h"
  #include "intrinsics.h"

    // new-styled keywords and intrinsic functions
    #define _ASM    __asm
    #define _DI()   _ASM("DI")
    #define _EI()   _ASM("EI")


  #ifdef USE_DISABLE_ALL_INTERRUPTS
    #define TOSEnableAllInterrupts()                    _EI()
    #define TOSDisableAllInterrupts()                   _DI()

    // Macro modified to remove compilation warning
    #define TOSInternalGetAndDisableAllInterrupts(ITState)          \
                              {                                     \
                                tTOSItState ITStateTmp=0;           \
                                /*ITStateTmp is stored in R1*/      \
                                _ASM("MOV R1,PSW");                 \
                                _ASM("AND R1,#0x1");                \
                                TOSDisableAllInterrupts();          \
                                (ITState) = ITStateTmp;             \
                              }
    #define TOSInternalSetAllInterruptsState(ITState)   _DI();if(ITState!=0){_EI();}
  #endif

  #define TOSEnableOSInterrupts()                     _EI()
  #define TOSDisableOSInterrupts()                    _DI()

  // Macro modified to remove compilation warning
  #define TOSInternalGetAndDisableOSInterrupts(ITState)             \
                            {                                       \
                                tTOSItState ITStateTmp=0;           \
                                /*ITStateTmp is stored in R1*/      \
                                _ASM("MOV R1,PSW");                 \
                                _ASM("AND R1,#0x80");               \
                                TOSDisableOSInterrupts();           \
                                (ITState) = ITStateTmp;             \
                            }

  #define TOSInternalSetOSInterruptsState(ITState)    _DI();if(ITState!=0){_EI();}

  #define TOSToggleOSInterrupts()   TOSEnableOSInterrupts();    \
                                    NOP();                      \
                                    TOSDisableOSInterrupts()

  #ifdef TOS_PREEMPTIVE
    #define mTOSEnterISR()                                        \
      mPushToSchedulerStack(U8,TOSInternalForbiddenPreemptLev);   \
      TOSInternalForbiddenPreemptLev = cTOSResourceScheduler

    #define mTOSLeaveISR()                                        \
      mPopFromSchedulerStack(U8,TOSInternalForbiddenPreemptLev);  \
      TOSOrdInternalSchedule()
  #endif
//------------------------------------------------------------------------------
//                            MICRO M16C
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//                            MICRO M32C
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//                            MICRO NEC V850 Fx/Dx
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//                            MICRO NEC V850 Fx/Dx/Sx3
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//                            MICRO Fuji 16Fx
//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
// Exported type
//------------------------------------------------------------------------------
//----- Clock management (must always be an unsigned type) -----
typedef U16 tTOSClock;

//----- Define the graph instance type -----
typedef U8 tTOSSeqGraphInstance;

//----- Define the SignalID type -----
typedef U16 tTOSSignalID;

//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Constant exported data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported functions
//------------------------------------------------------------------------------

#endif // I_TOSPARAM_H
