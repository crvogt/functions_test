#include <iostream>
#include <vector>
#include <cstdio>
#include "predictor_node_lib.h"
using namespace std;
//For use with testing class
/*
class ValueBlock{
private:
	double m;
public:
	double returnM(void) const{
		return m;
	}
	void setM(double val){
		m = val;
	}
};
*/


int main(int argc, char **argv){
	const int arrayVal = 5;
	int i = 0;
	char question = 'y';

	//Cube pointer
	ValueBlock *cubePointer;

	//Create a vector of cube objects
	vector<ValueBlock *> cubeVector;



	//Preparing data to pass to vectors
	double initLat[arrayVal] = {55.862282, 55.862278, 55.862278, 55.866093, 55.86235};
	double initLon[arrayVal] = {-3.1532116, -3.1532202, -3.1530969, -3.1532218, -3.153194};
	//Don't necessarily need to specify number of elements if initializing
	double initAlt[] = {154.77, 154.36, 179.98, 223.97, 140.54};

	//Send GPS values through. Check if they match any blocks. If not, create a new block
	

	/*
	while(i < arrayVal){
		//if(cubeVector.size() == 0){//vector size is zero, create a new object
		//}
		//cubePointer = new ValueBlock;
		//cubePointer->setM(initAlt[i]);
		//cubeVector.push_back(cubePointer);

		i++;
	}
	*/
	/*
	for(int j = 0; j < 5; j++){
		cout << "\n\n" << cubeVector[j]->returnM() << endl;
	}
	*/

	/*
	int l = 0, m = 0, k = 0;
	cout << "\n\nWould you like to add another value?: ";
	cin >> question;
	while(question == 'y'){
		cubePointer = new ValueBlock;
		cubePointer->setM(initLat[m]);
		cubeVector.push_back(cubePointer);
		l = i + m;
		cout << "m = " << m << "and i = " << l << endl;
		cout << "\nanother?: ";
		cin >> question;
		m++;
	}

	cout << "\nThanks for playing!" <<  endl;
	cout << "\n\nDisplaying the list:\n";
	for(k = 0; k < l; k++){
		cout << cubeVector[k]->returnM() << endl;
	}
	/*Vector Test*/
	/*
	for(int i = 0; i < 5; i++){
		gpsLatValsVec.push_back(initLat[i]);
		printf("\n GPS Lat vector val %d is %lf", i, gpsLatValsVec[i]);
	}
	*/

	//cout << endl;

	//Cube vector

	
	/*
	Get GPS values,
	if vector = 0 elements
	create a new instance of the class
	*/
	
	/*
	Get GPS values
	if vector ~= 0
	Check GPS values vs current vals
	if no similar GPS vals
	create new instance of class and store in vector
	*/
	//Store its address in a vector

	//As the plane flies, build the configuration space

	//Send measurements to appropriate config cube.

	return 0;
}