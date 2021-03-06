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
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/EXT_CMP/CPP_CMP/STK/SOURCES/TOS_SIG.C-arc  $
// $Revision:   1.1  $
// -----------------------------------------------------------------------------
/* $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/EXT_CMP/CPP_CMP/STK/SOURCES/TOS_SIG.C-arc  $
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
#define TOS_SIG "TOS_SIG"

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------
#include "tos_sig.h"
#include "lib.h"

//------------------------------------------------------------------------------
// Local constants
//------------------------------------------------------------------------------
#define cSizeEventTable         ((cTOSSigMaxSignalNumber + 7UL) / 8UL)
#define cNoEvent                0

//------------------------------------------------------------------------------
// Local macros
//------------------------------------------------------------------------------
#define mGetIndex( SignalID )   ( (SignalID) >> 3 )
#define mGetMask( SignalID )    ( (U8) ( (U8)1 << ((SignalID) & 7) ) )

//------------------------------------------------------------------------------
// Local types
//------------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// Local data
//------------------------------------------------------------------------------
static U8 u8EventTable[cSizeEventTable];    // container for events

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

//==============================================================================
//=========================== LOCAL FUNCTIONS ==================================
//==============================================================================

//==============================================================================
//=========================== EXPORTED FUNCTIONS ===============================
//==============================================================================

//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
void TOSSigInitialize( void )
{
    mLIBmemset( u8EventTable, cNoEvent, sizeof(u8EventTable) );
}

//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
CALLT_TYPE BOOL TOSReadSignal(const tTOSSignalID SignalId )
{
    BOOL bActiveSignal;

    TOSSuspendOSInterrupts();
    if( (u8EventTable[ mGetIndex(SignalId) ] & mGetMask(SignalId)) != 0 )
    {
        u8EventTable[ mGetIndex(SignalId) ] &= (U8) ~mGetMask(SignalId);
        bActiveSignal = cTrue;
    }
    else
    {
        bActiveSignal = cFalse;
    }
    TOSResumeOSInterrupts();

    return bActiveSignal;
}

//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
CALLT_TYPE void TOSWriteSignal(const tTOSSignalID SignalId )
{
    TOSSuspendOSInterrupts();
    u8EventTable[ mGetIndex(SignalId) ] |= mGetMask(SignalId);
    TOSResumeOSInterrupts();
}
