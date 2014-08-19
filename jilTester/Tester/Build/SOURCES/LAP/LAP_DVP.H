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
// Component:    LAP_DVP.H
// -----------------------------------------------------------------------------
// $Date:   Apr 22 2009 15:30:52  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_DVP/LAP_DVP.H-arc  $
// $Revision:   1.1  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_DVP/LAP_DVP.H-arc  $
// 
//    Rev 1.1   Apr 22 2009 15:30:52   adzhelp
// Cm003128: MEM_TYPE attribute added to service functions
// 
//    Rev 1.0   12 Mar 2009 15:47:34   akodzhh
// Initial revision.
//******************************************************************************
#endif

#ifndef I_LAP_DVP_H
#define I_LAP_DVP_H (1)

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//  
// #include <system_file_name.h>
// #include "project_file_name.h"
//------------------------------------------------------------------------------
#include "deftypes.h"

//------------------------------------------------------------------------------
// Data prefix for constant & data: see coding guideline
//
//------------------------------------------------------------------------------
// Constant data
//
// #define cu16LAYCmpConstantName   ((U16) ConstantValueUL)
//------------------------------------------------------------------------------
#define cNbServicesSupportedInDVP         ((U8)0x03)
#define cLAPDvpIdDVPSession               ((U8)0xFBUL)

//------------------------------------------------------------------------------
// Exported type
//
// typedef Expression tLAYCmpTypeName;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported data
//
// extern  tType   u8LAYCmpVariableName;
// extern  tType*  ps32LAYCmpVariableName; 
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Constant exported data
//
// extern const tType  s8LAYCmpVariableName;
//------------------------------------------------------------------------------
extern const U8 TabIdentifierServiceSupportedInDvpSession[];
extern const tLAPKwpServiceFunction TabServiceSupportedInDvpSession[];

//------------------------------------------------------------------------------
// Exported Macros
//
// #define LAYCmpMacroName(...)   (MacroDefinition)
//------------------------------------------------------------------------------

#define LAPDvpInitDvpSessionParameters()\
{\
  cNbServicesSupportedInDVP,\
  cLAPDvpIdDVPSession,\
  (const U8 *)TabIdentifierServiceSupportedInDvpSession,\
  (const tLAPKwpServiceFunction *)TabServiceSupportedInDvpSession,\
  LAPDvpCloseSession,\
  LAPDvpInitSession,\
}

//------------------------------------------------------------------------------
// Exported functions
//
// extern tReturnType LAYCmpFunctionName(tTypeArgument1 ArgumentName1, ... );
//------------------------------------------------------------------------------
extern MEM_TYPE void LAPDvpTreatReadDataByLocalIdentifierService(void);
extern MEM_TYPE void LAPDvpTreatStartRoutineByLocalIdentifierService(void);
extern MEM_TYPE void LAPDvpTreatStopRoutineByLocalIdentifierService(void);
extern MEM_TYPE void LAPDvpCloseSession(void);
extern MEM_TYPE void LAPDvpInitSession(void);

#endif   /* I_LAP_DVP_H */
