// tcCanNonUSDT.cpp: implementation of the tcCanNonUSDT class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Config.h"
#ifdef CANAL_CAN      // Le canal can est utilisé

#include "tcCanNonUSDT.h"
#include "LDBPCTim.h"	// Definit l'interface du Module Timer

#ifdef CAN_REPRISE_SUR_ERREUR
#pragma message( "tcCanNonUSDT> Retry strategy enable") 
#else
#pragma message( "tcCanNonUSDT> Retry strategy disable") 
#endif

//----------- Standard definition ------------------------------------
#ifdef CAN_MODE_PSA
  #define CAN_NO_PADDING      // No padding byte
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tcCanNonUSDT::tcCanNonUSDT(tcTimerCan* pTimerCan,tcCanUUDT* pCanUUDT)
{
  ASSERT(pCanUUDT!=NULL);
  m_pCanUUDT=pCanUUDT;
  ASSERT(pTimerCan!=NULL);
  m_pTimerCan=pTimerCan;

  //---- On initialise le timer périodique ----
  m_NumeroTempo=m_pTimerCan->InsererTempoPeriodique(cPasEmissionDecalleNonUSDT,&CallBackTempoPeriodique,this);
  if (m_NumeroTempo==cNumeroTempoInvalide)
  {
		SetErreur("tcCanNonUSDT::CreerObjet> Creation error on the shifted sending timer");
  }
  pCanUUDT->SetCallBackErr(CallBackErr,this);

  m_PciFC_BS      = cPciFC_BS;
  m_PciFC_STmin   = cPciFC_STmin;
  m_PciFC_FS      = cPciFC_FS;
  m_PciFC_WFTmax  = cPciFC_WFTmax;

  m_CanNoPadding = cFalse;

#ifndef DISABLE_SAD
  tcCanNonUSDT::m_SADObjectNumber = 0;
#endif
}

tcCanNonUSDT::~tcCanNonUSDT()
{
  // On détruit tout les ObjetCanUU crée
  tObjetCanNonUSDT* pObjetCanNonUSDT;
  while(m_lstObjetCanNonUSDT.GetSize()>0)
  {
    pObjetCanNonUSDT=(tObjetCanNonUSDT*)m_lstObjetCanNonUSDT.GetAt(0);
    m_pCanUUDT->DetruireObjet(&pObjetCanNonUSDT->ObjetCanUURep);
    m_pCanUUDT->DetruireObjet(&pObjetCanNonUSDT->ObjetCanUUReq);
    m_lstObjetCanNonUSDT.RemoveAt(0);
    delete pObjetCanNonUSDT;
  }

  // On arrête le timer pour l'émission périodique
  if (m_NumeroTempo!=cNumeroTempoInvalide)   
  {
    m_pTimerCan->EnleverTempoPeriodique(m_NumeroTempo);
  }

  delete m_pCanUUDT;
}

//********************************************************************//
// CallBack d'erreur de la UUDT, on fait suivre l'erreur
//********************************************************************//
void tcCanNonUSDT::CallBackErr(void* pParam)
{
  tcCanNonUSDT* pCanNonUSDT=(tcCanNonUSDT*)pParam;
  pCanNonUSDT->SetErreur(pCanNonUSDT->m_pCanUUDT->GetErreur());
}

//********************************************************************//
// On crée un objet CAN USDT
//********************************************************************//
BOOL tcCanNonUSDT::CreerObjet(tObjetCanUS2* pObjetCan)
{
  // On initialise les objetCanUU
  tObjetCanNonUSDT* pObjetCanNonUSDT=new tObjetCanNonUSDT;
  
  pObjetCanNonUSDT->ObjetCanUURep.Id=pObjetCan->IdRep;
  pObjetCanNonUSDT->ObjetCanUURep.ModeId=pObjetCan->ModeId;
  pObjetCanNonUSDT->ObjetCanUURep.Periode=0;
  pObjetCanNonUSDT->ObjetCanUURep.TypeDeCommunication=cTypeComUUReception;
  pObjetCanNonUSDT->ObjetCanUURep.FCallBackCon=NULL;
  pObjetCanNonUSDT->ObjetCanUURep.FCallBackInd=CallBackInd;
  pObjetCanNonUSDT->ObjetCanUURep.ParamCallBackInd=this;

  pObjetCanNonUSDT->ObjetCanUUReq.Id=pObjetCan->IdReq;
  pObjetCanNonUSDT->ObjetCanUUReq.ModeId=pObjetCan->ModeId;
  pObjetCanNonUSDT->ObjetCanUUReq.Periode=0;
  pObjetCanNonUSDT->ObjetCanUUReq.TypeDeCommunication=cTypeComUUTransmission;
  pObjetCanNonUSDT->ObjetCanUUReq.FCallBackCon=CallBackCon;
  pObjetCanNonUSDT->ObjetCanUUReq.ParamCallBackCon=this;
  pObjetCanNonUSDT->ObjetCanUUReq.FCallBackInd=NULL;

  pObjetCanNonUSDT->MsgCanSeg.MsgCan.Buffer=pObjetCanNonUSDT->MsgCanSegBuffer;
  pObjetCanNonUSDT->MsgCanSeg.Etat=cEtatAttenteInd;
  pObjetCanNonUSDT->DateEnvoi=0;
  pObjetCanNonUSDT->DateProchainEnvoi=0;
  pObjetCanNonUSDT->pObjetCanUS=pObjetCan;

  pObjetCanNonUSDT->pParam=NULL;

  if (CreerObjet(pObjetCanNonUSDT))
  {
#ifndef DISABLE_SAD
    if ((pObjetCan->pParam == NULL)  // Indicate that it is an USDT object only
      &&(tcCanNonUSDT::m_SADObjectNumber++ == 0))
    {
      m_SADName = m_pCanUUDT->SADGetName();
      char Name[cSADMaxNameLength];
      sprintf(Name,"CanUS%s",m_SADName);
      m_SADDoubleAdrFrame.SADConnect(Name);
    }
#endif
    pObjetCan->pParam = pObjetCanNonUSDT;
    return cTrue;
  }
  else
  {
    delete pObjetCanNonUSDT;
    return cFalse;
  }
}

