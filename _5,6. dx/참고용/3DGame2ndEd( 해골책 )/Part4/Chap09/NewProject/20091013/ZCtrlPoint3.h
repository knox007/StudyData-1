#ifndef _ZCTRLPOINT3_H_
#define _ZCTRLPOINT3_H_

#include "zctrlbase.h"

class ZCtrlPoint3 : public ZCtrlBase
{
protected:
	void _DoInterpol( ZTKeyPoint3* key, ZTKeyPoint3* p1, ZTKeyPoint3* p2, float a )
	{
		D3DXVec3Lerp( &key->value, &p1->value, &p2->value, a );
	}

	BOOL _GetKey( ZTKeyPoint3* key )
	{
		float		a;
		ZTKeyPoint3	*p1, *p2;

		_Get2Keys( m_fFrame, m_keys, p1, p2 );

		if( !p1 || !p2 )
		{
			key->frame = 0.0f;
			key->type = ZTKeyBase::KEYTYPE_POINT3;
			key->value.x = 0;
			key->value.y = 0;
			key->value.z = 0;
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
	ZCtrlPoint3(void);
	virtual ~ZCtrlPoint3(void);

	virtual BOOL GetKey( ZTKeyBase* pKey ) { return _GetKey( (ZTKeyPoint3*)pKey ); }
};

#endif // _ZCTRLPOINT3_H_
