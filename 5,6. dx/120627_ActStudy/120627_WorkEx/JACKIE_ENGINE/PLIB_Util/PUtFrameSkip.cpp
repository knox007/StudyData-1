#include "StdAfx.h"
#include "PUtFrameSkip.h"

void	CPUtFrameSkip::Init( float fFps )
{
	m_fSecPerFrame	=	1.0f / fFps;
	m_fTimer		=	0.0f;

}//	Init
//-----------------------------------------------------------------------------------
bool	CPUtFrameSkip::Update( float fElapsed )
{
	m_fTimer	+=	fElapsed;

	if( m_fTimer < 0 )
		return false;

	m_fTimer	-=	m_fSecPerFrame;

	return true;

}//	Update
//-----------------------------------------------------------------------------------