//********************************************************************//
// On crée un objet CAN NON USDT
//********************************************************************//
BOOL tcCanNonUSDT::CreerObjet(tObjetCanNonUSDT* pObjetCanNonUSDT)
{
  // On crée les objetCanUU
  if (!m_pCanUUDT->CreerObjet(&pObjetCanNonUSDT->ObjetCanUUReq))
  {
    SetErreur(m_pCanUUDT->GetErreur());
    return cFalse;
  }
  if (!m_pCanUUDT->CreerObjet(&pObjetCanNonUSDT->ObjetCanUURep))
  {
    m_pCanUUDT->DetruireObjet(&pObjetCanNonUSDT->ObjetCanUUReq);
    SetErreur(m_pCanUUDT->GetErreur());
    return cFalse;
  }
  m_Mutex.Lock();     // On vérouille l'accés à la liste au cas ou un des éléments serait utilisé par le thread
  m_lstObjetCanNonUSDT.Add(pObjetCanNonUSDT);
  m_Mutex.Unlock();   // On rend l'accés à la liste
  return cTrue;
}
//********************************************************************//
// On détruit un objet CAN USDT
//********************************************************************//
BOOL tcCanNonUSDT::DetruireObjet(tObjetCanUS2* pObjetCan)
{
  // On cherche l'objet à l'aide de l'ObjetCan correspondant
  U8 i=0;
  tObjetCanNonUSDT* pObjetCanNonUSDT=NULL;
  while((i<m_lstObjetCanNonUSDT.GetSize()) && (pObjetCanNonUSDT==NULL))
  {
    pObjetCanNonUSDT=(tObjetCanNonUSDT*)m_lstObjetCanNonUSDT.GetAt(i);
    if (pObjetCanNonUSDT->pObjetCanUS!=pObjetCan)
    {
      pObjetCanNonUSDT=NULL;
      i++;
    }
  }
  if (pObjetCanNonUSDT!=NULL)
  {
#ifndef DISABLE_SAD
    if ((pObjetCanNonUSDT->pParam == NULL)  // Indicate that it is an USDT object only
      &&(--tcCanNonUSDT::m_SADObjectNumber == 0))
    {
      m_SADDoubleAdrFrame.SADDeconnect();
    }
#endif
    m_Mutex.Lock();     // On vérouille l'accés à la liste au cas ou un des éléments serait utilisé par le thread
    m_pCanUUDT->DetruireObjet(&pObjetCanNonUSDT->ObjetCanUURep);
    m_pCanUUDT->DetruireObjet(&pObjetCanNonUSDT->ObjetCanUUReq);
    m_lstObjetCanNonUSDT.RemoveAt(i);
    delete pObjetCanNonUSDT;
    m_Mutex.Unlock();   // On rend l'accés à la liste
    return cTrue;
  }
  else
  {
    SetErreur("tcCanNonUSDT::DetruireObjet> CAN Object don't created");
    return cFalse;
  }
}

//********************************************************************//
// Emission d'un message
//********************************************************************//
BOOL tcCanNonUSDT::Req(tObjetCanUS2* pObjetCan,tMsgCan2* pMsg)
{
  // On cherche la correspondance
  U8 i=0;
  tObjetCanNonUSDT* pObjetCanNonUSDT=(tObjetCanNonUSDT*)pObjetCan->pParam;
  if (pObjetCanNonUSDT->MsgCanSeg.Etat==cEtatAttenteInd)
  {
    pObjetCanNonUSDT->MsgCanSeg.MsgCan.Longueur=pMsg->Longueur;
    memcpy(pObjetCanNonUSDT->MsgCanSeg.MsgCan.Buffer,pMsg->Buffer,pMsg->Longueur);
#ifdef CAN_REPRISE_SUR_ERREUR       // Si reprise sur erreur activé, on l'active
    pObjetCanNonUSDT->MsgCanSeg.NB_Reemission=0;   // On initialise la reprise sur erreur à 0
#endif
    Req(pObjetCanNonUSDT);
    return cTrue;
  }
  else
  {
    SetErreur("tcCanNonUSDT::Req> there is already one request in progress");
    return cFalse;
  }
}

//********************************************************************//
// CallBack de fin de transmission
//********************************************************************//
void tcCanNonUSDT::CallBackCon(tObjetCanUU2* pObjetCanUU, void* pParam)
{
  // On récupère le pointeur de la classe qui a été passé en paramêtre
  tcCanNonUSDT* pCanNonUSDT=(tcCanNonUSDT*)pParam;
  // On cherche l'objet à l'aide de l'ObjetCanReq correspondant
  U8 i=0;
  tObjetCanNonUSDT* pObjetCanNonUSDT=NULL;
  while((i<pCanNonUSDT->m_lstObjetCanNonUSDT.GetSize()) && (pObjetCanNonUSDT==NULL))
  {
    pObjetCanNonUSDT=(tObjetCanNonUSDT*)pCanNonUSDT->m_lstObjetCanNonUSDT.GetAt(i);
    if (&pObjetCanNonUSDT->ObjetCanUUReq!=pObjetCanUU)
    {
      pObjetCanNonUSDT=NULL;
      i++;
    }
  }
  if (pObjetCanNonUSDT!=NULL)
  {
    pCanNonUSDT->TraiteMsgCanSegCon(pObjetCanNonUSDT);
  }
}

