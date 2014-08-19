/*============================================================================
  Project ......................... STANDARD
  Component ....................... ldb_ioc
  -------------------------------------------------------------------------
  Copyright ... This software is JCI property. Duplication or
                disclosure is prohibited without JCI written permission
  ------------------------------------------------------------------------- 
    
  - This file should only contain data useful to the programmer to use
    this component
  - Component exported macros, constants and types are defined in this file
  - Component exported variables and functions are declared in this file 
    with the "extern" keyword
  
  -------------------------------------------------------------------------
  ldb_ioc.h file review :
  


  ==========================================================================*/

#ifndef I_LDB_IOC_H
#define I_LDB_IOC_H (1)

/*-------------------------------------------------------------------------
  Included files to resolve specific definitions in this file

  #include <system_file_name.h>
  #include "project_file_name.h"
  -------------------------------------------------------------------------*/

#include "deftypes.h"

#include "ldb_reg.h"
#include "ldb_iocp.h"
#include "ldb_Sup.h"

/*-------------------------------------------------------------------------
  Constant data

  #define cCMPConstantName   ((tType) ConstantValue)
  -------------------------------------------------------------------------*/

#define cLDBIocFallingEdge          FallingEdge
#define cLDBIocRisingEdge           RisingEdge
#define cLDBIocBothEdge             BothEdge

/*-------------------------------------------------------------------------
  Exported Macros

  #define mCMPMacroName   (MacroDefinition)
  -------------------------------------------------------------------------*/ 

/************************************************************************/
/*  General Macro                                                       */
/************************************************************************/

/**** services dedicate to timer ****/

/* Counters read */
/*-------------- */

/* Concatenation's macros */
#define mLDBIocReadCounter(TM)   mLDBIocReadCounter2(TM) 
#define mLDBIocReadCounter2(TM)  mLDBIocReadCounter_##TM()

/* Counter reading macros */
#define mLDBIocReadCounter_Timer00()   TM00
#define mLDBIocReadCounter_Timer01()   TM01
#define mLDBIocReadCounter_Timer2()    TM2
#define mLDBIocReadCounter_Timer50()   TM50
#define mLDBIocReadCounter_Timer51()   TM51
#define mLDBIocReadCounter_Timer52()   TM52
#define mLDBIocReadCounter_TimerH0()   NA
#define mLDBIocReadCounter_TimerH1()   NA
#define mLDBIocReadCounter_TimerWT()   NA

/* Timers Start */
/*------------- */

/* Concatenation's macros */
#define mLDBIocStartTimer(TM)    mLDBIocStartTimer2(TM)
#define mLDBIocStartTimer2(TM)   mLDBIocStartTimer_##TM()

/* Timers' start macros */
#define mLDBIocStartTimer_Timer00()   {mLDBRegWrite1BitInRegister(TMC00, 2, 1);\
                                       mLDBRegWrite1BitInRegister(TMC00, 3, 1);}
#define mLDBIocStartTimer_Timer01()   {mLDBRegWrite1BitInRegister(TMC01, 2, 1);\
                                       mLDBRegWrite1BitInRegister(TMC01, 3, 1);}

#define mLDBIocFreeRunningModeStartTimer(TM)    mLDBIocFreeRunningModeStartTimer2(TM)
#define mLDBIocFreeRunningModeStartTimer2(TM)   mLDBIocFreeRunningModeStartTimer_##TM()

#define mLDBIocFreeRunningModeStartTimer_Timer00()   \
{ \
    mLDBRegWrite1BitInRegister(TMC00, 2, 1); \
    mLDBRegWrite1BitInRegister(TMC00, 3, 0); \
}

#define mLDBIocFreeRunningModeStartTimer_Timer01()   \
{ \
    mLDBRegWrite1BitInRegister(TMC01, 2, 1); \
    mLDBRegWrite1BitInRegister(TMC01, 3, 0); \
}

#define mLDBIocStartTimer_Timer2()    (TMC2.2 = 1)
#define mLDBIocStartTimer_Timer50()   (TCE50 = 1)
#define mLDBIocStartTimer_Timer51()   (TMC51.7 = 1)
#define mLDBIocStartTimer_Timer52()   (TMC52.7 = 1)
#define mLDBIocStartTimer_TimerH0()   (mLDBRegWrite1BitInRegister(TMHMD0, 7, 1))
#define mLDBIocStartTimer_TimerH1()   (mLDBRegWrite1BitInRegister(TMHMD1, 7, 1))
#define mLDBIocStartTimer_TimerWT() \
    mLDBRegWrite1BitInRegister(WTM, 0, 1); \
    mLDBRegWrite1BitInRegister(WTM, 1, 1)                                      
#define mLDBIocStartTimer_TimerWTI()  mLDBRegWrite1BitInRegister(WTM, 0, 1)
                                       
/* Timers Stop */
/*------------ */
/* Concatenation's macros */
#define mLDBIocStopTimer(TM)    mLDBIocStopTimer2(TM)
#define mLDBIocStopTimer2(TM)   mLDBIocStopTimer_##TM()

/* Timers' stop macros */
#define mLDBIocStopTimer_Timer00()   {mLDBRegWrite1BitInRegister(TMC00, 2, 0);\
                                      mLDBRegWrite1BitInRegister(TMC00, 3, 0);}
#define mLDBIocStopTimer_Timer01()   {mLDBRegWrite1BitInRegister(TMC01, 2, 0);\
                                      mLDBRegWrite1BitInRegister(TMC01, 3, 0);}
#define mLDBIocStopTimer_Timer2()    (TMC2.2 = 0)
#define mLDBIocStopTimer_Timer50()   (TCE50 = 0)
#define mLDBIocStopTimer_Timer51()   (TMC51.7 = 0)
#define mLDBIocStopTimer_Timer52()   (TMC52.7 = 0)
#define mLDBIocStopTimer_TimerH0()   mLDBRegWrite1BitInRegister(TMHMD0, 7, 0)
#define mLDBIocStopTimer_TimerH1()   mLDBRegWrite1BitInRegister(TMHMD1, 7, 0)
#define mLDBIocStopTimer_TimerWT() \
    mLDBRegWrite1BitInRegister(WTM, 0, 0); \
    mLDBRegWrite1BitInRegister(WTM, 1, 0)
#define mLDBIocStopTimer_TimerWTI()  mLDBRegWrite1BitInRegister(WTM, 0, 0)

/* Test Timer State */
/*----------------- */

/* Concatenation's macros */
#define mLDBIocIsTimerStopped(TM)    mLDBIocIsTimerStopped2(TM)
#define mLDBIocIsTimerStopped2(TM)   mLDBIocIsTimerStopped_##TM()

