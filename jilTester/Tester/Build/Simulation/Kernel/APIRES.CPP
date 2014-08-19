/*============================================================================
  Project ......................... Common
  Component ....................... ApiRes
  File revision.................... $Revision
  Last modification date .......... $Modtime
  -------------------------------------------------------------------------
  Copyright ... This software is JCI property. Duplication or
                disclosure is prohibited without JCI written permission
  ------------------------------------------------------------------------- 

  - Macros, constants and types which are not exported are defined in 
    this file
  - Variables and functions which are not exported are defined in this 
    file with the static key word
  
  -------------------------------------------------------------------------
  Comments about the component (role, algorithm, structure, limitations,
           defined tasks and events...)

  - Role : C/C++ Interface for Resources Management (Channels, Flow, Frames)
  
  -------------------------------------------------------------------------
  $Workfile:   APIRES.CPP  $ file review : 
  $Log

	v1.0 :	GG		: 20/04/2000	: Creation
	v1.1 :	GG		: 21/11/2001	: Update for SM1003 project
	v1.2 :	GG & MG : 13/03/2002	: After adding CAN Layers

  ==========================================================================*/

/*--------------------------------------------------------------------------
  Body Identification
  --------------------------------------------------------------------------*/
#define ApiParam "ApiParam"

/*-------------------------------------------------------------------------
  Included files

  #include <system_file_name.h>
  #include "project_file_name.h"
  --------------------------------------------------------------------------*/

#include "Config.h"
#include "Ldbpc.h"			// Definition of types and basis constants
#include "LdbpcRes.h"		// Definition of Resource Module Interface
#include "tcCanalCan.h"		// Define tcTrameMsgCan Class Interface 

/*============================================================================
  =========================== EXPORTED FUNCTIONS =============================
  ==========================================================================*/

//--------------------------------------------------------------------------
//------------------------------ Configuration API -------------------------
//-------------------------- RESOURCES MODULE Interface --------------------
//--------------------------------------------------------------------------

// ------------------------------------------------------------------------
// Creation of a Channel
// ------------------------------------------------------------------------
BOOL RESCreerCanal(tChannel RefCan, char * pNom
				, tCallBackCanal * pStructCallBack, tpCanCBCtrl pCbControler
				, tpCanCBAutorise pCbAutorise)
{
  pStructCallBack->ChannelId = RefCan;
  strcpy(pStructCallBack->ChannelName,pNom);
  pStructCallBack->pCbControl  =   pCbControler;
  pStructCallBack->pCbEnable   =   pCbAutorise;

  return(Ressources.CreateChannel(pStructCallBack));
}

BOOL RESCreateChannel(tCallBackCanal * pStructCallBack)
{
  return(Ressources.CreateChannel(pStructCallBack));
}

BOOL RESCreateChannelXCAN(tXCanChannel * pStruct)
{
  return(Ressources.CreateChannelXCAN(pStruct));
}

void RESSetCurrentConfig(char * ConfigName)
{
    Ressources.SetXCANCurrentConfig(ConfigName);
}

// ------------------------------------------------------------------------
// Creation of an input Control
// ------------------------------------------------------------------------
BOOL RESCreerControleEnt(S32 * pRef, tChannel RefCan, char * pNom
							 , tCtrl Ctrl)
{
	return(Ressources.CreerControle(pRef, RefCan, pNom, Ctrl, 0,cDLLEntree ));
}

// ------------------------------------------------------------------------
// Creation of an output Control
// ------------------------------------------------------------------------
BOOL RESCreerControleSor(S32 * pRef, tChannel RefCan, char * pNom
							 , tCtrl Ctrl, tDelay Duree)
{
	return(Ressources.CreerControle(pRef, RefCan, pNom, Ctrl, Duree, cDLLSortie));
}

