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
// Component:    LDB_DOU
// -----------------------------------------------------------------------------
// $Date:   Mar 09 2010 09:48:20  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_DOU/LDB_DOU.C-arc  $
// $Revision:   1.18  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_DOU/LDB_DOU.C-arc   $
// 
//    Rev 1.18   Mar 09 2010 09:48:20   adzhelp
// Cm007644: DLK: Doolock Led switched off in sleep mode
// 
//    Rev 1.17   Feb 04 2010 12:28:30   adzhelp
// Cm007297: Implementation EEPROM reprogramming mode loop
// 
//    Rev 1.16   Jan 14 2010 17:40:46   amanevd
// Cm007119: Writing of outputs protected with critical section
// 
//    Rev 1.15   Dec 15 2009 11:23:30   amanevd
// Cm005566: QAC fix and RESULT.TXT update
// 
//    Rev 1.14   Dec 15 2009 10:38:24   amanevd
// Cm005566: DO_VERLOG SC detection strategy updated
// 
//    Rev 1.13   Dec 10 2009 09:50:34   adzhelp
// Cm005566: DO_VERLOG SCGnd and SCBat detection
// 
//    Rev 1.12   Dec 03 2009 11:38:04   amanevd
// Cm006751: DO_VERLOG set to 0 when not sending frame
// 
//    Rev 1.11   Nov 04 2009 17:42:06   adzhelp
// Cm005566: HW Protection - check for DO_VERLOG SC to gnd
// 
//    Rev 1.10   Oct 07 2009 09:03:48   adzhelp
// Cm005497: Protection from repeated controls nominal/sleep
// 
//    Rev 1.9   Oct 06 2009 11:40:46   adzhelp
// Cm005497: Implementation of unused pins treatment
// 
//    Rev 1.8   Sep 21 2009 12:04:40   amanevd
// Cm005044: Init value for port cLDBHarVerlogOut changed to 1
// 
//    Rev 1.7   Jul 15 2009 18:09:24   adzhelp
// Cm005205: Port1 mask updated: P16 removed from control
// 
//    Rev 1.6   Apr 27 2009 15:56:22   adzhelp
// Cm003272: Direct setting of VERLOG_LED output restricted only for sleep mode
// 
//    Rev 1.5   Apr 23 2009 17:47:52   adzhelp
// Cm003265: Last message byte removed
// 
//    Rev 1.4   Apr 23 2009 14:03:36   adzhelp
// Cm003272: Added possibility to command directly VERLOG_LED
// 
//    Rev 1.3   Apr 23 2009 13:31:56   adzhelp
// Cm003271: Added possibility to disable OPEN DOOR LED output
// 
//    Rev 1.2   Mar 19 2009 14:29:48   adzhelp
// Cm003619: Value masked before applying to port
// 
//    Rev 1.1   Mar 12 2009 08:57:48   adzhelp
// Cm003619: Parameterization of digital outputs
// 
//    Rev 1.0   10 Nov 2008 15:28:18   ailievb
// Initial revision.
//******************************************************************************


//------------------------------------------------------------------------------
// Body Identification
//------------------------------------------------------------------------------

#define ldb_dou "ldb_dou"

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------
#include "ldbtypes.h"
#include "ldb.h"
#include "ldb_int.h"
#include "ldb_reg.h"
#include "ldb_har.h"
#include "ldb_dou.h"
#include "ldb_doup.h"


//------------------------------------------------------------------------------
// Local constants
//------------------------------------------------------------------------------
// Active bits in mask ('1') inform which pins are digital outputs 
// managed by DOU channel
// Some ports can have dynamic masks when certain outputs are not driven
// depending on ECU type (set to 0V output)

#define cBuffer0Port        1
#define cBuffer0Mask        u8Buffer0Mask
#define cBuffer0MaskInit    (U8)0x0CU

#define cBuffer1Port        4
#define cBuffer1Mask        cBuffer1MaskInit
#define cBuffer1MaskInit    (U8)0x02U

#define cBuffer2Port        5
#define cBuffer2Mask        u8Buffer2Mask
#define cBuffer2MaskInit    (U8)0x04U

#define cBuffer3Port        7
#define cBuffer3Mask        u8Buffer3Mask
#define cBuffer3MaskInit    (U8)0xFFU

#define cBufferSize         4U

#define cPortResetValue         ((U8)0x00U)
#define cVerlogOutActiveValue   1
#define cVerlogOutSleepValue    0

