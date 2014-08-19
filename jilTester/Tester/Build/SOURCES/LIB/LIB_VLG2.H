#ifndef _QAC_
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
// Component:    <Comments about the component (role, algorithm, structure, 
//               limitations, defined tasks and events...)>
// -----------------------------------------------------------------------------
// $Date:   Sep 19 2009 16:50:40  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LIB/LIB_VLG2/LIB_VLG2.H-arc  $
// $Revision:   1.4  $
// -----------------------------------------------------------------------------  
//
//    $Log:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LIB/LIB_VLG2/LIB_VLG2.H-arc  $
// 
//    Rev 1.4   Sep 19 2009 16:50:40   amanevd
// Cm005797 & Cm005798: fix of both TCRs
// 
//    Rev 1.3   Sep 01 2009 18:00:52   amanevd
// Cm005142: All Functions(except interrupt context ones) moved to banked area
// 
//    Rev 1.2   Jul 16 2009 13:58:22   amanevd
// Cm005277: NRZ encoding applied
// 
//    Rev 1.1   Mar 23 2009 18:17:04   amanevd
// Cm003272 - Correction after DCD_LIB_VLG2 Review
//
//=============================================================================
#endif

// MISRAC_2004 rule 19.15:amanevd: This is standard header file

#ifndef I_LIB_VLG2_H
#define I_LIB_VLG2_H (1)

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

typedef void     (*tpLIBVlg2ControlDigitalOutput)      (BOOL State);

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
extern MEM_TYPE void LIBVlg2Init(U16 SecretKey, tpLIBVlg2ControlDigitalOutput OutputControl);
extern MEM_TYPE void LIBVlg2ProcessData(void);
extern MEM_TYPE void LIBVlg2AuthenticationSuccess(BOOL state);
extern void LIBVlg2TimerTick(void);
extern MEM_TYPE BOOL LIBVlg2FrameEmissionStopped(void);
extern MEM_TYPE void LIBVlg2UpdateSecretKey(U16 SKey);
extern MEM_TYPE void LIBVlg2UpdateIgnition(BOOL State);
extern MEM_TYPE void LIBVlg2PermanentAuthenticationEnabled(BOOL state);

#endif   // I_LIB_VLG2_H
