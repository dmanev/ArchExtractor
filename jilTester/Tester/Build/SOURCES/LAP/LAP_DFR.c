#ifndef _QAC_
//******************************************************************************
// Company:      Johnson Controls Inc.
// -----------------------------------------------------------------------------
// Copyright:    This software is JCI property.
//               Duplication or disclosure without JCI written authorization
//               is prohibited.
// -----------------------------------------------------------------------------
// Project:      X90_BCM
// Language:     C
// -----------------------------------------------------------------------------
// Component:    LAP_DFR
// -----------------------------------------------------------------------------
// $Log:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/DFR/LAP_DFR.c-arc  $
// 
//    Rev 1.23   Apr 13 2010 12:18:50   adzhelp
// Cm008191: Defroster cannot be active when ignition is off
// 
//    Rev 1.22   Mar 11 2010 17:51:02   amanevd
// Cm006814: Code review fixes - no binary code impact
// 
//    Rev 1.21   Mar 02 2010 10:41:36   adzhelp
// Cm006814: TPS_TEMPO_DEG normalized
// 
//    Rev 1.20   Feb 11 2010 17:31:32   adzhelp
// Cm006567: False activation on falling ignition corrected
// 
//    Rev 1.19   Feb 10 2010 16:46:48   amanevd
// Cm007075: Volatile Faults and Deprotection cleared at IGN ON
// 
//    Rev 1.18   Feb 05 2010 15:21:28   adzhelp
// Cm006567: Defroster activation/deactivation on switch input rising edge.
// 
//    Rev 1.17   Feb 05 2010 11:21:16   adzhelp
// Cm005590: Implementation of activation delay 1 s
// 
//    Rev 1.16   Jan 07 2010 15:25:50   amanevd
// Cm005566: Horn fault is detected and memorized at the same time
// 
//    Rev 1.15   Dec 15 2009 10:49:46   amanevd
// Cm005566: Include PWR_IGN==1 condition in DEFROSTER SC detection
// 
//    Rev 1.14   Dec 14 2009 11:02:16   amanevd
// Cm005566: Full Hardware Protection
// 
//    Rev 1.13   Nov 04 2009 16:26:50   adzhelp
// Cm005566: Implementation of HW Protection
// 
//    Rev 1.12   Nov 02 2009 09:49:18   adzhelp
// Cm006278: Integration test corrections
// 
//    Rev 1.11   Oct 01 2009 13:53:18   aangovt
// Cm006278: Defroster behavior after reset
// 
//    Rev 1.10   Apr 29 2009 14:08:52   adzhelp
// Cm003270: Functions moved to banked memory area
// 
//    Rev 1.9   Apr 07 2009 17:02:38   aangovt
// Cm003270: Changes after QAC analysis
// 
//    Rev 1.8   Apr 07 2009 11:56:56   adzhelp
// Cm003270: Integration test corrections
//
//******************************************************************************
#endif

//------------------------------------------------------------------------------
// Body Identification
//------------------------------------------------------------------------------
#define LAP_DFR  "LAP_DFR"

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//
// #include <system_file_name.h>
// #include "project_file_name.h"
//------------------------------------------------------------------------------
#include "dat.h"
#include "deftypes.h"
#include "lib.h"
#include "tos.h"
#include "LAP_DFR.h"
#include "LAP_DFR.hgr"

//------------------------------------------------------------------------------
// Local constants
//
// #define cConstantName   ((tType) ConstantValue)
//------------------------------------------------------------------------------
#define cInhibit              (0)
#define cAuthorize            (1)
#define cDefrostTimeout       (50000UL)  //50 s
#define cActivationDelay      (1000UL)   //1 s

// HW Protection
#define cFaultCountWarnThreshold    ((U8) 2U)
#define cFaultCountProtectThreshold ((U8) 4U)

#define cMaxU8                      ((U8) 0xFFU)

#define cDefrostTimeoutInTimerTick    (mTOSConvMsInTimerTick((U32)cDefrostTimeout))
#define cActivationDelayInTimerTick   (mTOSConvMsInTimerTick((U32)cActivationDelay))

