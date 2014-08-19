//**************************************************************************
// COMPOSANT : LdbpcCan
// FONCTION : Implementation de la classe tcCanal et ses classes dérivées
//
// Ce logiciel est la propriete de JCI :
// ---------------------------------------
// Il ne peut être reproduit ni communique en totalite ou partie sans
// son autorisation ecrite.
//
// ------------------------------------------------------------------------
// Definition des fonctions exportees par le composant LdbpcCan :
// ------------------------------------------------------------------
//
// ------------------------------------------------------------------------
// - Les macros, constantes et types qui ne sont pas destines a etre
// exportes sont definis dans ce fichier.
// - Les variables et fonctions qui ne sont pas destinees a etre exportees
// sont definies dans ce fichier et precedees du mot-cle static.
// ------------------------------------------------------------------------
// Commentaires sur le fonctionnement interne du composant:
// --------------------------------------------------------
// (structures de donnees, algorithmes, limitations, ...)
//
// ------------------------------------------------------------------------
// Nom et initiales des developpeurs :	GUILLEN	GG
//
// ------------------------------------------------------------------------
// Historique du fichier LdbpcCan.cpp:
// -------------------------------------
// (initiales, date, modification)
//
// cree par :	GG : 20/04/2000
//
//
//***************************************************************************

#define LdbpcCan "LdbpcCan"

//--------------------------------------------------------------------------
//---------------- Inclusion de fichiers (système et librairies -----------
//--------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////
//
// LdbpcCan.cpp: implementation of the tcElement class.
//
//////////////////////////////////////////////////////////////////////
#include "Ldbpc.h"			// Definition des types et constantes de bases
#include <string.h>			// Definition de la librairie de chaine de caractères

//--------------------------------------------------------------------------
//------- Inclusion des definitions des autres composants utiles ---------
//--------------------------------------------------------------------------
#include "LdbpcCan.h"		// Definition de la classe de gestion des canaux
#include "LdbpcErr.h"		// Definition du module de gestion des erreurs

#include "CANDll.h"     // Access to CANDLL
#include "XCarCAN.h"
//--------------------------------------------------------------------------
//------- Declaration des constantes locales à ce composant --------------
//--------------------------------------------------------------------------
// #define cNomConstante ValeurDeLaConstante

//--------------------------------------------------------------------------
//------- Declaration des macros locales à ce composant ------------------
//--------------------------------------------------------------------------
// #define mNomMacro (DefinitionDeLaMacro)

//--------------------------------------------------------------------------
//------- Definition des types locaux à ce composant ---------------------
//--------------------------------------------------------------------------
// typedef ... tNomType;
//--------------------------------------------------------------------------
//------- Variables locales à ce composant---------------------------------
//--------------------------------------------------------------------------
// static tType NomVariable;
// static tType* pNomVariable;
//--------------------------------------------------------------------------
//------- Donnees Constantes locales à ce composant ----------------------
//--------------------------------------------------------------------------
// static const tType NomVariable;
//--------------------------------------------------------------------------
//------- Variables exportees par ce composant ---------------------------
//--------------------------------------------------------------------------
// tType ComNomVariable; (Com: 3 lettres identifiant ce composant)
// tType* pComNomVariable;
//--------------------------------------------------------------------------
//------- Donnees Constantes exportees par ce composant ------------------
//--------------------------------------------------------------------------
// const tType ComNomVariable; (Com: 3 lettres identifiant ce composant)
//--------------------------------------------------------------------------
//---------------------------- Fonctions locales ---------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//------------------------- Fonctions exportees ----------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------- Implementation de la classe tcCanal -------------------
//--------------------------------------------------------------------------


//--------------------------------------------------------------------------
// Constructor
//--------------------------------------------------------------------------
tcCanal::tcCanal(tCallBackCanal * pStructCallBack)
{
	int Type;
	// Initialisation par default de la classe
	for(Type=0 ; Type<MAX_FLUX ; Type++ )	m_RefFlux[Type] = -1;

  memcpy(&m_StructCallBack,pStructCallBack,sizeof(tCallBackCanal));

	m_Autorise			= cTrue;
	m_RefCtrlEnCours	= 0;
	m_Etat				= 0;	
	m_Format			= cCodageIntel;
}

