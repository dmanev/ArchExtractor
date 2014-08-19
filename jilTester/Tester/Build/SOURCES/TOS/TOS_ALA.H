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
// Component:    TOS_ALA
//               TOS Alarm management
// -----------------------------------------------------------------------------
// $Date:   04 Feb 2009 17:03:04  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/EXT_CMP/CPP_CMP/STK/SOURCES/TOS_ALA.H-arc  $
// $Revision:   1.0  $
// -----------------------------------------------------------------------------
/* $Log:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/EXT_CMP/CPP_CMP/STK/SOURCES/TOS_ALA.H-arc  $
// 
//    Rev 1.0   04 Feb 2009 17:03:04   adzhelp
// Initial revision.
*/
//******************************************************************************
#ifndef I_TOS_ALA_H
#define I_TOS_ALA_H

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------

#include "tos.h"

//------------------------------------------------------------------------------
// Constant data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported types
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Constant exported data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported Macros
//------------------------------------------------------------------------------

//==============================================================================
// DESCRIPTION:         Initiates a relative Alarm
//
// PARAMETERS:          tTOSAlarm* pAlarm       - address of the relative Alarm
//                                                object type;
//                      tTOSTickAlarm Increment - this parameter is not taken
//                                                into account;
//                      tTOSTickAlarm Cycle     - this parameter can only take
//                                                value of 2 to the power of x.
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Calls the TOSSetRelAlarm_Interne function.
//                      Refer to Detailed Design Document
//==============================================================================
#define TOSSetRelAlarm( pAlarm, Increment, Cycle ) \
        TOSSetRelAlarm_Interne( pAlarm, Cycle )


//------------------------------------------------------------------------------
// Exported functions
//------------------------------------------------------------------------------

//==============================================================================
// DESCRIPTION:         Initialization of the TOS_ALA component
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Clears Alarm state;
//                      Clears all TOS_ORD task list.
//                      Refer to Detailed Design Document
//==============================================================================
void TOSAlaInitialize(void);

//==============================================================================
// DESCRIPTION:         Starts the TOS_ALA component.
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Calls TOSStartSlowestAlarms function with definition of
//                      the minimum incremental cycle to start LDB timer used by
//                      TOS_ALA.
//                      Refer to Detailed Design Document
//==============================================================================
void TOSStartAlarm(void);

//==============================================================================
// DESCRIPTION:         Stops the TOS_ALA component.
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Stops LDB timer used by TOS_ALA.
//                      Refer to Detailed Design Document
//==============================================================================
void TOSStopAlarm(void);

//==============================================================================
// DESCRIPTION:         Starts LDB timer used by TOS_ALA.
//
// PARAMETERS:          MinimumCycle - minimum incremental cycle for the LDB 
//                                     timer used by TOS_ALA. MinimumCycle has
//                                     to be more or equal to 1.
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Sets AlarmCycle to the MinimumCycle;
//                      Computes AlarmState;
//                      Starts LDB timer used by TOS_ALA.
//                      Refer to Detailed Design Document
//==============================================================================
void TOSStartSlowestAlarms(const tTOSTickAlarm MinimumCycle);

//==============================================================================
// DESCRIPTION:         Cancels the requested Alarm.
//
// PARAMETERS:          pAlarm - address of the requested Alarm
//                               object type. The parameter is not
//                               modified by this function. 
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Check if the asked period is 2 to power of x compatible.
//                      Removes the pAlarm task from the TOS_ORD task list.
//                      Refer to Detailed Design Document
//==============================================================================
void TOSCancelAlarm( const tTOSAlarm* const pAlarm);

//==============================================================================
// DESCRIPTION:         Initiates a relative Alarm.
//
// PARAMETERS:          pAlarm - address of the relative Alarm
//                               object type;
//                      Cycle  - this parameter can only take
//                               value of 2 to the power of x.
//                               Its min value is equal to 1.
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  This function is called through TOSSetRelAlarm macros.
//                      Checks if the asked period is 2 to power of x compatible.
//                      Initiates the pAlarm period to Cycle value.
//                      Adds the pAlarm task in the TOS_ORD task list.
//                      Refer to Detailed Design Document
//==============================================================================
void TOSSetRelAlarm_Interne( tTOSAlarm* const pAlarm, const tTOSTickAlarm Cycle );

//Callback
//==============================================================================
// DESCRIPTION:         CallBack function for the started LDB timer used by TOS_ALA.
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Activates the tasks which have to be executed in this period.
//                      Refer to Detailed Design Document
//==============================================================================
void TOSAlaCallBackTimer(void);

#endif //I_TOS_ALA_H 
