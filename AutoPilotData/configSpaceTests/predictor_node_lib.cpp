#include <iostream>
#include <vector>
#include "predictor_node_lib.h"
#include <math.h>
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
void ValueBlock::setAltDim(double altitude){
	altDim = altitude;
}

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

void ValueBlock::adjustAltDim(double altitude){
	setAltDim(altitude);
}
/*
double returnSumOfDistances(void) const{
	double sum;

	sum = latitudeS + latitudeF + longitudeS + longitudeF + altitudeS + altitudeF;

	return sum;
}
*/
 




/***********Outside of class*************/
void checkCube(GPSVals *GPSValStruct, windVals *windValStruct)){
	//startValsStruct holds the values to be passed to create the new block
	//GPSValStruct is simply incoming GPS values.
	GPSVals startValsStruct;
	
	//To hold sum of values from incoming struct
	double GPSValSum;
	
	//holds difference between closest block and current GPS values.
	double difference;
	double preDifference;
	
	//extremes
	double smallLat;
	double largeLat;
	double smallLong
	double largeLong;
	double smallAlt;
	double largeAlt;
	double tempHoldLong;
	double tempHoldLat;
	double tempHoldAlt;

	//Holds the it value for the closest value
	int countHigh;
	int roundingInt;
	
	//Hold difference between locations
	double locDifference;

	//cube pointer
	ValueBlock *cubePointer;

	//GPSValSum = GPSValStruct->latitudeInd + GPSValStruct->longitudeInd + GPSValStruct->altitudeInd;

	//cube vector
	vector <ValueBlock *> cubeVector;

	//Vector iterator
	vector<ValueBlock *>::iterator it;
	
	//add first GPS values


	//look through GPS values, get extremes, create box (2d, one layer)
	//while values less than greater value,
	tempHoldLong = smallLong;
	tempHoldLat = smallLat;
	tempHoldAlt = largeAlt - smallAlt;
	startValsStruct.latitudeInd = smallLat;
	startValsStruct.longitudeInd = smallLong;
	startValsStruct.altitudeInd = smallAlt + (largeAlt - smallAlt) / 2;

	while(tempHoldLong <= largeLong){
		while(tempHoldLat <= largeLat){
			cubePointer = new ValueBlock;
			cubePointer->adjustAltDim(tempHoldAlt);
			cubePointer->setGPSValues(startValStruct);
			cubeVector.pushback(cubePointer);
			tempHoldLat += cubePointer->returnLatDim();
		}
		tempHoldLong += cubePointer->returnLongDim();
	}
	/*
	//Control structure
	if(cubeVector.empty()){
		cubePointer = new ValueBlock;
		cubePointer->setGPSValues(GPSValStruct);
	}
	else{
		//check values of existing cubes
		for(it = cubeVector.begin()){
			//Check values to see if struct lies in existing block	
			if(GPSValStruct->latitudeInd >= cubeVector[it]->returnStartLength() && 
				GPSValStruct->latitudeInd <= cubeVector[it]->returnEndLength()){
				if(GPSValStruct->longitudeInd >= cubeVector[it]->returnStartWidth() && 
					GPSValStruct->longitudeInd <= cubeVector[it].returnEndWidth()){
					if(GPSValStruct->altitudeInd >= cubeVector[it].returnStartDepth() && 
						GPSValStruct->altitudeInd >= cubeVector[it].returnEndDepth()){
						//add wind values to this block and increase measurement number
						//cubeVector[it]->sendWindValues(windValStruct);
						//now return to make sure loop doesn't continue
						return; //hopefully doesn't exit ros
					}
				}
			}
			//Also check for closest block to values while we're in this loop
			difference = cubeVector[it]->returnSumOfDistances - GPSValSum;
			if(difference < preDifference){
				countHigh = it;
				preDifference = difference;
			}		
		}
		//Now we have the value of the closest block in countHigh
		locDifference = GPSValStruct->altitudeInd - cubeVector[countHigh]->returnStartDepth;
		//startValsStruct->altitudeInd = ;
		locDifference = GPSValStruct->longitudeInd - cubeVector[countHigh]->returnStartWidth;
		//startValsStruct->longitudeInd = ;
		locDifference = GPSValStruct->latitudeInd - cubeVector[countHigh]->returnStartLength;

		//Fill in blocks?					
	}

*/

	

//End of block	
}


/*
void writeCubesToFile(std::vector<ValueBlock> blockOut){
	//Want this file to write each block to an output file with all of its data
}
*/




















class test{

};



































































