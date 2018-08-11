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
		hFile = CreateFile("Test.txt",					//	������ �ϴ� ������ ���.
														//	260�� �����ϰ�.(MAX_PATH)

			GENERIC_READ,			//	������ ������ Ÿ��.													
									//	"0. ���� ������ ����"

			0,						//	���� ���.
									//	"0. ���� ������ ����"

			NULL,					//	���ϵ� �ڵ��� ���ϵ� ���μ����� ����� ������ ����.
									//	������� �������� NULL.

			OPEN_EXISTING,			//	�������(������) �ϴ� ������ �̹� ���� ��� ó��.
									//	"0. ���� ������ ����"

			FILE_ATTRIBUTE_NORMAL,	//	������ �Ӽ��� �ɼ� ����.

			NULL);					//	���� ������� �ϴ� ������ �߰� �Ӽ��� �����ϴ� ���ø� ������ �ڵ�.
									//	�Ϲ������� ������ ����. NULLó��.

									//	hFile : ������ ���ų� ������ ������ ��Ⱥ�Ǵ� ������ �ڵ�.
									//			���н� INVALID_HANDLE_VALUE ����.

		if (hFile != INVALID_HANDLE_VALUE)
		{
			ReadFile(hFile,
				buf,
				1024,
				&dwRead,
				NULL
			);

			//	�ڵ� �ݱ�.
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

