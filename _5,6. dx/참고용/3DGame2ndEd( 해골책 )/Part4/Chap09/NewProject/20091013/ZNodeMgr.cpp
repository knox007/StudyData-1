#include "ZNodeMgr.h"
#include "ZSceneMgr.h"



ZNodeMgr::ZNodeMgr( LPDIRECT3DDEVICE9 pDev, ZCParsedData* pData, SKINMETHOD sm )
{
	int		i;

	m_pDev = pDev;
	D3DXMatrixIdentity( &m_matTM );

	// copy info
	m_info.nObjectCount		= pData->m_info.nObjectCount;
	m_info.nSkinType		= pData->m_info.nSkinType;
	m_info.nMeshCount		= pData->m_info.nMeshCount;
	m_info.fAnimationStart	= pData->m_info.fAnimationStart;
	m_info.fAnimationEnd	= pData->m_info.fAnimationEnd;
	m_info.nKeyType			= pData->m_info.nKeyType;
	m_info.BoneTable		= pData->m_info.BoneTable;
	m_info.strObjectNameTable = pData->m_info.strObjectNameTable;

	// 매트릭스 팔레트를 Bone의 개수로
	m_matPalette.resize( m_info.BoneTable.size() );

	for( i = 0 ; i < pData->m_meshList.size() ; i++ )
	{
		if( !_IsBone( i ) )
			m_info.MeshTable.push_back( i );
	}

	// copy materials 
	for( i = 0 ; i < pData->m_materials.size() ; i++ )
		g_pSceneMgr->GetMaterialMgr()->AddMaterial( &pData->m_materials[i] );

	// copy meshes
	std::list<ZCMesh*>::iterator	it;
	ZNode*					pNode;
	int size = pData->m_meshList.size();
	D3DXVECTOR3	vMinBox, vMaxBox;
	D3DXVECTOR3	vMin, vMax;
	vMinBox = D3DXVECTOR3( 0, 0, 0 );
	vMaxBox = D3DXVECTOR3( 0, 0, 0 );
	for( i = 0, it = pData->m_meshList.begin() ; it != pData->m_meshList.end() ; i++, it++ )
	{
		// 부모가 없는 노드는 0번노드를 부모로 한다.
		if( (*it)->m_nParentID == -1 ) 
			(*it)->m_nParentID = 0;

		// Bone이나 Biped라면 ZBone으로 생성
		if( !( (*it)->m_strNodeType.compare( "BoneGeometry" ) ) || 
			!( (*it)->m_strNodeType.compare( "Biped_Object" ) ) || 
			!( (*it)->m_strNodeType.compare( "Bone" ) ) ||
			( (*it)->m_nObjectID == 0 ) )
		{
			pNode = (ZNode*)(new ZBone( pDev, *it ));
		}
		else	// Editable_Mesh라면 ZMesh로 생성
		if( !( (*it)->m_strNodeType.compare( "Editable_mesh" ) ) )
		{
			if( (*it)->m_isSkinned )	// Skin이 있으면 ZSkinnedMesh로 생성
			{
				switch( sm )	// 스키닝 방법에 따른 객체생성
				{
					case SKINMETHOD_SW :
						pNode = (ZNode*)(new ZSWSkinnedMesh( pDev, *it ));
						break;
					case SKINMETHOD_FF :
						pNode = (ZNode*)(new ZFFSkinnedMesh( pDev, *it ));
						break;
					case SKINMETHOD_VS :
						pNode = (ZNode*)(new ZFFSkinnedMesh( pDev, *it ));
						break;
				}
				((ZSkinnedMesh*)pNode)->SetMatrixPalette( &m_matPalette );
			}
			else	// Skin이 없으면 ZRigidMesh로 생성
				pNode = (ZNode*)(new ZRigidMesh( pDev, *it ));
		}
		else	// 이것도 저것도 아니면 그냥 ZNode로 생성
			pNode = new ZNode( pDev, *it );

		pNode->GetBBox( &vMin, &vMax );
		if( D3DXVec3Length( &vMinBox ) < D3DXVec3Length( &vMin ) ) vMinBox = vMin;
		if( D3DXVec3Length( &vMaxBox ) < D3DXVec3Length( &vMax ) ) vMaxBox = vMax;

		m_nodes.push_back( pNode );
	}
	m_bboxMinOrig = vMinBox;
	m_bboxMaxOrig = vMaxBox;
	m_fRadius = ( D3DXVec3Length( &vMinBox ) > D3DXVec3Length( &vMaxBox ) ) ? D3DXVec3Length( &vMinBox ) : D3DXVec3Length( &vMaxBox );
}

ZNodeMgr::~ZNodeMgr()
{
	stl_wipe_vector( m_matPalette );
//	stl_wipe_vector( m_pMaterialMgr );
	for( int i = 0 ; i < m_nodes.size() ; i++ ) S_DEL( m_nodes[i] );
	stl_wipe_vector( m_nodes );
}

