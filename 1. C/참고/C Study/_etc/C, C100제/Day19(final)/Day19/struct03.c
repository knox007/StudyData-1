#include <stdio.h>
#include <string.h>

enum ITEM{
	ITEM_EMPTY,		// == 0
	ITEM_ARMOR,		// == 1
	ITEM_WEAPON,	// == 2
	ITEM_RING,		// == 3
	ITEM_POTION,
	ITEM_SOLDOUT
};

struct tagItemInfo{
	enum ITEM itemKind;		//아이템 종류
	char name[50];			//아이템 이름
	char description[100];	//아이템 설명
	int attribute;			//아이템 특성
	int price;				//아이템 가격 
	int count;				//아이템 개수
};

/*
	구조체 사용 예
*/
void main(){

	struct tagItemInfo armor1;
	struct tagItemInfo weapon1;

	armor1.itemKind = ITEM_ARMOR;
	strcpy(armor1.name , "초보자용 옷");
	armor1.price = 1000;
	armor1.attribute = 1;
	strcpy(armor1.description, "초보자가 입는 간단한 옷이다");
	armor1.count = 1;

	weapon1.itemKind = ITEM_WEAPON;
	weapon1.price = 30000;


}