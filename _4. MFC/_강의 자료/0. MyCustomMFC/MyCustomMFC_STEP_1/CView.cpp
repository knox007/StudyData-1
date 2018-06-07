//====================================================
#include "CView.h"
//====================================================
CView g_View;
//====================================================
void CView::OnCreate() { MessageBox(NULL, TEXT("OnCreate"), TEXT("Custom MFC"), MB_ICONEXCLAMATION | MB_OK); }
//====================================================
void CView::OnDraw()
{
	HDC         hdc;
	PAINTSTRUCT ps;
	RECT        rect;

	hdc = BeginPaint(_hWnd, &ps);
	GetClientRect(_hWnd, &rect);
	DrawText(hdc, TEXT("OnDraw"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	EndPaint(_hWnd, &ps);

}//	void CView::OnDraw()
 //====================================================
void CView::OnLButtonDown() { MessageBox(NULL, TEXT("OnLButtonDown"), TEXT("Custom MFC"), MB_ICONEXCLAMATION | MB_OK); }
//====================================================
void CView::OnDestroy()
{
	MessageBox(NULL, TEXT("OnDestroy"), TEXT("Custom MFC"), MB_ICONEXCLAMATION | MB_OK);
	PostQuitMessage(0);
}
//====================================================