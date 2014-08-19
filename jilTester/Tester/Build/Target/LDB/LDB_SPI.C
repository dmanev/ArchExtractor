/*============================================================================
  Project ......................... STANDARD
  Component ....................... ldb_spi.c
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
  
  -------------------------------------------------------------------------
  ldb_spi.c file review : 

    See PVCS revision

  ==========================================================================*/

/*--------------------------------------------------------------------------
  Body Identification
  --------------------------------------------------------------------------*/
#define ldb_spi   "ldb_spi"

/*-------------------------------------------------------------------------
  Included files

  #include <system_file_name.h>
  #include "project_file_name.h"
  --------------------------------------------------------------------------*/
#include "ldb.h"
#include "ldb_har.h"
#include "ldb_spi.h"

/*--------------------------------------------------------------------------
  Local constants

  #define cConstantName   ((tType) ConstantValue)
  --------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------
  Local macros

  #define mMacroName   (MacroDefinition)
  --------------------------------------------------------------------------*/
#define mSetSckHigh()       mLDBHarWrite(cLDBHarSpiSCK,1)
#define mSetSckLow()        mLDBHarWrite(cLDBHarSpiSCK,0)

#define mReadDin()          mLDBHarRead(cLDBHarSpiSI)
#define mSetDoutHigh()      mLDBHarWrite(cLDBHarSpiSO,1)
#define mSetDoutLow()       mLDBHarWrite(cLDBHarSpiSO,0)

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

/*--------------------------------------------------------------------------
  Constant local data

  static const tType  VariableName;
  --------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------
  Exported data

  tType   CNLVariableName;      (CNL: 3 characters to identify this component)
  tType*  pCNLVariableName;     (CNL: 3 characters to identify this component)
  --------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------
  Constant exported data
 
  const tType   CNLVariableName;(CNL: 3 characters to identify this component)
  --------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------
  Local function prototypes
  
  static tTypeRetour FunctionName(tTypeArgument1 ArgumentName1, ... );
  --------------------------------------------------------------------------*/

/*============================================================================
  =========================== LOCAL FUNCTIONS ================================
  ==========================================================================*/

/*============================================================================
  DESCRIPTION :
  
  PARAMETERS (Type,Name,Min,Max) :   none

  RETURN VALUE :   none
 
  DESIGN INFORMATION :   refer to Detailed Design Document
  ==========================================================================*/
//static type FunctionName(...)

/*============================================================================
  =========================== EXPORTED FUNCTIONS =============================
  ==========================================================================*/
