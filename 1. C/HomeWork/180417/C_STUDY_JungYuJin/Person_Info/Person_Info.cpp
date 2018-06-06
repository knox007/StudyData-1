#include <iostream>
#include <crtdbg.h>
#include <string>
#include <windows.h>
#include <fstream>

using namespace std;

#ifndef _DEBUG
#include new
	new(_CLIENT_BLOCK,_FILE_,_LINE)
#endif

struct Person_info {
	string name, address, hp;
};

struct Person_info_package {

	void (Person_info_package::*fp)(); 

	Person_info *person_info_arr;
	int cnt, menu, cnt_temp;
	string str_temp;

	void init() {

		person_info_arr = NULL;

		ifstream fist;
		fist.open("c://Person_Info.txt", std::ios_base::in);
		cnt_temp =0;
		while (getline(fist, str_temp)) {
			cnt_temp++;
		}

		cnt = cnt_temp/5;

		if (fist.is_open() == true) {
			fist.close();
		}

		if (cnt > 0) {
			person_info_arr = new Person_info[cnt];
			fist.open("c://Person_Info.txt", std::ios_base::in);
			cnt_temp = 0;

			while (getline(fist, str_temp)) {
				if (cnt_temp % 5 == 1) {
					person_info_arr[cnt_temp/5].name = str_temp;
				} else if (cnt_temp % 5 == 2) {
					person_info_arr[cnt_temp/5].address = str_temp;
				} else if (cnt_temp % 5 == 3) {
					person_info_arr[cnt_temp/5].hp = str_temp;
				}
				cnt_temp++;
			}

			if (fist.is_open() == true) {
				fist.close();
			}
		}

		view_map();
		Sleep(2000);
		controller();
	}

