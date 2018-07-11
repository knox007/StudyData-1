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
			
			cout << "┌────────────────────────────────────┐" << endl;
			cout << "│                          주소록 출력 프로그램                          │" << endl;
			cout << "├────────────────────────────────────┤" << endl;

			for (int i=0; i<cnt; i++) {
				cout << "│[";
				cout.width(2);
				cout << i+1 << "] " << "이름 : " << p[i].name << "\t주소 : " << p[i].addr << "\t번호 : " << p[i].phone << "              │" <<endl;
			}
			cout << "└────────────────────────────────────┘" << endl;
			
			cout << "  뒤로 가시려면 1을 입력하여 주십시오 -> ";
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
			cout << "┌────────────────────────────────────┐" << endl;
			cout << "│                          주소록 추가 프로그램                          │" << endl;
			cout << "├────────────────────────────────────┤" << endl;

			cout << "│1. 이름(3글자)을 입력하여 주십시오 -> ";
			cin >> temp_name;
			
			cout << "│2. 주소를 동만 입력하여 주십시오 ex) 역삼동 -> ";
			cin >> temp_addr;
			
			cout << "│3. 번호를 하이푼(-) 포함하여 입력하여 주십시오 -> ";
			cin >> temp_phone;
			cout << "└────────────────────────────────────┘" << endl;
			
			if ( temp_name.length() == 6 && temp_addr.length() == 6 && temp_phone.length() == 13) {
				break;
			} else {
				cout << endl << "  이름, 주소, 번호를 서식에 맞게 작성하였는지 확인 하십시오. " << endl;
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
			
		cout << "┌────────────────────────────────────┐" << endl;
		cout << "│                          주소록 삭제 프로그램                          │" << endl;
		cout << "├────────────────────────────────────┤" << endl;
		
		for (int i=0; i<cnt; i++) {
			cout << "│[";
			cout.width(2);
			cout << i+1 << "] " << "이름 : " << p[i].name << "\t주소 : " << p[i].addr << "\t번호 : " << p[i].phone << "              │" <<endl;
		}
		cout << "└────────────────────────────────────┘" << endl;
		
		cout << "  삭제하려는 주소록의 번호를 입력 하십시오 -> ";
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
			
		cout << "┌────────────────────────────────────┐" << endl;
		cout << "│                          주소록 수정 프로그램                          │" << endl;
		cout << "├────────────────────────────────────┤" << endl;

		for (int i=0; i<cnt; i++) {
			cout << "│[";
			cout.width(2);
			cout << i+1 << "] " << "이름 : " << p[i].name << "\t주소 : " << p[i].addr << "\t번호 : " << p[i].phone << "              │" <<endl;
		}
		cout << "└────────────────────────────────────┘" << endl;

		cout << "  수정하려는 주소록의 번호를 입력하여 주십시오 -> ";
		cin >> num;

		while(1) {
			cout << endl << "  1. 이름(3글자)을 입력하여 주십시오 -> ";
			cin >> temp_name;
				
			cout << "  2. 주소를 동만 입력하여 주십시오 ex) 역삼동 -> ";
			cin >> temp_addr;
				
			cout << "  3. 번호를 하이푼(-) 포함하여 입력하여 주십시오 -> ";
			cin >> temp_phone;
				
			if ( temp_name.length() == 6 && temp_addr.length() == 6 && temp_phone.length() == 13) {
				break;
			} else {
				cout << endl << "  이름, 주소, 번호를 서식에 맞게 작성하였는지 확인 하십시오. " << endl;
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
			cout << "┌────────────────────────────────────┐" << endl;
			cout << "│                          주소록 관리 프로그램                          │" << endl;
			cout << "├────────────────────────────────────┤" << endl;
			cout << "│1. 주소록 출력  2. 주소록 추가  3. 주소록 삭제  4. 주소록 편집  5. 종료 │" << endl;
			cout << "└────────────────────────────────────┘" << endl;

			cout << endl << "  원하시는 메뉴를 선택하십시오 -> ";
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
				cout << "올바른 메뉴를 선택하여 주십시오" << endl;
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
