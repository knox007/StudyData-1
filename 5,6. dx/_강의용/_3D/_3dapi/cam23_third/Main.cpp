

#include "_StdAfx.h"


CMain::CMain()
{
	m_pD3DXFont	= NULL;
	m_pInput	= NULL;
	m_pGrid		= NULL;

	m_pCamT		= NULL;

	m_pMesh		= NULL;
}


HRESULT CMain::Init()
{
	SAFE_NEWCREATE1(m_pInput , CMcInput		, m_hWnd);
	SAFE_NEWCREATE1(m_pGrid	 , CMcGrid		, m_pd3dDevice);

	SAFE_NEWCREATE1(m_pCamT	 , CMcCamera	, m_pd3dDevice);

	D3DXCreateSphere(m_pd3dDevice, 2, 16, 16, &m_pMesh, 0);

	
	D3DXFONT_DESC hFont =
	{
		16, 0
		, FW_NORMAL
		, 1
		, FALSE
		, HANGUL_CHARSET
		, OUT_DEFAULT_PRECIS
		, ANTIALIASED_QUALITY
		, FF_DONTCARE
		, "Arial"
	};

	if( FAILED( D3DXCreateFontIndirect(m_pd3dDevice, &hFont, &m_pD3DXFont ) ) )
		return -1;

	return S_OK;
}


HRESULT CMain::Destroy()
{
	SAFE_RELEASE( m_pD3DXFont );

	SAFE_DELETE(	m_pInput	);
	SAFE_DELETE(	m_pGrid		);

	SAFE_DELETE(	m_pCamT		);
	
	SAFE_RELEASE(	m_pMesh		);

	return S_OK;
}



HRESULT CMain::Restore()
{
	if(m_pD3DXFont)
		m_pD3DXFont->OnResetDevice();

	return S_OK;
}


HRESULT CMain::Invalidate()
{
	if(m_pD3DXFont)
		m_pD3DXFont->OnLostDevice();

	return S_OK;
}




HRESULT CMain::FrameMove()
{
	SAFE_FRMOV(	m_pInput	);
	SAFE_FRMOV(	m_pCamT		);

	return S_OK;
}


HRESULT CMain::Render()
{
	HRESULT hr=0;

	if( FAILED( m_pd3dDevice->BeginScene() ) )
		return -1;


	m_pd3dDevice->Clear( 0L
						, NULL
						, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL
						, 0x00006699
						, 1.0f
						, 0L
						);

	
	//그리드를 그린다.
	SAFE_RENDER(	m_pGrid		);


	D3DLIGHT9 Lgt;
	D3DMATERIAL9	mtl;
	D3DUtil_InitLight( Lgt, D3DLIGHT_DIRECTIONAL, -1.0f, -1.0f, 2.0f );
	D3DUtil_InitMaterial(mtl,1.0f, 0.0f,0.0f);

	m_pd3dDevice->SetLight( 0, &Lgt );
	m_pd3dDevice->LightEnable( 0, TRUE );
	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0x000F0F0F );

	m_pd3dDevice->SetMaterial( &mtl );
	
	m_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	D3DXMATRIX mtW;
	D3DXMatrixIdentity(&mtW);

	D3DXVECTOR3	vcChar = m_pCamT->GetBasis();

	mtW._41 = vcChar.x;
	mtW._42 = vcChar.y;
	mtW._43 = vcChar.z;

	m_pd3dDevice->SetTransform(D3DTS_WORLD,&mtW);
	m_pMesh->DrawSubset(0);

	D3DXMatrixIdentity(&mtW);
	m_pd3dDevice->SetTransform(D3DTS_WORLD,&mtW);

	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);




	
	m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE);
	m_pd3dDevice->SetRenderState( D3DRS_ALPHATESTENABLE , FALSE);
	m_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pd3dDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	
	RECT	rc;
	char	sMsg[256]={0};
	sprintf( sMsg, "%s %s", m_strDeviceStats, m_strFrameStats	);
	SetRect(&rc, 2, 10, m_d3dsdBackBuffer.Width - 20, 30);

	m_pD3DXFont->DrawText(NULL, sMsg, -1, &rc, 0, D3DCOLOR_ARGB(255,255,255,0));

	m_pd3dDevice->EndScene();
	
	return S_OK;
}



LRESULT CMain::MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	if(m_pInput)
		m_pInput->MsgProc(hWnd, msg, wParam, lParam);

	switch( msg )
	{
		case WM_PAINT:
		{
			if( m_bLoadingApp )
			{
				HDC m_hDC = GetDC( hWnd );
				RECT rc;
				GetClientRect( hWnd, &rc );
				ReleaseDC( hWnd, m_hDC );
			}
			break;
		}
		
	}
	
	return CD3DApplication::MsgProc( hWnd, msg, wParam, lParam );
}