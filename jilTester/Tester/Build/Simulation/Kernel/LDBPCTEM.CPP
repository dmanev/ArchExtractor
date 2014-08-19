//**************************************************************************
// COMPOSANT : LDBPC_TEMPO
// FONCTION : TEMPORISATION
//
// Ce logiciel est la propriete de JCI :
// ---------------------------------------
// Il ne peut etre reproduit ni communique en totalite ou partie sans
// son autorisation ecrite.
//
// ------------------------------------------------------------------------
// Definition des fonctions exportees par le composant LDBPC_TEMPO :
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
// Historique du fichier LDBPCTem.cpp:
// -------------------------------------
// (initiales, date, modification)
//
// cree par :	GG : 07/04/2000 : Creation
//
//
//***************************************************************************

#define LDBPC_TEMPO "LDBPC_TEMPO"

//--------------------------------------------------------------------------
//---------------- Inclusion de fichiers (systeme et librairies) -----------
//--------------------------------------------------------------------------

#include "Ldbpc.h"		// Defini les types et constantes de bases
#include "LDBPCTem.h"	// Defini l'interface des classes tcTempo, tcTempoCB2 et tcTempoCB1

//--------------------------------------------------------------------------
//------- Inclusion des definitions des autres composants utiles -----------
//--------------------------------------------------------------------------
// #include <AUTRE_COMPOSANT.h>
#include "LDBPCErr.h"	
//--------------------------------------------------------------------------
//------- Declaration des constantes locales a ce composant ----------------
//--------------------------------------------------------------------------
// #define cNomConstante ValeurDeLaConstante
//--------------------------------------------------------------------------
//------- Declaration des macros locales a ce composant --------------------
//--------------------------------------------------------------------------
// #define mNomMacro (DefinitionDeLaMacro)
//--------------------------------------------------------------------------
//------- Definition des types locaux a ce composant -----------------------
//--------------------------------------------------------------------------
// typedef ... tNomType;

//--------------------------------------------------------------------------
//------- Variables locales a ce composant-----------------------------------
//--------------------------------------------------------------------------
// static tType NomVariable;
// static tType* pNomVariable;
//--------------------------------------------------------------------------
//------- Donnees Constantes locales a ce composant ------------------------
//--------------------------------------------------------------------------
// static const tType NomVariable;
//--------------------------------------------------------------------------
//------- Variables exportees par ce composant -----------------------------
//--------------------------------------------------------------------------
// tType ComNomVariable; (Com: 3 lettres identifiant ce composant)
// tType* pComNomVariable;
//--------------------------------------------------------------------------
//------- Donnees Constantes exportees par ce composant --------------------
//--------------------------------------------------------------------------
// const tType ComNomVariable; (Com: 3 lettres identifiant ce composant)
//--------------------------------------------------------------------------
//---------------------------- Fonctions locales ---------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//------------------------- Fonctions exportees ----------------------------
//--------------------------------------------------------------------------

U32	tcTempo::m_NbTempo = 0;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tcTempo::tcTempo()
{
	m_NbTempo++;

	Date = 0;
	Duree = 0;
	EstPeriodique = cTemNonPeriodique;
	Suivant = (tcTempo*)NULL;
	Actif = cFalse;
}

tcTempo::~tcTempo()
{
	m_NbTempo--;
}