#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("Registry");

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
	RECT rt;
	HKEY key;
	DWORD dwDisp;
	DWORD Size;
	switch (iMessage) {
	case WM_CREATE:
		RegCreateKeyEx(HKEY_CURRENT_USER, 
			"Software\\JackieSoft\\RegiTest\\Position",0,NULL,
			REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,NULL,&key,&dwDisp);
		Size=sizeof(LONG);
		if (RegQueryValueEx(	key,
								"Left",
								0,
								NULL,					//	읽은 값의 타입을 대입받을 변수의 포인터.
														//	DWORD형의 포인터. 불필요할 경우 NULL.
								(LPBYTE)&rt.left,		//	읽혀진 값을 받을 변수의 포인터.
								&Size					//	변수의 크기값을 가지는 변수의 주소.
							)			
			!=ERROR_SUCCESS)
			rt.left=0;
		Size=sizeof(LONG);
		if (RegQueryValueEx(key, "Top", 0, NULL,(LPBYTE)&rt.top, &Size)
			!=ERROR_SUCCESS)
			rt.top=0;
		Size=sizeof(LONG);
		if (RegQueryValueEx(key, "Right", 0, NULL,(LPBYTE)&rt.right, &Size)
			!=ERROR_SUCCESS)
			rt.right=100;
		Size=sizeof(LONG);
		if (RegQueryValueEx(key, "Bottom", 0, NULL,(LPBYTE)&rt.bottom, &Size)
			!=ERROR_SUCCESS)
			rt.bottom=100;;
		
		RegCloseKey(key);	//	레지스트리 키를 닫음.
							//	레지스트리 키도 메모리를 소모.

		MoveWindow(hWnd, rt.left, rt.top, rt.right-rt.left, 
			rt.bottom-rt.top, TRUE);
		return 0;
	case WM_DESTROY:
		RegCreateKeyEx(HKEY_CURRENT_USER, 
			"Software\\JackieSoft\\RegiTest\\Position",0,NULL,
			REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,NULL,&key,&dwDisp);
		GetWindowRect(hWnd, &rt);
		
		RegSetValueEx(	key,				//	RegCreateKeyEx로 생성된 키 핸들.
						"Left",				//	값의 이름을 지정.
						0,					//	사용하지 않음. 0으로 처리.
						REG_DWORD,			//	값의 데이터 타입.
						(LPBYTE)&rt.left,	//	저장하고자 하는 데이터의 포인터.
						sizeof(LONG)		//	데이터의 크기값.
					);

		RegSetValueEx(key, "Top",0,REG_DWORD,(LPBYTE)&rt.top,sizeof(LONG));
		RegSetValueEx(key, "Right",0,REG_DWORD,(LPBYTE)&rt.right,sizeof(LONG));
		RegSetValueEx(key, "Bottom",0,REG_DWORD,(LPBYTE)&rt.bottom,sizeof(LONG));
		RegCloseKey(key);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

