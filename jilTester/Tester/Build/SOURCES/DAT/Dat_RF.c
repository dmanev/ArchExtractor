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
// $Date:   May 26 2010 09:21:44  $
// $Archive::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_RF/Dat_RF.c-arc  $
// $Revision:   1.16  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_RF/Dat_RF.c-arc  $
// 
//    Rev 1.16   May 26 2010 09:21:44   adzhelp
// Cm008663: Long push events not stored
// 
//    Rev 1.15   May 20 2010 15:56:30   adzhelp
// Cm008663: No binary change: correction for 'passing RF'
// 
//    Rev 1.14   Mar 09 2010 11:37:06   adzhelp
// Cm007542:  Code review corrections
// 
//    Rev 1.13   Feb 22 2010 16:18:04   adzhelp
// Cm007542:  TRF_RECU in frame $21$DB can be on when no frame is detected
// 
//    Rev 1.12   Feb 03 2010 12:14:38   adzhelp
// Cm005245: Control of LIB_PCF refresh
// 
//    Rev 1.11   Dec 04 2009 16:48:58   adzhelp
// Cm006719: Added counter for RC blocks with correct CRC
// 
//    Rev 1.10   Oct 07 2009 11:41:26   adzhelp
// Cm006427: Functions moved to banked area
// 
//    Rev 1.9   Oct 06 2009 17:36:56   akodzhh
// Cm006427: DATRfPushMemorized is now updated for UnlockDrDoor, UnlockAll and LockAll trough LAP_DLK(SDO).
// 
//    Rev 1.8   Sep 21 2009 13:29:20   adzhelp
// Cm005180: Control cLDBRfDeactivateStrobe sent when RF channel disabled
// 
//    Rev 1.7   Sep 09 2009 14:20:38   ailievb
// Cm005180: RKE: According to CLR#105 RKE operation has to be managed by AUTRECRF
// 
//    Rev 1.6   Sep 01 2009 14:05:10   amanevd
// Cm005142: Status of Confidential Diagnostic routines included
// 
//    Rev 1.5   Aug 31 2009 16:13:42   amanevd
// Cm005142: Transfer of Confidential Diagnostic to LIB_CFD
// 
//    Rev 1.4   May 25 2009 14:00:38   ailievb
// Cm003265: Implementation of the Remote Keyless Entry functionality - CCover justifications
// 
//    Rev 1.3   May 07 2009 16:32:40   amanevd
// Cm004915 - Second key learning causes problem
// 
//    Rev 1.2   May 04 2009 17:11:10   akodzhh
// Cm004910: In $21 $DB diag request, TRF_OUV_COND, TRF_OUV are inverted.
// 
//    Rev 1.1   Apr 28 2009 10:55:06   adzhelp
// Cm003276: Implementation of RF sleep mode management
// 
//    Rev 1.0   Apr 17 2009 10:37:04   ailievb
// Initial revision.
// 
//******************************************************************************

//--------------------------------------------------------------------------
//  Body Identification
//--------------------------------------------------------------------------

#define dat_rf  "dat_rf"
//--------------------------------------------------------------------------
//  Included files
//
//  #include <system_file_name.h>
//  #include "project_file_name.h"
//--------------------------------------------------------------------------
#include "lib.h"
#include "tos.h"
#include "dat.h"
#include "dat_rf.h"
#include "dat_rf.hgr"

#include "lib_pcf.h"

//--------------------------------------------------------------------------
// Local constants
//
//  #define cConstantName   ((tType) ConstantValue)
//--------------------------------------------------------------------------
#define cSearchFramePeriodMs                                               \
  ((U8)(cDATRfLDBSearchFramePeriodMs/cDATCpuSleepGraphEnginePeriodMs))
#define cRCReceptionTimeOut                                               \
  ((U8)(cDATRfRCReceptionTimeOut/cDATCpuSleepGraphEnginePeriodMs))
#define cLongPushWaitTimeOut                                               \
  ((U8)(cDATRfLongPushWaitTimeOut/cDATCpuSleepGraphEnginePeriodMs))
#define cLongPushReceiveTimeOut                                            \
  ((U8)(cDATRfLongPushReceiveTimeOut/cDATCpuSleepGraphEnginePeriodMs))
#define cDiagMemorizationTime                                              \
  ((U8)(cDATRfDiagMemorizationTime/cDATCpuSleepGraphEnginePeriodMs))

#define cDATCpuSleepGraphEnginePeriodMs ((U8)20)

#define cNbMaxStockedInByte            ((U8)255)
#define cNoPushedButton                ((U8)0)
#define cButtonIsPushed                ((U8)1)
                                       
#define cRCFrame                       ((U8)1)
#define cSIFrame                       ((U8)2)
#define cNbBytesRCFrame                ((U8)11)
#define cNbBytesSIFrame                ((U8)2)
                                      
#define cIndiceKeyRf0                  ((U8)0)  // Key number used (Max = 3)
#define cIndiceKeyRf1                  ((U8)1)  
#define cIndiceKeyRf2                  ((U8)2)  
#define cIndiceKeyRf3                  ((U8)3)
                                       
#define cNbBytesRemoteSK               ((U8)6)
#define cNbBitsCryptage                ((U8)32)

#ifdef _DIAGNOSTIC_MEMO_    //For Diagnostic   
    #define cNbCodeDiagMemorized         ((U8)8)
    //Diagnostic codes and constant values
    #define cDiagLongPressButton1        ((U8)0x01)
    #define cDiagShortPressButton2       ((U8)0x02)
    #define cDiagShortPressButton1       ((U8)0x04)
    #define cDiagLongPressButton2        ((U8)0x08)
    #define cDiagRfFrameReceived         ((U8)0x10)
    #define cDiagRfFrameReceivedAndValid ((U8)0x20)
    #define cDiagShortPressButton3       ((U8)0x40)
    #define cDiagLongPressButton3        ((U8)0x80)
#endif

//for graph motor                    
#define cDATRfEnd                      ((U8)0xFF)
//--------------------------------------------------------------------------
//  Local macros
//
//  #define mMacroName   (MacroDefinition)
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
//  Local types
//
//  struct  sStructureName { ... };
//  union   uUnionName { ... };
//  enum    eEnumerationName { ... };
//  typedef Expression tTypeName;
//--------------------------------------------------------------------------

typedef union
{
    U16 Format16Bit;
    struct
    {
        U8 F8Bit1;
        U8 F8Bit2;
    } Format8Bit;
}tMot16Bit;

//--------------------------------------------------------------------------
//  Local data
//
//  static  tType   VariableName;
//  static  tType*  pVariableName; 
//--------------------------------------------------------------------------
static  BOOL  SearchFrameInCourse;    //Flag positioned by LDBCallBack
static  BOOL  WakeUpBlockReceived;    //Flag positioned by LDBCallBack                      
static  BOOL  RCFrameReceived;        //Flag positioned by LDBCallBack                          
static  BOOL  SIFrameReceived;        //Flag positioned by LDBCallBack    
                
