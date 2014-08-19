/*============================================================================
  Project ......................... LDBPC
  Component ....................... LdbpcRes
  File revision.................... $Revision:   1.0  $
  Last modification date .......... $Modtime:   04 Feb 2009 16:32:30  $
  -------------------------------------------------------------------------
  Copyright ... This software is JCI property. Duplication or
                disclosure is prohibited without JCI written permission
  ------------------------------------------------------------------------- 
    
  - This file should only contain data useful to the programmer to use
    this component
  - Component exported macros, constants and types are defined in this file
  - Component exported variables and functions are declared in this file 
    with the "extern" keyword
  
 -------------------------------------------------------------------------
  FONCTION : Gestion des Ressources (Canaux, Flux, Trames)
 ------------------------------------------------------------------------
 Nom et initiales des developpeurs :
		
		Gilles	GUILLEN		GG
		Mickael GRANDSIRE	MG

 Historique du fichier LdbpcRes.c:
 -------------------------------------
 (initiales, date, modification)

 v1.0	:	GG : 20/04/2000	: Creation
 v1.2 :	GG : 20/04/2000	: Modification
 v1.3 :	GG : 07/02/2002	: Modification
 v1.4 :	GG : 13/03/2002	: Ajout des couches CAN + Correction
 v1.5 :	GG : 18/03/2002	: Correction sur la verification des trames
 v1.6 :	GG : 10/06/2002	: Ajout de fonction de demande de modification forcée.
 v1.7 :	GG : 19/09/2002	: Ajout de fonction de comparaison OPENGL

 ------------------------------------------------------------------------

  LdbpcRes.cpp file review :

    PVCS Historic :

    $Log:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/EXT_CMP/CPP_CMP/STK/SIMUL/Kernel/LDBPCRES.CPP-arc  $  
// 
//    Rev 1.0   04 Feb 2009 17:02:24   adzhelp
// Initial revision.
 * 
 *    Rev 1.11   Oct 17 2007 15:21:52   aguillgi
 * PON URD42 VAL 6325 / PON URD45 BODY_SW 968 : LDBPC compile error under Visual Studio 2003. (proposed by Orlin Stoilov, reviewed by Gilles Guillen)
 * 
 *    Rev 1.10   Jul 06 2006 16:42:32   aguillgi
 * PON URD42 DEV 2413 / PON URD42 BODY_SW 1259 :  Add The ScanAll Trace for the All LDB Channel.
 * 
 *    Rev 1.9   31 Jan 2005 11:38:44   abarbae
 * PON URD42 DEV 2379 / PON URD42 BODY_SW 784 : Apply new coding rules base types
 * 
 *    Rev 1.8   Jan 21 2005 09:09:00   aguillg
 * PON URD42 DEV 2359 / PON URD42 BODY_SW 774 :  Add the management of the CAN buses of CANoe from XCAR  
 * 
 *    Rev 1.7   Aug 13 2004 16:33:54   aguillg
 * PON URD42 DEV 1919 / PON URD42 BODY_SW 632 : Creation of a CAN Gateway between X-Car and CANoe
 * 
 *    Rev 1.6   Aug 05 2004 16:21:40   aguillg
 * PON URD42 DEV 1919 / PON URD42 BODY_SW 632 : Creation of a CAN Gateway between X-Car and CANoe  
 * 
 *    Rev 1.5   Jan 19 2004 18:13:18   aguillg
 * PON URD42 DEV 1385 / PON URD45 BODY_SW 277  :    LDBPC fails when the type of lng in tMsg structure is equal U8.
 * 
 *    Rev 1.4   Dec 18 2003 21:48:54   aguillg
 * PON URD45 BODY_SW 267  : Création d'une variable permettant de savoir si on est sous E-Car ou sous R-Car.
 * 
 *    Rev 1.3   Dec 17 2003 22:29:34   aguillg
 * PON URD45 BODY_SW 267  : Création d'une variable permettant de savoir si on est sous E-Car ou sous R-Car.
 * 
 * PON URD42 BODY_SW 371 : Transalate LDB API into english
 * 
 *    Rev 1.2   Nov 14 2003 17:04:28   abarbae
 * PON URD42 BODY_SW 371 : Transalate LDB API into english
 * 
 *    Rev 1.1   Jun 12 2003 12:22:30   aguillg
 * Handle an LDB initialisation function LDBPCInit( )  in the setting.
 * 
 *    Rev 1.0   Apr 30 2003 08:13:08   abarbae
 * Initial revision.
 * 
 *    Rev 1.12   Mar 06 2003 14:21:56   guillen
 * English translation
 * 
 *    Rev 1.11   Nov 07 2002 14:21:02   guillen
 * Correction d'une erreur de compil en cas de non utilisation du CAN
 * 
 *    Rev 1.10   Oct 23 2002 08:36:48   guillen
 * Fin du test unitaire
 * 
 *    Rev 1.9   Oct 15 2002 16:58:50   guillen
 * Fin de Développement - Pour Validation de la v4.08

  ==========================================================================*/

#define LdbpcRes "LdbpcRes"
//--------------------------------------------------------------------------
//---------------- Inclusion de fichiers (système et librairies -----------
//--------------------------------------------------------------------------

#include "stdio.h"
#include "string.h"	
#include "LdbpcRes.h"		// Definit l'interface du Module Donnees

//--------------------------------------------------------------------------
//------- Inclusion des definitions des autres composants utiles ---------
//--------------------------------------------------------------------------
#include "Config.h"	    // Configuration du LDBPC
#include "LDBPCTim.h"	// Definit l'interface du Module Timer
#include "LDBPCDon.h"	// Definit l'interface du Module Donnees
#include "XCarCAN.h" // Definit l'interface du module tcTrameMsgCan

#ifdef CANAL_CAN
#include "tcCanalCan.h" // Definit l'interface du module tcTrameMsgCan
#endif // CANAL_CAN

#ifdef LDBPC_IMAGE_COMPARE
#include "ImgCompare.h" // Definit l'interface du module Compare Bitmap
#endif // LDBPC_IMAGE_COMPARE


//--------------------------------------------------------------------------
//------- Declaration des constantes locales à ce composant --------------
//--------------------------------------------------------------------------
// #define cNomConstante ValeurDeLaConstante
#define cBACK_SLACH "\\"
#define cStrModeAuto	"Auto"
#define cEmission	"Emis"
#define cReception	"Recep"
#define cStrBuffer	"Buffer"
#define cStrSize	"Size"
//--------------------------------------------------------------------------
//------- Declaration des macros locales à ce composant ------------------
//--------------------------------------------------------------------------
// #define mNomMacro (DefinitionDeLaMacro)

#define mCANAL(x)	(m_TabCanal.GetAt(x))
#define mFLUX(x)	(m_TabFlux.GetAt(x))
#define mTRAME(x)	(m_TabTrame.GetAt(x))
#define mCTRL(x)	(m_TabCtrl.GetAt(x))

#define mResVerifier(x,y)	((x < y.GetSize()) && (x >= 0))
#define mResVerifTrame(x)	((mResVerifier(x,m_TabTrame))?cLdbpcOk:cLdbpcErr)
#define mResVerifFlux(x)	((mResVerifier(x,m_TabFlux))?cLdbpcOk:cLdbpcErr)
#define mResVerifCanal(x)	((mResVerifier(x,m_TabCanal) && mCANAL(x))?cLdbpcOk:cLdbpcErr)
#define mResVerifCtrl(x)	((mResVerifier(x,m_TabCtrl))?cLdbpcOk:cLdbpcErr)

#define mTotalCanal		(m_TabCanal.GetSize())
#define mTotalFlux		(m_TabFlux.GetSize())
#define mTotalTrame		(m_TabTrame.GetSize())
#define mTotalCtrl		(m_TabCtrl.GetSize())


 

//--------------------------------------------------------------------------
//------- Definition des types locaux à ce composant ---------------------
//--------------------------------------------------------------------------
// typedef ... tNomType;
//--------------------------------------------------------------------------
//------- Variables locales à ce composant---------------------------------
//--------------------------------------------------------------------------
// static tType NomVariable;
// static tType* pNomVariable;

// Definition du module Ressources
tcRessources Ressources;

//--------------------------------------------------------------------------
//------- Donnees Constantes locales à ce composant ----------------------
//--------------------------------------------------------------------------
// static const tType NomVariable;
//--------------------------------------------------------------------------
//------- Variables exportees par ce composant ---------------------------
//--------------------------------------------------------------------------
// extern tType ComNomVariable; (Com: 3 lettres identifiant ce composant)
// extern tType* pComNomVariable;
extern void LDBPCInit();

//--------------------------------------------------------------------------
//------- Donnees Constantes exportees par ce composant ------------------
//--------------------------------------------------------------------------
// const tType ComNomVariable; (Com: 3 lettres identifiant ce composant)

//--------------------------------------------------------------------------
//------------------------- Fonctions exportees ----------------------------
//--------------------------------------------------------------------------
static char* NewStrCat(char * pStr1, char * pStr2 = NULL, char * pStr3 = NULL);

static char* NewStrCat(char * pStr1, char * pStr2, char * pStr3)
{
    U32 Length;
    char * StrNew;
	if(pStr1 == NULL)	 
	{ 
		mLDBPCErreur(cLdbpcErr); 
		return(NULL);
	}

	// Calcul de la taille totale
	Length = 1 + strlen(pStr1);
    if(pStr2 != NULL)    Length += strlen(pStr2);
    if(pStr3 != NULL)    Length += strlen(pStr3);

	// Allocation memoire pour le stockage
	StrNew = (char *) new char[Length * sizeof(char)];
    
    if(StrNew != NULL)
    {
        memset(StrNew,0,Length * sizeof(char));
        // Copie
        strcpy(StrNew , pStr1);
        if(pStr2 != NULL) strcpy(StrNew + strlen(StrNew) , pStr2);
        if(pStr3 != NULL) strcpy(StrNew + strlen(StrNew) , pStr3);
    }
    return(StrNew);
}

void CallBackFiStd(S32 Ref)
{
	Ressources.FinActionFi((S32) Ref);
}

void CallBackFnipStd(S32 Ref)
{
	Ressources.ActionFni((S32) Ref, cFluxNIP);
}

void CallBackFnicStd(S32 Ref)
{
	Ressources.ActionFni((S32) Ref, cFluxNIC);
}

void CallBackCtrlSor(S32 Ref)
{
	Ressources.FinControle(Ref);
}

void CallBackCtrlEnt(S32 Ref)
{
	Ressources.CBControler(Ref);
}


