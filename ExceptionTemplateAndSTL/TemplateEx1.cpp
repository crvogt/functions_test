//This program uses a function template
#include <iostream>
using namespace std;

//Template definition for a square function
template <class T>
T square(T number){
	return number * number;
}

int main(int argc, char **argv){
	int userInt;
	double userDouble;

	cout << "Enter an int and floating point val: ";
	cin >> userInt >> userDouble;
	cout << "Here are their squares: ";
	cout << square(userInt) << " and "
		 << square(userDouble) << endl;

	return 0;
}