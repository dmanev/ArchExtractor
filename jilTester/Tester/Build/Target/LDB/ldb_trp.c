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
// Component:    LDB_TRP
// -----------------------------------------------------------------------------
// $Date:   Apr 09 2010 13:55:06  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_TRP/ldb_trp.c-arc  $
// $Revision:   1.18  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_TRP/ldb_trp.c-arc  $
// 
//    Rev 1.18   Apr 09 2010 13:55:06   amanevd
// Cm007827: Comment update - no change in binary code
// 
//    Rev 1.17   Mar 15 2010 11:05:46   amanevd
// Cm007827: cTRearmInit no used - removed
// 
//    Rev 1.16   Mar 15 2010 10:40:10   amanevd
// Cm007827: Now Immo is operable in 6-18V range
// 
//    Rev 1.15   Feb 24 2010 11:51:56   amanevd
// Cm007357: Applied switch to write mode on falling edge
// 
//    Rev 1.14   Feb 12 2010 10:19:48   amanevd
// Cm007357: QAC fix
// 
//    Rev 1.13   Feb 05 2010 16:53:06   amanevd
// Cm007357: Fix of communication with B99 and BNew antennas
// 
//    Rev 1.12   Jan 18 2010 09:16:26   amanevd
// Cm005797: Sleep pulse measurement corrected
// 
//    Rev 1.11   Oct 08 2009 18:03:18   amanevd
// Cm006468: Enabling and Disabling of cLDBHarInterruptTrpVerlogTimerIt removed
// 
//    Rev 1.10   Sep 24 2009 11:57:40   amanevd
// Cm006224: All 6 issues fixed
// 
//    Rev 1.9   Sep 08 2009 12:26:16   amanevd
// Cm006224: 3 of 6 issues fixed
// 
//    Rev 1.8   Sep 01 2009 15:26:42   amanevd
// Cm005466: second code review corrections SW2
// 
//    Rev 1.7   Aug 27 2009 18:12:32   amanevd
// Cm005466: QAC and code review fix
// 
//    Rev 1.6   Jul 24 2009 14:04:20   amanevd
// Cm005466: Change of the nominal BPLM timing
// 
//    Rev 1.5   Jul 16 2009 09:34:38   amanevd
// Cm005205: Update of the start/stop macros for Verlog timer
// 
//    Rev 1.4   Jul 09 2009 09:35:30   amanevd
// Cm005100: SAD requirement SAD.ROB.OUT.01.R01 related fix
// 
//    Rev 1.3   May 07 2009 10:52:44   amanevd
// Cm003272 - Finishing part 3 - pre-integration
// 
//    Rev 1.2   Apr 29 2009 13:14:22   amanevd
// Cm003272 - Intermediate part 3 
// - PRS compliance
// 
//    Rev 1.1   Apr 24 2009 17:17:16   amanevd
// Cm003272 - Finishing part 2 - pre-integration
// 
//    Rev 1.0   Apr 22 2009 19:28:50   amanevd
// Initial revision.
// 
//******************************************************************************

//-----------------------------------------------------------------------------
//  Body Identification
//-----------------------------------------------------------------------------
#define ldb_trp   "ldb_trp"

//-----------------------------------------------------------------------------
//  Included files
//
//  #include <system_file_name.h>
//  #include "project_file_name.h"
//-----------------------------------------------------------------------------
#include "lib.h"
#include "ldb.h"
#include "ldb_ioc.h"
#include "ldb_int.h"
#include "ldb_har.h"
#include "ldb_trp.h"
#include "ldb_trpp.h"

//-----------------------------------------------------------------------------
//  Local constants
//
//  #define cConstantName   ((tType) ConstantValue)
//-----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// Maximum size in byte of the buffer used to send and receive data
// to/from the transponder.
//----------------------------------------------------------------------------
#define cMaxShortCircuitToGnd           ((U8) 6U)
#define cMaxShortCircuitToBat           ((U8) 3U)

#define cTransponderBufferSize          ((U8) 8U)

#define cDataPageSizeInBit              ((U8) 32U)

#define cMaskBitToSend                  ((U8) 0x80U)

#define cMaskBit0                       ((U8) 0x01U)

#define cNextByteMask                   ((U8) 7U)

#define cMaxNbBitInByte                 ((U8) 8U)

#define cShortCommandLenght             ((U16) 5U)
#define cLongCommandLenght              ((U16) 10U)
#define cPageLength                     ((U16) 32U)
#define cChallangeLenght                ((U16) 64U)

#define cMaxRestart                     ((U8) 5U)

#define cDivideBy8                      ((U8) 3U)

#define cTBitMaxLength                  ((U16) 255U)

#define cMaxVerlogCount                 ((U8) 24U)

#define cReceiveBufferIndex             ((U32) 4U)

#define cShiftBy2                       ((U16) 2U)
#define cShiftBy3                       ((U16) 3U)
#define cShiftBy6                       ((U16) 6U)
#define cShiftBy8                       ((U16) 8U)

#define cShortCircuitThreshold          ((U8)0xFFU)

#define cCommandSize                    ((U8) 2U)

#define cCommandLastByteMask            ((U8) 0xC0U)

//----------------------------------------------------------------------------
// Time out definitions
//----------------------------------------------------------------------------
#define cTResetTransponder            ((U16) mConvUsInTrpTick(10000U))

#define cTInterCom                    ((U16) mConvUsInTrpTick(800U))

#define cTInitPPGCorrection           ((U16) mConvTrpToPPGTick(mConvUsInTrpTick(18U)))

#define cTReadingMode                 ((U16) mConvUsInTrpTick(1100U))  // Replaced by 5 points
#define cTEchReadingMode              ((U16) mConvUsInTrpTick((U16)200U - cLDBTrpItDelayBeforeSwitchInstr))
#define cMaxReadingCounter            ((U8)6)

#define cTWritingPulseMode1           ((U16) mConvUsInTrpTick((U16)1056U - cLDBTrpItDelayBeforeSwitchInstr))
#define cTWritingPulseMode2           ((U16) mConvUsInTrpTick((U16)1030U - cLDBTrpItDelayBeforeSwitchInstr))

#define cWritePulseWidth              ((U16)48U)
#define cStopPulseWidth               ((U16)288U)

#define cTWritePulse                  ((U16) mConvTrpToPPGTick(mConvUsInTrpTick(cWritePulseWidth)))
#define cTBit0Pulse                   ((U16) mConvTrpToPPGTick(mConvUsInTrpTick((U16)152U - cLDBTrpItDelayBeforeSwitchInstr)))
#define cTBit1Pulse                   ((U16) mConvTrpToPPGTick(mConvUsInTrpTick((U16)227U - cLDBTrpItDelayBeforeSwitchInstr)))
#define cTStopPulse                   ((U16) mConvUsInTrpTick(cStopPulseWidth))

#define cInitRearmTime                ((U16) mConvTrpToPPGTick(mConvUsInTrpTick(8UL)))

