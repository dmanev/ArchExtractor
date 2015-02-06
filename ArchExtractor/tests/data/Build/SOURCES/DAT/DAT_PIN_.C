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
// Component:    DAT_PIN
// -----------------------------------------------------------------------------
// $Date:   Mar 02 2010 10:53:38  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_PIN/DAT_PIN.C-arc  $
// $Revision:   1.29  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_PIN/DAT_PIN.C-arc  $
// 
//    Rev 1.29   Mar 02 2010 10:53:38   adzhelp
// Cm006814: Max values for TPS_IMPUL_MINI and TPS_FILT_AF corrected
// 
//    Rev 1.28   Mar 01 2010 15:37:58   adzhelp
// Cm007579: Changed thresholds on inputs managed by analog input
// 
//    Rev 1.27   Feb 24 2010 15:55:14   adzhelp
// Cm007212:  HWP: SC detection of Verlog LED in sleep mode
// 
//    Rev 1.26   Feb 19 2010 14:15:16   adzhelp
// Cm006690: FRW&RRW: Big initial time delay of output relay switching off
// 
//    Rev 1.25   Feb 05 2010 15:27:06   adzhelp
// Cm006567: Defroster filtration after reset
// 
//    Rev 1.24   Feb 03 2010 10:11:54   adzhelp
// Cm006590, Cm006698: Inputs management during undervoltage
// 
//    Rev 1.23   Jan 15 2010 13:46:16   adzhelp
// Cm006838: HSI: Changing thresholds on the three digital input managed by analog input
// 
//    Rev 1.22   Dec 03 2009 10:34:40   amarinm1
// Cm006636: SW is now kept awake only when Position lights, hazard switch or ignition are active (doors and CDL switch removed).
// 
//    Rev 1.21   Nov 30 2009 16:33:34   amarinm1
// Cm006695: TPS_FILT_AF new value is taken into account on IGN rising edge.
// 
//    Rev 1.20   Nov 03 2009 16:36:14   adzhelp
// Cm006598: Wake-up on raising edge of POSITION_LIGHTS
// 
//    Rev 1.19   Oct 06 2009 11:00:10   adzhelp
// Cm006155: Enter in active sleep mode when requested from LDB_DIN
// 
//    Rev 1.18   Sep 24 2009 10:13:00   adzhelp
// Cm003262: EFX90_SW2_FP04 : Implementation of the Rear Wipers functionality
// 
//    Rev 1.17   Sep 16 2009 10:54:20   amarinm1
// Cm006271: Reading of TPS_FILT_AF was moved from DATPinLeaveStartingStepState() to FrontWiperAutostopFiltration().
// 
//    Rev 1.16   Jul 24 2009 09:07:48   adzhelp
// Cm005136: Produce control after inputs are read after starting step
// 
//    Rev 1.15   Jul 24 2009 08:48:54   adzhelp
// Cm005104: Allow fast initialization by analog inputs and shorten time by explicit tasks activation on starting step
// 
//    Rev 1.14   Jul 10 2009 10:02:56   adzhelp
// Cm005104, Cm004985: Immediate checks for wakeup implemented
// 
//    Rev 1.13   Apr 27 2009 16:56:12   adzhelp
// Cm003264: Implementation of doorlock
// 
//    Rev 1.12   Apr 22 2009 10:01:06   adzhelp
// Cm003261: Implementation of front wiper autostop filtration
// 
//    Rev 1.11   Apr 16 2009 09:40:44   adzhelp
// Cm003276: Analog inputs reading synchronized with LDB_SUP; callback for wakeup from LDB_DIN added
// 
//    Rev 1.10   Apr 13 2009 15:55:12   adzhelp
// Cm003619: Analog converter changed to 10 bit
// 
//    Rev 1.9   Apr 07 2009 12:22:58   adzhelp
// Cm003270: Implementation of DEFROSTER filtration
// 
//    Rev 1.8   Mar 31 2009 15:25:26   adzhelp
// Cm003276: Controls produced for changing of inputs instead of signals writing
// 
//    Rev 1.7   Mar 30 2009 14:17:58   adzhelp
// Cm003465: Conversion of analog inputs to digital ones excluded for simulation
// 
//    Rev 1.6   Mar 20 2009 18:02:36   adzhelp
// Cm003263: Added signaling for HAZARD_SW and PWR_IGN for LAP_FLI
// 
//    Rev 1.5   Mar 20 2009 17:30:14   adzhelp
// Cm003619: Parameterization according to HSI
// 
//    Rev 1.4   21 Jan 2009 15:55:58   avidoly
// Cm003209: EFX90_SW1_FP02: Implementation of the Interior Lights functionality (corrected signal)
// 
//    Rev 1.3   20 Jan 2009 14:10:40   avidoly
// Cm003276:  EFX90_SW1_FP13 : Implementation of the Wake Up & Sleep functionality
// Added signals for system wake up and maintain Active state
// 
//    Rev 1.2   02 Dec 2008 16:07:12   ailievb
// Cm003619: Parametrization of DAT_PIN
//
//    Rev 1.1   24 Nov 2008 15:19:12   ailievb
// Cm003619: Integration of DAT_PIN
//
//    Rev 1.0   10 Nov 2008 10:21:12   ailievb
// Initial revision.
//******************************************************************************

