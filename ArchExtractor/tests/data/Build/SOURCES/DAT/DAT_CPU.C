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
// Component:    DAT_CPU
// -----------------------------------------------------------------------------
// $Date:   Apr 27 2009 16:22:44  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_CPU/DAT_CPU.C-arc  $
// $Revision:   1.4  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_CPU/DAT_CPU.C-arc  $
// 
//    Rev 1.4   Apr 27 2009 16:22:44   adzhelp
// Cm003619: Alarm management for GraphGroupSleep added
// 
//    Rev 1.3   Apr 13 2009 15:27:08   adzhelp
// Cm003619: Alarm management for GraphGroup80Ms added
// 
//    Rev 1.2   Mar 30 2009 13:48:00   adzhelp
// Cm004676: Alarm management for GraphGroup20Ms added
// 
//    Rev 1.1   Mar 12 2009 09:12:50   adzhelp
// Cm003619: Graph engine period set to 10 ms
//
//    Rev 1.0   04 Feb 2009 17:02:12   ailievb
// Initial revision.
//******************************************************************************

//------------------------------------------------------------------------------
// Body Identification
//------------------------------------------------------------------------------
#define DAT_CPU   "DAT_CPU"


//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//
// #include <system_file_name.h>
// #include "project_file_name.h"
//------------------------------------------------------------------------------
#include "lib.h"
#include "tos.h"
#include "dat.h"
#include "DAT_CPU.h"
#include "DAT_CPUp.h"


//------------------------------------------------------------------------------
// Local constants
//
// #define cConstantName   ((tType) ConstantValue)
//------------------------------------------------------------------------------
#define cGraphEnginePeriodMs            ((U32)10UL)
#define cGraphEngine20MsPeriodMs        ((U32)20UL)
#define cGraphEngineSleepPeriodMs       ((U32)20UL)
#define cGraphEngine80MsPeriodMs        ((U32)80UL)

#define cMultiplyOf4Mask        3 // for the two less signifficant bits
#define cMultiplyOf2Mask        1 // for the less signifficant bit

// The watch-dog allow to check if the software is blocked in a loop.
// According to the priority of the task, there is to value of timeout :
// if the task priority is greater than watchdog task the timeout is
// - cRefreshWatchDogPeriodMs
// if the task priority is lower than watchdog task the timeout is
// - cWatchDogIdleTaskTimeoutMs
#define cRefreshWatchDogPeriodMs    ((U32)80UL)
#define cWatchDogIdleTaskTimeoutMs  ((U32)1000UL)

#define cWatchDogCounterMaxValue mDiv(cWatchDogIdleTaskTimeoutMs,cRefreshWatchDogPeriodMs)

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
static tTOSAlarm GraphEngineAlarm;
static tTOSAlarm GraphEngine20MsAlarm;
static tTOSAlarm GraphEngineSleepAlarm;
static tTOSAlarm GraphEngine80MsAlarm;
static tTOSAlarm RefreshWatchDogAlarm;
static BOOL  IsIdleGraphGroupEnable;
static U8    WatchDogCounter;

#ifdef COMPILATION_NATIVE
// for Windows unit test
tDATCpuStackWatermarkValue DATCpuWinSimStack[cDATCpuWinSimStackSize];
BOOL bDATCpuWinSimReset = cFalse;
BOOL  bDATCpuFirstWatermarkAssert;
tDATCpuStackWatermarkValue *cDATCpuWatermarkResetAddress = &DATCpuWinSimStack[0];
U8 *pDATCpuInStack = (U8 *)&DATCpuWinSimStack[cDATCpuWinSimStackSize-1];
#else
static BOOL  bDATCpuFirstWatermarkAssert;
#endif

#ifndef DISABLE_IDLE_MEASURE
U32 u32DATCpuUnUsedStackSize;
#endif

//------------------------------------------------------------------------------
// Constant local data
//
// static const tType  VariableName;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported data
//
// tType   u8LAYCmpVariableName; (LAY: 3 characters to identify the layer)
// tType*  pu8LAYCmpVariableName;(Cmp: 3 characters to identify the component)
//------------------------------------------------------------------------------

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
static void DATCpuCheckStackWatermarks(void);
static void DATCpuSetStackWatermarks(void);


