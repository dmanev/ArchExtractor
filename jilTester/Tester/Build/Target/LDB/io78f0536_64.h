/*-------------------------------------------------------------------------
 *      Declarations of SFR registers, interrupt and callt vector addresses
 *      for 78K0 microcontroller uPD78F0536_64.
 *
 *      This file can be used by both the 78K0
 *      Assembler, A78K, and the C/C++ compiler, ICC78K.
 *
 *      This header file is generated from the device file:
 *          DF053664.78K
 *          Copyright (C) NEC Corporation 2008
 *          Format version 2.31, File version 2.21
 *-------------------------------------------------------------------------*/

#ifndef __IO78F0536_64_H__
#define __IO78F0536_64_H__

#if !defined(__A78K__) && !defined(__ICC78K__)
  #error "IO78F0536_64.H file for use with 78K Series Assembler or Compiler only"
#endif

#if defined(__A78K__)
  #if __CORE__ != __78K0_BASIC__
    #if __CORE__ != __78K0__
      #error "IO78F0536_64.H file for use with A78K option -v0/-v1 only"
    #endif
  #endif
#endif
#if defined(__ICC78K__)
  #if __CORE__ != __78K0_BASIC__
    #if __CORE__ != __78K0__
      #error "IO78F0536_64.H file for use with ICC78K option -core 78k0_basic/78k0 only"
    #endif
  #endif
#endif

#ifdef __IAR_SYSTEMS_ICC__

#pragma language=extended
#pragma system_include

/*----------------------------------------------
 * SFR bits (default names)
 *--------------------------------------------*/

#ifndef __78K_BIT_STRUCTURE__
  #define __78K_BIT_STRUCTURE__
  typedef struct
  {
    unsigned char no0:1;
    unsigned char no1:1;
    unsigned char no2:1;
    unsigned char no3:1;
    unsigned char no4:1;
    unsigned char no5:1;
    unsigned char no6:1;
    unsigned char no7:1;
  } __BITS8;
#endif

/*----------------------------------------------
 *       SFR declarations
 *--------------------------------------------*/

