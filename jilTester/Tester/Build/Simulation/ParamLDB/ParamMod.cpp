/****************************************************************************
  Project ......................... AW1092
  Component ....................... parammod
  File revision.................... $Revision:   1.4  $
  Last modification date .......... $Modtime:   Oct 01 2009 11:39:34  $
  -------------------------------------------------------------------------
  Copyright ... This software is JCI property. Duplication or
                disclosure is prohibited without JCI written permission
  ------------------------------------------------------------------------- 

  - Macros, constants et types which are not exported are defined in 
    this file
  - Variables and functions which are not exported are defined in this 
    file with the static keyword
  
  -------------------------------------------------------------------------
  Comments about the component (role, algorithm, structure, limitations,
           defined tasks and events...)
  - Role :
  
  -------------------------------------------------------------------------
  ParamMod.c file review : 

   $Log:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/Build/Simulation/ParamLDB/ParamMod.cpp-arc  $
// 
//    Rev 1.4   Oct 01 2009 11:40:18   akodzhh
// Cm006291: RF test updated.
// 
//    Rev 1.3   Sep 21 2009 11:14:32   akodzhh
// Cm005207: Add SDO, KEY_BUTTON config params (21 D0, 3B D0).
// 
//    Rev 1.2   03 Sep 2009 17:09:18   akodzhh
// Cm005525: Use VERLOGON data name instead of VEH_DEPROTEGE.
// 
//    Rev 1.1   Jul 02 2009 18:22:00   akodzhh
// Cm005574: Updates after SW1.
// 
//    Rev 1.0   Mar 23 2009 12:23:42   adzhelp
// Initial revision.
 * 
 *    Rev 1.57   Jul 06 2007 14:25:12   agallil
 * PON URD45 CLI 2617:RA39: ALS still activated after engine stall+APC OFF condition: 
 * -> Creation of ENGINE_STALLED_TM_TP variable to manage the new timer
 * 
 *    Rev 1.56   Jan 26 2007 16:44:06   agallil
 * PON URD45 DEV 3738:New default for Base Station disconnection:
 * -> Add new output:"BaseStationDisconnected"
 * 
 *    Rev 1.55   Sep 28 2006 16:48:40   agallil
 * Add SendWriteVdiagAFSMode for Vdiag update.
 * 
 *    Rev 1.54   Jul 31 2006 16:02:16   agallil
 * Improve format for SerialNber from ReadBCMIdentificationAFSMode
 * 
 *    Rev 1.53   May 16 2006 18:34:36   agallil
 * Change ReadSoftwareAndTFCVersionID into ReadSoftwareAndVersionTFCMode and add ReadBCMIdentificationAFSMode
 * 
 *    Rev 1.52   09 Feb 2006 12:41:34   agallil
 * Add BCM Identification section and ReadSoftwareAndTFCVersionID routine call
 * 
 *    Rev 1.51   22 Dec 2005 15:53:12   agallil
 *  PON URD45 CLI 2161: FDC 22 - DoorLock - Actuator diag request for all doors. 
 * -> Add $30-$A4 actuator diag command (all cpe).
 * 
 *    Rev 1.50   Jul 07 2005 10:04:54   averrij
 * PON URD45 CLI 1732 / PON URD45 MODULES 8696
 * DFC17 - Activation of High beam lamps in Automatic Mode
 * 
 *    Rev 1.49   Jul 06 2005 17:05:28   averrij
 * PON URD45 CLI 1732 / PON URD45 MODULES 8696
 * DFC17 - Activation of High beam lamps in Automatic Mode
 * 
 *    Rev 1.48   May 26 2005 10:54:02   averrij
 * PON URD45 CLI 1774 / PON URD45 MODULES 
 * FDC 19 - DoorLock - Unlock With Doors - CAR Type VU Configuration
 * 
 *    Rev 1.47   May 18 2005 14:13:26   averrij
 * PON URD45 CLI 1738 / PON URD45 MODULES 
 * FDC 18 - Logical Lighting - Intelligent Interior light configuration
 * 
 *    Rev 1.46   Feb 25 2005 14:48:26   agrandm
 * Add CanBusOpen data
 * 
 *    Rev 1.45   Feb 24 2005 13:49:48   agrandm
 * Add data
 * 
 *    Rev 1.44   Jan 27 2005 09:27:58   agrandm
 * Update for AW1092_V03.01 version
 * 
 *    Rev 1.43   Sep 10 2004 16:15:12   awillen
 * Update for alarm test mode
 * 
 *    Rev 1.41   Aug 30 2004 14:23:36   alelabc
 * Add the data RESET
 * 
 *    Rev 1.40   Aug 25 2004 11:55:18   alelabc
 * PON URD45 DEV 1204 / PON URD45 MODULES 7827 :Add TFC model
 * 
 *    Rev 1.39   Aug 16 2004 13:35:26   alelabc
 * PON URD45 DEV 1180 / PON URD45 MODULES 7769 :    Invert ClkTransponder and Larc Outputs due to Hardware modification
 * 
 *    Rev 1.38   Jul 08 2004 14:30:08   awillen
 * PON URD45 DEV 835 / PON URD45 MODULES 6860:  Implementation of hardware defaults detection 
 * 
 *    Rev 1.37   May 27 2004 16:05:48   alelabc
 * Add the MuxOverTemp DTC
 * 
 *    Rev 1.36   May 25 2004 19:29:02   alelabc
 * PON URD45 MODULES 7282 - PON URD45 DEV 995: add the DTC reading and clearing services
 * 
 *    Rev 1.35   May 24 2004 18:00:46   abardep
 * Adding data for monitoring tests
 * 
 *    Rev 1.34   May 19 2004 16:45:10   agrandm
 * Simplify LRS
 * 
 *    Rev 1.33   May 14 2004 17:40:36   alelabc
 * PON URD45 CLI 835 / PON URD45 MODULES 7386 : spec evolutions (sse CDC AW1092 : Specification Foncitonnelle Diagnostic edition 3). Add the reading of sensor data
 * 
 *    Rev 1.32   May 13 2004 11:26:46   alelabc
 * PON URD45 CLI 835 / PON URD45 MODULES 7386 : spec evolutions (sse CDC AW1092 : Specification Foncitonnelle Diagnostic edition 3)
 * 
 *    Rev 1.31   May 10 2004 14:44:54   agrandm
 * PON URD45 DEV 959 / PON URD45 MODULES 7233: New hardware ProtoC delivery ( Add EsavCadenceValue)
 * 
 *    Rev 1.30   Apr 28 2004 16:18:20   alelabc
 * PON URD45 CLI 804 / PON URD45 MODULES 728, PON URD45 CLI 753 / PON URD45 MODULES 7169, PON URD45 CLI 687 / PON URD45 MODULES 6949 : add Eeprom parameters for LRS function, windows lift and rear wiper
 * 
 *    Rev 1.29   Apr 20 2004 14:50:12   agrandm
 * PON URD45 DEV 959 / PON URD45 MODULES 7233: New hardware ProtoC delivery
 * 
 *    Rev 1.28   Mar 25 2004 12:16:20   agrandm
 * Add ViriginKey event for Ecar
 * 
 *    Rev 1.27   Mar 25 2004 12:14:42   alelabc
 * Add the variable BattElecVoltage
 * 
 *    Rev 1.26   Feb 24 2004 18:35:20   apoulia
 * Add Sensor and Siren component
 * 
 *    Rev 1.25   Feb 06 2004 10:25:14   agrandm
 * PON URD45 DEV 654 / PON URD45 MODULES 6433: B2 delivery ( Add Airbag component )
 * 
 *    Rev 1.24   Feb 04 2004 15:04:24   alelabc
 * Add the diagnostic service to modify the parameter EEPCalTyp3A et EEPCalTyp6A
 * 
 *    Rev 1.23   Feb 02 2004 15:21:44   apoulia
 * PON URD45 DEV 612 / PON URD45 MODULES 6358 : bulbe failure and trailer detection : Add outputs for 5W/21W lamp power
 * 
 *    Rev 1.22   Jan 29 2004 16:27:10   apoulia
 * PON URD45 DEV 612 / PON URD45 MODULES 6358 Add flasher model
 * 
 *    Rev 1.21   Jan 05 2004 12:00:56   agrandm
 * Add Cpe model
 * 
 *    Rev 1.20   Dec 17 2003 15:08:24   agrandm
 * Add MODCmdLarc, MODLviD and MODLviM for automatic logic  inverting 
 * 
 *    Rev 1.19   Dec 12 2003 09:27:34   apoulia
 * PON URD45 DEV 606 / PON URD45 MODULES 6355 : Translate in English
 * 
 *    Rev 1.18   Dec 01 2003 12:24:54   alelabc
 * Change initial values of "config usine" parameter
 * 
 *    Rev 1.17   Nov 26 2003 14:52:06   awillen
 * $ECarOn was added
 * 
 *    Rev 1.16   Nov 18 2003 12:45:42   alelabc
 * Change The inital value of WIPING_TIME_PV
 * 
 *    Rev 1.15   Nov 14 2003 17:04:20   alelabc
 * Add the immobilizer diagnostic panel
 * 
 *    Rev 1.14   Nov 13 2003 10:57:06   agrandm
 * Add WinLift component
 * 
 *    Rev 1.13   Nov 07 2003 15:47:42   alelabc
 * Add the parameter GESTION_ENERGIE1
 * 
 *    Rev 1.12   Nov 05 2003 14:09:20   alelabc
 * Add the data for smile diagnostic request
 * 
 *    Rev 1.11   Nov 04 2003 16:31:00   agrandm
 * Add Reset fonctionnality
 * 
 *    Rev 1.10   Oct 29 2003 15:06:24   alelabc
 * Add a diagnostic request to read the analog inputs
 * 
 *    Rev 1.9   Oct 27 2003 13:59:44   alelabc
 * Add the request $21 $DC (reading of BCM input s) and $30 $XX (output commands).
 * 
 *    Rev 1.8   Oct 15 2003 15:30:04   agrandm
 * Change Croisement2 type to Entree
 * 
 *    Rev 1.7   Oct 15 2003 12:19:18   agrandm
 * Add new wiper model
 * 
 *    Rev 1.6   Oct 14 2003 17:32:52   alelabc
 * Create the parameter WIPING_TIME and the event ot send the $3B $D0 and $3B $D1 diagnostic frame
 * 
 *    Rev 1.5   Oct 09 2003 14:27:54   alelabc
 * Add the parameter TypeBoutonLVI
 * 
 *    Rev 1.4   Sep 26 2003 19:48:52   alelabc
 * Add SEUIL_VITESS_PLAF parameter
 * 
 *    Rev 1.3   Sep 16 2003 14:01:00   agrandm
 * Move KeyUsingNumber from ParamRf to ParamMod
 * 
 *    Rev 1.2   Sep 15 2003 17:28:28   agrandm
 * Rename ParamModInit by ModInit
 * 
 *    Rev 1.1   Sep 15 2003 12:23:58   alelabc
 * Add the parameter LONG_CAR.
 * 
 *    Rev 1.0   Sep 09 2003 18:39:28   adm
 * Initial revision.

   Rev 1.0   Jul 03 2003 18:22:08   adm
Initial revision.

*****************************************************************************/

