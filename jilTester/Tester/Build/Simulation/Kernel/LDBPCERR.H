//**************************************************************************
// COMPOSANT : ERREUR
// FONCTION : GESTION DES ERREURS
//
// Ce logiciel est la propriete de JCI :
// ---------------------------------------
// Il ne peut etre reproduit ni communique en totalite ou partie sans
// son autorisation ecrite.
//
// ------------------------------------------------------------------------
// Ce fichier doit etre inclus dans les composants utilisant les macros,
// types et fonctions definis par le composant LDBPC_ERREUR.
// Le fichier LDBPC_ERREUR.h doit contenir toute et uniquement
// l'information necessaire au programmeur pour utiliser le composant
// LDBPC_ERREUR.
// En particulier c'est ce fichier LDBPCERR.h qui contient l'historique
// et la documentation du composant dans son ensemble.
// ------------------------------------------------------------------------
// Reference a la documentation :
//
// ------------------------------------------------------------------------
// Presentation generale du composant :
//
// ------------------------------------------------------------------------
// Nom et initiales des developpeurs :
//
// ------------------------------------------------------------------------
// Historique du composant LDBPC_ERREUR dans son ensemble
// (initiales, date, modification)
//
// cree par :
//
// ------------------------------------------------------------------------
// Historique du fichier LdbpcErr.h
// (initiales, date, modification)
//
//***************************************************************************

//---- Definition pour mono-inclusion -----
#ifdef I_LDBPC_ERREUR
#else
#define I_LDBPC_ERREUR 1

#include "deftypes.h"
#include "ldbpc.h"
#include "LDBPCErc.h"

#ifdef LDBPC_TESTU
#include "testeur.h"
#endif
/*------------------------------------------------------------------------*/
/*-------  Declaration des macros exportees par ce composant  ------------*/
/*------------------------------------------------------------------------*/
/* (Com: 3 lettres identifiant ce composant)
#define mComNomMacro   (DefinitionDeLaMacro)
*/
class tcErreur;

#define mLDBPCErreur(x)  tcErreur::GererErreur(x,__LINE__,__FILE__)

#ifdef LDBPC_TESTU
    #define mLDBPCError(x)  mTSTCheckError((char*)pECStringError[x])
    #define mLDBPCErrorText(x,txt)  mTSTCheckErrorText((char*)pECStringError[x],txt)
#else
    #define mLDBPCError(x) tcErreur::SetError(x,__LINE__,__FILE__)
    #define mLDBPCErrorText(x,txt)  tcErreur::SetErrorText(x,txt,__LINE__,__FILE__)
#endif

#ifdef _DEBUG
#define mLDBPCAssert(cond)  if(!((BOOL)cond)) {DebugBreak();}
#else
	#define mLDBPCAssert(cond)
#endif

/*------------------------------------------------------------------------*/
/*-------  Definition des types exportes par ce composant  ---------------*/
/*------------------------------------------------------------------------*/
/* (Com: 3 lettres identifiant ce composant)
typedef ...   tComNomType;
*/

#define	cMediaErrASSERT				0x01
#define	cMediaErrAffichage			0x02
#define	cMediaErrFichier			0x04


/*------------------------------------------------------------------------*/
/*-------  Fonctions exportees (par ordre alphabetique)  -----------------*/
/*------------------------------------------------------------------------*/
/*
extern tTypeRetour ComNomFonction(tTypeArgument NomArgument,  ...);
*/

class tcErreur
{
public :

    static	tLDBPCStatut	GererErreur(tLDBPCStatut ErreurId, int Ligne, char * pNomFichier);
    static	void			GererErreur(char * pTextErreur, int Ligne, char * pNomFichier);
    static	void			SetMediaErreur(U8 MediaErr);
    static	void			SetFileErreur(const char * File);
    static	void	        SetError(U32 ErreurId, int Ligne, char * pNomFichier);
    static	void            SetErrorText(U32 ErrorCode, char * pTextError, int Ligne, char * pNomFichier);

    // Ajouter une trace d'erreur
    static	void AddTraceErreur(char * TextErreur);

    // Traitement de l'erreur
    static	void ProcessErreur(char * TextErreur);


    static	U8 s_TypeMedia;
    static	char s_Fichier[500];

};


#endif   // (I_LDBPC_ERREUR) fin de l'inclusion conditionnelle de Types.h