//--------------------------------------------------------------------------
//--------------- Implementation de la classe tcRessources ----------------
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
//	Construction du Module Ressources
//--------------------------------------------------------------------------
tcRessources::tcRessources()
{
	// Initialisation des trames, flux et canaux
	m_TabCanal.SetSize(0);
	m_TabFlux.SetSize(0);
	m_TabTrame.SetSize(0);
	m_TabCtrl.SetSize(0);
	m_pCBCanalEnCours = NULL;
	m_RefUCEenVeille = 0;
}

//--------------------------------------------------------------------------
//	Destruction du Module Ressources
//--------------------------------------------------------------------------
tcRessources::~tcRessources()
{
	// Destruction des trames, flux et canaux
	Destruction();

	// Suppression des trames, flux et canaux
	m_TabCanal.RemoveAll();
	m_TabFlux.RemoveAll();
	m_TabTrame.RemoveAll();
	m_TabCtrl.RemoveAll();
}

void tcRessources::Initialiser()
{
	S32 Id;
	tLDBPCStatut Res = cLdbpcOk;

	// Initialisation des canaux
	for(Id = 0; Id < mTotalCanal; Id ++)
	{
		if(mCANAL(Id))
		{
      mCANAL(Id)->Reset();
		}
	}

	// Initialisation des Flux
	for(Id = 0; Id < mTotalFlux; Id ++)
	{
		mFLUX(Id)->SetBufferTemp();
	}

	// Initialisation des Trames
	for(Id = 0; Id < mTotalTrame; Id ++)
	{
		mTRAME(Id)->Initialiser();
	}

    // Initialisation des messages segmentés
#ifdef CANAL_CAN
	CanalCan.Initialisation();
#endif // CANAL_CAN

  LDBPCInit();
}

//--------------------------------------------------------------------------
// Création d'un canal
//--------------------------------------------------------------------------

// Create a CAN for XCAN Channel
tLDBPCStatut tcRessources::CreateChannelXCAN(tXCanChannel * pStruct)
{
    ASSERT(pStruct != NULL);
    ASSERT(pStruct->pCallBackStruct != NULL);
    CChannelCAN * pChan = NULL;
    tLDBPCStatut Res = cLdbpcErr;
    tCallBackCanal * pStructCB = pStruct->pCallBackStruct;
    tChannel ChannelId = pStructCB->ChannelId;
    //  mCANAL(pStruct->pCallBackStruct->ChannelId)->XCanConnect(pStruct);

	// Verification de l'existance du canal
	Res = mResVerifCanal(ChannelId);
	if(Res == cLdbpcErr)	// N'existe pas
	{
		// Creation du canal
		pChan = new CChannelCAN(pStruct);
		// S'il a ete correctement cree
		if(pChan)
		{
			// Sauvegarde de la structure de callback
			m_pCBCanalEnCours = pStructCB;
			// Ajout du canal dans le tableau
			m_TabCanal.SetAtGrow(ChannelId, (tcCanal *)pChan);
			Res = cLdbpcOk;
		}
		else Res = mLDBPCErreur(cLdbpcErrAllocMem);
	}
	else	Res = mLDBPCErreur(cLdbpcErrParCanal);
	
	return Res;
}

// Create a LDBPC Channel
tLDBPCStatut tcRessources::CreateChannel(tCallBackCanal * pStruct)
{
	tLDBPCStatut Res = cLdbpcOk;
	tcCanal * pCanal = NULL;
  
  ASSERT(pStruct != NULL);

	// Verification de la structure de callback
	if(pStruct == NULL)	Res = mLDBPCErreur(cLdbpcErrParStructCB);
	if(Res == cLdbpcOk)
	{
		// Verification de l'existance du canal
		Res = mResVerifCanal(pStruct->ChannelId);
		if(Res == cLdbpcErr)	// N'existe pas
		{
			// Creation du canal
			pCanal = new tcCanal(pStruct);
            pCanal->m_SADAdrTrace.SADConnect(pStruct->ChannelName);
			// S'il a ete correctement cree
			if(pCanal)
			{
				// Sauvegarde de la structure de callback
				m_pCBCanalEnCours = pStruct;
				// Ajout du canal dans le tableau
				m_TabCanal.SetAtGrow(pStruct->ChannelId, pCanal);
				Res = cLdbpcOk;
			}
			else Res = mLDBPCErreur(cLdbpcErrAllocMem);
		}
		else	Res = mLDBPCErreur(cLdbpcErrParCanal);
	}
	
	return Res;
}

// ------------------------------------------------------------------------
// Création d'un controle
// ------------------------------------------------------------------------
tLDBPCStatut tcRessources::CreerControle(S32 * pRefCtrl, tChannel RefCan
		, char * pNom, tCtrl Ctrl, tDelay Duree, tDLLType Type)
{
	tLDBPCStatut Res = cLdbpcErr;
	tcCtrl * pCtrl= NULL;
	S32 RefEvt;
	char * pGroupe = NULL;
	S32 It;

	// Verification de l'existence du canal
	if(!mResVerifCanal(RefCan)) 
		return mLDBPCErreur(cLdbpcErrParCanal);

	// Verification des controles
	for(It = 0; It < mTotalCtrl; It++)
	{
		if((mCTRL(It)->LireRefCanal() == RefCan)
			&& (mCTRL(It)->LireCtrl() == Ctrl))
				return mLDBPCErreur(cLdbpcErrParCtrl);
	}

	// Lire le nom du canal
	mCANAL(RefCan)->LireNom(&pGroupe);

	// Creation du controle
	pCtrl = new tcCtrl(Ctrl, RefCan, Duree, Type);
	// S'il a ete correctement cree
	if(pCtrl)
	{
		// Ajout du controle dans un tableau
		S32 Ref = m_TabCtrl.Add(pCtrl);

		// Mise à jour de la reference (si elle existe)
		if(pRefCtrl)
		{
			*pRefCtrl = Ref;
		}

		if(Type == cDLLEntree)
		{
			Res = Donnees.CreerDonnee(&RefEvt,pNom,Type,cDLLTypeEvt,0,(U32)0,pGroupe,&CallBackRef,(tpParam)&CallBackCtrlEnt);
		}
		else
		{
			Res = Donnees.CreerDonnee(&RefEvt,pNom,Type,cDLLTypeEvt,0,(U32)0,pGroupe);
		}
		pCtrl->EcrireRefEvt(RefEvt);
	}
	else 
	{
		Res = mLDBPCErreur(cLdbpcErrAllocMem);
	}
	return Res;
}


// ------------------------------------------------------------------------
// Création d'un flux 
// ------------------------------------------------------------------------
tLDBPCStatut tcRessources::CreerFlux(tInfoFlux * pIflux)
{
	tLDBPCStatut Res = cLdbpcOk;
	tcFlux * pFlux = NULL;
	S32 RefFlux;

	// S'il s'agit d'un flux initie attache
	if(pIflux->RefCan != -1)
	{
		Res = mResVerifCanal(pIflux->RefCan);
		if(Res != cLdbpcOk)	 Res = mLDBPCErreur(cLdbpcErrParCanal);
	}

	if(Res == cLdbpcOk)
	{
		// S'il s'agit d'un flux initie attache
		if(pIflux->RefCan != -1)
		{
			// Verifie si le canal ne possede pas deja ce flux
			Res = LireRefFlux(pIflux->RefCan ,pIflux->TypeFlux ,&RefFlux);
			if(Res == cLdbpcOk)	Res = mLDBPCErreur(cLdbpcErrParFlux);
			else Res = cLdbpcOk;
		}
	}

	if(Res == cLdbpcOk)
	{
		switch(pIflux->TypeFlux)
		{
		case cFluxIP:

			// Creation du flux initie
			pFlux = (tcFlux *) new tcFluxI(mCANAL(pIflux->RefCan), pIflux);
			// S'il a bien ete cree
			if(pFlux)
			{
				// Ajout du flux dans un tableau
				RefFlux = m_TabFlux.Add(pFlux);
				
				// Mise à jour de la reference (si elle existe)
				if(pIflux->pRef)
				{
					*(pIflux->pRef) = RefFlux;
				}

				if(pIflux->RefCan != -1)
				{
					// Mise a jour de la fonction de callback en Emission
					mFLUX(RefFlux)->MajCallBack(m_pCBCanalEnCours->pCallBackTx);
					// Attache le flux au canal
					Res = mCANAL(pIflux->RefCan)->AttacherFlux(RefFlux, pIflux->TypeFlux);
				}
				else
				{
					Res = cLdbpcOk;
				}
			}
			else Res = mLDBPCErreur(cLdbpcErrAllocMem);
			break;

		case cFluxIC:

			// Creation du flux initie
			pFlux = (tcFlux *) new tcFluxI(mCANAL(pIflux->RefCan), pIflux);
			// S'il a bien ete cree
			if(pFlux)
			{
				// Ajout du flux dans un tableau
				RefFlux = m_TabFlux.Add(pFlux);
				
				// Mise à jour de la reference (si elle existe)
				if(pIflux->pRef)
				{
					*(pIflux->pRef) = RefFlux;
				}

				if(pIflux->RefCan != -1)
				{
					// Mise a jour de la fonction de callback en Reception
					mFLUX(RefFlux)->MajCallBack(m_pCBCanalEnCours->pCallBackRx);
					// Attache le flux au canal
					Res = mCANAL(pIflux->RefCan)->AttacherFlux(RefFlux, pIflux->TypeFlux);
				}
				else
				{
					Res = cLdbpcOk;
				}
			}
			else Res = mLDBPCErreur(cLdbpcErrAllocMem);
			break;

		case cFluxNIP:

			// Creation du flux initie
			pFlux = (tcFlux *) new tcFluxNIP(mCANAL(pIflux->RefCan), pIflux);
			// S'il a bien ete cree
			if(pFlux)
			{
				// Ajout du flux dans un tableau
				RefFlux = m_TabFlux.Add(pFlux);
				
				// Mise à jour de la reference (si elle existe)
				if(pIflux->pRef)
				{
					*(pIflux->pRef) = RefFlux;
				}

				if(pIflux->RefCan != -1)
				{
					// Attache le flux au canal
					Res = mCANAL(pIflux->RefCan)->AttacherFlux(RefFlux, pIflux->TypeFlux);
				}
				else
				{
					Res = cLdbpcOk;
				}
			}
			else Res = mLDBPCErreur(cLdbpcErrAllocMem);
			break;

		case cFluxNIC:

			// Creation du flux initie
			pFlux = (tcFlux *) new tcFluxNIC(mCANAL(pIflux->RefCan), pIflux);
			// S'il a bien ete cree
			if(pFlux)
			{
				// Ajout du flux dans un tableau
				RefFlux = m_TabFlux.Add(pFlux);
				
				// Mise à jour de la reference (si elle existe)
				if(pIflux->pRef)
				{
					*(pIflux->pRef) = RefFlux;
				}

				if(pIflux->RefCan != -1)
				{
					// Attache le flux au canal
					Res = mCANAL(pIflux->RefCan)->AttacherFlux(RefFlux, pIflux->TypeFlux);
				}
				else
				{
					Res = cLdbpcOk;
				}
			}
			else Res = mLDBPCErreur(cLdbpcErrAllocMem);
			break;

		default:
			Res = mLDBPCErreur(cLdbpcErrParFlux);
		}
	}
	return Res;
}

