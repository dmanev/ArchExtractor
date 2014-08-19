//**************************************************************************
// COMPOSANT : LdbpcRdo
// FONCTION : Implementation des classes de trame 
//
// Ce logiciel est la propriete de JCI :
// ---------------------------------------
// Il ne peut être reproduit ni communique en totalite ou partie sans
// son autorisation ecrite.
//
// ------------------------------------------------------------------------
// Definition des fonctions exportees par le composant LdbpcRdo :
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
// Historique du fichier LdbpcRdo.c:
// -------------------------------------
// (initiales, date, modification)
//
// v1.0	:	GG : 20/04/2000	: Creation
// v1.1 :	GG : 15/02/2002	: Correction PB de décalage
//
//
//***************************************************************************

#define LdbpcRdo "LdbpcRdo"

//--------------------------------------------------------------------------
//---------------- Inclusion de fichiers (système et librairies -----------
//--------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////
//
// LdbpcRdo.cpp: implementation of the tcElement class.
//
//////////////////////////////////////////////////////////////////////

#include "Ldbpc.h"			// Defini les types et constantes de bases
#include "math.h"			// Defini les routines mathematiques
#include "LdbpcRdo.h"
#include "string.h"
//--------------------------------------------------------------------------
//------- Inclusion des definitions des autres composants utiles ---------
//--------------------------------------------------------------------------
#include "LDBPCDon.h"	// Definit l'interface du Module Donnees
#include "LDBPCRes.h"	// Definit l'interface du Module Donnees
//--------------------------------------------------------------------------
//------- Declaration des constantes locales à ce composant --------------
//--------------------------------------------------------------------------
// #define cNomConstante ValeurDeLaConstante
#define cDecalageMax 2
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
//--------------- Implementation de la classe tcRefDonnee -----------------
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// Constructeurs
//--------------------------------------------------------------------------
tcRefDonnee::tcRefDonnee()
{
	m_RefDonnee	=	0;
	m_Position	=	0;
	m_pNext = (tcRefDonnee*)UNCHAINED;
	m_RefTrame = 0;
	m_TypeTab = 0;
	m_TailleBit = 0;
	m_Valeur = 0;
}

tcRefDonnee::tcRefDonnee(S32 RefTrame,S32 RefDonnee, U32 Position, U32 TailleTrame)
{
	m_RefTrame	= RefTrame;
	m_RefDonnee	=	RefDonnee;
	m_Position	=	Position;
	// Allouer un buffer pour les lectures ecritures et mémorisations 
	m_pBufferTemp = (U8*) new U8[(TailleTrame+cDecalageMax)*sizeof(U8)];
	memset(m_pBufferTemp,0,(TailleTrame+cDecalageMax)*sizeof(U8));
	m_pNext = (tcRefDonnee*)UNCHAINED;

	m_TypeTab = Donnees.SortieTypeBuffer(RefDonnee);
	m_TailleBit = Donnees.LireTailleDonnee(RefDonnee);

}

//--------------------------------------------------------------------------
// Destructeur
//--------------------------------------------------------------------------
tcRefDonnee::~tcRefDonnee()
{
	if(m_pBufferTemp)
		delete [] m_pBufferTemp;
}

//--------------------------------------------------------------------------
// Lire la position du bit de poids faible de la donnee
//--------------------------------------------------------------------------
U32 tcRefDonnee::LireLSB()
{
	U32 Lsb;

	// Lecture de la taille en bits de l'entree par reference
	Lsb = m_Position + m_TailleBit - 1;

	return Lsb;
}

