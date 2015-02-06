/****************************************************************************
  Project ......................... STANDARD
  Component ....................... dat_dou
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
  dat_dou.h file review :
  
   See PVCS Base

*****************************************************************************/

/*-------------------------------------------------------------------------
  Includes non re entry
  -------------------------------------------------------------------------*/
#ifndef I_DAT_DOU_H
#define I_DAT_DOU_H (1)

/*--------------------------------------------------------------------------
  Included files to resolve specific definitions in this file

  #include <system_file_name.h>
  #include "project_file_name.h"
  --------------------------------------------------------------------------*/
#include "dat_doup.h"
#include "dat_doux.h"

/*--------------------------------------------------------------------------
  Constant data

  #define cCMPConstantName   ((tType) ConstantValue)
  --------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------
  Exported Macros

  #define mCMPMacroName   (MacroDefinition)
  --------------------------------------------------------------------------*/ 

// Launch logical refresh
#define mDATDouRefreshOutput() TOSActivateTask(cTOSTaskID_WriteLogical)

/*--------------------------------------------------------------------------
  Exported types

  struct  sCMPStructureName { ... };
  union   uCMPUnionName { ... };
  enum    eCMPEnumerationName { ... };
  typedef Expression tCMPTypeName;

  --------------------------------------------------------------------------*/
typedef U8 tDATDou_ByteIndex;
typedef U8 tDATDou_BitIndex;

typedef U8 tDATDouState;

/*--------------------------------------------------------------------------
  Exported data

  extern  tType   CMPVariableName;
  extern  tType*  pCMPVariableName; 
  --------------------------------------------------------------------------*/ 
extern U8 DATDouOutputBuffer[];

/*--------------------------------------------------------------------------
  Constant exported data

  extern const tType  CMPVariableName;
  --------------------------------------------------------------------------*/ 

/*--------------------------------------------------------------------------
  Exported functions

  extern tReturnType CMPFunctionName(tTypeArgument1 ArgumentName1, ... );
  --------------------------------------------------------------------------*/ 
extern void DATDouInit(const U8*pBuffer);

extern void DATDouEnterNominalMode(void);
extern void DATDouEnterSleepMode(void);

// DAT_DOU's Task
extern void DATDouRefreshOutputTask(void);

// LDB's call-backs
extern void DATDouCallBackEndCtrl(tCtrl Ctrl, tStatus Statut);
extern void DATDouCallBackTxWithoutAddr(tStatus Statut);

// DAT_POU's Call-back
extern MEM_TYPE void DATPouPrepareRefresh(void);

/*-------------------------------------------------------------------------
  End of includes non re entry
  -------------------------------------------------------------------------*/
#endif  /* I_DAT_DOU_H */

