//**************************************************************************
// COMPOSANT : LDBPCEvt
// FONCTION : Implementation des classes de donnees 
//
// Ce logiciel est la propriete de JCI :
// ---------------------------------------
// Il ne peut être reproduit ni communique en totalite ou partie sans
// son autorisation ecrite.
//
// ------------------------------------------------------------------------
// Definition des fonctions exportees par le composant LDBPCEvt :
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
// Historique du fichier LDBPCEvt.c:
// -------------------------------------
// (initiales, date, modification)
//
// cree par :	GG : 13/04/2000
//
//
//***************************************************************************

#define LDBPCEvt "LDBPCEvt"

//--------------------------------------------------------------------------
//---------------- Inclusion de fichiers (système et librairies -----------
//--------------------------------------------------------------------------

#include "Ldbpc.h"			// Defini les types et constantes de bases
#include "LDBPCEvt.h"
#include "LdbpcErr.h"

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
//--------------- Implementation de la classe tcEvt -----------------------
//--------------------------------------------------------------------------

U32 tcEvt::m_NbEvt = 0;

//--------------------------------------------------------------------------
// Constructeur
//--------------------------------------------------------------------------
tcEvt::tcEvt(tDLLType Type, tpVoid pCallBackVoid, tpParam pParamCallBack) 
{
	// Initialisation du type
	m_Type = Type;
	SetCallBack(pCallBackVoid, pParamCallBack);
	m_NbEvt++;
}

//--------------------------------------------------------------------------
// Destructeur
//--------------------------------------------------------------------------
tcEvt::~tcEvt()
{
	m_NbEvt--;
}

//--------------------------------------------------------------------------
// Initialisation de la fonction CallBack
//--------------------------------------------------------------------------
void tcEvt::SetCallBack(tpVoid pCallBackVoid,tpParam pParamCallBack) 
{
	m_pCallBackVoid = pCallBackVoid;
	m_pParamCallBack = pParamCallBack;
}

//--------------------------------------------------------------------------
// Emettre un evenement
//--------------------------------------------------------------------------
void tcEvt::SignalerEvt(S32 Ref)
{
	if(m_pCallBackVoid && m_pParamCallBack)
	{
		// Executer la fonction CallBack
		m_pCallBackVoid(m_pParamCallBack,(tpParam)&Ref);
	}
}

//--------------------------------------------------------------------------
//----------------- Implementation de la classe tcTabEvt ------------------
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// Constructeur
//--------------------------------------------------------------------------

tcTabEvt::tcTabEvt() : tcEvtArray()
{
	SetSize(0);
}

//--------------------------------------------------------------------------
// Destructeur
//--------------------------------------------------------------------------
tcTabEvt::~tcTabEvt()
{
	int Id;
	tcEvt * pEvt;
	
	// Detruire les evenements
	for(Id = 0 ;Id < GetSize(); Id++ )
	{
		pEvt = GetAt(Id);
		if( pEvt != NULL)
		{
			delete pEvt;
			pEvt = NULL;
		}
	}
	
	// Detruire le tableau d'evenements
	RemoveAll();
}
