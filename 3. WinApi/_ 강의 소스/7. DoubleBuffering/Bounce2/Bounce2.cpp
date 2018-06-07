#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("Bounce2");

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

#define R 20
int x,y;
int xi,yi;
HBITMAP hBit;
void OnTimer()
{
	RECT crt;
	HDC hdc,hMemDC;
	HBITMAP OldBit;
	HPEN hPen,OldPen;
	HBRUSH hBrush,OldBrush;
	int i;

	GetClientRect(hWndMain,&crt);
	hdc=GetDC(hWndMain);
	
	//	화면 DC와 호환되는 DC 생성.
	hMemDC=CreateCompatibleDC(hdc);
	
	//	오프스크린 비트맵 생성.
	if (hBit == NULL)
		hBit = CreateCompatibleBitmap(hdc, crt.right, crt.bottom);
	
	//	가상 DC 생성.
	OldBit=(HBITMAP)SelectObject(hMemDC,hBit);

	//	가상 DC 초기화.
	FillRect(hMemDC,&crt,GetSysColorBrush(COLOR_WINDOW));

	//	타원 이동
	if (x <= R || x >= crt.right-R) {
		xi*=-1;
	}
	if (y <= R || y >= crt.bottom-R) {
		yi*=-1;
	}
	x+=xi;
	y+=yi;

	//	빨간 색 설정
	hPen = CreatePen(PS_INSIDEFRAME, 1, RGB(255, 0, 0));
	OldPen = (HPEN)SelectObject(hMemDC, hPen);
	//	세로 라인 그리기.
	for (i=0;i<crt.right;i+=10) {
		MoveToEx(hMemDC,i,0,NULL);
		LineTo(hMemDC,i,crt.bottom);
	}

	//	파란 색 설정.
	hPen = CreatePen(PS_INSIDEFRAME, 1, RGB(0, 0, 255));
	OldPen = (HPEN)SelectObject(hMemDC, hPen);
	//	가로 라인 그리기.
	for (i=0;i<crt.bottom;i+=10) {
		MoveToEx(hMemDC,0,i,NULL);
		LineTo(hMemDC,crt.right,i);
	}

	//	빨간 테두리 색 설정.
	hPen=CreatePen(PS_INSIDEFRAME,2,RGB(255,0,0));
	//	가상 DC에 설정.
	OldPen=(HPEN)SelectObject(hMemDC,hPen);

	//	파란 브러쉬 선택.
	hBrush=CreateSolidBrush(RGB(0,0,255));
	//	가상 DC에 설정.
	OldBrush=(HBRUSH)SelectObject(hMemDC,hBrush);

	//	타원 그리기.
	Ellipse(hMemDC,x-R,y-R,x+R,y+R);
	
	//	펜, 브러쉬 제거.
	DeleteObject(SelectObject(hMemDC,OldPen));
	DeleteObject(SelectObject(hMemDC,OldBrush));

	//	현재 가상 DC에 적용된 비트맵 핸들 제거.
	SelectObject(hMemDC,OldBit);
	//	가상 DC 제거.
	DeleteDC(hMemDC);
	ReleaseDC(hWndMain,hdc);
	InvalidateRect(hWndMain,NULL,FALSE);
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

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
	case WM_PAINT:
		hdc=BeginPaint(hWnd, &ps);
		if (hBit) DrawBitmap(hdc,0,0,hBit);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		if (hBit) {
			DeleteObject(hBit);
		}
		PostQuitMessage(0);
		KillTimer(hWnd,1);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
