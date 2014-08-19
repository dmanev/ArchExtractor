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
// Component:    LDB_INT
// -----------------------------------------------------------------------------
// $Date:   Nov 17 2009 11:23:54  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_INT/LDB_INTP.H-arc  $
// $Revision:   1.6  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_INT/LDB_INTP.H-arc  $
// 
//    Rev 1.6   Nov 17 2009 11:23:54   adzhelp
// Cm006675: INTTM50 enabled for CPU trace configuration
// 
//    Rev 1.5   Jul 24 2009 14:43:04   amanevd
// Cm005466: Preemtion on not critical interrupts
// 
//    Rev 1.4   Jul 16 2009 08:57:20   adzhelp
// Cm005205: INTTMH1 shared between sleep system timer, verlog and roomlamp dimming
// 
//    Rev 1.3   Jul 10 2009 15:06:36   adzhelp
// Cm005100: SAD.ROB.INT.02.R01 - Unexpected interrupts treatment  
// 
//    Rev 1.2   Apr 27 2009 15:50:46   adzhelp
// Cm003272: Sharing of timers 00/01 and H1implemented and their interrupt priorities set to high
// 
//    Rev 1.1   Mar 10 2009 16:10:38   adzhelp
// Cm003619: Parameterization for NEC K0
// 
//    Rev 1.0   10 Nov 2008 15:21:18   ailievb
// Initial revision.
//******************************************************************************

#ifndef I_LDB_INT_P_H
#define I_LDB_INT_P_H (1)

/*-------------------------------------------------------------------------
  Included files to resolve specific definitions in this file

  #include <system_file_name.h>
  #include "project_file_name.h"
  -------------------------------------------------------------------------*/
#include "deftypes.h"

/*-------------------------------------------------------------------------
  Constant data

  #define cCMPConstantName   ((tType) ConstantValue)
  -------------------------------------------------------------------------*/

// ---------------------------------------------
// Priority
// ---------------------------------------------
// Set each bit to either '0' (high priority), '1' (low priority)
#define cLDBIntPR0L ((U8)0xFFU )
#define cLDBIntPR0H ((U8)~(cLDBIntTMMK000 | cLDBIntTMMK010))
#define cLDBIntPR1L ((U8)0xFFU)
#define cLDBIntPR1H ((U8)~(cLDBIntTMMK001 | cLDBIntTMMK011))
// Shared interrupt for Timer 00 and 01
#define cLDBIntNoOwnerTM00TM01      0
#define cLDBIntTrpOwnerTM00TM01     1
#define cLDBIntRfOwnerTM00TM01      2

// Shared interrupt for Timer H1
#define cLDBIntNoOwnerTMH1          0
#define cLDBIntTrpPwmOwnerTMH1      1  // Resource is taken by PWM which enables TRP as well
#define cLDBIntTimOwnerTMH1         2

/*-------------------------------------------------------------------------
  Exported Macros

  #define mCMPMacroName   (MacroDefinition)
  -------------------------------------------------------------------------*/ 

// -----------------------------
// ISR Activation
// -----------------------------
// TODO: Just uncomment the line when you want to use an Isr

//#define INTCK2_ENABLE
//#define INTNMI_ENABLE
//#define INTLVI_ENABLE
//#define INTP0_ENABLE
//#define INTP1_ENABLE
//#define INTP2_ENABLE
//#define INTP3_ENABLE
//#define INTP4_ENABLE
//#define INTP5_ENABLE
//#define INTSRE6_ENABLE
//#define INTSR6_ENABLE
#define INTST6_ENABLE
//#define INTCSI10_ENABLE
#define INTST0_ENABLE
#define INTTMH1_ENABLE
#define INTTMH0_ENABLE

#ifdef TRACE_CPU_ACTIVE
#define INTTM50_ENABLE
#else
//#define INTTM50_ENABLE
#endif

