#ifndef _QAC_
//******************************************************************************
// Company:      Johnson Controls Inc.
// -----------------------------------------------------------------------------
// Copyright:    This software is JCI property.
//               Duplication or disclosure without JCI written authorization
//               is prohibited.
// -----------------------------------------------------------------------------
// Project:      X90_BCM
// Language:     C
// -----------------------------------------------------------------------------
// Component:    DAT_KWP.H
// -----------------------------------------------------------------------------
// $Log:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_KWP/DAT_KWP.H-arc  $   
// 
//    Rev 1.0   Jan 12 2009 11:31:08   akodzhh
// Initial revision.
// 
//
//******************************************************************************
#endif

#ifndef I_DAT_KWP_H
#define I_DAT_KWP_H (1)

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------
#ifdef _QAC_
#include "ldb.h"
#endif

//------------------------------------------------------------------------------
// Constant data
//------------------------------------------------------------------------------
#define cDATKwpRxBufferSize   ((U8)70)
#define cDATKwpTxBufferSize   ((U8)70)

#define cDATKwpBroadcastID    ((U8)0xFF)
#define cDATKwpECUId          ((U8)0x26)
#define cDATKwpDiagToolsId    ((U8)0xF1)

//------------------------------------------------------------------------------
// Exported type
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------ 
extern U8     DATKwpRxBuffer[cDATKwpRxBufferSize];
extern U8     DATKwpTxBuffer[cDATKwpRxBufferSize];

extern tMsg   DATKwpTxMsg;
extern U8     DATKwpRxFrameLgth;

//------------------------------------------------------------------------------
// Constant exported data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported Macros
//------------------------------------------------------------------------------
// API Control
#define mDATControlKwp(Ctrl)     DATKwp##Ctrl()
#define DATKwpSendFrame()        TOSActivateTask(cTOSTaskID_ControlKwp)
#define DATKwpNoAnswer()         DATKwpReturnInRxMode()
#define DATKwpWaitForWakeUp()    DATKwpActivateWakeUpDetection()

// API Read
#define mDATReadU8BitDATKwpRxFrameLgthDefault()            (DATKwpRxFrameLgth)
#define mDATReadTableU8BitDATKwpRxBufferDefault(Index)     (DATKwpRxBuffer[(Index)+3])
#define mDATReadU8BitTargetIDDefault()                     (DATKwpRxBuffer[1])

// API Write
#define mDATWriteU8BitDATKwpTxFrameLgthDefault(Val)          (DATKwpTxMsg.Lng = (Val))
#define mDATWriteTableU8BitDATKwpTxBufferDefault(Index,Val)  (DATKwpTxBuffer[(Index)+3] = (Val))

//------------------------------------------------------------------------------
// Exported functions
//------------------------------------------------------------------------------
extern void DATKwpInit(void);
extern void DATKwpReturnInRxMode(void);
extern void DATKwpTaskControl(void);
extern void DATKwpActivateWakeUpDetection(void);
extern void DATKwpLeaveStartingStepState(void);
extern void DATKwpIsMaintainActiveState(void);

#endif   /* I_DAT_KWP_H */
