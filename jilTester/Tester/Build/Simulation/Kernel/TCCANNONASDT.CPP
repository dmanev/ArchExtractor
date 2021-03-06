// tcCanNonASDT.cpp: implementation of the tcCanNonASDT class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Config.h"
#ifdef CANAL_CAN      // Le canal can est utilis�

#include "tcCanNonASDT.h"

#ifdef CAN_REPRISE_SUR_ERREUR
#pragma message( "tcCanNonASDT> Retry strategy enable") 
#else
#pragma message( "tcCanNonASDT> Retry strategy disable") 
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tcCanNonASDT::tcCanNonASDT(tcTimerCan* pTimerCan,tcCanUUDT* pCanUUDT):tcCanNonUSDT(pTimerCan,pCanUUDT)
{
  //---- On r�initialise le timer p�riodique ----
  if (m_NumeroTempo!=cNumeroTempoInvalide)
  {
    m_pTimerCan->SetCallBackTempoPeriodique(m_NumeroTempo,&CallBackTempoPeriodique,this);
  }
  // On d�finit la CallBack d'erreur USDT pour que les erreurs remonte � l'ASDT
  tcCanNonUSDT::SetCallBackErr(CallBackErr,this);

#ifndef DISABLE_SAD
  tcCanNonASDT::m_SADObjectNumber = 0;
#endif
}

tcCanNonASDT::~tcCanNonASDT()
{
#ifndef DISABLE_SAD
//  tcCanASDT::m_SADDoubleAdrFrame.SADDeconnect();
#endif
}

//********************************************************************//
// CallBack d'erreur de la USDT, on fait suivre l'erreur
//********************************************************************//
void tcCanNonASDT::CallBackErr(void* pParam)
{
  tcCanNonASDT* pCanNonASDT=(tcCanNonASDT*)pParam;
  pCanNonASDT->tcCanASDT::SetErreur(pCanNonASDT->tcCanUSDT::GetErreur());
}

//********************************************************************//
// On cr�e un objet CAN ASDT
//********************************************************************//
BOOL tcCanNonASDT::CreerObjet(tObjetCanAS2* pObjetCan)
{
  // On initialise l'objetCanUS
  tObjetCanNonASDT* pObjetCanNonASDT=new tObjetCanNonASDT;

  pObjetCanNonASDT->ObjetCanUS.IdRep=pObjetCan->IdRep;
  pObjetCanNonASDT->ObjetCanUS.IdReq=pObjetCan->IdReq;
  pObjetCanNonASDT->ObjetCanUS.ModeId=pObjetCan->ModeId;
  pObjetCanNonASDT->ObjetCanUS.FCallBackCon=CallBackConUS;
  pObjetCanNonASDT->ObjetCanUS.ParamCallBackCon=this;
  pObjetCanNonASDT->ObjetCanUS.FCallBackInd=CallBackIndUS;
  pObjetCanNonASDT->ObjetCanUS.ParamCallBackInd=this;

  pObjetCanNonASDT->ObjetCanUS.pParam = pObjetCan;  // For prevent an ASDT object creation
  pObjetCanNonASDT->pParam=NULL;

  // On cr�e l'objet CanUS
  if (tcCanNonUSDT::CreerObjet(&pObjetCanNonASDT->ObjetCanUS))
  {
#ifndef DISABLE_SAD
    if ((pObjetCan->pParam == NULL)  // Indicate that it is an ASDT object only
      &&(tcCanNonASDT::m_SADObjectNumber++ == 0))
    {
      tcCanASDT::m_SADName = m_pCanUUDT->SADGetName();
      char Name[cSADMaxNameLength];
      sprintf(Name,"CanAS%s",tcCanASDT::m_SADName);
      tcCanASDT::m_SADDoubleAdrFrame.SADConnect(Name);
    }
#endif
    pObjetCanNonASDT->pObjetCanAS=pObjetCan;
    ((tObjetCanNonUSDT*)pObjetCanNonASDT->ObjetCanUS.pParam)->pParam = pObjetCanNonASDT;
    pObjetCan->pParam = pObjetCanNonASDT;
    return cTrue;
  }
  else
  {
    delete pObjetCanNonASDT;
    return cFalse;
  }
}

