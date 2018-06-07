#include "StdAfx.h"
#include "PUIDlgResourceMgr.h"
#include "PUTCommon.h"
#include "PUIUniBuffer.h"
#include "PUIIMEEditBox.h"
#include "PUIDlg.h"
#include "PRCommonFunc.h"
#include <strsafe.h>
#include <string.h>

//-------------------------------------------------------------------
void CPUIDlgResourceMgr::InitMembers()
{
	m_pDevice		=	NULL;
	m_pStateBlock	=	NULL;
	m_pSprite		=	NULL;
//	m_DlgMgr.Clear();
	
}//	InitMembers
//-------------------------------------------------------------------
void CPUIDlgResourceMgr::ClearMembers()
{
	m_TextureCache.DeleteAll();

	m_FontCache.DeleteAll();

	m_CustomSkinEleCache.DeleteAll();

	CPUIUniBuffer::UnInitialize();

	CPUIIMEEditBox::UnInitialize();

}//	ClearMembers
//-------------------------------------------------------------------
HRESULT	CPUIDlgResourceMgr::OnCreateDevice( HWND hWnd, PRLPD3DDEV9 pDev )
{
	HRESULT	hr = S_OK;
	
	m_pDevice	=	pDev;

	size_t nCur = 0;
	for( nCur = 0; nCur < m_FontCache.GetSize(); ++nCur )
	{
		hr	=	CreateFont( nCur );
		if( FAILED(hr) )
			return hr;
	}

	for( nCur = 0; m_TextureCache.GetSize(); ++nCur )
	{
		hr	=	CreateTex( nCur );
		if( FAILED(hr) )
			return hr;
	}

	hr	=	D3DXCreateSprite( pDev, &m_pSprite );
	if( FAILED(hr) )
	{
		PUTOutputDebugStr(PUT_CSTR_TCHAR("D3DXCreateSprite\n"));
		return hr;
	}

	CPUIIMEEditBox::StaticOnCreateDevice( hWnd );

	return S_OK;
}//	OnCreateDevice
//-------------------------------------------------------------------
HRESULT	CPUIDlgResourceMgr::OnResetDevice( PRLPD3DDEV9 pDev )
{
	HRESULT	hr	=	S_OK;

	for( size_t nCur = 0; nCur < m_FontCache.GetSize(); ++nCur )
	{
		CPUIFontNode *pFontNode	=	m_FontCache.Find(nCur);

		if( pFontNode->m_pFont )
			pFontNode->m_pFont->OnResetDevice();
	}

	if( m_pSprite )
		m_pSprite->OnResetDevice();

	PRLPD3DDEV9	pDevice = pDev;
	
	hr = pDevice->CreateStateBlock( D3DSBT_ALL, &m_pStateBlock );
	if( FAILED(hr) )
	{
		PUTOutputDebugStr( PUT_CSTR_TCHAR("CreateStateBlock\n") );
		return E_FAIL;
	}

	return S_OK;

}//	OnResetDevice
//-------------------------------------------------------------------
HRESULT	CPUIDlgResourceMgr::OnLostDevice()
{
	for( size_t unCur = 0; unCur < m_FontCache.GetSize(); ++unCur )
	{
		CPUIFontNode*	pFontNode	=	m_FontCache.Find(unCur);
		if( pFontNode->m_pFont )
			pFontNode->m_pFont->OnLostDevice();
	}

	if( m_pSprite )
		m_pSprite->OnLostDevice();

	PUT_SAFE_RELEASE( m_pStateBlock );

	return S_OK;

}//	OnLostDevice
//-------------------------------------------------------------------
HRESULT	CPUIDlgResourceMgr::OnDestroyDevice()
{
	size_t unCur	=	0;
	m_pDevice		=	NULL;

	for( unCur = 0; unCur < m_FontCache.GetSize(); ++unCur )
	{
		CPUIFontNode*	pFontNode	=	m_FontCache.Find(unCur);
		PUT_SAFE_RELEASE( pFontNode->m_pFont );
	}

	for( unCur = 0; unCur < m_TextureCache.GetSize(); ++unCur )
	{
		CPUITexNode*	pTextureNode	=	m_TextureCache.Find(unCur);
		PUT_SAFE_RELEASE( pTextureNode->m_pTex );
	}

	PUT_SAFE_RELEASE( m_pSprite );

	return S_OK;

}//	OnDestroyDevice
//-------------------------------------------------------------------
bool	CPUIDlgResourceMgr::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{	
	if( m_DlgMgr.GetSize() == 0 )
		return false;	

	for( int nCur = m_DlgMgr.GetSize() - 1; nCur > -1; --nCur )
	{
		CPUIDlg*	pDlg	=	m_DlgMgr.Find(nCur);
		if( pDlg )
		{
			if( pDlg->MsgProc( hWnd, uMsg, wParam, lParam ) == CPUIDlg::eMSGVAL_HANDLED )
				return true;
		}
	}

	return false;
}//	MsgProc
//-------------------------------------------------------------------
bool	CPUIDlgResourceMgr::IMEMsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if( CPUIIMEEditBox::StaticMsgProc( hWnd, uMsg, wParam, lParam ) )
		return true;

	return false;
}//	IMEMsgProc
//-------------------------------------------------------------------
HRESULT	CPUIDlgResourceMgr::OnRender( PRLPD3DDEV9 pDev, float fElapsedTime )
{
	HRESULT hr = S_OK;

	for( size_t nCur = 0; nCur < m_DlgMgr.GetSize(); ++nCur )
	{		
		if( FAILED( hr = m_DlgMgr.Find(nCur)->OnRender( pDev, fElapsedTime ) ) )
			break;
	}

	return hr;
}//	OnRender
//-------------------------------------------------------------------
bool	CPUIDlgResourceMgr::RegisterDlg( CPUIDlg* pDlg )
{
	for( size_t unCur = 0; unCur < m_DlgMgr.GetSize(); ++unCur )
	{
		if( m_DlgMgr.Find( unCur ) == pDlg )
			return true;
	}

	m_DlgMgr.Add( pDlg );

	if( m_DlgMgr.GetSize() > 1 )
		m_DlgMgr.Find( m_DlgMgr.GetSize() - 2 )->SetNextDlg( pDlg );

	m_DlgMgr.Find( m_DlgMgr.GetSize() - 1 )->SetNextDlg( m_DlgMgr.Find( 0 ) );

	return true;
}//	RegisterDlg
//-------------------------------------------------------------------
void	CPUIDlgResourceMgr::UnRegisterDlg( CPUIDlg* pDlg )
{
	for( size_t unCur = 0; unCur < m_DlgMgr.GetSize(); ++unCur )
	{
		if( m_DlgMgr.Find( unCur ) == pDlg )
		{
			m_DlgMgr.Delete( unCur );

			if( m_DlgMgr.GetSize() > 0 )
			{
				int nPrev = 0, nNext = 0;
				
				if( unCur == 0 )
					nPrev	=	m_DlgMgr.GetSize() - 1;
				else
					nPrev	=	unCur - 1;


				if( unCur == m_DlgMgr.GetSize() - 1 )
					nNext	=	0;
				else
					nNext	=	unCur;

				m_DlgMgr.Find(nPrev)->SetNextDlg( m_DlgMgr.Find( nNext ) );


			}//	if( m_DlgMgr.GetSize() > 0 )

		}//	if( m_DlgMgr.Find( unCur ) == pDlg )

		return;
	}//	for( size_t unCur = 0; unCur < m_DlgMgr.GetSize(); ++unCur )

	return;

}//	UnRegisterDlg
//-------------------------------------------------------------------
void	CPUIDlgResourceMgr::UnRegisterDlgsAll()
{
	while( m_DlgMgr.GetSize() )
	{
		UnRegisterDlg( m_DlgMgr.Find( 0 ) );
	}
}//	UnRegisterDlgsAll
//-------------------------------------------------------------------
void	CPUIDlgResourceMgr::EnableKeyboardInputForAllDlgs()
{
	for( size_t unCur = 0; unCur < m_DlgMgr.GetSize(); ++unCur )
		m_DlgMgr.Find(unCur)->CheckKeyboardInput( true );
}//	EnableKeyboardInputForAllDlgs
//-------------------------------------------------------------------
int		CPUIDlgResourceMgr::AddFont( const WCHAR* ptszFaceName, UINT unHeight, UINT unWeight )
{
	for( size_t unCur = 0; unCur < m_FontCache.GetSize(); ++unCur )
	{
		CPUIFontNode*	pFontNode	=	m_FontCache.Find(unCur);

		size_t	unLen = 0;
		StringCchLengthW( ptszFaceName, MAX_PATH, &unLen );
		if( 0 == _wcsnicmp( pFontNode->m_tszFace, ptszFaceName, unLen ) &&
			pFontNode->m_unHeight == unHeight &&
			pFontNode->m_unWeight == unWeight )
		{
			return unCur;
		}

	}//	for( size_t unCur = 0; unCur < m_FontCache.GetSize(); ++unCur )

	CPUIFontNode*	pNewFontNode	=	NULL;
	PUTNEW( pNewFontNode, CPUIFontNode );

	if( !pNewFontNode )
		return -1;

	PUT_ZERO_MEMORY_PTR( pNewFontNode );
	StringCchCopyW( pNewFontNode->m_tszFace, MAX_PATH, ptszFaceName );
	pNewFontNode->m_unHeight	=	unHeight;
	pNewFontNode->m_unWeight	=	unWeight;
	m_FontCache.Add( pNewFontNode );

	int nFont	=	m_FontCache.GetSize() - 1;

	if( m_pDevice )
		CreateFont( nFont );

	return nFont;

}//	AddFont
//-------------------------------------------------------------------
HRESULT		CPUIDlgResourceMgr::CreateFont( UINT unID )
{
	HRESULT	hr	=	S_OK;

	CPUIFontNode*	pFontNode	=	m_FontCache.Find(unID);

	PUT_SAFE_RELEASE( pFontNode->m_pFont );

	hr	=	D3DXCreateFontW( m_pDevice,
							pFontNode->m_unHeight,
							0,
							pFontNode->m_unWeight,
							1,
							FALSE,
							DEFAULT_CHARSET,
							OUT_DEFAULT_PRECIS,
							DEFAULT_QUALITY,
							DEFAULT_PITCH | FF_DONTCARE,
							pFontNode->m_tszFace,
							&pFontNode->m_pFont );
	if( FAILED( hr ) )	
	{
		PUTOutputDebugStr( PUT_CSTR_TCHAR("D3DXCreateFontW Error\n") );
		return hr;
	}

	return hr;

}//	CreateFont
//-------------------------------------------------------------------
HRESULT		CPUIDlgResourceMgr::CreateTex( UINT unID )
{
	HRESULT	hr	=	S_OK;

	CPUITexNode*	pTextureNode	=	m_TextureCache.Find(unID);

	PRDXIMGINFO		d3dInfo;

	hr	=	devCreateTxtrFromFileEx(	m_pDevice,
											(TCHAR*)pTextureNode->m_wszFilename,											
											D3DX_DEFAULT,
											D3DX_DEFAULT,
											1,
											0,
											D3DFMT_UNKNOWN,
											D3DPOOL_MANAGED,
											D3DX_DEFAULT,
											D3DX_DEFAULT,
											0,
											&d3dInfo,
											NULL,
											&pTextureNode->m_pTex );

	if( FAILED(hr) )
	{
		PUTOutputDebugStr( PUT_CSTR_TCHAR("devCreateTxtrFromFileEx Error\n") );
		return hr;			
	}

	pTextureNode->m_dwWidth		=	d3dInfo.Width;
	pTextureNode->m_dwHeight	=	d3dInfo.Height;

	return hr;

}//	CreateTexture
//-------------------------------------------------------------------
int	CPUIDlgResourceMgr::AddTex( const WCHAR* ptszFileName )
{
	for( size_t nCur = 0; nCur < m_TextureCache.GetSize(); ++nCur )
	{
		CPUITexNode* pTextureNode	=	m_TextureCache.Find(nCur);

		size_t nLen = 0;
		StringCchLengthW( ptszFileName, MAX_PATH, &nLen );
		if( pTextureNode->m_bFileSource && 
			_wcsnicmp( pTextureNode->m_wszFilename, ptszFileName, nLen ) == 0 )
			return nCur;
	}

	CPUITexNode*	pNewTextureNode = NULL;
	PUTNEW( pNewTextureNode, CPUITexNode );

	if( !pNewTextureNode )
		return -1;

	PUT_ZERO_MEMORY_PTR( pNewTextureNode );
	pNewTextureNode->m_bFileSource = true;
	StringCchCopyW( pNewTextureNode->m_wszFilename, MAX_PATH, ptszFileName );
	
	m_TextureCache.Add( pNewTextureNode );

	int nTextureID = m_TextureCache.GetSize() - 1;

	if( GetDevice() )
		CreateTex( nTextureID );

	return nTextureID;

}//	AddTex( const WCHAR* ptszFileName )
//-------------------------------------------------------------------
int	CPUIDlgResourceMgr::AddTex( const WCHAR* ptszResourceName, HMODULE hResourceModule )
{
	for( size_t nCur = 0; nCur < m_TextureCache.GetSize(); ++nCur )
	{
		CPUITexNode* pTextureNode = m_TextureCache.Find(nCur);

		if( pTextureNode->m_bFileSource &&
			pTextureNode->m_hResourceModule == hResourceModule )
		{
			if( IS_INTRESOURCE( ptszResourceName ) )
			{
				if( (INT_PTR)ptszResourceName == pTextureNode->m_nResourceID )
					return nCur;
			}else
			{
				size_t nLen = 0;
				StringCchLengthW( ptszResourceName, MAX_PATH, &nLen );
				if( 0 == _wcsnicmp( pTextureNode->m_wszFilename, ptszResourceName, nLen ) )
					return nCur;
			}
		}
	}//	for( size_t nCur = 0; nCur < m_TextureCache.GetSize(); ++nCur )

	CPUITexNode* pNewTextureNode = NULL;
	PUTNEW( pNewTextureNode, CPUITexNode );
	
	if( pNewTextureNode == NULL )
		return -1;

	PUT_ZERO_MEMORY_PTR( pNewTextureNode );
	pNewTextureNode->m_hResourceModule	=	hResourceModule;
	if( IS_INTRESOURCE( ptszResourceName ) )
	{
		pNewTextureNode->m_nResourceID = (int)(size_t)ptszResourceName;
	}else
	{
		pNewTextureNode->m_nResourceID = 0;
		StringCchCopyW( pNewTextureNode->m_wszFilename, MAX_PATH, ptszResourceName );
	}

	m_TextureCache.Add( pNewTextureNode );

	int nTextureID = m_TextureCache.GetSize() - 1;

	if( GetDevice() )
		CreateTex( nTextureID );

	return nTextureID;

}//	AddTex( const WCHAR* ptszResourceName, HMODULE hResourceModule )
//-------------------------------------------------------------------
CPUITexNode*	CPUIDlgResourceMgr::GetTexNode( int nID )	
{
	return m_TextureCache.Find(nID);
}//	GetTextureNode
//-------------------------------------------------------------------
CPUIFontNode*		CPUIDlgResourceMgr::GetFontNode( int nID )
{ 
	return m_FontCache.Find( nID ); 
}//	GetFontNode
//-------------------------------------------------------------------
CUSTOMSKINELEARR*	CPUIDlgResourceMgr::GetCustomSkinElement( int nID )
{
	return  (m_CustomSkinEleCache.Find( nID ) );
}
//-------------------------------------------------------------------
int	CPUIDlgResourceMgr::MakeCustomSkinElement( std::vector<std::wstring>& strFilenameArray, int nFontID, DWORD dwTextFormat )
{
	if( GetFontNode( nFontID ) == NULL )
		return -1;

	CUSTOMSKINELEARR*	pSkinEle = NULL;
	PUTNEW( pSkinEle, CUSTOMSKINELEARR );
	
	for( size_t nCur = 0; nCur < strFilenameArray.size(); ++nCur )
	{
		int nTexID			=	AddTex( strFilenameArray[nCur].c_str() );
		CPUITexNode* pTex	=	GetTexNode( nTexID );

		// jackie_notice : 텍스쳐의 영역.
		CPUIElement Element;
		Element.SetTexID( nTexID );
		Element.SetFontID( nFontID );
		Element.SetTexFormat( dwTextFormat );
		Element.SetTexRect( 0, 0, pTex->m_dwWidth, pTex->m_dwHeight );

		// jackie_notice :  텍스쳐/폰트의 색/투명도 설정.
		for( BYTE byCur = 0; byCur < eCTRLSTATE_MAX; ++ byCur )
		{
			Element.GetTexColor().SetStateColor( byCur, PRCOLOR_NOCOLOR );
			Element.GetFontColor().SetStateColor(byCur, PRCOLOR_NOCOLOR );
		}

		pSkinEle->push_back( Element );

	}//	for( size_t nCur = 0; nCur < strFilenameArray.size(); ++nCur )

	m_CustomSkinEleCache.Add( pSkinEle );
	int nSkinEleCacheIdx = m_CustomSkinEleCache.GetSize() - 1;	
	return nSkinEleCacheIdx;
}
//-------------------------------------------------------------------
//	EOF