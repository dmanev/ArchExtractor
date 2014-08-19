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
// Component:    DAT_VLG
// -----------------------------------------------------------------------------
// $Date:   Dec 21 2009 13:45:18  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_VLG/DAT_VLG.H-arc  $
// $Revision:   1.9  $
// -----------------------------------------------------------------------------  
//
//    $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_VLG/DAT_VLG.H-arc  $
// 
//    Rev 1.9   Dec 21 2009 13:45:18   amanevd
// Cm005797: On input change LIBVlg2ProcessData() is called
// 
//    Rev 1.8   Nov 04 2009 17:50:26   amanevd
// Cm005566: Simplified Protection
// 
//    Rev 1.7   Oct 05 2009 16:32:16   amanevd
// Cm005791: Verlog Serial Line test included
// 
//    Rev 1.6   Sep 21 2009 12:01:56   amanevd
// Cm005044: Now Verlog frame is sent while in Permanent Authentication
// 
//    Rev 1.5   Aug 28 2009 10:14:50   amanevd
// Cm004914: Code review corrections
// 
//    Rev 1.4   Jul 16 2009 13:56:14   amanevd
// Cm005277: NRZ encoding applied
// 
//    Rev 1.3   May 13 2009 14:45:22   amanevd
// Cm003272 - QAC fix - NO IMPACT ON REAL CODE
// 
//    Rev 1.2   Apr 29 2009 13:12:30   amanevd
// Cm003272 - Intermediate part 3 
// - PRS compliance
// 
//    Rev 1.1   Apr 24 2009 17:17:12   amanevd
// Cm003272 - Finishing part 2 - pre-integration
// 
//    Rev 1.0   Mar 17 2009 15:53:50   amanevd
// Initial revision.
//
//=============================================================================

#ifndef I_DAT_VLG_H
#define I_DAT_VLG_H (1)

//-----------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//
// #include <system_file_name.h>
// #include "project_file_name.h"
//-----------------------------------------------------------------------------
#include "ldb.h"

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
// DAT_VLG Controls
#define cDATVlgStart                    ((tCtrl) 0x00U)
#define cDATVlgStop                     ((tCtrl) 0x01U)
#define cDATVlgSerialTest               ((tCtrl) 0x02U)

//-----------------------------------------------------------------------------
// Exported Macros
//
// #define LAYCmpMacroName(...)   (MacroDefinition)
//-----------------------------------------------------------------------------

// DAT Controls
#define mDATControlVlg(Control) DATVlgControl(Control)

#define mDATReadU1BitDATVlgSerialTestInProgressDefault() (bDATVlgSerialTestInProgress)

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
extern BOOL bDATVlgSerialTestInProgress;

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
extern void DATVlgInit(void);
extern void DATVlgKeyIsAuthenticated(void);
extern void DATVlgKeyIsNotAuthenticated(void);
extern void DATVlgStartAuthentPermKey(void);
extern void DATVlgExitFromAuthentPermKey(void);
extern void DATVlgControlDigitalOutput(const BOOL bStateP);
extern void DATVlgIsAnybodyMaintainActiveState(void);
extern void DATVlgFalling_PWR_IGN(void);
extern MEM_TYPE void DATVlgControl(const tCtrl Ctrl);

#endif   // I_DAT_VLG_H
