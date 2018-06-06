//=============================================================
//	http://www.crocus.co.kr/604
// Map Test.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.

/*

연관 컨테이너 Map

- 키와 값 한쌍으로 데이터를 관리.
- 중복된 키를 허용하지 않음.(Multimap 은 가능)
- 키에 의해서 자동으로 정렬.
- 임의 접근 연산자("[]")로 데이터에 접근 가능.

*/

//=============================================================
#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <map>
using namespace std;
//=============================================================
typedef map<int, int>			MapIntInt;
typedef MapIntInt::iterator		MapIntIntIter;

typedef map<string, string>		MapStrStr;
typedef MapStrStr::iterator		MapStrStrIter;

typedef pair<string, string>	PairStrStr;
typedef pair<int, int>			PairIntInt;
//=============================================================
void ShowData(MapStrStr& map)
{
	for (auto it = map.begin(); it != map.end(); it++)
		cout << (it->first.c_str()) << ' ' << (it->second.c_str()) << endl;

	cout << endl;

}//	void ShowData(MapStrStr& map)
//=============================================================
void ShowData(MapIntInt& map)
{
	for (auto it = map.begin(); it != map.end(); it++)
		cout << (it->first) << ' ' << (it->second) << endl;

	cout << endl;

}//	void ShowData(MapIntInt& map)
//=============================================================
template <typename TMap, typename TPair>
bool Insert(TMap& map, TPair pair)
{
	if (map.insert(pair).second == false)
		return false;

	return true;

}//	template <typename TMap, typename TPair> bool Insert(TMap& map, TPair pair)
//=============================================================
int main()
{
	//---------------------------
	// 할당 1.
	map<int, int> m1 = { { 0,1 },{ 1,2 },{ 2,3 },{ 4,4 } };	
	cout << "==== m1 할당 ====" << endl;
	ShowData(m1);

	// 할당 2.	임의 접근자를 이용한 방식.
	map<int, int> m2;
	m2[0] = 1;
	m2[1] = 2;	

	// 할당 3.	insert
	m2.insert({2,3});	

	// 할당 4.	pair를 이용한 insert
	pair<int, int> pairTmpInt(4, 5);
	if (Insert(m2, pairTmpInt) == false)
		cout << "추가 실패 T.T" << endl;
	else
		cout << "추가 성공!!" << endl;
	cout << endl;
	
	cout << "==== m2 할당 ====" << endl;
	ShowData(m2);


	//---------------------------
	cout << "==== m2 크기 ====" << endl;
	cout << "m2.size() : " << m2.size() << endl;
	cout << endl;


	//---------------------------
	cout << "==== 기본 초기값 ====" << endl;
	// map은 0으로 초기화 됨을 알 수 있다.
	for (int i = 0; i < 5; i++)
	{
		if (m1[i] == m2[i])
			cout << "m1[" << i << "] and m2[" << i << "] are same.  value = " << m1[i] << endl;
		else
		{
			cout << "m1[" << i << "] and m2[" << i << "] are different." << endl;
			cout << "m1[" << i << "] = " << m1[i] << endl;
			cout << "m2[" << i << "] = " << m2[i] << endl;
		}
	}
	cout << endl;


	//---------------------------
	// map은 string이 [ ] 사이에 들어갈 수 있다.
	cout << "==== key값으로 string 사용 ====" << endl;
	map<string, string> m3;	
	m3["hello"] = "HELLO";	
	m3["world"] = "WORLD";
	m3["korea"] = "korea";
	ShowData(m3);
	

	//---------------------------
	//	중복된 키에 데이터 입력.
	cout << "==== 기존에 있는 hello 키에 데이터 입력 ====" << endl;
	PairStrStr pairTmpStr("hello", "MYHello");
	if(Insert(m3, pairTmpStr) == false)
		cout << "추가 실패 T.T" << endl;
	cout << endl;


	//---------------------------
	cout << "==== string 사용 1 ====" << endl;
	cout << "m3[\"hello\"] = " << m3["hello"].c_str() << endl;
	cout << "m3[\"world\"] = " << m3["world"].c_str() << endl;
	cout << endl;

	cout << "==== string 사용 2 ====" << endl;
	cout << m3["hello"].at(0) << m3["hello"][1] << " " << m3["world"][3] << m3["world"].at(4) << endl;
	cout << endl;


	//---------------------------
	cout << "==== korea 인덱스를 이용한 삭제 ====" << endl;
	m3.erase("korea");
	ShowData(m3);

	return 0;

}//	int main()
//=============================================================