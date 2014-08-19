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
// Component:    LAP_KWP
// -----------------------------------------------------------------------------
// $Log:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_KWP/LAP_KWP.C-arc  $
// 
//    Rev 1.11   Mar 25 2010 14:28:44   adzhelp
// Cm007976: Code review corrections - comment removed
// 
//    Rev 1.10   Oct 27 2009 15:33:14   adzhelp
// Cm006382: Removal of implementation of start reprogramming session
// 
//    Rev 1.9   Oct 13 2009 18:21:30   akodzhh
// Cm005756: Comments added - Component Test results updated.
// 
//    Rev 1.8   Sep 21 2009 15:42:32   akodzhh
// Cm005756: P2 and TIdle timeouts adjusted.
// 
//    Rev 1.7   Sep 17 2009 10:20:36   adzhelp
// Cm003277: Implementation of start reprogramming session - jump to bootloader
// 
//    Rev 1.6   Sep 15 2009 09:47:46   akodzhh
// Cm006204: SDS positive response length changed to be 1 byte.
// 
//    Rev 1.5   Sep 14 2009 15:33:48   akodzhh
// Cm006204: SDS positive response length changed to be 1 byte. CR 1.5 issues fixed.
// 
//    Rev 1.4   Apr 29 2009 14:20:16   adzhelp
// Cm003128: Functions moved to banked memory area
// 
//    Rev 1.3   Apr 27 2009 14:11:00   akodzhh
// Cm003128: LAP_KWP Component test and QAC.
// 
//    Rev 1.2   Apr 22 2009 15:27:10   akodzhh
// Cm003128: StartCom positive response is always send CLR#69. SDS response 2 bytes(not 1). SDS: do not exit current session if the same is requested.
// 
//    Rev 1.1   20 Mar 2009 18:09:48   akodzhh
// Cm003128 - last session restore after Read immo conf.
// 
//    Rev 1.0   Jan 14 2009 16:24:04   akodzhh
// Initial revision.
// 
//******************************************************************************
#endif


//--------------------------------------------------------------------------
//  Body Identification
//--------------------------------------------------------------------------
#define lap_kwp  "lap_kwp"

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------
#include "lib.h"
#include "dat.h"
#include "tos.h"
#include "lap_kwp.h"
#include "lap_kwpp.h"
#include "lap_kwp.hgr"

//------------------------------------------------------------------------------
// Local constants
//------------------------------------------------------------------------------
// Cm005756: increase accuracy for the timeouts measured through graph group default
#define cTidle                    (mTOSConvMsEnTickHorloge(300UL) - (tTOSTimer)1U)
#define cCommunicationTimeOut     (mTOSConvMsEnTickHorloge(5000UL))
// Cm005756: increase accuracy for the timeouts measured through graph group default
#define cP2TimeOut                (mTOSConvMsEnTickHorloge(240UL) - (tTOSTimer)1U)

#define cRequestField         0
// SIDPR: SID+$40
#define cPositiveRespAdd     (U8)0x40

// lgth of frame
#define cTesterPresentRequestLgth    (U8)0x01
#define cStartSessionRequestLgth     (U8)0x02

#define cStartComRequestLgth         (U8)0x01
#define cStopComRequestLgth          (U8)0x01

#define cStartComRespLgth   (U8)3
#define cStartComPR     (U8)0xC1
#define cStartComKB1    (U8)0xD0
#define cStartComKB2    (U8)0x8F
#define cKB1Offset  1
#define cKB2Offset  2

// negative response
#define cNRSIDOffset 1
#define cNRCOffset   2

#define cDefaultSessionID      cLAPAfsIdAFSSession

//------------------------------------------------------------------------------
// Local macros
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Local types
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Local data
//------------------------------------------------------------------------------
static tTOSTempo  CommunicationTimeOut;
static tTOSTempo  TimerP2;

static U8     u8IndexRequestedService;
static BOOL   bComIsStopped;
static BOOL   bStartComIsValid;

