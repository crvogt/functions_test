//using new to get memory for strings
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

class String{
private:
	//pointer to a string
	char *str;
public:
	//a constructor with one arg
	String(char *s){
		int length = strlen(s);
		//get memory
		str = new char[length+1];
		//copy argument to it
		strcpy(str, s);
	}
	//destructor
	~String(){
		printf("\nDeleting str\n");
		delete[] str;
		printf("Memory has been released\n");
	}
	//Display the string
	void display(){
		//gonna use cout for now
		cout << str << endl;
	}
};

int main(int argc, char **argv){
	//uses 1 argument constructor
	String s1="whosawhatsit";

	cout << "s1="; //display string
	s1.display();
	
	return 0;
}