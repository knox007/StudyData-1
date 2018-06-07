#pragma once

#include <DShow.h>
#include <vmr9.h>
#pragma warning( disable : 4995 )
#pragma warning( disable : 4996 )

class CPRVmr9
{
public:	
	CPRVmr9( HWND hWndMedia, int nNumberOfStream = 4 );
	CPRVmr9()				{ InitData(); }
	virtual ~CPRVmr9()		{ ClearData(); }


public:	
	//	Graph configuration
	void			SetNumberOfLayer( int nNumOfLayer );
	BOOL			SetMediaWindow( HWND hWndMedia );
	BOOL			SetMediaFile( const char* pszFileName, int nLayer = 0 );
	BOOL			PreserveAspectRatio( BOOL bPreserve = TRUE );
	IBaseFilter*	AddFilter( const char* pszName, const GUID& CLSID );


	//	Graph control
	BOOL			PlayGraph();
	BOOL			StopGraph();
	BOOL			ResetGraph();
	IMediaEvent*	GetPtrMediaEvent();
	IMediaControl*	GetPtrMediaControl();
	IMediaSeeking*	GetPtrMediaSeeking();
	IBasicAudio*	GetPtrBasicAudio();

	//	Layer Control
	BOOL	GetVideoRect( LPRECT pRect );
	int		GetAlphaLayer( int nLayer );
	BOOL	SetAlphaLayer( int nLayer, int nAlpha );
	DWORD	GetLayerZOrder( int nLayer );
	BOOL	SetLayerZOrder( int nLayer, DWORD dwZOrder );
	BOOL	SetLayerRect( int nLayer, RECT rtLayer );

	//	Bitmap control
	BOOL	SetBitmap( LPDIRECT3DDEVICE9 pDev, const char* pszBitmapFileName, int nAlpha, COLORREF colTrans, RECT rtBitmap);
	BOOL	SetBitmapParams( LPDIRECT3DDEVICE9 pDev, int nAlpha, COLORREF colTrans, RECT rtBitmap );

	//	Reflected from Window
	BOOL	Repaint();
	BOOL	Resize();


protected:

	//	INIT Helper methods
	void	InitData();
	void	ClearData();


	//	Graph methods
	BOOL	BuildFilterGraph();
	BOOL	BuildVMR();
	BOOL	BuildSoundRenderer();
	BOOL	RenderGraph();

	//	D3d method
	BOOL	GetBitmapSize( const char* pszBitmapFileName, long& lHeight, long& lWidth );

	//	Layer helper methods
	BOOL	IsValidLayer( int nLayer );
	VMR9NormalizedRect	NormalizeRect( LPRECT prtVal );

	//	DSHOW helper methods
	HRESULT	AddToRot( IUnknown* pUnkGraph );
	void	RemoveFromRot();
	IPin*	GetPin(IBaseFilter* pFilter, PIN_DIRECTION PinDir );	
	HRESULT	GetNextFilter( IBaseFilter* pFilter, PIN_DIRECTION PinDir, IBaseFilter** ppNext );
	BOOL	RemoveFilterChain( IBaseFilter* pFilter, IBaseFilter* pStopFilter );
	HRESULT	AddFilterByClsid( IGraphBuilder *pGraph, LPCWSTR wszName, const GUID& clsid, IBaseFilter** ppF );

protected:
	DWORD			m_dwRotId;	
	int				m_nNumOfStream;

	//	Media Window
	HWND			m_hWndMedia;

	//	SRC Interfaces
	IBaseFilter*	m_srcFilterArray[10];

	//	SOUND Interfaces
	IBaseFilter*	m_pDxSoundFilter;

	//	GRAPH	Interfaces
	IUnknown*		m_pGraphUnknown;
	IGraphBuilder*	m_pGraphBuilder;
	IFilterGraph*	m_pFilterGraph;
	IFilterGraph2*	m_pFilterGraph2;
	IMediaControl*	m_pMediaControl;
	IMediaEvent*	m_pMediaEvent;
	IMediaEventEx*	m_pMediaEventEx;

	//	VMR9 Interface
	IBaseFilter*			m_pVMRBaseFilter;
	IVMRFilterConfig9*		m_pVMRFilterConfig;
	IVMRMixerBitmap9*		m_pVMRMixerBitmap;
	IVMRMixerControl9*		m_pVMRMixerControl;
	IVMRMonitorConfig9*		m_pVMRMonitorConfig;
	IVMRWindowlessControl9*	m_pVMRWindowlessControl;


	//	Dx Interface
	IDirect3DSurface9*		m_pDxSurface;
};
