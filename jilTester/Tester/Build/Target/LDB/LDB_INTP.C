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
// Component:    LDB_INTp
// -----------------------------------------------------------------------------
// $Date:   Jul 16 2009 08:55:36  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_INT/LDB_INTP.C-arc  $
// $Revision:   1.3  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_INT/LDB_INTP.C-arc  $
// 
//    Rev 1.3   Jul 16 2009 08:55:36   adzhelp
// Cm005205: INTTMH1 shared between sleep system timer, verlog and roomlamp dimming
// 
//    Rev 1.2   Jul 10 2009 15:06:36   adzhelp
// Cm005100: SAD.ROB.INT.02.R01 - Unexpected interrupts treatment  
// 
//    Rev 1.1   Apr 27 2009 15:52:08   adzhelp
// Cm003619: Integration test corrections
// 
//    Rev 1.0   Apr 27 2009 11:20:50   adzhelp
// Initial revision.
// 
//******************************************************************************

/*--------------------------------------------------------------------------
  Body Identification
  --------------------------------------------------------------------------*/

#define LDB_INTP   "LDB_INTP"

/*-------------------------------------------------------------------------
  Included files

  #include <system_file_name.h>
  #include "project_file_name.h"
  --------------------------------------------------------------------------*/

#include "ldb_intp.h"
#include "ldb_swi.h"
#include "ldb_har.h"
#include "ldb_trp.h"
#include "ldb_pwm.h"

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

U8 LDBIntInterruptOwnerTM00TM01 = cLDBIntNoOwnerTM00TM01;
U8 LDBIntInterruptOwnerTMH1     = cLDBIntNoOwnerTMH1;

/*--------------------------------------------------------------------------
  Constant exported data
 
  const tType   CMPVariableName;(CMP: 3 characters to identify this component)
  --------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------
  Local function prototypes
  
  static tTypeRetour FunctionName(tTypeArgument1 ArgumentName1, ... );
  --------------------------------------------------------------------------*/


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
  DESCRIPTION : Unexpected interrupt treatment
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
mLDBIntDeclareIsr(UnexpectedInterrupt)
{
    mLIBassert(cFalse);
    LDBReset();
}

/*============================================================================
  DESCRIPTION : INTTM001 Interrupt service
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
mLDBIntDeclareIsr(INTTM001)
{
    mLDBIntEnterIsr(INTTM001);

    if (LDBIntInterruptOwnerTM00TM01 == cLDBIntTrpOwnerTM00TM01)
    {
        LDBTrpPPGIt();
    }
    else
    {
        mLIBassert(LDBIntInterruptOwnerTM00TM01 == cLDBIntRfOwnerTM00TM01);
        LDBRfInterruptRfOCIt();
    }

    mLDBIntLeaveIsr(INTTM001);
}

/*============================================================================
  DESCRIPTION : INTTM000 Interrupt service
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
mLDBIntDeclareIsr(INTTM000)
{
    mLDBIntEnterIsr(INTTM000);

    if (LDBIntInterruptOwnerTM00TM01 == cLDBIntTrpOwnerTM00TM01)
    {
        LDBTrpTimeOutIt();
    }
    else
    {
        mLIBassert(LDBIntInterruptOwnerTM00TM01 == cLDBIntRfOwnerTM00TM01);
        mLIBassert(cFalse); // not used by RF
    }  

    mLDBIntLeaveIsr(INTTM000);
}

/*============================================================================
  DESCRIPTION : INTTM011 Interrupt service
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
mLDBIntDeclareIsr(INTTM011)
{
    mLDBIntEnterIsr(INTTM011);

    if (LDBIntInterruptOwnerTM00TM01 == cLDBIntTrpOwnerTM00TM01)
    {
        LDBTrpTimeCaptureIt();
    }
    else
    {
        mLIBassert(LDBIntInterruptOwnerTM00TM01 == cLDBIntRfOwnerTM00TM01);
        mLIBassert(cFalse);  // not used by RF
    }  

    mLDBIntLeaveIsr(INTTM011);
}

/*============================================================================
  DESCRIPTION : INTTM011 Interrupt service
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
mLDBIntDeclareIsr(INTTM010)
{
    mLDBIntEnterIsr(INTTM010);

    if (LDBIntInterruptOwnerTM00TM01 == cLDBIntTrpOwnerTM00TM01)
    {
        mLIBassert(cFalse);
    }
    else
    {
        mLIBassert(LDBIntInterruptOwnerTM00TM01 == cLDBIntRfOwnerTM00TM01);
        LDBRfInterruptRfICIt();
    }  

    mLDBIntLeaveIsr(INTTM010);
}

/*============================================================================
  DESCRIPTION : INTTMH1 Interrupt service
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
mLDBIntDeclareIsr(INTTMH1)
{
    mLDBIntEnterIsr(INTTMH1);

    if (LDBIntInterruptOwnerTMH1 == cLDBIntTrpPwmOwnerTMH1)
    {
        if (mLDBTrpIsVerlogTimerEnabled()) // LDB_TRP ISR invoked only when enabled
        {          
            LDBTrpVerlogTimerIt();
        }
        if (mLDBPwmIsFadingControlRequested())
        {
            // LDB_PWM ISR invoked only when change control requested
            LDBPwmControlFadingIt();
        }
        // No callback may be called: No need to disable interrupt for simplicity and 
        // because then the system is not heavily loaded (IMMO not operating)
    }
    else
    {
        mLIBassert(LDBIntInterruptOwnerTMH1 == cLDBIntTimOwnerTMH1);
        LDBTimSleepInterruptRealTime();
    }

    mLDBIntLeaveIsr(INTTMH1);
}
