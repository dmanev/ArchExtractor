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
// Component:    LDB_SUP
// -----------------------------------------------------------------------------
// $Date:   Feb 10 2010 09:18:16  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_SUP/LDB_SUP.C-arc  $
// $Revision:   1.6  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_SUP/LDB_SUP.C-arc   $
// 
//    Rev 1.6   Feb 10 2010 09:18:16   adzhelp
// Cm006219: Check for solder control mode entry
// 
//    Rev 1.5   Apr 27 2009 15:45:02   adzhelp
// Cm003265: Implementaion of sleep mode management for RF
// 
//    Rev 1.4   Apr 17 2009 15:26:54   adzhelp
// Cm003276: Corrections after target integration test:
// Memory configuration registers inited at the beginning
// 
//    Rev 1.3   Apr 16 2009 14:27:56   adzhelp
// Cm003276: Integration test changes
// 
//    Rev 1.2   Apr 16 2009 10:47:54   adzhelp
// Cm003276: Implementation of sleep mode management
// 
//    Rev 1.1   Mar 20 2009 14:48:48   adzhelp
// Cm003619: Parameterization of LDB_SUP according to HSI and MCU 78F0536
// 
//    Rev 1.0   04 Feb 2009 17:03:18   adzhelp
// Initial revision.
//******************************************************************************

/*--------------------------------------------------------------------------
  Body Identification
  --------------------------------------------------------------------------*/

#define LDB_SUP   "LDB_SUP"

/*-------------------------------------------------------------------------
  Included files

  #include <system_file_name.h>
  #include "project_file_name.h"
  --------------------------------------------------------------------------*/

#include "lib.h"
#include "TOS.h"
#include "ldb_tos.h"
#include "ldb_reg.h"
#include "ldb_int.h"
#include "ldb_tim.h"
#include "ldb_rf.h"
#include "ldb_sld.h"
#include "ldb_sup.h"


/*--------------------------------------------------------------------------
  Local constants

  #define cConstantName   ((tType) ConstantValue)
  --------------------------------------------------------------------------*/
#define cRefreshWatchdogValue       (U8)0xACU

// External RAM parameters
#define cExtRamAddressBegin         (U16)0xE800U // value for 78K0_F0536
#define cExtRamAddressEnd           (U16)0xF7FFU
#pragma segment="NEAR_Z" // last segment in Ext RAM that needs to be initialized
#define cExtRamAddressRealEnd       (U16)(__segment_end("NEAR_Z")) // end address + 1

#define cIMSRegInit                 (U8)0xCCU  // value for 78K0_F0536
#define cIXSRegInit                 (U8)0x04U  // value for 78K0_F0536

#define cOSTSRegInit                (U8)0x01U  // 128 uS oscillator stabilization time
                                               // (T = 2^13/fx)
#define cOSTCRegCompare             (U8)0x10U  // Compare value corresponding to cOSTSRegInit

// Sleep refresh period in LDB ticks
#define cSleepRefreshPeriod         (U8)2U // 40 ms

/*--------------------------------------------------------------------------
  Local macros

  #define mMacroName   (MacroDefinition)
  --------------------------------------------------------------------------*/
#define mHalt() _ASM("HALT"); \
                _ASM("NOP" ); \
                _ASM("NOP" )  
#define mStop() _ASM("STOP"); \
                _ASM("NOP" ); \
                _ASM("NOP" )  

// Disable active HW modules in MCU requiring peripheral clock
#define mDisableActiveHw() \
    { \
        mLIBassert(bClockForActiveModeSelected != cFalse); \
        bLDBSupActivatedHw = cFalse; \
        LDBAnaControl(cLDBAnaStopHW); \
        /* mDisableRfHw(); */ \
    }

// Enable HW modules in MCU requiring peripheral clock
#define mEnableActiveHw() \
    { \
        mLIBassert(bClockForActiveModeSelected != cFalse); \
        bLDBSupActivatedHw = cTrue; \
        LDBAnaControl(cLDBAnaStartHW); \
    }
