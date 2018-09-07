#ifndef _ZCTRLBASE_H_
#define _ZCTRLBASE_H_

#include "ZDefine.h"
#include <vector>

inline float _GetAlpha( float f1, float f2, float frame )
{
	return ( (frame-f1) / (f2-f1) );
}

template <class T>
void _Get2Keys( float frame, std::vector<ZTKeyBase*>& keys, T*& k1, T*& k2 )
{
	int		mkey;
	int		lkey = 0;
	int		rkey = keys.size()-1;

	if( keys.empty() )
	{
		k1 = k2 = NULL;
		return;
	}

	if( keys.size() > 1 )
	{
		if( frame > keys[rkey]->frame )
		{
			k1 = (T*)keys[rkey];
			k2 = (T*)keys[rkey];
			return;
		}
		if( frame < keys[lkey]->frame)
		{
			k1 = (T*)keys[lkey];
			k2 = (T*)keys[lkey];
			return;
		}

		while( rkey >= lkey )
		{
			mkey = (rkey + lkey)/2;
			if( keys[mkey]->frame <= frame && keys[mkey+1]->frame >= frame )
			{
				k1 = (T*)keys[mkey];
				k2 = (T*)keys[mkey+1];
				return;
			}
			if( keys[mkey]->frame > frame )
				rkey = mkey;
			else
				lkey = mkey;
		}
	}
	else
	if( keys.size() == 1 )
	{
		k1 = k2 = ((T*)keys[0]);
	}
	else
		k1 = k2 = NULL;
}

class ZCtrlBase
{
protected:
	float					m_fFrame;
	float					m_fFrameRate;
	std::vector<ZTKeyBase*>	m_keys;

protected:
	
	void _DoInterpol( ZTKeyBase* key, ZTKeyBase* p1, ZTKeyBase* p2, float a ) {}
	BOOL _GetKey( ZTKeyBase* key ) { return FALSE; }

public:
	ZCtrlBase(void) 
	{
		m_fFrame = 0.0f;
		m_fFrameRate = 30.0f;
	}
	ZCtrlBase( float fFrameRate ) { m_fFrameRate = fFrameRate; }
	virtual ~ZCtrlBase(void) { stl_wipe_vector( m_keys ); }
	virtual void SetTime( float fTime )	{ m_fFrame = fTime * m_fFrameRate; }
	virtual void SetFrame( float fFrame ) { m_fFrame = fFrame; }
	virtual BOOL GetKey( ZTKeyBase* pKey ) = 0;
	virtual BOOL AddKey( ZTKeyBase* pKey ) { m_keys.push_back( pKey ); return TRUE; }
	virtual BOOL HasKey() { return (BOOL)(!m_keys.empty()); }
};

#endif // _ZCTRLBASE_H_