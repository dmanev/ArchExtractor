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
// Component:    The component is responsible for the generation of sequences 
//               for controlling an audio producing device to generate sounds 
//               and melodies, that are described in the parameterization file 
//               DAT_BUZx.H
// -----------------------------------------------------------------------------
// $Date:   Mar 02 2010 10:51:52  $
// $Archive::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_BUZ/DAT_BUZ.c-arc  $
// $Revision:   1.5  $
// -----------------------------------------------------------------------------
// $Log:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_BUZ/DAT_BUZ.c-arc  $
// 
//    Rev 1.5   Mar 02 2010 10:51:52   adzhelp
// Cm006814: TPS_BUZ_CLI, TPS_CLI, SBR_TIMEOUT_TM_TP normalized
// 
//    Rev 1.4   Oct 19 2009 12:42:18   amarinm1
// Cm005858: Code review corrections, binary code not affected.
// 
//    Rev 1.3   Oct 13 2009 17:22:54   amarinm1
// Cm003273: Comment added for C-Cover justification.
// 
//    Rev 1.2   Apr 29 2009 12:00:24   adzhelp
// Cm003273: Functions moved to banked memory area
// 
//    Rev 1.1   Mar 20 2009 18:11:06   amarinm1
// Cm003273: Changes for integration.
// 
//    Rev 1.0   Feb 24 2009 12:25:42   amarinm1
// Initial revision.
//******************************************************************************
#endif

//------------------------------------------------------------------------------
// Body Identification
//------------------------------------------------------------------------------
#define dat_buz  "dat_buz"

// #define DEBUG_BUZ

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------
#include "deftypes.h"
#include "ldb.h"
#include "tos.h"
#include "dat.h"

// component header
#include "dat_buz.h"

// melodies parameterizations
#include "dat_buzx.h"


#ifdef DEBUG_BUZ
    #include<stdio.h>
#endif

//------------------------------------------------------------------------------
// Local constants
//------------------------------------------------------------------------------
#define cTPS_BUZ_CLI_Stepx100           ((U16)615)
#define cTPS_BUZ_CLI_StepMultiplier     ((U16)100)
#define cTPS_BUZ_CLI_StepMultiplierHalf ((U16)50)
#define cTPS_CLI_Step                   ((U16)100)
#define cNumberOfMsInSecond             ((U32)1000)
#define cSeatBeltSoundTotalTimeInMs     ((U32)900)
#define cSeatBeltSoundHalfTimeInMs      ((U32)450)
#define cBuzzerTaskPeriodMs             5UL

//------------------------------------------------------------------------------
// Local macros
//------------------------------------------------------------------------------

//TBD: MB: This macro to be optimized, when the real tick value is determined, 
// because it is executed within interrupt and the mul/div operations may take 
// significant time 
// instead, the parameterization may come with ready-to-use values

#define mConvertMsIntoBuzzerTicks(x)    \
    (U32)((((U32)(x)*1000UL)/cDATBuzTaskTimeInUs)/*+1*/)


//------------------------------------------------------------------------------
// Local types
//------------------------------------------------------------------------------

// This is an example:
// typedef Expression   tTypeName;

//------------------------------------------------------------------------------
// Local data
//------------------------------------------------------------------------------
static tMsg    BuzzerMsg;
static U8      u8SoundBuffer;
static BOOL    bDATBuzAbnormalVoltage;
static BOOL    bDATBuzStarted;

// industrialization request
static BOOL    bIndusBuzzerFreqFlag;

static tTOSAlarm BuzzerTaskAlarm;
      
//------------------------------------------------------------------------------
// Constant local data
//------------------------------------------------------------------------------

// This is an example:
// static const tType  cConstantName;

//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------
tSoundStruct    DATBuzBuffer[cNumberOfBuffers];

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
static MEM_TYPE void ContinuePlayingBrokenSound( void );
static MEM_TYPE U8   GetCurrentHighestPriorityBuffer( void );

#ifdef X90_PROJECT
static MEM_TYPE void DATBuzTask_Static(void);
static MEM_TYPE void DATBuzSetBuzzRequest_Static(const tSOUND SoundRequestP, const BOOL bSoundStateP);
static MEM_TYPE void DATBuzInit_Static(void);
static MEM_TYPE void DATBuzStart_Static(void);
static MEM_TYPE void DATBuzStop_Static(void);
static MEM_TYPE void DATBuzDiagBuzzStart_Static(const U16 u16FreqP);
static MEM_TYPE void DATBuzNormalVoltage_Static(void);
static MEM_TYPE void DATBuzAbnormalVoltage_Static(void);
static MEM_TYPE void DATBuzDiagBuzzStop_Static(void);
#endif

//==============================================================================
//=========================== LOCAL FUNCTIONS ==================================
//==============================================================================


