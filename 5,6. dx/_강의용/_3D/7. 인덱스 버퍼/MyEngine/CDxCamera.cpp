//======================================================
#include "Global.h"
//======================================================
//-------------------------------
CDxCamera::CDxCamera()
{
	m_pDev = NULL;

	m_fMoveSpeed = 0.1f;
	m_fRotSpeed = 0.1f;
}
//-------------------------------
int	CDxCamera::Create(LPDIRECT3DDEVICE9 pDev, float fMoveSpeed, float fRotSpeed)
{
	m_pDev = pDev;

	//	카메라 위치,타겟, 업벡터 설정.
	m_vecEyePos = D3DXVECTOR3(0, 5, -5);
	m_vecLookAt = D3DXVECTOR3(0, 0, 0);
	m_vecUp = D3DXVECTOR3(0, 1, 0);

	m_fMoveSpeed = fMoveSpeed;
	m_fRotSpeed = fRotSpeed;

	//	투영 행렬 설정.
	D3DXMatrixPerspectiveFovLH(
		&m_matProj,
		D3DX_PI / 4.f,
		g_pMyGame->GetScrWidth() / g_pMyGame->GetScrHeight(),
		1.f,
		5000.f);

	return 0;

}//	int	CDxCamera::Create(LPDIRECT3DDEVICE9 pDev)
//-------------------------------
int CDxCamera::FrameMove()
{
	if (g_pMyGame->GetInput()->KeyPress('W'))
		MoveForward(m_fMoveSpeed);
	if (g_pMyGame->GetInput()->KeyPress('S'))
		MoveForward(-m_fMoveSpeed);

	if (g_pMyGame->GetInput()->KeyPress('A'))
		MoveSide(-m_fMoveSpeed);
	if (g_pMyGame->GetInput()->KeyPress('D'))
		MoveSide(m_fMoveSpeed);
		
	if (g_pMyGame->GetInput()->KeyPress('Q'))
		MoveUp(m_fMoveSpeed);
	if (g_pMyGame->GetInput()->KeyPress('Z'))
		MoveUp(-m_fMoveSpeed);

	if (g_pMyGame->GetInput()->BtnPress(1))
	{
		D3DXVECTOR3	vecDelta = g_pMyGame->GetInput()->GetMouseEps();
		Rotate(&vecDelta, m_fRotSpeed);

	}//	if (g_pApp->GetInput()->BtnState(1))

	D3DXVECTOR3	vecDelta = g_pMyGame->GetInput()->GetMouseEps();
	MoveForward(vecDelta.z * m_fMoveSpeed);
	
	D3DXMatrixLookAtLH(&m_matView, &m_vecEyePos, &m_vecLookAt, &m_vecUp);
	m_pDev->SetTransform(D3DTS_VIEW, &m_matView);
	m_pDev->SetTransform(D3DTS_PROJECTION, &m_matProj);

	return 0;

}//	int CDxCamera::FrameMove()
//-------------------------------
void CDxCamera::MoveForward(float fSpeed)
{
	D3DXVECTOR3	dirZ(m_matView._13, m_matView._23, m_matView._33);
	D3DXVec3Normalize(&dirZ, &dirZ);

	m_vecEyePos += dirZ * fSpeed;
	m_vecLookAt += dirZ * fSpeed;

}//	void CDxCamera::MoveForward(float fSpeed)
//-------------------------------
void CDxCamera::MoveSide(float fSpeed)
{	
	D3DXVECTOR3 dirX(m_matView._11, 0, m_matView._31);
	D3DXVec3Normalize(&dirX, &dirX);

	m_vecEyePos += dirX * fSpeed;
	m_vecLookAt += dirX * fSpeed;

}//	void CDxCamera::MoveSide(float fSpeed)
//-------------------------------
void CDxCamera::MoveUp(float fSpeed)
{
	D3DXVECTOR3 dirY = D3DXVECTOR3(0, 1, 0);
	m_vecEyePos += dirY * fSpeed;
	m_vecLookAt += dirY * fSpeed;
}
//-------------------------------
void CDxCamera::Rotate(D3DXVECTOR3 *pvecDelta, float fSpeed)
{
	D3DXVECTOR3	vecDelta = *pvecDelta;

	float fYaw, fPitch;

	D3DXVECTOR3 dirX, dirY, dirZ;
	D3DXMATRIX matRotX, matRotY;

	//	월드 좌표 Y축에 대한 회전.	( Yaw )	-------------------
	fYaw = D3DXToRadian(vecDelta.x * fSpeed);
	//	회전에 대한 행렬값 연산.
	D3DXMatrixRotationY(&matRotY, fYaw);

	//	카메라의 Z축 방향.
	dirZ = m_vecLookAt - m_vecEyePos;
	//	카메라의 Y축 방향.
	dirY = D3DXVECTOR3(m_matView._12, m_matView._22, m_matView._32);

	//	회전에 대한 방향 재설정.
	D3DXVec3TransformCoord(&dirZ, &dirZ, &matRotY);
	D3DXVec3TransformCoord(&dirY, &dirY, &matRotY);

	m_vecLookAt = m_vecEyePos + dirZ;
	m_vecUp = dirY;
	D3DXMatrixLookAtLH(&m_matView, &m_vecEyePos, &m_vecLookAt, &m_vecUp);


	//	월드 좌표 X축에 대한 회전.	( Pitch )	---------------
	fPitch = D3DXToRadian(vecDelta.y * fSpeed);
	dirX = D3DXVECTOR3(m_matView._11, m_matView._21, m_matView._31);
	dirY = D3DXVECTOR3(m_matView._12, m_matView._22, m_matView._32);
	dirZ = m_vecLookAt - m_vecEyePos;

	D3DXMatrixRotationAxis(&matRotX, &dirX, fPitch);
	D3DXVec3TransformCoord(&dirZ, &dirZ, &matRotX);
	D3DXVec3TransformCoord(&dirY, &dirY, &matRotX);

	m_vecLookAt = m_vecEyePos + dirZ;
	m_vecUp = dirY;
	D3DXMatrixLookAtLH(&m_matView, &m_vecEyePos, &m_vecLookAt, &m_vecUp);

}//	void CDxCamera::Rotate(D3DXVECTOR3 *pvecDelta, float fSpeed)
//-------------------------------

//======================================================