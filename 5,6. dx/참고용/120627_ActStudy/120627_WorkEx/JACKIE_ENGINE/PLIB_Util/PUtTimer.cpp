#include "StdAfx.h"
#include "PUTTimer.h"


//--------------------------------------------------------------------
void CPUTTimer::InitMembers()
{
	QueryPerformanceFrequency( (LARGE_INTEGER*)&m_nInitTickPerSecond );

	m_nCurrentTime = m_nLastTime = m_nLastFPSUpdate = 0;
	m_nNumFrames = 0;
	m_fRunningTime = m_fTimeElapsed = m_fFPS = 0.0f;
	m_nFPSUpdateInterval = m_nInitTickPerSecond >> 1;
	
	m_bTimerStopped			=	true;
}//	InitMembers
//--------------------------------------------------------------------
void CPUTTimer::Start()
{
	if( !m_bTimerStopped )
	{
		return;
	}

	QueryPerformanceCounter( (LARGE_INTEGER*)&m_nLastTime );
	m_bTimerStopped	=	false;

}//	Start
//--------------------------------------------------------------------
void CPUTTimer::Stop()
{
	if( m_bTimerStopped )
		return;

	INT64 nStopTime	=	0;
	QueryPerformanceCounter( (LARGE_INTEGER *)&nStopTime );
	m_fRunningTime	+=	(float)(nStopTime - m_nLastTime) /  (float)m_nInitTickPerSecond;
	m_bTimerStopped = true;
}//	Stop
//---------------------------------------------------------------------
void CPUTTimer::OnUpdate(float fElapsedTime)
{
	if( m_bTimerStopped )
		return;

	QueryPerformanceCounter( (LARGE_INTEGER*)&m_nCurrentTime );

	m_fTimeElapsed = (float)( m_nCurrentTime - m_nLastTime ) / (float)m_nInitTickPerSecond;

	m_fRunningTime += m_fTimeElapsed;

	m_nNumFrames++;

	if( m_nCurrentTime - m_nLastFPSUpdate >= m_nFPSUpdateInterval )
	{
		float fCurrentTime	= (float)m_nCurrentTime / (float)m_nInitTickPerSecond;
		float fLastTime		= (float)m_nLastFPSUpdate / (float)m_nInitTickPerSecond;
		m_fFPS				= (float)m_nNumFrames / (fCurrentTime - fLastTime);

		m_nLastFPSUpdate	= m_nCurrentTime;
		m_nNumFrames		= 0;		
	}

	m_nLastTime	= m_nCurrentTime;


}//	Update
//---------------------------------------------------------------------
double	CPUTTimer::GetAbsoluteTime()
{
	LARGE_INTEGER	qwTime;
	QueryPerformanceCounter( &qwTime );

	double dfTime	=	qwTime.QuadPart / (double)m_nInitTickPerSecond;

	return dfTime;
}//	GetAbsoluteTime
//---------------------------------------------------------------------
//	EOF
 