/*============================================================================
  Component ....................... paramrf
  File revision ................... $Revision:   1.1  $
  Last modification date .......... $Modtime:   Sep 21 2009 13:59:54  $
  Generation date ................. 25/02/2003
  Author Name ..................... XX
  File Name ....................... ParamRf.cpp

  -------------------------------------------------------------------------
  Copyright ... This software is JCAE property. Duplication or
                disclosure is prohibited without JCAE written permission
  -------------------------------------------------------------------------

  - This file should only contain data useful to the programmer to use
    this Component
  - Component exported macros, constants and types are defined in this file
  - Component exported variables and functions are declared in this file
    with the extern keyword

  ==========================================================================*/
//***************************************************************************

#define ParamRf "ParamRf"


//--------------------------------------------------------------------------
//---------------- Inclusion de fichiers (système et librairies -----------
//--------------------------------------------------------------------------

#include "Ldbpc.h" // defini les types et constantes de bases
#include "Ldbpcpar.h"
#include "string.h"

#ifdef cLDBChannelRf

#define cSearchWakeUpTimeOutInUs    3000
#define cWakeUpDelayInUs            66500   // 200 ms

#define cBaud			9600
#define cNbBitData		8
#define cNbBitParite	0
#define cNbBitStop		1
#define cNbBitInterTrame 2

#define NbBit (cNbBitData + cNbBitParite + cNbBitInterTrame  + cNbBitStop)

#define cRfDureeOctet ( (((1000000*NbBit)/cBaud) * cTEMus)/cLDBTick )

#define cTailleMaxTrameReception	32 * 8

static	tS32Bit RfRefEvtWakeUp;
static	tS32Bit RfRefEvtSendFrame;
static	tS32Bit RfRefTailleNIC;
static	tS32Bit RfRefAdresseNIC;
static	tS32Bit RfRefRecepNIC;
static	tS32Bit RfRefAffichage;
static  tBooleen RfActive;
static  tBooleen PresentWakeUp;

static  tTimerRef refSearchWakeUpTimeOut;
static  tTimerRef refWakeUpDelay;

// LDBControl Specifique
static void RfSendReception();
static void SearchWakeUpTimeOut(tS32Bit Ref);
static void WakeUpDelay(tS32Bit Ref);

static void SearchWakeUpTimeOut(tS32Bit Ref)
{
  mLIBassert(Ref == refSearchWakeUpTimeOut);
  RfActive = cFaux;
  DATRfCallBackCtrl(cLDBRfWakeUpNotReceived);
}

static void RfCallBackCtrl(tCtrl Ctrl)
{
    switch (Ctrl)
    {
      case cLDBRfSearchFrame:
        RfActive = cVrai;
        if (PresentWakeUp == cVrai)
        {
          DATRfCallBackCtrl(cLDBRfWakeUpReceived);
        }
        else
        {
          LDBPCStartTimer(refSearchWakeUpTimeOut,((tDelay) ( (cSearchWakeUpTimeOutInUs * 1000) / cLDBTick)),SearchWakeUpTimeOut);
        }
        break;
      case cLDBRfStop:
        RfActive = cFaux;
        LDBPCStopTimer(refSearchWakeUpTimeOut,NULL);
        break;
      default:
        break;
    }
}

static void WakeUpDelay(tS32Bit Ref)
{
  mLIBassert(Ref == refWakeUpDelay);
  LDBPCStopTimer(refWakeUpDelay,NULL);
  PresentWakeUp = cFaux;
}

static void RfWakeUp(tS32Bit)
{
  PresentWakeUp = cVrai;
  LDBPCStopTimer(refWakeUpDelay,NULL);
  LDBPCStartTimer(refWakeUpDelay,((tDelay) ( (cWakeUpDelayInUs * 1000) / cLDBTick)),WakeUpDelay);
}

static void RfReception(tS32Bit)
{
  if (RfActive == cVrai)
  {
    PresentWakeUp = cFaux;
    RfSendReception();
  }
}

