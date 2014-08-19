/*============================================================================
  Component ....................... ParamDFA
  File revision ................... $Revision:   1.0  $
  Last modification date .......... $Modtime:   04 Feb 2009 16:32:34  $
  Generation date ................. 25/02/2003
  Author Name ..................... XX
  File Name ....................... ParamDfa.cpp

  -------------------------------------------------------------------------
  Copyright ... This software is JCI property. Duplication or
                disclosure is prohibited without JCI written permission
  -------------------------------------------------------------------------

  - This file should only contain data useful to the programmer to use
    this Component
  - Component exported macros, constants and types are defined in this file
  - Component exported variables and functions are declared in this file
    with the extern keyword

  ==========================================================================*/

//--------------------------------------------------------------------------
//---------------- Inclusion de fichiers (système et librairies -----------
//--------------------------------------------------------------------------
#define ParamDFA "ParamDFA"
//--------------------------------------------------------------------------
//---------------- Inclusion de fichiers (système et librairies -----------
//--------------------------------------------------------------------------
#if(defined (LDBPC_UTEST))
    #include "PARAMDFA.h"
#else
#include "stdafx.h"
#include "assert.h"
#include "Ldbpc.h"          // defini les types et constantes de bases
#include "Ldbpcpar.h"       // defini la librairie de parametrage
#include "LdbpcErr.h"
#endif

#ifdef cLDBChannelDfa

//--------------------------------------------------------------------------
// CANAL Dfa
//--------------------------------------------------------------------------
// Settings Dfa
//--------------------------------------------------------------------------

#define cu32DataFlashSize       ((U32)0x8000UL)
#define cu32SectorNumber        ((U32)16)
#define cu32FlashGranularity    ((U32)4)

#define mSectorMap()    \
    { \
        { 0x0000UL, 0x800UL }, \
        { 0x0800UL, 0x800UL }, \
        { 0x1000UL, 0x800UL }, \
        { 0x1800UL, 0x800UL }, \
        { 0x2000UL, 0x800UL }, \
        { 0x2800UL, 0x800UL }, \
        { 0x3000UL, 0x800UL }, \
        { 0x3800UL, 0x800UL }, \
        { 0x4000UL, 0x800UL }, \
        { 0x4800UL, 0x800UL }, \
        { 0x5000UL, 0x800UL }, \
        { 0x5800UL, 0x800UL }, \
        { 0x6000UL, 0x800UL }, \
        { 0x6800UL, 0x800UL }, \
        { 0x7000UL, 0x800UL }, \
        { 0x7800UL, 0x800UL }, \
    }

//Every time by startup this file is created, if it doesn't exist, and is initiated with cDFAEraseValue.
//this file is output file of simulated Data Flash.
//Its content correspond to content of DFATable - the mirror of Flash memory.
#define DFABinFileName            "DFA_OUT.DAT"

#define cDFADureeOctetREAD      ( 25 *(cTEMus/cLDBTick))
#define cDFADureeOctetWRITE     ( 300 *(cTEMus/cLDBTick))
#define cInvalidSector            0xFF
#define cInvalidAddr            0xFFFF
#define cDFABlankValue            0xFFFFFFFF
// Erased value should be untyped
#define cDFAErasedValue            0xFF
//--------------------------------------------------------------------------

#define cTitle    "Open the flash initialization file"
//#define cFilter "Flash Files (*.txt)|*.txt||All Files (*.*)|*.*||"
#define cFilter "Flash Files (*.DAT)|*.DAT||All Files (*.*)|*.*||"


static tMsg DFAMsg;
static tMsg DFABuf;
static U8 DFATable[cu32DataFlashSize];
U8 * const pLDBDfaTable = DFATable;

static tMsg * pDFARcvMsg;
static tAddress DFAAdresse;

static S32 DFARefFluxIP;
static S32 DFARefFluxIC;

static S32 DFARefTrameIP;
static S32 DFARefTrameIC;
static S32 DFARefBufferES;