extern __saddr __no_init volatile union { unsigned char P0; __BITS8 P0_bit; } @ 0xFF00;
extern __saddr __no_init volatile union { unsigned char P1; __BITS8 P1_bit; } @ 0xFF01;
extern __saddr __no_init volatile union { unsigned char P2; __BITS8 P2_bit; } @ 0xFF02;
extern __saddr __no_init volatile union { unsigned char P3; __BITS8 P3_bit; } @ 0xFF03;
extern __saddr __no_init volatile union { unsigned char P4; __BITS8 P4_bit; } @ 0xFF04;
extern __saddr __no_init volatile union { unsigned char P5; __BITS8 P5_bit; } @ 0xFF05;
extern __saddr __no_init volatile union { unsigned char P6; __BITS8 P6_bit; } @ 0xFF06;
extern __saddr __no_init volatile union { unsigned char P7; __BITS8 P7_bit; } @ 0xFF07;
extern __saddr __no_bit_access __no_init volatile union { unsigned short ADCR; struct { unsigned char :8; const unsigned char ADCRH; }; } @ 0xFF08;
extern __saddr __no_bit_access __no_init volatile const unsigned char RXB6 @ 0xFF0A;
extern __saddr __no_bit_access __no_init volatile unsigned char TXB6 @ 0xFF0B;
extern __saddr __no_init volatile union { unsigned char P12; __BITS8 P12_bit; } @ 0xFF0C;
extern __saddr __no_init volatile union { unsigned char P13; __BITS8 P13_bit; } @ 0xFF0D;
extern __saddr __no_init volatile union { unsigned char P14; __BITS8 P14_bit; } @ 0xFF0E;
extern __saddr __no_bit_access __no_init volatile const unsigned char SIO10 @ 0xFF0F;
extern __saddr __no_bit_access __no_init volatile const unsigned short TM00 @ 0xFF10;
extern __saddr __no_bit_access __no_init volatile unsigned short CR000 @ 0xFF12;
extern __saddr __no_bit_access __no_init volatile unsigned short CR010 @ 0xFF14;
extern __saddr __no_bit_access __no_init volatile const unsigned char TM50 @ 0xFF16;
extern __saddr __no_init volatile union { unsigned char CR50; __BITS8 CR50_bit; } @ 0xFF17;
extern __saddr __no_bit_access __no_init volatile unsigned char CMP00 @ 0xFF18;
extern __saddr __no_bit_access __no_init volatile unsigned char CMP10 @ 0xFF19;
extern __saddr __no_bit_access __no_init volatile unsigned char CMP01 @ 0xFF1A;
extern __saddr __no_bit_access __no_init volatile unsigned char CMP11 @ 0xFF1B;
extern __saddr __no_bit_access __no_init volatile const unsigned char TM51 @ 0xFF1F;
extern __sfr __no_init volatile union { unsigned char PM0; __BITS8 PM0_bit; } @ 0xFF20;
extern __sfr __no_init volatile union { unsigned char PM1; __BITS8 PM1_bit; } @ 0xFF21;
extern __sfr __no_init volatile union { unsigned char PM2; __BITS8 PM2_bit; } @ 0xFF22;
extern __sfr __no_init volatile union { unsigned char PM3; __BITS8 PM3_bit; } @ 0xFF23;
extern __sfr __no_init volatile union { unsigned char PM4; __BITS8 PM4_bit; } @ 0xFF24;
extern __sfr __no_init volatile union { unsigned char PM5; __BITS8 PM5_bit; } @ 0xFF25;
extern __sfr __no_init volatile union { unsigned char PM6; __BITS8 PM6_bit; } @ 0xFF26;
extern __sfr __no_init volatile union { unsigned char PM7; __BITS8 PM7_bit; } @ 0xFF27;
extern __sfr __no_init volatile union { unsigned char ADM; __BITS8 ADM_bit; } @ 0xFF28;
extern __sfr __no_init volatile union { unsigned char ADS; __BITS8 ADS_bit; } @ 0xFF29;
extern __sfr __no_init volatile union { unsigned char PM12; __BITS8 PM12_bit; } @ 0xFF2C;
extern __sfr __no_init volatile union { unsigned char PM14; __BITS8 PM14_bit; } @ 0xFF2E;
extern __sfr __no_init volatile union { unsigned char ADPC; __BITS8 ADPC_bit; } @ 0xFF2F;
extern __sfr __no_init volatile union { unsigned char PU0; __BITS8 PU0_bit; } @ 0xFF30;
extern __sfr __no_init volatile union { unsigned char PU1; __BITS8 PU1_bit; } @ 0xFF31;
extern __sfr __no_init volatile union { unsigned char PU3; __BITS8 PU3_bit; } @ 0xFF33;
extern __sfr __no_init volatile union { unsigned char PU4; __BITS8 PU4_bit; } @ 0xFF34;
extern __sfr __no_init volatile union { unsigned char PU5; __BITS8 PU5_bit; } @ 0xFF35;
extern __sfr __no_init volatile union { unsigned char PU7; __BITS8 PU7_bit; } @ 0xFF37;
extern __sfr __no_init volatile union { unsigned char PU12; __BITS8 PU12_bit; } @ 0xFF3C;
extern __sfr __no_init volatile union { unsigned char PU14; __BITS8 PU14_bit; } @ 0xFF3E;
extern __sfr __no_init volatile union { unsigned char CKS; __BITS8 CKS_bit; } @ 0xFF40;
extern __sfr __no_init volatile union { unsigned char CR51; __BITS8 CR51_bit; } @ 0xFF41;
extern __sfr __no_init volatile union { unsigned char TMC51; __BITS8 TMC51_bit; } @ 0xFF43;
extern __sfr __no_init volatile union { unsigned char EGP; __BITS8 EGP_bit; } @ 0xFF48;
extern __sfr __no_init volatile union { unsigned char EGN; __BITS8 EGN_bit; } @ 0xFF49;
extern __sfr __no_bit_access __no_init volatile const unsigned char SIO11 @ 0xFF4A;
extern __sfr __no_bit_access __no_init volatile unsigned char SOTB11 @ 0xFF4C;
extern __sfr __no_init volatile union { unsigned char ISC; __BITS8 ISC_bit; } @ 0xFF4F;
extern __sfr __no_init volatile union { unsigned char ASIM6; __BITS8 ASIM6_bit; } @ 0xFF50;
extern __sfr __no_bit_access __no_init volatile const unsigned char ASIS6 @ 0xFF53;
extern __sfr __no_bit_access __no_init volatile const unsigned char ASIF6 @ 0xFF55;
extern __sfr __no_bit_access __no_init volatile unsigned char CKSR6 @ 0xFF56;
extern __sfr __no_bit_access __no_init volatile unsigned char BRGC6 @ 0xFF57;
extern __sfr __no_init volatile union { unsigned char ASICL6; __BITS8 ASICL6_bit; } @ 0xFF58;
extern __sfr __no_bit_access __no_init volatile const union { unsigned short SDR0; struct { unsigned char SDR0L; unsigned char SDR0H; }; } @ 0xFF60;
extern __sfr __no_bit_access __no_init volatile union { unsigned short MDA0L; struct { unsigned char MDA0LL; unsigned char MDA0LH; }; } @ 0xFF62;
extern __sfr __no_bit_access __no_init volatile union { unsigned short MDA0H; struct { unsigned char MDA0HL; unsigned char MDA0HH; }; } @ 0xFF64;
extern __sfr __no_bit_access __no_init volatile union { unsigned short MDB0; struct { unsigned char MDB0L; unsigned char MDB0H; }; } @ 0xFF66;
extern __sfr __no_init volatile union { unsigned char DMUC0; __BITS8 DMUC0_bit; } @ 0xFF68;
extern __sfr __no_init volatile union { unsigned char TMHMD0; __BITS8 TMHMD0_bit; } @ 0xFF69;
extern __sfr __no_init volatile union { unsigned char TCL50; __BITS8 TCL50_bit; } @ 0xFF6A;
extern __sfr __no_init volatile union { unsigned char TMC50; __BITS8 TMC50_bit; } @ 0xFF6B;
extern __sfr __no_init volatile union { unsigned char TMHMD1; __BITS8 TMHMD1_bit; } @ 0xFF6C;
extern __sfr __no_init volatile union { unsigned char TMCYC1; __BITS8 TMCYC1_bit; } @ 0xFF6D;
extern __sfr __no_init volatile union { unsigned char KRM; __BITS8 KRM_bit; } @ 0xFF6E;
extern __sfr __no_init volatile union { unsigned char WTM; __BITS8 WTM_bit; } @ 0xFF6F;
extern __sfr __no_init volatile union { unsigned char ASIM0; __BITS8 ASIM0_bit; } @ 0xFF70;
extern __sfr __no_bit_access __no_init volatile unsigned char BRGC0 @ 0xFF71;
extern __sfr __no_bit_access __no_init volatile const unsigned char RXB0 @ 0xFF72;
extern __sfr __no_bit_access __no_init volatile const unsigned char ASIS0 @ 0xFF73;
extern __sfr __no_bit_access __no_init volatile unsigned char TXS0 @ 0xFF74;
extern __sfr __no_init volatile union { unsigned char CSIM10; __BITS8 CSIM10_bit; } @ 0xFF80;
extern __sfr __no_init volatile union { unsigned char CSIC10; __BITS8 CSIC10_bit; } @ 0xFF81;
extern __sfr __no_bit_access __no_init volatile unsigned char SOTB10 @ 0xFF84;
extern __sfr __no_init volatile union { unsigned char CSIM11; __BITS8 CSIM11_bit; } @ 0xFF88;
extern __sfr __no_init volatile union { unsigned char CSIC11; __BITS8 CSIC11_bit; } @ 0xFF89;
extern __sfr __no_init volatile union { unsigned char TCL51; __BITS8 TCL51_bit; } @ 0xFF8C;
extern __sfr __no_bit_access __no_init volatile unsigned char WDTE @ 0xFF99;
extern __sfr __no_init volatile union { unsigned char OSCCTL; __BITS8 OSCCTL_bit; } @ 0xFF9F;
extern __sfr __no_init volatile union { unsigned char RCM; __BITS8 RCM_bit; } @ 0xFFA0;
extern __sfr __no_init volatile union { unsigned char MCM; __BITS8 MCM_bit; } @ 0xFFA1;
extern __sfr __no_init volatile union { unsigned char MOC; __BITS8 MOC_bit; } @ 0xFFA2;
extern __sfr __no_init volatile const union { unsigned char OSTC; __BITS8 OSTC_bit; } @ 0xFFA3;
extern __sfr __no_init volatile union { unsigned char OSTS; __BITS8 OSTS_bit; } @ 0xFFA4;
extern __sfr __no_bit_access __no_init volatile unsigned char IIC0 @ 0xFFA5;
extern __sfr __no_init volatile union { unsigned char IICC0; __BITS8 IICC0_bit; } @ 0xFFA6;
extern __sfr __no_bit_access __no_init volatile unsigned char SVA0 @ 0xFFA7;
extern __sfr __no_init volatile union { unsigned char IICCL0; __BITS8 IICCL0_bit; } @ 0xFFA8;
extern __sfr __no_init volatile union { unsigned char IICX0; __BITS8 IICX0_bit; } @ 0xFFA9;
extern __sfr __no_init volatile const union { unsigned char IICS0; __BITS8 IICS0_bit; } @ 0xFFAA;
extern __sfr __no_init volatile union { unsigned char IICF0; __BITS8 IICF0_bit; } @ 0xFFAB;
extern __sfr __no_bit_access __no_init volatile const unsigned char RESF @ 0xFFAC;
extern __sfr __no_bit_access __no_init volatile const unsigned short TM01 @ 0xFFB0;
extern __sfr __no_bit_access __no_init volatile unsigned short CR001 @ 0xFFB2;
extern __sfr __no_bit_access __no_init volatile unsigned short CR011 @ 0xFFB4;
extern __sfr __no_init volatile union { unsigned char TMC01; __BITS8 TMC01_bit; } @ 0xFFB6;
extern __sfr __no_init volatile union { unsigned char PRM01; __BITS8 PRM01_bit; } @ 0xFFB7;
extern __sfr __no_init volatile union { unsigned char CRC01; __BITS8 CRC01_bit; } @ 0xFFB8;
extern __sfr __no_init volatile union { unsigned char TOC01; __BITS8 TOC01_bit; } @ 0xFFB9;
extern __sfr __no_init volatile union { unsigned char TMC00; __BITS8 TMC00_bit; } @ 0xFFBA;
extern __sfr __no_init volatile union { unsigned char PRM00; __BITS8 PRM00_bit; } @ 0xFFBB;
extern __sfr __no_init volatile union { unsigned char CRC00; __BITS8 CRC00_bit; } @ 0xFFBC;
extern __sfr __no_init volatile union { unsigned char TOC00; __BITS8 TOC00_bit; } @ 0xFFBD;
extern __sfr __no_init volatile union { unsigned char LVIM; __BITS8 LVIM_bit; } @ 0xFFBE;
extern __sfr __no_init volatile union { unsigned char LVIS; __BITS8 LVIS_bit; } @ 0xFFBF;
extern __sfr __no_bit_access __no_init volatile unsigned char PFCMD @ 0xFFC0;
extern __sfr __no_init volatile union { unsigned char PFS; __BITS8 PFS_bit; } @ 0xFFC2;
extern __sfr __no_init volatile union { unsigned char FLPMC; __BITS8 FLPMC_bit; } @ 0xFFC4;
extern __sfr __no_init volatile union { unsigned short IF0; struct { union { unsigned char IF0L; __BITS8 IF0L_bit; }; union { unsigned char IF0H; __BITS8 IF0H_bit; }; }; } @ 0xFFE0;
extern __sfr __no_init volatile union { unsigned short IF1; struct { union { unsigned char IF1L; __BITS8 IF1L_bit; }; union { unsigned char IF1H; __BITS8 IF1H_bit; }; }; } @ 0xFFE2;
extern __sfr __no_init volatile union { unsigned short MK0; struct { union { unsigned char MK0L; __BITS8 MK0L_bit; }; union { unsigned char MK0H; __BITS8 MK0H_bit; }; }; } @ 0xFFE4;
extern __sfr __no_init volatile union { unsigned short MK1; struct { union { unsigned char MK1L; __BITS8 MK1L_bit; }; union { unsigned char MK1H; __BITS8 MK1H_bit; }; }; } @ 0xFFE6;
extern __sfr __no_init volatile union { unsigned short PR0; struct { union { unsigned char PR0L; __BITS8 PR0L_bit; }; union { unsigned char PR0H; __BITS8 PR0H_bit; }; }; } @ 0xFFE8;
extern __sfr __no_init volatile union { unsigned short PR1; struct { union { unsigned char PR1L; __BITS8 PR1L_bit; }; union { unsigned char PR1H; __BITS8 PR1H_bit; }; }; } @ 0xFFEA;
extern __sfr __no_bit_access __no_init volatile unsigned char IMS @ 0xFFF0;
extern __sfr __no_bit_access __no_init volatile unsigned char BANK @ 0xFFF3;
extern __sfr __no_bit_access __no_init volatile unsigned char IXS @ 0xFFF4;
extern __sfr __no_init volatile union { unsigned char PCC; __BITS8 PCC_bit; } @ 0xFFFB;
extern __sfr __no_bit_access __no_init volatile unsigned char R8MTRM @ 0xFFFE;