//--------------------------------------------------------------------------
// Création d'une trame generique
//--------------------------------------------------------------------------
tLDBPCStatut tcRessources::CreateFrame(tInfoTrame * pInfoTrame)
{
    tLDBPCStatut Res = cLdbpcOk;
    tInfoBuildFrame InfoBuildFrame;
	S32 RefTrame;

    memset(&InfoBuildFrame,0,sizeof(tInfoBuildFrame));
    InfoBuildFrame.pInfoFrame = pInfoTrame;
    InfoBuildFrame.pCanal=mFLUX(pInfoTrame->RefFlux)->GetChannel();

    // Vérification de la structure
    Res = CheckFrame(pInfoTrame);
    if(Res != cLdbpcOk)
    {
        return(cLdbpcErr);
    }

    if(pInfoTrame->pRef == NULL)
    {
        pInfoTrame->pRef = &RefTrame;
    }

    // Construction des nom des données et du nom du groupe
	Res = NewDataFrameName(&InfoBuildFrame);
    if(Res != cLdbpcOk)
    {
        // Destruction du nom des données et du nom du groupe
        DeleteDataFrameName(&InfoBuildFrame);
        return(cLdbpcErr);
    }

    // Création des données
    Res = CreateDataFrame(&InfoBuildFrame);

    // Destruction du nom des données et du nom du groupe
    DeleteDataFrameName(&InfoBuildFrame);

    if(Res != cLdbpcOk)
    {
        return(cLdbpcErr);
    }

    // Construction de la Trame
    Res = BuildFrame(&InfoBuildFrame);
    if(Res != cLdbpcOk)
    {
        return(cLdbpcErr);
    }

    // Mise à jour de la CallBack pour les trames de Flux Non Initié
    if(pInfoTrame->TypeFlux == cFluxNIC)
    {
        SetCallBackNIC(&InfoBuildFrame);
    }
    else if (pInfoTrame->TypeFlux == cFluxNIP)
    {
        SetCallBackNIP(&InfoBuildFrame);
    }
    return(cLdbpcOk);
}

// Verification de la structure de creation de la trame
tLDBPCStatut tcRessources::CheckFrame(tInfoTrame * pInfoTrame)
{
    S32 It;
    char Texte[500];
    char * pNomTest	= NULL;
    tChannel RefCan;
    tLDBPCStatut Res = cLdbpcOk;
    
    // Si la trame n'a pas de info
    if(pInfoTrame == NULL)
    {
        mLDBPCErreur("Call RESCreerTrame(NULL) is Forbiden.");
        return(cLdbpcErrParPointNul);
    }

    // Si la trame n'a pas de nom
	if(!pInfoTrame->pName)		
    {
        mLDBPCErreur("Call RESCreerTrame(FrameInfo), the frame must have a name.");
        return(cLdbpcErrParPointNul);
    }

    // Si la trame et attachée au flux ET n'a pas de nom de groupe
    if((pInfoTrame->RefFlux == cNoFlux) && (!pInfoTrame->pGroupName))
    {
        sprintf(Texte,"Call RESCreerTrame(%s), the frame is unlink by a flow,"
            "so it must have a group name.",pInfoTrame->pName);
        mLDBPCErreur(Texte);
        return(cLdbpcErrParPointNul);
    }

    // Si la trame et attachée au flux
	if(pInfoTrame->RefFlux != cNoFlux)
	{
        // Verification de l'existance du flux
		Res = mResVerifFlux(pInfoTrame->RefFlux);

		// Verification du type de flux
		if(Res == cLdbpcOk)
        {
			// Lecture du type de flux 
			if(pInfoTrame->TypeFlux != mFLUX(pInfoTrame->RefFlux)->LireType())
            {
                sprintf(Texte,"Call RESCreerTrame(%s), the frame is link with"
                    "a failed flow.",pInfoTrame->pName);
                mLDBPCErreur(Texte);
                return(cLdbpcErrParFlux);
            }
        }

		if(Res == cLdbpcOk)
	    {
		    // Lecture de la reference de canal
		    RefCan = mFLUX(pInfoTrame->RefFlux)->LireRefCanal();

		    // Verification de l'existance du canal
		    Res = mResVerifCanal(RefCan);
            if(Res != cLdbpcOk)
            {
                sprintf(Texte,"Call RESCreerTrame(%s), the flow of the frame "
                    "is link with a failed Channel.",pInfoTrame->pName);
                mLDBPCErreur(Texte);
                return(cLdbpcErrParCanal); 
            }

	    }

    }

	// Verification des adresses et noms de trames
	for(It = 0; It < mTotalTrame; It++)		
	{
		if(mTRAME(It)->LireRefFlux() == pInfoTrame->RefFlux)
		{
			mTRAME(It)->LireNom(&pNomTest);
            // Si une trame existante possede le meme nom (Dans le meme Flux)
			if(!strcmp(pNomTest,pInfoTrame->pName))
            {
                sprintf(Texte,"Call RESCreerTrame(%s),another frame is "
                    "the same name. (in the channel)",pInfoTrame->pName);
                mLDBPCErreur(Texte);
                return(cLdbpcErrParNom);
            }

            // Si une trame existante possede la meme adresse (Dans le meme Flux)
			if(mTRAME(It)->LireAdresse() == pInfoTrame->Address)
            {
                sprintf(Texte,"Call RESCreerTrame(%s),another frame is "
                    "the same address. (in the channel)",pInfoTrame->pName);
                mLDBPCErreur(Texte);
                return(cLdbpcErrParAdresse);
            }
		}
	}

	// Verification du type de la trame
    if(pInfoTrame->TypeFrame == cTypeFrameVarSize)
    {
        if(pInfoTrame->TypeFlux ==  cFluxNIP)
        {
            sprintf(Texte,"Call RESCreerTrame(%s), a variable size frame is "
                "not available with a produced not initiated flow",pInfoTrame->pName);
            mLDBPCErreur(Texte);
            return(cLdbpcErr);
        }
        else if(pInfoTrame->TypeFlux ==  cFluxIC)
        {
            sprintf(Texte,"Call RESCreerTrame(%s), a variable size frame is "
                "not available with a consumed initiated flow",pInfoTrame->pName);
            mLDBPCErreur(Texte);
            return(cLdbpcErr);
        }
    }
    return(Res);
}

// Création des données associées à la creation de la trame
tLDBPCStatut tcRessources::CreateDataFrame(tInfoBuildFrame * pBuildFrame)
{
	char * pNomEvt		= NULL;
	char * pNomGroupe	= NULL;
    tLDBPCStatut Res = cLdbpcOk;
    tInfoTrame * pInfoTrame = pBuildFrame->pInfoFrame;

    // Pour les flux initiés
	if(mFluxInitie(pInfoTrame->TypeFlux))
	{
        // Création de la donnée : Evenement de la trame
		Res = Donnees.CreerDonnee(&(pBuildFrame->EvtRef),pBuildFrame->pEvtName,
            cDLLSortie,cDLLTypeEvt,0,(U32)0,pInfoTrame->pGroupName);
        if(Res != cLdbpcOk) 
        {
            return(Res);
        }

		// Si c'est une trame à longueur variable
		if(pInfoTrame->TypeFrame == cTypeFrameVarSize)
		{
			// Création de la donnée : Buffer de la trame
			Res = Donnees.CreerDonnee(&(pBuildFrame->BufferRef),
				pBuildFrame->pBufferName,cDLLSortie, cDLLTypeTab,
				pInfoTrame->MaxSize*8,(U8*)NULL,pInfoTrame->pGroupName);
			if(Res != cLdbpcOk) 
			{
				return(Res);
			}
        
			// Création de la donnée : Longueur du buffer de la trame
			Res = Donnees.CreerDonnee(&(pBuildFrame->BufferSizeRef),
				pBuildFrame->pBufferSizeName,cDLLSortie, cDLLTypeVal,32
			   ,(U32)0,pInfoTrame->pGroupName);
		}
	}
    // Pour les flux non initiés
	else if(mFluxNonInitie(pInfoTrame->TypeFlux))
    {
        // Création de la donnée RxMode
		Res = Donnees.CreerDonnee(&(pBuildFrame->RxModeRef),
            pBuildFrame->pRxModeName, cDLLEntree ,cDLLTypeVal , 8,
            (S32)pInfoTrame->RxMode, pInfoTrame->pGroupName);
        if(Res != cLdbpcOk) 
        {
            return(Res);
        }
        // Si Flux Non initié Consommé
        if(pInfoTrame->TypeFlux == cFluxNIC)
        {
			// Creation de l'évenement en entree
			Res = Donnees.CreerDonnee(&(pBuildFrame->EvtRef),
                pBuildFrame->pEvtName, cDLLEntree, cDLLTypeEvt, 0, (U32)0 ,
                pInfoTrame->pGroupName,&CallBackRef,(tpParam)CallBackFnicStd);
        }
        // Si Flux Non initié Produit
        else if(pInfoTrame->TypeFlux == cFluxNIP)
        {
			// Creation de l'évenement en entree
			Res = Donnees.CreerDonnee(&(pBuildFrame->EvtRef),
                pBuildFrame->pEvtName, cDLLEntree, cDLLTypeEvt, 0, (U32)0 ,
                pInfoTrame->pGroupName,&CallBackRef,(tpParam)CallBackFnipStd);
        }
        else
        {
			Res = mLDBPCErreur(cLdbpcErrParFlux);
        }

		// Si c'est une trame à longueur variable
		if((pInfoTrame->TypeFrame == cTypeFrameVarSize) && (Res == cLdbpcOk))
		{
			// Création de la donnée : Buffer de la trame
			Res = Donnees.CreerDonnee(&(pBuildFrame->BufferRef),
				pBuildFrame->pBufferName, cDLLEntree, cDLLTypeTab,
				pInfoTrame->MaxSize*8,(U8*)NULL,pInfoTrame->pGroupName);
			if(Res != cLdbpcOk) 
			{
				return(Res);
			}
        
			// Création de la donnée : Longueur du buffer de la trame
			Res = Donnees.CreerDonnee(&(pBuildFrame->BufferSizeRef),
				pBuildFrame->pBufferSizeName, cDLLEntree, cDLLTypeVal,32
			   ,(U32)0,pInfoTrame->pGroupName);
		}
    }
    else
    {
		Res = mLDBPCErreur(cLdbpcErrParFlux);
    }


    return(Res);
}

