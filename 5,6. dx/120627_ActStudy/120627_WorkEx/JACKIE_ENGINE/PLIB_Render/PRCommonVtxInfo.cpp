#include "stdafx.h"
#include "PRCommonVtxInfo.h"


//------------------------
//	Fixed Vertex Format 
//------------------------
//	------------------------------------------------------------------------------
void	SetVtxInfoXyz( sPRVtx_Xyz* pVtx, D3DXVECTOR3 vecPos )
{		
	pVtx->_fX = vecPos.x;
	pVtx->_fY = vecPos.y;
	pVtx->_fZ = vecPos.z;

}//	SetVtxInfoXyz
//	------------------------------------------------------------------------------
void	SetVtxInfoXyzTex1( sPRVtx_Xyz_Tex1* pVtx, D3DXVECTOR3 vecPos, float fTu, float fTv )
{
	pVtx->_fX = vecPos.x;
	pVtx->_fY = vecPos.y;
	pVtx->_fZ = vecPos.z;
	pVtx->_fTu = fTu;
	pVtx->_fTv = fTv;
}
//----------------------------------------------------------------------------------------
void	SetVtxInfoXyzDiff(sPRVtx_Xyz_Diff* pVtx, D3DXVECTOR3 p, D3DCOLOR clr)
{	
	SetVtxInfoXyz( pVtx, p );
	pVtx->_dxColor	=	clr;

}//	SetVtxInfoXyzDiff
//	------------------------------------------------------------------------------
void	SetVtxInfoXyzDiffTex1( sPRVtx_Xyz_Diff_Tex1* pVtx, D3DXVECTOR3 vecPos, D3DCOLOR dxColor, float fTu, float fTv )
{
	SetVtxInfoXyzDiff( pVtx, vecPos, dxColor );
	pVtx->_fTu		=	fTu;
	pVtx->_fTv		=	fTv;

}//	SetVtxInfoXyzDiffTex1
//	------------------------------------------------------------------------------
void	SetVtxInfoXyzDiffPtSize(sPRVtx_Xyz_Diff_PtSize* pVtx, D3DXVECTOR3 p, D3DCOLOR clr, float fPSize )
{
	SetVtxInfoXyzDiff( pVtx, p, clr );	
	pVtx->_fPSize		=	fPSize;

}//	SetVtxInfoXyzDiffPtSize
//	------------------------------------------------------------------------------
void	SetVtxInfoXyzNorm(sPRVtx_Xyz_Norm* pVtx, D3DXVECTOR3 vecPos, D3DXVECTOR3 vecNorm )
{
	SetVtxInfoXyz( pVtx, vecPos );
	
	pVtx->_fNormX	=	vecNorm.x;
	pVtx->_fNormY	=	vecNorm.y;
	pVtx->_fNormZ	=	vecNorm.z;	

}//	SetVtxInfoXyzNorm
//	------------------------------------------------------------------------------
void	SetVtxInfoXyzNormDiff( sPRVtx_Xyz_Norm_Diff* pVtx, D3DXVECTOR3 vecPos, D3DXVECTOR3 vecNorm, D3DCOLOR dxColor )
{
	SetVtxInfoXyzNorm( pVtx, vecPos, vecNorm );

	pVtx->_dxColor	=	dxColor;	

}//	SetVtxInfoXyzDiffNorm
//----------------------------------------------------------------------------------------
void	SetVtxInfoXyzNormTex1(sPRVtx_Xyz_Norm_Tex1* pVtx, D3DXVECTOR3 p, D3DXVECTOR3 nor, float fTu, float fTv )
{
	SetVtxInfoXyzNorm( pVtx, p, nor );

	pVtx->_fTu = fTu;
	pVtx->_fTv = fTv;

}//	SetVtxInfoXyzNormTex1
//--------------------------------------------------------------------------------
void	SetVtxInfoXyzNormDiffTex1(sPRVtx_Xyz_Norm_Diff_Tex1* pVtx, D3DXVECTOR3 p, D3DXVECTOR3 nor, float fTu, float fTv, D3DCOLOR dxColor )
{
	SetVtxInfoXyzNormDiff( pVtx, p, nor, dxColor);

	pVtx->_fTu	=	fTu;
	pVtx->_fTv	=	fTv;

}//	SetVtxInfoXyzNormTex1
//----------------------------------------------------------------------------------------
void	SetVtxInfoXyzrhw( sPRVtx_XyzRhw* pVtx, D3DXVECTOR4 vecPos )
{
	pVtx->_fX		= vecPos.x;
	pVtx->_fY		= vecPos.y;
	pVtx->_fZ		= vecPos.z;
	pVtx->_fRhw	= vecPos.w;

}//	SetVtxInfoXyzrhw
//	------------------------------------------------------------------------------
void	SetVtxInfoXyzrhwDiff( sPRVtx_XyzRhw_Diff* pVtx, D3DXVECTOR4 vecPos, D3DCOLOR dxColor )
{
	SetVtxInfoXyzrhw( pVtx, vecPos );
	pVtx->_dxColor	=	dxColor;

}//	SetVtxInfoXyzrhwDiff
//	------------------------------------------------------------------------------
void	SetVtxInfoXyzrhwDiffTex1( sPRVtx_Xyzrhw_Diff_Tex1* pVtx, D3DXVECTOR4 vecPos, D3DCOLOR dxColor, float fTu, float fTv )
{	
	pVtx->_fX		= vecPos.x;
	pVtx->_fY		= vecPos.y;
	pVtx->_fZ		= vecPos.z;
	pVtx->_fRhw		= vecPos.w;

	pVtx->_dxColor	= dxColor;
	
	pVtx->_fTu		=	fTu;
	pVtx->_fTv		=	fTv;

}//	SetVtxInfoXyzrhwDiffTex1
//	------------------------------------------------------------------------------
void	PRSetIdx3D(sPRINDEX16 &ci, WORD _0, WORD _1, WORD _2)
{	
	ci._wA	=	_0;
	ci._wB	=	_1;
	ci._wC	=	_2;

}//	PRSetIdx3D
//--------------------------------------------------------------------------------
void	PRSetIdx2D(sPRINDEX16_2D &ci, WORD _0, WORD _1)
{
	ci._wA	=	_0;
	ci._wB	=	_1;

}//	PRSetIdx2D
//--------------------------------------------------------------------------------