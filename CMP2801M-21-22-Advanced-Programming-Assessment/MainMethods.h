#pragma once
#include <string>
#include "IncorrectDecimals.h"
using namespace std;
class MainMethods //class does not need to define a constructor as this purely uses static methods and has no variables to initialise of it's own
{
public:
	static bool isNumber(string numericString);
	static void convert(int& intValue, string numericString) throw (IncorrectDecimals);
	static void convert(double& floatValue, string numericString) throw (IncorrectDecimals); //function overloading
};

