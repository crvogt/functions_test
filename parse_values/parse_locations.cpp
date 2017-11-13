#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(int argc, char **argv){
	std::string poseFileName = "/home/carson/functions_test/parse_values/pr2V3.txt";
	std::string poseMatName  = "/home/carson/functions_test/parse_values/pr2V3M.txt";
	// std::string poseFileName = "pr2V3.txt";
	// std::string poseMatName = "pr2V3M.txt";
	std::string line;
	std::ifstream poseFile;
	std::ofstream poseMFile;
	int counter = 1;
	float x, y, z;
	std::vector<float> xVec;
	std::vector<float> yVec;
	std::vector<float> zVec;

	poseFile.open(poseFileName);
	if(poseFile.is_open()){
		std::cout << "Opening files..." << std::endl;		
		while(getline(poseFile, line)){
			
			switch(counter){
				case 1: x = stof(line);
						xVec.push_back(x);
						counter++;
						break;
				case 2: y = stof(line);
						yVec.push_back(y);
						counter++;
						break;
				case 3: z = stof(line);
						zVec.push_back(z);
						counter = 1;
						break;
				default:
						std::cout << "\nNo Match\n";
			}
		}
	}
	else{
		std::cout << "Files not opening..." << std::endl;
		std::cout << poseFileName << std::endl;
	}
	std::cout << "Closing files...\n";
	poseFile.close();
	
	poseMFile.open(poseMatName);
	if(poseMFile.is_open()){	
		for(int i = 0; i < xVec.size(); i++){
			poseMFile << xVec[i] << "," << yVec[i] << "," << zVec[i] << "\n";
		}
	}
	else{
		std::cout << "MATLAB file not opening..." << std::endl;
	}

	return 1;
}