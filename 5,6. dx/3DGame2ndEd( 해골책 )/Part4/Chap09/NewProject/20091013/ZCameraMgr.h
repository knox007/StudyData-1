#ifndef _ZCAMERAMGR_H_
#define _ZCAMERAMGR_H_

#include "define.h"
#include "ZDefine.h"
#include "ZTrack.h"
#include "ZCamera.h"
#include "ZCParsedData.h"

class ZCameraMgr
{
protected:
	LPDIRECT3DDEVICE9		m_pDev;			/// D3D디바이스
	float					m_fFrameRate;
	ZTrack*					m_pTrackCamera;
	ZTrack*					m_pTrackTarget;
	D3DXMATRIXA16			m_matView;
	ZCamera*				m_pCamera;

public:
	ZCameraMgr(void);
	ZCameraMgr( LPDIRECT3DDEVICE9 pDev, ZCParsedData* pData );
	~ZCameraMgr(void);
	
	ZCamera*	GetCamera() { return m_pCamera; }
	void		SetCamera( ZCamera* pCamera ) { m_pCamera = pCamera; }
	void		GetCameraPos( float frame, D3DXVECTOR3* pEye, D3DXVECTOR3* pLookat );
	void		GetCameraPos_TimeBased( float time, D3DXVECTOR3* pEye, D3DXVECTOR3* pLookat )
	{
		GetCameraPos( time * m_fFrameRate, pEye, pLookat );
	}

	void			Animate( float frame );
	void			Animate_TimeBased( float time ) { Animate( time * m_fFrameRate ); }
	D3DXMATRIXA16*	SetFrame( float frame );
	D3DXMATRIXA16*	SetFrame_TimeBased( float time ) { SetFrame( time * m_fFrameRate ); }
};

#endif // _ZCAMERAMGR_H_