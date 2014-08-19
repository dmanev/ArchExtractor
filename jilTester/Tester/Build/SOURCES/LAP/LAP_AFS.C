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
// Component:    LAP_AFS.C
// -----------------------------------------------------------------------------
// $Date:   Oct 12 2010 10:21:24  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_ASF/LAP_AFS.C-arc  $
// $Revision:   1.65  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/LAP/LAP_ASF/LAP_AFS.C-arc  $
// 
//    Rev 1.65   Oct 12 2010 10:21:24   amanevd
// Cm011994: It should be possible to accept erase afs code routine even if code_apv_dispo=0
// 
//    Rev 1.64   Oct 12 2010 10:14:54   amanevd
// Cm011994: LAP_AFS.C reverted to rev. 1.60
// 
//    Rev 1.63   Jul 09 2010 14:12:50   adzhelp
// Cm009623: NOP instructions removed
// 
//    Rev 1.62   Jun 30 2010 14:37:26   adzhelp
// Cm009623: UNLOCK_DOORS added in '21 DD'
// 
//    Rev 1.61   Jun 29 2010 16:20:50   adzhelp
// Cm009573: Unlock driver door activated together with unlock doors
// 
//    Rev 1.60   Jun 18 2010 08:45:58   adzhelp
// Cm009329: Frequency for buzzer I/O Control changed from 4khz to 2.4khz
// 
//    Rev 1.59   Mar 25 2010 12:14:38   adzhelp
// Cm007976: QAC Corrections - no binary change
// 
//    Rev 1.58   Mar 24 2010 17:38:00   adzhelp
// Cm007976: NRC when no bootloader
// 
//    Rev 1.57   Mar 24 2010 09:45:36   adzhelp
// Cm007976: $21$80 is filled from lastest application logzone except for version ID and serial number
// 
//    Rev 1.56   Mar 22 2010 13:27:02   amanevd
// Cm007919: Diag value of VERLOGON modified
// 
//    Rev 1.55   Mar 08 2010 14:13:34   adzhelp
// Cm007695: Clearing of faults by TOS control
// 
//    Rev 1.54   Feb 22 2010 13:58:26   amanevd
// Cm007543: Calls to LIB_CFD functions are changed
// 
//    Rev 1.53   Feb 20 2010 14:54:28   amanevd
// Cm007539: Virgin Key Test status request correction
// 
//    Rev 1.52   Feb 17 2010 11:49:02   adzhelp
// Cm007126: Negative response for IOControl on the Horn output during Acitvate State
// 
//    Rev 1.51   Feb 17 2010 10:07:58   adzhelp
// Cm007541: Byte #12 of $61$A2 set to 0 instead of APV checksum
// 
//    Rev 1.50   Feb 15 2010 16:08:30   adzhelp
// Cm006878: VERLOG_ALGO is byte number #3, bit 0
// 
//    Rev 1.49   Feb 11 2010 17:27:12   amanevd
// Cm006997: Implementation of recent prsFS_IMMO-675 and prsFS_IMMO-676
// 
//    Rev 1.48   Jan 29 2010 18:05:22   amanevd
// Cm007116 & Cm007043: ValidateLearningInAfterSaleMode
// control is sent always but negative responce '0x22' is returned in some circumstances
// 
//    Rev 1.47   Jan 29 2010 15:23:44   amanevd
// Cm006878: In function LAPAfsTreatWriteDataByLocalIdentifierService
// 8-th byte is included as 'nothing to do case'
// 
//    Rev 1.46   Jan 28 2010 10:56:58   adzhelp
// Cm007172: Configuration BOOTLADER_IS_SUPPORTED updated
// 
//    Rev 1.45   Jan 26 2010 15:07:18   adzhelp
// Cm007172: Request $21$80 gets ECU Reference from Log Zone
// 
//    Rev 1.44   Jan 21 2010 08:52:24   amanevd
// Cm006997: prsFS_IMMO-675 and prsFS_IMMO-676 put back to initial condition
// 
//    Rev 1.43   Nov 23 2009 17:24:30   akodzhh
// Cm006728: LAP_AFS: Update for QAC warnings removal and justification.
// 
//    Rev 1.42   Nov 13 2009 11:29:12   akodzhh
// Cm005566: Component test - ccov justification comments added.
// 
//    Rev 1.41   Nov 04 2009 16:24:28   adzhelp
// Cm005566: Implementation of HW Protection
// 
//    Rev 1.40   Oct 27 2009 15:31:40   adzhelp
// Cm006382: Service SecurityAccess implemented
// 
//    Rev 1.39   Oct 27 2009 15:25:14   adzhelp
// Cm005566: EEP_DefAckVerlog removed
// 
//    Rev 1.38   Oct 19 2009 16:04:48   amarinm1
// Cm005858: Code review corrections for DAT_BUZ, only a macro name changed.
// 
//    Rev 1.37   Oct 08 2009 10:31:28   akodzhh
// Cm006459: BCM Serial Number now defined in $21$80.
// 
//    Rev 1.36   Oct 06 2009 16:46:02   akodzhh
// Cm005566: EEPROM stored faults renamed - update 21 94 and 14 FF.
// 
//    Rev 1.35   Oct 05 2009 14:21:46   amanevd
// Cm006322: Impossible to exit Plant mode when IGN ON and not all keys learnt
// 
//    Rev 1.34   Oct 05 2009 13:20:20   akodzhh
// Cm006299: DIAG : Start Permanent Authentication - set status 00h when successful.
// 
//    Rev 1.33   Sep 25 2009 10:32:56   akodzhh
// Cm005557: Exit the BCM After Sale learning with Abandon param - check for Ignition is removed.
// 
//    Rev 1.32   Sep 23 2009 13:29:34   akodzhh
// Cm005225: IO control of HORN_RL output is inhibited while cycle alarm is activated.
// 
//    Rev 1.31   Sep 23 2009 12:20:08   adzhelp
// Cm003277: Implementation of read log zone request (ID F0...FF)
// 
//    Rev 1.30   Sep 21 2009 14:55:50   akodzhh
// Cm005581: 21 DD updated - add RR_WIPER_RR_FOG_LAMP, HORN_RL, DEFROSTER outputs state.
// 
//    Rev 1.29   Sep 21 2009 11:04:46   akodzhh
// Cm005207: Add SDO, KEY_BUTTON config params (21 D0, 3B D0).
// 
//    Rev 1.28   Sep 18 2009 16:47:34   akodzhh
// Cm006292: Accept 3B D0 for CALVERDI parameter - add check.
// 
//    Rev 1.27   Sep 18 2009 16:20:52   akodzhh
// Cm006292: Accept 3B D0 for CALVERDI parameter.
// 
//    Rev 1.26   Sep 15 2009 18:36:32   akodzhh
// Cm005064: 21 DB - set reserved data bytes 12,13 to 0xFF.
// 
//    Rev 1.25   Sep 15 2009 13:41:14   akodzhh
// Cm005127: Use logical state ENGINE_RPM(running or not)instead of input state DI_ENGINE_RPM(request 21DC).
// 
//    Rev 1.24   03 Sep 2009 16:34:40   akodzhh
// Cm005525: Update "protected state" in $21$DB whit VERLOGON flag instead of EEP_CAR_SECURE.
// 
//    Rev 1.23   Sep 02 2009 11:55:20   akodzhh
// Cm004994: BAT_LIGHT_TEMPO activation on PWM_ROOMLAMP IOControl request is removed.
// 
//    Rev 1.22   Sep 01 2009 14:05:10   amanevd
// Cm005142: Status of Confidential Diagnostic routines included
// 
//    Rev 1.21   Aug 31 2009 15:59:42   amanevd
// Cm005142: Transfer of Confidential Diagnostic to LIB_CFD
// 
//    Rev 1.20   Aug 07 2009 18:09:48   amanevd
// Cm005142: Implementation of Confidential Diagnostic
// 
//    Rev 1.19   03 Aug 2009 12:12:30   akodzhh
// Cm004744: Write RR_Wiper\RR_Fog config parameters in mutual exclusion - $3B$D0.
// 
//    Rev 1.18   03 Aug 2009 10:33:56   akodzhh
// Cm005567: Routine TestVirginKey is started only if IGN is On.
// 
//    Rev 1.17   Jul 31 2009 17:14:14   akodzhh
// Cm005725: SRBLI Status request - check is added for supported RoutineID.
// 
//    Rev 1.16   Jul 31 2009 15:44:50   akodzhh
// Cm005750: write EEP_CALALARM param only when EEP_CAR_SECURE is Off.
// 
//    Rev 1.15   17 Jul 2009 11:31:04   akodzhh
// Cm005756: IOBLID timeout adjusted, code review 1.5 issues fixed.
// 
//    Rev 1.14   Jul 17 2009 10:53:00   amanevd
// Cm004914: AFS code is either erased on Routine request or after Ignition counting reaches N_MISE_APC
// 
//    Rev 1.13   Jul 15 2009 10:06:24   adzhelp
// Cm005586: DATTrpDiagKeyFrequency used instead of DATTrpFrequencyOfPresentKey
// 
//    Rev 1.12   Jul 10 2009 11:03:56   akodzhh
// Cm005586: IMMO: No update of "Frequency of presented key" in $21$DB Diagnostic request.
// 
//    Rev 1.11   06 Jul 2009 16:21:48   akodzhh
// Cm005168: Wrong content of the 3th,11th byte of the BCM System Faults Status reading frame.
// 
//    Rev 1.10   May 07 2009 21:05:56   akodzhh
// Cm004970: IMMO/DIAG: Stop routine for permanent authentication wont work.
// 
//    Rev 1.9   07 May 2009 15:23:40   akodzhh
// Cm004930: Response Routine in progress instead TerminatedOk for Start Permanent Authentication request.
// 
//    Rev 1.8   May 04 2009 17:46:04   akodzhh
// Cm003128: PWM_ROOMLAMP output state reading; $21 $DB - use EEP_CAR_SECURE for protected vehicle param (RELAIS_DEM).
// 
//    Rev 1.7   May 04 2009 17:18:20   akodzhh
// Cm004909: In $21 $DB diag request, ETAT_VEH_CONDA_DECONDA not managed.
// 
//    Rev 1.6   May 04 2009 15:59:08   akodzhh
// Cm004897: The permanent authentication ($31 $A6) routine must be managed in Diag AFS session ($C0) and not in Diag DEV Session ($A0).
// 
//    Rev 1.5   Apr 29 2009 13:57:14   adzhelp
// Cm003128: MEM_TYPE attribute added to service and static functions
//
//    Rev 1.4   16 Apr 2009 17:33:18   akodzhh
// Cm003128: Analogic values CLR #78. OPEN_DOOR_LED/Alarm output shared - ensure diag control. 
// Due to Eeprom mapping changes. Erase AFS code treatment.
// 
//    Rev 1.3   Mar 30 2009 16:51:24   akodzhh
// Cm003128: Write Calibr Params($3B$D1)- removed range checks for the values written; TPS_COM_MOTEUR step fixed; Read DI_ENGINE_RPM (replace ENGINE_RPM).
// 
//    Rev 1.2   20 Mar 2009 18:07:56   akodzhh
// Cm003128 - fixes for some data names and $3B$D1 frame
// 
//    Rev 1.1   Mar 13 2009 18:47:04   akodzhh
// Cm003128 - Implementation of the Diagnostic functionality - LAP_AFS -  macros for control SerialIO update, little fixes.
// 
//    Rev 1.0   Feb 18 2009 14:49:26   akodzhh
// Initial revision.
//******************************************************************************
#endif

//------------------------------------------------------------------------------
// Body Identification
//------------------------------------------------------------------------------
#define lap_afs   "lap_afs"

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------

#include "lib.h"
#include "lib_cfd.h"
#include "tos.h"
#include "dat.h"
#include "lap_kwp.h"
#include "lap_kwpp.h"
#include "lap_afs.h"
#include "lap_afsp.h"
#include "lap_afs.hgr"

#ifdef BOOTLOADER_IS_SUPPORTED
    #include "LIB_BOO.h"
#endif

//------------------------------------------------------------------------------
// Local constants
//------------------------------------------------------------------------------
#define cRoomLampDiagRatio  (U8)100
#define cDiagBuzzFrequency  (U16)2400U     // 2.4kHZ

// common constants
#define c8Bits  8
#define c7Bits  7
#define c6Bits  6
#define c5Bits  5
#define c4Bits  4
#define c3Bits  3
#define c2Bits  2
#define c1Bits  1
#define c16Bits  16
#define c24Bits  24

#define cLSBMask       (U8)0xFFU

#define cByte0  0
#define cByte1  1
#define cByte2  2
#define cByte3  3
#define cByte4  4

// Eeprom data
#define cEEP_ECUReferenceLength     5
#define cEEP_PieNumberLength        5
#define cEEP_PieIndexLength         2
#define cEEP_SerialNumberLength     3

#define cEEP_SerialNumberIndex      23
#define cVersionIndex               16
#define cIdentLastLogZone           ((U8)0xFEU)

#define cCLRDIOptionByte  (U8)0xFF
#define cVIN_Lgth           19
#define cDataOffset       (U8)2

#define cSupplierCode1  (U8)0x30U
#define cSupplierCode2  (U8)0x32U
#define cSupplierCode3  (U8)0x31U

#define cReservedValue  (U8)0xFFU

#define cMaskIndexOfKeyRecognized   (U8)0x0FU 
#define cMaskLearningModeInProgress (U8)0x07U
#define cMaskDiagKeyFrequency       (U8)0x07U
#define cMaskFlashingFrequency      (U8)0x03U  

#define cByteOutputStateBuzzer  7
#define cByteSTATUS_CLIGN       7
#define cByteTENSION_BATTERIE   14
#define cByte18                 18


//------------------------------------------------------------------------------
// Local macros
//------------------------------------------------------------------------------
#define mInitAfsTabIdentifierServiceSupported()   \
{                                                 \
    cLAPKwpIdReadDataByLocalIdentifier,                \
    cLAPKwpIdWriteDataByLocalIdentifier,               \
    cLAPKwpIdInputOutputControlByLocalIdentifier,      \
    cAPVIdLearningModeControl,                      \
    cLAPKwpIdStartRoutineByLocalIdentifier,            \
    cLAPKwpIdStopRoutineByLocalIdentifier,             \
    cLAPKwpIdClearDiagnosticInformation,               \
    cLAPKwpIdSecurityAccess                            \
}

#define mInitAfsTabServiceSupported()                 \
{                                                     \
    LAPAfsTreatReadDataByLocalIdentifierService,           \
    LAPAfsTreatWriteDataByLocalIdentifierService,          \
    LAPAfsTreatInputOutputControlByLocalIdentifierService, \
    LAPAfsTreatLearningModeControlService,                 \
    LAPAfsTreatStartRoutineByLocalIdentifierService,       \
    LAPAfsTreatStopRoutineByLocalIdentifierService,        \
    LAPAfsTreatClearDiagnosticInformation,                 \
    LAPAfsTreatSecurityAccessService                       \
}

#define mIsECU_LOG_ID(ID)   ((U8)((ID)&(U8)0xF0)==(U8)0xF0)

//------------------------------------------------------------------------------
// Local types
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Local data
//------------------------------------------------------------------------------
static U8     u8RoutineRequestInProgress;
static U8     u8OutputRequestInProgress;
static tTOSTempo  OutputControlTimeOut;
static tTOSTempo  OutputControlTimeOutValue;


