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
// Component:    LDB_PWM
// -----------------------------------------------------------------------------
// $Date:   Jun 30 2009 12:39:08  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_PWM/LDB_PWM.h-arc  $
// $Revision:   1.1  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_PWM/LDB_PWM.h-arc  $
// 
//    Rev 1.1   Jun 30 2009 12:39:08   adzhelp
// Cm005205: Updates after integration test and unit test
// 
//    Rev 1.0   Jun 23 2009 15:26:22   amarinm1
// Initial revision.
//
//******************************************************************************
#endif

#ifndef I_LDB_PWM_H
#define I_LDB_PWM_H

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------

// This is an example:
// Reduce to minimum the inclusions!!!
// #include <system_file_name.h>
// #include "project_file_name.h"

//#include "deftypes.h"
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
extern BOOL bPwmIsFadingControlRequested;

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
#define mLDBPwmInit()           LDBPwmInit()
#define mLDBPwmLeaveSleepMode() LDBPwmLeaveSleepMode()
#define mLDBPwmEnterSleepMode() LDBPwmEnterSleepMode()

#define mLDBPwmIsFadingControlRequested() (bPwmIsFadingControlRequested != cFalse)

//------------------------------------------------------------------------------
// Exported functions
//------------------------------------------------------------------------------
MEM_TYPE void LDBPwmInit( void );
MEM_TYPE void LDBPwmLeaveSleepMode( void );
MEM_TYPE void LDBPwmEnterSleepMode( void );
MEM_TYPE void LDBPwmSendWithAddr( const tAddress AddrP, const tMsg * const pMsgP );

#ifdef X90_PROJECT
void LDBPwmControlFadingIt(void);
#endif

#endif   // I_LDB_BUZ_H
