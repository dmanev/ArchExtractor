/*=========================================================================
  Function ........................ DAT
  Component ....................... DAT_SBK
  PVCS File revision............... :   1.0  $
  Last modification date .......... $Modtime:   Apr 25 2009 21:02:24  $
  ------------------------------------------------------------------------- 
  Copyright ...... This software is JCI property. Duplication or 
  disclosure is prohibited without the JCI writen authorization
  ------------------------------------------------------------------------- 
  DAT_SBK component exported function definition 
  
  This file DAT_SBK.c is compile and a DAT_SBK.o is generated
  The object file includes the functions exported by the component.
  
  - The macros, constatnts et types wich are not exported are defined in 
  this file
  - The variables and functions which are not exported are defined in this 
  file wich the static key word
  
  -------------------------------------------------------------------------
  Document reference : see the DAT_SBK.h file
  ------------------------------------------------------------------------- 
  Component presentation : see the DAT_SBK.h file
  -------------------------------------------------------------------------
  Comments on the component (algorithm, structure, limitations, ...)

  -------------------------------------------------------------------------
  DAT_SBK.c file review : 
  
  21/08/2001 : AV - Alexandre Vion (OW1003)

  =========================================================================*/

/*-------------------------------------------------------------------------
  Body Identification
  -------------------------------------------------------------------------*/


#define DAT_SBK    "dat_sbk"

/*-------------------------------------------------------------------------
  Included files

  #include <nom_du_ficher_systeme.h>
  #include "nom_du_ficher_utilisateur.h"
  -------------------------------------------------------------------------*/ 


#include "lib.h"              /* defini les types et constantes de bases */
#include "DAT_Sbk.h"
#include "Dat_Eep.h"

/*-------------------------------------------------------------------------
  Local constants

  #define cNomConstante   ValeurDeLaConstante
  -------------------------------------------------------------------------*/  

/////////////////////////////////////////////////////////////////////////////
// Bank flags : Mask definitions
/////////////////////////////////////////////////////////////////////////////

// ModeFlag ? WriteMode : ReadMode
#define   cFlag_ModeFlag          ((U8) 0x01)

// ErrorFlag ? WritingError : NoError
#define   cFlag_ErrorFlag         ((U8) 0x02)

/*-------------------------------------------------------------------------
  Local macro

  #define mNomMacro   (DefinitionDeLaMacro)
  -------------------------------------------------------------------------*/  

/////////////////////////////////////////////////////////////////////////////
// Handle conversions (between DAT_SBK and DAT_EEP)
/////////////////////////////////////////////////////////////////////////////

#define mConv_DatSbkHandle_To_DatEepHandle(HandleSbk)        \
            ((tDATEepProcessHandle)     (HandleSbk + cDATSbkFirstProcessHandle))

#define mConv_DatEepHandle_To_DatSbkHandle(HandleEep)        \
            ((tDATSbkSingleBankHandle)  (HandleEep - cDATSbkFirstProcessHandle))


/////////////////////////////////////////////////////////////////////////////
// Bank flag acces
/////////////////////////////////////////////////////////////////////////////

// Macro for "Mode" acces
#define   mBankFlag_SetReadMode(SINGLE_BANK_HANDLE)                   \
            { SingleBankFlags[SINGLE_BANK_HANDLE] &= ~cFlag_ModeFlag; } /* Reset    "cFlag_ModeFlag"  */  

#define   mBankFlag_SetWriteMode(SINGLE_BANK_HANDLE)                  \
            { SingleBankFlags[SINGLE_BANK_HANDLE] |=  cFlag_ModeFlag; }  /* Set      "cFlag_ModeFlag"  */  

// Macro for "Mode" tests
#define   mBankFlag_IsReadMode(SINGLE_BANK_HANDLE)                    \
            ( mBankFlag_IsWriteMode(SINGLE_BANK_HANDLE) == cFalse)       /* !"cFlag_ModeFlag" ?        */  

#define   mBankFlag_IsWriteMode(SINGLE_BANK_HANDLE)                   \
            ( SingleBankFlags[SINGLE_BANK_HANDLE] & cFlag_ModeFlag )    /* "cFlag_ModeFlag" ?         */  


// Macro for "Error" acces
#define   mBankFlag_SetNoError(SINGLE_BANK_HANDLE)                    \
            { SingleBankFlags[SINGLE_BANK_HANDLE] &= ~cFlag_ErrorFlag; }  /* Reset  "cFlag_ErrorFlag" */

#define   mBankFlag_SetWritingError(SINGLE_BANK_HANDLE)               \
            { SingleBankFlags[SINGLE_BANK_HANDLE] |=  cFlag_ErrorFlag; }  /* Set    "cFlag_ErrorFlag" */

