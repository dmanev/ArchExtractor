/*============================================================================
  Component ....................... parspd
  File revision ................... $Revision:   1.0  $
  Last modification date .......... $Modtime:   Jul 02 2009 13:33:16  $
  Generation date ................. 
  Author Name ..................... XX
  File Name ....................... ParamSpd.cpp

  -------------------------------------------------------------------------
  Copyright ... This software is JCI property. Duplication or
                disclosure is prohibited without JCI written permission
  -------------------------------------------------------------------------

  - This file should only contain data useful to the programmer to use
    this Component
  - Component exported macros, constants and types are defined in this file
  - Component exported variables and functions are declared in this file
    with the extern keyword

  ==========================================================================*/


/*---------------------------------------------------------------------------
     Included files
  ---------------------------------------------------------------------------*/
#include "Ldbpc.h"     // Define the types and base constants
#include "Ldbpcpar.h"  // Define the setting librairy

#ifdef cLDBChannelSpd

//--------------------------------------------------------------------------
//     CHANNEL Spd
//--------------------------------------------------------------------------
#define cSpdMsgLength  2

S32 RefTrame;

// LDBRecevoir redefinition
void SpdReceive(tAddress Address, tMsg* pMsg)
{
   RESLireTrame(RefTrame, pMsg);
}

void SpdInit(void)
{
    tCallBackCanal CallBackCanal;
    memset(&CallBackCanal,0,sizeof(tCallBackCanal));
    S32 RefFluxIC;


    // Creation of the Callback structure of the channel
    CallBackCanal.pCallBackCtrl        =   NULL;
    CallBackCanal.pCallBackEndCtrl     =   NULL;
    CallBackCanal.pCallBackTx          =   NULL;
    CallBackCanal.pCallBackRx          =   NULL;
    CallBackCanal.pTxSpontWithAddr     =   NULL;
    CallBackCanal.NbTxSpont            =   0;
    CallBackCanal.pRxSpontWithAddr     =   NULL;
    CallBackCanal.NbRxSpont            =   0;

    // Creation of the Spd channel
    RESCreerCanal(cLDBChannelSpd, "Spd", &CallBackCanal, NULL, NULL);

    // Format of the Channel
    RESEcrireFormat( cLDBChannelSpd, cCodageIntel);

    // Creation of the flux
    RESCreerFluxI(&RefFluxIC,cLDBChannelSpd, cFluxIC, SpdReceive);

    // Creation of the frames and the data 

    // Creation of the frame SpdMsg
    RESCreerTrameFI(&RefTrame, RefFluxIC, "SpdMsg", 0x0, cSpdMsgLength
           , cFluxIC,0*(cTEMus/cLDBTick));

    // Creation of input of the frame SpdMsg
    
    RESCreerEntreeV(NULL, RefTrame, "VEH_SPEED" ,8,0,0);
    RESCreerEntreeV(NULL, RefTrame, "ENGINE_RPM",8,0,8);
    

    // Creation of the controls 
    RESCreerControleSor(NULL, cLDBChannelSpd, "CtrlSpdControlStart", cLDBSpdControlStart, 0*(cTEMus/cLDBTick));
    RESCreerControleSor(NULL, cLDBChannelSpd, "CtrlSpdControlStop" , cLDBSpdControlStop , 0*(cTEMus/cLDBTick));
}

#endif // cLDBChannelSpd

