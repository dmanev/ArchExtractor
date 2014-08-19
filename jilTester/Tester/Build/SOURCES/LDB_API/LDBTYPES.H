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
// Component:    LDB_API
// -----------------------------------------------------------------------------
// $Date:   Apr 07 2009 13:55:58  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_API/LDBTYPES.H-arc  $
// $Revision:   1.1  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_API/LDBTYPES.H-arc            $
// 
//    Rev 1.1   Apr 07 2009 13:55:58   adzhelp
// Cm003619: Type 'LDBPARAM_DELAY_TYPE' (tDelay) changed to U8
// 
//    Rev 1.0   Feb 04 2009 17:03:14   adzhelp
// Initial revision.
//
//******************************************************************************

#ifndef I_LDBTYPES_H
#define I_LDBTYPES_H (1)


/*-------------------------------------------------------------------------
  Included files to resolve specific definitions in this file

  #include <system_file_name.h>
  #include "project_file_name.h"
  -------------------------------------------------------------------------*/
#include "deftypes.h"
#include "lib.h"

#if defined(__cplusplus)
#define extern extern "C"
#endif


/*-------------------------------------------------------------------------
  Constant data

  #define cCMPConstantName   ((tType) ConstantValue)
  -------------------------------------------------------------------------*/

// Choose the PC access memory format for E_CAR
#ifdef COMPILATION_NATIVE
#define cFormatIntel
#else
// Choose the target access memory format
#define cFormatIntel
#endif

// Type configuration
#define LDBPARAM_CHANNEL_TYPE    U8
#define LDBPARAM_ADDRESS_TYPE  U16
#define LDBPARAM_CTRL_TYPE     U8
#define LDBPARAM_STATUS_TYPE   U8
#define LDBPARAM_TIMERREF_TYPE U8
#define LDBPARAM_TYPE_LNGMSG   U16

#if(defined(COMPILATION_NATIVE) && (!defined(_QAC_)) && (!defined(ATTOL_COV)))

		#define LDBPARAM_DELAY_TYPE    unsigned __int64
#else
		#define LDBPARAM_DELAY_TYPE    U8
#endif

#ifndef COMPILATION_NATIVE
	#define TEMPO_TYPE 2
	#define LDB_MACRO_SERVICES
#endif

/*-------------------------------------------------------------------------
  Exported Macro

  #define mCMPMacroName   (MacroDefinition)
  -------------------------------------------------------------------------*/ 
#ifdef COMPILATION_NATIVE
	#define mLDBPARAM_SIMULATE_PROCESSING_TIME_MACRO(x) LDBSimulerTempsTraitement((x))
	#define mLDBPARAM_TRACE_MACRO( Texte )       LDBPcTrace( (Texte) )
#else
	#define mLDBPARAM_SIMULATE_PROCESSING_TIME_MACRO(x) 
	#define mLDBPARAM_TRACE_MACRO( Texte )       
#endif
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
#endif   /* I_LDBTYPES_H */
