/*=========================================================================
  Function ........................ DAT
  Component ....................... DAT_DBK
  PVCS File revision............... $
  Last modification date .......... $Modtime:   Apr 25 2009 21:07:00  $
  ------------------------------------------------------------------------- 
  Copyright ...... This software is JCI property. Duplication or 
  disclosure is prohibited without the JCI writen authorization
  ------------------------------------------------------------------------- 
  DAT_DBK component exported function definition 
  
  This file DAT_DBK.c is compile and a DAT_DBK.o is generated
  The object file includes the functions exported by the component.
  
  - The macros, constatnts et types wich are not exported are defined in 
  this file
  - The variables and functions which are not exported are defined in this 
  file wich the static key word
  
  -------------------------------------------------------------------------
  Document reference : see the DAT_DBK.h file
  ------------------------------------------------------------------------- 
  Component presentation : see the DAT_DBK.h file
  -------------------------------------------------------------------------
  Comments on the component (algorithm, structure, limitations, ...)

  -------------------------------------------------------------------------
  DAT_DBK.c file review : 
	
  $

  =========================================================================*/

/*-------------------------------------------------------------------------
  Body Identification
  -------------------------------------------------------------------------*/


#define Dat_Dbk    "Dat_Dbk"

/*-------------------------------------------------------------------------
  Included files

  #include <nom_du_ficher_systeme.h>
  #include "nom_du_ficher_utilisateur.h"
  -------------------------------------------------------------------------*/ 
#include "deftypes.h"
#include "lib.h"              /* defini les types et constantes de bases */
#include "Dat_Dbk.h"
#include "Dat_Eep.h"

// Modifs :
// DATDbkStartUpdate, DATDbkStartReading
// variable d'etat ecriture / lecture par Double banque


/*-------------------------------------------------------------------------
  Local constants

  #define cNomConstante   ValeurDeLaConstante
  -------------------------------------------------------------------------*/  
// attention le checksum doit etre en 0 sinon le prog doit etre modifie
#define cPosChecksum	0

#define cMskFlagStatusOk  (U8)0x01
#define cMskFlagWriteMode (U8)0x02

/*-------------------------------------------------------------------------
  Local macro

  #define mNomMacro   (DefinitionDeLaMacro)
  -------------------------------------------------------------------------*/  

#define mProcessHandleToDbkHandle(hProc)   ((tDATDbkDoubleBankHandle)(hProc-cDATDbkFirstProcessHandle))
#define mDbkHandleToProcessHandle(hDbk)   ((tDATEepProcessHandle)(hDbk+cDATDbkFirstProcessHandle))

#define mSetFlagStatusOk(hDbk)    { Flags[hDbk] |=  cMskFlagStatusOk; }
#define mClearFlagStatusOk(hDbk)  { Flags[hDbk] &= ~cMskFlagStatusOk; }
#define mReadFlagStatusOk(hDbk)   ((Flags[hDbk] &   cMskFlagStatusOk) != 0 )

#define mSetFlagWriteMode(hDbk)   { Flags[hDbk] |=  cMskFlagWriteMode; }
#define mClearFlagWriteMode(hDbk) { Flags[hDbk] &= ~cMskFlagWriteMode; }
#define mReadFlagWriteMode(hDbk)  ((Flags[hDbk] &   cMskFlagWriteMode)!= 0) 

/*-------------------------------------------------------------------------
  Local type

  struct  sNomStructure { ... };
  union   uNomUnion { ... };
  enum    eNomEnumeration { ... };
  typedef Expression tNomType;
  -------------------------------------------------------------------------*/

typedef enum
{
    cDbkNoError,
    cDbkErrorBk1,
    cDbkErrorBk2,
    cDbkErrorBKs
} tDbkError;

// definition des etats de sortie des graphes
typedef enum
{
    cGraphResultProcessing,
    cGraphResultOk,
    cGraphResultError
} tGraphResult;

// constantes du graph de la CallBack
typedef enum
{
    cGraphDbkWaitState,
    cGraphDbkReadState,
    cGraphDbkWriteState
} tGraphDbkStatus;

// constantes du graph d'ecriture double banque
typedef enum
{
    cGraphWriteDbkWaitState,
    cGraphWriteDbkBk1State,
    cGraphWriteDbkBk2State
} tGraphWriteDbkStatus;

// constantes du graph de lecture double banque
typedef enum
{
    cGraphReadDbkWaitState,
    cGraphReadDbkBk1State,
    cGraphReadDbkBk2State,
    cGraphReadDbkCheckState,
    cGraphReadDbkStrategyState
} tGraphReadDbkStatus;

// constantes du graph de lecture bloc
typedef enum
{
    cGraphReadWaitState,
    cGraphReadDatEepState,
    cGraphReadCheckDatEepState
} tGraphReadStatus;


/*-------------------------------------------------------------------------
  Local data

  static  tType   NomVariable;
  static  tType*  pNomVariable; 
  -------------------------------------------------------------------------*/
