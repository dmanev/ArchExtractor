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
// Component:    DAT_POU
// -----------------------------------------------------------------------------
// $Date:   Dec 14 2009 11:42:28  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_POU/DAT_POU.H-arc  $
// $Revision:   1.12  $
// -----------------------------------------------------------------------------
// $Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_POU/DAT_POU.H-arc   $
// 
//    Rev 1.12   Dec 14 2009 11:42:28   adzhelp
// Cm005566: Implementation of full HW protection and overvoltage protection
// 
//    Rev 1.11   Nov 26 2009 14:16:48   adzhelp
// Cm005566: QAC and unit test updates
// 
//    Rev 1.10   Nov 20 2009 17:36:28   akodzhh
// Cm005566: Added read macros for HW protection, used in TFC diag.
// 
//    Rev 1.9   Nov 18 2009 10:30:06   adzhelp
// Cm006629: Active protection of special outputs disabled
// 
//    Rev 1.8   Nov 10 2009 18:21:18   amanevd
// Cm006629: DO_VERLOG signal inverted
// 
//    Rev 1.7   Nov 04 2009 16:23:04   adzhelp
// Cm005566: Implementation of HW Protection
// 
//    Rev 1.6   Oct 07 2009 09:07:08   adzhelp
// Cm005497: Configuration of LDB_DOU according to ECUType 
// 
//    Rev 1.5   Jul 07 2009 15:40:40   akodzhh
// Cm005574: Parameterization of simulation after SW1 - LDBDou controls treatment.
// 
//    Rev 1.4   Apr 27 2009 15:29:52   akodzhh
// Cm003465: Diagnostic direct output control for simulation.
// 
//    Rev 1.3   Apr 23 2009 14:06:16   adzhelp
// Cm003272: Direct control of VERLOG_LED added
// 
//    Rev 1.2   Apr 22 2009 09:11:44   adzhelp
// Cm003272: Notification of DAT_TRP when diag on immobilizer output enabled
// 
//    Rev 1.1   Mar 20 2009 17:32:28   adzhelp
// Cm003619: Parameterization needed for diagnostics
// 
//    Rev 1.0   10 Nov 2008 10:26:18   ailievb
// Initial revision.
//******************************************************************************

#ifndef I_DAT_POU_H
#define I_DAT_POU_H (1)

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------
#include "deftypes.h"
#include "ldb.h"

#include "dat_dou.h"
#include "dat_poux.h"

//------------------------------------------------------------------------------
// Constant data
//------------------------------------------------------------------------------

// This is an example:
// #define cu16LAYCmpConstantName   ((U16)ConstantValue)

//------------------------------------------------------------------------------
// Exported Macros
//------------------------------------------------------------------------------
// Write macros
#define mDATPouWriteU1BitDelayed(ByteNbr,BitNbr,BitValue) \
  {\
    U8 Mask;\
    if (BitValue) \
    { \
      Mask = (U8)(1 << (BitNbr)); \
      *(DATPouSoftOutputBuffer+(ByteNbr)) |= Mask; \
    } \
    else  \
    { \
      Mask = (U8)~(1 << (BitNbr)); \
      *(DATPouSoftOutputBuffer+(ByteNbr)) &= Mask; \
    } \
  /*//QACJ 3435: adzhelp: standard STK macros used */\
  /*//QACJ 3456: adzhelp: standard STK macros used */\
  }

#define mDATPouWriteU1BitImmediate(ByteNbr,BitNbr,BitValue)   \
  {\
    if(mDATPouReadU1Bit(Inutile,ByteNbr, BitNbr, Default) != (BitValue))\
    {\
        mDATPouWriteU1BitDelayed(ByteNbr,BitNbr,BitValue);          \
        mDATDouRefreshOutput();\
    }\
  /*//QACJ 3435: adzhelp: standard STK macros used */\
  /*//QACJ 3456: adzhelp: standard STK macros used */\
  }

#define mDATPouWriteU1Bit(Inutile,ByteNbr,BitNbr,BitValue,TypeTraitement)\
  /*//QACJ 3443: adzhelp: standard STK macros used */\
  mDATPouWriteU1Bit##TypeTraitement(ByteNbr, BitNbr,BitValue)

