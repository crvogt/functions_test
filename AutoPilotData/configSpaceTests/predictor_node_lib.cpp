#include <iostream>
using namespace std;

/******************private*****************/
//We'd put functions here that might act within other functions (or methods)

/******************public******************/
//constructor/destructor goes here
double ValueBlock::getLength(void) const{
	return length;
}

double ValueBlock::getWidth(void) const{
	return width;
}

double ValueBlock::getDepth(void) const{
	return depth
}

void ValueBlock::setLength(double lat){
	length = lat;
}

void ValueBlock::setWidth(double lon){
	width = lon;
}

void ValueBlock::setDepth(double alt){
	depth = alt;
}

bool isCorrectCube(std::vector<ValueBlock> stdBlock){


}