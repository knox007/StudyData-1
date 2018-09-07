#include "StdAfx.h"
#include "PRDShowImage.h"
#include "PUtCommon.h"
#include "PRCommonFunc.h"
#include "PUtCommonStr.h"
#include "PRCommonVtxInfo.h"
#include "PRDShowTexture.h"
#include "PreDef_Render.h"
#include "PUTCommonVerIntegrate.h"

#pragma warning( disable : 4996 )
//----------------------------------------------------------------------------------- 
void	CPRDShowImage::InitMembers()
{
	m_pVtxBuff		=	NULL;
	m_pTextureBuff	=	NULL;

	m_szFPath[0]	=	0;
	m_szFName[0]	=	0;

	m_bVisible		=	true;
	m_ePlayState	=	ePLAYSTATE_NONE;

	SetSize( 0.0f, 0.0f );
	SetPos( 0.0f, 0.0f, 0.0f );

	m_nPlayCount	=	0;
	m_nPlayMaxCount	=	1;

	SetMediaType( eMEDIATYPE_NONE );
	SetMediaTypeSub( eMEDIATYPESUB_NONE );
	SetPlayState( ePLAYSTATE_NONE );

	SetD3DFormat( D3DFMT_UNKNOWN );

	m_bDeviceLost	=	false;

}//	InitMembers
//-----------------------------------------------------------------------------------
void	CPRDShowImage::ClearMembers()
{
#ifdef REGISTER_FILTERGRAPH
	RemoveFromROT();
#endif

	PUT_IsInValid( (!m_pMediaCtrl) )
		m_pMediaCtrl->Stop();

	PUT_IsInValid( (!m_pMediaCtrl) )
		m_pMediaCtrl.Release();

	PUT_IsInValid( (!m_pMediaEvent) )
		m_pMediaEvent.Release();

	PUT_IsInValid( (!m_pMediaPos) )
		m_pMediaPos.Release();	

	PUT_IsInValid( (!m_pGraphBuilder) )
		m_pGraphBuilder.Release();

	PUT_IsInValid( (!m_pRenderer) )
		m_pRenderer.Release();

	PUT_SAFE_RELEASE( m_pVtxBuff );
	PUT_SAFE_RELEASE( m_pTextureBuff );

}//	ClearMembers
//-----------------------------------------------------------------------------------
HRESULT		CPRDShowImage::InitVtxBuff( PRLPD3DDEV9 pDev )
{
	HRESULT	hr	=	devCreateVtxBuff(	pDev, 4 * sizeof(sPRVtx_Xyz_Diff_Tex1),
										0, 
										sPRVtx_Xyz_Diff_Tex1::FVF,
										D3DPOOL_MANAGED,	//	D3DPOOL_DEFAULT D3DPOOL_MANAGED
										&m_pVtxBuff,
										NULL	);
//	HRESULT	hr	=	pDev->CreateVertexBuffer(	4 * sizeof(sPRVtx_Xyz_Diff_Tex1),
//												0, 
//												sPRVtx_Xyz_Diff_Tex1::FVF,
//												D3DPOOL_MANAGED,	//	D3DPOOL_DEFAULT D3DPOOL_MANAGED
//												&m_pVtxBuff,
//												NULL	);
	PUT_IsFailed( hr )
	{
		PUT_ERROR;
		return E_FAIL;
	}

	sPRVtx_Xyz_Diff_Tex1	*pVertices = NULL;
	hr = m_pVtxBuff->Lock( 0, 0, (void**)&pVertices, 0 );
	PUT_IsFailed( hr )
	{
		PUT_ERROR;
		return E_FAIL;
	}

	float	fPosX = m_fWidth / 2.0f;
	float	fPosY = m_fHeight / 2.0f;

	D3DXVECTOR3 tmpVec;
	D3DCOLOR	tmpCol = 0xffffffff;
	float		fTU = 0.0f, fTV = 0.0f;

	tmpVec.x	=	-fPosX;
	tmpVec.y	=	fPosY;
	tmpVec.z	=	m_fPosZ;
	fTU	=	0.0f;
	fTV =	1.0f;

	SetVtxInfoXyzDiffTex1( &pVertices[0], tmpVec, tmpCol, fTU, fTV );

	tmpVec.x	=	-fPosX;
	tmpVec.y	=	-fPosY;
	tmpVec.z	=	m_fPosZ;
	fTU	=	0.0f;
	fTV	=	0.0f;
	SetVtxInfoXyzDiffTex1( &pVertices[1], tmpVec, tmpCol, fTU, fTV );


	tmpVec.x	=	fPosX;
	tmpVec.y	=	fPosY;
	tmpVec.z	=	m_fPosZ;
	fTU	=	1.0f;
	fTV	=	1.0f;
	SetVtxInfoXyzDiffTex1( &pVertices[2], tmpVec, tmpCol, fTU, fTV );


	tmpVec.x	=	fPosX;
	tmpVec.y	=	-fPosY;
	tmpVec.z	=	m_fPosZ;
	fTU	=	1.0f;
	fTV	=	0.0f;
	SetVtxInfoXyzDiffTex1( &pVertices[3], tmpVec, tmpCol, fTU, fTV );

	

	m_pVtxBuff->Unlock();

	return S_OK;

}//	InitVtxBuff
//-----------------------------------------------------------------------------------
HRESULT		CPRDShowImage::InitTextureBuff( PRLPD3DDEV9 pDev )
{
	HRESULT hr	=	S_OK;

	CComPtr<IBaseFilter>	pFSrc;			//	소스필터.
	CComPtr<IPin>			pFSrcPinOut;	//	소스필터 출력 핀.

	CPRDShowTexture			*pDShowTexture	=	NULL;

	hr = m_pGraphBuilder.CoCreateInstance( CLSID_FilterGraph, NULL, CLSCTX_INPROC );
	PUT_IsFailed( hr )
	{
		PUT_ERROR;
		return E_FAIL;
	}

#ifdef REGISTER_FILTERGRAPH
	AddToROT( m_pGraphBuilder );
#endif
	
	pDShowTexture = new CPRDShowTexture( NULL, &hr, this );
	if( FAILED( hr ) || !pDShowTexture )
	{
		PUT_ERROR;
		return E_FAIL;
	}

	m_pRenderer	=	pDShowTexture;
	hr = m_pGraphBuilder->AddFilter( m_pRenderer, L"TEXTURERENDERER" );
	PUT_IsFailed( hr )
	{
		PUT_ERROR;
		return hr;
	}

	WCHAR	wszPath[MAX_PATH]	=	{0};
	int		nLen	=	(int)strlen( m_szFPath );
//	mbstowcs_s( 0, wszPath, m_szFPath, nLen );
	mbstowcs( wszPath, m_szFPath, nLen );
	hr = m_pGraphBuilder->AddSourceFilter( wszPath, L"SOURCE", &pFSrc );

	PUT_IsFailed(hr)
	{
		switch( hr )
		{
		case E_NOINTERFACE:
			{
				PUT_ERROR;
				break;
			}

		case E_OUTOFMEMORY:
			{
				PUT_ERROR;
				break;
			}

		case E_POINTER:
			{
				PUT_ERROR;
				break;
			}

		case VFW_E_CANNOT_LOAD_SOURCE_FILTER:
			{
				PUT_ERROR;
				break;
			}

		case VFW_E_NOT_FOUND:
			{
				PUT_ERROR;
				break;
			}

		case VFW_E_UNKNOWN_FILE_TYPE:
			{
				PUT_ERROR;
				break;
			}

		}//	switch( hr )

		return hr;
		
	}//	PUT_IsFailed(hr)


	hr = pFSrc->FindPin( L"Output", &pFSrcPinOut );
	PUT_IsFailed( hr )
	{
		switch( hr )
		{
		case E_POINTER:
			PUT_ERROR;
			break;

		case VFW_E_NOT_FOUND:
			PUT_ERROR;
			break;
		}

		return hr;

	}//	PUT_IsFailed( hr )


#ifdef NO_AUDIO_RENDERER
	CComPtr<IPin>	pFTRPinIn;	//	텍스쳐 렌더러 입력핀.

	//	소스의 출력핀과 렌더러의 입력핀을 찾는다.
	hr = pDShowTexture->FindPin( L"In", &pFTRPinIn );
	PUT_IsFailed(hr)
	{
		PUT_ERROR;
		return hr;
	}

	//	두 필터 연결.
	hr = m_pGraphBuilder->Connect( pFSrcPinOut, pFTRPinIn );
	PUT_IsFailed(hr)
	{
		PUT_ERROR;
		return hr;
	}

#else	//	#ifdef NO_AUDIO_RENDERER

	hr = m_pGraphBuilder->Render( pFSrcPinOut );

	PUT_IsFailed(hr)
	{
		switch( hr )
		{
		case E_ABORT:
		case E_OUTOFMEMORY:
		case E_POINTER:
		case VFW_S_AUDIO_NOT_RENDERED:
		case VFW_S_DUPLICATE_NAME:
		case VFW_S_PARTIAL_RENDER:
		case VFW_S_VIDEO_NOT_RENDERED:		
		case VFW_E_CANNOT_CONNECT:
		case VFW_E_CANNOT_RENDER:
		case VFW_E_NO_ACCEPTABLE_TYPES:
		case VFW_E_NOT_IN_GRAPH:
			PUT_ERROR;
			return hr;
		}

	}//	PUT_IsFailed(hr)

#endif	//	~#ifdef NO_AUDIO_RENDERER

	m_pGraphBuilder->QueryInterface( &m_pMediaCtrl );
	m_pGraphBuilder->QueryInterface( &m_pMediaPos );
	m_pGraphBuilder->QueryInterface( &m_pMediaEvent );
	m_pMediaPos->put_CurrentPosition( 0 );

	hr = m_pMediaCtrl->Run();
	PUT_IsFailed( hr )
	{
		PUT_ERROR;
		return hr;
	}

	return S_OK;

}//	InitTextureBuff
//-----------------------------------------------------------------------------------
HRESULT		CPRDShowImage::OnRender( PRLPD3DDEV9 pDev, float fElapsedTime )
{
	PUT_IsInValid( pDev )
		return E_FAIL;

	PUT_IsInValid( IsVisible() )
		return E_FAIL;

	PUT_IsDiffer( GetPlayState(), ePLAYSTATE_PLAY )
		return E_FAIL;

	HRESULT hr = S_OK;

	// set maximum ambient light
	hr = devSetRSAMBIENT( pDev, RGB( 255, 255, 255 ) );

	// Turn off culling
	hr = devSetRSCullMode( pDev, D3DCULL_NONE );

	// Turn on the zbuffer
	hr = devSetRSZEnable( pDev, FALSE );

	hr = devSetAlphaBlend( pDev, eALPHABLENDTYPE_SA_DINVSA );
	hr = devSetAlphaTest( pDev, 0x08, D3DCMP_GREATEREQUAL );

	hr = devSetTxtr( pDev, 0, m_pTextureBuff );
	hr = devSetStreamSrc( pDev, 0, m_pVtxBuff, 0, sizeof(sPRVtx_Xyz_Diff_Tex1) );
	hr = devSetVtxShader( pDev, NULL );
	hr = devSetFVF( pDev, sPRVtx_Xyz_Diff_Tex1::FVF );
	hr = devDrawPrim( pDev, D3DPT_TRIANGLESTRIP, 0, 2 );

	PUT_IsInValid( CheckShowStatus() )
		return false;

	hr = devSetRSCullMode( pDev, D3DCULL_CCW );
	hr = devSetRSZEnable( pDev, TRUE );

	return hr;

}//	OnRender
//-----------------------------------------------------------------------------------
HRESULT		CPRDShowImage::OnResetDevice( PRLPD3DDEV9 pDev )
{
	return Init( pDev, m_szFPath, m_fWidth, m_fHeight );
}
//-----------------------------------------------------------------------------------
HRESULT		CPRDShowImage::OnLostDevice()
{
	ClearMembers();

	return S_OK;

}//	OnLostDevice
//-----------------------------------------------------------------------------------
HRESULT		CPRDShowImage::Init( PRLPD3DDEV9 pDev, char *pszFPath, float fWid, float fHei )
{
	HRESULT hr = E_FAIL;

	SetSize( fWid, fHei );

	hr = InitVtxBuff( pDev );

	PUT_IsFailed(hr)
	{
#ifndef _ENGCLI_VS2003_VS2008_
		strcpy_s( m_szFPath, sizeof( m_szFPath ), pszFPath );
#else
		PUT_Strcpy( m_szFPath, pszFPath );
#endif
		
		hr = InitTextureBuff( pDev );
	}

	m_nPlayCount = 1;

	return hr;

}//	Init
//-----------------------------------------------------------------------------------
HRESULT		CPRDShowImage::UpgradeGeom( long lActualW, long lTextureW, long lActualH, long lTextureH )
{
	HRESULT	hr	=	S_OK;

	if( lTextureW == 0 ||
		lTextureH == 0 )
	{
		PUT_ERROR;
		return E_INVALIDARG;
	}

	float	fUW	=	(float)lActualW / (float)lTextureW;
	float	fUH	=	(float)lActualH / (float)lTextureH;

	sPRVtx_Xyz_Diff_Tex1	*pVertices;
	hr = m_pVtxBuff->Lock( 0, 0, (void**)&pVertices, 0 );
	PUT_IsFailed( hr )
	{
		PUT_ERROR;
		return E_FAIL;
	}

	sPRVtx_Xyz_Diff_Tex1	*pV	=	pVertices;

	float	fWid	=	m_fWidth;
	float	fHei	=	m_fHeight;

	int		nSX		=	(int)(0.0f + 0.5f);	//	실수의 0.5f 오차를 줄인다.
	int		nSY		=	(int)(0.0f + 0.5f);
	int		nEX		=	(int)(0.0f + 0.5f);
	int		nEY		=	(int)(0.0f + 0.5f);

	float	fRatioSX	=	(float)nSX / fWid;
	float	fRatioSY	=	(float)nSY / fHei;
	float	fRatioEX	=	(float)nEX / fWid;
	float	fRatioEY	=	(float)nEY / fHei;

	float	fHalfW	=	fWid / 2.0f;
	float	fHalfH	=	fHei / 2.0f;


	D3DXVECTOR3 tmpVec;	
	D3DCOLOR	tmpCol = 0xffffffff;
	float fTu = 0.0f, fTv = 0.0f;

	tmpVec.x	=	-fHalfW + (float)nSX + 0.5f;
	tmpVec.y	=	-fHalfH + (float)nEX + 0.5f;
	tmpVec.z	=	m_fPosZ;
	fTu			=	0.0f + fRatioSX;
	fTv			=	0.0f - fRatioEY;	
	SetVtxInfoXyzDiffTex1( &pV[0], tmpVec, tmpCol, fTu, fTv );

	
	tmpVec.x	=	-fHalfW + (float)nSX + 0.5f;
	tmpVec.y	=	fHalfH - (float)nSY + 0.5f;
	tmpVec.z	=	m_fPosZ;
	fTu		=	0.0f + fRatioSX;
	fTv		=	1.0f + fRatioSY;
	SetVtxInfoXyzDiffTex1( &pV[1], tmpVec, tmpCol, fTu, fTv );


	tmpVec.x	=	fHalfW - (float)nEX + 0.5f;
	tmpVec.y	=	-fHalfH + (float)nEY + 0.5f;
	tmpVec.z	=	m_fPosZ;
	fTu			=	1.0f - fRatioEX;
	fTv			=	0.0f - fRatioEY;
	SetVtxInfoXyzDiffTex1( &pV[2], tmpVec, tmpCol, fTu, fTv );

	
	tmpVec.x	=	fHalfW - (float)nEX + 0.5f;
	tmpVec.y	=	fHalfH - (float)nSY + 0.5f;
	tmpVec.z	=	m_fPosZ;
	fTu		=	1.0f - fRatioEX;
	fTv		=	1.0f + fRatioSY;
	SetVtxInfoXyzDiffTex1( &pV[3], tmpVec, tmpCol, fTu, fTv );


	m_pVtxBuff->Unlock();

	return S_OK;

}//	UpgradeGeom
//-----------------------------------------------------------------------------------
void		CPRDShowImage::OnUpdate( PRLPD3DDEV9 pDev, float fElapsed )
{
	D3DXMATRIXA16	matWorld;

	PRDXMatInit( &matWorld );
	PRDXMatTranslation( &matWorld, m_fPosX, m_fPosY, m_fPosZ );
	devSetTrsformWorld( pDev, &matWorld );

}//	OnUpdate
//-----------------------------------------------------------------------------------
#ifdef REGISTER_FILTERGRAPH
HRESULT		CPRDShowImage::AddToROT(IUnknown *pUnkGraph )
{
	IMoniker			*pMk	= NULL;
	IRunningObjectTable	*pRot	= NULL;

	PUT_IsFailed( GetRunningObjectTable( 0, &pRot ) )
	{
		PUT_ERROR;
		return E_FAIL;
	}

	//	WCHAR	wsz[MAX_PATH] = {0};
	//	wsprintfW(wsz, L"FilterGraph %08x  pid %08x\0", (DWORD_PTR) 0, GetCurrentProcessId());
	char	wsz[MAX_PATH] = {0};
#ifndef _ENGCLI_VS2003_VS2008_
	sprintf_s(wsz, sizeof(wsz), "FilterGraph %08x  pid %08x\0", (DWORD_PTR) 0, GetCurrentProcessId());
#else
	PUT_Sprintf(wsz, "FilterGraph %08x  pid %08x\0", (DWORD_PTR) 0, GetCurrentProcessId());
#endif

	//	HRESULT	hr	=	CreateItemMoniker( L"!", wsz, &pmk );
	HRESULT	hr	=	CreateItemMoniker(  L"!",  (LPOLESTR)wsz, &pMk );

	PUT_IsSucceeded(hr)
	{
		hr = pRot->Register(	ROTFLAGS_REGISTRATIONKEEPSALIVE,
								pUnkGraph,
								pMk,
								&m_dwROTReg);
		pMk->Release();

	}//	PUT_IsSucceeded(hr)

	pRot->Release();

	return hr;	

}//	AddToROT
#endif	//	REGISTER_FILTERGRAPH
//-----------------------------------------------------------------------------------
void	CPRDShowImage::RemoveFromROT()
{
	IRunningObjectTable	*pRot	=	NULL;

	PUT_IsSucceeded( GetRunningObjectTable( 0, &pRot ) )
	{
		pRot->Revoke( m_dwROTReg );
		pRot->Release();
	}

}//	RemoveFromROT
//-----------------------------------------------------------------------------------
bool	CPRDShowImage::CheckShowStatus()
{
	long		lEventCode;
	LONG_PTR	lParam1, lParam2;
	HRESULT		hr;

	PUT_IsInValid( m_pMediaEvent )
	{
		PUT_ERROR;
		return false;
	}

	hr	=	m_pMediaEvent->GetEvent( &lEventCode, &lParam1, &lParam2, 0 );
	PUT_IsSucceeded( hr )
	{
		PUT_IsSame( lEventCode, EC_COMPLETE )
		{
			if( m_nPlayCount < m_nPlayMaxCount )
			{
				hr = m_pMediaPos->put_CurrentPosition(0);				
				SetPlayState( ePLAYSTATE_PLAY );
				++m_nPlayCount;

			}else//	if( m_nPlayCount < m_nPlayMaxCount )
			{
				SetPlayState( ePLAYSTATE_STOP );

			}//	~if( m_nPlayCount < m_nPlayMaxCount )

			//	해당 이벤트와 관련된 메모리들을 소거한다.
			hr = m_pMediaEvent->FreeEventParams( lEventCode, lParam1, lParam2 );
			return true;

		}else//	PUT_IsSame( lEventCode, EC_COMPLETE )
		{
			SetPlayState( ePLAYSTATE_PLAY );
			hr = m_pMediaEvent->FreeEventParams( lEventCode, lParam1, lParam2 );

		}//	~PUT_IsSame( lEventCode, EC_COMPLETE )

	}//	PUT_IsSucceeded( hr )

	return true;

}//	CheckShowStatus
//-----------------------------------------------------------------------------------
HRESULT		CPRDShowImage::Play()
{
	m_nPlayCount	=	1;
	SetPlayState( ePLAYSTATE_PLAY );
	m_pMediaPos->put_CurrentPosition(0);
	return S_OK;

}//	Play
//-----------------------------------------------------------------------------------
HRESULT		CPRDShowImage::Stop()
{
	SetPlayState( ePLAYSTATE_STOP );
	return S_OK;

}//	Stop
//-----------------------------------------------------------------------------------
HRESULT		CPRDShowImage::Pause()
{
	SetPlayState( ePLAYSTATE_PAUSE );
	return S_OK;

}//	Pause
//-----------------------------------------------------------------------------------