#pragma once
#include <string>
using namespace std;
class NotNumeric
{
public:
	NotNumeric(); //overloaded constructors as the if the string is null then a custom message is given in main
	NotNumeric(string m);
	string getMessage(); //other constructor gives a string to be used in the getMessage class
private:
	string message;
};

