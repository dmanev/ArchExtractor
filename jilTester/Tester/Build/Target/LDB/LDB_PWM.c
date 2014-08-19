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
// Component:    LDB_PWM
// -----------------------------------------------------------------------------
// $Date:   Oct 08 2009 18:26:50  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_PWM/LDB_PWM.c-arc  $
// $Revision:   1.4  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_PWM/LDB_PWM.c-arc  $
// 
//    Rev 1.4   Oct 08 2009 18:26:50   adzhelp
// Cm006468: Correct order of enable of flag controling interrupt
// 
//    Rev 1.3   Aug 18 2009 09:26:58   adzhelp
// Cm005205: Corrected problem on switching to 0%
// 
//    Rev 1.2   Jul 01 2009 09:57:54   adzhelp
// Cm005205: Corrected problem on switching between 100% -> 95% PWM
// 
//    Rev 1.1   Jun 30 2009 14:27:10   adzhelp
// Cm005205: Updates after integration test and unit test
// 
//    Rev 1.0   Jun 23 2009 15:26:22   amarinm1
// Initial revision.
//
//******************************************************************************
#endif

//------------------------------------------------------------------------------
// Body Identification
//------------------------------------------------------------------------------
#define ldb_pwm   "ldb_pwm"

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------
#include "ldb_reg.h"
#include "ldb_har.h"
#include "ldb_ioc.h"
#include "ldb_int.h"
#include "ldb_pwm.h"
#include "dat_pwmp.h"


//------------------------------------------------------------------------------
// Local constants
//------------------------------------------------------------------------------

// length of DAT buffer to LDB in bytes
#define cDatMessageLength       ((U16)3)

#define cMaxRatio               (U8)100
#define cu8RatioDivider         (U8)4

#define cTimerTrigger           ((U8)((cLDBHarPwmTimerPeriodInNs / cLDBHarTickInNsPwmTimer) - 1UL))  // N=23

//------------------------------------------------------------------------------
// Local macros
//------------------------------------------------------------------------------
// Set PWM duty cycle
// CMP11 = duty cycle / 4 - 1
// It is important that values 0 ... 3 are preset to 0 and 96...99 are preset to 100
#define mSetPwmDutyCycle(DutyCycle) \
{ \
    U8 RegDutyCycleValue = (((U8)(DutyCycle) / cu8RatioDivider) - 1); \
    mLIBassert(RegDutyCycleValue < cTimerTrigger); /* M = 0...N-1 */\
    mLDBIocSetPwmDutyCycle(cLDBHarPwmTimer, RegDutyCycleValue); \
}

//------------------------------------------------------------------------------
// Local types
//------------------------------------------------------------------------------

// This is an example:
// typedef Expression   tTypeName;

//------------------------------------------------------------------------------
// Local data
//------------------------------------------------------------------------------
static U8 u8OldPwmRatio;
static BOOL bKeepOutputActive;

//------------------------------------------------------------------------------
// Constant local data
//------------------------------------------------------------------------------

// This is an example:
// static const tType  cConstantName;

//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------
BOOL bPwmIsFadingControlRequested;

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


//==============================================================================
//=========================== LOCAL FUNCTIONS ==================================
//==============================================================================


//==============================================================================
//=========================== EXPORTED FUNCTIONS ===============================
//==============================================================================

//==============================================================================
// DESCRIPTION:         Initialization of PWM channel
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
MEM_TYPE void LDBPwmInit( void )
{
    mLDBHarWrite(cLDBHarILLOutput, 0);
    mLDBHarConfig(cLDBHarILLOutput, cLDBHarOutput);
    u8OldPwmRatio = 0;
    bPwmIsFadingControlRequested = cFalse;
    bKeepOutputActive = cFalse;
}


