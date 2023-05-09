#include "Current.h"
Current::Current(double b) throw (AccountExistsException) : Account(b) //current only uses balance so it uses the first overloaded parent constructor
{
	if (currentExists == true) 
	{
		throw AccountExistsException("Current");
	}
	else 
	{
		currentExists = true; //once the static bool is true than all instances of current when trying to be created will have currentExists set to true, preventing multiple currents from being made
	}
}
void Current::deposit(double amount) //funnctionality given to the pure virtual members of the account class
{
	double currentAmount = getBalance();
	currentAmount = currentAmount + amount;
	setBalance(currentAmount);
}
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
string Current::toString() 
{
	return "This is a current account";
}
int Current::getOverdraft() const 
{
	return overdraft;
}
bool Current::currentExists = false; //initialises the static variable