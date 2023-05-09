#include "Transaction.h"
//the time_t object is passed to the constructor, then it's reference given to a char pointer, before then having the pointer casted to a 
//string to prevent the data being overwritten
Transaction::Transaction(string d, time_t t, double v) 
{
	desc = d;
	timeStamp = t;
	value = v;
	charTime = ctime(&timeStamp);
	displayTime = (string)charTime;
}
string Transaction::toString() 
{
	return "This is a transaction object";
}
string Transaction::getDescription() 
{
	return desc;
}
string Transaction::getDate() 
{
	return displayTime;
}
double Transaction::getValue() 
{
	return value;
}
//overloaded friend << operator that displays each transaction description, value and time stamp when using << on a transaction object
ostream& operator <<(ostream& out, const Transaction& t)
{
	out.setf(ios::fixed);
	out.setf(ios::showpoint);
	out.precision(2);
	out << "Transaction has data: " << t.desc << " \x9c" << t.value << " on " << t.displayTime << endl;
	return out;
}
//comparator function that is used for dereferencing the getValue member on the transaction objects and sorts two transactions by their value in ascending order
bool Transaction::ascending(Transaction* t1, Transaction* t2)
{
	return (t1->getValue() < t2->getValue());
}