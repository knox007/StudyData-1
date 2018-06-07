#include "Common.h"
#include "GameInterface.h"
#include "PRCommonFunc.h"
#include "PRCommonTypeDef.h"
#include "PRXMeshHierachy.h"
#include "PRCommonVtxInfo.h"
#include "PRCamera.h"
#include "PUtTimer.h"
#include "PRLight.h"
#include "PRCore.h"
#include "PRCommonFunc.h"
#include "PRMdlXFile.h"




//---------------------------------------------------------------------------
void	CJGameInterface::InitMembersShader()
{
	m_pXFileUFO		=	NULL;
	m_pXFileMap		=	NULL;	
	m_pEffect		=	NULL;
 
}//	InitMembersShader
//---------------------------------------------------------------------------
void	CJGameInterface::ClearMembersShader()
{ 
	PUT_SAFE_DELETE( m_pXFileUFO );
	PUT_SAFE_DELETE( m_pXFileMap );
	PUT_SAFE_RELEASE( m_pEffect ); 

}//	ClearMembersShader
//---------------------------------------------------------------------------
HRESULT CJGameInterface::OnCreateDeviceShader( LPDIRECT3DDEVICE9 pDev )
{
	HWND	hWnd			=	NULL;
	HRESULT hr				=	S_OK;
	PRDXXBUFF	pShader	=	NULL;
	PRDXXBUFF	pErr	=	NULL;
	bool bRes				=	false;


	//@	UFO Mesh
	m_pXFileUFO		=	new CPRMdlXFile;
	bRes = m_pXFileUFO->Init( pDev, PUT_CSTR_TCHAR("TestResource/Model/xfile/ufo.x"), D3DXVECTOR3( 0,0,0 ), D3DXVECTOR3( 1,1,1 ), false );
	PUT_IsInValid( bRes )
	{
		IsFailed( E_FAIL );
	}

	//@ Map Mesh
	m_pXFileMap		=	new CPRMdlXFile;
	bRes = m_pXFileMap->Init( pDev, PUT_CSTR_TCHAR("TestResource/Model/xfile/map.x"), D3DXVECTOR3( 0,0,0 ), D3DXVECTOR3( 1,1,1 ), false );
	PUT_IsInValid( bRes )
	{
		IsFailed( E_FAIL );
	}

	//@ Effect
	pErr	=	NULL;
	hr = devCreateEffFromFile(	pDev, 
								PUT_CSTR_TCHAR("TestResource/shader/PixelPhong.fx"),
								NULL,
								NULL,
								0,
								NULL,
								&m_pEffect,
								&pErr
								);	
	PRCheckFXError( hr, pErr );

	m_hTechnique	=	PRGetTechByName( m_pEffect, "TShader" );
	m_hmatWVP		=	PRGetParaByName( m_pEffect, NULL, "matWVP" );
	m_hvecLightDir	=	PRGetParaByName( m_pEffect, NULL, "vecLightDir" );
	m_hvecColor		=	PRGetParaByName( m_pEffect, NULL, "vecColor" );
	m_hvecEyePos	=	PRGetParaByName( m_pEffect, NULL, "vecEyePos" );

	PUT_SAFE_RELEASE( pErr );
 
	return S_OK;

}//	OnCreateDeviceShader
//---------------------------------------------------------------------------
HRESULT CJGameInterface::OnRenderShader( LPDIRECT3DDEVICE9 pDev, float fElapsedTime )
{
	devSetTSSCOLOROP( pDev, 0, D3DTOP_SELECTARG1 );
	devSetTSSCOLORARG1( pDev, 0, D3DTA_TEXTURE );

	devSetRSZEnable( pDev, TRUE );	
	devSetSmpSFilters( pDev, 0, D3DTEXF_LINEAR );
	m_pXFileMap->OnRender( pDev, fElapsedTime );


	//@ 셰이더 ------------------------------------------------
	PUT_IsInValid( m_pEffect )
		return E_FAIL;

	PRDXMat	matTmp, 
				matTranslation, 
				matRotation,
				matLocal,
				matWorld, 
				matView, 
				matProj;

	PRDVec4	vecTmp,
				vecLightPos, 
				vecEyePos;
	

	m_pEffect->SetTechnique( m_hTechnique );
	m_pEffect->Begin( NULL, 0 );
	m_pEffect->BeginPass( 0 );
	devSetFVF( pDev, sPRVtx_Xyz_Norm::FVF );

	devSetTSSCOLOROP( pDev, 0, D3DTOP_SELECTARG1 );
	devSetTSSCOLORARG1( pDev, 0, D3DTA_DIFFUSE );

	
	PRDXMatTranslation( &matTmp, 1.0f, 0.0f, 0.0f );
	PRDXMatRotY( &matRotation, GetFrameWork()->GetTimer()->GetRunningTime() );
	PRDXMatTranslation( &matTranslation, 1.0f, 1.2f, 0.0f );
	matLocal = matTmp * matRotation * matTranslation;
	// 로컬-월드 변환행렬.
//	m_pEffect->SetMatrix( m_hmatLocal, &matLocal );
	// 로컬-투영 변환행렬.
	matWorld = matLocal * *GetCamera()->GetMat(CPRCamera::eMAT_VIEW) * *GetCamera()->GetMat(CPRCamera::eMAT_PROJECTION);
	m_pEffect->SetMatrix( m_hmatWVP, &matWorld );

	//	광원방향
	vecLightPos = PRDVec4( GetRenderer()->GetLight()->GetDir().x,
							GetRenderer()->GetLight()->GetDir().y,
							GetRenderer()->GetLight()->GetDir().z,
							0 );

	PRDXMatInv( &matTmp, NULL, &matWorld );
	PRDVec4Trsfrm( &vecTmp, &vecLightPos, &matTmp );
	PRDVec3Norm( (PRDVec3*)&vecTmp, (PRDVec3*)&vecTmp );
	vecTmp.w = -0.3f;	//	환경광 강도.
	m_pEffect->SetVector( m_hvecLightDir, &vecTmp );

	//	시점
	matTmp = matWorld * *GetCamera()->GetMat(CPRCamera::eMAT_VIEW);
	PRDXMatInv( &matTmp, NULL, &matTmp );
	vecTmp = PRDVec4( 0, 0, 0, 1 );
	PRDVec4Trsfrm( &vecTmp, &vecTmp, &matTmp );
	m_pEffect->SetVector( m_hvecEyePos, &vecTmp );

	PRDMTRL9* pMtrl = m_pXFileUFO->GetMtrls();
	int nMtrlSize = m_pXFileUFO->GetMtrlSize();
	for( int nCur = 0; nCur < nMtrlSize; ++nCur )
	{
		vecTmp.x = pMtrl->Diffuse.r / 1.3f;
		vecTmp.y = pMtrl->Diffuse.g / 1.3f;
		vecTmp.z = pMtrl->Diffuse.b / 1.3f;

		m_pEffect->SetVector( m_hvecColor, &vecTmp );
		m_pXFileUFO->OnRender( pDev, fElapsedTime );
	}
	
	m_pEffect->EndPass();
	m_pEffect->End();

	m_pEffect->SetTechnique( NULL );
	
	//@ ------------------------------------------------ 셰이더 --

	

	return S_OK;

}//	OnRenderShader
//---------------------------------------------------------------------------
HRESULT CJGameInterface::OnUpdateShader( float fElapsedTime )
{
	m_pXFileMap->OnUpdate( fElapsedTime );
	m_pXFileUFO->OnUpdate( fElapsedTime );

	return S_OK;
}//	OnUpdateShader
//---------------------------------------------------------------------------
HRESULT	CJGameInterface::OnResetDeviceShader( IDirect3DDevice9* pDevice )
{ 
	if( m_pEffect )
	{
		PUT_IsInValid(m_pEffect)
		{
			IsFailed(E_FAIL);
		}
		m_pEffect->OnResetDevice();
	}
	
	return S_OK;

}//	OnResetDeviceShader
//---------------------------------------------------------------------------
HRESULT	CJGameInterface::OnLostDeviceShader( LPDIRECT3DDEVICE9 pDev )
{ 
	if( m_pEffect )
	{
		PUT_IsInValid(m_pEffect)
		{
			IsFailed(E_FAIL);
		}
		m_pEffect->OnLostDevice();
	}
	
	return S_OK;

}//	OnLostDeviceShader
//---------------------------------------------------------------------------
//	EOF