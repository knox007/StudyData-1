#ifndef _JRCOMMONTYPEDEF_H_
#define _JRCOMMONTYPEDEF_H_
#pragma once


//--------------------------------------------------------------------------------
//	DX9 TYPE
//------------------------------------------
#define PRLPD3DDEV9			LPDIRECT3DDEVICE9
#define PRDVec				D3DVECTOR
#define PRDVec2				D3DXVECTOR2
#define PRDVec3				D3DXVECTOR3
#define PRDVec4				D3DXVECTOR4
#define PRDXMat				D3DXMATRIX
		
#define PRDXVTXBUFF9		LPDIRECT3DVERTEXBUFFER9
#define PRDXIDXBUFF9		LPDIRECT3DINDEXBUFFER9
#define PRDXTXTRBUFF9		LPDIRECT3DTEXTURE9

#define PRDXIMGINFO			D3DXIMAGE_INFO

#define PRDXVTXELE9			D3DVERTEXELEMENT9
#define PRLPDVTXDCLR9		LPDIRECT3DVERTEXDECLARATION9
#define PRLPDVTXSHADER9		LPDIRECT3DVERTEXSHADER9
#define PRDXXBUFF			LPD3DXBUFFER
#define PRDXXMESH			LPD3DXMESH
#define PRDDEVCREATEPARA	D3DDEVICE_CREATION_PARAMETERS
#define PRLPDXCNSTTABLE		LPD3DXCONSTANTTABLE
#define	PRDXHND				D3DXHANDLE
#define	PRDXEFFPOOL			LPD3DXEFFECTPOOL
#define	PRDXXEFF			LPD3DXEFFECT
#define	PRDXINCL			LPD3DXINCLUDE
#define	PRDMTRL9			D3DMATERIAL9
#define	PRDXMESHCONTAINER	LPD3DXMESHCONTAINER


								
					

//--------------------------------------------------------------------------------
// color
//------------------------------------------
#define PRCOLOR( a, r, g, b )			D3DCOLOR_ARGB( a, r, g, b )
#define PRCOLOR_NOCOLOR					PRCOLOR( 255, 255, 255, 255 )
#define PRCOLOR_NOCOLOR_ALPHA( Alpha )	PRCOLOR(Alpha, 255, 255, 255)
#define PRCOLOR_NOCOLOR_FULL			PRCOLOR_NOCOLOR_ALPHA( 255 )


#define PRCOLOR_RED( val )				D3DCOLOR_XRGB( val, 0, 0 )
#define PRCOLOR_GREEN( val )			D3DCOLOR_XRGB( 0, val, 0 )
#define PRCOLOR_BLUE( val )				D3DCOLOR_XRGB( 0, 0, val )

//#define PRCOLOR_RED( val )				D3DCOLOR_XRGB( val, 255 - val, 255 - val)
//#define PRCOLOR_GREEN( val )			D3DCOLOR_XRGB( 255 - val, val, 255 - val )
//#define PRCOLOR_BLUE( val )				D3DCOLOR_XRGB( 255 - val, 255 - val, val )



#endif	//	_JRCOMMONTYPEDEF_H_