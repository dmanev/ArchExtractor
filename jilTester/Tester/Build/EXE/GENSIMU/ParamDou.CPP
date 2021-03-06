/**************************************************************************

  Component             ParamDou.CPP
  -------------------------------------------------------------------------
  Copyright     This software is JCI property. Duplication or
                disclosure is prohibited without JCI written permission
  -------------------------------------------------------------------------
   
   - This file should only contain data useful to the programmer to use
     this component
   - Component exported macros, constants and types are defined in this file
   - Component exported variables and functions are declared in this file
     with the "extern" keyword
   
  -------------------------------------------------------------------------
    This file was generated by LDBPC Generator.dll 01.03
	
	Generation date : 15/02/2011 13:28
	Reference File  : ..\SOURCES\LAP\lap_sup.jil
	
***************************************************************************/



/*---------------------------------------------------------------------------
     Included files
  ---------------------------------------------------------------------------*/
#include "Ldbpc.h"     // Define the types and base constants
#include "Ldbpcpar.h"  // Define the setting librairy

#ifdef cLDBChannelDou

//--------------------------------------------------------------------------
//     CHANNEL Dou
//--------------------------------------------------------------------------
// CallBack LDBEmettreWithAddr to CallBack LDBEmettreWithoutAddr
void DATDouCallBackTxWithAddr(tAddress Adresse, tStatus Statut)
{
    DATDouCallBackTxWithoutAddr(Statut);
}

void DouInit(void)
{
    tCallBackCanal CallBackCanal;
    memset(&CallBackCanal,0,sizeof(tCallBackCanal));
    S32 RefFluxIP;
    S32 RefTrame;


    // Creation of the Callback structure of the channel
    CallBackCanal.pCallBackCtrl        =   NULL;
    CallBackCanal.pCallBackEndCtrl     =   DATDouCallBackEndCtrl;
    CallBackCanal.pCallBackTx          =   DATDouCallBackTxWithAddr;
    CallBackCanal.pCallBackRx          =   NULL;
    CallBackCanal.pTxSpontWithAddr     =   NULL;
    CallBackCanal.NbTxSpont            =   0;
    CallBackCanal.pRxSpontWithAddr     =   NULL;
    CallBackCanal.NbRxSpont            =   0;

    // Creation of the Dou channel
    RESCreerCanal(cLDBChannelDou, "Dou", &CallBackCanal, NULL, NULL);

    // Format of the Channel
    RESEcrireFormat( cLDBChannelDou, cCodageIntel);

    // Creation of the flux
    RESCreerFluxI(&RefFluxIP,cLDBChannelDou, cFluxIP, NULL);

    // Creation of the frames and the data 

    // Creation of the frame DouGeneratorMessage
    RESCreerTrameFI(&RefTrame, RefFluxIP, "DouGeneratorMessage", 0x0, 4
           , cFluxIP,0*(cTEMus/cLDBTick),cTypeFrameFixSize);

    // Creation of output of the frame DouGeneratorMessage
    RESCreerSortieV(NULL, RefTrame, "VERLOG_LED",1,0,5);
    RESCreerSortieV(NULL, RefTrame, "OPEN_DOOR_LED",1,0,4);
    RESCreerSortieV(NULL, RefTrame, "DEFROSTER",1,0,14);
    RESCreerSortieV(NULL, RefTrame, "HORN_RL",1,0,21);
    RESCreerSortieV(NULL, RefTrame, "LOCK_DOORS",1,0,31);
    RESCreerSortieV(NULL, RefTrame, "UNLOCK_DOORS",1,0,30);
    RESCreerSortieV(NULL, RefTrame, "BAT_LIGHT_TEMPO",1,0,29);
    RESCreerSortieV(NULL, RefTrame, "UNLOCK_DRIVER_DOOR",1,0,28);
    RESCreerSortieV(NULL, RefTrame, "FRONT_WIPER",1,0,27);
    RESCreerSortieV(NULL, RefTrame, "RR_WIPER_RR_FOG_LAMP",1,0,26);
    RESCreerSortieV(NULL, RefTrame, "DI_LEFT",1,0,25);
    RESCreerSortieV(NULL, RefTrame, "DI_RIGHT",1,0,24);

    // Creation of the controls 
    RESCreerControleSor(NULL, cLDBChannelDou, "CtrlDouEnterNominalMode", cLDBDouEnterNominalMode, 0*(cTEMus/cLDBTick));
    RESCreerControleSor(NULL, cLDBChannelDou, "CtrlDouEnterSleepMode", cLDBDouEnterSleepMode, 0*(cTEMus/cLDBTick));
    RESCreerControleSor(NULL, cLDBChannelDou, "CtrlDouSetDO_DATA_IMMOBILIZER", cLDBControlSetDO_DATA_IMMOBILIZER, 0*(cTEMus/cLDBTick));
    RESCreerControleSor(NULL, cLDBChannelDou, "CtrlDouClearDO_DATA_IMMOBILIZER", cLDBControlClearDO_DATA_IMMOBILIZER, 0*(cTEMus/cLDBTick));
    RESCreerControleSor(NULL, cLDBChannelDou, "CtrlDouSetDO_VERLOG", cLDBControlSetDO_VERLOG, 0*(cTEMus/cLDBTick));
    RESCreerControleSor(NULL, cLDBChannelDou, "CtrlDouClearDO_VERLOG", cLDBControlClearDO_VERLOG, 0*(cTEMus/cLDBTick));
    RESCreerControleSor(NULL, cLDBChannelDou, "CtrlDouEnableOPEN_DOOR_LED", cLDBDouEnableOPEN_DOOR_LED, 0*(cTEMus/cLDBTick));
    RESCreerControleSor(NULL, cLDBChannelDou, "CtrlDouDisableOPEN_DOOR_LED", cLDBDouDisableOPEN_DOOR_LED, 0*(cTEMus/cLDBTick));
    RESCreerControleSor(NULL, cLDBChannelDou, "CtrlDouSetVERLOG_LED", cLDBControlSetVERLOG_LED, 0*(cTEMus/cLDBTick));
    RESCreerControleSor(NULL, cLDBChannelDou, "CtrlDouClearVERLOG_LED", cLDBControlClearVERLOG_LED, 0*(cTEMus/cLDBTick));
}

#endif // cLDBChannelDou

