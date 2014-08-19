// tcCanUUDT.h: interface for the tcCanUUDT class.
//
//////////////////////////////////////////////////////////////////////
/******************************************************************************
--------------------------------------------------------------------------------
Cette classe est la classe de base pour la gestion du Can
Pour obtenir une classe can automatiquement

  tcCanUUDT* pCan=tcCanUUDT::ChercheCarteCan(VitesseCan,InfoCarte,Err);;

Si vous voulez une carte bien précise (ex: carte NI)

  tcCanUUDT* pCan= new tcCanNI(VitesseCan);

               ----------- 
              | tcCanUUDT | = 0 Classe abstraite
               ----------- 
                   / \
                    |
            --------------------...
           |            |
       -----------   ---------
      |tcCanVector| | tcCanNI |
       -----------   ---------

-------------------------------------------------------------------------------

Nom et initiales des developpeurs :

         Mickaël GRANDSIRE - MG

-------------------------------------------------------------------------------

Historique du fichier tcCanUUDT.h
(initiales, date, modification)

       Cree par : MG le 05/08/2001

******************************************************************************/

#if !defined(AFX_TCCANUUDT_H__8C765311_8B0C_11D5_BB10_000103175320__INCLUDED_)
#define AFX_TCCANUUDT_H__8C765311_8B0C_11D5_BB10_000103175320__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DefTypes.h"
#include "tcTimerCan.h"
#include "afxmt.h"          // pour le Mutex

#ifndef DISABLE_SAD
  #include "tcSADAdrFrame.h"
#endif

//---- Définition des cartes can ----
#define cCarteMskConstructeur   0xF0
#define cCarteMskPort           0x0F

#define cCarteNI_Port0          0x10
#define cCarteNI_Port1          0x11
#define cCarteVector_Port0      0x20
#define cCarteVector_Port1      0x21
#define cCarteNsi_Port0         0x30
#define cCarteNsi_Port1         0x31
#define cCarteJCI_Port0        0x40
#define cCarteJCI_Port1        0x41
#define cCarteAixia_Com1        0x50
#define cCarteAixia_Com2        0x51

#define cCarteIndefini          0x00
#define cCarteTest              0x01
#define cCarte1                 cCarteNI_Port0

#define cCarteMaxPort           0x01
#define cCarteIncConstructeur   0x10
#define cCarteIncPort           0x01

//---- Définition de constante diverse ----
#define cLongueurMaxTrameCan                8

#define cTypeComUUReception                 0
#define cTypeComUUReceptionRemote           1
#define cTypeComUUTransmissionPeriodique    2
#define cTypeComUUTransmissionRemote        3
#define cTypeComUUTransmission              4

#define cModeIdStandard                     0
#define cModeIdEtendu                       1

#define cEnvoiUUImmediat                    0
#define cEnvoiUUDiffere                     1

#define cPasPeriodiqueUUDT                  5    // Pas de périodicité de 5ms
#define cOffsetPeriodiqueMax                (10*cPasPeriodiqueUUDT)
#define cMaxFrameNumber                     50

#define cFlagXTDFrame                       0x80000000
#define cFlagSTDFrame                       0x00000000
#define cMaskId29Bits                       0x1FFFFFFF
#define cMaskId11Bits                       0x000007FF

//---- Type des trames CAN ----
typedef struct
{
    U8  Longueur;			                // Longueur de la trame
    U8  Buffer[cLongueurMaxTrameCan];	// Contenu de la trame
} tTrameCan2;

//---- Type des filtrages CAN en reception ----
#define cInvalidBaudrate         0xFFFFFFFF
#define cInvalidPort             0xFF
class tcParamCan2
{
public:
    tcParamCan2();     // Initialise par défaut plusieurs constantes

public:
    BOOL  m_bReset;      // Reset ou non la recherche de carte
    U32   m_BaudRate;
    U8    m_Port;
    U8    m_QueueRead;
    U8    m_QueueWrite;

    U32   m_CodeStd;
    U32   m_MaskStd;
    U32   m_CodeXtd;
    U32   m_MaskXtd;
};

class tObjetCanUU2;

//---- prototype des CallBackCan ----
typedef void (*tpfCallBackCanUUCon2)  (tObjetCanUU2*,void*);
typedef void (*tpfCallBackCanUUInd2)  (tObjetCanUU2*, tTrameCan2*,void*);
typedef void (*tpfCallBackCanUUErr)  (void*);

//---- Type des object CAN ----
class tObjetCanUU2
{
public:
    tObjetCanUU2() {
        FCallBackCon    = NULL;
        FCallBackInd    = NULL;
    }

public:
    BOOL  ModeId;                     // Standard ou étendu
    U32   Id;
    U8    TypeDeCommunication;        // - Reception
    // - Reception Remote           (Recoit automatiquement après une transmission)
    // - Transmission périodique
    // - Transmission Remote        (Emet automatiquement après une reception)
    // - Transmission
    U32   Periode;                    // Periode si TypeDeCommunication periodique (en ms)

