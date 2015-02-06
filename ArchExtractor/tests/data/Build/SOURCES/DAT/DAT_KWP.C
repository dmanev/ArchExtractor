#ifndef _QAC_
//******************************************************************************
// Company:      Johnson Controls Inc.
// -----------------------------------------------------------------------------
// Copyright:    This software is JCI property.
//               Duplication or disclosure without JCI written authorization
//               is prohibited.
// -----------------------------------------------------------------------------
// Project:      X90_BCM
// Language:     C
// -----------------------------------------------------------------------------
// Component:    DAT_KWP
// -----------------------------------------------------------------------------
// $Log:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_KWP/DAT_KWP.C-arc  $
// 
//    Rev 1.6   Jan 21 2010 11:43:30   adzhelp
// Cm007210: HWP: Change the KLine inhibition duration to 5 s
// 
//    Rev 1.5   Dec 14 2009 12:14:46   adzhelp
// Cm005566: QAC changes
// 
//    Rev 1.4   Dec 14 2009 11:31:18   adzhelp
// Cm005566: SC detection of KLine
// 
//    Rev 1.3   May 26 2009 11:42:52   akodzhh
// Cm003128: Add //CCOV ... justification.
// 
//    Rev 1.2   Apr 29 2009 12:06:14   adzhelp
// Cm003128: Functions moved to banked memory area
// 
//    Rev 1.1   Mar 20 2009 09:45:58   adzhelp
// Cm003128: Old type tU16Bit corrected to U16
// 
//    Rev 1.0   Jan 12 2009 11:31:08   akodzhh
// Initial revision.
//
//******************************************************************************
#endif

//--------------------------------------------------------------------------
//  Body Identification
//--------------------------------------------------------------------------
#define dat_kwp   "dat_kwp"

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------
#include "lib.h"
#include "tos.h"
#include "dat.h"
#include "dat_kwp.h"


//------------------------------------------------------------------------------
// Local constants
//------------------------------------------------------------------------------
#define cStopMode         (tKwpMode)0x00
#define cRxMode           (tKwpMode)0x01
#define cTxMode           (tKwpMode)0x02
#define cWakeUpMode       (tKwpMode)0x03

#define cKwpHeaderLgh     (U8)3
#define cKwpCksLgh        (U8)1
#define cKwpLghByte0x80   (U8)0x80

// HW Protection
#define cRestoreTimeMs    5000UL

//------------------------------------------------------------------------------
// Local macros
//------------------------------------------------------------------------------
#define mGetRxStartField        DATKwpRxBuffer[0]
#define mGetRxTargetId          DATKwpRxBuffer[1]
#define mGetRxSourceId          DATKwpRxBuffer[2]
#define mGetRxByte(Index)       DATKwpRxBuffer[Index]

#define mSetTxStartField(Value) (DATKwpTxBuffer[0]     = (Value)) 
#define mSetTxTargetId(Value)   (DATKwpTxBuffer[1]     = (Value))
#define mSetTxSourceId(Value)   (DATKwpTxBuffer[2]     = (Value))
#define mSetTxByte(Index,Value) (DATKwpTxBuffer[Index] = (Value))
//------------------------------------------------------------------------------
// Local types
//------------------------------------------------------------------------------
typedef U8 tKwpMode;

//------------------------------------------------------------------------------
// Local data
//------------------------------------------------------------------------------
static tKwpMode   KwpMode;
static BOOL       bDATKwpWakeUpIsRequested;

//------------------------------------------------------------------------------
// Constant local data
//------------------------------------------------------------------------------
// HW Protection
static tTOSTimer KLineFaultTimer;

//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------
U8    DATKwpRxBuffer[cDATKwpRxBufferSize];
U8    DATKwpTxBuffer[cDATKwpTxBufferSize];

tMsg  DATKwpTxMsg;
U8    DATKwpRxFrameLgth;

//------------------------------------------------------------------------------
// Constant exported data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Local function prototypes
//------------------------------------------------------------------------------
static U8 CalcChecksum(const U8* const pu8FrameP, const U8 u8LengthP);

#ifdef X90_PROJECT
static MEM_TYPE void DATKwpTaskControl_Static(void);
#endif

