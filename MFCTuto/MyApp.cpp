#include "pch.h"
#include "framework.h"
#include "MyApp.h"
#include "MyWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMyApp theApp;

BOOL CMyApp::InitInstance()
{
	m_pMainWnd = new CMyWindow();
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

