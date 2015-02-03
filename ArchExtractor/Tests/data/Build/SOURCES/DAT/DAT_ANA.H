//******************************************************************************
// Company:      Johnson Controls Inc.
// -----------------------------------------------------------------------------
// Copyright:    This software is JCI property.
//               Duplication or disclosure without JCI written authorization
//               is prohibited.
// -----------------------------------------------------------------------------
// Project:      <STANDARD>
// Language:     C
// -----------------------------------------------------------------------------
// Component:    <Comments about the component (role, algorithm, structure, 
//               limitations, defined tasks and events...)>
//******************************************************************************

#ifndef I_ANA_H
#define I_ANA_H

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//
// #include <system_file_name.h>
// #include "project_file_name.h"
//------------------------------------------------------------------------------

#include "deftypes.h"
#include "ldb.h"
#include "dat_anap.h"
#include "dat_anax.h"

//------------------------------------------------------------------------------
// Data prefix for constant & data
//
// unsigned int {u8,u16,u32} / signed int {s8,s16,s32} 
// register size unsigned int {r} / float {f32,f64}  / s for struct 
// no prefix for other types.
//
//------------------------------------------------------------------------------
// Constant data
//
// #define cu16LAYCmpConstantName   ((U16) ConstantValueUL)
//------------------------------------------------------------------------------
// Used for the initialisation
#define cDATAnaCoeff16          ((U8) 16UL)

#if(cDATAnaNumberOfBitsNonType < 9UL)
    // Used for 8 bits ADC
    #define cDATAnaNbByteValue          ((U8)1UL)
#else
    // Used for 10 bits ADC
    #define cDATAnaNbByteValue          ((U8)2UL)
#endif

//------------------------------------------------------------------------------
// Exported type
//
// typedef Expression tLAYCmpTypeName;
//------------------------------------------------------------------------------

#if(cDATAnaNumberOfBitsNonType < 9UL)
    // Used for 8 bits ADC
    typedef U8 tDATAnaValue;
#else
    // Used for 10 bits ADC
    typedef U16 tDATAnaValue;
#endif

#if ((cDATAnaInMaxNonType * cDATAnaDivisorValueNonType * cDATAnaKMaxNonType) < 0xFFFFUL)
    // Used for a 16 bits calculation (better on 8bits microcontrollers)
    typedef U16 tDATAnaCalculationSize;
#else
    // Used for a 32 bits calculation
    typedef U32 tDATAnaCalculationSize;
#endif

//------------------------------------------------------------------------------
// Exported Macros
//
// #define LAYCmpMacroName(...)   (MacroDefinition)
//------------------------------------------------------------------------------

// Definition of macros to access to data
#ifdef ConstantDivisor
   #define   mDATAnaGetFilteredValue( Channel ) \
                      ( (tDATAnaValue)(DATAnaFilteredBuffer[Channel]  / cDATAnaDivisorValue))
#else
   #define   mDATAnaGetFilteredValue( Channel ) \
                      ( (tDATAnaValue)(DATAnaFilteredBuffer[Channel]  >> DATAnaDivisorValueNow[Channel]))
#endif

#define   mDATAnaGetValue( Channel )       \
                      ( (tDATAnaValue)(DATAnaBufferFromLDB[Channel]) )

//------------------------------------------------------------------------------
// Exported data
//
// extern  tType   u8LAYCmpVariableName;
// extern  tType*  ps32LAYCmpVariableName; 
//------------------------------------------------------------------------------

// table containing the analog entries values
extern tDATAnaValue DATAnaBufferFromLDB[cDATAnaNumberOfChanels];

// table containing the filtered analog entries values
extern    tDATAnaCalculationSize DATAnaFilteredBuffer[cDATAnaNumberOfChanels];

//Filter values
#ifdef ConstantDivisor
    // Filtering with a constant divisor 
    // Table containing the different coefficient values
    extern const U8 DATAnaCoeffValue[cDATAnaNumberOfChanels];
#else
    // Filtering with a constant coefficient (1) 
    // Table containing the different divisor values
    extern const U8 DATAnaDivisorValueNow[cDATAnaNumberOfChanels];
#endif


//------------------------------------------------------------------------------
// Constant exported data
//
// extern const tType  s8LAYCmpVariableName;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported functions
//
// extern tReturnType LAYCmpFunctionName(tTypeArgument1 ArgumentName1, ... );
//------------------------------------------------------------------------------

extern MEM_TYPE void    DATAnaInitialize(const tDATAnaValue *StartingValues);

extern void    DATAnaStart(void);
extern void    DATAnaStop(void);

extern void    DATAnaTask(void);

extern void    DATAnaCallBackEndCtrl  (tCtrl, tStatus);
extern void    DATAnaCallBackRxWithoutAddr (tStatus);

// DAT_PAN's Call-back
extern void DATPanRefresh( void );

#endif
