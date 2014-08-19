// tcCanalCan.h: interface for the tcCanalCan class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCCANALCAN_H__DD247F84_165B_11D6_A188_0001030A1077__INCLUDED_)
#define AFX_TCCANALCAN_H__DD247F84_165B_11D6_A188_0001030A1077__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>

#include "Ldbpc.h"			// Definition les types et constantes de bases
#include "LdbpcTem.h"

#include "tcCanSession.h"
#include "tcCanECar.h"
#include "tcTimerCan.h"
#include "tcTrameMsgCan.h"
#include "tcTrameMsgCanAck.h"
#include "tcTrameMsgCanSession.h"

#define cDureeTempoTimerCanMs    5
#define cTemMs				           1000000

class tcCanalCan
{
public:
    tcCanalCan();
    virtual ~tcCanalCan();

    BOOL CreerMsgSeg( tParamMsgSeg* ParamMsgSeg, S32 RefCan);
    BOOL CreerMsgSegAck( tParamMsgSeg* ParamMsgSeg, S32 RefCan);
    BOOL CreerMsgSegSession( tParamMsgSeg* ParamMsgSeg, S32 RefCan);

    void Initialisation();
    void SetCanNoPadding(BOOL CanNoPadding)	{ m_pCanSession->SetCanNoPadding(CanNoPadding);}

protected:
    static void CallBackCanReq(U32 Id,tTrameCan2* pTrameCan,void* pParam);
    static void CallBackCanErr(void* pParam);

    static void SignalerFC_STmin(void* Param1,void* Param2);
    static void SignalerFC_BS(void* Param1,void* Param2);
    static void SignalerFC_WFTmax(void* Param1,void* Param2);
    static void SignalerFC_FS(void* Param1,void* Param2);

private:
    tcCanSession* m_pCanSession;
    tcCanECar*    m_pCanECar;
    tcTimerCan    m_TimerCan;

    static void CallBackTimerCan();
    tcTempoSimple m_TempoCan;

    CArray<tcTrameMsgCan*,tcTrameMsgCan*>               m_lstTramesMsg;
    CArray<tcTrameMsgCanAck*,tcTrameMsgCanAck*>         m_lstTramesMsgAck;
    CArray<tcTrameMsgCanSession*,tcTrameMsgCanSession*> m_lstTramesMsgSession;

    BOOL  m_VariableUSDTInitialise;
    S32     m_DonneeFC_STmin;
    S32     m_DonneeFC_BS;
    S32     m_DonneeFC_WFTmax;
    S32     m_DonneeFC_FS;
};

extern tcCanalCan CanalCan;

#endif // !defined(AFX_TCCANALCAN_H__DD247F84_165B_11D6_A188_0001030A1077__INCLUDED_)
