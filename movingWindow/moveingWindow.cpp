#include <iostream>

int main(int argc, char **argv){
	int array[20];
	int window[5];

	for(int i = 0; i < 20; i++){
		array[i] = i;
	}

	for(int i = 0; i < 5; i++){
		window[i] = array[i];
	}

	for(int i = 0; i < 20; i++){
		if(i < (19 - 5/2 - 1)){
			// // Now shift
			for(int j = 0; j < 5; j++){
				window[j] = array[i+j];
			}
			std::cout << "i: " << i << std::endl;
			for(int j = 0; j < 5; j++){
				std::cout << window[j] << std::endl;
			}
		}
	}

	std::cout << "20 - 5/2 -2 = " << 20-5/2-2 << std::endl;

	return 1;
}