// ------------------------------------------------------------------------
// Creation of an Initiated flow
// ------------------------------------------------------------------------
BOOL RESCreerFluxI(S32 * pRef, tChannel RefCan, tLdbpcTypeFlux TypeFlux
					   , tpFluCBActionI pCbAction)
{
	tInfoFlux Flux;
	Flux.pRef = pRef;
	Flux.RefCan = RefCan;
	Flux.TypeFlux = TypeFlux;
	Flux.pCbActionNIC = NULL;
	Flux.pCbActionNIP = NULL;
	Flux.pCbActionI = pCbAction;
	
	return(Ressources.CreerFlux(&Flux));
}

// ------------------------------------------------------------------------
// Creation of a Consumed not intiated flow
// ------------------------------------------------------------------------
BOOL RESCreerFluxNI(S32 * pRef, tChannel RefCan, tLdbpcTypeFlux TypeFlux
						, tpFluCBActionNI pCbAction)
{
	tInfoFlux Flux;
	Flux.pRef = pRef;
	Flux.RefCan = RefCan;
	Flux.TypeFlux = TypeFlux;
	Flux.pCbActionNIC = pCbAction;
	Flux.pCbActionNIP = NULL;
	Flux.pCbActionI = NULL;
	
	return(Ressources.CreerFlux(&Flux));
}

// ------------------------------------------------------------------------
// Creation of a Produced not intiated flow
// ------------------------------------------------------------------------
BOOL RESCreerFluxNIP(S32 * pRef, tChannel RefCan, tpFluCBActionNIP pCbAction)
{
	tInfoFlux Flux;
	Flux.pRef = pRef;
	Flux.RefCan = RefCan;
	Flux.TypeFlux = cFluxNIP;
	Flux.pCbActionNIC = NULL;
	Flux.pCbActionNIP = pCbAction;
	Flux.pCbActionI = NULL;
	
	return(Ressources.CreerFlux(&Flux));
}

// ------------------------------------------------------------------------
// Creation of a generic frame
// ------------------------------------------------------------------------
BOOL RESCreerTrame(tInfoTrame * pInfoTrame)
{
  return(Ressources.CreateFrame(pInfoTrame) == cLdbpcOk);
}

// ------------------------------------------------------------------------
// Creation of a frame link to a initated flow
// ------------------------------------------------------------------------
BOOL RESCreerTrameFI(S32 * pRef, S32 RefFlux, char * pNom
, tAddress Adresse, U32 TailleOctet, tLdbpcTypeFlux TypeFlux, tDelay Duree, tTypeFrame TypeFrame)
{
    tInfoTrame IT;

    memset(&IT,0, sizeof(tInfoTrame));
    IT.pRef = pRef;
    IT.RefFlux = RefFlux;
    IT.pName = pNom;
    IT.Address = Adresse;
    IT.MaxSize = TailleOctet;
    IT.TypeFlux = TypeFlux;
    IT.TxTime = Duree;
    IT.pGroupName = NULL;
    IT.TypeFrame = TypeFrame;
    IT.RxMode = 0;
    IT.RxPeriod = 0;
    IT.RxPhase = 0;
    IT.pRxNICCallBackFrame = NULL;
    IT.pRxNIPCallBackFrame = NULL;
    IT.pCallBackMsgSeg = NULL;
    IT.pParamCallBackMsgSeg = NULL;

    return(Ressources.CreateFrame(&IT) == cLdbpcOk);
}

// ------------------------------------------------------------------------
// Creation of a frame unlink to initiated flow
// ------------------------------------------------------------------------
BOOL RESCreerTrameFISA(S32 * pRef, char * pNom, tAddress Adresse
, U32 TailleOctet, char * pGroupe, tLdbpcTypeFlux TypeFlux, tDelay Duree, tTypeFrame TypeFrame)
{
    tInfoTrame IT;

    memset(&IT,0, sizeof(tInfoTrame));
    IT.pRef = pRef;
    IT.RefFlux = -1;
    IT.pName = pNom;
    IT.Address = Adresse;
    IT.MaxSize = TailleOctet;
    IT.TypeFlux = TypeFlux;
    IT.TxTime = Duree;
    IT.pGroupName = NULL;
    IT.TypeFrame = TypeFrame;
    IT.RxMode = 0;
    IT.RxPeriod = 0;
    IT.RxPhase = 0;
    IT.pRxNICCallBackFrame = NULL;
    IT.pRxNIPCallBackFrame = NULL;
    IT.pCallBackMsgSeg = NULL;
    IT.pParamCallBackMsgSeg = NULL;

    return(Ressources.CreateFrame(&IT) == cLdbpcOk);
}

