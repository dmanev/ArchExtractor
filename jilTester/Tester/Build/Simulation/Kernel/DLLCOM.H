/**************************************************************************



  Ce logiciel est la propriete de JCI.
  -------------------------------------

  Il ne peut etre reproduit ni communique en totalite ou partie sans
  son autorisation ecrite.

         ------------------------------

           COMPOSANT : dllcom

           FONCTION  : Dll de communication Outil/Appli

         ------------------------------

**************************************************************************


         COMPOSANT dllcom
         ----------------------



 Ce fichier doit etre inclus dans les composants utilisant les macros,
 types et fonctions definis par le composant ldbtimer.
 Le fichier ldbtimer.h doit contenir toute et uniquement
 l'information necessaire au programmeur pour utiliser le composant
 ldbtimer.
 En particulier c'est ce fichier ldbtimer.h qui contient l'historique
 et la documentation du composant dans son ensemble.


**************************************************************************

 Reference a la documentation :

 ------------------------------------------------------------------------

 Presentation generale du composant :

 ------------------------------------------------------------------------

 Synoptique des fonctions, description des types et macros exportes :

 ------------------------------------------------------------------------

 Nom et initiales des developpeurs :  DC le 24/02/2000

 ------------------------------------------------------------------------

 Historique du composant DLLCOM dans son ensemble
 (initiales, date, modification)

   cree par :

 Revision PVCS du fichier : :   1.1  $

 Date de derniere modification : $Modtime:   04 Feb 2009 16:32:30  $

 Historique PVCS :
 :   P:/STANDARD/AEH/STK/PVCS/archives/STK/TOOLS/TARGET/RCAR/INTERMAT/Standard/DLLCOM.h-arc  $
 * 
 *    Rev 1.1   Jul 01 2003 13:40:52   aguillg
 * Sources Transfert from Simulation PVCS Database
 * 
 *    Rev 1.0   Nov 19 2001 14:02:10   guillen
 * Initial revision.


 ------------------------------------------------------------------------

 Historique du fichier ldbtimer.h
 (initiales, date, modification)

***************************************************************************/

/*----- Definition pour mono-inclusion -----*/
#ifndef I_DLLCOM_H
#define I_DLLCOM_H (1)

/*--------------------------------------------------------------------------*/
/*------  Inclusion de fichiers .h utiles a l'expansion de celui-ci  -------*/
/*--------------------------------------------------------------------------*/
/*
#include "fichier.h"
*/

#include "deftypes.h"

/*--------------------------------------------------------------------------*/
/*----------------------  Internal Error list:  ----------------------------*/
/*--------------------------------------------------------------------------*/
//
// 100	appli is working out of its phase
// 101	a client is working out of its phase
// 102	DLLLireStatut()
// 103	No Callback function for DLLConnecterClient() service
// 104	DLLLireDonnee(Ref,NULL)
// 105	DLLLireHistoriqueDonnee(Ref,NULL)
// 106	DLLLireInfoDonnee(Ref,NULL)
// 107	DLLLireNombreDeDonnees(NULL)
// 108	DLLChercherRefDonnee(NULL)
// 109	DLLEcrireDonnee(Ref,NULL)
// 110	DLLReserverEcriture() pEcritureAutorisee==NULL
// 111	tcDonnee::BufferSize() on a non 'cDLLTypeTab' type data
// 112	The size of the shared data is too large.
// 113	Shared memory overflow
// 114	The shared data size is larger than the shared memory size in DLLCOM.
// 115	DLLLireDate(NULL)
// 116	The call of DLLAttendreControle() was unexpected
// 117	The function DLLAttendreControle(ptr) was called with argument ptr == NULL
// 118	Shared memory corrupted
// 119	ActiverEtAttendreActivation called with erroneous recepient


// Alignemment sur 8 octets
#pragma pack( push , 8)

/*--------------------------------------------------------------------------*/
/*-------  Declaration des constantes exportees par ce composant  ----------*/
/*--------------------------------------------------------------------------*/
/* (Com: 3 lettres identifiant ce composant)
#define cComNomConstante   ValeurDeLaConstante
*/

// La constante DLLCOM_EXPORTS permet de savoir si vous definissez
// les fonctions l'interface ou si vous les utilisez.
// -> si  vous utilisez la DLL ne definissez pas DLLCOM_EXPORTS
// -> si  vous creez la DLL definissez DLLCOM_EXPORTS

#if _MSC_VER >= 1000
	#ifndef BOUCHON_DLL
		#ifdef DLLCOM_EXPORTS
			#define DLLCOM_API __declspec(dllexport)
		#else
			#define DLLCOM_API __declspec(dllimport)
		#endif
	#else
