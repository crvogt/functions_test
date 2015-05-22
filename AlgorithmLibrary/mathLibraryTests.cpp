#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define PI 3.14159265

int main(int argc, char **argv){

	double magnitude, angle, xComponent, yComponent;
	string filename = "cppToQuiver3.csv";

	magnitude = 6;
	angle = 190; //In degrees

	xComponent = magnitude * sin(angle * PI / 180);
	yComponent = magnitude * cos(angle * PI / 180);

	cout << "\nX Component: " << xComponent << endl;
	cout << "Y Component: " << yComponent << endl;

	cout << "Writing to file" << endl;

	ofstream dataFileToMATLAB;
	dataFileToMATLAB.open(filename.c_str());
	
	for(int i = 0; i < 5; i++){
		dataFileToMATLAB << xComponent
				 << "," << yComponent
				 << endl;
	}

	dataFileToMATLAB.close();

	return 0;
}
