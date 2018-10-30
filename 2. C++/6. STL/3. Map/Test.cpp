//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
/*
	---------------
	1.	Map
	---------------

		-	연관 컨테이너.

		-	배열형식이 아닌 이진 탐색 트리 구조 기반.

			-	레드 블랙 트리( 자가 균형 이진 트리 )

		-	Key / Value 로 이루어짐.

		-	키의 중복을 불허.

			-	multimap는 키의 중복을 허가.

		-	삽입이 되면 자동으로 정렬됨.

		-	키로 문자열 사용 가능.

*/
//=================================================
//*
#include<map>
#include<string>
int main()
{
	map<int, string> m;

	m.insert(pair<int, string>(40, "me"));
	m.insert(pair<int, string>(35, "Show"));
	m.insert(pair<int, string>(10, "Dok2"));
	m.insert(pair<int, string>(90, "6"));
	m.insert(pair<int, string>(65, "money"));
	m.insert(pair<int, string>(20, "ZICO"));
	m.insert(pair<int, string>(50, "the"));
	
	map<int, string>::iterator iterCur;

	//접근방법 1 
	for (iterCur = m.begin(); iterCur != m.end(); ++iterCur) {
		cout << "[" << iterCur->first << ", " << iterCur->second << "]" << " ";
	}
	cout << endl;

	//접근방법 2 
	for (iterCur = m.begin(); iterCur != m.end(); ++iterCur) {
		cout << "[" << (*iterCur).first << ", " << (*iterCur).second << "]" << " ";
	}
	cout << endl;

	return 0;

}//	int main()
//*/
//=================================================
/*
#include<map>
#include<string>
int main()
{
	std::map<char*, int> mp;
	//std::map<string, int> mp

	mp["abc"] = 1;
	mp["111"] = 2;

	cout << mp["abc"] << endl;
	cout << mp["111"] << endl;

	//	전체 요소에 미치는 영향은??
	//	cout << mp["123"] << endl;

	if (mp.count("abc") != 0)
		cout << "abc 있음!\n";

	if (mp.count("aaa") != 0)
		cout << "aaa 있음!\n";
	else
		cout << "aaa 없음!\n";

	std::map<char*, int>::iterator iter;
	//std::map<string, int>::iterator iter;
	for (iter = mp.begin(); iter != mp.end(); iter++)
		cout << (*iter).first << ": " << (iter->second) << endl;

	return 0;
}
//*/
//=================================================
/*
	Quiz)	주소록 관리 프로그램을 map로 만든다.

			등록, 삭제, 조회, 전체 삭제 기능만 적용.
*/
//=================================================