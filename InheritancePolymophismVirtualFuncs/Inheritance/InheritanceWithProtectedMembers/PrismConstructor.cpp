/*
This program demonstrates passing args to a 
base class constructor
*/
#include <iostream>
#include "Cube.h"
using namespace std;

int main(int argc, char **argv){
	double cubeWidth;
	double cubeHeight;
	double cubeLength;

	cout << "Enter dims: " << endl;
	cout << "Width: ";
	cin >> cubeWidth;
	cout << "Height: ";
	cin >> cubeHeight;
	cout << "Length: ";
	cin >> cubeLength;

	//Define a cube object and use the 
	//dims entered by user

	Cube myCube(cubeWidth, cubeLength, cubeHeight);

	//Display cube dims
	cout << "Width: " << myCube.getWidth() << endl;
	cout << "Height: " << myCube.getHeight() << endl;
	cout << "Length: " << myCube.getLength() << endl;
	cout << "Base area: " << myCube.getArea() << endl;
	cout << "Volume: " << myCube.getVolume() << endl;

	return 0;
}