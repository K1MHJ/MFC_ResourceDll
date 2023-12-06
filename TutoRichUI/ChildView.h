
// ChildView.h : interface of the CChildView class
//


#pragma once


// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

private:
	CListCtrl m_ListCtrl;
	CEdit m_EditCtrl; // Edit control for subitem editing
	int m_nEditItem = 0;    // Row index being edited
    int m_nEditSubItem = 0; // Column index being edited
	CFont m_EditFont;  // Member variable in your class to hold the font
// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	void OnNMDblclkMyListctrl(NMHDR *pNMHDR, LRESULT *pResult);
	void OnLvnEndlabeleditMyListctrl(NMHDR *pNMHDR, LRESULT *pResult);
	void OnEnKillfocusEditSubitem();
	void CreateCustomFont();
	void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
};

