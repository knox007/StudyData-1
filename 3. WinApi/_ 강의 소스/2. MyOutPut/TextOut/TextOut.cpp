//======================================================
#include <windows.h>
//======================================================
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass=TEXT("TextOut");
//======================================================
int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance ,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
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

}//	int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance ,LPSTR lpszCmdParam,int nCmdShow)
//======================================================
//*
//	1.	GetDC / ReleaseDC
//		-	DC를 얻는 일반적인 방법.
//	2.	화면밖으로 이동, 크기 변경 하면 문자열이 일부 또는 전부 사라짐.
//		-	운영체제가 개별 윈도우의 화면을 보관 및 복구해주지 않기 때문.
//		-	해결책 :	화면이 지워질때 마다 문자열을 출력해야 함.
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	//	PAINTSTRUCT ps;

	switch (iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_LBUTTONDOWN:
		hdc = GetDC(hWnd);
		//	hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc,100,100,TEXT("Beautiful Korea"),15);		
		ReleaseDC(hWnd, hdc);
		//	EndPaint(hWnd, &ps);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
//*/
//======================================================
/*
//	3.	운영체제는 윈도우의 일부가 지워졌다는 사실을 WM_PAINT 메시지를 통하여 알린다.
//	4.	BeginPaint / EndPaint
//		-	WM_PAINT 메시지 내에서 그림 그리기 준비를 하는 좀더 전문적인 함수.
//		-	다른 메시지에선 사용할 수 없다.
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
		//	hdc = GetDC(hWnd);
		TextOut(hdc,100,100,TEXT("Beautiful Korea"),15);
		//	ReleaseDC(hWnd, hdc);
		EndPaint(hWnd,&ps);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
//*/
//======================================================
/*
//	BOOL TextOut(HDC hdc, int nXStart, int nYStart, LPCTSTR lpStr, int cbStr )
//	한줄 짜리 문자열 출력.
//	-	hdc					:	DC의 핸들.
//	-	nXStart, nYStart	:	문자열 출력 좌표.
//								윈도우 작업영역 원점 기준.
//	-	lpStr				:	출력할 문자열.
//	-	cbStr				:	출력할 문자열의 길이.

//	SetTextAlign(HDC hdc, UINT fMode)
//	정렬 상태 설정.
//	-	hdc					:	DC의 핸들.
//	-	fMode				:	정렬 모드.
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
				
		SetTextAlign(hdc, TA_CENTER);		
		TextOut(hdc,200,60,TEXT("Beautiful Korea"),15);		
		//	DC에 대한 속성 변경은 그 후의 출력에 일괄 적용된다.
		//	SetTextAlign(hdc, TA_LEFT);
		TextOut(hdc,200,80,TEXT("is My"),5);
		TextOut(hdc,200,100,TEXT("Lovely Home Country"),19);

		EndPaint(hWnd,&ps);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
//*/
//======================================================
/*
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
		//	CP( Current Position )
		//	-	텍스트 모드의 커서 역할. 다음 문자가 출력될 위치를 커서가 표시.
		//	-	그래픽 모드에서 다음 그래픽이 출력될 위치를 CP가 가지고 있음.
		//	-	TA_UPDATECP로 설정하면 출력위치를 지정하는 인수를 무시하고 CP의 위치에 문자열 출력.
		//	-	출력후 CP를 문자열 바로 다음 위치로 이동시킴.
		SetTextAlign(hdc, TA_UPDATECP);
		TextOut(hdc,200,60,TEXT("One "),4);
		TextOut(hdc,200,80,TEXT("Two "),4);
		TextOut(hdc,200,100,TEXT("Three"),5);
		EndPaint(hWnd,&ps);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
//*/
//======================================================