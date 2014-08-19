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
// Component:    DAT_TRP
// -----------------------------------------------------------------------------
// $Date:   Mar 22 2010 16:14:28  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_TRP/DAT_TRP.C-arc  $
// $Revision:   1.27  $
// -----------------------------------------------------------------------------  
//  $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_TRP/DAT_TRP.C-arc  $
// 
//    Rev 1.27   Mar 22 2010 16:14:28   amanevd
// Cm007334: (0==DO_DATA_IMMOBILIZERProtection) check before EEP_CDImmo increase
// 
//    Rev 1.26   Mar 01 2010 15:05:38   adzhelp
// Cm007334: Code review corrections
// 
//    Rev 1.25   Feb 25 2010 15:53:14   amanevd
// Cm007334: If Immo line is protected, DAT_TRP controls managing the line are not processed
// 
//    Rev 1.24   Feb 11 2010 17:11:36   amanevd
// Cm007463: LDBRefreshWatchDog() called before and after each LIBPcf function
// 
//    Rev 1.23   Feb 11 2010 16:25:58   amanevd
// Cm007463: LDBRefreshWatchDog() called before each LIBPcf function
// 
//    Rev 1.22   Feb 11 2010 16:19:04   amanevd
// Cm006992: "compt_nb_int" is incremented on sending START_AUTH
// 
//    Rev 1.21   Feb 08 2010 09:24:18   amanevd
// Cm006744: Perform 32-bit math operations only when values are changed
// 
//    Rev 1.20   Feb 03 2010 11:51:24   adzhelp
// Cm005245: Reordered header files inclusion
// 
//    Rev 1.19   Jan 22 2010 11:53:58   amanevd
// Cm006992: On ActivateDiag control check included prior send Stop control to LDB
// 
//    Rev 1.18   Jan 19 2010 14:42:56   amanevd
// Cm006992: "compt_nb_int" made as a full 8 bits counter incremented in case of faild or successful reception of the key RESPONSE
// 
//    Rev 1.17   Dec 15 2009 10:40:50   amanevd
// Cm005566: Defect is set only if PWR_IGN==1
// 
//    Rev 1.16   Dec 14 2009 10:52:16   amanevd
// Cm005566: Full Hardware Protection
// 
//    Rev 1.15   Nov 04 2009 16:32:10   amanevd
// Cm005566: Simplified Protection
// 
//    Rev 1.14   Oct 05 2009 13:52:08   amanevd
// Cm006307: DatTrpExportData.VirginKeyAuthentOk is set 1 when learning in Plant mode
// 
//    Rev 1.13   Oct 02 2009 14:03:04   amanevd
// Cm005807: Missing initial value of "compt_nb_int" set to 1
// 
//    Rev 1.12   Sep 17 2009 09:58:38   adzhelp
// Cm003277: DATTrpControl() defined as CALLT_TYPE
// 
//    Rev 1.11   Aug 07 2009 18:09:42   amanevd
// Cm005142: Implementation of Confidential Diagnostic
// 
//    Rev 1.10   Jul 14 2009 17:14:42   amanevd
// Cm005586: DiagKeyFrequency signal included
// 
//    Rev 1.9   May 21 2009 11:20:16   amanevd
// Cm003272: CCover and QAC justification - NO IMPACT ON REAL CODE
// 
//    Rev 1.8   May 18 2009 10:54:06   amanevd
// Cm003272L: Correction reagirding ILCR_DAT_TRP.xls, rev.: 1.0 - NO IMPACT ON REAL CODE
// 
//    Rev 1.7   May 11 2009 15:12:02   amanevd
// Cm003272 - Indent Change - NO IMPACT ON REAL CODE
// 
//    Rev 1.6   May 07 2009 11:30:00   amanevd
// Cm003272 - Finishing part 2 - pre-integration
// 
//    Rev 1.5   Apr 29 2009 13:12:30   amanevd
// Cm003272 - Intermediate part 3 
// - PRS compliance
// 
//    Rev 1.4   Apr 22 2009 19:23:40   amanevd
// Cm003272 - Finishing part 1 - pre-integration
// 
//    Rev 1.3   Feb 13 2009 14:52:10   amanevd
// Cm003272 - Intermediate part 1 - PRS compliance
// 
//    Rev 1.2   Feb 04 2009 15:12:34   amanevd
// Cm003272 - QAC fix
// 
//    Rev 1.1   Feb 04 2009 13:29:42   amanevd
// Cm003272 - Intermediate part 1
// - PRS compliance
// 
//    Rev 1.0   Jan 09 2009 14:03:58   amanevd
// Initial revision.
//=============================================================================

//-----------------------------------------------------------------------------
//  Body Identification
//-----------------------------------------------------------------------------
#define DAT_TRP  "DAT_TRP"

//-----------------------------------------------------------------------------
//  Included files
//
//  #include <system_file_name.h>
//  #include "project_file_name.h"
//-----------------------------------------------------------------------------
#include "tos.h"
#include "dat.h"
#include "ldb.h"
#include "lib_pcf.h"
#include "lib_rnd.h"
#include "dat_trp.h"
#include "dat_trp.hgr"

//-----------------------------------------------------------------------------
//  Local constants
//
//  #define cConstantName   ((tType) ConstantValue)
//-----------------------------------------------------------------------------

// Time out definition
#define cSendWriteCmdTimeOut    ((tTOSTimer) mTOSConvMsInTimerTick(60UL))
#define cSendDataToWriteTimeOut ((tTOSTimer) mTOSConvMsInTimerTick(60UL))
#define cIDEReadingTimeOut      ((tTOSTimer) mTOSConvMsInTimerTick(60UL))
#define cReadCmdTimeOut         ((tTOSTimer) mTOSConvMsInTimerTick(80UL))
#define cChallengeTimeOut       ((tTOSTimer) mTOSConvMsInTimerTick(80UL))
#define cControlTimeOut         ((tTOSTimer) mTOSConvMsInTimerTick(60UL))
#define cBlkPtrTimeOut          ((tTOSTimer) mTOSConvMsInTimerTick(60UL))
#define cWritingInTrpTimeOut    ((tTOSTimer) mTOSConvMsInTimerTick(40UL))

// Duration of the authentication time out
//QACJ 3443:amanevd: Last instance of mDATRead is a concatenation of mDATRead ## DataType## DataName ## TreatmentType()
#define mCalcTimeOutAuthent()   (mTOSConvMsInTimerTick((U32)(DatTrpLocalData.u16TimeOutTW2 = mDATRead( U16Bit, EEP_TimeOutTW2, Default))))

#define mTimeOutAuthent() (DatTrpLocalData.CalculatedTimeOutTW2 = \
                            (DatTrpLocalData.u16TimeOutTW2 == mDATRead( U16Bit, EEP_TimeOutTW2, Default)) \
                            ? DatTrpLocalData.CalculatedTimeOutTW2 \
    /*//QACJ 3443:amanevd: Last instance of mDATRead is a concatenation of mDATRead ## DataType## DataName ## TreatmentType()*/ \
                            : mCalcTimeOutAuthent())

// Used to generate encrypted signature for authentication challenge
#define cSignatureInitialValue  ((U32) 0xFFFFFFFFU)

#define cMaxAuthentTrialsCustomerMode       ((U8) 3)
#define cMaxAuthentTrialsLearningMode       ((U8) 2)

// Mask
#define cComputedCommandMask    ((tTrpCommand) 0x001FU)

#define cPageNumberMask         ((U8) 0x07U)
#define cFrequencyMask          ((U8) 0x30U)

#define cKeyLocked              ((U32)0x40000000U)
#define cKeyWithRF              ((U32)0x00000020U)
#define cKeyStandard            ((U32)0x00000010U)
#define cKeyStandardMsk         ((U32)0x000000F0U)
#define cKeyWithExtendedMemory  ((U32)0x00800000U)

#define cMaskBit0               ((U8) 0x01U)
#define cMaskBit1               ((U8) 0x02U)
#define cMaskBit2               ((U8) 0x04U)
#define cMaskBit3               ((U8) 0x08U)
#define cMaskBit4               ((U8) 0x10U)
#define cMaskBit5               ((U8) 0x20U)
#define cMaskBit6               ((U8) 0x40U)
#define cMaskBit7               ((U8) 0x80U)
// amanevd: 'Neg' constants make QAC to shut up. Must update them
// every time you update the original constant !!!
#define cNegMaskBit0            ((U8) 0xFEU)
#define cNegMaskBit1            ((U8) 0xFDU)
#define cNegMaskBit2            ((U8) 0xFBU)
#define cNegMaskBit3            ((U8) 0xF7U)
#define cNegMaskBit4            ((U8) 0xEFU)
#define cNegMaskBit5            ((U8) 0xDFU)
#define cNegMaskBit6            ((U8) 0xBFU)
#define cNegMaskBit7            ((U8) 0x7FU)

#define cMaskByte1              ((U32) 0x000000FFU)
#define cMaskByte2              ((U32) 0x0000FF00U)
#define cMaskByte3              ((U32) 0x00FF0000U)
#define cMaskByte4              ((U32) 0xFF000000U)
#define c24bitMask              ((U32) 0x00FFFFFFU)

#define cU8LowPart                ((U8) 0U)
#define cU8HighPart               ((U8) 1U)

#define cMaskU8LSB              ((U8) 0x0FU)
#define cMaskU8MSB              ((U8) 0xF0U)

// Maximum value of the default counters
#define cMaxWritingDefault                                  ((U8)   0xFFU)
#define cMaxAuthentDelayedCounter                           ((U8)   0xFFU)
#define cMaxAuthentFailureCounter                           ((U8)   0xFFU)
#define cMaxResynchroSuccessfulCounter                      ((U8)   0xFFU)
#define cMaxCDImmoCounter                                   ((U8)   0xFFU)

#define cTrpBufferSize          ((U8) 4)

// Transport ISK definition
#define cTranspIsk0             ((U8)0x4DU)
#define cTranspIsk1             ((U8)0x49U)
#define cTranspIsk2             ((U8)0x4BU)
#define cTranspIsk3             ((U8)0x52U)
#define cTranspIsk4             ((U8)0x4FU)
#define cTranspIsk5             ((U8)0x4EU)

// constant for shifting purposes
// amanevd: QAC expects 32 bit word, we are using 8 bit word
#ifndef _QAC_
#define cShift1                 ((U8) 1)
#define cShift2                 ((U8) 2)
#define cShift4                 ((U8) 4)
#define cShift8                 ((U8) 8)
#define cShift16                ((U8)16)
#define cShift24                ((U8)24)

