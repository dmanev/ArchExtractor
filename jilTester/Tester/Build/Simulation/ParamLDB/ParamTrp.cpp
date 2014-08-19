/*============================================================================
  Component ....................... paramtrp
  File revision ................... $Revision:   1.1  $
  Last modification date .......... $Modtime:   Jul 02 2009 18:18:42  $
  Generation date ................. 25/02/2003
  Author Name ..................... XX
  File Name ....................... ParamTrp.cpp

  -------------------------------------------------------------------------
  Copyright ... This software is JCAE property. Duplication or
                disclosure is prohibited without JCAE written permission
  -------------------------------------------------------------------------

  - This file should only contain data useful to the programmer to use
    this Component
  - Component exported macros, constants and types are defined in this file
  - Component exported variables and functions are declared in this file
    with the extern keyword

  ==========================================================================*/
//***************************************************************************
#define ParamTrp "ParamTrp"

//--------------------------------------------------------------------------
//---------------- Inclusion de fichiers (système et librairies -----------
//--------------------------------------------------------------------------

#include "Ldbpc.h" // defini les types et constantes de bases
#include "Ldbpcpar.h"
#include "LdbParam.h"
#include "string.h"

#ifdef cLDBChannelTrp

#define cMaxFrameLength   ((tU8Bit) 64)

#define cCtrlLengthInBit     ((tU8Bit) 8)
#define cStatusLengthInBit   ((tU8Bit) 8)
#define cAddrLengthInBit     ((tU8Bit) 16)
#define cMessageLengthInBit  ((tU8Bit) 64)
#define cLengthInBitOfMessageLength ((tU8Bit) 7)

static const tU8Bit cMessageInit[cMaxFrameLength] = {0, 0, 0, 0, 0, 0, 0, 0};

static  tMsg   ReceptionMsg;
static  tMsg   EmissionMsg;
static  tU8Bit BufferEmission[cMaxFrameLength];
static  tU8Bit BufferReception[cMaxFrameLength];
static tU32Bit  DataReceived;

static tS32Bit   TrpSendRef;
static tS32Bit   TrpReceiveRef;
static tS32Bit   TrpControlReceveidRef;
static tS32Bit   TrpAddressSentRef;
static tS32Bit   TrpAddressReceivedRef;
static tS32Bit   TrpMessageSentRef;
static tS32Bit   TrpMessageReceivedRef;
static tS32Bit   TrpMessageSentLengthRef;
static tS32Bit   TrpMessageReceivedLengthRef;
static tS32Bit   TrpStatusReceivedRef;

// LDBEmettre redefinition
void TrpSend(tAddress Address, tMsg* pMsg)
{
  EmissionMsg.Lng    = pMsg->Lng;
  EmissionMsg.pBuffer = pMsg->pBuffer;

  mLIBmemcpy(BufferEmission, pMsg->pBuffer, (pMsg->Lng/8));
  
  DONEcrireSortieB(TrpMessageSentRef, BufferEmission);
  DONEcrireSortieV(TrpAddressSentRef, Address);
  DONEcrireSortieV(TrpMessageSentLengthRef, pMsg->Lng);
  DONSignalerEvtSortie(TrpSendRef);
}

// LDBRecevoir redefinition
void TrpReceive(tAddress Address, tMsg* pMsg)
{
  ReceptionMsg.Lng    = pMsg->Lng;
  ReceptionMsg.pBuffer = pMsg->pBuffer;

  DONEcrireSortieV(TrpAddressSentRef, Address);
  DONEcrireSortieV(TrpMessageSentLengthRef, pMsg->Lng);  
  DONSignalerEvtSortie(TrpReceiveRef);
}

// DATTrpCallBackRxSpontWithoutAddr redefinition
void ChallengeReceived(tS32Bit)
{
  tU32Bit ulMessageLength;
  tMsg   Msg;

  DONLireV(TrpMessageReceivedLengthRef, &ulMessageLength, NULL, NULL);
  mLIBassert(ulMessageLength == 32);

  DONLireB(TrpMessageReceivedRef, BufferReception, NULL, NULL);
  DataReceived = (BufferReception[0] << 24) + (BufferReception[1] << 16) + (BufferReception[2] << 8) + BufferReception[3];

  Msg.pBuffer = (tU8Bit*)&DataReceived;
  Msg.Lng    = (LDBPARAM_TYPE_LNGMSG)ulMessageLength;

  DATTrpCallBackRxSpontWithoutAddr(cLDBCorrect, &Msg);
}