/*----------------------------------------------
 *       SFR bit declarations
 *--------------------------------------------*/

#define ADCE              ADM_bit.no0
#define ADCS              ADM_bit.no7

#define CLOE              CKS_bit.no4
#define BZOE              CKS_bit.no7

#define TOE51             TMC51_bit.no0
#define LVR51             TMC51_bit.no2
#define LVS51             TMC51_bit.no3
#define TCE51             TMC51_bit.no7

#define RXE6              ASIM6_bit.no5
#define TXE6              ASIM6_bit.no6
#define POWER6            ASIM6_bit.no7

#define SBRT6             ASICL6_bit.no6
#define SBRF6             ASICL6_bit.no7

#define DMUE              DMUC0_bit.no7

#define TOEN0             TMHMD0_bit.no0
#define TOLEV0            TMHMD0_bit.no1
#define TMHE0             TMHMD0_bit.no7

#define TOE50             TMC50_bit.no0
#define LVR50             TMC50_bit.no2
#define LVS50             TMC50_bit.no3
#define TCE50             TMC50_bit.no7

#define TOEN1             TMHMD1_bit.no0
#define TOLEV1            TMHMD1_bit.no1
#define TMHE1             TMHMD1_bit.no7

#define NRZ1              TMCYC1_bit.no0