//********************************************************************//
// CallBack de réception
//********************************************************************//
void tcCanNonUSDT::CallBackInd(tObjetCanUU2* pObjetCanUU, tTrameCan2* pTrameCan, void* pParam)
{
  // On récupère le pointeur de la classe qui a été passé en paramêtre
  tcCanNonUSDT* pCanNonUSDT=(tcCanNonUSDT*)pParam;
  // On cherche l'objet à l'aide de l'ObjetCanReq correspondant
  U8 i=0;
  tObjetCanNonUSDT* pObjetCanNonUSDT=NULL;
  while((i<pCanNonUSDT->m_lstObjetCanNonUSDT.GetSize()) && (pObjetCanNonUSDT==NULL))
  {
    pObjetCanNonUSDT=(tObjetCanNonUSDT*)pCanNonUSDT->m_lstObjetCanNonUSDT.GetAt(i);
    if (&pObjetCanNonUSDT->ObjetCanUURep!=pObjetCanUU)
    {
      pObjetCanNonUSDT=NULL;
      i++;
    }
  }
  if (pObjetCanNonUSDT!=NULL)
  {
    pCanNonUSDT->TraiteMsgCanSegInd(pObjetCanNonUSDT,pTrameCan);
  }
}

//********************************************************************//
// Traite le message segmenté
//********************************************************************//
void tcCanNonUSDT::TraiteMsgCanSegCon(tObjetCanNonUSDT* pObjetCanNonUSDT)
{
 #ifndef DISABLE_SAD
  tDelay Time;
  Timer.LireDate(&Time);
#endif  
 pObjetCanNonUSDT->MsgCanSeg.DateEvt=m_pTimerCan->GetDate(); // On mémorise la date du dernier évènement

  switch(pObjetCanNonUSDT->MsgCanSeg.Etat)
  {
  //********** On est en transmission de SF **********
  case cEtatAttenteConSF:
    pObjetCanNonUSDT->MsgCanSeg.Etat=cEtatAttenteInd;
#ifndef DISABLE_SAD
    m_SADDoubleAdrFrame.SADDoubleAdrFrameTraceTx(pObjetCanNonUSDT->pObjetCanUS->IdReq,pObjetCanNonUSDT->pObjetCanUS->IdRep,pObjetCanNonUSDT->MsgCanSeg.MsgCan.Longueur,pObjetCanNonUSDT->MsgCanSeg.MsgCan.Buffer,(tU32Bit)(Time/100000UL));
#endif  
    if (pObjetCanNonUSDT->pObjetCanUS->FCallBackCon!=NULL)    // Msg reçu...
    {
      pObjetCanNonUSDT->pObjetCanUS->FCallBackCon(pObjetCanNonUSDT->pObjetCanUS,pObjetCanNonUSDT->pObjetCanUS->ParamCallBackCon);
    }
    break;
  //********** On est en transmission de FF **********
  case cEtatAttenteConFF:
    pObjetCanNonUSDT->MsgCanSeg.Etat=cEtatAttenteIndFC;       // On attend maintenant le FC
    break;
  //********** On est en transmission de FC **********
  case cEtatAttenteConFC:
    if (pObjetCanNonUSDT->MsgCanSeg.FC_FS==cPciFC_FS_WT)      // On regarde si on a toujours le droit d'en envoyer
    {
      pObjetCanNonUSDT->MsgCanSeg.Etat=cEtatAttenteEnvoiFC;   // On envoi le FC_WT périodiquement
    }
    else
    {
      pObjetCanNonUSDT->MsgCanSeg.Etat=cEtatAttenteIndCF;     // On attend les CF
    }
    break;
  //********** On est en transmission de CF **********
  case cEtatAttenteConCF:
      pObjetCanNonUSDT->MsgCanSeg.Etat=cEtatAttenteEnvoiCF;   // On passe en envoi de CF différé
    break;
  //********** On est en transmission de CF pour un FC **********
  case cEtatAttenteConCFPourFC:
    pObjetCanNonUSDT->MsgCanSeg.Etat=cEtatAttenteIndFC;       // On attend maintenant le FC
    break;
  //********** On est en transmission de CF pour finir **********
  case cEtatAttenteConDerniereCF:
    pObjetCanNonUSDT->MsgCanSeg.Etat=cEtatAttenteInd;
#ifndef DISABLE_SAD
    m_SADDoubleAdrFrame.SADDoubleAdrFrameTraceTx(pObjetCanNonUSDT->pObjetCanUS->IdReq,pObjetCanNonUSDT->pObjetCanUS->IdRep,pObjetCanNonUSDT->MsgCanSeg.MsgCan.Longueur,pObjetCanNonUSDT->MsgCanSeg.MsgCan.Buffer,(tU32Bit)(Time/100000UL));
#endif  
    if (pObjetCanNonUSDT->pObjetCanUS->FCallBackCon!=NULL)    // Msg reçu...
    {
      pObjetCanNonUSDT->pObjetCanUS->FCallBackCon(pObjetCanNonUSDT->pObjetCanUS,pObjetCanNonUSDT->pObjetCanUS->ParamCallBackCon);
    }
    break;
  //********** Etat inconnu *******
  default:
    GereErreurUSDT(cErrEtatCon,pObjetCanNonUSDT);
    break;
  }
}

