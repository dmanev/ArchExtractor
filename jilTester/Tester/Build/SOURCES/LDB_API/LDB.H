/*============================================================================
  Project ......................... STANDARD
  Component ....................... ldb.h
  -------------------------------------------------------------------------
  Copyright ... This software is JCI property. Duplication or
                disclosure is prohibited without JCI written permission
  ------------------------------------------------------------------------- 
    
  - This file should only contain data useful to the programmer to use
    this component
  - Component exported macros, constants and types are defined in this file
  - Component exported variables and functions are declared in this file 
    with the "extern" key word
  
  -------------------------------------------------------------------------
  ldb.h file review :
  

  ==========================================================================*/

#ifndef I_LDB_H
#define I_LDB_H (1)

/*-------------------------------------------------------------------------
  Included files to resolve specific definitions in this file

  #include <system_file_name.h>
  #include "project_file_name.h"
  -------------------------------------------------------------------------*/
#include "DefTypes.h"
#include "ldbtypes.h"

/*-------------------------------------------------------------------------
  Constant data

  #define cCMPConstantName   ((tType) ConstantValue)
  -------------------------------------------------------------------------*/

//Status value common for all channel
#define cLDBCorrect        ((tStatus)0x00U)    // Control correctly done
#define cLDBError          ((tStatus)0x01U)    // Unknown control or not realized

/*-------------------------------------------------------------------------
  Exported Macro

  #define mCMPMacroName   (MacroDefinition)
  -------------------------------------------------------------------------*/ 

#define mLDBSimulateProcessingTime(x) mLDBPARAM_SIMULATE_PROCESSING_TIME_MACRO((x))
#define mLDBTrace( Text )            mLDBPARAM_TRACE_MACRO( (Text) )

#ifdef LDB_MACRO_SERVICES

#define LDBSendWithAddr( Channel, Ad, Msg ) \
                              mLDBSendWithAddr ## Channel( Ad, Msg )
#define LDBSendWithoutAddr( Channel, Msg ) \
                              mLDBSendWithoutAddr ## Channel( Msg )
#define LDBPrepareSendWithAddr( Channel, Ad, Msg ) \
                              mLDBPrepareSendWithAddr ## Channel( Ad, Msg )
#define LDBPrepareSendWithoutAddr( Channel, Msg ) \
                              mLDBPrepareSendWithoutAddr ## Channel( Msg )
#define LDBReceiveWithAddr( Channel, Ad, Msg ) \
                              mLDBReceiveWithAddr ## Channel( Ad, Msg )
#define LDBReceiveWithoutAddr( Channel, Msg ) \
                              mLDBReceiveWithoutAddr ## Channel( Msg )
#define LDBEnableCallBack( Channel, CallBackEnabled) \
                              mLDBEnableCallBack ## Channel( CallBackEnabled )
#define LDBControl( Channel, Ctrl) \
                              mLDBControl ## Channel( Ctrl )
#endif

/*-------------------------------------------------------------------------
  Exported type

  struct  sCMPStructureName { ... };
  union   uCMPUnionName { ... };
  enum    eCMPEnumerationName { ... };
  typedef Expression tCMPTypeName;

  -------------------------------------------------------------------------*/

typedef LDBPARAM_CHANNEL_TYPE  tChannel;
typedef LDBPARAM_ADDRESS_TYPE  tAddress;
typedef LDBPARAM_CTRL_TYPE     tCtrl;
typedef LDBPARAM_STATUS_TYPE   tStatus;
typedef LDBPARAM_DELAY_TYPE    tDelay;
typedef LDBPARAM_TIMERREF_TYPE tTimerRef;

typedef struct
{
    U8*              pBuffer;         // Message buffer
    LDBPARAM_TYPE_LNGMSG Lng;            // Message lenght
} tMsg;

//------------------------- CallBacks types  ---------------------------

typedef void  (*tpCallBackCtrl       )( tCtrl                   );
typedef void  (*tpCallBackStatusCtrl )( tCtrl,    tStatus       );
typedef void  (*tpCallBackStatusAddr  )( tAddress, tStatus       );
typedef void  (*tpCallBackRxWithAddr )( tAddress, tStatus, tMsg*);

