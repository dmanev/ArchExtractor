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
// $Date:   Sep 16 2009 16:42:50  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_PWM/DAT_PWMP.H-arc  $
// $Revision:   1.5  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_PWM/DAT_PWMP.H-arc  $
// 
//    Rev 1.5   Sep 16 2009 16:42:50   amarinm1
// Cm005205: Corrections of issues found during the code review.
// 
//    Rev 1.4   Jul 16 2009 09:15:52   adzhelp
// Cm005205: Implementation of roomlamp dimming
// 
//    Rev 1.3   Apr 22 2009 17:15:06   akodzhh
// Cm003128: PWM_ROOMLAMP output state reading for AFS.
// 
//    Rev 1.2   Mar 31 2009 11:33:46   adzhelp
// Cm003517: Roomlamp control by diagnostics according to LAP_TFC implementation
// 
//    Rev 1.1   Feb 25 2009 16:07:18   amarinm1
// Cm003209: Temporary solution for SW1 was implemented.
//
//******************************************************************************

#ifndef I_DAT_PWM_P
#define I_DAT_PWM_P (1)

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//
// #include <system_file_name.h>
// #include "project_file_name.h"
//------------------------------------------------------------------------------
#include "deftypes.h"


//------------------------------------------------------------------------------
// Constant data
//
// #define cLAYCmpConstantName   ((tType) ConstantValue)
//------------------------------------------------------------------------------
#define cPWM_ROOMLAMP_ID     0

#define cDATPwmNumberOfOuput 1


//------------------------------------------------------------------------------
// Exported Macros
//
// #define mLAYCmpMacroName   (MacroDefinition)
//------------------------------------------------------------------------------
#define cDATPwmInitOutputBuffer                                                \
            {                                                                  \
              {cDATPwmInitPWM_ROOMLAMPFreq, cDATPwmInitPWM_ROOMLAMPRatio}      \
            }


//------------------------------------------------------------------------------
// Exported Macros
//
// #define mCMPMacroName   (MacroDefinition)
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Exported type
//
// struct  sLAYCmpStructureName { ... };
// union   uLAYCmpUnionName { ... };
// enum    eLAYCmpEnumerationName { ... };
// typedef Expression tLAYCmpTypeName;
//------------------------------------------------------------------------------
typedef U16 tDATPwmFrequency;

typedef struct 
{
  tDATPwmFrequency Freq; 
  U8               Ratio;
} tDATPwmStruct;


//------------------------------------------------------------------------------
// Functionnal Data exported 
//------------------------------------------------------------------------------

// PWM_ROOMLAMP -- PWM output 1
#ifdef PWM_ROOMLAMP
  #error "Don't define PWM_ROOMLAMP, this token is used for macro concatenation."
#endif
#define cDATPwmInitPWM_ROOMLAMPFreq    ((tDATPwmFrequency) 250)
#define cDATPwmInitPWM_ROOMLAMPRatio   ((U8)  0)

#define mDATReadU16BitPWM_ROOMLAMPFreqDefaut()       (DATPwmSoftBuffer[cPWM_ROOMLAMP_ID].Freq)
#define mDATReadU8BitPWM_ROOMLAMPDefault()      (DATPwmSoftBuffer[cPWM_ROOMLAMP_ID].Ratio)

#define mDATReadU16BitPWM_ROOMLAMPDiagFreqDefaut()   (DATPwmHardBuffer[cPWM_ROOMLAMP_ID].Freq)
#define mDATReadU8BitPWM_ROOMLAMPDiagRatioDefault()  (DATPwmHardBuffer[cPWM_ROOMLAMP_ID].Ratio)

#define mDATReadU1BitPWM_ROOMLAMPDiagMaskDefault()   ((U1)(u8DATPwmDiagMask & 0x01))


#define mDATWriteU16BitPWM_ROOMLAMPFreqDefaut(Value)      \
            DATPwmWriteOutput(cPWM_ROOMLAMP_ID, Value, DATPwmSoftBuffer[cPWM_ROOMLAMP_ID].Ratio)

#define mDATWriteU8BitPWM_ROOMLAMPDefault(Value)     \
            DATPwmWriteOutput(cPWM_ROOMLAMP_ID, DATPwmSoftBuffer[cPWM_ROOMLAMP_ID].Freq, Value)


#define mDATWriteU16BitPWM_ROOMLAMPDiagFreqDefaut(Value)  \
            DATPwmWriteDiagOutput(cPWM_ROOMLAMP_ID, Value, DATPwmHardBuffer[cPWM_ROOMLAMP_ID].Ratio)

#define mDATWriteU8BitPWM_ROOMLAMPDiagRatioDefault(Value) \
            DATPwmWriteDiagOutput(cPWM_ROOMLAMP_ID, DATPwmHardBuffer[cPWM_ROOMLAMP_ID].Freq, Value)


#define mDATWriteU1BitPWM_ROOMLAMPDiagMaskDefault(Value)                       \
            {                                                                  \
                if ((Value & 0x01) == 0)                                       \
                {                                                              \
                    u8DATPwmDiagMask &= 0xFE;                                    \
                    DATPwmWriteOutput(cPWM_ROOMLAMP_ID,                        \
                                      DATPwmSoftBuffer[cPWM_ROOMLAMP_ID].Freq, \
                                      DATPwmSoftBuffer[cPWM_ROOMLAMP_ID].Ratio \
                                     );                                        \
                }                                                              \
                else                                                           \
                {                                                              \
                    u8DATPwmDiagMask |= 0x01;                                    \
                }                                                              \
            }


#endif   // I_DAT_PWM_P
