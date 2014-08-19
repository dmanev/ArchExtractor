/****************************************************************************
  Project ......................... Common
  Component ....................... ldb_tos
  File revision....................
  Last modification date ..........
  -------------------------------------------------------------------------
  Copyright ... This software is JCI property. Duplication or
                disclosure is prohibited without JCI written permission
  ------------------------------------------------------------------------- 
    
  - This file should only contain data useful to the programmer to use
    this component
  - Component exported macros, constants and types are defined in this file
  - Component exported variables and functions are declared in this file 
    with the "extern" keyword
  
  -------------------------------------------------------------------------
  ldb_tos.h file review :
  
   See PVCS Base

*****************************************************************************/

/*-------------------------------------------------------------------------
  Includes non re entry
  -------------------------------------------------------------------------*/
#ifndef I_LDB_TOS_H
#define I_LDB_TOS_H (1)

#if defined(__cplusplus)
#define extern extern "C"
#endif

/*-------------------------------------------------------------------------
  Included files to resolve specific definitions in this file

  #include <system_file_name.h>
  #include "project_file_name.h"

#ifndef COMPILATION_NATIVE	// Target specific file name
  #include <system_file_name.h>
  #include "project_file_name.h"
#endif
  -------------------------------------------------------------------------*/
#include "deftypes.h"
#include "tosparam.h"

#ifdef TOS_PREEMPTIVE
#include "tos_ord.h"
#endif

#ifdef TOS_PERF_CNT_ENABLE
#include "TOS_PerfCnt.h"
#endif

#if defined(X90_PROJECT) && defined(TRACE_CPU_ACTIVE)
#include "ldb_ioc.h"
#endif

/*-------------------------------------------------------------------------
  Constant data

  #define cCMPConstantName   ((tType) ConstantValue)
  -------------------------------------------------------------------------*/
#define cLDBCPUTraceIdleTask    10
#define cLDBCPUTraceMainLoop    0
#define cLDBCPUTraceScheduler   1
#define cLDBCPUTraceIdleState   2

/*-------------------------------------------------------------------------
  Exported Macro

  #define mCMPMacroName   (MacroDefinition)
  -------------------------------------------------------------------------*/ 
//----- Interrupt routines -----
#ifdef TOS_PREEMPTIVE
  #define mLDBEnterInterrupt(Handle)  mLDBEnterCPUTrace(Handle);  \
                                      TOSEnterISR()

  #define mLDBLeaveInterrupt()        mLDBExitCPUTrace();         \
                                      TOSLeaveISR()
#else
  #define mLDBEnterInterrupt(Handle)  mLDBEnterCPUTrace(Handle)
  #define mLDBLeaveInterrupt()        mLDBExitCPUTrace()
#endif

//----- Trace CPU -----
// You can trace the CPU load by define TRACE_CPU_ACTIVE in your project compilation options.
#ifdef TRACE_CPU_ACTIVE
  #ifdef X90_PROJECT
    #define mLDBInitCPUTrace(Handle)  LDBHandleCPU = (Handle)

    #define mLDBEnterCPUTrace(Handle) LDBHandleCPU = (Handle); \
                                      LDBHandleTimeStamp = mLDBIocReadCounter(mLDBTraceCpuTimerID)

    #define mLDBExitCPUTrace()        LDBHandleCPU = 255; \
                                      LDBHandleTimeStamp = mLDBIocReadCounter(mLDBTraceCpuTimerID)
    
    #define mLDBTraceCpuTimerID       Timer50  
  
  #else
    #define mLDBInitCPUTrace(Handle)  LDBHandleCPU = (Handle)

    #define mLDBEnterCPUTrace(Handle) LDBHandleCPU = (Handle)

    #define mLDBExitCPUTrace()        LDBHandleCPU = 255;
  #endif

#elif defined(TOS_PERF_CNT_ENABLE)
  #define mLDBInitCPUTrace(Handle) 

  #define mLDBEnterCPUTrace(Handle) mTOSPerfCntEnter(Handle)

  #define mLDBExitCPUTrace()        mTOSPerfCntExit()

#elif defined(_QAC_)
extern void NOP(void);
  #define mLDBInitCPUTrace(Handle)    NOP()
  #define mLDBEnterCPUTrace(Handle)   NOP()
  #define mLDBExitCPUTrace()          NOP()
#else
  #define mLDBInitCPUTrace(Handle)
  #define mLDBEnterCPUTrace(Handle)
  #define mLDBExitCPUTrace()
#endif

/*-------------------------------------------------------------------------
  Exported type

  struct  sCMPStructureName { ... };
  union   uCMPUnionName { ... };
  enum    eCMPEnumerationName { ... };
  typedef Expression tCMPTypeName;

  -------------------------------------------------------------------------*/
// You can trace the CPU load by define TRACE_CPU_ACTIVE in your project compilation options.
#ifdef TRACE_CPU_ACTIVE
// We use a type with size of data registers of the micro
typedef REG tLDBHandleCPU;
#ifdef X90_PROJECT
typedef U8 tLDBHandleTimer; // corresponding to timer used
#endif
#endif

/*-------------------------------------------------------------------------
  Exported data

  extern  tType   CMPVariableName;
  extern  tType*  pCMPVariableName; 
  -------------------------------------------------------------------------*/ 
// You can trace the CPU load by define TRACE_CPU_ACTIVE in your project compilation options.
#ifdef TRACE_CPU_ACTIVE
// This data must be defined by LDB
extern MEM_FAST volatile tLDBHandleCPU LDBHandleCPU;
#ifdef X90_PROJECT
extern MEM_FAST volatile tLDBHandleTimer LDBHandleTimeStamp;
#endif
#endif

/*-------------------------------------------------------------------------
  Constant exported data

  extern const tType  CMPVariableName;
  -------------------------------------------------------------------------*/ 

/*-------------------------------------------------------------------------
  Exported functions

  extern tReturnType CMPFunctionName(tTypeArgument1 ArgumentName1, ... );
  -------------------------------------------------------------------------*/ 
#if defined(__cplusplus)
  #undef extern //extern "C"
#endif

/*-------------------------------------------------------------------------
  End of includes non re entry
  -------------------------------------------------------------------------*/
#endif /* I_LDB_TOS_H */

