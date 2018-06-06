// CppTest.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//
//========================================================
#include "stdafx.h"
#include<vector>
#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;
//========================================================
template <typename T>
void ShowData(vector<T>& v)
{
	cout << "< ";
	for (int i = 0; i < v.size(); ++i)
		cout << v[i] << " ";
	cout << ">";
	cout << endl;

}//	template <typename T> void ShowData(vector<T>& v)
//========================================================
int main()
{
	//------------------
	//	랜덤 생성기 초기화.
	srand(time(NULL));
	
	//------------------
	//	랜덤 값으로 벡터 설정.
	vector<int> _vec(10);
	for (int i = 0; i < _vec.size(); ++i)
		_vec[i] = rand() % 100;
	
	//------------------
	//	정보 출력.
	cout << "Before : ";
	ShowData(_vec);

	//------------------
	//	짝수 값 제거.
	vector<int>::iterator curIter;
	vector<int>::iterator beginIter = _vec.begin();
	for (curIter = beginIter; curIter != _vec.end();)
	{
		if (*curIter % 2 == 0)
			curIter = _vec.erase(curIter);
		else
			++curIter;

	}//	for (curIter = beginIter; curIter != _vec.end(); ++curIter)
		
	 //------------------
	//	정보 출력.
	cout << "After : ";
	ShowData(_vec);


    return 0;

}//	int main()
//========================================================

