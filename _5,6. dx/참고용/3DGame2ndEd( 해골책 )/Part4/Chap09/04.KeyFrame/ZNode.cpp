#include "ZNode.h"

ZNode::ZNode( LPDIRECT3DDEVICE9 pDev, ZCMesh* pMesh )
{
	m_pDev = pDev;
	m_nNodeType = NODE_NODE;
	m_nObjectID = pMesh->m_nObjectID;
	m_nParentID = pMesh->m_nParentID;

	m_bboxMax.x = pMesh->m_bboxMax.x;
	m_bboxMax.y = pMesh->m_bboxMax.y;
	m_bboxMax.z = pMesh->m_bboxMax.z;
	m_bboxMin.x = pMesh->m_bboxMin.x;
	m_bboxMin.y = pMesh->m_bboxMin.y;
	m_bboxMin.z = pMesh->m_bboxMin.z;
	m_nMaterialID = pMesh->m_nMaterialID;

	// �⺻ local TM����
	memcpy( &m_matLocal, &pMesh->m_tm, sizeof m_matLocal );
	D3DXMatrixIdentity( &m_matTM );

	m_pTrack = new ZTrack( pMesh->m_track );
}

D3DXMATRIXA16* ZNode::Animate( float fFrame, D3DXMATRIXA16* pParentTM )
{
	D3DXMATRIXA16*	pmatAni;

	// �ִϸ��̼� ����� �����.
	pmatAni = m_pTrack->Animate( fFrame );

	m_matTM = m_matLocal * *pmatAni;

	// ���� posŰ���� ������ local TM�� ��ǥ�� ����Ѵ�
	if( pmatAni->_41 == 0.0f && pmatAni->_42 == 0.0f && pmatAni->_43 == 0.0f )
	{
		m_matTM._41 = m_matLocal._41;
		m_matTM._42 = m_matLocal._42;
		m_matTM._43 = m_matLocal._43;
	}
	else	// posŰ���� ��ǥ������ �����Ѵ�(�̷��� ���� ������ TM�� pos������ �ι�����ȴ�)
	{
		m_matTM._41 = pmatAni->_41;
		m_matTM._42 = pmatAni->_42;
		m_matTM._43 = pmatAni->_43;
	}
	m_matTM = m_matTM * *pParentTM;
	return &m_matTM;
}

ZNode::~ZNode()
{
	S_DEL( m_pTrack );
}

int	ZNode::DrawBBox()
{
	BOXVERTEX vtx[8];
	vtx[0] = BOXVERTEX( m_bboxMin.x, m_bboxMax.y, m_bboxMax.z, 0xffff0000 );
	vtx[1] = BOXVERTEX( m_bboxMax.x, m_bboxMax.y, m_bboxMax.z, 0xffff0000 );
	vtx[2] = BOXVERTEX( m_bboxMax.x, m_bboxMax.y, m_bboxMin.z, 0xffff0000 );
	vtx[3] = BOXVERTEX( m_bboxMin.x, m_bboxMax.y, m_bboxMin.z, 0xffff0000 );
	vtx[4] = BOXVERTEX( m_bboxMin.x, m_bboxMin.y, m_bboxMax.z, 0xffff0000 );
	vtx[5] = BOXVERTEX( m_bboxMax.x, m_bboxMin.y, m_bboxMax.z, 0xffff0000 );
	vtx[6] = BOXVERTEX( m_bboxMax.x, m_bboxMin.y, m_bboxMin.z, 0xffff0000 );
	vtx[7] = BOXVERTEX( m_bboxMin.x, m_bboxMin.y, m_bboxMin.z, 0xffff0000 );

	Index3w		idx[12] = 
	{ 
		{ 0, 1, 2 }, { 0, 2, 3 },	/// ����
		{ 4, 6, 5 }, { 4, 7, 6 },	/// �Ʒ���
		{ 0, 3, 7 }, { 0, 7, 4 },	/// �޸�
		{ 1, 5, 6 }, { 1, 6, 2 },	/// ������
		{ 3, 2, 6 }, { 3, 6, 7 },	/// �ո�
		{ 0, 4, 5 }, { 0, 5, 1 }	/// �޸�
	};

	m_pDev->MultiplyTransform( D3DTS_WORLD, &m_matTM );
	m_pDev->SetFVF( BOXVERTEX::FVF );
	m_pDev->DrawIndexedPrimitiveUP( D3DPT_TRIANGLELIST, 0, 8, 12, idx, D3DFMT_INDEX16, vtx, sizeof BOXVERTEX );

	return 1;
}

