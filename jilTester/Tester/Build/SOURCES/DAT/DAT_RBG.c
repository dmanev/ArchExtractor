#ifndef _QAC_
//******************************************************************************
// Company:      Johnson Controls Inc.
// -----------------------------------------------------------------------------
// Copyright:    This software is JCI property.
//               Duplication or disclosure without JCI written authorization
//               is prohibited.
// -----------------------------------------------------------------------------
// Project:      RSA_X90_BCM
// Language:     C
// -----------------------------------------------------------------------------
// Component:   DAT_RBG
// -----------------------------------------------------------------------------
// $Date:   Mar 09 2010 11:10:08  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_RBG/DAT_RBG.c-arc  $
// $Revision:   1.11  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_RBG/DAT_RBG.c-arc  $
// 
//    Rev 1.11   Mar 09 2010 11:10:08   adzhelp
// Cm006631: Code review corrections
// 
//    Rev 1.10   Mar 02 2010 16:20:14   adzhelp
// Cm006631: Decrementing of fault counter performed after 2 s has elapsed AND diag pulse is received
// 
//    Rev 1.9   Jan 21 2010 15:05:48   adzhelp
// Cm007074: Clearing of fault made on start-up
//
//    Rev 1.8   Dec 15 2009 11:56:06   amanevd
// Cm005566: EEP_DefAirbag is never cleared inside the component
//
//    Rev 1.7   Oct 02 2009 10:57:12   aangovt
// Cm005603: Corrections according to code review 1.5
// 
//    Rev 1.6   May 08 2009 16:33:17   aangovt
// Cm004984: Airbag diag pattern is the same with pointed in PRS and patern is not inverted. 
// 
//    Rev 1.5   May 08 2009 14:31:53   aangovt
// Cm004984: Airbag diag pattern is inverted.  
// 
//    Rev 1.4   Apr 25 2009 08:26:02   adzhelp 
// Cm003264: Functions moved to banked memory area
// 
//    Rev 1.3   Apr 22 2009 10:28:57   adzhelp 
// Cm003264: Macros for accessing fault flags updated  
// 
//    Rev 1.2   Apr 21 2009 19:09:51   ailievb 
// Cm003264 Implementation of the Doorlock functionality (Without SDO part)
// Added DATRbgStart and DATRbgStop functiona to stop adn start RBG from DLK component.  
// 
//    Rev 1.1   Apr 15 2009 09:58:47   aangovt
// Cm003264 - New template is added  
// 
//    Rev 1.0   Mar 26 2009 10:24:09   aangovt
// Initial revision. 
//******************************************************************************
#endif

//------------------------------------------------------------------------------
// Body Identification
//------------------------------------------------------------------------------
#define dat_rbg  "dat_rbg"

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//
// #include <system_file_name.h>
// #include "project_file_name.h"
//------------------------------------------------------------------------------
//#include "deftypes.h"
#include "lib.h"
#include "ldb.h"
#include "tos.h"
#include "dat.h"
#include "DAT_RBG.h"


//------------------------------------------------------------------------------
// Local constants
//
// #define cConstantName   ((tType) ConstantValue)
//------------------------------------------------------------------------------
#define cRbgTaskPeriodMs                              ((U8)(  5)) //5ms
#define cMaxNbDefaults                                ((U8)( 30)) //60secs
#define cMinNbPulsesDuringResetTime                   ((U8)(  2))


#define cLowLevelOnSerialLine                         ((BOOL)(0))
 
#define cResetTime                ((U16)(10000/cRbgTaskPeriodMs)) //10sec->2000samples
#define cMaxTimeWithoutDiagPulse  ((U16) (2000/cRbgTaskPeriodMs)) //2sec -> 400samples
#define cMaxCrashPulseTime        ((U16)  (150/cRbgTaskPeriodMs)) //150ms
#define cMinCrashPulseTime        ((U16)   (70/cRbgTaskPeriodMs)) //70ms
#define cMinDiagnosticPulseTime   ((U16)   (30/cRbgTaskPeriodMs)) //33ms rounded to 30ms
#define cMaxDiagnosticPulseTime   ((U16)   (40/cRbgTaskPeriodMs)) //39ms rounded to 40ms

//------------------------------------------------------------------------------
// Local macros
//
// #define mMacroName   (MacroDefinition)
//------------------------------------------------------------------------------
#define mSetFlagAirbagMalfunctionIsDetected()                             \
    mDATWrite(U1Bit, DefAirbag, cTrue, Default);                          \
    /*//QACJ 3412: aangovt: No unrecognized code */                       \
    /*//QACJ 3443: aangovt: No recursion */                               \
    mDATWrite(U1Bit, EEP_DefAirbag, cTrue, Immediate)

