//**************************************************************************
// COMPOSANT : LDBPC_TIMER
// FONCTION : TIMER
//
// Ce logiciel est la propriete de JCI :
// ---------------------------------------
// Il ne peut etre reproduit ni communique en totalite ou partie sans
// son autorisation ecrite.
//
// ------------------------------------------------------------------------
// Definition des fonctions exportees par le composant LDBPC_TIMER :
// ------------------------------------------------------------------
//
// ------------------------------------------------------------------------
// - Les macros, constantes et types qui ne sont pas destines a etre
// exportes sont definis dans ce fichier.
// - Les variables et fonctions qui ne sont pas destinees a etre exportees
// sont definies dans ce fichier et precedees du mot-cle static.
// ------------------------------------------------------------------------
// Commentaires sur le fonctionnement interne du composant:
// --------------------------------------------------------
// (structures de donnees, algorithmes, limitations, ...)
//
// ------------------------------------------------------------------------
// Nom et initiales des developpeurs :	
//
//		Gilles	GUILLEN		GG
//		Mickael GRANDSIRE	MG
//
// ------------------------------------------------------------------------
// Historique du fichier LDBPCTim.cpp:
// -------------------------------------
// (initiales, date, modification)
//
// v1.0	:	GG		: 10/04/2000	: Creation
// v1.1	:	GG		: 10/04/2000	: Maj
// v1.2 :	MG		: 14/03/2002	: Prise en compte des couches CAN
// v1.3 :	GG		: 19/09/2002	: Démarrage du Tos
//
//***************************************************************************

#define LDBPC_TIMER "LDBPC_TIMER"

//--------------------------------------------------------------------------
//---------------- Inclusion de fichiers (systeme et librairies) -----------
//--------------------------------------------------------------------------

#include "Ldbpc.h"		// Defini les types et constantes de bases
#include "LDBPCTim.h"	// Definit l'interface des classes tcTimer
#include "LDBPCDon.h"
#include "config.h"     // Configuration du LDBPC	

//--------------------------------------------------------------------------
//------- Inclusion des definitions des autres composants utiles -----------
//--------------------------------------------------------------------------
// #include <AUTRE_COMPOSANT.h>
#include "LDBPCErr.h"	// Definit l'interface des classes tcTimer
//--------------------------------------------------------------------------
//------- Declaration des constantes locales a ce composant ----------------
//--------------------------------------------------------------------------
// #define cNomConstante ValeurDeLaConstante
//--------------------------------------------------------------------------
//------- Declaration des macros locales a ce composant --------------------
//--------------------------------------------------------------------------
// #define mNomMacro (DefinitionDeLaMacro)
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
//------- Donnees Constantes locales a ce composant ------------------------
//--------------------------------------------------------------------------
// static const tType NomVariable;

//------- Definition des types locaux a ce composant -----------------------
//--------------------------------------------------------------------------
// typedef ... tNomType;
//--------------------------------------------------------------------------
//------- Variables locales a ce composant-----------------------------------
//--------------------------------------------------------------------------
// static tType NomVariable;
// static tType* pNomVariable;
BOOL	tcTimer::m_TraitementEnCours = cFalse;
HANDLE		tcTimer::m_hEvtLdbpc = NULL;
HANDLE		tcTimer::m_hEvtResumeLap = NULL;
HANDLE		tcTimer::m_hEvtExitLap = NULL;
HANDLE		tcTimer::m_hTabEvtLap[cMAX_EVT_LAP];

//--------------------------------------------------------------------------
//------- Variables exportees par ce composant -----------------------------
//--------------------------------------------------------------------------
// tType ComNomVariable; (Com: 3 lettres identifiant ce composant)
// tType* pComNomVariable;

tcTimer Timer;
BOOL LdbpcIsInitialised; // PON URD42 DEV 430 / PON URD45 BODY_SW 211 

//--------------------------------------------------------------------------
//------- Donnees Constantes exportees par ce composant --------------------
//--------------------------------------------------------------------------
// const tType ComNomVariable; (Com: 3 lettres identifiant ce composant)

//--------------------------------------------------------------------------
//------------------------- Fonctions exportees ----------------------------
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
//---------------------------- Fonctions locales ---------------------------
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
//	Construction du Module Timer
//--------------------------------------------------------------------------
tcTimer::tcTimer()
{
	// Initialisation des variables membres 
	m_Date = 0; 
	m_TraitementEnCours = cFalse;
	m_hTacheLap = INVALID_HANDLE_VALUE;
    m_DdeReset = cFalse;
	m_pTemposArmees = NULL;

	// Initialisation de la tempo du timer
	m_TempoTimer.pCallBack		= ReveillerTacheLdbpc;
	m_TempoTimer.EstPeriodique	= cTemNonPeriodique;

	// Destruction des evenements
	CloseEvents();
	// Intialisation des evenements
	CreateEvents();

	// Initialisation des tempos
	SupprimerToutesTempos();
}

