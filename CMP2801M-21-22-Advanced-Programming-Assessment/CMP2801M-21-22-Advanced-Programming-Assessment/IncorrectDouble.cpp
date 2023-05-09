#include "IncorrectDouble.h"
IncorrectDouble::IncorrectDouble(string m) 
{
	errorAmount = m;
}
string IncorrectDouble::getMessage() 
{
	return +"The amount \x9c" + errorAmount + " must be at most 2 decimals";
}