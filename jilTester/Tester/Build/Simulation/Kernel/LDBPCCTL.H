//**************************************************************************
// COMPOSANT : LdbpcCtl
// FONCTION : LdbpcCtl
//
// Ce logiciel est la propriete de JCI :
// ---------------------------------------
// Il ne peut etre reproduit ni communique en totalite ou partie sans
// son autorisation ecrite.
//
// ------------------------------------------------------------------------
// Ce fichier doit etre inclus dans les composants utilisant les macros,
// types et fonctions definis par le composant LdbpcCtl.
// Le fichier LdbpcCtl.h doit contenir toute et uniquement
// l'information necessaire au programmeur pour utiliser le composant
// LdbpcCtl.
// En particulier c'est ce fichier LdbpcCtl.h qui contient l'historique
// et la documentation du composant dans son ensemble.
// ------------------------------------------------------------------------
// Reference a la documentation :
//
// ------------------------------------------------------------------------
// Presentation generale du composant :
//
// ------------------------------------------------------------------------
// Nom et initiales des developpeurs :	GUILLEN	GG
//
// ------------------------------------------------------------------------
// Historique du composant LdbpcCtl dans son ensemble
// (initiales, date, modification)
//
// cree par :	GG : 09/05/2000
//
// ------------------------------------------------------------------------
// Historique du fichier LdbpcCtl.h
// (initiales, date, modification)
//
//***************************************************************************

//-------------------------------------------------------------------------
//----- Inclusion de fichiers .h utiles a l'expansion de celui-ci -------
//-------------------------------------------------------------------------
// #include "fichier.h"
#include "Array.h"
#include "Ldbpc.h"			// Defini les types et constantes de bases
#include "LdbpcTem.h"	


//---- Definition pour mono-inclusion -----
#if !defined(I_LdbpcCtl)
#define I_LdbpcCtl

//-------------------------------------------------------------------------
//------ Declaration des constantes exportees par ce composant ----------
//-------------------------------------------------------------------------
//(Com: 3 lettres identifiant ce composant)
//#define cComNomConstante ValeurDeLaConstante

//--------------------------------------------------------------------------
//------- Declaration des macros exportees par ce composant --------------
//--------------------------------------------------------------------------
// (Com: 3 lettres identifiant ce composant)
// #define mComNomMacro (DefinitionDeLaMacro)

//--------------------------------------------------------------------------
//------- Definition des types exportes par ce composant -----------------
//--------------------------------------------------------------------------
// (Com: 3 lettres identifiant ce composant)
// typedef ... tComNomType;
class tcCtrl;
typedef tcArray<tcCtrl *> tcTabCtrl;

//--------------------------------------------------------------------------
//------- Declaration des variables exportees par ce composant -----------
//--------------------------------------------------------------------------
// (Com: 3 lettres identifiant ce composant)
// extern tType ComNomVariable;
// extern tType* pComNomVariable;
//--------------------------------------------------------------------------
//------- Donnees Constantes exportees par ce composant ------------------
//--------------------------------------------------------------------------
// (Com: 3 lettres identifiant ce composant)
//extern const tType ComNomVariable;
// Nota:
// Pour les variables qui peuvent etre modifiees par LdbpcCtl mais non
// par les composants utilisateurs, on utilisera une definition conditionnel
//
// #ifdef LdbpcCtl
// extern tType ComNomVariable;
// #else
// extern const tType ComNomVariable;
// #endif
//--------------------------------------------------------------------------
//------------------------- Fonctions exportees ----------------------------
//--------------------------------------------------------------------------
// extern tTypeRetour NomFonction(tTypeArgument NomArgument, ...);


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class tcCtrl
{
public:
    // Constructeur
    tcCtrl(tCtrl Ctrl, tChannel RefCan, tDelay Duree, tDLLType Type);
    // Destructeur
    virtual ~tcCtrl();
    tcTempoParam1<S32> Tempo;
private:

    tCtrl	m_Ctrl;			// Controle
    tChannel	m_RefCanal;		// Reference du Canal
    tDelay	m_Duree;		// Duree de transmission du controle
    S32	m_RefEvt;		// Reference de l'evenement lie au controle
    tDLLType m_Type;	// Type du controle

public:

    // Lecture du Controle
    inline tCtrl LireCtrl() const		{ return m_Ctrl; }
    // Lecture du Controle
    inline BOOL CtrlEntree() const	{ return (BOOL)mCtrlEntree(m_Type); }
    inline BOOL CtrlSortie() const	{ return (BOOL)mCtrlSortie(m_Type); }

    // Lecture de la eference du Canal
    inline tChannel LireRefCanal() const	{ return m_RefCanal; }
    // Lecture de la Duree de transmission du controle
    inline tDelay LireDuree() const		{ return m_Duree; }
    // Lecture de la Reference de l'evenement lie au controle
    inline S32 LireRefEvt() const	{ return m_RefEvt; }

    // Ecriture du Controle
    inline void EcrireCtrl(tCtrl Ctrl) 			{ m_Ctrl = Ctrl; }
    // Ecriture de la eference du Canal
    inline void EcrireRefCanal(tChannel RefCan) 	{ m_RefCanal = RefCan; }
    // Ecriture de la Duree de transmission du controle
    inline void EcrireDuree(tDelay Duree) 		{ m_Duree = Duree; }
    // Ecriture de la Reference de l'evenement lie au controle
    inline void EcrireRefEvt(S32 Evt) 		{ m_RefEvt = Evt; }
};

#endif // fin de l'inclusion conditionnelle de LdbpcCtl.h