// ------------------------------------------------------------------------
// Chargement du Nom des données
// !!! ATTENTION ALLOCATION SANS DESALLOCATION !!!
// ------------------------------------------------------------------------
tLDBPCStatut tcRessources::NewDataFrameName(tInfoBuildFrame * pBF)
{
	tLDBPCStatut	Res			= cLdbpcOk;
	char *			pPrefix		= NULL;
	tChannel			RefCan		= -1;
    tInfoTrame * pIT = pBF->pInfoFrame;

    // Si la trame est liée à un flux
	if(pIT->RefFlux != cNoFlux)
    {
        RefCan = mFLUX(pIT->RefFlux)->LireRefCanal();
		// pPrefix -> le nom du canal
		mCANAL(RefCan)->LireNom(&pPrefix);
    }
    else
    {
		// pPrefix -> le nom du groupe
        pPrefix		= pIT->pGroupName;
    }

    // Si le flux est initié
	if(mFluxInitie(pIT->TypeFlux))
	{
		// Construction du nom de l'evt
		pBF->pEvtName = NewStrCat(pPrefix,cEmission,pIT->pName);
        if(pBF->pEvtName == NULL)
		{
	        Res = mLDBPCErreur(cLdbpcErrAllocMem);
        }
    }
    // Si le flux est non initié
	else
	{
		// Construction du nom de l'evt
		pBF->pEvtName = NewStrCat(pPrefix,cReception,pIT->pName);
        if(pBF->pEvtName == NULL)
		{
	        Res = mLDBPCErreur(cLdbpcErrAllocMem);
        }

		// Construction du nom de la donnée RxMode
		pBF->pRxModeName = NewStrCat(pPrefix,pIT->pName,cStrModeAuto);
        if(pBF->pRxModeName == NULL)
		{
	        Res = mLDBPCErreur(cLdbpcErrAllocMem);
        }
    }

    if((pIT->RefFlux != cNoFlux) && (Res == cLdbpcOk))
    {
		// Construction du nom du groupe
		pIT->pGroupName = NewStrCat(pPrefix,cBACK_SLACH,pIT->pName);
        if(pIT->pGroupName == NULL)
		{
	        Res = mLDBPCErreur(cLdbpcErrAllocMem);
        }
    }

	// Si c'est une trame à longueur variable
	if((pIT->TypeFrame == cTypeFrameVarSize) && (Res == cLdbpcOk))
	{
		// Construction du nom du Buffer
		pBF->pBufferName = NewStrCat(pPrefix,pIT->pName,cStrBuffer);
		if(pBF->pBufferName == NULL)
		{
			Res = mLDBPCErreur(cLdbpcErrAllocMem);
		}

		// Construction du nom de la taille du buffer
		pBF->pBufferSizeName = NewStrCat(pPrefix,pIT->pName,cStrSize);
		if(pBF->pBufferSizeName == NULL)
		{
			Res = mLDBPCErreur(cLdbpcErrAllocMem);
		}
	}

	return Res;
}

void tcRessources::DeleteDataFrameName(tInfoBuildFrame * pBuildFrame)
{
    tInfoTrame * pInfoTrame = pBuildFrame->pInfoFrame;

    // Destruction du nom de l'evénement
	if(pBuildFrame->pEvtName)
    {
        delete [] pBuildFrame->pEvtName;
    }

    // Destruction du nom du buffer
	if(pBuildFrame->pBufferName)
    {
        delete [] pBuildFrame->pBufferName;
    }

    // Destruction du nom de la taille du buffer
	if(pBuildFrame->pBufferSizeName)
    {
        delete [] pBuildFrame->pBufferSizeName;
    }

    // Destruction du nom du group si la trame est liée à un flux
	if((pInfoTrame->RefFlux != cNoFlux) && (pInfoTrame->pGroupName))
    {
        delete [] pInfoTrame->pGroupName;
    }

    // Destruction du nom du RxMode
	if(pBuildFrame->pRxModeName)
    {
        delete [] pBuildFrame->pRxModeName;
    }
}

tLDBPCStatut tcRessources::BuildFrame(tInfoBuildFrame * pBuildFrame)
{
    tLDBPCStatut	Res			= cLdbpcOk;
    tcTrame * pTrame	= NULL;
    tInfoTrame * pIT = pBuildFrame->pInfoFrame;

	switch(pIT->TypeFlux)
	{
	case cFluxIC:
	case cFluxIP:
			pTrame = (tcTrame *) new tcTrameFi(pBuildFrame);
			break;
	case cFluxNIC:
			pTrame = (tcTrame *) new tcTrameFnic(pBuildFrame);
			break;
	case cFluxNIP:
			pTrame = (tcTrame *) new tcTrameFnip(pBuildFrame);
			break;
	default:
			Res = mLDBPCErreur(cLdbpcErrFlux);
	}

	// Ajout de la trame dans la liste
	if(pTrame != NULL)
	{
		*(pIT->pRef) = (S32) m_TabTrame.Add(pTrame);
		if(pIT->RefFlux != cNoFlux)
		{
			// Attacher la trame
			Res = mFLUX(pIT->RefFlux)->Attacher(*(pIT->pRef));

			// Memorise la taille de max de la trame
			mFLUX(pIT->RefFlux)->SetBufferTempLng(pIT->MaxSize);
		}
        
        // Mise à jour de la duree de transmission
	    if((Res == cLdbpcOk) && mFluxInitie(pIT->TypeFlux))
        {
		    mTRAME(*(pIT->pRef))->EcrireDuree(pIT->TxTime);
        }
	}
	else
    {
        Res = mLDBPCErreur(cLdbpcErrAllocMem);
    }

    return(Res);
}

void tcRessources::SetCallBackNIP(tInfoBuildFrame * pBF)
{
	tAddress	Adr;
	S32		Id;
	tTxSpontWithAddr * pEmissionSp = NULL;
    tInfoTrame * pIT = pBF->pInfoFrame;

	// Si la callback transmise est nulle
	if(pIT->pRxNIPCallBackFrame == NULL) 
	{
		// Lecture de l'adresse de la trame
		Adr = mTRAME(*(pIT->pRef))->LireAdresse();
		// Recherche de la callback standard associee a la trame
		for(Id = 0 ; Id < m_pCBCanalEnCours->NbTxSpont 
			; Id++)
		{
			pEmissionSp = &(m_pCBCanalEnCours->pTxSpontWithAddr[Id]);
			// Si la callback associee a la trame est trouvee
			if((pEmissionSp != NULL) && (pEmissionSp->Address == Adr))
			{
				// Recuperation de la callback standard
				pIT->pRxNIPCallBackFrame = pEmissionSp->pCallBackStatus;
				break;
			}
		}
	}
	// Mise à jour du declencheur de la trame
	((tcTrameFnip*)mTRAME(*(pIT->pRef)))->MajDeclencheur(pBF->RxModeRef,
        pIT->RxPhase, pIT->RxPeriod, pIT->pRxNIPCallBackFrame);
}

void tcRessources::SetCallBackNIC(tInfoBuildFrame * pBF)
{
	tAddress	Adr;
	S32		Id;
	tRxSpontWithAddr *	pReceptionSp;
    tInfoTrame * pIT = pBF->pInfoFrame;

    // Si la callback transmise est nulle
	if(pIT->pRxNICCallBackFrame == NULL)
	{
		// Lecture de l'adresse de la trame
		Adr = mTRAME(*(pIT->pRef))->LireAdresse();
		// Recherche de la callback standard associee a la trame
		for(Id = 0 ; Id < m_pCBCanalEnCours->NbRxSpont ; Id++)
		{
			pReceptionSp = &(m_pCBCanalEnCours->pRxSpontWithAddr[Id]);
			// Si la callback associee a la trame est trouvee
			if((pReceptionSp != NULL) && (pReceptionSp->Address == Adr))
			{
				// Recuperation de la callback standard
				pIT->pRxNICCallBackFrame = pReceptionSp->pCallBackRx;
				break;
			}
		}
	}
	// Mise à jour du declencheur de la trame
	mTRAME(*(pIT->pRef))->MajDeclencheur(pBF->RxModeRef, pIT->RxPhase,
        pIT->RxPeriod, pIT->pRxNICCallBackFrame);
}

//--------------------------------------------------------------------------
// Attacher une entree ou une sortie a une trame avec sa position dans la trame
//--------------------------------------------------------------------------
tLDBPCStatut tcRessources::AttacherDonnee(S32 RefDonnee, S32 RefTrame
										  , U32 Position)
{
	tLDBPCStatut Res = cLdbpcErrTrame;

	// Verification de l'existance de la trame
	if(mResVerifTrame(RefTrame) == cLdbpcOk)
	{
		// Ajouter une donnee a une trame
		Res = mTRAME(RefTrame)->AjouterDonnee(RefTrame, RefDonnee, Position);
	}
	return Res;
}

//--------------------------------------------------------------------------
// Création d'une sortie < 32bits
//--------------------------------------------------------------------------
tLDBPCStatut tcRessources::CreerSortie(S32 * pRef, S32 RefTrame
, char * pNom, U32 TailleBit, U32 ValeurInit, U32 Position )
{
	tLDBPCStatut Res;
	S32 Ref;
	char * pGroupe = NULL;

	// Verification de l'existance de la trame
	if(mResVerifTrame(RefTrame) != cLdbpcOk)
		return mLDBPCErreur(cLdbpcErrParTrame);

	// Vérification que la trame est de flux produit
	if(!mFluxProduit(mTRAME(RefTrame)->LireType()))
		return mLDBPCErreur(cLdbpcErrParTrame);

	// Charger le nom du groupe
	Res = ChargerNomGroupe(RefTrame, &pGroupe);
	if(Res != cLdbpcOk)
		return mLDBPCErreur(Res);

	Res = Donnees.CreerDonnee(&Ref,pNom,cDLLSortie,cDLLTypeVal,TailleBit
		,ValeurInit,pGroupe);

	if(Res == cLdbpcOk)
	{
		// Attacher la sortie < 32bits à la trame
		Res = AttacherDonnee(Ref, RefTrame, Position);
		if(Res != cLdbpcOk)
			return	mLDBPCErreur(Res);
	
		if(pRef) *pRef = Ref;
		// Liberation du pointeur
		if(pGroupe)	delete [] pGroupe;
	}

	return Res;
}

