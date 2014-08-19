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
// Component:    DAT_PAN
// -----------------------------------------------------------------------------
// $Date:   Mar 08 2010 13:41:28  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_PAN/DAT_PAN.C-arc  $
// $Revision:   1.10  $
// -----------------------------------------------------------------------------
/* $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_PAN/DAT_PAN.C-arc  $
 * 
 *    Rev 1.10   Mar 08 2010 13:41:28   adzhelp
 * Cm007697: Checking of active flasher channel using Immediate access
 * 
 *    Rev 1.9   Feb 13 2010 09:11:08   adzhelp
 * Cm007063: Implementation of flashers' SC VBAT / open load calculation
 * 
 *    Rev 1.8   Feb 03 2010 10:00:58   adzhelp
 * Cm006590, Cm006698: Voltage checking only for active mode
 * 
 *    Rev 1.7   Feb 02 2010 16:50:42   adzhelp
 * Cm006590, Cm006698: Implementation of undervoltage condition checking
 * 
 *    Rev 1.6   Jan 15 2010 10:37:00   adzhelp
 * Cm006709: Coefficients for flasher current updated
 * 
 *    Rev 1.5   Dec 14 2009 11:41:00   adzhelp
 * Cm005566: Implementation of overvoltage protection
 * 
 *    Rev 1.4   Nov 20 2009 15:48:38   adzhelp
 * Cm005566: UT and QAC corrections
 * 
 *    Rev 1.3   Oct 08 2009 12:35:20   adzhelp
 * Cm006355: Calculation of 8bit voltage updated
 * 
 *    Rev 1.2   Sep 25 2009 10:45:52   amanevd
 * Cm006355: cR6006ValueInkOhm changed from 68 to 56
 * 
 *    Rev 1.1   Apr 22 2009 16:38:30   adzhelp
 * Cm003619: Implementation of calculated analog parameters
 * 
 *    Rev 1.0   20 Nov 2008 15:12:10   ailievb
 * Initial revision.
*/ 
//******************************************************************************
#endif

//------------------------------------------------------------------------------
// Body Identification
//------------------------------------------------------------------------------
#define dat_pan  "dat_pan"

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//
// #include <system_file_name.h>
// #include "project_file_name.h"
//------------------------------------------------------------------------------
#include "lib.h"
#include "dat.h"
#include "dat_pan.h"

//------------------------------------------------------------------------------
// Local constants
//
// #define cConstantName   ((tType) ConstantValue)
//------------------------------------------------------------------------------
#define cThousand               1000UL
#define cTen                      10UL

// Vbat calculation parameters
#define cR6006ValueInkOhm       56UL
#define cR6007ValueInkOhm       150UL
#define cAdcMaxValue            1023UL
#define cAdcMaxInputVoltage     5UL
#define cMaxByte                255UL
// These coefficients needs to be updated if upper are changed:
#define cConvTo8BitCoeff        23UL    // 0.23
#define cConvTo8BitDenom        100UL

// Flasher current calculation parameters
#define cFlasherCurrentCoeff    69564UL  // 6956.4

#define cFlasherCurrentCoeff8Bit  915UL // =  (6956.4 / 76) * 10

// Bulb failure calculation parameters (multiplied by 1000):
#define cParameterBulbOffset    9465000UL
#define cParameterBulbFactor    18560UL

// SC to VBAT calculation parameters (multiplied by 1000):
#define cParameterScOffset      753200UL
#define cParameterScFactor      1477UL

// Overvoltage parameters
#define cOverVoltageHighThresholdMv     17200UL
#define cOverVoltageLowThresholdMv      16700UL

#define cOverVoltageHighThresholdAdc    mConvertVoltageMVInAdcUnits_BatteryInput(cOverVoltageHighThresholdMv)
#define cOverVoltageLowThresholdAdc     mConvertVoltageMVInAdcUnits_BatteryInput(cOverVoltageLowThresholdMv)

