; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CExperimentDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "experiment.h"

ClassCount=3
Class1=CExperimentApp
Class2=CExperimentDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_EXPERIMENT_DIALOG
Resource4=IDD_DIALOGAdduser

[CLS:CExperimentApp]
Type=0
HeaderFile=experiment.h
ImplementationFile=experiment.cpp
Filter=N

[CLS:CExperimentDlg]
Type=0
HeaderFile=experimentDlg.h
ImplementationFile=experimentDlg.cpp
Filter=D
LastObject=CExperimentDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=experimentDlg.h
ImplementationFile=experimentDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_EXPERIMENT_DIALOG]
Type=1
Class=CExperimentDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BUTTON1,button,1342242816
Control4=IDC_SEARCHUSERNAME,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_RESULT,static,1342308352
Control7=IDC_SEARCH,button,1342242816
Control8=IDC_PRINT,edit,1350631556

[DLG:IDD_DIALOGAdduser]
Type=1
Class=?
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDITUSERNAME,edit,1350631552
Control4=IDC_STATICUSERNAME,static,1342308352
Control5=IDC_STATICPASSWD,static,1342308352
Control6=IDC_EDITPASSWORD,edit,1350631552

