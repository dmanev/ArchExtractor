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
// Component:    LAP_KWP.H
// -----------------------------------------------------------------------------
// $Log:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_KWP/LAP_KWP.H-arc  $
// 
//    Rev 1.3   Sep 23 2009 12:21:44   adzhelp
// Cm003277: Implementation of read log zone request (ID F0...FF)
// 
//    Rev 1.2   Apr 22 2009 15:27:06   adzhelp
// Cm003128: MEM_TYPE attribute added to tLAPKwpServiceFunction
// 
//    Rev 1.1   20 Mar 2009 18:09:48   akodzhh
// Cm003128 - last session restore after Read immo conf.
// 
//    Rev 1.0   Jan 14 2009 16:24:04   akodzhh
// Initial revision.
// 
//******************************************************************************
#endif

#ifndef I_LAP_KWP_H
#define I_LAP_KWP_H (1)

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Constant data
//------------------------------------------------------------------------------
#define cLAPKwpIdNoRequest                              ((U8) 0x00)
#define cLAPKwpIdStartDiagnosticSession                 ((U8) 0x10)
#define cLAPKwpIdSecurityAccess                         ((U8) 0x27)
#define cLAPKwpIdTesterPresent                          ((U8) 0x3E)
#define cLAPKwpIdEcuReset                               ((U8) 0x11)
#define cLAPKwpIdReadDataByLocalIdentifier              ((U8) 0x21)
#define cLAPKwpIdReadMemoryByAddress                    ((U8) 0x23)
#define cLAPKwpIdWriteDataByLocalIdentifier             ((U8) 0x3B)
#define cLAPKwpIdWriteMemoryByAddress                   ((U8) 0x3D)
#define cLAPKwpIdDynamicallyDefinedlocalIdentifier      ((U8) 0x2C)
#define cLAPKwpIdReadStatusOfDTC                        ((U8) 0x17)
#define cLAPKwpIdReadFreezeFrameData                    ((U8) 0x12)
#define cLAPKwpIdClearDiagnosticInformation             ((U8) 0x14)
#define cLAPKwpIdInputOutputControlByLocalIdentifier    ((U8) 0x30)
#define cLAPKwpIdStartRoutineByLocalIdentifier          ((U8) 0x31)
#define cLAPKwpIdStopRoutineByLocalIdentifier           ((U8) 0x32)
#define cLAPKwpIdRequestDownLoad                        ((U8) 0x34)
#define cLAPKwpIdRequestUpLoad                          ((U8) 0x35)
#define cLAPKwpIdReadDataByCommonIdentifier             ((U8) 0x22)
#define cLAPKwpIdStartCommunication                     ((U8) 0x81)
#define cLAPKwpIdStopCommunication                      ((U8) 0x82)
#define cLAPKwpIdControlDTCSetting                      ((U8) 0x85)

#define cLAPKwpIdNegativeResponse                       ((U8) 0x7F)
#define cLAPKwpNRLength                                 ((U8) 0x03)

#define cLAPKwpServiceIsCorrect         ((U8) 0x00)
#define cLAPKwpServiceNotSupported      ((U8) 0x11)
#define cLAPKwpInvalidFormat            ((U8) 0x12)
#define cLAPKwpConditionNotCorrect      ((U8) 0x22)
#define cLAPKwpFaultUponWriting         ((U8) 0x87)

// Request status
#define cLAPKwpNewServiceIsRequested        ((U8)1)
#define cLAPKwpServiceIsTreated             ((U8)2)
#define cLAPKwpServiceIsFinished            ((U8)3)

#define cLAPKwpRoutineNotActivated      ((U8) 0x00)
#define cLAPKwpRoutineInProgress        ((U8) 0x01)
#define cLAPKwpRoutineTerminatedOK      ((U8) 0x02)
#define cLAPKwpRoutineTerminatedNOK     ((U8) 0x04)

//------------------------------------------------------------------------------
// Exported type
//------------------------------------------------------------------------------
typedef void (MEM_TYPE* tLAPKwpServiceFunction)(void);

typedef struct sKWPParamOfSession
{
    U8                             NbOfSupportedService;
    U8                             SessionIdentifier;
    const U8 *                     pTabIdentifierOfSupportedService;
    const tLAPKwpServiceFunction * pTabFunctionOfSupportedService;
    tLAPKwpServiceFunction         CloseActiveSession;
    tLAPKwpServiceFunction         OpenActiveSession;
//QACJ 3205: akodzhh: the identifier is used in other LAP_DIAG files
} tLAPKwpParamOfSession;

//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------ 
extern U8  u8LAPKwpRequestStatus;

//------------------------------------------------------------------------------
// Constant exported data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported Macros
//------------------------------------------------------------------------------
#define LAPKwpIsNewServiceRequested() \
          ((BOOL)(u8LAPKwpRequestStatus == cLAPKwpNewServiceIsRequested))

#define LAPKwpSetServiceIsTreated() \
          (u8LAPKwpRequestStatus = cLAPKwpServiceIsTreated)

#define LAPKwpIsServiceTreated() \
          ((BOOL)(u8LAPKwpRequestStatus == cLAPKwpServiceIsTreated))

#define LAPKwpSetServiceIsFinished() \
          (u8LAPKwpRequestStatus = cLAPKwpServiceIsFinished)

#define LAPKwpIsServiceFinished() \
          ((BOOL)(u8LAPKwpRequestStatus == cLAPKwpServiceIsFinished))

#define LAPKwpReadDiagnosticRequest(Index) \
         (mDATReadTable(U8Bit,DATKwpRxBuffer,Index, Default))

#define LAPKwpWriteDiagnosticResponse(Index,Value) \
         mDATWriteTable(U8Bit,DATKwpTxBuffer,Index,Value, Default)

#define LAPKwpGetPtrDiagnosticResponse(Index)  (&DATKwpTxBuffer[3+(Index)])

//------------------------------------------------------------------------------
// Exported functions
//------------------------------------------------------------------------------
extern void LAPKwpPrepareNegativeResponse(const U8 u8NRCodeP);
extern void LAPKwpPreparePositiveResponse(const U8 u8LengthP);
extern void LAPKwpInitialize(void);
extern U8   LAPKwpGetActiveSessionID(void);
extern void LAPKwpRerstoreLastSession(void);


#endif   // I_LAP_KWP_H 
