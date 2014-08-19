/*============================================================================
  Component ....................... ParamINT
  File revision ................... $Revision:   1.0  $
  Last modification date .......... $Modtime:   04 Feb 2009 16:32:34  $
  Generation date ................. 19/03/2003  - 15:43:33 
  Author Name ..................... AB - Aaa BBB
  File Name ....................... ParamInt.cpp

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
#define ParamINT "ParamINT"

/*-------------------------------------------------------------------------
  Included files

  #include <system_file_name.h>
  #include "project_file_name.h"
  --------------------------------------------------------------------------*/
#include "Ldbpc.h"          // Basis types and constants definition 
#include "Ldbpcpar.h"       // Configuration API definition

#ifdef cLDBCanalInt

//--------------------------------------------------------------------------
// CHANNEL Int
//--------------------------------------------------------------------------

// Initialization of the channel Int
void IntInit(void)
{
    tCallBackCanal CallBackCanal;
    memset(&CallBackCanal,0,sizeof(tCallBackCanal));
    S32 RefFluxIP;
    S32 RefFluxIC;
    S32 RefTrame;

    // Creation of the Int channel Callback structure
    CallBackCanal.pCallBackCtrl            =   DATIntCallBackCtrl;
    CallBackCanal.pCallBackEndCtrl         =   DATIntCallBackEndCtrl;
    CallBackCanal.pCallBackTx        =   DATIntCallBackTxWithAddr;
    CallBackCanal.pCallBackRx       =   DATIntCallBackRxWithAddr;
    CallBackCanal.pTxSpontWithAddr      =   NULL;
    CallBackCanal.NbTxSpont     =   0;
    CallBackCanal.pRxSpontWithAddr     =   NULL;
    CallBackCanal.NbRxSpont    =   0;

    // Creation of the channel Int
    RESCreerCanal(cLDBCanalInt, "Int", &CallBackCanal, NULL, NULL);

    // Creation of the flux
    RESCreerFluxI(&RefFluxIP,cLDBCanalInt, cFluxIP, NULL);
    RESCreerFluxI(&RefFluxIC,cLDBCanalInt, cFluxIC, NULL);

    // Creation of the frames and the associated data

    // Creation of a Frame "SpeedometerFreqFrame"
    RESCreerTrameFI(&RefTrame, RefFluxIC, "SpeedometerFreqFrame", 0x00, 2
                    , cFluxIC,0*(cTEMus/cLDBTick));

    // Creation of the Inputs of the Frame"SpeedometerFreqFrame"
    RESCreerEntreeV(NULL, RefTrame, "SpeedometerFreq", 16 ,0x00, 0 );

    // Creation of a Frame "TachometerFreqFrame"
    RESCreerTrameFI(&RefTrame, RefFluxIC, "TachometerFreqFrame", 0x01, 2
                    , cFluxIC,0*(cTEMus/cLDBTick));

    // Creation of the Inputs of the Frame"TachometerFreqFrame"
    RESCreerEntreeV(NULL, RefTrame, "TachometerFreq", 16 ,0x00, 0 );

    // Creation of a Frame "FuelFlowRateFrame"
    RESCreerTrameFI(&RefTrame, RefFluxIC, "FuelFlowRateFrame", 0x02, 2
                    , cFluxIC,0*(cTEMus/cLDBTick));

    // Creation of the Inputs of the Frame"FuelFlowRateFrame"
    RESCreerEntreeV(NULL, RefTrame, "FuelFlowRateFrame", 16 ,0x00, 0 );

    // Creation of a Frame "EntrerTotalOdometerFrame"
    RESCreerTrameFI(&RefTrame, RefFluxIC, "EntrerTotalOdometerFrame", 0x03, 2
                    , cFluxIC,0*(cTEMus/cLDBTick));

    // Creation of the Inputs of the Frame"EntrerTotalOdometerFrame"
    RESCreerEntreeV(NULL, RefTrame, "EntrerTotalOdometer", 16 ,0x00, 0 );

    // Creation of a Frame "CalculatedTotalOdometerFrame"
    RESCreerTrameFI(&RefTrame, RefFluxIP, "CalculatedTotalOdometerFrame", 0x04, 2
                    , cFluxIP,0*(cTEMus/cLDBTick));

    // Creation of Outputs of the Frame "CalculatedTotalOdometerFrame"
    RESCreerSortieV(NULL, RefTrame, "CalculatedTotalOdometer", 16 , 0, 0 );

    // Creation of a Frame "CalculatedTotalMilometerFrame"
    RESCreerTrameFI(&RefTrame, RefFluxIP, "CalculatedTotalMilometerFrame", 0x05, 2
                    , cFluxIP,0*(cTEMus/cLDBTick));

    // Creation of Outputs of the Frame "CalculatedTotalMilometerFrame"
    RESCreerSortieV(NULL, RefTrame, "CalculatedTotalMilometerFrame", 16 , 0, 0 );

    // Creation of a Frame "CalculatedTotalTripmeterMilesFrame"
    RESCreerTrameFI(&RefTrame, RefFluxIP, "CalculatedTotalTripmeterMilesFrame", 0x06, 2
                    , cFluxIP,0*(cTEMus/cLDBTick));

    // Creation of Outputs of the Frame "CalculatedTotalTripmeterMilesFrame"
    RESCreerSortieV(NULL, RefTrame, "CalculatedTotalTripmeterMilesFrame", 16 , 0, 0 );

    // Creation of a Frame "EntrerTripmeter"
    RESCreerTrameFI(&RefTrame, RefFluxIC, "EntrerTripmeter", 0x07, 2
                    , cFluxIC,0*(cTEMus/cLDBTick));

    // Creation of the Inputs of the Frame"EntrerTripmeter"
    RESCreerEntreeV(NULL, RefTrame, "EntrerTripmeter", 16 ,0x00, 0 );

    // Creation of a Frame "CalculatedTripmeter"
    RESCreerTrameFI(&RefTrame, RefFluxIP, "CalculatedTripmeter", 0x08, 2
                    , cFluxIP,0*(cTEMus/cLDBTick));

    // Creation of Outputs of the Frame "CalculatedTripmeter"
    RESCreerSortieV(NULL, RefTrame, "CalculatedTripmeter", 16 , 0, 0 );

    // Creation of a Frame "EntrerInstCoveredDistance"
    RESCreerTrameFI(&RefTrame, RefFluxIC, "EntrerInstCoveredDistance", 0x09, 2
                    , cFluxIC,0*(cTEMus/cLDBTick));

    // Creation of the Inputs of the Frame"EntrerInstCoveredDistance"
    RESCreerEntreeV(NULL, RefTrame, "EntrerInstCoveredDistance", 16 ,0x00, 0 );

    // Creation of a Frame "CalculatedInstCoveredDistance"
    RESCreerTrameFI(&RefTrame, RefFluxIP, "CalculatedInstCoveredDistance", 0x0A, 2
                    , cFluxIP,0*(cTEMus/cLDBTick));

    // Creation of Outputs of the Frame "CalculatedInstCoveredDistance"
    RESCreerSortieV(NULL, RefTrame, "CalculatedInstCoveredDistance", 16 , 0, 0 );

    // Creation of a Frame "EntrerInstFuelConsumption"
    RESCreerTrameFI(&RefTrame, RefFluxIC, "EntrerInstFuelConsumption", 0x0B, 2
                    , cFluxIC,0*(cTEMus/cLDBTick));

    // Creation of the Inputs of the Frame"EntrerInstFuelConsumption"
    RESCreerEntreeV(NULL, RefTrame, "EntrerInstFuelConsumption", 16 ,0x00, 0 );

    // Creation of a Frame "CalculatedInstFuelConsumption"
    RESCreerTrameFI(&RefTrame, RefFluxIP, "CalculatedInstFuelConsumption", 0x0C, 2
                    , cFluxIP,0*(cTEMus/cLDBTick));

    // Creation of Outputs of the Frame "CalculatedInstFuelConsumption"
    RESCreerSortieV(NULL, RefTrame, "CalculatedInstFuelConsumption", 16 , 0, 0 );

    // Creation of the Controls
    RESCreerControleSor(NULL, cLDBCanalInt, "CtrlINTStart", cLDBINTStart, 0*(cTEMms/cLDBTick));
    RESCreerControleSor(NULL, cLDBCanalInt, "CtrlINTStop", cLDBINTStop, 0*(cTEMms/cLDBTick));
    RESCreerControleSor(NULL, cLDBCanalInt, "CtrlINTBeginResetTripmeter", cLDBINTBeginResetTripmeter, 0*(cTEMms/cLDBTick));
    RESCreerControleSor(NULL, cLDBCanalInt, "CtrlINTEndResetTripmeter", cLDBINTEndResetTripmeter, 0*(cTEMms/cLDBTick));
    RESCreerControleSor(NULL, cLDBCanalInt, "CtrlINTResetADAC", cLDBINTResetADAC, 0*(cTEMms/cLDBTick));
    RESCreerControleSor(NULL, cLDBCanalInt, "CtrlINTResetTotal", cLDBINTResetTotal, 0*(cTEMms/cLDBTick));
    RESCreerControleEnt(NULL, cLDBCanalInt, "CtrlINTPass1km", cLDBINTPass1km);
    RESCreerControleEnt(NULL, cLDBCanalInt, "CtrlINTPass100mTripmeter", cLDBINTPass100mTripmeter);
}
#endif
