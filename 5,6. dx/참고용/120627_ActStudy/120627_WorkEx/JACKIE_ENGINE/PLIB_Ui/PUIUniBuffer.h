#ifndef	_JUIUNIBUFFER_H_
#define _JUIUNIBUFFER_H_
#pragma once

#include <usp10.h>
//#include <tchar.h>


class CPUIFontNode;

class CPUIUniBuffer
{
public:
	CPUIUniBuffer( int nInitialsize = 1 )	
	{
		InitMembersEx( nInitialsize );		
	}
	~CPUIUniBuffer()						{ ClearMembers(); }
	void	InitMembers();
	void	InitMembersEx( int nInitialsize )
	{ 
		InitMembers(); 
		if( nInitialsize > 0 )
			SetBufferSize( nInitialsize );
	}
	void	ClearMembers();

	static	void	Initialize();
	static	void	UnInitialize();

	//	Buffer
	bool			SetBufferSize( int nSize );
	int				GetBufferSize()				{ return m_nBufferSize; }	
	int				GetTextSize()				{ return lstrlenW( m_ptszBuffer ); }
	const	WCHAR*	GetBuffer()	{ return m_ptszBuffer; }
	const	WCHAR&	operator[]( int n ) const	{ return m_ptszBuffer[n]; }
	WCHAR&			operator[]( int n );
	void			Clear();


	//	Font	
	void			SetFontNode( CPUIFontNode* pFontNode )	{ m_pFontNode = pFontNode; }
	CPUIFontNode*	GetFontNode()							{ return m_pFontNode; }


	//	Text
	bool	InsertChar( int nID, WCHAR tChar );
	bool	RemoveChar( int nID );
	bool	InsertString( int nID, const WCHAR* ptszText, int nCount = -1 );
	bool	SetText( const WCHAR* ptszText );


	//	Uniscribe
	HRESULT	CPtoX( int nCP, BOOL bTrail, int* pnX );
	HRESULT	XtoCP( int nX, int* pnCP, int* pnTrail );
	void	GetPriorItemPos( int nCP, int* pnPrior );
	void	GetNextItemPos( int nCP, int* pnPrior );


private:
	HRESULT		Analyse();

	//	Dummy Function
	static	HRESULT	WINAPI	
	Dummy_ScriptApplyDigitSubstitution( const SCRIPT_DIGITSUBSTITUTE*, SCRIPT_CONTROL*, SCRIPT_STATE* )
	{ return E_NOTIMPL; }

	static	HRESULT	WINAPI
	Dummy_ScriptStringAnalyse(	HDC, const void*, 
								int, int, int, DWORD, int, 
								SCRIPT_CONTROL*, SCRIPT_STATE*, const int*,
								SCRIPT_TABDEF*, const BYTE*, SCRIPT_STRING_ANALYSIS* )
	{ return E_NOTIMPL; }
	
	static	HRESULT	WINAPI
	Dummy_ScriptStringCPtoX(	SCRIPT_STRING_ANALYSIS, int, BOOL, int* )
	{ return E_NOTIMPL; }

	static	HRESULT WINAPI
	Dummy_ScriptStringXtoCP(	SCRIPT_STRING_ANALYSIS, int, int*, int* )
	{ return E_NOTIMPL; }

	static	HRESULT WINAPI
	Dummy_ScriptStringFree(		SCRIPT_STRING_ANALYSIS* )
	{ return E_NOTIMPL; }

	static	const SCRIPT_LOGATTR* WINAPI
	Dummy_ScriptString_pLogAttr(	SCRIPT_STRING_ANALYSIS )
	{ return NULL; }

	static	const int* WINAPI
	Dummy_ScriptString_pcOutChars(	SCRIPT_STRING_ANALYSIS )
	{ return NULL; }


	//	Function Ptr
	static	HRESULT	(WINAPI* _ScriptApplyDigitSubstitution)( const SCRIPT_DIGITSUBSTITUTE*, SCRIPT_CONTROL*, SCRIPT_STATE* );
	static	HRESULT (WINAPI* _ScriptStringAnalyse)( HDC, const void*,
													int, int, int, DWORD, int,
													SCRIPT_CONTROL*, SCRIPT_STATE*, const int*,
													SCRIPT_TABDEF*, const BYTE*, SCRIPT_STRING_ANALYSIS* );
	static	HRESULT (WINAPI* _ScriptStringCPtoX)(	SCRIPT_STRING_ANALYSIS, int, BOOL, int* );
	static	HRESULT	(WINAPI* _ScriptStringXtoCP)(	SCRIPT_STRING_ANALYSIS, int, int*, int* );
	static	HRESULT	(WINAPI* _ScriptStringFree)(	SCRIPT_STRING_ANALYSIS* );
	static	const	SCRIPT_LOGATTR*	(WINAPI* _ScriptString_pLogAttr)(	SCRIPT_STRING_ANALYSIS );
	static	const	int* (WINAPI* _ScriptString_pcOutChars)(	SCRIPT_STRING_ANALYSIS );


	static	HINSTANCE		s_hDll;
	WCHAR*					m_ptszBuffer;
	int						m_nBufferSize;

	CPUIFontNode*			m_pFontNode;
	bool					m_bAnalyseRequired;
	SCRIPT_STRING_ANALYSIS	m_Analysis;


};
#endif	//	_JUIUNIBUFFER_H_