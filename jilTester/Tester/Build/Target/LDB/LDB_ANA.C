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
// Component:    LDB_ANA
// -----------------------------------------------------------------------------
// $Date:   Mar 09 2010 09:50:58  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_ANA/LDB_ANA.C-arc  $
// $Revision:   1.7  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_ANA/LDB_ANA.C-arc   $
// 
//    Rev 1.7   Mar 09 2010 09:50:58   adzhelp
// Cm007644: DIAG ULQ not converted  when Doorlock LED active
// 
//    Rev 1.6   Feb 25 2010 17:24:00   adzhelp
// Cm007212: DIAG ULQ converted  when Doorlock LED or Verlog LED active
// 
//    Rev 1.5   Feb 24 2010 15:56:46   adzhelp
// Cm007212:  In sleep mode convert DIAG ULQ when Doorlock LED active
// 
//    Rev 1.4   Oct 07 2009 09:00:04   adzhelp
// Cm005497: Disabled pins are removed from conversion
// 
//    Rev 1.3   Apr 13 2009 15:53:18   adzhelp
// Cm003619: Conversion mode set to 10 bit 
// 
//    Rev 1.2   Apr 07 2009 14:19:24   adzhelp
// Cm003276: Voltage comparator control implemented. 
// In sleep mode convert only certain inputs.
// 
//    Rev 1.1   Mar 10 2009 09:53:20   adzhelp
// Cm003619: Parameterization of LDB_ANA for NEC K0 and project specifics
// 
//    Rev 1.0   20 Nov 2008 15:17:18   ailievb
// Initial revision.
//******************************************************************************

/*--------------------------------------------------------------------------
Body Identification
--------------------------------------------------------------------------*/

#define ldb_ana "ldb_ana"

/*-------------------------------------------------------------------------
Included files

  #include <system_file_name.h>
  #include "project_file_name.h"
--------------------------------------------------------------------------*/

#include "ldbtypes.h"
#include "ldb.h"
#include "ldb_reg.h"

#include "ldb_ana.h"

/*--------------------------------------------------------------------------
Local constants

  #define cConstantName   ((tType) ConstantValue)
--------------------------------------------------------------------------*/
// Wake-up inputs definitions
#define cAI_RR_DOORS_SW     cLDBHarAnaChannel1
#define cAI_DOOR_UNLOCK_SW  cLDBHarAnaChannel2

// HW protection input definition
#define cDIAG_DRIVER_ULQ    cLDBHarAnaChannel5

#define cMaxConvResult      1023U

/*--------------------------------------------------------------------------
Local macros

  #define mMacroName   (MacroDefinition)
--------------------------------------------------------------------------*/
#define mSetEnableComparator(Value)     mLDBRegWrite1BitInRegister(ADM, 0, Value)
#define mSetFrequency()                 (ADM = (cLdbAnaFrequency << 1U))
#define mSetChannelSelection(Valeur)    (ADS = Valeur)
#define mSetEnableConversion(Valeur)    mLDBRegWrite1BitInRegister(ADM, 7, Valeur)
#define mReadConvertedValue()           (ADCR >> 6U) // 10-bit result

#define mIsChannelActive(Channel)       (mLDBRegRead8BitRegister(ADPC) <= (U8)(Channel))

// HW protection LED verlog
#define mIsLEDVerlogEnabled()           (mLDBHarRead(cLDBHarVerlogLed) != cFalse)

/*--------------------------------------------------------------------------
Local types

  struct  sStructureName { ... };
  union   uUnionName { ... };
  enum    eEnumerationName { ... };
  typedef Expression tTypeName;
--------------------------------------------------------------------------*/
typedef U16 tConversionSize;

/*--------------------------------------------------------------------------
Local data

  static  tType   VariableName;
  static  tType*  pVariableName; 
--------------------------------------------------------------------------*/
static tConversionSize ConvResult;

/*--------------------------------------------------------------------------
Constant local data

  static const tType  VariableName;
--------------------------------------------------------------------------*/
// Enter here the different entries used
static const U8   AnalogInputs[cNumberAnalog] = mListAnalogInputs();
static BOOL bSleepMode = cTrue;

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
static MEM_TYPE void LDBAnaAcquire(U8 IndexAna);

/*============================================================================
=========================== LOCAL FUNCTIONS ================================
==========================================================================*/

/*============================================================================
  DESCRIPTION         : Acquire one analog input

  PARAMETERS          : None
  (Type,Name,Min,Max) 
  
  RETURN VALUE        : None
    
  DESIGN INFORMATION  : Refer to Detailed Design Document
============================================================================*/

