#pragma once
#include <string>
using namespace std;
class InvalidIsa
{
public:
	InvalidIsa(double a);
	string getMessage();
private:
	double amount;
};

