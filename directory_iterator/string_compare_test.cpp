#include <iostream>
#include <dirent.h>
#include <string.h>
// #include <system>

using namespace std;

int main(int argc, char **argv){
	string myFile;
	string moveFile = "mv data/";
	DIR *dir;
	string numStr, phiStr, thetaStr;
	int num, phi, theta;
	struct dirent *ent;
	int counter = 0;
	if((dir = opendir("/home/carson/functions_test/directory_iterator/data")) != NULL){
		// print all the files and directories within directory
		while((ent = readdir(dir)) != NULL){
			cout << ent->d_name << endl;
			string entString(ent->d_name);
			// strlen knows nothing about std::string. 
			// It is a C function that returns the length of a null-terminated string.
			// int length = strlen(entString);
			string::size_type length = entString.size();
			if(length > 3){
				int from = 0, to = 0;
				int parts = 0;
				for(int i = 0; i < length; i++){
					if(entString[i] == '_'){
						if(parts == 0){
							numStr = entString.substr(0,i);
							num = stoi(numStr);
							parts++;
							from = i + 1;
						}
						else if(parts == 1){
							to = i - from;
							thetaStr = entString.substr(from,to);
							theta = stoi(thetaStr);
							parts++;
							from = i + 1;
						}
					}
					else if(entString[i] == '.'){
						to = i - from;
						phiStr = entString.substr(from,to);
						phi = stoi(phiStr);
					}
				}

				cout << "\nnum: " << num << " theta: " << theta << " phi: " << phi << endl;
			}
			moveFile += entString + " .."; 
			system(moveFile);
		}
		closedir(dir);
	}
	else{
		// Could not open directory
		perror("");
		return EXIT_FAILURE;
	}

	return 1;
}