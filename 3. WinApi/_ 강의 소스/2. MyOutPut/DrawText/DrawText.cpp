//	http://www.soen.kr/xe/?mid=question&document_srl=19415
#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass=TEXT("DrawText");

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
//	DrawText(HDC hdc, LPCTSTR lpStr, int nCount, LPRECT lpRect, UINT uFormat)
//	사각영역을 정의하여 영역 안에 문자열 출력.
//	단, 직사각형만 표현.
//	-	hdc		:	DC의 핸들.
//	-	lpStr	:	출력할 문자열.
//	-	nCount	:	출력할 문자열의 길이. -1이면 문자열 끝까지 출력.
//	-	lpRect	:	문자열이 출력도리 사각영역.
//	-	uFormat	:	문자열 출력 방식.
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rt={100,100,400,300};
	TCHAR *str=TEXT("굿잡 게임 아카데미"
		"1기 여러분들"
		"화이팅입니다 ^^"
	);

	switch (iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
		//	문자열 끝까지 출력.
		//	중앙 정렬 및 자동개행 적용.
		DrawText(hdc,str,-1,&rt,DT_CENTER | DT_WORDBREAK);
		EndPaint(hWnd,&ps);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