//********************************************************************//
// Traite le message segmenté
//********************************************************************//
void tcCanNonUSDT::TraiteMsgCanSegInd(tObjetCanNonUSDT* pObjetCanNonUSDT,tTrameCan2* pTrameCan)
{
  ASSERT(pTrameCan!=NULL);

  pObjetCanNonUSDT->MsgCanSeg.DateEvt=m_pTimerCan->GetDate(); // On mémorise la date du dernier évènement

  switch(pObjetCanNonUSDT->MsgCanSeg.Etat)
  {
  //********** On est en attente de message **********
  case cEtatAttenteInd:
    switch(pTrameCan->Buffer[cPciPosCde]&cPciMskCde)      // On identifie la commande du PCI
    {
    case cPciSF:        // C'est une SingleFrame
      RepSF(pObjetCanNonUSDT,pTrameCan);
      break;
    case cPciFF:        // C'est une first frame
      RepFF(pObjetCanNonUSDT,pTrameCan);
      break;
    default:            // PCI non attendu
      GereErreurUSDT(cErrPci,pObjetCanNonUSDT,pTrameCan);
      break;
    }
    break;
  //********** On est en attente de FC, on regarde le PCI **********
  case cEtatAttenteIndFC:
    if ((pTrameCan->Buffer[cPciPosCde]&cPciMskCde)==cPciFC)
    {
      RepFC(pObjetCanNonUSDT,pTrameCan);
    }
    else                // PCI non attendu
    {
      GereErreurUSDT(cErrPci,pObjetCanNonUSDT,pTrameCan);
      //Re init state
      pObjetCanNonUSDT->MsgCanSeg.Etat = cEtatAttenteInd;
    }
    break;
  //********** On est en attente de CF, on regarde le PCI **********
  case cEtatAttenteIndCF:
    if ((pTrameCan->Buffer[cPciPosCde]&cPciMskCde)==cPciCF)
    {
      RepCF(pObjetCanNonUSDT,pTrameCan);
    }
    else    // Trame inattendu, erreur???
    {
        switch(pTrameCan->Buffer[cPciPosCde]&cPciMskCde)      // On identifie la commande du PCI
        {
            //maybe PSA MSDT re send: treat the new frame
            case cPciSF:        // C'est une SingleFrame
              RepSF(pObjetCanNonUSDT,pTrameCan);
              break;
            case cPciFF:        // C'est une first frame
              RepFF(pObjetCanNonUSDT,pTrameCan);
              break;
            default:            // PCI non attendu
              //Re init state
              pObjetCanNonUSDT->MsgCanSeg.Etat = cEtatAttenteInd;
              GereErreurUSDT(cErrPci,pObjetCanNonUSDT,pTrameCan);
              break;
        }
    }
    break;
  //********** Etat inconnu *******
  default:
    GereErreurUSDT(cErrEtatInd,pObjetCanNonUSDT,pTrameCan);
    break;
  }
}

//********************************************************************//
// Traitement d'une réception SF (Single Frame)
//********************************************************************//
void tcCanNonUSDT::RepSF(tObjetCanNonUSDT* pObjetCanNonUSDT,tTrameCan2* pTrameCan)
{
  // On simplifie l'écriture pour le message segmenté ----
  tMsgCanSeg* pMsgCanSeg=&pObjetCanNonUSDT->MsgCanSeg;
#ifndef DISABLE_SAD
  tDelay Time;
  Timer.LireDate(&Time);
#endif  

  // On sauvegarde le message et on le signale
  pMsgCanSeg->MsgCan.Longueur=pTrameCan->Buffer[cPciSFPosLng]&cPciSFMskLng;
  memcpy(pMsgCanSeg->MsgCan.Buffer,&pTrameCan->Buffer[cPciSFPosData],pMsgCanSeg->MsgCan.Longueur);

#ifndef DISABLE_SAD
  m_SADDoubleAdrFrame.SADDoubleAdrFrameTraceRx(pObjetCanNonUSDT->pObjetCanUS->IdRep,pObjetCanNonUSDT->pObjetCanUS->IdReq,pMsgCanSeg->MsgCan.Longueur,pMsgCanSeg->MsgCan.Buffer,(tU32Bit)(Time/100000UL));
#endif  
  if (pObjetCanNonUSDT->pObjetCanUS->FCallBackInd!=NULL) // On appelle la CallBack
  {
    pObjetCanNonUSDT->pObjetCanUS->FCallBackInd(pObjetCanNonUSDT->pObjetCanUS,&pMsgCanSeg->MsgCan,pObjetCanNonUSDT->pObjetCanUS->ParamCallBackInd);
  }
}

//********************************************************************//
// Traitement d'une réception FF (First Frame)
//********************************************************************//
void tcCanNonUSDT::RepFF(tObjetCanNonUSDT* pObjetCanNonUSDT,tTrameCan2* pTrameCan)
{
  // On simplifie l'écriture pour le message segmenté ----
  tMsgCanSeg* pMsgCanSeg=&pObjetCanNonUSDT->MsgCanSeg;
  // On sauvegarde le message et on envoi le FC
  pMsgCanSeg->MsgCan.Longueur=((U16)(pTrameCan->Buffer[cPciFFPosLng1]<<8)+pTrameCan->Buffer[cPciFFPosLng2])&cPciFFMskLng;
  memcpy(pMsgCanSeg->MsgCan.Buffer,&pTrameCan->Buffer[cPciFFPosData],cPciFFLngData);
  pMsgCanSeg->PosBuffer=cPciFFLngData;        // On écrira à cet endroit dans le message lors des CF
  pMsgCanSeg->FC_FS=m_PciFC_FS;               // On passe en mode CTS(prêt pour recevoir) ou Wait
  pMsgCanSeg->FC_BS=m_PciFC_BS;               // On attend des blocs de tant de données
  pMsgCanSeg->FC_STmin=m_PciFC_STmin;         // On attend tant de temps entre les CF
  pMsgCanSeg->CF_SN=1;                        // On initialise le Numéro de bloc en cours à 1
  pMsgCanSeg->FC_FS_WT=0;                     // On initialise le nombre de wait reçu à 0
  ReqFC(pObjetCanNonUSDT);                    // On envoi la requête de FC
}

