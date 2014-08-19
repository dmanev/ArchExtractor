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
// Component:    LDB_DOU
// -----------------------------------------------------------------------------
// $Date:   Feb 04 2010 12:28:30  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_DOU/LDB_DOU.H-arc  $
// $Revision:   1.4  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_DOU/LDB_DOU.H-arc   $
// 
//    Rev 1.4   Feb 04 2010 12:28:30   adzhelp
// Cm007297: Implementation EEPROM reprogramming mode loop
// 
//    Rev 1.3   Oct 06 2009 11:40:46   adzhelp
// Cm005497: Implementation of unused pins treatment
// 
//    Rev 1.2   Apr 27 2009 15:53:50   adzhelp
// Cm003619: LDBDouControl() placed in banked memory
// 
//    Rev 1.1   Mar 12 2009 08:57:48   adzhelp
// Cm003619: Parameterization of digital outputs
// 
//    Rev 1.0   10 Nov 2008 15:28:18   ailievb
// Initial revision.
//******************************************************************************

//----  Mono-inclusion Definition-----
#ifdef I_LDB_DOU
#else
#define I_LDB_DOU 1

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
// Exported Macros
//------------------------------------------------------------------------------
#define mLDBDouInit()            (LDBDouInit())
#define mLDBDouLeaveSleepMode()  (LDBDouControl(cLDBDouEnterNominalMode))
#define mLDBDouEnterSleepMode()  (LDBDouControl(cLDBDouEnterSleepMode))

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
// Exported functions
//------------------------------------------------------------------------------
extern MEM_TYPE void LDBDouInit(void);
//QACJ 3451: adzhelp: This function is also defined in LDPParam.h
extern void LDBDouSendWithoutAddr(const tMsg* const pMsg);
//QACJ 3451: adzhelp: This function is also defined in LDPParam.h
extern MEM_TYPE void LDBDouControl(const tCtrl Ctrl);

#endif // I_LDB_DOU
