//**************************************************************************
// COMPOSANT : LdbpcRes
// FONCTION :  Interface pour le Module RESSOURCES.
//
// Ce logiciel est la propriete de JCI :
// ---------------------------------------
// Il ne peut etre reproduit ni communique en totalite ou partie sans
// son autorisation ecrite.
//
// ------------------------------------------------------------------------
// Ce fichier doit etre inclus dans les composants utilisant les macros,
// types et fonctions definis par le composant LdbpcRes.
// Le fichier LdbpcRes.h doit contenir toute et uniquement
// l'information necessaire au programmeur pour utiliser le composant
// LdbpcRes.
// En particulier c'est ce fichier LdbpcRes.h qui contient l'historique
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
// Historique du composant LdbpcRes dans son ensemble
// (initiales, date, modification)
//
// cree par :	GG : 20/04/2000
//
// ------------------------------------------------------------------------
// Historique du fichier LdbpcRes.h
// (initiales, date, modification)
//
//***************************************************************************



//---- Definition pour mono-inclusion -----

#ifndef I_LdbpcRes
#define I_LdbpcRes
//-------------------------------------------------------------------------
//----- Inclusion de fichiers .h utiles a l'expansion de celui-ci -------
//-------------------------------------------------------------------------
#include "Ldbpc.h"			// Defini les types et constantes de bases
#include "LdbpcTra.h"		// Definit l'interface des classes de Trames
#include "LdbpcCan.h"		// Definit l'interface de la classe de Canal
#include "LdbpcFlu.h"		// Definit l'interface des classes de Flux
#include "LdbpcCtl.h"		// Defini la classe gerant les controles
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

class tcRessources;
extern tcRessources Ressources;

//--------------------------------------------------------------------------
//------- Donnees Constantes exportees par ce composant ------------------
//--------------------------------------------------------------------------
// (Com: 3 lettres identifiant ce composant)
//extern const tType ComNomVariable;
// Nota:
// Pour les variables qui peuvent etre modifiees par LdbpcRes mais non
// par les composants utilisateurs, on utilisera une definition conditionnel
//
// #ifdef LdbpcRes
// extern tType ComNomVariable;
// #else
// extern const tType ComNomVariable;
// #endif
//--------------------------------------------------------------------------
//------------------------- Fonctions exportees ----------------------------
//--------------------------------------------------------------------------
// extern tTypeRetour NomFonction(tTypeArgument NomArgument, ...);

// Traitement standard d'un flux inititie (ref : flux)
extern void CallBackFiStd(S32 ref);

// Traitement standard d'un flux non inititie produit (ref : evt)
extern void CallBackFnipStd(S32 ref);

// Traitement standard d'un flux non inititie consomme (ref : evt)
extern void CallBackFnicStd(S32 ref);

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//--------------------------------------------------------------------------
//------------------- Interface de la classe tcRessources -----------------
//--------------------------------------------------------------------------
class tcRessources
{
public:
    BOOL LireModeTrame(S32 RefTrame, char * Mode);
    tLDBPCStatut EcrireDureeTrame(tAddress Adresse,S32 RefFlux, tDelay Duree);
    void Initialiser();
    // Constructeur
    tcRessources();
    // Destructeur
    virtual ~tcRessources();


    tcTabCanal		m_TabCanal;			// Tableau de canaux
    tcTabFlux		m_TabFlux;			// Tableau de flux
    tcTabTrame		m_TabTrame;			// Tableau de trames
    tCallBackCanal *	m_pCBCanalEnCours;	// Canal en cours de creation
    tcTabCtrl		m_TabCtrl;			// Tableau de Controle

    // Create a LDBPC Channel
    tLDBPCStatut CreateChannel(tCallBackCanal * pStructCallBack);

    // Create a CAN for XCAN Channel
    tLDBPCStatut CreateChannelXCAN(tXCanChannel * pStruct);

