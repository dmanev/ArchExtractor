/*============================================================================
  Project ......................... STANDARD
  Component ....................... LDB_INT
  File revision.................... :   1.1  $
  Last modification date .......... $Modtime:   Jul 24 2009 14:37:50  $
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
  cmp.h file review :
  


  ==========================================================================*/

#ifndef I_LDB_INT_H
#define I_LDB_INT_H (1)

/*-------------------------------------------------------------------------
  Included files to resolve specific definitions in this file

  #include <system_file_name.h>
  #include "project_file_name.h"
  -------------------------------------------------------------------------*/

#include "deftypes.h"
#include "ldb_reg.h"
#include "ldb_tos.h"
#include "ldb_har.h"
#include "ldb_intp.h"

/*-------------------------------------------------------------------------
  Constant data

  #define cCMPConstantName   ((tType) ConstantValue)
  -------------------------------------------------------------------------*/
#ifdef cLDBHarMicro78K0_F0536

// MK0L Bits
#define cLDBIntSREMK6     0x80
#define cLDBIntPMK5       0x40
#define cLDBIntPMK4       0x20
#define cLDBIntPMK3       0x10
#define cLDBIntPMK2       0x08
#define cLDBIntPMK1       0x04
#define cLDBIntPMK0       0x02
#define cLDBIntLVIMK      0x01

// MK0H Bits
#define cLDBIntTMMK010    0x80
#define cLDBIntTMMK000    0x40
#define cLDBIntTMMK50     0x20
#define cLDBIntTMMKH0     0x10
#define cLDBIntTMMKH1     0x08
#define cLDBIntSTMK0      0x04
#define cLDBIntCSIMK10    0x04
#define cLDBIntSTMK6      0x02
#define cLDBIntSRMK6      0x01

// MK1L Bits
#define cLDBIntPMK7       0x80
#define cLDBIntPMK6       0x40
#define cLDBIntWTMK       0x20
#define cLDBIntKRMK       0x10
#define cLDBIntTMMK51     0x08
#define cLDBIntWTIMK      0x04
#define cLDBIntSRMK0      0x02
#define cLDBIntADMK       0x01

// MK1H Bits
#define cLDBIntTMMK011    0x08
#define cLDBIntTMMK001    0x04
#define cLDBIntCSIMK11    0x02
#define cLDBIntIICMK0     0x01
#define cLDBIntDMUMK      0x01

#else // STK
// MKOH Bits
#define cLDBIntPMK1       0x80
#define cLDBIntPMK0       0x40
#define cLDBIntTMMK22     0x20
#define cLDBIntTMMK21     0x10
#define cLDBIntTMMK20     0x08
#define cLDBIntOVFMK      0x04
#define cLDBIntADMK       0x02
#define cLDBIntWDTMK      0x01

// MKOH Bits
#define cLDBIntSRMK0      0x80
#define cLDBIntSERMK0     0x40
#define cLDBIntCSIMK30    0x20
#define cLDBIntCTMK1      0x10
#define cLDBIntCTMK0      0x08
#define cLDBIntCRMK       0x04
#define cLDBIntCEMK       0x02
#define cLDBIntPMK2       0x01

// MKOH Bits
#define cLDBIntCSIMK31    0x80
#define cLDBIntWTMK       0x40
#define cLDBIntWTIMK      0x20
#define cLDBIntUNUSED     0x10
#define cLDBIntTMMK52     0x08
#define cLDBIntTMMK51     0x04
#define cLDBIntTMMK50     0x02
#define cLDBIntSTMK0      0x01
#endif

