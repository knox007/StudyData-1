#ifndef _ZCTRLINT_H_
#define _ZCTRLINT_H_

#include "zctrlbase.h"

class ZCtrlInt : public ZCtrlBase
{
protected:
	void _DoInterpol( ZTKeyInt* key, ZTKeyInt* p1, ZTKeyInt* p2, float a )
	{
		key->value = (int)(p1->value * (1.0f-a) + a * p2->value);
	}

	BOOL _GetKey( ZTKeyInt* key )
	{
		float		a;
		ZTKeyInt	*p1, *p2;

		_Get2Keys( m_fFrame, m_keys, p1, p2 );

		if( !p1 || !p2 )
		{
			key->frame = 0.0f;
			key->type = ZTKeyBase::KEYTYPE_INT;
			key->value = 0;
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
	ZCtrlInt(void);
	virtual ~ZCtrlInt(void);

	virtual BOOL GetKey( ZTKeyBase* pKey ) { return _GetKey( (ZTKeyInt*)pKey ); }
};

#endif // _ZCTRLINT_H_