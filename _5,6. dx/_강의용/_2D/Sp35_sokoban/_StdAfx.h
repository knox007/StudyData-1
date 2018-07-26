//
//
////////////////////////////////////////////////////////////////////////////////


#pragma warning( disable : 4996)


#pragma once


#ifndef __STDAFX_H_
#define __STDAFX_H_


// �ٸ��콺�� ������ �� ������ �ݵ�� �ʿ�.
#define _WIN32_WINNT 0x0400


// DirectX�� ����ϱ����� �� �ʿ��� ���̺귯���� �������
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "DxErr.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dsound.lib")			// Direct Sound


#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>


// timeGetTime()�Լ��� ����ϱ� ���ؼ�..
#pragma comment(lib, "winmm.lib")
#include <Mmsystem.h>


#define GHWND		g_pApp->GetHwnd()
#define GDEVICE		g_pApp->GetDevice()
#define GSPRITE		g_pApp->GetSprite()

#include "resource.h"
#include "D3DApp.h"

#include "McUtil.h"
#include "LcInput.h"

#include "Stage.h"

#include "IGameStage.h"
#include "GameBegin.h"
#include "GamePlay.h"
#include "GameEnd.h"



#include "Main.h"

#endif