//==============================================================================
//=========================== LOCAL FUNCTIONS ==================================
//==============================================================================

//============================================================================
// DESCRIPTION:         CalcChecksum
//                This function calculate the checksum of the KWP frame
//  
// PARAMETERS:          
//          pFrame    : pointer to the beginning of the frame
//          Length    : length in byte of the frame
//
// RETURN VALUE:         checksum value
// 
// DESIGN INFORMATION:   refer to Detailed Design Document
//==========================================================================
static U8 CalcChecksum(const U8* const pu8FrameP, const U8 u8LengthP)
{
    U8 u8CksumL;
    U8 u8IndexL;

    u8CksumL = 0;

    //CCOV: akodzhh: can't be tested because of assert
    if( pu8FrameP != NULL )
    {
        mLIBassert(u8LengthP !=0 );
        for(u8IndexL=0;u8IndexL<(u8LengthP-1);u8IndexL++)
        {
            u8CksumL += pu8FrameP[u8IndexL];
        }
    }
    else
    {
        mLIBassert(cFalse);    // akodzhh: can't be tested
    }

    return(u8CksumL);
   
}

//==============================================================================
//=========================== EXPORTED FUNCTIONS ===============================
//==============================================================================

//============================================================================
// DESCRIPTION:         DATKwpInit
//        This function initialize DAT_KWP
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
// 
// DESIGN INFORMATION:  refer to Detailed Design Document
//============================================================================
void DATKwpInit(void)
{
    KwpMode                 = cStopMode;
    bDATKwpWakeUpIsRequested = cFalse;
    mSetTxTargetId(cDATKwpDiagToolsId);
    mSetTxSourceId(cDATKwpECUId);
}

//============================================================================
// DESCRIPTION:         DATKwpLeaveStartingStepState
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
// 
// DESIGN INFORMATION:  refer to Detailed Design Document
//============================================================================
void DATKwpLeaveStartingStepState(void)
{
    mLIBassert(KwpMode == cStopMode);
    KwpMode = cWakeUpMode;
    LDBControl(cLDBChannelKwp,cLDBKwpWaitForWakeUp);
}

//===========================================================================
// DESCRIPTION:         DATKwpReturnInRxMode
//        This function initialize the module in Rxmode after a bad frame received
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
// 
// DESIGN INFORMATION:  refer to Detailed Design Document
//============================================================================
void DATKwpReturnInRxMode(void)
{
    mLIBassert(KwpMode == cTxMode);
    if(bDATKwpWakeUpIsRequested == cFalse)
    {
        KwpMode = cRxMode;
        LDBControl(cLDBChannelKwp,cLDBKwpEnableRx);
    }
    else
    {
        KwpMode = cWakeUpMode;
        LDBControl(cLDBChannelKwp,cLDBKwpWaitForWakeUp);
        bDATKwpWakeUpIsRequested = cFalse;
    }

}

