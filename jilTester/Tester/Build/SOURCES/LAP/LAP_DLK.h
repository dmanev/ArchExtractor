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
// Component:    LAP_DLK
//               Doorlock
// -----------------------------------------------------------------------------
// $Date:   Mar 09 2010 10:01:46  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/DLK/LAP_DLK.h-arc  $
// $Revision:   1.4  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/DLK/LAP_DLK.h-arc  $
// 
//    Rev 1.4   Mar 09 2010 10:01:46   adzhelp
// Cm007644: Code review corrections
// 
//    Rev 1.3   Feb 25 2010 17:34:34   adzhelp
// Cm007212: HWP: Implementation of SC detection of Verlog LED and Doorlock LED in sleep mode
// 
//    Rev 1.2   Jul 07 2009 11:19:04   ailievb
// Cm005132: DLK: 'Master Front Doors unlocking' function do not operate when last RKE is Unlock and key is authorized
// 
//    Rev 1.1   Apr 29 2009 14:43:42   ailievb
// Cm003264:Implementation of the Doorlock functionality (Without SDO part)
// 
//    Rev 1.0   Apr 14 2009 11:00:12   ailievb
// Initial revision.
//
//******************************************************************************

#ifndef I_LAP_DLK_H
#define I_LAP_DLK_H (1)

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//
// #include <system_file_name.h>
// #include "project_file_name.h"
//------------------------------------------------------------------------------
#include "deftypes.h"

//------------------------------------------------------------------------------
// Data prefix for constant & data
//
// unsigned int {u8,u16,u32} / signed int {s8,s16,s32} 
// register size unsigned int {r} / float {f32,f64}  / s for struct 
// no prefix for other types.
//
//------------------------------------------------------------------------------
// Constant data
//
// #define cu16LAYCmpConstantName   ((U16) ConstantValueUL)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported type
//
// typedef Expression tLAYCmpTypeName;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported data
//
// extern  tType   u8LAYCmpVariableName;
// extern  tType*  ps32LAYCmpVariableName; 
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Constant exported data
//
// extern const tType  s8LAYCmpVariableName;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported Macros
//
// #define LAYCmpMacroName(...)   (MacroDefinition)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported functions
//
// extern tReturnType LAYCmpFunctionName(tTypeArgument1 ArgumentName1, ... );
//------------------------------------------------------------------------------
extern void DLKAirbagInformationManagement(void);
extern void DLKCommandCPERelay(void);
extern BOOL DLKCommandIsPending(void);
extern void DLKCommandMotorRelays(void);
extern void DLKDeCommandCPERelay(void);
extern void DLKDeCommandMotorRelays(void);
extern BOOL DLKDebounceTimeOut(void);
extern BOOL DLKIgnitionIsOff(void);
extern BOOL DLKIgnitionIsOnAndKeyWasRecognizedAndMotorIsNotCranking(void);
extern void DLKInputDataManagement(void);
extern BOOL DLKMotorActivationTimeOut(void);
extern BOOL DLKNoRequest(void);
extern void DLKOutputDataManagement(void);
extern void DLKProtectionSleepModeCallBack(void);
extern void DLKStartAirbagAndStartTimer(void);
extern void DLKStopAirbag(void);
extern BOOL DLKIgnitionIsOnAndKeyWasRecognizedAndLWS(void);

#endif   /* I_LAP_DLK_H */
