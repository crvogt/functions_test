#include <iostream>
using namespace std;

int main(int argc, char **argv){
	fstream lfFile;
	string fileName = "";
	float x = 0, y = 0, z = 0;
	int counter = 1;

	lfFile.open(fileName);
	if(lfFile.is_open()){
		if(!ptamFlag){
			while(getline(lfFile, line)){
				
				switch(counter){
					case 1: x = stof(line);
							counter++;
							break;
					case 2: y = stof(line);
							counter++;
							break;
					case 3: z = stof(line);
							counter = 1;
							lfFile.push_back(Point3f(x, y, z));
							break;
					default:
							cout << "\nNo Match\n";
				}
			}
		}
		
		else if(ptamFlag){
			while(getline(lfFile, line)){
				
				switch(counter){
					case 1: y = stof(line);
							counter++;
							break;
					case 2: z = stof(line);
							counter++;
							break;
					case 3: x = stof(line);
							counter = 1;
							lfFile.push_back(Point3f(x, y, z));
							break;
					default:
							cout << "\nNo Match\n";
				}
			}
		}

		lfFile.close();
	}
	else{
		cout << "Unable to open file" << endl;
	}
}