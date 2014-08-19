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
// Component:    LDB_RF
// -----------------------------------------------------------------------------
// $Date:   Feb 08 2010 11:10:38  $
// $Archive::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_RF/LDB_RF.h-arc  $
// $Revision:   1.4  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_RF/LDB_RF.h-arc  $
// 
//    Rev 1.4   Feb 08 2010 11:10:38   adzhelp
// Cm005818: Corrections according to JML issues
// 
//    Rev 1.3   Oct 06 2009 17:40:38   adzhelp
// Cm005818: Function moved to banked area
// 
//    Rev 1.2   Sep 07 2009 10:23:12   ailievb
// Cm005100: QAC and code review fix.
// 
//    Rev 1.1   Apr 28 2009 10:42:18   adzhelp
// Cm003276: Implementation of RF sleep mode management
// 
//    Rev 1.0   Apr 16 2009 15:37:00   ailievb
// Initial revision.
//******************************************************************************
#endif

#ifndef I_LDB_RF_H
#define I_LDB_RF_H (1)
//-------------------------------------------------------------------------
//  Included files to resolve specific definitions in this file
//
//  #include <system_file_name.h>
//  #include "project_file_name.h"
//-------------------------------------------------------------------------

#include "ldb_rfp.h"
//-------------------------------------------------------------------------
//  Constant data
//
//  #define cCNLConstantName   ((tType) ConstantValue)
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//  Exported Macros
//
//  #define mCNLMacroName   (MacroDefinition)
//-------------------------------------------------------------------------
#define mLDBRfInit                         LDBRfInit
#define mLDBRfEnterSleepMode()             (LDBRfControl(cLDBRfEnterSleepMode))
#define mLDBRfLeaveSleepMode()             (LDBRfControl(cLDBRfEnterNominalMode))

#define mLDBRfIsWakeUpDetectionFinished() \
    (bLDBRfIsWakeUpDetectionFinished != cFalse)

//-------------------------------------------------------------------------
//  Exported type
//
//  struct  sCNLStructureName { ... };
//  union   uCNLUnionName { ... };
//  enum    eCNLEnumerationName { ... };
//  typedef Expression tCNLTypeName;
//
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//  Exported data
//
//  extern  tType   CNLVariableName;
//  extern  tType*  pCNLVariableName; 
//-------------------------------------------------------------------------
#ifdef _DEBUG_LDBRF_ //externalized for TestU
  extern U16 NbLDBControlSearchWUP;
  extern U16 NbWUPTimeOut;
  extern U16 NbWUPBlocksSeen;
  extern U16 NbMPatternsSeen;
  extern U16 Nb1stPreambleDetectionSeen;
  extern U16 NbRCBlocksSeen;
  extern U16 NbSIBlocksSeen;
#endif

extern BOOL bLDBRfIsWakeUpDetectionFinished;
//-------------------------------------------------------------------------
//  Constant exported data
//
//  extern const tType  CNLVariableName;
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//  Exported functions
//
//  extern tReturnType CNLFunctionName(tTypeArgument1 ArgumentName1, ... );
//-------------------------------------------------------------------------

extern MEM_TYPE void LDBRfInit(void);
extern MEM_TYPE void LDBRfControl(const U8);
extern void LDBRfCallBackSleepTick(void);

#ifndef UTEST
extern void LDBRfInterruptRfICIt(void);
extern void LDBRfInterruptRfOCIt(void);
#endif

#endif   /* I_LDB_RF_H */