//============================================================================
// DESCRIPTION:         DATKwpCallBackRxSpontWithoutAddr
//        This function copy the frame in DATKwpRxFrameBuffer and activate
//        the task for the check of the frame
//
//        WARNING : this function is called under Interrupt         
//
// PARAMETERS:          
//        tStatus Statut  : Always cLDBCorrect
//        tMsg *pMsg      : contain the pointer to the received frame and its length
//
// RETURN VALUE:        none
// 
// DESIGN INFORMATION:  refer to Detailed Design Document
//============================================================================
//QACJ  3206: akodzhh: Standard JCI dat layer interface 
//QACJ  3227: akodzhh: Standard JCI dat layer interface - 'const' for 'pMsg' 
//QACJ  3673: akodzhh: Standard JCI dat layer interface - 'const' for the object pointed by 'pMsg'
void DATKwpCallBackRxSpontWithoutAddr(tStatus Statut,tMsg* pMsg)
{

    // Status is always correct because there aren't controls on the frame in LDB_KWP
    mLIBassert(Statut==cLDBCorrect);

    // the component must be in receive mode
    mLIBassert(KwpMode == cRxMode);

    //CCOV: akodzhh: can't be tested because of assert
    if( (pMsg != NULL) && (pMsg->pBuffer != NULL) )
    {
        // verify the length of the message
        mLIBassert(pMsg->Lng <= cDATKwpRxBufferSize);

        // Disable the reception
        LDBControl(cLDBChannelKwp,cLDBKwpDisableRx);

        DATKwpRxFrameLgth = (U8)pMsg->Lng;
    
        // copy KWP frame
        mLIBmemcpy(DATKwpRxBuffer,pMsg->pBuffer,pMsg->Lng);

        // active KWPManage task
        TOSActivateTask(cTOSTaskID_ControlKwp);
    }
    else
    {
        mLIBassert(cFalse);
    }
    
}
//============================================================================
// DESCRIPTION:         DATKwpCallBackTxWithoutAddr
//        This function inform the dat layer that the transmit is done
//
//        WARNING : this function is called under Interrupt         
//
// PARAMETERS:          
//        tStatus Statut : always cLDBCorrect
//
// RETURN VALUE:        none
// 
// DESIGN INFORMATION:  refer to Detailed Design Document
//============================================================================
//QACJ 3227: akodzhh: Standard JCI dat layer interface
void DATKwpCallBackTxWithoutAddr(tStatus Status)
{
    if (Status == cLDBCorrect)
    {
        DATKwpReturnInRxMode();
    }
    else if (Status == cLDBError)
    {
        mDATWrite(U1Bit, DefKLineCC, cTrue, Default);
        mDATWrite(U1Bit, EEP_DefKLineCC, cTrue, Default);
        //TODO: increment counter in EEP
        TOSStartTimer(&KLineFaultTimer);
        // do not return to Rx mode
    }
    else
    {
        mLIBassert(cFalse);
    }
}
//===========================================================================
//  DESCRIPTION : DATKwpTaskControl
//        Task for the managment of the frame
//      - in Rx mode      : this function control the validity of the KWP frame. if the frame is
//                        valid a signal is activate else the LDB layer return in Rx mode
//      - in Tx mode      : This function complete the header and the checksum of the frame and
//                        send it
//      - in WakeUp mode  : The signal EventIntKwpWakeUp and the control cTOSControlWakeUpRequest
//                        are activated
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
// 
// DESIGN INFORMATION:  refer to Detailed Design Document
//============================================================================
void DATKwpTaskControl(void)
{
#ifdef X90_PROJECT
    DATKwpTaskControl_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DATKwpTaskControl_Static(void)
{
#endif

    switch(KwpMode)
    {
    case cRxMode:
        //QACJ 3415: akodzhh: Cause CalcChecksum : the length must be tested before calculate the checksum
        //QACJ 3416: akodzhh: Cause CalcChecksum : the length must be tested before calculate the checksum
        if((mGetRxStartField == (U8)(cKwpLghByte0x80 + (DATKwpRxFrameLgth - cKwpHeaderLgh - cKwpCksLgh)))
            && (DATKwpRxFrameLgth > (cKwpHeaderLgh + cKwpCksLgh))
            && ( mGetRxSourceId == cDATKwpDiagToolsId)
            && ( CalcChecksum(DATKwpRxBuffer,DATKwpRxFrameLgth) == mGetRxByte(DATKwpRxFrameLgth-1)))
        {
            // calculate the data length
            DATKwpRxFrameLgth = (U8)(DATKwpRxFrameLgth - cKwpHeaderLgh) - cKwpCksLgh;
            // Inform LAP layer of the reception of new request
            TOSWriteSignal(cTOSSignalDiagnosticMessageIsReceived);
            KwpMode = cTxMode;
        }
        else
        {
            // Return in receive mode
            LDBControl(cLDBChannelKwp,cLDBKwpEnableRx);
        }
        break;

    case cTxMode:
        mLIBassert(DATKwpTxMsg.Lng<=(cDATKwpTxBufferSize - cKwpHeaderLgh - cKwpCksLgh));
        // complete the frame
        mSetTxStartField(cKwpLghByte0x80  | (U8)DATKwpTxMsg.Lng);
        DATKwpTxMsg.Lng = DATKwpTxMsg.Lng + (U16)(cKwpHeaderLgh + cKwpCksLgh);
        mSetTxByte(DATKwpTxMsg.Lng-1,CalcChecksum(DATKwpTxBuffer,(U8)DATKwpTxMsg.Lng));
        DATKwpTxMsg.pBuffer = DATKwpTxBuffer;
        // send the frame
        LDBSendWithoutAddr(cLDBChannelKwp,&DATKwpTxMsg);
        break;
    case cWakeUpMode :
        // Wakeup must be always sent (In sleep and WakeUp mode)
        // It allow to re-start a minimum activation time
        TOSSendControl(cTOSControlWakeUpRequest);
        TOSWriteSignal(cTOSSignalEventIntKwpWakeUp);
        // LDBKwp component is already in Rx mode because this mode is required to detect WakeUp.
        // Low state = 25 ms, High State = 25 ms, next message.
        KwpMode = cRxMode;
        break;
    //CCOV: akodzhh: can't be tested because of assert
    default:
        mLIBassert(cFalse);
        break;
    }

}
//============================================================================
// DESCRIPTION:         DATKwpCallBackCtrl
//        This function inform the dat layer that a Wake up is request
//        by the Kwp channel
//
//        WARNING : this function is called under Interrupt         
//
// PARAMETERS:          tCtrl Ctrl : cLDBKwpWakeUp
//
// RETURN VALUE:        none
// 
// DESIGN INFORMATION:  refer to Detailed Design Document
//============================================================================
//QACJ 3206: akodzhh: The parameter 'Ctrl' is used in an assertion
void DATKwpCallBackCtrl(tCtrl Ctrl)
{
    mLIBassert(Ctrl == cLDBKwpWakeUp);
    mLIBassert(KwpMode == cWakeUpMode);
  
    // active KWPManage task
    TOSActivateTask(cTOSTaskID_ControlKwp);
}

//============================================================================
// DESCRIPTION:         DATKwpCallBackEndCtrl
//                this function is just declare for E_CAR but isn't used
//
// PARAMETERS:          
//        tCtrl Ctrl      : cLDBKwpEnableRx,cLDBKwpDisableRx or cLDBKwpWaitForWakeUp
//        tStatus Statut  : Always cLDBCorrect
//
//
// RETURN VALUE:        none
// 
// DESIGN INFORMATION:  refer to Detailed Design Document
//============================================================================
//QACJ 3206: akodzhh: The parameter 'Ctrl' is used in an assertion
//QACJ 3206: akodzhh: The parameter 'Status' is used in an assertion
void DATKwpCallBackEndCtrl(tCtrl Ctrl, tStatus Status)
{
    mLIBassert(  (Ctrl == cLDBKwpEnableRx)
               ||(Ctrl == cLDBKwpDisableRx)
               ||(Ctrl == cLDBKwpWaitForWakeUp));
    mLIBassert(Status == cLDBCorrect);
}
//============================================================================
// DESCRIPTION:         DATKwpActivateWakeUpDetection
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
// 
// DESIGN INFORMATION:  refer to Detailed Design Document
//============================================================================
void DATKwpActivateWakeUpDetection(void)
{
    if (KwpMode != cRxMode)
    {
        bDATKwpWakeUpIsRequested = cTrue;
    }
    else
    {
        KwpMode = cWakeUpMode;
        LDBControl(cLDBChannelKwp,cLDBKwpDisableRx);
        LDBControl(cLDBChannelKwp,cLDBKwpWaitForWakeUp);
    }
}

//============================================================================
//  DESCRIPTION         : DATKwpIsMaintainActiveState
//
//  PARAMETERS          : None
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//============================================================================
void DATKwpIsMaintainActiveState(void)
{
    if (KwpMode != cWakeUpMode)
    {
        TOSWriteSignal(cTOSSignalSomebodyMaintainActiveState);
    }
    // HW Protection: timer refresh
    //QACJ 3415: adzhelp: Standard TOS function used
    //QACJ 3416: adzhelp: Standard TOS function used
    if ((TOSIsTimerStarted(&KLineFaultTimer) != cFalse) &&
        (TOSIsTimerElapsed(&KLineFaultTimer, mTOSConvMsInTimerTick(cRestoreTimeMs)) != cFalse)
       )        
    {
        TOSStopTimer(&KLineFaultTimer);
        mDATWrite(U1Bit, DefKLineCC, cFalse, Default);
        DATKwpReturnInRxMode();
    }
}