//--------------------------------------------------------------------------
// Création d'une sortie > 32bits
//--------------------------------------------------------------------------
tLDBPCStatut tcRessources::CreerSortie(S32 * pRef, S32  RefTrame, char * pNom
	, U32 TailleBit,	U8 * pBufferInit, U32 Position)
{
	tLDBPCStatut Res;
	S32 Ref;
	char * pGroupe = NULL;

	// Verification de l'existance de la trame
	if(mResVerifTrame(RefTrame) != cLdbpcOk)
		return mLDBPCErreur(cLdbpcErrParTrame);

	// Vérification que la trame est de flux produit
	if(!mFluxProduit(mTRAME(RefTrame)->LireType()))
		return mLDBPCErreur(cLdbpcErrParTrame);

	// Charger le nom du groupe
	Res = ChargerNomGroupe(RefTrame, &pGroupe);
	if(Res != cLdbpcOk)
		return mLDBPCErreur(Res);

	// Creer la sortie > 32bits (DLL)
	Res = Donnees.CreerDonnee(&Ref,pNom,cDLLSortie,cDLLTypeTab,TailleBit,pBufferInit,pGroupe);

	if(Res == cLdbpcOk)
	{
		// Attacher la sortie < 32bits à la trame
		Res = AttacherDonnee(Ref, RefTrame, Position);
		if(Res != cLdbpcOk)
			return	mLDBPCErreur(Res);
	
		if(pRef) *pRef = Ref;
		// Liberation du pointeur
		if(pGroupe)	delete [] pGroupe;
	}

	return Res;
}

//--------------------------------------------------------------------------
// Création d'une entree < 32bits
//--------------------------------------------------------------------------
tLDBPCStatut tcRessources::CreerEntree(S32 * pRef, S32 RefTrame, char * pNom
	, U32 TailleBit, U32 valeurInit, U32 Position)
{
	tLDBPCStatut Res = cLdbpcOk;
	S32 Ref;
	char * pGroupe = NULL;

	// Verification de l'existance de la trame
	if(mResVerifTrame(RefTrame) != cLdbpcOk)
		return mLDBPCErreur(cLdbpcErrParTrame);

	// Vérification que la trame est de flux consomme
	if(mFluxProduit(mTRAME(RefTrame)->LireType()))
		return mLDBPCErreur(cLdbpcErrParTrame);

	// Charger le nom du groupe
	Res = ChargerNomGroupe(RefTrame, &pGroupe);

	if(Res != cLdbpcOk)
		return mLDBPCErreur(Res);

	// Creer la entree < 32bits (DLL)
	Res = Donnees.CreerDonnee(&Ref,pNom,cDLLEntree,cDLLTypeVal,TailleBit,valeurInit,pGroupe);
	if(Res == cLdbpcOk)
	{
		// Attacher la entree < 32bits à la trame
		Res = AttacherDonnee(Ref, RefTrame, Position);
		if(Res != cLdbpcOk)
			return	mLDBPCErreur(Res);
	
		if(pRef) *pRef = Ref;
		// Liberation du pointeur
		if(pGroupe)	delete [] pGroupe;
	}

	return Res;
}

//--------------------------------------------------------------------------
// Création d'une entree > 32bits
//--------------------------------------------------------------------------
tLDBPCStatut tcRessources::CreerEntree(S32 * pRef, S32 RefTrame, char * pNom
	, U32 TailleBit, U8 * pBufferInit, U32 Position)
{
	tLDBPCStatut Res;
	S32 Ref;
	char * pGroupe = NULL;

	// Verification de l'existance de la trame
	if(mResVerifTrame(RefTrame) != cLdbpcOk)
		return mLDBPCErreur(cLdbpcErrParTrame);

	// Vérification que la trame est de flux consomme
	if(mFluxProduit(mTRAME(RefTrame)->LireType()))
		return mLDBPCErreur(cLdbpcErrParTrame);

	// Charger le nom du groupe
	Res = ChargerNomGroupe(RefTrame, &pGroupe);
	if(Res != cLdbpcOk)
		return mLDBPCErreur(Res);

	// Creer la entree > 32bits (DLL)
	Res = Donnees.CreerDonnee(&Ref,pNom,cDLLEntree,cDLLTypeTab,TailleBit,(U8 *)pBufferInit,pGroupe);
	if(Res == cLdbpcOk)
	{
		// Attacher la entree < 32bits à la trame
		Res = AttacherDonnee(Ref, RefTrame, Position);
		if(Res != cLdbpcOk)
			return	mLDBPCErreur(Res);
	
		if(pRef) *pRef = Ref;
		// Liberation du pointeur
		if(pGroupe)	delete [] pGroupe;
	}

	return Res;
}



//--------------------------------------------------------------------------
// Création d'une entree/sortie < 32bits
//--------------------------------------------------------------------------
tLDBPCStatut tcRessources::CreerEntSor(S32 * pRef, S32 RefTrame, char * pNom
	, U32 TailleBit, U32 valeurInit, U32 Position)
{
	tLDBPCStatut Res = cLdbpcOk;
	S32 Ref;
	char * pGroupe = NULL;

	// Verification de l'existance de la trame
	if(mResVerifTrame(RefTrame) != cLdbpcOk)
		return mLDBPCErreur(cLdbpcErrParTrame);

	// Charger le nom du groupe
	Res = ChargerNomGroupe(RefTrame, &pGroupe);

	if(Res != cLdbpcOk)
		return mLDBPCErreur(Res);

	// Creer la entree/sortie < 32bits (DLL)
	Res = Donnees.CreerDonnee(&Ref,pNom,cDLLEntreeSortie,cDLLTypeVal,TailleBit,valeurInit,pGroupe);
	if(Res == cLdbpcOk)
	{
		// Attacher la entree/sortie < 32bits à la trame
		Res = AttacherDonnee(Ref, RefTrame, Position);
		if(Res != cLdbpcOk)
			return	mLDBPCErreur(Res);
	
		if(pRef) *pRef = Ref;
		// Liberation du pointeur
		if(pGroupe)	delete [] pGroupe;
	}

	return Res;
}

//--------------------------------------------------------------------------
// Création d'une entree/sortie > 32bits
//--------------------------------------------------------------------------
tLDBPCStatut tcRessources::CreerEntSor(S32 * pRef, S32 RefTrame, char * pNom
	, U32 TailleBit, U8 * pBufferInit, U32 Position)
{
	tLDBPCStatut Res;
	S32 Ref;
	char * pGroupe = NULL;

	// Verification de l'existance de la trame
	if(mResVerifTrame(RefTrame) != cLdbpcOk)
		return mLDBPCErreur(cLdbpcErrParTrame);

	// Charger le nom du groupe
	Res = ChargerNomGroupe(RefTrame, &pGroupe);
	if(Res != cLdbpcOk)
		return mLDBPCErreur(Res);

	// Creer la entree/sortie > 32bits (DLL)
	Res = Donnees.CreerDonnee(&Ref,pNom,cDLLEntreeSortie,cDLLTypeTab,TailleBit,pBufferInit,pGroupe);
	if(Res == cLdbpcOk)
	{
		// Attacher la entree/sortie < 32bits à la trame
		Res = AttacherDonnee(Ref, RefTrame, Position);
		if(Res != cLdbpcOk)
			return	mLDBPCErreur(Res);
	
		if(pRef) *pRef = Ref;
		// Liberation du pointeur
		if(pGroupe)	delete [] pGroupe;
	}

	return Res;
}

//--------------------------------------------------------------------------
// Fin d'une tempo (pour les trames non initiées)
//--------------------------------------------------------------------------
void tcRessources::FinTempo(S32 RefTrame)
{
	tLdbpcTypeFlux	Type;
	S32			RefEvt;
	char			Mode = 0;

	// Verification de l'existance de la trame
	if(mResVerifTrame(RefTrame) == cLdbpcOk)
	{
		// Lecture du type 
		Type = mTRAME(RefTrame)->LireType();

		// Verification du type 
		if(mFluxNonInitie(Type))
		{
			// Armement d'une tempo
			mTRAME(RefTrame)->ArmerTempo();

			// Lecture du mode
			((tcTrameFni*)mTRAME(RefTrame))->LireMode(&Mode);
			if(Mode == cModeAuto)
			{
				// Lecture du type 
				RefEvt = mTRAME(RefTrame)->LireRefEvt();

				// Action Spontannee
				ActionFni(RefEvt, Type);
			}
		}
		else mLDBPCErreur(cLdbpcErrParFlux);
	}
	else mLDBPCErreur(cLdbpcErrParTrame);
}

//--------------------------------------------------------------------------
// Lire une reference de flux par rapport au canal
//--------------------------------------------------------------------------
tLDBPCStatut tcRessources::LireRefFlux(tChannel RefCan, tLdbpcTypeFlux TypeFlux, S32 * pRefFlux)
{
	tLDBPCStatut Res = cLdbpcErr;

	// Verification de l'existance du canal et de la reference de flux
	if((mResVerifCanal(RefCan) == cLdbpcOk) && pRefFlux)
	{
		// Lire une reference de flux par rapport au type de flux lie au canal
		Res = mCANAL(RefCan)->LireRefFlux(TypeFlux, pRefFlux);
		
		if(Res == cLdbpcOk)
		{
			// Verification de l'existance du flux
			Res = mResVerifFlux(*pRefFlux);
		}
	}
	return Res;
}

//--------------------------------------------------------------------------
// Lire une reference de trame par rapport au flux
//--------------------------------------------------------------------------
tLDBPCStatut tcRessources::LireRefTrame(S32 RefFlux, tAddress Adresse
									, S32 * pRefTrame)
{
	tLDBPCStatut	Res = cLdbpcErr;
	U32			Id;

	// Verification de l'existance du flux et de la reference de trame
	if((mResVerifFlux(RefFlux) == cLdbpcOk) && (pRefTrame))
	{
		// Lire le nombre de trames attachees au flux
		U32 Taille = mFLUX(RefFlux)->GetSize();
		// Parcours de toutes les trames attachees au flux
		for(Id = 0 ; Id < Taille ; Id++)
		{
			// Lire une reference de trame par rapport a un index dans le flux
			Res = mFLUX(RefFlux)->LireRefTrame(Id,pRefTrame);
			// lecture de l'adresse de la trame
			if((Adresse  == mTRAME(*pRefTrame)->LireAdresse())
				&& (Res == cLdbpcOk))
			{
				Res = cLdbpcOk;
				break;
			}
			else Res = cLdbpcErrTrame;
		}

		if(Res == cLdbpcOk)
		{
			// Verification de l'existance du trame
			Res = mResVerifTrame(*pRefTrame);
		}
	}
	return Res;
}