// Compilation debug : la DLL est remplacee par
// un bouchon
		#define DLLCOM_API
	#endif
#else
// Il faut redefinir DLLCOM_API pour le compilateur utilise
	#error Attention vous n'utlisez pas VISUAL C++ 5
#endif

/*--------------------------------------------------------------------------*/
/*-------  Declaration des macros exportees par ce composant  --------------*/
/*--------------------------------------------------------------------------*/
/* (Com: 3 lettres identifiant ce composant)
#define mComNomMacro   (DefinitionDeLaMacro)
*/

/*--------------------------------------------------------------------------*/
/*-------  Definition des types exportes par ce composant  -----------------*/
/*--------------------------------------------------------------------------*/
/* (Com: 3 lettres identifiant ce composant)
typedef ...   tComNomType;
*/

// Representation de la duree par unite de 1 ns
typedef unsigned __int64 tDLLDuree;

// Representation du retour d'une fonction de l'interface externe de la dll
typedef enum
{
    cDLLOK,
    cDLLFichierNonTrouve,
    cDLLAppliDeconnectee,
    cDLLNonOK,
    cDLLNonTrouve,
    cDLLDejaReservee,
    cDLLErreur,
    cDLLAlreadyConnnected
}	tDLLStatut;

// Representation du type de la donnee
typedef  enum
{
    cDLLEntree, 		// entree ou evenement entrant
    cDLLSortie, 		// sorite ou evenement sortant
    cDLLEntreeSortie, 	// entree et sortie
} tDLLType ;

// Representation du type de la valeur de la donnee
typedef  enum
{
    cDLLTypeVal, 		// Valeur <= 32bits
    cDLLTypeTab, 		// Table	au ou Valeur > 32bits
    cDLLTypeEvt, 		// Evenement (taille nulle)
} tDLLTypeVal ;

// Representation de la valeur de la donnee
typedef union
{
    U32	 	ULong;		// Valeur
    U8* 	pBuffer;	// Pointeur sur la valeur
} tDLLValeur;

// Representation d'un echantillon de la donnee
typedef struct
{
    tDLLValeur	Valeur;		// Valeur de la donnee
    tDLLDuree	Date;		// Date de mise a jour
} tDLLEchantillon;

// Representation des informations sur la donnee
typedef  struct
{
    tDLLType	Type; 		// Type de la donnee
    tDLLTypeVal TypeVal;	// Type de la valeur
    char*		pNom;		// Nom de la donnee
    tDLLValeur	ValInit;	// Valeur intiale de la donnee
    S32	        TailleBit;	// Taille en bits de la valeur
    char*		pGroupe;	// Groupe auquel appartient la donnee
} tDLLDonnee ;

// Representation d'une table de valeur
typedef struct
{
    tDLLEchantillon *	pTabVal;		// Tableau de echantillon
    U32 				NbVal; 			// Nombre de valeur
} tDLLTabEchantillon ;

// Representation d'une table de references de donnees
typedef struct
{
    S32	*	pTabRef;	// Tableau de reference
    S32		NbRef;		// Nombre de reference
} tDLLTabRefDonnee  ;


// Representation du type de commande de contrôle de l'application a tester
typedef enum
{
    cCCReset, 				// Reinitialisation de l'application a tester
    cCCExecuter, 			// Execution de l'application a tester
    cCCTerminer 			// Arrete l'application a tester
} tDLLCmdCtrl ;

// Representation de la signalisation des outils de test et de validation
typedef enum
{
    cSCAppliChargee,	// Signale que les donnees sont pretes a etre chargees
    cSCResetAppli, 		// Signale que l'appli. a tester a ete reinitialisee
    cSCTraitement, 		// Signale que l'appli. a tester a ete executee
    cSCFinTraitement, 	// Signale la fin d'une phase client
    cSCBreakPoint, 	    // Signale que l'on est en mode debug
} tDLLStatutClient;


// Representation de la commande de contrôle de l'application a tester
typedef struct
{
    tDLLCmdCtrl	Cmd;		// commande de contrôle de l'application a tester
    tDLLDuree	Date;		// duree de la commande
} tDLLControl ;

typedef struct
{
    U8 AppliConnectee;
    U8 CtrlConnecte;
    U8 RCarMode;
}   tDLLSatutConnection;

// Representation de la fonction de callback de fin de commande de contrôle
typedef void (*tpfDLLFinCtrl) (tDLLStatut);

// Representation de la fonction de callback de signalisation des outils
// de test et de validation
typedef U8 (*tpfDLLCallBackClient) (tDLLStatutClient);

