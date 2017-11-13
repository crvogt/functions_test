#include <iostream>
#include <fstream>

int main(int argc, char **argv){

	std::ofstream oTextFile;
	std::ifstream iTextFile;
	std::string fileLocation = "/home/carson/functions_test/add_to_text_file/testText.txt";
	std::string line;
	int number;
	float x;

	while(true){
		oTextFile.open(fileLocation, std::ios::app);
		while(true){
			std::cout << "Add number: ";
			std::cin >> number;
	        
	        if(number == 0){
	        	oTextFile.close();
	        	break;
	        }
	        else if(number < 0){
	        	oTextFile.close();
	        	return 1;
	        }
	        else{
	        	oTextFile << number;
	        	oTextFile << "\n";
	        }
		}

		iTextFile.open(fileLocation,std::ios::app);
		while(true){
			// Read values from file
			std::cout << "Numbers in file:\n";
	        while(getline(iTextFile, line)){
	            x = stof(line);
	            std::cout << x << std::endl;
	        }
	        std::cout << std::endl;
	        iTextFile.close();
	        break;
	    }
	}

	return 1;
}