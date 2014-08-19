/*=========================================================================
  Fonction ........................ dat
  Composant ....................... dat_dea
  Revision PVCS du fichier ........ :   1.3  $
  Date de derniere modification ... $Modtime:   Apr 25 2009 20:57:34  $
  ------------------------------------------------------------------------- 
  Copyright ...... Ce logiciel est la propriete de JCI. Il ne peut etre
                   reproduit ni communique en totalite ou partie sans son
                   autorisation ecrite.
  ------------------------------------------------------------------------- 
  Definition des fonctions exportees par le composant dat_dea:

  Ce fichier dat_dea.c sera compile en un fichier dat_dea.o,
  contenant le code objet des fonctions exportees par le composant.

  - Les  macros, constantes et types qui ne sont pas destines a etre
    exportes sont definis dans ce fichier.
  - Les variables et fonctions qui ne sont pas destinees a etre exportees
    sont definies dans ce fichier et precedees du mot-cle static.

  -------------------------------------------------------------------------
  Reference a la documentation: voir le fichier dat_dea.h
  ------------------------------------------------------------------------- 
  Presentation du composant: voir le fichier dat_dea.h
  -------------------------------------------------------------------------
  Commentaires sur le fonctionnement interne du composant:
    (structures de donnees, algorithmes, limitations, ...)

  -------------------------------------------------------------------------
  Historique PVCS du fichier dat_dea.c:

  :   //45s3/standard/Composants standards/pvcs/archives/Sources/DAT/EEP/DAT_DEA/Dat_dea.c-arc  $
 * 
 *    Rev 1.3   Mar 11 2002 21:42:20   lelabous
 * Complément de la correction de l'EPT PON URD 42  EPT96
 * 
 *    Rev 1.2   Mar 11 2002 21:10:14   lelabous
 * Correction de l'EPT PON URD42 EPT96 (Impossible d'accéder au dernier octet de l'Eeprom). 
 * 
 *    Rev 1.1   Feb 21 2002 15:32:22   lelabous
 * Suppression des commentaires au niveau de l'entête des fichiers
 * 
 *    Rev 1.0   Feb 11 2002 09:57:44   barbaux
 * Initial revision.
 * 
 
  REsumE des modifications:
  -------------------------

  ModifiE par XXX le XX:XX:XX  (EPT Pris en compte : XXX) :
                XXXXXXXXXXXXXXXXXXXXXXXXXX
                XXXXXXXXXXXXXXXXXXXXX


  =========================================================================*/

/*-------------------------------------------------------------------------
  Identification du corps
  -------------------------------------------------------------------------*/
#define dat_dea  "dat_dea"

/*-------------------------------------------------------------------------
  Fichiers inclus

  #include <nom_du_ficher_systeme.h>
  #include "nom_du_ficher_utilisateur.h"
  -------------------------------------------------------------------------*/ 
#include "deftypes.h"  
#include "lib.h"
#include "dat_dea.h"

/*-------------------------------------------------------------------------
  Constantes locales

  #define cNomConstante   ValeurDeLaConstante
  -------------------------------------------------------------------------*/  

/*-------------------------------------------------------------------------
  Macro locales

  #define mNomMacro   (DefinitionDeLaMacro)
  -------------------------------------------------------------------------*/  
#define mConvAdress8ToAdr16( Adr8 ) (U16)(Adr8 >> 1U)
#define mConvNumberByteToNumberWord( NumberByte ) (tDATEepOffset)(NumberByte >> 1U)

/*-------------------------------------------------------------------------
  Types locaux

  struct  sNomStructure { ... };
  union   uNomUnion { ... };
  enum    eNomEnumeration { ... };
  typedef Expression tNomType;
  -------------------------------------------------------------------------*/
typedef enum
{
    cProcessRequest=0,
    cActionRequest
} tCallBackRequest;

typedef enum
{
    cWriteByAddress=0,
    cReadByAddress
} tActionRequest;

/*-------------------------------------------------------------------------
  Variables locales

  static  tType   NomVariable;
  static  tType*  pNomVariable; 
  -------------------------------------------------------------------------*/

