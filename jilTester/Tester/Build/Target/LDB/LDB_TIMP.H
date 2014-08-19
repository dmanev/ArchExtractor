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
// -----------------------------------------------------------------------------
// $Date:   Nov 17 2009 11:21:28  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_TIM/LDB_TIMP.H-arc  $
// $Revision:   1.7  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_TIM/LDB_TIMP.H-arc  $
// 
//    Rev 1.7   Nov 17 2009 11:21:28   adzhelp
// Cm006675: Variables added and timer handling used in CPU trace configuration
// 
//    Rev 1.6   Jul 14 2009 10:19:50   adzhelp
// Cm005188: Alarm timeout callback removed from list
// 
//    Rev 1.5   Apr 27 2009 15:11:36   adzhelp
// Cm003265: LDBRfCallBackSleepTick() added into sleep timout list
// 
//    Rev 1.4   Apr 16 2009 10:34:48   adzhelp
// Cm003276: LDBTimStopSlowTimer() and LDBTimStartSlowTimer() added
// 
//    Rev 1.3   Apr 13 2009 15:20:24   adzhelp
// Cm003271: LDB_ALA timeout function added
// 
//    Rev 1.2   Mar 20 2009 14:53:46   adzhelp
// Cm003619: Added local timeout for LDB_KWP
// 
//    Rev 1.1   Mar 17 2009 14:54:18   adzhelp
// Cm003619: Add interface to use LDB timeouts
// 
//    Rev 1.0   04 Feb 2009 17:03:18   adzhelp
// Initial revision.
//******************************************************************************

#ifndef I_LDB_TIMP_H
#define I_LDB_TIMP_H (1)



/*-------------------------------------------------------------------------
  Included files to resolve specific definitions in this file

  #include <system_file_name.h>
  #include "project_file_name.h"
  -------------------------------------------------------------------------*/
#include "ldb_ioc.h"

 /*-------------------------------------------------------------------------
  Constant data

  #define cCMPConstantName   ((tType) ConstantValue)
  -------------------------------------------------------------------------*/

/************************
*  Timer configuration  *
************************/

// The value of cLDBTick must be defined in LDBparam.h

/*  // You must define this value with accordance to your Timer running period*/


/************************
*  TimeOut definitions  *
************************/
// Must be undefined when not using the TimeOut system
//#define TimerIsUsingTimeOutFunctions

// Period = cLDBTick
#define mLaunchItSequencedTimeOut()                                 \
    {                                                               \
        TimeOutRef = 0;                                             \
        TimeOutRef = TimeOutRef; /* disable compilation warning */  \
        /* Specify here list of functions called. Example: */       \
        /* mLDBTimCheckLaunchTimeOut(FunctionName); */              \
        /* ... */                                                   \
        mLDBTimCheckLaunchTimeOut(LDBKwpCallBackTimer);             \
    }

// Period = cTOSTickAlarmUs / 2
#define mLauchTosSequencedTimeOut()    TOSAlaCallBackTimer()

// Period = cLDBSleepTick
#define mLaunchSleepItSequencedTimeOut() \
    { \
        LDBSupCallBackSleepTimer(); \
        LDBRfCallBackSleepTick(); \
    }

/*-------------------------------------------------------------------------
  Exported Macros

  #define mCMPMacroName   (MacroDefinition)
  -------------------------------------------------------------------------*/ 
#define mLDBTimStartFastTimer() LDBTimStart()
#define mLDBTimStartSlowTimer() LDBTimStartSlowTimer()
#define mLDBTimStopFastTimer()  LDBTimStop()
#define mLDBTimStopSlowTimer()  LDBTimStopSlowtimer()

// Sequenced timeout macros (LDB timers):

// Timeout general macros (do not edit)
#define mLDBTimCheckLaunchTimeOut(TimeOutFunction)  \
    if (bLDBTimEnabled_##TimeOutFunction != cFalse) \
    {                                               \
        TimeOutFunction();                          \
    }

#define mLDBTimDefineTimeOut(TimeOutFunction)       \
    extern void TimeOutFunction(void);              \
    BOOL bLDBTimEnabled_##TimeOutFunction = cFalse;

#define mLDBTimDeclareTimeOut(TimeOutFunction)      \
    extern BOOL bLDBTimEnabled_##TimeOutFunction;

#define mLDBTimEnableTimeOut(TimeOutFunction) (bLDBTimEnabled_##TimeOutFunction = cTrue)
#define mLDBTimDisableTimeOut(TimeOutFunction) (bLDBTimEnabled_##TimeOutFunction = cFalse)

// Timeout parameterization macros
#ifdef ldb_tim
// Specify here list of each time out function. Example:
// mLDBTimDefineTimeOut(FunctionName);
// ....
   mLDBTimDefineTimeOut(LDBKwpCallBackTimer);
#else
// Specify here list of each time out function. Example:
// mLDBTimDeclareTimeOut(FunctionName);
// ....
   mLDBTimDeclareTimeOut(LDBKwpCallBackTimer);
#endif

#if defined(TRACE_CPU_ACTIVE) && defined(ldb_tim)
// Activate invocation of LDBTimpInit() in CPUTrace mode
#define TOS_PERF_CNT_ENABLE
#endif

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
extern void LDBTimStopSlowTimer(void);
extern void LDBTimStartSlowTimer(void);

extern void TOSAlaCallBackTimer(void);
extern void LDBSupCallBackSleepTimer(void);
extern void LDBRfCallBackSleepTick(void);

#endif   /* I_LDB_TIMP_H */
