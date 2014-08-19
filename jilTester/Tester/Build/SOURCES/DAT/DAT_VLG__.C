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
// Component:    DAT_VLG
// -----------------------------------------------------------------------------
// $Date:   Jun 16 2010 15:17:08  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_VLG/DAT_VLG.C-arc  $
// $Revision:   1.27  $
// -----------------------------------------------------------------------------  
//  $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_VLG/DAT_VLG.C-arc  $
// 
//    Rev 1.27   Jun 16 2010 15:17:08   adzhelp
// Cm009191: Return rev. 1.25 and set HW protection threshold to 60
// 
//    Rev 1.26   May 20 2010 14:13:30   amanevd
// Cm008639: function DATVlgIsFrameEmissionStopped updated
// 
//    Rev 1.25   Mar 08 2010 16:07:44   amanevd
// Cm007673: Checking of (0 == EEP_CodeAFSAvailable) replaced with
// (1 == EEP_EraseAFSCodeRequest)
// 
//    Rev 1.24   Feb 20 2010 11:38:26   amanevd
// Cm007272: Check if EEP_CodeAFSAvailable==1  in function DATVlgControlDigitalOutput
// instead on cDATVlgStart control
// 
//    Rev 1.23   Feb 10 2010 16:44:00   amanevd
// Cm007075: Volatile Faults and Deprotection cleared at IGN ON
// 
//    Rev 1.22   Feb 02 2010 14:57:20   amanevd
// Cm005797: Input update on VlgStart control
// 
//    Rev 1.21   Jan 27 2010 10:00:12   amanevd
// Cm007119: Correction of PWR_IGN rising edge detection
// 
//    Rev 1.20   Jan 15 2010 17:48:04   amanevd
// Cm005797: Refreshed LIB inputs on Authentication controls
// 
//    Rev 1.19   Jan 15 2010 11:35:04   amanevd
// Cm007164: Defect counter is increased only if defect is reported for the current
// sample
// 
//    Rev 1.18   Dec 21 2009 13:45:16   amanevd
// Cm005797: On input change LIBVlg2ProcessData() is called
// 
//    Rev 1.17   Dec 15 2009 10:45:22   amanevd
// Cm005566: DO_VERLOG is not protected in case of SC GND
// 
//    Rev 1.16   Dec 14 2009 10:52:16   amanevd
// Cm005566: Full Hardware Protection
// 
//    Rev 1.15   Dec 03 2009 11:37:28   amanevd
// Cm006751: DO_VERLOG set to 0 when not sending frame
// 
//    Rev 1.14   Nov 04 2009 16:32:00   amanevd
// Cm005566: Simplified Protection
// 
//    Rev 1.13   Oct 06 2009 17:25:32   amanevd
// Cm006446: 'EEP_EraseAFSCodeRequest' substituted with 'EEP_CodeAFSAvailable'
// 
//    Rev 1.12   Oct 05 2009 16:32:16   amanevd
// Cm005791: Verlog Serial Line test included
// 
//    Rev 1.11   Sep 21 2009 12:01:56   amanevd
// Cm005044: Now Verlog frame is sent while in Permanent Authentication
// 
//    Rev 1.10   Sep 18 2009 14:19:14   amanevd
// Cm005178: Taking in account AUTVERLOG on the fly
// 
//    Rev 1.9   Sep 18 2009 11:41:48   amanevd
// Cm005178: EEP_AUTVERLOG included as starting condition for Verlog
// 
//    Rev 1.8   Aug 28 2009 10:14:48   amanevd
// Cm004914: Code review corrections
// 
//    Rev 1.7   Jul 17 2009 10:52:58   amanevd
// Cm004914: AFS code is either erased on Routine request or after Ignition counting reaches N_MISE_APC
// 
//    Rev 1.6   Jul 16 2009 13:56:14   amanevd
// Cm005277: NRZ encoding applied
// 
//    Rev 1.5   May 21 2009 11:30:20   amanevd
// Cm003272 - CCover justification - NO IMPACT ON REAL CODE
// 
//    Rev 1.4   May 13 2009 14:45:22   amanevd
// Cm003272 - QAC fix - NO IMPACT ON REAL CODE
// 
//    Rev 1.3   Apr 29 2009 13:12:30   amanevd
// Cm003272 - Intermediate part 3 
// - PRS compliance
// 
//    Rev 1.2   Apr 24 2009 17:17:12   amanevd
// Cm003272 - Finishing part 2 - pre-integration
// 
//    Rev 1.1   Mar 23 2009 18:16:50   amanevd
// Cm003272 - Correction after DCD_LIB_VLG2 Review
// 
//    Rev 1.0   Mar 17 2009 15:53:50   amanevd
// Initial revision.
//
//=============================================================================

