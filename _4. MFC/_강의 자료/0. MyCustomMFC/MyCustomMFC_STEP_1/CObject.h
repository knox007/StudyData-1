//===================================================
#pragma once
#include<Windows.h>
//===================================================
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

	// message handler
	virtual void OnCreate() = 0;
	virtual void OnDraw() = 0;
	virtual void OnDestroy() = 0;
	virtual void OnLButtonDown() = 0;

};//class CObject
//===================================================
extern CObject* g_pObject;