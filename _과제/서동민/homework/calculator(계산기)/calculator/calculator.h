#pragma once
class Calculator
{
private:
	int Add(int a, int b);
	int Minus(int a, int b);
	int Multi(int a, int b);
	int Divide(int a, int b);

public:	
	void Run();
	Calculator();
	~Calculator();
};

