#pragma once
class InterestEarning //interface that only contains a single pure virtual function
{
public:
	virtual float computeInterest(int years) = 0;
};

