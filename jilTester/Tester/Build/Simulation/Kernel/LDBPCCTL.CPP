// LdbpcCtl.cpp: implementation of the tcCtrl class.
//**************************************************************************
// COMPOSANT : LdbpcCtl
// FONCTION : implementation of the tcCtrl class.
//
// Ce logiciel est la propriete de JCI :
// ---------------------------------------
// Il ne peut être reproduit ni communique en totalite ou partie sans
// son autorisation ecrite.
//
// ------------------------------------------------------------------------
// Definition des fonctions exportees par le composant LdbpcCtl :
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
// Historique du fichier LdbpcCtl.cpp:
// -------------------------------------
// (initiales, date, modification)
//
// cree par :	GG : 09/05/2000
//
//
//***************************************************************************
#define LdbpcCtl "LdbpcCtl"
//--------------------------------------------------------------------------
//---------------- Inclusion de fichiers (système et librairies -----------
//--------------------------------------------------------------------------
#include "Ldbpc.h"			// Defini les types et constantes de bases
#include "LdbpcCtl.h"		// Defini la classe gerant les controles

//--------------------------------------------------------------------------
//------- Inclusion des definitions des autres composants utiles ---------
//--------------------------------------------------------------------------
// #include "AUTRE_COMPOSANT.h"
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
//--------------- Implementation de la classe tcCtrl ----------------------
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// Constructeurs
//--------------------------------------------------------------------------
tcCtrl::tcCtrl(tCtrl Ctrl, tChannel RefCan, tDelay Duree, tDLLType Type)
{
	m_Ctrl		= Ctrl;		// Controle
	m_RefCanal	= RefCan;	// Reference du Canal
	if(Type == cDLLSortie)
		m_Duree		= Duree;	// Duree de transmission du controle
	else
		m_Duree		= (tDelay)0;
	m_Type		= Type;		// type du Controle
}

//--------------------------------------------------------------------------
// Destructeur
//--------------------------------------------------------------------------
tcCtrl::~tcCtrl()
{

}
