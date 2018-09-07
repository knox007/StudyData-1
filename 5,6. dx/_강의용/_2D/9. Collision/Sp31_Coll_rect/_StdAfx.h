//
//
////////////////////////////////////////////////////////////////////////////////


#pragma warning( disable : 4996)


#pragma once


#ifndef __STDAFX_H_
#define __STDAFX_H_


#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")


#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <Mmsystem.h>

#define GMAIN			g_pApp
#define GHINST			g_pApp->m_hInst
#define GHWND			g_pApp->m_hWnd
#define GDEVICE			g_pApp->m_pd3dDevice


#include "McUtil.h"
#include "D3DApp.h"
#include "LcSprite.h"
#include "LcInput.h"
#include "LcTexture.h"


#include "Main.h"

#endif