/* Macros de demarrage des timers */
#define mLDBIocIsTimerStopped_Timer00()   ((mLDBRegReadBitRegister(TMC00,2) == 0)&&(mLDBRegReadBitRegister(TMC00,3) == 0))
#define mLDBIocIsTimerStopped_Timer01()   ((mLDBRegReadBitRegister(TMC01,2) == 0)&&(mLDBRegReadBitRegister(TMC01,3) == 0))
#define mLDBIocIsTimerStopped_Timer2()    (mLDBRegReadBitRegister(TMC2,2) == 0)
#define mLDBIocIsTimerStopped_Timer50()   (mLDBRegReadBitRegister(TCE50) == 0)
#define mLDBIocIsTimerStopped_Timer51()   (mLDBRegReadBitRegister(TMC51,7) == 0)
#define mLDBIocIsTimerStopped_Timer52()   (mLDBRegReadBitRegister(TMC52,7) == 0)
#define mLDBIocIsTimerStopped_TimerH0()   (mLDBRegReadBitRegister(TMHMD0,7) == 0)
#define mLDBIocIsTimerStopped_TimerH1()   (mLDBRegReadBitRegister(TMHMD1,7) == 0)

// If only Watch Timer operates
#define mLDBIocIsTimerStopped_TimerWT()   (mLDBRegReadBitRegister(WTM,1) == 0) 
#define mLDBIocIsTimerStopped_TimerWTI()    (mLDBRegReadBitRegister(WTM,0) == 0) 

// If Interval Timer is simultaneously operated, zero-second start can be achieved only for the watch timer byclearing WTM1 to 0, but
//  WTM0 is not cleared. Therefore, an error up to 2^9 x 1/fW  seconds occurs in the first overflow (INTWT) after zero-second start. 


/* Type of timer used */
/*------------------- */

/* Concatenation's macros */
#define mLDBIocGetType(TM)    mLDBIocGetType2(TM)
#define mLDBIocGetType2(TM)   mLDBIocGetType_##TM()

/* Timer size definitions */
#define mLDBIocGetType_Timer00()   (16)
#define mLDBIocGetType_Timer01()   (16)
#define mLDBIocGetType_Timer2()    (16)
#define mLDBIocGetType_Timer50()   (8)
#define mLDBIocGetType_Timer51()   (8)
#define mLDBIocGetType_Timer52()   (8)
#define mLDBIocGetType_Timer5()    (16)
#define mLDBIocGetType_TimerH0()   (8)
#define mLDBIocGetType_TimerH1()   (8)

/* Set Timer Counter Source */
/*------------------------- */

/* To be used only when an external clock is used */

/* Concatenation's macros */
#define mLDBIocSetCounterSource(TM,CounterSource,Type)   mLDBIocSetCounterSource2(TM,CounterSource,Type)
#define mLDBIocSetCounterSource2(TM,CounterSource,Type)  mLDBIocSetCounterSource_##TM(CounterSource,Type)

/* Timer 00 /01 configuration */
/*--------------------------- */

#define mLDBIocSetCounterSource_Timer00(CounterSource,Type)    mLDBIocSetCounterSource_Timer00_##CounterSource(Type)
#define mLDBIocSetCounterSource_Timer00_External(Type)      mLDBIocSetCounterSource_Timer00_External_##Type()
#define mLDBIocSetCounterSource_Timer01(CounterSource,Type)    mLDBIocSetCounterSource_Timer01_##CounterSource(Type)
#define mLDBIocSetCounterSource_Timer01_External(Type)      mLDBIocSetCounterSource_Timer01_External_##Type()

/* Source select */
#define mLDBIocSetCounterSource_Timer00_External_Rising(Type)  (CR000 = 0x01)
#define mLDBIocSetCounterSource_Timer00_External_Falling(Type) (CR000 = 0x00)

#define mLDBIocSetCounterSource_Timer01_External_Rising(Type)  (CR001 = 0x01)
#define mLDBIocSetCounterSource_Timer01_External_Falling(Type) (CR001 = 0x00)

   #define mLDBIocSetCounterSource_Timer50(CounterSource,Type)    mLDBIocSetCounterSource_Timer50_##CounterSource(Type)
      #define mLDBIocSetCounterSource_Timer50_External(Type)      mLDBIocSetCounterSource_Timer50_External_##Type()
   #define mLDBIocSetCounterSource_Timer51(CounterSource,Type)    mLDBIocSetCounterSource_Timer51_##CounterSource(Type)
      #define mLDBIocSetCounterSource_Timer51_External(Type)      mLDBIocSetCounterSource_Timer51_External_##Type()

/* Source select */
#define mLDBIocSetCounterSource_Timer50_External_Rising()      (TCL50 = 0x01)
#define mLDBIocSetCounterSource_Timer50_External_Falling()     (TCL50 = 0x00)
#define mLDBIocSetCounterSource_Timer50_Internal(Type)         (TCL50 = 0x02)

#define mLDBIocSetCounterSource_Timer51_External_Rising(Type)  (TCL50 = 0x01)
#define mLDBIocSetCounterSource_Timer51_External_Falling(Type) (TCL50 = 0x00)
#define mLDBIocSetCounterSource_Timer51_Internal(Type)         (TCL50 = 0x02)

/* Timer 50 /51 configuration */
/*--------------------------- */

/* Concatenation's macros */
#define mLDBIocConfigure_Timer5(Type)           mLDBIocConfigure_Timer52(Type)
#define mLDBIocConfigure_Timer52(Type)          mLDBIocConfigure_Timer5_##Type()

/* TM5 Configuration */
#define mLDBIocConfigure_Timer5_16Bit           (TMC51.4 = 1)
#define mLDBIocConfigure_Timer5_8Bit            (TMC51.4 = 0)

/* Set timer counter source */
/* Seems to be unused on NEC */

/* Clock selection */
/*---------------- */

/* Concatenation's macros */
#define mLDBIocSelectClock(TM, Divider)         mLDBIocSelectClock2(TM, Divider)
#define mLDBIocSelectClock2(TM, Divider)        mLDBIocSelectClock_##TM(Divider)

#define mLDBIocSelectClock_Timer00(Divider)     mLDBIocSelectClock_Timer00_##Divider()
#define mLDBIocSelectClock_Timer01(Divider)     mLDBIocSelectClock_Timer01_##Divider()
#define mLDBIocSelectClock_Timer50(Divider)     mLDBIocSelectClock_Timer50_##Divider()
#define mLDBIocSelectClock_Timer51(Divider)     mLDBIocSelectClock_Timer51_##Divider()
#define mLDBIocSelectClock_Timer52(Divider)     mLDBIocSelectClock_Timer52_##Divider()
#define mLDBIocSelectClock_Timer5(Divider)      mLDBIocSelectClock_Timer5_##Divider()
#define mLDBIocSelectClock_TimerH0(Divider)     mLDBIocSelectClock_TimerH0_##Divider()
#define mLDBIocSelectClock_TimerH1(Divider)     mLDBIocSelectClock_TimerH1_##Divider()
#define mLDBIocSelectClock_TimerWT(Divider)     mLDBIocSelectClock_TimerWT_##Divider()
#define mLDBIocSelectClock_TimerWTI(Divider)    mLDBIocSelectClock_TimerWTI_##Divider()


