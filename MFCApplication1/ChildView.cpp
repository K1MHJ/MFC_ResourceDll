
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
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
	ON_COMMAND(ID_EDIT_PASTE, &CChildView::OnPaintNext)
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
	CPngImage pngImage;
	if (!pngImage.LoadFromFile(L"C:\\Users\\hyungjinkim\\dev\\VS_Projects\\Tutorial\\resource\\default.png")) {
		return FALSE;
	}
	preBmp.Attach(pngImage.Detach());
    preBmp.GetBitmap(&m_bm);
	if (!pngImage.LoadFromFile(L"C:\\Users\\hyungjinkim\\dev\\VS_Projects\\Tutorial\\resource\\click.png")) {
		return FALSE;
	}
	postBmp.Attach(pngImage.Detach());
	return TRUE;
}

void CChildView::OnPaintNext()
{
	CDC memoryDC;
	memoryDC.CreateCompatibleDC(NULL);
    CBitmap* oldBMP = memoryDC.SelectObject(&postBmp);
    m_memoryDC.BitBlt(
		0, 0, m_bm.bmWidth/2, m_bm.bmHeight/2, &memoryDC,
		0, 0, SRCCOPY);
    memoryDC.SelectObject(oldBMP);
	Invalidate();
}
void CChildView::OnPaintReset() 
{
    m_memoryDC.CreateCompatibleDC(NULL);
    CBitmap* oldBMP = m_memoryDC.SelectObject(&preBmp);
}
void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CRect rect;
	GetClientRect(&rect);
    dc.StretchBlt(
		0, 0, rect.Width(), rect.Height(), &m_memoryDC,
		0, 0, m_bm.bmWidth, m_bm.bmHeight, SRCCOPY);
}
int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	OnPaintReset();
	return 0;
}
