#include "stdafx.h"
#include "PUICtrlCommon.h"
#include "PUTCommon.h"

//-------------------------------------------------------
void CPUIBlendColor::InitMembers()
{
	for( int i = 0; i < eCTRLSTATE_MAX; ++i )
	{
		SetStateColor( i, D3DCOLOR_XRGB(0, 0, 0) );
	}

	SetCurrentColor( D3DCOLOR_XRGB(0, 0, 0) );
}//	InitMembers
//-------------------------------------------------------
void CPUIBlendColor::Init( D3DCOLOR colDefault, D3DCOLOR colDisabled, D3DCOLOR colHidden )
{
	for( int i = 0; i < eCTRLSTATE_MAX; ++i )
	{
		SetStateColor( i, colDefault );
	}
	SetStateColor( eCTRLSTATE_DISABLED, colDisabled );
	SetStateColor( eCTRLSTATE_HIDDEN, colHidden );

	SetCurrentColor( colHidden );
}//	Init
//-------------------------------------------------------
void CPUIBlendColor::Blend( UINT iState, float fElapsedTime, float fRate )
{
	D3DXCOLOR colDest = m_colState[ iState ];
	D3DXColorLerp( &m_colCurrent, &m_colCurrent, &colDest, 1.0f - powf( fRate, 30 * fElapsedTime ) );
}//	Blend
//-------------------------------------------------------





//-------------------------------------------------------
void CPUIElement::InitMembers()
{
	m_nTexIdx			= -1;
	m_nFontIdx				= -1;
	m_dwTexFormat			= -1;
	SetRectEmpty( &m_rtTexBounding );

	m_colTex.Init( D3DCOLOR_XRGB(128, 128, 128 ) );
	m_colFont.Init( D3DCOLOR_XRGB(128, 128, 128 ) );
}//	InitMembers
//-------------------------------------------------------
void CPUIElement::SetTex( int nTexId, RECT* prtTex, D3DCOLOR colDefault )
{
	m_nTexIdx = nTexId;

	if( prtTex )
		m_rtTexBounding = *prtTex;
	else
		SetRectEmpty( &m_rtTexBounding );

	m_colTex.Init( colDefault );
}//	SetTex
//-------------------------------------------------------
void CPUIElement::SetFont( int nFontId, D3DCOLOR colDefault, DWORD dwTextForm )
{
	m_nFontIdx		= nFontId;
	m_dwTexFormat	= dwTextForm;

	m_colFont.Init( colDefault );
}//	SetFont
//-------------------------------------------------------
void CPUIElement::Refresh()
{
	m_colTex.SetCurrentColor( m_colTex.GetStateColor( eCTRLSTATE_HIDDEN ) );
	m_colFont.SetCurrentColor( m_colFont.GetStateColor( eCTRLSTATE_HIDDEN ) );
}//	Refresh
//-------------------------------------------------------





//-------------------------------------------------------
void CPUITexNode::InitMembers()
{	
	m_hResourceModule	=	NULL;
	m_nResourceID		=	-1;
	PUT_ZERO_MEMORY( m_wszFilename );
	m_pTex				=	NULL;
	m_dwWidth			=	-1;
	m_dwHeight			=	-1;
	m_bFileSource		=	false;
}//	InitMembers
//-------------------------------------------------------





//-------------------------------------------------------
void CPUIFontNode::InitMembers()
{
	PUT_ZERO_MEMORY(m_tszFace);
	m_pFont		=	NULL;
	m_unHeight	=	0;
	m_unWeight	=	0;
}//	InitMembers
//-------------------------------------------------------




//-------------------------------------------------------
void CPUIElementHolder::InitMembers()
{
	unCtrlType	=	0;
	unIDx			=	0;

	PUT_ZERO_MEMORY(Element);
}//	InitMembers
//-------------------------------------------------------