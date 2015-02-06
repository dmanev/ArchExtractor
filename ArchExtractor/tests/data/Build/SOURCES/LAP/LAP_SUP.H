/*============================================================================
  Project ......................... STANDARD
  Component ....................... LAP_SUP
  File revision.................... :   1.0  $
  Last modification date .......... $Modtime:   04 Feb 2009 16:32:18  $
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
  lap_sup.h file review :
  


  ==========================================================================*/

#ifndef I_LAP_SUP_H
#define I_LAP_SUP_H (1)

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

extern void LAPSupActiveSleepRequest( void );
extern void LAPSupWakeUpRequest( void );

#endif   /* I_CMP_H */
