//******************************************************************************
// Company:      Johnson Controls Inc.
// -----------------------------------------------------------------------------
// Copyright:    This software is JCI property.
//               Duplication or disclosure without JCI written authorization
//               is prohibited.
// -----------------------------------------------------------------------------
// Project:      <PROJECT>
// Language:     ANSI-C
// -----------------------------------------------------------------------------
// Component:    <Comments about the component (role, algorithm, structure, 
//               limitations, defined tasks and events...)>
// -----------------------------------------------------------------------------
// $Date:   04 Feb 2009 17:02:40  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/EXT_CMP/CPP_CMP/STK/SIMUL/ParamLDB/PARAMEEP.CPP-arc  $
// $Revision:   1.0  $
// -----------------------------------------------------------------------------
/* $Log:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/EXT_CMP/CPP_CMP/STK/SIMUL/ParamLDB/PARAMEEP.CPP-arc  $
// 
//    Rev 1.0   04 Feb 2009 17:02:40   adzhelp
// Initial revision.
 * 
 *    Rev 1.11   May 03 2007 18:50:14   agueric
 * PON URD45 CUS 618 / PON URD45 BODY_SW 809 : "EEProm writing can be forbidden forever" => Integrated the DAT_MAN component
 * 
 *    Rev 1.8   Jul 29 2005 11:19:46   alentej
 * PON URD45 CUS 129 / PON URD42 BODY_SW 992 : Update of the code template after review done by the SEPG in June
*/
//******************************************************************************

//------------------------------------------------------------------------------
// Body Identification
//------------------------------------------------------------------------------
#define ParamEEP "ParamEEP"
//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//
// #include <system_file_name.h>
// #include "project_file_name.h"
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "assert.h"
#include "Ldbpc.h"          // defini les types et constantes de bases
#include "Ldbpcpar.h"       // defini la librairie de parametrage
#include "LdbpcErr.h"

#ifdef cLDBChannelEep

//------------------------------------------------------------------------------
// Local constants
//
// #define cConstantName   ((tType) ConstantValue)
//------------------------------------------------------------------------------
#define cEPPFileName			      "DAT_PEEi.txt"
//#define cInitialDir           "D:\\PROJECT\\BUILD\\SOURCES"
#define cEEPErrorOnOddAdress
#define cEEPTaille				      ((LDBPARAM_TYPE_LNGMSG)cLDBEepSize)
#define cEEPDureeOctetREAD      ( 25 *(cTEMus/cLDBTick))
#define cEEPDureeOctetWRITE     ( 300 *(cTEMus/cLDBTick))

#define cTitle	"Open the eeprom initialization file"
#define cFilter "Eeprom Files (*.txt)|*.txt||All Files (*.*)|*.*||"

//------------------------------------------------------------------------------
// Local macros
//
// #define mMacroName   (MacroDefinition)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Local types
//
// typedef Expression    tTypeName;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Data prefix
//
// unsigned int {u8,u16,u32} / signed int {s8,s16,s32} 
// register size unsigned int {r} / float {f32,f64}  / s for struct 
//
// -----------------------------------------------------------------------------
// Local data
//
// static  tType   u8VariableName;  
// static  tType*  pu8VariableName; 
//------------------------------------------------------------------------------
static tMsg EEPMsg;
static U8 EEPTable[cEEPTaille] = {0};
static U8 EEPTableInit[cEEPTaille] = {0};
static tMsg * pEEPRcvMsg;
static tAddress EEPAdresse;

static S32 EEPRefFluxIP;
static S32 EEPRefFluxIC;

static S32 EEPRefTrameIP;
static S32 EEPRefTrameIC;
static BOOL EEPVerrou;

#ifdef cLDBEepUnprotect

// EEPUnprotectCycleCount:
//   0..1   => immediate unprotect (like if the EEPROM is not protected)
//   2..254 => delayed unprotect, like if the write operation is not instantaneous
//   255    => unprotect never ends
static U8  EEPUnprotectCycleCount;
#endif // cLDBEepUnprotect
static S32 EEPRefBufferES;

