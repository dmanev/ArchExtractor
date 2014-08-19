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
// Component:    LDB_SLD
//               Solder test component
// -----------------------------------------------------------------------------
// $Date:   Feb 17 2010 14:45:50  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_SLD/LDB_SLDp.h-arc  $
// $Revision:   1.1  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LDB/LDB_SLD/LDB_SLDp.h-arc  $ 
// 
//    Rev 1.1   Feb 17 2010 14:45:50   adzhelp
// Cm006219: SPI type set to '4'. Output only pins retained to '0'.
// 
//    Rev 1.0   Feb 10 2010 10:15:40   adzhelp
// Initial revision.
//
//******************************************************************************

#ifndef I_LDB_SLDP_H
#define I_LDB_SLDP_H

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------

// This is an example:
// Reduce to minimum the inclusions!!!
// #include <system_file_name.h>
// #include "project_file_name.h"

//------------------------------------------------------------------------------
// Constant data
//------------------------------------------------------------------------------

/////////////////////////////////////////////
// Control signal 'Bit_Test_soudures' configuration
/////////////////////////////////////////////

// Set 'Bit_Test_soudures' pin: PX.b.bY (X = port number, Y = bit number)
#if defined(_QAC_)
#define cLDBSldBitTestSolderPin             (P7)
#elif !defined(UTEST)
#define cLDBSldBitTestSolderPin             (P7_bit.no6)
#endif

// Set 'Bit_Test_soudures' pin level (0 / 1) for entering into test mode
#define cLDBSldBitTestSolderPinEnterLevel   (1U)

// Set 'Bit_Test_soudures' pin level (0 / 1) in sleep position
#define cLDBSldBitTestSolderPinSleepLevel   (1U)

/////////////////////////////////////////////
// Timing configuration
/////////////////////////////////////////////

// Set time 'ton' in [ms] needed for entry into solder control mode
#define cLDBSldTonMs    (10UL)  // 10 ms

/////////////////////////////////////////////
// SPI configuration
/////////////////////////////////////////////

// Set utilized UART (SPI) number 0, 1, or 2 
#define cLDBSldUartNumber   1

// Set clock polarity: 0 / 1
// 0 - transmit data at falling edge, receive data at rising edge
// 1 - transmit data at rising edge, receive data at falling edge
#define cLDBSldClkPolarity  0

/////////////////////////////////////////////
// Ports configuration
/////////////////////////////////////////////

// MCU Port direction register : set either '1' or '0' according to MCU manual
#define cLDBSldPortOutputValue  0

// Set number of ports
#define cLDBSldPortsNumber      10

// Set list of available port registers in the specified order
// P0, P1, P2, P3, P4, P5, P6, P7, P12, P14
#define cLDBSldPortRegistersList() \
    { \
        &P0, \
        &P1, \
        &P2, \
        &P3, \
        &P4, \
        &P5, \
        &P6, \
        &P7, \
        &P12, \
        &P14 \
    }

// Set list of port direction registers in the specified order
#define cLDBSldPortDirRegistersList() \
    { \
        &PM0, \
        &PM1, \
        &PM2, \
        &PM3, \
        &PM4, \
        &PM5, \
        &PM6, \
        &PM7, \
        &PM12, \
        &PM14 \
    }

// Set list of input only pins for each port (bit 1 means input only)
#define cLDBSldPortInputOnlyPinsList() \
    { \
        ((U8)0x98U), /* Port 0 - P00 reserved, P04 SPI CLK, P03 SPI IN */ \
        ((U8)0x00U), /* Port 1 */ \
        ((U8)0x00U), /* Port 2 */ \
        ((U8)0xF0U), /* Port 3 - P37...P34 reserved */ \
        ((U8)0xF0U), /* Port 4 - P47...P44 reserved  */ \
        ((U8)0xF0U), /* Port 5 - P57...P54 reserved  */ \
        ((U8)0xF0U), /* Port 6 - P67...P64 reserved  */ \
        ((U8)0x40U), /* Port 7 - P76 - solder control pin */ \
        ((U8)0xE6U), /* Port 12 - P127...P123 reserved, P121 - X1, P122 - X2 */ \
        ((U8)0xFCU)  /* Port 14 - P147...P142 reserved  */ \
    }

// Set list of output only pins for each port (bit 1 means output only)
#define cLDBSldPortOutputOnlyPinsList() \
    { \
        ((U8)0x04U), /* Port 0 - P02 SPI OUT */ \
        ((U8)0x00U), /* Port 1 */ \
        ((U8)0x00U), /* Port 2 */ \
        ((U8)0x00U), /* Port 3 */ \
        ((U8)0x00U), /* Port 4 */ \
        ((U8)0x00U), /* Port 5 */ \
        ((U8)0x00U), /* Port 6 */ \
        ((U8)0x00U), /* Port 7 */ \
        ((U8)0x00U), /* Port 12 */ \
        ((U8)0x01U)  /* Port 14 - P140 clock output */ \
    }
    
/////////////////////////////////////////////
// Component test configuration
/////////////////////////////////////////////
// Use this mode only for testing operation of component.
// In this mode component returns:
// - First frame: port data read from ports
// - Next frames: port data sent by tester

#if !defined(UTEST) || defined(_QAC_)
// Set test communications mode (1 - enabled, 0 - disabled)
#define cLDBSldTestCommunications   0
#else
// for unit test mode enabled because active solder control may damage emulator pins
#define cLDBSldTestCommunications   1
#endif

//------------------------------------------------------------------------------
// Exported type
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------

// This is an example:
// Reduce to minimum the usage of extern data members!!!
// extern  tType   LAYCmpVariableName;
// extern  tType*  pLAYCmpVariableName;
// extern  U8      u8LAYCmpVariableName;
// extern  U16*    pu16LAYCmpVariableName;

//------------------------------------------------------------------------------
// Constant exported data
//------------------------------------------------------------------------------

// This is an example:
// Reduce to minimum the usage of extern constant data members!!!
// extern const tType  cLAYCmpConstantName;
// extern const U32    cu32LAYCmpConstantName;

//------------------------------------------------------------------------------
// Exported Macros
//------------------------------------------------------------------------------

// This is an example:
// #define LAYCmpMacroName(...)   (MacroDefinition)

//------------------------------------------------------------------------------
// Exported functions
//------------------------------------------------------------------------------

// This is an example:
// tType LAYCmpFunctionName( tTypeArgument1 ArgumentName1, ... );

#endif   // I_LDB_SLDP_H