static U8 DFAEraseSector;
tLDBDfaCfgData    CfgData;
tLDBDfaCfgData* pCfgData;

static S32 RefLDBWritingStatus;
static S32 RefLDBErasingStatus;
static S32 RefLDBIntVerifyStatus;


#ifdef    LDB_DFA_USE_WRITE_ERASE_PROTECTION

static BOOL bDFAProtectSector0;

#endif // LDB_DFA_USE_WRITE_ERASE_PROTECTION


typedef struct
{
    U32 Offset;    //offset of the Sector from the beginning of the flash in bytes
    U32 Size;        //size of the Sector in bytes
} tDfaSectorData;

static const tDfaSectorData SectorMap[cu32SectorNumber] =
    mSectorMap();

static void DFAReadInitFileInInitBuffer(void);
static void DFAWriteInFlashFile(U32 Offset, U32 u32Size);

static U32 GetSectorNumber(U32 Address)
{
    U32 i = 0;
    U32 Res = cu32SectorNumber;
    while(i<cu32SectorNumber)
    {
        if( Address<SectorMap[i].Offset+SectorMap[i].Size )
        {
            Res = i;
            i = cu32SectorNumber;
        }
        ++i;
    }
    mLIBassert( Res<cu32SectorNumber );
    return Res;
}

tStatus EraseSector(tLDBDfaCfgData* pCfgData)
{
    U32 SectorOffset;
    U32 SectorSize;

    if(pCfgData->u32BeginAddress != pCfgData->u32EndAddress) 
    {
        pCfgData->u8Status = cLDBError;    //TODO !! - type of error
        return cLDBError;    //not only one sector is requested
    }
    if(pCfgData->u32BeginAddress >= cu32SectorNumber)
    {
        pCfgData->u8Status = cLDBError;    //TODO !! - type of error
        return cLDBError;    //sector number is not correct
    }

    SectorSize = SectorMap[pCfgData->u32EndAddress].Size;
    SectorOffset = SectorMap[pCfgData->u32EndAddress].Offset;

    DFAMsg.pBuffer = DFATable;
    DFAMsg.Lng = cu32DataFlashSize;
//    DONLireB(DFARefBufferES, &DFATable[0][0],NULL,NULL);    //get in DFATable last DLL data
    RESEcrireDmdeMoficationTrame(DFARefTrameIP ,cTrue);
    memset(DFATable+SectorOffset,cDFAErasedValue,SectorSize);
    //write in file here only modified data
    DFAWriteInFlashFile( SectorOffset, SectorSize);

    RESEcrireDureeTrame(0, DFARefFluxIP, cDFADureeOctetWRITE*SectorSize);
    RESEcrireTrameCourante(DFARefFluxIP, 0, &DFAMsg);
    RESEmissionStd(cLDBChannelDfa);
    
    return cLDBCorrect;
}

