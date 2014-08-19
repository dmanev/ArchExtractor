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
// Component:    LDB_SLD
//               Solder test component
// -----------------------------------------------------------------------------
// $Date:   Mar 10 2010 16:09:02  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_SLD/LDB_SLD.c-arc  $
// $Revision:   1.2  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_SLD/LDB_SLD.c-arc  $ 
// 
//    Rev 1.2   Mar 10 2010 16:09:02   adzhelp
// Cm006219: Code review corrections - init ADC register
// 
//    Rev 1.1   Feb 17 2010 14:45:50   adzhelp
// Cm006219: SPI type set to '4'. Output only pins retained to '0'.
// 
//    Rev 1.0   Feb 10 2010 10:15:40   adzhelp
// Initial revision.
//
//******************************************************************************

//------------------------------------------------------------------------------
// Body Identification
//------------------------------------------------------------------------------
#define ldb_sld   "ldb_sld"

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------
#ifndef _QAC_
#include "io78f0536_64.h"
#include "intrinsics.h"
#endif

#include "deftypes.h"
#include "lib.h"
#include "ldb_sld.h"
#include "ldb_sldp.h"

#ifdef UTEST
#include "dat.h"
#endif

//------------------------------------------------------------------------------
// Local constants
//------------------------------------------------------------------------------

#define cByteMax        ((U8)0xFFU)

// SPI / CSI (UART)

// CSI registers configuration for SPI mode

// Register CSIM11 - Serial Operation Mode Register
//   transmit/receive mode, MSB first 
#define cCSIM11Init     ((U8)0x40U)
// Register CSI11 - Serial clock selection register
//  SPI Clock type 4, external clock
#define cCSIC11Init     ((U8)0x1FU)

// Note: SPI clock type is 4 for new versions of Solder Control PC SW 

// Timer configuration (used for 'ton' determination) - Timer H1
// TMHMD1 Register: count source fprs / 2^12, interval timer, output disabled
#define cTMH1MDInit  ((U8)0x40U)

// TH1 Register: trigger value
#define cTimerTrigger       mConvMsInTimerTick(cLDBSldTonMs)
#define cTimerTickUs        256UL // Fprs / 2^12

#define cCKSInit            ((U8)0x07U)

#ifdef _QAC_

// adzhelp: exclude message for missing declartion of MCU registers
#pragma PRQA_MESSAGES_OFF 3447 

// Here are written the identifiers of all utilized MCU registers and register bits
extern volatile U8 P0, P1, P2, P3, P4, P5, P6, P7, P12, P12, P14,
                  PM0, PM1, PM2, PM3, PM4, PM5, PM6, PM7, PM12, PM14, ADPC,
                  CSIE11, TMHMD1, WDTE, CSIM11, CSIMK11, SOTB11, SIO11, CLOE;

#pragma PRQA_MESSAGES_ON 3447

#endif


//------------------------------------------------------------------------------
// Local macros
//------------------------------------------------------------------------------
// Test pin
#define mIsTestPinEnterActive() (cLDBSldBitTestSolderPin == (U8)cLDBSldBitTestSolderPinEnterLevel)
#define mIsTestPinActive()      (cLDBSldBitTestSolderPin != (U8)cLDBSldBitTestSolderPinSleepLevel)
#define mIsTestPinSleep()       (cLDBSldBitTestSolderPin == (U8)cLDBSldBitTestSolderPinSleepLevel)

// SPI
#ifndef _QAC_
#define mInitSpi()              CSIM11 = cCSIM11Init; \
                                CSIC11 = cCSIC11Init; \
                                P0_bit.no2 = 0 /* SPI OUT */

#define mInitClockOutput()      CKS = cCKSInit; \
                                P14_bit.no0 = 0 /* CLOCK OUT */
#endif


#define mEnableSpi()            CSIMK11 = 1; /* disable interrupt */\
                                /*//QACJ 3412: adzhelp: Missing statement is appended on use */\
                                CSIE11 = 1

#define mSendSpi(Data)          (SOTB11 = (U8)(Data))
#define mReceiveSpi()           (SIO11)

#define mEnableClockOutput()    (CLOE = 1)

#ifndef _QAC_

#define mIsCommunicationInProgress()    (CSIM11_bit.no0 == 1) // CSOT11 bit

