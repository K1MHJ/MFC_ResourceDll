#include "pch.h"
#include "MyWindow.h"
#include "Resource.h"
#include "../MFCExLib/ResourceDef.h"

BEGIN_MESSAGE_MAP(CMyWindow, CFrameWnd)
    ON_WM_PAINT()
    ON_WM_LBUTTONDOWN()
    ON_WM_RBUTTONDOWN()
    ON_WM_DRAWITEM()
    ON_COMMAND(IDM_END, OnEnd)
    ON_COMMAND(IDM_ABOUT, OnAbout)
    ON_BN_CLICKED(IDC_BUTTON, OnButtonClicked)
END_MESSAGE_MAP()

typedef void(*typeDLLGetBitmap)(DWORD resource_ID, CBitmap* bitmap);
typeDLLGetBitmap DLLGetBitmap = nullptr;

CBitmap g_myBMP;
HINSTANCE hModule;
CMyWindow::CMyWindow()
{
    Create(NULL, L"猫でもわかるメニュー", WS_OVERLAPPEDWINDOW,
        CRect(100, 100, 100 + 820, 100 + 820), NULL, L"MYMENU");
    pMyStatic1 = new CStatic();
    pMyStatic1->Create(L"",
        WS_CHILD | WS_VISIBLE,
        CRect(20, 20, 40, 40),
        this);
    pMyStatic2 = new CStatic();
    pMyStatic2->Create(L"",
        WS_CHILD | WS_VISIBLE,
        CRect(20, 40, 40, 60),
        this);
    button.Create(L"Hello", BS_PUSHBUTTON | BS_OWNERDRAW, CRect(0, 0, 100, 100), this, IDC_BUTTON);
    button.ShowWindow(SW_SHOW);
    //button.SubclassDlgItem(IDC_BUTTON, this); // it only using in dialog I think

	hModule = AfxLoadLibrary(L"MFCExLib.dll");

    if (NULL != hModule) {
	    DLLGetBitmap = (typeDLLGetBitmap)GetProcAddress(hModule, "GetBitmapResource");
    }
}

void CMyWindow::OnPaint()
{
    CPaintDC dc(this);

    CDC memoryDC;
    CBitmap myBMP;
    CPngImage image;

    //AfxSetResourceHandle(AfxGetApp()->m_hInstance);
    if (!image.Load(IDB_PNG1, nullptr))
        return;

    memoryDC.CreateCompatibleDC(&dc);
    DLLGetBitmap(IDR_WHOLE_BACKGROUND, &myBMP);
    //myBMP.Attach(image.Detach());
    BITMAP bm;
    myBMP.GetBitmap(&bm);
    CBitmap* oldBMP = memoryDC.SelectObject(&myBMP);

    dc.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &memoryDC, 0, 0, SRCCOPY);
    memoryDC.SelectObject(oldBMP);

    CString str1 = L"回　左クリックされました";
    CString str2 = L"回　右クリックされました";
    dc.TextOut(40, 20, str1);
    dc.TextOut(40, 40, str2);
}

void CMyWindow::OnRButtonDown(UINT nFlags, CPoint pt)
{
    static int n = 1;
    WCHAR* szNum = L"%d";
    WCHAR str[8];
    wsprintf(str, szNum, n++);
    pMyStatic2->SetWindowText(str);
}


void CMyWindow::OnLButtonDown(UINT nFlags, CPoint pt)
{
    static int n = 1;
    WCHAR* szNum = L"%d";
    WCHAR str[8];
    TRACE("OnLButtonDown\n");
    wsprintf(str, szNum, n++);
    pMyStatic1->SetWindowText(str);
}
CMyWindow::~CMyWindow()
{
    delete pMyStatic1;
    delete pMyStatic2;
    AfxFreeLibrary(hModule);
    //CFrameWnd::~CFrameWnd();
}
void CMyWindow::OnAbout()
{
    MessageBox(L"粂井康孝・制作著作", L"About");
}

void CMyWindow::OnDrawItem(int nIDCtl,LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    if (nIDCtl == IDC_BUTTON) {
        CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
        CDC memdc;
        CBitmap btn_bitmap;
        TRACE("%d\n", button.pushed);
        DLLGetBitmap(button.pushed?IDR_BUTTON_PUSHED : IDR_BUTTON, &btn_bitmap);
		BITMAP bm;
		btn_bitmap.GetBitmap(&bm);
        memdc.CreateCompatibleDC(pDC);

		CBitmap* oldBMP = memdc.SelectObject(&btn_bitmap);
		pDC->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &memdc, 0, 0, SRCCOPY);
		memdc.SelectObject(oldBMP);
		CString str = L"HAHA";
		pDC->TextOut(0, 0, str);
        ::SetWindowPos(lpDrawItemStruct->hwndItem, HWND_TOP, 20, 20, 125, 75, SWP_SHOWWINDOW);
    }
    else {
        CFrameWnd::OnDrawItem(nIDCtl, lpDrawItemStruct);
    }
}

void CMyWindow::OnEnd()
{
    SendMessage(WM_CLOSE);
}

void CMyWindow::OnButtonClicked()
{
}
void CMyWindow::OnButtonSetFocus(CWnd* pOldWnd)
{
}
BOOL CMyWindow::OnCommand(WPARAM wParam, LPARAM lParam)
{
    switch (LOWORD(wParam)) 
    {
    case IDC_BUTTON:
        switch (HIWORD(wParam)) {
            default:
                break;
        }
        break;
    }
    return TRUE;
}