//********************************************************************//
// Traitement d'une réception CF (Consecutive Frame)
//********************************************************************//
void tcCanNonUSDT::RepCF(tObjetCanNonUSDT* pObjetCanNonUSDT,tTrameCan2* pTrameCan)
{
  // On simplifie l'écriture pour le message segmenté ----
  tMsgCanSeg* pMsgCanSeg=&pObjetCanNonUSDT->MsgCanSeg;
#ifndef DISABLE_SAD
  tDelay Time;
  Timer.LireDate(&Time);
#endif  

  // On sauvegarde le message et on envoi le FC
  if ((pTrameCan->Buffer[cPciCFPosSN]&cPciCFMskSN)==(pMsgCanSeg->CF_SN&0x0F))      // C'est le bon numéro de bloc
  {
    if (pMsgCanSeg->MsgCan.Longueur>(pMsgCanSeg->PosBuffer+cPciCFLngData))  // Si trame pleine, on recopie tout
    {
      memcpy(&pMsgCanSeg->MsgCan.Buffer[pMsgCanSeg->PosBuffer],&pTrameCan->Buffer[cPciCFPosData],cPciCFLngData);
      pMsgCanSeg->PosBuffer+=cPciCFLngData;
    }
    else  // Si dernière trame, on recopie seulement les derniers octets
    {
      if (pMsgCanSeg->MsgCan.Longueur<pMsgCanSeg->PosBuffer)
      {
        pMsgCanSeg->Etat=cEtatAttenteInd;
        SetErreur("the recieved length is greater than the define lenght.");
        return; 
      }
      else
      {
        memcpy(&pMsgCanSeg->MsgCan.Buffer[pMsgCanSeg->PosBuffer],&pTrameCan->Buffer[cPciCFPosData],pMsgCanSeg->MsgCan.Longueur-pMsgCanSeg->PosBuffer);
        pMsgCanSeg->PosBuffer=pMsgCanSeg->MsgCan.Longueur;
      }
    }
    if (pMsgCanSeg->PosBuffer==pMsgCanSeg->MsgCan.Longueur) // Si fini, on transmet le message
    {
      pObjetCanNonUSDT->MsgCanSeg.Etat=cEtatAttenteInd; // On retourne en mode attente
#ifndef DISABLE_SAD
      m_SADDoubleAdrFrame.SADDoubleAdrFrameTraceRx(pObjetCanNonUSDT->pObjetCanUS->IdRep,pObjetCanNonUSDT->pObjetCanUS->IdReq,pMsgCanSeg->MsgCan.Longueur,pMsgCanSeg->MsgCan.Buffer,(tU32Bit)(Time/100000UL));
#endif  
      if (pObjetCanNonUSDT->pObjetCanUS->FCallBackInd!=NULL) // On appelle la CallBack
      {
        pObjetCanNonUSDT->pObjetCanUS->FCallBackInd(pObjetCanNonUSDT->pObjetCanUS,&pMsgCanSeg->MsgCan,pObjetCanNonUSDT->pObjetCanUS->ParamCallBackInd);
      }
    }
    else if ((pMsgCanSeg->FC_BS!=0) && !(pMsgCanSeg->CF_SN%pMsgCanSeg->FC_BS))    // Si tout les blocs ont été reçu, on emet un FC
    {
      pMsgCanSeg->CF_SN++;                              // Et un bloc de plus
      ReqFC(pObjetCanNonUSDT);                          // On envoi la requête de FC
    }
    else
    {
      pMsgCanSeg->CF_SN++;                              // Et un bloc de plus
    }
  }
  else
  {
    GereErreurUSDT(cErrBS,pObjetCanNonUSDT);
  }
}

//********************************************************************//
// Traitement d'une réception FC (Flow Control)
//********************************************************************//
void tcCanNonUSDT::RepFC(tObjetCanNonUSDT* pObjetCanNonUSDT,tTrameCan2* pTrameCan)
{
  // On simplifie l'écriture pour le message segmenté ----
  tMsgCanSeg* pMsgCanSeg=&pObjetCanNonUSDT->MsgCanSeg;
  // On traite ce control
  pMsgCanSeg->FC_FS=(pTrameCan->Buffer[cPciFCPosFS]&cPciFCMskFS); 
  pMsgCanSeg->FC_BS=pTrameCan->Buffer[cPciFCPosBS];               // On enverra des blocs de tant de données
  pMsgCanSeg->FC_STmin=pTrameCan->Buffer[cPciFCPosSTmin];         // On espacera les blocs de tant de temps
  if (pMsgCanSeg->FC_FS==cPciFC_FS_CTS)                           // Si distant prêt à recevoir
  {
    ReqCF(pObjetCanNonUSDT);                                      // On transmet la première CF
  }
}

