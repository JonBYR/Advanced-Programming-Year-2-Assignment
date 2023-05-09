#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Transaction.h"
#include "TransactionNotFound.h" //these are all inherited by the child classes
using namespace std; 
class Account
{
public:
	Account(double b);
	Account(double b, string a); //polymorphism and overloading of account constructors
	float getBalance() const; //methods are constant as the overloaded operators and copy constructor in savings have const object reference parameters
	float getInitialBalance() const; //getters used to hide the functionality of the program
	virtual void deposit(double amount) = 0;
	virtual void withdraw(double amount) = 0; //in order for a class to be abstract it must have pure virtual functions that can be derived by the child class. 
	//This is done by initialising the methods to 0.
	virtual string toString(); //virtual void that will be given functionality in account because it is not pure virtual
	friend void transfer(Account* a1, Account* a2, double amount); //friend functions can be used anywhere in the program
	friend ostream& operator <<(ostream& out, const Account& a); //overloading the << operator which requires a ostream& return
	void addTransaction(Transaction* t);
	void viewTransactions();
	Transaction search(double value, int start, int end) throw (TransactionNotFound); //in order to throw errors in a function the specific error needed to be thrown is specified
	int getHistorySize();
	string getAccountType() const;
	~Account();
protected:
	void setBalance(double amount); //method can only be used by parent and child classes to set the balance
	//only one setter is used as balance is the only thing that changes in account
private:
	double balance;
	double initialBalance; //used in case the initialBalance is required for project
	vector <Transaction*> history;
	string accountType;
};

