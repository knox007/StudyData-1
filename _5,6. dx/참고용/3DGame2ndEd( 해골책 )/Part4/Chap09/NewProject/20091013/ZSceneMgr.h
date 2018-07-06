#ifndef _ZSCENEMGR_H_
#define _ZSCENEMGR_H_

#include "define.h"
#include "ZDefine.h"
#include "ZNodeMgr.h"
//#include "ZCameraMgr.h"
#include "ZTextureMgr.h"
#include "ZMaterialMgr.h"
#include "ZCParser.h"
#include "ZCParsedData.h"
#include "ZCameraMgr.h"

// 전방선언
class ZNodeMgr;
class ZTextureMgr;
class ZMaterialMgr;

class ZSceneMgr
{
protected:
	LPDIRECT3DDEVICE9		m_pDev;			/// D3D디바이스
	float					m_fFrameRate;
	ZNodeMgr*				m_pNodeMgr;
	ZTextureMgr*			m_pTextureMgr;
	ZMaterialMgr*			m_pMaterialMgr;
	ZCParsedData*			m_pData;
	ZCParser*				m_pParser;
	ZCameraMgr*				m_pCameraMgr;

protected:
	BOOL	_BuildManagers( LPDIRECT3DDEVICE9 pDev, ZCParsedData* pData, ZNodeMgr::SKINMETHOD sm );

public:
	ZSceneMgr( void );
	~ZSceneMgr( void );

	ZNodeMgr*		GetNodeMgr() { return m_pNodeMgr; }
	ZTextureMgr*	GetTextureMgr() { return m_pTextureMgr; }
	ZMaterialMgr*	GetMaterialMgr() { return m_pMaterialMgr; }
	ZCParsedData*	GetParsedData() { return m_pData; }
	ZCParser*		GetParser()	{ return m_pParser; }

	BOOL	Open( LPDIRECT3DDEVICE9 pDev, char* lpszFilename, ZNodeMgr::SKINMETHOD sm );
	void	SetFrame( float frame );
	void	SetTime( float time ) { SetFrame( time * m_fFrameRate ); }
	void	Draw();
	void	DrawBBox();
};

DECLARE ZSceneMgr* g_pSceneMgr;

#endif // _ZSCENEMGR_H_