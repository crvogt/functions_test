#ifndef __PREDICTOR_NODE_LIB_H
#define __PREDICTOR_NODE_LIB_H

#include <vector>
#include "csv_parser.h"

//This class defines one cube
class ValueBlock{
private:
	//Actaul dimensions of boxes, values assigned in constructor
	float latDim, longDim, altDim;
	
	//Keep track of number of measurements in block
	int numberOfMeasurements;

	 //Matrix dimensions (typical 0 is starting index value)
	int matX, matY, matZ;
	
	//These values will define the values around the boxes
	//Within the configuration space
	//Latitude values aka length
	double latitudeS, latitudeF;
	//Longitude values aka width
	double longitudeS, longitudeF;
	//Altitude values
	double altitudeS, altitudeF;
	//Let us know if windVectorAgg is empty
	bool isEmpty;
	
	//Need a way to aggregate all of the measurements taken within a block
	struct windComponents{
		float compass;
		float magnitude;
		float pressure;
		double windLatitude;
		double windLongitude;
		double windAltitude;
	};
	
	windComponents averageWCS;
	
	std::vector<windCompGlobal> windVectorAgg; 

	//Want to automatically create the cube
	void setLength(double);
	void setWidth(double);
	void setDepth(double);
	void setAltDim(double);
	void addToWindVec(windCompGlobal);
	void dataManip(void);
	void displayBlockVals(void);
	void setMatrixDims(int, int, int);

public:
	//Constructor
	ValueBlock();
	//Destructor
	~ValueBlock();
	
	//Return the values
	double returnStartLength(void) const;
	double returnEndLength(void) const;
	double returnStartWidth(void) const;
	double returnEndWidth(void) const;
	double returnStartDepth(void) const;
	double returnEndDepth(void) const;
	double returnLatDim(void) const;
	double returnLongDim(void) const;
	double returnAltDim(void) const;
	int returnXDimension(void) const;
	int returnYDimension(void) const;
	int returnZDimension(void) const;
	int returnNumOfMeasure(void) const;
	bool returnIsEmpty(void) const;
	void adjustAltDim(double);
	
	void addToWindDat(windCompGlobal);
	double setGPSValues(struct GPSVals *);
	void dataManipulation(void);
	void displayBlockValues(void);
	void setMatrixDimensions(int, int, int);
};

//GPS struct
struct GPSVals{
	double latitudeInd;
	double longitudeInd;
	double altitudeInd;
};

//Check values against cubes.
void checkCube(extremes *, std::vector<ValueBlock *> &);

void sortValues(std::vector<autopilotData> &, std::vector<ValueBlock *> &);

void cubeVectorPrint(std::vector<ValueBlock *> &);

void prettyPrint(std::vector<ValueBlock *> &);

#endif
