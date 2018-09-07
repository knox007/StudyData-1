#ifndef _ZCTRLFLOAT_H_
#define _ZCTRLFLOAT_H_

#include "zctrlbase.h"

class ZCtrlBezierFloat : public ZCtrlBase
{
protected:
	void _DoInterpol( ZTKeyFloat* key, ZTKeyFloat* p1, ZTKeyFloat* p2, float a )
	{
		key->value = p1->value * (1.0f-a) + a * p2->value;
	}

	BOOL _GetKey( ZTKeyFloat* key )
	{
		float		a;
		ZTKeyFloat	*p1, *p2;

		_Get2Keys( m_fFrame, m_keys, p1, p2 );

		if( !p1 || !p2 ) return FALSE;

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
	ZCtrlBezierFloat(void);
	virtual ~ZCtrlBezierFloat(void);

	virtual BOOL GetKey( ZTKeyBase* pKey ) { return _GetKey( (ZTKeyFloat*)pKey ); }
};

#endif // _ZCTRLFLOAT_H_