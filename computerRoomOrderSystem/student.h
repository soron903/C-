#pragma once
#include <iostream>
using namespace std;
#include <vector>
#include "computerRoom.h"
#include <fstream>
#include "Identity.h"
#include "GlobalFile.h"

class Student :public Identity
{
public:
	Student();

	Student(int id, string name, string pwd);

	virtual void operMenu();

	void applyOrder();

	void showOrder();

	void showAllOrder();

	void cancelOrder();

	int m_Id;
	
	vector<ComputerRoom> vCom;
};
