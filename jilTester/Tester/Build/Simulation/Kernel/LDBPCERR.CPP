//**************************************************************************
// COMPOSANT : LdbpcErreur
// FONCTION : Implementation des classes de FLux 
//
// Ce logiciel est la propriete de JCI :
// ---------------------------------------
// Il ne peut être reproduit ni communique en totalite ou partie sans
// son autorisation ecrite.
//
// ------------------------------------------------------------------------
// Definition des fonctions exportees par le composant LdbpcErreur :
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
// Historique du fichier LdbpcErr.c:
// -------------------------------------
// (initiales, date, modification)
//
// cree par :	GG : 30/05/2000
//
//
//***************************************************************************

#define LdbpcErreur "LdbpcErreur"

//--------------------------------------------------------------------------
//---------------- Inclusion de fichiers (système et librairies -----------
//--------------------------------------------------------------------------
#include "ldbpc.h"
#include "time.h"
#include "LdbpcErr.h"
#include "assert.h"

//--------------------------------------------------------------------------
//------- Inclusion des definitions des autres composants utiles ---------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//------- Declaration des constantes locales à ce composant --------------
//--------------------------------------------------------------------------
// #define cNomConstante ValeurDeLaConstante

#define cFichierErreur	"ErrLDBPC.txt"
#define cTitreMessage			"LDBPC"

//--------------------------------------------------------------------------
//------- Declaration des macros locales à ce composant ------------------
//--------------------------------------------------------------------------
// #define mNomMacro (DefinitionDeLaMacro)

//--------------------------------------------------------------------------
//------- Definition des types locaux à ce composant ---------------------
//--------------------------------------------------------------------------
// typedef ... tNomType;
//--------------------------------------------------------------------------
//------- Variables locales à ce composant---------------------------------
//--------------------------------------------------------------------------
// static tType NomVariable;
// static tType* pNomVariable;
//--------------------------------------------------------------------------
//------- Donnees Constantes locales à ce composant ----------------------
//--------------------------------------------------------------------------
// static const tType NomVariable;
static const char * ChaineErreur[] = 
{
// Niveau 0 ---------------------------------------------------------------
	"An error has been detected",			// 0
	"A memory leak has been detected",			// 1
// Niveau 1 ---------------------------------------------------------------
	"Nul pointer is used",			// 
	"An error has been detected on an event function",	// 
	"A communication error with the DLL has been detected",	// 
	"A LDBPC Error on a type of the value has been detected",						// 
	"A LDBPC Error on a data type has been detected",						// 
	"A LDBPC Error on a data flow has been detected",							// 
	"A LDBPC Error on a frame has been detected",							// 
	"A LDBPC Error on a data has been detected",							// 
	"A LDBPC Error on a channel has been detected",							// 
	"A LDBPC Error on a flow control has been detected",							// 
	"A LDBPC Error on a event has been detected",							// 
	"A LDBPC Error on a writing data has been detected",							// 
	"A LDBPC Error on a shift data has been detected",							// 
	"A LDBPC Error on a group has been detected",							// 
	"A LDBPC Error on a LDBPC Timer has been detected",							// 
// Niveau 2 ----------------------------------
	"Nul pointer is used",			// 
	"A configuration error on a data size",										// 
	"A configuration error on a name",										// 
	"A configuration error on a reference",										// 
	"A configuration error on a channel",										// 
	"A configuration error on a data flow",										// 
	"A configuration error on a frame",										// 							// 
	"A configuration error on a Callback structure ",										// 
	"A configuration error on a address",										// 
	"A configuration error on a flow control",										// 
	"",										// 
	"",										// 
};

const char * pECStringError[] = 
{
	"No Error",			        // cEC00000
	"Error EC00001",			// cEC00001
	"Error EC00002",			// cEC00002
	"Error EC00003",			// cEC00003
	"Error EC00004",			// cEC00004
	"Error EC00005",			// cEC00005
	"Error EC00006",			// cEC00006
	"Error EC00007",			// cEC00007
	"Error EC00008",			// cEC00008
	"Error EC00009",			// cEC00009
	"Error EC00010",			// cEC00010
	"Error EC00011",			// cEC00011
	"Error EC00012",			// cEC00012
};
//--------------------------------------------------------------------------
//------- Variables exportees par ce composant ---------------------------
//--------------------------------------------------------------------------
// tType ComNomVariable; (Com: 3 lettres identifiant ce composant)
// tType* pComNomVariable;
//--------------------------------------------------------------------------
//------- Donnees Constantes exportees par ce composant ------------------
//--------------------------------------------------------------------------
// const tType ComNomVariable; (Com: 3 lettres identifiant ce composant)
//--------------------------------------------------------------------------
//---------------------------- Fonctions locales ---------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//------------------------- Fonctions exportees ----------------------------
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
//--------------- Implementation de la classe tcErreur --------------------
//--------------------------------------------------------------------------
U8	tcErreur::s_TypeMedia = 0;
char	tcErreur::s_Fichier[] = {cFichierErreur};

// Mise à jour du Media de prise en comtpe des erreurs
void tcErreur::SetMediaErreur(U8 MediaErr)
{
	s_TypeMedia = MediaErr;
}

// Mise à jour du nom du fichier d'erreur
void tcErreur::SetFileErreur(const char * File)
{
	strcpy(s_Fichier, File);
}


// Generation de l'erreur
tLDBPCStatut tcErreur::GererErreur(tLDBPCStatut ErreurId, int Ligne
								   , char * pNomFichier)
{
	char Text[255];
	sprintf(Text, "-Line %d du file %s\nError : %s.",Ligne,pNomFichier
		,ChaineErreur[ErreurId]);
	ProcessErreur(Text);
	return(ErreurId);
}

void tcErreur::GererErreur(char * pTextErreur, int Ligne, char * pNomFichier)
{
	char Text[255];
	sprintf(Text, "-Line %d du file %s\nError : %s.", Ligne, pNomFichier
		, pTextErreur);
	ProcessErreur(Text);
}

void tcErreur::SetError(U32 ErrorCode, int Ligne, char * pNomFichier)
{
	char Text[255];
	sprintf(Text, "-Line (%d) of file (%s)\nError : %s.", Ligne, pNomFichier
		, pECStringError[ErrorCode]);
	ProcessErreur(Text);
}

void tcErreur::SetErrorText(U32 ErrorCode, char * pTextError, int Ligne, char * pNomFichier)
{
	char Text[255];
	sprintf(Text, "-Line (%d) of file (%s)\nError : %s:%s.", Ligne, pNomFichier
		, pECStringError[ErrorCode],pTextError);
	ProcessErreur(Text);
}

// Ajouter une trace d'erreur
void tcErreur::AddTraceErreur(char * TextErreur)
{
	char Text[255];
	sprintf(Text,"Trace : %s.",TextErreur);
	ProcessErreur(Text);
}

// Traitement de l'erreur
void tcErreur::ProcessErreur(char * TextErreur)
{
	time_t ltime;
	time( &ltime );
	FILE* pFile;

	if(s_TypeMedia & cMediaErrAffichage)
	{
			MessageBox(NULL,TextErreur,cTitreMessage
				,MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
	}

#ifdef _DEBUG
	if(s_TypeMedia & cMediaErrASSERT)
	{
		assert(0);
	}
#endif

	if(s_TypeMedia & cMediaErrFichier) 
	{
		pFile = fopen(s_Fichier,"a");
		if( pFile != NULL)
		{
			fprintf(pFile, "\n\n-%s%s"
						,ctime(&ltime)
						,TextErreur);
			fclose(pFile);
		}
	}

}
