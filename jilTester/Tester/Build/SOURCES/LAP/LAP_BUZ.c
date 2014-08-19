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
// Component:    This component's role is to manage the activation and
//               deactivation of forgotten lights and seatbelt buzzer signals.
//               The requests are passed to DAT_BUZ for further processing.
// -----------------------------------------------------------------------------
// $Date:   Mar 22 2010 14:24:10  $
// $Archive::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_BUZ/LAP_BUZ.c-arc  $
// $Revision:   1.9  $
// -----------------------------------------------------------------------------
// $Log:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_BUZ/LAP_BUZ.c-arc  $
// 
//    Rev 1.9   Mar 22 2010 14:24:10   adzhelp
// Cm006814: Code review corrections
// 
//    Rev 1.8   Mar 02 2010 10:42:56   adzhelp
// Cm006814: MAX_NB_ALERT_SEQUENCES_TP, SBR_ACTIVE_SPEED_THRESH_TP normalized
// 
//    Rev 1.7   Dec 15 2009 10:14:58   adzhelp
// Cm006711: HIGH_LOW_BEAM removed
// 
//    Rev 1.6   Dec 04 2009 17:03:20   amarinm1
// Cm006711: FR_FOG input was removed.
// 
//    Rev 1.5   Nov 24 2009 15:26:34   amarinm1
// Cm006711: Activation of External Lights buzzer on Rear Fog request was added.
// 
//    Rev 1.4   May 08 2009 16:17:04   amanevd
// Cm004940 - Remind of the forgotten External Lights v2
// 
//    Rev 1.3   May 08 2009 13:07:26   amanevd
// Cm004940 - Remind of the forgotten External Lights
// 
//    Rev 1.2   Apr 29 2009 14:05:38   adzhelp
// Cm003273: Functions moved to banked memory area
//
//    Rev 1.1   Apr 24 2009 11:18:52   amarinm1
// Cm003273: The logic of the seatbelt switch was reversed.
// 
//    Rev 1.0   Feb 25 2009 11:03:14   amarinm1
// Initial revision.
//******************************************************************************
#endif

//------------------------------------------------------------------------------
// Body Identification
//------------------------------------------------------------------------------
#define lap_buz   "lap_buz"

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------

// This is an example:
// #include <system_file_name.h>
// #include "project_file_name.h"


#include "deftypes.h" 
#include "tos.h"
#include "dat.h"
#include "lap_buz.h"
#include "lap_buz.hgr"


//------------------------------------------------------------------------------
// Local constants
//------------------------------------------------------------------------------

#define cOverSpeedDetectionDurationInTimerTicks (mTOSConvMsInTimerTick(3000UL))
#define cOverSpeedWarningActivationThreshold    ((U8)  120)
#define cOverSpeedWarningDeactivationThreshold  ((U8)  118)

//------------------------------------------------------------------------------
// Local macros
//------------------------------------------------------------------------------
#define mReadMaxNumberOfSeatBeltWarningActivations() \
    /* //QACJ 3443: amarinm1: There is no recursion - concatenation is applied to the second macro. */ \
    mDATRead(U8Bit, NEEP_MAX_NB_ALERT_SEQUENCES_TP, Default)

#define mReadIsSeatBeltWarningEnabled() \
    /* //QACJ 3443: amarinm1: There is no recursion - concatenation is applied to the second macro. */ \
    (BOOL) mDATRead(U1Bit, EEP_OUBLICEINTURE, Default)

#define mReadSeatBeltSpeedThreshold() \
    /* //QACJ 3443: amarinm1: There is no recursion - concatenation is applied to the second macro. */ \
    mDATRead(U8Bit, NEEP_SBR_ACTIVE_SPEED_THRESH_TP, Default)

#define mReadCurrentSpeed() \
    /* //QACJ 3443: amarinm1: There is no recursion - concatenation is applied to the second macro. */ \
    mDATRead(U8Bit, VEH_SPEED, Default)

#define mReadIsOverSpeedWarningEnabled() \
    /* //QACJ 3443: amarinm1: There is no recursion - concatenation is applied to the second macro. */ \
    (BOOL) mDATRead(U1Bit, EEP_DEM_SURVIT, Default)

