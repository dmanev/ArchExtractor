/****************************************************************************
Project ......................... LDBPC
Component ....................... LdbpcTra
File revision.................... 1.1
Last modification date .......... 22/01/2002
-------------------------------------------------------------------------
Copyright ... This software is JCI property. Duplication or
disclosure is prohibited without JCI written permission
------------------------------------------------------------------------- 

  - Macros, constants et types which are not exported are defined in 
  this file
  - Variables and functions which are not exported are defined in this 
  file with the static key word
  
    -------------------------------------------------------------------------
    Comments on the component (role, algorithm, structure, limitations,
    defined tasks and events...)
    - Role : Geestion des trames du LDBPC
    
      -------------------------------------------------------------------------
      GG : 20/04/2000 : v1.0	: Creation
      GG : 22/08/2001 : v1.1	: Optimisation
      GG : 22/01/2002 : v1.3	: Correction Init Fnip
      GG : 12/04/2002 : v1.4	: Optimisation est activée avec OPTIMISATION_LDBPC_TRAME 
      -------------------------------------------------------------------------
      On STK
      EB : 30/04/2002 : v1.0	: Initial Revision
      GG : 07/10/2002 : v1.1	: PON URD42 DEV 105 / PON URD45 BODY_SW 11   
*****************************************************************************/

#define LdbpcTra "LdbpcTra"

//--------------------------------------------------------------------------
//---------------- Inclusion de fichiers (système et librairies -----------
//--------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////
//
// LdbpcTra.cpp: implementation of the tcElement class.
//
//////////////////////////////////////////////////////////////////////
#include <string.h>
#include "config.h"
#include "Ldbpc.h"			// Defini les types et constantes de bases
#include "LdbpcTra.h"
#include "LdbpcRdo.h"

//--------------------------------------------------------------------------
//------- Inclusion des definitions des autres composants utiles ---------
//--------------------------------------------------------------------------
#include "LDBPCDon.h"		// Definit l'interface du Module Donnees
#include "LdbpcRes.h"		// Definit l'interface du Module Ressources
#include "LdbpcTim.h"		// Definit l'interface du Module Timer
#include "LdbpcCan.h"		// Definit l'interface de la classe Canal

//--------------------------------------------------------------------------
//------- Declaration des constantes locales à ce composant --------------
//--------------------------------------------------------------------------
// #define cNomConstante ValeurDeLaConstante
//--------------------------------------------------------------------------
//------- Declaration des macros locales à ce composant ------------------
//--------------------------------------------------------------------------
// #define mNomMacro (DefinitionDeLaMacro)

//--------------------------------------------------------------------------
//------- Definition des types locaux à ce composant ---------------------
//--------------------------------------------------------------------------
// typedef ... tNomType;
//--------------------------------------------------------------------------
//------- Variables locales à ce composant---------------------------------
//--------------------------------------------------------------------------
// static tType NomVariable;
// static tType* pNomVariable;
//--------------------------------------------------------------------------
//------- Donnees Constantes locales à ce composant ----------------------
//--------------------------------------------------------------------------
// static const tType NomVariable;
//--------------------------------------------------------------------------
//------- Variables exportees par ce composant ---------------------------
//--------------------------------------------------------------------------
// tType ComNomVariable; (Com: 3 lettres identifiant ce composant)
// tType* pComNomVariable;
//--------------------------------------------------------------------------
//------- Donnees Constantes exportees par ce composant ------------------
//--------------------------------------------------------------------------
// const tType ComNomVariable; (Com: 3 lettres identifiant ce composant)
//--------------------------------------------------------------------------
//---------------------------- Fonctions locales ---------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//------------------------- Fonctions exportees ----------------------------
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
//--------------- Implementation de la classe tcTrame -------------------
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// Constructeurs
//--------------------------------------------------------------------------
tcTrame::tcTrame()
{
  m_pCanal        = NULL;
  m_TypeFlux      = cNoFlux;
  m_RefFlux       = -1;
  
  m_pNom          = NULL;
  m_Adresse       = 0;
  m_CurrentSize   = 0; // Taille de la trame courante (en octet)
  m_MaxSize       = 0; // Taille de la trame max (en octet)
  m_TypeFrame     = cTypeFrameFixSize;
  m_pBufferTemp   = NULL;
  m_pBufferSave   = NULL;
  m_FlagModif     = cTrue;
  
  m_RefEvt        = -1;
  m_BufferRef     = -1;
  m_BufferSizeRef = -1;
}

