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
//               and melodies, that are described in this file.
// -----------------------------------------------------------------------------
// $Date:   Jul 31 2009 12:31:32  $
// $Archive::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_BUZ/DAT_BUZx.h-arc  $
// $Revision:   1.1  $
// -----------------------------------------------------------------------------
// $Log:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_BUZ/DAT_BUZx.h-arc  $
// 
//    Rev 1.1   Jul 31 2009 12:31:32   amarinm1
// Cm005858: The frequency for External Lights reminder was changed from 4000Hz to 2400.
// 
//    Rev 1.0   Feb 24 2009 12:25:42   amarinm1
// Initial revision.
//******************************************************************************
#endif

#ifndef I_DAT_BUZx_H
#define I_DAT_BUZx_H

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



// parameterization of buzzer sound motives

             // Silence parameters                                                      
#define      cBuzzerSilenceNumFrequencies    1
static   tPERIOD_DESC aBuzzerSilence[cBuzzerSilenceNumFrequencies]  = \
//       Frequency ActiveTime InactiveTime                                          
        {
            {    0,         0,           0   }
        };



             // BUZZER_Flasher_Click parameters
#define      cBuzzerFlasherClickNumFrequencies  1
static  tPERIOD_DESC aBuzzerFlasherClick[cBuzzerFlasherClickNumFrequencies]= \
//      Frequency ActiveTime InactiveTime                                          
        {
            {2100,        150,           0}
        };
// Note: the Active time here is just for backup. The real time is read and set
// in SetBuzzRequest().



             // BUZZER_Flasher_Clack parameters
#define      cBuzzerFlasherClackNumFrequencies  1
static  tPERIOD_DESC aBuzzerFlasherClack[cBuzzerFlasherClackNumFrequencies]= \
//      Frequency ActiveTime InactiveTime                                          
        {
            {2050,        150,           0}
        };
// Note: the Active time here is just for backup. The real time is read and set
// in SetBuzzRequest().


        
             // BUZZER_LockWithSpeed parameters                                 
#define      cBuzzerLWSNumFrequencies  2
static  tPERIOD_DESC aBuzzerLWS[cBuzzerLWSNumFrequencies]= \
//      Frequency ActiveTime InactiveTime                                          
        {
            {2976,       150,         0},
            {1953,       150,         0}
        };



             // BUZZER_SeatBelt parameters                                 
#define      cBuzzerSeatBeltNumFrequencies  1
static  tPERIOD_DESC aBuzzerSeatBelt[cBuzzerSeatBeltNumFrequencies]= \
//      Frequency ActiveTime InactiveTime                                          
        {
            {1000,       100,         800}
        };



             // BUZZER_OverSpeed parameters                                 
#define      cBuzzerOverSpeedNumFrequencies  2
static  tPERIOD_DESC aBuzzerOverSpeed[cBuzzerOverSpeedNumFrequencies]= \
//      Frequency ActiveTime InactiveTime                                          
        {
            {2400,       300,         300},
            {1600,       150,          50}
        };



             // BUZZER_ExtLight parameters                                 
#define      cBuzzerExtLightNumFrequencies  1
static  tPERIOD_DESC aBuzzerExtLight[cBuzzerExtLightNumFrequencies]= \
//      Frequency ActiveTime InactiveTime                                          
        {
            {2400,       100,         100}
        };





// parameterization of the buzzers melodies

static tMELODY_DESC DATBuzMelodies[cNumberOfMelodies] = \
{

    //-------------- eBUZZER_Silence -------------------------------------------

     // tMELODY_DESC
    {
         // tSND_DESC
        {       
             // Motive *
             aBuzzerSilence,
             // NumFrequencies
             cBuzzerSilenceNumFrequencies,
             // Repetitions
             0
        },
         // Pause
        0,
         // Repetitions
        0
    },


    //-------------- eBUZZER_FlasherClick --------------------------------------

     // tMELODY_DESC
    {
         // tSND_DESC
        {       
             // Motive *
             aBuzzerFlasherClick,
             // NumFrequencies
             cBuzzerFlasherClickNumFrequencies,
             // Repetitions
             1
        },
         // Pause
        0,
         // Repetitions
        1
    },


    //-------------- eBUZZER_FlasherClack --------------------------------------

     // tMELODY_DESC
    {
         // tSND_DESC
        {       
             // Motive *
             aBuzzerFlasherClack,
             // NumFrequencies
             cBuzzerFlasherClackNumFrequencies,
             // Repetitions
             1
        },
         // Pause
        0,
         // Repetitions
        1
    },


    //-------------- eBUZZER_LockWithSpeed -------------------------------------

     // tMELODY_DESC
    {
         // tSND_DESC
        {       
             // Motive *
             aBuzzerLWS,
             // NumFrequencies
             cBuzzerLWSNumFrequencies,
             // Repetitions
             1
        },
         // Pause
        0,
         // Repetitions
        1
    },


    //-------------- eBUZZER_SeatBelt ------------------------------------------

     // tMELODY_DESC
    {
         // tSND_DESC
        {       
             // Motive *
             aBuzzerSeatBelt,
             // NumFrequencies
             cBuzzerSeatBeltNumFrequencies,
             // Repetitions
             1
        },
         // Pause
        0,
         // Repetitions
        cDATBuzRepetitionsInfinite
    },


    //-------------- eBUZZER_OverSpeed -----------------------------------------

     // tMELODY_DESC
    {
         // tSND_DESC
        {       
             // Motive *
             aBuzzerOverSpeed,
             // NumFrequencies
             cBuzzerOverSpeedNumFrequencies,
             // Repetitions
             13
        },
         // Pause
        29600,
         // Repetitions
        cDATBuzRepetitionsInfinite
    },


    //-------------- eBUZZER_ExternalLight -------------------------------------

     // tMELODY_DESC
    {
         // tSND_DESC
        {       
             // Motive *
             aBuzzerExtLight,
             // NumFrequencies
             cBuzzerExtLightNumFrequencies,
             // Repetitions
             4
        },
         // Pause
        600,
         // Repetitions
        4
    }
};


//------------------------------------------------------------------------------
// Exported type
//------------------------------------------------------------------------------

// This is an example:
// typedef Expression tLAYCmpTypeName;

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

#endif   // I_LAY_CMP_H
