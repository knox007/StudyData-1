#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("BrowseFolder");

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

#include <shlobj.h>
BOOL BrowseFolder(HWND hParent, LPCTSTR szTitle, LPCTSTR StartPath, TCHAR *szFolder);

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	TCHAR *Mes=TEXT("왼쪽 마우스 버튼을 눌러 폴더를 선택하시오.");
	static TCHAR StartPath[MAX_PATH];
	TCHAR Folder[MAX_PATH];

	switch (iMessage) {
	case WM_CREATE:
		hWndMain=hWnd;
		return 0;
	case WM_LBUTTONDOWN:
		if (BrowseFolder(hWnd,TEXT("폴더를 선택하시오"),StartPath,Folder))	//	3.	디렉토리 선택 참고.
		{
			MessageBox(hWnd,Folder,TEXT("선택한 폴더"),MB_OK);
			lstrcpy(StartPath,Folder);
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

int CALLBACK BrowseCallbackProc(HWND hwnd,UINT uMsg,LPARAM lParam,LPARAM lpData)
{
	switch (uMsg) {
	case BFFM_INITIALIZED:
		if (lpData != NULL) {
			SendMessage(hwnd,BFFM_SETSELECTION,TRUE,(LPARAM)lpData);
		}
		break;
	}
	return 0;
}

BOOL BrowseFolder(	HWND hParent,		//	부모윈도우 핸들.
					LPCTSTR szTitle,	//	타이틀 바 캡션.
					LPCTSTR StartPath,	//	시작 디렉토리.
					TCHAR *szFolder		//	선택한 폴더를 얻기위한 버퍼.
				)
{
	LPMALLOC pMalloc;
	LPITEMIDLIST pidl;
	BROWSEINFO bi;

	bi.hwndOwner = hParent;				//	부모윈도우 핸들.
	bi.pidlRoot = NULL;
	bi.pszDisplayName = NULL;
	bi.lpszTitle = szTitle ;			//	타이틀 바 캡션.
	bi.ulFlags = 0;
	bi.lpfn = BrowseCallbackProc;;
	bi.lParam = (LPARAM)StartPath;		//	시작 디렉토리.
						
	pidl = SHBrowseForFolder(&bi);

	if (pidl == NULL) {
		return FALSE;
	}
	SHGetPathFromIDList(pidl, szFolder);	//	선택한 폴더를 얻기위한 버퍼.

	if (SHGetMalloc(&pMalloc) != NOERROR) {
		return FALSE;
	}
	pMalloc->Free(pidl);
	pMalloc->Release();
	return TRUE;
}