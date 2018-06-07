#include "ZNodeMgr.h"

ZNodeMgr::ZNodeMgr( LPDIRECT3DDEVICE9 pDev, ZCParsedData* pData )
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

	for( i = 0 ; i < pData->m_meshList.size() ; i++ )
	{
		if( !_IsBone( i ) )
			m_info.MeshTable.push_back( i );
	}

	// copy materials
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	string str;

	int size = pData->m_materialTable.size();
	m_materials.resize( size );

	for( i = 0 ; i < size ; i++ )
	{
		// ������ ��
		m_materials[i].opacity = pData->m_materialTable[i].opacity;	// �� ���� diffuse�� alpha������...

		// ������ Ȯ�걤 �Ӽ� ����
		D3DCOLORVALUE diffuse = { pData->m_materialTable[i].diffuse.r, pData->m_materialTable[i].diffuse.g, pData->m_materialTable[i].diffuse.b, m_materials[i].opacity };
		m_materials[i].material.Diffuse = diffuse;

		// ������ ȯ�汤 �Ӽ� ����
		D3DCOLORVALUE ambient = { pData->m_materialTable[i].ambient.r, pData->m_materialTable[i].ambient.g, pData->m_materialTable[i].ambient.b, m_materials[i].opacity };
		m_materials[i].material.Ambient = ambient;
		
		// ������ �ݻ籤 �Ӽ� ����
		D3DCOLORVALUE specular = { pData->m_materialTable[i].specular.r, pData->m_materialTable[i].specular.g, pData->m_materialTable[i].specular.b, m_materials[i].opacity };
		m_materials[i].material.Specular = specular;
		
		// ������ �߻걤 �Ӽ� ����
		D3DCOLORVALUE emissive = { pData->m_materialTable[i].emissive.r, pData->m_materialTable[i].emissive.g, pData->m_materialTable[i].emissive.b, m_materials[i].opacity };
		m_materials[i].material.Emissive = emissive;

		// �ݻ籤�� �������
		m_materials[i].material.Power = pData->m_materialTable[i].power;

		// Ȯ��� �ؽ�ó
		m_materials[i].pTex[0] = NULL;
		_splitpath( pData->m_materialTable[i].strMapDiffuse.c_str(), drive, dir, fname, ext ); str = fname; str += ext;
		D3DXCreateTextureFromFile( pDev, str.c_str(), &m_materials[i].pTex[0] );

		// ������ �ؽ�ó
		m_materials[i].pTex[1] = NULL;
		_splitpath( pData->m_materialTable[i].strMapBump.c_str(), drive, dir, fname, ext ); str = fname; str += ext;
		D3DXCreateTextureFromFile( pDev, str.c_str(), &m_materials[i].pTex[1] );
		
		// �ݻ�� �ؽ�ó
		m_materials[i].pTex[2] = NULL;
		_splitpath( pData->m_materialTable[i].strMapSpecular.c_str(), drive, dir, fname, ext ); str = fname; str += ext;
		D3DXCreateTextureFromFile( pDev, str.c_str(), &m_materials[i].pTex[2] );
		
		// �׿��� �߰����� �ؽ�ó
		m_materials[i].pTex[3] = NULL;
		_splitpath( pData->m_materialTable[i].strMapDisplace.c_str(), drive, dir, fname, ext ); str = fname; str += ext;
		D3DXCreateTextureFromFile( pDev, str.c_str(), &m_materials[i].pTex[3] );
	}

	// copy meshes
	list<ZCMesh*>::iterator	it;
	ZNode*					pNode;
	size = pData->m_meshList.size();
	for( i = 0, it = pData->m_meshList.begin() ; it != pData->m_meshList.end() ; i++, it++ )
	{
		// �θ� ���� ���� 0����带 �θ�� �Ѵ�.
		if( (*it)->m_nParentID == -1 ) 
			(*it)->m_nParentID = 0;

		// Bone�̳� Biped��� ZBone���� ����
		if( !( (*it)->m_strNodeType.compare( "BoneGeometry" ) ) || 
			!( (*it)->m_strNodeType.compare( "Biped_Object" ) ) || 
			!( (*it)->m_strNodeType.compare( "Bone" ) ) )
		{
			pNode = (ZNode*)(new ZBone( pDev, *it ));
		}
		else	// Editable_Mesh��� ZMesh�� ����
		if( !( (*it)->m_strNodeType.compare( "Editable_mesh" ) ) )
		{
			if( (*it)->m_isSkinned )	// Skin�� ������ ZSkinnedMesh�� ����
				pNode = (ZNode*)(new ZSkinnedMesh( pDev, *it ));
			else	// Skin�� ������ ZRigidMesh�� ����
				pNode = (ZNode*)(new ZRigidMesh( pDev, *it ));
		}
		else	// �̰͵� ���͵� �ƴϸ� �׳� ZNode�� ����
			pNode = new ZNode( pDev, *it );

		m_nodes.push_back( pNode );
	}
}