/*============================================================================
  DESCRIPTION :void LDBSpiInit(void)
                Init of the LDB layer
  
  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE :  none
 
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void LDBSpiInit(void)
{
#ifndef cLIBStkCpu_NecV850FxDxSx3
    mLDBHarConfig(cLDBHarSpiSO,cLDBHarOutput);
    mLDBHarConfig(cLDBHarSpiSCK,cLDBHarOutput);

    mLDBHarWrite(cLDBHarSpiSCK,cLDBSpiSckLevelInIdleMode);
    mLDBHarWrite(cLDBHarSpiSO,cLDBSpiSckLevelInIdleMode);
#else
    mLDBHarWrite(cLDBHarSpiSO,cLDBSpiSckLevelInIdleMode);
    mLDBHarConfig(cLDBHarSpiSO,cLDBHarOutput);

    mLDBHarWrite(cLDBHarSpiSCK,cLDBSpiSckLevelInIdleMode);
    mLDBHarConfig(cLDBHarSpiSCK,cLDBHarOutput);
#endif
}

#ifdef LDBSPI_FORMAT_LR_USED
/*============================================================================
  DESCRIPTION :void LDBSpiLRSendBits(U8 DataByte )
                Write a bit on the SPI bus

  PARAMETERS (Type,Name,Min,Max) :  
      - Data: Byte to write on SPI bus

  RETURN VALUE : none

  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void LDBSpiLRSendBits(U8 DataByte,U8 NbBits)
{
    U8 BitIndex;
    U8 Data;
    U8 DataMask;

    Data = DataByte;
    DataMask = (((U8)1)<<(NbBits-1));
    for(BitIndex = 0; BitIndex < NbBits; BitIndex++)
    {
        //  Clock edge signal for set data
        mSetSckLow();

        // Write data
        if ( (Data & DataMask) == DataMask)
        {
            mSetDoutHigh();
        }
        else
        {
            mSetDoutLow();
        }
        Data = Data<<1;

        //Temporization to ensure tDVCH and tCL
    #ifdef cLDBHarMicro78K0_F0536
       // No need of temporization: computations take time > 1 us
    #else
        mLDBHarActiveWaitUs(1);
    #endif

        //  Clock edge signal for sampling
        mSetSckHigh();
        //Temporization to ensure tCHDX and tCH
    #ifdef cLDBHarMicro78K0_F0536
        // No need of temporization: computations take time > 1 us
    #else
        mLDBHarActiveWaitUs(1);
    #endif
    }

    // Make sure to leave the SPI bus with the output pin in low state
    mSetDoutLow();
}

/*============================================================================
  DESCRIPTION :void LDBSpiLRReceiveBits(void )
                Read a bit on the SPI bus

  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE : byte read on the bus

  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
U8 LDBSpiLRReceiveBits(U8 NbBits)
{
    U8 ByteValue = 0;
    U8 BitIndex;

	// Fix the SPI bus output into the low state
    mSetDoutLow();

#ifndef cLIBStkEepType_STM93Cx6
    for(BitIndex = 0; BitIndex < NbBits; BitIndex++)
    {
        //  Clock edge signal for set data
        mSetSckLow();
        //Temporization to ensure tCLQV and tCL
        mLDBHarActiveWaitUs(1);
        //  Clock edge signal for sampling
        mSetSckHigh();
        //  Read bit
        ByteValue <<= 1;
        ByteValue |= mReadDin();
        //Temporization to ensure tCH
        mLDBHarActiveWaitUs(1);
    }
#else
    for(BitIndex = 0; BitIndex < NbBits; BitIndex++)
    {
        //  Clock to low
        mSetSckLow();
        //Temporization to ensure tCL
    #ifdef cLDBHarMicro78K0_F0536
        mLDBRegNop();
        mLDBRegNop();
        mLDBRegNop(); // 5 NOPs produce a duration of 1 us for low clock pulse 
        mLDBRegNop(); // measured on target
        mLDBRegNop();
    #else
        mLDBHarActiveWaitUs(1);
    #endif
        //  Clock to low
        mSetSckHigh();
        //Temporization to ensure tCH and tCHQV
    #ifdef cLDBHarMicro78K0_F0536
        // No need of temporization: computations take time > 1 us
    #else
        mLDBHarActiveWaitUs(1);
    #endif
        //  Read bit
        ByteValue <<= 1;
        ByteValue |= mReadDin();
    }
#endif
    return(ByteValue);
}
#endif  /*LDBSPI_FORMAT_LR_USED*/

#ifdef LDBSPI_FORMAT_LF_USED
/*============================================================================
  DESCRIPTION :void LDBSpiLFSendBits(U8 DataByte )
                Write a bit on the SPI bus

  PARAMETERS (Type,Name,Min,Max) :  
      - Data: Byte to write on SPI bus

  RETURN VALUE : none

  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void LDBSpiLFSendBits(U8 DataByte,U8 NbBits)
{
    U8 BitIndex;
    U8 Data;
    U8 DataMask;

    Data = DataByte;
    DataMask = (1<<(NbBits-1));
    for(BitIndex = 0; BitIndex < NbBits; BitIndex++)
    {
        //  Clock edge signal for set data
        mSetSckHigh();
        
        // Write data
        if ( (Data & DataMask) == DataMask)
        {
            mSetDoutHigh();
        }
        else
        {
            mSetDoutLow();
        }
        Data = Data<<1;

        //Temporization to ensure tDVCL and tCH
        mLDBHarActiveWaitUs(1);

        //  Clock edge signal for sampling
        mSetSckLow();
        //Temporization to ensure tCLDX and tCL
        mLDBHarActiveWaitUs(1);
    }

	// Make sure to leave the SPI bus with the output pin in low state
    mSetDoutLow();
}

/*============================================================================
  DESCRIPTION :void LDBSpiLFReceiveBits(void )
                Read a bit on the SPI bus

  PARAMETERS (Type,Name,Min,Max) :  none

  RETURN VALUE : byte read on the bus

  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
U8 LDBSpiLFReceiveBits(U8 NbBits)
{
    U8 ByteValue = 0;
    U8 BitIndex;

	// Fix the SPI bus output into the low state
    mSetDoutLow();

    for(BitIndex = 0; BitIndex < NbBits; BitIndex++)
    {
        //  Clock edge signal for set data
        mSetSckHigh();
        //Temporization to ensure tCHQV and tCH
        mLDBHarActiveWaitUs(1);
        //  Clock edge signal for sampling
        mSetSckLow();
        //  Read bit
        ByteValue <<= 1;
        ByteValue |= mReadDin();
        //Temporization to ensure tCL
        mLDBHarActiveWaitUs(1);
    }
    return(ByteValue);
}
#endif
