#pragma once
#include "Account.h"
#include "ExceedOverDraftException.h"
#include "AccountExistsException.h"
class Current : public Account
{
public:
	Current(double b) throw (AccountExistsException);
	virtual void deposit(double amount);
	virtual void withdraw(double amount) throw (ExceedOverDraftException);
	virtual string toString(); //the overwritten methods are called virtual for clarity so that we know these are the overwritten account methods
	int getOverdraft() const;
private:
	const signed int overdraft = -500; //as we know the overdraft is always -£500 the data type should be assigned as a constant signed int and assigned in the header file
	static bool currentExists; //as only one current account can exist a static bool is given as if it's value changes in one instance of a class it changes in all instances of the class, 
	//including new ones.
};

