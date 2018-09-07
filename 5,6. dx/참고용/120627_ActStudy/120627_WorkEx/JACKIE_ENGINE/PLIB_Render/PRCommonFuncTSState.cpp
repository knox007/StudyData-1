#include "stdafx.h"
#include "PRCommonFunc.h"

//--------------------------------------------------------------------------------
HRESULT	devSetTSS( PRLPD3DDEV9 pDev, DWORD dwStage, D3DTEXTURESTAGESTATETYPE eType, DWORD dwVal )
{
	return pDev->SetTextureStageState( dwStage, eType, dwVal );

}//	devSetTSS
//--------------------------------------------------------------------------------
HRESULT devSetTSSAlphop( PRLPD3DDEV9 pDev, DWORD dwState, DWORD dwVal )
{
	return devSetTSS( pDev, dwState, D3DTSS_ALPHAOP, dwVal );

}//	devSetTSSAlphop
//--------------------------------------------------------------------------------
HRESULT devSetTSSAlphaArg1( PRLPD3DDEV9 pDev, DWORD dwState, DWORD dwVal )
{
	return devSetTSS( pDev, dwState, D3DTSS_ALPHAARG1, dwVal );

}//	devSetTSSAlphaArg1
//--------------------------------------------------------------------------------
HRESULT devSetTSSAlphaArg2( PRLPD3DDEV9 pDev, DWORD dwState, DWORD dwVal )
{
	return devSetTSS( pDev, dwState, D3DTSS_ALPHAARG2, dwVal );

}//	devSetTSSAlphaArg2
//--------------------------------------------------------------------------------
HRESULT	devSetTSSCOLOROP( PRLPD3DDEV9 pDev, DWORD dwState, DWORD dwVal )
{
	return devSetTSS( pDev, dwState, D3DTSS_COLOROP, dwVal ); 

}//	devSetTSCOLOROP
//--------------------------------------------------------------------------------
HRESULT	devSetTSSCOLORARG1( PRLPD3DDEV9 pDev, DWORD dwState, DWORD dwVal )
{
	return devSetTSS( pDev, dwState, D3DTSS_COLORARG1, dwVal );

}//	devSetTSSCOLORARG1
//--------------------------------------------------------------------------------
HRESULT devCreateTxtrFromFileEx( PRLPD3DDEV9 pDev,
								LPCSTR                    pSrcFile,
								UINT                      Width,
								UINT                      Height,
								UINT                      MipLevels,
								DWORD                     Usage,
								D3DFORMAT                 Format,
								D3DPOOL                   Pool,
								DWORD                     Filter,
								DWORD                     MipFilter,
								D3DCOLOR                  ColorKey,
								D3DXIMAGE_INFO*           pSrcInfo,
								PALETTEENTRY*             pPalette,
								LPDIRECT3DTEXTURE9*       ppTexture)
{
	return D3DXCreateTextureFromFileEx( pDev, 
										pSrcFile, 
										Width, 
										Height, 
										MipLevels, 
										Usage, 
										Format, 
										Pool, 
										Filter, 
										MipFilter, 
										ColorKey, 
										pSrcInfo, 
										pPalette, 
										ppTexture );

}//	devCreateTxtrFromFileEx
//----------------------------------------------------------------------------------
//	EOF