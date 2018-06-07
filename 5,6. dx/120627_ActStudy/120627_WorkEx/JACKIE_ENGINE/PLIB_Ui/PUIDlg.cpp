#include "StdAfx.h"
#include "PUIDlg.h"
#include "PUTTimer.h"
#include "PUTCommon.h"
#include "PRCommonFunc.h"
#include "PRCommonVtxInfo.h"
#include "PUICtrlMisc.h"

#include "PUIDlgResourceMgr.h"
#include "PUIRadioButton.h"
#include "PUIComboBox.h"
#include "PUIButton.h"
#include "PUIIMEEditBox.h"
#include "PUIListBox.h"
#include "PUISlider.h"
#include "PUIEditBox.h"



//------------------------------------------------------------------------------------------
double		CPUIDlg::stt_dRefreshTime	=	0.0f;
CPUICtrl*	CPUIDlg::stt_pCtrlFocus	=	NULL;
CPUICtrl*	CPUIDlg::stt_pCtrlPressed	=	NULL;
//------------------------------------------------------------------------------------------
CPUIDlg::CPUIDlg( const CPUIDlg &rhs )
{
	*this = rhs;
	/*
	m_nDefaultCtrlID	=	rhs.m_nDefaultCtrlID;

	m_nPosX		=	rhs.m_nPosX;
	m_nPosY		=	rhs.m_nPosY;
	m_nWidth	=	rhs.m_nWidth;
	m_nHeight	=	rhs.m_nHeight;

	m_bVisible	=	rhs.m_bVisible;
	m_bDrag		=	rhs.m_bDrag;

	stt_dRefreshTime	=	rhs.stt_dRefreshTime;
	m_dLastRefreshTime	=	rhs.m_dLastRefreshTime;

	stt_pCtrlFocus		=	rhs.stt_pCtrlFocus;
	stt_pCtrlPressed	=	rhs.stt_pCtrlPressed;
	m_pCtrlMouseIn		=	rhs.m_pCtrlMouseIn;

	m_colLT	=	rhs.m_colLT;
	m_colRT	=	rhs.m_colRT;
	m_colLB	=	rhs.m_colLB;
	m_colRB	=	rhs.m_colRB;

	m_pResMgr			=	rhs.m_pResMgr;
	m_pCallbackEvent	=	rhs.m_pCallbackEvent;
	m_pCallbackEventUserContext		=	rhs.m_pCallbackEventUserContext;

	m_TexIDs	=	rhs.m_TexIDs;
	m_FontIDs	=	rhs.m_FontIDs;

	m_Ctrls		=	rhs.m_Ctrls;
	m_DefaultElements	=	rhs.m_DefaultElements;

	m_bShowDlgRect		=	rhs.m_bShowDlgRect;
	m_SkinElements		=	rhs.m_SkinElements;

	m_pPrevDlg		=	rhs.m_pPrevDlg;
	m_pNextDlg		=	rhs.m_pNextDlg;

	m_bNonUserEvents	=	rhs.m_bNonUserEvents;
	m_bKeyboardInput	=	rhs.m_bKeyboardInput;
	m_bMouseInput		=	rhs.m_bMouseInput;
	*/

}
//------------------------------------------------------------------------------------------
CPUIDlg&	CPUIDlg::operator=( const CPUIDlg &rhs )
{
	m_nDefaultCtrlID	=	rhs.m_nDefaultCtrlID;

	m_nPosX		=	rhs.m_nPosX;
	m_nPosY		=	rhs.m_nPosY;
	m_nWidth	=	rhs.m_nWidth;
	m_nHeight	=	rhs.m_nHeight;

	m_bVisible	=	rhs.m_bVisible;
	m_bDrag		=	rhs.m_bDrag;

	stt_dRefreshTime	=	rhs.stt_dRefreshTime;
	m_dLastRefreshTime	=	rhs.m_dLastRefreshTime;

	stt_pCtrlFocus		=	rhs.stt_pCtrlFocus;
	stt_pCtrlPressed	=	rhs.stt_pCtrlPressed;
	m_pCtrlMouseIn		=	rhs.m_pCtrlMouseIn;

	m_colLT	=	rhs.m_colLT;
	m_colRT	=	rhs.m_colRT;
	m_colLB	=	rhs.m_colLB;
	m_colRB	=	rhs.m_colRB;

	m_pResMgr			=	rhs.m_pResMgr;
	m_pCallbackEvent	=	rhs.m_pCallbackEvent;
	m_pCallbackEventUserContext		=	rhs.m_pCallbackEventUserContext;

	m_TexIDs	=	rhs.m_TexIDs;
	m_FontIDs	=	rhs.m_FontIDs;

	m_Ctrls		=	rhs.m_Ctrls;
	m_DefaultElements	=	rhs.m_DefaultElements;

	m_bShowDlgRect		=	rhs.m_bShowDlgRect;
	m_SkinElements		=	rhs.m_SkinElements;

	m_pPrevDlg		=	rhs.m_pPrevDlg;
	m_pNextDlg		=	rhs.m_pNextDlg;

	m_bNonUserEvents	=	rhs.m_bNonUserEvents;
	m_bKeyboardInput	=	rhs.m_bKeyboardInput;
	m_bMouseInput		=	rhs.m_bMouseInput;

	return *this;
}
//------------------------------------------------------------------------------------------
void	CPUIDlg::InitMembers()
{
	m_nPosX				=	0;
	m_nPosY				=	0;
	m_nWidth			=	0;
	m_nHeight			=	0;

	m_pResMgr			=	NULL;
	m_bVisible			=	true;
	m_bDrag				=	false;
	m_bShowDlgRect		=	false;

	m_colLB				=	0;
	m_colLT				=	0;
	m_colRB				=	0;
	m_colRT				=	0;

	m_pCallbackEvent	=	NULL;
	m_pCallbackEventUserContext	=	NULL;

	m_dLastRefreshTime	=	0;
	m_pCtrlMouseIn		=	NULL;

	m_pNextDlg			=	this;
	m_pPrevDlg			=	this;

	m_nDefaultCtrlID	=	0xffff;
	m_bNonUserEvents	=	false;
	m_bKeyboardInput	=	false;
	m_bMouseInput		=	true;
}//	InitMembers
//------------------------------------------------------------------------------------------
void	CPUIDlg::ClearMembers()
{
	RemoveAllCtrls();

	m_FontIDs.DeleteAll();
	m_TexIDs.DeleteAll();

	m_DefaultElements.DeleteAll();
	m_SkinElements.DeleteAll();
}//	ClearMembers
//------------------------------------------------------------------------------------------
void	CPUIDlg::Init(	int nSkinID,
						bool bRegisterDlg )
{	
	if( bRegisterDlg )
		m_pResMgr->RegisterDlg( this );

	SetTex( 0, MAKEINTRESOURCEW( 0xffff ), (HMODULE)0xffff );
	InitDefaultElements();

	if( nSkinID > -1 )
	{
		CUSTOMSKINELEARR* pSkinEleArr	=	m_pResMgr->GetCustomSkinElement( nSkinID );
		if( pSkinEleArr )
		{
			CUSTOMSKINELEARRITER	iterCurSkin	=	pSkinEleArr->begin();
			for( size_t unCur = 0; unCur < pSkinEleArr->size(); ++unCur, ++iterCurSkin )
			{
				CPUIElement pEle = (*iterCurSkin);
				SetSkinElement( unCur, &pEle );
			}

		}//	if( pSkinEleArr )
		
	}//	if( nSkinID > -1 )

}//	Init(	
 //			int nSkinID,
 //			bool bRegisterDlg )
//------------------------------------------------------------------------------------------
void	CPUIDlg::Init(	int nSkinID, 
						bool bRegisterDlg, 
						const WCHAR* ptszCtrlTextureFileName )
{	
	if( bRegisterDlg )
		m_pResMgr->RegisterDlg( this );
	SetTex( 0, ptszCtrlTextureFileName );
	InitDefaultElements();

	if( nSkinID > -1 )
	{
		CUSTOMSKINELEARR* pSkinEleArr	=	m_pResMgr->GetCustomSkinElement( nSkinID );
		if( pSkinEleArr )
		{
			CUSTOMSKINELEARRITER	iterCurSkin	=	pSkinEleArr->begin();
			for( size_t unCur = 0; unCur < pSkinEleArr->size(); ++unCur, ++iterCurSkin )
			{
				CPUIElement pEle = (*iterCurSkin);
				SetSkinElement( unCur, &pEle );
			}

		}//	if( pSkinEleArr )

	}//	if( nSkinID > -1 )

}//	Init(	
 //			int nSkinID, 
 //			bool bRegisterDlg, 
 //			const WCHAR* ptszCtrlTextureFileName )
