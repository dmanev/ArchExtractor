#ifndef _QAC_
//******************************************************************************
// Company:      Johnson Controls Inc.
// -----------------------------------------------------------------------------
// Copyright:    This software is JCI property.
//               Duplication or disclosure without JCI written authorization
//               is prohibited.
// -----------------------------------------------------------------------------
// Project:      RSA_X90_BCM
// Language:     C
// -----------------------------------------------------------------------------
// Component:    LAP_ALA
//               After sales alarm
// -----------------------------------------------------------------------------
// $Date:   Mar 04 2010 17:48:54  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_ALA/LAP_ALA.c-arc  $
// $Revision:   1.22  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_ALA/LAP_ALA.c-arc  $
// 
//    Rev 1.22   Mar 04 2010 17:48:54   adzhelp
// Cm006692: Trunk and hood removed from byte 2 pattern
// 
//    Rev 1.21   Feb 23 2010 14:24:10   adzhelp
// Cm007607: Active sleep state maintained after reset
// 
//    Rev 1.20   Oct 12 2009 16:03:28   akodzhh
// Cm005776, Cm005777: Comments added - QAC justification and CR 2.0 fix.
// 
//    Rev 1.19   Oct 01 2009 10:56:24   adzhelp
// Cm005776, Cm005777: Check for activation of main graph added
// 
//    Rev 1.18   Sep 29 2009 17:13:38   aangovt
// Cm005776, Cm005777: Check for configuration parameter is added
// 
//    Rev 1.17   Sep 25 2009 10:20:00   adzhelp
// Cm005776, Cm005777: Integration test changes
// 
//    Rev 1.16   Sep 15 2009 17:11:00   aangovt
// Cm005739, Cm005776, Cm005777: New graph is added for case of reset. Reading of EEP_CAR_SECURE flag in EnterActiveState is removed.
// 
//    Rev 1.15   09 Sep 2009 11:41:22   aangovt
// Cm005820: After change of doors state door state command is sent, only  if car is secured.
// 
//    Rev 1.14   Aug 25 2009 18:07:18   aangovt
// Cm005188: Code optimization - three controls, consumed by one function
// 
//    Rev 1.13   25 Aug 2009 12:28:34   aangovt
// Cm005188: Checks for doors falling edges is added.
// 
//    Rev 1.12   13 Jul 2009 09:44:30   aangovt
// Cm005188: Sleeping authorisation is added; update acording to Cm005189, Cm005431 and code review.
// 
//    Rev 1.11   May 18 2009 17:46:48   aangovt
// Update according to QAC analyse
// 
//    Rev 1.10   May 05 2009 18:13:54   aangovt
// Cm004913 - EEP_CALALARM verification at EnterActiveState is removed.
// 
//    Rev 1.9   May 05 2009 15:02:30   aangovt
// Cm004913 - EEP_CALALARM verification for sending of ARM command and DOOR STATUS is added.
// 
//    Rev 1.8   Apr 28 2009 16:40:56   aangovt
// Cm003271 Update according to UTEST and QAC analyse
// 
//    Rev 1.7   Apr 25 2009 17:17:20   aangovt
// Cm003271 Integration test corrections
// 
//    Rev 1.6   Apr 17 2009 19:35:10   aangovt
// Cm003271 - Update according to diagnostic at EnterActiveState
// 
//    Rev 1.5   Apr 17 2009 10:09:17   aangovt
// Cm003271 - Update according to prsFS_ASA-265 
// 
//    Rev 1.4   Apr 16 2009 10:48:12   aangovt
// Cm003271 - EEP parameter CAR_SECURE is used instead controls 
// 
//    Rev 1.3   Apr 14 2009 09:27:39   aangovt
// Cm003271 - checks for diagnostic session is added. 
// 
//    Rev 1.2   Mar 09 2009 13:07:21   aangovt
// Cm003271  Implementation of the Alarm functionality  
// 
//    Rev 1.1   Feb 20 2009 16:16:47   aangovt
// Cm003271  Implementation of the Alarm functionality 
// 
//    Rev 1.0   Feb 10 2009 13:55:09   aangovt
// Initial revision. 
//******************************************************************************
#endif