tcTrame::tcTrame(tInfoBuildFrame * pBuildFrame)
{
  char * pNom = pBuildFrame->pInfoFrame->pName;
  if(pNom)
  {
    m_pNom = (char *) new char[(strlen(pNom)+1)*sizeof(char)];
    if(m_pNom)
    {
      strcpy(m_pNom, pNom);
    }
    else
    {
      mLDBPCErreur(cLdbpcErrAllocMem);
    }
  }
  else m_pNom = NULL;
  
  m_pCanal = pBuildFrame->pCanal;
  m_RefFlux	= 	pBuildFrame->pInfoFrame->RefFlux;	
  m_TypeFlux	=	pBuildFrame->pInfoFrame->TypeFlux;
  
  m_Adresse	=	pBuildFrame->pInfoFrame->Address;
  m_MaxSize	=	pBuildFrame->pInfoFrame->MaxSize;
  m_CurrentSize = m_MaxSize;
  m_TypeFrame =   pBuildFrame->pInfoFrame->TypeFrame;
  
  m_RefEvt	=	pBuildFrame->EvtRef;
  m_BufferRef =   pBuildFrame->BufferRef;
  m_BufferSizeRef=   pBuildFrame->BufferSizeRef;
  
  if(m_TypeFrame == cTypeFrameVarSize)
  {
    // Intialisation de la fonction de CallBack
    Donnees.SetCallBack(m_BufferRef, &tcTrame::CallBackEvents,(tpParam)this);
    Donnees.SetCallBack(m_BufferSizeRef, &tcTrame::CallBackEvents,(tpParam)this);
  }
  
  m_FlagModif = cTrue;
  m_pBufferTemp = (U8*) new U8[sizeof(U8)*m_MaxSize];
  m_pBufferSave = (U8*) new U8[sizeof(U8)*m_MaxSize];
}

void tcTrame::Initialiser()
{
  m_FlagModif = cTrue;
}


//--------------------------------------------------------------------------
// Destructeur
//--------------------------------------------------------------------------
tcTrame::~tcTrame()
{
  tcRefDonnee * pRefdonnee;
  // Tant que la liste des references de donnees est pleine
  
  while(!m_ListeDonnee.IsEmpty())
  {
    // Récuperation de la reference de donnee en tete de liste
    pRefdonnee =  m_ListeDonnee.GetHead();
    // Suppression de la reference de donnee de la tete de la liste
    m_ListeDonnee.RemoveHead();
    // Destruction de la reference de donnee
    delete pRefdonnee;
  }
  
  if(m_pNom)
  {
    delete [] m_pNom;
  }
  if(m_pBufferTemp)
  {
    delete [] m_pBufferTemp;
  }
  if(m_pBufferSave)
  {
    delete [] m_pBufferSave;
  }
}

