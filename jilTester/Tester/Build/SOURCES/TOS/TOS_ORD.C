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
// Component:    TOS_ORD
//               TOS Task management with no preemption
// -----------------------------------------------------------------------------
// $Date:   Jul 24 2009 14:45:16  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/EXT_CMP/CPP_CMP/STK/SOURCES/TOS_ORD.C-arc  $
// $Revision:   1.1  $
// -----------------------------------------------------------------------------
/* $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/EXT_CMP/CPP_CMP/STK/SOURCES/TOS_ORD.C-arc  $
// 
//    Rev 1.1   Jul 24 2009 14:45:16   amanevd
// Cm005466: ListOfReadyTasks,
// ListOfSelectableTasks moved in fast memory
// 
//    Rev 1.0   04 Feb 2009 17:03:06   adzhelp
// Initial revision.
*/
//******************************************************************************

//------------------------------------------------------------------------------
// Body Identification
//------------------------------------------------------------------------------
#define TOS_ORD "TOS_ORD"

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------
#include "deftypes.h"
#include "tos_ord.h"
#include "ldb_tos.h"
#include "lib.h"
#ifdef TOS_PERF_CNT_ENABLE
 #include "TOS_PerfCnt.h"
#endif


#if cTOSNbMode >= 2
 #error "This TOS_ORD version do not support TOS mode management"
#endif

//------------------------------------------------------------------------------
// Local constants
//------------------------------------------------------------------------------
// Most prioritary task mask
#define cMaxTaskID    (((tTOSTaskID) 0x01UL) << (cTOSNbTask - ((tTOSTaskID)2UL) ))

//------------------------------------------------------------------------------
// Local macros
//------------------------------------------------------------------------------
#ifndef NO_DYNAMIC_DATA
  #define DATA_TYPE
#else
  #define DATA_TYPE static
//----- Scheduler stack management -----
  #define mClearSchedulerStack()                                         \
    (s8SchedulerStackLevel = ((S8)-1))

// Scheduler stack treat only tSchedulerStack type
  #define mPushToSchedulerStack(Type,Data)                               \
    {                                                                    \
        mLIBassert(sizeof(Type) == sizeof(tTOSTaskID));                  \
        s8SchedulerStackLevel++;                                           \
        mLIBassert(s8SchedulerStackLevel < (S8)(cTOSSchedulerStackSize));  \
        SchedulerStack[s8SchedulerStackLevel] = ((Type)(Data));            \
    }

  #define mPopFromSchedulerStack(Type,Data)                              \
    {                                                                    \
        mLIBassert(s8SchedulerStackLevel >= 0);                            \
        (Data) = ((Type)SchedulerStack[s8SchedulerStackLevel]);            \
        s8SchedulerStackLevel--;                                           \
    }

  #define cTOSSchedulerStackSize (cTOSMaxTaskNumber + cTOSOffsetSchedulerStackSize)
#endif

//------------------------------------------------------------------------------
// Local types
//------------------------------------------------------------------------------
#ifdef NO_DYNAMIC_DATA
typedef tTOSTaskID tSchedulerStack[cTOSSchedulerStackSize];
#endif

// -----------------------------------------------------------------------------
// Local data
//------------------------------------------------------------------------------
// List of ready tasks
#define	ListeTachesPretes    ListOfReadyTasks
static MEM_FAST volatile tTOSTaskID ListOfReadyTasks;

//List of all selectable tasks
#define ListeTachesEligibles   ListOfSelectableTasks
static MEM_FAST tTOSTaskID ListOfSelectableTasks;

static    BOOL          bSuspFlagOS;
static    tTOSItState   ITStateOS;

#ifdef USE_DISABLE_ALL_INTERRUPTS
static    BOOL          bSuspFlagAll;
static    tTOSItState   ITStateAll;
#endif

#ifdef NO_DYNAMIC_DATA
static    tSchedulerStack SchedulerStack;
static    S8              s8SchedulerStackLevel;
#endif

//------------------------------------------------------------------------------
// Constant local data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Constant exported data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Local function prototypes
//------------------------------------------------------------------------------

//==============================================================================
//=========================== LOCAL FUNCTIONS ==================================
//==============================================================================

//==============================================================================
//=========================== EXPORTED FUNCTIONS ===============================
//==============================================================================

//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
void TOSActivateTask(const tTOSTaskID TaskId)
{
    TOSSuspendOSInterrupts();
    ListOfReadyTasks |= TaskId;
    TOSResumeOSInterrupts();
}

//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
void TOSOrdSuspendTask(const tTOSTaskID TaskId)
{
    ListOfReadyTasks &= (tTOSTaskID)(~TaskId);
}

//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
void TOSSuspendOSInterrupts(void)
{
    TOSInternalGetAndDisableOSInterrupts(ITStateOS);
    // This assert will fail if you have called twice TOSSuspendOSInterrupts()
    mLIBassert((bSuspFlagOS = !bSuspFlagOS) == cTrue);
}

//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
void TOSResumeOSInterrupts(void)
{
    // This assert will fail if you have called twice TOSResumeOSInterrupts()
    mLIBassert((bSuspFlagOS = !bSuspFlagOS) == cFalse);
    TOSInternalSetOSInterruptsState(ITStateOS);
}

