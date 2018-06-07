#ifndef _JRCOMMONVTXINFO_H_
#define _JRCOMMONVTXINFO_H_
#pragma once

//----------------------------------------------------------------------------------------
//	Fixed Vertex Format 
//----------------------------------------------------------------------------------------
struct sPRVtx_Xyz
{
	float _fX, _fY, _fZ;

	sPRVtx_Xyz():	_fX(0.0f), _fY(0.0f), _fZ(0.0f)	{};
	
	enum { FVF = D3DFVF_XYZ };
};
void	SetVtxInfoXyz( sPRVtx_Xyz* pVtx, D3DXVECTOR3 vecPos );
//----------------------------------------------------------------------------------------
struct	sPRVtx_Xyz_Diff : public sPRVtx_Xyz
{	
	DWORD		_dxColor;

	sPRVtx_Xyz_Diff() : _dxColor(0xffffffff) {};

	enum { FVF = sPRVtx_Xyz::FVF | D3DFVF_DIFFUSE };		
};
void	SetVtxInfoXyzDiff(sPRVtx_Xyz_Diff* pVtx, D3DXVECTOR3 p, D3DCOLOR clr);
//----------------------------------------------------------------------------------------
struct	sPRVtx_Xyz_Tex1 : public sPRVtx_Xyz
{
	float _fTu, _fTv;

	sPRVtx_Xyz_Tex1() : _fTu(0.0f), _fTv(0.0f)	{};	

	enum { FVF = sPRVtx_Xyz::FVF | D3DFVF_TEX1 };
};
void	SetVtxInfoXyzTex1( sPRVtx_Xyz_Tex1* pVtx, D3DXVECTOR3 vecPos, float fTu, float fTv );
//----------------------------------------------------------------------------------------
struct	sPRVtx_Xyz_Diff_Tex1 : public sPRVtx_Xyz_Diff	//	PRDShowImage에서 주로 사용.
{ 	
	float		_fTu,_fTv;

	sPRVtx_Xyz_Diff_Tex1()	:	_fTu(0.0f), _fTv(0.0f)	{};

	enum { FVF = sPRVtx_Xyz_Diff::FVF | D3DFVF_TEX1 };
};
void	SetVtxInfoXyzDiffTex1( sPRVtx_Xyz_Diff_Tex1* pVtx, D3DXVECTOR3 vecPos, D3DCOLOR	dxColor, float fTu, float fTv );
//----------------------------------------------------------------------------------------
struct	sPRVtx_Xyz_Norm : public sPRVtx_Xyz
{
    float	_fNormX,
			_fNormY,
			_fNormZ;

	sPRVtx_Xyz_Norm() :	_fNormX(0.0f),
						_fNormY(0.0f),
						_fNormZ(0.0f)	{};
	enum { FVF = sPRVtx_Xyz::FVF | D3DFVF_NORMAL };
};
void	SetVtxInfoXyzNorm(sPRVtx_Xyz_Norm* pVtx, D3DXVECTOR3 vecPos, D3DXVECTOR3 vecNorm );
//----------------------------------------------------------------------------------------
struct	sPRVtx_Xyz_Norm_Diff : public sPRVtx_Xyz_Norm
{
	D3DCOLOR _dxColor;

	sPRVtx_Xyz_Norm_Diff() :	_dxColor(0xffffffff)
	{};

	enum { FVF = sPRVtx_Xyz_Norm::FVF | D3DFVF_DIFFUSE };
};
void	SetVtxInfoXyzNormDiff( sPRVtx_Xyz_Norm_Diff* pVtx, D3DXVECTOR3 vecPos, D3DXVECTOR3 vecNorm, D3DCOLOR dxColor );
//----------------------------------------------------------------------------------------
struct	sPRVtx_Xyz_Norm_Tex1 : public sPRVtx_Xyz_Norm
{
	float _fTu;
	float _fTv;

	sPRVtx_Xyz_Norm_Tex1() :	_fTu(0.0f),	_fTv(0.0f)	{};
	 
	enum { FVF = sPRVtx_Xyz_Norm::FVF | D3DFVF_TEX1};
};
void	SetVtxInfoXyzNormTex1(sPRVtx_Xyz_Norm_Tex1* pVtx, D3DXVECTOR3 p, D3DXVECTOR3 nor, float fTu, float fTv );
//----------------------------------------------------------------------------------------
struct	sPRVtx_Xyz_Norm_Diff_Tex1 : public sPRVtx_Xyz_Norm_Diff
{
	float _fTu;
	float _fTv;

	sPRVtx_Xyz_Norm_Diff_Tex1()	:	_fTu(0.0f), 
									_fTv(0.0f)
	{};

