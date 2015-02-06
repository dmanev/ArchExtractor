#ifndef _QAC_
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
// Component:    DAT_PAN
// -----------------------------------------------------------------------------
// $Date:   Feb 13 2010 09:11:08  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_PAN/DAT_PAN.H-arc  $
// $Revision:   1.7  $
// -----------------------------------------------------------------------------
/* $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_PAN/DAT_PAN.H-arc  $
 * 
 *    Rev 1.7   Feb 13 2010 09:11:08   adzhelp
 * Cm007063: Implementation of flashers' SC VBAT / open load calculation
 * 
 *    Rev 1.6   Feb 02 2010 16:50:42   adzhelp
 * Cm006590, Cm006698: Implementation of undervoltage condition checking
 * 
 *    Rev 1.5   Jan 15 2010 10:37:02   adzhelp
 * Cm006709: Coefficients for flasher current updated
 * 
 *    Rev 1.4   Dec 14 2009 11:40:36   adzhelp
 * Cm005566: Implementation of full HW protection and overvoltage protection
 * 
 *    Rev 1.3   Nov 20 2009 15:48:38   adzhelp
 * Cm005566: UT and QAC corrections
 * 
 *    Rev 1.2   Nov 04 2009 16:22:14   adzhelp
 * Cm005566: Implementation of HW Protection
 * 
 *    Rev 1.1   Apr 22 2009 09:21:18   adzhelp
 * Cm003619: Implementation of calculated analog parameters
 * 
 *    Rev 1.0   20 Nov 2008 15:12:10   ailievb
 * Initial revision.
*/ 
//******************************************************************************
#endif

#ifndef _dat_pan_H_
#define _dat_pan_H_

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//
// #include <system_file_name.h>
// #include "project_file_name.h"
//------------------------------------------------------------------------------

#include "deftypes.h"
#include "dat_ana.h"
#include "dat_panx.h"

//------------------------------------------------------------------------------
// Data prefix for constant & data: see coding guideline
//
//------------------------------------------------------------------------------
// Constant data
//
// #define cu16LAYCmpConstantName   ((U16) ConstantValueUL)
//------------------------------------------------------------------------------
// Short circuit thresholds
#define cDATPanDIAG_DRIVER_ULQ_SCBatThresholdMV                970UL
#define cDATPanDIAG_DRIVER_KLAXON_DualSCBatThresholdMV         900UL
#define cDATPanDIAG_DRIVER_KLAXON_SingleSCBatThresholdMV       450UL
#define cDATPanDIAG_DRIVER_KLAXON_SCGndThresholdMV             48UL
#define cDATPanDIAG_DRIVER_KLAXONK_LineTestSCBatThresholdMV    120UL
#define cDATPanDIAG_DRIVER_KLAXONK_LineCommandSCBatThresholdMV 60UL
#define cDATPanDIAG_DRIVER_HIGH_SIDE_SCGndThresholdMV          4800UL
#define cDATPanDIAG_FLASHER_SCGndThresholdMV                   4800UL

// ADC parameters
#define cDATPanMaxAdcValue      1023UL
#define cDATPanVRefVoltageInMV  5000UL

//------------------------------------------------------------------------------
// Exported type
//
// typedef Expression tLAYCmpTypeName;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported data
//
// extern  tType   u8LAYCmpVariableName;
// extern  tType*  ps32LAYCmpVariableName; 
//------------------------------------------------------------------------------
extern BOOL bDATPanOverVoltageIsDetected;
extern BOOL bDATPanUnderVoltageIsDetected;
extern BOOL bDATPanFlasherBulbFailure;
extern BOOL bDATPanFlasherSCBatOrOpenLoad;

//------------------------------------------------------------------------------
// Constant exported data
//
// extern const tType  s8LAYCmpVariableName;
//------------------------------------------------------------------------------

#ifdef cLIBStkScc2_Used
extern const U8 DATPanInitialization[cDATPanSizeAnaGeneratorMessage];
#else
extern const U8 DATPanInitialization[cDATPanBufferSizeEntree];
#endif

//------------------------------------------------------------------------------
// Exported Macros
//
// #define LAYCmpMacroName(...)   (MacroDefinition)
//------------------------------------------------------------------------------
#define mDATPanReadU8Bit(Frame, Byte, Bit, BitSize, TypeTraitement) \
                                    /*//QACJ 3443: adzhelp: Standard STK macro */\
                                    mDATPanReadU8Bit##TypeTraitement(Byte)

#define mDATPanReadU8BitImmediate(Channel)  mDATAnaGetValue(Channel)

#define mDATPanReadU8BitDelayed(Channel)    mDATAnaGetFilteredValue(Channel)

#define mDATPanReadU8BitDefault(Channel)    mDATAnaGetFilteredValue(Channel)


#define mDATPanReadU16Bit(Trame, Word, Bit, BitSize, TypeTraitement) \
                                    /*//QACJ 3443: adzhelp: Standard STK macro */\
                                    mDATPanReadU16Bit##TypeTraitement(Word)

