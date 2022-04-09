#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#include "Identity.h"
#include <fstream>
#include "GlobalFile.h"
#include "student.h"
#include "teachet.h"
#include "manager.h"

void teacherMenu(Identity*& teacher)
{
	while (1)
	{
		teacher->operMenu();

		Teacher* tea = (Teacher*)teacher;
		int select = 0;
		cin >> select;

		if (select == 1)
		{
			tea->showAllOrder();
		}
		else if (select == 2)
		{
			tea->validOrder();
		}
		else
		{
			delete teacher;
			cout << "ע����¼" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}
void managerMenu(Manager *&man)
{
	while (true)
	{
		man->operMenu();

		
		int select = 0;
		cin >> select;
		while (cin.fail())
		{
			cout << "�����ʽ���ԣ����������룺";
			cin.clear();
			cin.ignore(1024, '\n');
			cin >> select;
		}
		switch (select)
		{
		case 1:
			/*cout << 1 << endl;*/
			man->addPerson();
			break;
		case 2:
			/*cout << 2 << endl;*/
			man->showPerson();
			break;
		case 3:
			/*cout << 3 << endl;*/
			man->showComputer();
			break;
		case 4:
			/*cout << 4 << endl;*/
			man->cleanFile();
			break;
		case 5:
			man->modifyPWD();
			delete man;
			cout << "ע���ɹ�,�����µ�¼��" << endl;
			system("pause");
			system("cls");
			return;
			break;
		case 0:
			delete man;
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
			break;
		default:
			cout << "û���������ѡ��������������룡" << endl;
			break;
		}
		
	}
}

void studentMenu(Identity*& student)
{
	while (1)
	{
		student->operMenu();
		Student* stu = (Student*)student;
		int select = 0;

		cin >> select;
		while (cin.fail())
		{
			cout << "�����ʽ���ԣ����������룺" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			cin >> select;
		}
		switch (select)
		{
		case 1:
			stu->applyOrder();
			break;
		case 2:
			stu->showOrder();
			break;
		case 3:
			stu->showAllOrder();
			break;
		case 4:
			stu->cancelOrder();
			break;
		case 0:
			delete student;
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
			break;
		default:
			cout << "û���������ѡ����������룡" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

void loginIn(string fileName, int type)
{
	Identity* person = NULL;
	ifstream ifs;
	ifs.open(fileName, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ��" << endl;
		ifs.close();
		return;
	}
	int id = 0;
	string name;
	string pwd;
	
	if (type == 1)
	{
		cout << "����������ѧ�ţ�" << endl;
		cin >> id;
		while (cin.fail())
		{
			cout << "�����ʽ���ԣ����������룺";
			cin.clear();
			cin.ignore(1024, '\n');
			cin >> id;
		}
	}
	else if (type == 2)
	{
		cout << "����������ְ���ţ�" << endl;
		cin >> id;
		while (cin.fail())
		{
			cout << "�����ʽ���ԣ����������룺";
			cin.clear();
			cin.ignore(1024, '\n');
			cin >> id;
		}
	}
	cout << "�������û�����" << endl;
	cin >> name;
	cout << "���������룺" << endl;
	cin >> pwd;

	if (type == 1)
	{
		//ѧ�������֤
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (id == fId && name == fName && pwd == fPwd)
			{
				cout << "ѧ����½�ɹ�" << endl;
				system("pause");
				system("cls");

				person = new Student(id, name, pwd);
				studentMenu(person);
				return;
			}
		}
	}
	else if (type == 2)
	{
		//��ʦ�����֤
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (id == fId && name == fName && pwd == fPwd)
			{
				cout << "��ʦ��֤��½�ɹ�" << endl;
				system("pause");
				system("cls");

				person = new Teacher(id, name, pwd);
				teacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3)
	{
		//����Ա�����֤
		string fName;
		string fPwd;
		while (ifs >> fName && ifs >> fPwd)
		{
			if (name == fName && pwd == fPwd)
			{
				cout << "����Ա��֤��½�ɹ�" << endl;
				system("pause");
				system("cls");

				//person = new Manager(name, pwd);
				Manager *person = new Manager(name, pwd);
				managerMenu(person);
				return;
			}
		}
	}
	cout << "��֤��¼ʧ��" << endl;
	system("pause");
	system("cls");
	return;
}

enum options
{
	�˳�,
	ѧ������,
	��ʦ,
	����Ա
};

void menu()
{
	cout<<"======================================��ӭ��������ԤԼϵͳ======================================"<<endl;
	cout << "\t\t----------------------------------------------------------" << endl;
	cout << "\t\t|                                                         |" << endl;
	cout << "\t\t|                       1.ѧ������                        |" << endl;
	cout << "\t\t|                                                         |" << endl;
	cout << "\t\t|                       2.��ʦ                            |" << endl;
	cout << "\t\t|                                                         |" << endl;
	cout << "\t\t|                       3.����Ա                          |" << endl;
	cout << "\t\t|                                                         |" << endl;
	cout << "\t\t|                       0.�˳�                            |" << endl;
	cout << "\t\t|                                                         |" << endl;
	cout << "\t\t----------------------------------------------------------" << endl;
	cout << "�������������: " ;

}

int main()
{
	int select;
	while (true)
	{
		menu();
		cin >> select;
		while (cin.fail())
		{
			cout << "������������������:>";
			cin.clear();
			cin.ignore(1024, '\n');
			cin >> select;
			/*system("pause");
			system("cls");*/
		}

		switch (select)
		{
		case ѧ������:
			loginIn(STUDENT_FILE, 1);
			break;
		case ��ʦ:
			loginIn(TEACHER_FILE, 2);
			break;
		case ����Ա:
			loginIn(ADMIN_FILE, 3);
			break;
		case �˳�:
			cout << "��ӭ�´�ʹ��" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "������������������" << endl;
			system("pause");
			system("cls");

			break;
		}
	}
	

	system("pause");
	return 0;
}