static tDbkError DbkError [cNbDbk];
static U8 Flags [cNbDbk];
static BOOL DbkCallBackStatusOk;
static tDATDbkDoubleBankHandle HandleDbkInUse;
static tDATEepOffset SizeDbkChkInUse;


static tGraphDbkStatus GraphDbkStatus;
static tGraphWriteDbkStatus GraphWriteDbkStatus;
static tGraphReadDbkStatus GraphReadDbkStatus;
static tGraphReadStatus GraphReadStatus;

/*-------------------------------------------------------------------------
  Constant local Data

  static const tType  NomVariable;
  -------------------------------------------------------------------------*/  
// Structure en ROM qui permet d'acceder aux adresses des DBK
const tDATDbkTableBankRom DATDbkTableBankRom [cNbDbk] =
    {
        mDATDbkInitTableBankROM()
    };



/*-------------------------------------------------------------------------
  Exported data

  tType   COMNomVariable;          (COM: 3 lettres identifiant ce composant)
  tType*  pCOMNomVariable;         (COM: 3 lettres identifiant ce composant)
  -------------------------------------------------------------------------*/ 

// variable definissant toutes les doubles banques en RAM
tDATDbkMirrors DATDbkMirrors;

/*-------------------------------------------------------------------------
  Constant exported data
 
  const tType   COMNomVariable;    (COM: 3 lettres identifiant ce composant)
  -------------------------------------------------------------------------*/ 

/*-------------------------------------------------------------------------
  Local functions prototype
  
	static tTypeRetour NomFonction(tTypeArgument1 NomArgument1, ... );
  -------------------------------------------------------------------------*/


tGraphResult WritingDbkGraph ( void );
tGraphResult ReadingDbkGraph ( void );
tGraphResult ReadingBlockGraph ( tDATEepOffset  OffsetEeprom );
U16 ChecksumCalculation ( tDATEepOffset BlockSize );

#ifdef X90_PROJECT
static MEM_TYPE void DATDbkCallBackEep_Static(tDATEepProcessHandle ProcessHandle, BOOL CallBackStatusOk);
static MEM_TYPE tGraphResult ReadingBlockGraph_Static(tDATEepOffset OffsetEeprom);
static MEM_TYPE tGraphResult ReadingDbkGraph_Static(void);
#endif


/*.........................................................................
  ........................... LOCAL FUNCTIONS..............................
  .........................................................................*/

/*=========================================================================
! Function .........
U16 ChecksumCalculation ( tDATEepOffset BlockSize )
!--------------------------------------------------------------------------
! Function purpose :
//-------------------------------------------------------------------
// 
//              FONCTION QUI CALCULE LE CHECKSUM
//          en utilisant ce qui se trouve en RAM de travail
// 
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// 
//              CHECKSUM CALCULATION using working RAM
// 
//-------------------------------------------------------------------
!
!--------------------------------------------------------------------------
! Precondition (parameters):
!
! Type            Name                           Min          Max
! -------------------------------------------------------------------------
! tDATEepOffset		BlockSize					0			cDATDbkSizeMaxDbk
!--------------------------------------------------------------------------
! Postcondition (return values):
!
! Type            Name                           Min          Max
! -------------------------------------------------------------------------
! 	U16 Checksum								0			0xFFFF
!--------------------------------------------------------------------------
! Function review:
!
! Author  Ver.  Description
! -------------------------------------------------------------------------
!         1.00  Initial version
!
!==========================================================================*/

U16 ChecksumCalculation ( tDATEepOffset BlockSize )
{
    U16 Checksum;

    // used in debug mode to check param
    // permet de faire en mode debug des verif des param
    // si la condition n'est pas bonne un message d'erreur est genere
    mLIBassert( BlockSize > 1 );

    Checksum = 0;
    BlockSize --;
    // boucle de calcul du checksum
    while ( BlockSize > 0 )
    {
        Checksum += DATEepBuffer [ BlockSize ];
        BlockSize --;
    }
    // inverse la valeur du checksum
    Checksum = ~Checksum;

    return Checksum;
}



/*--------------------------------------------------------------------------*/
/*-------  Fonctions des Boites de GRAPHES  (par ordre alphabetique) -------*/
/*--------------------------------------------------------------------------*/
/*
tTypeRetour ComNomFonction(tTypeArgument NomArgument,  ...)
{
}
*/


/*.........................................................................
  ........................... EXPORTED FUNCTIONS. .........................
  .........................................................................*/

/*=========================================================================
! Function .........
void DATDbkStartReadingAllBanks ( void )
!--------------------------------------------------------------------------
! Function purpose :
! Permet de mettre en RAM le contenu de toutes les doubles banques en EEPROM
! reading EEPROM to RAM for all double banks
!--------------------------------------------------------------------------
! Precondition (parameters):
!
! Type            Name                           Min          Max
! -------------------------------------------------------------------------
!
!--------------------------------------------------------------------------
! Postcondition (return values):
!
! Type            Name                           Min          Max
! -------------------------------------------------------------------------
! 
!--------------------------------------------------------------------------
! Function review:
!
!
!==========================================================================*/

