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
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/EXT_CMP/CPP_CMP/STK/SOURCES/TOS_TPO.H-arc  $
// $Revision:   1.1  $
// -----------------------------------------------------------------------------
/* $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/EXT_CMP/CPP_CMP/STK/SOURCES/TOS_TPO.H-arc  $
// 
//    Rev 1.1   Sep 17 2009 10:27:10   adzhelp
// Cm003277: Functions defined as CALLT_TYPE
// 
//    Rev 1.0   04 Feb 2009 17:03:08   adzhelp
// Initial revision.
*/
//******************************************************************************
#ifndef I_TOS_TPO_H
#define I_TOS_TPO_H

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------
#include "tos.h"

//------------------------------------------------------------------------------
// Constant data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported type
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------
extern tTOSClock TOSClock;

//------------------------------------------------------------------------------
// Constant exported data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported Macros
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported functions
//------------------------------------------------------------------------------

//==============================================================================
// DESCRIPTION:         Initialization of the component
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Sets TOS clock to 1.
//                      Checks if the Timer tick can be divided by the alarm tick.
//                      If USE_DISABLE_TOSTIMER compilation directive is not used,
//                      starts the alarm corresponding to the TOS clock task,
//                      otherwise sets the TOS timer multiplication factor to
//                      cMinMultiplicationValue and sets the TOS clock task alarm
//                      to the right ID.
//                      Refer to Detailed Design Document
//==============================================================================
void TOSTpoInitialize( void );

//==============================================================================
// DESCRIPTION:         Periodic task of the component
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Increases TOSClock counter with u8TOSMultiplicationFactor value.
//                      If TOSClock counter is lower than u8TOSMultiplicationFactor
//                      increases TOSClock counter one more time.
//                      Refer to Detailed Design Document
//==============================================================================
void TOSClockTask( void );

//------------------------------------------------------------------------------
// ONE SHOT TIMERS
//------------------------------------------------------------------------------

//==============================================================================
// DESCRIPTION:         Starts the given timer
//
// PARAMETERS:          pTimer - timer's address to strore the current clock
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Must not be called inside an interrupt context!
//                      Refer to Detailed Design Document
//==============================================================================
CALLT_TYPE void TOSStartTimer( tTOSTimer* const pTimer );

//==============================================================================
// DESCRIPTION:         Stops the given timer
//
// PARAMETERS:          pTimer - timer's address to store zero to stop the timer.
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Sets pTimer to 0.
//                      Must not be called inside an interrupt context!
//                      Refer to Detailed Design Document
//==============================================================================
CALLT_TYPE void TOSStopTimer( tTOSTimer* const pTimer );

//==============================================================================
// DESCRIPTION:         Inidicates if the timer is active
//
// PARAMETERS:          pTimer - timer's address to check its value. This parameter
//                               must not be modified from this function.
//
// RETURN VALUE:        cTrue if pTimer value is not null, otherwise returns
//                      cFalse.
//
// DESIGN INFORMATION:  Refer to Detailed Design Document
//==============================================================================
BOOL TOSIsTimerStarted( const tTOSTimer* const pTimer );

//==============================================================================
// DESCRIPTION:         Indicates if requested Timeout is elapsed.
//
// PARAMETERS:          pTimer  - timer's address with stored  in starting moment
//                                system clock value;
//                      Timeout - requested timeout to compare with.
//
// RETURN VALUE:        cTrue if Timeout is elapsed, else cFalse.
//
// DESIGN INFORMATION:  If pTimer value is null, returns cTrue.
//                      Otherwise:
//                      - if clock is more than pTimer + Timeout,
//                        returns cTrue and stops the timer
//                      - otherwise, returns cFalse.
//                      Must not be called inside an interrupt context!
//                      Refer to Detailed Design Document
//==============================================================================
CALLT_TYPE BOOL TOSIsTimerElapsed( tTOSTimer* const pTimer, const tTOSTimer Timeout );

//==============================================================================
// DESCRIPTION:         Gets elapsed time
//
// PARAMETERS:          pTimer - timer's address with stored in starting moment
//                               system clock's value
//
// RETURN VALUE:        the difference between pTimer and current TOSClock value
//
// DESIGN INFORMATION:  Returns the difference between pTimer and TOSClock.
//                      If TOSClock < *pTime, the 0 value has to be "jump"
//                      Refer to Detailed Design Document
//==============================================================================
tTOSTimer TOSGetTimerElapsedTime( const tTOSTimer* const pTimer );

//------------------------------------------------------------------------------
// PERIODIC TIMERS
//------------------------------------------------------------------------------
//==============================================================================
// DESCRIPTION:         Starts the periodic timer pTimer
//
// PARAMETERS:          pTimer - periodic timer's address
//                      Delay  - delay's value
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Calculates and sets StartDate of the requested periodic timer.
//                      Refer to Detailed Design Document
//==============================================================================
void TOSStartPeriodicTimer_Internal( tTOSPeriodicTimer* const pTimer, const tTOSTimer Delay);

//==============================================================================
// DESCRIPTION:         Stops the periodic timer pTimer
//
// PARAMETERS:          pTimer - periodic timer's address
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Sets StartDate of the requested periodic timer to 0.
//                      Refer to Detailed Design Document
//==============================================================================
void TOSStopPeriodicTimer( tTOSPeriodicTimer* const pTimer );

//==============================================================================
// DESCRIPTION:         Indicates if the requested periodic timer is active
//
// PARAMETERS:          pTimer - periodic timer's address
//
// RETURN VALUE:        cTrue if the timer is active
//
// DESIGN INFORMATION:  Must not be called inside an interrupt context!
//                      Refer to Detailed Design Document
//==============================================================================
BOOL TOSIsPeriodicTimerStarted( const tTOSPeriodicTimer* const pTimer );

//==============================================================================
// DESCRIPTION:         Indicates if the requested periodic timer's time is elapsed
//
// PARAMETERS:          pTimer - periodic timer's address
//
// RETURN VALUE:        cTrue if the timer's time is elapsed
//
// DESIGN INFORMATION:  Calculates if the timer's time is elapsed and if it is - 
//                      re-starts the timer.
//                      Must not be called inside an interrupt context!
//                      Refer to Detailed Design Document
//==============================================================================
BOOL TOSIsPeriodicTimerElapsed( tTOSPeriodicTimer* const pTimer );


#ifdef USE_DISABLE_TOSTIMER
//==============================================================================
// DESCRIPTION:         Enables TOS timer
//
// PARAMETERS:          u8Period - imput value for the u8TOSMultiplicationFactor
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Sets u8TOSMultiplicationFactor with u8Period value.
//                      Sets TOSAlarmTPO period following u8TOSMultiplicationFactor.
//                      Starts TOSAlarmTPO alarm.
//                      Refer to Detailed Design Document
//==============================================================================
void TOSEnableTimer( const U8 u8Period );

//==============================================================================
// DESCRIPTION:         Disables TOS timer
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Cancels the requested TOS Timer's Alarm.
//                      Refer to Detailed Design Document
//==============================================================================
void TOSDisableTimer( void );

#endif // USE_DISABLE_TOSTIMER

#endif // I_TOS_TPO_H
