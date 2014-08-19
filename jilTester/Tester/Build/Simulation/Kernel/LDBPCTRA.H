//**************************************************************************
// COMPOSANT : LdbpcTra
// FONCTION :  Interface pour les classes de trames
//
// Ce logiciel est la propriete de JCI :
// ---------------------------------------
// Il ne peut etre reproduit ni communique en totalite ou partie sans
// son autorisation ecrite.
//
// ------------------------------------------------------------------------
// Ce fichier doit etre inclus dans les composants utilisant les macros,
// types et fonctions definis par le composant LdbpcTra.
// Le fichier LdbpcTra.h doit contenir toute et uniquement
// l'information necessaire au programmeur pour utiliser le composant
// LdbpcTra.
// En particulier c'est ce fichier LdbpcTra.h qui contient l'historique
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
// Historique du composant LdbpcTra dans son ensemble
// (initiales, date, modification)
//
// cree par :	GG : 20/04/2000
//
// ------------------------------------------------------------------------
// Historique du fichier LdbpcTra.h
// (initiales, date, modification)
//
//***************************************************************************

//-------------------------------------------------------------------------
//----- Inclusion de fichiers .h utiles a l'expansion de celui-ci -------
//-------------------------------------------------------------------------

#include "Ldbpc.h"			// Defini les types et constantes de bases
#include "LdbpcRdo.h"
#include "Array.h"
#include "LdbpcTem.h"

//---- Definition pour mono-inclusion -----

#if !defined(I_LdbpcTra)
#define I_LdbpcTra

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

class tcTrame;
typedef tcArray<tcTrame *> tcTabTrame;
class tcCanal;


typedef struct
{
    tInfoTrame* pInfoFrame;
    tcCanal *   pCanal;
    char *      pEvtName;
    char *      pBufferName;
    char *      pBufferSizeName;
    char *      pRxModeName;
    S32     EvtRef;
    S32     BufferRef;
    S32     RxModeRef;
    S32     BufferSizeRef;
}tInfoBuildFrame;

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
// Pour les variables qui peuvent etre modifiees par LdbpcTra mais non
// par les composants utilisateurs, on utilisera une definition conditionnel
//
// #ifdef LdbpcTra
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
//------------------- Interface de la classe tcTrame ----------------------
//--------------------------------------------------------------------------
class tcTrame
{
public:
    // ------------------------------------------------------------------------
    // Constructeurs
    // ------------------------------------------------------------------------
    tcTrame();
    tcTrame(tInfoBuildFrame * pBuildFrame);

    // ------------------------------------------------------------------------
    // Destructeur
    // ------------------------------------------------------------------------
    virtual ~tcTrame();

protected:
    tcCanal *		m_pCanal;
    tLdbpcTypeFlux	m_TypeFlux;		// Type de flux
    S32			m_RefFlux;		// Reference du flux

    char *			m_pNom;			// Nom de la trame
    tAddress		m_Adresse;		// Adresse de la trame
    U32			m_CurrentSize;	// Taille de la trame courante (en octet)
    U32			m_MaxSize;		// Taille de la trame max (en octet)
    tTypeFrame      m_TypeFrame;    // Trame à Longueur Fixe/Variable

    U8 *		m_pBufferTemp;
    U8 *		m_pBufferSave;
    BOOL		m_FlagModif;

    tcListRefDonnee	m_ListeDonnee;	// Liste de reference de donnees
    S32			m_RefEvt;		// Reference de l'evenement
    S32         m_BufferRef;
    S32         m_BufferSizeRef;

public:
    virtual	void Initialiser();
    // Lecture du Type du flux de la trame
    inline tLdbpcTypeFlux LireType(void) const { return m_TypeFlux; }

    // Lecture de la reference du flux de la trame
    inline S32 LireRefFlux(void) const { return m_RefFlux; }

    // Lecture de la reference de l'evenement de la trame
    inline S32 LireRefEvt(void) const { return m_RefEvt; }