// Macro for "Error" test
#define   mBankFlag_IsWritingError(SINGLE_BANK_HANDLE)                  \
            ( SingleBankFlags[SINGLE_BANK_HANDLE] & cFlag_ErrorFlag )     /* "cFlag_ErrorFlag" ?      */


/*-------------------------------------------------------------------------
  Local type

  struct  sNomStructure { ... };
  union   uNomUnion { ... };
  enum    eNomEnumeration { ... };
  typedef Expression tNomType;
  -------------------------------------------------------------------------*/

// StateChart State's ...
typedef enum
{
    cChartState_Wait,
    cChartState_Writing,
    cChartState_Reading,
    cChartState_CompareAfterReading
}     S8tState;

/*-------------------------------------------------------------------------
  Local data

  static  tType   NomVariable;
  static  tType*  pNomVariable; 
  -------------------------------------------------------------------------*/

// Bank Flags
static  U8          SingleBankFlags[cNbSbk];

// StateChart current state
static  S8tState     ChartState;

// StateChart current reading retry
static  U8          DatSbk_CurrentNumberOfReadingRetry;

/*-------------------------------------------------------------------------
  Constant local Data

  static const tType  NomVariable;
  -------------------------------------------------------------------------*/  

// Structure en ROM qui permet d'acceder aux adresses des SBK
const tDATSbkTableBankRom DATSbkTableBankRom [cNbSbk] =
    {
        mDATSbkInitTableBankROM()
    };

/*-------------------------------------------------------------------------
  Exported data

  tType   COMNomVariable;          (COM: 3 lettres identifiant ce composant)
  tType*  pCOMNomVariable;         (COM: 3 lettres identifiant ce composant)
  -------------------------------------------------------------------------*/ 

// variable definissant toutes les simples banques en RAM
tDATSbkMirrors    DATSbkMirrors;

/*-------------------------------------------------------------------------
  Constant exported data
 
  const tType   COMNomVariable;    (COM: 3 lettres identifiant ce composant)
  -------------------------------------------------------------------------*/ 

/*-------------------------------------------------------------------------
  Local functions prototype
  
  static tTypeRetour NomFonction(tTypeArgument1 NomArgument1, ... );
  -------------------------------------------------------------------------*/

// 16bits CheckSum (general) Computing function
static  U16 Compute16BitsCheckSum (U16* Buffer, U16 BufferSizeInWords);

#ifdef X90_PROJECT
static MEM_TYPE void DATSbkCallBackEep_Static( tDATEepProcessHandle DATEepProcessHandle, BOOL DATEepCallBackStatusIsOk );
#endif

/*.........................................................................
  ........................... LOCAL FUNCTIONS..............................
  .........................................................................*/

/*=========================================================================
! Function .........
! void DATSbkInit (void)
!--------------------------------------------------------------------------
! Function purpose :
! init for DAT_SBK component
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

void DATSbkInit (void)
{
    // StateChart Reset (very important)
    ChartState                          =  cChartState_Wait;

    // Current reading retry reset (not important)
    DatSbk_CurrentNumberOfReadingRetry  = 0;

    // Single Bank flags reset (not important)
    mLIBmemset(SingleBankFlags, 0x00, sizeof(SingleBankFlags));
}

/*=========================================================================
! Function .........
! U16 Compute16BitsCheckSum (U16* Buffer, U16 BufferSizeInWords)
!--------------------------------------------------------------------------
! Function purpose :
! 16bits CheckSum calculation on a *16bits* buffer 
!
!--------------------------------------------------------------------------
! Precondition (parameters):
!
! Type            Name                           Min          Max
! -------------------------------------------------------------------------
! U16*        Buffer                         16bits Buffer pointor 
! U16         BufferSizeInWords              0            ...          
!--------------------------------------------------------------------------
! Postcondition (return values):
!
! Type            Name                           Min          Max
! -------------------------------------------------------------------------
! U16         CheckSum                        0            0xFFFF
!--------------------------------------------------------------------------
! Function review:
!
! Return the sum'inverse
!==========================================================================*/

U16 Compute16BitsCheckSum (U16* Buffer, U16 BufferSizeInWords)
{
    U16 Checksum = 0;

    //// Used in debug mode to check param  ////
    mLIBassert(Buffer != NULL);

    // Compute the check-sum
    while (BufferSizeInWords > 0)
    {
        Checksum += *Buffer;

        // Inc./Dec.
        Buffer++;
        BufferSizeInWords--;
    }

    // Return the inverse of the check-sum value
    return (~Checksum);
}



