/*============================================================================
  Project ......................... SW0032
  Component ....................... CImgCompare
  File revision.................... $Revision:   1.0  $
  Last modification date .......... $Modtime:   04 Feb 2009 16:32:30  $
  -------------------------------------------------------------------------
  Copyright ... This software is JCI property. Duplication or
                disclosure is prohibited without JCI written permission
  ------------------------------------------------------------------------- 

  - Macros, constants and types which are not exported are defined in 
    this file
  - Variables and functions which are not exported are defined in this 
    file with the static key word
  
  -------------------------------------------------------------------------
  Comments on the component (role, algorithm, structure, limitations,
           defined tasks and events...)
  - Role :
  
  -------------------------------------------------------------------------
  ImgCompare.cpp file review : 

   $Log:   J:/_PVCSRoot/Renault/X90_BCM/SOFTWARE/PVCS/archives/DEVELOPMENT/EXT_CMP/CPP_CMP/STK/SIMUL/Kernel/IMGCOMPARE.CPP-arc  $
// 
//    Rev 1.0   04 Feb 2009 17:02:18   adzhelp
// Initial revision.
 * 
 *    Rev 1.3   Oct 17 2007 15:21:52   aguillgi
 * PON URD42 VAL 6325 / PON URD45 BODY_SW 968 : LDBPC compile error under Visual Studio 2003. (proposed by Orlin Stoilov, reviewed by Gilles Guillen)
 * 
 *    Rev 1.2   31 Jan 2005 11:38:42   abarbae
 * PON URD42 DEV 2379 / PON URD42 BODY_SW 784 : Apply new coding rules base types
 * 
 *    Rev 1.1   Nov 14 2003 17:04:24   abarbae
 * PON URD42 BODY_SW 371 : Transalate LDB API into english
 * 
 *    Rev 1.0   Apr 30 2003 08:12:52   abarbae
 * Initial revision.
 * 
 *    Rev 1.0   Sep 19 2002 17:32:50   guillen
 * Initial revision.
 * 
 *    Rev 1.0   Sep 19 2002 17:13:10   guillen
 * Initial revision.

  ==========================================================================*/

#include "config.h"
#ifdef LDBPC_IMAGE_COMPARE

/*--------------------------------------------------------------------------
  Body Identification
  --------------------------------------------------------------------------*/
#define ImgCompare "ImgCompare"

/*-------------------------------------------------------------------------
  Included files

  #include <system_file_name.h>
  #include "project_file_name.h"
  --------------------------------------------------------------------------*/
  #include "stdafx.h"
  #include "ImgCompare.h"
  #include "LDBPCDon.h"

/*--------------------------------------------------------------------------
  Local constants

  #define cConstantName   ((tType) ConstantValue)
  --------------------------------------------------------------------------*/
#define DECLSPEC __declspec(dllimport) 


/*--------------------------------------------------------------------------
  Local macro

  #define mMacroName   (MacroDefinition)
  --------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------
  Local type

  struct  sStructureName { ... };
  union   uUnionName { ... };
  enum    eEnumerationName { ... };
  typedef Expression tTypeName;
  --------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------
  Local data

  static  tType   VariableName;
  static  tType*  pVariableName; 
  --------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------
  Constant local Data

  static const tType  VariableName;
  --------------------------------------------------------------------------*/
	CImgCompare ImgCmp;

/*--------------------------------------------------------------------------
  Exported data

  tType   CMPVariableName;      (CMP: 3 characters to identify this component)
  tType*  pCMPVariableName;     (CMP: 3 characters to identify this component)
  --------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------
  Constant exported data
 
  const tType   CMPVariableName;(CMP: 3 characters to identify this component)
  --------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------
  Local function prototypes
  
  static tTypeRetour FunctionName(tTypeArgument1 ArgumentName1, ... );
  --------------------------------------------------------------------------*/