//********************************************************************//
// On red�finie l'objet CanNonUSDT pour forcer les callback � prendre en compte les virtual
//********************************************************************//
BOOL tcCanNonASDT::CreerObjet(tObjetCanNonUSDT* pObjetCanNonUSDT)
{
  // On red�finit les CallBacks pour caster l'objet CanNonUSDT en ObjetCanNonASDT et on cr�e l'objet
  pObjetCanNonUSDT->ObjetCanUURep.FCallBackCon=NULL;
  pObjetCanNonUSDT->ObjetCanUURep.FCallBackInd=CallBackInd;
  pObjetCanNonUSDT->ObjetCanUURep.ParamCallBackInd=this;

  pObjetCanNonUSDT->ObjetCanUUReq.FCallBackCon=CallBackCon;
  pObjetCanNonUSDT->ObjetCanUUReq.ParamCallBackCon=this;
  pObjetCanNonUSDT->ObjetCanUUReq.FCallBackInd=NULL;

  return tcCanNonUSDT::CreerObjet(pObjetCanNonUSDT);
}

//********************************************************************//
// On d�truit un objet CAN ASDT
//********************************************************************//
BOOL tcCanNonASDT::DetruireObjet(tObjetCanAS2* pObjetCan)
{
  // On cherche l'objet � l'aide de l'ObjetCan correspondant
  if (pObjetCan->pParam!=NULL)
  {
    tObjetCanNonASDT* pObjetCanNonASDT=(tObjetCanNonASDT*)pObjetCan->pParam;
#ifndef DISABLE_SAD
    if ((pObjetCanNonASDT->pParam == NULL)  // Indicate that it is an ASDT object only
      &&(--tcCanNonASDT::m_SADObjectNumber == 0))
    {
      tcCanASDT::m_SADDoubleAdrFrame.SADDeconnect();
    }
#endif
    DetruireObjet(&pObjetCanNonASDT->ObjetCanUS);     // On d�truit l'objet US
    delete pObjetCanNonASDT;
    return cTrue;
  }
  else
  {
    tcCanASDT::SetErreur("tcCanNonASDT::DetruireObjet> CAN Object don't created");
    return cFalse;
  }
}

//********************************************************************//
// Emission d'un message
//********************************************************************//
BOOL tcCanNonASDT::Req(tObjetCanAS2* pObjetCan,tMsgCan2* pMsg)
{
  ASSERT(pObjetCan->pParam!=NULL);
  tObjetCanNonASDT*     pObjetCanNonASDT=(tObjetCanNonASDT*)pObjetCan->pParam;
  tObjetCanNonUSDT*     pObjetCanNonUSDT=(tObjetCanNonUSDT*)pObjetCanNonASDT->ObjetCanUS.pParam;
  if (pObjetCanNonUSDT->MsgCanSeg.Etat==cEtatAttenteInd)
  {
    return Req(&((tObjetCanNonASDT*)pObjetCan->pParam)->ObjetCanUS,pMsg);    // On envoi la TrameUS
  }
  else
  {
    tcCanASDT::SetErreur("tcCanNonASDT::Req> Il y a d�j� une requ�te en cours");
    return cFalse;
  }
}

//********************************************************************//
// CallBack de fin de transmission UU
//********************************************************************//
void tcCanNonASDT::CallBackCon(tObjetCanUU2* pObjetCanUU, void* pParam)
{
  // On r�cup�re le pointeur de la classe qui a �t� pass� en param�tre
  tcCanNonASDT* pCanNonASDT=(tcCanNonASDT*)pParam;
  // On cherche l'objet � l'aide de l'ObjetCanReq correspondant
  U8 i=0;
  tObjetCanNonUSDT* pObjetCanNonUSDT=NULL;
  while((i<pCanNonASDT->m_lstObjetCanNonUSDT.GetSize()) && (pObjetCanNonUSDT==NULL))
  {
    pObjetCanNonUSDT=(tObjetCanNonUSDT*)pCanNonASDT->m_lstObjetCanNonUSDT.GetAt(i);
    if (&pObjetCanNonUSDT->ObjetCanUUReq!=pObjetCanUU)
    {
      pObjetCanNonUSDT=NULL;
      i++;
    }
  }
  if (pObjetCanNonUSDT!=NULL)
  {
    pCanNonASDT->TraiteMsgCanSegCon(pObjetCanNonUSDT);
  }
}

