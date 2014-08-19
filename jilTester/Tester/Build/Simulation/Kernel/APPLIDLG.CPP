// AppliDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Appli.h"
#include "AppliDlg.h"
#include "MainLev.h"
#include "Dllcom.h"
#include "XCarCAN.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern void IHM_Init_Param(void);

#define cMaxTexte 100

/////////////////////////////////////////////////////////////////////////////
// CAppliDlg dialog

CAppliDlg::CAppliDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAppliDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAppliDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_NbLine = 0;
}

void CAppliDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAppliDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAppliDlg, CDialog)
	//{{AFX_MSG_MAP(CAppliDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_SYSCOMMAND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAppliDlg message handlers

BOOL CAppliDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// IDM_XCARCAN_BOX Box must be in the system command range.
	ASSERT((IDM_XCARCAN_BOX & 0xFFF0) == IDM_XCARCAN_BOX);
	ASSERT(IDM_XCARCAN_BOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strMenu;
		strMenu.LoadString(IDS_XCARCAN_BOX);
		if (!strMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_XCARCAN_BOX, strMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// General initialisation of the IHM.
	IHM_Init_Param();

	DWORD RAS;
	m_hThread = CreateThread(	NULL, 
						0, 
						/*(LPTHREAD_START_ROUTINE )*/StartAppli,
						this,
						0,
						&RAS );

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAppliDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_XCARCAN_BOX)
    {
        // configuration dialog box
        if(XCAN_OpenDialogBox() == IDOK)
        {
            AfxMessageBox("The XCarCAN configuration will be applied\n"
                            "in the next simulation session !");    
        }
    }
    else
    {
        CDialog::OnSysCommand(nID, lParam);
    }
}

DWORD WINAPI CAppliDlg::StartAppli(  LPVOID lpParameter )
{
	CAppliDlg* pDlg = (CAppliDlg*)lpParameter;

	DWORD ret = StartLDBPC();

  if(pDlg->GetSafeHwnd() && pDlg->IsWindowEnabled())
  {
	  pDlg->PostMessage( WM_QUIT );
  }

	return ret;
}

CAppliDlg::~CAppliDlg()
{
  WaitForSingleObject(m_hThread, 2000);
	CloseHandle( m_hThread );
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAppliDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAppliDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAppliDlg::Trace(char* Texte)
{
	CEdit* pZoneTexte = (CEdit*)GetDlgItem( IDC_STATIC1 );
	m_Texte += CString(Texte);
	m_Texte += _T("\r\n");

	pZoneTexte->SetWindowText( m_Texte );

	// Limitation de la taille
	if( m_NbLine > cMaxTexte )
	{
		int Len = m_Texte.GetLength();
		int LenPremiereLigne = m_Texte.Find("\n") + 1;
		m_Texte = m_Texte.Right( Len - LenPremiereLigne );
	}
	else
	{
		m_NbLine ++; 
	}

	pZoneTexte->LineScroll( m_NbLine );
}

void CAppliDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CWnd* pZoneTexte = GetDlgItem( IDC_STATIC1 );

	if( pZoneTexte )
	{
		CRect Rect;
		GetClientRect( &Rect );
		pZoneTexte->MoveWindow( &Rect );
	}
}

void CAppliDlg::OnCancel()
{
  StopLDBPC();
}

