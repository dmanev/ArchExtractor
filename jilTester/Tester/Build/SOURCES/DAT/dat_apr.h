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
// Component:    DAT_APR
// ----------------------------------------------------------------------------
// $Date:   Mar 09 2010 15:20:06  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_APR/dat_apr.h-arc  $
// $Revision:   1.3  $
// ----------------------------------------------------------------------------  
//
//  $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_APR/dat_apr.h-arc  $ 
// 
//    Rev 1.3   Mar 09 2010 15:20:06   amanevd
// Cm006997: Code review correction
// 
//    Rev 1.2   Apr 29 2009 13:12:30   amanevd
// Cm003272 - Intermediate part 3 
// - PRS compliance
// 
//    Rev 1.1   Feb 04 2009 13:29:30   amanevd
// Cm003272 - Intermediate part 1
// - PRS compliance
// 
//    Rev 1.0   Jan 09 2009 14:07:06   amanevd
// Initial revision.
//
//=============================================================================


#ifndef I_DAT_APR_H
#define I_DAT_APR_H (1)

//-----------------------------------------------------------------------------
//  Included files
//
//  #include <system_file_name.h>
//  #include "project_file_name.h"
//-----------------------------------------------------------------------------

#include "LDB.H"

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
#define   cDATAprComputeISK                       ((U8) 0)
#define   cDATAprComputeRSK                       ((U8) 1)
#define   cDATAprComputeSKey                      ((U8) 2)
#define   cDATAprComputeAfterSaleCode             ((U8) 3)
#define   cDATAprComputeISKFromDiagAfterSaleCode  ((U8) 4)
#define   cDATAprTestDiagAfterSaleCode            ((U8) 5)
#define   cDATAprReadAfterSaleCode                ((U8) 6)
#define   cDATAprWriteAfterSaleCode               ((U8) 7)

//-----------------------------------------------------------------------------
// Exported Macros
//
// #define LAYCmpMacroName(...)   (MacroDefinition)
//-----------------------------------------------------------------------------
#define   mDATControlApr(Control) DATAprControl(Control)

// DAT Write
#define mDATWriteU32BitDATAprIdentifierDefault(Val)     \
            (DatAprExportData.Identifier = (Val))
#define mDATWriteU32BitDATAprPasswordTagDefault(Val)    \
            (DatAprExportData.PasswordTag = (Val))
#define mDATWriteTableU8BitDATAprImmobilizerSecretKeyDefault(Index, Val)    \
            (DatAprExportData.ImmobilizerSecretKey[Index] = (Val))
#define mDATWriteTableU8BitDATAprAfterSaleCodeDefault(Index, Val)   \
            (DatAprExportData.AfterSaleCode[Index] = (Val))
#define mDATWriteTableU8BitDATAprDiagAfterSaleCodeDefault(Index, Val)   \
            (DatAprExportData.DiagAfterSaleCode[Index] = (Val))

// DAT Read
#define mDATReadTableU8BitDATAprImmobilizerSecretKeyDefault(Index)  \
            (DatAprExportData.ImmobilizerSecretKey[Index])
#define mDATReadTableU8BitDATAprRemoteSecretKeyDefault(Index)   \
            (DatAprExportData.RemoteSecretKey[Index])
#define mDATReadTableU8BitDATAprAfterSaleCodeDefault(Index)     \
            (DatAprExportData.AfterSaleCode[Index])
#define mDATReadU1BitDATAprAfterSaleCodeRecognizedDefault()     \
            (DatAprExportData.AfterSaleCodeRecognized)
#define mDATReadU16BitDATAprSKeyDefault()                       \
            (DatAprExportData.SKey)

//-----------------------------------------------------------------------------
// Exported type
//
// typedef Expression tLAYCmpTypeName;
//-----------------------------------------------------------------------------
typedef struct tDatAprExportDataType
{
    U32    Identifier;
    U32    PasswordTag;
    U8     ImmobilizerSecretKey[cDATTrpISKLengthInBytes];
    U8     RemoteSecretKey[cDATTrpISKLengthInBytes];
    U8     AfterSaleCode[cDATTrpISKLengthInBytes];
    U8     DiagAfterSaleCode[cDATTrpISKLengthInBytes];
    U16    SKey;
    U1     AfterSaleCodeRecognized;    
} tDatAprExportData;
//-----------------------------------------------------------------------------
// Exported data
//
// extern  tType   u8LAYCmpVariableName;
// extern  tType*  ps32LAYCmpVariableName; 
//-----------------------------------------------------------------------------

extern tDatAprExportData DatAprExportData;

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

extern void DATAprInit(void);
extern MEM_TYPE void DATAprControl(const tCtrl);

#endif   // I_DAT_APR_H
