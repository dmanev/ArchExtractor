/*============================================================================
  Project ......................... Common
  Component ....................... ApiTimer
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

  - Role : Interface C/C++ pour la gestion du temps simulé
  
  -------------------------------------------------------------------------
  $Workfile:   APITIMER.CPP  $ file review : 
  $Log

	v1.0 :	GG		: 10/04/2000	: Creation

  ==========================================================================*/

/*--------------------------------------------------------------------------
  Body Identification
  --------------------------------------------------------------------------*/
#define ApiTimer "ApiTimer"


/*-------------------------------------------------------------------------
  Included files

  #include <system_file_name.h>
  #include "project_file_name.h"
  --------------------------------------------------------------------------*/

#include "Ldbpc.h"		// Definition of types and basis constants
#include "LDBPCTem.h"	// Define tcTempo Class Interface 
#include "LDBPCTim.h"	// Define tcTimer Class Interface 
#include "LDBPCRes.h"	// Definition of Resource Module Interface
#include "LDBPCErr.h"	// Definition of Error Module Interface

/*--------------------------------------------------------------------------
  Local constants

  #define cConstantName   ((tType) ConstantValue)
  --------------------------------------------------------------------------*/
#ifndef cNbTempoParam
	#define cNbTempoParam	100
#endif

/*--------------------------------------------------------------------------
  Local data

  static  tType   VariableName;
  static  tType*  pVariableName; 
  --------------------------------------------------------------------------*/
static tcTempoParam1<S32> TabTempoPar[cNbTempoParam];
static tTimerRef RefTempoPar = 0;

/*============================================================================
  =========================== EXPORTED FUNCTIONS =============================
  ==========================================================================*/

// ------------------------------------------------------------------------
// --------------------------- TOS / LDB API ------------------------------
// ------------------------------------------------------------------------


// ------------------------------------------------------------------------
// Return current simulatied time in nanoseconds
// ------------------------------------------------------------------------
U32 LDBTimPerfCntGetTime(void)
{
    return (U32)Timer.m_Date;
}

// ------------------------------------------------------------------------
// Start a temporization for a duration
// ------------------------------------------------------------------------
void LDBStartTimer(tTimerRef refTempo, tpFunct callback, tDelay dureeEnTick
					  , BOOL estPeriodique)
{
  // PON URD42 DEV 430 / PON URD45 BODY_SW 211
  // The LBBInit() function must be called before anyone function of the LDB LAYER
  assert(LdbpcIsInitialised == cTrue); 

	Timer.AjouterTempoDAT(refTempo, callback,dureeEnTick * cLDBTick, estPeriodique);
}

// ------------------------------------------------------------------------
// Stop a temporization
// ------------------------------------------------------------------------
tDelay LDBStopTimer(tTimerRef refTempo)
{
  // PON URD42 DEV 430 / PON URD45 BODY_SW 211
  // The LBBInit() function must be called before anyone function of the LDB LAYER
  assert(LdbpcIsInitialised == cTrue); 

	return(Timer.SupprimerTempoDAT(refTempo)/cLDBTick);
}

// ------------------------------------------------------------------------
// Read the date temporization
// ------------------------------------------------------------------------
tDelay LDBLireTempo(tTimerRef refTempo)
{
  // PON URD42 DEV 430 / PON URD45 BODY_SW 211
  // The LBBInit() function must be called before anyone function of the LDB LAYER
  assert(LdbpcIsInitialised == cTrue); 

	return(Timer.LireTempoDAT(refTempo)/cLDBTick);
}

// ------------------------------------------------------------------------
// Simulate the process time
// ------------------------------------------------------------------------
void LDBSimulerTempsTraitement(tDelay TempsEnTick)
{
  // PON URD42 DEV 430 / PON URD45 BODY_SW 211
  // The LBBInit() function must be called before anyone function of the LDB LAYER
  assert(LdbpcIsInitialised == cTrue); 

	if(TempsEnTick == 0)
	{
		mLDBPCErreur("Call the function SimulerTempsTraitement(TimeInTick)\n"
			"TimeInTick must be different of zero !");
	}
	else
	{
		Timer.TraiterTempo(TempsEnTick * cLDBTick);
	}
}

// ------------------------------------------------------------------------
// Wait a LDB Callback
// ------------------------------------------------------------------------
void LDBWaitForCallBack( void ) 
{
  // PON URD42 DEV 430 / PON URD45 BODY_SW 211
  // The LBBInit() function must be called before anyone function of the LDB LAYER
  assert(LdbpcIsInitialised == cTrue); 

	Timer.TraiterProchaineTempo();
}

// ------------------------------------------------------------------------
// Set the watch dog
// ------------------------------------------------------------------------
void LDBRefreshWatchDog(void) 
{
  // PON URD42 DEV 430 / PON URD45 BODY_SW 211
  // The LBBInit() function must be called before anyone function of the LDB LAYER
  assert(LdbpcIsInitialised == cTrue); 

}

// ------------------------------------------------------------------------
// Start the sleep mode
// ------------------------------------------------------------------------
void LDBEnterSleepMode(void) 
{
  // PON URD42 DEV 430 / PON URD45 BODY_SW 211
  // The LBBInit() function must be called before anyone function of the LDB LAYER
  assert(LdbpcIsInitialised == cTrue); 

	Ressources.EntrerVeille();
}

