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
// Component:    LAP_FLI
// -----------------------------------------------------------------------------
// $Log:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_FLI/LAP_FLI.h-arc  $
// 
//    Rev 1.2   Mar 17 2010 13:55:08   amanevd
// Cm006814: Code review corrections
// 
//    Rev 1.1   Apr 15 2009 12:31:52   amarinm1
// Cm003263 & Cm004774: Implementation of the overload protection and corresponding TFC test. Other minor changes.
// 
//    Rev 1.0   Feb 05 2009 12:07:48   amarinm1
// Initial revision.
//
//******************************************************************************

#ifndef I_lap_fla_H
#define I_lap_fla_H (1)

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//
// #include <system_file_name.h>
// #include "project_file_name.h"
//------------------------------------------------------------------------------
//#include "deftypes.h"

//------------------------------------------------------------------------------
// Data prefix for constant & data
//
// unsigned int {u8,u16,u32} / signed int {s8,s16,s32} 
// register size unsigned int {r} / float {f32,f64}  / s for struct 
// no prefix for other types.
//
//------------------------------------------------------------------------------
// Constant data
//
// #define cu16LAYCmpConstantName   ((U16) ConstantValueUL)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported type
//
// typedef Expression tLAYCmpTypeName;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported data
//
// extern  tType   u8LAYCmpVariableName;
// extern  tType*  ps32LAYCmpVariableName; 
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Constant exported data
//
// extern const tType  s8LAYCmpVariableName;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported Macros
//
// #define LAYCmpMacroName(...)   (MacroDefinition)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported functions
//
// extern tReturnType LAYCmpFunctionName(tTypeArgument1 ArgumentName1, ... );
//------------------------------------------------------------------------------
void LAPFliInitialize( void );
void LAPFliEnterActiveState( void );
void LAPFliLeaveActiveState( void );
void LAPFliIsAnybodyMaintainActiveState( void );
void LAPFliLeftFlashingForTFC( void );
void LAPFliRightFlashingForTFC( void );


/* [EXPORTED_FUNCTIONS_END] */

#endif   /* I_lap_fla_H */