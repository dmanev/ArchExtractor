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
// Component:    LAP_PAL
//               
// -----------------------------------------------------------------------------
// $Date:   Mar 11 2010 14:08:54  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_PAL/LAP_PAL.c-arc  $
// $Revision:   1.12  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_PAL/LAP_PAL.c-arc  $
// 
//    Rev 1.12   Mar 11 2010 14:08:54   adzhelp
// Cm006590, Cm006698: Code review corrections
// 
//    Rev 1.11   Jan 18 2010 14:50:22   adzhelp
// Cm006590, Cm006698: Door opened before reset is ignored in awake mode
// 
//    Rev 1.10   Dec 14 2009 11:02:18   amanevd
// Cm005566: Full Hardware Protection
// 
//    Rev 1.9   Dec 02 2009 11:10:22   adzhelp
// Cm006667: LAP_PAL can go to BCM sleep mode during alarm awake mode
// 
//    Rev 1.8   04 Nov 2009 15:57:18   akodzhh
// Cm006425: remove assert.
// 
//    Rev 1.7   04 Nov 2009 15:24:40   akodzhh
// Cm006562: Clear FlagRfLock after check is done.
// Cm006425: Disable of alarm by CALALPRI not terminate awake mode.
// 
//    Rev 1.6   Nov 04 2009 14:26:42   adzhelp
// Cm005566: Implementation of HW Protection functionality
// 
//    Rev 1.5   Oct 22 2009 14:45:32   amanevd
// Cm006425: QAC justification and UTest update
// 
//    Rev 1.4   06 Oct 2009 10:06:28   aangovt
// Cm006425: EEP_CALALPRI checks at active cycle are removed.
// 
//    Rev 1.3   06 Oct 2009 09:55:32   aangovt
// Cm006425: Corrections according to code review.
// 
//    Rev 1.2   Sep 25 2009 10:08:42   adzhelp
// Cm005225: Integration test changes
// 
//    Rev 1.1   Sep 14 2009 15:04:36   aangovt
// Cm005225: Clear Reset flag after alarm cycle
// 
//    Rev 1.0   Sep 09 2009 15:54:26   aangovt
// Initial revision.
//******************************************************************************

//------------------------------------------------------------------------------
// Body Identification
//------------------------------------------------------------------------------

#define LAP_PAL  "LAP_PAL"

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------

// This is an example:
// #include <system_file_name.h>
// #include "project_file_name.h"

#include "dat.h"
#include "deftypes.h"
#include "lib.h"
#include "tos.h"
#include "LAP_PAL.h"
#include "LAP_PAL.hgr"

//------------------------------------------------------------------------------
// Local constants
//------------------------------------------------------------------------------

// This is an example:
// #define cConstantName    ((tType)ConstantValue)

 

#define cWarningCycleDuration       ((tTOSTimer) (mTOSConvMsInTimerTick(2000UL)-(tTOSTimer) 1)) //2sec
#define cSilencePeriodDuration      ((tTOSTimer) (mTOSConvMsInTimerTick(10000UL)-(tTOSTimer) 1))//10sec
#define cWarningCycleRepetition     15
#define cEvenOrOddDevider            2
// Local macros
//------------------------------------------------------------------------------


// This is an example:
// #define mMacroName       (MacroDefinition)

#define cKeyIsRecognised            ((U16) 0x0001) //1
#define cKeyIsNotRecognised         ((U16) 0x0002)
#define cRfUnlockReceived           ((U16) 0x0004)
#define cRfLockReceived             ((U16) 0x0008)
#define cAlarmIsAwake               ((U16) 0x0010)
#define cAlarmIsActive              ((U16) 0x0020)
#define cFrontDoorsOpened           ((U16) 0x0040)
#define cRearDoorsOpened            ((U16) 0x0080)
#define cPowerIgnitionInhibited     ((U16) 0x0100)
#define cRfInhibited                ((U16) 0x0200)
#define cAuthenticationInhibited    ((U16) 0x0400)
#define cFirst30SecOfAlarmCycleDone ((U16) 0x0800)
#define cBcmCanSleep                ((U16) 0x1000) 
#define cAlarmTestModeRequested     ((U16) 0x2000) 

#define cMinNumberOfAlarmCycles         ((U8) 2)
#define cNumberOfAlarmCycles            ((U8) 3)
#define cMaxNumberOfAlarmCycles         ((U8) 10)


