#ifndef _ZTEXTUREMGR_H_
#define _ZTEXTUREMGR_H_

#include <d3d9.h>
#include <d3dx9.h>
#include <map>
#include "define.h"

class ZTextureMgr
{
	LPDIRECT3DDEVICE9										m_pDev;
	std::map<std::string, LPDIRECT3DTEXTURE9>				m_textures;
	std::map<std::string, LPDIRECT3DTEXTURE9>::iterator		itTexture;

	LPDIRECT3DTEXTURE9 _FindItem( const char* lpszTex );

public:
	ZTextureMgr(void);
	ZTextureMgr( LPDIRECT3DDEVICE9 pDev );
	~ZTextureMgr(void);
	
	LPDIRECT3DTEXTURE9	AddItem( const char* lpszTex );
	LPDIRECT3DTEXTURE9	GetItem( const char* lpszTex );
	void DelItem( const char* lpszTex );
};

#endif //  _ZTEXTUREMGR_H_