// Undervoltage parameters
#define cUnderVoltageThresholdMv        6000UL

#define cUnderVoltageThresholdAdc       mConvertVoltageMVInAdcUnits_BatteryInput(cUnderVoltageThresholdMv)

//------------------------------------------------------------------------------
// Local macros
//
// #define mMacroName   (MacroDefinition)
//------------------------------------------------------------------------------
//QACJ 3443: adzhelp: standard STK macros used
#define mCheckLeftFlasherActive() (mDATRead(U1Bit, DI_LEFT,  Immediate) != cFalse)

#define mConvertVoltageMVInAdcUnits_BatteryInput(Voltage) \
    (((U32)(Voltage) * (cAdcMaxValue * cR6006ValueInkOhm)) \
     / ((U32)cAdcMaxInputVoltage * (U32)(cR6006ValueInkOhm + cR6007ValueInkOhm) * (U32)cThousand))

//------------------------------------------------------------------------------
// Local types
//
// typedef Expression    tTypeName;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Data prefix
//
// unsigned int {u8,u16,u32} / signed int {s8,s16,s32} 
// register size unsigned int {r} / float {f32,f64}  / s for struct 
//
// -----------------------------------------------------------------------------
// Local data
//
// static  tType   u8VariableName;  
// static  tType*  pu8VariableName; 
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Constant local data
//
// static const tType  VariableName;
//------------------------------------------------------------------------------
static BOOL bOverVoltageOldStatus;
static U8 u8KilisLeft;
static U8 u8KilisRight;
static U32 u32KilisLeftThousand;
static U32 u32KilisRightThousand;

//------------------------------------------------------------------------------
// Exported data
//
// tType   u8LAYCmpVariableName; (LAY: 3 characters to identify the layer)
// tType*  pu8LAYCmpVariableName;(Cmp: 3 characters to identify the component)
//------------------------------------------------------------------------------
BOOL bDATPanOverVoltageIsDetected;
BOOL bDATPanUnderVoltageIsDetected;
BOOL bDATPanFlasherBulbFailure;
BOOL bDATPanFlasherSCBatOrOpenLoad;

//------------------------------------------------------------------------------
// Constant exported data
//
//             (LAY: 3 characters to identify the layer)
//             (Cmp: 3 characters to identify this component)
// 
// const tType   LAYCmpVariableName;
//------------------------------------------------------------------------------

// Initialisation values for the analog inputs
const U8 DATPanInitialization[cDATPanSizeAnaGeneratorMessage] = 
    cDATPanInitBufferAnaGeneratorMessage;

//------------------------------------------------------------------------------
// Local function prototypes
// 
// static tTypeRetour FunctionName(tTypeArgument1 ArgumentName1, ... );
//------------------------------------------------------------------------------

//==============================================================================
//=========================== LOCAL FUNCTIONS ==================================
//==============================================================================

//==============================================================================
// DESCRIPTION : 
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================

//==============================================================================
//=========================== EXPORTED FUNCTIONS ===============================
//==============================================================================

//==============================================================================
// DESCRIPTION : Call periodicaly when analog input is filtered
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : Empty function
//==============================================================================
void DATPanRefresh( void )
{   
    // Management of overvoltage status
    const U16 u16AdcValueL = mDATRead(U16Bit, DIAG_BAT, Immediate);

    if (mDATRead(U1Bit, BcmSleepMode, Default) == cFalse)
    {
        if (u16AdcValueL > cOverVoltageHighThresholdAdc)
        {
            if (bOverVoltageOldStatus != cFalse)
            {
                bDATPanOverVoltageIsDetected = cTrue;
            }
            else
            {
                // wait 2 consequtive samples
            }
            bOverVoltageOldStatus = cTrue;
        }
        else if (u16AdcValueL < cOverVoltageLowThresholdAdc)
        {
            if (bOverVoltageOldStatus == cFalse)
            {
                bDATPanOverVoltageIsDetected = cFalse;
            }
            else
            {
                // wait 2 consequtive samples
            }
            bOverVoltageOldStatus = cFalse;
        }
        else
        {
            // no change of overvoltage status
        }

        // Management of undervoltage status
        bDATPanUnderVoltageIsDetected = (BOOL)(u16AdcValueL <= cUnderVoltageThresholdAdc);
    }
    else
    {
        // sleep mode
        // retain last voltage status
    }
}

