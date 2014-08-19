// tcTrameMsgCanSession.h: interface for the tcTrameMsgCanSession class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCTRAMEMSGCANSESSION_H__A02B3C02_9B7E_11D5_BB22_000103175320__INCLUDED_)
#define AFX_TCTRAMEMSGCANSESSION_H__A02B3C02_9B7E_11D5_BB22_000103175320__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Ldbpc.h"			// Definition les types et constantes de bases
//#include "tcMsgSeg.h"		// Declaration de la classe de gestion de message segmentes
#include "LdbpcTem.h"
#include "tcCanSession.h"
#include "tcCanECar.h"

class tcTrameMsgCanSession
{
public:
    tcTrameMsgCanSession(tcCanSession* pCanSession,tcCanECar* pCanECar,tParamMsgSeg* pParamMsgSeg,S32 RefCan);
    virtual ~tcTrameMsgCanSession();

protected:

    // CallBack de réception de l'appli pour la DLL en Session
    static void CallBackInd(tObjetCanSession2* pObjetCanSession, tMsgCan2* pMsgCan,void* pParam);
    // CallBack de confirmation d'emission Session pour la DLL
    static void CallBackCon(tObjetCanSession2* pObjetCanSession,void* pParam);

    // CallBack de connexion de l'appli pour la DLL en Session
    static void CallBackConnectInd(tObjetCanSession2* pObjetCanSession,void* pParam);
    // CallBack de confirmation de connexion Session pour la DLL
    static void CallBackConnectCon(tObjetCanSession2* pObjetCanSession,void* pParam);
    // CallBack de déconnexion de l'appli pour la DLL en Session
    static void CallBackDeconnectInd(tObjetCanSession2* pObjetCanSession,void* pParam);
    // CallBack de confirmation de déconnexion Session pour la DLL
    static void CallBackDeconnectCon(tObjetCanSession2* pObjetCanSession,void* pParam);

    // CallBack de réception de la DLL pour l'appli en Session
    static void CallBackRxEvents(tpParam ,tpParam );
    // CallBack de connexion de la DLL pour l'appli en Session
    static void CallBackConnectRxEvents(tpParam ,tpParam );
    // CallBack de deconnexion de la DLL pour l'appli en Session
    static void CallBackDeconnectRxEvents(tpParam ,tpParam );
    // CallBack d'émission de l'appli pour la DLL en UUDT
    static void CallBackTxEvents(tpParam ,tpParam );

public:
    void ReqAppli(tTrameCan2* pTrameCan);

    // CallBack de réception de l'appli
    tpCallBackRxWithAddr   m_pCallBackRxAppli;

    tcCanSession* m_pCanSession;          // Port Can d'emission et de réception Session
    tcCanECar*    m_pCanECar;             // Port Can d'emission et de réception UU

    // ObjetCanSession
    tObjetCanSession2 m_ObjetCanSession;

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

    // NomDeMessageTxIndEvt : Signalisation de la Connexion
    S32 m_RefConnectTxIndEvt;

    // NomDeMessageTxIndEvt : Signalisation de la Deconnexion
    S32 m_RefDeconnectTxIndEvt;

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

    // NomDeMessageConnectRxIndEvt	: Signalisation de la Connexion
    S32 m_RefConnectRxIndEvt;
    // NomDeMessageRxConEvt : Confirmation de la Connexion
    S32 m_RefConnectRxConEvt;

    // NomDeMessageDeconnectRxIndEvt	: Signalisation de la Deconnexion
    S32 m_RefDeconnectRxIndEvt;
    // NomDeMessageRxConEvt : Confirmation de la Deconnexion
    S32 m_RefDeconnectRxConEvt;
};

#endif // !defined(AFX_TCTRAMEMSGCANSESSION_H__A02B3C02_9B7E_11D5_BB22_000103175320__INCLUDED_)