static const tLAPKwpParamOfSession*   pActiveSession;
static U8     u8LastSessionID;
static BOOL   bHaveToRestoreLastSession;
static BOOL   bNoAnswer;
//------------------------------------------------------------------------------
// Constant local data
//------------------------------------------------------------------------------
static const tLAPKwpParamOfSession TabSession[cLAPKwpNbrOfSessionSupported] = 
                                                          LAPKwpInitSessiontables();

//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------
U8  u8LAPKwpRequestStatus;

//------------------------------------------------------------------------------
// Constant exported data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Local function prototypes
//------------------------------------------------------------------------------
static MEM_TYPE BOOL  ServiceKnownByECUSession(const U8 u8ServiceIDP);
static MEM_TYPE void  TreatStartDiagnosticSession(void);
static MEM_TYPE void  TreatStopCommunication(void);
static MEM_TYPE void  TreatTesterPresentService(void);
static MEM_TYPE void  RestoreLastSession(void);
static MEM_TYPE void  TreatStartCommunication(void);

#ifdef X90_PROJECT
static MEM_TYPE void LAPKwpAnalyseRequest_Static(void);
static MEM_TYPE void LAPKwpStartCom_Static(void);
static MEM_TYPE void LAPKwpTreatStopCom_Static(void);
static MEM_TYPE void LAPKwpSendResponse_Static(void);
static MEM_TYPE void LAPKwpExecuteCurrentSessionService_Static(void);
static MEM_TYPE void LAPKwpInitialize_Static(void);
#endif


//==============================================================================
//=========================== LOCAL FUNCTIONS ==================================
//==============================================================================

//==============================================================================
// DESCRIPTION:         ServiceKnownByECUSession
//
// PARAMETERS:          U8
//
// RETURN VALUE:        BOOL
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
static MEM_TYPE BOOL ServiceKnownByECUSession(const U8 u8ServiceIDP)
{
    BOOL bResultL;
    U8   u8IndexL;

    bResultL = cFalse;
    if(pActiveSession != NULL)
    {
        for (u8IndexL=0 ; (u8IndexL<pActiveSession->NbOfSupportedService) ; u8IndexL++)
        {
            if (u8ServiceIDP ==  (pActiveSession->pTabIdentifierOfSupportedService)[u8IndexL])
            {
                bResultL = cTrue;
                u8IndexRequestedService = u8IndexL;
            }
        }
    }
    else
    {
        mLIBassert(cFalse); //CCOV: akodzhh: can't be tested because of assert
    } 
    
    return(bResultL);
}

//==============================================================================
// DESCRIPTION:         TreatStartDiagnosticSession
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
static MEM_TYPE void TreatStartDiagnosticSession(void)
{
    U8    u8IndexL;
    BOOL  bInvalidRequestL;

    bInvalidRequestL = cTrue;
    if (mDATRead(U8Bit,DATKwpRxFrameLgth,Default)== cStartSessionRequestLgth)
    {
        for (u8IndexL=0; (u8IndexL<cLAPKwpNbrOfSessionSupported)&&(bInvalidRequestL == cTrue); u8IndexL++)
        {
            if (TabSession[u8IndexL].SessionIdentifier == mDATReadTable(U8Bit,DATKwpRxBuffer,cRequestField+1,Default))
            {
                mLIBassert(pActiveSession != NULL);
                //QACJ 0506: akodzhh: pointer value is correct
                u8LastSessionID = pActiveSession->SessionIdentifier;
                
                // if session requested is not activated already
                if( TabSession[u8IndexL].SessionIdentifier != u8LastSessionID ) // prsFS_DIAG-674
                {
                    bHaveToRestoreLastSession = cFalse;
                    //close Active Session 
                    //QACJ 0506: akodzhh: pointer value is correct 
                    (*pActiveSession->CloseActiveSession)();    // prsFS_DIAG-673
                
                    // start new Session
                    (*TabSession[u8IndexL].OpenActiveSession)();
                    pActiveSession = &TabSession[u8IndexL];
                }
                
                bInvalidRequestL = cFalse;
            }
        }
    }

    if(bInvalidRequestL != cFalse)
    {
        LAPKwpPrepareNegativeResponse(cLAPKwpInvalidFormat);
    }
    else
    {   // Cm006204: SDS positive response length to be 1 byte.
        LAPKwpPreparePositiveResponse(1);
    }
}
//==============================================================================
// DESCRIPTION:         TreatStopCommunication
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
static MEM_TYPE void TreatStopCommunication(void)
{
  
    if (mDATRead(U8Bit,DATKwpRxFrameLgth,Default)== cStopComRequestLgth)
    {
        LAPKwpPreparePositiveResponse(1);
        bComIsStopped = cTrue;
    }
    else
    {
        LAPKwpPrepareNegativeResponse(cLAPKwpInvalidFormat);
    }
}

