/*============================================================================
  Project ......................... STANDARD
  Component ....................... LDB_EEP
  File revision....................
  Last modification date ..........
  -------------------------------------------------------------------------
  Copyright ... This software is JCI property. Duplication or
                disclosure is prohibited without JCI written permission
  ------------------------------------------------------------------------- 

  - Macros, constants and types which are not exported are defined in 
    this file
  - Variables and functions which are not exported are defined in this 
    file with the static key word
  
  -------------------------------------------------------------------------
  Comments about the component (role, algorithm, structure, limitations,
           defined tasks and events...)
  - Role :

        M93C76 EEP Driver
  
  -------------------------------------------------------------------------
  ldb_eep.c file review : 

    See PVCS revision

  ==========================================================================*/

/*--------------------------------------------------------------------------
  Body Identification
  --------------------------------------------------------------------------*/
#define LDB_EEP   "LDB_EEP"

/*-------------------------------------------------------------------------
  Included files

  #include <system_file_name.h>
  #include "project_file_name.h"
  --------------------------------------------------------------------------*/
#include "ldb.h"
#include "ldb_har.h"
#include "ldb_spi.h"
#include "ldb_tim.h"
#include "ldb_eep.h"

/*--------------------------------------------------------------------------
  Local constants

  #define cConstantName   ((tType) ConstantValue)
  --------------------------------------------------------------------------*/

#define cEEPROMPageSize     ((U16)32)

// Instructions                                              // Example for the M93C76
#define cInstructionREAD    ((U8)0x06)    // OpCode = 0000 0110 Address
#define cInstructionWRITE   ((U8)0x05)    // OpCode = 0000 0101 Address
#define cInstructionEWEN    ((U8)0x04)    // OpCode = 0000 0100 11xx xxxx
#define cInstructionEWDS    ((U8)0x04)    // OpCode = 0000 0100 00xx xxxx
#define cInstructionERASE   ((U8)0x07)    // OpCode = 0000 0111 Address
#define cInstructionERAL    ((U8)0x04)    // OpCode = 0000 0100 10xx xxxx
#define cInstructionWRAL    ((U8)0x04)    // OpCode = 0000 0100 01xx xxxx

#define cInstructionEWENCompletion11BitsHigh  ((U8)0x07)
#define cInstructionEWENCompletion11BitsLow   ((U8)0xFF)
#define cInstructionEWENCompletion10BitsHigh  ((U8)0x03)
#define cInstructionEWENCompletion10BitsLow   ((U8)0xFF)
#define cInstructionEWENCompletion9BitsHigh   ((U8)0x01)
#define cInstructionEWENCompletion9BitsLow    ((U8)0xFF)
#define cInstructionEWENCompletion8Bits       ((U8)0xFF)
#define cInstructionEWENCompletion7Bits       ((U8)0x7F)
#define cInstructionEWENCompletion6Bits       ((U8)0x3F)

#define cInstructionEWDSCompletion11BitsHigh  ((U8)0x01)
#define cInstructionEWDSCompletion11BitsLow   ((U8)0xFF)
#define cInstructionEWDSCompletion10BitsHigh  ((U8)0x00)
#define cInstructionEWDSCompletion10BitsLow   ((U8)0xFF)
#define cInstructionEWDSCompletion9BitsHigh   ((U8)0x00)
#define cInstructionEWDSCompletion9BitsLow    ((U8)0x7F)
#define cInstructionEWDSCompletion8Bits       ((U8)0x3F)
#define cInstructionEWDSCompletion7Bits       ((U8)0x1F)
#define cInstructionEWDSCompletion6Bits       ((U8)0x0F)

//EEPROM size

#ifdef cLDBHarEep93Type_M93C06
  #define cNbByte 32
  #error "This eeprom type has never been tested"
#elif defined(cLDBHarEep93Type_M93C46)
  #define cNbByte 128
  #error "This eeprom type has never been tested"
#elif defined(cLDBHarEep93Type_M93C56)
  #define cNbByte 256
#elif defined(cLDBHarEep93Type_M93C66)
  #define cNbByte 512
#elif defined(cLDBHarEep93Type_M93C76)
  #define cNbByte 1024
#elif defined(cLDBHarEep93Type_M93C86)
  #define cNbByte 2048
#else
  #error "This eeprom type is not managed by this component"
#endif

#if (defined(cLDBHarEep93Org_8Bits))
#elif (defined(cLDBHarEep93Org_16Bits))
#else
  #error "The acces type is not defined (in LDB_HAR)"
