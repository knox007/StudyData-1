//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
/*
	---------------
	1.	List
	---------------

		-	���� �����̳�.

		-	���� ��ũ�� ����Ʈ ����.

		-	����, ������ ����� ��� ��õ.

			-	��� �����̳��� ���� ����.

		-	���� ���� �ݺ���( at(), [] )�� ��� �Ұ�.

*/
//=================================================
//*
#include<list>

bool IsRangeOK(int num)
{
	return 100 <= num && num <= 200;
}

int main()
{	
	list<int> lt;

	//	�߰�.
	lt.push_back(10);
	lt.push_back(20);
	lt.push_back(108);
	lt.push_back(60);
	lt.push_back(10);
	lt.push_back(100);
	lt.push_back(40);
	lt.push_back(50);
	lt.push_back(10);
	lt.push_back(109);
	lt.push_back(30);
	lt.push_back(220);
	lt.push_back(10);

	list<int>::iterator iterCur;

	cout << "--- ��ȸ ---" << endl;
	for (iterCur = lt.begin(); iterCur != lt.end(); iterCur++) {
		cout << *iterCur << " ";
	}
	cout << endl << endl;


	cout << "--- ���Ǻ� ���� 1 ---" << endl;
	lt.remove_if(IsRangeOK);
	for (iterCur = lt.begin(); iterCur != lt.end(); iterCur++) {
		cout << *iterCur << " ";
	}
	cout << endl << endl;


	cout << "--- ���Ǻ� ���� 2 ---" << endl;
	lt.remove(10);
	for (iterCur = lt.begin(); iterCur != lt.end(); iterCur++) {
		cout << *iterCur << " ";
	}
	cout << endl << endl;


	cout << "--- ���� ---" << endl;
	lt.sort();
	for (iterCur = lt.begin(); iterCur != lt.end(); iterCur++) {
		cout << *iterCur << " ";
	}
	cout << endl << endl;


	lt.clear();
	cout << "--- ��ü ���� ---" << endl;
	for (iterCur = lt.begin(); iterCur != lt.end(); iterCur++) {
		cout << *iterCur << " ";
	}
	cout << endl << endl;


	return 0;

}//	int main()
//*/
//=================================================
/*
	Quiz)	�ּҷ� ���� ���α׷��� list�� �����.

			���, ����, ��ȸ, ����, ��ü ���� ��ɸ� ����.
*/
//=================================================