//--------------------------------------------------------------------------
//	Destruction du Module Timer
//--------------------------------------------------------------------------
tcTimer::~tcTimer()
{
	//	Terminer le Module Timer
	Terminer();
}

//--------------------------------------------------------------------------
//	Terminer le Module Timer
//--------------------------------------------------------------------------
void tcTimer::Terminer()
{
	// Destruction la tache (TACHE LAP)
	if(m_hTabEvtLap[cEVT_EXIT_LAP])
	{
		if(!SetEvent(m_hTabEvtLap[cEVT_EXIT_LAP])) 
			mLDBPCErreur(cLdbpcErrTimer);

		if(WaitForSingleObject(m_hTacheLap,5000) == WAIT_TIMEOUT)
			mLDBPCErreur(cLdbpcErrTimer);
	}

	// Destruction des evenements
	CloseEvents();

	if(m_hTacheLap != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hTacheLap);
		m_hTacheLap = INVALID_HANDLE_VALUE;
	}

	// Arreter toutes les tempo
	SupprimerToutesTempos();
}

//--------------------------------------------------------------------------
//	Lire la date courante
//--------------------------------------------------------------------------
BOOL tcTimer::LireDate(tDelay * pDate)
{
	*pDate = m_Date;
	return (cTrue);
}

//--------------------------------------------------------------------------
//	Initialiser et Executer les taches LAP et LDBPC pour un certain temps
//--------------------------------------------------------------------------
BOOL tcTimer::Reset()
{
	DWORD Ras;
	BOOL res = cFalse;
	m_TraitementEnCours = cFalse;

  // For Checking Initialisation : PON URD42 DEV 430 / PON URD45 BODY_SW 211 
  LdbpcIsInitialised = cFalse;

	// Arreter toutes les tempo
	SupprimerToutesTempos();

	if(m_hTacheLap != INVALID_HANDLE_VALUE)
	{
		// Destruction la tache (TACHE LAP)
		SetEvent(m_hTabEvtLap[cEVT_EXIT_LAP]);

		if(WaitForSingleObject(m_hTacheLap,2000) == WAIT_TIMEOUT)
			mLDBPCErreur(cLdbpcErrTimer);

        CloseHandle(m_hTacheLap);
        m_hTacheLap = INVALID_HANDLE_VALUE;
	}

	// Destruction des evenements
	CloseEvents();

	// Intialisation des evenements
	CreateEvents();

	// Création d'un thread pour démarrer mTOSStart() (TACHE LAP)
	m_hTacheLap = CreateThread(NULL, 0
		, (LPTHREAD_START_ROUTINE) this->DemarrerOS, 0, 0, &Ras);


	if(m_hTacheLap == NULL)
	{
		mLDBPCErreur(cLdbpcErrTimer);
	}
	else
	{
		SetThreadPriority(m_hTacheLap, THREAD_PRIORITY_IDLE);
		res = cTrue;
	}

	return (res);
}

//--------------------------------------------------------------------------
//	Initialiser et Executer les taches LAP et LDBPC pour un certain temps
//--------------------------------------------------------------------------
BOOL tcTimer::Initialiser()
{
	m_Date = 0;
    return Reset();
}

//--------------------------------------------------------------------------
//	Création des evenements des taches
//--------------------------------------------------------------------------
void tcTimer::CreateEvents()
{
	// Creation des evenements
	m_hTabEvtLap[cEVT_RESUME_LAP]	= CreateEvent(NULL, FALSE, FALSE, NULL );
	m_hTabEvtLap[cEVT_EXIT_LAP]		= CreateEvent(NULL, FALSE, FALSE, NULL );
	m_hEvtLdbpc						= CreateEvent(NULL, FALSE, FALSE, NULL );

	// Intialisation des evenements
	ResetEvent(m_hTabEvtLap[cEVT_RESUME_LAP]);
	ResetEvent(m_hTabEvtLap[cEVT_EXIT_LAP]);
	ResetEvent(m_hEvtLdbpc);
}
//--------------------------------------------------------------------------
//	Destruction des evenements des taches
//--------------------------------------------------------------------------
void tcTimer::CloseEvents()
{
	if(m_hTabEvtLap[cEVT_RESUME_LAP])
	{
		if(!CloseHandle(m_hTabEvtLap[cEVT_RESUME_LAP])) 
			mLDBPCErreur(cLdbpcErrTimer);
		m_hTabEvtLap[cEVT_RESUME_LAP] = NULL;
	}
	if(m_hTabEvtLap[cEVT_EXIT_LAP])
	{
		if(!CloseHandle(m_hTabEvtLap[cEVT_EXIT_LAP]))
			mLDBPCErreur(cLdbpcErrTimer);
		m_hTabEvtLap[cEVT_EXIT_LAP] = NULL;

	}
	if(m_hEvtLdbpc)
	{
		if(!CloseHandle(m_hEvtLdbpc)) mLDBPCErreur(cLdbpcErrTimer);
		m_hEvtLdbpc = NULL;
	}
}

