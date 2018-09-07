#ifndef _ZCTRLQUAT_H_
#define _ZCTRLQUAT_H_

#include "zctrlbase.h"

class ZCtrlQuat : public ZCtrlBase
{
protected:
	void _DoInterpol( ZTKeyQuat* key, ZTKeyQuat* p1, ZTKeyQuat* p2, float a )
	{
		D3DXQuaternionSlerp( &key->value, &p1->value, &p2->value, a );
	}

	BOOL _GetKey( ZTKeyQuat* key )
	{
		float		a;
		ZTKeyQuat	*p1, *p2;

		_Get2Keys( m_fFrame, m_keys, p1, p2 );

		if( !p1 || !p2 )
		{
			key->frame = 0.0f;
			key->type = ZTKeyBase::KEYTYPE_QUATERNION;
			key->value.x = 0;
			key->value.y = 0;
			key->value.z = 0;
			key->value.w = 1;
			return FALSE;
		}

		if( p1 == p2 )
		{
			*key = *p1;
		}
		else
		{
			a = _GetAlpha( p1->frame, p2->frame, m_fFrame );
			_DoInterpol( key, p1, p2, a );
		}

		return TRUE;
	}

public:
	ZCtrlQuat(void);
	virtual ~ZCtrlQuat(void);

	virtual BOOL GetKey( ZTKeyBase* pKey ) { _GetKey( (ZTKeyQuat*)pKey ); return TRUE; }
};

#endif // _ZCTRLQUAT_H_