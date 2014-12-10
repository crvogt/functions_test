#ifndef CUBE_H
#define CUBE_H
#include "Rectangle.h"

class Cube : public Rectangle{
private:
	double height;
	double volume;
public:
	//Default Constructor
	Cube() : Rectangle(){
		height = 0;
		volume = 0;
	}
	//Constructor 2
	Cube(double, double, double);

	double getHeight() const{
		return height;
	}

	double getVolume() const{
		return volume;
	}
};

//Cube class constructor 2
Cube::Cube(double w, double len, double h) : Rectangle(w, len){
	height = h;
	volume = getArea() * h;
}

#endif