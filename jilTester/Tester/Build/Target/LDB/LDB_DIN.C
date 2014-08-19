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
// Component:    LDB_DIN
// -----------------------------------------------------------------------------
// $Date:   Jan 15 2010 11:25:18  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_DIN/LDB_DIN.C-arc  $
// $Revision:   1.10  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_DIN/LDB_DIN.C-arc   $
// 
//    Rev 1.10   Jan 15 2010 11:25:18   adzhelp
// Cm006828: Shorten the time for LDB_KWP activation
// 
//    Rev 1.9   Jan 14 2010 14:27:56   adzhelp
// Cm006828: Implementation of sleep mode KLine WuP detection
// 
//    Rev 1.8   Oct 07 2009 09:01:32   adzhelp
// Cm005497: Disabled inversed inputs are set as inactive
// 
//    Rev 1.7   Jun 23 2009 17:22:42   adzhelp
// Cm005124: Inversion of reading of P01 removed
// 
//    Rev 1.6   Apr 27 2009 15:58:20   adzhelp
// Cm003619: LDBDouControl() placed in banked memory
// 
//    Rev 1.5   Apr 17 2009 15:23:58   adzhelp
// Cm003619: Inversion of inputs P140 and P33 removed
// 
//    Rev 1.4   Apr 16 2009 10:20:06   adzhelp
// Cm003276: Checking of falling edge on KLine for wake-up added
// 
//    Rev 1.3   Mar 19 2009 13:38:06   adzhelp
// Cm003276: In sleep mode only wake-up pins are read
// 
//    Rev 1.2   Mar 10 2009 10:22:40   adzhelp
// Cm003619: Parameterization according to DAT_DINp.jil
// 
//    Rev 1.1   Mar 20 2009 14:32:20   ailievb
// Cm003619: LDB_DIN parametrization.
// 
//    Rev 1.0   10 Nov 2008 15:27:18   ailievb
// Initial revision.
//******************************************************************************

/*--------------------------------------------------------------------------
Body Identification
--------------------------------------------------------------------------*/
#define ldb_din "ldb_din"

/*-------------------------------------------------------------------------
Included files

  #include <system_file_name.h>
  #include "project_file_name.h"
--------------------------------------------------------------------------*/
#include "ldbtypes.h"
#include "ldb.h"
#include "ldb_har.h"
#include "ldb_sup.h"
#include "ldb_din.h"
#include "ldb_dinp.h"

/*--------------------------------------------------------------------------
Local constants

  #define cConstantName   ((tType) ConstantValue)
--------------------------------------------------------------------------*/
// Configuration according to DAT_DINp.jil

// Active bits ('1') in mask specify which pins are read
// Active bits in inversion mask will invert the input value
// Active bits in sleep mask specify which inputs are read in sleep mode

// Buffer byte 0
#define cBuffer0Port        P0
#define cBuffer0Mask        (U8)0x22U
#define cBuffer0MaskInvert  (U8)0x00U
// Buffer byte 1
#define cBuffer1Port        P1
#define cBuffer1Mask        (U8)0x10U
#define cBuffer1MaskInvert  (U8)0x10U
#define cBuffer1MaskSleep   (U8)0x10U
// Buffer byte 2
#define cBuffer2Port        P3
#define cBuffer2Mask        (U8)0x0FU
#define cBuffer2MaskInvert  (U8)0x06U
// Buffer byte 3
#define cBuffer3Port        P4
#define cBuffer3Mask        (U8)0x0DU
#define cBuffer3MaskInvert  (U8)0x0DU
// Buffer byte 4
#define cBuffer4Port        P5
#define cBuffer4Mask        (U8)0x0BU
#define cBuffer4MaskInvert  (U8)0x02U
#define cBuffer4MaskSleep   (U8)0x08U
// Buffer byte 5
#define cBuffer5Port        P6
#define cBuffer5Mask        (U8)0x0FU
#define cBuffer5MaskInvert  (U8)0x00U
// Buffer byte 6
#define cBuffer6Port        P12
#define cBuffer6Mask        (U8)0x19U
#define cBuffer6MaskInvert  (U8)0x18U
#define cBuffer6MaskSleep   (U8)0x19U
// Buffer byte 7
#define cBuffer7Port        P14
#define cBuffer7Mask        (U8)0x01U
#define cBuffer7MaskInvert  (U8)0x00U

#define cBufferSize         9U

// KLine sleep mode polling:
#define cSampleLowMaxNum    (U8)2U

