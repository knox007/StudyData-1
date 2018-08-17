#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("MyComboBox");

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

#define ID_COMBOBOX 100
TCHAR *Items[] = { TEXT("사과"),TEXT("오렌지"),TEXT("메론"),TEXT("포도"), TEXT("딸기") };
HWND hCombo;
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	int i;
	TCHAR str[128];
	switch (iMessage) {
	case WM_CREATE:
		hCombo = CreateWindow(	TEXT("combobox"),
								NULL,
								WS_CHILD | WS_VISIBLE | CBS_DROPDOWN,	//	에디트 || 리스트 박스.
								10,10,80,100,
								hWnd,
								(HMENU)ID_COMBOBOX,
								g_hInst,
								NULL);

		for (i=0;i<5;i++)
			SendMessage(hCombo,CB_ADDSTRING,0,(LPARAM)Items[i]);	//	항목 추가.

		SendMessage(hCombo, CB_SETCURSEL, 0, 0);					//	인덱스로 항목 선택.
		return 0;


	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_COMBOBOX:
			switch (HIWORD(wParam)) {
			case CBN_SELCHANGE:			//	선택 변경
				i = SendMessage(hCombo, CB_GETCURSEL,0,0);			//	현재 선택된 항목의 번호(Index) 전달.
				SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)str);	//	지정한 항목의 문자열을 전달.
				SetWindowText(hWnd, str);
				break;
			case CBN_EDITCHANGE:	//	콤보박스의 에디트 갱신.
				GetWindowText(hCombo, str, 128);
				SetWindowText(hWnd,str);
				break;
			}
		}
		return 0;


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
