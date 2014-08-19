/*============================================================================
  Project ......................... LDBPC
  Component ....................... tcTrameMsgCanSession
  File revision.................... $Revision:   1.0  $
  Last modification date .......... $Modtime:   04 Feb 2009 16:32:32  $
  -------------------------------------------------------------------------
  Copyright ... This software is JCI property. Duplication or
                disclosure is prohibited without JCI written permission
  ------------------------------------------------------------------------- 
    
  - This file should only contain data useful to the programmer to use
    this component
  - Component exported macros, constants and types are defined in this file
  - Component exported variables and functions are declared in this file 
    with the "extern" keyword
  
  -------------------------------------------------------------------------
  tcTrameMsgCanSession.cpp file review :
  
    PVCS Historic :

    $Log:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/EXT_CMP/CPP_CMP/STK/SIMUL/Kernel/TCTRAMEMSGCANSESSION.CPP-arc  $  
// 
//    Rev 1.0   04 Feb 2009 17:02:38   adzhelp
// Initial revision.
 * 
 *    Rev 1.4   31 Jan 2005 11:38:50   abarbae
 * PON URD42 DEV 2379 / PON URD42 BODY_SW 784 : Apply new coding rules base types
 * 
 *    Rev 1.3   Aug 05 2004 16:22:08   aguillg
 * PON URD42 DEV 1919 / PON URD42 BODY_SW 632 : Creation of a CAN Gateway between X-Car and CANoe  
 * 
 *    Rev 1.2   Nov 26 2003 16:17:50   amonniy
 * Suite PON URD42 BODY_SW 371 : Transalate LDB API into english
 * 
 *    Rev 1.1   Nov 14 2003 17:04:34   abarbae
 * PON URD42 BODY_SW 371 : Transalate LDB API into english
 * 
 *    Rev 1.0   Apr 30 2003 08:13:46   abarbae
 * Initial revision.
 * 
 *    Rev 1.7   Mar 06 2003 14:23:44   guillen
 * English translation
 * 
 *    Rev 1.6   Oct 24 2002 17:23:16   guillen
 * Modification pour intégré les modification des couches CAN
 * 
 *    Rev 1.5   Oct 24 2002 14:32:40   guillen
 * Intégration des modification sur les couches CAN
 * 
 *    Rev 1.4   Oct 15 2002 16:58:52   guillen
 * Fin de Développement - Pour Validation de la v4.08

  ==========================================================================*/
#include "Config.h"
#ifdef CANAL_CAN      // Le canal can est utilisé

#include "tcTrameMsgCanSession.h"