//--------------------------------------------------------------------------
// Ajouter une donnee a une trame
//--------------------------------------------------------------------------
tLDBPCStatut tcTrame::AjouterDonnee(S32 RefTrame,S32 RefDonnee, U32 Position)
{
  BOOL bParcours = cTrue;
  tLDBPCStatut Res = cLdbpcErr;
  tcRefDonnee * pRefDonneeRef = NULL;
  tcRefDonnee * pRefDonneePrec = NULL;
  U32 lsbDonnee;				// position du lsb de la donnee
  U32 msbDonnee = Position;	// position du msb de la donnee
  
  // Creation de la reference de donnee
  tcRefDonnee * pRefdonnee = new tcRefDonnee(RefTrame,RefDonnee, Position, m_MaxSize);
  
  // Intialisation de la fonction de CallBack
  Donnees.SetCallBack(RefDonnee, &tcTrame::CallBackEvents,(tpParam)this);
  
  // Si la reference de donnee existe
  if(pRefdonnee)
  {
    lsbDonnee = pRefdonnee->LireLSB();
    // Verification du placement de la donnee dans la trame
    if((msbDonnee <= lsbDonnee) && (lsbDonnee < (m_MaxSize*8)))
    {
      Res = cLdbpcOk;
      // Initilisation de la position en tete de liste
      pRefDonneeRef =  m_ListeDonnee.GetHead();
      
      // Parcours de la liste
      while(pRefDonneeRef != NULL)
      {
        // Si la position du lsb de la donnee se trouve avant 
        // la position du msb de la donnee courante
        if(lsbDonnee < pRefDonneeRef->LireMSB()) break;
        // Si la donnee courante est la derniere de la liste
        else if(pRefDonneeRef->m_pNext == NULL)
        {
          // Si la position du msb de la donnee se trouve
          // avant ou egale la position du lsb de la derniere donnee
          if(msbDonnee <= pRefDonneeRef->LireLSB())
          {
            // Donnee a inserer incorrecte
            Res = cLdbpcErrDonnee;
          }
          // Donnee suivante
          pRefDonneePrec = pRefDonneeRef;
          pRefDonneeRef  = pRefDonneeRef->m_pNext;
        }
        // Si la position du msb de la donnee se trouve après 
        // la position du lsb de la donnee courante
        else if(msbDonnee > pRefDonneeRef->LireLSB())
        {
          // Donnee suivante
          pRefDonneePrec = pRefDonneeRef;
          pRefDonneeRef  = pRefDonneeRef->m_pNext;
        }
        else
        {
          // Donnee a inserer incorrecte
          Res = cLdbpcErrDonnee;
          // Fin de parcours de la liste
          break;
        }
      }
      
      if(Res == cLdbpcOk)
      {
        if(pRefDonneePrec == NULL)
        {
          // Ajout en tete de liste
          m_ListeDonnee.AddHead(pRefdonnee);
        }
        else
        {
          // Insertion de la tempo dans la liste
          m_ListeDonnee.InsertAfter(pRefDonneePrec, pRefdonnee);
        }
        
      }
    }
    else Res = cLdbpcErrDonnee;
  }
  
  // Si la reference de donnee existe et n'a pas ete attache a la liste
  if((Res != cLdbpcOk) && (pRefdonnee))
  {
    // Destruction de la reference
    delete pRefdonnee;
  }
  
  return Res;
}

//--------------------------------------------------------------------------
// Lire une trame
//--------------------------------------------------------------------------
tLDBPCStatut tcTrame::Lire(tMsg * pMsg)
{
  BOOL bParcours = cTrue;
  tcRefDonnee * pRefdonnee;
  tLDBPCStatut Res = cLdbpcOk;
  
  // GG : 12/04/2002
#ifndef OPTIMISATION_LDBPC_TRAME
  m_FlagModif = cTrue;
#endif
  
  if(m_FlagModif)
  {
    if(pMsg && pMsg->pBuffer)
    {
      // Effacer la trame
      memset(pMsg->pBuffer, 0, pMsg->Lng);
      
      // Type de Trame
      if(m_TypeFrame  == cTypeFrameFixSize)
      {
        // Verifiction de la taille demande
        if(pMsg->Lng == m_CurrentSize)
        {
          // Initilisation de la position en tete de liste
          pRefdonnee =  m_ListeDonnee.GetHead();
          
          // Parcours de la liste
          while(pRefdonnee != NULL)
          {
            // Lecture de la donnee dans le message
            Res = pRefdonnee->Lire(pMsg);
            
            // Donnee suivante
            pRefdonnee  = pRefdonnee->m_pNext;
          }
          
          // Sauvegarde de la trame
          memcpy(m_pBufferSave, pMsg->pBuffer, m_CurrentSize);
          m_FlagModif = cFalse;
        }
        else Res = mLDBPCErreur(cLdbpcErrTrame);
      }
      else if (m_TypeFrame  == cTypeFrameVarSize)
      {
        Donnees.Lire(m_BufferSizeRef, &m_CurrentSize);
        // Verification de la taille demande
        if(m_CurrentSize <= m_MaxSize)
        {
          pMsg->Lng = (U16)(m_CurrentSize & 0xFFFF);

          // Initilisation de la position en tete de liste
          pRefdonnee =  m_ListeDonnee.GetHead();

          //Check if there is mapped data
          if(pRefdonnee == NULL)
          {
            Donnees.Lire(m_BufferRef, m_pBufferTemp);
            memcpy(m_pBufferTemp, pMsg->pBuffer, m_CurrentSize);
          }
          else
          {
            //Used datas values

              // Parcours de la liste
              while(pRefdonnee != NULL)
              {
                // Lecture de la donnee dans le message
                Res = pRefdonnee->Lire(pMsg);
            
                // Donnee suivante
                pRefdonnee  = pRefdonnee->m_pNext;
              }
          }  
          
          // Sauvegarde de la trame
          memcpy(m_pBufferSave, pMsg->pBuffer, m_CurrentSize);
          m_FlagModif = cFalse;
        }
        else Res = mLDBPCErreur(cLdbpcErrTrame);
      }
    }
    else	Res = mLDBPCErreur(cLdbpcErrTrame);
  }
  else
  {
    // Sauvegarde de la trame
    memcpy(pMsg->pBuffer, m_pBufferSave, m_CurrentSize);
  }
  return Res;
}

