//**************************************************************************
// COMPOSANT : LDBPC_MAINLEV
// FONCTION : LDBPC_MAINLEV
//
// Ce logiciel est la propriete de JCI :
// ---------------------------------------
// Il ne peut etre reproduit ni communique en totalite ou partie sans
// son autorisation ecrite.
//
// ------------------------------------------------------------------------
// Ce fichier doit etre inclus dans les composants utilisant les macros,
// types et fonctions definis par le composant LDBPC_MAINLEV.
// Le fichier LDBPCTim.h doit contenir toute et uniquement
// l'information necessaire au programmeur pour utiliser le composant
// LDBPC_MAINLEV.
// En particulier c'est ce fichier MainLev.h qui contient l'historique
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
// Historique du composant LDBPC_TIMER dans son ensemble
// (initiales, date, modification)
//
// cree par :	GG : 10/04/2000
//
// ------------------------------------------------------------------------
// Historique du fichier LDBPCTim.h
// (initiales, date, modification)
//
//***************************************************************************

//-------------------------------------------------------------------------
//----- Inclusion de fichiers .h utiles a l'expansion de celui-ci ---------
//-------------------------------------------------------------------------


//---- Definition pour mono-inclusion -----
#if !defined(I_LDBPC_MAINLEV)
#define I_LDBPC_MAINLEV	1

//-------------------------------------------------------------------------
//------ Declaration des constantes exportees par ce composant ------------
//-------------------------------------------------------------------------
//(Com: 3 lettres identifiant ce composant)
//#define cComNomConstante ValeurDeLaConstante

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


int StartLDBPC(void);
void StopLDBPC(void);

#endif // I_LDBPC_MAINLEV