#define mDATPanReadU16BitImmediate(BytePos) mDATAnaGetValue( (BytePos)/2)

#define mDATPanReadU16BitDelayed(BytePos)   mDATAnaGetFilteredValue((BytePos)/2)

#define mDATPanReadU16BitDefault(BytePos)   mDATAnaGetFilteredValue((BytePos)/2)


#define mDATControlAna(Cmd) mDATPanControl##Cmd()

#define mDATPanControlInit() DATAnaInitialize((const tDATAnaValue*)DATPanInitialization)
#define mDATPanControlStart() DATAnaStart()
#define mDATPanControlStop() DATAnaStop()

//------------------------------------------------------------------------------

//////////////////////////////////
// Calculated analog parameters //
//////////////////////////////////

// BATTERY_VOLTAGE - Battery voltage in mV
#define mDATReadU16BitBATTERY_VOLTAGEDefault() mDATReadU16BitBATTERY_VOLTAGEImmediate()
#define mDATReadU16BitBATTERY_VOLTAGEImmediate() (DATPanCalculateBatteryVoltage())

// TENSION_BATTERIE - battery voltage (for AFS diag)
#define mDATReadU8BitTENSION_BATTERIEDefault() mDATReadU8BitTENSION_BATTERIEImmediate()
#define mDATReadU8BitTENSION_BATTERIEImmediate() (DATPanCalculateBatteryVoltage8Bit())

// OverVoltageIsDetected - overvoltage status with hysteresis
#define mDATReadU1BitOverVoltageIsDetectedDefault() bDATPanOverVoltageIsDetected

// UnderVoltageIsDetected - voltage is below 6 V
#define mDATReadU1BitUnderVoltageIsDetectedDefault() bDATPanUnderVoltageIsDetected

// FlashersCurrentInMilliAmpers - Current in the active flasher in mA
#define mDATReadU16BitFlashersCurrentInMilliAmpersDefault() \
    mDATReadU16BitFlashersCurrentInMilliAmpersImmediate()
#define mDATReadU16BitFlashersCurrentInMilliAmpersImmediate() \
    (DATPanCalculateFlashersCurrent())

// STATUS_CLIGN =  Indicator light current value (for AFS diag)
#define mDATReadU8BitSTATUS_CLIGNDefault() mDATReadU8BitSTATUS_CLIGNImmediate()
#define mDATReadU8BitSTATUS_CLIGNImmediate() (DATPanCalculateFlashersCurrent8Bit())

// Measure values of FlasherBulbFailure and FlasherSCBatOrOpenLoad:
//QACJ 3443: adzhelp: No recursion: mDATControl macro used
#define mDATControlDATPan(Control) mDATControlDATPan##Control()
#define mDATControlDATPanFlashersCurrentMeasure() (DATPanFlashersCurrentMeasure())

// FlasherBulbFailure 
#define mDATReadU1BitFlasherBulbFailureDefault() bDATPanFlasherBulbFailure

// FlasherSCBatOrOpenLoad
#define mDATReadU1BitFlasherSCBatOrOpenLoadDefault() bDATPanFlasherSCBatOrOpenLoad

// DIAG_DRIVER_ULQ
 
// DIAG_DRIVER_ULQ_SCBat - short circuit to BATT
#define mDATReadU1BitDIAG_DRIVER_ULQ_SCBatDefault() \
    (mDATReadU16BitDIAG_DRIVER_ULQImmediate() > \
     /*//QACJ 3443: adzhelp: No recursion: mDATRead macro used */\
     mDATPanConvertVoltageMVInAdcUnits(cDATPanDIAG_DRIVER_ULQ_SCBatThresholdMV))

// ULQCurrentInMilliAmpers (not implemented yet - ADC value)
#define mDATReadU16BitULQCurrentInMilliAmpersImmediate() mDATReadU16BitULQCurrentInMilliAmpersDefault()
//QACJ 3443: adzhelp: No recursion: mDATRead macro used
#define mDATReadU16BitULQCurrentInMilliAmpersDefault() mDATReadU16BitDIAG_DRIVER_ULQDefault()

// DIAG_DRIVER_KLAXON

// DIAG_DRIVER_KLAXON_DualSCBat - short circuit to BATT on 2 outputs
#define mDATReadU1BitDIAG_DRIVER_KLAXON_DualSCBatDefault() \
    (mDATReadU16BitDIAG_DRIVER_KLAXONImmediate() >  \
     /*//QACJ 3443: adzhelp: No recursion: mDATRead macro used */\
     mDATPanConvertVoltageMVInAdcUnits(cDATPanDIAG_DRIVER_KLAXON_DualSCBatThresholdMV))

