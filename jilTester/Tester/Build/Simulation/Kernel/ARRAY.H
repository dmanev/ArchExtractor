/***************************************************************************



  Ce logiciel est la propri‚t‚ de JCI.
  -------------------------------------

  Il ne peut ˆtre reproduit ni communiqu‚ en totalit‚ ou partie sans
  son autorisation ‚crite.

                     ------------------------------

                       COMPOSANT : tcArray

                       FONCTION  : Tableau dynamique

                     ------------------------------

**************************************************************************


 Historique du fichier dllcom.cpp:
 -------------------------------------
 (initiales, date, modification)
	Etienne BARBAUX Creation le 24/07/2000

***************************************************************************/
/*
#include <afxtempl.h>
#if !defined(I_ARRAY)
template <class TYPE>
class tcArray : public CArray< TYPE, TYPE> {};
#define I_ARRAY	1
#endif
*/
//---- Definition pour mono-inclusion -----
#if !defined(I_ARRAY)
#define I_ARRAY	1
// ******************************************************************
//
//			class tcArrayElt ->	Element de chainage
//
// ******************************************************************
// Element de chainage, cet element contient "Sz" donnees de type "TYPE"
template <class TYPE, int Sz>
class tcArrayElt
{
public :
    tcArrayElt( int PremierIndex)
    {
        m_PremierIndex = PremierIndex;
        m_Next = NULL;
        for(int i = 0; i < Sz; i++)
        {
            m_Table[i] = (TYPE)0;
        }
#ifdef TEST_TCARRAY
        printf("Alloc\n");
#endif
    }
    ~tcArrayElt(void)
    {
#ifdef TEST_TCARRAY
        printf("Delete\n");
#endif
    }

    // Les index utilisés par ces deux methodes correspondent aux index
    // du tcArray
    inline int			GetIndexMax()	 { return(m_PremierIndex+Sz); }
    inline int			GetIndexMin()	 { return(m_PremierIndex);    }
    inline TYPE& operator[](int Index)   { return m_Table[Index-m_PremierIndex]; }

    // pointeur vers le chainon suivant
    tcArrayElt<TYPE,Sz>*  m_Next;

private :
    int		m_PremierIndex; // = index de m_Table[0] dans le tcArray
    TYPE    m_Table[Sz];
};


// ******************************************************************
//
//			class tcArrayElt ->	Element de chainage
//
// ******************************************************************
template <class TYPE, int Sz = 1020>
class tcArray
{
public  :
    tcArray<TYPE,Sz>()	{ m_pPremierElt = NULL; m_Size=0; }
    ~tcArray<TYPE,Sz>()	{ RemoveAll(); }

    // ***************************************************
    // Methodes utilisants GetSize/GetSize/SetAt/GetAt
    // ***************************************************

    // Ajoute a la fin
    int Add(TYPE Val)
    {
        int OldSize = GetSize();
        SetSize( OldSize + 1 );
        SetAt( OldSize , Val );
        return OldSize;
    }

    // SetAtGrow() = SetAt() + SetSize() si besoin
    void SetAtGrow( int Index, TYPE Val )
    {
        if( (Index+1) > GetSize() )
        {
            SetSize( Index+1 );
        }
        SetAt( Index, Val );
    }

    inline void RemoveAll(void) { SetSize(0); }

    // ***************************************************
    // Methodes SetAt/GetAt operateur []
    // ***************************************************
    TYPE& operator[](int Index)
    {
        // On verifie si l'Index existe
        if( Index < GetSize() )
        {
            // On parcours la liste du debut a la fin
            tcArrayElt<TYPE,Sz>* Elt = m_pPremierElt;
            while( Elt != NULL )
            {
                // si le chainon courant contient l'index
                // on le retourne
                if( Index < Elt->GetIndexMax()  )
                {
                    return (*Elt)[Index];
                }
                Elt = Elt->m_Next;
            }
            // On ne doit pas sortir du while, si on en sort, c'est
            // que le champ m_Size est incoherent avec le nombre
            // d'elements de chainage.
        }

        // l'index est hors limite
        return *((TYPE*)NULL);
    }
    inline TYPE GetAt(int Index)		   { return (*this)[Index];}
    inline void SetAt(int Index, TYPE Val) { (*this)[Index] = Val; }

    // ***************************************************
    // Methodes GetSize/GetSize/SetAt/GetAt
    // ***************************************************
    inline int  GetSize() const {return m_Size;}
    void SetSize( int Size )
    {
        // mise a jour de m_Size
        m_Size = Size;

        // On verfie que les elts sont alloués jusqu'à "Size"
        tcArrayElt<TYPE,Sz>*  pElt	= m_pPremierElt;
        tcArrayElt<TYPE,Sz>** ppElt	= &m_pPremierElt;
        int IndexMaxEltPrec			= 0;

        while( IndexMaxEltPrec < Size )
        {
            if( pElt == NULL )
            {
                // Cet element de chainage n'est pas alloue
                // on l'alloue :
                pElt   = new tcArrayElt<TYPE,Sz>( IndexMaxEltPrec );
                *ppElt = pElt;
            }

            // on passe à l'elt suivant
            IndexMaxEltPrec  = pElt->GetIndexMax();
            ppElt            = &( pElt->m_Next );
            pElt             =    pElt->m_Next  ;
        }

        // On desaloue les elt correspondant a des index > a "Size"

        // pElt pointe sur le Next du dernier chainon qui doit
        // exister, on suuprime les elts suivants
        *ppElt = NULL;

        while( pElt != NULL )
        {
            tcArrayElt<TYPE,Sz>*  pNextElt = pElt->m_Next;
            delete pElt;
            pElt = pNextElt;
        }
    };

private :
    int						m_Size;
    tcArrayElt<TYPE,Sz>*	m_pPremierElt;
};


// ******************************************************************
//
//		                	TEST
//
// ******************************************************************

// pour rejouer le test :
// definir TEST_TCARRAY
// inclure Array.h dans un .C
// compiler et executer

#ifdef TEST_TCARRAY

typedef tcArray<int,3> tIntArray;

void Print( tIntArray* pArray )
{
    for( int i=0; i<pArray->GetSize(); i++)
    {
        printf( "%d ", pArray->GetAt(i) );
    }
    printf( "\n" );
}

int main(int argc, char* argv[])
{
    tIntArray Array;

    Print( &Array );
    Array.SetSize(10);
    for( int i=0; i<Array.GetSize(); i++)
    {
        Array[i] = i;
    }

    Array.Add(10);
    Array.SetAtGrow(12,12);
    Array.SetAt(11,11);

    printf( "Resultat Attendu -> 0 1 2 3 4 5 6 7 8 9 10 11 12\n" );
    printf( "Resultat         -> " );
    Print( &Array );
    printf( "\n" );

    // -------------- Diminution de la taille
    Array.SetSize(5);

    printf( "Resultat Attendu -> 0 1 2 3 4 \n" );
    printf( "Resultat         -> " );
    Print( &Array );
    printf( "\n" );

    printf("Verifiez que le nombre d'Alloc est egal au nombre de Delete\n\n");
    return 0;
}
#endif
#endif
