#ifndef _QAC_
//******************************************************************************
// Company:      Johnson Controls Inc.
// -----------------------------------------------------------------------------
// Copyright:    This software is JCI property.
//               Duplication or disclosure without JCI written authorization
//               is prohibited.
// -----------------------------------------------------------------------------
// Project:      X90_BCM
// Language:     C
// -----------------------------------------------------------------------------
// Component:    <Comments about the component (role, algorithm, structure, 
//               limitations, defined tasks and events...)>
// -----------------------------------------------------------------------------
// $Date:   Oct 01 2009 15:18:22  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/ILL/LAP_ILL.h-arc  $
// $Revision:   1.4  $
// -----------------------------------------------------------------------------
// $Log:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/ILL/LAP_ILL.h-arc  $
// 
//    Rev 1.4   Oct 01 2009 15:18:22   amarinm1
// Cm006282: Integration modifications.
// 
//    Rev 1.3   Oct 01 2009 11:39:04   amarinm1
// Cm006282: Starting the power relay is now done in LeaveStartingStepState too.
// 
//    Rev 1.2   Jan 06 2009 14:23:18   amarinm1
// Cm003209: Interior Lights component development.
// PVCS header comments were changed.
// 
//    Rev 1.1   Jan 06 2009 12:20:22   amarinm1
// Cm003209: Interior Lights component development.
// File updated to copmly with new QAC restrictions.
// 
//    Rev 1.0   Nov 24 2008 14:24:02   amarinm1
// Initial revision.
//
//    Rev 1.0   27 Oct 2008 09:22:26   avidoly
// Initial revision.
//
//    Rev 1.2   10 Mar 2005 16:30:22   abarbae
// PON URD42 DEV 2514 / PON URD42 BODY_SW 851 : Update component template for compatibility with VSS 
//
//******************************************************************************
#endif // _QAC_


#ifndef I_LAP_ILL_H
#define I_LAP_ILL_H (1)

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//
// #include <system_file_name.h>
// #include "project_file_name.h"
//------------------------------------------------------------------------------

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

extern void LAPIllInitialize(void);
extern void LAPIllLeaveStartingStepState(void);
extern void LAPIllEnterActiveState(void);
extern void LAPIllLeaveActiveState(void);
extern void LAPIllIsAnybodyMaintainActiveState(void);
extern void LAPIllManagement(void);
extern BOOL LAPIllLightsOnRequestIsTrue(void);
extern void LAPIllLightsOnExecution(void);
extern BOOL LAPIllLightsOffRequestIsTrue(void);
extern void LAPIllLightsOffExecution(void);
extern BOOL LAPIllLightsGraduallyOffRequestIsTrue(void);
extern void LAPIllLightsGraduallyOffExecution(void);
extern BOOL LAPIllGradualOffIsInProgress(void);
extern BOOL LAPIllLightsAreOff(void);
extern void LAPIllRKELock(void);
extern void LAPIllRKEUnlock(void);

/* [EXPORTED_FUNCTIONS_END] */


#endif   /* I_LAP_ILL_H */

