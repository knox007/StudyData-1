#include "stdafx.h"
#include "PRCommonFunc.h"
#include "PUtCommon.h"
#include "PUtCommonStr.h"

//--------------------------------------------------------------------------------
HRESULT	devSetVtxShader( PRLPD3DDEV9 pDev, PRLPDVTXSHADER9 pShader )
{
	return pDev->SetVertexShader( pShader );

}//	devSetVtxShader
//--------------------------------------------------------------------------------
HRESULT	devSetPxShader( PRLPD3DDEV9 pDev,	LPDIRECT3DPIXELSHADER9 pShader )
{
	return pDev->SetPixelShader( pShader );

}//	devSetPxShader
//--------------------------------------------------------------------------------
HRESULT	devCreateVtxDclr( LPDIRECT3DDEVICE9 pDev, CONST PRDXVTXELE9* pVertexElements,IDirect3DVertexDeclaration9** ppDecl)
{
	return pDev->CreateVertexDeclaration( pVertexElements, ppDecl );

}//	devCreateVtxDclr
//--------------------------------------------------------------------------------
HRESULT devSetVtxDclr( PRLPD3DDEV9 pDev, PRLPDVTXDCLR9 pDecl )
{
	return pDev->SetVertexDeclaration( pDecl );

}//	devSetVtxDclr
//--------------------------------------------------------------------------------
HRESULT devGetVertexDeclaration( PRLPD3DDEV9 pDev, PRLPDVTXDCLR9* ppDecl )
{
	return pDev->GetVertexDeclaration( ppDecl );

}//	devGetVertexDeclaration
//--------------------------------------------------------------------------------
HRESULT	devGetCreationParam( PRLPD3DDEV9 pDev, PRDDEVCREATEPARA *pParameters )
{
	return pDev->GetCreationParameters( pParameters );

}//	devGetCreationParam
//--------------------------------------------------------------------------------
HRESULT devCreateVtxShader(PRLPD3DDEV9 pDev, DWORD* pFunction,IDirect3DVertexShader9** ppShader)
{
	return pDev->CreateVertexShader( pFunction, ppShader );

}//	devCreateVtxShader
//--------------------------------------------------------------------------------
HRESULT	devCreateEffFromFile(	 PRLPD3DDEV9			pDevice,
							 LPCSTR				pSrcFile,
							 CONST D3DXMACRO*	pDefines,
							 PRDXINCL			pInclude,
							 DWORD				Flags,
							 PRDXEFFPOOL		pPool,
							 PRDXXEFF*			ppEffect,
							 PRDXXBUFF*		ppCompilationErrors)
{
	HRESULT hr = S_OK;

	hr = D3DXCreateEffectFromFile(	pDevice, 
		pSrcFile, 
		pDefines, 
		pInclude, 
		Flags, 
		pPool, 
		ppEffect, 
		ppCompilationErrors 
		);

	return hr;

}//	devdevCreateEffFromFile
//--------------------------------------------------------------------------------
HRESULT	DeclrFromFVF( DWORD FVF, PRDXVTXELE9 pDeclarator[MAX_FVF_DECL_SIZE] )
{
	return D3DXDeclaratorFromFVF( FVF, pDeclarator );

}//	DeclrFromFVF
//--------------------------------------------------------------------------------
void	PRCheckFXError( HRESULT hr, PRDXXBUFF pErr )
{
#if defined(_DEBUG) || defined(DEBUG)
	PUT_IsFailed( hr )
	{
		PUTShowErrCode();

		if( pErr )
		{
			PUT_ERROR_MSZ((TCHAR*)pErr->GetBufferPointer());			

		}//	if( pErr )

	}//	PUT_IsFailed( hr )
#else
	(__noop);
#endif

}//	CheckEffError
//--------------------------------------------------------------------------------
PRDXHND	PRGetTechByName( PRDXXEFF pEff, LPCSTR pName )
{
	return pEff->GetTechniqueByName( pName );

}//	PRGetTechByName
//--------------------------------------------------------------------------------
PRDXHND	PRGetParaByName( PRDXXEFF pEff, PRDXHND hPar, LPCSTR pName )
{
	return pEff->GetParameterByName( hPar, pName );

}//	PRGetParaByName
//---------------------------------------------------------------------------------
//	EOF