#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("Bounce");

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
	  ,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=NULL;
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd=CreateWindow(lpszClass,lpszClass,WS_BORDER | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT,CW_USEDEFAULT,640,350,
		NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);
	hWndMain=hWnd;
	
	while (GetMessage(&Message,NULL,0,0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

#define R 20
int x,y;
int xi,yi;
void OnTimer()
{
	RECT crt;

	GetClientRect(hWndMain,&crt);
	if (x <= R || x >= crt.right-R) {
		xi*=-1;
	}
	if (y <= R || y >= crt.bottom-R) {
		yi*=-1;
	}
	x+=xi;
	y+=yi;

	// ��ü ��ȿȭ
	InvalidateRect(hWndMain,NULL, FALSE);
	//InvalidateRect(hWndMain, NULL, TRUE);
/* �� �ֺ��� ��ȿȭ
	RECT rt;
	SetRect(&rt,x-R-5,y-R-5,x+R+5,y+R+5);
	InvalidateRect(hWndMain,&rt,TRUE);
//*/
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen,OldPen;
	HBRUSH hBrush,OldBrush;
	RECT crt;
	int i;

	switch (iMessage) {
	case WM_CREATE:
		x=50;
		y=50;
		xi=4;
		yi=5;
		SetTimer(hWnd,1,25,NULL);
		return 0;
	case WM_TIMER:
		OnTimer();
		return 0;

		//*
	case WM_ERASEBKGND:
		int a;
		a = 0;
		break;
		//return 0;
		//*/

	case WM_PAINT:
		hdc=BeginPaint(hWnd, &ps);
		GetClientRect(hWnd,&crt);

		hPen = CreatePen(PS_INSIDEFRAME, 1, RGB(255, 0, 0));
		OldPen = (HPEN)SelectObject(hdc, hPen);
		for (i=0;i<crt.right;i+=10) {
			MoveToEx(hdc,i,0,NULL);
			LineTo(hdc,i,crt.bottom);
		}

		hPen = CreatePen(PS_INSIDEFRAME, 1, RGB(0, 0, 255));
		OldPen = (HPEN)SelectObject(hdc, hPen);
		for (i=0;i<crt.bottom;i+=10) {
			MoveToEx(hdc,0,i,NULL);
			LineTo(hdc,crt.right,i);
		}

		//	�ܰ��� ����.
		hPen=CreatePen(PS_INSIDEFRAME,3,RGB(255, 255, 0));
		OldPen=(HPEN)SelectObject(hdc,hPen);

		//	���� �� ����.
		hBrush=CreateSolidBrush(RGB(0,0,255));
		OldBrush=(HBRUSH)SelectObject(hdc,hBrush);

		//	�� �׸���.
		Ellipse(hdc,x-R,y-R,x+R,y+R);

		//	�� ����.
		DeleteObject(SelectObject(hdc,OldPen));
		//	�귯�� ����
		DeleteObject(SelectObject(hdc,OldBrush));
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		KillTimer(hWnd,1);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
