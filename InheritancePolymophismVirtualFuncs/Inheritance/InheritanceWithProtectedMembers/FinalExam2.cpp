#include "FinalExam2.h"
/*
set function
The parameters are the number of questions and
the number of questions missed
*/

void FinalExam2::set(int questions, int missed){
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

/*
Definition of adjustScore.  If score is within
0.5 points of the next whole point, it rounds
the score up and recalculates the letter grade
*/

void FinalExam2::adjustScore(){
	double fraction = score - static_cast<int>(score);

	if(fraction > 0.5){
		//Adjust the score var in the GradedActivity
		//class
		score += (1.0 - fraction);
	}
}




