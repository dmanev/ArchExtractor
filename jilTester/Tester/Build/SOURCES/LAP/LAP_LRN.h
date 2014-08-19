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
// Component:    LAP_LRN
// ----------------------------------------------------------------------------
// $Date:   Mar 09 2010 17:37:42  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LRN/LAP_LRN.h-arc  $
// $Revision:   1.3  $
// ----------------------------------------------------------------------------  
//
//  $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LRN/LAP_LRN.h-arc  $ 
// 
//    Rev 1.3   Mar 09 2010 17:37:42   amanevd
// Cm006814: Code review corrections
// 
//    Rev 1.2   Sep 30 2009 18:08:26   amanevd
// Cm006328: 'COD_ERR_AP' set to 00h in Plant mode for already learnt key
// 
//    Rev 1.1   Aug 07 2009 18:09:48   amanevd
// Cm005142: Implementation of Confidential Diagnostic
// 
//    Rev 1.0   Jan 09 2009 14:21:00   amanevd
// Initial revision.
//
//=============================================================================

#ifndef I_LAP_LRN_H
#define I_LAP_LRN_H (1)


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

//------------------------------------------------------------------------------
// Exported functions
//
// extern tReturnType LAYCmpFunctionName(tTypeArgument1 ArgumentName1, ... );
//------------------------------------------------------------------------------
extern void LRNInitialize(void);
extern void LRNEnterActiveState(void);
extern void LRNLeaveActiveState(void);
extern void LRNStartLearningInFactoryMode(void);
extern void LRNExitFromLearningInFactoryMode(void);
extern void LRNStartLearningInAfterSaleMode(void);
extern void LRNValidateLearningInAfterSaleMode(void);
extern void LRNGiveUpLearningInAfterSaleMode(void);

#endif   // I_LAP_LRN_H
