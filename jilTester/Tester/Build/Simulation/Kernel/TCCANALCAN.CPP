//**************************************************************************
// COMPOSANT : tcCanalCan
// FONCTION : implementation of the tcCanalCan class.
//
// Ce logiciel est la propriete de JCI :
// ---------------------------------------
// Il ne peut être reproduit ni communique en totalite ou partie sans
// son autorisation ecrite.
//
// ------------------------------------------------------------------------
// Nom et initiales des developpeurs :
//
//		Gilles	GUILLEN		GG
//		Mickael GRANDSIRE	MG
//
// ------------------------------------------------------------------------
// Historique du fichier LdbpcRdo.c:
// -------------------------------------
// (initiales, date, modification)
//
// v1.0	:	MG		: 20/04/2000	: Creation
// v1.1 :	GG & MG	: 14/03/2002	: Bug : Gestion de plusieurs messages Can
//
//***************************************************************************
#include "Config.h"
#ifdef CANAL_CAN      // Le canal can est utilisé

#include "tcCanalCan.h"
#include "tcCanECar.h"
#include "tcCanNonSession.h"

#include <afxtempl.h>

#include "LdbpcRes.h"
#include "LdbpcDon.h"
#include "LdbpcTim.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
tcCanalCan CanalCan;

tcCanalCan::tcCanalCan()
{
  m_pCanECar    = NULL;
  m_pCanSession = NULL;
  // On initialise la carte Can
  m_pCanECar    = new tcCanECar(&m_TimerCan,CallBackCanReq,this);
  m_pCanSession = new tcCanNonSession(&m_TimerCan,m_pCanECar);
  m_pCanSession->SetCallBackErr(CallBackCanErr,this);
  m_VariableUSDTInitialise=cFalse;
}

tcCanalCan::~tcCanalCan()
{
  int i;
  for( i=0; i<m_lstTramesMsg.GetSize(); i++ )
  {
    delete m_lstTramesMsg[i];
  }
  m_lstTramesMsg.RemoveAll();
  for( i=0; i<m_lstTramesMsgAck.GetSize(); i++ )
  {
    delete m_lstTramesMsgAck[i];
  }
  m_lstTramesMsgAck.RemoveAll();
  for( i=0; i<m_lstTramesMsgSession.GetSize(); i++ )
  {
    delete m_lstTramesMsgSession[i];
  }
  m_lstTramesMsgSession.RemoveAll();

  //--- On ferme la carte CAN
  if (m_pCanSession!=NULL)
    delete m_pCanSession;
}

//********************************************************************//
// Initialisation du canal Can
//********************************************************************//
void tcCanalCan::Initialisation(void)
{
	m_TimerCan.Initialiser();	// Pour reseter les tempos lors d'un reset appli

  // On initialise le timer Can
	m_TempoCan.EstPeriodique = cTrue;
	m_TempoCan.Duree         = cDureeTempoTimerCanMs*cTemMs;
	m_TempoCan.pCallBack     = &CallBackTimerCan;
	Timer.SupprimerTempo(&m_TempoCan);
	Timer.AjouterTempo(&m_TempoCan);
}

//********************************************************************//
// Callback du timer Can
//********************************************************************//
void tcCanalCan::CallBackTimerCan()
{
  tDelay Date;
  Timer.LireDate(&Date);
  CanalCan.m_TimerCan.Executer((U32)(Date/cTemMs));
}

//********************************************************************//
// Création d'un message segmenté
//********************************************************************//
BOOL tcCanalCan::CreerMsgSeg(tParamMsgSeg * ParamMsgSeg, S32 RefCan)
{
	TRACE("Creation of a segmented message %s\n", ParamMsgSeg->Nom);
  tcTrameMsgCan* pTrameMsgCan = new tcTrameMsgCan(m_pCanSession,m_pCanECar,ParamMsgSeg,RefCan);
  m_lstTramesMsg.Add(pTrameMsgCan);
  if (!m_VariableUSDTInitialise)    // Au moins un message segmenté, on crée la config des wait,BS...
  {
    m_VariableUSDTInitialise=cTrue;
	  char Grp[MAX_STRING];
    char Nom[MAX_STRING];
	  sprintf(Grp,"%s\\MessagesSeg\\%s",Ressources.GetChannelName(RefCan),ParamMsgSeg->Nom); // Groupe Canal\MessagesSeg\NomMessage
	  sprintf(Nom,"%sFC_STmin",Ressources.GetChannelName(RefCan));
	  Donnees.CreerDonnee(&m_DonneeFC_STmin,Nom,cDLLEntree,cDLLTypeVal,8,m_pCanSession->GetPciFC_STmin(),Grp,SignalerFC_STmin,this);
	  sprintf(Nom,"%sFC_BS",Ressources.GetChannelName(RefCan));
	  Donnees.CreerDonnee(&m_DonneeFC_BS,Nom,cDLLEntree,cDLLTypeVal,8,m_pCanSession->GetPciFC_BS(),Grp,SignalerFC_BS,this);
	  sprintf(Nom,"%sFC_WFTmax",Ressources.GetChannelName(RefCan));
	  Donnees.CreerDonnee(&m_DonneeFC_WFTmax,Nom,cDLLEntree,cDLLTypeVal,8,m_pCanSession->GetPciFC_WFTmax(),Grp,SignalerFC_WFTmax,this);
	  sprintf(Nom,"%sFC_FS_WAIT",Ressources.GetChannelName(RefCan));
	  Donnees.CreerDonnee(&m_DonneeFC_FS,Nom,cDLLEntree,cDLLTypeVal,8,m_pCanSession->GetPciFC_FS(),Grp,SignalerFC_FS,this);
  }
  return cTrue;
}