#define WTM0              WTM_bit.no0
#define WTM1              WTM_bit.no1

#define RXE0              ASIM0_bit.no5
#define TXE0              ASIM0_bit.no6
#define POWER0            ASIM0_bit.no7

#define CSIE10            CSIM10_bit.no7

#define CSIE11            CSIM11_bit.no7

#define AMPH              OSCCTL_bit.no0
#define OSCSELS           OSCCTL_bit.no4
#define EXCLKS            OSCCTL_bit.no5
#define OSCSEL            OSCCTL_bit.no6
#define EXCLK             OSCCTL_bit.no7

#define RSTOP             RCM_bit.no0
#define LSRSTOP           RCM_bit.no1
#define RSTS              RCM_bit.no7

#define MCM0              MCM_bit.no0
#define MCS               MCM_bit.no1
#define XSEL              MCM_bit.no2

#define MSTOP             MOC_bit.no7

#define SPT0              IICC0_bit.no0
#define STT0              IICC0_bit.no1
#define ACKE0             IICC0_bit.no2
#define WTIM0             IICC0_bit.no3
#define SPIE0             IICC0_bit.no4
#define WREL0             IICC0_bit.no5
#define LREL0             IICC0_bit.no6
#define IICE0             IICC0_bit.no7

#define DFC0              IICCL0_bit.no2
#define SMC0              IICCL0_bit.no3
#define DAD0              IICCL0_bit.no4
#define CLD0              IICCL0_bit.no5

