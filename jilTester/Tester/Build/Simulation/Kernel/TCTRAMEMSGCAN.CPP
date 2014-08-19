/*============================================================================
  Project ......................... LDBPC
  Component ....................... tcTrameMsgCan
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
  tcTrameMsgCan.cpp file review :

    PVCS Historic :

    $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/EXT_CMP/CPP_CMP/STK/SIMUL/Kernel/TCTRAMEMSGCAN.CPP-arc  $  
// 
//    Rev 1.0   04 Feb 2009 17:02:38   adzhelp
// Initial revision.
 * 
 *    Rev 1.4   31 Jan 2005 11:38:50   abarbae
 * PON URD42 DEV 2379 / PON URD42 BODY_SW 784 : Apply new coding rules base types
 * 
 *    Rev 1.3   Aug 05 2004 16:22:06   aguillg
 * PON URD42 DEV 1919 / PON URD42 BODY_SW 632 : Creation of a CAN Gateway between X-Car and CANoe  
 * 
 *    Rev 1.2   Nov 26 2003 16:17:48   amonniy
 * Suite PON URD42 BODY_SW 371 : Transalate LDB API into english
 * 
 *    Rev 1.1   Nov 14 2003 17:04:34   abarbae
 * PON URD42 BODY_SW 371 : Transalate LDB API into english
 * 
 *    Rev 1.0   Apr 30 2003 08:13:42   abarbae
 * Initial revision.
 * 
 *    Rev 1.8   Mar 06 2003 14:23:46   guillen
 * English translation
 * 
 *    Rev 1.7   Oct 24 2002 17:23:14   guillen
 * Modification pour intégré les modification des couches CAN
 * 
 *    Rev 1.6   Oct 24 2002 14:32:38   guillen
 * Intégration des modification sur les couches CAN
 * 
 *    Rev 1.5   Oct 24 2002 11:02:46   guillen
 * Correction suite à une détection de fuite de mémoire
 * 
 *    Rev 1.4   Oct 23 2002 08:36:50   guillen
 * Fin du test unitaire
 * 
 *    Rev 1.3   Oct 15 2002 16:58:52   guillen
 * Fin de Développement - Pour Validation de la v4.08


  ==========================================================================*/
#include "Config.h"
#ifdef CANAL_CAN      // Le canal can est utilisé

#include "tcTrameMsgCan.h"

#include "LdbpcRes.h"
#include "LdbpcDon.h"
#include "LdbpcTim.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
tcTrameMsgCan::tcTrameMsgCan(tcCanSession* pCanSession,tcCanECar* pCanECar,tParamMsgSeg* pParamMsgSeg, S32 RefCan)
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

  // Paramêtre USDT
	m_ObjetCanUS.IdReq   = pParamMsgSeg->AdTrameTx;	  // Adresse de la trame à emettre
	m_ObjetCanUS.IdRep   = pParamMsgSeg->AdTrameRx;	  // Adresse de la trame à recevoir
  m_ObjetCanUS.ModeId  = cModeIdStandard;
  m_ObjetCanUS.FCallBackCon      = CallBackCon;
  m_ObjetCanUS.ParamCallBackCon  = this;
  m_ObjetCanUS.FCallBackInd      = CallBackInd;
  m_ObjetCanUS.ParamCallBackInd  = this;
  m_pCanSession->CreerObjet(&m_ObjetCanUS);            // On crée l'objet
	
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

	// Creation de la trame d'emission
    memset(&IT,0, sizeof(tInfoTrame));
    IT.pRef = NULL;
    IT.RefFlux = m_RefFluxIP;
    IT.pName = m_pNom;
    IT.Address =  (U16)m_ObjetCanUS.IdReq;
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

  // Recherche de la callback standard associee a la trame
	tCallBackCanal*   pCallBackCanal = Ressources.GetStructCallBackCanal();
	tRxSpontWithAddr*  pReceptionSp = NULL;
	for(int Id = 0 ; Id < pCallBackCanal->NbRxSpont ; Id++)
	{
		pReceptionSp = &(pCallBackCanal->pRxSpontWithAddr[Id]);
		// Si la callback associee a la trame est trouvee
		if((pReceptionSp  != NULL) && (pReceptionSp->Address == m_ObjetCanUS.IdRep))
		{
			// Recuperation de la callback standard
			m_pCallBackRxAppli = pReceptionSp->pCallBackRx;
			break;
		}
	}
}

