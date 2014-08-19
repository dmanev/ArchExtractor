#ifndef _QAC_
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
// Component:    <Name of the component and its variant number, if any>
//               <Comments about the component (role, algorithm, structure,
//               limitations, defined tasks and events...)>
// -----------------------------------------------------------------------------
// $Date:   Oct 19 2009 16:23:50  $
// $Archive::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_BUZ/LDB_BUZ.c-arc  $
// $Revision:   1.2  $
// -----------------------------------------------------------------------------
// $Log:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_BUZ/LDB_BUZ.c-arc  $
// 
//    Rev 1.2   Oct 19 2009 16:23:50   amarinm1
// Cm005858: Code review corrections, binary code not affected.
// 
//    Rev 1.1   Sep 25 2009 09:13:34   adzhelp
// Cm005225, Cm004744, Cm003262: Move functions to banked area.
// 
//    Rev 1.0   Mar 18 2009 18:02:34   amarinm1
// Initial revision.
//******************************************************************************
#endif

//------------------------------------------------------------------------------
// Body Identification
//------------------------------------------------------------------------------
#define ldb_buz   "ldb_buz"

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------

// This is an example:
// #include <system_file_name.h>
// #include "project_file_name.h"

// This is an example:
// #include "deftypes.h"   // Mandatory layer inclusions should be described
// #include "lib.h"        // in Software Architecture Document
// #include "tos.h"        //
// #include "dat.h"        //
#include "ldb_reg.h"
#include "ldb_har.h"
#include "ldb_buz.h"    



//------------------------------------------------------------------------------
// Local constants
//------------------------------------------------------------------------------

// Double the frequency because one cycle (Hz) needs two level inversions
#define cFrequencyMultiplier    2

// length of DAT buffer to LDB in bytes
#define cDatBufferLength        ((U16)2)


#define cTOE50_BitNumber        0
#define cTMC501_BitNumber       1
#define cLVS50_BitNumber        2
#define cLVR50_BitNumber        3
#define cTMC506_BitNumber       6
#define cTCE50_BitNumber        7


// Doubled values of all hard-coded frequencies
#define cFreq1                  ((U16)1000)
#define cFreq2                  ((U16)1600)
#define cFreq3                  ((U16)1953)
#define cFreq4                  ((U16)2050)
#define cFreq5                  ((U16)2100)
#define cFreq6                  ((U16)2400)
#define cFreq7                  ((U16)2976)
#define cFreq8                  ((U16)4000)
#define cFreqMax                ((U16)8000)


// Predefined values for input clock selection (TCL50) for the above frequencies
// For more info see chapter 8 of NEC 78K0/KE2 User's Manual
// fPRS = 16Mhz
#define cInputClockForFreq1     ((U8)5) // fPRS/2^6 = 250Khz
#define cInputClockForFreq2     ((U8)5)
#define cInputClockForFreq3     ((U8)6) // fPRS/2^8 = 62.5Khz
#define cInputClockForFreq4     ((U8)5)
#define cInputClockForFreq5     ((U8)5)
#define cInputClockForFreq6     ((U8)5)
#define cInputClockForFreq7     ((U8)5)
#define cInputClockForFreq8     ((U8)5)

#define cDefaultInputClock      ((U8)5)
#define cDefaultInputClockFrequency     ((U32)250000)


// Predefined values of CR50 for the above frequencies
#define cClockDivisorForFreq1   ((U8)125)
#define cClockDivisorForFreq2   ((U8)78)
#define cClockDivisorForFreq3   ((U8)16)
#define cClockDivisorForFreq4   ((U8)61)
#define cClockDivisorForFreq5   ((U8)59)
#define cClockDivisorForFreq6   ((U8)52)
#define cClockDivisorForFreq7   ((U8)42)
#define cClockDivisorForFreq8   ((U8)31)




//------------------------------------------------------------------------------
// Local macros
//------------------------------------------------------------------------------

// This is an example:
// #define mMacroName       (MacroDefinition)

//------------------------------------------------------------------------------
// Local types
//------------------------------------------------------------------------------

// This is an example:
// typedef Expression   tTypeName;

//------------------------------------------------------------------------------
// Local data
//------------------------------------------------------------------------------

// This is an example:
// static  tType   VariableName;
// static  tType*  pVariableName;
// static  U8      u8VariableName;
// static  U16*    pu16VariableName;

static U16  u16Freq;
static U8   u8CR50;
static U8   u8TCL50;
static BOOL bLDBBuzIsEnabled;


