#ifndef _QAC_
//******************************************************************************
// Company:      Johnson Controls Inc.
// -----------------------------------------------------------------------------
// Copyright:    This software is JCI property.
//               Duplication or disclosure without JCI written authorization
//               is prohibited.
// -----------------------------------------------------------------------------
// Project:      RSA_X90_BCM
// Language:     C
// -----------------------------------------------------------------------------
// Component:    DAT_RBG
// -----------------------------------------------------------------------------
// $Date    :   $
// $Archive :   $
// $Revision:   1.5  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_RBG/DAT_RBG.h-arc  $
// 
//    Rev 1.5   Jan 21 2010 15:04:52   adzhelp
// Cm007074: Functions moved to banked area
// 
//    Rev 1.4   Oct 02 2009 10:57:13   aangovt
// Cm005603: Corrections according to code review 1.5  
//
//    Rev 1.3   Apr 22 2009 10:17:26   adzhelp 
// Cm003264: Macro for reading flag for malfunction removed  
// 
//    Rev 1.2   Apr 21 2009 16:35:50   ailievb 
// Cm003264 Implementation of the Doorlock functionality (Without SDO part)
// Added DATRbgStart and DATRbgStop functiona to stop adn start RBG from DLK component.  
// 
//    Rev 1.1   Apr 15 2009 09:55:13   aangovt
// Cm003264 - New template is added  
// 
//    Rev 1.0   Mar 23 2009 17:42:29   aangovt
// Initial revision. 
//******************************************************************************
#endif

#ifndef I_dat_rbg_H
#define I_dat_rbg_H (1)

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
#define mDATControlRbag(Treatment) \
    DATRbg##Treatment()

//------------------------------------------------------------------------------
// Exported functions
//
// extern tReturnType LAYCmpFunctionName(tTypeArgument1 ArgumentName1, ... );
//------------------------------------------------------------------------------
extern void DATRbgInit(void);
extern void DATRbgAirbagCrashDetection(void);
extern MEM_TYPE void DATRbgStart(void);
extern MEM_TYPE void DATRbgStop(void);

#endif   // I_dat_rbg_H 
 
