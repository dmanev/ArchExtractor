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
// Component:    DAT_CMN
// -----------------------------------------------------------------------------
// $Date:   Oct 11 2010 16:17:52  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_CMN/DAT_CMN.C-arc  $
// $Revision:   1.36  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_CMN/DAT_CMN.C-arc  $
// 
//    Rev 1.36   Oct 11 2010 16:17:52   adzhelp
// Cm007166: SW version ID updated to 03.08
// 
//    Rev 1.35   Jul 09 2010 14:20:00   adzhelp
// Cm007166: SW version ID updated to B3.07
// 
//    Rev 1.34   Jul 01 2010 13:46:36   adzhelp
// Cm007166: SW version ID updated to 03.06
// 
//    Rev 1.33   Jun 30 2010 15:04:42   adzhelp
// Cm007166: SW version ID updated to 03.05a
// 
//    Rev 1.32   Jun 21 2010 15:48:58   adzhelp
// Cm007166: SW version ID updated to B3.06
// 
//    Rev 1.31   Jun 16 2010 14:40:14   adzhelp
// Cm007166: SW version ID updated to 03.05
// 
//    Rev 1.30   Jun 02 2010 09:29:54   adzhelp
// Cm007166: SW version ID updated to B3.05
// 
//    Rev 1.29   May 19 2010 15:35:02   adzhelp
// Cm007166: SW version ID updated to 03.04
// 
//    Rev 1.28   Mar 31 2010 09:09:06   adzhelp
// Cm007166: SW version ID updated to 03.03
// 
//    Rev 1.27   Mar 22 2010 11:08:54   adzhelp
// Cm007166: SW version ID updated to B3.03
// 
//    Rev 1.26   Mar 05 2010 10:22:48   adzhelp
// Cm007166: SW version ID updated to B3.02
// 
//    Rev 1.25   Mar 02 2010 17:24:50   adzhelp
// Cm007166: SW version ID updated to B3.01d
// 
//    Rev 1.24   Feb 26 2010 08:59:48   adzhelp
// Cm007166: SW version ID updated to B3.01c
// 
//    Rev 1.23   Feb 23 2010 11:25:06   adzhelp
// Cm007166: SW version ID updated to B3.01b
// 
//    Rev 1.22   Feb 19 2010 10:13:12   adzhelp
// Cm007575: Management of no-init flag 'BcmSleepRequested'
// 
//    Rev 1.21   Feb 15 2010 16:14:08   adzhelp
// Cm007166: SW version ID updated to B3.01a
// 
//    Rev 1.20   Feb 13 2010 09:16:32   adzhelp
// Cm007166: SW Version ID updated for VB3.01
// 
//    Rev 1.19   Feb 12 2010 09:45:18   adzhelp
// Cm007166: SW version ID updated to B3.00b
// 
//    Rev 1.18   Feb 05 2010 11:14:06   adzhelp
// Cm007006: Management of a Reset counter
// 
//    Rev 1.17   Feb 03 2010 11:53:30   adzhelp
// Cm005245: Refresh callback for LIB_PCF implemented
// 
//    Rev 1.16   Jan 28 2010 14:10:04   adzhelp
// Cm007166: SW Version ID updated for VB3.01
// 
//    Rev 1.15   Jan 26 2010 14:39:24   adzhelp
// Cm007166: SW version ID updated to B3.00a
// 
//    Rev 1.14   Jan 15 2010 14:15:00   adzhelp
// Cm007166: SW Version ID updated for VB3.00
// 
//    Rev 1.13   Dec 14 2009 12:26:10   adzhelp
// Cm006837: SW Version ID updated to B2.02
// 
//    Rev 1.12   Dec 04 2009 17:09:04   adzhelp
// Cm006837: SW Version ID updated to V02.02
// 
//    Rev 1.11   Nov 30 2009 15:40:46   adzhelp
// Cm006742: FRW / RRW common data added
// 
//    Rev 1.10   Oct 28 2009 11:13:00   adzhelp
// Cm006580: Version edition changed to '01'
// 
//    Rev 1.9   Sep 23 2009 10:25:08   amanevd
// Cm005133: tDATCmnData structure split to tDATCmnData and tDATCmnImmoData
// 
//    Rev 1.8   Sep 03 2009 12:37:04   amanevd
// Cm005133: Diagnostic information is cleared on MERA timeout, VERLOGON included
// 
//    Rev 1.7   Jul 17 2009 14:52:08   adzhelp
// Cm005574: Project checking excluded for simulation
// 
//    Rev 1.6   Jul 15 2009 10:08:32   adzhelp
// Cm005586: Code review corrections
// 
//    Rev 1.5   Jul 14 2009 14:29:18   amanevd
// Cm005586: KeyFrequency signal removed
// 
//    Rev 1.4   Jun 25 2009 09:47:58   adzhelp
// Cm005484: Version number updated for SW2
// 
//    Rev 1.3   Apr 28 2009 09:54:26   adzhelp
// Cm003619: Common object updated for immobilizer and RF integration
// 
//    Rev 1.2   Mar 23 2009 12:28:16   adzhelp
// Cm003465: Added stub functions for DAT_TRP
// 
//    Rev 1.1   Mar 20 2009 17:55:44   adzhelp
// Cm003619, Cm003128, Cm003263: Version number updated and stub interfaces created
// 
//    Rev 1.0   18 Feb 2009 14:18:18   ailievb
// Initial revision.
//******************************************************************************

