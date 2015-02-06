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
// Component:    LAP_TFC.H
// -----------------------------------------------------------------------------
// $Date:   Nov 20 2009 09:52:44  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_TFC/LAP_TFC.H-arc  $
// $Revision:   1.3  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_TFC/LAP_TFC.H-arc  $
// 
//    Rev 1.3   Nov 20 2009 09:52:44   akodzhh
// Cm006705: QAC - warnings resolved and justified.
// 
//    Rev 1.2   Apr 22 2009 15:28:02   adzhelp
// Cm003517: MEM_TYPE attribute added to service functions
// 
//    Rev 1.1   20 Mar 2009 18:18:32   akodzhh
// Cm003128 - fixes for warnings and some data names, Checksum calculation, sleep timeout measurement - use graph instead of task.
// 
//    Rev 1.0   Mar 17 2009 16:53:32   akodzhh
// Initial revision.
//******************************************************************************
#endif


#ifndef I_LAP_TFC_H
#define I_LAP_TFC_H (1)

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------
#ifdef _QAC_
#include "lap_kwp.h"
#endif
//------------------------------------------------------------------------------
// Constant data
//------------------------------------------------------------------------------
#define cNbServicesSupportedInTFC   ((U8)0x04)
#define cIdTFCSession               ((U8)0xFAUL)

//------------------------------------------------------------------------------
// Exported type
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Constant exported data
//------------------------------------------------------------------------------
//QACJ 3684: akodzhh: array size declared in lap_tfc.c 
extern const U8              TabIdentifierServiceSupportedInTfcSession[];
//QACJ 3684: akodzhh: array size declared in lap_tfc.c
extern const tLAPKwpServiceFunction TabServiceSupportedInTfcSession[];

//------------------------------------------------------------------------------
// Exported Macros
//------------------------------------------------------------------------------
#define LAPTfcInitTFCDiagSessionParameters()  \
{\
  cNbServicesSupportedInTFC,\
  cIdTFCSession,\
  (const U8 *)TabIdentifierServiceSupportedInTfcSession,\
  (const tLAPKwpServiceFunction *)TabServiceSupportedInTfcSession,\
  LAPTfcCloseSession,\
  LAPTfcInitSession,\
}

//------------------------------------------------------------------------------
// Exported functions
//------------------------------------------------------------------------------
extern MEM_TYPE void LAPTfcCloseSession(void);
extern MEM_TYPE void LAPTfcInitSession(void);
extern MEM_TYPE void LAPTfcTreatReadDataByLocalIdentifierService(void);
extern MEM_TYPE void LAPTfcTreatWriteDataByLocalIdentifierService(void);
extern MEM_TYPE void LAPTfcTreatInputOutputControlByLocalIdentifierService(void);
extern MEM_TYPE void LAPTfcTreatStartRoutineByLocalIdentifierService(void);

#endif   //  I_LAP_TFC_H 