/*--------------------------------------------------------------------------
  Body Identification
  --------------------------------------------------------------------------*/

#define parammod  "parammod"

/*--------------------------------------------------------------------------
  Included files

  #include <system_file_name.h>
  #include "project_file_name.h"
  --------------------------------------------------------------------------*/

#include "Ldbpc.h"     // Define the types and base constants
#include "Ldbpcpar.h"  // Define the setting librairy

/*--------------------------------------------------------------------------
  Local constants

  #define cConstantName   ((tType) ConstantValue)
  --------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------
  Local macros

  #define mMacroName   (MacroDefinition)
  --------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------
  Local types

  struct  sStructureName { ... };
  union   uUnionName { ... };
  enum    eEnumerationName { ... };
  typedef Expression tTypeName;
  --------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------
  Local data

  static  tType   VariableName;
  static  tType*  pVariableName; 
  --------------------------------------------------------------------------*/
static  tS32Bit EnterInAFSKeyLearningModeNIC;

/*--------------------------------------------------------------------------
  Constant local Data

  static const tType  VariableName;
  --------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------
  Exported data

  tType   CMPVariableName;      (CMP: 3 characters to identify this component)
  tType*  pCMPVariableName;     (CMP: 3 characters to identify this component)
  --------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------
  Constant exported data
 
  const tType   CMPVariableName;(CMP: 3 characters to identify this component)
  --------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------
  Local function prototypes
  
  static tTypeRetour FunctionName(tTypeArgument1 ArgumentName1, ... );
  --------------------------------------------------------------------------*/


/****************************************************************************
*...........................................................................*
*............................ LOCAL FUNCTIONS ..............................*
*...........................................................................*
****************************************************************************/

/* [LOCAL_FUNCTIONS_END] */
/*
void CallBackRst(tS32Bit)
{
    LDBReset();
}*/