void DATDbkStartReadingAllBanks ( void )
{
    tDATDbkDoubleBankHandle HandleDbk;

    for ( HandleDbk = 0 ; HandleDbk < cNbDbk ; HandleDbk ++ )
    {
        DATDbkStartReading ( HandleDbk );
    }
}


/*=========================================================================
! Function .........
void DATDbkStartReading ( tDATDbkDoubleBankHandle HandleDbk )
!--------------------------------------------------------------------------
! Function purpose :
! Permet de mettre en RAM le contenu d'une double banque en EEPROM
! reading EEPROM to RAM for one double bank
!--------------------------------------------------------------------------
! Precondition (parameters):
!
! Type            Name                           Min          Max
! -------------------------------------------------------------------------
!tDATDbkDoubleBankHandle HandleDbk					0		cNbDbk-1
!--------------------------------------------------------------------------
! Postcondition (return values):
!
! Type            Name                           Min          Max
! -------------------------------------------------------------------------
! 
!--------------------------------------------------------------------------
! Function review:
!
!
!==========================================================================*/

void DATDbkStartReading ( tDATDbkDoubleBankHandle HandleDbk )
{
    // used in debug mode to check param
    // permet de faire en mode debug des verif des param
    // si la condition n'est pas bonne un message d'erreur est genere
    // mLIBassert( condition )
    mLIBassert( HandleDbk < cNbDbk );

    // This assert check that this double-bank is'nt processing
    // a write operation
    mLIBassert(  (!DATEepIsActivate(mDbkHandleToProcessHandle(HandleDbk)))
                 ||( mReadFlagWriteMode(HandleDbk) == cFalse                ) );

    mClearFlagWriteMode(HandleDbk);
    DATEepProcessRequest( mDbkHandleToProcessHandle ( HandleDbk ));
}


/*=========================================================================
! Function .........
void DATDbkStartUpdate ( tDATDbkDoubleBankHandle HandleDbk )
!--------------------------------------------------------------------------
! Function purpose :
! Permet de mettre a jour le contenu d'une double banque en EEPROM depuis 
!     la RAM
! writing RAM to EEPROM for one double bank
!--------------------------------------------------------------------------
! Precondition (parameters):
!
! Type            Name                           Min          Max
! -------------------------------------------------------------------------
!tDATDbkDoubleBankHandle HandleDbk					0		cNbDbk-1
!--------------------------------------------------------------------------
! Postcondition (return values):
!
! Type            Name                           Min          Max
! -------------------------------------------------------------------------
! 
!--------------------------------------------------------------------------
! Function review:
!
!
!==========================================================================*/

void DATDbkStartUpdate ( tDATDbkDoubleBankHandle HandleDbk )
{
    // used in debug mode to check param
    // permet de faire en mode debug des verif des param
    // si la condition n'est pas bonne un message d'erreur est genere
    // mLIBassert( condition )
    mLIBassert( HandleDbk < cNbDbk );

    // If a write request occurs during a read operation,
    // this request is ignored.
    // This test is a robustness test. The else branch can'not be
    // covered in unitary test.
    if(   (DATEepIsActivate(mDbkHandleToProcessHandle(HandleDbk)) == cFalse)
       || (mReadFlagWriteMode(HandleDbk) != cFalse                         ) )
    {
        mSetFlagWriteMode(HandleDbk);
        DATEepProcessRequest(mDbkHandleToProcessHandle ( HandleDbk ));
    }
    else
    {
        // The EEPROM users can'not request to write during the reading.
        mLIBassert( cFalse );
    }
}


/*=========================================================================
! Function .........
BOOL DATDbkIsWriteOk( tDATDbkDoubleBankHandle DoubleBankHandle )
!--------------------------------------------------------------------------
! Function purpose :
! Permet de controler que l'ecriture de la banque est terminee
! check if double bank writing is terminated
!--------------------------------------------------------------------------
! Precondition (parameters):
!
! Type            Name                           Min          Max
! -------------------------------------------------------------------------
!tDATDbkDoubleBankHandle HandleDbk					0		cNbDbk-1
!--------------------------------------------------------------------------
! Postcondition (return values):
!
! Type            Name                           Min          Max
! -------------------------------------------------------------------------
! BOOL		IsWriteOk						cFalse		cTrue
!--------------------------------------------------------------------------
! Function review:
!
!
!==========================================================================*/

BOOL DATDbkIsWriteOk( tDATDbkDoubleBankHandle HandleDbk )
{
    BOOL IsWriteOk;

    // used in debug mode to check param
    // permet de faire en mode debug des verif des param
    // si la condition n'est pas bonne un message d'erreur est genere
    // mLIBassert( condition )
    mLIBassert( HandleDbk < cNbDbk );

    IsWriteOk = mReadFlagStatusOk(HandleDbk);

    return IsWriteOk;
}