// ------------------------------------------------------------------------
// Creation of a frame link to a Consumed not intiated flow
// ------------------------------------------------------------------------
BOOL RESCreerTrameFnic(S32 * pRef, S32 RefFlux, char * pNom
, tAddress Adresse, U32 TailleOctet, char Mode
, tDelay Periode, tDelay Phase, tpCallBackRxWithAddr pCbTrameNIC, tTypeFrame TypeFrame)
{
    tInfoTrame IT;

    memset(&IT,0, sizeof(tInfoTrame));
    IT.pRef = pRef;
    IT.RefFlux = RefFlux;
    IT.pName = pNom;
    IT.Address = Adresse;
    IT.MaxSize = TailleOctet;
    IT.TypeFlux = cFluxNIC;
    IT.TxTime = 0;
    IT.pGroupName = NULL;
    IT.TypeFrame = TypeFrame;
    IT.RxMode = Mode;
    IT.RxPeriod = Periode;
    IT.RxPhase = Phase;
    IT.pRxNICCallBackFrame = pCbTrameNIC;
    IT.pRxNIPCallBackFrame = NULL;
    IT.pCallBackMsgSeg = NULL;
    IT.pParamCallBackMsgSeg = NULL;

    return(Ressources.CreateFrame(&IT) == cLdbpcOk);
}

// ------------------------------------------------------------------------
// Creation of a frame unlink to a consumed not intiated flow
// ------------------------------------------------------------------------
BOOL RESCreerTrameFnicSA(S32 * pRef, char * pNom, tAddress Adresse
, U32 TailleOctet, char * pGroupe, char Mode
, tDelay Periode, tDelay Phase, tpCallBackRxWithAddr pCbTrameNIC, tTypeFrame TypeFrame)
{
    tInfoTrame IT;

    memset(&IT,0, sizeof(tInfoTrame));
    IT.pRef = pRef;
    IT.RefFlux = -1;
    IT.pName = pNom;
    IT.Address = Adresse;
    IT.MaxSize = TailleOctet;
    IT.TypeFlux = cFluxNIC;
    IT.TxTime = 0;
    IT.pGroupName = pGroupe;
    IT.TypeFrame = TypeFrame;
    IT.RxMode = Mode;
    IT.RxPeriod = Periode;
    IT.RxPhase = Phase;
    IT.pRxNICCallBackFrame = pCbTrameNIC;
    IT.pRxNIPCallBackFrame = NULL;
    IT.pCallBackMsgSeg = NULL;
    IT.pParamCallBackMsgSeg = NULL;

    return(Ressources.CreateFrame(&IT) == cLdbpcOk);
}

// ------------------------------------------------------------------------
// Creation of a frame link to a produced not initiated flow
// ------------------------------------------------------------------------
BOOL RESCreerTrameFnip(S32 * pRef, S32 RefFlux, char * pNom
, tAddress Adresse, U32 TailleOctet, char Mode
	, tDelay Periode, tDelay Phase, tpCallBackStatusAddr pCbTrameNIP)
{
    tInfoTrame IT;

    memset(&IT,0, sizeof(tInfoTrame));
    IT.pRef = pRef;
    IT.RefFlux = RefFlux;
    IT.pName = pNom;
    IT.Address = Adresse;
    IT.MaxSize = TailleOctet;
    IT.TypeFlux = cFluxNIP;
    IT.TxTime = 0;
    IT.pGroupName = NULL;
    IT.TypeFrame = cTypeFrameFixSize;
    IT.RxMode = Mode;
    IT.RxPeriod = Periode;
    IT.RxPhase = Phase;
    IT.pRxNICCallBackFrame = NULL;
    IT.pRxNIPCallBackFrame = pCbTrameNIP;
    IT.pCallBackMsgSeg = NULL;
    IT.pParamCallBackMsgSeg = NULL;

    return(Ressources.CreateFrame(&IT) == cLdbpcOk);
}

