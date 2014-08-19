// tcCanASDT.cpp: implementation of the tcCanASDT class.
//
//////////////////////////////////////////////////////////////////////
#include "Config.h"
#ifdef CANAL_CAN      // Le canal can est utilisé

#include "tcCanASDT.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tcCanASDT::tcCanASDT()
{
  m_Erreur=NULL;
  m_FCallBackErr=NULL;
}

tcCanASDT::~tcCanASDT()
{
  if (m_Erreur!=NULL)
  {
    delete m_Erreur;
  }
}

void tcCanASDT::SetCallBackErr(tpfCallBackCanASErr CallBack,void* pParam)
{
  m_FCallBackErr      = CallBack;
  m_ParamCallBackErr  = pParam;
}

//********************************************************************//
// Indication d'une erreur
//********************************************************************//
void tcCanASDT::SetErreur(char* Erreur)
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