//    pLDBDfaCfgData-> BeginAddress = 1st physical address to write
//    pLDBDfaCfgData->EndAddress=  last physical address to write
//    pLDBDfaCfgData->pBuffer contains value to write
tStatus WriteData(tLDBDfaCfgData* pCfgData)
{
    U32 Size;
    U32 i;
    U8 *pSrc;
    U8 *pDest;
    BOOL bError;
    tStatus Status;

    if(pCfgData->u32BeginAddress > pCfgData->u32EndAddress) 
    {
        pCfgData->u8Status = cLDBError;    //TODO !! - type of error
        return cLDBError;
    }
    Size = (pCfgData->u32EndAddress - pCfgData->u32BeginAddress);

    mLIBassert(Size <= cInvalidAddr);

    if ((Size % cu32FlashGranularity) != 0)
    {
        pCfgData->u8Status = cLDBError;
        return cLDBError;
    }

    DFAMsg.pBuffer = (U8*)DFATable;
    DFAMsg.Lng = cu32DataFlashSize;
//    DONLireB(DFARefBufferES, &DFATable[0][0],NULL,NULL);    //get in DFATable last DLL data
    RESEcrireDmdeMoficationTrame(DFARefTrameIP ,cTrue);
    // simulate write to simple flash: depending on erased flash value,
    //  the new data should be bitwise OR or bitwise AND between new & old value
    pDest = DFATable + pCfgData->u32BeginAddress;
    pSrc = pCfgData->pBuffer;
    i = Size;
    bError = cFalse;
    while(i--)
    {
        if( *pDest==cDFAErasedValue )
        {
            *pDest = *pSrc;
        }
        else
        {
            // What actually should happen is to use:
            //   - bitwise AND for flash technology wiht erased value 0xFFF...
            //   - bitwise OR for flash technology wiht erased value 0x000...
            //   - more sophisticated algorithm for memory with error
            //     detection and correction (for example ECC memory).
            // By now memory will not be changed upon second write but this
            // could be improved later.
            bError = cTrue;
            mLIBassert(cFalse);
        }
        ++pDest;
        ++pSrc;
    }
    //write in file here only modified data
    DFAWriteInFlashFile( pCfgData->u32BeginAddress, Size);

    RESEcrireDureeTrame(0, DFARefFluxIP, cDFADureeOctetWRITE*Size);
    RESEcrireTrameCourante(DFARefFluxIP, 0, &DFAMsg);
    RESEmissionStd(cLDBChannelDfa);

    Status = bError ? cLDBError : cLDBCorrect;
    return Status;
}

// LDBSendWithOutAddr Specifique
void DFAEmission(tAddress Adr, tMsg * pMsg)
{
    tStatus Status;
    U32 LDBStatus;

    mLIBassert(pMsg->Lng==sizeof(tLDBDfaCfgData));

    pCfgData = &CfgData;
    *pCfgData = *(tLDBDfaCfgData*)pMsg->pBuffer;    //to have last requested command
    pCfgData = (tLDBDfaCfgData*)pMsg->pBuffer;

    switch (pCfgData->u8Command)
    {
        case cLDBDfaErase:
            EraseSector(pCfgData);    //returns the first not erased address
            pCfgData->u8Status = cLDBInProgress;
            DONLireV(RefLDBErasingStatus,  &LDBStatus, NULL, NULL);
        break;

        case cLDBDfaIVerify:
            DONLireV(RefLDBIntVerifyStatus,  &LDBStatus, NULL, NULL);
        break;
        
        case cLDBDfaWrite:
            WriteData(pCfgData);
            pCfgData->u8Status = cLDBInProgress;
            DONLireV(RefLDBWritingStatus,  &LDBStatus, NULL, NULL);
        break;

        default:
            assert(0);
        break;

    }
    if(LDBStatus == 1)
    {
        Status = cLDBCorrect;
    }
    else
    {
        Status = cLDBError;
    }
    
    DATFrlCallBackTxWithoutAddr (Status);
}

tStatus DFABlankSearchFw(tLDBDfaCfgData* pCfgData)
{
    U8* p;
    U8* pBegin; 
    U8* pEnd;
    
    U32 BeginSector = GetSectorNumber(pCfgData->u32BeginAddress);
    U32 BeginSectorAddress = SectorMap[BeginSector].Offset;
    U32 Offset = (pCfgData->u32BeginAddress - BeginSectorAddress);

    pBegin = DFATable + SectorMap[BeginSector].Offset + Offset;

    pEnd  = DFATable + SectorMap[pCfgData->u32EndAddress].Offset + SectorMap[pCfgData->u32EndAddress].Size;

    if((BeginSector > cu32SectorNumber) || (pCfgData->u32EndAddress > cu32SectorNumber))
    {
        pCfgData->u8Status = cLDBError;    //TODO !! - type of error
        return cLDBError;    //address is not correct
    }
    if(((pBegin + Offset) > pEnd) || ((Offset % cu32FlashGranularity) != 0))
    {
        pCfgData->u8Status = cLDBError;    //TODO !! - type of error
        return cLDBError;    //offset is not correct
    }

    DFAMsg.pBuffer = DFATable;
    DFAMsg.Lng = cu32DataFlashSize;
//    DONLireB(DFARefBufferES, &DFATable[0][0],NULL,NULL);    //get in DFATable last DLL data

    for (p = pBegin; p < pEnd ; p += cu32FlashGranularity)
    {
        if (*((U32*)p) != cDFABlankValue)
            break;
    }
    if (p < pEnd)
    {
        pCfgData->u8Status = cLDBDfaNotBlank;
        *((U32*)(pCfgData->pBuffer)) = (U32)(p - DFATable);    // offset address from the beginning
    }
    else    //all is blank
    {
        pCfgData->u8Status = cLDBDfaBlank;
    }
    return cLDBCorrect;
}