//------------------------------------------------------------------------------
// Constant local data
//------------------------------------------------------------------------------

// This is an example:
// static const tType  cConstantName;

//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------

// This is an example:
// Reduce to minimum the usage of extern data members!!!
// tType   LAYCmpVariableName;  //LAY: 3 characters to identify the layer
// tType*  pLAYCmpVariableName; //Cmp: 3-4 characters to identify the component
// U8      u8LAYCmpVariableName;
// U16*    pu16LAYCmpVariableName;

//------------------------------------------------------------------------------
// Constant exported data
//------------------------------------------------------------------------------

// This is an example:
// Reduce to minimum the usage of extern constant data members!!!
// extern const tType  cLAYCmpConstantName;
// extern const U32    cu32LAYCmpConstantName;

//------------------------------------------------------------------------------
// Local function prototypes
//------------------------------------------------------------------------------
static MEM_TYPE void ConvertFrequencyToRegisterValue( U16 u16LocalFreqP );
static MEM_TYPE void SetRegistersToCurrentFrequencySettings( void );
static MEM_TYPE void SetRegistersToSilenceSettings( void );


//==============================================================================
//=========================== LOCAL FUNCTIONS ==================================
//==============================================================================

//==============================================================================
// DESCRIPTION:         < short description of the function >
//
// PARAMETERS:          < type,usage and constraints for all parameters >
//
// RETURN VALUE:        < type and usage >
//
// DESIGN INFORMATION:  < usage, pseudo code, algorithm, constraints ... >
//==============================================================================
static MEM_TYPE void ConvertFrequencyToRegisterValue( U16 u16LocalFreqP )
{
    switch( u16LocalFreqP )
    {
    case (U16)0:
        // Do nothing, register values won't be sent.
        break;
    case cFreq1:
        u8TCL50 = cInputClockForFreq1;
        u8CR50  = cClockDivisorForFreq1;
        break;
    case cFreq2:
        u8TCL50 = cInputClockForFreq2;
        u8CR50  = cClockDivisorForFreq2;
        break;
    case cFreq3:
        u8TCL50 = cInputClockForFreq3;
        u8CR50  = cClockDivisorForFreq3;
        break;
    case cFreq4:
        u8TCL50 = cInputClockForFreq4;
        u8CR50  = cClockDivisorForFreq4;
        break;
    case cFreq5:
        u8TCL50 = cInputClockForFreq5;
        u8CR50  = cClockDivisorForFreq5;
        break;
    case cFreq6:
        u8TCL50 = cInputClockForFreq6;
        u8CR50  = cClockDivisorForFreq6;
        break;
    case cFreq7:
        u8TCL50 = cInputClockForFreq7;
        u8CR50  = cClockDivisorForFreq7;
        break;
    case cFreq8:
        u8TCL50 = cInputClockForFreq8;
        u8CR50  = cClockDivisorForFreq8;
        break;
    default:
        if ( u16LocalFreqP > cFreqMax )
        {
            u16LocalFreqP = cFreqMax;
        }
        // The following settings may be improved for better accuracy by adding
        // a rounding calculation and even an algorithm for finding the best
        // input clock!
        u8TCL50 = cDefaultInputClock;
        u8CR50  = (U8)( cDefaultInputClockFrequency / (U32)(u16LocalFreqP * cFrequencyMultiplier) );
    }
}


//==============================================================================
// DESCRIPTION:         < short description of the function >
//
// PARAMETERS:          < type,usage and constraints for all parameters >
//
// RETURN VALUE:        < type and usage >
//
// DESIGN INFORMATION:  < usage, pseudo code, algorithm, constraints ... >
//==============================================================================
static MEM_TYPE void SetRegistersToCurrentFrequencySettings( void )
{
    // 1.Stop count operation before setting other registers (TCE50 = 0)
    mLDBRegWrite1BitInRegister(TMC50, cTCE50_BitNumber, 0);

    // 2.Select input clock
    mLDBRegWrite8BitRegister(TCL50, u8TCL50);
    // 3.Set counter comparator value
    mLDBRegWrite8BitRegister(CR50, (u8CR50 - (U8)1U)); // Compensation for real register value
    // 4.Enable output inversion (TMC501 = 1)
    mLDBRegWrite1BitInRegister(TMC50, cTMC501_BitNumber, 1);
    // 5.Set 'Clear & Start' on (TCL50 == CR50) (TMC506 = 0)
    mLDBRegWrite1BitInRegister(TMC50, cTMC506_BitNumber, 0);
    // 6.Enable the output (TOE50 = 1)
    mLDBRegWrite1BitInRegister(TMC50, cTOE50_BitNumber, 1);
    // 7.Set timer output F/F default level to low (LVS50 = 0, LVR50 = 1)
    mLDBRegWrite1BitInRegister(TMC50, cLVS50_BitNumber, 0);
    mLDBRegWrite1BitInRegister(TMC50, cLVR50_BitNumber, 1);
    // 8.Start count operation!
    mLDBRegWrite1BitInRegister(TMC50, cTCE50_BitNumber, 1);
}