// Cpu Trace identifiers
//#define cLDBIntCpuTraceINTReset 128
#define cLDBIntCpuTraceINTWDT   129
#define cLDBIntCpuTraceINTAD    130
#define cLDBIntCpuTraceINTOVF   131
#define cLDBIntCpuTraceINTTM20  132
#define cLDBIntCpuTraceINTTM21  133
#define cLDBIntCpuTraceINTTM22  134
#define cLDBIntCpuTraceINTP0    135
#define cLDBIntCpuTraceINTP1    136
#define cLDBIntCpuTraceINTP2    137
#define cLDBIntCpuTraceINTCE    138
#define cLDBIntCpuTraceINTCR    139
#define cLDBIntCpuTraceINTCT0   140
#define cLDBIntCpuTraceINTCT1   141
#define cLDBIntCpuTraceINTCSI30 142
#define cLDBIntCpuTraceINTSER0  143
#define cLDBIntCpuTraceINTSR0   144
#define cLDBIntCpuTraceINTST0   145
#define cLDBIntCpuTraceINTTM50  146
#define cLDBIntCpuTraceINTTM51  147
#define cLDBIntCpuTraceINTTM52  148
#define cLDBIntCpuTraceINTWTI   149
#define cLDBIntCpuTraceINTWT    150
#define cLDBIntCpuTraceINTCSI31 151
#ifdef cLDBHarMicro78K0_F0536
#define cLDBIntCpuTraceINTLVI   152
#define cLDBIntCpuTraceINTP3    153
#define cLDBIntCpuTraceINTP4    154
#define cLDBIntCpuTraceINTP5    155
#define cLDBIntCpuTraceINTSRE6  156
#define cLDBIntCpuTraceINTSR6   157
#define cLDBIntCpuTraceINTST6   158
#define cLDBIntCpuTraceINTCSI10 159
#define cLDBIntCpuTraceINTTMH1  160
#define cLDBIntCpuTraceINTTMH0  161
#define cLDBIntCpuTraceINTTM000 162
#define cLDBIntCpuTraceINTTM010 163
#define cLDBIntCpuTraceINTKR    164
#define cLDBIntCpuTraceINTP6    165
#define cLDBIntCpuTraceINTP7    166
#define cLDBIntCpuTraceINTIIC0  167
#define cLDBIntCpuTraceINTDMU   168
#define cLDBIntCpuTraceINTCSI11 169
#define cLDBIntCpuTraceINTTM001 170
#define cLDBIntCpuTraceINTTM011 171
#endif

/*-------------------------------------------------------------------------
  Exported Macros

  #define mCMPMacroName   (MacroDefinition)
  -------------------------------------------------------------------------*/ 

// ---------------------------------------------
// General macros
// ---------------------------------------------

// Theses macros needs to get the Interrupt Name and interupt level.
// All theses macro uses this type of definition :
//
// #define mLDBIntXxxIsr(Name)        mLDBIntXxxIsr2(Name)
// #define mLDBIntXxxIsr2(Name)       mLDBIntXxxIsr3(Name,cLDBIntLev##Name)
// #define mLDBIntXxxIsr3(Name,Level) mLDBIntXxxIsr4(Name,Level)
// #define mLDBIntXxxIsr4(Name,Level) ...
//
// For example :
// Component calls  : mLDBIntXxxIsr(cLDBHarIsrCanError)
// After first line : mLDBIntXxxIsr2(INTCE)
// After next line  : mLDBIntXxxIsr3(INTCE,cLDBIntLevINTCE)
// After next line  : mLDBIntXxxIsr4(INTCE,Level1)
// 
// So the last line can use Name and Level.

#ifndef _QAC_

#ifdef cLDBHarMicro78K0_F0536
#define mLDBIntDeclareIsr(Name)        mLDBIntDeclareIsr2(Name)
#define mLDBIntDeclareIsr2(Name)       __interrupt void LDBIntIsr##Name(void)

#else // STK
#define mLDBIntDeclareIsr(Name)        mLDBIntDeclareIsr2(Name)
#define mLDBIntDeclareIsr2(Name)       mLDBIntDeclareIsr3(Name,cLDBIntLev##Name)
#define mLDBIntDeclareIsr3(Name,Level) mLDBIntDeclareIsr4(Name,Level)
#define mLDBIntDeclareIsr4(Name,Level) interrupt[Name##_vect] mLDBIntBank##Level void LDBIntIsr##Name(void)
#endif

#define mLDBIntEnterIsr(Name)          mLDBIntEnterIsr2(Name)
#define mLDBIntEnterIsr2(Name)         mLDBIntEnterIsr3(Name,cLDBIntLev##Name)
#define mLDBIntEnterIsr3(Name,Level)   mLDBIntEnterIsr4(Name,Level)
#define mLDBIntEnterIsr4(Name,Level)   mLDBEnterInterrupt(cLDBIntCpuTrace##Name); {mLDBIntEnterIsr##Level

