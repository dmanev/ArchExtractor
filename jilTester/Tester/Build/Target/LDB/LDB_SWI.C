//******************************************************************************
// Company:      Johnson Controls Inc.
// -----------------------------------------------------------------------------
// Copyright:    This software is JCI property.
//               Duplication or disclosure without JCI written authorization
//               is prohibited.
// -----------------------------------------------------------------------------
// Project:      X90_BCM
// Language:     C
// -----------------------------------------------------------------------------
// Component:    LDB_SWI
// -----------------------------------------------------------------------------
// $Date:   Nov 17 2009 11:22:48  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_SWI/LDB_SWI.C-arc  $
// $Revision:   1.7  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_SWI/LDB_SWI.C-arc             $
// 
//    Rev 1.7   Nov 17 2009 11:22:48   adzhelp
// Cm006675: LDB_BUZ initialization excluded for CPU trace configuration
// 
//    Rev 1.6   Jul 16 2009 09:22:12   adzhelp
// Cm005205: LDB_PWM.h included
// 
//    Rev 1.5   Apr 27 2009 15:31:34   adzhelp
// Cm003272: LDB_TRP added; LDBSupEnterSleepMode() called last
// 
//    Rev 1.4   Apr 22 2009 17:47:42   adzhelp
// Cm003265: LDB_RF channel added
// 
//    Rev 1.3   Apr 13 2009 15:19:20   adzhelp
// Cm003271: LDB_ALA channel added
// 
//    Rev 1.2   Apr 10 2009 14:15:36   adzhelp
// Cm003264: Integration of LDB_SPD
// 
//    Rev 1.1   Mar 20 2009 14:49:44   adzhelp
// Cm003619: LDB_KWP and LDB_BUZ channels added
// 
//    Rev 1.0   Feb 04 2009 17:03:14   adzhelp
// Initial revision.
//
//******************************************************************************

/*--------------------------------------------------------------------------
  Body Identification
  --------------------------------------------------------------------------*/

#define ldb_swi   "ldb_swi"

/*-------------------------------------------------------------------------
  Included files

  #include <system_file_name.h>
  #include "project_file_name.h"
  --------------------------------------------------------------------------*/
#include "ldb.h"
#include "lib.h"
#include "ldb_ana.h"
#include "ldb_kwp.h"
#include "ldb_buz.h"
#include "ldb_spd.h"
#include "ldb_ala.h"
#include "ldb_rf.h"
#include "ldb_trp.h"
#include "ldb_pwm.h"
#include "ldb_swi.h"

/*--------------------------------------------------------------------------
  Local constants

  #define cConstantName   ((tType) ConstantValue)
  --------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------
  Local macros

  #define mMacroName   (MacroDefinition)
  --------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------
  Local types

  struct  sStructureName { ... };
  union   uUnionName { ... };
  enum    eEnumerationName { ... };
  typedef Expression tTypeName;
  --------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------
  Local data

  static  tType   VariableName;
  static  tType*  pVariableName; 
  --------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------
  Constant local data

  static const tType  VariableName;
  --------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------
  Exported data

  tType   CMPVariableName;      (CMP: 3 characters to identify this component)
  tType*  pCMPVariableName;     (CMP: 3 characters to identify this component)
  --------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------
  Constant exported data
 
  const tType   CMPVariableName;(CMP: 3 characters to identify this component)
  --------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------
  Local function prototypes
  
  static tTypeRetour FunctionName(tTypeArgument1 ArgumentName1, ... );
  --------------------------------------------------------------------------*/
#ifdef X90_PROJECT
static MEM_TYPE void LDBInit_Static(void);
static MEM_TYPE void LDBEnterSleepMode_Static(void);
static MEM_TYPE void LDBLeaveSleepMode_Static(void);
#endif


/*============================================================================
  =========================== LOCAL FUNCTIONS ================================
  ==========================================================================*/
/*============================================================================
  DESCRIPTION :
  
  PARAMETERS (Type,Name,Min,Max) :   none

  RETURN VALUE :   none
 
  DESIGN INFORMATION :   refer to Detailed Design Document
  ==========================================================================*/
//static type FunctionName(...)


/*============================================================================
  =========================== EXPORTED FUNCTIONS =============================
  ==========================================================================*/
