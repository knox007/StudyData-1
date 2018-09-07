#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("Thread");

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

DWORD WINAPI ThreadFunc(LPVOID temp)
{
	HDC hdc;
	BYTE Blue=0;
	HBRUSH hBrush, hOldBrush;
	hdc=GetDC(hWndMain);
	for (;;) {
		Blue+=5;
		Sleep(20);
		hBrush = CreateSolidBrush(RGB(0,0,Blue));
		hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc,10,10,400,200);
		SelectObject(hdc, hOldBrush);
		DeleteObject(hBrush);
	}
	ReleaseDC(hWndMain, hdc);
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	DWORD ThreadID;
	HANDLE hThread;

	switch (iMessage) {
	case WM_CREATE:
		hWndMain=hWnd;
		hThread = CreateThread(	NULL,			//	스레드 보안속성.
												//	자식 프로세스로 핸들을 상속하지 않는다면 NULL.
								
								0,				//	스레드의 스택크기.
												//	0 : 주 스레드와 같은 크기 할당.

								ThreadFunc,		//	실제 스레드를 적용할 함수.
												//	이 함수가 종료되면 스레드도 종료됨.
												//	DWORD WINAPI 함수이름(LPVOID temp)
												//	temp는 CreateThread의 네번째 인수로 지정.
			
								NULL,			//	ThreadFunc로 전달할 인자.

								0,				//	생성할 스레드의 특성.
												//		0					:	아무 특성 없음.
												//		CREATE_SUSPENDED	:	스레드를 만들기만 하고 실행 하지 않음.

								&ThreadID		//	생성된 스레드의 ID.
												//	스레드의 ID가 필요한 경우는 거의 없음.
												//	호환성을 위해 설정.
								);

		CloseHandle(hThread);					//	스레드 핸들 닫기.

		return TRUE;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