// Read macros
#define mDATPouReadU1Bit(Inutile,ByteNbr,BitNbr,TypeTraitement) \
  /*//QACJ 3443: adzhelp: standard STK macros used */\
  mDATPouReadU1Bit##TypeTraitement(ByteNbr, BitNbr)

#define mDATPouReadU1BitDefault(ByteNbr,BitNbr) \
  ((DATPouSoftOutputBuffer[ByteNbr] & (1 << (BitNbr)))!=0)

#define mDATPouReadU1BitDelayed(ByteNbr,BitNbr) \
  ((DATPouSoftOutputBuffer[ByteNbr] & (1 << (BitNbr)))!=0)

#define mDATPouReadU1BitImmediate(ByteNbr,BitNbr) \
  ((DATDouOutputBuffer[ByteNbr] & (1 << (BitNbr)))!=0)

#define mDATPouRead(Inutile,Octet,Bit,Etat,TypeTraitement) \
  mDATDouLireU1Bit(Octet,Bit,Etat)

//-------------------------------------------------------------------------
// Diagnostique Settings to set directly an output 
// SetDiag mask write value on buffer and active DOU Task

#define mDATWriteTableU1BitDATPouDiagBufferDefault(Index,BitValue)          \
  {                                                                         \
    U16 u16Index = (U16)(Index);                                            \
    U8 ByteNbr  = (U8)(u16Index & 0x00FFU);                                 \
    U8 BitNbr = (U8)((u16Index>>8) & 0x00FFU);                              \
    DATPouDiagBuffer[ByteNbr] &= (U8) ~((U8)(1 << (BitNbr)));               \
    DATPouDiagBuffer[ByteNbr] |= (U8) (((BitValue) & 0x01U) << (BitNbr));   \
  }

#define mDATWriteTableU1BitDATPouDiagMaskBufferDefault(Index,BitValue)          \
  {                                                                             \
    U16 u16Index = (U16)(Index);                                                \
    U8 ByteNbr  = (U8)(u16Index & 0x00FFU);                                      \
    U8 BitNbr = (U8)((u16Index>>8) & 0x00FFU);                                   \
    DATPouDiagMaskBuffer[ByteNbr] &= (U8) ~((U8)(1 <<(BitNbr)));                \
    DATPouDiagMaskBuffer[ByteNbr] |= (U8) (((BitValue) & 0x01U) << (BitNbr));   \
  }

#define mDATReadTableU1BitDATPouDiagBufferDefault(Index)      \
    /*//QACJ 3435: adzhelp: macros reused from AW1092: no change needed*/\
    /*//QACJ 3456: adzhelp: macros reused from AW1092: no change needed*/\
    ((DATPouDiagBuffer[(U8)((Index) & 0x00FFU)] >> ((U8)(((Index)>>8) & 0x00FFU))) & 0x01U)

#define mDATReadTableU1BitDATPouDiagMaskBufferDefault(Index)  \
    /*//QACJ 3435: adzhelp: macros reused from AW1092: no change needed*/\
    /*//QACJ 3456: adzhelp: macros reused from AW1092: no change needed*/\
    ((DATPouDiagMaskBuffer[(U8)((Index) & 0x00FF)] >> ((U8)(((Index)>>8) & 0x00FF))) & 0x01U)

#define mDATPouWriteU1BitWriteDiagOutput(ByteNbr,BitNbr,BitValue)   \
  {                                                                 \
    U8 Mask = (1 << (BitNbr));                                      \
    DATPouDiagMaskBuffer[ByteNbr] |= Mask;                          \
    if (BitValue)                                                   \
    {                                                               \
      DATPouDiagBuffer[ByteNbr] |= Mask;                            \
    }                                                               \
    else                                                            \
    {                                                               \
      Mask = (U8) ~(1 << (BitNbr));                                 \
      DATPouDiagBuffer[ByteNbr] &= Mask;                            \
    }                                                               \
    mDATDouRefreshOutput();                                         \
    /*//QACJ 3435: adzhelp: macros reused from AW1092: no change needed*/\
    /*//QACJ 3456: adzhelp: macros reused from AW1092: no change needed*/\
  }

