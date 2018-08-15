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
//	�簢������ �����Ͽ� ���� �ȿ� ���ڿ� ���.
//	��, ���簢���� ǥ��.
//	-	hdc		:	DC�� �ڵ�.
//	-	lpStr	:	����� ���ڿ�.
//	-	nCount	:	����� ���ڿ��� ����. -1�̸� ���ڿ� ������ ���.
//	-	lpRect	:	���ڿ��� ��µ��� �簢����.
//	-	uFormat	:	���ڿ� ��� ���.
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rt={100,100,400,300};
	TCHAR *str=TEXT("���� ���� ��ī����"
		"1�� �����е�"
		"ȭ�����Դϴ� ^^"
	);

	switch (iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
		//	���ڿ� ������ ���.
		//	�߾� ���� �� �ڵ����� ����.
		DrawText(hdc,str,-1,&rt,DT_CENTER | DT_WORDBREAK);
		EndPaint(hWnd,&ps);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