//==============================================================================
// DESCRIPTION : Initialize the macro component DAT_ANA
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : Calls DAT_ANA init
//==============================================================================
void DATPanInit(void )
{
    //QACJ 0310 : adzhelp: The cast is checked and is safe.    
    //QACJ 3305 : adzhelp: The cast is checked and is safe.    
    mDATPanControlInit();

    // DAT_PAN specific initialization
}

//==============================================================================
// DESCRIPTION : Calculate battery voltage in mV
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   U16: battery voltage in mV
//
// DESIGN INFORMATION : Calculation using one 32-bit multiplication and one 32-bit
//                      division. Constant of resistor dividers are used
//==============================================================================
MEM_TYPE U16 DATPanCalculateBatteryVoltage(void)
{
    // HSI padHSI-533: 
    // V(uC_ANI1) = Vbatt * R6006 / (R6006 + R6007)
    //=> Vbat = (Vbat digital value * 5/1023 ) * (R6006+R6007)/R6006
    
    //QACJ 3204: adzhelp: Usage of 'const' is recommended for parameters only
    U16 u16AdcNumberL = mDATRead(U16Bit, DIAG_BAT, Default);

    U32 u32ResultL = (U32)u16AdcNumberL *
        (((U32)cAdcMaxInputVoltage * (U32)(cR6006ValueInkOhm + cR6007ValueInkOhm)) * 
        (U32)cThousand); // The maximal possible value fits in U32
    u32ResultL /= (U32)(cAdcMaxValue * cR6006ValueInkOhm);

    return (U16)u32ResultL;
}

//==============================================================================
// DESCRIPTION : Calculate battery voltage in 8 bits
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   U8: Battery voltage coded in 8 bits
//
// DESIGN INFORMATION : Calculation using one 16-bit division and one 
//                      16-bit multiplication. Constants are precalculated 
//                      based on resistor divider values
//==============================================================================
MEM_TYPE U8 DATPanCalculateBatteryVoltage8Bit(void)
{
    // no 16 bit overflow will occur because max BAT is 1023
    return (U8)((U16)(mDATRead(U16Bit, DIAG_BAT, Default) * (U16)cConvTo8BitCoeff) 
        / (U16)cConvTo8BitDenom);
}

//==============================================================================
// DESCRIPTION : Calculate flashers' current in mA
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   U16: active flasher current in mA
//
// DESIGN INFORMATION : Calculation using one 32-bit multiplication and one 32-bit
//                      division. EEP constant is used.
//==============================================================================
MEM_TYPE U16 DATPanCalculateFlashersCurrent(void)
{
    // HSI padHSI-527: Iout =  Vsense Digital value * Kilis eeprom /15345
    //QACJ 3204: adzhelp: Usage of 'const' is recommended for parameters only
    U8 u8KilisL = (mCheckLeftFlasherActive() ? 
        mDATRead(U8Bit, EEP_FlaCoeffLNormal, Default) :
    mDATRead(U8Bit, EEP_FlaCoeffRNormal, Default) );

    //QACJ 3204: adzhelp: Usage of 'const' is recommended for parameters only
    U16 u16AdcNumberL = mDATRead(U16Bit, DIAG_FLASHER, Default);

    U32 u32ResultL = ((U32)u16AdcNumberL * (U32)u8KilisL) * ((U32)cThousand * (U32)cTen);
    // maximal possible value fits in U32
    u32ResultL /= (U32)cFlasherCurrentCoeff;

    return (U16)u32ResultL;
}

