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
// Component:    LDB_KWP
// -----------------------------------------------------------------------------
// $Date:   Oct 13 2010 09:25:12  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_KWP/LDB_KWP.C-arc  $
// $Revision:   1.10  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_KWP/LDB_KWP.C-arc   $
// 
//    Rev 1.10   Oct 13 2010 09:25:12   adzhelp
// Cm009704: QAC updates
// 
//    Rev 1.9   Oct 12 2010 17:22:36   adzhelp
// Cm009704: Disregard SC GND (local binary changes)
// 
//    Rev 1.8   Oct 12 2010 17:20:46   adzhelp
// Cm009704: Revert to rev. 1.6 (used in V03.05)
// 
//    Rev 1.7   Jul 06 2010 11:29:40   adzhelp
// Cm009704: Different callback status on SC VBAT / SC GND
// 
//    Rev 1.6   Jan 14 2010 14:26:50   adzhelp
// Cm006828: Implementation of new control for StartCom waiting
// 
//    Rev 1.5   Dec 14 2009 11:29:56   adzhelp
// Cm005566: SC detection of KLine
// 
//    Rev 1.4   Jul 13 2009 13:54:38   adzhelp
// Cm005100: Code review corrections
// 
//    Rev 1.3   Jul 13 2009 10:32:42   adzhelp
// Cm005100: Functions moved to banked area; QAC updates
// 
//    Rev 1.2   Jul 09 2009 16:37:16   akodzhh
// Cm005100: before all instances of mLDBIntEnableIsr(<interrupt>), there should be instance of mLDBIntClearIsrRequestFlag(<interrupt>).
// mLDBRegNop()usage adjusted. QAC warnings justified.
// 
//    Rev 1.1   Mar 17 2009 14:18:46   adzhelp
// Cm003128: Adaptation of LDB_KWP for NEC K0
//
//    Rev 1.0   10 Mar 2009 09:03:18   akodzhh
// Initial revision.
//******************************************************************************
#endif

//------------------------------------------------------------------------------
// Body Identification
//------------------------------------------------------------------------------
#define ldb_kwp   "ldb_kwp"

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------
#include "lib.h"
#include "ldb.h"
#include "ldb_int.h"
#include "ldb_tim.h"
#include "ldb_ioc.h"
#include "ldb_har.h"
#include "ldb_kwp.h"

//------------------------------------------------------------------------------
// Local constants
//------------------------------------------------------------------------------
#define cUARTBufferLgth           70

#define cTimeOutPeriodInUs        ((U16)10000)
#define cP1TimeOutInUs            ((U16)20000)

// Required UART baud rate is 10400
// Fprs = 16MHz, TPS01 = 1, TPS00 = 1 ->  Fxclk0 = 16000000/32 = 500kHz
// k = 24,    ( 16000000/32  )/2*k      => 10416.667 bps  => error = 0.16%
#define cUARTBaudRateRegValue   ((U8)0xD8)

#define cDisable                        0
#define cEnable                         1

//ParitySelection ASIMnPS
#define cNoParity                       0

//DataCharacterLength ASIMnCL
#define	c8Bits                          1

//StopBitLength ASIMnSL
#define c1Bit                           0

// Position of ASIMn - operation mode register
#define cASIMnPWR                         7
#define cASIMnTXE                         6
#define cASIMnRXE                         5
#define cASIMnPS1                         4
#define cASIMnPS0                         3
#define cASIMnCL                          2
#define cASIMnSL                          1
#define cASIMnBit0                        0

// ASISn register bits 2,1,0: PE0, FE0, OVE0
#define cRxStatusMask            0x07
          

#define cStateUndefined                       ((U8)0)
#define cStateRx                              ((U8)1)
#define cStateTx                              ((U8)2)
#define cStateWaitWakeUpPatternInitialState   ((U8)3)
#define cStateWaitWakeUpPatternLowState       ((U8)4)
#define cStateWaitWakeUpPatternHighState      ((U8)5)
#define cStateWaitWakeUpPatternByte           ((U8)6)

// Maximal tolerance is 2 ms

