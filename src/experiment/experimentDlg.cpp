// experimentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "experiment.h"
#include "experimentDlg.h"
#include ".\experimentdlg.h"
#include "DlgAddUser.h"
#include "database\database.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExperimentDlg dialog

CExperimentDlg::CExperimentDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExperimentDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExperimentDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExperimentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExperimentDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CExperimentDlg, CDialog)
	//{{AFX_MSG_MAP(CExperimentDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEARCH, OnSearch)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExperimentDlg message handlers

BOOL CExperimentDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CExperimentDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CExperimentDlg::OnPaint() 
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
HCURSOR CExperimentDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CExperimentDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	CDlgAddUser dlguser;
	dlguser.DoModal();
}

void CExperimentDlg::OnSearch() 
{
	// TODO: Add your control notification handler code here
	CDATABASE db(STR_DB_PATH,STR_DB_ADMIN,STR_DB_PASSWD,"");//数据库
	CString strsql = "";
	CString username;
	std::string logtime, msg;
	std::string res; // 结果字符串
	
	res = "   日志时间       日志信息  \r\n";
	GetDlgItemText(IDC_SEARCHUSERNAME, username);
	strsql.Format("select * from log where username='%s'",username);
	
	CSQL sql;
	IBPP::Statement st;
	sql.AppendSQL((LPTSTR)(LPCTSTR)(strsql));//加入SQL语句
	if (!db.isconnected())
		return;
	IBPP::Transaction tr = IBPP::TransactionFactory(db.get_db());
	tr->Start();
	
	bool rtn_flg = false;

	try{
		rtn_flg = db.ExecSqlTransaction(sql,st,tr);
		if (rtn_flg == false)
		{
			tr->Rollback();
			return;
		}
		rtn_flg = false;
		while (st->Fetch())//对角色数据集进行遍历
		{
			// st->Get("SALT",isalt);
			st->Get("logtime", logtime);
			st->Get("msg", msg);
			//输出信息
			res += logtime + " "; // 字符串拼接日志时间
			res += msg + "\r\n"; // 字符串拼接日志信息并换行
		}
		SetDlgItemText(IDC_PRINT, res.c_str());
		tr->Commit();
	}
	catch(IBPP::SQLException &e){ 
        tr->Rollback();
		rtn_flg = false;
	}
}
