//**************************************************************************
// COMPOSANT : ParamPWM
// FONCTION : ParamPWM
//
// Ce logiciel est la propriete de JCI :
// ---------------------------------------
// Il ne peut être reproduit ni communique en totalite ou partie sans
// son autorisation ecrite.
//
// ------------------------------------------------------------------------
// Definition des fonctions exportees par le composant ParamPWM :
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
//    BK. Beaugeois
//
// ------------------------------------------------------------------------
// Historique du fichier ParamPwm.cpp:
// -------------------------------------
// (initiales, date, modification)
//
// XX - 30/10/2002 à 15:27:01  - Générartion de ce fichier par Excel
//
//***************************************************************************
#define ParamPWM "ParamPWM"
//--------------------------------------------------------------------------
//---------------- Inclusion de fichiers (système et librairies -----------
//--------------------------------------------------------------------------
#include "Ldbpc.h"          // defini les types et constantes de bases
#include "Ldbpcpar.h"       // defini la librairie de parametrage
//
#ifdef cLDBChannelPwm

//--------------------------------------------------------------------------
// CANAL Pwm
//--------------------------------------------------------------------------

// Initialisation du Pwm
void PwmInit(void)
{
    tCallBackCanal CallBackCanal;
    memset(&CallBackCanal,0,sizeof(tCallBackCanal));
    S32 RefFluxIP;
    S32 RefTrame;

    // Creation de la structure de Callback du canal Pwm
    CallBackCanal.pCallBackCtrl            =   NULL;
    CallBackCanal.pCallBackTx        =   (tpCallBackStatusAddr)DATPwmCallBackTxWithAddr;  // parameters are const
    CallBackCanal.pCallBackRx       =   NULL;
    CallBackCanal.pTxSpontWithAddr      =   NULL;
    CallBackCanal.NbTxSpont     =   0;
    CallBackCanal.pRxSpontWithAddr     =   NULL;
    CallBackCanal.NbRxSpont    =   0;

    // Creation du canal Pwm
    RESCreerCanal(cLDBChannelPwm, "Pwm", &CallBackCanal, NULL, NULL);

    // Creation des flux
    RESCreerFluxI(&RefFluxIP,cLDBChannelPwm, cFluxIP, NULL);

    // Creation des trames et des donnees associées

    // Creation d'une trame "OutPwmCadrans"
    RESCreerTrameFI(&RefTrame, RefFluxIP, "OutPwmCadrans", 0x00, 3
                    , cFluxIP,0*(cTEMus/cLDBTick));

    // Creation des Sorties de la trame "OutPwmCadrans"
    RESCreerSortieV(NULL, RefTrame, "PWM_ROOMLAMP_FR", 16 , 0, 0 );
	RESCreerSortieV(NULL, RefTrame, "PWM_ROOMLAMP", 8 , 0, 16 );

    // Creation d'une trame "OutPwmLcd"
    //RESCreerTrameFI(&RefTrame, RefFluxIP, "OutPwmLcd", 0x01, 1
    //                , cFluxIP,0*(cTEMus/cLDBTick));

    // Creation des Sorties de la trame "OutPwmLcd"
    //RESCreerSortieV(NULL, RefTrame, "Pwm_Lcd", 8 , 0, 0 );

    // Creation des Controles
}
#endif
