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
// Component:    LDB_RF
// -----------------------------------------------------------------------------
// $Date:   Feb 22 2010 15:31:56  $
// $Archive::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_RF/LDB_RF.c-arc  $
// $Revision:   1.12  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_RF/LDB_RF.c-arc  $
// 
//    Rev 1.12   Feb 22 2010 15:31:56   adzhelp
// Cm005818: Code review corrections
// 
//    Rev 1.11   Feb 12 2010 17:16:56   adzhelp
// Cm005818: Timeout for M pattern scanning sequence removed
// 
//    Rev 1.10   Feb 08 2010 11:10:38   adzhelp
// Cm005818: Corrections according to JML issues
// 
//    Rev 1.9   Oct 06 2009 17:40:38   adzhelp
// Cm005818: Function moved to banked area
// 
//    Rev 1.8   Oct 06 2009 12:38:00   ailievb
// Cm005818: All SI blocks should be received and send to dat layer
// 
//    Rev 1.7   Sep 23 2009 10:43:42   ailievb
// Cm005818:RKE: Update RFchannel according to issues identified in AW1092 project
// 
//    Rev 1.6   Sep 21 2009 13:27:06   adzhelp
// Cm005180: Flag for STROBE control added
// 
//    Rev 1.5   Sep 07 2009 10:24:34   ailievb
// Cm005100: QAC and code review fix.
// 
//    Rev 1.4   Jul 10 2009 17:15:46   ailievb
// Cm005100:Writing mistake:char ":" at line 797 is changed to ";"
// 
//    Rev 1.3   Jul 10 2009 14:31:22   ailievb
// Cm004983:  W&S: The consumption in Sleep Mode is above 2.35 mA
// 
//    Rev 1.2   Jul 10 2009 13:55:28   ailievb
// Cm005100: Integration: some robust requirements are not respected in SW,1 SAD.ROB.OUT.01.R01
// 
//    Rev 1.1   Apr 28 2009 10:42:56   adzhelp
// Cm003276: Implementation of RF sleep mode management
// 
//    Rev 1.0   Apr 17 2009 09:40:42   ailievb
// Initial revision.
// 
//******************************************************************************
#endif

//--------------------------------------------------------------------------
//  Body Identification
//--------------------------------------------------------------------------

#define ldb_rf   "ldb_rf"

//-------------------------------------------------------------------------
//  Included files
//
//  #include <system_file_name.h>
//  #include "project_file_name.h"
//--------------------------------------------------------------------------

#include "lib.h"
#include "ldb.h"
#include "ldb_ioc.h"
#include "ldb_int.h"
#include "ldb_tim.h"
#include "ldb_har.h"
#include "ldb_rf.h"

//--------------------------------------------------------------------------
//  Local constants
//
//  #define cConstantName   ((tType) ConstantValue)
//--------------------------------------------------------------------------
#define cNextByteMask             ((U8)7U)
#define cRCBlockIndex             ((U8)0U)
#define cSIBlockIndex             ((U8)1U)
#define cMaxU16                   ((U16)0xFFFFU)
#define cNbBytesInRCBlockToBeRead (U8)(cLDBRfNbBitsInRCBlockToBeRead/8)


#define cTBitMaxIC                                                             \
         (U16)(mConvUsInTickRfTimerIC((cLDBRfTBitInUs + cLDBRfWakeUpBitToleranceInUs)))
#define cTBitMinIC                                                                                                          \
         (U16)(mConvUsInTickRfTimerIC(cLDBRfTBitInUs                            \
                                          - cLDBRfWakeUpBitToleranceInUs      \
                                          - cLDBRfMaxInterruptDurationInUs    \
                                          - cLDBRfLDBRegWaitDelay))

#define cTBitMaxOC                                                             \
         (U16)(mConvUsInTickRfTimerOC((cLDBRfTBitInUs + cLDBRfWakeUpBitToleranceInUs)))
#define cTBitMinOC                                                                                                          \
         (U16)(mConvUsInTickRfTimerOC(cLDBRfTBitInUs                            \
                                          - cLDBRfWakeUpBitToleranceInUs      \
                                          - cLDBRfMaxInterruptDurationInUs    \
                                          - cLDBRfLDBRegWaitDelay))

#define cTBitMinWithoutMaxInterruptDuration                                                                                                          \
         (U16)(mConvUsInTickRfTimerOC(cLDBRfTBitInUs                            \
                                          - cLDBRfWakeUpBitToleranceInUs      \
                                          - cLDBRfLDBRegWaitDelay))
// TimeOuts
#define cRfHardwareActivationTime                                            \
         mConvUsInTickRfTimerOC(cLDBRfRfHardwareActivationTimeInUs)
#define cRfHardwareActivationTimeSleep                                       \
         mConvUsInTickRfTimerOC(cLDBRfRfHardwareActivationTimeSleepInUs)
#define cWakeUpDetectionTimeOut                                              \
         ((cLDBRfMinNbWakeUpBits + cLDBRfMaxNbErrorWakeUpBits) * cTBitMaxOC) 
#define cWaitPreambleBitsTime                                                \
         (U16)(cLDBRfNbPreambleBitsTimeOut * cTBitMinOC)
#define cStartBitWindowClosingTime                                           \
          ( ((U16)(3*cTBitMaxOC/2)) - cTBitMinOC ) 
#define cSIBlockEndTime                                                      \
         mConvUsInTickRfTimerOC(cLDBRfNbBitsInSpaceOfSIBlock * cLDBRfTBitInUs)
//(10+1)*256 should be Tmax                 
#define cTOneAndAHalfBitMax       ((U16)((3*cTBitMaxIC)/2)) //=1.5*TBitMax=T1+T2+T2p