//==============================================================================
//=========================== LOCAL FUNCTIONS ==================================
//==============================================================================

//==============================================================================
// DESCRIPTION : DATCpuCheckStackWatermarks()
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
static void DATCpuCheckStackWatermarks(void)
{
    tDATCpuStackWatermarkValue *pWatermark;
    
    if (cDATCpuWatermarkAssertAddress != cDATCpuWatermarkDisable)
    {
        pWatermark = (tDATCpuStackWatermarkValue *)cDATCpuWatermarkAssertAddress;
        if (*pWatermark != cDATCpuWatermarkAssertValue)
        {
            if (bDATCpuFirstWatermarkAssert != cFalse)
            {
                bDATCpuFirstWatermarkAssert = cFalse;
#ifndef COMPILATION_NATIVE
                mLIBassert(cFalse);
#endif
            }
        }
    }
    if (cDATCpuWatermarkResetAddress != cDATCpuWatermarkDisable)
    {
        pWatermark = (tDATCpuStackWatermarkValue *)cDATCpuWatermarkResetAddress;
        if (*pWatermark != cDATCpuWatermarkResetValue)
        {
#ifdef COMPILATION_NATIVE
            bDATCpuWinSimReset = cTrue;
#else
            mLIBassert(cFalse);
            LDBReset();
#endif
        }
    }
}


//==============================================================================
// DESCRIPTION : DATCpuSetStackWatermarks
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
static void DATCpuSetStackWatermarks(void)
{
    tDATCpuStackWatermarkValue *pWatermark;
    
    if (cDATCpuWatermarkAssertAddress != cDATCpuWatermarkDisable)
    {
        pWatermark = (tDATCpuStackWatermarkValue *)cDATCpuWatermarkAssertAddress;
        *pWatermark = cDATCpuWatermarkAssertValue;
    }
    if (cDATCpuWatermarkResetAddress != cDATCpuWatermarkDisable)
    {
        pWatermark = (tDATCpuStackWatermarkValue *)cDATCpuWatermarkResetAddress;
        *pWatermark = cDATCpuWatermarkResetValue;
    }
}


//==============================================================================
// DESCRIPTION : DATCpuSetStackContents
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
static void DATCpuSetStackContents(void)
{
    if (cDATCpuWatermarkResetAddress != cDATCpuWatermarkDisable)
    {
		U8 *pu8start, *pu8stop;
#ifndef COMPILATION_NATIVE
        U8 u8InStack;
        U8 *pu8InStack = &u8InStack;
#else
        U8 *pu8InStack = pDATCpuInStack;
#endif
		// WARNING: memset() should not be used directly because it (as any function) pushes its arguments and return address in the stack and they could get overwritten!
        if ((U8 *)cDATCpuWatermarkResetAddress > pu8InStack)
        {
            // upward growing stack
			pu8start = pu8InStack;
			pu8stop = (U8 *)cDATCpuWatermarkResetAddress;
		}
        else
        {
            // downward growing stack
			pu8start = (U8 *)cDATCpuWatermarkResetAddress;
			pu8stop = pu8InStack;
        }
		while (pu8start <= pu8stop)
		{
				*pu8start = cDATCpuStackContentsValue;
				pu8start++;
		}
    }
}

//==============================================================================
//=========================== EXPORTED FUNCTIONS ===============================
//==============================================================================

//==============================================================================
// DESCRIPTION : DATCpuIdleTask: Idle task
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
void DATCpuIdleTask(void)
{
    if( IsIdleGraphGroupEnable != cFalse )
    {
        mTOSSeqMotorIdleGraphGroup();
    }
#ifndef DAT_CPU_ENABLE_HALT
    else
    {
        LDBWaitForCallBack();
    }
#endif
    
    WatchDogCounter = cWatchDogCounterMaxValue;
    
    DATCpuCheckStackWatermarks();
    
#ifndef DISABLE_IDLE_MEASURE    
    if (mDATCpuGetUnUsedStackSizeEnabled())
    {
        u32DATCpuUnUsedStackSize = DATCpuGetUnUsedStackSize();
    }
#endif
#ifdef DAT_CPU_ENABLE_HALT
    TOSHalt();
#endif
}


