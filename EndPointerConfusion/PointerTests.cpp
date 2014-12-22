#include <iostream>
using namespace std;

void functionWithPointer(int *, int **);

void PtrToPtr(int **);

int main(int argc, char **argv){
	/*
	I want to pass a pointer 
	and see what happens with it.
	Why do I need a reference to a 
	pointer? Or a ref to ptr?
	*/

	int *var1ptr, **var2ptr;
	int nVal = 5;

	//Set address of var1ptr to nVal
	//location
	var2ptr = &var1ptr;
	var1ptr = &nVal;

	//Now * is dereference
	cout << "\nvar1ptr is: " << *var1ptr
		 << endl;
	cout << "var2ptr is: " << **var2ptr
		 << endl;

	//Simple in-main change
	*var1ptr *= 5;

	cout << "\n\nAnd modified var1ptr once: " 
		 << *var1ptr << endl;
	cout << "And didn't touch var2ptr: "
		 << **var2ptr << endl;

	/*
	Now I want to see what happens when a
	pointer is changed in a function
	if that is possible. Binary tree education
	suggests otherwise, at least sort of
	*/
	
	functionWithPointer(var1ptr, var2ptr);

	cout << "\nHas var1ptr  been modified?: "
		 << *var1ptr << endl;

	/*
	Now modifying the pointer to a pointer
	in the function, thereby modifying the
	original pointer...
	*/

	PtrToPtr(var2ptr);

	cout << "\nThe value of the original ptr "
		 << "is now: " << *var1ptr << endl;

	return 0;
}

void functionWithPointer(int *passedPtrToVal, int **passedPtrToPtr){
	/*
	*/
	cout << "\n\nthe passedPtrToVal is: "
		 << *passedPtrToVal << endl;
	*passedPtrToVal *= 4;
	cout << "The passedPtrToPtr is: "
		 << **passedPtrToPtr << endl;
}

void PtrToPtr(int **pointerToPtr){
	cout << "\n\n\nNow Passing pointer to pointer"
		 << " only" << endl;

	**pointerToPtr *= 50;
}