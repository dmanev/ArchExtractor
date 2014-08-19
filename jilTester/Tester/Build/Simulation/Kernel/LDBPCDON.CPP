//******************************************************************************
// COMPOSANT : LDBPCDon
// FONCTION : Gestion des donnees (creation, acces, ecriture, lecture)
//
// Ce logiciel est la propriete de JCI :
// ---------------------------------------
// Il ne peut être reproduit ni communique en totalite ou partie sans
// son autorisation ecrite.
//
// ------------------------------------------------------------------------
// Definition des fonctions exportees par le composant LDBPCDon :
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
//		Christophe NAUDEAU  CN
//		
// ------------------------------------------------------------------------
// Historique du fichier LDBPCDon.c:
// -------------------------------------
// (initiales, date, modification)
//
// v1.0	:	GG		: 14/04/2000	: Creation
// v1.1 :	MG		: 13/03/2002	: Prise en compte des couches CAN
// v1.1 :	GG & CN : 13/03/2002	: Correction suite a l'évolution de DLLCOM
//
//***************************************************************************
#define LDBPCDon "LDBPCDon"
//--------------------------------------------------------------------------
//---------------- Inclusion de fichiers (système et librairies -----------
//--------------------------------------------------------------------------

#include "Ldbpc.h"			// Defini les types et constantes de bases
#include "LDBPCDon.h"		// Definit l'interface du Module Donnees

//--------------------------------------------------------------------------
//------- Inclusion des definitions des autres composants utiles ---------
//--------------------------------------------------------------------------
#include "LDBPCTim.h"	// Definit l'interface du Module Timer

//--------------------------------------------------------------------------
//------- Declaration des constantes locales à ce composant --------------
//--------------------------------------------------------------------------
// #define cNomConstante ValeurDeLaConstante
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

// Definition du module Donnees
tcDonnees Donnees;

//--------------------------------------------------------------------------
//------- Donnees Constantes locales à ce composant ----------------------
//--------------------------------------------------------------------------
// static const tType NomVariable;
//--------------------------------------------------------------------------
//------- Variables exportees par ce composant ---------------------------
//--------------------------------------------------------------------------
// extern tType ComNomVariable; (Com: 3 lettres identifiant ce composant)
// extern tType* pComNomVariable;

//--------------------------------------------------------------------------
//------- Donnees Constantes exportees par ce composant ------------------
//--------------------------------------------------------------------------
// const tType ComNomVariable; (Com: 3 lettres identifiant ce composant)

//--------------------------------------------------------------------------
//------------------------- Fonctions exportees ----------------------------
//--------------------------------------------------------------------------
void CallBackRef(tpParam Callback, tpParam ParamCallback)
{
  ((tpFunct1)Callback)(*((S32*)ParamCallback));
}

//--------------------------------------------------------------------------
//---------------------------- Fonctions locales ---------------------------
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
//--------------- Implementation de la classe tcDonnees -------------------
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
//	Construction du Module Donnees
//--------------------------------------------------------------------------
tcDonnees::tcDonnees()
{
	// Initialistaiton des fonctions CallBack
	m_pCBEvtEntrees = NULL;
	m_pTabUpdateData = NULL;	
	m_NbMaxData = 0;
}

//--------------------------------------------------------------------------
//	Destruction du Module Donnees
//--------------------------------------------------------------------------
tcDonnees::~tcDonnees()
{
	if(m_pTabUpdateData != NULL)
	{
		delete [] m_pTabUpdateData;	
	}
}

