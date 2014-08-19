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
// Component:    LAP_ILL
// -----------------------------------------------------------------------------
// $Date:   Mar 04 2010 15:12:40  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/ILL/LAP_ILL.c-arc  $
// $Revision:   1.23  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/ILL/LAP_ILL.c-arc  $
// 
//    Rev 1.23   Mar 04 2010 15:12:40   adzhelp
// Cm006814: QAC corrections
// 
//    Rev 1.22   Mar 02 2010 10:34:02   adzhelp
// Cm006814: TPS_APC, TPS_PLAF normalized
// 
//    Rev 1.21   Feb 19 2010 10:19:08   adzhelp
// Cm007575: No wake-up if flag 'BcmSleepRequested' set
// 
//    Rev 1.20   Jan 19 2010 11:43:58   adzhelp
// Cm006834: Lighting timeout restarted by next unlock
// 
//    Rev 1.19   Jan 15 2010 15:57:44   adzhelp
// Cm006829, Cm006636: Active state is not maintained when lighting is active
// 
//    Rev 1.18   Nov 02 2009 18:58:28   amarinm1
// Cm006581: Elapsed TPS_PLAF now triggers gradual turn-off.
// 
//    Rev 1.17   Nov 02 2009 17:29:38   amarinm1
// Cm006499: Power relay is now cut when leaving active state.
// 
//    Rev 1.16   Nov 02 2009 11:46:44   adzhelp
// Cm006587: Clearing of flags added when switch off lights
// 
//    Rev 1.15   Oct 05 2009 11:46:24   amarinm1
// Cm006413: Dimming process is now interruptable.
// 
//    Rev 1.14   Oct 01 2009 15:18:22   amarinm1
// Cm006282: Integration modifications.
// 
//    Rev 1.13   Oct 01 2009 11:39:04   amarinm1
// Cm006282: Starting the power relay is now done in LeaveStartingStepState too.
// 
//    Rev 1.12   Oct 01 2009 10:28:50   amarinm1
// Cm006370: Dimming times and algorhythm changed to adapt to low levels PWM.
// 
//    Rev 1.11   Sep 15 2009 13:53:12   amarinm1
// Cm005593: u8TPS_APCStepCounter is initialized every time PowerRelayCtrlTimeOut is started.
// 
//    Rev 1.10   Jul 10 2009 09:22:34   adzhelp
// Cm005104, Cm004985: Set ALIM PLAF to 1 with immediate acess on wakeup
// 
//    Rev 1.9   Jun 26 2009 11:41:18   amarinm1
// Cm005023: Bug fixed;
// Problems found during the code review were fixed;
// 
//    Rev 1.8   May 07 2009 14:54:32   ailievb
// Cm004928: Internal Light: Bad management after several RKE Lock/unlock requests
// 
//    Rev 1.7   Apr 29 2009 14:18:56   adzhelp
// Cm003209: Functions moved to banked memory area
// 
//    Rev 1.6   23 Apr 2009 12:13:10   amarinm1
// Cm003209: ALIM_PLAF was made independent of AUTPLAF;
// ALIM_PLAF changing from 0 to 1 activates the power output without any other conditions;
// 
//    Rev 1.5   Mar 30 2009 17:52:50   amarinm1
// Cm003209: The power relay timer was corrected so it can handle times bigger than the limit of U16 timer.
// Cm004676: A timeout for the gradual turn off was changed because the component graphs were set to 20ms execution.
// 
//    Rev 1.4   Jan 06 2009 14:23:18   amarinm1
// Cm003209: Interior Lights component development.
// PVCS header comments were changed.
// 
//    Rev 1.3   Jan 06 2009 12:20:22   amarinm1
// Cm003209: Interior Lights component development.
// File updated to copmly with new QAC restrictions.
// 
//    Rev 1.2   Dec 03 2008 14:21:16   amarinm1
// Files updated to use the new method for indicating edges with TOS signals. Also the names of some EEP variables were changed.
// 
//    Rev 1.1   02 Dec 2008 16:18:26   ailievb
// LAP_ILL integration.
// 
//    Rev 1.0   Nov 24 2008 14:24:02   amarinm1
// Initial revision.
//
//******************************************************************************
#endif // _QAC_