//--------------------------------------------------------------------------
// Lire une reference de trame par rapport au canal
//--------------------------------------------------------------------------
tLDBPCStatut tcRessources::LireRefTrame(tChannel RefCan, tLdbpcTypeFlux TypeFlux
						, tAddress Adresse, S32 * pRefTrame)
{
	tLDBPCStatut	Res;
	S32			Reflux;

	// Lire une reference de flux par rapport au canal
	Res = LireRefFlux(RefCan, TypeFlux, &Reflux);
	if(Res == cLdbpcOk)
	{
		// Lire une reference de trame par rapport flux
		Res = LireRefTrame(Reflux, Adresse, pRefTrame);
	}
	return Res;
}

//--------------------------------------------------------------------------
// Lire une trame 
//--------------------------------------------------------------------------
tLDBPCStatut tcRessources::LireTrame(S32 RefTrame, tMsg * pMsg)
{
	tLDBPCStatut Res = cLdbpcErr;

	// Verification de l'existance de la trame
	if(mResVerifTrame(RefTrame) == cLdbpcOk)
	{
		// Lire une trame
		Res = mTRAME(RefTrame)->Lire(pMsg);
	}
	return Res;
}

//--------------------------------------------------------------------------
// Lire la taille du buffer de la trame courante d'un flux initie
//--------------------------------------------------------------------------
U16 tcRessources::LireTailleTrameCourante(S32 RefFlux)
{
	U16 Taille = 0;

	// Verification de l'existance du flux
	if(mResVerifFlux(RefFlux) == cLdbpcOk)
	{	
		// Recuperation du type du flux
		tLdbpcTypeFlux Type = mFLUX(RefFlux)->LireType();

		// Verification que c'est un flux initie
		if(mFluxInitie(Type))	
		{
			// Lecture du message en cours
			Taille = mFLUX(RefFlux)->LireTailleMsgEnCours();
		}
	}
	return Taille;
}

//--------------------------------------------------------------------------
// Lire la trame courante d'un flux initie
//--------------------------------------------------------------------------
tLDBPCStatut tcRessources::LireTrameCourante(S32 RefFlux
										, tAddress * pAdresse, tMsg ** ppMsg)
{
	tLDBPCStatut Res = cLdbpcErr;

	// Verification de l'existance du flux
	if(mResVerifFlux(RefFlux) == cLdbpcOk)
	{	
		// Recuperation du type du flux
		tLdbpcTypeFlux Type = mFLUX(RefFlux)->LireType();

		// Verification que c'est un flux initie
		if(mFluxInitie(Type))	
		{
			// Lecture du message en cours
			Res = mFLUX(RefFlux)->LireMsgEnCours(ppMsg);
			// Lecture de l'adresse en cours
			*pAdresse = mFLUX(RefFlux)->LireAdrEnCours();
		}
	}
	return Res;
}

//--------------------------------------------------------------------------
// Lire l'etat de controle du canal
//--------------------------------------------------------------------------
tLDBPCStatut tcRessources::LireEtatControle(tChannel RefCan, char * pEtat)
{
	tLDBPCStatut Res = cLdbpcErr;

	// Verification de l'existance du canal
	if(mResVerifCanal(RefCan) == cLdbpcOk)
	{
		// Lire l'etat de controle du canal
		*pEtat = mCANAL(RefCan)->LireEtat();
		Res = cLdbpcOk;
	}
	return Res;
}


//--------------------------------------------------------------------------
// Ecrire une trame
//--------------------------------------------------------------------------
tLDBPCStatut tcRessources::EcrireTrame(S32 RefTrame, tMsg * pMsg)
{
	tLDBPCStatut Res = cLdbpcErr;

	// Verification de l'existance de la trame
	if(mResVerifTrame(RefTrame) == cLdbpcOk)
	{
		// Ecrire une trame
		Res = mTRAME(RefTrame)->Ecrire(pMsg);
	}
	return Res;
}

//--------------------------------------------------------------------------
// Ecrire la trame courante d'un flux
//--------------------------------------------------------------------------
tLDBPCStatut tcRessources::EcrireTrameCourante(S32 RefFlux
											 , tAddress Adresse, tMsg * pMsg)
{
	tLDBPCStatut Res = cLdbpcErr;

	// Verification de l'existance du flux
	if(mResVerifFlux(RefFlux) == cLdbpcOk)
	{
		// Recuperation du type du flux
		tLdbpcTypeFlux Type = mFLUX(RefFlux)->LireType();

		// Verification que c'est un flux initie
		if(mFluxInitie(Type))
		{
			// Ecriture du message en cours
			Res = mFLUX(RefFlux)->EcrireMsgEnCours(pMsg);
			// Ecriture de l'adresse en cours
			mFLUX(RefFlux)->EcrireAdrEnCours(Adresse);
		}
	}

	return Res;
}

//--------------------------------------------------------------------------
// Ecrire l'etat de controle du canal
//--------------------------------------------------------------------------
tLDBPCStatut tcRessources::EcrireEtatControle(tChannel RefCan, char Etat)
{
	tLDBPCStatut Res = cLdbpcErr;

	// Verification de l'existance du canal
	if(mResVerifCanal(RefCan) == cLdbpcOk)
	{
		// Lire l'etat de controle du canal
		mCANAL(RefCan)->EcrireEtat(Etat);
		Res = cLdbpcOk;
	}
	return Res;
}

//--------------------------------------------------------------------------
// Emission d'un Flux Initie vers un canal
//--------------------------------------------------------------------------
void tcRessources::ActionFi(tLdbpcTypeFlux Type, tChannel RefCan
							, tAddress Adresse, tMsg* pMsg)
{
	tLDBPCStatut	Res = cLdbpcErr;
	S32			RefFlux;
	char			Etat = 0;
	tDelay			Duree = 0;
	S32			RefTrame;

	// Verification de l'existance du canal
	if(mResVerifCanal(RefCan) == cLdbpcOk)
	{
		// Lire une reference de flux par rapport au canal
		Res = LireRefFlux(RefCan, Type, &RefFlux);

		if(Res == cLdbpcOk)
		{
			// Lire etat du canal
			LireEtatControle(RefCan, &Etat);
			// Si le canal n'est pas occupe
			if(Etat != cOccupe)
			{
				// GG : 18/03/2002
				// Pour les flux n'ayant pas de fonction callback personalisées
				if(mFLUX(RefFlux)->IsAction() == cFalse)
				{
          if(mCANAL(RefCan)->Send(Type, Adresse, pMsg)) return;

					// Recherche de la reference de trame
					// GG : 07/02/2002
					// Pour savoir si elle existe dans le paramétrage
					Res = LireRefTrame(RefFlux, Adresse, &RefTrame);

					if(Res != cLdbpcOk)	 
					{ 
						// the frame with this addess don't exist !
						// trame comportant cette adresse n'existe pas !
						mLDBPCErreur(Res); return; 
					}
				}

                tDelay Time;
                Timer.LireDate(&Time);
                if(Type == cFluxIP)
                {
                  mCANAL(RefCan)->m_SADAdrTrace.SADAdrFrameTraceTx(Adresse,pMsg->Lng,pMsg->pBuffer,(tU32Bit)(Time/100000UL));
                }
                else
                {
                  mCANAL(RefCan)->m_SADAdrTrace.SADAdrFrameTraceRx(Adresse,pMsg->Lng,pMsg->pBuffer,(tU32Bit)(Time/100000UL));
                }
				// Ecrire la trame courante d'un flux
				Res = 	EcrireTrameCourante(RefFlux, Adresse, pMsg);
				if(Res == cLdbpcOk)
				{
					// Appel de la fonction callback personalisee
					if(!mFLUX(RefFlux)->Action())
					{
						// Emission Standard du message courant 
						// d'un Flux Initie Produit vers un canal
						ActionFiStd(Type, RefCan);
					}
				}
				else Res = mLDBPCErreur(Res);
			}
			else Res = mLDBPCErreur(cLdbpcErrCanal);
		}
		else mLDBPCError(cEC00001);
	}
	else Res = mLDBPCErreur(cLdbpcErrParCanal);

}

//--------------------------------------------------------------------------
// Emission Standard du message courant d'un Flux Initie vers un canal
//--------------------------------------------------------------------------
void tcRessources::ActionFiStd(tLdbpcTypeFlux Type, tChannel RefCan)
{
	tLDBPCStatut	Res = cLdbpcErr;
	S32			RefFlux;
	S32			RefTrame;
	char			Etat = 0;
	tDelay			Duree = 0;
	tAddress		Adresse = 0;

	// Verification de l'existance du canal
	if(mResVerifCanal(RefCan) != cLdbpcOk)
	{ mLDBPCErreur(cLdbpcErrParCanal); return; }

	// Lire une reference de flux par rapport au canal
	Res = LireRefFlux(RefCan, Type, &RefFlux);
	if(Res != cLdbpcOk)	 { mLDBPCErreur(Res); return; }

	// Lire etat du canal
	Res	= LireEtatControle(RefCan, &Etat);
	if(Res != cLdbpcOk)	 { mLDBPCErreur(Res); return; }

	// Si le canal n'est pas occupe
	if(Etat != cOccupe)
	{
		// Rend le canal occupe
		Res = EcrireEtatControle(RefCan, cOccupe);
		if(Res != cLdbpcOk)	 { mLDBPCErreur(Res); return; }

		// Lecture de l'adresse courante de la trame 
		Adresse = mFLUX(RefFlux)->LireAdrEnCours();

		// Lecture de la reference de la trame 
		Res = 	LireRefTrame(RefFlux, Adresse, &RefTrame);
		if(Res != cLdbpcOk)	 { mLDBPCErreur(Res); return; }

		Duree = mTRAME(RefTrame)->LireDuree();
		if(Duree)
		{
			// Demarrer Tempo pour l'emission d'un controle
			mFLUX(RefFlux)->Tempo.EstPeriodique = cFalse;
			mFLUX(RefFlux)->Tempo.Duree = Duree * cLDBTick;
			mFLUX(RefFlux)->Tempo.Param = RefFlux;
			mFLUX(RefFlux)->Tempo.pCallBack = CallBackFiStd;
			Timer.AjouterTempo(&mFLUX(RefFlux)->Tempo);
		}
		else
		{
			CallBackFiStd(RefFlux);
		}
	}
	else mLDBPCErreur(cLdbpcErrCanal);
}

