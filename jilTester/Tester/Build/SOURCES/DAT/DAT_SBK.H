/*=========================================================================
  Function ........................ DAT
  Component ....................... DAT_SBK
  PVCS File revision............... :   1.0  $
  Last modification date .......... $Modtime:   Sep 24 2009 14:00:34  $
  ------------------------------------------------------------------------- 
  Copyright ...... This software is JCI property. Duplication or 
  disclosure is prohibited without the JCI writen authorization
  ------------------------------------------------------------------------- 
    
  - The macros, constatnts et types wich are not exported are defined in 
  this file
  - The variables and functions which are not exported are defined in this 
  file wich the static key word
  
  -------------------------------------------------------------------------
  Document reference : see the DAT_SBK.h file

  
  Component presentation : see the DAT_SBK.h file
  -------------------------------------------------------------------------
  Comments on the component (algorithm, structure, limitations, ...)

  -------------------------------------------------------------------------
  DAT_SBK.c file review : 
  
  :   P:/Logiciel/OW1003/archives/SOURCE/DAT/DAT_SBK/TestU/Dat_Sbk.H-arc  $
 * 
 *    Rev 1.0   Aug 30 2001 15:20:02   lentengn
 * Initial revision.
 * 
 *    Rev 1.0   Aug 20 2001 14:42:56   lentengn
 * Initial revision.

  =========================================================================*/


/*-------------------------------------------------------------------------
  Includes non re entry
  -------------------------------------------------------------------------*/
#ifdef I_DAT_SBK
#else
#define I_DAT_SBK (1)

/*-------------------------------------------------------------------------
Included files

  #include <nom_du_ficher_systeme>
  #include "nom_du_ficher_utilisateur"
-------------------------------------------------------------------------*/
#include "Dat_Eep.h"
#include "DAT_Sbkp.h"       // paramétrage

/*-------------------------------------------------------------------------
Constant data

  #define cCOMNomConstante   ValeurDeLaConstante
-------------------------------------------------------------------------*/

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


// Structure qui définit les adresses utilisées par les SBK
// Alloué en ROM
typedef struct
{
    U16*            AddBlockRam;
    tDATEepOffset       SizeBlockRam;
} tDATSbkTableBankRom;

typedef enum
{
    cDATSbkErrorReading,
    cDATSbkErrorWriting
} tDATSbkErrorHandle;

/*-------------------------------------------------------------------------
Exported data

extern  tType   COMNomVariable;
extern  tType*  pCOMNomVariable;
-------------------------------------------------------------------------*/
// Structure en RAM qui permet d'accéder à l'image RAM de la SBK
extern tDATSbkMirrors DATSbkMirrors;

/*-------------------------------------------------------------------------
Constant exported data

extern const tType  COMNomVariable;
-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
Exported funcions prototype

extern tTypeRetour COMNomFonction(tTypeArgument1 NomArgument1, ... );
-------------------------------------------------------------------------*/

// Init function
extern void     DATSbkInit (void);

// RAM to EEPROM update functions
extern void     DATSbkStartUpdate           ( tDATSbkSingleBankHandle HandleSbk );
extern BOOL DATSbkIsWriteOk             ( tDATSbkSingleBankHandle HandleSbk );

// EEPROM to RAM reading functions
extern void     DATSbkStartReadingAllBanks  ( void );
extern void     DATSbkStartReading          ( tDATSbkSingleBankHandle HandleSbk );

// common functions
extern BOOL DATSbkIsBankProcessing      ( tDATSbkSingleBankHandle HandleSbk );
extern BOOL DATSbkIsProcessing          ( void );

// Callback functions
extern MEM_TYPE void     DATPeeRebuildSingleBank         ( tDATSbkSingleBankHandle HandleSbk );
extern MEM_TYPE void     DATPeeSingleBankErrorIndication ( tDATSbkSingleBankHandle HandleSbk, tDATSbkErrorHandle SbkErrorHandle );

/*-------------------------------------------------------------------------
End of includes non re entry
-------------------------------------------------------------------------*/
#endif   /* fin de l'inclusion conditionnelle de DAT_SBK.h */