ZNodeMgr::~ZNodeMgr()
{
	stl_wipe_vector( m_materials );
	for( int i = 0 ; i < m_nodes.size() ; i++ ) S_DEL( m_nodes[i] );
	stl_wipe_vector( m_nodes );
}

int ZNodeMgr::Animate( float fFrame )
{
	int				i;
	int				id;
	D3DXMATRIXA16*	pTM;

	if( fFrame > m_info.fAnimationEnd ) fFrame = m_info.fAnimationEnd;
	if( fFrame < m_info.fAnimationStart ) fFrame = m_info.fAnimationStart;

	// ���� ����(bone)���� �ִϸ��̼� ����� ����� �д�
	for( i = 0 ; i < m_info.BoneTable.size(); i++ )
	{
		id =  m_nodes[m_info.BoneTable[i]]->GetParentID();
		pTM = m_nodes[id]->GetMatrixTM();
		m_nodes[m_info.BoneTable[i]]->Animate( fFrame, pTM );
	}

	// ���밡 �ƴ� �͵��� �ִϸ��̼� ����� �����
	for( i = 0 ; i < m_info.MeshTable.size() ; i++ )
	{
		id =  m_nodes[m_info.MeshTable[i]]->GetParentID();
		pTM = m_nodes[id]->GetMatrixTM();
		m_nodes[m_info.MeshTable[i]]->Animate( fFrame, pTM );
	}

	return 1;
}

int ZNodeMgr::Draw( int nNodeType )
{
	int				i;

	if( nNodeType == ZNode::NODE_MESH )
	{
		for( i = 0 ; i < m_info.MeshTable.size() ; i++ )
		{
			m_pDev->SetMaterial( &m_materials[m_nodes[m_info.MeshTable[i]]->GetMaterialID()].material );
			m_pDev->SetTexture( 0, m_materials[m_nodes[m_info.MeshTable[i]]->GetMaterialID()].pTex[0] ); 
			m_pDev->SetTransform( D3DTS_WORLD, &m_matTM );
			m_nodes[m_info.MeshTable[i]]->Draw();
		}
	}
	else
	if( nNodeType == ZNode::NODE_BONE )
	{
		for( i = 0 ; i < m_info.BoneTable.size() ; i++ )
		{
			m_pDev->SetMaterial( &m_materials[m_nodes[m_info.BoneTable[i]]->GetMaterialID()].material );
			m_pDev->SetTexture( 0, m_materials[m_nodes[m_info.BoneTable[i]]->GetMaterialID()].pTex[0] ); 
			m_pDev->SetTransform( D3DTS_WORLD, &m_matTM );
			m_nodes[m_info.BoneTable[i]]->Draw();
		}
	}
	else	// NODE_NODE
	{
		for( i = 0 ; i < m_nodes.size() ; i++ )
		{
			m_pDev->SetMaterial( &m_materials[m_nodes[i]->GetMaterialID()].material );
			m_pDev->SetTexture( 0, m_materials[m_nodes[i]->GetMaterialID()].pTex[0] ); 
			m_pDev->SetTransform( D3DTS_WORLD, &m_matTM );
			m_nodes[i]->Draw();
		}
	}

	return 1;
}

int ZNodeMgr::DrawBBox( int nNodeType )
{
	int				i;

	m_pDev->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );
	for( i = 0 ; i < m_nodes.size() ; i++ )
	{
		m_pDev->SetTransform( D3DTS_WORLD, &m_matTM );
		if( nNodeType == ZNode::NODE_NODE ) m_nodes[i]->DrawBBox();
		else if( nNodeType == ZNode::NODE_BONE ) { if( m_nodes[i]->GetNodeType() == ZNode::NODE_BONE ) m_nodes[i]->DrawBBox(); }
		else if( nNodeType == ZNode::NODE_MESH ) { if( m_nodes[i]->GetNodeType() == ZNode::NODE_MESH ) m_nodes[i]->DrawBBox(); }
	}
	m_pDev->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );

	return 1;
}

