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
// Component:    DAT_SPD
// -----------------------------------------------------------------------------
// $Date:   Nov 02 2009 09:52:06  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_SPD/DAT_SPD.c-arc  $
// $Revision:   1.1  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_SPD/DAT_SPD.c-arc  $
// 
//    Rev 1.1   Nov 02 2009 09:52:06   adzhelp
// Cm006278: Code review updates and addition of 'available' flags
// 
//    Rev 1.0   Apr 10 2009 15:32:44   aangovt
// Initial revision.
//******************************************************************************
#endif



//------------------------------------------------------------------------------
// Body Identification
//------------------------------------------------------------------------------
#define dat_spd  "dat_spd"

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//
// #include <system_file_name.h>
// #include "project_file_name.h"
//------------------------------------------------------------------------------
#include "deftypes.h"
#include "lib.h"
#include "tos.h"
#include "DAT_SPD.h"
#include "DAT_SPD.hgr"

//------------------------------------------------------------------------------
// Local constants
//
// #define cConstantName   ((tType) ConstantValue)
//------------------------------------------------------------------------------
// reduced with one tick to improve accuracy:
#define  cSpeedPeriod      (mTOSConvMsInTimerTick((U32)720UL) - (tTOSTimer)1U)
#define  cRPMPeriod        (mTOSConvMsInTimerTick((U32)960UL) - (tTOSTimer)1U)


//------------------------------------------------------------------------------
// Local macros
//
// #define mMacroName   (MacroDefinition)
//------------------------------------------------------------------------------

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
static tTOSTimer  RPMTimer;
static tTOSTimer  SpeedTimer;

static tMsg DATSpdMsg;
static U8 Buffer[cLDBSpdMessageLength];

//------------------------------------------------------------------------------
// Constant local data
//
// static const tType  VariableName;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported data
//
// tType   u8LAYCmpVariableName; (LAY: 3 characters to identify the layer)
// tType*  pu8LAYCmpVariableName;(Cmp: 3 characters to identify the component)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Constant exported data
//
//             (LAY: 3 characters to identify the layer)
//             (Cmp: 3 characters to identify this component)
// 
// const tType   LAYCmpVariableName;
//------------------------------------------------------------------------------
BOOL bDATSpdENGINE_RPM;
U8 u8DATSpdVEHICLE_SPEED;
BOOL bDATSpdENGINE_RPMAvailable;
BOOL bDATSpdVEHICLE_SPEEDAvailable;


//------------------------------------------------------------------------------
// Local function prototypes
// 
// static tTypeRetour FunctionName(tTypeArgument1 ArgumentName1, ... );
//------------------------------------------------------------------------------
#ifdef X90_PROJECT
static MEM_TYPE void DATSpdEnterActiveState_Static();
#endif

//==============================================================================
//=========================== LOCAL FUNCTIONS ==================================
//==============================================================================

/* [LOCAL_FUNCTIONS_END] */


//****************************************************************************
//*...........................................................................*
//*........................... EXPORTED FUNCTIONS.............................*
//*...........................................................................*
//****************************************************************************/

//==============================================================================
// DESCRIPTION : 
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none 
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
BOOL DATSpdIsRPMTimeoutIsElapsed(void)
{
    BOOL bTimerElapsedL = TOSIsTimerElapsed(&RPMTimer,cRPMPeriod);
    bTimerElapsedL = bTimerElapsedL;
    return bTimerElapsedL;
}
//==============================================================================
// DESCRIPTION : 
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none 
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
BOOL DATSpdIsSpeedTimeoutIsElapsed(void)
{
    BOOL bTimerElapsedL = TOSIsTimerElapsed(&SpeedTimer,cSpeedPeriod );
    bTimerElapsedL = bTimerElapsedL;
    return bTimerElapsedL;
}
//==============================================================================
// DESCRIPTION : 
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
void DATSpdReceiveRPMState(void)
{
    // Called periodically on 960 ms
    LDBReceiveWithAddr(cLDBChannelSpd, cLDBSpdAddrEngineRpm,  &DATSpdMsg );
    bDATSpdENGINE_RPM = (DATSpdMsg.pBuffer[cLDBSpdEngineRpmIndex] == cLDBSpdEngineRunning);
    bDATSpdENGINE_RPMAvailable = cTrue;
    TOSStartTimer(&RPMTimer);
}
//==============================================================================
// DESCRIPTION : 
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
void DATSpdReseiveSPDState(void)
{
    // Called periodically on 720 ms
    LDBReceiveWithAddr(cLDBChannelSpd, cLDBSpdAddrVehicleSpeed, &DATSpdMsg);
    u8DATSpdVEHICLE_SPEED  = DATSpdMsg.pBuffer[cLDBSpdVehicleSpeedIndex];
    bDATSpdVEHICLE_SPEEDAvailable = cTrue;
    TOSStartTimer(&SpeedTimer);
}

//==============================================================================
// DESCRIPTION : 
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
void DATSpdInit(void)
{
    DATSpdMsg.Lng = cLDBSpdMessageLength;
    DATSpdMsg.pBuffer = Buffer;
}


 
//==============================================================================
// DESCRIPTION : 
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
void DATSpdEnterActiveState(void)
{
#ifdef X90_PROJECT
    DATSpdEnterActiveState_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DATSpdEnterActiveState_Static()
{
#endif
    TOSSeqActivateGraph(cTOSSeqGraphIdSpeedManagement);
    TOSSeqActivateGraph(cTOSSeqGraphIdRPMManagement);
    LDBControl(cLDBChannelSpd, cLDBSpdControlStart);
    TOSStartTimer(&RPMTimer); 
    TOSStartTimer(&SpeedTimer);
    bDATSpdENGINE_RPMAvailable = cFalse;
    bDATSpdVEHICLE_SPEEDAvailable = cFalse;
    bDATSpdENGINE_RPM = cFalse;
    u8DATSpdVEHICLE_SPEED = 0;
}

//==============================================================================
// DESCRIPTION : 
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
void DATSpdLeaveActiveState(void)
{
    TOSSeqDeactivateGraph(cTOSSeqGraphIdSpeedManagement);
    TOSSeqDeactivateGraph(cTOSSeqGraphIdRPMManagement);
    LDBControl(cLDBChannelSpd, cLDBSpdControlStop);
}
/* [EXPORTED_FUNCTIONS_END] */
