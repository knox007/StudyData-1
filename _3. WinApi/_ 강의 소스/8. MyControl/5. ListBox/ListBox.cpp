#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("MyListBox");

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

#define ID_LISTBOX 100
TCHAR *Items[]={TEXT("사과"),TEXT("오렌지"),TEXT("메론"),TEXT("포도"), TEXT("딸기")};
HWND hList;
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	int i;
	TCHAR str[128];
	switch (iMessage) {
	case WM_CREATE:
		hList = CreateWindow(	TEXT("listbox"),
								NULL,
								WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY,	//	부모 윈도우로 통지 메시지 보내기
								10,10,80,85,
								hWnd,
								(HMENU)ID_LISTBOX,
								g_hInst,
								NULL);
		for (i=0;i<5;i++)
			SendMessage(hList,LB_ADDSTRING,0,(LPARAM)Items[i]);	//	항목 추가.
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_LISTBOX:
			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE:	//	선택 변경.
				i=SendMessage(hList, LB_GETCURSEL,0,0);			//	현재 선택된 항목의 번호(Index) 전달.
				SendMessage(hList, LB_GETTEXT, i, (LPARAM)str);	//	지정한 항목의 문자열을 전달.
				SetWindowText(hWnd, str);
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
