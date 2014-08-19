//**************************************************************************
// COMPOSANT : Ldbpcpar
// FONCTION :  Interface pour les classes de trames
//
// Ce logiciel est la propriete de JCI :
// ---------------------------------------
// Il ne peut etre reproduit ni communique en totalite ou partie sans
// son autorisation ecrite.
//
// ------------------------------------------------------------------------
// Ce fichier doit etre inclus dans les composants utilisant les macros,
// types et fonctions definis par le composant Ldbpcpar.
// Le fichier Ldbpcpar.h doit contenir toute et uniquement
// l'information necessaire au programmeur pour utiliser le composant
// Ldbpcpar.
// En particulier c'est ce fichier Ldbpcpar.h qui contient l'historique
// et la documentation du composant dans son ensemble.
// ------------------------------------------------------------------------
// Reference a la documentation :
//
// ------------------------------------------------------------------------
// Presentation generale du composant : API de paramétrage du LDBPC
//
// ------------------------------------------------------------------------
// Nom et initiales des developpeurs :
//
//		Gilles	GUILLEN		GG
//
// ------------------------------------------------------------------------
// Historique du composant Ldbpcpar dans son ensemble
// (initiales, date, modification)
//
// v1.0	:	GG		: 20/04/2000	: Creation
// v1.3 :	GG      : 18/03/2002	: Mise à jour de l'API de paramétrage
//									  suite à l'ajout des couches CAN
//
//***************************************************************************

//-------------------------------------------------------------------------
//----- Inclusion de fichiers .h utiles a l'expansion de celui-ci -------
//-------------------------------------------------------------------------
#include "Ldbpc.h"			// Defini les types et constantes de bases
#include <string.h>
#include "Apidonne.h"			// Defini les types et constantes de bases

/*----- Definition pour mono-inclusion -----*/
#ifdef I_Ldbpcpar
#else
#define I_Ldbpcpar 1

//-------------------------------------------------------------------------
//------ Declaration des constantes exportees par ce composant ----------
//-------------------------------------------------------------------------
//(Com: 3 lettres identifiant ce composant)
//#define cComNomConstante ValeurDeLaConstante

#define cTESTDEBUG     1   //  Active fonction ErreurLDB

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
//--------------------------------------------------------------------------
//------- Donnees Constantes exportees par ce composant ------------------
//--------------------------------------------------------------------------
// (Com: 3 lettres identifiant ce composant)
//extern const tType ComNomVariable;
// Nota:
// Pour les variables qui peuvent etre modifiees par LdbpcLds mais non
// par les composants utilisateurs, on utilisera une definition conditionnel
//
// #ifdef LdbpcLds
// extern tType ComNomVariable;
// #else
// extern const tType ComNomVariable;
// #endif
//--------------------------------------------------------------------------
//------------------------- Fonctions exportees ----------------------------
//--------------------------------------------------------------------------


// ------------------------------------------------------------------------
// ------------------------ API pour le parametrage -----------------------
// ------------------------------------------------------------------------


// --------------------------------------------------------------
//     Module TIMER
// --------------------------------------------------------------

// Lire la date courante
extern BOOL LDBPCLireDate(tDelay * Date);

// Arreter une temporisation
extern BOOL LDBPCStopTimer(tTimerRef RefTempo, tDelay * Duree );

// Demarrer une temporisation pour une duree determine
extern BOOL LDBPCStartTimer(tTimerRef RefTempo, tDelay DureeEnTick
                                       , tpFunct1 Callback);

// Créer une temporisation
extern BOOL LDBPCCreerTempo(tTimerRef * refTempo);

// --------------------------------------------------------------
//     Module RESSOURCES
// --------------------------------------------------------------

// Creation of the Can channel
extern BOOL  RESCreateChannelXCAN(tXCanChannel*);

extern BOOL  RESCreateChannel(tCallBackCanal*);

// Création d'un canal
extern BOOL RESCreerCanal(tChannel RefCan,char * pNom
                                  , tCallBackCanal * pStructCallBack
                                  , tpCanCBCtrl pCbControler, tpCanCBAutorise pCbAutorise);

// Création d'un flux Initie
extern BOOL RESCreerFluxI(S32 * pRef,tChannel RefCan
                                  , tLdbpcTypeFlux TypeFlux, tpFluCBActionI pCbAction);

