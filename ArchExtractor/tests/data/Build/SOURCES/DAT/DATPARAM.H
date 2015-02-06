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
// Component:    DAT_API
// -----------------------------------------------------------------------------
// $Date:   Apr 28 2009 09:45:40  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_API/DATPARAM.H-arc  $
// $Revision:   1.6  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_API/DATPARAM.H-arc            $
// 
//    Rev 1.6   Apr 28 2009 09:45:40   adzhelp
// Cm003272: DAT_VLG.H, DAT_TRP.H, DAT_APR.H added
// 
//    Rev 1.5   Apr 24 2009 17:05:18   adzhelp
// Cm003271, Cm003264, Cm003265: DAT_ALA.H, DAT_RBG.H, DAT_RF.H added
// 
//    Rev 1.4   Apr 10 2009 15:27:34   adzhelp
// Cm003264: Header file of DAT_SPD included
// 
//    Rev 1.3   Mar 20 2009 18:04:00   adzhelp
// Cm003619: Header file of DAT_PAN, DAT_CMN, DAT_KWP and DAT_BUZ included
// 
//    Rev 1.2   06 Feb 2009 08:52:26   adzhelp
// Cm003465: DAT_PWM header added
// 
//    Rev 1.1   Nov 12 2008 15:18:20   ailievb
// Cm003465: DAT_PAN header removed
// 
//    Rev 1.0   Nov 10 2008 10:13:52   ailievb
// Initial revision.
//
//******************************************************************************

#ifndef I_DATPARAM_H
#define I_DATPARAM_H (1)

/*-------------------------------------------------------------------------
  Included files to resolve specific definitions in this file

  #include <system_file_name.h>
  #include "project_file_name.h"
  -------------------------------------------------------------------------*/

// Add the header file of DAT Components
#include "DAT_CPU.H"
#include "DAT_PEE.H"
#include "DAT_PIN.H"
#include "DAT_POU.H"
#include "DAT_PAN.H"
#include "DAT_CMN.H"
#include "DAT_KWP.H"
#include "DAT_PWM.H"
#include "DAT_VLG.H"
#include "DAT_TRP.H"
#include "DAT_APR.H"
#include "DAT_BUZ.H"
#include "DAT_SPD.H"
#include "DAT_ALA.H"
#include "DAT_RBG.H"
#include "DAT_RF.H"


// TODO : DATPC Using
//#define DATPC_ENABLE	1
#if defined(COMPILATION_NATIVE) && defined(DATPC_ENABLE)
#include "DatpcPar.h"
#endif

/*-------------------------------------------------------------------------
  Constant data

  #define cCMPConstantName   ((tType) ConstantValue)
  -------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
  Exported Macro

  #define mCMPMacroName   (MacroDefinition)
  -------------------------------------------------------------------------*/ 

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

/*-------------------------------------------------------------------------
  Constant exported data

  extern const tType  CMPVariableName;
  -------------------------------------------------------------------------*/ 

/*-------------------------------------------------------------------------
  Exported functions

  extern tReturnType CMPFunctionName(tTypeArgument1 ArgumentName1, ... );
  -------------------------------------------------------------------------*/ 

/*-------------------------------------------------------------------------
  End of includes non re entry
  -------------------------------------------------------------------------*/
#endif   /* I_DATPARAM_H */

