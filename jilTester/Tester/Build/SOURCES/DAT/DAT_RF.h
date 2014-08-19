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
// Component:    <Name of the component and its variant number, if any>
//               <Comments about the component (role, algorithm, structure,
//               limitations, defined tasks and events...)>
// -----------------------------------------------------------------------------
// $Date:   Dec 04 2009 16:48:58  $
// $Archive::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_RF/DAT_RF.h-arc  $
// $Revision:   1.6  $
// -----------------------------------------------------------------------------
// $Log:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_RF/DAT_RF.h-arc  $
// 
//    Rev 1.6   Dec 04 2009 16:48:58   adzhelp
// Cm006719: Added counter for RC blocks with correct CRC
// 
//    Rev 1.5   Oct 07 2009 11:41:54   adzhelp
// Cm006427: Function moved to banked area
// 
//    Rev 1.4   Oct 06 2009 17:36:56   akodzhh
// Cm006427: DATRfPushMemorized is now updated for UnlockDrDoor, UnlockAll and LockAll trough LAP_DLK(SDO).
// 
//    Rev 1.3   Sep 01 2009 14:05:10   amanevd
// Cm005142: Status of Confidential Diagnostic routines included
// 
//    Rev 1.2   Aug 31 2009 16:13:42   amanevd
// Cm005142: Transfer of Confidential Diagnostic to LIB_CFD
// 
//    Rev 1.1   Apr 28 2009 10:55:06   adzhelp
// Cm003276: Implementation of RF sleep mode management
// 
//    Rev 1.0   Apr 17 2009 10:37:04   ailievb
// Initial revision.
// 
//    Rev 1.1   Apr 17 2009 10:25:02   ailievb
// Cm003265:Implementation of the Remote Keyless Entry functionality (Without SDO part)
// 
//    Rev 1.0   Mar 24 2009 10:40:00   ailievb
// Initial revision.
//******************************************************************************
#endif

#ifndef I_DAT_RF_H
#define I_DAT_RF_H (1)

/*--------------------------------------------------------------------------
  Included files to resolve specific definitions in this file

  #include <system_file_name.h>
  #include "project_file_name.h"
  --------------------------------------------------------------------------*/
#include "dat_rfp.h"

/*--------------------------------------------------------------------------
  Constant data

  #define cCMPConstantName   ((tType) ConstantValue)
  --------------------------------------------------------------------------*/
#define cDATRfShortPressButton1     ((U8)0x01)
#define cDATRfShortPressButton2     ((U8)0x02)
#define cDATRfShortPressButton3     ((U8)0x04)
#define cDATRfShortPressButton4     ((U8)0x08)

#define cDATRfLongPressButton1      ((U8)0x10)
#define cDATRfLongPressButton2      ((U8)0x20)
#define cDATRfLongPressButton3      ((U8)0x40)
#define cDATRfLongPressButton4      ((U8)0x80)

#ifdef _DIAGNOSTIC_MEMO_ //for Diagnostic
#define cDATRfDiagUnlockDrDoor  ((U8)0x01)
#define cDATRfDiagUnlockAll     ((U8)0x02)
#define cDATRfDiagLockAll       ((U8)0x04)
#endif
/*--------------------------------------------------------------------------
  Exported Macros

  #define mCMPMacroName   (MacroDefinition)
  --------------------------------------------------------------------------*/ 

//API LAP
#define mDATReadU1BitDATRfLockPushDefault()        (mDATReadU1BitDATRfButton1IsShortPressedDefault())
#define mDATReadU1BitDATRfUnlockPushDefault()      (mDATReadU1BitDATRfButton2IsShortPressedDefault())
#define mDATReadU1BitDATRfButton1IsShortPressedDefault() (DATRfReadButtonState(cDATRfShortPressButton1))
#define mDATReadU1BitDATRfButton2IsShortPressedDefault() (DATRfReadButtonState(cDATRfShortPressButton2))
#define mDATReadU1BitDATRfButton3IsShortPressedDefault() (DATRfReadButtonState(cDATRfShortPressButton3))
#define mDATReadU1BitDATRfButton4IsShortPressedDefault() (DATRfReadButtonState(cDATRfShortPressButton4))

#define mDATReadU1BitDATRfButton1IsLongPressedDefault()  (DATRfReadButtonState(cDATRfLongPressButton1))
#define mDATReadU1BitDATRfButton2IsLongPressedDefault()  (DATRfReadButtonState(cDATRfLongPressButton2))
#define mDATReadU1BitDATRfButton3IsLongPressedDefault()  (DATRfReadButtonState(cDATRfLongPressButton3))
#define mDATReadU1BitDATRfButton4IsLongPressedDefault()  (DATRfReadButtonState(cDATRfLongPressButton4))

#ifdef _DIAGNOSTIC_MEMO_    //For Diagnostic           
  #define mDATReadU8BitRfPushMemorizedDefault()               (DATRfPushMemorized)
  #define mDATReadU32BitRfRCFrameIDReceivedDefault()          (DATRfRCFrameIDEReceived)
#endif                                                        
#ifdef _TEST_RF_ //counters used for RF hardware testing   
  #define mDATReadU8BitDATRfNbWakeUpBlocksReceivedDefault()  (DATRfNbWakeUpBlocksReceived)
  #define mDATReadU8BitDATRfNbRCBlocksReceivedDefault()      (DATRfNbRCBlocksReceived)
  #define mDATReadU8BitDATRfNbRCBlocksReceivedCrcOKDefault() (DATRfNbRCBlocksReceivedCrcOK)
  #define mDATReadU8BitDATRfNbRCBlocksReceivedAndOKDefault() (DATRfNbRCBlocksReceivedAndOK)
