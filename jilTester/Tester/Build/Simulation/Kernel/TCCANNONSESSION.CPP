// tcCanNonSession.cpp: implementation of the tcCanNonSession class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Config.h"
#ifdef CANAL_CAN      // Le canal can est utilisé

#include "tcCanNonSession.h"

#ifdef CAN_REPRISE_SUR_ERREUR
#pragma message( "tcCanNonASDT> Retry strategy enable") 
#else
#pragma message( "tcCanNonASDT> Retry strategy disable") 
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tcCanNonSession::tcCanNonSession(tcTimerCan* pTimerCan,tcCanUUDT* pCanUUDT):tcCanNonASDT(pTimerCan,pCanUUDT)
{
  //---- On réinitialise le timer périodique ----
  if (m_NumeroTempo!=cNumeroTempoInvalide)
  {
    m_pTimerCan->SetCallBackTempoPeriodique(m_NumeroTempo,&CallBackTempoPeriodique,this);
  }
  // On définit la CallBack d'erreur ASDT pour que les erreurs remonte à la Session
  tcCanASDT::SetCallBackErr(CallBackErr,this);

#ifndef DISABLE_SAD
  tcCanNonSession::m_SADObjectNumber = 0;
#endif
}

tcCanNonSession::~tcCanNonSession()
{
#ifndef DISABLE_SAD
//  tcCanSession::m_SADDoubleAdrFrame.SADDeconnect();
#endif

}

//********************************************************************//
// CallBack d'erreur de la ASDT, on fait suivre l'erreur
//********************************************************************//
void tcCanNonSession::CallBackErr(void* pParam)
{
  tcCanNonSession* pCanNonSession=(tcCanNonSession*)pParam;
  pCanNonSession->tcCanSession::SetErreur(pCanNonSession->tcCanASDT::GetErreur());
}

//********************************************************************//
// On crée un objet CAN Session
//********************************************************************//
BOOL tcCanNonSession::CreerObjet(tObjetCanSession2* pObjetCan)
{
  // On initialise l'objetCanUS
  tObjetCanNonSession* pObjetCanNonSession=new tObjetCanNonSession;

  pObjetCanNonSession->ObjetCanAS.IdRep=pObjetCan->IdRep;
  pObjetCanNonSession->ObjetCanAS.IdReq=pObjetCan->IdReq;
  pObjetCanNonSession->ObjetCanAS.ModeId=pObjetCan->ModeId;
  pObjetCanNonSession->ObjetCanAS.FCallBackCon=CallBackConAS;
  pObjetCanNonSession->ObjetCanAS.ParamCallBackCon=this;
  pObjetCanNonSession->ObjetCanAS.FCallBackInd=CallBackIndAS;
  pObjetCanNonSession->ObjetCanAS.ParamCallBackInd=this;
  pObjetCanNonSession->Etat=cEtatRecepAS;

  pObjetCanNonSession->ObjetCanAS.pParam = pObjetCan;  // For prevent an Session object creation
  pObjetCanNonSession->pParam=NULL;

  // On crée l'objet CanAS
  if (tcCanNonASDT::CreerObjet(&pObjetCanNonSession->ObjetCanAS))
  {
#ifndef DISABLE_SAD
    if ((pObjetCan->pParam == NULL)  // Indicate that it is an ASDT object only
      &&(tcCanNonSession::m_SADObjectNumber++ == 0))
    {
      tcCanSession::m_SADName = m_pCanUUDT->SADGetName();
      char Name[cSADMaxNameLength];
      sprintf(Name,"CanSession%s",tcCanSession::m_SADName);
      tcCanSession::m_SADDoubleAdrFrame.SADConnect(Name);
    }
#endif
    pObjetCanNonSession->pObjetCanSession=pObjetCan;
    ((tObjetCanNonASDT*)pObjetCanNonSession->ObjetCanAS.pParam)->pParam = pObjetCanNonSession;
    pObjetCan->pParam = pObjetCanNonSession;
    return cTrue;
  }
  else
  {
    delete pObjetCanNonSession;
    return cFalse;
  }
}

