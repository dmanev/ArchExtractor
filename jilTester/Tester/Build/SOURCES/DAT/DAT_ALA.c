#ifndef _QAC_
//******************************************************************************
// Company:      Johnson Controls Inc.
// -----------------------------------------------------------------------------
// Copyright:    This software is JCI property.
//               Duplication or disclosure without JCI written authorization
//               is prohibited.
// -----------------------------------------------------------------------------
// Project:      RSA_X90_BCM
// Language:     C
// -----------------------------------------------------------------------------
// Component:    DAT_ALA
// -----------------------------------------------------------------------------
// $Date    :   Apr 25 2009 08:20:17  $
// $Archive :   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_ALA/DAT_ALA.c-arc  $
// $Revision:   1.7  $
// -----------------------------------------------------------------------------
// $Log     :   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_ALA/DAT_ALA.c-arc  $
// 
//    Rev 1.6   Apr 25 2009 08:20:17   aangovt
// Cm003271: Functions moved to banked memory area 
// 
//    Rev 1.5   Apr 13 2009 17:46:53   aangovt
// Cm003271 - Ararm Status for Diag is added  
// 
//    Rev 1.4   Apr 08 2009 11:44:02   aangovt
// Cm003271 Name of LDBDou contols is chanhed 
// 
//    Rev 1.3   Feb 23 2009 09:33:20   aangovt
// Cm003271  Implementation of the Alarm functionality 
// 
//    Rev 1.2   Feb 12 2009 17:26:51   aangovt
// Cm003271  Implementation of the Alarm functionality  
// 
//    Rev 1.1   Feb 10 2009 17:00:47   aangovt
// Cm003271  Implementation of the Alarm functionality 
// 
//    Rev 1.0   Feb 10 2009 13:24:09   aangovt
// Initial revision. 
//******************************************************************************
#endif
//------------------------------------------------------------------------------
// Body Identification
//------------------------------------------------------------------------------
#define DAT_ALA  "DAT_ALA"

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//
// #include <system_file_name.h>
// #include "project_file_name.h"
//------------------------------------------------------------------------------
#include "deftypes.h"
#include "lib.h"
#include "ldb.h"
#include "tos.h"
#include "dat.h"
#include "DAT_ALA.h"


//------------------------------------------------------------------------------
// Local constants
//
// #define cConstantName   ((tType) ConstantValue)
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Local macros
//
// #define mMacroName   (MacroDefinition)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Local types
//
// typedef Expression    tTypeName;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Data prefix
//
// unsigned int {u8,u16,u32} / signed int {s8,s16,s32} 
// register size unsigned int {r} / float {f32,f64}  / s for struct 
//
// -----------------------------------------------------------------------------
// Local data
//
// static  tType   u8VariableName;  
// static  tType*  pu8VariableName; 
//------------------------------------------------------------------------------
static tMsg DATAlaMsg;
//------------------------------------------------------------------------------
// Constant local data
//
// static const tType  VariableName;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported data
//
// tType   u8LAYCmpVariableName; (LAY: 3 characters to identify the layer)
// tType*  pu8LAYCmpVariableName;(Cmp: 3 characters to identify the component)
//------------------------------------------------------------------------------
U8     AlaCmdFrame[cDATALADataLenght];
BOOL  bDATAlaCommunicationIsRunning;
BOOL    bIsAlaDiagEnabled;
//------------------------------------------------------------------------------
// Constant exported data
//
//             (LAY: 3 characters to identify the layer)
//             (Cmp: 3 characters to identify this component)
// 
// const tType   LAYCmpVariableName;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Local function prototypes
// 
// static tTypeRetour FunctionName(tTypeArgument1 ArgumentName1, ... );
//------------------------------------------------------------------------------

#ifdef X90_PROJECT
static MEM_TYPE void DATAlaCallBackTxWithoutAddr_Static(tStatus Status);
static MEM_TYPE void DATAlaSendCommand_Static(void);
#endif

//==============================================================================
//=========================== LOCAL FUNCTIONS ==================================
//==============================================================================

// [LOCAL_FUNCTIONS_END] 


//==============================================================================
//=========================== EXPORTED FUNCTIONS ===============================
//==============================================================================

//==============================================================================
// DESCRIPTION : Initialization of DAT_ALA
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : refer to Detailed Design Document
//==============================================================================
void DATAlaInit(void)
{
    bDATAlaCommunicationIsRunning = cFalse;
    bIsAlaDiagEnabled = cFalse;
    mLIBmemset(AlaCmdFrame,0x00,cDATALADataLenght);
}

//==============================================================================
// DESCRIPTION : Callback from LDB_ALA - end of alarm frame transmission
//
// PARAMETERS (Type,Name,Min,Max) :   tStatus Status
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : refer to Detailed Design Document
//==============================================================================
//QACJ 3206: aangovt: tStatus Status is standard  parameter  for DAT callback
void DATAlaCallBackTxWithoutAddr(tStatus Status)
{
#ifdef X90_PROJECT
    DATAlaCallBackTxWithoutAddr_Static(Status);
}
#pragma optimize=no_inline
static MEM_TYPE void DATAlaCallBackTxWithoutAddr_Static(tStatus Status)
{
#endif
    
    mLIBassert(Status == cLDBCorrect);

    
    // The channel dou takes the control of OPEN_DOOR_LED output
    LDBControl(cLDBChannelDou,cLDBDouEnableOPEN_DOOR_LED);

    // End of the alarm communication
    bDATAlaCommunicationIsRunning = cFalse;
    DATDouRefreshOutputTask(); 
}

//==============================================================================
// DESCRIPTION : Starts alarm frame transmission with LDBSendWithoutAddr
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : refer to Detailed Design Document
//==============================================================================
void DATAlaSendCommand(void)
{
#ifdef X90_PROJECT
    DATAlaSendCommand_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void DATAlaSendCommand_Static(void)
{
#endif

    // Start the alarm sending
    bDATAlaCommunicationIsRunning = cTrue;

    // The alarm takes the control of OPEN_DOOR_LED output
    LDBControl(cLDBChannelDou,cLDBDouDisableOPEN_DOOR_LED);

    DATAlaMsg.Lng     = cDATALADataLenght;
    DATAlaMsg.pBuffer = AlaCmdFrame; 
    LDBSendWithoutAddr(cLDBChannelAla, &DATAlaMsg);
}
// [EXPORTED_FUNCTIONS_END] 