//==============================================================================
// DESCRIPTION:         < short description of the function >
//
// PARAMETERS:          < type,usage and constraints for all parameters >
//
// RETURN VALUE:        < type and usage >
//
// DESIGN INFORMATION:  < usage, pseudo code, algorithm, constraints ... >
//==============================================================================
static MEM_TYPE void ContinuePlayingBrokenSound( void )
{
    u8SoundBuffer = GetCurrentHighestPriorityBuffer();
    
    //continue playing the broken sound
    if ( DATBuzBuffer[u8SoundBuffer].DATBuzState == DATBUZ_PROCESS_SOUND_PAUSE )
    {
        //Continue to play lower priority buzzer that was interrupted
        //QACJ 0310: amarinm1: This is the expected type by the function. It is later casted to its original type.
        BuzzerMsg.pBuffer = (U8*)DATBuzBuffer[u8SoundBuffer].Buffer;
        LDBSendWithoutAddr (cLDBChannelBuz, (tMsg *)&BuzzerMsg);
        LDBControl (cLDBChannelBuz, cLDBBuzStartSound);
    }
    else
    {
        // Do nothing
    }
}

//==============================================================================
// DESCRIPTION:         < short description of the function >
//
// PARAMETERS:          < type,usage and constraints for all parameters >
//
// RETURN VALUE:        < type and usage >
//
// DESIGN INFORMATION:  < usage, pseudo code, algorithm, constraints ... >
//==============================================================================
static MEM_TYPE U8 GetCurrentHighestPriorityBuffer( void )
{
    U8 u8ResultL;

    //---------------------------------------------------------------------
    // Find highest priority sound to be played

    if (DATBuzBuffer[cBufferFlashers].DATBuzSoundToPlay != 
                eBUZZER_Silence)
    {
        u8ResultL = cBufferFlashers;
    }
    else if (DATBuzBuffer[cBufferLWS].DATBuzSoundToPlay != 
                eBUZZER_Silence)
    {
        DATBuzBuffer[cBufferFlashers].DATBuzState = DATBUZ_IDLE;
        
        u8ResultL = cBufferLWS;
    }
    else if (DATBuzBuffer[cBufferSeatBelt].DATBuzSoundToPlay != 
                eBUZZER_Silence)
    {
        DATBuzBuffer[cBufferFlashers].DATBuzState  = DATBUZ_IDLE;
        DATBuzBuffer[cBufferLWS].DATBuzState       = DATBUZ_IDLE;
        
        u8ResultL = cBufferSeatBelt;
    }
    else if (DATBuzBuffer[cBufferOverSpeed].DATBuzSoundToPlay != 
                eBUZZER_Silence)
    {
        DATBuzBuffer[cBufferFlashers].DATBuzState  = DATBUZ_IDLE;
        DATBuzBuffer[cBufferLWS].DATBuzState       = DATBUZ_IDLE;
        DATBuzBuffer[cBufferSeatBelt].DATBuzState  = DATBUZ_IDLE;

        u8ResultL = cBufferOverSpeed;
    }
    else if (DATBuzBuffer[cBufferExtLights].DATBuzSoundToPlay != 
                eBUZZER_Silence)
    {
        DATBuzBuffer[cBufferFlashers].DATBuzState  = DATBUZ_IDLE;
        DATBuzBuffer[cBufferLWS].DATBuzState       = DATBUZ_IDLE;
        DATBuzBuffer[cBufferSeatBelt].DATBuzState  = DATBUZ_IDLE;
        DATBuzBuffer[cBufferOverSpeed].DATBuzState = DATBUZ_IDLE;

        u8ResultL = cBufferExtLights;
    }
    else
    {
        DATBuzBuffer[cBufferFlashers].DATBuzState  = DATBUZ_IDLE;
        DATBuzBuffer[cBufferLWS].DATBuzState       = DATBUZ_IDLE;
        DATBuzBuffer[cBufferSeatBelt].DATBuzState  = DATBUZ_IDLE;
        DATBuzBuffer[cBufferOverSpeed].DATBuzState = DATBUZ_IDLE;
        DATBuzBuffer[cBufferExtLights].DATBuzState = DATBUZ_IDLE;

        u8ResultL = cBufferExtLights;
    }

    //---------------------------------------------------------------------

    return u8ResultL;
}


//==============================================================================
//=========================== EXPORTED FUNCTIONS ===============================
//==============================================================================


//==============================================================================
// DESCRIPTION:         < short description of the function >
//
// PARAMETERS:          < type,usage and constraints for all parameters >
//
// RETURN VALUE:        < type and usage >
//
// DESIGN INFORMATION:  < usage, pseudo code, algorithm, constraints ... >
//==============================================================================
BOOL DATBuzIsSoundPlaying(void)
{
    // DATBuzState keeps the next state to process so when a sound is being
    // played the next state is DATBUZ_PROCESS_SOUND_PAUSE
    const BOOL bResult = (BOOL)
        (   (   (DATBuzBuffer[u8SoundBuffer].DATBuzState == DATBUZ_PROCESS_SOUND_PAUSE)
             && (bDATBuzAbnormalVoltage == cFalse)   )
         || (bIndusBuzzerFreqFlag == cTrue)
        );

    return bResult;
}


