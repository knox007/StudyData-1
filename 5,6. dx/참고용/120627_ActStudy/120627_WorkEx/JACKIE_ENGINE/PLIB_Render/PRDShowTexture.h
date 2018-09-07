#ifndef	_PRDSHOWTEXTURE_H_ 
#define	_PRDSHOWTEXTURE_H_
#pragma once

//	당분간 맥스에서 무압축으로 만들것.

#include <atlbase.h>
#include <dshow.h>
#include <vmr9.h>
#include <streams.h>
#pragma warning( disable : 4819 )


class CPRDShowImage;

class CPRDShowTexture : public CBaseVideoRenderer
{
public:
	CPRDShowTexture( LPUNKNOWN pUnk, HRESULT *phr, CPRDShowImage* pDShowImg );
	~CPRDShowTexture()	{}

	HRESULT	CheckMediaType( const CMediaType* pMType );
	HRESULT	SetMediaType( LPDIRECT3DDEVICE9 pDev, const CMediaType* pMType );
	HRESULT	DoRenderSample( IMediaSample* pMSample );

	void			SetDShowImage( CPRDShowImage* pImage )	{ m_pDShowImage = pImage; }
	CPRDShowImage*	GetDShowImage()							{ return m_pDShowImage; }

protected:

	bool	m_bUseDynamicTextures;
	long	m_lVidWidth;
	long	m_lVidHeight;
	long	m_lVidPitch;

	CPRDShowImage	*m_pDShowImage;

};

#endif	//	_PRDSHOWTEXTURE_H_	