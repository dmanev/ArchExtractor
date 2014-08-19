/*============================================================================
  Project ......................... COMMON
  Component ....................... LIB_PCF_S01
  File revision.................... 
  Last modification date .......... 
  -------------------------------------------------------------------------
  Copyright ... This software is JCAE property. Duplication or
                disclosure is prohibited without JCAE written permission
  ------------------------------------------------------------------------- 
    
  - This file should only contain data useful to the programmer to use
    this component
  - Component exported macros, constants and types are defined in this file
  - Component exported variables and functions are declared in this file 
    with the "extern" keyword
  
  -------------------------------------------------------------------------
  lib_pcf_s01.h file review :
  
    See PVCS revision

  ==========================================================================*/

#ifndef I_LIB_PCF_S01_H
#define I_LIB_PCF_S01_H (1)

/*-------------------------------------------------------------------------
  Included files to resolve specific definitions in this file

  #include <system_file_name.h>
  #include "project_file_name.h"
  -------------------------------------------------------------------------*/
#include "deftypes.h"

/*-------------------------------------------------------------------------
  Constant data

  #define cLAYCmpConstantName   ((tType) ConstantValue)
  -------------------------------------------------------------------------*/
// Version ( This constant must be increased each time this file is modified )
// MSB: Spec version ( S01 ),   LSB: API version ( 00 )
#define cLIBPcfVersion                            ((tLIBPcfVersion)0x0100)

/*-------------------------------------------------------------------------
  Exported Macros

  #define mLAYCmpMacroName   (MacroDefinition)
  -------------------------------------------------------------------------*/ 
#define mLIBPcfGetRequiredVersion()               ( LIBPcfVersion )

/*-------------------------------------------------------------------------
  Exported type

  struct  sLAYCmpStructureName { ... };
  union   uLAYCmpUnionName { ... };
  enum    eLAYCmpEnumerationName { ... };
  typedef Expression tLAYCmpTypeName;

  -------------------------------------------------------------------------*/
typedef U16 tLIBPcfVersion;

#ifndef X90_PROJECT
typedef void (*tpTOSTaskFct)(void); //taken from Tos.h
#endif

/*-------------------------------------------------------------------------
  Exported data

  extern  tType   LAYCmpVariableName;
  extern  tType*  pLAYCmpVariableName; 
  -------------------------------------------------------------------------*/ 
extern MEM_FAST U32 LIBPcfRandomNumber;
extern MEM_FAST U32 LIBPcfCipheredData;
extern MEM_FAST U8* pLIBPcfSecretKey;
extern MEM_FAST U8* pLIBPcfIdentifier;
extern tpTOSTaskFct pLIBPcfRefresh;

/*-------------------------------------------------------------------------
  Constant exported data

  extern const tType  LAYCmpVariableName;
  -------------------------------------------------------------------------*/ 

/*-------------------------------------------------------------------------
  Exported functions

  extern tReturnType LAYCmpFunctionName(tTypeArgument1 ArgumentName1, ... );
  -------------------------------------------------------------------------*/ 

/*-------------------------------------------------------------------------
  Constant exported data

  extern const tType  CMPVariableName;
  -------------------------------------------------------------------------*/ 
extern const tLIBPcfVersion LIBPcfVersion;

/*-------------------------------------------------------------------------
  Exported functions

  extern tReturnType CMPFunctionName(tTypeArgument1 ArgumentName1, ... );
  -------------------------------------------------------------------------*/ 
extern MEM_TYPE void LIBPcfInitialize(void);
extern MEM_TYPE void LIBPcfCipherFunction(U8 DataLength);

#endif   /* I_LIB_PCF_S01_H */
