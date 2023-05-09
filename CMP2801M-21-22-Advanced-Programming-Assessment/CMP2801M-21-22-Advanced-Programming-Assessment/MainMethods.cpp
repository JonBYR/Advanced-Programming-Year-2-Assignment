#include "MainMethods.h"
bool MainMethods::isNumber(string numericString) //method checks that the string is a numeric string
{
	for (int i = 0; i < numericString.length(); i++)
	{
		if (isdigit(numericString[i]) == false) return false;
		return true;
	}
}
void MainMethods::convert(int& intValue, string numericString) //call by reference makes the change on the variable that is passed as the reference, in this case the int
{
	intValue = stoi(numericString); //converts string to an int
}
void MainMethods::convert(double& doubleValue, string numericString) throw (IncorrectDouble) //as we are overloading functions convert can refer to either an int or a double reference
{
	int decimalPosition = numericString.find('.'); //finds the decimal point
	string decimalPortion = numericString.substr(decimalPosition + 1); //splits the string into a substring containing all the numbers after the decimal
	if ((decimalPortion.length() <= 2) || numericString.find('.') == string::npos) doubleValue = stod(numericString); //converts string to a double if the decimals entered are 2 or less
	//string::npos is used to state that the character '.' isn't found
	else throw IncorrectDouble(numericString); //if the numbers are 3 or more then it's an invalid double and the exception is thrown
	
}