// DIAG_DRIVER_KLAXON_SingleSCBat - short circuit to BATT on single output
#define mDATReadU1BitDIAG_DRIVER_KLAXON_SingleSCBatDefault() \
    (mDATReadU16BitDIAG_DRIVER_KLAXONImmediate() >  \
     /*//QACJ 3443: adzhelp: No recursion: mDATRead macro used */\
     mDATPanConvertVoltageMVInAdcUnits(cDATPanDIAG_DRIVER_KLAXON_SingleSCBatThresholdMV))

// DIAG_DRIVER_KLAXON_SCGnd - short circuit to GND
#define mDATReadU1BitDIAG_DRIVER_KLAXON_SCGndDefault() \
    (mDATReadU16BitDIAG_DRIVER_KLAXONImmediate() <  \
     /*//QACJ 3443: adzhelp: No recursion: mDATRead macro used */\
     mDATPanConvertVoltageMVInAdcUnits(cDATPanDIAG_DRIVER_KLAXON_SCGndThresholdMV))

// DIAG_DRIVER_KLAXON_KLineTestSCBat - short circuit to BATT
#define mDATReadU1BitDIAG_DRIVER_KLAXON_KLineTestSCBatDefault() \
    (mDATReadU16BitDIAG_DRIVER_KLAXONImmediate() >  \
     /*//QACJ 3443: adzhelp: No recursion: mDATRead macro used */\
     mDATPanConvertVoltageMVInAdcUnits(cDATPanDIAG_DRIVER_KLAXON_KLineTestSCBatThresholdMV))

// DIAG_DRIVER_KLAXON_KLineCommandSCBat - short circuit to BATT
#define mDATReadU1BitDIAG_DRIVER_KLAXON_KLineCommandSCBatDefault() \
    (mDATReadU16BitDIAG_DRIVER_KLAXONImmediate() >  \
     /*//QACJ 3443: adzhelp: No recursion: mDATRead macro used */\
     mDATPanConvertVoltageMVInAdcUnits(cDATPanDIAG_DRIVER_KLAXON_KLineCommandSCBatThresholdMV))

// KlaxonCurrentInMilliAmpers (not implemented yet - ADC value)
#define mDATReadU16BitKlaxonCurrentInMilliAmpersImmediate() mDATReadU16BitKlaxonCurrentInMilliAmpersDefault()
//QACJ 3443: adzhelp: No recursion: mDATRead macro used
#define mDATReadU16BitKlaxonCurrentInMilliAmpersDefault() mDATReadU16BitDIAG_DRIVER_KLAXONDefault()

// DIAG_DRIVER_HIGH_SIDE

// DIAG_DRIVER_HIGH_SIDE_SCBat - short circuit to BATT
#define mDATReadU1BitDIAG_DRIVER_HIGH_SIDE_SCGndDefault() \
    (mDATReadU16BitDIAG_DRIVER_HIGH_SIDEImmediate() > \
     /*//QACJ 3443: adzhelp: No recursion: mDATRead macro used */\
     mDATPanConvertVoltageMVInAdcUnits(cDATPanDIAG_DRIVER_HIGH_SIDE_SCGndThresholdMV))

// PDOInMilliVolt - Diag driver high side  (not implemented yet - ADC value)
#define mDATReadU16BitPDOInMilliVoltImmediate() mDATReadU16BitPDOInMilliVoltDefault()
//QACJ 3443: adzhelp: No recursion: mDATRead macro used
#define mDATReadU16BitPDOInMilliVoltDefault() mDATReadU16BitDIAG_DRIVER_HIGH_SIDEDefault()

// DIAG_FLASHER

// DIAG_FLASHER_SCGnd - short circuit to GND
#define mDATReadU1BitDIAG_FLASHER_SCGndDefault() \
    (mDATReadU16BitDIAG_FLASHERImmediate() > \
     /*//QACJ 3443: adzhelp: No recursion: mDATRead macro used */\
     mDATPanConvertVoltageMVInAdcUnits(cDATPanDIAG_FLASHER_SCGndThresholdMV))


////////////////////////////////////////////////////////////////////////////////
// Conversion from voltage to ADC reading (10 bit ADC)
#define mDATPanConvertVoltageMVInAdcUnits(VoltageMV) \
    (U16)(((U32)(VoltageMV) * (U32)cDATPanMaxAdcValue) / (U32)cDATPanVRefVoltageInMV)

//------------------------------------------------------------------------------
// Exported functions
//
// extern tReturnType LAYCmpFunctionName(tTypeArgument1 ArgumentName1, ... );
//------------------------------------------------------------------------------
//QACJ 3451: adzhelp: Function declared in standard header as well
extern void DATPanRefresh( void );
extern void DATPanInit(void );
extern MEM_TYPE U16 DATPanCalculateBatteryVoltage(void);
extern MEM_TYPE U8 DATPanCalculateBatteryVoltage8Bit(void);
extern MEM_TYPE U16 DATPanCalculateFlashersCurrent(void);
extern MEM_TYPE U8 DATPanCalculateFlashersCurrent8Bit(void);
extern MEM_TYPE void DATPanFlashersCurrentMeasure (void);

#endif // _dat_pan_H_

