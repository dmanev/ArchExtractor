#ifndef _QAC_
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
// Component:    LAP_DVP.C
// -----------------------------------------------------------------------------
// $Date:   Apr 22 2009 15:33:08  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_DVP/LAP_DVP.C-arc  $
// $Revision:   1.2  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_DVP/LAP_DVP.C-arc  $
// 
//    Rev 1.2   Apr 22 2009 15:33:08   adzhelp
// Cm003128: MEM_TYPE attribute added to service functions.
// RF Test results added. DIAG_DRIVER updated
// 
//    Rev 1.1   20 Mar 2009 18:13:30   akodzhh
// Cm003128 - 2 bytes memmory address - use U16 instead of U32, RF test.
// 
//    Rev 1.0   12 Mar 2009 15:47:34   akodzhh
// Initial revision.
//******************************************************************************
#endif

//------------------------------------------------------------------------------
// Body Identification
//------------------------------------------------------------------------------
#define lap_dvp   "lap_dvp"

//------------------------------------------------------------------------------
//  Included files
//
// #include <system_file_name.h>
// #include "project_file_name.h"
//------------------------------------------------------------------------------

#include "lib.h"
#include "tos.h"
#include "dat.h"

#include "lap_kwp.h"
#include "lap_dvp.h"

//------------------------------------------------------------------------------
// Local constants
//
// #define cConstantName   ((tType) ConstantValue)
//------------------------------------------------------------------------------
#define cDVPNbFunctionControled         ((U8)2UL)

/////////////////////////////////////////////////////
// constantes for StartRoutineByLocalIdentifier service
/////////////////////////////////////////////////////
#define cSRBLIDReq_Lght                       ((U8) 0x03)
#define cSRBLIDReqRW_Lght                     ((U8) 0x08)
#define cSRBLIDResp_Lght                      ((U8) 0x03)
// SRBLI - Local Identifiers suported
#define cLocalId_Write                        ((U8) 0xFA )
#define cLocalId_Read                         ((U8) 0xFB )
#define cLocalId_TestRF                       ((U8) 0xFF )
#define cLocalId_TestEraseEepromDefault       ((U8) 0xFE )

// SRBLI Read/Write Memory type
#define    cDirectAccessEeprom                ((U8) 0x05 )
#define    cDirectAccessRam                   ((U8) 0x01 )
#define    cDirectAccessRom                   ((U8) 0x03 )

// SRBLI option byte 
#define cStartRoutine                         ((U8) 0x00 )
#define cReadRoutineStatus                    ((U8) 0x01 )


// Indice in DVPTableStatutFunction table
#define cRoutineWrite                         ((U8) 0x00 )
#define cRoutineRead                          ((U8) 0x01 )

#define cStartRoutine                         ((U8) 0x00 )
#define cReadRoutineStatus                    ((U8) 0x01 )

#define cMinRam1AdrMemory                     ((U16) 0xE800 ) 
#define cMaxRam1AdrMemory                     ((U16) 0xF7FF )
#define cMinRam2AdrMemory                     ((U16) 0xFB00 ) 
#define cMaxRam2AdrMemory                     ((U16) 0xFEDF )

#define cMinRomAdrMemory                      (0x0000UL )
#define cMaxRomAdrMemory                      ((U16) 0xBFFF )

#define cHeaderLgth  (U8)4
#define cMaxReadBufferSize   (U8)(( cDATKwpTxBufferSize-cHeaderLgth ) - cSRBLIDResp_Lght ) 


/////////////////////////////////////////////////////
// constants for ReadDataByLocalIdentifier (RDBLID)
/////////////////////////////////////////////////////
#define cBankNumber                             ((U8)cNbDbk + cNbSbk)

#define cRDBLIDReq_Lgth                         ((U8)2)

#define cRDBLID_EepromErrorID                   ((U8)0xF0)
#define cRDBLIDAns_EepromError_Lgth             ((U8)11)


//------------------------------------------------------------------------------
// Local macros
//
// #define mMacroName   (MacroDefinition)
//------------------------------------------------------------------------------
#define mDVPInitDvpTabIdentifierServiceSupported()  \
{                                                   \
  cLAPKwpIdStartRoutineByLocalIdentifier,              \
  cLAPKwpIdStopRoutineByLocalIdentifier,               \
  cLAPKwpIdReadDataByLocalIdentifier                   \
}

#define mDVPInitDvpTabServiceSupported()          \
{                                                 \
  LAPDvpTreatStartRoutineByLocalIdentifierService,    \
  LAPDvpTreatStopRoutineByLocalIdentifierService,     \
  LAPDvpTreatReadDataByLocalIdentifierService         \
}

