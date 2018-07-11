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

#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }


#include "D3DApp.h"

#endif