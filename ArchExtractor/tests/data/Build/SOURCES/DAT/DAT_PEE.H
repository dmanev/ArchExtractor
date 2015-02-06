/*============================================================================
  Project ......................... COMMON
  Component ....................... DAT_PEE
  File revision.................... :   1.3  $
  Last modification date .......... $Modtime:   Feb 26 2010 13:13:28  $
  -------------------------------------------------------------------------
  Copyright ... This software is JCI property. Duplication or
                disclosure is prohibited without JCI written permission
  ------------------------------------------------------------------------- 
    
  - This file should only contain data useful to the programmer to use
    this comp                   CONFIG_LIN_Slave_M16C_SCC2\$(SIMU_EXE)
onent
  - Component exported macros, constants and types are defined in this file
  - Component exported variables and functions are declared in this file 
    with the "extern" keyword
  
  -------------------------------------------------------------------------
  DAT_PEE.h file review :
  
    :   P:/STANDARD/AEH/STK/PVCS/archives/STK/CMP/SOURCES/DAT/EEP/DAT_PEE/Dat_pee.h-arc  $
 * 
 *    Rev 1.3   Aug 05 2003 13:31:18   abarbae
 * PON URD42 BODY_SW 239 :  Ajouter un outil de selection de configuration au Starter-Kit .
 * 
 *    Rev 1.2   Jun 12 2003 17:46:22   aguillg
 * Can Integration
 * 
 *    Rev 1.1   Jun 12 2003 09:59:40   aguillg
 * EEP Integration
 * 
 *    Rev 1.0   Apr 08 2003 12:19:00   aguillg
 * Initial revision.


  ==========================================================================*/

#ifndef I_DAT_PEE_H
#define I_DAT_PEE_H (1)


/*-------------------------------------------------------------------------
  Included files

  #include <system_file_name.h>
  #include "project_file_name.h"
  --------------------------------------------------------------------------*/
#include "deftypes.h"

#include "dat_peex.h"
#include "dat_peep.h"

#include "dat_eep.h"

#include "dat_dea.h"
#include "dat_sbk.h"
#include "dat_dbk.h"

/*-------------------------------------------------------------------------
  Constant data

  #define cCMPConstantName   ((tType) ConstantValue)
  -------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
  Exported Macros

  #define mCMPMacroName   (MacroDefinition)
  -------------------------------------------------------------------------*/ 

/*-----------------------------------------------------------------------------
          Macro redefinition for only Renault or Nissan managment
  ---------------------------------------------------------------------------*/
#undef mDATReadU1BitEEPRenaultNissanDefault
#define mDATReadU1BitEEPRenaultNissanDefault() (cFalse)

/*-----------------------------------------------------------------------------
                        Macros used by DAT_PEEx.H
  ---------------------------------------------------------------------------*/

/* These macros use macros of second level */

#define mDATPeeReadBuffer( Strategy, GroupName, Byte , Index, Access )\
        mDATPeeReadTable( U8Bit, Strategy, GroupName, Byte, Index, Access )

#define mDATPeeWriteBuffer( Strategy, GroupName, Byte , Index, Val, Access )\
        mDATPeeWriteTable( U8Bit, Strategy, GroupName, Byte, Index, Val, Access )

#define mDATPeeReadTable( TypeDonnee, Strategy, GroupName, Byte, Index, Access )\
        mDATPeeReadTable##TypeDonnee##Access( Strategy, GroupName, Byte , Index )

#define mDATPeeWriteTable( TypeDonnee, Strategy, GroupName, Byte, Index, Val, Access )\
        mDATPeeWriteTable##TypeDonnee##Access( Strategy, GroupName, Byte , Index, Val )


