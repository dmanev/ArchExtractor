//******************************************************************************
// Company:      Johnson Controls Inc.
// -----------------------------------------------------------------------------
// Copyright:    This software is JCI property.
//               Duplication or disclosure without JCI written authorization
//               is prohibited.
// -----------------------------------------------------------------------------
// Project:      STK
// Language:     ANSI-C
// -----------------------------------------------------------------------------
// Component:    TOS_TPO
//               TOS timer management
// -----------------------------------------------------------------------------
// $Date:   Sep 17 2009 10:27:10  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/EXT_CMP/CPP_CMP/STK/SOURCES/TOS_TPO.C-arc  $
// $Revision:   1.1  $
// -----------------------------------------------------------------------------
/* $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/EXT_CMP/CPP_CMP/STK/SOURCES/TOS_TPO.C-arc  $
// 
//    Rev 1.1   Sep 17 2009 10:27:10   adzhelp
// Cm003277: Functions defined as CALLT_TYPE
// 
//    Rev 1.0   04 Feb 2009 17:03:08   adzhelp
// Initial revision.
*/
//******************************************************************************

//------------------------------------------------------------------------------
// Body Identification
//------------------------------------------------------------------------------
#define TOS_TPO "TOS_TPO"

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------
#include "tos_tpo.h"
#include "lib.h"

//------------------------------------------------------------------------------
// Local constants
//------------------------------------------------------------------------------
#define cClockCycleInAlarmTick  ((U32)((cTOSTimerTickMs * (U16)1000UL)   \
                                                             / cTOSTickAlarmUs))
#define cMinMultiplicationValue  ((U8)0x01u)

//------------------------------------------------------------------------------
// Local macros
//------------------------------------------------------------------------------
#ifdef USE_DISABLE_TOSTIMER
    #define mGetMultiplier()    u8TOSMultiplicationFactor
#else
    #define mGetMultiplier()    ((U8)0x01u)
#endif

//------------------------------------------------------------------------------
// Local types
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Local data
//------------------------------------------------------------------------------
#ifdef USE_DISABLE_TOSTIMER
    static tTOSAlarm    TOSAlarmTPO;
    static U8           u8TOSMultiplicationFactor;
#endif

//------------------------------------------------------------------------------
// Constant local data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------
tTOSClock   TOSClock;

//------------------------------------------------------------------------------
// Constant exported data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Local function prototypes
//------------------------------------------------------------------------------

//==============================================================================
//=========================== LOCAL FUNCTIONS ==================================
//==============================================================================

//==============================================================================
//=========================== EXPORTED FUNCTIONS ===============================
//==============================================================================

//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
void TOSTpoInitialize( void )
{
#ifndef USE_DISABLE_TOSTIMER
    static tTOSAlarm  Alarm;
#endif

#ifdef TOS_PREEMPTIVE
    TOSGetSchedulerResource(); //if TOS is preemptive - disable preemption
#endif

    TOSClock = (tTOSClock) 1;

    // This assert check if the Timer tick can be divided by the alarm tick.
    // If this assert fails, verify the values of
    // cTOSTickAlarmUs and cTOSTimerTickMs
    // then change the value of cTOSTimerTickMs
    mLIBassert( ( cClockCycleInAlarmTick * cTOSTickAlarmUs ) ==
                ( (U32)1000UL * cTOSTimerTickMs ) );

#ifndef USE_DISABLE_TOSTIMER
    Alarm.TaskID = cTOSTaskIdTOSClock;
    TOSSetRelAlarm( &Alarm, 0, cClockCycleInAlarmTick );
#else
    u8TOSMultiplicationFactor = cMinMultiplicationValue;
    TOSAlarmTPO.TaskID = cTOSTaskIdTOSClock;
    TOSSetRelAlarm(
                   &TOSAlarmTPO,
                   0,
        (tTOSTickAlarm)(cClockCycleInAlarmTick * ((U32)u8TOSMultiplicationFactor))
                  );
#endif

#ifdef TOS_PREEMPTIVE
    TOSReleaseSchedulerResource(); //if TOS is preemptive - release the resource 
#endif

}

//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
CALLT_TYPE void TOSStartTimer( tTOSTimer* const pTimer )
{
    if (pTimer != NULL)
    {
#ifdef TOS_PREEMPTIVE
        TOSGetSchedulerResource(); //if TOS is preemptive - disable preemption
#endif

        *pTimer = TOSClock;

#ifdef TOS_PREEMPTIVE
        TOSReleaseSchedulerResource(); //if TOS is preemptive - release the resource 
#endif
    }
}

