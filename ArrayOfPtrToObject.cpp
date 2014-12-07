#include <iostream>
using namespace std;

class person{
protected: 			
					//Read up on inheritance
					//for protected
	char name[40];
public:
	void setName(){
		cout << "Enter name: ";
		cin >> name;
	}
	void printName(){
		cout << "\nName is: " << name;
	}
};

int main(){
	person *persPtr[3]; //array of pointers
	int n=0;			  //people in array
	char choice;

	do{				//put persons in array
		persPtr[n] = new person; //new person object
		persPtr[n]->setName(); //set person's name
		n++;

		cout << "Enter another (y/n)? ";
		cin >> choice;
	}while(choice == 'y');

	//print the names
	for (int j=0; j<n; j++){
		cout << "\nPerson number " << j+1;
		persPtr[j]->printName();
	}

	cout << endl;

	return 0;
}
