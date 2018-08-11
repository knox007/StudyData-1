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
		hThread = CreateThread(	NULL,			//	������ ���ȼӼ�.
												//	�ڽ� ���μ����� �ڵ��� ������� �ʴ´ٸ� NULL.
								
								0,				//	�������� ����ũ��.
												//	0 : �� ������� ���� ũ�� �Ҵ�.

								ThreadFunc,		//	���� �����带 ������ �Լ�.
												//	�� �Լ��� ����Ǹ� �����嵵 �����.
												//	DWORD WINAPI �Լ��̸�(LPVOID temp)
												//	temp�� CreateThread�� �׹�° �μ��� ����.
			
								NULL,			//	ThreadFunc�� ������ ����.

								0,				//	������ �������� Ư��.
												//		0					:	�ƹ� Ư�� ����.
												//		CREATE_SUSPENDED	:	�����带 ����⸸ �ϰ� ���� ���� ����.

								&ThreadID		//	������ �������� ID.
												//	�������� ID�� �ʿ��� ���� ���� ����.
												//	ȣȯ���� ���� ����.
								);

		CloseHandle(hThread);					//	������ �ڵ� �ݱ�.

		return TRUE;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
