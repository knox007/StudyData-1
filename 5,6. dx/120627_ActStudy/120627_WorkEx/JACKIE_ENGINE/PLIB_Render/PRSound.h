#ifndef _PRSOUND_H_
#define _PRSOUND_H_

#pragma once

#include <dsound.h>


#ifndef DSBCAPS_CUSTOME
#define DSBCAPS_CUSTOME (DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME)
#endif


class CPRSound
{
public:

	enum	eSTATE_
	{
		eSTATE_STOP,
		eSTATE_PLAY
	};

	CPRSound()		{ InitMembers(); }
	~CPRSound()		{ ClearMembers(); }

	bool	Load( HWND hWnd, char*	pszFileName );
	bool	LoadWAV( char *pszFileName, int nFlag = DSBCAPS_CUSTOME );
	bool	Unload();
	bool	Play( DWORD dwFlags = 0 );
	bool	Stop();
	bool	SetVolume( LONG lVol = 100 );
	bool	SetPan( LONG lPan = 0 );

	bool	ReadMMIO( HMMIO hMMioIn, MMCKINFO *pmmckInRiff, LPWAVEFORMATEX *ppwaveFormExInfo );
	bool	OpenWaveFile( LPSTR pszFName, HMMIO *phMMioIn, LPWAVEFORMATEX *ppwfxInfo, MMCKINFO *pckInfoRiff );
	bool	ReadWaveFile( HMMIO hMMioIn, UINT unRead, BYTE *pbyteDst, MMCKINFO *pmmckInfoIn, UINT *punActualread );
	bool	DescendIntoChunk( HMMIO *phMMioIn, MMCKINFO *pmmckInfoIn, MMCKINFO *pckInfoRiff );

	DWORD	GetBufferStatus();		//	사운드 버퍼의 현재 상태.
	DSCAPS	TalkBackToSoundCard();	//	사운드 카드 토크백.	
	DSBCAPS	TalkBackToBuffer();		//	사운드 버퍼 트크백.

	
private:
	void	InitMembers();
	void	ClearMembers();

	HWND	m_hWnd;

	int		m_nRate;
	int		m_nSize;
	eSTATE_	m_eState;

	DSBUFFERDESC			m_dsBufferDesc;
	WAVEFORMATEX			m_waveFormatEx;

	LPDIRECTSOUND8			m_pDxSound;
	LPDIRECTSOUNDBUFFER		m_pDxSoundBuffer;
};


#endif	//	_PRSOUND_H_