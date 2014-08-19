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
// Component:    LDB_ANA
// -----------------------------------------------------------------------------
// $Date:   Mar 10 2009 09:53:20  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_ANA/LDB_ANAP.H-arc  $
// $Revision:   1.1  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_ANA/LDB_ANAP.H-arc  $
// 
//    Rev 1.1   Mar 10 2009 09:53:20   adzhelp
// Cm003619: Parameterization of LDB_ANA for NEC K0 and project specifics
// 
//    Rev 1.0   20 Nov 2008 15:17:18   ailievb
// Initial revision.
//******************************************************************************

#ifndef I_LDB_ANA_P
#define I_LDB_ANA_P 1

/*-------------------------------------------------------------------------
  Included files to resolve specific definitions in this file

  #include <system_file_name.h>
  #include "project_file_name.h"
  -------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
  Constant data

  #define cCMPConstantName   ((tType) ConstantValue)
  -------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
  Exported Macros

  #define mCMPMacroName   (MacroDefinition)
  -------------------------------------------------------------------------*/ 
#define cLdbAnaFrequency  ((U8)0x08)
  // fprs being the frequency of the quart (16 MHz for these calculation)
  // the register has to be chosen this way : 
  // (conversion time)
  //  0x00 Freq = 264/fprs = 16.5 us
  //  0x04 Freq = 176/fprs = 11 us
  //  0x08 Freq = 132/fprs = 8.25 us
  //  From the NEC Documentation it has to be set above 6.6 us

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

#endif   // fin de l'inclusion conditionnelle de CE_COMPOSANT.h


