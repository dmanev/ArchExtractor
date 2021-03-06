// tcCanUSDT.h: interface for the tcCanUSDT class.
//
//////////////////////////////////////////////////////////////////////
/******************************************************************************
--------------------------------------------------------------------------------
Cette classe est la classe de base pour la gestion du Can
Pour obtenir une classe can automatiquement

  tcCanUSDT* pCan=tcCanUSDT::ChercheCarteCan(VitesseCan,InfoCarte,Err);;

Si vous voulez une carte bien pr�cise (ex: carte NI)

  tcCanUUDT* pCanNI= new tcCanNI(VitesseCan);
  tcCanUSDT* pCan= new tcCanNonUSDT(pCanNI);

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

D�finition possible � la compilation:
-------------------------------------
CAN_DETECTION_CARTE           : Inclue toutes les cartes Can d�velopp� et les cherches automatiquement
CAN_REPRISE_SUR_ERREUR        : G�re la reprise sur erreur USDT

-------------------------------------------------------------------------------

Nom et initiales des developpeurs :

         Micka�l GRANDSIRE - MG

-------------------------------------------------------------------------------

Historique du fichier tcCanUSDT.h
(initiales, date, modification)

       Cree par : MG le 05/08/2001

******************************************************************************/

#if !defined(AFX_TCCANUSDT_H__8C765312_8B0C_11D5_BB10_000103175320__INCLUDED_)
#define AFX_TCCANUSDT_H__8C765312_8B0C_11D5_BB10_000103175320__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DefTypes.h"
#include "tcCanUUDT.h"
#include "tcSADDoubleAdrFrame.h"

//---- D�finition de constante diverse ----
#define cLongueurMaxMsgCan                4095

#define cModeIdStandard                     0
#define cModeIdEtendu                       1

//---- Type des trames CAN ----
typedef struct
{
    U16 Longueur;			                // Longueur du message
    U8* Buffer;		                    // Contenu du message
} tMsgCan2;

class tObjetCanUS2;

//---- prototype des CallBackCan ----
typedef void (*tpfCallBackCanUSCon2)  (tObjetCanUS2* , void*);
typedef void (*tpfCallBackCanUSInd2)  (tObjetCanUS2* , tMsgCan2* , void*);
typedef void (*tpfCallBackCanUSErr)  (void*);

//---- Type des object CAN ----
class tObjetCanUS2
{
public:
    tObjetCanUS2() {
        FCallBackCon    = NULL;
        FCallBackInd    = NULL;
        pParam          = NULL;
    }

public:
    BOOL  ModeId;                       // Standard ou �tendu
    U32   IdReq;                        // Id pour transmettre
    U32   IdRep;                        // Id pour recevoir

    tpfCallBackCanUSCon2  FCallBackCon;     // Fin d'�mission
    tpfCallBackCanUSInd2  FCallBackInd;      // R�ception
    void*                ParamCallBackCon;
    void*                ParamCallBackInd;

    void* pParam;                           // Utilis� par les classes d�riv�e pour �viter les listes
    // NE PAS CHANGER SA VALEUR!!!
};

//******************************* Classe abstraite ****************************************
class tcCanUSDT
{
public:
    tcCanUSDT();
    virtual ~tcCanUSDT();

public:
    // Cr�ation et fermeture de sessions
    virtual BOOL CreerObjet(tObjetCanUS2* pObjetCan)=0;
    virtual BOOL CreerObjet(tObjetCanUU2* pObjetCan)=0;
    virtual BOOL DetruireObjet(tObjetCanUS2* pObjetCan)=0;
    virtual BOOL DetruireObjet(tObjetCanUU2* pObjetCan)=0;

    // Emission de trames
    virtual BOOL Req(tObjetCanUS2* pObjetCan,tMsgCan2* pMsg)=0;
    virtual BOOL Req(tObjetCanUU2* pObjetCan,tTrameCan2* pTrame,U8 Envoi=cEnvoiUUImmediat)=0;
    virtual BOOL ActiverReqPeriodique(tObjetCanUU2* pObjetCan,BOOL Active=cTrue)=0;

    // Configuration des param�tres USDT
    virtual void SetPciFC_BS(U8 PciFC_BS)         = 0;
    virtual void SetPciFC_STmin(U8 PciFC_STmin)   = 0;
    virtual void SetPciFC_FS(U8 PciFC_FS)         = 0;
    virtual void SetPciFC_WFTmax(U8 PciFC_WFTmax) = 0;
    virtual void SetCanNoPadding(BOOL CanNoPadding) = 0;

    virtual U8 GetPciFC_BS()      = 0;
    virtual U8 GetPciFC_STmin()   = 0;
    virtual U8 GetPciFC_FS()      = 0;
    virtual U8 GetPciFC_WFTmax()  = 0;
    virtual BOOL GetCanNoPadding() = 0;

    // Pour lire les erreurs notifi�es et les envoyer
    char* GetErreur() {return m_Erreur;};
    void SetCallBackErr(tpfCallBackCanUSErr pCallBack,void* pParam);

    // Cherche une carte Can automatiquement si CAN_DETECTION_CARTE d�fini
#ifdef CAN_DETECTION_CARTE
    static tcCanUSDT* ChercheCarteCan(tcTimerCan* pTimerCan,U32 VitesseCan,CString& InfoCarte,CString& Err, BOOL bReset = cFalse);
#endif

protected:
    void SetErreur(char* Erreur);

protected:
    BOOL m_CartePresente;

private:
    char*                 m_Erreur;
    tpfCallBackCanUSErr   m_FCallBackErr;
    void*                 m_ParamCallBackErr;

    //----- ScanAll link -----
#ifndef DISABLE_SAD
public:
    CString SADGetName() {return m_SADName;}
protected:
    tcSADDoubleAdrFrame m_SADDoubleAdrFrame;
    CString             m_SADName;
#endif
    //------------------------
};

#endif // !defined(AFX_TCCANUSDT_H__8C765312_8B0C_11D5_BB10_000103175320__INCLUDED_)
