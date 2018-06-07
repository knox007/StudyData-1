#ifndef _PUTCOMMON_H_
#define _PUTCOMMON_H_
#pragma once

#include <stdio.h>
#include <tchar.h>
#include <crtdbg.h>

//----------------------------------------------------------------------------------------
//	Loop
#define PUT_FOR( Cur, startIdx, DstIdx )		for( ##Cur = startIdx; ##Cur < DstIdx; ++##Cur )
//----------------------------------------------------------------------------------------
#define PUT_CSTR_UNI(str)		L##str
#define PUT_CSTR_TCHAR(str)		_T(##str)
//	Assert --------------------------------------------------------------------------
#define PUT_ERROR			_ASSERT(0)
void	PUT_ERROR_MSZ( TCHAR* ptszMsg );

//	Memory --------------------------------------------------------------------------
#define PUT_ZERO_MEMORY( x )	\
{\
	ZeroMemory( &x, sizeof(x) );\
}

#define PUT_ZERO_MEMORY_PTR( x )	\
{\
	ZeroMemory( x, sizeof((*x)) );\
}

#define PUT_True( x )	\
{\
	x = true;\
}

#define PUT_False( x )	\
{\
	x = false;\
}

#define PUT_TRUE( x )	\
{\
	x = TRUE;\
}

#define PUT_FALSE( x )	\
{\
	x = FALSE;\
}
//------------------------------------------------------------------------
#define PUTNEW( x, TYPE )		{ x = new TYPE; }
#define PUT_SAFE_RELEASE(x)			if( x ) { (x)->Release();	(x) = NULL; }
#define PUT_SAFE_DELETE(x)			if( x ) { delete(x);		(x) = NULL; }
#define PUT_SAFE_DELETE_ARRAY(x)	if( x ) { delete [] (x);	(x) = NULL; }
//------------------------------------------------------------------------
#define PUT_IsZero( eval )			if( eval == 0 )
#define PUT_IsInValid( eval )		PUT_IsZero( eval )
#define PUT_IsFailed( eval )		if( FAILED( eval ) )
//------------------------------------------------------------------------
void	IsFailed( HRESULT hr );
void	IsFailed( HRESULT hr, TCHAR *ptszErr );
//------------------------------------------------------------------------
#define PUT_IsSucceeded( eval )		if( SUCCEEDED( eval ) )
#define PUT_IsSame( ev1, ev2 )		if( ev1 == ev2 )
#define PUT_IsDiffer( ev1, ev2 )	if( ev1 != ev2 )
//------------------------------------------------------------------------
//	Show Message 
void	PUTSHOWERR( TCHAR *ptszMsg );
//------------------------------------------------------------------------
void	PUTShowErrCode();
//------------------------------------------------------------------------
#if defined(_DEBUG) || defined(DEBUG)
#define PUTOutputDebugStr		Trace
#else
#define PUTOutputDebugStr		(__noop)
#endif

#define PUTRTRACE		Trace		//!< Release에서도 Debug 메세지를 출력하기 위한 매크로
//------------------------------------------------------------------------
void Trace( const TCHAR *ptszFormat, ... );
//------------------------------------------------------------------------
//	Etc 
inline int RectWidth( RECT& rc )	{ return ( rc.right - rc.left ); }
inline int RectHeight( RECT& rc )	{ return ( rc.bottom - rc.top ); }
//------------------------------------------------------------------------
//	Dll 
#define GETPROCADDRESS( Module, APIName, Temp ) \
	Temp = GetProcAddress( Module, #APIName ); \
	if( Temp ) \
	*(FARPROC*)&_##APIName = Temp

#define PLACEHOLDERPROC( APIName ) \
	_##APIName = Dummy_##APIName


#endif	//	_PUTCOMMON_H_
