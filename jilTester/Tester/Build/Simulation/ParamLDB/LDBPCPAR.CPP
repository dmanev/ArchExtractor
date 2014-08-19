/*============================================================================
  Project ......................... PROJET
  Component ....................... LdbpcParam
  File revision.................... $Revision:   1.5  $
  Last modification date .......... $Modtime:   Jul 02 2009 18:15:52  $
  -------------------------------------------------------------------------
  Copyright ... This software is JCI property. Duplication or
                disclosure is prohibited without JCI written permission
  ------------------------------------------------------------------------- 

  - Macros, constants and types which are not exported are defined in 
    this file
  - Variables and functions which are not exported are defined in this 
    file with the static key word
  
  -------------------------------------------------------------------------
  Comments on the component (role, algorithm, structure, limitations,
           defined tasks and events...)
  - Role :
  
  -------------------------------------------------------------------------
  LdbpcPar.cpp file review : 

  ==========================================================================*/

/*--------------------------------------------------------------------------
  Body Identification
  --------------------------------------------------------------------------*/
#define Ldbpcpar "Ldbpcpar"

/*-------------------------------------------------------------------------
  Included files

  #include <system_file_name.h>
  #include "project_file_name.h"
  --------------------------------------------------------------------------*/
#include "Ldbpc.h"		// defini les types et constantes de bases
#include "Ldbpcpar.h"

/*--------------------------------------------------------------------------
  Local constants

  #define cConstantName   ((tType) ConstantValue)
  --------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------
  Local macro

  #define mMacroName   (MacroDefinition)
  --------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------
  Local type

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

/*--------------------------------------------------------------------------
  Exported function prototypes
  
  static tTypeRetour FunctionName(tTypeArgument1 ArgumentName1, ... );
  --------------------------------------------------------------------------*/

// LDB Channels
// TODO : Add the initialization exported functions of LDBPC Channels
//extern void xxxInit(void);

extern void RstInit(void);
extern void DinInit(void);
extern void PwmInit(void);
extern void KwpInit(void);
extern void LcdInit(void);
extern void MotInit(void);
extern void EepInit(void);
extern void DouInit(void);
extern void AnaInit(void);
extern void IntInit(void);
extern void LDBPCMotInit(void);
extern void DfaInit(void);
extern void ModInit(void);
extern void TrpInit(void);
extern void CanInit(void);

extern void BuzInit(void); // LDBPC_BUZ
extern void LDBPCBuzInit(void); // LDBPC ticks init
extern void AlaInit(void);
extern void RFInit(void);
extern void SpdInit(void);

// DAT Components
// TODO : Add the initialization exported functions of DAT component
//extern void DatpcxxxInit(void);


/*============================================================================
  =========================== LOCAL FUNCTIONS ================================
  ==========================================================================*/

/*============================================================================
  DESCRIPTION :
  
  PARAMETERS (Type,Name,Min,Max) :   none

  RETURN VALUE :   none
 
  DESIGN INFORMATION :   refer to Detailed Design Document
  ==========================================================================*/
//static type FunctionName(...)
//{
//}


/*============================================================================
  DESCRIPTION : General initialisation of the LDBPC.
  
  PARAMETERS (Type,Name,Min,Max) :   none

  RETURN VALUE :   none
 
  DESIGN INFORMATION :   refer to Detailed Design Document
  ==========================================================================*/
void LDBPC_Init_Param(void)
{
// Initialisation of the channel Xxx
//#ifdef cLDBCanalxxx
//	xxxInit();
//#endif

// Initialisation of the channel RST (Reset Management)
  RstInit();

// Initialisation of the channel ANA (Analog Input)
#ifdef cLDBChannelAna
   AnaInit();
#endif

// Initialisation of the channel DIN (Digital Input)
#ifdef cLDBChannelDin
   DinInit();
#endif

// Initialisation of the channel DOU (Digital Output)
#ifdef cLDBChannelDou
  DouInit();
#endif

// Initialisation of the channel EEP (EEPROM Management)
#ifdef cLDBChannelEep
  EepInit();
#endif
#ifdef cLDBChannelDfa
  DfaInit();
#endif

// Initialisation of the channel MOT (Stepper Motor)
#ifdef cLDBChannelMot
  MotInit();
#endif

// Initialisation of the channel CAN

#ifdef cLDBChannelCan
  CanInit();
#endif


#ifdef cLDBChannelLinM
  LinMInit();
#endif

#ifdef cLDBChannelLinS
  LinSInit();
#endif

// Initialisation of the channel Pwm
#ifdef cLDBChannelPwm
	PwmInit();
#endif

// Initialisation of the channel Kwp
#ifdef cLDBChannelKwp
	KwpInit();
#endif
// Initialisation of the channel Mod
#ifdef cLDBChannelMod
	ModInit();
#endif
// Initialisation of the channel Trp
#ifdef cLDBChannelTrp
	TrpInit();
#endif
    
// Initialisation of the channel Buz
#ifdef cLDBChannelBuz
  BuzInit();
#endif

  // Initialisation of the channel Ala
#ifdef cLDBChannelAla
  AlaInit();
#endif

  // Initialisation of the channel Rf
#ifdef cLDBChannelRf
  RFInit();
#endif

  // Initialisation of the channel Spd
#ifdef cLDBChannelSpd
  SpdInit();
#endif
#if 0 // !!! NOT INTEGRATED !!!

// Initialisation of the channel Lcd
#ifdef cLDBCanalLcd
	LcdInit();
#endif


// Initialisation of the channel Int
#ifdef cLDBCanalInt
  IntInit();
#endif

// Initialisation of the channel Loc (autotrain localisation)
#ifdef cLDBChannelLoc
  LocInit();
#endif

#endif
}

/*============================================================================
  DESCRIPTION : General initialisation of the DATPC.
  
  PARAMETERS (Type,Name,Min,Max) :   none

  RETURN VALUE :   none
 
  DESIGN INFORMATION :   refer to Detailed Design Document
  ==========================================================================*/
void DATPC_Init_Param(void)
{
// Initialisation du Composant DATPC xxx
//	InitDatpcxxx();

}


/*============================================================================
  DESCRIPTION : General initialisation of the LDBPC AND DATPC.
  
  PARAMETERS (Type,Name,Min,Max) :   none

  RETURN VALUE :   none
 
  DESIGN INFORMATION :   refer to Detailed Design Document
  ==========================================================================*/
void InitParametrage(void)
{
	LDBPC_Init_Param();
	DATPC_Init_Param();
}

/*============================================================================
  DESCRIPTION : LDBPCInit is called when the LDBInit is called.
  
  PARAMETERS (Type,Name,Min,Max) :   none

  RETURN VALUE :   none
 
  DESIGN INFORMATION :   refer to Detailed Design Document
  ==========================================================================*/
void LDBPCInit(void)
{
// Initialisation of the channel MOT (Stepper Motor)
#ifdef cLDBChannelMot
	LDBPCMotInit();
#endif

// Initialisation of the channel BUZ
#ifdef cLDBChannelBuz
	LDBPCBuzInit();
#endif
}

