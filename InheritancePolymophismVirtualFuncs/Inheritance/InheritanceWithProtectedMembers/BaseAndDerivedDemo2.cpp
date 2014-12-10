/*
This program demonstrates a base class
and a derived class 
ie, inheritance
*/
#include <iostream>
#include <iomanip>
#include "FinalExam2.h"
using namespace std;

int main(int argc, char *argv[]){
	//*argv[] for kicks
	//Number of qs on exam
	int questions;
	//Number of qs missed by student
	int missed;

	//Get number of questions on final
	cout << "How many questions on the final? ";
	cin >> questions;

	//Get the number of questions the stdt missed
	cout << "How many questions missed? ";
	cin >> missed;

	//Define a FinalExam object and initialize
	//it with the values entered
	FinalExam2 test(questions, missed);

	//Display the test results
	cout << setprecision(2);
	cout << "\nEach questions counts "
		 << test.getPointsEach()
		 << " points.\n";
	cout << "The exam score is " 
		 << test.getScore() << endl;
	cout << "The exam grade is "
		 << test.getLetterGrade() << endl;

	return 0;
}