//--------------------------------------------------------------------------
// Creation d'une donnee
//--------------------------------------------------------------------------
tLDBPCStatut tcDonnees::CreerDonnee(tsDonnee * pDonnee)
{
	tLDBPCStatut Res = cLdbpcErr;
	tDLLDonnee Data;
	U8* pBufferInit = NULL;
	tcEvt * pEvt = NULL;
	S32 Ref;
		
	// Vérification de certains paramettres
	if(((pDonnee->TypeVal == cDLLTypeVal) && ((pDonnee->TailleBit == 0) || (pDonnee->TailleBit > 32))) ||
		((pDonnee->TypeVal == cDLLTypeTab) &&( pDonnee->TailleBit == 0)))
		return mLDBPCErreur(cLdbpcErrParTailleDonnee);

	// Verification du nom
	if(pDonnee->pNom == NULL)
		return mLDBPCErreur(cLdbpcErrParNom);	

	// Initialisation Automatique du buffer d'initialisation
	if((pDonnee->TypeVal == cDLLTypeTab) && (pDonnee->ValInit.pBuffer == NULL))
	{
		pBufferInit = (U8 *)new U8[mTailleOctet(pDonnee->TailleBit)];
		if(pBufferInit != NULL)
		{
			memset(pBufferInit,0,mTailleOctet(pDonnee->TailleBit));
			pDonnee->ValInit.pBuffer = pBufferInit;
		}
		else
		{
			mLDBPCErreur(cLdbpcErrAllocMem);
		}
	}

	// Parametres de la donnee
	Data.Type		= pDonnee->Type;
	Data.TypeVal	= pDonnee->TypeVal;
	Data.pNom		= pDonnee->pNom;
	Data.ValInit	= pDonnee->ValInit;
	Data.TailleBit	= pDonnee->TailleBit;
	Data.pGroupe	= pDonnee->pGroupe;

	// Creation de la donnee
	if(DLLCreerDonnee(&Ref, &Data) != cDLLOK)
	{
		Res = mLDBPCErreur(cLdbpcErrDll);
	}
	else  if(pDonnee->Type != cDLLSortie)
	{
		// Creation d'un evenement
		pEvt = (tcEvt *) new tcEvt(pDonnee->Type, pDonnee->pCallBackVoid
														, pDonnee->pParamCallBack);
		if(pEvt)
		{
			// Ajout dans la liste d'evenements en entree
			m_TabEvt.SetAtGrow(Ref, pEvt);
			Res = cLdbpcOk;
		}
		else
			Res = mLDBPCErreur(cLdbpcErrAllocMem);
	}
	else
	{
		Res = cLdbpcOk;
	}

	// Mise a jour de la reference
	if(pDonnee->pRef)
	{
		*(pDonnee->pRef) = Ref;
	}

	// Desallocation du buffer
	if(pBufferInit != NULL)
	{
		delete [] pBufferInit;
	}

	return(Res);
}
tLDBPCStatut tcDonnees::CreerDonnee(S32 * pRef, char * pNom, tDLLType Type
	, tDLLTypeVal TypeVal, U32 TailleBit, U32 ValeurInit, char * pGroupe
	, tpVoid pVoid, tpParam pParam)
{
	tsDonnee Donnee;

	Donnee.pRef				= pRef;
	Donnee.pNom				= pNom;
	Donnee.Type				= Type;
	Donnee.TypeVal			= TypeVal;
	Donnee.TailleBit		= TailleBit;
	Donnee.ValInit.ULong	= ValeurInit;
	Donnee.pGroupe			= pGroupe;
	Donnee.pCallBackVoid	= pVoid;
	Donnee.pParamCallBack   = pParam;

	return CreerDonnee(&Donnee);
}

tLDBPCStatut tcDonnees::CreerDonnee(S32 * pRef, char * pNom, tDLLType Type
	, tDLLTypeVal TypeVal, U32 TailleBit, U8 * pBufferInit, char * pGroupe
	, tpVoid pVoid, tpParam pParam)
{
	tsDonnee Donnee;

	Donnee.pRef				= pRef;
	Donnee.pNom				= pNom;
	Donnee.Type				= Type;
	Donnee.TypeVal			= TypeVal;
	Donnee.TailleBit		= TailleBit;
	Donnee.ValInit.pBuffer	= pBufferInit;
	Donnee.pGroupe			= pGroupe;
	Donnee.pCallBackVoid	= pVoid;
	Donnee.pParamCallBack   = pParam;

	return(CreerDonnee(&Donnee));
}

