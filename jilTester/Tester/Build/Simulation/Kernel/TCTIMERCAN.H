// tcTimerCan.h: interface for the tcTimerCan class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCTIMERCAN_H__DD247F84_165B_11D6_A188_0001030A1077__INCLUDED_)
#define AFX_TCTIMERCAN_H__DD247F84_165B_11D6_A188_0001030A1077__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DefTypes.h"

#define cNbTempoCan               10
#define cNumeroTempoInvalide      -1

typedef void (*tpCallBack)(void* Param);
typedef struct
{
    U32     Duree;
    U32     Echeance;
    tpCallBack  pCallBack;
    void*       Param;
} tTempoCan;

class tcTimerCan
{
public:
    tcTimerCan();
    virtual ~tcTimerCan();

    void Initialiser();

    int       InsererTempoPeriodique(U32 Duree,tpCallBack pCallBack,void* Param=NULL);
    void      EnleverTempoPeriodique(int Numero);
    void      SetCallBackTempoPeriodique(int Numero,tpCallBack pCallBack,void* Param=NULL);
    void      SetDelayTempoPeriodique(int Numero,U32 Duree);

    void      Executer(U32 Date);
    int       GetDate() {return m_Date;}

    BOOL  DateDepassee(U32 Date);

private:
    U32   m_Date;
    tTempoCan m_lstTempoCan[cNbTempoCan];
};

#endif // !defined(AFX_TCTIMERCAN_H__DD247F84_165B_11D6_A188_0001030A1077__INCLUDED_)
