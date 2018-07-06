#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,
                   PSTR szCmdLine,int iCmdShow)
{
    MessageBox( NULL, "Hello World", "Hello", MB_OK );
    return 0;
}