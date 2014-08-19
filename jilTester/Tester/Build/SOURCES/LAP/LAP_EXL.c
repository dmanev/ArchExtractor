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
// Component:    LAP_EXL
// -----------------------------------------------------------------------------
// $Date:   Sep 24 2009 15:07:12  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_EXL/LAP_EXL.c-arc  $
// $Revision:   1.1  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_EXL/LAP_EXL.c-arc  $
// 
//    Rev 1.1   Sep 24 2009 15:07:12   adzhelp
// Cm004744: Integration changes
// 
//    Rev 1.0   Sep 14 2009 16:12:16   akodzhh
// Initial revision.
//******************************************************************************
#endif

//------------------------------------------------------------------------------
// Body Identification
//------------------------------------------------------------------------------
#define lap_exl   "lap_exl"

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------
#include "lib.h"        
#include "tos.h"        
#include "dat.h"        
#include "lap_exl.h"    
#include "lap_exl.hgr"  

//------------------------------------------------------------------------------
// Local constants
//------------------------------------------------------------------------------
#define cRRFogOutputOn             ((U8)0x00)
#define cRRFogOutputOff            ((U8)0x01)

//------------------------------------------------------------------------------
// Local macros
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Local types
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Local data
//------------------------------------------------------------------------------
static U8 u8LAPExlState;

//------------------------------------------------------------------------------
// Constant local data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Constant exported data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Local function prototypes
//------------------------------------------------------------------------------
#ifdef X90_PROJECT
static MEM_TYPE void LAPExlManagement_Static(void);
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

//==============================================================================
//=========================== EXPORTED FUNCTIONS ===============================
//==============================================================================

//==============================================================================
// DESCRIPTION:         LAPExlEnterActiveState
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  
//==============================================================================
void LAPExlEnterActiveState(void)
{
    mLIBassert(mDATRead(U1Bit, RR_WIPER_RR_FOG_LAMP, Default) == cFalse );
    // RearWiper and RearFog functions are never authorized at same time
    mLIBassert( ( mDATRead(U1Bit, EEP_EV_ARR        , Default)
                &&mDATRead(U1Bit, EEP_FEU_BROUILLARD, Default)) == cFalse );
 
    u8LAPExlState = cRRFogOutputOff;
    TOSSeqActivateGraph(cTOSSeqGraphIdLAPExlGraph);
}

//==============================================================================
// DESCRIPTION:         LAPExlLeaveActiveState
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  
//==============================================================================
void LAPExlLeaveActiveState(void)
{
    mLIBassert(mDATRead(U1Bit, RR_WIPER_RR_FOG_LAMP, Default) == cFalse );
    u8LAPExlState = cRRFogOutputOff;
    TOSSeqDeactivateGraph(cTOSSeqGraphIdLAPExlGraph);
}

//==============================================================================
// DESCRIPTION:         LAPExlManagement
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  
//==============================================================================
void LAPExlManagement(void)
{
#ifdef X90_PROJECT
    LAPExlManagement_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPExlManagement_Static(void)
{
#endif

    BOOL bRRFogAuthorised;

    bRRFogAuthorised = mDATRead(U1Bit, EEP_FEU_BROUILLARD, Default);
    
    switch(u8LAPExlState)
    {
    case cRRFogOutputOff:
        // check On conditions
        if(   ( bRRFogAuthorised == cTrue)
            &&( mDATRead(U1Bit, PWR_IGN, Default)       == cTrue )
            &&( mDATRead(U1Bit, RR_FOG_SW, Default)     == cTrue )
            &&( mDATRead(U1Bit, HIGH_LOW_BEAM, Default) == cTrue ) )
        {
            mDATWrite(U1Bit,RR_WIPER_RR_FOG_LAMP, cTrue, Default);
            u8LAPExlState = cRRFogOutputOn;
        }

        break;
        
    case cRRFogOutputOn:
        // check off conditions
        if(  ( bRRFogAuthorised == cFalse )
           ||( mDATRead(U1Bit, PWR_IGN, Default)       == cFalse )
           ||( mDATRead(U1Bit, RR_FOG_SW, Default)     == cFalse ) 
           ||( mDATRead(U1Bit, HIGH_LOW_BEAM, Default) == cFalse ) )
        {
            mDATWrite(U1Bit,RR_WIPER_RR_FOG_LAMP, cFalse, Default);
            u8LAPExlState = cRRFogOutputOff;
        }
        
        break;

    //CCOV: akodzhh: can't be tested because of assert
    default:
        mLIBassert(cFalse);
        break;
    }

}

