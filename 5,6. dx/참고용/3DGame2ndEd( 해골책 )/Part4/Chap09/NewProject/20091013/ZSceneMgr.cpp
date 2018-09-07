#include "zscenemgr.h"
#include "ZFLog.h"

ZSceneMgr::ZSceneMgr(void)
{
	m_pDev			= NULL;
	m_fFrameRate	= 30.0f;
	m_pNodeMgr		= NULL;
	m_pTextureMgr	= NULL;
	m_pMaterialMgr	= NULL;
	m_pCameraMgr	= NULL;

	m_pData			= NULL;
	m_pParser		= NULL;
}

ZSceneMgr::~ZSceneMgr(void)
{
	S_DEL( m_pNodeMgr );
	S_DEL( m_pTextureMgr );
	S_DEL( m_pMaterialMgr );
	S_DEL( m_pCameraMgr );

	S_DEL( m_pParser );
	S_DEL( m_pData );
}

BOOL ZSceneMgr::_BuildManagers( LPDIRECT3DDEVICE9 pDev, ZCParsedData* pData, ZNodeMgr::SKINMETHOD sm )
{
	S_DEL( m_pTextureMgr );
	S_DEL( m_pMaterialMgr );
	S_DEL( m_pNodeMgr );
	S_DEL( m_pCameraMgr );

	m_pDev			= pDev;
	m_fFrameRate	= pData->m_info.fFrameRate;
	// 각 매니저의 생성순서는 매우 중요하다.
	// ZNodeMgr에서 ZMaterialMgr를 사용하고, 
	// ZMaterialMgr에서 ZTextureMgr를 사용한다.
	m_pTextureMgr	= new ZTextureMgr( pDev );
	m_pMaterialMgr	= new ZMaterialMgr( pDev, pData->m_info.fFrameRate );
	m_pNodeMgr		= new ZNodeMgr( pDev, pData, sm );

//	m_pCameraMgr	= new ZCameraMgr( pDev, pData );
	
	return TRUE;
}

BOOL ZSceneMgr::Open( LPDIRECT3DDEVICE9 pDev, char* lpszFilename, ZNodeMgr::SKINMETHOD sm )
{
	S_DEL( m_pData );
	S_DEL( m_pParser );

	m_pParser = new ZCParser();
	m_pData = new ZCParsedData();

	if( !m_pParser->Parse( m_pData, lpszFilename ) )
	{
		S_DEL( m_pData );
		return FALSE;
	}

	std::list<ZCMesh*>::iterator		it;	// STL반복자 선언
	for( it = m_pData->m_meshList.begin() ; it != m_pData->m_meshList.end() ; it++ )
	{
		g_pLog->Log( "-------------------------------------" );
		g_pLog->Log( "ID:[%d,%s]", (*it)->m_nObjectID, m_pData->m_info.strObjectNameTable[(*it)->m_nObjectID].c_str() );
		g_pLog->Log( "Parent:[%d,%s]", (*it)->m_nParentID, (*it)->m_nParentID == -1 ? "undefined" : m_pData->m_info.strObjectNameTable[(*it)->m_nParentID].c_str() );
		g_pLog->Log( "Vertex:[%d]", (*it)->m_vertex.size() );
		g_pLog->Log( "Index:[%d]", (*it)->m_triindex.size() );
		g_pLog->Log( "MergedVertex:[%d]", (*it)->m_vtxFinal.size() );
		g_pLog->Log( "Skin:[%s]", (*it)->m_isSkinned ? "true" : "false" );
		g_pLog->Log( "-------------------------------------" );
	}

	_BuildManagers( pDev, m_pData, sm );

	// parser는 내부에 xml tree데이터를 보관하고 있으므로 메모리 사용량이 많다.
	// 사용완료 후에는 즉시 날려버린다.
	S_DEL( m_pParser );

	return TRUE;
}

void ZSceneMgr::SetFrame( float frame )
{
	m_pMaterialMgr->SetFrame( frame );
	m_pNodeMgr->SetFrame( frame );

//	m_pCameraMgr->Animate( frame );
}

void ZSceneMgr::Draw()
{
	m_pNodeMgr->Draw( 2 );	// // 0 = all, 1 = bone, 2 = mesh
}

void ZSceneMgr::DrawBBox()
{
	m_pNodeMgr->DrawBBox( 2 );	// // 0 = all, 1 = bone, 2 = mesh
}

