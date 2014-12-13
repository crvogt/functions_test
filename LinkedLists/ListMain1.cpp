#include "NumberList1.h"
#include <iostream>
using namespace std;

/*
This program demonstrates the delete node
operation on a linked list
*/

int main(int argc, char **argv){

	//Define a NumberList object
	NumberList1 list;

	//Append some values to the list
	list.appendNode(2.5);
	list.appendNode(7.9);
	list.appendNode(12.6);

	//Display the list
	cout << "Here are the initial values:\n";
	list.displayList();
	cout << endl;

	//Delete the middle node
	cout << "Now deleting the node in the middle:\n";
	list.deleteNode(7.9);

	//Display the list
	cout << "Here are the remaining values:\n";
	list.displayList();
	cout << endl;

	//Deleting the rest of the nodes
	cout << "Deleting the rest of the nodes:\n";
	list.deleteNode(2.5);
	list.deleteNode(12.6);

	//Display whatever remains
	cout << "The remains:\n";
	list.displayList();

	return 0;
}