//-----------------------------------------------------------------------------
//  Body Identification
//-----------------------------------------------------------------------------
#define DAT_VLG  "DAT_VLG"

//-----------------------------------------------------------------------------
//  Included files
//
//  #include <system_file_name.h>
//  #include "project_file_name.h"
//-----------------------------------------------------------------------------
#include "lib.h"
#include "tos.h"
#include "dat.h"
#include "dat_vlg.h"
#include "dat_vlg.hgr"
#include "lib_vlg2.h"

//-----------------------------------------------------------------------------
//  Local constants
//
//  #define cConstantName   ((tType) ConstantValue)
//-----------------------------------------------------------------------------

#define cNumberOfBytesToSend    ((U8) 10U)

#define cByteSize               ((U8) 8U)

#define cMaxSerialTestCount     ((U8) cByteSize*cNumberOfBytesToSend)

#define cMod2                   ((U8) 2U)

//HW Protection
#define cFaultCountWarnThreshold    ((U8) 2U)
#define cFaultCountProtectThreshold ((U8) 60U)
#define cMaxU8                      ((U8) 0xFFU)

#define cVlgHighState           ((U8) 0U)
#define cVlgLowState            ((U8) 1U)

#define cOverloadThreshold      ((U16)600UL)

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

typedef struct tDatVlgLocalDataType
{
    U16     SecretKey;
    BOOL    Ignition;
}tDatVlgLocalData;

//-----------------------------------------------------------------------------
//  Local data
//
//  static  tType   VariableName;
//  static  tType*  pVariableName; 
//-----------------------------------------------------------------------------

static tDatVlgLocalData DatVlgLocalData;
//QACJ 3207:amanevd: This is because QAC sees mLIBmem(..) macros as NOP
static tDatVlgLocalData DatVlgLocalDataPrev;

static U8   u8LibVlg2TickCounter;
static U8   u8LibVlg2SerialTestCounter;

static BOOL bPWR_IGNOld;
static BOOL bDO_VERLOGSCtoGnd;
static BOOL bDO_VERLOGSCtoBat;
static U8   u8FaultCounter;

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
BOOL bDATVlgSerialTestInProgress;

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
static MEM_TYPE void DATVlgSerialLineTest(void);
static MEM_TYPE void DATVlgForceInputUpdate(void);

#ifdef X90_PROJECT
static MEM_TYPE void DATVlgInit_Static(void);
static MEM_TYPE void DATVlgInputProcess_Static(void);
static MEM_TYPE void DATVlgProtectionTask_Static(void);
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
static MEM_TYPE void DATVlgSerialLineTest(void)
{
    BOOL    bTempL;

    // Sends 0x55 pattern, which is 01010101b
    if(cMaxSerialTestCount > u8LibVlg2SerialTestCounter)
    {
        mDATWrite(U1Bit, DO_VERLOG, 
            !(BOOL)(u8LibVlg2SerialTestCounter % cMod2), Default);
        u8LibVlg2SerialTestCounter++;
    }
    else
    {
        mDATWrite(U1Bit, DO_VERLOG, 0, Default);
        u8LibVlg2SerialTestCounter = 0;
        bDATVlgSerialTestInProgress = cFalse;
        bTempL = LIBVlg2FrameEmissionStopped();
        if(cFalse != bTempL)
        {
            TOSSeqDeactivateGraph(cTOSSeqGraphIdDATVlgOutputProtection);
        }
    }
}

