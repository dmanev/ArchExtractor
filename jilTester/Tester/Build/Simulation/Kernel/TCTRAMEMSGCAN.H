// tcTrameMsgCan.h: interface for the tcTrameMsgCan class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCTRAMEMSGCAN_H__A02B3C02_9B7E_11D5_BB22_000103175320__INCLUDED_)
#define AFX_TCTRAMEMSGCAN_H__A02B3C02_9B7E_11D5_BB22_000103175320__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Ldbpc.h"			// Definition les types et constantes de bases
#include "LdbpcTem.h"
#include "tcCanSession.h"
#include "tcCanECar.h"

class tcTrameMsgCan
{
public:
    tcTrameMsgCan(tcCanSession* pCanSession,tcCanECar* pCanECar,tParamMsgSeg* pParamMsgSeg,S32 RefCan);
    virtual ~tcTrameMsgCan();

protected:

    // CallBack de réception de l'appli pour la DLL en USDT
    static void CallBackInd(tObjetCanUS2* pObjetCanUS, tMsgCan2* pMsgCan,void* pParam);
    // CallBack de confirmation d'emission USDT pour la DLL
    static void CallBackCon(tObjetCanUS2* pObjetCanUS,void* pParam);
    // CallBack de réception de la DLL pour l'appli en USDT
    static void CallBackRxEvents(tpParam ,tpParam );
    // CallBack d'émission de l'appli pour la DLL en UUDT
    static void CallBackTxEvents(tpParam ,tpParam );

public:
    void ReqAppli(tTrameCan2* pTrameCan);

    // CallBack de réception de l'appli
    tpCallBackRxWithAddr   m_pCallBackRxAppli;

    tcCanSession* m_pCanSession;          // Port Can d'emission et de réception US
    tcCanECar* m_pCanECar;          // Port Can d'emission et de réception UU

    // ObjetCanUS
    tObjetCanUS2 m_ObjetCanUS;

    // Paramêtre pour la DLL
    char   m_pNom[MAX_STRING];
    S32 m_RefFluxIP;		// Reference du flux initié produit
    S32 m_RefFluxNIC;		// Reference du flux non initié consommé

    U16 m_TailleMax;  	// Taille Max du message en octet

    //-----------------------------------------------------------------
    // Message émis par l'application et reçu par les outils E-Car :
    //-----------------------------------------------------------------
    // NomDeMessageTxBuffer : Contenu du message
    S32 m_RefTxBuffer;
    // NomDeMessageTxLng 	  : Taille du message
    S32 m_RefTxLng;
    // NomDeMessageTxIndEvt : Signalisation du message
    S32 m_RefTxIndEvt;

    //-----------------------------------------------------------------
    // Message émis par les outils E-Car et reçu par l'application :
    //-----------------------------------------------------------------
    // NomDeMessageRxBuffer	: Contenu du message
    S32 m_RefRxBuffer;
    // NomDeMessageRxLng 	  : Taille du message
    S32 m_RefRxLng;
    // NomDeMessageRxIndEvt	: Signalisation du message
    S32 m_RefRxIndEvt;
    // NomDeMessageRxConEvt : Confirmation du message
    S32 m_RefRxConEvt;

};

#endif // !defined(AFX_TCTRAMEMSGCAN_H__A02B3C02_9B7E_11D5_BB22_000103175320__INCLUDED_)