    // Création d'un controle
    tLDBPCStatut CreerControle(S32 * pRefCtrl, tChannel refCan, char * pNom, tCtrl ctrl
                               , tDelay duree, tDLLType Type);

    // Création d'un flux
    tLDBPCStatut CreerFlux(tInfoFlux * Flux);

    // Création d'une trame generique
    tLDBPCStatut CreateFrame(tInfoTrame * pInfoTrame);
    tLDBPCStatut CheckFrame(tInfoTrame * pInfoTrame);
    tLDBPCStatut CreateDataFrame(tInfoBuildFrame * pBuildFrame);
    tLDBPCStatut NewDataFrameName(tInfoBuildFrame * pBuildFrame);
    void         DeleteDataFrameName(tInfoBuildFrame * pBuildFrame);
    tLDBPCStatut BuildFrame(tInfoBuildFrame * pBuildFrame);
    void SetCallBackNIC(tInfoBuildFrame * pBuildFrame);
    void SetCallBackNIP(tInfoBuildFrame * pBuildFrame);

    // Création d'une sortie < 32bits
    tLDBPCStatut CreerSortie(S32 * pRef, S32 refTrame, char * pNom
                             , U32 tailleBit, U32 valeurInit, U32 position);

    // Création d'une sortie > 32bits
    tLDBPCStatut CreerSortie(S32 * pRef, S32  refTrame, char * pNom
                             , U32 tailleBit,	U8 * bufferInit, U32 position);

    // Création d'une entree < 32bits
    tLDBPCStatut CreerEntree(S32 * pRef, S32 refTrame, char * pNom
                             , U32 tailleBit, U32 valeurInit, U32 position) ;

    // Création d'une entree > 32bits
    tLDBPCStatut CreerEntree(S32 * pRef, S32 refTrame, char * pNom
                             , U32 tailleBit, U8 * bufferInit, U32 position);

    // Création d'une entree/sortie < 32bits
    tLDBPCStatut CreerEntSor(S32 * pRef, S32 refTrame, char * pNom
                             , U32 tailleBit, U32 valeurInit, U32 position) ;

    // Création d'une entree/sortie > 32bits
    tLDBPCStatut CreerEntSor(S32 * pRef, S32 refTrame, char * pNom
                             , U32 tailleBit, U8 * bufferInit, U32 position);

    // Attacher une entree ou une sortie a une trame avec sa position dans la trame
    tLDBPCStatut AttacherDonnee(S32 RefES, S32 RefTrame, U32 Position);

    // Attacher un flux a un canal
    tLDBPCStatut AttacherFlux(S32 RefFlux, tChannel refCan);

    // Attacher une trame a un flux initie
    tLDBPCStatut AttacherTrame(S32 refTrame, S32  RefFlux, tDelay duree);

    // Attacher une trame a un flux Non Initie Consommee
    tLDBPCStatut AttacherTrame(S32 refTrame, S32 RefFlux, char mode
                               , tDelay periode, tDelay phase, tpCallBackRxWithAddr cbTrameNIC);

    // Attacher une trame a un flux Non Initie Produit
    tLDBPCStatut AttacherTrame(S32 refTrame, S32 RefFlux, char mode
                               , tDelay periode, tDelay phase, tpCallBackStatusAddr cbTrameNIP);

    // Lire une reference de trame par rapport au flux
    tLDBPCStatut LireRefFlux(tChannel refCan, tLdbpcTypeFlux TypeFlux, S32 * pRefFlux);

    // Lire une reference de trame par rapport au flux
    tLDBPCStatut LireRefTrame(S32 RefFlux, tAddress adresse, S32 * refTrame);

    // Lire une reference de trame par rapport au canal
    tLDBPCStatut LireRefTrame(tChannel refCan, tLdbpcTypeFlux TypeFlux, tAddress adresse
                              , S32 * pRefTrame);
    // Lire une trame
    tLDBPCStatut LireTrame(S32 refTrame, tMsg * Msg);

