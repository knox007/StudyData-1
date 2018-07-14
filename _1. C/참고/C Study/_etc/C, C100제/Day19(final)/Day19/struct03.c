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
	enum ITEM itemKind;		//������ ����
	char name[50];			//������ �̸�
	char description[100];	//������ ����
	int attribute;			//������ Ư��
	int price;				//������ ���� 
	int count;				//������ ����
};

/*
	����ü ��� ��
*/
void main(){

	struct tagItemInfo armor1;
	struct tagItemInfo weapon1;

	armor1.itemKind = ITEM_ARMOR;
	strcpy(armor1.name , "�ʺ��ڿ� ��");
	armor1.price = 1000;
	armor1.attribute = 1;
	strcpy(armor1.description, "�ʺ��ڰ� �Դ� ������ ���̴�");
	armor1.count = 1;

	weapon1.itemKind = ITEM_WEAPON;
	weapon1.price = 30000;


}