    // Attacher le flux à la trame
    inline void Attacher(S32 RefFlux) { m_RefFlux = RefFlux; }

    // Lecture du nom de la trame
    void LireNom(char ** pNom) const { *pNom = m_pNom; }

    // Ajouter une donnee a une trame
    tLDBPCStatut AjouterDonnee(S32 RefTrame, S32 RefDonnee, U32 Position);

    // Lire l'adresse de la trame
    inline tAddress LireAdresse() const { return m_Adresse; }

    // Lire une trame
    tLDBPCStatut Lire(tMsg * pMsg);

    // Ecrire une trame
    tLDBPCStatut Ecrire(tMsg * pMsg);

    //	Lire la duree du temps simule de transmission de la trame
    virtual tDelay	LireDuree(void) const {return 0;}

    //	Ecrire la duree du temps simule de transmission de la trame
    virtual void	EcrireDuree(tDelay duree) {}

    // Mise à jour la reference du mode, le retard et la periode de la trame
    virtual void MajDeclencheur(S32 RefMode, tDelay Phase, tDelay Periode
                                ,tpCallBackRxWithAddr cbTrameNIC){}

    virtual void MajDeclencheur(S32 RefMode, tDelay Phase, tDelay Periode
                                , tpCallBackStatusAddr pCbTrameNIP){}

    // Emission de l'evenement pour la simulation
    virtual void EmissionEvt(void) {}

    // Preparer un message
    virtual void Preparer(tMsg * pMsg) {}

    // Produire les donnees
    virtual tLDBPCStatut Produire(void) { return cLdbpcErr;}

    // Emission spontannee
    virtual void EmissionSpontanee(void) {}

    // Reception spontanee
    virtual void ReceptionSpontanee(void) {}

    static void CallBackEvents(tpParam pParam1, tpParam pParam2);

    void OnModification(void);

    virtual void ArmerTempo() {}

    void EcrireDmdeMofication(BOOL flag) { m_FlagModif = flag; }

    BOOL LireDmdeMofication() {	return(m_FlagModif); }
};

//--------------------------------------------------------------------------
//------------------- Interface de la classe tcTrameFi --------------------
//--------------------------------------------------------------------------
// Pour les flux Inities
class tcTrameFi : public tcTrame
{
public:
    // ------------------------------------------------------------------------
    // Constructeurs
    // ------------------------------------------------------------------------
    tcTrameFi();
    tcTrameFi(tInfoBuildFrame * pBuildFrame);

    // ------------------------------------------------------------------------
    // Destructeur
    // ------------------------------------------------------------------------
    virtual ~tcTrameFi();

protected:

    tDelay	m_Duree;	// Temps simule de transmission de la trame
    tpVoid 	m_pCallBackMsgSeg;
    tpParam  m_pParamCallBackMsgSeg;

public:

    //	Lire la duree du temps simule de transmission de la trame
    virtual tDelay	LireDuree(void) const;

    //	Ecrire la duree du temps simule de transmission de la trame
    virtual void	EcrireDuree(tDelay Duree);

    // Emission de l'evenement pour la simulation
    virtual void EmissionEvt(void);
};


//--------------------------------------------------------------------------
//------------------- Interface de la classe tcTrameFni -------------------
//--------------------------------------------------------------------------
// Pour les flux Non Inities
class tcTrameFni : public tcTrame
{
public:
    // ------------------------------------------------------------------------
    // Constructeurs
    // ------------------------------------------------------------------------
    tcTrameFni();
    tcTrameFni(tInfoBuildFrame * pBuildFrame);
    // ------------------------------------------------------------------------
    // Destructeur
    // ------------------------------------------------------------------------
    virtual ~tcTrameFni();
    void FinTempo();

protected:
    S32			m_RefMode;	// Entree corespondant au mode
    tDelay			m_Phase;	// Retard de la trame
    tDelay			m_Periode;	// Periode de la trame

