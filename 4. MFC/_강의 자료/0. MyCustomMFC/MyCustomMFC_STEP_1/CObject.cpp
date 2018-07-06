//===================================================
#include "CObject.h"
//===================================================
CObject* g_pObject;
//===================================================
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_CREATE:
		g_pObject->OnCreate();
		return 0;

	case WM_PAINT:
		g_pObject->OnDraw();
		return 0;

	case WM_DESTROY:
		g_pObject->OnDestroy();
		return 0;

	case WM_LBUTTONDOWN:
		g_pObject->OnLButtonDown();
		return 0;

	}//	switch (iMsg)
	return DefWindowProc(hwnd, iMsg, wParam, lParam);

}//LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
//===================================================
void CObject::InitInstance(TCHAR *pszName, HINSTANCE hInstance, PSTR szCmdLine, int iCmdShow)
{
	_wndClass.style = CS_HREDRAW | CS_VREDRAW;
	_wndClass.lpfnWndProc = WndProc;
	_wndClass.cbClsExtra = 0;
	_wndClass.cbWndExtra = 0;
	_wndClass.hInstance = hInstance;
	_wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	_wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	_wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	_wndClass.lpszMenuName = NULL;
	_wndClass.lpszClassName = pszName;

	RegisterClass(&_wndClass);

	_hWnd = CreateWindow(pszName,
		pszName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(_hWnd, iCmdShow);

}//	void CObject::InitInstance(HINSTANCE hInstance, PSTR szCmdLine,	int iCmdShow)
//===================================================
void CObject::Run()
{
	while (GetMessage(&_msg, NULL, 0, 0))
	{
		TranslateMessage(&_msg);
		DispatchMessage(&_msg);

	}//	while (GetMessage(&msg, NULL, 0, 0))

}//	void CObject::Run()
//===================================================
WPARAM CObject::ExitInstance() { return _msg.wParam; }
//===================================================