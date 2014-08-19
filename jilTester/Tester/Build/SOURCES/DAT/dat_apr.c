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
// $Date:   Mar 09 2010 15:16:22  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_APR/dat_apr.c-arc  $
// $Revision:   1.6  $
// ----------------------------------------------------------------------------  
//
//  $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_APR/dat_apr.c-arc  $
// 
//    Rev 1.6   Mar 09 2010 15:16:22   amanevd
// Cm006997: Code review correction
// 
//    Rev 1.5   Dec 03 2009 09:40:14   amanevd
// Cm006741: SKey byte order swapped
// 
//    Rev 1.4   Nov 10 2009 14:58:44   amanevd
// Cm006200: LIBLrnFnF order of arguments changed
// 
//    Rev 1.3   May 21 2009 11:09:40   amanevd
// Cm003272 - CCover justifications - NO CODE IMPACT
// 
//    Rev 1.2   Apr 29 2009 13:12:28   amanevd
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


//-----------------------------------------------------------------------------
//  Body Identification
//-----------------------------------------------------------------------------
#define dat_apr  "dat_apr"

//-----------------------------------------------------------------------------
//  Included files
//
//  #include <system_file_name.h>
//  #include "project_file_name.h"
//-----------------------------------------------------------------------------
#include "tos.h"
#include "lib_lrn.h"
#include "dat.h"
#include "dat_apr.h"
//-----------------------------------------------------------------------------
//  Local constants
//
//  #define cConstantName   ((tType) ConstantValue)
//-----------------------------------------------------------------------------
// for coding the After Sale value in eeprom memory
#define cAfterSaleValueCoding     ((U8) 0x4EU)  // N of Nissan


#define cShift8                   ((U8) 8)

//-----------------------------------------------------------------------------
//  Local macros
//
//  #define mMacroName   (MacroDefinition)
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//  Local types
//
//  struct  sStructureName { ... };
//  union   uUnionName { ... };
//  enum    eEnumerationName { ... };
//  typedef Expression tTypeName;
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//  Local data
//
//  static  tType   VariableName;
//  static  tType*  pVariableName; 
//-----------------------------------------------------------------------------
static    U8     VerlogCode[cDATTrpISKLengthInBytes];

//-----------------------------------------------------------------------------
//  Constant local data
//
//  static const tType  VariableName;
//-----------------------------------------------------------------------------

 
//-----------------------------------------------------------------------------
//  Exported data
//
//  tType   LAYCmpVariableName;   (LAY: 3 characters to identify the layer)
//  tType*  pLAYCmpVariableName;  (Cmp: 3 characters to identify this component)
//-----------------------------------------------------------------------------
tDatAprExportData DatAprExportData;
//-----------------------------------------------------------------------------
//  Constant exported data
//
//              (LAY: 3 characters to identify the layer)
//              (Cmp: 3 characters to identify this component)
// 
//  const tType   LAYCmpVariableName;
//-----------------------------------------------------------------------------
 
//-----------------------------------------------------------------------------
//  Local function prototypes
//  
//  static tTypeRetour FunctionName(tTypeArgument1 ArgumentName1, ... );
//-----------------------------------------------------------------------------
static MEM_TYPE void ReadAfterSaleCode(void);
static MEM_TYPE void TestDiagAfterSaleCode(void);
static MEM_TYPE void WriteAfterSaleCode(void);

//=============================================================================
//=========================== LOCAL FUNCTIONS =================================
//=============================================================================

//=============================================================================
//  DESCRIPTION : Read the After Sale code from the BCM EEPROM
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//=============================================================================

static MEM_TYPE void ReadAfterSaleCode(void)
{
  U8 u8IndexL;

  for (u8IndexL = 0; u8IndexL < cDATTrpISKLengthInBytes; u8IndexL++)
  {
    DatAprExportData.AfterSaleCode[u8IndexL] = 
        (mDATReadTable(U8Bit, EEP_AfterSalesCode, u8IndexL, Default) 
            ^ cAfterSaleValueCoding);
  }
}
//=============================================================================
//  DESCRIPTION : Test the After Sale code from diagnostic
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//=============================================================================

