//===============================================
#pragma once
//===============================================
#include<iostream>

template<typename Type>
class CTempSingleton
{	
	static Type* m_pInstance;
protected:
	//----------------------	
	CTempSingleton()	{}
	virtual ~CTempSingleton() {}
	//----------------------
	
public:	
	//----------------------
	static Type* GetInstance()
	{
		if (!m_pInstance)
			m_pInstance = new Type;

		return m_pInstance;
	}
	//----------------------
	static void DestroyInstance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = NULL;
		}
	}
	//----------------------
};// class CSingleton
//===============================================
template<typename Type>
Type *CTempSingleton<Type>::m_pInstance = NULL;
//===============================================
