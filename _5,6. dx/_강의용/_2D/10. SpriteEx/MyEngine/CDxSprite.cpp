//===============================================
#include "Global.h"
//===============================================
CDxSprite::CDxSprite() { m_pDxSprite = NULL; }
//===============================================
CDxSprite::~CDxSprite(){ Destroy(); }
//===============================================
void CDxSprite::Destroy(){ SAFE_RELEASE(m_pDxSprite); }
//===============================================
HRESULT CDxSprite::Create( LPDIRECT3DDEVICE9 pDev )
{
	if (FAILED(D3DXCreateSprite(pDev, &m_pDxSprite)))
	{
		SAFE_RELEASE(m_pDxSprite);
		return E_FAIL;
	}

	return S_OK;

}//	HRESULT CDxSprite::Create()
//===============================================
HRESULT CDxSprite::Draw(LPDIRECT3DTEXTURE9 pTex
	, const RECT *pSrcRect
	, const D3DXVECTOR2 *pScale
	, const D3DXVECTOR2 *pCenter
	, float fAngle
	, const D3DXVECTOR2 *pPosition
	, D3DCOLOR color)
{
	D3DXMATRIX mtWorld;
	D3DXMatrixIdentity(&mtWorld);

	float fTheta = D3DXToRadian(fAngle);

	D3DXMATRIX mtScale;
	D3DXMATRIX mtRotation;
	D3DXMATRIX mtTranslation;
	D3DXMATRIX mtRotationCenter;
	D3DXMATRIX mtRotationCenterInv;

	D3DXMatrixIdentity(&mtScale);
	D3DXMatrixIdentity(&mtRotation);
	D3DXMatrixIdentity(&mtTranslation);
	D3DXMatrixIdentity(&mtRotation);
	D3DXMatrixIdentity(&mtRotationCenter);
	D3DXMatrixIdentity(&mtRotationCenterInv);

	//	스케일 적용.
	if (pScale)
		D3DXMatrixScaling(&mtScale, pScale->x, pScale->y, 1.0f);

	//	회전 적용.
	D3DXMatrixRotationZ(&mtRotation, -fTheta);

	//	피벗 적용.
	if (pCenter)
		D3DXMatrixTranslation(&mtRotationCenter, pCenter->x, pCenter->y, 0);

	//	피벗 적용.
	if (pCenter)
		D3DXMatrixTranslation(&mtRotationCenterInv, -pCenter->x, -pCenter->y, 0);

	//	이동
	if (pPosition)
		D3DXMatrixTranslation(&mtTranslation, pPosition->x, pPosition->y, 0);

	mtWorld = mtScale * mtRotationCenterInv * mtRotation * mtRotationCenter * mtTranslation;

	m_pDxSprite->SetTransform(&mtWorld);
	m_pDxSprite->Draw(pTex, pSrcRect, NULL, NULL, color);

	D3DXMatrixIdentity(&mtWorld);
	m_pDxSprite->SetTransform(&mtWorld);

	return S_OK;

}//	HRESULT CDxSprite::Draw( ... )
//===============================================