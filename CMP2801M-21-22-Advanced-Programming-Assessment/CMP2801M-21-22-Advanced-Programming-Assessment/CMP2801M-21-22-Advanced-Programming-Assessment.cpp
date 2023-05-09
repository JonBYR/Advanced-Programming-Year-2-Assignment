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
#include "MainMethods.h" //contains methods only used by main
#include "ExceedOverDraftException.h"
#include "NegativeWithdrawalException.h"
#include "InvalidAccountGiven.h"
#include "InvalidIsa.h"
#include "AccountExistsException.h"
#include "InvalidIndexException.h"
#include "TransactionNotFound.h"
#include "SameAccount.h"
#include "NotNumeric.h"
#include "IncorrectDouble.h"
#include "CurrentProjection.h" //all exceptions included
using namespace std;
int main()
{
	vector <string> parameters;
	string userCommand;
	vector<Account*> allAccounts; //vector for all account pointers which are dynamically created in the open command
	// you may also want to store a collection of opened accounts here

	std::cout << "~~~ Welcome to LincBank! ~~~" << std::endl;
	cout << "As our customer you can do the following: open an account with 'open' (1 for current, 2 for savings, 3 for ISA, view an account (or all accounts by typing 0) with 'view', "
		 << "withdraw money from an account with 'withdraw', deposit money to an account with 'deposit', transfer money between accounts with 'transfer',"
		 << " project the interest on a savings account with 'project' or search for transactions in an account's history with 'search'. 'exit' will exit the program. 'options' gives this list again" << endl;
	while (userCommand != "exit")
	{
		parameters.clear(); // clear ready for next command
		cout << endl << ">>> ";
		getline(cin, userCommand);
		transform(userCommand.begin(), userCommand.end(), userCommand.begin(), ::tolower); //transfroms the string into lower case
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
			if (userCommand.empty()) throw NotNumeric(); //checks if the string userCommand the user inputs to is empty.
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
			if (command.compare("options") == 0) //command.compare("options" == 0) userCommand == "options"
			{
				cout << "As our customer you can do the following: open an account with 'open' (1 for current, 2 for savings, 3 for ISA, view an account (or all accounts by typing 0) with 'view', "
					<< "withdraw money from an account with 'withdraw', deposit money to an account with 'deposit', transfer money between accounts with 'transfer',"
					<< " project the interest on a savings account with 'project' or search for transactions in an account's history with 'search'. 'exit' will exit the program." 
					<< "'options' gives this list again" << endl;
				     //long lines of code can be broken up like so
			}
			else if (command.compare("open") == 0)
			{
				try // try code blocks will cease the command if an exception is thrown and caught inside each block.
				{
					parameters.at(2); //open requires something to be in index 2 at most so if nothing exists at this index then not enough parameters have been given
					string accountAnswer, balanceStringAnswer; //to store the parameters
					double balanceAnswer;
					auto timeDone = chrono::system_clock::now(); //uses <chrono> and <ctime>
					time_t transactionTime = chrono::system_clock::to_time_t(timeDone); //gets the current time. Chrono is a seperate namespace to std so we need to include chrono::
					accountAnswer = parameters[1];
					balanceStringAnswer = parameters[2];
					transform(accountAnswer.begin(), accountAnswer.end(), accountAnswer.begin(), ::tolower); //converts string to lower case using <algorithm>
				    if (!MainMethods::isNumber(balanceStringAnswer)) throw NotNumeric(balanceStringAnswer); //balanceAnswer cannot be a string or any other non-digit data type, so we use isNumber
					//to check if it is numeric or not 
					MainMethods::convert(balanceAnswer, balanceStringAnswer); //balanceAnswer will be given a value as it is referenced in the convert method in MainMethods
					//if the string is found to be numeric
					//static methods are called by the class name followed by ::
					if (balanceAnswer < 1000 && accountAnswer == "3") throw InvalidIsa(balanceAnswer); //isa cannot have values less than 1000
					
					if (accountAnswer == "1")
					{
						Account* a = new Current(balanceAnswer); //new dynamically created Account object that will be assigned to the vector and is of type Current
						allAccounts.push_back(a);
					}
					else if (accountAnswer == "2") //new dynamically created Account object assigned to vector of type savings or isa, which is a type of savings account
					{
						Account* a = new Savings(balanceAnswer, "savings"); //uses the other constructor in Account
						allAccounts.push_back(a);
					}
					else if (accountAnswer == "3") 
					{
						Account* a = new Savings(balanceAnswer, "isa"); //uses the other constructor in Account
						allAccounts.push_back(a);
					}
					else
					{
						throw InvalidAccountGiven(accountAnswer); //no valid account given
					}
					cout << "Account created successfully! This is account number: " << allAccounts.size() << endl;
					Transaction* initialTransaction = new Transaction("Initial Deposit", transactionTime, balanceAnswer); //creates new Transaction object that will be passed into the account object 
					//as a pointer
					allAccounts[(allAccounts.size() - 1)]->addTransaction(initialTransaction); //-> used rather than . due to allAccounts[index - 1] being a pointer
				}
				catch (InvalidAccountGiven e)
				{
					cout << e.getMessage() << endl;
				}
				catch (AccountExistsException e) //exception caught in the current/savings class
				{
					cout << e.accountErrorMessage() << endl;
				}
				catch (InvalidIsa e) 
				{
					cout << e.getMessage() << endl;
				}
				catch (NotNumeric e)
				{
					cout << e.getMessage() << endl;
				}
				catch (out_of_range const& exc) //used to catch a vector out of range exception
				{
					cout << "Invalid number of arguments given to open an account" << endl;
				}
				catch (IncorrectDouble e) 
				{
					cout << e.getMessage();
				}
			}
			else if (command.compare("view") == 0)
			{
				try
				{
					parameters.at(1); //to view an account requires at most something to be in index 1 so if it doesn't exist not enough parameters are given
					string stringIndex;
					int index;
					stringIndex = parameters[1];
					if (!MainMethods::isNumber(stringIndex)) throw NotNumeric(stringIndex); //method called for any variables that need to be numeric
					MainMethods::convert(index, stringIndex); //convert also works for ints such as index as the function is overloaded
					if (index > allAccounts.size() || index < 0) throw InvalidIndexException(); //if index exceeds the number of entries in the vector or is less than 0 
					//(as 0 is an option for view) throw an error
					if (index == 0)
					{
						for (int i = 0; i < allAccounts.size(); i++)
						{
							cout << allAccounts[i]->toString() << endl; //will call the child toString method
							cout << *allAccounts[i] << endl; //goes through all account pointers and displays the values using the << operator overload and the dereferencing operator *
							allAccounts[i]->viewTransactions();
						}
					}
					else
					{
						cout << allAccounts[index - 1]->toString() << endl; //index - 1 is used as vectors start from 0 and not 1
						cout << *allAccounts[index - 1] << endl; //goes through the specific account pointer, again using the << operator overload
						allAccounts[index - 1]->viewTransactions();
					}
				}
				catch (InvalidIndexException)
				{
					cout << "Index given does not exist";
				}
				catch (NotNumeric e)
				{
					cout << e.getMessage() << endl;;
				}
				catch (out_of_range const& exc) 
				{
					cout << "Invalid number of arguments given to view an account" << endl;
				}
			}
			else if (command.compare("withdraw") == 0)
			{
				try
				{
					parameters.at(2); //for withdraw and deposit something must at most exist at index 2 so if nothing is there not enough parameters have been given
					string stringIndex, stringAmount;
					int index;
					double amount;
					auto timeDone = chrono::system_clock::now();
					time_t transactionTime = chrono::system_clock::to_time_t(timeDone);
					stringIndex = parameters[1];
					if (!MainMethods::isNumber(stringIndex)) throw NotNumeric(stringIndex);
					MainMethods::convert(index, stringIndex);
					if (index > allAccounts.size() || index <= 0) throw InvalidIndexException(); //0 is not an option for any other command other than view so we include it for the exception
					stringAmount = parameters[2];
					if (!MainMethods::isNumber(stringAmount)) throw NotNumeric(stringAmount);
					MainMethods::convert(amount, stringAmount);
					allAccounts[index - 1]->withdraw(amount); //even though account has no functiionilty for withdraw or deposit, we can call the method as it being a pointer allows us to call it's
					//child methods
					cout << "Withdrawal successful" << endl;
					Transaction* accountTransaction = new Transaction("Withdrawal", transactionTime, amount); 
					allAccounts[index - 1]->addTransaction(accountTransaction); 
				}
				catch (ExceedOverDraftException) //thrown in the current class
				{
					cout << "Current account overdraft exceeded" << endl;
				}
				catch (NegativeWithdrawalException) //thrown in the savings class
				{
					cout << "Savings account cannot go below 0" << endl;
				}
				catch (InvalidIndexException)
				{
					cout << "Index given does not exist" << endl;
				}
				catch (NotNumeric e) 
				{
					cout << e.getMessage() << endl;;
				}
				catch (out_of_range const& exc) 
				{
					cout << "Invalid number of arguments given to withdraw from an account" << endl;
				}
				catch (IncorrectDouble e)
				{
					cout << e.getMessage();
				}
			}
			else if (command.compare("deposit") == 0)
			{
				try
				{
					parameters.at(2);
					string stringIndex, stringAmount;
					int index;
					double amount;
					auto timeDone = chrono::system_clock::now();
					time_t transactionTime = chrono::system_clock::to_time_t(timeDone);
					stringIndex = parameters[1];
					if (!MainMethods::isNumber(stringIndex)) throw NotNumeric(stringIndex);
					MainMethods::convert(index, stringIndex);
					if (index > allAccounts.size() || index <= 0) throw InvalidIndexException();
					stringAmount = parameters[2];
					if (!MainMethods::isNumber(stringAmount)) throw NotNumeric(stringAmount);
					MainMethods::convert(amount, stringAmount);
					allAccounts[index - 1]->deposit(amount);
					cout << "Deposit successful" << endl;
					Transaction* accountTransaction = new Transaction("Deposit", transactionTime, amount);
					allAccounts[index - 1]->addTransaction(accountTransaction);
				}
				catch (InvalidIndexException)
				{
					cout << "Index given does not exist" << endl;
				}
				catch (NotNumeric e) 
				{
					cout << e.getMessage() << endl;
				}
				catch (out_of_range const& exc)
				{
					cout << "Invalid number of arguments given to deposit to an account" << endl;
				}
				catch (IncorrectDouble e)
				{
					cout << e.getMessage();
				}
			}
			else if (command.compare("transfer") == 0)
			{
				try
				{
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
					allAccounts[indexOne - 1]->addTransaction(accountTransactionOne); //this one is for the withdrawal of money for transfer
					Transaction* accountTransactionTwo = new Transaction("Deposit for Transfer", transactionTime, amount);
					allAccounts[indexTwo - 1]->addTransaction(accountTransactionTwo); //this one is for the money deposited in transfer
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
				catch (SameAccount) 
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
				catch (IncorrectDouble e)
				{
					cout << e.getMessage();
				}
			}
			else if (command.compare("project") == 0)
			{
				try
				{
					parameters.at(2); //something must at most be in index 2 of the vector at index 2 so if there is nothing in the vector not enough arguments have been given
					string stringIndex, stringYears;
					int index;
					stringIndex = parameters[1];
					if (!MainMethods::isNumber(stringIndex)) throw NotNumeric(stringIndex);
					MainMethods::convert(index, stringIndex);
					if (index > allAccounts.size() || index <= 0) throw InvalidIndexException();
					if (typeid(*allAccounts[index - 1]) == typeid(Current)) throw CurrentProjection(); //checks that the account is of type current rather than savings, as we do not have interest
					//on current accounts
					else
					{
						Savings saveAccount = *allAccounts[index - 1]; //*allAccounts will refer to the data of the object rather than the memory address, meaning the data in the object is passed to 
						//the copy constructor. A savings object is created so that the project method can be called since it doesn't exist on the parent object
						int years; //interest rates are normally accrued yearly so therefore the number of years should be whole
						stringYears = parameters[2];
						if (!MainMethods::isNumber(stringYears)) throw NotNumeric(stringYears);
						MainMethods::convert(years, stringYears);
						cout.setf(ios::fixed);
						cout.setf(ios::showpoint);
						cout.precision(2);
						cout << "Balance after " << years << " years is \x9c" << saveAccount.computeInterest(years); //£ does not exist in MSVC format so we need to use it's 
						//hexidecimal code which is 9c and is accessed with th escape character \x
						//Note: MSVC stands for Microsoft Visual Studio
					}
				}
				catch (InvalidIndexException)
				{
					cout << "Index given does not exist";
				}
				catch (CurrentProjection)
				{
					cout << "Cannot give projection on a current account";
				}
				catch (NotNumeric e) 
				{
					cout << e.getMessage() << endl;
				}
				catch (out_of_range const& exc)
				{
					cout << "Invalid number of arguments given to project interest on an account" << endl;
				}
			}
			else if (command.compare("search") == 0)
			{
			    try 
			    {
					parameters.at(2); //something must at most be in index 2 of the vector so if there is nothing in the vector at index 2 not enough arguments have been given
					string stringIndex, stringValue;
					int index;
					double valueAnswer;
					int transactionsSize;
					stringIndex = parameters[1];
					if (!MainMethods::isNumber(stringIndex)) throw NotNumeric(stringIndex);
					MainMethods::convert(index, stringIndex);
					if (index > allAccounts.size() || index <= 0) throw InvalidIndexException();
					transactionsSize = allAccounts[index - 1]->getHistorySize(); //needed for search
					stringValue = parameters[2];
					if (!MainMethods::isNumber(stringValue)) throw NotNumeric(stringValue);
					MainMethods::convert(valueAnswer, stringValue);
					cout << allAccounts[index - 1]->search(valueAnswer, 0, transactionsSize - 1); //0 is the starting point of the overall vector, transactionSize - 1 is the end point
				
			    }
				catch (InvalidIndexException) 
				{
					cout << "Index given does not exist" << endl;
				}
				catch (TransactionNotFound e) //thrown in the account method
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
				catch (IncorrectDouble e)
				{
					cout << e.getMessage();
				}
			}

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
