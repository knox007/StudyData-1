
#include "_StdAfx.h"


CMain*	g_pApp	= NULL;


LRESULT WINAPI WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	return g_pApp->MsgProc(hWnd, msg, wParam, lParam);
}



INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{

	g_pApp	= new CMain;

	if(FAILED(g_pApp->Create(hInst)))
		return -1;

	INT	msg = g_pApp->Run();

	delete g_pApp;
	g_pApp = NULL;

	return msg;

}