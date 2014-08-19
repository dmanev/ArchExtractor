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
// Component:    LAP_PAL
// -----------------------------------------------------------------------------
// $Date:   Oct 05 2009 17:45:20  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_PAL/LAP_PAL.h-arc  $
// $Revision:   1.1  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_PAL/LAP_PAL.h-arc  $
// 
//    Rev 1.1   Oct 05 2009 17:45:20   aangovt
// Cm006425: Corrections after code review.
// 
//    Rev 1.0   Sep 09 2009 15:54:28   aangovt
// Initial revision.
//******************************************************************************
#endif

#ifndef I_LAP_PAL_H
#define I_LAP_PAL_H (1)

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

// This is an example:
// tType LAYCmpFunctionName( tTypeArgument1 ArgumentName1, ... );


extern BOOL LAPPalAlarmInhibited(void);
extern BOOL LAPPalIgnitionTurnsOff(void);
extern void LAPPalInitializeDisableMode(void);
extern void LAPPalInitializeStandbyMode(void);
extern BOOL LAPPalIsOneAlarmConditionActivated(void);
extern BOOL LAPPalRfLock(void);
extern BOOL LAPPalRfUnlockOrKeyIsRecognised(void);
extern void LAPPalStop(void);
extern void LAPPalUpdateAlarmDiagnostic(void);
extern BOOL LAPPalEndOfActivation(void);
extern void LAPPalEndOfAlarmCycle(void);
extern BOOL LAPPalNextAlarmCycle(void);
extern BOOL LAPPalEndOfAlarmActivation(void);
extern BOOL LAPPalActivate(void);
extern void LAPPalFalling_RR_DOORS_SW(void);
extern void LAPPalFalling_FR_DOORS_SW(void);
extern void LAPPalFalling_PWR_IGN(void);
extern void LAPPalRising_FR_DOORS_SW(void);
extern void LAPPalRising_RR_DOORS_SW(void);
extern void LAPPalRising_PWR_IGN(void);
extern void LAPPalLeaveActiveState(void);
extern void LAPPalEnterActiveState(void);
extern void LAPPalInitialize(void);
extern void LAPPalIsAnybodyMaintainActiveState(void);
extern void LAPPalKeyIsAuthenticated(void);
extern void LAPPalLockFromTheOutside(void);
extern void LAPPalUnlockFromTheOutside(void);
extern void LAPPalRfAlarmOff(void);
extern void LAPPalLeaveStartingStepState(void);
extern BOOL LAPPalHornActivationFinished(void);
#endif   /* I_LAP_PAL_H */