#define mDATPouWriteU1BitDisableDiagOutput(ByteNbr,BitNbr,Inutile)  \
  (DATPouDiagMaskBuffer[ByteNbr] &= (U8) ~(1 << (BitNbr)))

#define mDATPouReadU1BitReadDiagOutput(Inutile,ByteNbr,BitNbr)      \
  ((DATDouOutputBuffer[ByteNbr] & (1 << (BitNbr)))!=0)              

#define mDATPouReadU1BitReadDiagMask(Inutile,ByteNbr,BitNbr)        \
  ((DATPouDiagMaskBuffer[ByteNbr] & (1 << (BitNbr)))!=0)

//-------------------------------------------------------------------------
// Hardware Settings to disable or enable an output 
// if disabled, diag and application can't activate the associated output
//-------------------------------------------------------------------------
#define mDATPouWriteU1BitDisableOutput( ByteNbr, BitNbr, Inutile)  \
    { DATPouHardMaskBuffer[ ByteNbr ] |= (1 << (BitNbr));                 \
      mDATDouRefreshOutput();}  

#define mDATPouWriteU1BitEnableOutput(ByteNbr,BitNbr,Inutile)      \
  (DATPouHardMaskBuffer[ByteNbr] &= (U8) ~(1 << (BitNbr)))

#define mDATPouReadU1BitReadHardMask(Inutile,ByteNbr,BitNbr)        \
  ((DATPouHardMaskBuffer[ByteNbr] & (1 << (BitNbr)))!=0)
  
//-------------------------------------------------------------------------
// control macros

#define mDATControlPouEnterNominalMode()  DATDouEnterNominalMode()
#define mDATControlPouEnterSleepMode()    DATDouEnterSleepMode()

#define mDATControlPouInit()              DATDouInit(DATPouInitArray)

/*//QACJ 3443: adzhelp: standard STK macros used */\
#define mDATControlPou(Cmd)               mDATControlPou##Cmd()

//----------------------------
//  Hardware protection macros 
//----------------------------
// Write access

//VERLOG_LEDProtection
#define mDATWriteU1BitVERLOG_LEDProtectionDefault( Value )              \
{\
  bVERLOG_LEDDirectProtected = (BOOL)(Value);\
  mDATWriteU1BitOutputProtectionDefault(bVERLOG_LEDDirectProtected, cDATPouVERLOG_LEDByteIndex, cDATPouVERLOG_LEDBitIndex); \
}

//OPEN_DOOR_LEDProtection
#define mDATWriteU1BitOPEN_DOOR_LEDProtectionDefault( Value )              \
  mDATWriteU1BitOutputProtectionDefault(Value, cDATPouOPEN_DOOR_LEDByteIndex, cDATPouOPEN_DOOR_LEDBitIndex)

//DEFROSTERProtection
#define mDATWriteU1BitDEFROSTERProtectionDefault( Value )              \
  mDATWriteU1BitOutputProtectionDefault(Value, cDATPouDEFROSTERByteIndex, cDATPouDEFROSTERBitIndex)
#define mDATWriteU1BitDEFROSTERProtectionDelayed( Value )              \
  mDATWriteU1BitOutputProtectionDelayed(Value, cDATPouDEFROSTERByteIndex, cDATPouDEFROSTERBitIndex)

//HORN_RLProtection
#define mDATWriteU1BitHORN_RLProtectionDefault( Value )              \
  mDATWriteU1BitOutputProtectionDefault(Value, cDATPouHORN_RLByteIndex, cDATPouHORN_RLBitIndex)
#define mDATWriteU1BitHORN_RLProtectionDelayed( Value )              \
  mDATWriteU1BitOutputProtectionDelayed(Value, cDATPouHORN_RLByteIndex, cDATPouHORN_RLBitIndex)

//LOCK_DOORSProtection
#define mDATWriteU1BitLOCK_DOORSProtectionDefault( Value )              \
  mDATWriteU1BitOutputProtectionDefault(Value, cDATPouLOCK_DOORSByteIndex, cDATPouLOCK_DOORSBitIndex)
