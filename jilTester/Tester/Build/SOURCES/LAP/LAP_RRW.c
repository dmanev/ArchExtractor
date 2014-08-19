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
// Component:    LAP_RRW - Controls the rear wiper.             
// -----------------------------------------------------------------------------
// $Date:   Mar 22 2010 14:23:06  $
// $Archive::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_RRW/LAP_RRW.c-arc  $
// $Revision:   1.18  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_RRW/LAP_RRW.c-arc  $
// 
//    Rev 1.18   Mar 22 2010 14:23:06   amanevd
// Cm006814: HWP - Code review corrections
// 
//    Rev 1.17   Mar 19 2010 10:04:16   adzhelp
// Cm006814: Code review corrections
// 
//    Rev 1.16   Mar 02 2010 10:39:52   adzhelp
// Cm006814: TPS_ARRET, TPS_MAX_COUPLBLOC, TPS_REPRISE, TPS,ESSUIE_MINI, PROLONG_APPUI_ARR normalized
// 
//    Rev 1.15   Feb 18 2010 15:15:02   adzhelp
// Cm006593: Activation on washer switch rising edge.
// 
//    Rev 1.14   Feb 17 2010 17:36:18   adzhelp
// Cm007550: IGN ON condition filtration for 500 ms
// 
//    Rev 1.13   Feb 10 2010 16:47:58   amanevd
// Cm007075: Volatile Faults and Deprotection cleared at IGN ON
// 
//    Rev 1.12   Jan 29 2010 11:52:02   amanevd
// Cm007267: Permanent protection applied if SCLimit reached
// 
//    Rev 1.11   Jan 29 2010 11:31:16   amanevd
// Cm007267: cSClimit replaced with EEP_SCLimit
// 
//    Rev 1.10   Jan 07 2010 15:55:28   amanevd
// Cm005566: Stop position fault memorised is never deleted from component
// 
//    Rev 1.9   Dec 16 2009 14:54:34   amanevd
// Cm005566: External Lights Buzzer signal removed
// 
//    Rev 1.8   Dec 14 2009 11:02:18   amanevd
// Cm005566: Full Hardware Protection
// 
//    Rev 1.7   Nov 30 2009 13:17:04   amarinm1
// Cm006742: Configuration parameters are now calculated only when needed.
// 
//    Rev 1.6   Nov 06 2009 15:08:56   amarinm1
// Cm006421: Initial parking was implemented.
// 
//    Rev 1.6   Nov 06 2009 11:39:00   amarinm1
// Cm006421: Initial parking was implemented.
// 
//    Rev 1.5   Nov 04 2009 16:16:40   adzhelp
// Cm005566: Implementation of HW Protection
// 
//    Rev 1.4   Nov 04 2009 16:01:28   adzhelp
// Cm006576: FRW, RRW: Front and Rear wiper request should not be taken into account at the same time.
// 
//    Rev 1.3   Oct 09 2009 16:05:18   amarinm1
// Cm006451: Signal RearWiperStopIsAllowed_LAP_RRW is now read in LAPRrwINTStartWiping() in order to clear it.
// 
//    Rev 1.3   Oct 09 2009 15:24:20   amarinm1
// Cm006451: Signal RearWiperStopIsAllowed_LAP_RRW is now read in LAPRrwINTStartWiping() in order to clear it.
// 
//    Rev 1.2   Sep 24 2009 10:15:28   adzhelp
// Cm003262: EEP_EVAR_PRESENT renamed to EEP_EV_ARR
// 
//    Rev 1.1   Sep 15 2009 11:52:40   amarinm1
// Cm003262: Component was fully implemented.
// 
//    Rev 1.0   Sep 04 2009 16:55:22   amarinm1
// Initial revision.
// 
//******************************************************************************
#endif

//------------------------------------------------------------------------------
// Body Identification
//------------------------------------------------------------------------------
#define lap_rrw  "lap_rrw"


//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------
#include "tos.h"
#include "dat.h"
#include "lib.h"
#include "LAP_RRW.h"
#include "LAP_RRW.hgr"


//------------------------------------------------------------------------------
// Local constants
//------------------------------------------------------------------------------
#define cDisableWiping               cFalse
#define cEnableWiping                cTrue

#define cMotorOff                    (0)
#define cMotorOn                     (1)

// EEP parameter steps
#define cMsInASecond                 ((U32)1000)
#define cTPS_CAD_FIXE_step           ((U16)80)
#define cTPS_ESSUIE_MINI_step        ((U16)12)
#define cWashWaitInMs                ((U32)750)

// Initial parking states
#define cNotDefined                  ((U8)0)
#define cWiperInSpeedPosition        ((U8)1)
#define cStopPositionHasBeenReached  ((U8)2)

#define cIgnitionOnTimeoutMs         (500UL)
#define cIgnitionOnTimeoutTicks      (mTOSConvMsInTimerTick(cIgnitionOnTimeoutMs) - (tTOSTimer)1)

// HW Protection
#define cProtectionHeatCountInitial ((U8)20U)
#define cFaultCountProtectThreshold ((U8)10U)

//------------------------------------------------------------------------------
// Local macros
//------------------------------------------------------------------------------
#define mConvSecInTimerTick(delay)   (mTOSConvMsInTimerTick( ( cMsInASecond * (delay) ) ))



