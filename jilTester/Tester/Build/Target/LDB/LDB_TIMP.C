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
// Component:    LDB_TIM
//               Sleep mode timer management    
//               Example implementation of LDBTimPerfCntGetTime() 
//               high resolution timer
// -----------------------------------------------------------------------------
// $Log:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_TIM/LDB_TIMP.C-arc  $
// 
//    Rev 1.3   Nov 17 2009 11:21:28   adzhelp
// Cm006675: Variables added and timer handling used in CPU trace configuration
// 
//    Rev 1.2   Apr 27 2009 15:14:46   adzhelp
// Cm003272: Sharing of sleep timer implemented
// 
//    Rev 1.1   Apr 16 2009 10:36:54   adzhelp
// Cm003276: Implementation of sleep mode timer management
// 
//    Rev 1.0   04 Feb 2009 17:03:24   adzhelp
// Initial revision.
//******************************************************************************

//------------------------------------------------------------------------------
// Body Identification
//------------------------------------------------------------------------------
#define ldb_timp   "ldb_timp"

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//
// #include <system_file_name.h>
// #include "project_file_name.h"
//------------------------------------------------------------------------------

#include "ldb.h"
#include "ldb_ioc.h"
#include "ldb_int.h"
#ifdef TOS_PERF_CNT_ENABLE
 #include "TOS_PerfCnt.h"
#endif
#include "ldb_tim.h"

//------------------------------------------------------------------------------
// Local constants
//
// #define cConstantName   ((tType) ConstantValue)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Local macros
//
// #define mMacroName   (MacroDefinition)
//------------------------------------------------------------------------------

#ifdef TRACE_CPU_ACTIVE
// Select hardware timer
//to do...

// Change to (1) if you want PerfCnt to trace its own interrupt
#define mSelfTrace              (0)

#define mTraceCpuInterruptID INTTM50
#define cTCL50Init           0x06U // fprs/(2^8)

// to do #define mGetOverflowFlag(Timer)
// to do #define mGetOverflowFlagx(Timer)
#endif

//------------------------------------------------------------------------------
// Local types
//
// typedef Expression    tTypeName;
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Data prefix
//
// unsigned int {u8,u16,u32} / signed int {s8,s16,s32} 
// register size unsigned int {r} / float {f32,f64}  / s for struct 
//
// -----------------------------------------------------------------------------
// Local data
//
// static  tType   u8VariableName;  
// static  tType*  pu8VariableName; 
//------------------------------------------------------------------------------
#ifdef TOS_PERF_CNT_ENABLE
//to do: static volatile U16 u16TmrH;
#endif

//------------------------------------------------------------------------------
// Constant local data
//
// static const tType  VariableName;
//------------------------------------------------------------------------------

// select prescale value for HW timer
#define cPrescaleValue              0


#define cTimerResolutionInBits      16


//------------------------------------------------------------------------------
// Exported data
//
// tType   u8LAYCmpVariableName; (LAY: 3 characters to identify the layer)
// tType*  pu8LAYCmpVariableName;(Cmp: 3 characters to identify the component)
//------------------------------------------------------------------------------
#ifdef TRACE_CPU_ACTIVE
MEM_FAST volatile BOOL LDBHandleTimerOverflow;
MEM_FAST volatile tLDBHandleTimer LDBHandleTimeStamp;
#endif

//------------------------------------------------------------------------------
// Constant exported data
//
//             (LAY: 3 characters to identify the layer)
//             (Cmp: 3 characters to identify this component)
// 
// const tType   LAYCmpVariableName;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Local function prototypes
// 
// static tTypeRetour FunctionName(tTypeArgument1 ArgumentName1, ... );
//------------------------------------------------------------------------------

//==============================================================================
//=========================== LOCAL FUNCTIONS ==================================
//==============================================================================


//==============================================================================
//=========================== EXPORTED FUNCTIONS ===============================
//==============================================================================


//==============================================================================
// DESCRIPTION : Initialize high resolution timer
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : Refer to Detailed Design Document
//==============================================================================
void LDBTimpInit(void)
{
#ifdef TRACE_CPU_ACTIVE
    mLDBIocWriteTrigger(Trigger50, (U8)~0U);
    mLDBRegWrite8BitRegister(TCL50, cTCL50Init);
    
    mLDBIntClearIsrRequestFlag(mTraceCpuInterruptID);
    mLDBIntEnableIsr(mTraceCpuInterruptID);
    mLDBIocStartTimer(mLDBTraceCpuTimerID);
#endif
}

