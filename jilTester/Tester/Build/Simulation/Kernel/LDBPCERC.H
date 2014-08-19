/*============================================================================
  Project ......................... PROJECT
  Component ....................... LDBPCErc
  File revision.................... :   1.0  $
  Last modification date .......... $Modtime:   04 Feb 2009 16:32:30  $
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
  LDBPCErc.h file review :
  


  ==========================================================================*/

#ifndef I_LDBPCErc
#define I_LDBPCErc

/*-------------------------------------------------------------------------
  Included files to resolve specific definitions in this file

  #include <system_file_name.h>
  #include "project_file_name.h"
  -------------------------------------------------------------------------*/
#include "deftypes.h"

/*-------------------------------------------------------------------------
  Exported data

  extern  tType   CMPVariableName;
  extern  tType*  pCMPVariableName; 
  -------------------------------------------------------------------------*/ 
extern const char * pECStringError[];

/*-------------------------------------------------------------------------
  Constant data

  #define cCMPConstantName   ((tType) ConstantValue)
  -------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
                         Errors Codes of LDBPC
  -------------------------------------------------------------------------*/

#define cEC00000    ((U32) 0)       // No Error
#define cEC00001    ((U32) 1)       // Erreur 
#define cEC00002    ((U32) 2)       // No Error
#define cEC00003    ((U32) 3)       // Erreur 
#define cEC00004    ((U32) 4)       // No Error
#define cEC00005    ((U32) 5)       // Erreur 
#define cEC00006    ((U32) 6)       // No Error
#define cEC00007    ((U32) 7)       // Erreur 
#define cEC00008    ((U32) 8)       // No Error
#define cEC00009    ((U32) 9)       // Erreur 
#define cEC00010    ((U32) 10)      // No Error
#define cEC00011    ((U32) 11)      // Erreur 


#endif // I_LDBPCErc