//------------------------------
#define mReadDisableTimeout() \
    ( DATCmnFrRrwDisableTimeout = (u8DATCmnTPS_ARRET_old == mDATRead(U8Bit, NEEP_TPS_ARRET, Default)) ? \
    /* //QACJ 3443: amarinm1: There is no recursion - second macro is formed through concatenation. */ \
    DATCmnFrRrwDisableTimeout : mCalcDisableTimeout() )

#define mCalcDisableTimeout() \
    /* //QACJ 3443: amarinm1: There is no recursion - second macro is formed through concatenation. */ \
    (tTOSTimer)(mConvSecInTimerTick( (U32)(u8DATCmnTPS_ARRET_old = mDATRead(U8Bit, NEEP_TPS_ARRET, Default)) ))



//------------------------------
#define mReadWipingTimeout() \
    ( DATCmnFrRrwWipingTimeout = (u8DATCmnTPS_MAX_COUPLBLOC_old == mDATRead(U8Bit, NEEP_TPS_MAX_COUPLBLOC, Default)) ? \
    /* //QACJ 3443: amarinm1: There is no recursion - second macro is formed through concatenation. */ \
    DATCmnFrRrwWipingTimeout : mCalcWipingTimeout() )

#define mCalcWipingTimeout() \
    /* //QACJ 3443: amarinm1: There is no recursion - second macro is formed through concatenation. */ \
    (tTOSTimer)(mConvSecInTimerTick( (U32)(u8DATCmnTPS_MAX_COUPLBLOC_old = mDATRead(U8Bit, NEEP_TPS_MAX_COUPLBLOC, Default)) ))



//------------------------------
#define mReadWipingTimeoutReprise() \
    ( DATCmnRrwWipingTimeoutReprise = (u8DATCmnTPS_REPRISE_old == mDATRead(U8Bit, NEEP_TPS_REPRISE, Default)) ? \
    /* //QACJ 3443: amarinm1: There is no recursion - second macro is formed through concatenation. */ \
    DATCmnRrwWipingTimeoutReprise : mCalcWipingTimeoutReprise() )
        
#define mCalcWipingTimeoutReprise() \
    /* //QACJ 3443: amarinm1: There is no recursion - second macro is formed through concatenation. */ \
    (tTOSTimer)(mConvSecInTimerTick( (U32)(u8DATCmnTPS_REPRISE_old = mDATRead(U8Bit, NEEP_TPS_REPRISE, Default)) ))



//------------------------------
#define mReadIntermittentPause() \
    ( DATCmnFrRrwIntermittentPause = (u8DATCmnTPS_CAD_FIXE_old == mDATRead(U8Bit, EEP_TPS_CAD_FIXE, Default)) ? \
    /* //QACJ 3443: amarinm1: There is no recursion - second macro is formed through concatenation. */ \
    DATCmnFrRrwIntermittentPause : mCalcIntermittentPause() )

#define mCalcIntermittentPause() \
    /* //QACJ 3443: amarinm1: There is no recursion - second macro is formed through concatenation. */ \
    (tTOSTimer)(mTOSConvMsInTimerTick( (U32)( cTPS_CAD_FIXE_step * (u8DATCmnTPS_CAD_FIXE_old = mDATRead(U8Bit, EEP_TPS_CAD_FIXE, Default)) ) ) - (tTOSTimer)1U)



//------------------------------
#define mReadMinimumWipingTime() \
    ( DATCmnFrRrwMinimumWipingTime = (u8DATCmnTPS_ESSUIE_MINI_old == mDATRead(U8Bit, NEEP_TPS_ESSUIE_MINI, Default)) ? \
    /* //QACJ 3443: amarinm1: There is no recursion - second macro is formed through concatenation. */ \
    DATCmnFrRrwMinimumWipingTime : mCalcMinimumWipingTime() )

#define mCalcMinimumWipingTime() \
    /* //QACJ 3443: amarinm1: There is no recursion - second macro is formed through concatenation. */ \
    (tTOSTimer)(mTOSConvMsInTimerTick( (U32)( cTPS_ESSUIE_MINI_step * (u8DATCmnTPS_ESSUIE_MINI_old = mDATRead(U8Bit, NEEP_TPS_ESSUIE_MINI, Default)) ) ) - (tTOSTimer)1U)



//------------------------------
#define mReadWashWait() \
    (tTOSTimer)(mTOSConvMsInTimerTick( (U32)cWashWaitInMs ))


//------------------------------------------------------------------------------
// Local types
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Local data
//------------------------------------------------------------------------------
static tTOSTimer    TempoEP;
static tTOSTimer    TempoINT;
static tTOSTimer    TimerWashWait;
static tTOSTimer    IgnitionOnTimer;

static U8           u8ExtraWipeCounter;
static U8           u8InitialParkingState;

static BOOL         bProtectionOutput;
static BOOL         bParkingOutput;
static BOOL         bOutputINTOn;
static BOOL         bOutputWSHOn;
static BOOL         bMotorCommand;
static BOOL         bComponentIsEnabled;

// HWP
static BOOL         bPWR_IGNOld;
static U8           u8ProtectionCounter;
static U8           u8FaultCounter;

