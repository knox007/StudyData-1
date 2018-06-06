#include <stdio.h>
#include <string.h>

struct person {
	char name[10];
	int age;
	char sex[10];
	char area[10];
};

void main() {
	struct person p[2];
	FILE *f;
	int i;

	strcpy(p[0].name, "이강철");
	strcpy(p[1].name, "정유진");
	p[0].age = 30;
	p[1].age = 30;
	strcpy(p[0].sex, "남");
	strcpy(p[1].sex, "여");
	strcpy(p[0].area, "신림");
	strcpy(p[1].area, "독산");
	// at wt rt
	f = fopen("abc.txt", "w");

	for (i=0; i<2; i++) {
	fprintf(f, "%s %d %s %s \n",  p[i].name, p[i].age, p[i].sex, p[i].area);
	}
	/*
	for (i=0; i<2; i++) {
		fprintf(f, p[i].name);
		fprintf(f, p[i].age);
		fprintf(f, p[i].sex);
		fprintf(f, p[i].area);
	
	*/
	
	fclose(f);
	// 입력
}



/*
void main() {
	struct person p[2];
	FILE *f;
	int i;

	f = fopen("abc.txt", "r");
	for (i=0; i<2; i++) {
		fscanf(f, "%s %d %s %s", &p[i].name, &p[i].age, &p[i].sex, &p[i].area);
	}
	fclose(f);

	for (i=0; i<2; i++) {
		printf("%s %d %s %s \n", p[i].name, p[i].age, p[i].sex, p[i].area);
	}
}
*/