// ------------------------------------------------------------------------
// Creation of a frame unlink to a produced not initiated flow
// ------------------------------------------------------------------------
BOOL RESCreerTrameFnipSA(S32 * pRef, char * pNom
, tAddress Adresse, U32 TailleOctet, char * pGroupe, char Mode
	, tDelay Periode, tDelay Phase, tpCallBackStatusAddr pCbTrameNIP)
{
    tInfoTrame IT;

    memset(&IT,0, sizeof(tInfoTrame));
    IT.pRef = pRef;
    IT.RefFlux = -1;
    IT.pName = pNom;
    IT.Address = Adresse;
    IT.MaxSize = TailleOctet;
    IT.TypeFlux = cFluxNIP;
    IT.TxTime = 0;
    IT.pGroupName = pGroupe;
    IT.TypeFrame = cTypeFrameFixSize;
    IT.RxMode = Mode;
    IT.RxPeriod = Periode;
    IT.RxPhase = Phase;
    IT.pRxNICCallBackFrame = NULL;
    IT.pRxNIPCallBackFrame = pCbTrameNIP;
    IT.pCallBackMsgSeg = NULL;
    IT.pParamCallBackMsgSeg = NULL;

    return(Ressources.CreateFrame(&IT) == cLdbpcOk);
}

// ------------------------------------------------------------------------
// Creation of an output < 32bits
// ------------------------------------------------------------------------
BOOL RESCreerSortieV(S32 * pRef, S32 RefTrame, char * pNom
, U32 TailleBit, U32 ValeurInit, U32 Position)
{
	return(Ressources.CreerSortie(pRef, RefTrame, pNom, TailleBit, ValeurInit
		, Position));
}


// ------------------------------------------------------------------------
// Creation of an output > 32bits
// ------------------------------------------------------------------------
BOOL RESCreerSortieB(S32 * pRef, S32  RefTrame, char * pNom
, U32 TailleBit, U8 * pBufferInit, U32 Position)
{
	return(Ressources.CreerSortie(pRef, RefTrame, pNom, TailleBit, pBufferInit
		, Position));
}

// ------------------------------------------------------------------------
// Creation of an input < 32bits
// ------------------------------------------------------------------------
BOOL RESCreerEntreeV(S32 * pRef, S32 RefTrame, char * pNom
, U32 TailleBit, U32 ValeurInit, U32 Position)
{
	return(Ressources.CreerEntree(pRef, RefTrame, pNom, TailleBit, ValeurInit
		, Position));
}

// ------------------------------------------------------------------------
// Creation of an input > 32bits
// ------------------------------------------------------------------------
BOOL RESCreerEntreeB(S32 * pRef, S32 RefTrame, char * pNom
, U32 TailleBit, U8 * pBufferInit, U32 Position)
{
	return(Ressources.CreerEntree(pRef, RefTrame, pNom, TailleBit, pBufferInit
		, Position));
}

// ------------------------------------------------------------------------
// Creation of an input/output < 32bits
// ------------------------------------------------------------------------
BOOL RESCreerEntSorV(S32 * pRef, S32 RefTrame, char * pNom
, U32 TailleBit, U32 ValeurInit, U32 Position)
{
	return(Ressources.CreerEntSor(pRef, RefTrame, pNom, TailleBit, ValeurInit
		, Position));
}

// ------------------------------------------------------------------------
// Creation of an input/output > 32bits
// ------------------------------------------------------------------------
BOOL RESCreerEntSorB(S32 * pRef, S32 RefTrame, char * pNom
, U32 TailleBit, U8 * pBufferInit, U32 Position)
{
	return(Ressources.CreerEntSor(pRef, RefTrame, pNom, TailleBit, pBufferInit
		, Position));
}

// ------------------------------------------------------------------------
// Link a Data to a frame
// ------------------------------------------------------------------------
BOOL RESAttacherDonnee(S32 RefDonnee, S32 RefTrame, U32 Position)
{
	return(Ressources.AttacherDonnee(RefDonnee, RefTrame, Position));
}

