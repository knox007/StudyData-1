#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("Check");

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
	  ,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	//	������ ��� �귯�ø� ��Ʈ���� ����� ��ġ.
	WndClass.hbrBackground=(HBRUSH)(COLOR_BTNFACE+1);
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
	HDC hdc;
	PAINTSTRUCT ps;
	static HWND chk2StateManual, chk2StateAuto, chk3StateManual, chk3StateAuto;
	static BOOL bEllipse = FALSE;
	switch (iMessage) {
	case WM_CREATE:
		chk2StateManual = CreateWindow(	TEXT("button"),
								TEXT("�� �׸���?"),
								WS_CHILD | WS_VISIBLE | BS_CHECKBOX,		//	2���� ���� ����
								20,20,160,25,
								hWnd,
								(HMENU)0,
								g_hInst,
								NULL);

		chk2StateAuto = CreateWindow(	TEXT("button"),
								TEXT("���� �޽��� ���?"),
								WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,	//	2���� ���� �ڵ�
								20,50,160,25,
								hWnd,
								(HMENU)1,
								g_hInst,
								NULL);

		chk3StateManual = CreateWindow(	TEXT("button"),
								TEXT("3 State"),
								WS_CHILD | WS_VISIBLE | BS_3STATE,			//	3���� ���� ����
								20,80,160,25,
								hWnd,
								(HMENU)2,
								g_hInst,
								NULL);

		chk3StateAuto = CreateWindow(	TEXT("button"),
								TEXT("Auto 3 State"),
								WS_CHILD | WS_VISIBLE | BS_AUTO3STATE,		//	3���� ���� �ڵ�
								20,110,160,25,
								hWnd,
								(HMENU)3,
								g_hInst,
								NULL);
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 0:
			//bEllipse=(BOOL)(SendMessage(chk2StateManual,BM_GETCHECK,0,0)==BST_CHECKED);
			if (SendMessage(chk2StateManual,BM_GETCHECK,0,0)==BST_UNCHECKED)
			{
				SendMessage(chk2StateManual,BM_SETCHECK,BST_CHECKED,0);
				bEllipse = TRUE;
			}
			else
			{
				SendMessage(chk2StateManual,BM_SETCHECK,BST_UNCHECKED,0);
				bEllipse = FALSE;
			}

			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case 2:
			if (SendMessage(chk3StateManual,BM_GETCHECK,0,0)==BST_UNCHECKED)
				SendMessage(chk3StateManual,BM_SETCHECK,BST_CHECKED,0);
			else 
			if (SendMessage(chk3StateManual,BM_GETCHECK,0,0)==BST_INDETERMINATE)
				SendMessage(chk3StateManual,BM_SETCHECK,BST_UNCHECKED,0);
			else
				SendMessage(chk3StateManual,BM_SETCHECK,BST_INDETERMINATE,0);
			break;
		}
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
		
		if (bEllipse == TRUE)
			Ellipse(hdc,200,100,400,200);
		else
			Rectangle(hdc,200,100,400,200);

		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		if (SendMessage(chk2StateAuto,BM_GETCHECK,0,0)==BST_CHECKED)
			MessageBox(hWnd,TEXT("����!!"),TEXT("�˸�"),MB_OK);

		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
