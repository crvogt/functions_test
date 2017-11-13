#include <iostream>
#include <vector>

int main(int argc, char **argv){
	std::vector<int> myVec;

	for(int i = 0; i < 10; i++){
		myVec.push_back(i);
		std::cout << i << std::endl;
	}

	// Now sort such that it counts down from 10;
	int temp;
	for(int i = 0; i < myVec.size(); i++){
		for(int j = 0; j < myVec.size(); j++){
			if(myVec[i] > myVec[j]){
				temp = myVec[i];
				myVec[i] = myVec[j];
				myVec[j] = temp;
				// std::cout << "\n";
				// for(int k = 0; k < myVec.size(); k++){
				// 	std::cout << myVec[k] << std::endl;
				// }
				// std::cout << "\n";
			}
		}
	}

	std::cout << "\nsorted" << std::endl;
	for(int i = 0; i < myVec.size(); i++){
		std::cout << myVec[i] << std::endl;
	}

	return 1;
}