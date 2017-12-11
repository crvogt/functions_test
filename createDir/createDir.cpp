#include <sys/stat.h>
#include <iostream>
#include <stdlib.h>
#include <string>

int main(int argc, char **argv){
	int dir_err; 
	std::string fileStart = "mkdir num";
	std::string fileName;


	for(int i = 5; i <= 95; i++){
		fileName = fileStart + std::to_string(i);
		const char *cstr = fileName.c_str();
		system(cstr);
	}

	system("ls");
    // for(int i = 5; i <= 95; i++){
    //     dir_err = mkdir("/home/carson/functions_test/createDir/dir" + std::to_string(i), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    //     if (-1 == dir_err)
    //     {
    //         printf("Error creating directory!n");
    //         exit(1);
    //     }
    // }

    return 1;
}