//--------------------------------------------------------------------------
// Ecriture de la donnee a partir du message
//--------------------------------------------------------------------------
tLDBPCStatut tcRefDonnee::Ecrire(tMsg * pMsg)
{
	tLDBPCStatut Res = cLdbpcErr;
	U32 TailleTotale;

	// Taille de travail
	TailleTotale = m_TailleBit + (m_Position % 8);

	// Buffer de travail
	memset(m_pBufferTemp,0,mTailleOctet(TailleTotale));

	// Copier la partie de trame correspondant a la donnee dans un buffer
	// GG : 15/02/2002 : correction
	memcpy(m_pBufferTemp, &pMsg->pBuffer[m_Position/8], mTailleOctet(TailleTotale));

	// Decaler la partie de trame a gauche
	if(m_Position % 8)
		Res = DecalerAGauche(mTailleOctet(TailleTotale),(U8)(m_Position % 8));
	else Res = cLdbpcOk;

	if(m_TypeTab)
	{
		if(Res == cLdbpcOk)
		{
			// Copier le buffer dans la sortie
			Res = Donnees.EcrireSortie(m_RefDonnee, m_pBufferTemp);
		}
	}
	else
	{
		// Transforme la partie de trame en entier 32 bits
		Res = LireValeur();
		if(Res == cLdbpcOk)
		{
			// Copier la valeur dans la sortie 
			Res = Donnees.EcrireSortie(m_RefDonnee, m_Valeur);
		}
	}
	return Res;
}

//--------------------------------------------------------------------------
// Lecture de la donnee et stockage dans une trame 
// Copier le buffer dans le message
//--------------------------------------------------------------------------
tLDBPCStatut tcRefDonnee::Lire(tMsg * pMsg)
{
	U32 Id;
	U32 PosOctTrame  = m_Position/8;
	tLDBPCStatut Res = cLdbpcErr;
	U32 PosDonneeCalGau;
	U32 PosDonneeReel;
	U32 TailleTotale = m_TailleBit + (m_Position % 8);

	memset(m_pBufferTemp,0,mTailleOctet(TailleTotale));
	
	// Copier la donnee dans le buffer
	Res = LireDonnee();

	// Positionner le buffer
	if(Res == cLdbpcOk)
	{
		PosDonneeCalGau = 8-(m_TailleBit%8);
		PosDonneeReel = m_Position % 8;

		if(PosDonneeCalGau < PosDonneeReel )
			DecalerADroite(mTailleOctet(TailleTotale), (U8)(PosDonneeReel-PosDonneeCalGau));
		else if((PosDonneeCalGau > PosDonneeReel) && ((PosDonneeCalGau-PosDonneeReel)%8) )
			DecalerAGauche(mTailleOctet(TailleTotale), (U8)(PosDonneeCalGau-PosDonneeReel));

		// Masquer le premier octet
		pMsg->pBuffer[PosOctTrame] = pMsg->pBuffer[PosOctTrame] | m_pBufferTemp[0];
		
		// Copie du buffer
		for(Id = 1; Id < mTailleOctet(TailleTotale) ; Id++)
		{
			pMsg->pBuffer[PosOctTrame + Id] |= m_pBufferTemp[Id];
		}
	}


	return Res;
}