#define cTBitMaxPulse                 ((U16) mConvUsInTrpTick(cTBitMaxLength))

#define cTProg                        ((U16) mConvUsInTrpTick(12000UL))

//#define cTEqualizer                   ((U16) mConvUsInTrpTick((U16)2396UL - cWritePulseWidth - cLDBTrpItDelayBeforeSwitchInstr))
#define cTEqualizer                   ((U16) mConvUsInTrpTick((U16)2446UL - cWritePulseWidth - cLDBTrpItDelayBeforeSwitchInstr))

#define cTFirstWindowOpening          ((U16) mConvUsInTrpTick(cLDBTrpOneBitTimeMin))
#define cTWindowOpening               ((U16) mConvUsInTrpTick(cLDBTrpOneBitTimeMin - cLDBTrpItDelayMaxBeforeWindowOpening))
#define cTWindowClosing               ((U16) mConvUsInTrpTick(cLDBTrpTwoBitsTimeMax - cLDBTrpItDelayBeforeSwitchInstr))

// 512us +/- 5%
#define cSleepAckPulseTimeMin         ((U16) mConvUsInTrpTick(484U))
#define cSleepAckPulseTimeMax         ((U16) mConvUsInTrpTick(580U))

#define cTStartSleep                  ((U16) cTInterCom )
#define cTWaitBeforeSleepAck          ((U16) mConvUsInTrpTick(3500U))
#define cTWaitSleepAckTimeOut         ((U16) ((U16)2U * cSleepAckPulseTimeMax) - cTTestLigneStateTimeOut)
#define cTTestLigneStateTimeOut       ((U16) mConvUsInTrpTick(460U))
#define cTRestartBaseStationControl   ((U16) mConvUsInTrpTick(800U))

#define cTWaitBeforeWakeUpRaisingEdge ((U16) cTInterCom )
#define cTWaitingWakeUp               ((U16) mConvUsInTrpTick(500U))


//-----------------------------------------------------------------------------
//  Local macros
//
//  #define mMacroName   (MacroDefinition)
//-----------------------------------------------------------------------------
#ifdef _QAC_
    // Disabled  QAC warning QC0857: Number of macro definitions exceeds 1024 
    // it is normal STK code exceeds 1024 macro definitions
    #pragma PRQA_MESSAGES_OFF 0857
#endif


//----------------------------------------------------------------------------
// Convert time in micro second to a value in Trp tick
//----------------------------------------------------------------------------
#define mConvUsInTrpTick(Time) \
    ((U32)((U32)(Time) * ((U32)1000UL)) / cLDBHarTickInNsTrpTimeOutTimer)

#define mConvTrpToPPGTick(TrpTime)           ((U16)(TrpTime) >> 2)

//----------------------------------------------------------------------------
// Test of the capture duration
//----------------------------------------------------------------------------
#define mValidOneBitTime(Range)                                                         \
    (   ((U16)(Range) >= ((U16) mConvUsInTrpTick(cLDBTrpOneBitTimeMin)))                \
     && ((U16)(Range) <= ((U16) mConvUsInTrpTick(cLDBTrpOneBitTimeMax)))                \
    /*//QACJ 3435:amanevd: Macros is called with non arithmetic expression parameter*/  \
    /*//QACJ 3456:amanevd: Macros is called with non arithmetic expression parameter*/  \
    )

#define mValidOneAndAHalfBitTime(Range) \
    ((U16)(Range) <= ((U16) mConvUsInTrpTick(cLDBTrpOneAndAHalfBitTimeMax)))

#define mValidTwoBitsTime(Range) \
    ((U16)(Range) <= ((U16) mConvUsInTrpTick(cLDBTrpTwoBitsTimeMax)))

#define mValidSleepAckPulseTime(Range)                                                      \
    (   ((U16)(Range) > (U16)(  cSleepAckPulseTimeMin                                       \
                                -cTTestLigneStateTimeOut                                    \
                                -mConvUsInTrpTick(cLDBTrpItDelayMaxBeforeWindowOpening)))   \
     && ((U16)(Range) < (U16)(  cSleepAckPulseTimeMax                                       \
                                -cTTestLigneStateTimeOut                                    \
                                -mConvUsInTrpTick(cLDBTrpItDelayMaxBeforeWindowOpening)))   \
     /*//QACJ 3435:amanevd: Macros is called with non arithmetic expression parameter*/ \
     /*//QACJ 3456:amanevd: Macros is called with non arithmetic expression parameter*/ \
    )

// Calculates the offset for pu8ReceptionBuffer
#define mReceptionOffset(NumberOfBytes)     (U32)(((U32)(NumberOfBytes)/(U32)8U)+(U32)1U)

//----------------------------------------------------------------------------
// Control of the transponder line's state
//----------------------------------------------------------------------------
#define mWriteTranspondeurLine(State) mLDBHarWrite(cLDBHarTrpOut, (!(State)))
#define mReadTranspondeurLine()       ((U8)!(mLDBHarRead(cLDBHarTrpIn)))

//----------------------------------------------------------------------------
// Output compare time manages :
//  - TInterCom's time out
//  - TReadingMode's time out
//  - BPLM data coding (data send to the transponder) 
//  - Time out on the equalizer pattern detection
//  - Windowing during Manchester data decoding
//----------------------------------------------------------------------------
#define mStartTimeOut(Time)                                                         \
    mLDBIocStopTimer(cLDBHarTrpTimeOutTimer);                                       \
    mLDBIocSelectClock(cLDBHarTrpTimeOutTimer, cLDBHarSelectClockTrpTimeOutTimer);  \
    mLDBIocWriteTrigger(cLDBHarTrpTimeOutTrigger, ((U16)(Time) - (U16)1U));         \
    mLDBIntClearIsrRequestFlag(cLDBHarInterruptTrpTimeOutIt);                       \
    /*//QACJ 3412:amanevd: Macros uses register definitions from io78f0536_64.h*/   \
    mLDBIocStartTimer(cLDBHarTrpTimeOutTimer)

#define mRearmTimeOut(Time)                                                         \
    mLDBIocStopTimer(cLDBHarTrpTimeOutTimer);                                       \
    mLDBIocWriteTrigger(cLDBHarTrpTimeOutTrigger, ((U16)(Time) - (U16)1U));         \
    mLDBIntClearIsrRequestFlag(cLDBHarInterruptTrpTimeOutIt);                       \
    /*//QACJ 3412:amanevd: Macros uses register definitions from io78f0536_64.h*/   \
    mLDBIocStartTimer(cLDBHarTrpTimeOutTimer)

#define mStopTimeOut() \
    mLDBIntClearIsrRequestFlag(cLDBHarInterruptTrpTimeOutIt);                       \
    /*//QACJ 3412:amanevd: Macros uses register definitions from io78f0536_64.h*/   \
    mLDBIocStopTimer(cLDBHarTrpTimeOutTimer) 

#define mReadTimeOutValue()   \
    ((U16)mLDBIocReadCounter(cLDBHarTrpTimeOutTimer))

