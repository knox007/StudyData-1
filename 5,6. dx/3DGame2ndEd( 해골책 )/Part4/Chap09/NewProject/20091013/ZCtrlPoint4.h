#ifndef _ZCTRLPOINT4_H_
#define _ZCTRLPOINT4_H_

#include "zctrlbase.h"

class ZCtrlPoint4 : public ZCtrlBase
{
protected:
	void _DoInterpol( ZTKeyPoint4* key, ZTKeyPoint4* p1, ZTKeyPoint4* p2, float a )
	{
		D3DXVec4Lerp( &key->value, &p1->value, &p2->value, a );
	}

	BOOL _GetKey( ZTKeyPoint4* key )
	{
		float		a;
		ZTKeyPoint4	*p1, *p2;

		_Get2Keys( m_fFrame, m_keys, p1, p2 );

		if( !p1 || !p2 )
		{
			key->frame = 0.0f;
			key->type = ZTKeyBase::KEYTYPE_POINT4;
			key->value.x = 0;
			key->value.y = 0;
			key->value.z = 0;
			key->value.w = 0;
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
	ZCtrlPoint4(void);
	virtual ~ZCtrlPoint4(void);

	virtual BOOL GetKey( ZTKeyBase* pKey ) { _GetKey( (ZTKeyPoint4*)pKey ); return TRUE; }
};

#endif // _ZCTRLPOINT4_H_