//********************************************************************//
// Traitement d'une émission SF (Single Frame)
//********************************************************************//
void tcCanNonUSDT::ReqSF(tObjetCanNonUSDT* pObjetCanNonUSDT)
{
  // On simplifie l'écriture pour le message segmenté ----
  tMsgCanSeg* pMsgCanSeg=&pObjetCanNonUSDT->MsgCanSeg;
  // On transforme le message et on le signale
  tTrameCan2 TrameCan;
  memset(TrameCan.Buffer,cPciOctetDeRemplissage,cLongueurMaxTrameCan);
// Si Pas de directive de compile sur le NoPadding
#ifndef CAN_NO_PADDING
	// Traitement de la config de NoPadding "dynamique"
	if(m_CanNoPadding)
	{
		TrameCan.Longueur = pMsgCanSeg->MsgCan.Longueur + 1;  // Length of PCI
	}
	else
	{
		TrameCan.Longueur = cLongueurMaxTrameCan;
	}
#else
  TrameCan.Longueur = pMsgCanSeg->MsgCan.Longueur + 1;  // Length of PCI
#endif

  memcpy(&TrameCan.Buffer[cPciSFPosData],pMsgCanSeg->MsgCan.Buffer,pMsgCanSeg->MsgCan.Longueur);
  TrameCan.Buffer[cPciPosCde]=cPciSF|pMsgCanSeg->MsgCan.Longueur;
  pMsgCanSeg->Etat=cEtatAttenteConSF;                           // On passe en attente de confirmation d'envoi
  pMsgCanSeg->DateEvt=m_pTimerCan->GetDate();                   // On mémorise le dernier évènement
  m_pCanUUDT->Req(&pObjetCanNonUSDT->ObjetCanUUReq,&TrameCan);  // On envoi
}

//********************************************************************//
// Traitement d'une émission FF (First Frame)
//********************************************************************//
void tcCanNonUSDT::ReqFF(tObjetCanNonUSDT* pObjetCanNonUSDT)
{
  // On simplifie l'écriture pour le message segmenté ----
  tMsgCanSeg* pMsgCanSeg=&pObjetCanNonUSDT->MsgCanSeg;
  // On transforme le message et on le signale
  tTrameCan2 TrameCan;
  memset(TrameCan.Buffer,cPciOctetDeRemplissage,cLongueurMaxTrameCan);
  TrameCan.Longueur=cLongueurMaxTrameCan;
  memcpy(&TrameCan.Buffer[cPciFFPosData],pMsgCanSeg->MsgCan.Buffer,cPciFFLngData);
  pMsgCanSeg->PosBuffer=6;
  TrameCan.Buffer[cPciPosCde]=cPciFF|(pMsgCanSeg->MsgCan.Longueur>>8);
  TrameCan.Buffer[cPciFFPosLng2]=pMsgCanSeg->MsgCan.Longueur&0xFF;
  pMsgCanSeg->CF_SN=1;                                          // On initialise le Numéro de bloc à envoyer à 1
  pMsgCanSeg->Etat=cEtatAttenteConFF;                          // On passe en attente de confirmation d'envoi
  pMsgCanSeg->DateEvt=m_pTimerCan->GetDate();
  m_pCanUUDT->Req(&pObjetCanNonUSDT->ObjetCanUUReq,&TrameCan);  // On envoi
}

//********************************************************************//
// Traitement d'une émission CF (Consecutive Frame)
//********************************************************************//
void tcCanNonUSDT::ReqCF(tObjetCanNonUSDT* pObjetCanNonUSDT)
{
  // On simplifie l'écriture pour le message segmenté ----
  tMsgCanSeg* pMsgCanSeg=&pObjetCanNonUSDT->MsgCanSeg;
  // On transforme le message et on le signale
  tTrameCan2 TrameCan;
  memset(TrameCan.Buffer,cPciOctetDeRemplissage,cLongueurMaxTrameCan);
  TrameCan.Longueur = cLongueurMaxTrameCan;
  if (pMsgCanSeg->MsgCan.Longueur>pMsgCanSeg->PosBuffer+cPciCFLngData)
  {
    memcpy(&TrameCan.Buffer[cPciCFPosData],&pMsgCanSeg->MsgCan.Buffer[pMsgCanSeg->PosBuffer],cPciCFLngData);
    pMsgCanSeg->PosBuffer+=cPciCFLngData;
  }
  else
  {
// Si Pas de directive de compile sur le NoPadding
#ifndef CAN_NO_PADDING
	// Traitement de la config de NoPadding "dynamique"
	if(m_CanNoPadding)
	{
		TrameCan.Longueur = pMsgCanSeg->MsgCan.Longueur-pMsgCanSeg->PosBuffer + 1;
	}
#else
    TrameCan.Longueur = pMsgCanSeg->MsgCan.Longueur-pMsgCanSeg->PosBuffer + 1;
#endif
    memcpy(&TrameCan.Buffer[cPciCFPosData],&pMsgCanSeg->MsgCan.Buffer[pMsgCanSeg->PosBuffer],pMsgCanSeg->MsgCan.Longueur-pMsgCanSeg->PosBuffer);
    pMsgCanSeg->PosBuffer=pMsgCanSeg->MsgCan.Longueur;
  }
  if (pMsgCanSeg->PosBuffer==pMsgCanSeg->MsgCan.Longueur)      // Si fini
  {
    pMsgCanSeg->Etat=cEtatAttenteConDerniereCF;                // On passe en attente de confirmation du dernier envoi
  }
  else if ((pMsgCanSeg->FC_BS!=0) && !(pMsgCanSeg->CF_SN%pMsgCanSeg->FC_BS))             // Si nombre max de bloc atteint
  {
    pMsgCanSeg->FC_FS_WT=0;                                    // On initialise le nombre de wait reçu à 0 pour le prochain envoi de FC
    pMsgCanSeg->Etat=cEtatAttenteConCFPourFC;                  // On passe en attente de confirmation du dernier envoi avant un FC
  }
  else
  {
    pMsgCanSeg->Etat=cEtatAttenteConCF;                        // On passe en attente de la confirmation d'envoi
  }
  TrameCan.Buffer[cPciPosCde]=cPciCF|((pMsgCanSeg->CF_SN++)&0x0F);  // On incrémente le prochain numéro de bloc
  pMsgCanSeg->DateEvt=m_pTimerCan->GetDate();
  m_pCanUUDT->Req(&pObjetCanNonUSDT->ObjetCanUUReq,&TrameCan);      // On envoi
}

