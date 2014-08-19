//**************************************************************************
// COMPOSANT : LDBPCCom
// FONCTION : TYPELDB
//
// Ce logiciel est la propriete de JCI :
// ---------------------------------------
// Il ne peut etre reproduit ni communique en totalite ou partie sans
// son autorisation ecrite.
//
// ------------------------------------------------------------------------
// Ce fichier doit etre inclus dans les composants utilisant les macros,
// types et fonctions definis par le composant CE_COMPOSANT.
// Le fichier CE_COMPOSANT.h doit contenir toute et uniquement
// l'information necessaire au programmeur pour utiliser le composant
// CE_COMPOSANT.
// En particulier c'est ce fichier CE_COMPOSANT.h qui contient l'historique
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
// Historique du composant CE_COMPOSANT dans son ensemble
// (initiales, date, modification)
//
// cree par :
//
// ------------------------------------------------------------------------
// Historique du fichier typesldb.h
// (initiales, date, modification)
//
//***************************************************************************

#include "deftypes.h"

//---- Definition pour mono-inclusion -----
#ifdef I_TYPELDB
#else
#define I_TYPELDB 1

#define cCodageIntel		1
#define cCodageMotorola		2

/*------------------------------------------------------------------------*/
/*-------  Declaration des macros exportees par ce composant  ------------*/
/*------------------------------------------------------------------------*/
/* (Com: 3 lettres identifiant ce composant)
#define mComNomMacro   (DefinitionDeLaMacro)
*/
#define  MAX_STRING	256
#define  MAX_FLUX	4

#define	mFluxNonInitie(x)	(x & 0x2)
#define	mFluxInitie(x)		(!mFluxNonInitie(x))
#define	mFluxProduit(x)		(x & 0x1)
#define	mFluxConsomme(x)	(!mFluxProduit(x))

// Manipulation de bits
#define cTailleOctet		8
#define mNbOctetPlein(x)	(x/cTailleOctet)
#define mTailleOctet(x)		((x+(cTailleOctet-1))/cTailleOctet)
#define mNbBitSup(x)		((mTailleOctet(x)*cTailleOctet) - (mNbOctetPlein(x)*cTailleOctet))

#define mCtrlSortie(x)	(x == cDLLSortie)
#define mCtrlEntree(x)	(!mCtrlSortie(x))

// Mode d'emission des flux non initie
#define cModeMan		0
#define cModeAuto		1

// Temps
#define cTEMms (tDelay)(1000000L)
#define cTEMus (tDelay)(1000L   )
#define cTEMns (tDelay)(1L      )


/*------------------------------------------------------------------------*/
/*-------  Definition des types exportes par ce composant  ---------------*/
/*------------------------------------------------------------------------*/
/* (Com: 3 lettres identifiant ce composant)
typedef ...   tComNomType;
*/

// Types de Flux
typedef enum
{
    cNoFlux		= -1,		// Pas de flux
    cFluxIC		= 0x0,		// Flux Initie consomme
    cFluxIP		= 0x1,		// Flux Initie produit
    cFluxNIC	= 0x2,		// Flux Non Initie consomme
    cFluxNIP	= 0x3,		// Flux Non Initie produit
} tLdbpcTypeFlux;

// Type Evenement
#define cNoEvt			(-1)						// Pas d'Evenement
#define cEvtEntrant		((tDLLType)(cDLLEntree))	// Evenement en entree
#define cEvtFIC			((tDLLType)(cDLLSortie))	// Flux initie consomme
#define cEvtFIP			((tDLLType)(cDLLSortie))	// Flux initie produit
#define cEvtCtrl		((tDLLType)(cDLLEntreeSortie))	// Emission d'un controle

typedef void* tpParam;
typedef void (*tpFunct1)(S32);
typedef void (*tpVoid)(tpParam,tpParam);
typedef void (*tpCanCBCtrl)(tCtrl);
typedef void (*tpCanCBAutorise)(BOOL);
typedef void (* tpFluCBActionI)(tAddress , tMsg *);
typedef void (* tpFluCBActionNI)(tAddress);
typedef void (* tpFluCBActionNIP)(tAddress* , tMsg **);


