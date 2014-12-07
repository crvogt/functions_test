/*****************************************
Accept an array and its size as arguments
Dynamically allocate a new array that is
the same size as the argument array
Copy the elements of the argument array to
the new array
Return a pointer to the new array
*****************************************/

#include <iostream>
using namespace std;

//Function prototype
int *duplicateArray(const int *, int);
void displayArray(const int[], int);

int main(int argc, char **argv){
	//Define constants for the array sizes
	const int SIZE1 = 5, SIZE2 = 7, SIZE3 = 10;

	//Define three arrays of different sizes
	int array1[SIZE1] = {100,200,300,400,500};
	int array2[SIZE2] = {10,20,30,40,50,60,70};
	int array3[SIZE3] = {1,2,3,4,5,6,7,8,9,10};

	//Define three pointers for the dupilcate arrays
	int *dup1, *dup2, *dup3;

	//Duplicate the arrays
	dup1 = duplicateArray(array1, SIZE1);
	dup2 = duplicateArray(array2, SIZE2);
	dup3 = duplicateArray(array3, SIZE3);

	//Display the original arrays
	cout << "Here are the original array contents:\n";
	displayArray(array1, SIZE1);
	displayArray(array2, SIZE2);
	displayArray(array3, SIZE3);

	//Display the new arrays
	cout << "\nHere are the duplicate arrays:\n";
	displayArray(dup1, SIZE1);
	displayArray(dup2, SIZE2);
	displayArray(dup3, SIZE3);

	//Free the dynamically allocated memory
	//and set pointers to 0
	delete[] dup1;
	delete[] dup2;
	delete[] dup3;
	dup1 = 0;
	dup2 = 0;
	dup3 = 0;

	return 0;	
}

/************************************
The duplicateArray function accepts an int array
and an int that indicates the array's size. The
function creates a new array that is a duplicate
of the argument array and returns a pointer to the
new array. If an invalid size is passed the
function returns null
************************************/

int *duplicateArray(const int *arr, int size){
	int *newArray;

	//Validate the size, if 0 or neg
	//number was passed, return null
	if(size <= 0)
		return NULL;

	//Allocate new array
	newArray = new int[size];

	//Copy the array's contents to the 
	//new array
	for(int index=0; index<size; index++)
		newArray[index] = arr[index];

	//return a pointer to the new array
	return newArray;
}

void displayArray(const int arr[], int size){
	
	for(int index=0; index<size; index++)
		cout << arr[index] << " ";

	cout << endl;
}