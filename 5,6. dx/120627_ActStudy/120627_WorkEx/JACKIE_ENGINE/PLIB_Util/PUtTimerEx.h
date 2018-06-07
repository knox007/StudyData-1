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

	void	Reset();	//	Ÿ�̸� �缳��
	void	Start();	//	Ÿ�̸� ����
	void	Stop();		//	Ÿ�̸� ���� �Ǵ� �Ͻ�����
	void	Advance();	//	Ÿ�̸Ӹ� 0.1�� ����.
	double	GetAbsoluteTime();	//	���� �ý��� �ð��� ��´�.
	double	GetTime();			//	���� �ð��� ��´�.
	double	GetElapsedTime();	//	��� �ð��� ��´�.
	void	GetTimeValues( double *pfTime, double *pfAbsoluteTime, float *pfElapsedTime );	// ��� �ð����� ��´�.
	bool	IsStopped();		//	Ÿ�̸Ӱ� ����ٸ� true�� ��ȯ.

	//	���� �����带 ���� ���μ����� �����Ѵ�.
	//	�̰��� Ÿ�̹� �ڵ尡 ���� �Ѱ��� ���μ��������� ����ʰ� 
	//	���� ������ġ�κ��� ��� ���� ���⵵ ��ġ�� ������ �����Ѵ�.
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