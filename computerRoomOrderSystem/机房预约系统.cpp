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
			cout << "注销登录" << endl;
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
			cout << "输入格式不对，请重新输入：";
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
			cout << "注销成功,请重新登录！" << endl;
			system("pause");
			system("cls");
			return;
			break;
		case 0:
			delete man;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
			break;
		default:
			cout << "没有您输入的选项，返回请重新输入！" << endl;
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
			cout << "输入格式不对，请重新输入：" << endl;
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
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
			break;
		default:
			cout << "没有您输入的选项，请重新输入！" << endl;
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
		cout << "文件读取失败" << endl;
		ifs.close();
		return;
	}
	int id = 0;
	string name;
	string pwd;
	
	if (type == 1)
	{
		cout << "请输入您的学号：" << endl;
		cin >> id;
		while (cin.fail())
		{
			cout << "输入格式不对，请重新输入：";
			cin.clear();
			cin.ignore(1024, '\n');
			cin >> id;
		}
	}
	else if (type == 2)
	{
		cout << "请输入您的职工号：" << endl;
		cin >> id;
		while (cin.fail())
		{
			cout << "输入格式不对，请重新输入：";
			cin.clear();
			cin.ignore(1024, '\n');
			cin >> id;
		}
	}
	cout << "请输入用户名：" << endl;
	cin >> name;
	cout << "请输入密码：" << endl;
	cin >> pwd;

	if (type == 1)
	{
		//学生身份验证
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (id == fId && name == fName && pwd == fPwd)
			{
				cout << "学生登陆成功" << endl;
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
		//老师身份验证
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (id == fId && name == fName && pwd == fPwd)
			{
				cout << "教师验证登陆成功" << endl;
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
		//管理员身份验证
		string fName;
		string fPwd;
		while (ifs >> fName && ifs >> fPwd)
		{
			if (name == fName && pwd == fPwd)
			{
				cout << "管理员验证登陆成功" << endl;
				system("pause");
				system("cls");

				//person = new Manager(name, pwd);
				Manager *person = new Manager(name, pwd);
				managerMenu(person);
				return;
			}
		}
	}
	cout << "验证登录失败" << endl;
	system("pause");
	system("cls");
	return;
}

enum options
{
	退出,
	学生代表,
	老师,
	管理员
};

void menu()
{
	cout<<"======================================欢迎来到机房预约系统======================================"<<endl;
	cout << "\t\t----------------------------------------------------------" << endl;
	cout << "\t\t|                                                         |" << endl;
	cout << "\t\t|                       1.学生代表                        |" << endl;
	cout << "\t\t|                                                         |" << endl;
	cout << "\t\t|                       2.老师                            |" << endl;
	cout << "\t\t|                                                         |" << endl;
	cout << "\t\t|                       3.管理员                          |" << endl;
	cout << "\t\t|                                                         |" << endl;
	cout << "\t\t|                       0.退出                            |" << endl;
	cout << "\t\t|                                                         |" << endl;
	cout << "\t\t----------------------------------------------------------" << endl;
	cout << "请输入您的身份: " ;

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
			cout << "输入有误，请重新输入:>";
			cin.clear();
			cin.ignore(1024, '\n');
			cin >> select;
			/*system("pause");
			system("cls");*/
		}

		switch (select)
		{
		case 学生代表:
			loginIn(STUDENT_FILE, 1);
			break;
		case 老师:
			loginIn(TEACHER_FILE, 2);
			break;
		case 管理员:
			loginIn(ADMIN_FILE, 3);
			break;
		case 退出:
			cout << "欢迎下次使用" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "输入有误，请重新输入" << endl;
			system("pause");
			system("cls");

			break;
		}
	}
	

	system("pause");
	return 0;
}