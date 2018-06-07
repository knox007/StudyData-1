#pragma once
#include "stdafx.h"
#include "IFrBaseApp.h"
#include "PFrFrameWork.h"
#include "PRCore.h"
#include "PRFont.h"
#include "PRCamera.h"
 
//-----------------------------------------------------------------------------
void IFrBaseApp::LinkFramework( CPFrFrameWork* pFrame )	
{
	m_pFramework = pFrame;
}//	LinkFramework
//-----------------------------------------------------------------------------
void IFrBaseApp::RenderFrame( IDirect3DDevice9* pDevice, float elapsedTime )
{
	GetRenderer()->Clear();
	GetRenderer()->BeginScene();

	OnRender( GetRenderer()->GetDevice(), elapsedTime );

	GetRenderer()->EndScene();
	GetRenderer()->Present();
}//	RenderFrame
//-----------------------------------------------------------------------------
CPRCore* IFrBaseApp::GetRenderer()	
{
	return m_pFramework->GetRenderer();
}//	GetRenderer
//-----------------------------------------------------------------------------
CPRCamera* IFrBaseApp::GetCamera()
{
	return m_pFramework->GetCamera();
}//	GetCamera
//-----------------------------------------------------------------------------
CPFrFrameWork* IFrBaseApp::GetFrameWork()
{
	return m_pFramework;
}
//-----------------------------------------------------------------------------
//	EOF