#define cAllDoorAreClosed                 ((U8)0x00U) // all doors are closed


#define cAlarmDeactivated                ((U8)0)
#define cAlarmAwake                      ((U8)1)
#define cAlarmActivated                  ((U8)2)

//------------------------------------------------------------------------------
// Local macros
//------------------------------------------------------------------------------

// This is an example:
// #define mMacroName       (MacroDefinition)

// Flag's access macros
#define mSetFlagKeyIsRecognised()       (u16AlaFlag |= cKeyIsRecognised)
#define mClearFlagKeyIsRecognised()     (u16AlaFlag &= (U16)(~cKeyIsRecognised))
#define mGetFlagKeyIsRecognised()       ((u16AlaFlag & cKeyIsRecognised) != 0)

#define mSetFlagKeyIsNotRecognised()    (u16AlaFlag |= cKeyIsNotRecognised)
#define mClearFlagKeyIsNotRecognised()  (u16AlaFlag &= (U16)(~cKeyIsNotRecognised))
#define mGetFlagKeyIsNotRecognised()    ((u16AlaFlag & cKeyIsNotRecognised) != 0)

#define mSetFlagRfUnlockReceived()      (u16AlaFlag |= cRfUnlockReceived)
#define mClearFlagRfUnlockReceived()    (u16AlaFlag &= (U16)(~cRfUnlockReceived))
#define mGetFlagRfUnlockReceived()      ((u16AlaFlag & cRfUnlockReceived) != 0)

#define mSetFlagRfLockReceived()        (u16AlaFlag |= cRfLockReceived)
#define mClearFlagRfLockReceived()      (u16AlaFlag &= (U16)(~cRfLockReceived))
#define mGetFlagRfLockReceived()        ((u16AlaFlag & cRfLockReceived) != 0)



#define mSetFlagAlarmIsAwake()       (u16AlaFlag |= cAlarmIsAwake)
#define mClearFlagAlarmIsAwake()     (u16AlaFlag &= (U16)(~cAlarmIsAwake))
#define mGetFlagAlarmIsAwake()       ((u16AlaFlag & cAlarmIsAwake) != 0)
#define mGetFlagAlarmIsNotAwake()       ((u16AlaFlag & cAlarmIsAwake) == 0)

#define mSetFlagAlarmIsActive()        (u16AlaFlag |= cAlarmIsActive)
#define mClearFlagAlarmIsActive()      (u16AlaFlag &= (U16)(~cAlarmIsActive))
#define mGetFlagAlarmIsActive()        ((u16AlaFlag & cAlarmIsActive) != 0)
#define mGetFlagAlarmIsNotActive()        ((u16AlaFlag & cAlarmIsActive) == 0)

#define mSetFlagFrontDoorsOpened()        (u16AlaFlag |= cFrontDoorsOpened)
#define mClearFlagFrontDoorsOpened()      (u16AlaFlag &= (U16)(~cFrontDoorsOpened))
#define mGetFlagFrontDoorsOpened()        ((u16AlaFlag & cFrontDoorsOpened) != 0)
#define mGetFlagFrontDoorsNotOpened()     ((u16AlaFlag & cFrontDoorsOpened) == 0)

#define mSetFlagRearDoorsOpened()        (u16AlaFlag |= cRearDoorsOpened)
#define mClearFlagRearDoorsOpened()      (u16AlaFlag &= (U16)(~cRearDoorsOpened))
#define mGetFlagRearDoorsOpened()        ((u16AlaFlag & cRearDoorsOpened) != 0)
#define mGetFlagRearDoorsNotInhibited()     ((u16AlaFlag & cRearDoorsOpened) == 0)

#define mSetFlagPowerIgnitionInhibited()        (u16AlaFlag |= cPowerIgnitionInhibited)
#define mClearFlagPowerIgnitionInhibited()      (u16AlaFlag &= (U16)(~cPowerIgnitionInhibited))
#define mGetFlagPowerIgnitionInhibited()        ((u16AlaFlag & cPowerIgnitionInhibited) != 0)
#define mGetFlagPowerIgnitionNotInhibited()     ((u16AlaFlag & cPowerIgnitionInhibited) == 0)

