//******************************************************************************
// Company:      Johnson Controls Inc.
// -----------------------------------------------------------------------------
// Copyright:    This software is JCI property.
//               Duplication or disclosure without JCI written authorization
//               is prohibited.
// -----------------------------------------------------------------------------
// Project:      X90_BCM
// Language:     ANSI-C
// -----------------------------------------------------------------------------
// Component:    DAT_DEA
// -----------------------------------------------------------------------------
// $Date:   Mar 10 2009 16:56:52  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_DEA/DAT_DEAP.H-arc  $
// $Revision:   1.1  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_DEA/DAT_DEAP.H-arc  $
// 
//    Rev 1.1   Mar 10 2009 16:56:52   adzhelp
// Cm003278: EEPROM size for direct access updated
// 
//    Rev 1.0   04 Feb 2008 17:02:18   adzhelp
// Initial revision.
//******************************************************************************

/*-------------------------------------------------------------------------
  Non-reentrance des inclusions
  -------------------------------------------------------------------------*/
#ifndef _dat_deap_H_
#define _dat_deap_H_

/*-------------------------------------------------------------------------
  Fichiers inclus

  #include <nom_du_ficher_systeme>
  #include "nom_du_ficher_utilisateur"
  -------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
  Constantes exportees

  #define cCOMNomConstante   ValeurDeLaConstante
  -------------------------------------------------------------------------*/
#define cDATDeaMaxByte			16	
// cDATDeaSizeEeprom must be defined in Byte
#define cDATDeaSizeEeprom		512


/*-------------------------------------------------------------------------
  Macro exportees

  #define mCOMNomMacro   (DefinitionDeLaMacro)
  -------------------------------------------------------------------------*/ 
/*-------------------------------------------------------------------------
  Types exportes

  struct sCOMNomStructure { ... };
  union  uCOMNomUnion { ... };
  enum   eCOMNomEnumeration { ... };
  typedef ...  tCOMNomType;
  -------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------
  Variables exportees

  extern  tType   COMNomVariable;
  extern  tType*  pCOMNomVariable; 
  -------------------------------------------------------------------------*/ 
/*-------------------------------------------------------------------------
  Donnees constantes exportees

  extern const tType  COMNomVariable;
  -------------------------------------------------------------------------*/ 
/*-------------------------------------------------------------------------
  Prototypes des fonctions exportees

  extern tTypeRetour COMNomFonction(tTypeArgument1 NomArgument1, ... );
  -------------------------------------------------------------------------*/ 
/*-------------------------------------------------------------------------
  Fin de la non-reentrance des inclusions
  -------------------------------------------------------------------------*/
#endif

