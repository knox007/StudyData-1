#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass=TEXT("Client");

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

/*	WM_CREATE에서 작업영역 크기 조사
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static RECT rt;

	switch (iMessage) {
	case WM_CREATE:
		GetClientRect(hWnd,&rt);
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd, &ps);
		SetTextAlign(hdc,TA_CENTER);
		TextOut(hdc,rt.right/2, rt.bottom/2, TEXT("Center String"),13);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
//*/

/* WM_SIZE에서 작업영역 크기 조사
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static RECT rt;

	switch (iMessage) {
	case WM_SIZE:
		GetClientRect(hWnd, &rt);
		//rt.right=LOWORD(lParam);
		//rt.bottom=HIWORD(lParam);
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd, &ps);
		SetTextAlign(hdc,TA_CENTER);
		TextOut(hdc,rt.right/2, rt.bottom/2, TEXT("Center String"),13);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
//*/

/*	WM_PAINT에서 작업영역 크기 조사
//	-	결과는 같으나 최적화의 관점에서 본다면 비추.
//	-	WM_PAINT는 출력처리만 담당 할 것.
//		그 외 데이터 가공 부분은 관련 메시지에서 할 것.
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rt;

	switch (iMessage) {
	case WM_PAINT:
		hdc=BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rt);
		SetTextAlign(hdc,TA_CENTER);
		TextOut(hdc,rt.right/2, rt.bottom/2, TEXT("Center String"),13);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
//*/

//* WM_MOVE
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rt;
	static TCHAR tmp[100];

	switch (iMessage)
	{
	case WM_MOVE:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);		
		wsprintf(tmp, "x = %d, y = %d", x, y);
		InvalidateRect(hWnd, NULL, TRUE);
	}
	return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rt);
		SetTextAlign(hdc, TA_CENTER);
		TextOut(hdc, rt.right / 2, rt.bottom / 2, tmp, strlen(tmp));
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
//*/