#define CLX0              IICX0_bit.no0

#define SPD0              IICS0_bit.no0
#define STD0              IICS0_bit.no1
#define ACKD0             IICS0_bit.no2
#define TRC0              IICS0_bit.no3
#define COI0              IICS0_bit.no4
#define EXC0              IICS0_bit.no5
#define ALD0              IICS0_bit.no6
#define MSTS0             IICS0_bit.no7

#define IICRSV            IICF0_bit.no0
#define STCEN             IICF0_bit.no1
#define IICBSY            IICF0_bit.no6
#define STCF              IICF0_bit.no7

#define OVF01             TMC01_bit.no0

#define TOE01             TOC01_bit.no0
#define LVR01             TOC01_bit.no2
#define LVS01             TOC01_bit.no3
#define OSPE01            TOC01_bit.no5
#define OSPT01            TOC01_bit.no6

#define OVF00             TMC00_bit.no0

#define TOE00             TOC00_bit.no0
#define LVR00             TOC00_bit.no2
#define LVS00             TOC00_bit.no3
#define OSPE00            TOC00_bit.no5
#define OSPT00            TOC00_bit.no6

#define LVIF              LVIM_bit.no0
#define LVIMD             LVIM_bit.no1
#define LVISEL            LVIM_bit.no2
#define LVION             LVIM_bit.no7

#define FPRERR            PFS_bit.no0

#define FLSPM0            FLPMC_bit.no0
#define FWEPR             FLPMC_bit.no2
#define FWEDIS            FLPMC_bit.no3

#define LVIIF             IF0L_bit.no0
#define PIF0              IF0L_bit.no1
#define PIF1              IF0L_bit.no2
#define PIF2              IF0L_bit.no3
#define PIF3              IF0L_bit.no4
#define PIF4              IF0L_bit.no5
#define PIF5              IF0L_bit.no6
#define SREIF6            IF0L_bit.no7

#define SRIF6             IF0H_bit.no0
#define STIF6             IF0H_bit.no1
#define CSIIF10           IF0H_bit.no2
#define DUALIF0           IF0H_bit.no2
#define STIF0             IF0H_bit.no2
#define TMIFH1            IF0H_bit.no3
#define TMIFH0            IF0H_bit.no4
#define TMIF50            IF0H_bit.no5
#define TMIF000           IF0H_bit.no6
#define TMIF010           IF0H_bit.no7

