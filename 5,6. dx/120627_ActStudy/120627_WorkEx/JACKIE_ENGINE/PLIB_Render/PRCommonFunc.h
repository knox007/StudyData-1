#ifndef _JRCOMMON_H_
#define _JRCOMMON_H_
#pragma once

#include "PRCommonTypeDef.h"


//------------------------------------------------------------------------------------------
//	Shader
HRESULT	devSetVtxShader( PRLPD3DDEV9 pDev, PRLPDVTXSHADER9 pShader );
HRESULT	devSetPxShader( PRLPD3DDEV9 pDev, LPDIRECT3DPIXELSHADER9 pShader );
HRESULT	devCreateVtxDclr( LPDIRECT3DDEVICE9 pDev, CONST PRDXVTXELE9* pVertexElements,IDirect3DVertexDeclaration9** ppDecl); 
HRESULT devSetVtxDclr( PRLPD3DDEV9 pDev, PRLPDVTXDCLR9 ppDecl );
HRESULT devGetVertexDeclaration( PRLPD3DDEV9 pDev, PRLPDVTXDCLR9* ppDecl );
HRESULT devCreateVtxShader(PRLPD3DDEV9 pDev, DWORD* pFunction,IDirect3DVertexShader9** ppShader); 
HRESULT	DeclrFromFVF( DWORD FVF, PRDXVTXELE9 pDeclarator[MAX_FVF_DECL_SIZE] );
HRESULT	devCreateEffFromFile( PRLPD3DDEV9		pDevice,
							  LPCSTR            pSrcFile,
							  CONST D3DXMACRO*  pDefines,
							  PRDXINCL			pInclude,
							  DWORD             Flags,
							  PRDXEFFPOOL		pPool,
							  PRDXXEFF*			ppEffect,
							  PRDXXBUFF*		ppCompilationErrors);
void	PRCheckFXError( HRESULT hr, PRDXXBUFF pErr );
PRDXHND	PRGetTechByName( PRDXXEFF pEff, LPCSTR pName );
PRDXHND	PRGetParaByName( PRDXXEFF pEff, PRDXHND hPar, LPCSTR pName ); 

//------------------------------------------------------------------------------------------
//	Vtx
HRESULT	devCreateVtxBuff( PRLPD3DDEV9 pDev, UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool,IDirect3DVertexBuffer9** ppVertexBuffer,HANDLE* pSharedHandle );
HRESULT	devCreateIdxBuff( PRLPD3DDEV9 pDev, UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DIndexBuffer9** ppIndexBuffer,HANDLE* pSharedHandle);
HRESULT devVtxLock( PRDXVTXBUFF9 pVtx, UINT OffsetToLock,UINT SizeToLock,void** ppbData,DWORD Flags );
HRESULT devVtxUnlock( PRDXVTXBUFF9 pVtx );
HRESULT devSetStreamSrc( PRLPD3DDEV9 pDev, UINT unStreamNum, PRDXVTXBUFF9 pVB, UINT unOffsetInBytes, UINT unStride );
//------------------------------------------------------------------------------------------
//	Idx
HRESULT devIdxLock( PRDXIDXBUFF9 pIdx, UINT OffsetToLock,UINT SizeToLock,void** ppbData,DWORD Flags);
HRESULT devSetIdx( PRLPD3DDEV9 pDev, PRDXIDXBUFF9 pIB );
HRESULT devIdxUnlock( PRDXIDXBUFF9 pIdx );
//------------------------------------------------------------------------------------------
//	TransformMat
HRESULT	devSetTrsform( PRLPD3DDEV9 pDev, D3DTRANSFORMSTATETYPE eType, D3DMATRIX* pMat );
HRESULT	devSetTrsformWorld( PRLPD3DDEV9 pDev, D3DMATRIX* pMat );
HRESULT	devSetTrsformView( PRLPD3DDEV9 pDev, D3DMATRIX* pMat );
HRESULT	devSetTrsformProjection( PRLPD3DDEV9 pDev, D3DMATRIX* pMat );
//------------------------------------------------------------------------------------------
//	RenderState
HRESULT	devSetRS( PRLPD3DDEV9 pDev, D3DRENDERSTATETYPE eType, DWORD dwVal );
HRESULT devSetRSLightEnable( PRLPD3DDEV9 pDev, BOOL bVal );
HRESULT devSetRSZEnable( PRLPD3DDEV9 pDev, BOOL bVal );
HRESULT devSetRSZWriteEnable( PRLPD3DDEV9 pDev, BOOL bVal );
HRESULT	devSetRSCullMode( PRLPD3DDEV9 pDev, DWORD dwVal );
HRESULT	devSetRSFillMode( PRLPD3DDEV9 pDev, DWORD dwVal );
HRESULT devSetRSAMBIENT( PRLPD3DDEV9 pDev, DWORD dwVal );
HRESULT	devSetRSAlphaBlnd( PRLPD3DDEV9 pDev, BOOL bVal );
HRESULT	devSetRSAlphaTest( PRLPD3DDEV9 pDev, BOOL bVal );
HRESULT devSetRSAlphaREF( PRLPD3DDEV9 pDev, DWORD dwVal );
HRESULT devSetRSAlphaFunc( PRLPD3DDEV9 pDev, DWORD dwVal );
HRESULT devSetRSSRCBlnd( PRLPD3DDEV9 pDev, DWORD dwVal );
HRESULT devSetRSDSTBlnd( PRLPD3DDEV9 pDev, DWORD dwVal );
HRESULT devSetRSDiTherEnable( PRLPD3DDEV9 pDev, BOOL bVal );
HRESULT devSetRSSpecularEnable( PRLPD3DDEV9 pDev, BOOL bVal );
HRESULT devSetRSBlendOP( PRLPD3DDEV9 pDev, DWORD dwVal );
HRESULT devSetRSDestBlend( PRLPD3DDEV9 pDev, DWORD dwVal );
HRESULT devSetRSSrcBlend( PRLPD3DDEV9 pDev, DWORD dwVal );
HRESULT	devGetRState( PRLPD3DDEV9 pDev, D3DRENDERSTATETYPE eType, DWORD *pdwVal );
 //------------------------------------------------------------------------------------------