//==============================================================================
// DESCRIPTION:         TreatTesterPresentService
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
static MEM_TYPE void TreatTesterPresentService(void)
{
    if( (mDATRead(U8Bit,DATKwpRxFrameLgth,Default)== cTesterPresentRequestLgth))
    {
        LAPKwpPreparePositiveResponse(1);
    }
    else
    {
        LAPKwpPrepareNegativeResponse(cLAPKwpInvalidFormat);
    }
}

//==============================================================================
// DESCRIPTION:         RestoreLastSession
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
static MEM_TYPE void RestoreLastSession(void)
{
    U8 u8IndexL;

    //CCOV: akodzhh: can't be tested, because of global LAP_KWP Component Test desing.    
    if(  (u8LastSessionID == cLAPAfsIdDvpCustomerSession)
       ||(u8LastSessionID == cLAPDvpIdDVPSession))
    {
        u8LastSessionID = cDefaultSessionID; 
    }

    //CCOV: akodzhh: Defensive check, can't be covered, u8IndexL is always less then cLAPKwpNbrOfSessionSupported. 
    for (u8IndexL=0; bHaveToRestoreLastSession && (u8IndexL < cLAPKwpNbrOfSessionSupported); u8IndexL++)
    {
        //CCOV: akodzhh: can't be tested, because of global LAP_KWP Component Test desing.
        if (TabSession[u8IndexL].SessionIdentifier == u8LastSessionID)
        {
            //close Active Session
            //QACJ 0506: akodzhh: pointer value is correct 
            (*pActiveSession->CloseActiveSession)();
            
            // start last session
            (*TabSession[u8IndexL].OpenActiveSession)();
            pActiveSession = &TabSession[u8IndexL];

            bHaveToRestoreLastSession = cFalse;
        }
    }

}

//==============================================================================
// DESCRIPTION:         TreatStartCommunication
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
static MEM_TYPE void  TreatStartCommunication(void)
{
    if(mDATRead(U8Bit,DATKwpRxFrameLgth,Default)==cStartComRequestLgth)
    {
        mDATWriteTable(U8Bit,DATKwpTxBuffer,cRequestField,           cStartComPR, Default);
        mDATWriteTable(U8Bit,DATKwpTxBuffer,cRequestField+cKB1Offset,cStartComKB1,Default);
        mDATWriteTable(U8Bit,DATKwpTxBuffer,cRequestField+cKB2Offset,cStartComKB2,Default);
        mDATWrite(U8Bit, DATKwpTxFrameLgth,cStartComRespLgth,Default);
    }
    else
    {
        bNoAnswer = cTrue;
    }
}

