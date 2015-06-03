#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <fstream>

#include "predictor_node_lib.h"
#include "csv_parser.h"
using namespace std;

#define _USE_MATH_DEFINES

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

void ValueBlock::addToWindVec(windCompGlobal componentsStruct){
	windVectorAgg.push_back(componentsStruct);	
}

void ValueBlock::dataManip(void){
	int size = windVectorAgg.size();
	float compassSum = 0, magnitudeSum = 0, pressureSum = 0;
	for(int i = 0; i < size; i++){
		compassSum += windVectorAgg[i].compass;	
		//cout << "\nwind vector agg value " << i << " compass " << windVectorAgg[i].compass;
		magnitudeSum += windVectorAgg[i].magnitude;
		//cout << "\nwind vector agg value " << i << " magnitude " << windVectorAgg[i].magnitude;
		pressureSum += windVectorAgg[i].pressure;
	}
	if(size){
		//cout << "\nwindVectorAgg size " << size;
		averageWCS.compass = compassSum / size;
		//cout << "\ncompassSum " << compassSum; 
		averageWCS.magnitude = magnitudeSum / size;
		//cout << "\nmagnitudeSum " << magnitudeSum;
		averageWCS.pressure = pressureSum / size;
		//cout << "\npressureSum " << pressureSum
		//	 << endl;
		isEmpty = false;
	}
	else
		isEmpty = true;
}

void ValueBlock::displayBlockVals(void){
	if(averageWCS.compass && averageWCS.magnitude){
		//cout << "\nAverage compass heading: " << averageWCS.compass;
		//cout << "\nAverage magnitude: " << averageWCS.magnitude;
		//cout << endl;
	}
}

