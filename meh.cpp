#include <iostream>

int main(int argc, char **argv){
	int userIn;


	while(true){

	std::cin >> userIn;
		std::cout << "userIn: " <<  userIn;

		switch(userIn){
			case 1: std::cout << "left\n";
			case 2: std::cout << "right\n";
			default: std::cout << "default\n";
		}

	}

	return 1;
}