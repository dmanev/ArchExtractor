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
// Component:    DAT_PWM
// -----------------------------------------------------------------------------
// $Date:   Sep 07 2009 14:37:12  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_PWM/DAT_PWM.H-arc  $
// $Revision:   1.5  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_PWM/DAT_PWM.H-arc  $
// 
//    Rev 1.5   Sep 07 2009 14:37:12   amarinm1
// Cm005205: Corrections of issues found during the code review.
// 
//    Rev 1.4   Aug 25 2009 13:44:06   amarinm1
// Cm005205: Changes for compliance with QAC.
// 
//    Rev 1.3   Jul 16 2009 09:15:52   adzhelp
// Cm005205: Implementation of roomlamp dimming
// 
//    Rev 1.2   Apr 29 2009 12:07:16   adzhelp
// Cm003209: Functions moved to banked memory area
// 
//    Rev 1.1   Feb 25 2009 16:07:16   amarinm1
// Cm003209: Temporary solution for SW1 was implemented.
// 
//    Rev 1.0   02 Dec 2008 15:41:08   ailievb
// Initial revision.
//  
//******************************************************************************

#ifndef I_DAT_PWM_H
#define I_DAT_PWM_H (1)

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//
// #include <system_file_name.h>
// #include "project_file_name.h"
//------------------------------------------------------------------------------
#include "dat_pwmp.h"


//------------------------------------------------------------------------------
// Constant data
//
// #define cLAYCmpConstantName   ((tType) ConstantValue)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported Macros
//
// #define mLAYCmpMacroName   (MacroDefinition)
//------------------------------------------------------------------------------
#define mDATWriteU1BitPWM_ROOMLAMPHardMaskDefaut(Value)                        \
{                                                                              \
    if ( (Value) == 0 )                                                         \
    {                                                                          \
        u8DATPwmHardMask &= 0xFE;                                                \
        DATPwmWriteOutput(cPWM_ROOMLAMP_ID,                                    \
                          DATPwmSoftBuffer[cPWM_ROOMLAMP_ID].Freq,             \
                          DATPwmSoftBuffer[cPWM_ROOMLAMP_ID].Ratio             \
                         );                                                    \
    }                                                                          \
    else                                                                       \
    {                                                                          \
        u8DATPwmHardMask |= 0x01;                                                \
        DATPwmWriteOutput(cPWM_ROOMLAMP_ID,                                    \
                          DATPwmSoftBuffer[cPWM_ROOMLAMP_ID].Freq,             \
                          DATPwmSoftBuffer[cPWM_ROOMLAMP_ID].Ratio             \
                         );                                                    \
    }                                                                          \
}


//------------------------------------------------------------------------------
// Exported type
//
// struct  sLAYCmpStructureName { ... };
// union   uLAYCmpUnionName { ... };
// enum    eLAYCmpEnumerationName { ... };
// typedef Expression tLAYCmpTypeName;
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Exported data
//
// extern  tType   LAYCmpVariableName;
// extern  tType*  pLAYCmpVariableName; 
//------------------------------------------------------------------------------
extern tDATPwmStruct DATPwmSoftBuffer[cDATPwmNumberOfOuput];
extern tDATPwmStruct DATPwmHardBuffer[cDATPwmNumberOfOuput];
extern U8            u8DATPwmDiagMask;
extern U8            u8DATPwmHardMask;


//------------------------------------------------------------------------------
// Constant exported data
//
// extern const tType  LAYCmpVariableName;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported functions
//
// extern tReturnType LAYCmpFunctionName(tTypeArgument1 ArgumentName1, ... );
//------------------------------------------------------------------------------
extern void DATPwmInit(void);
extern MEM_TYPE void DATPwmWriteOutput(const U8 u8PwmOutputIndexP, const tDATPwmFrequency FrequencyP, const U8 u8CyclicRatioP);
extern MEM_TYPE void DATPwmWriteDiagOutput(const U8 u8PwmOutputIndexP, const tDATPwmFrequency FrequencyP, const U8 u8CyclicRatioP);
extern void DATPwmLeaveStartingStepState(void);


#endif   // I_DAT_PWM_H
