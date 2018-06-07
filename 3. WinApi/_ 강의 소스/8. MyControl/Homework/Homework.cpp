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





enum { ID_R1 = 101, ID_R2, ID_R3, ID_R4, ID_R5, ID_R6 }; // 버튼 6가지 간소화
HWND r1, r2, r3, r4, r5, r6;
int Graph = 0;
COLORREF Color = RGB(0, 0, 0);

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN MyPen, OldPen;
	static int x, y; //좌표 저장
	static int bold = 1; // 굵기 설정(기본이 1굵기)
	static BOOL bNowDraw = FALSE;

	switch (iMessage) {

	case WM_CREATE:

		CreateWindow(TEXT("button"), TEXT("두껍게"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 5, 5, 120, 50, hWnd, (HMENU)0, g_hInst, NULL); // 체크박스를 묶을 그룹
		CreateWindow(TEXT("button"), TEXT("색깔"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 145, 5, 120, 140, hWnd, (HMENU)1, g_hInst, NULL); // 라디오 버튼을 묶을 그룹

		r1 = CreateWindow(TEXT("button"), TEXT("두껍게"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 10, 20, 100, 30, hWnd, (HMENU)ID_R1, g_hInst, NULL); //체크박스(굵게)
		r2 = CreateWindow(TEXT("button"), TEXT("검정색"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 150, 20, 100, 30, hWnd, (HMENU)ID_R2, g_hInst, NULL); // 라디오 버튼(그룹시작), 색상결정
		r3 = CreateWindow(TEXT("button"), TEXT("빨간색"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 150, 50, 100, 30, hWnd, (HMENU)ID_R3, g_hInst, NULL); // 빨강색
		r4 = CreateWindow(TEXT("button"), TEXT("파란색"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 150, 80, 100, 30, hWnd, (HMENU)ID_R4, g_hInst, NULL); // 파란색
		r5 = CreateWindow(TEXT("button"), TEXT("녹색"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 150, 110, 100, 30, hWnd, (HMENU)ID_R5, g_hInst, NULL); // 녹색
		r6 = CreateWindow(TEXT("button"), TEXT("초기화"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 70, 100, 30, hWnd, (HMENU)ID_R6, g_hInst, NULL); // 화면 초기화 누르기 버튼

		CheckRadioButton(hWnd, ID_R2, ID_R6, ID_R2); // 색상 초기화는 검은색으로

		break;

	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case ID_R1:
			if (SendMessage(r1, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
			{
				SendMessage(r1, BM_SETCHECK, BST_CHECKED, 0);
				bold = 5; // 체크박스 체크시 굵기를 5로 만듬
			}
			else
			{
				SendMessage(r1, BM_SETCHECK, BST_UNCHECKED, 0);
				bold = 1;  //체크 해제시 다시 굵기는 1로
			}
			break;

		case ID_R2:
			Color = RGB(0, 0, 0); //검정
			break;

		case ID_R3:
			Color = RGB(255, 0, 0); // 빨강
			break;

		case ID_R4:
			Color = RGB(0, 0, 255); // 파랑
			break;

		case ID_R5:
			Color = RGB(0, 255, 0); // 녹색
			break;

		case ID_R6:
			InvalidateRect(hWnd, NULL, TRUE); // 화면 리셋
			break;
		}
		return 0;

	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam); // 마우스클릭한곳의 좌표를 입력받음
		bNowDraw = TRUE; // 그리기 시작
		return 0;

	case WM_MOUSEMOVE:

		if (bNowDraw == TRUE)
		{
			hdc = GetDC(hWnd);
			MyPen = CreatePen(PS_SOLID, bold, Color);
			OldPen = (HPEN)SelectObject(hdc, MyPen);
			MoveToEx(hdc, x, y, NULL); // 현재 위치까지 지정
			x = LOWORD(lParam);
			y = HIWORD(lParam); // 움직이는 지점의 좌표를 새로 입력받음
			LineTo(hdc, x, y); // 선 긋기
			SelectObject(hdc, OldPen);
			DeleteObject(MyPen);
			ReleaseDC(hWnd, hdc);
		}
		return 0;

	case WM_LBUTTONUP:
		bNowDraw = FALSE; // 그리기 끝
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}