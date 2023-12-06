
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "framework.h"
#include "TutoRichUI.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_NOTIFY(NM_DBLCLK, IDC_MY_LISTCTRL, &CChildView::OnNMDblclkMyListctrl)
    ON_NOTIFY(LVN_ENDLABELEDIT, IDC_MY_LISTCTRL, &CChildView::OnLvnEndlabeleditMyListctrl)
    ON_EN_KILLFOCUS(IDC_EDIT_SUBITEM, &CChildView::OnEnKillfocusEditSubitem)
    ON_WM_DESTROY()
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_MY_LISTCTRL, &CChildView::OnCustomDraw)
END_MESSAGE_MAP()

// CChildView message handlers
BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
}



int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	// Create the list control
    CRect rect;
    GetClientRect(&rect);
    m_ListCtrl.Create(WS_CHILD | WS_VISIBLE | LVS_REPORT, rect, this, IDC_MY_LISTCTRL); //LVS_EDITLABELS
    CreateCustomFont();  // Call the function to create the font

    // Set the list control to report view
    m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

    // Adding columns
    m_ListCtrl.InsertColumn(0, _T("Column 1"), LVCFMT_LEFT, 100);
    m_ListCtrl.InsertColumn(1, _T("Column 2"), LVCFMT_LEFT, 100);

    // Adding items
    m_ListCtrl.InsertItem(0, _T("Item 1"));
    m_ListCtrl.SetItemText(0, 1, _T("SubItem 1.1"));

    m_ListCtrl.InsertItem(1, _T("Item 2"));
    m_ListCtrl.SetItemText(1, 1, _T("SubItem 2.1"));

	return 0;
}


void CChildView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
    if (m_ListCtrl.GetSafeHwnd()) // Ensure the list control is created
    {
        m_ListCtrl.MoveWindow(0, 0, cx, cy, TRUE);
    }
}
void CChildView::OnNMDblclkMyListctrl(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    int nItem = pNMItemActivate->iItem;
    int nSubItem = pNMItemActivate->iSubItem;
    m_nEditItem = nItem;
    m_nEditSubItem = nSubItem;
    if (nItem != -1 && nSubItem != -1)
    {
        // Get the subitem rectangle
        CRect rect;
        m_ListCtrl.GetSubItemRect(nItem, nSubItem, LVIR_LABEL, rect);

        // Adjust the rectangle to fit the subitem
        // ...

        // Create and show the edit control
        m_EditCtrl.Create(WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, rect, this, IDC_EDIT_SUBITEM);
        m_EditCtrl.SetFont(&m_EditFont);  // Set the font to the edit control
        m_EditCtrl.SetWindowText(m_ListCtrl.GetItemText(nItem, nSubItem));
        m_EditCtrl.SetFocus();
    }

    *pResult = 0;
}
void CChildView::OnLvnEndlabeleditMyListctrl(NMHDR *pNMHDR, LRESULT *pResult)
{
    NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
    if (pDispInfo->item.pszText != NULL)
    {
        // Update the item with the new text
        m_ListCtrl.SetItemText(pDispInfo->item.iItem, 0, pDispInfo->item.pszText);
    }
    *pResult = 0;
}
void CChildView::OnEnKillfocusEditSubitem()
{
    // Save the edited text
    CString strText;
    m_EditCtrl.GetWindowText(strText);

    // Update the list control subitem with the new text
    // Retrieve the item and subitem index
    // ...

    m_ListCtrl.SetItemText(m_nEditItem, m_nEditSubItem, strText);

    // Destroy the edit control
    m_EditCtrl.DestroyWindow();
}
void CChildView::CreateCustomFont()
{
    CFont* pFont = m_ListCtrl.GetFont();
    LOGFONT lf;
    if (pFont != NULL)
    {
        if (pFont->GetLogFont(&lf))
        {
            // Now lf contains the details of the font
            // You can access various attributes like lf.lfHeight, lf.lfWeight, lf.lfFaceName, etc.
            m_EditFont.CreateFontIndirect(&lf);
        }
    }
    return;
    // Define font attributes
    int nHeight = -MulDiv(10, GetDeviceCaps(::GetDC(NULL), LOGPIXELSY), 72); // Example for 10 pt font
    m_EditFont.CreateFont(
        nHeight,               // Height
        0,                     // Width
        0,                     // Escapement
        0,                     // Orientation
        FW_NORMAL,             // Weight
        FALSE,                 // Italic
        FALSE,                 // Underline
        0,                     // StrikeOut
        ANSI_CHARSET,          // CharSet
        OUT_DEFAULT_PRECIS,    // OutPrecision
        CLIP_DEFAULT_PRECIS,   // ClipPrecision
        DEFAULT_QUALITY,       // Quality
        DEFAULT_PITCH | FF_SWISS, // PitchAndFamily, example: Swiss font
        _T("Arial"));          // Facename, example: Arial
}

void CChildView::OnDestroy()
{
    CWnd::OnDestroy();

    // TODO: Add your message handler code here
    DeleteObject(m_EditFont);
}
void CChildView::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMLVCUSTOMDRAW lpCustomDraw = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);

    if (lpCustomDraw->nmcd.dwDrawStage == CDDS_PREPAINT)
    {
        // 最初に、ここに入る
        // 次にCDDS_ITEMPREPAINTのステージに移行するために、このif文は必要
        *pResult = CDRF_NOTIFYITEMDRAW;
        return;
    }

    if (CDDS_ITEMPREPAINT == lpCustomDraw->nmcd.dwDrawStage)
    {
        if((CDIS_SELECTED & lpCustomDraw->nmcd.uItemState) == CDIS_SELECTED)
        {
            lpCustomDraw->nmcd.uItemState = CDIS_DEFAULT;
            lpCustomDraw->clrText = RGB(255,255,255);
            lpCustomDraw->clrTextBk = RGB(0, 0, 0);
            *pResult = CDRF_NEWFONT;
            return;
        }
        *pResult = CDRF_NOTIFYSUBITEMDRAW;
        return;
    }
    if (lpCustomDraw->nmcd.dwDrawStage == (CDDS_ITEMPREPAINT | CDDS_SUBITEM))
    {
        // 行指定
        if (lpCustomDraw->nmcd.dwItemSpec == 0 && lpCustomDraw->iSubItem == 1)
        {
            lpCustomDraw->clrText = RGB(255, 0, 0);
            lpCustomDraw->clrTextBk = RGB(200, 200, 200);
        }
        else
        {
            // 色を変更しないセルのデフォルト色を指定
            // これを指定しない場合、色を変更した列以降は、同じ色になってしまう
            lpCustomDraw->clrText = GetSysColor(COLOR_WINDOWTEXT);
            lpCustomDraw->clrTextBk = GetSysColor(COLOR_WINDOW);
        }
        *pResult = CDRF_NEWFONT;
        return;
    }
    *pResult = CDRF_DODEFAULT;
    return;
}