//==============================================================================
// DESCRIPTION : Returns high resolution timer value in ticks
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   32 - bit rolling timer value
//
// DESIGN INFORMATION : Refer to Detailed Design Document
//==============================================================================
#ifdef TOS_PERF_CNT_ENABLE
U32 LDBTimPerfCntGetTime(void)
{
//to do...
    return (1);
}
#endif

//==============================================================================
// DESCRIPTION : Handle 8 bit hardware timer overflow and increase the 
//     higher word of high resolution 32 bit timer. 
//      mLDBIntEnterIsr and mLDBIntLeaveIsr are omitted intentionally, because
//      TraceCPU cannot measure its own execution
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : Refer to Detailed Design Document
//==============================================================================
#ifdef TRACE_CPU_ACTIVE
mLDBIntDeclareIsr(mTraceCpuInterruptID)
{
    // write some value to this variable to trigger trace event
    // this will alert parser that overflow timer occurred.
    LDBHandleTimerOverflow = cTrue;
}
#endif

/*============================================================================
  DESCRIPTION         : Start ldb_tim component
  
  PARAMETERS          : None
  (Type,Name,Min,Max) 

  RETURN VALUE        : Always 0 for OSEK compatibility
 
  DESIGN INFORMATION  : Refer to Detailed Design Document
  ==========================================================================*/
void LDBTimStartSlowTimer(void)
{
    mLIBassert((cLDBSleepTick/cLDBHarSleepTickInNsRealTimeTimer) <
               (1UL << mLDBIocGetType(cLDBHarSleepRealTimeTimer)));
    
    // Initialize timer
    mLDBIntGetInterruptTMH1(cLDBIntTimOwnerTMH1);
    mLDBIocSetTimerModeIntervalTimer(cLDBHarSleepRealTimeTimer);
    mLDBIocSelectClock(cLDBHarSleepRealTimeTimer, cLDBHarSleepRealTimeTimerPrescaler);

    // Start timer
    mLDBIocWriteTrigger(cLDBHarSleepRealTimeTrigger,
                        ((cLDBSleepTick / cLDBHarSleepTickInNsRealTimeTimer)-1));
    mLDBIntClearIsrRequestFlag(cLDBHarSleepInterruptRealTimeIt);
    mLDBIntEnableIsr(cLDBHarSleepInterruptRealTimeIt);
    mLDBIocStartTimer(cLDBHarSleepRealTimeTimer);
}

/*============================================================================
  DESCRIPTION         : Stop ldb_tim component
  
  PARAMETERS          : None
  (Type,Name,Min,Max) 

  RETURN VALUE        : Always 0 for OSEK compatibility
 
  DESIGN INFORMATION  : Refer to Detailed Design Document
  ==========================================================================*/
void LDBTimStopSlowTimer(void)
{
    mLDBIocStopTimer(cLDBHarSleepRealTimeTimer);
    mLDBIntDisableIsr(cLDBHarSleepInterruptRealTimeIt);
    mLDBIntReleaseInterruptTMH1(cLDBIntTimOwnerTMH1);
}

//==============================================================================
// DESCRIPTION : Real time interrupt for sleep mode
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   None
//
// DESIGN INFORMATION : Refer to Detailed Design Document
//==============================================================================
#ifndef X90_PROJECT
mLDBIntDeclareIsr(cLDBHarSleepInterruptRealTimeIt)
{
    mLDBIntEnterIsr(cLDBHarSleepInterruptRealTimeIt);
#else
void LDBTimSleepInterruptRealTime(void)
{
#endif    
    // IT clearing
    mLDBIntClearIsrRequestFlag(cLDBHarSleepInterruptRealTimeIt);
    mLaunchSleepItSequencedTimeOut();

    mLauchTosSequencedTimeOut();

#ifndef X90_PROJECT
    mLDBIntLeaveIsr(cLDBHarSleepInterruptRealTimeIt);
#endif
}
