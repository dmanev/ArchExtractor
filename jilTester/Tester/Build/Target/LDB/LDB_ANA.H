//******************************************************************************
// Company:      Johnson Controls Inc.
// -----------------------------------------------------------------------------
// Copyright:    This software is JCI property.
//               Duplication or disclosure without JCI written authorization
//               is prohibited.
// -----------------------------------------------------------------------------
// Project:      X90_BCM
// Language:     ANSI-C
// -----------------------------------------------------------------------------
// Component:    LDB_ANA
// -----------------------------------------------------------------------------
// $Date:   Oct 07 2009 09:00:04  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_ANA/LDB_ANA.H-arc  $
// $Revision:   1.2  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_ANA/LDB_ANA.H-arc   $
// 
//    Rev 1.2   Oct 07 2009 09:00:04   adzhelp
// Cm005497: Disabled pins are removed from conversion
// 
//    Rev 1.1   Apr 07 2009 14:18:54   adzhelp
// Cm003276: Voltage comparator control implemented. 
// 
//    Rev 1.0   20 Nov 2008 15:17:18   ailievb
// Initial revision.
//******************************************************************************

#ifndef I_LDB_ANA
#define I_LDB_ANA 1

/*-------------------------------------------------------------------------
  Included files to resolve specific definitions in this file

  #include <system_file_name.h>
  #include "project_file_name.h"
  -------------------------------------------------------------------------*/

#include "ldb_anap.h"
#include "ldb_harp.h"
#include "ldb_swi.h"

/*-------------------------------------------------------------------------
  Constant data

  #define cCMPConstantName   ((tType) ConstantValue)
  -------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
  Exported Macros

  #define mCMPMacroName   (MacroDefinition)
  -------------------------------------------------------------------------*/ 

#define mLDBAnaInit()               LDBAnaInit()
#define mLDBAnaLeaveSleepMode()     LDBAnaLeaveSleepMode()
#define mLDBAnaEnterSleepMode()     LDBAnaEnterSleepMode()

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

extern void LDBAnaInit(void);
extern MEM_TYPE void LDBAnaReceiveWithoutAddr(tMsg* pMsg);
extern MEM_TYPE void LDBAnaControl(tCtrl Ctrl);
extern void LDBAnaLeaveSleepMode(void);
extern void LDBAnaEnterSleepMode(void);

#endif   // I_LDB_ANA
