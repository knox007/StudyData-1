#ifndef _PUTSINGLETON_H_
#define	_PUTSINGLETON_H_
#pragma once


#include <cassert>

template<typename objclass>
class CPUTSingleton
{
private:
	static objclass* m_pSingleton;

public:
	static objclass* CreateSingleton()
	{
		if(!m_pSingleton)
			m_pSingleton = new objclass;

		return m_pSingleton;
	}

	static void	DestroySingleton()
	{
		if(m_pSingleton)
		{
			delete m_pSingleton;
			m_pSingleton = NULL;
		}
	}

protected:
	CPUTSingleton()				{}
	virtual ~CPUTSingleton()	{}
};

template<class objclass>
objclass*	CPUTSingleton<objclass>::m_pSingleton = NULL;


#define	CREATESINGLETON( inst )		inst::CreateSingleton()	
#define DESTROYSINGLETON( inst )	inst::DestroySingleton()
#endif	//	_PUTSINGLETON_H_
