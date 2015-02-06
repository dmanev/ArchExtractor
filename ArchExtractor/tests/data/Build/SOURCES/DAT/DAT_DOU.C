/****************************************************************************
  Project ......................... STANDARD
  Component ....................... dat_Dou
  File revision.................... 
  Last modification date .......... 
  -------------------------------------------------------------------------
  Copyright ... This software is JCI property. Duplication or
                disclosure is prohibited without JCI written permission
  ------------------------------------------------------------------------- 

  - Macros, constants et types which are not exported are defined in 
    this file
  - Variables and functions which are not exported are defined in this 
    file with the static keyword
  
  -------------------------------------------------------------------------
  Comments about the component (role, algorithm, structure, limitations,
           defined tasks and events...)
  - Role :
  
  -------------------------------------------------------------------------
  dat_sor.c file review : 

   See PVCS Base

*****************************************************************************/

/*--------------------------------------------------------------------------
  Body Identification
  --------------------------------------------------------------------------*/
#define dat_Dou  "dat_Dou"

/*--------------------------------------------------------------------------
  Included files

  #include <system_file_name.h>
  #include "project_file_name.h"
  --------------------------------------------------------------------------*/
#include "lib.h"
#include "tos.h"

#include "dat_Dou.h"

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

#define    cSleepState              (tDATDouState)0
#define    cWakeUpState             (tDATDouState)1

/*--------------------------------------------------------------------------
  Local data

  static  tType   VariableName;
  static  tType*  pVariableName; 
  --------------------------------------------------------------------------*/
static tTOSAlarm  PeriodicAlarm;

static tDATDouState     Status;
static tMsg       OutputMsg;

/*--------------------------------------------------------------------------
  Constant local Data

  static const tType  VariableName;
  --------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------
  Exported data

  tType   CMPVariableName;      (CMP: 3 characters to identify this component)
  tType*  pCMPVariableName;     (CMP: 3 characters to identify this component)
  --------------------------------------------------------------------------*/
U8 DATDouOutputBuffer[cDATDouOutputBufferSizeInBytes];

/*--------------------------------------------------------------------------
  Constant exported data
 
  const tType   CMPVariableName;(CMP: 3 characters to identify this component)
  --------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------
  Local function prototypes
  
  static tTypeRetour FunctionName(tTypeArgument1 ArgumentName1, ... );
  --------------------------------------------------------------------------*/

/****************************************************************************
*...........................................................................*
*............................ LOCAL FUNCTIONS ..............................*
*...........................................................................*
****************************************************************************/

/****************************************************************************
*...........................................................................*
*........................... EXPORTED FUNCTIONS.............................*
*...........................................................................*
****************************************************************************/
/*============================================================================
  DESCRIPTION : Initialise DAT_SOR component
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void DATDouInit(const U8*pBuffer)
{
    mLIBmemcpy(DATDouOutputBuffer, pBuffer, cDATDouOutputBufferSizeInBytes);
    OutputMsg.pBuffer = DATDouOutputBuffer;
    OutputMsg.Lng    = cDATDouOutputBufferSizeInBytes;

    Status      = cSleepState;
    if(Status){} //to avoid a warning in release mode
}

/*============================================================================
  DESCRIPTION : Write the lgical output buffer
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void DATDouRefreshOutputTask(void)
{
    DATPouPrepareRefresh();
    LDBSendWithoutAddr(cLDBChannelDou,&OutputMsg);
}

/*============================================================================
  DESCRIPTION : This function is the call back called from 
                the LDB after writing logical output
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void DATDouCallBackTxWithoutAddr(tStatus Statut)
{
    mLIBassert(Statut == cLDBCorrect);
    Statut = Statut;  // pour eviter un warning a la compilation sur cible
}


/*============================================================================
  DESCRIPTION : 
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void DATDouEnterNominalMode(void)
{
    mLIBassert(Status != cWakeUpState);
    Status = cWakeUpState;

    PeriodicAlarm.TaskID = cTOSTaskID_WriteLogical;
    TOSSetRelAlarm(&PeriodicAlarm, 0, mTOSConvMsEnTickAlarm(cDATDouWritingPeriodeValueMs));
    LDBControl(cLDBChannelDou,cLDBDouEnterNominalMode);
}

/*============================================================================
  DESCRIPTION : Start the output alarm
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void DATDouEnterSleepMode(void)
{
    mLIBassert(Status == cWakeUpState);
    TOSCancelAlarm(&PeriodicAlarm);

#ifdef DATDOU_UPDATE_OUTPUT_BEFORE_SLEEPING
    DATDouRefreshOutputTask();
#endif
    Status = cSleepState;
    LDBControl(cLDBChannelDou,cLDBDouEnterSleepMode);
}

/*============================================================================
  DESCRIPTION : Control callback
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void DATDouCallBackEndCtrl(tCtrl Ctrl, tStatus Statut)
{
    mLIBassert(Statut == cLDBCorrect);
    Statut = Statut;  // pour eviter un warning a la compilation sur cible
    Ctrl = Ctrl;      // pour eviter un warning a la compilation sur cible
}


