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
// Component:    The component is responsible for the generation of sequences 
//               for controlling an audio producing device to generate sounds 
//               and melodies, that are described in the parameterization file 
//               DAT_BUZx.H
// -----------------------------------------------------------------------------
// $Date:   Feb 24 2009 12:25:42  $
// $Archive:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_BUZ/DAT_BUZp.h-arc  $
// $Revision:   1.0  $
// -----------------------------------------------------------------------------
// $Log:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_BUZ/DAT_BUZp.h-arc  $
// 
//    Rev 1.0   Feb 24 2009 12:25:42   amarinm1
// Initial revision.
//******************************************************************************
#endif

#ifndef I_DAT_BUZp_H
#define I_DAT_BUZp_H

//------------------------------------------------------------------------------
// Included files to resolve specific definitions in this file
//------------------------------------------------------------------------------

// This is an example:
// Reduce to minimum the inclusions!!!
// #include <system_file_name.h>
// #include "project_file_name.h"

//------------------------------------------------------------------------------
// Constant data
//------------------------------------------------------------------------------

// This is an example:
// #define cu16LAYCmpConstantName   ((U16)ConstantValue)


//------------------------------------------------------------------------------
// Exported type
//------------------------------------------------------------------------------

// This is an example:
// typedef Expression tLAYCmpTypeName;


// buzzer melodies parameterization - buzzer IDs
typedef enum tSOUND_enum
{
    eBUZZER_Silence       = 0,
    eBUZZER_FlasherClick  = 1,
    eBUZZER_FlasherClack  = 2,
    eBUZZER_LockWithSpeed = 3,
    eBUZZER_SeatBelt      = 4,
    eBUZZER_OverSpeed     = 5,
    eBUZZER_ExtLights     = 6,

    cNumberOfMelodies     = 7
}tSOUND;


//------------------------------------------------------------------------------
// Exported data
//------------------------------------------------------------------------------

// This is an example:
// Reduce to minimum the usage of extern data members!!!
// extern  tType   LAYCmpVariableName;
// extern  tType*  pLAYCmpVariableName;
// extern  U8      u8LAYCmpVariableName;
// extern  U16*    pu16LAYCmpVariableName;

//------------------------------------------------------------------------------
// Constant exported data
//------------------------------------------------------------------------------

// This is an example:
// Reduce to minimum the usage of extern constant data members!!!
// extern const tType  cLAYCmpConstantName;
// extern const U32    cu32LAYCmpConstantName;

//------------------------------------------------------------------------------
// Exported Macros
//------------------------------------------------------------------------------

// This is an example:
// #define LAYCmpMacroName(...)   (MacroDefinition)

//------------------------------------------------------------------------------
// Exported functions
//------------------------------------------------------------------------------

// This is an example:
// tType LAYCmpFunctionName( tTypeArgument1 ArgumentName1, ... );

#endif   // I_DAT_BUZp_H
