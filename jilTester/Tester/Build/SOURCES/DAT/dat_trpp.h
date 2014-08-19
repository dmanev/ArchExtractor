/*============================================================================
Project ......................... X90_BCM
Component ....................... Dat_trp
File revision.................... $Revision:   1.0  $
Last modification date .......... $Modtime:   Jan 09 2009 10:40:38  $
-------------------------------------------------------------------------
Copyright ... This software is JCAE property. Duplication or
disclosure is prohibited without JCAE written permission
------------------------------------------------------------------------- 

- This file should only contain data useful to the programmer to use
this component
- Component exported macros, constants and types are defined in this file
- Component exported variables and functions are declared in this file 
with the "extern" keyword

-------------------------------------------------------------------------
Dat_trp.h file review :

$Log::   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/X90_BCM/K0/L7/CMP/DAT/DAT_IMMO/DAT$
// 
//    Rev 1.0   Jan 09 2009 14:03:58   amanevd
// Initial revision.
* 
*    Rev 1.2   Sep 04 2008 11:38:40   amanevd
* Tm092393 - IMMO - ST5.1 DAT_TRP Issue log corrections
* 
*    Rev 1.1   Jun 20 2008 18:42:02   amanevd
* Tm089118 - Immo: BASESTATION AND KEY DTC DISCRIMINATION preliminary version
* 
*    Rev 1.0   Apr 24 2007 10:56:26   ailievb
* Initial revision.
* 
*    Rev 1.6   Mar 31 2006 13:54:12   amanevd
* PON URD45 VAL 3261 / PON URD45 MODULES 9950 - included check if MERA or MERA1 timers have elapsed depending on ENGINE_STATUS_84 variable
* 
*    Rev 1.5   Sep 09 2005 15:13:28   nick
* PON URD45 VAL 1947 : EXT_MEM diagnostic request WRITING EXTENDED MEMORY returns negative response 
* PON URD45 VAL 1951 : EXT_MEM diagnostic service READING EXTENDED MEMORY returns always the same value 
* PON URD45 VAL 1948 : EXT_MEM diagnostic request WRITING VIN EXTENDED MEMORY returns negative response 
* 
*    Rev 1.4   Sep 02 2005 17:08:30   abordap
* PON URD45 DEV 2211 / PON URD45 MODULES 9309  DTC : integration of Transponder Antenna DTC for SW4
* 
*    Rev 1.3   Aug 18 2005 20:21:18   taa
* PON URD45 DEV 2166 : AW1103_V03.04#5  
* unimplemented DTC fix 
* 
*    Rev 1.2   Aug 18 2005 16:15:34   nick
* PON URD45 DEV 2070 / PON URD45 MODULES 9125 : Extended Memory Feature implementation 
* 
*    Rev 1.0   Apr 18 2005 09:41:46   agrandm
* Initial revision.
* 
*    Rev 1.3   Mar 28 2005 14:55:02   nick
* All functionality integrated.
* 
*    Rev 1.5   Feb 17 2005 13:17:52   nick
* Minor fixes.
* 
*    Rev 1.4   Feb 16 2005 10:54:42   nick
* Minor fixes.
* 
*    Rev 1.3   Dec 23 2004 12:34:58   nick
* Upd.
* 
*    Rev 1.2   Dec 15 2004 10:26:00   tod
* remove debug code
* 
*    Rev 1.1   Nov 11 2004 10:19:54   nick
* Minor fix
* 
*    Rev 1.0   Nov 10 2004 10:40:14   nick
* Initial revision.
* 
*    Rev 1.0   Sep 15 2003 15:45:22   agrandm
* Initial revision.
* 
*    Rev 1.0   Sep 12 2003 15:15:46   agrandm
* Initial revision.
* 
*    Rev 1.1   Jul 08 2003 10:09:36   adm
* Update project name

==========================================================================*/

#ifndef I_DAT_TRPP_H
#define I_DAT_TRPP_H (1)

/*-------------------------------------------------------------------------
Included files to resolve specific definitions in this file

#include <system_file_name.h>
#include "project_file_name.h"
-------------------------------------------------------------------------*/

#include "deftypes.h"

/*-------------------------------------------------------------------------
Constant data

#define cLAYCmpConstantName   ((tType) ConstantValue)
-------------------------------------------------------------------------*/
// Max number of try for read, write and resynchronization
#define cDATTrpTransponderAccessMaxNumberOfTry    ((U8) 3)

// Max number of key
#define cDATTrpMaxNumberOfKey    ((U8) 4)

////////////////////////////////
// EEPROM data redefinition
////////////////////////////////

// Array of cDATTrpMaxNumberOfKey * tU32Bit
//#define TableOfKeyIdentifier              EEP_KeyIdentifier
//#define TableOfKeyPassword                EEP_PwdTag
//#define TableOfCurrentResynchroValue      EEP_SI28Bits
//#define TableOfInitialResynchroValue      EEP_InitialResynchroValue
//#define TableOfDefResynchroValueRead      EEP_DefResynchroValueRead
//#define TableOfDefResynchroValueWritten   EEP_DefResynchroValueWrite

// U8
//#define AuthentDelayedCounter       EEP_AuthentDelayedCounter
//#define AuthentFailureCounter       EEPAuthentFailureCounter
//#define ResynchroFailureCounter     EEPResynchroFailureCounter
//#define ResynchroSuccessfulCounter  EEPResynchroSuccessfulCounter
//#define ResynchroRequest            EEPResynchroRequest

/*-------------------------------------------------------------------------
Exported Macros

#define mLAYCmpMacroName   (MacroDefinition)
-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
Exported type

struct  sLAYCmpStructureName { ... };
union   uLAYCmpUnionName { ... };
enum    eLAYCmpEnumerationName { ... };
typedef Expression tLAYCmpTypeName;

-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
Exported data

extern  tType   LAYCmpVariableName;
extern  tType*  pLAYCmpVariableName; 
-------------------------------------------------------------------------*/ 

/*-------------------------------------------------------------------------
Constant exported data

extern const tType  LAYCmpVariableName;
-------------------------------------------------------------------------*/ 

/*-------------------------------------------------------------------------
Exported functions

extern tReturnType LAYCmpFunctionName(tTypeArgument1 ArgumentName1, ... );
-------------------------------------------------------------------------*/ 


#endif   /* I_DAT_TRPP_H */