// RAM/ROM direct access
#define mIsValidRamAddress(Address, DataLgth)     \
  (BOOL)( (((Address) >= cMinRam1AdrMemory)&&((Address)+(U16)(DataLgth) <= cMaxRam1AdrMemory))      \
        ||(((Address) >= cMinRam2AdrMemory)&&((Address)+(U16)(DataLgth) <= cMaxRam2AdrMemory)))

#if (cMinRomAdrMemory > 0)
#define mIsValidRomAddress(Address, DataLgth)     \
  (BOOL)( ((Address) >= cMinRomAdrMemory)&&((Address) + (U16)(DataLgth) <= cMaxRomAdrMemory))
#else
#define mIsValidRomAddress(Address, DataLgth)     \
  (BOOL)((Address) + (U16)(DataLgth) <= cMaxRomAdrMemory)
#endif


//------------------------------------------------------------------------------
// Local types
//
// struct  sStructureName { ... };
// union   uUnionName { ... };
// enum    eEnumerationName { ... };
// typedef Expression    tTypeName;
//------------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// Local data
//
// static  tType   u8VariableName;  
// static  tType*  pu8VariableName; 
//------------------------------------------------------------------------------

static U8    u8BufferSizeInByte;
static U8    u8TypeOfMemory;
static BOOL  bWritingIsDone;

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
static U8    DVPTableStatutFunction[cDVPNbFunctionControled];

//------------------------------------------------------------------------------
// Constant exported data
//
//             (LAY: 3 characters to identify the layer)
//             (Cmp: 3 characters to identify this component)
// 
// const tType   LAYCmpVariableName;
//------------------------------------------------------------------------------
const U8 TabIdentifierServiceSupportedInDvpSession[cNbServicesSupportedInDVP] =
          mDVPInitDvpTabIdentifierServiceSupported();

const tLAPKwpServiceFunction TabServiceSupportedInDvpSession[cNbServicesSupportedInDVP] =
          mDVPInitDvpTabServiceSupported();

//------------------------------------------------------------------------------
// Local function prototypes
// 
// static tTypeRetour FunctionName(tTypeArgument1 ArgumentName1, ... );
//------------------------------------------------------------------------------

//==============================================================================
//=========================== LOCAL FUNCTIONS ==================================
//==============================================================================

//============================================================================
//  DESCRIPTION :
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//  ==========================================================================
static MEM_TYPE void StatusRequest(void)
{
    U8  u8Access;
    U8  u8Index;

    if (LAPKwpReadDiagnosticRequest(1) == cLocalId_Read)
    {
        u8Access=cRoutineRead;
    }
    else
    {
        u8Access=cRoutineWrite;
    }

    if ( (mDATRead(U8Bit,DATDeaActionIsFinished,Default) == cTrue) && 
         (u8TypeOfMemory == cDirectAccessEeprom))
    {        
        // Preparation réponse positive
        DVPTableStatutFunction[u8Access]=cLAPKwpRoutineTerminatedOK;
        if (u8Access == cRoutineWrite)
        {
            if (mDATRead(U8Bit,DATDeaWriteIsOk,Default) == cFalse)
            {
                DVPTableStatutFunction[u8Access]=cLAPKwpRoutineTerminatedNOK;
            }
            LAPKwpPreparePositiveResponse(3);
        }
        else
        {
            for (u8Index=0;u8Index<u8BufferSizeInByte;u8Index++)
            {
                LAPKwpWriteDiagnosticResponse(3+u8Index,(mDATReadBuffer(DATDeaBufferU8Bit,u8Index, Default)));
            } 
            LAPKwpPreparePositiveResponse((U8)(3+u8BufferSizeInByte));
        }
    }
    else
    {
        LAPKwpPreparePositiveResponse(3);
    }
    LAPKwpWriteDiagnosticResponse(1,LAPKwpReadDiagnosticRequest(1));
    LAPKwpWriteDiagnosticResponse(2,DVPTableStatutFunction[u8Access]);

}


