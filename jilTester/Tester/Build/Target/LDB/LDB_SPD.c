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
// Component:    LDB_SPD
// -----------------------------------------------------------------------------
// $Date:   Oct 14 2009 17:20:30  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_SPD/LDB_SPD.c-arc  $
// $Revision:   1.2  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_SPD/LDB_SPD.c-arc  $
// 
//    Rev 1.2   Oct 14 2009 17:20:30   adzhelp
// Cm005225, Cm004744, Cm003262: Code review corrections
// 
//    Rev 1.1   Sep 25 2009 09:13:34   adzhelp
// Cm005225, Cm004744, Cm003262: Move functions to banked area.
// 
//    Rev 1.0   Apr 09 2009 10:20:20   adzhelp
// Initial revision.
//******************************************************************************
#endif

//------------------------------------------------------------------------------
// Body Identification
//------------------------------------------------------------------------------
#define ldb_spd   "ldb_spd"

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------
#include "ldb_int.h"
#include "ldb_reg.h"
#include "ldb_spd.h"

//------------------------------------------------------------------------------
// Local constants
//------------------------------------------------------------------------------
// Registers initializers
#define cRegisterTCL51Init  (U8)0x00U // TI51 pin falling edge
#define cRegisterTMC51Init  (U8)0x00U // Counter stopped, output disabled

#define cMaxCounterValue    (U8)0xFFU

// External interrupt for engine RPM measurement
#define cExtInterruptId     INTP6
#define cExtInterruptNum    6
// Threshold number of signal transitions on ENGINE_RPM input
#define cThresholdNumberEngineRunning   6U // corresponds to 6 periods
                                           // when f >= 6.7Hz (T <= 149 ms)
                                           // and reading period is 960 ms

//------------------------------------------------------------------------------
// Local macros
//------------------------------------------------------------------------------
// Vehicle Speed
#define mConfigureVehicleSpeedCounter() \
    /* Timer Clock Selection */ \
    mLDBRegWrite8BitRegister(TCL51, cRegisterTCL51Init); \
    /* Timer Mode Control */ \
    mLDBRegWrite8BitRegister(TMC51, cRegisterTMC51Init); \
    /* Compare register */ \
    mLDBRegWrite8BitRegister(CR51, cMaxCounterValue)

#define mStartVehicleSpeedCounter() \
    mClearVehicleSpeedCounterFlag(); \
    mLDBRegWrite1BitInRegister(TMC51, 7, 1)
#define mStopVehicleSpeedCounter()      mLDBRegWrite1BitInRegister(TMC51, 7, 0)
#define mGetVehicleSpeedCounter()       mLDBRegRead8BitRegister(TM51)
#define mIsVehicleSpeedCounterOverrun() (mLDBIntGetIsrRequestFlag(INTTM51) != 0)
#define mClearVehicleSpeedCounterFlag() mLDBIntClearIsrRequestFlag(INTTM51)

// Engine RPM
#define mConfigureEngineRpmDetection()

#define mStartEngineRpmDetection() \
{ \
    /* Enable external interrupt edge detection: both edges */ \
    mLDBRegWrite1BitInRegister(EGP, cExtInterruptNum, 1); \
    mLDBRegWrite1BitInRegister(EGN, cExtInterruptNum, 1); \
    mRestartEngineRpmDetection(); \
}

#define mRestartEngineRpmDetection() \
{ \
    u8RpmSignalRisingCounter = 0; \
    u8RpmSignalFallingCounter = 0; \
    mLDBIntClearIsrRequestFlag(cExtInterruptId); \
    mLDBIntEnableIsr(cExtInterruptId); \
}

#define mStopEngineRpmDeteciton() \
{ \
    mLDBIntDisableIsr(cExtInterruptId); \
    mLDBRegWrite1BitInRegister(EGP, cExtInterruptNum, 0); \
    mLDBRegWrite1BitInRegister(EGN, cExtInterruptNum, 0); \
}

#define mIsEngineRunning() \
    ((u8RpmSignalFallingCounter >= (U8)(cThresholdNumberEngineRunning + 1U)) || \
     (u8RpmSignalRisingCounter >= (U8)(cThresholdNumberEngineRunning + 1U)))

