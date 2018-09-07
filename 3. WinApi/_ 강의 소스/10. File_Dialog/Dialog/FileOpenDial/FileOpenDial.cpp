#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("FileOpenDial");

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

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	TCHAR *Mes=TEXT("마우스 왼쪽 버튼을 누르십시오");
	OPENFILENAME OFN;
	TCHAR str[300];
	TCHAR lpstrFile[MAX_PATH]="";

	switch (iMessage) {
	case WM_LBUTTONDOWN:
		memset(&OFN, 0, sizeof(OPENFILENAME));				//	OPENFILENAME 구조체 멤버의 대부분은 디폴트가 0 또는 NULL.

		OFN.lStructSize = sizeof(OPENFILENAME);				//	구조체의 크기. 버전 확인용.

		OFN.hwndOwner=hWnd;									//	대화상자의 소유자.

		OFN.lpstrFilter=TEXT("모든 파일(*.*)\0*.*\0");		//	필터.	"파일 형식\0필터"

		OFN.lpstrFile=lpstrFile;							//	파일 이름 에디트에 처음 나타낼 파일명 지정.
															//	사용자가 최종적으로 선택한 파일의 경로.
															//	충분한 길이의 버퍼를 제공하지 않으면 위험.(MAX_PATH 이상)

		OFN.nMaxFile=MAX_PATH;								//	lpstrFile의 길이.

		if (GetOpenFileName(&OFN)!=0)
		{
			wsprintf(str,TEXT("%s 파일을 선택했습니다."),OFN.lpstrFile);
			MessageBox(hWnd,str,TEXT("파일 열기 성공"),MB_OK);
		}
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd, &ps);
		TextOut(hdc,10,10,Mes,lstrlen(Mes));
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