	enum { FVF = sPRVtx_Xyz_Norm_Diff::FVF | D3DFVF_TEX1};
};
void	SetVtxInfoXyzNormDiffTex1(sPRVtx_Xyz_Norm_Diff_Tex1* pVtx, D3DXVECTOR3 p, D3DXVECTOR3 nor, float fTu, float fTv, D3DCOLOR dxColor );
//----------------------------------------------------------------------------------------
struct	sPRVtx_Xyz_Diff_PtSize : public sPRVtx_Xyz_Diff
{
	float		_fPSize;
	sPRVtx_Xyz_Diff_PtSize() : _fPSize(0.0f)	{};

	enum { FVF = sPRVtx_Xyz_Diff::FVF | D3DFVF_PSIZE };
};
void	SetVtxInfoXyzDiffPtSize(sPRVtx_Xyz_Diff_PtSize* pVtx, D3DXVECTOR3 p, D3DCOLOR clr, float fPSize );
//------------------------------------------------------------------------------------------
struct	sPRVtx_XyzRhw
{
	float _fX, _fY, _fZ, _fRhw;
	sPRVtx_XyzRhw() : _fX(0.0f), 
					_fY(0.0f), 
					_fZ(0.0f), 
					_fRhw(0.0f)	{};
	enum { FVF = D3DFVF_XYZRHW };
};
void	SetVtxInfoXyzrhw( sPRVtx_XyzRhw* pVtx, D3DXVECTOR4 vecPos );
//----------------------------------------------------------------------------------------
struct	sPRVtx_XyzRhw_Diff : public sPRVtx_XyzRhw
{	
	D3DCOLOR	_dxColor;
	sPRVtx_XyzRhw_Diff() : _dxColor(0xffffffff) {};
	sPRVtx_XyzRhw_Diff( D3DXVECTOR4 pos, DWORD dwCol )
	{
		_fX		= pos.x;
		_fY		= pos.y;
		_fZ		= pos.z;
		_fRhw	= pos.w;

		_dxColor = dwCol;
	}

	enum { FVF = sPRVtx_XyzRhw::FVF | D3DFVF_DIFFUSE	};		
};
void	SetVtxInfoXyzrhwDiff( sPRVtx_XyzRhw_Diff* pVtx, D3DXVECTOR4 vecPos, D3DCOLOR dxColor );
//----------------------------------------------------------------------------------------
struct	sPRVtx_Xyzrhw_Diff_Tex1 : public sPRVtx_XyzRhw_Diff
{ 
	float	_fTu,_fTv;

	sPRVtx_Xyzrhw_Diff_Tex1() : _fTu(0.0f), _fTv(0.0f) {};
	sPRVtx_Xyzrhw_Diff_Tex1( D3DXVECTOR4 pos, DWORD dwCol, float fTU, float fTV ) 
	{
		_fX		= pos.x;
		_fY		= pos.y;
		_fZ		= pos.z;
		_fRhw	= pos.w;

		_dxColor = dwCol;

		_fTu	=	fTU;
		_fTv	=	fTV;
	}

	enum { FVF = sPRVtx_XyzRhw_Diff::FVF | D3DFVF_TEX1 };
};
void	SetVtxInfoXyzrhwDiffTex1( sPRVtx_Xyzrhw_Diff_Tex1* pVtx, D3DXVECTOR4 vecPos, D3DCOLOR	dxColor, float fTu, float fTv );
//----------------------------------------------------------------------------------------
//	Index
//------------------------------------------------------------------------------------------
struct	sPRINDEX16
{
	WORD		_wA,	_wB,	_wC;
	sPRINDEX16(): _wA(0), _wB(0), _wC(0){}
	sPRINDEX16( WORD wA, WORD wB, WORD wC ) : _wA(wA), _wB(wB), _wC(wC) {};
};
//----------------------------------------------------------------------------------------
struct	sPRINDEX16_2D
{
	WORD			_wA,	_wB;
	sPRINDEX16_2D(): _wA(0), _wB(0){}
	sPRINDEX16_2D( WORD wA, WORD wB ) : _wA(wA), _wB(wB) {};
};

void	PRSetIdx3D(sPRINDEX16 &ci,	WORD _0, WORD _1, WORD _2);
void	PRSetIdx2D(sPRINDEX16_2D &ci,	WORD _0, WORD _1);
//------------------------------------------------------------------------------------------
struct sPRTVtx
{
	int _nVtxIdx;	//	배열에서 정점의 인덱스

	float _fU, _fV, _fW;

	sPRTVtx() : _nVtxIdx(-1), _fU(0.0f), _fV(0.0f), _fW(0.0f)
	{};
};
//------------------------------------------------------------------------------------------
#endif	//	_JRCOMMONVTXINFO_H_