// ------------------------------------------------------------------------
// Fin d'action d'un Flux Initie vers un canal
// ------------------------------------------------------------------------
void tcRessources::FinActionFi(S32 RefFlux)
{
	tLdbpcTypeFlux	Type;
	tMsg *			pMsg = NULL;
	tAddress		Adresse;
	S32			RefTrame;
	tLDBPCStatut	Res = cLdbpcErr;
	tChannel			RefCan;

	// Verification de l'existance du flux
	Res = mResVerifFlux(RefFlux);
	if( Res != cLdbpcOk) { mLDBPCErreur(cLdbpcErrFlux); return; }

	// Lecture de la reference de canal
	RefCan = mFLUX(RefFlux)->LireRefCanal();

	// Verification de l'existance du canal
	Res = mResVerifCanal(RefCan);
	if( Res != cLdbpcOk) { mLDBPCErreur(Res); return; }

	// Rend le canal disponible
	Res = EcrireEtatControle(RefCan, cDisponible);
	if(Res != cLdbpcOk)	 { mLDBPCErreur(Res); return; }

	// Lecture de l'adresse courante le la trame à lire 
	Res = LireTrameCourante(RefFlux, &Adresse, &pMsg);
	if(Res != cLdbpcOk)	 { mLDBPCErreur(Res); return; }

	// Recherche de la reference de trame
	Res = LireRefTrame(RefFlux, Adresse, &RefTrame);
	if(Res != cLdbpcOk)	 { mLDBPCErreur(Res); return; }

	// Recuperation du type du flux
	Type = mFLUX(RefFlux)->LireType();

	if(Type == cFluxIC)	
	{
		// Lecture de la trame
		// Optimisation N°1 GGL : 09/08/2001
//		Res = LireTrame(RefTrame, pMsg);
		Res = mTRAME(RefTrame)->Lire(pMsg);
		if(Res == cLdbpcOk)
		{
			// Emettre la fonction Callback correspondante
			mFLUX(RefFlux)->FinAction();

			// Emettre le message de lecture au LDS
			mTRAME(RefTrame)->EmissionEvt();
		}
		else Res = mLDBPCErreur(Res);
	}
	else if(Type == cFluxIP)	
	{
		// Ecriture de la trame
		Res = EcrireTrame(RefTrame, pMsg);
		if(Res == cLdbpcOk)
		{
			// Emettre la fonction Callback correspondante
			mFLUX(RefFlux)->FinAction();

			// Emettre le message d'ecriture au LDS
			mTRAME(RefTrame)->EmissionEvt();
		}
		else mLDBPCErreur(Res);
	}
	else mLDBPCErreur(cLdbpcErrFlux);
}	

// ------------------------------------------------------------------------
// Preparation d'emission d'un Flux Non Initie Produit vers un canal
// ------------------------------------------------------------------------
void tcRessources::PreparerActionFnip(tChannel RefCan, tAddress Adresse
									  , tMsg* pMsg)
{
	tLDBPCStatut	Res = cLdbpcErr;
	S32			RefFlux;
	S32			RefTrame;
	char			Etat = 0;
	tAddress		adr = Adresse;
	tMsg*			pMesg = pMsg;

	// Verification de l'existance du canal
	if(mResVerifCanal(RefCan) != cLdbpcOk)
	{ mLDBPCErreur(cLdbpcErrParCanal);  return; }

	// Lire une reference de flux par rapport au canal
	Res = LireRefFlux(RefCan, cFluxNIP, &RefFlux);
	if(Res != cLdbpcOk)
		{ mLDBPCErreur(cLdbpcErrFlux);  return; }

	if(mFLUX(RefFlux)->LireType() != cFluxNIP)
	if(Res != cLdbpcOk)
		{ mLDBPCErreur(cLdbpcErrFlux);  return; }
	
	// Recherche de la reference de trame
	Res = LireRefTrame(RefFlux, Adresse, &RefTrame);
	if(Res != cLdbpcOk)
		{ mLDBPCErreur(cLdbpcErrTrame);  return; }

	// Appel de la fonction callback personalisee
	mFLUX(RefFlux)->Action(&adr, &pMesg);

	// Preparer un message
	mTRAME(RefTrame)->Preparer(pMesg);
}

// ------------------------------------------------------------------------
// Emission d'un Flux Non Initie vers La couche DAT
// ------------------------------------------------------------------------
void tcRessources::ActionFni(S32 evt, tLdbpcTypeFlux Type)
{
	S32	RefFlux;
	tChannel	RefCan;
	int		Id;

	// Recherche de la reference de la trame liee à la reference de l'evt
	for(Id = 0 ;Id < mTotalTrame; Id++ )
	{
		if((mTRAME(Id)->LireRefEvt() == evt) 
			&& (mTRAME(Id)->LireType() == Type)) break;
	}

	// Verification de la reference
	if(Id < mTotalTrame && (mResVerifTrame(Id) == cLdbpcOk))
	{
		// Lecture de la reference de flux associee a la trame
		RefFlux = mTRAME(Id)->LireRefFlux();

		// Verification de la reference
		if(RefFlux != -1)
		{
			if((mResVerifFlux(RefFlux) == cLdbpcOk) 
				&& (mFLUX(RefFlux)->LireType() == Type))
			{
				// Lecture de la reference du canal	
				RefCan = mFLUX(RefFlux)->LireRefCanal();

				// Emission standard
				ActionFniStd(RefCan, Id, Type);
			}
			else	mLDBPCErreur(cLdbpcErrFlux);
		}
		else	ActionFniStd(-1, Id, Type);
	}
	else	mLDBPCErreur(cLdbpcErrTrame);
}

// ------------------------------------------------------------------------
// Emission standard d'un Flux Non Initie vers La couche DAT
// ------------------------------------------------------------------------
void tcRessources::ActionFniStd(tChannel RefCan, S32 RefTrame
												, tLdbpcTypeFlux Type)
{
	// Verification de la reference
	if(((RefCan == -1) || (mResVerifCanal(RefCan) == cLdbpcOk)) 
		&& (mResVerifTrame(RefTrame) == cLdbpcOk))
	{
		if(Type == cFluxNIP)
		{
			// Production des donnees
			if(mTRAME(RefTrame)->Produire())
			{
				if((RefCan == -1) || (mCANAL(RefCan)->LireAutorisation()))
				{
					// Emission Spontanee
					mTRAME(RefTrame)->EmissionSpontanee();
				}
			}
		}
		else if(Type == cFluxNIC)
		{
			if((RefCan == -1) || (mCANAL(RefCan)->LireAutorisation()))
			{
				// Reception Spontanee
				mTRAME(RefTrame)->ReceptionSpontanee();
			}
		}
		else	mLDBPCErreur(cLdbpcErrFlux);
	}
	else	mLDBPCErreur(cLdbpcErrCanal);
}

// ------------------------------------------------------------------------
// Autoriser les Flux Non Initie vers La couche DAT
// ------------------------------------------------------------------------
void tcRessources::Autoriser(tChannel RefCan, BOOL bCallbackAutorise)
{
	// Verification de la reference
	if(mResVerifCanal(RefCan) == cLdbpcOk)
	{
		// Verification de l'existance d'une autorisation personalisee
		if(!mCANAL(RefCan)->Autoriser(bCallbackAutorise))
		{
			mCANAL(RefCan)->EcrireAutorisation(bCallbackAutorise);
		}
	}
	else	mLDBPCErreur(cLdbpcErrCanal);
}

// ------------------------------------------------------------------------
// Lire la reference de controle par rapport au canal et au controle 
// ------------------------------------------------------------------------
tLDBPCStatut tcRessources::LireRefCtrl(S32 * pRefCtrl,tChannel RefCan
									   , tCtrl Ctrl)
{
	tLDBPCStatut	Res	= cLdbpcErr;
	tcCtrl *		pCtrl	= NULL;
	int				Id;

	// Verification de la reference du canal
	if(mResVerifCanal(RefCan) == cLdbpcOk)
	{
		// Recherche de la reference de controle parmis dans le tableau
		for(Id = 0 ;Id < m_TabCtrl.GetSize(); Id++ )
		{
			pCtrl = mCTRL(Id);
			// Si le canal et le control sont les memes -> la reference est = Id
			if((pCtrl->LireRefCanal() == RefCan) 
				&& (pCtrl->LireCtrl() == Ctrl)
				&& (pCtrl->CtrlSortie()))
			{
				*pRefCtrl = Id;
				Res	 = cLdbpcOk;
				break;
			}
		}
	}
	return Res;
}

// ------------------------------------------------------------------------
// Emettre un controle sur un canal
// ------------------------------------------------------------------------
void tcRessources::Controler(tChannel RefCan,tCtrl Ctrl)
{
	tDelay	Duree = 0;
	S32	RefCtrl = 0;

	// Verification de la reference de controle et de canal
	if(LireRefCtrl(&RefCtrl, RefCan, Ctrl))
	{
		// Verification de l'existance d'un controle personalise
		if(!mCANAL(RefCan)->Controler(Ctrl))
		{
			ControleStd(RefCan, Ctrl);
		}
	}
	else	mLDBPCErreur(cLdbpcErrCtrl);

}

// ------------------------------------------------------------------------
// Emettre un controle standard sur un canal
// ------------------------------------------------------------------------
void tcRessources::ControleStd(tChannel RefCan,tCtrl Ctrl)
{
	char	Etat		= 0;
	tDelay	Duree		= 0;
	S32	RefCtrl		= 0;

	// Verification de la reference de controle et de canal
	if(LireRefCtrl(&RefCtrl, RefCan, Ctrl))
	{
		// Lire etat du canal
		LireEtatControle(RefCan, &Etat);
		// Si le canal n'est pas occupe
		if(Etat != cOccupe)
		{
			// Ecrire etat du canal
			EcrireEtatControle(RefCan, cOccupe);

			// Ecrire la reference du ctrl en cours dans le canal
			mCANAL(RefCan)->EcrireCtrlEnCours(RefCtrl);

			// lire la duree du ctrl
			Duree = mCTRL(RefCtrl)->LireDuree();
			
			// GG: 29/11/2000 : modification :
			// Si la duree d'un controle = 0 appeler la callback immediatement
			if(Duree)
			{
				// Demarrer Tempo pour l'emission d'un controle
				mCTRL(RefCtrl)->Tempo.EstPeriodique = cFalse;
				mCTRL(RefCtrl)->Tempo.Duree = Duree * cLDBTick;
				mCTRL(RefCtrl)->Tempo.Param = RefCtrl;
				mCTRL(RefCtrl)->Tempo.pCallBack = CallBackCtrlSor;
				Timer.AjouterTempo(&mCTRL(RefCtrl)->Tempo);
			}
			else
			{
				FinControle(RefCtrl);				
			}
		}
	}
	else	mLDBPCErreur(cLdbpcErrCtrl);

}

