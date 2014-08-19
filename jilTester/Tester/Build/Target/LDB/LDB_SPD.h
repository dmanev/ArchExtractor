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
// Component:    LDB_SPD
// -----------------------------------------------------------------------------
// $Date:   Sep 25 2009 09:13:34  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_SPD/LDB_SPD.h-arc  $
// $Revision:   1.1  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_SPD/LDB_SPD.h-arc  $
// 
//    Rev 1.1   Sep 25 2009 09:13:34   adzhelp
// Cm005225, Cm004744, Cm003262: Move functions to banked area.
// 
//    Rev 1.0   Apr 09 2009 10:21:56   adzhelp
// Initial revision.
// 
//******************************************************************************
#endif

#ifndef I_LDB_SPD_H
#define I_LDB_SPD_H

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------
#include "ldb.h"

//------------------------------------------------------------------------------
// Constant data
//------------------------------------------------------------------------------

// This is an example:
// #define cu16LAYCmpConstantName   ((U16)ConstantValue)

//------------------------------------------------------------------------------
// Exported type
//------------------------------------------------------------------------------

// This is an example:
// typedef Expression tLAYCmpTypeName;

//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------

// This is an example:
// Reduce to minimum the usage of extern data members!!!
// extern  tType   LAYCmpVariableName;
// extern  tType*  pLAYCmpVariableName;
// extern  U8      u8LAYCmpVariableName;
// extern  U16*    pu16LAYCmpVariableName;

//------------------------------------------------------------------------------
// Constant exported data
//------------------------------------------------------------------------------

// This is an example:
// Reduce to minimum the usage of extern constant data members!!!
// extern const tType  cLAYCmpConstantName;
// extern const U32    cu32LAYCmpConstantName;

//------------------------------------------------------------------------------
// Exported Macros
//------------------------------------------------------------------------------
#define mLDBSpdInit()                       LDBSpdInit()
#define mLDBSpdLeaveSleepMode()
#define mLDBSpdEnterSleepMode()

//------------------------------------------------------------------------------
// Exported functions
//------------------------------------------------------------------------------
extern void LDBSpdInit(void);
extern MEM_TYPE void LDBSpdReceiveWithAddr(const tAddress Address, tMsg * const pMsg);
extern MEM_TYPE void LDBSpdControl(const tCtrl Ctrl);

#endif   // I_LDB_SPD_H
