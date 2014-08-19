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
// $Date:   Nov 06 2009 15:09:50  $
// $Archive::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_RRW/LAP_RRW.h-arc  $
// $Revision:   1.2  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_RRW/LAP_RRW.h-arc  $
// 
//    Rev 1.2   Nov 06 2009 15:09:50   amarinm1
// Cm006421: Second condition for initial parking was added.
// 
//    Rev 1.1   Oct 14 2009 15:24:58   amarinm1
// Cm006421: Initial parking was implemented.
// 
//    Rev 1.0   Sep 04 2009 16:55:22   amarinm1
// Initial revision.
// 
//******************************************************************************
#endif

#ifndef I_LAP_RRW_H
#define I_LAP_RRW_H

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------

// This is an example:
// Reduce to minimum the inclusions!!!
// #include <system_file_name.h>
// #include "project_file_name.h"

//------------------------------------------------------------------------------
// Constant data
//------------------------------------------------------------------------------

// This is an example:
// #define cu16LAYCmpConstantName   ((U16)ConstantValue)

//------------------------------------------------------------------------------
// Exported type
//------------------------------------------------------------------------------

// This is an example:
// typedef Expression tLAYCmpTypeName;

//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------

// This is an example:
// Reduce to minimum the usage of extern data members!!!
// extern  tType   LAYCmpVariableName;
// extern  tType*  pLAYCmpVariableName;
// extern  U8      u8LAYCmpVariableName;
// extern  U16*    pu16LAYCmpVariableName;

//------------------------------------------------------------------------------
// Constant exported data
//------------------------------------------------------------------------------

// This is an example:
// Reduce to minimum the usage of extern constant data members!!!
// extern const tType  cLAYCmpConstantName;
// extern const U32    cu32LAYCmpConstantName;

//------------------------------------------------------------------------------
// Exported Macros
//------------------------------------------------------------------------------

// This is an example:
// #define LAYCmpMacroName(...)   (MacroDefinition)

//------------------------------------------------------------------------------
// Exported functions
//------------------------------------------------------------------------------

#ifndef _QAC_
    extern BOOL LAPRrwEPStopPositionIsDetected( void );
    extern BOOL LAPRrwWashStopPositionIsDetected( void );
    extern BOOL LAPRrwOutputIsInactive( void );
    extern BOOL LAPRrwOutputIsActive( void );
    extern BOOL LAPRrwInitialWipingTimeoutHasElapsed( void );
    extern void LAPRrwEnableWiping( void );
    extern void LAPRrwTryWiping( void );
    extern void LAPRrwDisableWiping( void );
    extern BOOL LAPRrwDisableTimeoutHasElapsed( void );
    extern BOOL LAPRrwWipingTimeoutHasElapsed( void );
    extern BOOL LAPRrwWipingIsNotRequested( void );
    extern void LAPRrwStopProtectionMode( void );
    extern BOOL LAPRrwINTConditionsToStopArePresent( void );
    extern BOOL LAPRrwINTRequestIsOff( void );
    extern BOOL LAPRrwINTRequestIsOn( void );
    extern void LAPRrwINTStopWiping( void );
    extern BOOL LAPRrwINTPauseHasElapsed( void );
    extern void LAPRrwINTStartWiping( void );
    extern void LAPRrwINTStopTimer( void );
    extern BOOL LAPRrwWashCycleIsFinished( void );
    extern BOOL LAPRrwWashExtraWipeBegining( void );
    extern void LAPRrwWashProlongation( void );
    extern BOOL LAPRrwWashRequestIsOff( void );
    extern BOOL LAPRrwWashRequestIsOn( void );
    extern void LAPRrwStopWashWiping( void );
    extern void LAPRrwSetWashPressType( void );
    extern void LAPRrwInitWashProlongation( void );
    extern void LAPRrwStartWashWiping( void );
    extern void LAPRrwStartWashWait( void );
    extern void LAPRrwStartWashPressTimer( void );
    extern BOOL LAPRrwWashWaitHasElapsed( void );
    extern void LAPRrwArbitration( void );
    extern BOOL LAPRrwWiperIsInSpeedPosition( void );
    extern BOOL LAPRrwWiperIsInStopPosition( void );
    extern void LAPRrwStartParking( void );
    extern BOOL LAPRrwStopPositionHasBeenReached( void );
    extern void LAPRrwStopParking( void );
#endif // _QAC_

void LAPRrwEnterActiveState( void );
void LAPRrwLeaveActiveState( void );
void LAPRrwInitialize( void );                            


#endif   // I_LAP_RRW_H
