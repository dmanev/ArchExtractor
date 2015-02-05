/*============================================================================
  Project ......................... STANDARD
  Component ....................... Lap_sup
  File revision.................... :   1.1  $
  Last modification date .......... $Modtime:   04 Feb 2009 16:32:18  $
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

  - Role : Supervisor of STK project
  
  -------------------------------------------------------------------------
  Lap_sup.c file review : 


  ==========================================================================*/

/*--------------------------------------------------------------------------
  Body Identification
  --------------------------------------------------------------------------*/

#define lap_sup  "lap_sup"


/*-------------------------------------------------------------------------
  Included files

  #include <system_file_name.h>
  #include "project_file_name.h"
  --------------------------------------------------------------------------*/

#include "lib.h"
#include "tos.h"
#include "dat.h"
#include "lap_sup.h"
#include "lap_sup.hgr"
#include "lap_supp.h"

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
static  BOOL  SleepMode;
static tTOSTimer  MinActiveTimer;


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
  DESCRIPTION : Send a Control to Enter in Starting step State.
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void LAPSupControlEnterStartingStepState( void )
{
    TOSSendControl(cTOSControlEnterStartingStepState);
}

/*============================================================================
  DESCRIPTION : Send a Control Leave from the Starting Step State
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void LAPSupControlLeaveStartingStepState( void )
{
    TOSSendControl(cTOSControlLeaveStartingStepState);
}

/*============================================================================
  DESCRIPTION : Send a Control to enter in DAT Active State.
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void LAPSupControlDATEnterActiveState( void )
{
    TOSSendControl(cTOSControlDATEnterActiveState);
}

/*============================================================================
  DESCRIPTION : Send a Control to enter in LAP Active State.
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void LAPSupControlLAPEnterActiveState( void )
{
    TOSSendControl(cTOSControlLAPEnterActiveState);
}

/*============================================================================
  DESCRIPTION : Send Controls to leave LAP and DAT Active State.

  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void LAPSupControlLeaveActiveState( void )
{
    TOSSendControl(cTOSControlLAPLeaveActiveState);
    TOSSendControl(cTOSControlDATLeaveActiveState);
}


/*============================================================================
  DESCRIPTION : Read the Signal to check if an Active Sleep is Requested.
  
  PARAMETERS (Type,Name,Min,Max) :   none

  RETURN VALUE : retrun cTrue if somebody send a cTOSSignalActiveSleepRequested
                 signal, otherwise cFalse.
 
  DESIGN INFORMATION :   refer to Detailed Design Document
  ==========================================================================*/
BOOL LAPSupActiveSleepRequested( void )
{
    return(TOSReadSignal(cTOSSignalActiveSleepRequested));
}

/*============================================================================
  DESCRIPTION : Read the Signal to check if an wake up is Requested.
  
  PARAMETERS (Type,Name,Min,Max) :   none

  RETURN VALUE : retrun cTrue if somebody send a cTOSSignalWakeUpRequested
                 signal, otherwise cFalse.
 
  DESIGN INFORMATION :   refer to Detailed Design Document
  ==========================================================================*/
BOOL LAPSupWakeUpRequested( void )
{
    return(TOSReadSignal(cTOSSignalWakeUpRequested));
}

/*============================================================================
  DESCRIPTION : Ask to the subscriber components if anyone maintain 
                the starting step.
  
  PARAMETERS (Type,Name,Min,Max) :   none

  RETURN VALUE :   none
 
  DESIGN INFORMATION :   refer to Detailed Design Document
  ==========================================================================*/
BOOL LAPSupNobodyMaintainStartingStepState( void )
{
    TOSSendControl(cTOSControlIsAnybodyMaintainStartingStepState);

    return(TOSReadSignal(cTOSSignalSomebodyMaintainStartingStepState) == cFalse);
}

/*============================================================================
  DESCRIPTION : Ask to the subscriber components if anyone maintain 
                the ActiveSleep State.
  
  PARAMETERS (Type,Name,Min,Max) :   none

  RETURN VALUE :   none
 
  DESIGN INFORMATION :   refer to Detailed Design Document
  ==========================================================================*/
BOOL LAPSupNobodyMaintainActiveSleepState( void )
{
    TOSSendControl(cTOSControlIsAnybodyMaintainActiveSleepState);

    return(TOSReadSignal(cTOSSignalSomebodyMaintainActiveSleepState) == cFalse);
}

/*============================================================================
  DESCRIPTION : Ask to the subscriber components if anyone maintain 
                the Active State.
  
  PARAMETERS (Type,Name,Min,Max) :   none

  RETURN VALUE :   none
 
  DESIGN INFORMATION :   refer to Detailed Design Document
  ==========================================================================*/
BOOL LAPSupNobodyMaintainActiveState( void )
{
    TOSSendControl(cTOSControlIsAnybodyMaintainActiveState);

    return(TOSReadSignal(cTOSSignalSomebodyMaintainActiveState) == cFalse);
}

/*============================================================================
  =========================== EXPORTED FUNCTIONS =============================
  ==========================================================================*/

/*============================================================================
  DESCRIPTION : Request an Active Sleep State.
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void LAPSupActiveSleepRequest( void )
{
    if(SleepMode)
    {
        mDATControl( Cpu, Start );
        SleepMode = cFalse;
    }
    TOSWriteSignal(cTOSSignalActiveSleepRequested);
}

/*============================================================================
  DESCRIPTION : Request a Wake Up.
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void LAPSupWakeUpRequest( void )
{
    if(SleepMode)
    {
        mDATControl( Cpu, Start );
        SleepMode = cFalse;
    }
    TOSWriteSignal(cTOSSignalWakeUpRequested);
}

/*============================================================================
  DESCRIPTION : Enter in sleep state.
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void LAPSupEnterSleep( void )
{
    /* PON URD42 DEV 1104 / PON URD42 BODY_SW 338 */
    TOSReadSignal(cTOSSignalActiveSleepRequested);

    SleepMode = cTrue;
    mDATControl( Cpu, Stop );
}

/*============================================================================
  DESCRIPTION : Check if the minimun time to stay in active state is elapse.
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
BOOL LAPSupMinimumActiveTimeIsElapsed( void )
{
    return(TOSIsTimerElapsed(&MinActiveTimer, 
                                  cLAPSupMinActiveTimerMs / cTOSTimerTickMs));
}

/****************************************************************************
  DESCRIPTION         : Stay Active during cLAPSupMinActiveTimerMs ms after 
                        a entering in active state or a wake up Request. 
  PARAMETERS          : None
  (Type,Name,Min,Max) 

  RETURN VALUE        : None

  DESIGN INFORMATION  : Refer to Detailed Design Document

*****************************************************************************/
void LAPSupMinimumActiveTime(void)
{
    TOSStartTimer(&MinActiveTimer);
}

/*============================================================================
  DESCRIPTION : The Application stop.
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void LAPShutdownHook(U16 CodeErreur)
{
    // We enter this function only for target test.
    // Place a breackpoint on this function. Coderreur parameter indicates
    // errors number detected during the test.

    LDBReset();
}

/*============================================================================
  DESCRIPTION : The Application start.

  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void LAPStartupHook( void )
{
    // Components init
    LDBInit();
    TOSInit();

    // TODO : Component init calls
    TOSSendControl(cTOSControlDATInitialize);
    TOSSendControl(cTOSControlLAPInitialize);

    // Alarm authorization
    TOSStartAlarm();

    mDATControl( Cpu, Start );
    SleepMode = cFalse;

    TOSSeqActivateGraph( cTOSSeqGraphIdSupervisor );
}