    // Lire la taille du buffer de la trame courante d'un flux initie
    U16 LireTailleTrameCourante(S32 RefFlux);

    // Lire la trame courante d'un flux initie
    tLDBPCStatut LireTrameCourante(S32 RefFlux, tAddress  * adresse, tMsg ** msg);

    // Lire l'etat de controle du canal
    tLDBPCStatut LireEtatControle(tChannel refCan, char * etat);

    // Ecrire une trame
    tLDBPCStatut EcrireTrame(S32 refTrame, tMsg * msg);

    // Ecrite la trame courante d'un flux
    tLDBPCStatut EcrireTrameCourante(S32 RefFlux, tAddress adresse, tMsg * msg);

    // Ecrire l'etat de controle du canal
    tLDBPCStatut EcrireEtatControle(tChannel refCan, char etat);

    // Chargement du Nom de groupe
    tLDBPCStatut ChargerNomGroupe(S32 RefTrame, char ** pNomGroupe,char * pGroupe = NULL);

    // Acces au format d'un canal
    void Formater(tChannel RefCan,U8 Format);
    U8 GetFormat(S32 RefTrame);

    // Demande de le modification forcée de la trame
    void EcrireDmdeMoficationTrame(S32 RefTrame, BOOL flag);

    // Lecture de l'activation de la modification forcée de la trame
    BOOL LireDmdeMoficationTrame(S32 RefTrame);

    // ------------------------------------------------------------------------

    // Fin d'action d'un Flux Initie vers un canal
    void FinActionFi(S32 RefFlux);

    // Emission d'un Flux Initie vers un canal
    void ActionFi(tLdbpcTypeFlux Type, tChannel canal, tAddress adresse, tMsg* msg);

    // Emission Standard du message courant d'un Flux Initie vers un canal
    void ActionFiStd(tLdbpcTypeFlux Type, tChannel canal);

    // Preparation d'emission d'un Flux Non Initie Produit vers un canal
    void PreparerActionFnip(tChannel canal, tAddress adresse, tMsg* msg);

    // Emission d'un Flux Non Initie vers le LAP
    void ActionFni(S32 evt, tLdbpcTypeFlux Type);

    // Emission Standard d'un Flux Non Initie vers le LAP
    void ActionFniStd(tChannel refCan, S32 refTrame, tLdbpcTypeFlux Type);

    // Autoriser les Flux Non Initie vers le LAP
    void Autoriser(tChannel canal, BOOL callbackAutorise);

    // Emettre un controle sur un canal
    void Controler(tChannel canal,tCtrl ctrl);

    // Emettre un controle standard sur un canal
    void ControleStd(tChannel canal,tCtrl ctrl);

    // Emission du controle vers le LDS
    void FinControle(S32 RefCtrl);

    // Lire la reference de controle par rapport au canal et au controle
    tLDBPCStatut LireRefCtrl(S32 * pRefCtrl,tChannel canal,tCtrl ctrl);

    // Emission du controle vers le LAP
    void CBControler(S32 pRefCtrl);

    // Fin d'une tempo (pour les trames non initiées)
    void FinTempo(S32 refTrame);

    // Retourne la structure du canal en cours de construction
    tCallBackCanal * GetStructCallBackCanal() const { return(m_pCBCanalEnCours); }

    // Retourne le nom du canal
    char * GetChannelName(S32 RefCan);

    void CreationDonneesInternes(void);
    void EntrerVeille(void);
    void SortirVeille(void);

    char * GetXCANCurrentConfig();
    void SetXCANCurrentConfig(char * ConfigName);

private:
    // Desttruction des tableaux
    void Destruction();

    // Recherche la reference du controle à partir de la reference d'evenement
    tLDBPCStatut RechercherCtrl(S32 RefEvt, S32 * RefCtrl);
    S32 m_RefUCEenVeille;
};

#endif // fin de l'inclusion conditionnelle de LdbpcRes.h