/*=========================================================================
! Function .........
void DATDbkStartRestoringBrokenBanks( void )
!--------------------------------------------------------------------------
! Function purpose :
! reconstruction des DBK si un (et un seul) bloc est casse
! rebuild DBK if one block is broken
!--------------------------------------------------------------------------
! Precondition (parameters):
!
! Type            Name                           Min          Max
! -------------------------------------------------------------------------
!
!--------------------------------------------------------------------------
! Postcondition (return values):
!
! Type            Name                           Min          Max
! -------------------------------------------------------------------------
!
!--------------------------------------------------------------------------
! Function review:
!
!
!==========================================================================*/

void DATDbkStartRestoringBrokenBanks( void )
{
    tDATDbkDoubleBankHandle HandleDbk;

    for ( HandleDbk = 0 ; HandleDbk < cNbDbk ; HandleDbk ++ )
    {
        if (( DbkError [ HandleDbk ] == cDbkErrorBk1 ) || ( DbkError [ HandleDbk ] == cDbkErrorBk2 ))
        {
            // rebuild
            DATDbkStartUpdate ( HandleDbk );
        }
    }
}


/*=========================================================================
! Function .........
BOOL DATDbkIsBankProcessing ( tDATDbkDoubleBankHandle HandleDbk )
!--------------------------------------------------------------------------
! Function purpose :
! Permet de controler que l'ecriture de la banque est terminee
! check if double bank writing is terminated
!--------------------------------------------------------------------------
! Precondition (parameters):
!
! Type            Name                           Min          Max
! -------------------------------------------------------------------------
!tDATDbkDoubleBankHandle HandleDbk					0		cNbDbk-1
!--------------------------------------------------------------------------
! Postcondition (return values):
!
! Type            Name                           Min          Max
! -------------------------------------------------------------------------
! BOOL		IsBankProcessing				cFalse		cTrue
!--------------------------------------------------------------------------
! Function review:
!
!
!==========================================================================*/

BOOL DATDbkIsBankProcessing ( tDATDbkDoubleBankHandle HandleDbk )
{
    BOOL IsBankProcessing;

    // used in debug mode to check param
    // permet de faire en mode debug des verif des param
    // si la condition n'est pas bonne un message d'erreur est genere
    // mLIBassert( condition )
    mLIBassert( HandleDbk < cNbDbk );

    IsBankProcessing = DATEepIsActivate ( mDbkHandleToProcessHandle ( HandleDbk ));
    return IsBankProcessing;
}


/*=========================================================================
! Function .........
BOOL DATDbkIsProcessing ( void )
!--------------------------------------------------------------------------
! Function purpose :
! Permet de controler que l'ecriture de toutes les banques est terminee
! check if all double bank writing is terminated
!--------------------------------------------------------------------------
! Precondition (parameters):
!
! Type            Name                           Min          Max
! -------------------------------------------------------------------------
!
!--------------------------------------------------------------------------
! Postcondition (return values):
!
! Type            Name                           Min          Max
! -------------------------------------------------------------------------
! BOOL		IsTerminate						cFalse		cTrue
!--------------------------------------------------------------------------
! Function review:
!
!
!==========================================================================*/

BOOL DATDbkIsProcessing ( void )
{
    BOOL IsProcessing;
    tDATDbkDoubleBankHandle HandleDbk;

    IsProcessing = cFalse;
    for ( HandleDbk = 0 ; HandleDbk < cNbDbk ; HandleDbk ++ )
    {
        if ( DATDbkIsBankProcessing ( HandleDbk ) == cTrue )
        {
            IsProcessing = cTrue;
        }
    }
    return IsProcessing;
}



/*=========================================================================
! Function .........
void DATDbkCallBackEep ( tDATEepProcessHandle ProcessHandle, BOOL CallBackStatusOk )
!--------------------------------------------------------------------------
! Function purpose :
!   fonction qui est appele par DAT_EEP lorsque la precedente demande est terminee
!	DAT_EEP call this function when previous treatment is terminated
!
!--------------------------------------------------------------------------
! Precondition (parameters):
!
! Type            Name                           Min          Max
! -------------------------------------------------------------------------
!
!--------------------------------------------------------------------------
! Postcondition (return values):
!
! Type            Name                           Min          Max
! -------------------------------------------------------------------------
! 
!--------------------------------------------------------------------------
! Function review:
!
!
!==========================================================================*/

