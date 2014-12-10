#ifndef FINALEXAM2_H
#define FINALEXAM2_H
#include "GradedActivity2.h"

class FinalExam2 : public GradedActivity2{
private:
	int numQuestions;	//Number of questions
	double pointsEach;	//Points for each q
	int numMissed;		//Number of qs missed
public:
	//Default Constructor
	FinalExam2(){
		numQuestions = 0;
		pointsEach = 0;
		numMissed = 0;
	}
	
	//constructor
	FinalExam2(int questions, int missed){
		set(questions, missed);
	}
	
	//Mutator functions
	void set(int, int); //Defined in FinalExam.cpp
	void adjustScore(); //Defined in FinalExam.cpp

	//Accessor Functions
	double getNumQuestions()const{
		return numQuestions;
	}

	double getPointsEach() const{
		return pointsEach;
	}

	int getNumMissed() const{
		return numMissed;
	}
};

#endif