//******************************************************************************
// Company:      Johnson Controls Inc.
// -----------------------------------------------------------------------------
// Copyright:    This software is JCI property.
//               Duplication or disclosure without JCI written authorization
//               is prohibited.
// -----------------------------------------------------------------------------
// Project:      <STANDARD>
// Language:     C
// -----------------------------------------------------------------------------
// Component:    <Comments about the component (role, algorithm, structure, 
//               limitations, defined tasks and events...)>
//******************************************************************************

//------------------------------------------------------------------------------
// Body Identification
//------------------------------------------------------------------------------
#define dat_ana  "dat_ana"


//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//
// #include <system_file_name.h>
// #include "project_file_name.h"
//------------------------------------------------------------------------------

#include "deftypes.h"
#include "lib.h"
#include "tos.h"
#include "dat.h"
#include "dat_ana.h"

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
#ifndef cLDB_ANAIsSynchronous
static BOOL FirstConversion;
#endif 

static tTOSAlarm Alarm;

//------------------------------------------------------------------------------
// Constant local data
//
// static const tType  VariableName;
//------------------------------------------------------------------------------

static const tMsg Msg = { ((U8 *) DATAnaBufferFromLDB), 
                               (cDATAnaNumberOfChanels * cDATAnaNbByteValue)};
//Warning QAC 3218 File scope static, 'Msg', only accessed in one function. Misra Rule 22

//------------------------------------------------------------------------------
// Exported data
//
// tType   u8LAYCmpVariableName; (LAY: 3 characters to identify the layer)
// tType*  pu8LAYCmpVariableName;(Cmp: 3 characters to identify the component)
//------------------------------------------------------------------------------

tDATAnaValue    DATAnaBufferFromLDB[cDATAnaNumberOfChanels];

tDATAnaCalculationSize DATAnaFilteredBuffer[cDATAnaNumberOfChanels];

//------------------------------------------------------------------------------
// Constant exported data
//
//             (LAY: 3 characters to identify the layer)
//             (Cmp: 3 characters to identify this component)
// 
// const tType   LAYCmpVariableName;
//------------------------------------------------------------------------------

#ifdef ConstantDivisor
   // Table containing the different coefficient values
   const U8 DATAnaCoeffValue[cDATAnaNumberOfChanels]  = mDATAnaCoeffValue();
#else
   // Table containing the different divisor values
   const U8 DATAnaDivisorValueNow[cDATAnaNumberOfChanels] = mDATAnaDivisorValue();
#endif

//------------------------------------------------------------------------------
// Local function prototypes
// 
// static tTypeRetour FunctionName(tTypeArgument1 ArgumentName1, ... );
//------------------------------------------------------------------------------

//==============================================================================
//=========================== LOCAL FUNCTIONS ==================================
//==============================================================================

//==============================================================================
// DESCRIPTION :
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : (pseudo code, algorithm ... )
//==============================================================================
// static type FunctionName(...)


//==============================================================================
//=========================== EXPORTED FUNCTIONS ===============================
//==============================================================================

//==============================================================================
// DESCRIPTION : DATAnaInitialize
//
// PARAMETERS (Type,Name,Min,Max) :   tDATAnaValue* : address of the initial value
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : Initilisation of the component
//==============================================================================
MEM_TYPE void DATAnaInitialize(const tDATAnaValue *StartingValues)
{
    U8 Cmpt;
    // Initialization of storage spaces
    for (Cmpt = 0; Cmpt < cDATAnaNumberOfChanels; Cmpt++)
    {
        DATAnaBufferFromLDB[Cmpt] = StartingValues[Cmpt];
        #ifdef ConstantDivisor
            DATAnaFilteredBuffer[Cmpt] = ((tDATAnaValue)DATAnaBufferFromLDB[Cmpt]) * cDATAnaDivisorValue;
        #else
            DATAnaFilteredBuffer[Cmpt] = ((tDATAnaValue)DATAnaBufferFromLDB[Cmpt]) << DATAnaDivisorValueNow[Cmpt];
        #endif
    }

#ifndef cLDB_ANAIsSynchronous
    FirstConversion = cTrue;
#endif 
}

