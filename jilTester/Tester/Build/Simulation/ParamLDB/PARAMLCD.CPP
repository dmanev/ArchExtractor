/*============================================================================
  Component ....................... ParamLCD
  File revision ................... $Revision:   1.0  $
  Last modification date .......... $Modtime:   04 Feb 2009 16:32:34  $
  Generation date ................. 31/10/2002 à 13:10:29
  Author Name ..................... XX
  File Name ....................... ParamLcd.cpp

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
#define ParamLCD "ParamLCD"
//--------------------------------------------------------------------------
//---------------- Inclusion de fichiers (système et librairies -----------
//--------------------------------------------------------------------------
#include "Ldbpc.h"          // defini les types et constantes de bases
#include "Ldbpcpar.h"       // defini la librairie de parametrage
//
#ifdef cLDBCanalLcd

//--------------------------------------------------------------------------
// CANAL Lcd
//--------------------------------------------------------------------------

// CallBack de LDBSendWithAddr redirige vers une fonction CallBack de LDBSendWithoutAddr
void DATLcdCallBackTxWithAddr(tAddress Adresse, tStatus Statut)
{
    DATLcdCallBackTxWithoutAddr(Statut);
}

// Initialisation du Lcd
void LcdInit(void)
{
    tCallBackCanal CallBackCanal;
    memset(&CallBackCanal,0,sizeof(tCallBackCanal));
    S32 RefFluxIP;
    S32 RefTrame;

    // Creation de la structure de Callback du canal Lcd
    CallBackCanal.pCallBackCtrl            =   NULL;
    CallBackCanal.pCallBackEndCtrl         =   DATLcdCallBackEndCtrl;
    CallBackCanal.pCallBackTx        =   DATLcdCallBackTxWithAddr;
    CallBackCanal.pCallBackRx       =   NULL;
    CallBackCanal.pTxSpontWithAddr      =   NULL;
    CallBackCanal.NbTxSpont     =   0;
    CallBackCanal.pRxSpontWithAddr     =   NULL;
    CallBackCanal.NbRxSpont    =   0;

    // Creation du canal Lcd
    RESCreerCanal(cLDBCanalLcd, "Lcd", &CallBackCanal, NULL, NULL);

    // Creation des flux
    RESCreerFluxI(&RefFluxIP,cLDBCanalLcd, cFluxIP, NULL);

    // Creation des trames et des donnees associées

    // Creation d'une trame "TrameLCD"
    RESCreerTrameFI(&RefTrame, RefFluxIP, "TrameLCD", 0x00, 12
                    , cFluxIP,0*(cTEMus/cLDBTick));

    // Creation des Sorties de la trame "TrameLCD"
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment0_0", 1 , 0, 7 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment0_1", 1 , 0, 6 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment0_2", 1 , 0, 5 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment0_3", 1 , 0, 4 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment0_4", 1 , 0, 3 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment0_5", 1 , 0, 2 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment0_6", 1 , 0, 1 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment0_7", 1 , 0, 0 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment1_0", 1 , 0, 15 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment1_1", 1 , 0, 14 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment1_2", 1 , 0, 13 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment1_3", 1 , 0, 12 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment1_4", 1 , 0, 11 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment1_5", 1 , 0, 10 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment1_6", 1 , 0, 9 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment1_7", 1 , 0, 8 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment2_0", 1 , 0, 23 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment2_1", 1 , 0, 22 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment2_2", 1 , 0, 21 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment2_3", 1 , 0, 20 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment2_4", 1 , 0, 19 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment2_5", 1 , 0, 18 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment2_6", 1 , 0, 17 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment2_7", 1 , 0, 16 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment3_0", 1 , 0, 31 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment3_1", 1 , 0, 30 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment3_2", 1 , 0, 29 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment3_3", 1 , 0, 28 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment3_4", 1 , 0, 27 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment3_5", 1 , 0, 26 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment3_6", 1 , 0, 25 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment3_7", 1 , 0, 24 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment4_0", 1 , 0, 39 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment4_1", 1 , 0, 38 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment4_2", 1 , 0, 37 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment4_3", 1 , 0, 36 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment4_4", 1 , 0, 35 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment4_5", 1 , 0, 34 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment4_6", 1 , 0, 33 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment4_7", 1 , 0, 32 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment5_0", 1 , 0, 47 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment5_1", 1 , 0, 46 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment5_2", 1 , 0, 45 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment5_3", 1 , 0, 44 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment5_4", 1 , 0, 43 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment5_5", 1 , 0, 42 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment5_6", 1 , 0, 41 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment5_7", 1 , 0, 40 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment6_0", 1 , 0, 55 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment6_1", 1 , 0, 54 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment6_2", 1 , 0, 53 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment6_3", 1 , 0, 52 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment6_4", 1 , 0, 51 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment6_5", 1 , 0, 50 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment6_6", 1 , 0, 49 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment6_7", 1 , 0, 48 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment7_0", 1 , 0, 63 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment7_1", 1 , 0, 62 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment7_2", 1 , 0, 61 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment7_3", 1 , 0, 60 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment7_4", 1 , 0, 59 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment7_5", 1 , 0, 58 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment7_6", 1 , 0, 57 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment7_7", 1 , 0, 56 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment8_0", 1 , 0, 71 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment8_1", 1 , 0, 70 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment8_2", 1 , 0, 69 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment8_3", 1 , 0, 68 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment8_4", 1 , 0, 67 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment8_5", 1 , 0, 66 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment8_6", 1 , 0, 65 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment8_7", 1 , 0, 64 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment9_0", 1 , 0, 79 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment9_1", 1 , 0, 78 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment9_2", 1 , 0, 77 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment9_3", 1 , 0, 76 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment9_4", 1 , 0, 75 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment9_5", 1 , 0, 74 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment9_6", 1 , 0, 73 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment9_7", 1 , 0, 72 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment10_0", 1 , 0, 87 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment10_1", 1 , 0, 86 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment10_2", 1 , 0, 85 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment10_3", 1 , 0, 84 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment10_4", 1 , 0, 83 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment10_5", 1 , 0, 82 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment10_6", 1 , 0, 81 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment10_7", 1 , 0, 80 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment11_0", 1 , 0, 95 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment11_1", 1 , 0, 94 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment11_2", 1 , 0, 93 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment11_3", 1 , 0, 92 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment11_4", 1 , 0, 91 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment11_5", 1 , 0, 90 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment11_6", 1 , 0, 89 );
    RESCreerSortieV(NULL, RefTrame, "Lcd_Segment11_7", 1 , 0, 88 );

    // Creation des Controles
    RESCreerControleSor(NULL, cLDBCanalLcd, "CtrlLcdDemarrer", cLDBLcdDemarrer, 0*(cTEMms/cLDBTick));
    RESCreerControleSor(NULL, cLDBCanalLcd, "CtrlLcdArreter", cLDBLcdArreter, 0*(cTEMms/cLDBTick));
}
#endif
