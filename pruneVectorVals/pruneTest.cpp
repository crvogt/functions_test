#include <iostream>
#include <vector>

int main(int argc, char **argv){

	std::vector<int> testVals;
	for(int i = 0; i < 10; i++){
		testVals.push_back(i);
		std::cout << "i: " << i << std::endl;
	}

	std::cout << "removing 5th value (4)" << std::endl;

	for(int i = 0; i < testVals.size(); i++){
		if(testVals[i] == 4 || testVals[i] == 8){
			testVals.erase(testVals.begin()+i);
		}
	}

	std::cout << "resulting vector: " << std::endl;

	for(int i = 0; i < testVals.size(); i++){
		std::cout << "val: " << testVals[i] << std::endl;
	}

	std::cout << "int test: " << std::endl;

	int a, b;
	a = 5;
	b = a/2;
	std::cout << "b: " << b << std::endl;

	float testArray[5];

	for(int i = 0; i < 5; i++){
		testArray[i] = i;
	}

	std::cout << "Array values: " << std::endl;
	for(int i = 0; i < 5; i++){
		std::cout << testArray[i] << std::endl;
	}

	return 1;
}