//==============================================================================
// DESCRIPTION : DATAnaStart
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : Start of the component
//==============================================================================
void DATAnaStart(void)
{
    Alarm.TaskID = cTOSTaskID_TacheANA;
    TOSSetRelAlarm(&Alarm, 0,  mTOSConvMsEnTickAlarm (cDATAnaRefreshingTempoAnaMs));
#ifdef COMPILATION_NATIVE
    LDBControl(cLDBChannelAna, cLDBAnaStart);
#else
#ifdef cLDBAnaStart
    LDBControl(cLDBChannelAna, cLDBAnaStart);
#endif /* cLDBAnaStart */
#endif
}

//==============================================================================
// DESCRIPTION : DATAnaStop
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : Stop of the component
//==============================================================================
void DATAnaStop(void)
{
    TOSCancelAlarm(&Alarm);
#ifdef COMPILATION_NATIVE
    LDBControl(cLDBChannelAna, cLDBAnaStop);
#else
#ifdef cLDBAnaStop
    LDBControl(cLDBChannelAna, cLDBAnaStop);
#endif /* cLDBAnaStop */
#endif
}


//==============================================================================
// DESCRIPTION : DATAnaCallBackEndCtrl
//
// PARAMETERS (Type,Name,Min,Max) : tCtrl: control identifier
//                                  tStatus : control status   
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : End of control LDB callback
//==============================================================================
#ifdef COMPILATION_NATIVE
void DATAnaCallBackEndCtrl  (tCtrl Ctrl, tStatus Statut)
{
    Ctrl = Ctrl;
    Statut = Statut;
    mLIBassert(Statut==cLDBCorrect);
}
#else
#if (defined(cLDBAnaStart) || defined(cLDBAnaStop))
void DATAnaCallBackEndCtrl  (tCtrl Ctrl, tStatus Statut)
{
    Ctrl = Ctrl;
    Statut = Statut;
    mLIBassert(Statut==cLDBCorrect);
}
#endif
#endif

//==============================================================================
// DESCRIPTION : DATAnaCallBackRxWithoutAddr
//
// PARAMETERS (Type,Name,Min,Max) : tStatus : conversion status
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : End of reception callback: analog conversion is available
//==============================================================================
void DATAnaCallBackRxWithoutAddr (tStatus Statut)
{
    Statut = Statut;
    mLIBassert( Statut == cLDBCorrect );
}


//==============================================================================
// DESCRIPTION : DATAnaTask
//
// PARAMETERS (Type,Name,Min,Max) :   none
//
// RETURN VALUE :   none
//
// DESIGN INFORMATION : periodical receive of the analog entries
//==============================================================================
void DATAnaTask( void )
{
    U8    InputIndex;
    tDATAnaCalculationSize    Temp;

#ifdef cLDB_ANAIsSynchronous
    LDBReceiveWithoutAddr( cLDBChannelAna, (tMsg *) &Msg );
#else
    if (FirstConversion  == cFalse)
    {
#endif
        // going through all the entries
        for (InputIndex = 0; InputIndex < cDATAnaNumberOfChanels; InputIndex++)
        {
#ifdef ConstantDivisor
            // Filtering with a constant divisor
            Temp = (tDATAnaCalculationSize)DATAnaFilteredBuffer[InputIndex];
            Temp -= (Temp*DATAnaCoeffValue[InputIndex])/cDATAnaDivisorValue;
            Temp += ((tDATAnaCalculationSize)DATAnaBufferFromLDB[InputIndex]*DATAnaCoeffValue[InputIndex]);
            DATAnaFilteredBuffer[InputIndex] = Temp;
      
#else
            // Filtering with a constant coefficient (1)
            Temp = (tDATAnaCalculationSize)DATAnaFilteredBuffer[InputIndex];
            Temp -= (Temp>>DATAnaDivisorValueNow[InputIndex]);
            Temp += (tDATAnaCalculationSize)DATAnaBufferFromLDB[InputIndex];
            DATAnaFilteredBuffer[InputIndex] = Temp;
#endif
        }
    
    // Used to realize tests on the analog inputs such as analog entries used for digital entries
    DATPanRefresh();
    
#ifndef cLDB_ANAIsSynchronous
    }
    else
    {
        FirstConversion = cFalse;
    }
  
    LDBReceiveWithoutAddr( cLDBChannelAna, (tMsg *) &Msg );
#endif
}

