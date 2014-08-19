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
// Component:    LAP_AFS.H
// -----------------------------------------------------------------------------
// $Date:   Mar 08 2010 14:12:18  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_ASF/LAP_AFS.H-arc  $
// $Revision:   1.3  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_ASF/LAP_AFS.H-arc  $
// 
//    Rev 1.3   Mar 08 2010 14:12:18   adzhelp
// Cm007695: LAPAfsClearFaultFlagsAndCounters() declared
// 
//    Rev 1.2   Oct 27 2009 15:31:54   adzhelp
// Cm006382: Service SecurityAccess implemented
// 
//    Rev 1.1   Apr 22 2009 15:26:08   adzhelp
// Cm003128: MEM_TYPE attribute added to service functions
// 
//    Rev 1.0   Feb 18 2009 14:49:26   akodzhh
// Initial revision.
//******************************************************************************
#endif

#ifndef I_LAP_AFS_H
#define I_LAP_AFS_H (1)

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------
#ifdef _QAC_
#include "lap_kwp.h"
#endif
//------------------------------------------------------------------------------
// Constant data
//------------------------------------------------------------------------------
#define cNbServicesSupportedInAFS   ((U8)0x08)
#define cAPVIdLearningModeControl   ((U8)0x80)

#define cLAPAfsIdAFSSession               ((U8)0xC0)
#define cLAPAfsIdPlantSession             ((U8)0xB0)
#define cLAPAfsIdDvpCustomerSession       ((U8)0xA0)

//------------------------------------------------------------------------------
// Exported type
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Constant exported data
//------------------------------------------------------------------------------
extern const U8 TabIdentifierServiceSupportedInAfsSession[cNbServicesSupportedInAFS];
extern const tLAPKwpServiceFunction TabServiceSupportedInAfsSession[cNbServicesSupportedInAFS];

//------------------------------------------------------------------------------
// Exported Macros
//------------------------------------------------------------------------------
#define LAPAfsInitAfsSessionParameters()\
{\
  cNbServicesSupportedInAFS,\
  cLAPAfsIdAFSSession,\
  (const U8 *)TabIdentifierServiceSupportedInAfsSession,\
  (const tLAPKwpServiceFunction *)TabServiceSupportedInAfsSession,\
  LAPAfsCloseSession,\
  LAPAfsInitSession,\
}

#define LAPAfsInitPlantSessionParameters()\
{\
  cNbServicesSupportedInAFS,\
  cLAPAfsIdPlantSession,\
  (const U8 *)TabIdentifierServiceSupportedInAfsSession,\
  (const tLAPKwpServiceFunction *)TabServiceSupportedInAfsSession,\
  LAPAfsCloseSession,\
  LAPAfsInitSession,\
}

#define LAPAfsInitDvpCustomerSessionParameters()\
{\
  cNbServicesSupportedInAFS,\
  cLAPAfsIdDvpCustomerSession,\
  (const U8 *)TabIdentifierServiceSupportedInAfsSession,\
  (const tLAPKwpServiceFunction *)TabServiceSupportedInAfsSession,\
  LAPAfsCloseSession,\
  LAPAfsInitSession,\
}

//------------------------------------------------------------------------------
// Exported functions
//------------------------------------------------------------------------------
extern MEM_TYPE void LAPAfsTreatWriteDataByLocalIdentifierService(void);
extern MEM_TYPE void LAPAfsTreatReadDataByLocalIdentifierService(void);
extern MEM_TYPE void LAPAfsTreatInputOutputControlByLocalIdentifierService(void);
extern MEM_TYPE void LAPAfsTreatLearningModeControlService(void);
extern MEM_TYPE void LAPAfsTreatStartRoutineByLocalIdentifierService(void);
extern MEM_TYPE void LAPAfsTreatStopRoutineByLocalIdentifierService(void);
extern MEM_TYPE void LAPAfsTreatClearDiagnosticInformation(void);
extern MEM_TYPE void LAPAfsTreatSecurityAccessService(void);
extern MEM_TYPE void LAPAfsCloseSession(void);
extern MEM_TYPE void LAPAfsInitSession(void);
extern void LAPAfsIsMaintainActiveState(void);
extern void LAPAfsClearFaultFlagsAndCounters(void);

#endif   // I_LAP_AFS_H






























 