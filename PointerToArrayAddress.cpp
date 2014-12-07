/************************************************
This program uses two different notations
when dealing with a pointer variable that
is accepting an array address as an argument
************************************************/

#include <iostream>
#include <iomanip>
using namespace std;

void getSales(double *, int);
double totalSales(double *, int);

int main(){
	const int QTRS = 4;
	double sales[QTRS];

	//Get the sales data
	getSales(sales, QTRS);

	//Set the numeric output formatting
	cout << fixed << showpoint << setprecision(2);

	//Display the total sales for the year
	cout << "The total sales for the year are $";
	cout << totalSales(sales, QTRS) << endl;

	return 0;
}

void getSales(double *arr, int size){
	for(int count=0; count<size; count++){
		cout << "Enter the sales figure for quarter ";
		cout << (count + 1) << ": ";
		cin >> arr[count];
	}
}

double totalSales(double *arr, int size){
	double sum = 0.0;

	for(int count=0; count<size; count++){
		sum += *arr;
		arr++;
		cout << "\nThis could be the array address: " << arr;
		cout << endl;
	}

	return sum;
}