//------------------------------------------------------------------------------
// Constant local data
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Constant exported data
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Local function prototypes
//------------------------------------------------------------------------------
static MEM_TYPE void StopRearWiper( void );
static MEM_TYPE void RearWiperArbitration( void );
static MEM_TYPE void DisableFunctionallity( void );
static MEM_TYPE void ResumeAfterDisable( void );
static MEM_TYPE void HWProtection( void );

#ifdef X90_PROJECT
static MEM_TYPE void LAPRrwStopProtectionMode_Static(void);
static MEM_TYPE BOOL LAPRrwINTConditionsToStopArePresent_Static(void);
static MEM_TYPE void LAPRrwInitWashProlongation_Static(void);
static MEM_TYPE void LAPRrwArbitration_Static(void);
static MEM_TYPE void LAPRrwEnterActiveState_Static(void);
#endif

//==============================================================================
//=========================== LOCAL FUNCTIONS ==================================
//==============================================================================


//==============================================================================
// DESCRIPTION:         Rear Wiper Arbitration
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
static MEM_TYPE void RearWiperArbitration( void )
{
    if (bProtectionOutput == cDisableWiping)
    {
        // Motor Protection is active => the motor must be stopped immediatly
        bMotorCommand = cMotorOff;
    }
    else
    {
        if (   (bOutputWSHOn   == cTrue)
            || (bOutputINTOn   == cTrue)
            || (bParkingOutput == cTrue)   )
        {
            // Washing or INT request or protection graph is trying to release the blocked wiper
            bMotorCommand = cMotorOn;
        }
        else
        {
            bMotorCommand = cMotorOff;
        }
    }

    mDATWrite(U1Bit, RR_WIPER_RR_FOG_LAMP, bMotorCommand, Default);
}


//==============================================================================
// DESCRIPTION:         Stop rear wiper
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
static MEM_TYPE void StopRearWiper( void )
{
    TOSSeqDeactivateGraph(cTOSSeqGraphIdLAPRrwInitialParking);
    TOSSeqDeactivateGraph(cTOSSeqGraphIdLAPRrwEngineProtection);
    TOSSeqDeactivateGraph(cTOSSeqGraphIdLAPRrwIntermittentWipe);
    TOSSeqDeactivateGraph(cTOSSeqGraphIdLAPRrwWashing);

    bProtectionOutput     = cEnableWiping;
    bParkingOutput        = cFalse;
    bOutputINTOn          = cFalse;
    bOutputWSHOn          = cFalse;
    u8ExtraWipeCounter    = 0;

    TOSStopTimer( &TempoEP );
    TOSStopTimer( &TempoINT );
    TOSStopTimer( &TimerWashWait );
}


//==============================================================================
// DESCRIPTION :  Stop rear wiper, disable output
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : Refer to DCD
//==============================================================================
static MEM_TYPE void DisableFunctionallity(void)
{
    StopRearWiper();
    mDATWrite(U1Bit, RR_WIPER_RR_FOG_LAMP, cMotorOff, Default);  

    bComponentIsEnabled = cFalse;
}


//==============================================================================
// DESCRIPTION :  Resume component after it has been disabled
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : Refer to DCD
//==============================================================================
static MEM_TYPE void ResumeAfterDisable(void)
{
    TOSSeqActivateGraph(cTOSSeqGraphIdLAPRrwInitialParking);
    TOSSeqActivateGraph(cTOSSeqGraphIdLAPRrwEngineProtection);
    TOSSeqActivateGraph(cTOSSeqGraphIdLAPRrwIntermittentWipe);
    TOSSeqActivateGraph(cTOSSeqGraphIdLAPRrwWashing);

    bComponentIsEnabled = cTrue;

    mDATWrite(U1Bit, RearWasherButtonBlocked, 
              (mDATRead(U1Bit, RR_WASHER_SW, Default) != cFalse), Default);
}