static MEM_TYPE void TestDiagAfterSaleCode(void)
{
  U8   u8IndexL;
  BOOL bCodesAreDifferentL = cFalse;

  for (u8IndexL = 0; u8IndexL < cDATTrpISKLengthInBytes; u8IndexL++)
  {
    DatAprExportData.ImmobilizerSecretKey[u8IndexL] = 
        mDATReadTable(U8Bit, EEP_ImmoSecretKey, u8IndexL, Default);
  }

  LIBLrnFnG(DatAprExportData.ImmobilizerSecretKey,DatAprExportData.AfterSaleCode);

  for ( u8IndexL = 0; 
            (u8IndexL < cDATTrpISKLengthInBytes) 
        &&  (bCodesAreDifferentL == cFalse); 
        u8IndexL++)
  {
    bCodesAreDifferentL = (DatAprExportData.AfterSaleCode[u8IndexL] 
        != DatAprExportData.DiagAfterSaleCode[u8IndexL]);
  }

  DatAprExportData.AfterSaleCodeRecognized = (bCodesAreDifferentL == cFalse);
}
//=============================================================================
//  DESCRIPTION : Encode and write the After Sale code in the BCM EEPROM
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//=============================================================================

static MEM_TYPE void WriteAfterSaleCode(void)
{
  U8 u8IndexL;

  for (u8IndexL = 0; u8IndexL < cDATTrpISKLengthInBytes; u8IndexL++)
  {
    DatAprExportData.AfterSaleCode[u8IndexL] ^= cAfterSaleValueCoding;
    mDATWriteTable( U8Bit, 
                    EEP_AfterSalesCode, 
                    u8IndexL, 
                    DatAprExportData.AfterSaleCode[u8IndexL], 
                    Default);
  }
}

//=============================================================================
//============================ EXPORTED FUNCTIONS =============================
//=============================================================================

//*****************************************************************************
//  DESCRIPTION         : Control DAT_APR
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************

MEM_TYPE void DATAprControl(const tCtrl CtrlP)
{
  switch (CtrlP)
  {
  case cDATAprComputeISK:
    ///////////////////////////////
    // Function F(PWDTAG, IDE)
    ///////////////////////////////
    LIBLrnFnF(  DatAprExportData.Identifier,
                DatAprExportData.PasswordTag,
                DatAprExportData.ImmobilizerSecretKey);
    break;

  case cDATAprComputeRSK:
    ///////////////////////////////
    // Function M(IDE)
    ///////////////////////////////
    LIBLrnFnM(  DatAprExportData.Identifier,
                DatAprExportData.RemoteSecretKey);
    break;

  case cDATAprComputeSKey:
    ///////////////////////////////
    // Function H(ISK)
    ///////////////////////////////
    LIBLrnFnH(  DatAprExportData.ImmobilizerSecretKey,
                VerlogCode);
    DatAprExportData.SKey = (U16)((U16)VerlogCode[0] << cShift8) 
                                    | ((U16)VerlogCode[1]);
    break;

  case cDATAprComputeAfterSaleCode:
    ///////////////////////////////
    // Function G(ISK)
    ///////////////////////////////
    LIBLrnFnG(  DatAprExportData.ImmobilizerSecretKey,
                DatAprExportData.AfterSaleCode);
    break;

  case cDATAprComputeISKFromDiagAfterSaleCode:
    ///////////////////////////////
    // Function G-1(AfterSaleCode)
    ///////////////////////////////
    LIBLrnFnGInv(   DatAprExportData.DiagAfterSaleCode,
                    DatAprExportData.ImmobilizerSecretKey);
    break;

  case cDATAprTestDiagAfterSaleCode:
    TestDiagAfterSaleCode();
    break;

  case cDATAprReadAfterSaleCode:
    ReadAfterSaleCode();
    break;

  case cDATAprWriteAfterSaleCode:
    WriteAfterSaleCode();
    break;

  //CCOV: amanevd: Cannot be covered because this default case rises explicit assert
  default:
    mLIBassert(cFalse);
    break;
  }
}

//*****************************************************************************
//  DESCRIPTION         : Initialize DAT_APR
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************

void DATAprInit(void)
{
#ifndef X90_PROJECT
  U8 u8IndexL;

  DatAprExportData.Identifier              = 0;
  DatAprExportData.PasswordTag             = 0;
  DatAprExportData.AfterSaleCodeRecognized = 0;
  DatAprExportData.SKey                    = 0;

  for (u8IndexL = 0; u8IndexL < cDATTrpISKLengthInBytes; u8IndexL++)
  {
    DatAprExportData.ImmobilizerSecretKey[u8IndexL] = 0;
    DatAprExportData.RemoteSecretKey[u8IndexL]      = 0;
    DatAprExportData.AfterSaleCode[u8IndexL]        = 0;    
    DatAprExportData.DiagAfterSaleCode[u8IndexL]    = 0;
    VerlogCode[u8IndexL]           = 0;    
  }
#endif

  mLIBassert(mLIBLrnGetRequiredVersion() == cLIBLrnVersion);
  mLIBassert(cLIBLrnSkLength == cDATTrpISKLengthInBytes);
}