//--------------------------------------------------------------------------
// Destructeur
//--------------------------------------------------------------------------
tcCanal::~tcCanal()
{
}

// ***************************************************************************
//   Fonction exportee de la classe tcCanal :
//	 tLDBPCStatut AttacherFlux(S32 RefFlux,tLdbpcTypeFlux Type)
// ---------------------------------------------------------------------------
//   Role de la fonction  :
//		Attacher un flux a un canal	
//      Utilisateur : public
//		
//   Signification des parametres :
//      RefFlux		:	Reference du flux a attacher au canal.
//		Type		:	type du flux a attacher au canal.
//
//   Signification du resultat :
//      statut
//
//   Algorithme
//      Si le type de flux n'existe pas dans le canal
//			Affectation du flux au canal
//		Sinon
//			Erreur
//		Finsi
//
// ***************************************************************************
tLDBPCStatut tcCanal::AttacherFlux(S32 RefFlux,tLdbpcTypeFlux Type)
{
	tLDBPCStatut Res = cLdbpcErr;
	
	// Verification que le flux n'existe pas
	if(m_RefFlux[Type] == -1)
	{
		// Affectation du flux au canal
		m_RefFlux[Type] = RefFlux;			
		Res = cLdbpcOk;
	}
	else	Res = cLdbpcErrParFlux;

	return Res;
}

// ***************************************************************************
//   Fonction exportee de la classe tcCanal :
//	 tLDBPCStatut LireRefFlux(tLdbpcTypeFlux Type, S32 * pRefFlux)
// ---------------------------------------------------------------------------
//   Role de la fonction  :
//		Lire une reference de flux par rapport au type de flux dans la canal
//      Utilisateur : public
//		
//   Signification des parametres :
//		Type		:	type du flux a lire dans canal
//      RefFlux		:	Reference du flux a retourner par pointeur.
//
//   Signification du resultat :
//      statut
//
//   Algorithme
//		Si le pointeur passe en paramettre pointe sur un emplacament != NULL
//			Si le type de flux existe dans le canal
//				Affectation du flux au canal
//			Sinon
//				Erreur
//			Finsi
//		Sinon
//			Erreur
//		Finsi
//
// ***************************************************************************
tLDBPCStatut tcCanal::LireRefFlux(tLdbpcTypeFlux Type, S32 * pRefFlux)
{
	tLDBPCStatut Res = cLdbpcErrFlux;

	// Verification que la reference fournie existe
	if(pRefFlux)
	{
		// Verification que le flux existe
		if(m_RefFlux[Type] != -1)
		{
			*pRefFlux = m_RefFlux[Type];		
			Res = cLdbpcOk;
		}
		else	Res = cLdbpcErrFlux;
	}
	else Res = cLdbpcErrPointNul; 

	return Res;
}

// ***************************************************************************
//   Fonction exportee de la classe tcCanal :
//	 BOOL Autoriser(BOOL Autorise)
// ---------------------------------------------------------------------------
//   Role de la fonction  :
//		Demande d'autorisation effecutee par le parametrage.
//      Utilisateur : public
//		
//   Signification des parametres :
//		Autorise		:	cTrue si autorisation, cFalse sinon
//
//   Signification du resultat :
//      cTrue si la demande c'est bien effectuee, cFalse sinon
//
//   Algorithme
//		Si (le pointeur de fonction callback 
//			sur une autorisation personnalisee existe)
//				appel de la demande d'autorisation
//		Finsi
//
// ***************************************************************************
BOOL tcCanal::Autoriser(BOOL Autorise)
{
	BOOL bRes = cFalse;
	if(m_StructCallBack.pCbEnable)
	{
		m_StructCallBack.pCbEnable(Autorise);
	}
	return bRes;
}

