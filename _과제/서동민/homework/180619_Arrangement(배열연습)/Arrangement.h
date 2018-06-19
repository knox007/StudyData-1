#pragma once
#include"header.h"
struct _student{
		int k;
		int e;
		int m;
};
class CArrangement
{
	void Getmaxnum();
	void Getsmallnum();
	void Showgraph();
	void Abcshow();
	void Show();
	void Showavr();
	int _count;
	

	_student S[10];
public:
	void Run();
	CArrangement();
	~CArrangement(void);
};