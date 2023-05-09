#include "Account.h"
Account::Account(double b) 
{
	balance = b;
}
Account::Account(double b, string a) 
{
	balance = b;
	accountType = a;
}
double Account::getBalance() const
{
	return balance;
}
void Account::setBalance(double amount)
{
	balance = amount;
}
string Account::toString() //functionality of the virtual method that gets overwritten in child classes
{
	return "This is a generic account";
}
void Account::addTransaction(Transaction* t)
{
	history.push_back(t); //as the vector is full of pointers the parameter must also be a pointer.
	sort(history.begin(), history.end(), Transaction::ascending); //uses the static ascending method defined in Transaction 
	//to sort the vector by transaction value.
}
void Account::viewTransactions()
{
	cout << toString() << endl; //As the child classes have the overwritten virtual methods the toString method called is from the child class
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2); //sets the output so that it shows to two decimal points if the value entered is something like 12.90
	cout << "Account balance is:\x9c" << balance << endl;
	for (int i = 0; i < history.size(); i++) 
	{
		cout << *history[i] << endl; //displays all the information of each transaction using the overloaded << in Transaction
	}
}

void transfer(Account* a1, Account* a2, double amount)
{
	a1->balance = a1->balance - amount;
	a2->balance = a2->balance + amount;
}
//binary search function that first checks if the midpoint is the current value
//if it isn't then it checks if the value is greater than or less than the midpoint
//if the value is less than midpoint the right hand side of the vector is discarded, greater than does the opposite
//if the start point is no longer less than the end point the transaction value doesn't exist
Transaction Account::search(double value, int start, int end) throw (TransactionNotFound)
{
	if (start <= end)
	{
		int mid = (start + end) / 2; 
		if (history[mid]->getValue() == value) return *history[mid]; 
		else if (history[mid]->getValue() < value) return search(value, mid + 1, end); 
		else if (history[mid]->getValue() > value) return search(value, start, mid - 1); 
	}
	else throw TransactionNotFound(value); 
}
int Account::getHistorySize() 
{
	return history.size();
}
string Account::getAccountType() const
{
	return accountType;
}
Account::~Account() //account destructor ensures that all the dynamically created transaction objects that were passed through to the vector are then deleted in the class
{
	for (int i = 0; i < history.size(); i++) 
	{
		delete history[i]; //memory is freed as the dynamic object is deleted
	}
	history.clear(); //pointers cleared from the account
}