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
// Component:    LDB_SPI
// -----------------------------------------------------------------------------
// $Date:   Mar 06 2009 15:54:06  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_SPI/LDB_SPI.H-arc  $
// $Revision:   1.2  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_SPI/LDB_SPI.H-arc  $
// 
//    Rev 1.2   Mar 06 2009 15:54:06   adzhelp
// Cm003619: LDB_SPI parameterization
// 
//    Rev 1.1   06 Mar 2009 15:36:22   adzhelp
// Cm003619: Integration of standard LDB_SPI with SW management 
//
//    Rev 1.0   04 Feb 2009 17:03:22   adzhelp
// Initial revision.
//******************************************************************************

/*-------------------------------------------------------------------------
  Includes non re entry
  -------------------------------------------------------------------------*/
#ifndef I_LDB_SPI_H
#define I_LDB_SPI_H (1)

/*-------------------------------------------------------------------------
  Included files to resolve specific definitions in this file

  #include <system_file_name.h>
  #include "project_file_name.h"
  -------------------------------------------------------------------------*/
#include "ldb.h"
#include "ldb_spip.h"

/*-------------------------------------------------------------------------
  Constant data

  #define cCNLConstantName   ((tType) ConstantValue)
  -------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
  Exported Macros

  #define mCNLMacroName   (MacroDefinition)
  -------------------------------------------------------------------------*/ 
#define mLDBSpiInit()           LDBSpiInit()
#define mLDBSpiEnterSleepMode() mLDBSpiLRPutSckinIdleMode()
#define mLDBSpiLeaveSleepMode() mLDBSpiLRPutSckinIdleMode()

#define mLDBSpiLRReceiveByte()  LDBSpiLRReceiveBits(8)
#define mLDBSpiLRSendByte(Data) LDBSpiLRSendBits(Data,8)

#define mLDBSpiLFReceiveByte()  LDBSpiLFReceiveBits(8)
#define mLDBSpiLFSendByte(Data) LDBSpiLFSendBits(Data,8)

#if (cLDBSpiSckLevelInIdleMode == 0)
  #define mLDBSpiLRPutSckinIdleMode() mLDBHarWrite(cLDBHarSpiSCK,0);  \
                                      mLDBHarWrite(cLDBHarSpiSO,0)
  #define mLDBSpiLFPutSckinIdleMode() mLDBHarWrite(cLDBHarSpiSO,0)
#elif (cLDBSpiSckLevelInIdleMode == 1)
  #define mLDBSpiLRPutSckinIdleMode() mLDBHarWrite(cLDBHarSpiSO,1)
  #define mLDBSpiLFPutSckinIdleMode() mLDBHarWrite(cLDBHarSpiSCK,1);\
                                      mLDBHarWrite(cLDBHarSpiSO,1)
#else
  #error "bad value for cLDBSpiSckLevelInIdleMode"
#endif

/*-------------------------------------------------------------------------
  Exported type

  struct  sCNLStructureName { ... };
  union   uCNLUnionName { ... };
  enum    eCNLEnumerationName { ... };
  typedef Expression tCNLTypeName;

  -------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
  Exported data

  extern  tType   CNLVariableName;
  extern  tType*  pCNLVariableName; 
  -------------------------------------------------------------------------*/ 

/*-------------------------------------------------------------------------
  Constant exported data

  extern const tType  CNLVariableName;
  -------------------------------------------------------------------------*/ 

/*-------------------------------------------------------------------------
  Exported functions

  extern tReturnType CNLFunctionName(tTypeArgument1 ArgumentName1, ... );
  -------------------------------------------------------------------------*/ 
#ifdef LDBSPI_FORMAT_LR_USED
extern U8 LDBSpiLRReceiveBits(U8);
extern void   LDBSpiLRSendBits(U8,U8);
#endif

#ifdef LDBSPI_FORMAT_LF_USED
extern U8 LDBSpiLFReceiveBits(U8);
extern void   LDBSpiLFSendBits(U8,U8);
#endif

extern void   LDBSpiInit(void);

/*-------------------------------------------------------------------------
  End of includes non re entry
  -------------------------------------------------------------------------*/
#endif   /* I_LDB_SPI_H */
