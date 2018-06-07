#ifndef _PUTTIMEREX_H_
#define _PUTTIMEREX_H_

#pragma once

class CPUtTimerEx
{
public:
	// Ctor/Dtor ////////////////////////////////////
	CPUtTimerEx()			{ InitData(); }	
	void	InitData();	
	//////////////////////////////////// Ctor/Dtor //

	void	Reset();	//	타이머 재설정
	void	Start();	//	타이머 시작
	void	Stop();		//	타이머 정지 또는 일시정지
	void	Advance();	//	타이머를 0.1초 당긴다.
	double	GetAbsoluteTime();	//	순수 시스템 시간을 얻는다.
	double	GetTime();			//	현재 시간을 얻는다.
	double	GetElapsedTime();	//	경과 시간을 얻는다.
	void	GetTimeValues( double *pfTime, double *pfAbsoluteTime, float *pfElapsedTime );	// 모든 시간값을 얻는다.
	bool	IsStopped();		//	타이머가 멈췄다면 true를 반환.

	//	현재 스레드를 현재 프로세서로 제한한다.
	//	이것은 타이밍 코드가 오직 한가지 프로세서에서만 실행됨과 
	//	전원 관리장치로부터 어떠한 나쁜 영향도 끼치지 않음을 보증한다.
	void	LimitThreadAffinityToCurrentProc();

protected:
	LARGE_INTEGER	GetAdjustedCurrentTime();

	bool		m_bUsingQPF;
	bool		m_bTimerStopped;
	LONGLONG	m_llQFPTicksPerSec;

	LONGLONG	m_llStopTime;
	LONGLONG	m_llLastElapsedTime;
	LONGLONG	m_llBaseTime;
};

#endif	//	_PUTTIMEREX_H_