#include "LdbpcRes.h"
#include "LdbpcDon.h"
#include "LdbpcTim.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
tcTrameMsgCanSession::tcTrameMsgCanSession(tcCanSession* pCanSession,tcCanECar* pCanECar,tParamMsgSeg* pParamMsgSeg, S32 RefCan)
{
  tInfoTrame IT;
  ASSERT(pParamMsgSeg!=NULL);
  ASSERT(pCanSession!=NULL);
  ASSERT(pCanECar!=NULL);

  m_pCanSession=pCanSession;
  m_pCanECar=pCanECar;

  // Nom du message 
	strcpy(m_pNom, pParamMsgSeg->Nom);

  // Paramêtre de flux
	m_RefFluxIP  = pParamMsgSeg->RefFluxIP;	          // Reference du flux initié produit
	m_RefFluxNIC = pParamMsgSeg->RefFluxNIC;	        // Reference du flux non initié consomméC;
	m_TailleMax  = pParamMsgSeg->TailleMax;           // Taille Max du message en octet

  // Paramêtre Session
	m_ObjetCanSession.IdReq   = pParamMsgSeg->AdTrameTx;	  // Adresse de la trame à emettre
	m_ObjetCanSession.IdRep   = pParamMsgSeg->AdTrameRx;	  // Adresse de la trame à recevoir
  m_ObjetCanSession.ModeId  = cModeIdStandard;
  m_ObjetCanSession.FCallBackCon      = CallBackCon;
  m_ObjetCanSession.ParamCallBackCon  = this;
  m_ObjetCanSession.FCallBackInd      = CallBackInd;
  m_ObjetCanSession.ParamCallBackInd  = this;

  m_ObjetCanSession.FCallBackConnectCon = CallBackConnectCon;
  m_ObjetCanSession.ParamCallBackConnectCon  = this;
  m_ObjetCanSession.FCallBackConnectInd = CallBackConnectInd;
  m_ObjetCanSession.ParamCallBackConnectInd  = this;

  m_ObjetCanSession.FCallBackDeconnectCon = CallBackDeconnectCon;
  m_ObjetCanSession.ParamCallBackDeconnectCon  = this;
  m_ObjetCanSession.FCallBackDeconnectInd = CallBackDeconnectInd;
  m_ObjetCanSession.ParamCallBackDeconnectInd  = this;

  m_pCanSession->CreerObjet(&m_ObjetCanSession);            // On crée l'objet
	
  // Incription dans la DLL
  char Tmp[MAX_STRING];
	char Grp[MAX_STRING];
	// Groupe Canal\MessagesSeg\NomMessage
	sprintf(Grp,"%s\\MessagesSeg\\%s", Ressources.GetChannelName(RefCan), m_pNom);

	//-----------------------------------------------------------------
	// Message émis par l'application et reçu par les outils E-Car :
	//-----------------------------------------------------------------
	// NomDeMessageTxBuffer : Contenu du message
	sprintf(Tmp,"%sTxBuffer", m_pNom);
	Donnees.CreerDonnee(&m_RefTxBuffer,Tmp,cDLLSortie,cDLLTypeTab
		,m_TailleMax*cTailleOctet,(U8 *)NULL,Grp);

	// NomDeMessageTxLng 	: Taille du message
	sprintf(Tmp,"%sTxLng", m_pNom);
	Donnees.CreerDonnee(&m_RefTxLng,Tmp,cDLLSortie,cDLLTypeVal,2*cTailleOctet,(U32)0,Grp);

	// NomDeMessageTxIndEvt : Signalisation du message
	sprintf(Tmp,"%sTxIndEvt", m_pNom);
	Donnees.CreerDonnee(&m_RefTxIndEvt,Tmp,cDLLSortie,cDLLTypeEvt,0,(U32)0,Grp);

	// NomDeMessageConnectTxIndEvt : Signalisation de la Connexion
	sprintf(Tmp,"%sConnectTxIndEvt", m_pNom);
	Donnees.CreerDonnee(&m_RefConnectTxIndEvt,Tmp,cDLLSortie,cDLLTypeEvt,0,(U32)0,Grp);

	// NomDeMessageDeconnectTxIndEvt : Signalisation de la Deconnexion
	sprintf(Tmp,"%sDeconnectTxIndEvt", m_pNom);
	Donnees.CreerDonnee(&m_RefDeconnectTxIndEvt,Tmp,cDLLSortie,cDLLTypeEvt,0,(U32)0,Grp);

  // Creation de la trame d'emission
	// Creation de la trame d'emission
    memset(&IT,0, sizeof(tInfoTrame));
    IT.pRef = NULL;
    IT.RefFlux = m_RefFluxIP;
    IT.pName = m_pNom;
    IT.Address =  (U16)m_ObjetCanSession.IdReq;
    IT.MaxSize = cLongueurMaxTrameCan;
    IT.TypeFlux = cFluxIP;
    IT.TxTime = 480*(cTEMus/cLDBTick);
    IT.pGroupName = NULL;
#ifndef CAN_NO_PADDING
	if(pCanSession->GetCanNoPadding() == cTrue)
	{
		IT.TypeFrame = cTypeFrameVarSize;
	}
	else
	{
		IT.TypeFrame = pParamMsgSeg->TypeUUDTFrame;
	}
#else
		IT.TypeFrame = cTypeFrameVarSize;
#endif // CAN_NO_PADDING
    IT.RxMode = 0;
    IT.RxPeriod = 0;
    IT.RxPhase = 0;
    IT.pRxNICCallBackFrame = NULL;
    IT.pRxNIPCallBackFrame = NULL;
    IT.pCallBackMsgSeg = CallBackTxEvents;
    IT.pParamCallBackMsgSeg = (tpParam)this;
	Ressources.CreateFrame(&IT);

	//-----------------------------------------------------------------
	// Message émis par les outils E-Car et reçu par l'application :
	//-----------------------------------------------------------------
	// NomDeMessageRxBuffer	: Contenu du message
	sprintf(Tmp,"%sRxBuffer", m_pNom);
	Donnees.CreerDonnee(&m_RefRxBuffer,Tmp,cDLLEntree,cDLLTypeTab
		,m_TailleMax*cTailleOctet,(U8 *)NULL,Grp);

	// NomDeMessageRxLng 	: Taille du message
	sprintf(Tmp,"%sRxLng", m_pNom);
	Donnees.CreerDonnee(&m_RefRxLng,Tmp,cDLLEntree,cDLLTypeVal,2*cTailleOctet,(U32)0,Grp);

	// NomDeMessageRxIndEvt	: Signalisation du message
	sprintf(Tmp,"%sRxIndEvt", m_pNom);
	Donnees.CreerDonnee(&m_RefRxIndEvt,Tmp,cDLLEntree,cDLLTypeEvt
    ,0 ,(U32)0,Grp,CallBackRxEvents,(tpParam)this);

	// NomDeMessageRxConEvt : Confirmation du message
	sprintf(Tmp,"%sRxConEvt", m_pNom);
	Donnees.CreerDonnee(&m_RefRxConEvt,Tmp,cDLLSortie,cDLLTypeEvt,0,(U32)0,Grp);

	// NomDeMessageConnectRxIndEvt	: Signalisation du message
	sprintf(Tmp,"%sConnectRxIndEvt", m_pNom);
	Donnees.CreerDonnee(&m_RefConnectRxIndEvt,Tmp,cDLLEntree,cDLLTypeEvt
    ,0 ,(U32)0,Grp,CallBackConnectRxEvents,(tpParam)this);

	// NomDeMessageRxConEvt : Confirmation du message
	sprintf(Tmp,"%sConnectRxConEvt", m_pNom);
	Donnees.CreerDonnee(&m_RefConnectRxConEvt,Tmp,cDLLSortie,cDLLTypeEvt,0,(U32)0,Grp);

	// NomDeMessageRxIndEvt	: Signalisation du message
	sprintf(Tmp,"%sDeconnectRxIndEvt", m_pNom);
	Donnees.CreerDonnee(&m_RefDeconnectRxIndEvt,Tmp,cDLLEntree,cDLLTypeEvt
    ,0 ,(U32)0,Grp,CallBackDeconnectRxEvents,(tpParam)this);

	// NomDeMessageRxConEvt : Confirmation du message
	sprintf(Tmp,"%sDeconnectRxConEvt", m_pNom);
	Donnees.CreerDonnee(&m_RefDeconnectRxConEvt,Tmp,cDLLSortie,cDLLTypeEvt,0,(U32)0,Grp);

  // Recherche de la callback standard associee a la trame
	tCallBackCanal*   pCallBackCanal = Ressources.GetStructCallBackCanal();
	tRxSpontWithAddr*  pReceptionSp = NULL;
	for(int Id = 0 ; Id < pCallBackCanal->NbRxSpont ; Id++)
	{
		pReceptionSp = &(pCallBackCanal->pRxSpontWithAddr[Id]);
		// Si la callback associee a la trame est trouvee
		if((pReceptionSp  != NULL) && (pReceptionSp->Address == m_ObjetCanSession.IdRep))
		{
			// Recuperation de la callback standard
			m_pCallBackRxAppli = pReceptionSp->pCallBackRx;
			break;
		}
	}
}

