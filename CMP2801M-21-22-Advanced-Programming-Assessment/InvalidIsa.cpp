#include "InvalidIsa.h"
InvalidIsa::InvalidIsa(double a) 
{
	amount = a;
}
string InvalidIsa::getMessage() 
{
	char buffer[20]; 
	snprintf(buffer, 20, "%.2f", amount); 
	string stringMessage(buffer); 
	return "\x9c" + stringMessage + " is too low for account of type ISA";
}