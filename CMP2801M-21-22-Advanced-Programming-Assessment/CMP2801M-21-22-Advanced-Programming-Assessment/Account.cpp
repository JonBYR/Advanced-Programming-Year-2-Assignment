#include "Account.h"
Account::Account(double b) 
{
	balance = b;
	initialBalance = b;
}
Account::Account(double b, string a) 
{
	balance = b;
	initialBalance = b;
	accountType = a;
}
float Account::getBalance() const
{
	return balance;
}
float Account::getInitialBalance() const
{
	return initialBalance;
}
void Account::setBalance(double amount)
{
	balance = amount;
}
string Account::toString() //functionality of the virtual method that gets overwritten in child classes
{
	return "This is a generic account";
}
bool ascending(Transaction* t1, Transaction* t2)
{
	return (t1->getValue() < t2->getValue()); //comparator function that is used for dereferencing the transaction object pointers for the sort method call
}
void Account::addTransaction(Transaction* t)
{
	history.push_back(t); //as the vector is full of pointers the parameter must also be a pointer.
	sort(history.begin(), history.end(), ascending); //uses the ascending method defined in the account.cpp file to sort the vector by transaction value
}
void Account::viewTransactions()
{
	for (int i = 0; i < history.size(); i++) 
	{
		cout << *history[i] << endl; //displays all the information of each transaction
	}
}

void transfer(Account* a1, Account* a2, double amount)
{
	a1->balance = a1->balance - amount;
	a2->balance = a2->balance + amount; //as it is a friend function we can access the private members of the class as if the function was a member of the class
}

Transaction Account::search(double value, int start, int end) throw (TransactionNotFound) //search function is a binary search
{
	if (start <= end)
	{
		int mid = (start + end) / 2; //midpoint of the vector
		if (history[mid]->getValue() == value) return *history[mid]; //returns the data in transaction which is then used in the overloaded << operator in the transaction class
		else if (history[mid]->getValue() < value) return search(value, mid + 1, end); //if the midpoint is lower than value the left hand side of vector is discarded
		else if (history[mid]->getValue() > value) return search(value, start, mid - 1); //if the midpoint is highter than the value the right hand side is discarded
	}
	else throw TransactionNotFound(value); //if the array has been searched to the point that start has reached the end the transaction doesn't exist
}
ostream& operator <<(ostream& out, const Account& a) 
{
	out.setf(ios::fixed);
	out.setf(ios::showpoint);
	out.precision(2); //sets the output so that it shows to two decimal points if the value entered is something like 12.90
	out << "Account balance is:\x9c" << a.balance;
	return out;
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