#define mStartPPGOutput(TimeM, TimeN)                                               \
    mLDBIocStopTimer(cLDBHarTrpTimePPGTimer);                                       \
    mLDBIocSelectClock(cLDBHarTrpTimePPGTimer, cLDBHarSelectClockTrpPPGTimer);      \
    mLDBIocSelectTimerMode(cLDBHarTrpTimePPGTimer, cLDBHarTrpPPGTimeCompareTimer);  \
    mLDBIocWriteTrigger(cLDBHarTrpTimePPGTriggerM, ((U16)(TimeM) - (U16)1U));       \
    mLDBIocWriteTrigger(cLDBHarTrpTimePPGTriggerN, ((U16)(TimeN) - (U16)1U));       \
    mLDBIocOutputEnable(cLDBHarTrpTimePPGTimer);                                    \
    /*//QACJ 3412:amanevd: Macros uses register definitions from io78f0536_64.h*/   \
    mLDBIocStartTimer(cLDBHarTrpTimePPGTimer)


#define mStopPPGOutput()                                                            \
    mLDBIocStopTimer(cLDBHarTrpTimePPGTimer);                                       \
    /*//QACJ 3412:amanevd: Macros uses register definitions from io78f0536_64.h*/   \
    mLDBIocOutputDisable(cLDBHarTrpTimePPGTimer)

#define mRearmPPGOutput(TimeM, TimeN)                                               \
    mLDBIocStopTimer(cLDBHarTrpTimePPGTimer);                                       \
    mLDBIocWriteTrigger(cLDBHarTrpTimePPGTriggerM, ((U16)(TimeM) - (U16)1U));       \
    mLDBIocWriteTrigger(cLDBHarTrpTimePPGTriggerN, ((U16)(TimeN) - (U16)1U));       \
    mLDBIocOutputEnable(cLDBHarTrpTimePPGTimer);                                    \
    /*//QACJ 3412:amanevd: Macros uses register definitions from io78f0536_64.h*/   \
    mLDBIocStartTimer(cLDBHarTrpTimePPGTimer)

#define mReadPPGTimerValue()   \
    ((U16)mLDBIocReadCounter(cLDBHarTrpTimePPGTimer))

//----------------------------------------------------------------------------
// Main macro used to stop the input capture timer
//----------------------------------------------------------------------------
#define mStopTimeCaptureTimer() \
    mLDBIocStopTimer(cLDBHarTrpTimeCaptureTimer)  

//----------------------------------------------------------------------------
// Reading of the time capture value
//----------------------------------------------------------------------------

// Caution !!! this has to be updated with
// correct value cLDBHarTickInNsTrpTimeCaptureTimer/cLDBHarTickInNsTrpTimeOutTimer
// currently cLDBHarTickInNsTrpTimeCaptureTimer/cLDBHarTickInNsTrpTimeOutTimer == 4
#define mReadTimeCaptureValue()   \
    (U16)((U16)mLDBIocReadTrigger(cLDBHarTrpTimeCaptureTrigger) << (U16)2U)

//----------------------------------------------------------------------------
// Manchester data acquisition management
//----------------------------------------------------------------------------
#define mStartAcquistion()                                                                              \
    mLDBIocStopTimer(cLDBHarTrpTimeCaptureTimer);                                                       \
    mLDBIocSelectClock(cLDBHarTrpTimeCaptureTimer, cLDBHarSelectClockTrpTimeCaptureTimer);              \
    mLDBIocSelectTimerMode(cLDBHarTrpTimeCaptureTimer, cLDBHarFreeRunningModeTrpTimeCaptureTimer);      \
    mLDBIocConfigureFreeRunningMode(cLDBHarTrpTimeCaptureTimer, cLDBHarConfigureTrpTimeCaptureTimer);   \
    mLDBIocSetEdgeDetection(cLDBHarTrpTimeCaptureTimer, cLDBIocRisingEdge);                             \
    u16TimeMeasuredOld = 0;                                                                              \
    /*//QACJ 3412:amanevd: Macros uses register definitions from io78f0536_64.h*/                       \
    mLDBIocFreeRunningModeStartTimer(cLDBHarTrpTimeCaptureTimer)

//----------------------------------------------------------------------------
// Edge detection management
//----------------------------------------------------------------------------
#define mStartEdgeDetection(Edge)                                                                       \
    mLDBIocStopTimer(cLDBHarTrpTimeCaptureTimer);                                                       \
    mLDBIocSelectClock(cLDBHarTrpTimeCaptureTimer, cLDBHarSelectClockTrpTimeCaptureTimer);              \
    mLDBIocSelectTimerMode(cLDBHarTrpTimeCaptureTimer, cLDBHarFreeRunningModeTrpTimeCaptureTimer);      \
    mLDBIocConfigureFreeRunningMode(cLDBHarTrpTimeCaptureTimer, cLDBHarConfigureTrpTimeCaptureTimer);   \
    mLDBIocSetEdgeDetection(cLDBHarTrpTimeCaptureTimer, Edge);                                          \
    u16TimeMeasuredOld = 0;                                                                              \
    /*//QACJ 3412:amanevd: Macros uses register definitions from io78f0536_64.h*/                       \
    mLDBIocFreeRunningModeStartTimer(cLDBHarTrpTimeCaptureTimer)

//----------------------------------------------------------------------------
// Sleep and Wake Up acknowledge timing capture
//----------------------------------------------------------------------------
#define mStartBaseStationAckCapture()                                                                   \
    mLDBIocStopTimer(cLDBHarTrpTimeCaptureTimer);                                                       \
    mLDBIocSelectClock(cLDBHarTrpTimeCaptureTimer, cLDBHarSelectClockTrpTimeCaptureTimer);              \
    mLDBIocSelectTimerMode(cLDBHarTrpTimeCaptureTimer, cLDBHarFreeRunningModeTrpTimeCaptureTimer);      \
    mLDBIocConfigureFreeRunningMode(cLDBHarTrpTimeCaptureTimer, cLDBHarConfigureTrpTimeCaptureTimer);   \
    mLDBIocSetEdgeDetection(cLDBHarTrpTimeCaptureTimer, cLDBIocBothEdge);                               \
    u16TimeMeasuredOld = 0;                                                                              \
    /*//QACJ 3412:amanevd: Macros uses register definitions from io78f0536_64.h*/                       \
    mLDBIocFreeRunningModeStartTimer(cLDBHarTrpTimeCaptureTimer)

#define mStartVerlogTimer() (bLDBTrpIsVerlogTimerEnabled = cTrue)

#define mStopVerlogTimer() (bLDBTrpIsVerlogTimerEnabled = cFalse)

#ifdef _QAC_
    // Enabled  QAC warning QC0857: Number of macro definitions exceeds 1024 
    // it is normal STK code exceeds 1024 macro definitions
    #pragma PRQA_MESSAGES_ON 0857
#endif


