// tcCanNonUSDT.h: interface for the tcCanNonUSDT class.
//
//////////////////////////////////////////////////////////////////////
/******************************************************************************
--------------------------------------------------------------------------------
Cette classe est la classe de base pour la gestion du Can en USDT avec les cartes UUDT

Pour obtenir un pointeur sur une carte NI par exemple:

  tcCanUUDT* pCanNI= new tcCanNI(VitesseCan);
  tcCanUUDT* pCan= new tcCanNonUSDT(pCanNI);

               ----------- 
              | tcCanUSDT | =0
               ----------- 
                   / \
                    |
             ---------------
            |               |
     ------------   -------------- 1   ----------- 
    | tcCanJCI | | tcCanNonUSDT |---| tcCanUUDT | =0
     ------------   --------------     ----------- 
                                           / \
                                            |
                                    --------------------...
                                   |            |
                               ----------   ---------
                              | tcCanNSI | | tcCanNI |
                               ----------   ---------
( =0: Classe abstraite )

-------------------------------------------------------------------------------

Nom et initiales des developpeurs :

         Mickaël GRANDSIRE - MG

-------------------------------------------------------------------------------

Historique du fichier dat_ser.c
(initiales, date, modification)

       Cree par : MG le 05/08/2001

******************************************************************************/

#if !defined(AFX_TCCANNONUSDT_H__8C765313_8B0C_11D5_BB10_000103175320__INCLUDED_)
#define AFX_TCCANNONUSDT_H__8C765313_8B0C_11D5_BB10_000103175320__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tcCanUSDT.h"
#include "tcTimerCan.h"
#include "tcCanUUDT.h"
#include "afxmt.h"          // pour le Mutex

//------ Constante des états finis -----
#define cEtatAttenteInd               0
#define cEtatAttenteConCF             1
#define cEtatAttenteConCFPourFC       2
#define cEtatAttenteConDerniereCF     3
#define cEtatAttenteEnvoiCF           4
#define cEtatAttenteIndCF             5
#define cEtatAttenteConFC             6
#define cEtatAttenteIndFC             7
#define cEtatAttenteEnvoiFC           8
#define cEtatAttenteConFF             9
#define cEtatAttenteConSF             10
// Attention numéro limité à 19 car états suivants pris par les couches supérieures

//------ Constante du PCI (Protocol Control Information) -----
#define cPciSF			      0x00
#define cPciFF			      0x10
#define cPciCF	    		  0x20
#define cPciFC			      0x30

#define cPciMskCde        0xF0
#define cPciPosCde        0

#define cPciSFMskLng      0x07    // Masque de longueur d'une SF
#define cPciSFPosLng      0       // Masque de longueur d'une SF
#define cPciSFPosData     1       // Début des data dans une SF
#define cPciSFLngData     7       // Longueur max des data d'une SF

#define cPciFFMskLng      0x0FFF  // Masque de longueur d'une FF
#define cPciFFPosLng1     0       // Début de longueur dans une FF   MSB
#define cPciFFPosLng2     1       // Début de longueur dans une FF   LSB
#define cPciFFPosData     2       // Début des data dans une FF
#define cPciFFLngData     6       // Longueur des data dans une FF 

#define cPciCFMskSN       0x0F    // Masque de numéro de bloc d'une CF
#define cPciCFPosSN       0       // Numéro de blocs dans une CF
#define cPciCFPosData     1       // Début des data dans une CF
#define cPciCFLngData     7       // Longueur des data dans une CF 

//---- Type du message Flow control ----
#define cPciFC_STwait     200     // Temps minimum entre les FC Wait

#define cPciFC_FS_CTS     0       // Prêt à recevoir les données
#define cPciFC_FS_WT      1       // Attendre j'usqu'au prochain FC_CTS
#define cPciFCMskFS       0x0F    // Masque de position du FS
#define cPciFCPosFS       0       // Position du FS
#define cPciFCPosBS       1       // Position du BS 
#define cPciFCPosSTmin    2       // Position su STmin

//---- TimeOut de réception ----
#define cPciTimeOutN_As   200     // Emission  UUDT en emetteur  USDT (Sender)
#define cPciTimeOutN_Ar   200     // Emission  UUDT en recepteur USDT
#define cPciTimeOutN_Bs   900     // Reception FC   en emetteur  USDT (Sender)
#define cPciTimeOutN_Cr   1000    // Reception CF   en recepteur USDT