// ***************************************************************************
//   Fonction exportee de la classe tcCanal :
//	 BOOL Controler(tCtrl Ctrl,tMsg * pMsg)
// ---------------------------------------------------------------------------
//   Role de la fonction  :
//		Traitement d'un controle sortant effecutee par le parametrage.
//      Utilisateur : public
//		
//   Signification des parametres :
//		Ctrl	:	Identificateur du controle sortant.
//		pMsg	:	Pointeur sur le message.
//
//   Signification du resultat :
//      cTrue si le traitement du controle c'est bien effectué, cFalse sinon.
//
//   Algorithme
//		Si (le pointeur de fonction callback 
//			sur le traitement du controle personnalisee existe)
//				appel du traitement du controle
//		Finsi
//
// ***************************************************************************
BOOL tcCanal::Controler(tCtrl Ctrl)
{
	BOOL bRes = cFalse;
	if(m_StructCallBack.pCbControl)
	{
		m_StructCallBack.pCbControl(Ctrl);
	}
  return bRes;
}

// ***************************************************************************
//   Fonction exportee de la classe tcCanal :
//	 BOOL Controler(tCtrl Ctrl,tMsg * pMsg)
// ---------------------------------------------------------------------------
//   Role de la fonction  :
//		Appel de la callback de fin de Controle sortant.
//      Utilisateur : public
//		
//   Signification des parametres :
//		Ctrl	:	Identificateur du controle sortant.
//
//   Signification du resultat :
//      cTrue si l'appel de callback de fin de controle a bien ete effectue, cFalse sinon.
//
//   Algorithme
//		Si (le pointeur de fonction callback de fin de controle existe)
//				appel de la callback de fin controle
//		Finsi
//
// ***************************************************************************
BOOL tcCanal::FinControle(tCtrl Ctrl,tStatus Statut)
{
	BOOL bRes = cFalse;
	if(m_StructCallBack.pCallBackEndCtrl)
	{
		m_StructCallBack.pCallBackEndCtrl(Ctrl, Statut);
    bRes = cTrue;
	}
	return bRes;
}

