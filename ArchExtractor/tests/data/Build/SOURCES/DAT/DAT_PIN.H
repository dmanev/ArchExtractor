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
// Component:    DAT_PIN
// -----------------------------------------------------------------------------
// $Date:   Feb 03 2010 10:13:20  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_PIN/DAT_PIN.H-arc  $
// $Revision:   1.6  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_PIN/DAT_PIN.H-arc  $
// 
//    Rev 1.6   Feb 03 2010 10:13:20   adzhelp
// Cm006590, Cm006698: Inputs management during undervoltage
// 
//    Rev 1.5   Oct 06 2009 11:00:10   adzhelp
// Cm006155: Enter in active sleep mode when requested from LDB_DIN
// 
//    Rev 1.4   Apr 22 2009 09:39:04   adzhelp
// Cm003261: DATPinLeaveStartingStepState() declared
// 
//    Rev 1.3   Apr 16 2009 09:41:24   adzhelp
// Cm003276: Callback for wakeup from LDB_DIN added
// 
//    Rev 1.2   Apr 03 2009 13:55:38   adzhelp
// Cm003270: Implementation of DEFROSTER filtration
// 
//    Rev 1.1   Mar 20 2009 17:30:14   adzhelp
// Cm003619: Parameterization according to HSI
//
//    Rev 1.0   10 Nov 2008 10:21:12   ailievb
// Initial revision.
//******************************************************************************

/*-------------------------------------------------------------------------
  Includes non re entry
  -------------------------------------------------------------------------*/
#ifndef I_DAT_Pin_H
#define I_DAT_Pin_H (1)

/*--------------------------------------------------------------------------
  Included files to resolve specific definitions in this file

  #include <system_file_name.h>
  #include "project_file_name.h"
  --------------------------------------------------------------------------*/
#include "dat_Din.h"
#include "dat_Pinp.h"


/*--------------------------------------------------------------------------
  Constant data

  #define cCMPConstantName   ((tType) ConstantValue)
  --------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------
  Exported Macros

  #define mCMPMacroName   (MacroDefinition)
  --------------------------------------------------------------------------*/ 
// Read macros
#define mDATPinReadU1BitDelayed(Octet,Bit)  mDATDinGetFilteredValue(Octet,Bit)
#define mDATPinReadU1BitImmediate(Octet,Bit) mDATDinGetNonFilteredValue(Octet,Bit)

#define mDATPinReadU1Bit(Trame, Octet, Bit, TypeTraitement) \
  mDATPinReadU1Bit##TypeTraitement(Octet, Bit)

#define mDATPinWriteU1Bit(Trame,Octet,Bit, Etat,TypeTraitement)\
mDATPinWriteU1Bit##TypeTraitement(Trame,Octet, Bit,Etat)

#define mDATPinWriteU1BitDelayed(Trame,Octet,Bit,Etat) \
   mDATDinSetNonFilteredValue(Octet,Bit,Etat)

#define mDATPinWriteU1BitImmediate(Trame,Octet,Bit,Etat) \
   mDATDinSetNonFilteredValue(Octet,Bit,Etat); \
   mDATDinSetFilteredValue(Octet,Bit,Etat)

// Additional filtration on some inputs
#define mDATReadU1BitDEFROSTER_SW_FILTEREDDefault() \
    (bDATPinDefrosterSWFiltered)

// BCM in sleep mode
#define mDATReadU1BitBcmSleepModeDefault()  bDATPinSleepMode

// Control macros
#define mDATControlPinStop()              DATDinStop()
#define mDATControlPinStart()             DATDinStart()
#define mDATControlPinEnterSleepMode()    DATDinEnterSleepMode()
#define mDATControlPinInit()              DATPinInit()

#define mDATControlDin(Cmd)               mDATControlPin##Cmd()

/*--------------------------------------------------------------------------
  Exported types

  struct  sCMPStructureName { ... };
  union   uCMPUnionName { ... };
  enum    eCMPEnumerationName { ... };
  typedef Expression tCMPTypeName;

  --------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------
  Exported data

  extern  tType   CMPVariableName;
  extern  tType*  pCMPVariableName; 
  --------------------------------------------------------------------------*/ 
extern BOOL bDATPinDefrosterSWFiltered;
extern BOOL bDATPinSleepMode;

/*--------------------------------------------------------------------------
  Constant exported data

  extern const tType  CMPVariableName;
  --------------------------------------------------------------------------*/ 
extern const U8 DATPinInitArray[];

/*--------------------------------------------------------------------------
  Exported functions

  extern tReturnType CMPFunctionName(tTypeArgument1 ArgumentName1, ... );
  --------------------------------------------------------------------------*/ 
extern void DATPinInit(void);
extern void DATPinSelection(void);
extern void DATPinStateChange(void);
extern void DATPinEnterActiveState(void);
extern void DATPinLeaveActiveState(void);
extern void DATPinLeaveStartingStepState(void);
extern void DATPinCallBackCtrl(const tCtrl Ctrl);
extern void DATPinIsMaintainActiveState(void);
extern void DATPinIsMaintainActiveSleepState(void);

/*-------------------------------------------------------------------------
  End of includes non re entry
  -------------------------------------------------------------------------*/
#endif  /* I_DAT_Pin_H */