//------------------------------------------------------------------------------
// Local macros
//
// #define mMacroName   (MacroDefinition)
//------------------------------------------------------------------------------
#define mIsButtonRaisingEdge() \
    (   (bPreviousButtonState == cFalse) \
    /*//QACJ 3443: adzhelp: Standard STK macro used */\
     && (mDATRead(U1Bit, DEFROSTER_SW_FILTERED, Default) != cFalse) )
#define mRefreshButtonState() \
    /*//QACJ 3443: adzhelp: Standard STK macro used */\
    (bPreviousButtonState = mDATRead(U1Bit, DEFROSTER_SW_FILTERED, Default))

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
static tTOSTimer    TempoDefrostTimeout; 
static tTOSTimer    ActivationTimer;
static BOOL     bActivationDelayElapsed = cFalse;
static BOOL     bReadyToSleep = cTrue;
static BOOL     bPreviousButtonState = cFalse;
static U8       u8DFRStepTimeoutCounter = 0;
static BOOL     bActivateAfterReset = cFalse;
static BOOL     bPwrIgnAfterReset = cFalse;

// HW Protection
static BOOL     bPWR_IGNOld;
static BOOL     bDefrosterStopped;
static U8       u8DfrFaultCounter;
static U8       u8HrnFaultCounter;

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
#ifdef X90_PROJECT
static MEM_TYPE BOOL LAPDfrCommandOff_Static(void);
static MEM_TYPE BOOL LAPDfrCommandOn_Static(void);
static MEM_TYPE void LAPDfrProtectionTask_Static(void);
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
BOOL LAPDfrCommandOff(void)
{
#ifdef X90_PROJECT
    return LAPDfrCommandOff_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL LAPDfrCommandOff_Static(void)
{
#endif

    BOOL bDFRTimeElapsedL;
    BOOL bDeactivationFlagL;
    BOOL bReturnValueL = cFalse;

    if (mDATRead(U1Bit,EEP_AUTDEGIVRAGE,Default) == cAuthorize)
    {
    #ifdef X90_PROJECT
        //adzhelp: 5 NOPs added so that object file produced from rev. 1.22 to be identical with 1.23
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
    #endif
        
        bDeactivationFlagL = (BOOL)
            ((mDATRead(U1Bit,PWR_IGN,Default) == 0)  // prsFS_RDEF-422
            || 
            ((mDATRead(U1Bit,ENGINE_RPM,Default) == 0) &&
            (mDATRead(U1Bit, EEP_INFO_REGIME, Default)== 1) ));
                             
        bDFRTimeElapsedL = TOSIsTimerElapsed(&TempoDefrostTimeout, cDefrostTimeoutInTimerTick);

        if(bDFRTimeElapsedL != cFalse)
        {
            u8DFRStepTimeoutCounter--;
            TOSStartTimer(&TempoDefrostTimeout);
        }
 
        if( 
            (bDeactivationFlagL != cFalse)
            || (u8DFRStepTimeoutCounter == 0)
            || mIsButtonRaisingEdge()
         )
        {
            bReturnValueL = cTrue;
        }

        if (mDATRead(U1Bit, EEP_INFO_REGIME, Default)== 1)
        {        
            // Behaviour after reset
            if (mDATRead(U1Bit, ENGINE_RPMAvailable, Default) == cFalse)
            {
                bReturnValueL = cFalse; // keep output on after reset during RPM signal not measured
            }
            // Update activation timer state
            if (mDATRead(U1Bit,ENGINE_RPM,Default) == cFalse)
            {
                TOSStopTimer(&ActivationTimer);
                bActivationDelayElapsed = cFalse;
            }
        }
        else // EEP_INFO_REGIME = 0
        {
            if (bPwrIgnAfterReset != cFalse)
            {
                bReturnValueL = cFalse; // keep output on after reset during PWR_IGN signal not filtered

                if (mDATRead(U1Bit, PWR_IGN, Default) != cFalse)
                {
                    bPwrIgnAfterReset = cFalse; // clear flag
                }
                else
                {
                    // wait for filtered value of PWR_IGN to become '1'
                }
            }
        }
        mRefreshButtonState();
    }
    else
    {
        bReturnValueL = cTrue; // deactivate output
    }
 
	
    return bReturnValueL;
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
BOOL LAPDfrCommandOn(void)
{
#ifdef X90_PROJECT
    return LAPDfrCommandOn_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL LAPDfrCommandOn_Static(void)
{
#endif
    BOOL bReturnValueL = cFalse;
    BOOL bTimerStartedL;
    BOOL bTimerElapsedL;

    if (bActivateAfterReset != cFalse)
    {
        mLIBassert(mDATRead(U1Bit,EEP_AUTDEGIVRAGE,Default) == cAuthorize);
        
    #ifdef X90_PROJECT
        //adzhelp: 6 NOPs added so that object file produced from rev. 1.22 to be identical with 1.23
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
    #endif
        if (mDATRead(U1Bit,PWR_IGN,Immediate) == 0) //prsFS_RDEF-422
        {
            // Do not activate output
            mDATWrite(U1Bit, EEP_DefrosterActivationState, 0, Default);
            bActivateAfterReset = cFalse;
        }
        else
        {
            //non-filtered state of ignition is on
            //CCOV: adzhelp: Cannot be covered in unit test environment
            if (mDATRead(U1Bit,PWR_IGN,Default) != 0)
            {
                // activate output after filtered value of ignition is on
                bReturnValueL = cTrue;
            }
            bPwrIgnAfterReset = cTrue;
        }
    }
    else if (mDATRead(U1Bit,EEP_AUTDEGIVRAGE,Default) == cAuthorize)
    {
        if (mDATRead(U1Bit, EEP_INFO_REGIME, Default) != cFalse)
        {
            // Defroster activated on engine status

            if (bActivationDelayElapsed != cFalse)
            {
                if (mDATRead(U1Bit, ENGINE_RPM, Default) != cFalse)
                {
                    bReturnValueL = mIsButtonRaisingEdge();
                }
                else
                {
                    bActivationDelayElapsed = cFalse;
                }
            }
            else
            {
                //prsFS_RDEF-287 - Delay for activation
                bTimerStartedL = TOSIsTimerStarted(&ActivationTimer);

                if (bTimerStartedL == cFalse)
                {
                    if (mDATRead(U1Bit, ENGINE_RPM, Default) != cFalse)
                    {
                        TOSStartTimer(&ActivationTimer);
                    }
                    else
                    {
                        // wait for activation of engine
                    }
                }
                else
                {
                    bTimerElapsedL = 
                        TOSIsTimerElapsed(&ActivationTimer, cActivationDelayInTimerTick);

                    if (bTimerElapsedL != cFalse)
                    {
                        bActivationDelayElapsed = cTrue;
                        bReturnValueL = mIsButtonRaisingEdge();
                    }
                    else if (mDATRead(U1Bit, ENGINE_RPM, Default) == cFalse)
                    {
                        // engine stopped during activation timeout
                        TOSStopTimer(&ActivationTimer);
                    }
                    else
                    {
                        // wait for activation timeout: ignore defrosting request
                    }
                }
            }
        }
        else
        {
            // Defroster activated on ignition status
            bReturnValueL = (BOOL)
                ((mDATRead(U1Bit,PWR_IGN,Default) != cFalse) &&
                  mIsButtonRaisingEdge());
            
            TOSStopTimer(&ActivationTimer);
            bActivationDelayElapsed = cFalse;
        }
        mRefreshButtonState();
    }
    else
    {
        // Function not authorized
        TOSStopTimer(&ActivationTimer);
        bActivationDelayElapsed = cFalse;
    }
    return bReturnValueL;
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
void LAPDfrOff(void)
{
#ifdef X90_PROJECT
    static MEM_TYPE void LAPDfrOff_Static(void);
    LAPDfrOff_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPDfrOff_Static(void)
{
#endif
    mDATWrite(U1Bit,DEFROSTER,cInhibit,Default);
    bReadyToSleep = cTrue;
    u8DFRStepTimeoutCounter = 0;
    mDATWrite(U1Bit, EEP_DefrosterActivationState, 0, Default);
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
void LAPDfrOn(void)
{
#ifdef X90_PROJECT
    static MEM_TYPE void LAPDfrOn_Static(void);
    LAPDfrOn_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPDfrOn_Static(void)
{
#endif
    if (  (mDATRead(U1Bit, PWR_IGN, Default) != cFalse)
        //CCOV: adzhelp: Cannot be covered in unit test environment
        ||(bActivateAfterReset != cFalse) )
    {
        mDATWrite(U1Bit,DEFROSTER,cAuthorize,Default);
        mDATWrite(U1Bit, EEP_DefrosterActivationState, 1, Default);
        u8DFRStepTimeoutCounter = mDATRead(U8Bit, NEEP_TPS_TEMPO_DEG, Defaut);
        bReadyToSleep = cFalse;
        TOSStartTimer(&TempoDefrostTimeout);
        bActivateAfterReset = cFalse;
    }
    else
    {
        // this condition is entered after switching ignition off (INFO_REGIME = 1) 
        // a rising eddge from DEFROSTER_SW is obtained which may activate defroster
        // the unwanted activation will be observed on next ignition on
        u8DFRStepTimeoutCounter = (U8)1U;
        TOSStopTimer(&TempoDefrostTimeout);
    }    
}

//==============================================================================
// DESCRIPTION : Initialization of all local variables
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none 
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
void LAPDfrInitialize(void)
{
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
void LAPDfrIsAnybodyMaintainActiveState(void)
{
    if (bReadyToSleep == cFalse)
    {
        TOSWriteSignal(cTOSSignalSomebodyMaintainActiveState);
    }
}
//==============================================================================
// DESCRIPTION : Activation of Defroster 
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none 
//
// DESIGN INFORMATION : prsFS_RDEF-146, prsFS_RDEF-147, prsFS_RDEF-243
//==============================================================================
void LAPDfrEnterActiveState(void)
{
    TOSSeqActivateGraph(cTOSSeqGraphIdRDFRearDefoggerManagement);
    TOSSeqActivateGraph(cTOSSeqGraphIdRDFProtectionManagement);
    mRefreshButtonState();
    bPWR_IGNOld = cFalse;
    u8DfrFaultCounter = 0;
    u8HrnFaultCounter = 0;
    TOSStopTimer(&ActivationTimer);
    bActivationDelayElapsed = cFalse;
}
//==============================================================================
// DESCRIPTION : 
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none 
//
// DESIGN INFORMATION : prsFS_RDEF-146, prsFS_RDEF-147
//==============================================================================
void LAPDfrLeaveActiveState(void)
{
    // configure Outputs
    mDATWrite(U1Bit,DEFROSTER,cInhibit,Default);
    TOSSeqDeactivateGraph(cTOSSeqGraphIdRDFRearDefoggerManagement);
    TOSSeqDeactivateGraph(cTOSSeqGraphIdRDFProtectionManagement);
}
    //==============================================================================
// DESCRIPTION : Pal Protection Task
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : 
//==============================================================================
void LAPDfrProtectionTask(void)
{
#ifdef X90_PROJECT
    LAPDfrProtectionTask_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPDfrProtectionTask_Static(void)
{
#endif

    // PWR_IGN rising edge actions
    if(     (cFalse != mDATRead(U1Bit, PWR_IGN, Default))
         && (cFalse == bPWR_IGNOld)
      )
    {
        //amanevd: The counters are shared between SC to VBAT and SC to GND 
        //because of simplification of the algorithm. 
        //The only disadvantage of using only one counter is that in some very rare 
        //cases when we have SC to GND immediately after SC to VBAT or vice versa, 
        //we will take action for the defect in less samples. But in any case action 
        //will be taken and the defect will be notified.
        u8DfrFaultCounter = 0;
        u8HrnFaultCounter = 0;
        mDATWrite(U1Bit, DEFROSTERProtection, 0, Default);
        mDATWrite(U1Bit, HORN_RLProtection, 0, Default);
        mDATWrite(U1Bit, DefDfrToGnd, 0, Default);
        mDATWrite(U1Bit, DefDfrToBat, 0, Default);
        mDATWrite(U1Bit, DefHornCCBat, 0, Default);
        mDATWrite(U1Bit, DefHornCCGnd, 0, Default);
    }

    // Check if only DEFROSTER output is activated
    if(		(1 == mDATRead(U1Bit, DEFROSTER, Immediate))
        &&  (0 == mDATRead(U1Bit, HORN_RL, Immediate))
        &&  (0 == mDATRead(U1Bit, DEFROSTERProtection, Default))
        &&  (1 == mDATRead(U1Bit, PWR_IGN, Immediate))
      )
    {
        if (mDATRead(U1Bit, DIAG_DRIVER_KLAXON_SingleSCBat, Default) != cFalse)
        {
            u8DfrFaultCounter++;
            if(u8DfrFaultCounter >= cFaultCountProtectThreshold)
            {
                mDATWrite(U1Bit, DEFROSTERProtection, 1, Default);
                mDATWrite(U1Bit, EEP_DefDfrToBat, 1, Default);
            }
            else if(cFaultCountWarnThreshold == u8DfrFaultCounter)
            {
                mDATWrite(U1Bit, DefDfrToBat, 1, Default);
                mDATWrite(U1Bit, DefDfrToGnd, 0, Default);
            }
            else
            {
                // Nothing to do
            }
        }
        else if(mDATRead(U1Bit, DIAG_DRIVER_KLAXON_SCGnd, Default) != cFalse)
        {
            u8DfrFaultCounter++;
            if(u8DfrFaultCounter >= cFaultCountProtectThreshold)
            {
                mDATWrite(U1Bit, EEP_DefDfrToGnd, 1, Default);
            }
            else if(cFaultCountWarnThreshold == u8DfrFaultCounter)
            {
                mDATWrite(U1Bit, DefDfrToGnd, 1, Default);
                mDATWrite(U1Bit, DefDfrToBat, 0, Default);
            }
            else
            {
                // Nothing to do
            }
        }
        else
        {
            // No defect found so clear present flags and reset counters
            u8DfrFaultCounter = 0;
            mDATWrite(U1Bit, DefDfrToBat, 0, Default);
            mDATWrite(U1Bit, DefDfrToGnd, 0, Default);
        }
    }

    // Check if only HORN_RL output is activated
    if(     (1 == mDATRead(U1Bit, HORN_RL, Immediate))
        &&  (0 == mDATRead(U1Bit, DEFROSTER, Immediate))
        &&  (0 == mDATRead(U1Bit, HORN_RLProtection, Default))
        &&  (cFalse == bDefrosterStopped)
      )
    {
        if (mDATRead(U1Bit, DIAG_DRIVER_KLAXON_SingleSCBat, Default) != cFalse)
        {
            u8HrnFaultCounter++;
            if(u8HrnFaultCounter >= cFaultCountProtectThreshold)
            {
                mDATWrite(U1Bit, HORN_RLProtection, 1, Default);
                mDATWrite(U1Bit, EEP_DefHornCCBat, 1, Default);
            }
            else if(cFaultCountWarnThreshold == u8HrnFaultCounter)
            {
                mDATWrite(U1Bit, DefHornCCBat, 1, Default);
                mDATWrite(U1Bit, DefHornCCGnd, 0, Default);
            }
            else
            {
                // Nothing to do
            }
        }
        else if (mDATRead(U1Bit, DIAG_DRIVER_KLAXON_SCGnd, Default) != cFalse)
        {
            u8HrnFaultCounter++;
            if(u8HrnFaultCounter >= cFaultCountProtectThreshold)
            {
                mDATWrite(U1Bit, EEP_DefHornCCGnd, 1, Default);
            }
            else if(cFaultCountWarnThreshold == u8HrnFaultCounter)
            {
                mDATWrite(U1Bit, DefHornCCGnd, 1, Default);
                mDATWrite(U1Bit, DefHornCCBat, 0, Default);
            }
            else
            {
                // Nothing to do
            }
        }
        else
        {
            // No defect found so clear present flags and reset counters
            u8HrnFaultCounter = 0;
            mDATWrite(U1Bit, DefHornCCBat, 0, Default);
            mDATWrite(U1Bit, DefHornCCGnd, 0, Default);
        }
    }

    // Case where HORN_RL and DEFROSTER are activated both at the same time.
    // Or Defroster has been temporary stopped.
    if( (       (1 == mDATRead(U1Bit, HORN_RL, Immediate))
            &&  (1 == mDATRead(U1Bit, DEFROSTER, Immediate))
            &&  (1 == mDATRead(U1Bit, PWR_IGN, Immediate))
            &&  (   (0 == mDATRead(U1Bit, HORN_RLProtection, Default))
                 && (0 == mDATRead(U1Bit, DEFROSTERProtection, Default))
                )
        )
        ||  (cFalse != bDefrosterStopped)
      )
    {
        // Check if SC to VBATT is applied on both outputs
        if (mDATRead(U1Bit, DIAG_DRIVER_KLAXON_DualSCBat, Default) != cFalse)
        {
            u8HrnFaultCounter++;
            u8DfrFaultCounter++;
            if(u8HrnFaultCounter >= cFaultCountProtectThreshold)
            {
                mDATWrite(U1Bit, HORN_RLProtection, 1, Default);
                mDATWrite(U1Bit, EEP_DefHornCCBat, 1, Default);
                mDATWrite(U1Bit, DEFROSTERProtection, 1, Default);
                mDATWrite(U1Bit, EEP_DefDfrToBat, 1, Default);
            }
            else if(cFaultCountWarnThreshold == u8HrnFaultCounter)
            {
                mDATWrite(U1Bit, DefHornCCBat, 1, Default);
                mDATWrite(U1Bit, DefHornCCGnd, 0, Default);
                mDATWrite(U1Bit, DefDfrToGnd, 0, Default);
                mDATWrite(U1Bit, DefDfrToBat, 1, Default);
            }
            else
            {
                // Nothing to do
            }
        }
        // Check if only one output is in defective condition
        else if(mDATRead(U1Bit, DIAG_DRIVER_KLAXON_SingleSCBat, Default) != cFalse)
        {
            u8HrnFaultCounter++;
            u8DfrFaultCounter++;
            if(u8HrnFaultCounter >= cFaultCountProtectThreshold)
            {
                mDATWrite(U1Bit, DefHornCCBat, 1, Default);
                mDATWrite(U1Bit, DefHornCCGnd, 0, Default);
                mDATWrite(U1Bit, HORN_RLProtection, 1, Default);
                mDATWrite(U1Bit, EEP_DefHornCCBat, 1, Default);

                // Remove the temporary protectection on DEFROSTER
                mDATWrite(U1Bit, DEFROSTERProtection, 0, Default);
                bDefrosterStopped = cFalse;
            }
            else if(cFaultCountWarnThreshold == u8HrnFaultCounter)
            {
                // The strategy for detecting the defective output includes
                // temporary protection of one of the outputs and then checking
                // the status of DIAG_DRIVER_KLAXON.
                // Temporary protect Defroster to detect the defective output
                mDATWrite(U1Bit, DEFROSTERProtection, 1, Default);
                bDefrosterStopped = cTrue;
            }
            else
            {
                // Nothing to do
            }
        }
        else
        {
            // Check if Defroster output has been temporary stopped
            // If yes -> this is the defective output
            if(cFalse != bDefrosterStopped)
            {
                mDATWrite(U1Bit, DefDfrToBat, 1, Default);
                mDATWrite(U1Bit, EEP_DefDfrToBat, 1, Default);
                bDefrosterStopped = cFalse;
            }
            else
            {
                u8DfrFaultCounter = 0;
                mDATWrite(U1Bit, DefDfrToGnd, 0, Default);
                mDATWrite(U1Bit, DefDfrToBat, 0, Default);
            }

            u8HrnFaultCounter = 0;
            mDATWrite(U1Bit, DefHornCCBat, 0, Default);
            mDATWrite(U1Bit, DefHornCCGnd, 0, Default);
        }
    }

    bPWR_IGNOld = mDATRead(U1Bit, PWR_IGN, Default);
}

//==============================================================================
// DESCRIPTION : 
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none 
//
// DESIGN INFORMATION : 
//==============================================================================
void LAPDfrLeaveStartingStepState(void)
{
    if ((mDATRead(U1Bit,EEP_AUTDEGIVRAGE,Default) == cAuthorize) &&
        (mDATRead(U1Bit, EEP_DefrosterActivationState,  Default) != 0) )
    {
        bActivateAfterReset = cTrue;
        bPwrIgnAfterReset = cTrue;
        TOSSendControl(cTOSControlWakeUpRequest);
    }
}
/* [EXPORTED_FUNCTIONS_END] */