//--------------------------------------------------------------------------
// Création d'un evenement pour toutes les entrees
//--------------------------------------------------------------------------
tLDBPCStatut tcDonnees::CreerEvtEntrees(tpFunct1 pCallBackEvt)
{
	tLDBPCStatut Res = cLdbpcErr;

	if(pCallBackEvt)
	{
		// Mise à jour de la fonction callback
		m_pCBEvtEntrees = pCallBackEvt;
	}
	else	Res = mLDBPCErreur(cLdbpcErrParPointNul);
	
	return(Res);
}


//--------------------------------------------------------------------------
// Lire les evenements en entree
//--------------------------------------------------------------------------
tLDBPCStatut tcDonnees::LireEvtEntrees()
{
	tLDBPCStatut Res = cLdbpcOk;
	tDLLTabRefDonnee Tab;
    S32 Id;

    DLLLireNombreDeDonnees((S32 *)&(Tab.NbRef));
	if(Tab.NbRef > (S32)m_NbMaxData)
	{
		m_NbMaxData = Tab.NbRef;
		if(m_pTabUpdateData != NULL)
		{
			delete [] m_pTabUpdateData;	
		}
		m_pTabUpdateData = new S32[m_NbMaxData];	
	}
	Tab.pTabRef = m_pTabUpdateData;

	// Lire la liste des evenements entrants
	if(DLLLireListeDonneesModifiees(&Tab) == cDLLOK)
	{
		// Parcours des evenements
		for(Id = 0 ; Id < Tab.NbRef ; Id++)
		{
			// Signaler l'evenement
			EmettreEvtEnt(Tab.pTabRef[Id]);
		}
	}
	else Res = mLDBPCErreur(cLdbpcErrEvt);
	return(Res);
}

//--------------------------------------------------------------------------
// Emettre d'un evenement en entree
//--------------------------------------------------------------------------
tLDBPCStatut tcDonnees::EmettreEvtEnt(S32 Ref)
{
	BOOL	bRes = cFalse;
	tLDBPCStatut Res = cLdbpcErr;
	
	// Verification de l'existance de la reference
	if(Ref >= m_TabEvt.GetSize())
    {
	    return(Res);
    }
	mLDBPCAssert(Ref < m_TabEvt.GetSize());

	// Verification de l'evt
	mLDBPCAssert(m_TabEvt.GetAt(Ref) != NULL);
	mLDBPCAssert(m_TabEvt.GetAt(Ref)->LireType() != cDLLSortie);

	m_TabEvt.GetAt(Ref)->SignalerEvt(Ref);

	if(m_pCBEvtEntrees != NULL)
	{
		// Signaler l'evenement en general
		m_pCBEvtEntrees(Ref);
	}

	return(Res);
}
//--------------------------------------------------------------------------
// Emettre d'un evenement en sortie
//--------------------------------------------------------------------------
tLDBPCStatut tcDonnees::EmettreEvtSor(S32 Ref)
{
	tLDBPCStatut Res = cLdbpcErr;

	// Signaler l'evenement
	if(DLLSignalerEvt(Ref, Timer.m_Date) == cDLLOK)
	{
		Res = cLdbpcOk;
	}
	else
	{
		Res = mLDBPCErreur(cLdbpcErrEvt);
	}
	return Res;
}