//********************************************************************//
// CallBack de r�ception d'un message UU
//********************************************************************//
void tcCanNonASDT::CallBackInd(tObjetCanUU2* pObjetCanUU, tTrameCan2* pTrameCan, void* pParam)
{
  // On r�cup�re le pointeur de la classe qui a �t� pass� en param�tre
  tcCanNonASDT* pCanNonASDT=(tcCanNonASDT*)pParam;
  // On cherche l'objet � l'aide de l'ObjetCanReq correspondant
  U8 i=0;
  tObjetCanNonUSDT* pObjetCanNonUSDT=NULL;
  while((i<pCanNonASDT->m_lstObjetCanNonUSDT.GetSize()) && (pObjetCanNonUSDT==NULL))
  {
    pObjetCanNonUSDT=(tObjetCanNonUSDT*)pCanNonASDT->m_lstObjetCanNonUSDT.GetAt(i);
    if (&pObjetCanNonUSDT->ObjetCanUURep!=pObjetCanUU)
    {
      pObjetCanNonUSDT=NULL;
      i++;
    }
  }
  if (pObjetCanNonUSDT!=NULL)
  {
    pCanNonASDT->TraiteMsgCanSegInd(pObjetCanNonUSDT,pTrameCan);
  }
}

//********************************************************************//
// CallBack de fin de transmission US
//********************************************************************//
void tcCanNonASDT::CallBackConUS(tObjetCanUS2* pObjetCanUS, void* pParam)
{
  // On attend maintenant un acquitement
  ((tObjetCanNonUSDT*)pObjetCanUS->pParam)->MsgCanSeg.Etat=cEtatAttenteIndAK;
  ((tObjetCanNonUSDT*)pObjetCanUS->pParam)->MsgCanSeg.DateEvt=((tcCanNonASDT*)pParam)->m_pTimerCan->GetDate();
}

//********************************************************************//
// CallBack de r�ception d'un message US
//********************************************************************//
void tcCanNonASDT::CallBackIndUS(tObjetCanUS2* pObjetCanUS, tMsgCan2* pMsgCan, void* pParam)
{
  // On envoie un acquitement
  ((tcCanNonASDT*)pParam)->ReqAK((tObjetCanNonUSDT*)pObjetCanUS->pParam);
}

//********************************************************************//
// Traitement d'une r�ception AK (Acquittement)
//********************************************************************//
void tcCanNonASDT::RepAK(tObjetCanNonUSDT* pObjetCanNonUSDT)
{
  tObjetCanNonASDT* pObjetCanNonASDT=(tObjetCanNonASDT*)pObjetCanNonUSDT->pParam;
  // On signale que l'acquittement a �t� re�u, on envoi la confirmation d'envoi
  pObjetCanNonUSDT->MsgCanSeg.Etat=cEtatAttenteInd;
#ifndef DISABLE_SAD
  tcCanASDT::m_SADDoubleAdrFrame.SADDoubleAdrFrameTraceTx(pObjetCanNonASDT->pObjetCanAS->IdReq,pObjetCanNonASDT->pObjetCanAS->IdRep,pObjetCanNonUSDT->MsgCanSeg.MsgCan.Longueur,pObjetCanNonUSDT->MsgCanSeg.MsgCan.Buffer);
#endif  
  if (pObjetCanNonASDT->pObjetCanAS->FCallBackCon!=NULL) // On appelle la CallBack
  {
    pObjetCanNonASDT->pObjetCanAS->FCallBackCon(pObjetCanNonASDT->pObjetCanAS,pObjetCanNonASDT->pObjetCanAS->ParamCallBackCon);
  }
}

//********************************************************************//
// Traitement d'une �mission AK (Acquittement) 
//********************************************************************//
void tcCanNonASDT::ReqAK(tObjetCanNonUSDT* pObjetCanNonUSDT)
{
  // On simplifie l'�criture pour le message segment� ----
  tMsgCanSeg* pMsgCanSeg=&pObjetCanNonUSDT->MsgCanSeg;

  // On envoie la trame AK
  tTrameCan2 TrameCan;
  TrameCan.Longueur=cLongueurMaxTrameCan;
  memset(TrameCan.Buffer,cPciOctetDeRemplissage,cLongueurMaxTrameCan);
  TrameCan.Buffer[cPciPosCde]=cPciAK;
  pMsgCanSeg->Etat=cEtatAttenteConAK;                           // On passe en attente de confirmation d'envoi
  pMsgCanSeg->DateEvt=m_pTimerCan->GetDate();                   // On m�morise le dernier �v�nement
  m_pCanUUDT->Req(&pObjetCanNonUSDT->ObjetCanUUReq,&TrameCan);  // On envoi
}

//********************************************************************//
// CallBack timer g�rant les �missions de trames et les TimeOut
//********************************************************************//
void tcCanNonASDT::CallBackTempoPeriodique(void* Param)
{
  ((tcCanNonASDT*)Param)->TraiteTempoPeriodique();
}

