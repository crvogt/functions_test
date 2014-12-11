#include "NumberList1.h"
#include <iostream>
using namespace std;

/*
This program demonstrates a simple append
operation on a linked list
*/

int main(int argc, char **argv){

	//Define a NumberList object
	NumberList1 list;

	//Append some values to the list
	list.appendNode(2.5);
	list.appendNode(7.9);
	list.appendNode(12.6);

	//Insert a node in the middle of the list
	list.insertNode(10.5);

	//Display the values in this list
	list.displayList();

	return 0;
}