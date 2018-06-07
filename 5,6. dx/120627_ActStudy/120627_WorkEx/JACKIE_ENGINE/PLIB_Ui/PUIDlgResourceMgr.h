#ifndef	_JUIDLGRESOURCEMGR_H_
#define	_JUIDLGRESOURCEMGR_H_
#pragma once

#include "PUICtrlCommon.h"
#include "PUTVecMgr.h"
#include "PUTSingleton.h"
#include "PUICtrlCommon.h"
#include "PUIDlg.h"

class CPUIDlgResourceMgr : public CPUTSingleton<CPUIDlgResourceMgr>
{
public:
	CPUIDlgResourceMgr(void)	{ InitMembers(); }
	~CPUIDlgResourceMgr(void)	{ ClearMembers(); }
	void	InitMembers();
	void	ClearMembers();

	//	Device
	LPDIRECT3DDEVICE9	GetDevice()		{ return m_pDevice; }
	HRESULT				OnCreateDevice( HWND hWnd, LPDIRECT3DDEVICE9 pDev );
	HRESULT				OnResetDevice( LPDIRECT3DDEVICE9 pDev );
	HRESULT				OnLostDevice();
	HRESULT				OnDestroyDevice();


	//	Procedure & Render
	bool			IMEMsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	bool			MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	HRESULT			OnRender( LPDIRECT3DDEVICE9 pDef, float fElapsedTime );


	//	SkinElement
	int						MakeCustomSkinElement(	std::vector<std::wstring>& strFilenameArray, 
													int nFontID, DWORD dwTextFormat = DT_LEFT | DT_VCENTER );
	CUSTOMSKINELEARR*		GetCustomSkinElement(	int nID );


	//	Font
	int					AddFont( const WCHAR* ptszFaceName, UINT unHeight, UINT unWeight );
	CPUIFontNode*		GetFontNode( int nID );


	//	Texture
	int				AddTex( const WCHAR* ptszFileName );
	int				AddTex( const WCHAR* ptszResourceName, HMODULE hResourceModule );
	CPUITexNode*	GetTexNode( int nID );


	//	Dialog
	bool	RegisterDlg( CPUIDlg* pDlg );
	void	UnRegisterDlg( CPUIDlg* pDlg );
	void	UnRegisterDlgsAll();
	void	EnableKeyboardInputForAllDlgs();


	//	Etc
	IDirect3DStateBlock9		*m_pStateBlock;
	LPD3DXSPRITE				m_pSprite;

	CPUTVecMgrPt< CPUIDlg >*	GetDlgMgr()	{ return &m_DlgMgr; }


protected:
	HRESULT		CreateFont( UINT unID );
	HRESULT		CreateTex( UINT unID );

	LPDIRECT3DDEVICE9	m_pDevice;	
	CPUTVecMgrPt< CPUITexNode >			m_TextureCache;
	CPUTVecMgrPt< CPUIFontNode >		m_FontCache;
	CPUTVecMgrPt< CUSTOMSKINELEARR >	m_CustomSkinEleCache;
	CPUTVecMgrPt< CPUIDlg >				m_DlgMgr;
};
//	CPUIDlgResourceMgr

#define gUIDlgResMgr		CREATESINGLETON(CPUIDlgResourceMgr)
#define gUIDlgResMgrDestroy	DESTROYSINGLETON(CPUIDlgResourceMgr)
#endif //	_JUIDLGRESOURCEMGR_H_