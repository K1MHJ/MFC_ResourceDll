#pragma once
#include <afxwin.h>
#include "MyButton.h"
constexpr UINT IDC_BUTTON{ 101 };

class CMyWindow : public CFrameWnd
{
	CStatic* pMyStatic1;
	CStatic* pMyStatic2;
	MyButton button;
public:
	CMyWindow();           // protected constructor used by dynamic creation
	virtual ~CMyWindow();

	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT, CPoint);
	afx_msg void OnRButtonDown(UINT, CPoint);
	afx_msg void OnEnd();
	afx_msg void OnAbout();
	afx_msg BOOL OnCommand(WPARAM wParam,LPARAM lParam);
	afx_msg void OnDrawItem(int nIDCtl,LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnButtonClicked();
	afx_msg void OnButtonSetFocus(CWnd* pOldWnd);
	DECLARE_MESSAGE_MAP()
};


