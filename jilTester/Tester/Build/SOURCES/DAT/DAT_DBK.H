/*=========================================================================
  Function ........................ DAT
  Component ....................... DAT_DBK
  PVCS File revision............... $
  Last modification date .......... $Modtime:   Sep 24 2009 14:01:10  $
  ------------------------------------------------------------------------- 
  Copyright ...... This software is JCI property. Duplication or 
  disclosure is prohibited without the JCI writen authorization
  ------------------------------------------------------------------------- 
    
  - The macros, constatnts et types wich are not exported are defined in 
  this file
  - The variables and functions which are not exported are defined in this 
  file wich the static key word
  
  -------------------------------------------------------------------------
  Document reference : see the DAT_DBK.h file

  
  Component presentation : see the DAT_DBK.h file
  -------------------------------------------------------------------------
  Comments on the component (algorithm, structure, limitations, ...)

  -------------------------------------------------------------------------
  DAT_DBK.c file review : 
	
  $

  =========================================================================*/


/*-------------------------------------------------------------------------
  Includes non re entry
  -------------------------------------------------------------------------*/
#ifdef I_DAT_DBK
#else
#define I_DAT_DBK (1)

/*-------------------------------------------------------------------------
Included files

  #include <nom_du_ficher_systeme>
  #include "nom_du_ficher_utilisateur"
-------------------------------------------------------------------------*/
#include "deftypes.h"
#include "Dat_Dbkp.h"       // paramétrage
#include "Dat_Eep.h"

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


// Structure qui définit les adresses utilisées par les DBK
// Alloué en ROM
typedef struct
{
    U16 *AddBlockRam;
    tDATEepOffset SizeBlockRam;
} tDATDbkTableBankRom;

typedef enum
{
    cDATDbkErrorReadingBK1,
    cDATDbkErrorReadingBK2,
    cDATDbkErrorWritingBK1,
    cDATDbkErrorWritingBK2
} tDATDbkErrorHandle;

/*-------------------------------------------------------------------------
Exported data

extern  tType   COMNomVariable;
extern  tType*  pCOMNomVariable;
-------------------------------------------------------------------------*/
// Structure en RAM qui permet d'accéder à l'image RAM de la DBK
extern tDATDbkMirrors DATDbkMirrors;

/*-------------------------------------------------------------------------
Constant exported data

extern const tType  COMNomVariable;
-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
Exported funcions prototype

extern tTypeRetour COMNomFonction(tTypeArgument1 NomArgument1, ... );
-------------------------------------------------------------------------*/

// init function
extern void DATDbkInit (void);

// fonction de mise à jour de l'eeprom depuis le contenu RAM
// RAM to EEPROM update functions
extern void DATDbkStartUpdate ( tDATDbkDoubleBankHandle HandleDbk );
extern BOOL DATDbkIsWriteOk( tDATDbkDoubleBankHandle DoubleBankHandle );

// fonction de mise à jour de la RAM depuis le contenu de l'eeprom
// EEPROM to RAM reading functions
extern void DATDbkStartReadingAllBanks ( void );
extern void DATDbkStartReading ( tDATDbkDoubleBankHandle HandleDbk );

// Restoration
extern void DATDbkStartRestoringBrokenBanks( void );

// common functions
extern BOOL DATDbkIsBankProcessing( tDATDbkDoubleBankHandle HandleDbk );
extern BOOL DATDbkIsProcessing ( void );


// Callback functions
extern MEM_TYPE void DATPeeRebuildDoubleBank( tDATDbkDoubleBankHandle DoubleBankHandle );
extern MEM_TYPE void DATPeeErrorIndication( tDATDbkDoubleBankHandle DoubleBankHandle, tDATDbkErrorHandle ErrorHandle );


/*-------------------------------------------------------------------------
End of includes non re entry
-------------------------------------------------------------------------*/
#endif   /* fin de l'inclusion conditionnelle de DAT_DBK.h */