//********************************************************************//
// Traitement d'une émission FC (Flow Control)
//********************************************************************//
void tcCanNonUSDT::ReqFC(tObjetCanNonUSDT* pObjetCanNonUSDT)
{
  // On simplifie l'écriture pour le message segmenté ----
  tMsgCanSeg* pMsgCanSeg=&pObjetCanNonUSDT->MsgCanSeg;
  // Si CTS ou que FC_FS_WT < FC_WFTmax, alors on envoi
  if ((pMsgCanSeg->FC_FS==cPciFC_FS_CTS) || (pObjetCanNonUSDT->MsgCanSeg.FC_FS_WT++)<m_PciFC_WFTmax)
  {
    // On transforme le message et on le signale
    tTrameCan2 TrameCan;
    memset(TrameCan.Buffer,cPciOctetDeRemplissage,cLongueurMaxTrameCan);
// Si Pas de directive de compile sur le NoPadding
#ifndef CAN_NO_PADDING
	// Traitement de la config de NoPadding "dynamique"
	if(m_CanNoPadding)
	{
		TrameCan.Longueur = 3;  // Length of FC
	}
	else
	{
		TrameCan.Longueur = cLongueurMaxTrameCan;
	}
#else
  TrameCan.Longueur = 3;  // Length of FC
#endif

    pMsgCanSeg->FC_FS=m_PciFC_FS;               // On passe en mode CTS(prêt pour recevoir) ou Wait
    TrameCan.Buffer[cPciPosCde]=cPciFC|(pMsgCanSeg->FC_FS);
    TrameCan.Buffer[cPciFCPosBS]=pMsgCanSeg->FC_BS;
    TrameCan.Buffer[cPciFCPosSTmin]=pMsgCanSeg->FC_STmin;
    pMsgCanSeg->Etat=cEtatAttenteConFC;                          // On passe en attente de confirmation d'envoi
    pMsgCanSeg->DateEvt=m_pTimerCan->GetDate();
    m_pCanUUDT->Req(&pObjetCanNonUSDT->ObjetCanUUReq,&TrameCan);  // On envoi
  }
  else
  {
    GereErreurUSDT(cErrWFTmax,pObjetCanNonUSDT);
  }
}

//********************************************************************//
// CallBack timer gérant les émissions de trames et les TimeOut
//********************************************************************//
void tcCanNonUSDT::CallBackTempoPeriodique(void* Param)
{
  ((tcCanNonUSDT*)Param)->TraiteTempoPeriodique();
}

//********************************************************************//
// Timer gérant les émissions et les TimeOut
//********************************************************************//
void tcCanNonUSDT::TraiteTempoPeriodique()
{
  //---- On boucle pour transmettre les messages j'usqu'à l'arrêt ou regarder les TimeOut ----
  tObjetCanNonUSDT* pObjetCanNonUSDT;
  U8  NumObjetCan;
  U32 DureeTimeOut;
  tErreurUSDT TypeErr;

  if (m_Mutex.Lock(50))    // On se réserve la liste pour être sur qu'elle ne sera pas enlevée pendant le traitement
  {
	  NumObjetCan=0;
    while (NumObjetCan < m_lstObjetCanNonUSDT.GetSize())		// On parcourt la liste
    {
      pObjetCanNonUSDT=(tObjetCanNonUSDT*)m_lstObjetCanNonUSDT.GetAt(NumObjetCan++);
      switch(pObjetCanNonUSDT->MsgCanSeg.Etat)
      {
      case cEtatAttenteInd:       // Rien a faire, on est en mode d'attente
                      break;
      case cEtatAttenteEnvoiCF:   // On doit envoyer des CF en respectant STmin
                      if (m_pTimerCan->DateDepassee(pObjetCanNonUSDT->MsgCanSeg.DateEvt+pObjetCanNonUSDT->MsgCanSeg.FC_STmin))
                      {
                        ReqCF(pObjetCanNonUSDT); // On envoi la trame CF
                      }
                      break;
      case cEtatAttenteEnvoiFC:   // On doit envoyer des FC wait espacé d'un temps inférieur à un TimeOut
                      if (m_pTimerCan->DateDepassee(pObjetCanNonUSDT->MsgCanSeg.DateEvt+cPciFC_STwait))
                      {
                        ReqFC(pObjetCanNonUSDT); // On envoi la trame FC
                      }
                      break;
      default:                    // On regarde si un TimeOut de transmission n'est pas tombé
                      switch(pObjetCanNonUSDT->MsgCanSeg.Etat)
                      {
                      case cEtatAttenteConSF:         // Attente de confirmation d'envoi UUDT
                      case cEtatAttenteConFF:         //
                      case cEtatAttenteConCF:         //
                      case cEtatAttenteConCFPourFC:   //
                      case cEtatAttenteConDerniereCF: // 
                                                      DureeTimeOut = cPciTimeOutN_As;
                                                      TypeErr      = cErrTimeOutReq;
                                                      break;
                      case cEtatAttenteIndFC:         // TimeOut de réponse des FC
                                                      DureeTimeOut = cPciTimeOutN_Bs;
                                                      TypeErr      = cErrTimeOutReq;
                                                      break;    
                      case cEtatAttenteConFC:         //  TimeOut de confirmation des FC
                                                      DureeTimeOut = cPciTimeOutN_Ar;
                                                      TypeErr      = cErrTimeOutRep;
                                                      break;
                      case cEtatAttenteIndCF:         // TimeOut de réponse des CF
                                                      DureeTimeOut = cPciTimeOutN_Cr;
                                                      TypeErr      = cErrTimeOutRep;
                                                      break;
                      default:                        // Etat inconnu
                                                      DureeTimeOut = 0;
                                                      TypeErr      = cErrEtatTimeOut;
                                                      break;
                      }
                      if (m_pTimerCan->DateDepassee(pObjetCanNonUSDT->MsgCanSeg.DateEvt+DureeTimeOut))
                      {
                        GereErreurUSDT(TypeErr,pObjetCanNonUSDT);
                      }
      }
    }
    m_Mutex.Unlock();  // On rend l'accés à la liste
  }
}

