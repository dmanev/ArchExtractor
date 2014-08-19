//**************************************************************************
// COMPOSANT : LdbpcFlu
// FONCTION :  Interface pour la classes tcFlux
//
// Ce logiciel est la propriete de JCI :
// ---------------------------------------
// Il ne peut etre reproduit ni communique en totalite ou partie sans
// son autorisation ecrite.
//
// ------------------------------------------------------------------------
// Ce fichier doit etre inclus dans les composants utilisant les macros,
// types et fonctions definis par le composant LdbpcFlu.
// Le fichier LdbpcFlu.h doit contenir toute et uniquement
// l'information necessaire au programmeur pour utiliser le composant
// LdbpcFlu.
// En particulier c'est ce fichier LdbpcFlu.h qui contient l'historique
// et la documentation du composant dans son ensemble.
// ------------------------------------------------------------------------
// Reference a la documentation :
//
// ------------------------------------------------------------------------
// Presentation generale du composant : Gestion des flux LDBPC
//
// ------------------------------------------------------------------------
// Nom et initiales des developpeurs :
//
//		Gilles	GUILLEN		GG
//
// ------------------------------------------------------------------------
// Historique du composant LdbpcFlu dans son ensemble
// (initiales, date, modification)
//
// v1.0 :	GG : 25/04/2000	: Creation
// v1.2 :	GG : 18/03/2002	: Correction sur la verification des trames
//
// ------------------------------------------------------------------------
// Historique du fichier LdbpcFlu.h
// (initiales, date, modification)
//
//***************************************************************************

//-------------------------------------------------------------------------
//----- Inclusion de fichiers .h utiles a l'expansion de celui-ci -------
//-------------------------------------------------------------------------

#include "Array.h"
#include "Ldbpc.h"			// Defini les types et constantes de bases
#include "LdbpcTem.h"			// Defini les types et constantes de bases

//---- Definition pour mono-inclusion -----

#if !defined(I_LdbpcFlu)
#define I_LdbpcFlu

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

class tcFlux;
typedef tcArray<tcFlux *> tcTabFlux;
typedef tcArray<S32> tcDWordArray;

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
// Pour les variables qui peuvent etre modifiees par LdbpcFlu mais non
// par les composants utilisateurs, on utilisera une definition conditionnel
//
// #ifdef LdbpcFlu
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
class tcCanal;
//--------------------------------------------------------------------------
//------------------- Interface de la classe tcFlux ----------------------
//--------------------------------------------------------------------------
class tcFlux
{
public:
    // Constructeurs
    tcFlux();
    tcFlux(tcCanal * pCanal, tInfoFlux * pIflux);
    // Destructeur
    virtual ~tcFlux();
    tcTempoParam1<S32> Tempo;

protected:

    // Reference du Canal
    tcCanal * m_pCanal;

    // Reference du Canal
    tChannel	m_Canal;
    // Type de Trame
    tLdbpcTypeFlux	m_Type;
    // Taleau de trame
    tcDWordArray m_TabTrame;
    // Verifie l'existance de la reference de trame
    tLDBPCStatut ExisteTrame(S32 Ref);


public:

    tcCanal * GetChannel() const { return(m_pCanal); }

    virtual void SetBufferTemp() {}
    virtual void SetBufferTempLng(U32 taille) {}

    // Lire le type de flux
    inline tLdbpcTypeFlux LireType(void) const { return m_Type; }

    // Lire le nombre de trames attachees au flux
    inline int GetSize(void) const { return m_TabTrame.GetSize(); }

    // Lire la reference du canal
    inline tChannel LireRefCanal(void) const { return m_Canal; }

    // Ecrire la reference du canal
    inline void EcrireRefCanal(tChannel RefCan) { m_Canal = RefCan; }

    // Attacher une trame a un flux
    tLDBPCStatut Attacher(S32 RefTrame);

    // Lire une reference de trame par rapport a un index
    tLDBPCStatut LireRefTrame(int Index, S32 * pRefTrame);

    // Mise a jour de la fonction de callback en Emission
    virtual void MajCallBack(tpCallBackStatusAddr pFinAction) {}

    // Lecture de l'adresse en cours
    virtual tAddress LireAdrEnCours(void) const { return 0; }

    // Lecture de la taille du message en cours
    virtual U16 LireTailleMsgEnCours(void) const { return 0; }

