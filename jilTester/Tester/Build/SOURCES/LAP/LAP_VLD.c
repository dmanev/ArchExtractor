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
// Component:    LAP_VLD
// -----------------------------------------------------------------------------
// $Date:   Mar 10 2010 12:46:50  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_VLD/LAP_VLD.c-arc  $
// $Revision:   1.15  $
// -----------------------------------------------------------------------------  
//  $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_VLD/LAP_VLD.c-arc  $
// 
//    Rev 1.15   Mar 10 2010 12:46:50   amanevd
// Cm007212: Code review corrections
// 
//    Rev 1.14   Feb 25 2010 17:02:54   adzhelp
// Cm007212:  HWP: Implementation of SC detection of Verlog LED in sleep mode mode to LAP_DLK
// 
//    Rev 1.13   Feb 25 2010 15:00:44   adzhelp
// Cm007634: VERLOG LED protection moved to LAP_DLK
// 
//    Rev 1.12   Feb 24 2010 15:47:08   adzhelp
// Cm007212:  HWP: Implementation of SC detection of Verlog LED in sleep mode
// 
//    Rev 1.11   Feb 10 2010 16:48:18   amanevd
// Cm007075: Volatile Faults and Deprotection cleared at IGN ON
// 
//    Rev 1.10   Jan 18 2010 14:02:42   amanevd
// Cm006833: portected state:
// 1,5s period, 0,66 Hz at 3,33% duty cycle (50ms led on)
// 
//    Rev 1.9   Dec 15 2009 10:53:42   amanevd
// Cm005566: LED_VERLOG is not turned off prior attempt to protect it
// 
//    Rev 1.8   Dec 14 2009 11:02:20   amanevd
// Cm005566: Full Hardware Protection
// 
//    Rev 1.7   Nov 04 2009 17:52:10   amanevd
// Cm005566: Simplified Protection
// 
//    Rev 1.6   May 21 2009 12:37:22   amanevd
// Cm003272 - CCover justification - NO IMPACT ON REAL CODE
// 
//    Rev 1.5   May 13 2009 14:41:20   amanevd
// Cm003272 - QAC fix - NO IMPACT ON REAL CODE
// 
//    Rev 1.4   May 07 2009 10:52:18   amanevd
// Cm003272 - Finishing part 3 - pre-integration
// 
//    Rev 1.3   Apr 29 2009 13:14:20   amanevd
// Cm003272 - Intermediate part 3 
// - PRS compliance
// 
//    Rev 1.2   Apr 24 2009 17:17:16   amanevd
// Cm003272 - Finishing part 2 - pre-integration
// 
//    Rev 1.1   Apr 22 2009 19:23:58   amanevd
// Cm003272 - Finishing part 1 - pre-integration
// 
//    Rev 1.0   Feb 23 2009 16:33:02   amanevd
// Initial revision.
//
//=============================================================================

//-----------------------------------------------------------------------------
//  Body Identification
//-----------------------------------------------------------------------------
#define LAP_VLD  "LAP_VLD"

//-----------------------------------------------------------------------------
//  Included files
//
//  #include <system_file_name.h>
//  #include "project_file_name.h"
//-----------------------------------------------------------------------------
#include "tos.h"
#include "dat.h"
#include "LAP_VLD.h"
#include "LAP_VLD.hgr"

//-----------------------------------------------------------------------------
//  Local constants
//
//  #define cConstantName   ((tType) ConstantValue)
//-----------------------------------------------------------------------------
// Tempo value for different led pattern
#define cLedVerlogAlarmValueInUs    ((U32)20000UL)

#define cGraphEngineSleepPeriodMs   ((U8)20)

#define cTempo40ms                  ((U8)(40/cGraphEngineSleepPeriodMs))
#define cTempo1460ms                ((U8)(1460/cGraphEngineSleepPeriodMs))

#define cTempo125ms                 ((U8)(130/cGraphEngineSleepPeriodMs))

#define cTempo250ms                 ((U8)(260/cGraphEngineSleepPeriodMs))

#define cLedOff                     ((BOOL) 0)
#define cLedOn                      ((BOOL) 1)

// HW Protection
#define cMaxU8                      ((U8) 0xFFU)

//-----------------------------------------------------------------------------
//  Local macros
//
//  #define mMacroName   (MacroDefinition)
//-----------------------------------------------------------------------------

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
static U8   u8CurrentLedPattern;
static BOOL bLedState;

static U8   u8LedTempoDuration;

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
static void SetVerlogLedOutput(const BOOL bStateP);

#ifdef X90_PROJECT
static MEM_TYPE void LAPVldInitPattern_Static(void);
static MEM_TYPE void LAPVldTreatCurrentPattern_Static(void);
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
//  DESCRIPTION :
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//=============================================================================
static void SetVerlogLedOutput(const BOOL bStateP)
{
    mDATWrite(U1Bit, VERLOG_LED, bStateP, Default);
    mDATWrite(U1Bit, VERLOG_LEDDirect, bStateP, Default);
}

