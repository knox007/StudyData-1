#include "StdAfx.h"
#include "PRDShowTexture.h"
#include "PRDShowImage.h"
#include "PUtCommon.h"

struct __declspec(uuid("{71771540-2017-11cf-ae26-0020afd79767}")) CLSID_TextureRenderer;

#define		DX_FORMAT	D3DFMT_A8R8G8B8
//#define		DX_FORMAT	D3DFMT_X8R8G8B8

CPRDShowTexture
::CPRDShowTexture( LPUNKNOWN pUnk, HRESULT *phr, CPRDShowImage* pDShowImg )
: CBaseVideoRenderer(	__uuidof( CLSID_TextureRenderer ), NAME("Texture Renderer"), pUnk, phr ),
						m_bUseDynamicTextures(false)
{
	ASSERT(phr);
	if( phr )
		*phr = S_OK;

	m_pDShowImage = NULL;
	if( pDShowImg )
		m_pDShowImage = pDShowImg;

}//	CPRDShowTexture
//---------------------------------------------------------------------------------------------
HRESULT CPRDShowTexture::CheckMediaType( const CMediaType* pMType )
{
	HRESULT	hr		= E_FAIL;
	VIDEOINFO *pVI	= NULL;

	PUT_IsInValid(GetDShowImage())
	{
		PUT_ERROR;
		return E_FAIL;
	}

	CheckPointer( pMType, E_POINTER );

	PUT_IsDiffer( *pMType->FormatType(), FORMAT_VideoInfo )
	{
		PUT_ERROR;
		return E_INVALIDARG;
	}

	pVI		= (VIDEOINFO*)pMType->Format();

	if( IsEqualGUID( *pMType->Type(), MEDIATYPE_Video ) )
	{		
		GetDShowImage()->SetMediaType(CPRDShowImage::eMEDIATYPE_VIDEO);
		
		if( IsEqualGUID( *pMType->Subtype(), MEDIASUBTYPE_RGB24 ) )
		{
			GetDShowImage()->SetMediaTypeSub(CPRDShowImage::eMEDIATYPESUB_RGB24);
			hr = S_OK;

		}else
		if( IsEqualGUID( *pMType->Subtype(), MEDIASUBTYPE_RGB32 ) )
		{
			GetDShowImage()->SetMediaTypeSub(CPRDShowImage::eMEDIATYPESUB_RGB32);
			hr = S_OK;
		}

	}//	if( IsEqualGUID( *pMType->Type(), MEDIATYPE_Video ) )

	return hr;

}//	CheckMediaType
//---------------------------------------------------------------------------------------------
HRESULT CPRDShowTexture::SetMediaType( LPDIRECT3DDEVICE9 pDev, const CMediaType* pMType )
{
	HRESULT hr	=	E_FAIL;

	UINT	unWidth		=	2;
	UINT	unHeight	=	2;

	PUT_IsInValid( GetDShowImage() )
	{
		PUT_ERROR;
		return E_FAIL;
	}

	D3DCAPS9	caps;
	VIDEOINFO*	pVInfoBmp = NULL;
	pVInfoBmp	=	(VIDEOINFO*)pMType->Format();

	m_lVidWidth		=	pVInfoBmp->bmiHeader.biWidth;
	m_lVidHeight	=	abs(pVInfoBmp->bmiHeader.biHeight);

	if( pVInfoBmp->bmiHeader.biBitCount == 16 ||
		pVInfoBmp->bmiHeader.biBitCount == 24 )
		m_lVidPitch	=	( m_lVidWidth * 3 + 3 ) & ~(3);	//	강제로 피치를 rgb24에 맞춘다.
	else
		m_lVidPitch	=	( m_lVidWidth * 4 + 4 ) & ~(4);	//	강제로 피치를 rgb32에 맞춘다.

	PUT_ZERO_MEMORY( caps );

	hr = pDev->GetDeviceCaps( &caps );

	if( caps.Caps2 & D3DCAPS2_DYNAMICTEXTURES )
		m_bUseDynamicTextures = true;

	if( caps.TextureCaps & D3DPTEXTURECAPS_POW2 )
	{
		while( (long)unWidth < m_lVidWidth )
			unWidth = unWidth << 1;

		while( (long)unHeight < m_lVidHeight )
			unHeight = unHeight << 1;

		GetDShowImage()->UpgradeGeom( m_lVidWidth, unWidth, m_lVidHeight, unHeight );
	}else
	{
		unWidth		=	m_lVidWidth;
		unHeight	=	m_lVidHeight;
	}

	//	미디어 형식에 맞는 텍스쳐 만들기.
	hr = E_UNEXPECTED;
	PRDXTXTRBUFF9 pTex = GetDShowImage()->GetTexture();
	if( m_bUseDynamicTextures )
	{
		hr = pDev->CreateTexture(	unWidth, 
									unHeight, 
									1, 
									D3DUSAGE_DYNAMIC,
									DX_FORMAT,
									D3DPOOL_DEFAULT,
									&pTex,
									NULL );
		PUT_IsFailed( hr )
			m_bUseDynamicTextures = false;

	}//	if( m_bUseDynamicTextures )
	else
	{
		hr = pDev->CreateTexture(	unWidth,
									unHeight,
									1,
									0,
									DX_FORMAT,
									D3DPOOL_MANAGED,
									&pTex,
									NULL );

	}//	~if( m_bUseDynamicTextures )


	PUT_IsFailed( hr )
	{
		PUT_ERROR;
		return hr;	
	}

	D3DSURFACE_DESC ddsd;
	PUT_ZERO_MEMORY( ddsd );

	hr = GetDShowImage()->GetTexture()->GetLevelDesc( 0, &ddsd );
	PUT_IsFailed( hr )
	{
		PUT_ERROR;
		return hr;
	}

	CComPtr<IDirect3DSurface9>	pSurf;
	hr = GetDShowImage()->GetTexture()->GetSurfaceLevel(0, &pSurf);
	PUT_IsSucceeded( hr )
		pSurf->GetDesc(&ddsd);
	GetDShowImage()->SetD3DFormat(ddsd.Format);

	if( GetDShowImage()->GetD3DFromat() != DX_FORMAT &&
		GetDShowImage()->GetD3DFromat() != D3DFMT_A1R5G5B5 )
	{
		PUT_ERROR;
		return VFW_E_TYPE_NOT_ACCEPTED;
	}

	return hr;

}//	SetMediaType
//---------------------------------------------------------------------------------------------
HRESULT	CPRDShowTexture::DoRenderSample( IMediaSample* pMSample )
{
	BYTE	*pByteBmpBuff, *pByteTextureBuff;
	long	lTexturePitch;

	BYTE	*pByteSrc	=	NULL;
	DWORD	*pdwSrc		=	NULL;
	DWORD	*pdwDst		=	NULL;
	UINT	unRow = 0, unCol = 0, unWidth = 0;

	PUT_IsInValid( GetDShowImage() )
	{
		PUT_ERROR;
		return E_FAIL;
	}

	CheckPointer( pMSample, E_POINTER );
	CheckPointer( GetDShowImage()->GetTexture(), E_UNEXPECTED );

	pMSample->GetPointer( &pByteBmpBuff );

	HRESULT	hr = S_OK;
	D3DLOCKED_RECT	d3dLockRect;
	if( m_bUseDynamicTextures )
	{
		hr = GetDShowImage()->GetTexture()->LockRect( 0, &d3dLockRect, 0, D3DLOCK_DISCARD );
		PUT_IsFailed( hr )
		{
			PUT_ERROR;
			return hr;
		}
	}//	if( m_bUseDynamicTextures )
	else
	{
		hr = GetDShowImage()->GetTexture()->LockRect( 0, &d3dLockRect, 0, 0 );
		PUT_IsFailed( hr )
		{
			PUT_ERROR;
			return hr;
		}

	}//	~if( m_bUseDynamicTextures )
	
//	pByteTextureBuff	=	(BYTE*)( d3dLockRect.pBits );
	pByteTextureBuff	=	static_cast<byte*>( d3dLockRect.pBits );
	lTexturePitch		=	d3dLockRect.Pitch;

	if( GetDShowImage()->GetD3DFromat() == DX_FORMAT )
	{
		unWidth	=	m_lVidWidth / 4;

		PUT_IsSame( GetDShowImage()->GetMediaTypeSub(), CPRDShowImage::eMEDIATYPESUB_RGB24 )
		{
			for( unRow = 0; unRow < (UINT)m_lVidHeight; ++unRow )
			{
				pdwSrc	=	(DWORD*)pByteBmpBuff;
				pdwDst	=	(DWORD*)pByteTextureBuff;

				for( unCol = 0; unCol < unWidth; ++unCol )
				{
					pdwDst[0]	=	pdwSrc[0] | 0xff000000;
					pdwDst[1]	=	( ( pdwSrc[1] << 8 ) | 0xff000000 ) | ( pdwSrc[0] >> 24 );
					pdwDst[2]	=	( ( pdwSrc[2] << 16 ) | 0xff000000 ) | ( pdwSrc[0] >> 16 );
					pdwDst[3]	=	0xff000000 | ( pdwSrc[2] >> 8 );
					pdwDst += 4;
					pdwSrc += 3;

				}//	for( unCol = 0; unCol < unWidth; ++unCol )


				//	정렬되지 않은 바이트가 남아있을지 모른다.
				pByteSrc	=	(BYTE*)pdwSrc;
				for( unCol = 0; (UINT)m_lVidWidth; ++unCol )
				{
					*pdwDst	=	0xff000000				|
								( pByteSrc[2] << 16 )	|
								( pByteSrc[1] << 8 )	|
								( pByteSrc[0] );
					++pdwDst;
					pByteSrc	+= 3;

				}//	for( unCol = 0; (UINT)m_lVidWidth; ++unCol )

				pByteBmpBuff		+=	m_lVidPitch;
				pByteTextureBuff	+=	lTexturePitch;

			}//	for( unRow = 0; unRow < (UINT)m_lVidHeight; ++unRow )

		}//	PUT_IsSame( GetDShowImage()->GetMediaTypeSub(), CPRDShowImage::eMEDIATYPESUB_RGB24 )
		else
		PUT_IsSame( GetDShowImage()->GetMediaTypeSub(), CPRDShowImage::eMEDIATYPESUB_RGB32 )
		{
			for( unRow = 0; unRow < (UINT)m_lVidHeight; ++unRow )
			{
				pdwSrc	=	(DWORD*)pByteBmpBuff;
				pdwDst	=	(DWORD*)pByteTextureBuff;

				for( unCol = 0; unCol < unWidth; ++unCol )
				{
					pdwDst[0]	=	pdwSrc[0];
					pdwDst[1]	=	pdwSrc[1];
					pdwDst[2]	=	pdwSrc[2];
					pdwDst[3]	=	pdwSrc[3];

					pdwDst	+=	4;
					pdwSrc	+=	4;

				}//	for( unCol = 0; unCol < unWidth; ++unCol )

				pByteBmpBuff		+=	m_lVidPitch;
				pByteTextureBuff	+=	lTexturePitch;

			}//	for( unRow = 0; unRow < (UINT)m_lVidHeight; ++unRow )

		}//	PUT_IsSame( GetDShowImage()->GetMediaTypeSub(), CPRDShowImage::eMEDIATYPESUB_RGB32 )

	}//	if( GetDShowImage()->GetD3DFromat() == DX_FORMAT )


	PUT_IsSame( GetDShowImage()->GetD3DFromat(), D3DFMT_A1R5G5B5 )
	{
		for( int nHei = 0; nHei < m_lVidHeight; ++nHei )
		{
			BYTE	*pByteBmpBuffOld		=	pByteBmpBuff;
			BYTE	*pByteTextureBuffOld	=	pByteTextureBuff;

			for( int nWid = 0; nWid < m_lVidWidth; ++nWid )
			{
				*(WORD*)pByteTextureBuff	=	(WORD)
												( 0x8000 + 
												( ( pByteBmpBuff[2] & 0xf8 ) << 7 ) +
												( ( pByteBmpBuff[2] & 0xf8 ) << 2 ) +
												( pByteBmpBuff[0] >> 3 ) );

				pByteTextureBuff	+=	2;
				pByteBmpBuff		+=	3;

			}//	for( int nWid = 0; nWid < m_lVidWidth; ++nWid )

			pByteBmpBuff		=	pByteBmpBuffOld		+	m_lVidPitch;
			pByteTextureBuff	=	pByteTextureBuffOld	+	lTexturePitch;

		}//	for( int nHei = 0; nHei < m_lVidHeight; ++nHei )

	}//	PUT_IsSame( GetDShowImage()->GetD3DFromat(), D3DFMT_A1R5G5B5 )

	PUT_IsFailed( GetDShowImage()->GetTexture()->UnlockRect(0) )
	{
		PUT_ERROR;
		return E_FAIL;
	}

	return S_OK;

}//	DoRenderSample
//---------------------------------------------------------------------------------------------
//	EOF