//==============================================================================
// DESCRIPTION : DATCpuInit : Initialization of the component
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
void DATCpuInit(void)
{
    RefreshWatchDogAlarm.TaskID = cTOSTaskIdDATCpuRefreshWatchDogTask;
    GraphEngineSleepAlarm.TaskID = cTOSTaskIdGraphEngineTaskSleep;
    TOSSetRelAlarm( &RefreshWatchDogAlarm,0, mTOSConvMsInAlarmTick(cRefreshWatchDogPeriodMs) );
    TOSSetRelAlarm( &GraphEngineSleepAlarm,0, mTOSConvMsInAlarmTick(cGraphEngineSleepPeriodMs) );

    IsIdleGraphGroupEnable = cFalse;
    WatchDogCounter = cWatchDogCounterMaxValue;
    
    bDATCpuFirstWatermarkAssert = cTrue;

#ifndef DISABLE_IDLE_MEASURE    
    u32DATCpuUnUsedStackSize = 0;
#endif
    
    if (sizeof(tDATCpuStackWatermarkValue) == 4)
    {
        // warn that for accessing 32 bits (4 bytes) in many MCUs the address must be a multiply of 4!
        mLIBassert(((U32)cDATCpuWatermarkAssertAddress & cMultiplyOf4Mask) == 0);
        mLIBassert(((U32)cDATCpuWatermarkResetAddress & cMultiplyOf4Mask) == 0);
    }
    if (sizeof(tDATCpuStackWatermarkValue) == 2)
    {
        // warn that for accessing 16 bits (2 bytes) in many MCUs the address must be a multiply of 2!
        mLIBassert(((U32)cDATCpuWatermarkAssertAddress & cMultiplyOf2Mask) == 0);
        mLIBassert(((U32)cDATCpuWatermarkResetAddress & cMultiplyOf2Mask) == 0);
    }
    
    if (mDATCpuGetUnUsedStackSizeEnabled())
    {
        DATCpuSetStackContents();
    }
    
    DATCpuSetStackWatermarks();
}


//==============================================================================
// DESCRIPTION : DATCpuLeaveSleep : leave the sleep mode
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
void DATCpuLeaveSleep(void)
{
    GraphEngineAlarm.TaskID = cTOSTaskIdGraphEngineTask;
    GraphEngine20MsAlarm.TaskID = cTOSTaskIdGraphEngineTask20Ms;
    GraphEngine80MsAlarm.TaskID = cTOSTaskIdGraphEngineTask80Ms;
    TOSSetRelAlarm( &GraphEngineAlarm,0, mTOSConvMsInAlarmTick(cGraphEnginePeriodMs) );
    TOSSetRelAlarm( &GraphEngine20MsAlarm,0, mTOSConvMsInAlarmTick(cGraphEngine20MsPeriodMs) );
    TOSSetRelAlarm( &GraphEngine80MsAlarm,0, mTOSConvMsInAlarmTick(cGraphEngine80MsPeriodMs) );
    IsIdleGraphGroupEnable = cTrue;

    #ifdef USE_DISABLE_TOSTIMER
    TOSDisableTimer();
    TOSStopAlarm();
    #endif

    LDBLeaveSleepMode();

    #ifdef USE_DISABLE_TOSTIMER
    TOSStartAlarm();
    TOSEnableTimer(1); //Min Multiplicator Value = 1
    #endif
}


//==============================================================================
// DESCRIPTION : DATCpuEnterSleep : entreing into the sleep mode
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
void DATCpuEnterSleep(void)
{
    TOSCancelAlarm( &GraphEngineAlarm );
    TOSCancelAlarm( &GraphEngine20MsAlarm );
    TOSCancelAlarm( &GraphEngine80MsAlarm );
    IsIdleGraphGroupEnable = cFalse;

    #ifdef USE_DISABLE_TOSTIMER
    TOSDisableTimer();
    TOSStopAlarm();
    #endif

    LDBEnterSleepMode();

    #ifdef USE_DISABLE_TOSTIMER
    TOSStartSlowestAlarms((tTOSTickAlarm)(cLDBSleepTick / cLDBTick));
    TOSEnableTimer((tTOSTickAlarm)(cLDBSleepTick / cLDBTick));
    #endif
}