//------------------------------------------------------------------------------------------
void	CPUIDlg::Init(	int nSkinID, 
						bool bRegisterDlg, 
						const WCHAR* ptszCtrlTextureFileName, 
						HMODULE hCtrlTextureResModule )
{	
	if( bRegisterDlg )
		m_pResMgr->RegisterDlg( this );

	SetTex( 0, ptszCtrlTextureFileName, hCtrlTextureResModule );
	InitDefaultElements();

	if( nSkinID > -1 )
	{
		CUSTOMSKINELEARR*	pSkinEleArr	=	m_pResMgr->GetCustomSkinElement( nSkinID );
		if( pSkinEleArr )
		{
			CUSTOMSKINELEARRITER	iterCurSkin	=	pSkinEleArr->begin();
			for( size_t unCur = 0; unCur < pSkinEleArr->size(); ++unCur, ++iterCurSkin )
			{
				CPUIElement pEle = (*iterCurSkin);
				SetSkinElement( unCur, &pEle );
			}

		}//	if( pSkinEleArr )

	}//	if( nSkinID > -1 )
}//	Init(	
//			int nSkinID, 
 //			bool bRegisterDlg, 
 //			const WCHAR* ptszCtrlTextureFileName, 
 //			HMODULE hCtrlTextureResModule )
//------------------------------------------------------------------------------------------
void	CPUIDlg::SetCallBack( PCALLBACKUIEVENT pCallBack, void* pUserContext /* = NULL */ )
{	
	assert( m_pResMgr != NULL && PUT_CSTR_TCHAR("CPUIDlg::Init()를 먼저 호출 할 것.\n" ) );

	m_pCallbackEvent			=	pCallBack;
	m_pCallbackEventUserContext	=	pUserContext;	
}//	SetCallBack
//------------------------------------------------------------------------------------------
HRESULT	CPUIDlg::InitCtrl( CPUICtrl* pCtrl )
{
	HRESULT hr;

	if( pCtrl == NULL )
		return E_INVALIDARG;

	pCtrl->SetID( GetCtrlSize() );

	for( size_t nCur = 0; nCur < GetDefEleSize(); ++nCur )
	{
		CPUIElementHolder	*pEleHolder	=	m_DefaultElements.Find(nCur);
		if( pEleHolder->unCtrlType == pCtrl->GetType() )
			pCtrl->SetElement( pEleHolder->unIDx, &pEleHolder->Element );
	}

	hr = pCtrl->Init();
	if( FAILED( hr ) )
	{
		PUTOutputDebugStr( PUT_CSTR_TCHAR("CPUIDlg::InitCtrl()") );
		return E_FAIL;
	}

	return S_OK;

}//	InitCtrl
//------------------------------------------------------------------------------------------
HRESULT	CPUIDlg::AddCtrl( CPUICtrl *pCtrl, int nSkinID )
{
	HRESULT  hr = S_OK;

	hr = InitCtrl( pCtrl );
	if( FAILED( hr ) )
	{
		PUT_SAFE_DELETE( pCtrl );
		PUTOutputDebugStr( PUT_CSTR_TCHAR("CPUIDlg::AddCtrl()") );
		return E_FAIL;
	}

	m_Ctrls.Add( pCtrl );

	if( nSkinID > -1 )
	{
		CUSTOMSKINELEARR *pSkinEleArray	= m_pResMgr->GetCustomSkinElement( nSkinID );
		if( pSkinEleArray )
		{
			for( size_t nCur = 0; nCur < pSkinEleArray->size(); ++nCur )
			{
				pCtrl->SetCustomSkinElement( nCur, &(*pSkinEleArray)[nCur] );
			}
#ifndef _REMOVE_ORIGINAL_RENDER_
			pCtrl->SetCustomSkinEnable( true );
#endif
		}
	}

	return S_OK;

}//	AddCtrl
//------------------------------------------------------------------------------------------
void	CPUIDlg::RemoveCtrl( int nID )
{
	for( size_t unCur = 0; unCur < m_Ctrls.GetSize(); ++unCur )
	{
		CPUICtrl*	pCtrl	=	m_Ctrls.Find(unCur);

		if( pCtrl->GetID() == nID )
		{
			ClearFocus();

			if( stt_pCtrlFocus == pCtrl )
				stt_pCtrlFocus = NULL;

			if( stt_pCtrlPressed == pCtrl )
				stt_pCtrlPressed = NULL;

			if( m_pCtrlMouseIn == pCtrl )
				m_pCtrlMouseIn = NULL;

			PUT_SAFE_DELETE( pCtrl );
			m_Ctrls.Delete( unCur );

			return;

		}//	if( pCtrl->GetID() == nID )

	}//	for( size_t unCur = 0; unCur < m_Ctrls.GetSize(); ++unCur )

}//	RemoveCtrl
//------------------------------------------------------------------------------------------
void	CPUIDlg::RemoveAllCtrls()
{
	if( stt_pCtrlFocus && stt_pCtrlFocus->IsSameDlg(this) )
		stt_pCtrlFocus = NULL;

	if( stt_pCtrlPressed && stt_pCtrlPressed->IsSameDlg(this) )
		stt_pCtrlPressed = NULL;

	m_pCtrlMouseIn	=	NULL;

	m_Ctrls.DeleteAll();

}//	RemoveAllCtrls
//------------------------------------------------------------------------------------------
HRESULT	CPUIDlg::AddButton(	int nID, 
								const WCHAR* ptszText, 
								int nPosX, int nPosY, 
								int nWid, int nHei,
								int nSkinID, UINT unHotKey, 
								bool bIsDefault, 
								CPUIButton** ppCreated )
{
	HRESULT	hr = S_OK;

	CPUIButton	*pButton	=	NULL;
	PUTNEW( pButton, CPUIButton(this) );

	if( ppCreated != NULL )
		*ppCreated	=	pButton;

	if( pButton == NULL )
		return E_OUTOFMEMORY;

	hr = AddCtrl( pButton, nSkinID );
	if( FAILED( hr ) )
		return hr;

	pButton->SetID( nID );
	pButton->SetText( ptszText );
	pButton->SetPos( nPosX, nPosY );
	pButton->SetSize( nWid, nHei );
	pButton->SetHotkey( unHotKey );
	pButton->SetDefaultEnable( bIsDefault );

	return S_OK;

}//	AddButton
//------------------------------------------------------------------------------------------
HRESULT	CPUIDlg::AddIMEEditBox(	int nID, 
								const WCHAR* ptszText,
								int nPosX, int nPosY, int nWid, int nHei,
								int nSkinID, bool bIsDefault, 
								CPUIIMEEditBox** ppCreated )
{
	HRESULT	hr	=	S_OK;
	CPUIIMEEditBox	*pEditBox = NULL;
	PUTNEW( pEditBox, CPUIIMEEditBox( this ) );

	if( ppCreated != NULL )
		*ppCreated = pEditBox;

	if( pEditBox == NULL )
		return E_OUTOFMEMORY;

	hr = AddCtrl( pEditBox, nSkinID );
	if( FAILED( hr ) )
		return hr;

	pEditBox->SetID( nID );
	pEditBox->SetPos( nPosX, nPosY );
	pEditBox->SetSize( nWid, nHei );
	pEditBox->SetDefaultEnable( bIsDefault );

	if( ptszText )
		pEditBox->SetText( ptszText );

	return S_OK;

}//	AddIMEEditBox
//------------------------------------------------------------------------------------------
HRESULT	CPUIDlg::AddListBox(	int nID, 
								int nPosX, int nPosY, 
								int nWid, int nHei, 
								int nSkinID, int nScrollBarSkinID, 
								DWORD dwStyle, 
								CPUIListBox** ppCreated )
{
	HRESULT	hr = S_OK;
	CPUIListBox	*pListBox	=	NULL;
	PUTNEW( pListBox, CPUIListBox( this ) );

	if( ppCreated != NULL )
		*ppCreated = pListBox;

	if( pListBox == NULL )
		return E_OUTOFMEMORY;

	hr = AddCtrl( pListBox, nSkinID );
	if( FAILED( hr ) )
		return hr;

	pListBox->SetID( nID );
	pListBox->SetPos( nPosX, nPosY );
	pListBox->SetSize( nWid, nHei );
	pListBox->SetStyle( (CPUIListBox::eLISTBOXTYPE_)dwStyle );

	CPUIScrollBar	*pScrollBar	=	pListBox->GetScrollBar();

	if( nScrollBarSkinID > -1 )
	{
		CUSTOMSKINELEARR *pSkinEleArr	=	m_pResMgr->GetCustomSkinElement( nScrollBarSkinID );

		if( pSkinEleArr )
		{
			for( size_t unCur = 0; unCur < pSkinEleArr->size(); ++unCur )
			{
				pScrollBar->SetCustomSkinElement( unCur, &(*pSkinEleArr)[unCur] );
			}

#ifndef _REMOVE_ORIGINAL_RENDER_
			pScrollBar->SetCustomSkinEnable( true );
#endif

		}//	if( pSkinEleArr )

	}//	if( nScrollBarSkinID > -1 )

	return S_OK;

}//	AddListBox
//------------------------------------------------------------------------------------------
HRESULT	CPUIDlg::AddStatic(	int nID, 
							const WCHAR* ptszText, 				 
							int nPosX, int nPosY, 
							int nWid, int nHei,
							int nSkinID, 
							bool bIsDefault, 
							CPUIStatic** ppCreated )
{
	HRESULT	hr	=	S_OK;
	CPUIStatic	*pStatic	=	NULL;
	PUTNEW( pStatic, CPUIStatic( this ) );

	if( ppCreated != NULL )
		*ppCreated	=	pStatic;

	if( pStatic == NULL )
		return E_OUTOFMEMORY;

	hr = AddCtrl( pStatic, nSkinID );
	if( FAILED( hr ) )
		return hr;

	pStatic->SetID( nID );
	pStatic->SetText( ptszText );
	pStatic->SetPos( nPosX, nPosY );
	pStatic->SetSize( nWid, nHei );
	pStatic->SetDefaultEnable( bIsDefault );
	
	return S_OK;

}//	AddStatic
 //------------------------------------------------------------------------------------------