//------------------------------------------------------------------------------
// Body Identification
//------------------------------------------------------------------------------
#define dat_Pin  "dat_Pin"

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------
#include "lib.h"
#include "tos.h"
#include "dat.h"
#include "dat_Pin.h"
#include "dat_Pinp.h"


//------------------------------------------------------------------------------
// Local constants
//------------------------------------------------------------------------------
// Analog inputs
#if (cDATAnaNumberOfBitsNonType == 8UL)
// 1 LSB = 19.608 mV
#define cAdcThresholdHigh                   (U8)64 // 1.25 V
#define cAdcThresholdLow                    (U8)51 // 1 V
#elif (cDATAnaNumberOfBitsNonType == 10UL)
// 1 LSB = 4.89 mV
#define cAdcThresholdHigh                   (U16)153 // 0.75 V
#define cAdcThresholdLow                    (U16)102 // 0.5 V
#endif

#define cValueActiveMaxAI_RR_DOORS_SW       cAdcThresholdLow
#define cValueInactiveMinAI_RR_DOORS_SW     cAdcThresholdHigh
#define cValueActiveMaxAI_DOOR_UNLOCK_SW    cAdcThresholdLow
#define cValueInactiveMinAI_DOOR_UNLOCK_SW  cAdcThresholdHigh
#define cValueActiveMinFR_WIPER_INT_SW      cAdcThresholdHigh
#define cValueInactiveMaxFR_WIPER_INT_SW    cAdcThresholdLow

// Defroster
// number of steps for dat_din task( task is at 5ms) to reach 25 ms ( TPS_IMPUL_MINI step):
#define cDATPinNbOfStepsForTPS_IMPUL_MINI   (U8)5U 
// Maximal value of EEP_TPS_IMPUL_MINI
#define cDATPinMaxTPS_IMPUL_MINI            (U8)20U

// Front wipers
#define cEEP_TPS_FILT_AFMax                 (U8)13U
#define cTPS_FILT_AFStepMs                  (U8)6U
#define cEEP_TPS_POSIT_BALAISMax            (U8)7U
#define cEEP_TPS_POSIT_BALAISStepMs         (U8)6U

#define cSpeedPosition              ((U8)0)
#define cTransitionToStopPosition   ((U8)1)
#define cStopPositionDetected       ((U8)2)
#define cStopAllowed                ((U8)3)

// Active sleep duration
#define cActiveSleepDurationInMs    600UL

//------------------------------------------------------------------------------
// Local macros
//------------------------------------------------------------------------------