//--------------------------------------------------------------------------
//  Body Identification
//--------------------------------------------------------------------------
#define dat_cmn   "dat_cmn"

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------
#include "dat.h"
#include "lib_pcf.h"
#include "DAT_CMN.h"

//------------------------------------------------------------------------------
// Local constants
//------------------------------------------------------------------------------
// Software version / revision numbers
// version number
#define cVersionNumber      (U8)0x03U
// version edition
#define cVersionEdition     (U8)0x08U
// version patch: 0x00 for no patch or 'a', 'b', 'c', ...
#define cVersionPatch       (U8)'a'

#define cCarTrp       ((U8)0x01)
#define cAprTrp       ((U8)0x02)


#define cMaxByte            ((U8)0xFFU)

#define cSleepRequestedValue    ((U16)0x4AC3U)
#define cSleepNotRequestedValue ((U16)0x6F91U)

//------------------------------------------------------------------------------
// Local macros
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Local types
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Local data
//------------------------------------------------------------------------------
static U8      TrpResource;

#if !defined(COMPILATION_NATIVE) && !defined(DEBUG)
__no_init static U16 u16SleepRequestedState;
#else
static U16 u16SleepRequestedState;
#endif

//------------------------------------------------------------------------------
// Constant local data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------
tDATCmnData DATCmnData;

tDATCmnImmoData DATCmnImmoData;

// FRW / RRW common data
// Zero initialization is enough
U8 u8DATCmnTPS_ARRET_old;
U8 u8DATCmnTPS_MAX_COUPLBLOC_old;
U8 u8DATCmnTPS_CAD_FIXE_old;
U8 u8DATCmnTPS_APPUILAV_old;
U8 u8DATCmnTPS_ESSUIE_MINI_old;
U8 u8DATCmnTPS_REPRISE_old;

tTOSTimer DATCmnFrRrwDisableTimeout;
tTOSTimer DATCmnFrRrwWipingTimeout;
tTOSTimer DATCmnFrRrwIntermittentPause;
tTOSTimer DATCmnFrRrwMinimumWipingTime;
tTOSTimer DATCmnFrwWashPressThreshold;
tTOSTimer DATCmnRrwWipingTimeoutReprise;

//------------------------------------------------------------------------------
// Constant exported data
//------------------------------------------------------------------------------
const U8 DATCmnVerVersionNum[2] = {0x00U, cVersionNumber};
const U8 DATCmnVerRevisionNum[2] = {cVersionEdition, cVersionPatch};
const U8 DATCmnTfcVersionNum = cVersionNumber;
const U8 DATCmnTfcRevisionNum = cVersionEdition;

//------------------------------------------------------------------------------
// Local function prototypes
//------------------------------------------------------------------------------

//==============================================================================
//=========================== LOCAL FUNCTIONS ==================================
//==============================================================================

//==============================================================================
//=========================== EXPORTED FUNCTIONS ===============================
//==============================================================================

