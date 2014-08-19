/*============================================================================
  Project ......................... common
  Component ....................... LIB_RND
  File revision.................... 
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
  LIB_RND.c file review : 


  ==========================================================================*/

/*--------------------------------------------------------------------------
  Body Identification
  --------------------------------------------------------------------------*/

#define LIBRnd   "LIB_RND"

/*-------------------------------------------------------------------------
  Included files

  #include <system_file_name.h>
  #include "project_file_name.h"
  --------------------------------------------------------------------------*/
#include "LIB_RND.h"

/*--------------------------------------------------------------------------
  Local constants

  #define cConstantName   ((tType) ConstantValue)
  --------------------------------------------------------------------------*/
// Constants for the algorithm of generation of a random number
#define cConstA                 ((U32) 0x0343FD)
#define cConstB                 ((U32) 0x269EC3)

/*--------------------------------------------------------------------------
  Local macross

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
  DESCRIPTION : Calculate a random number
  
  PARAMETERS (Type,Name,Min,Max) :  U32 ulSeedValue

  RETURN VALUE :  calculated number
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
U32 LIBCalculateRandomNb(U32 ulSeedValue)
{
  static U32 ulCurrentValue;

  // take in account the new Input Number
  ulCurrentValue += ulSeedValue; 
  ulCurrentValue  = ((cConstA * ulCurrentValue) + cConstB);

  return (ulCurrentValue);
}
