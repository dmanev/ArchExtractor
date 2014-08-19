// Appli.h : main header file for the APPLI application
//

#if !defined(AFX_APPLI_H__32E3D7B5_A0E3_11D4_8E5A_005004074F5E__INCLUDED_)
#define AFX_APPLI_H__32E3D7B5_A0E3_11D4_8E5A_005004074F5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAppliApp:
// See Appli.cpp for the implementation of this class
//

class CAppliApp : public CWinApp
{
public:
    CAppliApp();

    void Trace(char* Texte);

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CAppliApp)
public:
    virtual BOOL InitInstance();
    //}}AFX_VIRTUAL

    // Implementation

    //{{AFX_MSG(CAppliApp)
    // NOTE - the ClassWizard will add and remove member functions here.
    //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPLI_H__32E3D7B5_A0E3_11D4_8E5A_005004074F5E__INCLUDED_)
