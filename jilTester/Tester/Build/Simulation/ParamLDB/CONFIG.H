/*============================================================================
  Project ......................... LDBPC
  Component ....................... Config
  File revision.................... :   1.1  $
  Last modification date .......... $Modtime:   04 Feb 2009 16:32:34  $
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
  config.h file review :
  


  ==========================================================================*/
#ifndef I_CONFIG_H_
#define I_CONFIG_H_

//************************************************************************//
// Ce fichier permet de d�finir tout les composants n�c�ssaires
// Il suffit de mettre en commentaire tout les param�tres non d�sir�s
//************************************************************************//

// ---------------------------------
// IHM
// ---------------------------------

// Module OPEN GL
//#define IHM_OPENGL

// ---------------------------------
// LDBPC
// ---------------------------------

// D�marrage de l'OS
#define mTOSStart()    TOSInternalStart();

extern "C" void TOSInternalStart(void);
//extern "C" void TOSStart(int mode);
//extern "C" void TOSStart(void);

// D�finition des couche CAN
#define CANAL_CAN

// Optimisation du LDBPC ( D�conseill�s pour les trames bidirectionnelles )
#define OPTIMISATION_LDBPC_TRAME

// Comparaison d'images OpenGL - Bitmap
//#define LDBPC_IMAGE_COMPARE

#endif // I_CONFIG_H_
