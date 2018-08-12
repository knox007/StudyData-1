// Implementation of the CMcCamera class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


CMcCamera::CMcCamera()
{
	m_pDev	= NULL;

	D3DXMatrixIdentity(&m_mtViw);
	D3DXMatrixIdentity(&m_mtPrj);


	m_vcEye		= D3DXVECTOR3(0,0,-1);													// Camera position
	m_vcLook	= D3DXVECTOR3(0,0, 0);													// Look vector
	m_vcUp		= D3DXVECTOR3(0,1, 0);														// up vector

	m_fFov		= D3DX_PI/4.f;
	m_fAsp		= 800.f/600.f;
	m_fNr		= 1.f;
	m_fFr		= 10000.f;

	m_vcBasis	= D3DXVECTOR3( 0, 0, 0);
	m_fEpslnY	=  20.f;
	m_fGap		= 100.f;
}

CMcCamera::~CMcCamera()
{

}

INT CMcCamera::Create(LPDIRECT3DDEVICE9 pDev)
{
	m_pDev		= pDev;

	m_vcBasis	= D3DXVECTOR3( 60, 50, 60);

	FLOAT fYaw	= D3DXToRadian(60.f);
	D3DXVECTOR3	vcZ( cosf(fYaw), 0, sinf(fYaw));

	vcZ			*=m_fGap;

	D3DXVECTOR3 vcLook	= m_vcBasis + D3DXVECTOR3(0, m_fEpslnY, 0);
	D3DXVECTOR3 vcEye	= vcLook - vcZ;

	SetParamView(vcEye, vcLook, D3DXVECTOR3(0,1,0));

	return 0;
}


INT CMcCamera::FrameMove()
{
	D3DXVECTOR3 vcDelta = g_pApp->m_pInput->GetMouseEps();

	if(vcDelta.z !=0.f)
	{
		m_fGap += vcDelta.z*0.1f;

		if(m_fGap<50.f)
			m_fGap = 50.f;

		D3DXVECTOR3 vcZ	= D3DXVECTOR3(m_mtViw._13, m_mtViw._23, m_mtViw._33);
		m_vcEye			= m_vcLook - vcZ* m_fGap;
	}

	if(g_pApp->m_pInput->KeyState('W'))
		MoveForward( 4.f, 1.f);

	if(g_pApp->m_pInput->KeyState('S'))
		MoveForward(-4.f, 1.f);

	if(g_pApp->m_pInput->KeyState('A'))
		MoveSideward(-4.f);

	if(g_pApp->m_pInput->KeyState('D'))
		MoveSideward(4.f);

	if(g_pApp->m_pInput->BtnState(1))
		Rotate(&vcDelta, 0.2f);


	UpdateViewProj();

	m_pDev->SetTransform(D3DTS_VIEW, &m_mtViw);
	m_pDev->SetTransform(D3DTS_PROJECTION, &m_mtPrj);

	return 0;
}


void CMcCamera::UpdateViewProj()
{
	D3DXMatrixPerspectiveFovLH(&m_mtPrj, m_fFov, m_fAsp, m_fNr, m_fFr);
	D3DXMatrixLookAtLH(&m_mtViw, &m_vcEye, &m_vcLook, &m_vcUp);
}



void CMcCamera::MoveSideward(FLOAT fSpeed)
{
	D3DXVECTOR3 tmp(m_mtViw._11, 0, m_mtViw._31);
	D3DXVec3Normalize(&tmp,&tmp);

	m_vcBasis+= tmp * fSpeed;
	m_vcEye  += tmp * fSpeed;
	m_vcLook += tmp * fSpeed;
}


void CMcCamera::MoveForward(FLOAT fSpeed, FLOAT fY)
{
	D3DXVECTOR3 tmp(m_mtViw._13, m_mtViw._23*fY, m_mtViw._33);
	D3DXVec3Normalize(&tmp,&tmp);

	m_vcBasis+= tmp * fSpeed;
	m_vcEye  += tmp * fSpeed;
	m_vcLook += tmp * fSpeed;
}


void CMcCamera::Rotate(const D3DXVECTOR3* vcDelta, float fSpeed)
{
	D3DXVECTOR3	vcEps = *vcDelta;

	FLOAT fYaw;
	FLOAT fPitch;
	D3DXVECTOR3 vcZ;
	D3DXVECTOR3 vcY;
	D3DXVECTOR3 vcX;

	D3DXMATRIX	rtY;
	D3DXMATRIX	rtX;

	// 월드 좌표 y 축에 대한 회전
	fYaw	= D3DXToRadian(vcEps.x * 0.1f);
	D3DXMatrixRotationY(&rtY, fYaw);

	vcZ = m_vcEye - m_vcLook;
	vcY = D3DXVECTOR3(m_mtViw._12, m_mtViw._22, m_mtViw._32);

	D3DXVec3TransformCoord(&vcZ, &vcZ, &rtY);
	D3DXVec3TransformCoord(&vcY, &vcY, &rtY);

	m_vcEye	= m_vcLook + vcZ;
	m_vcUp	= vcY;
	D3DXMatrixLookAtLH(&m_mtViw, &m_vcEye, &m_vcLook, &m_vcUp);


	// 카메라의 x 축에 대한 회전
	fPitch= D3DXToRadian(vcEps.y * 0.1f);
	vcZ = m_vcEye - m_vcLook;
	vcY = D3DXVECTOR3(m_mtViw._12, m_mtViw._22, m_mtViw._32);
	vcX = D3DXVECTOR3(m_mtViw._11, m_mtViw._21, m_mtViw._31);

	D3DXMatrixRotationAxis(&rtX, & vcX, fPitch);
	D3DXVec3TransformCoord(&vcZ, &vcZ, &rtX);
	D3DXVec3TransformCoord(&vcY, &vcY, &rtX);

	m_vcEye	= m_vcLook + vcZ;
	m_vcUp	= vcY;
	D3DXMatrixLookAtLH(&m_mtViw, &m_vcEye, &m_vcLook, &m_vcUp);
}
