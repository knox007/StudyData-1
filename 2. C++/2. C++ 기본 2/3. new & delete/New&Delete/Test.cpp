//=================================================
/*
	1.	new & delete

		-	�޸��� ���� �Ҵ�� ����.

			-	C ����� malloc / free�� ����.

				-	������

					-	malloc	-	void�� ������ ��ȯ.

									���� �����ڰ� ��Ȳ�� �°� ����ȯ�ؼ� ���.

						new		-	�뵵�� �°� �����͸� ��ȯ.

									���� ����ȯ�� �ʿ� ����.

		-	���

			-	��)
					int �� ������ 1���� �޸� ���� �Ҵ� �� ����.

						-	int *pVal = new int;

							delete pVal;

					���̰� size �� int �� �迭�� ���� �޸� ���� �Ҵ� �� ����.
						
						-	int *pArr = new int[ size ];

							delete [] pArr;

*/
//=================================================
#include<iostream>

using namespace std;

int main()
{
	int size;

	cout << "�Ҵ��Ϸ��� �迭�� ũ�� : ";
	cin >> size;


	int *pArr = (int*)malloc(sizeof(int)*size);
	//int *pArr = new int [size];

	
	for (int i = 0; i < size; ++i)
		pArr[i] = i + 10;

	for (int i = 0; i < size; ++i)
		cout << "pArr[ " << i << " ] = " << pArr[i] << endl;

	free(pArr);
	//delete[]pArr;

	return 0;
}


//=================================================
//	����

/*
//	https://egohim.blog.me/70074738205
//	�޸� ���� Ȯ��.	-	1.	����.
#define CRTDBG_MAP_ALLOC 

#include <stdlib.h>
#include <crtdbg.h>


//	#include <new.h>������ operator new�� malloc�� 
//	Derived�ؼ� ���� �� ���, ��� �� �� ����.

#ifdef _DEBUG
#define new new( _NORMAL_BLOCK, __FILE__, __LINE__ )
#endif

#include<iostream>

using namespace std;

int main()
{
	//	�޸� ���� Ȯ��.	-	3.	���.( ��ü ���� )
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//	�޸� ���� Ȯ��.	-	4.	�޸� �� ���� ã��
	//	_CrtSetBreakAlloc(188);

	int size;

	cout << "�Ҵ��Ϸ��� �迭�� ũ�� : ";
	cin >> size;


	int *pArr = (int*)malloc(sizeof(int)*size);
	//int *pArr = new int [size];


	for (int i = 0; i < size; ++i)
		pArr[i] = i + 10;

	for (int i = 0; i < size; ++i)
		cout << "pArr[ " << i << " ] = " << pArr[i] << endl;

	free(pArr);
	//delete[]pArr;


	//	�޸� ���� Ȯ��.	-	2.	���.( ������ ������ )
	//_CrtDumpMemoryLeaks();

	return 0;
}
//*/
//=================================================