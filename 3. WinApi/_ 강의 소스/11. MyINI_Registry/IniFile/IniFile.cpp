#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("IniFile");

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

char szCurDir[256] = { NULL, };
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	RECT rt;
	TCHAR buf[10];	
	switch (iMessage) {
	case WM_CREATE:

		//	ini파일 경로 설정.
		GetCurrentDirectory(256, szCurDir);
		strcat_s(szCurDir, "\\jackie.ini");

		rt.left=GetPrivateProfileInt("Position", "Left", 0, szCurDir);
		rt.top=GetPrivateProfileInt("Position", "Top", 0, szCurDir);
		rt.right=GetPrivateProfileInt("Position", "Right", 100, szCurDir);
		rt.bottom=GetPrivateProfileInt("Position", "Bottom", 100, szCurDir);
		MoveWindow(hWnd,
			rt.left, rt.top,
			rt.right-rt.left, 
			rt.bottom-rt.top, TRUE);
		return 0;

	case WM_DESTROY:
		GetWindowRect(hWnd, &rt);
		_itoa_s(rt.left, buf, 10);
		WritePrivateProfileString("Position", "Left", buf, szCurDir);
		_itoa_s(rt.top, buf, 10);
		WritePrivateProfileString("Position", "Top", buf, szCurDir);
		_itoa_s(rt.right, buf, 10);
		WritePrivateProfileString("Position", "Right", buf, szCurDir);
		_itoa_s(rt.bottom, buf, 10);
		WritePrivateProfileString("Position", "Bottom", buf, szCurDir);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
//*/