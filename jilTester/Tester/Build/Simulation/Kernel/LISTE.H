//******************************************************************************
// COMPOSANT : Liste
// FONCTION  : Gestion de liste d'objets
//
// Ce logiciel est la propriete de JCI :
// ---------------------------------------
// Il ne peut être reproduit ni communique en totalite ou partie sans
// son autorisation ecrite.
//
// ------------------------------------------------------------------------
// Definition des fonctions exportees par le composant Liste :
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
// Historique du fichier Liste.h:
// -------------------------------------
// (initiales, date, modification)
//
// v1.0	:	GG		: 14/04/2000	: Creation
// v1.1 :	MG		: 13/03/2002	: Prise en compte des couches CAN
//
//***************************************************************************

#if !defined(AFX_LISTE_H__67AEE5C8_5D4C_11D4_8E5A_005004074F5E__INCLUDED_)
#define AFX_LISTE_H__67AEE5C8_5D4C_11D4_8E5A_005004074F5E__INCLUDED_

#include "LDBPCErr.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define NEXT		m_pNext
#define UNCHAINED	((void*)((char *)NULL + 1))

template< class TYPE >
class tcListe
{
public:
    tcListe<TYPE>();
    virtual ~tcListe<TYPE>();

    int			IsEmpty() {return(m_pPremier == NULL);}

    TYPE* 		GetHead() {return m_pPremier; }
    //	TYPE*		GetTail();
    TYPE*		GetNext(TYPE*);

    void 		AddHead(TYPE*);
    //	void 		AddTail(TYPE*);

    void 		InsertAfter(TYPE*, TYPE*);

    void 		RemoveHead();
    void		RemoveNext(TYPE*);
    void		Remove(TYPE*);

private :

    TYPE*		m_pPremier;

};

template<class TYPE>
tcListe<TYPE>::tcListe<TYPE>()
{
    m_pPremier = NULL;
}

template<class TYPE>
tcListe<TYPE>::~tcListe<TYPE>()
{
}

/*template<class TYPE>
TYPE* tcListe<TYPE>::GetTail()
{
	TYPE* pElt = m_pPremier;

	if( pElt == NULL )
	{
		return NULL;
	}
	else
	{
		while( pElt->NEXT != NULL )
		{
			pElt = pElt->NEXT;
		}
		return pElt;
	}
}
*/
template<class TYPE>
TYPE* tcListe<TYPE>::GetNext(TYPE* pElt)
{
    if( pElt == NULL )
    {
        return NULL;
    }
    else
    {
        return pElt->NEXT;
    }
}

template<class TYPE>
void tcListe<TYPE>::AddHead(TYPE* pElt)
{
    if( pElt->NEXT == (TYPE*)UNCHAINED )
    {
        pElt->NEXT = m_pPremier;
        m_pPremier = pElt;
    }
    else
        mLDBPCErreur("Erreur tcListe");
}
/*
template<class TYPE>
void tcListe<TYPE>::AddTail(TYPE* pElt)
{
	if( pElt->NEXT == (TYPE*)UNCHAINED)
	{
		if( IsEmpty() )
		{
			m_pPremier = pElt;
		}
		else
		{
			GetTail()->NEXT = pElt;
		}

		pElt->NEXT = NULL;
	}
	else 
		mLDBPCErreur("Erreur tcListe");
}
*/
template<class TYPE>
void tcListe<TYPE>::InsertAfter(TYPE* pElt, TYPE* New)
{
    if( New->NEXT == (TYPE*)UNCHAINED)
    {
        New->NEXT = pElt->NEXT;
        pElt->NEXT = New;
    }
    else
        mLDBPCErreur("Erreur tcListe");
}

template<class TYPE>
void tcListe<TYPE>::RemoveHead()
{
    if( ! IsEmpty() )
    {
        TYPE* Suppr = m_pPremier;
        m_pPremier  = m_pPremier->NEXT;
        Suppr->NEXT = (TYPE*)UNCHAINED;
    }
}

template<class TYPE>
void tcListe<TYPE>::Remove(TYPE* Cible)
{
    TYPE** ppElt = &m_pPremier;

    while( *ppElt != NULL )
    {
        if( *ppElt == Cible )
        {
            *ppElt = Cible->NEXT;
            Cible->NEXT = (TYPE*)UNCHAINED;

            return;
        }

        ppElt = &( (*ppElt)->NEXT);
    }
}

template<class TYPE>
void tcListe<TYPE>::RemoveNext(TYPE* pElt)
{
    TYPE* pSuppr = pElt->NEXT;

    if( pSuppr != NULL )
    {
        pElt->NEXT = pSuppr->NEXT;
        pSuppr->NEXT = (TYPE*)UNCHAINED;
    }
}

#endif // !defined(AFX_LISTE_H__67AEE5C8_5D4C_11D4_8E5A_005004074F5E__INCLUDED_)