void CallBackTx(tS32Bit)
{
  tU32Bit ulMessageLength;
  tU32Bit Address;
  tU32Bit Status;

  DONLireV(TrpMessageReceivedLengthRef, &ulMessageLength, NULL, NULL);
  mLIBassert((ulMessageLength == 64) || (ulMessageLength == 32));

  DONLireV(TrpAddressReceivedRef, &Address, NULL, NULL);
  DONLireV(TrpStatusReceivedRef, &Status, NULL, NULL);

  DATTrpCallBackTxWithAddr((tAddress)Address, (tStatus)Status);
}

void CallBackRx(tS32Bit)
{
  tU32Bit ulMessageLength;
  tU32Bit Address;
  tU32Bit Status;

  DONLireV(TrpMessageReceivedLengthRef, &ulMessageLength, NULL, NULL);
  mLIBassert((ulMessageLength == 32) || (ulMessageLength == 10));

  DONLireB(TrpMessageReceivedRef, BufferReception, NULL, NULL);

  if (ulMessageLength == 10)
  {
    DataReceived = (BufferReception[0] << 8) + ((BufferReception[1] >> 6) & 0x03);
  }
  else
  {
    DataReceived = (BufferReception[0] << 24) + (BufferReception[1] << 16) + (BufferReception[2] << 8) + BufferReception[3];    
  }

  mLIBmemcpy(ReceptionMsg.pBuffer, (tU8Bit*)&DataReceived, 4);

  DONLireV(TrpAddressReceivedRef, &Address, NULL, NULL);
  DONLireV(TrpStatusReceivedRef, &Status, NULL, NULL);

  DATTrpCallBackRxWithAddr((tAddress)Address, (tStatus)Status);
}

void TrpEndControl(tS32Bit)
{
  tU32Bit ulCtrlLength;
  tU32Bit ulCtrlTypeValue;

  DONLireV(TrpControlReceveidRef, &ulCtrlTypeValue, &ulCtrlLength, NULL);

  if (ulCtrlTypeValue != cLDBTrpStop)
  {
    DATTrpCallBackEndCtrl((tCtrl)ulCtrlTypeValue, (tStatus)cLDBCorrect);
  }
}