//------ Constante initialisé par défaut ----
#define cPciOctetDeRemplissage  0xC2    // Octet de remplissage des trames

#define cPciFC_WFTmax     4             // Maximum de requète wait autorisée
#define cPciFC_BS         3             // Nombre maximum de bloc pouvant être reçu consécutivement
#define cPciFC_STmin      0             // Temps minimum entre les CF
#define cPciFC_FS         cPciFC_FS_CTS // Etat FC au départ

#define cPasEmissionDecalleNonUSDT    5 // Pas de périodicité de 5ms

#ifdef CAN_REPRISE_SUR_ERREUR           // Si reprise sur erreur activé
#define cReemissionMax    2             // Nombre de réémission maximum en cas d'échec
#endif


typedef enum
{
    cErrTimeOutReq,
    cErrTimeOutRep,
    cErrPci,
    cErrBS,
    cErrWFTmax,
    cErrEtatCon,
    cErrEtatInd,
    cErrEtatTimeOut,
} tErreurUSDT;

class tcCanNonUSDT : public tcCanUSDT
{
public:
    //------ Structure d'un message segmenté -----
    typedef struct
    {
        tMsgCan2   MsgCan;
        U16   PosBuffer;					// Position dans le buffer du MsgCan
        U8	  Etat;								// Etat du message
        U8    FC_FS;              // Type de controle de flux
        U8    FC_FS_WT;           // Nombre de Wait reçu
        U8    FC_BS;					    // Nombre de bloc Maximum
        U8    FC_STmin;           // Temps entre les CF
        U8    CF_SN;			        // Numéro du bloc en cours
        U8    NB_Reemission;	    // Nombre de reemission si echec
        DWORD     DateEvt;            // Date du dernier évenement
    } tMsgCanSeg;

    //---- Structure pour la correspondance ObjetCanUS<->ObjetCanUU ----
    typedef struct
    {
        tObjetCanUS2*  pObjetCanUS;
        tObjetCanUU2   ObjetCanUUReq;
        tObjetCanUU2   ObjetCanUURep;
        tMsgCanSeg    MsgCanSeg;				                    // Messages segmenté en constitution
        U8        MsgCanSegBuffer[cLongueurMaxMsgCan];  // et son buffer max
        DWORD         DateEnvoi;                            // Date du dernier envoi de trame
        DWORD         DateProchainEnvoi;                    // Date du prochain envoi de Msg

        void*         pParam;                               // Utilisé par les classes dérivée pour éviter les listes
        // NE PAS CHANGER SA VALEUR!!!
    } tObjetCanNonUSDT;

    tcCanNonUSDT(tcTimerCan* pTimerCan,tcCanUUDT* pCanUUDT);
    virtual ~tcCanNonUSDT();

    // Création et fermeture de sessions US
    virtual BOOL CreerObjet(tObjetCanUS2* pObjetCan);
    virtual BOOL CreerObjet(tObjetCanUU2* pObjetCan) {return m_pCanUUDT->CreerObjet(pObjetCan);};
    virtual BOOL DetruireObjet(tObjetCanUS2* pObjetCan);
    virtual BOOL DetruireObjet(tObjetCanUU2* pObjetCan) {return m_pCanUUDT->DetruireObjet(pObjetCan);};

    // Emission de trames
    virtual BOOL Req(tObjetCanUS2* pObjetCan,tMsgCan2* pMsg);
    virtual BOOL Req(tObjetCanUU2* pObjetCan,tTrameCan2* pTrameCan,U8 Envoi=cEnvoiUUImmediat) {return m_pCanUUDT->Req(pObjetCan,pTrameCan,Envoi);};
    virtual BOOL ActiverReqPeriodique(tObjetCanUU2* pObjetCan,BOOL Active=cTrue) {return m_pCanUUDT->ActiverReqPeriodique(pObjetCan,Active);};

    // Configuration des paramêtre USDT
    virtual void SetPciFC_BS(U8 PciFC_BS)         {m_PciFC_BS     = PciFC_BS;    }
    virtual void SetPciFC_STmin(U8 PciFC_STmin)   {m_PciFC_STmin  = PciFC_STmin; }
    virtual void SetPciFC_FS(U8 PciFC_FS)         {m_PciFC_FS     = PciFC_FS;    }
    virtual void SetPciFC_WFTmax(U8 PciFC_WFTmax) {m_PciFC_WFTmax = PciFC_WFTmax;}
    virtual void SetCanNoPadding(BOOL CanNoPadding)	{m_CanNoPadding = CanNoPadding;	};

