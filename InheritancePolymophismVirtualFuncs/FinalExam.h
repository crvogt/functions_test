#ifndef FINALEXAM_H
#define FINALEXAM_H
#include "GradedActivity1.h"

class FinalExam : public GradedActivity1{
private:
	int numQuestions;	//Number of questions
	double pointsEach;	//Points for each q
	int numMissed;		//Number of qs missed
public:
	//Default Constructor
	FinalExam(){
		numQuestions = 0;
		pointsEach = 0;
		numMissed = 0;
	}
	
	//constructor
	FinalExam(int questions, int missed){
		set(questions, missed);
	}
	
	//Mutator function
	void set(int, int); //Defined in FinalExam.cpp
	
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