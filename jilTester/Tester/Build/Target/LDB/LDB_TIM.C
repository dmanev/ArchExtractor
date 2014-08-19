/*============================================================================
  Project ......................... Common
  Component ....................... ldb_tim
  File revision.................... :  
  Last modification date .......... 
  -------------------------------------------------------------------------
  Copyright ... This software is JCI property. Duplication or
                disclosure is prohibited without JCI written permission
  ------------------------------------------------------------------------- 

  - Macros, constants and types which are not exported are defined in 
    this file
  - Variables and functions which are not exported are defined in this 
    file with the static key word
  
  -------------------------------------------------------------------------
  Comments about the component (role, algorithm, structure, limitations,
           defined tasks and events...)
  - Role :
  
  -------------------------------------------------------------------------
  ldb_tim.c file review : 


  ==========================================================================*/

/*--------------------------------------------------------------------------
  Body Identification
  --------------------------------------------------------------------------*/
#define ldb_tim   "ldb_tim"

/*-------------------------------------------------------------------------
  Included files

  #include <system_file_name.h>
  #include "project_file_name.h"
  --------------------------------------------------------------------------*/

#include "lib.h"
#include "ldb.h"
#include "ldb_ioc.h"
#include "ldb_int.h"
#include "ldb_har.h"
#include "ldb_tim.h"
#ifdef cLIBStkTosPerfCnt_Used
#ifdef TOS_PERF_CNT_ENABLE
 #include "TOS_PerfCnt.h"
#endif
#endif

/*--------------------------------------------------------------------------
  Local constants

  #define cConstantName   ((tType) ConstantValue)
  --------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------
  Local macros

  #define mMacroName   (MacroDefinition)
  --------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------
  Local types

  struct  sStructureName { ... };
  union   uUnionName { ... };
  enum    eEnumerationName { ... };
  typedef Expression tTypeName;
  --------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------
  Local data

  static  tType   VariableName;
  static  tType*  pVariableName; 
  --------------------------------------------------------------------------*/
static U8    TimerTosPeriod;
static U8    TimerTosCounter;

/*--------------------------------------------------------------------------
  Constant local data

  static const tType  VariableName;
  --------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------
  Exported data

  tType   CMPVariableName;      (CMP: 3 characters to identify this component)
  tType*  pCMPVariableName;     (CMP: 3 characters to identify this component)
  --------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------
  Constant exported data
 
  const tType   CMPVariableName;(CMP: 3 characters to identify this component)
  --------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------
  Local function prototypes
  
  static tTypeRetour FunctionName(tTypeArgument1 ArgumentName1, ... );
  --------------------------------------------------------------------------*/


/*============================================================================
  =========================== LOCAL FUNCTIONS ================================
  ==========================================================================*/

/*============================================================================
  DESCRIPTION :
  
  PARAMETERS (Type,Name,Min,Max) :   none

  RETURN VALUE :   none
 
  DESIGN INFORMATION :   refer to Detailed Design Document
  ==========================================================================*/
//static type FunctionName(...)

/*============================================================================
  =========================== EXPORTED FUNCTIONS =============================
  ==========================================================================*/
/*============================================================================
  DESCRIPTION         : Initialize timer
  
  PARAMETERS          : None
  (Type,Name,Min,Max) 

  RETURN VALUE        : None
 
  DESIGN INFORMATION  : Refer to Detailed Design Document
============================================================================*/
void LDBTimInit(void)
{
   // Initialize timer
   mLDBIocSetTimerModeIntervalTimer(cLDBHarRealTimeTimer);
   //    mLDBHarSpecificInitRealTimeTimer();
   LDBTimStart();
    #ifdef TOS_PERF_CNT_ENABLE
    LDBTimpInit();
    #endif
}

/*============================================================================
  DESCRIPTION         : Start ldb_tim component
  
  PARAMETERS          : None
  (Type,Name,Min,Max) 

  RETURN VALUE        : Always 0 for OSEK compatibility
 
  DESIGN INFORMATION  : Refer to Detailed Design Document
  ==========================================================================*/
