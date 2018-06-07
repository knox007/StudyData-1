#ifndef _ZTRACK_H_
#define _ZTRACK_H_

#include "define.h"
#include "ZDefine.h"
#include <d3d9.h>
#include <d3dx9.h>

/// 애니메이션 키값을 보관하기 위한 클래스
class ZTrack
{
public:
	enum INTERPOL { INTP_LINEAR, INTP_SPLINE, INTP_HERMIT };	// 현재는 LINEAR만 지원

protected:
	BOOL			m_bAnimatable;
	ZTKeys			m_keys;		/// 키값들
	D3DXMATRIXA16	m_matAni;	/// 최종적으로 구한 애니메이션 행렬
	float			m_fFrameRate;

	inline float _GetAlpha( float f1, float f2, float frame )
	{
		return ( (frame-f1) / (f2-f1) );
	}

	void _Get2Keys( float frame, std::vector<ZTKeyPos>& keys, ZTKeyPos*& k1, ZTKeyPos*& k2 );
	void _Get2Keys( float frame, std::vector<ZTKeyRot>& keys, ZTKeyRot*& k1, ZTKeyRot*& k2 );
	void _Get2Keys( float frame, std::vector<ZTKeyScl>& keys, ZTKeyScl*& k1, ZTKeyScl*& k2 );
public:	// 임시로 ZCameraMgr에서 _GetPosKey()를 사용하기 위해서 public으로 확장
	BOOL _GetPosKey( float frame, D3DXVECTOR3* pv );
	BOOL _GetRotKey( float frame, D3DXQUATERNION* pq );
	BOOL _GetSclKey( float frame, D3DXVECTOR3* pv );
public:
	ZTrack( Track& keys );
	ZTrack( float fFrameRate, Track& keys );
	~ZTrack();
	
	
	BOOL isAnimatable() { return m_bAnimatable; }
	D3DXMATRIXA16*	Animate( float frame );
};

#endif // _ZTRACK_H_