    // Lecture du message en cours
    virtual tLDBPCStatut LireMsgEnCours(tMsg ** ppMsg) {return cLdbpcErr;}

    // Ecriture du message en cours
    virtual tLDBPCStatut EcrireMsgEnCours(tMsg * pMsg) {return cLdbpcErr;}

    // Ecriture de l'adresse en cours
    virtual void EcrireAdrEnCours(tAddress) {}

    // Appel de la fonction callback personalisee
    virtual BOOL Action(void) {return 0;}
    // Appel de la fonction callback personalisee
    virtual BOOL Action(tAddress * Adr,tMsg ** pMsg){return 0;}

    // Test de la callback personalisee
    virtual BOOL IsAction(void) { return(cFalse);}

    // Appel de la fonction callback standard de din d'action(emission ou reception)
    virtual BOOL FinAction(void) { return 0; }
};


//--------------------------------------------------------------------------
//------------------- Interface de la classe tcFluxI ----------------------
//--------------------------------------------------------------------------
class tcFluxI : public tcFlux
{
public:
    // Constructeurs
    tcFluxI();
    tcFluxI(tcCanal * pCanal, tInfoFlux * pIflux);
    // Destructeur
    virtual ~tcFluxI();

private:

    // Fonction callback d'action personnalisee par le parametrage
    tpFluCBActionI m_pUserCBAction;
    // Fonction callback de Fin action standard
    tpCallBackStatusAddr	m_pCBFinActionStd;

    // Adresse en cours de transmission
    tAddress m_AdresseEnCours;
    // Message en cours de traitement
    tMsg * m_pMsgEnCours;
    tMsg m_MsgTemp;
    U32 m_TailleBufferMax;

public:
    virtual void SetBufferTemp()
    {
        if((m_MsgTemp.pBuffer == NULL)&&(m_TailleBufferMax))
            m_MsgTemp.pBuffer = (U8 *) new char[m_TailleBufferMax * sizeof(U8)];
    }
    virtual void SetBufferTempLng(U32 taille)
{ if(taille > m_TailleBufferMax) m_TailleBufferMax = taille; }

    // Lecture de l'adresse en cours
virtual tAddress LireAdrEnCours(void) const { return m_AdresseEnCours; }

    // Lecture de la taille du message en cours
    virtual U16 LireTailleMsgEnCours(void) const
    { return(m_pMsgEnCours?m_pMsgEnCours->Lng:0); }

    // Ecriture de l'adresse en cours
    virtual void EcrireAdrEnCours(tAddress Adr) {m_AdresseEnCours = Adr; }

    // Lecture du message en cours
    virtual tLDBPCStatut LireMsgEnCours(tMsg ** pMsg);

    // Ecriture du message en cours
    virtual tLDBPCStatut EcrireMsgEnCours(tMsg * pMsg);

    // Mise a jour de la fonction de callback en Emission
    void MajCallBack(tpCallBackStatusAddr pFinAction);

    // Appel de la fonction callback personalisee
    virtual BOOL Action(void);

    // Test de la callback personalisee
    virtual BOOL IsAction(void) { return(m_pUserCBAction != NULL) ;}

    // Appel de la fonction callback standard de din d'action(emission ou reception)
    virtual BOOL FinAction(void);
};


//--------------------------------------------------------------------------
//------------------- Interface de la classe tcFluxNI ---------------------
//--------------------------------------------------------------------------
class tcFluxNIP : public tcFlux
{
public:
    // Constructeurs
    tcFluxNIP();
    tcFluxNIP(tcCanal * pCanal, tInfoFlux * pIflux);
    tpFluCBActionNIP m_pUserCBAction;

    // Destructeur
    virtual ~tcFluxNIP();

    // Appel de la fonction callback personalisee
    virtual BOOL Action(tAddress * Adr,tMsg ** pMsg);

    // Test de la callback personalisee
    virtual BOOL IsAction(void) { return(m_pUserCBAction != NULL) ;}
};

class tcFluxNIC : public tcFlux
{
public:
    // Constructeurs
    tcFluxNIC();
    tcFluxNIC(tcCanal * pCanal, tInfoFlux * pIflux);
    tpFluCBActionNI m_pUserCBAction;

    // Destructeur
    virtual ~tcFluxNIC();

};

#endif // fin de l'inclusion conditionnelle de LdbpcFlu.h