/*.........................................................................
  ........................... EXPORTED FUNCTIONS. .........................
  .........................................................................*/




/*=========================================================================
! Function .........
BOOL DATSbkIsBankProcessing ( tDATSbkSingleBankHandle HandleSbk )
!--------------------------------------------------------------------------
! Function purpose :
! check if single bank writing is terminated
!--------------------------------------------------------------------------
! Precondition (parameters):
!
! Type            Name                           Min          Max
! -------------------------------------------------------------------------
!tDATSbkSingleBankHandle HandleSbk                0            cNbSbk-1
!--------------------------------------------------------------------------
! Postcondition (return values):
!
! Type            Name                           Min          Max
! -------------------------------------------------------------------------
! BOOL    IsBankProcessing                    cFalse        cTrue
!--------------------------------------------------------------------------
! Function review:
!
!
!==========================================================================*/

BOOL DATSbkIsBankProcessing ( tDATSbkSingleBankHandle HandleSbk )
{
    /// Used in debug mode to check param  ////
    mLIBassert( HandleSbk < cNbSbk );

    // Return ("HandleSbk" Bank is processing ?)
    return DATEepIsActivate (mConv_DatSbkHandle_To_DatEepHandle(HandleSbk));
}


/*=========================================================================
! Function .........
BOOL DATSbkIsProcessing ( void )
!--------------------------------------------------------------------------
! Function purpose :
! check if all single bank writing is terminated
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
! BOOL    IsTerminate                          cFalse        cTrue
!--------------------------------------------------------------------------
! Function review:
!
!
!==========================================================================*/

BOOL DATSbkIsProcessing ( void )
{
    tDATSbkSingleBankHandle HandleSbk;
    BOOL                IsProcessing = cFalse;

    // Check all banks ...
    for (HandleSbk = 0; HandleSbk < cNbSbk; HandleSbk++)
    {
        if (DATSbkIsBankProcessing(HandleSbk) == cTrue)
        {
            /* ok */
            IsProcessing = cTrue;

            /* Force "End of checking" */
            HandleSbk = cNbSbk;         // <=> break; (in order to avoid a QAC warning)
        }
    }

    // Return
    return IsProcessing;
}

/*=========================================================================
! Function .........
void DATSbkStartReadingAllBanks ( void )
!--------------------------------------------------------------------------
! Function purpose :
! reading EEPROM to RAM for all single banks
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

void DATSbkStartReadingAllBanks ( void )
{
    tDATSbkSingleBankHandle HandleSbk;

    // Reading request for all banks ...
    for (HandleSbk = 0; HandleSbk < cNbSbk; HandleSbk++)
    {
        DATSbkStartReading (HandleSbk);
    }
}

/*=========================================================================
! Function .........
void DATSbkStartReading ( tDATSbkSingleBankHandle Handle )
!--------------------------------------------------------------------------
! Function purpose :
! reading EEPROM to RAM for one single bank
!--------------------------------------------------------------------------
! Precondition (parameters):
!
! Type            Name                           Min          Max
! -------------------------------------------------------------------------
!tDATSbkSingleBankHandle HandleSbk                0            cNbSbk-1
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

void DATSbkStartReading ( tDATSbkSingleBankHandle HandleSbk )
{
    //// Used in debug mode to check param  ////
    mLIBassert( HandleSbk < cNbSbk );

    //// This assert check that this single-bank is'nt processing yet ////
    mLIBassert(DATSbkIsBankProcessing(HandleSbk) == cFalse);

    //// Starting Reading process ...
    mBankFlag_SetReadMode(HandleSbk);
    DATEepProcessRequest(mConv_DatSbkHandle_To_DatEepHandle(HandleSbk));
}


/*=========================================================================
! Function .........
void DATSbkStartUpdate ( tDATSbkSingleBankHandle HandleSbk )
!--------------------------------------------------------------------------
! Function purpose :
! writing RAM to EEPROM for one single bank
!--------------------------------------------------------------------------
! Precondition (parameters):
!
! Type            Name                           Min          Max
! -------------------------------------------------------------------------
!tDATSbkSingleBankHandle HandleSbk                0            cNbSbk-1
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

void DATSbkStartUpdate ( tDATSbkSingleBankHandle HandleSbk )
{
    //// Used in debug mode to check param  ////
    mLIBassert( HandleSbk < cNbSbk );

    // If a write request occurs during a read operation,
    // this request is ignored.
    // This test is a robustness test. The else branch can'not be
    // covered in unitary test.
    if(  (DATSbkIsBankProcessing(HandleSbk) == cFalse) ||
         (mBankFlag_IsReadMode (HandleSbk)  == cFalse)    )
    {
        //// Starting Writing process ...
        mBankFlag_SetWriteMode(HandleSbk);
        DATEepProcessRequest(mConv_DatSbkHandle_To_DatEepHandle(HandleSbk));
    }
    else
    {
        // The EEPROM users can'not request to write during the reading.
        mLIBassert( cFalse );
    }
}


/*=========================================================================
! Function .........
BOOL DATSbkIsWriteOk( tDATSbkSingleBankHandle HandleSbk )
!--------------------------------------------------------------------------
! Function purpose :
! check if single bank writing is correctly terminated
!--------------------------------------------------------------------------
! Precondition (parameters):
!
! Type            Name                           Min          Max
! -------------------------------------------------------------------------
!tDATSbkSingleBankHandle HandleSbk                0            cNbSbk-1
!--------------------------------------------------------------------------
! Postcondition (return values):
!
! Type            Name                           Min          Max
! -------------------------------------------------------------------------
! BOOL        IsWriteOk                        cFalse        cTrue
!--------------------------------------------------------------------------
! Function review:
!
!
!==========================================================================*/

