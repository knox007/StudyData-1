#pragma once
//=====================================================
struct SVtxTex
{
	//-------------------------------
	D3DXVECTOR3 _pos;	// ���� ��ġ
	float _u, _v;		//	�ؽ��� ��ǥ.
	//-------------------------------
	SVtxTex() { ZeroMemory(this, sizeof(this)); }
	//-------------------------------
	SVtxTex(D3DXVECTOR3 pos, float u, float v)
	{
		_pos = pos;
		_u = u;
		_v = v;
	}
	//-------------------------------

};	//	struct SVtxTex
#define D3DFVF_XYZTEX1	(D3DFVF_XYZ|D3DFVF_TEX1)
//=====================================================
struct SVtxDiffuse
{
	//-------------------------------
	D3DXVECTOR3 _pos;	//	���� ��ġ
	DWORD		_color;	//	���� ��.
	//-------------------------------
	SVtxDiffuse() { ZeroMemory(this, sizeof(this)); }
	//-------------------------------
	SVtxDiffuse(D3DXVECTOR3 pos, DWORD color)
	{
		_pos = pos;
		_color = color;
	}
	//-------------------------------

};	//	struct SVtxDiffuse
#define D3DFVF_XYZDIFFUSE	(D3DFVF_XYZ|D3DFVF_DIFFUSE)
//=====================================================
struct SIdx
{
	WORD	_0, _1, _2;
};
//=====================================================