#define ADIF              IF1L_bit.no0
#define SRIF0             IF1L_bit.no1
#define WTIIF             IF1L_bit.no2
#define TMIF51            IF1L_bit.no3
#define KRIF              IF1L_bit.no4
#define WTIF              IF1L_bit.no5
#define PIF6              IF1L_bit.no6
#define PIF7              IF1L_bit.no7

#define DMUIF             IF1H_bit.no0
#define IICIF0            IF1H_bit.no0
#define CSIIF11           IF1H_bit.no1
#define TMIF001           IF1H_bit.no2
#define TMIF011           IF1H_bit.no3

#define LVIMK             MK0L_bit.no0
#define PMK0              MK0L_bit.no1
#define PMK1              MK0L_bit.no2
#define PMK2              MK0L_bit.no3
#define PMK3              MK0L_bit.no4
#define PMK4              MK0L_bit.no5
#define PMK5              MK0L_bit.no6
#define SREMK6            MK0L_bit.no7

#define SRMK6             MK0H_bit.no0
#define STMK6             MK0H_bit.no1
#define CSIMK10           MK0H_bit.no2
#define DUALMK0           MK0H_bit.no2
#define STMK0             MK0H_bit.no2
#define TMMKH1            MK0H_bit.no3
#define TMMKH0            MK0H_bit.no4
#define TMMK50            MK0H_bit.no5
#define TMMK000           MK0H_bit.no6
#define TMMK010           MK0H_bit.no7

#define ADMK              MK1L_bit.no0
#define SRMK0             MK1L_bit.no1
#define WTIMK             MK1L_bit.no2
#define TMMK51            MK1L_bit.no3
#define KRMK              MK1L_bit.no4
#define WTMK              MK1L_bit.no5
#define PMK6              MK1L_bit.no6
#define PMK7              MK1L_bit.no7

#define DMUMK             MK1H_bit.no0
#define IICMK0            MK1H_bit.no0
#define CSIMK11           MK1H_bit.no1
#define TMMK001           MK1H_bit.no2
#define TMMK011           MK1H_bit.no3

#define LVIPR             PR0L_bit.no0
#define PPR0              PR0L_bit.no1
#define PPR1              PR0L_bit.no2
#define PPR2              PR0L_bit.no3
#define PPR3              PR0L_bit.no4
#define PPR4              PR0L_bit.no5
#define PPR5              PR0L_bit.no6
#define SREPR6            PR0L_bit.no7

#define SRPR6             PR0H_bit.no0
#define STPR6             PR0H_bit.no1
#define CSIPR10           PR0H_bit.no2
#define DUALPR0           PR0H_bit.no2
#define STPR0             PR0H_bit.no2
#define TMPRH1            PR0H_bit.no3
#define TMPRH0            PR0H_bit.no4
#define TMPR50            PR0H_bit.no5
#define TMPR000           PR0H_bit.no6
#define TMPR010           PR0H_bit.no7

#define ADPR              PR1L_bit.no0
#define SRPR0             PR1L_bit.no1
#define WTIPR             PR1L_bit.no2
#define TMPR51            PR1L_bit.no3
#define KRPR              PR1L_bit.no4
#define WTPR              PR1L_bit.no5
#define PPR6              PR1L_bit.no6
#define PPR7              PR1L_bit.no7

#define DMUPR             PR1H_bit.no0
#define IICPR0            PR1H_bit.no0
#define CSIPR11           PR1H_bit.no1
#define TMPR001           PR1H_bit.no2
#define TMPR011           PR1H_bit.no3

#define CSS               PCC_bit.no4
#define CLS               PCC_bit.no5
#define XTSTART           PCC_bit.no6

#pragma language=default

#endif /* __IAR_SYSTEMS_ICC__ */

#ifdef __IAR_SYSTEMS_ASM__

/*----------------------------------------------
 *       SFR declarations
 *--------------------------------------------*/

