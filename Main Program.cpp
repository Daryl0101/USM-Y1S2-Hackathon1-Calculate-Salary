/*
This is the main program to store employees' data 
from a text file, add and update the employees count 
and their data, then calculate their total
pay based on the hours worked by each of them.
*/
#include <iostream>
#include <fstream>
#include <string>
#include "Salary.h"
using namespace std;

void store(ifstream&, Salary[], int); //Store the data from file into array object
void print_all(Salary[], int); //Display all data in the array object
void add(Salary[], int&, const int); //Add new employees
void add_backend(Salary [], int&, int); //Add the data of new employees
void update(Salary[], int&); //Update the current data of all employees

int main()
{
	const int SIZE = 100;
	string file_name;
	ifstream file;
	cout<<"Please enter the name of file to open: ";
	getline(cin,file_name);
	file.open(file_name); //Open file
	
	//Testing file validity
	while(file.fail()==true)
	{
		file.clear();
		cout<<"File does not exist! Please try again!\n";
		cout<<"Please enter the name of file to open: ";
		getline(cin,file_name);
		file.open(file_name);
	}
	file.clear();
	
	//Testing the number of rows
	int num_of_employee = 0;
	string test;
	while(file)
	{
		getline(file,test,'\n');
		num_of_employee++;
	}
	num_of_employee-=1;
	file.clear();
	file.seekg(0, file.beg);
	
	Salary S[SIZE];
	store(file, S, num_of_employee);
	file.close();
	
	//User Menu
	system("cls");
	char ans;
	do
	{
		cout << "..........................................MENU.........................................\n"
		<< "What would you like to do? \n"
		<< "A : Add or update\n"
		<< "B : Display Workers' Details\n"
		<< "C : Exit menu\n";
		cout<<"Choice(A/B/C): ";
		cin >> ans;
		while(ans!='A' && ans!='a' && ans!='B' && ans!='b' && ans!='C' && ans!='c') //Test validity of user input
		{
			system("cls");
			cout<<"Please enter a valid input!\n";
			cout << "..........................................MENU.........................................\n"
			<< "What would you like to do? \n"
			<< "A : Add or update\n"
			<< "B : Display Workers' Details\n"
			<< "C : Exit menu\n";
			cout<<"Choice(A/B/C): ";
			cin>>ans;
			system("cls");
		}
		//Choices chosen by user
		switch(ans)
		{
			case 'A':
			case 'a': 
						system("cls");
						add(S, num_of_employee, SIZE);
						update(S, num_of_employee);
						system("pause");
						system("cls");
			
			case 'B' :
			case 'b' : 
						system("cls");
						char choice;
						//Ask if the user wants to print out the details of employees
						cout<<"Do you want to display the details of employees?(Y/N): ";
						cin>>choice;
						system("cls");
						while(choice!='Y'&&choice!='y'&&choice!='N'&&choice!='n') //Input validation
						{
							cout<<"Please enter a valid input!\n";
							cout<<"Do you want to display the details of employees?(Y/N): ";
							cin>>choice;
							system("cls");
						}
						
						if(choice=='Y'||choice=='y')
						{
							print_all(S, num_of_employee);
							system("pause");
							system("cls");
							break;
						}
						else
						break;
				
			case 'C' :
			case 'c' : 
						system("cls");
						cout<<"You have exitted the program!\n";
						system("pause");
						return 0;
		}
	}while(ans!='C'||ans!='c');
	
	return 0;
}

//Store data from file into array object
void store(ifstream& file, Salary S[], int num_of_employee)
{
	string n;
	double* h = new double [num_of_employee];
	
	for(int i=0; i<num_of_employee;i++)
	{
		getline(file, n, ';');
		if(i!=0)
		n.erase(n.begin()); //Erase the newline character at the start of string
		S[i].setName_H(n); //Set the name of employee
		for(int j=0;j<5;j++)
		{
			file>>h[j];
		}
		S[i].setHours_H(h); //Set the hours worked by employee
		S[i].calc_Salary(); //Calculate and set the salary of each employee
	}
	
	delete [] h;
}

