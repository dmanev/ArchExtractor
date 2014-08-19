// tcCanSession.cpp: implementation of the tcCanSession class.
//
//////////////////////////////////////////////////////////////////////
#include "Config.h"
#ifdef CANAL_CAN      // Le canal can est utilisé

#include "tcCanSession.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tcCanSession::tcCanSession()
{
  m_Erreur=NULL;
  m_FCallBackErr=NULL;
}

tcCanSession::~tcCanSession()
{
  if (m_Erreur!=NULL)
  {
    delete m_Erreur;
  }
}

void tcCanSession::SetCallBackErr(tpfCallBackCanSessionErr CallBack,void* pParam)
{
  m_FCallBackErr      = CallBack;
  m_ParamCallBackErr  = pParam;
}

//********************************************************************//
// Indication d'une erreur
//********************************************************************//
void tcCanSession::SetErreur(char* Erreur)
{
  ASSERT(Erreur!=NULL);
  if (m_Erreur!=NULL)
  {
    delete m_Erreur;
  }
  m_Erreur=new char[strlen(Erreur)+1];
  strcpy(m_Erreur,Erreur);
  if (m_FCallBackErr!=NULL)
  {
    m_FCallBackErr(m_ParamCallBackErr);
  }
}

#endif    // Le canal can est utilisé