#include <vector>
#include <cmath>
#include <iostream>

int main(int argc, char **argv){
	
	std::vector<int> myVec;
	int distance;

	for(int i = 0; i < 10; i++){
		myVec.push_back(i);
	}

	distance = 0;
	int k = 0;
	std::cout << "First method: " << std::endl;
	while(k < myVec.size()){
		for(int i = 0; i < myVec.size(); i++){
			if(k != i){
				distance = std::abs(myVec[k] - myVec[i]);
				if(distance == 1){
					myVec.erase(myVec.begin() + i);
					k = 0;
					break;
				}
			}
		}
		k++;
	}

	std::cout << std::endl;
	for(int i = 0; i < myVec.size(); i++){
		std::cout << "myVec: " << myVec[i] << std::endl;
	}

	myVec.clear();
	std::cout << "Second Method: " << std::endl;
	for(int i = 0; i < 10; i++){
		myVec.push_back(i);
	}

	// Now moving window;
	k = 0;
	while(k < myVec.size()){
		distance = std::abs(myVec[k] - myVec[k + 1]);
		if(distance == 1 && k != myVec.size() - 1){
			myVec.erase(myVec.begin() + (k + 1));
			k = 0;
		}
		k++;
	}

	for(int i = 0; i < myVec.size(); i++){
		std::cout << "myVec: " << myVec[i] << std::endl;
	}

	return 1;
}