#ifndef CURVEDACTIVITY_H
#define CURVEDACTIVITY_H
#include "GradedActivity1.h"

class CurvedActivity : public GradedActivity1{
protected:
	//Unadjusted score
	double rawScore;
	//Curve percentage
	double percentage;
public:
	//Default Constructor
	CurvedActivity() : GradedActivity1(){
		rawScore = 0;
		percentage = 0;
	}
	//Mutator functions
	void setScore(double s){
		rawScore = s;
		GradedActivity1::setScore(rawScore * percentage);
	}
	void setPercentage(double c){
		percentage = c;
	}
	//Accessor functions
	double getPercentage() const{
		return percentage;
	}
	double getRawScore() const{
		return rawScore;
	}
};

#endif