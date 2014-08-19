/*============================================================================
  Component ....................... parkwp
  File revision ................... $Revision:   1.1  $
  Last modification date .......... $Modtime:   Mar 20 2009 18:46:24  $
  Generation date ................. 25/02/2003
  Author Name ..................... XX
  File Name ....................... ParamKwp.cpp

  -------------------------------------------------------------------------
  Copyright ... This software is JCI property. Duplication or
                disclosure is prohibited without JCI written permission
  -------------------------------------------------------------------------

  - This file should only contain data useful to the programmer to use
    this Component
  - Component exported macros, constants and types are defined in this file
  - Component exported variables and functions are declared in this file
    with the extern keyword

  ==========================================================================*/
//***************************************************************************
#define ParamKWP "ParamKWP"

//--------------------------------------------------------------------------
//---------------- Inclusion de fichiers (système et librairies -----------
//--------------------------------------------------------------------------

#include "string.h"
#include "Ldbpc.h" // defini les types et constantes de bases
#include "Ldbpcpar.h"
#include "LDBPCTim.h"    // Definit l'interface du Module Timer
#include "LdbpcRes.h"        // Definit l'interface du Module Donnees

extern tcRessources Ressources;

#ifdef cLDBChannelKwp

#define cDureeOctetKwp    ( 1058 * cTEMus )
#define cDureeTIdle       ( 25000 * cTEMus )
#define cCodeOutil        0xF1
#define cKwpMaxFrameSize  70

static tAddress   AdresseKWP;

static tS32Bit      RefKWPTargetByteRx;
static tS32Bit      RefKWPSourceByteRx;
static tS32Bit      RefKWPLngRx;
static tS32Bit      RefKWPDataRx;
static tS32Bit      RefKWPChecksumRx;

static tS32Bit      RefKWPTargetByteTx;
static tS32Bit      RefKWPSourceByteTx;
static tS32Bit      RefKWPLngTx;
static tS32Bit      RefKWPDataTx;
static tTimerRef  RefKWPTempoEndEmission;
static tTimerRef  RefKWPTempoTIdle;
static tS32Bit      RefKWPChecksumTx;
static tS32Bit      RefKWPBCMReceiveKWPMsg;

static tS32Bit      RefReceptionOfNewMsg;

static tS32Bit      RxEnable;
static tS32Bit      SearchWakeUp;

void LDBPCKWPControler(tCtrl Ctrl)
{
  switch( Ctrl )
  {
    case( cLDBKwpWaitForWakeUp ):
      RxEnable = cFalse;
      SearchWakeUp = cTrue;
      break;

    case( cLDBKwpEnableRx ):
      RxEnable = cTrue;
      SearchWakeUp = cFalse;
      break;

    case( cLDBKwpDisableRx ):
      RxEnable = cFalse;
      SearchWakeUp = cFalse;
      break;

     default:
      mLIBassert(0);
      break;
  }
}

void EndEmissionKWP(tS32Bit)
{
  // Send control for the end of the emission (to the DAT layer)
  DATKwpCallBackTxWithoutAddr( cLDBCorrect );
  // Create a event for the end of the emission (for the scripts)
  DONSignalerEvtSortie( RefKWPBCMReceiveKWPMsg );
}

void LDBPCKWPEmettre(tAddress Adresse, tMsg* pMsg)
{
  mLIBassert(RxEnable == cFalse);
  // Copie du message
  DONEcrireSortieV( RefKWPTargetByteTx,    pMsg->pBuffer[1]    );
  DONEcrireSortieV( RefKWPSourceByteTx,    pMsg->pBuffer[2]    );
  DONEcrireSortieV( RefKWPLngTx,          pMsg->pBuffer[0] & 0x3F);
  DONEcrireSortieB( RefKWPDataTx,          &pMsg->pBuffer[3]  );
  DONEcrireSortieV( RefKWPChecksumTx,      pMsg->pBuffer[pMsg->Lng-1]);

  // Armement de la tempo de fin d'emission
  tDelay DureeEmission = (pMsg->Lng) * (cDureeOctetKwp);
  LDBPCStartTimer(RefKWPTempoEndEmission, DureeEmission/cLDBTick, EndEmissionKWP);
}