static  BOOL  RCReceptionTimeOutIsActive;  
static  BOOL  LongPushTimeOutIsActive;    

static  U8    ButtonPushed;           //State of each button on the keyfob
                                          //  Bit0 represents the first button short push
                                          //  Bit1 ---------- --- second button short push
                                          //  ...
                                          //  Bit3 ---------- --- fourth button short push
                                          //  Bit4 represents the first button long push
                                          //  ...
                                          //Each bit = 0 indicates the button is not pushed
                                          //---- --- = 1 indicates the button is pushed

static  U8    IndiceKeyRf;            // Key number used
                                          // Min = 0, Max = 3

#ifdef _DIAGNOSTIC_MEMO_ //for Diagnostic   
  // Extern dat
    U32 DATRfRCFrameIDEReceived;// RC frame Identifier received (extern for Diagnostic)
#else
    static U32   DATRfRCFrameIDEReceived;// RC frame Identifier received (extern for Diagnostic)
#endif

static U16   RCFrameSIReceived;      // RC frame Sequence Increment received  
static U8    RCFrameCIDReceived;     // RC frame Command ID received 

static U8    DataRCFrameReceived[cNbBytesRCFrame]; 
static U8    DataSIFrameReceived[cNbBytesSIFrame];    

static U32   SI28BitsLastRCFrameKnown;

static U8    TempoSearchFramePeriod;

static U8    TempoAlarmITForRCReceptionTimeOut;         //to manage a RCReception "timer"
static U8    TempoAlarmITForLongPushWaitTimeOut;        //to manage a SIWait "timer"
static U8    TempoAlarmITForLongPushReceiveTimeOut;     //to manage a SIReceive "timer"

#ifdef _DIAGNOSTIC_MEMO_    //for Diagnostic   
    static U8  TempoAlarmITForDiag[cNbCodeDiagMemorized]; //to manage a Diag "timer"
#endif

#ifdef _PASSING_RF_
    static U8  TempoAlarmITForPassingRf;
#endif

//--------------------------------------------------------------------------
//  Local function prototypes
//  
//  static tTypeRetour FunctionName(tTypeArgument1 ArgumentName1, ... );
//--------------------------------------------------------------------------
static void       RfPeriodicTask(void);

static void       CallBckReceptionRCFrame(tAddress Adresse, tStatus Statut, tMsg * pMsg);
static MEM_TYPE void       ExtractDataFromRCFrameReceived(void);
static MEM_TYPE U32    BuildingSI28BitsTheoric(U32 SIStartValue);
static MEM_TYPE U32    CalculRollingCodeTheoreticRCFrame(tDatRfMot32Bit Challenge);
static void       UpdateKeyResynchronisation(void);
                  
static void       CallBckReceptionSIFrame(tAddress Adresse, tStatus Statut, tMsg * pMsg);
                  
#ifdef _DIAGNOSTIC_MEMO_    //For Diagnostic   
    static MEM_TYPE void     ArmerNbAlarmITForDiag(const U8 DiagnosticCode); //to arm a Diag "timer"
#endif

#ifdef X90_PROJECT
static MEM_TYPE void DATRfLongPushDetected_Static(void);
#endif

//--------------------------------------------------------------------------
//  Constant local Data
//
//  static const tType  VariableName;
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//  Exported data
//
//  tType   CMPVariableName;      (CMP: 3 characters to identify this component)
//  tType*  pCMPVariableName;     (CMP: 3 characters to identify this component)
//--------------------------------------------------------------------------
#ifdef _DIAGNOSTIC_MEMO_ //for Diagnostic   
    U8  DATRfPushMemorized; 
#endif

#ifdef _TEST_RF_  //counters used for RF hardware testing   
    U8  DATRfNbWakeUpBlocksReceived;
    U8  DATRfNbRCBlocksReceived;
    U8  DATRfNbRCBlocksReceivedAndOK;
    U8  DATRfNbRCBlocksReceivedCrcOK;
    U8  DATRfNbSIBlocksReceived;
    U8  DATRfNbSIBlocksReceivedAndOK;
#endif

tDatRfMot32Bit DATRfRCFrameSRReceived;
//--------------------------------------------------------------------------
//  Constant exported data
// 
//  const tType   CMPVariableName;(CMP: 3 characters to identify this component)
//--------------------------------------------------------------------------
const tRxSpontWithAddr DATRfRxSpontTable[] = //tableau de pointeurs de fonctions
{
    {CallBckReceptionRCFrame,       cRCFrame},
    {CallBckReceptionSIFrame,       cSIFrame},
};

#ifdef X90_PROJECT
static MEM_TYPE void DATRfInit_Static(void);
static MEM_TYPE void DATRfShortPushDetectedAndArmLongPushTimer_Static(void);
static MEM_TYPE BOOL DATRfSiBlockReceivedAndLongPushWaitTimeElapsed_Static(void);
static MEM_TYPE BOOL DATRfNewRcBlockReceived_Static(void);
#endif

//==============================================================================
//*...........................................................................*
//*............................ LOCAL FUNCTIONS ..............................*
//*...........................................................................*
//==============================================================================/
//==============================================================================
//  DESCRIPTION : ArmerNbAlarmITForDiag
//  
//  PARAMETERS (Type,Name,Min,Max) :
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION : Rearms "timer" to cDATRfDiagMemorizationTime
//     
//==============================================================================
#ifdef _DIAGNOSTIC_MEMO_    //For Diagnostic   
static MEM_TYPE void   ArmerNbAlarmITForDiag(const U8 DiagnosticCode) //to set a Diag "timer"
{
    U8 Counter;

    DATRfPushMemorized |= DiagnosticCode; 
    for (Counter = 0; Counter<cNbCodeDiagMemorized ; Counter++)
    {
        if(DiagnosticCode == (0x01<<Counter))
        {
            TempoAlarmITForDiag[Counter] = cDiagMemorizationTime;
        }
    }
}
#endif

//==============================================================================
//  DESCRIPTION : CallBckReceptionRCFrame
//  
//  PARAMETERS (Type,Name,Min,Max) :
//    (tAddress Adresse, tStatus Statut, tMsg * pMsg)
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   
//  Fonction called by LDB part to do a copy of the received RC frame
//     
//==============================================================================*/
static void CallBckReceptionRCFrame(tAddress Adresse, tStatus Statut, tMsg * pMsg)
{
    //Copy contents in DataRCFrameReceived
    mLIBmemcpy ((U8*)DataRCFrameReceived, pMsg->pBuffer, cNbBytesRCFrame);

#ifdef _PASSING_RF_
    {
        if (TempoAlarmITForPassingRf == 0)
        {
            TempoAlarmITForPassingRf = cRCReceptionTimeOut;
            RCFrameReceived = cTrue;  
        }
        else
        {} //wait RCReceptionTimeOut
  }
#else
    //Flag to signal: RC frame received
    RCFrameReceived = cTrue;  
#endif

#ifdef _TEST_RF_ //update counters used for RF hardware testing   
    if (DATRfNbRCBlocksReceived < cNbMaxStockedInByte)
    {
        DATRfNbRCBlocksReceived++;
    }
    else
    {} //nothing to do
#endif
}

