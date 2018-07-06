#include "Common.h"
#include "GameInterface.h"
#include "PRCommonFunc.h"
#include "PRCommonTypeDef.h"
#include "PRCore.h"
#include "PRCamera.h"
#include "PRFont.h"
#include "PUTTimer.h"
#include "PUIDlgResourceMgr.h"
#include "UITestDlg.h"
#include "PUIListBox.h"
#include "PUIComboBox.h"
#include "PRInput.h"
#include "PRLight.h"
#include "PRXMeshHierachy.h"
#include "PUtCommon.h"
#include "PUtCommonStr.h"
#include "PUTCommonVerIntegrate.h"
#include "PRCommonVtxInfo.h"

#ifdef	_SAMP_ASEMODEL_RENDER_
#include "PRMdlAse.h"
#endif
 
#ifdef	_SAMP_ALPHABLEND_TEST_
PRDXVTXBUFF9 g_pVB		=	NULL;
PRDXTXTRBUFF9		g_pTSky		=	NULL;
PRDXTXTRBUFF9		g_pTEarth	=	NULL;

sPRVtx_Xyzrhw_Diff_Tex1 g_Vertices[]	= {
	{ D3DXVECTOR4( 50.0f,	50.0f,	0.5f, 0.0f ), D3DCOLOR_RGBA(0xff,0xff,0xff,0x80), 0, 0 },
	{ D3DXVECTOR4( 250.0f,	50.0f,	0.5f, 0.0f ), D3DCOLOR_RGBA(0xff,0xff,0xff,0x80), 1, 0 },
	{ D3DXVECTOR4( 50.0f,	250.0f, 0.5f, 0.0f ), D3DCOLOR_RGBA(0xff,0xff,0xff,0x80), 0, 1 },
	{ D3DXVECTOR4( 250.0f,	250.0f, 0.5f, 0.0f ), D3DCOLOR_RGBA(0xff,0xff,0xff,0x80), 1, 1 }
};
#endif


#ifdef _SAMP_D3DPT_TEST_TRIANGLEFAN_
	sPRVtx_Xyz_Diff gVtxInfo_TriangleFan[]	=	
	{
		{ D3DXVECTOR3( 0.0f, -1.0f, 0.0f ), PRCOLOR_NOCOLOR },
		{ D3DXVECTOR3(-1.0f, 0.0f, 0.0f), PRCOLOR_NOCOLOR },
		{ D3DXVECTOR3(-0.5f, 0.5f, 0.0f), PRCOLOR_NOCOLOR },

		{ D3DXVECTOR3( 0.0f, 1.0f, 0.0f), PRCOLOR_NOCOLOR },
		{ D3DXVECTOR3( 0.5f, 0.5f, 0.0f), PRCOLOR_NOCOLOR },
		{ D3DXVECTOR3( 1.0f, 0.0f, 0.0f), PRCOLOR_NOCOLOR } 
	};

	PRDXVTXBUFF9 g_pTriangleFan_VB     = NULL;
#endif//	_SAMP_D3DPT_TEST_TRIANGLEFAN_


#ifdef _SAMP_D3DPT_TEST_TRIANGLESTRIP_
	sPRVtx_Xyz_Diff gVtxInfo_TriangleStrip[]	=	
	{
		{ D3DXVECTOR3(-2.0f, 0.0f, 0.0f), PRCOLOR_NOCOLOR },
		{ D3DXVECTOR3(-1.0f, 1.0f, 0.0f), PRCOLOR_NOCOLOR },
		{ D3DXVECTOR3(-1.0f, 0.0f, 0.0f), PRCOLOR_NOCOLOR },
		{ D3DXVECTOR3( 0.0f, 1.0f, 0.0f), PRCOLOR_NOCOLOR },

		{ D3DXVECTOR3( 0.0f, 0.0f, 0.0f), PRCOLOR_NOCOLOR },
		{ D3DXVECTOR3( 1.0f, 1.0f, 0.0f), PRCOLOR_NOCOLOR },
		{ D3DXVECTOR3( 1.0f, 0.0f, 0.0f), PRCOLOR_NOCOLOR },
		{ D3DXVECTOR3( 2.0f, 1.0f, 0.0f), PRCOLOR_NOCOLOR }
	};

	PRDXVTXBUFF9 g_pTriangleStrip_VB     = NULL;