//==============================================================================
// DESCRIPTION :  Hardware protection routine
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : Refer to DCD
//==============================================================================
static MEM_TYPE void HWProtection( void )
{
    U16 u16TempL;

    // Manage inrush current timeout after output activation
    if (mDATRead(U1Bit, RR_WIPER_RR_FOG_LAMP, Immediate) != cFalse)
    {
        if (u8ProtectionCounter > 0)
        {
            u8ProtectionCounter--;            
        }
    }
    else
    {
        u8ProtectionCounter = cProtectionHeatCountInitial;
    }

    // Deprotection on rising edge of PWR_IGN
    if(     (cFalse != mDATRead(U1Bit, PWR_IGN, Default))
        &&  (cFalse == bPWR_IGNOld)
      )
    {
        if(mDATRead(U16Bit, EEP_SCLimit, Default) > mDATRead(U16Bit, EEP_CDRearWiper, Default))
        {
            mDATWrite(U1Bit, RR_WIPER_RR_FOG_LAMPProtection, 0, Default);            
            mDATWrite(U1Bit, DefRrwCC, 0, Default);
        }
        u8FaultCounter = 0;
    }

    // Protection applied if SCLimit is reached
    if(mDATRead(U16Bit, EEP_SCLimit, Default) <= mDATRead(U16Bit, EEP_CDRearWiper, Default))
    {
        mDATWrite(U1Bit, RR_WIPER_RR_FOG_LAMPProtection, 1, Default);
    }

    // SC GND detection management
    if (1 == mDATRead(U1Bit, RR_WIPER_RR_FOG_LAMP, Immediate))
    {
        // Inrush current timeout has elapsed
        if (u8ProtectionCounter == 0)
        {
            if (mDATRead(U1Bit, DIAG_DRIVER_HIGH_SIDE_SCGnd, Default) != cFalse)
            {
                u8FaultCounter++;
                if(u8FaultCounter >= cFaultCountProtectThreshold)
                {
                    mDATWrite(U1Bit, DefRrwCC, 1, Default);
                    mDATWrite(U1Bit, RR_WIPER_RR_FOG_LAMPProtection, 1, Default);
                    mDATWrite(U1Bit, EEP_DefRrwCC, 1, Default);

                    u16TempL = mDATRead(U16Bit, EEP_CDRearWiper, Default);
                    if(u16TempL < mDATRead(U16Bit, EEP_SCLimit, Default))
                    {
                        u16TempL ++;
                        mDATWrite(U16Bit, EEP_CDRearWiper, u16TempL, Default);
                    }
                }
            }
            else
            {
                mDATWrite(U1Bit, DefRrwCC, 0, Default);
                u8FaultCounter = 0;
            }
        }
    }

    bPWR_IGNOld = mDATRead(U1Bit, PWR_IGN, Default);
}

//==============================================================================
//=========================== EXPORTED FUNCTIONS ===============================
//==============================================================================

//---------------------------------------------------------------------------
//                      Functions used in several graphs
//---------------------------------------------------------------------------


//==============================================================================
// DESCRIPTION:         Monitors for stop position detected
//
// PARAMETERS:          None
//
// RETURN VALUE:        BOOL: cTrue if stop position is detected
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
BOOL LAPRrwEPStopPositionIsDetected( void )
{
    const BOOL bReturnValueL = TOSReadSignal(cTOSSignalRearStopPositionDetected_LAP_RRW1);
  
    return bReturnValueL;
}


//==============================================================================
// DESCRIPTION:         Monitors for stop position detected (for washing)
//
// PARAMETERS:          None
//
// RETURN VALUE:        BOOL: cTrue if stop position is detected
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
BOOL LAPRrwWashStopPositionIsDetected( void )
{
    const BOOL bReturnValueL = TOSReadSignal(cTOSSignalRearStopPositionDetected_LAP_RRW2);
  
    return bReturnValueL;
}


//---------------------------------------------------------------------------
//                      RRWEngineProtection Graph Functions
//---------------------------------------------------------------------------
//==============================================================================
// DESCRIPTION:         Checks if output is inactive
//
// PARAMETERS:          None
//
// RETURN VALUE:        BOOL: cTrue if rear wiper output is inactive
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
BOOL LAPRrwOutputIsInactive( void )
{
    const BOOL bReturnValueL = (mDATRead(U1Bit, RR_WIPER_RR_FOG_LAMP, Default) == 0);
  
    return bReturnValueL;
}


//==============================================================================
// DESCRIPTION:         Checks if output is active
//
// PARAMETERS:          None
//
// RETURN VALUE:        BOOL: cTrue if rear wiper output is active
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
BOOL LAPRrwOutputIsActive( void )
{
    const BOOL bReturnValueL = (mDATRead(U1Bit, RR_WIPER_RR_FOG_LAMP, Default) == 1);
  
    return bReturnValueL;
}


