#include "stdafx.h"
#include "PUTLog.h"
#include "PreDef_UT.h"
#include "PUtCommonStr.h"
#include "PUTCommonVerIntegrate.h"

//----------------------------------------------------------------------------------------
void	CPUTLog::InitMembers()
{
	m_nTarget = JLOG_WINDOW;
	m_hwnd = NULL;
	m_szFilename[0] = NULL;
}//	InitMember
//----------------------------------------------------------------------------------------
void	CPUTLog::ReleaseMember()
{
	DestroyWindow( m_hwnd );
}//	ReleaseMember
//----------------------------------------------------------------------------------------
void CPUTLog::StartLog( UINT32 nTarget, LPSTR szFilename )
{
	m_nTarget = nTarget;

	if( nTarget & JLOG_FILE )
#ifndef _ENGCLI_VS2003_VS2008_
		strcpy_s( m_szFilename, sizeof(szFilename), szFilename );
#else
		PUT_Strcpy( m_szFilename, szFilename );
#endif
		
	else
		m_szFilename[0] = NULL;

	if( nTarget & JLOG_WINDOW )
		CreateLogWindow();
	else
		m_hwnd = NULL;

	Log( "JLog Logging Started..." );
}//	StartLog
//----------------------------------------------------------------------------------------
void CPUTLog::CreateLogWindow()
{
	int			x, y, cx, cy;
	WNDCLASS	wc;
	RECT		rc;

	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc		= (WNDPROC)CPUTLog::WndProcCPUTLog;
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= GetModuleHandle( NULL );
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= (HBRUSH)GetStockObject( WHITE_BRUSH );
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= JLOG_WINDOW_TITLE;

	RegisterClass(&wc);

	cx = JLOG_WINDOW_CX;
	cy = JLOG_WINDOW_CY;
	x = GetSystemMetrics( SM_CXSCREEN ) - cx;
	y = 0;

	m_hwnd = CreateWindow( JLOG_WINDOW_TITLE, JLOG_WINDOW_TITLE, WS_POPUP | WS_CAPTION, x, y, cx, cy, NULL, NULL, GetModuleHandle( NULL ), NULL );
	GetClientRect( m_hwnd, &rc );
	m_hwndList = CreateWindow( "LISTBOX", "", WS_CHILD | WS_VSCROLL, 0, 0, rc.right, rc.bottom, m_hwnd, NULL, GetModuleHandle( NULL ), NULL );
	ShowWindow( m_hwnd, SW_SHOW );
	ShowWindow( m_hwndList, SW_SHOW );
}//	CreateLogWindow
//----------------------------------------------------------------------------------------
int CPUTLog::Log( LPSTR fmt, ... )
{
	char	buff[1024];
	char	date[128];
	char	time[128];

#ifndef _ENGCLI_VS2003_VS2008_
	_strdate_s( date, sizeof(date) );
	_strtime_s( time, sizeof(time) );
	//vsprintf( buff, fmt, (char *)(&fmt+1) );	
	vsprintf_s( buff, sizeof(buff), fmt, (char *)(&fmt+1) );
#else
	PUT_Strdate( date, sizeof(date) );
	PUT_StrTime( time, sizeof(time) );
	PUT_VSprintf( buff, sizeof(buff), fmt, (char *)(&fmt+1) );
#endif
	
	
	// Console에 출력할 경우 
	if( m_nTarget & JLOG_CONSOLE )
	{
		printf( "(date[%s] time[%s]) : %s\n", date, time, buff );
	}

	// Log File에 출력할 경우
	if( m_nTarget & JLOG_FILE )
	{
		FILE*	fp = NULL;
#ifndef	_ENGCLI_VS2003_VS2008_
		fopen_s( &fp, m_szFilename, "a+" );
#else
		PUT_FOpen( &fp, m_szFilename, "a+" );
#endif
		if( fp )
		{
			fprintf( fp, "(date[%s] time[%s]) : %s\n", date, time, buff );
			fclose( fp );
		}
	}

	// Log Window에 출력할 경우 
	if( m_nTarget & JLOG_WINDOW )
	{
		SendMessage( m_hwndList, LB_ADDSTRING, 0, (LPARAM) buff );
		UINT32 n = SendMessage( m_hwndList, LB_GETCOUNT, 0, 0L ) - 1;
		SendMessage( m_hwndList, LB_SETCURSEL, (WPARAM)n, 0L );
	}
	return 1;
}//	Log
//----------------------------------------------------------------------------------------
LRESULT CALLBACK 
CPUTLog::WndProcCPUTLog( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	return DefWindowProc( hwnd, uMsg, wParam, lParam );
}//	WndProcCPUTLog
//----------------------------------------------------------------------------------------
//	EOF