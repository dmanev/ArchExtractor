/*============================================================================
  Project ......................... Common
  Component ....................... ldb_tim
  File revision.................... :   1.0  $
  Last modification date .......... $Modtime:   04 Feb 2009 16:32:16  $
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
  ldb_tim.h file review :


  ==========================================================================*/

#ifndef I_LDB_TIM_H
#define I_LDB_TIM_H (1)

/*-------------------------------------------------------------------------
  Included files to resolve specific definitions in this file

  #include <system_file_name.h>
  #include "project_file_name.h"
  -------------------------------------------------------------------------*/
#include "ldb.h"
#include "ldb_timp.h"

/*-------------------------------------------------------------------------
  Constant data

  #define cCMPConstantName   ((tType) ConstantValue)
  -------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
  Exported Macros

  #define mCMPMacroName   (MacroDefinition)
  -------------------------------------------------------------------------*/ 
#define mLDBTimConvUsInTick(Tps)  (((U32)Tps * 1000UL) / cLDBTick)
#define mLDBTimConvMsInTick(Tps)  (((U32)Tps * 1000000UL) / cLDBTick)

#define mLDBTimInit() LDBTimInit()
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
// Initialisation
extern void LDBTimInit(void);
#ifdef TOS_PERF_CNT_ENABLE
extern void LDBTimpInit(void);
#endif


// Time out management
extern void LDBTimStart(void);
extern void LDBTimStop(void);

#endif   /* I_LDB_TIM_H */