//==============================================================================
// DESCRIPTION:         Leave sleep mode of PWM channel
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
MEM_TYPE void LDBPwmLeaveSleepMode( void )
{
    mLDBHarWrite(cLDBHarILLOutput, 0);

    // Initialization of Internal Lights output (Timer H1)

    // 1.Clear interrupt flag
    //QACJ 3141: adzhelp: Warning comes from STK macro
    mLDBIntClearIsrRequestFlag(cLDBHarPwmTimerIt);

#ifdef X90_PROJECT
    mLDBIntGetInterruptTMH1(cLDBIntTrpPwmOwnerTMH1);
#endif
    
    // 2. Enable interrupt
    //QACJ 3141: adzhelp: Warning comes from STK macro
    mLDBIntEnableIsr(cLDBHarPwmTimerIt);
    
    // 3. Select PWM mode (TMMD10 = 0; TMMD11 = 1)
    mLDBIocSetPWMMode(cLDBHarPwmTimer);

    // 5.Select input clock fPRS/2^12 = 3906.25Hz (CKS10 = 0; CKS11 = 0; CKS12 = 1)
    //QACJ 3109: adzhelp: Warning comes from STK macro
    mLDBIocSelectClock(cLDBHarPwmTimer, cLDBHarPwmTimerPrescaler);

    // 6. Write trigger
    //QACJ 0434: adzhelp: CMP01 is a MCU register identifier
    //QACJ 3892: adzhelp: CMP01 is 8 bits like cTimerTrigger
    mLDBIocWriteTrigger(cLDBHarPwmTimerTrigger, cTimerTrigger);

    // 7. Prepare output
    mLDBIocSetActiveLevel(cLDBHarPwmTimer, High);
    mLDBIocPWMOutputDisable(cLDBHarPwmTimer);

    // 8. Start timer
    mLDBIocStartTimer(cLDBHarPwmTimer);

    u8OldPwmRatio = 0;
    bPwmIsFadingControlRequested = cFalse;
    bKeepOutputActive = cFalse;
}


//==============================================================================
// DESCRIPTION:         Enter sleep mode of PWM channel
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
MEM_TYPE void LDBPwmEnterSleepMode( void )
{
    mLDBHarWrite(cLDBHarILLOutput, 0);
    mLDBHarConfig(cLDBHarILLOutput, cLDBHarOutput);
    
    // Disable of Timer H1

    // 1.Disable interrupt
    //QACJ 3141: adzhelp: Warning comes from STK macro
    mLDBIntDisableIsr(cLDBHarPwmTimerIt);
    
    // 2.Stop count operation before setting other registers (TMHE1 = 0)
    mLDBIocStopTimer(cLDBHarPwmTimer);

    // 3.Disable the output (TOEN1 = 0)
    mLDBIocPWMOutputDisable(cLDBHarPwmTimer);

#ifdef X90_PROJECT
    mLDBIntReleaseInterruptTMH1(cLDBIntTrpPwmOwnerTMH1);
#endif
}


