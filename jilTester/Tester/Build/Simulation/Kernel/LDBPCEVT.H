//**************************************************************************
// COMPOSANT : LDBPCEvt
// FONCTION :  Interface pour les classes de donnees
//
// Ce logiciel est la propriete de JCI :
// ---------------------------------------
// Il ne peut etre reproduit ni communique en totalite ou partie sans
// son autorisation ecrite.
//
// ------------------------------------------------------------------------
// Ce fichier doit etre inclus dans les composants utilisant les macros,
// types et fonctions definis par le composant LDBPCEvt.
// Le fichier LDBPCEvt.h doit contenir toute et uniquement
// l'information necessaire au programmeur pour utiliser le composant
// LDBPCEvt.
// En particulier c'est ce fichier LDBPCEvt.h qui contient l'historique
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
// Historique du composant LDBPCEvt dans son ensemble
// (initiales, date, modification)
//
// cree par :	GG : 13/04/2000
//
// ------------------------------------------------------------------------
// Historique du fichier LDBPCEvt.h
// (initiales, date, modification)
//
//***************************************************************************

//-------------------------------------------------------------------------
//----- Inclusion de fichiers .h utiles a l'expansion de celui-ci -------
//-------------------------------------------------------------------------

#include "Ldbpc.h"			// Defini les types et constantes de bases
#include "Array.h"

//---- Definition pour mono-inclusion -----

#if !defined(I_LDBPCEvt)
#define I_LDBPCEvt

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

class tcEvt;
typedef	tcArray<tcEvt *>	tcEvtArray;

//--------------------------------------------------------------------------
//--------------------- Interface de la classe tcEvt ----------------------
//--------------------------------------------------------------------------

class tcEvt
{
public:
    // Constructeur
    tcEvt(tDLLType Type, tpVoid pCallBackVoid = NULL
            , tpParam pParamCallBack = NULL);

    // Destruction
    virtual ~tcEvt();

    static U32 m_NbEvt;	// Nombre d'evenement

    // Lire le type  de l'evenement
    inline const tDLLType LireType() const { return m_Type; }

    // Ecrire le type  de l'evenement
    inline tDLLType&		EcrireType()	{ return m_Type; }

    // Emettre un evenement
    void SignalerEvt(S32 ref);

    void SetCallBack(tpVoid pVoid, tpParam pParam);

protected:
    tDLLType	m_Type;			// Type de l'evenement
    tpVoid m_pCallBackVoid;		// pointeur de la fonction callback
    tpParam m_pParamCallBack;	// pointeur de la fonction callback
};

//--------------------------------------------------------------------------
//--------------------- Interface de la classe tcTabEvt -------------------
//--------------------------------------------------------------------------

class tcTabEvt : public tcEvtArray
{
public:
    // Constructeur
    tcTabEvt();

    // Destruction
    virtual ~tcTabEvt();
};



#endif // fin de l'inclusion conditionnelle de LDBPCEvt.h
