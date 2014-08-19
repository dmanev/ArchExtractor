/*---------------------------------------------------------------------------

                This software is JCI property
                -----------------------------

    Duplication or disclosure is prohibited without JCI
    written permission.
    This file has been automatically generated with an excel file,
    by a visual basic macro.

 File                        : DAT_PEEx.h
 Project                     : STK
 Fonction                    : EEP
 Author                      : Petar Dzhelekarski
 Automatically generated on  : 20.9.2010 ã. a 14:34:03 
 Source file                 : DAT_EEPM.XLA
 Macro version               : 01.29
 Configuration version       : 02.05

---------------------------------------------------------------------------*/

#ifndef I_PEE_PARAM_H
#define I_PEE_PARAM_H (1)

//--------------------------------------------------------------------------
//----  Declaration of constants and macros exported by this component  ----
//--------------------------------------------------------------------------
//
// (Com: 3 letters identifying this component)
// #define cDATPeeNomConstante   ValeurDeLaConstante
//
// (Com: 3 letters identifying this component)
// #define mDATPeeNomMacro   (DefinitionDeLaMacro)


//--------------------------------------------------------------------------
//  Global Declaration
//--------------------------------------------------------------------------

#define mDATControlEep(Command)\
    mDATControlEep##Command();     

#define mDATControlEepInit()\
    DATEepInit();   \
    DATSbkInit();   \
    DATDbkInit();   \
    DATPeeInit();   \

#define mDATControlEepRestore()\
    DATDbkStartRestoringBrokenBanks();     \

#define mDATControlEepReadEep()\
    DATSbkStartReadingAllBanks();     \
    DATDbkStartReadingAllBanks();     \


//--------------------------------------------------------------------------
// Groups declarations
//--------------------------------------------------------------------------

// Information on the Group ErrorGroup
#define cDATPeeNumberOfDataErrorGroup         1 
#define cDATPeeSizeErrorGroup         10 
#ifdef cFormatMotorola
#define mDATPeeResetBufferErrorGroup()        {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0  \
     ,0xFF }
#else
#define mDATPeeResetBufferErrorGroup()        {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0  \
     ,0xFF }
#endif

#define mDATControlEepReadEepGroupErrorGroup()\
    DATSbkStartReading(cDATSbkHandleErrorGroup)

#define mDATReadU1BitIsEepGroupErrorGroupProcessingDefault() \
    DATSbkIsBankProcessing(cDATSbkHandleErrorGroup)

#define mDATControlEepUpDateEepGroupErrorGroup()\
    DATSbkStartUpdate(cDATSbkHandleErrorGroup)

#define mDATReadU1BitIsEepGroupErrorGroupWriteOkDefault() \
    DATSbkIsWriteOk(cDATSbkHandleErrorGroup)

// Information on the Group SupplierBank
#define cDATPeeNumberOfDataSupplierBank         14 
#define cDATPeeSizeSupplierBank         26 
#ifdef cFormatMotorola
#define mDATPeeResetBufferSupplierBank()        {0x0,0x1,0x96,0x20,0x27,0x82,0x1,0x2  \
     ,0x93,0x91,0x0,0x0,0x0,0x0,0x3,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x4,0x8C,0x8C,0x0  \
      }
#else
#define mDATPeeResetBufferSupplierBank()        {0x0,0x1,0x96,0x20,0x27,0x82,0x1,0x2  \
     ,0x93,0x91,0x0,0x0,0x0,0x0,0x3,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x4,0x8C,0x8C,0x0  \
      }
#endif

#define mDATControlEepReadEepGroupSupplierBank()\
    DATSbkStartReading(cDATSbkHandleSupplierBank)

#define mDATReadU1BitIsEepGroupSupplierBankProcessingDefault() \
    DATSbkIsBankProcessing(cDATSbkHandleSupplierBank)

#define mDATControlEepUpDateEepGroupSupplierBank()\
    DATSbkStartUpdate(cDATSbkHandleSupplierBank)

#define mDATReadU1BitIsEepGroupSupplierBankWriteOkDefault() \
    DATSbkIsWriteOk(cDATSbkHandleSupplierBank)

// Information on the Group DiagBank
#define cDATPeeNumberOfDataDiagBank         34 
#define cDATPeeSizeDiagBank         24 
#ifdef cFormatMotorola
#define mDATPeeResetBufferDiagBank()        {0xE,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0  \
     ,0x0,0x0,0x0,0x0,0x27,0x10,0x0,0x0,0x0,0x0 | 0x0 | 0x0 | 0x0 | 0x0 | 0x0 | 0x0 | 0x0  \
     ,0x0 | 0x0 | 0x0 | 0x0 | 0x0 | 0x0 | 0x0 | 0x0,0x0 | 0x0,0x0,0x0 }
#else
#define mDATPeeResetBufferDiagBank()        {0xE,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0  \
     ,0x0,0x0,0x0,0x0,0x10,0x27,0x0,0x0,0x0,0x0 | 0x0 | 0x0 | 0x0 | 0x0 | 0x0 | 0x0 | 0x0  \
     ,0x0 | 0x0 | 0x0 | 0x0 | 0x0 | 0x0 | 0x0 | 0x0,0x0 | 0x0,0x0,0x0 }
#endif

#define mDATControlEepReadEepGroupDiagBank()\
    DATDbkStartReading(cDATDbkHandleDiagBank)

#define mDATReadU1BitIsEepGroupDiagBankProcessingDefault() \
    DATDbkIsBankProcessing(cDATDbkHandleDiagBank)

#define mDATControlEepUpDateEepGroupDiagBank()\
    DATDbkStartUpdate(cDATDbkHandleDiagBank)

#define mDATReadU1BitIsEepGroupDiagBankWriteOkDefault() \
    DATDbkIsWriteOk(cDATDbkHandleDiagBank)

// Information on the Group VersionBank
#define cDATPeeNumberOfDataVersionBank         2 
#define cDATPeeSizeVersionBank         2 
#ifdef cFormatMotorola
#define mDATPeeResetBufferVersionBank()        {0x2,0x5 }
#else
#define mDATPeeResetBufferVersionBank()        {0x2,0x5 }
#endif

#define mDATControlEepReadEepGroupVersionBank()\
    DATSbkStartReading(cDATSbkHandleVersionBank)

#define mDATReadU1BitIsEepGroupVersionBankProcessingDefault() \
    DATSbkIsBankProcessing(cDATSbkHandleVersionBank)

#define mDATControlEepUpDateEepGroupVersionBank()\
    DATSbkStartUpdate(cDATSbkHandleVersionBank)

#define mDATReadU1BitIsEepGroupVersionBankWriteOkDefault() \
    DATSbkIsWriteOk(cDATSbkHandleVersionBank)

// Information on the Group GeneralParameterBank
#define cDATPeeNumberOfDataGeneralParameterBank         36 
#define cDATPeeSizeGeneralParameterBank         6 
#ifdef cFormatMotorola
#define mDATPeeResetBufferGeneralParameterBank()        {0x0 | 0x0 | 0x0 | 0x0 | 0x0 | 0x0 | 0x0 | 0x0,0x0 | 0x0 | 0x0 | 0x0 | 0x0 | 0x0 | 0x0 | 0x0  \
     ,0x0 | 0x0 | 0x0 | 0x0 | 0x0 | 0x0 | 0x0 | 0x80,0x1 | 0x0 | 0x0 | 0x0 | 0x10 | 0x0 | 0x0 | 0x0  \
     ,0x0 | 0x0 | 0x0,0x0 }
#else
#define mDATPeeResetBufferGeneralParameterBank()        {0x0 | 0x0 | 0x0 | 0x0 | 0x0 | 0x0 | 0x0 | 0x0,0x0 | 0x0 | 0x0 | 0x0 | 0x0 | 0x0 | 0x0 | 0x0  \
     ,0x0 | 0x0 | 0x0 | 0x0 | 0x0 | 0x0 | 0x0 | 0x80,0x1 | 0x0 | 0x0 | 0x0 | 0x10 | 0x0 | 0x0 | 0x0  \
     ,0x0 | 0x0 | 0x0,0x0 }
#endif

#define mDATControlEepReadEepGroupGeneralParameterBank()\
    DATDbkStartReading(cDATDbkHandleGeneralParameterBank)

#define mDATReadU1BitIsEepGroupGeneralParameterBankProcessingDefault() \
    DATDbkIsBankProcessing(cDATDbkHandleGeneralParameterBank)

#define mDATControlEepUpDateEepGroupGeneralParameterBank()\
    DATDbkStartUpdate(cDATDbkHandleGeneralParameterBank)

#define mDATReadU1BitIsEepGroupGeneralParameterBankWriteOkDefault() \
    DATDbkIsWriteOk(cDATDbkHandleGeneralParameterBank)

// Information on the Group FactoryConfigBank
#define cDATPeeNumberOfDataFactoryConfigBank         37 
#define cDATPeeSizeFactoryConfigBank         38 
#ifdef cFormatMotorola
#define mDATPeeResetBufferFactoryConfigBank()        {0x1,0xF4,0x25,0x24,0x0,0x2,0x14  \
     ,0xF,0x1,0x3,0x2A,0x3E,0x19,0x0,0x2,0x3,0x8,0x4,0x5,0x24,0xE,0x8,0x5C,0xA,0xA  \
     ,0x8,0x32,0x14,0x2,0x1E,0xA,0xA,0x4,0x4,0x5,0x64,0x0,0x0 }
#else
#define mDATPeeResetBufferFactoryConfigBank()        {0xF4,0x1,0x25,0x24,0x0,0x2,0x14  \
     ,0xF,0x1,0x3,0x2A,0x3E,0x19,0x0,0x2,0x3,0x8,0x4,0x5,0x24,0xE,0x8,0x5C,0xA,0xA  \
     ,0x8,0x32,0x14,0x2,0x1E,0xA,0xA,0x4,0x4,0x5,0x64,0x0,0x0 }
#endif

#define mDATControlEepReadEepGroupFactoryConfigBank()\
    DATDbkStartReading(cDATDbkHandleFactoryConfigBank)

#define mDATReadU1BitIsEepGroupFactoryConfigBankProcessingDefault() \
    DATDbkIsBankProcessing(cDATDbkHandleFactoryConfigBank)

#define mDATControlEepUpDateEepGroupFactoryConfigBank()\
    DATDbkStartUpdate(cDATDbkHandleFactoryConfigBank)

#define mDATReadU1BitIsEepGroupFactoryConfigBankWriteOkDefault() \
    DATDbkIsWriteOk(cDATDbkHandleFactoryConfigBank)

// Information on the Group VINBank
#define cDATPeeNumberOfDataVINBank         1 
#define cDATPeeSizeVINBank         19 
#ifdef cFormatMotorola
#define mDATPeeResetBufferVINBank()        {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0  \
     ,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0 }
#else
#define mDATPeeResetBufferVINBank()        {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0  \
     ,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0 }
#endif

#define mDATControlEepReadEepGroupVINBank()\
    DATSbkStartReading(cDATSbkHandleVINBank)

#define mDATReadU1BitIsEepGroupVINBankProcessingDefault() \
    DATSbkIsBankProcessing(cDATSbkHandleVINBank)

#define mDATControlEepUpDateEepGroupVINBank()\
    DATSbkStartUpdate(cDATSbkHandleVINBank)

#define mDATReadU1BitIsEepGroupVINBankWriteOkDefault() \
    DATSbkIsWriteOk(cDATSbkHandleVINBank)

// Information on the Group StaticImmoBank
#define cDATPeeNumberOfDataStaticImmoBank         19 
#define cDATPeeSizeStaticImmoBank         76 
#ifdef cFormatMotorola
#define mDATPeeResetBufferStaticImmoBank()        {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0  \
     ,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0  \
     ,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0  \
     ,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0  \
     ,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1 | 0x0 | 0x0 | 0x0 | 0x10 }
#else
#define mDATPeeResetBufferStaticImmoBank()        {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0  \
     ,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0  \
     ,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0  \
     ,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0  \
     ,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1 | 0x0 | 0x0 | 0x0 | 0x10 }
#endif

#define mDATControlEepReadEepGroupStaticImmoBank()\
    DATDbkStartReading(cDATDbkHandleStaticImmoBank)

#define mDATReadU1BitIsEepGroupStaticImmoBankProcessingDefault() \
    DATDbkIsBankProcessing(cDATDbkHandleStaticImmoBank)

#define mDATControlEepUpDateEepGroupStaticImmoBank()\
    DATDbkStartUpdate(cDATDbkHandleStaticImmoBank)

#define mDATReadU1BitIsEepGroupStaticImmoBankWriteOkDefault() \
    DATDbkIsWriteOk(cDATDbkHandleStaticImmoBank)

// Information on the Group DynamicImmoDataBank
#define cDATPeeNumberOfDataDynamicImmoDataBank         5 
#define cDATPeeSizeDynamicImmoDataBank         65 
#ifdef cFormatMotorola
#define mDATPeeResetBufferDynamicImmoDataBank()        {0x0,0x0,0x0,0x0,0x0,0x0,0x0  \
     ,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0  \
     ,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0  \
     ,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0  \
     ,0x0 }
#else
#define mDATPeeResetBufferDynamicImmoDataBank()        {0x0,0x0,0x0,0x0,0x0,0x0,0x0  \
     ,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0  \
     ,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0  \
     ,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0  \
     ,0x0 }
#endif

#define mDATControlEepReadEepGroupDynamicImmoDataBank()\
    DATDbkStartReading(cDATDbkHandleDynamicImmoDataBank)

#define mDATReadU1BitIsEepGroupDynamicImmoDataBankProcessingDefault() \
    DATDbkIsBankProcessing(cDATDbkHandleDynamicImmoDataBank)

#define mDATControlEepUpDateEepGroupDynamicImmoDataBank()\
    DATDbkStartUpdate(cDATDbkHandleDynamicImmoDataBank)

#define mDATReadU1BitIsEepGroupDynamicImmoDataBankWriteOkDefault() \
    DATDbkIsWriteOk(cDATDbkHandleDynamicImmoDataBank)

// Information on the Group SpareBank
#define cDATPeeNumberOfDataSpareBank         1 
#define cDATPeeSizeSpareBank         2 
#ifdef cFormatMotorola
#define mDATPeeResetBufferSpareBank()        {0x0,0x0 }
#else
#define mDATPeeResetBufferSpareBank()        {0x0,0x0 }
#endif

#define mDATControlEepReadEepGroupSpareBank()\
    DATSbkStartReading(cDATSbkHandleSpareBank)

#define mDATReadU1BitIsEepGroupSpareBankProcessingDefault() \
    DATSbkIsBankProcessing(cDATSbkHandleSpareBank)

#define mDATControlEepUpDateEepGroupSpareBank()\
    DATSbkStartUpdate(cDATSbkHandleSpareBank)

#define mDATReadU1BitIsEepGroupSpareBankWriteOkDefault() \
    DATSbkIsWriteOk(cDATSbkHandleSpareBank)


//--------------------------------------------------------------------------
// Functionnal data declaration
//--------------------------------------------------------------------------

// EEPErrorTable -- Group ErrorGroup, Byte  0  , Bit (MSB)  7  , SizeInBit  80 
#ifdef EEPErrorTable
  #error "Do not define EEPErrorTable, because this is a lexem used for concatenation."
#endif
#define mDATPeeResetEEPErrorTable()     \
{                                                     \
   mDATPeeWriteTable(U8Bit,Sbk,ErrorGroup,  0 ,  0, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,ErrorGroup,  0 ,  1, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,ErrorGroup,  0 ,  2, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,ErrorGroup,  0 ,  3, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,ErrorGroup,  0 ,  4, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,ErrorGroup,  0 ,  5, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,ErrorGroup,  0 ,  6, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,ErrorGroup,  0 ,  7, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,ErrorGroup,  0 ,  8, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,ErrorGroup,  0 ,  9, -1, Delayed) \
}
#define mDATReadTableU1BitEEPErrorTableDefaultValueDefault( Index ) \
      mDATPeeReadDefaultTable(U1Bit,Sbk, ErrorGroup,  0 , Index, Delayed)

#define mDATReadTableU8BitEEPErrorTableDefault( Index ) \
      mDATPeeReadTable(U8Bit,Sbk, ErrorGroup,  0 , Index, Delayed)
#define mDATWriteTableU8BitEEPErrorTableDelayed( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Sbk, ErrorGroup,  0 , Index, (ValueToWrite), Delayed)
#define mDATWriteTableU8BitEEPErrorTableImmediate( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Sbk, ErrorGroup,  0 , Index, (ValueToWrite), Immediate)
#define mDATWriteTableU8BitEEPErrorTableDefault( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Sbk, ErrorGroup,  0 , Index, (ValueToWrite), Immediate)

// EEP_PieNumber -- Group SupplierBank, Byte  0  , Bit (MSB)  7  , SizeInBit  40 
#ifdef EEP_PieNumber
  #error "Do not define EEP_PieNumber, because this is a lexem used for concatenation."
#endif
#define mDATPeeResetEEP_PieNumber()     \
{                                                     \
   mDATPeeWriteTable(U8Bit,Sbk,SupplierBank,  0 ,  0, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,SupplierBank,  0 ,  1, 1, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,SupplierBank,  0 ,  2, 150, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,SupplierBank,  0 ,  3, 32, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,SupplierBank,  0 ,  4, 39, Delayed) \
}
#define mDATReadTableU1BitEEP_PieNumberDefaultValueDefault( Index ) \
      mDATPeeReadDefaultTable(U1Bit,Sbk, SupplierBank,  0 , Index, Delayed)

#define mDATReadTableU8BitEEP_PieNumberDefault( Index ) \
      mDATPeeReadTable(U8Bit,Sbk, SupplierBank,  0 , Index, Delayed)
#define mDATWriteTableU8BitEEP_PieNumberDelayed( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Sbk, SupplierBank,  0 , Index, (ValueToWrite), Delayed)
#define mDATWriteTableU8BitEEP_PieNumberImmediate( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Sbk, SupplierBank,  0 , Index, (ValueToWrite), Immediate)
#define mDATWriteTableU8BitEEP_PieNumberDefault( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Sbk, SupplierBank,  0 , Index, (ValueToWrite), Immediate)

// EEP_ECUReference -- Group SupplierBank, Byte  5  , Bit (MSB)  7  , SizeInBit  40 
#ifdef EEP_ECUReference
  #error "Do not define EEP_ECUReference, because this is a lexem used for concatenation."
#endif
#define mDATPeeResetEEP_ECUReference()     \
{                                                     \
   mDATPeeWriteTable(U8Bit,Sbk,SupplierBank,  5 ,  0, 130, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,SupplierBank,  5 ,  1, 1, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,SupplierBank,  5 ,  2, 2, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,SupplierBank,  5 ,  3, 147, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,SupplierBank,  5 ,  4, 145, Delayed) \
}
#define mDATReadTableU1BitEEP_ECUReferenceDefaultValueDefault( Index ) \
      mDATPeeReadDefaultTable(U1Bit,Sbk, SupplierBank,  5 , Index, Delayed)

#define mDATReadTableU8BitEEP_ECUReferenceDefault( Index ) \
      mDATPeeReadTable(U8Bit,Sbk, SupplierBank,  5 , Index, Delayed)
#define mDATWriteTableU8BitEEP_ECUReferenceDelayed( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Sbk, SupplierBank,  5 , Index, (ValueToWrite), Delayed)
#define mDATWriteTableU8BitEEP_ECUReferenceImmediate( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Sbk, SupplierBank,  5 , Index, (ValueToWrite), Immediate)
#define mDATWriteTableU8BitEEP_ECUReferenceDefault( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Sbk, SupplierBank,  5 , Index, (ValueToWrite), Immediate)

// EEP_SerialNumber -- Group SupplierBank, Byte  10  , Bit (MSB)  7  , SizeInBit  24 
#ifdef EEP_SerialNumber
  #error "Do not define EEP_SerialNumber, because this is a lexem used for concatenation."
#endif
#define mDATPeeResetEEP_SerialNumber()     \
{                                                     \
   mDATPeeWriteTable(U8Bit,Sbk,SupplierBank,  10 ,  0, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,SupplierBank,  10 ,  1, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,SupplierBank,  10 ,  2, 0, Delayed) \
}
#define mDATReadTableU1BitEEP_SerialNumberDefaultValueDefault( Index ) \
      mDATPeeReadDefaultTable(U1Bit,Sbk, SupplierBank,  10 , Index, Delayed)

#define mDATReadTableU8BitEEP_SerialNumberDefault( Index ) \
      mDATPeeReadTable(U8Bit,Sbk, SupplierBank,  10 , Index, Delayed)
#define mDATWriteTableU8BitEEP_SerialNumberDelayed( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Sbk, SupplierBank,  10 , Index, (ValueToWrite), Delayed)
#define mDATWriteTableU8BitEEP_SerialNumberImmediate( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Sbk, SupplierBank,  10 , Index, (ValueToWrite), Immediate)
#define mDATWriteTableU8BitEEP_SerialNumberDefault( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Sbk, SupplierBank,  10 , Index, (ValueToWrite), Immediate)

// EEP_PieIndex -- Group SupplierBank, Byte  13  , Bit (MSB)  7  , SizeInBit  16 
#ifdef EEP_PieIndex
  #error "Do not define EEP_PieIndex, because this is a lexem used for concatenation."
#endif
#define mDATPeeResetEEP_PieIndex()     \
{                                                     \
   mDATPeeWriteTable(U8Bit,Sbk,SupplierBank,  13 ,  0, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,SupplierBank,  13 ,  1, 3, Delayed) \
}
#define mDATReadTableU1BitEEP_PieIndexDefaultValueDefault( Index ) \
      mDATPeeReadDefaultTable(U1Bit,Sbk, SupplierBank,  13 , Index, Delayed)

#define mDATReadTableU8BitEEP_PieIndexDefault( Index ) \
      mDATPeeReadTable(U8Bit,Sbk, SupplierBank,  13 , Index, Delayed)
#define mDATWriteTableU8BitEEP_PieIndexDelayed( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Sbk, SupplierBank,  13 , Index, (ValueToWrite), Delayed)
#define mDATWriteTableU8BitEEP_PieIndexImmediate( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Sbk, SupplierBank,  13 , Index, (ValueToWrite), Immediate)
#define mDATWriteTableU8BitEEP_PieIndexDefault( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Sbk, SupplierBank,  13 , Index, (ValueToWrite), Immediate)