//=============================================================================
//  DESCRIPTION : Forces PWR_IGN and SKey update
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//=============================================================================
static MEM_TYPE void DATVlgForceInputUpdate(void)
{
    LIBVlg2UpdateSecretKey(mDATRead(U16Bit, EEP_VerlogSKey, Default));
    LIBVlg2UpdateIgnition(mDATRead(U1Bit, PWR_IGN, Default));
    LIBVlg2ProcessData();
}
//=============================================================================
//============================ EXPORTED FUNCTIONS =============================
//=============================================================================

//=============================================================================
//  DESCRIPTION         : Control Digital Output
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//=============================================================================
void DATVlgControlDigitalOutput(const BOOL bStateP)
{
    if(     (cTrue == mDATRead(U1Bit, EEP_AUTVERLOG, Default))
        &&  (cTrue == mDATRead(U1Bit, EEP_EraseAFSCodeRequest, Default))
      )
    {
        mDATWrite(U1Bit, DO_VERLOG, (!bStateP), Default);
    }
    else
    {
        if(0 != mDATRead(U1Bit, DO_VERLOG, Default))
        {
            mDATWrite(U1Bit, DO_VERLOG, 0, Default);
        }
    }
}

//=============================================================================
//  DESCRIPTION         : Component initialization.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//=============================================================================
void DATVlgInit(void)
{
#ifdef X90_PROJECT
    DATVlgInit_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DATVlgInit_Static(void)
{
#endif
    DatVlgLocalData.SecretKey   = mDATRead(U16Bit, EEP_VerlogSKey, Default);
    DatVlgLocalData.Ignition    = mDATRead(U1Bit, PWR_IGN, Default);
    u8LibVlg2TickCounter        = 0;
    bDATVlgSerialTestInProgress = cFalse;
    bPWR_IGNOld                 = cFalse;
    u8FaultCounter  = 0;

    LIBVlg2Init(DatVlgLocalData.SecretKey, 
                (tpLIBVlg2ControlDigitalOutput)&DATVlgControlDigitalOutput);
    mLIBmemcpy(&DatVlgLocalDataPrev, &DatVlgLocalData, sizeof(tDatVlgLocalData));
}

//=============================================================================
//  DESCRIPTION         : Process DAT Vlg control
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//=============================================================================
MEM_TYPE void DATVlgControl(const tCtrl Ctrl)
{
    tTOSSeqGraphStateType tGraphState;

    switch (Ctrl)
    {
        case cDATVlgStart:

        tGraphState = TOSSeqGraphState(cTOSSeqGraphIdDATVlgInput);

        if (cTOSSeqActiveGraph != tGraphState)
        {
            TOSSeqActivateGraph(cTOSSeqGraphIdDATVlgInput);

            DATVlgForceInputUpdate();

            tGraphState = TOSSeqGraphState(cTOSSeqGraphIdDATVlgOutputProtection);

            if (cTOSSeqActiveGraph != tGraphState)
            {
                bPWR_IGNOld = cFalse;

                TOSSeqActivateGraph(cTOSSeqGraphIdDATVlgOutputProtection);
            }
        }
        break;

        case cDATVlgStop:
        LDBControl(cLDBChannelTrp, cLDBTrpStopVerlog);
        break;

        case cDATVlgSerialTest:
        bDATVlgSerialTestInProgress = cTrue;
        u8LibVlg2SerialTestCounter = 0;
        u8FaultCounter  = 0;
        tGraphState = TOSSeqGraphState(cTOSSeqGraphIdDATVlgOutputProtection);
        if (cTOSSeqActiveGraph != tGraphState)
        {
            mDATWrite(U1Bit, DO_VERLOGProtection, 0, Default);
            TOSSeqActivateGraph(cTOSSeqGraphIdDATVlgOutputProtection);
        }
        break;

        //CCOV: amanevd: Cannot be covered because this default case rises explicit assert
        default:
        mLIBassert(cFalse);
        break;
    }
}

//=============================================================================
//  DESCRIPTION         : Maintain active state
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//=============================================================================
void DATVlgIsAnybodyMaintainActiveState(void)
{
    tTOSSeqGraphStateType tGraphState;

    tGraphState = TOSSeqGraphState(cTOSSeqGraphIdDATVlgInput);

    if (    (cTOSSeqActiveGraph == tGraphState)
        ||  (cFalse != bDATVlgSerialTestInProgress)
       )
    {
        TOSWriteSignal(cTOSSignalSomebodyMaintainActiveState);
    }
    else
    {
        //Nothing
    }
}

//=============================================================================
//  DESCRIPTION         : Process Input.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//=============================================================================
void DATVlgInputProcess(void)
{
#ifdef X90_PROJECT
    DATVlgInputProcess_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DATVlgInputProcess_Static(void)
{
#endif

    REG rResL;

    DatVlgLocalData.SecretKey   = mDATRead(U16Bit, EEP_VerlogSKey, Default);
    DatVlgLocalData.Ignition    = mDATRead(U1Bit, PWR_IGN, Default);

    //QACJ 0543:amanevd: Result of mLIBmemcmp() expansion to NOP() in LIB.h
    rResL = (REG)mLIBmemcmp(&DatVlgLocalData, 
                &DatVlgLocalDataPrev, 
                sizeof(tDatVlgLocalData));

    if ((REG)0 != rResL)
    {
        LIBVlg2UpdateSecretKey(DatVlgLocalData.SecretKey);
        LIBVlg2UpdateIgnition(DatVlgLocalData.Ignition);
    }

    LIBVlg2ProcessData();
    mLIBmemcpy(&DatVlgLocalDataPrev, &DatVlgLocalData, sizeof(tDatVlgLocalData));
}

//=============================================================================
//  DESCRIPTION         : Check if frame emission is stopped
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : BOOL
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//=============================================================================
BOOL DATVlgIsFrameEmissionStopped(void)
{
    return LIBVlg2FrameEmissionStopped();
}

//=============================================================================
//  DESCRIPTION         : process KeyIsAuthenticated control
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//=============================================================================
void DATVlgKeyIsAuthenticated(void)
{
    LIBVlg2AuthenticationSuccess(cTrue);
    DATVlgForceInputUpdate();
}

//=============================================================================
//  DESCRIPTION         : process KeyIsNotAuthenticated control
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//=============================================================================
void DATVlgKeyIsNotAuthenticated(void)
{
    LIBVlg2AuthenticationSuccess(cFalse);
    DATVlgForceInputUpdate();
}

//=============================================================================
//  DESCRIPTION         : Callback from LDB controling frame generation
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//=============================================================================
void DATVlgCallBackCtrl(void)
{    
    if(u8LibVlg2TickCounter > 0)
    {
        if(cFalse == bDATVlgSerialTestInProgress)
        {
            LIBVlg2TimerTick();
        }
        else
        {
            DATVlgSerialLineTest();
        }

        u8LibVlg2TickCounter = 0;
    }
    else
    {
        u8LibVlg2TickCounter++;
    }
}

//=============================================================================
//  DESCRIPTION         : Callback from LDB check for SC to GND of DIO_ECM
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//=============================================================================
MEM_TYPE void DATVlgCallBackEndCtrl(const tCtrl CtrlP, const tStatus StatusP)
{
    U8  u8TempL;

    if(CtrlP == cLDBControlCheckDO_VERLOGSCGnd)
    {
        if(cLDBError == StatusP)
        {
            bDO_VERLOGSCtoGnd = cTrue;

            u8FaultCounter++;
            if(u8FaultCounter >= cFaultCountProtectThreshold)
            {
                mDATWrite(U1Bit, DefVerlogToGnd, 1, Default);
                mDATWrite(U1Bit, DefVerlogToBat, 0, Default);
                mDATWrite(U1Bit, EEP_DefVerlogToGnd, 1, Default);

                // Enter in IgnOff State
                u8TempL = mDATRead(U8Bit, EEP_CDVerlog, Default);
                if(u8TempL < cMaxU8)
                {
                    u8TempL ++;
                    mDATWrite(U8Bit, EEP_CDVerlog, u8TempL, Default);
                }
            }
            else
            {
                // Nothing to do
            }
        }
        else
        {
            bDO_VERLOGSCtoGnd = cFalse;
        }
    }
    else if(CtrlP == cLDBControlCheckDO_VERLOGSCBat)
    {
        if(cLDBError == StatusP)
        {
            bDO_VERLOGSCtoBat = cTrue;

            u8FaultCounter++;
            if(u8FaultCounter >= cFaultCountProtectThreshold)
            {
                mDATWrite(U1Bit, DefVerlogToGnd, 0, Default);
                mDATWrite(U1Bit, DefVerlogToBat, 1, Default);
                mDATWrite(U1Bit, DO_VERLOGProtection, 1, Default);
                mDATWrite(U1Bit, EEP_DefVerlogToBat, 1, Default);

                // Enter in IgnOff State
                u8TempL = mDATRead(U8Bit, EEP_CDVerlog, Default);
                if(u8TempL < cMaxU8)
                {
                    u8TempL ++;
                    mDATWrite(U8Bit, EEP_CDVerlog, u8TempL, Default);
                }
            }
            else
            {
                // Nothing to do
            }
        }
        else
        {
            bDO_VERLOGSCtoBat = cFalse;
        }
    }
    else
    {
        //CCOV: amanevd: Cannot be covered because this else section rises explicit assert
        mLIBassert(cFalse);
    }
}
//=============================================================================
//  DESCRIPTION         : Send LDB Trp control for stopping Verlog Timer
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//=============================================================================
void DATVlgStopVerlogTimer(void)
{
    LDBControl(cLDBChannelTrp, cLDBTrpStopVerlog);
    TOSSeqDeactivateGraph(cTOSSeqGraphIdDATVlgOutputProtection);
    mDATWrite(U1Bit, DO_VERLOG, 0, Default);
}

//=============================================================================
//  DESCRIPTION         : Protection Task
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//=============================================================================
void DATVlgProtectionTask(void)
{
#ifdef X90_PROJECT
    DATVlgProtectionTask_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DATVlgProtectionTask_Static(void)
{
#endif

    if(     (cFalse != mDATRead(U1Bit, PWR_IGN, Default))
        &&  (cFalse == bPWR_IGNOld)
      )
    {
        mDATWrite(U1Bit, DO_VERLOGProtection, 0, Default);
        mDATWrite(U1Bit, DefVerlogToGnd, 0, Default);
        mDATWrite(U1Bit, DefVerlogToBat, 0, Default);
        u8FaultCounter  = 0;
    }

    if(     (cFalse != mDATRead(U1Bit, PWR_IGN, Immediate))
        &&  (cFalse == mDATRead(U1Bit, DO_VERLOGProtection, Default))
      )
    {
        LDBControl(cLDBChannelDou, cLDBControlCheckDO_VERLOGSCDetect);

        if(     (cFalse == bDO_VERLOGSCtoGnd) 
            &&  (cFalse == bDO_VERLOGSCtoBat)
          )
        {
            u8FaultCounter = 0;
            mDATWrite(U1Bit, DefVerlogToGnd, 0, Default);
            mDATWrite(U1Bit, DefVerlogToBat, 0, Default);
        }
    }

    bPWR_IGNOld = mDATRead(U1Bit, PWR_IGN, Default);
}
//=============================================================================
//  DESCRIPTION         : process StartPermanentAuthentication control
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//=============================================================================
void DATVlgStartAuthentPermKey(void)
{
    LIBVlg2PermanentAuthenticationEnabled(cTrue);
}

//=============================================================================
//  DESCRIPTION         : process StopPermanentAuthentication control
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//=============================================================================
void DATVlgExitFromAuthentPermKey(void)
{
    LIBVlg2PermanentAuthenticationEnabled(cFalse);
}

//=============================================================================
//  DESCRIPTION         : process Falling_PWR_IGN control
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//=============================================================================
void DATVlgFalling_PWR_IGN(void)
{
    LIBVlg2UpdateIgnition(cFalse);
    LIBVlg2ProcessData();
}