/* Set clock */
/*---------- */
/* Timer 00 */
/* frequency = fprs: prohibited if operating on internal frh */
#define mLDBIocSelectClock_Timer00_0() \
{\
    mLDBRegWrite1BitInRegister(PRM00, 1, 0); \
    mLDBRegWrite1BitInRegister(PRM00, 0, 0); \
}
/* frequency = fprs/2^2 */
#define mLDBIocSelectClock_Timer00_2() \
{\
    mLDBRegWrite1BitInRegister(PRM00, 1, 0); \
    mLDBRegWrite1BitInRegister(PRM00, 0, 1); \
}
/* frequency = fprs/2^8 */
#define mLDBIocSelectClock_Timer00_8() \
{\
    mLDBRegWrite1BitInRegister(PRM00, 1, 1); \
    mLDBRegWrite1BitInRegister(PRM00, 0, 0); \
}

/* Edge detection on TI000/P00 input */
#define mLDBIocSelectClock_Timer00_InputCapture() \
{\
    mLDBRegWrite1BitInRegister(PRM00, 1, 1); \
    mLDBRegWrite1BitInRegister(PRM00, 0, 1); \
    mLDBRegWrite1BitInRegister(PRM00, 4, 0); \
    mLDBRegWrite1BitInRegister(PRM00, 5, 0); \
}

/* Timer 01 */
/* frequency = fprs: prohibited if operating on internal frh */
#define mLDBIocSelectClock_Timer01_0() \
{\
    mLDBRegWrite1BitInRegister(PRM01, 1, 0); \
    mLDBRegWrite1BitInRegister(PRM01, 0, 0); \
}
/* frequency = fprs/2^4 */
#define mLDBIocSelectClock_Timer01_4() \
{\
    mLDBRegWrite1BitInRegister(PRM01, 1, 0); \
    mLDBRegWrite1BitInRegister(PRM01, 0, 1); \
}
/* frequency = fprs/2^6 */
#define mLDBIocSelectClock_Timer01_6() \
{\
    mLDBRegWrite1BitInRegister(PRM01, 1, 1); \
    mLDBRegWrite1BitInRegister(PRM01, 0, 0); \
}
/* Edge detection on TI001/P05/SSI11 input */
#define mLDBIocSelectClock_Timer01_InputCapture() \
{\
    mLDBRegWrite1BitInRegister(PRM01, 1, 1); \
    mLDBRegWrite1BitInRegister(PRM01, 0, 1); \
}

/* Timer 50 */
#define mLDBIocSelectClock_Timer50_3()          (TCL50 = 0x02) /* frequency = fx/2^3 */
#define mLDBIocSelectClock_Timer50_5()          (TCL50 = 0x03) /* frequency = fx/2^5 */
#define mLDBIocSelectClock_Timer50_7()          (TCL50 = 0x04) /* frequency = fx/2^7 */
#define mLDBIocSelectClock_Timer50_8()          (TCL50 = 0x05) /* frequency = fx/2^8 */
#define mLDBIocSelectClock_Timer50_9()          (TCL50 = 0x06) /* frequency = fx/2^9 */
#define mLDBIocSelectClock_Timer50_11()         (TCL50 = 0x07) /* frequency = fx/2^11 */
/* Timer 51 */
#define mLDBIocSelectClock_Timer51_4()          (TCL51 = 0x02) /* frequency = fx/2^4 */
#define mLDBIocSelectClock_Timer51_6()          (TCL51 = 0x03) /* frequency = fx/2^6 */
#define mLDBIocSelectClock_Timer51_7()          (TCL51 = 0x04) /* frequency = fx/2^7 */
#define mLDBIocSelectClock_Timer51_8()          (TCL51 = 0x05) /* frequency = fx/2^8 */
#define mLDBIocSelectClock_Timer51_10()         (TCL51 = 0x06) /* frequency = fx/2^10 */
#define mLDBIocSelectClock_Timer51_12()         (TCL51 = 0x07) /* frequency = fx/2^12 */
/* Timer 52 */
#define mLDBIocSelectClock_Timer52_3()          (TCL52 = 0x02) /* frequency = fx/2^3 */
#define mLDBIocSelectClock_Timer52_4()          (TCL52 = 0x03) /* frequency = fx/2^4 */
#define mLDBIocSelectClock_Timer52_5()          (TCL52 = 0x04) /* frequency = fx/2^5 */
#define mLDBIocSelectClock_Timer52_7()          (TCL52 = 0x05) /* frequency = fx/2^7 */
#define mLDBIocSelectClock_Timer52_9()          (TCL52 = 0x06) /* frequency = fx/2^9 */
#define mLDBIocSelectClock_Timer52_11()         (TCL52 = 0x07) /* frequency = fx/2^11 */
/* Timer 5 (= Timer 50 + Timer 51) */
#define mLDBIocSelectClock_Timer5_3()           (TCL50 = 0x02) /* frequency = fx/2^3 */
#define mLDBIocSelectClock_Timer5_5()           (TCL50 = 0x03) /* frequency = fx/2^5 */
#define mLDBIocSelectClock_Timer5_7()           (TCL50 = 0x04) /* frequency = fx/2^7 */
#define mLDBIocSelectClock_Timer5_8()           (TCL50 = 0x05) /* frequency = fx/2^8 */
#define mLDBIocSelectClock_Timer5_9()           (TCL50 = 0x06) /* frequency = fx/2^9 */
#define mLDBIocSelectClock_Timer5_11()          (TCL50 = 0x07) /* frequency = fx/2^11 */


/* Timer 2 */
/* frequency = fx/2^3 */
#define mLDBIocSelectClock_Timer2_3() \
{ \
   PRM2.0 = 0; \
   PRM2.1 = 0; \
}
/* frequency = fx/2^4 */
#define mLDBIocSelectClock_Timer2_4() \
{ \
   PRM2.0 = 1; \
   PRM2.1 = 0; \
}
/* frequency = fx/2^5 */
#define mLDBIocSelectClock_Timer2_5() \
{ \
   PRM2.0 = 0; \
   PRM2.1 = 1; \
}
/* frequency = fx/2^6 */
#define mLDBIocSelectClock_Timer2_6() \
{ \
   PRM2.0 = 1; \
   PRM2.1 = 1; \
}