#define mIgnitionFallingEdgeIsDetected() \
    (TOSReadSignal(cTOSSignalFalling_PWR_IGN_LAP_BUZ))


//------------------------------------------------------------------------------
// Local types
//------------------------------------------------------------------------------

// This is an example:
// typedef Expression   tTypeName;

//------------------------------------------------------------------------------
// Local data
//------------------------------------------------------------------------------

// This is an example:
// static  tType   VariableName;
// static  tType*  pVariableName;
// static  U8      u8VariableName;
// static  U16*    pu16VariableName;

static tTOSTimer    OverSpeedTimer;
static U8           u8NumberOfSeatBeltWarningActivations;
static BOOL         bSeatBeltWarningIsPresent;
static BOOL         bOverSpeedWarningIsPresent;
static BOOL         bOverSpeedConditionIsPresent;
static BOOL         bExtLightsWarningIsPresent;

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

static MEM_TYPE void ExternalLightsManagement( void );
static MEM_TYPE void SeatBeltManagement( void );
static MEM_TYPE void OverSpeedManagement( void );
static MEM_TYPE void CheckForOverSpeedConditionPresent( void );

#ifdef X90_PROJECT
static MEM_TYPE void LAPBuzManagement_Static(void);
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
static MEM_TYPE void ExternalLightsManagement( void )
{
    if ( bExtLightsWarningIsPresent == cFalse )
    {
        if (   (mDATRead(U1Bit, PWR_IGN, Default)     == cFalse)
            && (mDATRead(U1Bit, FR_DOORS_SW, Default) == cTrue)
            && (   (mDATRead(U1Bit, POSITION_LIGHTS, Default) == cTrue) 
                || (   (mDATRead(U1Bit, EEP_FEU_BROUILLARD, Default) == cTrue)
                    && (mDATRead(U1Bit, RR_FOG_SW, Default)          == cTrue)
                   )
               )
           )
        {
            bExtLightsWarningIsPresent = cTrue;
            mDATWriteTable(U1Bit, BUZZER, eBUZZER_ExtLights, cTrue, Default);
        }
    }
    else // bExtLightsWarningIsPresent == cTrue
    {
        if (   (mDATRead(U1Bit, PWR_IGN, Default)     != cFalse)
            || (mDATRead(U1Bit, FR_DOORS_SW, Default) != cTrue)
            || (   (mDATRead(U1Bit, POSITION_LIGHTS, Default) != cTrue) 
                && (   (mDATRead(U1Bit, EEP_FEU_BROUILLARD, Default) != cTrue)
                    || (mDATRead(U1Bit, RR_FOG_SW, Default)          != cTrue)
                   )
               )
           )
        {
            bExtLightsWarningIsPresent = cFalse;
            mDATWriteTable(U1Bit, BUZZER, eBUZZER_ExtLights, cFalse, Default);
        }
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
static MEM_TYPE void SeatBeltManagement( void )
{
    if ( bSeatBeltWarningIsPresent == cFalse )
    {
        if (   (mReadIsSeatBeltWarningEnabled() == cTrue)
            && (mDATRead(U1Bit, PWR_IGN, Default) == 1)
            && (mReadCurrentSpeed() > mReadSeatBeltSpeedThreshold())
            && (mDATRead(U1Bit, SEATBELT_REMINDER_SW, Default) == 1)   
            && (u8NumberOfSeatBeltWarningActivations < 
                    mReadMaxNumberOfSeatBeltWarningActivations())   )
        {
            bSeatBeltWarningIsPresent = cTrue;
            u8NumberOfSeatBeltWarningActivations++;
            mDATWriteTable(U1Bit, BUZZER, eBUZZER_SeatBelt, cTrue, Default);
        }
    }
    else // bSeatBeltWarningIsPresent == cTrue
    {
        if (   (mReadIsSeatBeltWarningEnabled() == cFalse)
            || (mDATRead(U1Bit, SEATBELT_REMINDER_SW, Default) == 0)
            || (mDATRead(U1Bit, PWR_IGN, Default) == 0)   )
        {
            bSeatBeltWarningIsPresent = cFalse;
            mDATWriteTable(U1Bit, BUZZER, eBUZZER_SeatBelt, cFalse, Default);
        }
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
static MEM_TYPE void OverSpeedManagement( void )
{
    if ( bOverSpeedWarningIsPresent == cFalse )
    {
        if (   (mReadIsOverSpeedWarningEnabled() == cTrue)
            && (mDATRead(U1Bit, PWR_IGN, Default) == 1)
            && (bOverSpeedConditionIsPresent == cTrue)   )
        {
            bOverSpeedWarningIsPresent = cTrue;
            mDATWriteTable(U1Bit, BUZZER, eBUZZER_OverSpeed, cTrue, Default);
        }
    }
    else // bOverSpeedWarningIsPresent == cTrue
    {
        if (   (mReadIsOverSpeedWarningEnabled() == cFalse)
            || (mDATRead(U1Bit, PWR_IGN, Default) == 0)
            || (mReadCurrentSpeed() < cOverSpeedWarningDeactivationThreshold)  )
        {
            bOverSpeedWarningIsPresent = cFalse;
            bOverSpeedConditionIsPresent = cFalse;
            mDATWriteTable(U1Bit, BUZZER, eBUZZER_OverSpeed, cFalse, Default);
        }
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
static MEM_TYPE void CheckForOverSpeedConditionPresent( void )
{
    BOOL bOverSpeedTimerIsStartedL;
    BOOL bOverSpeedTimerIsElapsedL;

    if (mReadCurrentSpeed() > cOverSpeedWarningActivationThreshold)
    {
        bOverSpeedTimerIsStartedL = TOSIsTimerStarted(&OverSpeedTimer);

        if ( bOverSpeedTimerIsStartedL == cFalse )
        {
            if ( bOverSpeedConditionIsPresent == cFalse )
            {
                TOSStartTimer(&OverSpeedTimer);
            }
            else // bOverSpeedConditionIsPresent == cTrue
            {
                // Do nothing
            }
        }
        else // Timer is started
        {
            bOverSpeedTimerIsElapsedL = TOSIsTimerElapsed(&OverSpeedTimer, 
                                       cOverSpeedDetectionDurationInTimerTicks);
            if ( bOverSpeedTimerIsElapsedL == cTrue )
            {
                bOverSpeedConditionIsPresent = cTrue;
            }
            else
            {
                // Do nothing
            }
        }
    }
    else
    {
        bOverSpeedConditionIsPresent = cFalse;
        TOSStopTimer(&OverSpeedTimer);
    }
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
void LAPBuzInitialize( void )
{
    u8NumberOfSeatBeltWarningActivations = 0;
    bSeatBeltWarningIsPresent = cFalse;
    bOverSpeedWarningIsPresent = cFalse;
    bOverSpeedConditionIsPresent = cFalse;
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
void LAPBuzEnterActiveState( void )
{
    TOSSeqActivateGraph( cTOSSeqGraphIdLAPBuzMainGraph );
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
void LAPBuzLeaveActiveState( void )
{
    TOSSeqDeactivateGraph( cTOSSeqGraphIdLAPBuzMainGraph );
    TOSStopTimer(&OverSpeedTimer);
   
    mDATWriteTable(U1Bit, BUZZER, eBUZZER_SeatBelt, cFalse, Default);
    mDATWriteTable(U1Bit, BUZZER, eBUZZER_OverSpeed, cFalse, Default);
    mDATWriteTable(U1Bit, BUZZER, eBUZZER_ExtLights, cFalse, Default);

    LAPBuzInitialize();
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
void LAPBuzManagement( void )
{
#ifdef X90_PROJECT
    LAPBuzManagement_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPBuzManagement_Static(void)
{
#endif

    BOOL bIgnitionFallingEdgeIsDetectedL;

    if (   (mReadIsOverSpeedWarningEnabled() == cTrue)
        && (bOverSpeedWarningIsPresent       == cFalse)   )
    {
        CheckForOverSpeedConditionPresent();
    }
    else
    {
        bOverSpeedConditionIsPresent = cFalse;
        TOSStopTimer(&OverSpeedTimer);
    }

    ExternalLightsManagement();
    SeatBeltManagement();
    OverSpeedManagement();

    bIgnitionFallingEdgeIsDetectedL = mIgnitionFallingEdgeIsDetected();
    
    if ( bIgnitionFallingEdgeIsDetectedL == cTrue)
    {
        u8NumberOfSeatBeltWarningActivations = 0;
    }
}