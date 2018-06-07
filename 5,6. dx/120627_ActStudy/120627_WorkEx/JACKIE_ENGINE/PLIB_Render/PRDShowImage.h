#ifndef _PRDSHOWIMAGE_H_
#define _PRDSHOWIMAGE_H_
#pragma once

#include <atlbase.h>
#include <dshow.h>
#include <vmr9.h>
#include "PRCommonTypeDef.h"

#define REGISTER_FILTERGRAPH
//#define NO_AUDIO_RENDERER

class CPRDShowImage
{
public:

	enum	eMEDIATYPE_
	{
		eMEDIATYPE_NONE,
		eMEDIATYPE_VIDEO,		
		eMEDIATYPE_SIZE
	};


	enum	eMEDIATYPESUB_
	{
		eMEDIATYPESUB_NONE,
		eMEDIATYPESUB_RGB24,
		eMEDIATYPESUB_RGB32,
		eMEDIATYPESUB_SIZE
	};


	enum	ePLAYSTATE_
	{
		ePLAYSTATE_NONE,
		ePLAYSTATE_PLAY,
		ePLAYSTATE_STOP,
		ePLAYSTATE_PAUSE,
		ePLAYSTATE_SIZE
	};


	CPRDShowImage()		{ InitMembers(); }
	~CPRDShowImage()	{ ClearMembers(); }

	HRESULT		Init( LPDIRECT3DDEVICE9 pDev, char *pszFPath, float fWid, float fHei );
	HRESULT		InitVtxBuff( LPDIRECT3DDEVICE9 pDev );
	HRESULT		InitTextureBuff( LPDIRECT3DDEVICE9 pDev );

	HRESULT		OnResetDevice( LPDIRECT3DDEVICE9 pDev );
	HRESULT		OnLostDevice();
	HRESULT		OnRender( LPDIRECT3DDEVICE9 pDev, float fElapsedTime );
	void		OnUpdate( LPDIRECT3DDEVICE9 pDev, float fElapsedTime = 0 );

	HRESULT		UpgradeGeom( long lActualW, long lTextureW, long lActualH, long lTextureH );

	bool		CheckShowStatus();

	HRESULT		Play();
	HRESULT		Stop();
	HRESULT		Pause();

	void			SetMediaType( eMEDIATYPE_ eType )		{ m_eMediaType = eType; }
	eMEDIATYPE_		GetMediaType()							{ return m_eMediaType; }
	void			SetMediaTypeSub( eMEDIATYPESUB_ eType )	{ m_eMediaTypeSub = eType; }
	eMEDIATYPESUB_	GetMediaTypeSub()						{ return m_eMediaTypeSub; }
	void			SetD3DFormat( D3DFORMAT eForm )			{ m_d3dFormat = eForm; }
	D3DFORMAT		GetD3DFromat()							{ return m_d3dFormat; }

	bool			IsVisible()								{ return m_bVisible; }
	void			SetEnableVisible( bool bVisible )		{ m_bVisible = bVisible; }

	PRDXTXTRBUFF9	GetTexture()						{ return m_pTextureBuff; }
	void			SetPlayState( ePLAYSTATE_ eState )	{ m_ePlayState = eState; }
	ePLAYSTATE_		GetPlayState()						{ return m_ePlayState; }

	void	SetSize( float fWid, float fHei )		{ m_fWidth = fWid; m_fHeight = fHei; }
	void	SetPos( float fX, float fY, float fZ )	{ m_fPosX = fX, m_fPosY = fY, m_fPosZ = fZ; }
	void	SetPlayMaxCount( int nVal )				{ m_nPlayMaxCount = nVal; }	

private:
	void	InitMembers();
	void	ClearMembers();

	PRDXVTXBUFF9	m_pVtxBuff;
	PRDXTXTRBUFF9	m_pTextureBuff;

	CComPtr<IGraphBuilder>	m_pGraphBuilder;		
	CComPtr<IMediaControl>	m_pMediaCtrl;
	CComPtr<IMediaPosition>	m_pMediaPos;
	CComPtr<IMediaEvent>	m_pMediaEvent;
	CComPtr<IBaseFilter>	m_pRenderer;	//	사용자 렌더러.

	eMEDIATYPE_				m_eMediaType;
	eMEDIATYPESUB_			m_eMediaTypeSub;
	D3DFORMAT				m_d3dFormat;

	ePLAYSTATE_				m_ePlayState;

#ifdef REGISTER_FILTERGRAPH
	HRESULT	AddToROT(IUnknown *pUnkGraph );
	void	RemoveFromROT();
	DWORD	m_dwROTReg;
#endif//	REGISTER_FILTERGRAPH


	//	파일 경로명.
	char	m_szFPath[MAX_PATH];
	//	파일 이름.
	char	m_szFName[MAX_PATH];

	bool	m_bVisible;

	float	m_fWidth;
	float	m_fHeight;

	float	m_fPosX;
	float	m_fPosY;
	float	m_fPosZ;

	int		m_nPlayCount;
	int		m_nPlayMaxCount;

	bool	m_bDeviceLost;

};
//	class CPRDShowImage



#endif	//	_PRDSHOWIMAGE_H_