/* Timer H0 */
/* frequency = fprs: prohibited if operating on internal frh */
#define mLDBIocSelectClock_TimerH0_0() \
{\
    mLDBRegWrite1BitInRegister(TMHMD0, 6, 0); \
    mLDBRegWrite1BitInRegister(TMHMD0, 5, 0); \
    mLDBRegWrite1BitInRegister(TMHMD0, 4, 0); \
}
/* frequency = fprs/2 */
#define mLDBIocSelectClock_TimerH0_1() \
{\
    mLDBRegWrite1BitInRegister(TMHMD0, 6, 0); \
    mLDBRegWrite1BitInRegister(TMHMD0, 5, 0); \
    mLDBRegWrite1BitInRegister(TMHMD0, 4, 1); \
}
/* frequency = fprs/2^2 */
#define mLDBIocSelectClock_TimerH0_2() \
{\
    mLDBRegWrite1BitInRegister(TMHMD0, 6, 0); \
    mLDBRegWrite1BitInRegister(TMHMD0, 5, 1); \
    mLDBRegWrite1BitInRegister(TMHMD0, 4, 0); \
}
/* frequency = fprs/2^6 */
#define mLDBIocSelectClock_TimerH0_6() \
{\
    mLDBRegWrite1BitInRegister(TMHMD0, 6, 0); \
    mLDBRegWrite1BitInRegister(TMHMD0, 5, 1); \
    mLDBRegWrite1BitInRegister(TMHMD0, 4, 1); \
}
/* frequency = fprs/2^10 */
#define mLDBIocSelectClock_TimerH0_10() \
{\
    mLDBRegWrite1BitInRegister(TMHMD0, 6, 1); \
    mLDBRegWrite1BitInRegister(TMHMD0, 5, 0); \
    mLDBRegWrite1BitInRegister(TMHMD0, 4, 0); \
}


/* Timer H1 */
/* frequency = fprs: prohibited if operating on internal frh */
#define mLDBIocSelectClock_TimerH1_0() \
{\
    mLDBRegWrite1BitInRegister(TMHMD1, 6, 0); \
    mLDBRegWrite1BitInRegister(TMHMD1, 5, 0); \
    mLDBRegWrite1BitInRegister(TMHMD1, 4, 0); \
}
/* frequency = fprs/2 */
#define mLDBIocSelectClock_TimerH1_1() \
{\
    mLDBRegWrite1BitInRegister(TMHMD1, 6, 0); \
    mLDBRegWrite1BitInRegister(TMHMD1, 5, 0); \
    mLDBRegWrite1BitInRegister(TMHMD1, 4, 1); \
}
/* frequency = fprs/2^2 */
#define mLDBIocSelectClock_TimerH1_4() \
{\
    mLDBRegWrite1BitInRegister(TMHMD1, 6, 0); \
    mLDBRegWrite1BitInRegister(TMHMD1, 5, 1); \
    mLDBRegWrite1BitInRegister(TMHMD1, 4, 0); \
}
/* frequency = fprs/2^6 */
#define mLDBIocSelectClock_TimerH1_6() \
{\
    mLDBRegWrite1BitInRegister(TMHMD1, 6, 0); \
    mLDBRegWrite1BitInRegister(TMHMD1, 5, 1); \
    mLDBRegWrite1BitInRegister(TMHMD1, 4, 1); \
}
/* frequency = fprs/2^10 */
#define mLDBIocSelectClock_TimerH1_12() \
{\
    mLDBRegWrite1BitInRegister(TMHMD1, 6, 1); \
    mLDBRegWrite1BitInRegister(TMHMD1, 5, 0); \
    mLDBRegWrite1BitInRegister(TMHMD1, 4, 0); \
}
/* frequency = Frl/2^7 */
#define mLDBIocSelectClock_TimerH1_FRL_7() \
{\
    mLDBRegWrite1BitInRegister(TMHMD1, 6, 1); \
    mLDBRegWrite1BitInRegister(TMHMD1, 5, 0); \
    mLDBRegWrite1BitInRegister(TMHMD1, 4, 1); \
}
/* frequency = Frl/2^9 */
#define mLDBIocSelectClock_TimerH1_FRL_9() \
{\
    mLDBRegWrite1BitInRegister(TMHMD1, 6, 1); \
    mLDBRegWrite1BitInRegister(TMHMD1, 5, 1); \
    mLDBRegWrite1BitInRegister(TMHMD1, 4, 0); \
}
/* frequency = Frl */
#define mLDBIocSelectClock_TimerH1_FRL() \
{\
    mLDBRegWrite1BitInRegister(TMHMD1, 6, 1); \
    mLDBRegWrite1BitInRegister(TMHMD1, 5, 1); \
    mLDBRegWrite1BitInRegister(TMHMD1, 4, 1); \
}


/* Timer WT */
/* frequency = fprs: prohibited if operating on internal frh */

/* frequency = fprs/2^4 */
#define mLDBIocSelectClock_TimerWT_4() \
{\
    mLDBRegWrite1BitInRegister(WTM, 2, 1); \
    mLDBRegWrite1BitInRegister(WTM, 3, 1); \
}
/* frequency = fprs/2^5 */
#define mLDBIocSelectClock_TimerWT_5() \
{\
    mLDBRegWrite1BitInRegister(WTM, 2, 0); \
    mLDBRegWrite1BitInRegister(WTM, 3, 1); \
}
/* frequency = fprs/2^13 */
#define mLDBIocSelectClock_TimerWT_13() \
{\
    mLDBRegWrite1BitInRegister(WTM, 2, 1); \
    mLDBRegWrite1BitInRegister(WTM, 3, 0); \
}
/* frequency = fprs/2^4 */
#define mLDBIocSelectClock_TimerWT_14() \
{\
    mLDBRegWrite1BitInRegister(WTM, 2, 0); \
    mLDBRegWrite1BitInRegister(WTM, 3, 0); \
}

/* Timer WTI */
/* frequency = fprs: prohibited if operating on internal frh */

/* frequency = fprs/2^4 */
#define mLDBIocSelectClock_TimerWTI_4() \
{\
    mLDBRegWrite1BitInRegister(WTM, 4, 0); \
    mLDBRegWrite1BitInRegister(WTM, 5, 0); \
	mLDBRegWrite1BitInRegister(WTM, 6, 0); \
}
/* frequency = fprs/2^5 */
#define mLDBIocSelectClock_TimerWTI_5() \
{\
    mLDBRegWrite1BitInRegister(WTM, 4, 1); \
    mLDBRegWrite1BitInRegister(WTM, 5, 0); \
	mLDBRegWrite1BitInRegister(WTM, 6, 0); \
}
/* frequency = fprs/2^6 */
#define mLDBIocSelectClock_TimerWTI_6() \
{\
    mLDBRegWrite1BitInRegister(WTM, 4, 0); \
    mLDBRegWrite1BitInRegister(WTM, 5, 1); \
	mLDBRegWrite1BitInRegister(WTM, 6, 0); \
}
/* frequency = fprs/2^7 */
#define mLDBIocSelectClock_TimerWTI_7() \
{\
    mLDBRegWrite1BitInRegister(WTM, 4, 1); \
    mLDBRegWrite1BitInRegister(WTM, 5, 1); \
	mLDBRegWrite1BitInRegister(WTM, 6, 0); \
}
/* frequency = fprs/2^8 */
#define mLDBIocSelectClock_TimerWTI_8() \
{\
    mLDBRegWrite1BitInRegister(WTM, 4, 0); \
    mLDBRegWrite1BitInRegister(WTM, 5, 0); \
	mLDBRegWrite1BitInRegister(WTM, 6, 1); \
}
/* frequency = fprs/2^9 */
#define mLDBIocSelectClock_TimerWTI_9() \
{\
    mLDBRegWrite1BitInRegister(WTM, 4, 1); \
    mLDBRegWrite1BitInRegister(WTM, 5, 0); \
	mLDBRegWrite1BitInRegister(WTM, 6, 1); \
}
/* frequency = fprs/2^10 */
#define mLDBIocSelectClock_TimerWTI_10() \
{\
    mLDBRegWrite1BitInRegister(WTM, 4, 0); \
    mLDBRegWrite1BitInRegister(WTM, 5, 1); \
	mLDBRegWrite1BitInRegister(WTM, 6, 1); \
}
/* frequency = fprs/2^11 */
#define mLDBIocSelectClock_TimerWTI_11() \
{\
    mLDBRegWrite1BitInRegister(WTM, 4, 1); \
    mLDBRegWrite1BitInRegister(WTM, 5, 1); \
	mLDBRegWrite1BitInRegister(WTM, 6, 1); \
}