#define mDATWriteU1BitLOCK_DOORSProtectionDelayed( Value )              \
  mDATWriteU1BitOutputProtectionDelayed(Value, cDATPouLOCK_DOORSByteIndex, cDATPouLOCK_DOORSBitIndex)

//UNLOCK_DOORSProtection
#define mDATWriteU1BitUNLOCK_DOORSProtectionDefault( Value )              \
  mDATWriteU1BitOutputProtectionDefault(Value, cDATPouUNLOCK_DOORSByteIndex, cDATPouUNLOCK_DOORSBitIndex)
#define mDATWriteU1BitUNLOCK_DOORSProtectionDelayed( Value )              \
  mDATWriteU1BitOutputProtectionDelayed(Value, cDATPouUNLOCK_DOORSByteIndex, cDATPouUNLOCK_DOORSBitIndex)

//BAT_LIGHT_TEMPOProtection
#define mDATWriteU1BitBAT_LIGHT_TEMPOProtectionDefault( Value )              \
  mDATWriteU1BitOutputProtectionDefault(Value, cDATPouBAT_LIGHT_TEMPOByteIndex, cDATPouBAT_LIGHT_TEMPOBitIndex)
#define mDATWriteU1BitBAT_LIGHT_TEMPOProtectionDelayed( Value )              \
  mDATWriteU1BitOutputProtectionDelayed(Value, cDATPouBAT_LIGHT_TEMPOByteIndex, cDATPouBAT_LIGHT_TEMPOBitIndex)

//UNLOCK_DRIVER_DOORProtection
#define mDATWriteU1BitUNLOCK_DRIVER_DOORProtectionDefault( Value )              \
  mDATWriteU1BitOutputProtectionDefault(Value, cDATPouUNLOCK_DRIVER_DOORByteIndex, cDATPouUNLOCK_DRIVER_DOORBitIndex)
#define mDATWriteU1BitUNLOCK_DRIVER_DOORProtectionDelayed( Value )              \
  mDATWriteU1BitOutputProtectionDelayed(Value, cDATPouUNLOCK_DRIVER_DOORByteIndex, cDATPouUNLOCK_DRIVER_DOORBitIndex)

//FRONT_WIPERProtection
#define mDATWriteU1BitFRONT_WIPERProtectionDefault( Value )              \
  mDATWriteU1BitOutputProtectionDefault(Value, cDATPouFRONT_WIPERByteIndex, cDATPouFRONT_WIPERBitIndex)
#define mDATWriteU1BitFRONT_WIPERProtectionDelayed( Value )              \
  mDATWriteU1BitOutputProtectionDelayed(Value, cDATPouFRONT_WIPERByteIndex, cDATPouFRONT_WIPERBitIndex)

//RR_WIPER_RR_FOG_LAMPProtection
#define mDATWriteU1BitRR_WIPER_RR_FOG_LAMPProtectionDefault( Value )              \
  mDATWriteU1BitOutputProtectionDefault(Value, cDATPouRR_WIPER_RR_FOG_LAMPByteIndex, cDATPouRR_WIPER_RR_FOG_LAMPBitIndex)
#define mDATWriteU1BitRR_WIPER_RR_FOG_LAMPProtectionDelayed( Value )              \
  mDATWriteU1BitOutputProtectionDelayed(Value, cDATPouRR_WIPER_RR_FOG_LAMPByteIndex, cDATPouRR_WIPER_RR_FOG_LAMPBitIndex)

//DI_LEFTProtection
#define mDATWriteU1BitDI_LEFTProtectionDefault( Value )              \
  mDATWriteU1BitOutputProtectionDefault(Value, cDATPouDI_LEFTByteIndex, cDATPouDI_LEFTBitIndex)
#define mDATWriteU1BitDI_LEFTProtectionDelayed( Value )              \
  mDATWriteU1BitOutputProtectionDelayed(Value, cDATPouDI_LEFTByteIndex, cDATPouDI_LEFTBitIndex)

//DI_RIGHTProtection
#define mDATWriteU1BitDI_RIGHTProtectionDefault( Value )              \
  mDATWriteU1BitOutputProtectionDefault(Value, cDATPouDI_RIGHTByteIndex, cDATPouDI_RIGHTBitIndex)
