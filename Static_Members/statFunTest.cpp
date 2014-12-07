//This program demonstrates a static member function
#include <iostream>
#include <iomanip>
#include "Budget2StaticFunctions.h"
using namespace std;

int main(int argc, char **argv){
	int count; //loop counter
	double mainOfficeRequest; //main office
							//budget request
	const int NUM_DIVISIONS = 4;

	//Get the main office's budget request
	//Note that no instances of the Budget class have been defined
	cout << "Enter the main office's budget request: ";
	cin >> mainOfficeRequest;
	Budget::mainOffice(mainOfficeRequest);

	//An array of Budget objects
	Budget divisions[NUM_DIVISIONS];

	//Get the budget of requests for each division
	for(count=0; count<NUM_DIVISIONS; count++){
		double budgetAmount;
		cout << "Enter the budget request for division ";
		cout << (count + 1) << ": ";
		cin >> budgetAmount;
		divisions[count].addBudget(budgetAmount);
	}

	//Display the budget requests and teh corporate budget
	cout << fixed << showpoint << setprecision(2);
	cout << "\nHere are the division budget requests:\n";
	for(count=0; count<NUM_DIVISIONS; count++){
		cout << "\tDivision " << (count + 1) << "\t$ ";
		cout << divisions[count].getDivisionBudget() << endl;
	}
	cout << "\tTotal Budget Requests:\t$ ";
	cout << divisions[0].getCorpBudget() << endl;

	return 0;	
}