//--------------------------------------------------------------------------
//  Local macros
//
//  #define mMacroName   (MacroDefinition)
//--------------------------------------------------------------------------
#ifdef _DEBUG_WITH_GENERATOR_
    #define mActivateRfHardware()     mLDBHarWrite(cLDBHarRfStrobe,0)
#else
    #define mActivateRfHardware()     mLDBHarWrite(cLDBHarRfStrobe,1)
#endif

#define mDeactivateRfHardware()       mLDBHarWrite(cLDBHarRfStrobe,0)
#define mReadRfInput()                (U8)mLDBHarRead(cLDBHarRfInput)

#define mConvUsInTickRfTimerIC(Tps)                                            \
         (U16)(( (U32)((Tps) * (U32)1000U)/cLDBHarTickInNsRfTimerIC ) - (U32)1U)

#define mConvUsInTickRfTimerOC(Tps)                                            \
         (U16)(( (U32)((Tps) * (U32)1000U)/cLDBHarTickInNsRfTimerOC ) - (U32)1U)

#define mWakeUpEdgeInValidDataRange(Time)                                      \
          (BOOL)((  (( (U16)(Time) >= (U16)(2*cTBitMinIC))   && ( (U16)(Time) <= (U16)(2*cTBitMaxIC)))      \
          /*//QACJ 3435: ailievb: there is no side effect*/                    \
          /*//QACJ 3456: ailievb: there is no side effect*/                    \
          || (( (U16)(Time) >= (U16)((3*cTBitMinIC)/2)) && ( (Time) <= (U16)((3*cTBitMaxIC)/2)))  ))
#define mReadTimeCaptureValue()   \
          (mLDBIocReadTrigger(cLDBHarRfTriggerIC))


#ifndef _QAC_
#define mStartAcquistion()                                                     \
          mLDBIocStopTimer(cLDBHarRfTimerIC);                                  \
          mLDBIocSelectClock(cLDBHarRfTimerIC, cLDBHarSelectClockRfTimeCaptureTimer); \
          mLDBIocSelectCaptureMode(cLDBHarRfTimerIC, cLDBHarModeRfTimeCaptureTimer);  \
          mLDBIocWriteTrigger(cLDBHarRfTriggerIC2,cMaxU16-1);                  \
          mLDBIocSetEdgeDetection(cLDBHarRfTimerIC, cLDBRfWakeUpEdge);         \
          mLDBIocFreeRunningModeStartTimer(cLDBHarRfTimerIC)


#define mStartScanning(Trigger)                                                \
          mLDBIocStopTimer(cLDBHarRfTimerIC);                                  \
          mLDBIocSelectClock(cLDBHarRfTimerIC, cLDBHarSelectClockRfTimeCaptureTimer);  \
          mLDBIocSelectCaptureMode(cLDBHarRfTimerIC, cLDBHarModeRfTimeDoubleInterval); \
          mLDBIocWriteTrigger(cLDBHarRfTriggerIC, ((Trigger)-1));              \
          mLDBIocWriteTrigger(cLDBHarRfTriggerIC2, ((Trigger)-1));             \
          mLDBIocStartTimer(cLDBHarRfTimerIC)

//Output Capture Timer to be defined in ldb_harp.h
#define mStartTimeOut(Trigger)                                                 \
          mLDBIocStopTimer(cLDBHarRfTimerOC);                                  \
          mLDBIocSelectClock(cLDBHarRfTimerOC, cLDBHarCounterSourceRfTimerOC); \
          mLDBIocWriteTrigger(cLDBHarRfTriggerOC, ((Trigger)-1));              \
          mLDBIocStartTimer(cLDBHarRfTimerOC)

#define mStopTimeOut()                                                         \
          mLDBIocStopTimer(cLDBHarRfTimerOC);                                  \
          mLDBIntClearIsrRequestFlag(cLDBHarInterruptRfOCIt)
#else
// QAC configuration
  #define mStartAcquistion() NOP()
  #define mRestartAcquistion() NOP()                                                 
  #define mStartScanning(Trigger) NOP()
  #define mStartTimeOut(Trigger) NOP()
  #define mStopTimeOut() NOP()
#endif

//--------------------------------------------------------------------------
//  Local types
//
//  struct  sStructureName { ... };
//  union   uUnionName { ... };
//  enum    eEnumerationName { ... };
//  typedef Expression tTypeName;
//--------------------------------------------------------------------------
typedef enum
{ 
    cEndActivationTime, //"false enum" to avoid 16Bit constants
    cDetectWakeUp,
    cMPatternScanning,
    cTempoPreamble,
    cScan0,
    cScan1,
    cFirstPreambleEdgeDetection,
    cOpenWindowStartBit,
    cCloseWindowStartBit,
    cOpenWindowData,
    cDecoding,
    cTempoSIBlock,
    cStop
}tStateMachine;
//--------------------------------------------------------------------------
//  Local data
//
//  static  tType   VariableName;
//  static  tType*  pVariableName; 
//--------------------------------------------------------------------------

//counts the number of bits detected in block (WakeUp, Synchro and Data )
static U8   u8NbBitOk;
static U8   u8NbErrors;
static BOOL bLastEdgeSynchronized;
static U8   u8ReceivedBits;

static U16  u16Time;
//State machine variable
static tStateMachine u8DecodingState;

//message sent to DAT layer
static U8   u8ReceptionBuffer[cNbBytesInRCBlockToBeRead]; 
static U8*  pu8ReceptionBuffer;
static tMsg Msg;
static U16 u16TimeMeasuredOld;

static BOOL bSleepMode = cTrue;
static BOOL bRfChannelDeactivated = cFalse;

