#ifndef	_PUTTIMER_H_
#define _PUTTIMER_H_
#pragma once

#include "PUTSingleton.h"

class CPUTTimer : public CPUTSingleton<CPUTTimer>
{
friend CPUTSingleton<CPUTTimer>;

	CPUTTimer()				{ InitMembers(); }
	virtual ~CPUTTimer()	{ }

public:
	void			InitMembers();

	void			Start();
	void			Stop();
	void			OnUpdate(float fElapsedTime = 0);

	bool			IsStopped()			{ return m_bTimerStopped; }
	float			GetFPS()			{ return m_fFPS; }
	float			GetRunningTime()	{ return m_fRunningTime; }
	float			GetElapsedTime()	{ return m_bTimerStopped ? 0.0f : m_fTimeElapsed; }
	INT64			GetCurrentTime()	{ return m_nCurrentTime; }
	double			GetAbsoluteTime();
	LARGE_INTEGER	GetAdjustedCurrentTime();

private:
	INT64	m_nInitTickPerSecond;
	INT64	m_nCurrentTime;	
	INT64	m_nStopTime;
	INT64	m_nBaseTime;
	INT64	m_nLastTime;
	INT64	m_nLastFPSUpdate;
	INT64	m_nFPSUpdateInterval;	

	UINT	m_nNumFrames;
	float	m_fRunningTime;
	float	m_fTimeElapsed;	
	float	m_fFPS;
	bool	m_bTimerStopped;
};
//	CPUTTimer

#define gUtTimer		CREATESINGLETON(CPUTTimer)
#define gUtTimerDestroy	DESTROYSINGLETON(CPUTTimer)

#endif //	_PUTTIMER_H_