/*============================================================================
  DESCRIPTION : Callback input control of the Channel
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
BOOL tcCanal::CBControle(tCtrl Ctrl)
{
	BOOL bRes = cFalse;
	if(m_StructCallBack.pCallBackCtrl)
	{
		m_StructCallBack.pCallBackCtrl(Ctrl);
    bRes = cTrue;
	}
	return bRes;
}

/*============================================================================
  DESCRIPTION : Reset the generic Channel
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void tcCanal::Reset(void)
{
	// Rend le canal disponible
  m_Etat = cDisponible;

	// Autorisation de Callback par defaut
  m_Autorise = cTrue;
}

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//-------------------------   CChannelCAN   --------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

static void CallBackCon(tObjetCanUU* pObjetCanUU, void* pParam);
static void CallBackInd(tObjetCanUU* pObjetCanUU, tTrameCan* pTrameCan,void* pParam);

/*============================================================================
  DESCRIPTION : Construction of a CAN Channel for XCAN
  
  PARAMETERS (Type,Name,Min,Max) :  CAN channel structures  

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
CChannelCAN::CChannelCAN(tXCanChannel * pXCanChannel) : tcCanal(pXCanChannel->pCallBackStruct)
{
    memcpy(&m_XCanChannel,pXCanChannel,sizeof(tXCanChannel));

    m_WakeUp = cFalse;
    m_FirstCtrlInit = cTrue;
    m_pRxCANUUDT = NULL;
    m_pTxCANUUDT = NULL;

    m_pCANChannel = XCAN_GetCANConnection(m_XCanChannel.NodeName,"ECAR");
}

/*============================================================================
  DESCRIPTION : Destruction of a CAN Channel
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
CChannelCAN::~CChannelCAN()
{
  if(m_pCANChannel != NULL)
  {
    if(m_pRxCANUUDT != NULL)
    {
        m_pCANChannel->RemoveCanObjet(m_pRxCANUUDT);
        delete m_pRxCANUUDT;  
    }
    if(m_pTxCANUUDT != NULL)
    {
        m_pCANChannel->RemoveCanObjet(m_pTxCANUUDT );
        delete m_pTxCANUUDT ;  
    }

    m_ListTxId.RemoveAll();
    while(m_ListRxId.GetCount() > 0)
    {
      tMsgBuffer * pMsgBuffer = m_ListRxId.GetHead();
      m_ListRxId.RemoveHead();
      delete pMsgBuffer;
    }
  }
}

/*============================================================================
  DESCRIPTION : Receive Confirmation of sending message to CANDLL
  
  PARAMETERS (Type,Name,Min,Max) :   CAN Messages structures  

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void LdbpcTxCon(CChannelCAN* obj)
{
    obj->OnLdbpcTxCon();
}

void CallBackCon(tObjetCanUU* pObjetCanUU, void* pParam)
{
  ((CChannelCAN*)pParam)->OnTxCon(pObjetCanUU);
}

void CChannelCAN::OnTxCon(tObjetCanUU* pObjetCanUU)
{
  if(m_StructCallBack.pCallBackTx != NULL)
  {
    // Add the in FIFO
    m_CSTx.Lock();
    m_ListTxId.AddTail(pObjetCanUU->Id);
    m_CSTx.Unlock();

    // Activation
    if(m_TxTempo.Actif == 0)
    {
      m_TxTempo.Duree = 0;
      m_TxTempo.pObject = this;
      m_TxTempo.pCallBack = LdbpcTxCon;
      Timer.AjouterTempo(&(m_TxTempo));
    }
  }
}

void CChannelCAN::OnLdbpcTxCon()
{
  // Get From FIFO
  m_CSTx.Lock();
  while(m_ListTxId.GetCount() > 0)
  {
    U32 id = m_ListTxId.GetHead();
    m_StructCallBack.pCallBackTx((tAddress)id, cLDBCorrect);
    m_ListTxId.RemoveHead();
  }
  m_CSTx.Unlock();
}

/*============================================================================
  DESCRIPTION : Receive message From CANDLL
  
  PARAMETERS (Type,Name,Min,Max) : CAN Messages structures  

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void CallBackInd(tObjetCanUU* pObjetCanUU, tTrameCan* pTrameCan,void* pParam)
{
  ((CChannelCAN*)pParam)->OnRxInd(pObjetCanUU,pTrameCan);
}

void LdbpcRxInd(CChannelCAN* obj)
{
  obj->OnLdbpcRxInd();
}

void CChannelCAN::OnRxInd(tObjetCanUU* pObjetCanUU,tTrameCan* pTrameCan)
{
    // Add the in FIFO
    m_CSRx.Lock();
    tMsgBuffer * pMsgBuffer = new tMsgBuffer;
    memcpy((void *)&(pMsgBuffer->TrameCan),(void *)pTrameCan,sizeof(tTrameCan));
    pMsgBuffer->Id = pObjetCanUU->Id;
    m_ListRxId.AddTail(pMsgBuffer);
    m_CSRx.Unlock();

    // Activation
    if(m_RxTempo.Actif == 0)
    {
      m_RxTempo.Duree = 0;
      m_RxTempo.pObject = this;
      m_RxTempo.pCallBack = LdbpcRxInd;
      Timer.AjouterTempo(&(m_RxTempo));
    }
}

void CChannelCAN::OnLdbpcRxInd()
{
  tMsgBuffer * pMsgBuffer = NULL;
  tMsg Msg;

  if((m_WakeUp) && (m_StructCallBack.pCallBackCtrl != NULL))
  {
    m_WakeUp = cFalse;
    m_StructCallBack.pCallBackCtrl(m_XCanChannel.CANCell.CtrlWakeUp);
  }

  while(m_ListRxId.GetCount() > 0)
  {
    // Get From the FIFO
    m_CSRx.Lock();
    pMsgBuffer = m_ListRxId.GetHead();
    m_ListRxId.RemoveHead();
    m_CSRx.Unlock();
    Msg.Lng = pMsgBuffer->TrameCan.Longueur;
    Msg.pBuffer = pMsgBuffer->TrameCan.Buffer;
    if(m_XCanChannel.pCANRxCallBackInd != NULL)
    {
      m_XCanChannel.pCANRxCallBackInd((tAddress)pMsgBuffer->Id, cLDBCorrect, &Msg);
    }
    else if(m_StructCallBack.pRxSpontWithAddr != NULL)
    {
      int i;
      for(i = 0 ; i < m_StructCallBack.NbRxSpont; i++)
      {
        if(pMsgBuffer->Id == (U32)m_StructCallBack.pRxSpontWithAddr[i].Address)
        {
          m_StructCallBack.pRxSpontWithAddr[i].pCallBackRx((tAddress)pMsgBuffer->Id, cLDBCorrect, &Msg);
          delete pMsgBuffer;
          return;
        }
      }
    }
    delete pMsgBuffer;
  }
}

/*============================================================================
  DESCRIPTION : Send a CAN UUDT Frame  -> CANDLL
  
  PARAMETERS (Type,Name,Min,Max) :  type of the flux, Id CAN Message, Message

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
BOOL CChannelCAN::Send(tLdbpcTypeFlux Type, tAddress Address, tMsg* pMsg)
{
  if((Type == cFluxIP) && (m_pCANChannel != NULL))
  {
    tTrameCan Frame;
    Frame.Longueur = (U8)pMsg->Lng;
    memcpy(Frame.Buffer, pMsg->pBuffer ,pMsg->Lng);
    m_pTxCANUUDT->Id = (U32)Address;
    m_pCANChannel->Req(m_pTxCANUUDT, &Frame, cTrue);
    return(cTrue);
  }
  return(cFalse);
}

/*============================================================================
  DESCRIPTION : Reset the CAN Channel
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void CChannelCAN::Reset()
{
    Timer.SupprimerTempo(&m_TxTempo);
    Timer.SupprimerTempo(&m_RxTempo);
    m_ListTxId.RemoveAll();

    while(m_ListRxId.GetCount() > 0)
    {
        tMsgBuffer * pMsgBuffer = m_ListRxId.GetHead();
        m_ListRxId.RemoveHead();
        delete pMsgBuffer;
    }

    tcCanal::Reset();
    m_WakeUp = cFalse;
    m_FirstCtrlInit = cTrue;
    if(m_pCANChannel != NULL)
    {
        if(m_pTxCANUUDT == NULL) 
        {
            m_pTxCANUUDT = new tObjetCanUU();
            if(m_pTxCANUUDT != NULL)
            {
                // Set Information for CANDLL
                m_pTxCANUUDT->CommunicationType = cCanTransmissionMultiIdType;
                m_pTxCANUUDT->FCallBackCon      = CallBackCon;
                m_pTxCANUUDT->ParamCallBackCon  = this;
            }
        }
        else
        {
            m_pCANChannel->RemoveCanObjet(m_pTxCANUUDT);
        }

        if(m_pRxCANUUDT == NULL)
        {
            m_pRxCANUUDT = new tObjetCanUU();
            if(m_pRxCANUUDT != NULL)
            {
                // Set Information for CANDLL
                m_pRxCANUUDT->CommunicationType = cCanReceptionMultiIdType;
                m_pRxCANUUDT->FCallBackInd      = CallBackInd;
                m_pRxCANUUDT->ParamCallBackInd  = this;
            }
        }
        else
        {
            m_pCANChannel->RemoveCanObjet(m_pRxCANUUDT);
        }

        m_pCANChannel->AddCanObject(m_pTxCANUUDT);
        m_pCANChannel->AddCanObject(m_pRxCANUUDT);
        m_pCANChannel->InitializeCanTimer();
    }
}

/*============================================================================
  DESCRIPTION : Send Control event to the CAN Channel
  
  PARAMETERS (Type,Name,Min,Max) :  Id of the Control

  RETURN VALUE :  result
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
BOOL CChannelCAN::Controler(tCtrl Ctrl)
{
    BOOL bRes = cFalse;
    tcCanal::Controler(Ctrl);

    if((m_pCANChannel != NULL) && (m_XCanChannel.CANCell.Auto))
    {
        if(Ctrl == m_XCanChannel.CANCell.CtrlInit) 
        {
            if(m_FirstCtrlInit)
            {
                m_WakeUp = cTrue;
                m_FirstCtrlInit = cFalse;
            }
            m_ListTxId.RemoveAll();
        }
        else if(Ctrl == m_XCanChannel.CANCell.CtrlCancelTxInProgress)
        {
            m_ListTxId.RemoveAll();
        }
        else if(Ctrl == m_XCanChannel.CANCell.CtrlStop)
        {
            m_WakeUp = cTrue;
            m_ListTxId.RemoveAll();
        }
    }
    return bRes;
}