#define cPage0                  ((U8) 0)
#define cPage1                  ((U8) 1)
#define cPage2                  ((U8) 2)
#define cPage3                  ((U8) 3)
#define cPage4                  ((U8) 4)
#define cPage5                  ((U8) 5)
#define cPage6                  ((U8) 6)

#else
#define cShift1                 ((U32) 1)
#define cShift2                 ((U32) 2)
#define cShift4                 ((U32) 4)
#define cShift8                 ((U32) 8)
#define cShift16                ((U32)16)
#define cShift24                ((U32)24)

#define cPage0                  ((U32) 0)
#define cPage1                  ((U32) 1)
#define cPage2                  ((U32) 2)
#define cPage3                  ((U32) 3)
#define cPage4                  ((U32) 4)
#define cPage5                  ((U32) 5)
#define cPage6                  ((U32) 6)
#endif

// Lenght in bit of data transmited to the transponder
#define cTrpOutState            ((U16) 1)
#define cAuthLength				((U16) 5)
#define cStartEXMLength			((U16) 5)
#define cCommandLength          ((U16) 10)
#define cPageLength             ((U16) 32)
#define cIdentifierLength       ((U16) 32)
#define cSignatureLength        ((U16) 32)
#define cChallengeLength        ((U16) 64)

#define cTrpAuth			    ((U8) 0xC0U)   // 11000 000
#define cStartEXMMode           ((U8) 0x38U)   // 00111 000
#define cDecrementBlockPointer  ((U16)0x00BAU) // 00101 11010
#define cIncrementBlockPointer  ((U16)0x009BU) // 00100 11011
#define cInitializeBlockPointer ((U16)0x00D9U) // 00110 11001

//-----------------------------------------------------------------------------
//  Local macros
//
//  #define mMacroName   (MacroDefinition)
//-----------------------------------------------------------------------------

// Flag's access macros
#define mSetFlagImmoAntAnswerReceived()   (DatTrpLocalData.u8TrpFlag |= cMaskBit0)
#define mClearFlagImmoAntAnswerReceived() (DatTrpLocalData.u8TrpFlag &= cNegMaskBit0)
#define mGetFlagImmoAntAnswerReceived()   ((DatTrpLocalData.u8TrpFlag & cMaskBit0) != 0)

#define mSetFlagAnswerReceivedOK()   (DatTrpLocalData.u8TrpFlag |= cMaskBit1)
#define mClearFlagAnswerReceivedOK() (DatTrpLocalData.u8TrpFlag &= cNegMaskBit1)
#define mGetFlagAnswerReceivedOK()   ((DatTrpLocalData.u8TrpFlag & cMaskBit1) != 0)

#define mMarkTrpOutActive()         (u8DATTrpOutState = 1)
#define mMarkTrpOutInactive()       (u8DATTrpOutState = 0)


//-----------------------------------------------------------------------------
//  Local types
//
//  struct  sStructureName { ... };
//  union   uUnionName { ... };
//  enum    eEnumerationName { ... };
//  typedef Expression tTypeName;
//-----------------------------------------------------------------------------

typedef tAddress tTrpCommand;

typedef struct tDatTrpLocalDataType
{
    // Buffer used to received data from LDB_TRP
    U32         u32DataBuffer;
    // Exchange identifier buffer
    U8          ExchIdentifier[cTrpBufferSize];
    // Message DAT_TRP <=> LDB_TRP
    tMsg        TransponderMessage;

    // Timer used to manage communication time Out between the BCM and the Immobilizer Antenna
    tTOSTimer   TimeOutWaitingForImmoANTReply;
    // Timer used to manage the delay of writing in the EEP of the transponder
    tTOSTimer   TimeOutWaitingForWriting;
    // Timer used to manage the authentication time out
    tTOSTimer   AuthenticationTimeOut;
    // Data used to define the current command time out
    tTOSTimer   CommandTimeOut;
    tTOSTimer   CalculatedTimeOutTW2;

    tTrpCommand WritingCommand;
    tTrpCommand ReadingCommand;
    tTrpCommand InvertedReadingCommand;

    U16         u16TimeOutTW2;

    // Flags
    U8          u8TrpFlag;
    
    U8          u8ReadOrWriteNumberOfTry;
    U8          u8AuthentLocalCounter;
    U8          Buffer[cTrpBufferSize];

    // flag indication stop authentication service is requested;
    BOOL        bStopAuthentService;
    BOOL        bDiagnosticRunning;
}tDatTrpLocalData;

//-----------------------------------------------------------------------------
//  Local data
//
//  static  tType   VariableName;
//  static  tType*  pVariableName; 
//-----------------------------------------------------------------------------

// Dat Trp private Data
static tDatTrpLocalData DatTrpLocalData;

//-----------------------------------------------------------------------------
//  Constant local data
//
//  static const tType  VariableName;
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//  Exported data
//
//  tType   LAYCmpVariableName;   (LAY: 3 characters to identify the layer)
//  tType*  pLAYCmpVariableName;  (Cmp: 3 characters to identify this component)
//-----------------------------------------------------------------------------

tDatTrpExportData DatTrpExportData;

U8 u8DATTrpOutState;
//-----------------------------------------------------------------------------
//  Constant exported data
//
//              (LAY: 3 characters to identify the layer)
//              (Cmp: 3 characters to identify this component)
// 
//  const tType   LAYCmpVariableName;
//-----------------------------------------------------------------------------
//QACJ 3211:amanevd: The constant is used in 'mLIBmemcmp' macro execution as well as it is exported
const U8 DATTrpTransportISK[cDATTrpISKLengthInBytes] = 
    {cTranspIsk0,cTranspIsk1,cTranspIsk2,cTranspIsk3,cTranspIsk4,cTranspIsk5};

//-----------------------------------------------------------------------------
//  Local function prototypes
//  
//  static tTypeRetour FunctionName(tTypeArgument1 ArgumentName1, ... );
//-----------------------------------------------------------------------------
static tTrpCommand ComputeCommandWithPageNumber(const U8 u8PageNumberP, 
                                                const tTrpCommand tStandardCommandP);
static tTrpCommand EncodeCommand(tTrpCommand tOriginalCommandP);

static U32 U32ReverseByteOrder(const U32 u32TargetP);
static MEM_TYPE void SignalCurrentKeyFrequency(void);

#ifdef X90_PROJECT
static MEM_TYPE void DATTrpControl_Static(const tCtrl Ctrl);
static MEM_TYPE void DATTrpInit_Static(void);
static MEM_TYPE BOOL DATTrpAnswerChallengeReceivedOK_Static(void);
static MEM_TYPE void DATTrpCalculateChallenge_Static(void);
static MEM_TYPE BOOL DATTrpIdentifierReceivedOK_Static(void);
static MEM_TYPE void DATTrpSendReadCommand_Static(void);
static MEM_TYPE BOOL DATTrpNewAuthenticationAuthorized_Static(void);
static MEM_TYPE void DATTrpResynchronizationNotSuccess_Static(void);
static MEM_TYPE void DATTrpResynchronizationSuccess_Static(void);
static MEM_TYPE void DATTrpSendInvertedReadCommand_Static(void);
static MEM_TYPE BOOL DATTrpReadAndCompareOK_Static(void);
static MEM_TYPE void DATTrpSendWriteCommand_Static(void);
static MEM_TYPE void DATTrpSendDataToWrite_Static(void);
static MEM_TYPE BOOL DATTrpWriteCommandReceivedOK_Static(void);
static MEM_TYPE BOOL DATTrpPage3InvertedDataReceivedOK_Static(void);
static MEM_TYPE void DATTrpStartAuthenticationService_Static(void);
static MEM_TYPE void DATTrpAuthenticationNotSuccess_Static(void);
static MEM_TYPE void DATTrpAuthenticationSuccess_Static(void);
static MEM_TYPE void DATTrpSendStartAuth_Static(void);
static MEM_TYPE void DATTrpSendWakeUpControl_Static(void);
static MEM_TYPE BOOL DATTrpNewTryAuthorized_Static(void);
static MEM_TYPE BOOL DATTrpInLearningModeAndLessThanMaxTrials_Static(void);
#endif

//=============================================================================
//=========================== LOCAL FUNCTIONS =================================
//=============================================================================

//=============================================================================
//  DESCRIPTION :
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//=============================================================================
//static type FunctionName(...)

//=============================================================================
//  DESCRIPTION : Compute a transponder command with a page number. It used for
//                reading and writing command.
//  
//  PARAMETERS (Type,Name,Min,Max) : U8 ucPageNumberP : page number
//                                   tTrpCommand StandardCommandP : base command
//
//  RETURN VALUE :  Computed command.
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//=============================================================================
static tTrpCommand ComputeCommandWithPageNumber(const U8 u8PageNumberP, 
                                                const tTrpCommand tStandardCommandP)
{
    tTrpCommand tComputedCommandL;

    tComputedCommandL = tStandardCommandP | (u8PageNumberP & cPageNumberMask);
    tComputedCommandL =   (tComputedCommandL << (cShift4 + cShift1)) 
    | ((tTrpCommand)(~tComputedCommandL) & cComputedCommandMask);

    return tComputedCommandL;
}
//=============================================================================
//  DESCRIPTION : Encode a transponder command.
//  
//  PARAMETERS (Type,Name,Min,Max) : tTrpCommand OriginalCommand : unencoded command
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//=============================================================================
static tTrpCommand EncodeCommand(tTrpCommand tOriginalCommandP)
{
    tOriginalCommandP <<= cShift4 + cShift2;
    LIBPcfCipheredData =  (U32)((tOriginalCommandP << cShift8) & cMaskByte2)
    | (U32)((tOriginalCommandP >> cShift8) & cMaskByte1);

    LDBRefreshWatchDog();
    LIBPcfCipherFunction(cCommandLength);
    LDBRefreshWatchDog();

    LIBPcfCipheredData =  ((LIBPcfCipheredData << cShift8) & cMaskByte2)
    | ((LIBPcfCipheredData >> cShift8) & cMaskByte1);

    return ((tTrpCommand) LIBPcfCipheredData);
}

//=============================================================================
//  DESCRIPTION : Reverse Byte Order in U32
//  
//  PARAMETERS (Type,Name,Min,Max) : 
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//=============================================================================
static U32 U32ReverseByteOrder(const U32 u32TargetP)
{
    return    (((U32)(u32TargetP) >> cShift24) & cMaskByte1)
            | (((U32)(u32TargetP) >> cShift8)  & cMaskByte2)
            | (((U32)(u32TargetP) << cShift8)  & cMaskByte3)
            | (((U32)(u32TargetP) << cShift24) & cMaskByte4);
}