//=============================================================================
//  DESCRIPTION : ExtractDataFromRCFrameReceived
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION : Extract useful data from incoming RfFrame
//     
//==============================================================================
static MEM_TYPE void ExtractDataFromRCFrameReceived(void)
{
#ifdef _TEST_RF_ //initialize RC frame emitted when testing RF hardware
    U8 DataRCFrameEmitted[cNbBytesRCFrame] = mInitValueOfRCFrameEmitted();
    U8 NbByte;
#endif

    // Extract the key's Identifier transmitted from the RC frame received
    DATRfRCFrameIDEReceived =
      (  ( ((U32)(DataRCFrameReceived[0]) << 24) & (U32)0xFF000000UL )
       + ( ((U32)(DataRCFrameReceived[1]) << 16) & (U32)0x00FF0000 )
       + ( ((U32)(DataRCFrameReceived[2]) <<  8) & (U32)0x0000FF00 )
       + ( ((U32)(DataRCFrameReceived[3])      ) & (U32)0x000000FF )  );

    // Extract Sequence Increment Field from the RC frame received 
    RCFrameSIReceived =
      (  ( (((U16)DataRCFrameReceived[5]) >> 2) & (U16)0x003F ) //All bits to 0 except 1st 6 
       + ( (((U16)DataRCFrameReceived[4]) << 6) & (U16)0x03C0 )  );

    // Extract Rolling Code from the RC frame received
    DATRfRCFrameSRReceived.Format32Bit =   (U32)(((DataRCFrameReceived[8] << 6)& 0xFF) 
                  | (DataRCFrameReceived[9] >> 2));
    DATRfRCFrameSRReceived.Format32Bit = (DATRfRCFrameSRReceived.Format32Bit <<8) 
                  | (U32)(((DataRCFrameReceived[7] << 6)& 0xFF) | (DataRCFrameReceived[8] >> 2));
    DATRfRCFrameSRReceived.Format32Bit = (DATRfRCFrameSRReceived.Format32Bit <<8) 
                  | (U32)(((DataRCFrameReceived[6] << 6)& 0xFF) | (DataRCFrameReceived[7] >> 2));
    DATRfRCFrameSRReceived.Format32Bit = (DATRfRCFrameSRReceived.Format32Bit <<8) 
                  | (U32)(((DataRCFrameReceived[5] << 6)& 0xFF) | (DataRCFrameReceived[6] >> 2));

    // Extract the pushed button from the RC frame received
    RCFrameCIDReceived = (U8)(DataRCFrameReceived[4] >> 4) & (U8)0x0F;



#ifdef _TEST_RF_ //update counters used for RF hardware testing   
    for(NbByte = 0;
        ( (NbByte<cNbBytesRCFrame) && (DataRCFrameReceived[NbByte] == DataRCFrameEmitted[NbByte]) ); 
         NbByte++)
    {} //compare contents

    if((NbByte == cNbBytesRCFrame) && (DATRfNbRCBlocksReceivedAndOK < cNbMaxStockedInByte))
    {
        DATRfNbRCBlocksReceivedAndOK++;
    }
    else
    {} //nothing to do

    if (DATRfNbRCBlocksReceivedCrcOK < cNbMaxStockedInByte)
    {
        DATRfNbRCBlocksReceivedCrcOK++;
    }

#endif
}

//==============================================================================
//   Function Name : 
//     static void UpdateKeyResynchronisation( void )
//----------------------------------------------------------------------------
//   Function Role  :
//     allows to update if current Key needs to be resynchronise
//   Parameters Meaning :
//     
//   Result Meaning :
//     
//   Function  Description :
//     
//==============================================================================
static void UpdateKeyResynchronisation( void )
{
    U8 KeyNeedResync;

    KeyNeedResync = mDATRead (U8Bit, ResynchroRequest, Default);
                  //1 decalé de: la position de la clé
    KeyNeedResync |= (U8)(1 << IndiceKeyRf);
    mDATWrite (U8Bit, ResynchroRequest, KeyNeedResync, Default);
}

//==============================================================================
//   Function Name : 
//     static U32 ReBuildSI28Bits(U16 SI10BitsReceived, U32 SI28Bits)
//----------------------------------------------------------------------------
//   Function Role  :
//     
//   Parameters Meaning :
//      U16 SI10BitsReceived :  SI10Bits received
//      U32 SI28Bits :          Last SI28Bits saved.
//   Result Meaning :
//     
//   Function  Description :
//    SI10BitsReceived : 10 low bits of the SI28Bits used in the transponder to     
//    calculate the encryption.
//    This SI28Bits is increased when a key is pressed 
//    SI28Bits : enregistration in EEPROM of last SI28bits
//==============================================================================
static MEM_TYPE U32 ReBuildSI28Bits(U16 SI10BitsReceived, U32 SI28Bits)
{
    U16  SI10BitsPrevious;
    U32  SI28BitsPrevious; // SI28Bits of the last correct RC frame of this key
    U32  SI28BitsCalculated;
 
  
    SI28BitsPrevious = (SI28Bits & (U32)0x0FFFFFFF);    //force to 0 all bits except 28first
    SI10BitsPrevious = ((U16)SI28BitsPrevious) & 0x03FF;//force to 0 all bits except 10first


    // le SI28Bits calculed is the sum of :
    //                 - previous SI28bits which has its 10 low bits masked 
    //                 - SI10Bits received (sent to BCM in true value)
    //                 - potential carry over of 0x400

    if (SI10BitsPrevious < SI10BitsReceived) //less than 1024 pushes were done
    {
        SI28BitsCalculated = (SI28BitsPrevious & (U32)0x0FFFFC00) //force to 0 last 10 bits
                             + (U32)SI10BitsReceived;            //paste 10 SIbits received
    }
    else 
    {
        SI28BitsCalculated = (SI28BitsPrevious & (U32)0x0FFFFC00)  
                             + (U32)SI10BitsReceived
                             + (U32)0x400;
    }
    SI28BitsCalculated &= (U32)0x0FFFFFFF;  // to cancel a potential carry over on the bit 29.

    return ((U32)SI28BitsCalculated);   
}