//U8 GetNbScreen(void) {return 2;}
//BOOL ScreenCompare(U8 id, char * pFile, char * pMask, U8 Tol) {return cTrue;}
DECLSPEC U8 GetNbScreen(void);
DECLSPEC BOOL ScreenCompare(U8 id, char * pFile, char * pMask, U8 Tol);

/*--------------------------------------------------------------------------
  Exported member function of the exprted class.
  
  tType  tTypeRetour CClassName::FunctionName(tTypeArgument1 ArgumentName1, ... );
  --------------------------------------------------------------------------*/

/*============================================================================
  DESCRIPTION : Constructor
  
  PARAMETERS (Type,Name,Min,Max) :   none

  RETURN VALUE :   none
 
  DESIGN INFORMATION :   refer to Detailed Design Document
  ==========================================================================*/
CScreenCompare::CScreenCompare(U8 ScreenId)
{
	m_ScreenId = ScreenId;
	m_RefFile = -1;
	m_RefMask = -1;
	m_RefTol = -1;
	m_RefEvtStart = -1;
	m_RefEvtEnd = -1;
	m_RefResult = -1;
}

/*============================================================================
  DESCRIPTION : Destructor
  
  PARAMETERS (Type,Name,Min,Max) :   none

  RETURN VALUE :   none
 
  DESIGN INFORMATION :   refer to Detailed Design Document
  ==========================================================================*/
CScreenCompare::~CScreenCompare()
{

}

/*============================================================================
  DESCRIPTION : Creation
  
  PARAMETERS (Type,Name,Min,Max) :   none

  RETURN VALUE :   none
 
  DESIGN INFORMATION :   refer to Detailed Design Document
  ==========================================================================*/
void CScreenCompare::Create(void)
{
	tLDBPCStatut Statut;
	char * pName;
	char Group[] = {"ImageCompare"};

	CString Name,Prefix;
	Prefix.Format("Scr%d",m_ScreenId+1);

	Name.Format("%sFileNameRef",Prefix);
	pName = Name.GetBuffer(MAX_PATH);

	Statut = Donnees.CreerDonnee(&m_RefFile,pName,cDLLEntree,cDLLTypeTab, 255*8,(U8*)NULL,Group);
	
	Name.ReleaseBuffer();

	if(Statut != cLdbpcOk)
	{
		return;
	}

	Name.Format("%sFileNameMask",Prefix);
	pName = Name.GetBuffer(MAX_PATH);

	Statut = Donnees.CreerDonnee(&m_RefMask,pName,cDLLEntree,cDLLTypeTab, 255*8,(U8*)NULL,Group);
	
	Name.ReleaseBuffer();

	if(Statut != cLdbpcOk)
	{
		return;
	}

	Name.Format("%sTolerance",Prefix);
	pName = Name.GetBuffer(MAX_PATH);

	Statut = Donnees.CreerDonnee(&m_RefTol,pName,cDLLEntree,cDLLTypeVal,1,(U32)0,Group);
	
	Name.ReleaseBuffer();

	if(Statut != cLdbpcOk)
	{
		return;
	}

	Name.Format("%sEvtCompareStart",Prefix);
	pName = Name.GetBuffer(MAX_PATH);

	Statut = Donnees.CreerDonnee(&m_RefEvtStart,pName,cDLLEntree,cDLLTypeEvt,0,(U32)0
		,Group,CScreenCompare::s_Callback, (tpParam)this);
	
	Name.ReleaseBuffer();

	if(Statut != cLdbpcOk)
	{
		return;
	}

	Name.Format("%sEvtCompareEnd",Prefix);
	pName = Name.GetBuffer(MAX_PATH);

	Statut = Donnees.CreerDonnee(&m_RefEvtEnd,pName,cDLLSortie,cDLLTypeEvt,0,(U32)0,Group);
	
	Name.ReleaseBuffer();

	if(Statut != cLdbpcOk)
	{
		return;
	}

	Name.Format("%sResult",Prefix);
	pName = Name.GetBuffer(MAX_PATH);

	Statut = Donnees.CreerDonnee(&m_RefResult,pName,cDLLSortie,cDLLTypeVal,1,(U32)0,Group);
	
	Name.ReleaseBuffer();

	if(Statut != cLdbpcOk)
	{
		return;
	}
}

