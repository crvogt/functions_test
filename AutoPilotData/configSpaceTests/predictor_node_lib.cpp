#include <iostream>
#include <vector>
#include "predictor_node_lib.h"
using namespace std;

/******************private*****************/
//We'd put functions here that might act within other functions (or methods)
/*double ValueBlock::degreesToMeters(double deg1, double deg2){

	return distanceInMeters;
}

double ValueBlock::metersToDegrees(double dimension, double startDeg){

	return finishDeg;
}
*/
void ValueBlock::setLength(double latS){
	latitudeS = latS;
	latitudeF = latitudeS + latDim;
}

void ValueBlock::setWidth(double lonS){
	longitudeS = lonS;
	longitudeF = longitudeS + longDim;
}

void ValueBlock::setDepth(double altS){
	altitudeS = altS;
	altitudeF = altS + altDim;
}

//Destructor
ValueBlock::~ValueBlock(){

}

/******************public******************/
//constructor
//Should set initial dimensions for cubes
ValueBlock::ValueBlock(){
	//Want to set cube dimensions here
	//values in decimals of lat and long
	//Fairly subjective at the moment
	latDim = 0.00003;
	longDim = 0.00003;
	//altitude dimension in meters
	altDim = 3;
}

double ValueBlock::setValues(GPSVals gpsStruct){
	setLength(gpsStruct.latitudeInd);
	setWidth(gpsStruct.longitudeInd);
	setDepth(gpsStruct.altitudeInd);
}

double ValueBlock::getLength(void) const{
	return latDim;
}

double ValueBlock::getWidth(void) const{
	return longDim;
}

double ValueBlock::getDepth(void) const{
	//This should suffice (in meters)
	return altDim;
}



/***********Outside of class*************/

void checkCube(GPSVals valStruct){
	//For dimensions
	float latDimension, longDimension, altDimension;

	//Vector iterator
	vector<float>::iterator it;

	//Bringing in a block (or location) and checking it against other blocks...
	ValueBlock *cubePointer;

	//create vector
	vector <ValueBlock *> cubeVector;

	if(cubeVector.empty()){
		//create new block
		cubePointer = new ValueBlock;
		cubePointer->setValues(valStruct);
		cubeVector.push_back(cubePointer);
		//Get the dimensions we'll need from the class
		latDimension = cubePointer->getLength();
		longDimension = cubePointer->getWidth();
		altDimension = cubePointer->getDepth();
	}
	else{
		//check values of existing cubes
		for(it = cubeVector.begin)
			if(valStruct.latitudeInd >= valublockLatStart && valStruct.latitudeInd <= valublockLatEnd){
				//add wind values to this block and increase measurement number
			}
			else{
				//construct new block (or series of blocks depending on how far away we are)
				//Dimensions were pulled from the class earlier
				if()
					//make sure altitudes are constant, block wise
					//Just make sure they all line up
			}
	}
}
/*
void writeCubesToFile(std::vector<ValueBlock> blockOut){
	//Want this file to write each block to an output file with all of its data
}
*/