P0         DEFINE  0xFF00
P1         DEFINE  0xFF01
P2         DEFINE  0xFF02
P3         DEFINE  0xFF03
P4         DEFINE  0xFF04
P5         DEFINE  0xFF05
P6         DEFINE  0xFF06
P7         DEFINE  0xFF07
ADCR       DEFINE  0xFF08
ADCRH      DEFINE  0xFF09
RXB6       DEFINE  0xFF0A
TXB6       DEFINE  0xFF0B
P12        DEFINE  0xFF0C
P13        DEFINE  0xFF0D
P14        DEFINE  0xFF0E
SIO10      DEFINE  0xFF0F
TM00       DEFINE  0xFF10
CR000      DEFINE  0xFF12
CR010      DEFINE  0xFF14
TM50       DEFINE  0xFF16
CR50       DEFINE  0xFF17
CMP00      DEFINE  0xFF18
CMP10      DEFINE  0xFF19
CMP01      DEFINE  0xFF1A
CMP11      DEFINE  0xFF1B
TM51       DEFINE  0xFF1F
PM0        DEFINE  0xFF20
PM1        DEFINE  0xFF21
PM2        DEFINE  0xFF22
PM3        DEFINE  0xFF23
PM4        DEFINE  0xFF24
PM5        DEFINE  0xFF25
PM6        DEFINE  0xFF26
PM7        DEFINE  0xFF27
ADM        DEFINE  0xFF28
ADS        DEFINE  0xFF29
PM12       DEFINE  0xFF2C
PM14       DEFINE  0xFF2E
ADPC       DEFINE  0xFF2F
PU0        DEFINE  0xFF30
PU1        DEFINE  0xFF31
PU3        DEFINE  0xFF33
PU4        DEFINE  0xFF34
PU5        DEFINE  0xFF35
PU7        DEFINE  0xFF37
PU12       DEFINE  0xFF3C
PU14       DEFINE  0xFF3E
CKS        DEFINE  0xFF40
CR51       DEFINE  0xFF41
TMC51      DEFINE  0xFF43
EGP        DEFINE  0xFF48
EGN        DEFINE  0xFF49
SIO11      DEFINE  0xFF4A
SOTB11     DEFINE  0xFF4C
ISC        DEFINE  0xFF4F
ASIM6      DEFINE  0xFF50
ASIS6      DEFINE  0xFF53
ASIF6      DEFINE  0xFF55
CKSR6      DEFINE  0xFF56
BRGC6      DEFINE  0xFF57
ASICL6     DEFINE  0xFF58
SDR0       DEFINE  0xFF60
SDR0L      DEFINE  0xFF60
SDR0H      DEFINE  0xFF61
MDA0L      DEFINE  0xFF62
MDA0LL     DEFINE  0xFF62
MDA0LH     DEFINE  0xFF63
MDA0H      DEFINE  0xFF64
MDA0HL     DEFINE  0xFF64
MDA0HH     DEFINE  0xFF65
MDB0       DEFINE  0xFF66
MDB0L      DEFINE  0xFF66
MDB0H      DEFINE  0xFF67
DMUC0      DEFINE  0xFF68
TMHMD0     DEFINE  0xFF69
TCL50      DEFINE  0xFF6A
TMC50      DEFINE  0xFF6B
TMHMD1     DEFINE  0xFF6C
TMCYC1     DEFINE  0xFF6D
KRM        DEFINE  0xFF6E
WTM        DEFINE  0xFF6F
ASIM0      DEFINE  0xFF70
BRGC0      DEFINE  0xFF71
RXB0       DEFINE  0xFF72
ASIS0      DEFINE  0xFF73
TXS0       DEFINE  0xFF74
CSIM10     DEFINE  0xFF80
CSIC10     DEFINE  0xFF81
SOTB10     DEFINE  0xFF84
CSIM11     DEFINE  0xFF88
CSIC11     DEFINE  0xFF89
TCL51      DEFINE  0xFF8C
WDTE       DEFINE  0xFF99
OSCCTL     DEFINE  0xFF9F
RCM        DEFINE  0xFFA0
MCM        DEFINE  0xFFA1
MOC        DEFINE  0xFFA2
OSTC       DEFINE  0xFFA3
OSTS       DEFINE  0xFFA4
IIC0       DEFINE  0xFFA5
IICC0      DEFINE  0xFFA6
SVA0       DEFINE  0xFFA7
IICCL0     DEFINE  0xFFA8
IICX0      DEFINE  0xFFA9
IICS0      DEFINE  0xFFAA
IICF0      DEFINE  0xFFAB
RESF       DEFINE  0xFFAC
TM01       DEFINE  0xFFB0
CR001      DEFINE  0xFFB2
CR011      DEFINE  0xFFB4
TMC01      DEFINE  0xFFB6
PRM01      DEFINE  0xFFB7
CRC01      DEFINE  0xFFB8
TOC01      DEFINE  0xFFB9
TMC00      DEFINE  0xFFBA
PRM00      DEFINE  0xFFBB
CRC00      DEFINE  0xFFBC
TOC00      DEFINE  0xFFBD
LVIM       DEFINE  0xFFBE
LVIS       DEFINE  0xFFBF
PFCMD      DEFINE  0xFFC0
PFS        DEFINE  0xFFC2
FLPMC      DEFINE  0xFFC4
IF0        DEFINE  0xFFE0
IF0L       DEFINE  0xFFE0
IF0H       DEFINE  0xFFE1
IF1        DEFINE  0xFFE2
IF1L       DEFINE  0xFFE2
IF1H       DEFINE  0xFFE3
MK0        DEFINE  0xFFE4
MK0L       DEFINE  0xFFE4
MK0H       DEFINE  0xFFE5
MK1        DEFINE  0xFFE6
MK1L       DEFINE  0xFFE6
MK1H       DEFINE  0xFFE7
PR0        DEFINE  0xFFE8
PR0L       DEFINE  0xFFE8
PR0H       DEFINE  0xFFE9
PR1        DEFINE  0xFFEA
PR1L       DEFINE  0xFFEA
PR1H       DEFINE  0xFFEB
IMS        DEFINE  0xFFF0
BANK       DEFINE  0xFFF3
IXS        DEFINE  0xFFF4
PCC        DEFINE  0xFFFB
R8MTRM     DEFINE  0xFFFE

