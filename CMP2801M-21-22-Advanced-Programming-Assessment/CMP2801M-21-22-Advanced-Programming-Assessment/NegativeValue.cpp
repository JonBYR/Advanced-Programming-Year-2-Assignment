#include "NegativeValue.h"
NegativeValue::NegativeValue(string m) 
{
	message = m;
}
string NegativeValue::getMessage() {
	if (message == "Years" || message == "Opening Balance") return message + " cannot be a negative amount"; //these can have 0
	else return message + " cannot be a negative amount or 0"; //anything else cannot be 0
}