    tpfCallBackCanUUCon2  FCallBackCon;         // Fin d'émission
    tpfCallBackCanUUInd2  FCallBackInd;         // Réception
    void*                ParamCallBackCon;
    void*                ParamCallBackInd;

    void* pParam;                         // Utilisé par les classes dérivée pour éviter les listes
    // NE PAS CHANGER SA VALEUR!!!
};

//******************************* Classe abstraite ****************************************
class tcCanUUDT
{
    typedef struct
    {
        DWORD         DateProchainEnvoi;      // Date du prochain envoi de Msg
        BOOL      ReqPeriodique;          // Transmission périodique activée ou non
        tTrameCan2     Trame;                  // Message à envoyer périodiquement ou en remote
        tObjetCanUU2*  pObjetCanUU;
    } tObjetCanUUPeriodique;

    typedef struct
    {
        tObjetCanUU2*  pObjetCanUU;            // Objet envoyant le message
        tTrameCan2     Trame;                  // Message à envoyer
    } tTrameCanReq;

public:
    tcCanUUDT(tcTimerCan* pTimerCan);
    virtual ~tcCanUUDT();

public:
    // Création et fermeture de sessions
    virtual BOOL CreerObjet(tObjetCanUU2* pObjetCan);
    virtual BOOL DetruireObjet(tObjetCanUU2* pObjetCan);

    // Emission de messages
    virtual BOOL Req(tObjetCanUU2* pObjetCan,tTrameCan2* pTrameCan,U8 Envoi=cEnvoiUUImmediat);
    virtual BOOL ActiverReqPeriodique(tObjetCanUU2* pObjetCan,BOOL Active=cTrue);

    // Emission de trames
    virtual BOOL ReqTrame(tObjetCanUU2* pObjetCan,tTrameCan2* pTrameCan);

    // Pour lire les erreurs notifiées et les envoyer
    char* GetErreur() {return m_Erreur;};
    void SetCallBackErr(tpfCallBackCanUUErr pCallBack,void* pParam);

    // Cherche une carte Can automatiquement si CAN_DETECTION_CARTE défini
#ifdef CAN_DETECTION_CARTE
    static tcCanUUDT* ChercheCarteCan(tcTimerCan* pTimerCan,U32 VitesseCan,CString& InfoCarte,CString& Err,int NumCarte=cCarteIndefini,BOOL bReset = cFalse);
    static tcCanUUDT* ChercheCarteCan(tcTimerCan* pTimerCan,tcParamCan2* pParamCan,CString& InfoCarte,CString& Err,int NumCarte=cCarteIndefini);
#endif

    tcTimerCan* GetTimerCan() {return m_pTimerCan;}

protected:
    // Emission de trames
    virtual BOOL ReqTrameUU(tObjetCanUU2* pObjetCan,tTrameCan2* pTrameCan)=0;

protected:
    BOOL m_InitOk;
    BOOL m_CartePresente;

    CPtrArray   m_lstObjetCanUU;	// Liste de tout les objet CAN crée
    CMutex      m_Mutex;

    int         m_OffsetPeriodique;  // Pour ne pas envoyer toutes les trames en même temps

    //--- Donnée et fonction assurant l'émission périodique ---
protected:
    static void CallBackPeriodique(void* Param);

protected:
    void SetErreur(const char* Erreur);

protected:
    tcTimerCan*           m_pTimerCan;
    int                   m_NumeroTempo;

private:
    char*                 m_Erreur;

    tpfCallBackCanUUErr   m_FCallBackErr;
    void*                 m_ParamCallBackErr;

    CPtrArray             m_lstObjetCanUUPeriodique;	// Liste des objetCan périodique

    CMutex                m_MutexPeriodique;

//    CPtrArray             m_lstTramesReq;	            // Liste des trames à envoyer
//    CMutex                m_MutexTramesReq;
//    HANDLE                m_hEventReq;

//    static DWORD WINAPI CorpsThreadReq( LPVOID Param );  // Thread se chargeant des réceptions
//    BOOL  m_Arret;
//    U32   m_ThreadID;
//    HANDLE    m_hThread;
    static int m_Carte1;    // Mémorisation de la 1ère carte pour ne pas reprendre la même

    //----- ScanAll link -----
#ifndef DISABLE_SAD
public:
    CString SADGetName() {return m_SADName;}
protected:
    tcSADAdrFrame m_SADAdrFrame;
    CString       m_SADName;
#endif
    //------------------------
};

#endif // !defined(AFX_TCCANUUDT_H__8C765311_8B0C_11D5_BB10_000103175320__INCLUDED_)