// Création d'un flux Non Initie
extern BOOL RESCreerFluxNI(S32 * pRef,tChannel RefCan
                                   , tLdbpcTypeFlux TypeFlux, tpFluCBActionNI pCbAction);

// Création d'un flux Non Initie Produit
extern BOOL RESCreerFluxNIP(S32 * pRef,tChannel RefCan, tpFluCBActionNIP pCbAction);

// Création d'une trame
extern BOOL RESCreerTrame(tInfoTrame * pInfoTrame);

// Création d'une trame de flux initie
extern BOOL RESCreerTrameFI(S32 * pRef, S32  RefFlux, char * pNom, tAddress Adresse, 
                            U32 TailleOctet, tLdbpcTypeFlux TypeFlux, tDelay Duree, 
                            tTypeFrame TypeFrame = cTypeFrameFixSize);

// Création d'une trame de flux initie sans attache
BOOL RESCreerTrameFISA(S32 * pRef, char * pNom, tAddress Adresse, 
                       U32 TailleOctet, char * pGroupe, tLdbpcTypeFlux TypeFlux, 
                       tDelay Duree, tTypeFrame TypeFrame = cTypeFrameFixSize);

// Création d'une trame attache a un flux non initie consomme
extern BOOL RESCreerTrameFnic(S32 * pRefTrame, S32  RefFlux,char * pNom, 
                              tAddress Adresse, U32 TailleOctet, char mode, 
                              tDelay periode, tDelay phase,
                              tpCallBackRxWithAddr cbTrameNIC, tTypeFrame TypeFrame = cTypeFrameFixSize);

// Création d'une trame de flux non initie consomme sans attache
extern BOOL RESCreerTrameFnicSA(S32 * pRefTrame, char * pNom, tAddress Adresse,
                                U32 TailleOctet, char * pGroupe, char mode, tDelay periode, tDelay phase,
                                tpCallBackRxWithAddr cbTrameNIC, tTypeFrame TypeFrame = cTypeFrameFixSize);

// Création d'une trame attache a un flux non initie produit
extern BOOL RESCreerTrameFnip(S32 * pRefTrame, S32  RefFlux, char * pNom, tAddress Adresse,
                              U32 TailleOctet,char mode, tDelay periode, tDelay phase,
                              tpCallBackStatusAddr cbTrameNIP);

// Création d'une trame de flux non initie produit sans attache
extern BOOL RESCreerTrameFnipSA(S32 * pRefTrame, char * pNom, tAddress Adresse, 
                                U32 TailleOctet, char * pGroupe,char mode, tDelay periode, tDelay phase,
                                tpCallBackStatusAddr cbTrameNIP);

// Création d'une sortie < 32bits
extern BOOL RESCreerSortieV(S32 * pRefSortie, S32 RefTrame, char * pNom, 
                            U32 TailleBit, U32 ValeurInit, U32 Position);

// Création d'une sortie > 32bits
extern BOOL RESCreerSortieB(S32 * pRefSortie, S32  RefTrame, char * pNom
                                    , U32 TailleBit, U8 * pBufferInit, U32 Position);

// Création d'une entree < 32bits
extern BOOL RESCreerEntreeV(S32 * pRefEntree, S32 RefTrame, char * pNom
                                    , U32 TailleBit, U32 ValeurInit, U32 Position);

// Création d'une entree > 32bits
extern BOOL RESCreerEntreeB(S32 * pRefEntree, S32 pRefTrame, char * pNom
                                    , U32 TailleBit, U8 * pBufferInit, U32 Position);

// Création d'une entree/Sortie < 32bits
extern BOOL RESCreerEntSorV(S32 * pRef, S32 RefTrame, char * pNom
                                    , U32 TailleBit, U32 ValeurInit, U32 Position);

// Création d'une entree/Sortie > 32bits
extern BOOL RESCreerEntSorB(S32 * pRef, S32 pRefTrame, char * pNom
                                    , U32 TailleBit, U8 * pBufferInit, U32 Position);

// Liaison d'une entree/Sortie à une trame
extern BOOL RESAttacherDonnee(S32 RefDonnee, S32 RefTrame, U32 Position);

// Lire une reference de flux
extern BOOL RESLireRefFlux(tChannel RefCan, tLdbpcTypeFlux TypeFlux, S32 * pRefFlux);