//********************************************************************//
// On redéfinie l'objet CanNonUSDT pour forcer les callback à prendre en compte les virtual
//********************************************************************//
BOOL tcCanNonSession::CreerObjet(tObjetCanNonUSDT* pObjetCanNonUSDT)
{
  // On redéfinit les CallBacks pour caster l'objet CanNonUSDT en ObjetCanNonSession et on crée l'objet
  pObjetCanNonUSDT->ObjetCanUURep.FCallBackCon=NULL;
  pObjetCanNonUSDT->ObjetCanUURep.FCallBackInd=CallBackInd;
  pObjetCanNonUSDT->ObjetCanUURep.ParamCallBackInd=this;

  pObjetCanNonUSDT->ObjetCanUUReq.FCallBackCon=CallBackCon;
  pObjetCanNonUSDT->ObjetCanUUReq.ParamCallBackCon=this;
  pObjetCanNonUSDT->ObjetCanUUReq.FCallBackInd=NULL;

  return tcCanNonUSDT::CreerObjet(pObjetCanNonUSDT);
}

//********************************************************************//
// On détruit un objet CAN ASDT
//********************************************************************//
BOOL tcCanNonSession::DetruireObjet(tObjetCanSession2* pObjetCan)
{
  // On cherche l'objet à l'aide de l'ObjetCan correspondant
  if (pObjetCan->pParam!=NULL)
  {
    tObjetCanNonSession* pObjetCanNonSession=(tObjetCanNonSession*)pObjetCan->pParam;
#ifndef DISABLE_SAD
    if ((pObjetCanNonSession->pParam == NULL)  // Indicate that it is an Session object only
      &&(--tcCanNonSession::m_SADObjectNumber == 0))
    {
      tcCanSession::m_SADDoubleAdrFrame.SADDeconnect();    
    }
#endif
    DetruireObjet(&pObjetCanNonSession->ObjetCanAS);     // On détruit l'objet US
    delete pObjetCanNonSession;
    return cTrue;
  }
  else
  {
    tcCanSession::SetErreur("tcCanNonSession::DetruireObjet> Objet CAN non crée");
    return cFalse;
  }
}

//********************************************************************//
// Connexion
//********************************************************************//
BOOL tcCanNonSession::Connect(tObjetCanSession2* pObjetCan)
{
  tObjetCanNonSession*  pObjetCanNonSession=(tObjetCanNonSession*)pObjetCan->pParam;
  tObjetCanNonASDT*     pObjetCanNonASDT=(tObjetCanNonASDT*)pObjetCanNonSession->ObjetCanAS.pParam;
  tObjetCanNonUSDT*     pObjetCanNonUSDT=(tObjetCanNonUSDT*)pObjetCanNonASDT->ObjetCanUS.pParam;
  if ((pObjetCanNonUSDT->MsgCanSeg.Etat==cEtatAttenteInd)
    &&(pObjetCanNonSession->Etat==cEtatRecepAS))
  {
    pObjetCanNonUSDT->MsgCanSeg.NB_Reemission=0;
    pObjetCanNonSession->Etat=cEtatEnvoiCS;
    ReqCS(pObjetCanNonUSDT);
    return cTrue;
  }
  else
  {
    tcCanSession::SetErreur("tcCanNonSession::Connect> Il y a déjà une requète en cours");
    return cFalse;
  }
}

//********************************************************************//
// Emission d'un message
//********************************************************************//
BOOL tcCanNonSession::Req(tObjetCanSession2* pObjetCan,tMsgCan2* pMsg)
{
  ASSERT(pObjetCan->pParam!=NULL);
  tObjetCanNonSession*  pObjetCanNonSession=(tObjetCanNonSession*)pObjetCan->pParam;
  tObjetCanNonASDT*     pObjetCanNonASDT=(tObjetCanNonASDT*)pObjetCanNonSession->ObjetCanAS.pParam;
  tObjetCanNonUSDT*     pObjetCanNonUSDT=(tObjetCanNonUSDT*)pObjetCanNonASDT->ObjetCanUS.pParam;
  if ((pObjetCanNonUSDT->MsgCanSeg.Etat==cEtatAttenteInd)
    &&(pObjetCanNonSession->Etat==cEtatRecepAS))
  {
    pObjetCanNonSession->Etat=cEtatEnvoiAS;
    return Req(&((tObjetCanNonSession*)pObjetCan->pParam)->ObjetCanAS,pMsg);    // On envoi la TrameAS
  }
  else
  {
    tcCanSession::SetErreur("tcCanNonSession::Req> Il y a déjà une requète en cours");
    return cFalse;
  }
}