    virtual U8 GetPciFC_BS()      {return m_PciFC_BS;     }
    virtual U8 GetPciFC_STmin()   {return m_PciFC_STmin;  }
    virtual U8 GetPciFC_FS()      {return m_PciFC_FS;     }
    virtual U8 GetPciFC_WFTmax()  {return m_PciFC_WFTmax; }
    virtual BOOL GetCanNoPadding(){return m_CanNoPadding; }

    // Cherche une carte Can automatiquement si CAN_DETECTION_CARTE défini
#ifdef CAN_DETECTION_CARTE
    static tcCanUSDT* ChercheCarteCan(tcTimerCan* pTimerCan,U32 VitesseCan,CString& InfoCarte,CString& Err, BOOL bReset = cFalse);
#endif

protected:
    virtual BOOL CreerObjet(tObjetCanNonUSDT* pObjetCanNonUSDT);

    static void CallBackErr(void* pParam);

    static void CallBackCon(tObjetCanUU2* pObjetCanUU, void* pParam);
    static void CallBackInd(tObjetCanUU2* pObjetCanUU, tTrameCan2* pTrameCan, void* pParam);

    // Traite le 1er msg en envoi pour démarrer la routine
    virtual void TraiteMsgCanSegCon(tObjetCanNonUSDT* pObjetCanNonUSDT);
    virtual void TraiteMsgCanSegInd(tObjetCanNonUSDT* pObjetCanNonUSDT,tTrameCan2* pTrameCan);

    // Transmet ou reçoit les trames Can PCI
    virtual void RepSF(tObjetCanNonUSDT* pObjetCanNonUSDT,tTrameCan2* pTrameCan);
    virtual void RepFF(tObjetCanNonUSDT* pObjetCanNonUSDT,tTrameCan2* pTrameCan);
    virtual void RepCF(tObjetCanNonUSDT* pObjetCanNonUSDT,tTrameCan2* pTrameCan);
    virtual void RepFC(tObjetCanNonUSDT* pObjetCanNonUSDT,tTrameCan2* pTrameCan);

    virtual void ReqSF(tObjetCanNonUSDT* pObjetCanNonUSDT);
    virtual void ReqFF(tObjetCanNonUSDT* pObjetCanNonUSDT);
    virtual void ReqCF(tObjetCanNonUSDT* pObjetCanNonUSDT);
    virtual void ReqFC(tObjetCanNonUSDT* pObjetCanNonUSDT);

    virtual void Req(tObjetCanNonUSDT* pObjetCanNonUSDT);

    virtual void GereErreurUSDT(tErreurUSDT TypeErreur,tObjetCanNonUSDT* pObjetCanNonUSDT,tTrameCan2* pTrameCan=NULL);  // Gère les erreurs rencontrées
    virtual void InitialiseEtats(tObjetCanNonUSDT* pObjetCanNonUSDT);
    virtual void RepriseSurErreur(tObjetCanNonUSDT* pObjetCanNonUSDT);

    //--- Donnée et fonction assurant l'émission décalée dans le temps et la gestion des TimeOut ---
    static void CallBackTempoPeriodique(void* Param);
    void TraiteTempoPeriodique();
    tcTimerCan* GetTimerCan() {return m_pTimerCan;}

protected:
    U8  m_PciFC_BS;
    U8  m_PciFC_STmin;
    U8  m_PciFC_FS;
    U8  m_PciFC_WFTmax;
    BOOL m_CanNoPadding;

    CPtrArray   m_lstObjetCanNonUSDT;	      // Liste de tout les ObjetCanNonUSDT
    CMutex      m_Mutex;                    // Mutex pour accéder à la liste

    int         m_NumeroTempo;
    tcTimerCan* m_pTimerCan;

    tcCanUUDT*  m_pCanUUDT;                 // Pointeur sur la classe UUDT

    //----- ScanAll link -----
#ifndef DISABLE_SAD
protected:
    int         m_SADObjectNumber;
#endif
    //------------------------
};

#endif // !defined(AFX_TCCANNONUSDT_H__8C765313_8B0C_11D5_BB10_000103175320__INCLUDED_)
