//*****************************************************************************
// Company:      Johnson Controls Inc.
// ----------------------------------------------------------------------------
// Copyright:    This software is JCI property.
//               Duplication or disclosure without JCI written authorization
//               is prohibited.
// ----------------------------------------------------------------------------
// Project:      X90_BCM
// Language:     ANSI-C
// ----------------------------------------------------------------------------
// Component:    LAP_CAR
// ----------------------------------------------------------------------------
// $Date:   Jun 16 2010 14:21:28  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/CAR/LAP_CAR.c-arc  $
// $Revision:   1.18  $
// ----------------------------------------------------------------------------  
//
//  $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/CAR/LAP_CAR.c-arc  $
// 
//    Rev 1.18   Jun 16 2010 14:21:28   amanevd
// Cm009190: EEP_CodeAFSAvailable replaced with EEP_EraseAFSCodeRequest
// 
//    Rev 1.17   Mar 01 2010 14:29:04   adzhelp
// Cm007334: Code review corrections by BI
// 
//    Rev 1.16   Feb 25 2010 15:50:56   amanevd
// Cm007334: DO_DATA_IMMOBILIZERProtection set to 0 on PWR_IGN rising edge
// 
//    Rev 1.15   Feb 24 2010 18:25:38   amanevd
// Cm005797: KeyIsNotAuthenticated sent on MERA elapse
// 
//    Rev 1.14   Feb 10 2010 16:45:28   amanevd
// Cm007075: Volatile Faults and Deprotection cleared at IGN ON
// 
//    Rev 1.13   Feb 08 2010 09:25:42   amanevd
// Cm006744: Perform 32-bit math operations only when values are changed
// 
//    Rev 1.12   Feb 02 2010 14:54:48   amanevd
// Cm005797: cVerlogTimeOut set to 150ms
// 
//    Rev 1.11   Jan 15 2010 18:35:04   amanevd
// Cm005797: CARManageImmobiliserAndCarAntiTheft graph set on 10ms period
// 
//    Rev 1.10   Nov 02 2009 13:19:14   amanevd
// Cm006602: 60ms correction of EEP_TimeOutMERA removed
// 
//    Rev 1.9   Nov 02 2009 10:45:22   amanevd
// Cm006599: Verlog frame start time modified
// 
//    Rev 1.8   Sep 29 2009 18:20:58   amanevd
// Cm006330: Permanent authentication is suspended on ignition switched off
// 
//    Rev 1.7   Sep 25 2009 11:21:34   amanevd
// Cm006166: Resolution of TMP_MERA changed to Min=0 / Step=0,1s / Max=25.5s=> Default = 10s (100)
// 
//    Rev 1.6   Sep 03 2009 12:37:04   amanevd
// Cm005133: Diagnostic information is cleared on MERA timeout, VERLOGON included
// 
//    Rev 1.5   Aug 28 2009 17:41:32   amanevd
// Cm005567: Code review correction
// 
//    Rev 1.4   Jul 28 2009 14:59:28   amanevd
// Cm005567: TestVirginKey is available on unsuccessful authentication with PWR_IGN==1
// 
//    Rev 1.3   Jul 16 2009 11:40:46   amanevd
// Cm005193: Signal ECMIsProtected substituted with EEP_CodeAFSAvailable
// 
//    Rev 1.2   Apr 29 2009 13:13:52   amanevd
// Cm003272 - Intermediate part 3 
// - PRS compliance
// 
//    Rev 1.1   Apr 22 2009 19:23:48   amanevd
// Cm003272 - Finishing part 1 - pre-integration
// 
//    Rev 1.0   Jan 09 2009 14:18:20   amanevd
// Initial revision.
//
//=============================================================================

//-----------------------------------------------------------------------------
//  Body Identification
//-----------------------------------------------------------------------------

#define LAP_CAR   "LAP_CAR"

//-----------------------------------------------------------------------------
//  Included files
//
//  #include <system_file_name.h>
//  #include "project_file_name.h"
//-----------------------------------------------------------------------------

#include "lib.h"
#include "tos.h"
#include "dat.h"
#include "LAP_CAR.h"
#include "LAP_CAR.hgr"

//-----------------------------------------------------------------------------
//  Local constants
//
//  #define cConstantName   ((tType) ConstantValue)
//-----------------------------------------------------------------------------