// Timer control
    #define mInitTimer()        TMHMD1 = cTMH1MDInit; \
                                CMP01 = cTimerTrigger

    #define mStartTimer()       TMMKH1 = 1; /* disable interrupt */\
                                TMHE1 = 1

    #define mIsTimerElapsed()   (TMIFH1 == 1)

#else
    #define mIsCommunicationInProgress()    (CSIM11 == 1)

    #define mInitTimer()        NOP()
    #define mStartTimer()       NOP()
    #define mInitSpi()          NOP()
    #define mInitClockOutput()  NOP()
    #define mIsTimerElapsed()   (TMHMD1 == 0)
#endif

#define mConvMsInTimerTick(PeriodMs) \
    ((((PeriodMs) * 1000UL) / cTimerTickUs) - 1UL)

#define mRefreshWatchdog()      (WDTE = (U8)0xACU)

// Set to main port mode for all pins (important for NEC K0)
#define mSetPortFunction()      (ADPC = (U8)0x08U) // P2 pins set to port function

//------------------------------------------------------------------------------
// Local types
//------------------------------------------------------------------------------
typedef volatile U8 * const tpRegister;

//------------------------------------------------------------------------------
// Local data
//------------------------------------------------------------------------------
static tpRegister pPortRegisters[cLDBSldPortsNumber] = cLDBSldPortRegistersList();
static tpRegister pPortDirRegisters[cLDBSldPortsNumber] = cLDBSldPortDirRegistersList();

//------------------------------------------------------------------------------
// Constant local data
//------------------------------------------------------------------------------
#if (cLDBSldTestCommunications == 0)
static const U8 InputOnlyPins[cLDBSldPortsNumber] = cLDBSldPortInputOnlyPinsList();
#endif

static const U8 OutputOnlyPins[cLDBSldPortsNumber] = cLDBSldPortOutputOnlyPinsList();

//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------

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
static MEM_TYPE BOOL CheckSolderModeEntry(void);
static MEM_TYPE void SldInit(void);
static MEM_TYPE void SolderTestProcedure(void);
static MEM_TYPE void SetPortDirection(const U8 u8PortNum, const U8 u8Dir);
static MEM_TYPE U8   SpiProcess (const U8 u8TxData);

//==============================================================================
//=========================== LOCAL FUNCTIONS ==================================
//==============================================================================

//==============================================================================
// DESCRIPTION:         Check if entry into solder test mode is requested
//
// PARAMETERS:          None
//
// RETURN VALUE:        BOOL: cTrue when requested entry into solder mode
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
static MEM_TYPE BOOL CheckSolderModeEntry(void)
{
    BOOL bResult = cFalse;

    //QACJ 3416: No side effects
    if (mIsTestPinEnterActive())
    {
        // Wait for time 'ton'        
        mInitTimer();
        mStartTimer();
        
        //QACJ 3416: No side effects
        while (!mIsTimerElapsed())
        {
            //QACJ 3416: No side effects
            if (!mIsTestPinEnterActive()) // pin level shall be maintained
            {
                bResult = cFalse;
                break;
            }
            else
            {
                // wait
                mRefreshWatchdog();
            }
        //QACJ 2468: control variable is being changed by HW timer
        }
        
        //QACJ 3416: No side effects
        if (mIsTestPinEnterActive()) 
        {
            bResult = cTrue; // enable solder test mode
        }        
    }    
    return bResult;
}

//==============================================================================
// DESCRIPTION:         Component initialization
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
static MEM_TYPE void SldInit(void)
{
    U8 i;

#if (cLDBSldBitTestSolderPinEnterLevel == 0U)
    // when entry is performed with low level of control pin
        
    while (mIsTestPinActive())
    {
        // wait for rising edge
        mRefreshWatchdog();
    }    
#endif

    // Set to main port mode for all pins (important for NEC K0)
    mSetPortFunction();

    // Initial port direction configuration
    for (i = 0; i < cLDBSldPortsNumber; ++i)
    {
        // set all ports inputs except output only
        SetPortDirection(i, ((U8)cByteMax) & ((U8)~OutputOnlyPins[i]));
    }
    
    // Init SPI registers
    mInitSpi();
    mEnableSpi();

    // Enable clock output
    mInitClockOutput();
    mEnableClockOutput();
}

