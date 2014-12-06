#include <iostream>
#include <iomanip>
using namespace std;

int main(){
	const int NUM_COINS = 5;
	double coins[NUM_COINS] = {0.05, 0.1, 0.25, 0.5, 1.0};
	double *doublePtr; //pointer to a double
	int count;

	//Assign the address of the coins array
	//to doublePtr
	doublePtr = coins;

	//Display the contents of the coins array,
	//use subscripts with the pointer
	cout << "Here are the values in the coins array:\n";
	for(count=0; count<NUM_COINS; count++)
		cout << doublePtr[count] << " ";

	//Display the contents of the array again, but 
	//this time use pointer notation with the array name
	cout << "And again:\n";
	for(count=0; count<NUM_COINS; count++)
		cout << *(coins + count) << " ";
	cout << endl;
	
	return 0;	
}