#define mSetFlagRfInhibited()     (u16AlaFlag |= cRfInhibited)
#define mClearFlagRfInhibited()   (u16AlaFlag &= (U16)(~cRfInhibited))
#define mGetFlagRfInhibited()     ((u16AlaFlag & cRfInhibited) != 0)
#define mGetFlagRfNotInhibited()  ((u16AlaFlag & cRfInhibited) == 0)

#define mSetFlagAuthenticationInhibited()            (u16AlaFlag |= cAuthenticationInhibited)
#define mClearFlagAuthenticationInhibited()          (u16AlaFlag &= (U16)(~cAuthenticationInhibited))
#define mGetFlagAuthenticationInhibited()            ((u16AlaFlag & cAuthenticationInhibited) != 0)
#define mGetFlagAuthenticationNotInhibited()            ((u16AlaFlag & cAuthenticationInhibited) == 0)
                                          
#define mSetFlagFirst30SecOfAlarmCycleDone()         (u16AlaFlag |= cFirst30SecOfAlarmCycleDone)
#define mClearFlagFirst30SecOfAlarmCycleDone()       (u16AlaFlag &= (U16)(~cFirst30SecOfAlarmCycleDone))
#define mGetFlagFirst30SecOfAlarmCycleDone()         ((u16AlaFlag & cFirst30SecOfAlarmCycleDone) != 0)
#define mGetFlagFirst30SecOfAlarmCycleNotDone()      ((u16AlaFlag & cFirst30SecOfAlarmCycleDone) == 0)

                                          
#define mSetFlagBcmCanSleep()                (u16AlaFlag |= cBcmCanSleep)
#define mClearFlagBcmCanSleep()              (u16AlaFlag &= (U16)(~cBcmCanSleep))
#define mGetFlagBcmCanSleep()                ((u16AlaFlag & cBcmCanSleep) != 0)
#define mGetFlagBcmCannotSleep()             ((u16AlaFlag & cBcmCanSleep) == 0)

#define mSetFlagAlarmTestModeRequested()     (u16AlaFlag |= cAlarmTestModeRequested)
#define mClearFlagAlarmTestModeRequested()   (u16AlaFlag &= (U16)(~cAlarmTestModeRequested))
#define mGetFlagAlarmTestModeRequested()     ((u16AlaFlag & cAlarmTestModeRequested) != 0)

//------------------------------------------------------------------------------
// Local types
//------------------------------------------------------------------------------

// This is an example:
// typedef Expression   tTypeName;

//------------------------------------------------------------------------------
// Local data
//------------------------------------------------------------------------------
static tTOSTimer  WarningCycleTimer;
static tTOSTimer  PauseCycleTimer;

static U16    u16AlaFlag;
static U8     u8WarningCyclesCounter = 0;
static U8     u8WarningTONCounter = 0;
static BOOL   bPauseBetweenCyclesHasDone = cFalse;
static BOOL   bResetDuringAlarmCycle = cFalse;

static BOOL bDisableFrontDoorActivation = cFalse;
static BOOL bDisableRearDoorActivation = cFalse;

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

// This is an example:
// static tType CmpFunctionName( tTypeArgument1 ArgumentName1, ... );

static MEM_TYPE BOOL ReadDoorsInput(void);

#ifdef X90_PROJECT
static MEM_TYPE void LAPPalLeaveStartingStepState_Static(void);
static MEM_TYPE BOOL LAPPalRfLock_Static(void);
static MEM_TYPE void LAPPalInitializeDisableMode_Static(void);
static MEM_TYPE void LAPPalInitializeStandbyMode_Static(void);
static MEM_TYPE BOOL LAPPalActivate_Static(void);
static MEM_TYPE BOOL LAPPalNewAlarmCycle_Static(void);
static MEM_TYPE BOOL LAPPalHornActivationFinished_Static(void);
static MEM_TYPE void LAPPalStartHorn_Static(void);
static MEM_TYPE void LAPPalStartHornPause_Static(void);
static MEM_TYPE void LAPPalEndOfAlarmCycle_Static(void);
#endif

//==============================================================================
//=========================== LOCAL FUNCTIONS ==================================

//==============================================================================
// DESCRIPTION : Door state
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
static MEM_TYPE BOOL ReadDoorsInput(void)
{
    BOOL bReturnValueL;
    bReturnValueL = cFalse;


    if((mDATRead(U1Bit, FR_DOORS_SW, Default) != 0) || (mDATRead(U1Bit, RR_DOORS_SW, Default) != 0))
    {
        bReturnValueL = cTrue;
    }
    

    return bReturnValueL;
}
/* [LOCAL_FUNCTIONS_END] */
//==============================================================================
//=========================== EXPORTED FUNCTIONS ===============================
//==============================================================================

