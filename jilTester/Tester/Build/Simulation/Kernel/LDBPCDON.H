//**************************************************************************
// COMPOSANT : LDBPCDon
// FONCTION :  Interface pour le Module DONNEES.
//
// Ce logiciel est la propriete de JCI :
// ---------------------------------------
// Il ne peut etre reproduit ni communique en totalite ou partie sans
// son autorisation ecrite.
//
// ------------------------------------------------------------------------
// Ce fichier doit etre inclus dans les composants utilisant les macros,
// types et fonctions definis par le composant LDBPCDon.
// Le fichier LDBPCDon.h doit contenir toute et uniquement
// l'information necessaire au programmeur pour utiliser le composant
// LDBPCDon.
// En particulier c'est ce fichier LDBPCDon.h qui contient l'historique
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
// Historique du composant LDBPCDon dans son ensemble
// (initiales, date, modification)
//
// cree par :	GG : 14/04/2000
//
// ------------------------------------------------------------------------
// Historique du fichier LDBPCDon.h
// (initiales, date, modification)
//
//***************************************************************************

//-------------------------------------------------------------------------
//----- Inclusion de fichiers .h utiles a l'expansion de celui-ci -------
//-------------------------------------------------------------------------

#include "Ldbpc.h"			// Defini les types et constantes de bases
#include "LDBPCEvt.h"
#include "DLLCOM.h"			// Definit l'interface de la DLL 
#include "LdbpcErr.h"	// Definit l'interface des erreurs

//---- Definition pour mono-inclusion -----
#if !defined(I_LDBPCDon)
#define I_LDBPCDon

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
//--------------------------------------------------------------------------
//------- Declaration des variables exportees par ce composant -----------
//--------------------------------------------------------------------------
// (Com: 3 lettres identifiant ce composant)
// extern tType ComNomVariable;
// extern tType* pComNomVariable;
class tcDonnees;
extern tcDonnees Donnees;

//--------------------------------------------------------------------------
//------- Donnees Constantes exportees par ce composant ------------------
//--------------------------------------------------------------------------
// (Com: 3 lettres identifiant ce composant)
//extern const tType ComNomVariable;
// Nota:
// Pour les variables qui peuvent etre modifiees par LDBPCDon mais non
// par les composants utilisateurs, on utilisera une definition conditionnel
//
// #ifdef LDBPCDon
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

typedef struct
{
    S32 * pRef;
    tDLLType Type;
    tDLLTypeVal TypeVal;
    char * pNom;
    tDLLValeur ValInit;
    U32 TailleBit;
    char * pGroupe;
    tpVoid pCallBackVoid;
    tpParam pParamCallBack;
}tsDonnee;

//--------------------------------------------------------------------------
//------------------- Interface de la classe tcDonnees --------------------
//--------------------------------------------------------------------------

class tcDonnees
{
public:
    // ------------------------------------------------------------------------
    // Constructeur
    // ------------------------------------------------------------------------
    tcDonnees();
    // ------------------------------------------------------------------------
    // Destructeur
    // ------------------------------------------------------------------------
    virtual ~tcDonnees();

private:
    // ------------------------------------------------------------------------
    // Données Membres privées
    // ------------------------------------------------------------------------

    // Tableau des evenements
    tcTabEvt		m_TabEvt;
    // Pointeur de fonction CallBack pour tous les evenements en entree
    tpFunct1			m_pCBEvtEntrees;

    S32 * m_pTabUpdateData;
    U32 m_NbMaxData;

public:
    // ------------------------------------------------------------------------
    // Fonctions Membres publiques
    // ------------------------------------------------------------------------
    // Création d'une donnée
    tLDBPCStatut CreerDonnee(tsDonnee * pDonnee);
    tLDBPCStatut CreerDonnee(S32 *,char *,tDLLType,tDLLTypeVal,U32,U32,char *,tpVoid cb = NULL,tpParam p = NULL);
    tLDBPCStatut CreerDonnee(S32 *,char *,tDLLType,tDLLTypeVal,U32,U8*,char *,tpVoid cb = NULL,tpParam p = NULL);

    // Création d'un evenement pour toutes les entrees
    tLDBPCStatut CreerEvtEntrees(tpFunct1 pCallBackEvt);

    // Emettre d'un evenement en sortie
    tLDBPCStatut EmettreEvtSor(S32 Ref);

    // Lire une entree > 32bits
    tLDBPCStatut Lire(S32 Ref, U8 * pBuffer,
                      U32 * pTaille = NULL, tDelay * pDate= NULL);

    // Lire une entree < 32bits
    tLDBPCStatut Lire(S32 Ref, U32 * pValeur,
                      U32 * pTaille= NULL, tDelay * pDate= NULL);

    // Ecrire une donnee < 32bits
    tLDBPCStatut EcrireSortie(S32 Ref, U32 Valeur);

    // Ecrire une valeur (sortie) > 32bits
    tLDBPCStatut EcrireSortie(S32 Ref, U8 * pBuffer);

    // Lire la taille d'une donnee
    U32 LireTailleDonnee(S32 Ref);

    // Retourne cTrue si la donnee de reference Ref est de type Tableau
    BOOL SortieTypeBuffer(S32 Ref);

    // Lire les evenements en entree
    tLDBPCStatut LireEvtEntrees();

    // Emettre d'un evenement en entree
    tLDBPCStatut EmettreEvtEnt(S32 Ref);

    void SetCallBack(S32 Ref, tpVoid pVoid, tpParam pParam);
};

#endif // fin de l'inclusion conditionnelle de LDBPCDon.h