//============================================================================
//  =========================== EXPORTED FUNCTIONS =============================
//  ==========================================================================
//============================================================================
//  DESCRIPTION :
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//============================================================================
MEM_TYPE void LAPDvpTreatReadDataByLocalIdentifierService(void)
{
    U8  u8RequestStatusL;
    U8  u8IndexL;
    U8  ResponseLength ;
  
    u8RequestStatusL = cLAPKwpServiceIsCorrect;
    
    if(  (mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cRDBLIDReq_Lgth)
       &&(LAPKwpReadDiagnosticRequest(1) == cRDBLID_EepromErrorID) ) 
    {
        for (u8IndexL=0; u8IndexL<cBankNumber; u8IndexL++)
        {
           LAPKwpWriteDiagnosticResponse(2+u8IndexL,mDATReadTable(U8Bit,EEPErrorTable, u8IndexL, Default));
        }
        ResponseLength = cRDBLIDAns_EepromError_Lgth;  
    }
    else
    {
        u8RequestStatusL = cLAPKwpInvalidFormat;
    }

    if(u8RequestStatusL == cLAPKwpServiceIsCorrect)
    {
        LAPKwpWriteDiagnosticResponse(1,LAPKwpReadDiagnosticRequest(1));
        LAPKwpPreparePositiveResponse(ResponseLength);
    }
    else
    {
        LAPKwpPrepareNegativeResponse(u8RequestStatusL);
    }
    LAPKwpSetServiceIsFinished();

}

