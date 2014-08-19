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
// Component:    LDB_RF
// -----------------------------------------------------------------------------
// $Date:   Feb 12 2010 17:16:58  $
// $Archive::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_RF/LDB_RFp.h-arc  $
// $Revision:   1.6  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_RF/LDB_RFp.h-arc  $
// 
//    Rev 1.6   Feb 12 2010 17:16:58   adzhelp
// Cm005818: Timeout for M pattern scanning sequence removed
// 
//    Rev 1.5   Feb 08 2010 11:10:40   adzhelp
// Cm005818: Corrections according to JML issues
// 
//    Rev 1.4   Sep 08 2009 11:33:50   ailievb
// Cm005818: RKE: Update RFchannel according to issues identified in AW1092 project. 
// 
//    Rev 1.3   Sep 07 2009 10:23:50   ailievb
// Cm005100: QAC and code review fix.
// 
//    Rev 1.2   Jul 10 2009 14:31:44   ailievb
// Cm004983:  W&S: The consumption in Sleep Mode is above 2.35 mA
// 
//    Rev 1.1   Apr 28 2009 10:47:52   adzhelp
// Cm003276: Implementation of RF sleep mode management
// 
//    Rev 1.0   Apr 16 2009 15:37:00   ailievb
// Initial revision.
//******************************************************************************
#endif

#ifndef I_LDB_RF_P
#define I_LDB_RF_P (1)

//-------------------------------------------------------------------------
//  Included files to resolve specific definitions in this file
//
//  #include <system_file_name.h>
//  #include "project_file_name.h"
//-------------------------------------------------------------------------
#include "deftypes.h"

//-------------------------------------------------------------------------
//  Constant data
//
//  #define cCNLConstantName   ((tType) ConstantValue)
//-------------------------------------------------------------------------

#define cLDBRfMPatternBit                  ((U8)0U) 
#define cLDBRfWakeUpEdge                   cLDBIocRisingEdge

//Hardware activation time necessary before Rf frames can be received
#define cLDBRfRfHardwareActivationTimeInUs    1000UL //1ms = 10^3us
#define cLDBRfRfHardwareActivationTimeSleepInUs 100UL // 100 us this value is determined empirically
                                                      // to be updated when changes made in sleep mode management
//WAKE UP BLOCK
//Time between 2 falling edges of the WakeUp block
#define cLDBRfTBitInUs                     ((U16)256U) //256us 

//Number of WakeUp bits between 2 cosecutive edges
#define cLDBRfWakeUpIncrement               ((U8)  1U) 
#define cLDBRfWakeUpBitToleranceInUs        ((U16)35U) //will move the window 42

#define cLDBRfMinNbWakeUpBits               ((U8)  8U)   //Total NbWakeUpBits =16*16=256
#define cLDBRfMaxNbErrorWakeUpBits          ((U8)  2U) 
//RC BLOCK
#define cLDBRfMinNbMPatternBits             ((U8)  5U)
#define cLDBRfNbBitsInPreamble              ((U8) 14U)
#define cLDBRfNbPreambleBitsTimeOut         ((U8) 12U)
#define cLDBRfMaxNbPreambleErrorBits        ((U8)  3U)
//number of bits in a RCBlock without Run-in = 114-26
#define cLDBRfNbBitsInRCBlockToBeRead       ((U8) 88U)
//These 2 parametres should be mesured (see DCD for further details)
#define cLDBRfMaxInterruptDurationInUs      ((U16) 20U)    //Time execution IT
#define cLDBRfLDBRegWaitDelay               ((U16)(60U)) //Time from data reception  
                                                             //until input in IT function


//SI BLOCK
//number of bits in a RCBlock without Run-in nor Space= 114-26-78
#define cLDBRfNbBitsInSIBlockToBeRead       ((U8)10U)
#define cLDBRfNbBitsInSpaceOfSIBlock        ((U8)78U)
//-------------------------------------------------------------------------
//  Exported Macros
//
//  #define mCNLMacroName   (MacroDefinition)
//-------------------------------------------------------------------------
// Define following macro in order to measure duration of RF_STROBE active
// level in sleep mode: connect an oscilloscope to pin #43 (Port13)
// use it together with DISABLE_RECEPTION
//#define MEASURE_RF_STROBE_DURATION

// Define following macro to disable reception. Useful for measuring consumption
//#define DISABLE_RECEPTION

// Define following macro to enable additional debugging stuff
//#define _DEBUG_LDBRF_

// RF signal from waveform generator is used  
//#define _DEBUG_WITH_GENERATOR_

// Define following macro to enable recognition of key with specified ID in mIsKeyMatch()
//#define DEBUG_SPECIFIED_KEY
#define mLDBRfIsKeyMatch() ((Msg.pBuffer[0] == 0x53) && (Msg.pBuffer[1] == 0xD5) && (Msg.pBuffer[2] == 0x4A))

//-------------------------------------------------------------------------
//  Exported type
//
//  struct  sCNLStructureName { ... };
//  union   uCNLUnionName { ... };
// enum    eCNLEnumerationName { ... };
//  typedef Expression tCNLTypeName;
//
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//  Exported data
//
//  extern  tType   CNLVariableName;
//  extern  tType*  pCNLVariableName; 
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//  Constant exported data
//
//  extern const tType  CNLVariableName;
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//  Exported functions
//
//  extern tReturnType CNLFunctionName(tTypeArgument1 ArgumentName1, ... );
//-------------------------------------------------------------------------


#endif   /* I_LDB_RF_P */
