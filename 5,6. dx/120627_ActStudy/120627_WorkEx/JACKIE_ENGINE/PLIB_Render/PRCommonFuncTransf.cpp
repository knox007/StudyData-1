#include "stdafx.h"
#include "PRCommonFunc.h"



//--------------------------------------------------------------------------------
HRESULT	devSetTrsform( PRLPD3DDEV9 pDev, D3DTRANSFORMSTATETYPE eType, D3DMATRIX* pMat )
{
	return pDev->SetTransform( eType, pMat );

}//	devSetTrsform
//--------------------------------------------------------------------------------
HRESULT	devSetTrsformWorld( PRLPD3DDEV9 pDev, D3DMATRIX* pMat )
{
	return devSetTrsform( pDev, D3DTS_WORLD, pMat );	

}//	devSetTrsformWorld
//--------------------------------------------------------------------------------
HRESULT	devSetTrsformView( PRLPD3DDEV9 pDev, D3DMATRIX* pMat )
{
	return devSetTrsform( pDev, D3DTS_VIEW, pMat );

}//	devSetTrsformView
//--------------------------------------------------------------------------------
HRESULT	devSetTrsformProjection( PRLPD3DDEV9 pDev, D3DMATRIX* pMat )
{
	return devSetTrsform( pDev, D3DTS_PROJECTION, pMat );

}//	devSetTrsformProjection
//--------------------------------------------------------------------------------
//	EOF