void SendKWPFormattedMsg(tS32Bit)
{
  if (RxEnable == cTrue)
  {
    tU8Bit Corps[cKwpMaxFrameSize];
    tMsg Msg;
    tU32Bit Dest, Src, Lng, Cks;
    int I;

    DONLireV( RefKWPTargetByteRx,   &Dest, NULL, NULL) ;
    DONLireV( RefKWPSourceByteRx,    &Src, NULL, NULL) ;
    DONLireV( RefKWPLngRx,          &Lng, NULL, NULL) ;
    DONLireB( RefKWPDataRx,          &Corps[3], NULL, NULL );

    // The checkusm and the the start bit must be set by the script
    Corps[0] = (tU8Bit)  (Lng & 0xFF) + 0x80;
    Corps[1] = (tU8Bit)  Dest & 0xFF;
    Corps[2] = (tU8Bit)  Src & 0xFF;
    Msg.Lng  = (LDBPARAM_TYPE_LNGMSG) (Lng & 0x3F) + 4;
    Msg.pBuffer = Corps;

    Cks = 0;

    for(I=0;I<(Msg.Lng-1);I++)
    {
      Cks += Corps[I];
    }
    Corps[Msg.Lng-1] = (tU8Bit)  Cks;

    DONSignalerEvtSortie( RefReceptionOfNewMsg );

    tDelay Time;
    Timer.LireDate(&Time);
    Ressources.m_TabCanal[cLDBChannelKwp]->m_SADAdrTrace.SADAdrFrameTraceRx(0,Msg.Lng,Msg.pBuffer,(tU32Bit)(Time/100000UL));

    DATKwpCallBackRxSpontWithoutAddr(cLDBCorrect,&Msg);
  }
}

void SendKWPMsg(tS32Bit)
{
  if (RxEnable == cTrue)
  {
    tU8Bit Corps[cKwpMaxFrameSize];
    tMsg Msg;
    tU32Bit Dest, Src, Lng, Cks;

    DONLireV( RefKWPTargetByteRx,   &Dest, NULL, NULL) ;
    DONLireV( RefKWPSourceByteRx,    &Src, NULL, NULL) ;
    DONLireV( RefKWPLngRx,          &Lng, NULL, NULL) ;
    DONLireB( RefKWPDataRx,          &Corps[3], NULL, NULL );
    DONLireV( RefKWPChecksumRx,      &Cks, NULL, NULL) ;

    // The checkusm and the the start bit must be set by the script
    Corps[0] = (tU8Bit)  (Lng & 0xFF);
    Corps[1] = (tU8Bit)  Dest & 0xFF;
    Corps[2] = (tU8Bit)  Src & 0xFF;
    Msg.Lng  = (LDBPARAM_TYPE_LNGMSG) (Lng & 0x3F) + 4;
    Msg.pBuffer = Corps;
    Corps[Msg.Lng-1] = (tU8Bit)  Cks;

    DONSignalerEvtSortie( RefReceptionOfNewMsg );

    tDelay Time;
    Timer.LireDate(&Time);
    Ressources.m_TabCanal[cLDBChannelKwp]->m_SADAdrTrace.SADAdrFrameTraceRx(0,Msg.Lng,Msg.pBuffer,(tU32Bit)(Time/100000UL));

    DATKwpCallBackRxSpontWithoutAddr(cLDBCorrect,&Msg); 
  }
}

void SendKWPWakeUp(tS32Bit)
{
// This condition is commented because WakeUp always sent by LDB_DIN
  if (SearchWakeUp == cTrue)
  {
    SearchWakeUp = cFalse;
    RxEnable = cTrue;
    DATKwpCallBackCtrl(cLDBKwpWakeUp);
  }
}

void EndWakeUpMsg(tS32Bit)
{
  if (RxEnable == cTrue)
  {
    tU8Bit  Corps[cKwpMaxFrameSize];
    tMsg    Msg;
    tU32Bit  Dest,Src,Cks;

    DONLireV(RefKWPTargetByteRx,&Dest,NULL,NULL) ;
    DONLireV(RefKWPSourceByteRx,&Src,NULL,NULL) ;

    Corps[0] = 0x81;
    Corps[1] = (tU8Bit)(Dest & 0xFF);
    Corps[2] = (tU8Bit)(Src & 0xFF);
    Corps[3] = (tU8Bit)0x81;
    Msg.Lng     = 5;
    Msg.pBuffer  = Corps;

    Cks = 0;
    for(tU8Bit I=0;I<(Msg.Lng-1);I++)
    {
      Cks += Corps[I];
    }
    Corps[Msg.Lng-1] = (tU8Bit)  Cks;

    DONSignalerEvtSortie( RefReceptionOfNewMsg );

    tDelay Time;
    Timer.LireDate(&Time);
    Ressources.m_TabCanal[cLDBChannelKwp]->m_SADAdrTrace.SADAdrFrameTraceRx(0,Msg.Lng,Msg.pBuffer,(tU32Bit)(Time/100000UL));

    DATKwpCallBackRxSpontWithoutAddr(cLDBCorrect,&Msg);
  }
}

void SendKWPWakeUpMsg(tS32Bit)  // Send WakeUp next message
{
// This condition is commented because WakeUp always sent by LDB_DIN
  if (SearchWakeUp == cTrue)
  {
      SearchWakeUp = cFalse;
      RxEnable = cTrue;
      DATKwpCallBackCtrl(cLDBKwpWakeUp);    
      tDelay DureeWakeUp = tDelay (cDureeTIdle);
      LDBPCStartTimer(RefKWPTempoTIdle, DureeWakeUp/cLDBTick, EndWakeUpMsg);
  }
}