#ifdef USE_DISABLE_ALL_INTERRUPTS
//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
void TOSSuspendAllInterrupts(void)
{
    TOSInternalGetAndDisableAllInterrupts(ITStateAll);
    // This assert will fail if you have called twice TOSSuspendAllInterrupts()
    mLIBassert((bSuspFlagAll = !bSuspFlagAll) == cTrue);
}

//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
void TOSResumeAllInterrupts(void)
{
    // This assert fail if you have called twice TOSResumeAllInterrupts()
    mLIBassert((bSuspFlagAll = !bSuspFlagAll) == cFalse);
    TOSInternalSetAllInterruptsState(ITStateAll);
}
#endif

//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
void TOSShutdown(const U16 u16ErrorCode)
{
    TOSSuspendOSInterrupts();
    // In case of fatal error LAPShutdownHook() must provoke a reset.
    LAPShutdownHook(u16ErrorCode);
    TOSResumeOSInterrupts();
}

//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
void TOSInternalStart(void)
{
    bSuspFlagOS                      = cFalse;
#ifdef USE_DISABLE_ALL_INTERRUPTS
    bSuspFlagAll                     = cFalse;
	if(bSuspFlagAll){} //to avoid a warning in release mode
#endif
	if(bSuspFlagOS){} //to avoid a warning in release mode

    ListOfReadyTasks     = 0;
    ListOfSelectableTasks  = (tTOSTaskID)(((cMaxTaskID-((tTOSTaskID)1U))<< ((tTOSTaskID)1U)) + ((tTOSTaskID)1U));
    
#ifdef NO_DYNAMIC_DATA
    mClearSchedulerStack();
#endif
    
    // Application initialization (TOS, LAP, DAT and LDB)
    LAPStartupHook();

    // Interrupts authorization
    TOSEnableOSInterrupts();

    mLDBInitCPUTrace(cLDBCPUTraceMainLoop);

    //Infinite loop
    for(;;)
    {
        // before the idle task execution a scheduling is made too
        // execute the pending task
        TOSSchedule();

        // Idle task execution
        {
#ifdef TOS_NO_IDLE_TASK_TRACE
            TOSTaskList[0]();
#else
            mLDBEnterCPUTrace(cLDBCPUTraceIdleTask);
            TOSTaskList[0]();
            mLDBExitCPUTrace();
#endif
        }
    }
}

//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
void TOSSchedule(void)
{

    mLDBEnterCPUTrace(cLDBCPUTraceScheduler);
    while( (ListOfReadyTasks & ListOfSelectableTasks) != ((tTOSTaskID)0U) )
    {

        DATA_TYPE tTOSTaskID PreviousListOfSelectableTasks;
        
		U8 u8TaskID;

        DATA_TYPE tTOSTaskID          TOSTaskID;
        // save selectable task list
        PreviousListOfSelectableTasks = ListOfSelectableTasks;

        // search most priority pending task
        
		u8TaskID = cTOSNbTask - (U8)1U;

        TOSTaskID = cMaxTaskID;

        while( (TOSTaskID & ListOfReadyTasks) == ((tTOSTaskID)0U) )
        {
			u8TaskID--;

            TOSTaskID >>= 1U;
        }

        // Suppress task from the pending task list
        TOSSuspendOSInterrupts();
        ListOfReadyTasks -=  TOSTaskID;
        TOSResumeOSInterrupts();

        // update selectable task list
        TOSTaskID <<= 1U;
        TOSTaskID --;
        ListOfSelectableTasks = (tTOSTaskID)~TOSTaskID;

#ifdef NO_DYNAMIC_DATA      // Save context before call new task
        mPushToSchedulerStack(tTOSTaskID,PreviousListOfSelectableTasks)
#endif
        // task function calling
        {
			mLDBEnterCPUTrace((REG)(u8TaskID + cLDBCPUTraceIdleTask));

			(TOSTaskList[u8TaskID])();

            mLDBExitCPUTrace();
        }
#ifdef NO_DYNAMIC_DATA
        // Restore context
        mPopFromSchedulerStack(tTOSTaskID,PreviousListOfSelectableTasks)
#endif

        // restore selectable task list
        ListOfSelectableTasks = PreviousListOfSelectableTasks;
    }
    mLDBExitCPUTrace();
}

//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
void TOSHalt(void)
{
    //Use intermediate variable for QAC due to volatile type
    tTOSTaskID TaskList;

    //Disable interrupt using TOS service
    TOSDisableOSInterrupts();

    #ifndef TOS_NO_IDLE_MODE_TRACE
    mLDBEnterCPUTrace(cLDBCPUTraceIdleState);
    #endif

    TaskList = ListOfReadyTasks;

    while(TaskList == (tTOSTaskID)0UL)
    {
        //No pending task: go to halt mode
        LDBWaitForCallBack();

        //IT are executed
        TOSToggleOSInterrupts();

        //Re evaluate TaskList, because the interrupt can have activated a task
        TaskList = ListOfReadyTasks;
    }

    #ifndef TOS_NO_IDLE_MODE_TRACE
    mLDBExitCPUTrace();
    #endif

    //Enable interrupt using TOS service
    TOSEnableOSInterrupts();
}
