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
	cout << "��ǰ��������Ϊ��" << vCom.size() << endl;
	ifs.close();

}

void Manager::operMenu()
{
	cout << "\t\t��ӭ����Ա�� " << this->m_Name << " ��¼��" << endl;
	cout << "\t\t----------------------------------------------------------" << endl;
	cout << "\t\t|                                                         |" << endl;
	cout << "\t\t|                       1.����˺�                        |" << endl;
	cout << "\t\t|                                                         |" << endl;
	cout << "\t\t|                       2.�鿴�˺�                        |" << endl;
	cout << "\t\t|                                                         |" << endl;
	cout << "\t\t|                       3.��������                        |" << endl;
	cout << "\t\t|                                                         |" << endl;
	cout << "\t\t|                       4.���ԤԼ                        |" << endl;
	cout << "\t\t|                                                         |" << endl;
	cout << "\t\t|                       5.�޸�����                        |" << endl;
	cout << "\t\t|                                                         |" << endl;
	cout << "\t\t|                       0.ע����¼                        |" << endl;
	cout << "\t\t|                                                         |" << endl;
	cout << "\t\t----------------------------------------------------------" << endl;
	cout << "��ѡ�����Ĳ�����>" << endl;
}

void Manager::addPerson()
{
	cout << "����������˺ŵ�����" << endl;
	cout << "1.���ѧ��" << endl;
	cout << "2.�����ʦ" << endl;

	string fileName;
	string tip;
	ofstream ofs;

	int select = 0;
	string errorTip;//�ظ�������ʾ

	do
	{
		cin >> select;
		while (cin.fail())
		{
			cout << "����ѡ��������������룺";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> select;
		}
		switch (select)
		{
		case 1:
			fileName = STUDENT_FILE;
			tip = "������ѧ��";
			errorTip = "ѧ���ظ�������������";
			break;
		case 2:
			fileName = TEACHER_FILE;
			tip = "������ְ����";
			errorTip = "ְ�����ظ�������������";
			break;
		default:
			cout << "������Ч�����������룺";
			break;
		}
	} while (select != 1 && select != 2);
	
	
	ofs.open(fileName, ios::out | ios::app);
	if (!ofs.is_open())
	{
		cout << "�ļ���ʧ��" << endl;
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
				cout << "�����ʽ���ԣ�����������" << endl;
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
	
	
	cout << "������������" << endl;
	cin >> name;
	cout << "���������룺" << endl;
	cin >> pwd;

	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "��ӳɹ�" << endl;
	system("pause");
	system("cls");
	ofs.close();
	this->initVector();

}

void Manager::initVector()
{
	vStu.clear();
	vTea.clear();
	//��ȡѧ���ļ�
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ��" << endl;
		return;
	}
	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	}
	cout << "��ǰѧ��������Ϊ��" << vStu.size() << endl;
	ifs.close();

	Teacher t;
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ��" << endl;
		return;
	}

	while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd)
	{
		vTea.push_back(t);
	}
	cout << "��ǰ��ʦ����Ϊ��" << vTea.size() << endl;
	ifs.close();
}

void Manager::showPerson()
{

}

void Manager::showComputer()
{
	cout << "������Ϣ���£�" << endl;
	for (vector<ComputerRoom>::iterator itr = vCom.begin();itr != vCom.end();itr++)
	{
		cout << "�������: " << itr->m_ComId << " �����������: " << itr->m_MaxNum << endl;
	}
	system("pause");
	system("cls");
}

void Manager::cleanFile()
{
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();
	cout << "��ճɹ�" << endl;
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
	cout << "������ԭ�������ȷ�ϣ�" << endl;
	cin >> oldPwd;
	ifstream ifs;
	ifs.open(ADMIN_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ʧ��" << endl;
	}
	
	string name;
	string currPwd;
	while (ifs >> name && ifs >> currPwd)
	{
		if (currPwd == oldPwd)
		{
			cout << "����ȷ�ϳɹ���" << endl;
			break;
		}
		else
		{
			cout << "����ȷ��ʧ�ܣ����������룡" << endl;
			ifs.close();
			ifs.open(ADMIN_FILE, ios::in);
			if (!ifs.is_open())
			{
				cout << "�ļ���ʧ��" << endl;
			}

			cin >> oldPwd;
		}
	}
	ifs.close();
	string newPwd;
	string comfirmPwd;
	while (1)
	{
		cout << "�����������룺" << endl;
		cin >> newPwd;
		cout << "���ٴ�ȷ�����룺" << endl;
		cin >> comfirmPwd;

		if (newPwd == comfirmPwd)
		{
			ofstream ofs;
			ofs.open(ADMIN_FILE, ios::trunc);
			ofs.close();
			ofs.open(ADMIN_FILE, ios::out | ios::app);
			if (!ofs.is_open())
			{
				cout << "�ļ���ʧ��" << endl;
				cout << "�����޸�ʧ�ܣ�" << endl;
				return;
			}
			ofs.clear();
			ofs << name << " " << newPwd << " " << endl;
			cout << "�����޸ĳɹ���" << endl;
			ofs.close();
			return;
		}
		else
		{
			cout << "�����޸�ʧ��" << endl;
		}
	}
	
}