#define mGetU8Ptr( Strategy,GroupName,Byte ) \
        (& (((U8 *) &DAT##Strategy##Mirrors.##GroupName)[Byte]))


/* Unsigned types */

#define mDATPeeWriteU32Bit( Strategy, GroupName, Byte , Bit, BitSize, Val, Access ) \
    mDATPeeWriteU32Bit##Access( Strategy, GroupName, Byte , Bit, BitSize, Val)
#define mDATPeeReadU32Bit( Strategy, GroupName, Byte , Bit, BitSize, Access )   \
    ( mDATPeeReadU32Bit##Access( Strategy, GroupName, Byte , Bit, BitSize))

#define mDATPeeWriteU16Bit( Strategy, GroupName, Byte , Bit, BitSize, Val, Access ) \
    mDATPeeWriteU16Bit##Access( Strategy, GroupName, Byte , Bit, BitSize, Val)
#define mDATPeeReadU16Bit( Strategy, GroupName, Byte , Bit, BitSize, Access )   \
    ( mDATPeeReadU16Bit##Access( Strategy, GroupName, Byte , Bit, BitSize))

#define mDATPeeWriteU8Bit( Strategy, GroupName, Byte , Bit, BitSize, Val, Access )  \
    mDATPeeWriteU8Bit##Access( Strategy, GroupName, Byte , Bit, BitSize, Val)
#define mDATPeeReadU8Bit( Strategy, GroupName, Byte , Bit, BitSize, Access )    \
    ((U8) mDATPeeReadU8Bit##Access( Strategy, GroupName, Byte , Bit, BitSize ))

#define mDATPeeWriteU1Bit( Strategy, GroupName, Byte , Bit, Val, Access )             \
    mDATPeeWriteU1Bit##Access( Strategy, GroupName, Byte , Bit, Val)
#define mDATPeeReadU1Bit( Strategy, GroupName, Byte , Bit, Access )               \
    (mDATPeeReadU1Bit##Access( Strategy, GroupName, Byte , Bit))


/* Signed types */

#define mDATPeeWriteS8Bit( Strategy, GroupName, Byte , Bit, BitSize, Val, Access )  \
    mDATPeeWriteU8Bit##Access( Strategy, GroupName, Byte , Bit, BitSize, ((U8)Val))
#define mDATPeeReadS8Bit( Strategy, GroupName, Byte , Bit, BitSize, Access )    \
    ((S8) mDATPeeReadU8Bit##Access( Strategy, GroupName, Byte , Bit, BitSize ))

#define mDATPeeWriteS16Bit( Strategy, GroupName, Byte , Bit, BitSize, Val, Access ) \
    mDATPeeWriteU16Bit( Strategy, GroupName, Byte , Bit, BitSize, ((U16)Val), Access )
#define mDATPeeReadS16Bit( Strategy, GroupName, Byte , Bit, BitSize, Access )   \
    ((S16) mDATPeeReadU16Bit( Strategy, GroupName, Byte , Bit, BitSize, Access ))

#define mDATPeeWriteS32Bit( Strategy, GroupName, Byte , Bit, BitSize, Val, Access ) \
    mDATPeeWriteU32Bit( Strategy, GroupName, Byte , Bit, BitSize, ((U32)Val), Access )
#define mDATPeeReadS32Bit( Strategy, GroupName, Byte , Bit, BitSize, Access )   \
    ((S32) mDATPeeReadU32Bit( Strategy, GroupName, Byte , Bit, BitSize, Access ))

/*-----------------------------------------------------------------------------
                            Macros of second level
  ---------------------------------------------------------------------------*/

/* These macros use macros of third level */

/* Read / Write U1Bit */

#define mDATPeeWriteU1BitDelayed( Strategy, GroupName, Byte , Bit, Val)  \
    {                                                           \
        if( Val )                                               \
        {                                                       \
            *(mGetU8Ptr( Strategy, GroupName,Byte)) |= (U8)(1<<(Bit));    \
        }                                                       \
        else                                                    \
        {                                                       \
            *(mGetU8Ptr( Strategy, GroupName,Byte)) &= (U8)(((U16)(~(U16)(1<<(Bit)))& 0x00FF));   \
        }                                                       \
    }

#define mDATPeeWriteU1BitImmediate( Strategy, GroupName, Byte , Bit, Val)   \
    {                                                                       \
        if( mDATPeeReadU1BitDelayed( Strategy, GroupName,Byte,Bit) != Val ) \
        {                                                                   \
          if( Val )                                                         \
          {                                                                 \
              *(mGetU8Ptr( Strategy, GroupName,Byte)) |= ((U8)(1<<(Bit)) ); \
          }                                                                 \
          else                                                              \
          {                                                                 \
              *(mGetU8Ptr( Strategy, GroupName,Byte)) &= ((U8)(((U16)(~(U16)(1<<(Bit)))& 0x00FF)));   \
          }                                                                 \
          mDATControl(Eep,UpDateEepGroup##GroupName);                       \
        }                                                                   \
    }

#define mDATPeeReadU1BitDelayed( Strategy, GroupName, Byte , Bit)    \
   ((BOOL)( (*(mGetU8Ptr( Strategy, GroupName,Byte)) & ((U8)(1<<(Bit)))) != 0 ))


/* Read / Write U8Bit */

#define mDATPeeDec8( Bit, BitSize )   ((U8)((Bit)+1-(BitSize)))
#define mDATPeeMask8( Bit, BitSize )     ((U8)((1<<BitSize) -1))

#define mDATPeeWriteU8BitDelayed( Strategy, GroupName, Byte , Bit, BitSize, Val)        \
    {                                                                                   \
        /* Check the data don't overflow its max value */                               \
        /* On verifie que la donnee ne depasse pas sa valeur maxi */                    \
        if( ( (Val) & ~mDATPeeMask8( Bit, BitSize ) ) == 0 )                            \
        {                                                                               \
            /* In the frame, delete the data bits */                                    \
            /* Dans la trame, on efface les bits de la donnee */                        \
            (*(mGetU8Ptr( Strategy, GroupName,Byte))) = (U8)(                           \
                      (  (*(mGetU8Ptr( Strategy, GroupName,Byte))) &                    \
                           ((U8)((U16)(~(U16)(mDATPeeMask8(Bit,BitSize) << mDATPeeDec8(Bit,BitSize)))& 0x00FF))     \
                      )                                                                 \
            /* Set the data bits */                                                     \
            /* On postionne les bits de la donnee */                                    \
                      | (U8)((Val) << mDATPeeDec8( Bit, BitSize ))                      \
                                                             );                         \
        }                                                                               \
        else                                                                            \
        {                                                                               \
            /* incorrect value in Val: would affect also other bits */                  \
            mLIBassert(cFalse);                                                         \
        }                                                                               \
    }

   
#define mDATPeeWriteU8BitImmediate( Strategy, GroupName, Byte , Bit, BitSize, Val)    \
    {                                                                                 \
        if( mDATPeeReadU8BitDelayed( Strategy, GroupName,Byte,Bit,BitSize) != (Val) ) \
        {                                                                             \
          mDATPeeWriteU8BitDelayed( Strategy, GroupName, Byte , Bit, BitSize, Val);   \
          mDATControl(Eep,UpDateEepGroup##GroupName);                                 \
        }                                                                             \
    }

#define mDATPeeReadU8BitDelayed( Strategy, GroupName, Byte , Bit, BitSize) \
    ((U8)( ( *(mGetU8Ptr( Strategy, GroupName,Byte)) >>                    \
        mDATPeeDec8( Bit, BitSize )        ) &                             \
        mDATPeeMask8(Bit,BitSize)               ))


/* Read / Write U16Bit */

#define mDATPeeWriteU16BitDelayed( Strategy, GroupName, Byte , Bit, BitSize, Val)  \
          *((U16 *) mGetU8Ptr( Strategy, GroupName,Byte) )   = Val;

#define mDATPeeWriteU16BitImmediate( Strategy, GroupName, Byte , Bit, BitSize, Val)    \
    {                                                                                  \
        if( mDATPeeReadU16BitDelayed( Strategy, GroupName,Byte,Bit,BitSize) != (Val) ) \
        {                                                                              \
          mDATPeeWriteU16BitDelayed( Strategy, GroupName, Byte , Bit, BitSize, Val);   \
          mDATControl(Eep,UpDateEepGroup##GroupName);                                  \
        }                                                                              \
    }

#define mDATPeeReadU16BitDelayed( Strategy, GroupName, Byte , Bit, BitSize )       \
   ((U16)(*((U16 *) mGetU8Ptr( Strategy, GroupName,Byte) )))


/* Read / Write U32Bit */

#define mDATPeeWriteU32BitDelayed( Strategy, GroupName, Byte , Bit, BitSize, Val)                       \
        {                                                                                               \
           *((U16 *) mGetU8Ptr( Strategy, GroupName,Byte) )   = (U16)((Val) & 0x0000FFFF);              \
           *((U16 *) mGetU8Ptr( Strategy, GroupName,(Byte)+2) )   = (U16)(((Val) & 0xFFFF0000)>> 16) ;  \
        }

#define mDATPeeWriteU32BitImmediate( Strategy, GroupName, Byte , Bit, BitSize, Val)  \
    {                                                                                \
      if( mDATPeeReadU32BitDelayed( Strategy, GroupName,Byte,Bit,BitSize) != (Val) ) \
      {                                                                              \
        mDATPeeWriteU32BitDelayed( Strategy, GroupName, Byte , Bit, BitSize, Val);   \
        mDATControl(Eep,UpDateEepGroup##GroupName);                                  \
      }                                                                              \
    }

#define mDATPeeReadU32BitDelayed( Strategy, GroupName, Byte , Bit, BitSize )        \
  ( (U32) ((U32) (*((U16 *) mGetU8Ptr( Strategy, GroupName,Byte) )) +               \
               (U32) ( ((U32) (*((U16 *) mGetU8Ptr( Strategy, GroupName,(Byte)+2)))) << 16 )))


/* Read / Write Buffer */

#define mDATPeeWriteBufferDelayed( Strategy, GroupName, Byte , Index, Val )  \
    {                                                                        \
        *mGetU8Ptr( Strategy, GroupName,(Byte)+(Index)) = Val;               \
    }

#define mDATPeeWriteBufferImmediate( Strategy, GroupName, Byte , Index, Val )      \
    {                                                                              \
        if(mDATPeeReadBufferDelayed( Strategy, GroupName, Byte , Index ) != (Val)) \
        {                                                                          \
          mDATPeeWriteBufferDelayed( Strategy, GroupName, Byte , Index, Val );     \
          mDATControl(Eep,UpDateEepGroup##GroupName);                              \
        }                                                                          \
    }

#define mDATPeeReadBufferDelayed( Strategy, GroupName, Byte , Index )         \
    (*mGetU8Ptr( Strategy, GroupName,(Byte)+(Index)))


/* Read / Write Array Types */

#define mDATPeeWriteTableU8BitDelayed( Strategy, GroupName, Byte , Index, Val )  \
    {                                                                            \
    *mGetU8Ptr( Strategy, GroupName,(Byte)+(Index)) = Val;                       \
    }

#define mDATPeeWriteTableU8BitImmediate( Strategy, GroupName, Byte , Index, Val ) \
    {                                                                             \
      if(mDATPeeReadTableU8BitDelayed(Strategy, GroupName, Byte, Index) != (Val)) \
      {                                                                           \
        mDATPeeWriteTableU8BitDelayed( Strategy, GroupName, Byte , Index, Val );  \
        mDATControl(Eep,UpDateEepGroup##GroupName);                               \
      }                                                                           \
    }

#define mDATPeeWriteTableS8BitDelayed( Strategy, GroupName, Byte , Index, Val )  \
    {                                                                            \
      * ((S8 *) mGetU8Ptr( Strategy, GroupName,(Byte)+(Index))) = Val;           \
    }

#define mDATPeeWriteTableS8BitImmediate( Strategy, GroupName, Byte , Index, Val ) \
    {                                                                             \
      if(mDATPeeReadTableS8BitDelayed(Strategy, GroupName, Byte, Index) != (Val)) \
      {                                                                           \
        mDATPeeWriteTableS8BitDelayed( Strategy, GroupName, Byte , Index, Val );  \
        mDATControl(Eep,UpDateEepGroup##GroupName);                               \
      }                                                                           \
    }

#define mDATPeeWriteTableU16BitDelayed( Strategy, GroupName, Byte , Index, Val )  \
    {                                                                             \
    * ((U16 *) mGetU8Ptr( Strategy, GroupName,(Byte)+((Index)*2))) = Val;         \
    }

#define mDATPeeWriteTableU16BitImmediate( Strategy, GroupName, Byte , Index, Val ) \
    {                                                                              \
      if(mDATPeeReadTableU16BitDelayed(Strategy, GroupName, Byte, Index) != (Val)) \
      {                                                                            \
        mDATPeeWriteTableU16BitDelayed( Strategy, GroupName, Byte , Index, Val );  \
        mDATControl(Eep,UpDateEepGroup##GroupName);                                \
      }                                                                            \
    }

#define mDATPeeWriteTableS16BitDelayed( Strategy, GroupName, Byte , Index, Val )  \
    {                                                                             \
       * ((S16 *) mGetU8Ptr( Strategy, GroupName,(Byte)+((Index)*2))) = Val;      \
    }

#define mDATPeeWriteTableS16BitImmediate( Strategy, GroupName, Byte , Index, Val ) \
    {                                                                             \
      if(mDATPeeReadTableS16BitDelayed(Strategy, GroupName, Byte, Index) != (Val))  \
      {                                                                           \
        mDATPeeWriteTableS16BitDelayed( Strategy, GroupName, Byte , Index, Val ); \
        mDATControl(Eep,UpDateEepGroup##GroupName);                               \
      }                                                                           \
    }

#define mDATPeeWriteTableU32BitDelayed( Strategy, GroupName, Byte , Index, Val )  \
    {                                                                             \
       *((U16 *) mGetU8Ptr( Strategy, GroupName,(Byte)+((Index)*4)) )   = (U16)((Val) & 0x0000FFFF);\
       *((U16 *) mGetU8Ptr( Strategy, GroupName,(Byte)+((Index)*4)+2) ) = (U16)(((Val) & 0xFFFF0000)>> 16) ;\
    }

#define mDATPeeWriteTableU32BitImmediate( Strategy, GroupName, Byte , Index, Val ) \
    {                                                                              \
      if(mDATPeeReadTableU32BitDelayed(Strategy, GroupName, Byte, Index) != (Val)) \
      {                                                                            \
        mDATPeeWriteTableU32BitDelayed( Strategy, GroupName, Byte , Index, Val );  \
        mDATControl(Eep,UpDateEepGroup##GroupName);                                \
      }                                                                            \
    }

#define mDATPeeWriteTableS32BitDelayed( Strategy, GroupName, Byte , Index, Val )  \
    {                                                               \
       *((S16 *) mGetU8Ptr( Strategy, GroupName,(Byte)+((Index)*4)) )   = (S16)((Val) & 0x0000FFFF);\
       *((S16 *) mGetU8Ptr( Strategy, GroupName,(Byte)+((Index)*4)+2) ) = (S16)(((Val) & 0xFFFF0000)>> 16) ;\
    }

#define mDATPeeWriteTableS32BitImmediate( Strategy, GroupName, Byte , Index, Val ) \
    {                                                                              \
      if(mDATPeeReadTableS32BitDelayed(Strategy, GroupName, Byte, Index) != (Val)) \
      {                                                                            \
        mDATPeeWriteTableS32BitDelayed( Strategy, GroupName, Byte , Index, Val );  \
        mDATControl(Eep,UpDateEepGroup##GroupName);                                \
      }                                                                            \
    }

#define mDATPeeReadTableU8BitDelayed( Strategy, GroupName, Byte , Index )  \
    (*mGetU8Ptr( Strategy, GroupName,(Byte)+(Index)))

#define mDATPeeReadTableS8BitDelayed( Strategy, GroupName, Byte , Index )  \
    (* ((S8 *) mGetU8Ptr( Strategy, GroupName,(Byte)+(Index))))

#define mDATPeeReadTableU16BitDelayed( Strategy, GroupName, Byte , Index )  \
    (* ((U16 *)mGetU8Ptr( Strategy, GroupName,(Byte)+((Index)*2))))

#define mDATPeeReadTableS16BitDelayed( Strategy, GroupName, Byte , Index )  \
    (* ((S16 *) mGetU8Ptr( Strategy, GroupName,(Byte)+((Index)*2))))

#define mDATPeeReadTableU32BitDelayed( Strategy, GroupName, Byte , Index )  \
    ( (U32) ((U32)(*((U16 *) mGetU8Ptr( Strategy, GroupName,(Byte)+((Index)*4) ) )) + \
               (U32)( ((U32) (*((U16 *) mGetU8Ptr( Strategy, GroupName,(Byte)+((Index)*4)+2)))) << 16 )))

#define mDATPeeReadTableS32BitDelayed( Strategy, GroupName, Byte , Index )  \
    ( (S32) mDATPeeReadTableU32BitDelayed( Strategy, GroupName, Byte , Index ) )

#define mDATReadU1BitIsEepProcessingDefault()  DATEepIsProcessing()

/*-------------------------------------------------------------------------
  Exported type

  struct  sCMPStructureName { ... };
  union   uCMPUnionName { ... };
  enum    eCMPEnumerationName { ... };
  typedef Expression tCMPTypeName;

  -------------------------------------------------------------------------*/
extern BOOL DATPeeCompNOk;
extern BOOL DATEepromCheckingIsDone;
extern U16  DATPeeBytePosition;
extern U8   DATPeeBuffer[4];

/*-------------------------------------------------------------------------
  Exported data

  extern  tType   CMPVariableName;
  extern  tType*  pCMPVariableName; 
  -------------------------------------------------------------------------*/ 

/*-------------------------------------------------------------------------
  Constant exported data

  extern const tType  CMPVariableName;
  -------------------------------------------------------------------------*/ 

/*-------------------------------------------------------------------------
  Exported functions

  extern tReturnType CMPFunctionName(tTypeArgument1 ArgumentName1, ... );
  -------------------------------------------------------------------------*/ 
extern void DATPeeInit(void);
extern void DATPeeStartReadingEEP(void);
BOOL DATPeeIsReadFinished(void);
extern void DATPeeNormalizeParameters (void);

#endif   /* I_DAT_PEE_H */
