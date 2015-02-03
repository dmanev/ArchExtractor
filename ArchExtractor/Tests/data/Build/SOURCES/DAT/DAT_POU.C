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
// Component:    DAT_POU
// -----------------------------------------------------------------------------
// $Date:   Mar 19 2010 16:04:50  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_POU/DAT_POU.C-arc  $
// $Revision:   1.7  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_POU/DAT_POU.C-arc   $
// 
//    Rev 1.7   Mar 19 2010 16:04:50   adzhelp
// Cm006656: Code review corrections
// 
//    Rev 1.6   Dec 14 2009 11:42:28   adzhelp
// Cm005566: Implementation of full HW protection and overvoltage protection
// 
//    Rev 1.5   Nov 26 2009 14:16:48   adzhelp
// Cm005566: QAC and unit test updates
// 
//    Rev 1.4   Nov 20 2009 17:36:26   akodzhh
// Cm005566: Added read macros for HW protection, used in TFC diag.
// 
//    Rev 1.3   Nov 04 2009 16:23:02   adzhelp
// Cm005566: Implementation of HW Protection
// 
//    Rev 1.2   Oct 07 2009 09:07:08   adzhelp
// Cm005497: Configuration of LDB_DOU according to ECUType 
// 
//    Rev 1.1   Mar 20 2009 17:32:28   adzhelp
// Cm003619: Parameterization needed for diagnostics
// 
//    Rev 1.0   10 Nov 2008 10:26:18   ailievb
// Initial revision.
//******************************************************************************

//------------------------------------------------------------------------------
// Body Identification
//------------------------------------------------------------------------------
#define dat_pst  "dat_pou"

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------
#include "lib.h"
#include "tos.h"
#include "dat.h"
#include "dat_pou.h"
#include "dat_poux.h"

//------------------------------------------------------------------------------
// Local constants
//------------------------------------------------------------------------------

// This is an example:
// #define cConstantName    ((tType)ConstantValue)

//------------------------------------------------------------------------------
// Local macros
//------------------------------------------------------------------------------
#define mSaveProtectionBuffer() \
    mLIBmemcpy(HardMaskBufferCopy, DATPouHardMaskBuffer, cDATPouSizeDouGeneratorMessage)
#define mRestoreProtectionBuffer() \
    mLIBmemcpy(DATPouHardMaskBuffer, HardMaskBufferCopy, cDATPouSizeDouGeneratorMessage)
#define mManageOutputProtection() \
    ManageOutputProtection()

//------------------------------------------------------------------------------
// Local types
//------------------------------------------------------------------------------

// This is an example:
// typedef Expression   tTypeName;

//------------------------------------------------------------------------------
// Local data
//------------------------------------------------------------------------------
static U8 u8EcuType;

static BOOL bOverVoltageProtectionRunning;
static BOOL bAirbagUnlockActivated;
//QACJ 3207: adzhelp: Array is used by macro
static U8 HardMaskBufferCopy[cDATPouSizeDouGeneratorMessage];

//------------------------------------------------------------------------------
// Constant local data
//------------------------------------------------------------------------------

// This is an example:
// static const tType  cConstantName;

//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------
MEM_FAST U8 DATPouSoftOutputBuffer[cDATPouSizeDouGeneratorMessage];
MEM_FAST U8 DATPouDiagMaskBuffer[cDATPouSizeDouGeneratorMessage];
MEM_FAST U8 DATPouDiagBuffer[cDATPouSizeDouGeneratorMessage];
MEM_FAST U8 DATPouHardMaskBuffer[cDATPouSizeDouGeneratorMessage];

#ifndef _QAC_ // adzhelp: Following exported data is used by components 
              //          performing HW protection
BOOL bDO_DATA_IMMOBILIZERDiagEnabled;
BOOL bDO_VERLOGDiagEnabled;

BOOL bDO_VERLOG;
BOOL bDO_VERLOGProtected;
BOOL bVERLOG_LEDDirectProtected;
BOOL bDO_DATA_IMMOBILIZERProtected;
#endif

