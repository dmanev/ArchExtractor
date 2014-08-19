/*============================================================================
  Project ......................... PROJET
  Component ....................... IHMParam
  File revision.................... $Revision:   1.0  $
  Last modification date .......... $Modtime:   04 Feb 2009 16:32:34  $
  -------------------------------------------------------------------------
  Copyright ... This software is JCI property. Duplication or
                disclosure is prohibited without JCI written permission
  ------------------------------------------------------------------------- 

  - Macros, constants and types which are not exported are defined in 
    this file
  - Variables and functions which are not exported are defined in this 
    file with the static key word
  
  -------------------------------------------------------------------------
  Comments on the component (role, algorithm, structure, limitations,
           defined tasks and events...)
  - Role :
  
  -------------------------------------------------------------------------
  IHMParam.cpp file review : 

   $Log:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/EXT_CMP/CPP_CMP/STK/SIMUL/ParamLDB/IHMPARAM.CPP-arc  $
// 
//    Rev 1.0   04 Feb 2009 17:02:40   adzhelp
// Initial revision.
 * 
 *    Rev 1.1   31 Jan 2005 11:38:50   abarbae
 * PON URD42 DEV 2379 / PON URD42 BODY_SW 784 : Apply new coding rules base types
 * 
 *    Rev 1.0   Apr 30 2003 08:14:26   abarbae
 * Initial revision.
 * 
 *    Rev 1.0   Oct 04 2002 15:36:22   guillen
 * Initial revision.

  ==========================================================================*/

/*--------------------------------------------------------------------------
  Body Identification
  --------------------------------------------------------------------------*/
#define IHMParam "IHMParam"

/*-------------------------------------------------------------------------
  Included files

  #include <system_file_name.h>
  #include "project_file_name.h"
  --------------------------------------------------------------------------*/
  #include "config.h"

/*--------------------------------------------------------------------------
  Local constants

  #define cConstantName   ((tType) ConstantValue)
  --------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------
  Local macro

  #define mMacroName   (MacroDefinition)
  --------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------
  Local type

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
  Constant local Data

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

/*--------------------------------------------------------------------------
  Exported function prototypes
  
  static tTypeRetour FunctionName(tTypeArgument1 ArgumentName1, ... );
  --------------------------------------------------------------------------*/
#ifdef IHM_OPENGL
extern void OpenGl_Init_Param(void);
#endif

// LDB Channels
// TODO : Add the initialization exported functions of LDBPC Channels
//extern void Initxxx(void);

// DAT Components
// TODO : Add the initialization exported functions of DAT component
//extern void InitDatpcxxx(void);


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
//{
//}

/*============================================================================
  DESCRIPTION : General initialisation of the IHM.
  
  PARAMETERS (Type,Name,Min,Max) :   none

  RETURN VALUE :   none
 
  DESIGN INFORMATION :   refer to Detailed Design Document
  ==========================================================================*/
void IHM_Init_Param(void)
{
#ifdef IHM_OPENGL
	OpenGl_Init_Param();
#endif
}

