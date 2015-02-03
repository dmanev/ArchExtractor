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
// $Date:   Oct 01 2009 11:52:36  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_PWM/DAT_PWM.C-arc  $
// $Revision:   1.11  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_PWM/DAT_PWM.C-arc  $
// 
//    Rev 1.11   Oct 01 2009 11:52:36   amarinm1
// Cm006370: Limit values for ILL PWM changed according to the new HSI.
// 
//    Rev 1.10   Sep 07 2009 14:37:12   amarinm1
// Cm005205: Corrections of issues found during the code review.
// 
//    Rev 1.9   Aug 25 2009 13:44:06   amarinm1
// Cm005205: Changes for compliance with QAC.
// 
//    Rev 1.8   Aug 18 2009 09:47:42   adzhelp
// Cm005205: Corrections to respect padHSI-510 (the rule of 5%-95%)
// 
//    Rev 1.7   Jul 16 2009 09:15:52   adzhelp
// Cm005205: Implementation of roomlamp dimming
// 
//    Rev 1.6   Apr 29 2009 12:07:16   adzhelp
// Cm003209: Functions moved to banked memory area
// 
//    Rev 1.5   Apr 22 2009 17:15:06   akodzhh
// Cm003128: PWM_ROOMLAMP output state reading for AFS.
// 
//    Rev 1.4   Mar 31 2009 11:02:00   adzhelp
// Cm003517: Roomlamp control by diagnostics according to LAP_TFC implementation
// 
//    Rev 1.3   Mar 10 2009 17:40:42   amarinm1
// Cm003209: Two lines were commented to avoid compilator warnings.
// 
//    Rev 1.2   Mar 10 2009 17:30:12   amarinm1
// Cm003209: Problems in the previous revision were fixed.
// 
//    Rev 1.1   Feb 25 2009 16:07:16   amarinm1
// Cm003209: Temporary solution for SW1 was implemented.
// 
//    Rev 1.0   02 Dec 2008 15:41:08   ailievb
// Initial revision.
//
//******************************************************************************

//------------------------------------------------------------------------------
// Body Identification
//------------------------------------------------------------------------------
#define dat_pwm   "dat_pwm"


//------------------------------------------------------------------------------
// Included files
//
// #include <system_file_name.h>
// #include "project_file_name.h"
//------------------------------------------------------------------------------
#include "lib.h"
#include "tos.h"
#include "dat.h"
#include "dat_pwm.h"


//------------------------------------------------------------------------------
//  Local constants
//
//  #define cConstantName   ((tType) ConstantValue)
//------------------------------------------------------------------------------
// length of DAT buffer to LDB in bytes
#define cDatMessageLength       ((U16)3)

// Limits of cyclic ratio adjusted to respect padHSI-510 (the rule of 5%-95%):
#define cMaximalCyclicRatio     ((U8)95)
#define cMinimalCyclicRatio     ((U8)4)

#define cFullOutputRation       ((U8)100)


//------------------------------------------------------------------------------
// Local macros
//
// #define mMacroName   (MacroDefinition)
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Local types
//
// struct  sStructureName { ... };
// union   uUnionName { ... };
// enum    eEnumerationName { ... };
// typedef Expression tTypeName;
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Local data
//
// static  tType   VariableName;
// static  tType*  pVariableName; 
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Constant local data
//
// static const tType  VariableName;
//------------------------------------------------------------------------------
//QACJ 3207: amarinm1: Variable is used in DATPwmInit().
static const tDATPwmStruct InitPwmBuffer[cDATPwmNumberOfOuput] = 
                                                        cDATPwmInitOutputBuffer;


//------------------------------------------------------------------------------
// Exported data
//
// tType   LAYCmpVariableName;   (LAY: 3 characters to identify the layer)
// tType*  pLAYCmpVariableName;  (Cmp: 3 characters to identify this component)
//------------------------------------------------------------------------------
tDATPwmStruct DATPwmSoftBuffer[cDATPwmNumberOfOuput];
tDATPwmStruct DATPwmHardBuffer[cDATPwmNumberOfOuput];
U8            u8DATPwmDiagMask;
U8            u8DATPwmHardMask;


//------------------------------------------------------------------------------
// Constant exported data
//
// (LAY: 3 characters to identify the layer)
// (Cmp: 3 characters to identify this component)
// 
// const tType   LAYCmpVariableName;
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Local function prototypes
//  
// static tTypeRetour FunctionName(tTypeArgument1 ArgumentName1, ... );
//------------------------------------------------------------------------------


//============================================================================
//=========================== LOCAL FUNCTIONS ================================
//============================================================================

//==============================================================================
//  DESCRIPTION :
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//==============================================================================
//static type FunctionName(...)


//============================================================================
//=========================== EXPORTED FUNCTIONS =============================
//============================================================================

