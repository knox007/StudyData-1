#include "stdafx.h"
#include "PRCommonFunc.h"



//--------------------------------------------------------------------------------
HRESULT	devSetRS( PRLPD3DDEV9 pDev, D3DRENDERSTATETYPE eType, DWORD dwVal )
{
	return pDev->SetRenderState( eType, dwVal );	

}//	devSetRS
//--------------------------------------------------------------------------------
HRESULT devSetRSLightEnable( PRLPD3DDEV9 pDev, BOOL bVal )
{
	return devSetRS( pDev, D3DRS_LIGHTING, bVal );

}//	devSetLightEnable
//--------------------------------------------------------------------------------
HRESULT devSetRSZEnable( PRLPD3DDEV9 pDev, BOOL bVal )
{
	return devSetRS( pDev, D3DRS_ZENABLE, bVal );

}//	devSetRSZEnable
//--------------------------------------------------------------------------------
HRESULT devSetRSZWriteEnable( PRLPD3DDEV9 pDev, BOOL bVal )
{
	return devSetRS( pDev, D3DRS_ZWRITEENABLE, bVal );

}//	devSetRSZWriteEnable
//--------------------------------------------------------------------------------
HRESULT	devSetRSCullMode( PRLPD3DDEV9 pDev, DWORD dwVal )
{
	return devSetRS( pDev, D3DRS_CULLMODE, dwVal );

}//	devSetRSCullMode
//--------------------------------------------------------------------------------
HRESULT	devSetRSFillMode( PRLPD3DDEV9 pDev, DWORD dwVal )
{
	return devSetRS( pDev, D3DRS_FILLMODE, dwVal );

}//	devSetRSFillMode
//--------------------------------------------------------------------------------
HRESULT devSetRSAMBIENT( PRLPD3DDEV9 pDev, DWORD dwVal )
{
	return devSetRS( pDev, D3DRS_AMBIENT, dwVal );

}//	devSetRSAMBIENT
//--------------------------------------------------------------------------------
HRESULT	devSetRSAlphaBlnd( PRLPD3DDEV9 pDev, BOOL bVal )
{
	return devSetRS( pDev, D3DRS_ALPHABLENDENABLE, bVal );

}//	devSetRSAlphaBlnd
//--------------------------------------------------------------------------------
HRESULT	devSetRSAlphaTest( PRLPD3DDEV9 pDev, BOOL bVal )
{
	return devSetRS( pDev, D3DRS_ALPHATESTENABLE, bVal );

}//	devSetRSAlphaTest
//--------------------------------------------------------------------------------
HRESULT devSetRSAlphaREF( PRLPD3DDEV9 pDev, DWORD dwVal )
{
	return devSetRS( pDev, D3DRS_ALPHAREF, dwVal );

}//	devSetRSAlphaREF
//--------------------------------------------------------------------------------
HRESULT devSetRSAlphaFunc( PRLPD3DDEV9 pDev, DWORD dwVal )
{
	return devSetRS( pDev, D3DRS_ALPHAFUNC, dwVal );

}//	devSetRSAlphaFunc
//--------------------------------------------------------------------------------
HRESULT devSetRSSRCBlnd( PRLPD3DDEV9 pDev, DWORD dwVal )
{
	return devSetRS( pDev, D3DRS_SRCBLEND, dwVal );

}//	devSetRSSRCBlnd
//--------------------------------------------------------------------------------
HRESULT devSetRSDSTBlnd( PRLPD3DDEV9 pDev, DWORD dwVal )
{
	return devSetRS( pDev, D3DRS_DESTBLEND, dwVal );

}//	devSetRSDSTBlnd
//--------------------------------------------------------------------------------
HRESULT devSetRSDiTherEnable( PRLPD3DDEV9 pDev, BOOL bVal )
{
	return devSetRS( pDev, D3DRS_DITHERENABLE, bVal );

}//	devSetRSDiTherEnable
//--------------------------------------------------------------------------------
HRESULT devSetRSSpecularEnable( PRLPD3DDEV9 pDev, BOOL bVal )
{
	return devSetRS( pDev, D3DRS_SPECULARENABLE, bVal );

}//	devSetRSSpecularEnable
//--------------------------------------------------------------------------------
HRESULT devSetRSBlendOP( PRLPD3DDEV9 pDev, DWORD dwVal )
{
	return devSetRS( pDev, D3DRS_BLENDOP, dwVal );

}//	devSetRSBlendOP
//--------------------------------------------------------------------------------
HRESULT devSetRSDestBlend( PRLPD3DDEV9 pDev, DWORD dwVal )
{
	return devSetRS( pDev, D3DRS_DESTBLEND, dwVal );

}//	devSetRSDestBlend
//--------------------------------------------------------------------------------
HRESULT devSetRSSrcBlend( PRLPD3DDEV9 pDev, DWORD dwVal )
{
	return devSetRS( pDev, D3DRS_SRCBLEND, dwVal );

}//	devSetRSSrcBlend
//--------------------------------------------------------------------------------
HRESULT	devGetRState( PRLPD3DDEV9 pDev, D3DRENDERSTATETYPE eType, DWORD *pdwVal )
{
	return pDev->GetRenderState( eType, pdwVal );

}//	devGetRState
//--------------------------------------------------------------------------------

//	EOF