//==============================================================================
//   Function Name : 
//     static U32 BuildingSI28BitsTheoric( U32 StartValue )
//----------------------------------------------------------------------------
//   Function Role  :
//     Allows to calculate the theoretical SI28Bits
//   Parameters Meaning :
//     
//   Result Meaning :
//     
//   Function  Description :
//     
//==============================================================================
static MEM_TYPE U32 BuildingSI28BitsTheoric(U32 SIStartValue)
{
    tDatRfMot32Bit Challenge; //New challenge calculated from SI10Bits and CID received

    //Building expected SI28Bits 
    SI28BitsLastRCFrameKnown = ReBuildSI28Bits(RCFrameSIReceived, (SIStartValue));

    //SR frame: SI + CID
    Challenge.Format32Bit 
       = (SI28BitsLastRCFrameKnown << 4) | (U8)(RCFrameCIDReceived & 0x0F);

    return( CalculRollingCodeTheoreticRCFrame(Challenge) );
}

//==============================================================================
//   Function Name : 
//     static U32 CalculRollingCodeTheoreticRCFrame(tDatRfMot32Bit Challenge)
//----------------------------------------------------------------------------
//   Function Role  :
//     
//   Parameters Meaning :
//     
//   Result Meaning :
//     
//   Function  Description :
//     
//==============================================================================
static MEM_TYPE U32 CalculRollingCodeTheoreticRCFrame(tDatRfMot32Bit Challenge)
{
    tDatRfMot32Bit KeyIdentifier;
    U8 I;
    U8 BuffRemoteSecretKey[cNbBytesRemoteSK];

#ifdef _QAC_
    // Disabled  QAC warning QC3715: Implicit cast : unsigned char to int
    // Cause switch structure 
    #pragma PRQA_MESSAGES_OFF 3715
#endif

    switch (IndiceKeyRf) //Read enregistered RSK
    {
        case cIndiceKeyRf0:
            for (I=0; I<cNbBytesRemoteSK; I++)
            {
                BuffRemoteSecretKey[I] = mDATReadTable (U8Bit, TableOfRemoteSecretKey1, I, Default);
            }
        break;

        case cIndiceKeyRf1:
            for (I=0; I<cNbBytesRemoteSK; I++)
            {
                 BuffRemoteSecretKey[I] = mDATReadTable (U8Bit, TableOfRemoteSecretKey2, I, Default);
            }
        break;

        case cIndiceKeyRf2:
            for (I=0; I<cNbBytesRemoteSK; I++)
            {
                 BuffRemoteSecretKey[I] = mDATReadTable (U8Bit, TableOfRemoteSecretKey3, I, Default);
            }
        break;

        case cIndiceKeyRf3:
            for (I=0; I<cNbBytesRemoteSK; I++)
            {
                 BuffRemoteSecretKey[I] = mDATReadTable (U8Bit, TableOfRemoteSecretKey4, I, Default);
            }
        break;

        //CCOV: ailievb: Cannot be covered because this default case rises explicit assert
        default:
            mLIBassert(cFalse);
        break;
    }

#ifdef _QAC_
    #pragma PRQA_MESSAGES_ON 3715
#endif

    KeyIdentifier.Format32Bit = mDATReadTable (U32Bit, TableOfKeyIdentifier, IndiceKeyRf, Default);
    pLIBPcfIdentifier = (U8*)(&KeyIdentifier.Format32Bit);  //Init variable for TAG function

    // Inversion of high bits to low bits to have an intel format.
    Challenge.Format32Bit
      = (((U32)(Challenge.Format8Bit.F8Bit1) << 24) & (U32)0xFF000000UL) 
       + (((U32)(Challenge.Format8Bit.F8Bit2) << 16) & (U32)0x00FF0000)
       + (((U32)(Challenge.Format8Bit.F8Bit3) << 8)  & (U32)0x0000FF00)
       + ((U32)(Challenge.Format8Bit.F8Bit4)        & (U32)0x000000FF);
    LIBPcfRandomNumber = Challenge.Format32Bit;  //Init variable for TAG function

    KeyIdentifier.Format32Bit
      =   (((U32)(KeyIdentifier.Format8Bit.F8Bit1) << 24) & (U32)0xFF000000UL) 
         + (((U32)(KeyIdentifier.Format8Bit.F8Bit2) << 16) & (U32)0x00FF0000)
         + (((U32)(KeyIdentifier.Format8Bit.F8Bit3) << 8)  & (U32)0x0000FF00)
         +  ((U32)(KeyIdentifier.Format8Bit.F8Bit4)        & (U32)0x000000FF);

    pLIBPcfSecretKey = BuffRemoteSecretKey;   // Init variable for TAG function
    LIBPcfCipheredData = (U32)0;             // Init variable for TAG function
    LIBPcfInitialize();
    LIBPcfCipherFunction(cNbBitsCryptage);       // Fill LIBPcfCipheredData
  
    return ((U32)LIBPcfCipheredData);
}

//=============================================================================
//  DESCRIPTION : CallBckReceptionSIFrame
//  
//  PARAMETERS (Type,Name,Min,Max) : 
//    (tAddress Adresse, tStatus Statut, tMsg * pMsg)
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION : 
//    Fonction called by LDB part to do a copy of the received SI frame
//     
//==============================================================================
static void CallBckReceptionSIFrame(tAddress Adresse, tStatus Statut, tMsg * pMsg)
{
    mLIBmemcpy ((U8*)DataSIFrameReceived, pMsg->pBuffer, cNbBytesSIFrame);
    SIFrameReceived = cTrue; //Flag to signal: SI frame received

#ifdef _TEST_RF_ //update counters used for RF hardware testing   
    if (DATRfNbSIBlocksReceived < cNbMaxStockedInByte)
    {
        DATRfNbSIBlocksReceived++;
    }
    else
    {} //nothing to do
#endif
}

//==============================================================================
//  DESCRIPTION : RfPeriodicTask
//  
//  PARAMETERS (Type,Name,Min,Max) : 
//    (tAddress Adresse, tStatus Statut, tMsg * pMsg)
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION : 
//    Fonction called by LDB part to do a copy of the received SI frame
//     
//==============================================================================
static void RfPeriodicTask(void)
{
    //---- Update all counter ----
    if (TempoSearchFramePeriod > 0)
    {
        TempoSearchFramePeriod--;
    }

    if (TempoAlarmITForRCReceptionTimeOut > 0)
    {
        TempoAlarmITForRCReceptionTimeOut--;
    }

    if (TempoAlarmITForLongPushWaitTimeOut > 0)
    {
        TempoAlarmITForLongPushWaitTimeOut--;
    }

    if (TempoAlarmITForLongPushReceiveTimeOut > 0)
    {
        TempoAlarmITForLongPushReceiveTimeOut--;
    }

#ifdef _DIAGNOSTIC_MEMO_    //For Diagnostic   
    {
        U8 Counter;
        //---------------------------------------------------------------------------
        for (Counter=0; Counter<cNbCodeDiagMemorized; Counter++)
        {
            if ((DATRfPushMemorized & (U8)(0x01 << Counter)) != 0)
            { // memorization activated
                TempoAlarmITForDiag[Counter]--;
                if (TempoAlarmITForDiag[Counter] == 0) // 2s elapsed 
                {
                    DATRfPushMemorized &= (U8)(~(U8)(0x01 << Counter)); //Reset Diag flag
                }
            }
        }  //-------------------------------------------------------------------------
    }
#endif

#ifdef _PASSING_RF_
    if (TempoAlarmITForPassingRf>0) 
    {
        TempoAlarmITForPassingRf--; //rearm "timer"
    }
    else
    {} //nothing to do
#endif
}
/* [LOCAL_FUNCTIONS_END] */


