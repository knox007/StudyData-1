#pragma once

#ifndef _PROBJECT_H_
#define	_PROBJECT_H_


class CPRObject
{
public:
	CPRObject(void)	{ InitMembers(); }
	virtual ~CPRObject(void)	{}

	virtual	void	OnReset( LPDIRECT3DDEVICE9 pDev )	=	0;
	virtual	void	OnLost()	=	0;

	virtual	bool	OnUpdate( float fElapsedTime = 0 )	=	0;
	virtual HRESULT	OnRender( LPDIRECT3DDEVICE9 pDev, float fElapsedTime )	=	0;

	virtual	void	SetPos( D3DXVECTOR3 vPos )	{ m_vecPos = vPos; }

protected:

	void	InitMembers()	{ D3DXMatrixIdentity( &m_matWorld ); m_vecPos = D3DXVECTOR3( 0.0f, 0.0f, 0.0f ); }

	D3DXVECTOR3	m_vecPos;
	D3DXMATRIX	m_matWorld;
};

#endif	
//	_PROBJECT_H_