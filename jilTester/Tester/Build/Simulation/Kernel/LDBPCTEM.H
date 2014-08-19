//**************************************************************************
// COMPOSANT : LDBPC_TEMPO
// FONCTION : LDBPC_TEMPO
//
// Ce logiciel est la propriete de JCI :
// ---------------------------------------
// Il ne peut etre reproduit ni communique en totalite ou partie sans
// son autorisation ecrite.
//
// ------------------------------------------------------------------------
// Ce fichier doit etre inclus dans les composants utilisant les macros,
// types et fonctions definis par le composant LDBPC_TEMPO.
// Le fichier LDBPCTem.h doit contenir toute et uniquement
// l'information necessaire au programmeur pour utiliser le composant
// LDBPC_TEMPO.
// En particulier c'est ce fichier LDBPCTem.h qui contient l'historique
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
// Historique du composant LDBPC_TEMPO dans son ensemble
// (initiales, date, modification)
//
// GG : 07/04/2000 : Creation
// GG : 21/08/2001 : Optimisation et Generalisation
//
// ------------------------------------------------------------------------
// Historique du fichier LDBPCTem.h
// (initiales, date, modification)
//
//***************************************************************************

//-------------------------------------------------------------------------
//----- Inclusion de fichiers .h utiles a l'expansion de celui-ci ---------
//-------------------------------------------------------------------------

//---- Definition pour mono-inclusion -----
#if !defined(I_LDBPC_TEMPO)
#define I_LDBPC_TEMPO	1
#include "Ldbpc.h"			// Defini les types et constantes de bases

//-------------------------------------------------------------------------
//------ Declaration des constantes exportees par ce composant ------------
//-------------------------------------------------------------------------
//(Com: 3 lettres identifiant ce composant)
//#define cComNomConstante ValeurDeLaConstante

#define		cTemUtilTim				0
#define		cTemUtilLap				1
#define		cTemUtilLdbpcFlux		2
#define		cTemUtilLdbpcTrame		3
#define		cTemUtilLdbpcCtrl		4
#define		cTemUtilLdbpcPar		5
#define		cTemUtilLdbpcMsgSeg		6

#define		cTemPeriodique			cTrue
#define		cTemNonPeriodique		cFalse

#define		cTemTypeGen				0
#define		cTemTypeCB1				1
#define		cTemTypeCB2				2
#define		cTemTypeCB3				3

//--------------------------------------------------------------------------
//------- Declaration des macros exportees par ce composant ----------------
//--------------------------------------------------------------------------
// (Com: 3 lettres identifiant ce composant)
// #define mComNomMacro (DefinitionDeLaMacro)
//--------------------------------------------------------------------------
//------- Definition des types exportes par ce composant -------------------
//--------------------------------------------------------------------------
// (Com: 3 lettres identifiant ce composant)
// typedef ... tComNomType;


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class tcTempo
{
public:
    // Constructeur
    tcTempo();

    // Destructeur
    virtual ~tcTempo();

    // Donnee Membre publique et statique
    static U32 m_NbTempo;		// Nombre de tempo

    // Donnees Membres publiques

    BOOL	EstPeriodique ;		// periodique
    tDelay		Date ;				// Date d'écheance
    tDelay		Duree ;				// Duree de la tempo
    tcTempo *	Suivant;			// pointeur sur la tempo suivante
    BOOL	Actif;				// Armee

    // Fonction de traitement de la tempo
    virtual void Traiter()	= 0;
};

class tcTempoSimple : public tcTempo
{
public:

    typedef void (*tpCB)();

    // Constructeur
tcTempoSimple() : tcTempo() {pCallBack = NULL;}

    tpCB pCallBack;		// CallBack

    // Destructeur
    virtual ~tcTempoSimple() {}

    virtual void Traiter()
    {
        if(pCallBack)
            (*(pCallBack))();
    }
};

template <class TYPE>
class tcTempoParam1 : public tcTempo
{
public:

    typedef void (*tpCB)(TYPE);

    // Constructeur
tcTempoParam1() : tcTempo() { Param = (TYPE)0; pCallBack = (tpCB)NULL; }

    // Destructeur
    virtual ~tcTempoParam1() {}

    TYPE	Param;		// Param utilsateur
    tpCB	pCallBack;	// CallBack

    virtual void Traiter()
    {
        if(pCallBack)
            (*(pCallBack))(Param);
    }
};

template <class TYPEObject, class TYPECallBack>
class tcTempoObjet : public tcTempo
{
public:

    // Constructeur
tcTempoObjet() : tcTempo() {
        pCallBack = (TYPECallBack)NULL;
        pObject	= (TYPEObject)NULL;
    }

    // Destructeur
    virtual ~tcTempoObjet() {}

    TYPECallBack	pCallBack;	// CallBack Utilisateur
    TYPEObject		pObject;	// Objet Utilisateur

    virtual void Traiter()
    {
        if(pCallBack)
            (*(pCallBack))(pObject);
    }
};

#endif // I_LDBPC_TEMPO
