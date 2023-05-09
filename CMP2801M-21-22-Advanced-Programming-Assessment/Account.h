#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Transaction.h"
#include "TransactionNotFound.h" //these are all inherited by the child classes and cpp files
using namespace std; 
class Account
{
public:
	Account(double b);
	Account(double b, string a); //polymorphism and overloading of account constructors
	double getBalance() const; //methods are constant as the copy constructor in savings has const object reference parameters
	virtual void deposit(double amount) = 0;
	virtual void withdraw(double amount) = 0; //methods initialised to 0 so class is abstract
	virtual string toString(); 
	friend void transfer(Account* a1, Account* a2, double amount); //friend functions can be used anywhere in the program
	void addTransaction(Transaction* t);
	void viewTransactions();
	Transaction search(double value, int start, int end) throw (TransactionNotFound);
	int getHistorySize();
	string getAccountType() const;
	~Account();
protected:
	//setBalance should only be used in the child and parent classes to manipulate the balance
	void setBalance(double amount);
private:
	double balance;
	vector <Transaction*> history; //each transaction is made a pointer so a vector of pointers is used
	string accountType;
};

