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
// Component:    LAP_FLI
//               Flashers management
// -----------------------------------------------------------------------------
// $Log:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_FLI/LAP_FLI.c-arc  $
// 
//    Rev 1.37   Mar 17 2010 13:55:08   amanevd
// Cm006814: Code review corrections
// 
//    Rev 1.36   Mar 02 2010 10:22:00   adzhelp
// Cm006814: TPS_CLI, TPS_CLIDEGRAD, TPS_RETARD_DETRESSE, TIMER_DETRESSE normalized
// 
//    Rev 1.35   Mar 01 2010 11:26:08   adzhelp
// Cm007610: Integration changes - removed counter for SC VBAT
// 
//    Rev 1.34   Feb 26 2010 18:23:44   amanevd
// Cm007610: Included new strategy for detecting SC BAT
// 
//    Rev 1.33   Feb 26 2010 10:24:50   amanevd
// Cm007611:LAPFliLampsOn(void) is updated according prsFS_HWP-1022, prsFS_HWP-1088, prsFS_HWP-1089
// 
//    Rev 1.32   Feb 19 2010 15:50:00   adzhelp
// Cm007466: Crash hazard duration timout divided into steps
// 
//    Rev 1.31   Feb 13 2010 16:07:06   amanevd
// Cm007063: VBATT and Open Load detection correction
// 
//    Rev 1.30   Feb 13 2010 12:31:56   amanevd
// Cm007063: VBATT and Open Load detection implemented
// 
//    Rev 1.29   Feb 11 2010 14:27:46   amanevd
// Cm007465: Volatile defect flag is not cleared when Hazard mode is requested
// 
//    Rev 1.28   Feb 11 2010 14:09:30   adzhelp
// Cm007433: EEP_CrashHazardIsRequested maintains active state
// 
//    Rev 1.27   Feb 10 2010 12:49:58   amanevd
// Cm006744: Perform 32-bit math operations only when values are changed v2
// 
//    Rev 1.26   Feb 08 2010 09:26:52   amanevd
// Cm006744: Perform 32-bit math operations only when values are changed
// 
//    Rev 1.25   Jan 27 2010 15:11:34   amanevd
// Cm007185: In case of hazard activation, flashers are always unprotected
// 
//    Rev 1.24   Jan 07 2010 15:30:56   amanevd
// Cm005566: Deprotection of hazard occurs on next feature(Hazard) activation
// 
//    Rev 1.23   Dec 16 2009 09:12:56   adzhelp
// Cm005566: No buzzer in case of active HWP for Hazard mode
// 
//    Rev 1.22   Dec 14 2009 11:02:18   amanevd
// Cm005566: Full Hardware Protection
// 
//    Rev 1.21   Nov 17 2009 14:35:32   amarinm1
// Cm006596: Unlock feedback now has higher priority and interrupts a lock one.
// 
//    Rev 1.20   Nov 04 2009 17:01:20   adzhelp
// Cm005566: Implementation of HW Protection
// 
//    Rev 1.19   Nov 03 2009 14:02:46   amarinm1
// Cm006156: Buffer time between RF feedback and hazard warning changed to 150ms.
// 
//    Rev 1.18   Oct 14 2009 11:12:32   amarinm1
// Cm006277: EEP_CrashHazardIsRequested when crash warning duration is elapsed.
// 
//    Rev 1.17   Oct 13 2009 16:46:42   amarinm1
// Cm006475: LockUnlockConfirmationIsRequested_Memo is cleared in LAPFliLampsRequestHasChanged() in the case of 'No signal'
// 
//    Rev 1.16   Oct 05 2009 13:49:32   amarinm1
// Cm004936: Updating of FlashingFrequency is now done for both sides flashing too.
// 
//    Rev 1.15   Sep 29 2009 14:06:52   amarinm1
// Cm006156: New variable was added to keep the current flashing mode.
// 
//    Rev 1.14   Sep 25 2009 10:27:56   adzhelp
// Cm005225: Hazard enabled on request of perimeter alarm
// 
//    Rev 1.13   Sep 14 2009 15:34:30   amarinm1
// Cm006191, Cm005603: Crash warning management was changed according to both TCRs.
// 
//    Rev 1.12   Sep 14 2009 13:15:08   amarinm1
// Cm006156: Buffer time between hazard and RF feedback was changed to 150ms.
// 
//    Rev 1.11   12 Aug 2009 16:00:48   amarinm1
// Cm005756: Times that need precision were decreased with 1 tick.
// 
//    Rev 1.10   Aug 06 2009 16:10:16   amarinm1
// Cm005601: Changed the input management for left and right side indicators.
// 
//    Rev 1.9   Jul 30 2009 13:39:28   amarinm1
// Cm004936: Update of flashing frequency was implemented;
// Some issues from the code review were fixed.
// 
//    Rev 1.8   Jun 24 2009 15:04:00   amarinm1
// Cm005164: Lock/unlock feedback is now cleared on '>=' instead of '=='.
// 
//    Rev 1.7   Jun 24 2009 14:59:56   amarinm1
// Cm005167: Before incrementing the lock/unlock counter it is checked that the currently executed pattern is lock/unlock one.
// 
//    Rev 1.6   May 07 2009 21:02:42   amanevd
// Cm004975 - Unexpected warning activation
// 
//    Rev 1.5   Apr 29 2009 14:10:56   adzhelp
// Cm003263: Functions moved to banked memory area
// 
//    Rev 1.4   Apr 24 2009 17:19:16   amarinm1
// Cm003263: The timeout to measure the current was changed;
// Direction change is now taken into account immediately.
// 
//    Rev 1.3   Apr 22 2009 14:45:30   amarinm1
// Cm003263: The times for the directional indication and hazard flashing were fixed.
// 
//    Rev 1.2   Apr 15 2009 12:31:50   amarinm1
// Cm003263 & Cm004774: Implementation of the overload protection and corresponding TFC test. Other minor changes.
// 
//    Rev 1.1   Mar 20 2009 17:59:52   amarinm1
// <TCR_ID to be filled>: Changes for integration.
// 
//    Rev 1.0   Feb 05 2009 12:07:48   amarinm1
// Initial revision.
//
//******************************************************************************

//------------------------------------------------------------------------------
// Body Identification
//------------------------------------------------------------------------------
#define LAP_FLI  "LAP_FLI"

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//
// #include <system_file_name.h>
// #include "project_file_name.h"
//------------------------------------------------------------------------------
#include "lib.h"
#include "tos.h"
#include "dat.h"

#include "LAP_FLI.h"
#include "LAP_FLI.hgr"

//------------------------------------------------------------------------------
// Local constants
//
// #define cConstantName   ((tType) ConstantValue)
//------------------------------------------------------------------------------
#define cMeasureDefaultIntervalInMs     ((U32) 130)
#define cMeasureOffsetForSmallInterval  20UL

#define cRFOnTimeInMs               400UL
#define cRFOffTimeInMs              400UL
#define cHazardRFBufferTimeInMs     150UL
#define cLockUnlockBufferTimeInMs   150UL
#define cNumberOfLockFlashes    ((U8)    2)
#define cNumberOfUnlockFlashes  ((U8)    1)
#define cDiagOnTimeInMs         ((U16) 200)

// Constants are 50 because the step is 100ms and represent
// the whole on/off period while we need the duration of only one phase.
#define cTPS_CLI_step               (U16)50
#define cTPS_CLIDEGRAD_step         (U16)50

#define cTPS_RETARD_DETRESSE_step   (U16)100

#define cTIMER_DETRESSE_step        (U16)25000UL

// DI Lamps
#define cRightAndLeftSideOff    ((U8)    0)
#define cLeftSideOn             ((U8)    1)
#define cRightSideOn            ((U8)    2)
#define cRightAndLeftSideOn     ((U8)    3)

// Flashing Modes
#define cOff                    ((U8)    0)
#define cLeftTurn               ((U8)    1)
#define cRightTurn              ((U8)    2)
#define cHazard                 ((U8)    3)
#define cCrashHazard            ((U8)    4)
#define cRFFeedback             ((U8)    5)
#define cLeftTFC                ((U8)    6)
#define cRightTFC               ((U8)    7)


// HW Protection
#define cProtectionHeatCountInitial ((U8)20U)
#define cSCToGNDCountThreshold      ((U8)10U)

