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
// Component:    LAP_FRW
//               Front wipers
// -----------------------------------------------------------------------------
// $Date:   Mar 22 2010 14:48:54  $
// $Archive::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_FRW/LAP_FRW.c-arc  $
// $Revision:   1.15  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_FRW/LAP_FRW.c-arc  $
// 
//    Rev 1.15   Mar 22 2010 14:48:54   adzhelp
// Cm006814: Code review corrections
// 
//    Rev 1.14   Mar 02 2010 10:37:46   adzhelp
// Cm006814: TPS_ARRET, TPS_MAX_COUPLBLOC, TPS_APPUILAV, TPS,ESSUIE_MINI, PROLONG_APPUI_COURT, PROLONG_APPUI_LONG normalized
// 
//    Rev 1.13   Feb 18 2010 15:20:30   adzhelp
// Cm006594: Activation on rising edge of washer button
// 
//    Rev 1.12   Feb 17 2010 17:29:22   adzhelp
// Cm007070: IGN ON condition filtration for 500 ms
// 
//    Rev 1.11   Jan 20 2010 15:10:26   adzhelp
// Cm006669: On rising edges of front and rear washer switches activate front washer
// 
//    Rev 1.10   Jan 07 2010 15:48:10   amanevd
// Cm005566: Stop position fault memorised is never deleted from the component
// 
//    Rev 1.9   Nov 30 2009 13:12:20   amarinm1
// Cm006742: Configuration parameters are now calculated only when needed.
// 
//    Rev 1.8   Nov 02 2009 14:51:34   amarinm1
// Cm006576: Front wash request is taken into account only if rear wash is not requested.
// 
//    Rev 1.7   Oct 09 2009 15:20:24   amarinm1
// Cm006451: Signal FrontWiperStopIsAllowed_LAP_FRW is now read in LAPFrwINTStartWiping() in order to clear it.
// 
//    Rev 1.6   Aug 13 2009 13:12:20   amarinm1
// Cm005756: Times that need precision were decreased with 1 tick.
// 
//    Rev 1.5   Aug 05 2009 14:04:46   amarinm1
// Cm005598, Cm005599: Bad management of the protection function was fixed.
// -Issues from the code review were fixed.
// 
//    Rev 1.4   Jun 24 2009 14:47:54   amarinm1
// Cm005027 & Cm005029: Reading of FR_AUTOSTOP_SW is now done with immediate access.
// 
//    Rev 1.3   Apr 29 2009 14:17:14   adzhelp
// Cm003261: No code change. Functions moved to banked memory area
// 
//    Rev 1.2   Apr 22 2009 18:08:14   amarinm1
// Cm003261: The name of the output was changed to the correct one.
// 
//    Rev 1.1   Apr 22 2009 17:19:34   amarinm1
// Cm003261: A problem with short wash press detection was fixed.
// 
//    Rev 1.0   Apr 09 2009 14:47:48   amarinm1
// Initial revision.
//******************************************************************************
#endif

//------------------------------------------------------------------------------
// Body Identification
//------------------------------------------------------------------------------
#define lap_frw  "lap_frw"


//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------
#include "tos.h"
#include "dat.h"
#include "lib.h"
#include "LAP_FRW.h"
#include "LAP_FRW.hgr"


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
#define cTPS_APPUILAV_step           ((U16)12)
#define cTPS_ESSUIE_MINI_step        ((U16)12)
#define cWashWaitInMs                ((U32)750)

#define cIgnitionOnTimeoutMs         (500UL)
#define cIgnitionOnTimeoutTicks      (mTOSConvMsInTimerTick(cIgnitionOnTimeoutMs) - (tTOSTimer)1)

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
#define mReadIntermittentPause() \
    ( DATCmnFrRrwIntermittentPause = (u8DATCmnTPS_CAD_FIXE_old == mDATRead(U8Bit, EEP_TPS_CAD_FIXE, Default)) ? \
    /* //QACJ 3443: amarinm1: There is no recursion - second macro is formed through concatenation. */ \
    DATCmnFrRrwIntermittentPause : mCalcIntermittentPause() )

