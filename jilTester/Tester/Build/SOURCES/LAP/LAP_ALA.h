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
// Component:    LAP_ALA
// -----------------------------------------------------------------------------
// $Date    :   Apr 14 2009 10:56:07  $
// $Archive :   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_ALA/LAP_ALA.h-arc  $
// $Revision:   1.9  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_ALA/LAP_ALA.h-arc  $
// 
//    Rev 1.9   Feb 23 2010 14:24:10   adzhelp
// Cm007607: Active sleep state maintained after reset
// 
//    Rev 1.8   Sep 15 2009 17:11:02   aangovt
// Cm005739, Cm005776, Cm005777: New graph is added for case of reset. Reading of EEP_CAR_SECURE flag in EnterActiveState is removed.
// 
//    Rev 1.7   09 Sep 2009 11:41:22   aangovt
// Cm005820: After change of doors state door state command is sent, only  if car is secured.
// 
//    Rev 1.6   Aug 25 2009 18:07:18   aangovt
// Cm005188: Code optimization - three controls, consumed by one function
// 
//    Rev 1.5   25 Aug 2009 12:28:34   aangovt
// Cm005188: Checks for doors falling edges is added.
// 
//    Rev 1.4   13 Jul 2009 09:44:32   aangovt
// Cm005188: Sleeping authorisation is added; update acording to Cm005189, Cm005431 and code review.
// 
//    Rev 1.3   Apr 14 2009 10:56:07   aangovt
// Cm003271 - macro update  
// 
//    Rev 1.2   Apr 14 2009 09:41:51   aangovt
// Cm003271 - checks for diagnostic session is added.  
// 
//    Rev 1.1   Feb 20 2009 14:58:13   aangovt
// Cm003271  Implementation of the Alarm functionality 
// 
//    Rev 1.0   Feb 09 2009 14:30:19   aangovt
// Initial revision. 
//******************************************************************************
#endif

#ifndef I_lap_ala_H
#define I_lap_ala_H (1)

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
//#define mLDBAlaSendWithoutAddr(Msg)         LDBAlaSendWithoutAddr(Msg)
//------------------------------------------------------------------------------
// Exported functions
//
// extern tReturnType LAYCmpFunctionName(tTypeArgument1 ArgumentName1, ... );
//------------------------------------------------------------------------------

extern void LAPAlaInitialize(void);
extern void LAPAlaEnterActiveState(void);
extern void LAPAlaLeaveActiveState(void);
extern void LAPAlaIsAnybodyMaintainActiveState(void);
extern void LAPAlaIsAnybodyMaintainActiveSleepState(void);
extern void LAPAlaUnlockFromTheOutside(void);
extern void LAPAlaKeyIsAuthenticated(void);
extern void LAPAlaLockFromTheOutside(void);
extern void LAPAlaDiagEnable(void);
extern void LAPAlaDiagDisable(void);
extern void LAPAlaFallingEdgeForDS(void);
extern void LAPAlaFallingEdgeForPWR_IGN(void);
extern void LAPAlaLeaveStartingStepState(void);
// [EXPORTED_FUNCTIONS_END] 


#endif   // I_lap_ala_H 

