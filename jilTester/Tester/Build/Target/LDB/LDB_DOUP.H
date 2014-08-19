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
// Component:    LDB_DOU
// -----------------------------------------------------------------------------
// $Date:   Oct 06 2009 11:40:46  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_DOU/LDB_DOUP.H-arc  $
// $Revision:   1.2  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_DOU/LDB_DOUP.H-arc  $
// 
//    Rev 1.2   Oct 06 2009 11:40:46   adzhelp
// Cm005497: Implementation of unused pins treatment
// 
//    Rev 1.1   Mar 12 2009 08:57:48   adzhelp
// Cm003619: Parameterization of digital outputs
// 
//    Rev 1.0   10 Nov 2008 15:28:18   ailievb
// Initial revision.
//******************************************************************************

//----  Mono-inclusion Definition-----
#ifdef I_LDB_DOUP
#else
#define I_LDB_DOUP 1

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------

// This is an example:
// Reduce to minimum the inclusions!!!
// #include <system_file_name.h>
// #include "project_file_name.h"

//------------------------------------------------------------------------------
// Constant data
//------------------------------------------------------------------------------

// Correspondance HW level <-> ECU type
#define cLDBDouEcuTypeL1    ((U8)cLDBDouSetEcuType0)
#define cLDBDouEcuTypeL2    ((U8)cLDBDouSetEcuType1)
#define cLDBDouEcuTypeL3    ((U8)cLDBDouSetEcuType2)
#define cLDBDouEcuTypeL4    ((U8)cLDBDouSetEcuType4)
#define cLDBDouEcuTypeL5    ((U8)cLDBDouSetEcuType6)
#define cLDBDouEcuTypeL6    ((U8)cLDBDouSetEcuType5)
#define cLDBDouEcuTypeL7    ((U8)cLDBDouSetEcuType7)

// Configurations of analog pins register ADPC
#define cLDBDouADPCInitActiveL1 (U8)0x00U
#define cLDBDouADPCInitActiveL2 (U8)0x01U
#define cLDBDouADPCInitActiveL3 (U8)0x00U
#define cLDBDouADPCInitActiveL4 (U8)0x03U
#define cLDBDouADPCInitActiveL5 (U8)0x01U
#define cLDBDouADPCInitActiveL6 (U8)0x01U
#define cLDBDouADPCInitActiveL7 (U8)0x00U

#define cLDBDouADPCInitSleepL1  (U8)0x08U
#define cLDBDouADPCInitSleepL2  (U8)0x01U
#define cLDBDouADPCInitSleepL3  (U8)0x00U
#define cLDBDouADPCInitSleepL4  (U8)0x08U
#define cLDBDouADPCInitSleepL5  (U8)0x01U
#define cLDBDouADPCInitSleepL6  (U8)0x01U
#define cLDBDouADPCInitSleepL7  (U8)0x00U

// Configurations of digital pins register shared with analog PM2
#define cLDBDouPM2InitActiveL1  (U8)0xFFU
#define cLDBDouPM2InitActiveL2  (U8)0xFEU
#define cLDBDouPM2InitActiveL3  (U8)0xFFU
#define cLDBDouPM2InitActiveL4  (U8)0xF8U
#define cLDBDouPM2InitActiveL5  (U8)0xFEU
#define cLDBDouPM2InitActiveL6  (U8)0xFEU
#define cLDBDouPM2InitActiveL7  (U8)0xFFU

#define cLDBDouPM2InitSleepL1   (U8)0xFFU
#define cLDBDouPM2InitSleepL2   (U8)0xFEU
#define cLDBDouPM2InitSleepL3   (U8)0xFFU
#define cLDBDouPM2InitSleepL4   (U8)0xF8U
#define cLDBDouPM2InitSleepL5   (U8)0xFEU
#define cLDBDouPM2InitSleepL6   (U8)0xFEU
#define cLDBDouPM2InitSleepL7   (U8)0xFFU

//------------------------------------------------------------------------------
// Exported Macros
//------------------------------------------------------------------------------

// ECU Type general macros
#ifndef _QAC_
#define mLDBDouConfigUnusedPins(Mode, Type) mLDBDouConfigUnusedPins##Mode(Type)

