#pragma once
#include <string>
using namespace std;
class IncorrectDouble
{
public:
	IncorrectDouble(string m);
	string getMessage();
private:
	string errorAmount;
};

