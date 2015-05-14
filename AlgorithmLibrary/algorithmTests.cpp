#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


struct values{
	float a;
	float b;
};

//void printResults(vector<values> &);

void addHolderValues(values *);

int main(int argc, char **argv){
	//vector<values> valueVec;
	//float lower, upper;

	values holder;
	values holderPtr;

	holderPtr.a = 0;
	holderPtr.b = 0;
	holder = {5.3, 6.7};
	/*
	valueVec.push_back(holder);
	holder = {44, 33};
	valueVec.push_back(holder);
	holder = {422, 45};
	valueVec.push_back(holder);
	valueVec.push_back(holder);

	printResults(valueVec);
	
	for(int i = 0; i < valueVec.size(); i++){
		//cout << "\nValue of a: " << valueVec[i].a 
		//	 << "\nValue of b: " << valueVec[i].b << endl;
	}

	//cout << "\nNew size is: " <<  valueVec.size() << endl;
	*/ 
	cout << "\nFirst address of struct " << &holderPtr;

	addHolderValues(&holderPtr);

	cout << "\nHolder pointer values\n"
		 << "value a " << holderPtr.a
		 << "\nvalue b " << holderPtr.b 
		 << "\naddress of struct " << &holderPtr << endl;

	//May need to use iterator here...
	//lower = *min_element(valueVec[0].a, valueVec[3].a);
	return 0;
}

void addHolderValues(values *holderPtr){
	holderPtr->a = 5;
	holderPtr->b = 6;
}
/*
void printResults(vector<values> &valueVector){
	int size = valueVector.size();
	cout << endl;
	cout << valueVector[0].a <<endl; 
	
	for(int i = 0; i < size; i++){
	//	cout << "value a: " << valueVector[i].a << "\nvalue b: " << valueVector[i].b 
			 //<< endl;
	}

	//cout << "\nSize is: " << size << endl;
	values newHolder = {5433.4, 8784.99};

	valueVector.push_back(newHolder);
}
*/
/*************8
do some further investigation later, might put it off for now though
if those are the only functions I'm interested in at the moment :)
*********/