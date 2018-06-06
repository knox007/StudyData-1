#include "stdafx.h"
#include "CTest.h"
//=====================================
void CTest::AddValue(int val) { m_nValue += val; }
//=====================================
int CTest::GetValue() {	return m_nValue; }
//=====================================
void CTest::ShowData()
{
	cout << m_nValue;
	cout << endl;
}
//=====================================