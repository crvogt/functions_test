#include <iostream>
#include <vector>
#include <cstdio>
//#include "predictor_node_lib.h"
using namespace std;

int main(int argc, char **argv){
	
	//Preparing data to pass to vectors
	double initLat[5] = {55.862282, 55.862278, 55.862278, 55.866093, 55.86235};
	double initLon[5] = {-3.1532116, -3.1532202, -3.1530969, -3.1532218, -3.153194};
	//Don't necessarily need to specify number of elements if initializing
	double initAlt[] = {154.77, 154.36, 179.98, 223.97, 140.54};

	vector <double> gpsLatValsVec;
	vector <double> gpsLonValsVec;
	vector <double> altVec;
	
	/*Vector Test*/
	for(int i = 0; i < 5; i++){
		gpsLatValsVec.push_back(initLat[i]);
		printf("\n GPS Lat vector val %d is %lf", i, gpsLatValsVec[i]);
	}

	cout << endl;


	
	/*
	Get GPS values,
	if vector = 0 elements
	create a new instance of the class
	*/
	
	/*
	Get GPS values
	if vector ~= 0
	Check GPS values vs current vals
	if no similar GPS vals
	create new instance of class and store in vector
	*/
	//Store its address in a vector

	//As the plane flies, build the configuration space

	//Send measurements to appropriate config cube.

	return 0;
}