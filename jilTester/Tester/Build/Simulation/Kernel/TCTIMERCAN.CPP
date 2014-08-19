// tcTimerCan.cpp: implementation of the tcTimerCan class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Config.h"
#ifdef CANAL_CAN      // Le canal can est utilisé

#include "tcTimerCan.h"
#include "afx.h"          // pour la fonction TRACE

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tcTimerCan::tcTimerCan()
{
  for (int i=0;i<cNbTempoCan;i++)
  {
    m_lstTempoCan[i].Duree=0;
  }
  m_Date=0;
}

tcTimerCan::~tcTimerCan()
{

}

void tcTimerCan::Initialiser()
{
  m_Date = 0;
  for (int i=0;i<cNbTempoCan;i++)
  {
    m_lstTempoCan[i].Echeance = m_Date + m_lstTempoCan[i].Duree;
  }
}

int tcTimerCan::InsererTempoPeriodique(U32 Duree,tpCallBack pCallBack,void* Param)
{
  for (int i=0;i<cNbTempoCan;i++)
  {
    if (m_lstTempoCan[i].Duree==0)
    {
      break;
    }
  }
  if (i<cNbTempoCan)
  {
    if (Duree==0)
      Duree=1;
    m_lstTempoCan[i].Duree=Duree;
    m_lstTempoCan[i].Echeance=m_Date+Duree;
    m_lstTempoCan[i].pCallBack=pCallBack;
    m_lstTempoCan[i].Param=Param;
    return i;
  }
  else
  {
    return cNumeroTempoInvalide;
  }
}

void tcTimerCan::EnleverTempoPeriodique(int Numero)
{
  ASSERT(Numero!=cNumeroTempoInvalide);
  m_lstTempoCan[Numero].Duree=0;
}

void tcTimerCan::SetCallBackTempoPeriodique(int Numero,tpCallBack pCallBack,void* Param)
{
  ASSERT(Numero!=cNumeroTempoInvalide);
  m_lstTempoCan[Numero].pCallBack=pCallBack;
  m_lstTempoCan[Numero].Param=Param;
}

void tcTimerCan::SetDelayTempoPeriodique(int Numero,U32 Duree)
{
  ASSERT(Numero!=cNumeroTempoInvalide);
  if (Duree==0)
    Duree=1;
  m_lstTempoCan[Numero].Duree=Duree;
}

void tcTimerCan::Executer(U32 Date)
{
  if (m_Date<=Date)
  {
    m_Date=Date;
    for (int i=0;i<cNbTempoCan;i++)
    {
      if ((m_lstTempoCan[i].Duree!=0) && (m_lstTempoCan[i].Echeance<=m_Date))
      {
        m_lstTempoCan[i].Echeance+=m_lstTempoCan[i].Duree;
        m_lstTempoCan[i].pCallBack(m_lstTempoCan[i].Param);
      }
    }
  }
  else
  {
    TRACE("tcTimerCan::Executer> Error Timer");
  }
}

BOOL tcTimerCan::DateDepassee(U32 Date)
{
  return (Date<m_Date);
}

#endif    // Le canal can est utilisé