#ifdef _DEBUG_LDBRF_ //debug  
    U8  i;
    U8  j;
    U16 u16NbLDBControlSearchWUP;
    U16 u16NbWUPTimeOut;
    U16 u16NbWUPBlocksSeen;
    U16 u16NbMPatternsSeen;
    U16 u16Nb1stPreambleDetectionSeen;
    U16 u16NbStartBitSeen;
    U16 u16NbMissedRC_WindowWasClosed;
    U16 u16NbRCBlocksSeen;
    U16 u16NbSIBlocksSeen;
#endif
//--------------------------------------------------------------------------
//  Constant local data
//
//  static const tType  VariableName;
//--------------------------------------------------------------------------


//--------------------------------------------------------------------------
//  Exported data
//
//  tType   CNLVariableName;      (CNL: 3 characters to identify this component)
//  tType*  pCNLVariableName;     (CNL: 3 characters to identify this component)
//--------------------------------------------------------------------------
BOOL bLDBRfIsWakeUpDetectionFinished = cTrue;

//--------------------------------------------------------------------------
//  Constant exported data
// 
//  const tType   CNLVariableName;(CNL: 3 characters to identify this component)
//--------------------------------------------------------------------------


//--------------------------------------------------------------------------
//  Local function prototypes
//  
//  static tTypeRetour FunctionName(tTypeArgument1 ArgumentName1, ... );
//--------------------------------------------------------------------------
static void InitializeReceiving(void);
static void StoreBit(U1 u8Bit);

//============================================================================
//=========================== LOCAL FUNCTIONS ================================
//==========================================================================

//==========================================================================
//  DESCRIPTION : StoreBit
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION : 
//==========================================================================
static void StoreBit(const U1 u8Bit)
{
    if(u8ReceivedBits < cLDBRfNbBitsInRCBlockToBeRead)
    {
        if (u8ReceivedBits == 0)
        {
            pu8ReceptionBuffer = &u8ReceptionBuffer[0]; 
            *pu8ReceptionBuffer = u8Bit;
            
#ifdef _DEBUG_LDBRF_
            i = 0;
#endif
        }
        else
        {
            //QACJ 0490: ailievb: This is intentionally done and works correctly.
            //QACJ 3683: ailievb: This is intentionally done and works correctly.
            //QACJ 3892: ailievb: This is intentionally done and works correctly.
            if( (pu8ReceptionBuffer < &u8ReceptionBuffer[cNbBytesInRCBlockToBeRead]) &&
                (pu8ReceptionBuffer >= &u8ReceptionBuffer[0]) )
            {
                //QACJ 0506: ailievb: This is intentionally done and works correctly.
                *pu8ReceptionBuffer = (*pu8ReceptionBuffer << 1) + u8Bit;
                if((U8)(u8ReceivedBits & cNextByteMask) == cNextByteMask)
                {
                    //QACJ 0489: ailievb: This is intentionally done and works correctly.
                    pu8ReceptionBuffer++;
                }
            }
        }
        u8ReceivedBits++;
        
#ifdef _DEBUG_LDBRF_ //shows n° of data seen last time an RC was detected
        i = u8ReceivedBits;
#endif
    }
}

//==========================================================================
//  DESCRIPTION : InitializeReceiving
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION : Initialization of state machine
//==========================================================================
static void InitializeReceiving( void )
{ 
    mLDBIntDisableIsr(cLDBHarInterruptRfICIt);
    mLDBIntDisableIsr(cLDBHarInterruptRfOCIt);
    //clear timers
    //QACJ 3109: ailievb: Empty statement due to macro implementation in ldb_ioc.h
    mLDBIocStopTimer(cLDBHarRfTimerIC);
    //QACJ 3109: ailievb: Empty statement due to macro implementation in ldb_ioc.h
    mLDBIocStopTimer(cLDBHarRfTimerOC);
    
    //init all variables
    u8NbBitOk  = 0;                         
    u8NbErrors = 0;
    bLastEdgeSynchronized = 0;
    u8ReceivedBits = 0;
    u16Time = 0;
    mLIBmemset (u8ReceptionBuffer,0,cNbBytesInRCBlockToBeRead); 
    Msg.Lng = 0;        
    Msg.pBuffer = u8ReceptionBuffer;
    pu8ReceptionBuffer = &u8ReceptionBuffer[0]; 
}

//============================================================================
//=========================== EXPORTED FUNCTIONS =============================
//============================================================================