//==============================================================================
//...........................................................................
//.......................... EXPORTED FUNCTIONS.............................
//...........................................................................
//==============================================================================
//==============================================================================
//  DESCRIPTION : DATRfWakeUpBlockReceived
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE : True if a Rf WakeUp frame is received
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//     
//==============================================================================
BOOL DATRfWakeUpBlockReceived(void)
{
    // Execute periodic task
    RfPeriodicTask();

    //--------------------------------------------------------------
    // To launch the LDB_RF layer every cDATRfLDBSearchFramePeriodMs
    //--------------------------------------------------------------
    mLIBassert(RCReceptionTimeOutIsActive == cFalse);
    mLIBassert(LongPushTimeOutIsActive == cFalse);

    if (mDATRead(U1Bit, EEP_AUTRECRF, Default) == cTrue)
    {
        if (TempoSearchFramePeriod == 0)
        {
            SearchFrameInCourse = cTrue;
            TempoSearchFramePeriod = cSearchFramePeriodMs; // tempo shall be updated before LDB control
            LDBControl(cLDBChannelRf,cLDBRfSearchFrame); 
        }
    }
    else
    {
        LDBControl(cLDBChannelRf, cLDBRfDeactivateStrobe); // Prevent from HW activation
    }
    return (WakeUpBlockReceived);
}

//==============================================================================
//  DESCRIPTION : DATRfArmRCReceptionTimer
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//     
//==============================================================================
void DATRfArmRCReceptionTimer(void)
{
    //WakeUpBlock detection flag  is consumed
    WakeUpBlockReceived = cFalse;
    SIFrameReceived     = cFalse; //Flag positioned by LDBCallBack

    //An internal counter is used to generate the timer because timing TOS
    //functions are only available when BCM is awake
    TempoAlarmITForRCReceptionTimeOut = cRCReceptionTimeOut;
    RCReceptionTimeOutIsActive        = cTrue;    //flag
    LongPushTimeOutIsActive           = cFalse;   //flag
}