/*============================================================================
  DESCRIPTION : Static reception of the event
  
  PARAMETERS (Type,Name,Min,Max) :   none

  RETURN VALUE :   none
 
  DESIGN INFORMATION :   refer to Detailed Design Document
  ==========================================================================*/
void CScreenCompare::s_Callback(tpParam par1,tpParam par2)
{
	CScreenCompare * pScr = (CScreenCompare *)par1;
	if(pScr != NULL)
	{
		pScr->CallBack();
	}
}

/*============================================================================
  DESCRIPTION : Object receeption of the event
  
  PARAMETERS (Type,Name,Min,Max) :   none

  RETURN VALUE :   none
 
  DESIGN INFORMATION :   refer to Detailed Design Document
  ==========================================================================*/
void CScreenCompare::CallBack()
{
	char pFile[MAX_PATH];
	char pMask[MAX_PATH];
	U8 Tol;

	Donnees.Lire(m_RefFile, (U8*)pFile,NULL,NULL);
	Donnees.Lire(m_RefMask, (U8*)pMask,NULL,NULL);
	Donnees.Lire(m_RefTol, (U32 *)&Tol,NULL,NULL);
	if(ScreenCompare(m_ScreenId, pFile, pMask, Tol))
	{
		Donnees.EcrireSortie(m_RefResult,1);
	}
	else
	{
		Donnees.EcrireSortie(m_RefResult,(U32)0);
	}
	Donnees.EmettreEvtSor(m_RefEvtEnd);
}

//  ########################################################################
//  ########################################################################
//  ########################################################################



/*============================================================================
  DESCRIPTION : Constructor
  
  PARAMETERS (Type,Name,Min,Max) :   none

  RETURN VALUE :   none
 
  DESIGN INFORMATION :   refer to Detailed Design Document
  ==========================================================================*/
CImgCompare::CImgCompare()
{
	m_NbScreen = 0;
}

/*============================================================================
  DESCRIPTION : Destructor
  
  PARAMETERS (Type,Name,Min,Max) :   none

  RETURN VALUE :   none
 
  DESIGN INFORMATION :   refer to Detailed Design Document
  ==========================================================================*/
CImgCompare::~CImgCompare()
{
	Destroy();
}

/*============================================================================
  DESCRIPTION : Creation of the functionnal data
  
  PARAMETERS (Type,Name,Min,Max) :   none

  RETURN VALUE :   none
 
  DESIGN INFORMATION :   refer to Detailed Design Document
  ==========================================================================*/
void CImgCompare::Create(void)
{
	CScreenCompare * pScrCmp = NULL;

	m_NbScreen = GetNbScreen();
	for(U8 idx = 0; idx < m_NbScreen; idx++)
	{
		pScrCmp = new CScreenCompare(idx);
		if(pScrCmp)
		{
			Add(pScrCmp);
			pScrCmp->Create();
		}
	}
}

/*============================================================================
  DESCRIPTION : Destruction of the functionnal Data
  
  PARAMETERS (Type,Name,Min,Max) :   none

  RETURN VALUE :   none
 
  DESIGN INFORMATION :   refer to Detailed Design Document
  ==========================================================================*/
void CImgCompare::Destroy(void)
{
	CScreenCompare * pScrCmp = NULL;
	for(int idx = 0; idx < m_NbScreen; idx++)
	{
		pScrCmp = GetAt(idx);
		if(pScrCmp != NULL)
		{
			delete pScrCmp;
		}
	}
	RemoveAll();
}

#endif
