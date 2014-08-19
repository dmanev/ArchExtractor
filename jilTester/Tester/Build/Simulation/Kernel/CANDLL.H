// tcCanDll.h: interface for the tcCanDll class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCCANDLL_H__9C66F9D8_60F4_11D7_B772_0001030A1077__INCLUDED_)
#define AFX_TCCANDLL_H__9C66F9D8_60F4_11D7_B772_0001030A1077__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "deftypes.h"

#ifdef CANDLL_EXPORTS
#define CANDLL_API __declspec(dllexport)
#else
#define CANDLL_API __declspec(dllimport)
#endif

//---- Set 8 bytes alignment ----
#pragma pack( push , 8)

//*****************************************************************************
// Can constant
//*****************************************************************************
#define cCanCardAUTOMATIC             "AUTOMATIC"
#define cCanCardNSIPort0              "NSI,Port0"
#define cCanCardNSIPort1              "NSI,Port1"
#define cCanCardVECTORCanAC2PciXPort0 "VECTOR CanAC2Pci,Port0"
#define cCanCardVECTORCanAC2PciXPort1 "VECTOR CanAC2Pci,Port1"
#define cCanCardVECTORCanCardXPort0   "VECTOR CanCardX,Port0"
#define cCanCardVECTORCanCardXPort1   "VECTOR CanCardX,Port1"
#define cCanCardVECTORCanCardXLPort0  "VECTOR CanCardXL,Port0"
#define cCanCardVECTORCanCardXLPort1  "VECTOR CanCardXL,Port1"
#define cCanCardVECTORCanBoardXLPort0 "VECTOR CanBoardXL,Port0"
#define cCanCardVECTORCanBoardXLPort1 "VECTOR CanBoardXL,Port1"
#define cCanCardVECTORCanCaseXLPort0  "VECTOR CanCaseXL,Port0"
#define cCanCardVECTORCanCaseXLPort1  "VECTOR CanCaseXL,Port1"
#define cCanCardNIPort0               "NI,Port0"
#define cCanCardNIPort1               "NI,Port1"
#define cCanCardJCIPort0             "JCI,Port0"
#define cCanCardAIXIACom1Port0        "AIXIA,Com1,Port0"
#define cCanCardAIXIACom2Port0        "AIXIA,Com2,Port0"
#define cCanCardADLINKPort0           "ADLINK,Port0"
#define cCanCardADLINKPort1           "ADLINK,Port1"
#define cCanCardVIRTUAL               "VIRTUAL"

// If you use, this constant like Can card name, you must define the port number
// you can set the port automatically by adding (portNumber) at the end
// sample: VECTOR(0x0602)
#define cCanCardNSI                   "NSI"
#define cCanCardVECTOR                "VECTOR"
#define cCanCardNI                    "NI"
#define cCanCardJCI                  "JCI"
#define cCanCardAIXIA                 "AIXIA"
#define cCanCardADLINK                 "ADLINK"

#define cMaxCanFrameLength            8
#define cMaxCanMsgLength              4095

#define cCanErrorFlag                 0x20000000
#define cCanRemoteFrameFlag           0x40000000
#define cXTDFrameFlag                 0x80000000
#define cSTDFrameFlag                 0x00000000
#define cXTDFrameMask                 0x1FFFFFFF
#define cSTDFrameMask                 0x000007FF

#define cCanErrorFrameError           0x20000001
#define cCanErrorBusOff               0x20000002
#define cCanErrorNerr                 0x20000004

//*****************************************************************************
// Default parameter
//*****************************************************************************
#define cDefaultPciPaddingByte        0xC2  // Frame Padding byte
#define cDefaultPciFC_WFTmax          4     // Maximum number of wait requested
#define cDefaultPciFC_BS              3     // Maximum number of bloc accepted
#define cDefaultPciFC_STmin           0     // Minimum time between CF
#define cDefaultPciFC_FS              0     // FC state (wait or not)

//*****************************************************************************
// Can control type
//*****************************************************************************
typedef enum
{
  cCanChangeBaudrateControl,
  cCanAckControl,
} tCanControl;