#define mLDBDouConfigUnusedPinsActive(Type) \
    mLDBDouConfigUnusedDigitalInputsActive(Type); \
    mLDBDouConfigUnusedAnalogInputsActive(Type); \
    mLDBDouConfigUnusedDigitalOutputsActive(Type)

#define mLDBDouConfigUnusedPinsSleep(Type) \
    mLDBDouConfigUnusedDigitalInputsSleep(Type); \
    mLDBDouConfigUnusedAnalogInputsSleep(Type); \
    mLDBDouConfigUnusedDigitalOutputsSleep(Type)

#define mLDBDouConfigUnusedDigitalInputsActive(Type)    mLDBDouConfigUnusedDigitalInputsActive##Type()

#define mLDBDouConfigUnusedAnalogInputsActive(Type) \
    mLDBRegWrite8BitRegister(PM2, cLDBDouPM2InitActive##Type); \
    mLDBRegWrite8BitRegister(ADPC, cLDBDouADPCInitActive##Type)

#define mLDBDouConfigUnusedDigitalOutputsActive(Type) \
    /* Implemented in component */ \
    mConfigUnusedDigitalOutputsActive##Type()

#define mLDBDouConfigUnusedDigitalInputsSleep(Type)    mLDBDouConfigUnusedDigitalInputsActive##Type()

#define mLDBDouConfigUnusedAnalogInputsSleep(Type) \
    mLDBRegWrite8BitRegister(PM2, cLDBDouPM2InitSleep##Type); \
    mLDBRegWrite8BitRegister(ADPC, cLDBDouADPCInitSleep##Type)

#define mLDBDouConfigUnusedDigitalOutputsSleep(Type) /* No implementation needed */ 

// L1
#define mLDBDouConfigUnusedDigitalInputsActiveL1() \
    /* Port 40 */ \
    mLDBHarConfig(cLDBHarPort4_0, cLDBHarInput); \
    /* Port 124 */ \
    mLDBHarWrite(cLDBHarPort12_4, 0); \
    mLDBHarConfig(cLDBHarPort12_4, cLDBHarOutput); \
    /* Port 60 */ \
    mLDBHarConfig(cLDBHarPort6_0, cLDBHarInput); \
    /* Port 61 */ \
    mLDBHarConfig(cLDBHarPort6_1, cLDBHarInput); \
    /* Port 62 */ \
    mLDBHarConfig(cLDBHarPort6_2, cLDBHarInput); \
    /* Port 63 */ \
    mLDBHarConfig(cLDBHarPort6_3, cLDBHarInput); \
    /* Port 51 */ \
    mLDBHarConfig(cLDBHarPort5_1, cLDBHarInput); \
    /* Port 01 */ \
    mLDBHarWrite(cLDBHarPort0_1, 0); \
    mLDBHarConfig(cLDBHarPort0_1, cLDBHarOutput)

// L2
#define mLDBDouConfigUnusedDigitalInputsActiveL2() \
    /* Port 40 */ \
    mLDBHarConfig(cLDBHarPort4_0, cLDBHarInput); \
    /* Port 124 */ \
    mLDBHarConfig(cLDBHarPort12_4, cLDBHarInput); \
    /* Port 60 */ \
    mLDBHarWrite(cLDBHarPort6_0, 0); \
    mLDBHarConfig(cLDBHarPort6_0, cLDBHarOutput); \
    /* Port 61 */ \
    mLDBHarWrite(cLDBHarPort6_1, 0); \
    mLDBHarConfig(cLDBHarPort6_1, cLDBHarOutput); \
    /* Port 62 */ \
    mLDBHarWrite(cLDBHarPort6_2, 0); \
    mLDBHarConfig(cLDBHarPort6_2, cLDBHarOutput); \
    /* Port 63 */ \
    mLDBHarWrite(cLDBHarPort6_3, 0); \
    mLDBHarConfig(cLDBHarPort6_3, cLDBHarOutput); \
    /* Port 51 */ \
    mLDBHarConfig(cLDBHarPort5_1, cLDBHarInput); \
    /* Port 01 */ \
    mLDBHarConfig(cLDBHarPort0_1, cLDBHarInput)

// L3
#define mLDBDouConfigUnusedDigitalInputsActiveL3() \
    mLDBDouConfigUnusedDigitalInputsActiveL2()

// L4
#define mLDBDouConfigUnusedDigitalInputsActiveL4() \
    /* Port 40 */ \
    mLDBHarWrite(cLDBHarPort4_0, 0); \
    mLDBHarConfig(cLDBHarPort4_0, cLDBHarOutput); \
    /* Port 124 */ \
    mLDBHarWrite(cLDBHarPort12_4, 0); \
    mLDBHarConfig(cLDBHarPort12_4, cLDBHarOutput); \
    /* Port 60 */ \
    mLDBHarWrite(cLDBHarPort6_0, 0); \
    mLDBHarConfig(cLDBHarPort6_0, cLDBHarOutput); \
    /* Port 61 */ \
    mLDBHarWrite(cLDBHarPort6_1, 0); \
    mLDBHarConfig(cLDBHarPort6_1, cLDBHarOutput); \
    /* Port 62 */ \
    mLDBHarWrite(cLDBHarPort6_2, 0); \
    mLDBHarConfig(cLDBHarPort6_2, cLDBHarOutput); \
    /* Port 63 */ \
    mLDBHarWrite(cLDBHarPort6_3, 0); \
    mLDBHarConfig(cLDBHarPort6_3, cLDBHarOutput); \
    /* Port 51 */ \
    mLDBHarWrite(cLDBHarPort5_1, 0); \
    mLDBHarConfig(cLDBHarPort5_1, cLDBHarOutput); \
    /* Port 01 */ \
    mLDBHarWrite(cLDBHarPort0_1, 0); \
    mLDBHarConfig(cLDBHarPort0_1, cLDBHarOutput)

// L5
#define mLDBDouConfigUnusedDigitalInputsActiveL5() \
    mLDBDouConfigUnusedDigitalInputsActiveL3()

// L6
#define mLDBDouConfigUnusedDigitalInputsActiveL6() \
    mLDBDouConfigUnusedDigitalInputsActiveL3()

// L7
#define mLDBDouConfigUnusedDigitalInputsActiveL7() \
    /* Port 40 */ \
    mLDBHarConfig(cLDBHarPort4_0, cLDBHarInput); \
    /* Port 124 */ \
    mLDBHarConfig(cLDBHarPort12_4, cLDBHarInput); \
    /* Port 60 */ \
    mLDBHarConfig(cLDBHarPort6_0, cLDBHarInput); \
    /* Port 61 */ \
    mLDBHarConfig(cLDBHarPort6_1, cLDBHarInput); \
    /* Port 62 */ \
    mLDBHarConfig(cLDBHarPort6_2, cLDBHarInput); \
    /* Port 63 */ \
    mLDBHarConfig(cLDBHarPort6_3, cLDBHarInput); \
    /* Port 51 */ \
    mLDBHarConfig(cLDBHarPort5_1, cLDBHarInput); \
    /* Port 01 */ \
    mLDBHarConfig(cLDBHarPort0_1, cLDBHarInput)

#else // _QAC_
#define mLDBDouConfigUnusedPins(Mode, Type) NOP()
#endif

//------------------------------------------------------------------------------
// Exported type
//------------------------------------------------------------------------------

// This is an example:
// typedef Expression tLAYCmpTypeName;

//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------

// This is an example:
// Reduce to minimum the usage of extern data members!!!
// extern  tType   LAYCmpVariableName;
// extern  tType*  pLAYCmpVariableName;
// extern  U8      u8LAYCmpVariableName;
// extern  U16*    pu16LAYCmpVariableName;


//------------------------------------------------------------------------------
// Constant exported data
//------------------------------------------------------------------------------

// This is an example:
// Reduce to minimum the usage of extern constant data members!!!
// extern const tType  cLAYCmpConstantName;
// extern const U32    cu32LAYCmpConstantName;


//------------------------------------------------------------------------------
// Exported functions
//------------------------------------------------------------------------------

// This is an example:
// tType LAYCmpFunctionName( tTypeArgument1 ArgumentName1, ... );

#endif // I_LDB_DOUP