// Time out definition
#define cTimeOut3sECM       (mTOSConvMsInTimerTick(3000UL))
#define cTimeOut1sec        (mTOSConvMsInTimerTick(1000UL))
#define cTimeOut1mn         (mTOSConvMsInTimerTick(60000UL))
#define cVerlogTimeOut      (mTOSConvMsInTimerTick(150UL))

// amanevd: 'Neg' constants make QAC to shut up. Must update them
// every time you update the original constant !!!
#define cReadyToSleep       ((U8) 0x01U)
#define cNegReadyToSleep    ((U8) 0xFEU)
#define cTestVirginKey      ((U8) 0x02U)
#define cNegTestVirginKey   ((U8) 0xFDU)
#define cPermAuthMode       ((U8) 0x04U)
#define cNegPermAuthMode    ((U8) 0xFBU)

#define cMaxAuthentPermanentTotalCounter          ((U16)0xFFFFU)
#define cMaxAuthentPermanentFailCounter           ((U8)0xFFU)
#define cMaxAuthentPermanentResynchroFailCounter  ((U8)0xFFU)

//-----------------------------------------------------------------------------
//  Local macros
//
//  #define mMacroName   (MacroDefinition)
//-----------------------------------------------------------------------------
#define mSetReadyToSleep()    (u8CarImmoFlag |= cReadyToSleep)
#define mClearReadyToSleep()  (u8CarImmoFlag &= cNegReadyToSleep)
#define mReadyToSleepIsOn()   ((u8CarImmoFlag & cReadyToSleep) != 0)
#define mReadyToSleepIsOff()  ((u8CarImmoFlag & cReadyToSleep) == 0)

#define mSetTestVirginKey()   (u8CarImmoFlag |= cTestVirginKey)
#define mClearTestVirginKey() (u8CarImmoFlag &= cNegTestVirginKey)
#define mTestVirginKeyIsOn()  ((u8CarImmoFlag & cTestVirginKey) != 0)
#define mTestVirginKeyIsOff() ((u8CarImmoFlag & cTestVirginKey) == 0)

#define mSetPermAuthMode()    (u8CarImmoFlag |= cPermAuthMode)
#define mClearPermAuthMode()  (u8CarImmoFlag &= cNegPermAuthMode)
#define mPermAuthModeIsOn()   ((u8CarImmoFlag & cPermAuthMode) != 0)
#define mPermAuthModeIsOff()  ((u8CarImmoFlag & cPermAuthMode) == 0)

//QACJ 3443:amanevd: Last instance of mDATRead(cTimeOutMERA -> mDATRead -> mDATRead2 -> [mDATRead]) is a concatenation of mDATRead ## DataType## DataName ## TreatmentType()
#define mCalcTimeOutMERA()  (mTOSConvMsInTimerTick(((U32)(u8TimeOutMERA = mDATRead(U8Bit, EEP_TimeOutMERA, Default)) * 100UL)))

#define mReadTimeOutMERA()  (CalculatedMERA = \
                                (u8TimeOutMERA == mDATRead(U8Bit, EEP_TimeOutMERA, Default)) \
                                ? CalculatedMERA \
    /*//QACJ 3443:amanevd: Last instance of mDATRead(cTimeOutMERA -> mDATRead -> mDATRead2 -> [mDATRead]) is a concatenation of mDATRead ## DataType## DataName ## TreatmentType()*/ \
                                : mCalcTimeOutMERA())

//-----------------------------------------------------------------------------
//  Local types
//
//  struct  sStructureName { ... };
//  union   uUnionName { ... };
//  enum    eEnumerationName { ... };
//  typedef Expression tTypeName;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//  Local data
//
//  static  tType   VariableName;
//  static  tType*  pVariableName; 
//-----------------------------------------------------------------------------

// Timer
static tTOSTimer    CarImmobilizerTimer;
static tTOSTimer    CalculatedMERA;

// Flags
static U8   u8CarImmoFlag;

static U8   u8TimeOutMERA;

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

#ifdef X90_PROJECT
static MEM_TYPE BOOL CARIgnitionOFF_Static(void);
static MEM_TYPE void CARAuthorizedStandByMode_Static(void);
static MEM_TYPE void CARKeyAuthentication_Static(void);
static MEM_TYPE void CARKeyAuthenticationInTestMode_Static(void);
static MEM_TYPE void CARKeyAuthenticationWithTransportISK_Static(void);
static MEM_TYPE void CARPermanentAuthenticationResultNOK_Static(void);
#endif