//********************************************************************//
// Création d'un message segmenté acquitté
//********************************************************************//
BOOL tcCanalCan::CreerMsgSegAck(tParamMsgSeg * ParamMsgSeg, S32 RefCan)
{
	TRACE("Creation of a acknowledged segmented message %s\n", ParamMsgSeg->Nom);
  tcTrameMsgCanAck* pTrameMsgCanAck = new tcTrameMsgCanAck(m_pCanSession,m_pCanECar,ParamMsgSeg,RefCan);
  m_lstTramesMsgAck.Add(pTrameMsgCanAck);
  if (!m_VariableUSDTInitialise)    // Au moins un message segmenté, on crée la config des wait,BS...
  {
    m_VariableUSDTInitialise=cTrue;
	  char Grp[MAX_STRING];
    char Nom[MAX_STRING];
	  sprintf(Grp,"%s\\MessagesSeg\\%s",Ressources.GetChannelName(RefCan),ParamMsgSeg->Nom); // Groupe Canal\MessagesSeg\NomMessage
	  sprintf(Nom,"%sFC_STmin",Ressources.GetChannelName(RefCan));
	  Donnees.CreerDonnee(&m_DonneeFC_STmin,Nom,cDLLEntree,cDLLTypeVal,8,m_pCanSession->GetPciFC_STmin(),Grp,SignalerFC_STmin,this);
	  sprintf(Nom,"%sFC_BS",Ressources.GetChannelName(RefCan));
	  Donnees.CreerDonnee(&m_DonneeFC_BS,Nom,cDLLEntree,cDLLTypeVal,8,m_pCanSession->GetPciFC_BS(),Grp,SignalerFC_BS,this);
	  sprintf(Nom,"%sFC_WFTmax",Ressources.GetChannelName(RefCan));
	  Donnees.CreerDonnee(&m_DonneeFC_WFTmax,Nom,cDLLEntree,cDLLTypeVal,8,m_pCanSession->GetPciFC_WFTmax(),Grp,SignalerFC_WFTmax,this);
	  sprintf(Nom,"%sFC_FS_WAIT",Ressources.GetChannelName(RefCan));
	  Donnees.CreerDonnee(&m_DonneeFC_FS,Nom,cDLLEntree,cDLLTypeVal,8,m_pCanSession->GetPciFC_FS(),Grp,SignalerFC_FS,this);
  }
  return cTrue;
}

//********************************************************************//
// Création d'une session de message segmenté acquitté
//********************************************************************//
BOOL tcCanalCan::CreerMsgSegSession(tParamMsgSeg * ParamMsgSeg, S32 RefCan)
{
	TRACE("Creation of a session acknowledged segmented message %s\n", ParamMsgSeg->Nom);
  tcTrameMsgCanSession* pTrameMsgCanSession = new tcTrameMsgCanSession(m_pCanSession,m_pCanECar,ParamMsgSeg,RefCan);
  m_lstTramesMsgSession.Add(pTrameMsgCanSession);
  if (!m_VariableUSDTInitialise)    // Au moins un message segmenté, on crée la config des wait,BS...
  {
    m_VariableUSDTInitialise=cTrue;
	  char Grp[MAX_STRING];
    char Nom[MAX_STRING];
	  sprintf(Grp,"%s\\MessagesSeg\\%s",Ressources.GetChannelName(RefCan),ParamMsgSeg->Nom); // Groupe Canal\MessagesSeg\NomMessage
	  sprintf(Nom,"%sFC_STmin",Ressources.GetChannelName(RefCan));
	  Donnees.CreerDonnee(&m_DonneeFC_STmin,Nom,cDLLEntree,cDLLTypeVal,8,m_pCanSession->GetPciFC_STmin(),Grp,SignalerFC_STmin,this);
	  sprintf(Nom,"%sFC_BS",Ressources.GetChannelName(RefCan));
	  Donnees.CreerDonnee(&m_DonneeFC_BS,Nom,cDLLEntree,cDLLTypeVal,8,m_pCanSession->GetPciFC_BS(),Grp,SignalerFC_BS,this);
	  sprintf(Nom,"%sFC_WFTmax",Ressources.GetChannelName(RefCan));
	  Donnees.CreerDonnee(&m_DonneeFC_WFTmax,Nom,cDLLEntree,cDLLTypeVal,8,m_pCanSession->GetPciFC_WFTmax(),Grp,SignalerFC_WFTmax,this);
	  sprintf(Nom,"%sFC_FS_WAIT",Ressources.GetChannelName(RefCan));
	  Donnees.CreerDonnee(&m_DonneeFC_FS,Nom,cDLLEntree,cDLLTypeVal,8,m_pCanSession->GetPciFC_FS(),Grp,SignalerFC_FS,this);
  }
  return cTrue;
}