// EEP_DateCode -- Group SupplierBank, Byte  15  , Bit (MSB)  7  , SizeInBit  16 
#ifdef EEP_DateCode
  #error "Do not define EEP_DateCode, because this is a lexem used for concatenation."
#endif
#define mDATPeeResetEEP_DateCode()     \
{                                                     \
   mDATPeeWriteTable(U8Bit,Sbk,SupplierBank,  15 ,  0, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,SupplierBank,  15 ,  1, 0, Delayed) \
}
#define mDATReadTableU1BitEEP_DateCodeDefaultValueDefault( Index ) \
      mDATPeeReadDefaultTable(U1Bit,Sbk, SupplierBank,  15 , Index, Delayed)

#define mDATReadTableU8BitEEP_DateCodeDefault( Index ) \
      mDATPeeReadTable(U8Bit,Sbk, SupplierBank,  15 , Index, Delayed)
#define mDATWriteTableU8BitEEP_DateCodeDelayed( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Sbk, SupplierBank,  15 , Index, (ValueToWrite), Delayed)
#define mDATWriteTableU8BitEEP_DateCodeImmediate( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Sbk, SupplierBank,  15 , Index, (ValueToWrite), Immediate)
#define mDATWriteTableU8BitEEP_DateCodeDefault( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Sbk, SupplierBank,  15 , Index, (ValueToWrite), Immediate)

// EEP_InSituTestCounter -- Group SupplierBank, Byte  17  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_InSituTestCounter
  #error "Do not define EEP_InSituTestCounter, because this is a lexem used for concatenation."
#endif
#define cDATEEP_InSituTestCounterPositionByte      17 
#define cDATEEP_InSituTestCounterPositionBit        0xFF
#define mDATPeeResetU8BitEEP_InSituTestCounter()     \
      mDATPeeWriteU8Bit(Sbk, SupplierBank,  17 ,  7 ,  8 , 0, Delayed)
