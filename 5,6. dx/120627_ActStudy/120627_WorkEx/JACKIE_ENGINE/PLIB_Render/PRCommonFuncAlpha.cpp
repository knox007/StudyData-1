#include "stdafx.h"
#include "PRCommonFunc.h"


//--------------------------------------------------------------------------------
HRESULT devSetAlphaBlend_SADA( PRLPD3DDEV9 pDev )
{
	devSetRSZWriteEnable( pDev, FALSE );
	devSetRSAlphaBlnd( pDev, TRUE );
	devSetRSSRCBlnd( pDev, D3DBLEND_SRCALPHA );
	devSetRSDSTBlnd( pDev, D3DBLEND_DESTALPHA );

	return S_OK;

}//	devSetAlphaBlend_SADA
//--------------------------------------------------------------------------------
HRESULT devSetAlphaBlend_SA_DINVSA( PRLPD3DDEV9 pDev )
{
	devSetRSZWriteEnable( pDev, FALSE );
	devSetRSAlphaBlnd( pDev, TRUE );
	devSetRSSRCBlnd( pDev, D3DBLEND_SRCALPHA );
	devSetRSDSTBlnd( pDev, D3DBLEND_INVSRCALPHA);

	return S_OK;

}//	devSetAlphaBlend_SA_DINVSA
//--------------------------------------------------------------------------------
HRESULT	devSetAlphaBlend( PRLPD3DDEV9 pDev, eALPHABLENDTYPE_ eType )
{
	switch( eType )
	{
	case eALPHABLENDTYPE_SA_DA:
		{
			devSetAlphaBlend_SADA( pDev );
		}
		break;

	case eALPHABLENDTYPE_SA_DINVSA:
		{
			devSetAlphaBlend_SA_DINVSA( pDev );
		}
		break;
	}

	return S_OK;

}//	devSetAlphaBlend
//--------------------------------------------------------------------------------
HRESULT	devSetAlphaTest( PRLPD3DDEV9 pDev, DWORD dwVal, D3DCMPFUNC eType )
{
	devSetRSAlphaTest( pDev, TRUE );
	devSetRSAlphaREF( pDev, dwVal );
	devSetRSAlphaFunc( pDev, eType );

	return S_OK;

}//	devSetAlphaTest
//--------------------------------------------------------------------------------