// AppliDlg.h : header file
//

#if !defined(AFX_APPLIDLG_H__32E3D7B7_A0E3_11D4_8E5A_005004074F5E__INCLUDED_)
#define AFX_APPLIDLG_H__32E3D7B7_A0E3_11D4_8E5A_005004074F5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAppliDlg dialog

class CAppliDlg : public CDialog
{
    // Construction
public:
    CAppliDlg(CWnd* pParent = NULL);	// standard constructor
    virtual ~CAppliDlg();

    void Trace(char* Texte);
    static DWORD WINAPI StartAppli(  LPVOID lpParameter );

    // Dialog Data
    //{{AFX_DATA(CAppliDlg)
    enum { IDD = IDD_APPLI_DIALOG };
    // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CAppliDlg)
	protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

    // Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    //{{AFX_MSG(CAppliDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
  virtual void OnOk() {}

private:
    HANDLE	m_hThread;
    CString m_Texte;
    int		m_NbLine;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPLIDLG_H__32E3D7B7_A0E3_11D4_8E5A_005004074F5E__INCLUDED_)