// ------------------------------------------------------------------------
// Read a flow reference
// ------------------------------------------------------------------------
BOOL RESLireRefFlux(tChannel RefCan, tLdbpcTypeFlux TypeFlux, S32 * pRefFlux)
{
	return(Ressources.LireRefFlux(RefCan, TypeFlux, pRefFlux));
}

// ------------------------------------------------------------------------
// Read a frame reference by its flow
// ------------------------------------------------------------------------
BOOL RESLireRefTrameFlux(S32 RefFlux, tAddress Adresse
							 , S32 * pRefTrame)
{
	return(Ressources.LireRefTrame(RefFlux, Adresse, pRefTrame));
}

// ------------------------------------------------------------------------
// Read a frame reference by its channel
// ------------------------------------------------------------------------
BOOL RESLireRefTrameCanal(tChannel RefCan, tLdbpcTypeFlux TypeFlux, tAddress Adresse
						 , S32 * pRefTrame)
{
	return(Ressources.LireRefTrame(RefCan, TypeFlux, Adresse, pRefTrame));
}

// ------------------------------------------------------------------------
// Read a frame 
// ------------------------------------------------------------------------
BOOL RESLireTrame(S32 RefTrame, tMsg * pMsg)
{
	return(Ressources.LireTrame(RefTrame, pMsg));
}

// ------------------------------------------------------------------------
// Read the current frame of an initiated flow
// ------------------------------------------------------------------------
BOOL RESLireTrameCourante(S32 RefFlux, tAddress  * pAdresse
							  , tMsg ** ppMsg)
{
	return(Ressources.LireTrameCourante(RefFlux, pAdresse, ppMsg));
}

// ------------------------------------------------------------------------
// Read the control state of the channel
// ------------------------------------------------------------------------
BOOL RESLireEtatControle(tChannel RefCan, char * pEtat)
{
	return(Ressources.LireEtatControle(RefCan, pEtat));
}

// ------------------------------------------------------------------------
// Write a frame
// ------------------------------------------------------------------------
BOOL RESEcrireTrame(S32 RefTrame, tMsg * pMsg)
{
	return(Ressources.EcrireTrame(RefTrame, pMsg));
}

// ------------------------------------------------------------------------
// Write the current frame of a flow
// ------------------------------------------------------------------------
BOOL RESEcrireTrameCourante(S32 RefFlux, tAddress Adresse, tMsg * pMsg)
{
	return(Ressources.EcrireTrameCourante(RefFlux, Adresse, pMsg));
}

// ------------------------------------------------------------------------
// Write the control state of the channel
// ------------------------------------------------------------------------
BOOL RESEcrireEtatControle(tChannel RefCan, char Etat)
{
	return(Ressources.EcrireEtatControle(RefCan, Etat));
}

//--------------------------------------------------------------------------
// Send the current message of an initiated flow to a LDBPC Channel
//--------------------------------------------------------------------------
void RESEmissionStd(tChannel RefCan)
{
	Ressources.ActionFiStd(cFluxIP, RefCan);
}

//--------------------------------------------------------------------------
// Receive the current message of an initiated flow to a LDBPC Channel
//--------------------------------------------------------------------------
void RESReceptionStd(tChannel RefCan)
{
	Ressources.ActionFiStd(cFluxIC, RefCan);
}

// ------------------------------------------------------------------------
// Process the transmission or the reception of an initiated flow to a
// LDBPC Channel And Call the end process callback
// ------------------------------------------------------------------------
void RESTraiterFiStd(S32 RefFlux)
{
	Ressources.FinActionFi(RefFlux);
}

// ------------------------------------------------------------------------
// Spontaneous standard transmission of a not initiated flow to the DAT
// ------------------------------------------------------------------------
void RESEmissionSpontaneeStd(tChannel RefCan, S32 RefTrame)
{
	Ressources.ActionFniStd(RefCan, RefTrame, cFluxNIP);
}

// ------------------------------------------------------------------------
// Spontaneous standard receive of a not initiated flow to the DAT
// ------------------------------------------------------------------------
void RESReceptionSpontaneeStd(tChannel RefCan, U32 RefTrame)
{
	Ressources.ActionFniStd(RefCan, RefTrame, cFluxNIC);
}