// Representation de la fonction de callback de signalisation de transition
// pour l'appli
typedef void (*tpfDLLSignalisationTransition)(void);
typedef void (*tpfDLLModifFinExecution)(tDLLDuree);

/*--------------------------------------------------------------------------*/
/*-------  Declaration des variables exportees par ce composant  -----------*/
/*--------------------------------------------------------------------------*/
/* (Com: 3 lettres identifiant ce composant)
extern tType   ComNomVariable;       
extern tType*  pComNomVariable;
*/

/*--------------------------------------------------------------------------*/
/*-------  Donnees Constantes exportees par ce composant  ------------------*/
/*--------------------------
------------------------------------------------*/
/* (Com: 3 lettres identifiant ce composant)
extern const  tType   ComNomVariable;  
*/

/*--------------------------------------------------------------------------*/
/*-------  Fonctions exportees (par ordre alphabetique)  -------------------*/
/*--------------------------------------------------------------------------*/
/*
extern tTypeRetour ComNomFonction(tTypeArgument NomArgument,  ...);
*/

// --------------------------------------------------
//              Donnees - Creation
// --------------------------------------------------

// Creation d'une donnee		(APP)
DLLCOM_API tDLLStatut DLLCreerDonnee(	S32 *	pRef,
                                      const tDLLDonnee * pData) ;

// Reserver l'acces en ecritutre		(APP, CTRL, CLIENTS)
DLLCOM_API tDLLStatut DLLReserverEcriture(S32 Ref) ;

// Liberer l'acces en ecritutre		(APP, CTRL, CLIENTS)
DLLCOM_API tDLLStatut DLLLibererEcriture(S32 Ref) ;

// Lire l'etat de reservation
// si *pEcritureAutorisee est egal a cTrue le process appelant peux écrire la donnee
DLLCOM_API tDLLStatut DLLLireDroitEcriture(S32 Ref, U8* pEcritureAutorisee) ;

// --------------------------------------------------
//               Donnees - Acces
// --------------------------------------------------

// Lire une donnee 			(APP, CTRL, CLIENTS)
DLLCOM_API tDLLStatut DLLLireDonnee(S32 Ref, tDLLEchantillon* pEch) ;

// Ecrire une donnee			(APP, CTRL, CLIENTS)
DLLCOM_API tDLLStatut DLLEcrireDonnee (S32 Ref, tDLLEchantillon * pEch) ;

// Verification de la valeur d'une donnee < 32 bits	(CTRL, CLIENTS)
DLLCOM_API tDLLStatut DLLVerifierValeur(S32 Ref,
                                        U32 ValeurMin,
                                        U32 ValeurMax) ;

// Verification de la valeur d'une donnee	> 32 bits	(CTRL, CLIENTS)
DLLCOM_API tDLLStatut DLLVerifierBuffer(S32 Ref, U8 * pBuffer) ;

// Verification de la Instant de commutation d'une donnee	(CTRL, CLIENTS)
DLLCOM_API tDLLStatut DLLVerifierTransition(S32 Ref,
        tDLLDuree TMin,
        tDLLDuree TMax) ;

// Emettre d'un evenement		(APP, CTRL, CLIENTS)
DLLCOM_API tDLLStatut DLLSignalerEvt(S32 Ref, tDLLDuree Date) ;

// Lire la liste des donnees modifiees	(APP, CTRL, CLIENTS)
DLLCOM_API tDLLStatut DLLLireListeDonneesModifiees(tDLLTabRefDonnee* pTab) ;

// Lire l'historique d'une donnee		(CTRL, CLIENTS)
DLLCOM_API tDLLStatut DLLLireHistoriqueDonnee(S32 Ref ,tDLLTabEchantillon* pTabEch);

// --------------------------------------------------
//                Donnees - Informations
// --------------------------------------------------

// Lit le nombre de donnees crees
DLLCOM_API tDLLStatut DLLLireNombreDeDonnees(S32* pNb);

// Chercher la reference d'une donnee	(CTRL, CLIENTS)
DLLCOM_API tDLLStatut DLLChercherRefDonnee(char* pNom, S32* pRef) ;

// Lire le type d'une donnee		(APP, CTRL, CLIENTS)
DLLCOM_API tDLLStatut DLLLireInfoDonnee(S32 Ref,tDLLDonnee* pData) ;

// Lire la version de la DLL
DLLCOM_API tDLLStatut DLLGetVersion(char* DLLCOMVersion);

// Vérifie la version de l'install X-car
DLLCOM_API tDLLStatut DLLCheckXcarVersion(void);

// --------------------------------------------------
//                 Connexion/Deconnexion
// --------------------------------------------------