//=============================================================================
//=========================== LOCAL FUNCTIONS =================================
//=============================================================================

//=============================================================================
//  DESCRIPTION :
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//=============================================================================
//static type FunctionName(...)

//=============================================================================
//============================ EXPORTED FUNCTIONS =============================
//=============================================================================

//*****************************************************************************
//  DESCRIPTION :
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
//type LAYCmpFunctionName(...)
//{
//}

//*****************************************************************************
//  DESCRIPTION : Start the permanent authentication service
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void CARStartAuthentPermKey(void)
{
    mDATWrite(U16Bit,AuthentPermanentTotalCounter,0,Default);
    mDATWrite(U8Bit,AuthentPermanentFailCounter,0,Default);
    mDATWrite(U8Bit,AuthentPermanentResynchroFailCounter,0,Default);

    // Initialization of the test mode
    mSetPermAuthMode();
}

//*****************************************************************************
//  DESCRIPTION : Exit from the permanent authentication service
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void CARExitFromAuthentPermKey(void)
{
    // Stop the test mode
    mClearPermAuthMode();
}

//*****************************************************************************
//  DESCRIPTION : Start test virgin key service
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void CARStartTestVirginKey(void)
{
    // Initialization of the virgin test mode
    mSetTestVirginKey();

    // Switch off the LED_VERLOG
    mDATWrite(U8Bit, LedVerlogPattern, cDATSwitchOffVerlogPattern, Default);
}

//*****************************************************************************
//  DESCRIPTION : Set LAP_CAR component in the Run mode
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void CARImmoWorkingMode(void)
{
    mClearReadyToSleep();
}

//*****************************************************************************
//  DESCRIPTION : Treat authentication service error
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void CARKeyAuthentErrorAndProtected(void)
{ 
    // Error pattern on LED_VERLOG
    mDATWrite(U8Bit, LedVerlogPattern, cDATKeyNotRecognizedVerlogPattern, Default);

    // Inform that the key is not authenticated
    TOSSendControl(cTOSControlKeyIsNotAuthenticated);

    mDATControl(Vlg, cDATVlgStart);
}

//*****************************************************************************
//  DESCRIPTION : Test if the permanent authentication service is requested
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL CARAuthentPermActivated(void)
{
    return (mPermAuthModeIsOn());
} 

//*****************************************************************************
//  DESCRIPTION : Test if the permanent authentication service is in progress
//                  and PWR_IGN==1
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL CARAuthentPermActivatedAndIgnitionOn(void)
{
    return (mPermAuthModeIsOn() && (cFalse != mDATRead(U1Bit, PWR_IGN, Default)));
} 

//*****************************************************************************
//  DESCRIPTION : Start the MERA timer
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void CARStartTempoMera(void)
{
    // Switch off LED_VERLOG
    mDATWrite(U8Bit, LedVerlogPattern, cDATSwitchOffVerlogPattern, Default);

    TOSStartTimer(&CarImmobilizerTimer);
}

//*****************************************************************************
//  DESCRIPTION : Tempo Mera Elapsed Action
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void CARTempoMeraElapsedAction(void)
{
    mDATWrite(U1Bit, VERLOGON, 1, Default);
    mDATControl(Trp, cDATTrpInitDiagInfo);
    TOSSendControl(cTOSControlKeyIsNotAuthenticated);
}

//*****************************************************************************
//  DESCRIPTION : Start the immobilizer antenna sleep verification timer
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void CARStartTpoSleepVerify(void)
{
    TOSStartTimer(&CarImmobilizerTimer);
}

//*****************************************************************************
//  DESCRIPTION : Test if the MERA time out is elapsed
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL CARTempoMeraFinishedOK(void)
{
    tTOSTimer   CalculatedMERAL;

    //QACJ 3226: amanevd: This is intentional and is checked out for problems.
    CalculatedMERAL = mReadTimeOutMERA();
    return (TOSIsTimerElapsed(&CarImmobilizerTimer, CalculatedMERAL));
}

