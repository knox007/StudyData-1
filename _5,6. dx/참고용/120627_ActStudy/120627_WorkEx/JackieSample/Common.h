#ifndef _COMMON_H_
#define _COMMON_H_

#pragma once

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.

#include <Windows.h>
#include <stdio.h>

#include <d3d9.h>
#include <d3dx9.h>
#include <tchar.h>

#include "PUTCommon.h"
#include "GameInterface.h"

extern TCHAR* g_ptszWndTitle;

//----------------------------------------------------------------------------------------
//	Directory Path
extern const TCHAR*	DIRPATH_TESTRes;
extern const TCHAR*	DIRPATH_TESTRes_Txtr;
extern const TCHAR*	DIRPATH_XFILE;
extern const TCHAR*	DIRPATH_ASE;
extern const TCHAR*	DIRPATH_ASE_TXTR;
extern const TCHAR*	DIRPATH_SHADER;


#endif	//	_COMMON_H_