// Connexion de l'appli de la DLL		(APP)
DLLCOM_API tDLLStatut DLLConnecterAppli(	tpfDLLSignalisationTransition pST,
        tpfDLLModifFinExecution pMFE);
// Pour compatibilite, ne plus utiliser !
DLLCOM_API tDLLStatut DLLConnecterAppli(void);

// Connexion du CTRL	(CTRL)
DLLCOM_API tDLLStatut DLLConnecterCtrl(void);

// Connexion d'un interface materiel (APP + CTRL)
DLLCOM_API tDLLStatut DLLConnecterInterfaceMateriel(
    tpfDLLSignalisationTransition,
    tpfDLLModifFinExecution,
    tDLLDuree DureeMax	);
// Pour compatibilite, ne plus utiliser !
DLLCOM_API tDLLStatut DLLConnecterInterfaceMateriel( tDLLDuree DureeMax	);

// Connexion d'un client a la DLL		(CLIENT)
DLLCOM_API tDLLStatut DLLConnecterClient(tpfDLLCallBackClient pCallback);

// Deconnexion de la DLL
DLLCOM_API tDLLStatut DLLDeconnecter(void);


// Deconnexion d'un client de la DLL
DLLCOM_API tDLLStatut DLLDeconnecterClient(void);

// lecture d'informations sur les connections
// en deuxieme parametre, placer sizeof(tDLLSatutConnection)
DLLCOM_API tDLLStatut DLLLireStatut(tDLLSatutConnection* pStatut, U32 SizeOf );

// Vérification que l'appli est connectée sous Visual
DLLCOM_API U8 DLLAttendreOuSignalerReactivation(void);

// --------------------------------------------------
//                 Contrôles - commande
// --------------------------------------------------

// Charger l'application - fonction bloaquante jusqu'a la fin
// d'initialisation de l'application (CTRL)
DLLCOM_API tDLLStatut DLLChargerAPP(char * pNomExe,tpfDLLFinCtrl pCallback );

// Effectue une commande non bloquante de contrôle sur
// l'application (Intialisation, Execution, Arret)
// Avec un retour par CallBack			(CTRL)
DLLCOM_API tDLLStatut DLLCommander(tDLLControl Ctrl, tpfDLLFinCtrl pCallback) ;

// Attente d'une action de contrôle par la DLL	(APP)
DLLCOM_API tDLLStatut DLLAttendreControle(tDLLControl* pCtrl);

// --------------------------------------------------
//                 Contrôles - date
// --------------------------------------------------

// Lire la date courante			(CTRL, CLIENT)
DLLCOM_API tDLLStatut DLLLireDate(tDLLDuree * pDate);

// Demande d'activation apres une date(CLIENT)
DLLCOM_API tDLLStatut DLLDemandeActivation(tDLLDuree Date);

// Demande d'activation apres une duree ecoulee(CLIENT)
DLLCOM_API tDLLStatut DLLDemandeActivationSurTransition(S32 Ref);

// --------------------------------------------------
//                 Scripts
// --------------------------------------------------

// Demarrer la capture d'un script		(CTRL, CLIENT)
DLLCOM_API tDLLStatut DLLDemarrerCapture(char * pNomFichier);

// Terminer la capture d'un script		(CTRL, CLIENT)
DLLCOM_API tDLLStatut DLLTerminerCapture(void);

// --------------------------------------------------
//              Debuggeur de script
// --------------------------------------------------

// Passage en mode sans TimeOut (CTRL, CLIENT)
DLLCOM_API tDLLStatut DLLModeBreakpoint(void);


// -----------------------------------------------------
//      Fonction obsoletes gardées pour compatibilité
//       DLLCOM < V01.05
// -----------------------------------------------------
// Lire une donnee 			(APP, CTRL, CLIENTS)
DLLCOM_API tDLLStatut DLLLireDonnee(S32 Ref,const tDLLEchantillon ** ppEch) ;

// Lire la liste des donnees modifiees	(APP, CTRL, CLIENTS)
DLLCOM_API tDLLStatut DLLLireListeDonneesModifiees(const tDLLTabRefDonnee** ppTab) ;

// Lire l'historique d'une donnee		(CTRL, CLIENTS)
DLLCOM_API tDLLStatut DLLLireHistoriqueDonnee(S32 Ref ,const tDLLTabEchantillon** ppTabEch);

// Lire le type d'une donnee		(APP, CTRL, CLIENTS)
DLLCOM_API tDLLStatut DLLLireInfoDonnee(S32 Ref,const tDLLDonnee** ppData) ;


// Realignemment par default
#pragma pack( pop )

#endif   /* I_DLLCOM_H */