// ------------------------------------------------------------------------
// Standard transmission of a control 
// ------------------------------------------------------------------------
void RESControleStd(tChannel RefCan,tCtrl ctrl,tMsg * pMsg)
{
	Ressources.ControleStd(RefCan, ctrl);
}

// ------------------------------------------------------------------------
// Read the control reference
// ------------------------------------------------------------------------
BOOL RESLireRefCtrl(S32 * refCtrl,tChannel RefCan,tCtrl ctrl)
{
	return Ressources.LireRefCtrl(refCtrl, RefCan, ctrl);
}

// ------------------------------------------------------------------------
// Process of the control transmission to a LDBPC channel and Call the end
// processing callback
// ------------------------------------------------------------------------
void RESTraiterCtrlStd(S32 refCtrl)
{
	Ressources.FinControle(refCtrl);
}

// ------------------------------------------------------------------------
// Send a control the the DAT Layer
// ------------------------------------------------------------------------
void RESControleSpontanee(S32 refCtrl)
{
	Ressources.CBControler(refCtrl);
}

// ------------------------------------------------------------------------
// Write the Time transmission of a frame
// ------------------------------------------------------------------------
BOOL RESEcrireDureeTrame(tAddress Adresse, S32 RefFlux, tDelay Duree)
{
	return(Ressources.EcrireDureeTrame(Adresse, RefFlux, Duree));
}

// ------------------------------------------------------------------------
// Read the mode of the frame
// ------------------------------------------------------------------------
BOOL RESLireModeTrame(S32 RefTrame, char * Mode)
{
	return(Ressources.LireModeTrame(RefTrame, Mode));
}

// ------------------------------------------------------------------------
// Send a not initiated flow
// ------------------------------------------------------------------------
void RESActionFNI(S32 RefTrame)
{
	Ressources.FinTempo(RefTrame);
}

// ------------------------------------------------------------------------
// Set the transfer on INTEL or MOTOROLA format
// ------------------------------------------------------------------------
void RESEcrireFormat(tChannel RefCan,U8 Format)
{
	Ressources.Formater(RefCan,Format);
}

// ------------------------------------------------------------------------
// Set the forced update of the frame 
// ------------------------------------------------------------------------
void RESEcrireDmdeMoficationTrame(S32 RefTrame, BOOL flag)
{
	Ressources.EcrireDmdeMoficationTrame(RefTrame, flag);
}

// ------------------------------------------------------------------------
// Get the forced update state of the frame 
// ------------------------------------------------------------------------
BOOL RESLireDmdeMoficationTrame(S32 RefTrame)
{
	return(Ressources.LireDmdeMoficationTrame(RefTrame));
}

#ifdef CANAL_CAN      // if the CAN Channel is used

// ------------------------------------------------------------------------
// Create a segmented message
// ------------------------------------------------------------------------
BOOL RESCreerMsgSeg( tParamMsgSeg * ParamMsgSeg, S32 RefCan)
{
	return(CanalCan.CreerMsgSeg(ParamMsgSeg,RefCan));
}

// ------------------------------------------------------------------------
// Create an acknowledged segmented message
// ------------------------------------------------------------------------
BOOL RESCreerMsgSegAck( tParamMsgSeg * ParamMsgSeg, S32 RefCan)
{
	return(CanalCan.CreerMsgSegAck(ParamMsgSeg,RefCan));
}

// ------------------------------------------------------------------------
// Create a session acknowledged segmented message
// ------------------------------------------------------------------------
BOOL RESCreerMsgSegSession( tParamMsgSeg * ParamMsgSeg, S32 RefCan)
{
	return(CanalCan.CreerMsgSegSession(ParamMsgSeg,RefCan));
}

// ------------------------------------------------------------------------
// Configure the CAN layer with no padding
// ------------------------------------------------------------------------
void RESSetCanNoPadding(BOOL CanNoPadding)
{
	CanalCan.SetCanNoPadding(CanNoPadding);
}

