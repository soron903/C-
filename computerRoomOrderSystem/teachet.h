#pragma once
#include <iostream>
#include "Identity.h"
using namespace std;
#include "GlobalFile.h"
#include "orderFile.h"
#include <vector>

class Teacher :public Identity
{

public:

	Teacher();

	Teacher(int empId, string name, string pwd);

	virtual void operMenu();

	void showAllOrder();

	void validOrder();

	int m_EmpId;
};