#define mDATReadU8BitEEP_InSituTestCounterDefaultValueDefault() ((U8)0)
#define mDATReadU8BitEEP_InSituTestCounterDefault() \
      mDATPeeReadU8Bit(Sbk, SupplierBank,  17 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_InSituTestCounterDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Sbk, SupplierBank,  17 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_InSituTestCounterImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Sbk, SupplierBank,  17 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_InSituTestCounterDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Sbk, SupplierBank,  17 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_PassingTestCounter -- Group SupplierBank, Byte  18  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_PassingTestCounter
  #error "Do not define EEP_PassingTestCounter, because this is a lexem used for concatenation."
#endif
#define cDATEEP_PassingTestCounterPositionByte      18 
#define cDATEEP_PassingTestCounterPositionBit        0xFF
#define mDATPeeResetU8BitEEP_PassingTestCounter()     \
      mDATPeeWriteU8Bit(Sbk, SupplierBank,  18 ,  7 ,  8 , 0, Delayed)
#define mDATReadU8BitEEP_PassingTestCounterDefaultValueDefault() ((U8)0)
#define mDATReadU8BitEEP_PassingTestCounterDefault() \
      mDATPeeReadU8Bit(Sbk, SupplierBank,  18 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_PassingTestCounterDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Sbk, SupplierBank,  18 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_PassingTestCounterImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Sbk, SupplierBank,  18 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_PassingTestCounterDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Sbk, SupplierBank,  18 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_FinalTestCounter -- Group SupplierBank, Byte  19  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_FinalTestCounter
  #error "Do not define EEP_FinalTestCounter, because this is a lexem used for concatenation."
#endif
#define cDATEEP_FinalTestCounterPositionByte      19 
#define cDATEEP_FinalTestCounterPositionBit        0xFF
#define mDATPeeResetU8BitEEP_FinalTestCounter()     \
      mDATPeeWriteU8Bit(Sbk, SupplierBank,  19 ,  7 ,  8 , 0, Delayed)
#define mDATReadU8BitEEP_FinalTestCounterDefaultValueDefault() ((U8)0)
#define mDATReadU8BitEEP_FinalTestCounterDefault() \
      mDATPeeReadU8Bit(Sbk, SupplierBank,  19 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_FinalTestCounterDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Sbk, SupplierBank,  19 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_FinalTestCounterImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Sbk, SupplierBank,  19 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_FinalTestCounterDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Sbk, SupplierBank,  19 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_RfTestCounter -- Group SupplierBank, Byte  20  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_RfTestCounter
  #error "Do not define EEP_RfTestCounter, because this is a lexem used for concatenation."
#endif
#define cDATEEP_RfTestCounterPositionByte      20 
#define cDATEEP_RfTestCounterPositionBit        0xFF
#define mDATPeeResetU8BitEEP_RfTestCounter()     \
      mDATPeeWriteU8Bit(Sbk, SupplierBank,  20 ,  7 ,  8 , 0, Delayed)
#define mDATReadU8BitEEP_RfTestCounterDefaultValueDefault() ((U8)0)
#define mDATReadU8BitEEP_RfTestCounterDefault() \
      mDATPeeReadU8Bit(Sbk, SupplierBank,  20 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_RfTestCounterDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Sbk, SupplierBank,  20 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_RfTestCounterImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Sbk, SupplierBank,  20 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_RfTestCounterDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Sbk, SupplierBank,  20 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_ReliabilityTestCounter -- Group SupplierBank, Byte  21  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_ReliabilityTestCounter
  #error "Do not define EEP_ReliabilityTestCounter, because this is a lexem used for concatenation."
#endif
#define cDATEEP_ReliabilityTestCounterPositionByte      21 
#define cDATEEP_ReliabilityTestCounterPositionBit        0xFF
#define mDATPeeResetU8BitEEP_ReliabilityTestCounter()     \
      mDATPeeWriteU8Bit(Sbk, SupplierBank,  21 ,  7 ,  8 , 0, Delayed)
#define mDATReadU8BitEEP_ReliabilityTestCounterDefaultValueDefault() ((U8)0)
#define mDATReadU8BitEEP_ReliabilityTestCounterDefault() \
      mDATPeeReadU8Bit(Sbk, SupplierBank,  21 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_ReliabilityTestCounterDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Sbk, SupplierBank,  21 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_ReliabilityTestCounterImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Sbk, SupplierBank,  21 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_ReliabilityTestCounterDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Sbk, SupplierBank,  21 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_ECUType -- Group SupplierBank, Byte  22  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_ECUType
  #error "Do not define EEP_ECUType, because this is a lexem used for concatenation."
#endif
#define cDATEEP_ECUTypePositionByte      22 
#define cDATEEP_ECUTypePositionBit        0xFF
#define mDATPeeResetU8BitEEP_ECUType()     \
      mDATPeeWriteU8Bit(Sbk, SupplierBank,  22 ,  7 ,  8 , 4, Delayed)
#define mDATReadU8BitEEP_ECUTypeDefaultValueDefault() ((U8)4)
#define mDATReadU8BitEEP_ECUTypeDefault() \
      mDATPeeReadU8Bit(Sbk, SupplierBank,  22 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_ECUTypeDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Sbk, SupplierBank,  22 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_ECUTypeImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Sbk, SupplierBank,  22 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_ECUTypeDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Sbk, SupplierBank,  22 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_FlaCoeffLNormal -- Group SupplierBank, Byte  23  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_FlaCoeffLNormal
  #error "Do not define EEP_FlaCoeffLNormal, because this is a lexem used for concatenation."
#endif
#define cDATEEP_FlaCoeffLNormalPositionByte      23 
#define cDATEEP_FlaCoeffLNormalPositionBit        0xFF
#define mDATPeeResetU8BitEEP_FlaCoeffLNormal()     \
      mDATPeeWriteU8Bit(Sbk, SupplierBank,  23 ,  7 ,  8 , 140, Delayed)
#define mDATReadU8BitEEP_FlaCoeffLNormalDefaultValueDefault() ((U8)140)
#define mDATReadU8BitEEP_FlaCoeffLNormalDefault() \
      mDATPeeReadU8Bit(Sbk, SupplierBank,  23 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_FlaCoeffLNormalDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Sbk, SupplierBank,  23 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_FlaCoeffLNormalImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Sbk, SupplierBank,  23 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_FlaCoeffLNormalDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Sbk, SupplierBank,  23 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_FlaCoeffRNormal -- Group SupplierBank, Byte  24  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_FlaCoeffRNormal
  #error "Do not define EEP_FlaCoeffRNormal, because this is a lexem used for concatenation."
#endif
#define cDATEEP_FlaCoeffRNormalPositionByte      24 
#define cDATEEP_FlaCoeffRNormalPositionBit        0xFF
#define mDATPeeResetU8BitEEP_FlaCoeffRNormal()     \
      mDATPeeWriteU8Bit(Sbk, SupplierBank,  24 ,  7 ,  8 , 140, Delayed)
#define mDATReadU8BitEEP_FlaCoeffRNormalDefaultValueDefault() ((U8)140)
#define mDATReadU8BitEEP_FlaCoeffRNormalDefault() \
      mDATPeeReadU8Bit(Sbk, SupplierBank,  24 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_FlaCoeffRNormalDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Sbk, SupplierBank,  24 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_FlaCoeffRNormalImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Sbk, SupplierBank,  24 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_FlaCoeffRNormalDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Sbk, SupplierBank,  24 ,  7 ,  8 , (ValueToWrite), Immediate)

// Spare_SupplierBank -- Group SupplierBank, Byte  25  , Bit (MSB)  7  , SizeInBit  8 
#ifdef Spare_SupplierBank
  #error "Do not define Spare_SupplierBank, because this is a lexem used for concatenation."
#endif
#define cDATSpare_SupplierBankPositionByte      25 
#define cDATSpare_SupplierBankPositionBit        0xFF
#define mDATPeeResetU8BitSpare_SupplierBank()     \
      mDATPeeWriteU8Bit(Sbk, SupplierBank,  25 ,  7 ,  8 , 0, Delayed)
#define mDATReadU8BitSpare_SupplierBankDefaultValueDefault() ((U8)0)
#define mDATReadU8BitSpare_SupplierBankDefault() \
      mDATPeeReadU8Bit(Sbk, SupplierBank,  25 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitSpare_SupplierBankDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Sbk, SupplierBank,  25 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitSpare_SupplierBankImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Sbk, SupplierBank,  25 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitSpare_SupplierBankDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Sbk, SupplierBank,  25 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_VDiag -- Group DiagBank, Byte  0  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_VDiag
  #error "Do not define EEP_VDiag, because this is a lexem used for concatenation."
#endif
#define cDATEEP_VDiagPositionByte      0 
#define cDATEEP_VDiagPositionBit        0xFF
#define mDATPeeResetU8BitEEP_VDiag()     \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  0 ,  7 ,  8 , 14, Delayed)
#define mDATReadU8BitEEP_VDiagDefaultValueDefault() ((U8)14)
#define mDATReadU8BitEEP_VDiagDefault() \
      mDATPeeReadU8Bit(Dbk, DiagBank,  0 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_VDiagDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  0 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_VDiagImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  0 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_VDiagDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  0 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_AuthentDelayedCounter -- Group DiagBank, Byte  1  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_AuthentDelayedCounter
  #error "Do not define EEP_AuthentDelayedCounter, because this is a lexem used for concatenation."
#endif
#define cDATEEP_AuthentDelayedCounterPositionByte      1 
#define cDATEEP_AuthentDelayedCounterPositionBit        0xFF
#define mDATPeeResetU8BitEEP_AuthentDelayedCounter()     \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  1 ,  7 ,  8 , 0, Delayed)
#define mDATReadU8BitEEP_AuthentDelayedCounterDefaultValueDefault() ((U8)0)
#define mDATReadU8BitEEP_AuthentDelayedCounterDefault() \
      mDATPeeReadU8Bit(Dbk, DiagBank,  1 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_AuthentDelayedCounterDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  1 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_AuthentDelayedCounterImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  1 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_AuthentDelayedCounterDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  1 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_AuthentFailureCounter -- Group DiagBank, Byte  2  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_AuthentFailureCounter
  #error "Do not define EEP_AuthentFailureCounter, because this is a lexem used for concatenation."
#endif
#define cDATEEP_AuthentFailureCounterPositionByte      2 
#define cDATEEP_AuthentFailureCounterPositionBit        0xFF
#define mDATPeeResetU8BitEEP_AuthentFailureCounter()     \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  2 ,  7 ,  8 , 0, Delayed)
#define mDATReadU8BitEEP_AuthentFailureCounterDefaultValueDefault() ((U8)0)
#define mDATReadU8BitEEP_AuthentFailureCounterDefault() \
      mDATPeeReadU8Bit(Dbk, DiagBank,  2 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_AuthentFailureCounterDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  2 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_AuthentFailureCounterImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  2 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_AuthentFailureCounterDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  2 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_ResynchroFailureCounter -- Group DiagBank, Byte  3  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_ResynchroFailureCounter
  #error "Do not define EEP_ResynchroFailureCounter, because this is a lexem used for concatenation."
#endif
#define cDATEEP_ResynchroFailureCounterPositionByte      3 
#define cDATEEP_ResynchroFailureCounterPositionBit        0xFF
#define mDATPeeResetU8BitEEP_ResynchroFailureCounter()     \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  3 ,  7 ,  8 , 0, Delayed)
#define mDATReadU8BitEEP_ResynchroFailureCounterDefaultValueDefault() ((U8)0)
#define mDATReadU8BitEEP_ResynchroFailureCounterDefault() \
      mDATPeeReadU8Bit(Dbk, DiagBank,  3 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_ResynchroFailureCounterImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  3 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_ResynchroFailureCounterDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  3 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_ResynchroSuccessfulCounter -- Group DiagBank, Byte  4  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_ResynchroSuccessfulCounter
  #error "Do not define EEP_ResynchroSuccessfulCounter, because this is a lexem used for concatenation."
#endif
#define cDATEEP_ResynchroSuccessfulCounterPositionByte      4 
#define cDATEEP_ResynchroSuccessfulCounterPositionBit        0xFF
#define mDATPeeResetU8BitEEP_ResynchroSuccessfulCounter()     \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  4 ,  7 ,  8 , 0, Delayed)
#define mDATReadU8BitEEP_ResynchroSuccessfulCounterDefaultValueDefault() ((U8)0)
#define mDATReadU8BitEEP_ResynchroSuccessfulCounterDefault() \
      mDATPeeReadU8Bit(Dbk, DiagBank,  4 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_ResynchroSuccessfulCounterImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  4 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_ResynchroSuccessfulCounterDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  4 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_ResetCount -- Group DiagBank, Byte  5  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_ResetCount
  #error "Do not define EEP_ResetCount, because this is a lexem used for concatenation."
#endif
#define cDATEEP_ResetCountPositionByte      5 
#define cDATEEP_ResetCountPositionBit        0xFF
#define mDATPeeResetU8BitEEP_ResetCount()     \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  5 ,  7 ,  8 , 0, Delayed)
#define mDATReadU8BitEEP_ResetCountDefaultValueDefault() ((U8)0)
#define mDATReadU8BitEEP_ResetCountDefault() \
      mDATPeeReadU8Bit(Dbk, DiagBank,  5 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_ResetCountDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  5 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_ResetCountImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  5 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_ResetCountDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  5 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_CrashCount -- Group DiagBank, Byte  6  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_CrashCount
  #error "Do not define EEP_CrashCount, because this is a lexem used for concatenation."
#endif
#define cDATEEP_CrashCountPositionByte      6 
#define cDATEEP_CrashCountPositionBit        0xFF
#define mDATPeeResetU8BitEEP_CrashCount()     \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  6 ,  7 ,  8 , 0, Delayed)
#define mDATReadU8BitEEP_CrashCountDefaultValueDefault() ((U8)0)
#define mDATReadU8BitEEP_CrashCountDefault() \
      mDATPeeReadU8Bit(Dbk, DiagBank,  6 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_CrashCountDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  6 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_CrashCountImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  6 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_CrashCountDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  6 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_CDDoorLockLed -- Group DiagBank, Byte  7  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_CDDoorLockLed
  #error "Do not define EEP_CDDoorLockLed, because this is a lexem used for concatenation."
#endif
#define cDATEEP_CDDoorLockLedPositionByte      7 
#define cDATEEP_CDDoorLockLedPositionBit        0xFF
#define mDATPeeResetU8BitEEP_CDDoorLockLed()     \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  7 ,  7 ,  8 , 0, Delayed)
#define mDATReadU8BitEEP_CDDoorLockLedDefaultValueDefault() ((U8)0)
#define mDATReadU8BitEEP_CDDoorLockLedDefault() \
      mDATPeeReadU8Bit(Dbk, DiagBank,  7 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_CDDoorLockLedDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  7 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_CDDoorLockLedImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  7 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_CDDoorLockLedDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  7 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_CDLeftInd -- Group DiagBank, Byte  8  , Bit (MSB)  7  , SizeInBit  16 
#ifdef EEP_CDLeftInd
  #error "Do not define EEP_CDLeftInd, because this is a lexem used for concatenation."
#endif
#define cDATEEP_CDLeftIndPositionByte      8 
#define cDATEEP_CDLeftIndPositionBit        0xFF
#define mDATPeeResetU16BitEEP_CDLeftInd()     \
      mDATPeeWriteU16Bit(Dbk, DiagBank,  8 ,  7 ,  16 , 0, Delayed)
#define mDATReadU16BitEEP_CDLeftIndDefaultValueDefault() ((U16)0)
#define mDATReadU16BitEEP_CDLeftIndDefault() \
      mDATPeeReadU16Bit(Dbk, DiagBank,  8 ,  7 ,  16 , Delayed)
#define mDATWriteU16BitEEP_CDLeftIndDelayed(ValueToWrite) \
      mDATPeeWriteU16Bit(Dbk, DiagBank,  8 ,  7 ,  16 , (ValueToWrite), Delayed)
#define mDATWriteU16BitEEP_CDLeftIndImmediate(ValueToWrite) \
      mDATPeeWriteU16Bit(Dbk, DiagBank,  8 ,  7 ,  16 , (ValueToWrite), Immediate)
#define mDATWriteU16BitEEP_CDLeftIndDefault(ValueToWrite) \
      mDATPeeWriteU16Bit(Dbk, DiagBank,  8 ,  7 ,  16 , (ValueToWrite), Immediate)

// EEP_CDRightInd -- Group DiagBank, Byte  10  , Bit (MSB)  7  , SizeInBit  16 
#ifdef EEP_CDRightInd
  #error "Do not define EEP_CDRightInd, because this is a lexem used for concatenation."
#endif
#define cDATEEP_CDRightIndPositionByte      10 
#define cDATEEP_CDRightIndPositionBit        0xFF
#define mDATPeeResetU16BitEEP_CDRightInd()     \
      mDATPeeWriteU16Bit(Dbk, DiagBank,  10 ,  7 ,  16 , 0, Delayed)
#define mDATReadU16BitEEP_CDRightIndDefaultValueDefault() ((U16)0)
#define mDATReadU16BitEEP_CDRightIndDefault() \
      mDATPeeReadU16Bit(Dbk, DiagBank,  10 ,  7 ,  16 , Delayed)
#define mDATWriteU16BitEEP_CDRightIndDelayed(ValueToWrite) \
      mDATPeeWriteU16Bit(Dbk, DiagBank,  10 ,  7 ,  16 , (ValueToWrite), Delayed)
#define mDATWriteU16BitEEP_CDRightIndImmediate(ValueToWrite) \
      mDATPeeWriteU16Bit(Dbk, DiagBank,  10 ,  7 ,  16 , (ValueToWrite), Immediate)
#define mDATWriteU16BitEEP_CDRightIndDefault(ValueToWrite) \
      mDATPeeWriteU16Bit(Dbk, DiagBank,  10 ,  7 ,  16 , (ValueToWrite), Immediate)

// EEP_CDRearWiper -- Group DiagBank, Byte  12  , Bit (MSB)  7  , SizeInBit  16 
#ifdef EEP_CDRearWiper
  #error "Do not define EEP_CDRearWiper, because this is a lexem used for concatenation."
#endif
#define cDATEEP_CDRearWiperPositionByte      12 
#define cDATEEP_CDRearWiperPositionBit        0xFF
#define mDATPeeResetU16BitEEP_CDRearWiper()     \
      mDATPeeWriteU16Bit(Dbk, DiagBank,  12 ,  7 ,  16 , 0, Delayed)
#define mDATReadU16BitEEP_CDRearWiperDefaultValueDefault() ((U16)0)
#define mDATReadU16BitEEP_CDRearWiperDefault() \
      mDATPeeReadU16Bit(Dbk, DiagBank,  12 ,  7 ,  16 , Delayed)
#define mDATWriteU16BitEEP_CDRearWiperDelayed(ValueToWrite) \
      mDATPeeWriteU16Bit(Dbk, DiagBank,  12 ,  7 ,  16 , (ValueToWrite), Delayed)
#define mDATWriteU16BitEEP_CDRearWiperImmediate(ValueToWrite) \
      mDATPeeWriteU16Bit(Dbk, DiagBank,  12 ,  7 ,  16 , (ValueToWrite), Immediate)
#define mDATWriteU16BitEEP_CDRearWiperDefault(ValueToWrite) \
      mDATPeeWriteU16Bit(Dbk, DiagBank,  12 ,  7 ,  16 , (ValueToWrite), Immediate)

// EEP_SCLimit -- Group DiagBank, Byte  14  , Bit (MSB)  7  , SizeInBit  16 
#ifdef EEP_SCLimit
  #error "Do not define EEP_SCLimit, because this is a lexem used for concatenation."
#endif
#define cDATEEP_SCLimitPositionByte      14 
#define cDATEEP_SCLimitPositionBit        0xFF
#define mDATPeeResetU16BitEEP_SCLimit()     \
      mDATPeeWriteU16Bit(Dbk, DiagBank,  14 ,  7 ,  16 , 10000, Delayed)
#define mDATReadU16BitEEP_SCLimitDefaultValueDefault() ((U16)10000)
#define mDATReadU16BitEEP_SCLimitDefault() \
      mDATPeeReadU16Bit(Dbk, DiagBank,  14 ,  7 ,  16 , Delayed)
#define mDATWriteU16BitEEP_SCLimitDelayed(ValueToWrite) \
      mDATPeeWriteU16Bit(Dbk, DiagBank,  14 ,  7 ,  16 , (ValueToWrite), Delayed)
#define mDATWriteU16BitEEP_SCLimitImmediate(ValueToWrite) \
      mDATPeeWriteU16Bit(Dbk, DiagBank,  14 ,  7 ,  16 , (ValueToWrite), Immediate)
#define mDATWriteU16BitEEP_SCLimitDefault(ValueToWrite) \
      mDATPeeWriteU16Bit(Dbk, DiagBank,  14 ,  7 ,  16 , (ValueToWrite), Immediate)

// EEP_CDVerlogLed -- Group DiagBank, Byte  16  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_CDVerlogLed
  #error "Do not define EEP_CDVerlogLed, because this is a lexem used for concatenation."
#endif
#define cDATEEP_CDVerlogLedPositionByte      16 
#define cDATEEP_CDVerlogLedPositionBit        0xFF
#define mDATPeeResetU8BitEEP_CDVerlogLed()     \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  16 ,  7 ,  8 , 0, Delayed)
#define mDATReadU8BitEEP_CDVerlogLedDefaultValueDefault() ((U8)0)
#define mDATReadU8BitEEP_CDVerlogLedDefault() \
      mDATPeeReadU8Bit(Dbk, DiagBank,  16 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_CDVerlogLedDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  16 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_CDVerlogLedImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  16 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_CDVerlogLedDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  16 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_CDVerlog -- Group DiagBank, Byte  17  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_CDVerlog
  #error "Do not define EEP_CDVerlog, because this is a lexem used for concatenation."
#endif
#define cDATEEP_CDVerlogPositionByte      17 
#define cDATEEP_CDVerlogPositionBit        0xFF
#define mDATPeeResetU8BitEEP_CDVerlog()     \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  17 ,  7 ,  8 , 0, Delayed)
#define mDATReadU8BitEEP_CDVerlogDefaultValueDefault() ((U8)0)
#define mDATReadU8BitEEP_CDVerlogDefault() \
      mDATPeeReadU8Bit(Dbk, DiagBank,  17 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_CDVerlogDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  17 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_CDVerlogImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  17 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_CDVerlogDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  17 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_CDImmo -- Group DiagBank, Byte  18  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_CDImmo
  #error "Do not define EEP_CDImmo, because this is a lexem used for concatenation."
#endif
#define cDATEEP_CDImmoPositionByte      18 
#define cDATEEP_CDImmoPositionBit        0xFF
#define mDATPeeResetU8BitEEP_CDImmo()     \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  18 ,  7 ,  8 , 0, Delayed)
#define mDATReadU8BitEEP_CDImmoDefaultValueDefault() ((U8)0)
#define mDATReadU8BitEEP_CDImmoDefault() \
      mDATPeeReadU8Bit(Dbk, DiagBank,  18 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_CDImmoDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  18 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_CDImmoImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  18 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_CDImmoDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, DiagBank,  18 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_DefAfav -- Group DiagBank, Byte  19  , Bit (MSB)  0  , SizeInBit  1 
#ifdef EEP_DefAfav
  #error "Do not define EEP_DefAfav, because this is a lexem used for concatenation."
#endif
#define cDATEEP_DefAfavPositionByte      19 
#define cDATEEP_DefAfavPositionBit       0 
#define mDATPeeResetU1BitEEP_DefAfav()     \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  19 ,  0 , 0, Delayed)
#define mDATReadU1BitEEP_DefAfavDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_DefAfavDefault() \
      mDATPeeReadU1Bit(Dbk, DiagBank,  19 ,  0 , Delayed)
#define mDATWriteU1BitEEP_DefAfavDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  19 ,  0  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_DefAfavImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  19 ,  0  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_DefAfavDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  19 ,  0  , (ValueToWrite), Immediate)

// EEP_DefAfar -- Group DiagBank, Byte  19  , Bit (MSB)  1  , SizeInBit  1 
#ifdef EEP_DefAfar
  #error "Do not define EEP_DefAfar, because this is a lexem used for concatenation."
#endif
#define cDATEEP_DefAfarPositionByte      19 
#define cDATEEP_DefAfarPositionBit       1 
#define mDATPeeResetU1BitEEP_DefAfar()     \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  19 ,  1 , 0, Delayed)
#define mDATReadU1BitEEP_DefAfarDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_DefAfarDefault() \
      mDATPeeReadU1Bit(Dbk, DiagBank,  19 ,  1 , Delayed)
#define mDATWriteU1BitEEP_DefAfarDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  19 ,  1  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_DefAfarImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  19 ,  1  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_DefAfarDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  19 ,  1  , (ValueToWrite), Immediate)

// EEP_DefAirbag -- Group DiagBank, Byte  19  , Bit (MSB)  2  , SizeInBit  1 
#ifdef EEP_DefAirbag
  #error "Do not define EEP_DefAirbag, because this is a lexem used for concatenation."
#endif
#define cDATEEP_DefAirbagPositionByte      19 
#define cDATEEP_DefAirbagPositionBit       2 
#define mDATPeeResetU1BitEEP_DefAirbag()     \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  19 ,  2 , 0, Delayed)
#define mDATReadU1BitEEP_DefAirbagDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_DefAirbagDefault() \
      mDATPeeReadU1Bit(Dbk, DiagBank,  19 ,  2 , Delayed)
#define mDATWriteU1BitEEP_DefAirbagDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  19 ,  2  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_DefAirbagImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  19 ,  2  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_DefAirbagDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  19 ,  2  , (ValueToWrite), Immediate)

// EEP_DefClignL -- Group DiagBank, Byte  19  , Bit (MSB)  3  , SizeInBit  1 
#ifdef EEP_DefClignL
  #error "Do not define EEP_DefClignL, because this is a lexem used for concatenation."
#endif
#define cDATEEP_DefClignLPositionByte      19 
#define cDATEEP_DefClignLPositionBit       3 
#define mDATPeeResetU1BitEEP_DefClignL()     \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  19 ,  3 , 0, Delayed)
#define mDATReadU1BitEEP_DefClignLDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_DefClignLDefault() \
      mDATPeeReadU1Bit(Dbk, DiagBank,  19 ,  3 , Delayed)
#define mDATWriteU1BitEEP_DefClignLDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  19 ,  3  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_DefClignLImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  19 ,  3  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_DefClignLDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  19 ,  3  , (ValueToWrite), Immediate)

// EEP_DefClignR -- Group DiagBank, Byte  19  , Bit (MSB)  4  , SizeInBit  1 
#ifdef EEP_DefClignR
  #error "Do not define EEP_DefClignR, because this is a lexem used for concatenation."
#endif
#define cDATEEP_DefClignRPositionByte      19 
#define cDATEEP_DefClignRPositionBit       4 
#define mDATPeeResetU1BitEEP_DefClignR()     \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  19 ,  4 , 0, Delayed)
#define mDATReadU1BitEEP_DefClignRDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_DefClignRDefault() \
      mDATPeeReadU1Bit(Dbk, DiagBank,  19 ,  4 , Delayed)
#define mDATWriteU1BitEEP_DefClignRDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  19 ,  4  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_DefClignRImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  19 ,  4  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_DefClignRDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  19 ,  4  , (ValueToWrite), Immediate)

// EEP_DefEeprom -- Group DiagBank, Byte  19  , Bit (MSB)  5  , SizeInBit  1 
#ifdef EEP_DefEeprom
  #error "Do not define EEP_DefEeprom, because this is a lexem used for concatenation."
#endif
#define cDATEEP_DefEepromPositionByte      19 
#define cDATEEP_DefEepromPositionBit       5 
#define mDATPeeResetU1BitEEP_DefEeprom()     \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  19 ,  5 , 0, Delayed)
#define mDATReadU1BitEEP_DefEepromDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_DefEepromDefault() \
      mDATPeeReadU1Bit(Dbk, DiagBank,  19 ,  5 , Delayed)
#define mDATWriteU1BitEEP_DefEepromDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  19 ,  5  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_DefEepromImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  19 ,  5  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_DefEepromDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  19 ,  5  , (ValueToWrite), Immediate)

// EEP_DefTrpToBat -- Group DiagBank, Byte  19  , Bit (MSB)  6  , SizeInBit  1 
#ifdef EEP_DefTrpToBat
  #error "Do not define EEP_DefTrpToBat, because this is a lexem used for concatenation."
#endif
#define cDATEEP_DefTrpToBatPositionByte      19 
#define cDATEEP_DefTrpToBatPositionBit       6 
#define mDATPeeResetU1BitEEP_DefTrpToBat()     \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  19 ,  6 , 0, Delayed)
#define mDATReadU1BitEEP_DefTrpToBatDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_DefTrpToBatDefault() \
      mDATPeeReadU1Bit(Dbk, DiagBank,  19 ,  6 , Delayed)
#define mDATWriteU1BitEEP_DefTrpToBatDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  19 ,  6  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_DefTrpToBatImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  19 ,  6  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_DefTrpToBatDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  19 ,  6  , (ValueToWrite), Immediate)

// EEP_DefTrpToGnd -- Group DiagBank, Byte  19  , Bit (MSB)  7  , SizeInBit  1 
#ifdef EEP_DefTrpToGnd
  #error "Do not define EEP_DefTrpToGnd, because this is a lexem used for concatenation."
#endif
#define cDATEEP_DefTrpToGndPositionByte      19 
#define cDATEEP_DefTrpToGndPositionBit       7 
#define mDATPeeResetU1BitEEP_DefTrpToGnd()     \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  19 ,  7 , 0, Delayed)
#define mDATReadU1BitEEP_DefTrpToGndDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_DefTrpToGndDefault() \
      mDATPeeReadU1Bit(Dbk, DiagBank,  19 ,  7 , Delayed)
#define mDATWriteU1BitEEP_DefTrpToGndDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  19 ,  7  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_DefTrpToGndImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  19 ,  7  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_DefTrpToGndDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  19 ,  7  , (ValueToWrite), Immediate)

// EEP_DefVerlogToGnd -- Group DiagBank, Byte  20  , Bit (MSB)  0  , SizeInBit  1 
#ifdef EEP_DefVerlogToGnd
  #error "Do not define EEP_DefVerlogToGnd, because this is a lexem used for concatenation."
#endif
#define cDATEEP_DefVerlogToGndPositionByte      20 
#define cDATEEP_DefVerlogToGndPositionBit       0 
#define mDATPeeResetU1BitEEP_DefVerlogToGnd()     \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  20 ,  0 , 0, Delayed)
#define mDATReadU1BitEEP_DefVerlogToGndDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_DefVerlogToGndDefault() \
      mDATPeeReadU1Bit(Dbk, DiagBank,  20 ,  0 , Delayed)
#define mDATWriteU1BitEEP_DefVerlogToGndDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  20 ,  0  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_DefVerlogToGndImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  20 ,  0  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_DefVerlogToGndDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  20 ,  0  , (ValueToWrite), Immediate)

// EEP_DefVerlogToBat -- Group DiagBank, Byte  20  , Bit (MSB)  1  , SizeInBit  1 
#ifdef EEP_DefVerlogToBat
  #error "Do not define EEP_DefVerlogToBat, because this is a lexem used for concatenation."
#endif
#define cDATEEP_DefVerlogToBatPositionByte      20 
#define cDATEEP_DefVerlogToBatPositionBit       1 
#define mDATPeeResetU1BitEEP_DefVerlogToBat()     \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  20 ,  1 , 0, Delayed)
#define mDATReadU1BitEEP_DefVerlogToBatDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_DefVerlogToBatDefault() \
      mDATPeeReadU1Bit(Dbk, DiagBank,  20 ,  1 , Delayed)
#define mDATWriteU1BitEEP_DefVerlogToBatDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  20 ,  1  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_DefVerlogToBatImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  20 ,  1  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_DefVerlogToBatDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  20 ,  1  , (ValueToWrite), Immediate)

// EEP_DefKLineCC -- Group DiagBank, Byte  20  , Bit (MSB)  2  , SizeInBit  1 
#ifdef EEP_DefKLineCC
  #error "Do not define EEP_DefKLineCC, because this is a lexem used for concatenation."
#endif
#define cDATEEP_DefKLineCCPositionByte      20 
#define cDATEEP_DefKLineCCPositionBit       2 
#define mDATPeeResetU1BitEEP_DefKLineCC()     \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  20 ,  2 , 0, Delayed)
#define mDATReadU1BitEEP_DefKLineCCDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_DefKLineCCDefault() \
      mDATPeeReadU1Bit(Dbk, DiagBank,  20 ,  2 , Delayed)
#define mDATWriteU1BitEEP_DefKLineCCDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  20 ,  2  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_DefKLineCCImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  20 ,  2  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_DefKLineCCDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  20 ,  2  , (ValueToWrite), Immediate)

// EEP_DefDfrToBat -- Group DiagBank, Byte  20  , Bit (MSB)  3  , SizeInBit  1 
#ifdef EEP_DefDfrToBat
  #error "Do not define EEP_DefDfrToBat, because this is a lexem used for concatenation."
#endif
#define cDATEEP_DefDfrToBatPositionByte      20 
#define cDATEEP_DefDfrToBatPositionBit       3 
#define mDATPeeResetU1BitEEP_DefDfrToBat()     \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  20 ,  3 , 0, Delayed)
#define mDATReadU1BitEEP_DefDfrToBatDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_DefDfrToBatDefault() \
      mDATPeeReadU1Bit(Dbk, DiagBank,  20 ,  3 , Delayed)
#define mDATWriteU1BitEEP_DefDfrToBatDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  20 ,  3  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_DefDfrToBatImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  20 ,  3  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_DefDfrToBatDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  20 ,  3  , (ValueToWrite), Immediate)

// EEP_DefDfrToGnd -- Group DiagBank, Byte  20  , Bit (MSB)  4  , SizeInBit  1 
#ifdef EEP_DefDfrToGnd
  #error "Do not define EEP_DefDfrToGnd, because this is a lexem used for concatenation."
#endif
#define cDATEEP_DefDfrToGndPositionByte      20 
#define cDATEEP_DefDfrToGndPositionBit       4 
#define mDATPeeResetU1BitEEP_DefDfrToGnd()     \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  20 ,  4 , 0, Delayed)
#define mDATReadU1BitEEP_DefDfrToGndDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_DefDfrToGndDefault() \
      mDATPeeReadU1Bit(Dbk, DiagBank,  20 ,  4 , Delayed)
#define mDATWriteU1BitEEP_DefDfrToGndDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  20 ,  4  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_DefDfrToGndImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  20 ,  4  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_DefDfrToGndDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  20 ,  4  , (ValueToWrite), Immediate)

// EEP_DefHornCCBat -- Group DiagBank, Byte  20  , Bit (MSB)  5  , SizeInBit  1 
#ifdef EEP_DefHornCCBat
  #error "Do not define EEP_DefHornCCBat, because this is a lexem used for concatenation."
#endif
#define cDATEEP_DefHornCCBatPositionByte      20 
#define cDATEEP_DefHornCCBatPositionBit       5 
#define mDATPeeResetU1BitEEP_DefHornCCBat()     \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  20 ,  5 , 0, Delayed)
#define mDATReadU1BitEEP_DefHornCCBatDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_DefHornCCBatDefault() \
      mDATPeeReadU1Bit(Dbk, DiagBank,  20 ,  5 , Delayed)
#define mDATWriteU1BitEEP_DefHornCCBatDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  20 ,  5  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_DefHornCCBatImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  20 ,  5  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_DefHornCCBatDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  20 ,  5  , (ValueToWrite), Immediate)

// EEP_DefHornCCGnd -- Group DiagBank, Byte  20  , Bit (MSB)  6  , SizeInBit  1 
#ifdef EEP_DefHornCCGnd
  #error "Do not define EEP_DefHornCCGnd, because this is a lexem used for concatenation."
#endif
#define cDATEEP_DefHornCCGndPositionByte      20 
#define cDATEEP_DefHornCCGndPositionBit       6 
#define mDATPeeResetU1BitEEP_DefHornCCGnd()     \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  20 ,  6 , 0, Delayed)
#define mDATReadU1BitEEP_DefHornCCGndDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_DefHornCCGndDefault() \
      mDATPeeReadU1Bit(Dbk, DiagBank,  20 ,  6 , Delayed)
#define mDATWriteU1BitEEP_DefHornCCGndDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  20 ,  6  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_DefHornCCGndImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  20 ,  6  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_DefHornCCGndDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  20 ,  6  , (ValueToWrite), Immediate)

// EEP_DefDoorlockLedCC -- Group DiagBank, Byte  20  , Bit (MSB)  7  , SizeInBit  1 
#ifdef EEP_DefDoorlockLedCC
  #error "Do not define EEP_DefDoorlockLedCC, because this is a lexem used for concatenation."
#endif
#define cDATEEP_DefDoorlockLedCCPositionByte      20 
#define cDATEEP_DefDoorlockLedCCPositionBit       7 
#define mDATPeeResetU1BitEEP_DefDoorlockLedCC()     \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  20 ,  7 , 0, Delayed)
#define mDATReadU1BitEEP_DefDoorlockLedCCDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_DefDoorlockLedCCDefault() \
      mDATPeeReadU1Bit(Dbk, DiagBank,  20 ,  7 , Delayed)
#define mDATWriteU1BitEEP_DefDoorlockLedCCDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  20 ,  7  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_DefDoorlockLedCCImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  20 ,  7  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_DefDoorlockLedCCDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  20 ,  7  , (ValueToWrite), Immediate)

// EEP_DefVerlogLedCC -- Group DiagBank, Byte  21  , Bit (MSB)  0  , SizeInBit  1 
#ifdef EEP_DefVerlogLedCC
  #error "Do not define EEP_DefVerlogLedCC, because this is a lexem used for concatenation."
#endif
#define cDATEEP_DefVerlogLedCCPositionByte      21 
#define cDATEEP_DefVerlogLedCCPositionBit       0 
#define mDATPeeResetU1BitEEP_DefVerlogLedCC()     \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  21 ,  0 , 0, Delayed)
#define mDATReadU1BitEEP_DefVerlogLedCCDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_DefVerlogLedCCDefault() \
      mDATPeeReadU1Bit(Dbk, DiagBank,  21 ,  0 , Delayed)
#define mDATWriteU1BitEEP_DefVerlogLedCCDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  21 ,  0  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_DefVerlogLedCCImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  21 ,  0  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_DefVerlogLedCCDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  21 ,  0  , (ValueToWrite), Immediate)

// EEP_DefRrwCC -- Group DiagBank, Byte  21  , Bit (MSB)  1  , SizeInBit  1 
#ifdef EEP_DefRrwCC
  #error "Do not define EEP_DefRrwCC, because this is a lexem used for concatenation."
#endif
#define cDATEEP_DefRrwCCPositionByte      21 
#define cDATEEP_DefRrwCCPositionBit       1 
#define mDATPeeResetU1BitEEP_DefRrwCC()     \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  21 ,  1 , 0, Delayed)
#define mDATReadU1BitEEP_DefRrwCCDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_DefRrwCCDefault() \
      mDATPeeReadU1Bit(Dbk, DiagBank,  21 ,  1 , Delayed)
#define mDATWriteU1BitEEP_DefRrwCCDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  21 ,  1  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_DefRrwCCImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  21 ,  1  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_DefRrwCCDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, DiagBank,  21 ,  1  , (ValueToWrite), Immediate)

// Spare_DiagBank -- Group DiagBank, Byte  22  , Bit (MSB)  7  , SizeInBit  16 
#ifdef Spare_DiagBank
  #error "Do not define Spare_DiagBank, because this is a lexem used for concatenation."
#endif
#define cDATSpare_DiagBankPositionByte      22 
#define cDATSpare_DiagBankPositionBit        0xFF
#define mDATPeeResetU16BitSpare_DiagBank()     \
      mDATPeeWriteU16Bit(Dbk, DiagBank,  22 ,  7 ,  16 , 0, Delayed)
#define mDATReadU16BitSpare_DiagBankDefaultValueDefault() ((U16)0)
#define mDATReadU16BitSpare_DiagBankDefault() \
      mDATPeeReadU16Bit(Dbk, DiagBank,  22 ,  7 ,  16 , Delayed)
#define mDATWriteU16BitSpare_DiagBankDelayed(ValueToWrite) \
      mDATPeeWriteU16Bit(Dbk, DiagBank,  22 ,  7 ,  16 , (ValueToWrite), Delayed)
#define mDATWriteU16BitSpare_DiagBankImmediate(ValueToWrite) \
      mDATPeeWriteU16Bit(Dbk, DiagBank,  22 ,  7 ,  16 , (ValueToWrite), Immediate)
#define mDATWriteU16BitSpare_DiagBankDefault(ValueToWrite) \
      mDATPeeWriteU16Bit(Dbk, DiagBank,  22 ,  7 ,  16 , (ValueToWrite), Immediate)

// EEP_VersionEEPROM -- Group VersionBank, Byte  0  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_VersionEEPROM
  #error "Do not define EEP_VersionEEPROM, because this is a lexem used for concatenation."
#endif
#define cDATEEP_VersionEEPROMPositionByte      0 
#define cDATEEP_VersionEEPROMPositionBit        0xFF
#define mDATPeeResetU8BitEEP_VersionEEPROM()     \
      mDATPeeWriteU8Bit(Sbk, VersionBank,  0 ,  7 ,  8 , 2, Delayed)
#define mDATReadU8BitEEP_VersionEEPROMDefaultValueDefault() ((U8)2)
#define mDATReadU8BitEEP_VersionEEPROMDefault() \
      mDATPeeReadU8Bit(Sbk, VersionBank,  0 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_VersionEEPROMDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Sbk, VersionBank,  0 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_VersionEEPROMImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Sbk, VersionBank,  0 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_VersionEEPROMDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Sbk, VersionBank,  0 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_RevisionEEPROM -- Group VersionBank, Byte  1  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_RevisionEEPROM
  #error "Do not define EEP_RevisionEEPROM, because this is a lexem used for concatenation."
#endif
#define cDATEEP_RevisionEEPROMPositionByte      1 
#define cDATEEP_RevisionEEPROMPositionBit        0xFF
#define mDATPeeResetU8BitEEP_RevisionEEPROM()     \
      mDATPeeWriteU8Bit(Sbk, VersionBank,  1 ,  7 ,  8 , 5, Delayed)
#define mDATReadU8BitEEP_RevisionEEPROMDefaultValueDefault() ((U8)5)
#define mDATReadU8BitEEP_RevisionEEPROMDefault() \
      mDATPeeReadU8Bit(Sbk, VersionBank,  1 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_RevisionEEPROMDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Sbk, VersionBank,  1 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_RevisionEEPROMImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Sbk, VersionBank,  1 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_RevisionEEPROMDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Sbk, VersionBank,  1 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_DEM_SURVIT -- Group GeneralParameterBank, Byte  0  , Bit (MSB)  0  , SizeInBit  1 
#ifdef EEP_DEM_SURVIT
  #error "Do not define EEP_DEM_SURVIT, because this is a lexem used for concatenation."
#endif
#define cDATEEP_DEM_SURVITPositionByte      0 
#define cDATEEP_DEM_SURVITPositionBit       0 
#define mDATPeeResetU1BitEEP_DEM_SURVIT()     \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  0 ,  0 , 0, Delayed)
#define mDATReadU1BitEEP_DEM_SURVITDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_DEM_SURVITDefault() \
      mDATPeeReadU1Bit(Dbk, GeneralParameterBank,  0 ,  0 , Delayed)
#define mDATWriteU1BitEEP_DEM_SURVITDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  0 ,  0  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_DEM_SURVITImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  0 ,  0  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_DEM_SURVITDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  0 ,  0  , (ValueToWrite), Immediate)

// EEP_CALALPRI -- Group GeneralParameterBank, Byte  0  , Bit (MSB)  1  , SizeInBit  1 
#ifdef EEP_CALALPRI
  #error "Do not define EEP_CALALPRI, because this is a lexem used for concatenation."
#endif
#define cDATEEP_CALALPRIPositionByte      0 
#define cDATEEP_CALALPRIPositionBit       1 
#define mDATPeeResetU1BitEEP_CALALPRI()     \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  0 ,  1 , 0, Delayed)
#define mDATReadU1BitEEP_CALALPRIDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_CALALPRIDefault() \
      mDATPeeReadU1Bit(Dbk, GeneralParameterBank,  0 ,  1 , Delayed)
#define mDATWriteU1BitEEP_CALALPRIDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  0 ,  1  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_CALALPRIImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  0 ,  1  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_CALALPRIDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  0 ,  1  , (ValueToWrite), Immediate)

// EEP_CrashHazardIsRequested -- Group GeneralParameterBank, Byte  0  , Bit (MSB)  2  , SizeInBit  1 
#ifdef EEP_CrashHazardIsRequested
  #error "Do not define EEP_CrashHazardIsRequested, because this is a lexem used for concatenation."
#endif
#define cDATEEP_CrashHazardIsRequestedPositionByte      0 
#define cDATEEP_CrashHazardIsRequestedPositionBit       2 
#define mDATPeeResetU1BitEEP_CrashHazardIsRequested()     \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  0 ,  2 , 0, Delayed)
#define mDATReadU1BitEEP_CrashHazardIsRequestedDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_CrashHazardIsRequestedDefault() \
      mDATPeeReadU1Bit(Dbk, GeneralParameterBank,  0 ,  2 , Delayed)
#define mDATWriteU1BitEEP_CrashHazardIsRequestedDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  0 ,  2  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_CrashHazardIsRequestedImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  0 ,  2  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_CrashHazardIsRequestedDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  0 ,  2  , (ValueToWrite), Immediate)

// EEP_AUTDEGIVRAGE -- Group GeneralParameterBank, Byte  0  , Bit (MSB)  3  , SizeInBit  1 
#ifdef EEP_AUTDEGIVRAGE
  #error "Do not define EEP_AUTDEGIVRAGE, because this is a lexem used for concatenation."
#endif
#define cDATEEP_AUTDEGIVRAGEPositionByte      0 
#define cDATEEP_AUTDEGIVRAGEPositionBit       3 
#define mDATPeeResetU1BitEEP_AUTDEGIVRAGE()     \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  0 ,  3 , 0, Delayed)
#define mDATReadU1BitEEP_AUTDEGIVRAGEDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_AUTDEGIVRAGEDefault() \
      mDATPeeReadU1Bit(Dbk, GeneralParameterBank,  0 ,  3 , Delayed)
#define mDATWriteU1BitEEP_AUTDEGIVRAGEDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  0 ,  3  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_AUTDEGIVRAGEImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  0 ,  3  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_AUTDEGIVRAGEDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  0 ,  3  , (ValueToWrite), Immediate)

// EEP_RELAIS_DEM -- Group GeneralParameterBank, Byte  0  , Bit (MSB)  4  , SizeInBit  1 
#ifdef EEP_RELAIS_DEM
  #error "Do not define EEP_RELAIS_DEM, because this is a lexem used for concatenation."
#endif
#define cDATEEP_RELAIS_DEMPositionByte      0 
#define cDATEEP_RELAIS_DEMPositionBit       4 
#define mDATPeeResetU1BitEEP_RELAIS_DEM()     \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  0 ,  4 , 0, Delayed)
#define mDATReadU1BitEEP_RELAIS_DEMDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_RELAIS_DEMDefault() \
      mDATPeeReadU1Bit(Dbk, GeneralParameterBank,  0 ,  4 , Delayed)
#define mDATWriteU1BitEEP_RELAIS_DEMDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  0 ,  4  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_RELAIS_DEMImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  0 ,  4  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_RELAIS_DEMDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  0 ,  4  , (ValueToWrite), Immediate)

// EEP_RESERVED1 -- Group GeneralParameterBank, Byte  0  , Bit (MSB)  5  , SizeInBit  1 
#ifdef EEP_RESERVED1
  #error "Do not define EEP_RESERVED1, because this is a lexem used for concatenation."
#endif
#define cDATEEP_RESERVED1PositionByte      0 
#define cDATEEP_RESERVED1PositionBit       5 
#define mDATPeeResetU1BitEEP_RESERVED1()     \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  0 ,  5 , 0, Delayed)
#define mDATReadU1BitEEP_RESERVED1DefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_RESERVED1Default() \
      mDATPeeReadU1Bit(Dbk, GeneralParameterBank,  0 ,  5 , Delayed)
#define mDATWriteU1BitEEP_RESERVED1Delayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  0 ,  5  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_RESERVED1Immediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  0 ,  5  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_RESERVED1Default(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  0 ,  5  , (ValueToWrite), Immediate)

// EEP_DETCHOC -- Group GeneralParameterBank, Byte  0  , Bit (MSB)  6  , SizeInBit  1 
#ifdef EEP_DETCHOC
  #error "Do not define EEP_DETCHOC, because this is a lexem used for concatenation."
#endif
#define cDATEEP_DETCHOCPositionByte      0 
#define cDATEEP_DETCHOCPositionBit       6 
#define mDATPeeResetU1BitEEP_DETCHOC()     \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  0 ,  6 , 0, Delayed)
#define mDATReadU1BitEEP_DETCHOCDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_DETCHOCDefault() \
      mDATPeeReadU1Bit(Dbk, GeneralParameterBank,  0 ,  6 , Delayed)
#define mDATWriteU1BitEEP_DETCHOCDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  0 ,  6  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_DETCHOCImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  0 ,  6  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_DETCHOCDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  0 ,  6  , (ValueToWrite), Immediate)

// EEP_RESERVED2 -- Group GeneralParameterBank, Byte  0  , Bit (MSB)  7  , SizeInBit  1 
#ifdef EEP_RESERVED2
  #error "Do not define EEP_RESERVED2, because this is a lexem used for concatenation."
#endif
#define cDATEEP_RESERVED2PositionByte      0 
#define cDATEEP_RESERVED2PositionBit       7 
#define mDATPeeResetU1BitEEP_RESERVED2()     \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  0 ,  7 , 0, Delayed)
#define mDATReadU1BitEEP_RESERVED2DefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_RESERVED2Default() \
      mDATPeeReadU1Bit(Dbk, GeneralParameterBank,  0 ,  7 , Delayed)
#define mDATWriteU1BitEEP_RESERVED2Delayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  0 ,  7  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_RESERVED2Immediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  0 ,  7  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_RESERVED2Default(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  0 ,  7  , (ValueToWrite), Immediate)

// EEP_CONDATMPO -- Group GeneralParameterBank, Byte  1  , Bit (MSB)  0  , SizeInBit  1 
#ifdef EEP_CONDATMPO
  #error "Do not define EEP_CONDATMPO, because this is a lexem used for concatenation."
#endif
#define cDATEEP_CONDATMPOPositionByte      1 
#define cDATEEP_CONDATMPOPositionBit       0 
#define mDATPeeResetU1BitEEP_CONDATMPO()     \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  1 ,  0 , 0, Delayed)
#define mDATReadU1BitEEP_CONDATMPODefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_CONDATMPODefault() \
      mDATPeeReadU1Bit(Dbk, GeneralParameterBank,  1 ,  0 , Delayed)
#define mDATWriteU1BitEEP_CONDATMPODelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  1 ,  0  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_CONDATMPOImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  1 ,  0  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_CONDATMPODefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  1 ,  0  , (ValueToWrite), Immediate)

// EEP_RESERVED3 -- Group GeneralParameterBank, Byte  1  , Bit (MSB)  1  , SizeInBit  1 
#ifdef EEP_RESERVED3
  #error "Do not define EEP_RESERVED3, because this is a lexem used for concatenation."
#endif
#define cDATEEP_RESERVED3PositionByte      1 
#define cDATEEP_RESERVED3PositionBit       1 
#define mDATPeeResetU1BitEEP_RESERVED3()     \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  1 ,  1 , 0, Delayed)
#define mDATReadU1BitEEP_RESERVED3DefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_RESERVED3Default() \
      mDATPeeReadU1Bit(Dbk, GeneralParameterBank,  1 ,  1 , Delayed)
#define mDATWriteU1BitEEP_RESERVED3Delayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  1 ,  1  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_RESERVED3Immediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  1 ,  1  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_RESERVED3Default(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  1 ,  1  , (ValueToWrite), Immediate)

// EEP_CONDAROU -- Group GeneralParameterBank, Byte  1  , Bit (MSB)  2  , SizeInBit  1 
#ifdef EEP_CONDAROU
  #error "Do not define EEP_CONDAROU, because this is a lexem used for concatenation."
#endif
#define cDATEEP_CONDAROUPositionByte      1 
#define cDATEEP_CONDAROUPositionBit       2 
#define mDATPeeResetU1BitEEP_CONDAROU()     \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  1 ,  2 , 0, Delayed)
#define mDATReadU1BitEEP_CONDAROUDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_CONDAROUDefault() \
      mDATPeeReadU1Bit(Dbk, GeneralParameterBank,  1 ,  2 , Delayed)
#define mDATWriteU1BitEEP_CONDAROUDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  1 ,  2  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_CONDAROUImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  1 ,  2  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_CONDAROUDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  1 ,  2  , (ValueToWrite), Immediate)

// EEP_CARCLIENT -- Group GeneralParameterBank, Byte  1  , Bit (MSB)  3  , SizeInBit  1 
#ifdef EEP_CARCLIENT
  #error "Do not define EEP_CARCLIENT, because this is a lexem used for concatenation."
#endif
#define cDATEEP_CARCLIENTPositionByte      1 
#define cDATEEP_CARCLIENTPositionBit       3 
#define mDATPeeResetU1BitEEP_CARCLIENT()     \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  1 ,  3 , 0, Delayed)
#define mDATReadU1BitEEP_CARCLIENTDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_CARCLIENTDefault() \
      mDATPeeReadU1Bit(Dbk, GeneralParameterBank,  1 ,  3 , Delayed)
#define mDATWriteU1BitEEP_CARCLIENTDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  1 ,  3  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_CARCLIENTImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  1 ,  3  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_CARCLIENTDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  1 ,  3  , (ValueToWrite), Immediate)

// EEP_RESERVED4 -- Group GeneralParameterBank, Byte  1  , Bit (MSB)  4  , SizeInBit  1 
#ifdef EEP_RESERVED4
  #error "Do not define EEP_RESERVED4, because this is a lexem used for concatenation."
#endif
#define cDATEEP_RESERVED4PositionByte      1 
#define cDATEEP_RESERVED4PositionBit       4 
#define mDATPeeResetU1BitEEP_RESERVED4()     \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  1 ,  4 , 0, Delayed)
#define mDATReadU1BitEEP_RESERVED4DefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_RESERVED4Default() \
      mDATPeeReadU1Bit(Dbk, GeneralParameterBank,  1 ,  4 , Delayed)
#define mDATWriteU1BitEEP_RESERVED4Delayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  1 ,  4  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_RESERVED4Immediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  1 ,  4  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_RESERVED4Default(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  1 ,  4  , (ValueToWrite), Immediate)

// EEP_ALIM_PLAF -- Group GeneralParameterBank, Byte  1  , Bit (MSB)  5  , SizeInBit  1 
#ifdef EEP_ALIM_PLAF
  #error "Do not define EEP_ALIM_PLAF, because this is a lexem used for concatenation."
#endif
#define cDATEEP_ALIM_PLAFPositionByte      1 
#define cDATEEP_ALIM_PLAFPositionBit       5 
#define mDATPeeResetU1BitEEP_ALIM_PLAF()     \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  1 ,  5 , 0, Delayed)
#define mDATReadU1BitEEP_ALIM_PLAFDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_ALIM_PLAFDefault() \
      mDATPeeReadU1Bit(Dbk, GeneralParameterBank,  1 ,  5 , Delayed)
#define mDATWriteU1BitEEP_ALIM_PLAFDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  1 ,  5  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_ALIM_PLAFImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  1 ,  5  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_ALIM_PLAFDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  1 ,  5  , (ValueToWrite), Immediate)

// EEP_PIL_PLAF -- Group GeneralParameterBank, Byte  1  , Bit (MSB)  6  , SizeInBit  1 
#ifdef EEP_PIL_PLAF
  #error "Do not define EEP_PIL_PLAF, because this is a lexem used for concatenation."
#endif
#define cDATEEP_PIL_PLAFPositionByte      1 
#define cDATEEP_PIL_PLAFPositionBit       6 
#define mDATPeeResetU1BitEEP_PIL_PLAF()     \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  1 ,  6 , 0, Delayed)
#define mDATReadU1BitEEP_PIL_PLAFDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_PIL_PLAFDefault() \
      mDATPeeReadU1Bit(Dbk, GeneralParameterBank,  1 ,  6 , Delayed)
#define mDATWriteU1BitEEP_PIL_PLAFDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  1 ,  6  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_PIL_PLAFImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  1 ,  6  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_PIL_PLAFDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  1 ,  6  , (ValueToWrite), Immediate)

// EEP_RESERVED5 -- Group GeneralParameterBank, Byte  1  , Bit (MSB)  7  , SizeInBit  1 
#ifdef EEP_RESERVED5
  #error "Do not define EEP_RESERVED5, because this is a lexem used for concatenation."
#endif
#define cDATEEP_RESERVED5PositionByte      1 
#define cDATEEP_RESERVED5PositionBit       7 
#define mDATPeeResetU1BitEEP_RESERVED5()     \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  1 ,  7 , 0, Delayed)
#define mDATReadU1BitEEP_RESERVED5DefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_RESERVED5Default() \
      mDATPeeReadU1Bit(Dbk, GeneralParameterBank,  1 ,  7 , Delayed)
#define mDATWriteU1BitEEP_RESERVED5Delayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  1 ,  7  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_RESERVED5Immediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  1 ,  7  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_RESERVED5Default(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  1 ,  7  , (ValueToWrite), Immediate)

// EEP_RESERVED6 -- Group GeneralParameterBank, Byte  2  , Bit (MSB)  0  , SizeInBit  1 
#ifdef EEP_RESERVED6
  #error "Do not define EEP_RESERVED6, because this is a lexem used for concatenation."
#endif
#define cDATEEP_RESERVED6PositionByte      2 
#define cDATEEP_RESERVED6PositionBit       0 
#define mDATPeeResetU1BitEEP_RESERVED6()     \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  2 ,  0 , 0, Delayed)
#define mDATReadU1BitEEP_RESERVED6DefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_RESERVED6Default() \
      mDATPeeReadU1Bit(Dbk, GeneralParameterBank,  2 ,  0 , Delayed)
#define mDATWriteU1BitEEP_RESERVED6Delayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  2 ,  0  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_RESERVED6Immediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  2 ,  0  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_RESERVED6Default(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  2 ,  0  , (ValueToWrite), Immediate)

// EEP_CPE_IMPULS -- Group GeneralParameterBank, Byte  2  , Bit (MSB)  1  , SizeInBit  1 
#ifdef EEP_CPE_IMPULS
  #error "Do not define EEP_CPE_IMPULS, because this is a lexem used for concatenation."
#endif
#define cDATEEP_CPE_IMPULSPositionByte      2 
#define cDATEEP_CPE_IMPULSPositionBit       1 
#define mDATPeeResetU1BitEEP_CPE_IMPULS()     \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  2 ,  1 , 0, Delayed)
#define mDATReadU1BitEEP_CPE_IMPULSDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_CPE_IMPULSDefault() \
      mDATPeeReadU1Bit(Dbk, GeneralParameterBank,  2 ,  1 , Delayed)
#define mDATWriteU1BitEEP_CPE_IMPULSDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  2 ,  1  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_CPE_IMPULSImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  2 ,  1  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_CPE_IMPULSDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  2 ,  1  , (ValueToWrite), Immediate)

// EEP_FEU_BROUILLARD -- Group GeneralParameterBank, Byte  2  , Bit (MSB)  2  , SizeInBit  1 
#ifdef EEP_FEU_BROUILLARD
  #error "Do not define EEP_FEU_BROUILLARD, because this is a lexem used for concatenation."
#endif
#define cDATEEP_FEU_BROUILLARDPositionByte      2 
#define cDATEEP_FEU_BROUILLARDPositionBit       2 
#define mDATPeeResetU1BitEEP_FEU_BROUILLARD()     \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  2 ,  2 , 0, Delayed)
#define mDATReadU1BitEEP_FEU_BROUILLARDDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_FEU_BROUILLARDDefault() \
      mDATPeeReadU1Bit(Dbk, GeneralParameterBank,  2 ,  2 , Delayed)
#define mDATWriteU1BitEEP_FEU_BROUILLARDDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  2 ,  2  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_FEU_BROUILLARDImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  2 ,  2  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_FEU_BROUILLARDDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  2 ,  2  , (ValueToWrite), Immediate)

// EEP_EV_ARR -- Group GeneralParameterBank, Byte  2  , Bit (MSB)  3  , SizeInBit  1 
#ifdef EEP_EV_ARR
  #error "Do not define EEP_EV_ARR, because this is a lexem used for concatenation."
#endif
#define cDATEEP_EV_ARRPositionByte      2 
#define cDATEEP_EV_ARRPositionBit       3 
#define mDATPeeResetU1BitEEP_EV_ARR()     \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  2 ,  3 , 0, Delayed)
#define mDATReadU1BitEEP_EV_ARRDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_EV_ARRDefault() \
      mDATPeeReadU1Bit(Dbk, GeneralParameterBank,  2 ,  3 , Delayed)
#define mDATWriteU1BitEEP_EV_ARRDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  2 ,  3  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_EV_ARRImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  2 ,  3  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_EV_ARRDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  2 ,  3  , (ValueToWrite), Immediate)

// EEP_INFO_REGIME -- Group GeneralParameterBank, Byte  2  , Bit (MSB)  4  , SizeInBit  1 
#ifdef EEP_INFO_REGIME
  #error "Do not define EEP_INFO_REGIME, because this is a lexem used for concatenation."
#endif
#define cDATEEP_INFO_REGIMEPositionByte      2 
#define cDATEEP_INFO_REGIMEPositionBit       4 
#define mDATPeeResetU1BitEEP_INFO_REGIME()     \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  2 ,  4 , 0, Delayed)
#define mDATReadU1BitEEP_INFO_REGIMEDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_INFO_REGIMEDefault() \
      mDATPeeReadU1Bit(Dbk, GeneralParameterBank,  2 ,  4 , Delayed)
#define mDATWriteU1BitEEP_INFO_REGIMEDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  2 ,  4  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_INFO_REGIMEImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  2 ,  4  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_INFO_REGIMEDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  2 ,  4  , (ValueToWrite), Immediate)

// EEP_CLI_REM -- Group GeneralParameterBank, Byte  2  , Bit (MSB)  5  , SizeInBit  1 
#ifdef EEP_CLI_REM
  #error "Do not define EEP_CLI_REM, because this is a lexem used for concatenation."
#endif
#define cDATEEP_CLI_REMPositionByte      2 
#define cDATEEP_CLI_REMPositionBit       5 
#define mDATPeeResetU1BitEEP_CLI_REM()     \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  2 ,  5 , 0, Delayed)
#define mDATReadU1BitEEP_CLI_REMDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_CLI_REMDefault() \
      mDATPeeReadU1Bit(Dbk, GeneralParameterBank,  2 ,  5 , Delayed)
#define mDATWriteU1BitEEP_CLI_REMDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  2 ,  5  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_CLI_REMImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  2 ,  5  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_CLI_REMDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  2 ,  5  , (ValueToWrite), Immediate)

// EEP_CAD_BAGUE_AV -- Group GeneralParameterBank, Byte  2  , Bit (MSB)  6  , SizeInBit  1 
#ifdef EEP_CAD_BAGUE_AV
  #error "Do not define EEP_CAD_BAGUE_AV, because this is a lexem used for concatenation."
#endif
#define cDATEEP_CAD_BAGUE_AVPositionByte      2 
#define cDATEEP_CAD_BAGUE_AVPositionBit       6 
#define mDATPeeResetU1BitEEP_CAD_BAGUE_AV()     \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  2 ,  6 , 0, Delayed)
#define mDATReadU1BitEEP_CAD_BAGUE_AVDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_CAD_BAGUE_AVDefault() \
      mDATPeeReadU1Bit(Dbk, GeneralParameterBank,  2 ,  6 , Delayed)
#define mDATWriteU1BitEEP_CAD_BAGUE_AVDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  2 ,  6  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_CAD_BAGUE_AVImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  2 ,  6  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_CAD_BAGUE_AVDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  2 ,  6  , (ValueToWrite), Immediate)

// EEP_AUTCRASH -- Group GeneralParameterBank, Byte  2  , Bit (MSB)  7  , SizeInBit  1 
#ifdef EEP_AUTCRASH
  #error "Do not define EEP_AUTCRASH, because this is a lexem used for concatenation."
#endif
#define cDATEEP_AUTCRASHPositionByte      2 
#define cDATEEP_AUTCRASHPositionBit       7 
#define mDATPeeResetU1BitEEP_AUTCRASH()     \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  2 ,  7 , 1, Delayed)
#define mDATReadU1BitEEP_AUTCRASHDefaultValueDefault() ((BOOL)1)
#define mDATReadU1BitEEP_AUTCRASHDefault() \
      mDATPeeReadU1Bit(Dbk, GeneralParameterBank,  2 ,  7 , Delayed)
#define mDATWriteU1BitEEP_AUTCRASHDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  2 ,  7  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_AUTCRASHImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  2 ,  7  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_AUTCRASHDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  2 ,  7  , (ValueToWrite), Immediate)

// EEP_AUTVERLOG -- Group GeneralParameterBank, Byte  3  , Bit (MSB)  0  , SizeInBit  1 
#ifdef EEP_AUTVERLOG
  #error "Do not define EEP_AUTVERLOG, because this is a lexem used for concatenation."
#endif
#define cDATEEP_AUTVERLOGPositionByte      3 
#define cDATEEP_AUTVERLOGPositionBit       0 
#define mDATPeeResetU1BitEEP_AUTVERLOG()     \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  3 ,  0 , 1, Delayed)
#define mDATReadU1BitEEP_AUTVERLOGDefaultValueDefault() ((BOOL)1)
#define mDATReadU1BitEEP_AUTVERLOGDefault() \
      mDATPeeReadU1Bit(Dbk, GeneralParameterBank,  3 ,  0 , Delayed)
#define mDATWriteU1BitEEP_AUTVERLOGDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  3 ,  0  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_AUTVERLOGImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  3 ,  0  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_AUTVERLOGDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  3 ,  0  , (ValueToWrite), Immediate)

// EEP_AUTPLAF -- Group GeneralParameterBank, Byte  3  , Bit (MSB)  1  , SizeInBit  1 
#ifdef EEP_AUTPLAF
  #error "Do not define EEP_AUTPLAF, because this is a lexem used for concatenation."
#endif
#define cDATEEP_AUTPLAFPositionByte      3 
#define cDATEEP_AUTPLAFPositionBit       1 
#define mDATPeeResetU1BitEEP_AUTPLAF()     \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  3 ,  1 , 0, Delayed)
#define mDATReadU1BitEEP_AUTPLAFDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_AUTPLAFDefault() \
      mDATPeeReadU1Bit(Dbk, GeneralParameterBank,  3 ,  1 , Delayed)
#define mDATWriteU1BitEEP_AUTPLAFDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  3 ,  1  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_AUTPLAFImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  3 ,  1  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_AUTPLAFDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  3 ,  1  , (ValueToWrite), Immediate)

// EEP_KEY_BUTTON -- Group GeneralParameterBank, Byte  3  , Bit (MSB)  2  , SizeInBit  1 
#ifdef EEP_KEY_BUTTON
  #error "Do not define EEP_KEY_BUTTON, because this is a lexem used for concatenation."
#endif
#define cDATEEP_KEY_BUTTONPositionByte      3 
#define cDATEEP_KEY_BUTTONPositionBit       2 
#define mDATPeeResetU1BitEEP_KEY_BUTTON()     \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  3 ,  2 , 0, Delayed)
#define mDATReadU1BitEEP_KEY_BUTTONDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_KEY_BUTTONDefault() \
      mDATPeeReadU1Bit(Dbk, GeneralParameterBank,  3 ,  2 , Delayed)
#define mDATWriteU1BitEEP_KEY_BUTTONDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  3 ,  2  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_KEY_BUTTONImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  3 ,  2  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_KEY_BUTTONDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  3 ,  2  , (ValueToWrite), Immediate)

// EEP_CALALARM -- Group GeneralParameterBank, Byte  3  , Bit (MSB)  3  , SizeInBit  1 
#ifdef EEP_CALALARM
  #error "Do not define EEP_CALALARM, because this is a lexem used for concatenation."
#endif
#define cDATEEP_CALALARMPositionByte      3 
#define cDATEEP_CALALARMPositionBit       3 
#define mDATPeeResetU1BitEEP_CALALARM()     \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  3 ,  3 , 0, Delayed)
#define mDATReadU1BitEEP_CALALARMDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_CALALARMDefault() \
      mDATPeeReadU1Bit(Dbk, GeneralParameterBank,  3 ,  3 , Delayed)
#define mDATWriteU1BitEEP_CALALARMDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  3 ,  3  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_CALALARMImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  3 ,  3  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_CALALARMDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  3 ,  3  , (ValueToWrite), Immediate)

// EEP_CALULKTR -- Group GeneralParameterBank, Byte  3  , Bit (MSB)  4  , SizeInBit  1 
#ifdef EEP_CALULKTR
  #error "Do not define EEP_CALULKTR, because this is a lexem used for concatenation."
#endif
#define cDATEEP_CALULKTRPositionByte      3 
#define cDATEEP_CALULKTRPositionBit       4 
#define mDATPeeResetU1BitEEP_CALULKTR()     \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  3 ,  4 , 1, Delayed)
#define mDATReadU1BitEEP_CALULKTRDefaultValueDefault() ((BOOL)1)
#define mDATReadU1BitEEP_CALULKTRDefault() \
      mDATPeeReadU1Bit(Dbk, GeneralParameterBank,  3 ,  4 , Delayed)
#define mDATWriteU1BitEEP_CALULKTRDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  3 ,  4  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_CALULKTRImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  3 ,  4  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_CALULKTRDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  3 ,  4  , (ValueToWrite), Immediate)

// EEP_AUTRECRF -- Group GeneralParameterBank, Byte  3  , Bit (MSB)  5  , SizeInBit  1 
#ifdef EEP_AUTRECRF
  #error "Do not define EEP_AUTRECRF, because this is a lexem used for concatenation."
#endif
#define cDATEEP_AUTRECRFPositionByte      3 
#define cDATEEP_AUTRECRFPositionBit       5 
#define mDATPeeResetU1BitEEP_AUTRECRF()     \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  3 ,  5 , 0, Delayed)
#define mDATReadU1BitEEP_AUTRECRFDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_AUTRECRFDefault() \
      mDATPeeReadU1Bit(Dbk, GeneralParameterBank,  3 ,  5 , Delayed)
#define mDATWriteU1BitEEP_AUTRECRFDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  3 ,  5  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_AUTRECRFImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  3 ,  5  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_AUTRECRFDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  3 ,  5  , (ValueToWrite), Immediate)

// EEP_OUBLICEINTURE -- Group GeneralParameterBank, Byte  3  , Bit (MSB)  6  , SizeInBit  1 
#ifdef EEP_OUBLICEINTURE
  #error "Do not define EEP_OUBLICEINTURE, because this is a lexem used for concatenation."
#endif
#define cDATEEP_OUBLICEINTUREPositionByte      3 
#define cDATEEP_OUBLICEINTUREPositionBit       6 
#define mDATPeeResetU1BitEEP_OUBLICEINTURE()     \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  3 ,  6 , 0, Delayed)
#define mDATReadU1BitEEP_OUBLICEINTUREDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_OUBLICEINTUREDefault() \
      mDATPeeReadU1Bit(Dbk, GeneralParameterBank,  3 ,  6 , Delayed)
#define mDATWriteU1BitEEP_OUBLICEINTUREDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  3 ,  6  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_OUBLICEINTUREImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  3 ,  6  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_OUBLICEINTUREDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  3 ,  6  , (ValueToWrite), Immediate)

// EEP_CAR_SECURE -- Group GeneralParameterBank, Byte  3  , Bit (MSB)  7  , SizeInBit  1 
#ifdef EEP_CAR_SECURE
  #error "Do not define EEP_CAR_SECURE, because this is a lexem used for concatenation."
#endif
#define cDATEEP_CAR_SECUREPositionByte      3 
#define cDATEEP_CAR_SECUREPositionBit       7 
#define mDATPeeResetU1BitEEP_CAR_SECURE()     \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  3 ,  7 , 0, Delayed)
#define mDATReadU1BitEEP_CAR_SECUREDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_CAR_SECUREDefault() \
      mDATPeeReadU1Bit(Dbk, GeneralParameterBank,  3 ,  7 , Delayed)
#define mDATWriteU1BitEEP_CAR_SECUREDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  3 ,  7  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_CAR_SECUREImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  3 ,  7  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_CAR_SECUREDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  3 ,  7  , (ValueToWrite), Immediate)

// EEP_SDO -- Group GeneralParameterBank, Byte  4  , Bit (MSB)  0  , SizeInBit  1 
#ifdef EEP_SDO
  #error "Do not define EEP_SDO, because this is a lexem used for concatenation."
#endif
#define cDATEEP_SDOPositionByte      4 
#define cDATEEP_SDOPositionBit       0 
#define mDATPeeResetU1BitEEP_SDO()     \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  4 ,  0 , 0, Delayed)
#define mDATReadU1BitEEP_SDODefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_SDODefault() \
      mDATPeeReadU1Bit(Dbk, GeneralParameterBank,  4 ,  0 , Delayed)
#define mDATWriteU1BitEEP_SDODelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  4 ,  0  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_SDOImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  4 ,  0  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_SDODefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  4 ,  0  , (ValueToWrite), Immediate)

// EEP_DefrosterActivationState -- Group GeneralParameterBank, Byte  4  , Bit (MSB)  1  , SizeInBit  1 
#ifdef EEP_DefrosterActivationState
  #error "Do not define EEP_DefrosterActivationState, because this is a lexem used for concatenation."
#endif
#define cDATEEP_DefrosterActivationStatePositionByte      4 
#define cDATEEP_DefrosterActivationStatePositionBit       1 
#define mDATPeeResetU1BitEEP_DefrosterActivationState()     \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  4 ,  1 , 0, Delayed)
#define mDATReadU1BitEEP_DefrosterActivationStateDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_DefrosterActivationStateDefault() \
      mDATPeeReadU1Bit(Dbk, GeneralParameterBank,  4 ,  1 , Delayed)
#define mDATWriteU1BitEEP_DefrosterActivationStateDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  4 ,  1  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_DefrosterActivationStateImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  4 ,  1  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_DefrosterActivationStateDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  4 ,  1  , (ValueToWrite), Immediate)

// EEP_DoorlockLedActivation -- Group GeneralParameterBank, Byte  4  , Bit (MSB)  2  , SizeInBit  1 
#ifdef EEP_DoorlockLedActivation
  #error "Do not define EEP_DoorlockLedActivation, because this is a lexem used for concatenation."
#endif
#define cDATEEP_DoorlockLedActivationPositionByte      4 
#define cDATEEP_DoorlockLedActivationPositionBit       2 
#define mDATPeeResetU1BitEEP_DoorlockLedActivation()     \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  4 ,  2 , 0, Delayed)
#define mDATReadU1BitEEP_DoorlockLedActivationDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_DoorlockLedActivationDefault() \
      mDATPeeReadU1Bit(Dbk, GeneralParameterBank,  4 ,  2 , Delayed)
#define mDATWriteU1BitEEP_DoorlockLedActivationDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  4 ,  2  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_DoorlockLedActivationImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  4 ,  2  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_DoorlockLedActivationDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, GeneralParameterBank,  4 ,  2  , (ValueToWrite), Immediate)

// Spare_GeneralParameterBank -- Group GeneralParameterBank, Byte  5  , Bit (MSB)  7  , SizeInBit  8 
#ifdef Spare_GeneralParameterBank
  #error "Do not define Spare_GeneralParameterBank, because this is a lexem used for concatenation."
#endif
#define cDATSpare_GeneralParameterBankPositionByte      5 
#define cDATSpare_GeneralParameterBankPositionBit        0xFF
#define mDATPeeResetU8BitSpare_GeneralParameterBank()     \
      mDATPeeWriteU8Bit(Dbk, GeneralParameterBank,  5 ,  7 ,  8 , 0, Delayed)
#define mDATReadU8BitSpare_GeneralParameterBankDefaultValueDefault() ((U8)0)
#define mDATReadU8BitSpare_GeneralParameterBankDefault() \
      mDATPeeReadU8Bit(Dbk, GeneralParameterBank,  5 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitSpare_GeneralParameterBankDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, GeneralParameterBank,  5 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitSpare_GeneralParameterBankImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, GeneralParameterBank,  5 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitSpare_GeneralParameterBankDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, GeneralParameterBank,  5 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_TimeOutTW2 -- Group FactoryConfigBank, Byte  0  , Bit (MSB)  7  , SizeInBit  16 
#ifdef EEP_TimeOutTW2
  #error "Do not define EEP_TimeOutTW2, because this is a lexem used for concatenation."
#endif
#define cDATEEP_TimeOutTW2PositionByte      0 
#define cDATEEP_TimeOutTW2PositionBit        0xFF
#define mDATPeeResetU16BitEEP_TimeOutTW2()     \
      mDATPeeWriteU16Bit(Dbk, FactoryConfigBank,  0 ,  7 ,  16 , 500, Delayed)
#define mDATReadU16BitEEP_TimeOutTW2DefaultValueDefault() ((U16)500)
#define mDATReadU16BitEEP_TimeOutTW2Default() \
      mDATPeeReadU16Bit(Dbk, FactoryConfigBank,  0 ,  7 ,  16 , Delayed)
#define mDATWriteU16BitEEP_TimeOutTW2Delayed(ValueToWrite) \
      mDATPeeWriteU16Bit(Dbk, FactoryConfigBank,  0 ,  7 ,  16 , (ValueToWrite), Delayed)
#define mDATWriteU16BitEEP_TimeOutTW2Immediate(ValueToWrite) \
      mDATPeeWriteU16Bit(Dbk, FactoryConfigBank,  0 ,  7 ,  16 , (ValueToWrite), Immediate)
#define mDATWriteU16BitEEP_TimeOutTW2Default(ValueToWrite) \
      mDATPeeWriteU16Bit(Dbk, FactoryConfigBank,  0 ,  7 ,  16 , (ValueToWrite), Immediate)

// EEP_TPS_PLAF -- Group FactoryConfigBank, Byte  2  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_TPS_PLAF
  #error "Do not define EEP_TPS_PLAF, because this is a lexem used for concatenation."
#endif
#define cDATEEP_TPS_PLAFPositionByte      2 
#define cDATEEP_TPS_PLAFPositionBit        0xFF
#define mDATPeeResetU8BitEEP_TPS_PLAF()     \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  2 ,  7 ,  8 , 37, Delayed)
#define mDATReadU8BitEEP_TPS_PLAFDefaultValueDefault() ((U8)37)
#define mDATReadU8BitEEP_TPS_PLAFDefault() \
      mDATPeeReadU8Bit(Dbk, FactoryConfigBank,  2 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_TPS_PLAFDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  2 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_TPS_PLAFImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  2 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_TPS_PLAFDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  2 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_TPS_APC -- Group FactoryConfigBank, Byte  3  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_TPS_APC
  #error "Do not define EEP_TPS_APC, because this is a lexem used for concatenation."
#endif
#define cDATEEP_TPS_APCPositionByte      3 
#define cDATEEP_TPS_APCPositionBit        0xFF
#define mDATPeeResetU8BitEEP_TPS_APC()     \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  3 ,  7 ,  8 , 36, Delayed)
#define mDATReadU8BitEEP_TPS_APCDefaultValueDefault() ((U8)36)
#define mDATReadU8BitEEP_TPS_APCDefault() \
      mDATPeeReadU8Bit(Dbk, FactoryConfigBank,  3 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_TPS_APCDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  3 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_TPS_APCImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  3 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_TPS_APCDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  3 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_TPS_POSIT_BALAIS -- Group FactoryConfigBank, Byte  4  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_TPS_POSIT_BALAIS
  #error "Do not define EEP_TPS_POSIT_BALAIS, because this is a lexem used for concatenation."
#endif
#define cDATEEP_TPS_POSIT_BALAISPositionByte      4 
#define cDATEEP_TPS_POSIT_BALAISPositionBit        0xFF
#define mDATPeeResetU8BitEEP_TPS_POSIT_BALAIS()     \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  4 ,  7 ,  8 , 0, Delayed)
#define mDATReadU8BitEEP_TPS_POSIT_BALAISDefaultValueDefault() ((U8)0)
#define mDATReadU8BitEEP_TPS_POSIT_BALAISDefault() \
      mDATPeeReadU8Bit(Dbk, FactoryConfigBank,  4 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_TPS_POSIT_BALAISDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  4 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_TPS_POSIT_BALAISImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  4 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_TPS_POSIT_BALAISDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  4 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_TPS_FILT_AF -- Group FactoryConfigBank, Byte  5  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_TPS_FILT_AF
  #error "Do not define EEP_TPS_FILT_AF, because this is a lexem used for concatenation."
#endif
#define cDATEEP_TPS_FILT_AFPositionByte      5 
#define cDATEEP_TPS_FILT_AFPositionBit        0xFF
#define mDATPeeResetU8BitEEP_TPS_FILT_AF()     \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  5 ,  7 ,  8 , 2, Delayed)
#define mDATReadU8BitEEP_TPS_FILT_AFDefaultValueDefault() ((U8)2)
#define mDATReadU8BitEEP_TPS_FILT_AFDefault() \
      mDATPeeReadU8Bit(Dbk, FactoryConfigBank,  5 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_TPS_FILT_AFDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  5 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_TPS_FILT_AFImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  5 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_TPS_FILT_AFDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  5 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_TPS_MAX_COUPLBLOC -- Group FactoryConfigBank, Byte  6  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_TPS_MAX_COUPLBLOC
  #error "Do not define EEP_TPS_MAX_COUPLBLOC, because this is a lexem used for concatenation."
#endif
#define cDATEEP_TPS_MAX_COUPLBLOCPositionByte      6 
#define cDATEEP_TPS_MAX_COUPLBLOCPositionBit        0xFF
#define mDATPeeResetU8BitEEP_TPS_MAX_COUPLBLOC()     \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  6 ,  7 ,  8 , 20, Delayed)
#define mDATReadU8BitEEP_TPS_MAX_COUPLBLOCDefaultValueDefault() ((U8)20)
#define mDATReadU8BitEEP_TPS_MAX_COUPLBLOCDefault() \
      mDATPeeReadU8Bit(Dbk, FactoryConfigBank,  6 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_TPS_MAX_COUPLBLOCDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  6 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_TPS_MAX_COUPLBLOCImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  6 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_TPS_MAX_COUPLBLOCDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  6 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_TPS_ARRET -- Group FactoryConfigBank, Byte  7  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_TPS_ARRET
  #error "Do not define EEP_TPS_ARRET, because this is a lexem used for concatenation."
#endif
#define cDATEEP_TPS_ARRETPositionByte      7 
#define cDATEEP_TPS_ARRETPositionBit        0xFF
#define mDATPeeResetU8BitEEP_TPS_ARRET()     \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  7 ,  7 ,  8 , 15, Delayed)
#define mDATReadU8BitEEP_TPS_ARRETDefaultValueDefault() ((U8)15)
#define mDATReadU8BitEEP_TPS_ARRETDefault() \
      mDATPeeReadU8Bit(Dbk, FactoryConfigBank,  7 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_TPS_ARRETDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  7 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_TPS_ARRETImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  7 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_TPS_ARRETDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  7 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_PROLONG_APPUI_COURT -- Group FactoryConfigBank, Byte  8  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_PROLONG_APPUI_COURT
  #error "Do not define EEP_PROLONG_APPUI_COURT, because this is a lexem used for concatenation."
#endif
#define cDATEEP_PROLONG_APPUI_COURTPositionByte      8 
#define cDATEEP_PROLONG_APPUI_COURTPositionBit        0xFF
#define mDATPeeResetU8BitEEP_PROLONG_APPUI_COURT()     \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  8 ,  7 ,  8 , 1, Delayed)
#define mDATReadU8BitEEP_PROLONG_APPUI_COURTDefaultValueDefault() ((U8)1)
#define mDATReadU8BitEEP_PROLONG_APPUI_COURTDefault() \
      mDATPeeReadU8Bit(Dbk, FactoryConfigBank,  8 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_PROLONG_APPUI_COURTDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  8 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_PROLONG_APPUI_COURTImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  8 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_PROLONG_APPUI_COURTDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  8 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_PROLONG_APPUI_LONG -- Group FactoryConfigBank, Byte  9  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_PROLONG_APPUI_LONG
  #error "Do not define EEP_PROLONG_APPUI_LONG, because this is a lexem used for concatenation."
#endif
#define cDATEEP_PROLONG_APPUI_LONGPositionByte      9 
#define cDATEEP_PROLONG_APPUI_LONGPositionBit        0xFF
#define mDATPeeResetU8BitEEP_PROLONG_APPUI_LONG()     \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  9 ,  7 ,  8 , 3, Delayed)
#define mDATReadU8BitEEP_PROLONG_APPUI_LONGDefaultValueDefault() ((U8)3)
#define mDATReadU8BitEEP_PROLONG_APPUI_LONGDefault() \
      mDATPeeReadU8Bit(Dbk, FactoryConfigBank,  9 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_PROLONG_APPUI_LONGDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  9 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_PROLONG_APPUI_LONGImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  9 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_PROLONG_APPUI_LONGDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  9 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_TPS_APPUILAV -- Group FactoryConfigBank, Byte  10  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_TPS_APPUILAV
  #error "Do not define EEP_TPS_APPUILAV, because this is a lexem used for concatenation."
#endif
#define cDATEEP_TPS_APPUILAVPositionByte      10 
#define cDATEEP_TPS_APPUILAVPositionBit        0xFF
#define mDATPeeResetU8BitEEP_TPS_APPUILAV()     \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  10 ,  7 ,  8 , 42, Delayed)
#define mDATReadU8BitEEP_TPS_APPUILAVDefaultValueDefault() ((U8)42)
#define mDATReadU8BitEEP_TPS_APPUILAVDefault() \
      mDATPeeReadU8Bit(Dbk, FactoryConfigBank,  10 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_TPS_APPUILAVDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  10 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_TPS_APPUILAVImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  10 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_TPS_APPUILAVDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  10 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_TPS_CAD_FIXE -- Group FactoryConfigBank, Byte  11  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_TPS_CAD_FIXE
  #error "Do not define EEP_TPS_CAD_FIXE, because this is a lexem used for concatenation."
#endif
#define cDATEEP_TPS_CAD_FIXEPositionByte      11 
#define cDATEEP_TPS_CAD_FIXEPositionBit        0xFF
#define mDATPeeResetU8BitEEP_TPS_CAD_FIXE()     \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  11 ,  7 ,  8 , 62, Delayed)
#define mDATReadU8BitEEP_TPS_CAD_FIXEDefaultValueDefault() ((U8)62)
#define mDATReadU8BitEEP_TPS_CAD_FIXEDefault() \
      mDATPeeReadU8Bit(Dbk, FactoryConfigBank,  11 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_TPS_CAD_FIXEDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  11 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_TPS_CAD_FIXEImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  11 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_TPS_CAD_FIXEDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  11 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_TPS_ESSUIE_MINI -- Group FactoryConfigBank, Byte  12  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_TPS_ESSUIE_MINI
  #error "Do not define EEP_TPS_ESSUIE_MINI, because this is a lexem used for concatenation."
#endif
#define cDATEEP_TPS_ESSUIE_MINIPositionByte      12 
#define cDATEEP_TPS_ESSUIE_MINIPositionBit        0xFF
#define mDATPeeResetU8BitEEP_TPS_ESSUIE_MINI()     \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  12 ,  7 ,  8 , 25, Delayed)
#define mDATReadU8BitEEP_TPS_ESSUIE_MINIDefaultValueDefault() ((U8)25)
#define mDATReadU8BitEEP_TPS_ESSUIE_MINIDefault() \
      mDATPeeReadU8Bit(Dbk, FactoryConfigBank,  12 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_TPS_ESSUIE_MINIDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  12 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_TPS_ESSUIE_MINIImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  12 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_TPS_ESSUIE_MINIDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  12 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_TPS_POSIT_BALAIS_AR -- Group FactoryConfigBank, Byte  13  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_TPS_POSIT_BALAIS_AR
  #error "Do not define EEP_TPS_POSIT_BALAIS_AR, because this is a lexem used for concatenation."
#endif
#define cDATEEP_TPS_POSIT_BALAIS_ARPositionByte      13 
#define cDATEEP_TPS_POSIT_BALAIS_ARPositionBit        0xFF
#define mDATPeeResetU8BitEEP_TPS_POSIT_BALAIS_AR()     \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  13 ,  7 ,  8 , 0, Delayed)
#define mDATReadU8BitEEP_TPS_POSIT_BALAIS_ARDefaultValueDefault() ((U8)0)
#define mDATReadU8BitEEP_TPS_POSIT_BALAIS_ARDefault() \
      mDATPeeReadU8Bit(Dbk, FactoryConfigBank,  13 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_TPS_POSIT_BALAIS_ARDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  13 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_TPS_POSIT_BALAIS_ARImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  13 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_TPS_POSIT_BALAIS_ARDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  13 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_TPS_REPRISE -- Group FactoryConfigBank, Byte  14  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_TPS_REPRISE
  #error "Do not define EEP_TPS_REPRISE, because this is a lexem used for concatenation."
#endif
#define cDATEEP_TPS_REPRISEPositionByte      14 
#define cDATEEP_TPS_REPRISEPositionBit        0xFF
#define mDATPeeResetU8BitEEP_TPS_REPRISE()     \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  14 ,  7 ,  8 , 2, Delayed)
#define mDATReadU8BitEEP_TPS_REPRISEDefaultValueDefault() ((U8)2)
#define mDATReadU8BitEEP_TPS_REPRISEDefault() \
      mDATPeeReadU8Bit(Dbk, FactoryConfigBank,  14 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_TPS_REPRISEDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  14 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_TPS_REPRISEImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  14 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_TPS_REPRISEDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  14 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_PROLONG_APPUI_ARR -- Group FactoryConfigBank, Byte  15  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_PROLONG_APPUI_ARR
  #error "Do not define EEP_PROLONG_APPUI_ARR, because this is a lexem used for concatenation."
#endif
#define cDATEEP_PROLONG_APPUI_ARRPositionByte      15 
#define cDATEEP_PROLONG_APPUI_ARRPositionBit        0xFF
#define mDATPeeResetU8BitEEP_PROLONG_APPUI_ARR()     \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  15 ,  7 ,  8 , 3, Delayed)
#define mDATReadU8BitEEP_PROLONG_APPUI_ARRDefaultValueDefault() ((U8)3)
#define mDATReadU8BitEEP_PROLONG_APPUI_ARRDefault() \
      mDATPeeReadU8Bit(Dbk, FactoryConfigBank,  15 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_PROLONG_APPUI_ARRDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  15 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_PROLONG_APPUI_ARRImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  15 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_PROLONG_APPUI_ARRDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  15 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_TPS_CLI -- Group FactoryConfigBank, Byte  16  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_TPS_CLI
  #error "Do not define EEP_TPS_CLI, because this is a lexem used for concatenation."
#endif
#define cDATEEP_TPS_CLIPositionByte      16 
#define cDATEEP_TPS_CLIPositionBit        0xFF
#define mDATPeeResetU8BitEEP_TPS_CLI()     \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  16 ,  7 ,  8 , 8, Delayed)
#define mDATReadU8BitEEP_TPS_CLIDefaultValueDefault() ((U8)8)
#define mDATReadU8BitEEP_TPS_CLIDefault() \
      mDATPeeReadU8Bit(Dbk, FactoryConfigBank,  16 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_TPS_CLIDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  16 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_TPS_CLIImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  16 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_TPS_CLIDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  16 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_TPS_CLIDEGRAD -- Group FactoryConfigBank, Byte  17  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_TPS_CLIDEGRAD
  #error "Do not define EEP_TPS_CLIDEGRAD, because this is a lexem used for concatenation."
#endif
#define cDATEEP_TPS_CLIDEGRADPositionByte      17 
#define cDATEEP_TPS_CLIDEGRADPositionBit        0xFF
#define mDATPeeResetU8BitEEP_TPS_CLIDEGRAD()     \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  17 ,  7 ,  8 , 4, Delayed)
#define mDATReadU8BitEEP_TPS_CLIDEGRADDefaultValueDefault() ((U8)4)
#define mDATReadU8BitEEP_TPS_CLIDEGRADDefault() \
      mDATPeeReadU8Bit(Dbk, FactoryConfigBank,  17 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_TPS_CLIDEGRADDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  17 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_TPS_CLIDEGRADImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  17 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_TPS_CLIDEGRADDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  17 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_TPS_RETARD_DETRESSE -- Group FactoryConfigBank, Byte  18  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_TPS_RETARD_DETRESSE
  #error "Do not define EEP_TPS_RETARD_DETRESSE, because this is a lexem used for concatenation."
#endif
#define cDATEEP_TPS_RETARD_DETRESSEPositionByte      18 
#define cDATEEP_TPS_RETARD_DETRESSEPositionBit        0xFF
#define mDATPeeResetU8BitEEP_TPS_RETARD_DETRESSE()     \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  18 ,  7 ,  8 , 5, Delayed)
#define mDATReadU8BitEEP_TPS_RETARD_DETRESSEDefaultValueDefault() ((U8)5)
#define mDATReadU8BitEEP_TPS_RETARD_DETRESSEDefault() \
      mDATPeeReadU8Bit(Dbk, FactoryConfigBank,  18 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_TPS_RETARD_DETRESSEDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  18 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_TPS_RETARD_DETRESSEImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  18 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_TPS_RETARD_DETRESSEDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  18 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_TIMER_DETRESSE -- Group FactoryConfigBank, Byte  19  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_TIMER_DETRESSE
  #error "Do not define EEP_TIMER_DETRESSE, because this is a lexem used for concatenation."
#endif
#define cDATEEP_TIMER_DETRESSEPositionByte      19 
#define cDATEEP_TIMER_DETRESSEPositionBit        0xFF
#define mDATPeeResetU8BitEEP_TIMER_DETRESSE()     \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  19 ,  7 ,  8 , 36, Delayed)
#define mDATReadU8BitEEP_TIMER_DETRESSEDefaultValueDefault() ((U8)36)
#define mDATReadU8BitEEP_TIMER_DETRESSEDefault() \
      mDATPeeReadU8Bit(Dbk, FactoryConfigBank,  19 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_TIMER_DETRESSEDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  19 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_TIMER_DETRESSEImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  19 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_TIMER_DETRESSEDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  19 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_TPS_TEMPO_DEG -- Group FactoryConfigBank, Byte  20  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_TPS_TEMPO_DEG
  #error "Do not define EEP_TPS_TEMPO_DEG, because this is a lexem used for concatenation."
#endif
#define cDATEEP_TPS_TEMPO_DEGPositionByte      20 
#define cDATEEP_TPS_TEMPO_DEGPositionBit        0xFF
#define mDATPeeResetU8BitEEP_TPS_TEMPO_DEG()     \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  20 ,  7 ,  8 , 14, Delayed)
#define mDATReadU8BitEEP_TPS_TEMPO_DEGDefaultValueDefault() ((U8)14)
#define mDATReadU8BitEEP_TPS_TEMPO_DEGDefault() \
      mDATPeeReadU8Bit(Dbk, FactoryConfigBank,  20 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_TPS_TEMPO_DEGDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  20 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_TPS_TEMPO_DEGImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  20 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_TPS_TEMPO_DEGDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  20 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_TPS_IMPUL_MINI -- Group FactoryConfigBank, Byte  21  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_TPS_IMPUL_MINI
  #error "Do not define EEP_TPS_IMPUL_MINI, because this is a lexem used for concatenation."
#endif
#define cDATEEP_TPS_IMPUL_MINIPositionByte      21 
#define cDATEEP_TPS_IMPUL_MINIPositionBit        0xFF
#define mDATPeeResetU8BitEEP_TPS_IMPUL_MINI()     \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  21 ,  7 ,  8 , 8, Delayed)
#define mDATReadU8BitEEP_TPS_IMPUL_MINIDefaultValueDefault() ((U8)8)
#define mDATReadU8BitEEP_TPS_IMPUL_MINIDefault() \
      mDATPeeReadU8Bit(Dbk, FactoryConfigBank,  21 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_TPS_IMPUL_MINIDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  21 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_TPS_IMPUL_MINIImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  21 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_TPS_IMPUL_MINIDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  21 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_SBR_TIMEOUT_TM_TP -- Group FactoryConfigBank, Byte  22  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_SBR_TIMEOUT_TM_TP
  #error "Do not define EEP_SBR_TIMEOUT_TM_TP, because this is a lexem used for concatenation."
#endif
#define cDATEEP_SBR_TIMEOUT_TM_TPPositionByte      22 
#define cDATEEP_SBR_TIMEOUT_TM_TPPositionBit        0xFF
#define mDATPeeResetU8BitEEP_SBR_TIMEOUT_TM_TP()     \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  22 ,  7 ,  8 , 92, Delayed)
#define mDATReadU8BitEEP_SBR_TIMEOUT_TM_TPDefaultValueDefault() ((U8)92)
#define mDATReadU8BitEEP_SBR_TIMEOUT_TM_TPDefault() \
      mDATPeeReadU8Bit(Dbk, FactoryConfigBank,  22 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_SBR_TIMEOUT_TM_TPDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  22 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_SBR_TIMEOUT_TM_TPImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  22 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_SBR_TIMEOUT_TM_TPDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  22 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_SBR_ACTIVE_SPEED_THRESH_TP -- Group FactoryConfigBank, Byte  23  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_SBR_ACTIVE_SPEED_THRESH_TP
  #error "Do not define EEP_SBR_ACTIVE_SPEED_THRESH_TP, because this is a lexem used for concatenation."
#endif
#define cDATEEP_SBR_ACTIVE_SPEED_THRESH_TPPositionByte      23 
#define cDATEEP_SBR_ACTIVE_SPEED_THRESH_TPPositionBit        0xFF
#define mDATPeeResetU8BitEEP_SBR_ACTIVE_SPEED_THRESH_TP()     \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  23 ,  7 ,  8 , 10, Delayed)
#define mDATReadU8BitEEP_SBR_ACTIVE_SPEED_THRESH_TPDefaultValueDefault() ((U8)10)
#define mDATReadU8BitEEP_SBR_ACTIVE_SPEED_THRESH_TPDefault() \
      mDATPeeReadU8Bit(Dbk, FactoryConfigBank,  23 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_SBR_ACTIVE_SPEED_THRESH_TPDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  23 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_SBR_ACTIVE_SPEED_THRESH_TPImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  23 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_SBR_ACTIVE_SPEED_THRESH_TPDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  23 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_MAX_NB_ALERT_SEQUENCES_TP -- Group FactoryConfigBank, Byte  24  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_MAX_NB_ALERT_SEQUENCES_TP
  #error "Do not define EEP_MAX_NB_ALERT_SEQUENCES_TP, because this is a lexem used for concatenation."
#endif
#define cDATEEP_MAX_NB_ALERT_SEQUENCES_TPPositionByte      24 
#define cDATEEP_MAX_NB_ALERT_SEQUENCES_TPPositionBit        0xFF
#define mDATPeeResetU8BitEEP_MAX_NB_ALERT_SEQUENCES_TP()     \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  24 ,  7 ,  8 , 10, Delayed)
#define mDATReadU8BitEEP_MAX_NB_ALERT_SEQUENCES_TPDefaultValueDefault() ((U8)10)
#define mDATReadU8BitEEP_MAX_NB_ALERT_SEQUENCES_TPDefault() \
      mDATPeeReadU8Bit(Dbk, FactoryConfigBank,  24 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_MAX_NB_ALERT_SEQUENCES_TPDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  24 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_MAX_NB_ALERT_SEQUENCES_TPImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  24 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_MAX_NB_ALERT_SEQUENCES_TPDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  24 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_SEUIL_VIT_CONDAROU -- Group FactoryConfigBank, Byte  25  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_SEUIL_VIT_CONDAROU
  #error "Do not define EEP_SEUIL_VIT_CONDAROU, because this is a lexem used for concatenation."
#endif
#define cDATEEP_SEUIL_VIT_CONDAROUPositionByte      25 
#define cDATEEP_SEUIL_VIT_CONDAROUPositionBit        0xFF
#define mDATPeeResetU8BitEEP_SEUIL_VIT_CONDAROU()     \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  25 ,  7 ,  8 , 8, Delayed)
#define mDATReadU8BitEEP_SEUIL_VIT_CONDAROUDefaultValueDefault() ((U8)8)
#define mDATReadU8BitEEP_SEUIL_VIT_CONDAROUDefault() \
      mDATPeeReadU8Bit(Dbk, FactoryConfigBank,  25 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_SEUIL_VIT_CONDAROUDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  25 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_SEUIL_VIT_CONDAROUImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  25 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_SEUIL_VIT_CONDAROUDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  25 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_TPS_COM_MOTEUR -- Group FactoryConfigBank, Byte  26  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_TPS_COM_MOTEUR
  #error "Do not define EEP_TPS_COM_MOTEUR, because this is a lexem used for concatenation."
#endif
#define cDATEEP_TPS_COM_MOTEURPositionByte      26 
#define cDATEEP_TPS_COM_MOTEURPositionBit        0xFF
#define mDATPeeResetU8BitEEP_TPS_COM_MOTEUR()     \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  26 ,  7 ,  8 , 50, Delayed)
#define mDATReadU8BitEEP_TPS_COM_MOTEURDefaultValueDefault() ((U8)50)
#define mDATReadU8BitEEP_TPS_COM_MOTEURDefault() \
      mDATPeeReadU8Bit(Dbk, FactoryConfigBank,  26 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_TPS_COM_MOTEURDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  26 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_TPS_COM_MOTEURImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  26 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_TPS_COM_MOTEURDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  26 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_NBCOM_MAX -- Group FactoryConfigBank, Byte  27  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_NBCOM_MAX
  #error "Do not define EEP_NBCOM_MAX, because this is a lexem used for concatenation."
#endif
#define cDATEEP_NBCOM_MAXPositionByte      27 
#define cDATEEP_NBCOM_MAXPositionBit        0xFF
#define mDATPeeResetU8BitEEP_NBCOM_MAX()     \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  27 ,  7 ,  8 , 20, Delayed)
#define mDATReadU8BitEEP_NBCOM_MAXDefaultValueDefault() ((U8)20)
#define mDATReadU8BitEEP_NBCOM_MAXDefault() \
      mDATPeeReadU8Bit(Dbk, FactoryConfigBank,  27 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_NBCOM_MAXDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  27 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_NBCOM_MAXImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  27 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_NBCOM_MAXDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  27 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_TPS_REF -- Group FactoryConfigBank, Byte  28  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_TPS_REF
  #error "Do not define EEP_TPS_REF, because this is a lexem used for concatenation."
#endif
#define cDATEEP_TPS_REFPositionByte      28 
#define cDATEEP_TPS_REFPositionBit        0xFF
#define mDATPeeResetU8BitEEP_TPS_REF()     \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  28 ,  7 ,  8 , 2, Delayed)
#define mDATReadU8BitEEP_TPS_REFDefaultValueDefault() ((U8)2)
#define mDATReadU8BitEEP_TPS_REFDefault() \
      mDATPeeReadU8Bit(Dbk, FactoryConfigBank,  28 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_TPS_REFDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  28 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_TPS_REFImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  28 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_TPS_REFDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  28 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_TIMER_RECONDA_AUTO -- Group FactoryConfigBank, Byte  29  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_TIMER_RECONDA_AUTO
  #error "Do not define EEP_TIMER_RECONDA_AUTO, because this is a lexem used for concatenation."
#endif
#define cDATEEP_TIMER_RECONDA_AUTOPositionByte      29 
#define cDATEEP_TIMER_RECONDA_AUTOPositionBit        0xFF
#define mDATPeeResetU8BitEEP_TIMER_RECONDA_AUTO()     \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  29 ,  7 ,  8 , 30, Delayed)
#define mDATReadU8BitEEP_TIMER_RECONDA_AUTODefaultValueDefault() ((U8)30)
#define mDATReadU8BitEEP_TIMER_RECONDA_AUTODefault() \
      mDATPeeReadU8Bit(Dbk, FactoryConfigBank,  29 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_TIMER_RECONDA_AUTODelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  29 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_TIMER_RECONDA_AUTOImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  29 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_TIMER_RECONDA_AUTODefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  29 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_N_MISE_APC -- Group FactoryConfigBank, Byte  30  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_N_MISE_APC
  #error "Do not define EEP_N_MISE_APC, because this is a lexem used for concatenation."
#endif
#define cDATEEP_N_MISE_APCPositionByte      30 
#define cDATEEP_N_MISE_APCPositionBit        0xFF
#define mDATPeeResetU8BitEEP_N_MISE_APC()     \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  30 ,  7 ,  8 , 10, Delayed)
#define mDATReadU8BitEEP_N_MISE_APCDefaultValueDefault() ((U8)10)
#define mDATReadU8BitEEP_N_MISE_APCDefault() \
      mDATPeeReadU8Bit(Dbk, FactoryConfigBank,  30 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_N_MISE_APCDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  30 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_N_MISE_APCImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  30 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_N_MISE_APCDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  30 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_TPS_OUVPORTE -- Group FactoryConfigBank, Byte  31  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_TPS_OUVPORTE
  #error "Do not define EEP_TPS_OUVPORTE, because this is a lexem used for concatenation."
#endif
#define cDATEEP_TPS_OUVPORTEPositionByte      31 
#define cDATEEP_TPS_OUVPORTEPositionBit        0xFF
#define mDATPeeResetU8BitEEP_TPS_OUVPORTE()     \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  31 ,  7 ,  8 , 10, Delayed)
#define mDATReadU8BitEEP_TPS_OUVPORTEDefaultValueDefault() ((U8)10)
#define mDATReadU8BitEEP_TPS_OUVPORTEDefault() \
      mDATPeeReadU8Bit(Dbk, FactoryConfigBank,  31 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_TPS_OUVPORTEDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  31 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_TPS_OUVPORTEImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  31 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_TPS_OUVPORTEDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  31 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_TPS_BUZ_CLI -- Group FactoryConfigBank, Byte  32  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_TPS_BUZ_CLI
  #error "Do not define EEP_TPS_BUZ_CLI, because this is a lexem used for concatenation."
#endif
#define cDATEEP_TPS_BUZ_CLIPositionByte      32 
#define cDATEEP_TPS_BUZ_CLIPositionBit        0xFF
#define mDATPeeResetU8BitEEP_TPS_BUZ_CLI()     \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  32 ,  7 ,  8 , 4, Delayed)
#define mDATReadU8BitEEP_TPS_BUZ_CLIDefaultValueDefault() ((U8)4)
#define mDATReadU8BitEEP_TPS_BUZ_CLIDefault() \
      mDATPeeReadU8Bit(Dbk, FactoryConfigBank,  32 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_TPS_BUZ_CLIDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  32 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_TPS_BUZ_CLIImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  32 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_TPS_BUZ_CLIDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  32 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_tmp_app_cle -- Group FactoryConfigBank, Byte  33  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_tmp_app_cle
  #error "Do not define EEP_tmp_app_cle, because this is a lexem used for concatenation."
#endif
#define cDATEEP_tmp_app_clePositionByte      33 
#define cDATEEP_tmp_app_clePositionBit        0xFF
#define mDATPeeResetU8BitEEP_tmp_app_cle()     \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  33 ,  7 ,  8 , 4, Delayed)
#define mDATReadU8BitEEP_tmp_app_cleDefaultValueDefault() ((U8)4)
#define mDATReadU8BitEEP_tmp_app_cleDefault() \
      mDATPeeReadU8Bit(Dbk, FactoryConfigBank,  33 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_tmp_app_cleDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  33 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_tmp_app_cleImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  33 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_tmp_app_cleDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  33 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_timeout_app_cle -- Group FactoryConfigBank, Byte  34  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_timeout_app_cle
  #error "Do not define EEP_timeout_app_cle, because this is a lexem used for concatenation."
#endif
#define cDATEEP_timeout_app_clePositionByte      34 
#define cDATEEP_timeout_app_clePositionBit        0xFF
#define mDATPeeResetU8BitEEP_timeout_app_cle()     \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  34 ,  7 ,  8 , 5, Delayed)
#define mDATReadU8BitEEP_timeout_app_cleDefaultValueDefault() ((U8)5)
#define mDATReadU8BitEEP_timeout_app_cleDefault() \
      mDATPeeReadU8Bit(Dbk, FactoryConfigBank,  34 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_timeout_app_cleDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  34 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_timeout_app_cleImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  34 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_timeout_app_cleDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  34 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_TimeOutMERA -- Group FactoryConfigBank, Byte  35  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_TimeOutMERA
  #error "Do not define EEP_TimeOutMERA, because this is a lexem used for concatenation."
#endif
#define cDATEEP_TimeOutMERAPositionByte      35 
#define cDATEEP_TimeOutMERAPositionBit        0xFF
#define mDATPeeResetU8BitEEP_TimeOutMERA()     \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  35 ,  7 ,  8 , 100, Delayed)
#define mDATReadU8BitEEP_TimeOutMERADefaultValueDefault() ((U8)100)
#define mDATReadU8BitEEP_TimeOutMERADefault() \
      mDATPeeReadU8Bit(Dbk, FactoryConfigBank,  35 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_TimeOutMERADelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  35 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_TimeOutMERAImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  35 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_TimeOutMERADefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  35 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_PerimeterAlarmState -- Group FactoryConfigBank, Byte  36  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_PerimeterAlarmState
  #error "Do not define EEP_PerimeterAlarmState, because this is a lexem used for concatenation."
#endif
#define cDATEEP_PerimeterAlarmStatePositionByte      36 
#define cDATEEP_PerimeterAlarmStatePositionBit        0xFF
#define mDATPeeResetU8BitEEP_PerimeterAlarmState()     \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  36 ,  7 ,  8 , 0, Delayed)
#define mDATReadU8BitEEP_PerimeterAlarmStateDefaultValueDefault() ((U8)0)
#define mDATReadU8BitEEP_PerimeterAlarmStateDefault() \
      mDATPeeReadU8Bit(Dbk, FactoryConfigBank,  36 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_PerimeterAlarmStateDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  36 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_PerimeterAlarmStateImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  36 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_PerimeterAlarmStateDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  36 ,  7 ,  8 , (ValueToWrite), Immediate)

// Spare_FactoryConfigBank -- Group FactoryConfigBank, Byte  37  , Bit (MSB)  7  , SizeInBit  8 
#ifdef Spare_FactoryConfigBank
  #error "Do not define Spare_FactoryConfigBank, because this is a lexem used for concatenation."
#endif
#define cDATSpare_FactoryConfigBankPositionByte      37 
#define cDATSpare_FactoryConfigBankPositionBit        0xFF
#define mDATPeeResetU8BitSpare_FactoryConfigBank()     \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  37 ,  7 ,  8 , 0, Delayed)
#define mDATReadU8BitSpare_FactoryConfigBankDefaultValueDefault() ((U8)0)
#define mDATReadU8BitSpare_FactoryConfigBankDefault() \
      mDATPeeReadU8Bit(Dbk, FactoryConfigBank,  37 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitSpare_FactoryConfigBankDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  37 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitSpare_FactoryConfigBankImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  37 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitSpare_FactoryConfigBankDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, FactoryConfigBank,  37 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_VehicleIdentifierNumber -- Group VINBank, Byte  0  , Bit (MSB)  7  , SizeInBit  152 
#ifdef EEP_VehicleIdentifierNumber
  #error "Do not define EEP_VehicleIdentifierNumber, because this is a lexem used for concatenation."
#endif
#define mDATPeeResetEEP_VehicleIdentifierNumber()     \
{                                                     \
   mDATPeeWriteTable(U8Bit,Sbk,VINBank,  0 ,  0, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,VINBank,  0 ,  1, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,VINBank,  0 ,  2, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,VINBank,  0 ,  3, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,VINBank,  0 ,  4, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,VINBank,  0 ,  5, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,VINBank,  0 ,  6, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,VINBank,  0 ,  7, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,VINBank,  0 ,  8, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,VINBank,  0 ,  9, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,VINBank,  0 ,  10, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,VINBank,  0 ,  11, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,VINBank,  0 ,  12, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,VINBank,  0 ,  13, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,VINBank,  0 ,  14, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,VINBank,  0 ,  15, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,VINBank,  0 ,  16, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,VINBank,  0 ,  17, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Sbk,VINBank,  0 ,  18, 0, Delayed) \
}
#define mDATReadTableU1BitEEP_VehicleIdentifierNumberDefaultValueDefault( Index ) \
      mDATPeeReadDefaultTable(U1Bit,Sbk, VINBank,  0 , Index, Delayed)

#define mDATReadTableU8BitEEP_VehicleIdentifierNumberDefault( Index ) \
      mDATPeeReadTable(U8Bit,Sbk, VINBank,  0 , Index, Delayed)
#define mDATWriteTableU8BitEEP_VehicleIdentifierNumberDelayed( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Sbk, VINBank,  0 , Index, (ValueToWrite), Delayed)
#define mDATWriteTableU8BitEEP_VehicleIdentifierNumberImmediate( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Sbk, VINBank,  0 , Index, (ValueToWrite), Immediate)
#define mDATWriteTableU8BitEEP_VehicleIdentifierNumberDefault( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Sbk, VINBank,  0 , Index, (ValueToWrite), Immediate)

// EEP_KeyIdentifier -- Group StaticImmoBank, Byte  0  , Bit (MSB)  7  , SizeInBit  128 
#ifdef EEP_KeyIdentifier
  #error "Do not define EEP_KeyIdentifier, because this is a lexem used for concatenation."
#endif
#define mDATPeeResetEEP_KeyIdentifier()     \
{                                                     \
   mDATPeeWriteTable(U32Bit,Dbk,StaticImmoBank,  0 ,  0, 0, Delayed) \
   mDATPeeWriteTable(U32Bit,Dbk,StaticImmoBank,  0 ,  1, 0, Delayed) \
   mDATPeeWriteTable(U32Bit,Dbk,StaticImmoBank,  0 ,  2, 0, Delayed) \
   mDATPeeWriteTable(U32Bit,Dbk,StaticImmoBank,  0 ,  3, 0, Delayed) \
}
#define mDATReadTableU1BitEEP_KeyIdentifierDefaultValueDefault( Index ) \
      mDATPeeReadDefaultTable(U1Bit,Dbk, StaticImmoBank,  0 , Index, Delayed)

#define mDATReadTableU32BitEEP_KeyIdentifierDefault( Index ) \
      mDATPeeReadTable(U32Bit,Dbk, StaticImmoBank,  0 , Index, Delayed)
#define mDATWriteTableU32BitEEP_KeyIdentifierDelayed( Index, ValueToWrite ) \
      mDATPeeWriteTable(U32Bit,Dbk, StaticImmoBank,  0 , Index, (ValueToWrite), Delayed)
#define mDATWriteTableU32BitEEP_KeyIdentifierImmediate( Index, ValueToWrite ) \
      mDATPeeWriteTable(U32Bit,Dbk, StaticImmoBank,  0 , Index, (ValueToWrite), Immediate)
#define mDATWriteTableU32BitEEP_KeyIdentifierDefault( Index, ValueToWrite ) \
      mDATPeeWriteTable(U32Bit,Dbk, StaticImmoBank,  0 , Index, (ValueToWrite), Immediate)

// EEP_PwdTag -- Group StaticImmoBank, Byte  16  , Bit (MSB)  7  , SizeInBit  128 
#ifdef EEP_PwdTag
  #error "Do not define EEP_PwdTag, because this is a lexem used for concatenation."
#endif
#define mDATPeeResetEEP_PwdTag()     \
{                                                     \
   mDATPeeWriteTable(U32Bit,Dbk,StaticImmoBank,  16 ,  0, 0, Delayed) \
   mDATPeeWriteTable(U32Bit,Dbk,StaticImmoBank,  16 ,  1, 0, Delayed) \
   mDATPeeWriteTable(U32Bit,Dbk,StaticImmoBank,  16 ,  2, 0, Delayed) \
   mDATPeeWriteTable(U32Bit,Dbk,StaticImmoBank,  16 ,  3, 0, Delayed) \
}
#define mDATReadTableU1BitEEP_PwdTagDefaultValueDefault( Index ) \
      mDATPeeReadDefaultTable(U1Bit,Dbk, StaticImmoBank,  16 , Index, Delayed)

#define mDATReadTableU32BitEEP_PwdTagDefault( Index ) \
      mDATPeeReadTable(U32Bit,Dbk, StaticImmoBank,  16 , Index, Delayed)
#define mDATWriteTableU32BitEEP_PwdTagDelayed( Index, ValueToWrite ) \
      mDATPeeWriteTable(U32Bit,Dbk, StaticImmoBank,  16 , Index, (ValueToWrite), Delayed)
#define mDATWriteTableU32BitEEP_PwdTagImmediate( Index, ValueToWrite ) \
      mDATPeeWriteTable(U32Bit,Dbk, StaticImmoBank,  16 , Index, (ValueToWrite), Immediate)
#define mDATWriteTableU32BitEEP_PwdTagDefault( Index, ValueToWrite ) \
      mDATPeeWriteTable(U32Bit,Dbk, StaticImmoBank,  16 , Index, (ValueToWrite), Immediate)

// EEP_AfterSalesCode -- Group StaticImmoBank, Byte  32  , Bit (MSB)  7  , SizeInBit  48 
#ifdef EEP_AfterSalesCode
  #error "Do not define EEP_AfterSalesCode, because this is a lexem used for concatenation."
#endif
#define mDATPeeResetEEP_AfterSalesCode()     \
{                                                     \
   mDATPeeWriteTable(U8Bit,Dbk,StaticImmoBank,  32 ,  0, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Dbk,StaticImmoBank,  32 ,  1, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Dbk,StaticImmoBank,  32 ,  2, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Dbk,StaticImmoBank,  32 ,  3, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Dbk,StaticImmoBank,  32 ,  4, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Dbk,StaticImmoBank,  32 ,  5, 0, Delayed) \
}
#define mDATReadTableU1BitEEP_AfterSalesCodeDefaultValueDefault( Index ) \
      mDATPeeReadDefaultTable(U1Bit,Dbk, StaticImmoBank,  32 , Index, Delayed)

#define mDATReadTableU8BitEEP_AfterSalesCodeDefault( Index ) \
      mDATPeeReadTable(U8Bit,Dbk, StaticImmoBank,  32 , Index, Delayed)
#define mDATWriteTableU8BitEEP_AfterSalesCodeDelayed( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Dbk, StaticImmoBank,  32 , Index, (ValueToWrite), Delayed)
#define mDATWriteTableU8BitEEP_AfterSalesCodeImmediate( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Dbk, StaticImmoBank,  32 , Index, (ValueToWrite), Immediate)
#define mDATWriteTableU8BitEEP_AfterSalesCodeDefault( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Dbk, StaticImmoBank,  32 , Index, (ValueToWrite), Immediate)

// EEP_ImmoSecretKey -- Group StaticImmoBank, Byte  38  , Bit (MSB)  7  , SizeInBit  48 
#ifdef EEP_ImmoSecretKey
  #error "Do not define EEP_ImmoSecretKey, because this is a lexem used for concatenation."
#endif
#define mDATPeeResetEEP_ImmoSecretKey()     \
{                                                     \
   mDATPeeWriteTable(U8Bit,Dbk,StaticImmoBank,  38 ,  0, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Dbk,StaticImmoBank,  38 ,  1, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Dbk,StaticImmoBank,  38 ,  2, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Dbk,StaticImmoBank,  38 ,  3, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Dbk,StaticImmoBank,  38 ,  4, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Dbk,StaticImmoBank,  38 ,  5, 0, Delayed) \
}
#define mDATReadTableU1BitEEP_ImmoSecretKeyDefaultValueDefault( Index ) \
      mDATPeeReadDefaultTable(U1Bit,Dbk, StaticImmoBank,  38 , Index, Delayed)

#define mDATReadTableU8BitEEP_ImmoSecretKeyDefault( Index ) \
      mDATPeeReadTable(U8Bit,Dbk, StaticImmoBank,  38 , Index, Delayed)
#define mDATWriteTableU8BitEEP_ImmoSecretKeyDelayed( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Dbk, StaticImmoBank,  38 , Index, (ValueToWrite), Delayed)
#define mDATWriteTableU8BitEEP_ImmoSecretKeyImmediate( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Dbk, StaticImmoBank,  38 , Index, (ValueToWrite), Immediate)
#define mDATWriteTableU8BitEEP_ImmoSecretKeyDefault( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Dbk, StaticImmoBank,  38 , Index, (ValueToWrite), Immediate)

// EEP_RemoteSecretKey1 -- Group StaticImmoBank, Byte  44  , Bit (MSB)  7  , SizeInBit  48 
#ifdef EEP_RemoteSecretKey1
  #error "Do not define EEP_RemoteSecretKey1, because this is a lexem used for concatenation."
#endif
#define mDATPeeResetEEP_RemoteSecretKey1()     \
{                                                     \
   mDATPeeWriteTable(U8Bit,Dbk,StaticImmoBank,  44 ,  0, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Dbk,StaticImmoBank,  44 ,  1, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Dbk,StaticImmoBank,  44 ,  2, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Dbk,StaticImmoBank,  44 ,  3, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Dbk,StaticImmoBank,  44 ,  4, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Dbk,StaticImmoBank,  44 ,  5, 0, Delayed) \
}
#define mDATReadTableU1BitEEP_RemoteSecretKey1DefaultValueDefault( Index ) \
      mDATPeeReadDefaultTable(U1Bit,Dbk, StaticImmoBank,  44 , Index, Delayed)

#define mDATReadTableU8BitEEP_RemoteSecretKey1Default( Index ) \
      mDATPeeReadTable(U8Bit,Dbk, StaticImmoBank,  44 , Index, Delayed)
#define mDATWriteTableU8BitEEP_RemoteSecretKey1Delayed( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Dbk, StaticImmoBank,  44 , Index, (ValueToWrite), Delayed)
#define mDATWriteTableU8BitEEP_RemoteSecretKey1Immediate( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Dbk, StaticImmoBank,  44 , Index, (ValueToWrite), Immediate)
#define mDATWriteTableU8BitEEP_RemoteSecretKey1Default( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Dbk, StaticImmoBank,  44 , Index, (ValueToWrite), Immediate)

// EEP_RemoteSecretKey2 -- Group StaticImmoBank, Byte  50  , Bit (MSB)  7  , SizeInBit  48 
#ifdef EEP_RemoteSecretKey2
  #error "Do not define EEP_RemoteSecretKey2, because this is a lexem used for concatenation."
#endif
#define mDATPeeResetEEP_RemoteSecretKey2()     \
{                                                     \
   mDATPeeWriteTable(U8Bit,Dbk,StaticImmoBank,  50 ,  0, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Dbk,StaticImmoBank,  50 ,  1, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Dbk,StaticImmoBank,  50 ,  2, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Dbk,StaticImmoBank,  50 ,  3, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Dbk,StaticImmoBank,  50 ,  4, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Dbk,StaticImmoBank,  50 ,  5, 0, Delayed) \
}
#define mDATReadTableU1BitEEP_RemoteSecretKey2DefaultValueDefault( Index ) \
      mDATPeeReadDefaultTable(U1Bit,Dbk, StaticImmoBank,  50 , Index, Delayed)

#define mDATReadTableU8BitEEP_RemoteSecretKey2Default( Index ) \
      mDATPeeReadTable(U8Bit,Dbk, StaticImmoBank,  50 , Index, Delayed)
#define mDATWriteTableU8BitEEP_RemoteSecretKey2Delayed( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Dbk, StaticImmoBank,  50 , Index, (ValueToWrite), Delayed)
#define mDATWriteTableU8BitEEP_RemoteSecretKey2Immediate( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Dbk, StaticImmoBank,  50 , Index, (ValueToWrite), Immediate)
#define mDATWriteTableU8BitEEP_RemoteSecretKey2Default( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Dbk, StaticImmoBank,  50 , Index, (ValueToWrite), Immediate)

// EEP_RemoteSecretKey3 -- Group StaticImmoBank, Byte  56  , Bit (MSB)  7  , SizeInBit  48 
#ifdef EEP_RemoteSecretKey3
  #error "Do not define EEP_RemoteSecretKey3, because this is a lexem used for concatenation."
#endif
#define mDATPeeResetEEP_RemoteSecretKey3()     \
{                                                     \
   mDATPeeWriteTable(U8Bit,Dbk,StaticImmoBank,  56 ,  0, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Dbk,StaticImmoBank,  56 ,  1, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Dbk,StaticImmoBank,  56 ,  2, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Dbk,StaticImmoBank,  56 ,  3, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Dbk,StaticImmoBank,  56 ,  4, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Dbk,StaticImmoBank,  56 ,  5, 0, Delayed) \
}
#define mDATReadTableU1BitEEP_RemoteSecretKey3DefaultValueDefault( Index ) \
      mDATPeeReadDefaultTable(U1Bit,Dbk, StaticImmoBank,  56 , Index, Delayed)

#define mDATReadTableU8BitEEP_RemoteSecretKey3Default( Index ) \
      mDATPeeReadTable(U8Bit,Dbk, StaticImmoBank,  56 , Index, Delayed)
#define mDATWriteTableU8BitEEP_RemoteSecretKey3Delayed( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Dbk, StaticImmoBank,  56 , Index, (ValueToWrite), Delayed)
#define mDATWriteTableU8BitEEP_RemoteSecretKey3Immediate( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Dbk, StaticImmoBank,  56 , Index, (ValueToWrite), Immediate)
#define mDATWriteTableU8BitEEP_RemoteSecretKey3Default( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Dbk, StaticImmoBank,  56 , Index, (ValueToWrite), Immediate)

// EEP_RemoteSecretKey4 -- Group StaticImmoBank, Byte  62  , Bit (MSB)  7  , SizeInBit  48 
#ifdef EEP_RemoteSecretKey4
  #error "Do not define EEP_RemoteSecretKey4, because this is a lexem used for concatenation."
#endif
#define mDATPeeResetEEP_RemoteSecretKey4()     \
{                                                     \
   mDATPeeWriteTable(U8Bit,Dbk,StaticImmoBank,  62 ,  0, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Dbk,StaticImmoBank,  62 ,  1, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Dbk,StaticImmoBank,  62 ,  2, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Dbk,StaticImmoBank,  62 ,  3, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Dbk,StaticImmoBank,  62 ,  4, 0, Delayed) \
   mDATPeeWriteTable(U8Bit,Dbk,StaticImmoBank,  62 ,  5, 0, Delayed) \
}
#define mDATReadTableU1BitEEP_RemoteSecretKey4DefaultValueDefault( Index ) \
      mDATPeeReadDefaultTable(U1Bit,Dbk, StaticImmoBank,  62 , Index, Delayed)

#define mDATReadTableU8BitEEP_RemoteSecretKey4Default( Index ) \
      mDATPeeReadTable(U8Bit,Dbk, StaticImmoBank,  62 , Index, Delayed)
#define mDATWriteTableU8BitEEP_RemoteSecretKey4Delayed( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Dbk, StaticImmoBank,  62 , Index, (ValueToWrite), Delayed)
#define mDATWriteTableU8BitEEP_RemoteSecretKey4Immediate( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Dbk, StaticImmoBank,  62 , Index, (ValueToWrite), Immediate)
#define mDATWriteTableU8BitEEP_RemoteSecretKey4Default( Index, ValueToWrite ) \
      mDATPeeWriteTable(U8Bit,Dbk, StaticImmoBank,  62 , Index, (ValueToWrite), Immediate)

// EEP_VerlogSKey -- Group StaticImmoBank, Byte  68  , Bit (MSB)  7  , SizeInBit  16 
#ifdef EEP_VerlogSKey
  #error "Do not define EEP_VerlogSKey, because this is a lexem used for concatenation."
#endif
#define cDATEEP_VerlogSKeyPositionByte      68 
#define cDATEEP_VerlogSKeyPositionBit        0xFF
#define mDATPeeResetU16BitEEP_VerlogSKey()     \
      mDATPeeWriteU16Bit(Dbk, StaticImmoBank,  68 ,  7 ,  16 , 0, Delayed)
#define mDATReadU16BitEEP_VerlogSKeyDefaultValueDefault() ((U16)0)
#define mDATReadU16BitEEP_VerlogSKeyDefault() \
      mDATPeeReadU16Bit(Dbk, StaticImmoBank,  68 ,  7 ,  16 , Delayed)
#define mDATWriteU16BitEEP_VerlogSKeyDelayed(ValueToWrite) \
      mDATPeeWriteU16Bit(Dbk, StaticImmoBank,  68 ,  7 ,  16 , (ValueToWrite), Delayed)
#define mDATWriteU16BitEEP_VerlogSKeyImmediate(ValueToWrite) \
      mDATPeeWriteU16Bit(Dbk, StaticImmoBank,  68 ,  7 ,  16 , (ValueToWrite), Immediate)
#define mDATWriteU16BitEEP_VerlogSKeyDefault(ValueToWrite) \
      mDATPeeWriteU16Bit(Dbk, StaticImmoBank,  68 ,  7 ,  16 , (ValueToWrite), Immediate)

// EEP_NbKeysStd433MhzLearnt -- Group StaticImmoBank, Byte  70  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_NbKeysStd433MhzLearnt
  #error "Do not define EEP_NbKeysStd433MhzLearnt, because this is a lexem used for concatenation."
#endif
#define cDATEEP_NbKeysStd433MhzLearntPositionByte      70 
#define cDATEEP_NbKeysStd433MhzLearntPositionBit        0xFF
#define mDATPeeResetU8BitEEP_NbKeysStd433MhzLearnt()     \
      mDATPeeWriteU8Bit(Dbk, StaticImmoBank,  70 ,  7 ,  8 , 0, Delayed)
#define mDATReadU8BitEEP_NbKeysStd433MhzLearntDefaultValueDefault() ((U8)0)
#define mDATReadU8BitEEP_NbKeysStd433MhzLearntDefault() \
      mDATPeeReadU8Bit(Dbk, StaticImmoBank,  70 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_NbKeysStd433MhzLearntDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, StaticImmoBank,  70 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_NbKeysStd433MhzLearntImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, StaticImmoBank,  70 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_NbKeysStd433MhzLearntDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, StaticImmoBank,  70 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_NbKeysStd315MhzLearnt -- Group StaticImmoBank, Byte  71  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_NbKeysStd315MhzLearnt
  #error "Do not define EEP_NbKeysStd315MhzLearnt, because this is a lexem used for concatenation."
#endif
#define cDATEEP_NbKeysStd315MhzLearntPositionByte      71 
#define cDATEEP_NbKeysStd315MhzLearntPositionBit        0xFF
#define mDATPeeResetU8BitEEP_NbKeysStd315MhzLearnt()     \
      mDATPeeWriteU8Bit(Dbk, StaticImmoBank,  71 ,  7 ,  8 , 0, Delayed)
#define mDATReadU8BitEEP_NbKeysStd315MhzLearntDefaultValueDefault() ((U8)0)
#define mDATReadU8BitEEP_NbKeysStd315MhzLearntDefault() \
      mDATPeeReadU8Bit(Dbk, StaticImmoBank,  71 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_NbKeysStd315MhzLearntDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, StaticImmoBank,  71 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_NbKeysStd315MhzLearntImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, StaticImmoBank,  71 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_NbKeysStd315MhzLearntDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, StaticImmoBank,  71 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_NbKeysStd315MhzLowPowerLearnt -- Group StaticImmoBank, Byte  72  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_NbKeysStd315MhzLowPowerLearnt
  #error "Do not define EEP_NbKeysStd315MhzLowPowerLearnt, because this is a lexem used for concatenation."
#endif
#define cDATEEP_NbKeysStd315MhzLowPowerLearntPositionByte      72 
#define cDATEEP_NbKeysStd315MhzLowPowerLearntPositionBit        0xFF
#define mDATPeeResetU8BitEEP_NbKeysStd315MhzLowPowerLearnt()     \
      mDATPeeWriteU8Bit(Dbk, StaticImmoBank,  72 ,  7 ,  8 , 0, Delayed)
#define mDATReadU8BitEEP_NbKeysStd315MhzLowPowerLearntDefaultValueDefault() ((U8)0)
#define mDATReadU8BitEEP_NbKeysStd315MhzLowPowerLearntDefault() \
      mDATPeeReadU8Bit(Dbk, StaticImmoBank,  72 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_NbKeysStd315MhzLowPowerLearntDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, StaticImmoBank,  72 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_NbKeysStd315MhzLowPowerLearntImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, StaticImmoBank,  72 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_NbKeysStd315MhzLowPowerLearntDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, StaticImmoBank,  72 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_NbKeysLearnt -- Group StaticImmoBank, Byte  73  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_NbKeysLearnt
  #error "Do not define EEP_NbKeysLearnt, because this is a lexem used for concatenation."
#endif
#define cDATEEP_NbKeysLearntPositionByte      73 
#define cDATEEP_NbKeysLearntPositionBit        0xFF
#define mDATPeeResetU8BitEEP_NbKeysLearnt()     \
      mDATPeeWriteU8Bit(Dbk, StaticImmoBank,  73 ,  7 ,  8 , 0, Delayed)
#define mDATReadU8BitEEP_NbKeysLearntDefaultValueDefault() ((U8)0)
#define mDATReadU8BitEEP_NbKeysLearntDefault() \
      mDATPeeReadU8Bit(Dbk, StaticImmoBank,  73 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_NbKeysLearntDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, StaticImmoBank,  73 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_NbKeysLearntImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, StaticImmoBank,  73 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_NbKeysLearntDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, StaticImmoBank,  73 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_AfsEraseIgnitionCnt -- Group StaticImmoBank, Byte  74  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_AfsEraseIgnitionCnt
  #error "Do not define EEP_AfsEraseIgnitionCnt, because this is a lexem used for concatenation."
#endif
#define cDATEEP_AfsEraseIgnitionCntPositionByte      74 
#define cDATEEP_AfsEraseIgnitionCntPositionBit        0xFF
#define mDATPeeResetU8BitEEP_AfsEraseIgnitionCnt()     \
      mDATPeeWriteU8Bit(Dbk, StaticImmoBank,  74 ,  7 ,  8 , 0, Delayed)
#define mDATReadU8BitEEP_AfsEraseIgnitionCntDefaultValueDefault() ((U8)0)
#define mDATReadU8BitEEP_AfsEraseIgnitionCntDefault() \
      mDATPeeReadU8Bit(Dbk, StaticImmoBank,  74 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_AfsEraseIgnitionCntDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, StaticImmoBank,  74 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_AfsEraseIgnitionCntImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, StaticImmoBank,  74 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_AfsEraseIgnitionCntDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, StaticImmoBank,  74 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEP_BCMBlank -- Group StaticImmoBank, Byte  75  , Bit (MSB)  0  , SizeInBit  1 
#ifdef EEP_BCMBlank
  #error "Do not define EEP_BCMBlank, because this is a lexem used for concatenation."
#endif
#define cDATEEP_BCMBlankPositionByte      75 
#define cDATEEP_BCMBlankPositionBit       0 
#define mDATPeeResetU1BitEEP_BCMBlank()     \
      mDATPeeWriteU1Bit(Dbk, StaticImmoBank,  75 ,  0 , 1, Delayed)
#define mDATReadU1BitEEP_BCMBlankDefaultValueDefault() ((BOOL)1)
#define mDATReadU1BitEEP_BCMBlankDefault() \
      mDATPeeReadU1Bit(Dbk, StaticImmoBank,  75 ,  0 , Delayed)
#define mDATWriteU1BitEEP_BCMBlankDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, StaticImmoBank,  75 ,  0  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_BCMBlankImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, StaticImmoBank,  75 ,  0  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_BCMBlankDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, StaticImmoBank,  75 ,  0  , (ValueToWrite), Immediate)

// EEP_CodeAFSAvailable -- Group StaticImmoBank, Byte  75  , Bit (MSB)  1  , SizeInBit  1 
#ifdef EEP_CodeAFSAvailable
  #error "Do not define EEP_CodeAFSAvailable, because this is a lexem used for concatenation."
#endif
#define cDATEEP_CodeAFSAvailablePositionByte      75 
#define cDATEEP_CodeAFSAvailablePositionBit       1 
#define mDATPeeResetU1BitEEP_CodeAFSAvailable()     \
      mDATPeeWriteU1Bit(Dbk, StaticImmoBank,  75 ,  1 , 0, Delayed)
#define mDATReadU1BitEEP_CodeAFSAvailableDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_CodeAFSAvailableDefault() \
      mDATPeeReadU1Bit(Dbk, StaticImmoBank,  75 ,  1 , Delayed)
#define mDATWriteU1BitEEP_CodeAFSAvailableDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, StaticImmoBank,  75 ,  1  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_CodeAFSAvailableImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, StaticImmoBank,  75 ,  1  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_CodeAFSAvailableDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, StaticImmoBank,  75 ,  1  , (ValueToWrite), Immediate)

// EEP_ECMLearningModeFinished -- Group StaticImmoBank, Byte  75  , Bit (MSB)  2  , SizeInBit  1 
#ifdef EEP_ECMLearningModeFinished
  #error "Do not define EEP_ECMLearningModeFinished, because this is a lexem used for concatenation."
#endif
#define cDATEEP_ECMLearningModeFinishedPositionByte      75 
#define cDATEEP_ECMLearningModeFinishedPositionBit       2 
#define mDATPeeResetU1BitEEP_ECMLearningModeFinished()     \
      mDATPeeWriteU1Bit(Dbk, StaticImmoBank,  75 ,  2 , 0, Delayed)
#define mDATReadU1BitEEP_ECMLearningModeFinishedDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_ECMLearningModeFinishedDefault() \
      mDATPeeReadU1Bit(Dbk, StaticImmoBank,  75 ,  2 , Delayed)
#define mDATWriteU1BitEEP_ECMLearningModeFinishedDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, StaticImmoBank,  75 ,  2  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_ECMLearningModeFinishedImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, StaticImmoBank,  75 ,  2  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_ECMLearningModeFinishedDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, StaticImmoBank,  75 ,  2  , (ValueToWrite), Immediate)

// EEP_EraseAFSCodeRequest -- Group StaticImmoBank, Byte  75  , Bit (MSB)  3  , SizeInBit  1 
#ifdef EEP_EraseAFSCodeRequest
  #error "Do not define EEP_EraseAFSCodeRequest, because this is a lexem used for concatenation."
#endif
#define cDATEEP_EraseAFSCodeRequestPositionByte      75 
#define cDATEEP_EraseAFSCodeRequestPositionBit       3 
#define mDATPeeResetU1BitEEP_EraseAFSCodeRequest()     \
      mDATPeeWriteU1Bit(Dbk, StaticImmoBank,  75 ,  3 , 0, Delayed)
#define mDATReadU1BitEEP_EraseAFSCodeRequestDefaultValueDefault() ((BOOL)0)
#define mDATReadU1BitEEP_EraseAFSCodeRequestDefault() \
      mDATPeeReadU1Bit(Dbk, StaticImmoBank,  75 ,  3 , Delayed)
#define mDATWriteU1BitEEP_EraseAFSCodeRequestDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, StaticImmoBank,  75 ,  3  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_EraseAFSCodeRequestImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, StaticImmoBank,  75 ,  3  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_EraseAFSCodeRequestDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, StaticImmoBank,  75 ,  3  , (ValueToWrite), Immediate)

// EEP_AppCleNonEffect -- Group StaticImmoBank, Byte  75  , Bit (MSB)  4  , SizeInBit  1 
#ifdef EEP_AppCleNonEffect
  #error "Do not define EEP_AppCleNonEffect, because this is a lexem used for concatenation."
#endif
#define cDATEEP_AppCleNonEffectPositionByte      75 
#define cDATEEP_AppCleNonEffectPositionBit       4 
#define mDATPeeResetU1BitEEP_AppCleNonEffect()     \
      mDATPeeWriteU1Bit(Dbk, StaticImmoBank,  75 ,  4 , 1, Delayed)
#define mDATReadU1BitEEP_AppCleNonEffectDefaultValueDefault() ((BOOL)1)
#define mDATReadU1BitEEP_AppCleNonEffectDefault() \
      mDATPeeReadU1Bit(Dbk, StaticImmoBank,  75 ,  4 , Delayed)
#define mDATWriteU1BitEEP_AppCleNonEffectDelayed(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, StaticImmoBank,  75 ,  4  , (ValueToWrite), Delayed)
#define mDATWriteU1BitEEP_AppCleNonEffectImmediate(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, StaticImmoBank,  75 ,  4  , (ValueToWrite), Immediate)
#define mDATWriteU1BitEEP_AppCleNonEffectDefault(ValueToWrite) \
      mDATPeeWriteU1Bit(Dbk, StaticImmoBank,  75 ,  4  , (ValueToWrite), Immediate)

// EEP_SI28Bits -- Group DynamicImmoDataBank, Byte  0  , Bit (MSB)  7  , SizeInBit  128 
#ifdef EEP_SI28Bits
  #error "Do not define EEP_SI28Bits, because this is a lexem used for concatenation."
#endif
#define mDATPeeResetEEP_SI28Bits()     \
{                                                     \
   mDATPeeWriteTable(U32Bit,Dbk,DynamicImmoDataBank,  0 ,  0, 0, Delayed) \
   mDATPeeWriteTable(U32Bit,Dbk,DynamicImmoDataBank,  0 ,  1, 0, Delayed) \
   mDATPeeWriteTable(U32Bit,Dbk,DynamicImmoDataBank,  0 ,  2, 0, Delayed) \
   mDATPeeWriteTable(U32Bit,Dbk,DynamicImmoDataBank,  0 ,  3, 0, Delayed) \
}
#define mDATReadTableU1BitEEP_SI28BitsDefaultValueDefault( Index ) \
      mDATPeeReadDefaultTable(U1Bit,Dbk, DynamicImmoDataBank,  0 , Index, Delayed)

#define mDATReadTableU32BitEEP_SI28BitsDefault( Index ) \
      mDATPeeReadTable(U32Bit,Dbk, DynamicImmoDataBank,  0 , Index, Delayed)
#define mDATWriteTableU32BitEEP_SI28BitsDelayed( Index, ValueToWrite ) \
      mDATPeeWriteTable(U32Bit,Dbk, DynamicImmoDataBank,  0 , Index, (ValueToWrite), Delayed)
#define mDATWriteTableU32BitEEP_SI28BitsImmediate( Index, ValueToWrite ) \
      mDATPeeWriteTable(U32Bit,Dbk, DynamicImmoDataBank,  0 , Index, (ValueToWrite), Immediate)
#define mDATWriteTableU32BitEEP_SI28BitsDefault( Index, ValueToWrite ) \
      mDATPeeWriteTable(U32Bit,Dbk, DynamicImmoDataBank,  0 , Index, (ValueToWrite), Immediate)

// EEP_InitialResynchroValue -- Group DynamicImmoDataBank, Byte  16  , Bit (MSB)  7  , SizeInBit  128 
#ifdef EEP_InitialResynchroValue
  #error "Do not define EEP_InitialResynchroValue, because this is a lexem used for concatenation."
#endif
#define mDATPeeResetEEP_InitialResynchroValue()     \
{                                                     \
   mDATPeeWriteTable(U32Bit,Dbk,DynamicImmoDataBank,  16 ,  0, 0, Delayed) \
   mDATPeeWriteTable(U32Bit,Dbk,DynamicImmoDataBank,  16 ,  1, 0, Delayed) \
   mDATPeeWriteTable(U32Bit,Dbk,DynamicImmoDataBank,  16 ,  2, 0, Delayed) \
   mDATPeeWriteTable(U32Bit,Dbk,DynamicImmoDataBank,  16 ,  3, 0, Delayed) \
}
#define mDATReadTableU1BitEEP_InitialResynchroValueDefaultValueDefault( Index ) \
      mDATPeeReadDefaultTable(U1Bit,Dbk, DynamicImmoDataBank,  16 , Index, Delayed)

#define mDATReadTableU32BitEEP_InitialResynchroValueDefault( Index ) \
      mDATPeeReadTable(U32Bit,Dbk, DynamicImmoDataBank,  16 , Index, Delayed)
#define mDATWriteTableU32BitEEP_InitialResynchroValueDelayed( Index, ValueToWrite ) \
      mDATPeeWriteTable(U32Bit,Dbk, DynamicImmoDataBank,  16 , Index, (ValueToWrite), Delayed)
#define mDATWriteTableU32BitEEP_InitialResynchroValueImmediate( Index, ValueToWrite ) \
      mDATPeeWriteTable(U32Bit,Dbk, DynamicImmoDataBank,  16 , Index, (ValueToWrite), Immediate)
#define mDATWriteTableU32BitEEP_InitialResynchroValueDefault( Index, ValueToWrite ) \
      mDATPeeWriteTable(U32Bit,Dbk, DynamicImmoDataBank,  16 , Index, (ValueToWrite), Immediate)

// EEP_DefResynchroValueRead -- Group DynamicImmoDataBank, Byte  32  , Bit (MSB)  7  , SizeInBit  128 
#ifdef EEP_DefResynchroValueRead
  #error "Do not define EEP_DefResynchroValueRead, because this is a lexem used for concatenation."
#endif
#define mDATPeeResetEEP_DefResynchroValueRead()     \
{                                                     \
   mDATPeeWriteTable(U32Bit,Dbk,DynamicImmoDataBank,  32 ,  0, 0, Delayed) \
   mDATPeeWriteTable(U32Bit,Dbk,DynamicImmoDataBank,  32 ,  1, 0, Delayed) \
   mDATPeeWriteTable(U32Bit,Dbk,DynamicImmoDataBank,  32 ,  2, 0, Delayed) \
   mDATPeeWriteTable(U32Bit,Dbk,DynamicImmoDataBank,  32 ,  3, 0, Delayed) \
}
#define mDATReadTableU1BitEEP_DefResynchroValueReadDefaultValueDefault( Index ) \
      mDATPeeReadDefaultTable(U1Bit,Dbk, DynamicImmoDataBank,  32 , Index, Delayed)

#define mDATReadTableU32BitEEP_DefResynchroValueReadDefault( Index ) \
      mDATPeeReadTable(U32Bit,Dbk, DynamicImmoDataBank,  32 , Index, Delayed)
#define mDATWriteTableU32BitEEP_DefResynchroValueReadDelayed( Index, ValueToWrite ) \
      mDATPeeWriteTable(U32Bit,Dbk, DynamicImmoDataBank,  32 , Index, (ValueToWrite), Delayed)
#define mDATWriteTableU32BitEEP_DefResynchroValueReadImmediate( Index, ValueToWrite ) \
      mDATPeeWriteTable(U32Bit,Dbk, DynamicImmoDataBank,  32 , Index, (ValueToWrite), Immediate)
#define mDATWriteTableU32BitEEP_DefResynchroValueReadDefault( Index, ValueToWrite ) \
      mDATPeeWriteTable(U32Bit,Dbk, DynamicImmoDataBank,  32 , Index, (ValueToWrite), Immediate)

// EEP_DefResynchroValueWrite -- Group DynamicImmoDataBank, Byte  48  , Bit (MSB)  7  , SizeInBit  128 
#ifdef EEP_DefResynchroValueWrite
  #error "Do not define EEP_DefResynchroValueWrite, because this is a lexem used for concatenation."
#endif
#define mDATPeeResetEEP_DefResynchroValueWrite()     \
{                                                     \
   mDATPeeWriteTable(U32Bit,Dbk,DynamicImmoDataBank,  48 ,  0, 0, Delayed) \
   mDATPeeWriteTable(U32Bit,Dbk,DynamicImmoDataBank,  48 ,  1, 0, Delayed) \
   mDATPeeWriteTable(U32Bit,Dbk,DynamicImmoDataBank,  48 ,  2, 0, Delayed) \
   mDATPeeWriteTable(U32Bit,Dbk,DynamicImmoDataBank,  48 ,  3, 0, Delayed) \
}
#define mDATReadTableU1BitEEP_DefResynchroValueWriteDefaultValueDefault( Index ) \
      mDATPeeReadDefaultTable(U1Bit,Dbk, DynamicImmoDataBank,  48 , Index, Delayed)

#define mDATReadTableU32BitEEP_DefResynchroValueWriteDefault( Index ) \
      mDATPeeReadTable(U32Bit,Dbk, DynamicImmoDataBank,  48 , Index, Delayed)
#define mDATWriteTableU32BitEEP_DefResynchroValueWriteDelayed( Index, ValueToWrite ) \
      mDATPeeWriteTable(U32Bit,Dbk, DynamicImmoDataBank,  48 , Index, (ValueToWrite), Delayed)
#define mDATWriteTableU32BitEEP_DefResynchroValueWriteImmediate( Index, ValueToWrite ) \
      mDATPeeWriteTable(U32Bit,Dbk, DynamicImmoDataBank,  48 , Index, (ValueToWrite), Immediate)
#define mDATWriteTableU32BitEEP_DefResynchroValueWriteDefault( Index, ValueToWrite ) \
      mDATPeeWriteTable(U32Bit,Dbk, DynamicImmoDataBank,  48 , Index, (ValueToWrite), Immediate)

// EEP_ResynchroRequest -- Group DynamicImmoDataBank, Byte  64  , Bit (MSB)  7  , SizeInBit  8 
#ifdef EEP_ResynchroRequest
  #error "Do not define EEP_ResynchroRequest, because this is a lexem used for concatenation."
#endif
#define cDATEEP_ResynchroRequestPositionByte      64 
#define cDATEEP_ResynchroRequestPositionBit        0xFF
#define mDATPeeResetU8BitEEP_ResynchroRequest()     \
      mDATPeeWriteU8Bit(Dbk, DynamicImmoDataBank,  64 ,  7 ,  8 , 0, Delayed)
#define mDATReadU8BitEEP_ResynchroRequestDefaultValueDefault() ((U8)0)
#define mDATReadU8BitEEP_ResynchroRequestDefault() \
      mDATPeeReadU8Bit(Dbk, DynamicImmoDataBank,  64 ,  7 ,  8 , Delayed)
#define mDATWriteU8BitEEP_ResynchroRequestDelayed(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, DynamicImmoDataBank,  64 ,  7 ,  8 , (ValueToWrite), Delayed)
#define mDATWriteU8BitEEP_ResynchroRequestImmediate(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, DynamicImmoDataBank,  64 ,  7 ,  8 , (ValueToWrite), Immediate)
#define mDATWriteU8BitEEP_ResynchroRequestDefault(ValueToWrite) \
      mDATPeeWriteU8Bit(Dbk, DynamicImmoDataBank,  64 ,  7 ,  8 , (ValueToWrite), Immediate)

// EEPSparedArea -- Group SpareBank, Byte  0  , Bit (MSB)  7  , SizeInBit  16 
#ifdef EEPSparedArea
  #error "Do not define EEPSparedArea, because this is a lexem used for concatenation."
#endif
#define cDATEEPSparedAreaPositionByte      0 
#define cDATEEPSparedAreaPositionBit        0xFF
#define mDATPeeResetU16BitEEPSparedArea()     \
      mDATPeeWriteU16Bit(Sbk, SpareBank,  0 ,  7 ,  16 , 0, Delayed)
#define mDATReadU16BitEEPSparedAreaDefaultValueDefault() ((U16)0)
#define mDATReadU16BitEEPSparedAreaDefault() \
      mDATPeeReadU16Bit(Sbk, SpareBank,  0 ,  7 ,  16 , Delayed)
#define mDATWriteU16BitEEPSparedAreaDelayed(ValueToWrite) \
      mDATPeeWriteU16Bit(Sbk, SpareBank,  0 ,  7 ,  16 , (ValueToWrite), Delayed)
#define mDATWriteU16BitEEPSparedAreaImmediate(ValueToWrite) \
      mDATPeeWriteU16Bit(Sbk, SpareBank,  0 ,  7 ,  16 , (ValueToWrite), Immediate)
#define mDATWriteU16BitEEPSparedAreaDefault(ValueToWrite) \
      mDATPeeWriteU16Bit(Sbk, SpareBank,  0 ,  7 ,  16 , (ValueToWrite), Immediate)


//--------------------------------------------------------------------------
// Groups to define in the component DAT_Pee
//--------------------------------------------------------------------------

// mDATPeeReadTable(TypeDonnee, Strategy, Group, Byte, Bit, Index, TreatmentType)
// mDATPeeReadDefaultTable(TypeDonnee, Strategy, Group, Byte, Bit, Index)
// mDATPeeWriteTable(TypeDonnee, Strategy, Group, Byte, Bit, Index, ValueToWrite, TreatmentType)
// mDATPeeReadU8Bit(Strategy, Group, Byte, Bit, BitSize, TreatmentType)
// mDATPeeWriteU8Bit(Strategy, Group, Byte, Bit, BitSize, ValueToWrite, TreatmentType)
// mDATPeeReadU16Bit(Strategy, Group, Byte, Bit, BitSize, TreatmentType)
// mDATPeeWriteU16Bit(Strategy, Group, Byte, Bit, BitSize, ValueToWrite, TreatmentType)
// mDATPeeReadChamp8Bit(Strategy, Group, Byte, Bit, BitSize,TreatmentType)
// mDATPeeWriteChamp8Bit(Strategy, Group, Byte, Bit, BitSize, ValueToWrite, TreatmentType)

#endif    //  I_PEE_PARAM_H
