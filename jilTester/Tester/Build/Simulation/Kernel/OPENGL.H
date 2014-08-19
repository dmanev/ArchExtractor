/****************************************************************************
  Project ......................... STANDARD
  Component ....................... COpenGl
  File revision.................... :   1.0  $
  Last modification date .......... $Modtime:   04 Feb 2009 16:32:32  $
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
   $Workfile:   OPENGL.H  $ file review :
  
   :   P:/STANDARD/AEH/STK/PVCS/archives/STK/BUILD/SIMUL/KERNEL/OpenGl.h-arc  $
 * 
 *    Rev 1.0   Apr 30 2003 08:13:16   abarbae
 * Initial revision.
 * 
 *    Rev 1.0   Oct 04 2002 15:36:22   guillen
 * Initial revision.

*****************************************************************************/

#ifndef	I_OPENGL_H
#define I_OPENGL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*--------------------------------------------------------------------------
  Included files to resolve specific definitions in this file

  #include <system_file_name.h>
  #include "project_file_name.h"
  --------------------------------------------------------------------------*/

#include "DefTypes.h"

/*--------------------------------------------------------------------------
  Constant data

  #define cCMPConstantName   ((tType) ConstantValue)
  --------------------------------------------------------------------------*/

#define cMAX_SCREEN	((U8)0xFF)

// Screen Option
#define	cSCR_AUTO_SAVE_POS	0x00000001
#define	cSCR_AUTO_REFRESH	0x00000010

/*--------------------------------------------------------------------------
  Exported types

  struct  sCMPStructureName { ... };
  union   uCMPUnionName { ... };
  enum    eCMPEnumerationName { ... };
  typedef Expression tCMPTypeName;

  --------------------------------------------------------------------------*/

typedef struct
{
    U32 screenId;
    U8 * pName;
    U32 x;
    U32 y;
    U32 cx;
    U32 cy;
    U32 option;
    U32 refreshPeriodMs;
    CWnd * pParent;
} tScreen;


#endif // I_OPENGL_H
