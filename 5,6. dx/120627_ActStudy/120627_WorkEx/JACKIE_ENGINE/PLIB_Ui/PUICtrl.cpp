#include "StdAfx.h"
#include "PUICtrl.h"
#include "PUTCommon.h"
//------------------------------------------------------------------------------------
void	CPUICtrl::InitMembers()
{
	m_eCtrlType	=	eCTRLTYPE_NONE;
	m_nID		=	-1;
	m_unCtrlID	=	-1;
	m_pUserData	=	NULL;

	m_bEnable			=	true;
	m_bVisible			=	true;
	m_bMouseInRect		=	false;
	m_bFocus			=	false;	//	jackie 110908 Really Need??
	m_bDefault			=	false;
 	
	m_fSkinAlpha	=	0.0f;

	m_pDlg			=	NULL;

	m_nPosX			=	0;
	m_nPosY			=	0;
	m_nWidth		=	0;
	m_nHeight		=	0;

	PUT_ZERO_MEMORY( m_rcBoundBox );	
}//	InitMembers
//------------------------------------------------------------------------------------
void	CPUICtrl::ClearMembers()
{
	m_CustomSkinElements.DeleteAll();
	m_Elements.DeleteAll();
}//	ClearMembers
//------------------------------------------------------------------------------------
void	CPUICtrl::SetTextColor( D3DCOLOR col )
{
	CPUIElement*	pEle	=	GetElement(0);

	if( pEle )
		pEle->GetFontColor().SetStateColor( eCTRLSTATE_NORMAL, col );
}//	SetTextColor
//------------------------------------------------------------------------------------
HRESULT	CPUICtrl::SetElement( UINT unElement, CPUIElement* pEle )
{
	HRESULT	hr = S_OK;

	if( pEle == NULL )
		return E_INVALIDARG;

	for( size_t nCur = m_Elements.GetSize(); nCur <= unElement; ++nCur )
	{
		CPUIElement* pNewEle = NULL;
		PUTNEW( pNewEle, CPUIElement );

		if( pNewEle == NULL )
			return E_OUTOFMEMORY;

		m_Elements.Add( pNewEle );		
	}

	CPUIElement*	pCurEle = GetElement(unElement);
	*pCurEle	=	*pEle;

	return S_OK;
}//	SetElement
//------------------------------------------------------------------------------------
HRESULT	CPUICtrl::SetCustomSkinElement( UINT unElement, CPUIElement* pEle )
{
	HRESULT	hr = S_OK;

	if( pEle == NULL )
		return E_INVALIDARG;

	for(	UINT unCur = m_CustomSkinElements.GetSize();
			unCur <= unElement; ++unCur )
	{
		CPUIElement*	pNewEle = NULL;
		PUTNEW( pNewEle, CPUIElement );
		if( pNewEle == NULL )
			return E_OUTOFMEMORY;

		m_CustomSkinElements.Add( pNewEle );
	}

	CPUIElement*	pCurEle = GetCustomSkinElement(unElement);
	*pCurEle	=	*pEle;

	return S_OK;
}//	SetCustomSkinElement
//------------------------------------------------------------------------------------
void	CPUICtrl::Refresh()
{
	m_bMouseInRect	= false;
	m_bFocus		= false;	//	jackie 110908 Really Need??

	for( size_t nCur = 0; nCur < m_Elements.GetSize(); ++nCur )
	{
		CPUIElement*	pEle	=	GetElement(nCur);
		pEle->Refresh();
	}
}//	Refresh
//------------------------------------------------------------------------------------
void	CPUICtrl::UpdateRects()
{
	SetRect(	&m_rcBoundBox, 
				m_nPosX,			m_nPosY, 
				m_nPosX + m_nWidth,	m_nPosY + m_nHeight );
}//	UpdateRects
//------------------------------------------------------------------------------------
CPUIElement*	CPUICtrl::GetElement( UINT unElement )
{
	CPUIElement* pRetEle = NULL;
	size_t unSize = m_Elements.GetSize();
	
	VEC_ITER(CPUIElement*) iterCur = m_Elements.GetIterBegin();
	
	for( size_t nCur = 0; nCur < unSize; ++nCur, ++iterCur )
	{
		CPUIElement* pCurEle = (*iterCur);
		if( unElement == nCur )
		{
			pRetEle = pCurEle;
			break;
		}
	}

	return pRetEle;
}//	GetElement
//------------------------------------------------------------------------------------
CPUIElement*	CPUICtrl::GetCustomSkinElement( UINT unElement )
{
	CPUIElement* pRetEle = NULL;
	size_t unSize = m_CustomSkinElements.GetSize();		
	
	VEC_ITER(CPUIElement*) iterCur = m_CustomSkinElements.GetIterBegin();

	for( size_t nCur = 0; nCur < unSize; ++nCur, ++iterCur )
	{
		CPUIElement* pCurEle = (*iterCur);
		if( unElement == nCur )
		{
			pRetEle = pCurEle;
			break;
		}
	}

	return pRetEle;
}//	GetCustomSkinElement
//------------------------------------------------------------------------------------
//	EOF