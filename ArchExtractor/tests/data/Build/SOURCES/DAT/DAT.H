/*============================================================================
  Project ......................... STANDARD
  Component ....................... dat.h
  File revision.................... 
  Last modification date .......... 
  -------------------------------------------------------------------------
  Copyright ... This software is JCI property. Duplication or
                disclosure is prohibited without JCI written permission
  ------------------------------------------------------------------------- 
    
  - This file should only contain data useful to the programmer to use
    this component
  - Component exported macros, constants and types are defined in this file
  - Component exported variables and functions are declared in this file 
    with the "extern" key word
  
  -------------------------------------------------------------------------
  dat.h file review :
  
      See PVCS Base
 

  ==========================================================================*/
#ifndef I_DAT_H
#define I_DAT_H (1)

/*-------------------------------------------------------------------------
  Included files to resolve specific definitions in this file

  #include <system_file_name.h>
  #include "project_file_name.h"
  -------------------------------------------------------------------------*/
#include "deftypes.h"
#include "DATparam.h"

/////////////////////////////////////////////////////////////////////////////
// French API -> English API translation
/////////////////////////////////////////////////////////////////////////////

//////////////////////////   CONSUMPTION    /////////////////////////////////

#define mDATLire(DataType, DataName, ProcessingType)			\
    mDATRead(DataType, DataName, ProcessingType)

#define mDATLireBuffer(DataName, Index, ProcessingType)		\
	mDATReadBuffer(DataName, Index, ProcessingType)

#define mDATLireTableau(DataType, TableName, Index, ProcessingType) \
	mDATReadTable(DataType, TableName, Index, ProcessingType)

#define mDATLireStruct(DataType, DataName, pDestination, ProcessingType)  \
  mDATReadStruct(DataType, DataName, pDestination, ProcessingType)

//////////////////////////    PRODUCTION    /////////////////////////////////

#define mDATEcrire(DataType, DataName, Value, ProcessingType)	\
  mDATWrite(DataType, DataName, Value, ProcessingType)	

#define mDATEcrireBuffer(DataName, Index, Value, ProcessingType)  \
	mDATWriteBuffer(DataName, Index, Value, ProcessingType) 

#define mDATEcrireTableau(DataType, TableName, Index, Value, ProcessingType)\
	mDATWriteTable(DataType, TableName, Index, Value, ProcessingType)

#define mDATEcrireStruct(DataType, DataName, pSource, ProcessingType)  \
  mDATWriteStruct(DataType, DataName, pSource, ProcessingType) 

//////////////////////////    CONTROL    /////////////////////////////////

#define mDATControler(Object,Control)\
    mDATControl(Object,Control) 

//////////////////////////    PROCESSING TYPES ///////////////////////////

// "Default" processing type
// The responsability to choose the processing type is left
// to the relevant DAT component.
#define Defaut Default

// "Immediate" processing type
#define Immediat Immediate

// "Delayed" processing type
#define Differe Delayed 


/*-------------------------------------------------------------------------
  Constant data

  #define cCMPConstantName   ((tType) ConstantValue)
  -------------------------------------------------------------------------*/

// The following constants define the "DataType" parameter used in mDATRead
// and MDatWrite macro.
// By concatenation, they'll form new macro. As a consequence, those constants
// don't have to respect classical programmation rules.

// unsigned 1 bit data
#ifdef	U1Bit
  #error "You must not define U1Bit. This lexem is concatenated with mDATRead and mDATWrite macro."
#endif // U1Bit

// unsigned 8 bit data
#ifdef	U8Bit
  #error "You must not define U8Bit. This lexem is concatenated with mDATRead and mDATWrite macro."
#endif // U8Bit

// signed 8 bit data
#ifdef	S8Bit
  #error "You must not define S8Bit. This lexem is concatenated with mDATRead and mDATWrite macro."
#endif // S8Bit

// unsigned 16 bit data
#ifdef	U16Bit
  #error "You must not define U16Bit. This lexem is concatenated with mDATRead and mDATWrite macro."
#endif // U16Bit

// signed 16 bit data
#ifdef	S16Bit
  #error "You must not define S16Bit. This lexem is concatenated with mDATRead and mDATWrite macro."
#endif // S16Bit

// unsigned 32 bit data
#ifdef	U32Bit
  #error "You must not define U32Bit. This lexem is concatenated with mDATRead and mDATWrite macro."