//********************************************************************//
// Deconnexion
//********************************************************************//
BOOL tcCanNonSession::Deconnect(tObjetCanSession2* pObjetCan)
{
  tObjetCanNonSession*  pObjetCanNonSession=(tObjetCanNonSession*)pObjetCan->pParam;
  tObjetCanNonASDT*     pObjetCanNonASDT=(tObjetCanNonASDT*)pObjetCanNonSession->ObjetCanAS.pParam;
  tObjetCanNonUSDT*     pObjetCanNonUSDT=(tObjetCanNonUSDT*)pObjetCanNonASDT->ObjetCanUS.pParam;
  if ((pObjetCanNonUSDT->MsgCanSeg.Etat==cEtatAttenteInd)
    &&(pObjetCanNonSession->Etat==cEtatRecepAS))
  {
    pObjetCanNonUSDT->MsgCanSeg.NB_Reemission=0;
    pObjetCanNonSession->Etat=cEtatEnvoiDS;
    ReqDS(pObjetCanNonUSDT);
    return cTrue;
  }
  else
  {
    tcCanSession::SetErreur("tcCanNonSession::Deconnect> Il y a déjà une requète en cours");
    return cFalse;
  }
  return cTrue;
}

//********************************************************************//
// CallBack de fin de transmission UU
//********************************************************************//
void tcCanNonSession::CallBackCon(tObjetCanUU2* pObjetCanUU, void* pParam)
{
  // On récupère le pointeur de la classe qui a été passé en paramêtre
  tcCanNonSession* pCanNonSession=(tcCanNonSession*)pParam;
  // On cherche l'objet à l'aide de l'ObjetCanReq correspondant
  U8 i=0;
  tObjetCanNonUSDT* pObjetCanNonUSDT=NULL;
  while((i<pCanNonSession->m_lstObjetCanNonUSDT.GetSize()) && (pObjetCanNonUSDT==NULL))
  {
    pObjetCanNonUSDT=(tObjetCanNonUSDT*)pCanNonSession->m_lstObjetCanNonUSDT.GetAt(i);
    if (&pObjetCanNonUSDT->ObjetCanUUReq!=pObjetCanUU)
    {
      pObjetCanNonUSDT=NULL;
      i++;
    }
  }
  if (pObjetCanNonUSDT!=NULL)
  {
    pCanNonSession->TraiteMsgCanSegCon(pObjetCanNonUSDT);
  }
}

//********************************************************************//
// CallBack de réception d'un message UU
//********************************************************************//
void tcCanNonSession::CallBackInd(tObjetCanUU2* pObjetCanUU, tTrameCan2* pTrameCan, void* pParam)
{
  // On récupère le pointeur de la classe qui a été passé en paramêtre
  tcCanNonSession* pCanNonSession=(tcCanNonSession*)pParam;
  // On cherche l'objet à l'aide de l'ObjetCanReq correspondant
  U8 i=0;
  tObjetCanNonUSDT* pObjetCanNonUSDT=NULL;
  while((i<pCanNonSession->m_lstObjetCanNonUSDT.GetSize()) && (pObjetCanNonUSDT==NULL))
  {
    pObjetCanNonUSDT=(tObjetCanNonUSDT*)pCanNonSession->m_lstObjetCanNonUSDT.GetAt(i);
    if (&pObjetCanNonUSDT->ObjetCanUURep!=pObjetCanUU)
    {
      pObjetCanNonUSDT=NULL;
      i++;
    }
  }
  if (pObjetCanNonUSDT!=NULL)
  {
    pCanNonSession->TraiteMsgCanSegInd(pObjetCanNonUSDT,pTrameCan);
  }
}