// Enable RF HW
#ifdef MEASURE_RF_STROBE_DURATION
#define mEnableRfHw() \
    mLDBHarWrite(cLDBHarPort1_3, 1); \
    LDBRfControl(cLDBRfActivateStrobe)
#else
#define mEnableRfHw() \
    LDBRfControl(cLDBRfActivateStrobe)
#endif
// Disable RF HW
#define mDisableRfHw() LDBRfControl(cLDBRfDeactivateStrobe)


// Specific wake-up conditions
#define mIsKLineWakeUp() (mLDBHarRead(cLDBHarRxKwp) == 0) // possible K-Line wake-up

#define mIsWakeupDetectionStarted() (bWakeUpDetectionPinStarted != cFalse)
#define mInformWakeupDetectionStarted() \
    /* clear flag for wakeup detection */ \
    bWakeUpDetectionPinStarted = cFalse; \
    /* allow DAT layer to use ADC converter */ \
    bAnalogConversionAllowed = cTrue;
#define mInformWakeupDetectionStopped() \
    /* forbid DAT layer to use ADC converter */ \
    bAnalogConversionAllowed = cFalse;

// Uncomment following line to enable integration test of sleep mode
//#define TEST_INTEGRATION_SLEEP_MODE

#ifdef TEST_INTEGRATION_SLEEP_MODE
// Connect an oscilloscope to PIN#44
#define mStartWakeupScopeTrace() mLDBHarWrite(cLDBHarPort1_2, 1)
#define mStopWakeupScopeTrace()  mLDBHarWrite(cLDBHarPort1_2, 0)
#else
#define mStartWakeupScopeTrace()
#define mStopWakeupScopeTrace()
#endif

/*--------------------------------------------------------------------------
  Local types

  struct  sStructureName { ... };
  union   uUnionName { ... };
  enum    eEnumerationName { ... };
  typedef Expression tTypeName;
  --------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------
  Local data

  static  tType   VariableName;
  static  tType*  pVariableName; 
  --------------------------------------------------------------------------*/
static BOOL bSleepMode;
static volatile tDelay SleepTimerDelay;
static BOOL bWakeUpDetectionPinStarted;
static BOOL bClockForActiveModeSelected;
static BOOL bAnalogConversionAllowed;

/*--------------------------------------------------------------------------
  Constant local data

  static const tType  VariableName;
  --------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------
  Exported data

  tType   CMPVariableName;      (CMP: 3 characters to identify this component)
  tType*  pCMPVariableName;     (CMP: 3 characters to identify this component)
  --------------------------------------------------------------------------*/
BOOL bLDBSupActivatedHw;

/*--------------------------------------------------------------------------
  Constant exported data
 
  const tType   CMPVariableName;(CMP: 3 characters to identify this component)
  --------------------------------------------------------------------------*/
// OPTION BYTE
#pragma constseg=OPTBYTE
__root const U8 LDBHarOptionBytes[5]= 
{ 
    /* @0080 */ 0x7BU, // Window 100%, watchdog enabled, T = 124.12 ms, oscillator cannot be stopped
    /* @0081 */ 0x00U, // default POC mode
    /* @0082 */ 0x00U, // reserved
    /* @0083 */ 0x00U, // reserved
    /* @0084 */ 0x00U  // no on-chip debug
};
#pragma constseg=default


/*--------------------------------------------------------------------------
  Local function prototypes
  
  static tTypeRetour FunctionName(tTypeArgument1 ArgumentName1, ... );
  --------------------------------------------------------------------------*/
static void ConfigureClockForActiveMode(void);
static void ConfigureClockForSleepMode(void);

/*============================================================================
  =========================== LOCAL FUNCTIONS ================================
  ==========================================================================*/

