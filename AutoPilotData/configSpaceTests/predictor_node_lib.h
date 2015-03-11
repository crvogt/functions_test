#ifndef __PREDICTOR_NODE_LIB_H
#define __PREDICTOR_NODE_LIB_H
#include <vector>

class ValueBlock{
private:
	//Actaul dimensions of boxes, values assigned in constructor
	float latDim, longDim, altDim;
	//These values will define the values around the boxes
	//Within the configuration space
	//Latitude values
	double latitudeS, latitudeF;
	//Longitude values
	double longitudeS, longitudeF;
	//Altitude values
	double altitudeS, altitudeF;
	//Need a way to aggregate all of the measurements taken within a block
	//ie, store values in a vector (a struct?)
	struct windComponents{
		float x;
		float y;
		float z;
		float magnitude;
	}windVector;
	std::vector<float> windVectorAgg; 

	//Want to automatically create the cube
	void setLength(double);
	void setWidth(double);
	void setDepth(double);

	//Check ASTE 280 MATLAB code
	double degreesToMeters(double, double); 

public:
	//Constructor
	ValueBlock();
	//Destructor
	~ValueBlock();
	//This is where a vector with all the values would
	//be helpful, that is, wind speed vectors per cube
	//Here being as part of this class
	//Or do you want each class to be an instance within
	//the vector?
	//Return the values
	double getLength(void) const;
	double getWidth(void) const;
	double getDepth(void) const;
};

//Need a function to check the contents of each class (does a measurement
//fall within a specific cube or does a new one need to be created)
//But, each object will be stored in an instance of a vector

bool checkCube(std::vector<ValueBlock>);

void writeCubesToFile(std::vector<ValueBlock>);

/*************
class GPOverConfig{
private:
public:
};

class currentClassifier{
private:
public:
};

#endif
