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

	// 기본 local TM복사
	memcpy( &m_matLocal, &pMesh->m_tm, sizeof m_matLocal );
	D3DXMatrixIdentity( &m_matAni );
	D3DXMatrixIdentity( &m_matTM );
}

D3DXMATRIXA16* ZNode::Animate( float fFrame, D3DXMATRIXA16* pParentTM )
{
	m_matTM = m_matLocal * m_matAni * *pParentTM;
	return &m_matTM;
}

ZNode::~ZNode()
{
}