/* Write trigger */
/*-------------- */

/* Concatenation's macros */
#define mLDBIocWriteTrigger(TG, Value)       mLDBIocWriteTrigger2(TG, Value)
#define mLDBIocWriteTrigger2(TG, Value)      mLDBIocWriteTrigger_##TG(Value)

/* Write trigger services */
#define mLDBIocWriteTrigger_Trigger00_0(Value)    (CR000 = Value)
#define mLDBIocWriteTrigger_Trigger00_1(Value)    (CR010 = Value)
#define mLDBIocWriteTrigger_Trigger01_0(Value)    (CR001 = Value)
#define mLDBIocWriteTrigger_Trigger01_1(Value)    (CR011 = Value)
#define mLDBIocWriteTrigger_Trigger20(Value)      (CR20 = Value)
#define mLDBIocWriteTrigger_Trigger21(Value)      (CR21 = Value)
#define mLDBIocWriteTrigger_Trigger22(Value)      (CR22 = Value)
#define mLDBIocWriteTrigger_Trigger50(Value)      (CR50 = Value)
#define mLDBIocWriteTrigger_Trigger51(Value)      (CR51 = Value)
#define mLDBIocWriteTrigger_Trigger52(Value)      (CR52 = Value)
#define mLDBIocWriteTrigger_Trigger5(Value) \
{ \
   CR50 = (U8)(Value>>8); \
   CR51 = (U8)(Value); \
}
#define mLDBIocWriteTrigger_TriggerH0(Value)        (CMP00 = Value)
#define mLDBIocWriteTrigger_TriggerH1(Value)        (CMP01 = Value)


/* Read trigger */
/*------------- */

/* Concatenation's macros */
#define mLDBIocReadTrigger(TG)       mLDBIocReadTrigger2(TG)
#define mLDBIocReadTrigger2(TG)      mLDBIocReadTrigger_##TG()

/* Read trigger services */
#define mLDBIocReadTrigger_Trigger00_0()    (CR000)
#define mLDBIocReadTrigger_Trigger00_1()    (CR010)
#define mLDBIocReadTrigger_Trigger01_0()    (CR001)
#define mLDBIocReadTrigger_Trigger01_1()    (CR011)
#define mLDBIocReadTrigger_Trigger20()      (CR20)
#define mLDBIocReadTrigger_Trigger21()      (CR21)
#define mLDBIocReadTrigger_Trigger22()      (CR22)
#define mLDBIocReadTrigger_Trigger50()      (CR50)
#define mLDBIocReadTrigger_Trigger51()      (CR51)
#define mLDBIocReadTrigger_Trigger52()      (CR52)
#define mLDBIocReadTrigger_Trigger5()       (((U16)CR51)<<8 + CR50)
#define mLDBIocReadTrigger_TriggerH0()           (CMP00)
#define mLDBIocReadTrigger_TriggerH1()           (CMP01)

/*---------------------- */
/* Timer Output config   */
/*---------------------- */
#define mLDBIocOutputEnable(Timer)      mLDBIocOutputEnable2(Timer)
#define mLDBIocOutputEnable2(Timer)     mLDBIocOutputEnable_##Timer()

#define mLDBIocOutputEnable_Timer00()    {mLDBRegWrite8BitRegister(TOC00, 0x12);\
                                          mLDBRegWrite1BitInRegister(TOC00, 0, 1);} 

#define mLDBIocOutputEnable_Timer01()    {mLDBRegWrite8BitRegister(TOC01, 0x12);\
                                          mLDBRegWrite1BitInRegister(TOC01, 0, 1);}

#define mLDBIocOutputDisable(Timer)      mLDBIocOutputDisable2(Timer)
#define mLDBIocOutputDisable2(Timer)     mLDBIocOutputDisable_##Timer()

#define mLDBIocOutputDisable_Timer00()    mLDBRegWrite8BitRegister(TOC00, 0)
#define mLDBIocOutputDisable_Timer01()    mLDBRegWrite8BitRegister(TOC01, 0)

#define mLDBIocOutputConfig(Timer, Option)      mLDBIocOutputConfig2(Timer, Option)
#define mLDBIocOutputConfig2(Timer, Option)     mLDBIocOutputConfig_##Timer(Option)

#define mLDBIocOutputConfig_Timer00(Option)     mLDBIocOutputConfig_Timer002(Option)
#define mLDBIocOutputConfig_Timer002(Option)    mLDBIocOutputConfig_Timer00_##Option()

#define mLDBIocOutputConfig_Timer00_LowToHigh() {mLDBRegWrite1BitInRegister(TMC00, 3, 0);\
                                                 mLDBRegWrite1BitInRegister(TMC00, 2, 1);} 

#define mLDBIocOutputConfig_Timer00_HighToLow() {mLDBRegWrite1BitInRegister(TMC00, 2, 0);\
                                                 mLDBRegWrite1BitInRegister(TMC00, 3, 1);} 

#define mLDBIocOutputConfig_Timer01(Option)     mLDBIocOutputConfig_Timer012(Option)
#define mLDBIocOutputConfig_Timer012(Option)    mLDBIocOutputConfig_Timer01_##Option()

#define mLDBIocOutputConfig_Timer01_LowToHigh() {mLDBRegWrite1BitInRegister(TMC01, 3, 0);\
                                                 mLDBRegWrite1BitInRegister(TMC01, 2, 1);} 

#define mLDBIocOutputConfig_Timer01_HighToLow() {mLDBRegWrite1BitInRegister(TMC01, 2, 0);\
                                                 mLDBRegWrite1BitInRegister(TMC01, 3, 1);} 