//------------------------------------------------------------------------------
// Constant exported data
//------------------------------------------------------------------------------
const U8 DATPouInitArray[cDATPouSizeDouGeneratorMessage] = cDATPouInitBufferDouGeneratorMessage;

//------------------------------------------------------------------------------
// Local function prototypes
//------------------------------------------------------------------------------
static MEM_TYPE void ManageOutputProtection(void);

//==============================================================================
//=========================== LOCAL FUNCTIONS ==================================
//==============================================================================

//==============================================================================
// DESCRIPTION:         Manage Outputs Protection on overvoltage
//
// PARAMETERS:          None
//
// RETURN VALUE:        None
//
// DESIGN INFORMATION:  Refer to DCD
//==============================================================================
static MEM_TYPE void ManageOutputProtection(void)
{
    mDATWrite(U1Bit, RR_WIPER_RR_FOG_LAMPProtection, cTrue, Delayed);
    mDATWrite(U1Bit, FRONT_WIPERProtection, cTrue, Delayed);
    mDATWrite(U1Bit, DEFROSTERProtection, cTrue, Delayed);
    mDATWrite(U1Bit, DI_LEFTProtection, cTrue, Delayed);
    mDATWrite(U1Bit, DI_RIGHTProtection, cTrue, Delayed);
    
    if (bAirbagUnlockActivated == cFalse)
    {
        mDATWrite(U1Bit, LOCK_DOORSProtection, cTrue, Delayed);
        mDATWrite(U1Bit, UNLOCK_DOORSProtection, cTrue, Delayed);
        mDATWrite(U1Bit, UNLOCK_DRIVER_DOORProtection, cTrue, Delayed);
    }
    else
    {
        mDATWrite(U1Bit, LOCK_DOORSProtection, cFalse, Delayed);
        mDATWrite(U1Bit, UNLOCK_DOORSProtection, cFalse, Delayed);
        mDATWrite(U1Bit, UNLOCK_DRIVER_DOORProtection, cFalse, Delayed);
    }
    
    mDATWrite(U1Bit, HORN_RLProtection, cTrue, Delayed);
    mDATWrite(U1Bit, BAT_LIGHT_TEMPOProtection, cTrue, Delayed);
}

//==============================================================================
//=========================== EXPORTED FUNCTIONS ===============================
//==============================================================================

//==============================================================================
// DESCRIPTION : Initialise DAT_POU and DAT_DOU component
//  
// PARAMETERS (Type,Name,Min,Max) :  none
//
// RETURN VALUE :  none
// 
// DESIGN INFORMATION :  refer to Detailed Design Document
//==============================================================================
void DATPouInit(void)
{
    bOverVoltageProtectionRunning = cFalse;
    mLIBmemcpy(DATPouSoftOutputBuffer,DATPouInitArray,cDATPouSizeDouGeneratorMessage);
    mLIBmemcpy(DATPouDiagBuffer,DATPouInitArray,cDATPouSizeDouGeneratorMessage);
    DATDouInit(DATPouInitArray);
}