//--------------------------------------------------------------------------
// Ecrire une trame
//--------------------------------------------------------------------------
tLDBPCStatut tcTrame::Ecrire(tMsg * pMsg)
{
  BOOL bParcours = cTrue;
  tLDBPCStatut Res = cLdbpcErr;
  tcRefDonnee * pRefdonnee;
  tMsg Message;
  
  // GG : 12/04/2002
#ifndef OPTIMISATION_LDBPC_TRAME
  m_FlagModif = cTrue;
#endif
  
  if(!(mTrameSortie(m_TypeFlux)) || (!pMsg) || (!(pMsg->pBuffer)) || (pMsg->Lng <= 0))
  {
    return(mLDBPCErreur(cLdbpcErrEcritureDonnee));
  }
  
  // Type de Trame
  if((m_TypeFrame == cTypeFrameFixSize) && (pMsg->Lng == m_MaxSize))
  {
    if((memcmp(m_pBufferSave, pMsg->pBuffer, pMsg->Lng) == 0) && (m_FlagModif == cFalse))
    {
      return(cLdbpcOk);
    }
    // Affectation du message
    Message.pBuffer = m_pBufferTemp;
    Message.Lng = (U16)pMsg->Lng;
    if(Message.pBuffer)
    {
      // Copie du message
      memcpy(Message.pBuffer, pMsg->pBuffer, pMsg->Lng);
      Res = cLdbpcOk;
    }
    else 
      Res = mLDBPCErreur(cLdbpcErrAllocMem);
    
    if(Res == cLdbpcOk)
    {
      // Initilisation de la position en tete de liste
      pRefdonnee = m_ListeDonnee.GetHead();
      
      // Parcours de la liste
      while(pRefdonnee != NULL)
      {
        // Ecriture de la donnee a partir du le message
        Res = pRefdonnee->Ecrire(&Message);
        
        // Donnee suivante
        pRefdonnee  = pRefdonnee->m_pNext;
      }
      // Sauvegarde de la trame
      memcpy(m_pBufferSave, m_pBufferTemp, pMsg->Lng);
      m_FlagModif = cFalse;
      Res = cLdbpcOk;
    }
  }
  else if((m_TypeFrame == cTypeFrameVarSize) && (pMsg->Lng <= m_MaxSize))
  {
    if((memcmp(m_pBufferSave, pMsg->pBuffer, pMsg->Lng) != 0) || (m_FlagModif == cTrue))
    {
      Donnees.EcrireSortie(m_BufferRef, pMsg->pBuffer);
      memcpy(m_pBufferTemp, pMsg->pBuffer, pMsg->Lng);
      // Sauvegarde de la trame
      memcpy(m_pBufferSave, pMsg->pBuffer, pMsg->Lng);
      m_FlagModif = cFalse;
    }

    if((m_CurrentSize != pMsg->Lng) || (m_FlagModif == cTrue))
    {
      Donnees.EcrireSortie(m_BufferSizeRef,pMsg->Lng);
      // Sauvegarde de la trame
      m_CurrentSize = pMsg->Lng;
      m_FlagModif = cFalse;
    }
    Res = cLdbpcOk;
  }
  else
  {
    return(mLDBPCErreur(cLdbpcErrEcritureDonnee));
  }
  return Res;
}