// ------------------------------------------------------------------------
// Stop the sleep mode
// ------------------------------------------------------------------------
void LDBLeaveSleepMode(void)
{
  // PON URD42 DEV 430 / PON URD45 BODY_SW 211
  // The LBBInit() function must be called before anyone function of the LDB LAYER
  assert(LdbpcIsInitialised == cTrue); 

	Ressources.SortirVeille();
}

// ------------------------------------------------------------------------
// Reset the LDB
// ------------------------------------------------------------------------
void LDBReset(void) 
{
  // PON URD42 DEV 430 / PON URD45 BODY_SW 211
  // The LBBInit() function must be called before anyone function of the LDB LAYER
  assert(LdbpcIsInitialised == cTrue); 

	Timer.TraiterReset();
}

// ------------------------------------------------------------------------
// Interrupt managment
// ------------------------------------------------------------------------
void LDBSuspendreInterruptions(void)
{ 
  // PON URD42 DEV 430 / PON URD45 BODY_SW 211
  // The LBBInit() function must be called before anyone function of the LDB LAYER
  assert(LdbpcIsInitialised == cTrue); 

}
void LDBRestaurerInterruptions(void)
{ 
  // PON URD42 DEV 430 / PON URD45 BODY_SW 211
  // The LBBInit() function must be called before anyone function of the LDB LAYER
  assert(LdbpcIsInitialised == cTrue); 

}
void LDBDemasquerInterruptions(void)
{ 
  // PON URD42 DEV 430 / PON URD45 BODY_SW 211
  // The LBBInit() function must be called before anyone function of the LDB LAYER
  assert(LdbpcIsInitialised == cTrue); 

}
void LDBMasquerInterruptions(void)
{ 
  // PON URD42 DEV 430 / PON URD45 BODY_SW 211
  // The LBBInit() function must be called before anyone function of the LDB LAYER
  assert(LdbpcIsInitialised == cTrue); 

}

// ------------------------------------------------------------------------
// Process before interrupt
// ------------------------------------------------------------------------
void EnterISR(void)
{ 
  // PON URD42 DEV 430 / PON URD45 BODY_SW 211
  // The LBBInit() function must be called before anyone function of the LDB LAYER
  assert(LdbpcIsInitialised == cTrue); 

}

// ------------------------------------------------------------------------
// Process after interrupt
// ------------------------------------------------------------------------
void LeaveISR(void)
{ 
  // PON URD42 DEV 430 / PON URD45 BODY_SW 211
  // The LBBInit() function must be called before anyone function of the LDB LAYER
  assert(LdbpcIsInitialised == cTrue); 

}

// ------------------------------------------------------------------------
// ----------------------------- API TIMER --------------------------------
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// Read the Current Date
// ------------------------------------------------------------------------
BOOL LDBPCLireDate(tDelay * date)
{
//	return(Timer.LireDate(date));
	if(date)
	{
		*date = Timer.m_Date;
		return cTrue;
	}
	else
	{
		return cFalse;
	}
}

// ------------------------------------------------------------------------
// Initialize and start the LDBPC
// ------------------------------------------------------------------------
BOOL LDBPCInitialiser()
{
	return(Timer.Initialiser());
}

// ------------------------------------------------------------------------
// Execute the LDBPC for a duration
// ------------------------------------------------------------------------
BOOL LDBPCExecuter(tDelay duree)
{
	return(Timer.Executer(duree));
}


//--------------------------------------------------------------------------
//--------------------- Configuration Interface  ---------------------------
//--------------------------------------------------------------------------

// ------------------------------------------------------------------------
// Stop a LDBPC temporization 
// ------------------------------------------------------------------------
BOOL LDBPCStopTimer(tTimerRef refTempo, tDelay * duree )
{
	tDelay Duree = Timer.SupprimerTempo(&TabTempoPar[refTempo]);

	if(duree)
		*duree = Duree / cLDBTick;

	return(Duree != 0);
}

// ------------------------------------------------------------------------
// Star a LDBPC temporization 
// ------------------------------------------------------------------------
BOOL LDBPCStartTimer(tTimerRef refTempo, tDelay dureeEnTick, tpFunct1 callback)
{
	TabTempoPar[refTempo].Duree = dureeEnTick * cLDBTick;
	TabTempoPar[refTempo].pCallBack  = callback;
	Timer.AjouterTempo(&TabTempoPar[refTempo]);
	return(cTrue);
}

// ------------------------------------------------------------------------
// Create a LDBPC temporization 
// ------------------------------------------------------------------------
BOOL LDBPCCreerTempo(tTimerRef * refTempo)
{
	if(cNbTempoParam <= RefTempoPar)
	{
		// Redefinir cNbTempoParam à une valeur supérieur
		mLDBPCErreur(cLdbpcErr);
		return(cFalse);
	}
	else
	{
		if(refTempo)
		{
			*refTempo = RefTempoPar;
			TabTempoPar[RefTempoPar].Param = RefTempoPar;
			RefTempoPar++;
			return(cTrue);
		}
		else
		{
			return(cFalse);
		}
	}
}

