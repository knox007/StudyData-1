#include <iostream>		//	�������� �Ź����� ������� ����.


int main()
{
	//---------------------------------------------
	//	std::cout( Cout << ��´�� )
	//	<< : ��� ������.
	//---------------------------------------------

	//	endl�� ���๮��	
	//	std::cout << "aaa" << std::endl;
	//	std::cout << "aaa";



	//	std::cout << "aaa\n";

	//	������� ����.
	//	std::cout << "aaa " << "bbb " << "ccc " << std::endl;

	//	���� ������ �ʿ� ����.
	//	std::cout << 100;
	//	printf("%d\n", 100);

	//	ȥ�� ��� ����.
	//	std::cout << 1 << " bbb " << "ccc " << std::endl;


	//---------------------------------------------
	//	std::cin( Cin >> �Է� ���� )
	//	>> : �Է� ������.
	//---------------------------------------------
	//---------------
	/*
	int val1, val2;
	std::cout << "Input First Number : ";
	std::cin >> val1;

	std::cout << "Input Second Number : ";
	std::cin >> val2;

	int result = val1 + val2;
	std::cout << " Sum : " << result << std::endl;
	*/
	//---------------
	/*
	int val1, val2;
	std::cout << "Input Two Numbers : ";
	std::cin >> val1 >> val2;

	if (val1 > val2)
		std::cout << val1 << "is bigger than" << val2 << std::endl;
	else if (val1 < val2)
		std::cout << val2 << "is bigger than" << val1 << std::endl;
	else
		std::cout << "Same Number!!" << std::endl;
	*/
	//---------------
	/*
	char name[100];
	char nation[100];

	std::cout << "What is your name??" << std::endl;
	std::cin >> name;

	std::cout << "Where are you from??" << std::endl;
	std::cin >> nation;

	std::cout << "name : " << name << std::endl;
	std::cout << "nation : " << nation << std::endl;
	*/
	//---------------
	/*
	int val1, val2;

	std::cout << "Input Two Numbers : ";
	std::cin >> val1 >> val2;

	std::cout <<std::endl<< "Numbers between " << val1 << " and " << val2 << std::endl;
	for (int n = val1; n <= val2; ++n)
		std::cout << n << " ";
	std::cout << std::endl;
	*/
	//---------------

	return 0;

}