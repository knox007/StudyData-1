#pragma once
#ifndef _PRLIGHT_H_
#define _PRLIGHT_H_

#include "PRCommonTypeDef.h"

class CPRLight
{
public:
	enum eCOLOR_
	{
		eCOLOR_DIFF_MTRL,
		eCOLOR_DIFF_LIGHT,
		eCOLOR_AMBIENT,
		eCOLOR_SIZE
	};

	enum	eROTATE_
	{
		eROTATE_PITCH,
		eROTATE_YAW,		
		eROTATE_SIZE
	};

	CPRLight()	{ InitMembers(); }
	~CPRLight()	{}

	void Init(LPDIRECT3DDEVICE9 pDev, DWORD dwIDx,  D3DXVECTOR3 vecDir );
	void OnReset();


	void	SetType( D3DLIGHTTYPE eType )
			{ 
				m_Type = eType; 
				m_Light.Type = m_Type;
				OnUpdate();
			}
	void	SetIDx( DWORD dwIdx )
			{ m_dwIDx = dwIdx; }
	void	SetRange( float fRange )
			{ m_fRange = fRange; }
	void	CheckEnable( bool bEnable )
			{ m_bEnable = bEnable; }
	void	SetColor( eCOLOR_ eType, D3DXCOLOR &col )
			{ m_Color[eType] = col; }

	

	D3DLIGHTTYPE	GetType()	
					{ return m_Type; }
	DWORD			GetIDx()
					{ return m_dwIDx; }
	float			GetRange()
					{ return m_fRange; }
	bool			IsEnable()
					{ return m_bEnable; }
	D3DXCOLOR		GetColor( eCOLOR_ eType )
					{ return m_Color[eType]; }
	D3DVECTOR		GetDir()
					{ return m_Light.Direction;}

	void			OnUpdate( float fElapsed = 0.0f);
	void			SetRotate( float fStepX, float fStepY, float fElapsed );

public:

	void	InitMembers();

	LPDIRECT3DDEVICE9	m_pDev;
	D3DLIGHT9			m_Light;
	PRDMTRL9		m_Mtrl;
	D3DXVECTOR3			m_vecDir;
	D3DLIGHTTYPE		m_Type;

	float				m_fRotate[eROTATE_SIZE];
	float				m_fSpeed;
	
	D3DXCOLOR			m_Color[eCOLOR_SIZE];

	float				m_fRange;
	bool				m_bEnable;

	DWORD				m_dwIDx;
};

#endif
//	_PRLIGHT_H_