typedef enum
{
    cLdbpcOk						= -1,
    // Niveau 0 ----------------------------------
    cLdbpcErr						=  0,
    cLdbpcErrAllocMem				=  1,
    // Niveau 1 ----------------------------------
    cLdbpcErrPointNul				,
    cLdbpcErrFoncEvt				,
    cLdbpcErrDll					,
    cLdbpcErrTypeValeur				,
    cLdbpcErrTypeDonnee				,
    cLdbpcErrFlux					,
    cLdbpcErrTrame					,
    cLdbpcErrDonnee					,
    cLdbpcErrCanal					,
    cLdbpcErrCtrl					,
    cLdbpcErrEvt					,
    cLdbpcErrEcritureDonnee			,
    cLdbpcErrDecalage				,
    cLdbpcErrGroupe					,
    cLdbpcErrTimer					,
    // Niveau 2 ----------------------------------
    cLdbpcErrParPointNul			,
    cLdbpcErrParTailleDonnee		,
    cLdbpcErrParNom					,
    cLdbpcErrParRef					,
    cLdbpcErrParCanal				,
    cLdbpcErrParFlux				,
    cLdbpcErrParTrame				,
    cLdbpcErrParStructCB			,
    cLdbpcErrParAdresse				,
    cLdbpcErrParCtrl				,
    // Niveau 3 ----------------------------------

} tLDBPCStatut;

typedef struct
{
    tpCallBackCtrl       pCallBackCtrl;
    tpCallBackStatusCtrl pCallBackEndCtrl;
    tpCallBackStatusAddr  pCallBackTx;
    tpCallBackStatusAddr  pCallBackRx;
    tRxSpontWithAddr*	   pRxSpontAvecAdr;
    tTxSpontWithAddr*     pTxSpontAvecAdr;
    S16               NbRxSpont;
    S16               NbTxSpont;
} tCallBackCanal;

typedef struct
{
    S32 *RefMsgSeg;			// Référence du message (retour)

    char Nom[MAX_STRING]; 		// Nom du message
    U16 TailleMax;  		// Taille Max du message en octet
    S32 RefFluxIP;			// Reference du flux initié produit
    S32 RefFluxNIC;			// Reference du flux non initié consommé
    tAddress AdTrameTx;			// Adresse de la trame à emettre
    tAddress AdTrameRx;			// Adresse de la trame à recevoir
} tParamMsgSeg;

typedef struct
{
    S32 *				pRef;			// Reference of the flux
    tChannel				RefCan;			// Reference of the canal
    tLdbpcTypeFlux		TypeFlux ;		// Type of the flux
    tpFluCBActionNI		pCbActionNIC;	// Callback	Personnal action for fnic
    tpFluCBActionNIP	pCbActionNIP;	// Callback	Personnal action for fnip
    tpFluCBActionI		pCbActionI;		// Callback	Personnal action for fi
} tInfoFlux;


/*------------------------------------------------------------------------*/
/*-------  Declaration des variables exportees par ce composant  ---------*/
/*------------------------------------------------------------------------*/
/* (Com: 3 lettres identifiant ce composant)
extern tType   ComNomVariable;
extern tType*  pComNomVariable;
*/


/*------------------------------------------------------------------------*/
/*-------  Donnees Constantes exportees par ce composant  ----------------*/
/*------------------------------------------------------------------------*/
/* (Com: 3 lettres identifiant ce composant)
extern const  tType   ComNomVariable;
*/


/*------------------------------------------------------------------------*/
/*-------  Fonctions exportees (par ordre alphabetique)  -----------------*/
/*------------------------------------------------------------------------*/
/*
extern tTypeRetour ComNomFonction(tTypeArgument NomArgument,  ...);
*/
extern void CallBackRef(tpParam Callback, tpParam ParamCallback);


#endif   // (I_TYPELDB) fin de l'inclusion conditionnelle de typesldb.h
