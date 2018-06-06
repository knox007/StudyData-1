//=============================================================
#include <windows.h>
//=============================================================
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LPCTSTR g_lpszClass = TEXT("First");
//=============================================================
/*
WinMain			:	프로그램 시작점을 지정하는 고유함수.
					c/c++의 main 역할.
					윈도우 초기화 작업.
					구성 내용이 거의 비슷함.

APIENTRY		:	윈도우즈의 표준 호출 규약인 __stdcall을 사용한다는 뜻.

hInstance		:	프로그램 고유 ID.
					운영체제는 같은 프로그램이 중복 실행 되어도
					인스턴스를 참고하여 서로 다른 프로그램으로 인식.

hPrevInstance	:	바로 앞에 실행된 현재 프로그램의 인스턴스 핸들.
					없을 경우 NULL.
					Win32에서는 항상 NULL.
					16비트와의 호환성을 위해서만 존재.

lpszCmdParam	:	명령행으로 입력된 프로그램 인수. 예) notepad D:\test.txt

nCmdShow		:	프로그램이 실행될 형태.
					최소화, 보통모양 등.

* hInstance 외에는 잘 사용되지 않음.
*/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance , LPSTR lpszCmdParam, int nCmdShow)
{
	//-----------------------------------
	//	윈도우 클래스 등록
	//	WNDCLASS	:	만들고자 하는 윈도우의 여러가지 특성을 정의하는 구조체.
	WNDCLASS WndClass;

	//	WndClass.style			:	윈도우 스타일 정의.
	//								CS_HREDRAW | CS_VREDRAW	:	윈도우의 수직,수평 크기가 변할 경우 
	//															윈도우를 다시 그린다.						
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	//	WndClass.lpfnWndProc	:	윈도우 메시지 처리 함수 지정.
	WndClass.lpfnWndProc = WndProc;

	//	WndClass.cbClsExtra / WndClass.cbWndExtra	:	일종의 예약 영역.
	//													거의 사용하지 않음.
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	
	//	WndClass.hInstance		:	윈도우 클래스를 등록하고자 하는 프로그램 고유 ID.
	WndClass.hInstance = hInstance;

	//	WndClass.hCursor / WndClass.hIcon			:	윈도우가 사용할 마우스 커서와 아이콘 지정.
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	//	WndClass.hbrBackground	:	윈도우의 배경을 채색할 브러시 설정.
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	
	//	WndClass.lpszMenuName	:	프로그램이 사용할 메뉴 설정.
	//								리소스 에디터에서 별도로 만듦.
	//								링크시에 합쳐짐.
	//								사용하지 않을 경우 NULL.
	WndClass.lpszMenuName = NULL;
	
	//	WndClass.lpszClassName	:	윈도우 클래스 이름.
	WndClass.lpszClassName = g_lpszClass;
		
	//	윈도우 클래스 등록.
	RegisterClass(&WndClass);
	//-----------------------------------
	//	hWnd	:	CreateWindow 실행후 생성되는 윈도우의 고유 ID.
	HWND hWnd;
	//	생성하고자 하는 윈도우의 클래스 지정, 윈도우 타이틀 바에 나타낼 문자열
	hWnd = CreateWindow(g_lpszClass, "Hello API!!",
	//hWnd = CreateWindow("aa", "Hello API!!",
						
						//	윈도우 형태, 비트 필드값.
						//	WS_OVERLAPPEDWINDOW		:	시스템 메뉴 | 최대/최소 버튼 | 타이틀 바 | 경계선
						WS_OVERLAPPEDWINDOW,

						//	윈도우의 위치와 크기값, 픽셀 단위.
						//	CW_USEDEFAULT	:	운영체제가 화면크기에 맞게 적당한 크기와 위치를 설정.
						//	100,100,200,200,
						CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
					
						//	부모 윈도우가 있는 경우 부모 윈도우의 핸들(ID).
						//	MDI(다중 문서)프로그램, 팝업 윈도우등.
						//	자신이 최상위 인 경우 NULL.
						NULL,
						
						//	윈도우에서 사용할 메뉴의 핸들.
						//	WndClass.lpszMenuName와 동일하게 사용하려면 NULL
						(HMENU)NULL,

						//	윈도우를 만드는 주체의 핸들(ID).
						//	운영체제는 이 값을 참조하였다가 프로그램 종료시
						//	파괴되지 않은 윈도우를 자동으로 파괴함.
						hInstance,
		
						//	CREATESTRUCT라는 구조체의 주소.
						//	여러개의 우니도우를 만들때 각 윈도우에 고유 파라미터 전달 목적.
						//	잘 사용되지 않음.
						NULL);

	//	CreateWindow를 통해 메모리상에만 윈도우가 존재하게 됨.
	//	화면으로 보이게하는 역할.
	//	SW_HIDE, SW_MINIMIZE 등의 파라미터 제공.
	//	보통 nCmdShow를 그대로 전달.
	ShowWindow(hWnd, nCmdShow);
	//-----------------------------------
	/*
	///	메시지 루프

	GetMessage			:	메시지 큐에서 메시지를 읽어들임.
							( 메시지 큐	:	시스템이나 사용자로부터 발생된 메시지가 잠시 대기하는 일종의 메시지 임시 저장소. )
							읽어들인 메시지는 MSG구조체에 저장됨.
							WM_QUIT라는 메시지가 읽혀질때까지 반복됨.
							나머지 인자는 잘 사용되지 않음.
	
	TranslateMessage	:	키보드 입력 메시지를 가공하여 프로그램에서 사용하기 쉽게한다.
							WM_KEYDOWN 메시지가 발생했을때 문자라면 WM_CHAR 메시지로 변환하여
							어떤 문자가 입력되었는지 알수 있게 한다.

	DispatchMessage		:	메시지 큐에서 꺼낸 메시지를 WndProc으로 전달한다.
							실제 메시지 처리는 WndProc에서 한다.
	*/
	MSG Message;
	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	//-----------------------------------
	
	return (int)Message.wParam;

}//	int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance , LPSTR lpszCmdParam, int nCmdShow)
//=============================================================
/*
WndProc			:	사용자와 시스템이 보내는 메시지 처리.
					거의 모든 경우에 WinMain과 WndProc는 모두 구현해야함.
					프로그램의 실질적인 처리.

CALLBACK		:	APIENTRY와 같은 역할.

hWnd			:	메시지를 받을 윈도우의 핸들.
iMessage		:	어떤 종류의 메시지인지, 어떤 이벤트가 발생했는지에 대한 정보.
wParam, lParam	:	iMessage의 부가 정보.
					예) WM_LBUTTONDOWN - 화면의 
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
		//	윈도우 생성시 발생.
	case WM_CREATE:
		MessageBox(hWnd, "WM_CREATE", "", NULL);		
		//	메시지 처리후 반드시 0을 리턴.
		return 0;

		//	마우스 왼쪽 클릭시 발생.
	case WM_LBUTTONDOWN:
		int x, y;
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		TCHAR tmp[100];
		wsprintf(tmp, "x = %d, y = %d", x, y);
		MessageBox(hWnd, tmp, "WM_LBUTTONDOWN", NULL);
		return 0;
		//	윈도우 종료시 발생.
		//	X버튼(우측상단 시스템 버튼), Alt+F4등.
	case WM_DESTROY:
		MessageBox(hWnd, "WM_DESTROY", "", NULL);

		//	WM_QUIT를 메시지 큐에 전달.
		PostQuitMessage(0);
		return 0;

	}//	switch (iMessage)

	//	기본 이벤트 처리.
	//	switch (iMessage)에서 처리하지 않은 메시지 처리.
	//	예) 윈도우 이동, 윈도우 창 크기 변경 등.
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));

}//	LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
//=============================================================