//******************************************************************************
// COMPOSANT : MainLev
// FONCTION  : Point d'entrée du LDBPC
//
// Ce logiciel est la propriete de JCI :
// ---------------------------------------
// Il ne peut être reproduit ni communique en totalite ou partie sans
// son autorisation ecrite.
//
// ------------------------------------------------------------------------
// Definition des fonctions exportees par le composant MainLev :
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
// Historique du fichier MainLev.cpp:
// -------------------------------------
// (initiales, date, modification)
//
// v1.0	:	GG		: 14/04/2000	: Creation
// v1.1 :	MG		: 13/03/2002	: Prise en compte des couches CAN
//
//***************************************************************************

#include "param.h"
#include "LdbpcTim.h"
#include "LdbpcDon.h"
#include "LdbpcRes.h"
#include "DLLCOM.h"

static BOOL LDBPCState;

#include "XCarCAN.h"

void CB_ChangerDateFin(tDLLDuree DateFin)
{
    Timer.ChangerDateFin(DateFin);
}

void CB_LireDonnees(void)
{
    Donnees.LireEvtEntrees();
}

void StopLDBPC(void)
{
  LDBPCState = cFalse;
}

int StartLDBPC(void)
{
    tDLLControl Ctrl;       // Commande de controle
    Ctrl.Cmd = cCCReset;    // Initialisation de la commande
    Ctrl.Date = 0;          // de controle
    LDBPCState = cTrue;
    tcErreur::SetMediaErreur(cMediaErrAffichage | cMediaErrASSERT);
    tcErreur::SetFileErreur("ErrLdbpcLog.txt");
    // Connection du calculateur virtuel
    DLLConnecterAppli(CB_LireDonnees, CB_ChangerDateFin);

    // Retrait de l'icone d'attente au chargement de l'appli
    MSG Msg;
    PeekMessage(&Msg,NULL,0,0,0);

    // Données internes
    Ressources.CreationDonneesInternes(); 

    // Parametrage du LDBPC
    InitParametrage(); 

    // XCARCAN Start
    XCAN_Open();

    // Lancer le LAP jusqu'au premier "Simuler Temps"
    Timer.Initialiser();

    // Tant que l'application de controle n'a pas decider de terminer
    while((Ctrl.Cmd != cCCTerminer) && (LDBPCState == cTrue))
    {
        // Attente d'un control de l'application de controle
        if( DLLAttendreControle(&Ctrl) == cDLLErreur )	break;
        switch(Ctrl.Cmd)
        {
            // Control de fin 
            case cCCTerminer :
                break;

            // Controle d'execution
            case cCCExecuter :
                Timer.Executer(Ctrl.Date);
                break;

            // Controle d'intialisation
            case cCCReset :
                Timer.Initialiser();
                break;

            default :
                MessageBox(NULL,"Main Error !","LDBPC",MB_ICONSTOP);
        }
    }

    // XCARCAN Stop
    XCAN_Close();

    Timer.Terminer();
    DLLDeconnecter();

    return 0;
}

