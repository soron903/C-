#define _CRT_SECURE_NO_WARNINGS
#include "manager.h"
#include <iostream>
using namespace std;
Manager::Manager()
{
	
}

Manager::Manager(string name, string pwd)
{
	this->m_Name = name;
	this->m_Pwd = pwd;

	this->initVector();
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	ComputerRoom c;
	while (ifs >> c.m_ComId && ifs >> c.m_MaxNum)
	{
		vCom.push_back(c);
	}
	cout << "当前机房数量为：" << vCom.size() << endl;
	ifs.close();

}

void Manager::operMenu()
{
	cout << "\t\t欢迎管理员： " << this->m_Name << " 登录！" << endl;
	cout << "\t\t----------------------------------------------------------" << endl;
	cout << "\t\t|                                                         |" << endl;
	cout << "\t\t|                       1.添加账号                        |" << endl;
	cout << "\t\t|                                                         |" << endl;
	cout << "\t\t|                       2.查看账号                        |" << endl;
	cout << "\t\t|                                                         |" << endl;
	cout << "\t\t|                       3.常看机房                        |" << endl;
	cout << "\t\t|                                                         |" << endl;
	cout << "\t\t|                       4.清空预约                        |" << endl;
	cout << "\t\t|                                                         |" << endl;
	cout << "\t\t|                       5.修改密码                        |" << endl;
	cout << "\t\t|                                                         |" << endl;
	cout << "\t\t|                       0.注销登录                        |" << endl;
	cout << "\t\t|                                                         |" << endl;
	cout << "\t\t----------------------------------------------------------" << endl;
	cout << "请选择您的操作：>" << endl;
}

void Manager::addPerson()
{
	cout << "请输入添加账号的类型" << endl;
	cout << "1.添加学生" << endl;
	cout << "2.添加老师" << endl;

	string fileName;
	string tip;
	ofstream ofs;

	int select = 0;
	string errorTip;//重复错误提示

	do
	{
		cin >> select;
		while (cin.fail())
		{
			cout << "输入选项错误，请重新输入：";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> select;
		}
		switch (select)
		{
		case 1:
			fileName = STUDENT_FILE;
			tip = "请输入学号";
			errorTip = "学号重复，请重新输入";
			break;
		case 2:
			fileName = TEACHER_FILE;
			tip = "请输入职工号";
			errorTip = "职工号重复，请重新输入";
			break;
		default:
			cout << "输入无效，请重新输入：";
			break;
		}
	} while (select != 1 && select != 2);
	
	
	ofs.open(fileName, ios::out | ios::app);
	if (!ofs.is_open())
	{
		cout << "文件打开失败" << endl;
	}
	int id;
	string name;
	string pwd;
	cout << tip << endl;
	while (1)
	{
		
		while (1)
		{
			cin >> id;
			while (cin.fail())
			{
				cout << "输入格式不对，请重新输入" << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> id;
			}

			bool ret = this->checkRepeat(id, select);
			if (ret)
			{
				cout << errorTip << endl;
			}
			else
			{
				break;
			}
			

		}

		if (!cin.fail())
		{
			break;
		}
	}
	
	
	cout << "请输入姓名：" << endl;
	cin >> name;
	cout << "请输入密码：" << endl;
	cin >> pwd;

	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "添加成功" << endl;
	system("pause");
	system("cls");
	ofs.close();
	this->initVector();

}

void Manager::initVector()
{
	vStu.clear();
	vTea.clear();
	//读取学生文件
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败" << endl;
		return;
	}
	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	}
	cout << "当前学生数数量为：" << vStu.size() << endl;
	ifs.close();

	Teacher t;
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败" << endl;
		return;
	}

	while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd)
	{
		vTea.push_back(t);
	}
	cout << "当前老师数量为：" << vTea.size() << endl;
	ifs.close();
}

void Manager::showPerson()
{

}

void Manager::showComputer()
{
	cout << "机房信息如下：" << endl;
	for (vector<ComputerRoom>::iterator itr = vCom.begin();itr != vCom.end();itr++)
	{
		cout << "机房编号: " << itr->m_ComId << " 机房最大容量: " << itr->m_MaxNum << endl;
	}
	system("pause");
	system("cls");
}

void Manager::cleanFile()
{
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();
	cout << "清空成功" << endl;
	system("pause");
	system("cls");

}

bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)
	{
		for (vector<Student>::iterator itr = vStu.begin();itr != vStu.end();itr++)
		{
			if (id == itr->m_Id)
			{
				return true;
			}
		}
	}
	else
	{
		for (vector<Teacher>::iterator itr = vTea.begin();itr != vTea.end();itr++)
		{
			if (id == itr->m_EmpId)
			{
				return true;
			}
		}
	}
	return false;
}

void Manager::modifyPWD()
{
	string oldPwd;
	cout << "请输入原密码进行确认：" << endl;
	cin >> oldPwd;
	ifstream ifs;
	ifs.open(ADMIN_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件打开失败" << endl;
	}
	
	string name;
	string currPwd;
	while (ifs >> name && ifs >> currPwd)
	{
		if (currPwd == oldPwd)
		{
			cout << "密码确认成功！" << endl;
			break;
		}
		else
		{
			cout << "密码确认失败，请重新输入！" << endl;
			ifs.close();
			ifs.open(ADMIN_FILE, ios::in);
			if (!ifs.is_open())
			{
				cout << "文件打开失败" << endl;
			}

			cin >> oldPwd;
		}
	}
	ifs.close();
	string newPwd;
	string comfirmPwd;
	while (1)
	{
		cout << "请输入新密码：" << endl;
		cin >> newPwd;
		cout << "请再次确认密码：" << endl;
		cin >> comfirmPwd;

		if (newPwd == comfirmPwd)
		{
			ofstream ofs;
			ofs.open(ADMIN_FILE, ios::trunc);
			ofs.close();
			ofs.open(ADMIN_FILE, ios::out | ios::app);
			if (!ofs.is_open())
			{
				cout << "文件打开失败" << endl;
				cout << "密码修改失败！" << endl;
				return;
			}
			ofs.clear();
			ofs << name << " " << newPwd << " " << endl;
			cout << "密码修改成功！" << endl;
			ofs.close();
			return;
		}
		else
		{
			cout << "密码修改失败" << endl;
		}
	}
	
}