#endif//	_SAMP_D3DPT_TEST_TRIANGLESTRIP_



#ifdef _SAMP_D3DPT_TEST_LINESTRIP_
	sPRVtx_Xyz_Diff	gVtxInfo_LineStrip[]	=	
	{
		{ D3DXVECTOR3( 0.0f, 1.0f, 0.0f ),	PRCOLOR_NOCOLOR },
		{ D3DXVECTOR3( 1.0f, 0.0f, 0.0f ),	PRCOLOR_NOCOLOR },
		{ D3DXVECTOR3( 0.0f, -1.0f, 0.0f ),	PRCOLOR_NOCOLOR },

		{ D3DXVECTOR3( -1.0f, 0.0f, 0.0f ), PRCOLOR_NOCOLOR },
		{ D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),	PRCOLOR_NOCOLOR },
		{ D3DXVECTOR3( 0.0f, 1.0f, 0.0f ),	PRCOLOR_NOCOLOR }
	};

	PRDXVTXBUFF9	g_pLineStrip_VB	=	NULL;
#endif//	_SAMP_D3DPT_TEST_LINESTRIP_



#ifdef _SAMP_D3DPT_TEST_TRIANELIST_
	sPRVtx_Xyz_Diff	gVtxInfo_TriangleList[]	=	
	{
		{ D3DXVECTOR3( -1.0f, 0.0f, 0.0f ),	PRCOLOR_NOCOLOR },
		{ D3DXVECTOR3( 0.0f, 1.0f, 0.0f ),	PRCOLOR_NOCOLOR },
		{ D3DXVECTOR3( 1.0f, 0.0f, 0.0f ),	PRCOLOR_NOCOLOR },

		{ D3DXVECTOR3( -0.5f, -1.0f, 0.0f ), PRCOLOR_NOCOLOR },
		{ D3DXVECTOR3( 0.0f, -0.5f, 0.0f ),	PRCOLOR_NOCOLOR },
		{ D3DXVECTOR3( 0.5f, -1.0f, 0.0f ),	PRCOLOR_NOCOLOR }
	};

	PRDXVTXBUFF9	g_pTriangleList_VB	=	NULL;
	PRDXIDXBUFF9	g_pTriangleList_IB	=	NULL;
#endif//	_SAMP_D3DPT_TEST_TRIANELIST_