//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
CALLT_TYPE void TOSStopTimer( tTOSTimer* const pTimer )
{
    if (pTimer != NULL)
    {
#ifdef TOS_PREEMPTIVE
        TOSGetSchedulerResource(); //if TOS is preemptive - disable preemption
#endif

        *pTimer = 0;

#ifdef TOS_PREEMPTIVE
        TOSReleaseSchedulerResource(); //if TOS is preemptive - release the resource 
#endif
    }
}

//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
BOOL TOSIsTimerStarted( const tTOSTimer* const pTimer )
{
    BOOL bTimerIsStarted = cFalse;

    if (pTimer != NULL)
    {
#ifdef TOS_PREEMPTIVE
        TOSGetSchedulerResource(); //if TOS is preemptive - disable preemption
#endif
        
        // A timer is never equal to 0
        // The 0 value is reserved to the timer stoped
        if ( *pTimer != 0 )
        {
            bTimerIsStarted = cTrue;
        }
        
#ifdef TOS_PREEMPTIVE
        TOSReleaseSchedulerResource(); //if TOS is preemptive - release the resource 
#endif
    }

    return bTimerIsStarted;
}

//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
CALLT_TYPE BOOL TOSIsTimerElapsed( tTOSTimer* const pTimer, const tTOSTimer Timeout )
{
    tTOSTimer Delay;
    BOOL bTimerIsElapsed = cFalse;

    if (pTimer != NULL)
    {
#ifdef TOS_PREEMPTIVE
        TOSGetSchedulerResource(); //if TOS is preemptive - disable preemption
#endif

        // A timer is never equal to 0
        // The 0 value is reserved to the timer stoped
        if ( *pTimer == 0 )
        {
            bTimerIsElapsed = cTrue;
        }
        else
        {
            Delay = (tTOSTimer)( TOSClock - *pTimer );
            
            if ( TOSClock < *pTimer )
            {
                // The 0 value had been "jump" so we must substact 1 to the delay
                Delay--;
            }
            
            if ( (Delay > Timeout) || (Timeout == 0) )
            {
                // The timer is stoped
                *pTimer = 0;
                bTimerIsElapsed = cTrue;
            }

        }
        
#ifdef TOS_PREEMPTIVE
        TOSReleaseSchedulerResource(); //if TOS is preemptive - release the resource 
#endif
    }

    return bTimerIsElapsed;
}

//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
tTOSTimer TOSGetTimerElapsedTime( const tTOSTimer* const pTimer )
{
    tTOSTimer Delay = (tTOSTimer)0;

    if (pTimer != NULL)
    {
#ifdef TOS_PREEMPTIVE
        TOSGetSchedulerResource(); //if TOS is preemptive - disable preemption
#endif

        // A timer is never equal to 0
        // The 0 value is reserved to the timer stoped
        if ( *pTimer == 0 )
        {
            // This function must not be call with a stoped tempo
            mLIBassert( cFalse );
        }
        else
        {
            Delay = (tTOSTimer)( TOSClock - *pTimer );
            
            if ( TOSClock < *pTimer )
            {
                // The 0 value had been "jump" so we must substract 1 to the delay
                Delay--;
            }
        }

#ifdef TOS_PREEMPTIVE
        TOSReleaseSchedulerResource(); //if TOS is preemptive - release the resource 
#endif
    }

    return Delay;
}

//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
void TOSClockTask( void )
{
    TOSClock += mGetMultiplier();

    if ( TOSClock < mGetMultiplier() )
    {
        TOSClock++;
    }
}

#ifdef USE_DISABLE_TOSTIMER
//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
void TOSEnableTimer(const U8 u8Period )
{
#ifdef TOS_PREEMPTIVE
    TOSGetSchedulerResource(); //if TOS is preemptive - disable preemption
#endif

    mLIBassert( u8Period >= cMinMultiplicationValue );

    u8TOSMultiplicationFactor = u8Period;
    TOSAlarmTPO.Period = (tTOSTickAlarm)( cClockCycleInAlarmTick *
                                               ((U32)u8TOSMultiplicationFactor));

    TOSSetRelAlarm(
                   &TOSAlarmTPO,
                   0,
       (tTOSTickAlarm)(cClockCycleInAlarmTick*((U32)u8TOSMultiplicationFactor))
                  );

#ifdef TOS_PREEMPTIVE
    TOSReleaseSchedulerResource(); //if TOS is preemptive - release the resource 
#endif
}

//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
void TOSDisableTimer( void )
{
#ifdef TOS_PREEMPTIVE
    TOSGetSchedulerResource(); //if TOS is preemptive - disable preemption
#endif

    TOSCancelAlarm( &TOSAlarmTPO );

#ifdef TOS_PREEMPTIVE
    TOSReleaseSchedulerResource(); //if TOS is preemptive - release the resource 
#endif
}
#endif