//------------------------------------------------------------------------------
// Local macros
//
// #define mMacroName   (MacroDefinition)
//------------------------------------------------------------------------------
//QACJ 3410: amarinm1: This is intentionally done and works correctly.
#define mSet(DataName)            (FLAControlStatus.DataName  = cTrue)
//QACJ 3410: amarinm1: This is intentionally done and works correctly.
#define mClear(DataName)          (FLAControlStatus.DataName  = cFalse)
//QACJ 3410: amarinm1: This is intentionally done and works correctly.
#define mRead(DataName)           (FLAControlStatus.DataName)



// The times below are multiplied by 50 because the step is 100ms and represent
// the whole on/off period while we need the duration of only one phase.
#define mReadHazardOnTimeInMs()                                                \
        ( (U16)                                                          \
          /* //QACJ 3443: amarinm1: There is no recursion in the macro! */     \
          (cTPS_CLI_step * mDATRead(U8Bit, NEEP_TPS_CLI, Default)) )

#define mReadHazardOffTimeInMs()                                               \
        ( (U16)                                                          \
          /* //QACJ 3443: amarinm1: There is no recursion in the macro! */     \
          (cTPS_CLI_step * mDATRead(U8Bit, NEEP_TPS_CLI, Default)) )

#define mReadNormalDIOnTimeInMs()                                              \
        ( (U16)                                                          \
          /* //QACJ 3443: amarinm1: There is no recursion in the macro! */     \
          (cTPS_CLI_step * mDATRead(U8Bit, NEEP_TPS_CLI, Default)) )

#define mReadNormalDIOffTimeInMs()                                             \
        ( (U16)                                                          \
          /* //QACJ 3443: amarinm1: There is no recursion in the macro! */     \
          (cTPS_CLI_step * mDATRead(U8Bit, NEEP_TPS_CLI, Default)) )

#define mReadDegradedDIOnTimeInMs()                                            \
        ( (U16)                                                          \
          /* //QACJ 3443: amarinm1: There is no recursion in the macro! */     \
          (cTPS_CLIDEGRAD_step * mDATRead(U8Bit, NEEP_TPS_CLIDEGRAD, Default)) )

#define mReadDegradedDIOffTimeInMs()                                           \
        ( (U16)                                                          \
          /* //QACJ 3443: amarinm1: There is no recursion in the macro! */     \
          (cTPS_CLIDEGRAD_step * mDATRead(U8Bit, NEEP_TPS_CLIDEGRAD, Default)) )


#define mCalcCrashHazardDelayInTimerTick()  \
            ( mTOSConvMsInTimerTick((U32) (cTPS_RETARD_DETRESSE_step * \
                /* //QACJ 3443: amarinm1: There is no recursion in the macro! */ \
                (u8TPS_RETARD_DETRESSE = mDATRead(U8Bit, NEEP_TPS_RETARD_DETRESSE, Default)))) )

#define mReadCrashHazardDelayInTimerTick() \
            (CalculatedTPS_RETARD_DETRESSE = \
                (u8TPS_RETARD_DETRESSE == mDATRead(U8Bit, NEEP_TPS_RETARD_DETRESSE, Default)) \
                ? CalculatedTPS_RETARD_DETRESSE \
    /*//QACJ 3443:amanevd: Last instance of mDATRead is a concatenation of mDATRead ## DataType## DataName ## TreatmentType()*/ \
                : mCalcCrashHazardDelayInTimerTick())

#define mReadCrashHazardDurationStepInTimerTick() \
    mTOSConvMsInTimerTick((U32)cTIMER_DETRESSE_step)
#define mReadCrashHazardDurationSteps() \
    /*//QACJ 3443: adzhelp: Standard STK macros used */ \
    mDATRead(U8Bit, NEEP_TIMER_DETRESSE, Default)

// The times below are multiplied by 50 because the step is 100ms and represent
// the whole on/off period while we need the duration of only one phase.
#define mCalcHazardOffTimeInTimerTick() \
            ( mTOSConvMsInTimerTick( (U32)(cTPS_CLI_step * \
/*//QACJ 3443:amanevd: Last instance of mDATRead is a concatenation of mDATRead ## DataType## DataName ## TreatmentType()*/ \
                (u8TPS_CLI = mDATRead(U8Bit, NEEP_TPS_CLI, Default))) ) - (tTOSTimer)1 )

#define mReadHazardOffTimeInTimerTick()                                        \
            (CalculatedTPS_CLI = \
                (u8TPS_CLI == mDATRead(U8Bit, NEEP_TPS_CLI, Default)) \
                ? CalculatedTPS_CLI \
    /*//QACJ 3443:amanevd: Last instance of mDATRead is a concatenation of mDATRead ## DataType## DataName ## TreatmentType()*/ \
                : mCalcHazardOffTimeInTimerTick())

#define mCalcDegradedDIOnTimeInTimerTick() \
            ( mTOSConvMsInTimerTick( (U32)(cTPS_CLIDEGRAD_step * \
                /* //QACJ 3443: amarinm1: There is no recursion in the macro! */ \
                (u8TPS_CLIDEGRAD = mDATRead(U8Bit, NEEP_TPS_CLIDEGRAD, Default))) ) - (tTOSTimer)1U )

#define mReadDegradedDIOnTimeInTimerTick() \
            (CalculatedTPS_CLIDEGRAD = \
                (u8TPS_CLIDEGRAD == mDATRead(U8Bit, NEEP_TPS_CLIDEGRAD, Default)) \
                ? CalculatedTPS_CLIDEGRAD \
    /*//QACJ 3443:amanevd: Last instance of mDATRead is a concatenation of mDATRead ## DataType## DataName ## TreatmentType()*/ \
                : mCalcDegradedDIOnTimeInTimerTick())

//QACJ 3443:amanevd: Last instance of mDATRead is a concatenation of mDATRead ## DataType## DataName ## TreatmentType()
#define mReadDegradedDIOffTimeInTimerTick() mReadDegradedDIOnTimeInTimerTick()

#define mReadRFOnTimeInTimerTick()                                             \
(tTOSTimer)( mTOSConvMsInTimerTick( (U32)cRFOnTimeInMs ) - (tTOSTimer)1U )

#define mReadRFOffTimeInTimerTick()                                            \
(tTOSTimer)( mTOSConvMsInTimerTick( (U32)cRFOffTimeInMs ) - (tTOSTimer)1U )

#define mReadMeasureDefaultIntervalInTicks()                                       \
(tTOSTimer)( mTOSConvMsInTimerTick( cMeasureDefaultIntervalInMs ) - (tTOSTimer)1U )

#define mReadHazardRFBufferTimeInTicks()                                           \
(tTOSTimer)( mTOSConvMsInTimerTick( cHazardRFBufferTimeInMs ) - (tTOSTimer)1U )

#define mAllDoorsAreClosed()                                                   \
        ((BOOL)(   (mDATRead(U1Bit, RR_DOORS_SW, Default) == 0)                \
               /* //QACJ 3443: amarinm1: There is no recursion in the macro! */\
                && (mDATRead(U1Bit, FR_DOORS_SW, Default) == 0)  ))

#define mLockUnlockConfirmationIsRequested()                                   \
        ((BOOL)(   (mRead(LockConfirmationIsRequested)   == cTrue)             \
                || (mRead(UnlockConfirmationIsRequested) == cTrue)   ))

// FlasherSCBatOrOpenLoad detects only Open Load
#define mFlasherOpenLoad()      mDATReadU1BitFlasherSCBatOrOpenLoadDefault()
//------------------------------------------------------------------------------
// Local types
//
// typedef Expression    tTypeName;
//------------------------------------------------------------------------------
typedef struct sFlasherSignal
{
    U16   TimeDILampOn;
    U16   TimeDILampOff;
    U8    DILampCycleNumber;
    U8    DILampSideOn;
    U8    FlashingMode;
} tFlasherSignal;

typedef struct sFlasherFlag
{
    BOOL  TurnLeftIsRequested;
    BOOL  TurnRightIsRequested;          
    BOOL  DILampRequestHasChanged;
    BOOL  DILampHazard;    
    BOOL  CrashHazardIsRequested;
    BOOL  LockConfirmationIsRequested;
    BOOL  UnlockConfirmationIsRequested;
    BOOL  LockUnlockConfirmationIsRequested_Memo;
    BOOL  TFCFlashingIsRequested;
    BOOL  BulbFailureDetected;
    BOOL  OverVoltageIsDetected;
    BOOL  ShortCircuitIsDetected; // when set disables buzzer
    BOOL  TurnLeftIsRequestedByTFC;
    BOOL  TurnRightIsRequestedByTFC;          
} tFlasherFlag;


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
static  tFlasherSignal  DILampSignal;
static  tFlasherFlag    FLAControlStatus;