//--------------------------------------------------------------------------
// CallBack Statique
//--------------------------------------------------------------------------
void tcTrame::CallBackEvents(tpParam pParam1, tpParam pParam2)
{
  ((tcTrame *)pParam1)->OnModification();
}

//--------------------------------------------------------------------------
// Modification d'une  donnee
//--------------------------------------------------------------------------
void tcTrame::OnModification(void)
{
  m_FlagModif = cTrue;
}

//--------------------------------------------------------------------------
//--------------- Implementation de la classe tcTrameFi -------------------
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// Constructeurs
//--------------------------------------------------------------------------
tcTrameFi::tcTrameFi()
{
  m_Duree = 0; 
}

tcTrameFi::tcTrameFi(tInfoBuildFrame * pBuildFrame) : tcTrame(pBuildFrame)
{
  m_Duree = 0;
  m_pCallBackMsgSeg = pBuildFrame->pInfoFrame->pCallBackMsgSeg;
  m_pParamCallBackMsgSeg = pBuildFrame->pInfoFrame->pParamCallBackMsgSeg;
} 

//--------------------------------------------------------------------------
// Destructeur
//--------------------------------------------------------------------------
tcTrameFi::~tcTrameFi()
{
  
}

//--------------------------------------------------------------------------
//	Lire la duree du temps simule de transmission de la trame
//--------------------------------------------------------------------------
tDelay tcTrameFi::LireDuree(void) const
{ 
  return m_Duree;
}

//--------------------------------------------------------------------------
//	Ecrire la duree du temps simule de transmission de la trame
//--------------------------------------------------------------------------
void tcTrameFi::EcrireDuree(tDelay duree) 
{ 
  m_Duree = duree; 
}

//--------------------------------------------------------------------------
// Emission de l'evenement pour la simulation
//--------------------------------------------------------------------------
void tcTrameFi::EmissionEvt(void)
{
  if(m_RefEvt != -1)
  {
    Donnees.EmettreEvtSor(m_RefEvt);
  }
  // Traitement des messages segmentés
  if(m_pCallBackMsgSeg != NULL)
  {
    tMsg Message;
    // Affectationdu message
    Message.pBuffer = m_pBufferTemp;
    Message.Lng = (U16)m_CurrentSize;
    
    m_pCallBackMsgSeg(m_pParamCallBackMsgSeg,(tpParam)&Message);
  }
}

//--------------------------------------------------------------------------
//--------------- Implementation de la classe tcTrameFni ------------------
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// Constructeurs
//--------------------------------------------------------------------------
tcTrameFni::tcTrameFni()
{
  m_RefMode	=0	;	// Entree corespondant au mode
  m_Phase		=0	;	// Retard de la trame
  m_Periode	=0	;	// Periode de la trame
}

tcTrameFni::tcTrameFni(tInfoBuildFrame * pBuildFrame) : tcTrame(pBuildFrame)
{
  m_RefMode	=0	;	// Entree corespondant au mode
  m_Phase		=0	;	// Retard de la trame
  m_Periode	=0	;	// Periode de la trame
}

//--------------------------------------------------------------------------
// Destructeur
//--------------------------------------------------------------------------
tcTrameFni::~tcTrameFni()
{
  
}

void tcTrameFni::Initialiser()
{
  m_FlagModif = cTrue;
  if(m_Periode)
  {
    // PON URD42 DEV 105 / PON URD45 BODY_SW 11 
    if(m_Phase != 0)
    {
      m_Tempo.Duree = m_Phase;
    }
    else
    {
      m_Tempo.Duree = m_Periode;
    }
    m_Tempo.Duree = m_Phase;
    m_Tempo.EstPeriodique = cTrue;
    m_Tempo.pObject = this;
    m_Tempo.pCallBack = &FinTempos;
    Timer.SupprimerTempo(&m_Tempo);
    ArmerTempo();
  }
}

