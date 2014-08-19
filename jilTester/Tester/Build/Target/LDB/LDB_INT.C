/*============================================================================
  Project ......................... STANDARD
  Component ....................... LDB_INT
  File revision.................... :   1.0  $
  Last modification date .......... $Modtime:   Jul 24 2009 14:37:36  $
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
  cmp.c file review : 


  ==========================================================================*/

/*--------------------------------------------------------------------------
  Body Identification
  --------------------------------------------------------------------------*/

#define LDB_INT   "LDB_INT"

/*-------------------------------------------------------------------------
  Included files

  #include <system_file_name.h>
  #include "project_file_name.h"
  --------------------------------------------------------------------------*/

#include "ldb_int.h"


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


/*--------------------------------------------------------------------------
  Constant local data

  static const tType  VariableName;
  --------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------
  Exported data

  tType   CMPVariableName;      (CMP: 3 characters to identify this component)
  tType*  pCMPVariableName;     (CMP: 3 characters to identify this component)
  --------------------------------------------------------------------------*/

MEM_FAST volatile tLDBIntStateGroup1 LDBIntGroup1;
MEM_FAST volatile U8             LDBIntLevel;

#ifdef TRACE_CPU_ACTIVE
    // This data must be defined by LDB
MEM_FAST volatile tLDBHandleCPU LDBHandleCPU;
 
#endif

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
  DESCRIPTION :
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
/*type FunctionName(...)
{
}*/
void LDBIntInit(void)
{
    // After Startup all interrupts are disable
    LDBIntGroup1.Reg.MK0H = 0xFF;
    LDBIntGroup1.Reg.MK1L = 0xFF;
    LDBIntLevel = 0;

    // Priority Initialisation
    PR0L = cLDBIntPR0L;
    PR0H = cLDBIntPR0H;
    PR1L = cLDBIntPR1L;
#ifdef cLDBHarMicro78K0_F0536    
    PR1H = cLDBIntPR1H;
#endif
}