static  tTOSTimer       TimerDILamps;
static  tTOSTimer       TimerCrashHazardDelay;
static  tTOSTimer       TimerCrashHazardDurationStep;
static  tTOSTimer       TimerCurrentActiveTimeOut;
static  tTOSTimer       TimerCurrentInactiveTimeOut;

static  tTOSTimer       CalculatedTPS_RETARD_DETRESSE;
static  tTOSTimer       CalculatedTPS_CLI;
static  tTOSTimer       CalculatedTPS_CLIDEGRAD;

static U8               u8TimerStepCrashHazard;

static U8               u8FlashCount;

static  BOOL            bBothIndicatorsRequested;

// HW Protection
static  BOOL            bPWR_IGNOld;
static  BOOL            bLeftFlasherStopped;
static  BOOL            bFlasherSCBatOrOpenLoadReadAllowed;
static  BOOL            bSCBattDetected;
static  U8              u8ProtectionCounterLeft;
static  U8              u8ProtectionCounterRight;
static  U8              u8FaultCounter;

static  U8              u8TPS_RETARD_DETRESSE;
static  U8              u8TPS_CLI;
static  U8              u8TPS_CLIDEGRAD;

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
static MEM_TYPE void SetFlasherSignal( const U16, const U16, const U8, const U8 );
static MEM_TYPE void ClearRFEvents( void );
static MEM_TYPE BOOL CrashHazardDurationTimerIsElapsed( void );
static MEM_TYPE void SetFlasherDefect(const BOOL bLeftP, const BOOL bRightP, const BOOL bChkOpenLoadP);

#ifdef X90_PROJECT
static MEM_TYPE void LAPFliInitialize_Static(void);
static MEM_TYPE BOOL LAPFliLampsRequestHasChanged_Static( void );
static MEM_TYPE void LAPFliInputManagement_Static( void );
static MEM_TYPE void LAPFliLampsOn_Static(void);
static MEM_TYPE void LAPFliLampsOff_Static(void);
static MEM_TYPE void LAPFliMeasureCurrent_Static(void);
static MEM_TYPE void LAPFliProtectionTask_Static(void);
#endif

//==============================================================================
//=========================== LOCAL FUNCTIONS ==================================
//==============================================================================

//==============================================================================
// DESCRIPTION:         < short description of the function >
//
// PARAMETERS:          < type,usage and constraints for all parameters >
//
// RETURN VALUE:        < type and usage >
//
// DESIGN INFORMATION:  < usage, pseudo code, algorithm, constraints ... >
//==============================================================================
static MEM_TYPE void SetFlasherSignal(
                             const U16 TimeDILampOnP, 
                             const U16 TimeDILampOffP, 
                             const U8 DILampCycleNumberP, 
                             const U8 DILampSideOnP
                            )
{
    if (   (DILampSignal.TimeDILampOff      != TimeDILampOffP    ) 
        || (DILampSignal.TimeDILampOn       != TimeDILampOnP     )
        || (DILampSignal.DILampCycleNumber  != DILampCycleNumberP)
        || (DILampSignal.DILampSideOn       != DILampSideOnP     ) )
    {
                // -> RF pattern in progress
        if (   (DILampSignal.DILampCycleNumber != 0)  
                // -> Lamp was OFF
            || (DILampSignal.DILampSideOn  == cRightAndLeftSideOff)
            || (DILampSideOnP              == cRightAndLeftSideOff)
                // -> Flashing side has changed
            || (DILampSignal.DILampSideOn  != DILampSideOnP       )    )
        { 
            mSet(DILampRequestHasChanged);  // immediate reinitialisation
        }
        else
        {
            // Do nothing
        }
        DILampSignal.TimeDILampOff     = TimeDILampOffP;
        DILampSignal.TimeDILampOn      = TimeDILampOnP;
        DILampSignal.DILampCycleNumber = DILampCycleNumberP;
        DILampSignal.DILampSideOn      = DILampSideOnP;
    }
    else
    {
        // Do nothing
    }
}


//==============================================================================
// DESCRIPTION:         < short description of the function >
//
// PARAMETERS:          < type,usage and constraints for all parameters >
//
// RETURN VALUE:        < type and usage >
//
// DESIGN INFORMATION:  < usage, pseudo code, algorithm, constraints ... >
//==============================================================================
static MEM_TYPE void ClearRFEvents(void)
{
    mClear(LockConfirmationIsRequested);
    mClear(UnlockConfirmationIsRequested);
    //QACJ 3200: amarinm1: Reading is done just to clear the signal.
    TOSReadSignal(cTOSSignalLAPFliEventRfLockAll);
    //QACJ 3200: amarinm1: Reading is done just to clear the signal.
    TOSReadSignal(cTOSSignalLAPFliEventRfUnlockAll);
}


//==============================================================================
// DESCRIPTION:         < short description of the function >
//
// PARAMETERS:          < type,usage and constraints for all parameters >
//
// RETURN VALUE:        < type and usage >
//
// DESIGN INFORMATION:  < usage, pseudo code, algorithm, constraints ... >
//==============================================================================
static MEM_TYPE BOOL CrashHazardDurationTimerIsElapsed( void )
{
    const BOOL bTimerIsStartedL = TOSIsTimerStarted( &TimerCrashHazardDurationStep );
    BOOL bTimerIsElapsedL;
    BOOL bReturnL = cFalse;

    if (bTimerIsStartedL != cFalse)
    {
        bTimerIsElapsedL = TOSIsTimerElapsed(&TimerCrashHazardDurationStep, 
                                             mReadCrashHazardDurationStepInTimerTick() );
        if (bTimerIsElapsedL != cFalse)
        {
            if (u8TimerStepCrashHazard > 0)
            {
                u8TimerStepCrashHazard--;
            }

            if (u8TimerStepCrashHazard != 0)
            {
                TOSStartTimer(&TimerCrashHazardDurationStep);
            }
            else
            {
                bReturnL = cTrue;
            }
        }
    }

    return bReturnL;
}

//==============================================================================
// DESCRIPTION:         < short description of the function >
//
// PARAMETERS:          < type,usage and constraints for all parameters >
//
// RETURN VALUE:        < type and usage >
//
// DESIGN INFORMATION:  < usage, pseudo code, algorithm, constraints ... >
//==============================================================================
static MEM_TYPE void SetFlasherDefect(const BOOL bLeftP, const BOOL bRightP, const BOOL bChkOpenLoadP)
{
    U16 u16TempL;

    if(cFalse != bLeftP)
    {
        mDATWrite(U1Bit, DefClignL, 1, Default);
        mDATWrite(U1Bit, EEP_DefClignL, 1, Default);

        // Check if Open load is detected depending on bChkOpenLoadP flag.
        // if bChkOpenLoadP==cTrue and Open load detected the output will
        // not be protected
        if(     (cFalse == bChkOpenLoadP)
             || (cFalse == mFlasherOpenLoad())
          )
        {
            mDATWrite(U1Bit, DI_LEFTProtection, 1, Default);
            u16TempL = mDATRead(U16Bit, EEP_CDLeftInd, Default);
            if(u16TempL < mDATRead(U16Bit, EEP_SCLimit, Default))
            {
                u16TempL ++;
                mDATWrite(U16Bit, EEP_CDLeftInd, u16TempL, Default);
            }
        }
    }

    if(cFalse != bRightP)
    {
        mDATWrite(U1Bit, DefClignR, 1, Default);
        mDATWrite(U1Bit, EEP_DefClignR, 1, Default);

        mLIBassert(cFalse != bChkOpenLoadP);

        if(cFalse == mFlasherOpenLoad())
        {
            mDATWrite(U1Bit, DI_RIGHTProtection, 1, Default);
            u16TempL = mDATRead(U16Bit, EEP_CDRightInd, Default);
            if(u16TempL < mDATRead(U16Bit, EEP_SCLimit, Default))
            {
                u16TempL ++;
                mDATWrite(U16Bit, EEP_CDRightInd, u16TempL, Default);
            }
        }
    }
}