//********************************************************************//
// CallBack de fin de transmission AS
//********************************************************************//
void tcCanNonSession::CallBackConAS(tObjetCanAS2* pObjetCanAS, void* pParam)
{
  tcCanNonSession* pCanNonSession=(tcCanNonSession*)pParam;
  tObjetCanNonSession* pObjetCanNonSession=(tObjetCanNonSession*)((tObjetCanNonASDT*)pObjetCanAS->pParam)->pParam;
  tObjetCanNonASDT*     pObjetCanNonASDT=(tObjetCanNonASDT*)pObjetCanNonSession->ObjetCanAS.pParam;
  tObjetCanNonUSDT*     pObjetCanNonUSDT=(tObjetCanNonUSDT*)pObjetCanNonASDT->ObjetCanUS.pParam;

  // Pas besoin de remettre l'état session à 0 car il sert simplement à aiguiller les CallBacks ASDT (Et en plus, le Timeout ne le fera pas)
  switch(pObjetCanNonSession->Etat)
  {
  case cEtatEnvoiCS:  pObjetCanNonSession->Etat=cEtatRecepAS;
#ifndef DISABLE_SAD
                      pCanNonSession->tcCanSession::m_SADDoubleAdrFrame.SADDoubleAdrFrameTextTx(pObjetCanNonUSDT->pObjetCanUS->IdReq,pObjetCanNonUSDT->pObjetCanUS->IdRep,"Connection");
#endif  
                      if (pObjetCanNonSession->pObjetCanSession->FCallBackConnectCon!=NULL)
                      {
                        pObjetCanNonSession->pObjetCanSession->FCallBackConnectCon(pObjetCanNonSession->pObjetCanSession,pObjetCanNonSession->pObjetCanSession->ParamCallBackConnectCon);
                      }
                      break;
  case cEtatEnvoiDS:  pObjetCanNonSession->Etat=cEtatRecepAS;
#ifndef DISABLE_SAD
                      pCanNonSession->tcCanSession::m_SADDoubleAdrFrame.SADDoubleAdrFrameTextTx(pObjetCanNonUSDT->pObjetCanUS->IdReq,pObjetCanNonUSDT->pObjetCanUS->IdRep,"Deconnection");
#endif  
                      if (pObjetCanNonSession->pObjetCanSession->FCallBackDeconnectCon!=NULL)
                      {
                        pObjetCanNonSession->pObjetCanSession->FCallBackDeconnectCon(pObjetCanNonSession->pObjetCanSession,pObjetCanNonSession->pObjetCanSession->ParamCallBackDeconnectCon);
                      }
                      break;
  case cEtatEnvoiAS:  pObjetCanNonSession->Etat=cEtatRecepAS;
#ifndef DISABLE_SAD
                      pCanNonSession->tcCanSession::m_SADDoubleAdrFrame.SADDoubleAdrFrameTraceTx(pObjetCanNonUSDT->pObjetCanUS->IdReq,pObjetCanNonUSDT->pObjetCanUS->IdRep,pObjetCanNonUSDT->MsgCanSeg.MsgCan.Longueur,pObjetCanNonUSDT->MsgCanSeg.MsgCan.Buffer);
#endif  
                      if (pObjetCanNonSession->pObjetCanSession->FCallBackCon!=NULL)
                      {
                        pObjetCanNonSession->pObjetCanSession->FCallBackCon(pObjetCanNonSession->pObjetCanSession,pObjetCanNonSession->pObjetCanSession->ParamCallBackCon);
                      }
                      break;
  default:            TRACE("tcCanNonSession::CallBackIndAS> Etat message session indéfini (%02X)\n",pObjetCanNonSession->Etat);
                      break;
  }
}