//============================================================================
//  DESCRIPTION :InputCaptureIt (void)
//  
//  PARAMETERS (Type,Name,Min,Max) : none 
//
//  RETURN VALUE : none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//============================================================================
#ifdef UTEST
mLDBIntDeclareIsr(cLDBHarInterruptRfICIt)
{
    mLDBIntEnterIsr(cLDBHarInterruptRfICIt);
#else
void LDBRfInterruptRfICIt(void)
{
#endif
    U16 u16TimeMeasured;
    BOOL bDecodingProblem;
    
    //QACJ 0434: ailievb: CR010 is a MCU register identifier   
    u16TimeMeasured = (U16)mReadTimeCaptureValue();
    mLDBIntClearIsrRequestFlag(cLDBHarInterruptRfICIt); 
    switch(u8DecodingState)
    {
    case cDetectWakeUp:
        //read IC timer value in timer ticks (U16)
        //QACJ 0434: ailievb: TM00 is a MCU register identifier
        u16TimeMeasured = (U16)mReadTimeCaptureValue();
        u16Time = u16TimeMeasured - u16TimeMeasuredOld; 
        u16TimeMeasuredOld = u16TimeMeasured;

#ifdef _DEBUG_LDBRF_
        j++;
#endif
        if(( u16Time >= cTBitMinIC) && ( u16Time <= cTBitMaxIC))
        {
            u8NbBitOk+= cLDBRfWakeUpIncrement; //+1 for X90
            if(u8NbBitOk >= cLDBRfMinNbWakeUpBits)
            {
                mStopTimeOut();   //WakeUp timeout  
                mLDBIntDisableIsr(cLDBHarInterruptRfOCIt); // PONAEHNT084532.003 Step 3b: OC INT has to be disabled 
                u8NbBitOk = 0;
                mStartScanning(cTBitMinIC/2); //TBitMin/2
                u8DecodingState = cMPatternScanning;
                DATRfCallBackCtrl(cLDBRfWakeUpReceived);
#ifdef _DEBUG_LDBRF_
                u16NbWUPBlocksSeen++;
#endif
            }
            else
            {
            } //nothing to do
        }
        //edges that have timings corresponding to data frames timings
        //or maximum number of errors accepted has been reached
        //QACJ 3356: The 'if' expression is not analyzed correctly
        else if(  (  (mWakeUpEdgeInValidDataRange(u16Time) == cTrue)
                || (u8NbErrors >= cLDBRfMaxNbErrorWakeUpBits)   )
               /* && (u8NbBitOk > 1) */ )  // PONAEHNT084532.003 Step 3b
        { 
            mLDBIntDisableIsr(cLDBHarInterruptRfICIt);
            mLDBIntDisableIsr(cLDBHarInterruptRfOCIt);
            //QACJ 3109: ailievb: Empty statement due to macro implementation in ldb_ioc.h
            mLDBIocStopTimer(cLDBHarRfTimerIC);
            //QACJ 3109: ailievb: Empty statement due to macro implementation in ldb_ioc.h
            mLDBIocStopTimer(cLDBHarRfTimerOC);
            mDeactivateRfHardware();
            u8DecodingState = cStop;
#ifdef _DEBUG_LDBRF_
            u16NbWUPTimeOut++;
#endif
            DATRfCallBackCtrl(cLDBRfWakeUpNotReceived); // Enable sleep mode
            bLDBRfIsWakeUpDetectionFinished = cTrue;
        }
        else //count "errors", edges not accepted as part of WakeUp
        {
            u8NbErrors++;
        } 
        break;
            
    case cMPatternScanning://detects, through sampling, the M sequence (X consecutive samples = 1)
        //then waits TimeOut shorter than preamble duration
        //then detects 0 + 1: StartBit
        //QACJ 3346: ailievb: a register value is checked here
        if(mReadRfInput() == cLDBRfMPatternBit)
        {
            u8NbBitOk++;
            u8NbErrors = 0; // PONAEHNT084532.003, Step 4 : u8NbErrors is reinitialized to manage timeout
            if(u8NbBitOk >= cLDBRfMinNbMPatternBits)
            {
                //QACJ 3109: ailievb: Empty statement due to macro implementation in ldb_ioc.h
                mLDBIocStopTimer(cLDBHarRfTimerIC); //stop interval timer
                mLDBIntDisableIsr(cLDBHarInterruptRfICIt); // PONAEHNT084532.003, Step 4
                u8DecodingState = cTempoPreamble;
                mStartTimeOut(cWaitPreambleBitsTime); 
                // PONAEHNT084532.003 Step 3b 
                mLDBIntClearIsrRequestFlag(cLDBHarInterruptRfOCIt);
                mLDBIntEnableIsr(cLDBHarInterruptRfOCIt); 
#ifdef _DEBUG_LDBRF_
                u16NbMPatternsSeen++;
#endif
            }
            else
            {
            } //nothing to do, wait next IC It
        }
        else
        //QACJ 3201: ailievb: This statement is reachable when mReadRfInput is 1
        { //not yet in M sequence zone, wait next IC It
            u8NbBitOk = 0;
        }
        break;
            
    case cScan0:
        //QACJ 3325: ailievb: This control expression is true when mReadRfInput <> 0
        if(mReadRfInput() != cLDBRfMPatternBit) //Scan0 detected
        //QACJ 3201: ailievb: This statement is reachable when mReadRfInput is 1
        {
            u8NbErrors = 0; // PONAEHNT084532.003, Step 4 : u8NbErrors is reinitialized to manage timeout
            u8DecodingState = cScan1;
        }
        else
        {
            u8NbErrors++;
            if(u8NbErrors >= cLDBRfMaxNbPreambleErrorBits) //too many non Scan0 detected
            {
                mStopTimeOut();
                u8NbBitOk = 0;
                mStartScanning(cTBitMinIC/2); //TBitMin/2
                u8DecodingState = cMPatternScanning;
            }
            else
            {} //nothing to do, wait for next sample
        }
        break;
            
            
    case cScan1:
        //QACJ 3346: ailievb: a register value is checked here
        if(mReadRfInput() == cLDBRfMPatternBit) //Scan1 detected
        {
            //QACJ 3109: ailievb: Empty statement due to macro implementation in ldb_ioc.h
            mLDBIocStopTimer(cLDBHarRfTimerIC); //stop interval timer
            u8DecodingState = cFirstPreambleEdgeDetection;
            mStartAcquistion(); //Input capture
            mStartTimeOut(3*(cTBitMaxOC/2)); //start TimeOut 1st PreambleEdge
            mLDBIntClearIsrRequestFlag(cLDBHarInterruptRfOCIt);
            mLDBIntEnableIsr(cLDBHarInterruptRfOCIt);  // PONAEHNT084532.003, Step 5,7
        }
        else
        //QACJ 3201: ailievb: This statement is reachable when mReadRfInput is 1
        {
            u8NbErrors++;
            if(u8NbErrors >= cLDBRfMaxNbPreambleErrorBits)
            {
                mStopTimeOut();
                u8NbBitOk = 0;
                mStartScanning(cTBitMinIC/2); //TBitMin/2
                u8DecodingState = cMPatternScanning;
            }
            else
            {} //nothing to do, wait for next sample
        }
        break;
            
    case cFirstPreambleEdgeDetection: //edge detected
        mLDBIntDisableIsr(cLDBHarInterruptRfICIt);  // PONAEHNT084532.003, Step 8
        mStartTimeOut(cTBitMinWithoutMaxInterruptDuration - (mLDBIocReadCounter(cLDBHarRfTimerIC) - u16TimeMeasured)); // wait time(T1) to open window
        u16TimeMeasuredOld = u16TimeMeasured;
        u8NbBitOk = 0;
        u8DecodingState = cOpenWindowStartBit;
#ifdef _DEBUG_LDBRF_
        u16Nb1stPreambleDetectionSeen++;
#endif
        break;
            
    case cCloseWindowStartBit: //StartBit edge maybe detected
        u16TimeMeasured = (U16)mReadTimeCaptureValue(); 
        u16Time = u16TimeMeasured - u16TimeMeasuredOld;
        u16TimeMeasuredOld = u16TimeMeasured;
        if(u16Time > cTBitMaxIC) //StartBit found
        { 
            mLDBIntDisableIsr(cLDBHarInterruptRfICIt);  // PONAEHNT084532.003, Step 10
            u8DecodingState = cOpenWindowData;        
            u8ReceivedBits = 0; 
            bLastEdgeSynchronized = cFalse; 
            mStartTimeOut(cTBitMinWithoutMaxInterruptDuration - (mLDBIocReadCounter(cLDBHarRfTimerIC) - u16TimeMeasured));   // PONAEHNT084532.003, Step 10
#ifdef _DEBUG_LDBRF_
            u16NbStartBitSeen++; 
#endif
        }
        else
        { 
            u8NbBitOk++;
            if(u8NbBitOk >= cLDBRfNbBitsInPreamble)
            {
                mStopTimeOut();
                u8NbBitOk = 0;
                mStartScanning(cTBitMinIC/2); //TBitMin/2
                u8DecodingState = cMPatternScanning;
            }
            else //noise or preamble bit, nothing to do, waiting for StartBit
            {
                mStartTimeOut(cTBitMinWithoutMaxInterruptDuration - (mLDBIocReadCounter(cLDBHarRfTimerIC) - u16TimeMeasured));
                mLDBIntDisableIsr(cLDBHarInterruptRfICIt);
                u8DecodingState = cOpenWindowStartBit;
            }
        }
        u16Time = 0;
        break;
            
    case cDecoding:
        u16TimeMeasured = (U16)mReadTimeCaptureValue(); 
        u16Time = u16TimeMeasured - u16TimeMeasuredOld;
        u16TimeMeasuredOld = u16TimeMeasured;
        
        bDecodingProblem = cFalse;
        if(u16Time <= cTBitMaxIC) //in window TBit
        {            
            if(bLastEdgeSynchronized == cFalse)
            {
                StoreBit(1);
            }
            else
            {
                StoreBit(0); 
            }
        }
        else if(u16Time <= cTOneAndAHalfBitMax) //in window T1.5Bit
        {
            if(bLastEdgeSynchronized == cFalse)
            {
                StoreBit(0);
                if(u8ReceivedBits < cLDBRfNbBitsInRCBlockToBeRead) 
                {
                    bLastEdgeSynchronized = cTrue;
                }
                else
                {} //nothing to do
            }
            else
            {
                StoreBit(0);
                StoreBit(1);
                if(u8ReceivedBits < cLDBRfNbBitsInRCBlockToBeRead) 
                {
                    bLastEdgeSynchronized = cFalse;
                }
                else
                {} //nothing to do
            }
        }
        else //in window T2Bit or end of data
        {
            if(bLastEdgeSynchronized == cFalse)
            {
                StoreBit(0);
                StoreBit(1);
            }
            else // PONAEH084532 step 12 - text in yellow in standard algorithm in addition to §5.2
            {
                bDecodingProblem = cTrue;

                if(u8ReceivedBits == cLDBRfNbBitsInSIBlockToBeRead)
                {
                    //stop IC timer
                    mLDBIocStopTimer(cLDBHarRfTimerIC);
                    mLDBIntClearIsrRequestFlag(cLDBHarInterruptRfICIt); 
                    mLDBIntDisableIsr(cLDBHarInterruptRfICIt);

                    Msg.Lng = (U16)cLDBRfNbBitsInSIBlockToBeRead;
                    DATRfRxSpontTable[cSIBlockIndex].pCallBackRx(0x0000, cTrue, &Msg);

                    mStartTimeOut(cSIBlockEndTime);
                    u8DecodingState = cTempoSIBlock;
#ifdef _DEBUG_LDBRF_
                    NbSIBlocksSeen++;
#endif
                }
                else //look for a new block
                {
#ifdef _DEBUG_LDBRF_
                    u16NbMissedRC_WindowWasClosed++;
#endif
                    mStopTimeOut();
                    u8NbBitOk = 0;
                    mLDBIntClearIsrRequestFlag(cLDBHarInterruptRfICIt);
                    mStartScanning(cTBitMinIC/2); //TBitMin/2
                    u8DecodingState = cMPatternScanning;
                }
            }  
        }   

        if (bDecodingProblem == cFalse)
        {
            if(u8ReceivedBits >= cLDBRfNbBitsInRCBlockToBeRead)
            { //14 doc JM.L
                //stop all timers
                #ifdef DEBUG_SPECIFIED_KEY
                if (mLDBRfIsKeyMatch())
                #endif
                {
                    Msg.Lng = (U16)cLDBRfNbBitsInRCBlockToBeRead;   
                    DATRfRxSpontTable[cRCBlockIndex].pCallBackRx(0x0000, cTrue, &Msg);
                }
                //stop all timers
                //QACJ 3109: ailievb: Empty statement due to macro implementation in ldb_ioc.h
                mLDBIocStopTimer(cLDBHarRfTimerIC);
                mStopTimeOut();
                mLDBIntDisableIsr(cLDBHarInterruptRfOCIt); // PONAEHNT084532.003, Step 11
                u8NbBitOk = 0;
                mStartScanning(cTBitMinIC/2); 
                u8DecodingState = cMPatternScanning;
    #ifdef _DEBUG_LDBRF_
                u16NbRCBlocksSeen++;
    #endif
            }
            else
            { 
                // PONAEHNT084532.003, Step 12
                // When starting the timeout for cOpenWindowData, 
                // the timeout has to be set from Input Capture timing and not from INT processing (as latency may lead to open the window too late)
                mStartTimeOut(cTBitMinWithoutMaxInterruptDuration - (mLDBIocReadCounter(cLDBHarRfTimerIC) - u16TimeMeasured));   // PONAEHNT084532.003, Step 12
                mLDBIntDisableIsr(cLDBHarInterruptRfICIt); 
                u8DecodingState = cOpenWindowData;
            }
            u16Time = 0; 
        }
        break;
            
    default :
        mLIBassert(0);
        // stop LDB_RF
        mLDBIntDisableIsr(cLDBHarInterruptRfICIt);
        mLDBIntDisableIsr(cLDBHarInterruptRfOCIt );
        //QACJ 3109: ailievb: Empty statement due to macro implementation in ldb_ioc.h
        mLDBIocStopTimer(cLDBHarRfTimerIC);
        //QACJ 3109: ailievb: Empty statement due to macro implementation in ldb_ioc.h
        mLDBIocStopTimer(cLDBHarRfTimerOC);
        mDeactivateRfHardware();
        bLDBRfIsWakeUpDetectionFinished = cTrue;
        break;
    }
#ifdef UTEST
    mLDBIntLeaveIsr(cLDBHarInterruptRfICIt);
#endif
}

//============================================================================
//  DESCRIPTION :OutputCompareIt (void)
//  
//  PARAMETERS (Type,Name,Min,Max) : none 
//
//  RETURN VALUE : none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//============================================================================
#ifdef UTEST
mLDBIntDeclareIsr(cLDBHarInterruptRfOCIt)
{
    mLDBIntEnterIsr(cLDBHarInterruptRfOCIt);
#else
void LDBRfInterruptRfOCIt(void)
{
#endif
    switch(u8DecodingState)
    {
    case cEndActivationTime:
        mStartTimeOut(cWakeUpDetectionTimeOut); //start WakeUp detection timeout
        //Setup in Edge detection to wait for WakeUp block
        mLDBIntClearIsrRequestFlag(cLDBHarInterruptRfICIt);  // PONAEHNT084532.003, Step 1       
        mLDBIntEnableIsr(cLDBHarInterruptRfICIt);            // PONAEHNT084532.003, Step 1       
        mStartAcquistion();
        u16TimeMeasuredOld = 0;  
#ifndef DISABLE_RECEPTION
        u8DecodingState = cDetectWakeUp;
#else   // perform the same actions as in cDetectWakeUp when detection timeout ended
        u8DecodingState = cStop;
        mLDBIntDisableIsr(cLDBHarInterruptRfICIt);
        mLDBIntDisableIsr(cLDBHarInterruptRfOCIt);
        mLDBIocStopTimer(cLDBHarRfTimerIC);
        mLDBIocStopTimer(cLDBHarRfTimerOC);
    #ifdef MEASURE_RF_STROBE_DURATION
        mLDBHarWrite(cLDBHarPort1_3, 0);
    #endif
        mDeactivateRfHardware(); 
        u8DecodingState = cStop;
        DATRfCallBackCtrl(cLDBRfWakeUpNotReceived);   // Enable sleep mode
        bLDBRfIsWakeUpDetectionFinished = cTrue;
#endif

        break;
            
    case cDetectWakeUp: //WakeUp detection timeout is ended
        mLDBIntDisableIsr(cLDBHarInterruptRfICIt);
        mLDBIntDisableIsr(cLDBHarInterruptRfOCIt);
        //QACJ 3109: ailievb: Empty statement due to macro implementation in ldb_ioc.h
        mLDBIocStopTimer(cLDBHarRfTimerIC);
        //QACJ 3109: ailievb: Empty statement due to macro implementation in ldb_ioc.h
        mLDBIocStopTimer(cLDBHarRfTimerOC);
#ifdef MEASURE_RF_STROBE_DURATION
        mLDBHarWrite(cLDBHarPort1_3, 0);
#endif
        mDeactivateRfHardware(); 
        u8DecodingState = cStop;
#ifdef _DEBUG_LDBRF_
        u16NbWUPTimeOut++;
#endif
        DATRfCallBackCtrl(cLDBRfWakeUpNotReceived);   // Enable sleep mode
        bLDBRfIsWakeUpDetectionFinished = cTrue;
        break;
            
            
    case cTempoPreamble:
        mStopTimeOut();    
        mLDBIntDisableIsr(cLDBHarInterruptRfOCIt);  // PONAEHNT084532.003, Step 5
        u8NbErrors = 0; // PONAEHNT084532.003, Step 4 : u8NbErrors is reinitialized to manage timeout
        mStartScanning(cTBitMinIC/2); //TBitMin/2
        mLDBIntClearIsrRequestFlag(cLDBHarInterruptRfICIt);  
        mLDBIntEnableIsr(cLDBHarInterruptRfICIt); // PONAEHNT084532.003, Step 4
        u8DecodingState = cScan0;
        break;
            
            
    case cFirstPreambleEdgeDetection: //no edge was detected
        mStopTimeOut();                     //stop all timers
        mLDBIntDisableIsr(cLDBHarInterruptRfOCIt); // PONAEHNT084532.003 Step 8_Error
        //QACJ 3109: ailievb: Empty statement due to macro implementation in ldb_ioc.h
        mLDBIocStopTimer(cLDBHarRfTimerIC); 
        u8NbBitOk = 0;
        mLDBIntClearIsrRequestFlag(cLDBHarInterruptRfICIt);
        mStartScanning(cTBitMinIC/2); 
        u8DecodingState = cMPatternScanning;
        break;
            
            
    case cOpenWindowStartBit: 
        mLDBIntClearIsrRequestFlag(cLDBHarInterruptRfICIt);
        mLDBIntEnableIsr(cLDBHarInterruptRfICIt);  
        mStopTimeOut();
        mStartTimeOut(cStartBitWindowClosingTime);  //StartBitWindow ClosingTime
        u8DecodingState = cCloseWindowStartBit;
#ifdef _DEBUG_LDBRF_ //Toggles when window is opened
        u16NbWUPBlocksSeen++;
#endif
        break;
            
            
    case cCloseWindowStartBit: //didn't find StartBit, wait for mext RCBlock
        mLDBIntDisableIsr(cLDBHarInterruptRfICIt);      // PONAEHNT084532.003, Step 10_Error 
        mLDBIntDisableIsr(cLDBHarInterruptRfOCIt);      // PONAEHNT084532.003, Step 10_Error 
        u8NbBitOk = 0;
        mStartScanning(cTBitMinIC/2); //TBitMin/2
        u8DecodingState = cMPatternScanning;
        mLDBIntClearIsrRequestFlag(cLDBHarInterruptRfICIt);
        mLDBIntEnableIsr(cLDBHarInterruptRfICIt);      // PONAEHNT084532.003, Step 10_Error 
        break;
            
            
       //Start RC decoding and stocking
    case cOpenWindowData:
        mStartTimeOut( ((U16)(2*cTBitMaxOC)) - cTBitMinOC ) ; //WindowClosingTime
        u8DecodingState = cDecoding;
        mLDBIntClearIsrRequestFlag(cLDBHarInterruptRfICIt); // PONAEHNT084532.003, Step 10,11
        mLDBIntEnableIsr(cLDBHarInterruptRfICIt);           // PONAEHNT084532.003, Step 10,11
#ifdef _DEBUG_LDBRF_ //Toggles when window is opened
        u16NbWUPBlocksSeen++;
#endif
        break;
            
            
    case cDecoding: //window closed before any ICIt was detected!
        mStopTimeOut();
         
        if(u8ReceivedBits == cLDBRfNbBitsInSIBlockToBeRead)
        {
            //stop IC timer
            //QACJ 3109: ailievb: Empty statement due to macro implementation in ldb_ioc.h
            mLDBIocStopTimer(cLDBHarRfTimerIC);
            mLDBIntClearIsrRequestFlag(cLDBHarInterruptRfICIt); 
            mLDBIntDisableIsr(cLDBHarInterruptRfICIt);  // PONAEHNT084532.003, 12_Error
            Msg.Lng = (U16)cLDBRfNbBitsInSIBlockToBeRead;
            DATRfRxSpontTable[cSIBlockIndex].pCallBackRx(0x0000, cTrue, &Msg);
                
            mStartTimeOut(cSIBlockEndTime);
            u8DecodingState = cTempoSIBlock;
#ifdef _DEBUG_LDBRF_
            u16NbSIBlocksSeen++;
#endif
        }
        else //look for a new block
        {
#ifdef _DEBUG_LDBRF_
            u16NbMissedRC_WindowWasClosed++;
#endif
            u8NbBitOk = 0;
            mLDBIntDisableIsr(cLDBHarInterruptRfOCIt);  // PONAEHNT084532.003, 12_Error
            mStartScanning(cTBitMinIC/2); //TBitMin/2
            u8DecodingState = cMPatternScanning;
        }
        break;
            
            
    case cTempoSIBlock:
        mStopTimeOut();
        mLDBIntDisableIsr(cLDBHarInterruptRfOCIt);     // PONAEHNT084532.003, 12_Error
        u8NbBitOk = 0;
        mStartScanning(cTBitMinIC/2); //TBitMin/2
        u8DecodingState = cMPatternScanning;
        mLDBIntClearIsrRequestFlag(cLDBHarInterruptRfICIt);
        mLDBIntEnableIsr(cLDBHarInterruptRfICIt); 
        break;
            
    default :
        mLIBassert(0);
        // stop LDB_RF
        mLDBIntDisableIsr(cLDBHarInterruptRfICIt);
        mLDBIntDisableIsr(cLDBHarInterruptRfOCIt );
        //QACJ 3109: ailievb: Empty statement due to macro implementation in ldb_ioc.h
        mLDBIocStopTimer(cLDBHarRfTimerIC);
        //QACJ 3109: ailievb: Empty statement due to macro implementation in ldb_ioc.h
        mLDBIocStopTimer(cLDBHarRfTimerOC);
        mDeactivateRfHardware();
        bLDBRfIsWakeUpDetectionFinished = cTrue;

        break;
    }
#ifdef UTEST
    mLDBIntLeaveIsr(cLDBHarInterruptRfOCIt);
#endif
}

//============================================================================
//  DESCRIPTION :void LDBRfInit(void)
//                Init of the LDB layer
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//============================================================================
MEM_TYPE void LDBRfInit(void)
{
    mLDBHarWrite(cLDBHarRfStrobe, 0);
    mLDBHarConfig(cLDBHarRfStrobe,cLDBHarOutput);

    mLDBHarConfig(cLDBHarRfInput,cLDBHarInput);
    
    InitializeReceiving(); //Init all variables and stop timers
    mDeactivateRfHardware();  
    u8DecodingState = cStop;
    
#ifdef _DEBUG_LDBRF_ //Init debug variables
    i = 0;
    j = 0;
    u16NbLDBControlSearchWUP = 0;
    u16NbWUPTimeOut = 0;
    u16NbWUPBlocksSeen = 0;
    u16NbMPatternsSeen = 0;
    u16Nb1stPreambleDetectionSeen = 0;
    u16NbStartBitSeen = 0;
    u16NbMissedRC_WindowWasClosed = 0;
    u16NbRCBlocksSeen = 0;
    u16NbSIBlocksSeen = 0;
#endif
}

//============================================================================
//  DESCRIPTION :void LDBRfControl (tCtrl Ctrl)
//                Switching of the control access
//  
//  PARAMETERS (Type,Name,Min,Max) :  
//      - Channel: cLDBChannelRf
//      - Ctrl:    cLDBRfSearchFrame or cLDBRfStop
//
//  RETURN VALUE : none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//============================================================================
MEM_TYPE void LDBRfControl(const tCtrl Ctrl)
{
    switch(Ctrl)
    {
    case(cLDBRfSearchFrame):
#ifdef UTEST 
        InitializeReceiving();                //Init all variables and stop timers
        u8DecodingState = cEndActivationTime;
        mActivateRfHardware();
        mLDBIntClearIsrRequestFlag(cLDBHarInterruptRfICIt);
        mLDBIntEnableIsr(cLDBHarInterruptRfICIt);          
        mLDBIntClearIsrRequestFlag(cLDBHarInterruptRfOCIt);        
        mLDBIntEnableIsr(cLDBHarInterruptRfOCIt);        
        mStartTimeOut(cRfHardwareActivationTime); //timer 1 ms
#else
        bRfChannelDeactivated = cFalse;
        mLDBIntGetInterruptTM00TM01(cLDBIntRfOwnerTM00TM01);
        if (bSleepMode == cFalse)
        {
            #ifdef MEASURE_RF_STROBE_DURATION
                mLDBHarWrite(cLDBHarPort1_3, 1);
            #endif
            mActivateRfHardware();
        }

        if ((bSleepMode != cFalse) && ((BOOL)mLDBSupIsHwActivated() == cFalse))
        {
            // wait next clock cycle when HW will be activated by LDB_SUP
            DATRfCallBackCtrl(cLDBRfDecrementTempoSearchFrame);
        }
        else
        {
            InitializeReceiving(); //Init all variables and stop timers
            mLDBIntClearIsrRequestFlag(cLDBHarInterruptRfOCIt);        
            mLDBIntEnableIsr(cLDBHarInterruptRfOCIt);        
            //Setup to wait end of hardware TDA activation time
            u8DecodingState = cEndActivationTime;

            if (bSleepMode == cFalse)
            {
                mStartTimeOut(cRfHardwareActivationTime); //timer 1 ms
            }
            else
            {
                // in sleep mode strobe is activated earlier by LDB_SUP
                mStartTimeOut(cRfHardwareActivationTimeSleep); //timer 
            }
            bLDBRfIsWakeUpDetectionFinished = cFalse;
#ifdef _DEBUG_LDBRF_
            u16NbLDBControlSearchWUP++;
#endif
        }
#endif
        break;
        
    case(cLDBRfStop):  
        mLDBIntDisableIsr(cLDBHarInterruptRfICIt);
        mLDBIntDisableIsr(cLDBHarInterruptRfOCIt );
        //QACJ 3109: ailievb: Empty statement due to macro implementation in ldb_ioc.h
        mLDBIocStopTimer(cLDBHarRfTimerIC);
        //QACJ 3109: ailievb: Empty statement due to macro implementation in ldb_ioc.h
        mLDBIocStopTimer(cLDBHarRfTimerOC);
        mLDBIntReleaseInterruptTM00TM01(cLDBIntRfOwnerTM00TM01);
        mDeactivateRfHardware();
        bLDBRfIsWakeUpDetectionFinished = cTrue;
        break;
        
    case cLDBRfActivateStrobe:
        if (bRfChannelDeactivated == cFalse)
        {
            mActivateRfHardware();
        }
        break;
        
    case cLDBRfDeactivateStrobe:  // Called when RF is disabled in EEPROM
        mDeactivateRfHardware();             // Frame in course can be lost but it's not a problem
        bRfChannelDeactivated = cTrue;
        break;
    
    case cLDBRfEnterNominalMode:
        bSleepMode = cFalse;
        break;
    
    case cLDBRfEnterSleepMode:
        bSleepMode = cTrue;
        bLDBRfIsWakeUpDetectionFinished = cTrue;
        break;
        
    default:
        mLIBassert(cFalse);
        break;
    }
    
    DATRfCallBackEndCtrl(Ctrl, cLDBCorrect);
}

//============================================================================
//  DESCRIPTION :void LDBRfCallBackSleepTick (void)
//               Callback from sleep system timer
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE : none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//============================================================================
void LDBRfCallBackSleepTick(void)
{
    DATRfCallBackCtrl(cLDBRfControlSleepTick);
}