void LDBTimStart(void)
{
//    Verify that LDBTick is upper a multiple of cLDBHarTickInNsRealTimeTimer
//    mLIBassert( ((cLDBTick / cLDBHarTickInNsRealTimeTimer) *cLDBHarTickInNsRealTimeTimer)
//                == cLDBTick);

    mLIBassert((cLDBTick/cLDBHarTickInNsRealTimeTimer) < (1UL << mLDBIocGetType(cLDBHarRealTimeTimer)))

    mLDBIocWriteTrigger(cLDBHarRealTimeTrigger, ((cLDBTick / cLDBHarTickInNsRealTimeTimer)-1));
    mLDBIntClearIsrRequestFlag(cLDBHarInterruptRealTimeIt);
    mLDBIntEnableIsr(cLDBHarInterruptRealTimeIt);
    mLDBIocStartTimer(cLDBHarRealTimeTimer);

}

/*============================================================================
  DESCRIPTION         : Stop ldb_tim component
  
  PARAMETERS          : None
  (Type,Name,Min,Max) 

  RETURN VALUE        : Always 0 for OSEK compatibility
 
  DESIGN INFORMATION  : Refer to Detailed Design Document
  ==========================================================================*/
void LDBTimStop(void)
{
    mLDBIocStopTimer(cLDBHarRealTimeTimer);
    mLDBIntDisableIsr(cLDBHarInterruptRealTimeIt);
}

/*============================================================================
  DESCRIPTION         : Start Tempo TimeOutRef
  
  PARAMETERS          : tTimerRef TimeOutRef : timout reference number (0 to cLDBTimNbOfExternalTimeOut-1)
                        tDelay Duree         : duration in cLDBTick 
                        tpFunc pFunc         : function called a the time out expiration 
                        BOOL Periodique  : Automatic Reload of the timeout(cTrue or cFalse) 

  RETURN VALUE        : None
 
  DESIGN INFORMATION  : Refer to Detailed Design Document
  ==========================================================================*/
void LDBTimStartTimer( tTimerRef TimeOutRef, tDelay Duree)
{
   // Save period if periodic
   TimerTosPeriod = Duree -1;
   // Initialize count
   TimerTosCounter = TimerTosPeriod;  // +1 for ensure that tempo is upper that duree
}

/*============================================================================
  DESCRIPTION         : Stop Tempo TimeOutRef
  
  PARAMETERS          : tTimerRef TimeOutRef : timout reference number (0 to cLDBTimNbOfExternalTimeOut-1)
  RETURN VALUE        : Always 0 for OSEK compatibility
 
  DESIGN INFORMATION  : Refer to Detailed Design Document
  ==========================================================================*/
tDelay LDBTimStopTimer( tTimerRef TimeOutRef )
{
   return(TimerTosCounter);
}

/*============================================================================
  DESCRIPTION         : Real time interrupt
  
  PARAMETERS          : None
  (Type,Name,Min,Max) :

  RETURN VALUE        : None
 
  DESIGN INFORMATION  : Refer to Detailed Design Document
============================================================================*/

mLDBIntDeclareIsr(cLDBHarInterruptRealTimeIt)
{
   tTimerRef TimeOutRef;
   
   mLDBIntEnterIsr(cLDBHarInterruptRealTimeIt)
      
   // IT clearing
   mLDBIntClearIsrRequestFlag(cLDBHarInterruptRealTimeIt);
   mLaunchItSequencedTimeOut();

   // Calculate Tempos
   if (TimerTosCounter == 0)
   {
      TimerTosCounter = TimerTosPeriod;
      mLauchTosSequencedTimeOut();
   }
   else
   {
      TimerTosCounter--;
   }
   // Call callback
   mLDBIntLeaveIsr(cLDBHarInterruptRealTimeIt)
}
