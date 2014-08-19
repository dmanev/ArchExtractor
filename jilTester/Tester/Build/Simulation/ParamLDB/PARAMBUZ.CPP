/*============================================================================
  Project ......................... AZ1039
  Component ....................... LdbpcBuz
  File revision ................... $Revision:   1.1  $
  Last modification date .......... $Modtime:   Apr 17 2009 10:14:00  $
  Generation date ...;;;;;;........ 
  Source file .....................
  BTC version .....................

  -------------------------------------------------------------------------
  Copyright ... This software is JCAE property. Duplication or
                disclosure is prohibited without JCAE written permission
  -------------------------------------------------------------------------

  - This file should only contain data useful to the programmer to use
    this Component
  - Component exported macros, constants and types are defined in this file
  - Component exported variables and functions are declared in this file
    with the "extern" keyword
  -------------------------------------------------------------------------
  ParamBuz.cpp file review :

	$Log:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/Build/Simulation/ParamLDB/PARAMBUZ.CPP-arc  $
// 
//    Rev 1.1   Apr 17 2009 10:16:06   amarinm1
// Cm003273: Path to the sounds folder was changed.
// 
//    Rev 1.0   Mar 24 2009 11:57:48   amarinm1
// Initial revision.
 * 
 *    Rev 1.2   Dec 07 2005 13:50:36   Marin
 * Optmizations: removed unused callbacks
 * 
 *    Rev 1.1   Mar 01 2005 14:48:32   Yasen
 * Buzzer finished
 * 
 *    Rev 1.0   Feb 10 2005 13:30:46   Yasen
 * Initial revision.
  ==========================================================================*/

/*-------------------------------------------------------------------------
  Included files

  #include <system_file_name.h>
  #include "project_file_name.h"
  --------------------------------------------------------------------------*/

#include "Ldbpc.h"
#include "Ldbpcpar.h"
#include "Ldbpctim.h"


#include <stdio.h>
#include "windows.h"
#include "mmsystem.h"
#pragma comment(lib, "Winmm.lib")

#ifdef cLDBChannelBuz

#define cTimerUpdateBuzInNs 10000000UL


char sCurrentSound[100];//sound filename
static tcTempoSimple sBuzTimer;

extern "C" void DATBuzTask(void);



void LDBPCBuzInit(void)
{
    sBuzTimer.EstPeriodique = cTrue;
    sBuzTimer.Duree         = cTimerUpdateBuzInNs;
    sBuzTimer.pCallBack     = DATBuzTask;
            
    Timer.AjouterTempo(&sBuzTimer);

    sBuzTimer.Actif = cTrue;
}

/*============================================================================
  DESCRIPTION:	void LDBBuzControl(tCtrl Ctrl)
				Set buzzer play/stop sound
  
  PARAMETERS:	Ctrl:
				cLDBBuzStartSound - 
					play sound with frequency, set by LDBBuzSendWithoutAddr
				cLDBBuzCancelSound - stop sound

  RETURN VALUE:	none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/

void LDBBuzControl(tCtrl Ctrl)
{
    tStatus Status = cLDBCorrect;
    
	switch(Ctrl)
	{
	case cLDBBuzStartSound:
		sndPlaySound(sCurrentSound, SND_ASYNC | SND_LOOP);
		break;
	
	case cLDBBuzCancelSound:
		sndPlaySound(NULL, SND_ASYNC);
		break;

    case cLDBBuzEnable:
    case cLDBBuzDisable:
        break;

    default:
        mLIBassert (0);
        Status = cLDBError;
        break;
	}

}

/*============================================================================
  DESCRIPTION : void LDBBuzSendWithoutAddr(tMsg* Msg)
				Set buzzer frequency.
				To play it, send LDBBuzControl(cLDBBuzStartSound) after that.
			
  PARAMETERS:	Msg->pBuffer - Set sound frequency in Hz, tU16Bit var
				Msg->Lng	 - must be set to 2

  RETURN VALUE:	none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/

void LDBBuzSendWithAddr(tAddress Address, tMsg* Msg)
{
	tU16Bit u16Hz;
 	const char* sPath = "../../TOOLS/COMMON/XCAR/SOUNDS";
    tStatus Status = cLDBCorrect;
	
	mLIBassert(Msg->Lng == 2);

	sCurrentSound[0] = 0;
	mLIBmemcpy(&u16Hz, Msg->pBuffer, 2);

	sprintf(sCurrentSound, "%s/%d.wav", sPath, u16Hz);

}

/*============================================================================
  DESCRIPTION:	void BuzInit(void)
				Initialize LDBPC buzzer
			
  PARAMETERS:	none

  RETURN VALUE:	none
 
  DESIGN INFORMATION:  refer to Detailed Design Document
============================================================================*/
void BuzInit(void)
{
	sCurrentSound[0] = 0;

    tCallBackCanal CallBackCanal;
    tS32Bit RefFluxIP;
    tS32Bit RefTrame;

    // Creation of the Mot channel Callback structure
    CallBackCanal.pCallBackCtrl				=   NULL;
    CallBackCanal.pCallBackEndCtrl			=   NULL;
    CallBackCanal.pCallBackTx				=   NULL;
    CallBackCanal.pCallBackRx				=   NULL;
    CallBackCanal.pTxSpontWithAddr			=   NULL;
    CallBackCanal.NbTxSpont					=   0;
    CallBackCanal.pRxSpontWithAddr			=   NULL;
    CallBackCanal.NbRxSpont					=   0;

    // Creation of the channel Buz
    RESCreerCanal(cLDBChannelBuz, "Buz", &CallBackCanal, LDBBuzControl, NULL);

    RESCreerFluxI(&RefFluxIP,cLDBChannelBuz, cFluxIP, LDBBuzSendWithAddr);

    RESCreerTrameFI(&RefTrame, RefFluxIP, "FrameBuz", 0, 2
                    , cFluxIP,0*(cTEMus/cLDBTick));

    RESCreerSortieV(NULL, RefTrame, "BuzzerFrequencyInHz", 16 , 0, 0);



    // Creation of the Controls
    RESCreerControleSor(NULL, cLDBChannelBuz, "CtrlBuzStartSound",
			cLDBBuzStartSound,  0*(cTEMms/cLDBTick) );
    RESCreerControleSor(NULL, cLDBChannelBuz, "CtrlBuzCancelSound",
			cLDBBuzCancelSound, 0*(cTEMms/cLDBTick) );
    RESCreerControleSor(NULL, cLDBChannelBuz, "CtrlBuzEnable",
			cLDBBuzEnable,  0*(cTEMms/cLDBTick) );
    RESCreerControleSor(NULL, cLDBChannelBuz, "CtrlBuzDisable",
			cLDBBuzDisable, 0*(cTEMms/cLDBTick) );

}

//============================================================================

#endif //cLDBChannelBuz