//==============================================================================
// DESCRIPTION : DATCpuRefreshWatchDogTask : periodical task is create in order
// to refresh watchdog
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
void DATCpuRefreshWatchDogTask(void)
{
    // A periodical task is create in order to refresh watchdog.
    
    // This way of processing allows to:
    // - Insure that TOS time base correctly work
    // - Insure that tasks with higher priority than this task running.
    // - Get an unique mechanism in wake-up and sleep modes.
    
    // This way of processing does not allows to:
    // - Insure that tasks with lower priority than this task running.
    //   For example, if the graph engine run in idle task, this solution
    //   is not adjusted. In this case use a graph updating watchdog when
    //   a temporisation elapse.
    
    if( WatchDogCounter != 0)
    {
        // This counter allows to check that tasks of lower priority than
        // Watch dog tasks are also running.
        WatchDogCounter--;
    
        LDBRefreshWatchDog();
    }
}


//==============================================================================
// DESCRIPTION : DATCpuGetUnUsedStackSize : get the unused stack size
//
// PARAMETERS (Type,Name,Min,Max) :   U32 : unused stack size
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
// in bytes, if returned value = 0 then the measure is not performed (enabled),
//to enable it just define meaningful cDATCpuWatermarkResetAddress
//==============================================================================
U32 DATCpuGetUnUsedStackSize(void)
{
    U32 u32Size = 0;
    
    if (mDATCpuGetUnUsedStackSizeEnabled())
    {
#ifndef COMPILATION_NATIVE
        U8 *pu8InStack = (U8 *)&u32Size;
#else
        U8 *pu8InStack = pDATCpuInStack;
#endif
        U8 *pu8StackFrom = (U8 *)cDATCpuWatermarkResetAddress;
        // always start the scan from stack end to current stack pointer!
        if ((U8 *)cDATCpuWatermarkResetAddress > pu8InStack)
        {
            // upward growing stack
            pu8StackFrom--; // skip reset watermark
            while (   (pu8StackFrom > pu8InStack) && ((*pu8StackFrom == cDATCpuStackContentsValue)
                   || (pu8StackFrom == (U8 *)((U8 *)cDATCpuWatermarkAssertAddress+sizeof(tDATCpuStackWatermarkValue)-1))))
            {
                if (pu8StackFrom == (U8 *)((U8 *)cDATCpuWatermarkAssertAddress+sizeof(tDATCpuStackWatermarkValue)-1))
                {
                    // take into account assert watermark
                    pu8StackFrom -= sizeof(tDATCpuStackWatermarkValue);
                    u32Size += sizeof(tDATCpuStackWatermarkValue);
                }
                else
                {
                    u32Size++;
                    pu8StackFrom--;
                }
            }
        }
        else
        {
            // downward growing stack
            pu8StackFrom += sizeof(tDATCpuStackWatermarkValue); // skip reset watermark
            while ((pu8StackFrom < pu8InStack) && ((*pu8StackFrom == cDATCpuStackContentsValue) || (pu8StackFrom == (U8 *)cDATCpuWatermarkAssertAddress)))
            {
                if (pu8StackFrom == (U8 *)cDATCpuWatermarkAssertAddress)
                {
                    // take into account assert watermark
                    pu8StackFrom += sizeof(tDATCpuStackWatermarkValue);
                    u32Size += sizeof(tDATCpuStackWatermarkValue);
                }
                else
                {
                    u32Size++;
                    pu8StackFrom++;
                }
            }
        }
    }
    else
    {
        // functionality not enabled, cDATCpuWatermarkResetAddress must be defined
        // according to actual stack location
#ifndef COMPILATION_NATIVE
        mLIBassert(cFalse);
#endif
    }

    return u32Size;
}