#define INTTM000_ENABLE
#define INTTM010_ENABLE
//#define INTAD_ENABLE
#define INTSR0_ENABLE
#define INTWTI_ENABLE
//#define INTTM51_ENABLE
//#define INTKR_ENABLE
//#define INTWT_ENABLE
#define INTP6_ENABLE
//#define INTP7_ENABLE
//#define INTDMU_ENABLE
//#define INTIIC0_ENABLE
//#define INTCSI11_ENABLE
#define INTTM001_ENABLE
#define INTTM011_ENABLE
//#define BRK_I_ENABLE

  
// Shared interrupt for Timer 00 and 01
#define mLDBIntGetInterruptTM00TM01(InterruptOwnerId)                           \
          mLIBassert((LDBIntInterruptOwnerTM00TM01 == InterruptOwnerId)         \
                   ||(LDBIntInterruptOwnerTM00TM01 == cLDBIntNoOwnerTM00TM01)); \
          LDBIntInterruptOwnerTM00TM01 = InterruptOwnerId

#define mLDBIntReleaseInterruptTM00TM01(InterruptOwnerId);                      \
          mLIBassert((LDBIntInterruptOwnerTM00TM01 == InterruptOwnerId)         \
                   ||(LDBIntInterruptOwnerTM00TM01 == cLDBIntNoOwnerTM00TM01)); \
          LDBIntInterruptOwnerTM00TM01 = cLDBIntNoOwnerTM00TM01


// Shared interrupt for Timer H1
#define mLDBIntGetInterruptTMH1(InterruptOwnerId)                               \
          mLIBassert((LDBIntInterruptOwnerTMH1 == InterruptOwnerId)             \
                   ||(LDBIntInterruptOwnerTMH1 == cLDBIntNoOwnerTMH1));         \
          LDBIntInterruptOwnerTMH1 = InterruptOwnerId

#define mLDBIntReleaseInterruptTMH1(InterruptOwnerId);                          \
          mLIBassert((LDBIntInterruptOwnerTMH1 == InterruptOwnerId)             \
                   ||(LDBIntInterruptOwnerTMH1 == cLDBIntNoOwnerTMH1));         \
          LDBIntInterruptOwnerTMH1 = cLDBIntNoOwnerTMH1

// ---------------------------------------------
// Registers
// ---------------------------------------------

// ---------------------------------------------
//  How declare an Isr (Interrupt Service Routine)
// ---------------------------------------------

// mLDBIntDeclareIsr(INTxxx)
// {
//     mLDBIntEnterIsr(INTxxx);
//     ...
//     ... code ...
//     ...
//     mLDBIntLeaveIsr(INTxxx);
// }

// For example for the Isr CE :
//
// mLDBIntDeclareIsr(INTCE)
// {
//     mLDBIntEnterIsr(INTCE);
//     ...
//     ... code ...
//     ...
//     mLDBIntLeaveIsr(INTCE);
// }

// ---------------------------------------------
//  How to Enable & Disable an ISR
// ---------------------------------------------

//  mLDBIntEnableIsr(INTxxx);
//  mLDBIntDisableIsr(INTxxx);
//  mLDBIntGetIsrRequestFlag(INTxxx);
//  mLDBIntClearIsrRequestFlag(INTxxx);
//
//  For example for the Isr CE :
//
//  mLDBIntEnableIsr(INTCE);
//  mLDBIntDisableIsr(INTCE);
//  mLDBIntGetIsrRequestFlag(INTCE);
//  mLDBIntClearIsrRequestFlag(INTCE);

