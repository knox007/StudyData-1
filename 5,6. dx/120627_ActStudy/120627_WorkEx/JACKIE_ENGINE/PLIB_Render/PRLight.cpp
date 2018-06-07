#include "StdAfx.h"
#include "PRLight.h"
#include "PUtCommon.h"
#include "PRCommonFunc.h"

const float DEF_SPEED_ROTATE	=	10.0f;

//-----------------------------------------------------------------------
void	CPRLight::InitMembers()
{
	m_pDev		=	NULL;
	PUT_ZERO_MEMORY( m_Light );
	PUT_ZERO_MEMORY( m_Mtrl );
	PRDVecZero( m_vecDir );
	SetType( D3DLIGHT_DIRECTIONAL );

	for( int nCur = 0; nCur < eCOLOR_SIZE; ++nCur )
		m_Color[nCur]	=	PRCOLOR_NOCOLOR;

	m_fRotate[eROTATE_YAW]		=	0.0f;
	m_fRotate[eROTATE_PITCH]	=	0.0f;

	m_fRange	=	0;
	PUT_True( m_bEnable );
	SetIDx(0);
	CheckEnable( true );
	SetRange(1000.0f);
	m_fSpeed	=	DEF_SPEED_ROTATE;

}//	InitMember
//-----------------------------------------------------------------------
void	CPRLight::Init(PRLPD3DDEV9 pDev, DWORD dwIDx, D3DXVECTOR3 vecDir )
{
	SetIDx( dwIDx );

	m_pDev		=	pDev;

	PRDVec3Norm( &vecDir, &vecDir );

	m_vecDir	=	vecDir;

}//	Init
//-----------------------------------------------------------------------
void	CPRLight::OnReset()
{
	if( !m_pDev )
		return;

	D3DXCOLOR col = PRCOLOR_RED(255);
	SetColor( eCOLOR_DIFF_MTRL, col );

	m_Mtrl.Diffuse	=	m_Color[eCOLOR_DIFF_MTRL];	
	devSetMtrl( m_pDev, &m_Mtrl );

	m_Light.Type	=	GetType();
	m_Light.Diffuse	=	m_Color[eCOLOR_DIFF_LIGHT];

	PRDVec3Norm( &m_vecDir, &m_vecDir );
	m_Light.Range		=	GetRange();
	m_Light.Direction	=	m_vecDir;	
	devSetLight( m_pDev, m_dwIDx, &m_Light );
	devLightEnable( m_pDev, m_dwIDx, IsEnable() );
	
	devSetRS( m_pDev, D3DRS_AMBIENT, m_Color[eCOLOR_AMBIENT] );
	devSetRSLightEnable( m_pDev, TRUE );	

}//	OnReset
//-----------------------------------------------------------------------
void	CPRLight::OnUpdate( float fElapsed )
{
	D3DXMATRIX  matRot;
	D3DXMatrixRotationYawPitchRoll(	&matRot, 
									m_fRotate[eROTATE_YAW], 
									m_fRotate[eROTATE_PITCH],
									0
								);

	
	D3DXVECTOR3 vWorldDir, vLightDir =  (D3DXVECTOR3)m_Light.Direction;
	D3DXMATRIX	mLightDir;
	
	D3DXMatrixRotationYawPitchRoll( &mLightDir, 
									m_fRotate[eROTATE_YAW],
									m_fRotate[eROTATE_PITCH],
									0
								);
	D3DXVec3TransformCoord( &vWorldDir, &vLightDir, &mLightDir );
	PRDVec3Norm( &vWorldDir, &vWorldDir );

	m_Light.Direction = vWorldDir;

	if( m_pDev )
		devSetLight( m_pDev, m_dwIDx, &m_Light );		

}//	OnUpdate
//-----------------------------------------------------------------------
void	CPRLight::SetRotate( float fStepX, float fStepY, float fElapsed )
{	
	m_fRotate[eROTATE_YAW]		= -fStepX * fElapsed * m_fSpeed;
	m_fRotate[eROTATE_PITCH]	= -fStepY * fElapsed * m_fSpeed;
	m_fRotate[eROTATE_PITCH]	= __max( -D3DX_PI*0.5f, m_fRotate[eROTATE_PITCH]);
	m_fRotate[eROTATE_PITCH]	= __min( +D3DX_PI*0.5f, m_fRotate[eROTATE_PITCH]);

}//	SetRotate
//-----------------------------------------------------------------------