//==============================================================================
// DESCRIPTION : Calculate flashers' current in 8 bits
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   U8: active flasher current coded in 8 bits
//
// DESIGN INFORMATION : Calculation using one 32-bit multiplication and one 32-bit
//                      division. EEP constant is used.
//==============================================================================
MEM_TYPE U8 DATPanCalculateFlashersCurrent8Bit(void)
{
    //QACJ 3204: adzhelp: Usage of 'const' is recommended for parameters only
    U8 u8KilisL = (mCheckLeftFlasherActive() ? 
        mDATRead(U8Bit, EEP_FlaCoeffLNormal, Default) :
    mDATRead(U8Bit, EEP_FlaCoeffRNormal, Default) );

    //QACJ 3204: adzhelp: Usage of 'const' is recommended for parameters only
    U16 u16AdcNumberL = mDATRead(U16Bit, DIAG_FLASHER, Default);

    U32 u32ResultL = ((U32)u16AdcNumberL * (U32)u8KilisL) * (U32)cTen;
        // maximal possible value fits in U32
    u32ResultL /= (U32)cFlasherCurrentCoeff8Bit;

    if (u32ResultL > (U32)cMaxByte)
    {
        u32ResultL = cMaxByte;
    }

    return (U8)u32ResultL;
}

//==============================================================================
// DESCRIPTION : Check for flasher bulb failure
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : 
//==============================================================================
MEM_TYPE void DATPanFlashersCurrentMeasure (void)
{
    U8 u8KilisL;
    U32 u32KilisThousandL;
    U32 u32FormulaLeftSideL;
    
    const U16 u16AdcVsenseL = mDATRead(U16Bit, DIAG_FLASHER, Immediate); 
    const U16 u16AdcVbatL = mDATRead(U16Bit, DIAG_BAT, Immediate); 

    if (mCheckLeftFlasherActive())
    {
        // Use KILIS left
        u8KilisL = mDATRead(U8Bit, EEP_FlaCoeffLNormal, Default);

        if (u8KilisL != u8KilisLeft)
        {
            // perform 32 bit calculations only when values has changed
            u8KilisLeft = u8KilisL;
            u32KilisLeftThousand = (U32)u8KilisL * (U32)cThousand;
        }
        u32KilisThousandL = u32KilisLeftThousand;
    }
    else
    {
        // Use KILIS right
        u8KilisL = mDATRead(U8Bit, EEP_FlaCoeffRNormal, Default);

        if (u8KilisL != u8KilisRight)
        {
            // perform 32 bit calculations only when values has changed
            u8KilisRight = u8KilisL;
            u32KilisRightThousand = (U32)u8KilisL * (U32)cThousand;
        }
        u32KilisThousandL = u32KilisRightThousand;
    }

    // Formula left side common for both conditions:
    u32FormulaLeftSideL = (U32)u16AdcVsenseL * u32KilisThousandL;

    // 1. Check for SC to VBAT or open load
    bDATPanFlasherSCBatOrOpenLoad = cFalse;

    if (u32FormulaLeftSideL <
        ((U32)cParameterScOffset + ((U32)cParameterScFactor * (U32)u16AdcVbatL))
       )
    {
        bDATPanFlasherSCBatOrOpenLoad = cTrue; // SC to VBAT or open load
    }

    // 2. Check for flasher bulb failure
    bDATPanFlasherBulbFailure = cFalse;
    if (bDATPanFlasherSCBatOrOpenLoad == cFalse)
    {
        if (u32FormulaLeftSideL <
            ((U32)cParameterBulbOffset + ((U32)cParameterBulbFactor * (U32)u16AdcVbatL))
           )
        {
            bDATPanFlasherBulbFailure = cTrue; // bulb failure
        }
    }
    else
    {
        bDATPanFlasherBulbFailure = cTrue;
    }
}
