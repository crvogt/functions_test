#include "GradedActivity1.h"

char GradedActivity1::getLetterGrade() const{
	char letterGrade; //Hold letter grade

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