tcTrameMsgCan::~tcTrameMsgCan()
{

}

//********************************************************************//
// Emission d'une trame par l'appli, A envoyer sur la tcCanECar
//********************************************************************//
void tcTrameMsgCan::CallBackTxEvents(tpParam pParam, tpParam pMsg)
{
  tcTrameMsgCan* pTrameMsgCan=(tcTrameMsgCan*)pParam;

  ASSERT(((tMsg*)pMsg)->Lng<=8);

  tTrameCan2 TrameCan;
  TrameCan.Longueur = (U8)(((tMsg*)pMsg)->Lng);
  memcpy(TrameCan.Buffer,((tMsg*)pMsg)->pBuffer,TrameCan.Longueur);

  // On envoi en UUDT vers tcCanECar
  pTrameMsgCan->m_pCanECar->RepTrame(pTrameMsgCan->m_ObjetCanUS.IdRep,&TrameCan);
}

//********************************************************************//
// Reception d'une trame UUDT pour l'appli de la tcCanECar
//********************************************************************//
void tcTrameMsgCan::ReqAppli(tTrameCan2* pTrameCan)
{
  tMsg Msg;
  Msg.Lng=pTrameCan->Longueur;
  Msg.pBuffer=pTrameCan->Buffer;
  m_pCallBackRxAppli((U16)m_ObjetCanUS.IdRep,cLDBCorrect,&Msg);
}

//********************************************************************//
// Reception d'un message par la DLL
//********************************************************************//
void tcTrameMsgCan::CallBackRxEvents(tpParam pParam, tpParam pRef)
{
  // On envoi le message à la tcCanUSDT
  tcTrameMsgCan* pTrameMsgCan=(tcTrameMsgCan*)pParam;

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
  else    // On envoi en USDT vers l'appli
  {
    tMsgCan2 MsgCan;
    U8* Buffer=new U8[pTrameMsgCan->m_TailleMax];
    MsgCan.Buffer=Buffer;
    MsgCan.Longueur = (U16)Taille;
	Donnees.Lire(pTrameMsgCan->m_RefRxBuffer, MsgCan.Buffer, NULL, NULL);
    pTrameMsgCan->m_pCanSession->Req(&pTrameMsgCan->m_ObjetCanUS,&MsgCan);
	delete Buffer;
  }
}

//********************************************************************//
// CallBack de confirmation pour la DLL
//********************************************************************//
void tcTrameMsgCan::CallBackCon(tObjetCanUS2* pObjetCanUS, void* pParam)
{
  tcTrameMsgCan* pTrame = (tcTrameMsgCan*)pParam;
	// Emission de l'evenement de confirmation de reception du message
	Donnees.EmettreEvtSor(pTrame->m_RefRxConEvt);
}

//********************************************************************//
// CallBack de réception pour la DLL
//********************************************************************//
void tcTrameMsgCan::CallBackInd(tObjetCanUS2* pObjetCanUS, tMsgCan2* pMsgCan,void* pParam)
{
  tcTrameMsgCan* pTrame = (tcTrameMsgCan*)pParam;
	// Ecriture du message dans la dll
	Donnees.EcrireSortie(pTrame->m_RefTxBuffer,pMsgCan->Buffer);
	// Ecriture de la taille du message dans la dll
	Donnees.EcrireSortie(pTrame->m_RefTxLng,pMsgCan->Longueur);
	// Emission de l'evenement du message dans la dll
	Donnees.EmettreEvtSor(pTrame->m_RefTxIndEvt);
}

#endif CANAL_CAN