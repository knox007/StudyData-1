#include "stdafx.h"
#include "PRCommonFunc.h"
#include "PRCommonVtxInfo.h"
#include "PUTCommon.h"
#include "PUtCommonStr.h"


//--------------------------------------------------------------------------------
HRESULT	devClr(	PRLPD3DDEV9 pDev,
				DWORD	dwClrRectCnt,	D3DRECT*	prtClearArr, 
				DWORD	dwClrFlag,		D3DCOLOR	colBackScr,	
				float	fZ,				DWORD		dwStencil )
{
	return pDev->Clear( dwClrRectCnt, prtClearArr, dwClrFlag, colBackScr, fZ, dwStencil );

}//	devClear
//--------------------------------------------------------------------------------
HRESULT	devBeginScene( PRLPD3DDEV9 pDev )	
{ 
	return pDev->BeginScene();

}//	devBeginScene
//--------------------------------------------------------------------------------
HRESULT devEndScene( PRLPD3DDEV9 pDev )	
{ 
	return pDev->EndScene(); 

}//	devEndScene
//--------------------------------------------------------------------------------
HRESULT devPresent(	PRLPD3DDEV9 pDev, 
					RECT* pSourceRect,			RECT* pDestRect, 
					HWND hDestWindowOverride,	RGNDATA* pDirtyRegion )
{
	return pDev->Present( pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion );

}//	devPresent
//--------------------------------------------------------------------------------
HRESULT	devDrawPrim(	PRLPD3DDEV9 pDev, 
					D3DPRIMITIVETYPE PrimitiveType,
					UINT StartVertex,
					UINT PrimitiveCount)
{
	return pDev->DrawPrimitive( PrimitiveType, StartVertex, PrimitiveCount );

}//	devDrawP
//--------------------------------------------------------------------------------
HRESULT	devDrawIdxPrim(	PRLPD3DDEV9 pDev, 
						D3DPRIMITIVETYPE PrimitiveType,
						int BaseVertexIndex,
						UINT MinVertexIndex,
						UINT NumVertices,
						UINT startIndex,
						UINT primCount)
{
	return pDev->DrawIndexedPrimitive( PrimitiveType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount );

}//	devDrawIdxP
//--------------------------------------------------------------------------------

HRESULT	devDrawPUP(	PRLPD3DDEV9 pDev, 
				   D3DPRIMITIVETYPE eType, 
				   UINT unPrimitiveCount, 
				   const void* pVertexStreamZeroData, 
				   UINT unVertexStreamZeroStride )
{
	return pDev->DrawPrimitiveUP( eType, unPrimitiveCount, pVertexStreamZeroData, unVertexStreamZeroStride );

}//	devDrawPUP
//--------------------------------------------------------------------------------
void	devDrawLIneUP(	PRLPD3DDEV9 pDev, 
						D3DXVECTOR3 &vecStart, 
						D3DXVECTOR3	&vecEnd, 
						D3DCOLOR colStart,
						D3DCOLOR colEnd )
{
	sPRVtx_Xyz_Diff Vtx[2];
	PUT_ZERO_MEMORY( Vtx );
	SetVtxInfoXyzDiff( &Vtx[0], vecStart, colStart );
	SetVtxInfoXyzDiff( &Vtx[1], vecEnd, colEnd );	

	PRDXMat	matWorld;
	D3DXMatrixIdentity( &matWorld );	
	devSetTrsformWorld( pDev, &matWorld );

	devSetRSLightEnable( pDev, FALSE );
	devSetTxtr( pDev, 0, NULL );	
	devSetFVF( pDev, sPRVtx_Xyz_Diff::FVF );		
	devDrawPUP( pDev, D3DPT_LINELIST, 1, Vtx, sizeof(sPRVtx_Xyz_Diff) );
	devSetRSLightEnable( pDev, TRUE );
	
}//	devDrawLIne
//--------------------------------------------------------------------------------
void	devDrawPt(	PRLPD3DDEV9 pDev,
					D3DXVECTOR3 &vec,
					D3DCOLOR col )
{
	sPRVtx_Xyz_Diff Vtx;
	PUT_ZERO_MEMORY( Vtx );
	SetVtxInfoXyzDiff( &Vtx, vec, col );
	
	PRDXMat matWorld;
	D3DXMatrixIdentity( &matWorld );	
	devSetTrsformWorld( pDev, &matWorld );

	devSetRSLightEnable( pDev, FALSE );
	devSetTxtr( pDev, 0, NULL );
	devSetFVF( pDev, sPRVtx_Xyz_Diff::FVF );		
	devDrawPUP( pDev, D3DPT_POINTLIST, 1, &Vtx, sizeof(sPRVtx_Xyz_Diff) );
	devSetRSLightEnable( pDev, TRUE );

}//	devDrawPt
//--------------------------------------------------------------------------------
//	EOF