//------------------------------------------------------------------------------
// Constant local data
//------------------------------------------------------------------------------
static const U8 TableIOCBLIDIdentifier[cNbOutputToControl]=
{
    // TOR output
    cOutputLockDoors,    
    cOutputUnlockDoors,  
    cOutputUnlockDrDoor, 
    cOutputDiRight,      
    cOutputDiLeft,       
    cOutputFrWiper,      
    cOutputRrWiper,      
    cOutputBatLightTempo,
    cOutputDoorlockLed,  
    cOutputVerlogLed,    
    cOutputDefrosterRl,  
    cOutputHornRl,
    cOutputRrFogLamp,    
    // Serial port
    cOutputDataImmobilzer,
    cOutputVerlog,        
    // PWM
    cOutputPwmRoomLamp,
    cOutputBuzzer
};
    
static const U16 TableTorIndex[cNbTorToControl]=
{    
    // TOR output
    ((U16)cDATPouLOCK_DOORSByteIndex           | (U16)((U16)cDATPouLOCK_DOORSBitIndex           << c8BitsShift)),
    ((U16)cDATPouUNLOCK_DOORSByteIndex         | (U16)((U16)cDATPouUNLOCK_DOORSBitIndex         << c8BitsShift)),
    ((U16)cDATPouUNLOCK_DRIVER_DOORByteIndex   | (U16)((U16)cDATPouUNLOCK_DRIVER_DOORBitIndex   << c8BitsShift)),
    ((U16)cDATPouDI_RIGHTByteIndex             | (U16)((U16)cDATPouDI_RIGHTBitIndex             << c8BitsShift)),
    ((U16)cDATPouDI_LEFTByteIndex              | (U16)((U16)cDATPouDI_LEFTBitIndex              << c8BitsShift)),
    ((U16)cDATPouFRONT_WIPERByteIndex          | (U16)((U16)cDATPouFRONT_WIPERBitIndex          << c8BitsShift)),
    ((U16)cDATPouRR_WIPER_RR_FOG_LAMPByteIndex | (U16)((U16)cDATPouRR_WIPER_RR_FOG_LAMPBitIndex << c8BitsShift)),
    ((U16)cDATPouBAT_LIGHT_TEMPOByteIndex      | (U16)((U16)cDATPouBAT_LIGHT_TEMPOBitIndex      << c8BitsShift)),
    ((U16)cDATPouOPEN_DOOR_LEDByteIndex        | (U16)((U16)cDATPouOPEN_DOOR_LEDBitIndex        << c8BitsShift)),
    ((U16)cDATPouVERLOG_LEDByteIndex           | (U16)((U16)cDATPouVERLOG_LEDBitIndex           << c8BitsShift)),
    ((U16)cDATPouDEFROSTERByteIndex            | (U16)((U16)cDATPouDEFROSTERBitIndex            << c8BitsShift)),
    ((U16)cDATPouHORN_RLByteIndex              | (U16)((U16)cDATPouHORN_RLBitIndex              << c8BitsShift)),
    ((U16)cDATPouRR_WIPER_RR_FOG_LAMPByteIndex | (U16)((U16)cDATPouRR_WIPER_RR_FOG_LAMPBitIndex << c8BitsShift)) 
};

#define cPAlaStateActivated     (U8)2   // prsFS_ASA-450

//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Constant exported data
//------------------------------------------------------------------------------
//QACJ 3211: akodzhh: Identifier is exported and used in LAP_KWP to init AFS session
const U8 TabIdentifierServiceSupportedInAfsSession[cNbServicesSupportedInAFS] =
          mInitAfsTabIdentifierServiceSupported();
//QACJ 3211: akodzhh: Identifier is exported and used in LAP_KWP to init AFS session
const tLAPKwpServiceFunction TabServiceSupportedInAfsSession[cNbServicesSupportedInAFS] =
          mInitAfsTabServiceSupported();

//------------------------------------------------------------------------------
// Local function prototypes
//------------------------------------------------------------------------------
static MEM_TYPE BOOL IsFragileOutput      (const U8 u8OutputRequestP);
static MEM_TYPE BOOL IsCpeOutput          (const U8 u8OutputRequestP);
static MEM_TYPE U8   WriteOuputByDiag     (const U8 u8OutputIndexP, const U8 u8ControlTypeP);
static MEM_TYPE U8   DeactiveOutputControl(const U8 u8OutputIndexP);
static MEM_TYPE U8   ReadIOCBILStatus     (const U8 u8OutputIndexP);

#ifdef BOOTLOADER_IS_SUPPORTED
static MEM_TYPE U8   ReadECU_LOG(U8* const pu8RespLengthP);
#endif

#ifdef X90_PROJECT
static MEM_TYPE void FreeActuator_Static(void);
#endif

//==============================================================================
//=========================== LOCAL FUNCTIONS ==================================
//==============================================================================

//==============================================================================
// DESCRIPTION:         IsFragileOutput
//
// PARAMETERS:          U8
//
// RETURN VALUE:        BOOL
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
static MEM_TYPE BOOL IsFragileOutput(const U8 u8OutputRequestP)
{
    return((TableIOCBLIDIdentifier[u8OutputRequestP] == cOutputLockDoors   )||
           (TableIOCBLIDIdentifier[u8OutputRequestP] == cOutputUnlockDoors )||
           (TableIOCBLIDIdentifier[u8OutputRequestP] == cOutputUnlockDrDoor)||
           (TableIOCBLIDIdentifier[u8OutputRequestP] == cOutputDiRight     )||
           (TableIOCBLIDIdentifier[u8OutputRequestP] == cOutputDiLeft      ));
           
}

//==============================================================================
// DESCRIPTION:         IsCpeOutput
//
// PARAMETERS:          U8
//
// RETURN VALUE:        BOOL
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
static MEM_TYPE BOOL IsCpeOutput(const U8 u8OutputRequestP)
{
    return((TableIOCBLIDIdentifier[u8OutputRequestP] == cOutputLockDoors   )||
           (TableIOCBLIDIdentifier[u8OutputRequestP] == cOutputUnlockDoors )||
           (TableIOCBLIDIdentifier[u8OutputRequestP] == cOutputUnlockDrDoor));
           
}

//==============================================================================
// DESCRIPTION:         WriteOuputByDiag
//
// PARAMETERS:          U8  u8OutputIndexP
//                      U8  u8ControlTypeP
//
// RETURN VALUE:        U8
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
static MEM_TYPE U8 WriteOuputByDiag( const U8 u8OutputIndexP, const U8 u8ControlTypeP)
{
    U8   u8RequestStatusL;
    BOOL bIsFragileOutput;

    u8RequestStatusL = cLAPKwpServiceIsCorrect;

    if(u8OutputIndexP <cNbTorToControl)
    { //TOR output
        bIsFragileOutput = IsFragileOutput(u8OutputIndexP);
        if((bIsFragileOutput == cTrue) &&
           (u8ControlTypeP == cIOCBLID_PermanentActivationParam))
        {
            u8RequestStatusL = cLAPKwpInvalidFormat;
        }
        else
        {   // output shared with Alarm - stop Alarm
            if(   (u8OutputIndexP == cDoorlockLedIndex)
                &&(mDATRead(U1Bit,IsAlaDiagEnabled, Default ) == cFalse) )
            {            
                TOSSendControl(cTOSControlAlaDiagEnable);
            }
            
            if(   (u8OutputIndexP == cHornRlIndex)
                &&(mDATRead(U8Bit,EEP_PerimeterAlarmState, Default ) == cPAlaStateActivated) )
            {
                // prsFS_ASA-452 IO control of horn is inhibited 
                u8RequestStatusL = cLAPKwpConditionNotCorrect;
            }
            else
            {
                mDATWriteTable(U1Bit,DATPouDiagBuffer,TableTorIndex[u8OutputIndexP],1,Default);
                mDATWriteTable(U1Bit,DATPouDiagMaskBuffer,TableTorIndex[u8OutputIndexP],1,Default);
            }
            
        }
    }
    else if(u8OutputIndexP <(cNbTorToControl+cNbSerialLineToControl))
    {// Serial Line Output
        
        if( u8OutputIndexP == cNbTorToControl)
        {
            mDATWrite(U1Bit,DO_DATA_IMMOBILIZERDiagEnabled, cTrue, Default);
            mDATWrite(U1Bit,DO_DATA_IMMOBILIZERDiag   ,1,Default);
        }
        else
        {
            mDATWrite(U1Bit,DO_VERLOGDiagEnabled, cTrue, Default);
            mDATWrite(U1Bit,DO_VERLOGDiag        ,1,Default);
        }
        
    }
    else if(u8OutputIndexP < cNbOutputToControl)
    {
        if(u8OutputIndexP == (cNbTorToControl+cNbSerialLineToControl))
        {   //PWM output declard is the room lamp
            mDATWrite(U1Bit,PWM_ROOMLAMPDiagMask, 1, Default); 
            mDATWrite(U8Bit,PWM_ROOMLAMPDiagRatio, cRoomLampDiagRatio, Default);
        }
        else
        {   
            mDATWrite(U16Bit,DATBuzDiagBuzz, cDiagBuzzFrequency, Default);
        }
    }
    //CCOV: akodzhh: can't be covered, no other outputs
    else
    {   // no other outputs
        mLIBassert(cFalse);
    }
    return(u8RequestStatusL);
}

//==============================================================================
// DESCRIPTION:         DeactiveOutputControl
//
// PARAMETERS:          U8  u8OutputIndexP
//
// RETURN VALUE:        U8  u8RequestStatusL
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
//QACJ 3208: akodzhh: Return value is intentionally ignored in two cases
static MEM_TYPE U8 DeactiveOutputControl(const U8 u8OutputIndexP)
{
    const U8 u8RequestStatusL = cLAPKwpServiceIsCorrect;
    tTOSSeqGraphStateType IOControlGraphState;

    IOControlGraphState = TOSSeqGraphState(cTOSSeqLAPAfsIOControlByLocalID);

    if( IOControlGraphState == cTOSSeqActiveGraph)
    {
        TOSSeqDeactivateGraph(cTOSSeqLAPAfsIOControlByLocalID);
    }

    if(u8OutputIndexP < cNbTorToControl)
    { //TOR output

        if(mDATReadTable(U1Bit,DATPouDiagBuffer,TableTorIndex[u8OutputIndexP],Default) == 1)
        {
            mDATWriteTable(U1Bit,DATPouDiagBuffer,TableTorIndex[u8OutputIndexP],0,Default);
            mDATWriteTable(U1Bit,DATPouDiagMaskBuffer,TableTorIndex[u8OutputIndexP],0,Default);

            if(  (u8OutputIndexP == cDoorlockLedIndex)
               &&(mDATRead(U1Bit,IsAlaDiagEnabled, Default ) == cTrue) )
            {            
                TOSSendControl(cTOSControlAlaDiagDisable);
            }
        }

        u8OutputRequestInProgress = cNoOutputControl;
        LAPKwpSetServiceIsFinished();
    }
    else if(u8OutputIndexP <(cNbTorToControl+cNbSerialLineToControl))
    {// Serial Line Output

        if( u8OutputIndexP == cNbTorToControl)
        {
            if(mDATRead(U1Bit, DO_DATA_IMMOBILIZERDiagEnabled, Default) == cTrue)
            {
                mDATWrite(U1Bit,DO_DATA_IMMOBILIZERDiag, 0, Default);
                mDATWrite(U1Bit,DO_DATA_IMMOBILIZERDiagEnabled, cFalse, Default);
            }
           
        }
        else
        {
            if(mDATRead(U1Bit, DO_VERLOGDiagEnabled,Default) == cTrue)
            {
                mDATWrite(U1Bit,DO_VERLOGDiag, 0, Default);
                mDATWrite(U1Bit,DO_VERLOGDiagEnabled, cFalse, Default);
            }
        }

        u8OutputRequestInProgress = cNoOutputControl;
        LAPKwpSetServiceIsFinished();

    }
    else if(u8OutputIndexP < cNbOutputToControl)
    { 
        if(u8OutputIndexP == (cNbTorToControl+cNbSerialLineToControl))
        {//PWM output
            mDATWrite(U1Bit,PWM_ROOMLAMPDiagMask, 0, Default); 
        }
        else // Buzzer
        {
            mDATControl(DATBuzDiagBuzz, Stop);
        }

        u8OutputRequestInProgress = cNoOutputControl;
        LAPKwpSetServiceIsFinished();
    }
    //CCOV: akodzhh: can't be covered, no other outputs
    else
    {
        mLIBassert(cFalse);
    }
    return(u8RequestStatusL);
}

//==============================================================================
// DESCRIPTION:         ReadIOCBILStatus
//
// PARAMETERS:          U8  u8OutputIndexP
//
// RETURN VALUE:        U8
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
static MEM_TYPE U8 ReadIOCBILStatus(const U8 u8OutputIndexP)
{
    U8    u8RequestStatusL;
    BOOL  bOutputIsActiveL;

    u8RequestStatusL = cIOCBLID_RoutineIsFinishedID;

    if(u8OutputIndexP <cNbTorToControl)
    { //TOR output

        bOutputIsActiveL = mDATReadTable(U1Bit,DATPouDiagMaskBuffer,TableTorIndex[u8OutputIndexP],Default);

    }
    else if(u8OutputIndexP <(cNbTorToControl+cNbSerialLineToControl))
    {// Serial Line Output
        
        if( u8OutputIndexP == cNbTorToControl)
        {
            bOutputIsActiveL = mDATRead(U1Bit,DO_DATA_IMMOBILIZERDiagEnabled,Default);
        }
        else
        {
            bOutputIsActiveL = mDATRead(U1Bit,DO_VERLOGDiagEnabled,Default);
        }

    }
    else if(u8OutputIndexP < cNbOutputToControl)
    { 
        if(u8OutputIndexP == (cNbTorToControl+cNbSerialLineToControl))
        {//PWM output

            bOutputIsActiveL = mDATRead(U1Bit,PWM_ROOMLAMPDiagMask, Default);
        }
        else // Buzzer
        {
            bOutputIsActiveL = mDATRead(U1Bit,IsBuzzerSoundPlaying, Default);
        }
        
    }
    //CCOV: akodzhh: can't be covered, no other outputs
    else
    {
        mLIBassert(cFalse);
        bOutputIsActiveL = cFalse;
    }

    if(bOutputIsActiveL == cTrue)
    {
        u8RequestStatusL = cIOCBLID_RoutineInProgressID;
    }

    return(u8RequestStatusL);
}

#ifdef BOOTLOADER_IS_SUPPORTED
//==============================================================================
// DESCRIPTION:         ReadECU_LOG
//
// PARAMETERS:          U8* pu8RespLengthP
//
// RETURN VALUE:        U8 Request Status
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
static MEM_TYPE U8 ReadECU_LOG(U8* const pu8RespLengthP)
{
    U8 u8RequestStatusL;
    BOOL bResult;
    //QACJ 3672: akodzhh: Pointer value is correct
    tpRetreiveLogZoneRecord RetreiveLogZoneRecord;

    U8 u8LogZoneIdL;

    //QACJ 0506: akodzhh: Pointer value is correct
    *pu8RespLengthP = 0;

    //QACJ 0305: akodzhh: Cast is intentional and safety
    if ((BOOL)mLAPKwpCheckBootloaderPresent() != cFalse)
    {
        RetreiveLogZoneRecord = 
            ((tBootLinkTable*)cLIBBooBootLinkTableAddress)->pRetreiveLogZoneRecord;

        u8LogZoneIdL = LAPKwpReadDiagnosticRequest(1);
        
        if (u8LogZoneIdL == cRDBLID_BCMIdentificationID)
        {
            // Request '21 80' shall return response to '21 FE'
            u8LogZoneIdL = cIdentLastLogZone;
        }
        else
        {
            // request in range 0xF0 - 0xFF
        }

        // call bootloader function to read log zone
        bResult = RetreiveLogZoneRecord(LAPKwpGetPtrDiagnosticResponse(cByte2), u8LogZoneIdL);
        
        if( bResult == cFalse )
        {
            u8RequestStatusL = cLAPKwpInvalidFormat;
        }
        else
        {
            u8RequestStatusL = cLAPKwpServiceIsCorrect;
            *pu8RespLengthP  = cRDBLIDAns_ECU_LOG_Lgth;
        }
        
    }
    else // bootloader not present
    {
        u8RequestStatusL = cLAPKwpInvalidFormat;
    }
    return u8RequestStatusL;
}
#endif //BOOTLOADER_IS_SUPPORTED