// Digital outputs that can be disabled
#define cOutputBuffer3Port75    ((U8)0x20U)
#define cOutputBuffer3Port73    ((U8)0x08U)
#define cOutputBuffer3Port71    ((U8)0x02U)
#define cOutputBuffer3Port70    ((U8)0x01U)
#define cOutputBuffer2Port52    ((U8)0x04U)
#define cOutputBuffer0Port13    ((U8)0x08U)

// EEPROM regrogramming constants
#define cCsManagementAllowed    ((U8)0x4AU)
#define cCsManagementForbidden  ((U8)0U)
#define cWatchdogRefreshValue   ((U8)0xACU)

//------------------------------------------------------------------------------
// Local macros
//------------------------------------------------------------------------------
//QACJ 3443: adzhelp: Macro concatenation used
#define mConfigureDOPorts(Mode) mConfigureDOPorts##Mode()

// Configure all managed DO port pins as outputs
#define mConfigureDOPortsNominal() \
    mConfigurePort(cBuffer0Port, cBuffer0MaskInit); \
    mConfigurePort(cBuffer1Port, cBuffer1MaskInit); \
    mConfigurePort(cBuffer2Port, cBuffer2MaskInit); \
    /* //QACJ 3412: adzhelp: Last line statement is not necessary */ \
    mConfigurePort(cBuffer3Port, cBuffer3MaskInit)

// Independant from mode or ECU type all predefined outputs remain such:
#define mConfigureDOPortsSleep() mConfigureDOPortsNominal()