//---------------- Spontaneous Rx & Tx --------------
typedef struct
{
    tpCallBackRxWithAddr  pCallBackRx;
    tAddress              Address;
} tRxSpontWithAddr;

typedef struct
{
    tpCallBackStatusAddr   pCallBackStatus;
    tAddress              Address;
} tTxSpontWithAddr;

typedef tAddress    tTxSpontWithIdx;
typedef tAddress    tRxSpontWithIdx;

typedef void(*tpFunct)(void);

/*-------------------------------------------------------------------------
  Exported data

  extern  tType   CMPVariableName;
  extern  tType*  pCMPVariableName; 
  -------------------------------------------------------------------------*/ 

/*-------------------------------------------------------------------------
  Constant exported data

  extern const tType  CMPVariableName;
  -------------------------------------------------------------------------*/ 

/*-------------------------------------------------------------------------
  Exported functions

  extern tReturnType CMPFunctionName(tTypeArgument1 ArgumentName1, ... );
  -------------------------------------------------------------------------*/ 

#ifndef TEMPO_TYPE

extern tDelay LDBStopTimer         ( tTimerRef );
extern void   LDBStartTimer        ( tTimerRef, tpFunct, tDelay, BOOL );

#else
	#if TEMPO_TYPE == 1
		#define LDBStartTimer( Ref, pFonc, Delay, Bool) \
                            mLIBassert( Delay == 1 );      \
                            mLIBassert( Ref == 0 );        \
                            LDBTimStartTimer()

		#define LDBStopTimer( Ref)                      \
                            mLIBassert( Ref == 0 );        \
                            LDBTimStopTimer()

extern void LDBTimStartTimer(void);
extern tDelay LDBTimStopTimer(void);
	#endif

	#if TEMPO_TYPE == 2
		#define LDBStartTimer( Ref, pFonc, Delay, Bool) LDBTimStartTimer(Ref,Delay)
		#define LDBStopTimer( Ref) LDBTimStopTimer(Ref)

extern void LDBTimStartTimer(tTimerRef,tDelay);
extern tDelay LDBTimStopTimer(tTimerRef);
	#endif		

	#if TEMPO_TYPE == 3
		#define LDBStartTimer( Ref, pFonc, Delay, Bool) LDBTimStartTimer(Ref, Delay, Bool)
		#define LDBStopTimer( Ref) LDBTimStopTimer(Ref)

extern void LDBTimStartTimer(tTimerRef, tDelay, BOOL);
extern tDelay LDBTimStopTimer(tTimerRef);
	#endif		
#endif

// Performance Counter high resolution timer
#ifdef TOS_PERF_CNT_ENABLE
extern U32 LDBTimPerfCntGetTime(void);
#endif

// Watch dog refresh
extern void LDBRefreshWatchDog ( void );

extern void LDBReset           ( void );
extern void LDBInit            ( void );

extern void LDBEnterSleepMode  ( void );
extern void LDBLeaveSleepMode  ( void );
extern void LDBWaitForCallBack ( void );


#ifndef LDB_MACRO_SERVICES
extern void LDBSendWithAddr      (tChannel Channel, tAddress Ad, tMsg* Msg );
extern void LDBPrepareSendWithAddr(tChannel Channel, tAddress Ad, tMsg* Msg );
extern void LDBReceiveWithAddr    (tChannel Channel, tAddress Ad, tMsg* Msg );

extern void LDBSendWithoutAddr      (tChannel Channel, tMsg* Msg );
extern void LDBPrepareSendWithoutAddr(tChannel Channel, tMsg* Msg );
extern void LDBReceiveWithoutAddr    (tChannel Channel, tMsg* Msg );

extern void LDBControl       (tChannel Channel, tCtrl Ctrl);
extern void LDBEnableCallBack(tChannel Channel, BOOL CallBackEnabled );
#endif

/*--------------------------------------------------------------------------*/
/*-------  Definitions des canaux propres a cette implementation  ----------*/
/*--------------------------------------------------------------------------*/

#include "ldbparam.h"

/*-------------------------------------------------------------------------
  End of includes non re entry
  -------------------------------------------------------------------------*/
#endif   /* I_LDB_H */

