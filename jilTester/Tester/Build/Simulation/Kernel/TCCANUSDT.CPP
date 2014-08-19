// tcCanUSDT.cpp: implementation of the tcCanUSDT class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Config.h"
#ifdef CANAL_CAN      // Le canal can est utilisé

#include "tcCanUSDT.h"

#ifdef CAN_DETECTION_CARTE  // Si defini, on inclut toutes les cartes connues
#include "tcCanNonUSDT.h"
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
tcCanUSDT::tcCanUSDT()
{
  m_Erreur=NULL;
  m_FCallBackErr=NULL;
  m_CartePresente=cFalse;
}

tcCanUSDT::~tcCanUSDT()
{
  if (m_Erreur!=NULL)
  {
    delete m_Erreur;
  }
}

void tcCanUSDT::SetCallBackErr(tpfCallBackCanUSErr CallBack,void* pParam)
{
  m_FCallBackErr      = CallBack;
  m_ParamCallBackErr  = pParam;
}

//********************************************************************//
// Indication d'une erreur
//********************************************************************//
void tcCanUSDT::SetErreur(char* Erreur)
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

//---- Renvoit une carte CAN si on en a trouvé une de dispo -----
#ifdef CAN_DETECTION_CARTE
tcCanUSDT* tcCanUSDT::ChercheCarteCan(tcTimerCan* pTimerCan,U32 VitesseCan,CString& InfoCarte,CString& Err, BOOL bReset)
{
  tcCanUSDT* pCanUSDT;
//*** PAS DE CARTE USDT UTILISABLE DIRECTEMENT POUR LE MOMENT

  // On essaye une carte en USDT
/*  InfoCarte.Format("Carte JCIUSDT??? à %d Bds",VitesseCan);      //EXEMPLE
  pCanUSDT=new tcCanJCIUSDT(VitesseCan,1);
  if (pCanUSDT->m_CartePresente) // Si carte présente, on regarde si il y a eu une erreur
  {
    Err=pCanUSDT->GetErreur();
    if (!Err.IsEmpty())
    {
      delete pCanUSDT;
      return NULL;
    }
    else
      return pCanUSDT;
  }
  delete pCanUSDT;  // Si non présente, On essaye une autre carte
*/

  // On cherche une carte Can non USDT avec une carte UUDT
  pCanUSDT=tcCanNonUSDT::ChercheCarteCan(pTimerCan,VitesseCan,InfoCarte,Err,bReset);
  if (pCanUSDT==NULL)
  {
    return NULL;
  }
  else
  {
    return pCanUSDT;
  }
}
#endif


#endif    // Le canal can est utilisé