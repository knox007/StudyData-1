#include <windows.h>
//----------------------------------------
//	�������� ��� ���
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
LPCTSTR lpszClass=TEXT("Share");

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

TCHAR Mes[256];
HANDLE hFile;
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (iMessage) {
		//----------------------------------------
	case WM_CREATE:
		SetWorkDirectory();
		return 0;
		//----------------------------------------
	case WM_LBUTTONDOWN:
		if (hFile) {
			lstrcpy(Mes,"������ �̹� ������ �ֽ��ϴ�");
		} else {
			hFile=CreateFile(
				"TestFile.txt",
				GENERIC_READ,
				0,	//				FILE_SHARE_READ
					//				FILE_SHARE_WRITE
					//				FILE_SHARE_DELETE
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
			if (hFile==INVALID_HANDLE_VALUE)
				lstrcpy(Mes,"������ �� �� �����ϴ�");
			else
				lstrcpy(Mes,"������ �������ϴ�");
		}
		InvalidateRect(hWnd,NULL,TRUE);
		return 0;
	case WM_RBUTTONDOWN:
		if (hFile) {
			CloseHandle(hFile);
			hFile=NULL;
			lstrcpy(Mes,"������ �������ϴ�");
			InvalidateRect(hWnd,NULL,TRUE);
		}
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd, &ps);
		TextOut(hdc,50,50,Mes,lstrlen(Mes));
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		if (hFile)
			CloseHandle(hFile);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

