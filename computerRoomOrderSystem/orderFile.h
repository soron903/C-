#pragma once
#include <iostream>
#include "GlobalFile.h"
#include <map>
#include <fstream>
using namespace std;

class OrderFile
{
public:
	OrderFile();

	void updateOrder();

	map<int, map<string, string>> m_orderData;

	int m_Size;
};
