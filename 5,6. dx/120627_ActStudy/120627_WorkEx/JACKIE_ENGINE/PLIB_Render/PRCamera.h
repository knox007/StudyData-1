#pragma once
#ifndef	_PRACAMERAEX_H_
#define _PRACAMERAEX_H_


class CPRCamera
{
public:

	//@	카메라 행렬
	enum	eMAT_
	{
		eMAT_WORLD,
		eMAT_VIEW,
		eMAT_PROJECTION,
		eMAT_BILLBOARD,
		eMAT_SIZE
	};

	//@	카메라 벡터
	enum	eVEC_
	{
		eVEC_EYE,
		eVEC_LOOKAT,
		eVEC_DIR,
		eVEC_UP,
		eVEC_CROSS,
		eVEC_DEFEYE,
		eVEC_DEFLOOKAT,
		eVEC_SIZE
	};

	//@	회전
	enum	eROTATE_
	{
		eROTATE_PITCH,
		eROTATE_YAW,
		eROTATE_ROLL,
		eROTATE_SIZE
	};

	//@	속도
	enum	eSPEED_
	{
		eSPEED_MOVE,
		eSPEED_MOVE_MIN,
		eSPEED_ROTATE,
		eSPEED_BOOSTER_MOVE,
		eSPEED_BOOSTER_ROTATE,
		eSPEED_SIZE
	};

	//@	프로젝션 행렬 인자.
	enum	ePROJPARAM_
	{
		ePROJPARAM_FOV,
		ePROJPARAM_ASPECT,
		ePROJPARAM_NEAR,
		ePROJPARAM_FAR,
		ePROJPARAM_SIZE
	};

	//@	카메라 타입
	enum	eTYPE_
	{
		eTYPE_FIRST,
		eTYPE_THIRD,
		eTYPE_SIZE
	};


	//@	이동 위치.
	enum	eDELTA_
	{
		eDELTA_UNITPOS,
		eDELTA_TOTPOS,
		eDELTA_SIZE
	};

	//@	감도
	enum	eSMOOTH_
	{
		eSMOOTH_MOVE,
		eSMOOTH_ROTATE,
		eSMOOTH_POSDELTA,
		eSMOOTH_SIZE
	};

	//@	부스터 타입.
	enum	eBOOST_
	{
		eBOOST_MOVE,
		eBOOST_ROTATE,
		eBOOST_SIZE
	};

	//@	타겟과의 거리.
	enum	eDISTTOTARGET_
	{
		eDISTTOTARGET_CUR,
		eDISTTOTARGET_DEF,		
		eDISTTOTARGET_MIN,
		eDISTTOTARGET_SIZE
	};

	CPRCamera()	{ InitMembers(); }
	~CPRCamera()	{}
	void	InitMembers();

	HRESULT Init(LPDIRECT3DDEVICE9 dev, D3DXVECTOR3 *pos, D3DXVECTOR3 *targ);

	void	OnUpdate(float fElapsedTime = 0);
	void	Reset()	
			{ SetViewParams(&m_Vec[eVEC_DEFEYE], &m_Vec[eVEC_DEFLOOKAT]); }
	void	ResetTmpDelta();
			

	void	SetMove( D3DXVECTOR3 &vStep, float fElapsed );
	void	SetRotate( float fSetpX, float fStepY, float fElapsed );
	void	SetViewParams(D3DXVECTOR3* pEyePt, D3DXVECTOR3* pLookAt);
	void	SetProjParams(float fFov, float fAspect, float fNear, float fFar);	
	void	SetPosDelta( float fStepX, float fStepY, float fElapsed );		

	void	SetTarget(D3DXVECTOR3 &targ)	
			{ m_Vec[eVEC_LOOKAT] = targ; }
	void	SetType( eTYPE_ eType );
//			{ m_eType = eType; }	
	void	SetBoosterMove( float fVal )	
			{ m_fSpeed[eSPEED_BOOSTER_MOVE] = fVal; }
	void	SetVec( eVEC_ eType, D3DXVECTOR3 &vVal )	
			{ m_Vec[eType] = vVal; }
	
	void	SetDistToTargetCur( float fStep );

	void	SetSpeed( eSPEED_ eType, float fStep );





	eTYPE_	GetType()
	{ return m_eType; }	
	float	GetDistToTarget()	
	{ return m_fDistToTarget[eDISTTOTARGET_CUR]; }
	const D3DXMATRIX*	GetMat( eMAT_ eType )	
	{ return &m_Mat[eType]; }	
	const D3DXVECTOR3*	GetVec( eVEC_ eType )	
	{ return &m_Vec[eType]; }	
	const float			GetProjParam( ePROJPARAM_ eType )
	{ return m_fProjParam[eType]; }
	void	CheckEnableBoostRotate( bool bVal )	
	{ m_bBoost[eBOOST_ROTATE] = bVal; }
	void	CheckEnableBoostMove( bool bVal )
	{ 
		m_bBoost[eBOOST_MOVE] = bVal;
		if(bVal) 
			m_vecDelta[eDELTA_UNITPOS] *= m_fSpeed[eSPEED_BOOSTER_MOVE]; 
	}
	bool	IsEnableBoost( eBOOST_ eType )
	{ return m_bBoost[eType]; }




private:
	eTYPE_		m_eType;

	LPDIRECT3DDEVICE9 m_pDev;

	D3DXMATRIX	m_Mat[eMAT_SIZE];	
	D3DXVECTOR3	m_Vec[eVEC_SIZE];

	float		m_fRotate[eROTATE_SIZE];
	float		m_fSpeed[eSPEED_SIZE];	
	float		m_fProjParam[ePROJPARAM_SIZE];	
	float		m_fSmooth[eSMOOTH_SIZE];
	D3DXVECTOR3	m_vecDelta[eDELTA_SIZE];
	float		m_fDistToTarget[eDISTTOTARGET_SIZE];	

	bool		m_bBoost[eBOOST_SIZE];

};


#endif
//	_PRACAMERAEX_H_