void tcTrameFni::FinTempos(tcTrameFni* pTrame) // static
{ 
  if(pTrame)
  {
    pTrame->FinTempo(); 
  }
  else
  {
    mLDBPCErreur(cLdbpcErrTrame);
  }
}

void tcTrameFni::FinTempo()
{	
  char Mode;
  
  // PON URD42 DEV 105 / PON URD45 BODY_SW 11 
  m_Tempo.Duree = m_Periode;
  
  // Lecture du mode
  LireMode(&Mode);
  if(Mode == cModeAuto)
  {
    // Action Spontannee
    Action();
  }
}

void tcTrameFni::ArmerTempo()
{
  Timer.AjouterTempo(&m_Tempo);
}


//--------------------------------------------------------------------------
// Ecrire la reference du mode, le retard et la periode de la trame
//--------------------------------------------------------------------------
void tcTrameFni::EcrireDeclencheur(S32 RefMode, tDelay Phase, tDelay Periode)
{
  m_RefMode	= RefMode;	// Entree corespondant au mode
  m_Phase		= Phase;	// Retard de la trame
  m_Periode	= Periode;	// Periode de la trame
}

//--------------------------------------------------------------------------
// Lecture du mode
//--------------------------------------------------------------------------
void tcTrameFni::LireMode(char * mode)
{
  U32 ulMode;
  if(mode)
  {
    Donnees.Lire(m_RefMode, &ulMode, NULL, NULL);
    *mode = (char)ulMode;
  }
}

//--------------------------------------------------------------------------
//--------------- Implementation de la classe tcTrameFnip -----------------
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// Constructeurs
//--------------------------------------------------------------------------
tcTrameFnip::tcTrameFnip()
{
  m_pEmissionSp	=	NULL;
  m_MsgPreparee.pBuffer = NULL;
  m_MsgPreparee.Lng = 0;
}

tcTrameFnip::tcTrameFnip(tInfoBuildFrame * pBuildFrame) : tcTrameFni(pBuildFrame)
{
  m_pEmissionSp	=	NULL;
  m_MsgPreparee.pBuffer = NULL;
  m_MsgPreparee.Lng = (U16)pBuildFrame->pInfoFrame->MaxSize;
  m_pBufferTempFnip = (U8*) new U8[m_MsgPreparee.Lng*sizeof(U8)];
}

//--------------------------------------------------------------------------
// Destructeur
//--------------------------------------------------------------------------
tcTrameFnip::~tcTrameFnip()
{
  // Destruction du buffer temporaire
  if(m_pBufferTempFnip)	
    delete [] m_pBufferTempFnip;
}

void tcTrameFnip::Initialiser()
{
  // GG : 22/01/2002
  tcTrameFni::Initialiser();
  m_MsgPreparee.pBuffer = NULL;
}

//--------------------------------------------------------------------------
// Mise à jour la reference du mode, le retard et la periode de la trame
//--------------------------------------------------------------------------
void tcTrameFnip::MajDeclencheur(S32 RefMode, tDelay Phase, tDelay Periode
                                 , tpCallBackStatusAddr cbTrameNIP)
{
  // Ecrire la reference du mode, le retard et la periode de la trame
  EcrireDeclencheur(RefMode, Phase * cLDBTick, Periode * cLDBTick);
  
  // Mise à jour de la callback
  m_pEmissionSp	=	cbTrameNIP;
}

//--------------------------------------------------------------------------
// Preparer un message
//--------------------------------------------------------------------------
void tcTrameFnip::Preparer(tMsg * pMsg)
{
  if(pMsg->Lng == m_CurrentSize)
  {
    // Allocation du buffer
    m_MsgPreparee.pBuffer = m_pBufferTempFnip;
    if(m_MsgPreparee.pBuffer)
    {
      // Copie du buffer
      memcpy(m_MsgPreparee.pBuffer, pMsg->pBuffer, m_CurrentSize);
    }
    else mLDBPCErreur(cLdbpcErrTrame);
  }
  else mLDBPCErreur(cLdbpcErrTrame);
}

