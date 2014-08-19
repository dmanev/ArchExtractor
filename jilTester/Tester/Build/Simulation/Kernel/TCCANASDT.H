// tcCanASDT.h: interface for the tcCanASDT class.
//
//////////////////////////////////////////////////////////////////////
/******************************************************************************
--------------------------------------------------------------------------------
Cette classe est la classe de base pour la gestion du Can acquitée
Pour obtenir une classe can automatiquement

  tcCanASDT* pCan=tcCanASDT::ChercheCarteCan(VitesseCan,InfoCarte,Err);;

Si vous voulez une carte bien précise (ex: carte NI)

  tcCanUUDT* pCanNI      = new tcCanNI(VitesseCan);
  tcCanUSDT* pCanNonUSDT = new tcCanNonUSDT(pCanNI);
  tcCanASDT* pCan        = new tcCanNonASDT(pCanNonUSDT);

        -----------         ----------- 
       | tcCanASDT | =0    | tcCanUSDT | =0
        -----------         ----------- 
            / \                 / \
             |                   |
             |                   |
             |                   |
             |             -------------- 1   ----------- 
             |            | tcCanNonUSDT |---| tcCanUUDT | =0
             |             --------------     ----------- 
             |                   / \               / \
             |                    |                 |
             |--------------------         --------------------...
             |                            |            |
       --------------                 ----------   ---------
      | tcCanNonASDT |               | tcCanNSI | | tcCanNI |
       --------------                 ----------   ---------

( =0: Classe abstraite )

Définition possible à la compilation:
-------------------------------------
CAN_DETECTION_CARTE           : Inclue toutes les cartes Can développé et les cherches automatiquement
CAN_REPRISE_SUR_ERREUR        : Gère la reprise sur erreur USDT, Ne peut être activé avec la tcCanNonASDT
                                 

-------------------------------------------------------------------------------

Nom et initiales des developpeurs :

         Mickaël GRANDSIRE - MG

-------------------------------------------------------------------------------

Historique du fichier tcCanASDT.h
(initiales, date, modification)

       Cree par : MG le 11/02/2002

******************************************************************************/

#if !defined(AFX_TCCANASDT_H__3393BE81_1EDB_11D6_A188_0001030A1077__INCLUDED_)
#define AFX_TCCANASDT_H__3393BE81_1EDB_11D6_A188_0001030A1077__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tcCanUSDT.h"

class tObjetCanAS2;

//---- prototype des CallBackCan ----
typedef void (*tpfCallBackCanASCon2)  (tObjetCanAS2* , void*);
typedef void (*tpfCallBackCanASInd2)  (tObjetCanAS2* , tMsgCan2* , void*);
typedef void (*tpfCallBackCanASErr)  (void*);

//---- Type des object CAN ----
class tObjetCanAS2
{
public:
    tObjetCanAS2() {
        FCallBackCon    = NULL;
        FCallBackInd    = NULL;
        pParam          = NULL;
    }

public:
    BOOL  ModeId;                       // Standard ou étendu
    U32   IdReq;                        // Id pour transmettre
    U32   IdRep;                        // Id pour recevoir

    tpfCallBackCanASCon2  FCallBackCon;      // Fin d'émission
    tpfCallBackCanASInd2  FCallBackInd;      // Réception
    void*                ParamCallBackCon;
    void*                ParamCallBackInd;

    void* pParam;                           // Utilisé par les classes dérivée pour éviter les listes
    // NE PAS CHANGER SA VALEUR!!!
};

//******************************* Classe abstraite ****************************************
class tcCanASDT
{
public:
    tcCanASDT();
    virtual ~tcCanASDT();

public:
    // Création et fermeture de sessions
    virtual BOOL CreerObjet(tObjetCanAS2* pObjetCan)=0;
    virtual BOOL CreerObjet(tObjetCanUS2* pObjetCan)=0;
    virtual BOOL CreerObjet(tObjetCanUU2* pObjetCan)=0;
    virtual BOOL DetruireObjet(tObjetCanAS2* pObjetCan)=0;
    virtual BOOL DetruireObjet(tObjetCanUS2* pObjetCan)=0;
    virtual BOOL DetruireObjet(tObjetCanUU2* pObjetCan)=0;

    // Emission de trames
    virtual BOOL Req(tObjetCanAS2* pObjetCan,tMsgCan2* pMsg)=0;
    virtual BOOL Req(tObjetCanUS2* pObjetCan,tMsgCan2* pMsg)=0;
    virtual BOOL Req(tObjetCanUU2* pObjetCan,tTrameCan2* pTrame,U8 Envoi=cEnvoiUUImmediat)=0;
    virtual BOOL ActiverReqPeriodique(tObjetCanUU2* pObjetCan,BOOL Active=cTrue)=0;

    // Configuration des paramêtres USDT
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

    // Pour lire les erreurs notifiées et les envoyer
    char* GetErreur() {return m_Erreur;};
    void  SetCallBackErr(tpfCallBackCanASErr pCallBack,void* pParam);

    // Cherche une carte Can automatiquement si CAN_DETECTION_CARTE défini
#ifdef CAN_DETECTION_CARTE
    static tcCanASDT* ChercheCarteCan(tcTimerCan* pTimerCan,U32 VitesseCan,CString& InfoCarte,CString& Err);
#endif

protected:
    void SetErreur(char* Erreur);

private:
    char*                 m_Erreur;
    tpfCallBackCanASErr   m_FCallBackErr;
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

#endif // !defined(AFX_TCCANASDT_H__3393BE81_1EDB_11D6_A188_0001030A1077__INCLUDED_)
