//        ScanAllDll API
///////////////////////////////////////////////////////////////////////////////

#ifndef SCANALLDLL_H
#define SCANALLDLL_H

#ifdef __cplusplus
extern "C" {
#endif

    /* Used for function prototypes */
#define _SADFUNC_
    /*
    #if (__FLAT__) || defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
      #if (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED) || defined(__BORLANDC__)
        #define _SADFUNC_     __stdcall
    #error "1"
      #else
        #define _SADFUNC_
    #error "2"
      #endif
    #else
      #define _SADFUNC_       _far _pascal
    #error "3"
    #endif
    */
#ifndef DYNAMIC_SCANALLDLL_DRIVER   // Static loading
    // The following ifdef block is the standard way of creating macros which make exporting
    // from a DLL simpler. All files within this DLL are compiled with the SCANALLDLL_EXPORTS
    // symbol defined on the command line. this symbol should not be defined on any project
    // that uses this DLL. This way any other project whose source files include this file see
    // SCANALLDLL_API functions as being imported from a DLL, wheras this DLL sees symbols
    // defined with this macro as being exported.
  #ifdef SCANALLDLL_EXPORTS
    #define SCANALLDLL_API      __declspec(dllexport)
  #else
    #define SCANALLDLL_API      __declspec(dllimport)
  #endif
#endif

    //-----------------------------------------------------------------------------
    //          Definition
    //-----------------------------------------------------------------------------
    //----- Includes files -----
#include "deftypes.h"

    // 8 bytes alignment
#pragma pack( push , 8)

    //----- Handle definition -----
#define cSADInvalidHandle                   0xFFFFFFFF
#define cSADAllHandle                       0xFFFFFFFE
    typedef U32 tSADHandle;
    typedef U32 tSADGraphHandle;

    //----- Constant definition -----
#define cSADMaxNameLength                   128

    //----- Command definition -----
    typedef enum
    {
        cSADStart,                      // Customer cde
        cSADStop,                       // Customer cde
        cSADOpen,                       // TreeView cde
        cSADToggleRealTimeDisplay,      // Customer cde
        cSADCreateSupplier,             // TreeView cde
        cSADSave,                       // Customer cde
        cSADSerialize,                  // Customer cde
        cSADGetStatus,                  // Customer cde
        cSADGetCommandEnable,           // Customer cde
        cSADToggleTimeChronological,    // Customer cde
        cSADToggleTimeAbsolute,         // Customer cde
        cSADToggleTimeReal,             // Customer cde
        cSADClear,                      // Customer cde
        cSADApplyCdeToAll,              // Customer cde
        cSADToggleHHSS,                 // Customer cde
    } tSADCommandType;

    //----- Customer command enable definition -----
    typedef U32 tSADCustomerUserCommandEnable;
#define cSADStartStopEnable                 0x0001
#define cSADToggleRealTimeDisplayEnable     0x0002
#define cSADSaveEnable                      0x0004
#define cSADToggleTimeChronologicalEnable   0x0008
#define cSADToggleTimeAbsoluteEnable        0x0010
#define cSADToggleTimeRealEnable            0x0020
#define cSADClearEnable                     0x0040
#define cSADHHSSEnable                      0x0080

    //----- Command status definition -----
    typedef U32 tSADCustomerStatus;
#define cSADCustomerStarted                 0x0001
#define cSADCustomerTraceConnected          0x0002
#define cSADCustomerTimeChronological       0x0004
#define cSADCustomerTimeAbsolute            0x0008
#define cSADCustomerRealTimeDisplay         0x0010
#define cSADCustomerTimeReal                0x0020
#define cSADCustomerApplyCdeToAll           0x0040
#define cSADCustomerHHSS                    0x0080

    //----- Customer command definition -----
    typedef enum
    {
        cSADTx,
    } tSADCallBackCommandType;

    //----- Status definition -----
    typedef enum
    {
        cSADOk,
        cSADErrorMutex,
        cSADDeactivated,
        cSADNotConnected,
        cSADAlreadyConnected,
        cSADError,
    } tSADStatus;

    //----- Trace type definition -----
    typedef enum
    {
        cSADUndefinedType,
        cSADTextType,
        cSADFrameType,          // Buffer + length
        cSADAdrFrameType,       // Id + Buffer + length
        cSADDoubleAdrFrameType, // Id1 + Id2 + Buffer + length
        cSADGraphType,          // Graph
    } tSADTraceType;

    //----- Common CallBack definition -----
    typedef BOOL (*tSADCallBackCde)(tSADCallBackCommandType,void*,void*);

    //----- Frame type definition -----
#define cSADTypeTxFlag          0x80    // Rx        = 0, Tx        = 1
#define cSADTypeFrameTextFlag   0x40    // FrameData = 0, FrameText = 1
#define cSADTypeTextFlag        0x20    // NoText    = 1, Text      = 1
#define cSADTypeErrorFlag       0x10    // NoError   = 0, Error     = 1

#define cSADTypeStartFlag       0x01    // INTERNAL:  Started frame

    typedef U8 tSADTypeFlag;

#define cSADFixedBufferSize     4096

    //----- Text type definition -----
    typedef struct
    {
        tSADTypeFlag            Type;
        U32                 Time;
        COLORREF                Color;
    } tSADTextInfo;

    typedef struct
    {
        tSADTextInfo            Info;
        const char*             Buffer;
    } tSADTextType;

    typedef struct
    {
        COLORREF                Color;
        char                    Buffer[cSADFixedBufferSize];
    } tSADFixedTextType;

    //----- Frame type definition -----
    typedef struct
    {
        tSADTypeFlag            Type;                 // RX/TX, Text,Buffer
        U32                 Time;
        U32                 Lng;
    } tSADFrameInfo;

    typedef struct
    {
        tSADFrameInfo           Info;
        const U8*           Buffer;
    } tSADFrameType;

    typedef struct
    {
        U32                 Lng;
        U8                  Buffer[cSADFixedBufferSize];
    } tSADFixedFrameType;

    //----- AdrFrame type definition -----
    typedef struct
    {
        tSADTypeFlag            Type;
        U32                 Time;
        U32                 Lng;
        U32                 Adr;
    } tSADAdrFrameInfo;

    typedef struct
    {
        tSADAdrFrameInfo        Info;
        const U8*           Buffer;
    } tSADAdrFrameType;

    typedef struct
    {
        U32                 Lng;
        U32                 Adr;
        U8                  Buffer[cSADFixedBufferSize];
    } tSADFixedAdrFrameType;

    //----- DoubleAdrFrame type definition -----
    typedef struct
    {
        tSADTypeFlag            Type;
        U32                 Time;
        U32                 Lng;
        U32                 Adr1;
        U32                 Adr2;
    } tSADDoubleAdrFrameInfo;

    typedef struct
    {
        tSADDoubleAdrFrameInfo  Info;
        const U8*           Buffer;
    } tSADDoubleAdrFrameType;

    typedef struct
    {
        U32                 Lng;
        U32                 Adr1;
        U32                 Adr2;
        U8                  Buffer[cSADFixedBufferSize];
    } tSADFixedDoubleAdrFrameType;

    //----- Graph type definition -----
    typedef struct
    {
        tSADTypeFlag            Type;
        U32                 Time;
        U32                 Adr;
        U8                  DataSize;
    } tSADGraphInfo;

    typedef struct
    {
        tSADGraphInfo           Info;
        U32                 Data;
    } tSADGraphType;

    //----- Supplier info -----
    typedef struct
    {
        char ProcessName[cSADMaxNameLength];
        char TraceName[cSADMaxNameLength];
        tSADTraceType Type;
    } tSADSupplierInfo;

    //-----------------------------------------------------------------------------
    //          DYNAMIC LOADING FUNCTION
    //-----------------------------------------------------------------------------
#ifdef DYNAMIC_SCANALLDLL_DRIVER
    //-----------------------------------------------------------------------------
    //          API type for all
    //-----------------------------------------------------------------------------
    typedef U16     (_SADFUNC_ *SADGETDLLVERSION)();
    typedef U8      (_SADFUNC_ *SADENUMSUPPLIERS)(tSADSupplierInfo SupplierInfoList[]);

    //-----------------------------------------------------------------------------
    //          API type for Supplier function
    //-----------------------------------------------------------------------------
    //----- Universal function -----
    typedef tSADHandle  (_SADFUNC_ *SADCONNECTSUPPLIER)(tSADTraceType Type,const char* Name);
    typedef tSADStatus  (_SADFUNC_ *SADDECONNECTSUPPLIER)(tSADHandle Handle);
    typedef tSADStatus  (_SADFUNC_ *SADSETCALLBACKCDE)(tSADHandle Handle,tSADCallBackCde CallBackCde, void* CallBackCdeParam);

    //----- Specific functions -----
    //----- Text type -----
    typedef tSADStatus  (_SADFUNC_ *SADTEXTTRACE)(tSADHandle Handle,tSADTextType* pText);

    //----- Frame type -----
    typedef tSADStatus  (_SADFUNC_ *SADFRAMETRACE)(tSADHandle Handle,tSADFrameType* pFrame);

    //----- AdrFrame type -----
    typedef tSADStatus  (_SADFUNC_ *SADADRFRAMETRACE)(tSADHandle Handle,tSADAdrFrameType* pAdrFrame);

    //----- DoubleAdrFrame type -----
    typedef tSADStatus  (_SADFUNC_ *SADDOUBLEADRFRAMETRACE)(tSADHandle Handle,tSADDoubleAdrFrameType* pDoubleAdrFrame);

    //----- Graph type -----
    typedef tSADStatus  (_SADFUNC_ *SADGRAPHTRACE)(tSADHandle Handle,tSADGraphType* pGraph);

    //-----------------------------------------------------------------------------
    //          API for customer function
    //-----------------------------------------------------------------------------
    //----- Universal function -----
    typedef tSADHandle  (_SADFUNC_ *SADCONNECTCUSTOMER)(CWnd* pWndParent,UINT Id,const char* ProcessName,const char* TraceName);
    typedef tSADStatus  (_SADFUNC_ *SADDECONNECTCUSTOMER)(tSADHandle Handle);
    typedef tSADStatus  (_SADFUNC_ *SADCOMMANDCUSTOMER)(tSADHandle Handle,tSADCommandType Cde,void* Param);
    typedef tSADStatus  (_SADFUNC_ *SADGETCUSTOMERSTATUS)(tSADHandle Handle,tSADCustomerStatus* pStatus);

    typedef tSADStatus  (_SADFUNC_ *SADCONNECTVIEWER)(CWnd* pWndParent,UINT Id,UINT MessageCde);
    typedef tSADStatus  (_SADFUNC_ *SADDECONNECTVIEWER)();
    typedef tSADStatus  (_SADFUNC_ *SADCOMMANDTRACEVIEW)(tSADCommandType Cde);

    //-----------------------------------------------------------------------------
    //          STATIC LOADING FUNCTION
    //-----------------------------------------------------------------------------
#else
//-----------------------------------------------------------------------------
    //          API type for all
    //-----------------------------------------------------------------------------
    SCANALLDLL_API U16 SADGetDllVersion();
    SCANALLDLL_API U8  SADEnumSuppliers(tSADSupplierInfo SupplierInfoList[]);

    //-----------------------------------------------------------------------------
    //          API for Supplier function
    //-----------------------------------------------------------------------------
    //----- Universal function -----
    SCANALLDLL_API tSADHandle SADConnectSupplier(tSADTraceType Type,const char* Name);
    SCANALLDLL_API tSADStatus SADDeconnectSupplier(tSADHandle Handle);
    SCANALLDLL_API tSADStatus SADSetCallBackCde(tSADHandle Handle,tSADCallBackCde CallBackCde, void* CallBackCdeParam);

    //----- Specific functions -----
    //----- Text type -----
    SCANALLDLL_API tSADStatus SADTextTrace(tSADHandle Handle,tSADTextType* pText);

    //----- Frame type -----
    SCANALLDLL_API tSADStatus SADFrameTrace(tSADHandle Handle,tSADFrameType* pFrame);

    //----- AdrFrame type -----
    SCANALLDLL_API tSADStatus SADAdrFrameTrace(tSADHandle Handle,tSADAdrFrameType* pAdrFrame);

    //----- DoubleAdrFrame type -----
    SCANALLDLL_API tSADStatus SADDoubleAdrFrameTrace(tSADHandle Handle,tSADDoubleAdrFrameType* pDoubleAdrFrame);

    //----- Graph type -----
    SCANALLDLL_API tSADStatus SADGraphTrace(tSADHandle Handle,tSADGraphType* pGraph);

    //-----------------------------------------------------------------------------
    //          API type for customer function
    //-----------------------------------------------------------------------------
    //----- Universal function -----
    SCANALLDLL_API tSADHandle SADConnectCustomer(CWnd* pWndParent,UINT Id,const char* ProcessName,const char* TraceName);
    SCANALLDLL_API tSADStatus SADDeconnectCustomer(tSADHandle Handle);
    SCANALLDLL_API tSADStatus SADCommandCustomer(tSADHandle Handle,tSADCommandType Cde,void* Param);
    SCANALLDLL_API tSADStatus SADGetCustomerStatus(tSADHandle Handle,tSADCustomerStatus* pStatus);

    SCANALLDLL_API tSADStatus SADConnectTraceView(CWnd* pWndParent,UINT Id,UINT MessageCde);
    SCANALLDLL_API tSADStatus SADDeconnectTraceView();
    SCANALLDLL_API tSADStatus SADCommandTraceView(tSADCommandType Cde,void* Param);

#endif
    //-----------------------------------------------------------------------------
    //          END OF LOADING FUNCTION
    //-----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif   // _cplusplus

// Default alignment
#pragma pack( pop )

#endif // SCANALLDLL_H
