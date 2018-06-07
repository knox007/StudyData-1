#include "stdafx.h"
#include "PRAseGeom.h"
#include "PRCommonFunc.h"
#include "PUtCommonStr.h"

//----------------------------------------------------------------------------------------
void	CPRAseGeom::InitMembers()
{
	PUT_ZERO_MEMORY( *this );
	
	m_nMtrlRef = -1;

}//	InitMembers
//----------------------------------------------------------------------------------------
void	CPRAseGeom::ClearMembers()
{
	PUT_SAFE_DELETE_ARRAY( m_pVtxXyzArr )		
	PUT_SAFE_DELETE_ARRAY( m_pVtxNormArr )
	PUT_SAFE_DELETE_ARRAY( m_pTVtxArr )

	PUT_SAFE_DELETE_ARRAY( m_pIDxArr )
	PUT_SAFE_DELETE_ARRAY( m_pTIDxArr )

	PUT_SAFE_RELEASE( m_pBuffVtx )
	PUT_SAFE_RELEASE( m_pBuffIdx )

}//	ClearMembers
//----------------------------------------------------------------------------------------
bool	CPRAseGeom::CreateVtx( LPDIRECT3DDEVICE9 pDev )
{
	HRESULT hr = S_OK;
	bool bRes = true;

	//switch( GetFVF() )
	//{
	//case sPRVtx_Xyz::FVF:
	//	m_unVtxStructSize = sizeof( sPRVtx_Xyz_Diff );
	//	bRes = CreateVtx( pDev );
	//	break;

	//case sPRVtx_Xyz_Norm::FVF:
	//	m_unVtxStructSize = sizeof( sPRVtx_Xyz_Norm);
	//	bRes = CreateVtxNorm( pDev );
	//	break;

	//case sPRVtx_Xyz_Norm_Tex1::FVF:
	//	m_unVtxStructSize = sizeof( sPRVtx_Xyz_Norm_Tex1 );
	//	bRes = CreateVtxNormTex1( pDev );
	//	break;	
	//}

	
	switch( GetFVF() )
	{
	case sPRVtx_Xyz_Diff::FVF:
		m_unVtxStructSize = sizeof( sPRVtx_Xyz_Diff );
		bRes = CreateVtxDiff( pDev );
		break;

	case sPRVtx_Xyz_Norm_Diff::FVF:
		m_unVtxStructSize = sizeof( sPRVtx_Xyz_Norm_Diff );
		bRes = CreateVtxNormDiff( pDev );
		break;

	case sPRVtx_Xyz_Norm_Diff_Tex1::FVF:
		m_unVtxStructSize = sizeof( sPRVtx_Xyz_Norm_Diff_Tex1 );
		bRes = CreateVtxNormDiffTex1( pDev );
		break;	
	}

	return bRes;	

}//	CreateVtx
//----------------------------------------------------------------------------------------
bool	CPRAseGeom::CreateVtxDiff( LPDIRECT3DDEVICE9 pDev )
{
	HRESULT hr = S_OK;

	hr = pDev->CreateVertexBuffer(	m_nTotVtx * m_unVtxStructSize,
		D3DUSAGE_WRITEONLY,
		sPRVtx_Xyz_Diff::FVF,
		D3DPOOL_MANAGED,
		&m_pBuffVtx,
		NULL );

	if( FAILED(hr) )
		return false;


	sPRVtx_Xyz_Diff* pVertices = NULL;
	hr = m_pBuffVtx->Lock( 0, 0, (void**)&pVertices, 0 );
	if( FAILED(hr) )
		return false;

	m_nActTotVtx	=	m_nTotVtx;

	for( int nCur = 0; nCur < m_nActTotVtx; ++nCur )
	{
		pVertices[nCur]._fX			=	m_pVtxXyzArr[nCur]._fX;
		pVertices[nCur]._fY			=	m_pVtxXyzArr[nCur]._fY;
		pVertices[nCur]._fZ			=	m_pVtxXyzArr[nCur]._fZ;

		if( !PUT_StrNiCmp( GetNodeName(), PUT_CSTR_TCHAR("Bip") ) )
			pVertices[nCur]._dxColor	=	D3DCOLOR_XRGB(220, 50, 0);
		else
			pVertices[nCur]._dxColor	=	D3DCOLOR_XRGB(0, 0, 250);
	}

	m_pBuffVtx->Unlock();

	return true;

}//	CreateVtxDiff
//----------------------------------------------------------------------------------------
bool	CPRAseGeom::CreateVtxNorm( LPDIRECT3DDEVICE9 pDev )
{
	HRESULT hr = S_OK;

	hr = pDev->CreateVertexBuffer(	m_nTotVtx * m_unVtxStructSize,
		D3DUSAGE_WRITEONLY,
		sPRVtx_Xyz_Norm::FVF,
		D3DPOOL_MANAGED,
		&m_pBuffVtx,
		NULL );

	if( FAILED(hr) )
		return false;


	sPRVtx_Xyz_Norm* pVertices = NULL;
	hr = m_pBuffVtx->Lock( 0, 0, (void**)&pVertices, 0 );
	if( FAILED(hr) )
		return false;

	m_nActTotVtx	=	m_nTotVtx;

	for( int nCur = 0; nCur < m_nActTotVtx; ++nCur )
	{
		pVertices[nCur]._fX			=	m_pVtxXyzArr[nCur]._fX;
		pVertices[nCur]._fY			=	m_pVtxXyzArr[nCur]._fY;
		pVertices[nCur]._fZ			=	m_pVtxXyzArr[nCur]._fZ;

		pVertices[nCur]._fNormX		=	m_pVtxNormArr[nCur]._fX;
		pVertices[nCur]._fNormY		=	m_pVtxNormArr[nCur]._fY;
		pVertices[nCur]._fNormZ		=	m_pVtxNormArr[nCur]._fZ;
	}

	m_pBuffVtx->Unlock();

	return true;

}//	CreateVtxNorm
//----------------------------------------------------------------------------------------
bool	CPRAseGeom::CreateVtxNormDiff( LPDIRECT3DDEVICE9 pDev )
{
	HRESULT hr = S_OK;

	hr = pDev->CreateVertexBuffer(	m_nTotVtx * m_unVtxStructSize,
		D3DUSAGE_WRITEONLY,
		sPRVtx_Xyz_Norm_Diff::FVF,
		D3DPOOL_MANAGED,
		&m_pBuffVtx,
		NULL );

	if( FAILED(hr) )
		return false;


	sPRVtx_Xyz_Norm_Diff* pVertices = NULL;
	hr = m_pBuffVtx->Lock( 0, 0, (void**)&pVertices, 0 );
	if( FAILED(hr) )
		return false;

	m_nActTotVtx	=	m_nTotVtx;

	for( int nCur = 0; nCur < m_nActTotVtx; ++nCur )
	{
		pVertices[nCur]._fX			=	m_pVtxXyzArr[nCur]._fX;
		pVertices[nCur]._fY			=	m_pVtxXyzArr[nCur]._fY;
		pVertices[nCur]._fZ			=	m_pVtxXyzArr[nCur]._fZ;

		pVertices[nCur]._fNormX		=	m_pVtxNormArr[nCur]._fX;
		pVertices[nCur]._fNormY		=	m_pVtxNormArr[nCur]._fY;
		pVertices[nCur]._fNormZ		=	m_pVtxNormArr[nCur]._fZ;

		pVertices[nCur]._dxColor	=	PRCOLOR_RED( 120 );
	}

	m_pBuffVtx->Unlock();

	return true;

}//	CreateVtxNormDiff
//----------------------------------------------------------------------------------------
bool	CPRAseGeom::CreateVtxNormTex1( LPDIRECT3DDEVICE9 pDev )
{
	HRESULT hr = S_OK;

	hr = pDev->CreateVertexBuffer(	m_nTotTVtx * m_unVtxStructSize,
		D3DUSAGE_WRITEONLY,
		sPRVtx_Xyz_Norm_Tex1::FVF,
		D3DPOOL_MANAGED,
		&m_pBuffVtx,
		NULL );

	if( FAILED(hr) )
		return false;

	sPRVtx_Xyz_Norm_Tex1* pVertices = NULL;
	hr = m_pBuffVtx->Lock( 0, 0, (void**)&pVertices, 0 );
	if( FAILED(hr) )
		return false;

	m_nActTotVtx	=	m_nTotTVtx;

	for( int nCur = 0; nCur < m_nActTotVtx; ++nCur )
	{
		int nVt = m_pTVtxArr[nCur]._nVtxIdx;

		pVertices[nCur]._fX			=	m_pVtxXyzArr[nVt]._fX;
		pVertices[nCur]._fY			=	m_pVtxXyzArr[nVt]._fY;
		pVertices[nCur]._fZ			=	m_pVtxXyzArr[nVt]._fZ;

		pVertices[nCur]._fNormX		=	m_pVtxNormArr[nVt]._fX;
		pVertices[nCur]._fNormY		=	m_pVtxNormArr[nVt]._fY;
		pVertices[nCur]._fNormZ		=	m_pVtxNormArr[nVt]._fZ;

		pVertices[nCur]._fTu		=	m_pTVtxArr[nCur]._fU;
		pVertices[nCur]._fTv		=	m_pTVtxArr[nCur]._fV;
	}

	m_pBuffVtx->Unlock();

	return true;

}//	CreateVtxNormTex1
//----------------------------------------------------------------------------------------
bool	CPRAseGeom::CreateVtxNormDiffTex1( LPDIRECT3DDEVICE9 pDev )
{
	HRESULT hr = S_OK;

	hr = pDev->CreateVertexBuffer(	m_nTotTVtx * m_unVtxStructSize,
		D3DUSAGE_WRITEONLY,
		sPRVtx_Xyz_Norm_Diff_Tex1::FVF,
		D3DPOOL_MANAGED,
		&m_pBuffVtx,
		NULL );

	if( FAILED(hr) )
		return false;


	sPRVtx_Xyz_Norm_Diff_Tex1* pVertices = NULL;
	hr = m_pBuffVtx->Lock( 0, 0, (void**)&pVertices, 0 );
	if( FAILED(hr) )
		return false;

	m_nActTotVtx	= m_nTotTVtx;

	for( int nCur = 0; nCur < m_nActTotVtx; ++nCur )
	{
		int nVt	=	m_pTVtxArr[nCur]._nVtxIdx;

		pVertices[nCur]._fX			=	m_pVtxXyzArr[nVt]._fX;
		pVertices[nCur]._fY			=	m_pVtxXyzArr[nVt]._fY;
		pVertices[nCur]._fZ			=	m_pVtxXyzArr[nVt]._fZ;

		pVertices[nCur]._fNormX		=	m_pVtxNormArr[nVt]._fX;
		pVertices[nCur]._fNormY		=	m_pVtxNormArr[nVt]._fY;
		pVertices[nCur]._fNormZ		=	m_pVtxNormArr[nVt]._fZ;

		pVertices[nCur]._fTu		=	m_pTVtxArr[nCur]._fU;
		pVertices[nCur]._fTv		=	m_pTVtxArr[nCur]._fV;
		
		pVertices[nCur]._dxColor	=	PRCOLOR_NOCOLOR;

		TCHAR	tszTmp[MAX_PATH] = {0,};

		PUTOutputDebugStr(
			"%s, %f, %f, %f   , %f, %f, %f   , %f, %f\n",
			GetNodeName(),
			pVertices[nCur]._fX,
			pVertices[nCur]._fY,
			pVertices[nCur]._fZ,
			
			pVertices[nCur]._fNormX,
			pVertices[nCur]._fNormY,
			pVertices[nCur]._fNormZ,
			
			pVertices[nCur]._fTu,
			pVertices[nCur]._fTv);
	}

	m_pBuffVtx->Unlock();


	return true;
}//	CreateVtxNormDiffTex1
//----------------------------------------------------------------------------------------
bool	CPRAseGeom::CreateIdx( LPDIRECT3DDEVICE9 pDev )
{
	HRESULT hr = S_OK;

	hr = pDev->CreateIndexBuffer(	m_nTotIdx * sizeof( sPRINDEX16 ),
									D3DUSAGE_WRITEONLY,
									D3DFMT_INDEX16,
									D3DPOOL_MANAGED,
									&m_pBuffIdx,
									NULL );
	if( FAILED(hr) )
		return false;

	sPRINDEX16* pIndices = NULL;
	hr = m_pBuffIdx->Lock( 0, 0, (void**)&pIndices, 0 );
	if( FAILED(hr) )
		return false;


	if( ( GetFVF() & D3DFVF_TEX1 ) == D3DFVF_TEX1 )
	{
		m_nActTotIdx = m_nTotTIDx;

		for( int nCur = 0; nCur < m_nTotTIDx; ++nCur )
		{
			pIndices[nCur]._wA	=	m_pTIDxArr[nCur]._wA;
			pIndices[nCur]._wB	=	m_pTIDxArr[nCur]._wB;
			pIndices[nCur]._wC	=	m_pTIDxArr[nCur]._wC;
		}
	}else
	{
		m_nActTotIdx = m_nTotIdx;

		for( int nCur = 0; nCur < m_nTotIdx; ++nCur )
		{
			pIndices[nCur]._wA	=	m_pIDxArr[nCur]._wA;
			pIndices[nCur]._wB	=	m_pIDxArr[nCur]._wB;
			pIndices[nCur]._wC	=	m_pIDxArr[nCur]._wC;
		}
	}

	
	m_pBuffIdx->Unlock();

	return true;

}//	CreateIdx
//----------------------------------------------------------------------------------------
bool	CPRAseGeom::OnRender( LPDIRECT3DDEVICE9 pDev, float fElapsedTime )
{
	devSetStreamSrc(	pDev, 
						0, 
						m_pBuffVtx, 
						0, 
						m_unVtxStructSize );

	devSetIdx(	pDev, 
				m_pBuffIdx );


	devDrawIdxPrim( pDev,
					D3DPT_TRIANGLELIST, 
					0, 
					0, 
					m_nActTotVtx,
					0, 
					m_nActTotIdx );

	return true;

}//	OnRender
//----------------------------------------------------------------------------------------