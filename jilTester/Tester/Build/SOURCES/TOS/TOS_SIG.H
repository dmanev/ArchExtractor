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
// Component:    TOS_SIG
//               TOS signals management
// -----------------------------------------------------------------------------
// $Date:   Sep 17 2009 10:27:10  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/EXT_CMP/CPP_CMP/STK/SOURCES/TOS_SIG.H-arc  $
// $Revision:   1.1  $
// -----------------------------------------------------------------------------
/* $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/EXT_CMP/CPP_CMP/STK/SOURCES/TOS_SIG.H-arc  $
// 
//    Rev 1.1   Sep 17 2009 10:27:10   adzhelp
// Cm003277: Functions defined as CALLT_TYPE
// 
//    Rev 1.0   04 Feb 2009 17:03:08   adzhelp
// Initial revision.
*/
//******************************************************************************

#ifndef I_TOS_SIG_H
#define I_TOS_SIG_H

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
// DESCRIPTION:         Initializes the TOS_SIG component
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Resets all events
//                      Refer to Detailed Design Document
//==============================================================================
void TOSSigInitialize( void );

//==============================================================================
// DESCRIPTION:         Reads a specific signal
//
// PARAMETERS:          SignalId    - Signal to be read
//
// RETURN VALUE:        cTrue when the given signal is set, else cFalse
//
// DESIGN INFORMATION:  Reads the state of requested signal in events' table.
//                      If signal's value is TRUE returns TRUE and resets it,
//                      otherwise returns FALSE.
//                      Refer to Detailed Design Document
//==============================================================================
CALLT_TYPE BOOL TOSReadSignal(const tTOSSignalID SignalId );

//==============================================================================
// DESCRIPTION:         Writes a specific signal
//
// PARAMETERS:          SignalId    - Signal to be written
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Sets the state of requested signal in events' table.
//                      Refer to Detailed Design Document
//==============================================================================
CALLT_TYPE void TOSWriteSignal(const tTOSSignalID SignalId );

#endif // I_TOS_SIG_H
