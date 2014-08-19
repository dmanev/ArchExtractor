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
// Component:    LDB_TRP
// -----------------------------------------------------------------------------
// $Date:   Sep 01 2009 15:26:44  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_TRP/ldb_trpp.h-arc  $
// $Revision:   1.3  $
// -----------------------------------------------------------------------------  
//
//  $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_TRP/ldb_trpp.h-arc  $
// 
//    Rev 1.3   Sep 01 2009 15:26:44   amanevd
// Cm005466: second code review corrections SW2
// 
//    Rev 1.2   Aug 27 2009 18:12:32   amanevd
// Cm005466: QAC and code review fix
// 
//    Rev 1.1   Jul 24 2009 14:04:20   amanevd
// Cm005466: Change of the nominal BPLM timing
// 
//    Rev 1.0   Apr 22 2009 19:28:50   amanevd
// Initial revision.
//
//=============================================================================

#ifndef I_LDB_TRPP_H
#define I_LDB_TRPP_H (1)

//-----------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//
// #include <system_file_name.h>
// #include "project_file_name.h"
//-----------------------------------------------------------------------------
#include "ldb_har.h"

//-----------------------------------------------------------------------------
// Data prefix for constant & data
//
// unsigned int {u8,u16,u32} / signed int {s8,s16,s32} 
// register size unsigned int {r} / float {f32,f64}  / s for struct 
// no prefix for other types.
//
//-----------------------------------------------------------------------------
// Constant data
//
// #define cu16LAYCmpConstantName   ((U16) ConstantValueUL)
//-----------------------------------------------------------------------------

// 32To = 256 +/- 14%
#define cLDBTrpOneBitTimeMin            ((U16) 192U)
#define cLDBTrpOneBitTimeMax            ((U16) 320U)

#define cLDBTrpOneAndAHalfBitTimeMin   ((U16) 330U)
#define cLDBTrpOneAndAHalfBitTimeMax   ((U16) 438U)

#define cLDBTrpTwoBitsTimeMin           ((U16) 440U)
#define cLDBTrpTwoBitsTimeMax           ((U16) 584U)

#define cLDBTrpItDelayBeforeSwitchInstr       ((U16) 4U)
#define cLDBTrpItDelayMaxBeforeWindowOpening  ((U16) 21U)

#define cLDBTrpHwDelayBeforeLowLevelDetection ((U16) 5U)

//-----------------------------------------------------------------------------
// Exported Macros
//
// #define LAYCmpMacroName(...)   (MacroDefinition)
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Exported type
//
// typedef Expression tLAYCmpTypeName;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Exported data
//
// extern  tType   u8LAYCmpVariableName;
// extern  tType*  ps32LAYCmpVariableName; 
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Constant exported data
//
// extern const tType  s8LAYCmpVariableName;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Exported functions
//
// extern tReturnType LAYCmpFunctionName(tTypeArgument1 ArgumentName1, ... );
//-----------------------------------------------------------------------------

#endif   // I_LDB_TRPP_H
