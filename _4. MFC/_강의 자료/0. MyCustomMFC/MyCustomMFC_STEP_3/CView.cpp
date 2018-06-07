//====================================================
#include "CView.h"
//====================================================
CView g_View;
CViewFuncPt fpCViewGlobal;
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
BEGIN_MESSAGE_MAP(CView)
	
	{ WM_CREATE,&CView::OnCreate },
	{ WM_PAINT,&CView::OnDraw },
	{ WM_LBUTTONDOWN,&CView::OnLButtonDown },
	{ WM_DESTROY,&CView::OnDestroy },

END_MESSAGE_MAP()
//====================================================
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	int i = 0;
	while (CView::messageMap[i].iMsg != 0)
	{
		if (iMsg == CView::messageMap[i].iMsg)
		{
			fpCViewGlobal = CView::messageMap[i]._fp;
			(g_View.*fpCViewGlobal)();
		}
		++i;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);

}//LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
//====================================================