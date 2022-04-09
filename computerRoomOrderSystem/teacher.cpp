#define _CRT_SECURE_NO_WARNINGS
#include "teachet.h"

Teacher::Teacher()
{

}

Teacher::Teacher(int empId, string name, string pwd)
{
	this->m_EmpId = empId;
	this->m_Name = name;
	this->m_Pwd = pwd;
}

void Teacher::operMenu()
{
	cout << "\t\t��ӭ��ʦ�� " << this->m_Name << " ��¼��" << endl;
	cout << "\t\t----------------------------------------------------------" << endl;
	cout << "\t\t|                                                         |" << endl;
	cout << "\t\t|                       1.�鿴����ԤԼ                    |" << endl;
	cout << "\t\t|                                                         |" << endl;
	cout << "\t\t|                       2.���ԤԼ                        |" << endl;
	cout << "\t\t|                                                         |" << endl;
	cout << "\t\t|                       0.ע����¼                        |" << endl;
	cout << "\t\t|                                                         |" << endl;
	cout << "\t\t----------------------------------------------------------" << endl;
	cout << "��ѡ�����Ĳ�����>" << endl;
}

void Teacher::showAllOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0;i < of.m_Size;i++)
	{
		cout << i + 1 << ". ";
		cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"] << " ";
		cout << "ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����") << " ";
		cout << "ѧ�ţ�" << of.m_orderData[i]["stuId"] << " ";
		cout << "������" << of.m_orderData[i]["stuName"] << " ";
		cout << "������" << of.m_orderData[i]["roomId"] << " ";
		string status = "״̬��";
		if (of.m_orderData[i]["status"] == "1")
		{
			status += "�����";
		}
		else if (of.m_orderData[i]["status"] == "2")
		{
			status += "ԤԼ�ɹ�";
		}
		else if (of.m_orderData[i]["status"] == "-1")
		{
			status += "���δͨ��";

		}
		else
		{
			status += "ԤԼ��ȡ��";
		}
		cout << status << endl;
	}
	system("pause");
	system("cls");
}

void Teacher::validOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "����л�ԤԼ�ɹ��ļ�¼����ȡ������������Ҫȡ���ļ�¼" << endl;

	vector<int>v;
	int index = 1;
	for (int i = 0;i < of.m_Size;i++)
	{
		
			if (of.m_orderData[i]["status"] == "1")
			{
				v.push_back(i);
				cout << index++ << ".";
				cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"] << " ";
				cout << "ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����") << " ";
				cout << "������" << of.m_orderData[i]["roomId"] << " ";
				string status = "״̬��";
				if (of.m_orderData[i]["status"] == "1")
				{
					status += "�����";
				}
				
				cout << status << endl;
			}
		
	}

	cout << "��������Ҫ��˵ĵļ�¼��0������" << endl;
	unsigned int select = 0;
	int ret = 0;
	while (1)
	{
		cin >> select;
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				cout << "��������˽��" << endl;
				cout << "1.ͨ��" << endl;
				cout << "2.��ͨ��" << endl;
				cin >> ret;
				
				if (ret == 1)
				{
					of.m_orderData[v[select - 1]]["status"] = "2";
				}
				else
				{
					of.m_orderData[v[select - 1]]["status"] = "-1";
				}

				of.updateOrder();
				cout << "������" << endl;
				break;
			}
		}
		cout << "�����������������" << endl;
	}
	system("pause");
	system("cls");
}