//------------------------------------------------------------------------------
// Constant local data
//
// static const tType  VariableName;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported data
//
// tType   u8LAYCmpVariableName; (LAY: 3 characters to identify the layer)
// tType*  pu8LAYCmpVariableName;(Cmp: 3 characters to identify the component)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Constant exported data
//
//             (LAY: 3 characters to identify the layer)
//             (Cmp: 3 characters to identify this component)
// 
// const tType   LAYCmpVariableName;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Local function prototypes
// 
// static tTypeRetour FunctionName(tTypeArgument1 ArgumentName1, ... );
//------------------------------------------------------------------------------
void EEPReadInitFile(void);


//==============================================================================
//=========================== LOCAL FUNCTIONS ==================================
//==============================================================================

//==============================================================================
// DESCRIPTION : LDBSend simulation
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
// LDBSendWithAddr Specifique
void EEPEmission(tAddress Adr, tMsg * pMsg)
{
    EEPAdresse = Adr;

	#ifdef cEEPErrorOnOddAdress
    if(Adr%2) // If odd address
	{
		 mLDBPCErreur("EEP : Detect an eeprom writing on an odd address !");
	}
	#endif

	if(EEPVerrou == cFalse)
	{
		EEPMsg.pBuffer = EEPTable;
		EEPMsg.Lng = cEEPTaille;
		DONLireB(EEPRefBufferES, EEPTable,NULL,NULL);
		RESEcrireDmdeMoficationTrame(EEPRefTrameIP ,cTrue);
		memcpy(EEPTable + Adr, pMsg->pBuffer, pMsg->Lng);
		RESEcrireDureeTrame(0, EEPRefFluxIP, cEEPDureeOctetWRITE*pMsg->Lng);
		RESEcrireTrameCourante(EEPRefFluxIP, 0, &EEPMsg);
		RESEmissionStd(cLDBChannelEep);
	}
	else
	{
		mLDBPCErreur("EEP : Detect an eeprom writing on an locked eeprom !");
	}
}

//==============================================================================
// DESCRIPTION : LDBReceive simulation
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
// LDBReceiveWithAddr Specifique
void EEPReception(tAddress Adr, tMsg * pMsg)
{
    EEPAdresse = Adr;
    pEEPRcvMsg = pMsg;
    RESEcrireDureeTrame(0, EEPRefFluxIC, cEEPDureeOctetREAD*pMsg->Lng);
    RESEcrireTrameCourante(EEPRefFluxIC, 0, &EEPMsg);
    RESReceptionStd(cLDBChannelEep);
}

//==============================================================================
// DESCRIPTION : Callback once the LDBReceive is complete
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
// CallBack de LDBReceiveWithAddr Specifique
void EEPCallBackReception(tAddress Adresse, tStatus Status)
{
     memcpy(pEEPRcvMsg->pBuffer, EEPTable + EEPAdresse , pEEPRcvMsg->Lng);
     DATEepCallBackRxWithAddr(EEPAdresse ,Status);
}

//==============================================================================
// DESCRIPTION : Callback once the LDBSend is complete
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
// CallBack de LDBSendWithAddr Specifique
void EEPCallBackEmission(tAddress Adresse, tStatus Status)
{
     DATEepCallBackTxWithAddr(EEPAdresse ,Status);
}

//==============================================================================
// DESCRIPTION : Simulates (inside LDBPC) the action of a control
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
// LDBControl Specifique
void EEPCallBackCtrl(tCtrl Ctrl)
{
    switch (Ctrl)
    {
    case cLDBEepLock:
        EEPVerrou = cTrue;
        break;
    case cLDBEepUnLock:
        EEPVerrou = cFalse;
        break;
#ifdef cLDBEepUnprotect
    case cLDBEepUnprotect:
        break;
#endif // cLDBEepUnprotect
    default:
        break;
    }
}