/****************************************************************************
*...........................................................................*
*........................... EXPORTED FUNCTIONS.............................*
*...........................................................................*
****************************************************************************/
void ModInit(void)
{
  //--------------------------------------------------------------------------
  // Data for reset application
  //--------------------------------------------------------------------------
//   DONCreerEvtEntree( NULL, "Reset", CallBackRst, "Mod");
//  DONCreerEntreeV(NULL,   "ECarOn",        1, 1, "Mod");
//  DONCreerEntreeV(NULL,   "RESET",        1, 1, "Mod");

  //--------------------------------------------------------------------------
  // Data for Immobiliser model
  //--------------------------------------------------------------------------
  // Creation des donnees du modele de Cle avec RF 
  //--------------------------------------------------------------------------
  DONCreerEvtEntree(NULL, "ButtonRFLock",         NULL, "Mod\\Cle" );
  DONCreerEvtEntree(NULL, "ButtonRFUnlock",       NULL, "Mod\\Cle" );
  DONCreerEvtEntree(NULL, "ButtonRFTrunk",        NULL, "Mod\\Cle" );
  DONCreerEntreeV(NULL,   "RF_LOCK",              0, 1, "Mod\\Cle" );
  DONCreerEntreeV(NULL,   "RF_UNLOCK",            0, 1, "Mod\\Cle" );
  DONCreerEntreeV(NULL,   "RF_TRUNK",             0, 1, "Mod\\Cle" );
  DONCreerEntreeV(NULL,   "KeyNumberUsed",        1, 3, "Mod\\Cle" );
  DONCreerEvtEntree(NULL, "VirginKey",            NULL, "Mod\\Cle" );


  //--------------------------------------------------------------------------
  // Data for "Config usine - param généraux (ReadPlantConfigParam)"
  //--------------------------------------------------------------------------
  DONCreerEntreeV(NULL,   "DEM_SURVIT"      ,0, 1, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "CALALPRI"        ,0, 1, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "CALVERDI"        ,0, 1, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "AUTDEGIVRAGE"    ,0, 1, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "RELAIS_DEM"      ,0, 1, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "DETCHOC"         ,0, 1, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "CONDATMPO"       ,0, 1, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "CONDAROU"        ,0, 1, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "CARCLIENT"       ,0, 1, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "ALIM_PLAF"       ,0, 1, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "PIL_PLAF"        ,0, 1, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "SDO"             ,0, 1, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "CPE_IMPULS"      ,0, 1, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "FEU_BROUILLARD"  ,0, 1, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "EV_ARR"          ,0, 1, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "INFO_REGIME"     ,0, 1, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "CLI_REM"         ,0, 1, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "CAD_BAGUE_AV"    ,0, 1, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "AUTCRASH"        ,0, 1, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "AUTVERLOG"       ,0, 1, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "AUTPLAF"         ,0, 1, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "KEY_BUTTON"      ,0, 1, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "CALALARM"        ,0, 1, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "CALULKTR"        ,0, 1, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "AUTRECRF"        ,0, 1, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "OUBLICEINTURE"   ,0, 1, "Mod\\AFS_RDBLID" );

  //--------------------------------------------------------------------------
  // Data for "ReadPlantCalibrationParam"
  //--------------------------------------------------------------------------
  DONCreerEntreeV(NULL,   "Read_TPS_RETARD_DETRESSE"        ,0, 8, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "Read_TIMER_DETRESSE"             ,0, 8, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "Read_TPS_APC"                    ,0, 8, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "Read_TPS_PLAF"                   ,0, 8, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "Read_TPS_ESSUIE_MINI"            ,0, 8, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "Read_TPS_MAX_COUPLBLOC"          ,0, 8, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "Read_TPS_ARRET"                  ,0, 8, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "Read_TPS_REPRISE"                ,0, 8, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "Read_TPSFILT_AF"                 ,0, 8, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "Read_TPS_POSIT_BALAIS"           ,0, 8, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "Read_PROLONG_APPUI_COURT"        ,0, 8, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "Read_PROLONG_APPUI_LONG"         ,0, 8, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "Read_TPS_APPUILAV"               ,0, 8, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "Read_TPS_POSIT_BALAIS_AR"        ,0, 8, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "Read_PROLONG_APPUI_ARR"          ,0, 8, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "Read_SEUIL_VIT_CONDAROU"         ,0, 8, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "Read_TPS_COM_MOTEUR"             ,0, 8, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "Read_NBCOM_MAX"                  ,0, 8, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "Read_TPS_REF"                    ,0, 8, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "Read_TIMER_RECONDA_AUTO"         ,0, 8, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "Read_N_MISE_APC"                 ,0, 8, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "Read_TMPMERA"                    ,0, 8, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "Read_TPS_OUVPORTE"               ,0, 8, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "Read_TPS_TEMPO_DEG"              ,0, 8, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "Read_TPS_IMPUL_MINI"             ,0, 8, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "Read_SBR_ACTIVE_SPEED_THRESH_TP"  ,0, 8, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "Read_SBR_TIME_OUT_TM_TP"          ,0, 8, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "Read_MAX_NB_ALERT_SEQUENCES_TP"   ,0, 8, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "Read_TPS_BUZ_CLI"                ,0, 8, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "Read_TPS_CLI"                    ,0, 8, "Mod\\AFS_RDBLID" );
  DONCreerEntreeV(NULL,   "Read_TPS_CLIDEGRAD"              ,0, 8, "Mod\\AFS_RDBLID" );
  
  
  //--------------------------------------------------------------------------
  // Data for "Config usine (WritePlantCalibrationParam)"
  //--------------------------------------------------------------------------
  DONCreerEvtEntree(NULL, "TPS_RETARD_DETRESSE"        ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL, "TIMER_DETRESSE"             ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL, "TPS_APC"                    ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL, "TPS_PLAF"                   ,      NULL, "Mod\\AFS_WDBLID" );  
  DONCreerEvtEntree(NULL, "TPS_ESSUIE_MINI"            ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL, "TPS_MAX_COUPLBLOC"          ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL, "TPS_ARRET"                  ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL, "TPS_REPRISE"                ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL, "TPSFILT_AF"                 ,      NULL, "Mod\\AFS_WDBLID" );  
  DONCreerEvtEntree(NULL, "TPS_POSIT_BALAIS"           ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL, "PROLONG_APPUI_COURT"        ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL, "PROLONG_APPUI_LONG"         ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL, "TPS_APPUILAV"               ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL, "TPS_POSIT_BALAIS_AR"        ,      NULL, "Mod\\AFS_WDBLID" );  
  DONCreerEvtEntree(NULL, "PROLONG_APPUI_ARR"          ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL, "SEUIL_VIT_CONDAROU"         ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL, "TPS_COM_MOTEUR"             ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL, "NBCOM_MAX"                  ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL, "TPS_REF"                    ,      NULL, "Mod\\AFS_WDBLID" );  
  DONCreerEvtEntree(NULL, "TIMER_RECONDA_AUTO"         ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL, "N_MISE_APC"                 ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL, "TMPMERA"                    ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL, "TPS_OUVPORTE"               ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL, "TPS_TEMPO_DEG"              ,      NULL, "Mod\\AFS_WDBLID" );  
  DONCreerEvtEntree(NULL, "TPS_IMPUL_MINI"             ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL, "SBR_ACTIVE_SPEED_THRESH_TP" ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL, "SBR_TIME_OUT_TM_TP"         ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL, "MAX_NB_ALERT_SEQUENCES_TP"  ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL, "TPS_BUZ_CLI"                ,      NULL, "Mod\\AFS_WDBLID" );  
  DONCreerEvtEntree(NULL, "TPS_CLI"                    ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL, "TPS_CLIDEGRAD"              ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEntreeV( NULL,  "Write_CalibrParamByteNbr",  0, 8,"Mod\\AFS_WDBLID" );
  DONCreerEntreeV( NULL,  "Write_CalibrParamValue",    0, 8,"Mod\\AFS_WDBLID" );

    //--------------------------------------------------------------------------
  // Data for "Config usine (SendWriteConfigParam)"
  //--------------------------------------------------------------------------
  DONCreerEvtEntree(NULL,   "Set_DEM_SURVIT"      ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL,   "Set_CALALPRI"        ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL,   "Set_CALVERDI"        ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL,   "Set_AUTDEGIVRAGE"    ,      NULL, "Mod\\AFS_WDBLID" );  
  DONCreerEvtEntree(NULL,   "Set_RELAIS_DEM"      ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL,   "Set_DETCHOC"         ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL,   "Set_CONDATMPO"       ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL,   "Set_CONDAROU"        ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL,   "Set_CARCLIENT"       ,      NULL, "Mod\\AFS_WDBLID" );  
  DONCreerEvtEntree(NULL,   "Set_ALIM_PLAF"       ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL,   "Set_PIL_PLAF"        ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL,   "Set_SDO"             ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL,   "Set_CPE_IMPULS"      ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL,   "Set_FEU_BROUILLARD"  ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL,   "Set_EV_ARR"          ,      NULL, "Mod\\AFS_WDBLID" );  
  DONCreerEvtEntree(NULL,   "Set_INFO_REGIME"     ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL,   "Set_CLI_REM"         ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL,   "Set_CAD_BAGUE_AV"    ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL,   "Set_AUTCRASH"        ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL,   "Set_AUTVERLOG"       ,      NULL, "Mod\\AFS_WDBLID" );  
  DONCreerEvtEntree(NULL,   "Set_AUTPLAF"         ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL,   "Set_KEY_BUTTON"      ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL,   "Set_CALALARM"        ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL,   "Set_CALULKTR"        ,      NULL, "Mod\\AFS_WDBLID" );
  DONCreerEvtEntree(NULL,   "Set_AUTRECRF"        ,      NULL, "Mod\\AFS_WDBLID" );  
  DONCreerEvtEntree(NULL,   "Set_OUBLICEINTURE"   ,      NULL, "Mod\\AFS_WDBLID" );

  DONCreerEntreeV( NULL,  "Write_ConfigParamValue"  ,    0, 1,"Mod\\AFS_WDBLID" );

  //--------------------------------------------------------------------------
  // Data for BCM Identification
  //--------------------------------------------------------------------------
  // Data for Read Software Version in TFC Mode ($21 $90)"
  DONCreerEvtEntree(NULL, "ReadSoftwareAndVersionTFCMode",   NULL, "Mod\\BCMIdent" );
  DONCreerEntreeB( NULL,  "SoftVersion",                   0, 18,"Modele\\BCMIdent" );
  DONCreerEntreeB( NULL,  "Checksum",                      0, 36,"Modele\\BCMIdent" );
  DONCreerEntreeB( NULL,  "TFCVersion",                    0, 18,"Modele\\BCMIdent" );

  // Data for Read BCM Ident in AFS Mode ($21 $80)"
  DONCreerEvtEntree(NULL, "ReadBCMIdentificationAFSMode",   NULL, "Mod\\BCMIdent" );
  DONCreerEntreeB( NULL,  "ItemNber",                      0, 40,"Modele\\BCMIdent" );
  DONCreerEntreeB( NULL,  "Vdiag",                         0, 8,"Modele\\BCMIdent" );
  DONCreerEntreeB( NULL,  "ProviderNber",                  0, 24,"Modele\\BCMIdent" );
  DONCreerEntreeB( NULL,  "HWNber",                        0, 40,"Modele\\BCMIdent" );
  DONCreerEntreeB( NULL,  "SWVersion",                     0, 16,"Modele\\BCMIdent" );
  DONCreerEntreeB( NULL,  "SWRevision",                    0, 16,"Modele\\BCMIdent" );
  DONCreerEntreeB( NULL,  "HWRevision",                    0, 16,"Modele\\BCMIdent" );
  DONCreerEntreeB( NULL,  "TypeBCM",                       0, 8,"Modele\\BCMIdent" );
  DONCreerEntreeV( NULL,  "SerialNber",                    0, 24,"Modele\\BCMIdent" );

  // Data for Write Vdiag in TFC Mode ($21 $81)"
  DONCreerEvtEntree(NULL, "ReadBCM_VINID",               NULL, "Mod\\BCMIdent" );
  

  //--------------------------------------------------------------------------
  // Data for "Lecture des entrées and états du véhicule ($21 $DC)"
  //--------------------------------------------------------------------------
  DONCreerEntreeV(NULL,   "I_PWR_IGN",        0, 1, "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "I_DOOR_LOCK_SW",   0, 1, "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "I_DOOR_UNLOCK_SW", 0, 1, "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "I_RR_WASHER_SW",   0, 1, "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "I_DEFROSTER_SW",   0, 1, "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "I_RX_IMMOBILIZER", 0, 1, "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "I_RR_AUTOSTOP_SW", 0, 1, "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "I_RR_WIPER_INT_SW",0, 1, "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "I_POSITION_LIGHTS",0, 1, "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "I_HAZARD_SW",      0, 1, "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "I_R_FLASHER_SW",   0, 1, "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "I_L_FLASHER_SW",   0, 1, "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "I_FR_DOORS_SW",    0, 1, "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "I_FR_AUTOSTOP_SW", 0, 1, "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "I_RR_DOORS_SW",    0, 1, "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "I_FR_WASHER_SW",   0, 1, "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "I_FR_WIPER_INT_SW",0, 1, "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "I_AIRBAG_CRASH",   0, 1, "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "I_RX_VERLOG",      0, 1, "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "I_FR_FOG_SW_I_HIGH_LOW_BEAM",  0, 1, "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "I_RR_FOG_SW",                  0, 1, "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "I_SEATBELT_REMINDER_SW",       0, 1, "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "I_ENGINE_RPM",                 0, 2, "Mod\\DiagReadInput" );

 
  //--------------------------------------------------------------------------
  // Data for "Commande directe des actuateurs ($30 $XX)"
  //--------------------------------------------------------------------------
  DONCreerEvtEntree(NULL, "CPE_TOUS",               NULL,   "Mod\\DiagReadInput" );
  DONCreerEvtEntree(NULL, "CPE_PASSENGER",          NULL,   "Mod\\DiagReadInput" );
  DONCreerEvtEntree(NULL, "CPE_COMMUN",             NULL,   "Mod\\DiagReadInput" );
  DONCreerEvtEntree(NULL, "CPE_SUPERCONDA",         NULL,   "Mod\\DiagReadInput" );
  DONCreerEvtEntree(NULL, "CPE_COFFRE",             NULL,   "Mod\\DiagReadInput" );
  DONCreerEvtEntree(NULL, "CPE_SDO",                NULL,   "Mod\\DiagReadInput" );
  DONCreerEvtEntree(NULL, "CPE_PLCG",               NULL,   "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "CROISSEMENT",            0, 1,   "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "ROUTE",                  0, 1,   "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "CPE_SUPER_CONDA_COFFRE", 0, 1,   "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "CLIG_D",                 0, 1,   "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "CLIG_G",                 0, 1,   "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "PLAF_AVANT",             0, 1,   "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "PLAF_ARRIERE",           0, 1,   "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "ESSAV_PV",               0, 1,   "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "ESSAV_GV",               0, 1,   "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "ESSAR",                  0, 1,   "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "ALIM_TPO",               0, 1,   "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "LED_CPE",                0, 1,   "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "LED_VERLOG",             0, 1,   "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "VOYANT_DET",             0, 1,   "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "LARC",                   0, 1,   "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "LVI_MONT",               0, 1,   "Mod\\DiagReadInput" );
  DONCreerEntreeV(NULL,   "LVI_DESC",               0, 1,   "Mod\\DiagReadInput" );

  //--------------------------------------------------------------------------
  // Data for "Lecture des entrées Défaut ($21 $94)"
  //--------------------------------------------------------------------------
  DONCreerEntreeV(NULL,   "DEF_BTON_CPEOUV",        0, 1, "Mod\\DiagReadDefault" );
  DONCreerEntreeV(NULL,   "DEF_BTON_CPEFER",        0, 1, "Mod\\DiagReadDefault" );
  DONCreerEntreeV(NULL,   "DEF_AFAV",               0, 1, "Mod\\DiagReadDefault" );
  DONCreerEntreeV(NULL,   "DEF_AFAR",               0, 1, "Mod\\DiagReadDefault" );
  DONCreerEntreeV(NULL,   "DEF_AIRBAG",             0, 1, "Mod\\DiagReadDefault" );
  DONCreerEntreeV(NULL,   "DEF_CLIGN",              0, 1, "Mod\\DiagReadDefault" );
  DONCreerEntreeV(NULL,   "DEF_EEPROM",             0, 1, "Mod\\DiagReadDefault" );
  DONCreerEntreeV(NULL,   "DEF_CCp_TRANSP",         0, 1, "Mod\\DiagReadDefault" );
  DONCreerEntreeV(NULL,   "DEF_CCm_TRANSP",         0, 1, "Mod\\DiagReadDefault" );
  DONCreerEntreeV(NULL,   "DEF_CCp_VERLOG",         0, 1, "Mod\\DiagReadDefault" );
  DONCreerEntreeV(NULL,   "DEF_CCm_VERLOG",         0, 1, "Mod\\DiagReadDefault" );
  DONCreerEntreeV(NULL,   "DEF_ACK_VERLOG",         0, 1, "Mod\\DiagReadDefault" );
  DONCreerEntreeV(NULL,   "DEF_CCp_LARD",           0, 1, "Mod\\DiagReadDefault" );
  DONCreerEntreeV(NULL,   "DEF_CO_LARD",            0, 1, "Mod\\DiagReadDefault" );
  DONCreerEntreeV(NULL,   "DEF_CCp_DEMARREUR",      0, 1, "Mod\\DiagReadDefault" );
  DONCreerEntreeV(NULL,   "DEF_CO_DEMARREUR",       0, 1, "Mod\\DiagReadDefault" );

  DONCreerEntreeV(NULL,   "compt_nb_int",           0, 8, "Mod\\DiagReadDefault" );
  DONCreerEntreeV(NULL,   "COD_ERR_APP",            0, 8, "Mod\\DiagReadDefault" );
  DONCreerEntreeV(NULL,   "DEFM_AFAV",              0, 1, "Mod\\DiagReadDefault" );
  DONCreerEntreeV(NULL,   "DEFM_AFAR",              0, 1, "Mod\\DiagReadDefault" );
  DONCreerEntreeV(NULL,   "DEFM_AIRBAG",            0, 1, "Mod\\DiagReadDefault" );
  DONCreerEntreeV(NULL,   "DEFM_CLIGN",             0, 1, "Mod\\DiagReadDefault" );
  DONCreerEntreeV(NULL,   "DEFM_EEPROM",            0, 1, "Mod\\DiagReadDefault" );
  DONCreerEntreeV(NULL,   "DEFM_CCp_TRANSP",        0, 1, "Mod\\DiagReadDefault" );
  DONCreerEntreeV(NULL,   "DEFM_CCm_TRANSP",        0, 1, "Mod\\DiagReadDefault" );
  DONCreerEntreeV(NULL,   "DEFM_CCm_VERLOG",        0, 1, "Mod\\DiagReadDefault" );
  DONCreerEntreeV(NULL,   "DEFM_CCp_VERLOG",        0, 1, "Mod\\DiagReadDefault" );
  DONCreerEntreeV(NULL,   "DEFM_ACK_VERLOG",        0, 1, "Mod\\DiagReadDefault" );
  DONCreerEntreeV(NULL,   "DEFM_CCp_LARD",          0, 1, "Mod\\DiagReadDefault" );
  DONCreerEntreeV(NULL,   "DEFM_CO_LARD",           0, 1, "Mod\\DiagReadDefault" );
  DONCreerEntreeV(NULL,   "DEFM_CCp_DEMARREUR",     0, 1, "Mod\\DiagReadDefault" );
  DONCreerEntreeV(NULL,   "DEFM_CO_DEMARREUR",      0, 1, "Mod\\DiagReadDefault" );
  
  DONCreerEntreeV(NULL,   "CMPT_RESYNC"   ,         0, 8, "Mod\\DiagReadDefault" );
  DONCreerEntreeV(NULL,   "CMPT_ECHEC_RESYNC"   ,   0, 8, "Mod\\DiagReadDefault" );
  DONCreerEntreeV(NULL,   "CMPT_RETARD_TR"   ,      0, 8, "Mod\\DiagReadDefault" );
  DONCreerEntreeV(NULL,   "CMPT_ECHEC_TR"   ,       0, 8, "Mod\\DiagReadDefault" );
  DONCreerEntreeV(NULL,   "CMPT_RESET"   ,          0, 8, "Mod\\DiagReadDefault" );
  DONCreerEntreeV(NULL,   "CMPT_CHOC"   ,           0, 8, "Mod\\DiagReadDefault" );
  

  //-------------------------------------------------------------------------
  // Data for "Lecture des entrées Ana ($21 $DE)"
  //--------------------------------------------------------------------------
  DONCreerEntreeV(NULL,   "ReadVehicleSpeed",           0, 16,  "Mod\\DiagCodedInput" );
  DONCreerEntreeV(NULL,   "ReadDIAG_FLASHER",           0, 8,   "Mod\\DiagCodedInput" );
  DONCreerEntreeV(NULL,   "ReadDIAG_BAT",               0, 8,   "Mod\\DiagCodedInput" );
  
  //--------------------------------------------------------------------------
  // Data for "Immobilizer Diagnostic"
  //--------------------------------------------------------------------------

  DONCreerEvtEntree(NULL, "TestBlankKey",                    NULL, "Mod\\ImmoDiag" );
  DONCreerEvtEntree(NULL, "StartPermanentAuthentication",    NULL, "Mod\\ImmoDiag" );
  DONCreerEvtEntree(NULL, "StopPermanentAuthentication",     NULL, "Mod\\ImmoDiag" );
  DONCreerEvtEntree(NULL, "EraseAfterSalesCode",             NULL, "Mod\\ImmoDiag" );
  DONCreerEvtEntree(NULL, "EraseImmobilzerData",             NULL, "Mod\\ImmoDiag" );
  

  DONCreerEvtEntree(NULL, "EnterInLearningPlantMode",        NULL, "Mod\\ImmoDiag" );
  DONCreerEvtEntree(NULL, "ExitFromLearningPlantMode",       NULL, "Mod\\ImmoDiag" );
  DONCreerEvtEntree(NULL, "ValidateAFSKeyLearning",          NULL, "Mod\\ImmoDiag" );
  DONCreerEvtEntree(NULL, "GiveUpAFSKeyLearning",            NULL, "Mod\\ImmoDiag" );

   // Evt de la trame de Commande
  DONCreerEvtEntree( &EnterInAFSKeyLearningModeNIC, "EvtEnterInAFSKeyLearningMode", NULL , "Modele\\ImmoDiag");
  // Creation du buffer de la trame recue
   tU8Bit pBufferImmoR[32*8] = {0};
  DONCreerEntreeB(&EnterInAFSKeyLearningModeNIC, "EnterInAFSKeyLearningMode", pBufferImmoR, 32*8, "Modele\\ImmoDiag");
  // Taille du buffer de la trame recue
  DONCreerEntreeV(&EnterInAFSKeyLearningModeNIC, "SizeEnterInAFSKeyLearningModeRequest", 0, 6, "Modele\\ImmoDiag");

  DONCreerEvtEntree(NULL, "ReadAFSCode",                      NULL, "Mod\\ImmoDiag" );
  DONCreerEntreeB( NULL,  "AfterSalesCode",                   0, 48,"Modele\\ImmoDiag");

  DONCreerEvtEntree(NULL, "ReadImmoConfidentialData",         NULL, "Mod\\ImmoDiag" );
  DONCreerEntreeV(NULL,   "KeyLearntNumber",                  0, 8, "Mod\\ImmoDiag" ); 
  DONCreerEntreeB( NULL,  "IDE_KEY1",                         0, 32,"Modele\\ImmoDiag" );
  DONCreerEntreeB( NULL,  "IDE_KEY2",                         0, 32,"Modele\\ImmoDiag" );
  DONCreerEntreeB( NULL,  "IDE_KEY3",                         0, 32,"Modele\\ImmoDiag" );
  DONCreerEntreeB( NULL,  "IDE_KEY4",                         0, 32,"Modele\\ImmoDiag" );
  DONCreerEntreeB( NULL,  "ISK",                              0, 48,"Modele\\ImmoDiag" );
  DONCreerEntreeB( NULL,  "PWD_TAG1",                         0, 24,"Modele\\ImmoDiag" );
  DONCreerEntreeB( NULL,  "PWD_TAG2",                         0, 24,"Modele\\ImmoDiag" );
  DONCreerEntreeB( NULL,  "PWD_TAG3",                         0, 24,"Modele\\ImmoDiag" );
  DONCreerEntreeB( NULL,  "PWD_TAG4",                         0, 24,"Modele\\ImmoDiag" );

  DONCreerEvtEntree(NULL, "ReadImmoConfDynamicData",          NULL, "Mod\\ImmoDiag" );  
  DONCreerEntreeB( NULL,  "ChallengeRandomNb",                0, 32,"Modele\\ImmoDiag" );
  DONCreerEntreeB( NULL,  "ChallengeSignature",               0, 32,"Modele\\ImmoDiag" );
  DONCreerEntreeB( NULL,  "RepToChallenge",                   0, 32,"Modele\\ImmoDiag" );
  DONCreerEntreeB( NULL,  "RepToChallengeDecrypt",            0, 32,"Modele\\ImmoDiag" );
  DONCreerEntreeB( NULL,  "ResyncValue",                      0, 32,"Modele\\ImmoDiag" );
  DONCreerEntreeB( NULL,  "RollingCode",                      0, 32,"Modele\\ImmoDiag" );

  
  
  DONCreerEntreeV(NULL,   "ImmoAndRFDataPeriodicalReading",   0, 1, "Mod\\ImmoDiag" );
  DONCreerEntreeV(NULL,   "UCH_VIERGE" ,                      0, 1, "Mod\\ImmoDiag" );
  DONCreerEntreeV(NULL,   "IDENT_RECU" ,                      0, 1, "Mod\\ImmoDiag" );
  DONCreerEntreeV(NULL,   "IDENT_VALID" ,                     0, 1, "Mod\\ImmoDiag" );
  DONCreerEntreeV(NULL,   "REP_PRESENTE" ,                    0, 1, "Mod\\ImmoDiag" );
  DONCreerEntreeV(NULL,   "REP_BONNE" ,                       0, 1, "Mod\\ImmoDiag" );
  
  DONCreerEntreeV(NULL,   "VERLOGON" ,                        0, 1, "Mod\\ImmoDiag" );
  DONCreerEntreeV(NULL,   "CLE_1" ,                           0, 1, "Mod\\ImmoDiag" );
  DONCreerEntreeV(NULL,   "CLE_2" ,                           0, 1, "Mod\\ImmoDiag" );
  DONCreerEntreeV(NULL,   "CLE_3" ,                           0, 1, "Mod\\ImmoDiag" );
  DONCreerEntreeV(NULL,   "CLE_4" ,                           0, 1, "Mod\\ImmoDiag" );
  DONCreerEntreeV(NULL,   "FRQ_CLE_PRESENTE" ,                0, 3, "Mod\\ImmoDiag" );
  DONCreerEntreeV(NULL,   "CLE_VIERGE" ,                      0, 1, "Mod\\ImmoDiag" );
  DONCreerEntreeV(NULL,   "CLE_LOCKE" ,                       0, 1, "Mod\\ImmoDiag" );
  DONCreerEntreeV(NULL,   "MODE_USINE_APP" ,                  0, 1, "Mod\\ImmoDiag" );
  DONCreerEntreeV(NULL,   "MODE_APV_APP" ,                    0, 1, "Mod\\ImmoDiag" );
  DONCreerEntreeV(NULL,   "MODE_APV_REAF" ,                   0, 1, "Mod\\ImmoDiag" );
  DONCreerEntreeV(NULL,   "APP_CLE_NON_EFFECT" ,              0, 1, "Mod\\ImmoDiag" );
  
  DONCreerEntreeV(NULL,   "CODE_APV_DISPO" ,                  0, 1, "Mod\\ImmoDiag" );
  DONCreerEntreeV(NULL,   "CODE_APV_RECONNU" ,                0, 1, "Mod\\ImmoDiag" );
  DONCreerEntreeV(NULL,   "cde_eff_code_recu" ,               0, 1, "Mod\\ImmoDiag" );
  DONCreerEntreeB(NULL,   "IDE_CLE_TRP",                      0, 32,"Modele\\ImmoDiag");
  DONCreerEntreeV(NULL,   "CMPT_CLES" ,                       0, 8, "Mod\\ImmoDiag" );
  DONCreerEntreeV(NULL,   "CMPT_STD_433" ,                    0, 8, "Mod\\ImmoDiag" );
  DONCreerEntreeV(NULL,   "CMPT_STD_315" ,                    0, 8, "Mod\\ImmoDiag" );
  
  DONCreerEntreeV(NULL,   "ETAT_VEH_CONDA_DECONDA" ,          0, 1, "Mod\\ImmoDiag" );
  DONCreerEntreeV(NULL,   "DERNIERE_CMD" ,                    0, 1, "Mod\\ImmoDiag" );
  DONCreerEntreeV(NULL,   "RECONDA_AUTO" ,                    0, 1, "Mod\\ImmoDiag" );
  DONCreerEntreeV(NULL,   "CONDAROU_ACTIVE" ,                 0, 1, "Mod\\ImmoDiag" );
  DONCreerEntreeV(NULL,   "CONDAROU_ROULANT" ,                0, 1, "Mod\\ImmoDiag" );
  DONCreerEntreeV(NULL,   "VEHICULE_ROULANT" ,                0, 1, "Mod\\ImmoDiag" );
  DONCreerEntreeV(NULL,   "VEHICULE_APC" ,                    0, 1, "Mod\\ImmoDiag" );
  
  DONCreerEntreeV(NULL,   "DR_DOOR_UNLOCK_PUSH" ,             0, 1, "Mod\\ImmoDiag" );
  DONCreerEntreeV(NULL,   "DOOR_UNLOCK_PUSH" ,                0, 1, "Mod\\ImmoDiag" );
  DONCreerEntreeV(NULL,   "DOOR_LOCK_PUSH" ,                  0, 1, "Mod\\ImmoDiag" );
  
  DONCreerEntreeV(NULL,   "TRF_RECU" ,                        0, 1, "Mod\\ImmoDiag" );
  DONCreerEntreeV(NULL,   "TRF_OK" ,                          0, 1, "Mod\\ImmoDiag" );
  
  DONCreerEntreeB( NULL,  "IDE_CLE_RF",                       0, 32,"Modele\\ImmoDiag");
  DONCreerEntreeB( NULL,  "NbTryAuthent",                     0, 16,"Modele\\ImmoDiag");
  DONCreerEntreeV(NULL,   "NbFailAuthent" ,                   0, 8, "Mod\\ImmoDiag" );
  DONCreerEntreeV(NULL,   "NbResyncFail" ,                    0, 8, "Mod\\ImmoDiag" );
  
  DONCreerEntreeV(NULL,   "ImmoNegativeAnswer",               0, 1, "Mod\\ImmoDiag" );
  DONCreerEntreeV(NULL,   "PositiveAnswer",                   0, 1, "Mod\\ImmoDiag" );

  //--------------------------------------------------------------------------
  // Data for "Diagnostic modele"
  //--------------------------------------------------------------------------
  DONCreerEvtEntree(NULL, "SendStartCom",                   NULL, "Mod\\Diag" );
  DONCreerEvtEntree(NULL, "SendClearAllFailures",           NULL, "Mod\\Diag" );
  //DONCreerEvtEntree(NULL, "SendAlarmTest",                  NULL, "Mod\\Diag" );
  //DONCreerEvtEntree(NULL, "SendWriteConfigParam",           NULL, "Mod\\Diag" );
  DONCreerEvtEntree(NULL, "ReadPlantConfigParam",           NULL, "Mod\\Diag" );
  DONCreerEvtEntree(NULL, "ReadPlantCalibrationParam",      NULL, "Mod\\Diag" );
  //DONCreerEvtEntree(NULL, "WritePlantCalibrationParam",          NULL, "Mod\\Diag" ); // Write calibr byte
  //DONCreerEvtEntree(NULL, "SendWriteCalType",               NULL, "Mod\\Diag" );
  DONCreerEntreeV(NULL,   "DigitalInputPeriodicalReading",  0, 1, "Mod\\Diag" );
  //DONCreerEntreeV(NULL,   "GMPDataPeriodicalReading",       0, 1, "Mod\\Diag" );
  DONCreerEntreeV(NULL,   "MaintienCommunication",          0, 1, "Mod\\Diag" );
  DONCreerEntreeV(NULL,   "NegativeResponse",               0, 1, "Mod\\Diag" );
  DONCreerEntreeV(NULL,   "RDBLI_PositiveResponse",         0, 1, "Mod\\Diag" );
  DONCreerEntreeV(NULL,   "WDBLI_PositiveResponse",         0, 1, "Mod\\Diag" );
  DONCreerEntreeV(NULL,   "CodedValuePeriodicalReading",    0, 1, "Mod\\Diag" );
  //DONCreerEvtEntree(NULL, "EraseGMPData",                  NULL, "Mod\\Diag" );
  DONCreerEntreeV(NULL,   "DefaultPeriodicalReading",       0, 1, "Mod\\Diag" );

  // Data for Smile Eeprom
//  DONCreerEntreeV(NULL,   "SmileInProgress",                0, 1, "Mod\\Diag" );
//  DONCreerEntreeV(NULL,   "EepromWithKeyLearnt",            0, 1, "Mod\\Diag" );
//  DONCreerEvtEntree(NULL, "SmileEeprom",                    NULL, "Mod\\Diag" );  

  // Data for Calibration type
//  DONCreerEntreeV(NULL,   "CalTyp3A" ,                      156, 8, "Mod\\Diag" );
//  DONCreerEntreeV(NULL,   "CalTyp6A" ,                      160, 8, "Mod\\Diag" );


  //--------------------------------------------------------------------------
  // Data for "TFC model"
  //--------------------------------------------------------------------------
  DONCreerEvtEntree(NULL, "OpenTFCDiagnosticSession",        NULL, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFCMaintienCom",                   0, 1, "Mod\\TFC" );

  DONCreerEntreeV(NULL,   "TFCReadDigitalInput",                  0, 1, "Mod\\TFC" );

  DONCreerEntreeV(NULL,   "TFC_ENGINE_RPM",              0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_PWR_IGN",                 0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_Fixed1",                  0, 1, "Mod\\TFC" );                     
  DONCreerEntreeV(NULL,   "TFC_RR_WASHER_SW",            0, 1, "Mod\\TFC" );                     
  DONCreerEntreeV(NULL,   "TFC_FR_FOG_SW",               0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_RX_IMOBILIZER",           0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_Fixed2",                  0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_RX_VERLOG",               0, 1, "Mod\\TFC" );

  DONCreerEntreeV(NULL,   "TFC_L_FLASHER_SW",            0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_Fixed3",                  0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_Fixed4",                  0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_FR_DOORS_SW",             0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_DOOR_LOCK_SW",            0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_FR_WIPER_INT_SW",         0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_RR_FOG_SW",               0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_FR_WASHER_SW",            0, 1, "Mod\\TFC" );
                   
  DONCreerEntreeV(NULL,   "TFC_AIRBAG_CRASH",            0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_VEHICLE_SPEED",           0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_FR_AUTOSTOP_SW",          0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_RR_AUTOSTOP_SW",          0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_Fixed5",                  0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_Fixed6",                  0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_HAZARD_SW",               0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_R_FLASHER_SW",            0, 1, "Mod\\TFC" );
                   
  DONCreerEntreeV(NULL,   "TFC_Fixed7",                  0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_RR_WIPER_INT_SW",         0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_Fixed8",                  0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_POSITION_LIGHTS",         0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_RR_DOORS_SW",             0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_DOOR_UNLOCK_SW",          0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_DEFROSTER_SW",            0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_SEATBELT_REMINDER_SW",    0, 1, "Mod\\TFC" );

  DONCreerEntreeV(NULL,   "TFCReadAnalogInput",        0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_DIAG_BAT",              0, 16,  "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_DIAG_DRIVER_ULQ",       0, 16,  "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_DIAG_DRIVER_KLAXON",    0, 16,  "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_DIAG_FLASHER",          0, 16,  "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_DIAG_DRIVER_HIGH_SIDE", 0, 16,  "Mod\\TFC" );  
  DONCreerEntreeV(NULL,   "TFC_VehicleSpeed",          0, 16,  "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_EngineRpm",             0, 16,  "Mod\\TFC" );
  
  DONCreerEvtEntree(NULL, "StartAutoTestRoutine",              NULL, "Mod\\TFC" );
  //DONCreerEntreeB(NULL,   "OrderingMatrix",                0,48*8,   "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "SequenceMode",                     0, 8,  "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "StartDelayIn10ms",                 0, 8,  "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "SetupTime",                        0, 8,  "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "ActivationTimeOut",                0, 8,  "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "FilterTimeConstant",               0, 8,  "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "SynchroTimeOutIn10ms",             0, 8,  "Mod\\TFC" );  
  DONCreerEntreeV(NULL,   "OrderingMatrixSize",               0, 8,  "Mod\\TFC" );

  DONCreerEvtEntree(NULL, "StopAutoTestRoutine",               NULL, "Mod\\TFC" );
  DONCreerEntreeB(NULL,   "StopAutoTestResp",               0, 9*8,  "Mod\\TFC" );

  DONCreerEntreeV(NULL,   "TFC_OutDI_LEFT",                0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_OutDI_RIGHT",               0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_OutRR_WIPER_RR_FOG_LAMP",   0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_OutLOCK_DOORS",             0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_OutUNLOCK_DOORS",           0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_OutUNLOCK_DRIVER_DOOR",     0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_OutFRONT_WIPER",            0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_OutBAT_LIGHT_TEMPO",        0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_OutDEFROSTER",              0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_OutHORN_RL",                0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_OutOPEN_DOOR_LED",          0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_OutVERLOG_LED",             0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_OutDO_VERLOG",              0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_OutDO_DATA_IMMOBILIZER",    0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_OutPWM_ROOMLAMP",           0, 1, "Mod\\TFC" );
  DONCreerEntreeV(NULL,   "TFC_OutBUZZER",                 0, 1, "Mod\\TFC" );

  DONCreerEvtEntree(NULL, "StartRfTestRoutine",            NULL, "Mod\\TFC" );
  DONCreerEvtEntree(NULL, "StatusRfTestRoutine",           NULL, "Mod\\TFC" );
  

/*
  
  //--------------------------------------------------------------------------
  // Data for "Front wiper"
  //--------------------------------------------------------------------------
  DONCreerEntreeV(NULL,   "WIPING_TIME_GV",              1000, 16, "Mod\\FrtWiper");
  DONCreerEntreeV(NULL,   "WIPING_TIME_PV",              2300, 16, "Mod\\FrtWiper");
  DONCreerEntreeV(NULL,   "WIPING_AUTO_RETURN",             1,  1, "Mod\\FrtWiper");
  DONCreerEntreeV(NULL,   "WIPING_TIME_R",               2500, 16, "Mod\\RrWiper");
 
  //--------------------------------------------------------------------------
  // Data for analog input
  //--------------------------------------------------------------------------
  DONCreerEntreeV(NULL,   "MODDiagCpe",             0,   16, "Mod\\Ana"); 
  DONCreerEntreeV(NULL,   "MODPdo",                 0,   16, "Mod\\Ana"); 
  DONCreerEntreeV(NULL,   "MODShuntLvi",            0,   16, "Mod\\Ana"); 
  DONCreerEntreeV(NULL,   "MODCourantCli",          0,   16, "Mod\\Ana"); 
  DONCreerEntreeV(NULL,   "MODDiagBattCli",     13000,   16, "Mod\\Ana"); 
  DONCreerEntreeV(NULL,   "MODDiagBatterie",    13000,   16, "Mod\\Ana"); 
  DONCreerEntreeV(NULL,   "MODAnaCmdEsavCadence",   0,   16, "Mod\\Ana"); 
  DONCreerEntreeV(NULL,   "MODDiagLedVerlog",       0,   16, "Mod\\Ana"); 
  DONCreerEntreeV(NULL,   "MODAnaCtcArretFixeAr",   0,   16, "Mod\\Ana"); 
  DONCreerEntreeV(NULL,   "MODAnaCtcArretFixeAv",   0,   16, "Mod\\Ana"); 
  DONCreerEntreeV(NULL,   "MODDiagULQ1",            0,   16, "Mod\\Ana"); 
  DONCreerEntreeV(NULL,   "MODDiagULQ2",            0,   16, "Mod\\Ana"); 
  DONCreerEntreeV(NULL,   "MODDiagULQ3",            0,   16, "Mod\\Ana"); 

  DONCreerEntreeV(NULL,   "CMD_ESAV_CADENCE_AUTOMATIC",   1, 1, "Mod\\Ana"); 
  DONCreerEntreeV(NULL,   "CTC_ARRET_FIXE_AR_AUTOMATIC",  1, 1, "Mod\\Ana"); 
  DONCreerEntreeV(NULL,   "CTC_ARRET_FIXE_AV_AUTOMATIC",  1, 1, "Mod\\Ana"); 

  //--------------------------------------------------------------------------
  // Data for "Flasher"
  //--------------------------------------------------------------------------
  DONCreerEntreeV(NULL,   "FLA_LEFT_BULB_FAILURE",      0, 1, "Mod\\Flasher");
  DONCreerEntreeV(NULL,   "FLA_RIGHT_BULB_FAILURE",     0, 1, "Mod\\Flasher");
  DONCreerEntreeV(NULL,   "FLA_TRAILER",                0, 1, "Mod\\Flasher");
  DONCreerEntreeV(NULL,   "FLA_LEFT_5_TO_21W_BULB",     0, 1, "Mod\\Flasher");
  DONCreerEntreeV(NULL,   "FLA_RIGHT_5_TO_21W_BULB",    0, 1, "Mod\\Flasher");
 
  //--------------------------------------------------------------------------
  // Data for "Batt Elec "
  //--------------------------------------------------------------------------
  DONCreerEntreeV(NULL,   "BattElecVoltage",            0,   16, "Mod\\Ana"); 

  //--------------------------------------------------------------------------
  // Data for "Window lift"
  //--------------------------------------------------------------------------
  DONCreerEntreeV(NULL,   "LVI_FAILURE",            0,    1, "Mod\\WinLift");

  //--------------------------------------------------------------------------
  // Data for "light and rain sensor (LRS)"
  //--------------------------------------------------------------------------
  DONCreerEntreeV(NULL,   "LrsLightIntensity",      0,    8, "Mod\\Lrs");

  //--------------------------------------------------------------------------
  // IHM data
  //--------------------------------------------------------------------------
  DONCreerEntreeV(NULL,   "IHMCroisement2",         0,    1, "Mod\\Ihm");
  DONCreerEntreeV(NULL,   "IHMRearWiperPosition",   0,    8, "Mod\\Ihm");
  DONCreerEntreeV(NULL,   "IHMFrontWiperPosition",  0,    8, "Mod\\Ihm");
  DONCreerEntreeV(NULL,   "IHMFrontWiperPosition2", 0,    8, "Mod\\Ihm");
                          
  DONCreerEntreeV(NULL,   "IHMWindowStallDetected", 0,    1, "Mod\\Ihm");
  DONCreerEntreeV(NULL,   "IHMWindowClosed",        0,    1, "Mod\\Ihm");
  DONCreerEntreeV(NULL,   "IHMWindowOpened",        0,    1, "Mod\\Ihm");
  DONCreerEntreeV(NULL,   "IHMWindowPosition",      0,    8, "Mod\\Ihm");

  //--------------------------------------------------------------------------
  // Data for inverted logic input
  //--------------------------------------------------------------------------
  DONCreerEntreeV(NULL,   "MODCmdLviD",             0,    1, "Mod\\Tor");
  DONCreerEntreeV(NULL,   "MODCmdLviM",             0,    1, "Mod\\Tor");
  DONCreerEntreeV(NULL,   "MODCmdLarc",             0,    1, "Mod\\Tor");

  //--------------------------------------------------------------------------
  // Data for "Cpe"
  //--------------------------------------------------------------------------
  DONCreerEntreeV(NULL,   "StateCpeConducteur",     0,    2, "Mod\\Cpe");
  DONCreerEntreeV(NULL,   "StateCpePassager",       0,    2, "Mod\\Cpe");
  DONCreerEntreeV(NULL,   "StateCpePlcgPlcd",       0,    2, "Mod\\Cpe");
  DONCreerEntreeV(NULL,   "StateCpeCoffre",         0,    2, "Mod\\Cpe");

  //--------------------------------------------------------------------------
  // Data for "Airbag"
  //--------------------------------------------------------------------------
  DONCreerEntreeV(NULL,   "RbgLowStateDuration",    0,   16, "Mod\\Rbg");
  DONCreerEntreeV(NULL,   "RbgHighStateDuration",   0,   16, "Mod\\Rbg");
  DONCreerEntreeV(NULL,   "RbgPulseDuration",       0,   16, "Mod\\Rbg");
  DONCreerEvtEntree(NULL, "RbgSendPulse",           NULL,    "Mod\\Rbg");

  //--------------------------------------------------------------------------
  // Data for "Siren"
  //--------------------------------------------------------------------------
  DONCreerEntreeV(NULL,   "SirResponseEnable",      1,   1, "Mod\\Sir");
  DONCreerEntreeV(NULL,   "SirenMode"        ,      0,   2, "Mod\\Sir");
  DONCreerEntreeV(NULL,   "SirenParity"      ,      0,   1, "Mod\\Sir");
  DONCreerEntreeV(NULL,   "SirenStatus"      ,      0,   2, "Mod\\Sir");

  //--------------------------------------------------------------------------
  // Data for "Siren"
  //--------------------------------------------------------------------------
  DONCreerEntreeV(NULL,   "SenResponseEnable"      ,     1,   1, "Mod\\Sen");
  DONCreerEntreeV(NULL,   "SensorMode"             ,     0,   1, "Mod\\Sen");
  DONCreerEntreeV(NULL,   "SensorSensitivity"      ,     0,   2, "Mod\\Sen");
  DONCreerEntreeV(NULL,   "SensorIntrusionDetected",     0,   2, "Mod\\Sen");
  DONCreerEntreeV(NULL,   "SensorStatusOK"         ,     1,   2, "Mod\\Sen");



  //--------------------------------------------------------------------------
  // Data for "Rcar simulated data"
  //--------------------------------------------------------------------------
/ *
  DONCreerEntreeV(NULL,   "PartNumber",             0,  8, "Mod\\RCAR");
  DONCreerEntreeV(NULL,   "BenchNumber",            0,  8, "Mod\\RCAR");
  DONCreerEntreeB( NULL,  "OperatorName",           (tU8Bit*)"Pierre BARDET", 320,"Modele\\ImmoDiag");
  DONCreerEntreeB( NULL,  "TestPurpose",            (tU8Bit*)"Test avant essai ESD", 320,"Modele\\ImmoDiag");  
  DONCreerEntreeB( NULL,  "DefinitionLevel",        (tU8Bit*)"Proto B2", 320,"Modele\\ImmoDiag");
  DONCreerEntreeB(NULL,   "InputCurrent",           0,  8, "Mod\\RCAR");
  DONCreerEntreeV(NULL,   "CmdBattElec",            1,  1, "Mod\\RCAR");
  DONCreerEntreeV(NULL,   "CmdBattAux",             1,  1, "Mod\\RCAR");
  DONCreerEntreeV(NULL,   "InputCurrentFactor",     0,  8, "Mod\\RCAR");  

  DONCreerEntreeV(NULL,   "E_25_PLAF_AR"    ,       0,  1, "Mod\\RCAR");
  DONCreerEntreeV(NULL,   "E_80_PLAF_AR"    ,       0,  1, "Mod\\RCAR");
  DONCreerEntreeV(NULL,   "E_25_PLAF_AV"    ,       0,  1, "Mod\\RCAR");
  DONCreerEntreeV(NULL,   "E_80_PLAF_AV"    ,       0,  1, "Mod\\RCAR");
  
 //Bouchons
  DONCreerEntreeV(NULL,   "CanRecepOutput1Auto"   , 1,  1, "Mod\\RCAR");
  DONCreerEntreeV(NULL,   "FullRCar"              , 0,  1, "Mod\\RCAR");
  DONCreerEntreeV(NULL,   "BCMToolOperationOk"    , 1,  1, "Mod\\RCAR");
  DONCreerEntreeV(NULL,   "BCMToolInOperation"    , 0,  1, "Mod\\RCAR");
  DONCreerEntreeV(NULL,   "PcToToolCde"           , 0,  8, "Mod\\RCAR");
  DONCreerEvtEntree(NULL, "CanRecepPcToTool",       NULL,  "Mod\\RCAR");
  DONCreerEvtEntree(NULL, "CanEmisToolToPc",        NULL,  "Mod\\RCAR");
  DONCreerEntreeV(NULL,   "ToolToPcCde"           , 0,  8, "Mod\\RCAR");
  DONCreerEntreeB(NULL,   "PcToToolBuffer",         0,  8, "Mod\\RCAR");
  
  DONCreerEntreeV(NULL,   "CanBusOff",              0,  1, "Mod\\RCAR");
  DONCreerEntreeV(NULL,   "CanBusOpen",             0,  1, "Mod\\RCAR");

  DONCreerEvtEntree(NULL, "FinTestsCEM",         NULL, "Mod\\Cle" );
  
  DONCreerEntreeV(NULL,   "MonitoringRCar"    ,     0,  1, "Mod\\RCAR");* /

  

/ *
  DONCreerEntreeV(NULL,"TesterPWMPlafAv"       ,1,1, "Mod\\CEM");
  DONCreerEntreeV(NULL,"TesterPWMPlafAr"       ,1,1, "Mod\\CEM");
  DONCreerEntreeV(NULL,"TesterClignotant"      ,1,1, "Mod\\CEM");
  DONCreerEntreeV(NULL,"TesterEsav"            ,1,1, "Mod\\CEM");
  DONCreerEntreeV(NULL,"TesterEsar"            ,1,1, "Mod\\CEM");
  DONCreerEntreeV(NULL,"TesterCPE"             ,1,1, "Mod\\CEM");
  DONCreerEntreeV(NULL,"TesterLVI"             ,1,1, "Mod\\CEM");
  DONCreerEntreeV(NULL,"TesterPompesAV"        ,1,1, "Mod\\CEM");
  DONCreerEntreeV(NULL,"TesterPompesAR"        ,1,1, "Mod\\CEM");

  DONCreerEntreeV(NULL,"TempsCli"             ,2,8,   "Mod\\CEM");
  DONCreerEntreeV(NULL,"TempsCPE"             ,30,8,  "Mod\\CEM");
  DONCreerEntreeV(NULL,"TempsLVI"             ,30,8,  "Mod\\CEM");
  DONCreerEntreeV(NULL,"TempsPompes"          ,30,8,  "Mod\\CEM");* /
*/


}

/* [EXPORTED_FUNCTIONS_END] */






