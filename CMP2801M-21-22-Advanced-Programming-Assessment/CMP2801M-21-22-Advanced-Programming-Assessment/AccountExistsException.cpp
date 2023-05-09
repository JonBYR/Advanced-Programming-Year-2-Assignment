#include "AccountExistsException.h"
AccountExistsException::AccountExistsException(string s) 
{
	accountName = s;
}
string AccountExistsException::accountErrorMessage() 
{
	return "Account of type: " + accountName + " is already is existance";
}