void DATDbkCallBackEep ( tDATEepProcessHandle ProcessHandle, BOOL CallBackStatusOk )
{
#ifdef X90_PROJECT
    DATDbkCallBackEep_Static(ProcessHandle, CallBackStatusOk);
}
#pragma optimize=no_inline
static MEM_TYPE void DATDbkCallBackEep_Static(tDATEepProcessHandle ProcessHandle, BOOL CallBackStatusOk)
{
#endif
    tGraphResult SlaveStatus;

    // used in debug mode to check param
    // permet de faire en mode debug des verif des param
    // si la condition n'est pas bonne un message d'erreur est genere
    // mLIBassert( condition )
    mLIBassert( mProcessHandleToDbkHandle ( ProcessHandle ) < cNbDbk );

    // save param in global data
    // sauve les parametres en global pour ne pas avoir a les passer aux fonctions
    HandleDbkInUse = mProcessHandleToDbkHandle ( ProcessHandle );
    DbkCallBackStatusOk = CallBackStatusOk;
    // donne la taille de la banque en cours avec le checksum
    SizeDbkChkInUse = (tDATEepOffset) ( DATDbkTableBankRom [HandleDbkInUse].SizeBlockRam + (U8) 1 );

    // on ne sort pas de la callback tant que l'on n'a pas fait appel a une fonction Api Eep
    // callback musn't return before calling DAT_EEP function

    // graph de gestion de la double banque
    // double bank treatment routine
    switch ( GraphDbkStatus )
    {
    case cGraphDbkWaitState:
        if ( mReadFlagWriteMode(HandleDbkInUse) != cFalse )
        {
            // execute une demande d'ecriture en double banque
            // copie la RAM banque en RAM Travail
            // copy bank RAM to Working RAM
            // la taille en RAM est en mot (2 octects) et n'a pas de checksum
            // RAM size is in word and haven't checksum
            mLIBmemcpy ( (void*)(DATEepBuffer + 1) , (void*)DATDbkTableBankRom [HandleDbkInUse].AddBlockRam , (SizeDbkChkInUse - 1) * 2 );
            // Calcule le checksum
            // checksum calculation
            DATEepBuffer [ cPosChecksum ] = ChecksumCalculation ( SizeDbkChkInUse );
            // execute une demande d'ecriture
            // writing double bank
            SlaveStatus = WritingDbkGraph ();
            // va a l'etape suivante
            // go to next step
            GraphDbkStatus = cGraphDbkWriteState;
        }
        else
        {
            // execute une demande de lecture de la double banque
            // reading double bank
            SlaveStatus = ReadingDbkGraph ();
            // va a l'etape suivante
            // go to next step
            GraphDbkStatus = cGraphDbkReadState;
        }
        break;
    case cGraphDbkReadState:
        // execute une demande de lecture de la double banque
        // reading double bank
        SlaveStatus = ReadingDbkGraph ();
        if ( SlaveStatus != cGraphResultProcessing )
        {
            // copie la RAM de Travail dans la RAM de la bank
            // copy working RAM to bank RAM
            // la taille en RAM est en mot (2 octects) et n'a pas de checksum
            // RAM size is in word and haven't checksum
            mLIBmemcpy ( (void*)DATDbkTableBankRom [HandleDbkInUse].AddBlockRam , (void*)(DATEepBuffer + 1) , (SizeDbkChkInUse - 1) * 2 );
            // le travail sur la bank est termine
            // work is terminated
            mSetFlagStatusOk(HandleDbkInUse);
            // termine le process
            // stop the process
            DATEepTerminateProcess ();
            // retourne au repos
            // go back to wait
            GraphDbkStatus = cGraphDbkWaitState;
        }
        break;
    case cGraphDbkWriteState:
        // execute une demande de lecture de la double banque
        // writing double bank
        SlaveStatus = WritingDbkGraph ();
        if ( SlaveStatus == cGraphResultOk )
        {
            // le travail sur la bank est termine
            // work is terminated
            mSetFlagStatusOk(HandleDbkInUse);
            // termine le process
            // stop the process
            DATEepTerminateProcess ();
            // retourne au repos
            // go back to wait
            GraphDbkStatus = cGraphDbkWaitState;
        }
        else if ( SlaveStatus == cGraphResultError )
        {
            // le travail sur la bank est termine
            // work is terminated
            mClearFlagStatusOk(HandleDbkInUse);
            // termine le process
            // stop the process
            DATEepTerminateProcess ();
            // retourne au repos
            // go back to wait
            GraphDbkStatus = cGraphDbkWaitState;
        }
        break;
    default:
        mLIBassert(cFalse);
        break;
    }
}



/*=========================================================================
! Function .........
tGraphResult WritingDbkGraph ( void )
!--------------------------------------------------------------------------
! Function purpose :
//------------------------------------------------------------------------------------------
// Graph de gestion de l'ecriture EEPROM pour une double bank
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
// treatment for double bank writing in EEPROM
//------------------------------------------------------------------------------------------
!
!--------------------------------------------------------------------------
! Precondition (parameters):
!
! Type            Name                           Min          Max
! -------------------------------------------------------------------------
! 
!--------------------------------------------------------------------------
! Postcondition (return values):
!
! Type            Name                           Min          Max
! -------------------------------------------------------------------------
! tGraphResult	GraphStatus								
!--------------------------------------------------------------------------
! Function review:
!
!
!==========================================================================*/

