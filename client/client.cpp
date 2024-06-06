// client.cpp : Defines the class behaviors for the application.
//
#include "dh.h"
#include "stdafx.h"
#include "client.h"
#include "clientDlg.h"
#include "netlib/message.h"
#include ".\client.h"
#include "msgdispatcher.h"
#include "DLGLOGON.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientApp

BEGIN_MESSAGE_MAP(CClientApp, CWinApp)
	//{{AFX_MSG_MAP(CClientApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

Config g_cfg;

void init_threads()//��ʼ�������߳�
{
	g_cfg.setproc(NULL,msgdispatcher);
	CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)recvmsg,
								&g_cfg,0,NULL);//������Ϣ�����߳�
}

void exit_threads()//��ʼ�������߳�
{
	g_cfg.SetEndflg(true);
	while (g_cfg.GetEndflg()==true)
	{
		Sleep(100);
	}
}

// CclientApp ����

CClientApp::CClientApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CClientApp object

CClientApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CClientApp initialization

BOOL CClientApp::InitInstance()
{
	CoInitialize(NULL);
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	init_threads();
	CClientDlg dlg;
	CDLGLOGON dlglogon;
	
	int nResponse = dlglogon.DoModal();
	if (nResponse == IDOK)
	{
		m_pMainWnd = &dlg;
		dlg.DoModal();
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
int CClientApp::ExitInstance()
{
	// TODO: Add your specialized code here and/or call the base class
	CoUninitialize();
	return CWinApp::ExitInstance();
}