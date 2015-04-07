#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char **argv){
	
	char userVal;
	char charArray[] = "RoslinFlight0.txt";	

	for(int i = 0; i < 17; i++)
		cout << charArray[i];

	cout << "\nEnter a new value for flight number: ";
	cin >> userVal;	
	charArray[12] = userVal;
	string fileString(charArray);

	//fstream dataObject(fileString);
	//dataObject << userVal;
	
	cout << endl << endl;
	cout << "Modified string: ";
	cout << fileString << endl << endl;

	return 0;
}