#endif // U32Bit

// signed 32 bit data
#ifdef	S32Bit
  #error "You must not define S32Bit. This lexem is concatenated with mDATRead and mDATWrite macro."
#endif // S32Bit


// The following constants define the "processingType" parameter used in mDATRead
// and MDatWrite macro.

#ifdef	Default
  #error "You must not define Default. This lexem is concatenated with mDATRead and mDATWrite macro."
#endif // Default

#ifdef	Immediate   
  #error "You must not define Immediate. This lexem is concatenated with mDATRead and mDATWrite macro."
#endif // Immediat

#ifdef	Delayed	   
  #error "You must not define Delayed. This lexem is concatenated with mDATRead and mDATWrite macro."
#endif // Differe

/*-------------------------------------------------------------------------
  Exported Macro

  #define mCMPMacroName   (MacroDefinition)
  -------------------------------------------------------------------------*/ 

//////////////////////////   CONSOMMATION    /////////////////////////////////
#define mDATRead(DataType, DataName, TreatmentType)	\
        mDATRead2(DataType, DataName, TreatmentType)

#define mDATRead2(DataType, DataName, TreatmentType)	\
	mDATRead ## DataType ## DataName ## TreatmentType()

#define mDATReadBuffer(DataName, Index, TreatmentType)	\
        mDATReadBuffer2(DataName, Index, TreatmentType)

#define mDATReadBuffer2(DataName, Index, TreatmentType)	\
	mDATReadBuffer ## DataName ## TreatmentType( Index )

#define mDATReadTable(DataType, ArrayName, Index, TreatmentType)	\
        mDATReadTable2(DataType, ArrayName, Index, TreatmentType)
#define mDATReadTable2(DataType, ArrayName, Index, TreatmentType)	\
	mDATReadTable ## DataType ## ArrayName ## TreatmentType( Index )

#define mDATReadStruct(DataType, DataName, pDestination, TreatmentType)	\
        mDATReadStruct2(DataType, DataName, pDestination, TreatmentType)
#define mDATReadStruct2(DataType, DataName, pDestination, TreatmentType)	\
	mDATReadStruct ## DataType ## DataName ## TreatmentType( pDestination )

//////////////////////////    PRODUCTION    /////////////////////////////////
#define mDATWrite(DataType, DataName, ValueToWrite, TreatmentType)	\
        mDATWrite2(DataType, DataName, ValueToWrite, TreatmentType)

#define mDATWrite2(DataType, DataName, ValueToWrite, TreatmentType)	\
	mDATWrite ## DataType ## DataName ## TreatmentType( ValueToWrite )

#define mDATWriteBuffer(DataName, Index, ValueToWrite, TreatmentType)	\
        mDATWriteBuffer2(DataName, Index, ValueToWrite, TreatmentType)

#define mDATWriteBuffer2(DataName, Index, ValueToWrite, TreatmentType)	\
	mDATWriteBuffer ## DataName ## TreatmentType( Index, ValueToWrite )

#define mDATWriteTable(DataType, ArrayName, Index, ValueToWrite, TreatmentType)	\
        mDATWriteTable2(DataType, ArrayName, Index, ValueToWrite, TreatmentType)

#define mDATWriteTable2(DataType, ArrayName, Index, ValueToWrite, TreatmentType)	\
	mDATWriteTable ## DataType ## ArrayName ## TreatmentType( Index, ValueToWrite )

#define mDATWriteStruct(DataType, DataName, pSource, TreatmentType)	\
        mDATWriteStruct2(DataType, DataName, pSource, TreatmentType)

#define mDATWriteStruct2(DataType, DataName, pSource, TreatmentType)	\
	mDATWriteStruct ## DataType ## DataName ## TreatmentType( pSource )

//////////////////////////    CONTROLE    /////////////////////////////////

#define mDATControl(Objet,Controle)\
    mDATControl##Objet(Controle)  

/*-------------------------------------------------------------------------
  Exported type

  struct  sCMPStructureName { ... };
  union   uCMPUnionName { ... };
  enum    eCMPEnumerationName { ... };
  typedef Expression tCMPTypeName;

  -------------------------------------------------------------------------*/

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

/*-------------------------------------------------------------------------
  End of includes non re entry
  -------------------------------------------------------------------------*/
#endif   /* I_DAT_H */