//============================================================================
// DESCRIPTION:  Initialization
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
// 
// DESIGN INFORMATION:  refer to Detailed Design Document
//============================================================================
void DATCmnInitialize(void)
{
    // Init here only data different from zero or cFalse
    DATCmnImmoData.LearningModeInProgress = cDATNoLearningMode;
    DATCmnImmoData.LedVerlogPattern = cDATSwitchOffVerlogPattern;
    DATCmnImmoData.VerlogOn = 1;
    #if (!defined(X90_PROJECT) && !defined(COMPILATION_NATIVE))
        #error "DATCmnData shall be initialized explicitly when cFalse != 0"
    #endif
}
//============================================================================
// DESCRIPTION:  On TOS Control LeaveStartingStepState
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
// 
// DESIGN INFORMATION:  refer to Detailed Design Document
//============================================================================
void DATCmnLeaveStartingStepState(void)
{
    U8 u8ResetCountL;

    mLIBassert(TrpResource == 0);
    #ifndef COMPILATION_NATIVE
        pLIBPcfRefresh = DATCmnPcfRefresh;
    #endif
    mDATControl(Rf,Start);

    // Reset counter management
    u8ResetCountL = mDATRead(U8Bit, EEP_ResetCount, Default);
    if (u8ResetCountL < cMaxByte)
    {
        mDATWrite(U8Bit, EEP_ResetCount, (u8ResetCountL + (U8)1U), Default);
    }
}
//============================================================================
// DESCRIPTION:  On TOS Control GetAprTrpResource
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
// 
// DESIGN INFORMATION:  refer to Detailed Design Document
//============================================================================
void DATCmnGetAprTrpResource(void)
{
    if (TrpResource == 0) // Stop RF
    {
        mDATControl(Rf,Stop);
    }
    TrpResource |= cAprTrp;
}

//============================================================================
// DESCRIPTION:  On TOS Control ReleaseAprTrpResource
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
// 
// DESIGN INFORMATION:  refer to Detailed Design Document
//============================================================================
void DATCmnReleaseAprTrpResource(void)
{
    TrpResource &=~cAprTrp;
    if (TrpResource == 0) // Start RF
    {
        mDATControl(Rf,Start);
    }
}

//============================================================================
// DESCRIPTION:  On TOS Control GetCarTrpResource
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
// 
// DESIGN INFORMATION:  refer to Detailed Design Document
//============================================================================
void DATCmnGetCarTrpResource(void)
{
    if (TrpResource == 0) // Stop RF
    {
        mDATControl(Rf,Stop);
    }
    TrpResource |= cCarTrp;
}

//============================================================================
// DESCRIPTION:  On TOS Control ReleaseCarTrpResource
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
// 
// DESIGN INFORMATION:  refer to Detailed Design Document
//============================================================================
void DATCmnReleaseCarTrpResource(void)
{
    TrpResource &=~ cCarTrp;
    if (TrpResource == 0) // Start RF
    {
        mDATControl(Rf,Start);
    }
}

//============================================================================
// DESCRIPTION:  Performs refresh of tasks when LIB_PCF is being executed
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
// 
// DESIGN INFORMATION:  refer to Detailed Design Document
//============================================================================
void DATCmnPcfRefresh(void)
{
    // This refresh must be performed only for RF operation
    // In active mode of BCM and if resynchronization is needed

    if (  (TrpResource == 0)  // RF active
        &&(mDATRead(U1Bit, BcmSleepMode, Default) == cFalse) // active mode
        &&(DATCmnData.PcfRefreshAllowed != cFalse) )
    {
        TOSSchedule();
        LDBRefreshWatchDog();
    }
}

//============================================================================
// DESCRIPTION: 
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
// 
// DESIGN INFORMATION:  refer to Detailed Design Document
//============================================================================
MEM_TYPE BOOL DATCmnGetBcmSleepRequested (void)
{
    return (u16SleepRequestedState == cSleepRequestedValue);
}

//============================================================================
// DESCRIPTION: 
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
// 
// DESIGN INFORMATION:  refer to Detailed Design Document
//============================================================================
MEM_TYPE void DATCmnSetBcmSleepRequested (BOOL bSleepRequestedP)
{
    u16SleepRequestedState = (bSleepRequestedP != cFalse) ? cSleepRequestedValue
                                                          : cSleepNotRequestedValue;
}
