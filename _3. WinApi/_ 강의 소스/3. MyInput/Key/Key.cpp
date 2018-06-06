#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass=TEXT("Key");

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
		//	3. TranslateMessage 확인.
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	/*
	WM_CHAR에서 wParam / lParam 용도
	-	wParam	:	어떤 문자키를 눌렀는지 확인.
	-	lParam	:	Alt키등 특수키가 눌려졌는지 체크.
					비트 연산으로 체크.
					메시지 별로 다르다.
	*/
	HDC hdc;
	PAINTSTRUCT ps;
	static TCHAR str[256];
	int len;

	switch (iMessage) {
		//	3-1. TranslateMessage 참고 예제.
		/*
		case WM_KEYDOWN:
			return 0;
		case WM_KEYUP:
			return 0;
		//*/

	case WM_CHAR:
//*
		len=lstrlen(str);
		str[len]=(TCHAR)wParam;
		str[len+1]=0;
		InvalidateRect(hWnd,NULL,FALSE);	//	버퍼 안지우고 갱신.
//*/
/*
		if ((TCHAR)wParam == ' ') {
			str[0]=0;	//	0 다음 char은 무시.
		} else {
			len=lstrlen(str);
			str[len]=(TCHAR)wParam;
			str[len+1]=0;
		}
		InvalidateRect(hWnd,NULL,TRUE);	//	버퍼 지우고 갱신.
										//	2. 무효 영역 참고.
//*/
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
		TextOut(hdc,100,100,str,lstrlen(str));
		EndPaint(hWnd,&ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