//==============================================================================
// DESCRIPTION:         < short description of the function >
//
// PARAMETERS:          < type,usage and constraints for all parameters >
//
// RETURN VALUE:        < type and usage >
//
// DESIGN INFORMATION:  < usage, pseudo code, algorithm, constraints ... >
//==============================================================================
void DATBuzSetBuzzRequest(const tSOUND SoundRequestP, const BOOL bSoundStateP)
{
#ifdef X90_PROJECT
    DATBuzSetBuzzRequest_Static(SoundRequestP, bSoundStateP);
}
#pragma optimize=no_inline
static MEM_TYPE void DATBuzSetBuzzRequest_Static(const tSOUND SoundRequestP, const BOOL bSoundStateP)
{
#endif
    U16 u16TempL;

    switch(SoundRequestP)
    {
    case eBUZZER_FlasherClick:
        if (bSoundStateP == cTrue)
        {
            DATBuzBuffer[cBufferFlashers].DATBuzSoundToPlay = eBUZZER_FlasherClick;
            DATBuzBuffer[cBufferFlashers].DATBuzState = DATBUZ_PROCESS_START;
            DATBuzBuffer[cBufferFlashers].ticks_to_elapse = 0;


            // The active time needs to be dynamicly updated
            u16TempL = cTPS_BUZ_CLI_Stepx100 * (U16)mDATRead(U8Bit, NEEP_TPS_BUZ_CLI, Default);
            
            // Round the integer
            if ( (U16)(u16TempL % cTPS_BUZ_CLI_StepMultiplier) > cTPS_BUZ_CLI_StepMultiplierHalf )
            {
                u16TempL += cTPS_BUZ_CLI_StepMultiplier;
            }
            u16TempL /= cTPS_BUZ_CLI_StepMultiplier;

            DATBuzMelodies[eBUZZER_FlasherClick].Sound.Motive[0].ActiveTime = u16TempL;

            
            // Note: the following strategy is applied in order to ensure that
            // a lower priority sound is not started during the sound pause
            // when the flashers are active.

            // The inactive time is the rest of the click
            DATBuzMelodies[eBUZZER_FlasherClick].Sound.Motive[0].InactiveTime =
               (cTPS_CLI_Step * (U16)mDATRead(U8Bit, NEEP_TPS_CLI, Default)) - 
               DATBuzMelodies[eBUZZER_FlasherClick].Sound.Motive[0].ActiveTime;
        }
        else
        {
            DATBuzBuffer[cBufferFlashers].DATBuzSoundToPlay = eBUZZER_Silence;
            DATBuzBuffer[cBufferFlashers].DATBuzState = DATBUZ_IDLE;
            
            LDBControl (cLDBChannelBuz, cLDBBuzCancelSound);
        }
        break;

    case eBUZZER_FlasherClack:
        if (bSoundStateP == cTrue)
        {
            DATBuzBuffer[cBufferFlashers].DATBuzSoundToPlay = eBUZZER_FlasherClack;
            DATBuzBuffer[cBufferFlashers].DATBuzState = DATBUZ_PROCESS_START;
            DATBuzBuffer[cBufferFlashers].ticks_to_elapse = 0;


            // The active time needs to be dynamicly updated
            u16TempL = cTPS_BUZ_CLI_Stepx100 * (U16)mDATRead(U8Bit, NEEP_TPS_BUZ_CLI, Default);
            
            // Round the integer
            if ( (U16)(u16TempL % cTPS_BUZ_CLI_StepMultiplier) > cTPS_BUZ_CLI_StepMultiplierHalf )
            {
                u16TempL += cTPS_BUZ_CLI_StepMultiplier;
            }
            u16TempL /= cTPS_BUZ_CLI_StepMultiplier;

            DATBuzMelodies[eBUZZER_FlasherClack].Sound.Motive[0].ActiveTime = u16TempL;


            // Note: the following strategy is applied in order to ensure that
            // a lower priority sound is not started during the sound pause
            // when the flashers are active.

            // The inactive time is the rest of the click
            DATBuzMelodies[eBUZZER_FlasherClack].Sound.Motive[0].InactiveTime =
               (cTPS_CLI_Step * (U16)mDATRead(U8Bit, NEEP_TPS_CLI, Default)) - 
               DATBuzMelodies[eBUZZER_FlasherClack].Sound.Motive[0].ActiveTime;
        }
        else
        {
            DATBuzBuffer[cBufferFlashers].DATBuzSoundToPlay = eBUZZER_Silence;
            DATBuzBuffer[cBufferFlashers].DATBuzState = DATBUZ_IDLE;

            LDBControl (cLDBChannelBuz, cLDBBuzCancelSound);
            ContinuePlayingBrokenSound();
        }
        break;
    
    case eBUZZER_LockWithSpeed:
        if (bSoundStateP == cTrue)
        {
            DATBuzBuffer[cBufferLWS].DATBuzSoundToPlay = eBUZZER_LockWithSpeed;
            DATBuzBuffer[cBufferLWS].DATBuzState = DATBUZ_PROCESS_START;
            DATBuzBuffer[cBufferLWS].ticks_to_elapse = 0;
        }
        else
        {
            DATBuzBuffer[cBufferLWS].DATBuzSoundToPlay = eBUZZER_Silence;
            DATBuzBuffer[cBufferLWS].DATBuzState = DATBUZ_IDLE;

            LDBControl (cLDBChannelBuz, cLDBBuzCancelSound);
            ContinuePlayingBrokenSound();
        }
        break;
    
    case eBUZZER_SeatBelt:
        if (bSoundStateP == cTrue)
        {
            DATBuzBuffer[cBufferSeatBelt].DATBuzSoundToPlay = eBUZZER_SeatBelt;
            DATBuzBuffer[cBufferSeatBelt].DATBuzState = DATBUZ_PROCESS_START;
            DATBuzBuffer[cBufferSeatBelt].ticks_to_elapse = 0;

            // There is a duration timeout for the SeatBelt warning that needs
            // to be dynamicly updated.
            DATBuzMelodies[eBUZZER_SeatBelt].Repetitions = (U8)
            ( ((U32)mDATRead(U8Bit, NEEP_SBR_TIMEOUT_TM_TP, Default) * cNumberOfMsInSecond) / 
                        cSeatBeltSoundTotalTimeInMs );

            // To round the integer divisiion
            if ( (((U32)mDATRead(U8Bit, NEEP_SBR_TIMEOUT_TM_TP, Default) * cNumberOfMsInSecond) % 
                        cSeatBeltSoundTotalTimeInMs) > cSeatBeltSoundHalfTimeInMs ) 
            {
                DATBuzMelodies[eBUZZER_SeatBelt].Repetitions++;
            }
        }
        else
        {
            DATBuzBuffer[cBufferSeatBelt].DATBuzSoundToPlay = eBUZZER_Silence;
            DATBuzBuffer[cBufferSeatBelt].DATBuzState = DATBUZ_IDLE;

            LDBControl (cLDBChannelBuz, cLDBBuzCancelSound);
            ContinuePlayingBrokenSound();
        }
        break;
    
    case eBUZZER_OverSpeed:
        if (bSoundStateP == cTrue)
        {
            DATBuzBuffer[cBufferOverSpeed].DATBuzSoundToPlay = eBUZZER_OverSpeed;
            DATBuzBuffer[cBufferOverSpeed].DATBuzState = DATBUZ_PROCESS_START;
            DATBuzBuffer[cBufferOverSpeed].ticks_to_elapse = 0;
        }
        else
        {
            DATBuzBuffer[cBufferOverSpeed].DATBuzSoundToPlay = eBUZZER_Silence;
            DATBuzBuffer[cBufferOverSpeed].DATBuzState = DATBUZ_IDLE;

            LDBControl (cLDBChannelBuz, cLDBBuzCancelSound);
            ContinuePlayingBrokenSound();
        }
        break;
    
    case eBUZZER_ExtLights:
        if (bSoundStateP == cTrue)
        {
            DATBuzBuffer[cBufferExtLights].DATBuzSoundToPlay = eBUZZER_ExtLights;
            DATBuzBuffer[cBufferExtLights].DATBuzState = DATBUZ_PROCESS_START;
            DATBuzBuffer[cBufferExtLights].ticks_to_elapse = 0;
        }
        else
        {
            DATBuzBuffer[cBufferExtLights].DATBuzSoundToPlay = eBUZZER_Silence;
            DATBuzBuffer[cBufferExtLights].DATBuzState = DATBUZ_IDLE;

            LDBControl (cLDBChannelBuz, cLDBBuzCancelSound);
            ContinuePlayingBrokenSound();
        }
        break;

    //CCOV: amarinm1: Default case for invalid buzz requests. Cannot be covered because of the Assert.
    default:
        mLIBassert(cFalse);
    }
}


