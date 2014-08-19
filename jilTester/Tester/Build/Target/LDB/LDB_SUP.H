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
// Component:    LDB_SUP
// -----------------------------------------------------------------------------
// $Date:   Apr 27 2009 15:41:56  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_SUP/LDB_SUP.H-arc  $
// $Revision:   1.2  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_SUP/LDB_SUP.H-arc   $
// 
//    Rev 1.2   Apr 27 2009 15:41:56   adzhelp
// Cm003265: Macro mLDBSupIsHwActivated() defined
// 
//    Rev 1.1   Apr 16 2009 10:47:54   adzhelp
// Cm003276: Implementation of sleep mode management
// 
//    Rev 1.0   04 Feb 2009 17:03:18   adzhelp
// Initial revision.
//******************************************************************************

#ifndef I_LDB_SUP_H
#define I_LDB_SUP_H (1)

/*-------------------------------------------------------------------------
  Included files to resolve specific definitions in this file

  #include <system_file_name.h>
  #include "project_file_name.h"
  -------------------------------------------------------------------------*/
#include "ldb.h"

/*-------------------------------------------------------------------------
  Constant data

  #define cCMPConstantName   ((tType) ConstantValue)
  -------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
  Exported Macros

  #define mCMPMacroName   (MacroDefinition)
  -------------------------------------------------------------------------*/ 

//#define mLDBSupInit()
#define mLDBSupEnterSleepMode() LDBSupEnterSleepMode()
#define mLDBSupLeaveSleepMode() LDBSupLeaveSleepMode()

#define mLDBSupIsHwActivated()  (bLDBSupActivatedHw != cFalse)

/*-------------------------------------------------------------------------
Exported type

struct  sCMPStructureName { ... };
union   uCMPUnionName { ... };
enum    eCMPEnumerationName { ... };
typedef Expression tCMPTypeName;

-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
  Exported data

  extern  tType   CMPVariableName;
  extern  tType*  pCMPVariableName; 
  -------------------------------------------------------------------------*/ 
extern BOOL bLDBSupActivatedHw;

/*-------------------------------------------------------------------------
  Constant exported data

  extern const tType  CMPVariableName;
  -------------------------------------------------------------------------*/ 

/*-------------------------------------------------------------------------
  Exported functions

  extern tReturnType CMPFunctionName(tTypeArgument1 ArgumentName1, ... );
  -------------------------------------------------------------------------*/ 

void LDBSupEnterSleepMode(void);
void LDBSupLeaveSleepMode(void);
void LDBSupCallBackSleepTimer(void);

void LDBSupReceiveWithoutAddr(tMsg * const Msg);
void LDBSupControl(const tCtrl Ctrl);


void LDBRefreshWatchDog(void);
void LDBReset(void);
void LDBWaitForCallBack( void );

#endif   /* I_LDB_SUP_H */