#ifdef _SAMP_RENDERTEST_
void	RenderTest( IDirect3DDevice9* pDevice, float elapsedTime )
{
	D3DXMATRIX wrd;		
	D3DXMatrixIdentity(&wrd);	
	devSetTrsformWorld( pDevice, &wrd );
	
#ifdef _ENG_TEST_UI_
	gUIDlgResMgr->OnRender( pDevice, fElapsedTime );
#endif


#ifdef 	_ENG_DRAWPT_
	devDrawPt( pDevice, D3DXVECTOR3( 0.0, 0.0f, 0.0f ), PRCOLOR_NOCOLOR );
	devDrawPt( pDevice, D3DXVECTOR3(0.5f, 0.0f, 0.0f), PRCOLOR_NOCOLOR );
	devDrawPt( pDevice, D3DXVECTOR3(-0.5f, 0.0f, 0.0f), PRCOLOR_NOCOLOR );
	devDrawPt( pDevice, D3DXVECTOR3(0.0f, -0.5f, 0.0f), PRCOLOR_NOCOLOR );
	devDrawPt( pDevice, D3DXVECTOR3(0.0f, 0.5f, 0.0f), PRCOLOR_NOCOLOR );
#endif


#ifdef _SAMP_D3DPT_TEST_TRIANGLEFAN_
	devSetRSLightEnable( pDevice, FALSE );
	devSetStreamSrc( pDevice, 0, g_pTriangleFan_VB, 0, sizeof( sPRVtx_Xyz_Diff ) );
	devSetTxtr( pDevice, 0, NULL );
	devSetFVF( pDevice, sPRVtx_Xyz_Diff::FVF );
	devDrawPrim( pDevice, D3DPT_TRIANGLEFAN, 0, 4 );	//	삼각형 갯수.
	devSetRSLightEnable( pDevice, TRUE );
#endif


#ifdef _SAMP_D3DPT_TEST_TRIANGLESTRIP_	
	devSetRSLightEnable( pDevice, FALSE );
	devSetStreamSrc( pDevice, 0, g_pTriangleStrip_VB, 0, sizeof( sPRVtx_Xyz_Diff ) );
	devSetTxtr( pDevice, 0, NULL );
	devSetFVF( pDevice, sPRVtx_Xyz_Diff::FVF );
	devDrawPrim( pDevice, D3DPT_TRIANGLESTRIP, 0, 6 );	//	삼각형 갯수.
	devSetRSLightEnable( pDevice, TRUE );
#endif


#ifdef _SAMP_D3DPT_TEST_LINESTRIP_
	devSetRSLightEnable( pDevice, FALSE );
	devSetStreamSrc( pDevice, 0, g_pLineStrip_VB, 0, sizeof( sPRVtx_Xyz_Diff ) );
	devSetTxtr( pDevice, 0, NULL );
	devSetFVF( pDevice, sPRVtx_Xyz_Diff::FVF );
	devDrawPrim( pDevice, D3DPT_LINESTRIP, 0, 5 );	//	라인 갯수.
	devSetRSLightEnable( pDevice, TRUE );
#endif


#ifdef _SAMP_D3DPT_TEST_TRIANELIST_
	devSetRSLightEnable( pDevice, FALSE );
	devSetStreamSrc( pDevice, 0, g_pTriangleList_VB, 0, sizeof( sPRVtx_Xyz_Diff ) );
	devSetTxtr( pDevice, 0, NULL );
	devSetFVF( pDevice, sPRVtx_Xyz_Diff::FVF );
	devSetIdx( pDevice, g_pTriangleList_IB );
	//	devDrawP( pDevice, D3DPT_TRIANGLELIST, 0, 2 );	//	삼각형 갯수.
	devDrawIdxPrim( pDevice, D3DPT_TRIANGLELIST, 0, 0, 6, 0, 2 );

	devSetRSLightEnable( pDevice, TRUE );
#endif


#ifdef _SAMP_ALPHABLEND_TEST_

	devSetStreamSrc( pDevice, 0, g_pVB, 0, sizeof( sPRVtx_Xyzrhw_Diff_Tex1 ) );
	devSetFVF( pDevice, sPRVtx_Xyzrhw_Diff_Tex1::FVF );
	
	devSetRSAlphaBlnd( pDevice, FALSE );
	devSetTxtr( pDevice, 0, g_pTSky );
	devDrawPrim( pDevice, D3DPT_TRIANGLESTRIP, 0, 2 );

	devSetRSAlphaBlnd( pDevice, TRUE );
	devSetTxtr( pDevice, 0, g_pTEarth );
	devDrawPrim( pDevice, D3DPT_TRIANGLESTRIP, 0, 2 );

#endif	//	_SAMP_ALPHABLEND_TEST_

}//	RenderTest
#endif	//	_SAMP_RENDERTEST_


#ifdef _ENG_OBJECT_MGR_
#include "PRObjGrid.h"
#endif