//==============================================================================
// DESCRIPTION:         < short description of the function >
//
// PARAMETERS:          < type,usage and constraints for all parameters >
//
// RETURN VALUE:        < type and usage >
//
// DESIGN INFORMATION:  < usage, pseudo code, algorithm, constraints ... >
//==============================================================================
void DATBuzInit(void)
{
#ifdef X90_PROJECT
    DATBuzInit_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DATBuzInit_Static(void)
{
#endif

    u8SoundBuffer   = cBufferExtLights; //lowest priority buzzer
    BuzzerMsg.Lng   = sizeof(DATBuzBuffer[0].Buffer);
    bDATBuzStarted  = cFalse;

    DATBuzBuffer[cBufferFlashers].DATBuzSoundToPlay  = eBUZZER_Silence;
    DATBuzBuffer[cBufferLWS].DATBuzSoundToPlay       = eBUZZER_Silence;
    DATBuzBuffer[cBufferSeatBelt].DATBuzSoundToPlay  = eBUZZER_Silence;
    DATBuzBuffer[cBufferOverSpeed].DATBuzSoundToPlay = eBUZZER_Silence;
    DATBuzBuffer[cBufferExtLights].DATBuzSoundToPlay = eBUZZER_Silence;

    DATBuzBuffer[cBufferFlashers].ticks_to_elapse  = 0;
    DATBuzBuffer[cBufferLWS].ticks_to_elapse       = 0;
    DATBuzBuffer[cBufferSeatBelt].ticks_to_elapse  = 0;
    DATBuzBuffer[cBufferOverSpeed].ticks_to_elapse = 0;
    DATBuzBuffer[cBufferExtLights].ticks_to_elapse = 0;

    bDATBuzAbnormalVoltage = cFalse;

    bIndusBuzzerFreqFlag = cFalse;
}


//==============================================================================
// DESCRIPTION:         < short description of the function >
//
// PARAMETERS:          < type,usage and constraints for all parameters >
//
// RETURN VALUE:        < type and usage >
//
// DESIGN INFORMATION:  < usage, pseudo code, algorithm, constraints ... >
//==============================================================================
void DATBuzStart(void)
{
#ifdef X90_PROJECT
    DATBuzStart_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DATBuzStart_Static(void)
{
#endif

    if(bDATBuzStarted == cFalse)
    {
        bDATBuzStarted = cTrue;

        DATBuzBuffer[cBufferFlashers].DATBuzState  = DATBUZ_IDLE;
        DATBuzBuffer[cBufferLWS].DATBuzState       = DATBUZ_IDLE;
        DATBuzBuffer[cBufferSeatBelt].DATBuzState  = DATBUZ_IDLE;
        DATBuzBuffer[cBufferOverSpeed].DATBuzState = DATBUZ_IDLE;
        DATBuzBuffer[cBufferExtLights].DATBuzState = DATBUZ_IDLE;

        LDBControl( cLDBChannelBuz, cLDBBuzEnable );

        BuzzerTaskAlarm.TaskID = cTOSTaskIdDATBuzTask;
        TOSSetRelAlarm(&BuzzerTaskAlarm, 0, mTOSConvMsEnTickAlarm(cBuzzerTaskPeriodMs));
    }
}


//==============================================================================
// DESCRIPTION:         < short description of the function >
//
// PARAMETERS:          < type,usage and constraints for all parameters >
//
// RETURN VALUE:        < type and usage >
//
// DESIGN INFORMATION:  < usage, pseudo code, algorithm, constraints ... >
//==============================================================================
void DATBuzStop(void)
{
#ifdef X90_PROJECT
    DATBuzStop_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DATBuzStop_Static(void)
{
#endif

    if ( bDATBuzStarted == cTrue )
    {
        bDATBuzStarted = cFalse;
        
        DATBuzBuffer[cBufferFlashers].DATBuzState  = DATBUZ_IDLE;
        DATBuzBuffer[cBufferLWS].DATBuzState       = DATBUZ_IDLE;
        DATBuzBuffer[cBufferSeatBelt].DATBuzState  = DATBUZ_IDLE;
        DATBuzBuffer[cBufferOverSpeed].DATBuzState = DATBUZ_IDLE;
        DATBuzBuffer[cBufferExtLights].DATBuzState = DATBUZ_IDLE;

        DATBuzBuffer[cBufferFlashers].DATBuzSoundToPlay  = eBUZZER_Silence;
        DATBuzBuffer[cBufferLWS].DATBuzSoundToPlay       = eBUZZER_Silence;
        DATBuzBuffer[cBufferSeatBelt].DATBuzSoundToPlay  = eBUZZER_Silence;
        DATBuzBuffer[cBufferOverSpeed].DATBuzSoundToPlay = eBUZZER_Silence;
        DATBuzBuffer[cBufferExtLights].DATBuzSoundToPlay = eBUZZER_Silence;

        LDBControl( cLDBChannelBuz, cLDBBuzDisable );

        TOSCancelAlarm(&BuzzerTaskAlarm);
    }
}


//==============================================================================
// DESCRIPTION:         < short description of the function >
//
// PARAMETERS:          < type,usage and constraints for all parameters >
//
// RETURN VALUE:        < type and usage >
//
// DESIGN INFORMATION:  < usage, pseudo code, algorithm, constraints ... >
//==============================================================================
void DATBuzTask(void)
{
#ifdef X90_PROJECT
    DATBuzTask_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DATBuzTask_Static(void)
{
#endif
           //CCOV: amarinm1: Cannot be covered in normal operating conditions.
    if (   (bDATBuzStarted         == cTrue) 
        && (bDATBuzAbnormalVoltage == cFalse)   
        && (bIndusBuzzerFreqFlag   == cFalse)   )
    {

        //---------------------------------------------------------------------
        // Find highest priority sound to be played

        u8SoundBuffer = GetCurrentHighestPriorityBuffer();
        
        //---------------------------------------------------------------------

        //---------------------------------------------------------------------
        // ticks_to_elapse automatically delays the necessary amount of time 
        // until the next action of the state machine
        
        if( DATBuzBuffer[u8SoundBuffer].ticks_to_elapse != 0UL )
        {
            DATBuzBuffer[u8SoundBuffer].ticks_to_elapse--;
        }
        else //ticks are reaching 0, calculate the new buzzer state
        {
            //-----------------------------------------------------------------
            //print debug information

            #ifdef DEBUG_BUZ
            printf ("\n\rState: ");
            switch (DATBuzState)
            {
                case DATBUZ_IDLE:
                        printf ("DATBUZ_IDLE");
                    break;
                case DATBUZ_PROCESS_START:
                        printf ("DATBUZ_PROCESS_START");
                    break;
                case DATBUZ_PROCESS_SOUND_PERIOD:
                        printf ("DATBUZ_PROCESS_SOUND_PERIOD");
                    break;
                case DATBUZ_PROCESS_SOUND_PAUSE:
                        printf ("DATBUZ_PROCESS_SOUND_PAUSE");
                    break;
                case DATBUZ_PROCESS_MELODY_PAUSE:
                        printf ("DATBUZ_PROCESS_MELODY_PAUSE");
                    break;
                case DATBUZ_PROCESS_FINISHED:
                        printf ("DATBUZ_PROCESS_FINISHED");
                    break;
            }
            #endif   

            //-----------------------------------------------------------------
            //Buzzer state machine

            switch( DATBuzBuffer[u8SoundBuffer].DATBuzState )
            {

            case DATBUZ_IDLE:

                DATBuzBuffer[u8SoundBuffer].ticks_to_elapse = 0;

                break;


            case DATBUZ_PROCESS_START:

                // copy the data for the sound to be played
                DATBuzBuffer[u8SoundBuffer].sound                 = 
                    DATBuzBuffer[u8SoundBuffer].DATBuzSoundToPlay;

                DATBuzBuffer[u8SoundBuffer].melody_repetitions    = 
                    //QACJ 3689: amarinm1: The indexer(.sound) is set only through members of its enumerated type the highest value of which is the size of DATBuzMelodies.
                    DATBuzMelodies[DATBuzBuffer[u8SoundBuffer].sound].Repetitions;
                
                DATBuzBuffer[u8SoundBuffer].sound_repetitions     = 
                    //QACJ 3689: amarinm1: The indexer(.sound) is set only through members of its enumerated type the highest value of which is the size of DATBuzMelodies.
                    DATBuzMelodies[DATBuzBuffer[u8SoundBuffer].sound].Sound.Repetitions;
                
                DATBuzBuffer[u8SoundBuffer].sound_index           = 0;
                
                DATBuzBuffer[u8SoundBuffer].pmotive               = (tPERIOD_DESC*)
                    //QACJ 3689: amarinm1: The indexer(.sound) is set only through members of its enumerated type the highest value of which is the size of DATBuzMelodies.
                    DATBuzMelodies[DATBuzBuffer[u8SoundBuffer].sound].Sound.Motive;

                // jump to next state for sound playing
                DATBuzBuffer[u8SoundBuffer].DATBuzState = DATBUZ_PROCESS_SOUND_PERIOD;
            
                break;


            case DATBUZ_PROCESS_SOUND_PERIOD:

                // --- start playing the sound ---
        
                // load the sound into LDB (mDATBuzFillFrequencyForLDB)
                DATBuzBuffer[u8SoundBuffer].Buffer[0] = 
                    DATBuzBuffer[u8SoundBuffer].pmotive[DATBuzBuffer[u8SoundBuffer].sound_index].Frequency;

                //QACJ 0310: amarinm1: This is the expected type by the function. It is later casted to its original type.
                BuzzerMsg.pBuffer = (U8*)DATBuzBuffer[u8SoundBuffer].Buffer;
                LDBSendWithoutAddr(cLDBChannelBuz, (tMsg*)&BuzzerMsg);

                // start the loaded sound
                LDBControl(cLDBChannelBuz, cLDBBuzStartSound);
        
                DATBuzBuffer[u8SoundBuffer].ticks_to_elapse = 
                    mConvertMsIntoBuzzerTicks(
                    DATBuzBuffer[u8SoundBuffer].pmotive[DATBuzBuffer[u8SoundBuffer].sound_index].ActiveTime);

                DATBuzBuffer[u8SoundBuffer].DATBuzState = DATBUZ_PROCESS_SOUND_PAUSE;
                
                break;


            case DATBUZ_PROCESS_SOUND_PAUSE:

                // stop the sound
                LDBControl (cLDBChannelBuz, cLDBBuzCancelSound);

                DATBuzBuffer[u8SoundBuffer].ticks_to_elapse = 
                    mConvertMsIntoBuzzerTicks(
                    DATBuzBuffer[u8SoundBuffer].pmotive[DATBuzBuffer[u8SoundBuffer].sound_index].InactiveTime);
        
                // prepare next state

                DATBuzBuffer[u8SoundBuffer].sound_index++;

                if( DATBuzBuffer[u8SoundBuffer].sound_index < 
                    //QACJ 3689: amarinm1: The indexer(.sound) is set only through members of its enumerated type the highest value of which is the size of DATBuzMelodies.
                    DATBuzMelodies[DATBuzBuffer[u8SoundBuffer].sound].Sound.NumFrequencies
                  ) 
                {

                    // process the next frequency after the pause is finished
                    DATBuzBuffer[u8SoundBuffer].DATBuzState = DATBUZ_PROCESS_SOUND_PERIOD;
            
                }
                else // we have played the sound sequence 
                {
                    // one because we start counting the repetitions from 1
                    if (DATBuzBuffer[u8SoundBuffer].sound_repetitions > 1) 
                    {

                        DATBuzBuffer[u8SoundBuffer].DATBuzState = DATBUZ_PROCESS_SOUND_PERIOD;
                        DATBuzBuffer[u8SoundBuffer].sound_repetitions--;
                        // start over the sounds again if there is repetition
                        DATBuzBuffer[u8SoundBuffer].sound_index = 0;
                    }
                    else
                    {
                        DATBuzBuffer[u8SoundBuffer].DATBuzState = DATBUZ_PROCESS_MELODY_PAUSE;
                    }
                }

                break;


            case DATBUZ_PROCESS_MELODY_PAUSE:

                // 2 because melody repetitions are count from 1
                // and there is no need to wait the last pause time
                if(DATBuzBuffer[u8SoundBuffer].melody_repetitions > 1) 
                {
                    // wait the pause to elapse
                    DATBuzBuffer[u8SoundBuffer].ticks_to_elapse = 
                        //QACJ 3689: amarinm1: The indexer(.sound) is set only through members of its enumerated type the highest value of which is the size of DATBuzMelodies.
                        mConvertMsIntoBuzzerTicks(DATBuzMelodies[DATBuzBuffer[u8SoundBuffer].sound].Pause);

                    // load again parameters for melody repetition
                    DATBuzBuffer[u8SoundBuffer].sound_repetitions  = 
                        //QACJ 3689: amarinm1: The indexer(.sound) is set only through members of its enumerated type the highest value of which is the size of DATBuzMelodies.
                        DATBuzMelodies[DATBuzBuffer[u8SoundBuffer].sound].Sound.Repetitions;

                    DATBuzBuffer[u8SoundBuffer].sound_index = 0;
                
                    // check for infinite melody
                    if(    DATBuzBuffer[u8SoundBuffer].melody_repetitions != 
                        cDATBuzRepetitionsInfinite
                      )
                    {
                        // decrease melodies left to play
                        DATBuzBuffer[u8SoundBuffer].melody_repetitions--;
                    }
                
                    // start over again
                    DATBuzBuffer[u8SoundBuffer].DATBuzState = DATBUZ_PROCESS_SOUND_PERIOD;
                }
                else
                {
                    // no need to process the last pause
                    DATBuzBuffer[u8SoundBuffer].ticks_to_elapse = 0;
                    DATBuzBuffer[u8SoundBuffer].DATBuzState = DATBUZ_PROCESS_FINISHED;
                }

                break;


            case DATBUZ_PROCESS_FINISHED:

                DATBuzBuffer[u8SoundBuffer].DATBuzSoundToPlay = eBUZZER_Silence;
                DATBuzBuffer[u8SoundBuffer].DATBuzState = DATBUZ_IDLE;

                u8SoundBuffer = GetCurrentHighestPriorityBuffer();

                //continue playing the broken sound
                if ( DATBuzBuffer[u8SoundBuffer].DATBuzState == DATBUZ_PROCESS_SOUND_PAUSE )
                {
                    //Continue to play lower priority buzzer that was interrupted
                    //QACJ 0310: amarinm1: This is the expected type by the function. It is later casted to its original type.
                    BuzzerMsg.pBuffer = (U8*)DATBuzBuffer[u8SoundBuffer].Buffer;
                    LDBSendWithoutAddr (cLDBChannelBuz, (tMsg *)&BuzzerMsg);
                    LDBControl (cLDBChannelBuz, cLDBBuzStartSound);
                }

                break;

            //CCOV: amarinm1: Cannot be entered in normal operating conditions.
            default:
                mLIBassert(cFalse);

                //SPLUS checklist.
                //Lessons learned, point 1.2.5
                //In all the state machines with switch/cases the default  
                //case reinitialize the state machine.            

                LDBControl(cLDBChannelBuz, cLDBBuzCancelSound);

                DATBuzBuffer[cBufferFlashers].DATBuzSoundToPlay  = 
                    eBUZZER_Silence;
                DATBuzBuffer[cBufferLWS].DATBuzSoundToPlay       = 
                    eBUZZER_Silence;
                DATBuzBuffer[cBufferSeatBelt].DATBuzSoundToPlay  = 
                    eBUZZER_Silence;
                DATBuzBuffer[cBufferOverSpeed].DATBuzSoundToPlay = 
                    eBUZZER_Silence;
                DATBuzBuffer[cBufferExtLights].DATBuzSoundToPlay = 
                    eBUZZER_Silence;

                DATBuzBuffer[cBufferFlashers].ticks_to_elapse  = 0;
                DATBuzBuffer[cBufferLWS].ticks_to_elapse       = 0;
                DATBuzBuffer[cBufferSeatBelt].ticks_to_elapse  = 0;
                DATBuzBuffer[cBufferOverSpeed].ticks_to_elapse = 0;
                DATBuzBuffer[cBufferExtLights].ticks_to_elapse = 0;

                break;
            
            } //end switch
        }
    }
    else
    { 
        // we go without doing anything
    }
}


//==============================================================================
// DESCRIPTION:         < short description of the function >
//
// PARAMETERS:          < type,usage and constraints for all parameters >
//
// RETURN VALUE:        < type and usage >
//
// DESIGN INFORMATION:  < usage, pseudo code, algorithm, constraints ... >
//==============================================================================
void DATBuzNormalVoltage(void)
{
#ifdef X90_PROJECT
    DATBuzNormalVoltage_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DATBuzNormalVoltage_Static(void)
{
#endif

    bDATBuzAbnormalVoltage = cFalse;

    // restart the component again
    LDBControl(cLDBChannelBuz, cLDBBuzEnable);

    ContinuePlayingBrokenSound();

    // the sound that has been played upon abnormal voltage detection
    // was interrupted immediately, and will continue to be played 
    // from where it was stopped.
}


//==============================================================================
// DESCRIPTION:         < short description of the function >
//
// PARAMETERS:          < type,usage and constraints for all parameters >
//
// RETURN VALUE:        < type and usage >
//
// DESIGN INFORMATION:  < usage, pseudo code, algorithm, constraints ... >
//==============================================================================
void DATBuzAbnormalVoltage(void)
{
#ifdef X90_PROJECT
    DATBuzAbnormalVoltage_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DATBuzAbnormalVoltage_Static(void)
{
#endif

    bDATBuzAbnormalVoltage = cTrue;

    // stop the sound in progress
    LDBControl(cLDBChannelBuz, cLDBBuzDisable);
}


//==============================================================================
// DESCRIPTION:         < short description of the function >
//
// PARAMETERS:          < type,usage and constraints for all parameters >
//
// RETURN VALUE:        < type and usage >
//
// DESIGN INFORMATION:  < usage, pseudo code, algorithm, constraints ... >
//==============================================================================
void DATBuzDiagBuzzStart(const U16 u16FreqP)
{    
#ifdef X90_PROJECT
    DATBuzDiagBuzzStart_Static(u16FreqP);
}
#pragma optimize=no_inline
static MEM_TYPE void DATBuzDiagBuzzStart_Static(const U16 u16FreqP)
{
#endif

    tMsg    BuzzMsgL;
    U16     Buff[cDATBuzBufferSize];
    Buff[0] = u16FreqP;
    //QACJ 0310: amarinm1: This is the expected type by the function. It is later casted to its original type.
    BuzzMsgL.pBuffer = (U8*)Buff;
    BuzzMsgL.Lng = sizeof(Buff);
    LDBSendWithoutAddr(cLDBChannelBuz, (tMsg*)&BuzzMsgL);

    // start the loaded sound
    LDBControl(cLDBChannelBuz, cLDBBuzStartSound);

    // set flag
    bIndusBuzzerFreqFlag = cTrue;
}


//==============================================================================
// DESCRIPTION:         < short description of the function >
//
// PARAMETERS:          < type,usage and constraints for all parameters >
//
// RETURN VALUE:        < type and usage >
//
// DESIGN INFORMATION:  < usage, pseudo code, algorithm, constraints ... >
//==============================================================================
void DATBuzDiagBuzzStop(void)
{
#ifdef X90_PROJECT
    DATBuzDiagBuzzStop_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DATBuzDiagBuzzStop_Static(void)
{
#endif

    // stop the loaded sound
    LDBControl(cLDBChannelBuz, cLDBBuzCancelSound);

    ContinuePlayingBrokenSound();

    // unset flag 
    bIndusBuzzerFreqFlag = cFalse;
}