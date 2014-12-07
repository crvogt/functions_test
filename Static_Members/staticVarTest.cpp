#include <iostream>
#include "Tree.h"
using namespace std;

int main(int argc, char **argv){
	//Define three tree objects
	Tree oak;
	Tree palm;
	Tree maple;

	//Display the number of Tree objects
	cout << "\ntenemos " << palm.getObjectCount();
	cout << " currently" << endl;

	return 0;
}