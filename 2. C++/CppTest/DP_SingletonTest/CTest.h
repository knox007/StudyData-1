#pragma once
#include "TempSingleton.h"
#include <iostream>

using namespace std;

class CTest : public CTempSingleton<CTest>
{
	int m_nValue;
public:
	CTest() { m_nValue = 0; }
	virtual ~CTest(){}
	void AddValue(int val);
	int GetValue();
	void ShowData();
};

