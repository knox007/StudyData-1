//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
/*
	---------------
	1.	Map
	---------------

		-	���� �����̳�.

		-	�迭������ �ƴ� ���� Ž�� Ʈ�� ���� ���.

			-	���� �� Ʈ��( �ڰ� ���� ���� Ʈ�� )

		-	Key / Value �� �̷����.

		-	Ű�� �ߺ��� ����.

			-	multimap�� Ű�� �ߺ��� �㰡.

		-	������ �Ǹ� �ڵ����� ���ĵ�.

		-	Ű�� ���ڿ� ��� ����.

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

	//���ٹ�� 1 
	for (iterCur = m.begin(); iterCur != m.end(); ++iterCur) {
		cout << "[" << iterCur->first << ", " << iterCur->second << "]" << " ";
	}
	cout << endl;

	//���ٹ�� 2 
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

	//	��ü ��ҿ� ��ġ�� ������??
	//	cout << mp["123"] << endl;

	if (mp.count("abc") != 0)
		cout << "abc ����!\n";

	if (mp.count("aaa") != 0)
		cout << "aaa ����!\n";
	else
		cout << "aaa ����!\n";

	std::map<char*, int>::iterator iter;
	//std::map<string, int>::iterator iter;
	for (iter = mp.begin(); iter != mp.end(); iter++)
		cout << (*iter).first << ": " << (iter->second) << endl;

	return 0;
}
//*/
//=================================================
/*
	Quiz)	�ּҷ� ���� ���α׷��� map�� �����.

			���, ����, ��ȸ, ��ü ���� ��ɸ� ����.
*/
//=================================================