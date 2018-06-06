//	http://blockdmask.tistory.com/76
// List Test.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//
//====================================================
#include "stdafx.h"
#include<iostream>
#include<list>
#include<functional>
using namespace std;
//====================================================
typedef list<int> ListInt;
typedef list<int>::iterator ListIntIter;
//====================================================
void ShowData(ListInt& list)
{
	ListIntIter iterCurr;
	ListIntIter iterBegin = list.begin();
	ListIntIter iterEnd = list.end();
	
	iterCurr = iterBegin;
	while (iterCurr != iterEnd)
	{
		cout << *iterCurr << " ";
		++iterCurr;

	}//	while (iterCurr != iterEnd)
	cout << endl;

}//	void ShowData(ListInt& list)
//====================================================
bool IsInRange(int num) { return 10 <= num && num <= 30; }
//====================================================
int main()
{
	//------------------
	ListInt _listTest;	
	//	데이터 초기화.
	_listTest.push_back(10);
	_listTest.push_back(33);
	_listTest.push_back(45);
	_listTest.push_back(23);
	_listTest.push_back(32);
	cout << "====== 초기화 ======" << endl;
	//	데이터 출력.
	ShowData(_listTest);

	//------------------
	_listTest.sort();
	cout << "====== 오름차순 정렬 ======" << endl;
	//	데이터 출력.
	ShowData(_listTest);

	//------------------	
	_listTest.sort(greater<int>());
	cout << "====== 내림차순 정렬 ======" << endl;
	//	데이터 출력.
	ShowData(_listTest);
	
	//------------------	
	_listTest.remove_if(IsInRange);
	cout << "====== 조건부 삭제 ======" << endl;
	//	데이터 출력.
	ShowData(_listTest);
		

    return 0;

}//	int main()
//====================================================