#define cMinLowWakeUpPointNumber              ((U8)2)
#define cMaxLowWakeUpPointNumber              ((U8)4)
#define cMinHighWakeUpPointNumber             ((U8)2)
#define cMaxHighWakeUpPointNumber             ((U8)4)

// HW Protection
#define cNumberBytesScBatDetection            ((U8)3U)
#define cNumberBytesScGndDetection            ((U8)3U)
#define cIndexSubtractCompare                 ((U8)2U)  

//------------------------------------------------------------------------------
// Local macros
//------------------------------------------------------------------------------
  #define mConfigureUARTControl(UARTPort, Value)  mConfigureUARTControl2(UARTPort, Value)
  #define mConfigureUARTControl2(UARTPort, Value) mLDBRegWrite1BitInRegister(ASIM##UARTPort,cASIMnPWR,(Value))

  #define mConfigureUARTInRxMode(UARTPort)        mConfigureUARTInIdleMode(UARTPort);               \
                                                  mConfigureUARTControl(UARTPort,cDisable);   \
                                                  /* wait 2 cpu clock cycles */               \
                                                  mLDBRegNop(); \
                                                  /*//QACJ 3435: akodzhh: there is no side effect*/ \
                                                  /*//QACJ 3456: akodzhh: there is no side effect*/ \
                                                  /*//QACJ 3412: adzhelp: This macro calls another macro*/ \
                                                  mConfigureUARTInRxMode2(UARTPort)

  #define mConfigureUARTInRxMode2(UARTPort)       mConfigureUARTControl(UARTPort,cEnable);   \
                                                  mLDBRegWrite1BitInRegister(ASIM##UARTPort,cASIMnRXE, cEnable);   \
                                                  mLDBIntClearIsrRequestFlag(cLDBHarInterruptKwpRx);  \
                                                  /*//QACJ 3435: akodzhh: there is no side effect*/ \
                                                  /*//QACJ 3412: adzhelp: This macro calls another macro*/ \
                                                  mLDBIntEnableIsr(cLDBHarInterruptKwpRx)

  #define mConfigureUARTInRxModeHwp(UARTPort)     mLDBRegWrite1BitInRegister(ASIM##UARTPort,cASIMnRXE, cEnable);   \
                                                  /*//QACJ 3412: adzhelp: This macro calls another macro*/ \
                                                  mLDBIntClearIsrRequestFlag(cLDBHarInterruptKwpRx)
                                                
  #define mConfigureUARTInTxMode(UARTPort)        mConfigureUARTInTxMode2(UARTPort); \
                                                  /*//QACJ 3412: adzhelp: This macro calls another macro*/ \
                                                  /*//QACJ 3435: adzhelp: Parameter is always const*/ \
                                                  /*//QACJ 3456: adzhelp: Parameter is always const*/ \
                                                  mConfigureUARTInRxModeHwp(UARTPort)  

  #define mConfigureUARTInTxMode2(UARTPort)       mLDBRegWrite1BitInRegister(ASIM##UARTPort,cASIMnTXE, cEnable);   \
                                                  /* wait 2 cpu clock cycles - one is needed */                    \
                                                  mLDBRegNop(); \
                                                  mLDBIntClearIsrRequestFlag(cLDBHarInterruptKwpTx);    \
                                                  /*//QACJ 3412: adzhelp: This macro calls another macro*/ \
                                                  mLDBIntEnableIsr(cLDBHarInterruptKwpTx)
  
  #define mConfigureUARTInIdleMode(UARTPort)      mConfigureUARTInIdleMode2(UARTPort)

  #define mConfigureUARTInIdleMode2(UARTPort)     mLDBIntDisableIsr(cLDBHarInterruptKwpTx);         \
                                                  mLDBIntDisableIsr(cLDBHarInterruptKwpRx);         \
                                                  mLDBRegWrite1BitInRegister(ASIM##UARTPort,cASIMnTXE, cDisable);   \
                                                  /*//QACJ 3435: akodzhh: there is no side effect*/ \
                                                  /*//QACJ 0881: akodzhh: there is no side effect*/ \
                                                  /*//QACJ 3412: adzhelp: This macro calls another macro*/ \
                                                  mLDBRegWrite1BitInRegister(ASIM##UARTPort,cASIMnRXE, cDisable)
                                                  
                                                  
  #define mSetTransfertRate(UARTPort, Value)      mSetTransfertRate2(UARTPort, Value)
  #define mSetTransfertRate2(UARTPort, Value)     mLDBRegWrite8BitRegister(BRGC##UARTPort,Value)
                                                
  #define mSetTransmissionData(UARTPort,Value)    mSetTransmissionData2(UARTPort,Value)
  #define mSetTransmissionData2(UARTPort,Value)   mLDBRegWrite8BitRegister(TXS##UARTPort,Value)
                                                
  #define mReadReceivedData(UARTPort)             mReadReceivedData2(UARTPort)
  #define mReadReceivedData2(UARTPort)            mLDBRegRead8BitRegister(RXB##UARTPort)
                                                
  #define mReadReceivedStatus(UARTPort)           mReadReceivedStatus2(UARTPort)
  #define mReadReceivedStatus2(UARTPort)          (mLDBRegRead8BitRegister(ASIS##UARTPort) & cRxStatusMask)

  #define mSetParity(UARTPort,Value)              mSetParity2(UARTPort,Value)
  #define mSetParity2(UARTPort,Value)            {mLDBRegWrite1BitInRegister(ASIM##UARTPort, cASIMnPS0, (Value)&0x01);\
                                                  /*//QACJ 3435: akodzhh: there is no side effect*/ \
                                                  /*//QACJ 3456: akodzhh: there is no side effect*/ \
                                                  /*//QACJ 0881: akodzhh: there is no side effect*/ \
                                                  mLDBRegWrite1BitInRegister(ASIM##UARTPort, cASIMnPS1, ((Value)>>1)&0x01);}
  
  #define mSetCharacterLength(UARTPort,Value)     mSetCharacterLength2(UARTPort,Value)
  #define mSetCharacterLength2(UARTPort,Value)    mLDBRegWrite1BitInRegister(ASIM##UARTPort, cASIMnCL,  (Value))

  #define mSetStopBitLength(UARTPort,Value)       mSetStopBitLength2(UARTPort,Value)
  #define mSetStopBitLength2(UARTPort,Value)      mLDBRegWrite1BitInRegister(ASIM##UARTPort, cASIMnSL,  (Value))

  #define mSetASIMnBit0(UARTPort,Value)           mSetASIMnBit0_2(UARTPort,Value)
  #define mSetASIMnBit0_2(UARTPort,Value)         mLDBRegWrite1BitInRegister(ASIM##UARTPort, cASIMnBit0,  (Value))

//------------------------------------------------------------------------------
// Local types
//------------------------------------------------------------------------------

// This is an example:
// typedef Expression   tTypeName;

//------------------------------------------------------------------------------
// Local data
//------------------------------------------------------------------------------
static U8 u8UARTBuffer[cUARTBufferLgth];
static U8 u8UARTBufferDataLength;
static U8 u8TransmitDataIndex;
static U8 u8State;
static U8 u8WakeUpPointNumber;
static MEM_FAST tDelay volatile CounterTempo;
static tMsg RxMsg;

// HW protection
static U8 u8ScBatCounter;
static U8 u8ScGndCounter;

//------------------------------------------------------------------------------
// Constant local data
//------------------------------------------------------------------------------

// This is an example:
// static const tType  cConstantName;

//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------

// This is an example:
// Reduce to minimum the usage of extern data members!!!
// tType   LAYCmpVariableName;  //LAY: 3 characters to identify the layer
// tType*  pLAYCmpVariableName; //Cmp: 3-4 characters to identify the component
// U8      u8LAYCmpVariableName;
// U16*    pu16LAYCmpVariableName;

//------------------------------------------------------------------------------
// Constant exported data
//------------------------------------------------------------------------------

// This is an example:
// Reduce to minimum the usage of extern constant data members!!!
// extern const tType  cLAYCmpConstantName;
// extern const U32    cu32LAYCmpConstantName;

//------------------------------------------------------------------------------
// Local function prototypes
//------------------------------------------------------------------------------
static void StartLocalTimeOut(const tDelay DurationP);
static void StopLocalTimeOut(void);
static void LocalTimeOutElapsed(void);
static BOOL DetectShortCircuit (void);

//==============================================================================
//=========================== LOCAL FUNCTIONS ==================================
//==============================================================================

//==============================================================================
//  DESCRIPTION : StartLocalTimeOut (void)
//                Start local timeout
//  
//  PARAMETERS (Type,Name,Min,Max) : duration in cLDBTick 
//
//  RETURN VALUE : none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//==============================================================================
static void StartLocalTimeOut(const tDelay DurationP)
{
    TOSDisableOSInterrupts();

    // Verify that tempo is not currently set
    mLIBassert(CounterTempo == (tDelay)0);

    // Initialize count
    CounterTempo = DurationP + (tDelay)1;  // +1 for ensure that tempo is upper that duree

    mLDBTimEnableTimeOut(LDBKwpCallBackTimer);

    //Adapt PON URD45 DEV 2496 "StopTimer service from LDB_TIM is not protected against real time IT."
    TOSEnableOSInterrupts();
}


//==============================================================================
//  DESCRIPTION         : StopLocalTimeOut 
//                        Stop Local timeout
//  
//  PARAMETERS          : None
//
//  RETURN VALUE        : None
// 
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//==============================================================================
static void StopLocalTimeOut(void)
{
    TOSDisableOSInterrupts();

    mLDBTimDisableTimeOut(LDBKwpCallBackTimer);

    // Clear count
    CounterTempo = (tDelay)0;

    TOSEnableOSInterrupts();
}

//==============================================================================
//  DESCRIPTION : LocalTimeOutElapsed
//  
//  PARAMETERS (Type,Name,Min,Max) : none 
//
//  RETURN VALUE : none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//==============================================================================
static void LocalTimeOutElapsed(void)
{
    // Restart time out
    StartLocalTimeOut((tDelay)(mLDBTimConvUsInTick(cTimeOutPeriodInUs) - 1UL));

    switch(u8State)
    {
    case cStateWaitWakeUpPatternInitialState:
        //QACJ 3325: akodzhh: input state is checked here
        if (mLDBHarRead(cLDBHarRxKwp) == 1) // Initial state detected
        //QACJ 3201: akodzhh: on input state condition
        {
            u8WakeUpPointNumber = 0;
            u8State = cStateWaitWakeUpPatternLowState;
        }
        break;
    case cStateWaitWakeUpPatternLowState:
        // Try to recognize Low u8State
        //QACJ 3346: akodzhh: input state is checked here
        if (mLDBHarRead(cLDBHarRxKwp) == 0) // Count low state
        {
            u8WakeUpPointNumber++;
            if (u8WakeUpPointNumber > cMaxLowWakeUpPointNumber) // Bad low state
            {
                u8State = cStateWaitWakeUpPatternInitialState;
            }
        }
        else  // High level
        //QACJ 3201: akodzhh: on input state condition
        {
            if (u8WakeUpPointNumber < cMinLowWakeUpPointNumber)  
            {
                u8WakeUpPointNumber = 0;
            }
            else  // Good low state
            {
                u8WakeUpPointNumber = 1;  // High state detected
                u8State = cStateWaitWakeUpPatternHighState;
            }
        }
        break;
    case cStateWaitWakeUpPatternHighState:
        //QACJ 3325: akodzhh: input state is checked here
        if (mLDBHarRead(cLDBHarRxKwp) == 1)   // Wait minimum high state duration
        //QACJ 3201: akodzhh: on input state condition
        {
            u8WakeUpPointNumber++;
            if (u8WakeUpPointNumber >= cMinHighWakeUpPointNumber) // Good high WakeUp
            {
                u8UARTBufferDataLength  = 0;
                mConfigureUARTInRxMode(cLDBHarUARTKwp);
                
                u8State = cStateWaitWakeUpPatternByte;
            }
        }
        else  // Bad high state
        {
            u8State = cStateWaitWakeUpPatternInitialState;
        }
        break;
    case cStateWaitWakeUpPatternByte:
        // Wait maximum high state duration
        u8WakeUpPointNumber++;
        if (u8WakeUpPointNumber > cMaxHighWakeUpPointNumber)  // Detect bad high wakeUp pattern
        {
            // Stop reception and return in Initial Wake Up mode detection
            mConfigureUARTInIdleMode(cLDBHarUARTKwp);

            u8State = cStateWaitWakeUpPatternInitialState;
        }
        break;
    case cStateRx:  // Rx time out
        StopLocalTimeOut();  // Automatically ReActivated
        RxMsg.pBuffer           = u8UARTBuffer;
        RxMsg.Lng               = u8UARTBufferDataLength;
        DATKwpCallBackRxSpontWithoutAddr(cLDBCorrect,&RxMsg);
        u8UARTBufferDataLength = 0;
        break;
    default:
        mLIBassert(cFalse);
        break;
    }

}

//==============================================================================
//  DESCRIPTION : Check transmitted byte to detect short circuit
//  
//  PARAMETERS (Type,Name,Min,Max) : none 
//
//  RETURN VALUE : none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//==============================================================================
static BOOL DetectShortCircuit (void)
{
    BOOL bShortCircuitL = cFalse;

    if (u8TransmitDataIndex == (U8)1U)
    {
        // Tx interrupt occurs before own reception finished.
        // Each transmitted byte is checked during next interrupt
        u8ScBatCounter = 0;
        u8ScGndCounter = 0;
    }
    else 
    {
        if (mReadReceivedData(cLDBHarUARTKwp) != u8UARTBuffer[u8TransmitDataIndex - cIndexSubtractCompare])
        {
            //QACJ 3325: adzhelp: Value depends on MCU register
            if ((U8)(mLDBRegRead8BitRegister(ASIS0) & (U8)0x01U) != (U8)0) // Overrun condition
            //QACJ 3201: adzhelp: Value depends on MCU register
            {
                // byte cannot be checked because previous byte is lost
            }
            else
            {
                // difference: there is SC or disturbance
                //QACJ 3325: adzhelp: Value depends on MCU register
                if (mLDBHarRead(cLDBHarRxKwp) != 0)
                //QACJ 3201: adzhelp: Reachability depends on MCU register
                {
                    // SC to BAT occured
                    u8ScBatCounter++;

                #ifdef X90_PROJECT // adzhelp: Add 4 NOPs to preserve original location
                    NOP();NOP();NOP();NOP();
                #endif

                    if (u8ScBatCounter >= cNumberBytesScBatDetection)
                    {
                        // SC to BAT occured
                        bShortCircuitL = cTrue;
                        u8State = cStateUndefined;
                        mConfigureUARTInIdleMode(cLDBHarUARTKwp);
                        DATKwpCallBackTxWithoutAddr(cLDBError);
                    }
                }
                else
                {        
                    // SC to GND occured
                    // No protection needed
                    // Management of GND counter is not needed; kept to preserved original code
                    u8ScGndCounter++;
                    u8ScBatCounter = 0;
        
                #ifdef X90_PROJECT // adzhelp: Add 3 NOPs to preserve original location
                    NOP();NOP();NOP();
                #endif
                }
            }
        }
        else
        {
            // only problems in consequtive bytes are regarded
            u8ScGndCounter = 0;
            u8ScBatCounter = 0;
        }
    }
    return bShortCircuitL;
}

//==============================================================================
//=========================== EXPORTED FUNCTIONS ===============================
//==============================================================================

//==============================================================================
//  DESCRIPTION :void LDBKwpInit(void)
//                Init of the LDB layer
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//==============================================================================
MEM_TYPE void LDBKwpInit(void)
{
    u8State             = cStateUndefined;
    u8WakeUpPointNumber = 0;
    CounterTempo      = 0;

    mSetTransfertRate(cLDBHarUARTKwp,cUARTBaudRateRegValue);

    //QACJ 3109: adzhelp: Empty statement due to macro implementation
    mSetParity(cLDBHarUARTKwp,cNoParity);           
    mSetCharacterLength(cLDBHarUARTKwp,c8Bits);
    mSetStopBitLength(cLDBHarUARTKwp,c1Bit);  
    mSetASIMnBit0(cLDBHarUARTKwp,1);      

    mConfigureUARTControl(cLDBHarUARTKwp,cEnable);

    mLDBHarWrite(cLDBHarTxKwp, 1);
    mLDBHarConfig(cLDBHarTxKwp,cLDBHarOutput);
    mLDBHarConfig(cLDBHarRxKwp,cLDBHarInput);
}


//==============================================================================
//  DESCRIPTION :void LDBKwpSendWithoutAddr(tChannel Channel,tMsg *pMsg )
//                Switching of the send without address access
//  
//  PARAMETERS (Type,Name,Min,Max) :  
//      - Channel: Channel identifier
//      - *pMsg: datas buffer
//
//  RETURN VALUE : none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//==============================================================================
//QACJ 3673: akodzhh: standard interface
//QACJ 1330: akodzhh: standard interface
//QACJ 3227: akodzhh: standard interface
MEM_TYPE void LDBKwpSendWithoutAddr(tMsg *pMsg )
{   
#ifndef TESTU
    mLIBassert(u8State == cStateUndefined);
#endif
    mLIBassert((pMsg !=NULL)&&(pMsg->pBuffer !=NULL));
    mLIBassert((pMsg->Lng !=0) && (pMsg->Lng <cUARTBufferLgth));


#ifdef X90_PROJECT // adzhelp: add 56 NOPs to preserve binary location
    if (mLDBHarRead(cLDBHarRxKwp) == 0) // possible SC GND
    {
        // No protection needed
        NOP(); NOP(); NOP(); NOP(); NOP();
        NOP(); NOP(); NOP(); NOP(); NOP();
        NOP(); NOP(); NOP(); NOP(); NOP();
        NOP(); NOP(); NOP(); NOP(); NOP();
        NOP(); NOP(); NOP(); NOP(); NOP();
        NOP(); NOP(); NOP(); NOP(); NOP();
        NOP(); NOP(); NOP(); NOP(); NOP();
        NOP(); NOP(); NOP(); NOP(); NOP();
        NOP(); NOP(); NOP(); NOP(); NOP();
        NOP(); NOP(); NOP(); NOP(); NOP();
        NOP(); NOP(); NOP(); NOP(); NOP();
        NOP();
    }
#endif

    u8State = cStateTx;
    mLIBmemcpy(u8UARTBuffer,pMsg->pBuffer,pMsg->Lng);
    //QACJ 0506: akodzhh: a correct pointer value is always set in DAT_KWP
    u8UARTBufferDataLength =(U8)pMsg->Lng;

    mConfigureUARTInTxMode(cLDBHarUARTKwp);
    mSetTransmissionData(cLDBHarUARTKwp,u8UARTBuffer[0]);
    u8TransmitDataIndex = 1;
}

//==============================================================================
//  DESCRIPTION :void LDBKwpControl (tCtrl Ctrl)
//                Switching of the control access
//  
//  PARAMETERS (Type,Name,Min,Max) :  
//      - Channel: Channel identifier
//      - Ctrl: Control type
//
//  RETURN VALUE : none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//==============================================================================
MEM_TYPE void LDBKwpControl(tCtrl Ctrl)
{
    switch(Ctrl)
    {
    case cLDBKwpEnableRx:
        mLIBassert(u8State == cStateUndefined);   // WakeUp must have been detected
        u8State = cStateRx;
        u8UARTBufferDataLength = 0;
        mConfigureUARTInRxMode(cLDBHarUARTKwp);
        break;
    case cLDBKwpDisableRx:
        mLIBassert(u8State == cStateRx);
        StopLocalTimeOut();
        u8State = cStateUndefined;
        mConfigureUARTInIdleMode(cLDBHarUARTKwp);
        break;
    case cLDBKwpWaitForWakeUp:
        mLIBassert(u8State == cStateUndefined);
        u8State = cStateWaitWakeUpPatternInitialState;
        StartLocalTimeOut(mLDBTimConvUsInTick(cTimeOutPeriodInUs));
        break;
    case cLDBKwpWaitForStartCom:
        if ((u8State == cStateWaitWakeUpPatternInitialState) ||
            (u8State == cStateWaitWakeUpPatternLowState) )
        {
            u8UARTBufferDataLength  = 0;
            mConfigureUARTInRxMode(cLDBHarUARTKwp);        
            u8State = cStateWaitWakeUpPatternByte;
            Ctrl = cLDBKwpWaitForWakeUp;
        }
        else
        {
            mLIBassert(cFalse);
        }
        break;
    default:
        mLIBassert(cFalse);
        break;
    }
    DATKwpCallBackEndCtrl(Ctrl, cLDBCorrect);
}

//==============================================================================
//  DESCRIPTION : End Tx interrupt
//  
//  PARAMETERS (Type,Name,Min,Max) : none 
//
//  RETURN VALUE : none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//==============================================================================
mLDBIntDeclareIsr(cLDBHarInterruptKwpTx)
{
    mLDBIntEnterIsr(cLDBHarInterruptKwpTx);
    mLIBassert(u8State == cStateTx);

    // HW Protection: checking of transmitted bytes to determine SC
    //QACJ 3416: adzhelp: function has no side effects
    if (DetectShortCircuit() == cFalse)
    {
        if(u8TransmitDataIndex < u8UARTBufferDataLength)
        {
            mSetTransmissionData(cLDBHarUARTKwp,u8UARTBuffer[u8TransmitDataIndex]);
            u8TransmitDataIndex++;
        }
        else
        {
            u8State = cStateUndefined;
            mConfigureUARTInIdleMode(cLDBHarUARTKwp);
            DATKwpCallBackTxWithoutAddr(cLDBCorrect);
        }
    }
    mLDBIntLeaveIsr(cLDBHarInterruptKwpTx);
}

//==============================================================================
//  DESCRIPTION :Byte Rx interrupt
//  
//  PARAMETERS (Type,Name,Min,Max) : none 
//
//  RETURN VALUE : none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//==============================================================================
mLDBIntDeclareIsr(cLDBHarInterruptKwpRx)
{
    mLDBIntEnterIsr(cLDBHarInterruptKwpRx);
    //QACJ 3346: akodzhh: a register value is checked here
    if(mReadReceivedStatus(cLDBHarUARTKwp) == 0)  // Reception Ok
    {
        StopLocalTimeOut();  // Can be preempted because Tempo is stopped

        if (u8State == cStateWaitWakeUpPatternByte)   // WakeUp waiting
        {
            mLIBassert(u8UARTBufferDataLength == 0);
            u8State = cStateRx;                           // To leave WakeUp state
            DATKwpCallBackCtrl(cLDBKwpWakeUp);
        }

        if(u8UARTBufferDataLength < cUARTBufferLgth)
        {
            u8UARTBuffer[u8UARTBufferDataLength] = mReadReceivedData(cLDBHarUARTKwp);
            u8UARTBufferDataLength++;
        }

        StartLocalTimeOut(mLDBTimConvUsInTick(cP1TimeOutInUs));
    }
    else
    //QACJ 3201: akodzhh: on input state condition
    {
        mConfigureUARTInRxMode(cLDBHarUARTKwp);
    }
    
    mLDBIntLeaveIsr(cLDBHarInterruptKwpRx);
}


//==============================================================================
//  DESCRIPTION : LDBKwpCallBackTimer (void)
//                Increment timer counter
//  
//  PARAMETERS (Type,Name,Min,Max) : none 
//
//  RETURN VALUE : none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//==============================================================================
void LDBKwpCallBackTimer(void)
{
    //QACJ 3416: akodzhh: there is no side effects
    if (CounterTempo != (tDelay)0)      // Tempo is set
    {
        CounterTempo--;

        //QACJ 3416: akodzhh: there is no side effects
        if (CounterTempo == (tDelay)0)    // Tempo is elapsed
        {
            LocalTimeOutElapsed();        // Treatment
        }
    }
}


