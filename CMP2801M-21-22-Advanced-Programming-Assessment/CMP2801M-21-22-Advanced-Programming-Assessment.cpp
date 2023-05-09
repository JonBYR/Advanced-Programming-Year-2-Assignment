// CMP2801M-21-22-Advanced-Programming-Assessment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <ctime>
#include <string>
#include <algorithm>
#include "Account.h"
#include "Current.h"
#include "Savings.h"
#include "Transaction.h"
#include "MainMethods.h" //contains methods only to be used by main
#include "ExceedOverDraftException.h"
#include "NegativeWithdrawalException.h"
#include "InvalidAccountGiven.h"
#include "InvalidIsa.h"
#include "AccountExistsException.h"
#include "InvalidIndexException.h"
#include "TransactionNotFound.h"
#include "SameAccount.h"
#include "NotNumeric.h"
#include "IncorrectDecimals.h"
#include "NoAccounts.h"
#include "CurrentProjection.h" //all exceptions included
using namespace std;
int main()
{
	vector <string> parameters;
	string userCommand;
	int viewedIndex = 0; //the most recently viewed index will be stored, however it is initially 0 in case the command view is not used before deposit and withdraw
	vector<Account*> allAccounts; //vector for all account pointers which are dynamically created in the open command

	std::cout << "~~~ Welcome to LincBank! ~~~" << std::endl; //std has been left to show the skeleton code
	cout << "open type initial_deposit : open a current(1), savings(2) or ISA(3) account" << endl;
	cout << "view[index]: view balance and recent transactions" << endl;
	cout << "withdraw sum : withdraw funds from most recently viewed account" << endl;
	cout << "deposit sum : deposit funds into most recently viewed account" << endl;
	cout << "transfer src dest sum : transfer funds between accounts" << endl;
	cout << "project years : project balance forward in time" << endl;
	cout << "search value : search for transaction of specified value on a recently viewed account" << endl;
	cout << "exit: close this application" << endl;
	cout << "options: view these options again" << endl;

	while (userCommand != "exit")
	{
		parameters.clear(); // clear ready for next command
		cout << endl << ">>> ";
		getline(cin, userCommand);
		transform(userCommand.begin(), userCommand.end(), userCommand.begin(), ::tolower); 
		char* cstr = new char[userCommand.length() + 1];
		strcpy(cstr, userCommand.c_str());

		char* token;
		token = strtok(cstr, " ");
		string command;
		while (token != NULL)
		{
			parameters.push_back(token);
			token = strtok(NULL, " ");
		}
		 //Define all commands as per the brief
		try 
		{
			if (userCommand.empty()) throw NotNumeric(); //checks if the string userCommand is empty.
			command = parameters[0]; //if not empty then command takes the first parameter in the vector
		}
		catch (out_of_range const& exc) 
		{
			cout << "Invalid number of arguments given to open an account" << endl;
		}
		catch (NotNumeric)
		{
			cout << "Nothing was entered. Please type a command" << endl;
		}
			if (command.compare("options") == 0) 
			{
				//outputs all options to the user
				cout << "open type initial_deposit : open a current(1), savings(2) or ISA(3) account" << endl;
				cout << "view [index]: view balance and recent transactions" << endl;
				cout << "withdraw sum: withdraw funds from most recently viewed account" << endl;
				cout << "deposit sum: deposit funds into most recently viewed account" << endl;
				cout << "transfer src dest sum: transfer funds between accounts" << endl;
				cout << "project years: project balance forward in time" << endl;
				cout << "search value: search for transaction of specified value on a recently viewed account" << endl;
				cout << "exit: close this application" << endl;
				cout << "options: view these options again" << endl;
				     
			}
			else if (command.compare("open") == 0)
			{
				try //try will cease the if else blocks if an error is caught in them
				{
					parameters.at(2); //open requires something to be in index 2 at most so if nothing exists at this index then not enough parameters have been given
					string accountAnswer, balanceStringAnswer;
					double balanceAnswer;
					//lines below get the current time, using the chrono:: namespace
					auto timeDone = chrono::system_clock::now();
					time_t transactionTime = chrono::system_clock::to_time_t(timeDone);
					accountAnswer = parameters[1];
					balanceStringAnswer = parameters[2];
				    if (!MainMethods::isNumber(balanceStringAnswer)) throw NotNumeric(balanceStringAnswer); //checks if the opening balance is a number 
					MainMethods::convert(balanceAnswer, balanceStringAnswer); //balanceAnswer will be given a value as it is referenced in the convert method in MainMethods
					if (balanceAnswer < 1000 && accountAnswer == "3") throw InvalidIsa(balanceAnswer); //isa cannot have values less than 1000
					if (accountAnswer == "1")
					{
						Account* a = new Current(balanceAnswer); //new dynamically created Account object that will be assigned to the vector and is of type Current
						allAccounts.push_back(a);
					}
					else if (accountAnswer == "2") //new dynamically created Account object assigned to vector of type savings 
					{
						Account* a = new Savings(balanceAnswer, "savings"); //uses the other constructor in Account
						allAccounts.push_back(a);
					}
					else if (accountAnswer == "3") 
					{
						Account* a = new Savings(balanceAnswer, "isa"); //isa is a variant of the savings class
						allAccounts.push_back(a);
					}
					else
					{
						throw InvalidAccountGiven(accountAnswer); //no valid account given
					}
					cout << "Account created successfully! This is account number: " << allAccounts.size() << endl;
					viewedIndex = allAccounts.size() - 1; //the newest account is considered the most recently viewed account
					Transaction* initialTransaction = new Transaction("Initial Deposit", transactionTime, balanceAnswer); //creates new Transaction object that will be passed into the account object 
					//as a pointer
					allAccounts[(allAccounts.size() - 1)]->addTransaction(initialTransaction);
				}
				catch (InvalidAccountGiven e) //caught if the account given is not 1,2 or 3
				{
					cout << e.getMessage() << endl;
				}
				catch (AccountExistsException e) //exception caught in the current/savings class if a current or isa exists already
				{
					cout << e.accountErrorMessage() << endl;
				}
				catch (InvalidIsa e) //caught if isa balance < 1000
				{
					cout << e.getMessage() << endl;
				}
				catch (NotNumeric e) //caught if opening balance is not a double
				{
					cout << e.getMessage() << endl;
				}
				catch (out_of_range const& exc) //used to catch a vector out of range exception thrown by .at()
				{
					cout << "Invalid number of arguments given to open an account" << endl;
				}
				catch (IncorrectDecimals e) //caught if the double is given more than two decimals
				{
					cout << e.getMessage() << endl;
				}
			}
			else if (command.compare("view") == 0)
			{
				try
				{
					//views all information of a specified account
					parameters.at(1); //to view an account requires at most something to be in index 1 so if it doesn't exist not enough parameters are given
					string stringIndex;
					int index;
					stringIndex = parameters[1];
					if (!MainMethods::isNumber(stringIndex)) throw NotNumeric(stringIndex); 
					MainMethods::convert(index, stringIndex); //convert also works for ints such as index as the function is overloaded
					if (index > allAccounts.size() || index <= 0) throw InvalidIndexException(); //if index exceeds the number of entries in the vector or is less or equal than 0 throw error
					viewedIndex = index - 1; //the current viewed index gets replaced with the newly viewed index
					allAccounts[viewedIndex]->viewTransactions();
				}
				catch (InvalidIndexException) //caught if the index given doesn't exist in allAccounts vector
				{
					cout << "Index given does not exist" << endl;
				}
				catch (NotNumeric e)
				{
					cout << e.getMessage() << endl;
				}
				catch (out_of_range const& exc) 
				{
					for (int i = 0; i < allAccounts.size(); i++)
					{
						allAccounts[i]->viewTransactions(); //as there are no paramaters at index 1 then only the command view was entered, which is caught here. The functionality to see all accounts is
						//therefore done here as well
					}
				}
				catch (IncorrectDecimals e) 
				{
					cout << e.getMessage() << endl;
				}
			}
			else if (command.compare("withdraw") == 0)
			{
				try
				{
					//takes money out of the most recently viewed account
					parameters.at(1); //for withdraw and deposit something must at most exist at index 1 so if nothing is there not enough parameters have been given
					string stringAmount;
					double amount;
					auto timeDone = chrono::system_clock::now();
					time_t transactionTime = chrono::system_clock::to_time_t(timeDone);
					stringAmount = parameters[1];
					if (!MainMethods::isNumber(stringAmount)) throw NotNumeric(stringAmount);
					MainMethods::convert(amount, stringAmount);
					if (allAccounts.size() == 0) throw NoAccounts(); //there needs to be one account at least in order for there to be a withdrawal
					allAccounts[viewedIndex]->withdraw(amount);
					cout << "Withdrawal successful" << endl;
					Transaction* accountTransaction = new Transaction("Withdrawal", transactionTime, amount); 
					allAccounts[viewedIndex]->addTransaction(accountTransaction);
					allAccounts[viewedIndex]->viewTransactions();
				}
				catch (ExceedOverDraftException) //thrown in the current class if withdrawal exceeds -500
				{
					cout << "Current account overdraft exceeded" << endl;
				}
				catch (NegativeWithdrawalException) //thrown in the savings class if withdrawal exceeds 0
				{
					cout << "Savings account cannot go below 0" << endl;
				}
				catch (NotNumeric e) 
				{
					cout << e.getMessage() << endl;
				}
				catch (out_of_range const& exc) 
				{
					cout << "Invalid number of arguments given to withdraw from an account" << endl;
				}
				catch (IncorrectDecimals e)
				{
					cout << e.getMessage() << endl;
				}
				catch (NoAccounts) //caught if no accounts exist before command is called
				{
					cout << "No accounts to withdraw from" << endl;
				}
			}
			else if (command.compare("deposit") == 0)
			{
				try
				{
					//gives money into the most recently viewed account
					parameters.at(1);
					string stringAmount;
					double amount;
					auto timeDone = chrono::system_clock::now();
					time_t transactionTime = chrono::system_clock::to_time_t(timeDone);
					stringAmount = parameters[1];
					if (!MainMethods::isNumber(stringAmount)) throw NotNumeric(stringAmount);
					MainMethods::convert(amount, stringAmount);
					if (allAccounts.size() == 0) throw NoAccounts();
					allAccounts[viewedIndex]->deposit(amount);
					cout << "Deposit successful" << endl;
					Transaction* accountTransaction = new Transaction("Deposit", transactionTime, amount);
					allAccounts[viewedIndex]->addTransaction(accountTransaction);
					allAccounts[viewedIndex]->viewTransactions();
				}
				catch (NotNumeric e) 
				{
					cout << e.getMessage() << endl;
				}
				catch (out_of_range const& exc)
				{
					cout << "Invalid number of arguments given to deposit to an account" << endl;
				}
				catch (IncorrectDecimals e)
				{
					cout << e.getMessage() << endl;
				}
				catch (NoAccounts) 
				{
					cout << "No accounts to deposit to" << endl;
				}
			}
			else if (command.compare("transfer") == 0)
			{
				try
				{
					//transfers money between two specified accounts
					parameters.at(3); //something must be at index 3 at most for a transfer so if there is nothing in index 3 there are not enough arguments
					string stringIndexOne, stringIndexTwo, stringAmount;
					int indexOne, indexTwo;
					double amount;
					auto timeDone = chrono::system_clock::now();
					time_t transactionTime = chrono::system_clock::to_time_t(timeDone);
					stringIndexOne = parameters[1];
					if (!MainMethods::isNumber(stringIndexOne)) throw NotNumeric(stringIndexOne);
					MainMethods::convert(indexOne, stringIndexOne);
					if (indexOne > allAccounts.size() || indexOne <= 0) throw InvalidIndexException();
					stringIndexTwo = parameters[2];
					if (!MainMethods::isNumber(stringIndexTwo)) throw NotNumeric(stringIndexTwo);
					MainMethods::convert(indexTwo, stringIndexTwo);
					if (indexTwo > allAccounts.size() || indexTwo <= 0) throw InvalidIndexException();
					if (indexOne == indexTwo) throw SameAccount(); //cannot transfer to the same account
					stringAmount = parameters[3];
					if (!MainMethods::isNumber(stringAmount)) throw NotNumeric(stringAmount);
					MainMethods::convert(amount, stringAmount);
					if (typeid(*allAccounts[indexOne - 1]) == typeid(Current) && (allAccounts[indexOne - 1]->getBalance() - amount < -500)) throw ExceedOverDraftException(); 
					//current accounts have -500 overdraft
					if (typeid(*allAccounts[indexOne - 1]) == typeid(Savings) && (allAccounts[indexOne - 1]->getBalance() - amount < 0)) throw NegativeWithdrawalException(); 
					//savings and isa cannot go below 0
					transfer(allAccounts[indexOne - 1], allAccounts[indexTwo - 1], amount); //friend function called which is seperate to Account as it is not a member
					cout << "Transfer successful" << endl;
					Transaction* accountTransactionOne = new Transaction("Withdrawal for Transfer", transactionTime, amount); //two transaction objects created
					allAccounts[indexOne - 1]->addTransaction(accountTransactionOne); //this one is for the withdrawal of money for transfer on the first account
					Transaction* accountTransactionTwo = new Transaction("Deposit for Transfer", transactionTime, amount);
					allAccounts[indexTwo - 1]->addTransaction(accountTransactionTwo); //this one is for the money deposited in transfer on the second account
					allAccounts[indexOne - 1]->viewTransactions();
					allAccounts[indexTwo - 1]->viewTransactions();
				}
				catch (ExceedOverDraftException)
				{
					cout << "Current account overdraft exceeded" << endl;
				}
				catch (NegativeWithdrawalException)
				{
					cout << "Savings account cannot go below 0" << endl;
				}
				catch (InvalidIndexException)
				{
					cout << "Index given does not exist" << endl;
				}
				catch (SameAccount) //caught if the indicies of the account are the same
				{
					cout << "Account Indexes given are the same" << endl;
				}
				catch (NotNumeric e) 
				{
					cout << e.getMessage() << endl;
				}
				catch (out_of_range const& exc)
				{
					cout << "Invalid number of arguments given to transfer between accounts" << endl;
				}
				catch (IncorrectDecimals e)
				{
					cout << e.getMessage() << endl;
				}
			}
			else if (command.compare("project") == 0)
			{
				try
				{
					//projects interest on a recently viewed savings account
					parameters.at(1); //something must at most be in index 1 of the vector so if there is nothing in the vector not enough arguments have been given
					string stringYears;
					if (allAccounts.size() == 0) throw NoAccounts();
					if (typeid(*allAccounts[viewedIndex]) == typeid(Current)) throw CurrentProjection(); //cannot have interest on current accounts
					else
					{
						Savings saveAccount = *allAccounts[viewedIndex]; //invoking savings copy constructor
						int years; //interest rates are normally accrued yearly so therefore the number of years should be whole
						stringYears = parameters[1];
						if (!MainMethods::isNumber(stringYears)) throw NotNumeric(stringYears);
						MainMethods::convert(years, stringYears);
						cout.setf(ios::fixed);
						cout.setf(ios::showpoint);
						cout.precision(2);
						cout << "Balance after " << years << " years is \x9c" << saveAccount.computeInterest(years);
						//£ does not exist in MSVC format so we need to use it's 
						//hexidecimal code which is 9c and is accessed with th escape character \x
						//MSVC stands for Microsoft Visual Studio
					}
				}
				catch (CurrentProjection) //caught if the most recently viewed account is of type current
				{
					cout << "Cannot give projection on a current account" << endl;
				}
				catch (NotNumeric e) 
				{
					cout << e.getMessage() << endl;
				}
				catch (out_of_range const& exc)
				{
					cout << "Invalid number of arguments given to project interest on an account" << endl;
				}
				catch (IncorrectDecimals e) 
				{
					cout << e.getMessage() << endl;
				}
				catch (NoAccounts) 
				{
					cout << "No accounts to project interest on" << endl;
				}
			}
			else if (command.compare("search") == 0)
			{
			    try 
			    {
					//searches the most recent account for a transaction of a specific value
					parameters.at(1); //something must at most be in index 1 of the vector so if there is nothing in the vector at index 1 not enough arguments have been given
					string stringValue;
					double valueAnswer;
					int transactionsSize;
					if (allAccounts.size() == 0) throw NoAccounts();
					transactionsSize = allAccounts[viewedIndex]->getHistorySize();
					stringValue = parameters[1];
					if (!MainMethods::isNumber(stringValue)) throw NotNumeric(stringValue);
					MainMethods::convert(valueAnswer, stringValue);
					cout << allAccounts[viewedIndex]->search(valueAnswer, 0, transactionsSize - 1); //0 is the starting point of the overall vector, transactionSize - 1 is the end point
					//the method returns a transaction object which is displayed in the cout statement via overloaded << operator
			    }
				catch (TransactionNotFound e) //thrown in the account method if the transaction value doesn't exist
				{
					cout << e.getMessage() << endl;
				}
				catch (NotNumeric e) 
				{
					cout << e.getMessage() << endl;
				}
				catch (out_of_range const& exc)
				{
					cout << "Invalid number of arguments given to search transactions on an account" << endl;
				}
				catch (IncorrectDecimals e)
				{
					cout << e.getMessage() << endl;
				}
				catch (NoAccounts) 
				{
					cout << "No accounts to search" << endl;
				}
			}
			delete[] cstr; //as cstr is a dynamic array then it should be deleted to prevent a memory leak
		}
		
	std::cout << "Press any key to quit...";
	std::getchar(); //gets the character inputted
	for (int i = 0; i < allAccounts.size(); i++) 
	{
		delete allAccounts[i]; //deletes all dynamically created accounts. This deletes the object so that the memory is freed however the pointers will remain in the vector
	}
	allAccounts.clear(); //removes all the pointers so that the size returns to 0.
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
