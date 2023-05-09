#pragma once
#include <string>
using namespace std;
class AccountExistsException
{
public:
	AccountExistsException(string s);
	string accountErrorMessage();
private:
	string accountName;
};

