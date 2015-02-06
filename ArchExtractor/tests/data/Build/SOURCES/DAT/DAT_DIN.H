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

#ifndef I_DAT_Din_H
#define I_DAT_Din_H (1)

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//
// #include <system_file_name.h>
// #include "project_file_name.h"
//------------------------------------------------------------------------------
#include "deftypes.h"
#include "ldb.h"

#include "dat_Dinp.h"
#include "dat_Dinx.h"


#ifdef WAKE_BY_DIN_INTERRUPT
#ifndef WAKE_BY_DIN
#error 'Wake by Din interrupt capability must not be activate if wake by Din is not active'
#endif
#endif

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
#ifdef WAKE_BY_DIN
#define cDATDinSleepMode   ((tDATDinState)0UL)
#define cDATDinConfirmWakeUpMode ((tDATDinState)1UL)
#else
#define cDATDinStopMode   ((tDATDinState)3UL)
#endif
#define cDATDinNormalMode   ((tDATDinState)2UL)

    #define mDATDinDivideSup(N,D) (((N)+((D)-((U8)1UL)))/(D))
    #define mDATDinDivideSupNonType(N,D) (((N)+((D)-1UL))/(D))

#define cDATDinLastBitPosInSleepModeShifted ((U8) (cDATDinLastBitPosInSleepMode + ((U8)1UL)))
#define cDATDinLastBitPosInNominalModeShifted ((U8) (cDATDinLastBitPosInNominalMode + ((U8)1UL)))
#define cDATDinLastBitPosInNominalModeNonTypeShifted (cDATDinLastBitPosInNominalModeNonType + 1UL)

#if (defined(DATDIN_FAST_FILTER_X3)||defined(DATDIN_FAST_FILTER_X5))

#ifndef DATDIN_SAME_SLEEP_AND_NORMAL_INPUT
    #define cDATDinWordNbrToFilterInSleepMode  \
    ((U16)(mDATDinDivideSup(cDATDinLastBitPosInSleepModeShifted, (((U8)8UL)*cDATDinWordSize) )))

    #define cDATDinWordNbrToFilterInNormalModeNonType \
    mDATDinDivideSupNonType(cDATDinLastBitPosInNominalModeNonTypeShifted, 8UL*cDATDinWordSizeNonType)

    #define cDATDinWordNbrToFilterInNormalMode \
    ((U16)(mDATDinDivideSup(cDATDinLastBitPosInNominalModeShifted, (((U8)8UL)*cDATDinWordSize) )))

    // The fast filter algorithm use word.
    // So the buffer size must be a mutiple of word size
    #define cDATDinBufferSize ((U16)( (cDATDinWordNbrToFilterInNormalMode) * cDATDinWordSize ))
    #define cDATDinBufferUseSize ((U16)(mDATDinDivideSup(cDATDinLastBitPosInNominalModeShifted, ((U8)8UL) )))

    //Fast algo State machine initialization size when entering into normal mode
    #define cDATDinNormalModeInitByteSize ((U16)(cDATDinWordNbrToFilterInNormalMode - cDATDinLastBytePosInSleepMode-((U16)1UL)))
#else
    #define cDATDinWordNbrToFilter  \
    mDATDinDivideSup(cDATDinLastBitPosInSleepModeShifted, (((U8)8UL)*cDATDinWordSize))

    #define cDATDinWordNbrToFilterNonType  \
    mDATDinDivideSupNonType(cDATDinLastBitPosInNominalModeNonTypeShifted, 8UL*cDATDinWordSizeNonType)

    #define cDATDinWordNbrToFilterInNormalModeNonType cDATDinWordNbrToFilterNonType
    #define cDATDinWordNbrToFilterInNormalMode cDATDinWordNbrToFilter

    #define cDATDinBufferSize ((U16)( (cDATDinWordNbrToFilter) * cDATDinWordSize ))
    #define cDATDinBufferUseSize ((U16)(mDATDinDivideSup( cDATDinLastBitPosInSleepModeShifted, ((U8)8UL) )))
#endif

#else //(defined(DATDIN_FAST_FILTER_X3)||defined(DATDIN_FAST_FILTER_X5))

    #define cDATDinBufferSize ((U16)(mDATDinDivideSup( cDATDinLastBitPosInNominalModeShifted,((U8)8UL))))
    #define cDATDinBufferUseSize cDATDinBufferSize

#ifndef DATDIN_SAME_SLEEP_AND_NORMAL_INPUT
    //Tab initialization size when entering into normal mode (one input = 1 byte)
    #define cDATDinNormalModeInitByteSize ((U16)(cDATDinLastBitPosInNominalMode - cDATDinLastBitPosInSleepMode))
