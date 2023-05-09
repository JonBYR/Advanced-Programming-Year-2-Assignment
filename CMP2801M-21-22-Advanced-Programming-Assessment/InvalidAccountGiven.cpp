#include "InvalidAccountGiven.h"
InvalidAccountGiven::InvalidAccountGiven(string a) 
{
	invalidAccount = a;
}
string InvalidAccountGiven::getMessage() 
{
	return "The account " + invalidAccount + " does not exist. Please give a valid number as shown in the instructions";
}