//------------------------------------------------------------------------------
// Body Identification
//------------------------------------------------------------------------------
#define LAP_ILL   "LAP_ILL"


//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//
// #include <system_file_name.h>
// #include "project_file_name.h"
//------------------------------------------------------------------------------
#include "lib.h"
#include "tos.h"
#include "dat.h" //to be uncommented if needed
#include "lap_ill.h"
#include "lap_ill.hgr"

//------------------------------------------------------------------------------
// Local constants
//
// #define cConstantName   ((tType) ConstantValue)
//------------------------------------------------------------------------------
#define cLowPartStepTimeoutInMs      (20UL)
#define cHighPartStepTimeoutInMs     (100UL)
#define cLowHighBorderInPercents     ((U8)80UL)
#define cInternalLightsMaxOutput     ((U8)100UL)

// Limits of cyclic ratio adjusted to respect padHSI-510 (the rule of 5%-95%)
// These macros should be synchronized with the ones in DAT_PWM.c
// 95 corresponds to 96% in LDB_PWM which is its first step.
#define cMaximalCyclicRatio     ((U8)95)
#define cMinimalCyclicRatio     ((U8)4)

#define cTpsPlafStepInMs      (800UL)
#define cTpsApcStepInMs       (50000UL)

#define cLightingOff          ((U8)0)
#define cLightingOn           ((U8)1)

//------------------------------------------------------------------------------
// Local macros
//
// #define mMacroName   (MacroDefinition)
//------------------------------------------------------------------------------
#define mSetLightsOnTriggerEvent()                                             \
          (InternalLights.LightsOnTriggerEvent = cTrue)
#define mClearLightsOnTriggerEvent()                                           \
          (InternalLights.LightsOnTriggerEvent = cFalse)
#define mReadLightsOnTriggerEvent()                                            \
          ((BOOL)(InternalLights.LightsOnTriggerEvent == cTrue))

#define mSetLightsOffTriggerEvent()                                            \
          (InternalLights.LightsOffTriggerEvent = cTrue)
#define mClearLightsOffTriggerEvent()                                          \
          (InternalLights.LightsOffTriggerEvent = cFalse)
#define mReadLightsOffTriggerEvent()                                           \
          ((BOOL)(InternalLights.LightsOffTriggerEvent == cTrue))

#define mSetLightsGraduallyOffTriggerEvent()                                   \
          (InternalLights.LightsGraduallyOffTriggerEvent = cTrue)
#define mClearLightsGraduallyOffTriggerEvent()                                 \
          (InternalLights.LightsGraduallyOffTriggerEvent = cFalse)
#define mReadLightsGraduallyOffTriggerEvent()                                  \
          ((BOOL)(InternalLights.LightsGraduallyOffTriggerEvent == cTrue))

#define mSetDoorsLockedTriggerEvent()                                          \
          (bDoorsLockedTriggerEvent = cTrue)
#define mClearDoorsLockedTriggerEvent()                                        \
          (bDoorsLockedTriggerEvent = cFalse)
#define mReadDoorsLockedTriggerEvent()                                         \
          ((BOOL)(bDoorsLockedTriggerEvent == cTrue))

#define mSetDoorsUnlockedTriggerEvent()                                        \
          (bDoorsUnlockedTriggerEvent = cTrue)
#define mClearDoorsUnlockedTriggerEvent()                                      \
          (bDoorsUnlockedTriggerEvent = cFalse)
#define mReadDoorsUnlockedTriggerEvent()                                       \
          ((BOOL)(bDoorsUnlockedTriggerEvent == cTrue))

#define mReadTPS_APCStepInTimerTicks                                           \
    mTOSConvMsInTimerTick(cTpsApcStepInMs)

#define cLowPartStepTimeoutInTimerTicks()                                      \
    (mTOSConvMsInTimerTick(cLowPartStepTimeoutInMs) - (tTOSTimer)1U)

#define cHighPartStepTimeoutInTimerTicks()                                     \
    (mTOSConvMsInTimerTick(cHighPartStepTimeoutInMs) - (tTOSTimer)1U)