//*****************************************************************************
//  DESCRIPTION : Test if the ECM deprotection time out is elapsed
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL CARTpoECMisElapsed(void)
{
    return (TOSIsTimerElapsed(&CarImmobilizerTimer, cTimeOut3sECM));
}

//*****************************************************************************
//  DESCRIPTION : Test if the immobilizer antenna sleep verification time out
//  is elapsed
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL CARTpoSleepVerifyElapsed(void)
{
    return (TOSIsTimerElapsed(&CarImmobilizerTimer, cTimeOut1mn));
}

//*****************************************************************************
//  DESCRIPTION : Initialize LAP_CAR
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void CARInitialize(void)
{
    mClearPermAuthMode();
    mClearTestVirginKey();
}

//*****************************************************************************
//  DESCRIPTION : Indicate if LAP_CAR is ready to go to sleep mode
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void CARIsAnybodyMaintainActiveState(void)
{
    if (mReadyToSleepIsOff())
    {
        TOSWriteSignal(cTOSSignalSomebodyMaintainActiveState);
    }  
}

//*****************************************************************************
//  DESCRIPTION : Set LAP_CAR in run mode
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void CAREnterActiveState(void)
{
    TOSSeqActivateGraph(cTOSSeqGraphIdCARManageImmobiliserAndCarAntiTheft);
}

//*****************************************************************************
//  DESCRIPTION : Set LAP_CAR in sleep mode
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void CARLeaveActiveState(void)
{
    mLIBassert(mReadyToSleepIsOn());
    TOSSeqDeactivateGraph(cTOSSeqGraphIdCARManageImmobiliserAndCarAntiTheft);
}