//==============================================================================
// DESCRIPTION : Component initialization
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : 
//==============================================================================
void LAPPalInitialize(void)
{

    u16AlaFlag = 0;
    bPauseBetweenCyclesHasDone = cFalse;
    u8WarningTONCounter = 0;
    u8WarningCyclesCounter = 0; 
    bResetDuringAlarmCycle = cFalse;
}
//==============================================================================
// DESCRIPTION : Checks after reset
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : prsFS_ASA-430, prsFS_ASA-432, prsFS_ASA-435
//==============================================================================
void LAPPalLeaveStartingStepState(void)
{
#ifdef X90_PROJECT
    LAPPalLeaveStartingStepState_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPPalLeaveStartingStepState_Static(void)
{
#endif

    U8 u8AlarmStateAfterResetL;
    
    u16AlaFlag = 0;
    bPauseBetweenCyclesHasDone = cFalse;
    u8WarningTONCounter = 0;
    u8WarningCyclesCounter = 0; 
    
    TOSSeqActivateGraph(cTOSSeqGraphIdPerimeterAlarmManagement);
    u8AlarmStateAfterResetL = mDATRead(U8Bit, EEP_PerimeterAlarmState, Defaut);
    
    switch(u8AlarmStateAfterResetL)
    {
    case cAlarmDeactivated:

        mSetFlagBcmCanSleep();
        break;
    case cAlarmAwake:
        //QACJ 0277: aangovt: Clear bit operation
        mSetFlagBcmCanSleep();
        mSetFlagAlarmIsAwake();

        // Disable activation by a door that has been open before reset
        if (mDATRead(U1Bit, FR_DOORS_SW, Immediate) != cFalse)
        {
            bDisableFrontDoorActivation = cTrue;
            // rising edge expected after DIN filtration
        }
        if (mDATRead(U1Bit, RR_DOORS_SW, Immediate) != cFalse)
        {
            bDisableRearDoorActivation = cTrue;
            // rising edge expected after DIN filtration
        }
        break;
    case cAlarmActivated:
        bResetDuringAlarmCycle = cTrue;
        //QACJ 0277: aangovt: Clear bit operation
        mClearFlagBcmCanSleep();
        mSetFlagAlarmIsActive();
        break;
    //CCOV: aangovt: Cannot be covered because this default case rises explicit assert
    default:
        mLIBassert(cFalse);
        break;
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
void LAPPalIsAnybodyMaintainActiveState(void)
{
    if (mGetFlagBcmCannotSleep())
    {
        TOSWriteSignal(cTOSSignalSomebodyMaintainActiveState);
    }
}
//==============================================================================
// DESCRIPTION : Key Authentication
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
void LAPPalKeyIsAuthenticated(void)
{
    mSetFlagKeyIsRecognised(); 
    //QACJ 0277: aangovt: Clear bit operation
    mClearFlagKeyIsNotRecognised();
}

//==============================================================================
// DESCRIPTION : Rf Lock
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
void LAPPalLockFromTheOutside(void)
{
    mSetFlagRfLockReceived();
    //QACJ 0277: aangovt: Clear bit operation
    mClearFlagRfUnlockReceived();
}

//==============================================================================
// DESCRIPTION : Rf unlock
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
void LAPPalUnlockFromTheOutside(void)
{
    mSetFlagRfUnlockReceived();
    //QACJ 0277: aangovt: Clear bit operation
    mClearFlagRfLockReceived();
}
//==============================================================================
// DESCRIPTION : Condition for awake state of alarm
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : prsFS_ASA-410, prsFS_ASA-415
//==============================================================================
BOOL LAPPalRfLock(void)
{
#ifdef X90_PROJECT
    return LAPPalRfLock_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL LAPPalRfLock_Static(void)
{
#endif

    BOOL bReturnValueL = cFalse;
    BOOL bDoorStatusL;
    bDoorStatusL = ReadDoorsInput();
    
    if ((mGetFlagRfLockReceived()) && (bDoorStatusL == 0))
    {
        bReturnValueL = cTrue;
    }
    // Cm006562: perimeter alarm state during RKE lock and Door open.
    //QACJ 0277: aangovt: Clear bit operation
    mClearFlagRfLockReceived();
    
    return bReturnValueL;
}
//==============================================================================
// DESCRIPTION : Deactivation of alarm
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
void LAPPalInitializeDisableMode(void)
{
#ifdef X90_PROJECT
    LAPPalInitializeDisableMode_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPPalInitializeDisableMode_Static(void)
{
#endif

    
 
    mDATWrite(U1Bit, HORN_RL,0, Default);
    mDATWrite(U1Bit, HazardAlarmRequested, 0, Default);
 

    bResetDuringAlarmCycle = cFalse;
    //QACJ 0277: aangovt: Clear bit operation 
    mClearFlagFrontDoorsOpened();
    //QACJ 0277: aangovt: Clear bit operation
    mClearFlagRearDoorsOpened();
    u8WarningCyclesCounter = 0;
    //QACJ 0277: aangovt: Clear bit operation
    mClearFlagAlarmIsActive();
    //QACJ 0277: aangovt: Clear bit operation
    mClearFlagAlarmIsAwake();
    //QACJ 0277: aangovt: Clear bit operation
    mClearFlagKeyIsRecognised();
    //QACJ 0277: aangovt: Clear bit operation
    mClearFlagRfUnlockReceived();
    mDATWrite(U8Bit, EEP_PerimeterAlarmState, cAlarmDeactivated, Immediate);
    mSetFlagBcmCanSleep();
    u8WarningTONCounter = 0;
}
//==============================================================================
// DESCRIPTION : Alarm in awake mode
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : prsFS_ASA-410
//==============================================================================
void LAPPalInitializeStandbyMode(void)
{
#ifdef X90_PROJECT
    LAPPalInitializeStandbyMode_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPPalInitializeStandbyMode_Static(void)
{
#endif

    bResetDuringAlarmCycle = cFalse;
    //QACJ 0277: aangovt: Clear bit operation
    mClearFlagAlarmIsActive();
    mSetFlagAlarmIsAwake();
    //QACJ 0277: aangovt: Clear bit operation
    mSetFlagBcmCanSleep();
    //QACJ 0277: aangovt: Clear bit operation
    mClearFlagRfLockReceived();
    mDATWrite(U8Bit, EEP_PerimeterAlarmState, cAlarmAwake, Immediate);
}
//==============================================================================
// DESCRIPTION : Condition for deactivation of alarm
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : prsFS_ASA-410, prsFS_ASA-417, prsFS_ASA-419
//==============================================================================
BOOL LAPPalRfUnlockOrKeyIsRecognised(void)
{
    return ((BOOL)(  mGetFlagKeyIsRecognised() 
          || ( mGetFlagRfUnlockReceived() )));
}
//==============================================================================
// DESCRIPTION : Configuration parameter of alarm is changed
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : prsFS_ASA-456
//==============================================================================
BOOL LAPPalAlarmInhibited(void)
{
    BOOL bReturnValueL = cFalse;
   
    if(((BOOL)mGetFlagAlarmIsActive() == cFalse ) && ((BOOL)mGetFlagAlarmIsAwake() == cFalse))
    {
        bReturnValueL = (mDATRead(U1Bit, EEP_CALALPRI, Default) == cFalse);
    }

    return bReturnValueL;
}
//==============================================================================
// DESCRIPTION : Pause between 2 HORN sequences
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none 
//
// DESIGN INFORMATION : prsFS_ASA-407
//==============================================================================
BOOL LAPPAlHornPauseElapsed(void)
{
    BOOL bTimerElapsedL;
    bTimerElapsedL = TOSIsTimerElapsed(&PauseCycleTimer, cSilencePeriodDuration);
    return bTimerElapsedL; 
}
//==============================================================================
// DESCRIPTION : Checks for alarm activation
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none 
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
BOOL LAPPalActivate(void)
{
#ifdef X90_PROJECT
    return LAPPalActivate_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL LAPPalActivate_Static(void)
{
#endif

    BOOL bReturnValueL = cFalse;
    BOOL bFlagActivateAlarmL; 

    

    if(u8WarningCyclesCounter == 0)
    {
        bPauseBetweenCyclesHasDone = cTrue;
    }

    bFlagActivateAlarmL = (BOOL)  (((BOOL)mGetFlagRearDoorsOpened() == cTrue) 
        || ((BOOL)mGetFlagFrontDoorsOpened() == cTrue));


    if ((u8WarningCyclesCounter < cNumberOfAlarmCycles) &&
        ((bFlagActivateAlarmL == cTrue) || (bResetDuringAlarmCycle == cTrue)) && (bPauseBetweenCyclesHasDone == cTrue) )
    {
        bReturnValueL = cTrue;
    }


    if (bReturnValueL == cTrue)
    {
        mDATWrite(U8Bit, EEP_PerimeterAlarmState, cAlarmActivated, Immediate);
    }

    
    return bReturnValueL;
}
//==============================================================================
// DESCRIPTION : Start 10sec  pause between 2 alarm cycles
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none 
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
BOOL LAPPalNewAlarmCycle(void)
{
#ifdef X90_PROJECT
    return LAPPalNewAlarmCycle_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL LAPPalNewAlarmCycle_Static(void)
{
#endif
    
    BOOL bReturnValueL = cFalse;
    BOOL bFlagActivateAlarmL = cFalse;

    if(((BOOL)mGetFlagRearDoorsOpened() == cTrue) 
        || ((BOOL) mGetFlagFrontDoorsOpened() == cTrue))
    {
        bFlagActivateAlarmL = cTrue;
    }


    if((u8WarningCyclesCounter > 0) && (u8WarningCyclesCounter < cNumberOfAlarmCycles) && (bFlagActivateAlarmL == cTrue))
    {
        bReturnValueL = cTrue;
    }


    if (bReturnValueL == cTrue)
    {
        mDATWrite(U8Bit, EEP_PerimeterAlarmState, cAlarmActivated, Immediate);
    }




    return bReturnValueL;
}
//==============================================================================
// DESCRIPTION : Horn activation continues
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none 
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
BOOL LAPPalHornActivationContinues(void)
{
    BOOL bReturnValueL = cFalse;
    BOOL bTimerElapsedL;
    bTimerElapsedL = TOSIsTimerElapsed(&WarningCycleTimer, cWarningCycleDuration);

    if((bTimerElapsedL) && (u8WarningTONCounter < cWarningCycleRepetition))
    {
        bReturnValueL = cTrue;
    }
    return bReturnValueL;
}
//==============================================================================
// DESCRIPTION : Horn activation finished
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none 
//
// DESIGN INFORMATION : prsFS_ASA-428
//==============================================================================
BOOL LAPPalHornActivationFinished(void)
{
#ifdef X90_PROJECT
    return LAPPalHornActivationFinished_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL LAPPalHornActivationFinished_Static(void)
{
#endif

    BOOL bReturnValueL = cFalse;
    BOOL bTimerElapsedL;
    bTimerElapsedL = TOSIsTimerElapsed(&WarningCycleTimer, cWarningCycleDuration);

    if((bTimerElapsedL) && (cWarningCycleRepetition == u8WarningTONCounter) 
        && ((BOOL)mGetFlagFirst30SecOfAlarmCycleNotDone() == cTrue))
    {
        bReturnValueL = cTrue;
    }
    

    return bReturnValueL;
}
//==============================================================================
// DESCRIPTION : Wait for new alarm cycle
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none 
//
// DESIGN INFORMATION : prsFS_ASA-423
//==============================================================================
BOOL LAPPalNextAlarmCycle(void)
{
    BOOL bReturnValueL = cFalse;
    BOOL bTimerElapsedL;
    bTimerElapsedL = TOSIsTimerElapsed(&WarningCycleTimer, cWarningCycleDuration);
    
    if ((bTimerElapsedL) && (cWarningCycleRepetition == u8WarningTONCounter) )
    {
        bReturnValueL = cTrue;
    }
     
    
    
    return bReturnValueL;
}
//==============================================================================
// DESCRIPTION : Start Horn and Warnings
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : prsFS_ASA-406,  prsFS_ASA-421
//==============================================================================
void LAPPalStartHorn(void)
{
#ifdef X90_PROJECT
    LAPPalStartHorn_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPPalStartHorn_Static(void)
{
#endif

    u8WarningTONCounter++;
    
    //QACJ 0277: aangovt: Clear bit operation
    mClearFlagBcmCanSleep();
    //QACJ 0277: aangovt: Clear bit operation
    mClearFlagAlarmIsAwake();
    mSetFlagAlarmIsActive();
    
  
    
    if ((u8WarningTONCounter == 1)) 
    {
        mDATWrite(U1Bit, HazardAlarmRequested, 1, Default);
    }
    

    if (  (u8WarningTONCounter % cEvenOrOddDevider) == 1 )
    {
        mDATWrite(U1Bit, HORN_RL,1, Default);
    }
    else
    {
        mDATWrite(U1Bit, HORN_RL,0, Default);
    }
    TOSStartTimer(&WarningCycleTimer);

}
//==============================================================================
// DESCRIPTION : Start 10 sec pause between 2 horn sequences or 2 alarm cycles
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : prsFS_ASA-406, prsFS_ASA-408
//==============================================================================
void LAPPalStartHornPause(void)
{
#ifdef X90_PROJECT
    LAPPalStartHornPause_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPPalStartHornPause_Static(void)
{
#endif


    if (bPauseBetweenCyclesHasDone == cTrue)
    {
        mSetFlagFirst30SecOfAlarmCycleDone();
    }
    
    //QACJ 0277: aangovt: Clear bit operation
    mClearFlagBcmCanSleep();
    //QACJ 0277: aangovt: Clear bit operation
    mClearFlagAlarmIsAwake();
    mSetFlagAlarmIsActive();
    u8WarningTONCounter = 0;
    
    mDATWrite(U1Bit, HORN_RL, 0, Default);
    
    bPauseBetweenCyclesHasDone = cTrue;
    TOSStartTimer(&PauseCycleTimer);
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
void LAPPalRising_RR_DOORS_SW(void)
{
    if( (BOOL)mGetFlagAlarmIsAwake() == cTrue)
    {
        if (bDisableRearDoorActivation == cFalse)
        {
            mSetFlagRearDoorsOpened();
        }
        else
        {
            // rising edge caused by door opened before/during reset
            bDisableRearDoorActivation = cFalse;
        }
    }    
}
//==============================================================================
// DESCRIPTION : Rising edge of front doors
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : prsFS_ASA-426, prsFS_ASA-456
//==============================================================================
void LAPPalRising_FR_DOORS_SW(void)
{
    if( (BOOL)mGetFlagAlarmIsAwake() == cTrue)
    {
        if (bDisableFrontDoorActivation == cFalse)
        {
            mSetFlagFrontDoorsOpened();
        }
        else
        {
            // rising edge caused by door opened before/during reset
            bDisableFrontDoorActivation = cFalse;
        }
    }
}
//==============================================================================
// DESCRIPTION : Leave active state
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
void LAPPalLeaveActiveState(void)
{
    TOSSeqDeactivateGraph(cTOSSeqGraphIdPerimeterAlarmManagement);
    bDisableFrontDoorActivation = cFalse;
    bDisableRearDoorActivation = cFalse;
}
//==============================================================================
// DESCRIPTION : Enter active state 
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
void LAPPalEnterActiveState(void)
{
    U8 u8GraphStateL; 

    u8GraphStateL = (U8) TOSSeqGraphState(cTOSSeqGraphIdPerimeterAlarmManagement);
    if (u8GraphStateL == cTOSSeqInactiveGraph)
    {
        TOSSeqActivateGraph(cTOSSeqGraphIdPerimeterAlarmManagement);
    }
}
//==============================================================================
// DESCRIPTION : End of alarm cycle
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none 
//
// DESIGN INFORMATION : prsFS_ASA-428, prsFS_ASA-454
//==============================================================================
void LAPPalEndOfAlarmCycle(void)
{
#ifdef X90_PROJECT
    LAPPalEndOfAlarmCycle_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPPalEndOfAlarmCycle_Static(void)
{
#endif
    
    mDATWrite(U1Bit, HORN_RL,0, Default);
    mDATWrite(U1Bit, HazardAlarmRequested, 0, Default);        
    bResetDuringAlarmCycle = cFalse;
    u8WarningCyclesCounter++;
    u8WarningTONCounter = 0;
    //QACJ 0277: aangovt: Clear bit operation
    mClearFlagFrontDoorsOpened();
    //QACJ 0277: aangovt: Clear bit operation
    mClearFlagRearDoorsOpened();
    //QACJ 0277: aangovt: Clear bit operation
    mClearFlagFirst30SecOfAlarmCycleDone();
    bPauseBetweenCyclesHasDone = cFalse;

    mDATWrite(U8Bit, EEP_PerimeterAlarmState, cAlarmAwake, Immediate);
}

