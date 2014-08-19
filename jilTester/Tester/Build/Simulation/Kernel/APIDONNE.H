/*============================================================================
  Project ......................... LDBPC
  Component ....................... API_DATA
  File revision.................... :   1.0  $
  Last modification date .......... $Modtime:   04 Feb 2009 16:32:28  $
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
  ApiDonnee.h file review : 

  ==========================================================================*/
#ifdef I_API_DATA
#else
#define I_API_DATA (1)

#include "LdbpcCom.h"

#if defined(__cplusplus)
#define extern extern "C"
#endif

// --------------------------------------------------------------
//     Module DONNEES
// --------------------------------------------------------------

// Création d'une sortie < 32 bits
extern BOOL DONCreerSortieV(S32 * pRef, char * pNom, U32 ValeurInit, U32 TailleBit, char * pGroupe) ;

// Création d'une sortie > 32 bits
extern BOOL DONCreerSortieB(S32* pRef, char * pNom, U8 * pBufferInit, U32 TailleBit, char * pGroupe) ;

// Création d'une entree < 32 bits
extern BOOL DONCreerEntreeV(S32* pRef, char * pNom, U32 ValeurInit, U32 TailleBit, char * pGroupe) ;

// Création d'une entree > 32 bits
extern BOOL DONCreerEntreeB(S32* pRef, char * pNom, U8 * pBufferInit, U32 TailleBit, char * pGroupe) ;

// Création d'une entree/sortie < 32 bits
extern BOOL DONCreerEntreeSortieV(S32* pRef, char * pNom,U32 TailleBit, U32 ValeurInit, char * pGroupe) ;

// Création d'une entree/sortie > 32 bits
extern BOOL DONCreerEntreeSortieB(S32* pRef, char * pNom, U8 * pBufferInit, U32 TailleBit, char * pGroupe) ;

// Création d'un evenement en entree
extern BOOL DONCreerEvtEntree(S32 * pRef, char * pNom, tpFunct1 pCallBackEvt
                                      , char * pGroupe);

// Création d'un evenement pour toutes les entrees
extern BOOL DONCreerEvtEntrees(tpFunct1 pCallBackEvt) ;

// Création d'un evenement en sortie
extern BOOL DONCreerEvtSortie(S32 * pRef, char * pNom, char * pGroupe);

// Emettre d'un evenement en sortie
extern BOOL DONSignalerEvtSortie(S32 Ref) ;

// Lire une entree/sortie < 32bits
extern BOOL DONLireV(S32 Ref, U32 * pValeur, U32 * pTaille, tDelay * pDate) ;

// Lire une entree/sortie > 32bits
extern BOOL DONLireB(S32 Ref, U8 * pBuffer, U32 * pTaille, tDelay * pDate) ;

// Ecrire une sortie < 32bits
extern BOOL DONEcrireSortieV(S32 Ref, U32 Valeur);

// Ecrire une sortie > 32bits
extern BOOL DONEcrireSortieB(S32 Ref,U8 * pBuffer) ;

#if defined(__cplusplus)
#undef extern 
#endif

#endif //I_API_DATA