/*============================================================================
  DESCRIPTION :
  
  PARAMETERS (Type,Name,Min,Max) :   none

  RETURN VALUE :   none
 
  DESIGN INFORMATION :   refer to Detailed Design Document
  ==========================================================================*/
static void ConfigureClockForActiveMode(void)
{
    bClockForActiveModeSelected = cTrue;

    /* Operation Mode Select */
    mLIBassert(mLDBRegRead1BitInRegister(MOC, 7) == 1U); /* X1 should be stopped */
    mLDBRegWrite8BitRegister(OSCCTL, (U8)0x41U); /* X1 oscillator enabled, fxh > 10 MHz */
    /* Main OSC control - high system clock X1 */
    mLDBRegWrite1BitInRegister(MOC, 7, 0); /* X1 oscillator operating (@16 MHz) */

    while (mLDBRegRead8BitRegister(OSTC) < cOSTCRegCompare)
    {
        /* Wait for X1 oscillator stabilization */
    }
    /* Main clock mode */
    mLDBRegWrite8BitRegister(MCM, (U8)0x07U); /* main clock and peripheral clock set to high-speed clock */
    /* Internal oscillation */
    mLDBRegWrite8BitRegister(RCM, (U8)0x01U);  /* Internal oscillators: low-speed enabled; high speed disabled */
}

/*============================================================================
  DESCRIPTION :
  
  PARAMETERS (Type,Name,Min,Max) :   none

  RETURN VALUE :   none
 
  DESIGN INFORMATION :   refer to Detailed Design Document
  ==========================================================================*/
static void ConfigureClockForSleepMode(void)
{
    bClockForActiveModeSelected = cFalse;

    /* Internal oscillation */
    mLDBRegWrite8BitRegister(RCM, (U8)0x00U);  /*  Internal oscillators: low-speed enabled; high speed enabed */

    while (mLDBRegRead1BitInRegister(RCM, 7) == 0)
    {
        /* Wait for internal high speed oscillator stabilization */
    }
    /* Main clock mode */
    mLDBRegWrite8BitRegister(MCM, (U8)0x00U); /* main clock and peripheral clock set to internal high-speed clock */
    /* Main OSC control - high system clock X1 */
    mLDBRegWrite1BitInRegister(MOC, 7, 1); /* X1 oscillator stopped */
    /* Operation Mode Select */
    mLDBRegWrite8BitRegister(OSCCTL, (U8)0x00U); /* X1 oscillator disabled */
}

/*============================================================================
  =========================== EXPORTED FUNCTIONS =============================
  ==========================================================================*/

