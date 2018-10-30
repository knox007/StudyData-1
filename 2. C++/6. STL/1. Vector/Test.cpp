//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
/*
	---------------
	1.	Vector
	---------------

		-	���� �����̳�.

		-	�迭 ����.

		-	���� ������ ����

		-	����, ������ ����� ��쿡�� ����.

			-	����, ������ �ڸ� �����Ŀ� �ð� �ҿ�.

		-	reserve �Լ��� ũ�⸦ �̸� �Ҵ�.


*/
//=================================================
#include<vector>

int main()
{
	vector<int> vec;

	//	�߰�.
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);

	//	��� ���� - 1.
	cout << "--- ��� ���� (�迭 �ε���)---" << endl;
	for (int i = 0; i < vec.size(); ++i)
		cout << vec[i] << endl;

	//	��� ���� - 2.
	cout << "--- ��� ���� (���ͷ�����)---" << endl;
	vector<int>::iterator iterBegin = vec.begin();
	vector<int>::iterator iterEnd = vec.end();
	vector<int>::iterator iterCur;
	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)
		cout << (*iterCur) << endl;

	//	��� ����.
	cout << "--- ��� ���� ---" << endl;
	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)
	{
		if ((*iterCur) == 2)
		{
			vec.erase(iterCur);
			break;
		}
	}
	iterBegin = vec.begin();
	iterEnd = vec.end();
	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)
		cout << (*iterCur) << endl;

	//	��ü ����.
	cout << "--- ��ü ���� ---" << endl;
	vec.clear();
	iterBegin = vec.begin();
	iterEnd = vec.end();
	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)
		cout << (*iterCur) << endl;


	//	capacity ����.
	cout << "--- data size capacity ---" << endl;
	//	vec.reserve(100);	//	ũ�⸦ �̸� �Ҵ�.
	for (int i = 0; i <= 64; i++) {
		vec.push_back(i + 1);
		cout << "[" << vec[i] << " , " << vec.size() << " , " << vec.capacity() << "]" << endl;
	}

	return 0;

}//	int main()
//=================================================
/*
	Quiz)	�ּҷ� ���� ���α׷��� vector�� �����.

			���, ����, ��ȸ, ��ü ���� ��ɸ� ����.
*/
//=================================================