//	Texture
HRESULT	devSetTxtr( PRLPD3DDEV9 pDev, DWORD dwState, LPDIRECT3DBASETEXTURE9 ptex );
HRESULT	devSetTSS( PRLPD3DDEV9 pDev, DWORD dwState, D3DTEXTURESTAGESTATETYPE eType, DWORD dwVal );
HRESULT devSetTSSAlphop( PRLPD3DDEV9 pDev, DWORD dwState, DWORD dwVal );
HRESULT devSetTSSAlphaArg1( PRLPD3DDEV9 pDev, DWORD dwState, DWORD dwVal );
HRESULT devSetTSSAlphaArg2( PRLPD3DDEV9 pDev, DWORD dwState, DWORD dwVal );
HRESULT	devSetTSSCOLOROP( PRLPD3DDEV9 pDev, DWORD dwState, DWORD dwVal );
HRESULT	devSetTSSCOLORARG1( PRLPD3DDEV9 pDev, DWORD dwState, DWORD dwVal );
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
								LPDIRECT3DTEXTURE9*       ppTexture);
//------------------------------------------------------------------------------------------
//	Material & Light
HRESULT	devSetMtrl( PRLPD3DDEV9 pDev, PRDMTRL9* pMtrl );
HRESULT	devSetLight( PRLPD3DDEV9 pDev, DWORD dwIdx, D3DLIGHT9* pLight );
HRESULT	devLightEnable( PRLPD3DDEV9 pDev, DWORD dwIdx, BOOL bEnable );
//------------------------------------------------------------------------------------------
//	AlphaBlend
enum	eALPHABLENDTYPE_
{
	eALPHABLENDTYPE_SA_DA,
	eALPHABLENDTYPE_SA_DINVSA,	

