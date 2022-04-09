#pragma once
#include <iostream>
#include "Identity.h"
#include <fstream>
#include "GlobalFile.h"
#include <vector>
#include "teachet.h"
#include "student.h"
#include "computerRoom.h"
using namespace std;
class Manager :public Identity
{
public:

	Manager();

	Manager(string name, string pwd);

	virtual void operMenu();

	void addPerson();

	void showPerson();

	void showComputer();

	void cleanFile();

	void modifyPWD();

	void initVector();

	vector<Student> vStu;

	vector<Teacher> vTea;

	bool checkRepeat(int id, int type);

	vector<ComputerRoom> vCom;


};
