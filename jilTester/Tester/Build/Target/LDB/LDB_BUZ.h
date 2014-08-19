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
// Component:    <Name of the component and its variant number, if any>
//               <Comments about the component (role, algorithm, structure,
//               limitations, defined tasks and events...)>
// -----------------------------------------------------------------------------
// $Date:   Sep 25 2009 09:13:34  $
// $Archive::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_BUZ/LDB_BUZ.h-arc  $
// $Revision:   1.2  $
// -----------------------------------------------------------------------------
// $Log:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_BUZ/LDB_BUZ.h-arc  $
// 
//    Rev 1.2   Sep 25 2009 09:13:34   adzhelp
// Cm005225, Cm004744, Cm003262: Move functions to banked area.
// 
//    Rev 1.1   Mar 19 2009 12:16:22   amarinm1
// Macro for the init function was added.
//******************************************************************************
#endif

#ifndef I_LDB_BUZ_H
#define I_LDB_BUZ_H

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
#define mLDBBuzInit()   LDBBuzInit()

//------------------------------------------------------------------------------
// Exported functions
//------------------------------------------------------------------------------

MEM_TYPE void LDBBuzInit( void );
MEM_TYPE void LDBBuzControl( const tCtrl Ctrl );
MEM_TYPE void LDBBuzSendWithoutAddr( const tMsg * const Msg );

#endif   // I_LDB_BUZ_H
