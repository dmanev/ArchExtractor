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
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_SPD/DAT_SPD.h-arc  $
// $Revision:   1.1  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_SPD/DAT_SPD.h-arc  $
// 
//    Rev 1.1   Nov 02 2009 09:52:06   adzhelp
// Cm006278: Code review updates and addition of 'available' flags
// 
//    Rev 1.0   Apr 10 2009 15:32:44   aangovt
// Initial revision.
//******************************************************************************
#endif

#ifndef I_dat_spd_H
#define I_dat_spd_H (1)

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
extern BOOL bDATSpdENGINE_RPM;
extern U8 u8DATSpdVEHICLE_SPEED;
extern BOOL bDATSpdENGINE_RPMAvailable;
extern BOOL bDATSpdVEHICLE_SPEEDAvailable;

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
//////////////////////////////////////////////////////////////////////////
// Inputs not defined in Ana and Dio
//////////////////////////////////////////////////////////////////////////
#define mDATReadU1BitENGINE_RPMDefault() bDATSpdENGINE_RPM
#define mDATReadU1BitENGINE_RUNNINGDefault() mDATReadU1BitENGINE_RPMDefault() 
#define mDATReadU1BitENGINE_RPMAvailableDefault() bDATSpdENGINE_RPMAvailable

#define mDATReadU8BitVEHICLE_SPEEDDefault() u8DATSpdVEHICLE_SPEED
#define mDATReadU8BitVEH_SPEEDDefault() mDATReadU8BitVEHICLE_SPEEDDefault() 
#define mDATReadU1BitVEHICLE_SPEEDAvailableDefault() bDATSpdVEHICLE_SPEEDAvailable

//------------------------------------------------------------------------------
// Exported functions
//
// extern tReturnType LAYCmpFunctionName(tTypeArgument1 ArgumentName1, ... );
//------------------------------------------------------------------------------
extern void DATSpdInit(void);
extern void DATSpdLeaveActiveState(void);
extern void DATSpdEnterActiveState(void);
#ifndef _QAC_
extern BOOL DATSpdIsRPMTimeoutIsElapsed(void);
extern BOOL DATSpdIsSpeedTimeoutIsElapsed(void);
extern void DATSpdReceiveRPMState(void);
extern void DATSpdReseiveSPDState(void);
#endif
/* [EXPORTED_FUNCTIONS_END] */
#endif   /* I_dat_spd_H */