//------------------------------------------------------------------------------
// Body Identification
//------------------------------------------------------------------------------
#define lap_ala  "lap_ala"

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//
// #include <system_file_name.h>
// #include "project_file_name.h"
//------------------------------------------------------------------------------
#include "dat.h"
#include "deftypes.h"
#include "lib.h"
#include "tos.h"
#include "LAP_ALA.h"
#include "LAP_ALA.hgr"
 

//------------------------------------------------------------------------------
// Local constants
//
// #define cConstantName   ((tType) ConstantValue)
//------------------------------------------------------------------------------

// - 1 is because TOSTimerAlapsed checks only  Delay > Timeout

#define cPauseBetweenArmCommandAndDisarmCommand               ( mTOSConvMsInTimerTick((U32)180UL) - (tTOSTimer)1U)  
// pause is 180 ms,  because 10ms is  door state timeout and 10ms for true state

#define cPauseBetweenArmADisarmCommandAndDoorStateCommand      mTOSConvMsInTimerTick((U32)10UL - (tTOSTimer)1U)
#define cInhibit                                   0
#define cAuthorize                                 1


#define cDATAlaCmdFrameLenght             ((U8)0x04U)

#define cIgnStateIsOn                     ((U8)0x06U)

#define cTwoTimesSent                     ((U8) 2)

#define cByte0OfFrame                     ( 0)
#define cByte1OfFrame                     ( 1)
#define cByte2OfFrame                     ( 2)
#define cByte3OfFrame                     ( 3)

#define cAllDoorAreClosed                 ((U8)0x00U) // all doors are closed
#define cFrontDoorsOpened                 ((U8)0x03U) // Driver door and front passenger door
#define cRearDoorsOpened                  ((U8)0x0CU)  // includes rear passenger doors(left and right)

#define cArmCommand                       ((U8)0xC9U) // Arm command
#define cDisarmCommand                    ((U8)0xC6U) // Disarm command
#define cDoorStatusCommand                ((U8)0xDCU) // Door State

//------------------------------------------------------------------------------
// Local macros
//
// #define mMacroName   (MacroDefinition)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Local types
//
// typedef Expression    tTypeName;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Data prefix
//
// unsigned int {u8,u16,u32} / signed int {s8,s16,s32} 
// register size unsigned int {r} / float {f32,f64}  / s for struct 
//
// -----------------------------------------------------------------------------
// Local data
//
// static  tType   u8VariableName;  
// static  tType*  pu8VariableName; 
//------------------------------------------------------------------------------
static tTOSTimer  PauseBetweenTwoMessagesTimer;
static tTOSTimer  PauseBetweenTwoMessagesValue;



static U8     u8PreviousDoorState    = cAllDoorAreClosed;
// Bit 0 : Driver door
// Bit 1 : front passenger door
// Bit 2 : passenger rear left
// Bit 3 : passenger rear right
// Bit 4 : trunk

static BOOL   bSleepingAuthorisation = cTrue;
static BOOL   bSetAlarmIsRequested   = cFalse;
static BOOL   bUnsetAlarmIsRequested = cFalse;
static BOOL   bArmFollowedByDisarm   = cFalse;      // flag for ARM command followed by DISARM or opposite
static BOOL   bMemoIgnState          = cFalse;
static U8     u8LastCommandSent      = 0;
static BOOL   bFallingEdgeForDS      = cFalse;     // flag for falling edge of Power Ignition or doors for DOOR STATE command
static BOOL   bStateAfterReset;
 

 
//------------------------------------------------------------------------------
// Constant local data
//
// static const tType  VariableName;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported data
//
// tType   u8LAYCmpVariableName; (LAY: 3 characters to identify the layer)
// tType*  pu8LAYCmpVariableName;(Cmp: 3 characters to identify the component)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Constant exported data
//
//             (LAY: 3 characters to identify the layer)
//             (Cmp: 3 characters to identify this component)
// 
// const tType   LAYCmpVariableName;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Local function prototypes
// 
// static tTypeRetour FunctionName(tTypeArgument1 ArgumentName1, ... );
//------------------------------------------------------------------------------
static U8 ReadDoorsInput(void);
static BOOL DoorStateHasChanged(void);
static void ChecksumCalculation(void);

