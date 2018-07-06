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
		// ������ Ȯ�걤 �Ӽ� ����
		D3DCOLORVALUE diffuse = { pData->m_materialTable[i].diffuse.r, pData->m_materialTable[i].diffuse.g, pData->m_materialTable[i].diffuse.b, 0 };
		m_materials[i].material.Diffuse = diffuse;

		// ������ ȯ�汤 �Ӽ� ����
		D3DCOLORVALUE ambient = { pData->m_materialTable[i].ambient.r, pData->m_materialTable[i].ambient.g, pData->m_materialTable[i].ambient.b, 0 };
		m_materials[i].material.Ambient = ambient;
		
		// ������ �ݻ籤 �Ӽ� ����
		D3DCOLORVALUE specular = { pData->m_materialTable[i].specular.r, pData->m_materialTable[i].specular.g, pData->m_materialTable[i].specular.b, 0 };
		m_materials[i].material.Specular = specular;
		
		// ������ �߻걤 �Ӽ� ����
		D3DCOLORVALUE emissive = { pData->m_materialTable[i].emissive.r, pData->m_materialTable[i].emissive.g, pData->m_materialTable[i].emissive.b, 0 };
		m_materials[i].material.Emissive = emissive;

		// �ݻ籤�� �������
		m_materials[i].material.Power = pData->m_materialTable[i].power;

		// ������ ��
		m_materials[i].opacity = pData->m_materialTable[i].opacity;

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
//	m_nodes.resize( size );
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

	for( i = 0 ; i < m_nodes.size() ; i++ )
	{
		id =  m_nodes[i]->GetParentID();
		pTM = m_nodes[id]->GetMatrixTM();
		m_nodes[i]->Animate( fFrame, pTM );
	}

	return 1;
}

int ZNodeMgr::Draw()
{
	int				i;

	for( i = 0 ; i < m_nodes.size() ; i++ )
	{

		m_pDev->SetMaterial( &m_materials[m_nodes[i]->GetMaterialID()].material );
		m_pDev->SetTexture( 0, m_materials[m_nodes[i]->GetMaterialID()].pTex[0] ); 

		m_pDev->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );	// 0�� �ؽ�ó ���������� Ȯ�� ����
		m_pDev->SetSamplerState( 1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );	// 0�� �ؽ�ó ���������� Ȯ�� ����
		m_pDev->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP );
		m_pDev->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP );
		m_pDev->SetTextureStageState( 0, D3DTSS_TEXCOORDINDEX, 0 );		// 0�� �ؽ�ó : 0�� �ؽ�ó �ε��� ���
		m_pDev->SetTextureStageState( 1, D3DTSS_TEXCOORDINDEX, 0 );		// 1�� �ؽ�ó : 0�� �ؽ�ó �ε��� ���

		m_pDev->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );		// MODULATE�� ���´�.
		m_pDev->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );		// �ؽ�ó
		m_pDev->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );		// ������
		m_pDev->SetTextureStageState( 1, D3DTSS_COLOROP,   D3DTOP_DISABLE );

		m_pDev->SetTransform( D3DTS_WORLD, &m_matTM );
		m_nodes[i]->Draw();
	}

	return 1;
}