/*--------------------------------------------------------------------------
Local macros

  #define mMacroName   (MacroDefinition)
--------------------------------------------------------------------------*/
#define mReadPortInputsToBuffer(ByteNumber)             \
    mReadPortInputs(cBuffer##ByteNumber##Port,          \
                    cBuffer##ByteNumber##Mask,          \
                    cBuffer##ByteNumber##MaskInvert)

#define mReadPortInputsToBufferSleep(ByteNumber)        \
    mReadPortInputs(cBuffer##ByteNumber##Port,          \
                    cBuffer##ByteNumber##MaskSleep,     \
                    cBuffer##ByteNumber##MaskInvert)

#define mReadPortInputs(Port, Mask, MaskInvert) \
    (U8)( (U8)(mLDBRegRead8BitRegister(Port) & (Mask)) ^ (MaskInvert))

#define mDisableInversedInputsConfiguredAsOutputs() \
    if (mLDBRegRead1BitInRegister(PM4, 0) == cLDBHarOutput) \
    { \
        pu8Buffer[3] &= (U8)0xFEU; /* byte 3, bit 0 */ \
    } \
    if (mLDBRegRead1BitInRegister(PM12, 4) == cLDBHarOutput) \
    { \
        pu8Buffer[6] &= (U8)0xEFU; /* byte 6, bit 4 */ \
    } \
    if (mLDBRegRead1BitInRegister(PM5, 1) == cLDBHarOutput) \
    { \
        pu8Buffer[4] &= (U8)0xFDU; /* byte 4, bit 1 */ \
    }


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
static BOOL bSleepMode = cTrue;

// KLine sleep mode polling:
static BOOL bKLinePreviousLevel;
static BOOL bKLineFallingEdge;
static BOOL u8KLineLowLeveCount;

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
  DESCRIPTION : 

  PARAMETERS (Type,Name,Min,Max) :  none
  
  RETURN VALUE :  none
    
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void LDBDinInit(void)
{
}

/*============================================================================
  DESCRIPTION : 

  PARAMETERS (Type,Name,Min,Max) :  none
  
  RETURN VALUE :  none
    
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
void LDBDinReceiveWithoutAddr(tMsg* pMsg)
{
    if (pMsg != NULL)
    {
        U8* pu8Buffer = pMsg->pBuffer;
        mLIBassert(pMsg->Lng == cBufferSize);

        if (bSleepMode == cFalse)
        {
            pu8Buffer[0] = mReadPortInputsToBuffer(0);
            pu8Buffer[1] = mReadPortInputsToBuffer(1);
            pu8Buffer[2] = mReadPortInputsToBuffer(2);
            pu8Buffer[3] = mReadPortInputsToBuffer(3);
            pu8Buffer[4] = mReadPortInputsToBuffer(4);
            pu8Buffer[5] = mReadPortInputsToBuffer(5);
            pu8Buffer[6] = mReadPortInputsToBuffer(6);
            pu8Buffer[7] = mReadPortInputsToBuffer(7);
        }
        else
        {
            // Only wake-up inputs are read to avoid non-stabilization issues
            pu8Buffer[1] = mReadPortInputsToBufferSleep(1);
            pu8Buffer[4] = mReadPortInputsToBufferSleep(4);
            pu8Buffer[6] = mReadPortInputsToBufferSleep(6);
        }
        //Disabled inversed inputs which has been configured as outputs 
        //driving 0V (based on ECUType by LDB_DOU)
        mDisableInversedInputsConfiguredAsOutputs();
    }
}

/*============================================================================
  DESCRIPTION : 

  PARAMETERS (Type,Name,Min,Max) :  none
  
  RETURN VALUE :  none
    
  DESIGN INFORMATION :  refer to Detailed Design Document
============================================================================*/
MEM_TYPE void LDBDinControl(tCtrl Ctrl)
{
    switch(Ctrl)
    {    
    case cLDBDinEnterNominalMode:
        bSleepMode = cFalse;
        break;
    case cLDBDinEnterSleepMode:
        bSleepMode = cTrue;
        bKLineFallingEdge = cFalse;
        break;
    case cLDBDinInitiateKLineWakeupConditions:
        bKLinePreviousLevel = mLDBHarRead(cLDBHarRxKwp);
        break;
    case cLDBDinCheckKLineWakeupConditions:
        if (bKLineFallingEdge == cFalse)
        {        
            if ((mLDBHarRead(cLDBHarRxKwp) == 0) && (bKLinePreviousLevel != 0))
            {
                bKLineFallingEdge = cTrue;
                u8KLineLowLeveCount = cSampleLowMaxNum;
            }
            else
            {
                // wait for falling edge
            }
            bKLinePreviousLevel = mLDBHarRead(cLDBHarRxKwp);
        }
        else
        {
            if (u8KLineLowLeveCount > 0)
            {
                u8KLineLowLeveCount--;

                if (mLDBHarRead(cLDBHarRxKwp) == 1)
                {
                    // rising edge found
                    // request wake-up
                    LDBSupLeaveSleepMode();
                    // KWP wait for StartComminucations
                    LDBControl(cLDBChannelKwp, cLDBKwpWaitForStartCom);
                    DATPinCallBackCtrl(cLDBPinWakeUpRequested);
                }
                else
                {
                    // wait for rising edge
                }
            }
            else
            {
                bKLineFallingEdge = cFalse;
            }
        }
        break;
    default:
        mLIBassert(cFalse);
        break;
    }
}
