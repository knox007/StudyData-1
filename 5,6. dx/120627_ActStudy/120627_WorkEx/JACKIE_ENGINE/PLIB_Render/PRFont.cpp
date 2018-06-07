#include "StdAfx.h"
#include "PRFont.h"
#include "PUTCommon.h"
//----------------------------------------------------------------------------
void CPRFont::ClearMembers()	
{ 
	PUT_SAFE_RELEASE(m_pFont); 
}//	ClearMembers
//----------------------------------------------------------------------------
bool CPRFont::Init( LPDIRECT3DDEVICE9 pDev, WCHAR* ptszFaceName, int nSize, bool bBold /* = false */, bool bItalic /* = false */ )
{
	PUT_SAFE_RELEASE( m_pFont );
	HRESULT hr = 0;
	hr = D3DXCreateFontW(	pDev,
							-nSize,
							0,
							bBold ? 800 : 0,
							1,
							bItalic,
							DEFAULT_CHARSET,
							OUT_DEFAULT_PRECIS,
							DEFAULT_QUALITY,
							DEFAULT_PITCH | FF_DONTCARE,
							ptszFaceName,
							&m_pFont );
	if( FAILED( hr ) )
	{
		PUTSHOWERR(PUT_CSTR_TCHAR("CPRFont::Init - D3DXCreateFont() failed" ) );
		return false;
	}

	return true;							
}//	Init
//----------------------------------------------------------------------------
void CPRFont::Print( TCHAR* ptszText, int nPosX, int nPosY, DWORD dwColor, LPD3DXSPRITE sprite /* = NULL */, int nTextBoxWid /* = 0 */, int nTextBoxHei /* = 0 */, FONTALIGNMENT alignment /* = FA_LEFT */ )
{
	if( !m_pFont )
		return;

	DWORD dwFormat = DT_EXPANDTABS;
	
	if( nTextBoxWid == 0 )
		dwFormat |= DT_NOCLIP;
	else
	{
		dwFormat |= DT_WORDBREAK;
		switch( alignment )
		{
		case FA_LEFT:
			dwFormat |= DT_LEFT;
			break;

		case FA_CENTER:
			dwFormat |= DT_CENTER;
			break;

		case FA_RIGHT:
			dwFormat |= DT_RIGHT;
			break;

		case FA_TOPRIGHT:
			dwFormat |= DT_TOP | DT_RIGHT;
			break;

		case FA_BOTTOMRIGHT:
			dwFormat |= DT_BOTTOM | DT_RIGHT;
			break;

		case FA_TOPLEFT:
			dwFormat |= DT_TOP | DT_LEFT;
			break;

		case FA_BOTTOMLEFT:
			dwFormat |= DT_BOTTOM | DT_LEFT;
			break;
		}//	switch( alignment )

		if( nTextBoxHei == 0 )
			nTextBoxHei = 2000;		
	}

	RECT rect = { nPosX, nPosY, nPosX + nTextBoxWid, nPosY + nTextBoxHei };
	m_pFont->DrawText( sprite, ptszText, -1, &rect, dwFormat, dwColor );
}//	Print
//-----------------------------------------------------------------------------------
void CPRFont::OnLostDevice()
{
	if( m_pFont )
		m_pFont->OnLostDevice();
}//	OnLostDevice
//-----------------------------------------------------------------------------------
void CPRFont::OnResetDevice()
{
	if( m_pFont )
		m_pFont->OnResetDevice();
}//	OnResetDevice
//-----------------------------------------------------------------------------------
//	EOF