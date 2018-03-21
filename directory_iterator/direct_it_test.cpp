#include <iostream>
#include <dirent.h>
#include <string>

using namespace std;

int main(int argc, char **argv){
	char myFile[] = "0.jpg";
	char myFile2[] = "0.jpg";
	string myFile3 = "0.jpg";
	bool stopFlag = false;
	// string entString;
	DIR *dir;
	struct dirent *ent;
	if((dir = opendir("/home/carson/")) != NULL){
		// print all the files and directories within directory
		while((ent = readdir(dir)) != NULL){
			cout << ent->d_name << endl;
			string entString(ent->d_name);
			if(entString == myFile3){
				cout << "\nFound 0.jpg!\n";
				cout << "\nUsed ==\n";
				stopFlag = true;
				// return 1;
			}
			if(entString.compare(myFile3) == 0){
				cout << "\nEureka! using compare\n";
				stopFlag = true;
			}

			if(stopFlag)
				return 1;
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