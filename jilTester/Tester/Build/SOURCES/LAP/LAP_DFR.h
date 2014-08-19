//******************************************************************************
// Company:      Johnson Controls Inc.
// -----------------------------------------------------------------------------
// Copyright:    This software is JCI property.
//               Duplication or disclosure without JCI written authorization
//               is prohibited.
// -----------------------------------------------------------------------------
// Project:      LAP_DFR
// Language:     C
// -----------------------------------------------------------------------------
// Component:    <Comments about the component (role, algorithm, structure, 
//               limitations, defined tasks and events...)>
// -----------------------------------------------------------------------------
// $Date    :   Oct 01 2009 13:59:06  $
// $Archive :   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/DFR/LAP_DFR.h-arc  $
// $Revision:   1.5  $
// -----------------------------------------------------------------------------
// $Log:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/DFR/LAP_DFR.h-arc  $
// 
//    Rev 1.5   Oct 01 2009 15:01:44   aangovt
// Cm006278: Update according to code review
// 
//    Rev 1.4  Oct 01 2009 13:59:06   aangovt
// Cm006278: Defroster behavior after reset 
// 
//    Rev 1.3   Feb 20 2009 16:49:06   aangovt
// Cm003270 Implementation of the Rear Defrost functionality 
// 
//    Rev 1.2   Feb 20 2009 10:44:52   aangovt
// Cm003270 Implementation of the Rear Defrost functionality 
// 
//    Rev 1.1   Jan 21 2009 15:47:15   aangovt
// Cm003270 Implementation of the Rear Defrost functionality 
// 
//    Rev 1.0   Jan 12 2009 16:47:04   aangovt
// Initial revision. 
//******************************************************************************

#ifndef I_LAP_DFR_H
#define I_LAP_DFR_H (1)

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

extern void LAPDfrInitialize(void);
extern void LAPDfrEnterActiveState(void);
extern void LAPDfrLeaveActiveState(void);
extern void LAPDfrIsAnybodyMaintainActiveState(void);
extern void LAPDfrLeaveStartingStepState(void);
#ifndef _QAC_
extern void LAPDfrOff(void);
extern void LAPDfrOn(void);
extern BOOL LAPDfrCommandOff(void);
extern BOOL LAPDfrCommandOn(void);
#endif

/* [EXPORTED_FUNCTIONS_END] */


#endif   /* I_LAP_DFR_H */