static tCallBackRequest   CallBackRequest;
static tActionRequest     ActionRequest;
static BOOL           WriteToEEPROM;
static BOOL           ProcessSupervisorIsActive;
/*-------------------------------------------------------------------------
  Donnees constantes locales

  static const tType  NomVariable;
  -------------------------------------------------------------------------*/  

/*-------------------------------------------------------------------------
  Variables exportees

  tType   COMNomVariable;          (COM: 3 lettres identifiant ce composant)
  tType*  pCOMNomVariable;         (COM: 3 lettres identifiant ce composant)
  -------------------------------------------------------------------------*/ 

U8    DATDeaBufferU8Bit[cDATDeaMaxByte];
U16   DATDeaAddressInByte;
U8    DATDeaSizeBufferInByte;
BOOL  DATDeaWriteIsOk;
BOOL  DATDeaActionIsFinished;

/*-------------------------------------------------------------------------
  Donnees constantes exportees
 
  const tType   COMNomVariable;    (COM: 3 lettres identifiant ce composant)
  -------------------------------------------------------------------------*/ 

/*-------------------------------------------------------------------------
  Prototypes des fonctions locales

  static tTypeRetour NomFonction(tTypeArgument1 NomArgument1, ... );
  -------------------------------------------------------------------------*/
static BOOL AddressAndNumberOfByteIsEven(void);
static MEM_TYPE void StartAction(void);
static MEM_TYPE BOOL CheckConditionBeforeStartAction(void);

#ifdef X90_PROJECT
static MEM_TYPE void DATDeaCallBackEep_Static(tDATEepProcessHandle ProcessHandle, BOOL StatutOK);
static MEM_TYPE void DATDeaStartReadEepromByAddress_Static(void);
static MEM_TYPE void DATDeaStartWriteEepromByAddress_Static(void);
#endif    

/*.........................................................................
  ........................... FONCTIONS LOCALES ...........................
  .........................................................................*/
//****************************************************************************
//   Function Name :
//     static BOOL AddressAndNumberOfByteIsEven(void)
//****************************************************************************
// This function is only used in an assert call.
// So, this function cannot be covered by the unitary test.
static BOOL AddressAndNumberOfByteIsEven(void)
{
    BOOL  Even;

    Even = ((DATDeaAddressInByte    & 0x01) == 0) &&
           ((DATDeaSizeBufferInByte & 0x01) == 0);

    return Even;
}

//****************************************************************************
//   Function Name :
//     static BOOL CheckConditionBeforeStartAction(void)
//****************************************************************************
static MEM_TYPE BOOL CheckConditionBeforeStartAction(void)
{
    BOOL Status;

    Status = cFalse;

    if(  (AddressAndNumberOfByteIsEven())
       &&((U16)((U16)DATDeaSizeBufferInByte+DATDeaAddressInByte)<=cDATDeaSizeEeprom)
       &&(DATDeaActionIsFinished == cTrue)
       &&(DATDeaSizeBufferInByte != 0))
    {
        // Check that the address and the number of byte are even
        // Check that the Eeprom area to access is OK
        // Check that the previous action is finished
        // Check that the Length is not null
        Status = cTrue;
    }
    else
    {
        mLIBassert(cFalse);
    }

    return(Status);
}

//****************************************************************************
//   Function Name :
//     static void StartAction(void)
//****************************************************************************
static MEM_TYPE void StartAction(void)
{
    CallBackRequest=cActionRequest;

    if (ActionRequest==cWriteByAddress)
    {
        // Intialize the Eeprom work Buffer
        mLIBmemcpy( (U8*)DATEepBuffer, DATDeaBufferU8Bit, DATDeaSizeBufferInByte);
        DATEepAbsoluteWrite (DATEepBuffer, mConvAdress8ToAdr16(DATDeaAddressInByte),mConvNumberByteToNumberWord(DATDeaSizeBufferInByte));
    }
    else
    {
        DATEepAbsoluteRead (DATEepBuffer, mConvAdress8ToAdr16(DATDeaAddressInByte), mConvNumberByteToNumberWord(DATDeaSizeBufferInByte));
    }
}

