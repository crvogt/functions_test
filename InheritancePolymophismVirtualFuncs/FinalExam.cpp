#include <FinalExam.h>
/*
set function
The parameters are the number of questions and
the number of questions missed
*/

void FinalExam::set(int questions, int missed){
	//To hold the numeric score
	double numericScore;

	//Set number of questions and num missed
	numQuestions = questions;
	numMissed = missed;

	//Calculate the points for each q
	pointsEach = 100.0 / numQuestions;

	//Calculate the  numeric score for this exam
	numericScore = 100.0 - (missed * pointsEach);

	//call the inherited setScore function to set
	//The numeric score
	setScore(numericScore);
}