#ifndef __PREDICTOR_NODE_LIB_H
#define __PREDICTOR_NODE_LIB_H
#include <vector>

//This class defines one cube
class ValueBlock{
private:
	//Actaul dimensions of boxes, values assigned in constructor
	float latDim, longDim, altDim;
	
	//Keep track of number of measurements in block
	float numberOfMeasurements;
	
	//These values will define the values around the boxes
	//Within the configuration space
	//Latitude values
	double latitudeS, latitudeF;
	//Longitude values
	double longitudeS, longitudeF;
	//Altitude values
	double altitudeS, altitudeF;
	
	//Need a way to aggregate all of the measurements taken within a block
	struct windComponents{
		float x;
		float y;
		float z;
		float magnitude;
	}windStructComponents;
	
	//std::vector<windComponents> windVectorAgg; 

	//Want to automatically create the cube
	void setLength(double);
	void setWidth(double);
	void setDepth(double);
	void setAltDim(double);

	//Add wind values
	//void setWindValues(struct windStruct *);

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
	void adjustAltDim(double);
	double returnSumOfDistances(void) const;

	double setGPSValues(struct GPSVals *);
	//double sendWindValues(struct windStruct *);
};

//GPS struct
struct GPSVals{
	double latitudeInd;
	double longitudeInd;
	double altitudeInd;
};

//Wind values
struct windVals{
	float x;
	float y;
	float z;
	float magnitude;
};

//Check values against cubes.
void checkCube(struct GPSVals *);

//void writeCubesToFile(std::vector<ValueBlock>);

/*************
class GPOverConfig{
private:
public:
};

class currentClassifier{
private:
public:
};
*********/
#endif
