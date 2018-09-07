//======================================================
#include <windows.h>
//======================================================
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass=TEXT("TextOut");
//======================================================
int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance ,LPSTR lpszCmdParam,int nCmdShow)
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

}//	int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance ,LPSTR lpszCmdParam,int nCmdShow)
//======================================================
//*
//	1.	GetDC / ReleaseDC
//		-	DC�� ��� �Ϲ����� ���.
//	2.	ȭ������� �̵�, ũ�� ���� �ϸ� ���ڿ��� �Ϻ� �Ǵ� ���� �����.
//		-	�ü���� ���� �������� ȭ���� ���� �� ���������� �ʱ� ����.
//		-	�ذ�å :	ȭ���� �������� ���� ���ڿ��� ����ؾ� ��.
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	//	PAINTSTRUCT ps;

	switch (iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_LBUTTONDOWN:
		hdc = GetDC(hWnd);
		//	hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc,100,100,TEXT("Beautiful Korea"),15);		
		ReleaseDC(hWnd, hdc);
		//	EndPaint(hWnd, &ps);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
//*/
//======================================================
/*
//	3.	�ü���� �������� �Ϻΰ� �������ٴ� ����� WM_PAINT �޽����� ���Ͽ� �˸���.
//	4.	BeginPaint / EndPaint
//		-	WM_PAINT �޽��� ������ �׸� �׸��� �غ� �ϴ� ���� �������� �Լ�.
//		-	�ٸ� �޽������� ����� �� ����.
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
		//	hdc = GetDC(hWnd);
		TextOut(hdc,100,100,TEXT("Beautiful Korea"),15);
		//	ReleaseDC(hWnd, hdc);
		EndPaint(hWnd,&ps);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
//*/
//======================================================
/*
//	BOOL TextOut(HDC hdc, int nXStart, int nYStart, LPCTSTR lpStr, int cbStr )
//	���� ¥�� ���ڿ� ���.
//	-	hdc					:	DC�� �ڵ�.
//	-	nXStart, nYStart	:	���ڿ� ��� ��ǥ.
//								������ �۾����� ���� ����.
//	-	lpStr				:	����� ���ڿ�.
//	-	cbStr				:	����� ���ڿ��� ����.

//	SetTextAlign(HDC hdc, UINT fMode)
//	���� ���� ����.
//	-	hdc					:	DC�� �ڵ�.
//	-	fMode				:	���� ���.
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
				
		SetTextAlign(hdc, TA_CENTER);		
		TextOut(hdc,200,60,TEXT("Beautiful Korea"),15);		
		//	DC�� ���� �Ӽ� ������ �� ���� ��¿� �ϰ� ����ȴ�.
		//	SetTextAlign(hdc, TA_LEFT);
		TextOut(hdc,200,80,TEXT("is My"),5);
		TextOut(hdc,200,100,TEXT("Lovely Home Country"),19);

		EndPaint(hWnd,&ps);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
//*/
//======================================================
/*
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
		//	CP( Current Position )
		//	-	�ؽ�Ʈ ����� Ŀ�� ����. ���� ���ڰ� ��µ� ��ġ�� Ŀ���� ǥ��.
		//	-	�׷��� ��忡�� ���� �׷����� ��µ� ��ġ�� CP�� ������ ����.
		//	-	TA_UPDATECP�� �����ϸ� �����ġ�� �����ϴ� �μ��� �����ϰ� CP�� ��ġ�� ���ڿ� ���.
		//	-	����� CP�� ���ڿ� �ٷ� ���� ��ġ�� �̵���Ŵ.
		SetTextAlign(hdc, TA_UPDATECP);
		TextOut(hdc,200,60,TEXT("One "),4);
		TextOut(hdc,200,80,TEXT("Two "),4);
		TextOut(hdc,200,100,TEXT("Three"),5);
		EndPaint(hWnd,&ps);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
//*/
//======================================================