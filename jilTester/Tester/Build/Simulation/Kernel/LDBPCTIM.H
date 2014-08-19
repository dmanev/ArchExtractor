//**************************************************************************
// COMPOSANT : LDBPC_TIMER
// FONCTION : LDBPC_TIMER
//
// Ce logiciel est la propriete de JCI :
// ---------------------------------------
// Il ne peut etre reproduit ni communique en totalite ou partie sans
// son autorisation ecrite.
//
// ------------------------------------------------------------------------
// Ce fichier doit etre inclus dans les composants utilisant les macros,
// types et fonctions definis par le composant LDBPC_TIMER.
// Le fichier LDBPCTim.h doit contenir toute et uniquement
// l'information necessaire au programmeur pour utiliser le composant
// LDBPC_TIMER.
// En particulier c'est ce fichier LDBPCTim.h qui contient l'historique
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
//		Gilles	GUILLEN		GG
//		Mickael GRANDSIRE	MG
//
// ------------------------------------------------------------------------
// Historique du composant LDBPC_TIMER dans son ensemble
// (initiales, date, modification)
//
// v1.0	:	GG		: 10/04/2000	: Creation
// v1.1 :	MG		: 14/03/2002	: Prise en compte des couches CAN
//
// ------------------------------------------------------------------------
// Historique du fichier LDBPCTim.h
// (initiales, date, modification)
//
//***************************************************************************

//-------------------------------------------------------------------------
//----- Inclusion de fichiers .h utiles a l'expansion de celui-ci ---------
//-------------------------------------------------------------------------

#include "Ldbpc.h"		// Defini les types et constantes de bases
#include "LDBPCTem.h"	// Defini l'interface des classes de temporisation
#include "LDBPCErr.h"	// Definit l'interface des classes tcTimer

//---- Definition pour mono-inclusion -----
#if !defined(I_LDBPC_TIMER)
#define I_LDBPC_TIMER	1

//-------------------------------------------------------------------------
//------ Declaration des constantes exportees par ce composant ------------
//-------------------------------------------------------------------------
//(Com: 3 lettres identifiant ce composant)
//#define cComNomConstante ValeurDeLaConstante
#define		cTimTacheLap		1
#define		cTimTacheLdb		2

#define		cEVT_RESUME_LAP		0
#define		cEVT_EXIT_LAP		1
#define		cMAX_EVT_LAP		2

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
typedef void *HANDLE;

//--------------------------------------------------------------------------
//------- Declaration des variables exportees par ce composant -----------
//--------------------------------------------------------------------------
// (Com: 3 lettres identifiant ce composant)
// extern tType ComNomVariable;
// extern tType* pComNomVariable;
class tcTimer;
extern tcTimer Timer;

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

//--------------------------------------------------------------------------
//----------- Definition de la classe du Module Timer ----------------------
//--------------------------------------------------------------------------
class tcTimer
{
public:
    // ------------------------------------------------------------------------
    // Constructeur
    // ------------------------------------------------------------------------
    tcTimer();

    // ------------------------------------------------------------------------
    // Destructeur
    // ------------------------------------------------------------------------
    virtual ~tcTimer();

    // Date courante
    tDelay		m_Date;

private:
    // ------------------------------------------------------------------------
    // Données Membres privées
    // ------------------------------------------------------------------------

    // Liste des temporisations armees
    tcTempo	*		m_pTemposArmees;
    tcTempoSimple	m_TabTemposDAT[cLDBTimerNbr + 1];

    BOOL    m_DdeReset;

    // Drapeau de detection de la fin de tratement des tempo
    static BOOL		m_TraitementEnCours;

    // Handle de la tache LAP
    HANDLE		m_hTacheLap;
    // Handle de l'evenement de reveil de la tache LDBPC
    static HANDLE		m_hEvtLdbpc;
    // Handle de l'evenement de reveil de la tache LAP
    static HANDLE		m_hEvtResumeLap;
    // Handle de l'evenement de fin de la tache LAP
    static HANDLE		m_hEvtExitLap;
    // Tableau de Handles de reveil de la tache LAP
    static HANDLE		m_hTabEvtLap[cMAX_EVT_LAP];

public:
    // ------------------------------------------------------------------------
    // Fonctions Membres publiques
    // ------------------------------------------------------------------------
    //	Initialiser et Executer la tache LAP pour un certain temps
    BOOL Initialiser() ;

    inline void TraiterReset() {m_DdeReset = cTrue;}

    //	Executer la tache LAP pour un certain temps
    BOOL Executer(tDelay);

    //	Lire la date courante
    BOOL LireDate(tDelay *);

    //	Supprimer une tempo
    tDelay SupprimerTempo(tcTempo*);

    // Inserer une tempo
    void InsererTempo(tcTempo*);

    //	Traiter les temporisations
    void TraiterTempo(tDelay Duree);

    void TraiterProchaineTempo(void);

    void ChangerDateFin(tDelay Date);

    // Ajouter une temporisation DAT
    void AjouterTempoDAT(tTimerRef refTempo, tpFunct callback, tDelay duree
                         , BOOL estPeriodique)
    {
        if(refTempo > cLDBTimerNbr)
        {
            mLDBPCErreur(cLdbpcErrTimer);
        }
        m_TabTemposDAT[refTempo].Duree = duree;
        m_TabTemposDAT[refTempo].Date = duree + m_Date;
        m_TabTemposDAT[refTempo].EstPeriodique = estPeriodique;
        m_TabTemposDAT[refTempo].pCallBack = callback;
        InsererTempo(&m_TabTemposDAT[refTempo]);
    }

    void AjouterTempo(tcTempo* pTempo)
    {
        pTempo->Date = pTempo->Duree + m_Date;
        InsererTempo(pTempo);
    }

    // Arreter une temporisation DAT
    inline tDelay SupprimerTempoDAT(tTimerRef refTempo)
    {
        return(SupprimerTempo(&m_TabTemposDAT[refTempo]));
    }

    // Lire la date courante
    inline tDelay LireTempoDAT(tTimerRef refTempo)
    {
        return(m_TabTemposDAT[refTempo].Date - m_Date);
    }

    //
    void Terminer();

    // ------------------------------------------------------------------------
    // Fonction Membre privée
    // ------------------------------------------------------------------------
private:

    //
    void CloseEvents();

    // Reset de l'application
    BOOL Reset(void);

    // Tempo d'execution
    tcTempoSimple m_TempoTimer;

    //	Demarrer la tache LAP
    static int DemarrerOS(int x);

    //	Reveiller la tache LDBPC et Suspendre la tache LAP
    static void ReveillerTacheLdbpc();

    //	Reveiller la tache LAP et Suspendre la tache LDBPC
    static void ReveillerTacheLap();

    //	Initialisation des evenements des taches
    static void CreateEvents();

    // Desactiver les tempos de la liste
    void SupprimerToutesTempos(void);
};

#endif // I_LDBPC_TIMER