static void RfSendReception()
{
  LDBPCStopTimer(refSearchWakeUpTimeOut,NULL);
  PresentWakeUp = cFaux;

	tMsg Msg;
	tU8Bit Buffer[cTailleMaxTrameReception];
	Msg.pBuffer = Buffer;


	tU32Bit Val;
	DONLireV(RfRefTailleNIC,&Val,NULL,NULL);
	if(Val > 0)
	{
    tU32Bit Adresse;
		Msg.Lng    = (tU16Bit)Val;
		DONLireB(RfRefRecepNIC,Msg.pBuffer, NULL, NULL);
		DONLireV(RfRefAdresseNIC,&Adresse, NULL, NULL);

    const tRxSpontWithAddr* pStr;
 
    if( Adresse == DATRfRxSpontTable[0].Address )
    {
      // Start time out
	    pStr = &DATRfRxSpontTable[0];
      if (RfActive == cVrai)
      {
        pStr->pCallBackRx(0, cLDBCorrect, &Msg);
      }
    }
    else if (Adresse == DATRfRxSpontTable[1].Address)
    {         
	    pStr = &DATRfRxSpontTable[1];
      if (RfActive == cVrai)
      {
        pStr->pCallBackRx(1, cLDBCorrect, &Msg);
      }
    }
    else
    {
      // Not possible
    }
	}
}

void RFInit(void)
{
	tCallBackCanal RfCallBack;
	tS32Bit RfRefFluxNIC;

  RfActive      = cFaux;
  PresentWakeUp  = cFaux;
  LDBPCCreerTempo(&refSearchWakeUpTimeOut);
  LDBPCCreerTempo(&refWakeUpDelay);

	//--------------------------------------------------------------------------
	// Creation de la structure de Callback du canal RF
	//--------------------------------------------------------------------------
  RfCallBack.pCallBackCtrl		=   NULL;
  RfCallBack.pCallBackEndCtrl =   NULL;
  RfCallBack.pCallBackTx			=   NULL;
  RfCallBack.pCallBackRx		  =   NULL;
  RfCallBack.pRxSpontWithAddr  =   NULL;
  RfCallBack.pTxSpontWithAddr	=   NULL;
  RfCallBack.NbRxSpont			  =   0;
  RfCallBack.NbTxSpont			  =   0;

	//--------------------------------------------------------------------------
	// Creation du canal CAN
	//--------------------------------------------------------------------------
  RESCreerCanal(cLDBChannelRf, "Rf", (tCallBackCanal *)&RfCallBack, RfCallBackCtrl, NULL);

 	//--------------------------------------------------------------------------
	// Creation du flux Non Initie Consomme
	//--------------------------------------------------------------------------
  RESCreerFluxNI(&RfRefFluxNIC, cLDBChannelRf, cFluxNIC, NULL);

	// Evt de la trame de Commande
	DONCreerEvtEntree( &RfRefEvtWakeUp,   "RfEvtSendWakeUp",  RfWakeUp ,    "Rf\\TrameReception");
	DONCreerEvtEntree( &RfRefEvtSendFrame, "RfEvtSendFrame",   RfReception , "Rf\\TrameReception");

	// Creation du buffer de la trame recue
 	tU8Bit pBufferR[cTailleMaxTrameReception] = {0};
	DONCreerEntreeB(&RfRefRecepNIC, "CleBufferTrameRecue", pBufferR,
								cTailleMaxTrameReception, "Rf\\TrameReception");

	// Taille du buffer de la trame recue
	DONCreerEntreeV(&RfRefTailleNIC, "CleTailleTrameRecue", 0, 5, "Rf\\TrameReception");

  // Adresse de la trame recue
	DONCreerEntreeV(&RfRefAdresseNIC, "AdresseTrameRecue", 0, 5, "Rf\\TrameReception");

  // Creation des Controles
  RESCreerControleSor(NULL, cLDBChannelRf, "StopRFChannel", cLDBRfStop, 0*(cTEMms/cLDBTick));
  RESCreerControleSor(NULL, cLDBChannelRf, "RfSearchWakeUp", cLDBRfSearchFrame, 0*(cTEMms/cLDBTick));
  RESCreerControleSor(NULL, cLDBChannelRf, "RfActivateStrobe", cLDBRfActivateStrobe, 0*(cTEMms/cLDBTick));
  RESCreerControleSor(NULL, cLDBChannelRf, "RfDeactivateStrobe", cLDBRfDeactivateStrobe, 0*(cTEMms/cLDBTick));
}

#endif