int ZNodeMgr::Animate( float fFrame )
{
	int				i;
	int				id;
	int				size;
	D3DXMATRIXA16	m;
	D3DXMATRIXA16*	pTM;

	if( fFrame > m_info.fAnimationEnd ) fFrame = m_info.fAnimationEnd;
	if( fFrame < m_info.fAnimationStart ) fFrame = m_info.fAnimationStart;

	// 먼저 뼈대(bone)들의 애니메이션 행렬을 만들어 둔다
	size = m_info.BoneTable.size();
	for( i = 0 ; i < size ; i++ )
	{
		id =  m_nodes[m_info.BoneTable[i]]->GetParentID();
		pTM = m_nodes[id]->GetMatrixTM();
		m_nodes[m_info.BoneTable[i]]->Animate( fFrame, pTM );
		pTM = ((ZBone*)m_nodes[m_info.BoneTable[i]])->GetMatrixSkin();
		// 스키닝을 위해 스킨행렬을 매트릭스 팔레트에 등록
		m_matPalette[i] = *((D3DXMATRIX*)pTM); 
	}

	// 뼈대가 아닌 것들의 애니메이션 행렬을 만든다
	size = m_info.MeshTable.size();
	for( i = 0 ; i < size ; i++ )
	{
		id =  m_nodes[m_info.MeshTable[i]]->GetParentID();
		pTM = m_nodes[id]->GetMatrixTM();
		m_nodes[m_info.MeshTable[i]]->Animate( fFrame, pTM );
	}

	return 1;
}

int ZNodeMgr::Draw( int nNodeType )
{
	int		i;
	int		size;


	if( nNodeType == ZNode::NODE_MESH )
	{
		size = m_info.MeshTable.size();
		for( i = 0 ; i < size ; i++ )
		{
//			m_pDev->SetMaterial( &m_materials[m_nodes[m_info.MeshTable[i]]->GetMaterialID()].material );
//			m_pDev->SetTexture( 0, m_materials[m_nodes[m_info.MeshTable[i]]->GetMaterialID()].pTex[0] );
			g_pSceneMgr->GetMaterialMgr()->ApplyMaterial( m_nodes[m_info.MeshTable[i]]->GetMaterialID() );
			m_pDev->SetTransform( D3DTS_WORLD, &m_matTM );
			m_nodes[m_info.MeshTable[i]]->Draw( &m_matTM );
			m_pDev->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
		}
	}
	else
	if( nNodeType == ZNode::NODE_BONE )
	{
		size = m_info.BoneTable.size();
		for( i = 0 ; i < size ; i++ )
		{
//			m_pDev->SetMaterial( &m_materials[m_nodes[m_info.BoneTable[i]]->GetMaterialID()].material );
//			m_pDev->SetTexture( 0, m_materials[m_nodes[m_info.BoneTable[i]]->GetMaterialID()].pTex[0] );
			g_pSceneMgr->GetMaterialMgr()->ApplyMaterial( m_nodes[m_info.MeshTable[i]]->GetMaterialID() );
			m_pDev->SetTransform( D3DTS_WORLD, &m_matTM );
			m_nodes[m_info.BoneTable[i]]->Draw( &m_matTM );
			m_pDev->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
		}
	}
	else	// NODE_NODE
	{
		size = m_nodes.size();
		for( i = 0 ; i < size ; i++ )
		{
//			m_pDev->SetMaterial( &m_materials[m_nodes[i]->GetMaterialID()].material );
//			m_pDev->SetTexture( 0, m_materials[m_nodes[i]->GetMaterialID()].pTex[0] ); 
			g_pSceneMgr->GetMaterialMgr()->ApplyMaterial( m_nodes[m_info.MeshTable[i]]->GetMaterialID() );
			m_pDev->SetTransform( D3DTS_WORLD, &m_matTM );
			m_nodes[i]->Draw( &m_matTM );
			m_pDev->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
		}
	}

	return 1;
}

int ZNodeMgr::DrawBBox( int nNodeType )
{
	int		i;
	int		size;

	m_pDev->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );
	size = m_nodes.size();
	for( i = 0 ; i < size ; i++ )
	{
		m_pDev->SetTransform( D3DTS_WORLD, &m_matTM );
		if( nNodeType == ZNode::NODE_NODE ) m_nodes[i]->DrawBBox( &m_matTM );
		else if( nNodeType == ZNode::NODE_BONE ) { if( m_nodes[i]->GetNodeType() == ZNode::NODE_BONE ) m_nodes[i]->DrawBBox( &m_matTM ); }
		else if( nNodeType == ZNode::NODE_MESH ) { if( m_nodes[i]->GetNodeType() == ZNode::NODE_MESH ) m_nodes[i]->DrawBBox( &m_matTM ); }
	}
	m_pDev->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );

	return 1;
}

