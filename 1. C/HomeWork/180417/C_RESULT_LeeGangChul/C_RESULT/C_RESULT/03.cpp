#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <crtdbg.h>

using namespace std;

#ifndef _DEBUG
#include new
	new(_CLIENT_BLOCK,_FILE_,_LINE)
#endif

struct Person {
	string name;
	string addr;
	string phone;
};

struct PersonManager {
	int cnt;
	Person *p;
	
	void init_list() {
		p = NULL;
		string line;							
		int line_cnt = 0;	
		ifstream in;

		in.open("address_list.txt");		
		while (getline(in, line)) {			
			line_cnt++;
		}
		in.close();

		cnt = line_cnt/3;
		in.open("address_list.txt");
		if (cnt > 0 ) {
			p = new Person[cnt];
			line_cnt = 0;
			while (getline(in, line)) {	
				if (line_cnt % 3 == 0) {
					p[line_cnt/3].name = line;
				} else if (line_cnt % 3 == 1) {
					p[line_cnt/3].addr = line;
				} else if (line_cnt % 3 == 2) {
					p[line_cnt/3].phone = line;
				}
				line_cnt++;
			}
		}
		in.close();
	}
	void show_list() {
		int num;

		while(1) {
			system("cls");
			
			cout << "����������������������������������������������������������������������������" << endl;
			cout << "��                          �ּҷ� ��� ���α׷�                          ��" << endl;
			cout << "����������������������������������������������������������������������������" << endl;

			for (int i=0; i<cnt; i++) {
				cout << "��[";
				cout.width(2);
				cout << i+1 << "] " << "�̸� : " << p[i].name << "\t�ּ� : " << p[i].addr << "\t��ȣ : " << p[i].phone << "              ��" <<endl;
			}
			cout << "����������������������������������������������������������������������������" << endl;
			
			cout << "  �ڷ� ���÷��� 1�� �Է��Ͽ� �ֽʽÿ� -> ";
			cin >> num;

			if (num == 1) {
				break;
			}
		}
	}
	void add_list() {
		Person *temp_p = NULL;
		string temp_name;
		string temp_addr;
		string temp_phone;

		temp_p = p;

		int flag;

		while(1) {
			system("cls");
			flag = 1;
			cout << "����������������������������������������������������������������������������" << endl;
			cout << "��                          �ּҷ� �߰� ���α׷�                          ��" << endl;
			cout << "����������������������������������������������������������������������������" << endl;

			cout << "��1. �̸�(3����)�� �Է��Ͽ� �ֽʽÿ� -> ";
			cin >> temp_name;
			
			cout << "��2. �ּҸ� ���� �Է��Ͽ� �ֽʽÿ� ex) ���ﵿ -> ";
			cin >> temp_addr;
			
			cout << "��3. ��ȣ�� ����Ǭ(-) �����Ͽ� �Է��Ͽ� �ֽʽÿ� -> ";
			cin >> temp_phone;
			cout << "����������������������������������������������������������������������������" << endl;
			
			if ( temp_name.length() == 6 && temp_addr.length() == 6 && temp_phone.length() == 13) {
				break;
			} else {
				cout << endl << "  �̸�, �ּ�, ��ȣ�� ���Ŀ� �°� �ۼ��Ͽ����� Ȯ�� �Ͻʽÿ�. " << endl;
				Sleep(3000);
			}
				
		}

		p = new Person[cnt+1];

		for (int i=0; i<cnt; i++) {
			p[i] = temp_p[i];
		}

		p[cnt].name = temp_name;
		p[cnt].addr = temp_addr;
		p[cnt].phone = temp_phone;
		
		ofstream out;
		out.open("address_list.txt", ios::app);	
		out << temp_name << endl << temp_addr << endl << temp_phone << endl;
		out.close();
		
		cnt++;
		
		if (temp_p) {
			delete[] temp_p;
			temp_p = nullptr;
		}
		
	}
	void del_list() {
		Person *temp_p;
		int num;

		system("cls");
			
		cout << "����������������������������������������������������������������������������" << endl;
		cout << "��                          �ּҷ� ���� ���α׷�                          ��" << endl;
		cout << "����������������������������������������������������������������������������" << endl;
		
		for (int i=0; i<cnt; i++) {
			cout << "��[";
			cout.width(2);
			cout << i+1 << "] " << "�̸� : " << p[i].name << "\t�ּ� : " << p[i].addr << "\t��ȣ : " << p[i].phone << "              ��" <<endl;
		}
		cout << "����������������������������������������������������������������������������" << endl;
		
		cout << "  �����Ϸ��� �ּҷ��� ��ȣ�� �Է� �Ͻʽÿ� -> ";
		cin >> num;

		temp_p = p;
		p = new Person[cnt-1];

		for (int i=0; i<cnt-1; i++) {
			if (i >= num-1) {
				p[i] = temp_p[i+1];
			} else {
				p[i] = temp_p[i];
			}
		}
		
		ofstream out;
		out.open("address_list.txt");	
		for (int i=0; i<cnt-1; i++) {
			out << p[i].name << endl << p[i].addr << endl << p[i].phone << endl;
		}
		out.close();

		cnt--;
		
		if (temp_p) {
			delete[] temp_p;
			temp_p = nullptr;
		}
	}
	void modi_list() {
		string temp_name;
		string temp_addr;
		string temp_phone;
		int num;

		system("cls");
			
		cout << "����������������������������������������������������������������������������" << endl;
		cout << "��                          �ּҷ� ���� ���α׷�                          ��" << endl;
		cout << "����������������������������������������������������������������������������" << endl;

		for (int i=0; i<cnt; i++) {
			cout << "��[";
			cout.width(2);
			cout << i+1 << "] " << "�̸� : " << p[i].name << "\t�ּ� : " << p[i].addr << "\t��ȣ : " << p[i].phone << "              ��" <<endl;
		}
		cout << "����������������������������������������������������������������������������" << endl;

		cout << "  �����Ϸ��� �ּҷ��� ��ȣ�� �Է��Ͽ� �ֽʽÿ� -> ";
		cin >> num;

		while(1) {
			cout << endl << "  1. �̸�(3����)�� �Է��Ͽ� �ֽʽÿ� -> ";
			cin >> temp_name;
				
			cout << "  2. �ּҸ� ���� �Է��Ͽ� �ֽʽÿ� ex) ���ﵿ -> ";
			cin >> temp_addr;
				
			cout << "  3. ��ȣ�� ����Ǭ(-) �����Ͽ� �Է��Ͽ� �ֽʽÿ� -> ";
			cin >> temp_phone;
				
			if ( temp_name.length() == 6 && temp_addr.length() == 6 && temp_phone.length() == 13) {
				break;
			} else {
				cout << endl << "  �̸�, �ּ�, ��ȣ�� ���Ŀ� �°� �ۼ��Ͽ����� Ȯ�� �Ͻʽÿ�. " << endl;
				Sleep(3000);
			}
		}

		p[num-1].name = temp_name;
		p[num-1].addr = temp_addr;
		p[num-1].phone = temp_phone;

		ofstream out;
		out.open("address_list.txt");	
		for (int i=0; i<cnt; i++) {
			out << p[i].name << endl << p[i].addr << endl << p[i].phone << endl;
		}
		out.close();
	}
	void controller() {
		int ch;

		while(1) {
			system("cls");
			cout << "����������������������������������������������������������������������������" << endl;
			cout << "��                          �ּҷ� ���� ���α׷�                          ��" << endl;
			cout << "����������������������������������������������������������������������������" << endl;
			cout << "��1. �ּҷ� ���  2. �ּҷ� �߰�  3. �ּҷ� ����  4. �ּҷ� ����  5. ���� ��" << endl;
			cout << "����������������������������������������������������������������������������" << endl;

			cout << endl << "  ���Ͻô� �޴��� �����Ͻʽÿ� -> ";
			cin >> ch;

			if (ch == 1) {
				show_list();
			} else if (ch == 2) {
				add_list();
			} else if (ch == 3) {
				del_list();
			} else if (ch == 4) {
				modi_list();
			} else if (ch == 5) {
				break;
			} else {
				cout << "�ùٸ� �޴��� �����Ͽ� �ֽʽÿ�" << endl;
				Sleep(2000);
			}
		}
		
		if (p) {
			delete[] p;
			p = nullptr;
		}
	}
};

void main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	PersonManager pm;

	pm.init_list();
	pm.controller();
}