#define mResetFlagAirbagMalfunctionIsDetected()                           \
    /*//QACJ 3443: aangovt: No recursion */                               \
    mDATWrite(U1Bit, DefAirbag, cFalse, Default)


#define mSetFlagPermanentLowStateDetected()                               \
    (bPermanentLowStateDetected = cTrue)
#define mResetFlagPermanentLowStateDetected()                             \
    (bPermanentLowStateDetected = cFalse)
#define mFlagPermanentLowStateNotDetected                                 \
    (bPermanentLowStateDetected == cFalse)

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
static  U8 u8AMCounter;  // Airbag Malfunction counter
static U16 u16NbLowLevelSamples;
static U16 u16NbHighLevelSamples;
static U8 u8NbPulseDetectedByResetAirbag;
static U8 u8NbPulseDetectedByAirbag;
static U16 u16ResetTimer;
static U16 u16DecrementAMCounterTimer;
static tTOSAlarm AlarmDATRbgTask;
static BOOL bPermanentLowStateDetected;

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

//------------------------------------------------------------------------------
// Local function prototypes
// 
// static tTypeRetour FunctionName(tTypeArgument1 ArgumentName1, ... );
//------------------------------------------------------------------------------

//==============================================================================
//=========================== LOCAL FUNCTIONS ==================================
//==============================================================================

// [LOCAL_FUNCTIONS_END]


//==============================================================================
//=========================== EXPORTED FUNCTIONS ===============================
//==============================================================================

//==============================================================================
// DESCRIPTION : 
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
void DATRbgInit(void)
{
    u8NbPulseDetectedByResetAirbag = 0;
    u8NbPulseDetectedByAirbag = 0;
    bPermanentLowStateDetected   = cFalse;
    u16ResetTimer                   = cResetTime;
    u16NbLowLevelSamples            = 0;
    u16NbHighLevelSamples           = 0;
    u8AMCounter                  = 0;
    u16DecrementAMCounterTimer = 0;
}

//==============================================================================
// DESCRIPTION         : DATRbgStart
//
// PARAMETERS          : None
//
// RETURN VALUE        : None
//
// DESIGN INFORMATION  : Refer to Detailed Design Document
//
//==============================================================================
MEM_TYPE void DATRbgStart(void)
{
    DATRbgInit();
    mResetFlagAirbagMalfunctionIsDetected();
    //Launch RbgTask
    AlarmDATRbgTask.TaskID = cTOSTaskIdDATRbgTask;
    AlarmDATRbgTask.Period = mTOSConvMsInAlarmTick(cRbgTaskPeriodMs);
    TOSSetRelAlarm (&AlarmDATRbgTask, 0, mTOSConvMsInAlarmTick (cRbgTaskPeriodMs)); 
}

//==============================================================================
// DESCRIPTION         : DATRbgStop
//
// PARAMETERS          : None
//
// RETURN VALUE        : None
//
// DESIGN INFORMATION  : Refer to Detailed Design Document
//
//==============================================================================
MEM_TYPE void DATRbgStop(void)
{
    // init outputs that should not be positioned without Ignition and motor running
    // (won't be read anyway by LAP)
    // Stop RbgTask
    TOSCancelAlarm(&AlarmDATRbgTask);
}

