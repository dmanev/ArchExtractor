//**************************************************************************
// COMPOSANT : LdbpcFlu
// FONCTION : Implementation des classes de FLux 
//
// Ce logiciel est la propriete de JCI :
// ---------------------------------------
// Il ne peut être reproduit ni communique en totalite ou partie sans
// son autorisation ecrite.
//
// ------------------------------------------------------------------------
// Definition des fonctions exportees par le composant LdbpcFlu :
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
// Historique du fichier LdbpcFlu.c:
// -------------------------------------
// (initiales, date, modification)
//
// cree par :	GG : 20/04/2000
//
//
//***************************************************************************

#define LdbpcFlu "LdbpcFlu"

//--------------------------------------------------------------------------
//---------------- Inclusion de fichiers (système et librairies -----------
//--------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////
//
// LdbpcFlu.cpp: implementation of the tcElement class.
//
//////////////////////////////////////////////////////////////////////
#include "string.h"
#include "LdbpcFlu.h"

//--------------------------------------------------------------------------
//------- Inclusion des definitions des autres composants utiles ---------
//--------------------------------------------------------------------------
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
//--------------- Implementation de la classe tcFlux ----------------------
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// Constructeur
//--------------------------------------------------------------------------
tcFlux::tcFlux()
{
	// Initialisation du tableau de trame
	m_TabTrame.SetSize(0);
	m_Type = cNoFlux;
	m_pCanal = NULL;
}

tcFlux::tcFlux(tcCanal * pCanal, tInfoFlux * pIflux)
{
	m_pCanal = pCanal;
	m_Canal = pIflux->RefCan;
	m_Type	= pIflux->TypeFlux;

	// Initialisation du tableau de trame
	m_TabTrame.SetSize(0);
}
//--------------------------------------------------------------------------
//	Destructeur
//--------------------------------------------------------------------------
tcFlux::~tcFlux()
{
	m_TabTrame.RemoveAll();
}


//--------------------------------------------------------------------------
// Attacher une trame a un flux
//--------------------------------------------------------------------------
tLDBPCStatut tcFlux::Attacher(S32 refTrame)
{
	tLDBPCStatut	Res;

	// Verification de l'existance de la trame
	Res = ExisteTrame(refTrame);

	// Si elle n'existe pas dans le tableau
	if(Res == cLdbpcOk)
	{
		// Ajout de la reference dans le tableau
		m_TabTrame.Add(refTrame);
	}
	return Res;
}

//--------------------------------------------------------------------------
// Verifie l'existance de la reference de trame
//--------------------------------------------------------------------------
tLDBPCStatut tcFlux::ExisteTrame(S32 Ref)
{
	tLDBPCStatut Res = cLdbpcErr;
	int Id;
	
	// Parcours du tableau
	for(Id = 0; Id<m_TabTrame.GetSize() ; Id++)
	{
		// si la reference de la trame en cours est egale à la reference a trouve
		if(m_TabTrame.GetAt(Id) == Ref) break;
	}

	// si la reference de la trame n'a pas ete trouve
	if(Id == m_TabTrame.GetSize()) 
		Res = cLdbpcOk;

	return Res;
}

//--------------------------------------------------------------------------
// Lire une reference de trame par rapport a un index
//--------------------------------------------------------------------------
tLDBPCStatut tcFlux::LireRefTrame(int Index, S32 * pRefTrame)
{
	tLDBPCStatut Res = cLdbpcErr;

	// Verification de l'existance de la reference de trame
	if(Index < m_TabTrame.GetSize()) 
	{
		// Verification du pointeur
		if(pRefTrame)
		{
			*pRefTrame = m_TabTrame.GetAt(Index);
			Res = cLdbpcOk;
		}
		else Res = cLdbpcErrPointNul;
	}	
	else Res = cLdbpcErrTrame;

	return Res;
}


//--------------------------------------------------------------------------
//--------------- Implementation de la classe tcFluxI ---------------------
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// Constructeurs
//--------------------------------------------------------------------------
tcFluxI::tcFluxI():tcFlux()
{
	m_pUserCBAction		= NULL;
	m_pCBFinActionStd	= NULL;
	m_AdresseEnCours	= (tAddress)0;
	m_pMsgEnCours		= NULL;
	m_MsgTemp.pBuffer	= NULL;
	m_MsgTemp.Lng		= 0;
	m_TailleBufferMax	= 0;
}

tcFluxI::tcFluxI(tcCanal * pCanal, tInfoFlux * pIflux)
 : tcFlux(pCanal, pIflux)
{
	m_pCBFinActionStd	= NULL;
	m_AdresseEnCours	= (tAddress)0;
	m_pUserCBAction		= pIflux->pCbActionI;
	m_pMsgEnCours		= NULL;
	m_MsgTemp.pBuffer	= NULL;
	m_MsgTemp.Lng		= 0;
	m_TailleBufferMax	= 0;
}

