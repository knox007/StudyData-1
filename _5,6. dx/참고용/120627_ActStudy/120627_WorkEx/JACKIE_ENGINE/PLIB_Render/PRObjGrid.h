#pragma once

#ifndef	_PROBJGRID_H_
#define _PROBJGRID_H_

#include "PRObject.h"
#include "PRCommonVtxInfo.h"
#include "PRCommonTypeDef.h"

class CPRObjGrid : public CPRObject
{
public:
	CPRObjGrid()				
	{
		InitMembers(); 
	}
	CPRObjGrid( 
				D3DXVECTOR3 vPos,
				int nSize,
				D3DCOLOR colEdge	= D3DCOLOR( 0xffff0000 ), 
				D3DCOLOR colInner	= D3DCOLOR( 0xffffffff ) )	
	{ 
		InitMembers( vPos, nSize, colEdge, colInner ); 
	}
	virtual ~CPRObjGrid(void)
	{
		ClearMembers();
	}

	void	OnReset( LPDIRECT3DDEVICE9 pDev );
	void	OnLost();

	void	SetColorInner( D3DCOLOR col )	{ m_dxColorInnerLine = col; }
	void	SetColorEdge( D3DCOLOR col )	{ m_dxColorEdgeLine = col; }
	void	SetSize( int nSize )			{ m_nSize = nSize; }
	D3DCOLOR	GetColorInner()				{ return m_dxColorInnerLine; }	
	D3DCOLOR	GetColorEdge()				{ return m_dxColorEdgeLine; }

	bool	OnUpdate( float fElapsedTime = 0 )	{ return true; }
	HRESULT	OnRender( LPDIRECT3DDEVICE9 pDev, float fElapsedTime );


private:

	void	InitMembers();
	void	InitMembers( D3DXVECTOR3 vPos, int nSize, D3DCOLOR colEdge, D3DCOLOR colInner );
	void	ClearMembers();

	PRDXVTXBUFF9	m_VertBuff;
	PRDXIDXBUFF9	m_IdxBuff;
	D3DCOLOR				m_dxColorEdgeLine;
	D3DCOLOR				m_dxColorInnerLine;

	int		m_nSize;
	bool	m_bVisible;

};

#endif
//	_PROBJGRID_H_