//********************************************************************//
// CVallBack d'Evt de chgt de données
//********************************************************************//
void tcCanalCan::SignalerFC_STmin(void* Param1,void* Param2)
{
  tcCanalCan* pCanal = (tcCanalCan*)Param1;
  U32 Valeur;
  Donnees.Lire(pCanal->m_DonneeFC_STmin,&Valeur,NULL,NULL);
  pCanal->m_pCanSession->SetPciFC_STmin((U8)Valeur);
}

void tcCanalCan::SignalerFC_BS(void* Param1,void* Param2)
{
  tcCanalCan* pCanal = (tcCanalCan*)Param1;
  U32 Valeur;
  Donnees.Lire(pCanal->m_DonneeFC_BS,&Valeur,NULL,NULL);
  pCanal->m_pCanSession->SetPciFC_BS((U8)Valeur);
}

void tcCanalCan::SignalerFC_WFTmax(void* Param1,void* Param2)
{
  tcCanalCan* pCanal = (tcCanalCan*)Param1;
  U32 Valeur;
  Donnees.Lire(pCanal->m_DonneeFC_WFTmax,&Valeur,NULL,NULL);
  pCanal->m_pCanSession->SetPciFC_WFTmax((U8)Valeur);
}

void tcCanalCan::SignalerFC_FS(void* Param1,void* Param2)
{
  tcCanalCan* pCanal = (tcCanalCan*)Param1;
  U32 Valeur;
  Donnees.Lire(pCanal->m_DonneeFC_FS,&Valeur,NULL,NULL);
  pCanal->m_pCanSession->SetPciFC_FS((U8)Valeur);
}

//********************************************************************//
// CallBack d'émission de la tcCanEcar, il faut la renvoyer vers l'appli
//********************************************************************//
void tcCanalCan::CallBackCanReq(U32 Id,tTrameCan2* pTrameCan,void* pParam)
{
  tcCanalCan* pCanalCan=(tcCanalCan*)pParam;
  // On cherche la trameMsgCan correspondant à l'ID
  for (int i=0;i<pCanalCan->m_lstTramesMsg.GetSize();i++)
  {
    tObjetCanUS2* pObj=&pCanalCan->m_lstTramesMsg[i]->m_ObjetCanUS;
    if (pCanalCan->m_lstTramesMsg[i]->m_ObjetCanUS.IdReq==Id)
    {
      break;
    }
  }
  if (i<pCanalCan->m_lstTramesMsg.GetSize())
  {
    pCanalCan->m_lstTramesMsg[i]->ReqAppli(pTrameCan);
  }
  else  // On cherche dans les trames Ack
  {
    for (int i=0;i<pCanalCan->m_lstTramesMsgAck.GetSize();i++)
    {
      tObjetCanAS2* pObj=&pCanalCan->m_lstTramesMsgAck[i]->m_ObjetCanAS;
      if (pCanalCan->m_lstTramesMsgAck[i]->m_ObjetCanAS.IdReq==Id)
      {
        break;
      }
    }
    if (i<pCanalCan->m_lstTramesMsgAck.GetSize())
    {
      pCanalCan->m_lstTramesMsgAck[i]->ReqAppli(pTrameCan);
    }
    else  // On cherches dans les sessions de trames acquittées
    {
      for (int i=0;i<pCanalCan->m_lstTramesMsgSession.GetSize();i++)
      {
        tObjetCanSession2* pObj=&pCanalCan->m_lstTramesMsgSession[i]->m_ObjetCanSession;
        if (pCanalCan->m_lstTramesMsgSession[i]->m_ObjetCanSession.IdReq==Id)
        {
          break;
        }
      }
      if (i<pCanalCan->m_lstTramesMsgSession.GetSize())
      {
        pCanalCan->m_lstTramesMsgSession[i]->ReqAppli(pTrameCan);
      }
      else
      {
        char Texte[MAX_STRING];
        sprintf(Texte,"Reception of a not define frame by the DLL (%d)",Id);
		    mLDBPCErreur(Texte);
      }
    }
  }
}

//********************************************************************//
// CallBack d'erreur de transmission CAN
//********************************************************************//
void tcCanalCan::CallBackCanErr(void* pParam)
{
  tcCanalCan* pCanalCan=(tcCanalCan*)pParam;
  LDBPcTrace(pCanalCan->m_pCanSession->GetErreur());
//	mLDBPCErreur(pCanalCan->m_pCanSession->GetErreur());
}

#endif // CANAL_CAN