//==============================================================================
// DESCRIPTION : Modifies the logical output buffer before writing
//  
// PARAMETERS (Type,Name,Min,Max) :  none
//
// RETURN VALUE :  none
// 
// DESIGN INFORMATION :  refer to Detailed Design Document
//==============================================================================
MEM_TYPE void DATPouPrepareRefresh(void)
{
    U8 i;

    // Check for change of ECU Type
    if (u8EcuType != mDATRead(U8Bit, EEP_ECUType, Default))
    {
        // Switch pins configuration
        u8EcuType = mDATRead(U8Bit, EEP_ECUType, Default);
        #if !defined(COMPILATION_NATIVE) || defined(UTEST)
        LDBControl(cLDBChannelDou, (tCtrl)(cLDBDouSetEcuType0 + u8EcuType));
        #endif
    }

    // Overvoltage protection prsFS_HWP-982
    if (mDATRead(U1Bit, OverVoltageIsDetected, Default) != cFalse)
    {
        if (bOverVoltageProtectionRunning == cFalse)
        {
            bOverVoltageProtectionRunning = cTrue;
            mSaveProtectionBuffer();
        }
        // all protected outputs except LED outputs and interface outputs
        mManageOutputProtection();
        // shall be called periodically in order to disable any re-activated outputs
    }
    else // normal voltage
    {
        if (bOverVoltageProtectionRunning != cFalse)
        {
            bOverVoltageProtectionRunning = cFalse;
            mRestoreProtectionBuffer();
        }
        else
        {
            // overvoltage protection not running
        }
    }

    // Prepare DOU buffer
    for (i = 0; i < cDATPouSizeDouGeneratorMessage; i++)
    { 
        // Disable all protected outputs;
        // Disable all masked outputs, write soft outputs, except diag masked bits
        DATDouOutputBuffer[i] = ( (U8)~DATPouHardMaskBuffer[i]) & //HW protection
             (
                (U8) ( (U8)(DATPouSoftOutputBuffer[i] & ((U8)~DATPouDiagMaskBuffer[i])) // Diag masking
                      |(U8)(DATPouDiagBuffer[i] & DATPouDiagMaskBuffer[i]))
             );
    }
}

//==============================================================================
// DESCRIPTION : Perform HW configuration depending on EEP_ECUType
//  
// PARAMETERS (Type,Name,Min,Max) :  none
//
// RETURN VALUE :  none
// 
// DESIGN INFORMATION :  refer to Detailed Design Document
//==============================================================================
void DATPouLeaveStartingStepState(void)
{
    u8EcuType = mDATRead(U8Bit, EEP_ECUType, Default);

#if !defined(COMPILATION_NATIVE) || defined(UTEST)
    LDBControl(cLDBChannelDou, (tCtrl)(cLDBDouSetEcuType0 + u8EcuType));
#endif
    
    bAirbagUnlockActivated = mDATRead(U1Bit, EEP_CrashHazardIsRequested, Default);
}

//==============================================================================
// DESCRIPTION : Leave active state
//  
// PARAMETERS (Type,Name,Min,Max) :  none
//
// RETURN VALUE :  none
// 
// DESIGN INFORMATION :  refer to Detailed Design Document
//==============================================================================
void DATPouLeaveActiveState(void)
{
    if (bOverVoltageProtectionRunning != cFalse)
    {
        bOverVoltageProtectionRunning = cFalse;
        mRestoreProtectionBuffer();
    }
}

//==============================================================================
// DESCRIPTION : Modifies the logical output buffer before writing
//  
// PARAMETERS (Type,Name,Min,Max) :  none
//
// RETURN VALUE :  none
// 
// DESIGN INFORMATION :  refer to Detailed Design Document
//==============================================================================
void DATPouActivateFinalTest(void)
{
    // Deactivate application output
    mLIBmemset(DATPouDiagMaskBuffer, 0xFFU, cDATPouSizeDouGeneratorMessage);
}

//==============================================================================
// DESCRIPTION : Sets a flag that allows overvoltage protection of lock/unlock
//               outputs
//  
// PARAMETERS (Type,Name,Min,Max) :  none
//
// RETURN VALUE :  none
// 
// DESIGN INFORMATION :  refer to Detailed Design Document
//==============================================================================
void DATPouAirbagUnlockStarted(void)
{
    bAirbagUnlockActivated = cTrue;
    mDATDouRefreshOutput();
}

//==============================================================================
// DESCRIPTION : Resets a flag that allows overvoltage protection of lock/unlock
//               outputs
//  
// PARAMETERS (Type,Name,Min,Max) :  none
//
// RETURN VALUE :  none
// 
// DESIGN INFORMATION :  refer to Detailed Design Document
//==============================================================================
void DATPouAirbagUnlockFinished(void)
{
    bAirbagUnlockActivated = cFalse;
}

