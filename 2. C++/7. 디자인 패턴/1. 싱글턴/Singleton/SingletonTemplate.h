//======================================================
#pragma once
#include<iostream>
//======================================================
template<typename T>
class CSingletonTemplate
{	
	//---------------------------
	static T* _pInstance;
	//---------------------------
protected:
	CSingletonTemplate() {};	
	virtual ~CSingletonTemplate() {};
	//---------------------------
public:
	static T* GetInst()
	{
		if (_pInstance == NULL)
			_pInstance = new T();

		return _pInstance;
	}
	//---------------------------
	static void Destroy()
	{
		if (_pInstance != NULL)
		{
			delete _pInstance;
			_pInstance = NULL;
		}
	}
	//---------------------------
};

template <typename T> T* CSingletonTemplate<T>::_pInstance = NULL;
//======================================================