//==============================================================================
// DESCRIPTION:         < short description of the function >
//
// PARAMETERS:          < type,usage and constraints for all parameters >
//
// RETURN VALUE:        < type and usage >
//
// DESIGN INFORMATION:  < usage, pseudo code, algorithm, constraints ... >
//==============================================================================
static MEM_TYPE void SetRegistersToSilenceSettings( void )
{
    // 1.Stop count operation before setting other registers (TCE50 = 0)
    mLDBRegWrite1BitInRegister(TMC50, cTCE50_BitNumber, 0);

    // 2.Disable the output (TOE50 = 0)
    mLDBRegWrite1BitInRegister(TMC50, cTOE50_BitNumber, 0);
}

//==============================================================================
//=========================== EXPORTED FUNCTIONS ===============================
//==============================================================================

//==============================================================================
// DESCRIPTION:         < short description of the function >
//
// PARAMETERS:          < type,usage and constraints for all parameters >
//
// RETURN VALUE:        < type and usage >
//
// DESIGN INFORMATION:  < usage, pseudo code, algorithm, constraints ... >
//==============================================================================
MEM_TYPE void LDBBuzInit (void)
{
    mLDBHarWrite(cLDBHarBuzzerOutput, 0);
    mLDBHarConfig(cLDBHarBuzzerOutput, cLDBHarOutput);

    SetRegistersToSilenceSettings();

    bLDBBuzIsEnabled = cFalse;
}


//==============================================================================
// DESCRIPTION:         < short description of the function >
//
// PARAMETERS:          < type,usage and constraints for all parameters >
//
// RETURN VALUE:        < type and usage >
//
// DESIGN INFORMATION:  < usage, pseudo code, algorithm, constraints ... >
//==============================================================================
MEM_TYPE void LDBBuzControl( const tCtrl Ctrl )
{
    switch ( Ctrl )
    {
    case cLDBBuzEnable:
        bLDBBuzIsEnabled = cTrue;
        break;

    case cLDBBuzStartSound:
        // check if the driver is enabled
        if ( (bLDBBuzIsEnabled == cTrue) && (u16Freq != 0) )
        {
            SetRegistersToCurrentFrequencySettings();
        }
        else
        {
            SetRegistersToSilenceSettings();
        }
        break;

    case cLDBBuzDisable:
        bLDBBuzIsEnabled = cFalse;
        // pass-through to cLDBBuzCancelSound

    //QACJ 2003: amarinm1: It is intended that this case is always executed after the previous one.
    case cLDBBuzCancelSound:
        // stop the sound currently playing 
        SetRegistersToSilenceSettings();
        break;

    default:
        mLIBassert (cFalse);
    }
}


//==============================================================================
// DESCRIPTION:         < short description of the function >
//
// PARAMETERS:          < type,usage and constraints for all parameters >
//
// RETURN VALUE:        < type and usage >
//
// DESIGN INFORMATION:  < usage, pseudo code, algorithm, constraints ... >
//==============================================================================
MEM_TYPE void LDBBuzSendWithoutAddr( const tMsg * const Msg )
{
    if (   (Msg          == NULL)
        || (Msg->pBuffer == NULL)
        || (Msg->Lng     != cDatBufferLength)  )
    {
        mLIBassert( cFalse );
    }
    else
    {
        if ( bLDBBuzIsEnabled == cTrue ) 
        {
            // we come with correct buffer, enabled

            //QACJ 0310: amarinm1: This is intentionally done as this is the original data type.
            //QACJ 3305: amarinm1: This is intentionally done as this is the original data type.
            u16Freq = *((U16 *)Msg->pBuffer);

            // Calculate HW register values for the given frequency
            ConvertFrequencyToRegisterValue(u16Freq);
        }
        else
        {
            // Do nothing
        }

    }
}