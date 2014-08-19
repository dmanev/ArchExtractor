/*============================================================================
  Project ......................... Common
  Component ....................... ApiDonne
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
		   
  - Role : C/C++ interface for data management
  
  -------------------------------------------------------------------------
  $Workfile:   APIDONNE.CPP  $ file review : 
  $Log

	v1.0 :	GG : 14/04/2000	: Creation
	v1.2 :	GG : 13/03/2002	: Update the interface

  ==========================================================================*/

/*--------------------------------------------------------------------------
  Body Identification
  --------------------------------------------------------------------------*/
#define ApiDonne "ApiDonne"

/*-------------------------------------------------------------------------
  Included files

  #include <system_file_name.h>
  #include "project_file_name.h"
  --------------------------------------------------------------------------*/

#include "Ldbpc.h"			// Definition of types and basis constants
#include "LDBPCDon.h"		// Definition of DLL Data Module Interface
#include "ApiDonne.h"		// Definition of Application Data Module Interface

/*============================================================================
  =========================== EXPORTED FUNCTIONS =============================
  ==========================================================================*/

// ------------------------------------------------------------------------
// Creation of an output < 32 bits
// ------------------------------------------------------------------------
BOOL DONCreerSortieV(S32 * pRef, char * pNom, U32 ValeurInit
						 , U32 TailleBit, char * pGroupe)
{
	return(Donnees.CreerDonnee(pRef,pNom,cDLLSortie,cDLLTypeVal,TailleBit
		,(S32)ValeurInit,pGroupe));
}

// ------------------------------------------------------------------------
// Creation of an output > 32 bits (Table)
// ------------------------------------------------------------------------
BOOL DONCreerSortieB(S32 * pRef, char * pNom, U8 * pBufferInit
						 , U32 TailleBit, char * pGroupe)
{
	return(Donnees.CreerDonnee(pRef,pNom,cDLLSortie,cDLLTypeTab,TailleBit
		,(U8 *)pBufferInit,pGroupe));
}

// ------------------------------------------------------------------------
// Creation of an input < 32 bits
// ------------------------------------------------------------------------
BOOL DONCreerEntreeV(S32 * pRef, char * pNom, U32 ValeurInit
						, U32 TailleBit, char * pGroupe)
{
	return(Donnees.CreerDonnee(pRef,pNom,cDLLEntree,cDLLTypeVal,TailleBit
		,(S32)ValeurInit,pGroupe));
}

// ------------------------------------------------------------------------
// Creation of an input > 32 bits (Table)
// ------------------------------------------------------------------------
BOOL DONCreerEntreeB(S32 * pRef, char * pNom, U8 * pBufferInit
						, U32 TailleBit, char * pGroupe)
{
	return(Donnees.CreerDonnee(pRef,pNom,cDLLEntree,cDLLTypeTab,TailleBit
	   ,(U8 *)pBufferInit,pGroupe));
}

// ------------------------------------------------------------------------
// Creation of an input/output < 32 bits 
// ------------------------------------------------------------------------
BOOL DONCreerEntreeSortieV(S32 * pRef, char * pNom,U32 ValeurInit
							   , U32 TailleBit, char * pGroupe)
{
return(Donnees.CreerDonnee(pRef,pNom,cDLLEntreeSortie,cDLLTypeVal
	   ,TailleBit,(S32)ValeurInit,pGroupe));
}

// ------------------------------------------------------------------------
// Creation of an input/output > 32 bits (Table)
// ------------------------------------------------------------------------
BOOL DONCreerEntreeSortieB(S32 * pRef, char * pNom, U8 * pBufferInit
							   , U32 TailleBit, char * pGroupe)
{
return(Donnees.CreerDonnee(pRef,pNom,cDLLEntreeSortie,cDLLTypeTab,TailleBit
	   ,(U8 *)pBufferInit,pGroupe));
}

// ------------------------------------------------------------------------
// Creation of an input event
// ------------------------------------------------------------------------
BOOL DONCreerEvtEntree(S32 * pRef, char * pNom, tpFunct1 pCallBackEvt
						   , char * pGroupe)
{
	return(Donnees.CreerDonnee(pRef,pNom,cDLLEntree,cDLLTypeEvt,0,(U32)0
		,pGroupe,&CallBackRef,(tpParam)pCallBackEvt));
}
// ------------------------------------------------------------------------
// Creation of an output event
// ------------------------------------------------------------------------
BOOL DONCreerEvtSortie(S32 * pRef, char * pNom, char * pGroupe)
{
	return(Donnees.CreerDonnee(pRef,pNom,cDLLSortie,cDLLTypeEvt,0,(U32)0,pGroupe));
}

// ------------------------------------------------------------------------
// Creation of an event for all inputs
// ------------------------------------------------------------------------
BOOL DONCreerEvtEntrees(tpFunct1 pCallBackEvt)
{
	return(Donnees.CreerEvtEntrees(pCallBackEvt));
}


// ------------------------------------------------------------------------
// Send an output event 
// ------------------------------------------------------------------------
BOOL DONSignalerEvtSortie(S32 Ref)
{
	return(Donnees.EmettreEvtSor(Ref));
}

// ------------------------------------------------------------------------
// Read an input < 32bits
// ------------------------------------------------------------------------
BOOL DONLireV(S32 Ref, U32 * pValeur, U32 * pTaille
						, tDelay * pDate)
{
	return(Donnees.Lire(Ref, pValeur, pTaille, pDate));
}

// ------------------------------------------------------------------------
// Read an input > 32bits (Table)
// ------------------------------------------------------------------------
BOOL DONLireB(S32 Ref, U8 * pBuffer, U32 * pTaille
						, tDelay * pDate)
{
	return(Donnees.Lire(Ref, pBuffer, pTaille, pDate));
}

// ------------------------------------------------------------------------
// Write an output < 32bits
// ------------------------------------------------------------------------
BOOL DONEcrireSortieV(S32 Ref, U32 Valeur)
{
	return(Donnees.EcrireSortie(Ref, Valeur));
}

// ------------------------------------------------------------------------
// Write an output > 32bits (Table)
// ------------------------------------------------------------------------
BOOL DONEcrireSortieB(S32 Ref,U8 * pBuffer)
{
	return(Donnees.EcrireSortie(Ref, pBuffer));
}

