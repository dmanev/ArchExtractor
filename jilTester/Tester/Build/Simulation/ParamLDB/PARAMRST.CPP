//**************************************************************************
// COMPOSANT : PARAMRST
// FONCTION : PARAMRST
//
// Ce logiciel est la propriete de JCI :
// ---------------------------------------
// Il ne peut être reproduit ni communique en totalite ou partie sans
// son autorisation ecrite.
//
// ------------------------------------------------------------------------
// Definition des fonctions exportees par le composant parkwp :
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
// Nom et initiales des developpeurs :	GUILLEN	GG
//
// ------------------------------------------------------------------------
// Historique du fichier parkwp.c:
// -------------------------------------
// (initiales, date, modification)
//
// cree par :	GG : 05.05.2000 : Creation
//
//
//***************************************************************************
#define parrst "parrst"

//--------------------------------------------------------------------------
//---------------- Inclusion de fichiers (système et librairies -----------
//--------------------------------------------------------------------------

#include "Ldbpc.h" // defini les types et constantes de bases
#include "Ldbpcpar.h"

extern "C" void LAPIllRKELock(void);
extern "C" void LAPIllRKEUnlock(void);

void CallBackWakeUp(S32 v)
{
	DATDinCallBackCtrl( cLDBDinWakeUp );
}

void CallBackRst(S32 v)
{
    LDBReset();
}

void CallRKE_LOCK_REQUEST(S32 v)
{
	LAPIllRKELock();
}
void CallRKE_UNLOCK_REQUEST(S32 v)
{
	LAPIllRKEUnlock();
}


void RstInit(void)
{
	DONCreerEvtEntree( NULL, "Reset", CallBackRst, "Kwp" );
	DONCreerEvtEntree( NULL, "WakeUp", CallBackWakeUp, "Kwp" );
	DONCreerEvtEntree( NULL, "TEST_RKE_LOCK_REQUEST", CallRKE_LOCK_REQUEST, "Kwp" );
	DONCreerEvtEntree( NULL, "TEST_RKE_UNLOCK_REQUEST", CallRKE_UNLOCK_REQUEST, "Kwp" );
}

