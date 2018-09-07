#include "ZRigidMesh.h"

ZRigidMesh::ZRigidMesh( LPDIRECT3DDEVICE9 pDev, ZCMesh* pMesh ) : ZMesh( pDev, pMesh )
{
	_CreateVIB( pMesh );
}

ZRigidMesh::~ZRigidMesh()
{
	stl_wipe_vector( m_vtx );
	stl_wipe_vector( m_idx );
}

int ZRigidMesh::_CreateVIB( ZCMesh* pMesh )
{
	int		i;
	int		size;
	VOID*	pV;		// 정점버퍼 lock했을때 얻어오는 값
	VOID*	pI;		// 엔딕스버퍼 lock했을때 얻어오는 값

	size = pMesh->m_vtxFinal.size();
	m_dwFVF = ZRigidVertex::FVF;
	m_vtx.resize( size );
	m_nVerts = size;
	m_bboxMax = D3DXVECTOR3( pMesh->m_vtxFinal[0].p.x, pMesh->m_vtxFinal[0].p.y, pMesh->m_vtxFinal[0].p.z );
	m_bboxMin = D3DXVECTOR3( pMesh->m_vtxFinal[0].p.x, pMesh->m_vtxFinal[0].p.y, pMesh->m_vtxFinal[0].p.z );

	for( i = 0 ;  i < size ; i++ )
	{
		m_vtx[i].p.x = pMesh->m_vtxFinal[i].p.x;
		m_vtx[i].p.y = pMesh->m_vtxFinal[i].p.y;
		m_vtx[i].p.z = pMesh->m_vtxFinal[i].p.z;
		m_vtx[i].n.x = pMesh->m_vtxFinal[i].n.x;
		m_vtx[i].n.y = pMesh->m_vtxFinal[i].n.y;
		m_vtx[i].n.z = pMesh->m_vtxFinal[i].n.z;
		m_vtx[i].t.x = pMesh->m_vtxFinal[i].t.x;
		m_vtx[i].t.y = pMesh->m_vtxFinal[i].t.y;

		// 맥스스크립트로 얻어지는 경계상자는 이상할 경우가 많아서 직접 계산한다
		if( m_vtx[i].p.x > m_bboxMax.x ) m_bboxMax.x = m_vtx[i].p.x;
		if( m_vtx[i].p.y > m_bboxMax.y ) m_bboxMax.y = m_vtx[i].p.y;
		if( m_vtx[i].p.z > m_bboxMax.z ) m_bboxMax.z = m_vtx[i].p.z;
		if( m_vtx[i].p.x < m_bboxMin.x ) m_bboxMin.x = m_vtx[i].p.x;
		if( m_vtx[i].p.y < m_bboxMin.y ) m_bboxMin.y = m_vtx[i].p.y;
		if( m_vtx[i].p.z < m_bboxMin.z ) m_bboxMin.z = m_vtx[i].p.z;
	}
	// 정점 버퍼 생성
	m_pDev->CreateVertexBuffer( size * sizeof(ZRigidVertex), 0, m_dwFVF, D3DPOOL_DEFAULT, &m_pVB, NULL );
	m_pVB->Lock( 0, size * sizeof(ZRigidVertex), (void**)&pV, 0 );
	memcpy( pV, &m_vtx[0], size * sizeof(ZRigidVertex) );
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

int ZRigidMesh::Draw()
{
	m_pDev->MultiplyTransform( D3DTS_WORLD, &m_matTM );
	m_pDev->SetStreamSource( 0, m_pVB, 0, sizeof(ZRigidVertex) );
	m_pDev->SetFVF( m_dwFVF );
	m_pDev->SetIndices( m_pIB );
	m_pDev->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, m_nVerts, 0, m_nTriangles );
	return 1;
}

int ZRigidMesh::DrawBBox()
{
	return 1;
}