static MEM_TYPE void LDBAnaAcquire(U8 IndexAna)
{
    U8 u8ChannelL = AnalogInputs[IndexAna];

    if (mIsChannelActive(u8ChannelL))
    {
        // Selects A/D channel
        mSetChannelSelection(u8ChannelL);
        // Starts the A/D Converter
        mSetEnableConversion(1);
        // Clear the peinding flag of the interrupt
        mLDBIntClearIsrRequestFlag(INTAD);
        // Waits the pending flag of the interrupt to be up
        while (mLDBIntGetIsrRequestFlag(INTAD) == 0);
        // Reads the value converted
        ConvResult = mReadConvertedValue();
        // Stops the A/D converter
        mSetEnableConversion(0);
    }
    else
    {
        // Disabled inputs
        if ((IndexAna == cAI_RR_DOORS_SW) || (IndexAna == cAI_DOOR_UNLOCK_SW))
        {
            ConvResult = cMaxConvResult; // inputs are inverted
        }
        else
        {
            ConvResult = 0;
        }
    }
}

/*============================================================================
=========================== EXPORTED FUNCTIONS =============================
==========================================================================*/

/*============================================================================
  DESCRIPTION         : Acquires all the analog inputs

  PARAMETERS          : None
  (Type,Name,Min,Max) 
  
  RETURN VALUE        : None
    
  DESIGN INFORMATION  : Refer to Detailed Design Document
============================================================================*/

MEM_TYPE void LDBAnaReceiveWithoutAddr(tMsg* pMsg)
{
    if (pMsg != NULL)
    {
        U16* pu16Buffer = (U16*)(pMsg->pBuffer);
        mLIBassert(pMsg->Lng == cNumberAnalog * 2);
        
        if (bSleepMode == cFalse)
        {
            U8 i;
            for (i = 0; i < cNumberAnalog; ++i)
            {
                // Acquisition of the analog input
                LDBAnaAcquire(i);
                // Sends the result to the DAT layer
                pu16Buffer[i] = ConvResult;
            }
        }
        else
        {
            // Only wake-up inputs are read to spare time
            LDBAnaAcquire(cAI_RR_DOORS_SW);
            pu16Buffer[cAI_RR_DOORS_SW] = ConvResult;
            LDBAnaAcquire(cAI_DOOR_UNLOCK_SW);
            pu16Buffer[cAI_DOOR_UNLOCK_SW] = ConvResult;

            // HWP of LED Verlog in sleep mode
            // Convert diag input only when output is enabled
            if (mIsLEDVerlogEnabled())
            {
                LDBAnaAcquire(cDIAG_DRIVER_ULQ);
                pu16Buffer[cDIAG_DRIVER_ULQ] = ConvResult;
            }
        }
    }
    else
    {
          mLIBassert(cFalse);
    }
}

/*============================================================================
  DESCRIPTION         : Initialize the component

  PARAMETERS          : None
  (Type,Name,Min,Max) 
  
  RETURN VALUE        : None
    
  DESIGN INFORMATION  : Refer to Detailed Design Document
============================================================================*/

void LDBAnaInit(void)
{
    // Sets of the frequency
    mSetFrequency();
    // Enable voltage comparator 
    mSetEnableComparator(1);
}

/*============================================================================
  DESCRIPTION         : Control the component

  PARAMETERS          : None
  (Type,Name,Min,Max) 
  
  RETURN VALUE        : None
    
  DESIGN INFORMATION  : Refer to Detailed Design Document
============================================================================*/
MEM_TYPE void LDBAnaControl(tCtrl Ctrl)
{
    switch (Ctrl)
    {
    case cLDBAnaStartHW:
        // Enable voltage comparator 
        mSetEnableComparator(1);
        break;
    case cLDBAnaStopHW:
        // Disable voltage comparator 
        mSetEnableComparator(0);
        break;
    default:
        mLIBassert(cFalse);
        break;
    }
}

/*============================================================================
  DESCRIPTION         : Enter sleep mode

  PARAMETERS          : None
  (Type,Name,Min,Max) 
  
  RETURN VALUE        : None
    
  DESIGN INFORMATION  : Refer to Detailed Design Document
============================================================================*/
void LDBAnaLeaveSleepMode(void)
{
    bSleepMode = cFalse;
}

/*============================================================================
  DESCRIPTION         : Enter sleep mode

  PARAMETERS          : None
  (Type,Name,Min,Max) 
  
  RETURN VALUE        : None
    
  DESIGN INFORMATION  : Refer to Detailed Design Document
============================================================================*/
void LDBAnaEnterSleepMode(void)
{
    bSleepMode = cTrue;
}

