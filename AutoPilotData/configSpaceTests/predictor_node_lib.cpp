#include <iostream>
#include <vector>
using namespace std;

/******************private*****************/
//We'd put functions here that might act within other functions (or methods)
double ValueBlock::degreesToMeters(double deg1, double deg2){

	return distanceInMeters;
}

double ValueBlock::metersToDegrees(double dimension, double startDeg){

	return finishDeg;
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
	//Fairly subjective at the moment
	latDim = 0.00003;
	longDim = 0.00003;
	//altitude dimension in meters
	altDim = 3;
}

double ValueBlock::setValues(double lat, double lon, double alt){
	setLength(lat);
	setWidth(lon);
	setDepth(alt);
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
bool checkCube(std::vector<ValueBlock> stdBlock){
	//Bringing in a block (or location) and checking it against other blocks...

}

void writeCubesToFile(std::vector<ValueBlock> blockOut){
	//Want this file to write each block to an output file with all of its data
}

