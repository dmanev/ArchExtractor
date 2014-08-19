// tcCanUUDT.cpp: implementation of the tcCanUUDT class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Config.h"
#ifdef CANAL_CAN      // Le canal can est utilisé

#include "tcCanUUDT.h"

#ifdef CAN_DETECTION_CARTE      // Si defini, on inclu toutes les cartes connues
#include "tcCanTestUUDT.h"
#include "tcCanNI.h"
#include "tcCanVector.h"
#include "tcCanAIXIA.h"
#include "tcCanNsi.h"
#include "tcCanJCI.h"
#endif

int tcCanUUDT::m_Carte1 = cCarte1;    // Mémorisation de la 1ère carte pour ne pas reprendre la même

//////////////////////////////////////////////////////////////////////
// Param des cartes can
//////////////////////////////////////////////////////////////////////

tcParamCan2::tcParamCan2() 
{  
  m_bReset      = cFalse;
  m_BaudRate    = cInvalidBaudrate;
  m_Port        = cInvalidPort;
  m_QueueRead   = cMaxFrameNumber;
  m_QueueWrite  = cMaxFrameNumber;
  m_CodeStd     = 0;
  m_MaskStd     = 0;      // 0 Don't care, 1 must match
  m_CodeXtd     = 0;
  m_MaskXtd     = 0;      // 0 Don't care, 1 must match
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
tcCanUUDT::tcCanUUDT(tcTimerCan* pTimerCan)
{
  ASSERT(pTimerCan!=NULL);
  m_pTimerCan=pTimerCan;

  m_OffsetPeriodique  = 0;
  m_CartePresente     = cFalse;
  m_InitOk            = cFalse;
  m_Erreur            = NULL;
  m_FCallBackErr      = NULL;  

  m_NumeroTempo=cNumeroTempoInvalide;
/*
  // On crée l'évènement d'envoi
  m_hEventReq=CreateEvent(NULL,FALSE,FALSE,NULL);
  if (m_hEventReq==INVALID_HANDLE_VALUE)
  {
		SetErreur("tcCanUUDT::tcCanUUDT> Creation Error of the sending event");
  }

  // On initialise le corps du thread
  m_Arret=cFalse;
  m_hThread = CreateThread( NULL,0,CorpsThreadReq,(LPVOID)this,0,&m_ThreadID);
  if(m_hThread==INVALID_HANDLE_VALUE)
  {
		SetErreur("tcCanUUDT::tcCanUUDT> Creation Error of the sending thread");
  }
*/
}

tcCanUUDT::~tcCanUUDT()
{
/*
  // On arrête le thread
  if (m_ThreadID)
  {
    m_Arret=cTrue;
    WaitForSingleObject(m_hThread,5000);
    CloseHandle(m_hThread);
  }

  if (m_hEventReq==INVALID_HANDLE_VALUE)
  {
    CloseHandle(m_hEventReq);
  }
*/
  // On arrête le timer pour l'émission périodique
  if (m_NumeroTempo!=cNumeroTempoInvalide)   
  {
    m_pTimerCan->EnleverTempoPeriodique(m_NumeroTempo);
  }

  // On détruit tous les ObjetCanUUPeriodique crée
  m_MutexPeriodique.Lock();
  tObjetCanUUPeriodique* pObjetCanUUPeriodique;
  while(m_lstObjetCanUUPeriodique.GetSize())
  {
    pObjetCanUUPeriodique=(tObjetCanUUPeriodique*)m_lstObjetCanUUPeriodique.GetAt(0);
    delete pObjetCanUUPeriodique;
    m_lstObjetCanUUPeriodique.RemoveAt(0);
  }
  m_MutexPeriodique.Unlock();

  // On enlève tous les Handle mémorisé
  m_Mutex.Lock();
  while(m_lstObjetCanUU.GetSize()>0)
  {
    m_lstObjetCanUU.RemoveAt(0);
  }
  m_Mutex.Unlock();
/*
  // On vide la liste des messages à envoyer
  m_MutexTramesReq.Lock();
  while(m_lstTramesReq.GetSize())
  {
    delete  (tTrameCanReq*)m_lstTramesReq[0];
    m_lstTramesReq.RemoveAt(0);   // On enlève les message de la liste
  }
  m_MutexTramesReq.Unlock();
*/
  if (m_Erreur!=NULL)
  {
    delete m_Erreur;
  }
}

void tcCanUUDT::SetCallBackErr(tpfCallBackCanUUErr CallBack,void* pParam)
{
  m_FCallBackErr      = CallBack;
  m_ParamCallBackErr  = pParam;
}

//********************************************************************//
// Indication d'une erreur
//********************************************************************//
void tcCanUUDT::SetErreur(const char* Erreur)
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


//********************************************************************//
// On crée un objet CAN UUDT périodique, on défini un param supplémentaire
//********************************************************************//
BOOL tcCanUUDT::CreerObjet(tObjetCanUU2* pObjetCan)
{
  if (!m_InitOk)
  {
    SetErreur("tcCanUUDT::CreerObjet> the CAN card hasn't been initialized.");
    return cFalse;
  }
  if (pObjetCan->TypeDeCommunication!=cTypeComUUTransmissionPeriodique)
  {
    SetErreur("tcCanUUDT::CreerObjet> this class don't manage the periodical transmissions");
    return cFalse;
  }

  if (m_NumeroTempo==cNumeroTempoInvalide)   // On crée le timer pour l'émission périodique
  {
    m_NumeroTempo=m_pTimerCan->InsererTempoPeriodique(cPasPeriodiqueUUDT,&CallBackPeriodique,this);
    if (m_NumeroTempo==cNumeroTempoInvalide)
    {
		  SetErreur("tcCanUUDT::CreerObjet> Creation error of périodical timer");
    }
  }

  tObjetCanUUPeriodique* pObjetCanUUPeriodique=new tObjetCanUUPeriodique;
  pObjetCanUUPeriodique->ReqPeriodique=cFalse;
  pObjetCanUUPeriodique->DateProchainEnvoi=m_OffsetPeriodique;
  m_OffsetPeriodique += cPasPeriodiqueUUDT;
  if (m_OffsetPeriodique > cOffsetPeriodiqueMax)
  {
    m_OffsetPeriodique = 0;
  }
  pObjetCanUUPeriodique->pObjetCanUU=pObjetCan;
  m_MutexPeriodique.Lock();
  m_lstObjetCanUUPeriodique.Add(pObjetCanUUPeriodique);
  m_MutexPeriodique.Unlock();
  return cTrue;
}

//********************************************************************//
// On détruit un objet CAN UUDT
//********************************************************************//
BOOL tcCanUUDT::DetruireObjet(tObjetCanUU2* pObjetCan)
{
  // On cherche l'objet à l'aide du Handle correspondant
  U8 i=0;
  tObjetCanUUPeriodique* pObjetCanUUPeriodique=NULL;
  m_MutexPeriodique.Lock();
  while((i<m_lstObjetCanUUPeriodique.GetSize()) && (pObjetCanUUPeriodique==NULL))
  {
    pObjetCanUUPeriodique=(tObjetCanUUPeriodique*)m_lstObjetCanUUPeriodique.GetAt(i);
    if (pObjetCanUUPeriodique->pObjetCanUU!=pObjetCan)
    {
      pObjetCanUUPeriodique=NULL;
      i++;
    }
  }
  if (pObjetCanUUPeriodique!=NULL)
  {
    delete pObjetCanUUPeriodique;
    m_lstObjetCanUUPeriodique.RemoveAt(i);
  }
  else
  {
    SetErreur("tcCanUUDT::DetruireObjet> periodical Can object don't created.");
    m_MutexPeriodique.Unlock();
    return cFalse;
  }
  m_MutexPeriodique.Unlock();
  return cTrue;
}

//********************************************************************//
// Transmission d'un message
//********************************************************************//
BOOL tcCanUUDT::Req(tObjetCanUU2* pObjetCan,tTrameCan2* pTrameCan,U8 Envoi)
{
  // On regarde si l'objet est périodique
  if (pObjetCan->TypeDeCommunication!=cTypeComUUTransmissionPeriodique)
  {
    return ReqTrame(pObjetCan,pTrameCan);
  }
  else
  {
    // On cherche l'objet à l'aide du Handle correspondant
    U8 i=0;
    tObjetCanUUPeriodique* pObjetCanUUPeriodique=NULL;
    m_MutexPeriodique.Lock();
    while((i<m_lstObjetCanUUPeriodique.GetSize()) && (pObjetCanUUPeriodique==NULL))
    {
      pObjetCanUUPeriodique=(tObjetCanUUPeriodique*)m_lstObjetCanUUPeriodique.GetAt(i);
      if (pObjetCanUUPeriodique->pObjetCanUU!=pObjetCan)
      {
        pObjetCanUUPeriodique=NULL;
        i++;
      }
    }
    if (pObjetCanUUPeriodique!=NULL)
    {
      pObjetCanUUPeriodique->Trame.Longueur=pTrameCan->Longueur;
      memcpy(pObjetCanUUPeriodique->Trame.Buffer,pTrameCan->Buffer,pTrameCan->Longueur);
      if (Envoi==cEnvoiUUImmediat)    // Si envoi immédiat, on envoi
      {
        ReqTrame(pObjetCanUUPeriodique->pObjetCanUU,&pObjetCanUUPeriodique->Trame);
      }
    }
    else
    {
      SetErreur("tcCanUUDT::Req> Periodical Can object don't created.");
      m_MutexPeriodique.Unlock();
      return cFalse;
    }
    m_MutexPeriodique.Unlock();
    return cTrue;
  }
}

//********************************************************************//
// Activation de l'émission périodique ou non
//********************************************************************//
BOOL tcCanUUDT::ActiverReqPeriodique(tObjetCanUU2* pObjetCan,BOOL Active)
{
  // On cherche l'objet à l'aide du Handle correspondant
  U8 i=0;
  tObjetCanUUPeriodique* pObjetCanUUPeriodique=NULL;
  m_MutexPeriodique.Lock();
  while((i<m_lstObjetCanUUPeriodique.GetSize()) && (pObjetCanUUPeriodique==NULL))
  {
    pObjetCanUUPeriodique=(tObjetCanUUPeriodique*)m_lstObjetCanUUPeriodique.GetAt(i);
    if (pObjetCanUUPeriodique->pObjetCanUU!=pObjetCan)
    {
      pObjetCanUUPeriodique=NULL;
      i++;
    }
  }
  if (pObjetCanUUPeriodique!=NULL)
  {
    pObjetCanUUPeriodique->ReqPeriodique=Active;
    pObjetCanUUPeriodique->DateProchainEnvoi=m_pTimerCan->GetDate()+m_OffsetPeriodique;
    m_OffsetPeriodique += cPasPeriodiqueUUDT;
    if (m_OffsetPeriodique > cOffsetPeriodiqueMax)
    {
      m_OffsetPeriodique = 0;
    }
  }
  else
  {
    SetErreur("tcCanUUDT::ActiverReqPeriodique> Periodical Can object don't created.");
    m_MutexPeriodique.Unlock();
    return cFalse;
  }
  m_MutexPeriodique.Unlock();
  return cTrue;
}

//********************************************************************//
// CallBack gérant les émissions périodique
//********************************************************************//
void tcCanUUDT::CallBackPeriodique(void* Param)
{
  //---- On récupère le pointeur de la classe ----
  tcCanUUDT* pCanUUDT=(tcCanUUDT*)Param;
  tObjetCanUUPeriodique* pObjetCanUUPeriodique;
  U8 i;

  if (pCanUUDT->m_MutexPeriodique.Lock(50))
  {
    i=0;
    while(i<pCanUUDT->m_lstObjetCanUUPeriodique.GetSize())  // On transmet si la date est OK
    {
      pObjetCanUUPeriodique=(tObjetCanUUPeriodique*)pCanUUDT->m_lstObjetCanUUPeriodique.GetAt(i);
      if ((pObjetCanUUPeriodique->ReqPeriodique)
       && (pCanUUDT->GetTimerCan()->DateDepassee(pObjetCanUUPeriodique->DateProchainEnvoi)))
      {
        pCanUUDT->ReqTrame(pObjetCanUUPeriodique->pObjetCanUU,&pObjetCanUUPeriodique->Trame);
        pObjetCanUUPeriodique->DateProchainEnvoi+=pObjetCanUUPeriodique->pObjetCanUU->Periode;
      }
      i++;
    }
    pCanUUDT->m_MutexPeriodique.Unlock();
  }
}

//********************************************************************//
// Emission de trame
//********************************************************************//
BOOL tcCanUUDT::ReqTrame(tObjetCanUU2* pObjetCan,tTrameCan2* pTrameCan)
{
	ReqTrameUU(pObjetCan,pTrameCan);
	/*
  if (m_lstTramesReq.GetSize() < cMaxFrameNumber)
  {
    tTrameCanReq* pTrameCanReq=new tTrameCanReq;
    pTrameCanReq->pObjetCanUU=pObjetCan;
    pTrameCanReq->Trame.Longueur=pTrameCan->Longueur;
    memcpy(pTrameCanReq->Trame.Buffer,pTrameCan->Buffer,pTrameCan->Longueur);
    m_MutexTramesReq.Lock();
    m_lstTramesReq.Add(pTrameCanReq);
    m_MutexTramesReq.Unlock();
    SetEvent(m_hEventReq);

  }
  else
  {
    SetErreur("tcCanUUDT::ReqTrame> Overflow, frame lost");
    return cFalse;
  }
  */
  return cTrue;
}

//********************************************************************//
// Thread gérant les réceptions de trames
//********************************************************************//
/*
DWORD WINAPI tcCanUUDT::CorpsThreadReq( LPVOID Param )
{
  //---- On récupère le pointeur de la classe ----
  tcCanUUDT* pCanUUDT=(tcCanUUDT*)Param;

  //---- On boucle pour émmetre les messages j'usqu'à l'arrêt ----
  tObjetCanUU2*  pObjetCanUU;
  tTrameCanReq* pTrameCanReq;
  BOOL AttenteEvent;

  AttenteEvent=cTrue;
  while(!pCanUUDT->m_Arret)
  {
    // On attend les évènements
    switch(WaitForSingleObject(pCanUUDT->m_hEventReq,100))
    {
    case WAIT_OBJECT_0:     // Req Event
              pCanUUDT->m_MutexTramesReq.Lock();
              while(pCanUUDT->m_lstTramesReq.GetSize() && !pCanUUDT->m_Arret)
              {
                pTrameCanReq=(tTrameCanReq*)pCanUUDT->m_lstTramesReq[0];
                pObjetCanUU=pTrameCanReq->pObjetCanUU;
                pCanUUDT->m_MutexTramesReq.Unlock();
                if (pCanUUDT->ReqTrameUU(pObjetCanUU,&pTrameCanReq->Trame))
                {
                  pCanUUDT->m_MutexTramesReq.Lock();
                  pCanUUDT->m_lstTramesReq.RemoveAt(0);   // On enlève le message de la liste
                  pCanUUDT->m_MutexTramesReq.Unlock();
                  delete  pTrameCanReq;
                }
                else
                {
                  Sleep(2);   // On attend que la queue se vide
                }
                pCanUUDT->m_MutexTramesReq.Lock();
              }
              pCanUUDT->m_MutexTramesReq.Unlock();
              break;
    }
  }
  pCanUUDT->m_ThreadID=0;
  return cTrue;
}
*/
//********************************************************************//
// Renvoit une carte CAN si on en a trouvé une de dispo
//********************************************************************//
#ifdef CAN_DETECTION_CARTE
tcCanUUDT* tcCanUUDT::ChercheCarteCan(tcTimerCan* pTimerCan,U32 VitesseCan,CString& InfoCarte,CString& Err,int NumCarte,BOOL bReset)
{
  tcParamCan2 ParamCan;
  ParamCan.m_bReset   = bReset;
  ParamCan.m_BaudRate = VitesseCan;
  return ChercheCarteCan(pTimerCan,&ParamCan,InfoCarte,Err,NumCarte);
}

tcCanUUDT* tcCanUUDT::ChercheCarteCan(tcTimerCan* pTimerCan,tcParamCan2* pParamCan,CString& InfoCarte,CString& Err,int NumCarte)
{
  ASSERT(pParamCan!=NULL);

  tcCanUUDT* pCanUUDT;
  CString Erreur;
  int CarteEnCours;

  if(pParamCan->m_bReset == cTrue)
  {
	  m_Carte1 = cCarte1;
  }

  CarteEnCours=(NumCarte==cCarteIndefini)?m_Carte1:NumCarte;
  do
  {
    switch(CarteEnCours)
    {
    case cCarteTest:
            InfoCarte = "Test Card";
            pCanUUDT=new tcCanTestUUDT(pTimerCan);
            break;
    case cCarteNI_Port0:      // On essaye la carte NI
    case cCarteNI_Port1:
            pParamCan->m_Port = CarteEnCours&cCarteMskPort;
            InfoCarte.Format("NI Card: %d Bds Port %d",pParamCan->m_BaudRate,pParamCan->m_Port);
            pCanUUDT=new tcCanNI(pTimerCan,pParamCan);
            break;
    case cCarteVector_Port0:  // On essaye la carte Vector
    case cCarteVector_Port1:
            pParamCan->m_Port = CarteEnCours&cCarteMskPort;
            InfoCarte.Format("CanCardx Card: %d Bds Port %d",pParamCan->m_BaudRate,pParamCan->m_Port);
            pCanUUDT=new tcCanVector(pTimerCan,pParamCan);
            break;
    case cCarteNsi_Port0:     // On essaye la carte Nsi
    case cCarteNsi_Port1:
            pParamCan->m_Port = CarteEnCours&cCarteMskPort;
            InfoCarte.Format("Nsi Card: %d Bds Port %d",pParamCan->m_BaudRate,pParamCan->m_Port);
            pCanUUDT=new tcCanNsi(pTimerCan,pParamCan);
            break;
    case cCarteAixia_Com1:    // On essaye la carte AIXIA
    case cCarteAixia_Com2:
            pParamCan->m_Port = (CarteEnCours&cCarteMskPort)+1;
            InfoCarte.Format("Aixia Card: %d Bds Com%d",pParamCan->m_BaudRate,pParamCan->m_Port);
            pCanUUDT=new tcCanAIXIA(pTimerCan,pParamCan);
            break;
    case cCarteJCI_Port0:    // On essaye la carte JCI
    case cCarteJCI_Port1:
            pParamCan->m_Port = (CarteEnCours&cCarteMskPort);
            InfoCarte.Format("JCI Card: %d Bds Port %d",pParamCan->m_BaudRate,pParamCan->m_Port);
            pCanUUDT=new tcCanJCI(pTimerCan,pParamCan);
            break;
    default://On arrête, aucun modèle n'a été trouvée
            pCanUUDT = NULL;
            if (Erreur.IsEmpty())
            {
              Erreur="No another card detected";
            }
            Err+="\n";
            Err+=Erreur;
            break;
    }

    // On se prépare pour le port suivant
    if ((CarteEnCours&cCarteMskPort)<cCarteMaxPort)  // On essaye un autre port
    {
      CarteEnCours += cCarteIncPort;
    }
    else                                        // On essaye une autre carte
    {
      CarteEnCours += cCarteIncConstructeur;
      CarteEnCours &= cCarteMskConstructeur;     // On revient au port 0
    }
    m_Carte1 = CarteEnCours;  // La prochaine carte à essayer mémorisée

    if (pCanUUDT!=NULL)       // On a trouvé une carte
    {
      if (pCanUUDT->m_InitOk) // Si Init Carte OK
      {
        return pCanUUDT;
      }
      else                    // Sinon on change de carte
      {
        Erreur+="\n";
        Erreur+=InfoCarte;
        Erreur+=": ";
        Erreur+=pCanUUDT->GetErreur();
        delete pCanUUDT;

        if (NumCarte!=cCarteIndefini)   // La carte voulu n'existe pas
        {
          pCanUUDT = NULL;
          Err+="\n";
          Err+=Erreur;
        }
      }
    }
  } while(pCanUUDT != NULL);
  return NULL;
}
#endif


#endif    // Le canal can est utilisé