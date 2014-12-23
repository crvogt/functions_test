#include <iostream>
#include <cstdio>
using namespace std;

int g_One = 1;

void func(int *, int **);

int main(){

	int nvar = 2;
	int *pvar = &nvar;
	int **pvar2 = &pvar;
	func(pvar, pvar2);

	cout << "\nAnd the address exiting: "
		 << pvar << endl;
	int val;
	
	cout << endl;
	cout << *pvar << endl << endl;
	//cout << "Test" << endl;

	return 0;
}

void func(int *pValInt, int **pValInt2){

	int localValue = 10;

	cout << "\nAddress is: "
		 << pValInt;
	pValInt = &g_One;
	cout << "\npValInt is now: "
		 << *pValInt << endl;
	cout << "Now the address is: "
		 << pValInt << endl;

	pValInt = &localValue;
	cout << "And for a local val: "
		 << pValInt << endl;
	**pValInt2 = *pValInt;
}
