#include "Savings.h"
Savings::Savings(double b, string a) throw (AccountExistsException) : Account(b, a)
{
	accountType = a;
	if (a == "isa") 
	{
		if (isa == true)
		{
			throw AccountExistsException("ISA"); //caught in main if an ISA already exists
		}
		else 
		{
			isa = true;
			interestRate = 0.0115;
		}
	}
	else 
	{
		interestRate = 0.0085; //interest rates are converted to decimals
	}
}
Savings::Savings(const Account& a) : Account(a.getBalance(), a.getAccountType()) //copy constructor needed as the specific data from the Account vector needs to use a method exclusive to savings
{
	if (a.getAccountType() == "isa") //as the copy is only needed for the computeInterest method and is not added to the allAccounts vector, we do not need to check the isa bool 
	{
		interestRate = 0.0115;
	}
	else 
	{
		interestRate = 0.0085;
	}
}
string Savings::getSavingsAccountType()
{
	return accountType;
}
//balance is first taken from the parent class, then the deposit amount is added to it, before the balance is reset to the new amount
void Savings::deposit(double amount) //functionality of the deposit method from Account given
{
	double currentAmount = getBalance();
	currentAmount = currentAmount + amount;
	setBalance(currentAmount);
}
//balance is first taken from the parent class, then the withdraw amount is removed from it, before the balance is reset to the new amount
void Savings::withdraw(double amount) throw (NegativeWithdrawalException) //functionality of the withdraw method from Account given
{
	double amountToWithDraw = getBalance();
	amountToWithDraw = amountToWithDraw - amount;
	if (amountToWithDraw < 0)
	{
		throw NegativeWithdrawalException(); //custom exception handling that gets caught in the main file if the withdrawal goes below 0
	}
	else
	{
		setBalance(amountToWithDraw); //set balance is required for deposit and withdraw to amend to balance
	}
}
string Savings::toString() //overwritten toString method in child
{
	if (accountType == "isa") 
	{
		return "This is an ISA";
	}
	else 
	{
		return "This is a savings account";
	}
}
//firstly the power that will be used for the pow function is calculated with months * years
//then the brackets are calculated as (1 + r/n) with r being interest and n being number of months (12)
//the the value of the brackets is done to the power of months * years
//then this value is multiplied by the current balance
//finally the amount is rounded up using ceil, which multiplies the amount by 100 so no relevant digits are lost before then
//being divided by 100 to get it in required form.
double Savings::computeInterest(int years) 
{
	double currentSavings = getBalance();
	int monthsAndYears = 12 * years; 
	double interest = 1 + (interestRate / 12); 
	double compoundInterest = pow(interest, monthsAndYears); 
	currentSavings = currentSavings * compoundInterest; 
	currentSavings = ceil(currentSavings * 100.00) / 100.00;
	return currentSavings;
}
bool Savings::isa = false; //initialising the static member 