/*---------------------- */
/* Interval mode service */
/*---------------------- */

/* This mode is the only one of TM52 and cannot be set on timer TM2 */

/* Set to interval timer mode */
/*--------------------------- */

/* Concatenation's macros */
#define mLDBIocSetTimerModeIntervalTimer(TM)      mLDBIocSetTimerModeIntervalTimer2(TM)
#define mLDBIocSetTimerModeIntervalTimer2(TM)     mLDBIocSetTimerModeIntervalTimer_##TM()

/* Set to interval mode timer */
#define mLDBIocSetTimerModeIntervalTimer_Timer00()     {mLDBRegWrite1BitInRegister(TMC00, 2, 1);\
                                                        mLDBRegWrite1BitInRegister(TMC00, 3, 1);}
#define mLDBIocSetTimerModeIntervalTimer_Timer01()     {mLDBRegWrite1BitInRegister(TMC01, 2, 1);\
                                                        mLDBRegWrite1BitInRegister(TMC01, 3, 1);}
#define mLDBIocSetTimerModeIntervalTimer_Timer50()     (TMC50 = 0x00)
#define mLDBIocSetTimerModeIntervalTimer_Timer51()     (TMC51 = 0x00)
#define mLDBIocSetTimerModeIntervalTimer_Timer52()     TBD
#define mLDBIocSetTimerModeIntervalTimer_TimerH0() \
    mLDBRegWrite1BitInRegister(TMHMD0, 3, 0); \
    mLDBRegWrite1BitInRegister(TMHMD0, 2, 0)
#define mLDBIocSetTimerModeIntervalTimer_TimerH1() \
    mLDBRegWrite1BitInRegister(TMHMD1, 3, 0); \
    mLDBRegWrite1BitInRegister(TMHMD1, 2, 0)


/*------------------- */
/* Input capture mode */
/*------------------- */

#define mLDBIocSelectTimerMode(TM, Mode)      mLDBIocSelectTimerMode2(TM, Mode)
#define mLDBIocSelectTimerMode2(TM, Mode)     mLDBIocSelectTimerMode_##TM(Mode)

#define mLDBIocSelectTimerMode_Timer00(Mode) mLDBIocSelectTimerMode_Timer00_##Mode()
#define mLDBIocSelectTimerMode_Timer01(Mode) mLDBIocSelectTimerMode_Timer01_##Mode()

#define mLDBIocSelectTimerMode_Timer00_CompareAndCompare()\
{ \
    mLDBRegWrite1BitInRegister(CRC00, 0, 0); \
    mLDBRegWrite1BitInRegister(CRC00, 2, 0); \
}

#define mLDBIocSelectTimerMode_Timer00_CompareAndCapture()\
{ \
    mLDBRegWrite1BitInRegister(CRC00, 0, 0); \
    mLDBRegWrite1BitInRegister(CRC00, 1, 0); \
    mLDBRegWrite1BitInRegister(CRC00, 2, 1); \
}

#define mLDBIocSelectTimerMode_Timer00_CompareAndReverseCapture()\
{ \
    mLDBRegWrite1BitInRegister(CRC00, 0, 0); \
    mLDBRegWrite1BitInRegister(CRC00, 1, 1); \
    mLDBRegWrite1BitInRegister(CRC00, 2, 1); \
}

#define mLDBIocSelectTimerMode_Timer01_CompareAndCompare()\
{ \
    mLDBRegWrite1BitInRegister(CRC01, 0, 0); \
    mLDBRegWrite1BitInRegister(CRC01, 2, 0); \
}

#define mLDBIocSelectTimerMode_Timer01_CompareAndCapture()\
{ \
    mLDBRegWrite1BitInRegister(CRC01, 0, 0); \
    mLDBRegWrite1BitInRegister(CRC01, 1, 0); \
    mLDBRegWrite1BitInRegister(CRC01, 2, 1); \
}

#define mLDBIocSelectTimerMode_Timer01_CompareAndReverseCapture()\
{ \
    mLDBRegWrite1BitInRegister(CRC01, 0, 0); \
    mLDBRegWrite1BitInRegister(CRC01, 1, 1); \
    mLDBRegWrite1BitInRegister(CRC01, 2, 1); \
}

#define mLDBIocConfigureFreeRunningMode(TM, Option)      mLDBIocConfigureFreeRunningMode2(TM, Option)
#define mLDBIocConfigureFreeRunningMode2(TM, Option)     mLDBIocConfigureFreeRunningMode_##TM(Option)

#define mLDBIocConfigureFreeRunningMode_Timer00(Option) mLDBIocConfigureFreeRunningMode_Timer00_##Option()
#define mLDBIocConfigureFreeRunningMode_Timer01(Option) mLDBIocConfigureFreeRunningMode_Timer01_##Option()

#define mLDBIocConfigureFreeRunningMode_Timer00_DisableOutput() \
{ \
    mLDBRegWrite1BitInRegister(TOC00, 0, 0); \
}

#define mLDBIocConfigureFreeRunningMode_Timer01_DisableOutput() \
{ \
    mLDBRegWrite1BitInRegister(TOC01, 0, 0); \
}

/* This mode can only be used by TM2 */

/* Choose capture pulse */
/*--------------------- */

/* Concatenation's macros */
#define mLDBIocChooseCapturePulse(Divider)   mLDBIocChooseCapturePulse2(Divider)
#define mLDBIocChooseCapturePulse2(Divider)  mLDBIocChooseCapturePulse_##Divider()

/* Choose capture pulse */
#define mLDBIocChooseCapturePulse_1          (CRC2 = 0)
#define mLDBIocChooseCapturePulse_2          (CRC2 = 1)
#define mLDBIocChooseCapturePulse_4          (CRC2 = 2)
#define mLDBIocChooseCapturePulse_8          (CRC2 = 3)

#define mLDBIocSelectCaptureMode(TM, Mode)      mLDBIocSelectCaptureMode2(TM, Mode)
#define mLDBIocSelectCaptureMode2(TM, Mode)     mLDBIocSelectCaptureMode_##TM(Mode)

#define mLDBIocSelectCaptureMode_Timer00(Mode) mLDBIocSelectCaptureMode_Timer00_##Mode()

#define mLDBIocSelectCaptureMode_Timer00_Capture()\
{ \
    mLDBRegWrite1BitInRegister(CRC00, 0, 0); \
    mLDBRegWrite1BitInRegister(CRC00, 1, 1); \
    mLDBRegWrite1BitInRegister(CRC00, 2, 1); \
}
#define mLDBIocSelectCaptureMode_Timer00_DoubleInterval() \
{                                                         \
    mLDBRegWrite1BitInRegister(CRC00, 0, 0);              \
    mLDBRegWrite1BitInRegister(CRC00, 1, 0);              \
    mLDBRegWrite1BitInRegister(CRC00, 2, 0);              \
}