//--------------------------------------------------------------------------
//	Destructeur
//--------------------------------------------------------------------------
tcFluxI::~tcFluxI()
{
	if(m_MsgTemp.pBuffer) 
		delete [] m_MsgTemp.pBuffer;
}

//--------------------------------------------------------------------------
// Mise a jour de la fonction de callback en Emission
//--------------------------------------------------------------------------
void tcFluxI::MajCallBack(tpCallBackStatusAddr pFinAction) 
{
	m_pCBFinActionStd	= pFinAction; 
}

//--------------------------------------------------------------------------
// Appel de la fonction callback personalisee
//--------------------------------------------------------------------------
BOOL tcFluxI::Action(void)
{
	BOOL bRes = cFalse;

	// Verification de l'existance d'une fonction callback personalisee
	if(m_pUserCBAction && m_pMsgEnCours && m_pMsgEnCours->pBuffer)
	{
		// Appel de la fonction callback personalisee
		m_pUserCBAction(m_AdresseEnCours, m_pMsgEnCours);
		bRes = cTrue;	
	}
	return bRes;
}

//--------------------------------------------------------------------------
// Appel de la fonction callback standard de din d'action(emission ou reception)
//--------------------------------------------------------------------------
BOOL tcFluxI::FinAction(void)
{
	BOOL bRes = cFalse;

	// Verification de l'existance d'une fonction callback
	if(m_pCBFinActionStd)
	{
		// Appel de la fonction callback personalisee
		m_pCBFinActionStd(m_AdresseEnCours, cLDBCorrect);
		bRes = cTrue;	
	}
	return bRes;
}

//--------------------------------------------------------------------------
// Lecture du message en cours
//--------------------------------------------------------------------------
tLDBPCStatut tcFluxI::LireMsgEnCours(tMsg ** ppMsg)
{
	tLDBPCStatut bRes = cLdbpcErr;

	// S'il existe un message courant 
	if(m_pMsgEnCours && m_pMsgEnCours->pBuffer)
	{
		*ppMsg = m_pMsgEnCours;
		bRes = cLdbpcOk;
	}
	return bRes;
}

//--------------------------------------------------------------------------
// Ecriture du message en cours
//--------------------------------------------------------------------------
tLDBPCStatut tcFluxI::EcrireMsgEnCours(tMsg *pMsg)
{
	tLDBPCStatut Res = cLdbpcErr;

	// S'il existe un courant 
	if(pMsg && pMsg->pBuffer)
	{
		if(mFluxProduit(m_Type))
		{
			m_pMsgEnCours = &m_MsgTemp;
			m_pMsgEnCours->Lng = pMsg->Lng;
			if(m_pMsgEnCours && m_pMsgEnCours->pBuffer)
			{
				// Copie du buffer
				memcpy(m_pMsgEnCours->pBuffer,pMsg->pBuffer,pMsg->Lng);
				Res = cLdbpcOk;	
			}
		}
		else
		{
			// Memorisation de la structure
			m_pMsgEnCours = pMsg;
			Res = cLdbpcOk;	
		}
	}
	return Res;
}

//--------------------------------------------------------------------------
//--------------- Implementation de la classe tcFluxNIP --------------------
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// Constructeurs
//--------------------------------------------------------------------------
tcFluxNIP::tcFluxNIP():tcFlux()
{
	m_pUserCBAction		= NULL;
}

tcFluxNIP::tcFluxNIP(tcCanal * pCanal, tInfoFlux * pIflux)
 : tcFlux(pCanal, pIflux)
{
	m_pUserCBAction		= pIflux->pCbActionNIP;
}

//--------------------------------------------------------------------------
//	Destructeur
//--------------------------------------------------------------------------
tcFluxNIP::~tcFluxNIP()
{

}

//--------------------------------------------------------------------------
// Appel de la fonction callback personalisee
//--------------------------------------------------------------------------
BOOL tcFluxNIP::Action(tAddress * Adr,tMsg ** pMsg)
{
	BOOL bRes = cFalse;

	// Verification de l'existance d'une fonction callback personalisee
	if(m_pUserCBAction && Adr && (*pMsg) && (*pMsg)->pBuffer)
	{
		// Appel de la fonction callback personalisee
		m_pUserCBAction(Adr, pMsg);
		bRes = cTrue;	
	}
	return bRes;
}

//--------------------------------------------------------------------------
//--------------- Implementation de la classe tcFluxNIC --------------------
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// Constructeurs
//--------------------------------------------------------------------------
tcFluxNIC::tcFluxNIC():tcFlux()
{
	m_pUserCBAction		= NULL;
}

tcFluxNIC::tcFluxNIC(tcCanal * pCanal, tInfoFlux * pIflux)
 : tcFlux(pCanal, pIflux)
{
	m_pUserCBAction		= pIflux->pCbActionNIC;
}

//--------------------------------------------------------------------------
//	Destructeur
//--------------------------------------------------------------------------
tcFluxNIC::~tcFluxNIC()
{

}