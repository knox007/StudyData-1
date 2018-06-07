#ifndef	_GAMEINTERFACE_H_
#define _GAMEINTERFACE_H_
#pragma once

#include "IGameInterfaceBase.h"
#include "PFrFrameWork.h"
#include "PUtVecMgr.h"
#include "PRObject.h"
#include "PreDef.h"
#include "PRCommonTypeDef.h"

#ifdef _ENG_TEST_UI_
class CUITestDlg;
#endif	//	_ENG_TEST_UI_

class CPRMdlXFile; 

class CPFrFrameWork;

class CPRMdlAse;



class CJGameInterface : public IGameInterfaceBase
{
public:
	CJGameInterface()			{ InitMembers(); }
	virtual ~CJGameInterface()	{ ClearMembers(); }

	virtual void	InitMembers();
	virtual void	ClearMembers();

	virtual bool	Init();
	
	virtual	HRESULT	OnCreateDevice( IDirect3DDevice9* pDevice );
	virtual	HRESULT	OnResetDevice( IDirect3DDevice9* pDevice );
	virtual HRESULT	OnLostDevice();
	virtual HRESULT	OnDestroyDevice();
	virtual	void	OnUpdate( float fElapsedTime = 0 );
	virtual HRESULT	OnRender( IDirect3DDevice9* pDevice, float elapsedTime );

	virtual	LRESULT	CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );


	void	InitMembersShader();
	void	ClearMembersShader();
	HRESULT	OnCreateDeviceShader( LPDIRECT3DDEVICE9 pDev );
	HRESULT OnRenderShader( LPDIRECT3DDEVICE9 pDevice, float elapsedTime );
	HRESULT OnUpdateShader( float fElapsedTime = 0 );
	HRESULT	OnResetDeviceShader( IDirect3DDevice9* pDevice  = NULL );
	HRESULT	OnLostDeviceShader( LPDIRECT3DDEVICE9 pDev = NULL );


private:	
	TCHAR			m_tszFPS[100];

#ifdef _SAMP_RENDER_TEAPOT_
	ID3DXMesh*          m_pD3DXMesh;            // ¡÷¿¸¿⁄ ∏ﬁΩ√
#endif

#ifdef _ENG_TEST_UI_
	CUITestDlg*			m_pTestDlg;
#endif

#ifdef _ENG_OBJECT_MGR_
	CPUTVecMgrPt<CPRObject>	m_ObjMgr;
#endif

#ifdef _SAMP_ASEMODEL_RENDER_
	CPRMdlAse*	m_AseTest;
#endif





//@ ºŒ¿Ã¥ı ----------------------------------------------
	CPRMdlXFile	*m_pXFileUFO;
	CPRMdlXFile	*m_pXFileMap;

	PRDXXEFF	m_pEffect;		// ¿Ã∆Â∆Æ
	PRDXHND			m_hTechnique;
	PRDXHND			m_hmatWVP;
//	PRDXHND			m_hmatLocal;
	PRDXHND			m_hvecLightDir;
	PRDXHND			m_hvecColor;
	PRDXHND			m_hvecEyePos;

	PRDXMat		m_matView;
	PRDXMat		m_matProj;
//--------------------------------------------@ ºŒ¿Ã¥ı --

};

#endif	//	_GAMEINTERFACE_H_