#define mLDBIntLeaveIsr(Name)          mLDBIntLeaveIsr2(Name)
#define mLDBIntLeaveIsr2(Name)         mLDBIntLeaveIsr3(Name,cLDBIntLev##Name)
#define mLDBIntLeaveIsr3(Name,Level)   mLDBIntLeaveIsr4(Name,Level)
#define mLDBIntLeaveIsr4(Name,Level)   mLDBIntLeaveIsr##Level; } mLDBLeaveInterrupt();

#define mLDBIntDisableIsr(Name)        mLDBIntDisableIsr2(Name)
#define mLDBIntDisableIsr2(Name)       mLDBIntDisableIsr3(Name,cLDBIntLev##Name)
#define mLDBIntDisableIsr3(Name,Level) mLDBIntDisableIsr4(Name,Level)
#define mLDBIntDisableIsr4(Name,Level) mLDBIntDisableIsr##Level( Bit##Name )

#define mLDBIntEnableIsr(Name)         mLDBIntEnableIsr2(Name)
#define mLDBIntEnableIsr2(Name)        mLDBIntEnableIsr3(Name,cLDBIntLev##Name)
#define mLDBIntEnableIsr3(Name,Level)  mLDBIntEnableIsr4(Name,Level)
#define mLDBIntEnableIsr4(Name,Level)  mLDBIntEnableIsr##Level( Bit##Name )

#define mLDBIntSetIsrRequestFlag(Name)    mLDBIntSetIsrRequestFlag2(Name)
#define mLDBIntSetIsrRequestFlag2(Name)   {mLDBIntRegisterIsrRequestBit##Name = 1;}

#define mLDBIntClearIsrRequestFlag(Name)  mLDBIntClearIsrRequestFlag2(Name)
#define mLDBIntClearIsrRequestFlag2(Name) {mLDBIntRegisterIsrRequestBit##Name = 0;}

#define mLDBIntGetIsrRequestFlag(Name)    mLDBIntGetIsrRequestFlag2(Name)
#define mLDBIntGetIsrRequestFlag2(Name)   (mLDBIntRegisterIsrRequestBit##Name)

#else // QAC
#define mLDBIntDeclareIsr(Name)             void LDBIntIsr##Name(void)
#define mLDBIntEnterIsr(Name)               
#define mLDBIntLeaveIsr(Name)               
#define mLDBIntClearIsrRequestFlag(Name)    
#define mLDBIntSetIsrRequestFlag(Name)      
#define mLDBIntEnableIsr(Name)              
#define mLDBIntDisableIsr(Name)             
#endif
// ---------------------------------------------
// Enable / Disable interrupts
// ---------------------------------------------

#define mLDBIntEnableAllIts()   _EI()
#define mLDBIntDisableAllIts()  _DI()