tStatus DFABlankSearchBw(tLDBDfaCfgData* pCfgData)
{
    U8* p;
    U8* pBegin; 
    U8* pEnd;
    
    U32 BeginSectorAddress = SectorMap[pCfgData->u32EndAddress].Offset;

    pBegin = DFATable + pCfgData->u32BeginAddress;    //last address
    pEnd   = DFATable + BeginSectorAddress;

    if(pCfgData->u32EndAddress > cu32SectorNumber) 
    {
        pCfgData->u8Status = cLDBError;    //TODO !! - type of error
        return cLDBError;    //address is not correct
    }
    if((pCfgData->u32BeginAddress % cu32FlashGranularity) != 0)
    {
        pCfgData->u8Status = cLDBError;    //TODO !! - type of error
        return cLDBError;    //offset is not correct
    }

    DFAMsg.pBuffer = DFATable;
    DFAMsg.Lng = cu32DataFlashSize;
//    DONLireB(DFARefBufferES, &DFATable[0][0],NULL,NULL);    //get in DFATable last DLL data

    for (p = pBegin; p > pEnd ; p -= cu32FlashGranularity)
    {
        if (*((U32*)p) != cDFABlankValue)    //format of data is "Intel"(little endian)
            break;
    }
    if (p > pEnd)
    {
        pCfgData->u8Status = cLDBDfaNotBlank;
        *((U32*)(pCfgData->pBuffer)) = (U32)(p - DFATable);    // pBuffer[0…3] contains first non blank address backward.
    }
    else    //all is blank
    {
		if (*((U32*)pEnd) != cDFABlankValue)	//format of data is "Intel"(little endian)
        {
		    pCfgData->u8Status = cLDBDfaNotBlank;
		    *((U32*)(pCfgData->pBuffer)) = (U32)(pEnd - DFATable);	// pBuffer[0…3] contains first non blank address backward.
        }
        else
        {
            pCfgData->u8Status = cLDBDfaBlank;
        }
    }
    return cLDBCorrect;
}

tStatus DFAReadData(tLDBDfaCfgData* pCfgData)
{
    U32 Size;

    if(pCfgData->u32EndAddress <= pCfgData->u32BeginAddress) 
    {
        pCfgData->u8Status = cLDBError;    //TODO !! - type of error
        return cLDBError;    //address is not correct
    }

    Size = (pCfgData->u32EndAddress - pCfgData->u32BeginAddress);

    mLIBassert(Size <= cInvalidAddr);

    if((Size % cu32FlashGranularity) != 0)
    {
        pCfgData->u8Status = cLDBError;    //TODO !! - type of error
        return cLDBError;    //offset is not correct
    }

    DFAMsg.pBuffer = DFATable;
    DFAMsg.Lng = cu32DataFlashSize;
//    DONLireB(DFARefBufferES, &DFATable[0][0],NULL,NULL);    //get in DFATable last DLL data

    memcpy(pCfgData->pBuffer, DFATable + pCfgData->u32BeginAddress, Size);

    return cLDBCorrect;
}

