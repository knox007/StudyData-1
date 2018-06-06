#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("Mless");
int x;
int y;
TCHAR str[128];
HWND hMDlg;

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
	
	while (GetMessage(&Message,NULL,0,0))
	{
		/*
		5.	메시지 루프 처리
			IsDialogMessage	:	메시지가 대화상자를 위한 메시지인지 검사 후
								맞다면 메시지를 대화상자로 전달.
								예)	Tab 키에 의한 컨트롤 포커스 이동.
									Enter 키에 의한 디폴트 버튼 클릭.
			모델리스 대화상자가 2개 이상이라면 그 수만큼 똑같은 조건문을 반복 처리.

		*/
		if (!IsWindow(hMDlg) || !IsDialogMessage(hMDlg,&Message)) {
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}
	return (int)Message.wParam;
}

#include "resource.h"
BOOL CALLBACK MlessDlgProc(HWND hDlg,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	switch (iMessage) {
	case WM_INITDIALOG:
		SetDlgItemText(hDlg,IDC_STR,str);
		SetDlgItemInt(hDlg,IDC_X,x,FALSE);
		SetDlgItemInt(hDlg,IDC_Y,y,FALSE);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		/*
		3.	컨트롤 -> 대화상자 통신
			모델리스 형은 항상 열려 있으므로
			OK, Cancel 버튼이 논리적으로 어울리지 않아서 
			ID_CHANGE, ID_CLOSE를 추가, 수정했음.
		*/
		case ID_CHANGE:
			GetDlgItemText(hDlg,IDC_STR,str,128);
			x=GetDlgItemInt(hDlg,IDC_X,NULL,FALSE);
			y=GetDlgItemInt(hDlg,IDC_Y,NULL,FALSE);
			InvalidateRect(hWndMain,NULL,TRUE);
			return TRUE;
		case IDCANCEL:
		case ID_CLOSE:
			/*
			4.	대화상자 파괴시 EndDialog이 아닌 DestroyWindow 함수를 호출.
				hMDlg = NULL 처리를 해줌으로써 재생성 가능.
				IDCANCEL시에도 종료 처리해줘야함.
				-	IDCANCEL는 닫기버튼 클릭시에도 호출됨.
			*/
			DestroyWindow(hMDlg);
			hMDlg=NULL;
			return TRUE;
		}
		break;
	}
	return FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (iMessage) {
	case WM_CREATE:
		hWndMain=hWnd;
		x=100;
		y=100;
		lstrcpy(str,TEXT("String"));
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd, &ps);
		TextOut(hdc,x,y,str,lstrlen(str));
		EndPaint(hWnd, &ps);
		return 0;
	case WM_LBUTTONDOWN:
		//	0.	IsWindow
		//		-	원형 :	BOOL IsWindow( HWND hWnd )
		//					hWnd가 유효한 윈도우인가 확인.
		//		-	동일한 윈도우가 두번 생성되지 않도록 필터링.
		if (!IsWindow(hMDlg))
		{
			//	1.	모델리스형 대화 상자 생성.
			//		-	리턴값은 대화 상자의 핸들
			//		-	인자값은 DialogBox와 동일.			
			hMDlg = CreateDialog(	g_hInst,						//	대화상자 리소스를 가진 인스턴스의 핸들.
									MAKEINTRESOURCE(IDD_DIALOG1),	//	대화상자 템플리트의 리소스 ID.
									hWnd,							//	대화상자를 소유할 부모 윈도우 핸들.
									MlessDlgProc);					//	대화상자 프로시저.

			//	2.	모델리스형 대화 상자 출력.
			ShowWindow(hMDlg,SW_SHOW);
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

