/*
Inheritance involves a base class and 
a derived class. The base class is the 
general class and the derived class is the
specialized class.  The derived class is based
on or derived from the base class 
Can think of the base class as the parent
and the derived class as the child.
*/
#ifndef GRADEDACTIVITY2_H
#define GRADEDACTIVITY2_H

//Graded activity class declaration

class GradedActivity2{
protected:
	double score;	//to hold numeric score
public:
	//Default Constructor
	GradedActivity2(){
		score = 0;
	}

	//Constructor
	GradedActivity2(double s){
		score = s;
	}

	//Mutator function
	void setScore(double s){
		score = s;
	}

	//Accessor Function
	double getScore() const{
		return score;
	}

	char getLetterGrade() const;
};

#endif