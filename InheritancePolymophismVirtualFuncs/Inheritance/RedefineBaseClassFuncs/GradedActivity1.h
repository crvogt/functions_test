/*
Inheritance involves a base class and 
a derived class. The base class is the 
general class and the derived class is the
specialized class.  The derived class is based
on or derived from the base class 
Can think of the base class as the parent
and the derived class as the child.
*/
#ifndef GRADEDACTIVITY1_H
#define GRADEDACTIVITY1_H

//Graded activity class declaration

class GradedActivity1{
private:
	double score;	//to hold numeric score
public:
	//Default Constructor
	GradedActivity1(){
		score = 0;
	}

	//Constructor
	GradedActivity1(double s){
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

char GradedActivity1::getLetterGrade() const{
	char letterGrade;

	if(score > 89)
		letterGrade = 'A';
	else if(score > 79)
		letterGrade = 'B';
	else if(score > 69)
		letterGrade = 'C';
	else if(score > 59)
		letterGrade = 'D';
	else
		letterGrade = 'F';

	return letterGrade;
}

#endif