//==============================================================================
//=========================== EXPORTED FUNCTIONS ===============================
//==============================================================================
//==============================================================================
// DESCRIPTION:         LAPKwpAnalyseRequest
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
void LAPKwpAnalyseRequest(void)
{
#ifdef X90_PROJECT
    LAPKwpAnalyseRequest_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPKwpAnalyseRequest_Static(void)
{
#endif
    U8   u8RequestedServiceL;
    BOOL bServiceKnownByECUSession;
  
    // reset of the time out communication
    TOSStartTempo(&CommunicationTimeOut);
    if( (mDATRead(U8Bit,TargetID,Default)== cDATKwpECUId) 
      ||(mDATRead(U8Bit,TargetID,Default)== cDATKwpBroadcastID))
    {
        TOSStartTempo(&TimerP2);

        u8RequestedServiceL = mDATReadTable(U8Bit,DATKwpRxBuffer,cRequestField,Default);

        if ( u8RequestedServiceL == cLAPKwpIdStartCommunication)
        {
            // CLR #96 - send response
            // Communication is started, prepare response only  
            TreatStartCommunication();
        }
        else if ( u8RequestedServiceL == cLAPKwpIdStartDiagnosticSession)
        {
            TreatStartDiagnosticSession();
        }
        else if ( u8RequestedServiceL == cLAPKwpIdStopCommunication)
        {
            TreatStopCommunication();
        }
        else if ( u8RequestedServiceL == cLAPKwpIdTesterPresent)
        {
            TreatTesterPresentService();
        }
        else 
        {
            bServiceKnownByECUSession = ServiceKnownByECUSession(u8RequestedServiceL);
            if ( bServiceKnownByECUSession != cFalse)
            {
                if ( (mDATRead(U8Bit,TargetID,Default)!= cDATKwpBroadcastID)
                   ||(u8RequestedServiceL == cLAPKwpIdClearDiagnosticInformation))
                {
                    u8LAPKwpRequestStatus = cLAPKwpNewServiceIsRequested;
                }
            }
            else
            {
                // the service is unknown
                LAPKwpPrepareNegativeResponse(cLAPKwpServiceNotSupported);
            }
        }
    }
}
//==============================================================================
// DESCRIPTION:         LAPKwpExecuteCurrentSessionService
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
void LAPKwpExecuteCurrentSessionService(void)
{
#ifdef X90_PROJECT
    LAPKwpExecuteCurrentSessionService_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPKwpExecuteCurrentSessionService_Static(void)
{
#endif

    if(LAPKwpIsServiceFinished() == cFalse) 
    {
        //QACJ 0506: akodzhh: pointer value is correct
        (*(pActiveSession->pTabFunctionOfSupportedService[u8IndexRequestedService]))();
    }
}
//==============================================================================
// DESCRIPTION:         LAPKwpNewRequestIsReceived
//
// PARAMETERS:          none
//
// RETURN VALUE:        BOOL
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
BOOL LAPKwpNewRequestIsReceived(void)
{
    return TOSReadSignal(cTOSSignalDiagnosticMessageIsReceived);
}
//==============================================================================
// DESCRIPTION:         LAPKwpSendResponse
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
void LAPKwpSendResponse(void)
{
#ifdef X90_PROJECT
    LAPKwpSendResponse_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPKwpSendResponse_Static(void)
{
#endif
    BOOL bTempoElapsedL;

    bTempoElapsedL = TOSIsTempoElapsed(&TimerP2, cP2TimeOut);
    if( (bTempoElapsedL == cFalse) && 
        (mDATRead(U8Bit,TargetID,Default) == cDATKwpECUId)&& 
        (bNoAnswer != cTrue))
    {
        mDATControl(Kwp,SendFrame);
        if(bHaveToRestoreLastSession == cTrue) // confidential service finished
        {
            RestoreLastSession();
        }
    }
    else
    {
        mDATControl(Kwp,NoAnswer);
        bNoAnswer = cFalse; // clear flag
    }
    TOSStopTempo(&TimerP2);
}
//==============================================================================
// DESCRIPTION:         LAPKwpServiceIsFinishedOrTimeOutP2IsFinished
//
// PARAMETERS:          none
//
// RETURN VALUE:        BOOL
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
BOOL LAPKwpServiceIsFinishedOrTimeOutP2IsFinished(void)
{
    BOOL bTempoElapsedL;

    bTempoElapsedL = TOSIsTempoElapsed(&TimerP2, cP2TimeOut);
    return ((bTempoElapsedL) || (LAPKwpIsServiceFinished()));
}
//==============================================================================
// DESCRIPTION:         LAPKwpComTimeOutIsElapsedOrStopComReceived
//
// PARAMETERS:          none
//
// RETURN VALUE:        BOOL
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
BOOL LAPKwpComTimeOutIsElapsedOrStopComReceived(void)
{
    BOOL bTempoElapsedL;

    bTempoElapsedL = TOSIsTempoElapsed(&CommunicationTimeOut, cCommunicationTimeOut);
    return ((bTempoElapsedL) || (bComIsStopped != cFalse));
}
//==============================================================================
// DESCRIPTION:         LAPKwpIsWakeUpReceived
//
// PARAMETERS:          none
//
// RETURN VALUE:        BOOL
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
BOOL LAPKwpIsWakeUpReceived(void)
{
    return (TOSReadSignal(cTOSSignalEventIntKwpWakeUp));
}
//==============================================================================
// DESCRIPTION:         LAPKwpStartCom
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
void LAPKwpStartCom(void)
{
#ifdef X90_PROJECT
    LAPKwpStartCom_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPKwpStartCom_Static(void)
{
#endif
    TOSStopTempo(&CommunicationTimeOut);

    if( (mDATReadTable(U8Bit,DATKwpRxBuffer,cRequestField,Default)==cLAPKwpIdStartCommunication) &&
        (mDATRead(U8Bit,DATKwpRxFrameLgth,Default)==cStartComRequestLgth) &&
        (mDATRead(U8Bit,TargetID,Default) == cDATKwpECUId))
    {
        bStartComIsValid = cTrue;

        // Init local variable
        LAPKwpSetServiceIsFinished();

        // After a SartCom, the active session is the defaut session
        pActiveSession = &TabSession[0];
        //QACJ 0506: akodzhh: pointer value is correct
        (*pActiveSession->OpenActiveSession)();
        bComIsStopped = cFalse;

        // Send StartCom response
        mDATWriteTable(U8Bit,DATKwpTxBuffer,cRequestField,           cStartComPR, Default);
        mDATWriteTable(U8Bit,DATKwpTxBuffer,cRequestField+cKB1Offset,cStartComKB1,Default);
        mDATWriteTable(U8Bit,DATKwpTxBuffer,cRequestField+cKB2Offset,cStartComKB2,Default);
        mDATWrite(U8Bit, DATKwpTxFrameLgth,cStartComRespLgth,Default);
        mDATControl(Kwp,SendFrame);

        // Activate graph
        TOSSeqActiverGraphe(cTOSSeqKWPTreatRequest);

        // start com time out
        TOSStartTempo(&CommunicationTimeOut);
    }

}
//==============================================================================
// DESCRIPTION:         LAPKwpStartTimeOutInit
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
void LAPKwpStartTimeOutInit(void)
{
    TOSStartTempo(&CommunicationTimeOut);
}
//==============================================================================
// DESCRIPTION:         LAPKwpTimeOutInitElapsed
//
// PARAMETERS:          none
//
// RETURN VALUE:        BOOL
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
BOOL LAPKwpTimeOutInitElapsed(void)
{
    return TOSIsTempoElapsed(&CommunicationTimeOut, cTidle);
}
//==============================================================================
// DESCRIPTION:         LAPKwpTreatStopCom
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
void LAPKwpTreatStopCom(void)
{
#ifdef X90_PROJECT
    LAPKwpTreatStopCom_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPKwpTreatStopCom_Static(void)
{
#endif
    if( bStartComIsValid == cTrue)
    {
        TOSStopTempo(&CommunicationTimeOut);

        //close Active Session
        //QACJ 0506: akodzhh: pointer value is correct
        (*pActiveSession->CloseActiveSession)();

        // deactivate graph
        TOSSeqDesactiverGraphe(cTOSSeqKWPTreatRequest);

        if(bComIsStopped != cFalse)
        {
            if(mDATRead(U8Bit,TargetID,Default)!= cDATKwpBroadcastID)
            {
                // Send the stopcom response
                mDATControl(Kwp,SendFrame);
            }
            else
            {
                // Return in reception mode
                mDATControl(Kwp,NoAnswer);
            }
        }
        else // Communication time out
        {
            // communication timeout : no request actualy in treatment
            mLIBassert(LAPKwpIsServiceFinished() != cFalse);
            bComIsStopped = cTrue;
        }
        bStartComIsValid = cFalse;

    }
    else
    {
        //Bad StartCom
        mDATControl(Kwp,NoAnswer);
    }

    // Authorize KWP WakeUp
    mDATControl(Kwp,WaitForWakeUp);

}
//==============================================================================
// DESCRIPTION:         LAPKwpPrepareNegativeResponse
//
// PARAMETERS:          U8
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
void LAPKwpPrepareNegativeResponse(const U8  u8NRCodeP)
{
    U8 u8TempByteL;

    u8TempByteL = mDATReadTable(U8Bit,DATKwpRxBuffer,cRequestField, Default);
    mDATWriteTable(U8Bit,DATKwpTxBuffer,0,cLAPKwpIdNegativeResponse,Default);
    mDATWriteTable(U8Bit,DATKwpTxBuffer,cNRSIDOffset,u8TempByteL,Default);
    mDATWriteTable(U8Bit,DATKwpTxBuffer,cNRCOffset,  u8NRCodeP,  Default);
    mDATWrite(U8Bit, DATKwpTxFrameLgth,cLAPKwpNRLength,Default);

}
//==============================================================================
// DESCRIPTION:         LAPKwpPreparePositiveResponse
//
// PARAMETERS:          U8
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
void LAPKwpPreparePositiveResponse(const U8  u8LengthP)
{
    U8 u8TempByteL;
    u8TempByteL = mDATReadTable(U8Bit,DATKwpRxBuffer,cRequestField, Default);
    mDATWriteTable(U8Bit,DATKwpTxBuffer,cRequestField,(u8TempByteL+cPositiveRespAdd),Default);
    mDATWrite(U8Bit, DATKwpTxFrameLgth,u8LengthP,Default);
}
//==============================================================================
// DESCRIPTION:         LAPKwpReturnInWakeUpDetection
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
void LAPKwpReturnInWakeUpDetection(void)
{
    mDATControl(Kwp,WaitForWakeUp);
}
//==============================================================================
// DESCRIPTION:         LAPKwpInitialize
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
void LAPKwpInitialize(void)
{
#ifdef X90_PROJECT
    LAPKwpInitialize_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPKwpInitialize_Static(void)
{
#endif

    TOSSeqActiverGraphe(cTOSSeqKWPTreatCommunication);
    bComIsStopped = cTrue;
    bStartComIsValid = cFalse;
    bNoAnswer = cFalse; 
}

//==============================================================================
// DESCRIPTION:         LAPKwpGetActiveSessionID
//
// PARAMETERS:          none
//
// RETURN VALUE:        U8
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
U8 LAPKwpGetActiveSessionID(void)
{
    U8 u8SessionIdentifierL;

    if(pActiveSession != NULL)
    {
        u8SessionIdentifierL = pActiveSession->SessionIdentifier;
    }
    else    //CCOV: akodzhh: for QAC - can't be tested
    {
        mLIBassert(cFalse);
        u8SessionIdentifierL = cDefaultSessionID;
    }
    return u8SessionIdentifierL;
    
}

//==============================================================================
// DESCRIPTION:         LAPKwpRerstoreLastSession
//
// PARAMETERS:          none
//
// RETURN VALUE:        U8
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
void LAPKwpRerstoreLastSession(void)
{
    bHaveToRestoreLastSession = cTrue;
}
