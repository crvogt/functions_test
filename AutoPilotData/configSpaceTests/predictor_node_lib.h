#ifndef __PREDICTOR_NODE_LIB_H
#define __PREDICTOR_NODE_LIB_H
#include <vector>

class ValueBlock{
private:
	//These values will define the values around the boxes
	//Within the configuration space
	//Latitude value
	double length;
	//Longitude value
	double width;
	//Altitude value
	double depth;
	//Need a way to aggregate all of the measurements taken within a block
	//ie, store values in a vector
	std::vector<float> windVectorAgg; 

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

	void setLength(double);
	void setWidth(double);
	void setDepth(double);

};

//Need a function to check the contents of each class (does a measurement
//fall within a specific cube or does a new one need to be created)
//But, each object will be stored in an instance of a vector

bool isCorrectCube(std::vector<ValueBlock>);
#endif
