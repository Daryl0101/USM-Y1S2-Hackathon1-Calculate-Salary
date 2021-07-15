/*
This is the header file for the base class which holds the Name of employees.
*/
#ifndef NAME_H
#define NAME_H
#include <iostream>
#include <string>
using namespace std;

//Class Name
class Name
{
	private:
		string name; //Name of employee
	public:
		Name(){} //Constructor
		~Name(){} //Destructor
		//Mutator
		void setName(string); //Set the name of employee
		//Accessor
		string getName()const; //Get the name of employee
};

void Name::setName(string n)
{
	name = n;
}

string Name::getName()const
{
	return name;
}
#endif
