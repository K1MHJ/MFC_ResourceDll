// MyButton.cpp : implementation file
//

#include "pch.h"
#include "MyButton.h"


// MyButton

IMPLEMENT_DYNAMIC(MyButton, CButton)

MyButton::MyButton()
{

}

MyButton::~MyButton()
{
}
void MyButton::OnLButtonDown(UINT nFlags, CPoint point)
{
    // Handle mouse down event here
    CButton::OnLButtonDown(nFlags, point);
    pushed = true;
}
void MyButton::OnLButtonUp(UINT nFlags, CPoint point)
{
    // Handle mouse down event here
    CButton::OnLButtonDown(nFlags, point);
    pushed = false;
}

BEGIN_MESSAGE_MAP(MyButton, CButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// MyButton message handlers