tGraphResult WritingDbkGraph ( void )
{
    tGraphResult  GraphStatus;

    // used in debug mode to check param
    // permet de faire en mode debug des verif des param
    mLIBassert( HandleDbkInUse < cNbDbk );
    mLIBassert( SizeDbkChkInUse == DATDbkTableBankRom[HandleDbkInUse].SizeBlockRam+1);

    GraphStatus = cGraphResultProcessing;
    switch ( GraphWriteDbkStatus )
    {
    case cGraphWriteDbkWaitState:
        // commence par le bloc en erreur
        if ( DbkError [ HandleDbkInUse ] == cDbkErrorBk2 )
        {
            // ecrit le bloc 2
            // write block 2
            DATEepWrite ( DATEepBuffer , SizeDbkChkInUse , SizeDbkChkInUse );
        }
        else
        {
            // ecrit le bloc 1
            // write block 1
            DATEepWrite ( DATEepBuffer , 0 , SizeDbkChkInUse );
        }
        // va a l'etape suivante
        // go to next step
        GraphWriteDbkStatus = cGraphWriteDbkBk1State;
        break;
    case cGraphWriteDbkBk1State:
        if ( DbkCallBackStatusOk == cTrue )
        {
            // continue par l'autre bloc
            if ( DbkError [ HandleDbkInUse ] == cDbkErrorBk2 )
            {
                // ecrit le bloc 1
                // write block 1
                DATEepWrite ( DATEepBuffer , 0 , SizeDbkChkInUse );
            }
            else
            {
                // ecrit le bloc 2
                // write block 2
                DATEepWrite ( DATEepBuffer , SizeDbkChkInUse , SizeDbkChkInUse );
            }
            // va a l'etape suivante
            // go to next step
            GraphWriteDbkStatus = cGraphWriteDbkBk2State;
        }
        else
        {
            // le bloc 1 n'a pas ete ecrite correctement
            // write in block 1 is wrong
            DbkError [ HandleDbkInUse ] = cDbkErrorBk1;
            DATPeeErrorIndication ( HandleDbkInUse , cDATDbkErrorWritingBK1 );
            GraphStatus = cGraphResultError;
            GraphWriteDbkStatus = cGraphWriteDbkWaitState;
        }
        break;
    case cGraphWriteDbkBk2State:
        GraphWriteDbkStatus = cGraphWriteDbkWaitState;
        if ( DbkCallBackStatusOk == cTrue )
        {
            // les blocs 1 et 2 ont ete ecrites correctement
            // write in block 1 and 2 is rigth
            DbkError [ HandleDbkInUse ] = cDbkNoError;
            GraphStatus = cGraphResultOk;
        }
        else
        {
            // le bloc 2 n'a pas ete ecrite correctement
            // write in block 2 is wrong
            DbkError [ HandleDbkInUse ] = cDbkErrorBk2;
            DATPeeErrorIndication ( HandleDbkInUse , cDATDbkErrorWritingBK2 );
            GraphStatus = cGraphResultError;
        }
        break;
    default:
        mLIBassert(cFalse);
        break;
    }
    return ( GraphStatus );
}




/*=========================================================================
! Function .........
tGraphResult ReadingDbkGraph ( void )
!--------------------------------------------------------------------------
! Function purpose :
//------------------------------------------------------------------------------------------
// Graph de gestion de la lecture EEPROM pour une double banque
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
// treatment for double bank reading in EEPROM
//------------------------------------------------------------------------------------------
!
!--------------------------------------------------------------------------
! Precondition (parameters):
!
! Type            Name                           Min          Max
! -------------------------------------------------------------------------
! 
!--------------------------------------------------------------------------
! Postcondition (return values):
!
! Type            Name                           Min          Max
! -------------------------------------------------------------------------
! tGraphResult	GraphStatus								
!--------------------------------------------------------------------------
! Function review:
!
!
!==========================================================================*/