void ValueBlock::setMatrixDims(int x, int y, int z){
	matX = x;
	matY = y;
	matZ = z;
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
	latDim = 0.0001;
	longDim = 0.0001;
	altDim = 3;
	isEmpty = true;//equal to 1 for true
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

int ValueBlock::returnXDimension(void) const{
	return matX;
}

int ValueBlock::returnYDimension(void) const{
	return matY;
}

int ValueBlock::returnZDimension(void) const{
	return matZ;
}

int ValueBlock::returnNumOfMeasure(void) const{
	return numberOfMeasurements;
}

void ValueBlock::adjustAltDim(double altitude){
	setAltDim(altitude);
}

void ValueBlock::addToWindDat(windCompGlobal componentCarry){
	addToWindVec(componentCarry);
}
 
void ValueBlock::dataManipulation(void){
	dataManip();	
}

void ValueBlock::displayBlockValues(void){
	displayBlockVals();
}

void ValueBlock::setMatrixDimensions(int x, int y, int z){
	setMatrixDims(x, y, z);
}

bool ValueBlock::returnIsEmpty(void) const{
	return isEmpty;
}

double ValueBlock::returnAltMid(void) const{
	return (altitudeF + altitudeS) / 2;
}

double ValueBlock::returnLatMid(void) const{
	return (latitudeF + latitudeS) / 2;
}

double ValueBlock::returnLonMid(void) const{
	return (longitudeF + longitudeS) / 2;
}

float ValueBlock::returnAvgCompass(void) const{
	return averageWCS.compass;
}

float ValueBlock::returnAvgMagnitude(void) const{
	return averageWCS.magnitude;
}


/***********Outside of class*************/

void sortValues(vector<autopilotData> &flightVec, vector<ValueBlock *> &cubeVector){
	//will call addToWindDat
	int sizeFV = flightVec.size();
	int sizeCV = cubeVector.size();
	windCompGlobal componentCarry; 
	int i = 0, j = 0;

	for(i = 0; i < sizeFV; i++){
		for(j = 0; j < sizeCV; j++){
			if(flightVec[i].latitude >= cubeVector[j]->returnStartLength()
				&& flightVec[i].latitude <= cubeVector[j]->returnEndLength()
				&& flightVec[i].longitude >= cubeVector[j]->returnStartWidth()
				&& flightVec[i].longitude <= cubeVector[j]->returnEndWidth()
				&& flightVec[i].altitude >= cubeVector[j]->returnStartDepth()
				&& flightVec[i].altitude <= cubeVector[j]->returnEndDepth()){
				//addToWindDat(componentCarry)
				//Figure out wind components
				componentCarry.compass = flightVec[i].compass;
				//going basic for the moment
				componentCarry.magnitude = flightVec[i].airspeed - flightVec[i].groundspeed;
				
				//Atempt to resolve direction
				if(componentCarry.magnitude < 0){
					componentCarry.magnitude = fabs(componentCarry.magnitude);
				}
				else if(componentCarry.magnitude >= 0){
					if(componentCarry.compass <= 180){
						componentCarry.compass += 180; //to get correct direction
					}
					else if(componentCarry.compass > 180){
						componentCarry.compass -= 180;
					}
				}
				
				componentCarry.windLatitude = flightVec[i].latitude;
				componentCarry.windLongitude = flightVec[i].longitude;
				componentCarry.windAltitude = flightVec[i].altitude;
				componentCarry.pressure = flightVec[i].pressureInATM;

				cubeVector[j]->addToWindDat(componentCarry);
			}
		}
	}

	for(i = 0; i < sizeCV; i++){
		cubeVector[i]->dataManipulation();
	}	
}

/****************************************/
void checkCube(extremes *values, vector<ValueBlock *> &cubeVector){
	
	/*
	Current issue, make sure to check back about negative values
	*/
	//cout << "\n\nIn cube vector\n\n";
	//Debug counters
	int counterLat = 0, counterLon = 0, counterAlt = 0;	

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
	
	//look through GPS values, get extremes, create box (2d, one layer)
	//while values less than greater value,
	tempHoldLong = values->smallLong;
	tempHoldLat = values->smallLat;
	tempHoldAlt = values->smallAlt;
	startValsStruct.latitudeInd = values->smallLat;
	startValsStruct.longitudeInd = values->smallLong;
	startValsStruct.altitudeInd = values->smallAlt;

	/*
	This while loop simply takes the "extremes values"
	and creates a grid. Once this is done, the values are siphoned
	into their respective grid location
	*/
	while(tempHoldAlt <= values->largeAlt){
		while(tempHoldLong <= values->largeLong){
			while(tempHoldLat <= values->largeLat){
				cubePointer = new ValueBlock;
				//cubePointer->adjustAltDim(values->largeAlt - values->smallAlt);
				cubePointer->setGPSValues(&startValsStruct);
				cubeVector.push_back(cubePointer);
				cubePointer->setMatrixDimensions(counterLon, counterLat, counterAlt);
				tempHoldLat += cubePointer->returnLatDim();
				startValsStruct.latitudeInd = tempHoldLat;
				counterLat++;
			}
			tempHoldLong += cubePointer->returnLongDim();
			startValsStruct.longitudeInd = tempHoldLong;
			counterLon++;
			tempHoldLat = values->smallLat;
			counterLat = 0;			
		}
		//This should start the previous while loop up again
		counterLon = 0;
		tempHoldLong = values->smallLong;

		//Continuing first while loop and updating startValStruct
		tempHoldAlt += cubePointer->returnAltDim();
		startValsStruct.altitudeInd = tempHoldAlt;

		counterAlt++;
	}
}

void cubeVectorPrint(vector<ValueBlock *> &cubeVector){
	//cout << "\n\n\nPrinting values for cubeVector..." << endl;
	int emptyCount = 0;
	int size = cubeVector.size();

	for(int i = 0; i < size; i++){
		cubeVector[i]->displayBlockValues();
		if(!cubeVector[i]->returnIsEmpty()){
			emptyCount++;	
		}
	}
	cout << "\nsize: " << size << endl;
	cout << "empty: " << emptyCount << endl;
}

/*****************************************************************/
/*****************************************************************************/

void printToMatlabReadable(vector<ValueBlock *> &cubeVector){
	/*
	Want to write out to a csv file easily read by MATLAB to plot the data
	quiver3(x,y,z,u,v,w)
	u, v, and w are the directional vectors which, when resolved, will be
	scaled automatically with respect to eachother and shown in the finished
	direction (the combination of the three) i j k

	Possible to normalize

	M_PI is pi val
	*/
	int size, i;
	float u = 0, v = 0, w = 0;
	double toRad;
	string filename;
	ofstream matlabQuiverData;
	//float scalingFactor = 0.1;
	double normMag = 0;

	filename = "quiverData.csv";
	matlabQuiverData.open(filename.c_str());

	toRad = M_PI / 180;

	size = cubeVector.size();
	for(i = 0; i < size; i++){
		
		u = cubeVector[i]->returnAvgMagnitude() * sin(toRad * cubeVector[i]->returnAvgCompass());
		v = cubeVector[i]->returnAvgMagnitude() * cos(toRad * cubeVector[i]->returnAvgCompass());

		normMag = sqrt(pow(u,2.0) + pow(v,2) + pow(w,2));

		u /= normMag;
		v /= normMag;

		matlabQuiverData << cubeVector[i]->returnLonMid() << ","
						 << cubeVector[i]->returnLatMid() << ","
						 << cubeVector[i]->returnAltMid() << ","
						 << u << ","
						 << v << ","
						 << w << endl;
	
		u = 0;
		v = 0;
		w = 0;
	}

	matlabQuiverData.close();
	matlabQuiverData.clear();
}

/*
void prettyPrint(vector<ValueBlock *> &cubeVector){
	bool notFound = false;
	int x = 0, y = 0, z = 0;

	cout << "\n\nPrinting a pretty table of all the data, by slice" << endl
		 << endl;

	//Find 0 0 0 value, and so on.
	while(notfound){
		x = cubeVector[i].returnXDimension();
		y = cubeVector[i].returnYDimension();
		z = cubeVector[i].returnZDimension();
		if(x == xCount && y == yCount && z == zCount){
		}
	}
}
*/

/*
void dataPrune(vector<ValueBlock *> &cubeVector){
	int size, n = 0, i, clearCounter = 0, diffCount; //n is number of measurements
	float stdDev = 0, powHold = 0;
	float topMean = 0, bottomMean = 0, cubeComp = 0, valueForLargest = 0;
	double compMean = 0, devSum = 0, bigDiff = 0, bigDiffTemp = 0;
	bool goodFlag = true;

	size = cubeVector.size();

	for(i = 0; i < size; i++){
		if(!(cubeVector[i]->returnIsEmpty()) && cubeVector[i]->returnNumOfMeasure()){
			n++;
			compMean += cubeVector[i]->returnAvgCompass(); 
		}
	}

	//Average compass value
	compMean /= n;

	//Determine std deviation
	for(i = 0; i < size; i++){
		if(!(cubeVector[i]->returnIsEmpty()) && cubeVector[i]->returnNumOfMeasure()){
			powHold = cubeVector[i]->returnAvgCompass() - compMean;
			powHold = pow(powHold, 2);
			devSum += powHold;
		}
	}
	//Finish std dev calc
	stdDev = sqrt(devSum / (n - 1));
	cout << "\n\nMean is: " << compMean << endl;
	cout << "Standard deviation is: " << stdDev << endl;

	//Now filter out value outside of this
	topMean = compMean + stdDev;
	if(topMean > 360){
		topMean -= 360; 
	}
	bottomMean = compMean - stdDev;
	if(bottomMean < 0){
		bottomMean += 360;
	}

	for(i = 0; i < size; i++){
		cubeComp = cubeVector[i]->returnAvgCompass();

		//Find the value farthest from mean.
		bigDiffTemp = fabs(cubeComp - compMean);
		if(bigDiffTemp > bigDiff){
			bigDiff = bigDiffTemp;
			diffCount = i;
			valueForLargest = cubeVector[i]->returnAvgCompass();
			cout << "\nLarge val: " << valueForLargest << endl;
		}

		if(topMean < compMean){
			if(cubeComp >= compMean && cubeComp <= 360){
				goodFlag = true;				
			}
			else if(cubeComp > 360 && cubeComp < topMean){
				goodFlag = true;
			}
		}
		else if(bottomMean > compMean){
			if(cubeComp >= bottomMean && cubeComp <= 360){
				goodFlag = true;
			}
			else if(cubeComp > 360 && cubeComp <= compMean){
				goodFlag = true;
			}
		}
		else if(cubeComp >= bottomMean && cubeComp <= topMean){
			goodFlag = true;
		}
		else{
			goodFlag = false;
		}

		if(!goodFlag){
			//delete data
			deleteCubeData(cubeVector, i);
			clearCounter++;		
		}
	}	
	cout << "\nNumber cleared: " << clearCounter << endl;
	cout << "Biggest difference: " << bigDiffTemp << endl;
	cout << "Value for biggest difference: " << valueForLargest;
	cout << "\nIndex value for biggest difference: " << diffCount << endl;
}
*/