//********************************************************************//
// CallBack de réception d'un message AS
//********************************************************************//
void tcCanNonSession::CallBackIndAS(tObjetCanAS2* pObjetCanAS, tMsgCan2* pMsgCan, void* pParam)
{
  tcCanNonSession* pCanNonSession=(tcCanNonSession*)pParam;
  tObjetCanNonSession*  pObjetCanNonSession=(tObjetCanNonSession*)((tObjetCanNonASDT*)pObjetCanAS->pParam)->pParam;
  tObjetCanNonASDT*     pObjetCanNonASDT=(tObjetCanNonASDT*)pObjetCanNonSession->ObjetCanAS.pParam;
  tObjetCanNonUSDT*     pObjetCanNonUSDT=(tObjetCanNonUSDT*)pObjetCanNonASDT->ObjetCanUS.pParam;

  // Pas besoin de remettre l'état à 0 car le Timeout ne le fera pas
  switch(pObjetCanNonSession->Etat)
  {
  case cEtatRecepCS:  pObjetCanNonSession->Etat=cEtatRecepAS;
#ifndef DISABLE_SAD
                      pCanNonSession->tcCanSession::m_SADDoubleAdrFrame.SADDoubleAdrFrameTextRx(pObjetCanNonUSDT->pObjetCanUS->IdReq,pObjetCanNonUSDT->pObjetCanUS->IdRep,"Connection");
#endif  
                      if (pObjetCanNonSession->pObjetCanSession->FCallBackConnectInd!=NULL)
                      {
                        pObjetCanNonSession->pObjetCanSession->FCallBackConnectInd(pObjetCanNonSession->pObjetCanSession,pObjetCanNonSession->pObjetCanSession->ParamCallBackConnectInd);
                      }
                      break;
  case cEtatRecepDS:  pObjetCanNonSession->Etat=cEtatRecepAS;
#ifndef DISABLE_SAD
                      pCanNonSession->tcCanSession::m_SADDoubleAdrFrame.SADDoubleAdrFrameTextRx(pObjetCanNonUSDT->pObjetCanUS->IdReq,pObjetCanNonUSDT->pObjetCanUS->IdRep,"Deconnection");
#endif  
                      if (pObjetCanNonSession->pObjetCanSession->FCallBackDeconnectInd!=NULL)
                      {
                        pObjetCanNonSession->pObjetCanSession->FCallBackDeconnectInd(pObjetCanNonSession->pObjetCanSession,pObjetCanNonSession->pObjetCanSession->ParamCallBackDeconnectInd);
                      }
                      break;
  case cEtatRecepAS:  
#ifndef DISABLE_SAD
                      pCanNonSession->tcCanSession::m_SADDoubleAdrFrame.SADDoubleAdrFrameTraceRx(pObjetCanNonUSDT->pObjetCanUS->IdReq,pObjetCanNonUSDT->pObjetCanUS->IdRep,pObjetCanNonUSDT->MsgCanSeg.MsgCan.Longueur,pObjetCanNonUSDT->MsgCanSeg.MsgCan.Buffer);
#endif  
                      if (pObjetCanNonSession->pObjetCanSession->FCallBackInd!=NULL)
                      {
                        pObjetCanNonSession->pObjetCanSession->FCallBackInd(pObjetCanNonSession->pObjetCanSession,pMsgCan,pObjetCanNonSession->pObjetCanSession->ParamCallBackInd);
                      }
                      break;
  default:            TRACE("tcCanNonSession::CallBackConAS> Etat message session indéfini (%02X)\n",pObjetCanNonSession->Etat);
                      break;
  }
}

//********************************************************************//
// Traitement d'une émission CS (ConnectSession) 
//********************************************************************//
void tcCanNonSession::ReqCS(tObjetCanNonUSDT* pObjetCanNonUSDT)
{
  // On simplifie l'écriture pour le message segmenté ----
  tMsgCanSeg* pMsgCanSeg=&pObjetCanNonUSDT->MsgCanSeg;

  // On envoie la trame CS
  tTrameCan2 TrameCan;
  TrameCan.Longueur=cLongueurMaxTrameCan;
  memset(TrameCan.Buffer,cPciOctetDeRemplissage,cLongueurMaxTrameCan);
  TrameCan.Buffer[cPciPosCde]=cPciCS;
  pMsgCanSeg->Etat=cEtatAttenteConCS;                           // On passe en attente de confirmation d'envoi
  pMsgCanSeg->DateEvt=m_pTimerCan->GetDate();                   // On mémorise le dernier évènement
  m_pCanUUDT->Req(&pObjetCanNonUSDT->ObjetCanUUReq,&TrameCan);  // On envoi
}