//---------------------------------------------------------------------------
void CJGameInterface::InitMembers()
{		
#ifdef _SAMP_RENDER_TEAPOT_
	m_pD3DXMesh		=	NULL;
#endif

#ifdef _ENG_TEST_UI_
	m_pTestDlg		=	NULL;
#endif

	PUT_ZERO_MEMORY( m_tszFPS );

	InitMembersShader();


#ifdef _SAMP_ASEMODEL_RENDER_
	m_AseTest	=	NULL;
#endif
	
	
}//	InitMembers
//---------------------------------------------------------------------------
void CJGameInterface::ClearMembers()
{	
#ifdef _SAMP_RENDER_TEAPOT_
	PUT_SAFE_RELEASE( m_pD3DXMesh );
#endif

#ifdef _ENG_TEST_UI_
	gUIDlgResMgrDestroy;
	PUT_SAFE_DELETE( m_pTestDlg );
#endif

#ifdef _ENG_OBJECT_MGR_
	m_ObjMgr.DeleteAll();
#endif

#ifdef _SAMP_D3DPT_TEST_TRIANGLEFAN_
	PUT_SAFE_RELEASE( g_pTriangleFan_VB );
#endif

#ifdef _SAMP_D3DPT_TEST_TRIANGLESTRIP_
	PUT_SAFE_RELEASE( g_pTriangleStrip_VB) ;
#endif

#ifdef _SAMP_D3DPT_TEST_LINESTRIP_
	PUT_SAFE_RELEASE( g_pLineStrip_VB );
#endif

#ifdef _SAMP_D3DPT_TEST_TRIANELIST_
	PUT_SAFE_RELEASE( g_pTriangleList_VB );
	PUT_SAFE_RELEASE( g_pTriangleList_IB );
#endif

#ifdef _SAMP_ALPHABLEND_TEST_
	PUT_SAFE_RELEASE( g_pVB );
	PUT_SAFE_RELEASE( g_pTSky );
	PUT_SAFE_RELEASE( g_pTEarth );
#endif

#ifdef _SAMP_ASEMODEL_RENDER_
	PUT_SAFE_DELETE( m_AseTest );
#endif

	ClearMembersShader();


}//	ClearMembers
//---------------------------------------------------------------------------
LRESULT	CJGameInterface::WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
#ifdef _ENG_TEST_UI_

	if( gUIDlgResMgr->IMEMsgProc( hWnd, uMsg, wParam, lParam ) )
		return 0;

	if( gUIDlgResMgr->MsgProc( hWnd, uMsg, wParam, lParam ) )
		return 0;
