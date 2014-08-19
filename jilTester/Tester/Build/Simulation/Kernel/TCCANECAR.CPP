/*============================================================================
  Project ......................... LDBPC
  Component ....................... tcCanECar
  File revision.................... $Revision:   1.0  $
  Last modification date .......... $Modtime:   04 Feb 2009 16:32:32  $
  -------------------------------------------------------------------------
  Copyright ... This software is JCI property. Duplication or
                disclosure is prohibited without JCI written permission
  ------------------------------------------------------------------------- 
    
  - This file should only contain data useful to the programmer to use
    this component
  - Component exported macros, constants and types are defined in this file
  - Component exported variables and functions are declared in this file 
    with the "extern" keyword
  
  -------------------------------------------------------------------------
  tcCanECar.cpp file review :
  


  ==========================================================================*/
#include "Config.h"
#ifdef CANAL_CAN      // Le canal can est utilisé

#include "tcCanECar.h"
#include "LDBPCTim.h"	// Definit l'interface du Module Timer

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

tcCanECar::tcCanECar(tcTimerCan* pTimerCan,tpfCallBackCanReq FCallBackCanReq,void* pParam):tcCanUUDT(pTimerCan)
{
  ASSERT(FCallBackCanReq!=NULL);
  static NumInstance = 1;
  m_FCallBackCanReq=FCallBackCanReq;
  m_ParamCallBackCanReq=pParam;

  m_CartePresente = cTrue;
  m_InitOk        = cTrue;

#ifndef DISABLE_SAD
  m_SADName.Format("Ecar%d",NumInstance++);
  char Name[cSADMaxNameLength];
  sprintf(Name,"CanUU%s",m_SADName);
  m_SADAdrFrame.SADConnect(Name);
#endif

}

tcCanECar::~tcCanECar()
{
#ifndef DISABLE_SAD
  m_SADAdrFrame.SADDeconnect();
#endif
}

//********************************************************************//
// On crée un objet CAN UUDT
//********************************************************************//
BOOL tcCanECar::CreerObjet(tObjetCanUU2* pObjetCan)
{
  m_Mutex.Lock();
  if (pObjetCan->TypeDeCommunication==cTypeComUUTransmissionPeriodique)   // Ne gérant pas l'émission périodique, on le fait faire par l'UUDT
    tcCanUUDT::CreerObjet(pObjetCan);
  m_lstObjetCanUU.Add(pObjetCan);
  m_Mutex.Unlock();
  return cTrue;  
}

//********************************************************************//
// On détruit un objet CAN UUDT
//********************************************************************//
BOOL tcCanECar::DetruireObjet(tObjetCanUU2* pObjetCan)
{
  // On cherche l'objet à l'aide du Handle correspondant
  U8 i=0;
  tObjetCanUU2* pObjetCanUU=NULL;
  m_Mutex.Lock();
  while((i<m_lstObjetCanUU.GetSize()) && (pObjetCanUU==NULL))
  {
    pObjetCanUU=(tObjetCanUU2*)m_lstObjetCanUU.GetAt(i);
    if (pObjetCanUU!=pObjetCan)
    {
      pObjetCanUU=NULL;
      i++;
    }
  }
  if (pObjetCanUU!=NULL)
  {
    if (pObjetCanUU->TypeDeCommunication==cTypeComUUTransmissionPeriodique)   // Ne gérant pas l'émission périodique, on le fait faire par l'UUDT
      tcCanUUDT::DetruireObjet(pObjetCanUU);
    m_lstObjetCanUU.RemoveAt(i);
  }
  else
  {
    SetErreur("tcCanECar::DetruireObjet> CanObject don't created.");
    m_Mutex.Unlock();
    return cFalse;
  }
  m_Mutex.Unlock();
  return cTrue;
}

//********************************************************************//
// Transmission d'une trame
//********************************************************************//
BOOL tcCanECar::ReqTrameUU(tObjetCanUU2* pObjetCan,tTrameCan2* pTrameCan)
{

#ifndef DISABLE_SAD
  tDelay Time;
  Timer.LireDate(&Time);
  m_SADAdrFrame.SADAdrFrameTraceTx(pObjetCan->Id,pTrameCan->Longueur,pTrameCan->Buffer,(tU32Bit)(Time/100000UL));
#endif  
  // On signale une fin d'émission par callback si demandée
  if (pObjetCan->FCallBackCon!=NULL)
  {
    pObjetCan->FCallBackCon(pObjetCan,pObjetCan->ParamCallBackCon);
  }

  // Appel de la callback de cdl de l'application après traitement de la confirmation
  // par E_CAR au cas ou lors de la segmentation les couches DAT envoient une trame directement
  // dans le traitement de la reception (Couches DAT CAN Vector)
  m_FCallBackCanReq(pObjetCan->Id,pTrameCan,m_ParamCallBackCanReq);

  return cTrue;
}

//********************************************************************//
// Reception d'une trame
//********************************************************************//
void tcCanECar::RepTrame(U32 Id,tTrameCan2* pTrameCan)
{
 #ifndef DISABLE_SAD
  tDelay Time;
  Timer.LireDate(&Time);
#endif  
  // On cherche l'objet UUDT correspondant
  for (int i=0;i<m_lstObjetCanUU.GetSize();i++)
  {
    if (((tObjetCanUU2*)m_lstObjetCanUU[i])->Id==Id)
    {
      break;
    }
  }
  if ((i<m_lstObjetCanUU.GetSize()) && (((tObjetCanUU2*)m_lstObjetCanUU[i])->FCallBackInd!=NULL))
  {
#ifndef DISABLE_SAD
    m_SADAdrFrame.SADAdrFrameTraceRx(((tObjetCanUU2*)m_lstObjetCanUU[i])->Id,pTrameCan->Longueur,pTrameCan->Buffer,(tU32Bit)(Time/100000UL));
#endif  
    ((tObjetCanUU2*)m_lstObjetCanUU[i])->FCallBackInd(((tObjetCanUU2*)m_lstObjetCanUU[i]),pTrameCan,((tObjetCanUU2*)m_lstObjetCanUU[i])->ParamCallBackInd);
  }
  else
  {
    SetErreur("tcCanECar::RepTrame> Identifier don't define");
  }
}
#endif CANAL_CAN