//==============================================================================
// DESCRIPTION : 
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION ::  prsFS_DLK-426,:  prsFS_DLK-427, prsFS_DLK-428, prsFS_DLK-429,prsFS_DLK-430, prsFS_DLK-436, prsFS_DLK-438, prsFS_DLK-510
//==============================================================================
void DATRbgAirbagCrashDetection(void)
{
#ifdef X90_PROJECT
    static MEM_TYPE void DATRbgAirbagCrashDetection_Static(void);
    DATRbgAirbagCrashDetection_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DATRbgAirbagCrashDetection_Static(void)
{
#endif
    // Update counter reset mode
    if(u16ResetTimer > 0)
    {
        u16ResetTimer--;
    }
    else 
    {} //reset mode is over -> nothing to do

    // Management of clearing of defect
    if ((u8AMCounter>0) && (u16DecrementAMCounterTimer > 0))
    {
        u16DecrementAMCounterTimer--;

        if (u16DecrementAMCounterTimer == 0)
        {
            // timer 2 s is elapsed            
            u16DecrementAMCounterTimer = cMaxTimeWithoutDiagPulse;// reload timer

            if (u8NbPulseDetectedByAirbag > 0)
            {
                u8AMCounter--; //decrease default counter when a pulse is detected and 2 s has elapsed
                u8NbPulseDetectedByAirbag = 0;
            }
            else
            {}// do nothing
        }
    }

    if ((mDATRead(U1Bit,AIRBAG_CRASH, Immediate)) == cLowLevelOnSerialLine)
    {
        u16NbLowLevelSamples++;

        // If during 2 seconds no diagnostic pulse is detected, the "Airbag Malfunction" Counter is increased.
        if ( (u16NbLowLevelSamples >= cMaxCrashPulseTime)
        && ((U16)(u16NbLowLevelSamples + u16NbHighLevelSamples) >= cMaxTimeWithoutDiagPulse)
        && (u16ResetTimer == 0))
        {
            if (u8AMCounter < cMaxNbDefaults)
            {
                u8AMCounter++;
            }
            else
            {}
          
            u16NbLowLevelSamples  = 0; //reset counters 
            u16NbHighLevelSamples = 0; 
            mSetFlagPermanentLowStateDetected();

            // prepare timer for defect clearing
            u16DecrementAMCounterTimer = cMaxTimeWithoutDiagPulse;// reload timer for clearing of fault
            u8NbPulseDetectedByAirbag = 0;
        }
        else
        {
            // do nothing
        }
    }
    else
    {
        u16NbHighLevelSamples++;

    //pulse measuring between 33 and 39ms -> diagnostic pulse detected
        if( (u16NbLowLevelSamples >= cMinDiagnosticPulseTime) 
        && (u16NbLowLevelSamples <= cMaxDiagnosticPulseTime)
        && (mFlagPermanentLowStateNotDetected)  )
        {
            // Pulse is detected 
            u8NbPulseDetectedByAirbag++;

            if(u8NbPulseDetectedByResetAirbag < cMinNbPulsesDuringResetTime)//in reset mode
            {
                u8NbPulseDetectedByResetAirbag++;
            }
            else
            {} // do nothing

            u16NbHighLevelSamples = 0; 
       
        }
        else if((u16NbLowLevelSamples >= cMinCrashPulseTime) 
        && (u16NbLowLevelSamples <= cMaxCrashPulseTime)
        && (mFlagPermanentLowStateNotDetected))
        {
            // A crash should be authorized only if APC is on and the key was recognized
            // These conditions don't need to be verified because the component is 
            // started/stopped by LAP depending on Ignition state and key authentication
            TOSSendControl(cTOSControlAirbagUnlock);
        }
        else //pulse smaller than 33ms or between 40 & 70ms or bigger than 150ms
        {
            u16NbHighLevelSamples = u16NbLowLevelSamples + u16NbHighLevelSamples;
        }

        
        if(  (u16NbHighLevelSamples >= cMaxTimeWithoutDiagPulse) //2secs
        && (u16ResetTimer == 0)                              ) //&& not after reset
        { //increase default counter
            if(u8AMCounter < cMaxNbDefaults) 
            {
                u8AMCounter++;
            }
            else
            {} //don't increase if the value is already over its max
            u16NbHighLevelSamples    = 0;

            // prepare timer for defect clearing
            u16DecrementAMCounterTimer = cMaxTimeWithoutDiagPulse;// reload timer for clearing of fault
            u8NbPulseDetectedByAirbag = 0;
        }


        u16NbLowLevelSamples      = 0; //reset flag & counter
        mResetFlagPermanentLowStateDetected();
    }

    //prsFS_DLK-429
    if(  (u8NbPulseDetectedByResetAirbag < cMinNbPulsesDuringResetTime)
    && (u16ResetTimer == 0)  )
    {
        u8AMCounter = cMaxNbDefaults;
        u8NbPulseDetectedByResetAirbag = cMinNbPulsesDuringResetTime;
    }
    else
    {} //nothing to do

    // prsFS_DLK-430 - So when the "Airbag Malfunction" Counter reaches the maximum
    //cMaxNbDefaults = 30 -> 60secs without diagnostic pulse
    if(u8AMCounter == cMaxNbDefaults) //no need >= because already limited above
    {
        mSetFlagAirbagMalfunctionIsDetected();
    }
    else if(u8AMCounter == 0) 
    {
        mResetFlagAirbagMalfunctionIsDetected();
    }
    else
    {
        //maintain last value
    }
}
/* [EXPORTED_FUNCTIONS_END] */