//*****************************************************************************
//  DESCRIPTION : Test if ignition is Off
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL CARIgnitionOFF(void)
{
#ifdef X90_PROJECT
    return CARIgnitionOFF_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL CARIgnitionOFF_Static(void)
{
#endif

    BOOL bApcOffL;
    if (mDATRead(U1Bit, PWR_IGN, Default) == 0)
    {
        // Activate RF
        TOSSendControl(cTOSControlReleaseCarTrpResource);
        mClearPermAuthMode();

        if (    (cDATNoLearningMode == mDATRead(U8Bit, LearningModeInProgress, Default))
             && (1 == mDATRead(U1Bit, VERLOGON, Default))
           )
        {
            mDATControl(Trp, cDATTrpInitDiagInfo);
        }
        bApcOffL = cTrue;
    }
    else
    {
        bApcOffL = cFalse;
    }
    return bApcOffL;
}

//*****************************************************************************
//  DESCRIPTION : Test if ignition is On
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void CARAuthorizedStandByMode(void)
{
#ifdef X90_PROJECT
    CARAuthorizedStandByMode_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void CARAuthorizedStandByMode_Static(void)
{
#endif

    mSetReadyToSleep();

    // Update Led verlog pattern if condition change by diag
    // If BCM is not blank and no learning in progress
    if (   (mDATRead(U1Bit, EEP_BCMBlank, Default) == 0)
    && (mDATRead(U8Bit, LearningModeInProgress, Default) == cDATNoLearningMode))
    {
        // Protected state pattern on LED_VERLOG
        mDATWrite(U8Bit, LedVerlogPattern, cDATVehicleProtectedVerlogPattern, Default);
    }
    else
    {
        mDATWrite(U8Bit, LedVerlogPattern, cDATSwitchOffVerlogPattern, Default);
    }
}

//*****************************************************************************
//  DESCRIPTION : Test if ignition is On
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL CARIgnitionON(void)
{
    BOOL bApcOnL;
    if (mDATRead(U1Bit, PWR_IGN, Default) != 0)
    {
        // Deactivate RF
        TOSSendControl(cTOSControlGetCarTrpResource);
        mDATWrite(U1Bit, DefTrpShortCircuitToGnd, 0, Default);
        mDATWrite(U1Bit, DefTrpShortCircuitToBat, 0, Default);
        mDATWrite(U1Bit, DO_DATA_IMMOBILIZERProtection, 0, Default);
        bApcOnL = cTrue;
    }
    else
    {
        bApcOnL = cFalse;
    }
    return bApcOnL;
}

//*****************************************************************************
//  DESCRIPTION : Test if ignition is On for customer mode
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL CARCustomerIgnitionON(void)
{
    BOOL bApcOnL;
    if (    (mDATRead(U1Bit, PWR_IGN, Default) != 0)
         && (mDATRead(U8Bit, LearningModeInProgress, Default) == cDATNoLearningMode)
         && (mDATRead(U1Bit, EEP_BCMBlank, Default) == 0)
       )
    {
        // Deactivate RF
        TOSSendControl(cTOSControlGetCarTrpResource);
        mClearReadyToSleep();
        TOSStartTimer(&CarImmobilizerTimer);
        mDATWrite(U1Bit, DefTrpShortCircuitToGnd, 0, Default);
        mDATWrite(U1Bit, DefTrpShortCircuitToBat, 0, Default);
        mDATWrite(U1Bit, DO_DATA_IMMOBILIZERProtection, 0, Default);
        bApcOnL = cTrue;
    }
    else
    {
        bApcOnL = cFalse;
    }
    return bApcOnL;
}

//*****************************************************************************
//  DESCRIPTION : Treat BCM blank error
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void CARBCMBlankError(void)
{
    // Switch off LED_VERLOG
    mDATWrite(U8Bit, LedVerlogPattern, cDATSwitchOffVerlogPattern, Default);
}

//*****************************************************************************
//  DESCRIPTION : Test if BCM is blank
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL CARBCMBlankOK(void)
{
    return(mDATRead(U1Bit, EEP_BCMBlank, Default) != 0);
}

//*****************************************************************************
//  DESCRIPTION : Realize key authentication in customer mode
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void CARKeyAuthentication(void)
{
#ifdef X90_PROJECT
    CARKeyAuthentication_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void CARKeyAuthentication_Static(void)
{
#endif

    U8 u8IndexL;

    // Switch On the LED_VERLOG
    mDATWrite(U8Bit, LedVerlogPattern, cDATSwitchOnVerlogPattern, Default);  

    mDATWrite(U1Bit, DATTrpAuthentInLearningMode, 0, Default);
    mDATWrite(U1Bit, DATTrpActiveTestMode, 0, Default);

    // Authentication with BCM ISK
    for (u8IndexL = 0; u8IndexL < cDATTrpISKLengthInBytes; u8IndexL++)
    {
        mDATWriteTable(U8Bit, DATTrpISKForAuthent, u8IndexL, mDATReadTable(U8Bit, EEP_ImmoSecretKey, u8IndexL, Default), Default);
    }

    mDATControl(Trp, cDATTrpAuthenticate);
}

//*****************************************************************************
//  DESCRIPTION : Test if authentication service is not successfully finished
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL CARKeyAuthenticationNOK(void)
{
    return (mDATRead(U8Bit, DATTrpAuthenticationState, Default) == cDATTrpServiceNotSuccessful);
}

//*****************************************************************************
//  DESCRIPTION : Test if authentication service is successfully finished
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL CARKeyAuthenticationOK(void)
{
    return (mDATRead(U8Bit, DATTrpAuthenticationState, Default) == cDATTrpServiceSuccessful);
}

//*****************************************************************************
//  DESCRIPTION : Test if Verlog Timer Elapsed
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL CARIsVerlogTimerElapsed(void)
{
    const BOOL bTimerStartedL = TOSIsTimerStarted(&CarImmobilizerTimer);
    const BOOL bTimerElapsedL = TOSIsTimerElapsed(&CarImmobilizerTimer, cVerlogTimeOut);

    return  (bTimerStartedL && bTimerElapsedL);
}

//*****************************************************************************
//  DESCRIPTION : CARSendVerlogFrame
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void CARSendVerlogFrame(void)
{
    mDATControl(Vlg, cDATVlgStart);
}

//*****************************************************************************
//  DESCRIPTION : Authentication service is successfully finished
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void CARKeyAuthentResultOKandUnprotected(void)
{
    mDATWrite(U8Bit, LedVerlogPattern, cDATSwitchOnVerlogPattern, Default);

    // Start timer for the ECM deprotection
    TOSStartTimer(&CarImmobilizerTimer);

    mDATWrite(U1Bit, VERLOGON, 0, Default);

    // Inform that the key is authenticated
    TOSSendControl(cTOSControlKeyIsAuthenticated);

    mDATControl(Vlg, cDATVlgStart);  
}

//*****************************************************************************
//  DESCRIPTION : Test if the virgin key test is activated
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL CARVirginTestActivated(void)
{
    return (mTestVirginKeyIsOn());
}

//*****************************************************************************
//  DESCRIPTION : Start immobilizer antenna sleep control
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void CARPutImmobilizerAntennaInSleepMode(void)
{
    mDATControl(Trp, cDATTrpSleep);
}

//*****************************************************************************
//  DESCRIPTION : Test if immobilizer antenna sleep control is finished
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL CARSleepModeFinished(void)
{
    return mDATRead(U8Bit, DATTrpSleepControlState, Default) != cDATTrpServiceInProgress;
}

//*****************************************************************************
//  DESCRIPTION : Test if current key need resynchronization
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL CARKeyNeedResynchroOK(void)
{
    BOOL bResultL   = cFalse;

    if (mDATRead(U1Bit, DATTrpKeyWithRF, Default) != 0)
    {
        bResultL = ((mDATRead(U8Bit, EEP_ResynchroRequest, Default) & (U8)((U8)0x01U << mDATRead(U8Bit, DATTrpIndexOfKeyRecognized, Default))) != 0);
    }

    return bResultL;
}

//*****************************************************************************
//  DESCRIPTION : Start resynchronization service
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void CARKeyResynchronization(void)
{
    mDATWrite(U1Bit, DATTrpWriteSecretKeyHigh, 0, Default);
    mDATControl(Trp, cDATTrpResynchronize);
}

//*****************************************************************************
//  DESCRIPTION : Test if resynchronization service is finished
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL CARKeyResynchroFinished(void)
{
    return (mDATRead(U8Bit, DATTrpResynchronizationState, Default) != cDATTrpServiceInProgress);
}

//*****************************************************************************
//  DESCRIPTION : Manage LED_VERLOG pattern
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void CARManageVerlogPattern(void)
{
    // if After Sale Code is requested
    if (1 == mDATRead(U1Bit, EEP_EraseAFSCodeRequest, Default))
    {
        // Switch off LED_VERLOG
        mDATWrite(U8Bit, LedVerlogPattern, cDATSwitchOffVerlogPattern, Default);
    }
}

//*****************************************************************************
//  DESCRIPTION : Test if a learning is in progress
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL CARLearningModeInProgress(void)
{
    return (mDATRead(U8Bit, LearningModeInProgress, Default) != cDATNoLearningMode);
}

//*****************************************************************************
//  DESCRIPTION :
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void CARKeyAuthenticationInTestMode(void)
{
#ifdef X90_PROJECT
    CARKeyAuthenticationInTestMode_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void CARKeyAuthenticationInTestMode_Static(void)
{
#endif

    U8  u8IndexL;
    U16 u16AuthentTryCounterL;

    u16AuthentTryCounterL = mDATRead(U16Bit, AuthentPermanentTotalCounter, Default);
    if (u16AuthentTryCounterL < cMaxAuthentPermanentTotalCounter)
    {
        mDATWrite(U16Bit, AuthentPermanentTotalCounter, (u16AuthentTryCounterL + 1), Default);
    }

    // Authentication with BCM ISK
    for (u8IndexL = 0; u8IndexL < cDATTrpISKLengthInBytes; u8IndexL++)
    {
        mDATWriteTable(U8Bit, DATTrpISKForAuthent, u8IndexL, mDATReadTable(U8Bit, EEP_ImmoSecretKey, u8IndexL, Default), Default);
    }

    mDATControl(Vlg, cDATVlgStart);
    mDATControl(Trp, cDATTrpAuthenticate);
}

//*****************************************************************************
//  DESCRIPTION :
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void CARKeyAuthenticationWithTransportISK(void)
{
#ifdef X90_PROJECT
    CARKeyAuthenticationWithTransportISK_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void CARKeyAuthenticationWithTransportISK_Static(void)
{
#endif

    U8 u8IndexL;

    // Deactivate RF
    TOSSendControl(cTOSControlGetCarTrpResource);

    mClearTestVirginKey();

    mDATWrite(U1Bit, DATTrpAuthentInLearningMode, 1, Default);
    mDATWrite(U1Bit, DATTrpActiveTestMode, 1, Default);

    // Authentication with transport ISK
    for (u8IndexL = 0; u8IndexL < cDATTrpISKLengthInBytes; u8IndexL++)
    {
        mDATWriteTable(U8Bit, DATTrpISKForAuthent, u8IndexL, mDATReadTable(U8Bit, DATTrpTransportISK, u8IndexL, Default), Default);
    }
    mDATControl(Trp, cDATTrpAuthenticate);
}

//*****************************************************************************
//  DESCRIPTION :
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void CARVirginKeyEnd(void)
{
    mDATWrite(U1Bit, DATTrpActiveTestMode, 0, Default);
}

//*****************************************************************************
//  DESCRIPTION :
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL CARKeyWithRf(void)
{
    return (mDATRead(U1Bit, DATTrpKeyWithRF, Default) != 0);
}

//*****************************************************************************
//  DESCRIPTION :
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL CARResynchroNOK(void)
{
    return (mDATRead(U8Bit, DATTrpResynchronizationState, Default) == cDATTrpServiceNotSuccessful);
}

//*****************************************************************************
//  DESCRIPTION :
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL CARResynchroOK(void)
{
    return (mDATRead(U8Bit, DATTrpResynchronizationState, Default) == cDATTrpServiceSuccessful);
}

//*****************************************************************************
//  DESCRIPTION :
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void CARResynchronizationError(void)
{
    U8 u8ResynchroErrorCounterL;

    u8ResynchroErrorCounterL = mDATRead(U8Bit, AuthentPermanentResynchroFailCounter, Default);
    if (u8ResynchroErrorCounterL < cMaxAuthentPermanentResynchroFailCounter)
    {
        mDATWrite(U8Bit, AuthentPermanentResynchroFailCounter, (u8ResynchroErrorCounterL + 1), Default);
    }
}

//*****************************************************************************
//  DESCRIPTION :
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void CARPermanentAuthenticationResultNOK(void)
{
#ifdef X90_PROJECT
    CARPermanentAuthenticationResultNOK_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void CARPermanentAuthenticationResultNOK_Static(void)
{
#endif

    U8 u8AuthentErrorCounterL;

    u8AuthentErrorCounterL = mDATRead(U8Bit, AuthentPermanentFailCounter, Default);
    if (u8AuthentErrorCounterL < cMaxAuthentPermanentFailCounter)
    {
        mDATWrite(U8Bit, AuthentPermanentFailCounter, (u8AuthentErrorCounterL + 1), Default);
    }

    // Switch off LED_VERLOG
    mDATWrite(U8Bit, LedVerlogPattern, cDATSwitchOffVerlogPattern, Default);

    TOSStartTimer(&CarImmobilizerTimer);
}

//*****************************************************************************
//  DESCRIPTION :
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void CARPutImmobilizerAntennaInSleepModeAndStopPermanentAuthent(void)
{
    mDATWrite(U1Bit, DATTrpActiveTestMode, 0, Default);
    mDATWrite(U8Bit, LedVerlogPattern, cDATVehicleProtectedVerlogPattern, Default);
    mDATControl(Trp, cDATTrpSleep);
}

//*****************************************************************************
//  DESCRIPTION :
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL CARAuthentTimerElapsed(void)
{
    BOOL bTimerElapsedL;
    bTimerElapsedL = TOSIsTimerElapsed(&CarImmobilizerTimer, cTimeOut1sec);
    return bTimerElapsedL;
}

//*****************************************************************************
//  DESCRIPTION :
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void CARInitializePermanentAuthenticationTest(void)
{
    // Switch on LED_VERLOG
    mDATWrite(U8Bit, LedVerlogPattern, cDATSwitchOnVerlogPattern, Default);

    mDATWrite(U1Bit, DATTrpAuthentInLearningMode, 0, Default);
    mDATWrite(U1Bit, DATTrpActiveTestMode, 1, Default);
}

//*****************************************************************************
//  DESCRIPTION :
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
BOOL CARPermanentAuthentTestDeactivated(void)
{
    return (mPermAuthModeIsOff());
}

//*****************************************************************************
//  DESCRIPTION :
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//*****************************************************************************
void CARPermanentAuthenticationResultOK(void)
{
    // Switch on LED_VERLOG
    mDATWrite(U8Bit, LedVerlogPattern, cDATSwitchOnVerlogPattern, Default);
}