tcTrameMsgCanSession::~tcTrameMsgCanSession()
{

}

//********************************************************************//
// Emission d'une trame par l'appli, A envoyer sur la tcCanECar
//********************************************************************//
void tcTrameMsgCanSession::CallBackTxEvents(tpParam pParam, tpParam pMsg)
{
  tcTrameMsgCanSession* pTrameMsgCan=(tcTrameMsgCanSession*)pParam;

  ASSERT(((tMsg*)pMsg)->Lng<=8);

  tTrameCan2 TrameCan;
  TrameCan.Longueur = (U8)(((tMsg*)pMsg)->Lng);
  memcpy(TrameCan.Buffer,((tMsg*)pMsg)->pBuffer,TrameCan.Longueur);

  // On envoi en UUDT vers tcCanECar
  pTrameMsgCan->m_pCanECar->RepTrame(pTrameMsgCan->m_ObjetCanSession.IdRep,&TrameCan);
}

//********************************************************************//
// Reception d'une trame UUDT pour l'appli de la tcCanECar
//********************************************************************//
void tcTrameMsgCanSession::ReqAppli(tTrameCan2* pTrameCan)
{
  tMsg Msg;
  Msg.Lng=pTrameCan->Longueur;
  Msg.pBuffer=pTrameCan->Buffer;
  m_pCallBackRxAppli((U16)m_ObjetCanSession.IdReq,cLDBCorrect,&Msg);
}

//********************************************************************//
// Reception d'un message par la DLL
//********************************************************************//
void tcTrameMsgCanSession::CallBackRxEvents(tpParam pParam, tpParam pRef)
{
  // On envoi le message à la tcCanSessionDT
  tcTrameMsgCanSession* pTrameMsgCan=(tcTrameMsgCanSession*)pParam;

	// Lecture de la taille du message
	S32 Taille;
	Donnees.Lire(pTrameMsgCan->m_RefRxLng, (U32*)&Taille, NULL, NULL); 
	if(Taille > pTrameMsgCan->m_TailleMax)
  {
    char Texte[MAX_STRING];
    sprintf(Texte,"The reception of a segmented message \"%s\" of %d bytes has been "
			"detected whereas its max size is %d bytes.",pTrameMsgCan->m_pNom,Taille,pTrameMsgCan->m_TailleMax);
		mLDBPCErreur(Texte);
  }
  else    // On envoi en SessionDT vers l'appli
  {
    tMsgCan2 MsgCan;
    U8* Buffer=new U8[pTrameMsgCan->m_TailleMax];
    MsgCan.Buffer=Buffer;
    MsgCan.Longueur = (U16)Taille;
	  Donnees.Lire(pTrameMsgCan->m_RefRxBuffer, MsgCan.Buffer, NULL, NULL);
    pTrameMsgCan->m_pCanSession->Req(&pTrameMsgCan->m_ObjetCanSession,&MsgCan);
  }
}