// ---------------------------------------------
//  ISR Affectation
// ---------------------------------------------
// Either 'Level2' or 'Leve1' can be set
// Level 2 interrupts cannot be preempted
#define cLDBIntLevINTLVI    Level2
#define cLDBIntLevINTP0     Level2
#define cLDBIntLevINTP1     Level2
#define cLDBIntLevINTP2     Level2
#define cLDBIntLevINTP3     Level2
#define cLDBIntLevINTP4     Level2
#define cLDBIntLevINTP5     Level2
#define cLDBIntLevINTSRE6   Level2
#define cLDBIntLevINTSR6    Level2
#define cLDBIntLevINTST6    Level1
#define cLDBIntLevINTCSI10  Level2 // shared with INTST0
#define cLDBIntLevINTST0    Level1 // shared with INTCSI10
#define cLDBIntLevINTTMH1   Level1
#define cLDBIntLevINTTMH0   Level1
#define cLDBIntLevINTTM50   Level2
#define cLDBIntLevINTTM000  Level2
#define cLDBIntLevINTTM010  Level2
#define cLDBIntLevINTAD     Level2
#define cLDBIntLevINTSR0    Level1
#define cLDBIntLevINTWTI    Level1
#define cLDBIntLevINTTM51   Level2
#define cLDBIntLevINTKR     Level2
#define cLDBIntLevINTWT     Level2
#define cLDBIntLevINTP6     Level1
#define cLDBIntLevINTP7     Level2
#define cLDBIntLevINTIIC0   Level2 // shared with INTDMU
#define cLDBIntLevINTDMU    Level2 // shared with INTIIC0
#define cLDBIntLevINTCSI11  Level2
#define cLDBIntLevINTTM001  Level2
#define cLDBIntLevINTTM011  Level2

// ---------------------------------------------
//  Definition of Banks usage
// ---------------------------------------------
// No banks of interrupts for CPU used

// ---------------------------------------------
// Enter / Leave IT Level 1
// ---------------------------------------------

#define cLDBIntLevel1MK0H  (cLDBIntSTMK6+cLDBIntSTMK0+cLDBIntTMMKH0+cLDBIntTMMKH1)
#define cLDBIntLevel1MK1L  (cLDBIntSRMK0+cLDBIntWTIMK+cLDBIntPMK6)

#define mLDBIntEnterIsrLevel1  LDBIntLevel = 1;           \
                               MK0H |= cLDBIntLevel1MK0H; \
                               MK1L |= cLDBIntLevel1MK1L; \
                               _EI();

#define mLDBIntLeaveIsrLevel1  _DI();            \
                               LDBIntLevel = 0;  \
                               {                                        \
                                    U8  u8Tmp=LDBIntGroup1.Reg.MK0H;    \
                                    MK0H &= u8Tmp;                      \
                                    u8Tmp=LDBIntGroup1.Reg.MK1L;        \
                                    MK1L &= u8Tmp;                      \
                               }

// ---------------------------------------------
// Enter / Leave IT Level 2
// ---------------------------------------------

#define mLDBIntEnterIsrLevel2  U8 MemoLevel = LDBIntLevel; LDBIntLevel = 2;
#define mLDBIntLeaveIsrLevel2  LDBIntLevel = MemoLevel; 


/*-------------------------------------------------------------------------
  Exported type

  struct  sCMPStructureName { ... };
  union   uCMPUnionName { ... };
  enum    eCMPEnumerationName { ... };
  typedef Expression tCMPTypeName;

  -------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
  Exported data

  extern  tType   CMPVariableName;
  extern  tType*  pCMPVariableName; 
  -------------------------------------------------------------------------*/ 
extern U8 LDBIntInterruptOwnerTM00TM01;
extern U8 LDBIntInterruptOwnerTMH1;

/*-------------------------------------------------------------------------
  Constant exported data

  extern const tType  CMPVariableName;
  -------------------------------------------------------------------------*/ 

/*-------------------------------------------------------------------------
  Exported functions

  extern tReturnType CMPFunctionName(tTypeArgument1 ArgumentName1, ... );
  -------------------------------------------------------------------------*/ 
// functions sharing interrupts
extern void LDBTrpTimeOutIt(void);
extern void LDBTrpPPGIt(void);
extern void LDBTrpTimeCaptureIt(void);
extern void LDBTrpVerlogTimerIt(void);
extern void LDBPwmControlFadingIt(void);
extern void LDBRfInterruptRfOCIt(void);
extern void LDBRfInterruptRfICIt(void);
extern void LDBTimSleepInterruptRealTime(void);

#endif   /* I_LDB_INT_P_H */
