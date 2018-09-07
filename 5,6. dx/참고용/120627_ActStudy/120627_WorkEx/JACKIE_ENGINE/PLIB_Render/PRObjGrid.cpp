#include "StdAfx.h"
#include "PRObjGrid.h"
#include "PUtCommon.h"
#include "PRCommonFunc.h"
#include "PRCommonVtxInfo.h"


void	CPRObjGrid::InitMembers()
{
	m_VertBuff	=	0;
	m_IdxBuff	=	0;	

	m_nSize		=	0;
	PUT_True( m_bVisible );

	SetColorEdge( 0xffff0000 );
	SetColorInner( 0xff979797 );

}//	InitMembers
//----------------------------------------------------------------------------------------------------
void	CPRObjGrid::InitMembers(	D3DXVECTOR3 vPos, 
									int nSize,
									D3DCOLOR	colEdge,
									D3DCOLOR	colInner )
{
	InitMembers();

	SetPos( vPos );
	SetSize( nSize );
	SetColorEdge( colEdge );
	SetColorInner( colInner );

}//	InitMembers( int nSize, D3DXVECTOR3 vPos )
//----------------------------------------------------------------------------------------------------
void	CPRObjGrid::ClearMembers()
{
	PUT_SAFE_RELEASE( m_VertBuff ); 
	PUT_SAFE_RELEASE( m_IdxBuff ); 

}//	ClearMembers
//----------------------------------------------------------------------------------------------------
void	CPRObjGrid::OnReset( PRLPD3DDEV9 pDev )
{
	//!	버텍스 버퍼 초기화.
	if( FAILED( devCreateVtxBuff(	pDev,
									sizeof(sPRVtx_Xyz_Diff) * m_nSize * 4,
									0,
									sPRVtx_Xyz_Diff::FVF,
									D3DPOOL_MANAGED,	// D3DPOOL_MANAGED D3DPOOL_DEFAULT
									&m_VertBuff,
									NULL ) ) )
									return;



	sPRVtx_Xyz_Diff	*pVert;
	if( FAILED( m_VertBuff->Lock( 0, 0, (void**)&pVert, 0 ) ) )
		return;



	//! 가로
	for( int nCur = 0; nCur < m_nSize; ++nCur )
	{
		float fPos = float( nCur - ( m_nSize / 2 ) );

		D3DCOLOR dwCol = (fPos == 0 || nCur == 0 || nCur == m_nSize - 1 ) ? GetColorEdge() : GetColorInner();

		if( nCur != 0 && nCur % 2 == 0 && nCur != m_nSize - 1 )
			dwCol = PRCOLOR_GREEN( 120 );

		SetVtxInfoXyzDiff( 
							&pVert[nCur+0+(nCur * 1)],
							D3DXVECTOR3( fPos, 0.0f, float(-(m_nSize/2) ) ),
							dwCol);

		SetVtxInfoXyzDiff( 
							&pVert[nCur+1+(nCur * 1)],
							D3DXVECTOR3( fPos, 0.0f, float( (m_nSize/2) ) ),
							dwCol);
	}

	
	//!	세로
	for( int nCur = m_nSize; nCur < m_nSize*2; ++nCur )
	{
		float fPos = float( (nCur-m_nSize) - (m_nSize/2) );

		D3DCOLOR dwCol = (fPos == 0 || nCur == m_nSize || nCur == m_nSize*2 - 1 ) ? GetColorEdge() : GetColorInner();

		if( nCur != 0 && nCur % 2 == 0 )
			dwCol = PRCOLOR_GREEN( 120 );

		SetVtxInfoXyzDiff( 
			&pVert[nCur+0+(nCur * 1)],
			D3DXVECTOR3( float(-(m_nSize/2) ), 0.0f, fPos ),
			dwCol );

		SetVtxInfoXyzDiff( 
			&pVert[nCur+1+(nCur * 1)],
			D3DXVECTOR3( float( (m_nSize/2) ), 0.0f, fPos ),
			dwCol );
	}




	m_VertBuff->Unlock();



	//!	인덱스 버퍼 초기화.
	if( FAILED( devCreateIdxBuff(	pDev,
									sizeof( sPRINDEX16_2D ) * m_nSize * 2,
									0,
									D3DFMT_INDEX16,
									D3DPOOL_MANAGED,	// D3DPOOL_MANAGED D3DPOOL_DEFAULT
									&m_IdxBuff,
									NULL ) ) )
									return;

	sPRINDEX16_2D	*pIDx;
	if( FAILED( m_IdxBuff->Lock( 0, 0, (void**)&pIDx, 0 ) ) )
		return;

	for( int nCur = 0; nCur < m_nSize*2; ++nCur )
		PRSetIdx2D( pIDx[nCur], 
					 nCur + 0 + (nCur*1), 
					 nCur + 1 + (nCur*1) 
					);

	m_IdxBuff->Unlock();
 
}//	Reset
//----------------------------------------------------------------------------------------------------
void	CPRObjGrid::OnLost()
{
	ClearMembers();

}//	Lost
//----------------------------------------------------------------------------------------------------
HRESULT	CPRObjGrid::OnRender( PRLPD3DDEV9 pDev, float fElapsedTime  )
{
	if( !m_VertBuff || !m_IdxBuff || !m_bVisible )
		return E_FAIL;

	D3DXMATRIX	matWorld;
	matWorld = m_matWorld;
	D3DXMatrixTranslation( &matWorld, m_vecPos.x, m_vecPos.y, m_vecPos.z );	
	devSetTrsformWorld( pDev, &matWorld );
		
	devSetRS( pDev, D3DRS_LIGHTING, FALSE );
	devSetTxtr( pDev, 0, NULL );
	devSetStreamSrc( pDev, 0, m_VertBuff, 0, sizeof(sPRVtx_Xyz_Diff) );	
	devSetFVF( pDev, sPRVtx_Xyz_Diff::FVF );
	devSetIdx( pDev, m_IdxBuff );
	devDrawIdxPrim( pDev, D3DPT_LINELIST, 0, 0, m_nSize * 4 + 2, 0, m_nSize * 2 );
	devSetRS( pDev, D3DRS_LIGHTING, TRUE );
	
	//	X축
	devDrawLIneUP( pDev, D3DXVECTOR3((float)m_nSize, 0, 0), D3DXVECTOR3(-(float)m_nSize, 0, 0),		PRCOLOR_RED(255),	PRCOLOR_RED(255) );
	devDrawLIneUP( pDev, D3DXVECTOR3((float)m_nSize, 0, 2), D3DXVECTOR3( (float)m_nSize, 0, -2),	PRCOLOR_RED(255),	PRCOLOR_RED(255) );
	
	//	Z축
	devDrawLIneUP( pDev, D3DXVECTOR3(0, 0, -(float)m_nSize), D3DXVECTOR3(0, 0, (float)m_nSize),		PRCOLOR_BLUE(255),	PRCOLOR_BLUE(255) );
	devDrawLIneUP( pDev, D3DXVECTOR3(2, 0, (float)m_nSize), D3DXVECTOR3(-2, 0, (float)m_nSize),		PRCOLOR_BLUE(255),	PRCOLOR_BLUE(255) );

	//	Y축
	devDrawLIneUP( pDev, D3DXVECTOR3(0, (float)m_nSize, 0), D3DXVECTOR3(0, -(float)m_nSize, 0),		PRCOLOR_GREEN(255), PRCOLOR_GREEN(255) );
	devDrawLIneUP( pDev, D3DXVECTOR3(2, (float)m_nSize, 0), D3DXVECTOR3(-2, (float)m_nSize, 0),		PRCOLOR_GREEN(255), PRCOLOR_GREEN(255) );

	return S_OK;

}//	OnRender
//----------------------------------------------------------------------------------------------------
//	EOF