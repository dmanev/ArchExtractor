/*============================================================================
  Project ......................... PROJECT
  Component ....................... DAT_SBKp
  File revision.................... $
  Last modification date .......... $Modtime:   04 Feb 2009 16:32:20  $
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
  DAT_SBKp.h file review :
  
  $

  ==========================================================================*/

/*-------------------------------------------------------------------------
  Includes non re entry
  -------------------------------------------------------------------------*/
#ifndef _DAT_SBKp_H_
#define _DAT_SBKp_H_

/*-------------------------------------------------------------------------
Included files

  #include <nom_du_ficher_systeme>
  #include "nom_du_ficher_utilisateur"
-------------------------------------------------------------------------*/
#include "deftypes.h"
#include "DAT_SBKx.h"

/*-------------------------------------------------------------------------
Constant data

  #define cCOMNomConstante   ValeurDeLaConstante
-------------------------------------------------------------------------*/
// LES CONSTANTES DEFINIES CI DESSOUS DOIVENT ETRE MODIFIEES POUR
//     CHAQUE APPLICATION
// CONSTANT DATA DEFINED HEREAFTER MUST BE MODIFIED FOR EACH APPLICATION

/*  Definit le nombre d'essais de relecture
Il est important de parametrer une grande valeur parce que si une ecriture
intervient aprés un cas d'echec de lecture, la banque risque d'être
corrompue */

/*  Define number of reading retry
It's important to configure a high value because if a writing operation
is set after a failed reading case, the bank will be corrupted */
#define cSbk_NbRetryReadDatEepMax     100     

// défini le numéro de chaque banque utilisée
// define the number of each double bank
#define cDATSbkHandleNomBanque1    (tDATSbkSingleBankHandle)0UL
#define cDATSbkHandleNomBanque2    (tDATSbkSingleBankHandle)1UL
#define cDATSbkHandleNomBanque3    (tDATSbkSingleBankHandle)2UL
#define cDATSbkHandleNomBanque4    (tDATSbkSingleBankHandle)3UL
// défini la taille de chaque simples banques
// (taille en mot de 2 octets en RAM) c'est à dire sans le checksum 16bits
// define size of each single bank
// (size in word of 2 byte in RAM without 16bits checksum)
#define cDATSbkSizeEssaiSbk1  12U
#define cDATSbkSizeEssaiSbk2  4U
#define cDATSbkSizeEssaiSbk3  32U
#define cDATSbkSizeEssaiSbk4  24U

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

// si U8 -> jusqu'à 256 blocks
// cette déclaration doit être cohérente avec
// tDATEepProcessHandle dans DAT_EEPp.h
// must be coherent with
// tDATEepProcessHandle dans DAT_EEPp.h
typedef U8 tDATSbkSingleBankHandle;

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
