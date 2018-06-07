#include "ZSkinnedMesh.h"

ZSkinnedMesh::ZSkinnedMesh( LPDIRECT3DDEVICE9 pDev, ZCMesh* pMesh ) : ZMesh( pDev, pMesh )
{
	_CreateVIB( pMesh );
}

ZSkinnedMesh::~ZSkinnedMesh()
{
	stl_wipe_vector( m_vtx );
	stl_wipe_vector( m_idx );
}

int ZSkinnedMesh::_CreateVIB( ZCMesh* pMesh )
{
	int		i;
	int		size;
	VOID*	pV;		// 정점버퍼 lock했을때 얻어오는 값
	VOID*	pI;		// 엔딕스버퍼 lock했을때 얻어오는 값

	size = pMesh->m_vtxFinal.size();
	m_dwFVF = ZSkinnedVertex::FVF;
	m_vtx.resize( size );
	m_nVerts = size;
	for( i = 0 ;  i < size ; i++ )
	{
		m_vtx[i].p.x = pMesh->m_vtxFinal[i].p.x;
		m_vtx[i].p.y = pMesh->m_vtxFinal[i].p.y;
		m_vtx[i].p.z = pMesh->m_vtxFinal[i].p.z;
		m_vtx[i].b[0] = pMesh->m_vtxFinal[i].b[0];
		m_vtx[i].b[1] = pMesh->m_vtxFinal[i].b[1];
		m_vtx[i].b[2] = pMesh->m_vtxFinal[i].b[2];
		m_vtx[i].i = (DWORD)pMesh->m_vtxFinal[i].i;
		m_vtx[i].n.x = pMesh->m_vtxFinal[i].n.x;
		m_vtx[i].n.y = pMesh->m_vtxFinal[i].n.y;
		m_vtx[i].n.z = pMesh->m_vtxFinal[i].n.z;
		m_vtx[i].t.x = pMesh->m_vtxFinal[i].t.x;
		m_vtx[i].t.y = pMesh->m_vtxFinal[i].t.y;
	}
	// 정점 버퍼 생성
	m_pDev->CreateVertexBuffer( size * sizeof(ZSkinnedVertex), 0, m_dwFVF, D3DPOOL_DEFAULT, &m_pVB, NULL );
	m_pVB->Lock( 0, size * sizeof(ZSkinnedVertex), (void**)&pV, 0 );
	memcpy( pV, &m_vtx[0], size * sizeof(ZSkinnedVertex) );
	m_pVB->Unlock();

	// 인덱스 생성
	size = pMesh->m_idxFinal.size();
	m_idx.resize( size );
	m_nTriangles = size;
	for( i = 0 ; i < size ; i++ )
	{
		m_idx[i].i[0] = (WORD)pMesh->m_idxFinal[i].i[0];
		m_idx[i].i[1] = (WORD)pMesh->m_idxFinal[i].i[1];
		m_idx[i].i[2] = (WORD)pMesh->m_idxFinal[i].i[2];
	}

	// 인덱스 버퍼 생성
    m_pDev->CreateIndexBuffer( size * sizeof(Index3w), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIB, NULL );
    m_pIB->Lock( 0, size * sizeof(Index3w), (void**)&pI, 0 );
	memcpy( pI, &m_idx[0], size * sizeof(Index3w) );
    m_pIB->Unlock();

	return 1;
}

int ZSkinnedMesh::Draw()
{
	m_pDev->SetTransform( D3DTS_WORLD, &m_matTM );
	m_pDev->SetStreamSource( 0, m_pVB, 0, sizeof(ZSkinnedVertex) );
	m_pDev->SetFVF( m_dwFVF );
	m_pDev->SetIndices( m_pIB );
	m_pDev->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, m_nVerts, 0, m_nTriangles );
	return 1;
}

int ZSkinnedMesh::DrawBBox()
{
	return 1;
}
