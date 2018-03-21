#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main(int argc, char **argv){

	string myStringI = "-2";
	string myStringF = "12345";
	float myStringInt;
	float myStringFloat;
	float myNumba, myNumba1;

	// int stringLength = myStringF.len();

	string::size_type stringLength = myStringF.size();
	myStringInt = stoi(myStringF);
	cout << "\nmyStringInt: " << myStringInt << endl;
	myStringFloat = myStringInt / (pow(10,stringLength));
	myNumba1 = stof(myStringI);
	cout << "\nmyNumba1: " << myNumba1 << endl;
	if(myNumba1 <= 0)
		myNumba = myNumba1 - myStringFloat;
	else	
		myNumba = myNumba1 + myStringFloat;


	// cout << "\nstring length: " << stringLength << std::endl;
	cout << "\nstring float: " << myStringFloat << endl;
	cout << "myNumba: " << myNumba << endl;

	cout << "myNumba*2: " << myNumba*2 << endl;

	return 1;
}
