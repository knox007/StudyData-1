//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
/*
	---------------
	1.	List
	---------------

		-	순차 컨테이너.

		-	이중 링크드 리스트 구조.

		-	삽입, 삭제가 빈번한 경우 추천.

			-	모든 컨테이너중 가장 빠름.

		-	임의 접근 반복자( at(), [] )는 사용 불가.

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

	//	추가.
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

	cout << "--- 조회 ---" << endl;
	for (iterCur = lt.begin(); iterCur != lt.end(); iterCur++) {
		cout << *iterCur << " ";
	}
	cout << endl << endl;


	cout << "--- 조건부 삭제 1 ---" << endl;
	lt.remove_if(IsRangeOK);
	for (iterCur = lt.begin(); iterCur != lt.end(); iterCur++) {
		cout << *iterCur << " ";
	}
	cout << endl << endl;


	cout << "--- 조건부 삭제 2 ---" << endl;
	lt.remove(10);
	for (iterCur = lt.begin(); iterCur != lt.end(); iterCur++) {
		cout << *iterCur << " ";
	}
	cout << endl << endl;


	cout << "--- 정렬 ---" << endl;
	lt.sort();
	for (iterCur = lt.begin(); iterCur != lt.end(); iterCur++) {
		cout << *iterCur << " ";
	}
	cout << endl << endl;


	lt.clear();
	cout << "--- 전체 삭제 ---" << endl;
	for (iterCur = lt.begin(); iterCur != lt.end(); iterCur++) {
		cout << *iterCur << " ";
	}
	cout << endl << endl;


	return 0;

}//	int main()
//*/
//=================================================
/*
	Quiz)	주소록 관리 프로그램을 list로 만든다.

			등록, 삭제, 조회, 정렬, 전체 삭제 기능만 적용.
*/
//=================================================