//=============================================================================
//  DESCRIPTION : Indicate the key frequency for diagnostic services
//  
//  PARAMETERS (Type,Name,Min,Max) :  none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//=============================================================================
static MEM_TYPE void SignalCurrentKeyFrequency(void)
{
    switch (DatTrpExportData.FrequencyOfPresentKey)
    {
        case cDATTrpKey315Mhz:
        DatTrpExportData.DiagKeyFrequency = cDATKeyFrequency315Mhz;
        break;

        case cDATTrpKey315MhzSmall:
        DatTrpExportData.DiagKeyFrequency = cDATKeyFrequency315MhzSmall;
        break;

        case cDATTrpKey433Mhz:
        DatTrpExportData.DiagKeyFrequency = cDATKeyFrequency433Mhz;
        break;

        //CCOV: amanevd: Cannot be covered because this default case rises explicit assert
        default:
        mLIBassert(cFalse);
        break;
    }
}

//=============================================================================
//============================ EXPORTED FUNCTIONS =============================
//=============================================================================

//*****************************************************************************
//  DESCRIPTION         : Component initialization.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
void DATTrpInit(void)
{
#ifdef X90_PROJECT
    DATTrpInit_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DATTrpInit_Static(void)
{
#endif

#ifndef X90_PROJECT
    // DatTrpExportData and  DatTrpLocalData are placed in zero initialized RAM

    DatTrpExportData.ActiveTestMode                     = 0;
    DatTrpExportData.AuthentInLearningMode              = 0;
    DatTrpExportData.WriteSecretKeyHigh                 = 0;

    DatTrpExportData.IdentifierOfPresentKeyIsReceived   = 0;
    DatTrpExportData.IdentifierOfPresentKeyIsValid      = 0;
    DatTrpExportData.ResponseToChallengeIsPresent       = 0;
    DatTrpExportData.ResponseToChallengeIsValid         = 0;
    DatTrpExportData.PresentKeyLocked                   = 0;
    DatTrpExportData.KeyWithRF						    = 0;
    DatTrpExportData.KeyStandard					    = 0;
    DatTrpExportData.FrequencyOfPresentKey              = 0;
    DatTrpExportData.DiagKeyFrequency                   = 0;
    DatTrpExportData.IdentifierOfPresentKey             = 0;
    DatTrpExportData.DataRead                           = 0;
    DatTrpExportData.ResynchronizationValue             = 0;
    DatTrpExportData.VirginKeyAuthentOk                 = 0;
    DatTrpExportData.KeyLearningElapsed                 = 0;
    DatTrpExportData.WriteAccessWritingError            = 0;
    DatTrpExportData.WriteAccessReadingError            = 0;
    DatTrpExportData.AuthentTryCounter                  = 0;

    DatTrpLocalData.u8AuthentLocalCounter   = 0;
    DatTrpLocalData.bStopAuthentService = 0;
    DatTrpLocalData.bDiagnosticRunning  = 0;

#endif

    DatTrpExportData.IndexOfKeyRecognized               = cDATTrpInvalidKeyIndex;

    DatTrpExportData.AuthenticationState    = cDATTrpServiceNotStarted;
    DatTrpExportData.WakeUpControlState     = cDATTrpServiceNotStarted;
    DatTrpExportData.SleepControlState      = cDATTrpServiceNotStarted;
    DatTrpExportData.StopControlState       = cDATTrpServiceNotStarted;
    DatTrpExportData.WriteAccessState       = cDATTrpServiceNotStarted;
    DatTrpExportData.ResynchronizationState = cDATTrpServiceNotStarted;
    DatTrpExportData.LastVerlogStatus       = cDATTrpVerlogOff;

    mClearFlagImmoAntAnswerReceived();
    mClearFlagAnswerReceivedOK();

    //  Explicitly put the antena in sleep mode on system startup
    LDBControl(cLDBChannelTrp, cLDBTrpSleep);
}
//*****************************************************************************
//  DESCRIPTION         : Start an authentication service.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
void DATTrpStartAuthenticationService(void)
{
#ifdef X90_PROJECT
    DATTrpStartAuthenticationService_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DATTrpStartAuthenticationService_Static(void)
{
#endif

    //-----------------------------------//
    // Clear authentication output datas
    //-----------------------------------//
    DatTrpExportData.IdentifierOfPresentKeyIsReceived = 0;
    DatTrpExportData.IdentifierOfPresentKeyIsValid    = 0;
    DatTrpExportData.ResponseToChallengeIsPresent     = 0;
    DatTrpExportData.ResponseToChallengeIsValid       = 0;
    DatTrpExportData.PresentKeyLocked                 = 0;
    DatTrpExportData.KeyWithRF                        = 0;
    DatTrpExportData.FrequencyOfPresentKey            = 0;
    DatTrpExportData.IdentifierOfPresentKey           = 0;
    DatTrpExportData.IndexOfKeyRecognized             = cDATTrpInvalidKeyIndex;
    DatTrpExportData.VirginKeyAuthentOk               = 0;

    DatTrpExportData.AuthenticationState    = cDATTrpServiceInProgress;
    DatTrpExportData.AuthentTryCounter      = 0;
    DatTrpLocalData.u8AuthentLocalCounter   = 0;

    TOSStartTimer(&DatTrpLocalData.AuthenticationTimeOut);

    TOSSeqActivateGraph(cTOSSeqGraphIdDATTrpAuthentication);
}
//*****************************************************************************
//  DESCRIPTION         : Start a DAT_TRP control.
//
//  PARAMETERS          : tCtrl Ctrl = cDATTrpWakeUp, cDATTrpSleep, cDATTrpStop,
//  (Type,Name,Min,Max)                cDATTrpAuthenticate, cDATTrpWritePage,
//                                     cDATTrpReadPage, cDATTrpResynchronize
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
CALLT_TYPE void DATTrpControl(const tCtrl Ctrl)
{
#ifdef X90_PROJECT
    DATTrpControl_Static(Ctrl);
}
#pragma optimize=no_inline
static MEM_TYPE void DATTrpControl_Static(const tCtrl Ctrl)
{
#endif
    switch (Ctrl)
    {
        case cDATTrpWakeUp:

        if(     (cFalse == mDATRead(U1Bit, DO_DATA_IMMOBILIZERProtection, Default))
            &&  (cFalse == DatTrpLocalData.bDiagnosticRunning)
          )
        {
            DatTrpExportData.WakeUpControlState = cDATTrpServiceInProgress;
            mMarkTrpOutActive();
            LDBControl(cLDBChannelTrp, cLDBTrpWakeUp);
        }
        else
        {
            DatTrpExportData.WakeUpControlState = cDATTrpServiceNotSuccessful;
        }
        break;

        case cDATTrpSleep:

        if(     (cFalse == mDATRead(U1Bit, DO_DATA_IMMOBILIZERProtection, Default))
            &&  (cFalse == DatTrpLocalData.bDiagnosticRunning)
          )
        {
            // Prevention of simultaneous access of antena by immo or exm components
            // like:    if (DatTrpLocalData.CipheredCommunication == cTrue)                
            DatTrpExportData.SleepControlState = cDATTrpServiceSuccessful;
            mMarkTrpOutActive();
            LDBControl(cLDBChannelTrp, cLDBTrpSleep);
        }
        else
        {
            DatTrpExportData.SleepControlState = cDATTrpServiceNotSuccessful;
        }

        break;

        case cDATTrpStop:
        {
            DatTrpExportData.StopControlState = cDATTrpServiceInProgress;
            LDBControl(cLDBChannelTrp, cLDBTrpStop);
            mMarkTrpOutInactive();
        }
        break;

        case cDATTrpAuthenticate:

        if(     (cFalse == mDATRead(U1Bit, DO_DATA_IMMOBILIZERProtection, Default))
            &&  (cDATTrpServiceInProgress != DatTrpExportData.WriteAccessState)
            &&  (cFalse == DatTrpLocalData.bDiagnosticRunning)
          )
        {
            DatTrpExportData.AuthenticationState = cDATTrpServiceInProgress;
            DatTrpLocalData.bStopAuthentService = 0;
            mMarkTrpOutActive();
            DATTrpStartAuthenticationService();
        }
        else
        {
            DatTrpExportData.AuthenticationState = cDATTrpServiceNotSuccessful;
        }

        break;

        case cDATTrpWritePage:

        if(     (cFalse == mDATRead(U1Bit, DO_DATA_IMMOBILIZERProtection, Default))
            &&  (cFalse == DatTrpLocalData.bDiagnosticRunning)
          )
        {
            DatTrpLocalData.u8ReadOrWriteNumberOfTry = 0;
            DatTrpExportData.WriteAccessWritingError = 0;
            DatTrpExportData.WriteAccessReadingError = 0;
            DatTrpLocalData.WritingCommand           = ComputeCommandWithPageNumber(DatTrpExportData.PageNumber, cLDBTrpWrPage);
            DatTrpLocalData.ReadingCommand           = ComputeCommandWithPageNumber(DatTrpExportData.PageNumber, cLDBTrpRdPage);
            DatTrpExportData.WriteAccessState   = cDATTrpServiceInProgress;
            mMarkTrpOutActive();
            TOSSeqActivateGraph(cTOSSeqGraphIdDATTrpWriteAccess);
        }
        else
        {
            DatTrpExportData.WriteAccessState   = cDATTrpServiceNotSuccessful;
        }

        break;

        case cDATTrpResynchronize:

        if(     (cFalse == mDATRead(U1Bit, DO_DATA_IMMOBILIZERProtection, Default))
            &&  (cFalse == DatTrpLocalData.bDiagnosticRunning)
          )
        {
            DatTrpLocalData.u8ReadOrWriteNumberOfTry     = 0;
            DatTrpExportData.ResynchronizationValue = LIBCalculateRandomNb(TOSClock);
            DatTrpExportData.DataToWrite            = DatTrpExportData.ResynchronizationValue;
            DatTrpLocalData.WritingCommand               = cLDBTrpResync;
            DatTrpLocalData.ReadingCommand               = cLDBTrpRdSync;

            DatTrpExportData.ResynchronizationState = cDATTrpServiceInProgress;
            mMarkTrpOutActive();
            TOSSeqActivateGraph(cTOSSeqGraphIdDATTrpResynchronization);
        }
        else
        {
            DatTrpExportData.ResynchronizationState = cDATTrpServiceNotSuccessful;
        }
        break;

        case cDATTrpInitDiagInfo:
        {
            DatTrpExportData.IdentifierOfPresentKeyIsReceived  = 0;
            DatTrpExportData.IdentifierOfPresentKeyIsValid     = 0;
            DatTrpExportData.ResponseToChallengeIsPresent      = 0;
            DatTrpExportData.ResponseToChallengeIsValid        = 0;
            DatTrpExportData.PresentKeyLocked                  = 0;
            DatTrpExportData.KeyWithRF                         = 0;
            DatTrpExportData.KeyStandard     	               = 0;
            DatTrpExportData.FrequencyOfPresentKey             = 0;
            DatTrpExportData.DiagKeyFrequency                  = cDATKeyInvalidFrequency;
            DatTrpExportData.IdentifierOfPresentKey            = 0;
            DatTrpExportData.IndexOfKeyRecognized              = cDATTrpInvalidKeyIndex;
            DatTrpExportData.DataRead                          = 0;
            DatTrpExportData.AuthenticationState               = cDATTrpServiceNotStarted;   
            DatTrpExportData.ResynchronizationValue            = 0;
            DatTrpExportData.VirginKeyAuthentOk                = 0;
        }
        break;

        case cDATTrpStopAuthentService:
        {
            DatTrpLocalData.bStopAuthentService = cTrue;
        }
        break;

        case cDATTrpActivateDiag:
        { 
            if (    (cDATTrpServiceInProgress == DatTrpExportData.WriteAccessState)
                 || (cDATTrpServiceInProgress == DatTrpExportData.AuthenticationState)
               )
            {
                LDBControl(cLDBChannelTrp, cLDBTrpStop);
            }

            mMarkTrpOutInactive();
            DatTrpLocalData.bDiagnosticRunning = cTrue;
        }
        break;

        case cDATTrpDeactivateDiag:
        {
            DatTrpLocalData.bDiagnosticRunning = cFalse;
        }
        break;

        case cDATTrpTfcDiag:

        if(     (cFalse == mDATRead(U1Bit, DO_DATA_IMMOBILIZERProtection, Default))
             && (cDATTrpServiceInProgress != DatTrpExportData.WriteAccessState)
             && (cFalse == DatTrpLocalData.bDiagnosticRunning)
          )
        {
            DatTrpExportData.AuthenticationState = cDATTrpServiceInProgress;
            mMarkTrpOutActive();
            TOSSeqActivateGraph(cTOSSeqGraphIdDATTrpTfcDiag);
        }
        else
        {
            DatTrpExportData.AuthenticationState = cDATTrpServiceNotSuccessful;
        }
        break;

        //CCOV: amanevd: Cannot be covered because this default case rises explicit assert
        default:
        {
            mLIBassert(cFalse);
        }
        break;
    }
}

//*****************************************************************************
//  DESCRIPTION         : Update of the flags of detection of hardware defaults.
//
//  PARAMETERS          : tCtrl Ctrl = cLDBTrpWakeUp, cLDBTrpSleep, cLDBTrpStop
//  (Type,Name,Min,Max)   tStatus Status = cLDBCorrect, cLDBError
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
//QACJ 3227:amanevd: The function is declared without use of 'const' in standard components
MEM_TYPE void DATTrpCallBackCtrl(tCtrl Ctrl)
{
    U8 u8TempL;

    mMarkTrpOutInactive();
    if(cFalse != mDATRead(U1Bit, PWR_IGN, Immediate))
    {
        switch (Ctrl)
        {
            case cLDBTrpShortCircuitToBat :
            mDATWrite(U1Bit, DefTrpShortCircuitToGnd, 0, Default);
            mDATWrite(U1Bit, DefTrpShortCircuitToBat, 1, Default);
            mDATWrite(U1Bit, EEP_DefTrpToBat, 1, Default);
            if(cFalse == mDATRead(U1Bit, DO_DATA_IMMOBILIZERProtection, Default))
            {
                u8TempL = mDATRead(U8Bit, EEP_CDImmo, Default);
                if(u8TempL < cMaxCDImmoCounter)
                {
                    u8TempL++;
                    mDATWrite(U8Bit, EEP_CDImmo, u8TempL, Default);
                }
            }
            mDATWrite(U1Bit, DO_DATA_IMMOBILIZERProtection, 1, Default);
            break;

            case cLDBTrpShortCircuitToGnd :
            mDATWrite(U1Bit, DefTrpShortCircuitToGnd, 1, Default);
            mDATWrite(U1Bit, DefTrpShortCircuitToBat, 0, Default);
            mDATWrite(U1Bit, EEP_DefTrpToGnd, 1, Default);
            break;

            case cLDBTrpNoError :
            // Clear all error
            mDATWrite(U1Bit, DefTrpShortCircuitToBat, 0, Default);
            mDATWrite(U1Bit, DefTrpShortCircuitToGnd, 0, Default);
            break;

            //CCOV: amanevd: Cannot be covered because this default case rises explicit assert
            default :
            mLIBassert(cFalse);
            break;
        }
    }
}

//*****************************************************************************
//  DESCRIPTION         : Signals the end of a sending with address.
//
//  PARAMETERS          : tAddress Address = transponder commands
//  (Type,Name,Min,Max)   tStatus Status = cLDBCorrect, cLDBError
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
//QACJ 3227:amanevd: The function is declared without use of 'const' in standard components
//QACJ 3227:amanevd: The function is declared without use of 'const' in standard components
MEM_TYPE void DATTrpCallBackTxWithAddr(tAddress Address, tStatus Status)
{  
    mLIBassert((Status == cLDBCorrect) || (Status == cLDBError));

    mMarkTrpOutInactive();

    if (Address != cLDBTrpStartAuth)
    {
        mSetFlagImmoAntAnswerReceived();

        if (Status == cLDBCorrect)
        {
            mSetFlagAnswerReceivedOK();
        }
        else
        {
            mClearFlagAnswerReceivedOK();
        }
    }
    // else : in case of Start authentication service, this call back is ignored.
}

//*****************************************************************************
//  DESCRIPTION         : Signals the end of a control and its status.
//
//  PARAMETERS          : tCtrl Ctrl = cLDBTrpWakeUp, cLDBTrpSleep, cLDBTrpStop
//  (Type,Name,Min,Max)   tStatus Status = cLDBCorrect, cLDBError
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
//QACJ 3227:amanevd: The function is declared without use of 'const' in standard components
//QACJ 3227:amanevd: The function is declared without use of 'const' in standard components
MEM_TYPE void DATTrpCallBackEndCtrl(tCtrl Ctrl, tStatus Status)
{
    mLIBassert((Ctrl == cLDBTrpWakeUp) || (Ctrl == cLDBTrpSleep));
    mLIBassert((Status == cLDBCorrect) || (Status == cLDBError));

    mSetFlagImmoAntAnswerReceived();
    mMarkTrpOutInactive();

    if (Status == cLDBCorrect)
    {
        mSetFlagAnswerReceivedOK();
    }
    else
    {
        mClearFlagAnswerReceivedOK();
    }

    if ((Ctrl == cLDBTrpSleep) && (DatTrpExportData.SleepControlState == cDATTrpServiceInProgress))
    {
        DatTrpExportData.SleepControlState = cDATTrpServiceSuccessful;
    }
    else 
    {
        if ((Ctrl == cLDBTrpSleep) && (DatTrpExportData.StopControlState == cDATTrpServiceInProgress))
        {
            DatTrpExportData.StopControlState = cDATTrpServiceSuccessful;
        }
        else 
        {
            if (        (Ctrl == cLDBTrpWakeUp) 
               &&   (DatTrpExportData.WakeUpControlState == cDATTrpServiceInProgress))
            {
                if(Status == cLDBCorrect)
                {
                    DatTrpExportData.WakeUpControlState = cDATTrpServiceSuccessful;
                }
                else
                {
                    DatTrpExportData.WakeUpControlState = cDATTrpServiceNotSuccessful;
                }
            }
            else 
            {
            }
        }
    }
}

//*****************************************************************************
//  DESCRIPTION         : Indicate that the LDB has received data.
//
//  PARAMETERS          : tStatus Status = cLDBCorrect
//  (Type,Name,Min,Max)   tMsg*   pMsg
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
//QACJ 3206:amanevd: The pMsg parameter is used inside 'mLIBmemcmp' macro execution in function body
//QACJ 3206:amanevd: The pMsg parameter is used inside 'mLIBmemcmp' macro execution in function body
MEM_TYPE void DATTrpCallBackRxSpontWithoutAddr(tStatus Status, tMsg* pMsg)
{
    mLIBassert(Status == cLDBCorrect);

    mMarkTrpOutInactive();
    mSetFlagImmoAntAnswerReceived();
    mSetFlagAnswerReceivedOK();
    mLIBmemcpy((U8*)&DatTrpLocalData.u32DataBuffer, 
        pMsg->pBuffer, 
        sizeof(DatTrpLocalData.u32DataBuffer));
}

//*****************************************************************************
//  DESCRIPTION         : Signals the end of a receiving with address.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : cFalse or cTrue
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
//QACJ 3227:amanevd: The function is declared without use of 'const' in standard components
//QACJ 3206:amanevd: Address parameter is declared in standart interface LDBParam, it could not be changed.
MEM_TYPE void DATTrpCallBackRxWithAddr(tAddress Address, tStatus Status)
{
    mLIBassert((Status == cLDBCorrect) || (Status == cLDBError));

    mSetFlagImmoAntAnswerReceived();
    mMarkTrpOutInactive();

    if (Status == cLDBCorrect)
    {
        mSetFlagAnswerReceivedOK();
    }
    else
    {
        mClearFlagAnswerReceivedOK();
    }
}

//*****************************************************************************
//  DESCRIPTION         : Test if challenge received is valid
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : cFalse or cTrue
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
BOOL DATTrpAnswerChallengeReceivedOK(void)
{
#ifdef X90_PROJECT
    return DATTrpAnswerChallengeReceivedOK_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL DATTrpAnswerChallengeReceivedOK_Static(void)
{
#endif

    BOOL bResultL = cFalse;

    if (mGetFlagAnswerReceivedOK())
    {
        mLIBassert((cTrue == (BOOL)DatTrpExportData.AuthentInLearningMode) 
            || (DatTrpExportData.IndexOfKeyRecognized < cDATTrpMaxNumberOfKey));

        DatTrpExportData.ResponseToChallengeIsPresent = 1;

        //-------------------------------//
        // Decoding of Page 3 of Block 0
        //-------------------------------//
        DatTrpExportData.RepToChallange = DatTrpLocalData.u32DataBuffer;
        LIBPcfCipheredData = U32ReverseByteOrder(DatTrpLocalData.u32DataBuffer);
        LDBRefreshWatchDog();
        LIBPcfCipherFunction(cPageLength);
        LDBRefreshWatchDog();
        DatTrpExportData.DataRead  = U32ReverseByteOrder(LIBPcfCipheredData);
        DatTrpExportData.RepToChallangeDecrypt = DatTrpExportData.DataRead;

        if ((BOOL)DatTrpExportData.AuthentInLearningMode == cFalse)
        {
            //---------------------------------------//
            // Update key informations
            //---------------------------------------//
            DatTrpExportData.PresentKeyLocked = ((DatTrpExportData.DataRead & cKeyLocked) == cKeyLocked);
            DatTrpExportData.KeyWithRF = ((DatTrpExportData.IdentifierOfPresentKey & cKeyWithRF) == cKeyWithRF);
            DatTrpExportData.KeyStandard = ((DatTrpExportData.IdentifierOfPresentKey & cKeyStandardMsk) == cKeyStandard);
            DatTrpExportData.FrequencyOfPresentKey = (U8)(DatTrpExportData.DataRead >> cShift16) & cFrequencyMask;
            DatTrpExportData.KeyWithExtendedMemory = ((DatTrpExportData.DataRead & cKeyWithExtendedMemory) == cKeyWithExtendedMemory);       
            // Update of DiagKeyFrequency signal
            SignalCurrentKeyFrequency();
            //-------------------------------------------------------------------//
            // If received password tag is known by the BCM or if Learning Mode  
            // is in progress, the challenge is accepted.
            //-------------------------------------------------------------------//    
            bResultL = (BOOL)( ((DatTrpExportData.DataRead & c24bitMask) == mDATReadTable(U32Bit, EEP_PwdTag, DatTrpExportData.IndexOfKeyRecognized, Default)));

            DatTrpExportData.ResponseToChallengeIsValid = bResultL;
        }
        else
        {
            //------------------------------------------------------------------//
            // Prepare inverted Page3 reading to ensure good Page3 and good IDE
            //------------------------------------------------------------------//
            DatTrpLocalData.InvertedReadingCommand  = 
                ComputeCommandWithPageNumber(cPage3, cLDBTrpRdPageInv);

            bResultL = cTrue;
        }
    }

    return bResultL;
}
//*****************************************************************************
//  DESCRIPTION         : Authentication service not success
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document (REQ: prsFS_IMMO-684)
//
//*****************************************************************************
void DATTrpAuthenticationNotSuccess(void)
{
#ifdef X90_PROJECT
    DATTrpAuthenticationNotSuccess_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DATTrpAuthenticationNotSuccess_Static(void)
{
#endif

    U8 u8AuthentFailureCounterL = mDATRead(U8Bit, EEP_AuthentFailureCounter, Default);

    mLIBassert(DatTrpExportData.AuthenticationState == cDATTrpServiceInProgress);

    if(u8AuthentFailureCounterL < cMaxAuthentFailureCounter)
    {
        u8AuthentFailureCounterL++;
        mDATWrite(U8Bit, EEP_AuthentFailureCounter, u8AuthentFailureCounterL, Default);
    }

    mDATWrite(U8Bit, EEP_AuthentDelayedCounter, 0, Default);

    DatTrpExportData.AuthenticationState = cDATTrpServiceNotSuccessful;
}
//*****************************************************************************
//  DESCRIPTION         : Authentication service success
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
void DATTrpAuthenticationSuccess(void)
{
#ifdef X90_PROJECT
    DATTrpAuthenticationSuccess_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DATTrpAuthenticationSuccess_Static(void)
{
#endif

    REG u32ResL;

    mLIBassert(DatTrpExportData.AuthenticationState == cDATTrpServiceInProgress);

    //QACJ 0543:amanevd: Result of mLIBmemcmp() expansion to NOP() in LIB.h Authentication with transport ISK (virgin key test mode only)
    u32ResL = (REG)mLIBmemcmp(&DatTrpExportData.ISKForAuthent[0],
                DATTrpTransportISK,
                cDATTrpISKLengthInBytes);

    if ((REG)0 == u32ResL)
    {
        DatTrpExportData.VirginKeyAuthentOk = 1;
    }
    // prsFS_IMMO-1107
    else if(cDATFactoryMode == mDATRead(U8Bit, LearningModeInProgress, Default))
    {
        DatTrpExportData.VirginKeyAuthentOk = 1;
    }
    else
    {
        // Nothing to do
    }

    // Clear all error
    mDATWrite(U1Bit, DefTrpShortCircuitToBat, 0, Default);
    mDATWrite(U1Bit, DefTrpShortCircuitToGnd, 0, Default);
    DatTrpExportData.AuthenticationState = cDATTrpServiceSuccessful;
}

//*****************************************************************************
//  DESCRIPTION         : TfcDiag service not success
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document (REQ: prsFS_IMMO-684)
//
//*****************************************************************************
void DATTrpTfcDiagNotSuccess(void)
{
    DatTrpExportData.AuthenticationState = cDATTrpServiceNotSuccessful;
}

//*****************************************************************************
//  DESCRIPTION         : TfcDiag service success
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
void DATTrpTfcDiagSuccess(void)
{
    DatTrpExportData.AuthenticationState = cDATTrpServiceSuccessful;
}

//*****************************************************************************
//  DESCRIPTION         : Compute and send the authentication challenge.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
void DATTrpCalculateChallenge(void)
{
#ifdef X90_PROJECT
    DATTrpCalculateChallenge_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DATTrpCalculateChallenge_Static(void)
{
#endif

    //--------------------------//
    // Initialize TAG algorithm
    //--------------------------//
    LIBPcfRandomNumber = LIBCalculateRandomNb(TOSClock);
    pLIBPcfSecretKey   = DatTrpExportData.ISKForAuthent;  
    DatTrpLocalData.ExchIdentifier[cPage0] = 
        (U8)((DatTrpExportData.IdentifierOfPresentKey >> cShift24) & cMaskByte1);
    DatTrpLocalData.ExchIdentifier[cPage1] = 
        (U8)((DatTrpExportData.IdentifierOfPresentKey >> cShift16) & cMaskByte1);
    DatTrpLocalData.ExchIdentifier[cPage2] = 
        (U8)((DatTrpExportData.IdentifierOfPresentKey >> cShift8 ) & cMaskByte1);
    DatTrpLocalData.ExchIdentifier[cPage3] = 
        (U8)(DatTrpExportData.IdentifierOfPresentKey & cMaskByte1);

    pLIBPcfIdentifier = DatTrpLocalData.ExchIdentifier;
    LDBRefreshWatchDog();
    LIBPcfInitialize();

    //----------------------------------//
    // Generate the encrypted signature
    //----------------------------------//
    LIBPcfCipheredData = cSignatureInitialValue;
    LDBRefreshWatchDog();
    LIBPcfCipherFunction(cSignatureLength);
    LDBRefreshWatchDog();
    LIBPcfRandomNumber = U32ReverseByteOrder(LIBPcfRandomNumber);
    LIBPcfCipheredData = U32ReverseByteOrder(LIBPcfCipheredData);

    //------------------------------------------//
    // Indicate that answer is not received yet
    //------------------------------------------//
    mClearFlagImmoAntAnswerReceived();
    mClearFlagAnswerReceivedOK();

    //------------------------------------------------//
    // Prepare the message to send to the transponder
    //------------------------------------------------//
    DatTrpExportData.ExchChallenge.ulRandomNumber    = LIBPcfRandomNumber;
    DatTrpExportData.ExchChallenge.ulSignature       = LIBPcfCipheredData;
    DatTrpLocalData.TransponderMessage.Lng          = cChallengeLength;
    //QACJ 0310:amanevd: LIBPcf knows how data is structured in tChallange type so cast to (U8*) is not a problem
    DatTrpLocalData.TransponderMessage.pBuffer = (U8*)(&DatTrpExportData.ExchChallenge);

    //---------------------------//
    // Start communication timer
    //---------------------------//
    DatTrpLocalData.CommandTimeOut = cChallengeTimeOut;
    TOSStartTimer(&DatTrpLocalData.TimeOutWaitingForImmoANTReply);

    //----------------------------------//
    // Start the sending of the message
    //----------------------------------//

    LDBSendWithAddr(cLDBChannelTrp, cLDBTrpStartAuth, &DatTrpLocalData.TransponderMessage);
}

//*****************************************************************************
//  DESCRIPTION         : Identifier received OK for authentication service.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : cFalse or cTrue.
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
BOOL DATTrpIdentifierReceivedOK(void)
{
#ifdef X90_PROJECT
    return DATTrpIdentifierReceivedOK_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL DATTrpIdentifierReceivedOK_Static(void)
{
#endif

    BOOL bResultL = cFalse;
    U8   ucKeyNumberL;

    if (mGetFlagAnswerReceivedOK())
    {
        DatTrpExportData.IdentifierOfPresentKey = DatTrpLocalData.u32DataBuffer;
        DatTrpExportData.IdentifierOfPresentKeyIsReceived = 1;
        //-------------------------------------------------------------------//
        // Compare identifier received with all identifiers stored in Eeprom
        //-------------------------------------------------------------------//
        for ( ucKeyNumberL = 0; 
        (ucKeyNumberL < cDATTrpMaxNumberOfKey) && (cFalse == (BOOL)DatTrpExportData.IdentifierOfPresentKeyIsValid); 
        ucKeyNumberL++)
        {
            if (mDATReadTable(U32Bit, EEP_KeyIdentifier, ucKeyNumberL, Default) == DatTrpExportData.IdentifierOfPresentKey)
            {
                DatTrpExportData.IdentifierOfPresentKeyIsValid = 1;
                DatTrpExportData.IndexOfKeyRecognized = ucKeyNumberL;
            }
        }
        //-------------------------------------------------------------------//
        // If received identifier is known by the BCM or if Learning Mode is 
        // in progress, the identifier is accepted.
        //-------------------------------------------------------------------//
        bResultL = (BOOL)(   (DatTrpExportData.AuthentInLearningMode) 
                         || (DatTrpExportData.IdentifierOfPresentKeyIsValid)
                        );
    }

    return bResultL;
}

//*****************************************************************************
//  DESCRIPTION         : Identifier received OK for TfcDiag service.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : cFalse or cTrue.
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
BOOL DATTrpTfcResponceOK(void)
{
    return (mGetFlagAnswerReceivedOK());
}

//*****************************************************************************
//  DESCRIPTION         : Compute and send read command.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
void DATTrpSendReadCommand(void)
{
#ifdef X90_PROJECT
    DATTrpSendReadCommand_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DATTrpSendReadCommand_Static(void)
{
#endif

    tTrpCommand EncodedReadingCommand;

    // Prevention of simultaneous access of antena by immo or exm components
    // like:    if (DatTrpLocalData.CipheredCommunication == cTrue)
    //------------------------//
    // Encode command to send
    //------------------------//
    EncodedReadingCommand = EncodeCommand(DatTrpLocalData.ReadingCommand);

    //-------------------------------------------------//
    // Prepare message to receive the page value
    //-------------------------------------------------//
    DatTrpLocalData.TransponderMessage.Lng  = cPageLength;
    DatTrpLocalData.u32DataBuffer            = 0;
    //QACJ 0310:amanevd: Test on target prooves that this cast is compiled correct. As well as this is how it comes from reuse.
    DatTrpLocalData.TransponderMessage.pBuffer = (U8*)&DatTrpLocalData.u32DataBuffer;

    //------------------------------------------//
    // Indicate that answer is not received yet
    //------------------------------------------//
    mClearFlagImmoAntAnswerReceived();
    mClearFlagAnswerReceivedOK();

    //---------------------------//
    // Start communication timer
    //---------------------------//
    DatTrpLocalData.CommandTimeOut = cReadCmdTimeOut;
    TOSStartTimer(&DatTrpLocalData.TimeOutWaitingForImmoANTReply);

    //----------------------------------//
    // Start the sending of the message
    //----------------------------------//  

    LDBReceiveWithAddr(cLDBChannelTrp, EncodedReadingCommand, &DatTrpLocalData.TransponderMessage);
}
//*****************************************************************************
//  DESCRIPTION         : Start Sleep Control service.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
void DATTrpSendSleepControl(void)
{
    DatTrpLocalData.u8AuthentLocalCounter++;

    DatTrpLocalData.CommandTimeOut = cControlTimeOut;
    TOSStartTimer(&DatTrpLocalData.TimeOutWaitingForImmoANTReply);
    DatTrpExportData.SleepControlState = cDATTrpServiceInProgress;
    mClearFlagImmoAntAnswerReceived();
    mClearFlagAnswerReceivedOK();
    LDBControl(cLDBChannelTrp, cLDBTrpSleep);
}

//*****************************************************************************
//  DESCRIPTION         : Sleep control finished
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
BOOL DATTrpSleepFinished(void)
{
    return (BOOL)(DatTrpExportData.SleepControlState != cDATTrpServiceInProgress);
}
//*****************************************************************************
//  DESCRIPTION         : WakeUp control finished
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
BOOL DATTrpWakeUpFinished(void)
{
    return (BOOL)(DatTrpExportData.WakeUpControlState == cDATTrpServiceSuccessful);
}
//*****************************************************************************
//  DESCRIPTION         : Send start authentication command to the transponder.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
void DATTrpSendStartAuth(void)
{
#ifdef X90_PROJECT
    DATTrpSendStartAuth_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DATTrpSendStartAuth_Static(void)
{
#endif

    //-------------------------------------------------//
    // Prepare message to receive the identifier value
    //-------------------------------------------------//
    DatTrpLocalData.TransponderMessage.Lng  = cIdentifierLength;
    DatTrpLocalData.u32DataBuffer            = 0;
    //QACJ 0310:amanevd: Test on target prooves that this cast is compiled correct. As well as this is how it comes from reuse.
    DatTrpLocalData.TransponderMessage.pBuffer = (U8*)&DatTrpLocalData.u32DataBuffer;

    //------------------------------------------//
    // Indicate that answer is not received yet
    //------------------------------------------//
    mClearFlagImmoAntAnswerReceived();
    mClearFlagAnswerReceivedOK();

    //---------------------------//
    // Start communication timer
    //---------------------------//
    DatTrpLocalData.CommandTimeOut = cIDEReadingTimeOut;
    TOSStartTimer(&DatTrpLocalData.TimeOutWaitingForImmoANTReply);

    //---------------------------//
    // prsFS_IMMO-683:
    // increase by 1 the counter "compt_nb_int" 
    //---------------------------//
    DatTrpExportData.AuthentTryCounter++;

    //----------------------------------//
    // Start the sending of the message
    //----------------------------------//

    LDBReceiveWithAddr(cLDBChannelTrp, cLDBTrpStartAuth, &DatTrpLocalData.TransponderMessage);
}
//*****************************************************************************
//  DESCRIPTION         : Write Access service not successful.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
void DATTrpWriteNotSuccess(void)
{
    mLIBassert(DatTrpExportData.WriteAccessState == cDATTrpServiceInProgress);

    DatTrpExportData.WriteAccessState = cDATTrpServiceNotSuccessful;
}
//*****************************************************************************
//  DESCRIPTION         : Write Access service successful.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
void DATTrpWriteSuccess(void)
{
    mLIBassert(DatTrpExportData.WriteAccessState == cDATTrpServiceInProgress);


    DatTrpExportData.WriteAccessWritingError = 0;
    DatTrpExportData.WriteAccessReadingError = 0;

    DatTrpExportData.WriteAccessState = cDATTrpServiceSuccessful;
}
//*****************************************************************************
//  DESCRIPTION         : Test if there is a transponder answer error or a 
//                        time out on the current command.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : cFalse or cTrue.
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
BOOL DATTrpAnswerReceivedNOKOrTimeOut(void)
{
    const BOOL bTimerElapsedL = TOSIsTimerElapsed(
                    &DatTrpLocalData.TimeOutWaitingForImmoANTReply, 
                    DatTrpLocalData.CommandTimeOut);

    return  (   
                (  
                    (cFalse == (BOOL)mGetFlagAnswerReceivedOK())
                 && (cTrue == (BOOL)mGetFlagImmoAntAnswerReceived()) 
                )
             || (cFalse != bTimerElapsedL)
            );
}

//*****************************************************************************
//  DESCRIPTION         : Wake Up Control Not Successful.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
void DATTrpOnWakeUpControlNotSuccessful(void)
{
    DatTrpExportData.WakeUpControlState = cDATTrpServiceNotSuccessful;
}

//*****************************************************************************
//  DESCRIPTION         : Start Wake Up Control service.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
void DATTrpSendWakeUpControl(void)
{
#ifdef X90_PROJECT
    DATTrpSendWakeUpControl_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DATTrpSendWakeUpControl_Static(void)
{
#endif
    mLIBassert(DatTrpExportData.WakeUpControlState != cDATTrpServiceInProgress);
    DatTrpLocalData.CommandTimeOut = cControlTimeOut;
    TOSStartTimer(&DatTrpLocalData.TimeOutWaitingForImmoANTReply);
    DatTrpExportData.WakeUpControlState = cDATTrpServiceInProgress;
    mClearFlagImmoAntAnswerReceived();
    mClearFlagAnswerReceivedOK();
    LDBControl(cLDBChannelTrp, cLDBTrpWakeUp);
}
//*****************************************************************************
//  DESCRIPTION         : Test if authentication service is not successfully 
//                        finished.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : cFalse or cTrue
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
BOOL DATTrpAuhenticationServiceFinishedNOK(void)
{
    return (BOOL)(DatTrpExportData.AuthenticationState == cDATTrpServiceNotSuccessful);
}
//*****************************************************************************
//  DESCRIPTION         : Test if authentication service is successfully 
//                        finished.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : cFalse or cTrue
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
BOOL DATTrpAuhenticationServiceFinishedOK(void)
{
    return (BOOL)(DatTrpExportData.AuthenticationState == cDATTrpServiceSuccessful);
}
//*****************************************************************************
//  DESCRIPTION         : Test if a new authentication is authorized.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : cFalse or cTrue
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document 
//
//*****************************************************************************
BOOL DATTrpNewAuthenticationAuthorized(void)
{
#ifdef X90_PROJECT
    return DATTrpNewAuthenticationAuthorized_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL DATTrpNewAuthenticationAuthorized_Static(void)
{
#endif

    BOOL    bResultL = cFalse;
    tTOSTimer   TempTimer;

    if (cFalse == (BOOL)DatTrpExportData.ActiveTestMode)
    {
        if (cFalse == (BOOL)DatTrpExportData.AuthentInLearningMode)
        {
            // (REQ: prsFS_IMMO-479)
            if(DatTrpLocalData.u8AuthentLocalCounter < cMaxAuthentTrialsCustomerMode)
            {
                //QACJ 3226: amanevd: This is intentional and is checked out for problems.
                TempTimer = mTimeOutAuthent();
                bResultL = TOSIsTimerElapsed(&(DatTrpLocalData.AuthenticationTimeOut), 
                                            TempTimer);
                bResultL = (cFalse == bResultL);
            }
        }
        else
        {
            if(DatTrpLocalData.u8AuthentLocalCounter < cMaxAuthentTrialsLearningMode)
            {
                bResultL = (     (cFalse == (BOOL)DatTrpExportData.KeyLearningElapsed)
                            &&  (cFalse == DatTrpLocalData.bStopAuthentService)
                          );
            }
        }
    }    
    return (bResultL);
}
//*****************************************************************************
//  DESCRIPTION         : Increase Retry Counters
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document (REQ: prsFS_IMMO-480)
//
//*****************************************************************************
void DATTrpIncreaseRetryCounters(void)
{
    U8 u8AuthentDelayedCounterL = mDATRead(U8Bit, EEP_AuthentDelayedCounter, Default);

    if(u8AuthentDelayedCounterL < cMaxAuthentDelayedCounter)
    {
        u8AuthentDelayedCounterL++;
        mDATWrite(U8Bit, EEP_AuthentDelayedCounter, u8AuthentDelayedCounterL, Default);
    }
}

//*****************************************************************************
//  DESCRIPTION         : Resynchronization service not successful.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
void DATTrpResynchronizationNotSuccess(void)
{
#ifdef X90_PROJECT
    DATTrpResynchronizationNotSuccess_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DATTrpResynchronizationNotSuccess_Static(void)
{
#endif

    U8 ucResynchroFailureL;

    mLIBassert(   (DatTrpExportData.ResynchronizationState == cDATTrpServiceInProgress)
        || ((cFalse == (BOOL)DatTrpExportData.AuthentInLearningMode) && (DatTrpExportData.IndexOfKeyRecognized < cDATTrpMaxNumberOfKey)) );

    if (cFalse == (BOOL)DatTrpExportData.ActiveTestMode)
    {
        //------------------------------------------//
        // Update resynchronization failure counter
        //------------------------------------------//
        ucResynchroFailureL = mDATRead(U8Bit, EEP_ResynchroFailureCounter, Default);
        if (ucResynchroFailureL < cMaxWritingDefault)
        {
            mDATWrite(U8Bit, EEP_ResynchroFailureCounter, (ucResynchroFailureL + 1), Default);
        }

        // Writing in EEPROM is not authorized as long as the learning mode is in progress.
        if (cFalse == (BOOL)DatTrpExportData.AuthentInLearningMode)
        {
            //------------------------------------------------------------//
            // Write the last reading data or the default value in EEPROM
            //------------------------------------------------------------//
            mDATWriteTable(U32Bit, EEP_DefResynchroValueRead, DatTrpExportData.IndexOfKeyRecognized, DatTrpExportData.DataRead, Default);

            //---------------------------------------//
            // Write the last writing data in EEPROM
            //---------------------------------------//
            mDATWriteTable(U32Bit, EEP_DefResynchroValueWrite, DatTrpExportData.IndexOfKeyRecognized, DatTrpExportData.ResynchronizationValue, Default);
        }
    }

    DatTrpExportData.ResynchronizationState = cDATTrpServiceNotSuccessful;
}
//*****************************************************************************
//  DESCRIPTION         : Resynchronization service successful.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
void DATTrpResynchronizationSuccess(void)
{
#ifdef X90_PROJECT
    DATTrpResynchronizationSuccess_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DATTrpResynchronizationSuccess_Static(void)
{
#endif

    U8 ucClearResynchroFlagL;
    U8 ucResynchroSuccessfulL;

    mLIBassert((cTrue == (BOOL)DatTrpExportData.AuthentInLearningMode) || (DatTrpExportData.IndexOfKeyRecognized < cDATTrpMaxNumberOfKey));
    mLIBassert(DatTrpExportData.ResynchronizationState == cDATTrpServiceInProgress);

    if (cFalse == (BOOL)DatTrpExportData.ActiveTestMode)
    {
        //--------------------------------------------//
        // Update resynchronization successful counter
        //--------------------------------------------//
        ucResynchroSuccessfulL = mDATRead(U8Bit, EEP_ResynchroSuccessfulCounter, Default);
        if (ucResynchroSuccessfulL < cMaxResynchroSuccessfulCounter)
        {
            mDATWrite(U8Bit, EEP_ResynchroSuccessfulCounter,
                (ucResynchroSuccessfulL + 1), Default);
        }

        if (cFalse == (BOOL)DatTrpExportData.AuthentInLearningMode)
        {
            mDATWriteTable(U32Bit, EEP_InitialResynchroValue, DatTrpExportData.IndexOfKeyRecognized, DatTrpExportData.ResynchronizationValue, Default);
            mDATWriteTable(U32Bit, EEP_SI28Bits, DatTrpExportData.IndexOfKeyRecognized, DatTrpExportData.ResynchronizationValue, Default);

            ucClearResynchroFlagL = mDATRead(U8Bit, EEP_ResynchroRequest, Default);
            ucClearResynchroFlagL &= (U8)(~((U8)((U8)1 << DatTrpExportData.IndexOfKeyRecognized)));
            mDATWrite(U8Bit, EEP_ResynchroRequest, ucClearResynchroFlagL, Default);
        }
        else
        {
            //------------------------------------------------------------//
            // Write the last reading data or the default value in EEPROM
            //------------------------------------------------------------//
            mDATWriteTable(U32Bit, EEP_DefResynchroValueRead, mDATRead(U8Bit, NumberOfKeysLearnt, Default), DatTrpExportData.ResynchronizationValue, Default);

            //---------------------------------------//
            // Write the last writing data in EEPROM
            //---------------------------------------//
            mDATWriteTable(U32Bit, EEP_DefResynchroValueWrite, mDATRead(U8Bit, NumberOfKeysLearnt, Default), DatTrpExportData.ResynchronizationValue, Default);
        }
    }

    DatTrpExportData.ResynchronizationState = cDATTrpServiceSuccessful;
}
//*****************************************************************************
//  DESCRIPTION         : Start the Write Access service in the context of the
//                        Resynchronization service.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
void DATTrpStartWriteServiceForResync(void)
{
    mLIBassert(DatTrpExportData.WriteAccessState != cDATTrpServiceInProgress);

    DatTrpExportData.WriteAccessState = cDATTrpServiceInProgress;
    TOSSeqActivateGraph(cTOSSeqGraphIdDATTrpWriteAccess);
}
//*****************************************************************************
//  DESCRIPTION         : Test if Write Access service is not successfully 
//                        finished.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
BOOL DATTrpWriteServiceFinishedNOK(void)
{
    return (BOOL)(DatTrpExportData.WriteAccessState == cDATTrpServiceNotSuccessful);
}
//*****************************************************************************
//  DESCRIPTION         : Test if Write Access service is successfully finished.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
BOOL DATTrpWriteServiceFinishedOK(void)
{
    return (BOOL)(DatTrpExportData.WriteAccessState == cDATTrpServiceSuccessful);
}
//*****************************************************************************
//  DESCRIPTION         : Test if a new read or write access is authorized.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : cFalse or cTrue
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
BOOL DATTrpNewTryAuthorized(void)
{
#ifdef X90_PROJECT
    return DATTrpNewTryAuthorized_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL DATTrpNewTryAuthorized_Static(void)
{
#endif
    BOOL bResultL = cFalse;

    if (cFalse == (BOOL)DatTrpExportData.ActiveTestMode) 
    {
        if (cFalse == (BOOL)DatTrpExportData.AuthentInLearningMode)
        {
            //---------------------------------------------------------------//
            // In normal mode, use the max number of try to leave the service
            //---------------------------------------------------------------//
            bResultL = (DatTrpLocalData.u8ReadOrWriteNumberOfTry < cDATTrpTransponderAccessMaxNumberOfTry);
        }
        else
        {
            //---------------------------------------------------------------//
            // In learning mode, use a time out to leave the service
            //---------------------------------------------------------------//
            bResultL = (cFalse == (BOOL)DatTrpExportData.KeyLearningElapsed);
        }
    }
    return (bResultL);
}

//*****************************************************************************
//  DESCRIPTION         : Test if in Learning Mode and if Maximum number of
//                        writing trials are being made.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : cFalse or cTrue
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
BOOL DATTrpInLearningModeAndLessThanMaxTrials(void)
{
#ifdef X90_PROJECT
    return DATTrpInLearningModeAndLessThanMaxTrials_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL DATTrpInLearningModeAndLessThanMaxTrials_Static(void)
{
#endif
    BOOL bResultL = cFalse;

    if (cFalse == (BOOL)DatTrpExportData.ActiveTestMode) 
    {
        DatTrpLocalData.u8ReadOrWriteNumberOfTry++;

        if (cFalse != (BOOL)DatTrpExportData.AuthentInLearningMode)
        {
            //---------------------------------------------------------------//
            // In learning mode, count the max number of trials before new authent
            //---------------------------------------------------------------//
            bResultL = DatTrpLocalData.u8ReadOrWriteNumberOfTry < cDATTrpTransponderAccessMaxNumberOfTry;
        }
    }
    return (bResultL);
}

//*****************************************************************************
//  DESCRIPTION         : Compute and send inverted read command.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
void DATTrpSendInvertedReadCommand(void)
{
#ifdef X90_PROJECT
    DATTrpSendInvertedReadCommand_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DATTrpSendInvertedReadCommand_Static(void)
{
#endif

    tTrpCommand EncodedInvertedReadingCommand;

    // Prevention of simultaneous access of antena by immo or exm components
    // like:    if (DatTrpLocalData.CipheredCommunication == cTrue)
    //------------------------//
    // Encode command to send
    //------------------------//
    EncodedInvertedReadingCommand = EncodeCommand(DatTrpLocalData.InvertedReadingCommand);

    DatTrpLocalData.TransponderMessage.Lng  = cPageLength;
    DatTrpLocalData.u32DataBuffer            = 0;
    //QACJ 0310:amanevd: Test on target prooves that this cast is compiled correct. As well as this is how it comes from reuse.
    DatTrpLocalData.TransponderMessage.pBuffer = (U8*)&DatTrpLocalData.u32DataBuffer;

    //------------------------------------------//
    // Indicate that answer is not received yet
    //------------------------------------------//
    mClearFlagImmoAntAnswerReceived();
    mClearFlagAnswerReceivedOK();

    //---------------------------//
    // Start communication timer
    //---------------------------//
    DatTrpLocalData.CommandTimeOut = cReadCmdTimeOut;
    TOSStartTimer(&DatTrpLocalData.TimeOutWaitingForImmoANTReply);

    //----------------------------------//
    // Start the sending of the message
    //----------------------------------//  

    LDBReceiveWithAddr(cLDBChannelTrp, EncodedInvertedReadingCommand, &DatTrpLocalData.TransponderMessage);
}

//*****************************************************************************
//  DESCRIPTION         : Test if write command is successful.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : cFalse or cTrue
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
BOOL DATTrpPageWrittenOK(void)
{
    BOOL bTimerElapsedL;

    bTimerElapsedL = TOSIsTimerElapsed(&DatTrpLocalData.TimeOutWaitingForWriting, 
    cWritingInTrpTimeOut);

    return (    (cTrue == (BOOL)mGetFlagAnswerReceivedOK()) 
             && (cFalse != bTimerElapsedL));
}
//*****************************************************************************
//  DESCRIPTION         : Test if data read is OK and equal to the last data
//                        written.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : cFalse or cTrue
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
BOOL DATTrpReadAndCompareOK(void)
{
#ifdef X90_PROJECT
    return DATTrpReadAndCompareOK_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL DATTrpReadAndCompareOK_Static(void)
{
#endif

    BOOL bResultL = cFalse;

    if (mGetFlagAnswerReceivedOK())
    {
        // Prevention of simultaneous access of antena by immo or exm components
        // like:    if (DatTrpLocalData.CipheredCommunication == cTrue)
        //----------------------------//
        // Decode and store data read
        //----------------------------//
        LIBPcfCipheredData = U32ReverseByteOrder(DatTrpLocalData.u32DataBuffer);
        LDBRefreshWatchDog();
        LIBPcfCipherFunction(cPageLength);
        LDBRefreshWatchDog();
        DatTrpExportData.DataRead  =  U32ReverseByteOrder(LIBPcfCipheredData);

        if (cFalse == (BOOL)DatTrpExportData.WriteSecretKeyHigh)
        {
            bResultL = (BOOL)(DatTrpExportData.DataToWrite == DatTrpExportData.DataRead);
        }
        else
        {
            bResultL = (BOOL)(DatTrpExportData.DataToWrite == (DatTrpExportData.DataRead & (cMaskByte1 | cMaskByte2)));
        }
    }

    return (bResultL);
}
//*****************************************************************************
//  DESCRIPTION         : Action if data writing has failed
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document (REQ: prsFS_IMMO-527)
//
//*****************************************************************************
void DATTrpWriteNOKAction(void)
{
    DatTrpExportData.WriteAccessWritingError = 1;
}

//*****************************************************************************
//  DESCRIPTION         : Action if read data is not correct
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document (REQ: prsFS_IMMO-527)
//
//*****************************************************************************
void DATTrpReadNOKAction(void)
{
    
    if(cDATTrpServiceInProgress == DatTrpExportData.ResynchronizationState)
    {
        DatTrpExportData.ResynchronizationValue = 0;
        DatTrpExportData.DataToWrite = DatTrpExportData.ResynchronizationValue;
        DatTrpExportData.DataRead = 0;
    }
    
    DatTrpExportData.WriteAccessReadingError = 1;
}

//*****************************************************************************
//  DESCRIPTION         : Compute and send write command.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
void DATTrpSendWriteCommand(void)
{
#ifdef X90_PROJECT
    DATTrpSendWriteCommand_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DATTrpSendWriteCommand_Static(void)
{
#endif

    tTrpCommand EncodedWritingCommand;

    //-----------------------------------//
    // Set data read to the default value
    //-----------------------------------//
    DatTrpExportData.DataRead = cDATTrpResyncReadFailDefaultValue;

    //------------------------//
    // Encode command to send
    //------------------------//
    // Prevention of simultaneous access of antena by immo or exm components
    // like:    if (DatTrpLocalData.CipheredCommunication == cTrue)
    EncodedWritingCommand = EncodeCommand(DatTrpLocalData.WritingCommand);  
    //------------------------------------//
    // Prepare command to send
    //------------------------------------//

    DatTrpLocalData.TransponderMessage.Lng  = cCommandLength;
    DatTrpLocalData.u32DataBuffer            = 0;
    //QACJ 0310:amanevd: Test on target prooves that this cast is compiled correct. As well as this is how it comes from reuse.
    DatTrpLocalData.TransponderMessage.pBuffer = (U8*)&DatTrpLocalData.u32DataBuffer;

    //------------------------------------------//
    // Indicate that answer is not received yet
    //------------------------------------------//
    mClearFlagImmoAntAnswerReceived();
    mClearFlagAnswerReceivedOK();

    //---------------------------//
    // Start communication timer
    //---------------------------//
    DatTrpLocalData.CommandTimeOut = cSendWriteCmdTimeOut;
    TOSStartTimer(&DatTrpLocalData.TimeOutWaitingForImmoANTReply);
    TOSStartTimer(&DatTrpLocalData.TimeOutWaitingForWriting);

    //----------------------------------//
    // Start the sending of the message
    //----------------------------------//  

    LDBReceiveWithAddr(cLDBChannelTrp, EncodedWritingCommand, &DatTrpLocalData.TransponderMessage);
}

//*****************************************************************************
//  DESCRIPTION         : Send the 32 bits data to write in the transponder
//                        memory.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
void DATTrpSendDataToWrite(void)
{
#ifdef X90_PROJECT
    DATTrpSendDataToWrite_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DATTrpSendDataToWrite_Static(void)
{
#endif
    
    U32 ulEncodedDataToWriteL;

    // Prevention of simultaneous access of antena by immo or exm components
    // like:    if (DatTrpLocalData.CipheredCommunication == cTrue)
    //-----------------------//
    // Encode data to write
    //-----------------------//
    LIBPcfCipheredData = U32ReverseByteOrder(DatTrpExportData.DataToWrite);
    LDBRefreshWatchDog();
    LIBPcfCipherFunction(cPageLength);
    LDBRefreshWatchDog();
    ulEncodedDataToWriteL =  U32ReverseByteOrder(LIBPcfCipheredData);
    //------------------------------------------//
    // Prepare message to send
    //------------------------------------------//

    DatTrpLocalData.Buffer[cPage0] = (U8)(ulEncodedDataToWriteL);
    DatTrpLocalData.Buffer[cPage1] = (U8)(ulEncodedDataToWriteL >> cShift8);
    DatTrpLocalData.Buffer[cPage2] = (U8)(ulEncodedDataToWriteL >> cShift16);
    DatTrpLocalData.Buffer[cPage3] = (U8)(ulEncodedDataToWriteL >> cShift24);

    DatTrpLocalData.TransponderMessage.Lng      = cPageLength;
    DatTrpLocalData.TransponderMessage.pBuffer  = DatTrpLocalData.Buffer;

    //------------------------------------------//
    // Indicate that answer is not received yet
    //------------------------------------------//
    mClearFlagImmoAntAnswerReceived();
    mClearFlagAnswerReceivedOK();

    //---------------------------//
    // Start communication timer
    //---------------------------//
    DatTrpLocalData.CommandTimeOut = cSendDataToWriteTimeOut;
    TOSStartTimer(&DatTrpLocalData.TimeOutWaitingForImmoANTReply);
    TOSStartTimer(&DatTrpLocalData.TimeOutWaitingForWriting);

    //----------------------------------//
    // Start the sending of the message
    //----------------------------------//  

    LDBSendWithAddr(cLDBChannelTrp, DatTrpLocalData.WritingCommand, &DatTrpLocalData.TransponderMessage);
}
//*****************************************************************************
//  DESCRIPTION         : Test if write command answer is OK.
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : cFalse or cTrue
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
BOOL DATTrpWriteCommandReceivedOK(void)
{
#ifdef X90_PROJECT
    return DATTrpWriteCommandReceivedOK_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL DATTrpWriteCommandReceivedOK_Static(void)
{
#endif

    BOOL bResultL = cFalse;
    BOOL bTimerElapsedL;


    bTimerElapsedL = TOSIsTimerElapsed(&DatTrpLocalData.TimeOutWaitingForWriting, 
    cWritingInTrpTimeOut);

    if (    (cTrue == (BOOL)mGetFlagAnswerReceivedOK())
         && (cFalse != bTimerElapsedL)
       )
    {
        // Prevention of simultaneous access of antena by immo or exm components
        // like:    if (DatTrpLocalData.CipheredCommunication == cTrue)
        //-----------------------------------//
        // Decode and check command received
        //-----------------------------------//
        LIBPcfCipheredData =((DatTrpLocalData.u32DataBuffer >> cShift8 ) & cMaskByte1)
            | ((DatTrpLocalData.u32DataBuffer << (cShift8 + cShift4 + cShift2)) 
            & cMaskByte2);
        LDBRefreshWatchDog();
        LIBPcfCipherFunction(cCommandLength);
        LDBRefreshWatchDog();
        LIBPcfCipheredData =((LIBPcfCipheredData >> cShift8) & cMaskByte1)
            | ((LIBPcfCipheredData << cShift8) & cMaskByte2);
        LIBPcfCipheredData >>= (cShift4 + cShift2);

        bResultL = (BOOL)(LIBPcfCipheredData == (U32)DatTrpLocalData.WritingCommand);
    }

    return (bResultL);
}

//*****************************************************************************
//  DESCRIPTION         : Maintain active state
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : 
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
void DATTrpMaintainActiveState (void)
{
    if (cDATTrpServiceInProgress == DatTrpExportData.AuthenticationState)
    {
        TOSWriteSignal(cTOSSignalSomebodyMaintainActiveState);
    }
    else
    {
        //Nothing
    }
}

//*****************************************************************************
//  DESCRIPTION         : 
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
BOOL DATTrpAuthentInNormalMode(void)
{
    return (cFalse == (BOOL)DatTrpExportData.AuthentInLearningMode);
}
//*****************************************************************************
//  DESCRIPTION         : 
//
//  PARAMETERS          : None
//  (Type,Name,Min,Max) 
//
//  RETURN VALUE        : None
//
//  DESIGN INFORMATION  : Refer to Detailed Design Document
//
//*****************************************************************************
BOOL DATTrpPage3InvertedDataReceivedOK(void)
{
#ifdef X90_PROJECT
    return DATTrpPage3InvertedDataReceivedOK_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL DATTrpPage3InvertedDataReceivedOK_Static(void)
{
#endif

    BOOL bResultL = cFalse;

    if (mGetFlagAnswerReceivedOK())
    {
        //----------------------------//
        // Decode data read
        //----------------------------//
        LIBPcfCipheredData = U32ReverseByteOrder(DatTrpLocalData.u32DataBuffer);
        LDBRefreshWatchDog();
        LIBPcfCipherFunction(cPageLength);
        LDBRefreshWatchDog();
        LIBPcfCipheredData = U32ReverseByteOrder(LIBPcfCipheredData);

        if (LIBPcfCipheredData == ~DatTrpExportData.DataRead)
        {
            //---------------------------------------//
            // Update key informations
            //---------------------------------------//
            DatTrpExportData.PresentKeyLocked = ((DatTrpExportData.DataRead & cKeyLocked) == cKeyLocked);
            DatTrpExportData.KeyWithRF = ((DatTrpExportData.IdentifierOfPresentKey & cKeyWithRF) == cKeyWithRF);
            DatTrpExportData.KeyStandard = ((DatTrpExportData.IdentifierOfPresentKey & cKeyStandardMsk) == cKeyStandard);
            DatTrpExportData.FrequencyOfPresentKey = (U8)(DatTrpExportData.DataRead >> cShift16) & cFrequencyMask;
            DatTrpExportData.KeyWithExtendedMemory = ((DatTrpExportData.DataRead & cKeyWithExtendedMemory) == cKeyWithExtendedMemory);       
            // Update of DiagKeyFrequency signal
            SignalCurrentKeyFrequency();

            bResultL = cTrue;

            DatTrpExportData.ResponseToChallengeIsValid = bResultL;
        }

    }

    return (bResultL);
}