//-----------------------------------------------------------------------------
//  Local types
//
//  struct  sStructureName { ... };
//  union   uUnionName { ... };
//  enum    eEnumerationName { ... };
//  typedef Expression tTypeName;
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Decoding states
//----------------------------------------------------------------------------
typedef enum
{
    cReadingModeChecking    ,
    cOpenWindowData         ,
    cDecoding               ,
    cSleepAckDetection      ,
    cStop                   ,
    cTimeOutInterCom        ,
    cEndWritePulse          ,
    cEndStopPulse           ,
    cTimeOutProg            ,
    cTimeOutEqualizer       ,  
    cStartSleep             ,
    cStartSleepAckDetection ,
    cGenerateRaisingEdge    ,
    cWaitTransponderSleep   ,
    cWaitingWakeUp
}tStateMachine;

//-----------------------------------------------------------------------------
//  Local data
//
//  static  tType   VariableName;
//  static  tType*  pVariableName; 
//-----------------------------------------------------------------------------
static tStateMachine DecodingState;

static MEM_FAST tMsg TransponderMessage;
static MEM_FAST U8   TransponderBuffer[cTransponderBufferSize];
static MEM_FAST U8 CurrentCommand[cCommandSize];
static U8   u8ReceivedBits;
static U8   u8ExpectedBitsNb;
static U8   u8RestartCounter;

static BOOL bDataSynchronized;
static BOOL bTimeOutTProgRequested;
static BOOL bReceiveData;
static BOOL bDetectAckPulse;

static MEM_FAST U16  u16TimeMeasured;
static MEM_FAST U16  u16TimeMeasuredOld;
static MEM_FAST U16  u16TimeDifference;
static MEM_FAST U16  u16TimeCapture;
static MEM_FAST U16  u16TimeRearm;
static U8*  pu8ReceptionBuffer;

static U8 u8ShortCircuitToGnd;
static U8 u8ShortCircuitToBat;

//-----------------------------------------------------------------------------
//  Constant local data
//
//  static const tType  VariableName;
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//  Exported data
//
//  tType   LAYCmpVariableName;   (LAY: 3 characters to identify the layer)
//  tType*  pLAYCmpVariableName;  (Cmp: 3 characters to identify this component)
//-----------------------------------------------------------------------------
BOOL bLDBTrpIsVerlogTimerEnabled;

//-----------------------------------------------------------------------------
//  Constant exported data
//
//              (LAY: 3 characters to identify the layer)
//              (Cmp: 3 characters to identify this component)
// 
//  const tType   LAYCmpVariableName;
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//  Local function prototypes
//  
//  static tTypeRetour FunctionName(tTypeArgument1 ArgumentName1, ... );
//-----------------------------------------------------------------------------
static void StopCom(void);
static void StoreBit(const U8 u8Bit);
static void InitCom(void);

//=============================================================================
//=========================== LOCAL FUNCTIONS =================================
//=============================================================================

//=============================================================================
//  DESCRIPTION : Store a bit in the reception buffer.
//  
//  PARAMETERS (Type,Name,Min,Max) : U8 ucPageNumber : page number
//                                   tTrpCommand StandardCommand : base command
//
//  RETURN VALUE :  Computed command.
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//=============================================================================
static void StoreBit(const U8 u8Bit)
{
    if (u8ReceivedBits == 0)
    {
        //QACJ 0506:amanevd: The pointer is checked with assert in debug mode
        *pu8ReceptionBuffer = u8Bit & cMaskBit0;
    }
    else
    {
        *pu8ReceptionBuffer <<= 1;
        *pu8ReceptionBuffer  += u8Bit & cMaskBit0;

        if ((U8)(u8ReceivedBits & cNextByteMask) == cNextByteMask)
        {
            //QACJ 0489:amanevd: This is how it comes from STK
            pu8ReceptionBuffer--;
        }
    }
    u8ReceivedBits++;
}
//=============================================================================
//  DESCRIPTION : Initialize a communication
//  
//  PARAMETERS (Type,Name,Min,Max) :
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//=============================================================================
static void InitCom(void)
{
#ifdef X90_PROJECT
    mLDBIntGetInterruptTM00TM01(cLDBIntTrpOwnerTM00TM01);
#endif

    mLDBIntDisableIsr(cLDBHarInterruptTrpTimeOutIt);
    mLDBIntClearIsrRequestFlag(cLDBHarInterruptTrpTimeOutIt);
    mLDBIntEnableIsr(cLDBHarInterruptTrpTimeOutIt);

    mLDBIntDisableIsr(cLDBHarInterruptTrpTimeCaptureIt);
    mLDBIntClearIsrRequestFlag(cLDBHarInterruptTrpTimeCaptureIt);
}

//=============================================================================
//  DESCRIPTION : Stop a communication
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//=============================================================================
static void StopCom(void)
{    
    mStopTimeOut();
    mStopTimeCaptureTimer();
    mLDBIntDisableIsr(cLDBHarInterruptTrpTimeCaptureIt);
    mLDBIntDisableIsr(cLDBHarInterruptTrpTimeOutIt);
    mLDBIntDisableIsr(cLDBHarInterruptTrpPPGIt);
    mWriteTranspondeurLine(1);
    DecodingState = cStop;

#ifdef X90_PROJECT
    mLDBIntReleaseInterruptTM00TM01(cLDBIntTrpOwnerTM00TM01);
#endif
}

//=============================================================================
//============================ EXPORTED FUNCTIONS =============================
//=============================================================================

