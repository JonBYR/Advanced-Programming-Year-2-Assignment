#include "IncorrectDecimals.h"
IncorrectDecimals::IncorrectDecimals(string m, int num) //the int acts as a flag for the getMessage function. It will have a relevant int passed through for the if/else block
{
	errorValue = m;
	numberOfDecimals = num;
}
string IncorrectDecimals::getMessage() 
{
	if (numberOfDecimals == 0) 
	{
		return +"The number " + errorValue + " must be whole"; //if the number was meant to be an int
	}
	else if (numberOfDecimals == 2) 
	{
		return +"The amount \x9c" + errorValue + " must not exceed 2 decimals"; //if the number is a double but over 2 decimals
	}
}