#include "MainMethods.h"
bool MainMethods::isNumber(string numericString) //method checks that the string is a numeric string
{
	for (int i = 0; i < numericString.length(); i++)
	{
		if (isdigit(numericString[i]) == false) return false;
		return true;
	}
}
void MainMethods::convert(int& intValue, string numericString) throw (IncorrectDecimals) //call by reference makes the change on the variable that is passed as the reference, in this case the int
{
	if (numericString.find('.') != string::npos) throw IncorrectDecimals(numericString, 0);
	intValue = stoi(numericString); //converts string to an int
}
//this version of convert first looks for the decimal point and then splits it into separate strings past the decimal point
//if after the decimal the number of characters is 2 or less then the whole string is converted to double
//equally if the value has no decimal but still needs to be double then it is converted to double
//otherwise the double is invalid and an exception is thrown
void MainMethods::convert(double& doubleValue, string numericString) throw (IncorrectDecimals) //as we are overloading functions convert can refer to either an int or a double reference
{
	int decimalPosition = numericString.find('.'); 
	string decimalPortion = numericString.substr(decimalPosition + 1); 
	if ((decimalPortion.length() <= 2) || numericString.find('.') == string::npos) doubleValue = stod(numericString);
	else throw IncorrectDecimals(numericString, 2);
	
}