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
// $Date    :   Apr 14 2009 10:18:17  $
// $Archive :   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_ALA/DAT_ALA.h-arc  $
// $Revision:   1.6  $
// -----------------------------------------------------------------------------
// $Log     :   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_ALA/DAT_ALA.h-arc  $
// 
//    Rev 1.5   Apr 14 2009 10:18:17   aangovt
// Cm003271 - Update of Ararm Status for Diag macros   
// 
//    Rev 1.4   Apr 13 2009 17:39:44   aangovt
// Cm003271 - Ararm Status for Diag is added  
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

#ifndef I_DAT_ALA_H
#define I_DAT_ALA_H (1)

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//
// #include <system_file_name.h>
// #include "project_file_name.h"
//------------------------------------------------------------------------------
//#include "deftypes.h"

//------------------------------------------------------------------------------
// Data prefix for constant & data
//
// unsigned int {u8,u16,u32} / signed int {s8,s16,s32} 
// register size unsigned int {r} / float {f32,f64}  / s for struct 
// no prefix for other types.
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

//------------------------------------------------------------------------------
// Exported data
//
// extern  tType   u8LAYCmpVariableName;
// extern  tType*  ps32LAYCmpVariableName; 
//------------------------------------------------------------------------------
#define cDATALADataLenght 0x04
//------------------------------------------------------------------------------
// Constant exported data
//
// extern const tType  s8LAYCmpVariableName;
//------------------------------------------------------------------------------
extern U8     AlaCmdFrame[cDATALADataLenght];
extern BOOL  bDATAlaCommunicationIsRunning;
extern BOOL bIsAlaDiagEnabled;
//------------------------------------------------------------------------------
// Exported Macros
//
// #define LAYCmpMacroName(...)   (MacroDefinition)
//------------------------------------------------------------------------------
#define mDATReadTableU8BitAlaCmdFrameDefault(Index)  \
                    (AlaCmdFrame[Index])

#define mDATWriteTableU8BitAlaCmdFrameDefault(Index,Value)  \
                    (AlaCmdFrame[Index] = (Value))

#define mDATWriteU1BitIsAlaDiagEnabledDefault(Value) \
                    (bIsAlaDiagEnabled = (Value))

#define mDATReadU1BitIsAlaDiagEnabledDefault() \
                    (bIsAlaDiagEnabled)

#define mDATControlDATAla(Command) \
                      DATAla##Command()

#define mDATReadU1BitAlaCommunicationIsRunningDefault() \
                    (bDATAlaCommunicationIsRunning)
        
//------------------------------------------------------------------------------
// Exported functions
//
// extern tReturnType LAYCmpFunctionName(tTypeArgument1 ArgumentName1, ... );
//------------------------------------------------------------------------------
 
extern void DATAlaInit(void);
extern void DATAlaSendCommand(void);
// [EXPORTED_FUNCTIONS_END] 


#endif   // I_DAT_ALA_H 