// LDBReceiveWithOutAddr Specifique
void DFAReception(tAddress Adr, tMsg * pMsg)
{
    tStatus Status;

    mLIBassert(pMsg->Lng==sizeof(tLDBDfaCfgData));

    pCfgData = &CfgData;
    *pCfgData = *(tLDBDfaCfgData*)pMsg->pBuffer;    //to have last requested command
    pCfgData = (tLDBDfaCfgData*)pMsg->pBuffer;

    switch (pCfgData->u8Command)
    {
        case cLDBDfaCheckBlankFw:
            Status = DFABlankSearchFw(pCfgData);    //returns the first not blank address
            DATFrlCallBackRxWithoutAddr (Status);
        break;
#if (defined (LDB_DFA_USE_BLANK_CHECK_BY_SECTOR))
        case cLDBDfaCheckBlankBw:
            Status = DFABlankSearchBw(pCfgData);    //returns the first not blank address
            DATFrlCallBackRxWithoutAddr (Status);
        break;
#endif    //LDB_DFA_USE_BLANK_CHECK_BY_SECTOR
        case cLDBDfaRead:
            Status = DFAReadData(pCfgData);    //returns the first not blank address
            DATFrlCallBackRxWithoutAddr (Status);
        break;
        default:
            assert(0);
        break;

    }

}

// CallBack de LDBReceiveWithoutAddr Specifique
void DFACallBackReception(tAddress Adresse, tStatus Status)
{
//Do nothing
}

// CallBack de LDBSendWithOutAddr Specifique
void DFACallBackEmission(tAddress Adresse, tStatus Status)
{
//Do nothing
}

// LDBControl Specifique
void DFACallBackCtrl(tCtrl Ctrl)
{
    switch (Ctrl)
    {

    case cLDBDfaStatusCheck:
        break;
#ifdef    LDB_DFA_USE_WRITE_ERASE_PROTECTION

    case cLDBDfaProtectSector0:
        bDFAProtectSector0 = cTrue;
        break;
    case cLDBDfaUnprotectSector0:
        bDFAProtectSector0 = cFalse;
        break;

#endif // LDB_DFA_USE_WRITE_ERASE_PROTECTION

default:
        break;
    }
}
// Initialisation du Dfa
void DfaInit(void)
{
    tCallBackCanal CallBackCanal;
    memset(&CallBackCanal,0,sizeof(tCallBackCanal));
    DFAMsg.pBuffer = DFATable;
    DFAMsg.Lng = cu32DataFlashSize;
//    DFAVerrou = cFalse;
#ifdef    LDB_DFA_USE_WRITE_ERASE_PROTECTION
    bDFAProtectSector0 = cFalse;
#endif // LDB_DFA_USE_WRITE_ERASE_PROTECTION
    DFAEraseSector = cInvalidSector;    //there is no request for sector erasing

// Creation de la structure de Callback du canal Dfa
    CallBackCanal.pCallBackCtrl           =   NULL;
    CallBackCanal.pCallBackEndCtrl        =   (tpCallBackStatusCtrl)DATFrlCallBackEndCtrl;
    CallBackCanal.pCallBackTx             =   DFACallBackEmission;
    CallBackCanal.pCallBackRx             =   DFACallBackReception;
    CallBackCanal.pTxSpontWithAddr         =   NULL;
    CallBackCanal.NbTxSpont               =   0;
    CallBackCanal.pRxSpontWithAddr         =   NULL;
    CallBackCanal.NbRxSpont               =   0;

    // Creation du canal Dfa
    RESCreerCanal(cLDBChannelDfa, "Dfa", &CallBackCanal, DFACallBackCtrl, NULL);
    // RESEcrireFormat(cLDBChannelDfa, cCodageMotorola );

    // Creation des flux
    RESCreerFluxI(&DFARefFluxIP,cLDBChannelDfa, cFluxIP, DFAEmission);
    RESCreerFluxI(&DFARefFluxIC,cLDBChannelDfa, cFluxIC, DFAReception);

    // Creation des trames et des donnees associées
    RESCreerTrameFI(&DFARefTrameIP, DFARefFluxIP, "Write", 0, cu32DataFlashSize 
                    , cFluxIP,cDFADureeOctetWRITE);
    RESCreerTrameFI(&DFARefTrameIC, DFARefFluxIC, "Read", 0,  cu32DataFlashSize
                    , cFluxIC ,cDFADureeOctetREAD);

    // Lecture des valeurs d'init
    DFAReadInitFileInInitBuffer();


    RESCreerEntSorB(&DFARefBufferES, DFARefTrameIP, "Flash",  cu32DataFlashSize*8 , DFATable,  0 );
   
    RESAttacherDonnee(DFARefBufferES, DFARefTrameIC,  0 );

    // Creation des Controles
    RESCreerControleSor(NULL, cLDBChannelDfa, "DfaStatusCheck", cLDBDfaStatusCheck, 0*(cTEMms/cLDBTick));

    #ifdef    LDB_DFA_USE_WRITE_ERASE_PROTECTION
    RESCreerControleSor(NULL, cLDBChannelDfa, "DFAProtectS0", cLDBDfaProtectSector0, 0*(cTEMms/cLDBTick));
    RESCreerControleSor(NULL, cLDBChannelDfa, "DFAUnprotectS0", cLDBDfaUnprotectSector0, 0*(cTEMms/cLDBTick));
    #endif // LDB_DFA_USE_WRITE_ERASE_PROTECTION

    DONCreerEntreeV(&RefLDBWritingStatus,"LDBWritingStatus", 1 /*Init value*/ , 1, "LDBPC_DFA");
    DONCreerEntreeV(&RefLDBErasingStatus,"LDBErasingStatus", 1 /*Init value*/ , 1, "LDBPC_DFA");
    DONCreerEntreeV(&RefLDBIntVerifyStatus,"LDBIntVerifyStatus", 1 /*Init value*/ , 1, "LDBPC_DFA");

}

