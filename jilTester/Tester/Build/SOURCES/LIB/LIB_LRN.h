//*****************************************************************************
// Company:      Johnson Controls Inc.
// ----------------------------------------------------------------------------
// Copyright:    This software is JCI property.
//               Duplication or disclosure without JCI written authorization
//               is prohibited.
// ----------------------------------------------------------------------------
// Project:      X90_BCM
// Language:     ANSI-C
// ----------------------------------------------------------------------------
// Component:    <Comments about the component (role, algorithm, structure, 
//               limitations, defined tasks and events...)>
// ----------------------------------------------------------------------------
// $Date:   Sep 16 2009 17:36:26  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LIB/LIB_LRN/LIB_LRN.h-arc  $
// $Revision:   1.2  $
// ----------------------------------------------------------------------------  
//
//  $Log:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LIB/LIB_LRN/LIB_LRN.h-arc  $ 
// 
//    Rev 1.2   Sep 16 2009 17:36:26   amanevd
// Cm003277 - LIB_PCF and LIB_LRN functions moved to BANKED memory
// 
//    Rev 1.1   Apr 29 2009 13:16:02   amanevd
// Cm003272 - Intermediate part 3 
// - PRS compliance
// 
//=============================================================================

#ifndef I_LIB_LRN_H
#define I_LIB_LRN_H (1)

//-----------------------------------------------------------------------------
//  Included files
//
//  #include <system_file_name.h>
//  #include "project_file_name.h"
//-----------------------------------------------------------------------------
#include "deftypes.h"

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
// Version ( This constant must be increased each time this file is modified )
// MSB: Spec version ( S01 ),   LSB: API version ( 00 )
#define cLIBLrnVersion                            (0x0100)

// Secret key lenght
#define cLIBLrnSkLength                           ((U8)6)


//-----------------------------------------------------------------------------
// Exported Macros
//
// #define LAYCmpMacroName(...)   (MacroDefinition)
//-----------------------------------------------------------------------------
#define mLIBLrnGetRequiredVersion()               ( LIBLrnVersion )

//-----------------------------------------------------------------------------
// Exported type
//
// typedef Expression tLAYCmpTypeName;
//-----------------------------------------------------------------------------
typedef U16 tLIBLrnVersion;

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
extern const tLIBLrnVersion   LIBLrnVersion;

//-----------------------------------------------------------------------------
// Exported functions
//
// extern tReturnType LAYCmpFunctionName(tTypeArgument1 ArgumentName1, ... );
//-----------------------------------------------------------------------------

extern MEM_TYPE void LIBLrnFnF(U32 Ide,U32 Pwd,U8* pIsk);
extern MEM_TYPE void LIBLrnFnG(U8* pIsk, U8* pApv);
extern MEM_TYPE void LIBLrnFnGInv(U8* pApv, U8* pIsk);
extern MEM_TYPE void LIBLrnFnH(U8* pIsk,U8* pVsk);
extern MEM_TYPE void LIBLrnFnM(U32 Ide,U8* pRsk);
extern MEM_TYPE void LIBLrnFnE(U32 Ide1, U32 Pwd1, U32 Pwd2, U32 Pwd3, U32 Pwd4, U8* pIsk, U8* pDe);

#endif   // I_LIB_LRN_H
