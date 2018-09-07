#pragma once
#include "stdafx.h"
#include "IGameInterfaceBase.h"
#include "PFrFrameWork.h"
#include "PRCore.h"
#include "PRFont.h"
#include "PRCamera.h"
 
//-----------------------------------------------------------------------------
void IGameInterfaceBase::LinkFramework( CPFrFrameWork* pFrame )	
{
	m_pFramework = pFrame;
}//	LinkFramework
//-----------------------------------------------------------------------------
void IGameInterfaceBase::RenderFrame( IDirect3DDevice9* pDevice, float elapsedTime )
{
	GetRenderer()->Clear();
	HRESULT hr = GetRenderer()->BeginScene();

	OnRender( GetRenderer()->GetDevice(), elapsedTime );

	GetRenderer()->EndScene();
	GetRenderer()->Present();
}//	RenderFrame
//-----------------------------------------------------------------------------
CPRCore* IGameInterfaceBase::GetRenderer()	
{
	return m_pFramework->GetRenderer();
}//	GetRenderer
//-----------------------------------------------------------------------------
CPRCamera* IGameInterfaceBase::GetCamera()
{
	return m_pFramework->GetCamera();
}//	GetCamera
//-----------------------------------------------------------------------------
CPFrFrameWork* IGameInterfaceBase::GetFrameWork()
{
	return m_pFramework;
}
//-----------------------------------------------------------------------------
//	EOF