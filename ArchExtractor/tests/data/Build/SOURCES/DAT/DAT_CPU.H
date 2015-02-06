/*============================================================================
  Project ......................... PROJECT
  Component ....................... DAT_CPU
  File revision.................... :   1.3  $
  Last modification date .......... $Modtime:   04 Feb 2009 16:32:26  $
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
  DAT_CPU.h file review :
  


  ==========================================================================*/

#ifndef I_DAT_CPU_H
#define I_DAT_CPU_H (1)

/*-------------------------------------------------------------------------
  Included files to resolve specific definitions in this file

  #include <system_file_name.h>
  #include "project_file_name.h"
  -------------------------------------------------------------------------*/

#include "deftypes.h"

/*-------------------------------------------------------------------------
  Constant data

  #define cCMPConstantName   ((tType) ConstantValue)
  -------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
  Exported Macros

  #define mCMPMacroName   (MacroDefinition)
  -------------------------------------------------------------------------*/ 
#define mDATControlCpu(CTRL)            mDATControlCpu##CTRL()
#define mDATControlGraphEngine(CTRL)    mDATControlCpu##CTRL()
#define mDATControlCpuStart()           (DATCpuLeaveSleep())
#define mDATControlCpuStop()            (DATCpuEnterSleep())
#define mDATControlCpuReset()           (LDBReset())

#define mDATReadU32BitUnUsedStackSizeDefault() 	(DATCpuGetUnUsedStackSize())
#define mDATReadU32UnUsedStackSizeDefault() 	(DATCpuGetUnUsedStackSize())

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

extern void DATCpuInit(void);
extern void DATCpuIdleTask(void);
extern void DATCpuRefreshWatchDogTask(void);

extern void DATCpuLeaveSleep(void);
extern void DATCpuEnterSleep(void);

extern U32 DATCpuGetUnUsedStackSize(void); // in bytes, if = 0 then the measure is not performed (enabled), see DAT_CPUp.h for how to enable/disable it

#endif   /* I_DAT_CPU_H */