#define mDATWriteU1BitDI_RIGHTProtectionDelayed( Value )              \
  mDATWriteU1BitOutputProtectionDelayed(Value, cDATPouDI_RIGHTByteIndex, cDATPouDI_RIGHTBitIndex)

//Read access

//VERLOG_LEDProtection
#define mDATReadU1BitVERLOG_LEDProtectionDefault()              \
  mDATReadU1BitOutputProtectionDefault(cDATPouVERLOG_LEDByteIndex, cDATPouVERLOG_LEDBitIndex)

//OPEN_DOOR_LEDProtection
#define mDATReadU1BitOPEN_DOOR_LEDProtectionDefault()              \
  mDATReadU1BitOutputProtectionDefault(cDATPouOPEN_DOOR_LEDByteIndex, cDATPouOPEN_DOOR_LEDBitIndex)

//DEFROSTERProtection
#define mDATReadU1BitDEFROSTERProtectionDefault()              \
  mDATReadU1BitOutputProtectionDefault(cDATPouDEFROSTERByteIndex, cDATPouDEFROSTERBitIndex)

//HORN_RLProtection
#define mDATReadU1BitHORN_RLProtectionDefault()              \
  mDATReadU1BitOutputProtectionDefault(cDATPouHORN_RLByteIndex, cDATPouHORN_RLBitIndex)

//LOCK_DOORSProtection
#define mDATReadU1BitLOCK_DOORSProtectionDefault()              \
  mDATReadU1BitOutputProtectionDefault(cDATPouLOCK_DOORSByteIndex, cDATPouLOCK_DOORSBitIndex)

//UNLOCK_DOORSProtection
#define mDATReadU1BitUNLOCK_DOORSProtectionDefault()              \
  mDATReadU1BitOutputProtectionDefault(cDATPouUNLOCK_DOORSByteIndex, cDATPouUNLOCK_DOORSBitIndex)

//BAT_LIGHT_TEMPOProtection
#define mDATReadU1BitBAT_LIGHT_TEMPOProtectionDefault()              \
  mDATReadU1BitOutputProtectionDefault(cDATPouBAT_LIGHT_TEMPOByteIndex, cDATPouBAT_LIGHT_TEMPOBitIndex)

//UNLOCK_DRIVER_DOORProtection
#define mDATReadU1BitUNLOCK_DRIVER_DOORProtectionDefault()              \
  mDATReadU1BitOutputProtectionDefault(cDATPouUNLOCK_DRIVER_DOORByteIndex, cDATPouUNLOCK_DRIVER_DOORBitIndex)

//FRONT_WIPERProtection
#define mDATReadU1BitFRONT_WIPERProtectionDefault()              \
  mDATReadU1BitOutputProtectionDefault(cDATPouFRONT_WIPERByteIndex, cDATPouFRONT_WIPERBitIndex)

//RR_WIPER_RR_FOG_LAMPProtection
#define mDATReadU1BitRR_WIPER_RR_FOG_LAMPProtectionDefault()              \
  mDATReadU1BitOutputProtectionDefault(cDATPouRR_WIPER_RR_FOG_LAMPByteIndex, cDATPouRR_WIPER_RR_FOG_LAMPBitIndex)

//DI_LEFTProtection
#define mDATReadU1BitDI_LEFTProtectionDefault()              \
  mDATReadU1BitOutputProtectionDefault(cDATPouDI_LEFTByteIndex, cDATPouDI_LEFTBitIndex)

//DI_RIGHTProtection
#define mDATReadU1BitDI_RIGHTProtectionDefault()              \
  mDATReadU1BitOutputProtectionDefault(cDATPouDI_RIGHTByteIndex, cDATPouDI_RIGHTBitIndex)


//-------------------------------------------------------------------------

#ifndef _QAC_

#define mDATWriteU1BitOutputProtectionDefault(BitValue, ByteNbr, BitNbr) \
    mDATWriteU1BitOutputProtectionImmediate(BitValue, ByteNbr, BitNbr)