/*============================================================================
  DESCRIPTION :void LDBInit(void)
                Init of the LDB layer
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void LDBInit(void)
{
#ifdef X90_PROJECT
    LDBInit_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LDBInit_Static(void)
{
#endif

#ifdef mLDBHarInit
      mLDBHarInit();
#endif
#ifdef mLDBSupInit
     mLDBSupInit();
#endif
#ifdef mLDBIntInit
     mLDBIntInit();
#endif
#ifdef mLDBTimInit
     mLDBTimInit();
#endif
#ifdef mLDBSpiInit
      mLDBSpiInit();
#endif
#ifdef mLDBEepInit
      mLDBEepInit();
#endif
#ifdef mLDBKwpInit
      mLDBKwpInit();
#endif
#ifdef mLDBCanInit
      mLDBCanInit();
#endif
#ifdef mLDBAnaInit
      mLDBAnaInit();
#endif
#ifdef mLDBPwmInit
      mLDBPwmInit();
#endif
#ifdef mLDBDinInit
      mLDBDinInit();
#endif
#ifdef mLDBDouInit
      mLDBDouInit();
#endif
#ifdef mLDBFlaInit
      mLDBFlaInit();
#endif
#ifdef mLDBLshInit
      mLDBLshInit();
#endif
#ifdef mLDBLmhInit
      mLDBLmhInit();
#endif
#ifdef mLDBMotInit
      mLDBMotInit();
#endif
#ifdef mLDBBuzInit
#ifndef TRACE_CPU_ACTIVE // buzzer channel is not used for CPU trace
    mLDBBuzInit();
#endif
#endif
#ifdef mLDBSpdInit
    mLDBSpdInit();
#endif
#ifdef mLDBAlaInit
    mLDBAlaInit();
#endif
#ifdef mLDBRfInit
    mLDBRfInit();
#endif
#ifdef mLDBTrpInit
    mLDBTrpInit();
#endif
}
/*============================================================================
  DESCRIPTION :void LDBEnterSleepMode(void)
                Enter in sleep mode
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void LDBEnterSleepMode(void)
{
#ifdef X90_PROJECT
    LDBEnterSleepMode_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LDBEnterSleepMode_Static(void)
{
#endif

#ifdef mLDBIntEnterSleepMode
     mLDBIntEnterSleepMode();
#endif
#ifdef mLDBTimEnterSleepMode
     mLDBTimEnterSleepMode();
#endif
#ifdef mLDBEepEnterSleepMode
      mLDBEepEnterSleepMode();
#endif
#ifdef mLDBSpiEnterSleepMode
      mLDBSpiEnterSleepMode();
#endif
#ifdef mLDBKwpEnterSleepMode
      mLDBKwpEnterSleepMode();
#endif
#ifdef mLDBCanEnterSleepMode
      mLDBCanEnterSleepMode();
#endif
#ifdef mLDBAnaEnterSleepMode
      mLDBAnaEnterSleepMode();
#endif
#ifdef mLDBPwmEnterSleepMode
      mLDBPwmEnterSleepMode();
#endif
#ifdef mLDBDinEnterSleepMode
      mLDBDinEnterSleepMode();
#endif
#ifdef mLDBDouEnterSleepMode
      mLDBDouEnterSleepMode();
#endif
#ifdef mLDBFlaEnterSleepMode
      mLDBFlaEnterSleepMode();
#endif
#ifdef mLDBLshEnterSleepMode
      mLDBLshEnterSleepMode();
#endif
#ifdef mLDBLmhEnterSleepMode
      mLDBLmhEnterSleepMode();
#endif
#ifdef mLDBHarEnterSleepMode
      mLDBHarEnterSleepMode();
#endif
#ifdef mLDBMotEnterSleepMode
      mLDBMotEnterSleepMode();
#endif
#ifdef mLDBBuzEnterSleepMode
      mLDBBuzEnterSleepMode();
#endif
#ifdef mLDBSpdEnterSleepMode
      mLDBSpdEnterSleepMode();
#endif
#ifdef mLDBAlaEnterSleepMode
      mLDBAlaEnterSleepMode();
#endif
#ifdef mLDBRfEnterSleepMode
      mLDBRfEnterSleepMode();
#endif
#ifdef mLDBTrpEnterSleepMode
      mLDBTrpEnterSleepMode();
#endif
#ifdef mLDBSupEnterSleepMode
     mLDBSupEnterSleepMode();
#endif
}
/*============================================================================
  DESCRIPTION :void LDBLeaveSleepMode(void)
                Init of the LDB layer
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void LDBLeaveSleepMode(void)
{
#ifdef X90_PROJECT
    LDBLeaveSleepMode_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LDBLeaveSleepMode_Static(void)
{
#endif

#ifdef mLDBHarLeaveSleepMode
     mLDBHarLeaveSleepMode();
#endif
#ifdef mLDBSupLeaveSleepMode
     mLDBSupLeaveSleepMode();
#endif
#ifdef mLDBIntLeaveSleepMode
     mLDBIntLeaveSleepMode();
#endif
#ifdef mLDBTimLeaveSleepMode
     mLDBTimLeaveSleepMode();
#endif
#ifdef mLDBSpiLeaveSleepMode
      mLDBSpiLeaveSleepMode();
#endif
#ifdef mLDBEepLeaveSleepMode
      mLDBEepLeaveSleepMode();
#endif
#ifdef mLDBKwpLeaveSleepMode
      mLDBKwpLeaveSleepMode();
#endif
#ifdef mLDBCanLeaveSleepMode
      mLDBCanLeaveSleepMode();
#endif
#ifdef mLDBAnaLeaveSleepMode
      mLDBAnaLeaveSleepMode();
#endif
#ifdef mLDBPwmLeaveSleepMode
      mLDBPwmLeaveSleepMode();
#endif
#ifdef mLDBDinLeaveSleepMode
      mLDBDinLeaveSleepMode();
#endif
#ifdef mLDBDouLeaveSleepMode
      mLDBDouLeaveSleepMode();
#endif
#ifdef mLDBFlaLeaveSleepMode
      mLDBFlaLeaveSleepMode();
#endif
#ifdef mLDBLshLeaveSleepMode
      mLDBLshLeaveSleepMode();
#endif
#ifdef mLDBLmhLeaveSleepMode
      mLDBLmhLeaveSleepMode();
#endif
#ifdef mLDBMotLeaveSleepMode
      mLDBMotLeaveSleepMode();
#endif
#ifdef mLDBBuzLeaveSleepMode
      mLDBBuzLeaveSleepMode();
#endif
#ifdef mLDBSpdLeaveSleepMode
      mLDBSpdLeaveSleepMode();
#endif
#ifdef mLDBAlaLeaveSleepMode
      mLDBAlaLeaveSleepMode();
#endif
#ifdef mLDBRfLeaveSleepMode
      mLDBRfLeaveSleepMode();
#endif
#ifdef mLDBTrpLeaveSleepMode
      mLDBTrpLeaveSleepMode();
#endif
}

