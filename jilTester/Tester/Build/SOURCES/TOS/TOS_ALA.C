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
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/EXT_CMP/CPP_CMP/STK/SOURCES/TOS_ALA.C-arc  $
// $Revision:   1.0  $
// -----------------------------------------------------------------------------
/* $Log:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/EXT_CMP/CPP_CMP/STK/SOURCES/TOS_ALA.C-arc  $
// 
//    Rev 1.0   04 Feb 2009 17:03:04   adzhelp
// Initial revision.
*/
//******************************************************************************

//------------------------------------------------------------------------------
// Body Identification
//------------------------------------------------------------------------------
#define TOS_ALA "TOS_ALA"

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------
#include "tos_ala.h"
#include "tos_ord.h"
#include "ldb_tos.h"
#include "lib.h"

//------------------------------------------------------------------------------
// Local constants
//------------------------------------------------------------------------------
//This constant defines the number of slot available
#define cNbSlot ((U8)8)

//This constant defines the period of designed for Alarm management LDB timer
#define cPeriodeTempoLDB    cPeriodTimerLDB
#define cPeriodTimerLDB     ((U32) ((U32)cTOSTickAlarmUs * (U16)1000L) / \
                            (cLDBTick * (U8)2L) )

//------------------------------------------------------------------------------
// Local macros
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Local types
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Local data
//------------------------------------------------------------------------------
static tTOSTickAlarm    AlarmState;
static tTOSTickAlarm    AlarmCycle;
static tTOSOrdTaskList  TasksList[cNbSlot];

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
// DESCRIPTION         : Returns the slot Id corresponding to input parameter 
//                       Duration.
//
// PARAMETERS          : Duration - this parameter can only take
//                                  value of 2 to the power of x.
//
// RETURN VALUE        : U8
//
// DESIGN INFORMATION  : Checks if Duration is different from 0.
//                       Returns the position of the first bit to 1 of the tick counter, starting
//                       with the less significant bit.
     
//==============================================================================
static U8 GetSlot( tTOSTickAlarm Duration);

//==============================================================================
//=========================== LOCAL FUNCTIONS ==================================
//==============================================================================
static U8 GetSlot( tTOSTickAlarm Duration )
{
    U8 u8SlotID = 0;

    // Checks if Duration is different from 0
    mLIBassert(Duration != 0);
    while( (Duration & 1) == 0 )
    {
        u8SlotID++;
        Duration >>= 1;
    }

    return u8SlotID;
}

//==============================================================================
//=========================== EXPORTED FUNCTIONS ===============================
//==============================================================================

//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
void TOSAlaInitialize(void)
{
    U8 u8NbSlot;
    AlarmState = 0;
    for (u8NbSlot = 0;u8NbSlot < cNbSlot;u8NbSlot++)
    {
        TOSOrdClearTaskList(&TasksList[u8NbSlot]);
    }
}

//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
void TOSStartAlarm(void)
{
    TOSStartSlowestAlarms(1);
}

//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
void TOSStartSlowestAlarms(const tTOSTickAlarm MinimumCycle)
{
    //check if cTOSTickAlarmUs is a 2-multiple of cLDBTick
    mLIBassert( (cPeriodTimerLDB * (U8)2L * cLDBTick) ==  
                ((U32)1000L * cTOSTickAlarmUs) );

    AlarmCycle = MinimumCycle;
    AlarmState &= (tTOSTickAlarm) ~((tTOSTickAlarm)(AlarmCycle - 1));

    LDBStartTimer(
                  cTOSTimerLdbDesignedForALA,
                  TOSAlaCallBackTimer,
                  ((LDBPARAM_DELAY_TYPE)( ((LDBPARAM_DELAY_TYPE)cPeriodTimerLDB)
                  * ((LDBPARAM_DELAY_TYPE)MinimumCycle))),
                  cTrue
                 );
}

//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
void TOSStopAlarm(void)
{
    LDBPARAM_DELAY_TYPE Res = LDBStopTimer( cTOSTimerLdbDesignedForALA );
}

//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
void TOSSetRelAlarm_Interne( tTOSAlarmType const pAlarm, const tTOSTickAlarm Cycle )
{
    U8 u8SlotID;
    
    if (pAlarm != NULL)
    {
        u8SlotID = GetSlot( Cycle );
        
        // Check if the asked period is 2 to power of x compatible.
        mLIBassert( ((tTOSTickAlarm)1 << u8SlotID) == Cycle );
        
        pAlarm->Period = Cycle;
        
        TOSSuspendOSInterrupts();
        TOSOrdAddTaskToList(&TasksList[u8SlotID],pAlarm->TaskID);
        TOSResumeOSInterrupts();
    }
}

//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
void TOSCancelAlarm( const tTOSAlarm* const pAlarm )
{
    U8 u8SlotID;

    if (pAlarm != NULL)
    {
        u8SlotID = GetSlot( pAlarm->Period );
        
        // Check if the asked period is 2 to power of x compatible.
        mLIBassert( ((tTOSTickAlarm)1 << u8SlotID) == pAlarm->Period );
        
        TOSSuspendOSInterrupts();
        TOSOrdRemoveTaskFromList(&TasksList[u8SlotID],pAlarm->TaskID);
        TOSOrdSuspendTask(pAlarm->TaskID);
        TOSResumeOSInterrupts();
    }
}

//==============================================================================
// DESCRIPTION:         See component header file
//==============================================================================
void TOSAlaCallBackTimer(void)
{
    AlarmState = ((tTOSTickAlarm) (AlarmCycle + AlarmState));
    if( AlarmState != 0)
    {
        U8 u8SlotID = GetSlot( AlarmState );
        TOSOrdActivateTaskList( &TasksList[u8SlotID] );
    }
}