static void DFAWriteInFlashFile( U32 Offset, U32 u32Size)
{
    U32     u32WriteSize;
    FILE*   pFlashFile;

    pFlashFile = fopen (DFABinFileName, "r+b");

    if (pFlashFile != NULL)
    {
        if (0 == fseek (pFlashFile, Offset, SEEK_SET))        //If successful,fseek returns 0;SEEK_SET = Beginning of file; offset from the SEEK_SET
        {
            u32WriteSize = fwrite((U8*)DFATable+Offset, 1, u32Size, pFlashFile );
            if (u32WriteSize < u32Size)
            {
                assert(u32WriteSize == u32Size);
            }
        }
        else
            assert(0);
        fclose (pFlashFile);
    }
    else
    {
#ifndef LDBPC_UTEST
        MessageBox(0,"Cannot write to DFA Output file!","ERRPR",0);
#endif //LDBPC_UTEST
    }
}

static void DFAReadInitFileInInitBuffer(void)
{
    BOOL bError = cFalse;
    U32  u32ReadSize;
    FILE*   pFlashFile;

    // default flash value is erased value
    mLIBmemset(DFATable,cDFAErasedValue,cu32DataFlashSize);

    pFlashFile = fopen (DFABinFileName, "rb");

    if (pFlashFile != NULL)
    {
        u32ReadSize = fread(DFATable, 1, cu32DataFlashSize, pFlashFile );
        if( u32ReadSize!=cu32DataFlashSize)
        {
            bError = cTrue;
        }
        fclose (pFlashFile);
    }
    else
    {
        bError = cTrue;
    }
    if( bError )
    {
        // in case of error, try to overwrite the whole file
        pFlashFile = fopen(DFABinFileName,"wb");
        fclose(pFlashFile);
        DFAWriteInFlashFile(0,cu32DataFlashSize);
    }
}

#endif

