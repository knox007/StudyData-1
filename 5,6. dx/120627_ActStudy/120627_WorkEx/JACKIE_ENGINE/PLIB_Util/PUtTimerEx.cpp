#include "StdAfx.h"
#include "PUtTimerEx.h"


// InitData / CloseData ////////////////////////////////////
void CPUtTimerEx::InitData()
{
	m_bTimerStopped		=	true;
	m_llQFPTicksPerSec	=	0;

	m_llStopTime		=	0;
	m_llLastElapsedTime	=	0;
	m_llBaseTime		=	0;

	// 카운터의 빈도를 얻는다.
	LARGE_INTEGER	qwTickPerSec;
	QueryPerformanceFrequency(&qwTickPerSec);
	m_llQFPTicksPerSec = qwTickPerSec.QuadPart;
}
//////////////////////////////////// InitData / CloseData //




// Reset //////////////////////////////////////////////
void CPUtTimerEx::Reset()
{
	LARGE_INTEGER qwTime = GetAdjustedCurrentTime();

	m_llBaseTime		=	qwTime.QuadPart;
	m_llLastElapsedTime	=	qwTime.QuadPart;
	m_llStopTime		=	0;
	m_bTimerStopped		=	false;
}
////////////////////////////////////////////// Reset //




// Start //////////////////////////////////////////////
void
CPUtTimerEx::Start()
{
	LARGE_INTEGER	qwTime;

	QueryPerformanceCounter( &qwTime );

	if( m_bTimerStopped )
		m_llBaseTime += qwTime.QuadPart - m_llStopTime;

	m_llStopTime		=	0;
	m_llLastElapsedTime	=	qwTime.QuadPart;
	m_bTimerStopped		=	false;
}
////////////////////////////////////////////// Start //




// Stop ///////////////////////////////////////////////
void
CPUtTimerEx::Stop()
{
	if( !m_bTimerStopped )
	{
		LARGE_INTEGER	qwTime;
		QueryPerformanceCounter( &qwTime );
		m_llStopTime		=	qwTime.QuadPart;
		m_llLastElapsedTime	=	qwTime.QuadPart;
		m_bTimerStopped		=	true;
	}
}
/////////////////////////////////////////////// Stop //




// Advance ////////////////////////////////////////////
void
CPUtTimerEx::Advance()
{
	m_llStopTime	+= m_llQFPTicksPerSec / 10;
}
//////////////////////////////////////////// Advance //



// GetAbsoluteTime ////////////////////////////////////
double
CPUtTimerEx::GetAbsoluteTime()
{
	LARGE_INTEGER qwTime;
	QueryPerformanceCounter( &qwTime );
	double fTime	=	qwTime.QuadPart / (double)m_llQFPTicksPerSec;
	return fTime;
}
//////////////////////////////////// GetAbsoluteTime //




// GetTime ///////////////////////////////////////////////
double
CPUtTimerEx::GetTime()
{
	LARGE_INTEGER qwTime = GetAdjustedCurrentTime();

	double fAppTime	=	(double)(qwTime.QuadPart - m_llBaseTime) / (double)m_llQFPTicksPerSec;

	return fAppTime;
}
/////////////////////////////////////////////// GetTime //



// GetTimeValues //////////////////////////////////////////////
void
CPUtTimerEx::GetTimeValues( double *pfTime, double *pfAbsoluteTime, float *pfElapsedTime )
{	
	if( pfTime && pfAbsoluteTime && pfElapsedTime )
	{
		return;
	}

	LARGE_INTEGER qwTime	=	GetAdjustedCurrentTime();

	float fElapsedTime	=	(float)((double)(qwTime.QuadPart - m_llLastElapsedTime) / (double)	m_llQFPTicksPerSec);

	m_llLastElapsedTime	=	qwTime.QuadPart;

	// Clamp the timer to non-negative values to ensure the timer is accurate.
	// fElapsedTime can be outside this range if processor goes into a 
	// power save mode or we somehow get shuffled to another processor.  
	// However, the main thread should call SetThreadAffinityMask to ensure that 
	// we don't get shuffled to another processor.  Other worker threads should NOT call 
	// SetThreadAffinityMask, but use a shared copy of the timer data gathered from 
	// the main thread.

	if( fElapsedTime < 0.0f )
		fElapsedTime = 0.0f;

	*pfAbsoluteTime =	qwTime.QuadPart / (double)m_llQFPTicksPerSec;
	*pfTime			=	(qwTime.QuadPart - m_llBaseTime) / (double)m_llQFPTicksPerSec;
	*pfElapsedTime	=	fElapsedTime;
}
////////////////////////////////////////////// GetTimeValues //




// GetElapsedTime /////////////////////////////////////////////////
double
CPUtTimerEx::GetElapsedTime()
{
	LARGE_INTEGER qwTime = GetAdjustedCurrentTime();

	double fElapsedTime	=	(double)(qwTime.QuadPart - m_llLastElapsedTime ) / (double) m_llQFPTicksPerSec;
	m_llLastElapsedTime	=	qwTime.QuadPart;

	// See the explanation about clamping in CPUtTimerEx::GetTimeValues()
	if( fElapsedTime < 0.0f )
		fElapsedTime = 0.0f;

	return fElapsedTime;
}
///////////////////////////////////////////////// GetElapsedTime //




// GetAdjustedCurrentTime /////////////////////////////////////////////
LARGE_INTEGER 
CPUtTimerEx::GetAdjustedCurrentTime()
{
	LARGE_INTEGER qwTime;
	if( m_llStopTime != 0 )
		qwTime.QuadPart = m_llStopTime;
	else
		QueryPerformanceCounter(&qwTime);

	return qwTime;
}
///////////////////////////////////////////// GetAdjustedCurrentTime //





// IsStopped /////////////////////////////////////////////////////
bool
CPUtTimerEx::IsStopped()
{
	return m_bTimerStopped;
}
///////////////////////////////////////////////////// IsStopped //



 