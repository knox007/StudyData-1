#include ".\ztexturemgr.h"

ZTextureMgr::ZTextureMgr(void)
{
	m_pDev = NULL;
}

ZTextureMgr::ZTextureMgr( LPDIRECT3DDEVICE9 pDev )
{
	m_pDev = pDev;
}

ZTextureMgr::~ZTextureMgr(void)
{
//	stl_wipe( m_textures );
}

LPDIRECT3DTEXTURE9 ZTextureMgr::_FindItem( const char* lpszTex )
{
	itTexture = m_textures.find( lpszTex );
	if( itTexture == m_textures.end() ) 
		return NULL;
	else 
		return (*itTexture).second;
}
LPDIRECT3DTEXTURE9 ZTextureMgr::AddItem( const char* lpszTex )
{
	LPDIRECT3DTEXTURE9	pTex;
	pTex = _FindItem( lpszTex );
	if( !pTex )
	{
		D3DXCreateTextureFromFile( m_pDev, lpszTex, &pTex );
		if( !pTex )
		{
			return NULL;
		}
		else
		{
			m_textures[lpszTex] = pTex;
			return pTex;
		}
	}
	else
		return pTex;
}

LPDIRECT3DTEXTURE9 ZTextureMgr::GetItem( const char* lpszTex )
{
	return AddItem( lpszTex );
}

void ZTextureMgr::DelItem( const char* lpszTex )
{
	m_textures.erase( lpszTex );
}