//--------------------------------------------------------------------------
// Lecture de la donnee et stockage dans un buffer
//--------------------------------------------------------------------------
tLDBPCStatut tcRefDonnee::LireDonnee()
{
	S32	Id1;
	S32	Id2;
	tLDBPCStatut Res = cLdbpcErr;
	U32 Valeur = 0;
	if(m_TypeTab)
	{
		// Copier la donnee dans le buffer
		Res = Donnees.Lire(m_RefDonnee, m_pBufferTemp, NULL, NULL);
	}
	else
	{
		// Copier la donnee dans le buffer
		Res = Donnees.Lire(m_RefDonnee, &Valeur, NULL, NULL);
		
		// Transformer en valeur
		Id2 = 0;
		for(Id1 = mTailleOctet(m_TailleBit)-1; Id1 >= 0; Id1--)
		{
			switch(Id2)
			{
				case 3:	m_pBufferTemp[Id1] = (U8)((Valeur & 0xFF000000L) >> 24);	break;
				case 2:	m_pBufferTemp[Id1] = (U8)((Valeur & 0xFF0000L	) >> 16);	break;
				case 1:	m_pBufferTemp[Id1] = (U8)((Valeur & 0xFF00L	) >> 8);		break;
				case 0:	m_pBufferTemp[Id1] = (U8)(Valeur & 0xFFL		);			break;
				default : Res = mLDBPCErreur(cLdbpcErrDecalage);
			}
			Id2++;
		}

		if(Ressources.GetFormat(m_RefTrame) == cCodageIntel)
		{
			U8 car;
			if(mTailleOctet(m_TailleBit) == 4)
			{
				car = m_pBufferTemp[0];
				m_pBufferTemp[0] = m_pBufferTemp[3];
				m_pBufferTemp[3] = car;
				car = m_pBufferTemp[1];
				m_pBufferTemp[1] = m_pBufferTemp[2];
				m_pBufferTemp[2] = car;
			}
			else if(mTailleOctet(m_TailleBit) == 2)
			{
				car = m_pBufferTemp[0];
				m_pBufferTemp[0] = m_pBufferTemp[1];
				m_pBufferTemp[1] = car;
			}
		}
	}

	return Res;
}

//--------------------------------------------------------------------------
// Lit une valeur de 32 bit dans le buffer
//--------------------------------------------------------------------------
tLDBPCStatut tcRefDonnee::LireValeur()
{
	tLDBPCStatut Res = cLdbpcErr;
	S32	Id1;
	S32	Id2;

	m_Valeur = 0;

	if(mTailleOctet(m_TailleBit) <= sizeof(U32))
	{
		if(m_TailleBit % 8)
			Res = DecalerADroite(mTailleOctet(m_TailleBit), (U8)(8-(m_TailleBit % 8)));
		else Res = cLdbpcOk;

		if(Res == cLdbpcOk)
		{
			// Transformer en valeur
			Id2 = 0;
			for(Id1 = mTailleOctet(m_TailleBit)-1; Id1 >= 0; Id1--)
			{
				switch(Id2)
				{
				case 3:	m_Valeur |= (((U32)m_pBufferTemp[Id1])<<24) & 0xFF000000L;	break;
				case 2:	m_Valeur |= (((U32)m_pBufferTemp[Id1])<<16) & 0xFF0000L;	break;
				case 1:	m_Valeur |= (((U32)m_pBufferTemp[Id1])<<8) & 0xFF00L;		break;
				case 0:	m_Valeur |= m_pBufferTemp[Id1] & 0xFFL;		break;
				default : Res = mLDBPCErreur(cLdbpcErrDecalage);
				}
				Id2++;
			}

			if(Ressources.GetFormat(m_RefTrame) == cCodageIntel)
			{
				U32 Val1,Val2,Val3,Val4;
				if(mTailleOctet(m_TailleBit) == 4)
				{
					Val1 = (m_Valeur & 0xFF000000L)>>24;
					Val2 = (m_Valeur & 0xFFL)<<24;
					Val3 = (m_Valeur & 0xFF0000L)>>8;
					Val4 = (m_Valeur & 0xFF00L)<<8;
					m_Valeur = 0;
					m_Valeur |= Val2 & 0xFF000000L;
					m_Valeur |= Val1 & 0xFFL;
					m_Valeur |= Val4 & 0xFF0000L;
					m_Valeur |= Val3 & 0xFF00L;
				}
				else if(mTailleOctet(m_TailleBit) == 2)
				{
					Val1 = m_Valeur & 0xFF00L;
					Val2 = m_Valeur & 0xFFL;
					m_Valeur = 0;
					m_Valeur |= (Val2<<8) & 0xFF00L;
					m_Valeur |= (Val1>>8) & 0xFFL;
				}
			}
		}

	}
	else
		Res = mLDBPCErreur(cLdbpcErrDecalage);

	return Res;
}