//--------------------------------------------------------------------------
//	Executer les taches LAP et LDBPC pour un certain temps
//--------------------------------------------------------------------------
BOOL tcTimer::Executer(tDelay date)
{
    if( m_DdeReset )
    {
        m_DdeReset = cFalse;
        Reset();
    }

	BOOL bRes = cFalse;
	if(date >= m_Date)
	{
		// Inserer une tempo permettant le basculement des taches
		m_TempoTimer.Date = date;
		InsererTempo(&m_TempoTimer);

		// Lecture des Entrees modifiees
		Donnees.LireEvtEntrees();

		// Reprise de la tache						(TACHE LAP)
		// Mise en atttente de la tache en cours	(TACHE LDBPC)
		ReveillerTacheLap();
		bRes = cTrue;
	}
	else mLDBPCErreur(cLdbpcErrTimer);

	return (bRes);
}

//--------------------------------------------------------------------------
//	Executer les taches LAP et LDBPC pour un certain temps
//--------------------------------------------------------------------------
void tcTimer::ChangerDateFin(tDelay Date)
{
	if(m_TempoTimer.Actif == cTrue)
	{
		SupprimerTempo(&m_TempoTimer);
		m_TempoTimer.Duree = Date - m_Date;
		m_TempoTimer.Date = Date;
		InsererTempo(&m_TempoTimer);
	}
	else
	{
		mLDBPCErreur(cLdbpcErrTimer);
	}
}

//--------------------------------------------------------------------------
//	Demarrer la tache LAP
//--------------------------------------------------------------------------
int tcTimer::DemarrerOS(int x)
{
	DWORD EvtIndex;

	// Mise en atttente de la tache en cours	(TACHE LAP)
	EvtIndex = WaitForMultipleObjects(cMAX_EVT_LAP, m_hTabEvtLap, FALSE, INFINITE);
	switch(EvtIndex)
	{
		case cEVT_RESUME_LAP:
								mTOSStart();
								break;
		case cEVT_EXIT_LAP:
								ExitThread(0);
								break;

		default:				mLDBPCErreur(cLdbpcErrTimer);
	}
	return(0);
}

//--------------------------------------------------------------------------
//	Reveiller la tache LDBPC et Suspendre la tache LAP
//--------------------------------------------------------------------------
void tcTimer::ReveillerTacheLdbpc()
{
	DWORD EvtIndex;
	// Reprise de la tache						(TACHE LDBPC)
	if(!SetEvent(m_hEvtLdbpc)) 
	{
		mLDBPCErreur(cLdbpcErrTimer);
		GetLastError();
 	}

	// Mise en atttente de la tache en cours	(TACHE LAP)
	EvtIndex = WaitForMultipleObjects(cMAX_EVT_LAP, m_hTabEvtLap, FALSE, INFINITE);
	switch(EvtIndex)
	{
		case cEVT_RESUME_LAP:	break;

		case cEVT_EXIT_LAP:
								ExitThread(1);
								break;

		default:				mLDBPCErreur(cLdbpcErrTimer);
	}
}

//--------------------------------------------------------------------------
//	Reveiller la tache LAP et Suspendre la tache LDBPC
//--------------------------------------------------------------------------
void tcTimer::ReveillerTacheLap()
{
	// Reprise de la tache						(TACHE LAP)
	if(!SetEvent(m_hTabEvtLap[cEVT_RESUME_LAP])) mLDBPCErreur(cLdbpcErrTimer);

	// Mise en atttente de la tache en cours	(TACHE LDBPC)
	WaitForSingleObject(m_hEvtLdbpc,INFINITE);
}