#define mAllDoorsAreClosed()                                                   \
 ((BOOL)(  (mDATRead(U1Bit, RR_DOORS_SW, Default) == 0)                        \
/* //QACJ 3443: amarinm1: No recursion in the definition! */                   \
        && (mDATRead(U1Bit, FR_DOORS_SW, Default) == 0)))

#define mADoorIsOpened()                                                       \
 ((BOOL)(  (mDATRead(U1Bit, RR_DOORS_SW, Default) == 1)                        \
/* //QACJ 3443: amarinm1: No recursion in the definition! */                   \
        || (mDATRead(U1Bit, FR_DOORS_SW, Default) == 1)))

#define mIgnitionRisingEdgeIsPresent()                                         \
 (TOSReadSignal(cTOSSignalRising_PWR_IGN_LAP_ILL))

#define mIgnitionFallingEdgeIsPresent()                                        \
 (TOSReadSignal(cTOSSignalFalling_PWR_IGN_LAP_ILL))

#define mFrontDoorsChangingStateEventIsPresent()                               \
 (TOSReadSignal(cTOSSignalChanging_FR_DOORS_SW_LAP_ILL))

#define mRearDoorsChangingStateEventIsPresent()                                \
 (TOSReadSignal(cTOSSignalChanging_RR_DOORS_SW_LAP_ILL))  

//------------------------------------------------------------------------------
// Local types
//
// typedef Expression    tTypeName;
//------------------------------------------------------------------------------
typedef struct tInternalLightingStructure
{
    tTOSTimer LightsOnTimeOut;
    U8        State;
    BOOL      LightsOnTriggerEvent;
    BOOL      LightsOffTriggerEvent;
    BOOL      LightsGraduallyOffTriggerEvent;
} sInternalLigthingStructure;


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

static sInternalLigthingStructure InternalLights;

static tTOSTimer    LogicalLightingTimeOut;
static tTOSTimer    LightsGraduallyOffDelay;
static tTOSTimer    PowerRelayCtrlTimeOut;

static U8           u8TPS_APCStepCounter;

static BOOL         bDoorsUnlockedTriggerEvent;
static BOOL         bDoorsLockedTriggerEvent;
static BOOL         bComponentIsEnabled;
static BOOL         bALIM_PLAF_memo;
static BOOL         bPowerRelayStopIsAllowed;



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
static MEM_TYPE void LightingPowerRelayManagement (void);
static MEM_TYPE void DisableFunctionallity        (void);
static MEM_TYPE void ResumeAfterDisable           (void);
static MEM_TYPE void LAPIllInitPowerRelay         (void);

#ifdef X90_PROJECT
static MEM_TYPE void LAPIllInitialize_Static(void);
static MEM_TYPE void LAPIllEnterActiveState_Static(void);
static MEM_TYPE void LAPIllLeaveActiveState_Static(void);
static MEM_TYPE BOOL LAPIllLightsOnRequestIsTrue_Static(void);
static MEM_TYPE BOOL LAPIllLightsOffRequestIsTrue_Static(void);
static MEM_TYPE BOOL LAPIllLightsGraduallyOffRequestIsTrue_Static(void);
static MEM_TYPE void LAPIllLightsGraduallyOffExecution_Static(void);
#endif

