//===================================================
#pragma once
#include<Windows.h>
//====================================================
class CObject
{
protected:
	HWND        _hWnd;
	MSG         msg;
	WNDCLASS	wndclass;

public:
	void InitInstance( TCHAR *pszName, HINSTANCE hInstance, PSTR szCmdLine, int iCmdShow);
	void Run();
	WPARAM ExitInstance();

};//class CObject
//===================================================
extern CObject* g_pObject;