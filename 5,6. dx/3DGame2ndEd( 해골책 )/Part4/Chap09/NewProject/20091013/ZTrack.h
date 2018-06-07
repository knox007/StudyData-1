#ifndef _ZTRACK_H_
#define _ZTRACK_H_

#include "define.h"
#include "ZDefine.h"
#include <d3d9.h>
#include <d3dx9.h>

/// �ִϸ��̼� Ű���� �����ϱ� ���� Ŭ����
class ZTrack
{
public:
	enum INTERPOL { INTP_LINEAR, INTP_SPLINE, INTP_HERMIT };	// ����� LINEAR�� ����

protected:
	BOOL			m_bAnimatable;
	ZTKeys			m_keys;		/// Ű����
	D3DXMATRIXA16	m_matAni;	/// ���������� ���� �ִϸ��̼� ���
	float			m_fFrameRate;

	inline float _GetAlpha( float f1, float f2, float frame )
	{
		return ( (frame-f1) / (f2-f1) );
	}

	void _Get2Keys( float frame, std::vector<ZTKeyPos>& keys, ZTKeyPos*& k1, ZTKeyPos*& k2 );
	void _Get2Keys( float frame, std::vector<ZTKeyRot>& keys, ZTKeyRot*& k1, ZTKeyRot*& k2 );
	void _Get2Keys( float frame, std::vector<ZTKeyScl>& keys, ZTKeyScl*& k1, ZTKeyScl*& k2 );
public:	// �ӽ÷� ZCameraMgr���� _GetPosKey()�� ����ϱ� ���ؼ� public���� Ȯ��
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