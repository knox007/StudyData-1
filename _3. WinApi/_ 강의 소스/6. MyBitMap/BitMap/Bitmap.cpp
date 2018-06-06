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
		-	인자로 주어진 dc와 동일한 특성의 메모리 DC 반환.
		-	비트맵은 용량이 커서 화면으로 곧바로 추력할 수 없고 메모리 DC에 미리 준비해 놓고 사용.
			-	메모리 DC : 화면 DC와 동일한 특성을 가지며 내부에 출력 표면을 지닌 메모리 영역.
		*/
		MemDC=CreateCompatibleDC(hdc);


		/*
		MyBitmap=LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_AVG3));
		-	비트맵 로딩.
		*/
		MyBitmap=LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_AVG3));

		/*
		OldBitmap=(HBITMAP)SelectObject(MemDC, MyBitmap);
		-	GDI오브젝트 핸들을 주어진 dc에 선택하게 한다.
		-	리턴값은 이전에 선택되어 있던 같은 종류의 오브젝트 핸들.
			-	복구를 위해 반드시 필요함.
		*/
		OldBitmap=(HBITMAP)SelectObject(MemDC, MyBitmap);

		BitBlt(hdc, 0,0,648,365,MemDC,0,0, SRCCOPY);
		//StretchBlt(hdc,0,400, 324, 183, MemDC, 0, 0, 648, 365, SRCCOPY);
		//StretchBlt(hdc, 0, 400, 1296, 730, MemDC, 0, 0, 648, 365, SRCCOPY);

		/*
		SelectObject(MemDC,OldBitmap);
		DeleteObject(MyBitmap);
		-	GDI 오브젝트는 사용후 반드시 삭제해야함.
			-	GDI 오브젝트로 메모리 리소스를 소모하기 때문.
		-	현재 선택되어 있는 GDI 오브젝트는 사용할 수 없음.
		-	삭제 하기전에 현재 선택되어 있는 객체를 선택 해제.
			-	SelectObject(MemDC, DeleteObject(MyBitmap)); 
		*/
		SelectObject(MemDC,OldBitmap);
		DeleteObject(MyBitmap);

		/*
		DeleteDC(MemDC);
		-	메모리 DC 제거.
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