//********************************************************************//
// Emission d'un message en mémoire
//********************************************************************//
void tcCanNonUSDT::Req(tObjetCanNonUSDT* pObjetCanNonUSDT)
{
  //---- On définis l'envoi ----
  if (pObjetCanNonUSDT->MsgCanSeg.MsgCan.Longueur<=cPciSFLngData)
    ReqSF(pObjetCanNonUSDT);
  else
    ReqFF(pObjetCanNonUSDT);
}

//********************************************************************//
// Gere les erreurs suivants le type
//********************************************************************//
void tcCanNonUSDT::GereErreurUSDT(tErreurUSDT TypeErreur,tObjetCanNonUSDT* pObjetCanNonUSDT,tTrameCan2* pTrameCan)
{
  switch(TypeErreur)
  {
  case cErrBS:      // Erreur de réception, on ignore le message USDT entier
                    TRACE("tcCanNonUSDT::GereErreurUSDT> invalid block number (%02X)\n",pObjetCanNonUSDT->MsgCanSeg.CF_SN);
                    InitialiseEtats(pObjetCanNonUSDT);
                    break;
  case cErrTimeOutReq: // On ignore le message envoyé
                    TRACE("tcCanNonUSDT::GereErreurUSDT> emission timeout error\n");
                    RepriseSurErreur(pObjetCanNonUSDT);
                    break;
  case cErrTimeOutRep: // On ignore le message reçu
                    TRACE("tcCanNonUSDT::GereErreurUSDT> Received TimeOut Error\n");
                    InitialiseEtats(pObjetCanNonUSDT);
                    break;
  case cErrWFTmax:  // On fait une erreur car on a atteint le maximum de FC_FS_WT
                    TRACE("tcCanNonUSDT::GereErreurUSDT> Max number of Wait is done\n");
                    InitialiseEtats(pObjetCanNonUSDT);
                    SetErreur("tcCanNonUSDT::GereErreurUSDT> Max number of Wait is done\n");
                    break;
  case cErrPci:     // On ignore la trame reçu
                    TRACE("tcCanNonUSDT::GereErreurUSDT> Pci command unexpected (%02X)\n",pTrameCan->Buffer[cPciPosCde]);
                    break;
  case cErrEtatCon: // On ignore la trame reçu
                    TRACE("tcCanNonUSDT::GereErreurUSDT> confirmation state message undefined (%d)\n",pObjetCanNonUSDT->MsgCanSeg.Etat);
                    break;
  case cErrEtatInd: // On ignore la trame reçu
                    TRACE("tcCanNonUSDT::GereErreurUSDT> received state message undefined (%d)\n",pObjetCanNonUSDT->MsgCanSeg.Etat);
                    break;
  case cErrEtatTimeOut:  // On retourne dans l'état initiale car on a un TimeOut sur un  état indéfini
                    TRACE("tcCanNonUSDT::GereErreurUSDT> State message undefined at the timeOut test (%d)\n",pObjetCanNonUSDT->MsgCanSeg.Etat);
                    InitialiseEtats(pObjetCanNonUSDT);
                    break;
  }
}

//********************************************************************//
// Gère la reprise sur erreur
//********************************************************************//
void tcCanNonUSDT::RepriseSurErreur(tObjetCanNonUSDT* pObjetCanNonUSDT)
{
#ifdef CAN_REPRISE_SUR_ERREUR       // Si reprise sur erreur activé, On réémet le message USDT entier cReemissionMax fois maximum
  TRACE("tcCanNonUSDT::Retry on error> ...\n");
  if (pObjetCanNonUSDT->MsgCanSeg.NB_Reemission++<cReemissionMax)
  {
    Req(pObjetCanNonUSDT);
  }
  else
  {
    InitialiseEtats(pObjetCanNonUSDT);
  }
#else
  pObjetCanNonUSDT->MsgCanSeg.Etat=cEtatAttenteInd;
#endif
}

//********************************************************************//
// Initialisation de l'état d'émission/réception
//********************************************************************//
void tcCanNonUSDT::InitialiseEtats(tObjetCanNonUSDT* pObjetCanNonUSDT)
{
  pObjetCanNonUSDT->MsgCanSeg.Etat=cEtatAttenteInd;
  TRACE("tcCanNonUSDT::InitializeState> ...\n");
}

//********************************************************************//
// Cherche une carte Can UUDT
//********************************************************************//
#ifdef CAN_DETECTION_CARTE
tcCanUSDT* tcCanNonUSDT::ChercheCarteCan(tcTimerCan* pTimerCan,U32 VitesseCan,CString& InfoCarte,CString& Err, BOOL bReset)
{
  tcCanUSDT* pCanUSDT;
  tcCanUUDT* pCanUUDT;
  //---- Renvoit une carte CAN si on en a trouvé une de dispo -----
  pCanUUDT=tcCanUUDT::ChercheCarteCan(pTimerCan,VitesseCan,InfoCarte,Err,cCarteIndefini,bReset);
  if (pCanUUDT==NULL)
  {
    return NULL;
  }
  else
  {
    pCanUSDT=new tcCanNonUSDT(pTimerCan,pCanUUDT);
    Err=pCanUSDT->GetErreur();
    if (!Err.IsEmpty())
    {
      delete pCanUSDT;
      delete pCanUUDT;
      return NULL;
    }
    else
    {
      return pCanUSDT;
    }
  }
}
#endif

#endif    // Le canal can est utilisé