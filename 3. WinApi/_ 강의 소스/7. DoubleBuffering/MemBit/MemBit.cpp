#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("MemBit");

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


/* ȭ�鿡 ���� �׸���
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	int i;
	HBRUSH MyBrush, OldBrush;
	int x,y;
	
	switch (iMessage)
	{

	case WM_ERASEBKGND:
		return 0;

	case WM_PAINT:
		hdc=BeginPaint(hWnd, &ps);
		for (i=0;i<5000;i++)
		{
			MyBrush=CreateSolidBrush(RGB(rand()%256, rand()%256, rand()%256));
			OldBrush=(HBRUSH)SelectObject(hdc,MyBrush);

			x=rand()%720;
			y=rand()%520;
			Ellipse(hdc,x,y,x+rand()%50+30,y+rand()%50+30);

			SelectObject(hdc,OldBrush);
			DeleteObject(MyBrush);
		}
		EndPaint(hWnd, &ps);
		return 0;
	
	case WM_LBUTTONDOWN:
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
//*/


//*
void DrawBitmap(HDC hdc,int x,int y,HBITMAP hBit)
{
	HDC MemDC;
	HBITMAP OldBitmap;
	int bx,by;
	BITMAP bit;

	MemDC=CreateCompatibleDC(hdc);
	OldBitmap=(HBITMAP)SelectObject(MemDC, hBit);

	GetObject(hBit,sizeof(BITMAP),&bit);
	bx=bit.bmWidth;
	by=bit.bmHeight;

	BitBlt(hdc,x,y,bx,by,MemDC,0,0,SRCCOPY);

	SelectObject(MemDC,OldBitmap);
	DeleteDC(MemDC);
}

// ���� ����
HBITMAP MemBit;			// ���� �޸� ��Ʈ��

// ���� �޸� ��Ʈ�ʿ� �׸��� �̸� �׷� �д�.
void Ready(HWND hWnd)
{
	int i;
	HBITMAP hOldBmp;
	HDC hdc, MemDC;
	hdc=GetDC(hWnd);
	HBRUSH MyBrush, OldBrush;
	int x,y;
		
	//	�޸� DC ����.
	MemDC=CreateCompatibleDC(hdc);

	// �̹� ��Ʈ���� ������� ������ �����.
	if (MemBit)
		DeleteObject(MemBit);

	// ������ũ�� ��Ʈ���� �����.
	MemBit = CreateCompatibleBitmap(hdc, 800, 600);

	//	�޸� DC�� ������ũ�� ��Ʈ���� �����Ѵ�.
	//	-	�޸� DC�� ����ȭ���� ��.
	hOldBmp=(HBITMAP)SelectObject(MemDC, MemBit);

	// �޸� ��Ʈ���� ������� ä�� �� �������� Ÿ�� 5000���� �׸���.
	PatBlt(MemDC,0,0,800,600,WHITENESS);
	for (i=0;i<5000;i++) {
		MyBrush=CreateSolidBrush(RGB(rand()%256, rand()%256, rand()%256));
		OldBrush=(HBRUSH)SelectObject(MemDC,MyBrush);
		x=rand()%720;
		y=rand()%520;
		Ellipse(MemDC,x,y,x+rand()%50+30,y+rand()%50+30);
		SelectObject(MemDC,OldBrush);
		DeleteObject(MyBrush);
	}

	// �������� �Ѵ�.
	SelectObject(MemDC, hOldBmp);
	DeleteDC(MemDC);
	ReleaseDC(hWnd, hdc);
}


// ���� ȭ�鿡 �׸���
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (iMessage) {
	case WM_PAINT:
		hdc=BeginPaint(hWnd, &ps);
		DrawBitmap(hdc,0,0,MemBit);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_LBUTTONDOWN:
		Ready(hWnd);
		InvalidateRect(hWnd, NULL, FALSE);
		return 0;
	case WM_DESTROY:
		if (MemBit)
			DeleteObject(MemBit);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
//*/



