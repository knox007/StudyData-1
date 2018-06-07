#ifndef _IFRBASEAPP_H_
#define _IFRBASEAPP_H_
#pragma once

#include <Windows.h>
#include <d3d9.h>

class CPFrFrameWork;
class CPRCore;
class CPRCamera;

class IFrBaseApp
{
public:
	IFrBaseApp()				{ InitMembers(); }
	virtual ~IFrBaseApp()		{}
	virtual	void InitMembers()	{ m_pFramework = NULL; }    

	virtual bool Init() = 0;
	
    virtual HRESULT OnCreateDevice( IDirect3DDevice9* pDevice ) = 0;
    virtual HRESULT OnResetDevice( IDirect3DDevice9* pDevice ) = 0;
    virtual HRESULT OnLostDevice() = 0;
    virtual HRESULT OnDestroyDevice() = 0;
    virtual void OnUpdate( IDirect3DDevice9* pDevice, float elapsedTime ) = 0;
    virtual void RenderFrame( IDirect3DDevice9* pDevice, float elapsedTime );
	virtual void OnRender( IDirect3DDevice9* pDevice, float elapsedTime ) = 0;	
	virtual	LRESULT	CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) = 0;
	void	LinkFramework( CPFrFrameWork* pFrame );

	CPRCore*		GetRenderer();
	CPRCamera*		GetCamera();
	CPFrFrameWork*	GetFrameWork();


protected:
	CPFrFrameWork*	m_pFramework;
};

#endif	//	_IFRBASEAPP_H_