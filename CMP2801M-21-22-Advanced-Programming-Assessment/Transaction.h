#pragma once
#define _CRT_SECURE_NO_WARNINGS //needed in order to allow the ctime command to run
#include <iostream>
#include <string>
#include <ctime>
using namespace std;
class Transaction
{
public:
	Transaction(string d, time_t t, double v);
	string toString();
	string getDescription();
	string getDate();
	double getValue();
	friend ostream& operator <<(ostream& out, const Transaction& t);
	static bool ascending(Transaction* t1, Transaction* t2); //needs to be static in order to use it in account
private:
	string desc;
	time_t timeStamp;
	double value;
	char* charTime; //needed to convert the time_t object to a char array via the command c_time
	string displayTime;
};

