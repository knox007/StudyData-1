#include "StdAfx.h"
#include "PRSound.h"
#include "PUtCommon.h"

#define	DSVOLUME_TO_DB(Volume)	((DWORD)(-30 * (100 - Volume ) ) )
//------------------------------------------------------------------------------------
void	CPRSound::InitMembers()
{
	m_hWnd		=	NULL;
	m_nRate		=	0;
	m_nSize		=	0;
	m_eState	=	eSTATE_STOP;

	PUT_ZERO_MEMORY( m_dsBufferDesc );
	PUT_ZERO_MEMORY( m_waveFormatEx );

	m_pDxSound			=	NULL;
	m_pDxSoundBuffer	=	NULL;

}//	InitMembers
//------------------------------------------------------------------------------------
void	CPRSound::ClearMembers()
{
	PUT_SAFE_RELEASE( m_pDxSoundBuffer );
	PUT_SAFE_RELEASE( m_pDxSound );

}//	ClearMembers
//------------------------------------------------------------------------------------
bool	CPRSound::ReadMMIO( HMMIO hMMioIn, MMCKINFO *pmmckInRiff, LPWAVEFORMATEX *ppwaveFormExInfo )
{
	MMCKINFO		ckIn;
	PCMWAVEFORMAT	pcmwf;
	*ppwaveFormExInfo	=	NULL;

	if( mmioDescend( hMMioIn, pmmckInRiff, NULL, 0 ) )
	{
		PUT_ERROR;
		return false;
	}


	if(	( pmmckInRiff->ckid		!=	FOURCC_RIFF ) ||
					( pmmckInRiff->fccType	!=	mmioFOURCC('W','A','V','E')) )
	{
		PUT_ERROR;
		return false;
	}

	ckIn.ckid	=	mmioFOURCC( 'f','m','t',' ' );
	if( mmioDescend( hMMioIn, &ckIn, pmmckInRiff, MMIO_FINDCHUNK ) )
	{
		PUT_ERROR;
		return false;
	}


	if( ( ckIn.cksize < (LONG)sizeof( pcmwf ) ) )
	{
		PUT_ERROR;
		return false;
	}


	if( ( mmioRead( hMMioIn, (HPSTR)&pcmwf, sizeof(pcmwf) ) != sizeof(pcmwf) ) )
	{
		PUT_ERROR;
		return false;
	}


	if( ( pcmwf.wf.wFormatTag == WAVE_FORMAT_PCM ) )
	{
		if( NULL == (*ppwaveFormExInfo = new WAVEFORMATEX ) )
		{
			PUT_ERROR;
			return false;
		}

		memcpy( *ppwaveFormExInfo, &pcmwf, sizeof( pcmwf ) );
		(*ppwaveFormExInfo)->cbSize	=	0;

	}//	if( ( pcmwf.wf.wFormatTag == WAVE_FORMAT_PCM ) )
	else
	{
		WORD	wExtraBytes	=	0;

		if( mmioRead( hMMioIn, (LPSTR)&wExtraBytes, sizeof( WORD ) ) != sizeof( WORD ) )
		{
			PUT_ERROR;
			return false;
		}

		*ppwaveFormExInfo	=	(LPWAVEFORMATEX)new char[ sizeof(WAVEFORMATEX) + wExtraBytes ];

		if( NULL == *ppwaveFormExInfo )
		{
			PUT_ERROR;
			return false;
		}

		memcpy( *ppwaveFormExInfo, &pcmwf, sizeof( pcmwf) );
		(*ppwaveFormExInfo)->cbSize	=	wExtraBytes;

		if( mmioRead(	hMMioIn, 
						(LPSTR)(((BYTE*)&(*ppwaveFormExInfo)->cbSize ) + sizeof(WORD)), wExtraBytes ) != wExtraBytes )
		{
			PUT_ERROR;
			return false;
		}

	}//	~if( ( pcmwf.wf.wFormatTag == WAVE_FORMAT_PCM ) )

	if( mmioAscend( hMMioIn, &ckIn, 0 ) )
	{
		PUT_ERROR;
		return false;
	}

	return true;

}//	ReadMMIO
//------------------------------------------------------------------------------------
bool	CPRSound::OpenWaveFile( LPSTR pszFName, HMMIO *phMMioIn, LPWAVEFORMATEX *ppwfxInfo, MMCKINFO *pckInfoRiff )
{
	HMMIO	hmmioIn	=	NULL;

	hmmioIn	=	mmioOpen( pszFName, NULL, MMIO_ALLOCBUF | MMIO_READ );

	PUT_IsInValid( hmmioIn )
	{
		PUT_ERROR;
		return false;
	}

	PUT_IsInValid( ReadMMIO( hmmioIn, pckInfoRiff, ppwfxInfo ) )
	{		
		mmioClose( hmmioIn, 0 );
		PUT_ERROR;
		return false;
	}

	*phMMioIn	=	hmmioIn;

	return true;

}//	OpenWaveFile
//------------------------------------------------------------------------------------
bool	CPRSound::DescendIntoChunk( HMMIO *phMMioIn, MMCKINFO *pmmckInfoIn, MMCKINFO *pckInfoRiff )
{
	if( mmioSeek( *phMMioIn, pckInfoRiff->dwDataOffset + sizeof(FOURCC), SEEK_SET ) == -1 )
	{
		PUT_ERROR;
		return false;
	}

	pmmckInfoIn->ckid	=	mmioFOURCC( 'd', 'a', 't', 'a' );
	if( mmioDescend( *phMMioIn, pmmckInfoIn, pckInfoRiff, MMIO_FINDCHUNK ) )
	{
		PUT_ERROR;
		return false;
	}

	return true;

}//	DescendIntoChunk
//------------------------------------------------------------------------------------
bool	CPRSound::ReadWaveFile( HMMIO hMMioIn, UINT unRead, BYTE *pbyteDst, MMCKINFO *pmmckInfoIn, UINT *punActualread )
{
	MMIOINFO	mmioInfoIn;
	UINT		unDataIn	=	unRead;

	*punActualread	=	0;

	if( mmioGetInfo( hMMioIn, &mmioInfoIn, 0 ) )
	{
		PUT_ERROR;
		return false;
	}

	if( unDataIn > pmmckInfoIn->cksize )
		unDataIn	=	pmmckInfoIn->cksize;

	pmmckInfoIn->cksize	-=	unDataIn;

	for( DWORD dwCur = 0; dwCur < unDataIn; ++dwCur )
	{
		if( mmioInfoIn.pchNext == mmioInfoIn.pchEndRead )
		{
			if( mmioAdvance( hMMioIn, &mmioInfoIn, MMIO_READ ) )
			{
				PUT_ERROR;
				return false;			
			}

			if( mmioInfoIn.pchNext == mmioInfoIn.pchEndRead )
			{
				PUT_ERROR;
				return false;
			}			

		}//	if( mmioInfoIn.pchNext == mmioInfoIn.pchEndRead )

		*( (BYTE*)pbyteDst + dwCur )	=	*( (BYTE*)mmioInfoIn.pchNext );
		++mmioInfoIn.pchNext;

	}//	for( DWORD dwCur = 0; dwCur < unDataIn; ++dwCur )

	if( mmioSetInfo( hMMioIn, &mmioInfoIn, 0 ) )
	{
		PUT_ERROR;
		return false;
	}

	*punActualread	=	unDataIn;
	
	return true;

}//	ReadWaveFile
//------------------------------------------------------------------------------------
bool	CPRSound::LoadWAV( char *pszFileName, int nFlag )
{
	HMMIO		hWav	=	NULL;
	MMCKINFO	mmChild, mmParent;

	//	사운드 버퍼에 저장될 내용을 임시로 기억해둘 장소.
	BYTE	*pByteWholeSoundBuff;				//	전체 사운드 정보.
	LPVOID	pPrimarySoundBuff	=	NULL;		//	첫번째 사운드 정보.
	LPVOID	pSecondarySoundBuff	=	NULL;		//	두번째 사운드 정보.
	DWORD	dwPrimaryLength, dwSecondaryLength;	//	버퍼의 길이.
	UINT	unWaveSize		=	0;
	LPWAVEFORMATEX	pWfmtx	=	NULL;
	DSBUFFERDESC	dsbd;

	//	웨이브 파일 열기에 실패했다면 에러.
	if( OpenWaveFile( pszFileName, &hWav, &pWfmtx, &mmParent ) == 0 )
	{
		PUT_ERROR;
		return false;
	}

	if( DescendIntoChunk( &hWav, &mmChild, &mmParent ) )
	{
		PUT_ERROR;
		return false;
	}

	memset( &dsbd, 0, sizeof( dsbd ) );
	dsbd.dwSize			=	sizeof( dsbd );
	dsbd.dwFlags		=	nFlag | DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE;
	dsbd.dwBufferBytes	=	mmChild.cksize;
	dsbd.lpwfxFormat	=	pWfmtx;

	//	사운드 버퍼 생성.
	PUT_IsFailed( (m_pDxSound->CreateSoundBuffer( &dsbd, &m_pDxSoundBuffer, NULL ) ) )
	{
		mmioClose( hWav, 0 );
		PUT_ERROR;
		return false;
	}

	m_nSize		=	mmChild.cksize;
	m_eState	=	eSTATE_STOP;

	pByteWholeSoundBuff	=	new BYTE[m_nSize];

	//	웨이브 파일 읽기 실패했다면 에러.
	if( ReadWaveFile( hWav, m_nSize, pByteWholeSoundBuff, &mmChild, &unWaveSize ) == 0 )
	{
		mmioClose( hWav, 0 );
		PUT_ERROR;
		return false;
	}

	//	사운드 버퍼에 잠금 설정.
	PUT_IsFailed( (m_pDxSoundBuffer->Lock(	0, dsbd.dwBufferBytes,
											(LPVOID*)&pPrimarySoundBuff, &dwPrimaryLength,
											&pSecondarySoundBuff, &dwSecondaryLength, 0 ) ) )
	{
		PUT_ERROR;
		return false;
	}

	//	버퍼에 사운드 정보 복사.
	memcpy( pPrimarySoundBuff, pByteWholeSoundBuff, dwPrimaryLength );							//	순환버퍼의 앞부분 복사.
	memcpy( pSecondarySoundBuff, (pByteWholeSoundBuff + dwPrimaryLength ), dwSecondaryLength );	//	순환버퍼의 뒷부분 복사.

	//	사운드 버퍼에 잠금 해제.
	PUT_IsFailed( ( m_pDxSoundBuffer->Unlock( pPrimarySoundBuff, dsbd.dwBufferBytes, NULL, 0 ) ) )
	{
		PUT_ERROR;
		return false;
	}

	PUT_SAFE_DELETE( pByteWholeSoundBuff );

	return true;

}//	LoadWAV
//------------------------------------------------------------------------------------
bool	CPRSound::Load( HWND hWnd, char* pszFileName )
{
	m_hWnd	=	hWnd;

	//	DXSound 생성
	PUT_IsFailed( (DirectSoundCreate8( NULL, &m_pDxSound, NULL ) ) )
	{
		PUT_ERROR;
		return false;
	}

	//	DXSound 협력레벨 설정.
	if( m_pDxSound->SetCooperativeLevel( m_hWnd, DSSCL_NORMAL ) != DS_OK )
	{
		PUT_ERROR;
		return false;
	}

	if( !LoadWAV( pszFileName ) )
	{
		PUT_ERROR;
		return false;
	}

	return true;

}//	Load
//------------------------------------------------------------------------------------
bool	CPRSound::Play( DWORD dwFlags )
{
	m_eState	=	eSTATE_PLAY;

	PUT_IsFailed( ( m_pDxSoundBuffer->Play( 0, 0, dwFlags ) ) )
	{
		PUT_ERROR;
		return false;
	}

	return true;

}//	Play
//------------------------------------------------------------------------------------
bool	CPRSound::Stop()
{
	m_pDxSoundBuffer->SetCurrentPosition( 0 );

	m_eState	=	eSTATE_STOP;

	PUT_IsFailed( m_pDxSoundBuffer->Stop() )
	{
		PUT_ERROR;
		return false;
	}

	return true;
}//	Stop
//------------------------------------------------------------------------------------
bool	CPRSound::SetVolume( LONG lVol )
{
	PUT_IsFailed( m_pDxSoundBuffer->SetVolume( DSVOLUME_TO_DB( lVol ) ) )
	{
		PUT_ERROR;
		return false;
	}

	return true;

}//	SetVolume
//------------------------------------------------------------------------------------
bool	CPRSound::SetPan( LONG lPan )
{
	PUT_IsFailed( m_pDxSoundBuffer->SetPan( lPan ) )
	{
		PUT_ERROR;
		return false;
	}

	return true;

}//	SetPan
//------------------------------------------------------------------------------------
DWORD	CPRSound::GetBufferStatus()
{
	DWORD	dwStatus;
	PUT_IsFailed( m_pDxSoundBuffer->GetStatus( &dwStatus ) )
	{
		PUT_ERROR;
		return false;
	}

	return true;

}//	GetBufferStatus
//------------------------------------------------------------------------------------
DSCAPS	CPRSound::TalkBackToSoundCard()
{
	DSCAPS	dscaps;
	PUT_IsFailed( m_pDxSound->GetCaps( &dscaps ) )
	{
		PUT_ERROR;
		exit(1);
	}

	return dscaps;

}//	TalkBackToSoundCard
//------------------------------------------------------------------------------------
DSBCAPS	CPRSound::TalkBackToBuffer()
{
	DSBCAPS	dsbcaps;
	PUT_IsFailed( m_pDxSoundBuffer->GetCaps( &dsbcaps ) )
	{
		PUT_ERROR;
		exit(1);
	}

	return dsbcaps;

}//	TalkBackToBuffer
//------------------------------------------------------------------------------------
//	EOF