#define mCalcIntermittentPause() \
    /* //QACJ 3443: amarinm1: There is no recursion - second macro is formed through concatenation. */ \
    (tTOSTimer)(mTOSConvMsInTimerTick( (U32)( cTPS_CAD_FIXE_step * (u8DATCmnTPS_CAD_FIXE_old = mDATRead(U8Bit, EEP_TPS_CAD_FIXE, Default)) ) ) - (tTOSTimer)1U)



//------------------------------
#define mReadWashPressThreshold() \
    ( DATCmnFrwWashPressThreshold = (u8DATCmnTPS_APPUILAV_old == mDATRead(U8Bit, NEEP_TPS_APPUILAV, Default)) ? \
    /* //QACJ 3443: amarinm1: There is no recursion - second macro is formed through concatenation. */ \
    DATCmnFrwWashPressThreshold : mCalcWashPressThreshold() )

#define mCalcWashPressThreshold() \
    /* //QACJ 3443: amarinm1: There is no recursion - second macro is formed through concatenation. */ \
    (tTOSTimer)(mTOSConvMsInTimerTick( (U32)( cTPS_APPUILAV_step * (u8DATCmnTPS_APPUILAV_old = mDATRead(U8Bit, NEEP_TPS_APPUILAV, Default)) ) ) - (tTOSTimer)1U)



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
static tTOSTimer    TimerWashPress;
static tTOSTimer    IgnitionOnTimer;

static U8           u8ExtraWipeCounter;

static BOOL         bProtectionOutput;
static BOOL         bOutputINTOn;
static BOOL         bOutputWSHOn;
static BOOL         bWashPressIsLong;
static BOOL         bMotorCommand;

static BOOL         bFrontWasherSWOld;
static BOOL         bRearWasherSWOld;


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
static MEM_TYPE void StopFrontWiper( void );
static MEM_TYPE void FrontWiperArbitration( void );

