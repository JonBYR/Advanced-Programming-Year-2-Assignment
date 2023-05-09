#pragma once
#include "Account.h"
#include "NegativeWithdrawalException.h"
#include "InterestEarning.h"
#include "math.h" //required for the function pow for the function computeInterest
#include "AccountExistsException.h"
#include <string>
using namespace std;
class Savings : public Account, InterestEarning
{
public:
	Savings(double b, string a) throw (AccountExistsException);
	Savings(const Account& a); //copy constructor created for the copying of account values
	virtual void deposit(double amount);
	virtual void withdraw(double amount) throw (NegativeWithdrawalException);
	virtual string toString();
	virtual double computeInterest(int years);
	virtual string getSavingsAccountType();
private:
	double interestRate;
	static bool isa; //isa is a static bool to check that only one isa is made
	string accountType;
};