//*****************************************************************************
// Can communication type
//*****************************************************************************
typedef enum
{
  cCanTransmissionAndReceptionType,
  cCanPeriodicalTransmissionType,
  cCanTransmissionMultiIdType,
  cCanReceptionMultiIdType
} tCanCommunicationType;

//*****************************************************************************
// Message callback
//*****************************************************************************
typedef enum
{
  cNormalMsg,
  cWarningMsg,
  cErrorMsg,
} tMsgType;

//*****************************************************************************
// Can frame and Can message
//*****************************************************************************
typedef struct
{
  U8  Longueur;
  U8  Buffer[cMaxCanFrameLength];
} tTrameCan;

typedef struct
{
  U16 Longueur;
  U8* Buffer;
} tMsgCan;

//*****************************************************************************
// Can object class
//*****************************************************************************
class tcCanDll;
class tObjetCanUU;
class tObjetCanUS;
class tObjetCanAS;
class tObjetCanSession;

//---- CallBack prototype ----
typedef void (*tpfCallBackCanMsg)                 (tMsgType,const char*,void*);
                                                  
typedef void (*tpfCallBackCanUUCon)               (tObjetCanUU*,void*);
typedef void (*tpfCallBackCanUUInd)               (tObjetCanUU*,tTrameCan*,void*);
                                                  
typedef void (*tpfCallBackCanUSCon)               (tObjetCanUS*,void*);
typedef void (*tpfCallBackCanUSInd)               (tObjetCanUS*,tMsgCan*,void*);
typedef void (*tpfCallBackCanUSIndSpy)            (tObjetCanUS*,tMsgCan*,U8 ,void*);
                                                  
typedef void (*tpfCallBackCanASCon)               (tObjetCanAS*,void*);
typedef void (*tpfCallBackCanASInd)               (tObjetCanAS*,tMsgCan*,void*);
typedef void (*tpfCallBackCanASIndSpy)            (tObjetCanAS*,tMsgCan*,U8 ,void*);

typedef void (*tpfCallBackCanSessionConnectCon)   (tObjetCanSession*,void*);
typedef void (*tpfCallBackCanSessionConnectInd)   (tObjetCanSession*,void*);
typedef void (*tpfCallBackCanSessionCon)          (tObjetCanSession*,void*);
typedef void (*tpfCallBackCanSessionInd)          (tObjetCanSession*,tMsgCan*,void*);
typedef void (*tpfCallBackCanSessionDeconnectCon) (tObjetCanSession*,void*);
typedef void (*tpfCallBackCanSessionDeconnectInd) (tObjetCanSession*,void*);
typedef void (*tpfCallBackCanSessionConnectSpy)   (tObjetCanSession*,U8,void*);
typedef void (*tpfCallBackCanSessionIndSpy)       (tObjetCanSession*,tMsgCan*,U8,void*);
typedef void (*tpfCallBackCanSessionDeconnectSpy) (tObjetCanSession*,U8,void*);

//---- Can UU class ----
class tObjetCanUU
{
public:
  tObjetCanUU()
  {
    Periode       = 0;
    FCallBackCon  = NULL;
    FCallBackInd  = NULL;
    pParam        = NULL;
    ModeHighVoltage = cFalse;
    memset(Reserved,0,sizeof(Reserved));
  }

public:
  U32               Id;                 // XTD id begin by 0x80000000
  tCanCommunicationType CommunicationType;
  U32               Periode;            // Transmission Period (ms)
  U8                ModeHighVoltage;
  U8                Reserved[127];      // Reserved for future evolution

public:
  tpfCallBackCanUUCon   FCallBackCon;       // End transmission callback
  tpfCallBackCanUUInd   FCallBackInd;       // Reception callback
  void*                 ParamCallBackCon;
  void*                 ParamCallBackInd;

  void* pParam;                             // Reserved Param, DO NOT CHANGED
};

