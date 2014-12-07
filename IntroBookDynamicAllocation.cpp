#include <iostream>
#include <iomanip>
using namespace std;

int main(int argc, char **argv){
	double *sales,		//dynamically allocate an array
			total=0.0,	//"accumulator"
			average;	//To hold average sales
	int numDays,		//To hold num days of sales
		count;			//Counter variable

	//Get the number of days of sales
	cout << "How many days of sales ";
	cout << "figures do you wish to process? ";
	cin >> numDays;

	//Dynamically allocate an array large
	//enough to handle that many days of
	//sales amounts
	sales = new double[numDays];

	//Get the sales figures for each day
	cout << "Enter the sales figures below\n";
	for(count=0; count<numDays; count++){
		cout << "Day " << (count + 1) << ": ";
		cin >> sales[count];
	}

	//Calculate the total sales
	for(count=0; count<numDays; count++){
		total += sales[count];
	}

	//Calculate the average sales per day
	average = total / numDays;

	//Display the results
	cout << fixed << showpoint << setprecision(2);
	cout << "\n\nTotal Sales: $" << total << endl;
	cout << "Average Sales: $" << average << endl;

	//Free dynamically allocated memory
	delete[] sales;
	sales = 0;	//makes sales point to null

	return 0;
}