//=============================================================================
//============================ EXPORTED FUNCTIONS =============================
//=============================================================================

//=============================================================================
//  DESCRIPTION : Read the led pattern
//                Switches the pattern and the led state, starts the timer with 
//                associated value switch ON or OFF the led
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//=============================================================================
void LAPVldInitPattern(void)
{
#ifdef X90_PROJECT
    LAPVldInitPattern_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPVldInitPattern_Static(void)
{
#endif
    // Read the led pattern requested
    u8CurrentLedPattern = mDATRead(U8Bit, LedVerlogPattern, Default);

    switch (u8CurrentLedPattern)
    {
        case cDATVehicleProtectedVerlogPattern:
        bLedState           = cLedOn;
        u8LedTempoDuration  = cTempo40ms;
        break;

        case cDATLearningVerlogPattern:
        bLedState           = cLedOn;
        u8LedTempoDuration  = cTempo250ms;
        break;

        case cDATKeyNotRecognizedVerlogPattern:
        bLedState           = cLedOn;
        u8LedTempoDuration  = cTempo125ms;
        break;

        case cDATSwitchOnVerlogPattern:
        bLedState   = cLedOn;
        break;

        case cDATSwitchOffVerlogPattern:
        bLedState   = cLedOff;
        break;

        //CCOV: amanevd: Cannot be covered because this default case rises explicit assert
        default:
        mLIBassert(cFalse);
        break;
    }

    SetVerlogLedOutput(bLedState);
}

//=============================================================================
//  DESCRIPTION : Switch the led state for blinking patterns
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//=============================================================================
void LAPVldTreatCurrentPattern(void)
{
#ifdef X90_PROJECT
    LAPVldTreatCurrentPattern_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPVldTreatCurrentPattern_Static(void)
{
#endif

    switch (u8CurrentLedPattern)
    {
        case cDATVehicleProtectedVerlogPattern:
        if (bLedState == cLedOn)
        {
            bLedState           = cLedOff;
            u8LedTempoDuration  = cTempo1460ms;
        }
        else
        {
            bLedState           = cLedOn;
            u8LedTempoDuration  = cTempo40ms;
        }
        break;

        case cDATLearningVerlogPattern:
        if (bLedState == cLedOn)
        {
            bLedState           = cLedOff;
            u8LedTempoDuration  = cTempo250ms;
        }
        else
        {
            bLedState           = cLedOn;
            u8LedTempoDuration  = cTempo250ms;
        }
        break;

        case cDATKeyNotRecognizedVerlogPattern:
        if (bLedState == cLedOn)
        {
            bLedState           = cLedOff;
            u8LedTempoDuration  = cTempo125ms;
        }
        else
        {
            bLedState           = cLedOn;
            u8LedTempoDuration  = cTempo125ms;
        }
        break;

        //CCOV: amanevd: Cannot be covered because this default case rises explicit assert
        default:
        mLIBassert(cFalse);
        break;
    }
    SetVerlogLedOutput(bLedState);
}

//=============================================================================
//  DESCRIPTION : Test the end of a half pattern for blinking pattern
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//=============================================================================
BOOL LAPVldCurrentLedPattern(void)
{
    return (   (u8CurrentLedPattern != cDATSwitchOnVerlogPattern)
            && (u8CurrentLedPattern != cDATSwitchOffVerlogPattern)
            && (u8LedTempoDuration == 0) );
}

//=============================================================================
//  DESCRIPTION : Test if a new pattern is requested
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//=============================================================================
BOOL LAPVldNewLedPattern(void)
{
    if (u8LedTempoDuration > 0)
    {
        u8LedTempoDuration--;
    }
    return (u8CurrentLedPattern != mDATRead(U8Bit, LedVerlogPattern, Default));
}

//*****************************************************************************
//  DESCRIPTION         : Initialize the component
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
void LAPVldInitialize(void)
{
    // Pattern must be 20 ms
    mLIBassert((cGraphEngineSleepPeriodMs*1000UL) == cLedVerlogAlarmValueInUs);
    mLIBassert(mDATRead(U1Bit, VERLOG_LED, Default) == cLedOff);
    mLIBassert(mDATRead(U8Bit, LedVerlogPattern, Default) == cDATSwitchOffVerlogPattern);

    // Initialize the local variables
    u8LedTempoDuration      = 0;
    u8CurrentLedPattern     = cDATSwitchOffVerlogPattern;
    bLedState               = cLedOff;
   
    mDATWrite(U1Bit, VERLOG_LEDProtection, 0, Default);

    TOSSeqActivateGraph(cTOSSeqGraphIdLAPVldPatternManagement);
}
