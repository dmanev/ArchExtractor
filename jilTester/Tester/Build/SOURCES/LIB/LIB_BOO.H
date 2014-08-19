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
// Component:    LIB_BOO
// -----------------------------------------------------------------------------
// $Date:   Oct 30 2009 11:54:34  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/CMN_CMP/LIB/LIB_BOO/LIB_BOO.H-arc  $
// $Revision:   1.2  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/CMN_CMP/LIB/LIB_BOO/LIB_BOO.H-arc     $
// 
//    Rev 1.2   Oct 30 2009 11:54:34   adzhelp
// Cm006254: Boot link table address updated
// 
//    Rev 1.1   Sep 17 2009 09:41:04   adzhelp
// Cm003277: Definitions for start addresses added. 
// Definition for watchdog configuraiton added.
// 
//    Rev 1.0   04 Feb 2009 17:03:18   adzhelp
// Initial revision.
//******************************************************************************

#ifdef I_LIB_BOO_H
#else
#define I_LIB_BOO_H (1)

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//
// #include <system_file_name.h>
// #include "project_file_name.h"
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Constant data
//
// extern const tType  s8LAYCmpVariableName;
//------------------------------------------------------------------------------

//LinkTable address definition (permits to the customer softare to access to shared function)
#define   cLIBBooBootLinkTableAddress    ((U16)0x6800UL)

//Definition of the entry point of the customer applicative software
#ifndef DEBUG
//For boot with SA1/SA2 active
#define   cLIBBooApplicationStartAddress ((U16)0x0090UL)



#else
#define   cLIBBooApplicationStartAddress ((U16)0x0090UL)
#endif


// Watchog configuration in OPTION BYTE @0x0080
#define cLIBBooWatchdogConfiguration    (U8)0x7BU   // Window 100%, watchdog enabled, 
                                                    //T = 124.12 ms, oscillator cannot be stopped

//------------------------------------------------------------------------------
// Exported Macros
//
// #define LAYCmpMacroName(...)   (MacroDefinition)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported type
//
// typedef Expression tLAYCmpTypeName;
//------------------------------------------------------------------------------

typedef void (*tpReturnToBootLink)      (BOOL, U16);
typedef BOOL (*tpRetreiveLogZoneRecord) (U8 *, U8 );
typedef void (*tpRetreiveECUIdent)      (U8 *);
typedef BOOL (*tpInfractAttDetected)    (void );
typedef void (*tpVoidLink)( void );

//Interface APPLI-BOOT definition
typedef struct
{
  tpReturnToBootLink      pReturnToBootLink;
  tpRetreiveLogZoneRecord pRetreiveLogZoneRecord;
  tpRetreiveECUIdent      pRetreiveECUIdent;
  tpInfractAttDetected    pInfractAttDetected;
  tpVoidLink              pVoidLink4;
  tpVoidLink              pVoidLink5;
  tpVoidLink              pVoidLink6;
  tpVoidLink              pVoidLink7;
} tBootLinkTable;


//------------------------------------------------------------------------------
// Exported data
//
// extern  tType   u8LAYCmpVariableName;
// extern  tType*  ps32LAYCmpVariableName; 
//------------------------------------------------------------------------------

extern U32 LIBBooForcedLoaderModeDetected;
extern U32 LIBBooVehicleStateDetected;
extern U16 LIBBooApplicationRandomNumber;


//------------------------------------------------------------------------------
// Constant exported data
//
// extern const tType  s8LAYCmpVariableName;
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Exported functions
//
// extern tReturnType LAYCmpFunctionName(tTypeArgument1 ArgumentName1, ... );
//------------------------------------------------------------------------------

extern BOOL LIBIsReturnToBootMode(void);
extern U16  LIBGetSeedInitialValue(void);
extern BOOL LIBIsDownloadEnable(void);
#ifdef COMPILATION_NATIVE
extern BOOL LIBIsECUFunctional(void);
#endif
extern void LIBDisableReturnToBoot(void);
extern void LIBReturnToApplication(void);
extern void LIBBooSetNoInitVar(U32 dwVal);
extern void LIBReturnToBoot(BOOL Security,U16 ApplicationRandomNumber);

extern BOOL LIBBooIsBootClusterSwapPerformed(void);
extern void LIBBooDisableBootClusterSwap(void);
extern void LIBBooPerformBootClusterSwap(void);

#endif   /* I_LIB_BOO_H */

