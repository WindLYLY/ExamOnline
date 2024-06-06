// DLGLOGON.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "DLGLOGON.h"
#include "./netlib/message.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDLGLOGON dialog


CDLGLOGON::CDLGLOGON(CWnd* pParent /*=NULL*/)
	: CDialog(CDLGLOGON::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDLGLOGON)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDLGLOGON::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDLGLOGON)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDLGLOGON, CDialog)
	//{{AFX_MSG_MAP(CDLGLOGON)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLGLOGON message handlers
#define LEN_USER 20
#define LEN_PASSWD 20
CString g_name = "";
void CDLGLOGON::OnOK() 
{
	// TODO: Add extra validation here
	CString struser,strpasswd,strrandom,strinput;
	char *pdata;

	GetDlgItemText(IDC_STATICRANDOM,strrandom);
	GetDlgItemText(IDC_EDITCHECKSUM,strinput);
	if (strinput != strrandom)
	{
		AfxMessageBox("Ð£ÑéÂë´íÎó£¡");
		return;
	}	

	GetDlgItemText(IDC_EDITUSERNAME,struser);
	GetDlgItemText(IDC_EDITPASSWD,strpasswd);
	pdata = new char[LEN_USER+LEN_PASSWD];
	memset(pdata,0,LEN_USER+LEN_PASSWD);
	int lentocpuser;
	int lentocppasswd;
	if (struser.GetLength()<LEN_USER)
		lentocpuser = struser.GetLength();
	else
		lentocpuser = LEN_USER - 1;
	memcpy(pdata,(char *)(LPCTSTR)struser,lentocpuser);
	if (strpasswd.GetLength()<LEN_PASSWD)
		lentocppasswd = strpasswd.GetLength();
	else
		lentocppasswd = LEN_PASSWD - 1;
	memcpy(pdata+LEN_USER,(char *)(LPCTSTR)strpasswd,lentocppasswd);
	if (DoMsgSend(MSG_MANAGE,MSG_LOGON,pdata,LEN_USER+LEN_PASSWD))
	{
		g_name = struser;
		CDialog::OnOK();
	}
	else
	{
		AfxMessageBox("ÃÜÂëÊäÈë´íÎó£¬ÇëÖØÐÂÊäÈë!");
	}
	if (pdata)
		delete []pdata;
}

BOOL CDLGLOGON::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	time_t t;
	srand((unsigned) time(&t));
	
	char s[5];
	memset(s,0,5);
	for(int i=0;i<4;i++)
	{
		s[i] = 'A' + rand()%10;
	}

	SetDlgItemText(IDC_STATICRANDOM,s);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