// Création d'un controle en entree
extern BOOL RESCreerControleEnt(S32 * pRefCtrl, tChannel RefCan, char * pNom
                                        , tCtrl Ctrl);

// Création d'un controle en sortie
extern BOOL RESCreerControleSor(S32 * RefCtrl, tChannel RefCan, char * Nom
                                        , tCtrl Ctrl, tDelay Duree);

// Lire une reference de trame par rapport au flux
extern BOOL RESLireRefTrameFlux(S32 RefFlux, tAddress Adresse, S32 * pRefTrame);

// Lire une reference de trame par rapport au canal
extern BOOL RESLireRefTrameCanal(tChannel RefCan, char typeFlux, tAddress Adresse
                                         , S32 * RefTrame);

// Lire une trame
extern BOOL RESLireTrame(S32 RefTrame, tMsg * pMsg);

// Lire la trame courante d'un flux initie
extern BOOL RESLireTrameCourante(S32 RefFlux, tAddress  * pAdresse, tMsg ** ppMsg);

// Lire l'etat de controle du canal
extern BOOL RESLireEtatControle(tChannel RefCan, U32 * pEtat);

// Ecrire une trame
extern BOOL RESEcrireTrame(S32 RefTrame, tMsg * pMsg);

// Ecrite la trame courante d'un flux
extern BOOL RESEcrireTrameCourante(S32 RefFlux, tAddress Adresse, tMsg * pMsg);

// Ecrire l'etat de controle du canal
extern BOOL RESEcrireEtatControle(tChannel RefCan, U32 Etat);

// Emission Standard du message courant d'un Flux Initie vers un canal
extern void RESEmissionStd(tChannel RefCan);

// Reception Standard du message courant d'un Flux Initie vers un canal
extern void RESReceptionStd(tChannel RefCan);

// Traitement de l'emission ou de la reception d'un Flux Initie vers un canal
// et Appel de la callback de fin de traitement
extern void RESTraiterFiStd(S32 RefFlux);

// Emission spontanee standard d'un Flux Non Initie vers le LAP
extern void RESEmissionSpontaneeStd(tChannel RefCan, S32 RefTrame);

// Reception spontanee standard d'un Flux Non Initie vers le LAP
extern void RESReceptionSpontaneeStd(tChannel RefCan, S32 RefTrame);

// Emission standard d'un controle sur un canal
extern void RESControleStd(tChannel RefCan,tCtrl Ctrl,tMsg * pMsg);

// Lire la reference de controle par rapport au canal et au controle
extern BOOL RESLireRefCtrl(S32 * pRefCtrl,tChannel Canal,tCtrl Ctrl);

// Lecture du Mode de la trame
extern BOOL RESLireModeTrame(S32 RefTrame, char * Mode);

// Demarrer une Action d'un flux non initié
extern void RESActionFNI(S32 RefTrame);

// Traitement de l'emission d'un controle vers un canal
extern void RESTraiterCtrlStd(S32 RefCtrl);

// Emission du controle vers le LAP
extern void RESControleSpontanee(S32 RefCtrl);

// Ecrire la duree d'une trame
extern BOOL RESEcrireDureeTrame(tAddress Adresse, S32 RefFlux, tDelay Duree);

// Etablir le transfert de données au format INTEL ou MOTOROLA
extern void RESEcrireFormat(tChannel RefCan,U8 Format);

extern void RESSetCurrentConfig(char * ConfigName);


// Messages segmentes
// ------------------

// Creer un message segmente
extern BOOL RESCreerMsgSeg( tParamMsgSeg * , S32 );

// Creer un message segmente acquite
extern BOOL RESCreerMsgSegAck( tParamMsgSeg * , S32 );

// Creer une session de message segmente acquitte
extern BOOL RESCreerMsgSegSession( tParamMsgSeg * , S32 );

// Configurer les couches CAN sans octets de bourrage
extern void RESSetCanNoPadding(BOOL CanNoPadding);

// Demande de le modification forcée de la trame
extern void RESEcrireDmdeMoficationTrame(S32 RefTrame, BOOL flag);

// Lecture de l'activation de la modification forcée de la trame
extern BOOL RESLireDmdeMoficationTrame(S32 RefTrame);

#endif   // fin de l'inclusion conditionnelle de LdbpcPar.h 
