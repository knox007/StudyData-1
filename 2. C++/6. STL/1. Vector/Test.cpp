//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
/*
	---------------
	1.	Vector
	---------------

		-	순차 컨테이너.

		-	배열 형식.

		-	임의 접근이 가능

		-	삽입, 삭제가 빈번한 경우에는 비추.

			-	삽입, 삭제후 자리 재정렬에 시간 소요.

		-	reserve 함수로 크기를 미리 할당.


*/
//=================================================
#include<vector>

int main()
{
	vector<int> vec;

	//	추가.
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);

	//	요소 접근 - 1.
	cout << "--- 요소 접근 (배열 인덱스)---" << endl;
	for (int i = 0; i < vec.size(); ++i)
		cout << vec[i] << endl;

	//	요소 접근 - 2.
	cout << "--- 요소 접근 (이터레이터)---" << endl;
	vector<int>::iterator iterBegin = vec.begin();
	vector<int>::iterator iterEnd = vec.end();
	vector<int>::iterator iterCur;
	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)
		cout << (*iterCur) << endl;

	//	요소 삭제.
	cout << "--- 요소 삭제 ---" << endl;
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

	//	전체 삭제.
	cout << "--- 전체 삭제 ---" << endl;
	vec.clear();
	iterBegin = vec.begin();
	iterEnd = vec.end();
	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)
		cout << (*iterCur) << endl;


	//	capacity 참고.
	cout << "--- data size capacity ---" << endl;
	//	vec.reserve(100);	//	크기를 미리 할당.
	for (int i = 0; i <= 64; i++) {
		vec.push_back(i + 1);
		cout << "[" << vec[i] << " , " << vec.size() << " , " << vec.capacity() << "]" << endl;
	}

	return 0;

}//	int main()
//=================================================
/*
	Quiz)	주소록 관리 프로그램을 vector로 만든다.

			등록, 삭제, 조회, 전체 삭제 기능만 적용.
*/
//=================================================