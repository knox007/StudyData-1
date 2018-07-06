#include "StdAfx.h"
#include "PUIStatic.h"
#include "PUTCommon.h"
#include "PUICtrlMisc.h"
#include "PUIDlg.h"
#include "PUICtrl.h"
#include <strsafe.h>


//------------------------------------------------------------------------------------
void	CPUIStatic::InitMembers()
{
	m_eCtrlType		=	eCTRLTYPE_STATIC;
	PUT_ZERO_MEMORY( m_tszText );
	
	m_Elements.DeleteAll();
}//	InitMembers
//------------------------------------------------------------------------------------
HRESULT	CPUIStatic::OnRender( LPDIRECT3DDEVICE9 pDev, float fElapsedTime )
{
	if( !m_bVisible )
		return S_OK;

	eCTRLSTATE_	eState = eCTRLSTATE_NORMAL;

	if( !m_bEnable )
		eState	=	eCTRLSTATE_DISABLED;

	CPUIElement*	pEle = GetCustomSkinElement( eSKINTYPE_STATIC_BACKGROUND );

	pEle->GetTexColor().Blend( eState, fElapsedTime, 0.0f );
	pEle->GetFontColor().Blend( eState, fElapsedTime, 0.0f );

	m_pDlg->DrawSkinSprite( pEle, &m_rcBoundBox );
	m_pDlg->DrawSkinText( m_tszText, pEle, &m_rcBoundBox, true );

	return S_OK;
}//	Render
//------------------------------------------------------------------------------------
HRESULT	CPUIStatic::GetTextCopy( WCHAR* ptszDest, UINT unBufferCnt )
{
	if( !ptszDest || unBufferCnt == 0 )
		return E_INVALIDARG;

	StringCchCopyW( ptszDest, unBufferCnt, m_tszText );

	return S_OK;
}//	GetTextCopy
//------------------------------------------------------------------------------------
HRESULT CPUIStatic::SetText( const WCHAR* ptszText )
{
	if( !ptszText )
	{
		m_tszText[0] = 0;
		return S_OK;
	}

	StringCchCopyW( m_tszText, MAX_PATH, ptszText );
	return S_OK;
}//	SetText
//------------------------------------------------------------------------------------
//	EOF