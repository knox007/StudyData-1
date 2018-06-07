#include "StdAfx.h"
#include "PRCamera.h"
#include "PUtCommon.h"
#include "PRCommonFunc.h"
#include "PUtLog.h"

const	float	MIN_SPEED_MOVE		=	1.0f;
const	float	DEF_SPEED_MOVE		=	10.5f;
const	float	DEF_SPEED_ROTATE	=	5.0f;

const	float	DEF_BOOSTER_MOVE	=	1.8f;
const	float	DEF_BOOSTER_ROTATE	=	3.0f;

const	float	DEF_DISTTOTARGET	=	10.0f;
const	float	MIN_DISTTOTARGET	=	0.5f;

const	float	DEF_SMOOTH_MOVE		=	0.2f;
const	float	DEF_SMOOTH_ROTATE	=	0.5f;
const	float	DEF_SMOOTH_POSDELTA	=	0.25f;
const	float	MIN_SMOOTH_POSDELTA	=	0.001f;

const	float	DEF_PROJECTIONPARA_FOV		=	D3DX_PI / 4.f;
const	float	DEF_PROJECTIONPARA_ASPECT	=	1.0f;
const	float	DEF_PROJECTIONPARA_NEAR		=	1.0f;
const	float	DEF_PROJECTIONPARA_FAR		=	100.0f;