//==============================================================================
// DESCRIPTION:         Transmit and receive a byte via SPI
//
// PARAMETERS:          U8 u8TxData: byte to transmit
//
// RETURN VALUE:        U8: received byte
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
static MEM_TYPE U8 SpiProcess (const U8 u8TxData)
{
    U8 u8RxData;

    //QACJ 3416: No side effects
    while (mIsCommunicationInProgress())
    {
        // wait until transmit buffer empty
        mRefreshWatchdog();
        //QACJ 2468: adzhelp: control variable is a register bit
    }
    mSendSpi(u8TxData);

    //QACJ 3416: No side effects
    while (mIsCommunicationInProgress()) // is here an incoming data: receive complete
    {
        // wait until receive buffer full
        mRefreshWatchdog();
        //QACJ 2468: adzhelp: control variable is a register bit
    }
    u8RxData = mReceiveSpi();	

    return u8RxData;
}

//==============================================================================
// DESCRIPTION:         Set port direction register
//
// PARAMETERS:          U8 u8PortNum: port number; U8 u8Dir: direction bits
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
static MEM_TYPE void SetPortDirection(const U8 u8PortNum, const U8 u8Dir)
{
    if (u8PortNum < cLDBSldPortsNumber)    
    {
#if (cLDBSldPortOutputValue != 0)
        // '0' is output acc. to solder test specification
        // INVERSE is required for MCU direction registers
        *(pPortDirRegisters[u8PortNum]) = (U8)(~u8Dir); 
#else
        *(pPortDirRegisters[u8PortNum]) = u8Dir;
#endif
    }
}

//==============================================================================
// DESCRIPTION:         Solder test procedure
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
static MEM_TYPE void SolderTestProcedure(void)
{
    U8 i;
    U8 PortWrite[cLDBSldPortsNumber];  // wanted states of ports
    U8 PortRead[cLDBSldPortsNumber];   // read states of ports
    U8 PortDir[cLDBSldPortsNumber];    // wanted direction of ports 
                                          // (bit 0 - output, bit 1 - input)

    // Initial port read
    for (i = 0; i < cLDBSldPortsNumber; ++i)
    {
    #if (cLDBSldTestCommunications == 1) // Test Mode enabled
        PortRead[i] = 0xA0U + i; // return known values in first frame
    #else
        // Read ports
        PortRead[i] = *(pPortRegisters[i]);
    #endif
    }   
   
    
    // Solder test procedure endless loop
    for (;;)
    {
        // SPI transfer

        for (i = 0; i < cLDBSldPortsNumber; ++i)
        {            
            // receive direction / send broadcasting index
            PortDir[i] = SpiProcess(i + 1);   
            // receive wanted port states / send previously read port states
            
            PortWrite[i] = SpiProcess(PortRead[i]);
        }

        //QACJ 3416: No side effects
        while (mIsTestPinSleep())
        {
            // wait for falling edge
            mRefreshWatchdog();
            //QACJ 2468: adzhelp: control variable is a register bit
        }

#if (cLDBSldTestCommunications == 1) // Test Mode enabled
        
        for (i = 0; i < cLDBSldPortsNumber; ++i)
        {
            // Read
            PortRead[i] = PortWrite[i]; // prepare to return values received by tester       
            PortDir[i] = PortDir[i]; // remove warning
        }

#else // normal mode

        for (i = 0; i < cLDBSldPortsNumber; ++i)
        {
            // Read
            PortRead[i] = *(pPortRegisters[i]);
        }

        for (i = 0; i < cLDBSldPortsNumber; ++i)
        {
            // Write
            // For NEC K0 - output only pins' latches should be fixed to certain values
            // These values are '0':
            *(pPortRegisters[i]) = PortWrite[i] & ((U8)~OutputOnlyPins[i]);

            // Change direction
            SetPortDirection(i, ((InputOnlyPins[i]) | 
                                 ((PortDir[i]) & ((U8)~OutputOnlyPins[i]))));
        }
#endif

        //QACJ 3416: No side effects
        while (mIsTestPinActive())
        {
            // wait for rising edge
            mRefreshWatchdog();
            //QACJ 2468: adzhelp: control variable is a register bit
        }   
    }  
}

//==============================================================================
//=========================== EXPORTED FUNCTIONS ===============================
//==============================================================================

//==============================================================================
// DESCRIPTION:         Enters into solder test mode depending on the test pin
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
MEM_TYPE void LDBSldEnterSolderTest(void)
{
    const BOOL bCheck = CheckSolderModeEntry();

    if (bCheck != cFalse)
    {
        SldInit();
        SolderTestProcedure();
    }
}