//==============================================================================
//  DESCRIPTION :
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//==============================================================================
void DATPwmInit(void)
{
    u8DATPwmDiagMask = 0;
    u8DATPwmHardMask = 0;
    mLIBmemcpy( DATPwmSoftBuffer, InitPwmBuffer, (sizeof(tDATPwmStruct)*cDATPwmNumberOfOuput) );
    mLIBmemcpy( DATPwmHardBuffer, InitPwmBuffer, (sizeof(tDATPwmStruct)*cDATPwmNumberOfOuput) );
}


//==============================================================================
//  DESCRIPTION :
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//==============================================================================
MEM_TYPE void DATPwmWriteOutput(const U8 u8PwmOutputIndexP, const tDATPwmFrequency FrequencyP, const U8 u8CyclicRatioP)
{
    tMsg Msg;

    mLIBassert( FrequencyP != 0 );
    
    DATPwmSoftBuffer[u8PwmOutputIndexP].Freq  = FrequencyP;
    DATPwmSoftBuffer[u8PwmOutputIndexP].Ratio = u8CyclicRatioP;
    
    if ( (u8DATPwmDiagMask & (U8)(1 << u8PwmOutputIndexP) ) == 0)
    {
        DATPwmHardBuffer[u8PwmOutputIndexP].Freq  = DATPwmSoftBuffer[u8PwmOutputIndexP].Freq;

        if (   ( u8CyclicRatioP < cMinimalCyclicRatio)
            || ((u8DATPwmHardMask & (U8)(1 << u8PwmOutputIndexP)) != 0)   )
        {
            DATPwmHardBuffer[u8PwmOutputIndexP].Ratio = 0;
        }
        else if ( u8CyclicRatioP > cMaximalCyclicRatio )
        {
            DATPwmHardBuffer[u8PwmOutputIndexP].Ratio = cFullOutputRation;
        }
        else
        {
            DATPwmHardBuffer[u8PwmOutputIndexP].Ratio = DATPwmSoftBuffer[u8PwmOutputIndexP].Ratio;
        }
    }
    
    Msg.Lng = cDatMessageLength;
    //QACJ 0310: amarinm1: Standart procedure, the array is then casted to its original type.
    Msg.pBuffer = (U8 *) &DATPwmHardBuffer[u8PwmOutputIndexP];
    LDBSendWithAddr(cLDBChannelPwm, u8PwmOutputIndexP, &Msg);
}


//==============================================================================
//  DESCRIPTION :
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//==============================================================================
MEM_TYPE void DATPwmWriteDiagOutput(const U8 u8PwmOutputIndexP, const tDATPwmFrequency FrequencyP, const U8 u8CyclicRatioP)
{
    tMsg Msg;

    mLIBassert( (u8DATPwmDiagMask & (1 << u8PwmOutputIndexP)) != 0 );
    mLIBassert( FrequencyP != 0 );
    
    DATPwmHardBuffer[u8PwmOutputIndexP].Freq = FrequencyP;
    
    if (   ( u8CyclicRatioP < cMinimalCyclicRatio )
        || ((u8DATPwmHardMask & (U8)(1 << u8PwmOutputIndexP)) != 0)   )
    {
        DATPwmHardBuffer[u8PwmOutputIndexP].Ratio = 0;
    }
    else if ( u8CyclicRatioP > cMaximalCyclicRatio )
    {
        DATPwmHardBuffer[u8PwmOutputIndexP].Ratio = cFullOutputRation;
    }
    else
    {
        DATPwmHardBuffer[u8PwmOutputIndexP].Ratio = u8CyclicRatioP;
    }

    Msg.Lng = cDatMessageLength;
    //QACJ 0310: amarinm1: Standart procedure, the array is then casted to its original type.
    Msg.pBuffer = (U8 *) &DATPwmHardBuffer[u8PwmOutputIndexP];
    LDBSendWithAddr(cLDBChannelPwm, u8PwmOutputIndexP, &Msg);
}


//==============================================================================
//  DESCRIPTION :
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//==============================================================================
//QACJ 3206: amarinm1: Both parameters are used for Assert checks.
void DATPwmCallBackTxWithAddr(const tAddress Ad, const tStatus Status)
{
    mLIBassert(Status == cLDBCorrect);
    mLIBassert(Ad < cDATPwmNumberOfOuput);
}


//==============================================================================
//  DESCRIPTION :
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//==============================================================================
void DATPwmLeaveStartingStepState(void)
{
    U8 u8Index;

    //QACJ 2465: amarinm1: Done like this for flexibility.
    for(u8Index = 0; u8Index < cDATPwmNumberOfOuput; u8Index++)
    {
        DATPwmWriteOutput(u8Index, 
                          DATPwmSoftBuffer[u8Index].Freq, 
                          DATPwmSoftBuffer[u8Index].Ratio
                         );
    }
}

