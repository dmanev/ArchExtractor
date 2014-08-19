//**************************************************************************
// COMPOSANT : LdbpcCan
// FONCTION :  Interface pour la classes tcCanal
//
// Ce logiciel est la propriete de JCI :
// ---------------------------------------
// Il ne peut etre reproduit ni communique en totalite ou partie sans
// son autorisation ecrite.
//
// ------------------------------------------------------------------------
// Ce fichier doit etre inclus dans les composants utilisant les macros,
// types et fonctions definis par le composant LdbpcCan.
// Le fichier LdbpcCan.h doit contenir toute et uniquement
// l'information necessaire au programmeur pour utiliser le composant
// LdbpcCan.
// En particulier c'est ce fichier LdbpcCan.h qui contient l'historique
// et la documentation du composant dans son ensemble.
// ------------------------------------------------------------------------
// Reference a la documentation :
//
// ------------------------------------------------------------------------
// Presentation generale du composant :
//
// ------------------------------------------------------------------------
// Nom et initiales des developpeurs :	GUILLEN	GG
//
// ------------------------------------------------------------------------
// Historique du composant LdbpcCan dans son ensemble
// (initiales, date, modification)
//
// cree par :	GG : 20/04/2000
//
// ------------------------------------------------------------------------
// Historique du fichier LdbpcCan.h
// (initiales, date, modification)
//
//***************************************************************************

//-------------------------------------------------------------------------
//----- Inclusion de fichiers .h utiles a l'expansion de celui-ci -------
//-------------------------------------------------------------------------

//---- Definition pour mono-inclusion -----

#if !defined(I_LdbpcCan)
#define I_LdbpcCan

#include "Array.h"
#include "Ldbpc.h"			// Defini les types et constantes de bases
#include "LdbpcTim.h"			// Defini les types et constantes de bases
#include "afxtempl.h"			// Defini les types et constantes de bases
#include "afxmt.h"			// Defini les types et constantes de bases
#include "CANDll.h"		// Access to CANDLL
#include "tcSADAdrFrame.h"

//-------------------------------------------------------------------------
//------ Declaration des constantes exportees par ce composant ----------
//-------------------------------------------------------------------------
//(Com: 3 lettres identifiant ce composant)
//#define cComNomConstante ValeurDeLaConstante
//--------------------------------------------------------------------------
//------- Declaration des macros exportees par ce composant --------------
//--------------------------------------------------------------------------
// (Com: 3 lettres identifiant ce composant)
// #define mComNomMacro (DefinitionDeLaMacro)

//--------------------------------------------------------------------------
//------- Definition des types exportes par ce composant -----------------
//--------------------------------------------------------------------------
// (Com: 3 lettres identifiant ce composant)
// typedef ... tComNomType;

class tcCanal;
typedef tcArray<tcCanal *> tcTabCanal;
//--------------------------------------------------------------------------
//------- Declaration des variables exportees par ce composant -----------
//--------------------------------------------------------------------------
// (Com: 3 lettres identifiant ce composant)
// extern tType ComNomVariable;
// extern tType* pComNomVariable;
//--------------------------------------------------------------------------
//------- Donnees Constantes exportees par ce composant ------------------
//--------------------------------------------------------------------------
// (Com: 3 lettres identifiant ce composant)
//extern const tType ComNomVariable;
// Nota:
// Pour les variables qui peuvent etre modifiees par LdbpcCan mais non
// par les composants utilisateurs, on utilisera une definition conditionnel
//
// #ifdef LdbpcCan
// extern tType ComNomVariable;
// #else
// extern const tType ComNomVariable;
// #endif
//--------------------------------------------------------------------------
//------------------------- Fonctions exportees ----------------------------
//--------------------------------------------------------------------------
// extern tTypeRetour NomFonction(tTypeArgument NomArgument, ...);

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define cDisponible		0
#define cOccupe			  1

typedef struct
{
  tTrameCan TrameCan;
  U32  Id;
}tMsgBuffer;
//--------------------------------------------------------------------------
//------------------- Interface de la classe tcCanal ----------------------
//--------------------------------------------------------------------------
class tcCanal
{
public:
    tcCanal(tCallBackCanal * pStructCallBack=NULL);