//--------------------------------------------------------------------------
// Lire une entree/sortie < 32bits
//--------------------------------------------------------------------------
tLDBPCStatut tcDonnees::Lire(S32 Ref, U32 * pValeur
								   , U32 * pTaille, tDelay * pDate)
{
	tLDBPCStatut Res = cLdbpcErr;
	tDLLEchantillon Ech;
	tDLLDonnee Data;

	// Lecture des informations sur la donnee
	if(DLLLireInfoDonnee(Ref, &Data) == cDLLOK)
	{
		// Verification que la valeur de la donnee est une valeur < 32 bit
		if(Data.TypeVal == cDLLTypeVal)
		{
			// Vérification de certains paramettres
			if(pValeur != NULL)
			{
				// Lecture de la valeur de la donnee
				if(DLLLireDonnee(Ref, &Ech) == cDLLOK)
				{
					*pValeur = Ech.Valeur.ULong;
					if(pTaille != NULL)
					{
						// Affectation de la taille de la donnee
						*pTaille = Data.TailleBit;
					}

					if(pDate != NULL)
					{
						// Affectation de la date de derniere modification de la donnee
						*pDate = Ech.Date;
					}
					Res = cLdbpcOk;
				}
				else	Res = mLDBPCErreur(cLdbpcErrDll);
			}
			else	Res = mLDBPCErreur(cLdbpcErrParPointNul);
		}
		else	Res = mLDBPCErreur(cLdbpcErrParRef);
	}
	else	Res = mLDBPCErreur(cLdbpcErrDll);

	return Res;
}

//--------------------------------------------------------------------------
// Lire une entree/sortie > 32bits
//--------------------------------------------------------------------------
tLDBPCStatut tcDonnees::Lire(S32 Ref, U8 * pBuffer,
	U32 * pTaille, tDelay * pDate)
{
	tLDBPCStatut Res = cLdbpcErr;
	tDLLEchantillon Ech;
	tDLLDonnee Data;

	// Lecture des informations sur la donnee
	if(DLLLireInfoDonnee(Ref, &Data) == cDLLOK)
	{
		// Verification que la valeur de la donnee est une valeur < 32 bit
		if(Data.TypeVal == cDLLTypeTab)
		{
			// Vérification de certains paramettres
			if(pBuffer != NULL)
			{
				// Lecture de la valeur de la donnee
				if(DLLLireDonnee(Ref, &Ech) == cDLLOK)
				{
					memcpy(pBuffer, Ech.Valeur.pBuffer, mTailleOctet(Data.TailleBit));

					// Lecture de la taille de la donnee
					if(pTaille != NULL)
					{
						*pTaille = Data.TailleBit;
					}

					// Lecture de la date de la donnee
					if(pDate != NULL)
					{
						*pDate = Ech.Date;
					}
					
					Res = cLdbpcOk;
				}
				else	Res = mLDBPCErreur(cLdbpcErrDll);
			}
			else	Res = mLDBPCErreur(cLdbpcErrParPointNul);
		}
		else	Res = mLDBPCErreur(cLdbpcErrParRef);
	}
	else	Res = mLDBPCErreur(cLdbpcErrDll);

	return Res;
}

//--------------------------------------------------------------------------
// Ecrire une valeur (sortie) < 32bits
//--------------------------------------------------------------------------
tLDBPCStatut tcDonnees::EcrireSortie(S32 Ref, U32 Valeur)
{
	tLDBPCStatut Res = cLdbpcErr;
	tDLLEchantillon Ech;
	tDLLDonnee Data;

	// Lecture des informations sur la donnee
	if(DLLLireInfoDonnee(Ref, &Data) == cDLLOK)
	{
		// Verification que la donnee est une sortie
		// Verification que la valeur de la donnee est une valeur < 32 bit
		if(((Data.Type == cDLLSortie) || (Data.Type == cDLLEntreeSortie)) 
			&& (Data.TypeVal == cDLLTypeVal)) 
		{
			Ech.Valeur.ULong = Valeur;

			// Lire la date courante
			Ech.Date = Timer.m_Date;

			// Ecriture de la valeur de la donnee
			if(DLLEcrireDonnee(Ref, &Ech) == cDLLOK)
			{
				Res = cLdbpcOk;
			}
			else
			{
				Res = mLDBPCErreur(cLdbpcErrDll);
			}
	
			// GG & CN : 13/03/2002
			if(Data.Type == cDLLEntreeSortie)
			{
				// Verification de l'evt
				mLDBPCAssert(m_TabEvt.GetAt(Ref) != NULL);

				// Signaler l'evenement
			    m_TabEvt.GetAt(Ref)->SignalerEvt(Ref);
			}
		}
		else	Res = mLDBPCErreur(cLdbpcErrParRef);

	}
	else	Res = mLDBPCErreur(cLdbpcErrDll);

	return Res;
}