//==============================================================================
// DESCRIPTION:         Send with address of PWM channl
//
// PARAMETERS:          tAddress AddrP - Address of PWM output, 
//                      tMsg pMsgP - Message of type tDATPwmStruct containg duty cycle (ratio)
//                      Freq is not used
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
MEM_TYPE void LDBPwmSendWithAddr( const tAddress AddrP, const tMsg * const pMsgP )
{
    tDATPwmStruct * pPwmConfigL;    
    U8 u8Ratio;
    
    // Verify the validity of the message
    mLIBassert(pMsgP          != NULL);
    mLIBassert(pMsgP->pBuffer != NULL);
    mLIBassert(pMsgP->Lng     == cDatMessageLength);
    
  
    //QACJ 0310: amarinm1: This is the original pointer type in DAT_PWM.c 
    //QACJ 3305: amarinm1: This is the original pointer type in DAT_PWM.c 
    //QACJ 0506: amarinm1: It is checked for NULL value in the assert above.
    pPwmConfigL = (tDATPwmStruct *)pMsgP->pBuffer;
    u8Ratio =(U8)(pPwmConfigL->Ratio);

    // Verify the validity of the Cyclic ratio
    mLIBassert(u8Ratio <= cMaxRatio);


    switch(AddrP)
    {
        case (tAddress)cPWM_ROOMLAMP_ID:
        if (u8OldPwmRatio == u8Ratio)
        {
            // no change, do nothing
        }
        else if (u8Ratio == cMaxRatio)
        {
            mLDBHarWrite(cLDBHarILLOutput, 1); // According to Figure 9-2. Block Diagram of 8-Bit Timer H1 (MCU Manual)
            // When P16 = 1 then output is always 1 (logical OR)
            u8OldPwmRatio = cMaxRatio;
        }
        else if (u8Ratio == 0)
        {
            u8OldPwmRatio = 0; // old value to be set before fading control requested
            mLDBHarWrite(cLDBHarILLOutput, 0); // restore output latch
            
            // Disable output immediately in order to prevent short parasitic pulse
            // Such pulse appears when timer output is disabled after interrupt request
            mLDBHarConfig(cLDBHarILLOutput, cLDBHarInput);  // safe when level on output is low
            bPwmIsFadingControlRequested = cTrue;
        }
        else // Ratio between 0 and 100
        {
            if ((u8OldPwmRatio == 0) || (u8OldPwmRatio == cMaxRatio))
            {
                u8OldPwmRatio = u8Ratio; // old value to be set before fading control requested
                // Update the duty cycle
                // NOTE: update of CMP11 during counter operation is not
                // taken into account until previous value has been reached 
                // by the clock counter. Also, even if the value is reached 
                // at the moment of writing, it takes at least 3 clock
                // cycles to update the register.
                //QACJ 3205: adzhelp: RegDutyCycleValue is used in STK macro
                //QACJ 3220: adzhelp: Macro implementation contains block declaration                
                //QACJ 3109: adzhelp: Warning comes from STK macro
                mSetPwmDutyCycle(u8Ratio);
                bPwmIsFadingControlRequested = cTrue;
            }
            else
            {
                // Only duty cycle needs to be updated
                u8OldPwmRatio = u8Ratio;
                // Update the duty cycle
                //QACJ 3205: adzhelp: RegDutyCycleValue is used in STK macro
                //QACJ 3220: adzhelp: Macro implementation contains block declaration                
                //QACJ 3109: adzhelp: Warning comes from STK macro
                mSetPwmDutyCycle(u8Ratio);
            }
        }
        break;
  
        default:
        mLIBassert(cFalse);
    //QACJ 3352: amarinm1: It is easily expandable this way.
    }

    DATPwmCallBackTxWithAddr(AddrP, cLDBCorrect);
}

//==============================================================================
// DESCRIPTION:         ISR of PWM timer
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
#ifndef X90_PROJECT
mLDBIntDeclareIsr(cLDBHarPwmTimerIt)
{
    //QACJ 3141: adzhelp: Warning comes from STK macro
    mLDBIntEnterIsr(cLDBHarPwmTimerIt);

    if (mLDBPwmIsFadingControlRequested())
    {

#else
void LDBPwmControlFadingIt(void)
{
#endif

        if (u8OldPwmRatio == 0)
        {
            // Switch to 0% PWM
            // 1.Stop count operation before setting other registers
            mLDBIocStopTimer(cLDBHarPwmTimer);
            // 2. Disable output
            mLDBIocPWMOutputDisable(cLDBHarPwmTimer);
            // 3. Start timer
            mLDBIocStartTimer(cLDBHarPwmTimer);
            bPwmIsFadingControlRequested = cFalse;

            // restore output
            mLDBHarConfig(cLDBHarILLOutput, cLDBHarOutput);
            // Output shall be restored after timer output is disabled 
            // in order to remove parasitic short pulse
        }
        else // ratio > 1
        {
            // Switch to XX% PWM
            if (bKeepOutputActive == cFalse)
            {
                bKeepOutputActive = cTrue;
                // 1.Stop count operation before setting other registers
                mLDBIocStopTimer(cLDBHarPwmTimer);
                // 2. Enable output
                mLDBIocPWMOutputEnable(cLDBHarPwmTimer);
                // 3. Start timer
                mLDBIocStartTimer(cLDBHarPwmTimer);
                mLDBIocRefreshPwmDutyCycle(cLDBHarPwmTimer); // see list of precautions for TimerHn
                // output will be 0 for 1 period: hold it fixed to '1' : see Figure 9-12
            }
            else
            {            
                mLDBHarWrite(cLDBHarILLOutput, 0); // restore output latch
                bKeepOutputActive = cFalse;
                bPwmIsFadingControlRequested = cFalse;
            }
        }

#ifndef X90_PROJECT
    }

    //QACJ 3141: adzhelp: Warning comes from STK macro
    mLDBIntLeaveIsr(cLDBHarPwmTimerIt);
#endif
}