//Calculate the total salary of each employee for the whole week
double calcTotal(Salary S[], int i)
	{
		S[i].total_salary=0;
		for(int d=0;d<S[i].DAYS;d++)
		{
			S[i].total_salary+=S[i].salary[d];
		}
		return S[i].total_salary;
	}

//Display the data of all employees
void print_all(Salary S[], int num_of_employee)
{	
	cout<<"TOTAL NUMBER OF EMPLOYEES: "<<num_of_employee<<endl;
	cout<<"Hourly Pay Rate: RM"<<getRate(S)<<endl;
	double total;
	double* h = new double [num_of_employee];
	double* sal = new double [num_of_employee];
	cout<<"-------------------------------------------\nName\tDay\t\tHours\tSalary\n-------------------------------------------\n";
	for(int i=0; i<num_of_employee;i++)
	{
		if(i!=0)
		cout<<endl;
		cout<<S[i].getName_H()<<"\t";
		S[i].getHours_H(h); //Retrieving data of the number of hours worked for each day for current employee into temporary array
		S[i].getSalary(sal);
		for(int d=0;d<5;d++)
		{
			if(d==0)
			{
				cout<<S[i].getDW(d)<<"\t\t"<<h[d]<<"\t"<<sal[d]<<"\n";
			}
			else if(d==1 || d==4)
			{
				cout<<"\t"<<S[i].getDW(d)<<"\t\t"<<h[d]<<"\t"<<sal[d]<<endl;
			}
			else if(d==2 || d==3)
			{
				cout<<"\t"<<S[i].getDW(d)<<"\t"<<h[d]<<"\t"<<sal[d]<<endl;
			}
		}
		cout<<"-------------------------------------------\n";
		cout<<"Total\t\t\t\t"<<calcTotal(S,i)<<endl;
		cout<<"-------------------------------------------\n";
	}
	delete [] h;
	delete [] sal;
}

//Add option for user to add new employees into the array object
void add(Salary S[], int& num_of_employee, const int SIZE)
{
	int add_employee = 0, minimum, maximum,original=num_of_employee;
	char choice;
	
	//Ask if the user wants to add employees
	cout<<"Do you want to add employees?(Y/N): ";
	cin>>choice;
	system("cls");
	while(choice!='Y'&&choice!='y'&&choice!='N'&&choice!='n') //Input validation
	{
		cout<<"Please enter a valid input!\n";
		cout<<"Do you want to add employees?(Y/N): ";
		cin>>choice;
		system("cls");
	}
	
	//Check if array object is full
	if(num_of_employee==SIZE)
	{
		cout<<"Insufficient space to add!\n";
		return;
	}
	else
	{
		minimum=1;
		maximum=SIZE-num_of_employee;
	}
	
	if(choice=='N'||choice=='n')
	return;
	else
	{
		char choice2;
		do
		{
			//Number of employees to add
			cout<<"How many employees do you want to add?("<<minimum<<"~"<<maximum<<"): ";
			cin>>add_employee;
			system("cls");
			while(add_employee<minimum||add_employee>maximum) //Input validation
			{
				cout<<"Please enter a valid number!\n";
				cout<<"How many employees do you want to add?("<<minimum<<"~"<<maximum<<"): ";
				cin>>add_employee;
				system("cls");
			}
			
			cout<<"Your choice is ("<< add_employee << ").\nDo you want to change?\nYou will not be able to change the number after you confirmed your choice.(Y/N): ";
			cin>>choice2;
			while(choice2!='Y'&&choice2!='y'&&choice2!='N'&&choice2!='n') //Input validation
			{
				cout<<"Please enter a valid input!\n";
				cout<<"Your choice is ("<< add_employee << ").\nDo you want to change?\nYou will not be able to change the number after you confirmed your choice.(Y/N): ";
				cin>>choice2;
				system("cls");
			}
			if(choice2=='Y'||choice2=='y')
			add_employee=0;
		}while(choice2=='Y'||choice2=='y');
		num_of_employee += add_employee;
		add_backend(S, num_of_employee, original);
		system("cls");
	}
}

