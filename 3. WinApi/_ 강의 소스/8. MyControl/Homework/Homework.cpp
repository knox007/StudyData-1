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





enum { ID_R1 = 101, ID_R2, ID_R3, ID_R4, ID_R5, ID_R6 }; // ��ư 6���� ����ȭ
HWND r1, r2, r3, r4, r5, r6;
int Graph = 0;
COLORREF Color = RGB(0, 0, 0);

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN MyPen, OldPen;
	static int x, y; //��ǥ ����
	static int bold = 1; // ���� ����(�⺻�� 1����)
	static BOOL bNowDraw = FALSE;

	switch (iMessage) {

	case WM_CREATE:

		CreateWindow(TEXT("button"), TEXT("�β���"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 5, 5, 120, 50, hWnd, (HMENU)0, g_hInst, NULL); // üũ�ڽ��� ���� �׷�
		CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 145, 5, 120, 140, hWnd, (HMENU)1, g_hInst, NULL); // ���� ��ư�� ���� �׷�

		r1 = CreateWindow(TEXT("button"), TEXT("�β���"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 10, 20, 100, 30, hWnd, (HMENU)ID_R1, g_hInst, NULL); //üũ�ڽ�(����)
		r2 = CreateWindow(TEXT("button"), TEXT("������"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 150, 20, 100, 30, hWnd, (HMENU)ID_R2, g_hInst, NULL); // ���� ��ư(�׷����), �������
		r3 = CreateWindow(TEXT("button"), TEXT("������"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 150, 50, 100, 30, hWnd, (HMENU)ID_R3, g_hInst, NULL); // ������
		r4 = CreateWindow(TEXT("button"), TEXT("�Ķ���"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 150, 80, 100, 30, hWnd, (HMENU)ID_R4, g_hInst, NULL); // �Ķ���
		r5 = CreateWindow(TEXT("button"), TEXT("���"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 150, 110, 100, 30, hWnd, (HMENU)ID_R5, g_hInst, NULL); // ���
		r6 = CreateWindow(TEXT("button"), TEXT("�ʱ�ȭ"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 70, 100, 30, hWnd, (HMENU)ID_R6, g_hInst, NULL); // ȭ�� �ʱ�ȭ ������ ��ư

		CheckRadioButton(hWnd, ID_R2, ID_R6, ID_R2); // ���� �ʱ�ȭ�� ����������

		break;

	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case ID_R1:
			if (SendMessage(r1, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
			{
				SendMessage(r1, BM_SETCHECK, BST_CHECKED, 0);
				bold = 5; // üũ�ڽ� üũ�� ���⸦ 5�� ����
			}
			else
			{
				SendMessage(r1, BM_SETCHECK, BST_UNCHECKED, 0);
				bold = 1;  //üũ ������ �ٽ� ����� 1��
			}
			break;

		case ID_R2:
			Color = RGB(0, 0, 0); //����
			break;

		case ID_R3:
			Color = RGB(255, 0, 0); // ����
			break;

		case ID_R4:
			Color = RGB(0, 0, 255); // �Ķ�
			break;

		case ID_R5:
			Color = RGB(0, 255, 0); // ���
			break;

		case ID_R6:
			InvalidateRect(hWnd, NULL, TRUE); // ȭ�� ����
			break;
		}
		return 0;

	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam); // ���콺Ŭ���Ѱ��� ��ǥ�� �Է¹���
		bNowDraw = TRUE; // �׸��� ����
		return 0;

	case WM_MOUSEMOVE:

		if (bNowDraw == TRUE)
		{
			hdc = GetDC(hWnd);
			MyPen = CreatePen(PS_SOLID, bold, Color);
			OldPen = (HPEN)SelectObject(hdc, MyPen);
			MoveToEx(hdc, x, y, NULL); // ���� ��ġ���� ����
			x = LOWORD(lParam);
			y = HIWORD(lParam); // �����̴� ������ ��ǥ�� ���� �Է¹���
			LineTo(hdc, x, y); // �� �߱�
			SelectObject(hdc, OldPen);
			DeleteObject(MyPen);
			ReleaseDC(hWnd, hdc);
		}
		return 0;

	case WM_LBUTTONUP:
		bNowDraw = FALSE; // �׸��� ��
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}