/*============================================================================
  Project ......................... PROJECT
  Component ....................... DAT_DBKp
  File revision.................... $
  Last modification date .......... $Modtime:   04 Feb 2009 16:32:22  $
  -------------------------------------------------------------------------
  Copyright ... This software is JCI property. Duplication or
                disclosure is prohibited without JCI written permission
  ------------------------------------------------------------------------- 
    
  - This file should only contain data useful to the programmer to use
    this component
  - Component exported macros, constants and types are defined in this file
  - Component exported variables and functions are declared in this file 
    with the "extern" keyword
  
  -------------------------------------------------------------------------
  DAT_DBKp.h file review :
  
  $

  ==========================================================================*/

/*-------------------------------------------------------------------------
  Includes non re entry
  -------------------------------------------------------------------------*/
#ifndef _DAT_DBKp_H_
#define _DAT_DBKp_H_


/*-------------------------------------------------------------------------
Included files

  #include <nom_du_ficher_systeme>
  #include "nom_du_ficher_utilisateur"
-------------------------------------------------------------------------*/
#include "deftypes.h"
#include "DAT_DBKx.h"

/*-------------------------------------------------------------------------
Constant data

  #define cCOMNomConstante   ValeurDeLaConstante
-------------------------------------------------------------------------*/
// LES CONSTANTES DEFINIES CI DESSOUS DOIVENT ETRE MODIFIEES POUR
//     CHAQUE APPLICATION
// CONSTANT DATA DEFINED HEREAFTER MUST BE MODIFIED FOR EACH APPLICATION

/*  Definit le nombre d'essais de relecture
Il est important de parametrer une grande valeur parce que si une ecriture
intervient apr�s un cas d'echec de lecture, la banque risque d'�tre
corrompue */

/*  Define number of reading retry
It's important to configure a high value because if a writing operation
is set after a failed reading case, the bank will be corrupted */
#define cNbRetryReadDatEepMax		100
// d�fini le num�ro de chaque banque utilis�e
// define the number of each double bank
#define cDATDbkHandleNomBanque1		(tDATDbkDoubleBankHandle)0UL
#define cDATDbkHandleNomBanque2		(tDATDbkDoubleBankHandle)1UL
#define cDATDbkHandleNomBanque3		(tDATDbkDoubleBankHandle)2UL
#define cDATDbkHandleNomBanque4		(tDATDbkDoubleBankHandle)3UL
// d�fini la taille de chaque double banques
// (taille en mot de 2 octets en RAM) c'est � dire sans le checksum
// define size of each double bank
// (size in word of 2 byte in RAM without checksum)
#define cDATDbkSizeNomBanque1	12U
#define cDATDbkSizeNomBanque2	4U
#define cDATDbkSizeNomBanque3	32U
#define cDATDbkSizeNomBanque4	24U

/*-------------------------------------------------------------------------
Exported Macro

  #define mCOMNomMacro   (DefinitionDeLaMacro)
-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
Exported type

struct sCOMNomStructure { ... };
union  uCOMNomUnion { ... };
enum   eCOMNomEnumeration { ... };
typedef ...  tCOMNomType;
-------------------------------------------------------------------------*/

// si U8 -> jusqu'� 256 blocks
// cette d�claration doit �tre coh�rente avec
// tDATEepProcessHandle dans DAT_EEPp.h
// must be coherent with
// tDATEepProcessHandle dans DAT_EEPp.h
typedef U8 tDATDbkDoubleBankHandle;


/*-------------------------------------------------------------------------
  Exported data

  extern  tType   COMNomVariable;
  extern  tType*  pCOMNomVariable; 
  -------------------------------------------------------------------------*/ 

/*-------------------------------------------------------------------------
  Constant exported data

  extern const tType  COMNomVariable;
  -------------------------------------------------------------------------*/ 

/*-------------------------------------------------------------------------
  Exported funcions prototype

  extern tTypeRetour COMNomFonction(tTypeArgument1 NomArgument1, ... );
  -------------------------------------------------------------------------*/ 

/*-------------------------------------------------------------------------
  End of includes non re entry
  -------------------------------------------------------------------------*/
#endif
