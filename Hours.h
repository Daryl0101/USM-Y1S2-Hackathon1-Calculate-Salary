/*
This is the header file for the class which uses composition which holds the total hours worked by an employee.
*/
#ifndef HOURS_H
#define HOURS_H
#include <iostream>
#include <string>
#include "Name.h"
using namespace std;

//class Hours
class Hours
{
	private:
		const int DAYS = 5; //Total working days in a week
		double hours[5]; //Array to hold working hours of an employee
		Name N;
	public:
		Hours() //Constructor
		{
			for(int i=0;i<DAYS;i++) //Initialise all values in the array to 0
			{
				hours[i]=0;
			}
		}
		~Hours() //Destructor
		{
			for(int i=0;i<DAYS;i++) //Initialise all values in the array to 0
			{
				hours[i]=0;
			}
		}
		//Mutator
		void setName_H(string); //Set name of employee
		void setHours_H(double[]); //Set working hours of employee for whole week
		void setOneHour_H(double, int); //set working hours for employee for one day
		
		//Accessor
		string getName_H()const; //Get name of employee
		void getHours_H(double[])const; //Get working hours of employee for whole week
		double getOneHour_H(int);//Get working hours for employee for one day
};

void Hours::setName_H(string n)
{
	N.setName(n);
}

void Hours::setHours_H(double h[])
{
	for(int i=0; i<DAYS; i++)
	{
		hours[i]=h[i];
	}
}

void Hours::setOneHour_H(double h, int i)
{
	hours[i]=h;
}

string Hours::getName_H()const
{
	return N.getName();
}

void Hours::getHours_H(double h[])const
{
	for(int i=0; i<DAYS;i++)
	{
		h[i]=hours[i];
	}
}

double Hours::getOneHour_H(int i)
{
	return hours[i];
}

#endif
