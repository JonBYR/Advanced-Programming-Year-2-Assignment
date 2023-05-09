#pragma once
#include <string>
using namespace std;
class TransactionNotFound
{
public:
	TransactionNotFound(double v);
	string getMessage();
private:
	double errorValue;
};