// ****************************************************************************
//  State Change Macros
//                        *** WARNING ***
//  Theses states are available during the call of DATPinStateChange function.
//  ***************************************************************************
#define mIsRaisingEdge(Data)    \
   mDATDinGetRaisingEdge( cDATPin##Data##ByteIndex, cDATPin##Data##BitIndex )   
         
#define mIsFallingEdge(Data)    \
   mDATDinGetFallingEdge( cDATPin##Data##ByteIndex, cDATPin##Data##BitIndex )  
          
#define mIsStateChange(Data)    \
   mDATDinGetStateChange( cDATPin##Data##ByteIndex, cDATPin##Data##BitIndex )            

// *****************************************************************************
//  Immediate State Change Macros : for use in sleep mode
//                        *** WARNING ***
//  Non-filtered states are used
//  ***************************************************************************/
#define mIsRaisingEdgeImmediate(Data)    \
   mGetRaisingEdgeImmediate( cDATPin##Data##ByteIndex, cDATPin##Data##BitIndex )   
         
#define mIsFallingEdgeImmediate(Data)    \
   mGetFallingEdgeImmediate( cDATPin##Data##ByteIndex, cDATPin##Data##BitIndex )  
          
#define mIsStateChangeImmediate(Data)    \
   mGetStateChangeImmediate( cDATPin##Data##ByteIndex, cDATPin##Data##BitIndex )            

// Implementation of immediate state change macros
#define mGetRaisingEdgeImmediate(ByteNbr,BitNbr) \
      ((BOOL)((mDATDinGetNonFilteredValue( (ByteNbr),(BitNbr)) == cTrue)\
               && (mDATDinGetFilteredValue( (ByteNbr),(BitNbr)) == cFalse)))

#define mGetFallingEdgeImmediate(ByteNbr,BitNbr) \
      ((BOOL)((mDATDinGetNonFilteredValue( (ByteNbr),(BitNbr)) == cFalse)\
               && (mDATDinGetFilteredValue( (ByteNbr),(BitNbr)) == cTrue)))

#define mGetStateChangeImmediate(ByteNbr,BitNbr) \
      ((BOOL)(mDATDinGetNonFilteredValue( (ByteNbr),(BitNbr)) \
               != mDATDinGetFilteredValue( (ByteNbr),(BitNbr)) ) )

// Retain present filtered value: copy from filtered to non-filtered buffer
#define mRetainInput(Data) \
    mDATDinSetNonFilteredValue(cDATPin##Data##ByteIndex, cDATPin##Data##BitIndex, \
        mDATDinGetFilteredValue(cDATPin##Data##ByteIndex, cDATPin##Data##BitIndex))

// Rear and front wipers
#if defined(_QAC_) || defined(TESTU)
#define mForceFrwGraphsExecution() NOP()
#define mForceRrwGraphsExecution() NOP()
#else
#define mForceFrwGraphsExecution() \
        /* Call all front wiper graphs */ \
        TOSSeqMotor(cTOSSeqGraphIdLAPFrwEngineProtection, cTOSSeqGraphIdLAPFrwControl); \
        mForceOutputsRefresh()

#define mForceRrwGraphsExecution() \
        /* Call all rear wiper graphs */ \
        TOSSeqMotor(cTOSSeqGraphIdLAPRrwEngineProtection, cTOSSeqGraphIdLAPRrwControl); \
        mForceOutputsRefresh()

#define mForceOutputsRefresh() mDATDouRefreshOutput()

#endif

//------------------------------------------------------------------------------
// Local types
//------------------------------------------------------------------------------

// This is an example:
// typedef Expression   tTypeName;

//------------------------------------------------------------------------------
// Local data
//------------------------------------------------------------------------------
static U8 u8DefrosterSWCounter;
static BOOL bPreviousFR_AUTOSTOP_SW;
static BOOL bPreviousRR_AUTOSTOP_SW;
static U8 u8WipersStopFilteringTicks;
static U8 u8FrAutostopTimeCounter;
static U8 u8RrAutostopTimeCounter;
static U8 u8FrontWiperStopState;
static U8 u8RearWiperStopState;
static BOOL bInputsReadAfterStartingStepState;
static U8 u8TPS_FILT_AF;

static tTOSTimer ActiveSleepTimer;

static tTOSTimer TestVerlogTimer;
//------------------------------------------------------------------------------
// Constant local data
//------------------------------------------------------------------------------

// This is an example:
// static const tType  cConstantName;

//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------
BOOL bDATPinDefrosterSWFiltered;
BOOL bDATPinSleepMode = cTrue;

//------------------------------------------------------------------------------
// Constant exported data
//------------------------------------------------------------------------------
const U8 DATPinInitArray[] = cDATPinInitBufferDinGeneratorMessage;

//------------------------------------------------------------------------------
// Local function prototypes
//------------------------------------------------------------------------------
static void DefrosterFiltration(void);
static U8 DetermineFrwAutostopOffset(void);
static void FrontWiperAutostopFiltration(void);
static U8 DetermineRrwAutostopOffset(void);
static void RearWiperAutostopFiltration(void);
static MEM_TYPE void WipersParametersRefresh(void);
static MEM_TYPE void SleepModeAnalogInputsReading(void);
static MEM_TYPE void SleepModeStateChange(void);

#ifdef X90_PROJECT
static MEM_TYPE void DATPinEnterActiveState_Static(void);
#endif

//==============================================================================
//=========================== LOCAL FUNCTIONS ==================================
//==============================================================================

//==============================================================================
// DESCRIPTION : Rear defroster filtration
//  
// PARAMETERS (Type,Name,Min,Max) :  none
//
// RETURN VALUE :  none
// 
// DESIGN INFORMATION :  refer to Detailed Design Document
//==============================================================================
static void DefrosterFiltration(void)
{
    if (u8DefrosterSWCounter > 0)
    {
        u8DefrosterSWCounter--;
    }

    if (u8DefrosterSWCounter == 0)
    {
        bDATPinDefrosterSWFiltered = mDATRead(U1Bit,DEFROSTER_SW,Default);

        if (mIsFallingEdge(DEFROSTER_SW))
        {
            U8 u8EEP_TPS_IMPUL_MINI = mDATRead(U8Bit, EEP_TPS_IMPUL_MINI, Default);
            if (u8EEP_TPS_IMPUL_MINI > cDATPinMaxTPS_IMPUL_MINI)
            {
                u8EEP_TPS_IMPUL_MINI = cDATPinMaxTPS_IMPUL_MINI;
            }
            u8DefrosterSWCounter = u8EEP_TPS_IMPUL_MINI * cDATPinNbOfStepsForTPS_IMPUL_MINI;
        }
    }
    else
    {
        // Wait for Tpush timeout
    }
}

//==============================================================================
// DESCRIPTION : Determine front wiper autostop offset
//  
// PARAMETERS (Type,Name,Min,Max) :  none
//
// RETURN VALUE :  none
// 
// DESIGN INFORMATION :  refer to Detailed Design Document
//==============================================================================
#ifdef X90_PROJECT
#pragma optimize=no_inline
#endif
static U8 DetermineFrwAutostopOffset(void)
{
    U8 u8FrOffsetTimeInTaskTicksL;
    U8 u8TPS_POSIT_BALAISL = mDATRead(U8Bit, EEP_TPS_POSIT_BALAIS, Default);


    if (u8TPS_POSIT_BALAISL > cEEP_TPS_POSIT_BALAISMax)
    {
        u8TPS_POSIT_BALAISL = cEEP_TPS_POSIT_BALAISMax;
    }

    // TPS_POSIT_BALAIS     DATDinTask   Ticks  Corrected ticks
    // x 1 = 6 ms           5 ms         1      0
    // x 2 = 12 ms          10 ms        2      1
    // x 3 = 18 ms          20 ms        4      3
    // x 4 = 24 ms          25 ms        5      4
    // x 5 = 30 ms          30 ms        6      5
    // x 6 = 36 ms          35 ms        7      6
    // x 7 = 42 ms          40 ms        8      7

    // aim is to avoid use of DIV / MUL in active mode
    if (u8TPS_POSIT_BALAISL < (U8)2U)
    {
        u8FrOffsetTimeInTaskTicksL = 0;
    }
    else if (u8TPS_POSIT_BALAISL == (U8)2U)
    {
        u8FrOffsetTimeInTaskTicksL = 1U;
    }
    else
    {
        u8FrOffsetTimeInTaskTicksL = u8TPS_POSIT_BALAISL - 1U;
    }

    return u8FrOffsetTimeInTaskTicksL;
}

//==============================================================================
// DESCRIPTION : Front Wiper Autostop Filtration
//  
// PARAMETERS (Type,Name,Min,Max) :  none
//
// RETURN VALUE :  none
// 
// DESIGN INFORMATION :  refer to Detailed Design Document
//==============================================================================
static void FrontWiperAutostopFiltration(void)
{
    BOOL bFR_AUTOSTOP_SW = mDATRead(U1Bit, FR_AUTOSTOP_SW, Immediate);
    U8 u8FrOffsetTimeInTaskTicksL;


    if (bFR_AUTOSTOP_SW != cFalse)
    {
        if (bPreviousFR_AUTOSTOP_SW == cFalse) 
        {
            u8FrAutostopTimeCounter = 0;
            u8FrontWiperStopState = cTransitionToStopPosition;
        }

        if (   (bPreviousFR_AUTOSTOP_SW != cFalse) 
            || (u8WipersStopFilteringTicks < 1)   ) // important for short durations
        {
            if (u8FrontWiperStopState == cTransitionToStopPosition)
            {
                u8FrAutostopTimeCounter++;
                if (u8FrAutostopTimeCounter >= u8WipersStopFilteringTicks)
                {
                    TOSSendControl(cTOSControlFrontStopPositionDetected);
                    u8FrontWiperStopState = cStopPositionDetected;
                    u8FrAutostopTimeCounter = 0;

                    // Determination of offset time
                    // placed here for optimization
                    u8FrOffsetTimeInTaskTicksL = DetermineFrwAutostopOffset();
                
                    if(u8FrAutostopTimeCounter >= u8FrOffsetTimeInTaskTicksL)
                    {
                        TOSWriteSignal(cTOSSignalFrontWiperStopIsAllowed_LAP_FRW);
                        mForceFrwGraphsExecution();
                        u8FrontWiperStopState = cStopAllowed;
                    }
                }
            }
            else if (u8FrontWiperStopState == cStopPositionDetected)
            {
                u8FrAutostopTimeCounter++;

                // Determination of offset time
                // placed here for optimization
                u8FrOffsetTimeInTaskTicksL = DetermineFrwAutostopOffset();
                
                if(u8FrAutostopTimeCounter >= u8FrOffsetTimeInTaskTicksL)
                {
                    TOSWriteSignal(cTOSSignalFrontWiperStopIsAllowed_LAP_FRW);
                    mForceFrwGraphsExecution();
                    u8FrontWiperStopState = cStopAllowed;
                }
            }
            else
            {
                //cStopAllowed
            }
        }
    }
    else // FR_AUTOSTOP_SW == 0
    {
        u8FrAutostopTimeCounter = 0;
        u8FrontWiperStopState = cSpeedPosition;

        if (bPreviousFR_AUTOSTOP_SW != cFalse)
        {
            TOSWriteSignal(cTOSSignalFR_AUTOSTOP_SWFalling_LAP_FRW);
        }
    }
    bPreviousFR_AUTOSTOP_SW = mDATRead(U1Bit, FR_AUTOSTOP_SW, Immediate);
}

//==============================================================================
// DESCRIPTION : Determine rear wiper autostop offset
//  
// PARAMETERS (Type,Name,Min,Max) :  none
//
// RETURN VALUE :  none
// 
// DESIGN INFORMATION :  refer to Detailed Design Document
//==============================================================================
#ifdef X90_PROJECT
#pragma optimize=no_inline
#endif
static U8 DetermineRrwAutostopOffset(void)
{
    U8 u8RrOffsetTimeInTaskTicksL;
    U8 u8TPS_POSIT_BALAIS_ARL = mDATRead(U8Bit, EEP_TPS_POSIT_BALAIS_AR, Default);
    
    if (u8TPS_POSIT_BALAIS_ARL > cEEP_TPS_POSIT_BALAISMax)
    {
        u8TPS_POSIT_BALAIS_ARL = cEEP_TPS_POSIT_BALAISMax;
    }

    // TPS_POSIT_BALAIS_AR  DATDinTask   Ticks  Corrected ticks
    // x 1 = 6 ms           5 ms         1      0
    // x 2 = 12 ms          10 ms        2      1
    // x 3 = 18 ms          20 ms        4      3
    // x 4 = 24 ms          25 ms        5      4
    // x 5 = 30 ms          30 ms        6      5
    // x 6 = 36 ms          35 ms        7      6
    // x 7 = 42 ms          40 ms        8      7

    // aim is to avoid use of DIV / MUL in active mode
    if (u8TPS_POSIT_BALAIS_ARL < (U8)2U)
    {
        u8RrOffsetTimeInTaskTicksL = 0;
    }
    else if (u8TPS_POSIT_BALAIS_ARL == (U8)2U)
    {
        u8RrOffsetTimeInTaskTicksL = 1U;
    }
    else
    {
        u8RrOffsetTimeInTaskTicksL = u8TPS_POSIT_BALAIS_ARL - 1U;
    }

    return u8RrOffsetTimeInTaskTicksL;
}

//==============================================================================
// DESCRIPTION : Rear Wiper Autostop Filtration
//  
// PARAMETERS (Type,Name,Min,Max) :  none
//
// RETURN VALUE :  none
// 
// DESIGN INFORMATION :  refer to Detailed Design Document
//==============================================================================
static void RearWiperAutostopFiltration(void)
{
    BOOL bRR_AUTOSTOP_SW = mDATRead(U1Bit, RR_AUTOSTOP_SW, Immediate);
    U8 u8RrOffsetTimeInTaskTicksL;

    if (bRR_AUTOSTOP_SW != cFalse)
    {
        if (bPreviousRR_AUTOSTOP_SW == cFalse) 
        {
            u8RrAutostopTimeCounter = 0;
            u8RearWiperStopState = cTransitionToStopPosition;
        }

        if (   (bPreviousRR_AUTOSTOP_SW != cFalse) 
            || (u8WipersStopFilteringTicks < 1)   ) // important for short durations
        {
            if (u8RearWiperStopState == cTransitionToStopPosition)
            {
                u8RrAutostopTimeCounter++;
                if (u8RrAutostopTimeCounter >= u8WipersStopFilteringTicks)
                {
                    TOSSendControl(cTOSControlRearStopPositionDetected);
                    u8RearWiperStopState = cStopPositionDetected;
                    u8RrAutostopTimeCounter = 0;

                    // Determination of offset time
                    // placed here for optimization
                    u8RrOffsetTimeInTaskTicksL = DetermineRrwAutostopOffset();
                
                    if(u8RrAutostopTimeCounter >= u8RrOffsetTimeInTaskTicksL)
                    {
                        TOSWriteSignal(cTOSSignalRearWiperStopIsAllowed_LAP_RRW);                    
                        mForceRrwGraphsExecution();
                        u8RearWiperStopState = cStopAllowed;
                    }
                }
            }
            else if (u8RearWiperStopState == cStopPositionDetected)
            {
                u8RrAutostopTimeCounter++;

                // Determination of offset time
                // placed here for optimization
                u8RrOffsetTimeInTaskTicksL = DetermineRrwAutostopOffset();
                
                if(u8RrAutostopTimeCounter >= u8RrOffsetTimeInTaskTicksL)
                {
                    TOSWriteSignal(cTOSSignalRearWiperStopIsAllowed_LAP_RRW);                    
                    mForceRrwGraphsExecution();
                    u8RearWiperStopState = cStopAllowed;
                }
            }
            else
            {
                //cStopAllowed
            }
        }
    }
    else // RR_AUTOSTOP_SW == 0
    {
        u8RrAutostopTimeCounter = 0;
        u8RearWiperStopState = cSpeedPosition;

        if (bPreviousRR_AUTOSTOP_SW != cFalse)
        {
            TOSWriteSignal(cTOSSignalRR_AUTOSTOP_SWFalling_LAP_RRW);
        }
    }
    bPreviousRR_AUTOSTOP_SW = mDATRead(U1Bit, RR_AUTOSTOP_SW, Immediate);
}

//==============================================================================
// DESCRIPTION : Wipers Parameters Refresh
//  
// PARAMETERS (Type,Name,Min,Max) :  none
//
// RETURN VALUE :  none
// 
// DESIGN INFORMATION :  refer to Detailed Design Document
//==============================================================================
#ifdef X90_PROJECT
#pragma optimize=no_inline
#endif
static MEM_TYPE void WipersParametersRefresh(void)
{
    // Wipers parameter to be updated on ignition on
    if (u8TPS_FILT_AF != mDATRead(U8Bit, EEP_TPS_FILT_AF, Default))
    {
        u8TPS_FILT_AF = mDATRead(U8Bit, EEP_TPS_FILT_AF, Default);

        if (u8TPS_FILT_AF > cEEP_TPS_FILT_AFMax)
        {
            u8TPS_FILT_AF = cEEP_TPS_FILT_AFMax;
        }
        
        
        if (u8TPS_FILT_AF < (U8)2U)
        {
            u8WipersStopFilteringTicks = 0;
        }
        else if (u8TPS_FILT_AF == (U8)2U)
        {
            u8WipersStopFilteringTicks = 1U;
        }
        else
        {
            u8WipersStopFilteringTicks = mDiv((U8)(u8TPS_FILT_AF * (U8)cTPS_FILT_AFStepMs), 
                (U8)cDATDinNominalSamplingPeriodValueMs) - (U8)1U;
        }
    }
}

//==============================================================================
// DESCRIPTION :
//  
// PARAMETERS (Type,Name,Min,Max) :  none
//
// RETURN VALUE :  none
// 
// DESIGN INFORMATION :  refer to Detailed Design Document
//==============================================================================
#ifdef X90_PROJECT
#pragma optimize=no_inline
#endif
static MEM_TYPE void SleepModeAnalogInputsReading(void)
{
    tMsg Msg;
    U8 Buffer[cLDBSupMessageLength];
    Msg.Lng = cLDBSupMessageLength;
    Msg.pBuffer = Buffer;
    LDBReceiveWithoutAddr(cLDBChannelSup, &Msg);

    if (Buffer[cLDBSupAnalogConversionAllowedIndex] != cFalse)
    {
        // Only in sleep mode during wake up detection sequence on 40 ms
        // need to be done here in order to capture analog wakeup inputs
        if (Buffer[cLDBSupClockForActiveModeSelectedIndex] == cFalse)
        {
            // DATDinTask is executed on internal oscillator: need to synchronize 
            // sleep system timer
            LDBControl(cLDBChannelSup, cLDBSupSynchronizeSleepTimer);
        }
        else
        {
            // invoke directly DAT_ANA task
            #ifndef cLDB_ANAIsSynchronous
                #error "LDB_ANA must operate in synchronous mode"
            #endif
            DATAnaTask();
        }
        LDBControl(cLDBChannelSup, cLDBSupWakeUpDetectionPinStarted);

        // HW protection of LED verlog in sleep mode
        TOSSendControl(cTOSControlProtectionLedVerlogSleepMode);
    }
    else
    {
        // direct analog conversion is not allowed yet by LDB
    }
}

//==============================================================================
//  DESCRIPTION : Indicates that input has changed in sleep mode
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//==============================================================================
#ifdef X90_PROJECT
#pragma optimize=no_inline
#endif
static MEM_TYPE void SleepModeStateChange(void)
{
    // Sleep mode
    // Check for wake up conditions (non-filtered inputs)

    if (  mIsRaisingEdgeImmediate(PWR_IGN)
       || mIsRaisingEdgeImmediate(POSITION_LIGHTS)
       || mIsRaisingEdgeImmediate(HAZARD_SW)
       || mIsStateChangeImmediate(FR_DOORS_SW)
       || mIsStateChangeImmediate(RR_DOORS_SW)
       || mIsRaisingEdgeImmediate(DOOR_LOCK_SW)
       || mIsRaisingEdgeImmediate(DOOR_UNLOCK_SW))
    {
       TOSSendControl(cTOSControlWakeUpRequest);
       bDATPinSleepMode = cFalse; // set flag immediate to forbid further direct analog conversion
    }

    if (bInputsReadAfterStartingStepState != cFalse)
    {
        // Components connected to this control may read inputs using Immediate access
        TOSSendControl(cTOSControlInputsReadAfterStartingStepState); 
        // Used by components to check blocked buttons
        bInputsReadAfterStartingStepState = cFalse;

        // Check for defroster blocked button
        if (  (mDATRead(U1Bit,EEP_AUTDEGIVRAGE,Default) != cFalse)
            &&(mDATRead(U1Bit,DEFROSTER_SW, Immediate) != cFalse))
        {
            bDATPinDefrosterSWFiltered = cTrue;
            u8DefrosterSWCounter = cDATPinNbOfStepsForTPS_IMPUL_MINI;
        }
    }
}

//==============================================================================
//=========================== EXPORTED FUNCTIONS ===============================
//==============================================================================

//==============================================================================
//  DESCRIPTION : Initialise DAT_Pin and DAT_DIN component
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//==============================================================================
void DATPinInit(void)
{
    DATDinInit(DATPinInitArray);
}

//==============================================================================
//  DESCRIPTION : Allows to invalidate some inputs
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//==============================================================================
void DATPinSelection(void)
{
#if (!defined(COMPILATION_NATIVE) || defined(TESTU))

    // For simulation the inputs RR_DOORS_SW, DOOR_UNLOCK_SW, FR_WIPER_INT_SW
    // can be set as digital inputs
    U16 u16AdcValue;

    if (bDATPinSleepMode != cFalse)
    {
        SleepModeAnalogInputsReading();
    }

    u16AdcValue = mDATRead(U16Bit, AI_RR_DOORS_SW, Immediate);
    if (u16AdcValue < cValueActiveMaxAI_RR_DOORS_SW)
    {
        mDATWrite(U1Bit, RR_DOORS_SW, cTrue, Delayed);
    }
    else if (u16AdcValue > cValueInactiveMinAI_RR_DOORS_SW)
    {
        mDATWrite(U1Bit, RR_DOORS_SW, cFalse, Delayed);
    }
    else
    {
        // no change of input
    }

    u16AdcValue = mDATRead(U16Bit, AI_DOOR_UNLOCK_SW, Immediate);
    if (u16AdcValue < cValueActiveMaxAI_DOOR_UNLOCK_SW)
    {
        mDATWrite(U1Bit, DOOR_UNLOCK_SW, cTrue, Delayed);
    }
    else if (u16AdcValue > cValueInactiveMinAI_DOOR_UNLOCK_SW)
    {
        mDATWrite(U1Bit, DOOR_UNLOCK_SW, cFalse, Delayed);
    }
    else
    {
        // no change of input
    }

    u16AdcValue = mDATRead(U16Bit, AI_FR_WIPER_INT_SW, Immediate);
    if (u16AdcValue > cValueActiveMinFR_WIPER_INT_SW)
    {
        mDATWrite(U1Bit, FR_WIPER_INT_SW, cTrue, Delayed);
    }
    else if (u16AdcValue < cValueInactiveMaxFR_WIPER_INT_SW)
    {
        mDATWrite(U1Bit, FR_WIPER_INT_SW, cFalse, Delayed);
    }
    else
    {
        // no change of input
    }
#endif // COMPILATION_NATIVE

    // Undervoltage management
    if ((mDATRead(U1Bit, UnderVoltageIsDetected, Default) != cFalse) &&
        (bDATPinSleepMode == cFalse) )
    {
        // Mask actual input values with last good values (filtered values)
        mRetainInput(DOOR_UNLOCK_SW);
        mRetainInput(DOOR_LOCK_SW);
        mRetainInput(FR_DOORS_SW);
        mRetainInput(RR_DOORS_SW);
        mRetainInput(AIRBAG_CRASH);
        mRetainInput(DEFROSTER_SW);
        mRetainInput(L_FLASHER_SW);
        mRetainInput(R_FLASHER_SW);
        mRetainInput(HAZARD_SW);
    }
}

//===============================================================================
//  DESCRIPTION : Indicates that input has changed
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
// ==============================================================================
void DATPinStateChange(void)
{
    // the wake up by DIN is call on filtered changement on an input

    if (bDATPinSleepMode == cFalse)
    {
        if(     (cTrue == TOSIsTimerStarted(&TestVerlogTimer))
             && (cTrue == TOSIsTimerElapsed(&TestVerlogTimer, 
                    mTOSConvMsInTimerTick(10560)))
          )
        {
            TOSStopTimer(&TestVerlogTimer);
        }

        //RR_DOORS_SW
        if (mIsStateChange(RR_DOORS_SW))
        {
            TOSSendControl(cTOSControlChanging_RR_DOORS_SW);
            if (mIsFallingEdge(RR_DOORS_SW))
            {
                TOSSendControl(cTOSControlFalling_RR_DOORS_SW);
            }
            else
            {
                TOSSendControl(cTOSControlRising_RR_DOORS_SW);
            }
        }
    
        //FR_DOORS_SW
        if (mIsStateChange(FR_DOORS_SW))
        {
           TOSSendControl(cTOSControlChanging_FR_DOORS_SW);
           if (mIsFallingEdge(FR_DOORS_SW))
           {
               TOSSendControl(cTOSControlFalling_FR_DOORS_SW);
           }
           else
           {
               TOSSendControl(cTOSControlRising_FR_DOORS_SW);
           }
        }

        //DOOR_LOCK_SW
        if (mIsRaisingEdge(DOOR_LOCK_SW))
        {
            TOSSendControl(cTOSControlRising_DOOR_LOCK_SW);
        }

        //DOOR_UNLOCK_SW
        if (mIsRaisingEdge(DOOR_UNLOCK_SW))
        {
            TOSSendControl(cTOSControlRising_DOOR_UNLOCK_SW);
        }

        //HAZARD_SW
        if (mIsFallingEdge(HAZARD_SW))
        {
            TOSSendControl(cTOSControlFalling_HAZARD_SW);
        }

        //PWR_IGN
        if (mIsFallingEdge(PWR_IGN))
        {
            TOSSendControl(cTOSControlFalling_PWR_IGN);
            TOSStartTimer(&TestVerlogTimer);
        }
        else
        {
            if (mIsRaisingEdge(PWR_IGN))
            {
                TOSSendControl(cTOSControlRising_PWR_IGN);

                // Wipers parameter to be updated on ignition on
                WipersParametersRefresh();
            }
        }

        // Defroster button filtration
        if (mDATRead(U1Bit,EEP_AUTDEGIVRAGE,Default) != cFalse)
        {
            DefrosterFiltration();
        }
        
        // Wipers operate only when ignition is on
        if (mDATRead(U1Bit, PWR_IGN, Default) != cFalse)
        {
            // Front wiper filtration
            FrontWiperAutostopFiltration();
        
            // Rear wiper filtration
            if (mDATRead(U1Bit, EEP_EV_ARR, Default) != cFalse)
            {
                RearWiperAutostopFiltration();
            }
        }
    }
    else
    {
        // Sleep mode
        // Check for wake up conditions (non-filtered inputs)
        SleepModeStateChange();
    }
}

//===============================================================================
//  DESCRIPTION         : Maintain Active State
//
// PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//===============================================================================
void DATPinIsMaintainActiveState(void)
{
    if(       (mDATRead(U1Bit, POSITION_LIGHTS,    Default) == (U1)1)
        ||    (mDATRead(U1Bit, HAZARD_SW,            Default) == (U1)1)
        ||    (mDATRead(U1Bit, PWR_IGN,            Default) == (U1)1)
      )
    {
        TOSWriteSignal(cTOSSignalSomebodyMaintainActiveState);
    }
}

//===============================================================================
//  DESCRIPTION         : Maintain Active Sleep State
//
// PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//===============================================================================
void DATPinIsMaintainActiveSleepState(void)
{
    if ((TOSIsTimerStarted(&ActiveSleepTimer) != cFalse) &&
        (TOSIsTimerElapsed(&ActiveSleepTimer, 
            mTOSConvMsInTimerTick(cActiveSleepDurationInMs)) == cFalse))
    {
        TOSWriteSignal(cTOSSignalSomebodyMaintainActiveSleepState);
    }     
}

//===============================================================================
//  DESCRIPTION         : Put DAT_PIN in active state
//  
// PARAMETERS (Type,Name,Min,Max) :  none
//
// RETURN VALUE :  none
// 
// DESIGN INFORMATION :  refer to Detailed Design Document
//===============================================================================
void DATPinEnterActiveState (void)
{
#ifdef X90_PROJECT
    DATPinEnterActiveState_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DATPinEnterActiveState_Static(void)
{
#endif
    bDATPinSleepMode = cFalse;
    u8FrAutostopTimeCounter = 0;
    u8RrAutostopTimeCounter = 0;
    u8FrontWiperStopState = cStopAllowed;
    u8RearWiperStopState  = cStopAllowed;
    bPreviousFR_AUTOSTOP_SW = mDATRead(U1Bit, FR_AUTOSTOP_SW, Immediate);
    bPreviousRR_AUTOSTOP_SW = mDATRead(U1Bit, RR_AUTOSTOP_SW, Immediate);
    u8TPS_FILT_AF = 0;
    u8WipersStopFilteringTicks = 0;
}

//===============================================================================
//  DESCRIPTION         : Put DAT_PIN in inactive state
//  
// PARAMETERS (Type,Name,Min,Max) :  none
//
// RETURN VALUE :  none
// 
// DESIGN INFORMATION :  refer to Detailed Design Document
//===============================================================================
void DATPinLeaveActiveState (void)
{
    bDATPinSleepMode = cTrue;
    TOSStopTimer(&ActiveSleepTimer);
    u8DefrosterSWCounter = 0;
}

//===============================================================================
//  DESCRIPTION         : Put DAT_PIN in leave starting state
//  
// PARAMETERS (Type,Name,Min,Max) :  none
//
// RETURN VALUE :  none
// 
// DESIGN INFORMATION :  refer to Detailed Design Document
//===============================================================================
void DATPinLeaveStartingStepState(void)
{
    // Check wake-up conditions immediately after starting step
    // Reduce power on initialization time for both analog and digital inputs
    // Allow wake-up by analog inputs
    TOSActivateTask(cTOSTaskID_TacheANA); // ANA task must have higher priority than DIN task
    TOSActivateTask(cTOSTaskID_ReadLogical);
    bInputsReadAfterStartingStepState = cTrue;
}

//===============================================================================
// DESCRIPTION         : Callback control from LDB_DIN
//  
// PARAMETERS (Type,Name,Min,Max) :  none
//
// RETURN VALUE :  none
// 
// DESIGN INFORMATION :  refer to Detailed Design Document
//===============================================================================
void DATPinCallBackCtrl (const tCtrl Ctrl)
{
    if (Ctrl == cLDBPinWakeUpRequested)
    {
        TOSSendControl(cTOSControlActiveSleepRequest);
        TOSStartTimer(&ActiveSleepTimer);
    }
    else
    {
        mLIBassert(cFalse);
    }
}