#ifdef X90_PROJECT
static MEM_TYPE void LAPFrwStopProtectionMode_Static(void);
static MEM_TYPE BOOL LAPFrwINTConditionsToStopArePresent_Static(void);
static MEM_TYPE void LAPFrwInitWashProlongation_Static(void);
static MEM_TYPE void LAPFrwArbitration_Static(void);
static MEM_TYPE void LAPFrwEnterActiveState_Static(void);
#endif

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
static MEM_TYPE void StopFrontWiper( void )
{
    TOSSeqDeactivateGraph(cTOSSeqGraphIdLAPFrwEngineProtection);
    TOSSeqDeactivateGraph(cTOSSeqGraphIdLAPFrwIntermittentWipe);
    TOSSeqDeactivateGraph(cTOSSeqGraphIdLAPFrwWashing);

    bProtectionOutput     = cEnableWiping;
    bOutputINTOn          = cFalse;
    bOutputWSHOn          = cFalse;
    u8ExtraWipeCounter    = 0;
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
static MEM_TYPE void FrontWiperArbitration( void )
{
    if (bProtectionOutput == cDisableWiping)
    {
        // Motor Protection is active => the motor must be stopped immediatly
        bMotorCommand = cMotorOff;
    }
    else
    {
        if (   (bOutputWSHOn == cTrue)
            || (bOutputINTOn == cTrue)   )
        {
            // Washing or INT request or protection graph is trying to release the blocked wiper
            bMotorCommand = cMotorOn;
        }
        else
        {
            bMotorCommand = cMotorOff;
        }
    }

    mDATWrite(U1Bit, FRONT_WIPER, bMotorCommand, Default);
}


//==============================================================================
//=========================== EXPORTED FUNCTIONS ===============================
//==============================================================================

//---------------------------------------------------------------------------
//                      Functions used in several graphs
//---------------------------------------------------------------------------


//==============================================================================
// DESCRIPTION:         < short description of the function >
//
// PARAMETERS:          < type,usage and constraints for all parameters >
//
// RETURN VALUE:        < type and usage >
//
// DESIGN INFORMATION:  < usage, pseudo code, algorithm, constraints ... >
//==============================================================================
BOOL LAPFrwEPStopPositionIsDetected( void )
{
    const BOOL bReturnValueL = TOSReadSignal(cTOSSignalFrontStopPositionDetected_LAP_FRW1);
  
    return bReturnValueL;
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
BOOL LAPFrwWashStopPositionIsDetected( void )
{
    const BOOL bReturnValueL = TOSReadSignal(cTOSSignalFrontStopPositionDetected_LAP_FRW2);
  
    return bReturnValueL;
}


//---------------------------------------------------------------------------
//                      FRWEngineProtection Graph Functions
//---------------------------------------------------------------------------
//==============================================================================
// DESCRIPTION:         < short description of the function >
//
// PARAMETERS:          < type,usage and constraints for all parameters >
//
// RETURN VALUE:        < type and usage >
//
// DESIGN INFORMATION:  < usage, pseudo code, algorithm, constraints ... >
//==============================================================================
BOOL LAPFrwOutputIsInactive( void )
{
    const BOOL bReturnValueL = (mDATRead(U1Bit, FRONT_WIPER, Default) == 0);
  
    return bReturnValueL;
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
BOOL LAPFrwOutputIsActive( void )
{
    const BOOL bReturnValueL = (mDATRead(U1Bit, FRONT_WIPER, Default) == 1);
  
    return bReturnValueL;
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
BOOL LAPFrwInitialWipingTimeoutHasElapsed( void )
{
#ifdef X90_PROJECT
    static MEM_TYPE BOOL LAPFrwInitialWipingTimeoutHasElapsed_Static(void);
    return LAPFrwInitialWipingTimeoutHasElapsed_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL LAPFrwInitialWipingTimeoutHasElapsed_Static(void)
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
// DESCRIPTION:         < short description of the function >
//
// PARAMETERS:          < type,usage and constraints for all parameters >
//
// RETURN VALUE:        < type and usage >
//
// DESIGN INFORMATION:  < usage, pseudo code, algorithm, constraints ... >
//==============================================================================
void LAPFrwEnableWiping( void )
{
    bProtectionOutput = cEnableWiping;

    // Clear front fixed stop fault
    mDATWrite(U1Bit, DefAFAV,     cFalse, Default);

    TOSStartTimer( &TempoEP );
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
void LAPFrwTryWiping( void )
{
    bProtectionOutput = cEnableWiping;
    TOSStartTimer( &TempoEP );
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
void LAPFrwDisableWiping( void )
{
    bProtectionOutput = cDisableWiping;

    // Declare front fixed stop fault
    mDATWrite(U1Bit, DefAFAV,     cTrue, Default);
    mDATWrite(U1Bit, EEP_DefAfav, cTrue, Immediate);
    
    TOSStartTimer( &TempoEP );
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
BOOL LAPFrwDisableTimeoutHasElapsed( void )
{
#ifdef X90_PROJECT
    static MEM_TYPE BOOL LAPFrwDisableTimeoutHasElapsed_Static(void);
    return LAPFrwDisableTimeoutHasElapsed_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL LAPFrwDisableTimeoutHasElapsed_Static(void)
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
// DESCRIPTION:         < short description of the function >
//
// PARAMETERS:          < type,usage and constraints for all parameters >
//
// RETURN VALUE:        < type and usage >
//
// DESIGN INFORMATION:  < usage, pseudo code, algorithm, constraints ... >
//==============================================================================
BOOL LAPFrwWipingTimeoutHasElapsed( void )
{
#ifdef X90_PROJECT
    static MEM_TYPE BOOL LAPFrwWipingTimeoutHasElapsed_Static(void);
    return LAPFrwWipingTimeoutHasElapsed_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL LAPFrwWipingTimeoutHasElapsed_Static(void)
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
// DESCRIPTION:         < short description of the function >
//
// PARAMETERS:          < type,usage and constraints for all parameters >
//
// RETURN VALUE:        < type and usage >
//
// DESIGN INFORMATION:  < usage, pseudo code, algorithm, constraints ... >
//==============================================================================
BOOL LAPFrwWipingIsNotRequested( void )
{
    const BOOL bReturnValueL = (   (mDATRead(U1Bit, FR_WASHER_SW, Default) == 0)
                                && (mDATRead(U1Bit, FR_WIPER_INT_SW, Default) == 0)  );
  
    return bReturnValueL;
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
void LAPFrwStopProtectionMode( void )
{
#ifdef X90_PROJECT
    LAPFrwStopProtectionMode_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPFrwStopProtectionMode_Static(void)
{
#endif    
    // Reset flag
    bProtectionOutput = cEnableWiping;

    // Clear front fixed stop fault
    mDATWrite(U1Bit, DefAFAV,     cFalse, Default);

    // Clear Output
    mDATWrite(U1Bit, FRONT_WIPER, cMotorOff, Default);

    // Restart the command graphs
    TOSSeqDeactivateGraph(cTOSSeqGraphIdLAPFrwIntermittentWipe);
    TOSSeqDeactivateGraph(cTOSSeqGraphIdLAPFrwWashing);

    bOutputWSHOn = cFalse;
    bOutputINTOn = cFalse;
    u8ExtraWipeCounter = 0;

    TOSSeqActivateGraph(cTOSSeqGraphIdLAPFrwIntermittentWipe);
    TOSSeqActivateGraph(cTOSSeqGraphIdLAPFrwWashing);
}


//---------------------------------------------------------------------------
//                      FRWIntermittentWipe Graph Functions
//---------------------------------------------------------------------------
//See Definition of the functions used in several graphs.

//==============================================================================
// DESCRIPTION:         < short description of the function >
//
// PARAMETERS:          < type,usage and constraints for all parameters >
//
// RETURN VALUE:        < type and usage >
//
// DESIGN INFORMATION:  < usage, pseudo code, algorithm, constraints ... >
//==============================================================================
BOOL LAPFrwINTConditionsToStopArePresent( void )
{
#ifdef X90_PROJECT
    return LAPFrwINTConditionsToStopArePresent_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL LAPFrwINTConditionsToStopArePresent_Static(void)
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
            TOSReadSignal(cTOSSignalFrontWiperStopIsAllowed_LAP_FRW);
        bReturnValueL &= bFrontWiperStopIsAllowedL;
    }

    return bReturnValueL;
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
BOOL LAPFrwINTRequestIsOff( void )
{
    const BOOL bReturnValueL = (mDATRead(U1Bit, FR_WIPER_INT_SW, Default) == 0);
    
    return bReturnValueL;
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
BOOL LAPFrwINTRequestIsOn( void )
{
    const BOOL bReturnValue = (mDATRead(U1Bit, FR_WIPER_INT_SW, Default) == 1);
 
    return bReturnValue;
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
void LAPFrwINTStopWiping( void )
{
    if ( bOutputWSHOn == cTrue )
    {
        bOutputINTOn = cFalse;
        TOSSeqFreezeGraph(cTOSSeqGraphIdLAPFrwIntermittentWipe);
    }
    else
    {
        bOutputINTOn = cFalse;
        TOSStartTimer( &TempoINT );
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
BOOL LAPFrwINTPauseHasElapsed( void )
{
#ifdef X90_PROJECT
    static MEM_TYPE BOOL LAPFrwINTPauseHasElapsed_Static(void);
    return LAPFrwINTPauseHasElapsed_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL LAPFrwINTPauseHasElapsed_Static(void)
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
// DESCRIPTION:         < short description of the function >
//
// PARAMETERS:          < type,usage and constraints for all parameters >
//
// RETURN VALUE:        < type and usage >
//
// DESIGN INFORMATION:  < usage, pseudo code, algorithm, constraints ... >
//==============================================================================
void LAPFrwINTStartWiping( void )
{
    bOutputINTOn = cTrue;
    TOSStartTimer( &TempoINT );

    //QACJ 3200: amarinm1: This is done just to clear the signal.
    TOSReadSignal(cTOSSignalFrontWiperStopIsAllowed_LAP_FRW);
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
void LAPFrwINTStopTimer( void )
{
    TOSStopTimer( &TempoINT );
}


//---------------------------------------------------------------------------
//                      FRWWashing Graph Functions
//---------------------------------------------------------------------------

//==============================================================================
// DESCRIPTION:         < short description of the function >
//
// PARAMETERS:          < type,usage and constraints for all parameters >
//
// RETURN VALUE:        < type and usage >
//
// DESIGN INFORMATION:  < usage, pseudo code, algorithm, constraints ... >
//==============================================================================
BOOL LAPFrwWashCycleIsFinished( void )
{
    const BOOL bReturnValueL = (u8ExtraWipeCounter == 0);
 
    return bReturnValueL;
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
BOOL LAPFrwWashExtraWipeBegining( void )
{
    const BOOL bFR_AUTOSTOP_SW_FallingEdgeIsDetectedL = 
        TOSReadSignal(cTOSSignalFR_AUTOSTOP_SWFalling_LAP_FRW);
    const BOOL bReturnValueL = 
              (   (u8ExtraWipeCounter > 0)
               && (bFR_AUTOSTOP_SW_FallingEdgeIsDetectedL == 1) );
  
    return bReturnValueL;
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
void LAPFrwWashProlongation( void )
{
    u8ExtraWipeCounter--;
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
void LAPFrwPrepareToStopWashProlongation( void )
{
    //QACJ 3200: amarinm1: This is done just to clear the signal.
    TOSReadSignal(cTOSSignalFrontStopPositionDetected_LAP_FRW2);
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
BOOL LAPFrwWashRequestIsOff( void )
{
    const BOOL bReturnValueL = (mDATRead(U1Bit, FR_WASHER_SW, Default) == 0);
 
    return bReturnValueL;
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
BOOL LAPFrwWashRequestIsOn( void )
{
#ifdef X90_PROJECT
    static MEM_TYPE BOOL LAPFrwWashRequestIsOn_Static(void);
    return LAPFrwWashRequestIsOn_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL LAPFrwWashRequestIsOn_Static(void)
{
#endif  
    BOOL bReturnValueL = cFalse;
    const BOOL bFrontWasherSWL = mDATRead(U1Bit, FR_WASHER_SW, Default);
    const BOOL bRearWasherSWL = mDATRead(U1Bit, RR_WASHER_SW, Default);
    
    if (mDATRead(U1Bit, FrontWasherButtonBlocked, Default) != cFalse)
    {
        // button pressed before ignition on
        // ignore button
        if (bFrontWasherSWL == cFalse)
        {
            mDATWrite(U1Bit, FrontWasherButtonBlocked, cFalse, Default);
        }
        else
        {
            // wait for button release
        }
    }    
    else if (bFrontWasherSWL != cFalse)
    {
        if (  (bFrontWasherSWOld == cFalse) // FR washer rising edge
            &&(bRearWasherSWL != cFalse) && (bRearWasherSWOld == cFalse)) // RR washer rising edge
        {
            // Rising edge of both switches (prsFS_FRW-334)
            bReturnValueL = cTrue;
        }
        else if (mDATRead(U1Bit, RearWasherButtonBlocked, Default) == cFalse)
        {
            bReturnValueL = (bRearWasherSWL == cFalse); // check if rear washer switch inactive
            // but only when button is not blocked
        }
        else
        {
            // rear washer button blocked, disregard it
            bReturnValueL = cTrue;
        }
    }
    else
    {
        // wait for button press
    }

    // Update old values
    bFrontWasherSWOld = bFrontWasherSWL;
    bRearWasherSWOld = bRearWasherSWL;

    return bReturnValueL;
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
void LAPFrwStopWashWiping( void )
{
    const tTOSSeqGraphStateType INTGraphStateL = 
        TOSSeqGraphState(cTOSSeqGraphIdLAPFrwIntermittentWipe);

    bOutputWSHOn = cFalse;

    if ( INTGraphStateL == cTOSSeqFrozenGraph ) 
    {
        // INT graph has been frozen in 'stop' position because of the wash wiping

        // INT wiping should continue with an off phase after the wash wiping
        // and timer is currently stopped(elapsed) so start it
        TOSStartTimer( &TempoINT );

        TOSSeqUnfreezeGraph(cTOSSeqGraphIdLAPFrwIntermittentWipe);        
    }
    else
    {
        // Do nothing
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
void LAPFrwSetWashPressType( void )
{
#ifdef X90_PROJECT
    static MEM_TYPE void LAPFrwSetWashPressType_Static(void);
    LAPFrwSetWashPressType_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPFrwSetWashPressType_Static(void)
{
#endif  
    tTOSTimer WashPressThresholdL;

    //QACJ 3226: amarinm1: This is intentional and is checked for problems.
    WashPressThresholdL = mReadWashPressThreshold();
    bWashPressIsLong = TOSIsTempoElapsed( &TimerWashPress, WashPressThresholdL );
    // In case it's not elapsed
    TOSStopTimer( &TimerWashPress );
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
void LAPFrwInitWashProlongation( void )
{
#ifdef X90_PROJECT
    LAPFrwInitWashProlongation_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPFrwInitWashProlongation_Static(void)
{
#endif
    const BOOL bWashPressTimerIsStarted = TOSIsTimerStarted(&TimerWashPress);
   
    // Timer is still running so wash press type isn't yet determined
    if ( bWashPressTimerIsStarted == cTrue )
    {
        LAPFrwSetWashPressType();
    }

    if ( bWashPressIsLong == cFalse )
    {
        u8ExtraWipeCounter = mDATRead(U8Bit, NEEP_PROLONG_APPUI_COURT, Default);
    }
    else
    {
        u8ExtraWipeCounter = mDATRead(U8Bit, NEEP_PROLONG_APPUI_LONG, Default);
    }

    // Determine the number of extra wipes.
    // According the spec, the wipe will stop after u8ExtraWipeCounter rising edge of FR_AUTOSTOP_SW
    if ( mDATRead(U1Bit, FR_AUTOSTOP_SW, Immediate) == 0 )
    {
        // front is wiping (Stop position is not reached)
        if ( u8ExtraWipeCounter > 0 )
        {
            u8ExtraWipeCounter--;   //first extra wipe has already begun
        }
        else
        {
            // Do nothing
        }
    }
    else
    {
        // front is not wiping (Stop position is reached)
    }

    //QACJ 3200: amarinm1: This is done just to clear the signal.
    TOSReadSignal(cTOSSignalFR_AUTOSTOP_SWFalling_LAP_FRW);
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
void LAPFrwStartWashWiping( void )
{
    bOutputWSHOn = cTrue;
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
void LAPFrwStartWashWait( void )
{
    TOSStartTimer( &TimerWashWait );
    TOSStartTimer( &TimerWashPress );
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
void LAPFrwStartWashPressTimer( void )
{
    TOSStartTimer( &TimerWashPress );
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
BOOL LAPFrwWashWaitHasElapsed( void )
{
    BOOL            bReturnValueL;
    const tTOSTimer WashWaitL = mReadWashWait();

    bReturnValueL = TOSIsTimerElapsed( &TimerWashWait, WashWaitL );

    return bReturnValueL;
}


//---------------------------------------------------------------------------
//                      FRWControl Graph Functions
//---------------------------------------------------------------------------

//==============================================================================
// DESCRIPTION:         < short description of the function >
//
// PARAMETERS:          < type,usage and constraints for all parameters >
//
// RETURN VALUE:        < type and usage >
//
// DESIGN INFORMATION:  < usage, pseudo code, algorithm, constraints ... >
//==============================================================================
void LAPFrwArbitration( void )
{
#ifdef X90_PROJECT
    LAPFrwArbitration_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPFrwArbitration_Static(void)
{
#endif
    tTOSSeqGraphStateType FrontWiperGraphState;
    BOOL bTimerStartedL;
    BOOL bTimerElapsedL;

    if ( mDATRead(U1Bit, PWR_IGN, Default) == 0 )
    {
        StopFrontWiper();
        
        mDATWrite(U1Bit, FRONT_WIPER, 0, Default);
        TOSStopTimer(&IgnitionOnTimer);
    }
    else
    {
        // Only one graph state is read because
        // all graphs are activated or deactivated in the same time.
        FrontWiperGraphState = TOSSeqGraphState(cTOSSeqGraphIdLAPFrwEngineProtection);

        if (FrontWiperGraphState == cTOSSeqInactiveGraph)
        {
            bTimerStartedL = TOSIsTimerStarted(&IgnitionOnTimer);

            if (bTimerStartedL == cFalse)
            {
                TOSStartTimer(&IgnitionOnTimer);

                // Clear the front wiper fault immediately
                mDATWrite(U1Bit, DefAFAV,     cFalse, Default);
            }
            else
            {
                bTimerElapsedL = TOSIsTimerElapsed(&IgnitionOnTimer, cIgnitionOnTimeoutTicks);

                if (bTimerElapsedL != cFalse)
                {
                    // The graphs are inactive => it is a raising edge of Apc
                    TOSSeqActivateGraph(cTOSSeqGraphIdLAPFrwEngineProtection);
                    TOSSeqActivateGraph(cTOSSeqGraphIdLAPFrwIntermittentWipe);
                    TOSSeqActivateGraph(cTOSSeqGraphIdLAPFrwWashing);

                    // Initial states of buttons
                    bFrontWasherSWOld = mDATRead(U1Bit, FR_WASHER_SW, Default);
                    bRearWasherSWOld = mDATRead(U1Bit, RR_WASHER_SW, Default);

                    mDATWrite(U1Bit, FrontWasherButtonBlocked, 
                              (bFrontWasherSWOld != cFalse), Default);
                }
                else
                {
                    // wait timer to elapse
                }
            }
        }
        else
        {
            // nothing. The graphs are already active
        } 

        // Front wiper arbitration management
        FrontWiperArbitration();
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
void LAPFrwEnterActiveState( void )
{
#ifdef X90_PROJECT
    LAPFrwEnterActiveState_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPFrwEnterActiveState_Static(void)
{
#endif
    tTOSSeqGraphStateType ControlGraphState;

    ControlGraphState = TOSSeqGraphState(cTOSSeqGraphIdLAPFrwControl);

    if (ControlGraphState == cTOSSeqInactiveGraph)
    {
        TOSSeqActivateGraph(cTOSSeqGraphIdLAPFrwControl);
    }
    else
    {
        // Nothing to do.
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
void LAPFrwLeaveActiveState( void )
{
    mDATWrite(U1Bit, FRONT_WIPER, cMotorOff, Default);

    TOSSeqDeactivateGraph(cTOSSeqGraphIdLAPFrwControl);
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
void LAPFrwInitialize( void )
{
    StopFrontWiper();

    // Check the initial value
    mLIBassert( mDATRead(U1Bit, FRONT_WIPER, Default) == 0 );
}


/* [EXPORTED_FUNCTIONS_END] */