#endif /* __IAR_SYSTEMS_ASM__ */

/*----------------------------------------------
 *       Interrupt vector addresses
 *--------------------------------------------*/

#define RST_vect                 (0x00)
#define INTCK2_vect              (0x02)
#define INTNMI_vect              (0x02)
#define INTLVI_vect              (0x04)
#define INTP0_vect               (0x06)
#define INTP1_vect               (0x08)
#define INTP2_vect               (0x0A)
#define INTP3_vect               (0x0C)
#define INTP4_vect               (0x0E)
#define INTP5_vect               (0x10)
#define INTSRE6_vect             (0x12)
#define INTSR6_vect              (0x14)
#define INTST6_vect              (0x16)
#define INTCSI10_vect            (0x18)
#define INTST0_vect              (0x18)
#define INTTMH1_vect             (0x1A)
#define INTTMH0_vect             (0x1C)
#define INTTM50_vect             (0x1E)
#define INTTM000_vect            (0x20)
#define INTTM010_vect            (0x22)
#define INTAD_vect               (0x24)
#define INTSR0_vect              (0x26)
#define INTWTI_vect              (0x28)
#define INTTM51_vect             (0x2A)
#define INTKR_vect               (0x2C)
#define INTWT_vect               (0x2E)
#define INTP6_vect               (0x30)
#define INTP7_vect               (0x32)
#define INTDMU_vect              (0x34)
#define INTIIC0_vect             (0x34)
#define INTCSI11_vect            (0x36)
#define INTTM001_vect            (0x38)
#define INTTM011_vect            (0x3A)
#define BRK_I_vect               (0x3E)

/*----------------------------------------------
 *       Callt vector addresses
 *--------------------------------------------*/

#define CALLT_40_vect            (0x40)
#define CALLT_42_vect            (0x42)
#define CALLT_44_vect            (0x44)
#define CALLT_46_vect            (0x46)
#define CALLT_48_vect            (0x48)
#define CALLT_4A_vect            (0x4A)
#define CALLT_4C_vect            (0x4C)
#define CALLT_4E_vect            (0x4E)
#define CALLT_50_vect            (0x50)
#define CALLT_52_vect            (0x52)
#define CALLT_54_vect            (0x54)
#define CALLT_56_vect            (0x56)
#define CALLT_58_vect            (0x58)
#define CALLT_5A_vect            (0x5A)
#define CALLT_5C_vect            (0x5C)
#define CALLT_5E_vect            (0x5E)
#define CALLT_60_vect            (0x60)
#define CALLT_62_vect            (0x62)
#define CALLT_64_vect            (0x64)
#define CALLT_66_vect            (0x66)
#define CALLT_68_vect            (0x68)
#define CALLT_6A_vect            (0x6A)
#define CALLT_6C_vect            (0x6C)
#define CALLT_6E_vect            (0x6E)
#define CALLT_70_vect            (0x70)
#define CALLT_72_vect            (0x72)
#define CALLT_74_vect            (0x74)
#define CALLT_76_vect            (0x76)
#define CALLT_78_vect            (0x78)
#define CALLT_7A_vect            (0x7A)
#define CALLT_7C_vect            (0x7C)
#define CALLT_7E_vect            (0x7E)

#endif /* __IO78F0536_64_H__ */
