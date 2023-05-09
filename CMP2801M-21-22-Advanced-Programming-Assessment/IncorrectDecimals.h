#pragma once
#include <string>
using namespace std;
class IncorrectDecimals
{
public:
	IncorrectDecimals(string m, int num);
	string getMessage();
private:
	string errorValue;
	int numberOfDecimals;
};

