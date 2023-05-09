#include "Current.h"
Current::Current(double b) throw (AccountExistsException) : Account(b)
{
	if (currentExists == true) 
	{
		throw AccountExistsException("Current");
	}
	else 
	{
		currentExists = true;
	}
}
//balance is first taken from the parent class, then the deposit amount is added to it, before the balance is reset to the new amount
void Current::deposit(double amount) //functionality given to the pure virtual members of the account class
{
	double currentAmount = getBalance();
	currentAmount = currentAmount + amount;
	setBalance(currentAmount);
}
//balance is first taken from the parent class, then the withdraw amount is removed from it, before the balance is reset to the new amount
void Current::withdraw(double amount) throw (ExceedOverDraftException)
{
	double amountToWithDraw = getBalance();
	amountToWithDraw = amountToWithDraw - amount;
	if (amountToWithDraw < overdraft) 
	{
		throw ExceedOverDraftException(); //custom exception handling that gets caught in the main file if the withdraw goes over the overdraft limit
	}
	else 
	{
		setBalance(amountToWithDraw);
	}
}
string Current::toString() //overwritten toString method from account
{
	return "This is a current account";
}
int Current::getOverdraft() const 
{
	return overdraft;
}
bool Current::currentExists = false; //initialises the static variable