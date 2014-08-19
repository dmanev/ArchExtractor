/*============================================================================
  Project ......................... STANDARD
  Component ....................... LDB_REG
  File revision.................... :   1.1  $
  Last modification date .......... $Modtime:   Mar 23 2009 16:13:30  $
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

#ifndef I_LDB_REG_H
#define I_LDB_REG_H (1)

/*-------------------------------------------------------------------------
  Included files to resolve specific definitions in this file

  #include <system_file_name.h>
  #include "project_file_name.h"
  -------------------------------------------------------------------------*/
#include "deftypes.h"
#ifndef _QAC_
#include "io78f0536_64.h"
#include "intrinsics.h"
#endif
/*-------------------------------------------------------------------------
  Constant data

  #define cCMPConstantName   ((tType) ConstantValue)
  -------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
  Exported Macros

  #define mCMPMacroName   (MacroDefinition)
  -------------------------------------------------------------------------*/ 
#define mLDBRegNop() __no_operation()

#ifdef _QAC_

// Write a bit in a register
  #define mLDBRegWrite1BitInRegister(RegisterName, BitNb, BitToWrite)    NOP()

// Write a 8 bit register
  #define mLDBRegWrite8BitRegister(RegisterName, ByteToWrite)  NOP()

// Write a 16 bit register
  #define mLDBRegWrite16BitRegister(RegisterName, WordToWrite) NOP()

// Read a bit in a register
  #define mLDBRegRead1BitInRegister(RegisterName, BitNb) 0

// Read a 8 bit register
  #define mLDBRegRead8BitRegister(RegisterName) 0

// Read a 16 bit register
  #define mLDBRegRead16BitRegister(RegisterName) 0

#else

// Write a bit in a register
  #define mLDBRegWrite1BitInRegister(ID, P0, P1) mLDBRegWrite1BitInRegisterx(ID, P0, P1)
  #define mLDBRegWrite1BitInRegisterx(Register, BitNumber, Value) \
    (Register##_bit.no##BitNumber = Value)

// Write a 8 bit register
  #define mLDBRegWrite8BitRegister(RegisterName, ByteToWrite) \
      (RegisterName = (U8)(ByteToWrite))

// Write a 16 bit register
  #define mLDBRegWrite16BitRegister(RegisterName, WordToWrite) \
      (RegisterName = (U16)(WordToWrite))

// Read a bit in a register
  #define mLDBRegRead1BitInRegister(ID, P0) mLDBRegRead1BitInRegisterx(ID, P0)
  #define mLDBRegRead1BitInRegisterx(Register, BitNumber) \
    (Register##_bit.no##BitNumber)
  #define mLDBRegReadBitRegister mLDBRegRead1BitInRegister

// Read a 8 bit register
  #define mLDBRegRead8BitRegister(RegisterName) \
      ((U8)RegisterName)

// Read a 16 bit register
  #define mLDBRegRead16BitRegister(RegisterName) \
      ((U16)RegisterName)

#endif  /*_QAC_*/

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


#endif   /* I_CMP_H */
