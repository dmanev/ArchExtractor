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
// Component:    <Name of the component and its variant number, if any>
//               <Comments about the component (role, algorithm, structure,
//               limitations, defined tasks and events...)>
// -----------------------------------------------------------------------------
// $Date:   Apr 22 2009 17:19:34  $
// $Archive::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_FRW/LAP_FRW.h-arc  $
// $Revision:   1.1  $
// -----------------------------------------------------------------------------
// $Log:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_FRW/LAP_FRW.h-arc  $
// 
//    Rev 1.1   Apr 22 2009 17:19:34   amarinm1
// Cm003261: A problem with short wash press detection was fixed.
// 
//    Rev 1.0   Apr 09 2009 14:47:48   amarinm1
// Initial revision.
//******************************************************************************
#endif

#ifndef I_LAP_FRW_H
#define I_LAP_FRW_H

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
    extern BOOL LAPFrwEPStopPositionIsDetected( void );
    extern BOOL LAPFrwWashStopPositionIsDetected( void );
    extern BOOL LAPFrwOutputIsInactive( void );
    extern BOOL LAPFrwOutputIsActive( void );
    extern BOOL LAPFrwInitialWipingTimeoutHasElapsed( void );
    extern void LAPFrwEnableWiping( void );
    extern void LAPFrwTryWiping( void );
    extern void LAPFrwDisableWiping( void );
    extern BOOL LAPFrwDisableTimeoutHasElapsed( void );
    extern BOOL LAPFrwWipingTimeoutHasElapsed( void );
    extern BOOL LAPFrwWipingIsNotRequested( void );
    extern void LAPFrwStopProtectionMode( void );
    extern BOOL LAPFrwINTConditionsToStopArePresent( void );
    extern BOOL LAPFrwINTRequestIsOff( void );
    extern BOOL LAPFrwINTRequestIsOn( void );
    extern void LAPFrwINTStopWiping( void );
    extern BOOL LAPFrwINTPauseHasElapsed( void );
    extern void LAPFrwINTStartWiping( void );
    extern void LAPFrwINTStopTimer( void );
    extern BOOL LAPFrwWashCycleIsFinished( void );
    extern BOOL LAPFrwWashExtraWipeBegining( void );
    extern void LAPFrwWashProlongation( void );
    extern BOOL LAPFrwWashRequestIsOff( void );
    extern BOOL LAPFrwWashRequestIsOn( void );
    extern void LAPFrwStopWashWiping( void );
    extern void LAPFrwSetWashPressType( void );
    extern void LAPFrwInitWashProlongation( void );
    extern void LAPFrwStartWashWiping( void );
    extern void LAPFrwStartWashWait( void );
    extern void LAPFrwStartWashPressTimer( void );
    extern BOOL LAPFrwWashWaitHasElapsed( void );
    extern void LAPFrwArbitration( void );
#endif // _QAC_

void LAPFrwEnterActiveState( void );
void LAPFrwLeaveActiveState( void );
void LAPFrwInitialize( void );                            


#endif   // I_LAP_FRW_H