//---- SegmentationInfo class ----
class tSegmentationInfo
{
public:
  tSegmentationInfo()
  {
    NoPadding       = cFalse;
    PaddingByte     = cDefaultPciPaddingByte;
    RetryStategyNb  = 0;
    FC_BS           = cDefaultPciFC_BS;
    FC_STmin        = cDefaultPciFC_STmin;
    FC_FS           = cDefaultPciFC_FS;
    FC_WFTmax       = cDefaultPciFC_WFTmax;
    memset(Reserved,0,sizeof(Reserved));
  };

public:
  U8  NoPadding;                    // No padding
  U8    PaddingByte;                  // Padding byte
  U8    RetryStategyNb;               // Retry strategy
  U8    FC_BS;
  U8    FC_STmin;
  U8    FC_FS;
  U8    FC_WFTmax;
  U8    Reserved[128];                // Reserved for future evolution
};

//---- SegmentedCanObject class ----
class tSegmentedCanObject
{
public:
  tSegmentedCanObject()
  {
    SpyMode         = cFalse;
    pParam          = NULL;
    memset(Reserved,0,sizeof(Reserved));
  };

public:
  U8  SpyMode;                      // SpyMode
  U32   IdReq;                        // Transmission Id
  U32   IdRep;                        // Reception Id
  U8    Reserved[128];                // Reserved for future evolution

  tSegmentationInfo SegmentationInfo;

  void*     pParam;                       // Reserved Param, DO NOT CHANGED
};

//---- Can US class ----
class tObjetCanUS : public tSegmentedCanObject
{
public:
  tObjetCanUS()
  {
    FCallBackCon    = NULL;
    FCallBackInd    = NULL;
    FCallBackIndSpy = NULL;
  }

public:
  tpfCallBackCanUSCon     FCallBackCon;      // Fin d'émission
  tpfCallBackCanUSInd     FCallBackInd;      // Réception
  tpfCallBackCanUSIndSpy  FCallBackIndSpy;   // Spy
  void*                   ParamCallBackCon;
  void*                   ParamCallBackInd;
  void*                   ParamCallBackIndSpy;
};

//---- Can AS class ----
class tObjetCanAS : public tSegmentedCanObject
{
public:
  tObjetCanAS() 
  { 
    FCallBackCon    = NULL;
    FCallBackInd    = NULL;
    FCallBackIndSpy = NULL;
  }

public:
  tpfCallBackCanASCon     FCallBackCon;      // End transmission callback
  tpfCallBackCanASInd     FCallBackInd;      // Reception callback
  tpfCallBackCanASIndSpy  FCallBackIndSpy;   // Spy callback
  void*                   ParamCallBackCon;
  void*                   ParamCallBackInd;
  void*                   ParamCallBackIndSpy;
};

//---- Can Session class ----
class tObjetCanSession : public tSegmentedCanObject
{
public:
  tObjetCanSession()  
  { 
    SpyMode                   = cFalse;
    FCallBackConnectCon       = NULL;
    FCallBackConnectInd       = NULL;
    FCallBackCon              = NULL;
    FCallBackInd              = NULL;
    FCallBackDeconnectCon     = NULL;
    FCallBackDeconnectInd     = NULL;
    FCallBackConnectIndSpy    = NULL;
    FCallBackIndSpy           = NULL;
    FCallBackDeconnectIndSpy  = NULL;
  }

public:
  tpfCallBackCanSessionConnectCon   FCallBackConnectCon;      // End connection callback
  tpfCallBackCanSessionConnectInd   FCallBackConnectInd;      // Start connection callback
  tpfCallBackCanSessionCon          FCallBackCon;             // End transmission callback
  tpfCallBackCanSessionInd          FCallBackInd;             // Reception callback
  tpfCallBackCanSessionDeconnectCon FCallBackDeconnectCon;    // End deconnection callback
  tpfCallBackCanSessionDeconnectInd FCallBackDeconnectInd;    // Start deconnection callback
  tpfCallBackCanSessionConnectSpy   FCallBackConnectIndSpy;   // Spy connection callback
  tpfCallBackCanSessionIndSpy       FCallBackIndSpy;          // Spy callback
  tpfCallBackCanSessionDeconnectSpy FCallBackDeconnectIndSpy; // Spy deconnection callback
  void*                             ParamCallBackConnectCon;
  void*                             ParamCallBackConnectInd;
  void*                             ParamCallBackCon;
  void*                             ParamCallBackInd;
  void*                             ParamCallBackDeconnectCon;
  void*                             ParamCallBackDeconnectInd;
  void*                             ParamCallBackConnectIndSpy;
  void*                             ParamCallBackIndSpy;
  void*                             ParamCallBackDeconnectIndSpy;
};