#endif

	return GetFrameWork()->WndProc( hWnd, uMsg, wParam, lParam );

}//	WndProc
//---------------------------------------------------------------------------
bool CJGameInterface::Init()
{
	// 디바이스 정보가 필요없는 초기화.
	//	OnCreateDevice 다음에 호출된다.

#ifdef _ENG_TEST_UI_
	m_pTestDlg		=	new	CUITestDlg;

	///	대화상자		
	m_pTestDlg->SetResMgr( gUIDlgResMgr );
	m_pTestDlg->Init();   
#endif

	return true;
}//	Init
//---------------------------------------------------------------------------
HRESULT CJGameInterface::OnCreateDevice( IDirect3DDevice9* pDevice )
{
	HRESULT hr = S_OK;
//	GetFrameWork()->GetFont()->Init( pDevice, L"Arial", 12 );
	GetFrameWork()->GetFont()->Init( pDevice, L"Arial", 12, FALSE, TRUE );	// 이탤릭체만 적용
//	GetFrameWork()->GetFont()->Init( pDevice, L"Arial", 12, TRUE, TRUE );	// 이탤릭체 + 볼드 적용

#ifdef _SAMP_RENDER_TEAPOT_	
	hr = D3DXCreateTeapot( pDevice, &m_pD3DXMesh, NULL );
	PUT_IsFailed( hr )
		return hr;
#endif

#ifdef _ENG_TEST_UI_
	gUIDlgResMgr->OnCreateDevice( GetFrameWork()->GetHwnd(), pDevice );
	gUIDlgResMgr->AddFont( L"굴림", 12, FW_NORMAL );
#endif

#ifdef _ENG_OBJECT_MGR_
	m_ObjMgr.Add( new CPRObjGrid( D3DXVECTOR3(0.0f, 0.0f, 0.0f), 21 ) );
#endif


#ifdef _SAMP_D3DPT_TEST_TRIANGLEFAN_
	hr = devCreateVtxBuff(	pDevice,
		6 * sizeof( sPRVtx_Xyz_Diff ),	//	버택스 갯수
		0,
		sPRVtx_Xyz_Diff::FVF,
		D3DPOOL_MANAGED,	// D3DPOOL_MANAGED D3DPOOL_DEFAULT 차이???
		&g_pTriangleFan_VB,
		NULL );

	if( FAILED(hr) )
		return hr;

	sPRVtx_Xyz_Diff *pVertice = NULL;	
	g_pTriangleFan_VB->Lock( 0, 0, (void**)&pVertice, 0 );

	memcpy( pVertice, gVtxInfo_TriangleFan, sizeof( gVtxInfo_TriangleFan ) );
	g_pTriangleFan_VB->Unlock();
#endif

#ifdef _SAMP_D3DPT_TEST_TRIANGLESTRIP_
	hr = devCreateVtxBuff(	pDevice,
						8 * sizeof( sPRVtx_Xyz_Diff ),	//	버택스 갯수
						0,
						sPRVtx_Xyz_Diff::FVF,
						D3DPOOL_MANAGED,	// D3DPOOL_MANAGED D3DPOOL_DEFAULT 차이???
						&g_pTriangleStrip_VB,
						NULL );

	if( FAILED(hr) )
		return hr;

	sPRVtx_Xyz_Diff *pVertice = NULL;
	g_pTriangleStrip_VB->Lock( 0, 0, (void**)&pVertice, 0 );
	memcpy( pVertice, gVtxInfo_TriangleStrip, sizeof( gVtxInfo_TriangleStrip ) );
	g_pTriangleStrip_VB->Unlock();
#endif 


#ifdef _SAMP_D3DPT_TEST_LINESTRIP_
	hr = devCreateVtxBuff(	pDevice,
		6 * sizeof( sPRVtx_Xyz_Diff ),
		0,
		sPRVtx_Xyz_Diff::FVF,
		D3DPOOL_MANAGED,	// D3DPOOL_MANAGED D3DPOOL_DEFAULT 차이???
		&g_pLineStrip_VB,
		NULL );

	if( FAILED(hr) )
		return hr;

	sPRVtx_Xyz_Diff *pVertice = NULL;
	g_pLineStrip_VB->Lock( 0, 0, (void**)&pVertice, 0 );
	memcpy( pVertice, gVtxInfo_LineStrip, sizeof( gVtxInfo_LineStrip ) );
	g_pLineStrip_VB->Unlock();
#endif


#ifdef _SAMP_D3DPT_TEST_TRIANELIST_
	hr = devCreateVtxBuff(	pDevice,
		6 * sizeof( sPRVtx_Xyz_Diff ),
		0,
		sPRVtx_Xyz_Diff::FVF,
		D3DPOOL_MANAGED,	// D3DPOOL_MANAGED D3DPOOL_DEFAULT 차이???
		&g_pTriangleList_VB,
		NULL );

	if( FAILED(hr) )
		return hr;

	sPRVtx_Xyz_Diff *pVertice = NULL;
	g_pTriangleList_VB->Lock( 0, 0, (void**)&pVertice, 0 );
	memcpy( pVertice, gVtxInfo_TriangleList, sizeof( gVtxInfo_TriangleList ) );
	g_pTriangleList_VB->Unlock();


	sPRINDEX16 indices[]	=
	{
		{ 0, 1, 2 }, 
		{ 3, 4, 5 }
	};

	hr = devCreateIdxBuff(	pDevice, 
							2 * sizeof( sPRINDEX16 ),
							0,
							D3DFMT_INDEX16,
							D3DPOOL_MANAGED,
							&g_pTriangleList_IB,
							NULL );
	if( FAILED( hr ) )
		return E_FAIL;

	void*	pIndices;
	g_pTriangleList_IB->Lock( 0, sizeof( indices ), (void**)&pIndices, 0 );
	memcpy( pIndices, indices, sizeof(indices) );
	g_pTriangleList_IB->Unlock();

#endif

#ifdef _SAMP_ALPHABLEND_TEST_

	hr = devCreateVtxBuff(	pDevice, 
							4 * sizeof(sPRVtx_Xyzrhw_Diff_Tex1),
							0, sPRVtx_Xyzrhw_Diff_Tex1::FVF,
							D3DPOOL_MANAGED,
							&g_pVB, 
							NULL
							);

	PUT_IsFailed( hr )
	{
		PUT_ERROR;
		return E_FAIL;
	}

	void*	pVertices;
	hr = devVtxLock( g_pVB, 0, sizeof(g_Vertices), (void**)&pVertices, 0 );
	PUT_IsFailed( hr )
	{
		PUT_ERROR;
		return hr;
	}
	memcpy( pVertices, g_Vertices, sizeof( g_Vertices ) );
	devVtxUnlock( g_pVB );


	hr = D3DXCreateTextureFromFile( pDevice, 
									"TestResource/texture/SKy.BMP",
									&g_pTSky );
	PUT_IsFailed( hr )
	{
		PUT_ERROR;
		return E_FAIL;
	}


	hr = D3DXCreateTextureFromFile( pDevice, 
									"TestResource/texture/earth.bmp",
									&g_pTEarth );

	PUT_IsFailed( hr )
	{
		PUT_ERROR;
		return E_FAIL;
	}

	devSetRSDiTherEnable( pDevice, FALSE );		
	devSetRSSpecularEnable( pDevice, FALSE );
	devSetRSZEnable( pDevice, TRUE );
	devSetRSAMBIENT( pDevice, 0x000f0f0f );

	devSetTSSAlphop( pDevice, 0, D3DTOP_MODULATE );
	devSetTSSAlphaArg1( pDevice, 0, D3DTA_TEXTURE );	
	devSetTSSAlphaArg2( pDevice, 0, D3DTA_DIFFUSE );

	devSetRSBlendOP( pDevice, D3DBLENDOP_ADD );
	devSetRSDestBlend( pDevice, D3DBLEND_INVSRCALPHA );
	devSetRSSrcBlend( pDevice, D3DBLEND_SRCALPHA );
 
#endif	//	_SAMP_ALPHABLEND_TEST_

	OnCreateDeviceShader( pDevice );


#ifdef _SAMP_ASEMODEL_RENDER_
	m_AseTest	=	new CPRMdlAse;
	TCHAR	szAse[128]		= {0,};
	TCHAR	szAseTxtr[128]	= {0,};
	PUT_Sprintf( szAse, "%s%s",		DIRPATH_ASE,		PUT_CSTR_TCHAR("mong.ASE") );

	bool bRes = m_AseTest->OnCreate(	pDevice, 
										szAse, 
										(void*)DIRPATH_ASE_TXTR );
#endif


 	return hr;	
}//	OnCreateDevice
//---------------------------------------------------------------------------
HRESULT CJGameInterface::OnResetDevice( IDirect3DDevice9* pDevice )
{
	GetFrameWork()->GetFont()->OnResetDevice();

	GetFrameWork()->GetRenderer()->GetLight()->OnReset();

#ifdef _ENG_OBJECT_MGR_	
	VEC_ITER(CPRObject*) iterCur =	m_ObjMgr.GetIterBegin();
	while( iterCur != m_ObjMgr.GetIterEnd() )
	{
		CPRObjGrid *pObj = (CPRObjGrid*)(*iterCur);
		pObj->OnReset( pDevice );
		++iterCur;
	}
#endif

#ifdef _ENG_TEST_UI_
	gUIDlgResMgr->OnResetDevice( pDevice );
#endif

	OnResetDeviceShader( pDevice );

	return S_OK;
}//	OnResetDevice
//---------------------------------------------------------------------------
HRESULT CJGameInterface::OnLostDevice()
{
	GetFrameWork()->GetFont()->OnLostDevice();

#ifdef _ENG_TEST_UI_
	gUIDlgResMgr->OnLostDevice();
#endif


#ifdef _ENG_OBJECT_MGR_	
	VEC_ITER(CPRObject*) iterCur =	m_ObjMgr.GetIterBegin();
	while( iterCur != m_ObjMgr.GetIterEnd() )
	{
		CPRObjGrid *pObj = (CPRObjGrid*)(*iterCur);
		pObj->OnLost();
		++iterCur;
	}
#endif

	OnLostDeviceShader( );


	return S_OK;

}//	OnLostDevice
//---------------------------------------------------------------------------
HRESULT CJGameInterface::OnDestroyDevice()
{
	GetFrameWork()->GetFont()->ClearMembers();

#ifdef _ENG_TEST_UI_
	gUIDlgResMgr->OnDestroyDevice();
#endif

	return S_OK;
}//	OnDestroyDevice
//---------------------------------------------------------------------------
void CJGameInterface::OnUpdate( float fElapsedTime )
{
#ifdef _FR_TIMEREX_
	static	DWORD	dwTick	=	0;
	static	DWORD	dwFPS	=	0;

	// 1초 경과후 출력한다.
	if( GetTickCount() - dwTick > 1000 )
	{
		dwTick	=	GetTickCount();

#ifndef _ENGCLI_VS2003_VS2008_
		sprintf_s( m_tszFPS, sizeof( m_tszFPS ), "%d FPS", dwFPS );
#else
		PUT_Sprintf( m_tszFPS, sizeof( m_tszFPS ), "%d FPS", dwFPS );
#endif
		
		
		dwFPS = 0;
		return;	
	}

	++dwFPS;

#else
#ifndef _ENGCLI_VS2003_VS2008_
	sprintf_s( m_tszFPS, sizeof( m_tszFPS ), "%.2f FPS", GetFrameWork()->GetTimer()->GetFPS() );
#else
	PUT_Sprintf( m_tszFPS, "%.2f FPS", GetFrameWork()->GetTimer()->GetFPS() );
#endif
#endif	//	_FR_TIMEREX_


	if( GetFrameWork() )
	{
		//@	스샷 찍기.
		if( GetFrameWork()->GetInput()->IsKeyOneClick( DIK_F1 ) )
		{
			GetFrameWork()->GetRenderer()->SaveScreenShot("ScreenShot");
		}

		//@	스크린모드 전환.
		if( GetFrameWork()->GetInput()->IsKeyOneClick( DIK_F2 ) )
		{
			if( GetFrameWork() )
				GetFrameWork()->ToggleFullScreen();
		}

		//@	와이어모드 전환.
		if( GetFrameWork()->GetInput()->IsKeyOneClick( DIK_F3 ) )
		{
			if( GetFrameWork() )
				GetFrameWork()->ToggleWireFrame();
		}

		//@	카메라 타입 전환.
		if( GetFrameWork()->GetInput()->IsKeyOneClick( DIK_F4 ) )
		{
			if( GetFrameWork()->GetCamera()->GetType() == CPRCamera::eTYPE_FIRST )
			{
				GetFrameWork()->GetCamera()->SetType(CPRCamera::eTYPE_THIRD);
			}
			else
				GetFrameWork()->GetCamera()->SetType(CPRCamera::eTYPE_FIRST);
		}

		GetFrameWork()->GetCamera()->ResetTmpDelta();

		//@	조명 타입 전환.
		if( GetFrameWork()->GetInput()->IsKeyOneClick( DIK_F5 ) )
		{
			if( GetFrameWork()->GetRenderer()->GetLight()->GetType() == D3DLIGHT_DIRECTIONAL )
				GetFrameWork()->GetRenderer()->GetLight()->SetType( D3DLIGHT_POINT );
			else
				GetFrameWork()->GetRenderer()->GetLight()->SetType( D3DLIGHT_DIRECTIONAL );
		}

		//@	종료.
		if( GetFrameWork()->GetInput()->IsKeyOneClick( DIK_ESCAPE ) )
		{
			PostQuitMessage( 0 );
		}


#ifdef _SAMP_ALPHABLEND_TEST_

		// D3DRS_BLENDOP : 블렌드옵션
		// D3DRS_DESTBLEND : 바닥색 ( 이미 렌더링된 렌더링 타겟색의 합성강도 ) Cd
		// D3DRS_SRCBLEND : 덮일색 ( 이제부터 렌더링하려는 폴리곤의 합성강도 ) Cs
		PRLPD3DDEV9 pDev = GetFrameWork()->GetRenderer()->GetDevice();

		if( GetFrameWork()->GetInput()->IsKeyOneClick( DIK_1 ) )
		{			
			//선형합성 C = Cd(1 - As) + CsAs
			devSetRSBlendOP( pDev, D3DBLENDOP_ADD );			
			devSetRSDestBlend( pDev, D3DBLEND_INVSRCALPHA );
			devSetRSSrcBlend( pDev, D3DBLEND_SRCALPHA );
		}
		if( GetFrameWork()->GetInput()->IsKeyOneClick( DIK_2 ) )
		{
			//덧셈합성 C = Cd + CsAs
			devSetRSBlendOP( pDev, D3DBLENDOP_ADD );			
			devSetRSDestBlend( pDev, D3DBLEND_ONE );
			devSetRSSrcBlend( pDev, D3DBLEND_SRCALPHA );
		}
		if( GetFrameWork()->GetInput()->IsKeyOneClick( DIK_3 ) )
		{
			//뺄셈합성 C = Cd - CsAs
			devSetRSBlendOP( pDev, D3DBLENDOP_REVSUBTRACT );
			devSetRSDestBlend( pDev, D3DBLEND_ONE );
			devSetRSSrcBlend( pDev, D3DBLEND_SRCALPHA );
		}
		if( GetFrameWork()->GetInput()->IsKeyOneClick( DIK_4 ) )
		{
			//곱셉합성 C = Cd * Cs
			devSetRSBlendOP( pDev, D3DBLENDOP_ADD );
			devSetRSDestBlend( pDev, D3DBLEND_SRCCOLOR );
			devSetRSSrcBlend( pDev, D3DBLEND_ZERO );
		}
		if( GetFrameWork()->GetInput()->IsKeyOneClick( DIK_5 ) )
		{
			//제곱합성 C = Cd  * Cd
			devSetRSBlendOP( pDev, D3DBLENDOP_ADD );
			devSetRSDestBlend( pDev, D3DBLEND_DESTCOLOR );
			devSetRSSrcBlend( pDev, D3DBLEND_ZERO );
		}
		if( GetFrameWork()->GetInput()->IsKeyOneClick( DIK_6 ) )
		{
			//네거티브 포지티브 반전 C = ( 1 - Cd ) * Cs
			devSetRSBlendOP( pDev, D3DBLENDOP_ADD );
			devSetRSDestBlend( pDev, D3DBLEND_ZERO );
			devSetRSSrcBlend( pDev, D3DBLEND_INVDESTCOLOR );
		}
		if( GetFrameWork()->GetInput()->IsKeyOneClick( DIK_7 ) )
		{
			//불투명 C = Cs
			devSetRSBlendOP( pDev, D3DBLENDOP_ADD );
			devSetRSDestBlend( pDev, D3DBLEND_ZERO );
			devSetRSSrcBlend( pDev, D3DBLEND_ONE );
		}
		if( GetFrameWork()->GetInput()->IsKeyOneClick( DIK_8 ) )
		{
			//불투명 C = Cd
			devSetRSBlendOP( pDev, D3DBLENDOP_ADD );
			devSetRSDestBlend( pDev, D3DBLEND_ONE );
			devSetRSSrcBlend( pDev, D3DBLEND_ZERO );
		}

#endif	//	#ifdef _SAMP_ALPHABLEND_TEST_

	}//	if( GetFrameWork() )

#ifdef _SAMP_ASEMODEL_RENDER_
	m_AseTest->OnUpdate( fElapsedTime );
#endif



}//	OnUpdate
//---------------------------------------------------------------------------
HRESULT CJGameInterface::OnRender( PRLPD3DDEV9 pDev, float fElapsedTime )
{
	GetFrameWork()->GetFont()->Print( m_tszFPS, 5, 5, D3DCOLOR_XRGB( 255, 255, 0 ) );


#ifdef _ENG_OBJECT_MGR_
	devSetVtxShader( pDev, NULL );
	devSetPxShader( pDev, NULL );
	devSetRSZEnable( pDev, TRUE );
	VEC_ITER(CPRObject*) iterCur =	m_ObjMgr.GetIterBegin();
	while( iterCur != m_ObjMgr.GetIterEnd() )
	{
		CPRObjGrid *pObj = (CPRObjGrid*)(*iterCur);
		pObj->OnRender( pDev, fElapsedTime );
		++iterCur;
	}
	devSetRSZEnable( pDev, FALSE );
#endif


#ifdef _SAMP_RENDER_TEAPOT_
	devSetTxtr( pDev, 0, NULL );
	devSetRSAlphaBlnd( pDev, FALSE );
	devSetRSZEnable( pDev, TRUE );
	devSetRSCullMode( pDev, D3DCULL_NONE );
	m_pD3DXMesh->DrawSubset(0);	
	devSetRSCullMode( pDev, D3DCULL_CCW );
	devSetRSZEnable( pDev, FALSE );
#endif


#ifdef _SAMP_RENDERTEST_	
	RenderTest( pDev, fElapsedTime );
#endif

//	OnRenderShader( pDev, fElapsedTime );

	m_AseTest->OnRender( pDev, fElapsedTime );

	
	return S_OK;

}//	Render
//---------------------------------------------------------------------------
//	EOF