//==============================================================================
//  DESCRIPTION : DATRfNewRcBlockReceived
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//     
//==============================================================================
BOOL DATRfNewRcBlockReceived(void)
{
#ifdef X90_PROJECT
    return DATRfNewRcBlockReceived_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL DATRfNewRcBlockReceived_Static(void)
{
#endif
    BOOL RCBlockReceivedIsOK;

#ifdef _PASSING_RF_
#else
    BOOL NewKeyPressAndIdentifierOk;
    U32  KeyIdentifier;
    U32  RollingCodeCalculated;
#endif
    U8   ParityCodeCalculated;
    U8   i;

    // Execute periodic task
    RfPeriodicTask();

    //Default value (function return value)
    RCBlockReceivedIsOK = cFalse;

    if(RCFrameReceived == cTrue) //A RC frame has been received
    {  
        RCFrameReceived = cFalse; //Received frame flag is consumed

#ifndef X90_PROJECT // Cm007542: TRF_RECU is on when no frame detected
#ifdef _DIAGNOSTIC_MEMO_    //For Diagnostic   
    ArmerNbAlarmITForDiag(cDiagRfFrameReceived);
#endif
#endif
        //Verify Parity
        //-------------
        //Check RCframe data by calculating PARity byte and comparing it with PARity byte received
        ParityCodeCalculated = 0;
        for (i=0; i<(cNbBytesRCFrame-1); i++) //For each byte in block RC
        {  
             ParityCodeCalculated = (U8)(ParityCodeCalculated ^ DataRCFrameReceived[i]);
        }

        if (ParityCodeCalculated == DataRCFrameReceived[cNbBytesRCFrame - 1]) // Parity is Ok
        { 
            ExtractDataFromRCFrameReceived(); //Extract all data contained in the RC frame received

#ifdef X90_PROJECT // Cm007542: TRF_RECU is on when no frame detected
#ifdef _DIAGNOSTIC_MEMO_    //For Diagnostic (both for normal and passing RF mode)  
        ArmerNbAlarmITForDiag(cDiagRfFrameReceived);
#endif
#endif

#ifdef _PASSING_RF_
        RCBlockReceivedIsOK = cTrue; //RC frame is accepted 
#else

            //Verify IDE & SI
            //---------------
            // Test if this is a new key press 
            NewKeyPressAndIdentifierOk = cFalse;
            for (i=0; ((i<4) && (NewKeyPressAndIdentifierOk == cFalse)) ;i++)
            {
                KeyIdentifier = mDATReadTable (U32Bit, TableOfKeyIdentifier, i, Default);

                // IF (the KeyIdentifier is correct) AND (KeyIdentifier is knew) 
                // THEN NewKeyPressAndIdentifierOk = cTrue
                if (   (DATRfRCFrameIDEReceived == KeyIdentifier) 
                    && (RCFrameSIReceived
                    != ((U16)(mDATReadTable (U32Bit, TableOfCurrentResynchroValue, i, Default)) & 0x03FF)))
                {
                IndiceKeyRf = i;
                NewKeyPressAndIdentifierOk = cTrue;
                }  
                else
                { // Nothing to do
                } 
            } 


            //Verify RC
            //---------
            if (NewKeyPressAndIdentifierOk == cTrue) //New button pressed and identifier Ok
            { 
                //Building of expected SI28Bits 
                RollingCodeCalculated
                   = BuildingSI28BitsTheoric( (U32)(mDATReadTable (U32Bit, TableOfCurrentResynchroValue, IndiceKeyRf, Default)) );
      
                // Test of rolling code
               if (RollingCodeCalculated == DATRfRCFrameSRReceived.Format32Bit)
               { //The rolling code received is equal to previous received or in window(+0 +1024) 
           
                   RCBlockReceivedIsOK = cTrue; //RC frame is accepted 
               }
               else //The rolling code is out of acceptation window, but is it in the other 
                    //known resynchronisation windows?
               { 
                   //In all cases, a demand of resynchronisation is done.
                   UpdateKeyResynchronisation();
                   LDBRefreshWatchDog(); // invoke directly watchdog refreshment - needed for sleep mode
                   mDATWrite(U1Bit, PcfRefreshAllowed, cTrue, Default); // allow LIB_PCF to be preempted
    
                   //Building SI28Bits with initial value taught by BCM.Value used when key battery is changed
                   RollingCodeCalculated
                     = BuildingSI28BitsTheoric    ( (U32)((mDATReadTable (U32Bit, TableOfInitialResynchroValue, IndiceKeyRf, Default)) + (U32)0x08000200));

                   if (RollingCodeCalculated == DATRfRCFrameSRReceived.Format32Bit)    
                   { 
                       RCBlockReceivedIsOK = cTrue; //RC frame is accepted
                   }
                   else
                   { //Try with the last written resync value            
                       RollingCodeCalculated
                          = BuildingSI28BitsTheoric( (U32)(mDATReadTable (U32Bit, TableOfDefResynchroValueWritten, IndiceKeyRf, Default)) );

                       if (RollingCodeCalculated == DATRfRCFrameSRReceived.Format32Bit)    
                       {
                           RCBlockReceivedIsOK = cTrue; //RC frame is accepted
                       }
                       else
                       { //Try with the last read resync value              
                           RollingCodeCalculated
                              = BuildingSI28BitsTheoric( (U32)(mDATReadTable (U32Bit, TableOfDefResynchroValueRead, IndiceKeyRf, Default)) );

                           if (RollingCodeCalculated == DATRfRCFrameSRReceived.Format32Bit)    
                           {
                               RCBlockReceivedIsOK = cTrue; //RC frame is accepted
                           }
                           else
                           { //Try with the last written resync value when the key battery has been changed                
                               RollingCodeCalculated
                                  = BuildingSI28BitsTheoric( (U32)((mDATReadTable (U32Bit, TableOfDefResynchroValueWritten, IndiceKeyRf, Default)) + (U32)0x08000200));

                               if (RollingCodeCalculated == DATRfRCFrameSRReceived.Format32Bit)    
                               {
                                   RCBlockReceivedIsOK = cTrue; //RC frame is accepted
                               }
                               else
                               { //Try with the last read resync value when the key battery has been changed                  
                                   RollingCodeCalculated
                                     = BuildingSI28BitsTheoric( (U32)((mDATReadTable (U32Bit, TableOfDefResynchroValueRead, IndiceKeyRf, Default)) + (U32)0x08000200));

                                  //To decide whether RC frame is accepted
                                  RCBlockReceivedIsOK = (RollingCodeCalculated == DATRfRCFrameSRReceived.Format32Bit);
                               } 
                           }
                       }
                   }
                   mDATWrite(U1Bit, PcfRefreshAllowed, cFalse, Default); // forbid LIB_PCF to be preempted
               }
            }
            else
            { //Nothing to do: DATRfRCFrameIDEReceived or RCFrameSIReceived are not correct
            }
#endif //_PASSING_RF_
        }
        else //Bad parity, so RC frame is not accepted
        { //In case it was reset before because a 1st good RCframe was received
            //and so as to not wait the SIframe timeout
            RCReceptionTimeOutIsActive = cTrue; 
        }
    } 
    else
    { //Nothing to do, a RC frame has not been received
    }


#ifdef _DIAGNOSTIC_MEMO_    //For Diagnostic   
    if(RCBlockReceivedIsOK == cTrue)
    {
        ArmerNbAlarmITForDiag(cDiagRfFrameReceivedAndValid);
    }
     else
    {} //nothing to do
#endif

    return (RCBlockReceivedIsOK);
}

//==============================================================================
//  DESCRIPTION : DATRfRCReceptionTimeElapsedOrLongPushReceiveTimeElapsed
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//     
//==============================================================================
BOOL DATRfRCReceptionTimeElapsedOrLongPushReceiveTimeElapsed(void)
{
    BOOL TimeElapsed;
    TimeElapsed =
       (  (  (TempoAlarmITForRCReceptionTimeOut == 0) && RCReceptionTimeOutIsActive   )
          || (  (TempoAlarmITForLongPushReceiveTimeOut == 0) && LongPushTimeOutIsActive   )
       );  

    return (TimeElapsed);
}

//==============================================================================
//  DESCRIPTION : DATRfSearchWakeUpBlock
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//     
//==============================================================================
void DATRfSearchWakeUpBlock(void)
{
    LDBControl(cLDBChannelRf, cLDBRfStop);
    SearchFrameInCourse = cFalse;
    RCReceptionTimeOutIsActive = cFalse;
    // Stop Timeout for SI reception 
    LongPushTimeOutIsActive    = cFalse;
}

//==============================================================================
//  DESCRIPTION : DATRfShortPushDetectedAndArmLongPushTimer
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//     
//==============================================================================
void DATRfShortPushDetectedAndArmLongPushTimer(void)
{
#ifdef X90_PROJECT
    DATRfShortPushDetectedAndArmLongPushTimer_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DATRfShortPushDetectedAndArmLongPushTimer_Static(void)
{
#endif
    TOSSendControl(cTOSControlWakeUpRequest); //Wake LAP up

    //Button short push is saved for LAP to read
    ButtonPushed = (RCFrameCIDReceived & cMaskNonExistingButtons);

    //Stop Timeout for RC reception and save last SI block received in EEPROM
    RCReceptionTimeOutIsActive = cFalse;
#ifdef _PASSING_RF_
    mDATWriteTable (U32Bit, TableOfCurrentResynchroValue, 0, RCFrameSIReceived, Default);
#else
    mDATWriteTable (U32Bit, TableOfCurrentResynchroValue, IndiceKeyRf, SI28BitsLastRCFrameKnown, Default);
#endif

    //Start tempo for long push management
    LongPushTimeOutIsActive               = cTrue;
    TempoAlarmITForLongPushWaitTimeOut    = cLongPushWaitTimeOut;
    TempoAlarmITForLongPushReceiveTimeOut = cLongPushReceiveTimeOut;

#ifdef _DIAGNOSTIC_MEMO_    //For Diagnostic   
// Cm006427: SDO managed in LAP_DLK.
#if (!defined(X90_PROJECT) && !defined(COMPILATION_NATIVE))
    //Remember various buttons can be pressed simultaneously
    if((ButtonPushed & cDATRfShortPressButton1) == cDATRfShortPressButton1)   
    {
        ArmerNbAlarmITForDiag(cDiagShortPressButton1);
    }
    else
    {} //nothing to do
    if((ButtonPushed & cDATRfShortPressButton2) == cDATRfShortPressButton2)     
    {
        ArmerNbAlarmITForDiag(cDiagShortPressButton2);
    }
    else
    {} //nothing to do
    if((ButtonPushed & cDATRfShortPressButton3) == cDATRfShortPressButton3)     
    {
        ArmerNbAlarmITForDiag(cDiagShortPressButton3);
    }
    else
  {} //nothing to do
#endif
#endif
}

//==============================================================================
//  DESCRIPTION : DATRfSiBlockReceivedAndLongPushWaitTimeElapsed
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//     
//==============================================================================
BOOL DATRfSiBlockReceivedAndLongPushWaitTimeElapsed(void)
{
#ifdef X90_PROJECT
    return DATRfSiBlockReceivedAndLongPushWaitTimeElapsed_Static();
}
#pragma optimize=no_inline
static MEM_TYPE BOOL DATRfSiBlockReceivedAndLongPushWaitTimeElapsed_Static(void)
{
#endif
    BOOL  SIBlockReceivedIsOK;
#ifdef _PASSING_RF_
#else
    U16   SI10BitsRCFrame;
    tMot16Bit SI10BitsSIFrame;
#endif
#ifdef _TEST_RF_ //initialize SI frame emitted when testing RF hardware
    U8 DataSIFrameEmitted[cNbBytesSIFrame] = mInitValueOfSIFrameEmitted();
    U8 NbByte;
#endif

    //Default value
    SIBlockReceivedIsOK = cFalse;


    if(SIFrameReceived == cTrue)
    {
        SIFrameReceived = cFalse; //Received frame is consumed

#ifdef _PASSING_RF_
        SIBlockReceivedIsOK = cTrue; 
#else
        SI10BitsRCFrame
            = (U16)( (mDATReadTable (U32Bit, TableOfCurrentResynchroValue, IndiceKeyRf, Default) & (U16)0x03FF) ); 

        SI10BitsSIFrame.Format8Bit.F8Bit2 =  DataSIFrameReceived[0] >> 6;
        SI10BitsSIFrame.Format8Bit.F8Bit1 = (DataSIFrameReceived[0] << 2) | (DataSIFrameReceived[1] & 0x03);

        //Decides whether SI frame is accepted
        SIBlockReceivedIsOK = ( SI10BitsRCFrame == (SI10BitsSIFrame.Format16Bit & 0x03FF) ); 
#endif

#ifdef _TEST_RF_ //update counters used for RF hardware testing   
    for(NbByte = 0;
        ( (NbByte<cNbBytesSIFrame) && (DataSIFrameReceived[NbByte] == DataSIFrameEmitted[NbByte]) ); 
        NbByte++)
    {} //compare contents
    if((NbByte == cNbBytesSIFrame) && (DATRfNbSIBlocksReceivedAndOK < cNbMaxStockedInByte))
    {
        DATRfNbSIBlocksReceivedAndOK++;
    }
    else
    {} //nothing to do
#endif

  }
  else
  { //No SI frame was received
  }

    return (  (SIBlockReceivedIsOK == cTrue)  
    //SI blocks are ignored until after cDATRfLongPushWaitTimeOut
           && (TempoAlarmITForLongPushWaitTimeOut == 0) 
           && (TempoAlarmITForLongPushReceiveTimeOut > 0)
    //This condition is necessary to avoid the case in wish a WakeUpBlock followed
    //by an SIblock is received: SIblock acccepted only if an RCblock has been received
           && (LongPushTimeOutIsActive == cTrue) 
           );
}

//==============================================================================
//  DESCRIPTION : DATRfLongPushDetected
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//     
//==============================================================================
void DATRfLongPushDetected(void)
{
#ifdef X90_PROJECT
    DATRfLongPushDetected_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DATRfLongPushDetected_Static(void)
{
#endif
    //Button long push is saved for LAP to read
#ifdef X90_PROJECT
    ButtonPushed = 0; // no long pushes for X90
    
    //adzhelp:  NOPs added so that object file produced from rev. 1.15 to be identical with 1.16
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();
#else
    ButtonPushed = ((RCFrameCIDReceived << 4) & cMaskNonExistingButtons);
#endif

    // it's always true at this level
    mLIBassert(LongPushTimeOutIsActive == cTrue);
    // Force TimeOut to pass on to SearchFrame mode
    // TempoAlarmITForLongPushReceiveTimeOut = 0;
    // Stop Timeout for SI reception 
    LongPushTimeOutIsActive = cFalse;

#ifdef _DIAGNOSTIC_MEMO_    //For Diagnostic   
    //Remember various buttons can be pressed simultaneously
    if ( (ButtonPushed & cDATRfLongPressButton1) == cDATRfLongPressButton1)   
    {
        ArmerNbAlarmITForDiag(cDiagLongPressButton1);
    }
    if ( (ButtonPushed & cDATRfLongPressButton2) == cDATRfLongPressButton2)     
    {
        ArmerNbAlarmITForDiag(cDiagLongPressButton2);
    }
    if ( (ButtonPushed & cDATRfLongPressButton3) == cDATRfLongPressButton3)     
    {
        ArmerNbAlarmITForDiag(cDiagLongPressButton3);
    }
#endif
}
/* [GRAPH_FUNCTIONS_END] */


//==============================================================================
//  DESCRIPTION : DATRfReadButtonState
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   Button State (on/off)
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//     
//==============================================================================
BOOL DATRfReadButtonState(U8 Button)
{
    BOOL  ButtonState;

    //Remember various buttons can be pressed at the same time
    if ((ButtonPushed & Button) == Button)
    {
        ButtonState = cButtonIsPushed;

        //Reset buttons read
        ButtonPushed &= (U8)~Button;
    }
    else
    {
        ButtonState = cNoPushedButton;
    }
 
    return (ButtonState);
}

//==============================================================================
//  DESCRIPTION : DATRfCallBackCtrl
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//     
//==============================================================================
void DATRfCallBackCtrl(tCtrl Ctrl)
{
    if (Ctrl == cLDBRfWakeUpReceived)
    {
        mLIBassert((RCReceptionTimeOutIsActive == cFalse) && (LongPushTimeOutIsActive == cFalse));
        WakeUpBlockReceived = cTrue;
#ifdef _TEST_RF_ //update counter used for RF hardware testing
        if(DATRfNbWakeUpBlocksReceived < cNbMaxStockedInByte)
        {
            DATRfNbWakeUpBlocksReceived++;
        }
#endif
    }
    else if (Ctrl == cLDBRfControlSleepTick)
    {
        // GraphEngineTaskSleep is on 20 ms and LDBSleepTick is on 20 ms
        // so task needs to be activated directly by sleep system timer interrupt context
        //CCOV: ailievb: Sharing of sleep timer between RF adn Immo, can't be tested at unit test(covered)
        TOSActivateTask(cTOSTaskIdGraphEngineTaskSleep);
    }
    else if (Ctrl == cLDBRfDecrementTempoSearchFrame)
    {
        //CCOV: ailievb: synchronization with LDB sleep ticks, can't be tested at unit test(covered)
        mLIBassert(TempoSearchFramePeriod > 0);
        TempoSearchFramePeriod--;
        // decrement tempo in order to synchronize with LDB sleep ticks with active peripheral clock
    }
    else  // Enable sleep mode, WakeUp frame not received
    {
        mLIBassert(Ctrl == cLDBRfWakeUpNotReceived);
        SearchFrameInCourse = cFalse;
    }
}

//==============================================================================
//  DESCRIPTION : DATRfCallBackEndCtrl
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//     
//==============================================================================
void DATRfCallBackEndCtrl(tCtrl Ctrl, tStatus Status) 
{
    mLIBassert (Status == cLDBCorrect); //cLDBCorrect defined in ldb.h.
}

//==============================================================================
//  DESCRIPTION : DATRfInit
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION : Function called at reset or StartRf
//     
//==============================================================================
void DATRfInit(void)
{
#ifdef X90_PROJECT
    DATRfInit_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DATRfInit_Static(void)
{
#endif
    mLIBassert(cDATRfLDBSearchFramePeriodMs < cDATRfWakeUpBlockDuration);
    mLIBassert((cDATRfLDBSearchFramePeriodMs % cDATCpuSleepGraphEnginePeriodMs) == 0);

    //Init variables
    SearchFrameInCourse  = cFalse; //Flag positioned by LDBCallBack
    WakeUpBlockReceived  = cFalse; //Flag positioned by LDBCallBack
    RCFrameReceived      = cFalse; //Flag positioned by LDBCallBack
    SIFrameReceived      = cFalse; //Flag positioned by LDBCallBack

    TempoSearchFramePeriod = 0;

    //Init RCReception "timer",SIWait "timer" and SIReception "timer"
    mLIBassert((cDATRfRCReceptionTimeOut % cDATCpuSleepGraphEnginePeriodMs) == 0);
    TempoAlarmITForRCReceptionTimeOut = cRCReceptionTimeOut;

    mLIBassert((cDATRfLongPushWaitTimeOut % cDATCpuSleepGraphEnginePeriodMs) == 0);
    TempoAlarmITForLongPushWaitTimeOut = cLongPushWaitTimeOut;

    mLIBassert((cDATRfLongPushReceiveTimeOut % cDATCpuSleepGraphEnginePeriodMs) == 0);
    TempoAlarmITForLongPushReceiveTimeOut = cLongPushReceiveTimeOut;

#ifdef _PASSING_RF_
    TempoAlarmITForPassingRf = cRCReceptionTimeOut;
#endif

    RCReceptionTimeOutIsActive = cFalse; //Flag, indicates if timer is active
    LongPushTimeOutIsActive    = cFalse; //Flag, indicates if timer is active

    //Frames initialized to 0
    mLIBmemset ((U8*)DataRCFrameReceived,0,cNbBytesRCFrame); 
#ifdef _QAC_
    { U8 i;
        for(i=0; i<cNbBytesSIFrame ; i++)
        {
            DataSIFrameReceived[0] = 0;
        }
    }
#else
    mLIBmemset ((U8*)DataSIFrameReceived,0,cNbBytesSIFrame); 
#endif
    DATRfRCFrameIDEReceived = 0;
    RCFrameSIReceived       = 0; 
    RCFrameCIDReceived      = 0;

    SI28BitsLastRCFrameKnown = 0;
    ButtonPushed = cNoPushedButton; 

#ifdef _DIAGNOSTIC_MEMO_ //for Diagnostic   
    {
        DATRfPushMemorized = cNoPushedButton;
        mLIBmemset(TempoAlarmITForDiag,cDiagMemorizationTime,cNbCodeDiagMemorized);
    }
#endif
#ifdef _TEST_RF_ //init counters used for RF hardware testing   
    DATRfNbWakeUpBlocksReceived  = 0;
    DATRfNbRCBlocksReceived      = 0;
    DATRfNbRCBlocksReceivedAndOK = 0;
    DATRfNbRCBlocksReceivedCrcOK = 0;
    DATRfNbSIBlocksReceived      = 0;
    DATRfNbSIBlocksReceivedAndOK = 0;
#endif
}

//==============================================================================
//  DESCRIPTION : DATRfStart
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//     
//==============================================================================
void DATRfStart(void)
{
    DATRfInit();
    // Launch Rf graph
    TOSSeqActivateGraph(cTOSSeqGraphIdDATRfReceptionManagement);
}

//==============================================================================
//  DESCRIPTION : DATRfStop
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//     
//==============================================================================
void DATRfStop(void)
{
    // Stop LDBRf
    LDBControl (cLDBChannelRf, cLDBRfStop);
    // Stop Rf graph
    TOSSeqDeactivateGraph(cTOSSeqGraphIdDATRfReceptionManagement);
    //Force TimeOut to authorise sleep mode
    LongPushTimeOutIsActive = cFalse;
}

//==============================================================================
//  DESCRIPTION : DATRfInitializeRFTest
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//     
//==============================================================================
#ifdef _TEST_RF_ //init counters used for RF hardware testing   
void DATRfInitializeRFTest(void) 
{
    DATRfNbWakeUpBlocksReceived  = 0;
    DATRfNbRCBlocksReceived      = 0;
    DATRfNbRCBlocksReceivedAndOK = 0;
    DATRfNbRCBlocksReceivedCrcOK = 0;
    DATRfNbSIBlocksReceived      = 0;
    DATRfNbSIBlocksReceivedAndOK = 0;
}
#endif

//==============================================================================
//  DESCRIPTION : DATRfIsAnybodyMaintainActiveState 
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//     
//==============================================================================
void DATRfIsAnybodyMaintainActiveSleepState(void)
{
    // Sleep not allowed as long as RF wakeUp search is in course
    if (SearchFrameInCourse != cFalse)
    {
        TOSWriteSignal(cTOSSignalSomebodyMaintainActiveSleepState);
     }
}

//==============================================================================
//  DESCRIPTION : DATRfIsAnybodyMaintainActiveState 
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :   refer to Detailed Design Document
//     
//==============================================================================
void DATRfIsAnybodyMaintainActiveState(void)
{
    // Sleep not allowed as long as we're waiting for posible SI blocks 
    // or there are pending requests (not read by LAP)
    if ((SearchFrameInCourse != cFalse)
        ||(ButtonPushed != cNoPushedButton)) 
    {
        TOSWriteSignal (cTOSSignalSomebodyMaintainActiveState);
    }
}


//==============================================================================
//  DESCRIPTION : DATRfArmerNbAlarmITForDiag 
//  
//  PARAMETERS (Type,Name,Min,Max) :   none
//
//  RETURN VALUE :   none
// 
//  DESIGN INFORMATION :  Cm006427: SDO managed in LAP_DLK.
//     
//==============================================================================
#ifdef _DIAGNOSTIC_MEMO_    //For Diagnostic
MEM_TYPE void DATRfArmerNbAlarmITForDiag(U8 u8RfButtonCodeP)
{
    ArmerNbAlarmITForDiag(u8RfButtonCodeP);           
}
#endif
/* [EXPORTED_FUNCTIONS_END] */