#define mConfigurePort(Port, Mask) mConfigurePort2(Port, Mask)
#define mConfigurePort2(Port, Mask) \
    /* //QACJ 0881: adzhelp: Order of evalution of parameters not important */ \
    /* //QACJ 3435: adzhelp: Multiple use of parameters not important */ \
    mLDBRegWrite8BitRegister(PM##Port, (U8)(mLDBRegRead8BitRegister(PM##Port) & (U8)(~(Mask))))


// Set zeros for all managed DO port pins
#define mResetDOPorts() \
    mResetPort(cBuffer0Port, cBuffer0Mask); \
    mResetPort(cBuffer1Port, cBuffer1Mask); \
    mResetPort(cBuffer2Port, cBuffer2Mask); \
    /* //QACJ 3412: adzhelp: Last line statement is not necessary */ \
    mResetPort(cBuffer3Port, cBuffer3Mask)

#define mResetPort(Port, Mask) mWritePort(Port, Mask, cPortResetValue)

#define mWritePort(Port, Mask, Value) mWritePort2(Port, Mask, Value)

#ifndef _QAC_
#define mWritePort2(Port, Mask, Value) \
    { \
        U8 u8InvMask; \
        U8 u8Result; \
        u8Result = (U8)((U8)(Value) & (U8)(Mask)); \
        u8InvMask = (U8)~((U8)(Mask)); \
        mLDBIntDisableAllIts(); \
        mLDBRegWrite8BitRegister(P##Port, \
            (U8)( (U8)((U8)mLDBRegRead8BitRegister(P##Port) & (U8)u8InvMask) | \
                  (U8)u8Result) ); \
        mLDBIntEnableAllIts(); \
    }
#else
#define mWritePort2(Port, Mask, Value)  NOP()
#endif

// Special masks treatment
// P13 - OPEN_DOOR_LED
// Unmask - disable control of pin
#define mUnmaskOPEN_DOOR_LED()  (u8Buffer0Mask &= (U8)0xF7U)
// Mask - enable control of pin
#define mMaskOPEN_DOOR_LED() (u8Buffer0Mask |= (U8)cOutputBuffer0Port13)
// Restore masks
#define mRestoreMasks() \
    u8Buffer0Mask = cBuffer0MaskInit; \
    u8Buffer2Mask = cBuffer2MaskInit; \
    /* //QACJ 3412: adzhelp: Last line statement is not necessary */ \
    u8Buffer3Mask = cBuffer3MaskInit

// Digital outputs disabled on ECU type in active mode
// Outputs will be driven 0 V even if requested active by application

// L1
#define mConfigUnusedDigitalOutputsActiveL1() \
    mRestoreMasks(); \
    u8Buffer3Mask &= (U8)~(cOutputBuffer3Port73 | cOutputBuffer3Port71 | cOutputBuffer3Port70); \
    u8Buffer2Mask &= (U8)~(cOutputBuffer2Port52); \
    /* //QACJ 3412: adzhelp: Last line statement is not necessary */ \
    u8Buffer0Mask &= (U8)~(cOutputBuffer0Port13)

// L2
#define mConfigUnusedDigitalOutputsActiveL2() \
    mRestoreMasks(); \
    u8Buffer3Mask &= (U8)~(cOutputBuffer3Port75 | cOutputBuffer3Port73); \
    /* //QACJ 3412: adzhelp: Last line statement is not necessary */ \
    u8Buffer2Mask &= (U8)~(cOutputBuffer2Port52)

// L3
#define mConfigUnusedDigitalOutputsActiveL3() \
    mRestoreMasks()

// L4
#define mConfigUnusedDigitalOutputsActiveL4() \
    mRestoreMasks(); \
    u8Buffer3Mask &= (U8)~(cOutputBuffer3Port75 | cOutputBuffer3Port73 | cOutputBuffer3Port71 | cOutputBuffer3Port70); \
    u8Buffer2Mask &= (U8)~(cOutputBuffer2Port52); \
    /* //QACJ 3412: adzhelp: Last line statement is not necessary */ \
    u8Buffer0Mask &= (U8)~(cOutputBuffer0Port13)

// L5
#define mConfigUnusedDigitalOutputsActiveL5() \
    mRestoreMasks(); \
    u8Buffer3Mask &= (U8)~(cOutputBuffer3Port75 | cOutputBuffer3Port71 ); \
    /* //QACJ 3412: adzhelp: Last line statement is not necessary */ \
    u8Buffer2Mask &= (U8)~(cOutputBuffer2Port52)

// L6
#define mConfigUnusedDigitalOutputsActiveL6() \
    mConfigUnusedDigitalOutputsActiveL5()

#define mConfigUnusedDigitalOutputsActiveL7() \
    mRestoreMasks()

// EEPROM reprogramming management:
#define mConfigureAllPortsAsInputs() \
    mLDBRegWrite8BitRegister(PM0, 0xFFU); \
    mLDBRegWrite8BitRegister(PM1, 0xFFU); \
    mLDBRegWrite8BitRegister(PM2, 0xFFU); \
    mLDBRegWrite8BitRegister(PM3, 0xFFU); \
    mLDBRegWrite8BitRegister(PM4, 0xFFU); \
    mLDBRegWrite8BitRegister(PM5, 0xFFU); \
    mLDBRegWrite8BitRegister(PM6, 0xFFU); \
    mLDBRegWrite8BitRegister(PM7, 0xFFU); \
    mLDBRegWrite8BitRegister(PM12, 0xFFU); \
    /*//QACJ 3412: adzhelp: Last line statement will be appended on use */\
    mLDBRegWrite8BitRegister(PM14, 0xFFU)

//------------------------------------------------------------------------------
// Local types
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Local data
//------------------------------------------------------------------------------
static BOOL bSleepMode = cTrue;

static MEM_FAST U8 u8Buffer0Mask = cBuffer0MaskInit;
//QACJ 3207: adzhelp: Variable is used in macros
static MEM_FAST U8 u8Buffer2Mask = cBuffer2MaskInit;
//QACJ 3207: adzhelp: Variable is used in macros
static MEM_FAST U8 u8Buffer3Mask = cBuffer3MaskInit;

static U8 u8EcuType = (U8)cLDBDouEcuTypeL7; // all pins used

static U8 u8EepromReprogCsManagement;

//------------------------------------------------------------------------------
// Constant local data
//------------------------------------------------------------------------------

// This is an example:
// static const tType  cConstantName;

//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Constant exported data
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Local function prototypes
//------------------------------------------------------------------------------
static MEM_TYPE void ConfigUnusedPins (void);

//==============================================================================
//=========================== LOCAL FUNCTIONS ==================================
//==============================================================================

//==============================================================================
// DESCRIPTION :
//  
// PARAMETERS (Type,Name,Min,Max) :  none
//
// RETURN VALUE :  none
// 
// DESIGN INFORMATION :  refer to Detailed Design Document
//==============================================================================
static MEM_TYPE void ConfigUnusedPins (void)
{
    if (bSleepMode == cFalse)
    {
        // Active mode configuration
        switch (u8EcuType)
        {
        case cLDBDouEcuTypeL1:
            mLDBDouConfigUnusedPins(Active, L1);
            break;
        case cLDBDouEcuTypeL2:
            mLDBDouConfigUnusedPins(Active, L2);
            break;
        case cLDBDouEcuTypeL3:
            mLDBDouConfigUnusedPins(Active, L3);
            break;
        case cLDBDouEcuTypeL4:
            mLDBDouConfigUnusedPins(Active, L4);
            break;
        case cLDBDouEcuTypeL5:
            mLDBDouConfigUnusedPins(Active, L5);
            break;
        case cLDBDouEcuTypeL6:
            mLDBDouConfigUnusedPins(Active, L6);
            break;
        case cLDBDouEcuTypeL7:
            mLDBDouConfigUnusedPins(Active, L7);
            break;
        default:
            mLIBassert(cFalse);
            break;
        }
    }
    else
    {
        // Sleep mode configuration
        switch (u8EcuType)
        {
        case cLDBDouEcuTypeL1:
            mLDBDouConfigUnusedPins(Sleep, L1);
            break;
        case cLDBDouEcuTypeL2:
            mLDBDouConfigUnusedPins(Sleep, L2);
            break;
        case cLDBDouEcuTypeL3:
            mLDBDouConfigUnusedPins(Sleep, L3);
            break;
        case cLDBDouEcuTypeL4:
            mLDBDouConfigUnusedPins(Sleep, L4);
            break;
        case cLDBDouEcuTypeL5:
            mLDBDouConfigUnusedPins(Sleep, L5);
            break;
        case cLDBDouEcuTypeL6:
            mLDBDouConfigUnusedPins(Sleep, L6);
            break;
        case cLDBDouEcuTypeL7:
            mLDBDouConfigUnusedPins(Sleep, L7);
            break;
        default:
            mLIBassert(cFalse);
            break;
        }
    }
}


//==============================================================================
//=========================== EXPORTED FUNCTIONS ===============================
//==============================================================================

//==============================================================================
// DESCRIPTION :
//  
// PARAMETERS (Type,Name,Min,Max) :  none
//
// RETURN VALUE :  none
// 
// DESIGN INFORMATION :  refer to Detailed Design Document
//==============================================================================
MEM_TYPE void LDBDouInit(void)
{
    mConfigureDOPorts(Nominal);
    mResetDOPorts();
    // VERLOG output
    mLDBHarWrite(cLDBHarVerlogOut, cVerlogOutSleepValue);
    mLDBHarConfig(cLDBHarVerlogOut, cLDBHarOutput);
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
MEM_TYPE void LDBDouControl(const tCtrl Ctrl)
{
    switch(Ctrl)
    {
    case cLDBDouEnterNominalMode :
        if (bSleepMode != cFalse)  // controls are called by DAT_DOU and DAT_CPU
        {
            bSleepMode = cFalse;
            mConfigureDOPorts(Nominal);
            mLDBHarWrite(cLDBHarVerlogOut, cVerlogOutSleepValue);
            ConfigUnusedPins();
            u8EepromReprogCsManagement = cCsManagementForbidden;
        }
        break;
    case cLDBDouEnterSleepMode :
        if (bSleepMode == cFalse)   // controls are called by DAT_DOU and DAT_CPU
        {
            bSleepMode = cTrue;
            mConfigureDOPorts(Sleep);
            mResetDOPorts(); // disable all managed outputs
            mLDBHarWrite(cLDBHarVerlogOut, cVerlogOutSleepValue);
            ConfigUnusedPins();
        }
        break;
    
    // Control DO_DATA_IMMOBILIZER (cLDBHarTrpOut)
    case cLDBControlSetDO_DATA_IMMOBILIZER:
        mLDBHarWrite(cLDBHarTrpOut, 1);
        break;
    case cLDBControlClearDO_DATA_IMMOBILIZER:
        mLDBHarWrite(cLDBHarTrpOut, 0);
        break;
    
    // Control DO_VERLOG (cLDBHarVerlogOut)
    case cLDBControlSetDO_VERLOG:
        mLDBHarWrite(cLDBHarVerlogOut, 1);
        break;
    case cLDBControlClearDO_VERLOG:
        mLDBHarWrite(cLDBHarVerlogOut, 0);
        break;

    case cLDBControlCheckDO_VERLOGSCDetect:
        //QACJ 3346: amanevd: Value depends from digital input state
        if(0 == mLDBHarRead(cLDBHarVerlogOut))
        {
            // Check SC to Gnd on DIO_ECM
            //QACJ 3325: amanevd: Value depends from digital input state
            if(1 == mLDBHarRead(cLDBHarVerlogIn))
            //QACJ 3201: amanevd: Statement is reachable
            {
                // Output set to '0' (active) but Verlog line seen not active
                DATVlgCallBackEndCtrl(cLDBControlCheckDO_VERLOGSCGnd, cLDBError);
            }
            else
            {
                DATVlgCallBackEndCtrl(cLDBControlCheckDO_VERLOGSCGnd, cLDBCorrect);
            }
        }
        else
        //QACJ 3201: amanevd: Statement is reachable
        {
            // Check SC to Bat on DIO_ECM
            //QACJ 3346: adzhelp: Value depends from digital input state
            if(0 == mLDBHarRead(cLDBHarVerlogIn))
            {
                // Output set to '1' (active) but Verlog line seen active
                DATVlgCallBackEndCtrl(cLDBControlCheckDO_VERLOGSCBat, cLDBError);
            }
            else
            {
                DATVlgCallBackEndCtrl(cLDBControlCheckDO_VERLOGSCBat, cLDBCorrect);
            }
        }
        break;

    // Control DOOR_LOCK_LED
    case cLDBDouEnableOPEN_DOOR_LED:
        mMaskOPEN_DOOR_LED();
        break;
    case cLDBDouDisableOPEN_DOOR_LED:
        if ((u8EcuType != cLDBDouEcuTypeL1) && (u8EcuType != cLDBDouEcuTypeL4))
        {
            mUnmaskOPEN_DOOR_LED();
        }
        break;

    // Control VERLOG_LED (cLDBHarVerlogLed)
    case cLDBControlSetVERLOG_LED:
        if (bSleepMode != cFalse)
        {
            mLDBHarWrite(cLDBHarVerlogLed, 1);
        }
        break;
    case cLDBControlClearVERLOG_LED:
        if (bSleepMode != cFalse)
        {
            mLDBHarWrite(cLDBHarVerlogLed, 0);
        }
        break;

    // EEPROM reprogramming CS management
    case cLDBDouPrepareEepromReprog:
        u8EepromReprogCsManagement = cCsManagementAllowed;
        break;

    case cLDBDouStartEepromReprog:
        if (u8EepromReprogCsManagement == cCsManagementAllowed)
        {
            mLDBIntDisableAllIts();
            mConfigureAllPortsAsInputs();

            //QACJ 3323: adzhelp: The endless loop is intentional
            while (cTrue != cFalse) // Exit from this mode by reset only
            {
                // endless loop is intentional
                // this is very specific manufacturing mode
                mLDBHarWrite(cLDBHarEepCS, mLDBHarRead(cLDBHarEepCsShadow));
                mLDBRegWrite8BitRegister(WDTE, cWatchdogRefreshValue);
            }
        }
        break;
    
    // ECU Type controls //

    case cLDBDouSetEcuType0:
        mResetDOPorts();
        u8EcuType = cLDBDouSetEcuType0;
        ConfigUnusedPins();
        break;
    case cLDBDouSetEcuType1:
        mResetDOPorts();
        u8EcuType = cLDBDouSetEcuType1;
        ConfigUnusedPins();
        break;
    case cLDBDouSetEcuType2:
        mResetDOPorts();
        u8EcuType = cLDBDouSetEcuType2;
        ConfigUnusedPins();
        break;
    case cLDBDouSetEcuType3:
        mResetDOPorts();
        mLIBassert(cFalse); // this type is not supported
        u8EcuType = cLDBDouEcuTypeL7; // set to L7 for target - no restrictions
        ConfigUnusedPins();
        break;
    case cLDBDouSetEcuType4:
        mResetDOPorts();
        u8EcuType = cLDBDouSetEcuType4;
        ConfigUnusedPins();
        break;
    case cLDBDouSetEcuType5:
        mResetDOPorts();
        u8EcuType = cLDBDouSetEcuType5;
        ConfigUnusedPins();
        break;
    case cLDBDouSetEcuType6:
        mResetDOPorts();
        u8EcuType = cLDBDouSetEcuType6;
        ConfigUnusedPins();
        break;
    case cLDBDouSetEcuType7:
        mResetDOPorts();
        u8EcuType = cLDBDouSetEcuType7;
        ConfigUnusedPins();
        break;

    default :
        mLIBassert(0);
        break;
    }
}
//==============================================================================
// DESCRIPTION : Write digital outputs states
//  
// PARAMETERS (Type,Name,Min,Max) :  none
//
// RETURN VALUE :  none
// 
// DESIGN INFORMATION :  refer to Detailed Design Document
//==============================================================================
void LDBDouSendWithoutAddr(const tMsg* const pMsg)
{
    //QACJ 3203: adzhelp: Identifier used in macro mWritePort
    U8* pu8Buffer;

    if (pMsg != NULL)
    {
        //QACJ 3199: adzhelp: Identifier used in macro mWritePort
        pu8Buffer = pMsg->pBuffer;
        mLIBassert(pMsg->Lng == cBufferSize);

        mWritePort(cBuffer0Port, cBuffer0Mask, pu8Buffer[0]);
        mWritePort(cBuffer1Port, cBuffer1Mask, pu8Buffer[1]);
        mWritePort(cBuffer2Port, cBuffer2Mask, pu8Buffer[2]);
        mWritePort(cBuffer3Port, cBuffer3Mask, pu8Buffer[3]);
    }
}
