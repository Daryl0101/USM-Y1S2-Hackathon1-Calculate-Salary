/*
This is the header file of the derived class which holds the salary of each employee. 
*/
#ifndef SALARY_H
#define SALARY_H
#include <iostream>
#include <string>
#include "Hours.h"
using namespace std;

//Class Salary
class Salary:public Hours//Derived from class "Hours"
{
	private:
		const double RATE = 20; //rate of pay for an hour
		const int DAYS = 5; //Total working days in a week
		const string DW[5]={"Monday", "Tuesday", "Wednesday","Thursday","Friday"}; //Days
		double salary[5]; //Salary for each day
		double total_salary; //Total salary for a week
	public:
		Salary()//Constructor
		{
			for(int i=0;i<DAYS;i++) //Initialise all values in the array to 0
			{
				salary[i]=0;
			}
		}
		~Salary()//Destructor
		{
			for(int i=0;i<DAYS;i++) //Initialise all values in the array to 0
			{
				salary[i]=0;
			}
		}
		//Mutator
		void calc_Salary(); //Calculate and set the values of all salaries
		//Accessor
		void getSalary(double[])const; //Get all the salary of an employee
		string getDW(int); //Get the days
		friend double calcTotal(Salary[],int); //Calculate the total salaries for the whole week
		friend double getRate(Salary[]); //Get the rate of hourly pay of the employees
};

void Salary::calc_Salary()
{
	double h[DAYS];
	Hours::getHours_H(h);
	for(int i=0;i<DAYS;i++)
	{
		salary[i]=h[i]*RATE;
	}
}

void Salary::getSalary(double s[])const
{
	for(int i=0;i<DAYS;i++)
	{
		s[i]=salary[i];
	}
}

string Salary::getDW(int i)
{
	return DW[i];
}
#endif
