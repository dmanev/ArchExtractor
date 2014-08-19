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
// Component:    DAT_RF
// -----------------------------------------------------------------------------
// $Date:   May 28 2010 18:04:10  $
// $Archive::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_RF/Dat_RFp.h-arc  $
// $Revision:   1.2  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_RF/Dat_RFp.h-arc  $
// 
//    Rev 1.2   May 28 2010 18:04:10   adzhelp
// Cm008663: Code review updates - comments updated
// 
//    Rev 1.1   Mar 09 2010 11:37:06   adzhelp
// Cm007542:  Code review corrections
// 
//    Rev 1.0   Apr 17 2009 10:37:06   ailievb
// Initial revision.
//
//******************************************************************************

#ifdef I_dat_rfp
#else
#define I_dat_rfp (1)

//--------------------------------------------------------------------------
//  Included files to resolve specific definitions in this file
//
//  #include <system_file_name.h>
//  #include "project_file_name.h"
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
//  Constant data
//
//  #define cCMPConstantName   ((tType) ConstantValue)
//--------------------------------------------------------------------------

//Compilation directives, to be uncomented if used
#define _TEST_ALL_BUTTONS_  // Defined to enable all possible push events
                            // adhzelp: This definition should be commented for next version 
                            // and the corresponding mask cMaskNonExistingButtons to be adjusted
//#define _PASSING_RF_      // If defined generates SW that accepts any key ID
#define _DIAGNOSTIC_MEMO_   // Defined to enable diagnostic memorizations
#define _TEST_RF_           // Defined to enable diagnsotic RF testing routines

//periods
#define cDATRfLDBSearchFramePeriodMs    ((U8)40)
  //cDATRfLDBSearchFramePeriodMs should be a multiple of cDATCpuSleepGraphEnginePeriodMs

#define cDATRfWakeUpBlockDuration       ((U16)64) 
  //cWakeUpBlockReceptionTimeOut: non existant because LDB stops himself...

//RC block waiting timeout: aprox: WUPBlock + NbRCBlocks*RCBlock ms 
#define cDATRfRCReceptionTimeOut        ((U16)180) 

//Long Push waiting timeout          
#define cDATRfLongPushWaitTimeOut       ((U16)1000)         // 1s
#define cDATRfLongPushReceiveTimeOut    ((U16)(1000+1000))  // 1s after

#define cDATRfDiagMemorizationTime      ((U16)2000) // For Diagnostic
  //cDiagMemorizationTime should be a multiple of cDATCpuSleepGraphEnginePeriodMs


// Constants for project AW1092. In each constant defined bellow,                    
//  Bit0 represents the first button short push
//  Bit1 ---------- --- second button short push
//  ...
//  Bit3 ---------- --- fourth button short push
//  Bit4 represents the first button long push
//  ...
//Each bit = 0 indicates the button is masked and always forced to 0
//---- --- = 1 indicates the button is allowed and can be pushed
#ifdef _TEST_ALL_BUTTONS_                     
    #define cMaskNonExistingButtons         (0xFF) // no mask applied for TestU purposes
#else   // Definition of mask that will mask the non used buttons for AW1092
                                                         //long-short push
    #define cDATRfMaskFor2ButtonKey           ((U8)0x03) //0000-0011: no 3rd&4th button and long pushs
       
    #define cMaskNonExistingButtons cDATRfMaskFor2ButtonKey
    
#endif

/*--------------------------------------------------------------------------
  Exported Macros

  #define mCMPMacroName   (MacroDefinition)
  --------------------------------------------------------------------------*/ 

//EEPROM redefinition                     To be completed with project's E²PROM 
#define TableOfKeyIdentifier              EEP_KeyIdentifier
#define TableOfRemoteSecretKey1           EEP_RemoteSecretKey1
#define TableOfRemoteSecretKey2           EEP_RemoteSecretKey2
#define TableOfRemoteSecretKey3           EEP_RemoteSecretKey3
#define TableOfRemoteSecretKey4           EEP_RemoteSecretKey4
#define TableOfCurrentResynchroValue      EEP_SI28Bits
#define TableOfInitialResynchroValue      EEP_InitialResynchroValue
#define TableOfDefResynchroValueRead      EEP_DefResynchroValueRead
#define TableOfDefResynchroValueWritten   EEP_DefResynchroValueWrite
#define ResynchroRequest                  EEP_ResynchroRequest   
//-------------------------------------------------------------------------
//  Exported types
//
//  struct  sCMPStructureName { ... };
//  union   uCMPUnionName { ... };
//  enum    eCMPEnumerationName { ... };
// typedef Expression tCMPTypeName;
//
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
//  Exported data
//
//  extern  tType   CMPVariableName;
//  extern  tType*  pCMPVariableName; 
//--------------------------------------------------------------------------
#ifdef _TEST_RF_     
    //to be initialized with contents of RC frame emitted when testing RF hardware
    #define mInitValueOfRCFrameEmitted() \
           {0xC2, 0xF0, 0xA5, 0xC2, 0x81, 0xB3, 0x40, 0x22, 0x5A, 0x00, 0x5F}
    //to be initialized with contents of SI frame emitted when testing RF hardware
    #define mInitValueOfSIFrameEmitted() \
           {0x00, 0x01}
#endif

//--------------------------------------------------------------------------
//  Constant exported data
//
//  extern const tType  CMPVariableName;
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
//  Exported functions
//
//  extern tReturnType CMPFunctionName(tTypeArgument1 ArgumentName1, ... );
//--------------------------------------------------------------------------


/* [EXPORTED_FUNCTIONS_END] */


#endif   /* I_dat_rf */

