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
// Component:    DAT_CPU
// -----------------------------------------------------------------------------
// $Date:   Feb 13 2010 09:43:40  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_CPU/DAT_CPUP.H-arc  $
// $Revision:   1.5  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_CPU/DAT_CPUP.H-arc  $
// 
//    Rev 1.5   Feb 13 2010 09:43:40   adzhelp
// Cm007228: Allocate available RAM for stack (0xFBA8 - 0xFE1F - 632 bytes)
// 
//    Rev 1.4   Jul 20 2009 09:35:38   adzhelp
// Cm005100: SAD.ROB.STACK.01.R02 - Stack restored to end of RAM
// (NEC: SP can point only to internal RAM addresses)
// 
//    Rev 1.3   Jul 13 2009 09:24:22   adzhelp
// Cm005100: SAD.ROB.STACK.01.R02 - Stack moved to address range 0xFB00 + 512 bytes
// 
//    Rev 1.2   Mar 30 2009 13:44:14   adzhelp
// Cm004676: Stack idle measure disabled
// 
//    Rev 1.1   Mar 16 2009 16:03:58   adzhelp
// Cm003619: Stack monitoring enabled
 //
//    Rev 1.0   10 Nov 2008 10:12:36   ailievb
// Initial revision.
//******************************************************************************
#ifndef I_DAT_CPUP_H
#define I_DAT_CPUP_H (1)

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//
// #include <system_file_name.h>
// #include "project_file_name.h"
//------------------------------------------------------------------------------
#include "deftypes.h"

/*
Set cDATCpuWatermarkResetAddress in the section for target to end_of_the_stack address.
If the stack is not at fixed position, its end address could be determined from the map file.
If the stack usage overwtites the value at this address, the target is reset.  
Optionaly, cDATCpuWatermarkAssertAddress could be set in the target section to point somewhere
in the stack just for having a notification (assertion) when running a debug version on the target
and the stack usage overwrites the value there. 
Generally, both addresses should be multiply of 4 (the two less significant bits equal to zero). 
 
To help the development to choose an adequate stack size, unused stack space measurement functionality is available.
By default it is enabled when cDATCpuWatermarkResetAddress is defined. 
Currently the calculated value could be seen on the emulator: global variable u32DATCpuUnUsedStackSize. 
*/

//------------------------------------------------------------------------------
// Data prefix for constant & data: see coding guideline
//
//------------------------------------------------------------------------------
// Constant data
//
// #define cu16LAYCmpConstantName   ((U16) ConstantValueUL)
//------------------------------------------------------------------------------
#ifdef COMPILATION_NATIVE
// settings for  Windows unit test
// DO NOT EDIT!
    #define cDATCpuWinSimStackSize 100
    #define cDATCpuWatermarkAssertAddress &DATCpuWinSimStack[cDATCpuWinSimStackSize/3]
    #define cDATCpuWatermarkAssertValue cDATCpuWatermarkDefaultValue
    #define cDATCpuWatermarkResetValue cDATCpuWatermarkDefaultValue
#else
// Settings for target NEC K0 F0536 / X90_BCM
// Stack in range 0xFBA8 - 0xFE1F (632 bytes). Stack is decreasing in depth.
// Warning level 70% according to SIP
    // stack assert watermark
    // if enabled,  it is recommended to be = stack_end - 10% stack size
    #define cDATCpuWatermarkAssertAddress (cDATCpuWatermarkResetAddress + 64U)
    #define cDATCpuWatermarkAssertValue cDATCpuWatermarkDefaultValue
    // stack reset watermark
    // if enabled, it is recommended to be = stack_end for downward
    // (decreasing in depth) stack, and = stack_end - 4 for upward (increasing in depth)
    // stack.
     // set here the stack begin address calculated as: _CSTACK_END_ADDRESS - _CSTACK_SIZE + 1 
     // or take it from .map file, segment CSTACK range
    #define cDATCpuWatermarkResetAddress 0xFBA8U
    #define cDATCpuWatermarkResetValue cDATCpuWatermarkDefaultValue
#endif

//Stack unused space measurement:
#define cDATCpuStackContentsValue	 ((U8)0x69UL) // value to fill initially the stack with

//Stack overflow protection:
// if assigned to watermark address, disables corresponding check and action
#define cDATCpuWatermarkDisable ((U32)0x00UL)
// or other value, but do not use 0
#define cDATCpuWatermarkDefaultValue ((U32)0x0BADBAD0UL)

// By default the unused stack size is periodically measured in idle processing.
// Define DISABLE_IDLE_MEASURE in order to save runtime performance in idle processing and bit of a RAM (4 bytes).
// Alternative to check the unused stack size in this case will be to use a dedicated diagnostic service.
#define DISABLE_IDLE_MEASURE 

//------------------------------------------------------------------------------
// Exported type
//
// typedef Expression tLAYCmpTypeName;
//------------------------------------------------------------------------------
typedef U32 tDATCpuStackWatermarkValue;  // normally 32 bits is an adequate choice here, probably on some 8 bit MCUs 16 bits could be prefered

//------------------------------------------------------------------------------
// Exported data
//
// extern  tType   u8LAYCmpVariableName;
// extern  tType*  ps32LAYCmpVariableName; 
//------------------------------------------------------------------------------
#ifdef COMPILATION_NATIVE
// settings for  Windows unit test
// DO NOT EDIT!
    // we will simulate the stack in an array, just to be able to run the Windows unit test on it
    extern tDATCpuStackWatermarkValue DATCpuWinSimStack[];
    // only for unit testing in Windows: true when stack overflow reset will be called on target
    extern BOOL bDATCpuWinSimReset;
    // only for unit testing in Windows: false when assert watermark is overwritten
    extern BOOL bDATCpuFirstWatermarkAssert;
    // only for unit testing in Windows
    extern U32 u32DATCpuUnUsedStackSize;
    // the following two are manipulated from the unit test in order to be able
    //to test both upward and downward stacks
    extern tDATCpuStackWatermarkValue *cDATCpuWatermarkResetAddress;
    extern U8 *pDATCpuInStack;
#else
// settings for target
    extern U32 u32DATCpuUnUsedStackSize;
#endif


// #define DAT_CPU_ENABLE_HALT // To be use only on V850 ES Fx3Sx3Dx3

//------------------------------------------------------------------------------
// Constant exported data
//
// extern const tType  s8LAYCmpVariableName;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported Macros
//
// #define LAYCmpMacroName(...)   (MacroDefinition)
//------------------------------------------------------------------------------
#ifdef COMPILATION_NATIVE
// settings for  Windows unit test
// DO NOT EDIT!
    #define mDATCpuGetUnUsedStackSizeEnabled() (cTrue)
#else
// settings for target
// TODO: #define mDATCpuGetUnUsedStackSizeEnabled() (cFalse)
// in the final product this functionality should be disabled!
    #define mDATCpuGetUnUsedStackSizeEnabled() (cDATCpuWatermarkResetAddress != cDATCpuWatermarkDisable)
// if enabled, see variable u32DATCpuUnUsedStackSize value in emulator
#endif

//------------------------------------------------------------------------------
// Exported functions
//
// extern tReturnType LAYCmpFunctionName(tTypeArgument1 ArgumentName1, ... );
//------------------------------------------------------------------------------
#endif   /* I_DAT_CPUP_H */