//==============================================================================
//=========================== EXPORTED FUNCTIONS ===============================
//==============================================================================
//==============================================================================
// DESCRIPTION:         LAPAfsTreatClearDiagnosticInformation
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
MEM_TYPE void LAPAfsTreatClearDiagnosticInformation(void)
{
    
    if( (mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cCLRDIReq_Lght) &&
        (LAPKwpReadDiagnosticRequest(1) == cCLRDIOptionByte) &&
        (LAPKwpReadDiagnosticRequest(cByte2) == 0x00)  )
    {
        LAPAfsClearFaultFlagsAndCounters();

        // Prepare the BCM response
        LAPKwpWriteDiagnosticResponse(1,cCLRDIOptionByte);
        LAPKwpWriteDiagnosticResponse(cByte2,0x00);
        LAPKwpPreparePositiveResponse(cByte3);
    }
    else
    {
        // negative response
        LAPKwpPrepareNegativeResponse(cLAPKwpInvalidFormat);
    }

    LAPKwpSetServiceIsFinished();
}

//==============================================================================
// DESCRIPTION:         LAPAfsClearFaultFlagsAndCounters
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
void LAPAfsClearFaultFlagsAndCounters (void)
{
#ifdef X90_PROJECT
    static MEM_TYPE void LAPAfsClearFaultFlagsAndCounters_Static(void);
    LAPAfsClearFaultFlagsAndCounters_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void LAPAfsClearFaultFlagsAndCounters_Static(void)
{
#endif
    
    // Erase the RAM fault flags
    mDATWrite(U1Bit, DefBtonCpeOuv, 0, Default);
    mDATWrite(U1Bit, DefBtonCpeFer, 0, Default);

    mDATWrite(U1Bit, DefAFAV,       0, Default);
    mDATWrite(U1Bit, DefAFAR,       0, Default);
    mDATWrite(U1Bit, DefAirbag,     0, Default);
    mDATWrite(U1Bit, DefClignL,     0, Default);
    mDATWrite(U1Bit, DefClignR,     0, Default);
    mDATWrite(U1Bit, DefEEPROM,     0, Default);
    
    mDATWrite(U1Bit, DefTrpShortCircuitToBat , 0, Default);
    mDATWrite(U1Bit, DefTrpShortCircuitToGnd , 0, Default);
    
    mDATWrite(U1Bit, DefVerlogToGnd,0, Default);
    mDATWrite(U1Bit, DefVerlogToBat,0, Default);
    mDATWrite(U1Bit, DefVerlogLedCC,0, Default);
    mDATWrite(U1Bit, DefDfrToBat,   0, Default);
    mDATWrite(U1Bit, DefDfrToGnd,   0, Default);
  
    mDATWrite(U1Bit, DefHornCCBat,0, Default);
    mDATWrite(U1Bit, DefHornCCGnd,0, Default);
    mDATWrite(U1Bit, DefKLineCC,0, Default);
    mDATWrite(U1Bit, DefDoorlockLedCC,0, Default);
    mDATWrite(U1Bit, DefRrwCC,0, Default);        
    
    mDATWrite(U8Bit, DATTrpAuthentTryCounter , 0, Default);  // compt_nb_int
    mDATWrite(U8Bit, COD_ERR_APP , 0, Default);
    

    // Erase the eeprom default flag
    mDATWrite(U1Bit, EEP_DefAfav          , 0, Default);
    mDATWrite(U1Bit, EEP_DefAfar          , 0, Default);
    mDATWrite(U1Bit, EEP_DefAirbag        , 0, Default);
    mDATWrite(U1Bit, EEP_DefClignL        , 0, Default);
    mDATWrite(U1Bit, EEP_DefClignR        , 0, Default);
    mDATWrite(U1Bit, EEP_DefEeprom        , 0, Default);
    mDATWrite(U1Bit, EEP_DefTrpToBat      , 0, Default);
    mDATWrite(U1Bit, EEP_DefTrpToGnd      , 0, Default);
    mDATWrite(U1Bit, EEP_DefVerlogToGnd   , 0, Default);
    mDATWrite(U1Bit, EEP_DefVerlogToBat   , 0, Default);
    mDATWrite(U1Bit, EEP_DefDfrToBat      , 0, Default);
    mDATWrite(U1Bit, EEP_DefDfrToGnd      , 0, Default);
    mDATWrite(U1Bit, EEP_DefHornCCBat     , 0, Default);
    mDATWrite(U1Bit, EEP_DefHornCCGnd     , 0, Default);
    mDATWrite(U1Bit, EEP_DefKLineCC       , 0, Default);
    mDATWrite(U1Bit, EEP_DefDoorlockLedCC , 0, Default);
    mDATWrite(U1Bit, EEP_DefVerlogLedCC   , 0, Default);
    mDATWrite(U1Bit, EEP_DefRrwCC         , 0, Default);


    // Erase Immo data 
    mDATWrite(U8Bit, EEP_ResynchroSuccessfulCounter, 0, Default);
    mDATWrite(U8Bit, EEP_ResynchroFailureCounter   , 0, Default);
    mDATWrite(U8Bit, EEP_AuthentDelayedCounter     , 0, Default);
    mDATWrite(U8Bit, EEP_AuthentFailureCounter     , 0, Default);

    // Erase the reset counter
    mDATWrite(U8Bit, EEP_ResetCount, 0, Default);
    // Erase the collision counter
    mDATWrite(U8Bit, EEP_CrashCount, 0, Default);
}

//==============================================================================
// DESCRIPTION:         LAPAfsTreatStartRoutineByLocalIdentifierService
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
MEM_TYPE void LAPAfsTreatStartRoutineByLocalIdentifierService(void)
{
    U8  u8AnswerStatusL;
    U8  u8RoutineStatusL;
    
    u8AnswerStatusL = cLAPKwpServiceIsCorrect;
    u8RoutineStatusL = cLAPKwpRoutineNotActivated;

    if  ( mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cSRBIDReq_Lght )
    {
        if (LAPKwpReadDiagnosticRequest(cByte2) == 0x00) // Launch the routine
        {

            switch (LAPKwpReadDiagnosticRequest(1))
            {

            case cSRBID_StartPermanentAuthenticationID : 
                if ( (mDATRead(U1Bit, EEP_BCMBlank, Default) ==0)    
                   &&(mDATRead(U1Bit, PWR_IGN, Default) == 0))
                {
                    TOSSendControl(cTOSControlStartPermanentAuthentication);
                    u8RoutineStatusL = cSRBID_StartRoutineAccepted; // Cm006299: accept a status of 00h to be compatible with Polaris BCM 
                    u8RoutineRequestInProgress = cSRBID_StartPermanentAuthenticationID;
                }
                else
                {
                    u8AnswerStatusL = cLAPKwpConditionNotCorrect;
                }
                break;

            case cSRBID_EraseAfterSalesCodeID :

            #ifdef X90_PROJECT
                //amanevd: 6 NOPs added so that object file produced from rev. 1.64 to be identical with 1.65
                NOP();
                NOP();
                NOP();
                NOP();
                NOP();
                NOP();
            #endif

                // Stop the active routine (Only the routine permanent authentication can be active)
                TOSSendControl(cTOSControlStopPermanentAuthentication);
                u8RoutineRequestInProgress = cNoRoutineControl;

                // prsFS_IMMO-675
                mDATWrite(U1Bit, EEP_EraseAFSCodeRequest, 1, Default); // cde_eff_code_recu

                u8RoutineStatusL = cLAPKwpRoutineTerminatedOK;
                break;

            case cSRBID_TestVirginKeyID :
                if ((mDATRead(U1Bit, PWR_IGN, Default) == 1)
                  &&(mDATRead(U8Bit, LearningModeInProgress, Default) == cDATNoLearningMode))
                {
                    // Stop the active routine (Only the routine permanent authentication can be active)
                    TOSSendControl(cTOSControlStopPermanentAuthentication);  
                    u8RoutineRequestInProgress = cSRBID_TestVirginKeyID;

                    TOSSendControl(cTOSControlStartTestVirginKey);  
                    u8RoutineStatusL = cLAPKwpRoutineInProgress;
                }
                else
                {
                    u8AnswerStatusL = cLAPKwpConditionNotCorrect;
                }
                break;

            default :
                u8AnswerStatusL = 
                    LIBCfdExecuteConfDiagRequest(   LAPKwpReadDiagnosticRequest(0),
                                                    LAPKwpReadDiagnosticRequest(1),
                                                    &u8RoutineStatusL);
                u8RoutineRequestInProgress = cNoRoutineControl;
                break;
            } // switch LID

        }
        else if (LAPKwpReadDiagnosticRequest(cByte2) == 0x01) // Request status
        {
            switch (LAPKwpReadDiagnosticRequest(1)) // Routine ID
            {
                case cSRBID_StartPermanentAuthenticationID:
                case cSRBID_EraseAfterSalesCodeID:
                if (u8RoutineRequestInProgress == LAPKwpReadDiagnosticRequest(1))
                {
                    u8RoutineStatusL = cLAPKwpRoutineInProgress;
                }
                else
                {
                    u8RoutineStatusL = cLAPKwpRoutineTerminatedOK;
                }
                break;

                case cSRBID_TestVirginKeyID:

                if (u8RoutineRequestInProgress == LAPKwpReadDiagnosticRequest(1))
                {
                    if(cDATTrpServiceInProgress == mDATRead(U8Bit, DATTrpAuthenticationState, Default))
                    {
                        u8RoutineStatusL = cLAPKwpRoutineInProgress;
                    }
                    else if(cFalse != mDATRead(U1Bit, VirginKeyAuthentOk, Default))
                    {
                        u8RoutineStatusL = cLAPKwpRoutineTerminatedOK;
                    }
                    else
                    {
                        u8RoutineStatusL = cLAPKwpRoutineTerminatedNOK;
                    }
                }
                else
                {
                    u8RoutineStatusL = cLAPKwpRoutineNotActivated;
                }
                break;

                default:

                //QACJ 3416: akodzhh: There is no side effedct
                if(cFalse != LIBCfdIsConfDiagRoutineRequest(LAPKwpReadDiagnosticRequest(1)))
                {
                    //CCOV: akodzhh: can't be covered, available for now Cfd routines are always finished.
                    if (u8RoutineRequestInProgress == LAPKwpReadDiagnosticRequest(1))
                    {
                        u8RoutineStatusL = cLAPKwpRoutineInProgress;
                    }
                    else
                    {
                        u8RoutineStatusL = cLAPKwpRoutineTerminatedOK;
                    }
                }
                else
                {
                    // Not supported routine ID
                    u8AnswerStatusL = cLAPKwpInvalidFormat;
                }
                break;
            }
                
        }
        else
        {
            u8AnswerStatusL = cLAPKwpInvalidFormat;
        }
    }
    else    // invalid length
    {
        u8AnswerStatusL = cLAPKwpInvalidFormat;
    }

    if (u8AnswerStatusL == cLAPKwpServiceIsCorrect)
    {
        LAPKwpWriteDiagnosticResponse(1,LAPKwpReadDiagnosticRequest(1));
        LAPKwpWriteDiagnosticResponse(cByte2,u8RoutineStatusL);
        LAPKwpPreparePositiveResponse(cByte3);
    }
    else
    {   // negative response
        LAPKwpPrepareNegativeResponse(u8AnswerStatusL);
    }
    LAPKwpSetServiceIsFinished();
}


//==============================================================================
// DESCRIPTION:         LAPAfsTreatStopRoutineByLocalIdentifierService
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
MEM_TYPE void LAPAfsTreatStopRoutineByLocalIdentifierService(void)
{
    if ( (  (LAPKwpReadDiagnosticRequest(1) == u8RoutineRequestInProgress) ||
            (LAPKwpReadDiagnosticRequest(1) == 0x00))&&
         (LAPKwpReadDiagnosticRequest(cByte2) == 0x00) )
    {  
        LAPKwpWriteDiagnosticResponse(1,u8RoutineRequestInProgress);
        LAPKwpWriteDiagnosticResponse(cByte2,cLAPKwpRoutineTerminatedOK);
        LAPKwpPreparePositiveResponse(cByte3);

        u8RoutineRequestInProgress = cNoRoutineControl;
        TOSSendControl(cTOSControlStopPermanentAuthentication);  
    }
    else
    {
        LAPKwpPrepareNegativeResponse(cLAPKwpInvalidFormat);
    }
    LAPKwpSetServiceIsFinished();
}

//==============================================================================
// DESCRIPTION:         LAPAfsTreatWriteDataByLocalIdentifierService
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
MEM_TYPE void LAPAfsTreatWriteDataByLocalIdentifierService(void)
{

    U8  u8RequestStatusL;
    U8  u8BitPositionL;
    U8  u8BytePositionL;
    U8  u8BitToWriteL;
    U8  u8IndexL;
    
    u8RequestStatusL = cLAPKwpServiceIsCorrect;

    switch (LAPKwpReadDiagnosticRequest(1))
    {

    case cWDBLID_GeneralParamBitToBitID:
        
        if(LAPKwpIsServiceTreated() == cFalse)    
        {
            u8BitPositionL =  LAPKwpReadDiagnosticRequest(cByte2);
            u8BytePositionL = LAPKwpReadDiagnosticRequest(cByte3);
            if (LAPKwpReadDiagnosticRequest(cByte4) == 0)
            {
                u8BitToWriteL = 0;
            }
            else
            {
                u8BitToWriteL = 1;
            }

            if (  ( mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cWDBLIDReq_GeneralParamBitToBit_Lgth)
                &&( u8BytePositionL >= 1) && ( u8BytePositionL <= cByte4)
                &&( u8BitPositionL  < c8Bits)  )
            {    
                
                u8IndexL = (U8)(((U8)(u8BytePositionL-1)<<(U8)c3Bits)| u8BitPositionL);

                switch(u8IndexL)
                {
                case cIndexDEM_SURVIT:        
                    mDATWrite(U1Bit,EEP_DEM_SURVIT,    u8BitToWriteL, Immediate);
                    break;                                                     
                case cIndexCALALPRI:        
                    mDATWrite(U1Bit,EEP_CALALPRI,      u8BitToWriteL, Immediate);
                    break;                                                     
                case cIndexCALVERDI:        
                    // Cm006292: Request for this parameter should not be rejected
                    LAPKwpSetServiceIsFinished();
                    break;
                case cIndexAUTDEGIVRAGE:        
                    mDATWrite(U1Bit,EEP_AUTDEGIVRAGE,  u8BitToWriteL, Immediate);
                    break;                                                     
                case cIndexRELAIS_DEM:        
                    mDATWrite(U1Bit,EEP_RELAIS_DEM,    u8BitToWriteL, Immediate);
                    break;                                                     
                case cIndexDETCHOC:        
                    mDATWrite(U1Bit,EEP_DETCHOC,       u8BitToWriteL, Immediate);
                    break;                                                     
                case cIndexCONDATMPO:        
                    mDATWrite(U1Bit,EEP_CONDATMPO,     u8BitToWriteL, Immediate);
                    break;                                                     
                case cIndexCONDAROU:        
                    mDATWrite(U1Bit,EEP_CONDAROU,      u8BitToWriteL, Immediate);
                    break;                                                     
                case cIndexCARCLIENT:        
                    mDATWrite(U1Bit,EEP_CARCLIENT,     u8BitToWriteL, Immediate);
                    break;                                                     
                case cIndexALIM_PLAF:        
                    mDATWrite(U1Bit,EEP_ALIM_PLAF,     u8BitToWriteL, Immediate);
                    break;                                                     
                case cIndexPIL_PLAF:        
                    mDATWrite(U1Bit,EEP_PIL_PLAF,      u8BitToWriteL, Immediate);
                    break;                                                     
                case cIndexVERLOG_ALGO:
                    // do nothing: for compatibility
                    break;
                case cIndexSDO:        
                    mDATWrite(U1Bit,EEP_SDO,           u8BitToWriteL, Immediate);
                    break;
                case cIndexCPE_IMPULS:        
                    mDATWrite(U1Bit,EEP_CPE_IMPULS,    u8BitToWriteL, Immediate);
                    break;                                                     
                case cIndexFEU_BROUILLARD:
                    if(u8BitToWriteL == 1) // prsFS_EXL-211
                    {
                        // inhibit RR_Wiper function
                        mDATWrite(U1Bit,EEP_EV_ARR, 0, Immediate);    
                    }
                    mDATWrite(U1Bit,EEP_FEU_BROUILLARD,u8BitToWriteL, Immediate);
                    break;                                                     
                case cIndexEV_ARR:
                    if(u8BitToWriteL == 1) // prsFS_EXL-212
                    {
                        // inhibit RR_Fog function 
                        mDATWrite(U1Bit,EEP_FEU_BROUILLARD, 0, Immediate);    
                    }
                    mDATWrite(U1Bit,EEP_EV_ARR,        u8BitToWriteL, Immediate);
                    break;                                                     
                case cIndexINFO_REGIME:        
                    mDATWrite(U1Bit,EEP_INFO_REGIME,   u8BitToWriteL, Immediate);
                    break;                                                     
                case cIndexCLI_REM:        
                    mDATWrite(U1Bit,EEP_CLI_REM,       u8BitToWriteL, Immediate);
                    break;                                                     
                case cIndexCAD_BAGUE_AV:        
                    mDATWrite(U1Bit,EEP_CAD_BAGUE_AV,  u8BitToWriteL, Immediate);
                    break;                                                     
                case cIndexAUTCRASH:        
                    mDATWrite(U1Bit,EEP_AUTCRASH,      u8BitToWriteL, Immediate);
                    break;                                                     
                case cIndexAUTVERLOG:        
                    mDATWrite(U1Bit,EEP_AUTVERLOG,     u8BitToWriteL, Immediate);
                    break;                                                     
                case cIndexAUTPLAF:        
                    mDATWrite(U1Bit,EEP_AUTPLAF,       u8BitToWriteL, Immediate);
                    break;                                                     
                case cIndexKEY_BUTTON:        
                    mDATWrite(U1Bit,EEP_KEY_BUTTON,   u8BitToWriteL, Immediate);
                    break;                                                     
                case cIndexCALALARM:
                    // prsFS_ASA-253
                    if(mDATRead(U1Bit, EEP_CAR_SECURE, Default) == cFalse)
                    {
                        mDATWrite(U1Bit,EEP_CALALARM, u8BitToWriteL, Immediate);
                    }
                    else
                    {
                        u8RequestStatusL = cLAPKwpConditionNotCorrect;
                        LAPKwpSetServiceIsFinished();
                    }                    
                    break;                                                     
                case cIndexCALULKTR:       
                    mDATWrite(U1Bit,EEP_CALULKTR,      u8BitToWriteL, Immediate);
                    break;                                                     
                case cIndexAUTRECRF:        
                    mDATWrite(U1Bit,EEP_AUTRECRF,      u8BitToWriteL, Immediate);
                    break;                                                     
                case cIndexOUBLICEINTURE:        
                    mDATWrite(U1Bit,EEP_OUBLICEINTURE, u8BitToWriteL, Immediate);
                    break;
                default:
                    // reserved bit    
                    u8RequestStatusL = cLAPKwpInvalidFormat;
                    LAPKwpSetServiceIsFinished();
                    break;
                }
                
                if( (u8RequestStatusL == cLAPKwpServiceIsCorrect)
                  &&(u8IndexL != cIndexCALVERDI))
                {
                    LAPKwpSetServiceIsTreated();
                }
                
            }
            else
            {
                u8RequestStatusL = cLAPKwpInvalidFormat;
                LAPKwpSetServiceIsFinished();
            }
            
        }
        else     // service is already started, waiting write to be finished
        {
            if(mDATRead(U1Bit,IsEepGroupGeneralParameterBankProcessing,Default) == cFalse)
            {
                if(mDATRead(U1Bit,IsEepGroupGeneralParameterBankWriteOk,Default) == cFalse)
                {
                    u8RequestStatusL = cLAPKwpFaultUponWriting;
                }

                LAPKwpSetServiceIsFinished();       // prsFS_DIAG-919
            }

        }
        break;
    

    case cWDBLID_FactoryConfigID :
        if(LAPKwpIsServiceTreated() == cFalse)    
        {
            if(mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cWDBLIDReq_FactoryConfig_Lgth)
            {
                switch(LAPKwpReadDiagnosticRequest(cByte2))
                {
                case cNbTPS_RETARD_DETRESSE:
                    mDATWrite(U8Bit, EEP_TPS_RETARD_DETRESSE,LAPKwpReadDiagnosticRequest(cByte3), Default);
                    break;
                case cNbTIMER_DETRESSE:        
                    mDATWrite(U8Bit, EEP_TIMER_DETRESSE,     LAPKwpReadDiagnosticRequest(cByte3), Default);
                    break;
                case cNbTPS_APC:
                    mDATWrite(U8Bit, EEP_TPS_APC,            LAPKwpReadDiagnosticRequest(cByte3), Default);
                    break;
                case cNbTPS_PLAF:
                    mDATWrite(U8Bit, EEP_TPS_PLAF,           LAPKwpReadDiagnosticRequest(cByte3), Default);
                    break;
                case cNbTPS_ESSUIE_MINI:        
                    mDATWrite(U8Bit, EEP_TPS_ESSUIE_MINI,    LAPKwpReadDiagnosticRequest(cByte3), Default);
                    break;
                case cNbTPS_MAX_COUPLBLOC:
                    mDATWrite(U8Bit, EEP_TPS_MAX_COUPLBLOC,  LAPKwpReadDiagnosticRequest(cByte3), Default);
                    break;
                case cNbTPS_ARRET:
                    mDATWrite(U8Bit, EEP_TPS_ARRET,          LAPKwpReadDiagnosticRequest(cByte3), Default);
                    break;
                case cNbTPS_REPRISE:
                    mDATWrite(U8Bit, EEP_TPS_REPRISE,        LAPKwpReadDiagnosticRequest(cByte3), Default);
                    break;
                case cNbTPS_FILT_AF:
                    mDATWrite(U8Bit, EEP_TPS_FILT_AF,         LAPKwpReadDiagnosticRequest(cByte3), Default);
                    break;
                case cNbTPS_POSIT_BALAIS:
                    mDATWrite(U8Bit, EEP_TPS_POSIT_BALAIS,   LAPKwpReadDiagnosticRequest(cByte3), Default);
                    break;
                case cNbPROLONG_APPUI_COURT:
                    mDATWrite(U8Bit, EEP_PROLONG_APPUI_COURT,LAPKwpReadDiagnosticRequest(cByte3), Default);
                    break;
                case cNbPROLONG_APPUI_LONG:
                    mDATWrite(U8Bit, EEP_PROLONG_APPUI_LONG, LAPKwpReadDiagnosticRequest(cByte3), Default);
                    break;
                case cNbTPS_APPUILAV:
                    mDATWrite(U8Bit, EEP_TPS_APPUILAV,       LAPKwpReadDiagnosticRequest(cByte3), Default);
                    break;
                case cNbTPS_POSIT_BALAIS_AR:
                    mDATWrite(U8Bit, EEP_TPS_POSIT_BALAIS_AR,LAPKwpReadDiagnosticRequest(cByte3), Default);
                    break;
                case cNbPROLONG_APPUI_ARR:
                    mDATWrite(U8Bit, EEP_PROLONG_APPUI_ARR,  LAPKwpReadDiagnosticRequest(cByte3), Default);
                    break;
                case cNbSEUIL_VIT_CONDAROU:
                    mDATWrite(U8Bit, EEP_SEUIL_VIT_CONDAROU, LAPKwpReadDiagnosticRequest(cByte3), Default);
                    break;
                case cNbTPS_COM_MOTEUR:
                    mDATWrite(U8Bit, EEP_TPS_COM_MOTEUR,     LAPKwpReadDiagnosticRequest(cByte3), Default);
                    break;
                case cNbNBCOM_MAX:
                    mDATWrite(U8Bit, EEP_NBCOM_MAX,          LAPKwpReadDiagnosticRequest(cByte3), Default);
                    break;
                case cNbTPS_REF:
                    mDATWrite(U8Bit, EEP_TPS_REF,            LAPKwpReadDiagnosticRequest(cByte3), Default);
                    break;
                case cNbTIMER_RECONDA_AUTO:
                    mDATWrite(U8Bit, EEP_TIMER_RECONDA_AUTO, LAPKwpReadDiagnosticRequest(cByte3), Default);
                    break;
                case cNbN_MISE_APC:
                    mDATWrite(U8Bit, EEP_N_MISE_APC,         LAPKwpReadDiagnosticRequest(cByte3), Default);
                    break;
                case cNbTMPMERA:
                    mDATWrite(U8Bit, EEP_TimeOutMERA,            LAPKwpReadDiagnosticRequest(cByte3), Default);
                    break;
                case cNbTPS_OUVPORTE:
                    mDATWrite(U8Bit, EEP_TPS_OUVPORTE,       LAPKwpReadDiagnosticRequest(cByte3), Default);
                    break;
                case cNbTPS_TEMPO_DEG:
                    mDATWrite(U8Bit, EEP_TPS_TEMPO_DEG,      LAPKwpReadDiagnosticRequest(cByte3), Default);
                    break;
                case cNbTPS_IMPUL_MINI:
                    mDATWrite(U8Bit, EEP_TPS_IMPUL_MINI,     LAPKwpReadDiagnosticRequest(cByte3), Default);
                    break;
                case cNbSBR_ACTIVE_SPEED_THRESH_TP:
                    mDATWrite(U8Bit, EEP_SBR_ACTIVE_SPEED_THRESH_TP,    LAPKwpReadDiagnosticRequest(cByte3), Default);
                    break;
                case cNbSBR_TIMEOUT_TM_TP:
                    mDATWrite(U8Bit, EEP_SBR_TIMEOUT_TM_TP,            LAPKwpReadDiagnosticRequest(cByte3), Default);
                    break;
                case cNbMAX_NB_ALERT_SEQUENCES_TP:
                    mDATWrite(U8Bit, EEP_MAX_NB_ALERT_SEQUENCES_TP,     LAPKwpReadDiagnosticRequest(cByte3), Default);
                    break;
                case cNbTPS_BUZ_CLI:
                    mDATWrite(U8Bit, EEP_TPS_BUZ_CLI,                   LAPKwpReadDiagnosticRequest(cByte3), Default);
                    break;
                case cNbTPS_CLI:
                    mDATWrite(U8Bit, EEP_TPS_CLI,                       LAPKwpReadDiagnosticRequest(cByte3), Default);
                    break;
                case cNbTPS_CLIDEGRAD:
                    mDATWrite(U8Bit, EEP_TPS_CLIDEGRAD,                 LAPKwpReadDiagnosticRequest(cByte3), Default);
                    break;      
                default:
                    u8RequestStatusL = cLAPKwpInvalidFormat;
                    LAPKwpSetServiceIsFinished();
                    break; 
                }
            
                if (u8RequestStatusL == cLAPKwpServiceIsCorrect)
                {
                    mDATControl(Eep,UpDateEepGroupFactoryConfigBank);
                    LAPKwpSetServiceIsTreated();
                }    
            
            }
            else
            {
                u8RequestStatusL = cLAPKwpInvalidFormat;
                LAPKwpSetServiceIsFinished();
            }

        }
        else     // service is already started, waiting write to be finished
        {
            if(mDATRead(U1Bit,IsEepGroupFactoryConfigBankProcessing,Default) == cFalse)
            {
                if(mDATRead(U1Bit,IsEepGroupFactoryConfigBankWriteOk,Default) == cFalse)
                {
                    u8RequestStatusL = cLAPKwpFaultUponWriting;
                }

                LAPKwpSetServiceIsFinished();   // prsFS_DIAG-919
            }

        }

        break;

     case cWDBLID_VINID :
        if(LAPKwpIsServiceTreated() == cFalse)    
        {
        
            if ( mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cWDBLIDReq_VIN_Lgth)
            {
                for(u8IndexL=0; u8IndexL<cVIN_Lgth; u8IndexL++)
                {
                    mDATWriteTable(U8Bit,EEP_VehicleIdentifierNumber,u8IndexL,LAPKwpReadDiagnosticRequest(cByte2+u8IndexL),Immediate);
                }
                LAPKwpSetServiceIsTreated();
            }
            else
            {
                u8RequestStatusL = cLAPKwpInvalidFormat;
                LAPKwpSetServiceIsFinished();
            }
        }
        else     // service is already started, waiting write to be finished
        {
            if(mDATRead(U1Bit,IsEepGroupVINBankProcessing,Default) == cFalse)
            {
                if(mDATRead(U1Bit,IsEepGroupVINBankWriteOk,Default) == cFalse)
                {
                    u8RequestStatusL = cLAPKwpFaultUponWriting;
                }

                LAPKwpSetServiceIsFinished();   // prsFS_DIAG-919
            }

        }
        break;

    default :
        u8RequestStatusL = cLAPKwpInvalidFormat;
        LAPKwpSetServiceIsFinished();
        break;
    }

    
    if( LAPKwpIsServiceTreated() == cFalse )
    {
        if(u8RequestStatusL != cLAPKwpServiceIsCorrect)
        {
            LAPKwpPrepareNegativeResponse(u8RequestStatusL);
        }
        else
        {
            LAPKwpWriteDiagnosticResponse(1,LAPKwpReadDiagnosticRequest(1));
            LAPKwpPreparePositiveResponse(cByte2);
        }
        

    }
    
}

//==============================================================================
// DESCRIPTION:         LAPAfsTreatReadDataByLocalIdentifierService
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
MEM_TYPE void LAPAfsTreatReadDataByLocalIdentifierService(void)
{
    U8  u8RequestStatusL;
    U8  u8IndexL;
    U8  u8TempVarL;
    U8  u8ResponseLengthL ;
    U8  u8PlafValueL;
    U8  u8BytePos;
    BOOL bDiagVERLOGON;
  
    u8RequestStatusL = cLAPKwpServiceIsCorrect;
    u8ResponseLengthL = 0;
    if (mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cRDBLIDReq_Lgth)
    {
        switch (LAPKwpReadDiagnosticRequest(1))
        {
        case cRDBLID_DefaultDataID : 
            for(u8IndexL=0;u8IndexL<(cRDBLIDAns_DefaultData_Lgth- cDataOffset);u8IndexL++)
            {
                LAPKwpWriteDiagnosticResponse(cByte2+u8IndexL, 0x00);
            }
            u8IndexL = cByte2;
            //Read Faults Present
            //Byte 1
            //QACJ 3198: akodzhh: Variable is initialized and then modified bit by bit before being used
            u8TempVarL = 0x00;
            u8TempVarL =(mDATRead(U1Bit, DefBtonCpeOuv, Default))      |
                        (mDATRead(U1Bit, DefBtonCpeFer, Default)  <<c1Bits) |
                        (mDATRead(U1Bit, DefAFAV,       Default)  <<c2Bits) |
                        (mDATRead(U1Bit, DefAFAR,       Default)  <<c3Bits) |
                        (mDATRead(U1Bit, DefAirbag,     Default)  <<c4Bits) |
                        (((U1)(mDATRead(U1Bit, DefClignL , Default)||
                               mDATRead(U1Bit, DefClignR , Default)  ) & (U1)1U)<<c6Bits) |
                        (mDATRead(U1Bit, DefEEPROM,     Default)  <<c7Bits);

            LAPKwpWriteDiagnosticResponse(u8IndexL,u8TempVarL);
            u8IndexL++;
            //QACJ 3198: akodzhh: Variable is initialized and then modified bit by bit before being used    
            u8TempVarL = 0x00;
            u8TempVarL =(mDATRead(U1Bit, DefTrpShortCircuitToBat, Default)      <<c4Bits) |
                        (mDATRead(U1Bit, DefTrpShortCircuitToGnd, Default)      <<c5Bits);

            LAPKwpWriteDiagnosticResponse(u8IndexL,u8TempVarL);
            u8IndexL++;
            //QACJ 3198: akodzhh: Variable is initialized and then modified bit by bit before being used
            u8TempVarL = 0x00;
            u8TempVarL =(mDATRead(U1Bit, DefVerlogToGnd, Default)   <<c1Bits) |   //DefSireneToGnd
                        (mDATRead(U1Bit, DefVerlogToBat, Default)   <<c2Bits) |   //DefSireneToBat
                        (mDATRead(U1Bit, DefDfrToBat,    Default)   <<c6Bits) |   //DEF_CC+_LARD  (DEFROSTER_RL)
                        (mDATRead(U1Bit, DefDfrToGnd,    Default)   <<c7Bits);    //DEF_CO_LARD   (DEFROSTER_RL)

            LAPKwpWriteDiagnosticResponse(u8IndexL,u8TempVarL);
            u8IndexL++;

            //QACJ 3198: akodzhh: Variable is initialized and then modified bit by bit before being used
            u8TempVarL = 0x00;
            u8TempVarL =   (mDATRead(U1Bit, DefHornCCBat,       Default))    |         //DEF_CC+_DEMARREUR
                           (mDATRead(U1Bit, DefHornCCGnd,       Default)<<c1Bits) |       //DEF_CO_DEMARREUR
                           (mDATRead(U1Bit, DefDoorlockLedCC,   Default)<<c6Bits);

            LAPKwpWriteDiagnosticResponse(u8IndexL,u8TempVarL);
            u8IndexL++;

            LAPKwpWriteDiagnosticResponse(u8IndexL, mDATRead(U8Bit, DATTrpAuthentTryCounter, Default));
            u8IndexL++;
            
            LAPKwpWriteDiagnosticResponse(u8IndexL, mDATRead(U8Bit, COD_ERR_APP, Default));
            u8IndexL++;


            //Read EEP Stored Faults
            //QACJ 3198: akodzhh: Variable is initialized and then modified bit by bit before being used
            u8TempVarL = 0x00;
            u8TempVarL =(mDATRead(U1Bit, EEP_DefAfav  , Default)     <<c2Bits) |
                        (mDATRead(U1Bit, EEP_DefAfar  , Default)     <<c3Bits) |
                        (mDATRead(U1Bit, EEP_DefAirbag, Default)     <<c4Bits) |
                        (((U1)( mDATRead(U1Bit, EEP_DefClignL , Default)
                              ||mDATRead(U1Bit, EEP_DefClignR , Default) )&(U1)1)<<c6Bits) | 
                        (mDATRead(U1Bit, EEP_DefEeprom, Default)     <<c7Bits);

            LAPKwpWriteDiagnosticResponse(u8IndexL,u8TempVarL);
            u8IndexL++;
            //QACJ 3198: akodzhh: Variable is initialized and then modified bit by bit before being used
            u8TempVarL = 0x00;
            u8TempVarL =(mDATRead(U1Bit, EEP_DefTrpToBat, Default)      <<c4Bits) |
                        (mDATRead(U1Bit, EEP_DefTrpToGnd, Default)      <<c5Bits);

            LAPKwpWriteDiagnosticResponse(u8IndexL,u8TempVarL);
            u8IndexL++;
            //QACJ 3198: akodzhh: Variable is initialized and then modified bit by bit before being used
            u8TempVarL = 0x00;
            u8TempVarL =(mDATRead(U1Bit, EEP_DefVerlogToGnd, Default)   <<c1Bits) |   //DefSireneToGnd
                        (mDATRead(U1Bit, EEP_DefVerlogToBat, Default)   <<c2Bits) |   //DefSireneToBat
                        (mDATRead(U1Bit, EEP_DefDfrToBat, Default)      <<c6Bits) |   //DEF_CC+_LARD  (DEFROSTER_RL)
                        (mDATRead(U1Bit, EEP_DefDfrToGnd, Default)      <<c7Bits);    //DEF_CO_LARD   (DEFROSTER_RL)

            LAPKwpWriteDiagnosticResponse(u8IndexL,u8TempVarL);
            u8IndexL++;

            //QACJ 3198: akodzhh: Variable is initialized and then modified bit by bit before being used
            u8TempVarL = 0x00;
            u8TempVarL =   (mDATRead(U1Bit, EEP_DefHornCCBat,       Default))    |  //DEF_CC+_DEMARREUR
                           (mDATRead(U1Bit, EEP_DefHornCCGnd,       Default)<<c1Bits) |  //DEF_CO_DEMARREUR 
                           (mDATRead(U1Bit, EEP_DefDoorlockLedCC,   Default)<<c6Bits);

            LAPKwpWriteDiagnosticResponse(u8IndexL,u8TempVarL);
            u8IndexL++;


            LAPKwpWriteDiagnosticResponse(u8IndexL,mDATRead(U8Bit, EEP_ResynchroSuccessfulCounter, Default));
            u8IndexL++;
            LAPKwpWriteDiagnosticResponse(u8IndexL,mDATRead(U8Bit, EEP_ResynchroFailureCounter,    Default));
            u8IndexL++;
            LAPKwpWriteDiagnosticResponse(u8IndexL,mDATRead(U8Bit, EEP_AuthentDelayedCounter,      Default));
            u8IndexL++;
            LAPKwpWriteDiagnosticResponse(u8IndexL,mDATRead(U8Bit, EEP_AuthentFailureCounter,      Default));
            u8IndexL++; //Reserved
            u8IndexL++; 
            LAPKwpWriteDiagnosticResponse(u8IndexL,mDATRead(U8Bit, EEP_ResetCount, Default));
            u8IndexL++;
            LAPKwpWriteDiagnosticResponse(u8IndexL,mDATRead(U8Bit, EEP_CrashCount, Default));

            u8ResponseLengthL = cRDBLIDAns_DefaultData_Lgth;                 

            break;
        // lecture de l'identification du calculateur
        case cRDBLID_GeneralParamID :
            for(u8IndexL=0;u8IndexL<(cRDBLIDAns_GeneralParam_Lgth - cDataOffset);u8IndexL++)
            {
                LAPKwpWriteDiagnosticResponse(cByte2+u8IndexL, 0x00);
            }
            u8IndexL = cByte2;
            // Byte 1
            //QACJ 3198: akodzhh: Variable is initialized and then modified bit by bit before being used
            u8TempVarL = 0x00;
            u8TempVarL =   ( mDATRead(U1Bit,EEP_DEM_SURVIT,  Default)       ) |
                        ( mDATRead(U1Bit,EEP_CALALPRI,    Default)     <<c1Bits ) |
            
                        ( mDATRead(U1Bit,EEP_AUTDEGIVRAGE,Default)     <<c3Bits ) |
                        ( mDATRead(U1Bit,EEP_RELAIS_DEM,  Default)     <<c4Bits ) |
                        ( mDATRead(U1Bit,EEP_DETCHOC,     Default)     <<c7Bits );

            LAPKwpWriteDiagnosticResponse(u8IndexL,u8TempVarL);
            u8IndexL++;

            // Byte 2
            //QACJ 3198: akodzhh: Variable is initialized and then modified bit by bit before being used
            u8TempVarL = 0x00;
            u8TempVarL =( mDATRead(U1Bit,EEP_CONDATMPO, Default)     <<c1Bits ) |                    
                        ( mDATRead(U1Bit,EEP_CONDAROU,  Default)     <<c3Bits ) |
                        ( mDATRead(U1Bit,EEP_CARCLIENT, Default)     <<c4Bits ) |                    
                        ( mDATRead(U1Bit,EEP_ALIM_PLAF, Default)     <<c6Bits ) |
                        ( mDATRead(U1Bit,EEP_PIL_PLAF,  Default)     <<c7Bits );

            LAPKwpWriteDiagnosticResponse(u8IndexL,u8TempVarL);
            u8IndexL++;

            // Byte 3
            //QACJ 3198: akodzhh: Variable is initialized and then modified bit by bit before being used
            u8TempVarL = 0x00;
            u8TempVarL =( mDATRead(U1Bit,EEP_SDO,           Default)     <<c1Bits ) |
                        ( mDATRead(U1Bit,EEP_CPE_IMPULS,    Default)     <<c2Bits ) |
                        ( mDATRead(U1Bit,EEP_FEU_BROUILLARD,Default)     <<c3Bits ) |
                        ( mDATRead(U1Bit,EEP_EV_ARR,        Default)     <<c4Bits ) |
                        ( mDATRead(U1Bit,EEP_INFO_REGIME,   Default)     <<c5Bits ) |
                        ( mDATRead(U1Bit,EEP_CLI_REM,       Default)     <<c6Bits ) |
                        ( mDATRead(U1Bit,EEP_CAD_BAGUE_AV,  Default)     <<c7Bits );

            LAPKwpWriteDiagnosticResponse(u8IndexL,u8TempVarL);
            u8IndexL++;

            // Byte 4
            //QACJ 3198: akodzhh: Variable is initialized and then modified bit by bit before being used
            u8TempVarL = 0x00;
            u8TempVarL =( mDATRead(U1Bit,EEP_AUTCRASH,      Default)     << 0 ) |
                        ( mDATRead(U1Bit,EEP_AUTVERLOG,     Default)     <<c1Bits ) |
                        ( mDATRead(U1Bit,EEP_AUTPLAF,       Default)     <<c2Bits ) |
                        ( mDATRead(U1Bit,EEP_KEY_BUTTON,    Default)     <<c3Bits ) |
                        ( mDATRead(U1Bit,EEP_CALALARM,      Default)     <<c4Bits ) |
                        ( mDATRead(U1Bit,EEP_CALULKTR,      Default)     <<c5Bits ) |
                        ( mDATRead(U1Bit,EEP_AUTRECRF,      Default)     <<c6Bits ) |
                        ( mDATRead(U1Bit,EEP_OUBLICEINTURE, Default)     <<c7Bits );

            LAPKwpWriteDiagnosticResponse(u8IndexL,u8TempVarL);
            
            u8ResponseLengthL = cRDBLIDAns_GeneralParam_Lgth;
            break;

        case cRDBLID_FactoryConfigID :

            for(u8IndexL=0;u8IndexL<(cRDBLIDAns_FactoryConfig_Lgth - cDataOffset);u8IndexL++)
            {
                LAPKwpWriteDiagnosticResponse(cByte2+u8IndexL, 0x00);
            }

            LAPKwpWriteDiagnosticResponse((U32)(1+cNbTPS_RETARD_DETRESSE       ), mDATRead(U8Bit, EEP_TPS_RETARD_DETRESSE,  Default));
            LAPKwpWriteDiagnosticResponse((U32)(1+cNbTIMER_DETRESSE            ), mDATRead(U8Bit, EEP_TIMER_DETRESSE,       Default));
            LAPKwpWriteDiagnosticResponse((U32)(1+cNbTPS_APC                   ), mDATRead(U8Bit, EEP_TPS_APC,              Default));
            LAPKwpWriteDiagnosticResponse((U32)(1+cNbTPS_PLAF                  ), mDATRead(U8Bit, EEP_TPS_PLAF,             Default));
            LAPKwpWriteDiagnosticResponse((U32)(1+cNbTPS_ESSUIE_MINI           ), mDATRead(U8Bit, EEP_TPS_ESSUIE_MINI,      Default));
            LAPKwpWriteDiagnosticResponse((U32)(1+cNbTPS_MAX_COUPLBLOC         ), mDATRead(U8Bit, EEP_TPS_MAX_COUPLBLOC,    Default));
            LAPKwpWriteDiagnosticResponse((U32)(1+cNbTPS_ARRET                 ), mDATRead(U8Bit, EEP_TPS_ARRET,            Default));
            LAPKwpWriteDiagnosticResponse((U32)(1+cNbTPS_REPRISE               ), mDATRead(U8Bit, EEP_TPS_REPRISE,          Default));
            LAPKwpWriteDiagnosticResponse((U32)(1+cNbTPS_FILT_AF               ), mDATRead(U8Bit, EEP_TPS_FILT_AF,          Default));
            LAPKwpWriteDiagnosticResponse((U32)(1+cNbTPS_POSIT_BALAIS          ), mDATRead(U8Bit, EEP_TPS_POSIT_BALAIS,     Default));
            LAPKwpWriteDiagnosticResponse((U32)(1+cNbPROLONG_APPUI_COURT       ), mDATRead(U8Bit, EEP_PROLONG_APPUI_COURT,  Default));
            LAPKwpWriteDiagnosticResponse((U32)(1+cNbPROLONG_APPUI_LONG        ), mDATRead(U8Bit, EEP_PROLONG_APPUI_LONG,   Default));
            LAPKwpWriteDiagnosticResponse((U32)(1+cNbTPS_APPUILAV              ), mDATRead(U8Bit, EEP_TPS_APPUILAV,         Default));
            LAPKwpWriteDiagnosticResponse((U32)(1+cNbTPS_POSIT_BALAIS_AR       ), mDATRead(U8Bit, EEP_TPS_POSIT_BALAIS_AR,  Default));
            LAPKwpWriteDiagnosticResponse((U32)(1+cNbPROLONG_APPUI_ARR         ), mDATRead(U8Bit, EEP_PROLONG_APPUI_ARR,    Default));
            LAPKwpWriteDiagnosticResponse((U32)(1+cNbSEUIL_VIT_CONDAROU        ), mDATRead(U8Bit, EEP_SEUIL_VIT_CONDAROU,   Default));
            LAPKwpWriteDiagnosticResponse((U32)(1+cNbTPS_COM_MOTEUR            ), mDATRead(U8Bit, EEP_TPS_COM_MOTEUR,       Default));
            LAPKwpWriteDiagnosticResponse((U32)(1+cNbNBCOM_MAX                 ), mDATRead(U8Bit, EEP_NBCOM_MAX,            Default));
            LAPKwpWriteDiagnosticResponse((U32)(1+cNbTPS_REF                   ), mDATRead(U8Bit, EEP_TPS_REF,              Default));
            LAPKwpWriteDiagnosticResponse((U32)(1+cNbTIMER_RECONDA_AUTO        ), mDATRead(U8Bit, EEP_TIMER_RECONDA_AUTO,   Default));
            LAPKwpWriteDiagnosticResponse((U32)(1+cNbN_MISE_APC                ), mDATRead(U8Bit, EEP_N_MISE_APC,           Default));
            LAPKwpWriteDiagnosticResponse((U32)(1+cNbTMPMERA                   ), mDATRead(U8Bit, EEP_TimeOutMERA,              Default));
            LAPKwpWriteDiagnosticResponse((U32)(1+cNbTPS_OUVPORTE              ), mDATRead(U8Bit, EEP_TPS_OUVPORTE,         Default));
            LAPKwpWriteDiagnosticResponse((U32)(1+cNbTPS_TEMPO_DEG             ), mDATRead(U8Bit, EEP_TPS_TEMPO_DEG,        Default));
            LAPKwpWriteDiagnosticResponse((U32)(1+cNbTPS_IMPUL_MINI            ), mDATRead(U8Bit, EEP_TPS_IMPUL_MINI,       Default));
            LAPKwpWriteDiagnosticResponse((U32)(1+cNbSBR_ACTIVE_SPEED_THRESH_TP), mDATRead(U8Bit, EEP_SBR_ACTIVE_SPEED_THRESH_TP,   Default));
            LAPKwpWriteDiagnosticResponse((U32)(1+cNbSBR_TIMEOUT_TM_TP         ), mDATRead(U8Bit, EEP_SBR_TIMEOUT_TM_TP,            Default));
            LAPKwpWriteDiagnosticResponse((U32)(1+cNbMAX_NB_ALERT_SEQUENCES_TP ), mDATRead(U8Bit, EEP_MAX_NB_ALERT_SEQUENCES_TP,    Default));
            LAPKwpWriteDiagnosticResponse((U32)(1+cNbTPS_BUZ_CLI               ), mDATRead(U8Bit, EEP_TPS_BUZ_CLI,                  Default));
            LAPKwpWriteDiagnosticResponse((U32)(1+cNbTPS_CLI                   ), mDATRead(U8Bit, EEP_TPS_CLI,                      Default));
            LAPKwpWriteDiagnosticResponse((U32)(1+cNbTPS_CLIDEGRAD             ), mDATRead(U8Bit, EEP_TPS_CLIDEGRAD,                Default));


            u8ResponseLengthL = cRDBLIDAns_FactoryConfig_Lgth;
            break;

        case cRDBLID_BCMIdentificationID :

            u8TempVarL = ReadECU_LOG(&u8ResponseLengthL);
            
            //CCOV adzhelp: Bootloader is not available in unit test framework
            if (u8TempVarL == cLAPKwpServiceIsCorrect)
            {
                // Serial number is obtained from EEP if it exists
                if (   (mDATReadTable(U8Bit, EEP_SerialNumber, cByte0, Default) != 0) 
                     ||(mDATReadTable(U8Bit, EEP_SerialNumber, cByte1, Default) != 0) 
                     ||(mDATReadTable(U8Bit, EEP_SerialNumber, cByte2, Default) != 0) )
                {
                    // Serial number exists in EEP, use it
                    for (u8IndexL = 0; u8IndexL < cEEP_SerialNumberLength; u8IndexL++)
                    {
                        LAPKwpWriteDiagnosticResponse((cEEP_SerialNumberIndex+u8IndexL),mDATReadTable(U8Bit, EEP_SerialNumber, u8IndexL, Default));
                    }
                }
                else
                {
                    // Serial number already taken from log zone
                }
                
                // Version identification is taken from ROM
                u8BytePos = cVersionIndex;
                LAPKwpWriteDiagnosticResponse(u8BytePos,mDATReadTable(U8Bit, VerVersionNum,0,Default));
                u8BytePos++;
                LAPKwpWriteDiagnosticResponse(u8BytePos,mDATReadTable(U8Bit, VerVersionNum,1,Default));
                u8BytePos++;
                LAPKwpWriteDiagnosticResponse(u8BytePos,mDATReadTable(U8Bit, VerRevisionNum,0,Default));
                u8BytePos++;
                LAPKwpWriteDiagnosticResponse(u8BytePos,mDATReadTable(U8Bit, VerRevisionNum,1,Default));
            }
            else
            {
            #if defined(COMPILATION_NATIVE) || defined(UTEST) || defined(DEBUG)
                // ECU reference cannot be obtained from log zone, get it from ROM
                // (for simulation, unit test and debugger)

                u8BytePos = cByte2;

                for(u8IndexL=0;u8IndexL< cEEP_ECUReferenceLength;u8IndexL++)
                {
                    // ECU reference
                    LAPKwpWriteDiagnosticResponse(u8BytePos+u8IndexL,mDATReadTable(U8Bit,EEP_ECUReference,u8IndexL,Default));
                }

                u8BytePos += cEEP_ECUReferenceLength;

                LAPKwpWriteDiagnosticResponse(u8BytePos,mDATRead(U8Bit, EEP_VDiag, Default));
                u8BytePos++;
                // Supplier's Code
                LAPKwpWriteDiagnosticResponse(u8BytePos, cSupplierCode1);
                u8BytePos++;
                LAPKwpWriteDiagnosticResponse(u8BytePos, cSupplierCode2);
                u8BytePos++;
                LAPKwpWriteDiagnosticResponse(u8BytePos, cSupplierCode3);
                u8BytePos++;
                for(u8IndexL=0;u8IndexL< cEEP_PieNumberLength;u8IndexL++)
                {
                    LAPKwpWriteDiagnosticResponse(u8BytePos+u8IndexL,mDATReadTable(U8Bit,EEP_PieNumber,u8IndexL,Default));  
                }
                u8BytePos += cEEP_PieNumberLength;
                LAPKwpWriteDiagnosticResponse(u8BytePos,mDATReadTable(U8Bit, VerVersionNum,0,Default));
                u8BytePos++;
                LAPKwpWriteDiagnosticResponse(u8BytePos,mDATReadTable(U8Bit, VerVersionNum,1,Default));
                u8BytePos++;
                LAPKwpWriteDiagnosticResponse(u8BytePos,mDATReadTable(U8Bit, VerRevisionNum,0,Default));
                u8BytePos++;
                LAPKwpWriteDiagnosticResponse(u8BytePos,mDATReadTable(U8Bit, VerRevisionNum,1,Default));
                u8BytePos++;
            
                LAPKwpWriteDiagnosticResponse(u8BytePos,mDATReadTable(U8Bit,EEP_PieIndex,0,Default));
                u8BytePos++;
                LAPKwpWriteDiagnosticResponse(u8BytePos,mDATReadTable(U8Bit,EEP_PieIndex,1,Default));
                u8BytePos++; 
            
                LAPKwpWriteDiagnosticResponse(u8BytePos,mDATRead(U8Bit,EEP_ECUType,Default));
                u8BytePos++; 
                // Cm006459: BCM Serial Number
                for (u8IndexL = 0; u8IndexL < cEEP_SerialNumberLength; u8IndexL++)
                {
                    LAPKwpWriteDiagnosticResponse((u8BytePos+u8IndexL),mDATReadTable(U8Bit, EEP_SerialNumber, u8IndexL, Default));
                }
            #else
                // target with no bootloader
                u8RequestStatusL = cLAPKwpConditionNotCorrect;
            #endif
            }

            u8ResponseLengthL = cRDBLIDAns_BCMIdentification_Lgth;
            break;


        case cRDBLID_ImmoDataID :
            for(u8IndexL=0;u8IndexL<(cRDBLIDAns_ImmoData_Lgth - cDataOffset);u8IndexL++)
            {
                LAPKwpWriteDiagnosticResponse(cByte2+u8IndexL,0x00);
            }
            u8IndexL = cByte2;
            //Byte 1
            bDiagVERLOGON = (mDATRead(U1Bit, VERLOGON, Default) 
                            || (cFalse == mDATRead(U1Bit, EEP_EraseAFSCodeRequest,Default)));
            //QACJ 3198: akodzhh: Variable is initialized and then modified bit by bit before being used
            u8TempVarL = 0x00;
            u8TempVarL =(mDATRead(U1Bit, EEP_BCMBlank, Default)) |
                        (mDATRead(U1Bit, DATTrpIdentifierOfPresentKeyIsReceived, Default)<<c1Bits) |
                        (mDATRead(U1Bit, DATTrpIdentifierOfPresentKeyIsValid, Default)   <<c2Bits) |
                        (mDATRead(U1Bit, DATTrpResponseToChallengeIsPresent, Default)    <<c3Bits) |
                        (mDATRead(U1Bit, DATTrpResponseToChallengeIsValid, Default)      <<c4Bits) |
                        (bDiagVERLOGON <<c5Bits);   // Protected Vehicle
                        // Reserved 6
                        // Reserved 7                  
            LAPKwpWriteDiagnosticResponse(u8IndexL,u8TempVarL);
            u8IndexL++;

            //Byte 2
            //QACJ 3198: akodzhh: Variable is initialized and then modified bit by bit before being used
            u8TempVarL = 0x00;
            u8TempVarL =(((U8)(1<<mDATRead(U8Bit, DATTrpIndexOfKeyRecognized, Default)) & cMaskIndexOfKeyRecognized)) |
                        ((mDATRead(U8Bit, DATTrpDiagKeyFrequency, Default) & cMaskDiagKeyFrequency)<<c4Bits)|
                        ( mDATRead(U1Bit, VirginKeyAuthentOk, Default)  <<c7Bits); // HK TODO: ?cle_vierge(transport key)
            LAPKwpWriteDiagnosticResponse(u8IndexL,u8TempVarL);
            u8IndexL++;

            //Byte 3
            //QACJ 3198: akodzhh: Variable is initialized and then modified bit by bit before being used
            u8TempVarL = 0x00;
            u8TempVarL = (mDATRead(U1Bit, DATTrpPresentKeyLocked,Default)) |
                        ((mDATRead(U8Bit,LearningModeInProgress,Default) & cMaskLearningModeInProgress) <<c1Bits) |
                        (mDATRead(U1Bit, EEP_AppCleNonEffect, Default)           <<c4Bits) |
                        // Reserved 5
                        (mDATRead(U1Bit, EEP_CodeAFSAvailable, Default)          <<c6Bits) |
                        (mDATRead(U1Bit, AFSCodeIsOk,Default)                    <<c7Bits    );
            LAPKwpWriteDiagnosticResponse(u8IndexL,u8TempVarL);
            u8IndexL++;

            //Byte 4
            //QACJ 3198: akodzhh: Variable is initialized and then modified bit by bit before being used
            u8TempVarL = 0x00;
            u8TempVarL =   // Reserved 0..6
                        
                        (mDATRead(U1Bit, EEP_EraseAFSCodeRequest,Default)     <<c7Bits); 
            LAPKwpWriteDiagnosticResponse(u8IndexL,u8TempVarL);
            u8IndexL++;

            //Byte 5
            LAPKwpWriteDiagnosticResponse(u8IndexL,((U8)(mDATRead(U32Bit,DATTrpIdentifierOfPresentKey,Default)>>c24Bits)));
            u8IndexL++;
            //Byte 6
            LAPKwpWriteDiagnosticResponse(u8IndexL,((U8)(mDATRead(U32Bit,DATTrpIdentifierOfPresentKey,Default)>>c16Bits)));
            u8IndexL++;
            //Byte 7
            LAPKwpWriteDiagnosticResponse(u8IndexL,((U8)(mDATRead(U32Bit,DATTrpIdentifierOfPresentKey,Default)>>c8Bits)));
            u8IndexL++;
            //Byte 8
            LAPKwpWriteDiagnosticResponse(u8IndexL,((U8)mDATRead(U32Bit,DATTrpIdentifierOfPresentKey   ,Default)));
            u8IndexL++;

            //Byte 9 to 11
            if ((mDATRead(U8Bit,LearningModeInProgress,Default) != cDATNoLearningMode)
              &&(mDATRead(U8Bit,LearningModeInProgress,Default) != cDATBcmReplacement))
            {
                LAPKwpWriteDiagnosticResponse(u8IndexL,mDATRead(U8Bit,NumberOfKeysLearnt,Default));
                u8IndexL++;
                LAPKwpWriteDiagnosticResponse(u8IndexL,mDATRead(U8Bit,NumberOfKeys433MHzLearnt,Default));
                u8IndexL++;
                LAPKwpWriteDiagnosticResponse(u8IndexL,mDATRead(U8Bit,NumberOfKeys315MHzLearnt,Default));
                u8IndexL++;
            }   
            else
            {
                LAPKwpWriteDiagnosticResponse(u8IndexL,mDATRead(U8Bit,EEP_NbKeysLearnt,Default));
                u8IndexL++;
                LAPKwpWriteDiagnosticResponse(u8IndexL,mDATRead(U8Bit,EEP_NbKeysStd433MhzLearnt,Default));
                u8IndexL++;
                LAPKwpWriteDiagnosticResponse(u8IndexL,mDATRead(U8Bit,EEP_NbKeysStd315MhzLearnt,Default));
                u8IndexL++;
            }

            // Cm005064; Byte 12,13 - RESERVED
            LAPKwpWriteDiagnosticResponse(u8IndexL,cReservedValue);
            u8IndexL++;
            LAPKwpWriteDiagnosticResponse(u8IndexL,cReservedValue);
            u8IndexL++;

            //Byte 14
            //QACJ 3198: akodzhh: Variable is initialized and then modified bit by bit before being used
            u8TempVarL = 0x00;
            u8TempVarL =( mDATRead(U1Bit,LastOpeningPanelControl,Default))|
                        ( mDATRead(U1Bit,LastCommandOrigin,Default)                     <<c1Bits) |
                        ( mDATRead(U1Bit,VehicleIsAutoRelocked,Default)                 <<c2Bits) |
                        ( mDATRead(U1Bit,EEP_CARCLIENT,Default)                         <<c3Bits) | // CONDAROU_ACTIV
                        ( mDATRead(U1Bit,VehicleIsLockedWithSpeed,Default)              <<c4Bits) | // CONDA_ROULANT
                        ( mDATRead(U1Bit,VehiculeHasBeenMoving,Default)                 <<c5Bits) | // VEHICULE_ROULANT
                        ( mDATRead(U1Bit,PWR_IGN,Default)                               <<c6Bits);
                        // Reserved 7
            LAPKwpWriteDiagnosticResponse(u8IndexL,u8TempVarL);
            u8IndexL++;

            //Byte 15   HK TODO #3 #6 #7 Bits Reserved - chek
            LAPKwpWriteDiagnosticResponse(u8IndexL,mDATRead(U8Bit,RfPushMemorized,Default));
            u8IndexL++;

            //Byte 16 to 19 // Ident_Cle
            LAPKwpWriteDiagnosticResponse(u8IndexL,(((U8)(mDATRead(U32Bit,RfRCFrameIDReceived,Default)>>c24Bits) &cLSBMask)));
            u8IndexL++;
            LAPKwpWriteDiagnosticResponse(u8IndexL,(((U8)(mDATRead(U32Bit,RfRCFrameIDReceived,Default)>>c16Bits) &cLSBMask)));
            u8IndexL++;
            LAPKwpWriteDiagnosticResponse(u8IndexL,(((U8)(mDATRead(U32Bit,RfRCFrameIDReceived,Default)>>c8Bits ) &cLSBMask)));
            u8IndexL++;
            LAPKwpWriteDiagnosticResponse(u8IndexL,(((U8)(mDATRead(U32Bit,RfRCFrameIDReceived,Default)         ) &cLSBMask)));
            u8IndexL++;

            //Byte 20 and 21
            u8TempVarL = (U8)(mDATRead(U16Bit,AuthentPermanentTotalCounter,Default)>>c8Bits);
            LAPKwpWriteDiagnosticResponse(u8IndexL,u8TempVarL);
            u8IndexL++;
            u8TempVarL = (U8)(mDATRead(U16Bit,AuthentPermanentTotalCounter,Default));
            LAPKwpWriteDiagnosticResponse(u8IndexL,u8TempVarL);
            u8IndexL++;
            //Byte 22
            LAPKwpWriteDiagnosticResponse(u8IndexL,mDATRead(U8Bit,AuthentPermanentFailCounter,Default));
            u8IndexL++;
            //Byte 23
            LAPKwpWriteDiagnosticResponse(u8IndexL,mDATRead(U8Bit,AuthentPermanentResynchroFailCounter,Default));
            u8IndexL++;
            //Byte 24 RESERVED
            u8TempVarL = cReservedValue; 
            LAPKwpWriteDiagnosticResponse(u8IndexL,u8TempVarL);


            u8ResponseLengthL = cRDBLIDAns_ImmoData_Lgth;
            break;


        case cRDBLID_APVCodeID :
            if(mDATRead(U1Bit,EEP_CodeAFSAvailable,Default) != cFalse)
            {
                u8BytePos = cByte2;
                mDATControl(Apr,cDATAprReadAfterSaleCode);
                for(u8IndexL=0;u8IndexL<cDATTrpISKLengthInBytes;u8IndexL++)
                { // APV code +checksum
                    LAPKwpWriteDiagnosticResponse(cByte2+u8IndexL,mDATReadTable(U8Bit, DATAprAfterSaleCode,u8IndexL,Default));
                }
                u8BytePos += cDATTrpISKLengthInBytes;
                LAPKwpWriteDiagnosticResponse(u8BytePos, 0); 

                u8ResponseLengthL = cRDBLIDAns_APVCode_Lgth;
            }
            else
            {
                u8RequestStatusL = cLAPKwpConditionNotCorrect;
            }
            break;

        case cRDBLID_InputAndVehicleStateID :
            u8BytePos = cByte2;
            //QACJ 3198: akodzhh: Variable is initialized and then modified bit by bit before being used
            u8TempVarL = 0x00; // Byte 1
            u8TempVarL = (mDATRead(U1Bit,PWR_IGN,       Default)   ) 
                        |(mDATRead(U1Bit,DOOR_LOCK_SW,  Default)<<c1Bits)
                        |(mDATRead(U1Bit,DOOR_UNLOCK_SW,Default)<<c2Bits)
                        |(mDATRead(U1Bit,RR_WASHER_SW  ,Default)<<c5Bits)
                        |(mDATRead(U1Bit,DEFROSTER_SW  ,Default)<<c6Bits)  // LUNETTE - Rear window input
                        |(mDATRead(U1Bit,DI_DATA_IMMOBILIZER, Default)<<c7Bits); // TRANSPONDEUR - Transponder line                    ;
            LAPKwpWriteDiagnosticResponse(u8BytePos,u8TempVarL);
            u8BytePos++;

            //QACJ 3198: akodzhh: Variable is initialized and then modified bit by bit before being used
            u8TempVarL = 0x00; // Byte 2
            u8TempVarL = (mDATRead(U1Bit,RR_AUTOSTOP_SW,Default))
                        |(mDATRead(U1Bit,RR_WIPER_INT_SW,Default)<<c2Bits);                    
            LAPKwpWriteDiagnosticResponse(u8BytePos,u8TempVarL);
            u8BytePos++;

            //QACJ 3198: akodzhh: Variable is initialized and then modified bit by bit before being used
            u8TempVarL = 0x00; // Byte 3 
            u8TempVarL =  (mDATRead(U1Bit,POSITION_LIGHTS,Default)   )  // CDE_FEUX_LANT - Side light input
                         |(mDATRead(U1Bit,HAZARD_SW,      Default)<<c1Bits)
                         |(mDATRead(U1Bit,R_FLASHER_SW,   Default)<<c2Bits)
                         |(mDATRead(U1Bit,L_FLASHER_SW,   Default)<<c3Bits)
                         |(mDATRead(U1Bit,FR_DOORS_SW,    Default)<<c4Bits) 
                         |(mDATRead(U1Bit,FR_AUTOSTOP_SW, Default)<<c5Bits)
                         |(mDATRead(U1Bit,RR_DOORS_SW,    Default)<<c6Bits)
                         |(mDATRead(U1Bit,FR_WASHER_SW,   Default)<<c7Bits);
            LAPKwpWriteDiagnosticResponse(u8BytePos,u8TempVarL);
            u8BytePos++;

            //QACJ 3198: akodzhh: Variable is initialized and then modified bit by bit before being used
            u8TempVarL = 0x00; // Byte 4
            u8TempVarL = (mDATRead(U1Bit,FR_WIPER_INT_SW,Default)   )                    
                        |(mDATRead(U1Bit,AIRBAG_CRASH,   Default)<<c7Bits);
            LAPKwpWriteDiagnosticResponse(u8BytePos,u8TempVarL);
            u8BytePos++;

            //QACJ 3198: akodzhh: Variable is initialized and then modified bit by bit before being used
            u8TempVarL = 0x00; // Byte 5
            u8TempVarL = (mDATRead(U1Bit,DI_VERLOG,   Default)<<c1Bits)
                        // FR_FOG_SW/HIGH_LOW_BEAM(P0.4)                        
                        |(mDATRead(U1Bit,HIGH_LOW_BEAM,   Default)<<c3Bits)   // BRAV+CODE_PHARE - front fog lights + code/light input
                        |(mDATRead(U1Bit,RR_FOG_SW,   Default)<<c6Bits)
                        |(mDATRead(U1Bit,SEATBELT_REMINDER_SW,Default)<<c7Bits);
            LAPKwpWriteDiagnosticResponse(u8BytePos,u8TempVarL);
            u8BytePos++;

            //QACJ 3198: akodzhh: Variable is initialized and then modified bit by bit before being used
            u8TempVarL = 0x00; // Byte 6
            u8TempVarL =  (mDATRead(U1Bit,ENGINE_RPM,Default)<<c1Bits);    // MOT_TOURNANT - Engine running           
            LAPKwpWriteDiagnosticResponse(u8BytePos,u8TempVarL);


            u8ResponseLengthL = cRDBLIDAns_InputAndVehicleStateLgth;
            break;

        case cRDBLID_OutputStateID :
            for(u8IndexL=0;u8IndexL<(U8)(cRDBLIDAns_OutputStateLgth - cDataOffset);u8IndexL++)
            {
                LAPKwpWriteDiagnosticResponse(cByte2+u8IndexL,0x00);
            } 
            if (mDATRead(U8Bit, PWM_ROOMLAMPDiagRatio, Default) != 0) // Read DATPwmHardBuffer
            {
                u8PlafValueL = 1;
            }
            else
            {
                u8PlafValueL = 0;
            }

            u8BytePos = cByte2;
            u8TempVarL = (mDATRead(U1Bit,LOCK_DOORS,   Immediate)         )     
                        |(mDATRead(U1Bit,UNLOCK_DRIVER_DOOR,Immediate) <<c1Bits)  // Cm005581: prsFS_DIAG-802
                        |(mDATRead(U1Bit,UNLOCK_DRIVER_DOOR,Immediate) <<c2Bits)
                        |(mDATRead(U1Bit,DI_RIGHT,     Immediate) <<c3Bits) 
                        |(mDATRead(U1Bit,DI_LEFT,      Immediate) <<c4Bits)
                        // HK TODO:  Nominal/Double frequency indicator - bits 5,6 
                        |((mDATRead(U8Bit,FlashingFrequency,Default) & cMaskFlashingFrequency)<<c5Bits)
                        |( u8PlafValueL<<c7Bits);
            LAPKwpWriteDiagnosticResponse(u8BytePos,u8TempVarL);
            u8BytePos++;

            //QACJ 3198: akodzhh: Variable is initialized and then modified bit by bit before being used
            u8TempVarL = 0x00;
            u8TempVarL = (mDATRead(U1Bit,FRONT_WIPER,    Immediate))
                        // Reserved 1 
                        |(mDATRead(U1Bit,OPEN_DOOR_LED,  Immediate)<<c2Bits) 
                        |(mDATRead(U1Bit,VERLOG_LED   ,  Immediate)<<c3Bits)
                        // Reserved 4                        
                        |(mDATRead(U1Bit,RR_WIPER_RR_FOG_LAMP,  Immediate)<<c5Bits)
                        // Reserved 6 
                        |(mDATRead(U1Bit,BAT_LIGHT_TEMPO,Immediate)<<c7Bits);

            LAPKwpWriteDiagnosticResponse(u8BytePos,u8TempVarL);
            u8BytePos++;

            // Byte #8 Cm005581: prsFS_DIAG-802
            //QACJ 3198: akodzhh: Variable is initialized and then modified bit by bit before being used
            u8TempVarL = 0x00;
            u8TempVarL =// Reserved 0 
                         (mDATRead(U1Bit,RR_WIPER_RR_FOG_LAMP, Immediate )<<c1Bits)
                        // Reserved 2
                        // Reserved 3
                        |(mDATRead(U1Bit,HORN_RL, Immediate)<<c4Bits)
                        // Reserved 5
                        // Reserved 6 
                        |(mDATRead(U1Bit,DEFROSTER, Immediate)<<c7Bits);

            LAPKwpWriteDiagnosticResponse(u8BytePos,u8TempVarL);
            

            // Byte 9,10 Reserved
            
            // Byet 11 
            u8TempVarL =  mDATRead(U1Bit, IsBuzzerSoundPlaying, Default) & 0x01;
            //Bits 1..7 Reserved 

            LAPKwpWriteDiagnosticResponse(cByteOutputStateBuzzer,u8TempVarL);

            u8ResponseLengthL = cRDBLIDAns_OutputStateLgth;
            break;


        case cRDBLID_VINID :
            for(u8IndexL=0; u8IndexL<(U8)(cRDBLIDAns_VIN_Lgth - cDataOffset); u8IndexL++)
            {
                LAPKwpWriteDiagnosticResponse(cByte2+u8IndexL,mDATReadTable(U8Bit,EEP_VehicleIdentifierNumber,u8IndexL,Default));
            }
            u8ResponseLengthL = cRDBLIDAns_VIN_Lgth;
            break;

        case cRDBLID_CodedValueID :

            for(u8IndexL=0;u8IndexL<(U8)(cRDBLIDAns_CodedValueLgth - cDataOffset);u8IndexL++)
            {
                LAPKwpWriteDiagnosticResponse(cByte2+u8IndexL,cReservedValue);
            }

            u8BytePos = cByte2; 
            //HK TODO: EAVAV -  Value of the variable intermittent facility ring (not used)? (U16 in AW1092 - AnaCmdEsavCadenceInMilliVolt)
            LAPKwpWriteDiagnosticResponse(u8BytePos,  0x00); // FR_WIPER_INT_SW
            u8BytePos++;
            LAPKwpWriteDiagnosticResponse(u8BytePos,  0);
            u8BytePos++;
            LAPKwpWriteDiagnosticResponse(u8BytePos,  mDATRead(U8Bit, VEHICLE_SPEED, Default));
            
            // reserved 5..6 FFh             
            // CLR: #78
            LAPKwpWriteDiagnosticResponse(cByteSTATUS_CLIGN,  mDATRead(U8Bit, STATUS_CLIGN  , Default) ); 
            // reserved 8..13 FFh
            // CLR: #78
            LAPKwpWriteDiagnosticResponse(cByteTENSION_BATTERIE, mDATRead(U8Bit, TENSION_BATTERIE, Default)); 
            // reserved 15..17 FFh
            // blank    18..21 00h
            u8BytePos = cByte18;
            LAPKwpWriteDiagnosticResponse(u8BytePos, (U8)0x00);
            u8BytePos++;
            LAPKwpWriteDiagnosticResponse(u8BytePos, (U8)0x00);             
            u8BytePos++;
            LAPKwpWriteDiagnosticResponse(u8BytePos, (U8)0x00);
            u8BytePos++;
            LAPKwpWriteDiagnosticResponse(u8BytePos, (U8)0x00);

            u8ResponseLengthL = cRDBLIDAns_CodedValueLgth;
            break;

        default :
        #ifdef BOOTLOADER_IS_SUPPORTED
            if( mIsECU_LOG_ID(LAPKwpReadDiagnosticRequest(1)))
            {
                u8RequestStatusL = ReadECU_LOG(&u8ResponseLengthL);
            }
            else
        #endif
            {
                u8RequestStatusL = 
                LIBCfdExecuteConfDiagRequest(   LAPKwpReadDiagnosticRequest(0),
                                                LAPKwpReadDiagnosticRequest(1),
                                                &u8ResponseLengthL);
            }
            
            break;
        }

    }
    else
    {
        u8RequestStatusL = cLAPKwpInvalidFormat;
    }

    if(u8RequestStatusL == cLAPKwpServiceIsCorrect)
    {
        LAPKwpWriteDiagnosticResponse(1,LAPKwpReadDiagnosticRequest(1));
        LAPKwpPreparePositiveResponse(u8ResponseLengthL);
    }
    else
    {
        LAPKwpPrepareNegativeResponse(u8RequestStatusL);
    }
    LAPKwpSetServiceIsFinished();
}

//==============================================================================
// DESCRIPTION:         LAPAfsTreatInputOutputControlByLocalIdentifierService
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
MEM_TYPE void LAPAfsTreatInputOutputControlByLocalIdentifierService(void)
{
    U8  u8RequestStatusL;
    U8  u8OutputRequestL;
    U8  u8IndexL;

    u8RequestStatusL = cLAPKwpInvalidFormat;
    u8OutputRequestL = cNoOutputControl;

    mLIBassert(cNbOutputToControl <= cNoOutputControl);
    // Search output controled
    for (u8IndexL=0; u8IndexL<cNbOutputToControl; u8IndexL++)
    {
        if (LAPKwpReadDiagnosticRequest(1) == TableIOCBLIDIdentifier[u8IndexL])
        {
            u8OutputRequestL = u8IndexL;
        }
    }

    if( (u8OutputRequestL != cNoOutputControl) &&
        (mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cIOCBLIDReq_Lgth ))
    {
        if((LAPKwpReadDiagnosticRequest(cByte2) == cIOCBLID_StartRoutineID                ) &&
           ((LAPKwpReadDiagnosticRequest(cByte3) == cIOCBLID_DeactivationParam       ) ||
            (LAPKwpReadDiagnosticRequest(cByte3) == cIOCBLID_PermanentActivationParam) ||
            (LAPKwpReadDiagnosticRequest(cByte3) == cIOCBLID_TemporaryActivationParam)    ))
        {
            // Start Routine Request
            if(LAPKwpReadDiagnosticRequest(cByte3) == cIOCBLID_DeactivationParam)
            {
                // deactivation Reaquest

                // Special outputs
                if(   (u8OutputRequestL == cHornRlIndex)
                    &&(mDATRead(U8Bit,EEP_PerimeterAlarmState, Default ) == cPAlaStateActivated) )
                {
                    // prsFS_ASA-452 IO control of horn is inhibited 
                    u8RequestStatusL = cLAPKwpConditionNotCorrect;
                }
                else // Normal outputs
                {
                    u8RequestStatusL = DeactiveOutputControl(u8OutputRequestL);
                    if((u8RequestStatusL == cLAPKwpServiceIsCorrect) && (LAPKwpIsServiceFinished() !=cFalse))
                    {
                        // The active output is deactivate
                        LAPKwpWriteDiagnosticResponse(cByte2,cIOCBLID_RoutineIsFinishedID);
                        u8OutputRequestInProgress = cNoOutputControl;
                    }
                    //CCOV: akodzhh: can't be covered, now supported outputs are always deactivated at this step.
                    //CCOV: akodzhh: can't be covered, now supported outputs are always deactivated at this step.
                    else
                    {
                        // Wait the next graph cycle
                    }
                }
            }
            else 
            {
                // Activation request
                if(  u8OutputRequestInProgress != cNoOutputControl)
                {
                    // desactivate the currently active output
                    //QACJ 3200: akodzhh: Return value is intentionally ignored here
                    DeactiveOutputControl(u8OutputRequestInProgress); // Ignore Status
                }

                if(u8OutputRequestInProgress == cNoOutputControl) 
                { 
                    u8RequestStatusL = WriteOuputByDiag (u8OutputRequestL, LAPKwpReadDiagnosticRequest(cByte3));

                    if(u8RequestStatusL == cLAPKwpServiceIsCorrect)
                    {
                        u8OutputRequestInProgress = u8OutputRequestL;
                        if(LAPKwpReadDiagnosticRequest(cByte3) == cIOCBLID_TemporaryActivationParam)
                        {
                            TOSSeqActiverGraphe(cTOSSeqLAPAfsIOControlByLocalID);
                        }
                        LAPKwpWriteDiagnosticResponse(cByte2,cIOCBLID_RoutineInProgressID);
                    }
                    LAPKwpSetServiceIsFinished();
                }
                //CCOV: akodzhh: can't be covered, now supported outputs are always deactivated in one step.
                else
                {
                // Wait the next graph cycle
                }
            }
        }
        else 
        {
            if(LAPKwpReadDiagnosticRequest(cByte2) == cIOCBLID_ReadStatusID)
            { // Read Status Request
                LAPKwpWriteDiagnosticResponse(cByte2,ReadIOCBILStatus(u8OutputRequestL));
                u8RequestStatusL = cLAPKwpServiceIsCorrect;
                LAPKwpSetServiceIsFinished();
            }
        }
    }
    //CCOV: akodzhh: can't be covered, now supported outputs are always deactivated in one step.
    if(LAPKwpIsServiceTreated() == cFalse)
    {
        // Request treatment is finished or status is not correct
        if(u8RequestStatusL != cLAPKwpServiceIsCorrect)
        {
            LAPKwpPrepareNegativeResponse(u8RequestStatusL);
        }
        else
        {
            LAPKwpWriteDiagnosticResponse(1,LAPKwpReadDiagnosticRequest(1));
            LAPKwpPreparePositiveResponse(cIOCBLIDAns_Lgth);
        }
        LAPKwpSetServiceIsFinished(); // Force the end of the treatment for enable the answer
    }
}

//==============================================================================
// DESCRIPTION:         LAPAfsTreatLearningModeControlService
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
MEM_TYPE void LAPAfsTreatLearningModeControlService(void)
{
    U8  u8RequestStatusL;
    U8  u8IndexL;

    u8RequestStatusL = cLAPKwpServiceIsCorrect;

    switch (LAPKwpReadDiagnosticRequest(1))
    {
    case cLMC_EnterInFactoryLearningModeID:
        if(mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cLMCReq_Factory_Lgth)
        {
            if(mDATRead(U1Bit,FactoryModeAuthorized,Default) != cFalse)
            {
                TOSSendControl(cTOSControlStartLearningInFactoryMode);
            }
            else
            {
                u8RequestStatusL = cLAPKwpConditionNotCorrect;
            }

        }
        else
        {
            u8RequestStatusL = cLAPKwpInvalidFormat;
        }
        break;

    case cLMC_LeaveInFactoryLearningModeID:
        if(mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cLMCReq_Factory_Lgth)
        {
            if(     (cDATFactoryMode == mDATRead(U8Bit,LearningModeInProgress,Default))
                &&  (cFalse == mDATRead(U1Bit, PWR_IGN, Default))
              )
            {
                TOSSendControl(cTOSControlExitFromLearningInFactoryMode);
            }
            else
            {
                u8RequestStatusL = cLAPKwpConditionNotCorrect;
            }

        }
        else
        {
            u8RequestStatusL = cLAPKwpInvalidFormat;
        }
        break;

    case cLMC_EnterInAFSLearningModeID:
        if(mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cLMCReq_EnterInAFSLearningMode_Lgth)
        {
            if(mDATRead(U1Bit,AfterSaleModeAuthorized,Default) == cTrue)
            {
                for(u8IndexL=0;u8IndexL<cDATTrpISKLengthInBytes;u8IndexL++)
                {
                    mDATWriteTable(U8Bit,DATAprDiagAfterSaleCode,u8IndexL,LAPKwpReadDiagnosticRequest(cByte2+u8IndexL),Default);
                }

                if(mDATRead(U1Bit, EEP_BCMBlank, Default) == cFalse)
                {
                    //------------------------------------------
                    // BCM is not blank => test After Sale code
                    //------------------------------------------
                    mDATControl(Apr,cDATAprTestDiagAfterSaleCode);
                    mDATWrite(U1Bit,AFSCodeIsOk,mDATRead(U1Bit,DATAprAfterSaleCodeRecognized,Default),Default);
                    if(mDATRead(U1Bit,AFSCodeIsOk,Default) == cFalse)
                    {
                        u8RequestStatusL = cLAPKwpConditionNotCorrect;
                    }
                }
                if(u8RequestStatusL == cLAPKwpServiceIsCorrect)
                {
                    TOSSendControl(cTOSControlStartLearningInAfterSaleMode);
                }

            }
            else
            {
                u8RequestStatusL = cLAPKwpConditionNotCorrect;
            }
        }
        else
        {
            u8RequestStatusL = cLAPKwpInvalidFormat;
        }
        break;

    case cLMC_LeaveInAFSLearningModeID:
        if(mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cLMCReq_LeaveInAFSLearningMode_Lgth)
        {
            if(LAPKwpReadDiagnosticRequest(cByte2) == cLMCL_AFSLearningValidation)
            {
                if(mDATRead(U1Bit,AfterSaleModeValidationAuthorized,Default) == cTrue)
                {
                    TOSSendControl(cTOSControlValidateLearningInAfterSaleMode);
                    if(     (mDATRead(U8Bit,LearningModeInProgress,Default) == cDATBcmReplacement)
                        ||  (   (mDATRead(U8Bit,LearningModeInProgress,Default) == cDATKeyReassignment)
                             && (0 == mDATRead(U8Bit, NumberOfKeysLearnt, Default))
                            )
                      )
                    {
                        u8RequestStatusL = cLAPKwpConditionNotCorrect;
                    }
                    else
                    {

                    }
                }
                else
                {
                    u8RequestStatusL = cLAPKwpConditionNotCorrect;
                }
            }
            else if(LAPKwpReadDiagnosticRequest(cByte2) == cLMCL_AFSLearningCancel)
            {
                if( (mDATRead(U8Bit,LearningModeInProgress,Default) == cDATBcmReplacement) 
                  ||(mDATRead(U8Bit,LearningModeInProgress,Default) == cDATKeyReassignment))
                {
                    TOSSendControl(cTOSControlGiveUpLearningInAfterSaleMode);
                }
                else
                {
                    u8RequestStatusL = cLAPKwpConditionNotCorrect;
                }
            }
            else
            {
                u8RequestStatusL = cLAPKwpConditionNotCorrect;
            }

        }
        else
        {
            u8RequestStatusL = cLAPKwpInvalidFormat;
        }
        break;

    default :
        u8RequestStatusL = cLAPKwpInvalidFormat;
        break;
    }

    if(u8RequestStatusL != cLAPKwpServiceIsCorrect)
    {
        LAPKwpPrepareNegativeResponse(u8RequestStatusL);
    }
    else
    {
        LAPKwpWriteDiagnosticResponse(1,LAPKwpReadDiagnosticRequest(1));
        LAPKwpPreparePositiveResponse(cLMCAns_Lgth);
    }
    LAPKwpSetServiceIsFinished();

}

//==============================================================================
// DESCRIPTION:         LAPAfsInitSession
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
MEM_TYPE void LAPAfsInitSession(void)
{
    u8OutputRequestInProgress = cNoOutputControl;    
    u8RoutineRequestInProgress = cNoRoutineControl;
}

//==============================================================================
// DESCRIPTION:         LAPAfsCloseSession
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
MEM_TYPE void LAPAfsCloseSession(void)
{
    if(  u8OutputRequestInProgress != cNoOutputControl)
    {
        // desactivate the currently active output
        // Ignore Status
        //QACJ 3200: akodzhh: Return value is intentionally ignored here
        DeactiveOutputControl(u8OutputRequestInProgress);
    }

    if( (mDATRead(U8Bit, LearningModeInProgress,Default) == cDATKeyReassignment) ||
        (mDATRead(U8Bit, LearningModeInProgress,Default) == cDATBcmReplacement))
    {
        TOSSendControl(cTOSControlGiveUpLearningInAfterSaleMode);
    }
    if(mDATRead(U8Bit, LearningModeInProgress,Default) == cDATFactoryMode)
    {
        TOSSendControl(cTOSControlExitFromLearningInFactoryMode);
    }

    // Stop the mode "Permanent authentication"
    TOSSendControl(cTOSControlStopPermanentAuthentication);  


}

//==============================================================================
// DESCRIPTION:         FreeActuator
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
void FreeActuator(void)
{
#ifdef X90_PROJECT
    FreeActuator_Static();
}
#pragma optimize=no_inline
static MEM_TYPE void FreeActuator_Static(void)
{
#endif
    if ( u8OutputRequestInProgress < cNbTorToControl)
    {
        mDATWriteTable(U1Bit,DATPouDiagBuffer,TableTorIndex[u8OutputRequestInProgress],0,Default);
        mDATWriteTable(U1Bit,DATPouDiagMaskBuffer,TableTorIndex[u8OutputRequestInProgress],0,Default);
        if(u8OutputRequestInProgress == cDoorlockLedIndex)
        {            
            mLIBassert(mDATRead(U1Bit,IsAlaDiagEnabled, Default ) == cTrue);
            TOSSendControl(cTOSControlAlaDiagDisable);
        }
    }
    else if (u8OutputRequestInProgress < (cNbTorToControl+cNbSerialLineToControl))
    {

        if( u8OutputRequestInProgress == cNbTorToControl)
        {
            mDATWrite(U1Bit,DO_DATA_IMMOBILIZERDiag, 0,Default);
            mDATWrite(U1Bit,DO_DATA_IMMOBILIZERDiagEnabled, cFalse, Default);
        }
        else
        {
            mDATWrite(U1Bit,DO_VERLOGDiag     , 0,Default);
            mDATWrite(U1Bit,DO_VERLOGDiagEnabled, cFalse, Default);
        }
    }
    else if(u8OutputRequestInProgress < cNbOutputToControl)
    { 
        if( u8OutputRequestInProgress == (cNbTorToControl+cNbSerialLineToControl))
        {//PWM output
            mDATWrite(U1Bit,PWM_ROOMLAMPDiagMask,  0, Default); 
        }
        else // Buzzer
        {
            mDATControl(DATBuzDiagBuzz, Stop);
        }

    }
    //CCOV: akodzhh: can't be covered, no other outputs
    else
    {
        mLIBassert(cFalse);
    }
    u8OutputRequestInProgress = cNoOutputControl;
}

//==============================================================================
// DESCRIPTION:         StartActivationTimeOut
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
void StartActivationTimeOut(void)
{
    BOOL bIsCpeOutput;

    bIsCpeOutput = IsCpeOutput(u8OutputRequestInProgress);
    if(bIsCpeOutput == cTrue)
    {
        OutputControlTimeOutValue = cIOCBLIDCpeTimeOutInTick;
    }
    else
    {
        OutputControlTimeOutValue = cIOCBLIDNormalOutputTimeOut;
    }
    
    TOSStartTempo(&OutputControlTimeOut);
}


//==============================================================================
// DESCRIPTION:         IOCBLIDTimeOutIsElapsed
//
// PARAMETERS:          none
//
// RETURN VALUE:        BOOL
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
BOOL IOCBLIDTimeOutIsElapsed(void)
{
    return (BOOL)TOSIsTempoElapsed(&OutputControlTimeOut, OutputControlTimeOutValue);
}

//==============================================================================
// DESCRIPTION:         LAPAfsIsMaintainActiveState
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
void LAPAfsIsMaintainActiveState(void)
{
    tTOSSeqGraphStateType IOControlGraphState;

    IOControlGraphState = TOSSeqGraphState(cTOSSeqLAPAfsIOControlByLocalID);      
    if( IOControlGraphState == cTOSSeqActiveGraph ) 
    {
        TOSWriteSignal(cTOSSignalSomebodyMaintainActiveState);    
    }
}

//==============================================================================
// DESCRIPTION:         LAPAfsTreatSecurityAccessService
//
// PARAMETERS:          none
//
// RETURN VALUE:        none
//
// DESIGN INFORMATION:  refer to Detailed Design Document
//==============================================================================
MEM_TYPE void LAPAfsTreatSecurityAccessService(void)
{
#ifdef BOOTLOADER_IS_SUPPORTED

    BOOL bCheckDynamicParameters;
    #ifndef COMPILATION_NATIVE
    tBootLinkTable* pReturnToBoot;
    #endif

    if  ((mDATRead(U8Bit,DATKwpRxFrameLgth,Default) == cSAReq_Lngth)
      &&(LAPKwpReadDiagnosticRequest(1) == cLIdReqSecurityAccess1))
    {
        //QACJ 0305: akodzhh: Cast is intentional and safe
        bCheckDynamicParameters = (BOOL)mLAPKwpCheckBootJumpConditions();
        LDBRefreshWatchDog();

        if(bCheckDynamicParameters != cFalse)
        {
            //Execute specific command
            //QACJ 3141: akodzhh: Keep for readability
            mLAPKwpAddSpecificCommand();

            #ifndef COMPILATION_NATIVE
            // call LIBReturnToBoot function (defined in LIB_BOO.C)
            pReturnToBoot = (tBootLinkTable *)cLIBBooBootLinkTableAddress;
            (*pReturnToBoot->pReturnToBootLink)(bCheckDynamicParameters,(U16)TOSClock);
            // After the boot jump, a RESET is done by the BOOT
            #endif
        }
        else
        {
            LAPKwpPrepareNegativeResponse(cLAPKwpConditionNotCorrect);
            //Send negative response: execution condition not met
        }
    }
    else
    {
        // Prepare negative response  : Sub service not supported - invalid format 
        LAPKwpPrepareNegativeResponse(cLAPKwpInvalidFormat);
    }

#else  // bootloader not supported
    // negative response
    LAPKwpPrepareNegativeResponse(cLAPKwpServiceNotSupported);
#endif
    LAPKwpSetServiceIsFinished();
}