//********************************************************************//
// Gere les erreurs suivants le type, on v�rifie si il y a l'acquittement comme erreur
//********************************************************************//
void tcCanNonASDT::GereErreurUSDT(tErreurUSDT TypeErreur,tObjetCanNonUSDT* pObjetCanNonUSDT,tTrameCan2* pTrameCan)
{
  U32       DureeTimeOut;
  tErreurUSDT   TypeErr;

  if (pObjetCanNonUSDT->pParam!=NULL)  // On a un ObjetNonASDT
  {
    tObjetCanNonASDT* pObjetCanNonASDT=(tObjetCanNonASDT*)pObjetCanNonUSDT->pParam;
    switch(TypeErreur)
    {
    case cErrEtatCon: // On regarde si on a re�u la confirmation d'envoi de l'acquittement
                      if (pObjetCanNonUSDT->MsgCanSeg.Etat==cEtatAttenteConAK)
                      {
                        pObjetCanNonUSDT->MsgCanSeg.Etat=cEtatAttenteInd;
#ifndef DISABLE_SAD
                        tcCanASDT::m_SADDoubleAdrFrame.SADDoubleAdrFrameTraceRx(pObjetCanNonUSDT->pObjetCanUS->IdReq,pObjetCanNonUSDT->pObjetCanUS->IdRep,pObjetCanNonUSDT->MsgCanSeg.MsgCan.Longueur,pObjetCanNonUSDT->MsgCanSeg.MsgCan.Buffer);
#endif  
                        if (pObjetCanNonASDT->pObjetCanAS->FCallBackInd!=NULL) // On appelle la CallBack
                        {
                          pObjetCanNonASDT->pObjetCanAS->FCallBackInd(
                              pObjetCanNonASDT->pObjetCanAS,
                              &pObjetCanNonUSDT->MsgCanSeg.MsgCan,
                              pObjetCanNonASDT->pObjetCanAS->ParamCallBackInd
                                                                     );
                        }
                      }
                      else
                      {
                        tcCanNonUSDT::GereErreurUSDT(TypeErreur,pObjetCanNonUSDT,pTrameCan);
                      }
                      break;
    case cErrEtatInd: // On regarde si on est en etat d'attente d'un ack
                      ASSERT(pTrameCan!=NULL);
                      if (pObjetCanNonUSDT->MsgCanSeg.Etat==cEtatAttenteIndAK)
                      {
                        if (pTrameCan->Buffer[cPciPosCde]==cPciAK)
                        {
                          RepAK(pObjetCanNonUSDT);
                        }
                        else
                        {
                          tcCanNonUSDT::GereErreurUSDT(cErrPci,pObjetCanNonUSDT,pTrameCan);
                        }
                      }
                      else
                      {
                        tcCanNonUSDT::GereErreurUSDT(TypeErreur,pObjetCanNonUSDT,pTrameCan);
                      }
                      break;
    case cErrEtatTimeOut:     // Un etat n'a pas �t� connu � la gestion du timeOut
                      switch(pObjetCanNonUSDT->MsgCanSeg.Etat)
                      {
                      case cEtatAttenteConAK:   // Attente de confirmation d'envoi UUDT
                                                DureeTimeOut = cPciTimeOutN_Ar;
                                                TypeErr      = cErrTimeOutRep;
                                                break;
                      case cEtatAttenteIndAK:   // TimeOut de r�ponse des AK
                                                DureeTimeOut = cPciTimeOutN_Bs;
                                                TypeErr      = cErrTimeOutReq;
                                                break;
                      default:                  // Etat inconnu
                                                DureeTimeOut = 0;
                                                TypeErr      = cErrEtatTimeOut;
                                                break;
                      }
                      if (m_pTimerCan->DateDepassee(pObjetCanNonUSDT->MsgCanSeg.DateEvt+DureeTimeOut))
                      {
                        tcCanNonUSDT::GereErreurUSDT(TypeErr,pObjetCanNonUSDT);
                      }
                      break;
    default:          // On g�re l'erreur dans la USDT
                      tcCanNonUSDT::GereErreurUSDT(TypeErreur,pObjetCanNonUSDT,pTrameCan);
    }
  }
  else    // Pas d'objet NonASDT, on redescend dans la USDT
  {
    tcCanNonUSDT::GereErreurUSDT(TypeErreur,pObjetCanNonUSDT,pTrameCan);
  }
}

#endif    // Le canal can est utilis