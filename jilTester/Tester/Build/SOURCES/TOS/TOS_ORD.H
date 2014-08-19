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
// $Date:   04 Feb 2009 17:03:06  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/EXT_CMP/CPP_CMP/STK/SOURCES/TOS_ORD.H-arc  $
// $Revision:   1.0  $
// -----------------------------------------------------------------------------
/* $Log:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/EXT_CMP/CPP_CMP/STK/SOURCES/TOS_ORD.H-arc  $
// 
//    Rev 1.0   04 Feb 2009 17:03:06   adzhelp
// Initial revision.
*/
//******************************************************************************

#ifndef I_TOS_ORD_H
#define I_TOS_ORD_H

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------
#include "tos.h"

#ifdef TOS_PREEMPTIVE
  #error "This version of TOS_ORD is non preemptive"
#endif

//------------------------------------------------------------------------------
// Constant data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported type
//------------------------------------------------------------------------------
typedef tTOSTaskID tTOSOrdTaskList;

//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Constant exported data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported Macros
//------------------------------------------------------------------------------
#define TOSOrdClearTaskList(pTaskList)              (*(pTaskList) = 0)
#define TOSOrdActivateTaskList(pTaskList)           (TOSActivateTask(*(pTaskList)))
#define TOSOrdAddTaskToList(pTaskList,TaskId)       ((*(pTaskList)) |= (TaskId))
#define TOSOrdRemoveTaskFromList(pTaskList,TaskId)  ((*(pTaskList)) &= (tTOSTaskID)(~(TaskId)))

//------------------------------------------------------------------------------
// Exported functions
//------------------------------------------------------------------------------

//----- Interrupt management services -----
//==============================================================================
// DESCRIPTION:         Suspends OS interrupt
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Calls TOSInternalGetAndDisableOSInterrupts(ITStateOS)
//                      Refer to Detailed Design Document
//==============================================================================
void TOSSuspendOSInterrupts(void);

//==============================================================================
// DESCRIPTION:         Resumes OS interrupt
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Calls TOSInternalSetOSInterruptsState (ITStateOS)
//                      Refer to Detailed Design Document
//==============================================================================
void TOSResumeOSInterrupts(void);

#ifdef USE_DISABLE_ALL_INTERRUPTS
//==============================================================================
// DESCRIPTION:         Suspends ALL interrupt
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Calls TOSInternalGetAndDisableAllInterrupts(ITStateAll)
//                      Refer to Detailed Design Document
//==============================================================================
void TOSSuspendAllInterrupts(void);

//==============================================================================
// DESCRIPTION:         Resumes ALL interrupts
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Calls TOSInternalSetAllInterruptsState (ITStateAll)
//                      Refer to Detailed Design Document
//==============================================================================
void TOSResumeAllInterrupts(void);
#endif


//----- Tasks management services -----
//==============================================================================
// DESCRIPTION:         The most priority ready task than the current one passes
//                      into activated state 
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  While(Is ready selectable task)
//                      - Select most priority ready task;
//                      - save selectable task list;
//                      - update selectable task list;
//                      - execute the task;
//                      - restore selectable task list.
//                      Refer to Detailed Design Document
//==============================================================================
void TOSSchedule(void);

//==============================================================================
// DESCRIPTION:         Activation of a TOS task. The task passes in ready state.
//
// PARAMETERS:          TaskId - task identifier. It can only take value of 2 to
//                               the power of x. 
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Updates ListOfReadyTasks with the ID of the task to be activated
//                      Refer to Detailed Design Document
//==============================================================================
void TOSActivateTask(const tTOSTaskID TaskId);

//==============================================================================
// DESCRIPTION        : Removes the requested TaskId from the list of ready tasks
//
// PARAMETERS:          TaskId - task identifier. It can only take value of 2 to
//                               the power of x. 
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Updates ListOfReadyTasks removing the requested TaskId from it
//                      Refer to Detailed Design Document
//==============================================================================
void TOSOrdSuspendTask(const tTOSTaskID TaskId);

//----- TOS management services -----
//==============================================================================
// DESCRIPTION:         Provokes OS stop
//
// PARAMETERS:          u16ErrorCode - error code
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Allows stopping TOS functioning in 2 cases:
//                      - To change the mode of functioning with error code cTOSOk=0;
//                      - To restart system after a fatal error;
//                      This function:
//                      - Suspends OS interrupts;
//                      - Calls LAPShutdownHook(u16ErrorCode). In case of fatal 
//                      error LAPShutdownHook() must provoke a reset.
//                      - Resumes OS interrupts
//                      Refer to Detailed Design Document
//==============================================================================
void TOSShutdown(const U16 u16ErrorCode);

//==============================================================================
// DESCRIPTION:         Starts TOS
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  - Initializes TOS_ORD;
//                      - Initializes DAT and LDB;
//                      - Enables OS Interrupts;
//                      - This is the scheduler entering point. The software never 
//                        exit this function. The Infinite loop provokes:
//                            - Scheduling;
//                            - Idle task exectuion.
//                      Refer to Detailed Design Document
//==============================================================================
void TOSInternalStart(void);

//==============================================================================
// DESCRIPTION:         Idle mode entering, CPU is going to sleep untill an interrupt wake it
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:
//
//                      if(Is no task pending)
//                         go to sleep mode
//                      else
//                         execute tasks
//                      end if
//
//==============================================================================
void TOSHalt(void);


#endif // I_TOS_ORD_H

