/*============================================================================
  Project ......................... STANDARD
  Component ....................... ldb_har
  File revision.................... $Revision:   1.0  $
  Last modification date .......... $Modtime:   03 Nov 2008 15:50:42  $
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
  cmp.h file review :
  


  ==========================================================================*/

#ifndef I_LDB_HAR_H
#define I_LDB_HAR_H (1)

/*-------------------------------------------------------------------------
  Included files to resolve specific definitions in this file

  #include <system_file_name.h>
  #include "project_file_name.h"
  -------------------------------------------------------------------------*/

#include "deftypes.h"
#include "ldb_harp.h"
#include "ldb_reg.h"

/*-------------------------------------------------------------------------
  Constant data

  #define cCMPConstantName   ((tType) ConstantValue)
  -------------------------------------------------------------------------*/

#define cLDBHarInput  1
#define cLDBHarOutput 0

/*-------------------------------------------------------------------------
  Exported Macros

  #define mCMPMacroName   (MacroDefinition)
  -------------------------------------------------------------------------*/ 
#define mLDBHarInit()               (LDBHarInit())

#define mLDBHarConfig(Signal,Dir)   mLDBHarConfig2(Signal,Dir)
#define mLDBHarWrite(Signal,Value)  mLDBHarWrite2(Signal,Value)
#define mLDBHarRead(Signal)         mLDBHarRead2(Signal)

#define mLDBHarConfig2(Signal,Dir)   { PM##Signal = Dir;  }
#define mLDBHarWrite2(Signal,Value)  { P##Signal = Value; }
#define mLDBHarRead2(Signal)         ( P##Signal )


// Macro mLDBHarActiveWaitUs :
// This macro give service to an active wait of n microsecond
// the precision and the step of the macro depend on the frequency of the main clock
// the minimum value(in µs) is equal to 83 / Main Frequency(in MHz)
// the step value (in µs) is equal to 29 / Main Frequency(in MHz)

#define mLDBHarActiveWaitUs(DelayInUs )                                                           \
          LDBHarActiveWaitUs(                                                                     \
              (((U16)DelayInUs *(cLDBHarMainClockInHz/1000000UL))<= ((U16)55UL)) ?        \
              0 :                                                                  \
              (U16)( (  ((U16)DelayInUs)                                   \
                           *((U16)(cLDBHarMainClockInHz/1000000UL))            \
                           -((U16)56UL))                                       \
                        /((U16)28UL)                                           \
                        +((U16)1UL )))

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
extern void LDBHarInit(void);
extern void LDBHarActiveWaitUs(U16 CompteurMax);


#endif   /* I_CMP_H */