//==============================================================================
// DESCRIPTION : Callback from X-CAR when a control has been processed
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
// LDBControl callback. Call EEP callbacke xcept for unprotect cases
void EEPCallbackEndCtrl (tCtrl Ctrl, tStatus Status)
{
    switch (Ctrl)
    {
    case cLDBEepLock:
        EEPVerrou = cTrue;
        break;
    case cLDBEepUnLock:
        EEPVerrou = cFalse;
        break;
#ifdef cLDBEepUnprotect
    case cLDBEepUnprotect:
        if (EEPUnprotectCycleCount == 255U)
        {
            // Never unprotect so never call back
            return;
        }
        else if (EEPUnprotectCycleCount <= 1)
        {
            // Callback!
        }
        else
        {
            EEPUnprotectCycleCount--;
            return;
        }
        break;
#endif // cLDBEepUnprotect
    default:
        break;
    }
    DATEepCallBackEndCtrl (Ctrl, Status);
}



//==============================================================================
// DESCRIPTION : Environment init
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
// Initialisation du Eep
void EepInit(void)
{
    tCallBackCanal CallBackCanal;
    memset(&CallBackCanal,0,sizeof(tCallBackCanal));
    EEPMsg.pBuffer = EEPTable;
    EEPMsg.Lng = cEEPTaille;
#ifdef cLDBEepUnprotect
    EEPUnprotectCycleCount = 3U;// Delayed unprotect
#endif // cLDBEepUnprotect
    EEPVerrou = cFalse;

// Creation de la structure de Callback du canal Eep
    CallBackCanal.pCallBackCtrl           =   NULL;
    CallBackCanal.pCallBackEndCtrl        =   EEPCallbackEndCtrl;
    CallBackCanal.pCallBackTx             =   EEPCallBackEmission;
    CallBackCanal.pCallBackRx             =   EEPCallBackReception;
    CallBackCanal.pTxSpontWithAddr        =   NULL;
    CallBackCanal.NbTxSpont               =   0;
    CallBackCanal.pRxSpontWithAddr        =   NULL;
    CallBackCanal.NbRxSpont               =   0;

    // Creation du canal Eep
    RESCreerCanal(cLDBChannelEep, "Eep", &CallBackCanal, EEPCallBackCtrl, NULL);
    // RESEcrireFormat(cLDBChannelEep, cCodageMotorola );

    // Creation des flux
    RESCreerFluxI(&EEPRefFluxIP,cLDBChannelEep, cFluxIP, EEPEmission);
    RESCreerFluxI(&EEPRefFluxIC,cLDBChannelEep, cFluxIC, EEPReception);

    // Creation des trames et des donnees associées
    RESCreerTrameFI(&EEPRefTrameIP, EEPRefFluxIP, "Write", 0, cEEPTaille 
                    , cFluxIP,cEEPDureeOctetWRITE);
    RESCreerTrameFI(&EEPRefTrameIC, EEPRefFluxIC, "Read", 0,  cEEPTaille
                    , cFluxIC ,cEEPDureeOctetREAD);

    // Lecture des valeurs d'init
	EEPReadInitFile();

    RESCreerEntSorB(&EEPRefBufferES, EEPRefTrameIP, "Eeprom",  cEEPTaille*8 , EEPTableInit,  0 );
   
    RESAttacherDonnee(EEPRefBufferES, EEPRefTrameIC,  0 );

    // Creation des Controles
    RESCreerControleSor(NULL, cLDBChannelEep, "EEPVerrouille", cLDBEepLock, 0*(cTEMms/cLDBTick));
    RESCreerControleSor(NULL, cLDBChannelEep, "EEPDeverrouille", cLDBEepUnLock, 0*(cTEMms/cLDBTick));
    RESCreerControleSor(NULL, cLDBChannelEep, "EEPCheckWriteCompletion", cLDBEepCheckWriteCompletion, 0*(cTEMms/cLDBTick));

#ifdef cLDBEepUnprotect
    RESCreerControleSor(NULL, cLDBChannelEep, "EEPUnprotect", cLDBEepUnprotect, 1*(cTEMms/cLDBTick));
    DONCreerSortieV( NULL,  "EEPUnprotectIsUsed",	0x01U, 8U, "Eep" );
#else // cLDBEepUnprotect
    RESCreerControleSor(NULL, cLDBChannelEep, "EEPUnprotect", cLDBEepUnLock + 0x10U, 1*(cTEMms/cLDBTick));
    DONCreerSortieV( NULL,  "EEPUnprotectIsUsed",	0x00U, 8U, "Eep" );
#endif // cLDBEepUnprotect

}

