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
// Component:    LDB_SLD
//               Solder test component
// -----------------------------------------------------------------------------
// $Date:   Feb 10 2010 10:15:40  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_SLD/LDB_SLD.h-arc  $
// $Revision:   1.0  $
// -----------------------------------------------------------------------------
// $Log:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_SLD/LDB_SLD.h-arc  $ 
// 
//    Rev 1.0   Feb 10 2010 10:15:40   adzhelp
// Initial revision.
//
//******************************************************************************

#ifndef I_LDB_SLD_H
#define I_LDB_SLD_H

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------

// This is an example:
// Reduce to minimum the inclusions!!!
// #include <system_file_name.h>
// #include "project_file_name.h"

//------------------------------------------------------------------------------
// Constant data
//------------------------------------------------------------------------------

// This is an example:
// #define cu16LAYCmpConstantName   ((U16)ConstantValue)

//------------------------------------------------------------------------------
// Exported type
//------------------------------------------------------------------------------

// This is an example:
// typedef Expression tLAYCmpTypeName;

//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------

// This is an example:
// Reduce to minimum the usage of extern data members!!!
// extern  tType   LAYCmpVariableName;
// extern  tType*  pLAYCmpVariableName;
// extern  U8      u8LAYCmpVariableName;
// extern  U16*    pu16LAYCmpVariableName;

//------------------------------------------------------------------------------
// Constant exported data
//------------------------------------------------------------------------------

// This is an example:
// Reduce to minimum the usage of extern constant data members!!!
// extern const tType  cLAYCmpConstantName;
// extern const U32    cu32LAYCmpConstantName;

//------------------------------------------------------------------------------
// Exported Macros
//------------------------------------------------------------------------------

// This is an example:
// #define LAYCmpMacroName(...)   (MacroDefinition)

//------------------------------------------------------------------------------
// Exported functions
//------------------------------------------------------------------------------
extern MEM_TYPE void LDBSldEnterSolderTest(void);

#endif   // I_LDB_SLD_H
