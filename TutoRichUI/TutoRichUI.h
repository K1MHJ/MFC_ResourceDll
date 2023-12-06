
// TutoRichUI.h : main header file for the TutoRichUI application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CTutoRichUIApp:
// See TutoRichUI.cpp for the implementation of this class
//

class CTutoRichUIApp : public CWinApp
{
public:
	CTutoRichUIApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	DECLARE_MESSAGE_MAP()
};

extern CTutoRichUIApp theApp;