//==============================================================================
//=========================== LOCAL FUNCTIONS ==================================
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
static MEM_TYPE void LightingPowerRelayManagement (void)
{
    BOOL bPowerRelayTimerIsStartedL;
    BOOL bPowerRelayTimerIsElapsedL;
    BOOL bDoorsChangingStateIsPresentL;
    BOOL bIgnitionRisingEdgeIsPresentL;
    BOOL bIgnitionFallingEdgeIsPresentL;

    if (mDATRead(U1Bit, EEP_ALIM_PLAF, Default) == 0)
    {
        mDATWrite(U1Bit, BAT_LIGHT_TEMPO, 0, Default);
        TOSStopTimer(&PowerRelayCtrlTimeOut);

        bALIM_PLAF_memo = 0;
    }
    else
    {
        bDoorsChangingStateIsPresentL  = 
            mFrontDoorsChangingStateEventIsPresent();
        bDoorsChangingStateIsPresentL |= mRearDoorsChangingStateEventIsPresent();
        bIgnitionFallingEdgeIsPresentL = mIgnitionFallingEdgeIsPresent();

        if (   (bDoorsChangingStateIsPresentL   == cTrue) 
            || (bIgnitionFallingEdgeIsPresentL  == cTrue) )
        {
            mDATWrite(U1Bit, BAT_LIGHT_TEMPO, 1, Default);
            TOSStopTimer(&PowerRelayCtrlTimeOut);
            TOSStartTimer(&PowerRelayCtrlTimeOut);
            bPowerRelayStopIsAllowed = cFalse;
            u8TPS_APCStepCounter = 0;
        }
        else
        {
            bIgnitionRisingEdgeIsPresentL = mIgnitionRisingEdgeIsPresent();

            if (bIgnitionRisingEdgeIsPresentL == cTrue)
            {
                mDATWrite(U1Bit, BAT_LIGHT_TEMPO, 1, Default);
                TOSStopTimer(&PowerRelayCtrlTimeOut);                
                bPowerRelayStopIsAllowed = cFalse;
            }
            else
            {
                bPowerRelayTimerIsStartedL = 
                    TOSIsTimerStarted(&PowerRelayCtrlTimeOut);
                bPowerRelayTimerIsElapsedL = 
                    TOSIsTimerElapsed(&PowerRelayCtrlTimeOut, mReadTPS_APCStepInTimerTicks);
              
                if (bPowerRelayTimerIsStartedL && bPowerRelayTimerIsElapsedL)
                {
                    u8TPS_APCStepCounter++;
                    TOSStartTimer(&PowerRelayCtrlTimeOut);
                    
                    if (u8TPS_APCStepCounter >= mDATRead(U8Bit, NEEP_TPS_APC, Default))
                    {
                        bPowerRelayStopIsAllowed = cTrue;
                        TOSStopTimer(&PowerRelayCtrlTimeOut);
                    }
                    else
                    {
                        // Do nothing
                    }
                }
                else
                {
                    // Power relay output has just been enabled
                    if ( bALIM_PLAF_memo == 0 )
                    {
                        mDATWrite(U1Bit, BAT_LIGHT_TEMPO, 1, Default);
                        TOSStartTimer(&PowerRelayCtrlTimeOut);                        
                        bPowerRelayStopIsAllowed = cFalse;
                        u8TPS_APCStepCounter = 0;
                    }
                    else
                    {
                        // Do nothing
                    }
                }
            }
        }

        bALIM_PLAF_memo = 1;
    }
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
static MEM_TYPE void DisableFunctionallity(void)
{
    TOSSeqDeactivateGraph(cTOSSeqGraphIdLAPIllInternalLightsController);

    LAPIllLightsOffExecution();

    TOSStopTimer(&PowerRelayCtrlTimeOut);
    TOSStopTimer(&LightsGraduallyOffDelay);  

    bComponentIsEnabled = cFalse;
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
static MEM_TYPE void ResumeAfterDisable(void)
{
    if (mDATRead(U1Bit, EEP_ALIM_PLAF, Default) == 0)
    {
        mDATWrite(U1Bit, BAT_LIGHT_TEMPO, 0, Default);
    }
    else
    {
        mDATWrite(U1Bit, BAT_LIGHT_TEMPO, 1, Default);
        TOSStartTimer(&PowerRelayCtrlTimeOut);
        bPowerRelayStopIsAllowed = cFalse;
        u8TPS_APCStepCounter = 0;
    }

    InternalLights.LightsOnTimeOut  = 0;
    InternalLights.State            = cLightingOff;
    mClearLightsOnTriggerEvent();
    mClearLightsOffTriggerEvent();
    mClearLightsGraduallyOffTriggerEvent();
    mClearDoorsLockedTriggerEvent();
    mClearDoorsUnlockedTriggerEvent();

    TOSSeqActivateGraph(cTOSSeqGraphIdLAPIllInternalLightsController);

    bComponentIsEnabled = cTrue;
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
static MEM_TYPE void LAPIllInitPowerRelay(void)
{    
    if (mDATRead(U1Bit, EEP_ALIM_PLAF, Default) == 0)
    {
        mDATWrite(U1Bit, BAT_LIGHT_TEMPO, 0, Default);
        bALIM_PLAF_memo = 0;
    }
    else
    {
        mDATWrite(U1Bit, BAT_LIGHT_TEMPO, 1, Immediate);
        TOSStartTimer(&PowerRelayCtrlTimeOut);
        bPowerRelayStopIsAllowed = cFalse;
        u8TPS_APCStepCounter = 0;
        bALIM_PLAF_memo = 1;
    }
}


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
void LAPIllInitialize(void)
{
#ifdef X90_PROJECT
    LAPIllInitialize_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPIllInitialize_Static(void)
{
#endif
    PowerRelayCtrlTimeOut           = 0;
    u8TPS_APCStepCounter            = 0;
    InternalLights.LightsOnTimeOut  = 0;
    InternalLights.State            = cLightingOff;

    mClearLightsOnTriggerEvent();
    mClearLightsOffTriggerEvent();
    mClearLightsGraduallyOffTriggerEvent();
    mClearDoorsLockedTriggerEvent();
    mClearDoorsUnlockedTriggerEvent();
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
void LAPIllLeaveStartingStepState(void)
{
    if (mDATRead(U1Bit, BcmSleepRequested, Default) == cFalse)
    {
        // BCM wakes up if EEP_ALIM_PLAF is set

        LAPIllInitPowerRelay();

        if (mDATRead(U1Bit, BAT_LIGHT_TEMPO, Default) != cFalse)
        {
            TOSSendControl(cTOSControlWakeUpRequest);
        }
    }
    else
    {
        mDATWrite(U1Bit, BcmSleepRequested, cFalse, Default);
        // do not wake up
    }
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
void LAPIllEnterActiveState(void)
{
#ifdef X90_PROJECT
    LAPIllEnterActiveState_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPIllEnterActiveState_Static(void)
{
#endif
    
    LAPIllInitPowerRelay();

    if (mDATRead(U1Bit, EEP_AUTPLAF, Default) == 1)
    {
        mClearDoorsLockedTriggerEvent();
        mClearDoorsUnlockedTriggerEvent();

        TOSSeqActivateGraph(cTOSSeqGraphIdLAPIllInternalLightsController);

        bComponentIsEnabled = cTrue;
    }
    else // AUTPLAF = 0, component is disabled
    {        
        bComponentIsEnabled = cFalse;
    }
    TOSSeqActivateGraph(cTOSSeqGraphIdLAPIllInternalLightsManagement);
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
void LAPIllLeaveActiveState(void)
{
#ifdef X90_PROJECT
    LAPIllLeaveActiveState_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPIllLeaveActiveState_Static(void)
{
#endif
    if (bComponentIsEnabled == cTrue)
    {
        TOSSeqDeactivateGraph(cTOSSeqGraphIdLAPIllInternalLightsManagement);
        TOSSeqDeactivateGraph(cTOSSeqGraphIdLAPIllInternalLightsController);

        LAPIllLightsOffExecution();

        TOSStopTimer(&PowerRelayCtrlTimeOut);
        TOSStopTimer(&LightsGraduallyOffDelay); 
    }
    else
    {
        TOSSeqDeactivateGraph(cTOSSeqGraphIdLAPIllInternalLightsManagement);
    }
     
    mDATWrite(U1Bit, BAT_LIGHT_TEMPO, 0, Default);
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
void LAPIllIsAnybodyMaintainActiveState(void)
{
    if (  (mDATRead(U1Bit, BAT_LIGHT_TEMPO, Default) == 0)
        ||(bPowerRelayStopIsAllowed == cTrue)   
       )
    {
      // Do nothing
    }
    else
    {
        TOSWriteSignal(cTOSSignalSomebodyMaintainActiveState);
    }
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
void LAPIllManagement(void)
{
    if (mDATRead(U1Bit, EEP_AUTPLAF, Default) == 1)
    {
        if (bComponentIsEnabled == cFalse)
        {
            ResumeAfterDisable();
        }
        else
        {
            // Do nothing
        }
    }
    else // AUTPLAF = 0, Internal Lights disabled
    {
        if (bComponentIsEnabled == cTrue)
        {
            DisableFunctionallity();
        }
        else
        {
            // Do nothing
        }
        
    }

    LightingPowerRelayManagement();
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
BOOL LAPIllLightsOnRequestIsTrue(void)
{
#ifdef X90_PROJECT
    return LAPIllLightsOnRequestIsTrue_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL LAPIllLightsOnRequestIsTrue_Static(void)
{
#endif

    if (mADoorIsOpened() == cTrue) 
    {
        mSetLightsOnTriggerEvent();
    }
    else 
    {
        if (   (mDATRead(U1Bit, EEP_PIL_PLAF, Default) == 1)
            && (mReadDoorsUnlockedTriggerEvent() == cTrue) )
        {
            mSetLightsOnTriggerEvent();
            InternalLights.LightsOnTimeOut = 
            
            // Max(NEEP_TPS_PLAF) * Step fits in U16
            mTOSConvMsInTimerTick
                ((U32)((U16)mDATRead(U8Bit,NEEP_TPS_PLAF,Default) *
                                                             (U16)cTpsPlafStepInMs ));
            TOSStartTimer(&LogicalLightingTimeOut);
            mClearDoorsUnlockedTriggerEvent();
        }
        else
        {
            // Do nothing
        }
    }
        
    return (mReadLightsOnTriggerEvent());
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
void LAPIllLightsOnExecution(void)
{
    mDATWrite(U8Bit, PWM_ROOMLAMP, cInternalLightsMaxOutput, Default);
    InternalLights.State = cLightingOn;
    mClearLightsOnTriggerEvent();
    mClearLightsOffTriggerEvent();
    mClearLightsGraduallyOffTriggerEvent();
    // In case of interrupted dimming cycle
    TOSStopTimer(&LightsGraduallyOffDelay);
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
BOOL LAPIllLightsOffRequestIsTrue(void)
{
#ifdef X90_PROJECT
    return LAPIllLightsOffRequestIsTrue_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL LAPIllLightsOffRequestIsTrue_Static(void)
{
#endif

    if (mAllDoorsAreClosed() == cTrue)
    {
        if (mDATRead(U1Bit, EEP_PIL_PLAF, Default) == 0)
        {
            mSetLightsOffTriggerEvent();
        }
        else // PIL_PLAF == 1
        {
            if (   (mDATRead(U1Bit, PWR_IGN, Default) == 0)
                && (mReadDoorsLockedTriggerEvent() == cTrue)   )
            {
                mSetLightsOffTriggerEvent();
                mClearDoorsLockedTriggerEvent();                    
            }
            else
            {
                // Do nothing
            }
        }
    }
    else
    {
        TOSStopTimer(&LogicalLightingTimeOut);
    }

    return (mReadLightsOffTriggerEvent() == cTrue);
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
BOOL LAPIllLightsGraduallyOffRequestIsTrue(void)
{
#ifdef X90_PROJECT
    return LAPIllLightsGraduallyOffRequestIsTrue_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL LAPIllLightsGraduallyOffRequestIsTrue_Static(void)
{
#endif

    BOOL bLightsOnTimerIsStarted;
    BOOL bLightsOnTimerIsElapsed;

    if (   (mDATRead(U1Bit, EEP_PIL_PLAF, Default) ==     1)
        && (mAllDoorsAreClosed()                   == cTrue)   )
    {
        if (mDATRead(U1Bit, PWR_IGN, Default) == 0)
        {
            bLightsOnTimerIsStarted = 
                TOSIsTimerStarted(&LogicalLightingTimeOut);
            bLightsOnTimerIsElapsed = 
                TOSIsTimerElapsed(&LogicalLightingTimeOut, 
                                   InternalLights.LightsOnTimeOut);

            if (   (bLightsOnTimerIsStarted == cTrue)
                && (bLightsOnTimerIsElapsed == cTrue) )    
            {
                mSetLightsGraduallyOffTriggerEvent();
                TOSStopTimer(&LogicalLightingTimeOut);
            }
            else
            {
                if (bLightsOnTimerIsStarted == cFalse)
                {
                    InternalLights.LightsOnTimeOut = 
                    
                    // Max(NEEP_TPS_PLAF) * Step fits in U16
                    mTOSConvMsInTimerTick
                    ((U32)((U16)mDATRead(U8Bit, NEEP_TPS_PLAF, Default) *
                                                     (U16)cTpsPlafStepInMs ));
                    TOSStartTimer(&LogicalLightingTimeOut);
                }
                else if (mReadDoorsUnlockedTriggerEvent() != cFalse)
                {
                    // Restart of lighting timeout due to unlock
                    TOSStartTimer(&LogicalLightingTimeOut);
                    mClearDoorsUnlockedTriggerEvent();                        
                }
                else
                {
                    // Do nothing
                }
            }
        }
        else // (mDATRead(U1Bit, PWR_IGN, Default) == 1)
        {
            mSetLightsGraduallyOffTriggerEvent();
        }
    }
    else
    {
        // Do nothing
    }
    
    return (mReadLightsGraduallyOffTriggerEvent() == cTrue);
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
void LAPIllLightsOffExecution(void)
{
    mDATWrite(U8Bit, PWM_ROOMLAMP, 0, Default);
    InternalLights.State = cLightingOff;
    mClearLightsOnTriggerEvent();
    mClearLightsOffTriggerEvent();
    mClearLightsGraduallyOffTriggerEvent();
    mClearDoorsUnlockedTriggerEvent();
    mClearDoorsLockedTriggerEvent();
    TOSStopTimer(&LogicalLightingTimeOut);
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
void LAPIllLightsGraduallyOffExecution(void)
{
#ifdef X90_PROJECT
    LAPIllLightsGraduallyOffExecution_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPIllLightsGraduallyOffExecution_Static(void)
{
#endif

    U8   u8TempValue;
    BOOL bTimeoutElapsed;

    if (mDATRead(U8Bit, PWM_ROOMLAMP, Default) < cLowHighBorderInPercents)                                                       
    {
        bTimeoutElapsed = 
            TOSIsTimerElapsed(&LightsGraduallyOffDelay, 
                              cLowPartStepTimeoutInTimerTicks());
    }
    else
    {
        bTimeoutElapsed = 
            TOSIsTimerElapsed(&LightsGraduallyOffDelay, 
                              cHighPartStepTimeoutInTimerTicks());
    }

    if (bTimeoutElapsed == cTrue)
    {
        u8TempValue = mDATRead(U8Bit, PWM_ROOMLAMP, Default);
        if (u8TempValue > cMaximalCyclicRatio) 
        {
            u8TempValue = cMaximalCyclicRatio;
            mDATWrite(U8Bit, PWM_ROOMLAMP, u8TempValue, Default);
            TOSStopTimer(&LightsGraduallyOffDelay);
            TOSStartTimer(&LightsGraduallyOffDelay); 
        }
        else if (u8TempValue <= cMinimalCyclicRatio) 
        {
            u8TempValue = 0;
            mDATWrite(U8Bit, PWM_ROOMLAMP, u8TempValue, Default);
            TOSStopTimer(&LightsGraduallyOffDelay);
            InternalLights.State = cLightingOff;
            mClearLightsOnTriggerEvent();
            mClearLightsOffTriggerEvent();
            mClearLightsGraduallyOffTriggerEvent();
            TOSStopTimer(&LogicalLightingTimeOut);
        }
        else // Value in the working range
        {
            u8TempValue--;
            mDATWrite(U8Bit, PWM_ROOMLAMP, u8TempValue, Default);
            TOSStopTimer(&LightsGraduallyOffDelay);
            TOSStartTimer(&LightsGraduallyOffDelay); 
        }
    }
    else
    {
        // Do nothing
    }
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
BOOL LAPIllGradualOffIsInProgress(void)
{
    return (mDATRead(U8Bit, PWM_ROOMLAMP, Default) != 0);
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
BOOL LAPIllLightsAreOff(void)
{
    return (mDATRead(U8Bit, PWM_ROOMLAMP, Default) == 0);
}


//==============================================================================
// DESCRIPTION :
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : The doors are closed because the control is sending only
// if the door are closed
//==============================================================================
void LAPIllRKELock(void)
{
    mSetDoorsLockedTriggerEvent(); 
    mClearDoorsUnlockedTriggerEvent();
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
void LAPIllRKEUnlock(void)
{
    mSetDoorsUnlockedTriggerEvent();
    mClearDoorsLockedTriggerEvent();
//QACJ 0862: amarinm1: .hgr file is automatically included when generating the .c file with the Graph Designer
}