    char * GetName() const { return((char*)(m_StructCallBack.ChannelName)); }
    virtual ~tcCanal();

    tcSADAdrFrame m_SADAdrTrace;

    // Acces au format du Canal (Intel ou Motorola)
    inline void SetFormat(U8 Format) {m_Format = Format;}
    inline U8 GetFormat(void) {return m_Format;}

    // Lecture du nom du Canal
    void LireNom(char ** pNom) const { *pNom = (char*)(m_StructCallBack.ChannelName); }

    // Attacher un flux a un canal
    tLDBPCStatut AttacherFlux(S32 RefFlux,tLdbpcTypeFlux Type);

    // Lire une reference de flux par rapport au type de flux
    tLDBPCStatut LireRefFlux(tLdbpcTypeFlux Type, S32 * pRefFlux);

    // Lecture de l'etat du canal
    inline char LireEtat() const { return m_Etat; }

    // Ecriture de l'etat du canal
    inline void EcrireEtat(char Etat) { m_Etat = Etat; }

    // Lecture de l'autorisation des flux non initie sur le canal
    inline BOOL LireAutorisation(void) const { return m_Autorise; }

    // Ecriture de l'autorisation des flux non initie sur le canal
    inline void EcrireAutorisation(BOOL Autorise)
    {
        m_Autorise = Autorise;
    }

    // Ecriture du ctrl en cours sur le canal
    inline void EcrireCtrlEnCours(U32 RefCtrl) { m_RefCtrlEnCours = RefCtrl; }

    // Controle personalise
    virtual BOOL Controler(tCtrl Ctrl);

    // Appel de la callback de fin de Controle
    virtual BOOL FinControle(tCtrl Ctrl,tStatus Statut);

    // Appel de la callback de Controle du LAP
    virtual BOOL CBControle(tCtrl Ctrl);

    // Autorisation personalisee
    virtual BOOL Autoriser(BOOL Autorise);

    virtual void Reset(void);
    virtual BOOL Send(tLdbpcTypeFlux Type, tAddress Adresse, tMsg* pMsg) {return(cFalse);}

protected:

    // Tableau de flux
    S32 m_RefFlux[MAX_FLUX];
    // Drapeau d'autrisation
    BOOL	m_Autorise;
    // Ref de control en cours
    U32		m_RefCtrlEnCours;
    // Etat du Canal
    char		m_Etat;
    // Format du Canal (Intel ou Motorola)
    U8		m_Format;
    tCallBackCanal m_StructCallBack;
};


class tObjetCanUU;
class tcCanDll;
class CChannelCAN;

class CChannelCAN : public tcCanal
{
public:
    CChannelCAN(tXCanChannel * pStruct=NULL);
    virtual ~CChannelCAN();

    void OnLdbpcTxCon();
    void OnLdbpcRxInd();
    void OnTxCon(tObjetCanUU* pObjetCanUU);
    void OnRxInd(tObjetCanUU* pObjetCanUU, tTrameCan* pTrameCan);

    // Controle personalise
    virtual BOOL Controler(tCtrl Ctrl);
    virtual void Reset(void);

    virtual BOOL Send(tLdbpcTypeFlux Type, tAddress Adresse, tMsg* pMsg);


private:

    typedef void (*tpf)(CChannelCAN*);
    tcTempoObjet<CChannelCAN*,tpf> m_TxTempo;
    CList<U32,U32> m_ListTxId;
    CCriticalSection m_CSTx;

    tcTempoObjet<CChannelCAN*,tpf> m_RxTempo;
    CList<tMsgBuffer*,tMsgBuffer*> m_ListRxId;
    CCriticalSection m_CSRx;

    tcCanDll * m_pCANChannel;
    tObjetCanUU * m_pRxCANUUDT;
    tObjetCanUU * m_pTxCANUUDT;
    tXCanChannel m_XCanChannel;
    BOOL	m_WakeUp;
    BOOL	m_FirstCtrlInit;
};

#endif // fin de l'inclusion conditionnelle de LdbpcCan.h