#ifdef X90_PROJECT
static MEM_TYPE void LAPAlaSendArmCommand_Static(void);
static MEM_TYPE BOOL LAPAlaDoorStateCommandIsRequested_Static(void);
static MEM_TYPE BOOL LAPAlaArmFollowedByDisarm_Static(void);
static MEM_TYPE BOOL LAPAlaPauseIsFinished_Static(void);
static MEM_TYPE void LAPAlaSendDisarmCommand_Static(void);
static MEM_TYPE void LAPAlaSendDoorState_Static(void);
static MEM_TYPE void LAPAlaDiagEnable_Static(void);
static MEM_TYPE void LAPAlaDiagDisable_Static(void);
#endif

//==============================================================================
//=========================== LOCAL FUNCTIONS ==================================
//==============================================================================

// [LOCAL_FUNCTIONS_END] 
//==============================================================================
// DESCRIPTION : 
//
// PARAMETERS (Type,Name,Min,Max) :   Present Door State
//
// RETURN VALUE :   U8
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
static U8 ReadDoorsInput(void)
{
    U8 u8ReturnValueL;
    u8ReturnValueL = cAllDoorAreClosed;
 
    if(mDATRead(U1Bit, FR_DOORS_SW, Default) != 0)
    {
        u8ReturnValueL |= cFrontDoorsOpened;
    }
    if(mDATRead(U1Bit, RR_DOORS_SW, Default) != 0)
    {
        u8ReturnValueL |= cRearDoorsOpened;
    }

    return u8ReturnValueL;
}
//==============================================================================
// DESCRIPTION : check for doors state changes
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   BOOL
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
static BOOL DoorStateHasChanged(void)
{
    U8    u8ActualDoorStateL;
    BOOL  bResultL;  
	
     
    u8ActualDoorStateL = ReadDoorsInput();
	
    if (u8ActualDoorStateL == u8PreviousDoorState) 
    {
        bResultL = cFalse;
    }
    else
    {
        bResultL = cTrue;
    }
    return bResultL;
	
}
//==============================================================================
// DESCRIPTION : Checksum Calculation for 4th byte of alarm command
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : Byte 4 = sum Ai x 2^(n-i) => for n=3 : Byte 4 = Value_of_Byte1*4 + Value_of_Byte2*2 + Value_of_Byte3
//                               i=1
//prsFS_ASA-386, prsFS_ASA-387, prsFS_ASA-388
//==============================================================================
static void ChecksumCalculation(void)
{
    U8  u8ChecksumL;
    U8  u8CounterL;
	
    u8ChecksumL = 0;
    for (u8CounterL=0; u8CounterL < cByte3OfFrame; u8CounterL++)
    {
        u8ChecksumL += (U8) (mDATReadTable(U8Bit, AlaCmdFrame, u8CounterL, Default) << (U8)(cDATAlaCmdFrameLenght - u8CounterL - cTwoTimesSent));
    }
	
    mDATWriteTable(U8Bit, AlaCmdFrame, cByte3OfFrame, u8ChecksumL, Default);
}

//==============================================================================

