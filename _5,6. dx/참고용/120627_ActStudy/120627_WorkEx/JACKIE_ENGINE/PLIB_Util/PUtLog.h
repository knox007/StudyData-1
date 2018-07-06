#ifndef _JLOG_H_
#define _JLOG_H_
#pragma once

#include "PUTSingleton.h"

#define JLOG_CONSOLE			0x00000001
#define JLOG_FILE				0x00000002
#define JLOG_WINDOW				0x00000004
#define JLOG_ALL				( JLOG_CONSOLE | JLOG_FILE | JLOG_WINDOW )
#define JLOG_WINDOW_TITLE				"JACKIE LOG"
#define JLOG_WINDOW_CX				300
#define JLOG_WINDOW_CY				600

class CPUTLog : public CPUTSingleton<CPUTLog>
{
friend CPUTSingleton<CPUTLog>;
	unsigned int	m_nTarget;
	char			m_szFilename[MAX_PATH];
	HWND			m_hwnd;
	HWND			m_hwndList;
	CPUTLog()					{ InitMembers(); }
	virtual		~CPUTLog()		{ ReleaseMember(); }

public:
	void	InitMembers();
	void	ReleaseMember();
	void	CreateLogWindow();
	void	StartLog( UINT32 nTarget, LPSTR szFilename = NULL );
	int		Log( LPSTR fmt, ... );

private:
	static	LRESULT CALLBACK
	CPUTLog::WndProcCPUTLog( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
};
//	CPUTLog

#define gUtLog			CREATESINGLETON(CPUTLog)
#define gUtLogDestroy	DESTROYSINGLETON(CPUTLog)
#endif // _JLOG_H_