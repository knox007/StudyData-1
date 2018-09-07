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

	//	x파일에 애니정보가 있다면 몇세트가 있는지 저장한다.
	if( m_pAniCtrl )
		m_unNumAniSets	=	m_pAniCtrl->GetMaxNumAnimationSets();


	if( GetRootFrame() )
	{
		//	본 설정.
		SetupBoneMatrices( pDev, (sPRDXXFRAMEEx*)GetRootFrame(), NULL );

		//	본 메트릭스 행렬을 만든다.
		m_pmatBone	=	new D3DXMATRIX[ m_nMaxBones ];
		ZeroMemory( m_pmatBone, sizeof( D3DXMATRIX ) * m_nMaxBones );

		//	현재 모델에 대한 경계구를 계산.
		//	( CalculateInitialViewMatrix 함수에서 카메라의 위치를 정확히 잡는데 사용.)
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
	//	먼저 확장된 구조체로 캐스트한다.
	sPRDXXMESHCONTAINEREx	*pMesh	=	(sPRDXXMESHCONTAINEREx*)pFrame->pMeshContainer;

	//	해당 프레임이 메쉬를 가지고 있다면....
	if( pMesh )
	{
		//	FrameMove로 갱신할때 어떤것이 첫번째 메쉬인지 저장할 필요가 있다.
		PUT_IsInValid( m_pFirstMesh )
			m_pFirstMesh	=	pMesh;

		//	스킨 정보가 있다면 본 행렬을 설정한다.
		if( pMesh->pSkinInfo && pMesh->MeshData.pMesh )
		{
			//	나중에 텍스쳐를 입힐 메쉬의 복사본을 만든다.
			PRDXVTXELE9	d3dDclr[ MAX_FVF_DECL_SIZE ]	=	{0,};
			PUT_IsFailed( pMesh->MeshData.pMesh->GetDeclaration( d3dDclr ) )
			{
				return;
			}

			pMesh->MeshData.pMesh->CloneMesh( D3DXMESH_MANAGED, d3dDclr, pDev, &pMesh->_pSkinMeshEx );

			//	추후에 사용하기 위해 본갯수를 계산
			//	( 본 매트릭스 행렬을 만드는게 얼마나 큰지 알기위해.. )
			m_nMaxBones	=	max( m_nMaxBones, (int)pMesh->pSkinInfo->GetNumBones() );

			//	각각의 본은 행렬로 계산된다.
			for( UINT unCur = 0; unCur < pMesh->pSkinInfo->GetNumBones(); ++unCur )
			{
				//	본을 가지고 있는 프레임을 찾는다.
				sPRDXXFRAMEEx	*pTmpFrame	=	(sPRDXXFRAMEEx*)D3DXFrameFind( GetRootFrame(), pMesh->pSkinInfo->GetBoneName( unCur ) );

				//	본을 설정하고 변환행렬을 가리키도록 한다.
				pMesh->_ppmatFrameCombinedPtrEx[ unCur ]	=	&pTmpFrame->_matCombinedTransformEx;
			}

		}//	if( pMesh->pSkinInfo && pMesh->MeshData.pMesh )

	}//	if( pMesh )


	//	이웃 프레임으로 넘어간다.
	if( pFrame->pFrameSibling )
		SetupBoneMatrices( pDev, (sPRDXXFRAMEEx*)pFrame->pFrameSibling, pmatParent );

	//	자식 프레임으로 넘어간다.
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

	//	부모 행렬이 존재한다면 프레임 행렬에 곱한다.
	if( pmatParent )
		D3DXMatrixMultiply( &pCurFrame->_matCombinedTransformEx, &pCurFrame->TransformationMatrix, pmatParent );
	else
		pCurFrame->_matCombinedTransformEx	=	pCurFrame->TransformationMatrix;


	//	순환되는 이웃 프레임이 있다면
	if( pCurFrame->pFrameSibling )
		UpdateFrameMatrices( pCurFrame->pFrameSibling, pmatParent );


	//	순환되는 자식 프레임이 있다면
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

	//	이웃 프레임에 대한 재귀 호출	
	if( pFrame->pFrameSibling )
		DrawFrame( pDev, pFrame->pFrameSibling );

	//	자식 프레임에 대한 재귀 호출	
	if( pFrame->pFrameFirstChild )
		DrawFrame( pDev, pFrame->pFrameFirstChild );

}//	DrawFrame
//-------------------------------------------------------------------------------
void	CPRMdlXFile::DrawMeshContainer( PRLPD3DDEV9 pDev, PRDXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase ) const
{
	//	확장 프레임 타입으로 캐스팅
	sPRDXXFRAMEEx	*pFrame	=	( sPRDXXFRAMEEx* )pFrameBase;

	//	확장 메쉬 컨테이너로 캐스팅
	sPRDXXMESHCONTAINEREx *pMeshContainer	=	(sPRDXXMESHCONTAINEREx*)pMeshContainerBase;

	//	월드 매트릭스 설정
	devSetTrsformWorld( pDev, &pFrame->_matCombinedTransformEx );

//	devSetTSSCOLOROP( pDev, 0, D3DTOP_MODULATE );
//	devSetTSSCOLOROP( pDev, 0, D3DTSS_COLORARG1 );
//	devSetTSSCOLORARG1( pDev, 0, D3DTA_TEXTURE );

	//	각 재질을 순환하며 랜더링
	for( UINT unCur = 0; unCur < pMeshContainer->NumMaterials; ++unCur )
	{
		devSetMtrl( pDev, &pMeshContainer->_pMtrlsEx[ unCur ] );
		devSetTxtr( pDev, 0, pMeshContainer->_ppTexturesEx[ unCur ] );

		PRDXXMESH	pDrawMesh	=	( pMeshContainer->pSkinInfo ) ? pMeshContainer->_pSkinMeshEx : pMeshContainer->MeshData.pMesh;

		pDrawMesh->DrawSubset( unCur );
	}

	//	여기서 매터리얼을 재설정해준다.
	//	왜 그런지 확실히 모르므로 필요하다고 생각될때 
	//	구현하자. 
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

	//	현재 애니매이션을 저장한다.
	m_unCurAniSet	=	unIdx;

	//	컨트롤러로 부터 애니매이션 셋을 얻는다.
	LPD3DXANIMATIONSET	pSet;
	m_pAniCtrl->GetAnimationSet( m_unCurAniSet, &pSet );

	//	트랙 교차
	DWORD	dwNewTrack	=	( m_unCurTrack == 0 ? 1 : 0 );

	//	트랙에 할당.
	m_pAniCtrl->SetTrackAnimationSet( dwNewTrack, pSet );
	pSet->Release();

	m_pAniCtrl->UnkeyAllTrackEvents( m_unCurTrack );
	m_pAniCtrl->UnkeyAllTrackEvents( dwNewTrack );

	m_pAniCtrl->KeyTrackEnable( m_unCurTrack, FALSE, m_unCurTrack + DEF_MOVETRANSITIONTIME );
	m_pAniCtrl->KeyTrackSpeed( m_unCurTrack, 0.0f, m_unCurTrack, DEF_MOVETRANSITIONTIME, D3DXTRANSITION_LINEAR );
	m_pAniCtrl->KeyTrackWeight( m_unCurTrack, 0.0f, m_fCurTime, DEF_MOVETRANSITIONTIME, D3DXTRANSITION_LINEAR );

	//	새 트랙 활성화.
	m_pAniCtrl->SetTrackEnable( dwNewTrack, TRUE );
	
	//	새 트랙의 진행속도를 설정하는 이벤트 추가.
	m_pAniCtrl->KeyTrackSpeed( dwNewTrack, 1.0f, m_fCurTime, DEF_MOVETRANSITIONTIME, D3DXTRANSITION_LINEAR );
	m_pAniCtrl->KeyTrackWeight( m_unCurTrack, 1.0f, m_fCurTime, DEF_MOVETRANSITIONTIME, D3DXTRANSITION_LINEAR );
	
	//	현재 트랙 저장.
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
	
	PUT_IsInValid( m_bAni )	//	애니 여부.
	{
		fElapsed	=	0.0f;
	}else
	{
		//	애니 속도 조절.
		fElapsed	/=	m_fSpeedAdjust;

	}//	PUT_IsInValid( m_bAni )


	//	시간을 진행시키고 컨트롤러에 설정.
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

	
	//	계층에서 모델 행렬 갱신.
	UpdateFrameMatrices( GetRootFrame(), &m_matWorld );

	
	//	모델이 스킨 메쉬를 가지고 있다면 버텍스 갱신.
	sPRDXXMESHCONTAINEREx	*pMesh	=	m_pFirstMesh;
	if( ( pMesh && pMesh->pSkinInfo ) )
	{
		UINT	unNumBones	=	pMesh->pSkinInfo->GetNumBones();

		//	본 스페이스에서 캐릭터 스페이스로 각각의 본을 변환하는 본 행렬을 만든다.
		//	( exFrameCombinedMatrixPointer를 통하여..)
		//	그리고 pexMatBoneOffset의 본 옵셋을 이용하여 본 주위를 메쉬로 감싼다.
		for( UINT unCur = 0; unCur < unNumBones; ++unCur )
			D3DXMatrixMultiply( &m_pmatBone[unCur],
								&pMesh->_pmatBoneOffsetsEx[unCur],
								pMesh->_ppmatFrameCombinedPtrEx[unCur] );

		//	새로운 본 행렬에 기반을 둔 버텍스 위치를 수정할 필요가 있다.
		//	버텍스버퍼를 잠근후 UpdateSkinnedMesh를 호출함으로써 이뤄진다.
		//	UpdateSkinnedMesh는 원래 버텍스 데이터를 갖고 있으며( pMesh->MeshData.pMesh 안에 있는..) 그 행렬을 적용하여
		//	스킨 메쉬에 새 버텍스들을 채운다.(pMesh->pexSkinMesh).

		//	UpdateSkinnedMesh은 소프트웨어 스키닝방법을 사용한다.
		//	소프트웨어 스키닝방법은 스키닝 정보를 수반하는데 가장 느리지만
		//	대다수의 그래픽 디바이스에서 다루기 가장 쉬운 방법이다.
		//	스키닝을 하는데 하드웨어를 사용하는 다른 방법도 존재한다.
		//	자세한건  dx샘플의 Skinned mesh를 참고할것.

		void	*pSrc	=	NULL;
		pMesh->MeshData.pMesh->LockVertexBuffer( D3DLOCK_READONLY, (void**)&pSrc );

		void	*pDest	=	NULL;
		pMesh->_pSkinMeshEx->LockVertexBuffer( 0, (void**)&pDest );

		//	스킨 메쉬.
		pMesh->pSkinInfo->UpdateSkinnedMesh( m_pmatBone, NULL, pSrc, pDest );

		//	메쉬 버텍스 버퍼 잠금 해제.
		pMesh->_pSkinMeshEx->UnlockVertexBuffer();
		pMesh->MeshData.pMesh->UnlockVertexBuffer();

	}//	if( ( pMesh && pMesh->pSkinInfo ) )

	return true;

}//	OnUpdate
//-------------------------------------------------------------------------------