#endif

//API LAP français pour compatibilité... 
#define mDATLireU1BitDATRfButton1IsShortPressedDefaut() (DATRfReadButtonState(cDATRfShortPressButton1))
#define mDATLireU1BitDATRfButton2IsShortPressedDefaut() (DATRfReadButtonState(cDATRfShortPressButton2))
#define mDATLireU1BitDATRfButton3IsShortPressedDefaut() (DATRfReadButtonState(cDATRfShortPressButton3))
#define mDATLireU1BitDATRfButton4IsShortPressedDefaut() (DATRfReadButtonState(cDATRfShortPressButton4))

#define mDATLireU1BitDATRfButton1IsLongPressedDefaut()  (DATRfReadButtonState(cDATRfLongPressButton1))
#define mDATLireU1BitDATRfButton2IsLongPressedDefaut()  (DATRfReadButtonState(cDATRfLongPressButton2))
#define mDATLireU1BitDATRfButton3IsLongPressedDefaut()  (DATRfReadButtonState(cDATRfLongPressButton3))
#define mDATLireU1BitDATRfButton4IsLongPressedDefaut()  (DATRfReadButtonState(cDATRfLongPressButton4))

#define mDATReadU32BitRollingCodeDefault()              (DATRfRCFrameSRReceived.Format32Bit)
#ifdef _DIAGNOSTIC_MEMO_ //for Diagnostic           
  #define mDATLireU8BitRfPushMemorizedDefaut()              (DATRfPushMemorized)
  #define mDATLireU32BitRfRCFrameIDReceivedDefaut()         (DATRfRCFrameIDEReceived)
#endif
#ifdef _TEST_RF_ //counters used for RF hardware testing   
  #define mDATLireU8BitDATRfNbWakeUpBlocksReceivedDefaut()  (DATRfNbWakeUpBlocksReceived)
  #define mDATLireU8BitDATRfNbRCBlocksReceivedDefaut()      (DATRfNbRCBlocksReceived)
  #define mDATLireU8BitDATRfNbRCBlocksReceivedAndOKDefaut() (DATRfNbRCBlocksReceivedAndOK)
  #define mDATLireU8BitDATRfNbSIBlocksReceivedDefaut()      (DATRfNbSIBlocksReceived)
  #define mDATLireU8BitDATRfNbSIBlocksReceivedAndOKDefaut() (DATRfNbSIBlocksReceivedAndOK)
#endif


#define mDATControlRf(Ctrl)         mDATRfControl##Ctrl()
#define mDATRfControlStart()        DATRfStart()
#define mDATRfControlStop()         DATRfStop()
#ifdef _TEST_RF_ //counters used for RF hardware testing   
  #define mDATRfControlInitializeRFTest()   DATRfInitializeRFTest()
#endif

#ifdef _DIAGNOSTIC_MEMO_
    #define DATRfMemorisePush(ButtonCode)  DATRfArmerNbAlarmITForDiag(ButtonCode)
#else
    #define DATRfMemorisePush(ButtonCode)  
#endif

/*--------------------------------------------------------------------------
  Exported types

  struct  sCMPStructureName { ... };
  union   uCMPUnionName { ... };
  enum    eCMPEnumerationName { ... };
  typedef Expression tCMPTypeName;

  --------------------------------------------------------------------------*/
typedef union
{
    U32 Format32Bit;
    struct
    {
        U16 F16Bit1;
        U16 F16Bit2;
    }Format16Bit;
    struct
    {
        U8 F8Bit1;
        U8 F8Bit2;
        U8 F8Bit3;
        U8 F8Bit4;
    }Format8Bit;
}tDatRfMot32Bit;

/*--------------------------------------------------------------------------
  Exported data

  extern  tType   CMPVariableName;
  extern  tType*  pCMPVariableName; 
  --------------------------------------------------------------------------*/ 
#ifdef _DIAGNOSTIC_MEMO_ //for Diagnostic   
  extern U8  DATRfPushMemorized;
  extern U32 DATRfRCFrameIDEReceived; //RC frame Identifier received  
#endif
#ifdef _TEST_RF_ //counters used for RF hardware testing   
  extern U8  DATRfNbWakeUpBlocksReceived;
  extern U8  DATRfNbRCBlocksReceived;
  extern U8  DATRfNbRCBlocksReceivedAndOK;
  extern U8  DATRfNbRCBlocksReceivedCrcOK;
  extern U8  DATRfNbSIBlocksReceived;
  extern U8  DATRfNbSIBlocksReceivedAndOK;
#endif

extern tDatRfMot32Bit DATRfRCFrameSRReceived;

/*--------------------------------------------------------------------------
  Constant exported data

  extern const tType  CMPVariableName;
  --------------------------------------------------------------------------*/ 

/*--------------------------------------------------------------------------
  Exported functions

  extern tReturnType CMPFunctionName(tTypeArgument1 ArgumentName1, ... );
  --------------------------------------------------------------------------*/ 
extern void   DATRfInit(void);
extern void   DATRfStart(void);  
extern void   DATRfStop(void);
extern void   DATRfTask(void);
extern BOOL DATRfReadButtonState(U8);
extern void   DATRfIsAnybodyMaintainActiveState(void);
extern void   DATRfIsAnybodyMaintainActiveSleepState(void);
extern void   DATRfInitializeRFTest(void); //counters used for RF hardware testing 
#ifdef _DIAGNOSTIC_MEMO_ //for Diagnostic   
extern MEM_TYPE void   DATRfArmerNbAlarmITForDiag(U8 u8RfButtonCodeP);
#endif 

/* [EXPORTED_FUNCTIONS_END] */

#endif   /* I_DAT_RF_H */

