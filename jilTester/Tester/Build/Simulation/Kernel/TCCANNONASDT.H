// tcCanNonASDT.h: interface for the tcCanNonASDT class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCCANNONASDT_H__3393BE83_1EDB_11D6_A188_0001030A1077__INCLUDED_)
#define AFX_TCCANNONASDT_H__3393BE83_1EDB_11D6_A188_0001030A1077__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tcCanASDT.h"
#include "tcCanNonUSDT.h"

//------ Constante du PCI (Protocol Control Information) -----
#define cPciAK			      0x74

//------ Constante des états finis -----
#define cEtatAttenteConAK             20
#define cEtatAttenteIndAK             21
// Attention numéro limité à 29 car états suivants pris par les couches supérieures

class tcCanNonASDT :
            public tcCanASDT,
            public tcCanNonUSDT
{
public: 
    //---- Structure pour la correspondance ObjetCanAS<->ObjetCanUS ----
    typedef struct
    {
        tObjetCanAS2*      pObjetCanAS;
        tObjetCanUS2       ObjetCanUS;

        void*             pParam;             // Utilisé par les classes dérivée pour éviter les listes
        // NE PAS CHANGER SA VALEUR!!!
    } tObjetCanNonASDT;

    tcCanNonASDT(tcTimerCan* pTimerCan,tcCanUUDT* pCanUUDT);
    virtual ~tcCanNonASDT();

    // Création et fermeture de sessions
    virtual BOOL CreerObjet(tObjetCanAS2* pObjetCan);
    virtual BOOL CreerObjet(tObjetCanUS2* pObjetCan) {return tcCanNonUSDT::CreerObjet(pObjetCan);}
    virtual BOOL CreerObjet(tObjetCanUU2* pObjetCan) {return tcCanNonUSDT::CreerObjet(pObjetCan);}
    virtual BOOL DetruireObjet(tObjetCanAS2* pObjetCan);
    virtual BOOL DetruireObjet(tObjetCanUS2* pObjetCan) {return tcCanNonUSDT::DetruireObjet(pObjetCan);}
    virtual BOOL DetruireObjet(tObjetCanUU2* pObjetCan) {return tcCanNonUSDT::DetruireObjet(pObjetCan);}

    // Emission de trames
    virtual BOOL Req(tObjetCanAS2* pObjetCan,tMsgCan2* pMsg);
    virtual BOOL Req(tObjetCanUS2* pObjetCan,tMsgCan2* pMsg) {return tcCanNonUSDT::Req(pObjetCan,pMsg);}
    virtual BOOL Req(tObjetCanUU2* pObjetCan,tTrameCan2* pTrame,U8 Envoi=cEnvoiUUImmediat)  {return tcCanNonUSDT::Req(pObjetCan,pTrame,Envoi);}
    virtual BOOL ActiverReqPeriodique(tObjetCanUU2* pObjetCan,BOOL Active=cTrue) {return tcCanNonUSDT::ActiverReqPeriodique(pObjetCan,Active);}

    // Configuration des paramêtre USDT
    virtual void SetPciFC_BS(U8 PciFC_BS)         {tcCanNonUSDT::SetPciFC_BS(PciFC_BS);         }
    virtual void SetPciFC_STmin(U8 PciFC_STmin)   {tcCanNonUSDT::SetPciFC_STmin(PciFC_STmin);   }
    virtual void SetPciFC_FS(U8 PciFC_FS)         {tcCanNonUSDT::SetPciFC_FS(PciFC_FS);         }
    virtual void SetPciFC_WFTmax(U8 PciFC_WFTmax) {tcCanNonUSDT::SetPciFC_WFTmax(PciFC_WFTmax); }
    virtual void SetCanNoPadding(BOOL CanNoPadding)	{tcCanNonUSDT::SetCanNoPadding(CanNoPadding);}

    virtual U8 GetPciFC_BS()      {return tcCanNonUSDT::GetPciFC_BS();     }
    virtual U8 GetPciFC_STmin()   {return tcCanNonUSDT::GetPciFC_STmin();  }
    virtual U8 GetPciFC_FS()      {return tcCanNonUSDT::GetPciFC_FS();     }
    virtual U8 GetPciFC_WFTmax()  {return tcCanNonUSDT::GetPciFC_WFTmax(); }
    virtual BOOL GetCanNoPadding(){return tcCanNonUSDT::GetCanNoPadding(); }

protected:
    virtual BOOL CreerObjet(tObjetCanNonUSDT* pObjetCanNonUSDT);

    static void CallBackErr(void* pParam);

    static void CallBackCon(tObjetCanUU2* pObjetCanUU, void* pParam);
    static void CallBackInd(tObjetCanUU2* pObjetCanUU, tTrameCan2* pTrameCan, void* pParam);

    static void CallBackConUS(tObjetCanUS2* pObjetCanUS, void* pParam);
    static void CallBackIndUS(tObjetCanUS2* pObjetCanUS, tMsgCan2* pMsgCan, void* pParam);

    virtual void GereErreurUSDT(tErreurUSDT TypeErreur,tObjetCanNonUSDT* pObjetCanNonUSDT,tTrameCan2* pTrameCan=NULL);  // Gère les erreurs rencontrées

    //--- fonction assurant l'émission décalée dans le temps et la gestion des TimeOut ---
    static void CallBackTempoPeriodique(void* Param);

    virtual void RepAK(tObjetCanNonUSDT* pObjetCanNonUSDT);
    virtual void ReqAK(tObjetCanNonUSDT* pObjetCanNonUSDT);

    //----- ScanAll link -----
#ifndef DISABLE_SAD
protected:
    int         m_SADObjectNumber;
#endif
    //------------------------
};

#endif // !defined(AFX_TCCANNONASDT_H__3393BE83_1EDB_11D6_A188_0001030A1077__INCLUDED_)
