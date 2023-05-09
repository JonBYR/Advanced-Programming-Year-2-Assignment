#include "TransactionNotFound.h"
TransactionNotFound::TransactionNotFound(double v) 
{
	errorValue = v;
}
string TransactionNotFound::getMessage() 
{
	char buffer[20]; //creates a CString
	snprintf(buffer, 20, "%.2f", errorValue); //formats the CString so that it only goes to a maximum of 2 decimal places
	string stringMessage(buffer); //converts the CString to a regular string
	return "Transaction with value of \x9c" + stringMessage + " does not exist";
}