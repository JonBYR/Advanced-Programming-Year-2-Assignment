#include "NotNumeric.h"
NotNumeric::NotNumeric() 
{

}
NotNumeric::NotNumeric(string m) 
{
	message = m;
}
string NotNumeric::getMessage() 
{
	return message + " is not a numeric value/is a negative value";
}