//==============================================================================
// DESCRIPTION:         Checks if initial wiping timeout has elapsed
//
// PARAMETERS:          None
//
// RETURN VALUE:        BOOL: cTrue if timeout elapsed
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
BOOL LAPRrwInitialWipingTimeoutHasElapsed( void )
{
#ifdef X90_PROJECT
    static MEM_TYPE BOOL LAPRrwInitialWipingTimeoutHasElapsed_Static(void);
    return LAPRrwInitialWipingTimeoutHasElapsed_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL LAPRrwInitialWipingTimeoutHasElapsed_Static(void)
{
#endif  
    tTOSTimer TempoL;
    BOOL bReturnValueL;

    //QACJ 3226: amarinm1: This is intentional and is checked for problems.
    TempoL = mReadMinimumWipingTime() + mReadWipingTimeout();
    bReturnValueL = TOSIsTempoElapsed( &TempoEP, TempoL );

    return bReturnValueL;
}


//==============================================================================
// DESCRIPTION:         Enable wiping
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
void LAPRrwEnableWiping( void )
{
    bProtectionOutput = cEnableWiping;

    if (u8InitialParkingState < cStopPositionHasBeenReached)
    {
        u8InitialParkingState++;
    }

    // Clear front fixed stop fault
    mDATWrite(U1Bit, DefAFAR,     cFalse, Default);                             

    TOSStartTimer( &TempoEP );
}


//==============================================================================
// DESCRIPTION:         Try wiping
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
void LAPRrwTryWiping( void )
{
    bProtectionOutput = cEnableWiping;
    TOSStartTimer( &TempoEP );
}


//==============================================================================
// DESCRIPTION:         Disable wiping
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
void LAPRrwDisableWiping( void )
{
    bProtectionOutput = cDisableWiping;

    // Declare front fixed stop fault
    mDATWrite(U1Bit, DefAFAR,     cTrue, Default);                              
    mDATWrite(U1Bit, EEP_DefAfar, cTrue, Immediate);
    
    TOSStartTimer( &TempoEP );
}


//==============================================================================
// DESCRIPTION:         Check if disable timeout is elapsed
//
// PARAMETERS:          None
//
// RETURN VALUE:        BOOL: cTrue if timeout elapsed
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
BOOL LAPRrwDisableTimeoutHasElapsed( void )
{
#ifdef X90_PROJECT
    static MEM_TYPE BOOL LAPRrwDisableTimeoutHasElapsed_Static(void);
    return LAPRrwDisableTimeoutHasElapsed_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL LAPRrwDisableTimeoutHasElapsed_Static(void)
{
#endif  
    tTOSTimer DisableTimeoutL;
    BOOL bReturnValueL;

    //QACJ 3226: amarinm1: This is intentional and is checked for problems.
    DisableTimeoutL = mReadDisableTimeout();
    bReturnValueL   = TOSIsTempoElapsed( &TempoEP, DisableTimeoutL );
  
    return bReturnValueL;
}


//==============================================================================
// DESCRIPTION:         Check if wiping timeout is elapsed
//
// PARAMETERS:          None
//
// RETURN VALUE:        BOOL: cTrue if timeout elapsed
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
BOOL LAPRrwWipingTimeoutHasElapsed( void )
{
#ifdef X90_PROJECT
    static MEM_TYPE BOOL LAPRrwWipingTimeoutHasElapsed_Static(void);
    return LAPRrwWipingTimeoutHasElapsed_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL LAPRrwWipingTimeoutHasElapsed_Static(void)
{
#endif  
    tTOSTimer WipingTimeoutL;
    BOOL bReturnValueL;

    //QACJ 3226: amarinm1: This is intentional and is checked for problems.
    WipingTimeoutL = mReadWipingTimeoutReprise();
    bReturnValueL  = TOSIsTempoElapsed( &TempoEP, WipingTimeoutL );

    return bReturnValueL;
}


//==============================================================================
// DESCRIPTION:         Check if stop wiping timeout is elapsed
//
// PARAMETERS:          None
//
// RETURN VALUE:        BOOL: cTrue if timeout elapsed
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
BOOL LAPRrwStopTryingTimeoutHasElapsed( void )
{
#ifdef X90_PROJECT
    static MEM_TYPE BOOL LAPRrwStopTryingTimeoutHasElapsed_Static(void);
    return LAPRrwStopTryingTimeoutHasElapsed_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL LAPRrwStopTryingTimeoutHasElapsed_Static(void)
{
#endif  
    tTOSTimer WipingTimeoutL;
    BOOL bReturnValueL;

    //QACJ 3226: amarinm1: This is intentional and is checked for problems.
    WipingTimeoutL = mReadWipingTimeout();
    bReturnValueL  = TOSIsTempoElapsed( &TempoEP, WipingTimeoutL );

    return bReturnValueL;
}


//==============================================================================
// DESCRIPTION:         Check if wiping is not requested
//
// PARAMETERS:          None
//
// RETURN VALUE:        BOOL: cTrue if wiping not requested
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
BOOL LAPRrwWipingIsNotRequested( void )
{
    const BOOL bReturnValueL = (   (bParkingOutput == cFalse)
                                && (mDATRead(U1Bit, RR_WASHER_SW, Default)    == 0)
                                && (mDATRead(U1Bit, RR_WIPER_INT_SW, Default) == 0)  );
  
    return bReturnValueL;
}


//==============================================================================
// DESCRIPTION:         Stop protection mode
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
void LAPRrwStopProtectionMode( void )
{
#ifdef X90_PROJECT
    LAPRrwStopProtectionMode_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPRrwStopProtectionMode_Static(void)
{
#endif    
    // Reset flag
    bProtectionOutput = cEnableWiping;

    // Clear front fixed stop fault
    mDATWrite(U1Bit, DefAFAR,     cFalse, Default);                             

    // Clear Output
    mDATWrite(U1Bit, RR_WIPER_RR_FOG_LAMP, cMotorOff, Default);

    // Restart the command graphs
    TOSSeqDeactivateGraph(cTOSSeqGraphIdLAPRrwIntermittentWipe);
    TOSSeqDeactivateGraph(cTOSSeqGraphIdLAPRrwWashing);

    bOutputWSHOn = cFalse;
    bOutputINTOn = cFalse;
    u8ExtraWipeCounter = 0;

    TOSSeqActivateGraph(cTOSSeqGraphIdLAPRrwIntermittentWipe);
    TOSSeqActivateGraph(cTOSSeqGraphIdLAPRrwWashing);
}


//---------------------------------------------------------------------------
//                      RRWIntermittentWipe Graph Functions
//---------------------------------------------------------------------------

//See Definition of the functions used in several graphs.
//==============================================================================
// DESCRIPTION:         Check if intermittent conditions to stop are present
//
// PARAMETERS:          None
//
// RETURN VALUE:        BOOL: cTrue if stop conditions present
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
BOOL LAPRrwINTConditionsToStopArePresent( void )
{
#ifdef X90_PROJECT
    return LAPRrwINTConditionsToStopArePresent_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL LAPRrwINTConditionsToStopArePresent_Static(void)
{
#endif    
    tTOSTimer  MinimumWipingTimeL;
    BOOL       bReturnValueL;
    BOOL       bFrontWiperStopIsAllowedL;

    if ( bOutputWSHOn == cTrue )
    {
        bReturnValueL = cTrue;
    }
    else
    {
        //QACJ 3226: amarinm1: This is intentional and is checked for problems.
        MinimumWipingTimeL = mReadMinimumWipingTime();
        bReturnValueL = TOSIsTempoElapsed( &TempoINT, MinimumWipingTimeL );

        bFrontWiperStopIsAllowedL = 
            TOSReadSignal(cTOSSignalRearWiperStopIsAllowed_LAP_RRW);
        bReturnValueL &= bFrontWiperStopIsAllowedL;
    }

    return bReturnValueL;
}


//==============================================================================
// DESCRIPTION:         Check if intermittent request is off
//
// PARAMETERS:          None
//
// RETURN VALUE:        BOOL: cTrue if request is off
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
BOOL LAPRrwINTRequestIsOff( void )
{
    const BOOL bReturnValueL = (mDATRead(U1Bit, RR_WIPER_INT_SW, Default) == 0);
    
    return bReturnValueL;
}


//==============================================================================
// DESCRIPTION:         Check if intermittent request is on
//
// PARAMETERS:          None
//
// RETURN VALUE:        BOOL: cTrue if request is on
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
BOOL LAPRrwINTRequestIsOn( void )
{
    const BOOL bReturnValue = (mDATRead(U1Bit, RR_WIPER_INT_SW, Default) == 1);
 
    return bReturnValue;
}


//==============================================================================
// DESCRIPTION:         Intermittent mode: stop wiping
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
void LAPRrwINTStopWiping( void )
{
    if ( bOutputWSHOn == cTrue )
    {
        bOutputINTOn = cFalse;
        TOSSeqFreezeGraph(cTOSSeqGraphIdLAPRrwIntermittentWipe);
    }
    else
    {
        bOutputINTOn = cFalse;
        TOSStartTimer( &TempoINT );
    }
}


//==============================================================================
// DESCRIPTION:         Check if intermittent pause has elapsed
//
// PARAMETERS:          None
//
// RETURN VALUE:        BOOL: cTrue if elapsed
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
BOOL LAPRrwINTPauseHasElapsed( void )
{
#ifdef X90_PROJECT
    static MEM_TYPE BOOL LAPRrwINTPauseHasElapsed_Static(void);
    return LAPRrwINTPauseHasElapsed_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL LAPRrwINTPauseHasElapsed_Static(void)
{
#endif  
    tTOSTimer IntermittentPauseL;
    BOOL bReturnValueL;

    //QACJ 3226: amarinm1: This is intentional and is checked for problems.
    IntermittentPauseL = mReadIntermittentPause();
    bReturnValueL = TOSIsTempoElapsed( &TempoINT, IntermittentPauseL );

    return bReturnValueL;
}


//==============================================================================
// DESCRIPTION:         Intermittent mode: start wiping
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
void LAPRrwINTStartWiping( void )
{
    bOutputINTOn = cTrue;
    TOSStartTimer( &TempoINT );
    
    // Stop initial parking at first wiping request
    bParkingOutput = cFalse;
    TOSSeqDeactivateGraph(cTOSSeqGraphIdLAPRrwInitialParking);

    //QACJ 3200: amarinm1: This is done just to clear the signal.
    TOSReadSignal(cTOSSignalRearWiperStopIsAllowed_LAP_RRW);
}


//==============================================================================
// DESCRIPTION:         Intermittent mode: stop timer
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
void LAPRrwINTStopTimer( void )
{
    TOSStopTimer( &TempoINT );
}


//---------------------------------------------------------------------------
//                      RRWWashing Graph Functions
//---------------------------------------------------------------------------

//==============================================================================
// DESCRIPTION:         Check if wash cycle is finished
//
// PARAMETERS:          None
//
// RETURN VALUE:        BOOL: cTrue if finished
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
BOOL LAPRrwWashCycleIsFinished( void )
{
    const BOOL bReturnValueL = (u8ExtraWipeCounter == 0);
 
    return bReturnValueL;
}


//==============================================================================
// DESCRIPTION:         Check if extra wipe beginning is requested
//
// PARAMETERS:          None
//
// RETURN VALUE:        BOOL: cTrue if requested
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
BOOL LAPRrwWashExtraWipeBegining( void )
{
    const BOOL bRR_AUTOSTOP_SW_FallingEdgeIsDetectedL = 
        TOSReadSignal(cTOSSignalRR_AUTOSTOP_SWFalling_LAP_RRW);
    const BOOL bReturnValueL = 
              (   (u8ExtraWipeCounter > 0)
               && (bRR_AUTOSTOP_SW_FallingEdgeIsDetectedL == 1) );
  
    return bReturnValueL;
}


//==============================================================================
// DESCRIPTION:         Wash prolongation
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
void LAPRrwWashProlongation( void )
{
    u8ExtraWipeCounter--;
}


//==============================================================================
// DESCRIPTION:         Prepare to stop wash prolongation
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
void LAPRrwPrepareToStopWashProlongation( void )
{
    //QACJ 3200: amarinm1: This is done just to clear the signal.
    TOSReadSignal(cTOSSignalRearStopPositionDetected_LAP_RRW2);
}


//==============================================================================
// DESCRIPTION:         Check if wash request is off
//
// PARAMETERS:          None
//
// RETURN VALUE:        BOOL: cTrue if not requested
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
BOOL LAPRrwWashRequestIsOff( void )
{
    const BOOL bReturnValueL = (mDATRead(U1Bit, RR_WASHER_SW, Default) == 0);
 
    return bReturnValueL;
}


//==============================================================================
// DESCRIPTION:         Check if wash request is on
//
// PARAMETERS:          None
//
// RETURN VALUE:        BOOL: cTrue if requested
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
BOOL LAPRrwWashRequestIsOn( void )
{
    BOOL bReturnValueL = cFalse;

    if (mDATRead(U1Bit, RearWasherButtonBlocked, Default) != cFalse)
    {
        // button pressed before ignition on
        // ignore button
        if (mDATRead(U1Bit, RR_WASHER_SW, Default) == cFalse)
        {
            mDATWrite(U1Bit, RearWasherButtonBlocked, cFalse, Default);
        }
        else
        {
            // wait for button release
        }
    }
    else
    {
        if (mDATRead(U1Bit, FrontWasherButtonBlocked, Default) == cFalse)
        {
            bReturnValueL = (   (mDATRead(U1Bit, RR_WASHER_SW, Default) == 1)
                             && (mDATRead(U1Bit, FR_WASHER_SW, Default) == 0)   );
        }
        else
        {
            // front washer button blocked, disregard it
            bReturnValueL = (mDATRead(U1Bit, RR_WASHER_SW, Default) == 1);
        }
    }
    
    return bReturnValueL;
}


//==============================================================================
// DESCRIPTION:         Stop wash wiping
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
void LAPRrwStopWashWiping( void )
{
    const tTOSSeqGraphStateType INTGraphStateL = 
        TOSSeqGraphState(cTOSSeqGraphIdLAPRrwIntermittentWipe);

    bOutputWSHOn = cFalse;

    if ( INTGraphStateL == cTOSSeqFrozenGraph ) 
    {
        // INT graph has been frozen in 'stop' position because of the wash wiping

        // INT wiping should continue with an off phase after the wash wiping
        // and timer is currently stopped(elapsed) so start it
        TOSStartTimer( &TempoINT );

        TOSSeqUnfreezeGraph(cTOSSeqGraphIdLAPRrwIntermittentWipe);        
    }
    else
    {
        // Do nothing
    }
}


//==============================================================================
// DESCRIPTION:         Initialize wash prolongation
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
void LAPRrwInitWashProlongation( void )
{
#ifdef X90_PROJECT
    LAPRrwInitWashProlongation_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPRrwInitWashProlongation_Static(void)
{
#endif

    u8ExtraWipeCounter = mDATRead(U8Bit, NEEP_PROLONG_APPUI_ARR, Default);

    // Determine the number of extra wipes.
    // According the spec, the wipe will stop after u8ExtraWipeCounter rising edge of RR_AUTOSTOP_SW
    if ( mDATRead(U1Bit, RR_AUTOSTOP_SW, Immediate) == 0 )
    {
        // rear is wiping (Stop position is not reached)
        if ( u8ExtraWipeCounter > 0 )
        {
            u8ExtraWipeCounter--;   //first extra wipe has already begun
        }
        else
        {
            u8ExtraWipeCounter = u8ExtraWipeCounter;
            // Do nothing
        }
    }
    else
    {
        // rear is not wiping (Stop position is reached)
    }

    //QACJ 3200: amarinm1: This is done just to clear the signal.
    TOSReadSignal(cTOSSignalRR_AUTOSTOP_SWFalling_LAP_RRW);
}


//==============================================================================
// DESCRIPTION:         Start wash wiping
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
void LAPRrwStartWashWiping( void )
{
    bOutputWSHOn = cTrue;
}


//==============================================================================
// DESCRIPTION:         Start wash wait
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
void LAPRrwStartWashWait( void )
{
    TOSStartTimer( &TimerWashWait );
    
    // Stop initial parking graph at first wiping request
    bParkingOutput = cFalse;
    TOSSeqDeactivateGraph(cTOSSeqGraphIdLAPRrwInitialParking);
}


//==============================================================================
// DESCRIPTION:         Check if wash wait has elapsed
//
// PARAMETERS:          None
//
// RETURN VALUE:        BOOL: cTrue if elapsed
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
BOOL LAPRrwWashWaitHasElapsed( void )
{
    BOOL            bReturnValueL;
    const tTOSTimer WashWaitL = mReadWashWait();

    bReturnValueL = TOSIsTimerElapsed( &TimerWashWait, WashWaitL );

    return bReturnValueL;
}


//---------------------------------------------------------------------------
//                      Initial Parking Graph Functions
//---------------------------------------------------------------------------

//==============================================================================
// DESCRIPTION:         Check if wiper is in speed position
//
// PARAMETERS:          None
//
// RETURN VALUE:        BOOL: cTrue if in speed position
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
BOOL LAPRrwWiperIsInSpeedPosition( void )
{
    const BOOL bReturnValueL = (mDATRead(U1Bit, RR_AUTOSTOP_SW, Immediate) == 0);

    return bReturnValueL;
}


//==============================================================================
// DESCRIPTION:         Check if wiper is in stop position
//
// PARAMETERS:          None
//
// RETURN VALUE:        BOOL: cTrue if in stop position
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
BOOL LAPRrwWiperIsInStopPosition( void )
{
    const BOOL bReturnValueL = (mDATRead(U1Bit, RR_AUTOSTOP_SW, Immediate) == 1);

    return bReturnValueL;
}


//==============================================================================
// DESCRIPTION:         Start parking
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
void LAPRrwStartParking( void )
{
    bParkingOutput = cTrue;
}


//==============================================================================
// DESCRIPTION:         Check if stop position has been reached
//
// PARAMETERS:          None
//
// RETURN VALUE:        BOOL: cTrue if position reached
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
BOOL LAPRrwStopPositionHasBeenReached( void )
{
    const BOOL bReturnValueL = (u8InitialParkingState >= cStopPositionHasBeenReached);

    return bReturnValueL;
}


//==============================================================================
// DESCRIPTION:         Stop parking
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
void LAPRrwStopParking( void )
{
    bParkingOutput = cFalse;
}


//---------------------------------------------------------------------------
//                      RRWControl Graph Functions
//---------------------------------------------------------------------------

//==============================================================================
// DESCRIPTION:         Rear wiper arbitration management and HW protection
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
void LAPRrwArbitration( void )
{
#ifdef X90_PROJECT
    LAPRrwArbitration_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPRrwArbitration_Static(void)
{
#endif
    BOOL bTimerStartedL;
    BOOL bTimerElapsedL;

    if (   (mDATRead(U1Bit, EEP_EV_ARR, Default) == 1)
        && (mDATRead(U1Bit, PWR_IGN,    Default) == 1)   )
    {
        if (bComponentIsEnabled == cFalse)
        {
            bTimerStartedL = TOSIsTimerStarted(&IgnitionOnTimer);

            if (bTimerStartedL == cFalse)
            {
                TOSStartTimer(&IgnitionOnTimer);

                // Clear the front wiper fault immediately
                mDATWrite(U1Bit, DefAFAR,     cFalse, Default);                             
            }
            else
            {
                bTimerElapsedL = TOSIsTimerElapsed(&IgnitionOnTimer, cIgnitionOnTimeoutTicks);

                if (bTimerElapsedL != cFalse)
                {
                    ResumeAfterDisable();
                }
            }
        }
        else
        {
            // Do nothing
        }
        
        // Rear wiper arbitration management
        RearWiperArbitration();
    }
    else // Rear wiper disabled
    {
        TOSStopTimer(&IgnitionOnTimer);

        if (bComponentIsEnabled == cTrue)
        {
            DisableFunctionallity();
        }
        else
        {
            // Do nothing
        }
        u8InitialParkingState = cNotDefined;

        //QACJ 3200: amarinm1: This is done just to clear the signal.
        TOSReadSignal(cTOSSignalRearStopPositionDetected_LAP_RRW1);
        //QACJ 3200: amarinm1: This is done just to clear the signal.
        TOSReadSignal(cTOSSignalRearStopPositionDetected_LAP_RRW2);
    }

    // Run hardware protection routine
    HWProtection();
}

//==============================================================================
// DESCRIPTION:         Enter active state
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
void LAPRrwEnterActiveState( void )
{
#ifdef X90_PROJECT
    LAPRrwEnterActiveState_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPRrwEnterActiveState_Static(void)
{
#endif
    tTOSSeqGraphStateType ControlGraphStateL;

    ControlGraphStateL = TOSSeqGraphState(cTOSSeqGraphIdLAPRrwControl);

    if (ControlGraphStateL == cTOSSeqInactiveGraph)
    {
        TOSSeqActivateGraph(cTOSSeqGraphIdLAPRrwControl);
    }
    else
    {
        // Nothing to do.
    }     
    bPWR_IGNOld = cFalse;
    u8FaultCounter = 0;
    u8ProtectionCounter = cProtectionHeatCountInitial;
}


//==============================================================================
// DESCRIPTION:         Leave active state
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
void LAPRrwLeaveActiveState( void )
{
    DisableFunctionallity();

    TOSSeqDeactivateGraph(cTOSSeqGraphIdLAPRrwControl);
}


//==============================================================================
// DESCRIPTION:         Initialize component
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
void LAPRrwInitialize( void )
{
    StopRearWiper();

    // Check the initial value
    mLIBassert( mDATRead(U1Bit, RR_WIPER_RR_FOG_LAMP, Default) == 0 );
    bPWR_IGNOld = cFalse;
    u8FaultCounter = 0;
    u8ProtectionCounter = cProtectionHeatCountInitial;
}


/* [EXPORTED_FUNCTIONS_END] */
