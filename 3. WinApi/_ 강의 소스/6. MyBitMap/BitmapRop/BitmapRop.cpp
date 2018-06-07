#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("BitmapRop");

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

	hWnd=CreateWindow(lpszClass,lpszClass,WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
		NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);

	while (GetMessage(&Message,NULL,0,0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

#include "resource.h"
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc,MemDC;
	PAINTSTRUCT ps;
	HBITMAP MyBitmap, OldBitmap;
	switch (iMessage) {
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SelectObject(hdc,GetStockObject(DKGRAY_BRUSH));
		Ellipse(hdc,10,10,150,100);
		MemDC=CreateCompatibleDC(hdc);
		MyBitmap=LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		OldBitmap=(HBITMAP)SelectObject(MemDC, MyBitmap);
		/*	
			SRCCOPY		:	비트맵을 그대로 화면dc에 출력			Src
			SRCAND		:	비트맵과 화면dc를 AND 연산.				Src & 화면DC
			SRCPAINT	:	비트맵과 화면dc를 OR 연산				Src | 화면DC
			SRCERASE	:	비트맵과 화면dc의 반전색을 AND연산.		Src & ~화면DC
			SRCINVERT	:	비트맵과 화면dc를 XOR연산				Src ^ 화면DC
		*/
		BitBlt(hdc, 0,0,123,160,MemDC,0,0, SRCERASE);
		SelectObject(MemDC,OldBitmap);
		DeleteObject(MyBitmap);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

