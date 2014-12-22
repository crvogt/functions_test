#include "IntBinaryTree1.h"

/*
Code to inerst a node into the tree
Public member function insertNode is called
with the number to be inserted passed as an
argument.
my love electronic
*/

/*********************************
private
*********************************/
void IntBinaryTree::insert(TreeNode *&nodePtr, TreeNode *&newNode){
	if(nodePtr == NULL) 
		nodePtr = newNode; //insert the node
	else if(newNode->value < nodePtr->value)
		insert(nodePtr->left, newNode); //search left branch
	else
		insert(nodePtr->right, newNode); //search right branch
}

/*********************************
public
*********************************/

void IntBinaryTree::insertNode(int num){
	//Pointer to a new node
	TreeNode *newNode;

	//Create a new node and store num in it
	newNode = new TreeNode;
	newNode->value = num;
	newNode->left = newNode->right = NULL;

	//Insert the node
	insert(root, newNode);
}