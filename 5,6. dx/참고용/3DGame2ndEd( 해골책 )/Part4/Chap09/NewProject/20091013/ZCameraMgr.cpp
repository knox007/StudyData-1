#include ".\ZCameraMgr.h"

ZCameraMgr::ZCameraMgr(void)
{
	m_pDev			= NULL;
	m_fFrameRate	= 30.0f;
	m_pTrackCamera	= NULL;
	m_pTrackTarget	= NULL;
	m_pCamera		= NULL;
}

ZCameraMgr::ZCameraMgr( LPDIRECT3DDEVICE9 pDev, ZCParsedData* pData )
{
	m_pDev			= pDev;
	m_fFrameRate	= pData->m_info.fFrameRate;
	m_pTrackCamera	= new ZTrack( m_fFrameRate, pData->m_camera.trkCamera );
	m_pTrackTarget	= new ZTrack( m_fFrameRate, pData->m_camera.trkTarget );
}

ZCameraMgr::~ZCameraMgr(void)
{
	S_DEL( m_pTrackCamera );
	S_DEL( m_pTrackTarget );
}

void ZCameraMgr::GetCameraPos( float frame, D3DXVECTOR3* pEye, D3DXVECTOR3* pLookat )
{
	m_pTrackCamera->_GetPosKey( frame, pEye );
	m_pTrackTarget->_GetPosKey( frame, pLookat );
}

D3DXMATRIXA16* ZCameraMgr::SetFrame( float frame )
{
	D3DXVECTOR3		eye;
	D3DXVECTOR3		lookat;

	GetCameraPos( frame, &eye, &lookat );
	m_pCamera->SetEye( &eye );
	m_pCamera->SetLookat( &lookat );
	m_pCamera->Flush();

	return m_pCamera->GetViewMatrix();
}

void ZCameraMgr::Animate( float frame )
{
	D3DXMATRIXA16*	pmat = SetFrame( frame );
	m_pDev->SetTransform( D3DTS_VIEW, pmat );
}