	eALPHABLENDTYPE_SIZE
};
HRESULT	devSetAlphaBlend( PRLPD3DDEV9 pDev, eALPHABLENDTYPE_ eType );
HRESULT	devSetAlphaTest( PRLPD3DDEV9 pDev, DWORD dwVal, D3DCMPFUNC eType );
//------------------------------------------------------------------------------------------
//	Etc
HRESULT	devSetSmpS( PRLPD3DDEV9 pDev, DWORD dwSampler, D3DSAMPLERSTATETYPE eType, DWORD dwVal );
HRESULT	devSetSmpSMINFilter( PRLPD3DDEV9 pDev, DWORD dwSampler, DWORD dwVal );
HRESULT	devSetSmpSMAGFilter( PRLPD3DDEV9 pDev, DWORD dwSampler, DWORD dwVal );
HRESULT	devSetSmpSMIPFilter( PRLPD3DDEV9 pDev, DWORD dwSampler, DWORD dwVal );
HRESULT	devSetSmpSFilters( PRLPD3DDEV9 pDev, DWORD dwSampler, DWORD dwVal );

HRESULT	devSetFVF( PRLPD3DDEV9 pDev, DWORD dwFVF );
HRESULT	devClr(	PRLPD3DDEV9 pDev, 
					DWORD		dwClrRectCnt,
					D3DRECT*	prtClearArr,
					DWORD		dwClrFlag,
					D3DCOLOR	colBackScr,
					float		m_fZ,
					DWORD		dwStencil );
HRESULT	devBeginScene( PRLPD3DDEV9 pDev );
HRESULT devEndScene( PRLPD3DDEV9 pDev );
HRESULT devPresent( PRLPD3DDEV9 pDev, RECT* pSourceRect = NULL, RECT* pDestRect = NULL, HWND hDestWindowOverride = NULL, RGNDATA* pDirtyRegion = NULL );
HRESULT	devGetCreationParam( PRLPD3DDEV9 pDev, PRDDEVCREATEPARA *pParameters );
void	PRCheckError( HRESULT hr );
//------------------------------------------------------------------------------------------
// Device DrawPrimitive
HRESULT	devDrawPrim(	PRLPD3DDEV9 pDev, 
					D3DPRIMITIVETYPE PrimitiveType,
					UINT StartVertex,
					UINT PrimitiveCount);

HRESULT	devDrawIdxPrim(	PRLPD3DDEV9 pDev, 
						D3DPRIMITIVETYPE,
						int BaseVertexIndex,
						UINT MinVertexIndex,
						UINT NumVertices,
						UINT startIndex,
						UINT primCount);

HRESULT	devDrawPUP(	PRLPD3DDEV9 pDev, 
							D3DPRIMITIVETYPE eType, 
							UINT unPrimitiveCount, 
							const void* pVertexStreamZeroData, 
							UINT unVertexStreamZeroStride ); 

void	devDrawLIneUP(	PRLPD3DDEV9 pDev, 
						D3DXVECTOR3 &vecStart, 
						D3DXVECTOR3& vecEnd, 
						D3DCOLOR colStart,
						D3DCOLOR colEnd );

void	devDrawPt(	PRLPD3DDEV9 pDev,
					D3DXVECTOR3 &vec,
					D3DCOLOR col );
//------------------------------------------------------------------------------------------
// Vector
#define PRDVecZero( x )	\
{\
	x = D3DXVECTOR3(0,0,0);\
}//	PRDVecZero
D3DXVECTOR3*	PRDVec3Norm( D3DXVECTOR3 *pOut, CONST D3DXVECTOR3 *pV );
D3DXVECTOR4*	PRDVec4Trsfrm( D3DXVECTOR4 *pOut, CONST D3DXVECTOR4 *pV, CONST D3DXMATRIX *pM );
//------------------------------------------------------------------------------------------
// Matrix
D3DXMATRIX*		PRDXMatInit( PRDXMat *pOut );
D3DXMATRIX*		PRDXMatTranslation( PRDXMat*pOut, FLOAT x, FLOAT y, FLOAT z );
D3DXMATRIX*		PRDXMatRotX( PRDXMat*pOut, FLOAT Angle );
D3DXMATRIX*		PRDXMatRotY( PRDXMat*pOut, FLOAT Angle );
D3DXMATRIX*		PRDXMatRotZ( PRDXMat*pOut, FLOAT Angle );
D3DXMATRIX*		PRDXMatInv( PRDXMat *pOut, FLOAT *pDeterminant, CONST PRDXMat *pM );
D3DXMATRIX*		PRDXMatTranspose( D3DXMATRIX *pOut, CONST D3DXMATRIX *pM );
//--------------------------------------------------------------------------------



#endif	//	_JRCOMMON_H_