// ------------------------------------------------------------------------
// Emission du controle vers le LDS
// ------------------------------------------------------------------------
void tcRessources::FinControle(S32 RefCtrl)
{
	tChannel	RefCan;
	S32	RefEvt;
	tStatus Statut = cLDBCorrect;
	tCtrl	Ctrl;

	// Verification de la reference du ctrl
	if(mResVerifCtrl(RefCtrl) == cLdbpcOk)
	{
		// Lecture du type
		if(mCTRL(RefCtrl)->CtrlSortie())
		{
			// Lecture de la reference du canal
			RefCan = mCTRL(RefCtrl)->LireRefCanal();

			// Verification de la reference du canal
			if(mResVerifCanal(RefCan) == cLdbpcOk)
			{
				// Ecrire etat du canal
				EcrireEtatControle(RefCan, cDisponible);

				// Lecture du controle
				Ctrl  = mCTRL(RefCtrl)->LireCtrl();

				// Lecture de la reference d'evenement
				RefEvt = mCTRL(RefCtrl)->LireRefEvt();

				// Emission du controle (DLL)
				Donnees.EmettreEvtSor(RefEvt);

				// Appel de la callback de fin de Controle
				mCANAL(RefCan)->FinControle(Ctrl, Statut);
			}
			else	mLDBPCErreur(cLdbpcErrCtrl);
		}
		else	mLDBPCErreur(cLdbpcErrCtrl);
	}
	else	mLDBPCErreur(cLdbpcErrCtrl);
}

// ------------------------------------------------------------------------
// Recherche la reference du controle à partir de la reference d'evenement
// ------------------------------------------------------------------------
tLDBPCStatut tcRessources::RechercherCtrl(S32 RefEvt, S32 * RefCtrl)
{
	tLDBPCStatut Res = cLdbpcErrCtrl;
	S32 Id;

	// Parcours du tableau de Controle
	for(Id = 0 ;Id < m_TabCtrl.GetSize(); Id++ )
	{
		if(mCTRL(Id)->LireRefEvt() == RefEvt)
		{
			if(RefCtrl)
			{
				*RefCtrl = Id;
				Res = cLdbpcOk;
				break;
			}	
		}
	}
	return Res;
}

// ------------------------------------------------------------------------
// Emission du controle vers La couche DAT
// ------------------------------------------------------------------------
void tcRessources::CBControler(S32 RefEvt)
{
	tChannel	RefCan;
	tCtrl	Ctrl;
	S32  RefCtrl;

	// Verification de la reference du ctrl
	if(RechercherCtrl(RefEvt, &RefCtrl) == cLdbpcOk)
	{
		// Lecture du type
		if(mCTRL(RefCtrl)->CtrlEntree())
		{
			// Lecture de la reference du canal
			RefCan = mCTRL(RefCtrl)->LireRefCanal();

			// Verification de la reference du canal
			if(mResVerifCanal(RefCan) == cLdbpcOk)
			{
				// Lecture du controle
				Ctrl  = mCTRL(RefCtrl)->LireCtrl();

				// Appel de la callback de fin de Controle
				mCANAL(RefCan)->CBControle(Ctrl);
			}
			else	mLDBPCErreur(cLdbpcErrCtrl);
		}
		else	mLDBPCErreur(cLdbpcErrCtrl);
	}
	else	mLDBPCErreur(cLdbpcErrCtrl);
}

// ------------------------------------------------------------------------
// Detruire les trames, flux et canaux
// ------------------------------------------------------------------------
void tcRessources::Destruction()
{
	U32		Id;
	tcCanal *	pCanal	= NULL;
	tcFlux  *	pFlux	= NULL;
	tcTrame *	pTrame	= NULL;
	tcCtrl *	pCtrl	= NULL;

	// Detruire le tableau de canaux
	for(Id = 0 ;Id < (U32)m_TabCanal.GetSize(); Id++ )
	{
		pCanal = mCANAL(Id);
		if(pCanal)
			delete pCanal;
	}

	// Detruire le tableau de flux
	for(Id = 0 ;Id < (U32)m_TabFlux.GetSize(); Id++ )
	{
		pFlux = mFLUX(Id);
		if(pFlux)
			delete pFlux;
	}

	// Detruire le tableau de trame
	for(Id = 0 ;Id < (U32)mTotalTrame; Id++ )
	{
		pTrame = mTRAME(Id);
		if(pTrame)
			delete pTrame;
	}

	// Detruire le tableau de Controle
	for(Id = 0 ;Id < (U32)m_TabCtrl.GetSize(); Id++ )
	{
		pCtrl = mCTRL(Id);
		if(pCtrl)
			delete pCtrl;
	}
}

//--------------------------------------------------------------------------
// Ecrire la duree d'une trame
//--------------------------------------------------------------------------
tLDBPCStatut tcRessources::EcrireDureeTrame(tAddress Adresse,S32 RefFlux, tDelay Duree)
{
	tLDBPCStatut Res = cLdbpcErr;
	S32 RefTrame;

	// Verification de l'existance du flux
	if(mResVerifFlux(RefFlux) == cLdbpcOk)
	{
		// Lire une reference de trame par rapport au flux
		LireRefTrame(RefFlux, Adresse, &RefTrame);
		mTRAME(RefTrame)->EcrireDuree(Duree);
		Res = cLdbpcOk;
	}
	else
		Res = mLDBPCErreur(cLdbpcErrTrame);

	return Res;
}

// Lecture du Mode de la trame
BOOL tcRessources::LireModeTrame(S32 RefTrame, char * Mode)
{
	tLDBPCStatut Res = cLdbpcErr;
	if((mResVerifTrame(RefTrame) == cLdbpcOk) && (Mode))
	{
		// Lecture du mode
		((tcTrameFni*)mTRAME(RefTrame))->LireMode(Mode);
		Res = cLdbpcOk;
	}
	else Res = mLDBPCErreur(cLdbpcErrTrame);

	return((BOOL)(Res == cLdbpcOk));
}

void tcRessources::Formater(tChannel RefCan,U8 Format)
{
	// Verification de l'existence du canal
	if(!mResVerifCanal(RefCan)) 
		mLDBPCErreur(cLdbpcErrParCanal);

	// Mise à Jour du Format
	mCANAL(RefCan)->SetFormat(Format);
}

U8 tcRessources::GetFormat(S32 RefTrame)
{
	tChannel RefCan;
	S32 RefFlux;
	// Verification de l'existence du canal
	if(!mResVerifTrame(RefTrame))
	{
		mLDBPCErreur(cLdbpcErrParTrame);
		return 0;
	}
	RefFlux = mTRAME(RefTrame)->LireRefFlux();
	// Verification de l'existence du flux
	if(!mResVerifFlux(RefFlux))
	{
		mLDBPCErreur(cLdbpcErrParFlux);
		return 0;
	}

	RefCan = mFLUX(RefFlux)->LireRefCanal();
	// Verification de l'existence du canal
	if(!mResVerifCanal(RefCan)) 
	{
		mLDBPCErreur(cLdbpcErrParCanal);
		return 0;
	}

	// Lecture du Format du canal
	return 	mCANAL(RefCan)->GetFormat();
}

char * tcRessources::GetChannelName(S32 RefCan)
{
	return(mCANAL(RefCan)->GetName());
}

// Creation des données internes
void tcRessources::CreationDonneesInternes(void)
{
  S32 Ref;

	Donnees.CreerDonnee(&m_RefUCEenVeille,"ECUSleeping",cDLLSortie,cDLLTypeVal,1,1,"Standard");
	Donnees.CreerDonnee(&Ref,"IsRCarMode",cDLLSortie,cDLLTypeVal,1,(U32)0,"Standard");
	Donnees.CreerDonnee(&Ref,"IsECarMode",cDLLSortie,cDLLTypeVal,1,1,"Standard");

#ifdef LDBPC_IMAGE_COMPARE
   	// Chargement des donnees
	ImgCmp.Create();
#endif LDBPC_IMAGE_COMPARE

}

// Mettre en veille
void tcRessources::EntrerVeille(void) 
{
	Donnees.EcrireSortie( m_RefUCEenVeille, (U32)1);
}

// Arreter la Veille
void tcRessources::SortirVeille(void)
{
	Donnees.EcrireSortie( m_RefUCEenVeille, (U32)0);
}

// Demande de le modification forcée de la trame 
void tcRessources::EcrireDmdeMoficationTrame(S32 RefTrame, BOOL flag)
{
	if(mTRAME(RefTrame) != NULL)
	{
		mTRAME(RefTrame)->EcrireDmdeMofication(flag);
	}
}

// Lecture de l'activation de la modification forcée de la trame 
BOOL tcRessources::LireDmdeMoficationTrame(S32 RefTrame)
{
	if(mTRAME(RefTrame) != NULL)
	{
		return(mTRAME(RefTrame)->LireDmdeMofication());
	}
	return(cFalse);
}

// ------------------------------------------------------------------------
// Chargement du Nom de groupe
// !!! ATTENTION ALLOCATION SANS DESALLOCATION !!!
// ------------------------------------------------------------------------
tLDBPCStatut tcRessources::ChargerNomGroupe(S32 RefTrame
									, char ** pNomGroupe,char * pGroupe)
{
	tLDBPCStatut	Res = cLdbpcErr;
	char *			pNomCan = pGroupe;
	char *			pNomTrame = NULL;
	S32			RefFlux;
	tChannel			RefCan;

	// Verification de l'existance de la trame
	Res = mResVerifTrame(RefTrame);
	if(Res == cLdbpcOk)
	{
		// Lecture de la reference de flux
		RefFlux = mTRAME(RefTrame)->LireRefFlux();

		if(RefFlux != -1)
			// Verification de l'existance du flux
			Res = mResVerifFlux(RefFlux);
		else if(!pGroupe)
			Res = cLdbpcErrGroupe;

		if(Res == cLdbpcOk)
		{
			if(RefFlux != -1)
			{
				// Lecture de la reference de canal
				RefCan = mFLUX(RefFlux)->LireRefCanal();

				// Verification de l'existance du canal
				Res = mResVerifCanal(RefCan);
			}

			if(Res == cLdbpcOk)
			{
				if(RefFlux != -1)
						// Lire le nom du canal
						mCANAL(RefCan)->LireNom(&pNomCan);
				
				// Lire le nom de la trame
				mTRAME(RefTrame)->LireNom(&pNomTrame);

                // Construction du nom du groupe
	            *pNomGroupe = NewStrCat(pNomCan, cBACK_SLACH, pNomTrame);
                if(*pNomGroupe == NULL)
	            {
	                Res = mLDBPCErreur(cLdbpcErrAllocMem);
                }
			}
			else	mLDBPCErreur(cLdbpcErrCanal);
		}
		else	mLDBPCErreur(cLdbpcErrFlux);
	}
	else	mLDBPCErreur(cLdbpcErrTrame);

	return Res;
}

void tcRessources::SetXCANCurrentConfig(char * ConfigName)
{ 
    XCAN_SetConfiguration(ConfigName);
}
