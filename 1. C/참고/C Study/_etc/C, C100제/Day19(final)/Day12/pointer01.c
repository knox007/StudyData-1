#include <stdio.h>

int swap(int a, int b){
	int tmp;
	tmp = a;
	a = b;
	b = tmp;
	return a;
}

void main(){

	int a = 10;
	int b = 20;
	//int tmp;
	//tmp = a;
	//a = b;
	//b = tmp;
	swap(a,b);
	printf("a= %d, b = %d\n", a,b);

}