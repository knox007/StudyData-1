#include "StdAfx.h"
#include "PRXMeshHierachy.h"
#include "PUtCommon.h"
#include "PUtCommonFPath.h"
#include "PRCommonFunc.h"
#include "PRXFileCommon.h"
#include "PUtCommonStr.h"
#include "PreDef_Render.h"
#include "PUtCommonStr.h"
#include "PUTCommonVerIntegrate.h"

HRESULT	AllocateName( const char *pszName, char **ppNewName )
{
	UINT	unLength	=	0;

	if( pszName )
	{
		unLength	=	(UINT)strlen( pszName ) + 1;
		*ppNewName	=	new char[unLength];
		
		PUT_IsInValid( *ppNewName )
		{
			return E_OUTOFMEMORY;
		}

		memcpy( *ppNewName, pszName, unLength * sizeof( char ) );

	}//	if( pszName )
	else
	{
		*ppNewName	=	NULL;


	}//	~if( pszName )

	return S_OK;

}//	AllocateName
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
void	CPRXMeshHierachy::InitMembers()
{
	PUT_ZERO_MEMORY( m_szPath );

}//	InitMembers
//-------------------------------------------------------------------------
HRESULT	CPRXMeshHierachy::CreateFrame( const char *pszName, LPD3DXFRAME *ppretNewFrame )
{
	HRESULT	hr	=	S_OK;

	*ppretNewFrame	=	0;

	sPRDXXFRAMEEx	*pNewFrame	=	new sPRDXXFRAMEEx;
	PUT_ZERO_MEMORY_PTR( pNewFrame );

	PRDXMatInit( &pNewFrame->TransformationMatrix );
	PRDXMatInit( &pNewFrame->_matCombinedTransformEx );

	pNewFrame->pMeshContainer	=	0;
	pNewFrame->pFrameSibling	=	0;
	pNewFrame->pFrameFirstChild	=	0;

	*ppretNewFrame	=	pNewFrame;

	hr	=	AllocateName( pszName, &pNewFrame->Name );

	PUT_IsFailed( hr )
	{
		PUT_SAFE_DELETE( pNewFrame );
	}

	return hr;

}//	CreateFrame
//-------------------------------------------------------------------------
HRESULT CPRXMeshHierachy::CreateMeshContainer(	const char *pszName, 
												const D3DXMESHDATA *pMeshData,
												const D3DXMATERIAL	*pMtrlEx, 
												const D3DXEFFECTINSTANCE *pEffectInstances,
												DWORD dwNumMaterials, 
												const DWORD *pdwAdjacency, 
												LPD3DXSKININFO pSkinInfo,
												PRDXMESHCONTAINER *ppResNewMeshContainer )
{
	HRESULT	hr	=	S_OK;

	sPRDXXMESHCONTAINEREx	*pNewMeshContainer	=	new sPRDXXMESHCONTAINEREx;
	PUT_ZERO_MEMORY_PTR( pNewMeshContainer );

	*ppResNewMeshContainer	=	0;

	hr	=	AllocateName( pszName, &pNewMeshContainer->Name );

	PUT_IsFailed( hr )
	{
		PUT_SAFE_DELETE( ppResNewMeshContainer );
		return hr;
	}

	PUT_IsDiffer( pMeshData->Type, D3DXMESHTYPE_MESH )
	{
		DestroyMeshContainer( pNewMeshContainer );
		return E_FAIL;
	}

	pNewMeshContainer->MeshData.Type	=	D3DXMESHTYPE_MESH;

	//	인접 데이터 - 삼각형 인접에 관한 정보를 갖는다
	DWORD	dwFaces	=	pMeshData->pMesh->GetNumFaces();
	pNewMeshContainer->pAdjacency	=	new DWORD[ dwFaces * 3 ];
	memcpy( pNewMeshContainer->pAdjacency,
			pdwAdjacency,
			sizeof(DWORD) * dwFaces * 3 );

	
	//	DX의 디바이스정보를 얻는다, 
	//	운좋게도 메쉬자체가 그 정보를 가지고 있다
	//	(주의: 사용하고 나면 릴리즈해줄것)
	PRLPD3DDEV9	pd3dDevice	=	0;
	pMeshData->pMesh->GetDevice( &pd3dDevice );

	//	복사하기보단 포인터를 할당하고 ref를 추가하자.
	pNewMeshContainer->MeshData.pMesh	=	pMeshData->pMesh;
	pNewMeshContainer->MeshData.pMesh->AddRef();

	//	재질과 텍스쳐 정보를 만든다. 
	//	(주의: 최소 한개 이상의 정보는 있어야한다.)
	pNewMeshContainer->NumMaterials		=	max( dwNumMaterials, 1 );
	pNewMeshContainer->_pMtrlsEx		=	new PRDMTRL9[ pNewMeshContainer->NumMaterials ];
	pNewMeshContainer->_ppTexturesEx	=	new PRDXTXTRBUFF9[ pNewMeshContainer->NumMaterials ];
	m_ppTexturesEx	=	pNewMeshContainer->_ppTexturesEx;
	m_pMaterial		=	pNewMeshContainer->_pMtrlsEx;
	m_dwMtrlsSize	=	dwNumMaterials;

	ZeroMemory( pNewMeshContainer->_ppTexturesEx,
				sizeof( PRDXTXTRBUFF9 ) * pNewMeshContainer->NumMaterials );

	if( dwNumMaterials > 0 )
	{
		//	모든 텍스쳐를 로딩해서 재질에 복사한다.
		for( DWORD dwCur = 0; dwCur < dwNumMaterials; ++dwCur )
		{
			pNewMeshContainer->_ppTexturesEx[ dwCur ]	=	0;
			pNewMeshContainer->_pMtrlsEx[dwCur]			=	pMtrlEx[ dwCur ].MatD3D;
			
			if( pMtrlEx[dwCur].pTextureFilename )
			{
				char	szTexturePath[MAX_PATH]	=	{0,};
#ifndef _ENGCLI_VS2003_VS2008_
				strcpy_s( szTexturePath, pMtrlEx[dwCur].pTextureFilename );
#else
				PUT_Strcpy( szTexturePath, pMtrlEx[dwCur].pTextureFilename );
#endif

				char	szTmpPath[MAX_PATH]		=	{0,};
#ifndef _ENGCLI_VS2003_VS2008_
				sprintf_s( szTmpPath, sizeof( szTmpPath ), "%s%s", m_szPath, szTexturePath );
#else
				PUT_Sprintf( szTmpPath, "%s%s", m_szPath, szTexturePath );
#endif

				PUT_IsInValid( PUT_IsFilePathExist( szTmpPath ) )
				{
					return hr;
				}

				hr	=	D3DXCreateTextureFromFile(	pd3dDevice,
													szTmpPath,
													&pNewMeshContainer->_ppTexturesEx[dwCur] );

				
				PUT_IsFailed( hr )
				{
					return hr;
				}

			}//	if( pMtrlEx[dwCur].pTextureFilename )

		}//	for( DWORD dwCur = 0; dwCur < dwNumMaterials; ++dwCur )

	}//	if( dwNumMaterials > 0 )
	else
	{
		PUT_ZERO_MEMORY_PTR( &pNewMeshContainer->_pMtrlsEx[0] );

		pNewMeshContainer->_pMtrlsEx[0].Diffuse.r	=	0.5f;
		pNewMeshContainer->_pMtrlsEx[0].Diffuse.g	=	0.5f;
		pNewMeshContainer->_pMtrlsEx[0].Diffuse.b	=	0.5f;
		pNewMeshContainer->_pMtrlsEx[0].Specular	=	pNewMeshContainer->_pMtrlsEx[0].Diffuse;
		pNewMeshContainer->_ppTexturesEx[0]			=	0;

	}//	~if( dwNumMaterials > 0 )


	//	메쉬와 연관된 스킨 데이터가 있다면 복사한다.
	if( pSkinInfo )
	{
		pNewMeshContainer->pSkinInfo	=	pSkinInfo;

		pSkinInfo->AddRef();

		UINT	unNumBones	=	pSkinInfo->GetNumBones();
		pNewMeshContainer->_pmatBoneOffsetsEx		=	new D3DXMATRIX[ unNumBones ];

		//	본과 프레임 행렬에대한 배열을 만든다.
		pNewMeshContainer->_ppmatFrameCombinedPtrEx	=	new D3DXMATRIX*[ unNumBones ];

		//	나중에 구할 필요가 없도록 각각의 본행렬옵셋을 구한다.
		for( UINT unCur = 0; unCur < unNumBones; ++unCur )
			pNewMeshContainer->_pmatBoneOffsetsEx[unCur]	=	*(pNewMeshContainer->pSkinInfo->GetBoneOffsetMatrix( unCur ) );

		//	주의:	마소 샘플에선 GenerateSkinnedMesh함수가 여기서 호출되어 
		//			최적의 하드웨어 가속을 위한 스킨 메쉬데이터를 준비하도록 한다.
		//			주석들에서 언급했듯이 하드웨어 스키닝이 아닌 소프트웨어 방식으로 한다.
		//			나중에 하드웨어방식으로 함 해보자!!ㅋㅋ

	}//	if( pSkinInfo )
	else
	{
		//	스킨 정보가 없다면 모든 포인터는 널이다.
		pNewMeshContainer->pSkinInfo				=	0;
		pNewMeshContainer->_pmatBoneOffsetsEx		=	0;
		pNewMeshContainer->_pSkinMeshEx				=	0;
		pNewMeshContainer->_ppmatFrameCombinedPtrEx	=	0;
		
	}//	~if( pSkinInfo )

	//	디바이스를 얻었을때 내부 참조카운트를 증가토록 했다.
	//	그러니 릴리즈시켜준다.
	pd3dDevice->Release();

	//	메쉬는 이펙트 파일에 대한 참조값을 포함할지도 모른다.
	if( pEffectInstances )
	{
		if( pEffectInstances->pEffectFilename )
			PUTOutputDebugStr( "이 x파일은 이펙트 파일을 참고로 하지만 이번 버전에선 이펙트파일은 다루지 않는다." );
	}

	*ppResNewMeshContainer	=	pNewMeshContainer;

	return hr;

}//	CreateMeshContainer
//-------------------------------------------------------------------------
HRESULT	CPRXMeshHierachy::DestroyFrame( LPD3DXFRAME pFrameToFree )
{
	sPRDXXFRAMEEx	*pFrame	=	(sPRDXXFRAMEEx*)pFrameToFree;

	PUT_SAFE_DELETE( pFrame->Name );
	PUT_SAFE_DELETE( pFrame );

	return S_OK;

}//	DestroyFrame
//-------------------------------------------------------------------------
HRESULT	CPRXMeshHierachy::DestroyMeshContainer( PRDXMESHCONTAINER pMeshContainerToFree )
{
	sPRDXXMESHCONTAINEREx	*pMeshContainer	=	(sPRDXXMESHCONTAINEREx*)pMeshContainerToFree;

	PUT_IsInValid( pMeshContainer )
		return S_OK;

	PUT_SAFE_DELETE( pMeshContainer->Name );

	if( pMeshContainer->_ppTexturesEx )
	{
		for( UINT unCur = 0; unCur < pMeshContainer->NumMaterials; ++unCur )
			PUT_SAFE_RELEASE( pMeshContainer->_ppTexturesEx[unCur] );
	}

	PUT_SAFE_DELETE_ARRAY( pMeshContainer->_ppTexturesEx );

	PUT_SAFE_DELETE_ARRAY( pMeshContainer->_pMtrlsEx );

	PUT_SAFE_DELETE( pMeshContainer->pAdjacency );

	PUT_SAFE_DELETE_ARRAY( pMeshContainer->_pmatBoneOffsetsEx );
	
	PUT_SAFE_DELETE_ARRAY( pMeshContainer->_ppmatFrameCombinedPtrEx );

	PUT_SAFE_RELEASE( pMeshContainer->_pSkinMeshEx );

	PUT_SAFE_RELEASE( pMeshContainer->MeshData.pMesh );

	PUT_SAFE_RELEASE( pMeshContainer->pSkinInfo );

	PUT_SAFE_DELETE( pMeshContainer );

	return S_OK;

}//	DestroyMeshContainer
//-------------------------------------------------------------------------
void	CPRXMeshHierachy::SetPath( char *pszPath )
{
	PUT_ZERO_MEMORY( m_szPath );
#ifndef _ENGCLI_VS2003_VS2008_
	sprintf_s( m_szPath, sizeof( m_szPath ), "%s/", pszPath );
#else
	PUT_Sprintf( m_szPath, "%s/", pszPath );
#endif

}//	SetPath
//-------------------------------------------------------------------------
//	EOF