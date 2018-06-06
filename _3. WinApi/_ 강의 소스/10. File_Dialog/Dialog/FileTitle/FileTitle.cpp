#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("FileTitle");

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
	TCHAR szFileTitle[MAX_PATH];
	TCHAR InitDir[MAX_PATH];

	switch (iMessage) {
	case WM_LBUTTONDOWN:
		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner=hWnd;
		OFN.lpstrFilter=TEXT("모든 파일(*.*)\0*.*\0");
		OFN.lpstrFile=lpstrFile;
		OFN.nMaxFile=MAX_PATH;

		OFN.lpstrTitle=TEXT("파일을 선택해 주십시오");	//	대화상자의 캡션 설정.
														//	설정하지 않으면 "열기" 또는 "저장"이 기본으로 사용됨.
		
		OFN.lpstrFileTitle=szFileTitle;					//	선택한 파일의 경로를 제외한 이름만 반환됨.

		OFN.nMaxFileTitle=MAX_PATH;						//	szFileTitle 길이 지정.

		OFN.lpstrDefExt="abc";							//	디폴트 확장자 지정.
														//	"txt","exe"처럼 .은 포함하지 말것.
														//	3자 이상은 무시됨.
		GetWindowsDirectory(InitDir,MAX_PATH);			//	

		OFN.lpstrInitialDir=InitDir;					//	파일 열기 대화상자가 보여줄 시작 위치.
														//	운영체제 버전에 따라 다르며 다소 복잡함.

		if (GetOpenFileName(&OFN)!=0)
		{
			wsprintf(str,
					TEXT("%s 파일을 선택했습니다. 파일명은 %s입니다.")
					TEXT("파일명 오프셋=%d, 확장자 오프셋=%d"),
					lpstrFile,
					szFileTitle,
					OFN.nFileOffset,
					OFN.nFileExtension);

			MessageBox(hWnd,str,"파일 열기 성공",MB_OK);
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

