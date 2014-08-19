/*---------------------------------------------------------------------------

                This software is JCI property
                -----------------------------

    Duplication or disclosure is prohibited without JCI
    written permission.
    This file has been automatically generated with an excel file,
    by a visual basic macro.

 File                        : DAT_DBKx.h
 Project                     : STK
 Fonction                    : EEP
 Author                      : Petar Dzhelekarski
 Automatically generated on  : 20.9.2010 ã. a 14:34:03 
 Source file                 : DAT_EEPM.XLA
 Macro version               : 01.29
 Configuration version       : 02.05

---------------------------------------------------------------------------*/

#ifndef I_DAT_DBKx_PARAM_H
#define I_DAT_DBKx_PARAM_H (1)


//--------------------------------------------------------------------------
//----  Declaration des constantes exportees par ce composant --------------
//--------------------------------------------------------------------------

// Definit le nombre de copies de ce type de banque
// Define the number of bank copy for this bank type
#define cDATDbkNumberOfBankCopy    2

// Definit le numero de chaque banque utilisee
// Define the number of each bank
#define cDATDbkHandleDiagBank    (tDATDbkDoubleBankHandle)0UL
#define cDATDbkHandleGeneralParameterBank    (tDATDbkDoubleBankHandle)1UL
#define cDATDbkHandleFactoryConfigBank    (tDATDbkDoubleBankHandle)2UL
#define cDATDbkHandleStaticImmoBank    (tDATDbkDoubleBankHandle)3UL
#define cDATDbkHandleDynamicImmoDataBank    (tDATDbkDoubleBankHandle)4UL

// Definit la taille de chaque banque
//  (taille en mot de 2 octets en RAM sans le checksum)
// Define size of each bank
//  (size in word of 2 byte in RAM without checksum)
#define cDATDbkSizeDiagBank    12U
#define cDATDbkSizeGeneralParameterBank    3U
#define cDATDbkSizeFactoryConfigBank    19U
#define cDATDbkSizeStaticImmoBank    38U
#define cDATDbkSizeDynamicImmoDataBank    33U

// Definit la taille de la RAM de travail
//  qui doit être la taille de la plus grande bank + 1 pour le checksum
//  cette déclaration doit être cohérente avec
//  cDATEepBufferSize dans DAT_EEPp.h
// Define max size of working RAM
//  which is size of the largest double bank (in RAM)
//  must be coherent with
//  cDATEepBufferSize dans DAT_EEPp.h
#define cDATDbkSizeMaxDbk  39

// Definit le nombre de groupes utilises
// Define number of group used
#define cNbDbk 5

// défini le handle de process de la premiere banque
// (+1 pour les banques suivantes)
#define cDATDbkFirstProcessHandle 5

// défini le nombre d'enregistrements pour chaque banque (toujours >= 1 !!!)
// define the number of records for each bank (always >= 1 !!!)

//--------------------------------------------------------------------------
//----  Declaration des macros exportees par ce composant ------------------
//--------------------------------------------------------------------------
// Macro de remplissage des banques ROM
// Macro wich fills ROM banks
#define mDATDbkInitTableBankROM() \
  {DATDbkMirrors.DiagBank, (tDATEepOffset)cDATDbkSizeDiagBank }, \
  {DATDbkMirrors.GeneralParameterBank, (tDATEepOffset)cDATDbkSizeGeneralParameterBank }, \
  {DATDbkMirrors.FactoryConfigBank, (tDATEepOffset)cDATDbkSizeFactoryConfigBank }, \
  {DATDbkMirrors.StaticImmoBank, (tDATEepOffset)cDATDbkSizeStaticImmoBank }, \
  {DATDbkMirrors.DynamicImmoDataBank, (tDATEepOffset)cDATDbkSizeDynamicImmoDataBank }

//--------------------------------------------------------------------------
//----  Declaration des structures exportees par ce composant --------------
//--------------------------------------------------------------------------

// Structure qui definit les images en RAM
// Struct define RAM mirrors
typedef struct
{
  U16 DiagBank[cDATDbkSizeDiagBank];
  U16 GeneralParameterBank[cDATDbkSizeGeneralParameterBank];
  U16 FactoryConfigBank[cDATDbkSizeFactoryConfigBank];
  U16 StaticImmoBank[cDATDbkSizeStaticImmoBank];
  U16 DynamicImmoDataBank[cDATDbkSizeDynamicImmoDataBank];
} tDATDbkMirrors;

#endif
