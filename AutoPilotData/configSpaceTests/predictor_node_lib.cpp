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

/*
void ValueBlock::setWindValues(windStruct *windVals){
	windStructComponents.x = windVals->x;
	windStructComponents.y = windVals->y;
	windStructComponents.z = windVals->z;
	windStructComponents.magnitude = windVals->magnitude;
}
*/

//Destructor
ValueBlock::~ValueBlock(){

}

/******************public******************/
//constructor
//Should set initial dimensions for cubes
ValueBlock::ValueBlock(){
	//Want to set cube dimensions here
	//values in decimals of lat and long
	latDim = 0.00003;
	longDim = 0.00003;
	//altitude dimension in meters
	altDim = 3;
}

double ValueBlock::setGPSValues(GPSVals *gpsStruct){
	//Send GPS values to private member that will adjust sizes
	setLength(gpsStruct->latitudeInd);
	setWidth(gpsStruct->longitudeInd);
	setDepth(gpsStruct->altitudeInd);
}

double ValueBlock::returnStartLength(void) const{
	return latitudeS;
}

double ValueBlock::returnEndLength(void) const{
	return latitudeF;
}

double ValueBlock::returnStartWidth(void) const{
	return longitudeS;
}

double ValueBlock::returnEndWidth(void) const{
	return longitudeF;
}

double ValueBlock::returnStartDepth(void) const{
	//This should suffice (in meters)
	return altitudeS;
}

double ValueBlock::returnEndDepth(void) const{
	return altitudeF;
}

double ValueBlock::returnLatDim(void) const{
	return latDim;
}

double ValueBlock::returnLongDim(void) const{
	return longDim;
}

double ValueBlock::returnAltDim(void) const{
	return altDim;
}




/***********Outside of class*************/
void checkCube(GPSVals *GPSValStruct, windVals *windValStruct)){
	GPSVals startValsStruct;

	//For dimensions
	//float latDimension, longDimension, altDimension;
	//latDimension = cubePointer->getLength();
	//longDimension = cubePointer->getWidth();
	//altDimension = cubePointer->getDepth();
	
	//cube pointer
	ValueBlock *cubePointer;

	//cube vector
	vector <ValueBlock *> cubeVector;

	//Vector iterator
	vector<ValueBlock *>::iterator it;
	if(cubeVector.empty()){
		cubePointer = new ValueBlock;
		cubePointer->setGPSValues(GPSValStruct);
	}
	else{
		//check values of existing cubes
		for(it = cubeVector.begin()){
			if(abs(GPSValStruct->latitudeInd) >= abs(cubeVector[it]->returnStartLength()) && 
				abs(GPSValStruct->latitudeInd) <= abs(cubeVector[it]->returnEndLength())){
				if(abs(GPSValStruct->longitudeInd) >= abs(cubeVector[it]->returnStartWidth()) && 
					abs(GPSValStruct->longitudeInd) <= abs(cubeVector[it].returnEndWidth())){
					if(abs(GPSValStruct->altitudeInd) >= abs(cubeVector[it].returnStartDepth()) && 
						abs(GPSValStruct->altitudeInd) >= abs(cubeVector[it].returnEndDepth())){
						//add wind values to this block and increase measurement number
						//cubeVector[it]->sendWindValues(windValStruct);
					}
				}
			}
			else{
				//Create new block
				cubePointer = new ValueBlock;
				//setGPSValues requires a struct of the start locations

			}					
		}
	}

//End of block	
}


/*
void writeCubesToFile(std::vector<ValueBlock> blockOut){
	//Want this file to write each block to an output file with all of its data
}
*/
