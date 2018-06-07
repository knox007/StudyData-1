//==============================================
#include <windows.h>
#include "CObject.h"
#include "CView.h"
//==============================================
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, PSTR szCmdLine,int iCmdShow)
{
	g_pObject = &g_View;
    
	g_pObject->InitInstance(TEXT("CUSTOM MFC STEP 2"), hInstance,szCmdLine,iCmdShow);
    
	g_pObject->Run();

    return g_pObject->ExitInstance();

}//	int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, PSTR szCmdLine,int iCmdShow)
//==============================================