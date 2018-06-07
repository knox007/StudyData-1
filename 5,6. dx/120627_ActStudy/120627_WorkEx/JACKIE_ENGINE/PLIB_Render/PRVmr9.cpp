#include "StdAfx.h"
#include "PRVmr9.h"
#include "PUtCommon.h"
#include <atlbase.h>

#define	WM_MEDIA_NOTIF		WM_APP + 1
//--------------------------------------------------------------------------
CPRVmr9::CPRVmr9( HWND hWndMedia, int nNumberOfStream )
{
	InitData();
	if( IsWindow( hWndMedia ) ){
		m_hWndMedia = hWndMedia;
	}

	if( nNumberOfStream > 0 && nNumberOfStream < 11 ){
		m_nNumOfStream = nNumberOfStream;
	}

}//	CPRVmr9( HWND hWndMedia, int nNumberOfStream )
//--------------------------------------------------------------------------
void	CPRVmr9::
InitData()
{
	m_dwRotId		=	-1;
	m_nNumOfStream	=	4;		//	default VMR9 config.
	m_hWndMedia		=	NULL;

	//	SRC Interface.
	for( int nCur = 0; nCur < 10; ++nCur ){
		m_srcFilterArray[nCur] = NULL;
	}

	//	Sound Interface
	m_pDxSoundFilter	=	NULL;

	//	Graph Interface
	m_pGraphUnknown		=	NULL;
	m_pGraphBuilder		=	NULL;
	m_pFilterGraph		=	NULL;
	m_pFilterGraph2		=	NULL;
	m_pMediaControl		=	NULL;
	m_pMediaEvent		=	NULL;
	m_pMediaEventEx		=	NULL;

	//	VMR9 Interface
	m_pVMRBaseFilter		=	NULL;
	m_pVMRFilterConfig		=	NULL;
	m_pVMRMixerBitmap		=	NULL;
	m_pVMRMixerControl		=	NULL;
	m_pVMRMonitorConfig		=	NULL;
	m_pVMRWindowlessControl	=	NULL;

	//	DxInterface
	m_pDxSurface			=	NULL;

}//	InitData
//--------------------------------------------------------------------------
void	CPRVmr9::
ClearData()
{
	//	CALLBACK Handle
	if( m_pMediaEventEx != NULL ){
		m_pMediaEventEx->SetNotifyWindow( NULL, WM_MEDIA_NOTIF, NULL );
	}


	//	SRC Interface
	for( int nCur = 0; nCur < 10; ++nCur ){
		IBaseFilter*	pSrcFilter = m_srcFilterArray[nCur];
		PUT_SAFE_RELEASE( pSrcFilter );
	}

	//	SOUND Interface
	PUT_SAFE_RELEASE( m_pDxSoundFilter );

	//	VMR9 Interface
	PUT_SAFE_RELEASE( m_pVMRFilterConfig );
	PUT_SAFE_RELEASE( m_pVMRMixerBitmap );
	PUT_SAFE_RELEASE( m_pVMRMixerControl );
	PUT_SAFE_RELEASE( m_pVMRMonitorConfig );
	PUT_SAFE_RELEASE( m_pVMRWindowlessControl );
	PUT_SAFE_RELEASE( m_pVMRBaseFilter );

	//	GRAPH Interface
	PUT_SAFE_RELEASE( m_pGraphBuilder );
	PUT_SAFE_RELEASE( m_pFilterGraph );
	PUT_SAFE_RELEASE( m_pFilterGraph2 );
	PUT_SAFE_RELEASE( m_pMediaControl );
	PUT_SAFE_RELEASE( m_pMediaEvent );
	PUT_SAFE_RELEASE( m_pMediaEventEx );
	PUT_SAFE_RELEASE( m_pGraphUnknown );

	//	Dx	Interface
	PUT_SAFE_RELEASE( m_pDxSurface );

}//	ClearData
//--------------------------------------------------------------------------
HRESULT	CPRVmr9::
AddToRot( IUnknown* pUnkGraph )
{
	if( !pUnkGraph )
		return E_INVALIDARG;

	IMoniker*				pMoniker	=	NULL;
	IRunningObjectTable*	pROT		=	NULL;
	if( FAILED( GetRunningObjectTable( 0, &pROT ) ) )
		return E_FAIL;

	WCHAR wsz[MAX_PATH]	=	{0};
	wsprintfW( wsz, L"FilterGraph %08x pid %08x", ( DWORD_PTR )pUnkGraph, GetCurrentProcessId() );
	HRESULT	hr = CreateItemMoniker( L"!", wsz, &pMoniker );
	if( SUCCEEDED( hr ) ){
		hr = pROT->Register( 0, pUnkGraph, pMoniker, &m_dwRotId );
		pMoniker->Release();
	}

	pROT->Release();

	return hr;

}//	AddToRot
//--------------------------------------------------------------------------
void	CPRVmr9::
RemoveFromRot()
{
	if( m_dwRotId != -1 ){
		IRunningObjectTable* pRot = NULL;
		if( SUCCEEDED( GetRunningObjectTable( 0, &pRot ) ) ){
			pRot->Revoke( m_dwRotId );
			m_dwRotId = -1;
			pRot->Release();
		}
	}

}//	RemoveFromRot
//--------------------------------------------------------------------------
IPin*	CPRVmr9::
GetPin( IBaseFilter* pFilter, PIN_DIRECTION PinDir )
{
	BOOL		bFound	=	FALSE;
	IEnumPins*	pEnum	=	NULL;
	IPin*		pPin	=	NULL;

	pFilter->EnumPins( &pEnum );
	while( pEnum->Next( 1, &pPin, 0 ) == S_OK ){
		PIN_DIRECTION	PinDirThis;
		pPin->QueryDirection( &PinDirThis );
		if( bFound = ( PinDir == PinDirThis ) )
			break;
		pPin->Release();
	}
	pEnum->Release();

	return ( bFound ? pPin : 0);

}//	GetPin
//--------------------------------------------------------------------------
HRESULT	CPRVmr9::
GetNextFilter( IBaseFilter* pFilter, PIN_DIRECTION PinDir, IBaseFilter** ppNext )
{
	if( !pFilter || !ppNext )
		return E_POINTER;

	IEnumPins*	pEnum	=	NULL;
	IPin*		pPin	=	NULL;
	HRESULT		hr		=	pFilter->EnumPins( &pEnum );
	if( FAILED( hr ) )
		return hr;

	while( S_OK == pEnum->Next( 1, &pPin, 0 ) ){
		PIN_DIRECTION	ThisPinDir;
		hr	=	pPin->QueryDirection( &ThisPinDir );
		if( FAILED( hr ) ){
			hr	=	E_UNEXPECTED;
			pPin->Release();
			break;
		}
		if( ThisPinDir == PinDir ){
			IPin*	pPinNext	=	0;
			hr	=	pPin->ConnectedTo( &pPinNext );
			if( SUCCEEDED( hr ) ){
				PIN_INFO	PinInfo;
				hr	=	pPinNext->QueryPinInfo( &PinInfo );
				pPinNext->Release();
				pPin->Release();
				pEnum->Release();
				if( FAILED( hr ) || ( PinInfo.pFilter == NULL ) )
					return E_UNEXPECTED;

				*ppNext	=	PinInfo.pFilter;
				return S_OK;
			}
		}
		pPin->Release();
	}
	pEnum->Release();

	return E_FAIL;

}//	GetNextFilter
//--------------------------------------------------------------------------
BOOL	CPRVmr9::
RemoveFilterChain( IBaseFilter* pFilter, IBaseFilter* pStopFilter )
{
	HRESULT	hr;

	IBaseFilter*	pFilterFound	=	NULL;

	hr	=	GetNextFilter( pFilterFound, PINDIR_OUTPUT, &pFilterFound );
	if( SUCCEEDED( hr ) && ( pFilterFound != pStopFilter ) ){
		RemoveFilterChain( pFilterFound, pStopFilter );
		pFilterFound->Release();
	}

	m_pFilterGraph->RemoveFilter( pFilter );

	return TRUE;

}//	RemoveFilterChain
//--------------------------------------------------------------------------
HRESULT	CPRVmr9::
AddFilterByClsid( IGraphBuilder *pGraph, LPCWSTR wszName, const GUID& clsid, IBaseFilter** ppF )
{
	*ppF	=	NULL;

	HRESULT	hr	=	CoCreateInstance( clsid, NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)ppF );
	if( SUCCEEDED( hr ) ){
		hr	=	pGraph->AddFilter( (*ppF), wszName );
	}

	return hr;

}//	AddFilterByClsid
//--------------------------------------------------------------------------
BOOL	CPRVmr9::
IsValidLayer( int nLayer )
{
	if( nLayer > 9 || nLayer < 0)
		return FALSE;

	IBaseFilter*	pBaseFilter	=	m_srcFilterArray[ nLayer ];

	if( pBaseFilter == NULL )
		return FALSE;
	else
		return TRUE;

}//	IsValidLayer
//--------------------------------------------------------------------------
VMR9NormalizedRect	CPRVmr9::
NormalizeRect( LPRECT prtVal )
{
	VMR9NormalizedRect	nRect;

	RECT	rtVideo;
	if( GetVideoRect( &rtVideo ) ){
		int nWidth	=	rtVideo.right	-	rtVideo.left;
		int nHeight	=	rtVideo.bottom	-	rtVideo.top;

		try{
			nRect.left	=	( (float) ( ( prtVal->left * 100 ) / nWidth ) ) / 100.0f;
		}catch(...){
			nRect.left	=	0.0f;
		}

		try{
			nRect.right	=	( (float) ( (prtVal->right * 100 ) / rtVideo.right ) ) / 100.0f;
		}catch(...){
			nRect.right	=	1.0f;
		}

		try{
			nRect.top	=	( (float) ( ( prtVal->top * 100 ) / nHeight ) ) / 100.0f;
		}catch(...){
			nRect.top	=	0.0f;
		}

		try{
			nRect.bottom	=	( (float) ( ( prtVal->bottom * 100 ) / rtVideo.bottom ) ) / 100.0f;
		}catch(...){
			nRect.bottom	=	1.0f;
		}
	}

	return nRect;

}//	NormalizeRect
//--------------------------------------------------------------------------
BOOL	CPRVmr9::
SetMediaWindow( HWND hWndMedia )
{
	if( !IsWindow( hWndMedia ) ){
		PUT_ERROR;
		return FALSE;
	}

	m_hWndMedia	=	hWndMedia;

	return TRUE;

}//	SetMediaWindow
//--------------------------------------------------------------------------
BOOL	CPRVmr9::
SetMediaFile( const char* pszFileName, int nLayer )
{
	USES_CONVERSION;

	HRESULT	hr = S_OK;
	BOOL	bHaveToRun	=	FALSE;

	if( pszFileName == NULL ){
		PUT_ERROR;
		return FALSE;
	}

	if( m_pGraphBuilder == NULL ){
		BOOL	bRet	=	BuildFilterGraph();
		if( !bRet )
			return bRet;
	}

	OAFilterState filterState;
	m_pMediaControl->GetState( 500, &filterState );
	if( filterState != State_Stopped ){
		m_pMediaControl->Stop();
		bHaveToRun = TRUE;
	}

	if( m_srcFilterArray[nLayer] == NULL ){
		char	szFilterName[10] = {0};
		sprintf( szFilterName, "SRC%02d", nLayer );
		IBaseFilter*	pBaseFilter = NULL;
		hr = m_pGraphBuilder->AddSourceFilter( A2W(pszFileName), A2W(szFilterName), &pBaseFilter );
		if( FAILED( hr ) ){
			PUT_ERROR;
			return FALSE;
		}
		m_srcFilterArray[nLayer]	=	pBaseFilter;
	}
	else{
		IBaseFilter*	pBaseFilter	=	m_srcFilterArray[nLayer];
		RemoveFilterChain( pBaseFilter, m_pVMRBaseFilter );
		pBaseFilter->Release();
		m_srcFilterArray[nLayer]	=	NULL;

		char szFilterName[10]	=	{0};
		sprintf( szFilterName, "SRC%02d", nLayer );
		hr	=	m_pGraphBuilder->AddSourceFilter( A2W( pszFileName ), A2W( szFilterName ), &pBaseFilter );
		m_srcFilterArray[nLayer]	=	pBaseFilter;
		if( FAILED( hr ) ){
			m_srcFilterArray[nLayer]	=	NULL;
			PUT_ERROR;
			return FALSE;
		}
	}

	BOOL	bRet	=	RenderGraph();
	if( !bRet )
		return bRet;

	if( bHaveToRun )
		m_pMediaControl->Run();

	return TRUE;

}//	SetMediaFile
//--------------------------------------------------------------------------
BOOL	CPRVmr9::
BuildFilterGraph()
{
	HRESULT	hr;

	ClearData();
	RemoveFromRot();

	hr	=	CoCreateInstance( CLSID_FilterGraph, NULL, CLSCTX_INPROC, IID_IUnknown, (void**)&m_pGraphUnknown );
	if( FAILED( hr ) ){
		PUT_ERROR;
		return FALSE;
	}

	hr	=	m_pGraphUnknown->QueryInterface( IID_IGraphBuilder, (void**)&m_pGraphBuilder );
	hr	=	m_pGraphUnknown->QueryInterface( IID_IFilterGraph, (void**)&m_pFilterGraph );
	hr	=	m_pGraphUnknown->QueryInterface( IID_IFilterGraph2, (void**)&m_pFilterGraph2 );
	hr	=	m_pGraphUnknown->QueryInterface( IID_IMediaControl, (void**)&m_pMediaControl );
	hr	=	m_pGraphUnknown->QueryInterface( IID_IMediaEvent, (void**)&m_pMediaEvent );
	hr	=	m_pGraphUnknown->QueryInterface( IID_IMediaEventEx, (void**)&m_pMediaEventEx );

	if( m_pMediaEventEx != NULL ){
		m_pMediaEventEx->SetNotifyWindow( (OAHWND)m_hWndMedia, WM_MEDIA_NOTIF, NULL );
	}	

	BuildSoundRenderer();

	AddToRot( m_pGraphUnknown );

	return BuildVMR();

}//	BuildFilterGraph
//--------------------------------------------------------------------------
BOOL	CPRVmr9::
BuildVMR()
{
	HRESULT	hr;

	if( !m_hWndMedia ){
		PUT_ERROR;
		return FALSE;
	}

	if( !m_pGraphBuilder ){
		PUT_ERROR;
		return FALSE;
	}

	IBaseFilter* pVmr	=	NULL;
	hr	=	CoCreateInstance( CLSID_VideoMixingRenderer9, 0, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)&m_pVMRBaseFilter );
	if( FAILED(hr) ){
		PUT_ERROR;
		return FALSE;
	}


	hr	=	m_pGraphBuilder->AddFilter( m_pVMRBaseFilter, L"VMR9" );
	if( FAILED(hr) ){
		PUT_ERROR;
		return FALSE;
	}


	hr	=	m_pVMRBaseFilter->QueryInterface( IID_IVMRFilterConfig9, (void**)&m_pVMRFilterConfig );
	if( SUCCEEDED(hr) ){
		m_pVMRFilterConfig->SetRenderingMode( VMR9Mode_Windowless );
		m_pVMRFilterConfig->SetNumberOfStreams( m_nNumOfStream );
	}

	hr	=	m_pVMRBaseFilter->QueryInterface( IID_IVMRWindowlessControl9, (void**)&m_pVMRWindowlessControl );
	if( SUCCEEDED(hr) ){
		m_pVMRWindowlessControl->SetVideoClippingWindow( m_hWndMedia );
		m_pVMRWindowlessControl->SetAspectRatioMode( VMR9ARMode_LetterBox );
	}

	hr	=	m_pVMRBaseFilter->QueryInterface( IID_IVMRMixerBitmap9, (void**)&m_pVMRMixerBitmap );
	hr	=	m_pVMRBaseFilter->QueryInterface( IID_IVMRMixerControl9, (void**)&m_pVMRMixerControl );
	hr	=	m_pVMRBaseFilter->QueryInterface( IID_IVMRMonitorConfig9, (void**)&m_pVMRMonitorConfig );

	return TRUE;

}//	BuildVMR
//--------------------------------------------------------------------------
BOOL	CPRVmr9::
BuildSoundRenderer()
{
	HRESULT	hr;

	hr	=	AddFilterByClsid( m_pGraphBuilder, L"DirectSound", CLSID_DSoundRender, &m_pDxSoundFilter );
	if( FAILED( hr ) ){
		PUT_ERROR;
		return FALSE;
	}

	return TRUE;

}//	BuildSoundRenderer
//--------------------------------------------------------------------------
BOOL	CPRVmr9::
RenderGraph()
{
	HRESULT	hr;

	if( m_pFilterGraph2 == NULL ){
		PUT_ERROR;
		return FALSE;
	}

	for( int nCur = 0; nCur < 10; ++nCur )
	{
		IBaseFilter*	pBaseFilter = m_srcFilterArray[nCur];
		if( pBaseFilter != NULL ){
			IPin*	pPin	=	GetPin( pBaseFilter, PINDIR_OUTPUT );
			if( pPin != NULL ){
				try{
					hr	=	m_pFilterGraph2->RenderEx( pPin, AM_RENDEREX_RENDERTOEXISTINGRENDERERS, NULL );
				}catch(...){

				}
			}
		}
	}
	return TRUE;

}//	RenderGraph
//--------------------------------------------------------------------------
BOOL	CPRVmr9::
PreserveAspectRatio( BOOL bPreserve )
{
	if( !m_pVMRWindowlessControl ){
		PUT_ERROR;
		return FALSE;
	}

	if( bPreserve )
		m_pVMRWindowlessControl->SetAspectRatioMode( VMR9ARMode_LetterBox );
	else
		m_pVMRWindowlessControl->SetAspectRatioMode( VMR9ARMode_None );

	return TRUE;

}//	PreserveAspectRatio
//--------------------------------------------------------------------------
IBaseFilter*	CPRVmr9::
AddFilter( const char* pszName, const GUID& CLSID )
{
	USES_CONVERSION;

	HRESULT	hr;

	IBaseFilter*	pBaseFilter	=	NULL;

	if( pszName == NULL ){
		PUT_ERROR;
		return NULL;
	}

	hr	=	AddFilterByClsid( m_pGraphBuilder, A2W(pszName), CLSID, &pBaseFilter );
	if( FAILED(hr) ){
		PUT_ERROR;
		return NULL;
	}

	return pBaseFilter;

}//	AddFilter
//--------------------------------------------------------------------------
BOOL	CPRVmr9::
PlayGraph()
{
	if( m_pMediaControl == NULL ){
		PUT_ERROR;
		return FALSE;
	}

	if( m_pVMRWindowlessControl == NULL ){
		PUT_ERROR;
		return FALSE;
	}

	LONG	Width;
	LONG	Height;
	LONG	ARWidth;
	LONG	ARHeight;
	m_pVMRWindowlessControl->GetNativeVideoSize( &Width, &Height, &ARWidth, &ARHeight );

	RECT	mediaRect;
	mediaRect.left		=	0;
	mediaRect.top		=	0;
	mediaRect.right		=	Width;
	mediaRect.bottom	=	Height;

	RECT	wndRect;
	GetClientRect( m_hWndMedia, &wndRect );
	m_pVMRWindowlessControl->SetVideoPosition( &mediaRect, &wndRect );

	m_pMediaControl->Run();

	return TRUE;

}//	PlayGraph
//-----------------------------------------------------------------------------
BOOL	CPRVmr9::
StopGraph()
{
	if( m_pMediaControl == NULL ){
		PUT_ERROR;
		return FALSE;
	}

	m_pMediaControl->Stop();

	return TRUE;

}//	StopGraph
//-----------------------------------------------------------------------------
BOOL	CPRVmr9::
ResetGraph()
{
	if( m_pMediaControl )
	{
		m_pMediaControl->Stop();
	}

	try{
		ClearData();
	}catch(...)
	{
		PUT_ERROR;
		return FALSE;
	}

	return TRUE;

}//	ResetGraph
//--------------------------------------------------------------------------
IMediaEvent*	CPRVmr9::
GetPtrMediaEvent()
{
	if( m_pGraphBuilder == NULL ){
		PUT_ERROR;
		return NULL;
	}

	if( m_pMediaEvent )
		m_pMediaEvent->AddRef();

	return m_pMediaEvent;

}//	GetPtrMediaEvent
//--------------------------------------------------------------------------
IMediaControl*	CPRVmr9::
GetPtrMediaControl()
{
	if( m_pGraphBuilder == NULL ){
		PUT_ERROR;
		return NULL;
	}

	if( m_pMediaControl )
		m_pMediaControl->AddRef();

	return m_pMediaControl;

}//	GetPtrMediaControl
//--------------------------------------------------------------------------
IMediaSeeking*	CPRVmr9::
GetPtrMediaSeeking()
{
	IMediaSeeking*	pMediaSeeking	=	NULL;

	if( m_pGraphBuilder == NULL ){
		PUT_ERROR;
		return NULL;
	}

	m_pGraphBuilder->QueryInterface( IID_IMediaSeeking, (void**)&pMediaSeeking );

	return pMediaSeeking;

}//	GetPtrMediaSeeking
//--------------------------------------------------------------------------
IBasicAudio*	CPRVmr9::
GetPtrBasicAudio()
{
	IBasicAudio*	pBaseAudio	=	NULL;

	if( m_pGraphBuilder == NULL ){
		PUT_ERROR;
		return NULL;
	}

	m_pGraphBuilder->QueryInterface( IID_IBasicAudio, (void**)&pBaseAudio );

	return pBaseAudio;

}//	GetPtrBasicAudio
//--------------------------------------------------------------------------
BOOL	CPRVmr9::
Repaint()
{
	if( m_pVMRWindowlessControl == NULL ){
		PUT_ERROR;
		return FALSE;
	}

	HDC hDc	 =	GetDC( m_hWndMedia );
	m_pVMRWindowlessControl->RepaintVideo( m_hWndMedia, hDc );

	return TRUE;

}//	Repaint
//--------------------------------------------------------------------------
BOOL	CPRVmr9::
Resize()
{
	if( m_pVMRWindowlessControl == NULL ){
		PUT_ERROR;
		return FALSE;
	}

	LONG	Width;
	LONG	Height;
	LONG	ARWidth;
	LONG	ARHeight;
	m_pVMRWindowlessControl->GetNativeVideoSize( &Width, &Height, &ARWidth, &ARHeight );

	RECT	mediaRect;
	mediaRect.left		=	0;
	mediaRect.top		=	0;
	mediaRect.right		=	Width;
	mediaRect.bottom	=	Height;

	RECT	wndRect;
	GetClientRect( m_hWndMedia, &wndRect );
	m_pVMRWindowlessControl->SetVideoPosition( &mediaRect, &wndRect );

	return	FALSE;

}//	Resize
//--------------------------------------------------------------------------
BOOL	CPRVmr9::
GetVideoRect( LPRECT pRect )
{
	HRESULT	hr;

	if( pRect == NULL ){
		PUT_ERROR;
		return FALSE;
	}


	if( m_pVMRWindowlessControl == NULL ){
		PUT_ERROR;
		return FALSE;
	}


	LONG	Width;
	LONG	Height;
	LONG	ARWidth;
	LONG	ARHeight;
	hr	=	m_pVMRWindowlessControl->GetNativeVideoSize( &Width, &Height, &ARWidth, &ARHeight );


	if( FAILED(hr) ){
		PUT_ERROR;
		return FALSE;
	}

	pRect->left		=	0;
	pRect->top		=	0;
	pRect->right	=	Width;
	pRect->bottom	=	Height;

	return TRUE;

}//	GetVideoRect
//--------------------------------------------------------------------------
BOOL	CPRVmr9::
SetAlphaLayer( int nLayer, int nAlpha )
{
	HRESULT	hr;

	if( !IsValidLayer( nLayer ) ){
		PUT_ERROR;
		return FALSE;
	}

	if( nAlpha < 0 || nAlpha > 100 ){
		PUT_ERROR;
		return FALSE;
	}

	if( m_pVMRMixerControl == NULL ){
		PUT_ERROR;
		return FALSE;
	}

	float	fAlpha	=	((float)nAlpha) / 100.0f;
	hr	=	m_pVMRMixerControl->SetAlpha( nLayer, fAlpha );

	return TRUE;

}//	SetAlphaLayer
//--------------------------------------------------------------------------
int		CPRVmr9::
GetAlphaLayer( int nLayer )
{
	HRESULT hr;

	if( !IsValidLayer( nLayer ) )
	{
		PUT_ERROR;
		return 1;
	}

	if( m_pVMRMixerControl == NULL ){
		PUT_ERROR;
		return 1;
	}

	float	fAlpha;
	hr	=	m_pVMRMixerControl->GetAlpha( nLayer, &fAlpha );

	return (int)(fAlpha * 100);

}//	GetAlphaLayer
//--------------------------------------------------------------------------
DWORD	CPRVmr9::
GetLayerZOrder( int nLayer )
{
	HRESULT	hr;
	DWORD	dwZOrder;

	if( !IsValidLayer(nLayer) ){
		PUT_ERROR;
		return FALSE;
	}

	if( m_pVMRMixerControl == NULL ){
		PUT_ERROR;
		return FALSE;
	}

	hr	=	m_pVMRMixerControl->GetZOrder( nLayer, &dwZOrder );

	return dwZOrder;

}//	GetLayerZOrder
//--------------------------------------------------------------------------
BOOL	CPRVmr9::
SetLayerZOrder( int nLayer, DWORD dwZOrder )
{
	HRESULT	hr;

	if( !IsValidLayer(nLayer) ){
		PUT_ERROR;
		return FALSE;
	}

	if( m_pVMRMixerControl == NULL ){
		PUT_ERROR;
		return FALSE;
	}

	hr	=	m_pVMRMixerControl->SetZOrder( nLayer, dwZOrder );
	if( FAILED(hr) ){
		PUT_ERROR;
		return FALSE;
	}

	return	TRUE;

}//	SetLayerZOrder
//--------------------------------------------------------------------------
BOOL	CPRVmr9::
SetLayerRect( int nLayer, RECT rtLayer )
{
	HRESULT hr;

	if( !IsValidLayer( nLayer ) ){
		PUT_ERROR;
		return FALSE;
	}

	if( !m_pVMRMixerControl == NULL ){
		PUT_ERROR;
		return FALSE;
	}

	if( m_pVMRWindowlessControl == NULL ){
		PUT_ERROR;
		return FALSE;
	}

	VMR9NormalizedRect	nRect = NormalizeRect( &rtLayer );
	hr	=	m_pVMRMixerControl->SetOutputRect( nLayer, &nRect );
	if( FAILED(hr) ){
		PUT_ERROR;
		return FALSE;
	}

	return TRUE;

}//	SetLayerRect
//--------------------------------------------------------------------------
BOOL	CPRVmr9::
GetBitmapSize( const char* pszBitmapFileName, long& lHeight, long& lWidth )
{
	BOOL	bRet = FALSE;

	HANDLE	hBitmap		=	LoadImage(	NULL,
		pszBitmapFileName,
		IMAGE_BITMAP,
		0, 0,
		LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE
		);

	if( hBitmap ){
		BITMAP	bmpInfo;
		if( GetObject( hBitmap, sizeof( bmpInfo ), &bmpInfo ) ){
			lHeight	=	bmpInfo.bmHeight;
			lWidth	=	bmpInfo.bmWidth;
			bRet	=	TRUE;
		}
	}

	DeleteObject( hBitmap );

	return bRet;

}//	GetBitmapSize
//--------------------------------------------------------------------------
BOOL	CPRVmr9::
SetBitmap( LPDIRECT3DDEVICE9 pDev,  const char* pszBitmapFileName, int nAlpha, COLORREF colTrans, RECT rtBitmap )
{
	HRESULT	hr = S_OK;

	if( m_pVMRMixerBitmap == NULL ){
		PUT_ERROR;
		return FALSE;
	}

	if( m_pVMRWindowlessControl == NULL ){
		PUT_ERROR;
		return FALSE;
	}

	if( pDev ){
		PUT_ERROR;
		return FALSE;
	}

	PUT_SAFE_RELEASE( m_pDxSurface );

	long lWidth, lHeight;
	if( !GetBitmapSize( pszBitmapFileName, lHeight, lWidth ) ){
		lWidth = 128;
		lHeight = 128;
	}

	hr	=	pDev->CreateOffscreenPlainSurface(	lWidth, lHeight,
		D3DFMT_X8R8G8B8,
		D3DPOOL_SYSTEMMEM,
		&m_pDxSurface,
		NULL
		);

	if( FAILED( hr ) ){
		PUT_ERROR;
		return FALSE;
	}


	D3DXLoadSurfaceFromFile(	m_pDxSurface,
		NULL,
		NULL,
		pszBitmapFileName,
		NULL,
		D3DX_DEFAULT,
		0,
		NULL
		);

	VMR9NormalizedRect	nRect	=	NormalizeRect( &rtBitmap );
	VMR9AlphaBitmap	alphaBitmap;
	alphaBitmap.dwFlags			=	VMR9AlphaBitmap_EntireDDS | VMR9AlphaBitmap_SrcColorKey;
	alphaBitmap.hdc				=	NULL;
	alphaBitmap.pDDS			=	m_pDxSurface;
	alphaBitmap.clrSrcKey		=	colTrans;
	alphaBitmap.rDest.top		=	nRect.top;
	alphaBitmap.rDest.left		=	nRect.left;
	alphaBitmap.rDest.bottom	=	nRect.bottom;
	alphaBitmap.rDest.right		=	nRect.right;
	alphaBitmap.fAlpha			=	nAlpha / 100.0f;

	hr	=	m_pVMRMixerBitmap->SetAlphaBitmap( &alphaBitmap );
	if( FAILED(hr) ){
		PUT_ERROR;
		return FALSE;
	}

	return TRUE;

}//	SetBitmap
//--------------------------------------------------------------------------
BOOL	CPRVmr9::
SetBitmapParams( LPDIRECT3DDEVICE9 pDev, int nAlpha, COLORREF colTrans, RECT rtBitmap )
{
	HRESULT	hr;

	if( m_pVMRMixerBitmap == NULL ){
		PUT_ERROR;
		return FALSE;
	}

	if( m_pVMRWindowlessControl == NULL ){
		PUT_ERROR;
		return FALSE;
	}

	if( pDev == NULL ){
		PUT_ERROR;
		return FALSE;
	}

	if( m_pDxSurface == NULL ){
		PUT_ERROR;
		return FALSE;
	}

	VMR9NormalizedRect	nRect	=	NormalizeRect( &rtBitmap );
	VMR9AlphaBitmap	alphaBitmap;
	alphaBitmap.dwFlags			=	VMR9AlphaBitmap_EntireDDS | VMR9AlphaBitmap_SrcColorKey;
	alphaBitmap.hdc				=	NULL;
	alphaBitmap.pDDS			=	m_pDxSurface;
	alphaBitmap.clrSrcKey		=	colTrans;
	alphaBitmap.rDest.top		=	nRect.top;
	alphaBitmap.rDest.left		=	nRect.left;
	alphaBitmap.rDest.bottom	=	nRect.bottom;
	alphaBitmap.rDest.right		=	nRect.right;
	alphaBitmap.fAlpha			=	nAlpha / 100.0f;

	hr	=	m_pVMRMixerBitmap->SetAlphaBitmap( &alphaBitmap );
	if( FAILED(hr) ){
		PUT_ERROR;
		return FALSE;
	}

	return TRUE;

}//	SetBitmapParams
//--------------------------------------------------------------------------