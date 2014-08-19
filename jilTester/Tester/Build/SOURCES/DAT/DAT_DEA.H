/*=========================================================================
  Fonction ........................ dat
  Composant ....................... dat_dea
  Revision PVCS du fichier ........ :   1.1  $
  Date de derniere modification ... $Modtime:   04 Feb 2009 16:32:22  $
  -------------------------------------------------------------------------
  Copyright ...... Ce logiciel est la propriete de JCI. Il ne peut etre
                   reproduit ni communique en totalite ou partie sans son
                   autorisation ecrite.
  -------------------------------------------------------------------------

  Ce fichier doit etre inclus dans les composants utilisant les macros,
  types et fonctions definis par le composant dat_dea.
  Le fichier dat_dea.h doit contenir toute et uniquement
  l'information necessaire au programmeur pour utiliser le composant
  dat_dea.
  En particulier c'est ce fichier dat_dea.h qui contient l'historique
  et la documentation du composant dans son ensemble.

  -------------------------------------------------------------------------
  Reference a la documentation:

   - DSL:
   - DCL:
   - EPT:

  -------------------------------------------------------------------------
  Presentation generale du composant:

  -------------------------------------------------------------------------
  Synoptique des fonctions et description des types et macros exportes:

  -------------------------------------------------------------------------
  Historique PVCS du fichier dat_dea.c:
  
  :   //45s3/standard/Composants standards/pvcs/archives/Sources/DAT/EEP/DAT_DEA/Dat_dea.h-arc  $
 * 
 *    Rev 1.1   Feb 21 2002 15:32:22   lelabous
 * Suppression des commentaires au niveau de l'entête des fichiers
 * 
 *    Rev 1.0   Feb 11 2002 09:57:44   barbaux
 * Initial revision.
 * 

  =========================================================================*/

/*-------------------------------------------------------------------------
  Non-reentrance des inclusions
  -------------------------------------------------------------------------*/
#ifndef _dat_dea_H_
#define _dat_dea_H_

/*-------------------------------------------------------------------------
  Fichiers inclus

  #include <nom_du_ficher_systeme>
  #include "nom_du_ficher_utilisateur"
  -------------------------------------------------------------------------*/
#include "dat_eep.h"
#include "dat_deap.h"

/*-------------------------------------------------------------------------
  Constantes exportees

  #define cCOMNomConstante   ValeurDeLaConstante
  -------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------
  Macro exportees

  #define mCOMNomMacro   (DefinitionDeLaMacro)
  -------------------------------------------------------------------------*/ 

// This macro check that the number of byte is inferior to the max size of work buffer
#define mDATWriteU8BitDATDeaSizeBufferInByteDefault(ValueToWrite) \
    {                                                             \
        mLIBassert ((ValueToWrite)<=cDATDeaMaxByte);              \
	    DATDeaSizeBufferInByte=(ValueToWrite);                    \
    }

#define mDATWriteU16BitDATDeaAddressInByteDefault(ValueToWrite) \
			(DATDeaAddressInByte=ValueToWrite)

#define mDATReadU8BitDATDeaWriteIsOkDefault() \
			(DATDeaWriteIsOk)

#define mDATReadU8BitDATDeaActionIsFinishedDefault() \
			(DATDeaActionIsFinished)

#define mDATControlDATDea(Treatment) \
			DATDea##Treatment ()

#define mDATReadBufferDATDeaBufferU8BitDefault(Index) \
			(DATDeaBufferU8Bit[Index])

#define mDATWriteBufferDATDeaBufferU8BitDefault(Index, ValueToWrite  ) \
			(DATDeaBufferU8Bit[Index]=ValueToWrite)

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
extern U8	  DATDeaBufferU8Bit[cDATDeaMaxByte];
extern U16  DATDeaAddressInByte;
extern U8		DATDeaSizeBufferInByte;
extern BOOL DATDeaWriteIsOk;
extern BOOL DATDeaActionIsFinished;
/*-------------------------------------------------------------------------
  Donnees constantes exportees

  extern const tType  COMNomVariable;
  -------------------------------------------------------------------------*/ 

/*-------------------------------------------------------------------------
  Prototypes des fonctions exportees

  extern tTypeRetour COMNomFonction(tTypeArgument1 NomArgument1, ... );
  -------------------------------------------------------------------------*/ 

extern void DATDeaStartWriteEepromByAddress(void);
extern void DATDeaStartReadEepromByAddress (void);
extern void DATDeaInitialize (void);

/*-------------------------------------------------------------------------
  Fin de la non-reentrance des inclusions
  -------------------------------------------------------------------------*/
#endif

