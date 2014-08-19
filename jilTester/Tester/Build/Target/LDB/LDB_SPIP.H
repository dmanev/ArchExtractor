/*============================================================================
  Project ......................... PROJECT
  Component ....................... ldb_spip.h
  File revision.................... :   1.0  $
  Last modification date .......... $Modtime:   Mar 07 2008 09:36:32  $
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
  ldb_spip.h file review :
  
    :   P:/STANDARD/AEH/STK/PVCS/archives/STK/CMP/SOURCES/LDB/LDB_SPI/ldb_spip.h-arc  $
 * 
 *    Rev 1.0   Aug 05 2003 10:41:12   agrandm
 * Initial revision.

  ==========================================================================*/

/*-------------------------------------------------------------------------
  Includes non re entry
  -------------------------------------------------------------------------*/
#ifndef I_LDB_SPIP_H
#define I_LDB_SPIP_H (1)

/*-------------------------------------------------------------------------
  Included files to resolve specific definitions in this file

  #include <system_file_name.h>
  #include "project_file_name.h"
  -------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
  Constant data

  #define cCMPConstantName   ((tType) ConstantValue)
  -------------------------------------------------------------------------*/
/* SPI format used */
//LR : data is latched at the rising edge  (CPOL=0 ,CPHA=0) or (CPOL=1 ,CPHA=1)
//LF : data is latched at the falling edge (CPOL=1 ,CPHA=0) or (CPOL=0 ,CPHA=1)
//(see doc NT 0308021 for details)

// uncomment the following compile directive to use the mode
  #define LDBSPI_FORMAT_LR_USED
//#define LDBSPI_FORMAT_LF_USED


/* SCLK pin state in idle mode*/
//  0:  low level
//  1 : high level

  #define cLDBSpiSckLevelInIdleMode   0

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

/*-------------------------------------------------------------------------
  End of includes non re entry
  -------------------------------------------------------------------------*/
#endif //I_LDB_SPIP
