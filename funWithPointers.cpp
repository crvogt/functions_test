#include <cstdio>
#include "basicFunctions.h"

void multiplyByTwo(double *passedVal){
	*passedVal*=2;
}

void divideByTwo(double *passedVal){
	*passedVal/=2;
}

int main(int argc, char **argv){

	double *aPointer;
	double myValue, myModifiedValue;

	myValue=5.75;
	aPointer=&myValue;
	*aPointer=7;
	printf("\nCurrent Value: %lf", myValue);

	myModifiedValue=10;
	*aPointer=myModifiedValue;

	printf("\nModified Value: %lf\n", myValue);

	//Modify again in a function
	//Try just passing pointers

	multiplyByTwo(aPointer);

	printf("Value multipled by two after fun: %lf\n", myValue);	

	divideByTwo(aPointer);

	printf("Value divided by two after fun: %lf\n", myValue);

	return 0;
}
/*
void multiplyByTwo(double *passedVal){
	*passedVal*=2; //The value at this address is being
				   //multiplied by two
}

void divideByTwo(double *passedVal){
	*passedVal/=2;	//The value at this address is being
					//divided by two
}
*/