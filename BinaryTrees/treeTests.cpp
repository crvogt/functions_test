/*
This program builds a binary 
tree with 5 nodes
*/
#include <iostream>
#include "IntBinaryTree1.h"
using namespace std;


int main(int argc, char **argv){

	IntBinaryTree tree;

	tree.insertNode(5);
	tree.insertNode(7);
	tree.insertNode(2);
	tree.insertNode(6);
	tree.insertNode(26);
	return 0;
}


