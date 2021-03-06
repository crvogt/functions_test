#include <iostream>
#include <vector>
#include <cstdio>
#include <math.h>

#include "csv_parser.h"
#include "predictor_node_lib.h"
//#include "gaussian_process.h"

int programRoute(void);

using namespace std;

int main(int argc, char **argv){
	int choice = 0;

	choice = programRoute();

	//Call a struct that holds the data of interest
	//Defined in csv_parser.h
	extremes values;

	//Define the vector
	//Autopilot data is a struct defined in csv_parser
	vector<autopilotData> flightVec;

	//Valueblock vector object
	vector<ValueBlock *> cubeVector;
	
	//Parses files of interest, data goes into a vector
	parseFile(flightVec);
	
	//Returns the highest and lowest values to create
	//cube grid
	returnExtremes(flightVec, &values);

	//Function to create grid
	checkCube(&values, cubeVector);	

	//Can now work with cubeVector as it's being returned
	sortValues(flightVec, cubeVector);

	//Test to print compass and mag
	cubeVectorPrint(cubeVector);

	printToMatlabReadable(cubeVector);

	//Pretty print of 3D matrix
	//prettyPrint(cubeVector);

	//create own series of matrices
	//myMatrix(int, int, int, cubeVector);

	/*
	A couple of notes on how to approach the gaussian - 
	First interpolate: Empty cells need to be interpolated based on the 
	cells with surrounding data.
	Regression: Once the interpolation has finished, we can, on a cell by
	cell basis, start to predict based off the measurements within that 
	cell. Though, it will be good to look at other methods.. Is there a 
	way by which I can ALSO include data from surrounding cells when getting
	the predicted values, or will it be better not to?
	If we go by individual cells, I think that this will be a better method
	if we're to look at then doing feature detection.
	Pattern Recognition for types of weather: I think a Gaussian mixture
	model will not be a bad way to approach this type of thing (see mathematical
	monk number 16)
	*/
	
	//univarGauss(cubeVector);

	return 0;
}

int programRoute(void){
	//Choose the direction of the program

	int choice = 0;
	
	while(!choice){
		cout << "\n\nFeature recognition?(1)"
			 << "\nField Interpolation and Regression?(2)"
			 << "\nWeather Prediction(3)"
			 << "\nFeature recognition and regression?(4)\n";

		cin >> choice;
		if(!choice){
			cout << "\nMust make a choice at this point\n";
		}
	}

	return choice;
}