// ---------------------------------------------
// Enable / Disable IT Level 1&2
// ---------------------------------------------
#define mLDBIntDisableIsrLevel1(Name)                \
    _DI();                                           \
    LDBIntGroup1.Bit.##Name=1;                       \
    if(LDBIntLevel==0){mLDBIntRegisterIsrEnable##Name = 1;}\
    if(LDBIntLevel!=2){_EI();}

#define mLDBIntEnableIsrLevel1(Name)                 \
    _DI();                                           \
    LDBIntGroup1.Bit.##Name=0;                       \
    if(LDBIntLevel==0){mLDBIntRegisterIsrEnable##Name = 0;}\
    if(LDBIntLevel!=2){_EI();}                           


#define mLDBIntDisableIsrLevel2(Name) mLDBIntRegisterIsrEnable##Name = 1;
#define mLDBIntEnableIsrLevel2(Name)  mLDBIntRegisterIsrEnable##Name = 0;

// ---------------------------------------------
// Registers
// ---------------------------------------------
#ifdef cLDBHarMicro78K0_F0536

//Enable
#define mLDBIntRegisterIsrEnableBitINTLVI   LVIMK
#define mLDBIntRegisterIsrEnableBitINTP0    PMK0
#define mLDBIntRegisterIsrEnableBitINTP1    PMK1
#define mLDBIntRegisterIsrEnableBitINTP2    PMK2
#define mLDBIntRegisterIsrEnableBitINTP3    PMK3
#define mLDBIntRegisterIsrEnableBitINTP4    PMK4
#define mLDBIntRegisterIsrEnableBitINTP5    PMK5
#define mLDBIntRegisterIsrEnableBitINTSRE6  SREMK6
#define mLDBIntRegisterIsrEnableBitINTSR6   SRMK6
#define mLDBIntRegisterIsrEnableBitINTST6   STMK6
#define mLDBIntRegisterIsrEnableBitINTCSI10 CSIMK10 // shared with INTST0
#define mLDBIntRegisterIsrEnableBitINTST0   STMK0   // shared with INTCSI10
#define mLDBIntRegisterIsrEnableBitINTTMH1  TMMKH1
#define mLDBIntRegisterIsrEnableBitINTTMH0  TMMKH0
#define mLDBIntRegisterIsrEnableBitINTTM50  TMMK50
#define mLDBIntRegisterIsrEnableBitINTTM000 TMMK000
#define mLDBIntRegisterIsrEnableBitINTTM010 TMMK010
#define mLDBIntRegisterIsrEnableBitINTAD    ADMK
#define mLDBIntRegisterIsrEnableBitINTSR0   SRMK0
#define mLDBIntRegisterIsrEnableBitINTWTI   WTIMK
#define mLDBIntRegisterIsrEnableBitINTTM51  TMMK51
#define mLDBIntRegisterIsrEnableBitINTKR    KRMK
#define mLDBIntRegisterIsrEnableBitINTWT    WTMK
#define mLDBIntRegisterIsrEnableBitINTP6    PMK6
#define mLDBIntRegisterIsrEnableBitINTP7    PMK7
#define mLDBIntRegisterIsrEnableBitINTIIC0  IICMK0 // shared with INTDMU
#define mLDBIntRegisterIsrEnableBitINTDMU   DMUMK  // shared with INTIIC0
#define mLDBIntRegisterIsrEnableBitINTCSI11 CSIMK11
#define mLDBIntRegisterIsrEnableBitINTTM001 TMMK001
#define mLDBIntRegisterIsrEnableBitINTTM011 TMMK011

//Request
#define mLDBIntRegisterIsrRequestBitINTLVI   LVIIF
#define mLDBIntRegisterIsrRequestBitINTP0    PIF0
#define mLDBIntRegisterIsrRequestBitINTP1    PIF1
#define mLDBIntRegisterIsrRequestBitINTP2    PIF2
#define mLDBIntRegisterIsrRequestBitINTP3    PIF3
#define mLDBIntRegisterIsrRequestBitINTP4    PIF4
#define mLDBIntRegisterIsrRequestBitINTP5    PIF5
#define mLDBIntRegisterIsrRequestBitINTSRE6  SREIF6
#define mLDBIntRegisterIsrRequestBitINTSR6   SRIF6
#define mLDBIntRegisterIsrRequestBitINTST6   STIF6
#define mLDBIntRegisterIsrRequestBitINTCSI10 CSIIF10 // shared with INTST0
#define mLDBIntRegisterIsrRequestBitINTST0   STIF0   // shared with INTCSI10
#define mLDBIntRegisterIsrRequestBitINTTMH1  TMIFH1
#define mLDBIntRegisterIsrRequestBitINTTMH0  TMIFH0
#define mLDBIntRegisterIsrRequestBitINTTM50  TMIF50
#define mLDBIntRegisterIsrRequestBitINTTM000 TMIF000
#define mLDBIntRegisterIsrRequestBitINTTM010 TMIF010
#define mLDBIntRegisterIsrRequestBitINTAD    ADIF
#define mLDBIntRegisterIsrRequestBitINTSR0   SRIF0
#define mLDBIntRegisterIsrRequestBitINTWTI   WTIIF
#define mLDBIntRegisterIsrRequestBitINTTM51  TMIF51
#define mLDBIntRegisterIsrRequestBitINTKR    KRIF
#define mLDBIntRegisterIsrRequestBitINTWT    WTIF
#define mLDBIntRegisterIsrRequestBitINTP6    PIF6
#define mLDBIntRegisterIsrRequestBitINTP7    PIF7
#define mLDBIntRegisterIsrRequestBitINTIIC0  IICIF0 // shared with INTDMU
#define mLDBIntRegisterIsrRequestBitINTDMU   DMUIF  // shared with INTIIC0
#define mLDBIntRegisterIsrRequestBitINTCSI11 CSIIF11
#define mLDBIntRegisterIsrRequestBitINTTM001 TMIF001
#define mLDBIntRegisterIsrRequestBitINTTM011 TMIF011

#else // STK

#define mLDBIntRegisterIsrEnableBitINTCE    CEMK
#define mLDBIntRegisterIsrEnableBitINTCR    CRMK
#define mLDBIntRegisterIsrEnableBitINTCT0   CTMK0
#define mLDBIntRegisterIsrEnableBitINTCT1   CTMK1
#define mLDBIntRegisterIsrEnableBitINTP0    PMK0
#define mLDBIntRegisterIsrEnableBitINTP1    PMK1
#define mLDBIntRegisterIsrEnableBitINTP2    PMK2
#define mLDBIntRegisterIsrEnableBitINTOVF   OVFMK
#define mLDBIntRegisterIsrEnableBitINTTM20  TMMK20
#define mLDBIntRegisterIsrEnableBitINTTM21  TMMK21
#define mLDBIntRegisterIsrEnableBitINTTM22  TMMK22
#define mLDBIntRegisterIsrEnableBitINTTM50  TMMK50
#define mLDBIntRegisterIsrEnableBitINTTM51  TMMK51
#define mLDBIntRegisterIsrEnableBitINTTM52  TMMK52
#define mLDBIntRegisterIsrEnableBitINTWTI   WTIMK
#define mLDBIntRegisterIsrEnableBitINTWT    WTMK
#define mLDBIntRegisterIsrEnableBitINTWDT   WDTMK
#define mLDBIntRegisterIsrEnableBitINTAD    ADMK
#define mLDBIntRegisterIsrEnableBitINTCSI30 CSIMK30
#define mLDBIntRegisterIsrEnableBitINTSER0  SERMK0
#define mLDBIntRegisterIsrEnableBitINTSR0   SRMK0
#define mLDBIntRegisterIsrEnableBitINTST0   STMK0 
#define mLDBIntRegisterIsrEnableBitINTCSI31 CSIMK31


#define mLDBIntRegisterIsrRequestBitINTCE    CEIF
#define mLDBIntRegisterIsrRequestBitINTCR    CRIF
#define mLDBIntRegisterIsrRequestBitINTCT0   CTIF0
#define mLDBIntRegisterIsrRequestBitINTCT1   CTIF1
#define mLDBIntRegisterIsrRequestBitINTP0    PIF0
#define mLDBIntRegisterIsrRequestBitINTP1    PIF1
#define mLDBIntRegisterIsrRequestBitINTP2    PIF2
#define mLDBIntRegisterIsrRequestBitINTOVF   OVFIF
#define mLDBIntRegisterIsrRequestBitINTTM20  TMIF20
#define mLDBIntRegisterIsrRequestBitINTTM21  TMIF21
#define mLDBIntRegisterIsrRequestBitINTTM22  TMIF22
#define mLDBIntRegisterIsrRequestBitINTTM50  TMIF50
#define mLDBIntRegisterIsrRequestBitINTTM51  TMIF51
#define mLDBIntRegisterIsrRequestBitINTTM52  TMIF52
#define mLDBIntRegisterIsrRequestBitINTWTI   WTIIF
#define mLDBIntRegisterIsrRequestBitINTWT    WTIF
#define mLDBIntRegisterIsrRequestBitINTWDT   WDTIF
#define mLDBIntRegisterIsrRequestBitINTAD    ADIF
#define mLDBIntRegisterIsrRequestBitINTCSI30 CSIIF30
#define mLDBIntRegisterIsrRequestBitINTSER0  SERIF0
#define mLDBIntRegisterIsrRequestBitINTSR0   SRIF0
#define mLDBIntRegisterIsrRequestBitINTST0   STIF0 
#define mLDBIntRegisterIsrRequestBitINTCSI31 CSIIF31

#endif

// ---------------------------------------------
// LDB internal
// ---------------------------------------------
#define mLDBIntInit()           LDBIntInit()
//#define mLDBIntEnterSleepMode() LDBIntEnterSleepMode()
//#define mLDBIntLeaveSleepMode() LDBIntLeaveSleepMode()

/*-------------------------------------------------------------------------
  Exported type

  struct  sCMPStructureName { ... };
  union   uCMPUnionName { ... };
  enum    eCMPEnumerationName { ... };
  typedef Expression tCMPTypeName;

  -------------------------------------------------------------------------*/
typedef union
{
#ifdef cLDBHarMicro78K0_F0536
    struct
    {
        // MK0H
        U8  UnUsedBit00:1;
        U8  BitINTST6:1;
        U8  BitINTST0:1;
        U8  BitINTTMH1:1;
        U8  BitINTTMH0:1;
        U8  UnUsedBit05:1;
        U8  UnUsedBit06:1;
        U8  UnUsedBit07:1;

        // MK1L
        U8  UnUsedBit08:1;
        U8  BitINTSR0:1;
        U8  BitINTWTI:1;
        U8  UnUsedBit11:1;
        U8  UnUsedBit12:1;
        U8  UnUsedBit13:1;
        U8  BitINTP6:1;
        U8  UnUsedBit15:1;
    } Bit;
    struct
    {
        U8 MK0H;
        U8 MK1L;
    } Reg;
#else
    struct
    {
U8  UnUsed:1;
U8  BitINTCE:1;
U8  BitINTCR:1;
U8  BitINTCT0:1;
U8  BitINTCT1:1;
    } Bit;

    U8 RegMK0H;
#endif
} tLDBIntStateGroup1;

/*-------------------------------------------------------------------------
  Exported data

  extern  tType   CMPVariableName;
  extern  tType*  pCMPVariableName; 
  -------------------------------------------------------------------------*/ 
extern MEM_FAST volatile tLDBIntStateGroup1 LDBIntGroup1;
extern MEM_FAST volatile U8             LDBIntLevel;

/*-------------------------------------------------------------------------
  Constant exported data

  extern const tType  CMPVariableName;
  -------------------------------------------------------------------------*/ 

/*-------------------------------------------------------------------------
  Exported functions

  extern tReturnType CMPFunctionName(tTypeArgument1 ArgumentName1, ... );
  -------------------------------------------------------------------------*/ 

void LDBIntInit(void);

// ----------------------------------------------
// Interrupt vector table declaration
// ----------------------------------------------

// INTx_ENABLE is defined in LDB_INTp.h

//#if defined(INTx_ENABLE)
//    //Interrupt is used in application
//    #pragma vector=INTx_vect
//    mLDBIntDeclareIsr(INTx);
//    #define cUnusedVectorINTx // empty definition
//#else
//    // Interrupt is assigned to common ISR to treat unexpected interrupts
//    #define cUnusedVectorINTx INTLVI_vect, // vector address plus comma
//#endif


#ifdef cLDBHarMicro78K0_F0536

#if defined(INTLVI_ENABLE)
    #pragma vector=INTLVI_vect
    mLDBIntDeclareIsr(INTLVI);
    #define cUnusedVectorINTLVI
#else
    #define cUnusedVectorINTLVI INTLVI_vect,    
#endif

#if defined(INTP0_ENABLE)
    #pragma vector=INTP0_vect
    mLDBIntDeclareIsr(INTP0);
    #define cUnusedVectorINTP0
#else
    #define cUnusedVectorINTP0 INTP0_vect,
#endif

#if defined(INTP1_ENABLE)
    #pragma vector=INTP1_vect
    mLDBIntDeclareIsr(INTP1);
    #define cUnusedVectorINTP1
#else
    #define cUnusedVectorINTP1 INTP1_vect,
#endif

#if defined(INTP2_ENABLE)
    #pragma vector=INTP2_vect
    mLDBIntDeclareIsr(INTP2);
    #define cUnusedVectorINTP2
#else
    #define cUnusedVectorINTP2 INTP2_vect,
#endif

#if defined(INTP3_ENABLE)
    #pragma vector=INTP3_vect
    mLDBIntDeclareIsr(INTP3);
    #define cUnusedVectorINTP3
#else
    #define cUnusedVectorINTP3 INTP3_vect,
#endif

#if defined(INTP4_ENABLE)
    #pragma vector=INTP4_vect
    mLDBIntDeclareIsr(INTP4);
    #define cUnusedVectorINTP4
#else
    #define cUnusedVectorINTP4 INTP4_vect,
#endif

#if defined(INTP5_ENABLE)
    #pragma vector=INTP5_vect
    mLDBIntDeclareIsr(INTP5);
    #define cUnusedVectorINTP5
#else
    #define cUnusedVectorINTP5 INTP5_vect,
#endif

#if defined(INTSRE6_ENABLE)
    #pragma vector=INTSRE6_vect
    mLDBIntDeclareIsr(INTSRE6);
    #define cUnusedVectorINTSRE6
#else
    #define cUnusedVectorINTSRE6 INTSRE6_vect,
#endif

#if defined(INTSR6_ENABLE)
    #pragma vector=INTSR6_vect
    mLDBIntDeclareIsr(INTSR6);
    #define cUnusedVectorINTSR6
#else
    #define cUnusedVectorINTSR6 INTSR6_vect,
#endif

#if defined(INTST6_ENABLE)
    #pragma vector=INTST6_vect
    mLDBIntDeclareIsr(INTST6);
    #define cUnusedVectorINTST6
#else
    #define cUnusedVectorINTST6 INTST6_vect,
#endif

#if (defined(INTCSI10_ENABLE) && defined(INTST0_ENABLE))
    #error "INTCSI10 and INTST0 are shared interrupts"
#elif defined(INTCSI10_ENABLE)
    #pragma vector=INTCSI10_vect
    mLDBIntDeclareIsr(INTCSI10);
    #define cUnusedVectorINTCSI10_INTST0
#elif defined(INTST0_ENABLE)
    #pragma vector=INTST0_vect
    mLDBIntDeclareIsr(INTST0);
    #define cUnusedVectorINTCSI10_INTST0
#else
    #define cUnusedVectorINTCSI10_INTST0 INTCSI10_vect,
#endif

#if defined(INTTMH1_ENABLE)
    #pragma vector=INTTMH1_vect
    mLDBIntDeclareIsr(INTTMH1);
    #define cUnusedVectorINTTMH1
#else
    #define cUnusedVectorINTTMH1 INTTMH1_vect,
#endif

#if defined(INTTMH0_ENABLE)
    #pragma vector=INTTMH0_vect
    mLDBIntDeclareIsr(INTTMH0);
    #define cUnusedVectorINTTMH0
#else
    #define cUnusedVectorINTTMH0 INTTMH0_vect,
#endif

#if defined(INTTM50_ENABLE)
    #pragma vector=INTTM50_vect
    mLDBIntDeclareIsr(INTTM50);
    #define cUnusedVectorINTTM50
#else
    #define cUnusedVectorINTTM50 INTTM50_vect,
#endif

#if defined(INTTM000_ENABLE)
    #pragma vector=INTTM000_vect
    mLDBIntDeclareIsr(INTTM000);
    #define cUnusedVectorINTTM000
#else
    #define cUnusedVectorINTTM000 INTTM000_vect,
#endif

#if defined(INTTM010_ENABLE)
    #pragma vector=INTTM010_vect
    mLDBIntDeclareIsr(INTTM010);
    #define cUnusedVectorINTTM010
#else
    #define cUnusedVectorINTTM010 INTTM010_vect,
#endif

#if defined(INTAD_ENABLE)
    #pragma vector=INTAD_vect
    mLDBIntDeclareIsr(INTAD);
    #define cUnusedVectorINTAD
#else
    #define cUnusedVectorINTAD INTAD_vect,
#endif

#if defined(INTSR0_ENABLE)
    #pragma vector=INTSR0_vect
    mLDBIntDeclareIsr(INTSR0);
    #define cUnusedVectorINTSR0
#else
    #define cUnusedVectorINTSR0 INTSR0_vect,
#endif

#if defined(INTWTI_ENABLE)
    #pragma vector=INTWTI_vect
    mLDBIntDeclareIsr(INTWTI);
    #define cUnusedVectorINTWTI
#else
    #define cUnusedVectorINTWTI INTWTI_vect,
#endif

#if defined(INTTM51_ENABLE)
    #pragma vector=INTTM51_vect
    mLDBIntDeclareIsr(INTTM51);
    #define cUnusedVectorINTTM51
#else
    #define cUnusedVectorINTTM51 INTTM51_vect,
#endif

#if defined(INTKR_ENABLE)
    #pragma vector=INTKR_vect
    mLDBIntDeclareIsr(INTKR);
    #define cUnusedVectorINTKR
#else
    #define cUnusedVectorINTKR INTKR_vect,
#endif

#if defined(INTWT_ENABLE)
    #pragma vector=INTWT_vect
    mLDBIntDeclareIsr(INTWT);
    #define cUnusedVectorINTWT
#else
    #define cUnusedVectorINTWT INTWT_vect,
#endif

#if defined(INTP6_ENABLE)
    #pragma vector=INTP6_vect
    mLDBIntDeclareIsr(INTP6);
    #define cUnusedVectorINTP6
#else
    #define cUnusedVectorINTP6 INTP6_vect,
#endif

#if defined(INTP7_ENABLE)
    #pragma vector=INTP7_vect
    mLDBIntDeclareIsr(INTP7);
    #define cUnusedVectorINTP7
#else
    #define cUnusedVectorINTP7 INTP7_vect,
#endif

#if (defined(INTIIC0_ENABLE) && defined(INTDMU_ENABLE))
    #error "INTIIC0 and INTDMU are shared interrupts"
#elif defined(INTIIC0_ENABLE)
    #pragma vector=INTIIC0_vect
    mLDBIntDeclareIsr(INTIIC0);
    #define cUnusedVectorINTIIC0_INTDMU
#elif defined(INTDMU_ENABLE)
    #pragma vector=INTDMU_vect
    mLDBIntDeclareIsr(INTDMU);
    #define cUnusedVectorINTIIC0_INTDMU
#else
    #define cUnusedVectorINTIIC0_INTDMU INTIIC0_vect,
#endif

#if defined(INTCSI11_ENABLE)
    #pragma vector=INTCSI11_vect
    mLDBIntDeclareIsr(INTCSI11);
    #define cUnusedVectorINTCSI11
#else
    #define cUnusedVectorINTCSI11 INTCSI11_vect,
#endif

#if defined(INTTM001_ENABLE)
    #pragma vector=INTTM001_vect
    mLDBIntDeclareIsr(INTTM001);
    #define cUnusedVectorINTTM001
#else
    #define cUnusedVectorINTTM001 INTTM001_vect,
#endif

#if defined(INTTM011_ENABLE)
    #pragma vector=INTTM011_vect
    mLDBIntDeclareIsr(INTTM011);
    #define cUnusedVectorINTTM011
#else
    #define cUnusedVectorINTTM011 INTTM011_vect,
#endif

#if defined(BRK_I_ENABLE)
    #pragma vector=BRK_I_vect
    mLDBIntDeclareIsr(BRK_I);
    #define cUnusedVectorBRK_I
#else
    #define cUnusedVectorBRK_I BRK_I_vect,
#endif


// Unexpected interrupt ISR declaration

// #pragma vector = vector_address1, vector_address2, ... vector_addressN
// mLDBIntDeclareIsr(UnexpectedInterrupt);

#pragma vector = \
    cUnusedVectorINTLVI     cUnusedVectorINTP0      cUnusedVectorINTP1 \
    cUnusedVectorINTP2      cUnusedVectorINTP3      cUnusedVectorINTP4 \
    cUnusedVectorINTP5      cUnusedVectorINTSRE6    cUnusedVectorINTSR6\
    cUnusedVectorINTST6     cUnusedVectorINTCSI10_INTST0  cUnusedVectorINTTMH1 \
    cUnusedVectorINTTMH0    cUnusedVectorINTTM50    cUnusedVectorINTTM000 \
    cUnusedVectorINTTM010   cUnusedVectorINTAD      cUnusedVectorINTSR0 \
    cUnusedVectorINTWTI     cUnusedVectorINTTM51    cUnusedVectorINTKR \
    cUnusedVectorINTWT      cUnusedVectorINTP6      cUnusedVectorINTP7 \
    cUnusedVectorINTIIC0_INTDMU cUnusedVectorINTCSI11 cUnusedVectorINTTM001 \
    cUnusedVectorINTTM011   cUnusedVectorBRK_I \
    INTNMI_vect /* NMI always unused for K0 */
mLDBIntDeclareIsr(UnexpectedInterrupt);
    
#endif // cLDBHarMicro78K0_F0536

#endif   /* I_LDB_INT_H */
