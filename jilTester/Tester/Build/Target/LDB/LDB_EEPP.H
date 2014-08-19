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
// Component:    LDB_EEP
// -----------------------------------------------------------------------------
// $Date:   Mar 06 2009 16:00:30  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_EEP/LDB_EEPP.H-arc  $
// $Revision:   1.1  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_EEP/LDB_EEPP.H-arc  $
// 
//    Rev 1.1   Mar 06 2009 16:00:30   adzhelp
// Cm003619: Sleep/inactive level ot CS set
// 
//    Rev 1.0   10 Nov 2008 15:30:18   ailievb
// Initial revision.
//******************************************************************************

/*-------------------------------------------------------------------------
  Includes non re entry
  -------------------------------------------------------------------------*/
#ifndef I_LDB_EEPP_H
#define I_LDB_EEPP_H (1)

/*-------------------------------------------------------------------------
  Included files to resolve specific definitions in this file

  #include <system_file_name.h>
  #include "project_file_name.h"
  -------------------------------------------------------------------------*/
#include "ldb_reg.h"
#include "ldb_har.h"

/*-------------------------------------------------------------------------
  Constant data

  #define cCMPConstantName   ((tType) ConstantValue)
  -------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
  Exported Macros

  #define mCMPMacroName   (MacroDefinition)
  -------------------------------------------------------------------------*/ 
// Control used
#define mLDBEepSendByteToSPI(Byte)              mLDBSpiLRSendByte(Byte)
#define mLDBEepSendBitsToSPI(DataByte, NbBits)  LDBSpiLRSendBits(DataByte, NbBits)
#define mLDBEepReadByteFromSPI()                mLDBSpiLRReceiveByte()

#define mLDBEepPutSPIInIdleMode()               mLDBSpiLRPutSckinIdleMode()

#define mLDBEepEnterSleepMode()                 mLDBHarWrite(cLDBHarEepCS, 0) // CS is output only pin

#define mLDBEepLeaveSleepMode()                 mLDBHarWrite(cLDBHarEepCS, 0) // CS is output only pin

#define mLDBEepSelectMemoryOrganization()

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
#endif   /* I_LDB_EEPP_H */