//==============================================================================
// DESCRIPTION : EEP contents file reading
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
void EEPDecodeFile( char* FileName, U8* pBuff, U32 Size )
{
    FILE* pFile = fopen( FileName, "r" );
    assert( pFile != NULL );

	memset(pBuff,0xFF,Size); 

    int  Adresse = 0;
    char Mot[1024];
    enum {cInit,cLecture,cCommentaire} Etat = cInit;

    while( fscanf( pFile, "%s", &Mot ) != EOF )
	{ 
        switch( Etat )
        {
        case( cInit ) :
            assert( Mot[0] == '@'  );

            // Lire adresse
            sscanf( &Mot[1], "%x", &Adresse );
            assert(Adresse>=0);
            assert((U32)Adresse<Size);

            Etat = cLecture;
            break;

        case( cLecture ) :
            if( Mot[0] == '@'  )
            {
                // Detection d'une adresse
                sscanf( &Mot[1], "%x", &Adresse );
                assert(Adresse>=0);
                assert((U32)Adresse<Size);
            }
            else if( strcmp( Mot, "/*" ) == 0 )
            {
                // Detection d'un debut de commentaire
                Etat = cCommentaire;
            }
            else if( strncmp( Mot, "0x", 2 ) ==  0)
            {
                // Detection d'un octet en hexa
                int Byte;
                sscanf( &Mot[2], "%x", &Byte );

                assert((U32)Adresse<Size);
                pBuff[Adresse] = (U8)Byte;    
                Adresse ++;
            }
            else
            {
                // Detection d'un octet en decimal
                int Byte;
                sscanf( Mot, "%d", &Byte );

                assert((U32)Adresse<Size);
                pBuff[Adresse] = (U8)Byte;    
                Adresse ++;
            }
            break;

        case( cCommentaire ):
            if( strcmp( Mot, "*/" ) == 0 )
            {
                // Detection d'une fin de commentaire
                Etat = cLecture;
            }
            break;

        default :
            assert(0);
            break;
        }
	}

	fclose(pFile);
}

//==============================================================================
// DESCRIPTION : EEP init file reading
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
void EEPReadInitFile(void)
{
    char Buff[256];
    char* Str = Buff;
	BOOL bStatus = FALSE;
	CString NomFichier;
	// Title of the dialog box
	CString csTitle = _T(cTitle);
	// Filters Combobox
	CString csFilter = _T(cFilter);

	// TRUE for open
	CFileDialog filedlg(TRUE, NULL, ""
	, OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST
	, (LPCTSTR)csFilter, NULL);
	filedlg.m_ofn.lpstrTitle = (LPCTSTR)csTitle;

	#ifdef cInitialDir
	filedlg.m_ofn.lpstrInitialDir = _T(cInitialDir);
	#endif // cInitialDir

    strncpy( Buff,GetCommandLine(),sizeof(Buff));

    if( Str[0] == '"' )
    {
        Str++;
        while(Str[strlen(Str)-1] != '"') 
        {
          Str[strlen(Str)-1]=0;
        }
        Str[strlen(Str)-1]=0;
    }
	strcpy( &Str[ strlen(Str)-strlen(AfxGetAppName())-4], cEPPFileName);

	NomFichier = CString(Str);
		
	// Test if the file exist
	CFile file;
	if(file.Open(NomFichier,CFile::modeRead))
	{
		file.Close();
		bStatus = TRUE;
	}

	while(bStatus != TRUE)
	{
		// Open the dialog box
		if(filedlg.DoModal() == IDCANCEL)
		{
			if(AfxMessageBox("The eeprom initialization file will be not load.\n"
				"Would you continue ?",MB_YESNO) == IDNO)
			{
				return;
			}
		}

		// Get the file Name
		NomFichier = filedlg.GetPathName();

		if(!NomFichier.IsEmpty())
		{
			bStatus = TRUE;
		}
	}
	if(bStatus)
	{
		EEPDecodeFile(NomFichier.GetBuffer(0), EEPTableInit, cEEPTaille );
		NomFichier.ReleaseBuffer();
	}
}

#endif