tGraphResult ReadingDbkGraph ( void )
{
#ifdef X90_PROJECT
    return ReadingDbkGraph_Static();
}
#pragma optimize=no_inline
static MEM_TYPE tGraphResult ReadingDbkGraph_Static(void)
{
#endif
    tGraphResult GraphStatus;
    tGraphResult SlaveStatus;

    // used in debug mode to check param
    // permet de faire en mode debug des verif des param
    mLIBassert( HandleDbkInUse < cNbDbk );
    mLIBassert( SizeDbkChkInUse == DATDbkTableBankRom[HandleDbkInUse].SizeBlockRam+1);

    GraphStatus = cGraphResultProcessing;
    switch ( GraphReadDbkStatus )
    {
    case cGraphReadDbkWaitState:
        // lit le bloc 1 (appelle le graph de lecture)
        // block 1 reading
        SlaveStatus = ReadingBlockGraph ( 0 );
        // va a l'etape suivante
        // go to next step
        GraphReadDbkStatus = cGraphReadDbkBk1State;
        break;
    case cGraphReadDbkBk1State:
        // lit le bloc 1 (appelle le graph de lecture)
        // block 1 reading
        SlaveStatus = ReadingBlockGraph ( 0 );
        if ( SlaveStatus == cGraphResultOk )
        {
            // verifie le bloc 2
            // check block 2
            DATEepCompare ( DATEepBuffer , SizeDbkChkInUse , SizeDbkChkInUse );
            // va a l'etape suivante
            // go to next step
            GraphReadDbkStatus = cGraphReadDbkCheckState;
        }
        else if ( SlaveStatus == cGraphResultError )
        {
            // copie la RAM de Travail dans la RAM de la bank
            // pour pouvoir disposer d'une image des deux blocs pour la strategie
            // copy working RAM to bank RAM
            mLIBmemcpy ( (void*)DATDbkTableBankRom [HandleDbkInUse].AddBlockRam , (void*)(DATEepBuffer + 1) , (SizeDbkChkInUse - 1) * 2 );
            // positionne un indicateur d'erreur
            DbkError [ HandleDbkInUse ] = cDbkErrorBk1;
            // lit le bloc 2 (appelle le graph)
            // block 2 reading
            SlaveStatus = ReadingBlockGraph ( SizeDbkChkInUse );
            // va a l'etape suivante
            // go to next step
            GraphReadDbkStatus = cGraphReadDbkBk2State;
        }
        break;
    case cGraphReadDbkBk2State:
        // lit le bloc 2 (appelle le graph)
        // block 2 reading
        SlaveStatus = ReadingBlockGraph ( SizeDbkChkInUse );
        if ( SlaveStatus == cGraphResultOk )
        {
            // retourne au repos
            // go back waiting
            GraphStatus = cGraphResultOk;
            GraphReadDbkStatus = cGraphReadDbkWaitState;
        }
        else if ( SlaveStatus == cGraphResultError )
        {
            DbkError [ HandleDbkInUse ] = cDbkErrorBKs;
            // Applique la strategie specifique  (appelle le graph)
            // strategy for total rebuild
            DATPeeRebuildDoubleBank ( HandleDbkInUse );
            // recopie en RAM de travail le contenu de l'image RAM
            mLIBmemcpy ( (void*)(DATEepBuffer + 1) , (void*)DATDbkTableBankRom [HandleDbkInUse].AddBlockRam , (SizeDbkChkInUse - 1) * 2 );
            // la reconstruction est terminee la ram de travail contient un bloc homogene
            GraphStatus = cGraphResultError;
            GraphReadDbkStatus = cGraphReadDbkWaitState;
        }
        break;
    case cGraphReadDbkCheckState:
        if ( DbkCallBackStatusOk == cTrue )
        {
            // la verif est ok la ram de travail contient un bloc homogene
            // chech ok, working RAM contain rigth data
            DbkError [ HandleDbkInUse ] = cDbkNoError;
            GraphStatus = cGraphResultOk;
            GraphReadDbkStatus = cGraphReadDbkWaitState;
        }
        else
        {
            // block 2 <> block 1 and block 1 = ok
            DbkError [ HandleDbkInUse ] = cDbkErrorBk2;
            // retourne au repos
            // go back waiting
            GraphStatus = cGraphResultOk;
            GraphReadDbkStatus = cGraphReadDbkWaitState;
        }
        break;
    default:
        mLIBassert(cFalse);
        break;
    }
    return ( GraphStatus );
}


/*=========================================================================
! Function .........
tGraphResult ReadingBlockGraph ( tDATEepOffset OffsetEeprom )
!--------------------------------------------------------------------------
! Function purpose :
//------------------------------------------------------------------------------------------
// Graph de gestion de la lecture EEPROM pour un bloc
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
// treatment for one block reading in EEPROM
//------------------------------------------------------------------------------------------
!
!--------------------------------------------------------------------------
! Precondition (parameters):
!
! Type            Name                           Min          Max
! -------------------------------------------------------------------------
! tDATEepOffset		OffsetEeprom					0		SizeDbkChkInUse
//      il faut que OffsetEeprom contienne l'offset dans la bk
//          soit 0 pour le bloc 1 de la DBK
//          soit SizeDbkChkInUse pour le bloc 2 de la DBK
// OffsetEeprom must have 0 (bloc 1) or SizeDbkChkInUse value (bloc 2)
!--------------------------------------------------------------------------
! Postcondition (return values):
!
! Type            Name                           Min          Max
! -------------------------------------------------------------------------
! tGraphResult	GraphStatus								
!--------------------------------------------------------------------------
! Function review:
!
!
!==========================================================================*/