#endif


/*--------------------------------------------------------------------------
  Local macros

  #define mMacroName   (MacroDefinition)
  --------------------------------------------------------------------------*/

//first temporization to ensure tCLSH
//second temporization to ensure tSHCH
#define mSelectEEPChip()    mLDBEepPutSPIInIdleMode();\
                            mLDBHarActiveWaitUs(1);\
                            mLDBHarWrite(cLDBHarEepCS,1);\
                            mLDBHarActiveWaitUs(1)

//temporization to ensure the CS = 0 validity (Tslsh and Tslch value)
//no need to wait tCLSL because its value is 0
#define mUnselectEEPChip()  mLDBHarWrite(cLDBHarEepCS,0);\
                            mLDBHarActiveWaitUs(1)

#define mReadEEPBusyState() mLDBHarRead(cLDBHarSpiSI)
  
/*--------------------------------------------------------------------------
  Local types

  struct  sStructureName { ... };
  union   uUnionName { ... };
  enum    eEnumerationName { ... };
  typedef Expression tTypeName;
  --------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------
  Local data

  static  tType   VariableName;
  static  tType*  pVariableName; 
  --------------------------------------------------------------------------*/

static  tAddress  WriteAddress;
static  BOOL  IsWriteProcessing;

/*--------------------------------------------------------------------------
  Constant local data

  static const tType  VariableName;
  --------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------
  Exported data

  tType   CMPVariableName;      (CMP: 3 characters to identify this component)
  tType*  pCMPVariableName;     (CMP: 3 characters to identify this component)
  --------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------
  Constant exported data
 
  const tType   CMPVariableName;(CMP: 3 characters to identify this component)
  --------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------
  Local function prototypes
  
  static tTypeRetour FunctionName(tTypeArgument1 ArgumentName1, ... );
  --------------------------------------------------------------------------*/

static BOOL IsWriteFinished (void);

/*============================================================================
  =========================== LOCAL FUNCTIONS ================================
  ==========================================================================*/

/*============================================================================
  DESCRIPTION : static BOOL IsWriteFinished(void)
            Check if write operation is finished
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
static BOOL IsWriteFinished(void)
{
  U8 StatusRegister;

  //  Select
  mSelectEEPChip();

  //Temporization to ensure the status validity (tSHQV value)
  mLDBHarActiveWaitUs(1);

  StatusRegister = mReadEEPBusyState();

  //  UnSelect
  mUnselectEEPChip();

  return( (StatusRegister == 1) );
}

/*============================================================================
  =========================== EXPORTED FUNCTIONS =============================
  ==========================================================================*/

