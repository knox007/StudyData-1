#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass=TEXT("GoodJob MessageBox");

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

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	switch (iMessage) {

	case WM_CREATE:

		//	������ Ÿ��Ʋ ���ڿ� �б�.
		TCHAR str[128];
		GetWindowText(hWnd, str, strlen(str));
		MessageBox(hWnd, str, TEXT("WM_CREATE"), MB_OK);

		return 0;
	case WM_LBUTTONDOWN:
		
		//	������ Ÿ��Ʋ ���ڿ� ����.
		wsprintf(str, TEXT("AAA = %d"), 100);
		SetWindowText(hWnd, str);

		//	�޽��� �ڽ� ���ϰ� Ȯ��.
		if (MessageBox(hWnd, TEXT("���� ��ī���� �л��Դϱ�?"), TEXT("��ü�� ������!!"), MB_YESNO) == IDYES)
			MessageBox(hWnd, TEXT("�� �׷����ϴ�!!"), TEXT("�ź�Ȯ��"), MB_OK);
		else
			MessageBox(hWnd, TEXT("�ƴѵ���!!"), TEXT("�ź� ��Ȯ��"), MB_OK);
		
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
