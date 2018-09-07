#ifndef _ZCTRLSTRING_H_
#define _ZCTRLSTRING_H_

#include "zctrlbase.h"

class ZCtrlString : public ZCtrlBase
{
	BOOL _GetKey( ZTKeyString* pKey )
	{
		if( m_keys.empty() )
			((ZTKeyString*)pKey)->value = "";
		else
			((ZTKeyString*)pKey)->value = ((ZTKeyString*)(m_keys[0]))->value;
		return TRUE;
	}

public:
	ZCtrlString(void);
	virtual ~ZCtrlString(void);
//	virtual BOOL GetKey( ZTKeyBase* pKey ) { ((ZTKeyString*)pKey)->value = ((ZTKeyString*)(m_keys[0]))->value; return TRUE; }
	virtual BOOL GetKey( ZTKeyBase* pKey ) { _GetKey( (ZTKeyString*)pKey ); return TRUE; }
};

#endif // _ZCTRLSTRING_H_