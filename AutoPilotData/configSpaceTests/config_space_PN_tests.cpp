#include <iostream>
#include <vector>
#include <cstdio>
#include <math.h>

#include "csv_parser.h"
#include "predictor_node_lib.h"

using namespace std;

int main(int argc, char **argv){

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
	checkCube(flightVec, &values, cubeVector);	

	//Can now work with cubeVector as it's being returned

	return 0;
}

