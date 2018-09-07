#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("Bitmap");

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

		/*
		MemDC=CreateCompatibleDC(hdc);
		-	���ڷ� �־��� dc�� ������ Ư���� �޸� DC ��ȯ.
		-	��Ʈ���� �뷮�� Ŀ�� ȭ������ ��ٷ� �߷��� �� ���� �޸� DC�� �̸� �غ��� ���� ���.
			-	�޸� DC : ȭ�� DC�� ������ Ư���� ������ ���ο� ��� ǥ���� ���� �޸� ����.
		*/
		MemDC=CreateCompatibleDC(hdc);


		/*
		MyBitmap=LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_AVG3));
		-	��Ʈ�� �ε�.
		*/
		MyBitmap=LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_AVG3));

		/*
		OldBitmap=(HBITMAP)SelectObject(MemDC, MyBitmap);
		-	GDI������Ʈ �ڵ��� �־��� dc�� �����ϰ� �Ѵ�.
		-	���ϰ��� ������ ���õǾ� �ִ� ���� ������ ������Ʈ �ڵ�.
			-	������ ���� �ݵ�� �ʿ���.
		*/
		OldBitmap=(HBITMAP)SelectObject(MemDC, MyBitmap);

		BitBlt(hdc, 0,0,648,365,MemDC,0,0, SRCCOPY);
		//StretchBlt(hdc,0,400, 324, 183, MemDC, 0, 0, 648, 365, SRCCOPY);
		//StretchBlt(hdc, 0, 400, 1296, 730, MemDC, 0, 0, 648, 365, SRCCOPY);

		/*
		SelectObject(MemDC,OldBitmap);
		DeleteObject(MyBitmap);
		-	GDI ������Ʈ�� ����� �ݵ�� �����ؾ���.
			-	GDI ������Ʈ�� �޸� ���ҽ��� �Ҹ��ϱ� ����.
		-	���� ���õǾ� �ִ� GDI ������Ʈ�� ����� �� ����.
		-	���� �ϱ����� ���� ���õǾ� �ִ� ��ü�� ���� ����.
			-	SelectObject(MemDC, DeleteObject(MyBitmap)); 
		*/
		SelectObject(MemDC,OldBitmap);
		DeleteObject(MyBitmap);

		/*
		DeleteDC(MemDC);
		-	�޸� DC ����.
		*/
		DeleteDC(MemDC);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
