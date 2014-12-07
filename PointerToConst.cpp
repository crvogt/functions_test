//Pointers to const and arrays and
//addresses and such.

#include <iostream>
#include <iomanip>
using namespace std;

void displayPayRates(const double *, int);

int main(int argc, char **argv){
	//
	const int SIZE = 6;
	const double payRates[SIZE] = {18.55, 17.45, 12.85, 14.97, 10.35, 18.89};

	displayPayRates(payRates, SIZE);

	return 0;
}

void displayPayRates(const double *rates, int size){
	//set numeric output formatting
	int count;

	cout << setprecision(2) << fixed << showpoint;

	//Display all the pay rates
	for(count=0; count<size; count++){
		cout << "Pay rate for employee " << (count + 1);
		cout << " is $" << *(rates + count) << endl;
	}

	//Print the address now
	cout << "\nRespective addresses:\n";
	for (count=0; count<size; count++){
		cout << (rates + count) << endl;
		//cout << rates++ << endl;
	}

	cout << endl << endl;

	for(count=0; count<size; count++){
		cout << rates++ <<endl;
	}
}