void TrpInit(void)
{
  tCallBackCanal TrpCallBack;
  tS32Bit TrpRefFluxNIC;
  tS32Bit TrpRefFluxIP;
  tS32Bit TrpRefFluxIC;
  
  //--------------------------------------------------------------------------
  // Creation de la structure de Callback du canal Trp
  //--------------------------------------------------------------------------
  TrpCallBack.pCallBackCtrl    = DATTrpCallBackCtrl;
  TrpCallBack.pCallBackEndCtrl = NULL;
  TrpCallBack.pCallBackTx      = NULL;
  TrpCallBack.pCallBackRx      = NULL;
  TrpCallBack.pRxSpontWithAddr  = NULL;
  TrpCallBack.pTxSpontWithAddr  = NULL;
  TrpCallBack.NbRxSpont        = 0;
  TrpCallBack.NbTxSpont        = 0;

  //--------------------------------------------------------------------------
  // Creation du canal TRP
  //--------------------------------------------------------------------------
  RESCreerCanal(cLDBChannelTrp, "Trp", (tCallBackCanal*)&TrpCallBack, NULL, NULL);

  //--------------------------------------------------------------------------
  // Creation du flux Initie produit
  //--------------------------------------------------------------------------
  RESCreerFluxI(&TrpRefFluxIP, cLDBChannelTrp, cFluxIP, TrpSend);
  RESCreerTrameFI(NULL, TrpRefFluxIP, "TrpTX", 0, cMaxFrameLength, cFluxIP, 0);

  DONCreerEvtSortie(&TrpSendRef, "TrpEvtSendRequested", "Trp\\Request");
  DONCreerEvtEntree(NULL, "TrpEvtSendResponse", CallBackTx, "Trp\\Response");

  //--------------------------------------------------------------------------
  // Creation du flux Initie consomme
  //--------------------------------------------------------------------------
  RESCreerFluxI(&TrpRefFluxIC, cLDBChannelTrp, cFluxIC, TrpReceive);
  
  DONCreerEvtSortie(&TrpReceiveRef, "TrpEvtReceiveRequested", "Trp\\Request");
  DONCreerEvtEntree(NULL, "TrpEvtReceiveResponse", CallBackRx, "Trp\\Response");

  //--------------------------------------------------------------------------
  // Creation du flux Non Initie Consomme
  //--------------------------------------------------------------------------
  RESCreerFluxNI(&TrpRefFluxNIC, cLDBChannelTrp, cFluxNIC, NULL);

  DONCreerEvtEntree(NULL, "TrpEvtReceiveSpontResponse", ChallengeReceived, "Trp\\Response");

  //--------------------------------------------------------------------------
  // Creation des controles
  //--------------------------------------------------------------------------
  RESCreerControleSor(NULL, cLDBChannelTrp, "TrpCtrlWakeUp", cLDBTrpWakeUp , 0*(cTEMms/cLDBTick));
  RESCreerControleSor(NULL, cLDBChannelTrp, "TrpCtrlSleep",  cLDBTrpSleep  , 0*(cTEMms/cLDBTick));
  RESCreerControleSor(NULL, cLDBChannelTrp, "TrpCtrlStop",   cLDBTrpStop   , 0*(cTEMms/cLDBTick));
  RESCreerControleSor(NULL, cLDBChannelTrp, "TrpCtrlStopVerlog", cLDBTrpStopVerlog, 0*(cTEMms/cLDBTick));

  RESCreerControleEnt(NULL, cLDBChannelTrp, "TrpCtrlLinkError", cLDBTrpLinkError);
  RESCreerControleEnt(NULL, cLDBChannelTrp, "TrpCtrlDataError", cLDBTrpDataError);
  RESCreerControleEnt(NULL, cLDBChannelTrp, "TrpCtrlShortCircuitToBat", cLDBTrpShortCircuitToBat);
  RESCreerControleEnt(NULL, cLDBChannelTrp, "TrpCtrlShortCircuitToGnd", cLDBTrpShortCircuitToGnd);
  RESCreerControleEnt(NULL, cLDBChannelTrp, "TrpCtrlNoError", cLDBTrpNoError);

	// Control response received event
  DONCreerEvtEntree(NULL, "TrpEvtCtrlResponse", TrpEndControl, "Trp\\Response");

  // Type of control received in the response
  DONCreerEntreeV(&TrpControlReceveidRef, "CtrlType", 0, cCtrlLengthInBit, "Trp\\Response");


  DONCreerSortieV(&TrpAddressSentRef, "TrpAddressReceived", 0, cAddrLengthInBit, "Trp\\Request");
  DONCreerEntreeV(&TrpAddressReceivedRef, "TrpAddressSent", 0, cAddrLengthInBit, "Trp\\Response");

  DONCreerSortieB(&TrpMessageSentRef, "TrpMessageReceived", (tU8Bit*)&cMessageInit, cMessageLengthInBit, "Trp\\Request");
  DONCreerEntreeB(&TrpMessageReceivedRef, "TrpMessageSend", (tU8Bit*)&cMessageInit, cMessageLengthInBit, "Trp\\Response");

  DONCreerSortieV(&TrpMessageSentLengthRef, "TrpMessageReceivedLength", 0, cLengthInBitOfMessageLength, "Trp\\Request");
  DONCreerEntreeV(&TrpMessageReceivedLengthRef, "TrpMessageSentLength", 0, cLengthInBitOfMessageLength, "Trp\\Response");

  DONCreerEntreeV(&TrpStatusReceivedRef, "TrpResponseStatus", 0, cStatusLengthInBit, "Trp\\Response");
}

#endif // cLDBChannelTrp