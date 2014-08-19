//******************************************************************************
// Company:      Johnson Controls Inc.
// -----------------------------------------------------------------------------
// Copyright:    This software is JCI property.
//               Duplication or disclosure without JCI written authorization
//               is prohibited.
// -----------------------------------------------------------------------------
// Project:      SW0032
// Language:     ANSI-C
// -----------------------------------------------------------------------------
// Component:    <Comments about the component (role, algorithm, structure, 
//               limitations, defined tasks and events...)>
// -----------------------------------------------------------------------------
// QACJ - (0288): Specific comment characters needed for PVCS compatibility
// $Date:   04 Feb 2009 17:02:50  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/EXT_CMP/CPP_CMP/STK/SOURCES/DAT_EEP.H-arc  $
// $Revision:   1.0  $
// -----------------------------------------------------------------------------
// QACJ - (2017): Comment style needed for our toolkit
/* $Log:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/EXT_CMP/CPP_CMP/STK/SOURCES/DAT_EEP.H-arc  $
// 
//    Rev 1.0   04 Feb 2009 17:02:50   adzhelp
// Initial revision.
*/
//******************************************************************************

#ifndef _DAT_EEP_H_
#define _DAT_EEP_H_

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//
// #include <system_file_name.h>
// #include "project_file_name.h"
//------------------------------------------------------------------------------
#include "Deftypes.h"
#include "DAT_EEPp.h"

//------------------------------------------------------------------------------
// Data prefix for constant & data: see coding guideline
//
//------------------------------------------------------------------------------
// Constant data
//
// #define cu16LAYCmpConstantName   ((U16) ConstantValueUL)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported type
//
// typedef Expression tLAYCmpTypeName;
//------------------------------------------------------------------------------
typedef struct
{
    U16           Offset;
    tDATEepOffset Size;
    U8            CallBackNumber;
} tDATEepBloc;

typedef void (*tpfCallBack)(tDATEepProcessHandle ProcessHandle, BOOL StatusOk);

//------------------------------------------------------------------------------
// Exported data
//
// extern  tType   u8LAYCmpVariableName;
// extern  tType*  ps32LAYCmpVariableName; 
//------------------------------------------------------------------------------

extern U16 DATEepBuffer[cDATEepBufferSize];

//------------------------------------------------------------------------------
// Constant exported data
//
// extern const tType  s8LAYCmpVariableName;
//------------------------------------------------------------------------------

// recomputing the process list and indexes in case the unprotect featuer is required

#ifdef cLIBStkUnprotect_Used

// Append the DatMan process to the configured ones

#define cDATEepProcessHandleForDatMan ((tDATEepProcessHandle) cDATEepNumberOfProcess)

#define cDATEepExtendedNumberOfProcess (cDATEepNumberOfProcess + 1U)

#define mDATEepProcessInformationTable()       \
    mDATEepDeclareBlocList(),                  \
    { 0, 0, cDATEepNumberOfCallBack }

#define cDATEepExtendedNumberOfCallBack (cDATEepNumberOfCallBack + 1U)

#define mDATEepExtendedCallBackList()          \
    mDATEepDeclareCallBackList(),              \
    DATManCallBackEep

#else // cLIBStkUnprotect_Used

#define cDATEepExtendedNumberOfProcess   cDATEepNumberOfProcess
#define mDATEepProcessInformationTable() mDATEepDeclareBlocList()
#define cDATEepExtendedNumberOfCallBack  cDATEepNumberOfCallBack
#define mDATEepExtendedCallBackList()    mDATEepDeclareCallBackList()

#endif // cLIBStkUnprotect_Used


//------------------------------------------------------------------------------
// Exported Macros
//
// #define LAYCmpMacroName(...)   (MacroDefinition)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported functions
//
// extern tReturnType LAYCmpFunctionName(tTypeArgument1 ArgumentName1, ... );
//------------------------------------------------------------------------------

// Begining and end of process
extern void DATEepProcessRequest(tDATEepProcessHandle ProcessHandle);
extern void DATEepTerminateProcess(void);
extern BOOL DATEepIsActivate(tDATEepProcessHandle ProcessHandle);

// Data bloc acces
extern void DATEepRead   (U16* pBuff, tDATEepOffset Ad, tDATEepOffset Sz);
extern void DATEepWrite  (U16* pBuff, tDATEepOffset Ad, tDATEepOffset Sz);
extern void DATEepCompare(U16* pBuff, tDATEepOffset Ad, tDATEepOffset Sz);

// Superviser acces
extern void DATEepAbsoluteRead (U16* pBuff, U16 Ad, tDATEepOffset Sz);
extern void DATEepAbsoluteWrite(U16* pBuff, U16 Ad, tDATEepOffset Sz);
extern void DATEepIsMaintainActiveSleepState( void );
#ifdef cLIBStkUnprotect_Used
extern void DATEepUnprotect (void);
#endif

// Eeprom task
extern void DATEepTask(void);

// Initialisation
extern void DATEepInit(void);

// Check EEP is processing
extern BOOL DATEepIsProcessing(void);

// Call-Back DAT_PEE
extern BOOL DATPeeIsEepromAccessible(void);

// Call-Back DAT_MAN
#ifdef cLIBStkUnprotect_Used
extern void DATManCallBackEep(tDATEepProcessHandle ProcessHandle, BOOL StatusOk);
#endif

#endif   /* I_DAT_EEP_H */