BOOL DATSbkIsWriteOk( tDATSbkSingleBankHandle HandleSbk )
{
    BOOL IsWriteOk = cFalse;

    //// Used in debug mode to check param  ////
    mLIBassert( HandleSbk < cNbSbk );

    // Check error flag ...
    if (mBankFlag_IsWritingError(HandleSbk) == cFalse)
    {
        /* ok */
        IsWriteOk = cTrue;
    }

    // Return
    return IsWriteOk;
}


/*=========================================================================
! Function .........
void DATSbkCallBackEep ( tDATEepProcessHandle DATEepProcessHandle, BOOL DATEepCallBackStatusIsOk )
!--------------------------------------------------------------------------
! Function purpose :
!  DAT_EEP call this function when previous treatment is terminated
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
! Callback musn't return before calling DAT_EEP function !
!
!==========================================================================*/

void DATSbkCallBackEep ( tDATEepProcessHandle DATEepProcessHandle, BOOL DATEepCallBackStatusIsOk )
{
#ifdef X90_PROJECT
    DATSbkCallBackEep_Static(DATEepProcessHandle, DATEepCallBackStatusIsOk);
}
#pragma optimize=no_inline
static MEM_TYPE void DATSbkCallBackEep_Static( tDATEepProcessHandle DATEepProcessHandle, BOOL DATEepCallBackStatusIsOk )
{
#endif    
    tDATSbkSingleBankHandle       HandleSbk;
        
    U16*                      Sbk_AddBlockRam;
    tDATEepOffset                 Sbk_SizeBlockRam;

    // Get the current Sbk Handle
    HandleSbk         = mConv_DatEepHandle_To_DatSbkHandle(DATEepProcessHandle);

    //// Used in debug mode to check param  ////
    mLIBassert(HandleSbk < cNbSbk);

    // Get information on current Sbk bank
    Sbk_AddBlockRam   = DATSbkTableBankRom[HandleSbk].AddBlockRam;
    Sbk_SizeBlockRam  = DATSbkTableBankRom[HandleSbk].SizeBlockRam;

    ///////////////////////////////////////////////////////////////////////
    // State Mate :)
    // (Continue treatment routine ...)
    ///////////////////////////////////////////////////////////////////////
    switch (ChartState)
    {

        ///////////////////////////////////////////////////////////////////////
        // Waiting for the activated process ?
        ///////////////////////////////////////////////////////////////////////
    case cChartState_Wait:

        ////////////////////////////////////////////////////
        // Performe a writing operation ?
        ////////////////////////////////////////////////////
        if (mBankFlag_IsWriteMode(HandleSbk) == cTrue)
        {
            // >>> Get ready for "Writing" <<<
            ChartState = cChartState_Writing;

            // Store data into DAT_EEP buffer
            // (keep one 16bits-word for check-sum at the buffer'top)
            mLIBmemcpy ((U8 *) (DATEepBuffer + 1),
                        (U8 *) (Sbk_AddBlockRam), Sbk_SizeBlockRam * sizeof(U16));

            // Compute the 16bits check-sum (of DAT_EEP)
            // and store it at the DAT_EEP buffer'top
            DATEepBuffer[0] = Compute16BitsCheckSum (DATEepBuffer+1, Sbk_SizeBlockRam);


            // Now, let's go for writing operation by the way of DAT_EEP
            DATEepWrite (DATEepBuffer, (tDATEepOffset)0, (tDATEepOffset)(1 + Sbk_SizeBlockRam));
            // NOTA : "+1" is for the 16bits check-sum (at the top of the bank)
        }
        else
            ////////////////////////////////////////////////////
            // or Performe a reading operation ?
            ////////////////////////////////////////////////////
        {
            // >>> Get ready for "Reading" state <<<
            ChartState = cChartState_Reading;

            // Reset "current number of reading retry"
            DatSbk_CurrentNumberOfReadingRetry = 0;

            // Now, let's go for reading operation by the way of DAT_EEP
            DATEepRead(DATEepBuffer, (tDATEepOffset)0, (tDATEepOffset)(1 + Sbk_SizeBlockRam));
            // NOTA : "+1" is for the 16bits check-sum (at the top of the bank)
        }



        break;


        ///////////////////////////////////////////////////////////////////////
        // Waiting for the terminated writing process ?
        ///////////////////////////////////////////////////////////////////////
    case cChartState_Writing:

        // Writing process is done (bye bye)
        ChartState = cChartState_Wait;
        DATEepTerminateProcess();

        // Check for error reporting
        if (DATEepCallBackStatusIsOk == cTrue)
        {
            /* No error detected */
            mBankFlag_SetNoError(HandleSbk);
        }
        else
        {
            /* Write Error detected ! */
            mBankFlag_SetWritingError(HandleSbk);
            DATPeeSingleBankErrorIndication(HandleSbk, cDATSbkErrorWriting);
        }

        break;


        ///////////////////////////////////////////////////////////////////////
        // Waiting for the terminated reading process ?
        ///////////////////////////////////////////////////////////////////////
    case cChartState_Reading:

        // Make a copy of DAT_EEP buffer into DAT_SBK current ram buffer (without the 16bits check-sum)...
        mLIBmemcpy ((U8 *) (Sbk_AddBlockRam),
                    (U8 *) (DATEepBuffer + 1), Sbk_SizeBlockRam * sizeof(U16));


        // Check the 16bits check-sum (locate at the bank'top) ...
        if (Compute16BitsCheckSum(DATEepBuffer + 1, Sbk_SizeBlockRam) == DATEepBuffer[0])
        {
            // The Reading process is done (bye bye)
            ChartState = cChartState_Wait;
            DATEepTerminateProcess();
        }
        else  // Error detected, start "Compare" process
        {
            // >>> Get ready for "Compare" state <<<
            ChartState = cChartState_CompareAfterReading;

            // Now, let's go for compare operation by the way of DAT_EEP
            DATEepCompare(DATEepBuffer, (tDATEepOffset)0, (tDATEepOffset)(1 + Sbk_SizeBlockRam));
            // NOTA : "+1" is for the 16bits check-sum (at the top of the bank)
        }

        break;


        ///////////////////////////////////////////////////////////////////////
        // Waiting for the terminated "Compare After Reading" process ?
        ///////////////////////////////////////////////////////////////////////
    case cChartState_CompareAfterReading:

        // Check compare error status (Compare Ok ?)
        if (DATEepCallBackStatusIsOk == cTrue)
        {
            // Compare process is done (bye bye)
            ChartState = cChartState_Wait;
            DATEepTerminateProcess();

            // Compare Ok => bank is broken (this bank must be rebuild par DAT_PEE)
            DATPeeRebuildSingleBank(HandleSbk);
        }
        else  // Noisy reading => re-start reading process !
        {
            // Can we re-start reading process ?
            if (DatSbk_CurrentNumberOfReadingRetry < cSbk_NbRetryReadDatEepMax)
            {
                // >>> Get ready for "Reading" state <<<
                ChartState = cChartState_Reading;

                // Now, let's go for retry reading operation
                DatSbk_CurrentNumberOfReadingRetry++;
                DATEepRead(DATEepBuffer, (tDATEepOffset)0, (tDATEepOffset)(1 + Sbk_SizeBlockRam));
                // NOTA : "+1" is for the 16bits check-sum (at the top of the bank)

            } else  // Max retry reached !
            {
                // Compare process is done (bye bye)
                ChartState = cChartState_Wait;
                DATEepTerminateProcess();

                /* Write Error reporting (external only) and
                   Inform the DAT_PEE compoment in order to rebuild the current bank */
                DATPeeSingleBankErrorIndication(HandleSbk, cDATSbkErrorReading);
                DATPeeRebuildSingleBank(HandleSbk);
            }
        }

        break;


        ///////////////////////////////////////////////////////////////////////
        // Default/Error State
        ///////////////////////////////////////////////////////////////////////
    default:
        mLIBassert(cFalse);    /* error report */
        break;
    }
}


