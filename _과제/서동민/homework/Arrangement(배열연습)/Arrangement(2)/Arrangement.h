#pragma once
#include"header.h"
class CArrangement
{
	int Getmaxnum();
	int Getsmallnum();
	void Show();
	void Showgraph();
public:
	
	int _arr[10];
	int _count;
	void Run();

	CArrangement(int count,int *arr);
	CArrangement();
	~CArrangement(void);
};