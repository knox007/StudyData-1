#include <windows.h>
//----------------------------------------
//	실행파일 경로 얻기
#include <Shlwapi.h>
#pragma comment(lib,"Shlwapi.lib")
void SetWorkDirectory()
{
	TCHAR szPath[MAX_PATH] = { 0, };
	GetCurrentDirectory(MAX_PATH, szPath);
	//*
	ZeroMemory(szPath, sizeof(szPath));

	GetModuleFileName(NULL, szPath, MAX_PATH);
	TCHAR *findpp = strrchr(szPath, '\\');
	strset(findpp + 1, '\0');
	SetCurrentDirectory(szPath);
	//*/
}
//----------------------------------------
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("ReadFile");

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

TCHAR buf[1024];
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HANDLE hFile;
	DWORD dwRead;
	RECT rt;
	
	switch (iMessage) {
		//----------------------------------------
	case WM_CREATE:
		SetWorkDirectory();
		return 0;
		//----------------------------------------
	case WM_LBUTTONDOWN:
	{
		hFile = CreateFile("Test.txt",					//	열고자 하는 파일의 경로.
														//	260자 이하일것.(MAX_PATH)

			GENERIC_READ,			//	파일의 엑세스 타입.													
									//	"0. 파일 엑세스 참고"

			0,						//	공유 모드.
									//	"0. 파일 엑세스 참고"

			NULL,					//	리턴된 핸들을 차일드 프로세스로 상속할 것인지 지정.
									//	사용하지 않을때는 NULL.

			OPEN_EXISTING,			//	만들고자(열고자) 하는 파일이 이미 있을 경우 처리.
									//	"0. 파일 엑세스 참고"

			FILE_ATTRIBUTE_NORMAL,	//	파일의 속성과 옵션 설정.

			NULL);					//	새로 만들고자 하는 파일의 추가 속성을 지원하는 템플릿 파일의 핸들.
									//	일반적으로 사용되지 않음. NULL처리.

									//	hFile : 파일을 열거나 생성에 성공시 반횐되는 파일의 핸들.
									//			실패시 INVALID_HANDLE_VALUE 리턴.

		if (hFile != INVALID_HANDLE_VALUE)
		{
			ReadFile(hFile,
				buf,
				1024,
				&dwRead,
				NULL
			);

			//	핸들 닫기.
			CloseHandle(hFile);

			InvalidateRect(hWnd, NULL, TRUE);
		}
	}
	return 0;

	case WM_PAINT:
		hdc=BeginPaint(hWnd, &ps);
		GetClientRect(hWnd,&rt);
		DrawText(hdc,buf,-1,&rt,DT_WORDBREAK);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

