#ifndef _ZCTRLBOOL_H_
#define _ZCTRLBOOL_H_

#include "zctrlbase.h"

class ZCtrlBool : public ZCtrlBase
{
protected:
	void _DoInterpol( ZTKeyBool* key, ZTKeyBool* p1, ZTKeyBool* p2, float a )
	{
		key->value = a < 0.999f ? p1->value : p2->value;
	}

	BOOL _GetKey( ZTKeyBool* key )
	{
		float		a;
		ZTKeyBool	*p1, *p2;

		_Get2Keys( m_fFrame, m_keys, p1, p2 );

		if( !p1 || !p2 )
		{
			key->frame = 0.0f;
			key->type = ZTKeyBase::KEYTYPE_BOOL;
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
	ZCtrlBool(void);
	virtual ~ZCtrlBool(void);
	virtual BOOL GetKey( ZTKeyBase* pKey ) { return _GetKey( (ZTKeyBool*)pKey ); }
};

#endif // _ZCTRLBOOL_H_