//Add the data of new employees
void add_backend(Salary S[], int& num_of_employee, int original)
{
	string n;
	double* h = new double [5];
	system("cls");
	for(int i=original; i<num_of_employee; i++)
	{
		cout<<"........Employee "<< i << "........\n";
		cout<<"Name: ";
		cin.ignore();
		getline(cin, n);
		S[i].setName_H(n);
		for(int j=0; j<5;j++)
		{
			cout<<S[i].getDW(j)<<": ";
			cin>>h[j];
			while(h[j]<0||h[j]>24)
			{
				cout<<"Please enter a valid number(0~24): ";
				cin>>h[j];
			}
			cout<<endl;
		}
		S[i].setHours_H(h);
		S[i].calc_Salary();
		system("pause");
		system("cls");
	}
	delete [] h;
}

//Update the data of all existing employees
void update(Salary S[], int& num_of_employee)
{
	char choice;
	
	//Ask if the user wants to add employees
	cout<<"Do you want to update the employees' data'?(Y/N): ";
	cin>>choice;
	system("cls");
	while(choice!='Y'&&choice!='y'&&choice!='N'&&choice!='n') //Input validation
	{
		cout<<"Please enter a valid input!\n";
		cout<<"Do you want to update the employees' data'?(Y/N): ";
		cin>>choice;
		system("cls");
	}
	
	if(choice=='N'||choice=='n')
	return;
	else
	{
		char choice5;
		int serial_employee;
		do
		{
			print_all(S, num_of_employee);
			char choice2;
			do
			{
				//Number of employees to add
				cout<<"Who's data do you want to update?("<<1<<"~"<<num_of_employee<<"): ";
				cin>>serial_employee;
				system("cls");
				while(serial_employee<1||serial_employee>num_of_employee) //Input validation
				{
					cout<<"Please enter a valid number!\n";
					cout<<"Who's data do you want to update?("<<1<<"~"<<num_of_employee<<"): ";
					cin>>serial_employee;
					system("cls");
				}
				
				//Check if user is sure on his/ her input
				cout<<"Your choice is ("<< serial_employee << ").\nDo you want to change?(Y/N): ";
				cin>>choice2;
				system("cls");
				while(choice2!='Y'&&choice2!='y'&&choice2!='N'&&choice2!='n') //Input validation
				{
					cout<<"Please enter a valid input!\n";
					cout<<"Your choice is ("<< serial_employee << ").\nDo you want to change?(Y/N): ";
					cin>>choice2;
					system("cls");
				}
			}while(choice2=='Y'||choice2=='y');
			//User menu to choose which detail of the employee to be changed
			char choice4;
			do
			{
				char choice3;
				cout<<"What data do you wish to change?\n";
				cout<<".....................Data.....................\n";
				cout<<"A.\tName ("<<S[serial_employee-1].getName_H()<<")\n"
					<<"B.\tMonday Working Hours ("<<S[serial_employee-1].getOneHour_H(0)<<")\n"
					<<"C.\tTuesday Working Hours ("<<S[serial_employee-1].getOneHour_H(1)<<")\n"
					<<"D.\tWednesday Working Hours ("<<S[serial_employee-1].getOneHour_H(2)<<")\n"
					<<"E.\tThursday Working Hours ("<<S[serial_employee-1].getOneHour_H(3)<<")\n"
					<<"F.\tFriday Working Hours ("<<S[serial_employee-1].getOneHour_H(4)<<")\n"
					<<"..............................................\n"
					<<"Choice(A/B/C/D/E/F): ";
				cin>>choice3;
				system("cls");
				while(choice3!='A'&&choice3!='a'&&choice3!='B'&&choice3!='b'&&choice3!='C'&&choice3!='c'&&choice3!='D'&&choice3!='d'&&choice3!='E'&&choice3!='e'&&choice3!='F'&&choice3!='f') //Input validation
				{
					cout<<"Please enter a valid choice!\n";
					cout<<"What data do you wish to change?\n";
					cout<<".....................Data.....................\n";
					cout<<"A.\tName ("<<S[serial_employee-1].getName_H()<<")\n"
					<<"B.\tMonday Working Hours ("<<S[serial_employee-1].getOneHour_H(0)<<")\n"
					<<"C.\tTuesday Working Hours ("<<S[serial_employee-1].getOneHour_H(1)<<")\n"
					<<"D.\tWednesday Working Hours ("<<S[serial_employee-1].getOneHour_H(2)<<")\n"
					<<"E.\tThursday Working Hours ("<<S[serial_employee-1].getOneHour_H(3)<<")\n"
					<<"F.\tFriday Working Hours ("<<S[serial_employee-1].getOneHour_H(4)<<")\n"
						<<"..............................................\n"
						<<"Choice(A/B/C/D/E/F): ";
					cin>>choice3;
					system("cls");
				}
				
				//Choices of user to change which data
				int hr;
				string na;
				switch(choice3)
				{
					case'A':
					case'a':
						cout<<"Enter the name for this employee: ";
						S[serial_employee-1].setName_H(na);
						break;
					case'B':
					case'b':
						cout<<"Enter the working hours(0~24): ";
						cin>>hr;
						while(hr<0||hr>24)
						{
							cout<<"Please enter a valid number!\n";
							cout<<"Enter the working hours(0~24): ";
							cin>>hr;
						}
						S[serial_employee-1].setOneHour_H(hr,0);
						S[serial_employee-1].calc_Salary();
						break;
					case'C':
					case'c':
						cout<<"Enter the working hours(0~24): ";
						cin>>hr;
						while(hr<0||hr>24)
						{
							cout<<"Please enter a valid number!\n";
							cout<<"Enter the working hours(0~24): ";
							cin>>hr;
						}
						S[serial_employee-1].setOneHour_H(hr,1);
						S[serial_employee-1].calc_Salary();
						break;
					case'D':
					case'd':
						cout<<"Enter the working hours(0~24): ";
						cin>>hr;
						while(hr<0||hr>24)
						{
							cout<<"Please enter a valid number!\n";
							cout<<"Enter the working hours(0~24): ";
							cin>>hr;
						}
						S[serial_employee-1].setOneHour_H(hr,2);
						S[serial_employee-1].calc_Salary();
						break;
					case'E':
					case'e':
					cout<<"Enter the working hours(0~24): ";
						cin>>hr;
						while(hr<0||hr>24)
						{
							cout<<"Please enter a valid number!\n";
							cout<<"Enter the working hours(0~24): ";
							cin>>hr;
						}
						S[serial_employee-1].setOneHour_H(hr,3);
						S[serial_employee-1].calc_Salary();
						break;
					case'F':
					case'f':
						cout<<"Enter the working hours(0~24): ";
						cin>>hr;
						while(hr<0||hr>24)
						{
							cout<<"Please enter a valid number!\n";
							cout<<"Enter the working hours(0~24): ";
							cin>>hr;
						}
						S[serial_employee-1].setOneHour_H(hr,4);
						S[serial_employee-1].calc_Salary();
						break;
				}
				system("cls");
				//Asks user if he/she still wants to upate the data of current employee
				print_all(S,num_of_employee);
				cout<<"Do you want to continue changing the data of Employee " << serial_employee<<"?(Y/N): ";
				cin>>choice4;
				system("cls");
				while(choice4!='Y'&&choice4!='y'&&choice4!='N'&&choice4!='n') //Input validation
				{
					cout<<"Please enter a valid input!\n";
					cout<<"Do you want to continue changing the data of Employee " << serial_employee<<"?(Y/N): ";
					cin>>choice4;
					system("cls");
				}
			}while(choice4=='Y'||choice4=='y');
			
			//Asks user if he/she wants to change the data of other employees
			cout<<"Do you want to change other data?(Y/N): ";
			cin>>choice5;
			system("cls");
			while(choice5!='Y'&&choice5!='y'&&choice5!='N'&&choice5!='n') //Input validation
			{
				cout<<"Please enter a valid input!\n";
				cout<<"Do you want to change other data?(Y/N): ";
				cin>>choice5;
				system("cls");
			}
			
		}while(choice5=='Y'||choice5=='y');
	}
}

double getRate(Salary S[])
{
	return S[0].RATE;
}