//********************************************************************//
// Traitement d'une émission DS (ConnectSession) 
//********************************************************************//
void tcCanNonSession::ReqDS(tObjetCanNonUSDT* pObjetCanNonUSDT)
{
  // On simplifie l'écriture pour le message segmenté ----
  tMsgCanSeg* pMsgCanSeg=&pObjetCanNonUSDT->MsgCanSeg;

  // On envoie la trame DS
  tTrameCan2 TrameCan;
  TrameCan.Longueur=cLongueurMaxTrameCan;
  memset(TrameCan.Buffer,cPciOctetDeRemplissage,cLongueurMaxTrameCan);
  TrameCan.Buffer[cPciPosCde]=cPciDS;
  pMsgCanSeg->Etat=cEtatAttenteConDS;                           // On passe en attente de confirmation d'envoi
  pMsgCanSeg->DateEvt=m_pTimerCan->GetDate();                   // On mémorise le dernier évènement
  m_pCanUUDT->Req(&pObjetCanNonUSDT->ObjetCanUUReq,&TrameCan);  // On envoi
}

//********************************************************************//
// CallBack timer gérant les émissions de trames et les TimeOut
//********************************************************************//
void tcCanNonSession::CallBackTempoPeriodique(void* Param)
{
  ((tcCanNonSession*)Param)->TraiteTempoPeriodique();
}

//********************************************************************//
// Gere les erreurs suivants le type, on vérifie si il y a l'acquittement comme erreur
//********************************************************************//
void tcCanNonSession::GereErreurUSDT(tErreurUSDT TypeErreur,tObjetCanNonUSDT* pObjetCanNonUSDT,tTrameCan2* pTrameCan)
{
  U32       DureeTimeOut;
  tErreurUSDT   TypeErr;

  if ((pObjetCanNonUSDT->pParam!=NULL)                                // On a un ObjetNonASDT
    &&(((tObjetCanNonASDT*)pObjetCanNonUSDT->pParam)->pParam!=NULL))  // On a un ObjetNonSession
  {
    tObjetCanNonSession* pObjetCanNonSession=(tObjetCanNonSession*)((tObjetCanNonASDT*)pObjetCanNonUSDT->pParam)->pParam;

    switch(TypeErreur)
    {
    case cErrEtatCon: // On regarde si on a reçu la confirmation d'envoi de la connection de session
                      if (pObjetCanNonUSDT->MsgCanSeg.Etat==cEtatAttenteConCS)
                      {
                        pObjetCanNonSession->Etat=cEtatEnvoiCS;
                        pObjetCanNonUSDT->MsgCanSeg.Etat=cEtatAttenteIndAK;
                        pObjetCanNonUSDT->MsgCanSeg.DateEvt=m_pTimerCan->GetDate();
                      }
                      else if (pObjetCanNonUSDT->MsgCanSeg.Etat==cEtatAttenteConDS)
                      {
                        pObjetCanNonSession->Etat=cEtatEnvoiDS;
                        pObjetCanNonUSDT->MsgCanSeg.Etat=cEtatAttenteIndAK;
                        pObjetCanNonUSDT->MsgCanSeg.DateEvt=m_pTimerCan->GetDate();
                      }
                      else
                      {
                        tcCanNonASDT::GereErreurUSDT(TypeErreur,pObjetCanNonUSDT,pTrameCan);
                      }
                      break;
    case cErrPci:     // On regarde si on a reçu un CS ou un DS, si oui, on envoi l'acquittement
                      ASSERT(pTrameCan!=NULL);
                      if (pTrameCan->Buffer[cPciPosCde]==cPciCS)
                      {
                        pObjetCanNonSession->Etat=cEtatRecepCS;
                        ReqAK(pObjetCanNonUSDT);
                      }
                      else if (pTrameCan->Buffer[cPciPosCde]==cPciDS)
                      {
                        pObjetCanNonSession->Etat=cEtatRecepDS;
                        ReqAK(pObjetCanNonUSDT);
                      }
                      else
                      {
                        tcCanNonASDT::GereErreurUSDT(TypeErreur,pObjetCanNonUSDT,pTrameCan);
                      }
                      break;
    case cErrEtatTimeOut:     // Un etat n'a pas été connu à la gestion du timeOut
                      switch(pObjetCanNonUSDT->MsgCanSeg.Etat)
                      {
                      case cEtatAttenteConCS:   // Attente de confirmation d'envoi UUDT
                      case cEtatAttenteConDS:
                                                DureeTimeOut = cPciTimeOutN_Ar;
                                                TypeErr      = cErrTimeOutReq;
                                                break;
                      case cEtatAttenteIndCS:   // TimeOut de réponse des Sessions
                      case cEtatAttenteIndDS:   
                                                DureeTimeOut = cPciTimeOutN_Bs;
                                                TypeErr      = cErrTimeOutRep;
                                                break;
                      default:                  // Etat inconnu
                                                DureeTimeOut = 0;
                                                TypeErr      = cErrEtatTimeOut;
                                                break;
                      }
                      if (m_pTimerCan->DateDepassee(pObjetCanNonUSDT->MsgCanSeg.DateEvt+DureeTimeOut))
                      {
                        tcCanNonASDT::GereErreurUSDT(TypeErr,pObjetCanNonUSDT);
                      }
                      break;
    default:          // On gére l'erreur dans la ASDT
                      tcCanNonASDT::GereErreurUSDT(TypeErreur,pObjetCanNonUSDT,pTrameCan);
    }
  }
  else    // Pas d'objet NonSession, on redescend
  {
    tcCanNonASDT::GereErreurUSDT(TypeErreur,pObjetCanNonUSDT,pTrameCan);
  }
}