/*============================================================================
  DESCRIPTION : void LDBEepInit(void)
              Initialize LDB Eep
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
MEM_TYPE void LDBEepInit(void)
{
  IsWriteProcessing = cFalse;
  mLDBEepSelectMemoryOrganization();
  mUnselectEEPChip();
}

/*============================================================================
  DESCRIPTION : LDBEepSendWithAddr
        Write pMsg->Lng bytes in eeprom
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
MEM_TYPE void  LDBEepSendWithAddr(tAddress Address,tMsg* pMsg)
{
  U8 u8Index;

  // check if the data size goes beyond the current EEPROM page
  mLIBassert( ((Address + pMsg->Lng) <= cNbByte) && 
      (((Address % cEEPROMPageSize) + pMsg->Lng) <= cEEPROMPageSize) );

  WriteAddress = Address;

  //  Select eep
  mSelectEEPChip();

  // send WRITE instruction
  mLDBEepSendBitsToSPI(cInstructionWRITE, 3);

  // send address
  #if (defined(cLDBHarEep93Type_M93C06) || defined(cLDBHarEep93Type_M93C46))
    {
      #if (defined(cLDBHarEep93Org_8Bits))
      {
        mLDBEepSendBitsToSPI((U8)WriteAddress,7);
      }
      #elif (defined(cLDBHarEep93Org_16Bits))
      {
        mLDBEepSendBitsToSPI((U8)(WriteAddress>>1),6);
      }
      #endif
    }
  #elif (defined(cLDBHarEep93Type_M93C56) || defined(cLDBHarEep93Type_M93C66))
    {
      #if (defined(cLDBHarEep93Org_8Bits))
      {
        mLDBEepSendBitsToSPI((U8)(WriteAddress >> 8),1);
        mLDBEepSendByteToSPI((U8)WriteAddress);
      }
      #elif (defined(cLDBHarEep93Org_16Bits))
      {
        mLDBEepSendByteToSPI((U8)(WriteAddress>>1));
      }
      #endif
    }
  #elif (defined(cLDBHarEep93Type_M93C76) || defined(cLDBHarEep93Type_M93C86))
    {
      #if (defined(cLDBHarEep93Org_8Bits))
      {
        mLDBEepSendBitsToSPI((U8)(WriteAddress >> 8),3);
        mLDBEepSendByteToSPI((U8)WriteAddress);
      }
      #elif (defined(cLDBHarEep93Org_16Bits))
      {
        mLDBEepSendBitsToSPI((U8)((WriteAddress>>1) >> 8),2);
        mLDBEepSendByteToSPI((U8)(WriteAddress>>1));
      }
      #endif
    }
  #endif

  // send datas
  #if (defined(cLDBHarEep93Org_8Bits))
    {
      mLDBEepSendByteToSPI(pMsg->pBuffer[0]);
    }
  #elif (defined(cLDBHarEep93Org_16Bits))
    {
      for (u8Index = 0; u8Index < pMsg->Lng; u8Index++)
      {
          mLDBEepSendByteToSPI(pMsg->pBuffer[u8Index]);
      }
    }
  #endif

  //  Unselect eep
  mLDBEepPutSPIInIdleMode();
  mUnselectEEPChip();

  IsWriteProcessing = cTrue;
}

/*============================================================================
  DESCRIPTION : LDBEepReceiveWithAddr
          Read pMsg->Lng bytes from eeprom
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
MEM_TYPE void  LDBEepReceiveWithAddr(tAddress Address,tMsg* pMsg)
{
  U8 u8Index;

  // check if the data size goes beyond the current EEPROM page
  mLIBassert( ((Address + pMsg->Lng) <= cNbByte) && 
      (((Address % cEEPROMPageSize) + pMsg->Lng) <= cEEPROMPageSize) );

  IsWriteProcessing = cFalse;

  //select eep
  mSelectEEPChip();

  // send READ instruction
  mLDBEepSendBitsToSPI(cInstructionREAD, 3);

  //send address
  #if (defined(cLDBHarEep93Type_M93C06) || defined(cLDBHarEep93Type_M93C46))
    {
      #if (defined(cLDBHarEep93Org_8Bits))
      {
        mLDBEepSendBitsToSPI((U8)Address,7);
      }
      #elif (defined(cLDBHarEep93Org_16Bits))
      {
        mLDBEepSendBitsToSPI((U8)(Address>>1),6);
      }
      #endif
    }
  #elif (defined(cLDBHarEep93Type_M93C56) || defined(cLDBHarEep93Type_M93C66))
    {
      #if (defined(cLDBHarEep93Org_8Bits))
      {
        mLDBEepSendBitsToSPI((U8)(Address >> 8),1);
        mLDBEepSendByteToSPI((U8)Address);
      }
      #elif (defined(cLDBHarEep93Org_16Bits))
      {
        mLDBEepSendByteToSPI((U8)(Address>>1));
      }
      #endif
    }
  #elif (defined(cLDBHarEep93Type_M93C76) || defined(cLDBHarEep93Type_M93C86))
    {
      #if (defined(cLDBHarEep93Org_8Bits))
      {
        mLDBEepSendBitsToSPI((U8)(Address >> 8),3);
        mLDBEepSendByteToSPI((U8)Address);
      }
      #elif (defined(cLDBHarEep93Org_16Bits))
      {
        mLDBEepSendBitsToSPI((U8)((Address>>1) >> 8),2);
        mLDBEepSendByteToSPI((U8)(Address>>1));
      }
      #endif
    }
  #endif

  //Received data
  for (u8Index = 0; u8Index < pMsg->Lng; u8Index++)
  {
      pMsg->pBuffer[u8Index] = mLDBEepReadByteFromSPI();
  }

  //unselect eep
  mLDBEepPutSPIInIdleMode();
  mUnselectEEPChip();

  DATEepCallBackRxWithAddr(Address, cLDBCorrect);
}

/*============================================================================
  DESCRIPTION :void LDBEepControl(tCtrl Ctrl)
            Lock and unlock eeprom
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
MEM_TYPE void LDBEepControl(tCtrl Ctrl)
{

  //  Command evaluation
  switch(Ctrl)
  {
    case cLDBEepUnLock:
      //  Select eep
      mSelectEEPChip();
      // send EWEN instruction
      mLDBEepSendBitsToSPI(cInstructionEWEN, 3);

      #if (defined(cLDBHarEep93Type_M93C06) || defined(cLDBHarEep93Type_M93C46))
        {
          #if (defined(cLDBHarEep93Org_8Bits))
          {
            mLDBEepSendBitsToSPI(cInstructionEWENCompletion7Bits, 7);
          }
          #elif (defined(cLDBHarEep93Org_16Bits))
          {
            mLDBEepSendBitsToSPI(cInstructionEWENCompletion6Bits, 6);
          }
          #endif
        }
      #elif (defined(cLDBHarEep93Type_M93C56) || defined(cLDBHarEep93Type_M93C66))
        {
          #if (defined(cLDBHarEep93Org_8Bits))
          {
            mLDBEepSendBitsToSPI(cInstructionEWENCompletion9BitsHigh, 1);
            mLDBEepSendByteToSPI(cInstructionEWENCompletion9BitsLow);
          }
          #elif (defined(cLDBHarEep93Org_16Bits))
          {
            mLDBEepSendByteToSPI(cInstructionEWENCompletion8Bits);
          }
          #endif
        }
      #elif (defined(cLDBHarEep93Type_M93C76) || defined(cLDBHarEep93Type_M93C86))
        {
          #if (defined(cLDBHarEep93Org_8Bits))
          {
            mLDBEepSendBitsToSPI(cInstructionEWENCompletion11BitsHigh, 3);
            mLDBEepSendByteToSPI(cInstructionEWENCompletion11BitsLow);
          }
          #elif (defined(cLDBHarEep93Org_16Bits))
          {
            mLDBEepSendBitsToSPI(cInstructionEWENCompletion10BitsHigh, 2);
            mLDBEepSendByteToSPI(cInstructionEWENCompletion10BitsLow);
          }
          #endif
        }
      #endif

      //  Unselect eep
      mLDBEepPutSPIInIdleMode();
      mUnselectEEPChip();
      break;
    case cLDBEepLock:
      //  Select eep
      mSelectEEPChip();
      // send EWDS instruction
      mLDBEepSendBitsToSPI(cInstructionEWDS, 3);

      #if (defined(cLDBHarEep93Type_M93C06) || defined(cLDBHarEep93Type_M93C46))
        {
          #if (defined(cLDBHarEep93Org_8Bits))
          {
            mLDBEepSendBitsToSPI(cInstructionEWDSCompletion7Bits, 7);
          }
          #elif (defined(cLDBHarEep93Org_16Bits))
          {
            mLDBEepSendBitsToSPI(cInstructionEWDSCompletion6Bits, 6);
          }
          #endif
        }
      #elif (defined(cLDBHarEep93Type_M93C56) || defined(cLDBHarEep93Type_M93C66))
        {
          #if (defined(cLDBHarEep93Org_8Bits))
          {
            mLDBEepSendBitsToSPI(cInstructionEWDSCompletion9BitsHigh, 1);
            mLDBEepSendByteToSPI(cInstructionEWDSCompletion9BitsLow);
          }
          #elif (defined(cLDBHarEep93Org_16Bits))
          {
            mLDBEepSendByteToSPI(cInstructionEWDSCompletion8Bits);
          }
          #endif
        }
      #elif (defined(cLDBHarEep93Type_M93C76) || defined(cLDBHarEep93Type_M93C86))
        {
          #if (defined(cLDBHarEep93Org_8Bits))
          {
            mLDBEepSendBitsToSPI(cInstructionEWDSCompletion11BitsHigh, 3);
            mLDBEepSendByteToSPI(cInstructionEWDSCompletion11BitsLow);
          }
          #elif (defined(cLDBHarEep93Org_16Bits))
          {
            mLDBEepSendBitsToSPI(cInstructionEWDSCompletion10BitsHigh, 2);
            mLDBEepSendByteToSPI(cInstructionEWDSCompletion10BitsLow);
          }
          #endif
        }
      #endif

      //  Unselect eep
      mLDBEepPutSPIInIdleMode();
      mUnselectEEPChip();
      break;
    case cLDBEepCheckWriteCompletion:
      if( IsWriteProcessing != cFalse )
      {
        // There is no timeout in the LDB.
        // The timeout is managed by the DAT Layer
        if ( IsWriteFinished() == cTrue )
        {
          // If the write operation is finished
          DATEepCallBackTxWithAddr(WriteAddress, cLDBCorrect);
          IsWriteProcessing = cFalse;
        }
      }
      break;
    default :
      mLIBassert(cFalse);
      break;

  }
  DATEepCallBackEndCtrl(Ctrl,cLDBCorrect);

}
