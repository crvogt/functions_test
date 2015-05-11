#include <iostream>
#include <vector>
#include <math.h>

#include "predictor_node_lib.h"
#include "csv_parser.h"
using namespace std;

/******************private*****************/
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
void checkCube(vector<autopilotData> &flightVector, extremes *values,
			   vector<ValueBlock *> &cubeVector){
	
	/*
	Current issue, make sure to check back about negative values
	*/

	//Debug counters
	int counterLat = 0, counterLon = 0;	

	//startValsStruct holds the values to be passed to create the new block
	//GPSValStruct is simply incoming GPS values.
	GPSVals startValsStruct;
		
	//Simple holders	
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

	//Define in main?
	//cube vector
	//vector<ValueBlock *> cubeVector;

	//Vector iterator
	//vector<ValueBlock *>::iterator it;
	
	//look through GPS values, get extremes, create box (2d, one layer)
	//while values less than greater value,
	tempHoldLong = values->smallLong;
	tempHoldLat = values->smallLat;
	tempHoldAlt = values->smallAlt;
	startValsStruct.latitudeInd = values->smallLat;
	startValsStruct.longitudeInd = values->smallLong;
	startValsStruct.altitudeInd = (values->largeAlt / 2);

	/*
	This while loop simply takes the "extremes values"
	and creates a grid. Once this is done, the values are siphoned
	into their respective grid location
	*/
	while(tempHoldLong <= values->largeLong){
		while(tempHoldLat <= values->largeLat){
			cubePointer = new ValueBlock;
			cubePointer->adjustAltDim(values->largeAlt - values->smallAlt);
			cubePointer->setGPSValues(&startValsStruct);
			cubeVector.push_back(cubePointer);
			tempHoldLat += cubePointer->returnLatDim();
			startValsStruct.latitudeInd = tempHoldLat;
			//Debug check
			cout << "\nNumber of iterations (counterLat): " << (counterLat + 1);
			counterLat++;			
		}
		//This should start the previous while loop up again
		tempHoldLat = values->smallLat;
		counterLat = 0;

		//Continuing first while loop and updating startValStruct
		tempHoldLong += cubePointer->returnLongDim();
		startValsStruct.longitudeInd = tempHoldLong;
		cout << "\n\nNumber of iterations (counterLon): " << (counterLon + 1)
			 << endl;
		counterLon++;
	}

	cout << endl;
}