#define mDATWriteU1BitOutputProtectionImmediate(BitValue, ByteNbr, BitNbr)\
  {\
    U8 Mask;\
    if ((BitValue)) \
    { \
      Mask = (1 << (BitNbr)); \
      *(DATPouHardMaskBuffer+(ByteNbr)) |= Mask; \
      mDATDouRefreshOutput();\
    } \
    else  \
    { \
      Mask = (U8)~(1 << (BitNbr)); \
      *(DATPouHardMaskBuffer+(ByteNbr)) &= Mask; \
    } \
  }

#define mDATWriteU1BitOutputProtectionDelayed(BitValue, ByteNbr, BitNbr)\
  {\
    U8 Mask;\
    if ((BitValue)) \
    { \
      Mask = (1 << (BitNbr)); \
      *(DATPouHardMaskBuffer+(ByteNbr)) |= Mask; \
    } \
    else  \
    { \
      Mask = (U8)~(1 << (BitNbr)); \
      *(DATPouHardMaskBuffer+(ByteNbr)) &= Mask; \
    } \
  }

#else
#define mDATWriteU1BitOutputProtectionDefault(BitValue, ByteNbr, BitNbr) NOP()
#define mDATWriteU1BitOutputProtectionDelayed(BitValue, ByteNbr, BitNbr) NOP()
#endif

#define mDATReadU1BitOutputProtectionDefault(ByteNbr, BitNbr)\
      ((*(DATPouHardMaskBuffer+(ByteNbr)) >> (BitNbr)) & (U8)1)\

#define mDATReadTableU1BitDATPouHardMaskBufferDefault(Index)  \
    /*//QACJ 3435: adzhelp: macros reused from AW1092: no change needed*/\
    /*//QACJ 3456: adzhelp: macros reused from AW1092: no change needed*/\
    ((DATPouHardMaskBuffer[(U8)((Index) & 0x00FF)] >> ((U8)(((Index)>>8) & 0x00FF))) & 0x01U)

//-------------------------------------------------------------------------
// Special outputs

// DO_VERLOG
#define mDATWriteU1BitDO_VERLOGDefault(Val) \
    { \
        if (bDO_VERLOGDiagEnabled == cFalse) \
        { \
            tCtrl Ctrl; \
            bDO_VERLOG = (Val); \
            Ctrl = (((bDO_VERLOG != cFalse) && (cFalse == bDO_VERLOGProtected) ) \
                                        ? cLDBControlSetDO_VERLOG \
                                        : cLDBControlClearDO_VERLOG); \
            LDBControl(cLDBChannelDou, Ctrl); \
        } \
    }

#define mDATReadU1BitDO_VERLOGDefault() bDO_VERLOG // this flag is common for diag and appli
#define mDATReadU1BitDO_VERLOGImmediate()   \
        ((cFalse != bDO_VERLOG) && (cFalse == bDO_VERLOGProtected))


// VERLOG_LEDDirect
#define mDATWriteU1BitVERLOG_LEDDirectDefault(Val) \
{ \
    tCtrl Ctrl = ( (((Val) != cFalse) && (bVERLOG_LEDDirectProtected == cFalse) ) \
                                    ? cLDBControlSetVERLOG_LED \
                                    : cLDBControlClearVERLOG_LED); \
    LDBControl(cLDBChannelDou, Ctrl); \
}


// Diagnostic mode of special outputs

// DO_DATA_IMMOBILIZERDiag / DO_DATA_IMMOBILIZERDiagEnabled
#define mDATWriteU1BitDO_DATA_IMMOBILIZERDiagEnabledDefault(Val) \
    { \
        bDO_DATA_IMMOBILIZERDiagEnabled = (Val); \
        /* Control immobilizer: */ \
        if (bDO_DATA_IMMOBILIZERDiagEnabled == cFalse) \
        { \
            mDATControl(Trp, cDATTrpDeactivateDiag); \
        } \
        else \
        { \
            mDATControl(Trp, cDATTrpActivateDiag); \
        } \
    }