	void view_map() {
		int wall[10][10] = {{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
							{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							{ 0, 2, 3, 4, 0, 5, 6, 7, 8, 0 },
							{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }};

		for (int i=0; i<10; i++) {
			for (int j=0; j<10; j++) {
				if (wall[i][j] == 0) {
					cout << "  ";
				} else if (wall[i][j] == 1) {
					cout << "��";
				} else if (wall[i][j] == 2) {
					cout << "��";
				} else if (wall[i][j] == 3) {
					cout << "��";
				} else if (wall[i][j] == 4) {
					cout << "��";
				} else if (wall[i][j] == 5) {
					cout << "��";
				} else if (wall[i][j] == 6) {
					cout << "��";
				} else if (wall[i][j] == 7) {
					cout << "��";
				} else if (wall[i][j] == 8) {
					cout << "��";
				} 
			}
			cout << endl;
		}
	}

	void person_info_list() {
		system("cls");
		cout << "����������������������" << endl;
		cout << "               �ּҷ� ����Ʈ              " << endl;
		cout << "����������������������" << endl << endl;

		for (int i=0; i<cnt; i++) {
			cout << "[" << i+1 << "]" << " �̸� : " << person_info_arr[i].name << " | �ּ� : " << person_info_arr[i].address << " | ����ó : " << person_info_arr[i].hp << endl << endl; 
		}

		cout << "------------------------------------------" << endl;
		cout << "�ڷΰ��� �Ͻ÷��� ���ڸ� �Է��ϼ��� �� ";
		cin >> menu;
	}

	void person_info_add() {
		system("cls");
		cout << "����������������������" << endl;
		cout << "                �ּҷ� �߰�               " << endl;
		cout << "����������������������" << endl << endl;

		for (int i=0; i<cnt; i++) {
			cout << "[" << i+1 << "]" << " �̸� : " << person_info_arr[i].name << " | �ּ� : " << person_info_arr[i].address << " | ����ó : " << person_info_arr[i].hp << endl << endl; 
		}

		ofstream fost;
		fost.open("c://Person_Info.txt", std::ios_base::out | std::ios_base::app);

		Person_info *info_add;
		info_add = person_info_arr;
		person_info_arr = new Person_info[cnt+1];

		for (int i=0; i<cnt; i++) {
			person_info_arr[i] = info_add[i];	
		}

		if (info_add) {
			delete[] info_add;
			info_add = nullptr;
		}

		cout << "------------------------------------------" << endl;
		string Name, Address, Hp;
		cout << " �߰� �� �̸����ּҡ� " << endl << " ����ó�� �Է��ϼ��� �� ";
		cin >> Name >> Address >> Hp;

		person_info_arr[cnt].name = Name;
		person_info_arr[cnt].address = Address;
		person_info_arr[cnt].hp = Hp;

		fost << "[" << cnt+1 << "]" << endl << person_info_arr[cnt].name << endl << person_info_arr[cnt].address << endl << person_info_arr[cnt].hp << endl << "��������" << endl;

		cnt++;

		if (fost.is_open() == true) {
			fost.close();
		}
	}

	void person_info_del() {
		while (1) {
			system("cls");

			cout << "����������������������" << endl;
			cout << "                �ּҷ� ����               " << endl;
			cout << "����������������������" << endl << endl;

			for (int i=0; i<cnt; i++) {
				cout << "[" << i+1 << "]" << " �̸� : " << person_info_arr[i].name << " | �ּ� : " << person_info_arr[i].address << " | ����ó : " << person_info_arr[i].hp << endl << endl; 
			}

			cout << "------------------------------------------" << endl;
			int num;
			cout << " ���� �� ��ȣ�� �Է��ϼ��� �� " << endl << " �ڷΰ���� 0�� �����ּ��� �� ";
			cin >> num;

			if (num == 0) {
				break;
			} else {

				Person_info *info_del;
				info_del = person_info_arr;
				person_info_arr = new Person_info[cnt-1];

				for (int i=0; i<cnt-1; i++) {
					if (i>=num-1) {
						person_info_arr[i] = info_del[i+1];
					} else {
						person_info_arr[i] = info_del[i];
					}
				}

				ofstream fost;
				fost.open("c://Person_Info.txt", std::ios_base::out);

				for (int i=0; i<cnt-1; i++) {
					fost << "[" << i+1 << "]" << endl << person_info_arr[i].name << endl << person_info_arr[i].address << endl << person_info_arr[i].hp << endl << "��������" << endl;
				}
		
				if (info_del) {
					delete[] info_del;
					info_del = nullptr;
				}

				if (fost.is_open() == true) {
					fost.close();
				}
				cnt--;		
			}
		}
	}

	void person_info_edit() {
		while (1) {
			system("cls");

			cout << "����������������������" << endl;
			cout << "                �ּҷ� ����               " << endl;
			cout << "����������������������" << endl << endl;

			for (int i=0; i<cnt; i++) {
				cout << "[" << i+1 << "]" << " �̸� : " << person_info_arr[i].name << " | �ּ� : " << person_info_arr[i].address << " | ����ó : " << person_info_arr[i].hp << endl << endl; 
			}

			cout << "------------------------------------------" << endl;
			int num;
			string Name, Address, Hp; 
			cout << " ���� �� ��ȣ�� �Է��ϼ��� �� " << endl << " �ڷΰ���� 0�� �����ּ��� �� ";
			cin >> num;

			if (num == 0) {
				break;
			} else {

				cout << endl;

				cout << " ���� �� �̸����ּҡ� " << endl << " ����ó�� �Է��ϼ��� �� ";
				cin >> Name >> Address >> Hp;

				person_info_arr[num-1].name = Name;
				person_info_arr[num-1].address = Address;
				person_info_arr[num-1].hp = Hp;

		
				ofstream fost;
				fost.open("c://Person_Info.txt", std::ios_base::out);

				for (int i=0; i<cnt; i++) {
					fost << "[" << i+1 << "]" << endl << person_info_arr[i].name << endl << person_info_arr[i].address << endl << person_info_arr[i].hp << endl << "��������" << endl;
				}

				if (fost.is_open() == true) {
					fost.close();
				}
			}
		}
	}

	void controller() {
		while (1) {
			system("cls");

			cout << "������������" << endl;
			cout << "      �ּҷ� �޴�     " << endl;
			cout << "������������" << endl << endl;

			cout << " 1. �ּҷ� ����Ʈ" << endl << endl;
			cout << " 2. �ּҷ� �߰�" << endl << endl;
			cout << " 3. �ּҷ� ����" << endl << endl;
			cout << " 4. �ּҷ� ����" << endl << endl;
			cout << " 5. ����" << endl << endl;
			cout << "----------------------" << endl << endl;

			cout << " �޴��� �Է��ϼ��� �� ";
			cin >> menu;

			if (menu == 1) {		
				fp = &Person_info_package::person_info_list;
			} else if (menu == 2) {
				fp = &Person_info_package::person_info_add;
			} else if (menu == 3) {
				fp = &Person_info_package::person_info_del;
			} else if (menu == 4) {
				fp = &Person_info_package::person_info_edit;
			} else if (menu == 5) {
				system("cls");
				cout << "�ּҷ� ���α׷��� �����մϴ�." << endl << endl;
				break;
			} else {
				system("cls");
				cout << "ERROR!!!" << endl << endl;
				cout << "�ڷΰ��� �Ͻ÷��� ���ڸ� �Է��ϼ��� �� ";
				cin >> menu; 
			}

			(this->*fp)();
		}

		if (person_info_arr) {
			delete[] person_info_arr;
			person_info_arr = nullptr;
		}
	}
};

void main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Person_info_package person_info_package;
	person_info_package.init();
}