//********************************************************************//
// Connexion par la DLL
//********************************************************************//
void tcTrameMsgCanSession::CallBackConnectRxEvents(tpParam pParam, tpParam pRef)
{
  // On envoi le message à la tcCanSessionDT
  tcTrameMsgCanSession* pTrameMsgCan=(tcTrameMsgCanSession*)pParam;
  pTrameMsgCan->m_pCanSession->Connect(&pTrameMsgCan->m_ObjetCanSession);
}

//********************************************************************//
// Deconnexion par la DLL
//********************************************************************//
void tcTrameMsgCanSession::CallBackDeconnectRxEvents(tpParam pParam, tpParam pRef)
{
  // On envoi le message à la tcCanSessionDT
  tcTrameMsgCanSession* pTrameMsgCan=(tcTrameMsgCanSession*)pParam;
  pTrameMsgCan->m_pCanSession->Deconnect(&pTrameMsgCan->m_ObjetCanSession);
}

//********************************************************************//
// CallBack de confirmation pour la DLL
//********************************************************************//
void tcTrameMsgCanSession::CallBackCon(tObjetCanSession2* pObjetCanSession, void* pParam)
{
  tcTrameMsgCanSession* pTrame = (tcTrameMsgCanSession*)pParam;
	// Emission de l'evenement de confirmation de reception du message
	Donnees.EmettreEvtSor(pTrame->m_RefRxConEvt);
}

//********************************************************************//
// CallBack de réception pour la DLL
//********************************************************************//
void tcTrameMsgCanSession::CallBackInd(tObjetCanSession2* pObjetCanSession, tMsgCan2* pMsgCan,void* pParam)
{
  tcTrameMsgCanSession* pTrame = (tcTrameMsgCanSession*)pParam;
	// Ecriture du message dans la dll
	Donnees.EcrireSortie(pTrame->m_RefTxBuffer,pMsgCan->Buffer);
	// Ecriture de la taille du message dans la dll
	Donnees.EcrireSortie(pTrame->m_RefTxLng,pMsgCan->Longueur);
	// Emission de l'evenement du message dans la dll
	Donnees.EmettreEvtSor(pTrame->m_RefTxIndEvt);
}

//********************************************************************//
// CallBack de confirmation de connexion pour la DLL
//********************************************************************//
void tcTrameMsgCanSession::CallBackConnectCon(tObjetCanSession2* pObjetCanSession, void* pParam)
{
  tcTrameMsgCanSession* pTrame = (tcTrameMsgCanSession*)pParam;
	// Emission de l'evenement de confirmation de reception de connexion
	Donnees.EmettreEvtSor(pTrame->m_RefConnectRxConEvt);
}

//********************************************************************//
// CallBack de réception de connexion pour la DLL
//********************************************************************//
void tcTrameMsgCanSession::CallBackConnectInd(tObjetCanSession2* pObjetCanSession, void* pParam)
{
  tcTrameMsgCanSession* pTrame = (tcTrameMsgCanSession*)pParam;
	// Emission de l'evenement de connexion dans la dll
	Donnees.EmettreEvtSor(pTrame->m_RefConnectTxIndEvt);
}

//********************************************************************//
// CallBack de confirmation de déconnexion pour la DLL
//********************************************************************//
void tcTrameMsgCanSession::CallBackDeconnectCon(tObjetCanSession2* pObjetCanSession, void* pParam)
{
  tcTrameMsgCanSession* pTrame = (tcTrameMsgCanSession*)pParam;
	// Emission de l'evenement de confirmation de déconnexion du message
	Donnees.EmettreEvtSor(pTrame->m_RefDeconnectRxConEvt);
}

//********************************************************************//
// CallBack de réception pour la DLL
//********************************************************************//
void tcTrameMsgCanSession::CallBackDeconnectInd(tObjetCanSession2* pObjetCanSession, void* pParam)
{
  tcTrameMsgCanSession* pTrame = (tcTrameMsgCanSession*)pParam;
	// Emission de l'evenement de déconnexion dans la dll
	Donnees.EmettreEvtSor(pTrame->m_RefDeconnectTxIndEvt);
}
#endif CANAL_CAN