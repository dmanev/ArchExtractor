#ifndef _QAC_
//******************************************************************************
// Company:      Johnson Controls Inc.
// -----------------------------------------------------------------------------
// Copyright:    This software is JCI property.
//               Duplication or disclosure without JCI written authorization
//               is prohibited.
// -----------------------------------------------------------------------------
// Project:      X90_BCM
// Language:     C
// -----------------------------------------------------------------------------
// Component:    LAP_KWPP.H
// -----------------------------------------------------------------------------
// $Log:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_KWP/LAP_KWPP.H-arc  $
// 
//    Rev 1.2   14 Oct 2009 11:07:40   akodzhh
// Cm005756: Comment added - Component Test and reults update.
// 
//    Rev 1.1   Sep 17 2009 10:21:12   adzhelp
// Cm003277: Implementation of jump to bootloader conditions
// 
//    Rev 1.0   Jan 14 2009 16:24:04   akodzhh
// Initial revision.
// 
//******************************************************************************
#endif


#ifndef I_LAP_KWPP_H
#define I_LAP_KWPP_H (1)

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------
#ifndef UTEST
  #include "lap_afs.h"
  #include "lap_dvp.h"
  #include "lap_tfc.h"
#endif

//------------------------------------------------------------------------------
// Constant data
//------------------------------------------------------------------------------
#ifdef UTEST
  #define cLAPKwpNbrOfSessionSupported ((U8)2UL)
#else
  #define cLAPKwpNbrOfSessionSupported ((U8)5UL)
#endif
//------------------------------------------------------------------------------
// Exported type
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Constant exported data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Exported Macros
//------------------------------------------------------------------------------

// Session definition
// Warning : the first session of the list is the default session
#ifdef UTEST
#define LAPKwpInitSessiontables()                         \
  {                                                     \
    mTSTInitSession1Parameters(),                       \
    mTSTInitSession2Parameters()                        \
  }
#else
#define LAPKwpInitSessiontables()                         \
  {                                                     \
    LAPAfsInitAfsSessionParameters(),                     \
    LAPAfsInitPlantSessionParameters(),                   \
    LAPAfsInitDvpCustomerSessionParameters(),             \
    LAPDvpInitDvpSessionParameters(),                     \
    LAPTfcInitTFCDiagSessionParameters()                  \
  }
#endif

//This compilation option active the management of the reprogrammation (Jump to the Boot loader)
#define BOOTLOADER_IS_SUPPORTED

//Add here the project specific macro to execute actions before jump into the boot
#define  mLAPKwpAddSpecificCommand()
        //Warning: if you have a high voltage supply you should wait the electronic has finished
        //to switch his power supply to the battery supply before jump into the boot software
/*      #define  mLAPDiaAddSpecificCommand()\
        while (IsHighVoltageAlimStopped == cFalse)\
        {\
                       LDBRefreshWatchDog();\
        //QACJ 2017: akodzhh: macro in comment
        }*/

//Add here the project specific macro for BOOT jump condition check
#define mLAPKwpCheckBootJumpConditions() \
    (   mLAPKwpCheckBootloaderPresent() \
     && mLAPKwpCheckDynamicConditions() \
     && mLAPKwpCheckImmoInactive() \
    )

#ifdef COMPILATION_NATIVE
#define mLAPKwpCheckBootloaderPresent() cFalse
#else
#define mLAPKwpCheckBootloaderPresent() \
     (  ((((tBootLinkTable*)cLIBBooBootLinkTableAddress)->pVoidLink6) == ((tpVoidLink)0x426FU) /*'Bo'*/ ) \
     && ((((tBootLinkTable*)cLIBBooBootLinkTableAddress)->pVoidLink7) == ((tpVoidLink)0x6F74U) /*'ot'*/ ) )
#endif

#define mLAPKwpCheckDynamicConditions() \
    (  (mDATRead(U1Bit, ENGINE_RUNNING, Default) == cFalse) \
    && (mDATRead(U8Bit, VEHICLE_SPEED, Default) == 0) ) 

#define mLAPKwpCheckImmoInactive() (mDATRead(U1Bit, PWR_IGN, Default) == 0)

//------------------------------------------------------------------------------
// Exported functions
//------------------------------------------------------------------------------
//QACJ 0862: akodzhh: file content is referenced in macro
//QACJ 0862: akodzhh: file content in referenced in macro
//QACJ 0862: akodzhh: file content in referenced in macro
//QACJ 0882: akodzhh: forceincluded deftypes.h
#endif //  I_LAP_KWPP_H 