//============================================================================
//  DESCRIPTION :
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//============================================================================
MEM_TYPE void LAPDvpTreatStartRoutineByLocalIdentifierService(void)
{
  U16   u16AddressMemory;
  U32   u8Index;
  U8    u8Access;
  U8    u8RequestStatus;
  
  u8RequestStatus = cLAPKwpServiceIsCorrect;
  
    switch(LAPKwpReadDiagnosticRequest(1))
    {
        case cLocalId_TestRF:
        
        if(  (LAPKwpReadDiagnosticRequest(2) == cReadRoutineStatus)
           &&(mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cSRBLIDReq_Lght))
        {
            for(u8Index = 3; u8Index < 9; u8Index++)
            {
                LAPKwpWriteDiagnosticResponse(3,0x00);
            }
            // Read the
            LAPKwpWriteDiagnosticResponse(1,cLocalId_TestRF);
            LAPKwpWriteDiagnosticResponse(2,cLAPKwpRoutineInProgress);

            // Number of Wake up received by the BCM
                        LAPKwpWriteDiagnosticResponse(3,mDATRead(U8Bit, DATRfNbWakeUpBlocksReceived, Default));
                        // Number of RC bloc received by the BCM
                        LAPKwpWriteDiagnosticResponse(4,mDATRead(U8Bit, DATRfNbRCBlocksReceived, Default));
                        // Number of RC bloc received with the data defined in DAT_RFp.h by the BCM
                        LAPKwpWriteDiagnosticResponse(5,mDATRead(U8Bit, DATRfNbRCBlocksReceivedAndOK, Default));
            
            // PDO value in milli-volt
            LAPKwpWriteDiagnosticResponse(6, (U8)((mDATRead(U16Bit, PDOInMilliVolt, Immediate) & 0xFF00)  >> 8));
            LAPKwpWriteDiagnosticResponse(7, (U8)( mDATRead(U16Bit, PDOInMilliVolt, Immediate) & 0x00FF)); 
            /*
            // Number of SI bloc received by the BCM (contents not verified)
                        LAPKwpWriteDiagnosticResponse(8,mDATRead(U8Bit, DATRfNbSIBlocksReceived, Default));*/
            

            LAPKwpPreparePositiveResponse((U8)(9));
        }  
        else if(  (LAPKwpReadDiagnosticRequest(2) == cStartRoutine)
                &&(mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cSRBLIDReq_Lght))
        {
            // Launch the RF test
            mDATControl(Rf, InitializeRFTest);
            LAPKwpWriteDiagnosticResponse(1,cLocalId_TestRF);
            LAPKwpWriteDiagnosticResponse(2,cLAPKwpRoutineInProgress);
            LAPKwpPreparePositiveResponse(cSRBLIDResp_Lght);
        }
        else
        {
            u8RequestStatus = cLAPKwpInvalidFormat;
        }
        break;
    

    case cLocalId_TestEraseEepromDefault:
     
        if (  (LAPKwpReadDiagnosticRequest(2) == cReadRoutineStatus)
           &&(mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cSRBLIDReq_Lght))
        {
            LAPKwpWriteDiagnosticResponse(1,cLocalId_TestEraseEepromDefault);
            LAPKwpWriteDiagnosticResponse(2,cLAPKwpRoutineTerminatedOK);
            LAPKwpPreparePositiveResponse(cSRBLIDResp_Lght);
        }  
        else if(  (LAPKwpReadDiagnosticRequest(2) == cStartRoutine)
                &&(mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cSRBLIDReq_Lght))
        {
            for (u8Index=0; u8Index<cBankNumber; u8Index++)
            {
                mDATWriteTable(U8Bit, EEPErrorTable, u8Index, 0x00, Default);
            }
            LAPKwpWriteDiagnosticResponse(1,cLocalId_TestEraseEepromDefault);
            LAPKwpWriteDiagnosticResponse(2,cLAPKwpRoutineInProgress);
            LAPKwpPreparePositiveResponse(cSRBLIDResp_Lght);
        }
        else
        {
            u8RequestStatus = cLAPKwpInvalidFormat;
        }
        break;

    case cLocalId_Read:

        if (  (LAPKwpReadDiagnosticRequest(2) == cReadRoutineStatus)
           &&(mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cSRBLIDReq_Lght))
        {
            // Request of the routine Status
            StatusRequest();
        }
        else if (  (LAPKwpReadDiagnosticRequest(2) == cStartRoutine)
                 &&(mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cSRBLIDReqRW_Lght)
                 &&(LAPKwpReadDiagnosticRequest(4)==0x00)) // address MSB
        {
            u8TypeOfMemory = LAPKwpReadDiagnosticRequest(3);
            u16AddressMemory = ((U16)(LAPKwpReadDiagnosticRequest(5))<<8) + \
                                (U16)(LAPKwpReadDiagnosticRequest(6));
            u8BufferSizeInByte = LAPKwpReadDiagnosticRequest(7);

            
            if (  (u8TypeOfMemory == cDirectAccessEeprom) 
                &&(u8BufferSizeInByte != 0)&&(u8BufferSizeInByte <= cDATDeaMaxByte)
                &&((U16)(u8BufferSizeInByte+u16AddressMemory)<=cDATDeaSizeEeprom)  
                &&((u16AddressMemory&0x01) == 0)&&((u8BufferSizeInByte&0x01) == 0))
            { 
                if(mDATRead(U8Bit,DATDeaActionIsFinished,Default) == cTrue)
                {
                    u8Access = cRoutineRead;
                    DVPTableStatutFunction[u8Access]=cLAPKwpRoutineInProgress;
                    mDATWrite(U8Bit, DATDeaSizeBufferInByte, u8BufferSizeInByte, Default);
                    mDATWrite(U16Bit, DATDeaAddressInByte, u16AddressMemory, Default);

                    mDATControl(DATDea, StartReadEepromByAddress);

                    LAPKwpWriteDiagnosticResponse(1,LAPKwpReadDiagnosticRequest(1));
                    LAPKwpWriteDiagnosticResponse(2,DVPTableStatutFunction[u8Access]);
                    LAPKwpPreparePositiveResponse(3);
                }
                else
                {
                    u8RequestStatus = cLAPKwpConditionNotCorrect;
                }

            }
            else if(  ( ((u8TypeOfMemory == cDirectAccessRam)&&
                          mIsValidRamAddress(u16AddressMemory,u8BufferSizeInByte))
                       ||
                        ((u8TypeOfMemory == cDirectAccessRom)&&
                          mIsValidRomAddress(u16AddressMemory,u8BufferSizeInByte)) )
                    &&(u8BufferSizeInByte <= cMaxReadBufferSize))
            {
                u8Access = cRoutineRead;
                // Double cast needed because CPU has 16-bit address field
                mLIBmemcpy(&DATKwpTxBuffer[6],(U8*)u16AddressMemory, u8BufferSizeInByte);
                LAPKwpPreparePositiveResponse((U8) (3 + u8BufferSizeInByte));

                DVPTableStatutFunction[u8Access] = cLAPKwpRoutineTerminatedOK;
                LAPKwpWriteDiagnosticResponse(1,LAPKwpReadDiagnosticRequest(1));
                LAPKwpWriteDiagnosticResponse(2,DVPTableStatutFunction[u8Access]);
            }
            else
            {
                // Others memories no treated
                u8RequestStatus = cLAPKwpInvalidFormat;
            }
        }
        else
        {
            u8RequestStatus = cLAPKwpInvalidFormat;
        }
        break;

    case cLocalId_Write:
        
        if (  (LAPKwpReadDiagnosticRequest(2) == cReadRoutineStatus)
            &&(mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cSRBLIDReq_Lght))
        {
            // Request of the routine Status
            StatusRequest();
        }
        else if( (LAPKwpReadDiagnosticRequest(2) == cStartRoutine)
               &&(mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == (cSRBLIDReqRW_Lght + LAPKwpReadDiagnosticRequest(7)))
               &&(LAPKwpReadDiagnosticRequest(4)==0x00)) // address MSB
        {
            u8TypeOfMemory  =  LAPKwpReadDiagnosticRequest(3);
            u16AddressMemory = ((U16)(LAPKwpReadDiagnosticRequest(5))<<8) + \
                                (U16)(LAPKwpReadDiagnosticRequest(6));
            u8BufferSizeInByte = LAPKwpReadDiagnosticRequest(7);

            if (  (u8TypeOfMemory == cDirectAccessEeprom)
                &&( mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == (cSRBLIDReqRW_Lght + u8BufferSizeInByte)) 
                &&(u8BufferSizeInByte != 0)&&(u8BufferSizeInByte <= cDATDeaMaxByte)
                &&((U16)(u8BufferSizeInByte+u16AddressMemory)<=cDATDeaSizeEeprom)  
                &&((u16AddressMemory&0x01) == 0)&&((u8BufferSizeInByte&0x01) == 0))
            { 
                
                if(mDATRead(U8Bit,DATDeaActionIsFinished,Default) == cTrue)
                {
                    u8Access = cRoutineWrite;
                    DVPTableStatutFunction[u8Access]=cLAPKwpRoutineInProgress;
                    mDATWrite (U8Bit, DATDeaSizeBufferInByte, u8BufferSizeInByte, Default);
                    mDATWrite  (U16Bit, DATDeaAddressInByte, u16AddressMemory, Default);

                    for (u8Index=0;u8Index<u8BufferSizeInByte;u8Index++)
                    {
                        mDATWriteBuffer(DATDeaBufferU8Bit,u8Index, LAPKwpReadDiagnosticRequest (8+u8Index), Default);
                    }
                    mDATControl (DATDea, StartWriteEepromByAddress);
                    bWritingIsDone = cTrue;
                }
                else
                {
                    u8RequestStatus = cLAPKwpConditionNotCorrect;
                }
                
                LAPKwpWriteDiagnosticResponse(1,LAPKwpReadDiagnosticRequest(1));
                LAPKwpWriteDiagnosticResponse(2,DVPTableStatutFunction[u8Access]);
                LAPKwpPreparePositiveResponse(3);
            }
            else if(  (u8TypeOfMemory == cDirectAccessRam)
                    && mIsValidRamAddress(u16AddressMemory,u8BufferSizeInByte))
            {
                u8Access = cRoutineWrite;
                // Double cast needed because CPU has 16-bit address field
                mLIBmemcpy((U8*)u16AddressMemory,&DATKwpRxBuffer[11], u8BufferSizeInByte); 

                DVPTableStatutFunction[u8Access] = cLAPKwpRoutineTerminatedOK;               
                LAPKwpPreparePositiveResponse((U8)3);
                LAPKwpWriteDiagnosticResponse(1,LAPKwpReadDiagnosticRequest(1));
                LAPKwpWriteDiagnosticResponse(2,DVPTableStatutFunction[u8Access]);
            }
            else
            {
                // Others memories no treated
                u8RequestStatus = cLAPKwpInvalidFormat;
            }
        }
        else    
        {
            u8RequestStatus = cLAPKwpInvalidFormat;
        }
        break;

    default:
        u8RequestStatus = cLAPKwpInvalidFormat;
        break;
    }


    if (u8RequestStatus != cLAPKwpServiceIsCorrect)
    {
        // Prepare Reponse negative : Format Invalide
        LAPKwpPrepareNegativeResponse(u8RequestStatus);
    }    
    LAPKwpSetServiceIsFinished();

}
//============================================================================
//  DESCRIPTION :
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//============================================================================
MEM_TYPE void LAPDvpTreatStopRoutineByLocalIdentifierService(void)
{
   LAPKwpSetServiceIsFinished();
}

//============================================================================
//  DESCRIPTION :
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//============================================================================
MEM_TYPE void LAPDvpInitSession(void)
{
    // init des fonctions controlees en test fin chaine
    mLIBmemset(DVPTableStatutFunction, cLAPKwpRoutineNotActivated, cDVPNbFunctionControled);

    bWritingIsDone = cFalse;
}
//============================================================================
//  DESCRIPTION :
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :  none
// 
//  DESIGN INFORMATION :  refer to Detailed Design Document
//============================================================================
MEM_TYPE void LAPDvpCloseSession(void)
{
    // Reset when the frame is sent
    if (bWritingIsDone == cTrue)
    {
        mDATControl(Cpu, Reset);
    }
}