//*****************************************************************************
// tcParamCan class
//*****************************************************************************
class tcParamCan
{
public:
  tcParamCan()
  {
    strcpy(CanCardName,cCanCardAUTOMATIC);
    Port          = 0;    // Useless if can card port name is defined in can card name
    BaudRate      = 500000;
    Spy           = cFalse;
    QueueRead     = 20;
    QueueWrite    = 20;
    CodeStd       = 0;
    MaskStd       = 0;      
    CodeXtd       = 0;
    MaskXtd       = 0;
    FCallBackMsg  = NULL;
    memset(Reserved,0,sizeof(Reserved));
  }

public:
  char          CanCardName[MAX_PATH];  // If Name is cCanCardAUTOMATIC, the name will be replaced by found card name

  U16       Port;
  U32       BaudRate;
  U8        Spy;                    // Acquit or not can frame
  U8        QueueRead;                
  U8        QueueWrite;               
                                          
  U32       CodeStd;                  
  U32       MaskStd;                // 0 Don't care, 1 must match
  U32       CodeXtd;                  
  U32       MaskXtd;                // 0 Don't care, 1 must match

  tpfCallBackCanMsg FCallBackMsg;
  void*             ParamCallBackMsg;

  void*         Param1;                 // Param used for spécific card
  void*         Param2;                 

  U8        Reserved[128];          // Reserved for future evolution
};

//*****************************************************************************
// tcCanDll class
//*****************************************************************************
class CANDLL_API tcCanDll
{
public:
  //---- Retrieve version of tcCanDll ----
  static U16 GetVersion();
  //---- Retrieve Can Card list ---- > If CanCardName is NULL, it return the number of can card available
  static U8 GetCanCardListAvailable(U8 Num,char* CanCardName);

public:
  tcCanDll(tcParamCan* pParamCan);
  virtual ~tcCanDll();

public:
  //---- Can timer ----
  static void     InitializeCanTimer();
  static void     ExecuteCanTimer(U32 Date);
  static U32      GetCanTimerDate();

  //---- Can control ---
  U8      Control(tCanControl CanControl,void* Param);

  //---- CallBackMsg ----
  void      SetCallBackMsg(tpfCallBackCanMsg FCallBackMsg,void* ParamCallBackMsg);

  //---- Session object ----
  U8  AddCanObject(tObjetCanSession* pObjetCan);
  void      RemoveCanObjet(tObjetCanSession* pObjetCan);

  U8  Connect(tObjetCanSession* pObjetCan);
  U8  Deconnect(tObjetCanSession* pObjetCan);
  U8  Req(tObjetCanSession* pObjetCan,tMsgCan* pMsg);

  //---- ASDT object ----
  U8  AddCanObject(tObjetCanAS* pObjetCan);
  void      RemoveCanObjet(tObjetCanAS* pObjetCan);

  U8  Req(tObjetCanAS* pObjetCan,tMsgCan* pMsg);

  //---- USDT object ----
  U8  AddCanObject(tObjetCanUS* pObjetCan);
  void      RemoveCanObjet(tObjetCanUS* pObjetCan);

  U8  Req(tObjetCanUS* pObjetCan,tMsgCan* pMsg);

  //---- UUDT object ----
  U8  AddCanObject(tObjetCanUU* pObjetCan);
  void      RemoveCanObjet(tObjetCanUU* pObjetCan);

  U8  Req(tObjetCanUU* pObjetCan,tTrameCan* pTrame,U8 EnvoiImmediat = cTrue);
  U8  ActivateReqPeriodical(tObjetCanUU* pObjetCan,U8 Active = cTrue);
  
protected:
  // Can card Handle, reserved
  void*     m_pParam;
};


//---- Set default alignment ----
#pragma pack( pop )

#endif // !defined(AFX_TCCANDLL_H__9C66F9D8_60F4_11D7_B772_0001030A1077__INCLUDED_)
