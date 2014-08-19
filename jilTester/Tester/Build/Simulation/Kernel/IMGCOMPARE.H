/****************************************************************************
  Project ......................... SW0032
  Component ....................... CImgCompare & CScreenCompare
  File revision.................... :   1.0  $
  Last modification date .......... $Modtime:   04 Feb 2009 16:32:30  $
  -------------------------------------------------------------------------
  Copyright ... This software is JCI property. Duplication or
                disclosure is prohibited without JCI written permission
  ------------------------------------------------------------------------- 
    
  - This file should only contain data useful to the programmer to use
    this component
  - Component exported macros, constants and types are defined in this file
  - Component exported variables and functions are declared in this file 
    with the "extern" keyword
  
  -------------------------------------------------------------------------
   $Workfile:   IMGCOMPARE.H  $ file review :
  
   :   P:/STANDARD/AEH/STK/PVCS/archives/STK/BUILD/SIMUL/KERNEL/ImgCompare.h-arc  $
 * 
 *    Rev 1.0   Apr 30 2003 08:12:52   abarbae
 * Initial revision.
 * 
 *    Rev 1.0   Sep 19 2002 17:32:50   guillen
 * Initial revision.
 * 
 *    Rev 1.0   Sep 19 2002 17:13:10   guillen
 * Initial revision.

*****************************************************************************/
#ifndef	I_IMG_COMPARE_H
#define I_IMG_COMPARE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*--------------------------------------------------------------------------
  Included files to resolve specific definitions in this file

  #include <system_file_name.h>
  #include "project_file_name.h"
  --------------------------------------------------------------------------*/

#include "Ldbpc.h"
#include "array.h"


/*--------------------------------------------------------------------------
  Constant data

  #define cCMPConstantName   ((tType) ConstantValue)
  --------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------
  Exported types

  struct  sCMPStructureName { ... };
  union   uCMPUnionName { ... };
  enum    eCMPEnumerationName { ... };
  typedef Expression tCMPTypeName;

  --------------------------------------------------------------------------*/
class CImgCompare;
extern CImgCompare ImgCmp;


/*--------------------------------------------------------------------------
  Exported class

  class  CClassName { ... };

  --------------------------------------------------------------------------*/

class CScreenCompare
{
public:
    CScreenCompare(U8 ScreenId);

    virtual ~CScreenCompare();

    void Create(void);

    void Initialize(void);

    static void s_Callback(tpParam par1,tpParam par2);

    void CallBack(void);
private:
    U8 m_ScreenId;

    S32 m_RefFile;
    S32 m_RefMask;
    S32 m_RefTol;
    S32 m_RefEvtStart;
    S32 m_RefEvtEnd;
    S32 m_RefResult;
};

typedef	tcArray<CScreenCompare *>	CScreenComparetArray;

// Interface for the CImgCompare class.
class CImgCompare : public CScreenComparetArray
{
public:

    CImgCompare();				// standard constructor

    virtual ~CImgCompare();		// standard destructor

    void Create(void);

    void Initialize(void);

    void Destroy(void);

private :
    int m_NbScreen;
};

#endif // I_IMG_COMPARE_H
