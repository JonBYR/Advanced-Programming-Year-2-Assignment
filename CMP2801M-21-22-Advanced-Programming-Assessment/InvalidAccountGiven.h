#pragma once
#include <string>
using namespace std;
class InvalidAccountGiven
{
public:
	InvalidAccountGiven(string a);
	string getMessage();
private:
	string invalidAccount;
};

