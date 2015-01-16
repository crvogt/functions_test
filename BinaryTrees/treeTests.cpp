/*
This program builds a binary 
tree with 5 nodes
*/
#include <iostream>
#include "IntBinaryTree1.h"
using namespace std;


int main(int argc, char **argv){

	IntBinaryTree tree;
	int value;

	//Insert some nodes
	cout << "Inserting nodes.\n";
	tree.insertNode(5);
	tree.insertNode(8);
	tree.insertNode(3);
	tree.insertNode(12);
	tree.insertNode(9);

	//Display in order
	cout << "Inorder traversal:\n";
	tree.displayInOrder();

	//Display preorder
	cout << "\nPreorder traversal:\n";
	tree.displayPreOrder();

	//Display postorder
	cout << "\nPostorder traversal:\n";
	tree.displayPostOrder();

	//Search for a value
	cout << "\n\nEnter a value to search for: ";
	cin >> value;
	if(tree.searchNode(value)){
		cout << endl 
			 << value << " is found in the tree\n";
	}
	else{
		cout << endl
			 << value << " wasn\'t found\n";
	}
	cout << "\nEnter another value to search for: ";
	cin >> value;
	if(tree.searchNode(value)){
		cout << endl
			 << value << " is found in the tree\n";
	}
	else{
		cout << endl
			 << value << " wasn't found\n";
	}

	//Now to delete values
	cout << "\nDeleting 12..." << endl;
	tree.remove(12);
	cout << "Deleting 8..." << endl;
	tree.remove(8);

	//Display the values
	cout << "Here are the nodes again:\n";
	tree.displayInOrder();

	return 0;
}