#include "StdAfx.h"
#include "PRMdlXFile.h"
#include "PUtCommon.h"
#include "PUtCommonFPath.h"
#include "PRCommonFunc.h"
#include "PRXMeshHierachy.h"

const float		DEF_MOVETRANSITIONTIME	=	0.25f;

//-----------------------------------------------------------------------
void	CPRMdlXFile::InitMembers()
{
	m_pmatBone		=	NULL;
	m_pFirstMesh	=	NULL;
	m_pFrameRoot 	=	NULL;
	m_pAniCtrl		=	NULL;

	m_fSpeedAdjust			=	1.0f;	

	m_unCurTrack 		=	0;
	m_fCurTime  		=	0;
	m_unNumAniSets		=	0;
	m_unCurAniSet  		=	0;
	m_nMaxBones  		=	0;

	m_fSphereRadius			=	0;
	m_vecSphereCenter		=	D3DXVECTOR3( 0.0f, 0.0f, 0.0f );

	PUT_True( m_bAni );

	m_fAniStartTime 	=	0;
	PUT_False( m_bRepeatAni );
	PUT_False( m_bProcessAni	);	
	
	PRDXMatInit( &m_matWorld );
	m_vecScale				=	D3DXVECTOR3( 1.0f, 1.0f, 1.0f ) * 1.5f;
	m_vecPos				=	D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	m_quartOrientation		=	D3DXQUATERNION( 0.0f, 0.0f, 0.0f, 1.0f );

	m_fExtraTime 			=	0;

}//	InitMembers
//-------------------------------------------------------------------------------
void	CPRMdlXFile::ClearMembers()
{
	PUT_SAFE_RELEASE( m_pAniCtrl );

	if( GetRootFrame() )
	{
		CPRXMeshHierachy	memAllocator;
		D3DXFrameDestroy( GetRootFrame(), &memAllocator );		
		m_pFrameRoot 	=	NULL;
	}

	PUT_SAFE_DELETE_ARRAY( m_pmatBone );

	PUT_SAFE_DELETE( m_pXMeshHierachy );

}//	ClearMembers
//-------------------------------------------------------------------------------
bool	CPRMdlXFile::Init( PRLPD3DDEV9 pDev, char *pszXFile, D3DXVECTOR3 vPos, D3DXVECTOR3 vScale, bool bRepeatAni )
{
	PUT_IsInValid( Load( pDev, pszXFile ) )
	{
		PUT_ERROR;
		return false;
	}

	SetPos( vPos );
	SetScale( vScale );
	SetEnableRepeatAni( bRepeatAni );

	PUT_IsInValid( m_unNumAniSets )
	{
		SetAniSet(0);
	}else
		SetAniSet(1);

	return true;

}//	Init
//-------------------------------------------------------------------------------
bool	CPRMdlXFile::Load( PRLPD3DDEV9 pDev, const char *pszFName )
{
//	CPRXMeshHierachy	*pMemAlloc	=	new CPRXMeshHierachy;
	m_pXMeshHierachy	=	new CPRXMeshHierachy;

	std::string	szPathOnly;
	std::string	szFNameOnly;

	PUT_SplitPath( pszFName, &szPathOnly, &szFNameOnly );

	SetFName( (char*)szFNameOnly.c_str() );

//	pMemAlloc->SetPath( (char*)szPathOnly.c_str() );
	m_pXMeshHierachy->SetPath( (char*)szPathOnly.c_str() );

	HRESULT	hr	=	D3DXLoadMeshHierarchyFromX( pszFName,
												D3DXMESH_MANAGED,
												pDev,
												m_pXMeshHierachy, //pMemAlloc,
												NULL,
												&m_pFrameRoot,
												&m_pAniCtrl
												);

//	PUT_SAFE_DELETE( pMemAlloc );

	if( FAILED(hr) )
		return false;

	//	x���Ͽ� �ִ������� �ִٸ� �Ʈ�� �ִ��� �����Ѵ�.
	if( m_pAniCtrl )
		m_unNumAniSets	=	m_pAniCtrl->GetMaxNumAnimationSets();


	if( GetRootFrame() )
	{
		//	�� ����.
		SetupBoneMatrices( pDev, (sPRDXXFRAMEEx*)GetRootFrame(), NULL );

		//	�� ��Ʈ���� ����� �����.
		m_pmatBone	=	new D3DXMATRIX[ m_nMaxBones ];
		ZeroMemory( m_pmatBone, sizeof( D3DXMATRIX ) * m_nMaxBones );

		//	���� �𵨿� ���� ��豸�� ���.
		//	( CalculateInitialViewMatrix �Լ����� ī�޶��� ��ġ�� ��Ȯ�� ��µ� ���.)
		D3DXFrameCalculateBoundingSphere( GetRootFrame(), &m_vecSphereCenter, &m_fSphereRadius );

	}//	if( m_pFrameRoot )

	return true;	

}//	Load
//-------------------------------------------------------------------------------
D3DXVECTOR3	CPRMdlXFile::GetInitCameraPos() const
{
	D3DXVECTOR3	vecCamPos( 0.0f, m_vecSphereCenter.y, -( m_fSphereRadius * 3 ) );
	return vecCamPos;

}//	GetInitCameraPos
//-------------------------------------------------------------------------------
void	CPRMdlXFile::SetupBoneMatrices( PRLPD3DDEV9 pDev, sPRDXXFRAMEEx *pFrame, LPD3DXMATRIX pmatParent )
{
	//	���� Ȯ��� ����ü�� ĳ��Ʈ�Ѵ�.
	sPRDXXMESHCONTAINEREx	*pMesh	=	(sPRDXXMESHCONTAINEREx*)pFrame->pMeshContainer;

	//	�ش� �������� �޽��� ������ �ִٸ�....
	if( pMesh )
	{
		//	FrameMove�� �����Ҷ� ����� ù��° �޽����� ������ �ʿ䰡 �ִ�.
		PUT_IsInValid( m_pFirstMesh )
			m_pFirstMesh	=	pMesh;

		//	��Ų ������ �ִٸ� �� ����� �����Ѵ�.
		if( pMesh->pSkinInfo && pMesh->MeshData.pMesh )
		{
			//	���߿� �ؽ��ĸ� ���� �޽��� ���纻�� �����.
			PRDXVTXELE9	d3dDclr[ MAX_FVF_DECL_SIZE ]	=	{0,};
			PUT_IsFailed( pMesh->MeshData.pMesh->GetDeclaration( d3dDclr ) )
			{
				return;
			}

			pMesh->MeshData.pMesh->CloneMesh( D3DXMESH_MANAGED, d3dDclr, pDev, &pMesh->_pSkinMeshEx );

			//	���Ŀ� ����ϱ� ���� �������� ���
			//	( �� ��Ʈ���� ����� ����°� �󸶳� ū�� �˱�����.. )
			m_nMaxBones	=	max( m_nMaxBones, (int)pMesh->pSkinInfo->GetNumBones() );

			//	������ ���� ��ķ� ���ȴ�.
			for( UINT unCur = 0; unCur < pMesh->pSkinInfo->GetNumBones(); ++unCur )
			{
				//	���� ������ �ִ� �������� ã�´�.
				sPRDXXFRAMEEx	*pTmpFrame	=	(sPRDXXFRAMEEx*)D3DXFrameFind( GetRootFrame(), pMesh->pSkinInfo->GetBoneName( unCur ) );

				//	���� �����ϰ� ��ȯ����� ����Ű���� �Ѵ�.
				pMesh->_ppmatFrameCombinedPtrEx[ unCur ]	=	&pTmpFrame->_matCombinedTransformEx;
			}

		}//	if( pMesh->pSkinInfo && pMesh->MeshData.pMesh )

	}//	if( pMesh )


	//	�̿� ���������� �Ѿ��.
	if( pFrame->pFrameSibling )
		SetupBoneMatrices( pDev, (sPRDXXFRAMEEx*)pFrame->pFrameSibling, pmatParent );

	//	�ڽ� ���������� �Ѿ��.
	if( pFrame->pFrameFirstChild )
		SetupBoneMatrices( pDev, (sPRDXXFRAMEEx*)pFrame->pFrameFirstChild, &pFrame->_matCombinedTransformEx );

}//	SetupBoneMatrices
//-------------------------------------------------------------------------------
void	CPRMdlXFile::SetRot( D3DXVECTOR3 vecRot )
{
	D3DXQUATERNION	d3dQuat;
	D3DXQuaternionIdentity( &d3dQuat );
	m_vecRot	=	vecRot;
	D3DXQuaternionRotationYawPitchRoll( &d3dQuat, vecRot.y, vecRot.x, vecRot.z );

	m_quartOrientation	=	d3dQuat;

}//	SetRot
//-------------------------------------------------------------------------------
void	CPRMdlXFile::UpdateFrameMatrices( const LPD3DXFRAME pFrameBase, const D3DXMATRIX *pmatParent )
{
	sPRDXXFRAMEEx	*pCurFrame	=	(sPRDXXFRAMEEx*)pFrameBase;

	//	�θ� ����� �����Ѵٸ� ������ ��Ŀ� ���Ѵ�.
	if( pmatParent )
		D3DXMatrixMultiply( &pCurFrame->_matCombinedTransformEx, &pCurFrame->TransformationMatrix, pmatParent );
	else
		pCurFrame->_matCombinedTransformEx	=	pCurFrame->TransformationMatrix;


	//	��ȯ�Ǵ� �̿� �������� �ִٸ�
	if( pCurFrame->pFrameSibling )
		UpdateFrameMatrices( pCurFrame->pFrameSibling, pmatParent );


	//	��ȯ�Ǵ� �ڽ� �������� �ִٸ�
	if( pCurFrame->pFrameFirstChild )
		UpdateFrameMatrices( pCurFrame->pFrameFirstChild, &pCurFrame->_matCombinedTransformEx );

}//	UpdateFrameMatrices
//-------------------------------------------------------------------------------
HRESULT	CPRMdlXFile::OnRender( PRLPD3DDEV9 pDev, float fElapsedTime )
{	
	if( GetRootFrame() )
	{
		DrawFrame( pDev, GetRootFrame() );
		return S_OK;
	}

	return E_FAIL;

}//	OnRender
//-------------------------------------------------------------------------------
void	CPRMdlXFile::DrawFrame( PRLPD3DDEV9 pDev, LPD3DXFRAME pFrame ) const
{
	PRDXMESHCONTAINER	pMeshContainer	=	pFrame->pMeshContainer;

	while( pMeshContainer )
	{
		DrawMeshContainer( pDev, pMeshContainer, pFrame );
		pMeshContainer	=	pMeshContainer->pNextMeshContainer;
	}

	//	�̿� �����ӿ� ���� ��� ȣ��	
	if( pFrame->pFrameSibling )
		DrawFrame( pDev, pFrame->pFrameSibling );

	//	�ڽ� �����ӿ� ���� ��� ȣ��	
	if( pFrame->pFrameFirstChild )
		DrawFrame( pDev, pFrame->pFrameFirstChild );

}//	DrawFrame
//-------------------------------------------------------------------------------
void	CPRMdlXFile::DrawMeshContainer( PRLPD3DDEV9 pDev, PRDXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase ) const
{
	//	Ȯ�� ������ Ÿ������ ĳ����
	sPRDXXFRAMEEx	*pFrame	=	( sPRDXXFRAMEEx* )pFrameBase;

	//	Ȯ�� �޽� �����̳ʷ� ĳ����
	sPRDXXMESHCONTAINEREx *pMeshContainer	=	(sPRDXXMESHCONTAINEREx*)pMeshContainerBase;

	//	���� ��Ʈ���� ����
	devSetTrsformWorld( pDev, &pFrame->_matCombinedTransformEx );

//	devSetTSSCOLOROP( pDev, 0, D3DTOP_MODULATE );
//	devSetTSSCOLOROP( pDev, 0, D3DTSS_COLORARG1 );
//	devSetTSSCOLORARG1( pDev, 0, D3DTA_TEXTURE );

	//	�� ������ ��ȯ�ϸ� ������
	for( UINT unCur = 0; unCur < pMeshContainer->NumMaterials; ++unCur )
	{
		devSetMtrl( pDev, &pMeshContainer->_pMtrlsEx[ unCur ] );
		devSetTxtr( pDev, 0, pMeshContainer->_ppTexturesEx[ unCur ] );

		PRDXXMESH	pDrawMesh	=	( pMeshContainer->pSkinInfo ) ? pMeshContainer->_pSkinMeshEx : pMeshContainer->MeshData.pMesh;

		pDrawMesh->DrawSubset( unCur );
	}

	//	���⼭ ���͸����� �缳�����ش�.
	//	�� �׷��� Ȯ���� �𸣹Ƿ� �ʿ��ϴٰ� �����ɶ� 
	//	��������. 
	//	JACKIENOTE_12/03/06
	//	devSetMtrl( )

}//	DrawMeshContainer
//-------------------------------------------------------------------------------
void	CPRMdlXFile::SetAniSet( UINT unIdx )
{
	PUT_IsSame( unIdx, m_unCurAniSet )	
		return;
	
	if( unIdx >= m_unCurAniSet )
		unIdx = 0;

	//	���� �ִϸ��̼��� �����Ѵ�.
	m_unCurAniSet	=	unIdx;

	//	��Ʈ�ѷ��� ���� �ִϸ��̼� ���� ��´�.
	LPD3DXANIMATIONSET	pSet;
	m_pAniCtrl->GetAnimationSet( m_unCurAniSet, &pSet );

	//	Ʈ�� ����
	DWORD	dwNewTrack	=	( m_unCurTrack == 0 ? 1 : 0 );

	//	Ʈ���� �Ҵ�.
	m_pAniCtrl->SetTrackAnimationSet( dwNewTrack, pSet );
	pSet->Release();

	m_pAniCtrl->UnkeyAllTrackEvents( m_unCurTrack );
	m_pAniCtrl->UnkeyAllTrackEvents( dwNewTrack );

	m_pAniCtrl->KeyTrackEnable( m_unCurTrack, FALSE, m_unCurTrack + DEF_MOVETRANSITIONTIME );
	m_pAniCtrl->KeyTrackSpeed( m_unCurTrack, 0.0f, m_unCurTrack, DEF_MOVETRANSITIONTIME, D3DXTRANSITION_LINEAR );
	m_pAniCtrl->KeyTrackWeight( m_unCurTrack, 0.0f, m_fCurTime, DEF_MOVETRANSITIONTIME, D3DXTRANSITION_LINEAR );

	//	�� Ʈ�� Ȱ��ȭ.
	m_pAniCtrl->SetTrackEnable( dwNewTrack, TRUE );
	
	//	�� Ʈ���� ����ӵ��� �����ϴ� �̺�Ʈ �߰�.
	m_pAniCtrl->KeyTrackSpeed( dwNewTrack, 1.0f, m_fCurTime, DEF_MOVETRANSITIONTIME, D3DXTRANSITION_LINEAR );
	m_pAniCtrl->KeyTrackWeight( m_unCurTrack, 1.0f, m_fCurTime, DEF_MOVETRANSITIONTIME, D3DXTRANSITION_LINEAR );
	
	//	���� Ʈ�� ����.
	m_unCurTrack	=	dwNewTrack;


}//	SetAniSet
//-------------------------------------------------------------------------------
void	CPRMdlXFile::SetAniNext()
{
	UINT	unNewAniSet	=	m_unCurAniSet + 1;
	if( unNewAniSet >= m_unNumAniSets )
		unNewAniSet	=	0;

	SetAniSet( unNewAniSet );

}//	SetAniNext
//-------------------------------------------------------------------------------
std::string	CPRMdlXFile::GetAniSetName( UINT unIdx )
{
	if( unIdx >= m_unNumAniSets )
		return NULL;

	LPD3DXANIMATIONSET	pSet;
	m_pAniCtrl->GetAnimationSet( m_unCurAniSet, &pSet );

	std::string	strName( pSet->GetName() );

	pSet->Release();

	return strName;

}//	GetAniSetName
//-------------------------------------------------------------------------------
void	CPRMdlXFile::SetAniSlower()
{
	m_fSpeedAdjust	+=	0.1f;

}//	SetAniSlower
//-------------------------------------------------------------------------------
void	CPRMdlXFile::SetAniFaster()
{
	if( m_fSpeedAdjust > 0.0f )
		m_fSpeedAdjust -= 0.1f;

}//	SetAniFaster
//-------------------------------------------------------------------------------
void	CPRMdlXFile::SetAniStart()
{
	PUT_IsInValid( m_bProcessAni )
	{
		PUT_True( m_bProcessAni );
		m_fAniStartTime 	=	0;
		LPD3DXANIMATIONSET	pAS	=	NULL;
		m_pAniCtrl->GetAnimationSet( m_unCurAniSet, &pAS );
		m_pAniCtrl->SetTrackAnimationSet( m_unCurTrack, pAS );
		PUT_SAFE_RELEASE( pAS );

		m_pAniCtrl->SetTrackEnable( m_unCurTrack, TRUE );
		m_pAniCtrl->SetTrackWeight( m_unCurTrack, 1.0f );
		m_pAniCtrl->SetTrackSpeed( m_unCurTrack, 1.0f );

		m_pAniCtrl->SetTrackPosition( m_unCurTrack, 0.0f );

	}//	PUT_IsInValid( m_bProcessAni )

}//	SetAniStart
//-------------------------------------------------------------------------------
bool	CPRMdlXFile::OnUpdate( float fElapsed )
{
	D3DXMATRIX	matScale;
	D3DXMATRIX	matPos;
	D3DXMATRIX	matRot;
	D3DXMATRIX	*pmatQuaternion	=	NULL;

	PRDXMatInit( &matScale );
	PRDXMatInit( &matPos );
	PRDXMatInit( &matRot );
	pmatQuaternion	=	D3DXMatrixRotationQuaternion( &matRot, &m_quartOrientation );

	PRDXMatInit( &m_matWorld );
	D3DXMatrixTranslation( &matPos, m_vecPos.x, m_vecPos.y, m_vecPos.z );
	D3DXMatrixScaling( &matScale, m_vecScale.x, m_vecScale.y, m_vecScale.z );
	D3DXMatrixMultiply( &matPos, &matScale, &matPos );
	D3DXMatrixMultiply( &m_matWorld, &matScale, &matPos );
	D3DXMatrixMultiply( &m_matWorld, pmatQuaternion, &m_matWorld );	
	
	PUT_IsInValid( m_bAni )	//	�ִ� ����.
	{
		fElapsed	=	0.0f;
	}else
	{
		//	�ִ� �ӵ� ����.
		fElapsed	/=	m_fSpeedAdjust;

	}//	PUT_IsInValid( m_bAni )


	//	�ð��� �����Ű�� ��Ʈ�ѷ��� ����.
	if( m_pAniCtrl )
	{
		PUT_IsInValid( m_bRepeatAni )
		{
			m_fAniStartTime	=	m_fAniStartTime + fElapsed;

			LPD3DXANIMATIONSET	pAniSet = NULL;
			HRESULT	hr	=	m_pAniCtrl->GetAnimationSet( m_unCurAniSet, &pAniSet );

			if( m_bProcessAni )
			{
				if( pAniSet )
				{
					double	dPeriod	=	pAniSet->GetPeriod();

					if( m_fAniStartTime <= dPeriod )
					{
						m_pAniCtrl->AdvanceTime( fElapsed, NULL );
						m_fExtraTime	=	dPeriod - m_fAniStartTime;

					}//	if( m_fAniStartTime <= dPeriod )
					else
					{
						PUT_False( m_bProcessAni );
						m_pAniCtrl->AdvanceTime( m_fExtraTime, NULL );
						m_pAniCtrl->ResetTime();
						m_fAniStartTime 	=	0;
						m_fExtraTime  		=	0;

					}//	~if( m_fAniStartTime <= dPeriod )

				}//	if( pAniSet )

			}//	if( m_bProcessAni )
			else
			{
				m_pAniCtrl->SetTrackPosition( m_unCurAniSet, 0.0f );

			}//	~if( m_bProcessAni )

		}//	PUT_IsInValid( m_bRepeatAni )
		else
		{
			m_pAniCtrl->AdvanceTime( fElapsed, NULL );
			PUT_False( m_bProcessAni );
			
		}//	~PUT_IsInValid( m_bRepeatAni )

	}//	if( m_pAniCtrl )

	
	m_fCurTime	+=	fElapsed;

	
	//	�������� �� ��� ����.
	UpdateFrameMatrices( GetRootFrame(), &m_matWorld );

	
	//	���� ��Ų �޽��� ������ �ִٸ� ���ؽ� ����.
	sPRDXXMESHCONTAINEREx	*pMesh	=	m_pFirstMesh;
	if( ( pMesh && pMesh->pSkinInfo ) )
	{
		UINT	unNumBones	=	pMesh->pSkinInfo->GetNumBones();

		//	�� �����̽����� ĳ���� �����̽��� ������ ���� ��ȯ�ϴ� �� ����� �����.
		//	( exFrameCombinedMatrixPointer�� ���Ͽ�..)
		//	�׸��� pexMatBoneOffset�� �� �ɼ��� �̿��Ͽ� �� ������ �޽��� ���Ѵ�.
		for( UINT unCur = 0; unCur < unNumBones; ++unCur )
			D3DXMatrixMultiply( &m_pmatBone[unCur],
								&pMesh->_pmatBoneOffsetsEx[unCur],
								pMesh->_ppmatFrameCombinedPtrEx[unCur] );

		//	���ο� �� ��Ŀ� ����� �� ���ؽ� ��ġ�� ������ �ʿ䰡 �ִ�.
		//	���ؽ����۸� ����� UpdateSkinnedMesh�� ȣ�������ν� �̷�����.
		//	UpdateSkinnedMesh�� ���� ���ؽ� �����͸� ���� ������( pMesh->MeshData.pMesh �ȿ� �ִ�..) �� ����� �����Ͽ�
		//	��Ų �޽��� �� ���ؽ����� ä���.(pMesh->pexSkinMesh).

		//	UpdateSkinnedMesh�� ����Ʈ���� ��Ű�׹���� ����Ѵ�.
		//	����Ʈ���� ��Ű�׹���� ��Ű�� ������ �����ϴµ� ���� ��������
		//	��ټ��� �׷��� ����̽����� �ٷ�� ���� ���� ����̴�.
		//	��Ű���� �ϴµ� �ϵ��� ����ϴ� �ٸ� ����� �����Ѵ�.
		//	�ڼ��Ѱ�  dx������ Skinned mesh�� �����Ұ�.

		void	*pSrc	=	NULL;
		pMesh->MeshData.pMesh->LockVertexBuffer( D3DLOCK_READONLY, (void**)&pSrc );

		void	*pDest	=	NULL;
		pMesh->_pSkinMeshEx->LockVertexBuffer( 0, (void**)&pDest );

		//	��Ų �޽�.
		pMesh->pSkinInfo->UpdateSkinnedMesh( m_pmatBone, NULL, pSrc, pDest );

		//	�޽� ���ؽ� ���� ��� ����.
		pMesh->_pSkinMeshEx->UnlockVertexBuffer();
		pMesh->MeshData.pMesh->UnlockVertexBuffer();

	}//	if( ( pMesh && pMesh->pSkinInfo ) )

	return true;

}//	OnUpdate
//-------------------------------------------------------------------------------