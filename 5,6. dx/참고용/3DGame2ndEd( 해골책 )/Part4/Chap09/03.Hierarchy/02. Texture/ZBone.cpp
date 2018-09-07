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
	return 1;
}

int	ZBone::DrawBBox()
{
	return 1;
}

