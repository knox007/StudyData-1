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

#include "resource.h"

#define GHINST			g_pApp->GetHinst()
#define GHWND			g_pApp->GetHwnd()
#define GDEVICE			g_pApp->GetDevice()


#include "McUtil.h"
#include "D3DApp.h"
#include "LcSprite.h"
#include "LcInput.h"
#include "LcTexture.h"


#include "Main.h"

#endif