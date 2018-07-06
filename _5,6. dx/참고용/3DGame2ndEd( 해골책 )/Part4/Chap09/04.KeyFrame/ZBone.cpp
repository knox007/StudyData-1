#include "ZBone.h"

ZBone::ZBone( LPDIRECT3DDEVICE9 pDev, ZCMesh* pMesh ) : ZNode( pDev, pMesh )
{
	m_nNodeType = NODE_BONE;
}

ZBone::~ZBone()
{
}
	
int	ZBone::Draw()
{

	BOXVERTEX vtx[8];
	vtx[0] = BOXVERTEX( -1,  1,  1 , 0xffff0000 );		/// v0
	vtx[1] = BOXVERTEX(  1,  1,  1 , 0xffff0000 );		/// v1
	vtx[2] = BOXVERTEX(  1,  1, -1 , 0xffff0000 );		/// v2
	vtx[3] = BOXVERTEX( -1,  1, -1 , 0xffff0000 );		/// v3
	vtx[4] = BOXVERTEX( -1, -1,  1 , 0xffff0000 );		/// v4
	vtx[5] = BOXVERTEX(  1, -1,  1 , 0xffff0000 );		/// v5
	vtx[6] = BOXVERTEX(  1, -1, -1 , 0xffff0000 );		/// v6
	vtx[7] = BOXVERTEX( -1, -1, -1 , 0xffff0000 );		/// v7

	Index3w		idx[12] = 
	{ 
		{ 0, 1, 2 }, { 0, 2, 3 },	/// À­¸é
		{ 4, 6, 5 }, { 4, 7, 6 },	/// ¾Æ·§¸é
		{ 0, 3, 7 }, { 0, 7, 4 },	/// ¿Þ¸é
		{ 1, 5, 6 }, { 1, 6, 2 },	/// ¿À¸¥¸é
		{ 3, 2, 6 }, { 3, 6, 7 },	/// ¾Õ¸é
		{ 0, 4, 5 }, { 0, 5, 1 }	/// µÞ¸é
	};

	m_pDev->MultiplyTransform( D3DTS_WORLD, &m_matTM );
	m_pDev->SetFVF( BOXVERTEX::FVF );
	m_pDev->DrawIndexedPrimitiveUP( D3DPT_TRIANGLELIST, 0, 8, 12, idx, D3DFMT_INDEX16, vtx, sizeof BOXVERTEX );

//	ZNode::DrawBBox();
	return 1;
}