//------------------------------------------------------------------------------
// Local types
//------------------------------------------------------------------------------

// This is an example:
// typedef Expression   tTypeName;

//------------------------------------------------------------------------------
// Local data
//------------------------------------------------------------------------------
static U8 u8RpmSignalFallingCounter;
static U8 u8RpmSignalRisingCounter;

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

// This is an example:
// static tType CmpFunctionName( tTypeArgument1 ArgumentName1, ... );

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
// This is an example:
// static tType CmpFunctionName( tTypeArgument1 ArgumentName1, ... )
// {
//      ... body
// }

//==============================================================================
//=========================== EXPORTED FUNCTIONS ===============================
//==============================================================================

//==============================================================================
// DESCRIPTION:         Initialization of SPD channel
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
void LDBSpdInit(void)
{
    mConfigureVehicleSpeedCounter();
    mConfigureEngineRpmDetection();
}

//==============================================================================
// DESCRIPTION:         LDB receive with address of SPD channel
//
// PARAMETERS:          const tAddress Address - address of parameter to read:
//                          either speed of engine state
//                      tMsg* const pMsg - pointer to data message  
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
MEM_TYPE void LDBSpdReceiveWithAddr(const tAddress Address, tMsg* const pMsg)
{
    if (pMsg != NULL)
    {
        mLIBassert(pMsg->Lng == cLDBSpdMessageLength);
        if (Address == cLDBSpdAddrVehicleSpeed)
        {
            // called on period 720 ms
            if (mIsVehicleSpeedCounterOverrun())
            {
                pMsg->pBuffer[cLDBSpdVehicleSpeedIndex] = cMaxCounterValue;
            }
            else
            {
                pMsg->pBuffer[cLDBSpdVehicleSpeedIndex] = mGetVehicleSpeedCounter();
                mStopVehicleSpeedCounter();
            }
            mStartVehicleSpeedCounter();
        }
        else if (Address == cLDBSpdAddrEngineRpm)
        {
            // called on period 960 ms
            mLDBIntDisableIsr(cExtInterruptId); // protect shared counters from interrupt access
            pMsg->pBuffer[cLDBSpdEngineRpmIndex] = 
                (mIsEngineRunning() ? cLDBSpdEngineRunning : cLDBSpdEngineNotRunning);
            mRestartEngineRpmDetection();
        }
        else
        {
            mLIBassert(cFalse);
        }
    }
    else
    {
        mLIBassert(cFalse);
    }
}

//==============================================================================
// DESCRIPTION:         LDB control of SPD channel
//
// PARAMETERS:          const tCtrl Ctrl - Control type
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
MEM_TYPE void LDBSpdControl(const tCtrl Ctrl)
{
    switch (Ctrl)
    {
    case cLDBSpdControlStart:
        mStartVehicleSpeedCounter();
        mStartEngineRpmDetection();
        break;
    case cLDBSpdControlStop:
        mStopVehicleSpeedCounter();
        mStopEngineRpmDeteciton();
        break;
    default:
        mLIBassert(cFalse);
    }
}

//==============================================================================
// DESCRIPTION:         External interrupt service routine
//
// PARAMETERS:          N/A
//
// RETURN VALUE:        N/A
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
mLDBIntDeclareIsr(cExtInterruptId)
{
    mLDBIntEnterIsr(cExtInterruptId);

    if (mLDBHarRead(cLDBHarEngineRpmInput) == 0)
    {
        u8RpmSignalFallingCounter++;
    }
    else
    {
        u8RpmSignalRisingCounter++;
    }

    if ((u8RpmSignalFallingCounter >= (U8)(cThresholdNumberEngineRunning + 1U)) ||
        (u8RpmSignalRisingCounter >= (U8)(cThresholdNumberEngineRunning + 1U))   )
    {
        // external interrupt protection: engine is running
        mLDBIntDisableIsr(cExtInterruptId);
    }
    mLDBIntLeaveIsr(cExtInterruptId);
}
