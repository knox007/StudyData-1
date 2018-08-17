#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("Radio");

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
	  ,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
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

//	#define문 과의 차이점은???
enum
{ 
	ID_R1 = 101,
	ID_R2,
	ID_R3,
	ID_R4,
	ID_R5,
	ID_R6
};

HWND rbttn_1, rbttn_2, rbttn_3, rbttn_4, rbttn_5, rbttn_6;
int Graph=0;
COLORREF Color=RGB(0,0,0);
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH MyBrush, OldBrush;
	switch (iMessage) {
	case WM_CREATE:
		CreateWindow(	TEXT("button"),
						TEXT("도형"),
						WS_CHILD | WS_VISIBLE | BS_GROUPBOX,	//	그룹 박스 컨트롤
						5,5,120,110,
						hWnd,
						(HMENU)0,
						g_hInst,
						NULL);

		CreateWindow(	TEXT("button"),
						TEXT("색깔"),
						WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
						145,5,120,110,
						hWnd,
						(HMENU)1,
						g_hInst,
						NULL);

		rbttn_1 = CreateWindow(	TEXT("button"),
				TEXT("사각형"),
				WS_CHILD | WS_VISIBLE |	BS_AUTORADIOBUTTON | WS_GROUP,	//	그룹을 이루는 첫번째 라디오 버튼.
				10,20,100,30,
				hWnd,
				(HMENU)ID_R1,
				g_hInst,
				NULL);

		rbttn_2 = CreateWindow(	TEXT("button"),
				TEXT("타원"),
				WS_CHILD | WS_VISIBLE |	BS_AUTORADIOBUTTON,
				10,50,100,30,
				hWnd,
				(HMENU)ID_R2,
				g_hInst,
				NULL);

		rbttn_3 = CreateWindow(	TEXT("button"),
				TEXT("선"),
				WS_CHILD | WS_VISIBLE |	BS_AUTORADIOBUTTON,
				10,80,100,30,
				hWnd,
				(HMENU)ID_R3,
				g_hInst,
				NULL);

		rbttn_4 = CreateWindow(	TEXT("button"),
				TEXT("검정색"),
				WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,	//	그룹을 이루는 첫번째 라디오 버튼.
				150,20,100,30,
				hWnd,
				(HMENU)ID_R4,
				g_hInst,
				NULL);

		rbttn_5 = CreateWindow(	TEXT("button"),
				TEXT("빨간색"),
				WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
				150,50,100,30,
				hWnd,
				(HMENU)ID_R5,
				g_hInst,
				NULL);

		rbttn_6 = CreateWindow(TEXT("button"),
				TEXT("파란색"),
				WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
				150,80,100,30,
				hWnd,
				(HMENU)ID_R6,
				g_hInst,
				NULL);

		CheckRadioButton(hWnd, ID_R1, ID_R3, ID_R1);
		CheckRadioButton(hWnd, ID_R4, ID_R6, ID_R4);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_R1:
			Graph=0;
			break;
		case ID_R2:
			Graph=1;
			break;
		case ID_R3:
			Graph=2;
			break;
		case ID_R4:
			Color=RGB(0,0,0);
			break;
		case ID_R5:
			Color=RGB(255,0,0);
			break;
		case ID_R6:
			Color=RGB(0,0,255);
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
		MyBrush=CreateSolidBrush(Color);
		OldBrush=(HBRUSH)SelectObject(hdc,MyBrush);
		switch (Graph) {
		case 0:
			Rectangle(hdc,10,200,200,300);
			break;
		case 1:
			Ellipse(hdc,10,200,200,300);
			break;
		case 2:
			MoveToEx(hdc,10,200,NULL);
			LineTo(hdc,200,300);
			break;
		}
		SelectObject(hdc,OldBrush);
		DeleteObject(MyBrush);
		EndPaint(hWnd,&ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

/*
	case WM_COMMAND:
		if (HIWORD(wParam) == BN_CLICKED) {
			InvalidateRect(hWnd, NULL, TRUE);
		}
		return 0;
	case WM_PAINT:
		if (SendMessage(r1,BM_GETCHECK,0,0)==BST_CHECKED) Graph=0;
		if (SendMessage(r2,BM_GETCHECK,0,0)==BST_CHECKED) Graph=1;
		if (SendMessage(r3,BM_GETCHECK,0,0)==BST_CHECKED) Graph=2;
		if (SendMessage(r4,BM_GETCHECK,0,0)==BST_CHECKED) Color=RGB(0,0,0);
		if (SendMessage(r5,BM_GETCHECK,0,0)==BST_CHECKED) Color=RGB(255,0,0);
		if (SendMessage(r6,BM_GETCHECK,0,0)==BST_CHECKED) Color=RGB(0,0,255);
		hdc=BeginPaint(hWnd,&ps);
		....
//*/