#endif

#endif


//------------------------------------------------------------------------------
// Exported Macros
//
// #define LAYCmpMacroName(...)   (MacroDefinition)
//------------------------------------------------------------------------------
#define mDATDinGetRaisingEdge(ByteNbr,BitNbr)  \
      ((BOOL)((mDATDinGetFilteredValue( (ByteNbr),(BitNbr)) == cTrue)\
               && (mDATDinGetStateChange( (ByteNbr),(BitNbr)) == cTrue)))

#define mDATDinGetFallingEdge(ByteNbr,BitNbr)  \
      ((BOOL)((mDATDinGetFilteredValue((ByteNbr),(BitNbr)) == cFalse)\
               && (mDATDinGetStateChange((ByteNbr),(BitNbr)) == cTrue)))

#define mDATDinGetStateChange(ByteNbr,BitNbr)  \
      ((BOOL)((DATDinInputBuffers.StateChange[ByteNbr] & (((U8)1UL) << (BitNbr)))!=0))

#define mDATDinGetFilteredValue(ByteNbr,BitNbr)  \
      ((BOOL)((DATDinInputBuffers.Filtered[ByteNbr] & (((U8)1UL) << (BitNbr)))!=0))

#define mDATDinGetNonFilteredValue(ByteNbr,BitNbr) \
      ((BOOL)((DATDinInputBuffers.NonFiltered[ByteNbr] & (((U8)1UL) << (BitNbr)))!=0))

#define mDATDinGetNonFilteredBuffer() (DATDinInputBuffers.NonFiltered)

#define mDATDinSetNonFilteredValue(ByteNbr,BitNbr,BitValue)            \
    {                                                                  \
        if( BitValue )                                                 \
        {                                                              \
            DATDinInputBuffers.NonFiltered[ByteNbr] |= (((U8)1UL)<<(BitNbr));  \
        }                                                              \
        else                                                           \
        {                                                              \
            DATDinInputBuffers.NonFiltered[ByteNbr] &= ~(((U8)1UL)<<(BitNbr)); \
        }                                                              \
    }
    
#define mDATDinSetFilteredValue(ByteNbr,BitNbr,BitValue)            \
    {                                                               \
        if( BitValue )                                              \
        {                                                           \
            DATDinInputBuffers.Filtered[ByteNbr] |= (((U8)1UL)<<(BitNbr));  \
        }                                                           \
        else                                                        \
        {                                                           \
            DATDinInputBuffers.Filtered[ByteNbr] &= ~(((U8)1UL)<<(BitNbr)); \
        }                                                           \
    }

//------------------------------------------------------------------------------
// Exported type
//
// typedef Expression tLAYCmpTypeName;
//------------------------------------------------------------------------------
#ifdef cDATDinWordSizeNonType
    #if cDATDinWordSizeNonType == 1UL 
        typedef U8 tDATDinWord;
    #else
        #if cDATDinWordSizeNonType == 2UL 
            typedef U16 tDATDinWord;
        #else
            #if cDATDinWordSizeNonType == 4UL 
                typedef U32 tDATDinWord;
            #else
                #error "Incorrect word size"
            #endif
        #endif
    #endif
#endif

typedef U8 tDATDinState;
typedef U8 tDATDin_ByteIndex;
typedef U8 tDATDin_BitIndex;

typedef struct
{
    U8 Filtered[cDATDinBufferSize];
    U8 NonFiltered[cDATDinBufferSize];
    U8 StateChange[cDATDinBufferSize];
} tDATDinLogicalInputBuffers;

//------------------------------------------------------------------------------
// Exported data
//
// extern  tType   u8LAYCmpVariableName;
// extern  tType*  ps32LAYCmpVariableName; 
//------------------------------------------------------------------------------
extern MEM_FAST tDATDinLogicalInputBuffers DATDinInputBuffers;

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
extern void   DATDinCallBackCtrl(tCtrl Ctrl);
extern void   DATDinCallBackEndCtrl(tCtrl Ctrl, tStatus Statut);
extern void   DATDinLeaveStartingStepState(void);
extern void   DATDinEnterActiveState(void);
extern void   DATDinLeaveActiveState(void);

extern void   DATDinCallBackRxWithoutAddr(tStatus Statut);
extern void   DATDinReadTask(void);
extern MEM_TYPE void   DATDinInit(const U8* pBuffer);

extern void   DATDinMaintainActiveSleepState(void);

//call back defined outside
extern void   DATPinSelection  (void);
extern void   DATPinStateChange(void);

#endif  /* I_DAT_Din_H */