//--------------------------------------------------------------------------
// Ecrire une valeur (sortie) > 32bits
//--------------------------------------------------------------------------
tLDBPCStatut tcDonnees::EcrireSortie(S32 Ref, U8 * pBuffer)
{
	tLDBPCStatut Res = cLdbpcErr;
	tDLLEchantillon Ech;
	tDLLDonnee Data;

	// Lecture des informations sur la donnee
	if(DLLLireInfoDonnee(Ref, &Data) == cDLLOK)
	{
		// Verification que la donnee est une sortie
		// Verification que la valeur de la donnee est une valeur < 32 bit
		if(((Data.Type == cDLLSortie) || (Data.Type == cDLLEntreeSortie)) 
			&& (Data.TypeVal == cDLLTypeTab)) 
		{
			Ech.Valeur.pBuffer = pBuffer;

			// Lire la date courante
			Ech.Date = Timer.m_Date;

			// Ecriture de la valeur de la donnee
			if(DLLEcrireDonnee(Ref, &Ech) == cDLLOK)
			{
				Res = cLdbpcOk;
			}
			else
			{
				Res = mLDBPCErreur(cLdbpcErrDll);
			}

				// GG & CN : 13/03/2002
			if(Data.Type == cDLLEntreeSortie)
			{
				// Verification de l'evt
				mLDBPCAssert(m_TabEvt.GetAt(Ref) != NULL);

				// Signaler l'evenement
			    m_TabEvt.GetAt(Ref)->SignalerEvt(Ref);
			}
		}
		else
			Res = mLDBPCErreur(cLdbpcErrParRef);
	}
	else
		Res = mLDBPCErreur(cLdbpcErrDll);

	return Res;
}

//--------------------------------------------------------------------------
// Lire la taille d'une donnee
//--------------------------------------------------------------------------
U32 tcDonnees::LireTailleDonnee(S32 Ref)
{
	U32 Res = 0;
	tDLLDonnee Data;

	// Lecture des informations sur la donnee
	if(DLLLireInfoDonnee(Ref, &Data) != cDLLOK)
	{
		mLDBPCErreur(cLdbpcErrDll);
	}
	else 
	{
		Res = Data.TailleBit;
	}

	return Res;
}

//--------------------------------------------------------------------------
// Retourne cTrue si la donnee de reference Ref est de type Tableau
//--------------------------------------------------------------------------
BOOL tcDonnees::SortieTypeBuffer(S32 Ref)
{
	BOOL Res = cFalse;
	tDLLDonnee Data;

	// Lecture des informations sur la donnee
	if(DLLLireInfoDonnee(Ref, &Data) != cDLLOK)
	{
		mLDBPCErreur(cLdbpcErrDll);
	}
	else 
	{
		Res = (BOOL)(Data.TypeVal == cDLLTypeTab);
	}

	return Res;
}

//--------------------------------------------------------------------------
// Intialisaion de la callback de la donnée
//--------------------------------------------------------------------------
void tcDonnees::SetCallBack(S32 Ref, tpVoid pVoid, tpParam pParam)
{
	tLDBPCStatut Res = cLdbpcErr;
	tDLLDonnee Data;

	// Lecture des informations sur la donnee
	if(DLLLireInfoDonnee(Ref, &Data) != cDLLOK)
	{
		mLDBPCErreur(cLdbpcErrDll);
	}
	else 
	{
		if(Data.Type != cDLLSortie)
		{
			// Verification de l'existance de la reference
			mLDBPCAssert(Ref < m_TabEvt.GetSize());

			// Verification de l'evt entrant
			mLDBPCAssert(m_TabEvt.GetAt(Ref) != NULL);

			m_TabEvt.GetAt(Ref)->SetCallBack(pVoid, pParam);
		}
	}
}