/*============================================================================
  DESCRIPTION :
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void LDBRefreshWatchDog(void)
{
    mLDBRegWrite8BitRegister(WDTE, cRefreshWatchdogValue);
}

/*============================================================================
  DESCRIPTION :
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void LDBReset(void)
{
    _DI();
    while(1) {}
}

/*============================================================================
  DESCRIPTION :
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void main(void)
{
    // Initialisation du CPU
    //----------------------

    // Memory configuration: must be confured first!
    mLDBRegWrite8BitRegister(IMS, cIMSRegInit);   // Memory size switching register
    mLDBRegWrite8BitRegister(IXS, cIXSRegInit);   // Expansion RAM switching register
  
    // Clock configuration
    
    // Select oscillation stabilization time
    mLDBRegWrite8BitRegister(OSTS, cOSTSRegInit);
    // Processor clock control
    mLDBRegWrite8BitRegister(PCC, (U8)0x00U);   // Set fcpu = fxp, main system clock

    // Set configuration for active mode
    ConfigureClockForActiveMode();

    //Uncomment following lines if CLKOUT pin has to be enabled:
    //mLDBHarConfig(cLDBHarPort14_0, cLDBHarOutput); 
    //CLOE = 1;
  
    // Initialisation du WatchDog Timer
    //---------------------------------
  
    // Watchdog of 78K0_F0536 can generate reset only
    // There is no dedicated watchdog interrupt
    // Configuration of watchdog is done in option byte in LDB_HAR

    
	// initialize internal expansion RAM: only occupied segments
    mLIBmemset((U16*)cExtRamAddressBegin, 0,
        (cExtRamAddressRealEnd - cExtRamAddressBegin));
    
    // Internal Init
    // initialize variables
    bSleepMode = cFalse;
    bClockForActiveModeSelected = cTrue;

    LDBSldEnterSolderTest();

    TOSStart(0); 
}

/*============================================================================
  DESCRIPTION :
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void LDBWaitForCallBack( void )
{
    if (bSleepMode != cFalse)
    {
        if (mLDBRfIsWakeUpDetectionFinished())
        {
            if (bClockForActiveModeSelected != cFalse) 
            {
                // Idle task can be called before tasks detecting wake-up
                // therefore check if detection is started
                mDisableActiveHw();
                ConfigureClockForSleepMode();
            } 
            if (mIsWakeupDetectionStarted())
            {
                mInformWakeupDetectionStopped();
                mStopWakeupScopeTrace();
                mStop();
                mStartWakeupScopeTrace();
            }
        }
    }
}

/*============================================================================
  DESCRIPTION :
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void LDBSupEnterSleepMode( void )
{
    if (bSleepMode == cFalse)
    {
        bSleepMode = cTrue;
        mLDBTimStopFastTimer();
        SleepTimerDelay = (tDelay)cSleepRefreshPeriod;            
        mDisableActiveHw();
        LDBDinControl(cLDBDinInitiateKLineWakeupConditions);
        mInformWakeupDetectionStarted();
        ConfigureClockForSleepMode();
        mLDBTimStartSlowTimer();
    }
}

/*============================================================================
  DESCRIPTION :
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void LDBSupLeaveSleepMode( void )
{
    if (bSleepMode != cFalse)
    {
        bSleepMode = cFalse;
        SleepTimerDelay = 0;
        LDBTimStopSlowTimer();
        if (bClockForActiveModeSelected == cFalse)
        {
            ConfigureClockForActiveMode();
            mEnableActiveHw();
        }
        mLDBTimStartFastTimer();
    }
}

/*============================================================================
  DESCRIPTION :
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void LDBSupCallBackSleepTimer(void)
{
    if (SleepTimerDelay > 0)
    {
        LDBDinControl(cLDBDinCheckKLineWakeupConditions);

        SleepTimerDelay--;        
        if (SleepTimerDelay == 0)
        {
            // Start of periodical wakeup detection procedure
            SleepTimerDelay = (tDelay)cSleepRefreshPeriod;
            if (mLDBRfIsWakeUpDetectionFinished() != cFalse)
            {
                mEnableRfHw(); // RF HW can be enabled without peripheral clock
                ConfigureClockForActiveMode();
                mEnableActiveHw();
            }
            else
            {
                // RF has not yet finished detection 
            }
            mInformWakeupDetectionStarted();
        }
    }
}

/*============================================================================
  DESCRIPTION :
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void LDBSupReceiveWithoutAddr(tMsg * const Msg)
{
    if (Msg != NULL)
    {
        mLIBassert(Msg->Lng == cLDBSupMessageLength);

        Msg->pBuffer[cLDBSupClockForActiveModeSelectedIndex] = 
            bClockForActiveModeSelected;
        Msg->pBuffer[cLDBSupAnalogConversionAllowedIndex] = 
            bAnalogConversionAllowed;
    }    
}

/*============================================================================
  DESCRIPTION :
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void LDBSupControl(const tCtrl Ctrl)
{
    switch (Ctrl)
    {
    case cLDBSupWakeUpDetectionPinStarted:
        bWakeUpDetectionPinStarted = cTrue;
        break;
    case cLDBSupSynchronizeSleepTimer:
        SleepTimerDelay = (tDelay)cSleepRefreshPeriod;
        break;
    default:
        mLIBassert(cFalse);
    }
}