#define mDATReadU1BitDO_DATA_IMMOBILIZERDiagEnabledDefault()    bDO_DATA_IMMOBILIZERDiagEnabled
#define mDATWriteU1BitDO_DATA_IMMOBILIZERDiagDefault(Val) \
    { \
        mLIBassert(bDO_DATA_IMMOBILIZERDiagEnabled != cFalse); \
        LDBControl(cLDBChannelDou, ((Val) != cFalse) ? cLDBControlSetDO_DATA_IMMOBILIZER \
                                                     : cLDBControlClearDO_DATA_IMMOBILIZER); \
    }

// DO_VERLOGDiag / DO_VERLOGDiagEnabled
#define mDATWriteU1BitDO_VERLOGDiagEnabledDefault(Val) \
    (bDO_VERLOGDiagEnabled = (BOOL)(Val)) 
#define mDATReadU1BitDO_VERLOGDiagEnabledDefault()  bDO_VERLOGDiagEnabled
#define mDATWriteU1BitDO_VERLOGDiagDefault(Val) \
    { \
        tCtrl Ctrl; \
        bDO_VERLOG = (Val); \
        Ctrl = (((bDO_VERLOG != cFalse) && (cFalse == bDO_VERLOGProtected) ) \
                                    ? cLDBControlSetDO_VERLOG \
                                    : cLDBControlClearDO_VERLOG ); \
        mLIBassert(bDO_VERLOGDiagEnabled != cFalse); \
        LDBControl(cLDBChannelDou, Ctrl ); \
    }

// Protection of special outputs

// DO_VERLOGProtection
#define mDATReadU1BitDO_VERLOGProtectionDefault()   bDO_VERLOGProtected
#define mDATWriteU1BitDO_VERLOGProtectionDefault( Value )   \
    { \
        tCtrl Ctrl; \
        bDO_VERLOGProtected = (BOOL)(Value); \
        \
        Ctrl = (((bDO_VERLOG != cFalse) && (cFalse == bDO_VERLOGProtected) ) \
                                        ? cLDBControlSetDO_VERLOG \
                                        : cLDBControlClearDO_VERLOG); \
        LDBControl(cLDBChannelDou, Ctrl); \
    }

// DO_DATA_IMMOBILIZERProtection
#define mDATReadU1BitDO_DATA_IMMOBILIZERProtectionDefault()     bDO_DATA_IMMOBILIZERProtected
#define mDATWriteU1BitDO_DATA_IMMOBILIZERProtectionDefault(Val) \
    (bDO_DATA_IMMOBILIZERProtected = (BOOL)(Val))
        
//------------------------------------------------------------------------------
// Exported type
//------------------------------------------------------------------------------

// This is an example:
// typedef Expression tLAYCmpTypeName;

//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------
extern MEM_FAST U8 DATPouSoftOutputBuffer[cDATPouSizeDouGeneratorMessage];
extern MEM_FAST U8 DATPouDiagMaskBuffer[cDATPouSizeDouGeneratorMessage];
extern MEM_FAST U8 DATPouDiagBuffer[cDATPouSizeDouGeneratorMessage];
extern MEM_FAST U8 DATPouHardMaskBuffer[cDATPouSizeDouGeneratorMessage];

extern BOOL bDO_DATA_IMMOBILIZERDiagEnabled;
extern BOOL bDO_VERLOGDiagEnabled;

extern BOOL bDO_VERLOG;
extern BOOL bDO_VERLOGProtected;
extern BOOL bVERLOG_LEDDirectProtected;
extern BOOL bDO_DATA_IMMOBILIZERProtected;

//------------------------------------------------------------------------------
// Constant exported data
//------------------------------------------------------------------------------
extern const U8 DATPouInitArray[cDATPouSizeDouGeneratorMessage];

//------------------------------------------------------------------------------
// Exported functions
//------------------------------------------------------------------------------
extern void DATPouInit(void);
//QACJ 3451: function is declared in standard component as well
extern MEM_TYPE void DATPouPrepareRefresh(void);
extern void DATPouLeaveStartingStepState(void);
extern void DATPouLeaveActiveState(void);
extern void DATPouActivateFinalTest(void);
extern void DATPouAirbagUnlockStarted(void);
extern void DATPouAirbagUnlockFinished(void);

#endif  /* I_DAT_POU_H */
