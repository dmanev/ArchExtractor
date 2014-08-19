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
// Component:    LDB_KWP
// -----------------------------------------------------------------------------
// $Date:   Jul 13 2009 10:32:26  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_KWP/LDB_KWP.H-arc  $
// $Revision:   1.3  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_KWP/LDB_KWP.H-arc   $
// 
//    Rev 1.3   Jul 13 2009 10:32:26   adzhelp
// Cm005100: Functions moved to banked area
// 
//    Rev 1.2   Jul 09 2009 16:37:16   akodzhh
// Cm005100: before all instances of mLDBIntEnableIsr(<interrupt>), there should be instance of mLDBIntClearIsrRequestFlag(<interrupt>).
// mLDBRegNop()usage adjusted. QAC warnings justified.
// 
//    Rev 1.1   Mar 17 2009 14:17:38   adzhelp
// Cm003128: Adaptation of LDB_KWP for NEC K0
//
//    Rev 1.0   10 Mar 2009 09:03:18   akodzhh
// Initial revision.
//******************************************************************************
#endif

#ifndef I_LDB_KWP_H
#define I_LDB_KWP_H

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------
#include "ldb.h"

//------------------------------------------------------------------------------
// Constant data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported type
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Constant exported data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported Macros
//------------------------------------------------------------------------------
#define mLDBKwpInit                         LDBKwpInit
#define mLDBKwpSendWithoutAddr              LDBKwpSendWithoutAddr
#define mLDBKwpControl                      LDBKwpControl

//------------------------------------------------------------------------------
// Exported functions
//------------------------------------------------------------------------------
extern MEM_TYPE void LDBKwpInit(void);
extern MEM_TYPE void LDBKwpSendWithoutAddr(tMsg *);
extern MEM_TYPE void LDBKwpControl(tCtrl);
extern void LDBKwpEnterSleepMode(void);
extern void LDBKwpLeaveSleepMode(void);
extern void LDBKwpCallBackTimer(void);


#endif   // I_LDB_KWP_H