tGraphResult ReadingBlockGraph ( tDATEepOffset OffsetEeprom )
{
#ifdef X90_PROJECT
    return ReadingBlockGraph_Static(OffsetEeprom);
}
#pragma optimize=no_inline
static MEM_TYPE tGraphResult ReadingBlockGraph_Static(tDATEepOffset OffsetEeprom)
{
#endif
    static U8 NbRetryReadDatEep;

    tGraphResult GraphStatus;
    U16 Checksum;

    // used in debug mode to check param
    // permet de faire en mode debug des verif des param
    mLIBassert( HandleDbkInUse < cNbDbk );
    mLIBassert( SizeDbkChkInUse == DATDbkTableBankRom[HandleDbkInUse].SizeBlockRam+1);
    mLIBassert( OffsetEeprom < (DATDbkTableBankRom[HandleDbkInUse].SizeBlockRam+1)*2 );

    // init des variables
    // init
    GraphStatus = cGraphResultProcessing;
    switch ( GraphReadStatus )
    {
    case cGraphReadWaitState:
        // on lit le bloc entier, offsetEeprom vaut 0 pour bloc 1 et TailleBlock pour Bloc 2
        // block reading; offsetEeprom = 0 bloc 1 and = TailleBlock Bloc 2
        DATEepRead ( DATEepBuffer , OffsetEeprom , SizeDbkChkInUse );
        // init variable
        NbRetryReadDatEep = cNbRetryReadDatEepMax;
        // va a l'etape suivante
        // go to next step
        GraphReadStatus = cGraphReadDatEepState;
        break;
    case cGraphReadDatEepState:
        // si le Graph est appele et que l'on est a l'etat cGraphReadDatEepState
        // cela signifie que la lecture demandee est terminee (transition tjrs vraie)
        // calcule le checksum
        // cheksum calculation
        Checksum = ChecksumCalculation ( SizeDbkChkInUse );
        // teste le checksum pour savoir quelle sera l'etape suivante
        if ( Checksum == DATEepBuffer [ cPosChecksum ] )
        {
            // le checksum est bon
            // correct checksum
            // la fonction a reussie
            GraphStatus = cGraphResultOk;
            // retourne a l'etat de repos
            // go back to wait
            GraphReadStatus = cGraphReadWaitState;
        }
        else
        {
            // le checksum est faux
            // bad checksum
            // fait une verification
            DATEepCompare ( DATEepBuffer , OffsetEeprom , SizeDbkChkInUse );
            // va a l'etape suivante
            // go to next step
            GraphReadStatus = cGraphReadCheckDatEepState;
        }
        break;
    case cGraphReadCheckDatEepState:
        // teste si la verification est ok
        if ( DbkCallBackStatusOk == cTrue )
        {
            // le bloc est deteriore retourne une erreur
            // block is bad
            GraphStatus = cGraphResultError;
            // retourne a l'etat de repos
            // go back to wait
            GraphReadStatus = cGraphReadWaitState;
        }
        else
        {
            // il y a eu une erreur de lecture recommence
            // decremente le nombre d'essai
            // reading error; NbRetry - 1
            NbRetryReadDatEep --;
            if ( NbRetryReadDatEep == 0 )
            {
                // le nombre d'essai autorise est termine
                // retourne une erreur
                // retry isterminated
                GraphStatus = cGraphResultError;
                if ( OffsetEeprom == 0 )
                {
                    // erreur sur le bloc 1
                    // block 1 error
                    DATPeeErrorIndication ( HandleDbkInUse , cDATDbkErrorReadingBK1 );
                }
                else
                {
                    // erreur sur le bloc 2
                    // block 2 error
                    DATPeeErrorIndication ( HandleDbkInUse , cDATDbkErrorReadingBK2 );
                }
                // retourne a l'etat de repos
                // go back to wait
                GraphReadStatus = cGraphReadWaitState;
            }
            else
            {
                // on lit la banque entiere, offsetEeprom vaut 0 pour BK1 et TailleBlock pour BK2
                // block reading; offsetEeprom = 0 bloc 1 and = TailleBlock Bloc 2
                DATEepRead ( DATEepBuffer , OffsetEeprom , SizeDbkChkInUse );
                // va a l'etape suivante
                // go to next step
                GraphReadStatus = cGraphReadDatEepState;
            }
        }
        break;
    default:
        mLIBassert(cFalse);
        break;
    }
    return ( GraphStatus );
}




/*=========================================================================
! Function .........
void DATDbkInit (void)
!--------------------------------------------------------------------------
! Function purpose :
//------------------------------------------------------------------------------------------
// init du composant DAT_DBK
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
// init for DAT_DBK component
//------------------------------------------------------------------------------------------
!
!--------------------------------------------------------------------------
! Precondition (parameters):
!
! Type            Name                           Min          Max
! -------------------------------------------------------------------------
!
!--------------------------------------------------------------------------
! Postcondition (return values):
!
! Type            Name                           Min          Max
! -------------------------------------------------------------------------
!
!--------------------------------------------------------------------------
! Function review:
!
!
!==========================================================================*/

void DATDbkInit (void)
{
    // init
    // graph var
    GraphDbkStatus = cGraphDbkWaitState;
    GraphWriteDbkStatus = cGraphWriteDbkWaitState;
    GraphReadDbkStatus = cGraphReadDbkWaitState;
    GraphReadStatus = cGraphReadWaitState;

    mLIBmemset( Flags, 0, sizeof(Flags) );
    mLIBmemset( DbkError, 0, sizeof(DbkError) );

    HandleDbkInUse = cNbDbk;
}


