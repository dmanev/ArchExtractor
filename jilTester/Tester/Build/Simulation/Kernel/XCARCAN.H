/*============================================================================
  Project ......................... XCARCAN
  Interface ....................... XCARCAN
  -------------------------------------------------------------------------
  Copyright ... This software is JCI property. Duplication or
                disclosure is prohibited without JCI written permission
  ------------------------------------------------------------------------- 
    
  - This file should only contain data useful to the programmer to use
    this component
  - Component exported macros, constants and types are defined in this file
  - Component exported variables and functions are declared in this file 
    with the "extern" keyword
  
  -------------------------------------------------------------------------
  XCarCAN.h file review : XCarCANoe.mdl
  ==========================================================================*/

#ifndef I_XCarCAN_DEFINED_H
#define I_XCarCAN_DEFINED_H (1)

/*-------------------------------------------------------------------------
  Included files

  #include <system_file_name.h>
  #include "project_file_name.h"
  --------------------------------------------------------------------------*/
#include "deftypes.h"

//-----------------------------------------------------------------------------
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the XCARCAN_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// XCARCAN_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef XCARCAN_EXPORTS
#define XCARCAN_API __declspec(dllexport)
#else
#define XCARCAN_API __declspec(dllimport)
#endif

//---- Set 8 bytes alignment ----
#pragma pack( push , 8)

//-----------------------------------------------------------------------------

/*-------------------------------------------------------------------------
  Exported type

  struct  sCMPStructureName { ... };
  union   uCMPUnionName { ... };
  enum    eCMPEnumerationName { ... };
  typedef Expression tCMPTypeName;

  -------------------------------------------------------------------------*/
typedef unsigned __int64 tU64Bit;
class tcCanDll;

//-----------------------------------------------------------------------------
// XCarCAN Interface
//-----------------------------------------------------------------------------
extern "C" XCARCAN_API void XCAN_SetConfiguration(char * ConfigName);

extern "C" XCARCAN_API tcCanDll* XCAN_GetCANConnection(char * NodeName, char * ToolName);

extern "C" XCARCAN_API int XCAN_OpenDialogBox();

extern "C" XCARCAN_API U8   XCAN_Open();
extern "C" XCARCAN_API void XCAN_Close();

//---- Set default alignment ----
#pragma pack( pop )


#endif // I_XCarCAN_DEFINED_H