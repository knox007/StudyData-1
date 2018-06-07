#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass=TEXT("MyTimer");

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
		  ,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
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
/*
UINT SetTimer( HWND hWnd, UINT nIDEvent, UINT uElapse, TIMERPROC lpTimerFunc)
	
	hWnd		:	타이머 메시지를 받을 윈도우.
					보통 WndProc의 hWnd를 그대로 사용.
	
	nIDEvent	:	타이머의 ID.

	uElapse		:	타이머의 주기.
					단위는 1/1000초.
					이 값이 1이라고 해서 타이머 메시지가 초당 1000번 발생하진 않는다.
					1초에 100회 이상 발생하지 않음.

	lpTimerFunc	:	타이머 메시지가 발생할때 마다 호출될 함수.



*/
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	SYSTEMTIME st;
	static TCHAR sTime[128];
	static RECT rt={100,100,400,120};

	switch (iMessage) {
	case WM_CREATE:
		SetTimer(hWnd,1,100,NULL);
//		SendMessage(hWnd, WM_TIMER, 1, 0);
		return 0;
	case WM_TIMER:
		/*
		wParam	:	타이머 ID.
		lParam	:	타이머 메시지 발생시 호출될 함수의 번지.
		*/
		GetLocalTime(&st);
		wsprintf(sTime,TEXT("지금은 %d시 %d분 %d초 입니다."),
			st.wHour,st.wMinute,st.wSecond);
		InvalidateRect(hWnd,NULL,TRUE);
//		InvalidateRect(hWnd,&rt,TRUE);
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
		TextOut(hdc,100,100,sTime,lstrlen(sTime));
		EndPaint(hWnd,&ps);
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd,1);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
