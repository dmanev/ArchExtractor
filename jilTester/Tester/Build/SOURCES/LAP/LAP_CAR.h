//*****************************************************************************
// Company:      Johnson Controls Inc.
// ----------------------------------------------------------------------------
// Copyright:    This software is JCI property.
//               Duplication or disclosure without JCI written authorization
//               is prohibited.
// ----------------------------------------------------------------------------
// Project:      X90_BCM
// Language:     ANSI-C
// ----------------------------------------------------------------------------
// Component:    LAP_CAR
// ----------------------------------------------------------------------------
// $Date:   Jun 16 2010 15:03:56  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/CAR/LAP_CAR.h-arc  $
// $Revision:   1.2  $
// ----------------------------------------------------------------------------  
//
//  $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/CAR/LAP_CAR.h-arc  $ 
// 
//    Rev 1.2   Jun 16 2010 15:03:56   amanevd
// Cm009190: Code review correction
// 
//    Rev 1.1   Apr 22 2009 19:23:48   amanevd
// Cm003272 - Finishing part 1 - pre-integration
// 
//    Rev 1.0   Jan 09 2009 14:18:20   amanevd
// Initial revision.
// 
//    Rev 1.0   Oct 09 2003 10:15:18   agrandm
// Initial revision.
//
//=============================================================================

#ifndef I_LAP_CAR_H
#define I_LAP_CAR_H (1)

//-----------------------------------------------------------------------------
//  Included files
//
//  #include <system_file_name.h>
//  #include "project_file_name.h"
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
extern void CARInitialize(void);
extern void CARIsAnybodyMaintainActiveState(void);
extern void CAREnterActiveState(void);
extern void CARLeaveActiveState(void);
extern void CARStartAuthentPermKey(void);
extern void CARExitFromAuthentPermKey(void);
extern void CARStartTestVirginKey(void);

#endif   // I_LAP_CAR_H