    typedef	void (*tpCB)(tcTrameFni*);

    tcTempoObjet<tcTrameFni*,tpCB>	m_Tempo;

    // Ecrire la reference du mode, le retard et la periode de la trame
    void EcrireDeclencheur(S32 RefMode, tDelay Phase, tDelay Periode);

    virtual void Action(void) = 0;
public:
    static void FinTempos(tcTrameFni* pTrame);
    virtual	void Initialiser();

    // Lecture de la période
    inline tDelay LirePeriode() const { return m_Periode; }

    // Lecture du mode
    void LireMode(char * mode);

    // Mise à jour la reference du mode, le retard et la periode de la trame
    virtual void MajDeclencheur(S32 RefMode, tDelay Phase, tDelay Periode
                                ,tpCallBackRxWithAddr cbTrameNIC){}
    virtual void MajDeclencheur(S32 RefMode, tDelay Phase, tDelay Periode
                                , tpCallBackStatusAddr cbTrameNIP){}
    // Preparer un message
    virtual void Preparer(tMsg * msg) {}

    // Produire les donnees
    virtual tLDBPCStatut Produire(void) {return cLdbpcErr;}

    // Emission spontannee
    virtual void EmissionSpontanee(void) {}

    // Reception spontanee
    virtual void ReceptionSpontanee(void) {}

    // Armement de la tempo
    virtual void ArmerTempo();
};

//--------------------------------------------------------------------------
//------------------- Interface de la classe tcTrameFnip ------------------
//--------------------------------------------------------------------------
// Pour les flux Non Inities Produits
class tcTrameFnip : public tcTrameFni
{
public:
    void Initialiser();
    // ------------------------------------------------------------------------
    // Constructeurs
    // ------------------------------------------------------------------------
    tcTrameFnip();
    tcTrameFnip(tInfoBuildFrame * pBuildFrame);
    // ------------------------------------------------------------------------
    // Destructeur
    // ------------------------------------------------------------------------
    virtual ~tcTrameFnip();

    // Mise à jour la reference du mode, le retard et la periode de la trame
    virtual void MajDeclencheur(S32 RefMode, tDelay Phase, tDelay Periode
                                , tpCallBackStatusAddr pCbTrameNIP);

    // Preparer un message
    virtual void Preparer(tMsg * msg);

    // Produire les donnees
    virtual tLDBPCStatut Produire(void);

    // Emmission spontannee
    virtual void EmissionSpontanee(void);
    virtual void Action(void);
private:
    U8 * m_pBufferTempFnip;
    // Fonction callback d'emission spontannee
    tpCallBackStatusAddr	m_pEmissionSp;
    tMsg m_MsgPreparee;
    // Detruire Message en cours
    void DestruireMsg();

};

//--------------------------------------------------------------------------
//------------------- Interface de la classe tcTrameFnic ------------------
//--------------------------------------------------------------------------
// Pour les flux Non Inities Consommes
class tcTrameFnic : public tcTrameFni
{
public:
    // ------------------------------------------------------------------------
    // Constructeurs
    // ------------------------------------------------------------------------
    tcTrameFnic();
    tcTrameFnic(tInfoBuildFrame * pBuildFrame);
    // ------------------------------------------------------------------------
    // Destructeur
    // ------------------------------------------------------------------------
    virtual ~tcTrameFnic();

    // Mise à jour la reference du mode, le retard et la periode de la trame
    virtual void MajDeclencheur(S32 RefMode, tDelay Phase, tDelay Periode
                                ,tpCallBackRxWithAddr pCbTrameNIC);

    // Reception spontanee
    virtual void ReceptionSpontanee(void);
    virtual void Action(void);
private:
    // Fonction callback de reception spontannee
    tpCallBackRxWithAddr		m_pReceptionSp;

};

#endif // fin de l'inclusion conditionnelle de LdbpcTra.h