//=============================================================================
//============================ EXPORTED FUNCTIONS =============================
//=============================================================================
//==============================================================================
// DESCRIPTION : Pause between  two alarm messages
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
void LAPAlaStartPauseBetweenMessage(void)
{
    TOSStartTimer(&PauseBetweenTwoMessagesTimer);
}
//==============================================================================
// DESCRIPTION : Door state command request
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   BOOL
//
// DESIGN INFORMATION : prsFS_ASA-262, prsFS_ASA-263
//==============================================================================
BOOL LAPAlaDoorStateCommandIsRequested(void)
{
#ifdef X90_PROJECT
    return LAPAlaDoorStateCommandIsRequested_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL LAPAlaDoorStateCommandIsRequested_Static(void)
{
#endif

    BOOL bReturnValueL = cFalse;
    BOOL bDoorStateHasChangedL;
    BOOL bCarSecuredL; 

    bCarSecuredL = mDATRead(U1Bit, EEP_CAR_SECURE, Default);

  
    bDoorStateHasChangedL = DoorStateHasChanged();
    if( (bMemoIgnState != (mDATRead(U1Bit,PWR_IGN,Defaut)))  
    || 	 ((bDoorStateHasChangedL == cTrue) && (bCarSecuredL == cTrue) ))
    {
        bReturnValueL = cTrue;
        PauseBetweenTwoMessagesValue = cPauseBetweenArmADisarmCommandAndDoorStateCommand;
        u8LastCommandSent = cDoorStatusCommand;
    }
    
    bMemoIgnState = mDATRead(U1Bit, PWR_IGN, Defaut);
    u8PreviousDoorState = ReadDoorsInput();


    return bReturnValueL;

}
//==============================================================================
// DESCRIPTION : Arm command followed of Disarm and vice versa
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   BOOL
//
// DESIGN INFORMATION : _ReqId_ :  prsFS_ASA-370
//==============================================================================
BOOL LAPAlaArmFollowedByDisarm(void)
{
#ifdef X90_PROJECT
    return LAPAlaArmFollowedByDisarm_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL LAPAlaArmFollowedByDisarm_Static(void)
{
#endif

    BOOL bReturnValueL = cFalse;
    // ARM command is followed by DISARM command - timeout is 200ms 
    //(10ms for door state request and 190 if after arm is disarm command)

    // DISARM command is followed by ARM command - timeout is 200ms 
    //(10ms for door state request and 190 if after disarm is  arm command)

    if(  (u8LastCommandSent == cArmCommand) 
        &&
        (bUnsetAlarmIsRequested == cTrue)
      )
    {
        PauseBetweenTwoMessagesValue = cPauseBetweenArmCommandAndDisarmCommand;
        bReturnValueL = cTrue;
        bArmFollowedByDisarm = cFalse;
    }

    if( (u8LastCommandSent == cDisarmCommand) 
       &&
       (bSetAlarmIsRequested  == cTrue)
       )
    {
        PauseBetweenTwoMessagesValue = cPauseBetweenArmCommandAndDisarmCommand;
        bReturnValueL = cTrue;
        bArmFollowedByDisarm = cFalse;
    }
      
    return bReturnValueL;
}
//==============================================================================
// DESCRIPTION : Pause is finished
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   BOOL
//
// DESIGN INFORMATION :prsFS_ASA-367, prsFS_ASA-368, prsFS_ASA-369, prsFS_ASA-370
//==============================================================================
BOOL LAPAlaPauseIsFinished(void)
{
#ifdef X90_PROJECT
    return LAPAlaPauseIsFinished_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL LAPAlaPauseIsFinished_Static(void)
{
#endif

    BOOL  bTempoElapsedL;
    
    bTempoElapsedL = TOSIsTimerElapsed(&PauseBetweenTwoMessagesTimer, PauseBetweenTwoMessagesValue);
    return bTempoElapsedL;
}
//==============================================================================
// DESCRIPTION : Sending of Arm Command to the AFS Alarm ACU, through the 'Cobra' serial link
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION :prsFS_ASA-375, prsFS_ASA-376, prsFS_ASA-377, prsFS_ASA-378, prsFS_ASA-379,prsFS_ASA-386, prsFS_ASA-387, prsFS_ASA-388
// prsFS_ASA-251 - BCM Reset - Component Activation, there is no special input for Reset Counter from EEP
//==============================================================================
void LAPAlaSendArmCommand(void)
{
#ifdef X90_PROJECT
    LAPAlaSendArmCommand_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPAlaSendArmCommand_Static(void)
{
#endif
    if ( mDATRead(U1Bit, EEP_CALALARM, Default) == cAuthorize)
    {    
        // Forbid the sleep until the end of the emission
        bSleepingAuthorisation = cFalse;


        // Clear the new command request;
        bSetAlarmIsRequested  = cFalse;

        // Set the data to send to the alarm
        mDATWriteTable(U8Bit, AlaCmdFrame, cByte0OfFrame, cArmCommand, Default);
        mDATWriteTable(U8Bit, AlaCmdFrame, cByte1OfFrame, (U8)mDATReadTable(U8Bit,EEP_VehicleIdentifierNumber,1,Default) , Default);
        mDATWriteTable(U8Bit, AlaCmdFrame, cByte2OfFrame, (U8)mDATReadTable(U8Bit,EEP_VehicleIdentifierNumber,0,Default), Default);
        ChecksumCalculation(); // This function calculate the checksum 
                             // AND set the byte 3 of the buffer AlaCmdFrame

        // Send the message to the alarm
        mDATControl(DATAla, SendCommand);
        // Sets type of  sent command
        u8LastCommandSent = cArmCommand;
        // Pause after Arm command will be 10ms - next command is DOOR STATUS
        PauseBetweenTwoMessagesValue = cPauseBetweenArmADisarmCommandAndDoorStateCommand;
        // Checks  how many times Command is sent
    }
    else
    {
        bSleepingAuthorisation = cTrue;
    }
 
 
}
//==============================================================================
// DESCRIPTION : Sending of Disarm Command to the AFS Alarm ACU, through the 'Cobra' serial link
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION :prsFS_ASA-255, prsFS_ASA-256, prsFS_ASA-375, prsFS_ASA-376, prsFS_ASA-377, prsFS_ASA-378, prsFS_ASA-379, prsFS_ASA-386, prsFS_ASA-387, prsFS_ASA-388
// prsFS_ASA-252 - BCM Reset - Component Activation, there is no special input for Reset Counter from EEP
//==============================================================================
void LAPAlaSendDisarmCommand(void)
{
#ifdef X90_PROJECT
    LAPAlaSendDisarmCommand_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPAlaSendDisarmCommand_Static(void)
{
#endif

    if ( mDATRead(U1Bit, EEP_CALALARM, Default) == cAuthorize)
    {

        // Forbid the sleep until the end of the emission
        bSleepingAuthorisation = cFalse;



        // Clear the new command request
        bUnsetAlarmIsRequested  = cFalse;

        // Set the data to send to the alarm
        mDATWriteTable(U8Bit, AlaCmdFrame, cByte0OfFrame, cDisarmCommand, Default);
        mDATWriteTable(U8Bit, AlaCmdFrame, cByte1OfFrame, mDATReadTable(U8Bit,EEP_VehicleIdentifierNumber,1,Default) , Default);
        mDATWriteTable(U8Bit, AlaCmdFrame, cByte2OfFrame, mDATReadTable(U8Bit,EEP_VehicleIdentifierNumber,0,Default), Default);
        ChecksumCalculation(); // This function calculate the checksum 
                         // AND set the byte 3 of the buffer AlaCmdFrame

        // Send the message to the alarm
        mDATControl(DATAla, SendCommand);


        // Sets type of  sent command
        u8LastCommandSent = cDisarmCommand;
        // Pause after Disarm command will be 10ms - next command is DOOR STATUS
        PauseBetweenTwoMessagesValue = cPauseBetweenArmADisarmCommandAndDoorStateCommand  ;
        // Checks  how many times Command is sent
   
    }
    else
    {
        bSleepingAuthorisation = cTrue;
    }


}
//==============================================================================
// DESCRIPTION : Sending of DOOR STATE to the AFS Alarm ACU, through the 'Cobra' serial link
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : prsFS_ASA-264, prsFS_ASA-384, prsFS_ASA-385
//==============================================================================
void LAPAlaSendDoorState(void)
{
#ifdef X90_PROJECT
    LAPAlaSendDoorState_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPAlaSendDoorState_Static(void)
{
#endif

    U8 u8DoorStatusL;

    if ( mDATRead(U1Bit, EEP_CALALARM, Default) == cAuthorize)
    {
        // Set previous Door Status and previous Ign State
        u8DoorStatusL = (U8)(ReadDoorsInput() | ((mDATRead(U1Bit, PWR_IGN, Defaut)) << cIgnStateIsOn));
        // Forbid the sleep until the end of the emission
        bSleepingAuthorisation = cFalse;
        // Set the data to send to the alarm
        mDATWriteTable(U8Bit, AlaCmdFrame, cByte0OfFrame, cDoorStatusCommand, Default);
        mDATWriteTable(U8Bit, AlaCmdFrame, cByte1OfFrame, u8DoorStatusL, Default);
        mDATWriteTable(U8Bit, AlaCmdFrame, cByte2OfFrame, (U8)0x00, Default);
        ChecksumCalculation(); // This function calculate the checksum 
        // AND set the byte 3 of the buffer AlaCmdFrame
        // Send the message to the alarm
        mDATControl(DATAla, SendCommand);


        // Clear Falling edge flag and authorize sleep state; LastCommandSent is DoorStatus
        if (bFallingEdgeForDS == cTrue)
        {
            bFallingEdgeForDS = cFalse;
        }


        PauseBetweenTwoMessagesValue =  cPauseBetweenArmADisarmCommandAndDoorStateCommand;
    }
    else
    {
        bSleepingAuthorisation = cTrue;
    }
    
}
//==============================================================================
// DESCRIPTION : Alarm command sending is finished
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   BOOL
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
BOOL LAPAlaSendingIsFinished(void)
{
    return (BOOL)(mDATRead(U1Bit, AlaCommunicationIsRunning, Default) == 0);
}
//==============================================================================
// DESCRIPTION : Checks that car is secured
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   BOOL
//
// DESIGN INFORMATION : prsFS_ASA-240, prsFS_ASA-254
//==============================================================================
BOOL LAPAlaIsCarSecure(void)
{

    return (bSetAlarmIsRequested && (bArmFollowedByDisarm == cFalse));
}
//==============================================================================
// DESCRIPTION : Checks that car is  not secured
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   BOOL 
//
// DESIGN INFORMATION : prsFS_ASA-255, prsFS_ASA-256
//==============================================================================
BOOL LAPAlaIsNotSecure(void)
{

    return (bUnsetAlarmIsRequested && (bArmFollowedByDisarm == cFalse));
}

//==============================================================================
// DESCRIPTION : Component initialization
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
void LAPAlaInitialize(void)
{
    bStateAfterReset = cTrue;
    TOSStopTimer(&PauseBetweenTwoMessagesTimer);
}
//==============================================================================
// DESCRIPTION : Checks is anybody maintain active state
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : prsFS_ASA-259
//==============================================================================
void LAPAlaIsAnybodyMaintainActiveState(void)
{
    if (bSleepingAuthorisation == cFalse)
    {
        TOSWriteSignal(cTOSSignalSomebodyMaintainActiveState);
    }
	
}

//==============================================================================
// DESCRIPTION : Checks is anybody maintain active sleep state
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : prsFS_ASA-259
//==============================================================================
void LAPAlaIsAnybodyMaintainActiveSleepState(void)
{
    if (bSleepingAuthorisation == cFalse)
    {
        TOSWriteSignal(cTOSSignalSomebodyMaintainActiveSleepState);
    }
	
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
void LAPAlaEnterActiveState(void)
{
    mDATWrite(U1Bit, IsAlaDiagEnabled, 0,Defaut);
    
    if (bStateAfterReset != cFalse)
    {
        // do not start main graph
        // graph will be started by reset graph
    }
    else
    {
        //QACJ 3204: akodzhh: keep for readability 
        //QACJ 3220: akodzhh: keep for clarity
        tTOSSeqGraphStateType GraphStateL = TOSSeqGraphState(cTOSSeqGraphIdLAPAlarms);
        if (GraphStateL == cTOSSeqInactiveGraph)
        {
            TOSSeqActivateGraph(cTOSSeqGraphIdLAPAlarms);
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
void LAPAlaLeaveActiveState(void)
{
    TOSSeqDeactivateGraph(cTOSSeqGraphIdLAPAlarms);
    mDATWrite(U1Bit, IsAlaDiagEnabled, 0,Defaut);
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
void LAPAlaLeaveStartingStepState(void)
{
    mDATWrite(U1Bit, IsAlaDiagEnabled, 0,Defaut);
    if (mDATRead(U1Bit, EEP_CALALARM, Default) == cAuthorize)
    {
        if( mDATRead(U1Bit, EEP_CAR_SECURE, Default) == cFalse)
        {
            bUnsetAlarmIsRequested = cTrue;
        }
        else
        {
            bSetAlarmIsRequested = cTrue;
        }

        TOSSeqActivateGraph(cTOSSeqGraphIdAlarmAfterReset);
    }
    else
    {
        bStateAfterReset = cFalse;
    }
    
}
//==============================================================================
// DESCRIPTION : Car unlock
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : prsFS_ASA-255, prsFS_ASA-256
//==============================================================================
void LAPAlaUnlockFromTheOutside(void)
{
    if (mDATRead(U1Bit, EEP_CALALARM, Default) == cAuthorize)
    {
        bUnsetAlarmIsRequested = cTrue;
        if(u8LastCommandSent == cArmCommand) 
        {
            bArmFollowedByDisarm = cTrue;
        }
    }
}
//==============================================================================
// DESCRIPTION : Key authentication
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : prsFS_ASA-265
//==============================================================================
void LAPAlaKeyIsAuthenticated(void)
{
    if (mDATRead(U1Bit, EEP_CALALARM, Default) == cAuthorize)
    {
        bUnsetAlarmIsRequested = cTrue;
 
        if(u8LastCommandSent == cArmCommand) 
        {
            bArmFollowedByDisarm = cTrue;
        }
    }
 
}

//==============================================================================
// DESCRIPTION : Falling edge of door ot ignition
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : prsFS_ASA-262
//==============================================================================
void LAPAlaFallingEdgeForDS(void)
{
    if ((mDATRead(U1Bit, EEP_CAR_SECURE, Default) == cTrue)
        && (mDATRead(U1Bit, EEP_CALALARM, Default) == cAuthorize))
    {
        bFallingEdgeForDS = cTrue;
        bSleepingAuthorisation = cFalse;
    }
}
//==============================================================================
// DESCRIPTION : Falling edge of door ot ignition
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : prsFS_ASA-262
//==============================================================================
void LAPAlaFallingEdgeForPWR_IGN(void)
{
    if (mDATRead(U1Bit, EEP_CALALARM, Default) == cAuthorize)
    {
        bFallingEdgeForDS = cTrue;
        bSleepingAuthorisation = cFalse;
    }
}
//==============================================================================
// DESCRIPTION : Car locked
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : prsFS_ASA-240, prsFS_ASA-2
//==============================================================================
void LAPAlaLockFromTheOutside(void)
{
    if (mDATRead(U1Bit, EEP_CALALARM, Default) == cAuthorize)
    {
        bSetAlarmIsRequested = cTrue;

        if (u8LastCommandSent == cDisarmCommand) 
        {
            bArmFollowedByDisarm = cTrue;
        }
    }
}
//==============================================================================
// DESCRIPTION :  Diagnostic is enabled
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
void LAPAlaDiagEnable(void)
{
#ifdef X90_PROJECT
    LAPAlaDiagEnable_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPAlaDiagEnable_Static(void)
{
#endif

    U8 u8GraphStateL; 
    u8GraphStateL = (U8) TOSSeqGraphState(cTOSSeqGraphIdLAPAlarms);

    mDATWrite(U1Bit, IsAlaDiagEnabled, 1,Defaut);
    if(u8GraphStateL == cTOSSeqActiveGraph)
    {
        TOSSeqFreezeGraph(cTOSSeqGraphIdLAPAlarms);
    }
    
}
//==============================================================================
// DESCRIPTION : Diagnostic is disabled
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
void LAPAlaDiagDisable(void)
{
#ifdef X90_PROJECT
    LAPAlaDiagDisable_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPAlaDiagDisable_Static(void)
{
#endif

    U8 u8GraphStateL; 
    u8GraphStateL = (U8) TOSSeqGraphState(cTOSSeqGraphIdLAPAlarms);

    mDATWrite(U1Bit, IsAlaDiagEnabled, 0,Defaut);
    if(u8GraphStateL == cTOSSeqFrozenGraph)
    {
        TOSSeqUnfreezeGraph(cTOSSeqGraphIdLAPAlarms);    
    }
    

}
//==============================================================================
// DESCRIPTION : Sets sleeping authorization
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
void LAPAlaSetSleepingAuthorisation(void)
{
    bSleepingAuthorisation = cTrue;
}
//==============================================================================
// DESCRIPTION : No door or ignition falling edges
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : prsFS_ASA-262
//==============================================================================
BOOL LAPAlaNoFallingEdges(void)
{
    BOOL bReturnValueL = cFalse;

    // if no falling edges presented, authorize sleep mode of BCM
    if (bFallingEdgeForDS == cFalse)
    {
        bReturnValueL = cTrue;
    }

    return bReturnValueL;
    
}
//==============================================================================
// DESCRIPTION : door or ignition falling edges
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : prsFS_ASA-262
//==============================================================================
BOOL LAPAlaFallingEdges(void)
{
    return bFallingEdgeForDS;
}

//==============================================================================
// DESCRIPTION : 
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : Refer to DCD
//==============================================================================
void LAPAlaAfterResetFinished(void)
{    
    TOSSeqActivateGraph(cTOSSeqGraphIdLAPAlarms);
    bStateAfterReset = cFalse;
    bMemoIgnState = mDATRead(U1Bit,PWR_IGN,Default);

    bSleepingAuthorisation = cTrue;
}

// [EXPORTED_FUNCTIONS_END] 
 