//--------------------------------------------------------------------------
// Produire les donnees
//--------------------------------------------------------------------------
tLDBPCStatut tcTrameFnip::Produire(void)
{
  tLDBPCStatut Res = cLdbpcErr;
  
  if(m_MsgPreparee.pBuffer)
  {
    // Production des donnees
    Res = Ecrire(&m_MsgPreparee);
  }
  return Res;
}

//--------------------------------------------------------------------------
// Emission spontannee
//--------------------------------------------------------------------------
void tcTrameFnip::EmissionSpontanee(void)
{
  if(m_MsgPreparee.pBuffer && m_pEmissionSp)
  {
    tDelay Time;
    Timer.LireDate(&Time);
    m_pCanal->m_SADAdrTrace.SADAdrFrameTraceTx(m_Adresse,m_CurrentSize,m_pBufferTemp,(tU32Bit)(Time/100000UL));
    // Emission de la callback
    m_pEmissionSp(m_Adresse, cLDBCorrect);
  }
}	

//--------------------------------------------------------------------------
// Action spontannee
//--------------------------------------------------------------------------
void tcTrameFnip::Action()
{
  if(m_MsgPreparee.pBuffer)
  {
    // Production des donnees
    if(Ecrire(&m_MsgPreparee) == cLdbpcOk)
    {
      if(m_pCanal->LireAutorisation() || (m_RefFlux == -1))
      {
        if(m_pEmissionSp)
        {
          // Emission de la callback
          m_pEmissionSp(m_Adresse, cLDBCorrect);
        }
        else mLDBPCErreur(cLdbpcErrTrame);
      }
    }
    else mLDBPCErreur(cLdbpcErrTrame);
  }
  else mLDBPCErreur(cLdbpcErrTrame);
}

//--------------------------------------------------------------------------
//--------------- Implementation de la classe tcTrameFnic -----------------
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// Constructeurs
//--------------------------------------------------------------------------
tcTrameFnic::tcTrameFnic()
{
  m_pReceptionSp	=	NULL;
}

tcTrameFnic::tcTrameFnic(tInfoBuildFrame * pBuildFrame) : tcTrameFni(pBuildFrame)
{
  m_pReceptionSp	=	NULL;
}

//--------------------------------------------------------------------------
// Destructeur
//--------------------------------------------------------------------------
tcTrameFnic::~tcTrameFnic()
{
  
}


//--------------------------------------------------------------------------
// Mise à jour la reference du mode, le retard et la periode de la trame
//--------------------------------------------------------------------------
void tcTrameFnic::MajDeclencheur(S32 RefMode, tDelay Phase, tDelay Periode
                                 ,tpCallBackRxWithAddr cbTrameNIC)
{
  // Ecrire la reference du mode, le retard et la periode de la trame
  EcrireDeclencheur(RefMode, Phase * cLDBTick, Periode * cLDBTick);
  
  // Mise à jour de la callback
  m_pReceptionSp	=	cbTrameNIC;
}

//--------------------------------------------------------------------------
// Reception spontanee
//--------------------------------------------------------------------------
void tcTrameFnic::ReceptionSpontanee(void) 
{
  tLDBPCStatut Res;
  tMsg Msg ;
  
  // Affectation du message
  Msg.pBuffer = m_pBufferTemp;
  Msg.Lng = (U16) m_CurrentSize;
  
  // Lecture des donnees
  Res = Lire(&Msg);
  
  // Emission de la callback
  if(Res && m_pReceptionSp)
  {
    tDelay Time;
    Timer.LireDate(&Time);
    m_pCanal->m_SADAdrTrace.SADAdrFrameTraceRx(m_Adresse,m_CurrentSize,m_pBufferTemp,(tU32Bit)(Time/100000UL));
    m_pReceptionSp(m_Adresse, cLDBCorrect ,&Msg);
  }
}

//--------------------------------------------------------------------------
// Action spontannee
//--------------------------------------------------------------------------
void tcTrameFnic::Action()
{
  if(m_pCanal->LireAutorisation() || (m_RefFlux == -1))
  {
    ReceptionSpontanee();
  }
}