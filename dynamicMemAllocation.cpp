#include <cstdio>
#include <cstring> //for strlen

int main(){
	char *str="Idle hands";
	int len = strlen(str); 		//pointer q...

	char *ptr;					//pointer to char
	ptr = new char[len+1];		//set aside mem
								//string + '\0'

	strcpy(ptr, str);			//copy str to new memory area ptr

	printf("ptr= %s\n", ptr);	//Show that ptr is now in str

	delete[] ptr;				//release ptr's memory

	return 0;		
}