void KwpInit(void)
{
  tCallBackCanal CallBackKWP;
  tS32Bit refFluxIp;
  tU8Bit InitZero[cKwpMaxFrameSize];
  memset( InitZero, 0, cKwpMaxFrameSize );

  //--------------------------------------------------------------------------
  // Creation de la structure de Callback du canal CAN
  //--------------------------------------------------------------------------
  CallBackKWP.pCallBackCtrl     = NULL;
  CallBackKWP.pCallBackEndCtrl  = DATKwpCallBackEndCtrl;
  CallBackKWP.pCallBackTx       = NULL;
  CallBackKWP.pCallBackRx       = NULL;
  CallBackKWP.pRxSpontWithAddr   = NULL;
  CallBackKWP.pTxSpontWithAddr   = NULL;
  CallBackKWP.NbRxSpont         = 0;
  CallBackKWP.NbTxSpont         = 0;

  //--------------------------------------------------------------------------
  // Creation du canal CAN
  //--------------------------------------------------------------------------
  RESCreerCanal(cLDBChannelKwp, "Kwp", (tCallBackCanal *)&CallBackKWP, LDBPCKWPControler, NULL);

  //--------------------------------------------------------------------------
  // Creation des flux
  //--------------------------------------------------------------------------  
  RESCreerFluxI(&refFluxIp,cLDBChannelKwp, cFluxIP , LDBPCKWPEmettre );

  // Creation des deux trames
  RESCreerTrameFI(NULL, refFluxIp, "EmissionUCH", 0, cKwpMaxFrameSize, cFluxIP,0);

  //--------------------------------------------------------------------------
  // Creation des donnees
  //--------------------------------------------------------------------------
  DONCreerEntreeV   ( &RefKWPTargetByteRx,      "KWPTargetByteRx",    0x26, 8, "Kwp" );
  DONCreerEntreeV   ( &RefKWPSourceByteRx,      "KWPSourceByteRx",    0xF1, 8, "Kwp" );
  DONCreerEntreeV   ( &RefKWPLngRx,             "KWPLngRx",            0, 8, "Kwp" );
  DONCreerEntreeB   ( &RefKWPDataRx,            "KWPDataRx",          InitZero, (cKwpMaxFrameSize-3)*8, "Kwp" ) ;
  DONCreerEntreeV   ( &RefKWPChecksumRx,        "KWPChecksumRx",      0, 8, "Kwp" );
  DONCreerEvtEntree ( NULL,                     "KWPSendMsg",         SendKWPMsg, "Kwp" );
  DONCreerEvtEntree ( NULL,                     "KWPSendFormattedMsg",SendKWPFormattedMsg, "Kwp" );
  DONCreerEvtEntree ( NULL,                     "KWPSendWakeUp",      SendKWPWakeUp, "Kwp" );
  DONCreerEvtEntree ( NULL,                     "KWPSendWakeUpMsg",   SendKWPWakeUpMsg, "Kwp" );
  DONCreerEvtSortie ( &RefReceptionOfNewMsg,    "KWPSendMsgOk",      "Kwp" );  

  DONCreerSortieV   ( &RefKWPTargetByteTx,      "KWPTargetByteTx",   0xF1, 8, "Kwp" );
  DONCreerSortieV   ( &RefKWPSourceByteTx,      "KWPSourceByteTx",   0x26, 8, "Kwp" );
  DONCreerSortieV   ( &RefKWPLngTx,             "KWPLngTx",          0, 6, "Kwp" );
  DONCreerSortieB   ( &RefKWPDataTx,            "KWPDataTx",         InitZero, (cKwpMaxFrameSize-3)*8, "Kwp" ) ;
  DONCreerSortieV   ( &RefKWPChecksumTx,        "KWPChecksumTx",     0, 8, "Kwp" );
  DONCreerEvtSortie ( &RefKWPBCMReceiveKWPMsg,  "KWPReceiveMsg",     "Kwp" );
  LDBPCCreerTempo   ( &RefKWPTempoEndEmission );
  LDBPCCreerTempo   ( &RefKWPTempoTIdle );

  // Create controls
  RESCreerControleSor(NULL, cLDBChannelKwp, "CtrlKwpWaitForWakeUp", cLDBKwpWaitForWakeUp, 0*(cTEMus/cLDBTick));
  RESCreerControleSor(NULL, cLDBChannelKwp, "CtrlKwpEnableRx",      cLDBKwpEnableRx, 0*(cTEMus/cLDBTick));
  RESCreerControleSor(NULL, cLDBChannelKwp, "CtrlKwpDisableRx",     cLDBKwpDisableRx, 0*(cTEMus/cLDBTick));
  RESCreerControleEnt(NULL, cLDBChannelKwp, "CtrlKwpWakeUp",        cLDBKwpWakeUp);

  RxEnable      = cTrue;
  SearchWakeUp  = cTrue;
}
#endif