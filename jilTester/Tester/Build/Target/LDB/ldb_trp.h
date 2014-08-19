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
// Component:    LDB_TRP
// -----------------------------------------------------------------------------
// $Date:   Feb 12 2010 10:19:48  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_TRP/ldb_trp.h-arc  $
// $Revision:   1.7  $
// -----------------------------------------------------------------------------  
//
//    $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_TRP/ldb_trp.h-arc  $
// 
//    Rev 1.7   Feb 12 2010 10:19:48   amanevd
// Cm007357: QAC fix
// 
//    Rev 1.6   Sep 01 2009 15:26:44   amanevd
// Cm005466: second code review corrections SW2
// 
//    Rev 1.5   Aug 27 2009 18:12:32   amanevd
// Cm005466: QAC and code review fix
//
//    Rev 1.4   7/17/09 4:30 PM     amanevd
// Cm005466: Change of the nominal BPLM timing 
//
//    Rev 1.3   7/16/09 9:33 AM     amanevd
// Cm005205: Update of the start/stop macros for Verlog timer 
//
//    Rev 1.2   4/29/09 12:23 PM    amanevd
// Cm003272 - Intermediate part 3 - PRS compliance  
//
//    Rev 1.1   4/24/09 11:23 AM    amanevd
// Cm003272 - Finishing part 2 - pre-integration 
//
//    Rev 1.0   4/22/09 6:38 PM     amanevd
// Initial revision. 
//
//=============================================================================

#ifndef I_LDB_TRP_H
#define I_LDB_TRP_H (1)

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

//-----------------------------------------------------------------------------
// Exported Macros
//
// #define LAYCmpMacroName(...)   (MacroDefinition)
//-----------------------------------------------------------------------------
#define mLDBTrpInit()            (LDBTrpInit())
#define mLDBTrpLeaveSleepMode()  (LDBTrpControl(cLDBTrpEnterNominalMode))
#define mLDBTrpEnterSleepMode()  (LDBTrpControl(cLDBTrpEnterSleepMode))

#define mLDBTrpIsVerlogTimerEnabled() (bLDBTrpIsVerlogTimerEnabled != cFalse)
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
extern BOOL bLDBTrpIsVerlogTimerEnabled;

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
extern MEM_TYPE void LDBTrpInit(void);
//QACJ 3451: amanevd: This function is also defined in LDPParam.h
extern MEM_TYPE void LDBTrpControl(const tCtrl Ctrl);
//QACJ 3451: amanevd: This function is also defined in LDPParam.h
extern MEM_TYPE void LDBTrpSendWithAddr(tAddress, const tMsg * const );
//QACJ 3451: amanevd: This function is also defined in LDPParam.h
extern MEM_TYPE void LDBTrpReceiveWithAddr(const tAddress, const tMsg * const );

#ifdef X90_PROJECT
    extern void LDBTrpPPGIt(void);
    extern void LDBTrpTimeCaptureIt(void);
    extern void LDBTrpTimeOutIt(void);
    extern void LDBTrpVerlogTimerIt(void);
#endif

#endif  // I_LDB_TRP_H 
