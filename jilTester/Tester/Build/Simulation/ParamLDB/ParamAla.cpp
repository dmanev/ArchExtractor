/*============================================================================
  Component ....................... ParamAla
  File revision ................... $Revision:   1.3  $
  Last modification date .......... $Modtime:   Sep 28 2009 12:03:04  $
  Author Name ..................... MG - Mickael GRANDSIRE
  File Name ....................... ParamAla.cpp

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
#define ParamAla "ParamAla"

/*-------------------------------------------------------------------------
  Included files

  #include <system_file_name.h>
  #include "project_file_name.h"
  --------------------------------------------------------------------------*/
#include "Ldbpc.h"          // Basis types and constants definition 
#include "Ldbpcpar.h"       // Configuration API definition

#ifdef cLDBChannelAla

//--------------------------------------------------------------------------
// CHANNEL Ala
//--------------------------------------------------------------------------

void DATAlaCallBackTxWithAddr(tAddress Adresse, tStatus Statut)
{
    DATAlaCallBackTxWithoutAddr(Statut);    
}

// Initialisation du Ala
void AlaInit(void)
{

    tCallBackCanal CallBackCanal;
    tS32Bit RefFluxIP;
    tS32Bit RefTrame;
    // Creation of the Ala channel Callback structure
    CallBackCanal.pCallBackCtrl     = NULL;
    CallBackCanal.pCallBackEndCtrl  = NULL;
    CallBackCanal.pCallBackTx       = DATAlaCallBackTxWithAddr;
    CallBackCanal.pCallBackRx       = NULL;
    CallBackCanal.pTxSpontWithAddr  = NULL;
    CallBackCanal.NbTxSpont         = 0;
    CallBackCanal.pRxSpontWithAddr  = NULL;
    CallBackCanal.NbRxSpont         = 0;

  
    // Creation of the channel Ala
     RESCreerCanal(cLDBChannelAla, " Ala", &CallBackCanal, NULL, NULL);

    // Creation of the flux
     RESCreerFluxI(&RefFluxIP,cLDBChannelAla,cFluxIP,NULL);

     
    
    // Creation of "AlaCde" frame
     RESCreerTrameFI(&RefTrame,RefFluxIP, "AlaCde", 0x00, 4
         , cFluxIP, ((4*12)+20)*(cTEMms/cLDBTick));

    

    RESCreerSortieV(NULL, RefTrame, "AlaMode",  8 , 0, 0 );
    RESCreerSortieV(NULL, RefTrame, "AlaData1", 8 , 0, 8 );
    RESCreerSortieV(NULL, RefTrame, "AlaData2", 8 , 0, 16 );
    RESCreerSortieV(NULL, RefTrame, "AlaData3", 8 , 0, 24 );

  
     
}
#endif