//--------------------------------------------------------------------------
// Decaler un buffer à gauche de d'un nombre de bits
//--------------------------------------------------------------------------
tLDBPCStatut tcRefDonnee::DecalerAGauche(U32 TailleBuf, U8 decalage)
{
	tLDBPCStatut Res = cLdbpcOk;
	U32	Id;
	U8 Mem[50] = {0};
	U8	Masque;

	// Véification des parametres
	if((decalage > 0) && (decalage < 8) && (TailleBuf >= mTailleOctet((U32)m_TailleBit)) 
		&& (m_pBufferTemp != NULL) && (m_TailleBit > 0) )
	{
		memcpy(Mem, m_pBufferTemp, TailleBuf);
		
		// Decalage du buffer
		for(Id = 0; Id < TailleBuf; Id++)
		{
			m_pBufferTemp[Id] = m_pBufferTemp[Id] << decalage;
		}

		// Preparation du masque pour replacer les bits qui seront perdus au decalage
		Masque = 0xFF >> (8-decalage); 

		// Replacer des bits perdus au Decalage
		for(Id = 1; Id < TailleBuf; Id++)
		{
			m_pBufferTemp[Id-1] = (m_pBufferTemp[Id-1] & ~Masque) | ((Mem[Id] >> (8-decalage)) & Masque);
		}

		// Remise a zero des octets en fin de donnee non utilises
		for(Id = mTailleOctet(m_TailleBit); Id < TailleBuf ; Id++)
			m_pBufferTemp[Id] = 0;
	}
	else
		Res = mLDBPCErreur(cLdbpcErr);

	return Res;
}

//--------------------------------------------------------------------------
// Decaler le buffer à droite
//--------------------------------------------------------------------------
tLDBPCStatut tcRefDonnee::DecalerADroite(U32 TailleBuf, U8 decalage)
{
	tLDBPCStatut Res = cLdbpcOk;
	U32	Id1;
	U8 Mem[50] = {0};	// Attention !!!!
	U8	Masque;
	U32 TailleTotal = m_TailleBit + (U32)decalage;

	// Vérification des parametres
	if((decalage > 0) && (decalage < 8) && (TailleBuf >= mTailleOctet(TailleTotal)) 
		&& (m_pBufferTemp != NULL) && (m_TailleBit > 0))
	{
		memcpy(Mem, m_pBufferTemp, TailleBuf);

		// Decalage du buffer a la position dans la trame
		for(Id1 = 0; Id1 < TailleBuf; Id1++)
		{
			m_pBufferTemp[Id1] = m_pBufferTemp[Id1] >> decalage;
		}

		// Preparation du masque pour replacer les bits qui seront perdus au decalage
		Masque = 0xFF << (8-(decalage));

		// Replacer des bits perdus au Decalage
		for(Id1 = 1; Id1 < TailleBuf; Id1++)
		{
			// GG : 15/02/2002 : correction
			m_pBufferTemp[Id1] = (m_pBufferTemp[Id1] & ~Masque) | ((Mem[Id1-1] << (8-(decalage))) & Masque);
		}

		// Masque du premier octet
		Masque = (U8)pow((double)2,(double)(8 - (decalage%8))) - 1;

		// Remise a zero des bits du premier octet non utilises
		m_pBufferTemp[0] = m_pBufferTemp[0] & Masque;

		// Masque du dernier octet
    /* CV : fig bug => comment this line from starter kit
		Masque = ~((U8)pow((double)2,(double)(8 - (TailleTotal%8))) - 1);
		
		// Remise a zero des bits en fin de donnee non utilises
		if(Masque)
			m_pBufferTemp[mTailleOctet(TailleTotal)-1] = m_pBufferTemp[mTailleOctet(TailleTotal)-1] & Masque;
      */
	}
	else
		Res = mLDBPCErreur(cLdbpcErr);

	return Res;
}