HRESULT	CPUIDlg::AddCheckBox(	int nID, 
								const WCHAR* ptszText, 
								int nPosX, int nPosY, 
								int nWid, int nHei,
								int nSkinID, 
								bool bChecked,
								UINT unHotKey,
								bool bIsDefault, 
								CPUICheckBox** ppCreated )
{
	HRESULT hr	=	S_OK;
	CPUICheckBox	*pCheckBox	=	NULL;
	PUTNEW( pCheckBox, CPUICheckBox( this ) );

	if( ppCreated != NULL )
		*ppCreated = pCheckBox;

	if( pCheckBox == NULL )
		return E_OUTOFMEMORY;

	hr = AddCtrl( pCheckBox, nSkinID );
	if( FAILED( hr ) )
		return hr;

	pCheckBox->SetID( nID );
	pCheckBox->SetText( ptszText );
	pCheckBox->SetPos( nPosX, nPosY );
	pCheckBox->SetSize( nWid, nHei );
	pCheckBox->SetHotkey( unHotKey );
	pCheckBox->SetDefaultEnable( bIsDefault );
	pCheckBox->SetCheck( bChecked );

	return S_OK;

}//	AddCheckBox
//------------------------------------------------------------------------------------------
HRESULT	CPUIDlg::AddRadioButton(	int nID, 
									UINT unButtonGroup,	
									const WCHAR* ptszText, 
									int nPosX, int nPosY, 
									int nWid, int nHei,
									int nSkinID, 
									bool bChecked,
									UINT unHotKey, 
									bool bIsDefault,
									CPUIRadioButton** ppCreated )
{
	HRESULT hr = S_OK;
	CPUIRadioButton	*pRadioButton	=	NULL;
	PUTNEW( pRadioButton, CPUIRadioButton( this ) );

	if( ppCreated != NULL )
		*ppCreated = pRadioButton;

	if( pRadioButton == NULL )
		return E_OUTOFMEMORY;

	hr = AddCtrl( pRadioButton, nSkinID );
	if( FAILED( hr ) )
		return hr;

	pRadioButton->SetID( nID );
	pRadioButton->SetText( ptszText );
	pRadioButton->SetButtonGroup( unButtonGroup );
	pRadioButton->SetPos( nPosX, nPosY );
	pRadioButton->SetSize( nWid, nHei );
	pRadioButton->SetHotkey( unHotKey );
	pRadioButton->SetCheck( bChecked );
	pRadioButton->SetDefaultEnable( bIsDefault );
	
	return S_OK;

}//	AddRadioButton
//------------------------------------------------------------------------------------------
HRESULT	CPUIDlg::AddComboBox(	int nID, 
								int nPosX,	int nPosY, 
								int nWid,	int nHei,
								int nSkinID, int nScrollBarSkinID,
								UINT unHotKey, bool bIsDefault,
								CPUIComboBox** ppCreated )
{
	HRESULT hr	=	S_OK;
	CPUIComboBox	*pComboBox	=	NULL;
	PUTNEW( pComboBox, CPUIComboBox( this ) );

	if( ppCreated != NULL )
		*ppCreated	=	pComboBox;

	if( pComboBox == NULL )
		return E_OUTOFMEMORY;

	hr	=	AddCtrl( pComboBox, nSkinID );
	if( FAILED( hr ) )
		return hr;

	pComboBox->SetID( nID );
	pComboBox->SetPos( nPosX, nPosY );
	pComboBox->SetSize( nWid, nHei );
	pComboBox->SetHotkey( unHotKey );
	pComboBox->SetDefaultEnable( bIsDefault );

	CPUIScrollBar	*pScrollBar	=	pComboBox->GetScrollBar();

	if( nScrollBarSkinID > -1 )
	{
		CUSTOMSKINELEARR	*pSkinEleArr	=	m_pResMgr->GetCustomSkinElement( nScrollBarSkinID );
		if( pSkinEleArr )
		{
			for( size_t unCur = 0; unCur < pSkinEleArr->size(); ++unCur )
			{
				pScrollBar->SetCustomSkinElement( unCur, &(*pSkinEleArr)[unCur] );
			}
#ifndef _REMOVE_ORIGINAL_RENDER_
			pScrollBar->SetCustomSkinEnable( true );
#endif
		}
	}

	return S_OK;
	
}//	AddComboBox
//------------------------------------------------------------------------------------------
//HRESULT	CPUIDlg::AddSlider(	int nID,
//								int nPosX, int nPosY, 
//								int nWid, int nHei,
//								int nSkinID, 
//								int nMin, int nMax,
//								int nVal, 
//								bool bIsDefault, 
//								CPUISlider** ppCreated )
HRESULT	CPUIDlg::AddSlider(	int nID,
						   int nPosX, int nPosY, 
						   int nWid, int nHei,
						   int nSkinID, 						   
						   int nVal, 
						   bool bIsDefault, 
						   CPUISlider** ppCreated )
{
	HRESULT	hr	=	S_OK;
	CPUISlider	*pSlider	=	NULL;
	PUTNEW( pSlider, CPUISlider( this ) );

	if( ppCreated != NULL )
		*ppCreated	=	pSlider;

	if( pSlider == NULL )
		return E_OUTOFMEMORY;

	hr	=	AddCtrl( pSlider, nSkinID );
	if( FAILED( hr ) )
		return hr;

	pSlider->SetID( nID );
	pSlider->SetPos( nPosX, nPosY );
	pSlider->SetSize( nWid, nHei );
	pSlider->SetDefaultEnable( bIsDefault );
	pSlider->SetRange( 0, nWid );
	pSlider->SetVal( nVal );
	pSlider->UpdateRects();

	return S_OK;

}//	AddSlider
//------------------------------------------------------------------------------------------
HRESULT	CPUIDlg::AddEditBox(	int nID, 
								const WCHAR* ptszText,								
								int nPosX,	int nPosY, 
								int nWid,	int nHei,
								int nSkinID,
								bool bIsDefault,
								CPUIEditBox** ppCreated )
{
	HRESULT	hr	=	S_OK;
	CPUIEditBox	*pEditBox	=	NULL;
	PUTNEW( pEditBox, CPUIEditBox( this ) );

	if( ppCreated != NULL )
		*ppCreated	=	pEditBox;

	if( pEditBox == NULL )
		return E_OUTOFMEMORY;

	hr	=	AddCtrl( pEditBox, nSkinID );
	if( FAILED( hr ) )
		return hr;

	pEditBox->SetID( nID );
	pEditBox->SetPos( nPosX, nPosY );
	pEditBox->SetSize( nWid, nHei );
	pEditBox->SetDefaultEnable( bIsDefault );

	if( ptszText )
		pEditBox->SetText( ptszText );


	return S_OK;

}//	AddEditBox
//------------------------------------------------------------------------------------------
void	CPUIDlg::Refresh()
{
	if( stt_pCtrlFocus )
		stt_pCtrlFocus->OnFocusOut( NULL );

	if( m_pCtrlMouseIn )
		m_pCtrlMouseIn->SetMouseInRect( false );

	stt_pCtrlFocus		=	NULL;
	stt_pCtrlPressed	=	NULL;
	m_pCtrlMouseIn		=	NULL;

	for( size_t unCur = 0; unCur < m_Ctrls.GetSize(); ++unCur )
	{
		CPUICtrl*	pCtrl	=	m_Ctrls.Find( unCur );
		pCtrl->Refresh();
	}

	if( m_bKeyboardInput )
		FocusDefaultCtrl();

}//	Refresh
//------------------------------------------------------------------------------------------
HRESULT		CPUIDlg::OnRender( PRLPD3DDEV9 pDev, float fElapsedTime )
{
	assert( m_pResMgr->GetDevice() && 
//			m_pResMgr->m_pStateBlock &&
			" CPUIDlgResourceMgr를 확인해보삼\n" );

	if( m_dLastRefreshTime < stt_dRefreshTime )
	{
		m_dLastRefreshTime	=	(double)gUtTimer->GetCurrentTime();
		Refresh();
	}

	if( !m_bVisible )
		return S_OK;

//	m_pResMgr->m_pStateBlock->Capture();

	/*devSetRS( pDev,	D3DRS_ALPHABLENDENABLE,			TRUE );
	devSetRS( pDev,	D3DRS_SRCBLEND,					D3DBLEND_SRCALPHA );
	devSetRS( pDev,	D3DRS_DESTBLEND,				D3DBLEND_INVSRCALPHA );*/

	devSetRSAlphaBlnd(	pDev, TRUE );	
	devSetRSSRCBlnd(	pDev, D3DBLEND_SRCALPHA );
	devSetRSDSTBlnd(	pDev, D3DBLEND_INVSRCALPHA );
//	devSetRS( pDev,	D3DRS_ALPHATESTENABLE,			FALSE );
	devSetRSAlphaTest( pDev, FALSE );
	devSetRS( pDev,	D3DRS_SEPARATEALPHABLENDENABLE,	FALSE );
	devSetRS( pDev,	D3DRS_BLENDOP,					D3DBLENDOP_ADD );
	devSetRS( pDev,	D3DRS_COLORWRITEENABLE,			D3DCOLORWRITEENABLE_ALPHA | D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_RED );
	devSetRS( pDev,	D3DRS_SHADEMODE,				D3DSHADE_GOURAUD );
	devSetRS( pDev,	D3DRS_FOGENABLE,				FALSE );
//	devSetRS( pDev,	D3DRS_ZWRITEENABLE,				FALSE );
	devSetRSZWriteEnable( pDev, FALSE );
//	devSetRS( pDev,	D3DRS_FILLMODE,					D3DFILL_SOLID );
//	devSetRS( pDev,	D3DRS_CULLMODE,					D3DCULL_CCW );
	devSetRSCullMode( pDev, D3DCULL_CCW );

//	devSetTSS( pDev, 0,	D3DTSS_COLOROP,		D3DTOP_SELECTARG2 );
	devSetTSSCOLOROP( pDev, 0, D3DTOP_SELECTARG2 );
	devSetTSS( pDev, 0,	D3DTSS_COLORARG2,	D3DTA_DIFFUSE );
//	devSetTSS( pDev, 0,	D3DTSS_ALPHAOP,		D3DTOP_SELECTARG1 );
	devSetTSSAlphop( pDev, 0, D3DTOP_SELECTARG1 );
	devSetTSS( pDev, 0,	D3DTSS_ALPHAARG1,	D3DTA_DIFFUSE );
	devSetTSS( pDev, 0,	D3DTSS_RESULTARG,	D3DTA_CURRENT );
//	devSetTSS( pDev, 1,	D3DTSS_COLOROP,		D3DTOP_DISABLE );
	devSetTSSCOLOROP( pDev, 1, D3DTOP_DISABLE );
//	devSetTSS( pDev, 1,	D3DTSS_ALPHAOP,		D3DTOP_DISABLE );
	devSetTSSAlphop( pDev, 1, D3DTOP_DISABLE );

	BOOL	bBackGroundVisible	=	( m_colLT | m_colRT | m_colLB | m_colRB ) & 0xff000000;

	if( bBackGroundVisible )
	{
		sPRVtx_XyzRhw_Diff	vertice[4];
		PUT_ZERO_MEMORY( vertice );
		SetVtxInfoXyzrhwDiff( &vertice[0], D3DXVECTOR4( (float)m_nPosX,			(float)m_nPosY,				0.5f,	1.0f ), m_colLT );
		SetVtxInfoXyzrhwDiff( &vertice[1], D3DXVECTOR4( (float)m_nPosX+m_nWidth,	(float)m_nPosY,				0.5f,	1.0f ),	m_colRT );		
		SetVtxInfoXyzrhwDiff( &vertice[2], D3DXVECTOR4( (float)m_nPosX+m_nWidth,	(float)m_nPosY+m_nHeight,	0.5f,	1.0f ),	m_colRB );
		SetVtxInfoXyzrhwDiff( &vertice[3], D3DXVECTOR4( (float)m_nPosX,			(float)m_nPosY+m_nHeight,	0.5f,	1.0f ),	m_colLB );

		devSetVtxShader( pDev, NULL );
		devSetPxShader( pDev, NULL );

		devSetRS( pDev, D3DRS_ZENABLE, FALSE );
		devSetFVF( pDev, sPRVtx_XyzRhw_Diff::FVF );
		devDrawPUP( pDev, D3DPT_TRIANGLEFAN, 2, vertice, sizeof( sPRVtx_XyzRhw_Diff ) );
		devSetRS( pDev, D3DRS_ZENABLE, TRUE );
	
	}//	if( bBackGroundVisible )

//	devSetTSS( pDev, 0, D3DTSS_COLOROP,	D3DTOP_MODULATE );
	devSetTSSCOLOROP( pDev, 0, D3DTOP_MODULATE );
	devSetTSS( pDev, 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	devSetTSS( pDev, 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

//	devSetTSS( pDev, 0, D3DTSS_ALPHAOP,	D3DTOP_MODULATE );
	devSetTSSAlphop( pDev, 0, D3DTOP_MODULATE );	
	devSetTSS( pDev, 0, D3DTSS_ALPHAARG1,	D3DTA_TEXTURE );
	devSetTSS( pDev, 0, D3DTSS_ALPHAARG2,	D3DTA_DIFFUSE );

//	devSetSmpSMINFilter( pDev, 0, D3DTEXF_LINEAR );
	devSetSmpSFilters( pDev, 0, D3DTEXF_LINEAR );

	m_pResMgr->m_pSprite->Begin( D3DXSPRITE_ALPHABLEND );

	CPUIElement*	pElement	=	GetSkinElement( eSKINTYPE_DIALOG_BACKGROUND );
	if( pElement )
	{
		RECT	rcDlg;
		rcDlg.left		=	m_nPosX;
		rcDlg.top		=	m_nPosY;
		rcDlg.right		=	m_nPosX + m_nWidth;
		rcDlg.bottom	=	m_nPosY + m_nHeight;

		pElement->GetTexColor().Blend( eCTRLSTATE_NORMAL, fElapsedTime, 0.0f );
		pElement->GetFontColor().Blend( eCTRLSTATE_NORMAL, fElapsedTime, 0.0f );

		DrawSkinSprite( pElement, &rcDlg );

	}//	if( pElement )


	if( m_bShowDlgRect )
	{
		RECT	rcDlg;
		rcDlg.left		=	0;
		rcDlg.top		=	0;
		rcDlg.right		=	m_nWidth;
		rcDlg.bottom	=	m_nHeight;
		DrawRect( &rcDlg, D3DCOLOR_RGBA( 40, 40, 40, 128 ) );

	}//	if( m_bShowDlgRect )


	for( size_t unCur = 0; unCur < m_Ctrls.GetSize(); ++unCur )
	{
		CPUICtrl*	pCtrl	=	m_Ctrls.Find(unCur);

		if( pCtrl == stt_pCtrlFocus )
			continue;

		pCtrl->OnRender( pDev, fElapsedTime );

	}//	for( size_t unCur = 0; unCur < m_Ctrls.GetSize(); ++unCur )


	if( stt_pCtrlFocus != NULL &&
		stt_pCtrlFocus->IsSameDlg(this) )
		stt_pCtrlFocus->OnRender( pDev, fElapsedTime );

	m_pResMgr->m_pSprite->End();

//	m_pResMgr->m_pStateBlock->Apply();

//	devSetRS(	pDev,	D3DRS_ZWRITEENABLE,	TRUE );
	return S_OK;

}//	Render
//------------------------------------------------------------------------------------------
HRESULT		CPUIDlg::SetFont( UINT unID, const WCHAR* ptszFaceName, long lHeight, long lWeight )
{
	assert( m_pResMgr != NULL && 
		PUT_CSTR_TCHAR("CPUIDlg::Init()를 먼저 호출했는지 확인해보삼\n") );

	
	for( UINT unCur = m_FontIDs.GetSize(); unCur <= unID; ++unCur )
		m_FontIDs.Add( -1 );

	int nFont	=	m_pResMgr->AddFont( ptszFaceName, lHeight, lWeight );
	m_FontIDs.Insert( unID, nFont );

	return S_OK;

}//	SetFont
//------------------------------------------------------------------------------------------
CPUIFontNode*	CPUIDlg::GetFont( UINT unID )
{
	if( !m_pResMgr )
		return NULL;

	return m_pResMgr->GetFontNode( m_FontIDs.Find( unID ) );

}//	GetFont
//------------------------------------------------------------------------------------------
CPUIFontNode*	CPUIDlg::GetFontFromManager( UINT unID )
{
	if( !m_pResMgr )
		return NULL;

	return m_pResMgr->GetFontNode( unID );

}//	GetFontFromManager
//------------------------------------------------------------------------------------------
HRESULT		CPUIDlg::SetTex( UINT unID, const WCHAR* ptszFileName )
{
	assert( m_pResMgr != NULL && PUT_CSTR_TCHAR("CPUIDlg::Init() 먼저 호출 확인\n") );

	for( size_t unCur = m_TexIDs.GetSize(); unCur <= unID; ++unCur )
		m_TexIDs.Add( -1 );

	int nTexture	=	m_pResMgr->AddTex( ptszFileName );

	m_TexIDs.Insert( unID, nTexture );

	return S_OK;

}//	SetTex( UINT unID, 
 //				const WCHAR* ptszFileName )
//------------------------------------------------------------------------------------------
HRESULT		CPUIDlg::SetTex( UINT unID, const WCHAR* ptszResName, HMODULE hResourceModule )
{
	assert( m_pResMgr !=0 &&
		PUT_CSTR_TCHAR("CPUIDlg::Init() 먼저 호출 확인\n") );

	for( size_t unCur = m_TexIDs.GetSize(); unCur <= unID; ++unCur )
		m_TexIDs.Add( -1 );

	int nTexture	=	m_pResMgr->AddTex( ptszResName, hResourceModule );

	m_TexIDs.Insert( unID, nTexture );

	return S_OK;

}//	SetTex( UINT unID, 
 //				const WCHAR* ptszResName, 
 //				HMODULE hResourceModule )
//------------------------------------------------------------------------------------------
CPUITexNode*	CPUIDlg::GetTex( UINT unID )
{
	if( !m_pResMgr )
		return NULL;

	return m_pResMgr->GetTexNode( m_TexIDs.Find(unID) );

}//	GetTex
//------------------------------------------------------------------------------------------
void	CPUIDlg::SendEvent( UINT unEvent, bool bTriggeredByUser, CPUICtrl* pCtrl )
{
	if( !m_pCallbackEvent )
		return;

	if( !bTriggeredByUser && !m_bNonUserEvents )
		return;

	m_pCallbackEvent( unEvent, pCtrl->GetID(), pCtrl, m_pCallbackEventUserContext );

}//	SendEvent
//------------------------------------------------------------------------------------------
int		CPUIDlg::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	POINT	ptMousePos	=	{ -1, -1 };

	bool	bHandled	=	false;

	if( !m_bVisible )
		return eMSGVAL_NOTHANDLED;

	if( ( WM_LBUTTONDOWN == uMsg || WM_LBUTTONDBLCLK == uMsg || WM_KEYDOWN == uMsg ) )
		m_pResMgr->EnableKeyboardInputForAllDlgs();

	if( stt_pCtrlFocus &&
		stt_pCtrlFocus->IsSameDlg(this) &&
		stt_pCtrlFocus->IsEnable() )
	{
		if( stt_pCtrlFocus->MsgProc( hWnd, uMsg, wParam, lParam ) )
			return eMSGVAL_HANDLED;
	}


	switch( uMsg )
	{
	case WM_SIZE:
	case WM_MOVE:
		{
			POINT	pt	=	{ -1, -1 };
			OnMouseMove( pt );
		}//	WM_SIZE
		 // WM_MOVE
		break;


	case WM_ACTIVATEAPP:
		{
			if( stt_pCtrlFocus &&
				stt_pCtrlFocus->IsSameDlg(this) &&
				stt_pCtrlFocus->IsEnable() )
			{
				if( wParam )
					stt_pCtrlFocus->OnFocusIn(hWnd);
				else
					stt_pCtrlFocus->OnFocusOut(hWnd);
			}

		}//	WM_ACTIVATEAPP
		break;


	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		{

			//	HandleKeyboard ------------------------------------
			if( stt_pCtrlFocus &&
				stt_pCtrlFocus->IsSameDlg(this) &&
				stt_pCtrlFocus->IsEnable() )
			{
				if( stt_pCtrlFocus->HandleKeyboard( hWnd, uMsg, wParam, lParam ) )
					return eMSGVAL_HANDLED;
			}
			//	-------------------------------- HandleKeyboard ---


			//	OnHotKey ------------------------------------------
			if( WM_KEYDOWN == uMsg &&
				(	!stt_pCtrlFocus || 
				(	
					!stt_pCtrlFocus->IsSameType( eCTRLTYPE_EDITBOX ) &&
					!stt_pCtrlFocus->IsSameType( eCTRLTYPE_IMEEDITBOX ) 
				) 
				) )
			{
				for( size_t unCur = 0; unCur < m_Ctrls.GetSize(); ++unCur )
				{
					CPUICtrl*	pCtrl	=	m_Ctrls.Find(unCur);
					if( pCtrl->GetHotkey() == wParam )
					{
						pCtrl->OnHotKey();
						return eMSGVAL_HANDLED;
					}
				}
			}
			//	-------------------------------------- OnHotKey ---



			//	OnCycleFocus --------------------------------------
			if( WM_KEYDOWN == uMsg )
			{
				if( !m_bKeyboardInput )
					return eMSGVAL_NOTHANDLED;

				switch( wParam )
				{
				case VK_RIGHT:
				case VK_DOWN:
					{
						if( stt_pCtrlFocus )						
							return OnCycleFocus( true );						

					}//	VK_RIGHT
					 //	VK_DOWN
					break;

				case VK_LEFT:
				case VK_UP:
					{
						if( stt_pCtrlFocus )
							return OnCycleFocus( false );

					}//	VK_LEFT
					 //	VK_UP
					break;

				case VK_TAB:
					{
						bool	bShiftDown	=	( (GetKeyState( VK_SHIFT ) & 0x8000) != 0 );
						return	OnCycleFocus(bShiftDown);
					}//	VK_TAB
					break;

				}//	switch( wParam )

			}//	if( WM_KEYDOWN == uMsg )
			//	---------------------------------- OnCycleFocus ---

										


		}//	WM_KEYDOWN
		 // WM_SYSKEYDOWN
		 //	WM_KEYUP
		 //	WM_SYSKEYUP
		break;


	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_LBUTTONDBLCLK:
	case WM_MBUTTONDBLCLK:
	case WM_RBUTTONDBLCLK:
//	case WM_XBUTTONDBLCLK:
	case WM_MOUSEWHEEL:
		{
			ptMousePos.x	=	short( LOWORD( lParam ) );
			ptMousePos.y	=	short( HIWORD( lParam ) );

			if( !m_bMouseInput )
				return eMSGVAL_HANDLED;

			POINT	ptMousePt	=	{ ptMousePos.x, ptMousePos.y };
			ptMousePt.x	-=	m_nPosX;
			ptMousePt.y	-=	m_nPosY;

			if( stt_pCtrlFocus &&
				stt_pCtrlFocus->IsSameDlg(this) &&
				stt_pCtrlFocus->IsEnable() )
			{
				if( stt_pCtrlFocus->HandleMouse( hWnd, uMsg, ptMousePt, wParam, lParam ) )
					return eMSGVAL_HANDLED;
			}

			CPUICtrl*	pCtrl	=	GetCtrlAtPoint( ptMousePt );
			if( pCtrl && pCtrl->IsEnable() )
			{
				bHandled	=	pCtrl->HandleMouse( hWnd, uMsg, ptMousePt, wParam, lParam );
				if( bHandled )
					return eMSGVAL_HANDLED;

			}//	if( pCtrl && pCtrl->IsEnable() )
			else
			{
				if( WM_LBUTTONDOWN == uMsg &&
					stt_pCtrlFocus	&&
					stt_pCtrlFocus->IsSameDlg(this) )
				{
					stt_pCtrlFocus->OnFocusOut(hWnd);
					stt_pCtrlFocus	=	NULL;
				}

			}//	~if( pCtrl && pCtrl->IsEnable() )

			switch( uMsg )
			{
				case WM_MOUSEMOVE:
					{
						OnMouseMove( ptMousePt );

						RECT	rcDlg;
						rcDlg.left		=	m_nPosX;
						rcDlg.top		=	m_nPosY;
						rcDlg.right		=	m_nPosX + m_nWidth;
						rcDlg.bottom	=	m_nPosY + m_nHeight;

						if( PtInRect( &rcDlg, ptMousePos ) )
							return eMSGVAL_MOUSE_IN;

						return eMSGVAL_NOTHANDLED;

					}//	WM_MOUSEMOVE
					break;

			}//	switch( uMsg )

		}	//	WM_MOUSEMOVE
			//	WM_LBUTTONDOWN
			//	WM_LBUTTONUP
			//	WM_MBUTTONDOWN
			//	WM_MBUTTONUP
			//	WM_RBUTTONDOWN
			//	WM_RBUTTONUP
			//	WM_XBUTTONDOWN
			//	WM_XBUTTONUP
			//	WM_LBUTTONDBLCLK
			//	WM_MBUTTONDBLCLK
			//	WM_RBUTTONDBLCLK
			//	WM_MOUSEWHEEL
		break;


	case WM_CAPTURECHANGED:
		{
			m_bDrag	=	false;
		}
		break;
		
	}//	switch( uMsg )

	return eMSGVAL_NOTHANDLED;

}//	MsgProc
//------------------------------------------------------------------------------------------
CPUICtrl*	CPUIDlg::GetCtrlAtPoint( POINT pt )
{
	for( UINT unCur = 0; unCur < m_Ctrls.GetSize(); ++unCur )
	{
		CPUICtrl*	pCtrl	=	m_Ctrls.Find(unCur);
		if( !pCtrl )
			continue;

		if( pCtrl->ContainsPoint( pt ) &&
			pCtrl->IsEnable() &&
			pCtrl->IsVisible() )
			return pCtrl;

	}//	for( UINT unCur = 0; unCur < m_Ctrls.GetSize(); ++unCur )

	return NULL;

}//	GetCtrlAtPoint
//------------------------------------------------------------------------------------------
bool	CPUIDlg::GetCtrlEnabled( int nID )
{
	CPUICtrl*	pCtrl	=	GetCtrl( nID );
	if( !pCtrl )
		return false;

	return pCtrl->IsEnable();

}//	GetCtrlEnabled
//------------------------------------------------------------------------------------------
void	CPUIDlg::SetCtrlEnabled( int nID, bool bEnable )
{
	CPUICtrl*	pCtrl	=	GetCtrl( nID );
	if( !pCtrl )
		return;

	pCtrl->SetEnable( bEnable );

}//	SetCtrlEnabled
//------------------------------------------------------------------------------------------
CPUICtrl*	CPUIDlg::GetCtrl( int nID )
{
	for( UINT unCur = 0; unCur < m_Ctrls.GetSize(); ++unCur )
	{
		CPUICtrl*	pCtrl	=	m_Ctrls.Find(unCur);

		if( pCtrl->IsSameID( nID ) )
			return pCtrl;

	}//	for( UINT unCur = 0; unCur < m_Ctrls.GetSize(); ++unCur )

	return NULL;

}//	GetCtrl( int nID )
//------------------------------------------------------------------------------------------
CPUICtrl*	CPUIDlg::GetCtrl( int nID, eCTRLTYPE_ eType )
{
	for( UINT unCur = 0; unCur < m_Ctrls.GetSize(); ++unCur )
	{
		CPUICtrl*	pCtrl	=	m_Ctrls.Find(unCur);

		if( pCtrl->IsSameID( nID ) &&
			pCtrl->IsSameType( eType ) )
			return pCtrl;
		
	}//	for( UINT unCur = 0; unCur < m_Ctrls.GetSize(); ++unCur )

	return NULL;

}//	GetCtrl( int nID, eCTRLTYPE_ eType )
//------------------------------------------------------------------------------------------
CPUICtrl*	CPUIDlg::GetNextCtrl( CPUICtrl* pCtrl )
{
	int nIdx	=	pCtrl->GetID() + 1;

	CPUIDlg*	pDlg	=	pCtrl->GetDlg();

	while( nIdx >= (int)pDlg->m_Ctrls.GetSize() )
	{
		pDlg	=	pDlg->m_pNextDlg;
		nIdx	=	0;
	}

	return pDlg->m_Ctrls.Find(nIdx);

}//	GetNextCtrl
//------------------------------------------------------------------------------------------
CPUICtrl*	CPUIDlg::GetPrevCtrl( CPUICtrl* pCtrl )
{
	int nIdx	=	pCtrl->GetID() - 1;
	CPUIDlg*	pDlg	=	pCtrl->GetDlg();

	while( nIdx < 0 )
	{
		pDlg	=	pDlg->m_pPrevDlg;
		if( !pDlg )
			pDlg	=	pCtrl->GetDlg();

		nIdx	=	pDlg->m_Ctrls.GetSize() - 1;
	}

	return pDlg->m_Ctrls.Find( nIdx );

}//	GetPrevCtrl
//------------------------------------------------------------------------------------------
void	CPUIDlg::ClearRadioButtonGroup( UINT unGroup )
{
	for( UINT unCur = 0; unCur < m_Ctrls.GetSize(); ++unCur )
	{
		CPUICtrl*	pCtrl	=	m_Ctrls.Find(unCur);

		if( pCtrl->IsSameType( eCTRLTYPE_RADIOBUTTON ) )
		{
			CPUIRadioButton*	pRadioButton	=	(CPUIRadioButton*)pCtrl;

			if( pRadioButton->GetButtonGroup() == unGroup )
				pRadioButton->SetCheck( false, false );

		}//	if( pCtrl->IsSameType( eCTRLTYPE_RADIOBUTTON ) )

	}//	for( UINT unCur = 0; unCur < m_Ctrls.GetSize(); ++unCur )

}//	ClearRadioButtonGroup
//------------------------------------------------------------------------------------------
void	CPUIDlg::ClearComboBox( int nID )
{
	CPUIComboBox*	pComboBox	=	GetComboBox( nID );
	if( !pComboBox )
		return;

	pComboBox->RemoveAllItems();

}//	ClearComboBox
//------------------------------------------------------------------------------------------
void	CPUIDlg::RequestFocus( CPUICtrl* pCtrl )
{
	if( stt_pCtrlFocus == pCtrl )
		return;

	if( !pCtrl->IsActive() )
		return;

	if( stt_pCtrlFocus )
		stt_pCtrlFocus->OnFocusOut();

	pCtrl->OnFocusIn();
	stt_pCtrlFocus	=	pCtrl;

}//	RequestFocus
//------------------------------------------------------------------------------------------
HRESULT		CPUIDlg::CalcTextRect( const WCHAR* ptszText, CPUIElement* pElement, RECT* prcDest, int nCount /* = -1 */ )
{
	HRESULT	hr	=	S_OK;

	CPUIFontNode*	pFontNode	=	GetFont( pElement->GetFontID() );
	if( !pFontNode )
		return E_FAIL;

	DWORD	dwTextFormat	=	pElement->GetTextFormat() | DT_CALCRECT;

	hr	=	pFontNode->m_pFont->DrawTextW( NULL, ptszText, nCount, prcDest, dwTextFormat, pElement->GetFontColor().GetCurrentColor() );

	if( FAILED( hr ) )
		return hr;

	return S_OK;

}//	CalcTextRect
//------------------------------------------------------------------------------------------
HRESULT		CPUIDlg::DrawText( const WCHAR* ptszText, CPUIElement* pElement, RECT* prcDest, bool bShadow /* = false */, int nCount /* = -1 */ )
{
	HRESULT	hr	=	S_OK;

	PUT_IsZero( pElement->GetFontColor().GetCurrentColor().a )
		return S_OK;

	RECT rtScreen	=	*prcDest;
	OffsetRect( &rtScreen, m_nPosX, m_nPosY );

	D3DXMATRIXA16	matTransform;
	D3DXMatrixIdentity( &matTransform );
	m_pResMgr->m_pSprite->SetTransform( &matTransform );

	CPUIFontNode* pFontNode	=	GetFont( pElement->GetFontID() );

	if( bShadow )
	{
		RECT rtShadow	=	rtScreen;
		OffsetRect( &rtScreen, 1, 1 );
		hr = pFontNode->m_pFont->DrawTextW(	m_pResMgr->m_pSprite,
											ptszText,
											nCount,
											&rtShadow,
											pElement->GetTextFormat(),
											D3DCOLOR_ARGB(DWORD(pElement->GetFontColor().GetCurrentColor().a * 255), 0, 0, 0 ) 
										);

		PUT_IsFailed( hr )
			return hr;

	}//	if( bShadow )

	hr = pFontNode->m_pFont->DrawTextW(	m_pResMgr->m_pSprite,
										ptszText,
										nCount,
										&rtScreen,
										pElement->GetTextFormat(),
										pElement->GetFontColor().GetCurrentColor()
									);
	PUT_IsFailed( hr )
		return hr;

	return S_OK;

}//	DrawText
//------------------------------------------------------------------------------------------
HRESULT	CPUIDlg::DrawSkinText( const WCHAR* ptszText, CPUIElement* pElement, RECT* prcDest, bool bShadow /* = false */, int nCount /* = -1 */ )
{
	HRESULT	hr	=	S_OK;

	PUT_IsZero( pElement->GetFontColor().GetCurrentColor().a )
		return S_OK;

	RECT rtScreen = *prcDest;
	OffsetRect( &rtScreen, m_nPosX, m_nPosY );

	D3DXMATRIXA16	matTransform;
	D3DXMatrixIdentity( &matTransform );
	m_pResMgr->m_pSprite->SetTransform( &matTransform );

	CPUIFontNode*	pFontNode	=	m_pResMgr->GetFontNode( pElement->GetFontID() );
	if( !pFontNode )
		return E_FAIL;

	if( bShadow )
	{
		RECT	rtShadow	=	rtScreen;
		OffsetRect( &rtScreen, 1, 1 );
		hr	=	pFontNode->m_pFont->DrawTextW(	m_pResMgr->m_pSprite,
												ptszText,
												nCount,
												&rtShadow,
												pElement->GetTextFormat(),
												D3DCOLOR_ARGB( DWORD(pElement->GetFontColor().GetCurrentColor().a * 255 ), 0, 0, 0 ) );

		PUT_IsFailed( hr )
			return hr;

	}//	if( bShadow )

	hr	=	pFontNode->m_pFont->DrawTextW(	m_pResMgr->m_pSprite,
											ptszText,
											nCount, 
											&rtScreen,
											pElement->GetTextFormat(),
											pElement->GetFontColor().GetCurrentColor()
										);

	PUT_IsFailed( hr )
		return hr;

	return S_OK;

}//	DrawSkinText
//------------------------------------------------------------------------------------------
void	CPUIDlg::SetBackgroundColors( D3DCOLOR colTL, D3DCOLOR colTR, D3DCOLOR colBL, D3DCOLOR colBR )
{
	m_colLB	=	colBL;
	m_colLT	=	colTL;
	m_colRB	=	colBR;
	m_colRT	=	colTR;

}//	SetBackgroundColors
//------------------------------------------------------------------------------------------
void	CPUIDlg::ClearFocus()
{
	if( stt_pCtrlFocus )
	{
		stt_pCtrlFocus->OnFocusOut();
		stt_pCtrlFocus	=	NULL;
	}

	ReleaseCapture();

}//	ClearFocus
//------------------------------------------------------------------------------------------
void	CPUIDlg::FocusDefaultCtrl()
{
	for( UINT unCur = 0; unCur < m_Ctrls.GetSize(); ++unCur )
	{
		CPUICtrl*	pCtrl	=	m_Ctrls.Find( unCur );

		if( pCtrl->IsDefaultEnable() )
		{
			ClearFocus();

			stt_pCtrlFocus	=	pCtrl;
			stt_pCtrlFocus->OnFocusIn();
			return;

		}//	if( pCtrl->IsDefaultEnable() )

	}//	for( UINT unCur = 0; unCur < m_Ctrls.GetSize(); ++unCur )

}//	FocusDefaultCtrl
//------------------------------------------------------------------------------------------
bool	CPUIDlg::OnCycleFocus( bool bForward )
{
	CPUICtrl*	pCtrl		=	NULL;
	CPUIDlg*	pDlg		=	NULL;
	CPUIDlg*	pLastDlg	=	NULL;

	if( !stt_pCtrlFocus )
	{
		if( bForward )
		{
			for( UINT unCur = 0; unCur < m_pResMgr->GetDlgMgr()->GetSize(); ++unCur )
			{
				pDlg	=	pLastDlg	=	m_pResMgr->GetDlgMgr()->Find(unCur);

				if( pDlg && pDlg->m_Ctrls.GetSize() > 0 )
				{
					pCtrl	=	pDlg->m_Ctrls.Find(unCur);
					break;

				}//	if( pDlg && pDlg->m_Ctrls.GetSize() > 0 )

			}//	for( UINT unCur = 0; unCur < m_pResMgr->GetDlgMgr()->GetSize(); ++unCur )

			if( !pDlg || !pCtrl )
				return true;

		}//	if( bForward )
		else
		{
			for( UINT unCur = m_pResMgr->GetDlgMgr()->GetSize() - 1; unCur >= 0; --unCur )
			{
				pDlg	=	pLastDlg	=	m_pResMgr->GetDlgMgr()->Find(unCur);
				if( pDlg &&
					pDlg->m_Ctrls.GetSize() > 0 )
				{
					pCtrl	=	pDlg->m_Ctrls.Find(pDlg->m_Ctrls.GetSize() - 1 );
					break;
				}

			}//	for( UINT unCur = m_pResMgr->m_DlgMgr.GetSize() - 1; unCur >= 0; --unCur )


			if( !pDlg || !pCtrl )
				return true;

		}//	~if( bForward )

	}//	if( !stt_pCtrlFocus )
	else
	{
		if( stt_pCtrlFocus->IsSameDlg( this ) )
			return false;
		else
		{
			pLastDlg	=	stt_pCtrlFocus->GetDlg();
			pCtrl	=	(bForward) ? GetNextCtrl( stt_pCtrlFocus ) : GetPrevCtrl( stt_pCtrlFocus );
			pDlg	=	pCtrl->GetDlg();
		}
	}//	~if( !stt_pCtrlFocus )

	for( int nCur = 0; nCur < 0xffff; ++nCur )
	{
		int	nLastDlgIdx	=	m_pResMgr->GetDlgMgr()->GetIDx( pLastDlg );
		int	nDlgIdx		=	m_pResMgr->GetDlgMgr()->GetIDx( pDlg );

		if( ( !bForward && nLastDlgIdx < nDlgIdx ) ||
			( bForward && nDlgIdx < nLastDlgIdx ) )
		{
			if( stt_pCtrlFocus )
				stt_pCtrlFocus->OnFocusOut();
			stt_pCtrlFocus	=	NULL;
			return true;
		}

		if( pCtrl == stt_pCtrlFocus )
			return true;

		if( pCtrl->GetDlg()->m_bKeyboardInput &&
			pCtrl->IsFocus() )
		{
			if( stt_pCtrlFocus )
				stt_pCtrlFocus->OnFocusOut();
			stt_pCtrlFocus	=	pCtrl;
			stt_pCtrlFocus->OnFocusIn();
			return true;
		}

		pLastDlg	=	pDlg;
		pCtrl		=	( bForward ) ? GetNextCtrl( pCtrl ) : GetPrevCtrl( pCtrl );
		pDlg		=	pCtrl->GetDlg();

	}//	for( int nCur = 0; nCur < 0xffff; ++nCur )

	return false;

}//	OnCycleFocus
//------------------------------------------------------------------------------------------
HRESULT	CPUIDlg::DrawSkinSprite( CPUIElement* pElement, RECT* prcDest )
{
	PUT_IsZero( pElement->GetTexColor().GetCurrentColor().a )
		return S_OK;

	RECT	rtTexture	=	pElement->GetTexRect();

	RECT	rtScreen	=	*prcDest;
	OffsetRect( &rtScreen, m_nPosX, m_nPosY );

	CPUITexNode*	pTextureNode	=	m_pResMgr->GetTexNode( pElement->GetTexID() );
	if( !pTextureNode )
		return E_FAIL;

	float	fScaleX	=	(float)RectWidth(rtScreen) / RectWidth(rtTexture);
	float	fScaleY	=	(float)RectHeight(rtScreen) / RectHeight(rtTexture);

	D3DXMATRIXA16	matTransform;
	D3DXMatrixScaling( &matTransform, fScaleX, fScaleY, 1.0f );

	m_pResMgr->m_pSprite->SetTransform( &matTransform );

	D3DXVECTOR3	vPos( (float)rtScreen.left, (float)rtScreen.top, 0.0f );

	vPos.x	/=	fScaleX;
	vPos.y	/=	fScaleY;

	return m_pResMgr->m_pSprite->Draw(	pTextureNode->m_pTex,
										&rtTexture, 
										NULL,
										&vPos,
										pElement->GetTexColor().GetCurrentColor() );
	
}//	DrawSkinSprite
//------------------------------------------------------------------------------------------
HRESULT	CPUIDlg::DrawSprite( CPUIElement* pElement, RECT* prcDest )
{
	if( pElement->GetTexColor().GetCurrentColor().a == 0 )
		return S_OK;

	RECT	rtTexture	=	pElement->GetTexRect();

	RECT	rtScreen	=	*prcDest;
	OffsetRect( &rtScreen, m_nPosX, m_nPosY );

	CPUITexNode*	pTextureNode	=	GetTex( pElement->GetTexID() );
	if( !pTextureNode )
		return E_FAIL;

	float	fScaleX	=	(float)RectWidth( rtScreen ) / RectWidth( rtTexture );
	float	fScaleY	=	(float)RectHeight( rtScreen ) / RectHeight( rtTexture );

	D3DXMATRIXA16	matTransform;
	D3DXMatrixScaling( &matTransform, fScaleX, fScaleY, 1.0f );

	m_pResMgr->m_pSprite->SetTransform( &matTransform );

	D3DXVECTOR3	vPos( (float)rtScreen.left, (float)rtScreen.top, 0.0f );

	vPos.x	/=	fScaleX;
	vPos.y	/=	fScaleY;

	return m_pResMgr->m_pSprite->Draw(	pTextureNode->m_pTex, 
										&rtTexture, 
										NULL,
										&vPos,
										pElement->GetTexColor().GetCurrentColor() );

}//	DrawSprite
//------------------------------------------------------------------------------------------
HRESULT	CPUIDlg::DrawPolyLine( POINT* pPoints, UINT unNumPts, D3DCOLOR col )
{
	sPRVtx_Xyzrhw_Diff_Tex1* pVertices	=	NULL;
	PUTNEW( pVertices, sPRVtx_Xyzrhw_Diff_Tex1[ unNumPts ] );

	if( !pVertices )
		return E_OUTOFMEMORY;

	sPRVtx_Xyzrhw_Diff_Tex1* pVert	=	pVertices;
	POINT*	pt	=	pPoints;
	D3DXVECTOR4 tmpPos;
	D3DCOLOR	tmpCol;
	float fTu = 0.0f, fTV = 0.0f;
	for( UINT unCur = 0; unCur < unNumPts; ++unCur )
	{
		tmpPos.x	=	m_nPosX + (float)pt->x;
		tmpPos.y	=	m_nPosY + (float)pt->y;
		tmpPos.z	=	0.5f;
		tmpPos.w	=	1.0f;

		tmpCol		=	col;
		
		fTu	=	0.0f;
		fTV	=	0.0f;

		SetVtxInfoXyzrhwDiffTex1( pVert, tmpPos, tmpCol, fTu, fTV );

		++pVert;
		++pt;

	}//	for( UINT unCur = 0; unCur < unNumPts; ++unCur )

	PRLPD3DDEV9	pDev	=	m_pResMgr->GetDevice();

	m_pResMgr->m_pSprite->Flush();

	PRLPDVTXDCLR9	pDecl	=	NULL;
	devGetVertexDeclaration( pDev, &pDecl );
	devSetFVF( pDev, sPRVtx_Xyzrhw_Diff_Tex1::FVF );
	
//	devSetTSS( pDev, 0, D3DTSS_COLOROP, D3DTOP_SELECTARG2 );
	devSetTSSCOLOROP( pDev, 0, D3DTOP_SELECTARG2 );
//	devSetTSS( pDev, 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2 );
	devSetTSSAlphop( pDev, 0, D3DTOP_SELECTARG2 );
	
//	devDrawPrimitiveUP( pDev, D3DPT_LINESTRIP, unNumPts - 1, pVertices, sizeof( sFVF_XYZRHW_DIFF_TEX1 ) );

//	devSetTSS( pDev, 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
	devSetTSSCOLOROP( pDev, 0, D3DTOP_MODULATE );
//	devSetTSS( pDev, 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );
	devSetTSSAlphop( pDev, 0, D3DTOP_MODULATE );

	devSetVtxDclr( pDev, pDecl );
	pDecl->Release();

	PUT_SAFE_DELETE_ARRAY( pVertices );

	return S_OK;

}//	DrawPolyLine
//------------------------------------------------------------------------------------------
HRESULT	CPUIDlg::DrawRect( RECT* pRect, D3DCOLOR col )
{
	RECT	rcScreen	=	*pRect;
	OffsetRect( &rcScreen, m_nPosX, m_nPosY );


	sPRVtx_Xyzrhw_Diff_Tex1 vertices[4];
	PUT_ZERO_MEMORY( vertices );
	
	SetVtxInfoXyzrhwDiffTex1(	&vertices[0], 
								D3DXVECTOR4( (float)rcScreen.left - 0.5f, (float)rcScreen.top - 0.5f, 0.5f, 1.0f ),
								col,	
								0.0f,	0.0f );
	SetVtxInfoXyzrhwDiffTex1(	&vertices[1], 
								D3DXVECTOR4( (float)rcScreen.right - 0.5f, (float)rcScreen.top - 0.5f, 0.5f, 1.0f ),
								col,
								1.0f,	0.0f );
	SetVtxInfoXyzrhwDiffTex1(	&vertices[2], 
								D3DXVECTOR4( (float)rcScreen.right - 0.5f,	(float)rcScreen.bottom - 0.5f, 0.5f, 1.0f ),
								col,
								1.0f,	1.0f );
	SetVtxInfoXyzrhwDiffTex1(	&vertices[3], 
								D3DXVECTOR4( (float)rcScreen.left - 0.5f,	(float)rcScreen.bottom - 0.5f,	0.5f,	1.0f ),	
								col,
								0.0f,	1.0f );


	PRLPD3DDEV9 pDev	=	m_pResMgr->GetDevice();

	m_pResMgr->m_pSprite->Flush();
	PRLPDVTXDCLR9	pDecl	=	NULL;
	devGetVertexDeclaration( pDev, &pDecl );
	devSetFVF( pDev, sPRVtx_Xyzrhw_Diff_Tex1::FVF );

//	devSetTSS( pDev, 0, D3DTSS_COLOROP, D3DTOP_SELECTARG2 );
	devSetTSSCOLOROP( pDev, 0, D3DTOP_SELECTARG2 );
//	devSetTSS( pDev, 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2 );
	devSetTSSAlphop( pDev, 0, D3DTOP_SELECTARG2 );

	devDrawPUP( pDev, D3DPT_TRIANGLEFAN, 2, vertices, sizeof( sPRVtx_Xyzrhw_Diff_Tex1 ) );

//	devSetTSS( pDev, 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
	devSetTSSCOLOROP( pDev, 0, D3DTOP_MODULATE );
//	devSetTSS( pDev, 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );
	devSetTSSAlphop( pDev, 0, D3DTOP_MODULATE );

	devSetVtxDclr( pDev, pDecl );

	pDecl->Release();

	return S_OK;

}//	DrawRect
//------------------------------------------------------------------------------------------
void	CPUIDlg::SetNextDlg( CPUIDlg* pNextDlg )
{
	if( !pNextDlg )
		pNextDlg	=	this;

	m_pNextDlg	=	pNextDlg;
	if( pNextDlg )
		m_pNextDlg->m_pPrevDlg	=	this;

}//	SetNextDlg
//------------------------------------------------------------------------------------------
HRESULT		CPUIDlg::SetDefaultElement( UINT unCtrlType, UINT unElement, CPUIElement* pElement )
{
	for( UINT unCur = 0; unCur < m_DefaultElements.GetSize(); ++unCur )
	{
		CPUIElementHolder* pEleHolder	=	m_DefaultElements.Find(unCur);

		if( pEleHolder->unCtrlType == unCtrlType	&&
			pEleHolder->unIDx	==	unElement )
		{
			pEleHolder->Element	=	*pElement;
			return S_OK;
		}
	}


	CPUIElementHolder*	pNewEleHold = NULL;
	pNewEleHold	=	new	CPUIElementHolder;
	if( !pNewEleHold )
		return E_OUTOFMEMORY;

	pNewEleHold->unCtrlType	=	unCtrlType;
	pNewEleHold->unIDx		=	unElement;
	pNewEleHold->Element	=	*pElement;

	m_DefaultElements.Add( pNewEleHold );

	return S_OK;

}//	SetDefaultElement
//------------------------------------------------------------------------------------------
CPUIElement*	CPUIDlg::GetDefaultElement( UINT unCtrlType, UINT unElement )
{
	for( UINT unCur = 0; unCur < m_DefaultElements.GetSize(); ++unCur )
	{
		CPUIElementHolder* pEleHold	=	m_DefaultElements.Find(unCur);
		
		if( pEleHold->unCtrlType	==	unCtrlType &&
			pEleHold->unIDx			==	unElement )			
			return &pEleHold->Element;

	}//	for( int unCur = 0; unCur < m_DefaultElements.GetSize(); ++unCur )

	return NULL;

}//	GetDefaultElement
//------------------------------------------------------------------------------------------
HRESULT		CPUIDlg::SetSkinElement( UINT unElement, CPUIElement* pElement )
{
	HRESULT	hr	=	S_OK;

	if( !pElement )
		return E_INVALIDARG;

	for( UINT unCur = m_SkinElements.GetSize(); unCur <= unElement; ++unCur )
	{
		CPUIElement*	pNewEle	=	NULL;
		PUTNEW( pNewEle, CPUIElement );

		if( !pNewEle )
			return E_OUTOFMEMORY;

		m_SkinElements.Add( pNewEle );		

	}//	for( UINT unCur = m_SkinElements.GetSize(); unCur <= unElement; ++unCur )

	CPUIElement*	pCurEle	=	m_SkinElements.Find(unElement);
	*pCurEle				=	*pElement;

	return S_OK;

}//	SetSkinElement
//------------------------------------------------------------------------------------------
void	CPUIDlg::OnMouseMove( POINT pt )
{
	CPUICtrl*	pCtrl	=	GetCtrlAtPoint( pt );

	if( pCtrl == m_pCtrlMouseIn )
		return;

	if( m_pCtrlMouseIn )
		m_pCtrlMouseIn->SetMouseInRect( false );

	m_pCtrlMouseIn	=	pCtrl;
	if( pCtrl )
		m_pCtrlMouseIn->SetMouseInRect( true );

}//	OnMouseMove
//------------------------------------------------------------------------------------------
void	CPUIDlg::InitDefaultElements()
{
	SetFont( 0, L"Arial", 14, FW_NORMAL );

	CPUIElement Element;
	
	Element.SetFont( 0, D3DCOLOR_ARGB( 255, 0, 0 ,0 ), DT_LEFT | DT_TOP );
	SetDefaultElement( eCTRLTYPE_COMBOBOX, 0, &Element );

	Element.SetFont( 0, D3DCOLOR_ARGB( 255, 0, 0 ,0 ), DT_CENTER | DT_VCENTER );
	SetDefaultElement( eCTRLTYPE_IMEEDITBOX, 0, &Element );

	Element.SetFont( 0, D3DCOLOR_ARGB( 255, 0, 0 ,0 ), DT_LEFT | DT_TOP );
	SetDefaultElement( eCTRLTYPE_LISTBOX, 0, &Element );

}//	InitDefaultElements
//------------------------------------------------------------------------------------------
//	EOF