//--------------------------------------------------------------------------
//	Insertion d'une tempo dans la liste des tempos armees
//--------------------------------------------------------------------------
void tcTimer::InsererTempo(tcTempo * pNewTempo)
{
	tcTempo** ppTempo = &m_pTemposArmees;
	tcTempo* pTempo   = m_pTemposArmees;

	// Si la tempo existe et est presente dans la liste des tempos armees
	if((pNewTempo == NULL) || (pNewTempo->Actif == cTrue))
	{
		mLDBPCErreur(cLdbpcErrTimer);
		return;
	}

	// Parcours de la liste des tempos armees
	while( (pTempo != NULL) && (pTempo->Date < pNewTempo->Date) )
	{
		// Tempo suivante
		ppTempo = &( pTempo->Suivant );
		pTempo  = pTempo->Suivant;
	}

	// Activation de la tempo
	pNewTempo->Actif = cTrue;

	// Insertion de la tempo dans la liste des tempos armees
	pNewTempo->Suivant = pTempo;
	*ppTempo           = pNewTempo;
}

//--------------------------------------------------------------------------
//	Suppression d'une tempo dans la liste des tempos armees
//--------------------------------------------------------------------------
tDelay tcTimer::SupprimerTempo(tcTempo * pTempoCible)
{
	tDelay DureeRestante = 0;

	tcTempo** ppTempo = &m_pTemposArmees;
	tcTempo* pTempo   = m_pTemposArmees;

	// Si la tempo existe
	if(pTempoCible == NULL)
	{
		mLDBPCErreur(cLdbpcErrTimer);
		return 0;
	}

	// Parcours de la liste des tempos armees
	while( pTempo != NULL )
	{
		if( pTempo == pTempoCible )
		{
			// on retire la tempo de la liste
			(*ppTempo) = pTempo->Suivant;
			break;
		}

		// Tempo suivante
		ppTempo = &( pTempo->Suivant );
		pTempo  = pTempo->Suivant;
	}

	// Si tempo activee
	if(pTempoCible->Date != 0)
	{
		// Calcul de la duree restante avant l'echeance
		DureeRestante = pTempoCible->Date - m_Date;
	}

	// Desactivation de la tempo
	pTempoCible->Actif	= cFalse;
	pTempoCible->Suivant= NULL;

	return(DureeRestante);
}

//--------------------------------------------------------------------------
//	Traitement de la premiere tempo de la liste des tempos armees
//--------------------------------------------------------------------------
void tcTimer::TraiterProchaineTempo(void) 
{
	tcTempo* pTempo   = m_pTemposArmees;

	// S'il y a des tempo dans la liste
	if( pTempo != NULL )
	{
		// Suppression de la tempo de la liste (en tete de liste)
		m_pTemposArmees = pTempo->Suivant;

		// Mise à jour de la date courante
		m_Date = pTempo->Date;

		// Desactivation de la tempo
		pTempo->Actif = cFalse;

		// si la tempo est periodique
		if(pTempo->EstPeriodique == cTemPeriodique)
		{
			// Mise a jour de la date d'echeance
			pTempo->Date = pTempo->Duree + m_Date;

			// Insrerer la tempo dans la liste
			InsererTempo(pTempo);
		}

		// Taitement de la temporisation
		pTempo->Traiter();
	}
	else
	{
		// Generer Erreur
		mLDBPCErreur(cLdbpcErrTimer);
	}
}

//--------------------------------------------------------------------------
//	Traitement des tempos de la liste des tempos armees pendant la duree
//--------------------------------------------------------------------------
void tcTimer::TraiterTempo(tDelay duree)
{
	tDelay DateFin = m_Date + duree;

	// Eviter la reentrance
	if(m_TraitementEnCours)
	{
		//-- Generer Erreur
		mLDBPCErreur(cLdbpcErrTimer);
		return;
	}

	// Initialisation pour commencer le traitement
	m_TraitementEnCours = cTrue;

	// S'il y a des tempo dans la liste
	while( (m_pTemposArmees != NULL) && (DateFin >= m_pTemposArmees->Date))
	{
		TraiterProchaineTempo();
	}

	// Si la liste est vide
	if(m_pTemposArmees == NULL)
	{
		// Generer Erreur
		mLDBPCErreur(cLdbpcErrTimer);
	}

	// Mise à jour de la date courante
	m_Date = DateFin;

	// Initialisation pour finir le traitement
	m_TraitementEnCours = cFalse;
}

//--------------------------------------------------------------------------
//	Desactivation de toutes les tempos de la liste
//--------------------------------------------------------------------------
void tcTimer::SupprimerToutesTempos(void)
{
	tcTempo* pTempo   = m_pTemposArmees;
	int i;

	while(pTempo != NULL)
	{
		// Desactivation de la tempo
		pTempo->Actif = cFalse;

		// Temporisation suivante
		pTempo  = pTempo->Suivant;
	}

	for(i = 0; i<cLDBTimerNbr; i++)
	{
		m_TabTemposDAT[i].Actif = cFalse;
	}

	// Suppression des tempos de la liste
	m_pTemposArmees = NULL;

	// Initialisation de la tempo du timer
	m_TempoTimer.Actif = cFalse;
}
