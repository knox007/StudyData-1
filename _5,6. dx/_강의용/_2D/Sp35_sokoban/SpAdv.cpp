//
// 1. Original 코드 : 12/12/2006 장청명(청강문화산업대학)
//
// 2. Update 12/29/2006
//
//



#include "_StdAfx.h"


CMain*	g_pApp = NULL;


INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
	CMain d3dApp;

	g_pApp = &d3dApp;

	if(FAILED(d3dApp.Create(hInst)))
		return -1;

	return d3dApp.Run();
}