/* Valid edge selection */
/*--------------------- */

/* Concatenation's macros */
#define mLDBIocSetEdgeDetection(TM, Type)       mLDBIocSetEdgeDetection2(TM, Type)
#define mLDBIocSetEdgeDetection2(TM, Type)      mLDBIocSetEdgeDetection_##TM(Type)
#define mLDBIocSetEdgeDetection_Timer00(Type)      mLDBIocSetEdgeDetection_Timer00_##Type()
#define mLDBIocSetEdgeDetection_Timer01(Type)      mLDBIocSetEdgeDetection_Timer01_##Type()
#define mLDBIocSetEdgeDetection_CR21(Type)      mLDBIocSetEdgeDetection_CR21_##Type()
#define mLDBIocSetEdgeDetection_CR22(Type)      mLDBIocSetEdgeDetection_CR22_##Type()


/* Valid edge selection */
#define mLDBIocSetEdgeDetection_Timer00_FallingEdge() \
{ \
    mLDBRegWrite1BitInRegister(PRM00, 4, 0); \
    mLDBRegWrite1BitInRegister(PRM00, 5, 0); \
}
#define mLDBIocSetEdgeDetection_Timer00_RisingEdge() \
{ \
    mLDBRegWrite1BitInRegister(PRM00, 4, 1); \
    mLDBRegWrite1BitInRegister(PRM00, 5, 0); \
}
#define mLDBIocSetEdgeDetection_Timer00_BothEdge() \
{ \
    mLDBRegWrite1BitInRegister(PRM00, 4, 1); \
    mLDBRegWrite1BitInRegister(PRM00, 5, 1); \
}
#define mLDBIocSetEdgeDetection_Timer01_FallingEdge() \
{ \
    mLDBRegWrite1BitInRegister(PRM01, 4, 0); \
    mLDBRegWrite1BitInRegister(PRM01, 5, 0); \
}
#define mLDBIocSetEdgeDetection_Timer01_RisingEdge() \
{ \
    mLDBRegWrite1BitInRegister(PRM01, 4, 1); \
    mLDBRegWrite1BitInRegister(PRM01, 5, 0); \
}
#define mLDBIocSetEdgeDetection_Timer01_BothEdge() \
{ \
    mLDBRegWrite1BitInRegister(PRM01, 4, 1); \
    mLDBRegWrite1BitInRegister(PRM01, 5, 1); \
}

#define mLDBIocSetEdgeDetection_CR20_FallingEdge() \
{ \
   PRM2.2 = 0; \
   PRM2.3 = 0; \
}
#define mLDBIocSetEdgeDetection_CR20_RisingEdge() \
{ \
   PRM2.2 = 1; \
   PRM2.3 = 0; \
}
#define mLDBIocSetEdgeDetection_CR20_BothEdges() \
{ \
   PRM2.2 = 1; \
   PRM2.3 = 1; \
}
#define mLDBIocSetEdgeDetection_CR21_FallingEdge() \
{ \
   PRM2.4 = 0; \
   PRM2.5 = 0; \
}
#define mLDBIocSetEdgeDetection_CR21_RisingEdge() \
{ \
   PRM2.4 = 1; \
   PRM2.5 = 0; \
}
#define mLDBIocSetEdgeDetection_CR21_BothEdges() \
{ \
   PRM2.4 = 1; \
   PRM2.5 = 1); \
}
#define mLDBIocSetEdgeDetection_CR22_FallingEdge() \
{ \
   PRM2.6 = 0; \
   PRM2.7 = 0; \
}
#define mLDBIocSetEdgeDetection_CR22_RisingEdge() \
{ \
   PRM2.6 = 1; \
   PRM2.7 = 0; \
}
#define mLDBIocSetEdgeDetection_CR22_BothEdges() \
{ \
   PRM2.6 = 1; \
   PRM2.7 = 1; \
}
/*----------------- */
/* PWM mode service */
/*----------------- */

/* This mode can only be used by TM 50 and 51 */

/* Set to PWM mode */
/*---------------- */

/* Concatenation's macros */
#define mLDBIocSetPWMMode(TM)       mLDBIocSetPWMMode2(TM)
#define mLDBIocSetPWMMode2(TM)      mLDBIocSetPWMMode_##TM()

/* Set to Pwm mode */
#define mLDBIocSetPWMMode_Timer50()    (TMC50 = 0x41)
#define mLDBIocSetPWMMode_Timer51()    (TMC51 = 0x41)

#define mLDBIocSetPWMMode_TimerH0()    \
    mLDBRegWrite1BitInRegister(TMHMD0, 2, 0); \
    mLDBRegWrite1BitInRegister(TMHMD0, 3, 1) \

#define mLDBIocSetPWMMode_TimerH1()    \
    mLDBRegWrite1BitInRegister(TMHMD1, 2, 0); \
    mLDBRegWrite1BitInRegister(TMHMD1, 3, 1) \


/* PWM operation enable */
/*--------------------- */

/* Concatenation's macros */
#define mLDBIocPWMOutputEnable(TM)  mLDBIocPWMOutputEnable2(TM)
#define mLDBIocPWMOutputEnable2(TM) mLDBIocPWMOutputEnable_##TM()

/* Output enable */
#define mLDBIocPWMOutputEnable_Timer50() \
{ \
   P3.4 = 0;  \
   TOE50 = 1; \
}
#define mLDBIocPWMOutputEnable_Timer51() \
{ \
   P9.1 = 0;  \
   TOE50 = 1; \
}
#define mLDBIocPWMOutputEnable_TimerH0()    mLDBRegWrite1BitInRegister(TMHMD0, 0, 1)
#define mLDBIocPWMOutputEnable_TimerH1()    mLDBRegWrite1BitInRegister(TMHMD1, 0, 1)


/* PWM operation disable */
/*---------------------- */

/* Concatenation's macros */
#define mLDBIocPWMOutputDisable(TM)        mLDBIocPWMOutputDisable2(TM)
#define mLDBIocPWMOutputDisable2(TM)       mLDBIocPWMOutputDisable_##TM()

/* Output disable */
#define mLDBIocPWMOutputDisable_Timer50() \
{ \
   TOE50 = 0; \
   P3.4 = 1;  \
}
#define mLDBIocPWMOutputDisable_Timer51() \
{ \
   TOE50 = 0; \
   P9.1 = 1;  \
}
#define mLDBIocPWMOutputDisable_TimerH0()    mLDBRegWrite1BitInRegister(TMHMD0, 0, 0)
#define mLDBIocPWMOutputDisable_TimerH1()    mLDBRegWrite1BitInRegister(TMHMD1, 0, 0)

/* Select Active Level */
/*-------------------- */