//********************************************************************//
// Initialisation de l'état d'émission/réception
//********************************************************************//
void tcCanNonSession::InitialiseEtats(tObjetCanNonUSDT* pObjetCanNonUSDT)
{
  if ((pObjetCanNonUSDT->pParam!=NULL)                                // On a un ObjetNonASDT
    &&(((tObjetCanNonASDT*)pObjetCanNonUSDT->pParam)->pParam!=NULL))  // On a un ObjetNonSession
  {
    TRACE("tcCanNonSession::InitialiseEtats> ...\n");
    tObjetCanNonSession* pObjetCanNonSession=(tObjetCanNonSession*)((tObjetCanNonASDT*)pObjetCanNonUSDT->pParam)->pParam;
    pObjetCanNonSession->Etat=cEtatRecepAS;
    tcCanNonASDT::InitialiseEtats(pObjetCanNonUSDT);
  }
  else    // Pas d'objet NonSession, on redescend
  {
    tcCanNonASDT::InitialiseEtats(pObjetCanNonUSDT);
  }
}

//********************************************************************//
// Gère la reprise sur erreur
//********************************************************************//
void tcCanNonSession::RepriseSurErreur(tObjetCanNonUSDT* pObjetCanNonUSDT)
{
  if ((pObjetCanNonUSDT->pParam!=NULL)                                // On a un ObjetNonASDT
    &&(((tObjetCanNonASDT*)pObjetCanNonUSDT->pParam)->pParam!=NULL))  // On a un ObjetNonSession
  {
    tObjetCanNonSession* pObjetCanNonSession=(tObjetCanNonSession*)((tObjetCanNonASDT*)pObjetCanNonUSDT->pParam)->pParam;
#ifdef CAN_REPRISE_SUR_ERREUR       // Si reprise sur erreur activé, On réémet le message US,CS,DS cReemissionMax fois maximum
    TRACE("tcCanNonSession::RepriseSurErreur> ...\n");
    if (pObjetCanNonUSDT->MsgCanSeg.NB_Reemission++<cReemissionMax)
    {
      switch(pObjetCanNonSession->Etat)
      {
      case cEtatEnvoiCS:  ReqCS(pObjetCanNonUSDT);
                          break;
      case cEtatEnvoiDS:  ReqDS(pObjetCanNonUSDT);
                          break;
      case cEtatEnvoiAS:  tcCanNonUSDT::Req(pObjetCanNonUSDT);
                          break;
      default:
        TRACE("tcCanNonSession::RepriseSurErreur> Etat non identifié pour la reprise sur erreur (%d)\n",pObjetCanNonSession->Etat);
      }
    }
    else
    {
      InitialiseEtats(pObjetCanNonUSDT);
    }
#else
    pObjetCanNonSession->Etat=cEtatRecepAS;
    pObjetCanNonUSDT->MsgCanSeg.Etat=cEtatAttenteInd;
#endif
  }
  else    // Pas d'objet NonSession, on redescend
  {
    tcCanNonASDT::RepriseSurErreur(pObjetCanNonUSDT);
  }
}

#endif    // Le canal can est utilisé