// [LOCAL_FUNCTIONS_END]


//==============================================================================
//=========================== EXPORTED FUNCTIONS ===============================
//==============================================================================


//==============================================================================
// DESCRIPTION:         < short description of the function >
//
// PARAMETERS:          < type,usage and constraints for all parameters >
//
// RETURN VALUE:        < type and usage >
//
// DESIGN INFORMATION:  < usage, pseudo code, algorithm, constraints ... >
//==============================================================================
void LAPFliInitialize( void )
{
#ifdef X90_PROJECT
    LAPFliInitialize_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPFliInitialize_Static(void)
{
#endif

    DILampSignal.TimeDILampOff     = 0;
    DILampSignal.TimeDILampOn      = 0;
    DILampSignal.DILampCycleNumber = 0;
    DILampSignal.DILampSideOn      = cRightAndLeftSideOff;
    DILampSignal.FlashingMode      = cOff;
    u8FlashCount                   = 0;
    bBothIndicatorsRequested       = cFalse;

    mDATWrite(U8Bit, FlasherLampsTestResult, cDATCmnFlasherLampsNotTested, Default);

    mLIBmemset(&FLAControlStatus, 0, sizeof(FLAControlStatus));
    bPWR_IGNOld = cFalse;
    u8ProtectionCounterLeft = cProtectionHeatCountInitial;
    u8ProtectionCounterRight = cProtectionHeatCountInitial;
    u8FaultCounter           = 0;
}


//==============================================================================
// DESCRIPTION:         < short description of the function >
//
// PARAMETERS:          < type,usage and constraints for all parameters >
//
// RETURN VALUE:        < type and usage >
//
// DESIGN INFORMATION:  < usage, pseudo code, algorithm, constraints ... >
//==============================================================================
void LAPFliEnterActiveState( void )
{
    mDATWrite(U8Bit, FlasherLampsTestResult, cDATCmnFlasherLampsNotTested, Default);

    mClear( LockConfirmationIsRequested );
    mClear( UnlockConfirmationIsRequested );
    mClear( TFCFlashingIsRequested );      

    TOSSeqActivateGraph( cTOSSeqGraphIdLAPFliInput );
    TOSSeqActivateGraph( cTOSSeqGraphIdLAPFliLampsState );
    TOSSeqActivateGraph( cTOSSeqGraphIdLAPFliProtectionManagement );
    bPWR_IGNOld = cFalse;
    u8ProtectionCounterLeft = cProtectionHeatCountInitial;
    u8ProtectionCounterRight = cProtectionHeatCountInitial;
    u8FaultCounter = 0;
}


//==============================================================================
// DESCRIPTION:         < short description of the function >
//
// PARAMETERS:          < type,usage and constraints for all parameters >
//
// RETURN VALUE:        < type and usage >
//
// DESIGN INFORMATION:  < usage, pseudo code, algorithm, constraints ... >
//==============================================================================
void LAPFliLeaveActiveState( void )
{
    mDATWrite(U1Bit, DI_LEFT,  0, Default);
    mDATWrite(U1Bit, DI_RIGHT, 0, Default);
    TOSSeqDeactivateGraph( cTOSSeqGraphIdLAPFliInput );
    TOSSeqDeactivateGraph( cTOSSeqGraphIdLAPFliLampsState );
    TOSSeqDeactivateGraph( cTOSSeqGraphIdLAPFliProtectionManagement );
}


//==============================================================================
// DESCRIPTION:         < short description of the function >
//
// PARAMETERS:          < type,usage and constraints for all parameters >
//
// RETURN VALUE:        < type and usage >
//
// DESIGN INFORMATION:  < usage, pseudo code, algorithm, constraints ... >
//==============================================================================
void LAPFliIsAnybodyMaintainActiveState( void )
{
    if (   (mDATRead(U1Bit, EEP_CrashHazardIsRequested, Default) != cFalse)
        || (mLockUnlockConfirmationIsRequested() == cTrue)   )
    {
        TOSWriteSignal(cTOSSignalSomebodyMaintainActiveState);
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
BOOL LAPFliLampsRequestHasChanged( void )
{
#ifdef X90_PROJECT
    return LAPFliLampsRequestHasChanged_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL LAPFliLampsRequestHasChanged_Static( void )
{
#endif

    U8    u8DILampSideL;
    BOOL  bReturnValueL;
    BOOL  bBufferTimeHasElapsedL;
    BOOL  bCrashHazardDelayHasElapsedL;
    BOOL  bCrashhazardDurationTimerIsStartedL;

    tTOSTimer   CrashHazardDelayInTimerTickL;
    tTOSTimer   HazardOffTimeInTimerTickL;
        
    
    // -------------------------------------------------------------------------
    // DIAGNOSTIC TEST
    // -------------------------------------------------------------------------
    if ( mRead(TurnLeftIsRequestedByTFC) == cTrue )
    {
        mClear(TurnLeftIsRequestedByTFC);
        SetFlasherSignal( cDiagOnTimeInMs, 0, 1, cLeftSideOn );
        DILampSignal.FlashingMode = cLeftTFC;
        mSet(TFCFlashingIsRequested);
    }
    else if ( mRead(TurnRightIsRequestedByTFC) == cTrue )
    {
        mClear(TurnRightIsRequestedByTFC);
        SetFlasherSignal( cDiagOnTimeInMs, 0, 1, cRightSideOn );
        DILampSignal.FlashingMode = cRightTFC;
        mSet(TFCFlashingIsRequested);
    }
    else if ( mRead(TFCFlashingIsRequested) == cTrue )
    {
        // Do nothing
    }

    // -------------------------------------------------------------------------
    // UNLOCK ALL SIGNAL
    // -------------------------------------------------------------------------
    else if ( mRead(UnlockConfirmationIsRequested) == cTrue )
    {
        if (   ( mRead(DILampHazard) == cTrue )
            || ( mRead(LockConfirmationIsRequested) == cTrue )   )
        {
               // Only one side can be checked
            if (mDATRead(U1Bit, DI_LEFT,  Default) == 0)
            {
                bBufferTimeHasElapsedL = 
                    TOSIsTimerElapsed( &TimerDILamps, 
                                       mReadHazardRFBufferTimeInTicks() );
                if (bBufferTimeHasElapsedL == cTrue)
                {
                    SetFlasherSignal( cRFOnTimeInMs, 
                                      cRFOffTimeInMs, 
                                      cNumberOfUnlockFlashes, 
                                      cRightAndLeftSideOn
                                    );
                    DILampSignal.FlashingMode   =  cRFFeedback;
                    TimerCurrentActiveTimeOut   =  mReadRFOnTimeInTimerTick();
                    TimerCurrentInactiveTimeOut =  mReadRFOffTimeInTimerTick();
                    
                    if ( mRead(LockConfirmationIsRequested) == cTrue )
                    {
                        mClear(LockConfirmationIsRequested);
                    }
                }
            }
            else // ON phase
            {
                if ( mRead(LockConfirmationIsRequested) == cTrue )
                {
                    // Forse both sides to off for the buffer time
                    SetFlasherSignal( cLockUnlockBufferTimeInMs, 
                                      cLockUnlockBufferTimeInMs, 
                                      1, 
                                      cRightAndLeftSideOff
                                    );
                }
            }
        }
        else
        {
            SetFlasherSignal( cRFOnTimeInMs, 
                              cRFOffTimeInMs, 
                              cNumberOfUnlockFlashes, 
                              cRightAndLeftSideOn
                            );
            DILampSignal.FlashingMode = cRFFeedback;
        }
    }

    // -------------------------------------------------------------------------
    // LOCK ALL SIGNAL
    // -------------------------------------------------------------------------
    else if ( mRead(LockConfirmationIsRequested) == cTrue )
    {
        if ( mRead(DILampHazard) == cTrue )
        {
                    // Only one side can be checked
            if (   (mDATRead(U1Bit, DI_LEFT,  Default) == 0)
                && (DILampSignal.FlashingMode != cRFFeedback)   )
            {
                bBufferTimeHasElapsedL = 
                    TOSIsTimerElapsed( &TimerDILamps, 
                                       mReadHazardRFBufferTimeInTicks() );
                if (bBufferTimeHasElapsedL == cTrue)
                {
                    SetFlasherSignal( cRFOnTimeInMs, 
                                      cRFOffTimeInMs, 
                                      cNumberOfLockFlashes, 
                                      cRightAndLeftSideOn
                                    );
                    DILampSignal.FlashingMode   =  cRFFeedback;
                    TimerCurrentActiveTimeOut   =  mReadRFOnTimeInTimerTick();
                    TimerCurrentInactiveTimeOut =  mReadRFOffTimeInTimerTick();
                }
                else
                {
                    // Do nothing
                }
            }
            else
            {
                // Do nothing
            }
        }
        else
        {
            SetFlasherSignal( cRFOnTimeInMs, 
                              cRFOffTimeInMs, 
                              cNumberOfLockFlashes, 
                              cRightAndLeftSideOn
                            );
            DILampSignal.FlashingMode = cRFFeedback;
        }
    }
        
    // -------------------------------------------------------------------------
    // CRASH HAZARD SIGNAL
    // -------------------------------------------------------------------------
    else if ( mRead( CrashHazardIsRequested ) == cTrue )
    {
        //QACJ 3226: amanevd: This is intentional and is checked out for problems.
        CrashHazardDelayInTimerTickL = mReadCrashHazardDelayInTimerTick();
        bCrashHazardDelayHasElapsedL = 
            TOSIsTimerElapsed( &TimerCrashHazardDelay,
                               CrashHazardDelayInTimerTickL );
        if ( bCrashHazardDelayHasElapsedL == cTrue )
        {
            if ( mRead(LockUnlockConfirmationIsRequested_Memo) == cFalse )
            {
                SetFlasherSignal( mReadHazardOnTimeInMs(), 
                                  mReadHazardOffTimeInMs(), 
                                  0, 
                                  cRightAndLeftSideOn
                                );
                DILampSignal.FlashingMode = cCrashHazard;
                bCrashhazardDurationTimerIsStartedL = 
                    TOSIsTimerStarted( &TimerCrashHazardDurationStep );
                if ( bCrashhazardDurationTimerIsStartedL == cFalse )
                {
                    TOSStartTimer( &TimerCrashHazardDurationStep );
                    u8TimerStepCrashHazard = mReadCrashHazardDurationSteps();
                }
                else
                {
                    // Do nothing
                }
            }
            else // LockUnlockConfirmationIsRequested_Memo == cTrue
            {
                //QACJ 3226: amanevd: This is intentional and is checked out for problems.
                HazardOffTimeInTimerTickL = mReadHazardOffTimeInTimerTick();
                bBufferTimeHasElapsedL = 
                    TOSIsTimerElapsed( &TimerDILamps, 
                                       HazardOffTimeInTimerTickL );
                if ( bBufferTimeHasElapsedL == cTrue )
                {
                    SetFlasherSignal( mReadHazardOnTimeInMs(), 
                                      mReadHazardOffTimeInMs(), 
                                      0, 
                                      cRightAndLeftSideOn
                                    );
                    DILampSignal.FlashingMode = cCrashHazard;
                    TOSStartTimer( &TimerCrashHazardDurationStep );
                    u8TimerStepCrashHazard = mReadCrashHazardDurationSteps();
                    FLAControlStatus.LockUnlockConfirmationIsRequested_Memo = cFalse;
                }
                else
                {
                    // Because LAPFliLampsOffTimeIsElapsed() checks THIS
                    //QACJ 3226: amanevd: This is intentional and is checked out for problems.
                    TimerCurrentInactiveTimeOut = 
                        mReadHazardOffTimeInTimerTick();
                    DILampSignal.FlashingMode = cCrashHazard;
                }
            }
        }
        else
        {
            // Do nothing
        }
    }

    // -------------------------------------------------------------------------
    // HAZARD SIGNAL
    // -------------------------------------------------------------------------
    else if ( mRead(DILampHazard) == cTrue )
    {
        if ( mRead(LockUnlockConfirmationIsRequested_Memo) == cFalse )
        {
            SetFlasherSignal( mReadHazardOnTimeInMs(), 
                              mReadHazardOffTimeInMs(), 
                              0, 
                              cRightAndLeftSideOn
                            );
            DILampSignal.FlashingMode = cHazard;
        }
        else // LockUnlockConfirmationIsRequested_Memo == cTrue
        {
            bBufferTimeHasElapsedL = 
                    TOSIsTimerElapsed( &TimerDILamps, 
                                       mReadHazardRFBufferTimeInTicks() );
            if ( bBufferTimeHasElapsedL == cTrue )
            {
                SetFlasherSignal( mReadHazardOnTimeInMs(), 
                                  mReadHazardOffTimeInMs(), 
                                  0, 
                                  cRightAndLeftSideOn
                                );
                DILampSignal.FlashingMode = cHazard;
                FLAControlStatus.LockUnlockConfirmationIsRequested_Memo = cFalse;
            }
            else
            {
                // Because LAPFliLampsOffTimeIsElapsed() checks THIS
                TimerCurrentInactiveTimeOut = mReadHazardRFBufferTimeInTicks();
                DILampSignal.FlashingMode = cHazard;
            }
        }
    }

    // -------------------------------------------------------------------------
    // TURN LEFT / RIGHT SIGNAL
    // -------------------------------------------------------------------------
    else if (   (mRead(TurnLeftIsRequested)  == cTrue) 
             || (mRead(TurnRightIsRequested) == cTrue)  )
    {
        if ( mRead(TurnLeftIsRequested) == cTrue )
        {
            u8DILampSideL = cLeftSideOn;            
            DILampSignal.FlashingMode = cLeftTurn;
        }
        else
        {
            u8DILampSideL = cRightSideOn;            
            DILampSignal.FlashingMode = cRightTurn;
        }

        // Set normal or degraded flashing time
        if ( mRead(BulbFailureDetected) == cTrue )
        {
               // New, update timer
            if ( DILampSignal.TimeDILampOff != 
                 mReadDegradedDIOffTimeInMs() ) 
            {
                //QACJ 3226: amanevd: This is intentional and is checked out for problems.
                TimerCurrentActiveTimeOut   = 
                    mReadDegradedDIOnTimeInTimerTick();
                //QACJ 3226: amanevd: This is intentional and is checked out for problems.
                TimerCurrentInactiveTimeOut = 
                    mReadDegradedDIOffTimeInTimerTick();
            }
            else
            {
                // Do nothing
            }
            SetFlasherSignal( mReadDegradedDIOnTimeInMs(), 
                              mReadDegradedDIOffTimeInMs(), 
                              0, 
                              u8DILampSideL
                            );
        }
        else // Normal
        {   
            SetFlasherSignal( mReadNormalDIOnTimeInMs(), 
                              mReadNormalDIOffTimeInMs(), 
                              0, 
                              u8DILampSideL
                            );
        }

    }

    // -------------------------------------------------------------------------
    // NO SIGNAL
    // -------------------------------------------------------------------------
    else 
    {
        SetFlasherSignal( 0, 0, 0, cRightAndLeftSideOff );            
        DILampSignal.FlashingMode = cOff;
        mSet(DILampRequestHasChanged);  // force the immediate refresh
        FLAControlStatus.LockUnlockConfirmationIsRequested_Memo = cFalse;
        mClear(BulbFailureDetected);
        mClear(ShortCircuitIsDetected);
    }

    if ( mRead(DILampRequestHasChanged) == cTrue )
    {
        bReturnValueL = cTrue;
        mClear(DILampRequestHasChanged);
        u8FlashCount = 0;

        if(     (cHazard == DILampSignal.FlashingMode)
             || (cCrashHazard == DILampSignal.FlashingMode)
             || (cRFFeedback == DILampSignal.FlashingMode)
          )
        {
            mDATWrite(U1Bit, DI_LEFTProtection, 0, Default);
            mDATWrite(U1Bit, DI_RIGHTProtection, 0, Default);
            bSCBattDetected = cFalse;
        }

        mClear(OverVoltageIsDetected);
        mClear(ShortCircuitIsDetected);
    }
    else
    {
        bReturnValueL = cFalse;
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
void LAPFliLampsOff(void)
{
#ifdef X90_PROJECT
    LAPFliLampsOff_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPFliLampsOff_Static(void)
{
#endif


    mDATWrite(U1Bit, DI_LEFT,  0, Default);
    mDATWrite(U1Bit, DI_RIGHT, 0, Default);

    if (mRead(ShortCircuitIsDetected) == cFalse)
    {
        mDATWriteTable(U1Bit, BUZZER, eBUZZER_FlasherClack, cTrue, Default);
    }
    else
    {
        // buzzer sound disabled during SC if faulty side is turned on 
        // or if both sides are faulty in Hazard mode
    }
            
    // Flashing for TFC is only once so clear the flag on each LampsOff
    mClear( TFCFlashingIsRequested );
    

    FLAControlStatus.LockUnlockConfirmationIsRequested_Memo =
        ((BOOL)(   (FLAControlStatus.LockConfirmationIsRequested)
                || (FLAControlStatus.UnlockConfirmationIsRequested)  ));
    
    if (   (mLockUnlockConfirmationIsRequested() == cTrue)
        && (DILampSignal.FlashingMode == cRFFeedback )   )
    {
        // RF MODE
        u8FlashCount++;
        if ( u8FlashCount >= DILampSignal.DILampCycleNumber )
        {
            DILampSignal.DILampSideOn = cRightAndLeftSideOff;

            mClear( LockConfirmationIsRequested );
            mClear( UnlockConfirmationIsRequested ); 
            
            u8FlashCount = 0;
        }
        else
        {
            // Do nothing
        }
    }
    else
    {
        // Do nothing
    }
    
    TOSStartTempo( &TimerDILamps );
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
BOOL LAPFliLampsOffTimeIsElapsed(void)
{
    return 
        (BOOL)( TOSIsTimerElapsed(&TimerDILamps, TimerCurrentInactiveTimeOut) );
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
void LAPFliLampsOn(void)
{
#ifdef X90_PROJECT
    LAPFliLampsOn_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPFliLampsOn_Static(void)
{
#endif

    if ( (DILampSignal.DILampSideOn & cLeftSideOn) != 0 )
    {
        mDATWrite(U1Bit, DI_LEFT, 1, Default);
    }
    else
    {
        mDATWrite(U1Bit, DI_LEFT, 0, Default);
    }

    if ( (DILampSignal.DILampSideOn & cRightSideOn) != 0 )
    {
        mDATWrite(U1Bit, DI_RIGHT, 1, Default);
    }
    else
    {
        mDATWrite(U1Bit, DI_RIGHT, 0, Default);
    }

    // Update buzzer status for Hazard mode and active HW protection
    if (    (   (
                    (DILampSignal.FlashingMode == cHazard) 
                 || (DILampSignal.FlashingMode == cCrashHazard)
                )
             && (   (mDATRead(U1Bit, DI_LEFTProtection, Default) != cFalse) 
                 && (mDATRead(U1Bit, DI_RIGHTProtection, Default) != cFalse)
                )
            )
         || (   (   (DILampSignal.FlashingMode == cLeftTFC)
                 || (DILampSignal.FlashingMode == cLeftTurn)                 
                )
             && (mDATRead(U1Bit, DI_LEFTProtection, Default) != cFalse)
            )
         || (   (   (DILampSignal.FlashingMode == cRightTFC)
                 || (DILampSignal.FlashingMode == cRightTurn)                 
                )
             && (mDATRead(U1Bit, DI_RIGHTProtection, Default) != cFalse)
            )
       )
    {
        mSet(ShortCircuitIsDetected);
    }
    else
    {
        mClear(ShortCircuitIsDetected);
    }

    if (   (mDATRead(U1Bit, DI_LEFT,  Default) == 1)
        || (mDATRead(U1Bit, DI_RIGHT, Default) == 1)   )
    {
        if (mRead(ShortCircuitIsDetected) == cFalse)
        {        
            mDATWriteTable(U1Bit, BUZZER, eBUZZER_FlasherClick, cTrue, Default);
        }
        else
        {
            // buzzer sound disabled during SC if faulty side is turned on 
            // or if both sides are faulty in Hazard mode
        }
    }

    TOSStartTempo( &TimerDILamps );
    TimerCurrentActiveTimeOut = 
        (mTOSConvMsInTimerTick((U32)DILampSignal.TimeDILampOn) - (tTOSTimer)1U);
    TimerCurrentInactiveTimeOut = 
        (mTOSConvMsInTimerTick((U32)DILampSignal.TimeDILampOff) - (tTOSTimer)1U);


    // Update Diag flashing frequency
    if (   (DILampSignal.DILampSideOn == cLeftSideOn)
        || (DILampSignal.DILampSideOn == cRightSideOn)  )
    {
        if ( mRead(BulbFailureDetected) == cTrue )
        {
            mDATWrite(U8Bit, 
                      FlashingFrequency, 
                      cDATCmnDegradedFlashingMode, 
                      Default
                     );
        }
        else
        {
            mDATWrite(U8Bit, 
                      FlashingFrequency, 
                      cDATCmnNormalFlashingMode, 
                      Default
                     );
        }
    }
    else if (DILampSignal.DILampSideOn == cRightAndLeftSideOn)
    {
        mDATWrite(U8Bit, FlashingFrequency, cDATCmnNormalFlashingMode, Default);
    }
    else
    {
        mDATWrite(U8Bit, FlashingFrequency, cDATCmnNoFlashing, Default);
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
BOOL LAPFliLampsOnTimeIsElapsed(void)
{
    const BOOL bLampsOnTimerIsElapsedL = 
                   TOSIsTimerElapsed(&TimerDILamps, TimerCurrentActiveTimeOut);

    return (BOOL)( bLampsOnTimerIsElapsedL  == cTrue );
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
void LAPFliMeasureCurrent(void)
{
#ifdef X90_PROJECT
    LAPFliMeasureCurrent_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPFliMeasureCurrent_Static(void)
{
#endif
    
    
    BOOL bBulbFailureIsPresentL;
    
    // Bulb Failure and Trailer Detection
    if ( mDATRead(U1Bit, DI_LEFT, Default) != mDATRead(U1Bit, DI_RIGHT, Default) )
    {
        mClear( BulbFailureDetected );

        // Measure current and check if there is a burned out lamp
        bBulbFailureIsPresentL = mDATRead(U1Bit, FlasherBulbFailure, Default);
    
        if ( bBulbFailureIsPresentL == cTrue )
        {
            mDATWrite(U8Bit, FlasherLampsTestResult, cDATCmnFlasherLampIsBurnedOut, Default);
            mSet( BulbFailureDetected );
        }
        else
        {
            mDATWrite(U8Bit, FlasherLampsTestResult, cDATCmnFlasherLampsAreOK, Default);
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
BOOL LAPFliMeasureCurrentOk(void)
{
    const tTOSTimer TimerDILampsElapsedTimeL = 
                        TOSGetTimerElapsedTime(&TimerDILamps);
    tTOSTimer       MeasureCurrentInterval;
    BOOL            bTimeForCurrentMeasureHasElapsed = cFalse;

    if ( TimerCurrentActiveTimeOut > mReadMeasureDefaultIntervalInTicks() )
    {
        MeasureCurrentInterval = mReadMeasureDefaultIntervalInTicks();
    }
    else
    {
        MeasureCurrentInterval = 
            TimerCurrentActiveTimeOut - (mTOSConvMsInTimerTick(cMeasureOffsetForSmallInterval));
        // Compensation for the case when timeout is equal to the elapsed time
        MeasureCurrentInterval--;
    }

    if( TimerDILampsElapsedTimeL > MeasureCurrentInterval )
    {
        bTimeForCurrentMeasureHasElapsed = cTrue;
        mDATControl(DATPan, FlashersCurrentMeasure);
        bFlasherSCBatOrOpenLoadReadAllowed  = cTrue;
    }

    return bTimeForCurrentMeasureHasElapsed;
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
void LAPFliInputManagement(void)
{
#ifdef X90_PROJECT
    LAPFliInputManagement_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPFliInputManagement_Static( void )
{
#endif

    BOOL bRfLockIsDetectedL;
    BOOL bRfUnlockIsDetectedL;
    BOOL bPWR_IGN_RisingEdgeIsDetectedL;
    BOOL bHAZARD_SW_FallingEdgeIsDetectedL;
    BOOL bCrashHazardDurationHasElapsedL;
    BOOL bCrashUnlockHasFinishedL;
    BOOL bCrashHazardWarningIsEnabledL;

    // -------------------------------------------------------------------------
    // LOCK ALL SIGNAL
    // -------------------------------------------------------------------------
    bRfLockIsDetectedL = TOSReadSignal(cTOSSignalLAPFliEventRfLockAll);
    if (   ( bRfLockIsDetectedL    == cTrue)
        && ( mAllDoorsAreClosed() == cTrue)  )
    {
        mSet(LockConfirmationIsRequested);
    }
    else
    {
        // Do nothing
    }

    // -------------------------------------------------------------------------
    // UNLOCK ALL SIGNAL
    // -------------------------------------------------------------------------
    bRfUnlockIsDetectedL = TOSReadSignal(cTOSSignalLAPFliEventRfUnlockAll);
    if (   ( bRfUnlockIsDetectedL  == cTrue)
        && ( mAllDoorsAreClosed() == cTrue)  )
    {
        mSet(UnlockConfirmationIsRequested);
    }
    else
    {
        // Do nothing
    }
        
    // ----------------------------------
    // TURN INDICATOR MANAGEMENT
    // ----------------------------------
    if ( mDATRead(U1Bit, PWR_IGN, Default) == cTrue )
    {
        if (   ( mDATRead(U1Bit, L_FLASHER_SW, Default) == cTrue ) 
            && ( mDATRead(U1Bit, R_FLASHER_SW, Default) == cTrue )   )
        {
            if ( bBothIndicatorsRequested == cFalse )
            {
                if ( mRead(TurnLeftIsRequested) == cTrue )
                {
                    // Right indicator turned while left flasher was on
                    mSet  ( TurnRightIsRequested );
                    mClear( TurnLeftIsRequested );
                    bBothIndicatorsRequested = cTrue;
                    ClearRFEvents();
                }
                else if ( mRead(TurnRightIsRequested) == cTrue )
                {
                    // Left indicator turned while right flasher was on
                    mSet  ( TurnLeftIsRequested );
                    mClear( TurnRightIsRequested );
                    bBothIndicatorsRequested = cTrue;
                    ClearRFEvents();
                }
                else
                {
                    // Do nothing
                }
            }
            else
            {
                // Do nothing
            }
        }
        else if ( mDATRead(U1Bit, L_FLASHER_SW, Default) == cTrue )
        {
            mSet  ( TurnLeftIsRequested );
            mClear( TurnRightIsRequested );
            bBothIndicatorsRequested = cFalse;
            ClearRFEvents();
        }
        else if ( mDATRead(U1Bit, R_FLASHER_SW, Default) == cTrue )
        {
            mSet  ( TurnRightIsRequested );
            mClear( TurnLeftIsRequested );
            bBothIndicatorsRequested = cFalse;
            ClearRFEvents();
        }
        else
        {
            mClear( TurnLeftIsRequested );
            mClear( TurnRightIsRequested );
            bBothIndicatorsRequested = cFalse;
        }
    }
    else
    {
        mClear( TurnLeftIsRequested );
        mClear( TurnRightIsRequested );
        bBothIndicatorsRequested = cFalse;
    }
 
    // -------------------------------------------------------------------------
    // CRASH HAZARD SIGNAL
    // -------------------------------------------------------------------------
    if ( mRead( CrashHazardIsRequested ) == cFalse )
    {
        bCrashUnlockHasFinishedL =
            TOSReadSignal(cTOSSignalLAPFliCrashUnlockFinished);
        bCrashHazardWarningIsEnabledL =
            mDATRead(U1Bit, EEP_DETCHOC, Default);

        if (   ( bCrashUnlockHasFinishedL      == cTrue) 
            && ( bCrashHazardWarningIsEnabledL == cTrue)  )
        {
            mSet( CrashHazardIsRequested );
            TOSStartTempo( &TimerCrashHazardDelay );

            //QACJ 3200: amarinm1: Reading is done just to clear the signal.
            TOSReadSignal(cTOSSignalRising_PWR_IGN_LAP_FLI);
            //QACJ 3200: amarinm1: Reading is done just to clear the signal.
            TOSReadSignal(cTOSSignalFalling_HAZARD_SW_LAP_FLI);
        }
        else
        {
            // Do nothing
        }  
    }
    else // CrashHazardIsRequested == cTrue
    {
        bPWR_IGN_RisingEdgeIsDetectedL = 
            TOSReadSignal(cTOSSignalRising_PWR_IGN_LAP_FLI);
        bHAZARD_SW_FallingEdgeIsDetectedL = 
            TOSReadSignal(cTOSSignalFalling_HAZARD_SW_LAP_FLI);
        bCrashHazardDurationHasElapsedL = 
            CrashHazardDurationTimerIsElapsed();

        if (   ( bPWR_IGN_RisingEdgeIsDetectedL    == cTrue)
            || ( bHAZARD_SW_FallingEdgeIsDetectedL == cTrue)
            || ( bCrashHazardDurationHasElapsedL   == cTrue)   )
        {
            mClear( CrashHazardIsRequested );
            mDATWrite(U1Bit, EEP_CrashHazardIsRequested, cFalse, Immediate);
            TOSStopTimer( &TimerCrashHazardDurationStep );
            u8TimerStepCrashHazard = 0;
        }
        else
        {
            // Do nothing
        }
    }

    // -------------------------------------------------------------------------
    // HAZARD SIGNAL DETERMINATION
    // -------------------------------------------------------------------------
    if (( mDATRead(U1Bit, HAZARD_SW, Default) == cTrue ) ||
        ( mDATRead(U1Bit, HazardAlarmRequested, Default) == cTrue))
    {
        mSet( DILampHazard );
    }
    else
    {
        if ( mRead( DILampHazard ) == cTrue )
        {
            mClear( DILampHazard );
            ClearRFEvents();
        }
        else
        {
            // Do nothing
        }
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
void LAPFliLeftFlashingForTFC( void )
{
    mSet(TurnLeftIsRequestedByTFC);
    mDATWrite(U8Bit, FlasherLampsTestResult, cDATCmnFlasherLampsNotTested, Default);
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
void LAPFliRightFlashingForTFC( void )
{
    mSet(TurnRightIsRequestedByTFC);
    mDATWrite(U8Bit, FlasherLampsTestResult, cDATCmnFlasherLampsNotTested, Default);
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
void LAPFliProtectionTask(void)
{
#ifdef X90_PROJECT
    LAPFliProtectionTask_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPFliProtectionTask_Static(void)
{
#endif
    // Manage timeout after output activation
    // Left
    if (mDATRead(U1Bit, DI_LEFT, Immediate) != cFalse)
    {
        if (u8ProtectionCounterLeft > 0)
        {
            u8ProtectionCounterLeft--;
        }
    }
    else
    {
        u8ProtectionCounterLeft = cProtectionHeatCountInitial;
    }
    // Right
    if (mDATRead(U1Bit, DI_RIGHT, Immediate) != cFalse)
    {
        if (u8ProtectionCounterRight > 0)
        {
            u8ProtectionCounterRight--;
        }
    }
    else
    {
        u8ProtectionCounterRight = cProtectionHeatCountInitial;
    }

    // Deprotection on rising edge of PWR_IGN
    if(     (cFalse != mDATRead(U1Bit, PWR_IGN, Default))
        &&  (cFalse == bPWR_IGNOld)
      )
    {
        if(mDATRead(U16Bit, EEP_SCLimit, Default) > mDATRead(U16Bit, EEP_CDLeftInd, Default))
        {
            mDATWrite(U1Bit, DI_LEFTProtection, 0, Default);
            mDATWrite(U1Bit, DefClignL, 0, Default);
        }
        if(mDATRead(U16Bit, EEP_SCLimit, Default) > mDATRead(U16Bit, EEP_CDRightInd, Default))
        {
            mDATWrite(U1Bit, DI_RIGHTProtection, 0, Default);
            mDATWrite(U1Bit, DefClignR, 0, Default);
        }

        bSCBattDetected = cFalse;
        u8FaultCounter = 0;
    }

    // Deprotection on Hazards request
    if(     (cHazard != DILampSignal.FlashingMode)
         && (cCrashHazard != DILampSignal.FlashingMode)
         && (cRFFeedback != DILampSignal.FlashingMode)
      )
    {
        if(mDATRead(U16Bit, EEP_SCLimit, Default) <= mDATRead(U16Bit, EEP_CDLeftInd, Default))
        {
            mDATWrite(U1Bit, DI_LEFTProtection, 1, Default);
        }
        if(mDATRead(U16Bit, EEP_SCLimit, Default) <= mDATRead(U16Bit, EEP_CDRightInd, Default))
        {
            mDATWrite(U1Bit, DI_RIGHTProtection, 1, Default);
        }
    }

    // SC VBAT detection management
    if(     (cOff != DILampSignal.FlashingMode)
        &&  (0 ==  mDATRead(U1Bit, DI_LEFT, Immediate)) 
        &&  (0 ==  mDATRead(U1Bit, DI_RIGHT, Immediate))
      )
    {
        if(cFalse != mDATRead(U1Bit, DIAG_FLASHER_SCGnd, Default))
        {
            if(cFalse == bSCBattDetected)
            {
                mDATWrite(U1Bit, DefClignL, 1, Default);
                mDATWrite(U1Bit, DefClignR, 1, Default);
                mDATWrite(U1Bit, EEP_DefClignL, 1, Default);
                mDATWrite(U1Bit, EEP_DefClignR, 1, Default);

                bSCBattDetected = cTrue;
            }
        }
        else if(    (0 == mDATRead(U1Bit, DI_RIGHTProtection, Default))
                 && (0 == mDATRead(U1Bit, DI_LEFTProtection, Default))
                 && (cFalse == mFlasherOpenLoad())
               )
        {
            u8FaultCounter = 0;
            bSCBattDetected = cFalse;
            mDATWrite(U1Bit, DefClignR, 0, Default);
            mDATWrite(U1Bit, DefClignL, 0, Default);
        }
        else
        {
            // Nothing to do
        }
    }

    // SC GND detection on LEFT Flahser
    if(     (1 ==  mDATRead(U1Bit, DI_LEFT, Immediate)) 
        &&  (0 ==  mDATRead(U1Bit, DI_RIGHT, Immediate))  // Hazard mode excluded
        &&  (0 ==  mDATRead(U1Bit, DI_LEFTProtection, Default))
      )
    {
        // 200ms inrush current timeout has elapsed or Open load detection is allowed
        if (    (0 == u8ProtectionCounterLeft)
             || (cFalse != bFlasherSCBatOrOpenLoadReadAllowed)
           ) 
        {
            if(     (   (cFalse != mDATRead(U1Bit, DIAG_FLASHER_SCGnd, Default))
                     && (cFalse == bSCBattDetected)
                    )
                ||  (   (cFalse != bFlasherSCBatOrOpenLoadReadAllowed)
                     && (cFalse != mFlasherOpenLoad())
                    )
              ) 
            {
                u8FaultCounter++;
                if(     (u8FaultCounter >= cSCToGNDCountThreshold)
                     || (cFalse != mFlasherOpenLoad())
                  )
                {
                    // Set LEFT flasher defect, perform open load detection check
                    // Protect the flasher output only in case of SC GND
                    SetFlasherDefect(cTrue, cFalse, cTrue);
                }
            }
            else
            {
                if(cFalse == mFlasherOpenLoad())
                {
                    u8FaultCounter = 0;
                    mDATWrite(U1Bit, DefClignL, 0, Default);
                }
            }
        }
    }
    // SC GND detection on RIGHT flasher. Do not enter here if
    // LEFT flasher has been temporary stopped for troubleshooting
    // in Hazard mode '(cFalse == bLeftFlasherStopped)'
    else if(    (1 ==  mDATRead(U1Bit, DI_RIGHT, Immediate))
             && (0 ==  mDATRead(U1Bit, DI_LEFT, Immediate))  // Hazard mode excluded
             && (0 ==  mDATRead(U1Bit, DI_RIGHTProtection, Default))
             && (cFalse == bLeftFlasherStopped)
           )
    {
        // 200ms inrush current timeout has elapsed or Open load detection is allowed
        if (    (0 == u8ProtectionCounterRight)
             || (cFalse != bFlasherSCBatOrOpenLoadReadAllowed)
           )
        {
            if(     (   (cFalse != mDATRead(U1Bit, DIAG_FLASHER_SCGnd, Default))
                     && (cFalse == bSCBattDetected)
                    )
                ||  (   (cFalse != bFlasherSCBatOrOpenLoadReadAllowed)
                     && (cFalse != mFlasherOpenLoad())
                    )
              ) 
            {
                u8FaultCounter++;
                if(     (u8FaultCounter >= cSCToGNDCountThreshold)
                     || (cFalse != mFlasherOpenLoad())
                  )
                {
                    // Set RIGHT flasher defect, perform open load detection check.
                    // Protect the flasher output only in case of SC GND
                    SetFlasherDefect(cFalse, cTrue, cTrue);
                }
            }
            else
            {
                if(cFalse == mFlasherOpenLoad())
                {
                    u8FaultCounter = 0;
                    mDATWrite(U1Bit, DefClignR, 0, Default);
                }
            }
        }
    }
    // SC GND detection on HAZARD activated. Enter here if LEFT flasher 
    // has been temporary stopped for troubleshooting in Hazard mode 
    // '(cFalse != bLeftFlasherStopped)'
    else if(    (   (1 == mDATRead(U1Bit, DI_RIGHT, Immediate))
                 && (1 == mDATRead(U1Bit, DI_LEFT, Immediate))  // Hazard mode
                 && (   (0 == mDATRead(U1Bit, DI_RIGHTProtection, Default))
                     && (0 == mDATRead(U1Bit, DI_LEFTProtection, Default))
                    )
                )
             || (cFalse != bLeftFlasherStopped)
           )
    {
        // 200ms inrush current timeout has elapsed or Open load detection is allowed
        if (    (0 == u8ProtectionCounterRight) // u8ProtectionCounterLeft is expected to have the same value
             || (cFalse != bFlasherSCBatOrOpenLoadReadAllowed)
           )
        {
            if(     (   (cFalse != mDATRead(U1Bit, DIAG_FLASHER_SCGnd, Default))
                     && (cFalse == bSCBattDetected)
                    )
                &&  (cFalse == bFlasherSCBatOrOpenLoadReadAllowed)
              ) 
            {
                u8FaultCounter++;
                if(u8FaultCounter >= cSCToGNDCountThreshold)
                {
                    if(cFalse == bLeftFlasherStopped)
                    {
                        // Temporary protect Left flasher to detect the defective side
                        mDATWrite(U1Bit, DI_LEFTProtection, 1, Default);
                        bLeftFlasherStopped = cTrue;
                    }
                    // LEFT flasher has been temporary stopped and defect still exists
                    // => set defect on RIGHT flasher
                    else
                    {
                        // Set RIGHT flasher defect, perform open load detection check.
                        // Protect the flasher output only in case of SC GND
                        SetFlasherDefect(cFalse, cTrue, cTrue);

                        // Remove the temporary protectection on Left flasher
                        mDATWrite(U1Bit, DI_LEFTProtection, 0, Default);
                        bLeftFlasherStopped = cFalse;
                    }
                }
            }
            // Set defect on both sides in case of Open Load
            else if(    (cFalse != mFlasherOpenLoad())
                     && (cFalse != bFlasherSCBatOrOpenLoadReadAllowed)
                   )
            {
                mDATWrite(U1Bit, DefClignL, 1, Default);
                mDATWrite(U1Bit, EEP_DefClignL, 1, Default);
                mDATWrite(U1Bit, DefClignR, 1, Default);
                mDATWrite(U1Bit, EEP_DefClignR, 1, Default);
            }
            else
            {
                // LEFT flasher has been temporary stopped and defect has disappeared
                // => set defect on LEFT flasher
                if(cFalse != bLeftFlasherStopped)
                {
                    // Set LEFT flasher defect, do not perform open load detection check
                    // => Protect the flasher output
                    SetFlasherDefect(cTrue, cFalse, cFalse);

                    bLeftFlasherStopped = cFalse;
                }
                else if(    (cFalse == bSCBattDetected)
                         && (cFalse == mFlasherOpenLoad())
                       )
                {
                    u8FaultCounter = 0;
                    mDATWrite(U1Bit, DefClignR, 0, Default);
                    mDATWrite(U1Bit, DefClignL, 0, Default);
                }
                else
                {
                    // Nothing to do
                }
            }

        }
    }
    else
    {
        // do nothing
    }

    bFlasherSCBatOrOpenLoadReadAllowed = cFalse;
    bPWR_IGNOld = mDATRead(U1Bit, PWR_IGN, Default);
}

// [EXPORTED_FUNCTIONS_END]

