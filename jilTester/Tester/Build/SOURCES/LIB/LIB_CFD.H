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
// Component:    LIB_CFD
// -----------------------------------------------------------------------------
// $Date:   Feb 22 2010 13:55:50  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LIB/LIB_CFD/LIB_CFD.H-arc  $
// $Revision:   1.3  $
// -----------------------------------------------------------------------------  
//
//    $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LIB/LIB_CFD/LIB_CFD.H-arc  $
// 
//    Rev 1.3   Feb 22 2010 13:55:50   amanevd
// Cm007543: LIB_CFD is updated in order to separate two different requests: ReadDataByLocalIdentifier and StartRoutineByLocalIdentifier
// 
//    Rev 1.2   Sep 01 2009 18:02:30   amanevd
// Cm005142: All functions moved to banked area
// 
//    Rev 1.1   Sep 01 2009 14:05:10   amanevd
// Cm005142: Status of Confidential Diagnostic routines included
// 
//    Rev 1.0   Aug 31 2009 16:10:10   amanevd
// Initial revision.
// 
//=============================================================================

// MISRAC_2004 rule 19.15:amanevd: This is standard header file

#ifndef I_LIB_CFD_H
#define I_LIB_CFD_H (1)

//-----------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//
// #include <system_file_name.h>
// #include "project_file_name.h"
//-----------------------------------------------------------------------------

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

extern MEM_TYPE U8   LIBCfdExecuteConfDiagRequest(U8 u8RequestTypeP, U8 u8RequestP, U8* pu8SecondParamP);
extern MEM_TYPE BOOL LIBCfdIsConfDiagRoutineRequest(U8 u8RequestP);

#endif   // I_LIB_CFD_H
