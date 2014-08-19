/*---------------------------------------------------------------------------

                This software is JCI property
                -----------------------------

    Duplication or disclosure is prohibited without JCI
    written permission.
    This file has been automatically generated with an excel file,
    by a visual basic macro.

 File                        : DAT_EEPx.h
 Project                     : STK
 Fonction                    : EEP
 Author                      : Petar Dzhelekarski
 Automatically generated on  : 20.9.2010 ã. a 14:34:03 
 Source file                 : DAT_EEPM.XLA
 Macro version               : 01.29
 Configuration version       : 02.05

---------------------------------------------------------------------------*/

#ifndef I_DAT_EEPx_PARAM_H
#define I_DAT_EEPx_PARAM_H (1)


//--------------------------------------------------------------------------
//----  Declaration des constantes exportees par ce composant --------------
//--------------------------------------------------------------------------

// Definit le nombre de process
// Define number of process
#define cDATEepNumberOfProcess 11U

// Taille du buffer partage
// Size of shared buffer
#define cDATEepBufferSize  (U16)39

// Definit la structure de l'eeprom
// Define eeprom structure
//{Offset, Size, Call back number}
#define mDATEepDeclareBlocList()    \
  {    0,    6, cDATEepCallBackSbkNumber }, \
  {    6,   14, cDATEepCallBackSbkNumber }, \
  {   46,    2, cDATEepCallBackSbkNumber }, \
  {   96,   11, cDATEepCallBackSbkNumber }, \
  {  253,    2, cDATEepCallBackSbkNumber }, \
  {   20,   26, cDATEepCallBackDbkNumber }, \
  {   48,    8, cDATEepCallBackDbkNumber }, \
  {   56,   40, cDATEepCallBackDbkNumber }, \
  {  107,   78, cDATEepCallBackDbkNumber }, \
  {  185,   68, cDATEepCallBackDbkNumber }, \
  {    0,    0, cDATEepCallBackDeaNumber }

// Numeros des callback
// Callback numbers
#define cDATEepCallBackSbkNumber 0
#define cDATEepCallBackDbkNumber 1
#define cDATEepCallBackDeaNumber 2

// Nombre de callback
// Number of callback
#define cDATEepNumberOfCallBack   (U16)3

// Liste des callback
// Callback list
#define mDATEepDeclareCallBackList()\
    DATSbkCallBackEep,              \
    DATDbkCallBackEep,              \
    DATDeaCallBackEep,              \

#endif