/* Concatenation's macros */
#define mLDBIocSetActiveLevel(TM, Level)        mLDBIocSetActiveLevel2(TM, Level)
#define mLDBIocSetActiveLevel2(TM, Level)       mLDBIocSetActiveLevel_##TM(Level)
#define mLDBIocSetActiveLevel_Timer50(Level)       mLDBIocSetActiveLevel_Timer50_##Level()
#define mLDBIocSetActiveLevel_Timer51(Level)       mLDBIocSetActiveLevel_Timer51_##Level()
#define mLDBIocSetActiveLevel_TimerH0(Level)       mLDBIocSetActiveLevel_TimerH0_##Level()
#define mLDBIocSetActiveLevel_TimerH1(Level)       mLDBIocSetActiveLevel_TimerH1_##Level()

/* Set to Pwm mode */
#define mLDBIocSetActiveLevel_Timer50_High()      (TMC50.1 = 0)
#define mLDBIocSetActiveLevel_Timer50_Low()       (TMC50.1 = 1)
#define mLDBIocSetActiveLevel_Timer51_High()      (TMC51.1 = 0)
#define mLDBIocSetActiveLevel_Timer51_Low()       (TMC51.1 = 1)
#define mLDBIocSetActiveLevel_TimerH0_High()      mLDBRegWrite1BitInRegister(TMHMD0, 1, 0)
#define mLDBIocSetActiveLevel_TimerH0_Low()       mLDBRegWrite1BitInRegister(TMHMD0, 1, 1)
#define mLDBIocSetActiveLevel_TimerH1_High()      mLDBRegWrite1BitInRegister(TMHMD1, 1, 0)
#define mLDBIocSetActiveLevel_TimerH1_Low()       mLDBRegWrite1BitInRegister(TMHMD1, 1, 1)

/* Select Duty Cycle */
/*-------------------- */
#define mLDBIocSetPwmDutyCycle(TM, DutyCycle)   mLDBIocSetPwmDutyCycle2(TM, DutyCycle)
#define mLDBIocSetPwmDutyCycle2(TM, DutyCycle)  mLDBIocSetPwmDutyCycle_##TM(DutyCycle)

#define mLDBIocSetPwmDutyCycle_TimerH0(DutyCycle)   mLDBRegWrite8BitRegister(CMP10, DutyCycle)
#define mLDBIocSetPwmDutyCycle_TimerH1(DutyCycle)   mLDBRegWrite8BitRegister(CMP11, DutyCycle)

/* Refresh Duty Cycle (See precaution list for Timer Hn) */
/*-------------------- */
#define mLDBIocRefreshPwmDutyCycle(TM)   mLDBIocRefreshPwmDutyCycle2(TM)
#define mLDBIocRefreshPwmDutyCycle2(TM)  mLDBIocRefreshPwmDutyCycle_##TM()

#define mLDBIocRefreshPwmDutyCycle_TimerH0()  \
    mLDBIocSetPwmDutyCycle_TimerH0(mLDBRegRead8BitRegister(CMP10))
#define mLDBIocRefreshPwmDutyCycle_TimerH1()  \
    mLDBIocSetPwmDutyCycle_TimerH1(mLDBRegRead8BitRegister(CMP11))

/*---------------------------- */
/* Output compare mode service */
/*---------------------------- */

/* This mode can only be used by TM 51 and 52 */

/* Select Output Compare mode */
/*--------------------------- */

/* Concatenation's macros */
#define mLDBIocSetTriggerModeOutputCompare(TM)  mLDBIocSetTriggerModeOutputCompare2(TM)
#define mLDBIocSetTriggerModeOutputCompare2(TM) mLDBIocSetTriggerModeOutputCompare_##TM()

/* Set to Ouput Compare mode */
#define mLDBIocSetTriggerModeOutputCompare_Timer50()  (TMC50 = 0x03)
#define mLDBIocSetTriggerModeOutputCompare_Timer51()  (TMC51 = 0x03)

/* Activate Output Toggle */
/*----------------------- */

/* Concatenation's macros */
#define mLDBIocSetOutputToggle(TM)              mLDBIocSetOutputToggle2(TM)
#define mLDBIocSetOutputToggle2(TM)             mLDBIocSetOutputToggle_##TM()

/* Activate Output Toggle */
#define mLDBIocSetOutputToggle_Timer50() \
{ \
   TOE50 = 1; \
   TMC50.1 = 1; \
}
#define mLDBIocSetOutputToggle_Timer51() \
{ \
   TMC51.0 = 1; \
   TMC51.1 = 1; \
}

/* Desactivate Output Toggle */
/*-------------------------- */

/* Concatenation's macros */
#define mLDBIocUnsetOutputToggle(TM)              mLDBIocUnsetOutputToggle2(TM)
#define mLDBIocUnsetOutputToggle2(TM)             mLDBIocUnsetOutputToggle_##TM()

/* Desactivate Output Toggle */
#define mLDBIocUnsetOutputToggle_Timer50() \
{ \
   TOE50 = 0; \
   TMC50.1 = 0; \
}
#define mLDBIocUnsetOutputToggle_Timer51() \
{ \
   TMC51.0 = 0; \
   TMC51.1 = 0; \
}

/* Set Output */
/*----------- */

/* Concatenation's macros */
#define mLDBIocSetOutput(TM)              mLDBIocSetOutput2(TM)
#define mLDBIocSetOutput2(TM)             mLDBIocSetOutput_##TM()

/* Activate Output Toggle */
#define mLDBIocSetOutput_Timer50() \
{ \
   LVR50 = 1; \
   LVS50 = 0; \
}
#define mLDBIocSetOutput_Timer51() \
{ \
   TMC51.2 = 1; \
   TMC51.3 = 0; \
}

/* Reset Output */
/*------------- */

/* Concatenation's macros */
#define mLDBIocResetOutput(TM)            mLDBIocResetOutput2(TM)
#define mLDBIocResetOutput2(TM)           mLDBIocResetOutput_##TM()

/* Activate Output Toggle */
#define mLDBIocResetOutput_Timer50() \
{ \
   LVR50 = 0; \
   LVS50 = 1; \
}
#define mLDBIocResetOutput_Timer51() \
{ \
   TMC51.2 = 0; \
   TMC51.3 = 1; \
}

/* No change of Output */
/*-------------------- */

/* Concatenation's macros */
#define mLDBIocNoChangeOutput(TM)         mLDBIocNoChangeOutput2(TM)
#define mLDBIocNoChangeOutput2(TM)        mLDBIocNoChangeOutput_##TM()

/* Activate Output Toggle */
#define mLDBIocNoChangeOutput_Timer50() \
{ \
   LVR50 = 0; \
   LVS50 = 0; \
}
#define mLDBIocNoChangeOutput_Timer51() \
{ \
   TMC51.2 = 0; \
   TMC51.3 = 0; \
}

/*-------------------------------------------------------------------------
  Exported functions

  extern tReturnType CMPFunctionName(tTypeArgument1 ArgumentName1, ... );
  -------------------------------------------------------------------------*/ 
extern void LDBIocInit(void);

#endif   /* I_LDB_IOC_H */