//--------------------------------------------------------------------------------------------
void	CPRCamera::InitMembers()
{
	m_eType	=	eTYPE_THIRD;
	PRDVecZero( m_vecDelta[eDELTA_TOTPOS] );
	ResetTmpDelta();

}//	InitMember
//--------------------------------------------------------------------------------------------
HRESULT CPRCamera::Init(PRLPD3DDEV9 dev, D3DXVECTOR3 *pos, D3DXVECTOR3 *targ)
{
	m_Vec[eVEC_EYE]		= (pos)  ? *pos  : D3DXVECTOR3(0,0,0);
	m_Vec[eVEC_LOOKAT]	= (targ) ? *targ : D3DXVECTOR3(0,0,0);
	m_Vec[eVEC_UP]		= D3DXVECTOR3(0,1,0);
	m_Vec[eVEC_DIR]		= D3DXVECTOR3(0,0,1);
	m_Vec[eVEC_CROSS]	= D3DXVECTOR3(0,0,0);	

	m_fRotate[eROTATE_YAW]		= 0.0f; 
	m_fRotate[eROTATE_PITCH]	= 0.0f; 
	m_fRotate[eROTATE_ROLL]		= 0.0f; 

	m_fSpeed[eSPEED_MOVE]			= DEF_SPEED_MOVE;
	m_fSpeed[eSPEED_MOVE_MIN]		= MIN_SPEED_MOVE;
	m_fSpeed[eSPEED_ROTATE]			= DEF_SPEED_ROTATE;
	m_fSpeed[eSPEED_BOOSTER_MOVE]	= DEF_BOOSTER_MOVE;
	m_fSpeed[eSPEED_BOOSTER_ROTATE]	= DEF_BOOSTER_ROTATE;

	m_fDistToTarget[eDISTTOTARGET_DEF]	=	DEF_DISTTOTARGET;
	m_fDistToTarget[eDISTTOTARGET_CUR]	=	m_fDistToTarget[eDISTTOTARGET_DEF];
	m_fDistToTarget[eDISTTOTARGET_MIN]	=	MIN_DISTTOTARGET;

	m_fSmooth[eSMOOTH_MOVE]		= DEF_SMOOTH_MOVE;
	m_fSmooth[eSMOOTH_ROTATE]	= DEF_SMOOTH_ROTATE;
	m_fSmooth[eSMOOTH_POSDELTA] = DEF_SMOOTH_POSDELTA;

	if(dev) 
	{
		D3DVIEWPORT9 vp;	
		dev->GetViewport(&vp);	
		m_fProjParam[ePROJPARAM_ASPECT] = (float)vp.Width / (float)vp.Height;	
	}
	else		
		m_fProjParam[ePROJPARAM_ASPECT] = DEF_PROJECTIONPARA_ASPECT;

	m_fProjParam[ePROJPARAM_FOV]	 = DEF_PROJECTIONPARA_FOV;
	m_fProjParam[ePROJPARAM_NEAR]	 = DEF_PROJECTIONPARA_NEAR; 
	m_fProjParam[ePROJPARAM_FAR]	 = DEF_PROJECTIONPARA_FAR;

	//카메라 행렬 초기화.
	SetViewParams( &m_Vec[eVEC_EYE], &m_Vec[eVEC_LOOKAT] );
	//프로젝션 행렬 초기화.
	SetProjParams( m_fProjParam[ePROJPARAM_FOV], m_fProjParam[ePROJPARAM_ASPECT], m_fProjParam[ePROJPARAM_NEAR], GetProjParam(ePROJPARAM_FAR) );

	return S_OK;

}//	Init
//--------------------------------------------------------------------------------------------
void CPRCamera::OnUpdate(float et)
{
	// 부드러운 이동
	m_vecDelta[eDELTA_TOTPOS]	=		m_vecDelta[eDELTA_TOTPOS]
									*	(1.0f - m_fSmooth[eSMOOTH_MOVE]) 
									+	m_vecDelta[eDELTA_UNITPOS]
									*	m_fSmooth[eSMOOTH_MOVE];

	if (D3DXVec3Length(&m_vecDelta[eDELTA_TOTPOS])<=MIN_SMOOTH_POSDELTA) 
		m_vecDelta[eDELTA_TOTPOS] *= 0.f;	

	D3DXMATRIX  mCamRot;
	D3DXVECTOR3 WorldUp, WorldDir;
	// 로컬좌표를 회전 시켜 카메라 방향과 up을 만든다.
	D3DXVECTOR3 LocalUp	= D3DXVECTOR3(0,1,0);
	D3DXVECTOR3 LocalDir= D3DXVECTOR3(0,0,1);


	//yaw, pitch의 각도로 회전행렬을 만든다.
	D3DXMatrixRotationYawPitchRoll(&mCamRot, m_fRotate[eROTATE_YAW], m_fRotate[eROTATE_PITCH], 0);
	D3DXVec3TransformCoord(&WorldUp,  &LocalUp,  &mCamRot);
	D3DXVec3TransformCoord(&WorldDir, &LocalDir, &mCamRot);
	//---------------------------------
	// 3인칭 카메라
	//---------------------------------
	//이동방향을 회전 시켜 카메라 이동방향을 만든다.
	D3DXVECTOR3 posDeltaWorld;
	D3DXVec3TransformCoord(&posDeltaWorld, &m_vecDelta[eDELTA_TOTPOS], &mCamRot);
	
	if( GetType() == eTYPE_THIRD )
	{	
		//보는 방향과 위치.
		m_Vec[eVEC_LOOKAT] += posDeltaWorld;
		m_Vec[eVEC_EYE]   = m_Vec[eVEC_LOOKAT] - (WorldDir * m_fDistToTarget[eDISTTOTARGET_CUR]);
	}
	//---------------------------------
	// 1인칭 카메라
	//---------------------------------
	else
	{	
		//보는 방향과 위치.
		m_Vec[eVEC_EYE] += posDeltaWorld;
		m_Vec[eVEC_LOOKAT] = m_Vec[eVEC_EYE] + WorldDir;
	}

	//방향과 크로스벡터를 구해 놓는다.
	m_Vec[eVEC_DIR]=m_Vec[eVEC_LOOKAT]-m_Vec[eVEC_EYE];
	PRDVec3Norm(&m_Vec[eVEC_DIR], &m_Vec[eVEC_DIR]);
	D3DXVec3Cross(&m_Vec[eVEC_CROSS], &LocalUp, &m_Vec[eVEC_DIR]);
	PRDVec3Norm(&m_Vec[eVEC_CROSS], &m_Vec[eVEC_CROSS]);

	//카메라 행렬을 만들고, 카메라의 역행렬도 만들어 둔다.
	D3DXMatrixLookAtLH(&m_Mat[eMAT_VIEW], &m_Vec[eVEC_EYE], &m_Vec[eVEC_LOOKAT], &WorldUp);
		
	//프로젝션 행렬을 만든다.
	D3DXMatrixPerspectiveFovLH(&m_Mat[eMAT_PROJECTION], m_fProjParam[ePROJPARAM_FOV], 
														m_fProjParam[ePROJPARAM_ASPECT], 
														m_fProjParam[ePROJPARAM_NEAR], 
														m_fProjParam[ePROJPARAM_FAR]);
														

	//빌보드 행렬.
	PRDXMatInv(&m_Mat[eMAT_WORLD], NULL, &m_Mat[eMAT_VIEW]);
	D3DXMatrixIdentity(&m_Mat[eMAT_BILLBOARD]);
	for (int i=0; i<3; ++i) {
		for (int j=0; j<3; ++j) {
			m_Mat[eMAT_BILLBOARD].m[i][j] = m_Mat[eMAT_VIEW].m[j][i];
		}
	}

}//	OnUpdate
//--------------------------------------------------------------------------------------------
void CPRCamera::SetViewParams(D3DXVECTOR3* pEyePt, D3DXVECTOR3* pLookAt)
{
	if( !pEyePt || !pLookAt ) 
		return;

	//카메라 행렬을 만든다.
	m_Vec[eVEC_DEFEYE] = m_Vec[eVEC_EYE]  = *pEyePt;
	m_Vec[eVEC_DEFLOOKAT] = m_Vec[eVEC_LOOKAT] = *pLookAt;

	D3DXMatrixLookAtLH(&m_Mat[eMAT_VIEW], pEyePt, pLookAt, &m_Vec[eVEC_UP]);

	D3DXMATRIX mInvView;
	PRDXMatInv(&mInvView, NULL, &m_Mat[eMAT_VIEW]);

	D3DXVECTOR3* pZb = (D3DXVECTOR3*)&mInvView._31;
	//회전각을 구한다.
	m_fRotate[eROTATE_YAW]		= atan2f(pZb->x, pZb->z);
	float len	= sqrtf(pZb->z*pZb->z + pZb->x*pZb->x);
	m_fRotate[eROTATE_PITCH]		= -atan2f(pZb->y,len);

}//	SetViewParams
//--------------------------------------------------------------------------------------------
void CPRCamera::SetProjParams(float fFov, float fAspect, float fNear, float fFar)
{
	m_fProjParam[ePROJPARAM_FOV]	= fFov;
	m_fProjParam[ePROJPARAM_ASPECT]	= fAspect;
	m_fProjParam[ePROJPARAM_NEAR]	= fNear;
	m_fProjParam[ePROJPARAM_FAR]	= fFar;
	D3DXMatrixPerspectiveFovLH(&m_Mat[eMAT_PROJECTION], fFov, fAspect, fNear, fFar);

}//	SetProjParams
//--------------------------------------------------------------------------------------------
void CPRCamera::SetMove( D3DXVECTOR3 &vStep, float fElapsed )
{	
	m_vecDelta[eDELTA_UNITPOS] += vStep*fElapsed*m_fSpeed[eSPEED_MOVE];	

}//	SetMove
//--------------------------------------------------------------------------------------------
void	CPRCamera::SetRotate( float fStepX, float fStepY, float fElapsed )
{
	float fBoost = 1.0f;
	if( IsEnableBoost(eBOOST_ROTATE) )
		fBoost = m_fSpeed[eSPEED_BOOSTER_ROTATE];

	m_fRotate[eROTATE_YAW]  += fStepX * fElapsed * m_fSmooth[eSMOOTH_ROTATE] * fBoost * m_fSpeed[eSPEED_ROTATE];
	m_fRotate[eROTATE_PITCH]+= fStepY* fElapsed * m_fSmooth[eSMOOTH_ROTATE] * fBoost * m_fSpeed[eSPEED_ROTATE];
	m_fRotate[eROTATE_PITCH] = __max( -D3DX_PI*0.5f, m_fRotate[eROTATE_PITCH]);
	m_fRotate[eROTATE_PITCH] = __min( +D3DX_PI*0.5f, m_fRotate[eROTATE_PITCH]);

}//	SetRotate
//--------------------------------------------------------------------------------------------
void	CPRCamera::SetPosDelta( float fStepX, float fStepY, float fElapsed )
{
	m_vecDelta[eDELTA_TOTPOS].x = -fStepX * fElapsed * (m_fDistToTarget[eDISTTOTARGET_CUR] * m_fSmooth[eSMOOTH_POSDELTA] );
	m_vecDelta[eDELTA_TOTPOS].y =  fStepY * fElapsed * (m_fDistToTarget[eDISTTOTARGET_CUR] * m_fSmooth[eSMOOTH_POSDELTA] );	

}//	SetPosDelta
//--------------------------------------------------------------------------------------------
void	CPRCamera::SetDistToTargetCur( float fStep )
{
	// 마우스 휠 = 카메라 스피드
	m_fDistToTarget[eDISTTOTARGET_CUR] -= fStep;
	if(m_fDistToTarget[eDISTTOTARGET_CUR]<m_fDistToTarget[eDISTTOTARGET_MIN]) 
		m_fDistToTarget[eDISTTOTARGET_CUR]=m_fDistToTarget[eDISTTOTARGET_MIN];

}//	SetDistToTargetCur
//--------------------------------------------------------------------------------------------
void	CPRCamera::SetSpeed( eSPEED_ eType, float fStep )
{
	//마우스 휠 = 카메라 스피드
	m_fSpeed[eType]	+=	fStep;	
	if(m_fSpeed[eType]<m_fSpeed[eSPEED_MOVE_MIN]) 
		m_fSpeed[eType]=m_fSpeed[eSPEED_MOVE_MIN];

}//	SetSpeed
//--------------------------------------------------------------------------------------------
void	CPRCamera::ResetTmpDelta()			
{ 
	PRDVecZero( m_vecDelta[eDELTA_UNITPOS] );

}//	ResetTmpDelta
//--------------------------------------------------------------------------------------------
void	CPRCamera::SetType( eTYPE_ eType )	
{
	m_eType = eType;
		
	if( m_eType == eTYPE_THIRD )
	{
		D3DXVECTOR3 vecRes = *GetVec( CPRCamera::eVEC_LOOKAT );

		vecRes +=	*GetVec(CPRCamera::eVEC_DIR ) * GetDistToTarget();

		SetVec( CPRCamera::eVEC_LOOKAT, vecRes );

	}//	if( m_eType == eTYPE_THIRD )

}//SetType
//--------------------------------------------------------------------------------------------
//	EOF