#endif // CANAL_CAN : if the CAN Channel is used


// ------------------------------------------------------------------------
// --------------------------------- LDB API -----------------------------
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// Initialization of The LDBPC (Resources Module)
// ------------------------------------------------------------------------
void LDBInit(void)
{
  LdbpcIsInitialised = cTrue; // PON URD42 DEV 430 / PON URD45 BODY_SW 211 
	Ressources.Initialiser();
}

// ------------------------------------------------------------------------
// Send a initiated produced flow to a channel
// ------------------------------------------------------------------------
void LDBSendWithAddr(tChannel RefCan, tAddress Adresse, tMsg* pMsg)
{
  // PON URD42 DEV 430 / PON URD45 BODY_SW 211
  // The LBBInit() function must be called before anyone function of the LDB LAYER
  assert(LdbpcIsInitialised == cTrue); 

	Ressources.ActionFi(cFluxIP, RefCan, Adresse, pMsg);
}
void LDBSendWithoutAddr(tChannel RefCan, tMsg* pMsg)
{
  // PON URD42 DEV 430 / PON URD45 BODY_SW 211
  // The LBBInit() function must be called before anyone function of the LDB LAYER
  assert(LdbpcIsInitialised == cTrue); 

  Ressources.ActionFi(cFluxIP, RefCan, 0, pMsg);
}

// ------------------------------------------------------------------------
// Prepare a Produced not intiated flow
// ------------------------------------------------------------------------
void LDBPrepareSendWithAddr(tChannel RefCan, tAddress Adresse, tMsg* pMsg)
{
  // PON URD42 DEV 430 / PON URD45 BODY_SW 211
  // The LBBInit() function must be called before anyone function of the LDB LAYER
  assert(LdbpcIsInitialised == cTrue); 

  Ressources.PreparerActionFnip(RefCan, Adresse, pMsg);

}
void LDBPrepareSendWithoutAddr(tChannel RefCan, tMsg* pMsg)
{
  // PON URD42 DEV 430 / PON URD45 BODY_SW 211
  // The LBBInit() function must be called before anyone function of the LDB LAYER
  assert(LdbpcIsInitialised == cTrue); 

	Ressources.PreparerActionFnip(RefCan, 0, pMsg);
}

// ------------------------------------------------------------------------
// Receive an initiated consumed flow to a channel
// ------------------------------------------------------------------------
void LDBReceiveWithAddr(tChannel RefCan, tAddress Adresse, tMsg* pMsg)
{
  // PON URD42 DEV 430 / PON URD45 BODY_SW 211
  // The LBBInit() function must be called before anyone function of the LDB LAYER
  assert(LdbpcIsInitialised == cTrue); 

	Ressources.ActionFi(cFluxIC, RefCan, Adresse, pMsg);
}
void LDBReceiveWithoutAddr(tChannel RefCan, tMsg* pMsg)
{
  // PON URD42 DEV 430 / PON URD45 BODY_SW 211
  // The LBBInit() function must be called before anyone function of the LDB LAYER
  assert(LdbpcIsInitialised == cTrue); 

	Ressources.ActionFi(cFluxIC, RefCan, 0, pMsg);
}
// ------------------------------------------------------------------------
// Send a control to a channel
// ------------------------------------------------------------------------
void LDBControl(tChannel RefCan, tCtrl    ctrl)
{
  // PON URD42 DEV 430 / PON URD45 BODY_SW 211
  // The LBBInit() function must be called before anyone function of the LDB LAYER
  assert(LdbpcIsInitialised == cTrue); 

	Ressources.Controler(RefCan, ctrl);
}

// ------------------------------------------------------------------------
// Authorization of not initiated flow
// ------------------------------------------------------------------------
void LDBEnableCallBack(tChannel RefCan, BOOL bCallBackAutorise)
{
  // PON URD42 DEV 430 / PON URD45 BODY_SW 211
  // The LBBInit() function must be called before anyone function of the LDB LAYER
  assert(LdbpcIsInitialised == cTrue); 

	Ressources.Autoriser(RefCan, bCallBackAutorise);
}
