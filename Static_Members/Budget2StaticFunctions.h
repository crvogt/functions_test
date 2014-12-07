/*
Static member functions allow you to
modify the class's static member variables 
any instances of the class are defined
in memory. This gives you the ability
to create very specialized setup routines
for class objects.
*/
#ifndef BUDGET2STATICFUNCTIONS_H
#define BUDGET2STATICFUNCTIONS_H

//Budget class declaration
class Budget{
private:
	//static member variable
	static double corpBudget;
	//instance member variable
	double divisionBudget;

public:
	Budget(){
		divisionBudget = 0;
	}

	void addBudget(double b){
		divisionBudget += b;
		corpBudget += b;
	}

	double getDivisionBudget() const{
		return divisionBudget;
	}

	double getCorpBudget() const{
		return corpBudget;
	}

	//Static member function
	static void mainOffice(double); 
};

double Budget::corpBudget = 0;

void Budget::mainOffice(double mOffice){
	corpBudget += mOffice;
}

#endif