//*****************************************************************************
//  DESCRIPTION : Interruption of the input capture timer
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//*****************************************************************************
#ifndef X90_PROJECT
mLDBIntDeclareIsr(cLDBHarInterruptTrpTimeCaptureIt)
{
    mLDBIntEnterIsr(cLDBHarInterruptTrpTimeCaptureIt);
#else
void LDBTrpTimeCaptureIt(void)
{
#endif

    switch (DecodingState)
    {
        case cReadingModeChecking:

        mWriteTranspondeurLine(0);
        //QACJ 0434:amanevd: 'CR000' is declared in io78f0536_64.h
        mStartTimeOut(cTWritingPulseMode2);
        mStopTimeCaptureTimer();
        mLDBIntDisableIsr(cLDBHarInterruptTrpTimeCaptureIt);
        DecodingState = cEndWritePulse;
        break;

        case cDecoding:

        //Mesure du temps entre 2 fronts descendant
        //QACJ 0434:amanevd: 'CR011' is declared in io78f0536_64.h
        u16TimeMeasured = mReadTimeCaptureValue();

        if (mValidOneBitTime(u16TimeMeasured - u16TimeMeasuredOld))       //T = 1Tbit
        {
            if (bDataSynchronized == cFalse)          //Synchro bit "1"
            {
                StoreBit(1);
            }
            else                                      //Synchro bit "0"
            {
                StoreBit(0);
            }
        }
        else if (mValidOneAndAHalfBitTime(u16TimeMeasured - u16TimeMeasuredOld))    //T = 1.5Tbit
        {
            if (bDataSynchronized == cFalse)                      //Synchro bit "1"
            {
                StoreBit(0);

                if (u8ReceivedBits < u8ExpectedBitsNb)              
                {
                    bDataSynchronized = cTrue;
                }
            }
            else                                                  //Synchro bit "0"
            {
                StoreBit(0);
                StoreBit(1);

                if (u8ReceivedBits < u8ExpectedBitsNb)
                {
                    bDataSynchronized = cFalse;
                }
            }
        }
        else if (mValidTwoBitsTime(u16TimeMeasured - u16TimeMeasuredOld))    //T = 2Tbit                                                    //T = 2Tbit
        {
            if (bDataSynchronized == cFalse)                      //Synchro bit "1"
            {
                StoreBit(0);
                StoreBit(1);
            }
            else                                                  //Synchro bit "0"
            {
                //DF : Cas ou l'on a un glitch dans la sequence 010
                StoreBit(1);
                StoreBit(0); 
                //StopCom();
                //DF : fin
            }      
        }
        else
        {
            //DF : Permet de faire apparaitre une erreur IDE
            DATTrpCallBackRxWithAddr(0, cLDBError);  
            //DF : fin
            //DF : Diag
            //Erreur decodage => Defaut Data
            //DATTrpCallBackCtrl(cLDBTrpDataError);
            StopCom();
            //DF : fin
        }

        if (u8ReceivedBits >= u8ExpectedBitsNb)         //Tous les bits de la Data sont recus
        {
            StopCom();

            if (bReceiveData != cFalse)
            {
                TransponderMessage.Lng     = u8ExpectedBitsNb;
                TransponderMessage.pBuffer = (U8*)(&TransponderBuffer[cReceiveBufferIndex]);

                DATTrpCallBackTxWithAddr(cLDBTrpStartAuth, cLDBCorrect);
                DATTrpCallBackRxSpontWithoutAddr(cLDBCorrect, &TransponderMessage);
            }
            else
            {
                DATTrpCallBackRxWithAddr(0, cLDBCorrect);
            }
        }
        else                                        //Data incomplete
        {
            mRearmTimeOut(cTWindowOpening);         //220µs 
            mLDBIntDisableIsr(cLDBHarInterruptTrpTimeCaptureIt);
            mLDBIntClearIsrRequestFlag(cLDBHarInterruptTrpTimeCaptureIt);
            DecodingState = cOpenWindowData;
        }
        if(cStop != DecodingState)
        {
            u16TimeMeasuredOld = u16TimeMeasured; 
        }
        break;

        case cSleepAckDetection:

        u16TimeMeasured = mReadTimeCaptureValue();   

        if (mValidSleepAckPulseTime(u16TimeMeasured))
        {
            mStartTimeOut(cTResetTransponder);
            mWriteTranspondeurLine(1);
            DecodingState = cWaitTransponderSleep;
        }
        else
        {
            mStartTimeOut(cTRestartBaseStationControl);
            u8RestartCounter++;
            DecodingState = cStartSleep;
        }
        mStopTimeCaptureTimer();
        break;

        case cStop:

        // Keep this state only for code optimization
        mLIBassert(cFalse);
        break;

        default:
        mLIBassert(cFalse);
        break;
    }

    mLDBIntClearIsrRequestFlag(cLDBHarInterruptTrpTimeCaptureIt);
#ifndef X90_PROJECT
    mLDBIntLeaveIsr(cLDBHarInterruptTrpTimeCaptureIt);
#endif
}

//*****************************************************************************
//  DESCRIPTION : Interruption of the output compare PPG output timer
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//*****************************************************************************

#ifndef X90_PROJECT
mLDBIntDeclareIsr(cLDBHarInterruptTrpPPGIt)
{
    mLDBIntEnterIsr(cLDBHarInterruptTrpPPGIt);
#else
void LDBTrpPPGIt(void)
{
#endif

    if(cEndWritePulse == DecodingState)
    {
        TransponderMessage.Lng--;

        if (TransponderMessage.Lng == 0)
        {
            mWriteTranspondeurLine(1);

            //QACJ 0434:amanevd: 'CR000' is declared in io78f0536_64.h
            mRearmTimeOut(cTStopPulse);
            mStopPPGOutput();
            DecodingState = cEndStopPulse;          
        }
        else
        {
            //QACJ 0506:amanevd: The pointer is checked with assert in debug mode
            *TransponderMessage.pBuffer <<= 1;

            if ((U8)(TransponderMessage.Lng & cNextByteMask) == (U8)0)
            {
                //QACJ 0489:amanevd: This is how it comes from STK
                TransponderMessage.pBuffer--;
            }

            //QACJ 0506:amanevd: The pointer is checked with assert in debug mode
            if (((U8)(*TransponderMessage.pBuffer) & cMaskBitToSend) != 0)
            {
                //QACJ 0434:amanevd: 'TM01' is declared in io78f0536_64.h
                u16TimeDifference = mReadPPGTimerValue();
                //QACJ 0434:amanevd: 'TM00' is declared in io78f0536_64.h
                u16TimeCapture = mReadTimeOutValue();

//===================================================================================================
//
// TRP     PPG Interrupt n-1                                                          PPG Interrupt n
// Line    |                           Start of the new pattern                       |
//         V                           |                                              V
//    -----+                           |      +---------------------------------------+
//         |      Time of servicing    |      |                                       |
//         |      | Interrupt          |      |                                       |
//         |      V                    V      |                                       |
//         +----------------------------------+                                       +--------------
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//         ^      ^                    ^      ^                                       ^
// Desc-   |<--+->|<----------------+->|<-+-->|                                       |
// ription |   +                    +  |  ++(cTBit1Pulse-cTWritePulse                 |
//         |   +                    +  |     -u16TimeDifference-u16TimeRearm)         |
//         |   +                    +  |                                              |
//         |   +                    +  |<------------+------------------------------->|
//         |   +                    +                +                                |
//         |   +                    ++u16TimeRearm   ++(cTBit1Pulse-u16TimeDifference |
//         |   ++u16TimeDifference                     -u16TimeRearm)                 |
//         |                                                                          |
//         |<----------cTWritePulse---------->|                                       |
//         |<---------------------cTBit1Pulse---------------------------------------->|
//
//  1. u16TimeDifference    -   The time measured between 
//                              PPG interrupt and actual time of interrupt servicing
//  2. u16TimeRearm         -   The time for rearming the timer(from previous cycle)
//  3. cTWritePulse         -   WritePulse time constant
//  4. cTBit1Pulse          -   TBit1Pulse time constant
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//  mRearmPPGOutput(M, N) produces waveform with the following metrics:
//
//  +                                            +--------------+
//  |                                            |              |
//  |                                            |              |
//  |                                            |              |
//  +--------------------------------------------+              +--------------
//  ^                                            ^              ^  
//  |<-------------------N---------------------->|              |
//  |<-----------------------------M--------------------------->|    
//
//===================================================================================================

                //QACJ 0434:amanevd: 'CR001' is declared in io78f0536_64.h
                //QACJ 0434:amanevd: 'CR011' is declared in io78f0536_64.h
                mRearmPPGOutput(cTBit1Pulse - u16TimeDifference - u16TimeRearm, 
                    cTBit1Pulse - cTWritePulse - u16TimeDifference - u16TimeRearm);
                u16TimeRearm = (U16)((U16)(mReadTimeOutValue() - u16TimeCapture) >> cShiftBy2);
                mLIBassert(cTBit1Pulse > (cTWritePulse + u16TimeDifference + u16TimeRearm));
            }
            else
            {
                //QACJ 0434:amanevd: 'TM01' is declared in io78f0536_64.h
                u16TimeDifference = mReadPPGTimerValue();
                //QACJ 0434:amanevd: 'TM00' is declared in io78f0536_64.h
                u16TimeCapture = mReadTimeOutValue();

//===================================================================================================
//
// TRP     PPG Interrupt n-1                                                          PPG Interrupt n
// Line    |                           Start of the new pattern                       |
//         V                           |                                              V
//    -----+                           |      +---------------------------------------+
//         |      Time of servicing    |      |                                       |
//         |      | Interrupt          |      |                                       |
//         |      V                    V      |                                       |
//         +----------------------------------+                                       +--------------
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//         ^      ^                    ^      ^                                       ^
// Desc-   |<--+->|<----------------+->|<-+-->|                                       |
// ription |   +                    +  |  ++(cTBit0Pulse-cTWritePulse                 |
//         |   +                    +  |     -u16TimeDifference-u16TimeRearm)         |
//         |   +                    +  |                                              |
//         |   +                    +  |<------------+------------------------------->|
//         |   +                    +                +                                |
//         |   +                    ++u16TimeRearm   ++(cTBit0Pulse-u16TimeDifference |
//         |   ++u16TimeDifference                     -u16TimeRearm)                 |
//         |                                                                          |
//         |<----------cTWritePulse---------->|                                       |
//         |<---------------------cTBit0Pulse---------------------------------------->|
//
//  1. u16TimeDifference    -   The time measured between 
//                              PPG interrupt and actual time of interrupt servicing
//  2. u16TimeRearm         -   The time for rearming the timer(from previous cycle)
//  3. cTWritePulse         -   WritePulse time constant
//  4. cTBit0Pulse          -   TBit0Pulse time constant
//
//===================================================================================================

                //QACJ 0434:amanevd: 'CR001' is declared in io78f0536_64.h
                //QACJ 0434:amanevd: 'CR011' is declared in io78f0536_64.h
                mRearmPPGOutput(cTBit0Pulse - u16TimeDifference - u16TimeRearm, 
                    cTBit0Pulse - cTWritePulse - u16TimeDifference - u16TimeRearm);
                u16TimeRearm = (U16)((U16)(mReadTimeOutValue()- u16TimeCapture) >> cShiftBy2);
                mLIBassert(cTBit0Pulse > (cTWritePulse + u16TimeDifference + u16TimeRearm));
            }
        }
    }
    else
    {
        mLIBassert(cFalse);
    }

    mLDBIntClearIsrRequestFlag(cLDBHarInterruptTrpPPGIt);
#ifndef X90_PROJECT
    mLDBIntLeaveIsr(cLDBHarInterruptTrpPPGIt);
#endif
}

//*****************************************************************************
//  DESCRIPTION : Interruption of the output compare timer
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//*****************************************************************************
#ifndef X90_PROJECT
mLDBIntDeclareIsr(cLDBHarInterruptTrpTimeOutIt)
{
    U16 u16Temp;
    mLDBIntEnterIsr(cLDBHarInterruptTrpTimeOutIt);
#else
void LDBTrpTimeOutIt(void)
{
    U16 u16Temp;
#endif

    switch (DecodingState)
    {
        case cTimeOutInterCom:

        mStartEdgeDetection(cLDBIocRisingEdge);

        mLDBIntDisableIsr(cLDBHarInterruptTrpTimeCaptureIt);
        mLDBIntClearIsrRequestFlag(cLDBHarInterruptTrpTimeCaptureIt);
        mLDBIntEnableIsr(cLDBHarInterruptTrpTimeCaptureIt);

        //QACJ 0434:amanevd: 'CR000' is declared in io78f0536_64.h
        mRearmTimeOut(cTEchReadingMode);
        u8RestartCounter = 0;

        DecodingState = cReadingModeChecking;
        break;

        case cReadingModeChecking:

        //QACJ 3346:amanevd: The 'if' expression is not analysed correct, because of incorrect inclusion of io78f0536_64.h
        if (mReadTranspondeurLine() != cFalse)
        {
            u8RestartCounter++;
            if (u8RestartCounter > cMaxReadingCounter)   // Ensure reading mode
            {
                mWriteTranspondeurLine(0);

                mStopTimeCaptureTimer();

                mLDBIntDisableIsr(cLDBHarInterruptTrpTimeCaptureIt);

                mRearmTimeOut(cTWritingPulseMode1);

                DecodingState = cEndWritePulse;
            }
        }
        else
        //QACJ 3201:amanevd: The 'if' expression is not analysed correct, because of incorrect inclusion of io78f0536_64.h
        {
            u8RestartCounter = 0;
        }
        break;

        case cEndWritePulse:

        if(    (cShortCommandLenght == TransponderMessage.Lng)
            || (cLongCommandLenght  == TransponderMessage.Lng)
            || (cPageLength         == TransponderMessage.Lng)
            || (cChallangeLenght    == TransponderMessage.Lng)
          )
        {
            u16TimeDifference = 0;

            mLDBIntDisableIsr(cLDBHarInterruptTrpPPGIt);
            mLDBIntClearIsrRequestFlag(cLDBHarInterruptTrpPPGIt);
            mLDBIntEnableIsr(cLDBHarInterruptTrpPPGIt);

            mWriteTranspondeurLine(1);

            u16Temp = (cTBitMaxPulse*TransponderMessage.Lng);
            mRearmTimeOut(u16Temp);

            mLIBassert(NULL != TransponderMessage.pBuffer);

            //QACJ 0506:amanevd: The pointer is checked with assert in debug mode
            if ((*TransponderMessage.pBuffer & cMaskBitToSend) != 0)
            {
                //QACJ 0434:amanevd: 'CR001' is declared in io78f0536_64.h
                //QACJ 0434:amanevd: 'CR011' is declared in io78f0536_64.h
                mStartPPGOutput(cTBit1Pulse - cTInitPPGCorrection, 
                    cTBit1Pulse - cTInitPPGCorrection - cTWritePulse);
                u16TimeRearm = cInitRearmTime;
            }
            else
            {
                //QACJ 0434:amanevd: 'CR001' is declared in io78f0536_64.h
                //QACJ 0434:amanevd: 'CR011' is declared in io78f0536_64.h
                mStartPPGOutput(cTBit0Pulse - cTInitPPGCorrection, 
                    cTBit0Pulse - cTInitPPGCorrection - cTWritePulse);
                u16TimeRearm = cInitRearmTime;
            }

            DecodingState = cEndWritePulse;
        }
        else
        {
            StopCom();
            DATTrpCallBackRxWithAddr(0, cLDBError);
        }
        break;

        case cEndStopPulse:

        mLDBIntDisableIsr(cLDBHarInterruptTrpPPGIt);

        if (bTimeOutTProgRequested != cFalse)
        {
            mRearmTimeOut(cTProg);
            DecodingState = cTimeOutProg;
        }
        else
        {
            mRearmTimeOut(cTEqualizer);
            DecodingState = cTimeOutEqualizer;
        }
        break;

        case cTimeOutProg:

        StopCom();
        DATTrpCallBackTxWithAddr(0, cLDBCorrect);
        break;

        case cTimeOutEqualizer:

        mStartAcquistion();     //Initialisation Timer en mode capture, Detection sur front descendant, Commence à compter entre 2 front descendant

        mRearmTimeOut(cTFirstWindowOpening);    //220µs fenetre de detection du front descendant du dernier bit EQ

        u8ReceivedBits    = 0;
        u16TimeMeasured    = 0;
        bDataSynchronized = cFalse;             //Synchronisation bit "1"
        DecodingState     = cOpenWindowData;
        mLDBIntDisableIsr(cLDBHarInterruptTrpTimeCaptureIt);
        mLDBIntClearIsrRequestFlag(cLDBHarInterruptTrpTimeCaptureIt);
        break;

        case cOpenWindowData:

        mRearmTimeOut(cTWindowClosing);         //580µs
        mLDBIntDisableIsr(cLDBHarInterruptTrpTimeCaptureIt);
        mLDBIntClearIsrRequestFlag(cLDBHarInterruptTrpTimeCaptureIt);
        mLDBIntEnableIsr(cLDBHarInterruptTrpTimeCaptureIt);
        DecodingState = cDecoding;              //Decodage Data
        break;

        case cDecoding:

        StopCom();                              //Time Out => arret machine d'état
        //DF : Diag
        //Probleme Data sortie en Time Out
        DATTrpCallBackRxWithAddr(0, cLDBError);
        //DF : fin
        break;

        case cStartSleep:

        if (u8RestartCounter < cMaxRestart)
        {
            // Line must be set to 1
            //QACJ 3325:amanevd: The 'if' expression is not analysed correct, because of incorrect inclusion of io78f0536_64.h
            if (mReadTranspondeurLine() == (U8)0U)   // Short circuit to Gnd
            //QACJ 3201:amanevd: The 'if' expression is not analysed correct, because of incorrect inclusion of io78f0536_64.h
            {
                if (u8ShortCircuitToGnd < cShortCircuitThreshold)
                {
                    u8ShortCircuitToGnd++;            // Possible noise, wait sleep to ensure good high level
                }
            }
            else            
            {
                u8ShortCircuitToGnd = 0;            // no short circuit
            }
            mStartTimeOut(cTWaitBeforeSleepAck);
            mWriteTranspondeurLine(0);
            DecodingState = cStartSleepAckDetection;
        }
        else
        {
            StopCom();
            if( u8ShortCircuitToGnd > cMaxShortCircuitToGnd )
            {
                DATTrpCallBackCtrl(cLDBTrpShortCircuitToGnd);
            }
            else if( u8ShortCircuitToBat > cMaxShortCircuitToBat)
            {
                DATTrpCallBackCtrl(cLDBTrpShortCircuitToBat);
            }
            else
            {
                //Nothing to do
            }
            DATTrpCallBackEndCtrl(cLDBTrpSleep, cLDBError);
        }
        break;

        case cStartSleepAckDetection:    

        // Line must be set to 0
        //QACJ 3346:amanevd: The 'if' expression is not analysed correct, because of incorrect inclusion of io78f0536_64.h
        if (mReadTranspondeurLine() != (U8)0U)   // Short circuit to Batt
        {
            if (u8ShortCircuitToBat < cShortCircuitThreshold)
            {
                u8ShortCircuitToBat++;
            }
        }
        else
        //QACJ 3201:amanevd: The 'if' expression is not analysed correct, because of incorrect inclusion of io78f0536_64.h
        {
            u8ShortCircuitToBat = 0;
        }
        mStartTimeOut(cTTestLigneStateTimeOut);
        mWriteTranspondeurLine(1);
        bDetectAckPulse = cTrue;
        DecodingState   = cSleepAckDetection;
        break;

        case cSleepAckDetection:

        if ((bDetectAckPulse != cFalse) && (mReadTranspondeurLine() != (U8)0U))
        {
            mLDBIntDisableIsr(cLDBHarInterruptTrpTimeCaptureIt);
            mLDBIntClearIsrRequestFlag(cLDBHarInterruptTrpTimeCaptureIt);
            mLDBIntEnableIsr(cLDBHarInterruptTrpTimeCaptureIt);

            mStartTimeOut(cTWaitSleepAckTimeOut);
            mStartBaseStationAckCapture();
            bDetectAckPulse = cFalse;
        }
        else
        {
            mStopTimeCaptureTimer();
            mLDBIntDisableIsr(cLDBHarInterruptTrpTimeCaptureIt);
            mStartTimeOut(cTRestartBaseStationControl);
            u8RestartCounter++;
            DecodingState = cStartSleep;
        }
        break;

        case cWaitTransponderSleep:

        StopCom();
        DATTrpCallBackEndCtrl(cLDBTrpSleep, cLDBCorrect);
        break;

        case cGenerateRaisingEdge:

        mStartTimeOut(cTWaitingWakeUp);
        mWriteTranspondeurLine(1);
        DecodingState = cWaitingWakeUp;
        break;

        case cWaitingWakeUp:

        StopCom();
        DecodingState = cStop;
        DATTrpCallBackEndCtrl(cLDBTrpWakeUp, cLDBCorrect);
        break;  

        default:
        mLIBassert(cFalse);
        break;
    }

    mLDBIntClearIsrRequestFlag(cLDBHarInterruptTrpTimeOutIt);
#ifndef X90_PROJECT
    mLDBIntLeaveIsr(cLDBHarInterruptTrpTimeOutIt);
#endif
}

//*****************************************************************************
//  DESCRIPTION : Interruption of the Verlog output timer
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//*****************************************************************************
#ifndef X90_PROJECT
mLDBIntDeclareIsr(cLDBHarInterruptTrpVerlogTimerIt)
{
    mLDBIntEnterIsr(cLDBHarInterruptTrpVerlogTimerIt);
#else
void LDBTrpVerlogTimerIt(void)
{
#endif

    DATVlgCallBackCtrl();

    mLDBIntClearIsrRequestFlag(cLDBHarInterruptTrpVerlogTimerIt);
#ifndef X90_PROJECT
    mLDBIntLeaveIsr(cLDBHarInterruptTrpVerlogTimerIt);
#endif
}

//*****************************************************************************
//  DESCRIPTION         : Init of the LDB_TRP
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
MEM_TYPE void LDBTrpInit(void)
{  
    mLDBHarWrite(cLDBHarTrpOut, 0);
    mLDBHarConfig(cLDBHarTrpOut, cLDBHarOutput);
    mLDBHarConfig(cLDBHarTrpIn, cLDBHarInput);

    mStopTimeOut();
    mStopTimeCaptureTimer();
    mLDBIntDisableIsr(cLDBHarInterruptTrpTimeCaptureIt);
    mLDBIntDisableIsr(cLDBHarInterruptTrpTimeOutIt);
    mLDBIntDisableIsr(cLDBHarInterruptTrpPPGIt);
    DecodingState = cStop;

    u8ShortCircuitToGnd = 0;
    u8ShortCircuitToBat = 0;

    bLDBTrpIsVerlogTimerEnabled = cFalse;
}

//*****************************************************************************
//  DESCRIPTION         : Send data to the transponder
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//    - Addr  : Transponder command
//    - *pMsg : Data buffer
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
//QACJ 3206:amanevd: This is how it comes from STK
MEM_TYPE void LDBTrpSendWithAddr(tAddress Addr, const tMsg * const pMsg)
{
    U8 u8NumberOfBytesToSend;


    mLIBassert(NULL != pMsg);

    //--------------------------------------
    // Command expects data responce
    //--------------------------------------
    bReceiveData = cTrue;

    //-------------------------------------------------------------
    // Compute the number of bytes to send
    //-------------------------------------------------------------
    //QACJ 0506:amanevd: The pointer is checked with assert in debug mode
    u8NumberOfBytesToSend = ((U8)pMsg->Lng >> cDivideBy8);

    //-------------------------------------------------------------
    // Store the data to write
    //-------------------------------------------------------------
    mLIBmemcpy(TransponderBuffer, pMsg->pBuffer, u8NumberOfBytesToSend);

    //-------------------------------------------------------------
    // Prepare message to send the data
    //-------------------------------------------------------------
    TransponderMessage.pBuffer  = &TransponderBuffer[u8NumberOfBytesToSend - 1];
    TransponderMessage.Lng      = pMsg->Lng;
    pu8ReceptionBuffer          = TransponderMessage.pBuffer;

    mLIBassert(NULL != pu8ReceptionBuffer);

    //-------------------------------------------------------------
    // Test if a writing in a transponder memory page is requested
    //-------------------------------------------------------------
    bTimeOutTProgRequested = ((U8)(pMsg->Lng) == cDataPageSizeInBit);
    
    DecodingState = cTimeOutInterCom;
    mWriteTranspondeurLine(1);
    //QACJ 0434:amanevd: 'CR000' is declared in io78f0536_64.h
    mStartTimeOut(cTInterCom);

    InitCom();
}

//*****************************************************************************
//  DESCRIPTION         : Receive data from the transponder
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//    - Addr  : Transponder command
//    - *pMsg : data buffer
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
MEM_TYPE void LDBTrpReceiveWithAddr(const tAddress Addr, const tMsg * const pMsg)
{
    mLIBassert(NULL != pMsg);

    //--------------------------------------
    // Command data responce is filled in pMsg
    //--------------------------------------
    bReceiveData = cFalse;

    //--------------------------------------
    // Prepare message to send the command
    //--------------------------------------    
    if (Addr == cLDBTrpStartAuth)
    {
        TransponderMessage.Lng = cShortCommandLenght;
        CurrentCommand[1] = (U8)(Addr << cShiftBy3);
    }
    else
    {
        TransponderMessage.Lng = cLongCommandLenght;
        CurrentCommand[1] = (U8)((U8)(Addr >> cShiftBy8) & cCommandLastByteMask);
        CurrentCommand[0] = (U8)(Addr >> cShiftBy6);
    }

    TransponderMessage.pBuffer = ((U8*)&CurrentCommand[1]);

    //--------------------------------------
    // Prepare data to receive response
    //--------------------------------------
    //QACJ 0506:amanevd: The pointer is checked with assert in debug mode
    if (pMsg->Lng == cLongCommandLenght)
    {
        pu8ReceptionBuffer = &pMsg->pBuffer[1];
    }
    else
    {
        pu8ReceptionBuffer = &pMsg->pBuffer[(U8)(pMsg->Lng >> cDivideBy8) - (U8)1U];
    }

    mLIBassert(NULL != pu8ReceptionBuffer);
    u8ExpectedBitsNb = (U8)pMsg->Lng;

    bTimeOutTProgRequested = cFalse;
    DecodingState          = cTimeOutInterCom;
    mWriteTranspondeurLine(1);
    //QACJ 0434:amanevd: 'CR000' is declared in io78f0536_64.h
    mStartTimeOut(cTInterCom);

    InitCom();
}

//*****************************************************************************
//  DESCRIPTION         : Send a control to the base-station
//
//  PARAMETERS (Type,Name,Min,Max): 
//      - Ctrl: Control send to the base-station
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
MEM_TYPE void LDBTrpControl(const tCtrl Ctrl)
{
    switch (Ctrl)
    {
        case cLDBTrpWakeUp:    

        //QACJ 0434:amanevd: 'CR000' is declared in io78f0536_64.h
        mStartTimeOut(cTWaitBeforeWakeUpRaisingEdge);
        mWriteTranspondeurLine(0);
        DecodingState = cGenerateRaisingEdge;

        mStartVerlogTimer();
        InitCom();
        break;

        case cLDBTrpSleep:    

        mStartTimeOut(cTStartSleep);
        u8RestartCounter = 0;
        DecodingState    = cStartSleep;

#ifdef X90_PROJECT
        mLDBIntGetInterruptTM00TM01(cLDBIntTrpOwnerTM00TM01);
#endif
        mLDBIntDisableIsr(cLDBHarInterruptTrpTimeOutIt);
        mLDBIntClearIsrRequestFlag(cLDBHarInterruptTrpTimeOutIt);
        mLDBIntEnableIsr(cLDBHarInterruptTrpTimeOutIt);

        mLDBIntDisableIsr(cLDBHarInterruptTrpTimeCaptureIt);
        mLDBIntClearIsrRequestFlag(cLDBHarInterruptTrpTimeCaptureIt);
        break;

        case cLDBTrpStop:

        StopCom();
        break;

        case cLDBTrpStopVerlog:

        mStopVerlogTimer();
        break;

        case cLDBTrpEnterNominalMode:

        mLDBHarWrite(cLDBHarTrpOut, 0);
        mLDBHarConfig(cLDBHarTrpOut, cLDBHarOutput);
        mLDBHarConfig(cLDBHarTrpIn, cLDBHarInput);
        break;

        case cLDBTrpEnterSleepMode:

        mLDBHarWrite(cLDBHarTrpOut, 0);
        mLDBHarConfig(cLDBHarTrpOut, cLDBHarOutput);
        mLDBHarConfig(cLDBHarTrpIn, cLDBHarInput);
        mStopVerlogTimer();
        break;

        default:
        mLIBassert(cFalse);
        break;
    }
}