/*.........................................................................
  ........................... FONCTIONS EXPORTEES .........................
  .........................................................................*/

//****************************************************************************
//   Function Name :
//     void DATDeaStartWriteEepromByAddress (void)
//****************************************************************************
void DATDeaStartWriteEepromByAddress (void)
{
#ifdef X90_PROJECT
    DATDeaStartWriteEepromByAddress_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DATDeaStartWriteEepromByAddress_Static(void)
{
#endif
    if(CheckConditionBeforeStartAction() != cFalse)
    {
        // Init of flags
        ActionRequest=cWriteByAddress;
        DATDeaActionIsFinished=cFalse;

        if (ProcessSupervisorIsActive==cFalse)
        {
            // Open the supervisor process
            CallBackRequest=cProcessRequest;
            DATEepProcessRequest (cDATEepProcessSupervisor);
        }
        else
        {
            StartAction();
        }
    }
    else
    {
        mLIBassert(cTrue); //For QAC
        //Do nothing
    }
}


//****************************************************************************
//   Function Name :
//     void DATDeaStartReadEepromByAddress (void)
//****************************************************************************
void DATDeaStartReadEepromByAddress (void)
{
#ifdef X90_PROJECT
    DATDeaStartReadEepromByAddress_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DATDeaStartReadEepromByAddress_Static(void)
{
#endif

    CheckConditionBeforeStartAction();

    // Init of flags
    ActionRequest=cReadByAddress;
    DATDeaActionIsFinished=cFalse;

    if (ProcessSupervisorIsActive==cFalse)
    {
        CallBackRequest=cProcessRequest;
        // Open the supervisor process
        DATEepProcessRequest (cDATEepProcessSupervisor);
    }
    else
    {
        StartAction();
    }
}

//****************************************************************************
//   Function Name :
//     void DATDeaCallBackEep (tDATEepProcessHandle ProcessHandle, BOOL StatutOK)
//****************************************************************************
void DATDeaCallBackEep (tDATEepProcessHandle ProcessHandle, BOOL StatutOK)
{
#ifdef X90_PROJECT
    DATDeaCallBackEep_Static(ProcessHandle, StatutOK);
}
#pragma optimize=no_inline
static MEM_TYPE void DATDeaCallBackEep_Static(tDATEepProcessHandle ProcessHandle, BOOL StatutOK)
{
#endif    
    switch (CallBackRequest)
    {
    case cProcessRequest :
        // End of the request opening
        ProcessSupervisorIsActive=cTrue;
        StartAction();
        break;

    case cActionRequest :
        // End of the action (writing or reading)
        DATDeaActionIsFinished=cTrue;

        if (ActionRequest==cWriteByAddress)
        {
            DATDeaWriteIsOk=cTrue;
            if (StatutOK==cFalse)
            {
                DATDeaWriteIsOk=cFalse;
            }
            else
            {
                // nothing
            }
            WriteToEEPROM=cTrue;
            // The supervisor process is never closed after a writing
        }
        else
        {
            // Copy the result of reading to DATDeaBufferU8Bit
            mLIBmemcpy(DATDeaBufferU8Bit, (U8*)DATEepBuffer, DATDeaSizeBufferInByte);

            if (WriteToEEPROM==cFalse)
            {
                // Close the supervisor process if no writing have been done before
                DATEepTerminateProcess();
                ProcessSupervisorIsActive=cFalse;
            }
            else
            {
                // The supervisor process is never closed after a writing
            }
        }
        break;

    default :
        // impossible
        mLIBassert( cFalse );
        break;
    }
}

//****************************************************************************
//   Function Name :
//    void DATDeaInitialize (void)
//****************************************************************************
void DATDeaInitialize (void)
{
    mLIBassert( sizeof(DATDeaBufferU8Bit) <= sizeof(DATEepBuffer) );

    DATDeaWriteIsOk=cTrue;
    DATDeaActionIsFinished=cTrue;
    WriteToEEPROM=cFalse;
    ProcessSupervisorIsActive=cFalse;
}
