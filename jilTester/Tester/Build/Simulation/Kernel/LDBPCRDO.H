//**************************************************************************
// COMPOSANT : LdbpcRdo
// FONCTION :  Interface pour les classes de trames
//
// Ce logiciel est la propriete de JCI :
// ---------------------------------------
// Il ne peut etre reproduit ni communique en totalite ou partie sans
// son autorisation ecrite.
//
// ------------------------------------------------------------------------
// Ce fichier doit etre inclus dans les composants utilisant les macros,
// types et fonctions definis par le composant LdbpcRdo.
// Le fichier LdbpcRdo.h doit contenir toute et uniquement
// l'information necessaire au programmeur pour utiliser le composant
// LdbpcRdo.
// En particulier c'est ce fichier LdbpcRdo.h qui contient l'historique
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
// Historique du composant LdbpcRdo dans son ensemble
// (initiales, date, modification)
//
// cree par :	GG : 20/04/2000
//
// ------------------------------------------------------------------------
// Historique du fichier LdbpcRdo.h
// (initiales, date, modification)
//
//***************************************************************************

//-------------------------------------------------------------------------
//----- Inclusion de fichiers .h utiles a l'expansion de celui-ci -------
//-------------------------------------------------------------------------

#include "Ldbpc.h"			// Defini les types et constantes de bases
#include "ldb.h"		// Defini les types et constantes de bases
//#include <afxtempl.h>
#include "Liste.h"			// Defini une classe template de Liste chainee

//---- Definition pour mono-inclusion -----

#if !defined(I_LdbpcRdo)
#define I_LdbpcRdo

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
#define mTrameSortie(x)	((x == 0x1) | (x == 0x3))
#define mTrameEntree(x)	(!mTrameSortie(x))

//--------------------------------------------------------------------------
//------- Definition des types exportes par ce composant -----------------
//--------------------------------------------------------------------------
// (Com: 3 lettres identifiant ce composant)
// typedef ... tComNomType;

class tcRefDonnee;
typedef tcListe<tcRefDonnee> tcListRefDonnee;

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
// Pour les variables qui peuvent etre modifiees par LdbpcRdo mais non
// par les composants utilisateurs, on utilisera une definition conditionnel
//
// #ifdef LdbpcRdo
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

//--------------------------------------------------------------------------
//------------------- Interface de la classe tcRefDonnee ------------------
//--------------------------------------------------------------------------
class tcRefDonnee
{
public:
    // ------------------------------------------------------------------------
    // Constructeurs
    // ------------------------------------------------------------------------
    tcRefDonnee();
    tcRefDonnee(S32 RefTrame,S32 RefDonnee,U32 Position,U32 TailleTrame);
    // ------------------------------------------------------------------------
    // Destructeur
    // ------------------------------------------------------------------------
    virtual ~tcRefDonnee();

protected:
    S32 m_RefTrame;		// Reference de la trame
    S32 m_RefDonnee;		// Reference de la donnee
    U32 m_Position;		// Position de la donnee dans la trame
    U8 * m_pBufferTemp;
    BOOL m_TypeTab;		// Type de la valeur
    S32	 m_TailleBit;	// Taille en bits de la valeur
    S32	 m_Valeur;		// Valeur

public:
    tcRefDonnee * m_pNext;

    // Lire la position du bit de poids fort de la donnee
    inline U32 LireMSB(void) const { return m_Position; }

    // Lire la position du bit de poids faible de la donnee
    U32 LireLSB(void);

    // Lecture de la donnee dans le message
    tLDBPCStatut Lire(tMsg * pMsg);

    // Ecriture de la donnee a partir du le message
    tLDBPCStatut Ecrire(tMsg * pMsg);

    static void CallBackEvents(tpParam pParam1, tpParam pParam2);

private:

    // Lit une valeur de 32 bit dans le buffer
    tLDBPCStatut LireValeur();

    // Lecture de la donnee et stockage dans un buffer
    tLDBPCStatut LireDonnee();

    // Decaler à gauche dans la trame
    tLDBPCStatut DecalerAGauche(U32 TailleBuf, U8 decalage);

    // Decaler le buffer à droite
    tLDBPCStatut DecalerADroite(U32 TailleBuf, U8 decalage);

    void Lecture(void);

};

#endif // fin de l'inclusion conditionnelle de LdbpcRdo.h
